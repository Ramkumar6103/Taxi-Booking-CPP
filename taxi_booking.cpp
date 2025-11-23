#include <bits/stdc++.h>
using namespace std;

class Customer {
private:
    int customerID;
    char pickUp;
    char drop;
    int pickTime;

public:
    Customer(int id, char pickup, char drop, int pTime) {
        this->customerID = id;
        this->pickUp = pickup;
        this->drop = drop;
        this->pickTime = pTime;
    }

    int getCustomerId() { return customerID; }
    char getPickUp() { return pickUp; }
    char getDrop() { return drop; }
    int getPickUpTime() { return pickTime; }
};

class Booking {
private:
    int bookingID;
    int dropTime;
    int amount;
    Customer customer;

public:
    Booking(int id, int dTime, int amount, Customer c)
        : customer(c)
    {
        this->bookingID = id;
        this->dropTime = dTime;
        this->amount = amount;
    }

    int getBookingId() { return bookingID; }
    int getDropTime() { return dropTime; }
    int getAmount() { return amount; }
    Customer getCustomer() { return customer; }
	int getCustomerId() { return customer.getCustomerId(); }
	int getPickUpTime() { return customer.getPickUpTime(); }
	char getPickUp() { return customer.getPickUp(); }
	char getDrop() { return customer.getDrop(); }
};

class Taxi {
private:
    int taxiID;
    char currSpot;
    int freeTime;
    int earnings;
    vector<Booking> bookings;

public:
    Taxi(int id) {
        this->taxiID = id;
        this->currSpot = 'A';
        this->freeTime = 0;
        this->earnings = 0;
    }

    bool isFree(char pickUp, int pickTime) {
        int travel = abs(pickUp - currSpot);
        return (freeTime + travel <= pickTime);
    }

    void assignBooking(Booking b) {
        bookings.push_back(b);
        earnings += b.getAmount();
        currSpot = b.getCustomer().getDrop();
    }

    int getTaxiId() { return taxiID; }
    char getCurrSpot() { return currSpot; }
    int getFreeTime() { return freeTime; }
    int getEarnings() { return earnings; }
    vector<Booking> getBookings() { return bookings; }

    void setFreeTime(int ft) { freeTime = ft; }
	void setEarnings(int e) { earnings = e; }
	void setCurrSpot(char cs) { currSpot = cs; }
};

class BookingSystem {
private:
    vector<Taxi> taxis;
    int bookingId = 1;

public:
    BookingSystem(int taxiCount) {
        for (int i = 1; i <= taxiCount; i++) {
            taxis.push_back(Taxi(i));
        }
    }

    int calculateCharges(char pickUp, char drop) {
        int distanceUnits = abs(pickUp - drop);
        int distance = distanceUnits * 15;

        int charges = 100; // base
        distance -= 5;     // first 5 km free

        if (distance > 0) charges += distance * 10;

        return charges;
    }

    Taxi* findTaxi(char pickUp, int pickTime) {
        vector<Taxi*> freeTaxis;

        for (auto &t : taxis) {
            if (t.isFree(pickUp, pickTime)) {
                freeTaxis.push_back(&t);
            }
        }

        if (freeTaxis.empty()) return nullptr;

        int minDist = INT_MAX;

        for (auto t : freeTaxis) {
            minDist = min(minDist, abs(pickUp - t->getCurrSpot()));
        }

        vector<Taxi*> closest;

        for (auto t : freeTaxis) {
            if (abs(pickUp - t->getCurrSpot()) == minDist) {
                closest.push_back(t);
            }
        }

        Taxi* selected = closest[0];

        for (auto t : closest) {
            if (t->getEarnings() < selected->getEarnings())
                selected = t;
        }

        return selected;
    }

    void bookTaxi(Customer c) {
        Taxi* selected = findTaxi(c.getPickUp(), c.getPickUpTime());

        if (selected == nullptr) {
            cout << "No taxi available\n";
            return;
        }

        int travelTime = abs(c.getPickUp() - c.getDrop());
        int dropTime = c.getPickUpTime() + travelTime;

        int charges = calculateCharges(c.getPickUp(), c.getDrop());

        Booking booking(bookingId++, dropTime, charges, c);

        selected->assignBooking(booking);
        selected->setFreeTime(dropTime);
		selected->setEarnings(selected->getEarnings() + charges);
		selected->setCurrSpot(c.getDrop());
        cout << "Taxi " << selected->getTaxiId() << " allocated\n";
    }

	void displayEarnings() {
		for (auto &t : taxis) {
			cout << "Taxi ID: " << t.getTaxiId() << ", Earnings: " << t.getEarnings() << "\n";
			cout << "Bookings:\n";
			for(auto &b : t.getBookings()){
				cout<< "  Booking ID: " << b.getBookingId()
				     << ", Customer ID: " << b.getCustomerId() 
				     << ", From: " << b.getPickUp()
				     << ", To: " << b.getDrop()
				     << ", Pickup Time: " << b.getPickUpTime()
				     << ", Drop Time: " << b.getDropTime()
				     << ", Amount: " << b.getAmount() << "\n";
			}
		}
	}
};

int main() {
    Customer c1(1, 'A', 'B', 9);
    Customer c2(2, 'B', 'D', 9);
    Customer c3(3, 'B', 'C', 12);

    BookingSystem bs(4);

    bs.bookTaxi(c1);
    bs.bookTaxi(c2);
    bs.bookTaxi(c3);

	bs.displayEarnings();

    return 0;
}
