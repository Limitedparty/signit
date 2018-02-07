#include "directory.h"

// Конструктор директории
Directory::Directory(Config *config) {
	config_ = config;
}

// Загрузка файлов директории (и поиск подходящих)
void Directory::load() {
	std::cout << "\nSearching files...\n";
	std::regex fileRegex(config_->getRegexSearch());
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
	std::string startSign = config_->getSign().start;
	std::string textSign = config_->getSign().text;
	std::string endSign = config_->getSign().end;
	std::string sign = startSign + textSign + endSign;
	int endSpaces = config_->getSign().spaces;
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
		if (endSign.length() == buffer) {
			endPos = i;
			buffer = 0;
		}
	}

	if (startPos != -1 && endPos != -1) {
		// Заменяем подпись
		filetext.replace(startPos, endPos + 1, sign);
	} else {
		// Добавление подписи к файлу, у которого не было подписи
		filetext.insert(0, sign);
	}
	endPos = sign.length() - 1;

	// Проверка количества пробелов после подписи
	for (size_t i = 0; i < endSpaces; i++)
	{
		if ((endPos + i + 1) < filetext.length() && filetext[endPos + i + 1] != '\n')
			filetext.insert(endPos + i + 1, 1, '\n');
	}
}