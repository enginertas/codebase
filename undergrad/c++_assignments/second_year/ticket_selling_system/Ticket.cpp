#include "hw1.h"

//initialization of ticket object
Ticket::Ticket(string eventId, string ownerName, int numSeats, bool isReservation)
	:eventId(eventId),ownerName(ownerName),numSeats(numSeats), isReservation(isReservation)
{
}

int Ticket::getNumberOfSeats()
{
	return numSeats;
}

string Ticket::getEventId()
{
	return eventId;
}

string Ticket::getOwnerName()
{
	return ownerName;
}

bool Ticket::getIsReservation(){
	return isReservation;
}

Ticket::~Ticket()
{
}

ostream& operator<<(ostream& out, const Ticket &ticket)
{
	cout<<ticket.eventId<<endl;
	cout<<ticket.ownerName<<endl;
	cout<<ticket.numSeats<<endl;
	
	if(ticket.isReservation)	//if true set as reserved, else set as sold
		cout<<"RESERVATION"<<endl;
	else	
		cout<<"SOLD"<<endl;
					

}
