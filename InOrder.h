//
// Created by Zoe Apokalypse on 2022/4/10.
//

#ifndef RES_TEST_INORDER_H
#define RES_TEST_INORDER_H

#include "Menu.h"
#include "CustomerData.h"

using namespace std;

static int inid = 1000;
static int tablenumber = 100;
int Outid;

class InOrder : public Menu
        {
        private:
            int id[LENGTH] = {0};
            string name[LENGTH];
            double price[LENGTH];
            int count[LENGTH];
            int DishID[LENGTH];
            double totalprice = 0;
            int N = 0;
            int year;
            int month;
            int day;
        public:
            InOrder(Date* d);
            void order();
            void print();
        };

InOrder::InOrder(Date* d)
{
    Menu* M;
    M = new Menu;
    string Order = M -> ADDRESS(7);
    inid++;
    year = d -> get_year();
    month = d -> get_month();
    day = d -> get_day();
    ifstream IN;
    IN.open(Order);
    int x, y, z, m;
    IN >> x >> y >> z >> m >> Outid;
    if (x == year && y == month && z == day)
        inid = m + 1;
    else
        Outid = 2000;
    IN.close();
}

void InOrder::order()
{
    ofstream inside;
    inside.open("orderid.txt");
    inside << year << '\n' << month << '\n' << day << '\n' << inid << '\n' << Outid;
    inside.close();
    Menu* m;
    m = new Menu;
    m -> MENU();
    int DishNum;
    cout << "Please enter the dish number you want to order.\nEnter 0 to exit\n";
    cin >> DishNum;
    while (DishNum != 0)
    {
        if (DishNum > 0 && DishNum < LENGTH)
        {
            cout << "Please enter the quantity you want to order\n";
            cin >> count[N];
            id[N] = m -> id[DishNum - 1];
            name[N] = m -> name[DishNum - 1];
            if(discount <= 10)
                price[N] = m -> price[DishNum - 1] * discount / 10;
            if (discount > 10)
                price[N] = m -> price[DishNum - 1] * discount / 100;
            totalprice += price[N] * count[N];
            DishID[N++] = DishNum;
            cout << "Please enter the dish number you want to order.\nEnter 0 to exit\n";
            cin >> DishNum;
        }
        else
        {
            cout << "The number you entered does not exit! :(\nPlease re-enter\n\n";
            cin >> DishNum;
            //break;
        }
    }
    print();
}

void InOrder::print()
{
    Menu* m;
    m = new Menu;
    string address = m -> ADDRESS(6);
    //cout << address << endl;//test
    cout << "Your order ID is: " << inid << endl;
    cout << "Your consumption mode is: In store\n";
    cout << "Your table ID is: " << ++tablenumber << endl;
    cout << "Your table fee is:" << "2¥\n";
    cout << "Our discount today is: " << discount << "%\n";
    cout << "Your order is as follows: \n\n";

    cout << "Number" << '\t' << "Name" << "\t\t\t\t\t\t" << "Price\t" << "Count\t" << "Total\n";
    cout << "--------------------------------------------------------------\n";
    for (int i = 0; i < N; i++)
    {
        if (DishID [i] > 0 && DishID [i] < 10)//价格对齐
            {
            if (name[i].length() < 11)
                cout << DishID[i] << "       " << name[i] << "\t\t\t\t\t" << price[i] << "\t\t" << count[i] << "\t\t" << price[i] * count[i] << endl;
            else if (name[i].length() <= 15 && name[i].length() >= 11 )
                cout << DishID[i] << "       " << name[i] << "\t\t\t\t" << price[i] << "\t\t" << count[i] << "\t\t" << price[i] * count[i] << endl;
            else if (name[i].length() <= 19 && name[i].length() > 15 )
                cout << DishID[i] << "       " << name[i] << "\t\t\t" << price[i] << "\t\t" << count[i] << "\t\t" << price[i] * count[i] << endl;
            else if (name[i].length() < 24 && name[i].length() > 19 )
                cout << DishID[i] << "       " << name[i] << "\t\t" << price[i] << "\t\t" << count[i] << "\t\t" << price[i] * count[i] << endl;
            else if (name[i].length() >= 24 )
                cout << DishID[i] << "       " << name[i] << '\t' << price[i] << "\t\t" << count[i] << "\t\t" << price[i] * count[i] << endl;
            }
        else
        {
            if (name[i].length() < 11)
                cout << DishID[i] << "      " << name[i] << "\t\t\t\t\t" << price[i] << "\t\t" << count[i] << "\t\t" << price[i] * count[i] << endl;
            else if (name[i].length() <= 15 && name[i].length() >= 11 )
                cout << DishID[i] << "      " << name[i] << "\t\t\t\t" << price[i] << "\t\t" << count[i] << "\t\t" << price[i] * count[i] << endl;
            else if (name[i].length() <= 19 && name[i].length() > 15 )
                cout << DishID[i] << "      " << name[i] << "\t\t\t" << price[i] << "\t\t" << count[i] << "\t\t" << price[i] * count[i] << endl;
            else if (name[i].length() < 24 && name[i].length() > 19 )
                cout << DishID[i] << "      " << name[i] << "\t\t" << price[i] << "\t\t" << count[i] << "\t\t" << price[i] * count[i] << endl;
            else if (name[i].length() >= 24 )
                cout << DishID[i] << "      " << name[i] << '\t' << price[i] << "\t\t" << count[i] << "\t\t" << price[i] * count[i] << endl;
        }
    }
    cout << "\nYour total consumption is: " << totalprice + 2 << " ¥.\n\n";

    string str = address + m -> toString(year) + '-' + m -> toString(month) + '-' + m -> toString(day) + ".txt";//储存订单文件的地址
    ofstream out(str, ios::app);//写入文件
    out << inid << ":\n\n";
    cout << "Number" << '\t' << "Name" << "\t\t\t\t\t\t" << "Price\t" << "Count\t" << "Total\n";
    out << "--------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++)
    {
        if (DishID [i] > 0 && DishID [i] < 10)//价格对齐
            {
            if (name[i].length() < 11)
                out << DishID[i] << "       " << name[i] << "\t\t\t\t\t" << price[i] << "\t\t" << count[i] << "\t\t" << price[i] * count[i] << endl;
            else if (name[i].length() <= 15 && name[i].length() >= 11 )
                out << DishID[i] << "       " << name[i] << "\t\t\t\t" << price[i] << "\t\t" << count[i] << "\t\t" << price[i] * count[i] << endl;
            else if (name[i].length() <= 19 && name[i].length() > 15 )
                out << DishID[i] << "       " << name[i] << "\t\t\t" << price[i] << "\t\t" << count[i] << "\t\t" << price[i] * count[i] << endl;
            else if (name[i].length() < 24 && name[i].length() > 19 )
                out << DishID[i] << "       " << name[i] << "\t\t" << price[i] << "\t\t" << count[i] << "\t\t" << price[i] * count[i] << endl;
            else if (name[i].length() >= 24 )
                out << DishID[i] << "       " << name[i] << '\t' << price[i] << "\t\t" << count[i] << "\t\t" << price[i] * count[i] << endl;
            }
        else
        {
            if (name[i].length() < 11)
                out << DishID[i] << "      " << name[i] << "\t\t\t\t\t" << price[i] << "\t\t" << count[i] << "\t\t" << price[i] * count[i] << endl;
            else if (name[i].length() <= 15 && name[i].length() >= 11 )
                out << DishID[i] << "      " << name[i] << "\t\t\t\t" << price[i] << "\t\t" << count[i] << "\t\t" << price[i] * count[i] << endl;
            else if (name[i].length() <= 19 && name[i].length() > 15 )
                out << DishID[i] << "      " << name[i] << "\t\t\t" << price[i] << "\t\t" << count[i] << "\t\t" << price[i] * count[i] << endl;
            else if (name[i].length() < 24 && name[i].length() > 19 )
                out << DishID[i] << "      " << name[i] << "\t\t" << price[i] << "\t\t" << count[i] << "\t\t" << price[i] * count[i] << endl;
            else if (name[i].length() >= 24 )
                out << DishID[i] << "      " << name[i] << '\t' << price[i] << "\t\t" << count[i] << "\t\t" << price[i] * count[i] << endl;
        }
    }
    out << "\nThe total consumption is: " << totalprice + 2 << " ¥.\n\n";
    total += totalprice + 2;
    out.close();
}

#endif //RES_TEST_INORDER_H
