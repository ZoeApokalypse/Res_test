//
// Created by Zoe Apokalypse on 2022/4/10.
//

#ifndef RES_TEST_WIN_MENU_H
#define RES_TEST_WIN_MENU_H

#define LENGTH_win 24
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Date.h"
//#include "CN.h"

using namespace std;
static double total_win = 0;
static double discount_win = 100;
class WIN_Menu
        {
        private:
            int count_win = 0;
            string raw_material_1_win[LENGTH_win];
            double PoRM_1_win [LENGTH_win];
            string raw_material_2_win[LENGTH_win];
            double PoRM_2_win [LENGTH_win];
            string raw_material_3_win[LENGTH_win];
            double PoRM_3_win [LENGTH_win];
            double COST_win [LENGTH_win];
            double PROFIT_win [LENGTH_win];
            string line_temp_win;
            string Split_win[9];
            string address_win = "data\\win_menu.txt";//����Ϊ���ģ�4�ַ����У������룬��ΪMac��Win��
            string address1_win = "data\\menu1.txt";//��ñ���??Ӣ���Ű�ܲ�
            string chef_win = "data\\Chef.txt";//�����ʦ�˻�/����
            string admin_win = "data\\admin.txt";//�������Ա�˻�/����
            string user_win = "data\\User_Data.txt";//����ͻ��˻�/����
            string order_win = "order\\";//���涩���ļ����ļ���
            string ORDER_win = "order\\ORDER.txt";//����order id
        public:
            int id_win[LENGTH_win] = {0};
            string name_win[LENGTH_win];
            double price_win[LENGTH_win];
            void initialization_win();
            void fill_in_null_win(string &temp);
            void L_Print_win(int i);
            void MENU_win();
            void print_win();
            void print_for_adm_win();
            void WRITE_win(int i, ofstream& temp);
            void add_win();
            void sub_win();
            //void modify_win();
            void search_win();
            void Discount_win(double i);
            string ADDRESS_win (int flag);
            void Crazy_Thursday_win();
            static string toString_win(int i);
            static int toInt_win(string str);
            void statistics_win (int a, int b);
            void search_file_win(Date *date);
        };

void WIN_Menu::initialization_win()//����String��ʼ�������ã�
{
    for (int i = 0; i < LENGTH_win; i++)
    {
        raw_material_1_win[i] = "NULL";
        raw_material_2_win[i] = "NULL";
        raw_material_3_win[i] = "NULL";
    }
}

void WIN_Menu::fill_in_null_win(string &temp)//����
{
    //cout << temp.length() << " ";//test
    if (temp.empty())
    {
        temp = "NULL";
        //cout << "NULL!";//test
    }
}

void WIN_Menu::L_Print_win(int i) {
    cout
            << '\t' << raw_material_1_win[i] << '\t' << PoRM_1_win [i]
            << '\t' << raw_material_2_win[i] << '\t' << PoRM_2_win [i]
            << '\t' << raw_material_3_win[i] << '\t' << PoRM_3_win [i]
            << '\t' << COST_win [i] << '\t' << PROFIT_win [i] << endl;
}

void WIN_Menu::MENU_win()
{
    string file = address_win;
    ifstream MENU (file.c_str());
    if (!MENU.is_open())
        cout << "Can't open the MENU file!" << endl;
    count_win = 0;
    //initialization_win();//TEST

    while (std::getline(MENU, line_temp_win))
    {
        //string line_temp_win = UTF8ToGB(line_temp_win.c_str()).c_str();
        //cout << count_win << endl;//test
        //cout << line_temp_win << endl;//test
        int m = 0;
        for (int i = 0; i < line_temp_win.length(); i++)
        {
            if (line_temp_win[i] == ',')//split
            {
                Split_win[m] = line_temp_win.substr(0, i);
                line_temp_win.erase(0, i + 1);
                i = 0;
                m++;
            }
            else if (i == line_temp_win.length() - 1)  // Last word
                Split_win [m] = line_temp_win.substr(0, i + 1);
        }

        id_win [count_win] = toInt_win(Split_win[0]);//String to int
        name_win [count_win] = Split_win [1];
        price_win [count_win]= toInt_win(Split_win[2]);
        raw_material_1_win [count_win] = Split_win [3];
        PoRM_1_win [count_win]= toInt_win(Split_win[4]);
        raw_material_2_win [count_win] = Split_win [5];
        PoRM_2_win [count_win]= toInt_win(Split_win[6]);
        raw_material_3_win [count_win] = Split_win [7];
        PoRM_3_win [count_win]= toInt_win(Split_win[8]);
        COST_win [count_win] = PoRM_1_win [count_win] + PoRM_2_win [count_win] + PoRM_3_win [count_win];
        PROFIT_win [count_win] = price_win [count_win] - COST_win [count_win];

        //if the number of Raw materials is less than 4, replace the null string with "NULL"
        fill_in_null_win(raw_material_1_win[count_win]);
        fill_in_null_win(raw_material_2_win[count_win]);
        fill_in_null_win(raw_material_3_win[count_win]);
        //cout << endl;//test
        count_win ++;
    }
    //initialization_win();//TEST!!NULL
}

void WIN_Menu::print_win()//for customers
{
    cout << "Number" << '\t' << "Name" << '\t' << '\t' << '\t' << '\t' << "Price\n";
    cout << "------------------------------------------------\n";
    for (int i = 0; i < count_win; i++)
    {
        if (id_win [i] > 0 && id_win [i] < 10)//�۸����
        {
            if (name_win[i].length() <= 15)
                cout << id_win[i] << "       " << name_win[i] << '\t' << '\t' << '\t' << price_win[i] << endl;
            else if (name_win[i].length() < 24 && name_win[i].length() > 15 )
                cout << id_win[i] << "       " << name_win[i] << '\t' << '\t' << price_win[i] << endl;
            else if (name_win[i].length() >= 24 )
                cout << id_win[i] << "       " << name_win[i] << '\t' << price_win[i] << endl;
        }
        else if (id_win [i] >= 10)
        {
            if (name_win[i].length() <= 15)
                cout << id_win[i] << "      " << name_win[i] << '\t' << '\t' << '\t' << price_win[i] << endl;
            else if (name_win[i].length() < 24 && name_win[i].length() > 15 )
                cout << id_win[i] << "      " << name_win[i] << '\t' << '\t' << price_win[i] << endl;
            else if (name_win[i].length() >= 24 )
                cout << id_win[i] << "      " << name_win[i] << '\t' << price_win[i] << endl;
        }
    }
}

void WIN_Menu::print_for_adm_win()//for chef_win and managers
{
    cout << "\nThis is the menu details for Chef & Manager:\n\n";
    cout << "------------------------------------------------"
            "------------------------------------------------\n";
    cout << "Number" << '\t' << "Name" << '\t' << '\t' << '\t' << '\t' << "Price"
    << '\t' << "RM 1" << '\t' << "PRM1"
    << '\t' << "RM 2" << '\t' << "PRM2"
    << '\t' << "RM 3" << '\t' << "PRM3"
    << '\t' << "Cost" << '\t' << "Profit\n";
    cout << "------------------------------------------------"
            "------------------------------------------------\n";
    for (int i = 0; i < count_win; i++)
    {
        if (id_win [i] > 0 && id_win [i] < 10)//�۸���룬���С��10��һλ��
        {
            if (name_win[i].length() <= 15)
            {
                cout << id_win[i] << "       " << name_win[i] << '\t' << '\t' << '\t' << price_win[i];
                L_Print_win(i);
            }
            else if (name_win[i].length() < 24 && name_win[i].length() > 15 )
            {
                cout << id_win[i] << "       " << name_win[i] << '\t' << '\t' << price_win[i];
                L_Print_win(i);
            }
            else if (name_win[i].length() >= 24 )
            {
                cout << id_win[i] << "       " << name_win[i] << '\t' << price_win[i];
                L_Print_win(i);
            }
        }
        else//��Ŵ���10��2λ����
        {
            if (name_win[i].length() <= 15)
            {
                cout << id_win[i] << "      " << name_win[i] << '\t' << '\t' << '\t' << price_win[i];
                L_Print_win(i);
            }
            else if (name_win[i].length() < 24 && name_win[i].length() > 15 )
            {
                cout << id_win[i] << "      " << name_win[i] << '\t' << '\t' << price_win[i];
                L_Print_win(i);
            }
            else if (name_win[i].length() >= 24 )
            {
                cout << id_win[i] << "      " << name_win[i] << '\t' << price_win[i];
                L_Print_win(i);
            }
        }
    }
    cout << "------------------------------------------------"
            "------------------------------------------------\n\n";
}

void WIN_Menu::WRITE_win(int i, ofstream &temp) {
    temp << i + 1 << "," << name_win[i] << "," << price_win[i]
         << "," << raw_material_1_win[i] << "," << PoRM_1_win[i]
         << "," << raw_material_2_win[i] << "," << PoRM_2_win[i]
         << "," << raw_material_3_win[i] << "," << PoRM_3_win[i] << ",";
}

void WIN_Menu::add_win()
{
    string name_temp;
    int flag = 0;
    count_win++;
    //cout << count_win << endl;//test
    ofstream menu;
    menu.open(address_win, ios::app);
    cout << "Please enter the name, price, ingredients with its cost of the dish in turn.\n";
    loop: cin >> name_temp;
    flag = 0;
    for (int i = 0; i < count_win; i ++)
    {
        if (name_temp == name_win[i])
            flag += 1;//�жϲ����Ƿ��ظ�
    }
    if (flag != 0)
    {
        cout << "\nThe dish name you entered has been occupied. :(\nPlease re-enter.\n";
        goto loop;
    }
    name_win [count_win] = name_temp;
    cin >> price_win[count_win]
        >> raw_material_1_win[count_win] >> PoRM_1_win[count_win]
        >> raw_material_2_win[count_win] >> PoRM_2_win[count_win]
        >> raw_material_3_win[count_win] >> PoRM_3_win[count_win];
    menu << endl;
    WRITE_win(count_win, menu);
    menu.close();
}

void WIN_Menu::sub_win()
{
    ofstream menu;
    menu.open(address_win);
    int num;
    cout << "Please enter the number of the dish you want to delete: (enter 0 to exit)\n";
    cin >> num;
    while (num != 0)
    {
        if (num < 0 || num > count_win)
            cout << "The dish number you entered does not exist\n";
        else
        {
            count_win--;
            for (int i = num - 1; i < count_win; i++)
            {
                id_win[i] = id_win[i + 1];
                name_win[i] = name_win[i + 1];
                price_win[i] = price_win[i + 1];
                raw_material_1_win[i] = raw_material_1_win[i + 1];
                PoRM_1_win[i] = PoRM_1_win[i + 1];
                raw_material_2_win[i] = raw_material_2_win[i + 1];
                PoRM_2_win[i] = PoRM_2_win[i + 1];
                raw_material_3_win[i] = raw_material_3_win[i + 1];
                PoRM_3_win[i] = PoRM_3_win[i + 1];
            }
        }
        cout << "Please enter the number of the dish you want to delete: (enter 0 to exit)\n";
        cin >> num;
    }
    for (int i = 0; i < count_win; i++)
    {
        WRITE_win(i, menu);//write in
        menu << endl;
    }
    menu.close();
}

/*void WIN_Menu::modify_win()
{
    ofstream menu;
    menu.open(address_win);
    int num;
    cout << "Please enter the number of the dish you want to modify: (enter 0 to exit)\n";
    cin >> num;
    while (num != 0)
    {
        if (num < 0 || num > count_win)
            cout << "The dish number you entered does not exist\n";
        else
        {
            cout << "Please enter the dish name you want to modify: (if you do not modify the dish name, enter 0)\n";
            string str;
            cin >> str;
            if (str != "0")
            {
                name_win[num - 1] = "";
                name_win[num - 1] = str;
            }
            cout << "Please enter the dish name you want to modify: (if you do not modify the dish name, enter 0)\n";
            int p;
            cin >> p;
            if (p != 0)
                price_win[num - 1] = p;
        }
        cout << "Please enter the number of the dish you want to modify: (enter 0 to exit)\n";
        cin >> num;
    }
    for (int i = 0; i < count_win; i++)
    {
        WRITE_win(i, menu);//write in
    }
    menu.close();
}*/

void WIN_Menu::search_win()
{
    ifstream menu;
    menu.open(address_win);
    int num;
    cout << "Please enter the number of the dish you want to find: (enter 0 to exit)\n";
    cin >> num;
    while (num != 0)
    {
        if (num < 0 || num > count_win)
            cout << "The dish number you entered does not exist\n";
        else
        {
            cout << "Number" << '\t' << "Name" << '\t' << '\t' << '\t' << '\t' << "Price"
                 << '\t' << "RM 1" << '\t' << "PRM1"
                 << '\t' << "RM 2" << '\t' << "PRM2"
                 << '\t' << "RM 3" << '\t' << "PRM3"
                 << '\t' << "Cost" << '\t' << "Profit\n";
            cout << "------------------------------------------------"
                    "------------------------------------------------\n";

            int i = num -1;

            if (id_win [i] > 0 && id_win [i] < 10)//�۸���룬���С��10��һλ��
            {
                if (name_win[i].length() <= 15)
                {
                    cout << id_win[i] << "       " << name_win[i] << '\t' << '\t' << '\t' << price_win[i];
                    L_Print_win(i);
                }
                else if (name_win[i].length() < 24 && name_win[i].length() > 15 )
                {
                    cout << id_win[i] << "       " << name_win[i] << '\t' << '\t' << price_win[i];
                    L_Print_win(i);
                }
                else if (name_win[i].length() >= 24 )
                {
                    cout << id_win[i] << "       " << name_win[i] << '\t' << price_win[i];
                    L_Print_win(i);
                }
            }
            else//��Ŵ���10��2λ����
            {
                if (name_win[i].length() <= 15)
                {
                    cout << id_win[i] << "      " << name_win[i] << '\t' << '\t' << '\t' << price_win[i];
                    L_Print_win(i);
                }
                else if (name_win[i].length() < 24 && name_win[i].length() > 15 )
                {
                    cout << id_win[i] << "      " << name_win[i] << '\t' << '\t' << price_win[i];
                    L_Print_win(i);
                }
                else if (name_win[i].length() >= 24 )
                {
                    cout << id_win[i] << "      " << name_win[i] << '\t' << price_win[i];
                    L_Print_win(i);
                }
            }
        }
        cout << "\nPlease enter the number of the dish you want to find: (enter 0 to exit)\n";
        cin >> num;
    }
    menu.close();
}

void WIN_Menu::Discount_win(double i)
{
    discount_win = i;
}

string WIN_Menu::ADDRESS_win(int flag)
{
   switch (flag)
   {
       case 1:
           return address_win;
       case 2:
           return address1_win;
       case 3:
           return chef_win;
       case 4:
           return admin_win;
       case 5:
           return user_win;
       case 6:
           return order_win;
       case 7:
           return ORDER_win;
   }
    return std::string();
}

void WIN_Menu::Crazy_Thursday_win()
{
    time_t timer;
    time(&timer);
    tm* t = localtime(&timer);
    Date* D;
    D = new Date(t -> tm_year + 1900, t -> tm_mon + 1, t -> tm_mday);

    int y = t -> tm_year + 1900;
    int m = t -> tm_mon + 1;
    int d = t -> tm_mday;

    if(m == 1 || m == 2)
    {
        m += 12;
        y --;
    }

    int Week=(d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7;
    if (Week == 3)
    {
        cout << "\nToday is Crazy Thursday!!!\nAll customers enjoy a 50% discount!\n\n";
        Discount_win(5);
    }
    else if (m == 4 && d == 29)
    {
        cout << "\nToday is the store manager's birthday ��\nAll customers enjoy a 50% discount!\n\n";
        Discount_win(5);
    }
}

//����Ϊԭ��file_management--------------------------------------------------------------------------------------------------

string WIN_Menu::toString_win(int i)
{
    stringstream s;
    s << i;
    return s.str();
    // ��intת����string
}

int WIN_Menu::toInt_win(string str)
{
    return atoi(str.c_str());
    // ��stringת����int
}


void WIN_Menu::statistics_win(int a, int b)
{
    int in = a;
    int out = b;
    time_t timer;
    time (&timer);
    tm* t = localtime(&timer);
    Date* d;
    d = new Date(t -> tm_year + 1900, t -> tm_mon + 1, t -> tm_mday);
    cout << "Today is " << t -> tm_year + 1900 << "-" << t -> tm_mon + 1 << "-" << t -> tm_mday << "-\n";
    cout << "The ratio of in store consumption to takeout today is: " << in << ":" << out << endl;
    cout << "Today's total_win sales are: " << total_win << "$\n";
}

void WIN_Menu::search_file_win(Date* date)//��ɾ�Ĳ�������Ϊ�ļ����Ķ����ļ���txt��
{
    string address = ADDRESS_win(6);
    int year, month, day;
    year = date -> get_year();
    month = date -> get_month();
    day = date -> get_day();
    string str = address + toString_win(year) + '-' + toString_win(month) + '-' + toString_win(day) + ".txt";
    ifstream s;
    s.open(str);
    string t[500];
    int l = 0;
    int h = 0;
    string j[50];
    int high[50] = { 0 };
    while (getline(s, t[l]))
    {
        cout << t[l] << endl;
        if (t[l].length() == 4)
        {
            high[h] = l;
            j[h++] = t[l];
        }
        l++;
    }
    s.close();
    cout << "Enter 1 to delete\nEnter 0 to exit\nPlease enter: ";
    int op;
    cin >> op;
    while (op != 0)
    {
        while (op != 1)
        {
            cout << "\nInput error, please re-enter\n";
            cout << "Enter 1 to delete\nEnter 0 to exit\nPlease enter: ";
            cin >> op;
        }
        if (op == 1)
        {
            cout << "\nPlease enter the order number you want to delete\n";
            string op_;
            cin >> op_;
            int flag = -1;
            for (int i = 0; i < h; i++)
                if (op_ == j[i])
                {
                    flag = i;
                    break;
                }
            if (flag == -1)
            {
                cout << "The order number you entered does not exist\n";
                cout << "Enter 1 to delete\nEnter 0 to exit\nPlease enter: ";
                cin >> op;
                continue;
            }
            else
            {
                if (high[flag + 1] != 0)
                {
                    for (int k = high[flag]; k < high[flag + 1]; k++)
                        t[k] = "0";
                }
                else
                {
                    for (int k = high[flag]; k < l; k++)
                        t[k] = "0";
                }
                ofstream s;
                s.open(str);
                for (int p = 0; p < l; p++)
                {
                    if (t[p] != "0")
                        s << t[p] << endl;
                }
                s.close();
            }
            cout << "\nEnter 1 to delete\nEnter 0 to exit\nPlease enter: " << endl;
            cin >> op;
        }
    }
}

#endif //RES_TEST_WIN_MENU_H
