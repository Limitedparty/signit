#include "directory.h"

// Конструктор директории
Directory::Directory(Config *config) {
	config_ = config;
}

// Загрузка файлов директории (и поиск подходящих)
bool Directory::load() {
	std::cout << "\nSearching files...\n";
	std::regex fileRegex("\.txt|\.cfg");
	// Перебор файлов в папке
	for (auto &p : fs::recursive_directory_iterator(config_->getWorkPath())) {
		std::string path = p.path().string();
		if (std::regex_search(path, fileRegex)) {
			// ...и запихивание подходящих в массив
			filesPaths.push_back(path);
			std::cout << p << '\n';
		}
	}
	return false;
}