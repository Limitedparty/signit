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

	return true;
}

// Интерпретация значений конфиг файла
bool Config::keyset(std::string key, std::string value) {
	// Путь до рабочей папки
	if (key == "workPath") {
		// Проверяем существование папки
		if (fs::exists(value)) {
			workPath_ == value;
			std::cout << "Set workPath=" << value << "\n";
			return true;
		} else {
			std::cout << "Error! workPath=" << value << " doesn't exists\n";
			return false;
		}
	}
	return true;
}