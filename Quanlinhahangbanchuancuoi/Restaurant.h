#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <string>
#include "config.h"
#include "MenuItem.h"
#include "Food.h"
#include "Drink.h"
#include "Customer.h"
#include "Bill.h"
using namespace std;

class Restaurant {
private:
    string name;

    MenuItem* menu[MAX_MENU_ITEMS];
    int menuCount;

    Customer* customers[MAX_CUSTOMERS];
    int customerCount;

    Bill* bills[MAX_BILLS];
    int billCount;

public:
    Restaurant();
    Restaurant(const string& _name);
    ~Restaurant();

    // MENU
    bool loadMenuFromFile(const string& filename);
    bool saveMenuToFile(const string& filename) const;

    bool addMenuItem(MenuItem* item);
    bool removeMenuItem(int id);
    MenuItem* findMenuItemByID(int id) const;
    bool updateMenuItem(int id,
        const string& newName,
        double newPrice,
        int newStock);

    void showMenu() const;

    // CUSTOMER
    Customer* addCustomer(int id,
        const string& name,
        const string& phone);
    Customer* findCustomerByID(int id);
    void showCustomers() const;

    // BILL
    Bill* createBill(int billID, Customer* customer); // lưu luôn vào mảng
    void finalizeBill(Bill* bill);                    // cập nhật doanh thu + history

    void showAllBills() const;

    // STATISTICS
    double getTotalRevenue() const;
    Customer* getTopCustomerByRevenue();
};

#endif // RESTAURANT_H
