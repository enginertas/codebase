#ifndef _HW1_H_
#define _HW1_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* Event*/
class Event
{
        private:
                string  eventId;
                string placeName;
                string eventName;
                vector<string> performers;
                string date;
                int price;

        public:
                Event(string id, string placeName, string eventName, string date, int price);
                ~Event();
                void addPerformer(string performer);

                string getEventId();
                string getPlaceName();
                string getDate();

                friend ostream& operator<<(ostream& out, const Event &event);
};

ostream& operator<<(ostream &out, const Event &event);


/* Place */
class Place
{
        public:
                enum Type {
                        PLACE_CONCERT_HALL = 1,
                        PLACE_THEATRE = 2,
                        PLACE_PUB = 3,
                        PLACE_STADIUM = 4
                };

        private:
                string placeName;
                int maxSeats;
                string address;
                Place::Type type;

        public:
                Place(string name, Place::Type type, int seats, string address);
                ~Place();
                void setAddress(string newAddress);

                int getMaxSeats();
                string getPlaceName();

                friend ostream& operator<<(ostream& out, const Place &place);
};

ostream& operator<<(ostream& out, const Place &place);


/* Ticket */
class Ticket
{
        private:
                int numSeats;
                string ownerName;
                string eventId;
                bool isReservation;

        public:
                Ticket(string eventId, string ownerName, int numSeats, bool isReservation);
                ~Ticket();

                int getNumberOfSeats();
                string getEventId();
                string getOwnerName();
                bool getIsReservation();

                friend ostream& operator<<(ostream& out, const Ticket &ticket);
};

ostream& operator<<(ostream& out, const Ticket &ticket);


/* Database */

/*
   only Database class will throw exceptions

   ERR_PLACE_EXISTS
   ERR_PLACE_NOT_EXISTS
   ERR_EVENT_EXISTS
   ERR_EVENT_NOT_EXISTS
   ERR_PLACE_OCCUPIED
   ERR_NOT_ENOUGH_SEATS
   ERR_TICKET_CUSTOMER_EXISTS
   ERR_TICKET_CUSTOMER_NOT_EXISTS

   will be thrown in all methods whereever applicable.

*/
enum SystemError
{
        ERR_PLACE_EXISTS = 0,
        ERR_PLACE_NOT_EXISTS = 1,
        ERR_EVENT_EXISTS = 2,
        ERR_EVENT_NOT_EXISTS = 3,
        ERR_PLACE_OCCUPIED = 4,
        ERR_NOT_ENOUGH_SEATS = 5,
        ERR_TICKET_CUSTOMER_EXISTS = 6,
        ERR_TICKET_CUSTOMER_NOT_EXISTS = 7,
};

class Database
{
        private:
                vector<Place> places;
                vector<Event> events;
                vector<Ticket> tickets;

        public:
                Database();		////////////////
                ~Database();	////////////////

                void addPlace(Place place); //////////////
                void addEvent(Event event); //////////////

                void reserveTicket(string eventId, string personName, int numSeats); /////////////
                void cancelTicket(string eventId, string personName); ////////////

                // hint: cancel reservation and add ticket again
                void sellTicket(string eventId, string personName); /////////////

                Place getPlace(string placeName);			/////////////
                Event getEvent(string eventId);				/////////////
                vector<Ticket> getEventTickets(string eventId);		/////////////
                vector<Event> getEventsByPlace(string placeName);	/////////////

                int getNumberOfAvailableSeats(string eventId);
                
                void listPlaces();		/////////
                void listEvents();		/////////
                void listEventTickets(string eventId);	
                void listEventsByPlace(string placeName);
};
#endif
