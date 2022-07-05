#ifndef CJ_RANDOM_HPP
#define CJ_RANDOM_HPP

#include <vector>
#include <fstream>
#include <cstdlib> // rand

using std::vector;

#define NUM_RAND_ITEMS 5000
#define SRAND_SEED 48334

void generateRandFile(int num);
void readFromRandFile(const char * fname, std::vector<int> * v);
void cj_srand(int seed);
int cj_rand();
extern vector<int> rand_num_list;
extern int cj_rand_seed;
extern int cj_rand_max;

#endif