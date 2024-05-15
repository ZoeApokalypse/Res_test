//
// Created by Zoe Apokalypse on 2022/4/10.
//

#ifndef RES_TEST_WIN_INORDER_H
#define RES_TEST_WIN_INORDER_H

#include "WIN_Menu.h"
#include "WIN_CustomerData.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

static int inid = 1000;
static int tablenumber = 100;
int Outid;

class WIN_InOrder : public WIN_Menu {
private:
    int id_win[LENGTH_win] = {0};
    string name_win[LENGTH_win];
    double price_win[LENGTH_win];
    int count_win[LENGTH_win];
    int DishID_win[LENGTH_win];
    double totalprice_win = 0;
    int N_win = 0;
    int year_win;
    int month_win;
    int day_win;

public:
    WIN_InOrder(Date* d);
    void order_win();
    void print_win();
};

WIN_InOrder::WIN_InOrder(Date* d) {
    WIN_Menu* M = new WIN_Menu();
    string orderFile = M->ADDRESS_win(7);
    inid++;
    year_win = d->get_year();
    month_win = d->get_month();
    day_win = d->get_day();

    ifstream inFile(orderFile);
    int x, y, z, m;
    inFile >> x >> y >> z >> m >> Outid;
    if (x == year_win && y == month_win && z == day_win) {
        inid = m + 1;
    } else {
        Outid = 2000;
    }
    inFile.close();
}

void WIN_InOrder::order_win() {
    ofstream outFile("orderid.txt");
    outFile << year_win << '\n' << month_win << '\n' << day_win << '\n' << inid << '\n' << Outid;
    outFile.close();

    WIN_Menu* menu = new WIN_Menu();
    menu->MENU_win();

    int dishNum;
    cout << "Please enter the dish number you want to order.\nEnter 0 to exit\n";
    cin >> dishNum;

    while (dishNum != 0) {
        if (dishNum > 0 && dishNum < LENGTH_win) {
            cout << "Please enter the quantity you want to order\n";
            cin >> count_win[N_win];
            id_win[N_win] = menu->id_win[dishNum - 1];
            name_win[N_win] = menu->name_win[dishNum - 1];
            if (discount_win <= 10)
                price_win[N_win] = menu->price_win[dishNum - 1] * discount_win / 10;
            else
                price_win[N_win] = menu->price_win[dishNum - 1] * discount_win / 100;

            totalprice_win += price_win[N_win] * count_win[N_win];
            DishID_win[N_win++] = dishNum;

            cout << "Please enter the dish number you want to order.\nEnter 0 to exit\n";
            cin >> dishNum;
        } else {
            cout << "The number you entered does not exist! :(\nPlease re-enter\n\n";
            cin >> dishNum;
        }
    }
    print_win();
}

void WIN_InOrder::print_win() {
    WIN_Menu* menu = new WIN_Menu();
    string address = menu->ADDRESS_win(6);

    cout << "Your order ID is: " << inid << endl;
    cout << "Your consumption mode is: In store\n";
    cout << "Your table ID is: " << ++tablenumber << endl;
    cout << "Your table fee is: 2¥\n";
    cout << "Our discount today is: " << discount_win << "%\n";
    cout << "Your order is as follows: \n\n";

    cout << "Number\tName\t\t\tPrice\tCount\tTotal\n";
    cout << "--------------------------------------------------------------\n";

    for (int i = 0; i < N_win; i++) {
        cout << DishID_win[i] << "\t" << name_win[i] << "\t" << price_win[i] << "\t" << count_win[i] << "\t" << price_win[i] * count_win[i] << endl;
    }

    cout << "\nYour total consumption is: " << totalprice_win + 2 << "¥.\n\n";

    string filePath = address + menu->toString_win(year_win) + '-' + menu->toString_win(month_win) + '-' + menu->toString_win(day_win) + ".txt";
    ofstream outFile(filePath, ios::app);
    outFile << inid << ":\n\n";
    outFile << "Number\tName\t\t\tPrice\tCount\tTotal\n";
    outFile << "--------------------------------------------------------------" << endl;

    for (int i = 0; i < N_win; i++) {
        outFile << DishID_win[i] << "\t" << name_win[i] << "\t" << price_win[i] << "\t" << count_win[i] << "\t" << price_win[i] * count_win[i] << endl;
    }

    outFile << "\nThe total consumption is: " << totalprice_win + 2 << "¥.\n\n";
    total_win += totalprice_win + 2;
    outFile.close();
}

#endif // RES_TEST_WIN_INORDER_H


