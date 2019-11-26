#include <iostream>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include <string>
#include <numeric>
#include <iomanip>
using vect = std::vector<double>;
using matrix = std::vector<std::vector<double>>;
using my_pair = std::pair<double,double>;
#define INF (NAN)
std::vector<my_pair> solution;
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
void print(matrix m)
{
    for(const auto &row_vec : m)
    {
        for(const auto &elem : row_vec)
        {
            std::cout<<std::setw(5);
            std::cout<<elem;
        }
        std::cout<<std::endl;
    }
}

void print_vect_of_pairs(std::vector<my_pair> output)
{
    for(auto &x:output)
    {
        std::cout<<x.first<<" , "<<x.second<<std::endl;
    }
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
        for(int col = 0; col < m.size(); col++)
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
        for(int j = 0; j < m.size(); j++)
        {
            if(i == row or j == col)
                m[i][j] = INF;
        }
    }
    m[col][row] = INF;
    return m;
}
/*
void matrix2x2_fun(matrix m)
{
    std::vector<int> row_indexes;
    std::vector<int> col_indexes;
    if(!zeros_check_rows())
    {
        reduce_all_rows();
    }
    if(!zeros_check_cols()){reduce_all_cols();}
    for(int i = 0; i<m.size() ; i++)
    {
        if(is_zero_in_row(i,m))
            row_indexes.push_back(i);
        if(is_zero_in_col(i,m))
            col_indexes.push_back(i);
    }
    for(int i = 0; i<row_indexes.size(); i++)
    {
        for(int j = 0; j<col_indexes.size() ; j++)
        {
            int row_index = row_indexes[i];
            int col_index = col_indexes[j];
            int other_row = row_indexes[row_indexes.size() - 1 - i];
            int other_col = col_indexes[col_indexes.size() - 1 - j];
            if(std::isnan(m[row_index][col_index])){
                solution.push_back(std::make_pair(row_index, other_col));
                solution.push_back(std::make_pair(other_row, col_index));
            }
        }
    }
}
*/

std::vector<int>sort_and_give_result()
{
    std::vector<my_pair> sorted_vec;
    my_pair tmp;
    std::vector<int> vec_results;
    for (std::size_t i = 0; i < solution.size(); i++)
    {
        if (i == 0)
        {
            sorted_vec.push_back(solution[i]);
        }
        tmp = sorted_vec[i];
        for (std::size_t j = 0; j < solution.size(); j++)
        {
            if (tmp.second == solution[j].first)
            {
                sorted_vec.push_back(solution[j]);
                break;
            }
        }
    }

    for (int i = 0; i < sorted_vec.size(); i++)
    {
        vec_results.push_back(std::get<0>(sorted_vec[i])+1);
    }
    return vec_results;
}

void print_solution() {

    for(auto elem: solution)
    {
        std:: cout << " ("<<elem.first+1 <<" "<< elem.second+1<<") ";
    }

}
matrix tsp(std::vector<std::vector<double>> cost_matrix)
{
    double lower_bound = 0;
    double min_help = 0;
    int i = 0;
    while(i<cost_matrix.size())
    {
        if(!is_zero_in_each_col_and_row(cost_matrix))
        {
            for(int j = 0; j<cost_matrix.size(); j++)
            {
                if(!is_zero_in_row(j,cost_matrix))
                {
                    min_help = find_min_in_a_row(j,cost_matrix);
                    lower_bound = lower_bound + min_help;
                    cost_matrix = reduce_row(j,cost_matrix);
                }
            }

            for(int k = 0; k<cost_matrix.size(); k++)
            {
                if(!is_zero_in_col(k,cost_matrix))
                {
                    min_help = find_min_in_a_col(k,cost_matrix);
                    lower_bound = lower_bound + min_help;
                    cost_matrix = reduce_col(k,cost_matrix);
                }
            }
            print(cost_matrix);
        }
        /*
        std::cout<<"Lower bound: "<<lower_bound<<std::endl;
        auto mins = min_apart_from_zero(cost_matrix);
        cost_matrix = make_no_entry(mins.first, mins.second,cost_matrix);
        print(cost_matrix);
        std::cout<<std::endl;
         */
        i++;
    }

    //std::cout<<"Lower bound: "<<lower_bound<<std::endl;
    return cost_matrix;
}

int main() {

    matrix cos_matrix {
            {INF, 10, 8, 19, 12},
            {10, INF, 20, 6, 3},
            {8, 20, INF, 4, 2},
            {19, 6, 4, INF, 7},
            {12, 3, 2, 7, INF}
    };

    matrix mat2 {
            {INF,  0.0,  1.0,  2.0,  5.0},
            {3.0,  INF,  4.0,  6.0,  4.0},
            {4.0,  4.0,  INF,  5.0,  4.0},
            {2.0,  6.0,  5.0,  INF,  4.0},
            {7.0,  3.0,  8.0,  6.0,  INF},
    };

    matrix mat1 {
            {INF, 12,   3,  45,   6},
            {78, INF,  90,  21,   3},
            { 5,  56, INF,  23,  98},
            {12,   6,   8, INF,  34},
            { 3,  98,   3,   2, INF}
    };

    matrix test = tsp(mat2);
    print(test);
    return 0;
}