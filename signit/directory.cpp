#include "directory.h"

// Конструктор директории
Directory::Directory(Config *config) {
	config_ = config;
}

// Загрузка файлов директории (и поиск подходящих)
void Directory::load() {
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
}

// Работа над файлами
void Directory::operation() {
	// Перебор всех файлов
	for each (auto path in filesPaths)
	{
		std::fstream fs;
		std::string filetext = "";
		// Читаем
		fs.open(path, std::fstream::in);
		char c;
		while (fs.get(c))
			filetext += c;
		fs.close();

		// Проводим операции
		addSign(filetext);

		// Сохраняем
		fs.open(path, std::fstream::out);
		fs.write(filetext.c_str(), filetext.length());
	}
}

// Добавление подписи
void Directory::addSign(std::string &filetext) {
	std::string startSign = "/*\n";
	std::string textSign = "* Program\n* @author 2018\n";
	std::string endSign = "*/\n\n";
	int startPos = -1;
	int endPos = -1;
	int buffer = 0;

	// Поиск совпадения с началом
	for (size_t i = 0; i < startSign.length(); i++)
	{
		if (filetext[i] == startSign[i])
			buffer++;
	}
	if (buffer == startSign.length())
		startPos = 0;

	buffer = 0;
	// Поиск совпадения с концом
	for (size_t i = 0; i < filetext.length(); i++)
	{
		if (filetext[i] == endSign[buffer])
			buffer++;
		else
			buffer = 0;
		if (startSign.length() == buffer) {
			endPos = i;
			buffer = 0;
		}
	}

	if (startPos != -1 && endPos != -1) {
		// Заменяем подпись
		filetext.replace(startPos, endPos + 2, startSign + textSign + endSign);
	} else {
		// Добавление подписи к файлу, у которого не было подписи
		filetext.insert(0, startSign + textSign + endSign);
	}
}