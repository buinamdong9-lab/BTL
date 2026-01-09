#pragma once

#include <iostream>
#include <string>

using namespace std;

/*
    MenuItem là lớp trừu tượng (abstract):
    - Có hàm ảo thuần túy `display()` và `clone()` => lớp con (Food, Drink) phải triển khai.
    - Đây là KẾ THỪA TRỪU TƯỢNG và ĐA HÌNH: khi lưu trữ con trỏ loại MenuItem*,
      gọi menu[i]->display() sẽ thực thi hàm tương ứng của lớp con (polymorphism).
*/
class MenuItem {
protected:
    int id;
    string name;
    double price;
    int stock;
    string category;
        
public:
    MenuItem();
    MenuItem(int _id,
        const string& _name,
        double _price,
        const string& _category,
        int _stock);
    virtual ~MenuItem();

    int getID() const;
    string getName() const;
    double getPrice() const;
    string getCategory() const;
    int getStock() const;

    void setName(const string& _name);
    void setPrice(double _price);
    void setCategory(const string& _category);
    void setStock(int _stock);

    bool isAvailable() const;
    void reduceStock(int quantity); 
    void restock(int quantity);

    // Hàm ảo thuần túy => lớp này là abstract
    virtual void display() const = 0;
    virtual MenuItem* clone() const = 0;

    // Nạp chồng toán tử: in thông tin ngắn gọn của MenuItem
    // Đây là ví dụ OPERATOR OVERLOADING -> định nghĩa ngoài lớp (free function)
    friend std::ostream& operator<<(std::ostream& os, const MenuItem& m);

    // Nạp chồng toán tử so sánh (theo id)
    bool operator==(const MenuItem& other) const { return id == other.id; }
};

