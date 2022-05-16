//
// Created by Zoe Apokalypse on 2022/4/10.
//

#ifndef RES_TEST_WIN_OUTORDER_H
#define RES_TEST_WIN_OUTORDER_H

#include "WIN_Menu.h"
#include "WIN_CustomerData.h"

using namespace std;
static int Inid;
static int outid = 1000;

class WIN_OutOrder : public WIN_Menu
        {
        private:
            int id_win[LENGTH_win] = {0};
            string name_win[LENGTH_win];
            double price_win[LENGTH_win];
            int count_win[LENGTH_win];
            int DishID_win[LENGTH_win];
            double totalprice_win = 0;
            int N_win = 0;
            string time_win;
            string phonenumber_win;
            string where_win;
            int year_win;
            int month_win;
            int day_win;
        public:
            WIN_OutOrder(Date* d);
            void order_win();
            void print_win();
        };

WIN_OutOrder::WIN_OutOrder(Date* d)
{
    WIN_Menu* M;
    M = new WIN_Menu;
    string Order = M->ADDRESS_win(7);
    outid++;
    year_win = d -> get_year();
    month_win = d -> get_month();
    day_win = d -> get_day();
    ifstream OUT;
    OUT.open(Order);
    int x, y, z, n;
    OUT >> x >> y >> z >> Inid >> n;
    if (x == year_win && y == month_win && z == day_win)
        outid = n + 1;
    else
        Inid = 1000;
    OUT.close();
}

void WIN_OutOrder::order_win()
{
    ofstream outside;
    outside.open("orderid.txt");
    outside << year_win << '\n' << month_win << '\n' << day_win << '\n' << Inid << '\n' << outid;
    outside.close();
    WIN_Menu* m;
    m = new WIN_Menu;
    m->MENU_win();
    int DishNum;
    cout << "Please enter the delivery time: ";
    cin >> time_win;
    cout << "\nPlease enter the delivery location: ";
    cin >> where_win;
    cout << "\nPlease confirm your phone number: \n";
    cin >> phonenumber_win;
    cout << "Please enter the dish number you want to order and enter 0 to exit\n";
    cin >> DishNum;
    while (DishNum != 0)
    {
        cout << "Please enter the quantity you want to order\n";
        cin >> count_win[N_win];
        id_win[N_win] = m -> id_win[DishNum - 1];
        name_win[N_win] = m -> name_win[DishNum - 1];
        if (discount_win <= 10)
            price_win[N_win] = m -> price_win[DishNum - 1] * discount_win / 10;
        if (discount_win > 10)
            price_win[N_win] = m -> price_win[DishNum - 1] * discount_win / 100;
        totalprice_win += price_win[N_win] * count_win[N_win];
        DishID_win[N_win++] = DishNum;
        cout << "Please enter the dish number you want to order, enter 0 to exit\n";
        cin >> DishNum;
    }
    print_win();
}

void WIN_OutOrder::print_win()
{
    WIN_Menu* m;
    m = new WIN_Menu;
    string address = m->ADDRESS_win(6);
    //cout << address_win << endl;//test
    cout << "Your order ID is: " << outid << endl;
    cout << "Your consumption mode is: Take Out\n";
    cout << "Your meal delivery time is: " << time_win << endl;
    cout << "Your delivery location is: " << where_win << endl;
    cout << "Your mobile number is: " << phonenumber_win << endl;
    cout << "Your table ID is: " << ++tablenumber << endl;
    cout << "Your table fee is: 2��\n";
    cout << "Our discount today is: " << discount_win << "%\n";
    cout << "Your order is as follows: \n\n";

    cout << "Number" << '\t' << "Name" << '\t' << '\t' << '\t' << '\t' << "Price\t" << "Count\t" << "Total\n";
    cout << "--------------------------------------------------------------\n";
    for (int i = 0; i < N_win; i++)
    {
        if (DishID_win [i] > 0 && DishID_win [i] < 10)//�۸����
        {
            if (name_win[i].length() <= 15)
                cout << DishID_win[i] << "       " << name_win[i] << '\t' << '\t' << '\t' << price_win[i] << '\t' << count_win[i] << '\t' << price_win[i] * count_win[i] << endl;
            else if (name_win[i].length() < 24 && name_win[i].length() > 15 )
                cout << DishID_win[i] << "       " << name_win[i] << '\t' << '\t' << price_win[i] << '\t' << count_win[i] << '\t' << price_win[i] * count_win[i] << endl;
            else if (name_win[i].length() >= 24 )
                cout << DishID_win[i] << "       " << name_win[i] << '\t' << price_win[i] << '\t' << count_win[i] << '\t' << price_win[i] * count_win[i] << endl;
        }
        else if (DishID_win [i] >= 10)
        {
            if (name_win[i].length() <= 15)
                cout << DishID_win[i] << "      " << name_win[i] << '\t' << '\t' << '\t' << price_win[i] << '\t' << count_win[i] << '\t' << price_win[i] * count_win[i] << endl;
            else if (name_win[i].length() < 24 && name_win[i].length() > 15 )
                cout << DishID_win[i] << "      " << name_win[i] << '\t' << '\t' << price_win[i] << '\t' << count_win[i] << '\t' << price_win[i] * count_win[i] << endl;
            else if (name_win[i].length() >= 24 )
                cout << DishID_win[i] << "      " << name_win[i] << '\t' << price_win[i] << '\t' << count_win[i] << '\t' << price_win[i] * count_win[i] << endl;
        }
    }
    cout << "\nYour total consumption is: " << totalprice_win + 2 << " ��.\n\n";

    string str = address + m->toString_win(year_win) + '-' + m->toString_win(month_win) + '-' + m->toString_win(day_win) + ".txt";//���涩���ļ��ĵ�ַ
    ofstream out(str, ios::app);//д���ļ�
    out << inid << ":\n\n";
    out << "Number" << '\t' << "Name" << '\t' << '\t' << '\t' << '\t' << "Price\t" << "Count\t" << "Total\n";
    out << "--------------------------------------------------------------" << endl;
    for (int i = 0; i < N_win; i++)
    {
        if (DishID_win [i] > 0 && DishID_win [i] < 10)//�۸����
        {
            if (name_win[i].length() <= 15)
                out << DishID_win[i] << "       " << name_win[i] << '\t' << '\t' << '\t' << price_win[i] << '\t' << count_win[i] << '\t' << price_win[i] * count_win[i] << endl;
            else if (name_win[i].length() < 24 && name_win[i].length() > 15 )
                out << DishID_win[i] << "       " << name_win[i] << '\t' << '\t' << price_win[i] << '\t' << count_win[i] << '\t' << price_win[i] * count_win[i] << endl;
            else if (name_win[i].length() >= 24 )
                out << DishID_win[i] << "       " << name_win[i] << '\t' << price_win[i] << '\t' << count_win[i] << '\t' << price_win[i] * count_win[i] << endl;
        }
        else if (DishID_win [i] >= 10)
        {
            if (name_win[i].length() <= 15)
                out << DishID_win[i] << "      " << name_win[i] << '\t' << '\t' << '\t' << price_win[i] << '\t' << count_win[i] << '\t' << price_win[i] * count_win[i] << endl;
            else if (name_win[i].length() < 24 && name_win[i].length() > 15 )
                out << DishID_win[i] << "      " << name_win[i] << '\t' << '\t' << price_win[i] << '\t' << count_win[i] << '\t' << price_win[i] * count_win[i] << endl;
            else if (name_win[i].length() >= 24 )
                out << DishID_win[i] << "      " << name_win[i] << '\t' << price_win[i] << '\t' << count_win[i] << '\t' << price_win[i] * count_win[i] << endl;
        }
    }
    out << "\nThe total consumption is: " << totalprice_win + 2 << " ?.\n\n";
    total_win += totalprice_win + 2;
    out.close();
}

#endif //RES_TEST_WIN_OUTORDER_H
