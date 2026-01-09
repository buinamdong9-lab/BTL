#include "AppUI.h"
#include <iostream>
#include <string>
#include <limits>
#include "Food.h"
#include "Drink.h"

using namespace std;

// ==== HÀM HỖ TRỢ ==== //
void clearInput() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pauseScreen() {
    cout << "\nNhan ENTER de tiep tuc...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ---- Nghiệp vụ: Gọi món cho bill chưa thanh toán ----
void menuAddItemsToBill(Restaurant& res) {
    // (move implementation from your original file here unchanged)
    int billID;
    cout << "Nhap ID hoa don (chua thanh toan): ";
    cin >> billID;
    clearInput();

    Bill* bill = res.findBillByID(billID);
    if (!bill) {
        cout << "Khong tim thay hoa don.\n";
        return;
    }
    if (bill->isPaid()) {
        cout << "Hoa don da duoc thanh toan, khong the goi mon.\n";
        return;
    }

    while (true) {
        int itemID;
        cout << "Nhap ID mon (0 de ket thuc): ";
        cin >> itemID;
        if (itemID == 0) { clearInput(); break; }

        MenuItem* item = res.findMenuItemByID(itemID);
        if (!item) {
            cout << "Khong tim thay mon.\n";
            continue;
        }

        int quantity;
        cout << "Nhap so luong: ";
        cin >> quantity;
        clearInput();

        if (!bill->addItem(item, quantity))
            cout << "Khong the them mon (qua gioi han/so luong khong hop le).\n";
        else
            cout << "Da them mon vao hoa don.\n";
    }
}

// ==== CHUC NANG MENU ==== //
void menuLoadMenu(Restaurant& res) {
    string filename;
    cout << "Nhap ten file menu (mac dinh: menu.txt): ";
    getline(cin, filename);
    if (filename.empty()) filename = "menu.txt";

    if (res.loadMenuFromFile(filename))
        cout << "Da tai menu thanh cong.\n";
    else
        cout << "Khong the tai menu.\n";
}

void menuShowMenu(Restaurant& res) { res.showMenu(); }
void menuShowMenuStock(Restaurant& res) { res.showMenuStock(); }

void menuAddMenuItem(Restaurant& res) {
    // (move implementation unchanged)
    int typeChoice;
    cout << "Them mon vao menu:\n";
    cout << "1. Mon an\n";
    cout << "2. Do uong\n";
    cout << "Lua chon: ";
    cin >> typeChoice;
    clearInput();

    int id, stock;
    double price;
    string name;

    cout << "Nhap ID: ";
    cin >> id;
    clearInput();

    cout << "Nhap ten mon: ";
    getline(cin, name);

    cout << "Nhap gia: ";
    cin >> price;

    cout << "Nhap so luong con: ";
    cin >> stock;
    clearInput();

    MenuItem* item = NULL;

    if (typeChoice == 1) {
        string dishType;
        int servingSize;

        cout << "Nhap loai mon (khai vi/chinh/trang mieng/...): ";
        getline(cin, dishType);

        cout << "Nhap khoi luong phuc vu (gram): ";
        cin >> servingSize;

        item = new Food(id, name, price, stock, dishType, servingSize);
    }
    else if (typeChoice == 2) {
        string beverageType;
        char alcoChar;
        bool isAlcoholic;

        cout << "Nhap loai do uong (nuoc ep/bia/...): ";
        getline(cin, beverageType);

        cout << "Co con khong? (y/n): ";
        cin >> alcoChar;

        isAlcoholic = (alcoChar == 'y' || alcoChar == 'Y');

        item = new Drink(id, name, price, stock, beverageType, isAlcoholic);
    }
    else {
        cout << "Lua chon khong hop le.\n";
        return;
    }

    if (res.addMenuItem(item))
        cout << "Da them mon vao menu.\n";
    else {
        cout << "Khong the them mon.\n";
        delete item;
    }
}

void menuUpdateMenuItem(Restaurant& res) {
    int id;
    cout << "Nhap ID mon can cap nhat: ";
    cin >> id;
    clearInput();

    string newName;
    double newPrice;
    int newStock;

    cout << "Nhap ten moi: ";
    getline(cin, newName);

    cout << "Nhap gia moi: ";
    cin >> newPrice;

    cout << "Nhap so luong con lai moi: ";
    cin >> newStock;
    clearInput();

    if (res.updateMenuItem(id, newName, newPrice, newStock))
        cout << "Cap nhat mon thanh cong.\n";
    else
        cout << "Khong the cap nhat (ID khong ton tai).\n";
}

void menuRemoveMenuItem(Restaurant& res) {
    int id;
    cout << "Nhap ID mon can xoa: ";
    cin >> id;
    clearInput();

    if (res.removeMenuItem(id))
        cout << "Da xoa mon khoi menu.\n";
    else
        cout << "Khong the xoa (ID khong ton tai).\n";
}

void menuFindMenuItem(Restaurant& res) {
    int id;
    cout << "Nhap ID mon can tim: ";
    cin >> id;
    clearInput();

    MenuItem* item = res.findMenuItemByID(id);
    if (item) {
        cout << "Tim thay mon:\n";
        item->display();
    }
    else {
        cout << "Khong tim thay mon.\n";
    }
}

// ==== CHUC NANG BAN ==== //
void menuAddTable(Restaurant& res) {
    int id, capacity;
    cout << "Nhap ID ban: ";
    cin >> id;
    cout << "Nhap suc chua: ";
    cin >> capacity;
    clearInput();

    if (res.createTable(id, capacity))
        cout << "Da them ban.\n";
    else
        cout << "Khong the them ban (da het cho/ID bi trung).\n";
}

void menuShowTables(Restaurant& res) { res.showTables(); }

// ==== CHUC NANG KHACH HANG ==== //
void menuAddCustomer(Restaurant& res) {
    int id;
    string name, phone;

    cout << "Nhap ID khach hang: ";
    cin >> id;
    clearInput();

    cout << "Nhap ten khach hang: ";
    getline(cin, name);

    cout << "Nhap so dien thoai: ";
    getline(cin, phone);

    Customer* c = res.addCustomer(id, name, phone);
    if (c) cout << "Da them khach hang.\n";
    else   cout << "Khong the them khach hang.\n";
}

void menuShowCustomers(Restaurant& res) { res.showCustomers(); }

// ==== CHUC NANG HOA DON ==== //
void menuCreateBill(Restaurant& res) {
    // (move the implementation unchanged)
    int billID;
    cout << "Nhap ID hoa don moi: ";
    cin >> billID;

    int customerID;
    cout << "Nhap ID khach hang: ";
    cin >> customerID;
    clearInput();

    Customer* c = res.findCustomerByID(customerID);
    if (!c) {
        cout << "Khach hang khong ton tai. Them khach hang truoc.\n";
        return;
    }

    Bill* bill = res.createBill(billID, c);

    if (!bill) {
        cout << "Khong the tao hoa don (da dat gioi han).\n";
        return;
    }

    string dt;
    cout << "Nhap ngay/gio (vd: 2025-12-28 19:30): ";
    getline(cin, dt);
    bill->setDateTime(dt);

    while (true) {
        int tableID;
        cout << "Nhap ID ban (0 de ket thuc): ";
        cin >> tableID;
        if (tableID == 0) { clearInput(); break; }

        if (res.assignTableToBill(bill, tableID))
            cout << "Da gan ban " << tableID << " cho hoa don (da dat).\n";
        else
            cout << "Khong the gan ban (ban khong ton tai hoac da duoc su dung).\n";
    }

    while (true) {
        int itemID;
        cout << "Nhap ID mon (0 de ket thuc): ";
        cin >> itemID;
        if (itemID == 0) {
            clearInput();
            break;
        }

        MenuItem* item = res.findMenuItemByID(itemID);
        if (!item) {
            cout << "Khong tim thay mon.\n";
            continue;
        }

        int quantity;
        cout << "Nhap so luong: ";
        cin >> quantity;
        clearInput();

        if (!bill->addItem(item, quantity))
            cout << "Khong the them mon.\n";
        else
            cout << "Da them mon.\n";
    }

    char payNow;
    cout << "Ban co muon thanh toan ngay? (y/n): ";
    cin >> payNow;
    clearInput();
    if (payNow == 'y' || payNow == 'Y') {
        if (res.payBill(bill->getID()))
            cout << "Da thanh toan va luu thong ke.\n";
        else
            cout << "Thanh toan that bai.\n";
    }
    else {
        cout << "Hoa don duoc luu va cho thanh toan sau (ban da dat cac bàn).\n";
    }
}

void menuPayBill(Restaurant& res) {
    int id;
    cout << "Nhap ID hoa don can thanh toan: ";
    cin >> id;
    clearInput();

    if (res.payBill(id))
        cout << "Thanh toan thanh cong.\n";
    else
        cout << "Khong the thanh toan (hoa don khong ton tai hoac da thanh toan).\n";
}

void menuShowAllBills(Restaurant& res) { res.showAllBills(); }

void menuShowStatistics(Restaurant& res) {
    double total = res.getTotalRevenue();
    cout << "Tong doanh thu: " << total << endl;

    Customer* top = res.getTopCustomerByRevenue();
    if (top) {
        cout << "Khach hang co doanh thu cao nhat:\n";
        top->display();
    }
    else {
        cout << "Chua co khach hang nao.\n";
    }
}

void printMainMenu() {
    cout << "\n=========== HE THONG NHA HANG ===========\n";
    cout << "1. Tai menu tu file\n";
    cout << "2. Hien thi menu\n";
    cout << "3. Them mon vao menu\n";
    cout << "4. Cap nhat mon trong menu\n";
    cout << "5. Xoa mon khoi menu\n";
    cout << "6. Tim mon theo ID\n";
    cout << "7. Them khach hang\n";
    cout << "8. Hien thi khach hang\n";
    cout << "9. Tao hoa don\n";
    cout << "10. Hien thi tat ca hoa don (CHUA THANH TOAN)\n";
    cout << "11. Thong ke doanh thu\n";
    cout << "12. Them ban\n";
    cout << "13. Hien thi ban\n";
    cout << "14. Xem ton kho menu\n";
    cout << "15. Thanh toan hoa don\n";
    cout << "16. Goi mon cho hoa don chua thanh toan\n";
    cout << "0. Thoat\n";
    cout << "=========================================\n";
    cout << "Lua chon cua ban: ";
}