#ifndef __POLYNOM_H__
#define __POLYNOM_H__
#include "list.h"
#include <iostream>
using namespace std;

struct Monom
{
	double coef;
	int degree;
};

class TPolynom
{
	TList <Monom> tp;
	string polynom;
public:
	TPolynom() {};
	void SetList(string t);
	void GetList();
	TPolynom operator +(TPolynom& tp);
	TPolynom operator *(TPolynom& tp);
	double meaning(double x, double y, double z);
	void sort();
	void similarity();
	void toString();
	string GetString();
};
#endif