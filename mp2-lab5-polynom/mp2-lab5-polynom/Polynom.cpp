#include "list.h"
#include "Polynom.h"
#include <iostream>
#include <cmath>
#include <sstream>
void TPolynom::SetList(string t)
{
	this->tp.~TList();
	Monom tmp;
	tmp.degree = 0;
	string tpk;
	double coef;
	int i=0, start=-1;
	polynom = t;
	while (i <= t.size())
	{
		if ((t[i] == '+')||(t[i] == '-')||(i==0)||(t[i]=='\0'))
		{
			if (i != 0)
			{
				tp.InsertLast(tmp);
				tmp.degree = 0;
			}
			if ((t[i] == 'x') || (t[i] == 'y') || (t[i] == 'z'))
			{
				tmp.coef = 1;
				goto l;
			}
			else
			{
				start = i;
				i++;
			}
		}
		else
		{
			if ((t[i] == 'x') || (t[i] == 'y') || (t[i] == 'z'))
			{
				if ((i - start > 1)||((i==1)&&(t[start]!='-')))
				{
					tpk = t.substr(start, i - start);
					coef = atof(tpk.c_str());
					tmp.coef = coef;
					start = -1;
				}
				else
				{
					if (t[start] =='+')
						tmp.coef = 1;
					else
						tmp.coef = -1;
					start = -1;
				}
				l:if (t[i] == 'x')
				{
					i++; 
					if ((t[i] >= 48) && (t[i] <= 57))
					{
						tmp.degree = 100 * (t[i] - 48);
						i++;
						if ((t[i] >= 48) && (t[i] <= 57))
							throw;
					}
					else tmp.degree = 100;
				}
				if (t[i] == 'y')
				{
					i++;
					if ((t[i] >= 48) && (t[i] <= 57))
					{
						tmp.degree = tmp.degree + 10 * (t[i] - 48);
						i++;
						if ((t[i] >= 48) && (t[i] <= 57))
							throw;
					}
					else tmp.degree = tmp.degree + 10;
				}
				if (t[i] == 'z')
				{
					i++;
					if ((t[i] >= 48) && (t[i] <= 57))
					{
						tmp.degree = tmp.degree + (t[i] - 48);
						i++;
						if ((t[i] >= 48) && (t[i] <= 57))
							throw;
					}
					else tmp.degree = tmp.degree + 1;
				}
			}
			else i++;
		}
	}
}
void TPolynom::GetList()
{
	Monom t;
	for (int i = 0; i < tp.GetSize(); i++)
	{
		t = tp.GetElem(i);
		cout << "Степень  " << t.degree << endl;
		cout << "Коэф  " << t.coef << endl;
	}
}
void TPolynom::sort()
{
	TList <Monom> tpe(tp);
	TList <Monom> res;
	if (tp.Empty()) 
	{
		throw;
	}
	Monom max;
	int ind;
	while (tpe.GetSize() != 1)
	{
		max = tpe.GetElem(0);
		ind = 0;
		for (int i = 1; i < tpe.GetSize(); i++)
		{
			if (tpe.GetElem(i).degree > max.degree)
			{
				max = tpe.GetElem(i);
				ind = i;
			}
		}
		res.InsertLast(max);
		tpe.DeleteElem(ind);
	}
	res.InsertLast(tpe.GetElem(0));
	tp = res;
}
void TPolynom::similarity()
{
	int i,j;
	for ( i = 0; i < tp.GetSize(); i++)
	{
		Monom& m1 = tp.GetElem(i);
		for (size_t j = i + 1; j < tp.GetSize(); j++)
		{
			Monom& m2 = tp.GetElem(j);
			if (m1.degree == m2.degree)
			{
				m1.coef = m1.coef + m2.coef;
				tp.DeleteElem(j);
			}
		}
	}
	for (i = 0; i < tp.GetSize(); i++)
	{
		if (tp.GetElem(i).coef == 0)
		{
			tp.DeleteElem(i);
			i = i - 1;
		}
	}
}
TPolynom TPolynom:: operator +(TPolynom& tmp)
{
	TPolynom res;
	TPolynom k;
	k = tmp;
	res.tp = tp + k.tp;
	res.sort();
	res.similarity();
	k.tp.nullcount();
	return res;
}
TPolynom TPolynom:: operator *(TPolynom& tmp)
{
	TPolynom res;
	Monom tres;
	Monom x1, x2;
	int i,j;
	int resdeg=0, tmpdeg=0;
	for (i = 0; i < tp.GetSize(); i++)
	{
		x1 = tp.GetElem(i);
		for (j = 0; j < tmp.tp.GetSize(); j++)
		{
			x2 = tmp.tp.GetElem(j);
			tres.coef = x1.coef * x2.coef;
			tmpdeg = (x1.degree / 100) + (x2.degree / 100);
			if (tmpdeg >= 10)
				throw;
			resdeg = tmpdeg * 100;
			tmpdeg = ((x1.degree % 100)/10) + ((x2.degree % 100)/10);
			if (tmpdeg >= 10)
				throw;
			resdeg = resdeg + tmpdeg * 10;
			tmpdeg = (x1.degree % 10) + (x2.degree % 10);
			if (tmpdeg >= 10)
				throw;
			resdeg = resdeg + tmpdeg;
			tres.degree = resdeg;
			res.tp.InsertLast(tres);
		}
	}
	res.sort();
	res.similarity();
	return res;
}
double TPolynom::meaning(double x, double y, double z)
{
	double res=0;
	int i;
	Monom tmp;
	for (i = 0; i < tp.GetSize(); i++)
	{
		tmp = tp.GetElem(i);
		res = res + tmp.coef * pow(x, tmp.degree / 100) * pow(y, (tmp.degree % 100) / 10) * pow(z, tmp.degree % 10);
	}
	return res;
}
void TPolynom::toString()
{
	int i;
	Monom tmp;
	string p;
	for (i = 0; i < tp.GetSize(); i++)
	{
		tmp = tp.GetElem(i);
		ostringstream ostr; 
		ostr << tmp.coef; 
		p += ostr.str();
		if ((tmp.degree / 100) != 0)
		{
			p += "x";
			p += (tmp.degree / 100) + 48;
		}
		if (((tmp.degree % 100)/10) != 0)
		{
			p += "y";
			p += ((tmp.degree % 100)/10) + 48;
		}
		if ((tmp.degree % 10) != 0)
		{
			p += "z";
			p += (tmp.degree %10) + 48;
		}
		if (i!= tp.GetSize()-1)
		p += "+";
	}
	polynom = p;
}
string TPolynom::GetString()
{
	return polynom;
}

