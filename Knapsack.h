#include <iostream>
#include <cassert>
#include <vector>
#include <bitset>
using namespace std;


class Knapsack{
public:
	Knapsack(int w, vector<Item> list)	: greatest(w,list.size())		{itemList = list; n = 0;}
	void bruteForce();
	Inventory bruteForce(Inventory& possibility);

	void maxBound();
	Inventory maxBound(Inventory& possibility);

	void reversalPrune();
	Inventory reversalPrune(Inventory& possibility);
	void reset();
	
	//This next section is my failed code. I left it in because I discuss it in my paper. Please note that some of it does not work. Other parts work just fine but gave me nominal or no efficiency gain
	/*void bruteMinBound();
	Inventory bruteMinBound(Inventory& possibility);

	void bruteDoubleBound();
	Inventory bruteDoubleBound(Inventory& possibility);

	void bruteGreedy();
	Inventory bruteGreedy(Inventory& possibility);

	void bruteDoubleGreedy();
	Inventory bruteDoubleGreedy(Inventory& possibility);

	void prepare();*/

	Inventory greedy();
	void print()											{cout << "Number of recursive calls: " << n << endl; greatest.print(itemList);}

private:
	long long n;//used to see how many recursive calls are made per algorithm
	Inventory greatest;
	//double greedyVal;//was used when I was planning on using greedy. Now depreciated
	vector<Item> itemList;
};