#include <iostream>
#include <cassert>
#include <vector>
#include <bitset>


class Knapsack{
public:
	Knapsack(int w, vector<Item> list)	: greatest(w)		{itemList = list;}
	void bruteForce();
	Inventory bruteForce(Inventory possibility);
	Inventory bruteMaxBound(Inventory possibility);
	Inventory bruteMinBound(Inventory possibility);
	Inventory bruteDoubleBound(Inventory possibility);
	Inventory greedy();
	Inventory dynamic();

private:
	Inventory greatest;
	vector<Item> itemList;
};