#include <cstdlib> // rand
#include <iostream>
#include <fstream>
#include <vector>

void generateFile() {
	srand(48334);
	std::ofstream f;
	f.open ("vals.cjr");
	if(f.is_open()) {
		for (int i = 0; i < 1000; ++i)
		{
			// std::cout << rand() << std::endl;
			f << rand() << std::endl;
		}
		f.close();
	}
}

void readFromRandFile(const char * fname, std::vector<int> * v) { // help here https://stackoverflow.com/questions/14516915/read-numeric-data-from-a-text-file-in-c#14517130
	std::fstream f(fname, std::ios_base::in);
	int val;
	while(f >> val)
		v->push_back(val);
	// std::cout << (*v)[v->size()-1] << std::endl;
}

int main(int argc, char const *argv[])
{
	std::vector<int> v;
	generateFile();
	// readFromRandFile("vals.cjr", &v);
	return 0;
}