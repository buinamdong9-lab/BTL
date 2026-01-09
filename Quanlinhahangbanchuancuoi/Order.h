#ifndef ORDERITEM_H
#define ORDERITEM_H

#include "MenuItem.h"

class OrderItem {
private:
    MenuItem* item;
    int quantity;

public:
    OrderItem();
	OrderItem(MenuItem* _item, int _quantity); // Khởi tạo với con trỏ đến MenuItem và số lượng món hàng

	MenuItem* getItem() const; // Lấy con trỏ đến MenuItem được đặt hàng 
	int getQuantity() const; // Lấy số lượng món hàng được đặt

	void setItem(MenuItem* _item); // Đặt con trỏ đến MenuItem được đặt hàng
	void setQuantity(int q); // Đặt số lượng món hàng được đặt 

	double getTotal() const; // Tính tổng tiền của món hàng (giá * số lượng)
	void display() const;	// Hiển thị thông tin món hàng được đặt
};

#endif // ORDERITEM_H
