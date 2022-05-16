//
// Created by Zoe Apokalypse on 2022/4/10.
//

#ifndef RES_TEST_WIN_INORDER_H
#define RES_TEST_WIN_INORDER_H

#include "WIN_Menu.h"
#include "WIN_CustomerData.h"

using namespace std;

static int inid = 1000;
static int tablenumber = 100;
int Outid;

class WIN_InOrder : public WIN_Menu
        {
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

WIN_InOrder::WIN_InOrder(Date* d)
{
    WIN_Menu* M;
    M = new WIN_Menu;
    string Order = M->ADDRESS_win(7);
    inid++;
    year_win = d -> get_year();
    month_win = d -> get_month();
    day_win = d -> get_day();
    ifstream IN;
    IN.open(Order);
    int x, y, z, m;
    IN >> x >> y >> z >> m >> Outid;
    if (x == year_win && y == month_win && z == day_win)
        inid = m + 1;
    else
        Outid = 2000;
    IN.close();
}

void WIN_InOrder::order_win()
{
    ofstream inside;
    inside.open("orderid.txt");
    inside << year_win << '\n' << month_win << '\n' << day_win << '\n' << inid << '\n' << Outid;
    inside.close();
    WIN_Menu* m;
    m = new WIN_Menu;
    m->MENU_win();
    int DishNum;
    cout << "Please enter the dish number you want to order.\nEnter 0 to exit\n";
    cin >> DishNum;
    while (DishNum != 0)
    {
        if (DishNum > 0 && DishNum < LENGTH_win)
        {
            cout << "Please enter the quantity you want to order\n";
            cin >> count_win[N_win];
            id_win[N_win] = m -> id_win[DishNum - 1];
            name_win[N_win] = m -> name_win[DishNum - 1];
            if(discount_win <= 10)
                price_win[N_win] = m -> price_win[DishNum - 1] * discount_win / 10;
            if (discount_win > 10)
                price_win[N_win] = m -> price_win[DishNum - 1] * discount_win / 100;
            totalprice_win += price_win[N_win] * count_win[N_win];
            DishID_win[N_win++] = DishNum;
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
    print_win();
}

void WIN_InOrder::print_win()
{
    WIN_Menu* m;
    m = new WIN_Menu;
    string address = m->ADDRESS_win(6);
    //cout << address_win << endl;//test
    cout << "Your order ID is: " << inid << endl;
    cout << "Your consumption mode is: In store\n";
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
    out << "\nThe total consumption is: " << totalprice_win + 2 << " ��.\n\n";
    total_win += totalprice_win + 2;
    out.close();
}

#endif //RES_TEST_WIN_INORDER_H
