#include<iostream>
#include <iomanip>
#include<clocale>
#include<windows.h>
#define SIZE 10

struct my_time
{
	int hours;
	int minutes;
};
struct train
{
	int number;
	char dest[SIZE];
	my_time time;
	train* next;
	train* prev;
};

using namespace std;
//Функции для манипуляций с поездами
train* create();//возврат адреса корня
train* add(train* previous);//возврат адреса добавленного
train* get_info();//ввод в отдельной функции, для удобства отладки
int show(train* root, int number);// для выдачи информации по номеру поезда
int show(train* root, char dest[]);// для выдачи информации по станции
int show_all(train* root);

train* get_info()
{
	train* current = new train;
	cout << "Введите номер поезда: ";
	cin >> current->number;
	cout << "Введите пункт назначения: ";
	cin >> current->dest;
	cout << "Введите время; Часы: ";
	cin >> current->time.hours;
	cout << "Введите время; Минуты: ";
	cin >> current->time.minutes;
	return current;
}

train* create()
{
	train* first = new train;
	first = get_info();
	first->prev = NULL;
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
	current->prev = previous;//указали (текущий->назад) на предыдущий
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
	cout << "Время отправления: " << element->time.hours << ':' << element->time.minutes << endl;
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
			cout << "Время отправления: " << element->time.hours << ':' << element->time.minutes << endl;
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
	train* current = root;
	while(current)
	{
		cout << "Номер поезда: " << current->number << endl;
		cout << "Направление: " << current->dest << endl;
		cout << "Время отправления: " << current->time.hours << ':' << current->time.minutes << endl;
		current = current->next;
	}
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
	switch (command)
	{
	case 'a':
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
		if (!current ||!previous)
		{
			goto label;
		}
		break;
	case 'v':
		if (is_first) {
			cout << "Ни одного поезда не добавлено\n";
			break;
		}
		show_all(first);
		break;

	case 'i':
		cout << "Номер поезда: ";
		int number;
		cin >> number;
		show(first, number);
		break;

	case 's':
		cout << "Название станции: ";
		char station[SIZE];
		cin >> station;
		show(first, station);
		break;
	
	case 'q':
	return 0;
	
	default:
		cout << "Неверная операция\n";
		break;
	}
	goto label;
}
