#include "Bill.h"
#include "Customer.h"
#include <iostream>
using namespace std;

// Constructor mặc định
Bill::Bill()
    : billID(0), dateTime(""), customer(NULL),
    tableCount(0), itemCount(0),
    taxRate(0.08), serviceRate(0.05)
{
    for (int i = 0; i < MAX_TABLES_PER_BILL; ++i)
        tableIDs[i] = -1; // Khởi tạo mảng bàn với giá trị -1
}

// Constructor với ID hóa đơn và khách hàng
Bill::Bill(int _billID, Customer* _customer)
    : billID(_billID), dateTime(""), customer(_customer),
    tableCount(0), itemCount(0),
    taxRate(0.08), serviceRate(0.05)
{
    for (int i = 0; i < MAX_TABLES_PER_BILL; ++i)
        tableIDs[i] = -1;
}

// Getter các thuộc tính
int Bill::getID() const { return billID; }
string Bill::getDateTime() const { return dateTime; }
Customer* Bill::getCustomer() const { return customer; }
int Bill::getTableCount() const { return tableCount; }
int Bill::getItemCount() const { return itemCount; }
int Bill::getTableIDAt(int index) const {
    if (index < 0 || index >= tableCount) return -1;
    return tableIDs[index];
}
double Bill::getTaxRate() const { return taxRate; }
double Bill::getServiceRate() const { return serviceRate; }

// Setter ngày giờ
void Bill::setDateTime(const string& dt) { dateTime = dt; }

// Setter thuế (không âm)
void Bill::setTaxRate(double rate) {
    if (rate < 0) rate = 0;
    taxRate = rate;
}

// Setter phí dịch vụ (không âm)
void Bill::setServiceRate(double rate) {
    if (rate < 0) rate = 0;
    serviceRate = rate;
}

// Kiểm tra bàn đã có trong hóa đơn chưa
bool Bill::hasTable(int tableID) const {
    for (int i = 0; i < tableCount; ++i) {
        if (tableIDs[i] == tableID) return true;
    }
    return false;
}

// Thêm bàn vào hóa đơn (không trùng, kiểm tra phạm vi)
bool Bill::addTable(int tableID) {
    if (tableID <= 0 || tableID > MAX_TABLES) return false; // ID bàn không hợp lệ
    if (tableCount >= MAX_TABLES_PER_BILL) return false; // Quá số bàn tối đa
    if (hasTable(tableID)) return false; // Trùng bàn

    tableIDs[tableCount++] = tableID;
    return true;
}

// Gỡ bàn khỏi hóa đơn
bool Bill::removeTable(int tableID) {
    int idx = -1;
    for (int i = 0; i < tableCount; ++i) {
        if (tableIDs[i] == tableID) { idx = i; break; }
    }
    if (idx == -1) return false;
    for (int i = idx; i < tableCount - 1; ++i) {
        tableIDs[i] = tableIDs[i + 1];
    }
    tableIDs[tableCount - 1] = -1;
    --tableCount;
    return true;
}

// Thêm món vào hóa đơn
bool Bill::addItem(MenuItem* item, int quantity) {
    if (!item) return false; // Món không hợp lệ
    if (itemCount >= MAX_ORDER_ITEMS) return false; // Quá số món tối đa
    if (quantity <= 0) return false; // Số lượng không hợp lệ

    items[itemCount++] = OrderItem(item, quantity);
    return true;
}

// Cập nhật số lượng món
bool Bill::updateItemQuantity(int index, int newQuantity) {
    if (index < 0 || index >= itemCount) return false;
    if (newQuantity < 0) newQuantity = 0;
    items[index].setQuantity(newQuantity);
    return true;
}

// Xóa món theo chỉ số
bool Bill::removeItem(int index) {
    if (index < 0 || index >= itemCount) return false;
    for (int i = index; i < itemCount - 1; ++i)
        items[i] = items[i + 1]; // Dời các món phía sau lên
    --itemCount;
    return true;
}

// Tính tổng tiền chưa thuế và dịch vụ
double Bill::calcSubtotal() const {
    double sum = 0.0;
    for (int i = 0; i < itemCount; ++i)
        sum += items[i].getTotal();
    return sum;
}

// Tính thuế
double Bill::calcTax() const { return calcSubtotal() * taxRate; }

// Tính phí dịch vụ
double Bill::calcServiceFee() const { return calcSubtotal() * serviceRate; }

// Tính tổng tiền phải thanh toán
double Bill::calcTotal() const {
    return calcSubtotal() + calcTax() + calcServiceFee();
}

// Hiển thị hóa đơn ra màn hình (tiếng Việt)
void Bill::display() const {
    cout << "================= HOA DON =================\n";
    cout << "Ma HĐ      : " << billID << endl;
    cout << "Ngay/Gio   : " << dateTime << endl;

    if (customer) {
        cout << "Khach hang : " << customer->getName()
            << " | SĐT: " << customer->getPhone() << endl;
    }

    cout << "Ban        : ";
    for (int i = 0; i < tableCount; ++i) {
        cout << tableIDs[i];
        if (i < tableCount - 1) cout << ", ";
    }
    cout << "\n-------------------------------------------\n";

    cout << "Mon Hang:\n";
    for (int i = 0; i < itemCount; ++i)
        items[i].display(); // Gọi hàm hiển thị của từng OrderItem

    cout << "-------------------------------------------\n";
    double subtotal = calcSubtotal();
    double tax = calcTax();
    double service = calcServiceFee();
    double total = calcTotal();

    cout << "Tam Tinh  : " << subtotal << endl;
    cout << "Thue      : " << tax << endl;
    cout << "Phi DV    : " << service << endl;
    cout << "TONG CONG : " << total << endl;
    cout << "===========================================\n";
}
