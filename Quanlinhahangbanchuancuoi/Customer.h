#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include "config.h"
using namespace std;

class Bill; // forward declaration

class Customer {
private:
    int id;
    string name;
    string phone;
    double totalRevenue;
    Bill* historyBills[MAX_BILLS_PER_CUSTOMER];
    int billCount;

public:
    Customer();
    Customer(int _id, const string& _name, const string& _phone);

    int getID() const;
    string getName() const;
    string getPhone() const;
    double getTotalRevenue() const;
    int getBillCount() const;

    void setName(const string& _name);
    void setPhone(const string& _phone);

    void addBill(Bill* bill);
    void updateRevenue(double amount);

    void display() const;
};

#endif // CUSTOMER_H
