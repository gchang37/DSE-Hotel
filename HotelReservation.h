/**
 * HotelReservation.h file
 * Description: this class models hotel reservation
 * Author: Gina Chang
 * Creation Date:June 1st, 2018
 */ 

#ifndef HotelReservation_h
#define HotelReservation_h

#include <iostream>
#include <string>
#include <stdexcept>
//#include <stdio.h>
using namespace std;

struct Date{
  int day;
  int month;
  int year;
};

class Room{
    public:            
        //int numOfBeds;
        Room* next;

        Room();
        Room(int);
        //Room(int, int);
        int getRoomID();

    private:
      int roomID;    
      friend class SLL;
      friend class Customer;
};

class Customer{
    public:
      Customer *next;
      Customer *prev;

      Customer();
      Customer(string, string, int, int);
      /*Customer(Customer &c){ 
        this->customerID = c.customerID;
        this->numOfRequestBeds = c.numOfRequestBeds;
        this->checkInDate = c.checkInDate;
        this->checkOutDate = c.checkOutDate;
      }*/
      string getCustomerID();
      int getRequestedBeds() const;
      Date getDate(string);
      Date getCheckInDate();
      Date getCheckOutDate();
      Date duration_of_stay(Date, int);
      void setRoom(int);
      int getRoomID();

    private:
      string customerID;
      int numOfRequestBeds;
      Date checkInDate;
      Date checkOutDate;
      Room room;
      friend class DLL;    
       
};

class SLL{
  public:
    int inUse = 0;
    SLL();
    SLL(int, int);
    //void addFirstRoom(Room);
    void addFirstRoom(int);
    int getBedNum() const;
    int getFirstRoomID() const;
    int getTotalBedNum() const;   
    int removeFirstRoom() throw (runtime_error);
    bool isEmpty() const;
    int getSize() const;

  private:
    Room *head;
    int beds, total,capacity = 0;
    //friend class DLL;
};

class DLL{
  public:
    DLL();
    //void insert(Customer&);
    void insert(Customer*, Customer*);
    Customer* getFirstCustomer() const;
    //int getFirstCustomerRmID(); //const;
    Customer* getLastCustomer() const;
    //int getLastCustomerRmID() const;
    string getCustomerID() const;
    Date getCheckOutDate() const;
    Room removeFirst() throw (runtime_error);
    bool isEmpty() const;
    int getSize() const;

  private:
    Customer *head;
    Customer *tail;
    int size;
    friend class PriorityQueue;
};

class PriorityQueue{
  public:
    PriorityQueue();
    int getSize() const;
    bool isEmpty();
    Date topCheckOutDate();
    string topcheckOutID();
    //bool getFirstRoomID(int, int);
    bool isEarlierDate(Date, Date);
    void push(Customer*);
    Room pop() throw (runtime_error);

  private:
    DLL list;
};



#endif