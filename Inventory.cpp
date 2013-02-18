#include <iostream>
#include "Item.h"
#include "Inventory.h"
#include <cassert>
using namespace std;


Inventory::Inventory(int w){
	low = false;
	length = 0;
	weightLimit = w;
	Item greatest();
}

Inventory::Inventory(const Inventory& other){
	low = other.low;
	length = other.getLength();
	weightLimit = other.getWeightLimit();
	greatest = other.greatest;
	options = other.options;
}

Inventory Inventory::operator=(const Inventory& other){
	low = other.low;
	length = other.getLength();
	weightLimit = other.getWeightLimit();
	greatest = other.greatest;
	options = other.options;
	//cout << options[length] << endl;
}

bool Inventory::push(bool check, vector<Item>& itemList){
	cout << greatest.getValue() << " <= " << itemList[length].getValue() << endl;
	if (greatest.getWeight() + itemList[length].getWeight() <= weightLimit){
		if(check)
			greatest.addTo(itemList[length].getWeight(), itemList[length].getValue());
		options.set(length, check);
		//cout << options[length] << endl;
		//cout << check << endl;
		length++;
		/*for(int i = 0; i < length; i++)
			cout << options[i];
		cout << endl;*/
		return true;
	}
	else { 
		options.set(length, false);
		length++;
		return false;
	}

	//cout << endl;
}

void Inventory::print(vector<Item>& itemList)	const{
	cout << "length = " << length << endl;
	cout << "Greatest = " << greatest.getValue() << endl;
	for (int i = 0; i < (int)itemList.size(); i++){
		cout << options[i] << " ";
	}
}

void Inventory::reset(){
	length = 0;
	greatest.reset();
}

