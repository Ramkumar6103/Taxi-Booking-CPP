#include<bits/stdc++.h>
using namespace std;
class Customer{
private:
	int customerID;
	char pickUp;
	char drop;
	int pickTime;
public:
Customer(int id, char pickup, char drop, int pTime){
	this->customerID = id;
	this->pickUp = pickup;
	this->drop = drop;
	this->pickTime = pTime;
}
public:
int getCustomerId(){
	return customerID;
}
char getPickUp(){
	return pickUp;
}
char getDrop(){
	return drop;
}
int getPickUpTime(){
	return pickTime;
}
}
};

class Booking{
private:
	int bookingID;
	int dropTime;
	int amount;
	Customer customer;
public:
Booking(int id, int dTime, int amount, Customer customer){
	this->bookingID = id;
	this->dropTime = dTime;
	this->amount = amount;
	this->customer = customer;
public:
int getBookingId(){
	return bookingID;
}
int getDropTime(){
	return dropTime;
}
int getAmount(){
	return amount;
}
Customer getCustomer(){
	return customer;
}
}
};

class Taxi{
private:
	int taxiID;
	char currSpot;
	int freeTime;
	int earnings;
	vector<Booking> bookings;
public:
Taxi(int id){
	this->taxiID = id;
	this->currSpot = 'A';
	this->freeTime = 0;
	this->earnings = 0;
}
public:
bool isFree(char pickUp, int pickTime){
	int timeTravel = abs(pickup - currSpot);
	if(freeTime+timeTravel <= pickTime){
		return true;
	}
	return false;
}

void assignBookings(Booking b){
	bookings.push_back(b);
}

int getTaxiId(){
	return taxiID;
}
char getCurrSpot(){
	return currSpot;
}
int getFreeTime(){
	return freeTime;
}
int getEarning(){
	return earnings;
}
vector<Booking> getBookings(){
	return bookings;
};

class BookingSystem{
private:
	vector<Taxi> taxis;
public:
	BookingSystem(int taxiCount){
		for(int i=1;i<=taxiCOunt;i++){
			taxis.push_back(Taxi(i));
		}
	}	
int calculateCharges(char pickUp, char drop){
	int distance = abs(pickUp - drop) * 15;
	int charges = 100;
	distance -= 5;
	charges += (distance * 10);
	return charges;
}

Taxi findTaxi(char pickUp, int pickTime){
	vector<Taxi> freeTaxis;
	for(auto t : Taxis){
		if(isFree(pickUp, pickTime) freeTaxis.push_back(t);
	}
	int minDistance = INT_MAX;
	for(auto t: freeTaxis){
		minDistance = min(minDistance, abs(pickUp - t->getCurrSpot()));
	}
	vector<Taxi> closest;
	int minEarnings = INT_MAX;
	for(auto t: freeTaxis){
		}
}


	
};
int main(){
	return 0;
}