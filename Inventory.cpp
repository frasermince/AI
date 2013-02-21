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
	Item optimum();
}

Inventory::Inventory(const Inventory& other){
	//low = other.low;
	length = other.getLength();
	weightLimit = other.getWeightLimit();
	optimum = other.optimum;
	options = other.options;
	rev = other.rev;
	fin = other.fin;
	max = other.max;
}

Inventory Inventory::operator=(const Inventory& other){
	//low = other.low;
	length = other.getLength();
	weightLimit = other.getWeightLimit();
	optimum = other.optimum;
	options = other.options;
	rev = other.rev;
	fin = other.fin;
	max = other.max;
	return *this;
}

bool Inventory::push(bool check, vector<Item>& itemList){//pushes check onto options adds the length value of itemList to greatest as needed
	bool win;
	int input;
	if(rev)
		input = max - length;
	else
		input = length;
	double newWeight;
	if(rev)
		newWeight = optimum.getWeight();
	else
		newWeight = optimum.getWeight() + itemList[input].getWeight();
	// notice that even if I specify true it will still push false if it goes overweight or in the case of rev is already underweight
	if (newWeight <= weightLimit xor rev) {//when rev is on we are starting from the top and working down otherwise we are working up
		if(check){ //only want to change optimum if check is true. Otherwise we are not taking this item
			if (!rev)
				optimum.addTo(itemList[input].getWeight(), itemList[input].getValue());
			else{
				optimum.subTo(itemList[input].getWeight(), itemList[input].getValue());
			}
		}
		options.set(input, check);
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
}

void Inventory::print(vector<Item>& itemList)	const{//prints the inventory
	cout << "Optimum value = " << optimum.getValue() << endl;
	cout << "Final weight = " << optimum.getWeight() << endl;
	int count;
	if(rev)
		count = max - length;
	else
		count = length;
	cout << "length = " << itemList.size() << endl;
	for (int i = 0; i < (int)itemList.size(); i++){
		cout << options[i] << " ";
	}
}

void Inventory::reset(){//clears the inventory for reuse
	fin = false;
	rev = false;
	length = 0;
	options.reset();
	optimum.reset();
	//low = false;
}

void Inventory::reversal(double weight, double value){//makes it so the inventory starts with all items and items are removed
	rev = true;
	length = max;
	optimum.set(weight, value);//puts everything within optimum
}
