class Item{
public:
	Item()									{weight = 0; value = 0; ratio = 0;}
	Item(double w, double v)				{weight = w; value = v; ratio = 0;}
	Item(const Item& other)					{weight = other.weight; value = other.value; ratio = other.ratio;}
	Item	operator=(const Item& other)	{weight = other.weight; value = other.value; ratio = other.ratio; return *this;}
	void	set(double w, double v)			{weight = w; value = v;}
	double	getWeight()const				{return weight;}
	double	getValue()const					{return value;}
	double	getRatio()const					{return ratio;}
	void	setRatio(double num)			{ratio = num;}
	void	addTo(double w, double v)		{weight += w; value += v;}
	void	subTo(double w, double v)		{weight -= w; value -= v;}
	void	reset()							{weight = 0; value = 0; ratio = 0;}
	bool	operator<(const Item& other) const;
	bool	operator!=(const Item& other) const;
private:
	double weight;
	double value;
	double ratio;
};