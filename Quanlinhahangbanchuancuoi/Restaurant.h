#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <string>
#include "config.h"
#include "MenuItem.h"
#include "Food.h"
#include "Drink.h"
#include "Customer.h"
#include "Bill.h"
#include "Table.h"
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

    Table* tables[MAX_TABLES];
    int tableCount;

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
    void showMenuStock() const;

    // CUSTOMER
    Customer* addCustomer(int id,
        const string& name,
        const string& phone);
    Customer* findCustomerByID(int id);
    void showCustomers() const;

    // BILL
    Bill* createBill(int billID, Customer* customer); // lưu luôn vào mảng
    void finalizeBill(Bill* bill);                    // internal: cập nhật lịch sử (không tự động gọi trên tạo)
    bool payBill(int billID);                         // thanh toán: finalize + ghi file thống kê

    // Tìm bill theo ID (dùng cho nghiệp vụ gọi món cho bill chưa thanh toán)
    Bill* findBillByID(int billID) const;

    // Hiển thị: chỉ hiện các bill chưa thanh toán theo yêu cầu
    void showAllBills() const;

    // TABLES
    bool createTable(int id, int capacity);
    Table* findTableByID(int id) const;
    void showTables() const;
    bool assignTableToBill(Bill* bill, int tableID);
    void releaseTablesFromBill(Bill* bill);

    // STATISTICS
    double getTotalRevenue() const;
    Customer* getTopCustomerByRevenue();
};

#endif // RESTAURANT_H
