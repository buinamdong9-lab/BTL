#include "MenuItem.h"
#include <iostream>
#include <iomanip>
using namespace std;

MenuItem::MenuItem()
    : id(0), name(""), price(0.0), category(""), stock(0) {
}

MenuItem::MenuItem(int _id, 
    const string& _name,
    double _price,
    const string& _category,
    int _stock)
    : id(_id), name(_name), price(_price),
    category(_category), stock(_stock) {
}

MenuItem::~MenuItem() {}

int MenuItem::getID() const { return id; }
string MenuItem::getName() const { return name; }
double MenuItem::getPrice() const { return price; }
string MenuItem::getCategory() const { return category; }
int MenuItem::getStock() const { return stock; }

void MenuItem::setName(const string& _name) { name = _name; }

void MenuItem::setPrice(double _price) {
    if (_price >= 0) price = _price;
}

void MenuItem::setCategory(const string& _category) {
    category = _category;
}

void MenuItem::setStock(int _stock) {
    if (_stock < 0) _stock = 0;
    stock = _stock;
}

bool MenuItem::isAvailable() const {
    return stock > 0;
}

void MenuItem::reduceStock(int quantity) {
    if (quantity <= 0) return;
    stock -= quantity;
    if (stock < 0) stock = 0;
}

void MenuItem::restock(int quantity) {
    if (quantity <= 0) return;
    stock += quantity;
}

// Triển khai operator<< cho MenuItem: in các trường cơ bản.
// Lưu ý: hàm này không gọi display() vì display() xuất ra cout trực tiếp.
// operator<< in định dạng ngắn gọn vào ostream được cung cấp.
std::ostream& operator<<(std::ostream& os, const MenuItem& m) {
    os << left
       << setw(6) << m.id
       << setw(30) << m.name
       << setw(10) << m.price
       << setw(8) << m.stock
       << setw(12) << m.category;
    return os;
}