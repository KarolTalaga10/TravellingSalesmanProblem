// Karol TALAGA 302929

#ifndef TSP_TSP_HPP
#define TSP_TSP_HPP

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
double get_forbidden_cost();
matrix transpose(matrix m);
double find_min_in_a_row(int row, matrix m);
double find_min_in_a_col(int col, matrix& m);
bool is_zero_in_row(int row, matrix m);
bool is_zero_in_col(int col, matrix& m);
bool is_zero_in_each_col_and_row(matrix m);
matrix reduce_row(int row, matrix& m);
matrix reduce_col(int col, matrix& m);
std::vector<std::pair<double, my_pair >> find_zeros_coordinates(matrix m);
my_pair min_apart_from_zero(matrix m);
matrix make_no_entry(int row, int col, matrix& m);
bool is_zero_or_nan_everywhere(matrix m);
void zeros_matrix(matrix m);
std::vector<int> sort_path();
std::vector<int> tsp(std::vector<std::vector<double>> cost_matrix);
#endif //TSP_TSP_HPP
