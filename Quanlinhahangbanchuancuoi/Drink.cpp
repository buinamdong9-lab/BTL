#include "Drink.h"
#include <iostream>
#include <iomanip>
using namespace std;

// Constructor mặc định
Drink::Drink()
    : MenuItem(),
    beverageType(""),
    isAlcoholic(false)
{
    category = "Đo uong"; // Chuyển tên loại sang tiếng Việt
}

// Constructor đầy đủ với các thuộc tính
Drink::Drink(int _id,
    const string& _name,
    double _price,
    int _stock,
    const string& _beverageType,
    bool _isAlcoholic)
    : MenuItem(_id, _name, _price, "Đo uong", _stock),
    beverageType(_beverageType),
    isAlcoholic(_isAlcoholic) {
}

// Getter
string Drink::getBeverageType() const { return beverageType; }
bool Drink::getIsAlcoholic() const { return isAlcoholic; }

// Setter
void Drink::setBeverageType(const string& _beverageType) { beverageType = _beverageType; }
void Drink::setIsAlcoholic(bool _isAlcoholic) { isAlcoholic = _isAlcoholic; }

// Hiển thị thông tin đồ uống ra màn hình (tiếng Việt)
void Drink::display() const {
    cout << left
        << setw(8) << "[Drink]"
        << setw(6) << id
        << setw(20) << name
        << setw(10) << price
        << setw(8) << stock
        << setw(18) << beverageType
        << setw(10) << (isAlcoholic ? "Co" : "Khong")
        << endl;
}

// Tạo bản sao đối tượng
MenuItem* Drink::clone() const {
    return new Drink(*this);
}
