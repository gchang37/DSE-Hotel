#include "HotelReservation.h"
using namespace std;

/* Room Implementation */
Room::Room(){}
Room::Room(int rmNum){
  roomID = rmNum;
  next = nullptr;
}
/*
Room::Room(int id, int beds){
    roomID = id;
    numOfBeds = beds;
}*/

int Room::getRoomID(){return roomID;}

/* Customer Implementation */

Customer::Customer(){next = prev = nullptr;}

Customer::Customer(string inDate, string custName, int beds, int stay){
    this->checkInDate = getDate(inDate);
    this->customerID = custName;
    this->numOfRequestBeds = beds;
    this->checkOutDate = duration_of_stay(checkInDate, stay);
}

int Customer::getRequestedBeds()const{return numOfRequestBeds;}

string Customer::getCustomerID(){return customerID;}

Date Customer::getDate(string inDate){
  const char *date = inDate.c_str();
  //string in = inDate;
  //char* date = in;
  Date d;
  sscanf(date, "%2d/%2d/%4d", &d.month, &d.day, &d.year);
  //cout << d.day << d.month << d.year << endl;
  return d;
}

Date Customer::getCheckInDate(){return checkInDate;}

Date Customer::getCheckOutDate(){return checkOutDate;}

Date Customer::duration_of_stay(Date inDate, int stay){
  Date out;
  int carry= 0;

  out.day = inDate.day +stay;
  while(out.day >28){
    if(out.month == 2){
      out.day -= 28;
    }else if(out.month == 4 || out.month == 6 || out.month == 9 || out.month == 11){
      out.day -= 30;
    }else {out.day -= 31;}
    carry ++;
  }
  if(carry > 0){
    out.month += carry;
    if(out.month >12){
      out.month -= 12;
      carry = 1;
    }else carry = 0;
  }
  if(carry >0){
    out.year ++;
  }


  return out;
}

void Customer::setRoom(int rmID){
  this->room = Room(rmID);
  cout << "the given room is " << rmID << endl;
}

int Customer::getRoomID(){return room.getRoomID();}

/* SLL Implementation */

SLL::SLL(){
  head = nullptr;
  total = capacity = 0;
}

SLL::SLL(int bednum, int bTotal){
  head = nullptr;
  beds = bednum;
  total = bTotal;
  capacity = 0;
}
/*
void SLL::addFirstRoom(Room r){
  r.next = head;
  *head = r;
  capacity ++;  
}*/
void SLL::addFirstRoom(int rmID){
  Room *room = new Room(rmID);
  //Room *tmp = head;
  room->next = head;
  head = room;
  capacity++;
}

int SLL::getBedNum() const{return beds;}

int SLL::getFirstRoomID() const{
  if (capacity == 0)
    throw runtime_error("Index out of range");
  else
    return head->roomID;
}

int SLL::getTotalBedNum() const {return total;}

int SLL::removeFirstRoom() throw (runtime_error){
  if (capacity == 0){
    throw runtime_error("No available rooms in the list");
  }else{
    capacity --;
    Room *tmp = head;
    int id = tmp->roomID;
    head = head->next;
    tmp = nullptr;
    delete tmp;
    return id;
  }
}

bool SLL::isEmpty() const{
  return head == nullptr;
}

int SLL::getSize() const{
  return capacity;
}

/* DLL Implementation*/


DLL::DLL(){
  head = tail = nullptr;
  size = 0;
}

void DLL::insert(Customer *c, Customer *cp){
  Customer *newCustomer = c;
  if(getSize() == 0){
    head = newCustomer;
    tail = newCustomer;
    cout << "1st customer added to DLL " << endl;
  }else if (cp == tail){        //inserting after tail
    newCustomer->prev = tail;
    tail->next = newCustomer;
    tail = newCustomer;
    cout << " customer added to the back" << endl;
  }else if(cp == head) {      //inserting before head
    newCustomer->next = head;
    head->prev = newCustomer;
    head = newCustomer;
    cout << " customer added to the front " << endl;
  }else {
    /*newCustomer->next = cp->next;
    cp->next->prev = newCustomer;
    cp->next = newCustomer;
    newCustomer->prev = cp;*/
    newCustomer->next = cp;
    newCustomer->prev = cp->prev;
    cp->prev->next = newCustomer;
    cp->prev = newCustomer;
    cout << " just checked in " << endl;
  }
  size++;
}

Customer* DLL::getFirstCustomer() const {
  return head;
}
/*
int DLL::getFirstCustomerRmID() {
  return head->getRoomID();
}*/

Customer* DLL::getLastCustomer() const{return tail;}

//int DLL::getLastCustomerRmID() const {return tail->getRoomID();}

string DLL::getCustomerID() const{
  if (getSize() == 0){
    throw runtime_error("Index out of range");
  }else return head->customerID;
}

Date DLL::getCheckOutDate() const{
  if(getSize() == 0){
    throw runtime_error("Index out of Bound");
  }else return head->checkOutDate;
}

Room DLL::removeFirst() throw (runtime_error){
  if (getSize() == 0){
   throw runtime_error("No elements in the list");
  }else{
    Customer *leaving = head;
    Room needsCleaning = leaving->room;
    if(getSize()==1){
      head = tail = nullptr;
    }else{
      leaving->next->prev = nullptr;
      head = head->next;
    }
    size--;  
    leaving = nullptr;
    delete leaving;
    return needsCleaning;
  }
}

bool DLL::isEmpty() const{
  return head == nullptr;
}

int DLL::getSize() const{
  return size;
}

/* Priority Implementation */


PriorityQueue::PriorityQueue(){
}

bool PriorityQueue::isEarlierDate(Date d1, Date d2){
  if(d1.year <= d2.year){
    if(d1.month <= d2.month){
      if(d1.day < d2.day){return true;}
    }
  }
  return false;
}

void PriorityQueue::push(Customer *c){
  //Customer person = Customer(c);
  Customer *cpos = list.getFirstCustomer();
  Date compDate;
  Date currDate = c->getCheckOutDate();

  if(getSize()==0){
    list.insert(c,cpos);
  }else{
    bool found = false;
    for(int i = 0; i < getSize(); i++){
    //need to make sure that if inserting in front of head , nullptr is given
    // need to make sure if the two date are the same,
      compDate = cpos->getCheckOutDate();
      if(isEarlierDate(currDate, compDate)){
        found = true;
        list.insert(c, cpos);
        break;
      }
      cpos = cpos->next;
    }
    if(!found){ cout << "add to the end" << endl;
      cpos = list.getLastCustomer();
      list.insert(c, cpos);
    }
    
  }
  
}


Date PriorityQueue::topCheckOutDate(){
    return list.getCheckOutDate();
}


string PriorityQueue::topcheckOutID(){
    return list.getCustomerID();
}

Room PriorityQueue::pop() throw (runtime_error){
return list.removeFirst();
}


int PriorityQueue::getSize() const{
  return list.getSize();
}

bool PriorityQueue::isEmpty(){
  return list.isEmpty();
}
