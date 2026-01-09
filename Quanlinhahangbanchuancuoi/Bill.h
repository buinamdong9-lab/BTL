#ifndef BILL_H
#define BILL_H

#include <string>
#include "config.h"
#include "Order.h"
using namespace std;

class Customer;

class Bill {
private:
	int billID;
	string dateTime; // Thời gian tạo hóa đơn
	Customer* customer; // Khách hàng liên kết với hóa đơn

	int tableIDs[MAX_TABLES_PER_BILL];// Mảng lưu trữ ID các bàn
	int tableCount; // Số lượng bàn trong hóa đơn

	OrderItem items[MAX_ORDER_ITEMS];// Mảng lưu trữ các món hàng đã đặt
	int itemCount;// Số lượng món hàng đã đặt

	double taxRate;// Thuế suất áp dụng cho hóa đơn
	double serviceRate;// Phí dịch vụ áp dụng cho hóa đơn

public:
	Bill();
	Bill(int _billID, Customer* _customer);

	int getID() const; // Lấy ID hóa đơn
	string getDateTime() const; // Lấy thời gian tạo hóa đơn
	Customer* getCustomer() const; // Lấy con trỏ đến khách hàng liên kết với hóa đơn
	int getTableCount() const; //   Lấy số lượng bàn trong hóa đơn
	int getItemCount() const; // Lấy số lượng món hàng đã đặt
	int getTableIDAt(int index) const; // Lấy ID bàn theo chỉ số (0..tableCount-1)

	double getTaxRate() const; // Lấy thuế suất áp dụng cho hóa đơn
	double getServiceRate() const; // Lấy phí dịch vụ áp dụng cho hóa đơn

	void setDateTime(const string& dt); // Đặt thời gian tạo hóa đơn
	void setTaxRate(double rate); //	Đặt thuế suất áp dụng cho hóa đơn
	void setServiceRate(double rate);	// Đặt phí dịch vụ áp dụng cho hóa đơn

	bool hasTable(int tableID) const; // Kiểm tra hóa đơn đã chứa bàn này chưa
	bool addTable(int tableID); // Thêm bàn vào hóa đơn (không trùng, kiểm tra phạm vi)
	bool removeTable(int tableID); // Gỡ bàn khỏi hóa đơn
	bool addItem(MenuItem* item, int quantity); // Thêm món hàng vào hóa đơn
	bool updateItemQuantity(int index, int newQuantity); // Cập nhật số lượng món hàng trong hóa đơn
	bool removeItem(int index);// Xóa món hàng khỏi hóa đơn

	double calcSubtotal() const; // Tính tổng tiền trước thuế và phí dịch vụ
	double calcTax() const;// Tính tiền thuế
	double calcServiceFee() const;// Tính phí dịch vụ
	double calcTotal() const;// Tính tổng tiền thanh toán

	void display() const;// Hiển thị thông tin hóa đơn
};

#endif // BILL_H
