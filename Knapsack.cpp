#include "Item.h"
#include "Inventory.h"
#include "Knapsack.h"
#include <ctime>
#include <algorithm>
#include <cassert>
using namespace std;


void Knapsack::bruteForce(){
	greatest.reset();
	n = 0;
	greatest = bruteForce(greatest);
}

Inventory Knapsack::bruteForce(Inventory& possibility){
	n++;
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


void Knapsack::reversalPrune(){
	greatest.reset();
	double total = 0; double valTotal = 0;;
	for(int i = 0; i < itemList.size(); i++){
		total += itemList[i].getWeight();
		valTotal += itemList[i].getValue();
	}
	if (total/2 <= (double)greatest.getWeightLimit()){
		greatest.reversal(total, valTotal);
	}
	n = 0;
	greatest = reversalPrune(greatest);
	if(greatest.getGreatest().getWeight() > greatest.getWeightLimit())
		greatest.reset();
	greatest.flip();
}

Inventory Knapsack::reversalPrune(Inventory& possibility){
	n++;
	Inventory copy = possibility;
	//cout << "check" << endl;
	if (possibility.isFin()){
		//cout << "base "; 
		//possibility.print(itemList); 
		//cout << endl;
		return possibility;
	}

	//possibility.print(itemList);
	if(possibility.push(true, itemList))
		possibility = reversalPrune(possibility);
	if(copy.push(false, itemList))
		copy = reversalPrune(copy);
	//cout << "compare" << copy.getGreatest().value << " and " << possibility.getGreatest().value << endl;

	if (possibility.getGreatest().getValue() >= copy.getGreatest().getValue() || copy.getGreatest().getWeight() > copy.getWeightLimit()){
		//copy.print(itemList);
		return possibility;
	}
	else{
		//possibility.print(itemList);
		return copy;
	}
}

void Knapsack::bruteMaxBound(){
	n = 0;
	greatest.reset();
	greatest = bruteMaxBound(greatest);
}

Inventory Knapsack::bruteMaxBound(Inventory& possibility){
	n++;
	Inventory accepted = possibility;
	bool one;
	bool two;
	//cout << "check" << endl;
	if (possibility.isFin()){
		return possibility;
	}
	one = accepted.push(true, itemList);
	two = possibility.push(false, itemList);
	//possibility.print(itemList);
	if(one)
		accepted = bruteMaxBound(accepted);
	possibility = bruteMaxBound(possibility);

	//accepted.print(itemList);
	//
	//accepted.print(itemList);
	//cout << endl << "<" << endl;
	//rejected.print(itemList);
	//cout << endl;
	//cout << "compare" << copy.getGreatest().value << " and " << possibility.getGreatest().value << endl;
	if ((accepted.getGreatest().getValue() >= possibility.getGreatest().getValue()) && one){
		return accepted;
	}
	else
		return possibility;
}

void Knapsack::bruteMinBound(){
	n = 0;
	greatest.reset();
	greatest = bruteMinBound(greatest);
}

Inventory Knapsack::bruteMinBound(Inventory& possibility){
	n++;
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
	possibility = bruteMinBound(possibility);
	copy.push(false, itemList) == true;
	copy = bruteMinBound(copy);
	//cout << "compare" << copy.getGreatest().value << " and " << possibility.getGreatest().value << endl;
	if (!copy.isLow() && copy.getGreatest().getValue() >= possibility.getGreatest().getValue()){
		return copy;
	}
	else
		return possibility;
}

void Knapsack::bruteDoubleBound(){
	n = 0;
	greatest.reset();
	greatest = bruteDoubleBound(greatest);
}

Inventory Knapsack::bruteDoubleBound(Inventory& possibility){
	n++;
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
		possibility = bruteDoubleBound(possibility);
	if(copy.push(false, itemList) == true)
		copy = bruteDoubleBound(copy);
	//cout << "compare" << copy.getGreatest().value << " and " << possibility.getGreatest().value << endl;
	if (!copy.isLow() && copy.getGreatest().getValue() >= possibility.getGreatest().getValue()){
		return copy;
	}
	else
		return possibility;
}

void Knapsack::bruteGreedy(){
	if(greedyVal == 0){
		prepare();
	}
	greatest.reset();
	n = 0;
	greatest = bruteGreedy(greatest);

}

Inventory Knapsack::bruteGreedy(Inventory& possibility){
	n++;
	Inventory copy = possibility;
	bool one;
	bool two;
	//cout << "check" << endl;
	if (possibility.getLength() == itemList.size()){
		return possibility;
	}
	possibility.push(true, itemList);
	copy.push(false, itemList);
	
	one = (double)possibility.getGreatest().getValue() <= greedyVal;
	//two = (double)copy.getGreatest().getValue() <= greedyVal;
	if(one)
		possibility = bruteGreedy(possibility);
	else
		cout << (double)possibility.getGreatest().getValue() << " > " << greedyVal << endl;
	copy = bruteGreedy(copy);
	//cout << "compare" << copy.getGreatest().value << " and " << possibility.getGreatest().value << endl;

	if (possibility.getGreatest().getValue() >= copy.getGreatest().getValue() && one){
		//copy.print(itemList);
		return possibility;
	}
	else{
		//possibility.print(itemList);
		return copy;
	}
}


void Knapsack::bruteDoubleGreedy(){
	if(greedyVal == 0){
		prepare();
	}
	n = 0;
	greatest.reset();
	
	greatest = bruteDoubleGreedy(greatest);

}

Inventory Knapsack::bruteDoubleGreedy(Inventory& possibility){
	n++;
	Inventory copy = possibility;
	//cout << "check" << endl;
	if (possibility.getLength() == itemList.size()){
		//cout << "base "; 
		//possibility.print(itemList); 
		//cout << endl;
		return possibility;
	}

	
	//possibility.print(itemList);
	
	if(possibility.push(true, itemList) && (double)possibility.getGreatest().getValue() <= greedyVal)
		possibility = bruteDoubleGreedy(possibility);
	if(copy.push(false, itemList) && (double)copy.getGreatest().getValue() <= greedyVal)
		copy = bruteDoubleGreedy(copy);
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

void Knapsack::prepare(){
	Item temp = greedy().getGreatest();
	double weight = temp.getWeight();
	double value = temp.getValue();
	cout << "weight: " << weight << endl;
	cout << "value: " << value << endl;
	double limit = greatest.getWeightLimit();
	cout << "Fraction = " << (limit/weight) << endl;
	value *= (limit/weight);
	cout << "Max = " << value << endl;
	greedyVal = value;
}

Inventory Knapsack::greedy(){
	greatest.reset();
	for(int i = 0; i < itemList.size(); i++){
		itemList[i].setRatio(itemList[i].getWeight() / itemList[i].getValue());
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

