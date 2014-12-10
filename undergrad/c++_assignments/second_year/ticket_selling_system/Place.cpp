#include "hw1.h"

//Construction of Place
Place::Place(string name, Place::Type type, int seats, string address)
	: placeName(name), type(type), maxSeats(seats), address(address)
{
}

//
void Place::setAddress(string newAddress)
{	
	address.erase();			//deallocating old address
	address=newAddress;			//getting new address
}

int Place::getMaxSeats()
{	
	return maxSeats;
}

string Place::getPlaceName()
{	
	return placeName;
}

ostream& operator<<(ostream &out, const Place &place)
{
	if(place.maxSeats)
	{
		cout<<place.placeName<<endl;
		cout<<(Place::Type)place.type<<endl;
		cout<<place.maxSeats<<endl;
		cout<<place.address<<endl;
	}
	else
		cout<<place.placeName<<endl;
}
Place::~Place()
{
}


