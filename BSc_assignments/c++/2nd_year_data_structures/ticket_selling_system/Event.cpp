#include "hw1.h"

//Construction of Event
Event::Event(string id, string placeName, string eventName, string date, int price)
	:eventId(id),placeName(placeName),eventName(eventName),date(date),price(price)
{
}

void Event::addPerformer(string performer)
{
	performers.push_back(performer);
}

string Event::getEventId()
{
	return eventId;
}

string Event::getPlaceName()
{
	return placeName;
}

string Event::getDate()
{
	return date;
}

Event::~Event()
{
}


ostream& operator<<(ostream &out, const Event &event)
{
	int i,sizex;
	if(event.placeName=="")
		cout<<event.eventId<<endl;	
	else
	{
		cout<<event.eventId<<endl;
		cout<<event.eventName<<endl;
		cout<<event.date<<endl;
		cout<<event.price<<endl;
		cout<<event.placeName<<endl;
	
		sizex=event.performers.size();	//getting the number of performers
		cout<<sizex<<endl;		//printing the number of performers
	
		for(i=0;i<sizex;i++)
			cout<<event.performers[i]<<endl;
	}

}
