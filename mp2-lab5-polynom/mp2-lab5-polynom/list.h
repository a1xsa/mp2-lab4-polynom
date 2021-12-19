#ifndef __LIST_H__
#define __LIST_H__
template <class T>
struct Node
{
	T data;
	Node* pNext;
};
template <class T>
class TList
{
private:
	Node<T>* pfirst;
	int count;
public:
	TList();
	TList(const TList<T>& tp);
	~TList();
	TList<T> operator = (const TList<T>& tp);
	TList<T> operator + ( TList<T>& tp);
	bool Empty() const;
	void DeleteElem(int ind);
	void InsertFirst(T tp);
	void InsertLast(T tp);
	T& GetElem(int num);
	void nullcount() { count = 0; };
	int GetSize(){return count;}
};
template <class T>
TList<T>::TList()
{
	pfirst = nullptr;
	count = 0;
}
template <class T>
TList<T>::TList(const TList<T>& tp)
{
	count = 0;
	if (tp.count!=0)
	{
	Node<T>* tmp, * prev;
	prev = new Node<T>;
	prev->data = tp.pfirst->data;
	pfirst = prev;
	count++;
	tmp = tp.pfirst->pNext;
	while (tmp != nullptr)
	{
		Node<T>* new_node = new Node<T>;
		new_node->data = tmp->data;
		prev->pNext = new_node;
		prev = new_node;
		tmp = tmp->pNext;
		count++;
	}
	prev->pNext = nullptr;
	}
	else
	{
		count = 0;
		pfirst=nullptr;
	}
}
template <class T>
void TList<T>::DeleteElem(int ind)
{
	if (pfirst == nullptr)
		throw;
	if (ind == 0)
	{
		Node<T>* temp = pfirst->pNext;
		delete pfirst;
		pfirst = temp;
		count--;
	}
	else if (ind == count - 1)
	{
		int i=0;
		Node<T>* p;
		for (p = pfirst; i<count-1; p = p->pNext, i++);
		p->pNext = nullptr;
		delete p->pNext;
		count--;
	}
	else
	{
		Node<T>* p;
		Node<T>* prev = nullptr;
		int i = 0;
		for (p = pfirst; i != ind; prev = p, p = p->pNext, i++)
			;
		prev->pNext = p->pNext;
		delete p;
		count--;
	}
}
template <class T>
TList<T>::~TList()
{
	while (count != 0)
	{
		Node<T>* tmp = pfirst->pNext;
		delete pfirst;
		pfirst = tmp;
		count--;
	}
}
template <class T>
TList<T> TList<T>::operator +(TList<T>& tp)
{
	TList<T> res(*this);
	Node<T>* p;
	p = res.pfirst;
	while (p->pNext != nullptr)
		p = p->pNext;
	p->pNext = tp.pfirst; 
	res.count = res.count + tp.count;
	return res;
}
template <class T>
TList<T> TList<T>::operator =(const TList<T>& tp)
{
	if (this == &tp)
		return (*this);
	while (count > 0)
	{
		Node<T>* tmp = pfirst->pNext;
		delete pfirst;
		pfirst = tmp;
		count--;
	}
	if (tp.count != 0)
	{
		Node<T>* tmp, * prev;
		prev = new Node<T>;

		prev->data = tp.pfirst->data;
		pfirst = prev;
		count++;
		tmp = tp.pfirst->pNext;
		while (tmp != nullptr)
		{
			Node<T>* new_node = new Node<T>;
			new_node->data = tmp->data;
			prev->pNext = new_node;
			prev = new_node;
			tmp = tmp->pNext;
			count++;
		}
		prev->pNext = nullptr;
	}
	else
	{
		count = 0;
		pfirst = nullptr;
	}
	return (*this);
}
template <class T>
bool TList<T>::Empty() const
{
	if (count == 0)
		return 1;
	return 0;
}
template <class T>
void TList<T>::InsertFirst(T tp)
{
	Node<T>* pNode=new Node<T>;
	pNode->data = tp;
	pNode->pNext = pfirst;
	pfirst = pNode;
	count++;
}
template <class T>
void TList<T>::InsertLast(T tp)
{
	Node<T>* p;
	Node<T>* pNode = new Node<T>;
	pNode->data = tp;
	if (count==0)
	{
		pNode->pNext = pfirst;
		pfirst = pNode;
		count++;
		return;
	}
	p = pfirst;
	while (p->pNext != nullptr)
		p = p->pNext;
		p->pNext = pNode;
		pNode->pNext = nullptr;
	count++;
}
template <class T>
T& TList<T>::GetElem(int num)
{
	if (num > count)
		throw;
	Node<T>* pNode = new Node<T>;
	Node<T>* t;
	t = pfirst;
	for (int i = 1; i <= num; i++)
	{
		t = t->pNext;
	}
	pNode = t;
	return pNode->data;
}
#endif