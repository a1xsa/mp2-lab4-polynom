#include <iostream>
#include "Polynom.h"
#include "list.h"
#include <string>
#include <fstream>

using namespace std;
void ReadFile(TList<TPolynom>& array)
{
	string line;
	ifstream in("C:\\off\\mp2-lab5-polynom\\mp2-lab5-polynom\\Polynom.txt");
	if (in.is_open())
	{
		TPolynom v;
		while (getline(in, line))
		{
			cout << line << endl;
			v.SetList(line);
			v.sort();
			v.similarity();
			v.toString();
			array.InsertLast(v);
			
		}
		in.close();
	}
}
void RecordFile(TList<TPolynom>& array)
{
	ofstream out("C:\\off\\mp2-lab5-polynom\\mp2-lab5-polynom\\Polynom.txt");
	for (int i = 0; i < array.GetSize(); i++)
	{
		out<<array.GetElem(i).GetString();
		out << endl;
	}
}
int menu()
{
	int k;
	cout << "Выберите дейтсвие:" << endl;
	cout << "1. Добавить новый полином." << endl;
	cout << "2. Удалить полином по индексу. " << endl;
	cout << "3. Список полиномов на данный момент." << endl;
	cout << "4. Получить полиномы из файла." << endl;
	cout << "5. Сохранить полиномы в файл." << endl;
	cout << "6. Сумма полиномов." << endl;
	cout << "7. Произведение полиномов." << endl;
	cout << "8. Расчет в точке." << endl;
	cout << "0. Выйти из программы." << endl;
	cin >> k;
	return k;
}
void main()
{
	setlocale(LC_ALL, "Russian");
	TList <TPolynom> array;
	string t;
	double res;
	TPolynom v;
	int n;
	int x1, x2;
l:	switch (menu())
	{
	case 1:
		cin >> t;
		v.SetList(t);
		v.sort();
		v.similarity();
		v.toString();
		array.InsertLast(v);
		break;
	case 2:
		if (array.Empty())
		{
			cout << "Список полиномов пуст" << endl;
			break;
		}
		cout << "Введите номер полинома для удаления" << endl;
		for (int i = 0; i < array.GetSize(); i++)
		{
			cout << i + 1 << ".";
			cout<<array.GetElem(i).GetString();
			cout << endl;
		}
		cin >> n;
		array.DeleteElem(n-1);
		break;
	case 3:
		if (array.Empty())
			cout << "Список полиномов пуст" << endl;
		for (int i = 0; i < array.GetSize(); i++)
		{
			cout << i + 1 << ".";
			cout << array.GetElem(i).GetString();
			cout << endl;
		}
		break;
	case 4:
		ReadFile(array);
		break;
	case 5:
		RecordFile(array);
		break;
	case 6:
		if (array.Empty())
		{
			cout << "Список полиномов пуст" << endl;
			break;
		}
		for (int i = 0; i < array.GetSize(); i++)
		{
			cout << i +1 << ".";
			cout << array.GetElem(i).GetString();
			cout << endl;
		}
		cout << "Введите номера полиномов" << endl;
		cin >> x1;
		cin >> x2;
		v=array.GetElem(x1-1) + array.GetElem(x2-1);
		cout << "Результат:" << endl;
		v.toString();
		cout << v.GetString();
		cout << endl;
		break;
	case 7:
		if (array.Empty())
		{
			cout << "Список полиномов пуст" << endl;
			break;
		}
		for (int i = 0; i < array.GetSize(); i++)
		{
			cout << i + 1 << ".";
			cout << array.GetElem(i).GetString();
			cout << endl;
		}
		cout << "Введите номера полиномов" << endl;
		cin >> x1;
		cin >> x2;
		v = array.GetElem(x1 - 1) * array.GetElem(x2 - 1);
		cout << "Результат:" << endl;
		v.toString();
		cout << v.GetString();
		cout << endl;
		break;
	case 8:
		if (array.Empty())
		{
			cout << "Список полиномов пуст" << endl;
			break;
		}
		for (int i = 0; i < array.GetSize(); i++)
		{
			cout << i + 1 << ".";
			cout << array.GetElem(i).GetString();
			cout << endl;
		}
		cout << "Введите номер полиномa" << endl;
		cin >> x1;
		double x, y, z;
		cout << "Введите параметры x, y, z:" << endl;
		cin >> x;
		cin >>y;
		cin >> z;
		cout << "Результат равен:" << endl;
		cout<<array.GetElem(x1 - 1).meaning(x, y, z);
		cout << endl;
		break;
	case 0:
		return;
	}
	goto l;
}