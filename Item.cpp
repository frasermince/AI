#include "Item.h"

	bool Item::operator<(const Item& other) const{
		return ratio < other.ratio;
	}

	bool Item::operator!=(const Item& other) const{
		return ratio != other.ratio;
	}