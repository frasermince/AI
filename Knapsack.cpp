#include "Item.h"
#include "Inventory.h"
#include "Knapsack.h"
#include <ctime>
#include <algorithm>
#include <cassert>
using namespace std;


void Knapsack::bruteForce(){//simple brute force implementation. No pruning
	greatest.reset();//resets greatest so that multiple pruning methods can be called in a rwo
	n = 0;
	greatest = bruteForce(greatest);//calls a helper function that does all the work
	//print could theoretically be put here but it would mess up the timing. I am manually doing it from main after I determine my timing.
}

Inventory Knapsack::bruteForce(Inventory& possibility){
	n++;
	Inventory reject = possibility;//copy Inventory
	if (possibility.isFin()){//base case
		return possibility;
	}
	possibility.push(true, itemList);//pushes true onto the bitset for the kth item and adds the k weight and value to the current Item within inventory
	possibility = bruteForce(possibility);//recursive call for true
	reject.push(false, itemList);//Puts false onto bitset
	reject = bruteForce(reject);

	if (reject.getGreatest().getValue() >= possibility.getGreatest().getValue()){
		return reject;
	}
	else{
		return possibility;
	}
}

void Knapsack::maxBound(){//Simple pruning that cuts off any recursive calls that cause the current weight and value to go over limit
	n = 0;
	greatest.reset();
	greatest = maxBound(greatest);
}

Inventory Knapsack::maxBound(Inventory& possibility){
	n++;
	Inventory accepted = possibility;
	bool one;
	bool two;
	if (possibility.isFin()){
		return possibility;
	}
	one = accepted.push(true, itemList);
	two = possibility.push(false, itemList);
	if(one)
		accepted = maxBound(accepted);
	possibility = maxBound(possibility);

	if ((accepted.getGreatest().getValue() >= possibility.getGreatest().getValue()) && one){
		return accepted;
	}
	else
		return possibility;
}


void Knapsack::reversalPrune(){//Pruning that starts Inventory containing everything and works backwards if over half the items are needed to fill the bag
	greatest.reset();
	double total = 0; double valTotal = 0;;
	for(int i = 0; i < itemList.size(); i++){//gets the sum of all the items
		total += itemList[i].getWeight();
		valTotal += itemList[i].getValue();
	}
	if (total/2 <= (double)greatest.getWeightLimit()){//checks if the knapsack needs over half the items to be full
		greatest.reversal(total, valTotal);
	}
	n = 0;
	greatest = reversalPrune(greatest);
	if(greatest.getGreatest().getWeight() > greatest.getWeightLimit())
		greatest.reset();
	if(rev)
		greatest.flip();
}

Inventory Knapsack::reversalPrune(Inventory& possibility){//this part is fairly standard. The interesting stuff happens in the other reversalPrune function and within inventory
	n++;
	Inventory copy = possibility;
	if (possibility.isFin()){
		return possibility;
	}

	if(possibility.push(true, itemList))
		possibility = reversalPrune(possibility);
	if(copy.push(false, itemList))
		copy = reversalPrune(copy);

	if (possibility.getGreatest().getValue() >= copy.getGreatest().getValue() || copy.getGreatest().getWeight() > copy.getWeightLimit()){
		return possibility;
	}
	else{
		return copy;
	}
}



//This next section is my failed code. I left it in because I discuss it in my paper. Please note that some of it does not work. Other parts work just fine but gave me nominal or no efficiency gain.
/*void Knapsack::bruteMinBound(){
	n = 0;
	greatest.reset();
	greatest = bruteMinBound(greatest);
}

Inventory Knapsack::bruteMinBound(Inventory& possibility){
	n++;
	Inventory copy = possibility;
	if (possibility.getLength() == itemList.size()){
		if(possibility.getGreatest() < greatest.getGreatest()){
			possibility.setLow();
		}
		return possibility;
	}

	
	possibility.push(true, itemList) == true;
	possibility = bruteMinBound(possibility);
	copy.push(false, itemList) == true;
	copy = bruteMinBound(copy);
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
	if (possibility.getLength() == itemList.size()){
		if(possibility.getGreatest() < greatest.getGreatest()){
			possibility.setLow();
		}
		return possibility;
	}

	
	if(possibility.push(true, itemList) == true)
		possibility = bruteDoubleBound(possibility);
	if(copy.push(false, itemList) == true)
		copy = bruteDoubleBound(copy);
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
	if (possibility.getLength() == itemList.size()){
		return possibility;
	}
	possibility.push(true, itemList);
	copy.push(false, itemList);
	
	one = (double)possibility.getGreatest().getValue() <= greedyVal;
	if(one)
		possibility = bruteGreedy(possibility);
	else
		cout << (double)possibility.getGreatest().getValue() << " > " << greedyVal << endl;
	copy = bruteGreedy(copy);

	if (possibility.getGreatest().getValue() >= copy.getGreatest().getValue() && one){
		return possibility;
	}
	else{
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
	if (possibility.getLength() == itemList.size()){
		return possibility;
	}

	
	
	if(possibility.push(true, itemList) && (double)possibility.getGreatest().getValue() <= greedyVal)
		possibility = bruteDoubleGreedy(possibility);
	if(copy.push(false, itemList) && (double)copy.getGreatest().getValue() <= greedyVal)
		copy = bruteDoubleGreedy(copy);

	if (copy.getGreatest().getValue() >= possibility.getGreatest().getValue()){
		return copy;
	}
	else{
		return possibility;
	}
}

void Knapsack::prepare(){
	Item temp = greedy().getGreatest();
	double weight = temp.getWeight();
	double value = temp.getValue();
	double limit = greatest.getWeightLimit();
	value *= (limit/weight);
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
}*/

