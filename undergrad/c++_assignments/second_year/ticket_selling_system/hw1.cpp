#include <iostream>
#include "hw1.h"


/* catch(SystemError x) {
		cout << " An error occured !! " ;
	if(x == 0 ) cout << "ERR_PLACE_EXISTS"<<endl;
	if(x == 1 ) cout << "ERR_PLACE_NOT_EXISTS"<<endl; 
	if(x == 2 ) cout << "ERR_EVENT_EXISTS"<<endl;
	if(x == 3 ) cout << "ERR_EVENT_NOT_EXISTS"<<endl;
	if(x == 4 ) cout << "ERR_PLACE_OCCUPIED"<<endl;
	if(x == 5 ) cout << "ERR_NOT_ENOUGH_SEATS"<<endl;
	if(x == 6 ) cout << "ERR_TICKET_CUSTOMER_EXISTS"<<endl;
	if(x == 7 ) cout << "ERR_TICKET_CUSTOMER_NOT_EXISTS"<<endl;
	} */

using namespace std;

int main()
{
	Database data;
	
	cout<<"--------------------------------------------------------------"<<endl;
	Place p1("ANKARA SANAT EVİ",Place::PLACE_THEATRE,250, "Kızılay/ANKARA");	
	data.addPlace(p1);

	Place p2("ANKARA SANAT EVİ",Place::PLACE_THEATRE,292,"Serinyol");
	data.addPlace(p2);
	
	Place p3("KKM",Place::PLACE_CONCERT_HALL,500,"ODTU Kampüsü/ANKARA");
	data.addPlace(p3);

	Place p4("METU STADIUM",Place::PLACE_STADIUM,3000,"ODTÜ ÇANKAYA/ANKARA");
	p4.setAddress("ODTU STADYUMU");
	data.addPlace(p4);
	
	cout<<"--------------------------------------------------------------"<<endl;
	Event e("teoman 08", "asdsk", "teoman konseri","20081010",20);
	data.addEvent(e);

	Event e1("teoman 08","METU STADIUM","teoman konseri","20081010",20);
	e1.addPerformer("Teoman");
	data.addEvent(e1);

	Event e2("teoman 08","Bralsla","dşsfösşd","şdfdkfşsdk",43);
	data.addEvent(e2);
	
	Event e3("Tiyatro 08-09","ANKARA SANAT EVİ","Sivas 98","20080304",15);
	e3.addPerformer("Genco Erkal");
	e3.addPerformer("Fazil Say");
	data.addEvent(e3);
	
	Event e4("ODTU ACILIS 2008","ANKARA SANAT EVİ","Acılıs Konseri","20081017",10);
	e4.addPerformer("Şebnem Ferah");
	e4.addPerformer("Mor ve Ötesi");
	e4.addPerformer("Ezginin Günlüğü");
	data.addEvent(e4);

	Event e5("yara-34", "KKM", "Yara Gösterisi", "20081030",24);
	data.addEvent(e5);

	Event e6("yara-44", "KKM", "Yara Gösterisi", "20081030",24);
	data.addEvent(e6);

	cout<<"--------------------------------------------------------------"<<endl;
	data.listPlaces();
	data.listEvents();

	cout << "---------------------------------------------------------------------------"<<endl;

	cout << data.getEvent("Tiyatro 08-09");
	cout <<data.getPlace("fdskfsm");
	cout << data.getPlace("ANKARA SANAT EVİ");
	cout<< data.getEvent("fkdsfdfsdkfkfş");

	cout << "---------------------------------------------------------------------------"<<endl;

	vector <Event> x1;
	x1 = data.getEventsByPlace("ANKARA SANAT EVİ");
	for(int i = 0; i < x1.size() ; i++)
		cout << x1[i];

	vector <Event> x2;
	x2 = data.getEventsByPlace("Asada");
	for(int i = 0; i < x2.size() ; i++)
		cout << x2[i];

	cout << "---------------------------------------------------------------------------"<<endl;
	
	data.listEventsByPlace("ANKARA SANAT EVİ");
	data.listEventsByPlace("kfsdmdsm");

	cout << "---------------------------------------------------------------------------"<<endl;
	
	data.reserveTicket("ODTU ACILIS 2008","Erhan Erhan",10);
	data.reserveTicket("ODTU ACILIS 2008","Pelin Pelin",99);
	data.reserveTicket("Burhan Çeçen", "Engin Ertaş",21);
	data.reserveTicket("ODTU ACILIS 2008","Engin Ertaş",141);
	data.reserveTicket("ODTU ACILIS 2008","Erhan Erhan",455);
	data.reserveTicket("ODTU ACILIS 2008","sarıtüze",1);
	
	cout << "---------------------------------------------------------------------------"<<endl;
	
	data.sellTicket("ODTU ACILIS 2008","Erhan Erham");
	data.sellTicket("ODTU ACILIS 2008","Erhan Erhan");
	data.sellTicket("ODTU ACILISI 2008","Erhan Erhan");

	cout << "---------------------------------------------------------------------------"<<endl;
	data.cancelTicket("ODTU ACILIS 2008","Erhan Erham");
	data.cancelTicket("ODTU ACILISI 2008","Erhan Erhan");
	data.cancelTicket("ODTU ACILIS 2008","Engin Ertaş");
	
	cout << "---------------------------------------------------------------------------"<<endl;
	data.listEventTickets("ODTU ACILIS 2008");
	data.listEventTickets("ODTU ACILIS 2wq008");

	data.listEventTickets("ODTU ACILIS 2008");
	data.listEventTickets("GAZİ ACILIS 2008");
	
	cout << "---------------------------------------------------------------------------"<<endl;

	vector <Ticket> t;
	
	t = data.getEventTickets("ODTU ACILIS 2008");
	for(int i = 0; i < t.size() ; i++)
		cout << t[i];
	
	t = data.getEventTickets("sssa");

	cout << "---------------------------------------------------------------------------"<<endl;
	cout << "---------------------------------------------------------------------------"<<endl;

	int j = data.getNumberOfAvailableSeats("ODTU ACILIS 2008");
	cout << j<< endl;
		
	j=data.getNumberOfAvailableSeats("Tiyatro 08-09");
	cout << j<< endl;
	
	j=data.getNumberOfAvailableSeats("Tiyatro sdfsf08-09");
	cout<<j<<endl;
	

	cout << "---------------------------------------------------------------------------"<<endl;

	cout<<e5;
	cout<<p1;
	return 0;
}




















































