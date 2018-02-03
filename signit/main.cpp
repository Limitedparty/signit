#include "config.h"

Config config;

int init() {
	if (!config.setup()) {
		std::cout << "Error configuration setup.\n";
		return 1;
	}
}

int main() {
	init();
	system("pause");
}