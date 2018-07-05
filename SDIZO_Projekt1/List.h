#pragma once
class List
{
	class ListElem{
		
		int var;
		struct ListElem *next;
		struct ListElem *prev;
		friend class List;

		public:
		ListElem() {
			next = NULL;
			prev = NULL;
		}
		~ListElem() {
			delete next;
			delete prev;
		}
	};		

	ListElem *first;
	ListElem *last;
	int size;

public:
	List();
	~List();
	int Menu();
	int LoadFromFile(std::string filename);
	int AddElementZero(int v);
	int AddElementFirst(int v);
	int AddElementLast(int v);
	int AddElement(int v, int position);
	int DeleteList();
	int DeleteElementFirst();
	int DeleteElementLast();
	int DeleteElement(int position);
	int FindElementFound(int v);
	int ShowList(int n);
	int FindElement(int v);
};

