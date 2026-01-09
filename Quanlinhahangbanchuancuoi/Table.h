#ifndef TABLE_H
#define TABLE_H

#include "TableStatus.h"
#include <iostream>
#include <ostream>
using namespace std;

/*
    Table: quản lý trạng thái từng bàn.
    Thêm nạp chồng toán tử operator<< để in nhanh thông tin bàn.
    - Đây là ví dụ NẠP CHỒNG TOÁN TỬ (operator overloading).
*/
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

// Định nghĩa inline operator<< trong header để tránh lỗi liên kết
inline std::ostream& operator<<(std::ostream& os, const Table& t) {
    os << "Ban: " << t.getID()
       << " | Suc chua: " << t.getCapacity()
       << " | Trang thai: ";
    switch (t.getStatus()) {
    case EMPTY:    os << "Trong"; break;
    case WAITING:  os << "Cho phuc vu"; break;
    case OCCUPIED: os << "Dang su dung"; break;
    default:       os << "Khong xac dinh"; break;
    }
    os << '\n';
    return os;
}

#endif // TABLE_H
