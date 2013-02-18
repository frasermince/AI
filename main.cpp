#include <iostream>
#include <cassert>
#include <vector>
#include "Item.h"
#include "Inventory.h"
#include "Knapsack.h"
using namespace std;

int main(){
	vector<Item> itemList;
	Item one(23,92);
	Item two(31,57);
	Item three(29,49);
	Item four(44,68);
	Item five(53,60);
	Item six(38,43);
	Item seven(63,67);
	Item eight(85,84);
	Item nine(89,87);
	Item ten(82,72);
	itemList.push_back(one);
	itemList.push_back(two);
	itemList.push_back(three);
	itemList.push_back(four);
	itemList.push_back(five);
	itemList.push_back(six);
	itemList.push_back(seven);
	itemList.push_back(eight);
	itemList.push_back(nine);
	itemList.push_back(ten);
	Knapsack a(165, itemList);
	a.bruteForce();
	a.print();
	//cout << temp.getGreatest().value << endl << temp.getGreatest().weight << endl;

}