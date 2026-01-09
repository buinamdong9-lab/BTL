#ifndef TABLE_H
#define TABLE_H

#include "TableStatus.h"
#include <iostream>
using namespace std;

class Table {
private:
    int id;
    TableStatus status;
    int capacity;

public:
    Table();
    Table(int _id, int _capacity);

    int getID() const;
    TableStatus getStatus() const;
    int getCapacity() const;

    void setStatus(TableStatus s);
    void setCapacity(int c);

    void markWaiting();
    void markOccupied();
    void markEmpty();

    void display() const;
};

#endif // TABLE_H
