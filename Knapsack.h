#include <iostream>
#include <cassert>
#include <vector>
#include <bitset>


class Knapsack{
public:
	Knapsack(int w, vector<Item> list)	: greatest(w)		{itemList = list;}
	void bruteForce();
	Inventory bruteForce(Inventory& possibility);
	void bruteMaxBound();
	Inventory bruteMaxBound(Inventory& possibility);
	void bruteMinBound();
	Inventory bruteMinBound(Inventory& possibility);
	void bruteDoubleBound();
	Inventory bruteDoubleBound(Inventory& possibility);
	Inventory greedy();
	void print()											{greatest.print(itemList);}

private:
	Inventory greatest;
	vector<Item> itemList;
};