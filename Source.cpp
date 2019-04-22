#include<iostream>
#include <windows.h>
#define SIZE 100
struct stack
{
	char symbol;
	stack* next;
};
void push(stack** top,char symbol, bool* first)// двойной указатель, чтобы изменить указатель 
{
	stack* current = new stack;
	current->symbol = symbol;
	if(*first)
	{
		current->next = NULL;//дно стека
		*top = current;
		*first = false;
	}
	else {
		current->next = *top;
		*top = current;
	}
}
void pop(stack** top)
{
	std::cout << (*top)->symbol;
	*top = (*top)->next;
}
using namespace std;
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	bool first = true;
	stack* example = NULL;
	stack** top = &example;//верхний элемент указывает на NULL: больше элементов нет
	setlocale(LC_ALL, "Russian");
	char sentance[SIZE];
	cout << "¬ведите предложение: ";
	cin.getline(sentance,SIZE);
	const char* psent = sentance;
	while(*(psent-1))//из-за инкремента, указатель стоит на следующем за '\0' элементе
	{	
		while (*psent != ' '&&  *psent)
		{
			push(top, *psent, &first);
			psent++;
		}
		while(*top)
		{
			pop(top);
		}
		first = true;
		psent++;//инкремент, чтобы перейти на новый символ после ' '
		cout << ' ';
	}
	cout << endl;
	system("pause");
	return 0;	
}