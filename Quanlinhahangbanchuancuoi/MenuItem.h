#pragma once

#include <iostream>
#include <string>

using namespace std;

/*
    MenuItem là lớp trừu tượng (abstract) — có phương thức ảo thuần túy:
      virtual void display() const = 0;
      virtual MenuItem* clone() const = 0;
    => Đây là KẾ THỪA TRỪU TƯỢNG + ĐA HÌNH (polymorphism):
       - Lớp con (Food, Drink) kế thừa MenuItem và triển khai display()/clone().
       - Ở runtime ta gọi menu[i]->display() và sẽ thực thi hàm display() tương ứng theo kiểu thực tế (Food/Drink).
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
};

