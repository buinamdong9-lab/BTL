#ifndef DRINK_H
#define DRINK_H

#include "MenuItem.h"
#include <string>
using namespace std;

class Drink : public MenuItem {
private:
    string beverageType; // soft drink, juice, beer, coffee, ...
    bool   isAlcoholic;  // true = alcoholic

public:
    Drink();
    Drink(int _id,
        const string& _name,
        double _price,
        int _stock,
        const string& _beverageType,
        bool _isAlcoholic);

    string getBeverageType() const;
    bool   getIsAlcoholic() const;

    void setBeverageType(const string& _beverageType);
    void setIsAlcoholic(bool _isAlcoholic);

    virtual void display() const override;
    virtual MenuItem* clone() const override;
};

#endif // DRINK_H
