#include <iostream>
#include "Restaurant.h"
#include "AppUI.h"

using namespace std;

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
        case 16: menuAddItemsToBill(res); pauseScreen(); break;
        case 0: cout << "Dang thoat...\n"; break;
        default:
            cout << "Lua chon khong hop le.\n";
            pauseScreen();
            break;
        }

    } while (choice != 0);
//dongbuitest   
    return 0;
}
