#include <iostream>
#include <string>
#include <limits>
#include "Restaurant.h"
using namespace std;

// ==== HÀM HỖ TRỢ ==== //

// Xoa bo du lieu thua trong cin sau khi nhap
void clearInput() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Tam dung man hinh cho nguoi dung nhan ENTER
void pauseScreen() {
    cout << "\nNhan ENTER de tiep tuc...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ==== CHUC NANG MENU ==== //

// Tai menu tu file
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

// Hien thi tat ca cac mon trong menu
void menuShowMenu(Restaurant& res) {
    res.showMenu();
}

// Xem tồn kho menu
void menuShowMenuStock(Restaurant& res) {
    res.showMenuStock();
}

// Them mon moi vao menu
void menuAddMenuItem(Restaurant& res) {
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

    // Nhap thong tin chung
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

    if (typeChoice == 1) { // Mon an
        string dishType;
        int servingSize;

        cout << "Nhap loai mon (khai vi/chinh/trang mieng/...): ";
        getline(cin, dishType);

        cout << "Nhap khoi luong phuc vu (gram): ";
        cin >> servingSize;

        // Tao mon an moi
        item = new Food(id, name, price, stock,
            dishType, servingSize);
    }
    else if (typeChoice == 2) { // Do uong
        string beverageType;
        char alcoChar;
        bool isAlcoholic;

        cout << "Nhap loai do uong (nuoc ep/bia/...): ";
        getline(cin, beverageType);

        cout << "Co con khong? (y/n): ";
        cin >> alcoChar;

        isAlcoholic = (alcoChar == 'y' || alcoChar == 'Y');

        // Tao do uong moi
        item = new Drink(id, name, price, stock,
            beverageType, isAlcoholic);
    }
    else {
        cout << "Lua chon khong hop le.\n";
        return;
    }

    // Them vao menu cua nha hang
    if (res.addMenuItem(item))
        cout << "Da them mon vao menu.\n";
    else {
        cout << "Khong the them mon.\n";
        delete item;
    }
}

// Cap nhat thong tin mon trong menu
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

// Xoa mon khoi menu
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

// Tim mon theo ID
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

void menuShowTables(Restaurant& res) {
    res.showTables();
}

// ==== CHUC NANG KHACH HANG ==== //

// Them khach hang moi
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

// Hien thi danh sach khach hang
void menuShowCustomers(Restaurant& res) {
    res.showCustomers();
}

// ==== CHUC NANG HOA DON ==== //

// Tao hoa don moi
void menuCreateBill(Restaurant& res) {
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

    // Them ban vao hoa don
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

    // Them mon vao hoa don
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

    // Hỏi có thanh toán ngay không
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

// Thanh toán hóa đơn (từ menu, theo ID)
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

// Hien thi tat ca hoa don
void menuShowAllBills(Restaurant& res) {
    res.showAllBills();
}

// ==== THONG KE ==== //

// Hien thi tong doanh thu va khach hang co doanh thu cao nhat
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

// ==== MENU CHINH ==== //
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
    cout << "0. Thoat\n";
    cout << "=========================================\n";
    cout << "Lua chon cua ban: ";
}

// ==== HAM MAIN ==== //
int main() {
    Restaurant res("Nha hang cua toi");

    // Tạo sẵn 10 bàn (1..10), mỗi bàn 10 người
    for (int i = 1; i <= 10; ++i) {
        res.createTable(i, 10);
    }

    int choice = -1;
    do {
        printMainMenu();
        if (!(cin >> choice)) {
            cin.clear();
            clearInput();
            cout << "Nhap khong hop le. Vui long nhap so.\n";
            continue;
        }
        clearInput();

        switch (choice) {
        case 1: menuLoadMenu(res);        pauseScreen(); break;
        case 2: menuShowMenu(res);        pauseScreen(); break;
        case 3: menuAddMenuItem(res);     pauseScreen(); break;
        case 4: menuUpdateMenuItem(res);  pauseScreen(); break;
        case 5: menuRemoveMenuItem(res);  pauseScreen(); break;
        case 6: menuFindMenuItem(res);    pauseScreen(); break;
        case 7: menuAddCustomer(res);     pauseScreen(); break;
        case 8: menuShowCustomers(res);   pauseScreen(); break;
        case 9: menuCreateBill(res);      pauseScreen(); break;
        case 10:menuShowAllBills(res);    pauseScreen(); break;
        case 11: menuShowStatistics(res); pauseScreen(); break;
        case 12: menuAddTable(res);       pauseScreen(); break;
        case 13: menuShowTables(res);     pauseScreen(); break;
        case 14: menuShowMenuStock(res);  pauseScreen(); break;
        case 15: menuPayBill(res);        pauseScreen(); break;
        case 0: cout << "Dang thoat...\n"; break;
        default:
            cout << "Lua chon khong hop le.\n";
            pauseScreen();
            break;
        }

    } while (choice != 0);

    return 0;
}
