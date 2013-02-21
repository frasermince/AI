#include <iostream>
#include "Item.h"
#include "Inventory.h"
#include <cassert>
using namespace std;


Inventory::Inventory(int w, int num){
	max = num;
	//low = false;
	rev = false;
	fin = false;
	length = 0;
	weightLimit = w;
	Item greatest();
}

Inventory::Inventory(const Inventory& other){
	//low = other.low;
	length = other.getLength();
	weightLimit = other.getWeightLimit();
	greatest = other.greatest;
	options = other.options;
	rev = other.rev;
	fin = other.fin;
	max = other.max;
}

Inventory Inventory::operator=(const Inventory& other){
	//low = other.low;
	length = other.getLength();
	weightLimit = other.getWeightLimit();
	greatest = other.greatest;
	options = other.options;
	rev = other.rev;
	fin = other.fin;
	max = other.max;
	return *this;
	//cout << options[length] << endl;
}

bool Inventory::push(bool check, vector<Item>& itemList){//pushes check onto options adds the length value of itemList to greatest as needed
	bool win;
	int input;
	if(rev)
		input = max - length;
	else
		input = length;
	//cout << greatest.getWeight() + itemList[length].getWeight() << " <= " << weightLimit << endl;
	double newWeight;
	if(rev)
		newWeight = greatest.getWeight();
	else
		newWeight = greatest.getWeight() + itemList[input].getWeight();
	// notice that even if I specify true it will still push false if it goes overweight or in the case of rev is already underweight
	if (newWeight <= weightLimit xor rev) {//when rev is on we are starting from the top and working down otherwise we are working up
		if(check){ //only want to change greatest if check is true. Otherwise we are not taking this item
			if (!rev)
				greatest.addTo(itemList[input].getWeight(), itemList[input].getValue());
			else{
				greatest.subTo(itemList[input].getWeight(), itemList[input].getValue());
			}
		}
		options.set(input, check);
		//cout << "check" << endl;
		win = true;
	}
	else { 
		options.set(input, false);

		win = false;
	}

	if(rev){
		length--;
		if(length == 0){
			fin = true;
		}
	}
	else{
		length++;
		if(length == max){
			fin = true;
		}
	}
	return win;
	//cout << endl;
}

void Inventory::print(vector<Item>& itemList)	const{//prints the inventory
	cout << "Greatest = " << greatest.getValue() << endl;
	int count;
	if(rev)
		count = max - length;
	else
		count = length;
	cout << "length = " << itemList.size() << endl;
	for (int i = 0; i < itemList.size(); i++){
		cout << options[i] << " ";
	}
}

void Inventory::reset(){//clears the inventory for reuse
	fin = false;
	rev = false;
	length = 0;
	options.reset();
	greatest.reset();
	//low = false;
}

void Inventory::reversal(double weight, double value){//makes it so the inventory starts with all items and items are removed
	rev = true;
	length = max;
	greatest.set(weight, value);//puts everything within greatest
}
