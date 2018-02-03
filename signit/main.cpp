#include "config.h"
#include "directory.h"

Config config;
Directory *directory;

int init() {
	if (!config.setup()) {
		std::cout << "Error configuration setup.\n";
		return 1;
	}
	directory = new Directory(&config);
	directory->load();
	directory->operation();
}

int main() {
	init();
	system("pause");
}