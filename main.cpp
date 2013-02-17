#include <iostream>
#include <cassert>
#include <vector>
#include "Item.h"
#include "Inventory.h"
#include "Knapsack.h"
using namespace std;

int main(){
	vector<Item> itemList;
	Item one(20,5);
	Item two(8,15);
	Item three(20,30);
	Item four(35,16);
	Item five(80,45);
	Inventory temp(30);
	itemList.push_back(one);
	itemList.push_back(two);
	itemList.push_back(three);
	itemList.push_back(four);
	itemList.push_back(five);
	Knapsack a(30, itemList);
	a.bruteForce();
	//cout << temp.getGreatest().value << endl << temp.getGreatest().weight << endl;

}