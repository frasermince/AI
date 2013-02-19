#include <vector>
#include <bitset>
using namespace std;



class Inventory{
public:
	Inventory(int w);
	Inventory(const Inventory& other);
	bool push(bool check, vector<Item>& itemList);
	Inventory operator=(const Inventory& other);
	int getLength()	const				{return length;}
	int getWeightLimit()	const 		{return weightLimit;}
	Item getGreatest()	const 			{return greatest;}
	void print(vector<Item>& itemList)	const;
	void reset();
	void setLow()						{low = true;}
	bool isLow()						{return low;}
private:
	int length;
	int weightLimit;
	bitset<64> options;//construction?
	Item greatest;
	bool low;
};

