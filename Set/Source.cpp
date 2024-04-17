#include "Set.h"
#include "Octal.h"
#include <Windows.h>
#include <string>
#include <fstream>

bool get_integer(int& x, int A = 0, int B = 0)
{
	std::cin >> x;
	bool result = false;
	if (std::cin.good() && (A == B || !(x < A) && !(B < x)))
		result = true;
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	return result;
}

template <class key>
bool get_key(key& x)
{
	std::cin >> x;
	bool result = false;
	if (std::cin.good())
		result = true;
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	return result;
}

int get_filename(std::string& filename)
{
	int result = -1;
	std::getline(std::cin, filename);
	if (filename.find_first_of("<>:\"/\\|?*") == std::string::npos)
	{
		std::ifstream file(filename);
		result = (file.good() ? 1 : 0);
		file.close();
	}
	return result;
}

template <class key>
Set<key>* init(std::string class_name, std::string name)
{
	system("cls");
	std::cout << "Инициализировать Set<" << class_name << "> " << name << " из файла?\n1. Да\n0. Нет\n->";
	int choice = -1;
	while (!get_integer(choice, 0, 1))
		std::cout << "Ошибка ввода!\n->";

	Set<key>* result;
	if (choice)
	{
		std::string filename;
		std::cout << "Введите имя файла (c расширением):\n->";
		while (get_filename(filename) != 1)
			std::cout << "Не удалось открыть файл " << filename << "!\n->";
		std::ifstream file(filename);
		result = new Set<key>(file);
		file.close();
	}
	else
		result = new Set<key>;

	return result;
}

template <class key>
void submenu(std::string class_name)
{
	Set<key>* a = init<key>(class_name, "a"), * b = init<key>(class_name, "b");

	system("cls");
	int choice = -1;
	while (choice != 0)
	{
		std::cout << "a = {" << *a << "}\n";
		std::cout << "b = {" << *b << "}\n";
		std::cout << "1. Добавить элемент во множество\n";
		std::cout << "2. Удалить элемент из множества\n";
		std::cout << "3. Найти элемент во множестве\n";
		std::cout << "4. Вывести множество в файл\n";
		std::cout << "5. Найти объединение множеств\n";
		std::cout << "6. Найти пересечение множеств\n";
		std::cout << "7. Найти разность множеств\n";
		std::cout << "0. Выйти в главное меню\n->";
		while (!get_integer(choice, 0, 7))
			std::cout << "Ошибка ввода!\n->";

		int subchoice = -1;
		key tmp{};
		std::string filename;

		if (choice >= 1 && choice <= 4)
		{
			std::cout << "1. a\n2. b\n->";
			while (!get_integer(subchoice, 1, 2))
				std::cout << "Ошибка ввода!\n->";

			if (choice == 4)
			{
				std::cout << "Введите имя файла (c расширением):\n->";
				while (get_filename(filename) != 0)
					std::cout << "Не удалось создать файл " << filename << "!\n->";
			}
			else
			{
				std::cout << "Введите элемент\n->";
				while (!get_key(tmp))
					std::cout << "Ошибка ввода!\n->";
			}
		}
		else if (choice == 7)
		{
			std::cout << "1. a - b\n2. b - a\n->";
			while (!get_integer(subchoice, 1, 2))
				std::cout << "Ошибка ввода!\n->";
		}

		if (choice)
			system("cls");
		switch (choice)
		{
		case 1:
			if (subchoice == 1)
				std::cout << "Элемент " << tmp << (a->insert(tmp) ? " добавлен во множество a\n" : " не добавлен во множество a\n");
			else
				std::cout << "Элемент " << tmp << (b->insert(tmp) ? " добавлен во множество b\n" : " не добавлен во множество b\n");
			break;
		case 2:
			if (subchoice == 1)
				std::cout << "Элемент " << tmp << (a->erase(tmp) ? " удален из множества a\n" : " не удален из множества a\n");
			else
				std::cout << "Элемент " << tmp << (b->erase(tmp) ? " удален из множества b\n" : " не удален из множества b\n");
			break;
		case 3:
			if (subchoice == 1)
				std::cout << "Элемент " << tmp << (a->find(tmp) ? " найден во множестве a\n" : " не найден во множестве a\n");
			else
				std::cout << "Элемент " << tmp << (b->find(tmp) ? " найден во множестве b\n" : " не найден во множестве b\n");
			break;
		case 4:
		{
			std::ofstream file(filename);
			if (subchoice == 1)
				file << *a;
			else
				file << *b;
			file.close();
		}
		break;
		case 5:
			std::cout << "a + b = {" << *a + *b << "}\n";
			break;
		case 6:
			std::cout << "a * b = {" << *a * *b << "}\n";
			break;
		case 7:
			if (subchoice == 1)
				std::cout << "a - b = {" << *a - *b << "}\n";
			else
				std::cout << "b - a = {" << *b - *a << "}\n";
			break;
		case 0:
			delete a;
			delete b;
			break;
		}
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int choice = -1;
	while (choice != 0)
	{
		system("cls");
		std::cout << "1. Set<int>\n2. Set<string>\n3. Set<Octal>\n0. Выход\n->";
		while (!get_integer(choice, 0, 3))
			std::cout << "Ошибка ввода!\n->";

		switch (choice)
		{
		case 1:
			submenu<int>("int");
			break;
		case 2:
			submenu<std::string>("string");
			break;
		case 3:
			submenu<Octal>("Octal");
			break;
		}
	}
	return 0;
}