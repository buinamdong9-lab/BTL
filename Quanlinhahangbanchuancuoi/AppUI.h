#pragma once

#include "Restaurant.h"

// Helper functions
void clearInput();
void pauseScreen();
void printMainMenu();

// Menu / UI operations
void menuAddItemsToBill(Restaurant& res);
void menuLoadMenu(Restaurant& res);
void menuShowMenu(Restaurant& res);
void menuShowMenuStock(Restaurant& res);
void menuAddMenuItem(Restaurant& res);
void menuUpdateMenuItem(Restaurant& res);
void menuRemoveMenuItem(Restaurant& res);
void menuFindMenuItem(Restaurant& res);

void menuAddTable(Restaurant& res);
void menuShowTables(Restaurant& res);

void menuAddCustomer(Restaurant& res);
void menuShowCustomers(Restaurant& res);

void menuCreateBill(Restaurant& res);
void menuPayBill(Restaurant& res);
void menuShowAllBills(Restaurant& res);

void menuShowStatistics(Restaurant& res);