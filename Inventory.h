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
	void setLow()						{low = true;}
	bool isLow()						{return low;}
	void reversal(double weight, double val);
	bool isFin() const 					{return fin;}
	void flip()							{options.flip();}
private:
	int length;
	int max;
	int weightLimit;
	bitset<64> options;//construction?
	Item greatest;
	bool low;
	bool rev;
	bool fin;
};

