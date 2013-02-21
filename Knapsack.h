#include <iostream>
#include <cassert>
#include <vector>
#include <bitset>
using namespace std;


class Knapsack{
public:
	Knapsack(int w, vector<Item> list)	: greatest(w,list.size())		{itemList = list; greedyVal = 0; n = 0;}
	void bruteForce();
	Inventory bruteForce(Inventory& possibility);

	void reversalPrune();
	Inventory reversalPrune(Inventory& possibility);

	void bruteMaxBound();
	Inventory bruteMaxBound(Inventory& possibility);

	void bruteMinBound();
	Inventory bruteMinBound(Inventory& possibility);

	void bruteDoubleBound();
	Inventory bruteDoubleBound(Inventory& possibility);

	void bruteGreedy();
	Inventory bruteGreedy(Inventory& possibility);

	void bruteDoubleGreedy();
	Inventory bruteDoubleGreedy(Inventory& possibility);

	void prepare();

	Inventory greedy();
	void print()											{cout << n << endl; greatest.print(itemList);}

private:
	long long n;
	Inventory greatest;
	double greedyVal;
	vector<Item> itemList;
};