//
// Created by Zoe Apokalypse on 2022/4/10.
//

#ifndef RES_TEST_MENU_H
#define RES_TEST_MENU_H

#define LENGTH 24
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Date.h"
#include <locale>
#include <codecvt>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
static double discount = 10;
static double total = 0;
class Menu
        {
        private:
            int count = 0;
            string raw_material_1[LENGTH];
            double PoRM_1 [LENGTH];
            string raw_material_2[LENGTH];
            double PoRM_2 [LENGTH];
            string raw_material_3[LENGTH];
            double PoRM_3 [LENGTH];
            string raw_material_4[LENGTH];
            double PoRM_4 [LENGTH];
            double COST [LENGTH];
            double PROFIT [LENGTH];
            string line_temp;
            string Split[11];
            string address = "data/menu.txt";//配料为中文+emoji，4字符排列，很整齐
            string address1 = "data/menu1.txt";//最好别用‼️英文排版很差
            string chef = "data/Chef.txt";//储存厨师账户/密码
            string admin = "data/admin.txt";//储存管理员账户/密码
            string user = "data/User_Data.txt";//储存客户账户/密码
            string order = "order/";//储存订单文件的文件夹
            string ORDER = "order/ORDER.txt";//储存order id
        public:
            int id[LENGTH] = {0};
            string name[LENGTH];
            double price[LENGTH];
            void initialization();
            void fill_in_null(string &temp);
            void L_Print(int i);
            void MENU();
            void print();
            void print_for_adm();
            void WRITE(int i,ofstream& temp);
            void add();
            void sub();
            //void modify();
            void search();
            void Discount(double i);
            string ADDRESS (int flag);
            void Crazy_Thursday();
            static string toString(int i);
            static int toInt(string str);
            void statistics (int a, int b);
            void search_file(Date *date);
        };

void Menu::initialization()//所有String初始化（弃用）
{
    for (int i = 0; i < LENGTH; i++)
    {
        raw_material_1[i] = "NULL";
        raw_material_2[i] = "NULL";
        raw_material_3[i] = "NULL";
        raw_material_4[i] = "NULL";
    }
}

void Menu::fill_in_null(string &temp)
{
    //cout << temp.length() << " ";//test
    if (temp.empty())
    {
        temp = "NULL";
        //cout << "NULL!";//test
    }
}

void Menu::L_Print(int i)
{
    cout
    << '\t' << '\t' << '\t' << raw_material_1[i] << '\t' << '\t' << PoRM_1 [i]
    << '\t' << '\t' << raw_material_2[i] << '\t' << '\t' << PoRM_2 [i]
    << '\t' << '\t' << raw_material_3[i] << '\t' << '\t' << PoRM_3 [i]
    << '\t' << '\t' << raw_material_4[i] << '\t' << '\t' << PoRM_4 [i]
    << '\t' << '\t' << COST [i] << '\t' << '\t' << PROFIT [i] << endl;
}

void Menu::MENU() {
    string file = address;
    ifstream MENU(file);

    if (!MENU.is_open()) {
        cout << "Can't open the MENU file!" << endl;
        return;
    }

    // 设置读取文件的locale为UTF-8
    MENU.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));

    count = 0;

    while (std::getline(MENU, line_temp)) {
        wstring_convert<codecvt_utf8<wchar_t>> converter;
        wstring wide_line = converter.from_bytes(line_temp);

        int m = 0;
        size_t pos = 0;
        while ((pos = wide_line.find(L',')) != wstring::npos) {
            Split[m] = converter.to_bytes(wide_line.substr(0, pos));
            wide_line.erase(0, pos + 1);
            m++;
        }
        Split[m] = converter.to_bytes(wide_line);

        id[count] = toInt(Split[0]);
        name[count] = Split[1];
        price[count] = toInt(Split[2]);
        raw_material_1[count] = Split[3];
        PoRM_1[count] = toInt(Split[4]);
        raw_material_2[count] = Split[5];
        PoRM_2[count] = toInt(Split[6]);
        raw_material_3[count] = Split[7];
        PoRM_3[count] = toInt(Split[8]);
        raw_material_4[count] = Split[9];
        PoRM_4[count] = toInt(Split[10]);
        COST[count] = PoRM_1[count] + PoRM_2[count] + PoRM_3[count] + PoRM_4[count];
        PROFIT[count] = price[count] - COST[count];

        fill_in_null(raw_material_1[count]);
        fill_in_null(raw_material_2[count]);
        fill_in_null(raw_material_3[count]);
        fill_in_null(raw_material_4[count]);

        count++;
    }
}
void Menu::print()//for customers
{
    cout << "Number\tName\t\t\t\t\t\t\tPrice\n";
    cout << "----------------------------------------------------\n";
    for (int i = 0; i < count; i++)
    {
        if (id [i] > 0 && id [i] < 10)//价格对齐
            {
            if (name[i].length() < 7)
                cout << id[i] << "       " << name[i] << "\t\t\t\t\t\t\t" << price[i] << endl;
            if (name[i].length() <= 11 && name[i].length() > 7)
                cout << id[i] << "       " << name[i] << "\t\t\t\t\t\t" << price[i] << endl;
            else if (name[i].length() <= 15 && name[i].length() >= 11 )
                cout << id[i] << "       " << name[i] << "\t\t\t\t\t" << price[i] << endl;
            else if (name[i].length() <= 19 && name[i].length() > 15 )
                cout << id[i] << "       " << name[i] << "\t\t\t\t" << price[i] << endl;
            else if (name[i].length() < 24 && name[i].length() > 19 )
                cout << id[i] << "       " << name[i] << "\t\t\t" << price[i] << endl;
            else if (name[i].length() >= 24 )
                cout << id[i] << "       " << name[i] << "\t\t" << price[i] << endl;
            }
        else
        {
            if (name[i].length() < 7)
                cout << id[i] << "      " << name[i] << "\t\t\t\t\t\t\t" << price[i] << endl;
            if (name[i].length() <= 11 && name[i].length() > 7)
                cout << id[i] << "      " << name[i] << "\t\t\t\t\t\t" << price[i] << endl;
            else if (name[i].length() <= 15 && name[i].length() >= 11 )
                cout << id[i] << "      " << name[i] << "\t\t\t\t\t" << price[i] << endl;
            else if (name[i].length() <= 19 && name[i].length() > 15 )
                cout << id[i] << "      " << name[i] << "\t\t\t\t" << price[i] << endl;
            else if (name[i].length() < 24 && name[i].length() > 19 )
                cout << id[i] << "      " << name[i] << "\t\t\t" << price[i] << endl;
            else if (name[i].length() >= 24 )
                cout << id[i] << "      " << name[i] << "\t\t" << price[i] << endl;
        }
    }
}

void Menu::print_for_adm()//for chef and managers
{
    cout << "\nThis is the menu details for Chef & Manager:\n\n";
    cout << "------------------------------------------------"
            "------------------------------------------------"
            "---------------------------------------------------\n";
    cout << "Number\tName\t\t\t\t\t\t\tPrice"
    << '\t' << "    RM 1" << '\t' << "  PoRM 1"
    << '\t' << "RM 2" << '\t' << "  PoRM 2"
    << '\t' << " RM 3" << '\t' << "  PoRM 3"
    << '\t' << "RM 4" << '\t' << "  PoRM 4"
    << '\t' << "Cost" << '\t' << "Profit\n";
    cout << "------------------------------------------------"
            "------------------------------------------------"
            "---------------------------------------------------\n";

    for (int i = 0; i < count; i++)
    {
        if (id [i] > 0 && id [i] < 10)//价格对齐，序号小于10，一位数
        {
            if (name[i].length() < 11)
            {
                cout << id[i] << "       " << name[i] << "\t\t\t\t\t\t" << price[i];
                L_Print(i);
            }
            else if (name[i].length() <= 15 && name[i].length() >= 11 )
            {
                cout << id[i] << "       " << name[i] << "\t\t\t\t\t" << price[i];
                L_Print(i);
            }
            else if (name[i].length() <= 19 && name[i].length() > 15 )
            {
                cout << id[i] << "       " << name[i] << "\t\t\t\t" << price[i];
                L_Print(i);
            }
            else if (name[i].length() < 24 && name[i].length() > 19 )
            {
                cout << id[i] << "       " << name[i] << "\t\t\t" << price[i];
                L_Print(i);
            }
            else if (name[i].length() >= 24 )
            {
                cout << id[i] << "       " << name[i] << "\t\t" << price[i];
                L_Print(i);
            }
        }
        else//序号大于10（2位数）
        {
            if (name[i].length() < 11)
            {
                cout << id[i] << "      " << name[i] << "\t\t\t\t\t\t" << price[i];
                L_Print(i);
            }
            else if (name[i].length() <= 15 && name[i].length() >= 11 )
            {
                cout << id[i] << "      " << name[i] << "\t\t\t\t\t" << price[i];
                L_Print(i);
            }
            else if (name[i].length() <= 19 && name[i].length() > 15 )
            {
                cout << id[i] << "      " << name[i] << "\t\t\t\t" << price[i];
                L_Print(i);
            }
            else if (name[i].length() < 24 && name[i].length() > 19 )
            {
                cout << id[i] << "      " << name[i] << "\t\t\t" << price[i];
                L_Print(i);
            }
            else if (name[i].length() >= 24 )
            {
                cout << id[i] << "      " << name[i] << "\t\t" << price[i];
                L_Print(i);
            }
        }
    }
    cout << "------------------------------------------------"
            "------------------------------------------------"
            "---------------------------------------------------\n\n";
}

void Menu::WRITE(int i, ofstream &temp) {
    temp << i + 1 << "," << name[i] << "," <<  price[i]
    << "," << raw_material_1[i] << "," << PoRM_1[i]
    << "," << raw_material_2[i] << "," << PoRM_2[i]
    << "," << raw_material_3[i] << "," << PoRM_3[i]
    << "," << raw_material_4[i] << "," << PoRM_4[i] << ",";
}

void Menu::add()
{
    string name_temp;
    int flag = 0;
    count++;
    //cout << count << endl;//test
    ofstream menu;
    menu.open(address, ios::app);
    cout << "Please enter the name, price, ingredients with its cost of the dish in turn.\n";
    loop: cin >> name_temp;
    flag = 0;
    for (int i = 0; i < count; i ++)
    {
        if (name_temp == name[i])
            flag += 1;//判断菜名是否重复
    }
    if (flag != 0)
    {
        cout << "\nThe dish name you entered has been occupied. :(\nPlease re-enter.\n";
        goto loop;
    }
    name [count] = name_temp;
    cin >> price[count]
    >> raw_material_1[count] >> PoRM_1[count]
    >> raw_material_2[count] >> PoRM_2[count]
    >> raw_material_3[count] >> PoRM_3[count]
    >> raw_material_4[count] >> PoRM_4[count];
    menu << endl;
    WRITE(count,menu);
    menu.close();
}

void Menu::sub()
{
    ofstream menu;
    menu.open(address);
    int num;
    cout << "Please enter the number of the dish you want to delete: (enter 0 to exit)\n";
    cin >> num;
    while (num != 0)
    {
        if (num < 0 || num > count)
            cout << "The dish number you entered does not exist\n";
        else
        {
            count--;
            for (int i = num - 1; i < count; i++)
            {
                id[i] = id[i + 1];
                name[i] = name[i + 1];
                price[i] = price[i + 1];
                raw_material_1[i] = raw_material_1[i + 1];
                PoRM_1[i] = PoRM_1[i + 1];
                raw_material_2[i] = raw_material_2[i + 1];
                PoRM_2[i] = PoRM_2[i + 1];
                raw_material_3[i] = raw_material_3[i + 1];
                PoRM_3[i] = PoRM_3[i + 1];
                raw_material_4[i] = raw_material_4[i + 1];
                PoRM_4[i] = PoRM_4[i + 1];
            }
        }
        cout << "Please enter the number of the dish you want to delete: (enter 0 to exit)\n";
        cin >> num;
    }
    for (int i = 0; i < count; i++)
    {
        WRITE(i,menu);//write in
        menu << endl;
    }
    menu.close();
}

/*void Menu::modify()
{
    ofstream menu;
    menu.open(address);
    int num;
    cout << "Please enter the number of the dish you want to modify: (enter 0 to exit)\n";
    cin >> num;
    while (num != 0)
    {
        if (num < 0 || num > count)
            cout << "The dish number you entered does not exist\n";
        else
        {
            cout << "Please enter the dish name you want to modify: (if you do not modify the dish name, enter 0)\n";
            string str;
            cin >> str;
            if (str != "0")
            {
                name[num - 1] = "";
                name[num - 1] = str;
            }
            cout << "Please enter the dish name you want to modify: (if you do not modify the dish name, enter 0)\n";
            int p;
            cin >> p;
            if (p != 0)
                price[num - 1] = p;
        }
        cout << "Please enter the number of the dish you want to modify: (enter 0 to exit)\n";
        cin >> num;
    }
    for (int i = 0; i < count; i++)
    {
        WRITE(i,menu);//write in
    }
    menu.close();
}*/

void Menu::search()
{
    //cout << count;
    ifstream menu;
    menu.open(address);
    int num;
    cout << "Please enter the number of the dish you want to find: (enter 0 to exit): \n";
    cin >> num;
    while (num != 0)
    {
        if (num < 0 || num > count)
            cout << "The dish number you entered does not exist\n";
        else
        {
            int lp = num - 1;

            cout << "\nThis is the menu details for Chef & Manager:\n\n";
            cout << "------------------------------------------------"
                    "------------------------------------------------"
                    "---------------------------------------------------\n";
            cout << "Number\tName\t\t\t\t\t\t\tPrice"
            << '\t' << "    RM 1" << '\t' << "  PoRM 1"
            << '\t' << "RM 2" << '\t' << "  PoRM 2"
            << '\t' << " RM 3" << '\t' << "  PoRM 3"
            << '\t' << "RM 4" << '\t' << "  PoRM 4"
            << '\t' << "Cost" << '\t' << "Profit\n";
            cout << "------------------------------------------------"
                    "------------------------------------------------"
                    "---------------------------------------------------\n";

            if (id [lp] > 0 && id [lp] < 10)//价格对齐，序号小于10，一位数
                {
                if (name[lp].length() < 11)
                {
                    cout << id[lp] << "       " << name[lp] << "\t\t\t\t\t\t" << price[lp];
                    L_Print(lp);
                }
                else if (name[lp].length() <= 15 && name[lp].length() >= 11 )
                {
                    cout << id[lp] << "       " << name[lp] << "\t\t\t\t\t" << price[lp];
                    L_Print(lp);
                }
                else if (name[lp].length() <= 19 && name[lp].length() > 15 )
                {
                    cout << id[lp] << "       " << name[lp] << "\t\t\t\t" << price[lp];
                    L_Print(lp);
                }
                else if (name[lp].length() < 24 && name[lp].length() > 19 )
                {
                    cout << id[lp] << "       " << name[lp] << "\t\t\t" << price[lp];
                    L_Print(lp);
                }
                else if (name[lp].length() >= 24 )
                {
                    cout << id[lp] << "       " << name[lp] << "\t\t" << price[lp];
                    L_Print(lp);
                }
                }
            else//序号大于10（2位数）
            {
                if (name[lp].length() < 11)
                {
                    cout << id[lp] << "      " << name[lp] << "\t\t\t\t\t\t" << price[lp];
                    L_Print(lp);
                }
                else if (name[lp].length() <= 15 && name[lp].length() >= 11 )
                {
                    cout << id[lp] << "      " << name[lp] << "\t\t\t\t\t" << price[lp];
                    L_Print(lp);
                }
                else if (name[lp].length() <= 19 && name[lp].length() > 15 )
                {
                    cout << id[lp] << "      " << name[lp] << "\t\t\t\t" << price[lp];
                    L_Print(lp);
                }
                else if (name[lp].length() < 24 && name[lp].length() > 19 )
                {
                    cout << id[lp] << "      " << name[lp] << "\t\t\t" << price[lp];
                    L_Print(lp);
                }
                else if (name[lp].length() >= 24 )
                {
                    cout << id[lp] << "      " << name[lp] << "\t\t" << price[lp];
                    L_Print(lp);
                }
            }
        }
        cout << "\nPlease enter the number of the dish you want to find: (enter 0 to exit)\n";
        cin >> num;
    }
    menu.close();
}

void Menu::Discount(double i)
{
    discount = i;
}

string Menu::ADDRESS(int flag)
{
   switch (flag)
   {
       case 1:
           return address;
       case 2:
           return address1;
       case 3:
           return chef;
       case 4:
           return admin;
       case 5:
           return user;
       case 6:
           return order;
       case 7:
           return ORDER;
   }
   return std::string();
}

void Menu::Crazy_Thursday()
{
    time_t timer;
    time (&timer);
    tm* t = localtime (&timer);
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
        Discount(5);
    }
    else if (m == 4 && d == 29)
    {
        cout << "\nToday is the store manager's birthday 🎂！\nAll customers enjoy a 50% discount!\n\n";
        Discount(5);
    }
}

//下面为原本file_management-----------------------------------------------------------------------------------------

string Menu::toString(int i)
{
    stringstream s;
    s << i;
    return s.str();
    // 将int转换成string
}

int Menu::toInt(string str)
{
    return atoi(str.c_str());
    // 将string转换成int
}


void Menu::statistics(int a,int b)
{
    int in = a;
    int out = b;
    time_t timer;
    time (&timer);
    tm *t = localtime(&timer);
    Date *d1;
    d1 = new Date(t -> tm_year + 1900, t -> tm_mon + 1, t -> tm_mday);
    cout << "Today is " << t -> tm_year + 1900 << "-" << t -> tm_mon + 1 << "-" << t -> tm_mday << "\n";
    cout << "The ratio of in store consumption to takeout today is: " << in << ":" << out << endl;
    cout << "Today's total sales are: " << total << "¥\n";
}

void Menu::search_file(Date* date)//增删改查以日期为文件名的订单文件（txt）
{
    string address = ADDRESS(6);
    int year, month, day;
    year = date -> get_year();
    month = date -> get_month();
    day = date -> get_day();
    string str = address + toString(year) + '-' + toString(month) + '-' + toString(day) + ".txt";
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

#endif //RES_TEST_MENU_H
