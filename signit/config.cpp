#include "config.h"

// Конструктор конфига
Config::Config() {
	configFile_ = "signitconfig";
}

// Подготовка конфига
bool Config::setup() {
	// Пробуем прочитать конфиг
	if (!read()) {
		// Не получилось? Создадим его
		if (create()) {
			// Пробуем прочитать его еще раз
			if (!read()) return false;
		} else return false;
	}

	return true;
}

// Чтение конфига
bool Config::read() {
	std::ifstream readFile;
	readFile.open(configFile_);

	// Если не удалось открыть файл
	if (!readFile.is_open()) {
		std::cout << "Error. File '" << configFile_ << "' not found\n";
		return false;
	}

	std::string line;
	while (std::getline(readFile, line)) {
		std::string key, value;
		// Игнорируем комментарии
		if (line[0] != '#') {
			bool splited = false;
			for (size_t i = 0; i < line.size(); i++) {
				if (splited) value += line[i];
				if (line[i] == '=') splited = true;
				if (!splited) key += line[i];
			}
			keyset(key, value);
		}
	}

	return true;
}
// Создание конфига
bool Config::create() {
	std::cout << "Creating config file...\n";
	std::ofstream writeFile;
	writeFile.open(configFile_);

	// Если не удалось открыть файл (т.е. создать)
	if (!writeFile.is_open()) {
		std::cout << "Error. Can't create configuration file\n";
		return false;
	}

	// Записываем в файл стандартную чушь
	writeFile << "# Signit configuration file" << std::endl;
	writeFile << "workPath=./" << std::endl;
	writeFile << "regexSearch=\\.txt|\\.cfg" << std::endl;
	writeFile << "# Sign settings (start and end without \\n)" << std::endl;
	writeFile << "signStart=/*" << std::endl;
	writeFile << "signText=\\n* Program\\n* @author\\n" << std::endl;
	writeFile << "signEnd=*/" << std::endl;
	writeFile << "signEndSpaces=2" << std::endl;

	return true;
}

// Интерпретация значений конфиг файла
bool Config::keyset(std::string key, std::string value) {
	// Путь до рабочей папки
	if (key == "workPath") {
		// Проверяем существование папки
		if (fs::exists(value)) {
			workPath_ = value;
			std::cout << "Set workPath=" << value << "\n";
			return true;
		} else {
			std::cout << "Error! workPath=" << value << " doesn't exists\n";
			return false;
		}
	}

	// Регулярные выражения
	if (key == "regexSearch") {
		std::cout << "Set regexSearch=" << value << "\n";
		regexSearch_ = value;
	}

	// Начало подписи
	if (key == "signStart") {
		sign_.start = value;
	}

	// Текст подписи
	if (key == "signText") {
		// Замена \n на нормальный конец строки
		char last = ' ';
		for (size_t i = 0; i < value.length(); i++)
		{
			if (last == '\\' && value[i] == 'n') {
				value.replace(i-1, 2, "\n");
			}
			last = value[i];
		}
		sign_.text = value;
		std::cout << "Set signText=" << value << "\n";
	}

	// Конец подписи
	if (key == "signEnd") {
		sign_.end = value;
	}

	// Количество пробелов после подписи
	if (key == "signEndSpaces") {
		sign_.spaces = atoi(value.c_str());
	}

	return true;
}