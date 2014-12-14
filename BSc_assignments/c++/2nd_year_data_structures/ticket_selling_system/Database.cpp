#include "hw1.h"

Database::Database()
{
}

Database::~Database()
{
	tickets.clear();
	events.clear();
	places.clear();
}

Place Database::getPlace(string placeName)
{
	int pp,sizePlace;
	sizePlace=places.size();   //get the size of the places vector
	
	try{
		for(pp=0; pp<sizePlace; pp++)
			if(places[pp].getPlaceName()==placeName)	//if place name does not exist, throw an error
				return places[pp];
	
		throw (SystemError) 1;
	}
	catch(SystemError x) 
	{
		Place a("ERR_PLACE_NOT_EXISTS",Place::PLACE_STADIUM,0,"");
		return a;
	
	}
	
}

Event Database::getEvent(string eventId)
{
	int pe,sizeEvent;
	sizeEvent=events.size();	//get the size of event vector
	
	try{
		for(pe=0;pe<sizeEvent; pe++)
			if(events[pe].getEventId()==eventId)	//if the event does not exist throw an error
				return events[pe];
		
		throw (SystemError) 3;
	}
	catch(SystemError x) 
	{
		Event a("ERR_EVENT_NOT_EXIST","","","",0);		
		return a;
	}
	
}

vector<Ticket> Database::getEventTickets(string eventId)	//choosing tickets by given eventid criteria
{
	vector<Ticket> newTickets;
	int newCount,sizex;

	sizex=tickets.size();	//getting the size of vector of ticket

	for(newCount=0; newCount<sizex; newCount++)
		if(eventId== tickets[newCount].getEventId())		//get the tickets whose event ids are same
			newTickets.push_back(tickets[newCount]);

	return newTickets;
	
}

vector<Event> Database::getEventsByPlace(string placeName)  //choose events by placename criteria
{
	vector<Event> newEvents;
	int newCount,sizex;

	sizex=events.size();	//getting the size of vector of events

	for(newCount=0; newCount<sizex; newCount++)
		if(placeName== events[newCount].getPlaceName())		//get the events whose place names are same
			newEvents.push_back(events[newCount]);

	return newEvents;
}

void Database::addPlace(Place place)
{
	int sizex,i;
	string name;

	name=place.getPlaceName();				//getting place name
	sizex=places.size();					//getting size of place vector
		
	try{
		for(i=0; i<sizex; i++)							//searching place entries
		{
			if(places[i].getPlaceName()==name)	
				throw (SystemError) 0;					//if place exists, return error messages
		}
		places.push_back(place);		//if no error messages received add place entry.
	}
	
	catch(SystemError x) {
		cout << "ERR_PLACE_EXISTS"<<endl;
	}
}

void Database::addEvent(Event event)
{
	int i,sizex;
	string evId, evDate, plName;
	bool doesExist=false;
	vector<Event> eventList;		//definition of new eventlist

	evId=event.getEventId();		//getting event id to buffer
	evDate= event.getDate();		//getting date of event
	plName= event.getPlaceName();		//getting the name of place
	
	try{
		sizex=events.size();	//getting size of events
		
		for(i=0; i<sizex; i++)
		{
			if(evId==events[i].getEventId())		//if id exists throw an existence error
				throw (SystemError) 2;				
		}
		
		eventList=getEventsByPlace(plName);			//filtering events and choosing the right ones.
		sizex=eventList.size();
		
		if(sizex)					//if there exist entries in new vector, control the dates
			for(i=0; i<sizex; i++)
			{
				if(evDate==eventList[i].getDate())			//if there exists an event in same place at same time
					throw (SystemError) 4;				//produce occupiancy error
			}
		
		else 
		{	
			sizex=places.size();				//getting size of place vector
			for(i=0; i<sizex; i++)				//find the placeName if it exists
				if(plName==places[i].getPlaceName())
				{	
					doesExist=true;		
					break;
				}
			if(!doesExist)			//if place does not exist
				throw (SystemError) 1;	//throw an existance exception

		}
		events.push_back(event);
	
	}
	catch(SystemError x) {
	
		if(x==1)cout << "ERR_PLACE_NOT_EXISTS"<<endl; 
		if(x==2)cout << "ERR_EVENT_EXISTS"<<endl;
		if(x==4)cout << "ERR_PLACE_OCCUPIED"<<endl;
			
	}
	
	eventList.clear();			//deleting the vector, and cleaning the buffer
}



void Database::reserveTicket(string eventId, string personName, int numSeats)
{
	int i,sizex,totalSeat=0,maxSeats;
	vector<Ticket> ticketList;
	bool doesExist=false;

	ticketList=getEventTickets(eventId);				//choose tickets belongs to eventId
	sizex=ticketList.size();					//get the size of list
	

	try{
		for(i=0;i<sizex;i++)
			if(personName!=ticketList[i].getOwnerName())		//if ownernames are different
				totalSeat+=ticketList[i].getNumberOfSeats();	//calculate occupied seats
			
			else throw (SystemError) 6;							//if they are same throw existence exception
				
		if(totalSeat)
		{	
			maxSeats=getPlace(getEvent(eventId).getPlaceName()).getMaxSeats();
			if(totalSeat + numSeats > maxSeats)	//if there aren't enough place throw an error
				throw (SystemError) 5;
		}
		else 
		{
			sizex=places.size();				//getting size of event vector
			for(i=0; i<sizex; i++)				//find the placeName if it exists
				if(eventId==events[i].getEventId())
				{	
					doesExist=true;		
					break;
				}
			if(!doesExist)			//if place does not exist
				throw (SystemError) 3;	//throw an existance exception
		}
		tickets.push_back(Ticket(eventId,personName,numSeats,true));	//add new ticket object

	}
	catch(SystemError x) {
		if(x==3) cout << "ERR_EVENT_NOT_EXISTS"<<endl; 
		if(x==5) cout << "ERR_NOT_ENOUGH_SEATS"<<endl;		
		if(x==6) cout << "ERR_TICKET_CUSTOMER_EXISTS"<<endl;
	
	}
	ticketList.clear();			//deleting the vector, and cleaning the buffer
}

void Database::cancelTicket(string eventId, string personName)
{
	int i,sizex;
	bool doesExist=false;

	sizex=tickets.size();					//get the size of list

	try{
		for(i=0;i<sizex;i++)		
			if(personName==tickets[i].getOwnerName()&&eventId==tickets[i].getEventId())
			{															
			tickets.erase(tickets.begin()+i,tickets.begin()+i+1);
				doesExist=true;			//if ticket is found, erase the relevant entry and indicate as bool


			}
		if(!doesExist)				//if ticket weren't found, throw an exception
			throw (SystemError) 7;
	}
	catch(SystemError x) {
		cout << "ERR_TICKET_CUSTOMER_NOT_EXISTS"<<endl;
	}
}				

void Database::sellTicket(string eventId, string personName)
{
	int i,sizex,seats;
	bool doesExist=false;

	sizex=tickets.size();					//get the size of list

	try{
		for(i=0;i<sizex;i++)
			if(personName==tickets[i].getOwnerName()&&eventId==tickets[i].getEventId())
			{	
				seats=tickets[i].getNumberOfSeats();
					
				//if ticket is found, erase the relevant entry and indicate as bool
			
				tickets.erase(tickets.begin()+i,tickets.begin()+i+1);
				tickets.push_back(Ticket (eventId,personName,seats,false));
						
				//and add again as a ticket
				doesExist=true;


			}
		if(!doesExist)
			throw (SystemError) 7;
	}
	catch(SystemError x) {
		cout << "ERR_TICKET_CUSTOMER_NOT_EXISTS"<<endl;
	}
}				

int Database::getNumberOfAvailableSeats(string eventId)
{
	int maxSeats,i,sizex,occupied=0;
	vector<Ticket> ticketList;
	bool doesExist=false;

	ticketList=getEventTickets(eventId);		//choose tickets belongs to eventId
	sizex=ticketList.size();					//get the size of list
		
	try{
		if(sizex)
			for(i=0;i<sizex;i++)
				occupied+=ticketList[i].getNumberOfSeats();   //find total occupied seats
		else
		{
			sizex=events.size();
			for(i=0;i<sizex;i++)
				if(events[i].getEventId()==eventId)
				{
					doesExist=true;
					break;
				}	

			if(!doesExist)
				throw (SystemError) 3;
		}
			
	}	
	catch(SystemError x)
	{
		cout<<"ERR_EVENT_NOT_EXIST"<<endl;
		
	}

	maxSeats= getPlace(getEvent(eventId).getPlaceName()).getMaxSeats(); 
	ticketList.clear();	

	return maxSeats-occupied;
}

void Database::listPlaces()
{
	int i,sizex;
	
	sizex=places.size();	//get the size of list
	
	for(i=0; i<sizex; i++)		//list all the place entries
		cout<<places[i];
}

void Database::listEvents()
{
	int i,sizex;
	
	sizex=events.size();	//get the size of list

	for(i=0; i<sizex; i++)		//list all the event entries
		cout<<events[i];
}

void Database::listEventTickets(string eventId)
{
	int i,sizex;
	vector<Ticket> ticketList;
	
	ticketList=getEventTickets(eventId);
	sizex=ticketList.size();	//get the size of list

	try{	
		if(sizex)
			for(i=0;i<sizex;i++)
				cout<<ticketList[i];
		else	
			throw (SystemError) 3;	
	}
	catch(SystemError x){
		cout<<"ERR_EVENT_NOT_EXISTS"<<endl;
	}
	
	ticketList.clear();
}

void Database::listEventsByPlace(string placeName)
{
	int i,sizex;
	vector<Event> eventList;

	eventList=getEventsByPlace(placeName);
	sizex=eventList.size();	//get the size of list

	try{	
		if(sizex)
			for(i=0;i<sizex;i++)
				cout<<eventList[i];
		else	
			throw (SystemError) 1;	
	}
	
	catch(SystemError x){
		cout<<"ERR_PLACE_NOT_EXISTS"<<endl;
	}
	
	eventList.clear();
}


