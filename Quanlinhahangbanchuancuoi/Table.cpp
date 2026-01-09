#include "Table.h"
using namespace std;

Table::Table()
    : id(0), status(EMPTY), capacity(0) {
}

Table::Table(int _id, int _capacity)
    : id(_id), status(EMPTY), capacity(_capacity) {
}

// ===== GETTERS =====
int Table::getID() const { return id; }
TableStatus Table::getStatus() const { return status; }
int Table::getCapacity() const { return capacity; }

// ===== SETTERS =====
void Table::setStatus(TableStatus s) { status = s; }

void Table::setCapacity(int c) {
    if (c < 0) c = 0;
    capacity = c;
}

// ===== MARK STATUS =====
void Table::markWaiting() { status = WAITING; }
void Table::markOccupied() { status = OCCUPIED; }
void Table::markEmpty() { status = EMPTY; }

// ===== DISPLAY =====
void Table::display() const {
    cout << "Ban: " << id
        << " | Suc chua: " << capacity
        << " | Trang thai: ";
    switch (status) {
    case EMPTY:    cout << "Trong"; break;
    case WAITING:  cout << "Cho phuc vu"; break;
    case OCCUPIED: cout << "Dang su dung"; break;
    default:       cout << "Khong xac dinh"; break;
    }
    cout << endl;
}
