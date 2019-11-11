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

std::vector<my_pair> find_zeros_coordinates(matrix m)
{
    std::vector<my_pair> zeros_coordinates;
    my_pair pair_index;
    for(int row = 0; row < m.size(); row++)
    {
        for(int col = 0; col < m.size(); col++)
        {
            if(m[row][col] == 0)
            {
                pair_index = std::make_pair(row, col);
                zeros_coordinates.push_back(pair_index);
            }
        }
    }
    return zeros_coordinates;
}

std::vector<my_pair> min_apart_from_zero_row(matrix m)
{
    auto coordinates = find_zeros_coordinates(m);
    std::vector<my_pair> vect_of_mins;
    for(const auto& elem : coordinates)
    {
        m[elem.first][elem.second] = INF;
        double r_min = find_min_in_a_row(elem.first, m);
        double c_min = find_min_in_a_col(elem.second, m);
        auto new_pair = std::make_pair(r_min,c_min);
        vect_of_mins.push_back(new_pair);
        m[elem.first][elem.second] = 0;
    }
    return vect_of_mins;
}

matrix make_no_entry(int row, int col, matrix m)
{
    for(int i = 0; i < m.size(); i++)
    {
        for(int j = 0; j < m.size(); j++)
        {
            if(i == row or j == col)
                m[i][j] = INF;
        }
    }
    m[row][col] = INF;
    return m;
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

            //auto coordinates = find_zeros_coordinates(cost_matrix);
            //print_vect_of_pairs(coordinates);
            //std::cout<<std::endl;
            auto mins = min_apart_from_zero_row(cost_matrix);
            print_vect_of_pairs(mins);
        }
        i++;
    }

    std::cout<<"Lower bound: "<<lower_bound<<std::endl;
    return cost_matrix;
    //    std::vector<int> min_way = sort();
    //    return min_way;
}
//  */
int main() {

    matrix cost_matrix {
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
    //std::cout<<std::endl;
    //print(cost_matrix);
    //std::cout<<std::endl;
    //std::cout<<find_min_in_a_row(4,cost_matrix);
    //std::cout<<find_min_in_a_col(0,mat2)<<std::endl;
    //std::cout<<find_min_in_a_col(1,mat2)<<std::endl;
    //std::cout<<find_min_in_a_col(2,mat2)<<std::endl;
    //std::cout<<find_min_in_a_col(3,mat2)<<std::endl;
    //std::cout<<find_min_in_a_col(4,mat2)<<std::endl;
    //std::cout<<is_zero_in_col(0,mat2)<<std::endl;
    //std::cout<<is_zero_in_col(1,mat2)<<std::endl;
    //std::cout<<is_zero_in_col(2,mat2)<<std::endl;
    //std::cout<<is_zero_in_col(3,mat2)<<std::endl;
    //std::cout<<is_zero_in_col(4,mat2)<<std::endl;
   /* print(reduce_row(0,cost_matrix));
    std::cout<<std::endl;
    print(reduce_row(1,cost_matrix));
    std::cout<<std::endl;
    print(reduce_row(2,cost_matrix));
    std::cout<<std::endl;
    print(reduce_row(3,cost_matrix));
    std::cout<<std::endl;
    print(reduce_row(4,cost_matrix));
    std::cout<<std::endl;
    print(reduce_col(0,cost_matrix));
    std::cout<<std::endl;
    print(reduce_col(1,cost_matrix));
    std::cout<<std::endl;
    print(reduce_col(2,cost_matrix));
    std::cout<<std::endl;
    print(reduce_col(3,cost_matrix));
    std::cout<<std::endl;
    print(reduce_col(4,cost_matrix));
    std::cout<<std::endl;
*/
   // bool x = is_zero_in_each_col_and_row(cost_matrix);
   // std::cout<< x <<std::endl;
    matrix test = tsp(cost_matrix);
    print(test);
    return 0;
}