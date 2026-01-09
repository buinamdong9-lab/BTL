#include "Food.h"
#include <iostream>
#include <iomanip>
using namespace std;

// Constructor mặc định
Food::Food()
    : MenuItem(),
    dishType(""),
    servingSize(0)
{
    category = "Mon an"; // Chuyển category sang tiếng Việt
}

// Constructor đầy đủ với các thuộc tính
Food::Food(int _id,
    const string& _name,
    double _price,
    int _stock,
    const string& _dishType,
    int _servingSize)
    : MenuItem(_id, _name, _price, "Mon an", _stock),
    dishType(_dishType),
    servingSize(_servingSize) {
}

// Getter
string Food::getDishType() const { return dishType; }
int Food::getServingSize() const { return servingSize; }

// Setter
void Food::setDishType(const string& _dishType) { dishType = _dishType; }

void Food::setServingSize(int _servingSize) {
    if (_servingSize < 0) _servingSize = 0; // Không cho âm
    servingSize = _servingSize;
}

// Hiển thị thông tin món ăn ra màn hình (tiếng Việt)
#include <iomanip>

void Food::display() const {
    cout << left
        << setw(8) << "[Food]"
        << setw(6) << id
        << setw(20) << name
        << setw(10) << price
        << setw(8) << stock
        << setw(18) << dishType
        << setw(10) << (to_string(servingSize) + "g")
        << endl;
}

// Tạo bản sao đối tượng
MenuItem* Food::clone() const {
    return new Food(*this);
}
