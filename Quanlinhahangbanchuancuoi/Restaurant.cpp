#include "Restaurant.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

// ===== CONSTRUCTOR =====

// Khởi tạo mặc định
Restaurant::Restaurant()
    : name(""), menuCount(0), customerCount(0), billCount(0), tableCount(0)
{
    for (int i = 0; i < MAX_MENU_ITEMS; ++i) menu[i] = NULL;
    for (int i = 0; i < MAX_CUSTOMERS; ++i) customers[i] = NULL;
    for (int i = 0; i < MAX_BILLS; ++i) bills[i] = NULL;
    for (int i = 0; i < MAX_TABLES; ++i) tables[i] = NULL;
}

// Khởi tạo với ten nha hang
Restaurant::Restaurant(const string& _name)
    : name(_name), menuCount(0), customerCount(0), billCount(0), tableCount(0)
{
    for (int i = 0; i < MAX_MENU_ITEMS; ++i) menu[i] = NULL;
    for (int i = 0; i < MAX_CUSTOMERS; ++i) customers[i] = NULL;
    for (int i = 0; i < MAX_BILLS; ++i) bills[i] = NULL;
    for (int i = 0; i < MAX_TABLES; ++i) tables[i] = NULL;
}

// HUY CONSTRUCTOR: xoa tat ca doi tuong dong bo nho
Restaurant::~Restaurant() {
    for (int i = 0; i < menuCount; ++i) delete menu[i];
    for (int i = 0; i < customerCount; ++i) delete customers[i];
    for (int i = 0; i < billCount; ++i) delete bills[i];
    for (int i = 0; i < tableCount; ++i) delete tables[i];
}

// ===== TABLES =====

bool Restaurant::createTable(int id, int capacity) {
    if (tableCount >= MAX_TABLES) return false;
    if (findTableByID(id) != NULL) return false; // duplicate id
    tables[tableCount++] = new Table(id, capacity);
    return true;
}

Table* Restaurant::findTableByID(int id) const {
    for (int i = 0; i < tableCount; ++i)
        if (tables[i] && tables[i]->getID() == id)
            return tables[i];
    return NULL;
}

void Restaurant::showTables() const {
    cout << "===== DANH SACH BAN (" << tableCount << ") =====\n";
    for (int i = 0; i < tableCount; ++i)
        if (tables[i]) cout << *tables[i]; // sử dụng operator<<
    cout << "===============================================\n";
}

// Gán bàn vào hóa đơn (nếu bàn tồn tại và đang rảnh)
bool Restaurant::assignTableToBill(Bill* bill, int tableID) {
    if (!bill) return false;
    Table* t = findTableByID(tableID);
    if (!t) return false;
    if (t->getStatus() != EMPTY) return false;
    if (!bill->addTable(tableID)) return false;
    // Khi gán bàn: đánh dấu "Đã đặt" (WAITING)
    t->markWaiting();
    return true;
}

// Giải phóng (set empty) các bàn có trong hóa đơn (gọi khi thanh toán)
void Restaurant::releaseTablesFromBill(Bill* bill) {
    if (!bill) return;
    for (int i = 0; i < bill->getTableCount(); ++i) {
        int tid = bill->getTableIDAt(i);
        Table* t = findTableByID(tid);
        if (t) t->markEmpty();
    }
}

// ===== MENU =====

// Tai menu tu file
bool Restaurant::loadMenuFromFile(const string& filename) {
    ifstream fin(filename.c_str());
    if (!fin.is_open()) {
        cout << "Khong the mo file: " << filename << endl;
        return false;
    }

    // Xoa menu cu
    for (int i = 0; i < menuCount; ++i) {
        delete menu[i];
        menu[i] = NULL;
    }
    menuCount = 0;

    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue; // bo qua dong rong
        stringstream ss(line);
        string token;

        getline(ss, token, ';');
        char type = token.empty() ? ' ' : token[0]; // F = mon an, D = do uong

        getline(ss, token, ';');
        int id = stoi(token);

        getline(ss, token, ';');
        string name = token;

        getline(ss, token, ';');
        double price = stod(token);

        getline(ss, token, ';');
        int stock = stoi(token);

        if (type == 'F') { // Mon an
            string dishType;                    
            int servingSize;
            bool isVegetarian;

            getline(ss, dishType, ';');
            getline(ss, token, ';'); servingSize = stoi(token);
            getline(ss, token, ';'); isVegetarian = (token == "1");

            if (menuCount < MAX_MENU_ITEMS) {
                menu[menuCount++] = new Food(id, name, price, stock,
                    dishType, servingSize);
            }
        }
        else if (type == 'D') { // Do uong
            string beverageType;
            bool isAlcoholic, isHot;

            getline(ss, beverageType, ';');
            getline(ss, token, ';'); isAlcoholic = (token == "1");
            getline(ss, token, ';'); isHot = (token == "1");

            if (menuCount < MAX_MENU_ITEMS) {
                menu[menuCount++] = new Drink(id, name, price, stock,
                    beverageType, isAlcoholic);
            }
        }
    }

    fin.close();
    cout << "Da tai " << menuCount << " mon tu file.\n";
    return true;
}

// Luu menu vao file
bool Restaurant::saveMenuToFile(const string& filename) const {
    ofstream fout(filename.c_str());
    if (!fout.is_open()) {
        cout << "Khong the luu file: " << filename << endl;
        return false;
    }

    for (int i = 0; i < menuCount; ++i) {
        MenuItem* item = menu[i];
        if (!item) continue;

        Food* f = dynamic_cast<Food*>(item);
        Drink* d = dynamic_cast<Drink*>(item);

        if (f) {
            fout << "F;"
                << f->getID() << ";"
                << f->getName() << ";"
                << f->getPrice() << ";"
                << f->getStock() << ";"
                << f->getDishType() << ";"
                << f->getServingSize() << ";"
 
                << "\n";
        }
        else if (d) {
            fout << "D;"
                << d->getID() << ";"
                << d->getName() << ";"
                << d->getPrice() << ";"
                << d->getStock() << ";"
                << d->getBeverageType() << ";"
                << (d->getIsAlcoholic() ? 1 : 0) << ";"
                << "\n";
        }
    }

    fout.close();
    cout << "Da luu menu vao file.\n";
    return true;
}

// Them mon vao menu
bool Restaurant::addMenuItem(MenuItem* item) {
    if (!item) return false;
    if (menuCount >= MAX_MENU_ITEMS) return false;
    menu[menuCount++] = item;
    return true;
}

// Xoa mon theo ID
bool Restaurant::removeMenuItem(int id) {
    for (int i = 0; i < menuCount; ++i) {
        if (menu[i] && menu[i]->getID() == id) {
            delete menu[i];
            for (int j = i; j < menuCount - 1; ++j)
                menu[j] = menu[j + 1];
            menu[menuCount - 1] = NULL;
            --menuCount;
            return true;
        }
    }
    return false;
}

// Tim mon theo ID
MenuItem* Restaurant::findMenuItemByID(int id) const {
    for (int i = 0; i < menuCount; ++i)
        if (menu[i] && menu[i]->getID() == id)
            return menu[i];
    return NULL;
}

// Cap nhat mon theo ID
bool Restaurant::updateMenuItem(int id,
    const string& newName,
    double newPrice,
    int newStock)
{
    MenuItem* item = findMenuItemByID(id);
    if (!item) return false;
    item->setName(newName);
    item->setPrice(newPrice);
    item->setStock(newStock);
    return true;
}

// Hien thi menu
void Restaurant::showMenu() const {
    cout << "===== MENU (" << menuCount << " mon) =====\n";
    cout << left
        << setw(8) << "Loai"
        << setw(6) << "ID"
        << setw(20) << "Ten"
        << setw(10) << "Gia"
        << setw(8) << "Ton"
        << setw(18) << "Loai mon"
        << setw(10) << "Khoi luong|Con|Da"
        << endl;

    cout << string(80, '-') << endl;

    for (int i = 0; i < menuCount; ++i)
        if (menu[i]) menu[i]->display();
    cout << "===========================================\n";
}

// Hien thi tồn kho (ID, Ten, Ton)
void Restaurant::showMenuStock() const {
    cout << "===== TON KHO MENU =====\n";
    cout << left << setw(6) << "ID" << setw(30) << "Ten" << setw(8) << "Ton" << endl;
    cout << string(50, '-') << endl;
    for (int i = 0; i < menuCount; ++i) {
        if (!menu[i]) continue;
        cout << left << setw(6) << menu[i]->getID()
            << setw(30) << menu[i]->getName()
            << setw(8) << menu[i]->getStock()
            << endl;
    }
    cout << "=========================\n";
}

// ===== KHACH HANG =====

// Them khach hang moi
Customer* Restaurant::addCustomer(int id,
    const string& name,
    const string& phone)
{
    if (customerCount >= MAX_CUSTOMERS) return NULL;
    customers[customerCount] = new Customer(id, name, phone);
    return customers[customerCount++];
}

// Tim khach hang theo ID
Customer* Restaurant::findCustomerByID(int id) {
    for (int i = 0; i < customerCount; ++i)
        if (customers[i] && customers[i]->getID() == id)
            return customers[i];
    return NULL;
}

// Hien thi danh sach khach hang
void Restaurant::showCustomers() const {
    cout << "===== DANH SACH KHACH HANG (" << customerCount << ") =====\n";
    for (int i = 0; i < customerCount; ++i)
        if (customers[i]) customers[i]->display();
    cout << "===============================================\n";
}

// ===== HOA DON =====

// Tao hoa don moi
Bill* Restaurant::createBill(int billID, Customer* customer) {
    if (billCount >= MAX_BILLS) return NULL;
    bills[billCount] = new Bill(billID, customer);
    return bills[billCount++];
}

// finalizeBill: cập nhật lịch sử KH (giảm tồn kho) - internal
void Restaurant::finalizeBill(Bill* bill) {
    if (!bill) return;
    if (bill->isPaid()) return;
    // Giảm tồn kho: duyệt các order item trong hóa đơn và giảm stock
    for (int i = 0; i < bill->getItemCount(); ++i) {
        const OrderItem& oi = bill->getOrderItemAt(i);
        MenuItem* mi = oi.getItem();
        if (mi) {
            mi->reduceStock(oi.getQuantity());
        }
    }

    Customer* c = bill->getCustomer();
    if (c) {
        double total = bill->calcTotal();
        c->updateRevenue(total);
        c->addBill(bill);
    }
    // giải phóng bàn sau khi hoàn tất hóa đơn
    releaseTablesFromBill(bill);
    bill->setPaid(true);
}

// Thanh toán hóa đơn theo ID: gọi finalize + ghi file thống kê
bool Restaurant::payBill(int billID) {
    Bill* b = NULL;
    for (int i = 0; i < billCount; ++i) {
        if (bills[i] && bills[i]->getID() == billID) { b = bills[i]; break; }
    }
    if (!b) return false;
    if (b->isPaid()) return false; // đã thanh toán

    // finalize (update customer history + release tables + giảm tồn kho)
    finalizeBill(b);

    // ghi file thống kê (append)
    ofstream fout("statistics.txt", ios::app);
    if (!fout.is_open()) {
        cout << "Khong the mo file statistics.txt de luu thong ke.\n";
        return false;
    }

    // Ghi dưới dạng CSV: billID;dateTime;customerID;customerName;total
    fout << b->getID() << ";"
         << b->getDateTime() << ";";

    Customer* c = b->getCustomer();
    if (c) {
        fout << c->getID() << ";" << c->getName() << ";";
    }
    else {
        fout << "0;Unknown;";
    }

    fout << b->calcTotal() << "\n";
    fout.close();

    return true;
}

// Hien thi tat ca hoa don CHƯA THANH TOÁN (theo yêu cầu)
void Restaurant::showAllBills() const {
    cout << "===== HOA DON CHUA THANH TOAN =====\n";
    bool any = false;
    for (int i = 0; i < billCount; ++i) {
        if (bills[i] && !bills[i]->isPaid()) {
            cout << *bills[i]; // sử dụng operator<<
            any = true;
        }
    }
    if (!any) cout << "Khong co hoa don chua thanh toan.\n";
    cout << "===================================\n";
}

// ===== THONG KE =====

// Tong doanh thu (tổng tất cả các bill — bao gồm đã thanh toán)
double Restaurant::getTotalRevenue() const {
    double sum = 0.0;
    for (int i = 0; i < billCount; ++i)
        if (bills[i]) sum += bills[i]->calcTotal();
    return sum;
}

// Khach hang co doanh thu cao nhat
Customer* Restaurant::getTopCustomerByRevenue() {
    if (customerCount == 0) return NULL;
    Customer* best = customers[0];
    for (int i = 1; i < customerCount; ++i)
        if (customers[i]->getTotalRevenue() > best->getTotalRevenue())
            best = customers[i];
    return best;
}

// Tim hoa don theo ID
Bill* Restaurant::findBillByID(int billID) const {
    for (int i = 0; i < billCount; ++i) {
        if (bills[i] && bills[i]->getID() == billID)
            return bills[i];
    }
    return NULL;
}
