#include "Item.h"
#include "Inventory.h"
#include "Knapsack.h"
#include <ctime>
#include <algorithm>
#include <cassert>
using namespace std;


void Knapsack::bruteForce(){
	greatest.reset();
	greatest = bruteForce(greatest);
}

Inventory Knapsack::bruteForce(Inventory& possibility){
	Inventory copy = possibility;
	//cout << "check" << endl;
	if (possibility.getLength() == itemList.size()){
		//cout << "base "; 
		//possibility.print(itemList); 
		//cout << endl;
		return possibility;
	}

	
	//possibility.print(itemList);
	possibility.push(true, itemList);
	possibility = bruteForce(possibility);
	copy.push(false, itemList);
	copy = bruteForce(copy);
	//cout << "compare" << copy.getGreatest().value << " and " << possibility.getGreatest().value << endl;

	if (copy.getGreatest().getValue() >= possibility.getGreatest().getValue()){
		//copy.print(itemList);
		return copy;
	}
	else{
		//possibility.print(itemList);
		return possibility;
	}
}

void Knapsack::bruteMaxBound(){
	greatest.reset();
	greatest = bruteMaxBound(greatest);
}

Inventory Knapsack::bruteMaxBound(Inventory& possibility){
	Inventory copy = possibility;
	//cout << "check" << endl;
	if (possibility.getLength() == itemList.size()){
		return possibility;
	}

	
	//possibility.print(itemList);
	if(possibility.push(true, itemList) == true)
		possibility = bruteForce(possibility);
	if(copy.push(false, itemList) == true)
		copy = bruteForce(copy);
	//cout << "compare" << copy.getGreatest().value << " and " << possibility.getGreatest().value << endl;
	if (copy.getGreatest().getValue() >= possibility.getGreatest().getValue()){
		return copy;
	}
	else
		return possibility;
}

void Knapsack::bruteMinBound(){
	greatest.reset();
	greatest = bruteMinBound(greatest);
}

Inventory Knapsack::bruteMinBound(Inventory& possibility){
	Inventory copy = possibility;
	//cout << "check" << endl;
	if (possibility.getLength() == itemList.size()){
		if(possibility.getGreatest() < greatest.getGreatest()){
			possibility.setLow();
		}
		return possibility;
	}

	
	//possibility.print(itemList);
	possibility.push(true, itemList) == true;
	possibility = bruteForce(possibility);
	copy.push(false, itemList) == true;
	copy = bruteForce(copy);
	//cout << "compare" << copy.getGreatest().value << " and " << possibility.getGreatest().value << endl;
	if (!copy.isLow() && copy.getGreatest().getValue() >= possibility.getGreatest().getValue()){
		return copy;
	}
	else
		return possibility;
}

void Knapsack::bruteDoubleBound(){
	greatest.reset();
	greatest = bruteDoubleBound(greatest);
}

Inventory Knapsack::bruteDoubleBound(Inventory& possibility){
	Inventory copy = possibility;
	//cout << "check" << endl;
	if (possibility.getLength() == itemList.size()){
		if(possibility.getGreatest() < greatest.getGreatest()){
			possibility.setLow();
		}
		return possibility;
	}

	
	//possibility.print(itemList);
	if(possibility.push(true, itemList) == true)
		possibility = bruteForce(possibility);
	if(copy.push(false, itemList) == true)
		copy = bruteForce(copy);
	//cout << "compare" << copy.getGreatest().value << " and " << possibility.getGreatest().value << endl;
	if (!copy.isLow() && copy.getGreatest().getValue() >= possibility.getGreatest().getValue()){
		return copy;
	}
	else
		return possibility;
}

Inventory Knapsack::greedy(){
	greatest.reset();
	for(int i = 0; i < itemList.size(); i++){
		itemList[i].setRatio(itemList[i].getValue() / itemList[i].getWeight());
	}
	int temp = itemList.size() - 1;
	sort(itemList.begin(), itemList.end());
	for(int j = 0; j < itemList.size(); j++){
		if(greatest.push(true, itemList) == false){
			break;
		}
	}
	return greatest;
}

