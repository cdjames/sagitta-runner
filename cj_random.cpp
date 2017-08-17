#include "cj_random.hpp"

vector<int> rand_num_list;
int cj_rand_seed;
int cj_rand_max;

void generateRandFile() {
	srand(SRAND_SEED);
	std::ofstream f;
	f.open ("vals.cjr");
	if(f.is_open()) {
		for (int i = 0; i < NUM_RAND_ITEMS; ++i)
		{
			f << rand() << std::endl;
		}
		f.close();
	}
}

void readFromRandFile(const char * fname, std::vector<int> * v) { // help here https://stackoverflow.com/questions/14516915/read-numeric-data-from-a-text-file-in-c#14517130
	cj_rand_max = 0;
	std::fstream f(fname, std::ios_base::in);
	int val;
	while(f >> val) {
		v->push_back(val);
		cj_rand_max++;
	}
	cj_rand_max--; // use as an index (0 start)
	// std::cout << (*v)[v->size()-1] << std::endl;
}

void cj_srand(int seed) {
	cj_rand_seed = seed%(cj_rand_max+1);
}

int cj_rand() {
	if(cj_rand_seed < cj_rand_max)
		cj_rand_seed++;
	else
		cj_rand_seed = 0;
	return rand_num_list[cj_rand_seed];
}