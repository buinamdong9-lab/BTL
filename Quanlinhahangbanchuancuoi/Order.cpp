#include "Order.h"
#include <iostream>
using namespace std;

OrderItem::OrderItem() : item(NULL), quantity(0) {}

OrderItem::OrderItem(MenuItem* _item, int _quantity): item(_item), quantity(_quantity){}

MenuItem* OrderItem::getItem() const {
	return item;
}

int OrderItem::getQuantity() const {
	return quantity;
}

void OrderItem::setItem(MenuItem* _item) {
	item = _item;
}

void OrderItem::setQuantity(int q) {
	quantity = q;
}

double OrderItem :: getTotal() const 
{
	if (!item)
	{
		return 0.0;
	}

	return item->getPrice() * quantity;
}

void OrderItem::display() const //Hiển thị thông tin món hàng được đặt tren 1 dòng ten x so luong = tong tien
{
	if (!item)
	{
		cout << "Khong co order!\n" << endl;
		return;
	}
	cout << " - " << item->getName()
		 << " x " << quantity
		 << " = " << getTotal() << endl;
}
