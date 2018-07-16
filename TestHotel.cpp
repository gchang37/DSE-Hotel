#include <fstream> // needed to read file: hotel log
#include <sstream> // needed to read file: hotel log

#include <iostream>
#include <string>
#include <vector>
#include "HotelReservation.h"
using namespace std;

/* prototype for test */
void testIStringStream();
void testIFStream();
void testRoom();
void testCustomer();
void testCustomerQueue();

/*testing utility: */

/**
 * assert statement
 */         
void _assert(string exp, string act) {
    if(exp != act) {
        cerr << "FAIL exp:'" << exp << "' act:'" << act << "'" << endl;
    }
}
void _assert(int exp, int act) {
    if(exp != act) {
        cerr << "FAIL exp:'" << exp << "' act:'" << act << "'" << endl;
    }
}

/**
 * prints the Date struct
 */ 
void printDate(Date d){
    cout << d.year << "-" <<  d.month  << "-" << d.day << endl;
}

/* functions for hotel*/

/**
 * populating the SLL with rooms
 */ 
void generateRooms(vector<SLL> r, int beds , int total){
    string tmp = to_string(beds);
    string tmp1, tmp2= "";

    for(int j=1; j<=total; j++){
        tmp1 = to_string(j);
        tmp2 = tmp + tmp1;
        //cout << tmp2 << endl;
        r[beds].addFirstRoom(stoi(tmp2));
        tmp2 = "";
    }
}

/**
 * checking which room is available based on request
 * @param: assigning a room to customer based on request
 */
bool check_in(Customer *c, vector<SLL> &r, PriorityQueue &pq){
    int request = c->getRequestedBeds();
    cout << "customer requested " << request << " beds/room" << endl;
    bool hasFoundRoom = false;
    int rmNum = 0;

    /*if(r[request].inUse + r[request].getSize()< r[request].getTotalBedNum()){// not enough room with this bed number has been created
        rmNum = r[request].getTotalBedNum()-r[request].getSize();
        c.setRoom(rmNum);
        r[request].inUse++;
        pq.push(c);
    }else{*/
        for(int i = 0; i < (int)r.size()-1; i++){
            if(!r[request].isEmpty()){
                hasFoundRoom = true;
                rmNum = r[request].removeFirstRoom();
                c->setRoom(rmNum);
                cout << "about to add p" << endl;
                pq.push(c);
                cout << "p added" << endl;
                break;
            }
            request ++;
            cout << "all rooms with " << request << " beds/room is occupied! Checking the next set of rooms" << endl;
        }
        if(!hasFoundRoom){
            cout << "sorry all rooms are occupied with guests!" << endl;
        }
    //}
    return hasFoundRoom;    
}

/**
 * customer requesting room
 * need to decrement inuse--
 */ 
void check_out(Customer c){

}

/**
 *  reading Customer arrival via Hotel Log
 */ 
void readFromLog(vector<SLL> &r, PriorityQueue &p){
    istringstream iss;
    string date, name, bedNum, stay;
    string line = "" ;
    
    ifstream infile("myTest.txt");
    //ifstream infile("test.txt");
    if(infile.fail()){
        cout<< "Invalid pathway to text" << endl;
    }else{
        while(getline(infile, line)){
            
            stringstream iss(line);
            getline(iss, date, ',');
            getline(iss, name, ',');
            getline(iss, bedNum, ',');
            getline(iss, stay, ','); //check!!
            //cout << date << name << bedNum << stay << endl;
            
            Customer *c = new Customer(date, name, stoi(bedNum), stoi(stay));

            if(!check_in(c,r,p)){
                cout << "Too many guests! Not enough room" << endl;
                break;
            }
            
           //cout << line << endl;
        }
    }
    cout << "Finished writing inputes" << endl;
    infile.close();
}


/**
 * determines if priority queue ha
 * @return:true, if either queue is not empty or there's more customer being read in; false, otherwise
 */ 
bool hasNext(){
    return false;
} 

void runHotel(){
    Room room();
    vector<SLL> rooms;
    PriorityQueue pq;

    int rm1bd = 5;
    int rm2bd = 2;
    int rm3bd = 2;
    /*cout << "Please enter the amount of rooms for 1 bed, 2 bed, 3 bed" << endl;
    cin >> rm1bd >> rm2bd >> rm3bd;
    cout << rm1bd << endl;*/

    rooms.push_back(SLL());
    rooms.push_back(SLL(1,rm1bd));
    rooms.push_back(SLL(2,rm2bd));
    rooms.push_back(SLL(3,rm3bd));

    /*generateRooms(rooms, 1, rm1bd);
    generateRooms(rooms, 2, rm2bd);
    generateRooms(rooms, 3, rm3bd);*/
    string tmp = to_string(1);
    string tmp1, tmp2= "";

    for(int j=1; j<=rm1bd; j++){
        tmp1 = to_string(j);
        tmp2 = tmp + tmp1;
        //cout << tmp2 << endl;
        rooms[1].addFirstRoom(stoi(tmp2));
        tmp2 = "";
    }
    
    tmp = to_string(2);
    for(int j=1; j<=rm2bd; j++){
        tmp1 = to_string(j);
        tmp2 = tmp + tmp1;
        //cout << tmp2 << endl;
        rooms[2].addFirstRoom(stoi(tmp2));
        tmp2 = "";
    }

    tmp = to_string(3);
    for(int j=1; j<=rm3bd; j++){
        tmp1 = to_string(j);
        tmp2 = tmp + tmp1;
        //cout << tmp2 << endl;
        rooms[3].addFirstRoom(stoi(tmp2));
        tmp2 = "";
    }
    readFromLog(rooms,pq);
}

int main(){
    
    //testIStringStream();
    //testRoom();
    //testCustomer();
    //testCustomerQueue();

    runHotel();

    //cin.ignore(2);
    return 0;
}

/**
 * testing input string from in-stream
 */
void testIStringStream(){
    istringstream iss;
    string date, name;
    int bedNum, stay;

    string request = "1/1/2018, 843A62A1MR, 3, 7";
    iss.str(request);
    iss >> date >> name >> bedNum >> stay;
    cout << "Finished writing inputes" << endl;
    cout << iss.str() << '\n';
    cout << "The date is" << date << name << bedNum << stay;
}

/**
 * testing SLL and Room
 */ 
void testRoom(){
    Room room();
    vector<SLL> rooms;
    //int maxbed;
    int rm1bd = 5;
    int rm2bd = 2;
    int rm3bd = 2;
    rooms.push_back(SLL());
    rooms.push_back(SLL(1,rm1bd));
    cout << "There are "<< rooms[1].getTotalBedNum() << " rooms with " <<  rooms[1].getBedNum() << "beds" << endl;
    rooms.push_back(SLL(2,rm2bd));
    cout << "There are "<< rooms[2].getTotalBedNum() << " rooms with " <<  rooms[2].getBedNum() << "beds" << endl;
    rooms.push_back(SLL(3,rm3bd));
    cout << "There are "<< rooms[3].getTotalBedNum() << " rooms with " <<  rooms[3].getBedNum() << "beds" << endl;
    cout << "Max bed num for a room " << rooms.size()-1 << endl;

    for(int j=1; j<=rm1bd; j++){
        rooms[1].addFirstRoom(j);
    }
    _assert(rm1bd, rooms[1].getSize());
    cout << "The first ava room is rm-1" << rooms[1].getFirstRoomID() << endl;
    cout << "Assigning rm-1" << rooms[1].removeFirstRoom() << endl;
    _assert(rm1bd-1, rooms[1].getSize());

    for(int j=1; j<=rm2bd; j++){
        rooms[2].addFirstRoom(j);
    }
    _assert(rm2bd, rooms[2].getSize());
    cout << "The first ava room is rm-2" << rooms[2].getFirstRoomID() << endl;
    cout << "Assigning rm-2" << rooms[2].removeFirstRoom() << endl;
    _assert(rm2bd-1, rooms[2].getSize());
    
}

/**
 * testing out customers and DLL
 */ 
void testCustomer(){
    //cout << "Testing Customer and DLL" << endl;
    Customer c1("1/1/2018", "onethGuest", 3, 7);
    _assert("onethGuest", c1.getCustomerID());
    cout << "The check-in date: ";
    printDate(c1.getCheckInDate());
    cout << "The Check-out date: " ;
    printDate(c1.getCheckOutDate());
    c1.setRoom(301);
    _assert(301, c1.getRoomID());

    DLL dll;
    Customer * p1 = &c1;
    cout << "DLL created" << endl;
    _assert(1, dll.isEmpty());
    _assert(0, dll.getSize());
    //dll.removeFirst();
    dll.insert(p1, nullptr);
    _assert(0,dll.isEmpty());
    _assert(1, dll.getSize());
    cout << "The customer that just checked in is " << dll.getCustomerID() << endl;
    cout << dll.getCustomerID() << " plans to check out " ;
    printDate(dll.getCheckOutDate());

    Customer c2("1/12/2018", "secondGuest", 1, 2);
    c2.setRoom(101);
    Customer *p2 = &c2;
    dll.insert(p2, p1);
    _assert(2, dll.getSize());

    Customer c3("1/14/2018", "thirdGuest", 2, 4);
    c3.setRoom(202);
    Customer *p3 = &c3;
    cout << "The Check-out date: " ;
    printDate(c3.getCheckOutDate());
    dll.insert(p3,p2);
    _assert(3, dll.getSize());
    cout << "Boundary case: accomplished adding customer at the end of DLL" << endl;
    cout << endl;

    Customer c0 ("1/1/2018", "0thGuest", 3, 3);
    Customer *p0 = &c0;
    c0.setRoom(303);    
    dll.insert(p0, p1);
    _assert(4, dll.getSize());
    cout << dll.getCustomerID() << " plans to check out " ;
    printDate(dll.getCheckOutDate());

    Customer c5("1/2/2018", "fifthGuest", 1, 3);
    Customer *p5 = &c5;
    c5.setRoom(105);
    cout << "The Check-out date: " ;
    printDate(c5.getCheckOutDate());
    dll.insert(p5,p0);
    _assert(5, dll.getSize());
    cout << dll.getCustomerID() << " plans to check out " ;
    printDate(dll.getCheckOutDate());

    cout << "Removing the first customer from DLL" << endl;
    Room r = dll.removeFirst();
    cout << "The room that needs to cleaned is " << r.getRoomID() << endl;
    _assert(4, dll.getSize());
    cout << dll.getCustomerID() << " plans to check out " ;
    printDate(dll.getCheckOutDate());

}

/**
 * testing out customers and DLL
 */ 
void testCustomerQueue(){
    PriorityQueue pq;
    _assert(1, pq.isEmpty());
    Customer c1("1/1/2018", "onethGuest", 3, 7);
    Customer *p1 = &c1;
    c1.setRoom(301);
    cout << "enqueuing customer c1" << endl;
    pq.push(p1);
    _assert(0, pq.isEmpty());
    _assert(1, pq.getSize());
    int rmID = 0;
    //_assert(1, pq.getFirstRoomID(3,rmID));
    //_assert(301, rmID);
    cout << pq.topcheckOutID() << " plans to check out " ;
    printDate(pq.topCheckOutDate());

    Customer c2("1/12/2018", "secondGuest", 1, 2);
    Customer *p2 = &c2;
    c2.setRoom(101);
    pq.push(p2);
    _assert(2, pq.getSize());

    Customer c3 ("1/14/2018", "thirdGuest", 2, 4);
    Customer *p3 = &c3;
    c3.setRoom(202);
    pq.push(p3); 

    Customer c0 ("1/1/2018", "0thGuest", 3, 3);
    Customer *p0 = &c0;
    c0.setRoom(303);
    pq.push(p0);

    Customer c5("1/2/2018", "fifthGuest", 1, 3);
    Customer *p5 = &c5;
    c5.setRoom(105);
    pq.push(p5);

    cout << endl;

    _assert(5, pq.getSize());
    cout << pq.topcheckOutID() << " plans to check out " ;
    printDate(pq.topCheckOutDate());

    Room r = pq.pop();
    cout << r.getRoomID() << "needs house keeping" << endl;

    _assert(4, pq.getSize());
    cout << pq.topcheckOutID() << " plans to check out " ;
    printDate(pq.topCheckOutDate());

    r = pq.pop();
    cout << r.getRoomID() << " also needs house keeping" << endl;

    _assert(3, pq.getSize());
    cout << pq.topcheckOutID() << " plans to check out " ;
    printDate(pq.topCheckOutDate());

    r = pq.pop();
    cout << r.getRoomID() << " also needs house keeping" << endl;

    _assert(2, pq.getSize());
    cout << pq.topcheckOutID() << " plans to check out " ;
    printDate(pq.topCheckOutDate());

    r = pq.pop();
    cout << r.getRoomID() << " also needs house keeping" << endl;

    _assert(1, pq.getSize());
    cout << pq.topcheckOutID() << " plans to check out " ;
    printDate(pq.topCheckOutDate());


}