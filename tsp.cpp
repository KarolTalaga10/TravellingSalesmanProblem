// Karol TALAGA 302929

#include "tsp.hpp"
std::vector<my_pair> solution;
double get_forbidden_cost()
{
    return INF;
}

matrix transpose(matrix m)
{
    matrix transposition_of_matrix(m[0].size(),vect(m.size()));
    for(int row_index = 0; row_index < m.size(); row_index++)
    {
        for(int col_index = 0; col_index < m[row_index].size() ; col_index++)
        {
            transposition_of_matrix[row_index][col_index] = m[col_index][row_index];
        }
    }
    return transposition_of_matrix;
}

double find_min_in_a_row(int row, matrix m)
{
    double min = m[row][0];
    int i = 0;
    while(std::isnan(min) && i < m[row].size())
    {
        min=m[row][i];
        i++;
    }
    for(const auto &elem : m[row])
    {
        if(elem < min)
            min = elem;
    }
    return min;
}

double find_min_in_a_col(int col, matrix& m)
{
    matrix new_matrix = transpose(m);
    double min_col = find_min_in_a_row(col,new_matrix);
    return min_col;
}

bool is_zero_in_row(int row, matrix m)
{
    for(const auto &elem : m[row])
        if(elem == 0) return true;
    return false;
}

bool is_zero_in_col(int col, matrix& m)
{
    matrix new_matrix = transpose(m);
    bool zero_in_col = is_zero_in_row(col, new_matrix);
    return zero_in_col;
}

bool is_zero_in_each_col_and_row(matrix m)
{
    for(int i = 0; i<m.size(); i++)
    {
        if(!is_zero_in_row(i,m))
            return false;
    }

    for(int i = 0; i<m.size(); i++)
    {
        if(!is_zero_in_col(i,m))
            return false;
    }
    return true;
}

matrix reduce_row(int row, matrix& m)
{
    double min = find_min_in_a_row(row, m);
    for(auto& elem: m[row])
    {
        elem = elem - min;
    }
    return m;
}

matrix reduce_col(int col, matrix& m)
{
    matrix help = transpose(m);
    help = reduce_row(col, help);
    m = transpose(help);
    return m;
}

std::vector<std::pair<double, my_pair >> find_zeros_coordinates(matrix m)
{
    std::vector<std::pair<double, my_pair >> zeros_coordinates;
    my_pair pair_index;
    for(int row = 0; row < m.size(); row++)
    {
        for(int col = 0; col < m[row].size(); col++)
        {
            if(m[row][col] == 0)
            {
                pair_index = std::make_pair(row, col);
                std::pair<double, my_pair> new_pair = std::make_pair(0, pair_index);
                zeros_coordinates.push_back(new_pair);
            }
        }
    }
    return zeros_coordinates;
}

my_pair min_apart_from_zero(matrix m)
{
    auto coordinates = find_zeros_coordinates(m);
    for(auto& elem : coordinates)
    {
        m[elem.second.first][elem.second.second] = INF;
        double r_min = find_min_in_a_row(elem.second.first, m);
        double c_min = find_min_in_a_col(elem.second.second, m);
        double sum = r_min + c_min;
        elem.first = sum;
        m[elem.second.first][elem.second.second] = 0;
    }
    double max_from_mins = coordinates[0].first;
    my_pair from_to = coordinates[0].second; // first - row to delete, second - col to delete
    for(auto elem : coordinates)
    {
        if(elem.first > max_from_mins)
        {
            max_from_mins = elem.first;
            from_to = elem.second;
        }
    }
    solution.push_back(from_to);
    return from_to;
}

matrix make_no_entry(int row, int col, matrix& m)
{
    for(int i = 0; i < m.size(); i++)
    {
        for(int j = 0; j < m[i].size(); j++)
        {
            if(i == row or j == col)
                m[i][j] = INF;
        }
    }
    m[col][row] = INF;
    return m;
}

bool is_zero_or_nan_everywhere(matrix m)
{
    bool flag = false;
    for(std::size_t i = 0; i < m.size(); i++)
    {
        for(std::size_t j = 0; j < m[i].size(); j++)
        {
            if(m[i][j] == 0 or std::isnan(m[i][j]))
            {
                flag = true;
            }
            else
            {
                flag = false;
                break;
            }
        }
    }
    return flag;
}

void zeros_matrix(matrix m)
{
    if(!is_zero_in_each_col_and_row(m))
    {
        for(int j = 0; j<m.size(); j++)
        {
            if(!is_zero_in_row(j,m))
            {
                m = reduce_row(j,m);
            }
        }
        for(int k = 0; k<m.size(); k++)
        {
            if(!is_zero_in_col(k,m))
            {
                m = reduce_col(k,m);
            }
        }
    }
    std::vector<int> row_ind;
    std::vector<int> col_ind;
    for(int i = 0; i<m.size() ; i++)
    {
        if(is_zero_in_row(i, m))
        {
            row_ind.push_back(i);
        }
        if(is_zero_in_col(i, m))
        {
            col_ind.push_back(i);
        }
    }
    for(int i = 0; i<row_ind.size(); i++)
    {
        for(int j = 0; j<col_ind.size() ; j++)
        {
            int row_index_v1 = row_ind[i];
            int col_index_v1 = col_ind[j];
            int row_index_v2 = row_ind[row_ind.size() - 1 - i];
            int col_index_v2 = col_ind[col_ind.size() - 1 - j];
            if(std::isnan(m[row_index_v1][col_index_v1]))
            {
                solution.emplace_back(std::make_pair(row_index_v1, col_index_v2));
                solution.emplace_back(std::make_pair(row_index_v2, col_index_v1));
            }
        }
    }
}

std::vector<int> sort_path()
{
    std::vector<my_pair> final_path;
    my_pair tmp;
    std::vector<int> sorted;
    for (std::size_t i = 0; i < solution.size(); i++)
    {
        if (i==0)
        {
            final_path.push_back(solution[i]);
        }
        tmp = final_path[i];
        for (std::size_t j = 0; j < solution.size(); j++)
        {
            if (tmp.second == solution[j].first)
            {
                final_path.push_back(solution[j]);
                break;
            }
        }
    }

    for (int i = 0; i < final_path.size(); i++)
    {
        sorted.push_back(std::get<0>(final_path[i])+1);
    }
    return sorted;
}


std::vector<int> tsp(std::vector<std::vector<double>> cost_matrix)
{
    int i = 0;
    while(i<cost_matrix.size())
    {
        if(!is_zero_in_each_col_and_row(cost_matrix))
        {
            for(int j = 0; j<cost_matrix.size(); j++)
            {
                if(!is_zero_in_row(j,cost_matrix))
                {
                    cost_matrix = reduce_row(j,cost_matrix);
                }
            }
            for(int k = 0; k<cost_matrix.size(); k++)
            {
                if(!is_zero_in_col(k,cost_matrix))
                {
                    cost_matrix = reduce_col(k,cost_matrix);
                }
            }
        }
        auto mins = min_apart_from_zero(cost_matrix);
        cost_matrix = make_no_entry(mins.first, mins.second,cost_matrix);
        if(is_zero_or_nan_everywhere(cost_matrix))
        {
            zeros_matrix(cost_matrix);
            break;
        }
        i++;
    }
    std::vector<int> best_way = sort_path();
    return best_way;
}
