#include<iostream>
#include <iomanip>
#include<clocale>
#include<windows.h>
#include<fstream>
#include <string>
#define SIZE 30


struct my_time
{
	int hours;
	int minutes;
};
struct train
{
	int number;
	char dest[SIZE];
	my_time* time;
	train* next;
};

using namespace std;
//Функции для манипуляций с поездами
train* create();//возврат адреса корня
train* add(train* previous);//возврат адреса добавленного
train* get_info();//ввод в отдельной функции, для удобства отладки
my_time* time();//ввод времени с проверкой
int show(train* root, int number);// для выдачи информации по номеру поезда
int show(train* root, char dest[]);// для выдачи информации по станции
int show_all(train* root);// используем чтение из файла для быстрой выдачи целого списка
int write_file(train* record);

train* get_info()
{
ErrorLabel:
	train* current = new train;
	try {
		cout << "Введите номер поезда: ";
		cin >> current->number;
		cin.ignore(1000,'\n');
		cout << "Введите пункт назначения: ";
		cin >> current->dest;
		if (!cin || current->dest == '\0')
		{
			throw "Ошибка типа данных!\n";
		}
		cin.ignore(1000, '\n');
		current->time = time();
	}
	catch(const char* TypeError)
	{
		system("cls");
		cin.clear();
		cin.ignore(1000, '\n');
		cout << TypeError << endl;
		delete current;
		goto ErrorLabel;
	}
	return current;
}
my_time* time() {
	my_time* now = new my_time;
		while (true) {
			cout << "Введите время: Часы: ";
			cin >> now->hours;
			if (now->hours >= 24 || now->hours < 0 || now->hours == '\0')
			{
				cout << "Ошибка! Введите верное время!\n";
				system("pause");
				system("cls");
				cin.clear();
				cin.ignore(1000, '\n');
				continue;
			}
			cout << "Введите время: Минуты: ";
			cin >> now->minutes;
			if (now->minutes > 59 || now->minutes < 0 || now->minutes == '\0')
			{
				cout << "Ошибка! Введите верное время!\n";
				system("pause");
				system("cls");
				cin.clear();
				cin.ignore(1000, '\n');
				continue;
			}
			break;
		}
		return now;
}
	

train* create()
{
	train* first = new train;
	first = get_info();
	first->next = NULL;
	return first;
}
train* add(train* previous)
{
	train* current = new train;
	current = get_info();
	train* to_next = previous->next;// запомнили следующий элемент
	previous->next = current;//указали (предыдущий->вперед) на текущий
	current->next = to_next;//указали (текущий->вперед) на следующий (взяли выше)
	return current;
}

int show(train* root, int number)
{
	train* element = root;
	while (element->number != number)//пока не найдем
	{
		element = element->next;
		if (element==NULL)
		{
			cout << "Нет такого поезда!\n" << endl;
			return 0;
		}
	}
	cout << "Номер поезда: " << element->number << endl;
	cout << "Направление: " << element->dest << endl;
	cout << "Время отправления: " << element->time->hours << ':' << element->time->minutes << endl;
	return 0;
}

int show(train* root, char dest[])
{
	setlocale(LC_ALL, "Russian");
	train* element = root;
	bool free = true;
	while (element)//пока не NULL
	{
		if (strcmp(dest,element->dest)==0)
		{
			free = false;
			cout << "Номер поезда: " << element->number << endl;
			cout << "Направление: " << element->dest << endl;
			cout << "Время отправления: " << element->time->hours << ':' << element->time->minutes << endl;
		}
		element = element->next;	
	}	
	if (free)
	{
		cout << "Нет поездов по данному направлению\n";
	}
	return 0;
}
int show_all(train* root)
{
	train* current = new train;
	ifstream file;
	string buff;
	file.open("file.bin", ios::binary);
	if (!file.is_open())
	{
		cout << "Невозможно открыть файл!" << endl;
		return -1;
	}
	getline(file, buff);
	while(!file.eof())
	{
		getline(file,buff);
		cout << "Номер поезда: " << buff << endl;
		getline(file, buff);
		cout << "Направление: " << buff << endl;
		getline(file, buff);
		cout << "Время отправления: " << buff;
		getline(file, buff);
		cout << ':' << buff <<endl;
	}
	file.close();
	return 0;
}

int write_file(train* currrent)
{
	ofstream file;
	file.open("file.bin", ios::binary | ios::app);
	if(!file.is_open())
	{
		cout << "Невозможно открыть файл!" << endl;
		return -1;
	}
	file << endl;
	file << currrent->number<<endl;
	file << currrent->dest << endl;
	file << currrent->time->hours<<endl;
	file << currrent->time->minutes;
	file.close();
	return 0;
}


int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	train* previous = NULL;//это к add(), указатель на предыдущий элемент списка
	train* first = NULL;
	train* current = NULL; // это к add(),компилятор не дает их объявить в switch-case, потому они здесь
	bool is_first = true;//является ли первым элементом
label://метка возврата к меню
	cout << "--------------------------------------------------------------------------------" << setw(45);
	cout << "МЕНЮ ПРОГРАММЫ" << endl;
	cout << "--------------------------------------------------------------------------------";
	cout << "Выберите нужное действие:" << endl;
	cout << "Добавить поезд (a)" << endl << "Вывести список поездов (v)" << endl <<
		"Вывести информацию о поезде (i)" << endl << "Вывести информацию о поездах до станции (s)" << endl << "Выйти из программы (q)" << endl <<
		"Ответ: ";
	char command;
	cin >> command;
	cin.ignore(1000, '\n');
	system("cls");
	switch (command)
	{
	case 'a':
		system("cls");
		if (is_first) {
			first = create();
			previous = first;
			is_first = false;
		}
		else
		{
			current = add(previous);
			previous = current;
		}
		write_file(previous);
		system("cls");
		cout<<"Поезд создан!\n";
		break;
	case 'v':
		if (is_first) {
			cout << "Ни одного поезда не добавлено\n";
			break;
		}
		show_all(first);
		break;

	case 'i':
		if (is_first) {
			cout << "Ни одного поезда не добавлено\n";
			break;
		}
		int number;
		cout << "Номер поезда: ";
		cin >> number;
		if (cin.fail()) {
			cout << "Неверный тип данных!\n";
			cin.clear();
			cin.ignore(1000, '\n');
			break;
		}
		system("cls");
		show(first, number);
		break;

	case 's':
		if (is_first) {
			cout << "Ни одного поезда не добавлено\n";
			break;
		}
		cout << "Название станции: ";
		char station[SIZE];
		cin >> station;
		system("cls");
		show(first, station);
		break;
	
	case 'q':
		if (remove("file.bin") != 0)
			std::cout << "Ошибка удаления файла\n";
		return 0;
	
	default:
		cout << "Неверная операция\n";
		break;
	}
	cout << endl;
	system("pause");
	system("cls");
	goto label;
}
