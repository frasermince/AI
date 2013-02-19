#include <iostream>
#include <cassert>
#include <vector>
#include <fstream>
#include "Item.h"
#include "Inventory.h"
#include "Knapsack.h"
//#include <chrono>
using namespace std;

int main(){
	int num = 30;
	vector<Item> itemList;
	Item temp();
	/*Item one(23,92);
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
	itemList.push_back(ten);*/
	fstream file;
	file.open("/Users/Fraser/Desktop/Programming/Artificial Intelligence/AI/k_basic/k30.txt", fstream::in);
	int maxWeight;
	file >> maxWeight;
	double weight;
	double value;
	for(int i = 0; i < num; i++){
		file >> weight; file >> value;
		itemList.push_back(Item(weight, value));
	}
	Knapsack a(maxWeight, itemList);
	clock_t t;
	t = clock();
	a.reversalPrune();
	cout << "reversalPrune: " << (float) clock()/CLOCKS_PER_SEC - (float)t/CLOCKS_PER_SEC << endl;

	a.print();
	cout << endl << endl;

	t = clock();
	a.bruteForce();
	cout << "BruteForce: " << (float) clock()/CLOCKS_PER_SEC - (float)t/CLOCKS_PER_SEC << endl;

	a.print();
	cout << endl << endl;

	

	/*t = clock();
	a.bruteMaxBound();
	cout << "bruteMaxBound: " << (float) clock()/CLOCKS_PER_SEC - (float)t/CLOCKS_PER_SEC << endl;

	a.print();
	cout << endl << endl;*/
	
	/*t = clock();
	a.bruteMinBound();
	cout << "bruteMinBound: " << (float) clock()/CLOCKS_PER_SEC - (float)t/CLOCKS_PER_SEC << endl;

	a.print();
	cout << endl << endl;

	t = clock();
	a.bruteDoubleBound();
	cout << "bruteDoubleBound: " << (float) clock()/CLOCKS_PER_SEC - (float)t/CLOCKS_PER_SEC << endl;

	a.print();
	cout << endl << endl;

	t = clock();
	a.bruteGreedy();
	cout << "bruteGreedy: " << (float) clock()/CLOCKS_PER_SEC - (float)t/CLOCKS_PER_SEC << endl;

	a.print();
	cout << endl << endl;

	t = clock();
	.bruteDoubleGreedy();
	cout << "bruteDoubleGreedy: " << (float) clock()/CLOCKS_PER_SEC - (float)t/CLOCKS_PER_SEC << endl;
	
	a.print();
	cout << endl << endl;*/
	//cout << endl;
	//cout << temp.getGreatest().value << endl << temp.getGreatest().weight << endl;

}