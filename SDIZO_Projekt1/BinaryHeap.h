#pragma once
class BinaryHeap
{
	int *heap;
	int size;

public:
	BinaryHeap();
	~BinaryHeap();
	int Menu();
	int SortUp(int index);
	int SortDown(int index);
	int AddElement(int var);
	int DeleteHeap();
	int DeleteElementMax();
	int DeleteElementMin();
	int DeleteElement(int element);
	int DeleteElementIndex(int index);
	int LoadFromFile(std::string filename);
	int CompareElements(int index, int element);
	int FindElement(int element);
	void gotoxy(int x, int y);
	void ShowHeap();
	void Swap(int & p1, int & p2);
};

