#include <vector>
#include <bitset>
using namespace std;



class Inventory{
public:
	Inventory(int w, int num);
	Inventory(const Inventory& other);
	bool push(bool check, vector<Item>& itemList);
	Inventory operator=(const Inventory& other);
	int getLength()	const				{return length;}
	int getWeightLimit()	const 		{return weightLimit;}
	Item getGreatest()	const 			{return greatest;}
	void print(vector<Item>& itemList)	const;
	void reset();
	//void setLow()						{low = true;}
	//bool isLow()						{return low;}
	void reversal(double weight, double val);
	bool isRev()	const				{return rev;}
	bool isFin() 	const 				{return fin;}
	void flip()							{options.flip();}//nots all bits
private:
	int length;
	int max;
	int weightLimit;
	bitset<64> options;//power of 2 for efficiency sake
	Item greatest;
	//bool low; originially used for bruteMin. No longer in user
	bool rev;//see reversal function
	bool fin;//determines if the base case has been reached
};

