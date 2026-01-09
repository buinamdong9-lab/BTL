#include "Customer.h"
#include "Bill.h"
#include <iostream>
using namespace std;

// Constructor mặc định
Customer::Customer()
    : id(0), name(""), phone(""),
    totalRevenue(0.0), billCount(0)
{
    for (int i = 0; i < MAX_BILLS_PER_CUSTOMER; ++i)
        historyBills[i] = NULL; // Khởi tạo mảng lưu lịch sử hóa đơn
}

// Constructor với ID, tên và số điện thoại
Customer::Customer(int _id, const string& _name, const string& _phone)
    : id(_id), name(_name), phone(_phone),
    totalRevenue(0.0), billCount(0)
{
    for (int i = 0; i < MAX_BILLS_PER_CUSTOMER; ++i)
        historyBills[i] = NULL;
}

// Getter các thuộc tính
int Customer::getID() const { return id; }
string Customer::getName() const { return name; }
string Customer::getPhone() const { return phone; }
double Customer::getTotalRevenue() const { return totalRevenue; }
int Customer::getBillCount() const { return billCount; }

// Setter tên và số điện thoại
void Customer::setName(const string& _name) { name = _name; }
void Customer::setPhone(const string& _phone) { phone = _phone; }

// Thêm hóa đơn vào lịch sử khách hàng
void Customer::addBill(Bill* bill) {
    if (!bill) return; // Kiểm tra hợp lệ
    if (billCount < MAX_BILLS_PER_CUSTOMER) {
        historyBills[billCount++] = bill; // Thêm hóa đơn
    }
}

// Cập nhật tổng doanh thu của khách hàng
void Customer::updateRevenue(double amount) {
    totalRevenue += amount;
}

// Hiển thị thông tin khách hàng ra màn hình (tiếng Việt)
void Customer::display() const {
    cout << "Khach hang ID : " << id << endl;
    cout << "Ten         : " << name << endl;
    cout << "So dien thoai: " << phone << endl;
    cout << "Tong doanh thu: " << totalRevenue << endl;
    cout << "So hoa don  : " << billCount << endl;
    cout << "-------------------------------------\n";
}
