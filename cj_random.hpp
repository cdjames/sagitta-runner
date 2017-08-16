#ifndef CJ_RANDOM_HPP
#define CJ_RANDOM_HPP

#include <vector>
#include <fstream>

using std::vector;

void readFromRandFile(const char * fname, std::vector<int> * v);
void cj_srand(int seed);
int cj_rand();
extern vector<int> rand_num_list;
extern int cj_rand_seed;
extern int cj_rand_max;

#endif