#ifndef FOOD_H
#define FOOD_H

#include "MenuItem.h"
#include <string>
using namespace std;

class Food : public MenuItem {
private:
    string dishType;     // appetizer, main course, dessert, ...
    int    servingSize;  // grams

public:
    Food();
    Food(int _id,
        const string& _name,
        double _price,
        int _stock,
        const string& _dishType,
        int _servingSize);

    string getDishType() const;
    int    getServingSize() const;

    void setDishType(const string& _dishType);
    void setServingSize(int _servingSize);

    virtual void display() const override;
    virtual MenuItem* clone() const override;
};

#endif // FOOD_H
