//
// Created by Zoe Apokalypse on 2022/4/10.
//

#ifndef RES_TEST_CONTROL_H
#define RES_TEST_CONTROL_H

#include <iostream>
#include <ctime> //time
#include "InOrder.h"
#include "OutOrder.h"
#include "Date.h"
#include "Menu.h"
#include "CustomerData.h"


using namespace std;

void L_menu()//little menu for customers
{
    cout << "----------------------------------------------------"
            "\n\nEnter 1: Sign in as Customer"
            "\nEnter 2: Sign in as Chef"
            "\nEnter 3: Sign in as Manager"
            "\nEnter 0: Log Out\n\nPlease enter: ";
}

void LC_menu()//little menu for chef
{
    cout << "Please enter the instructions:"
            "\n\n1 to add dishes."
            "\n2 to modify dishes."
            "\n3 to delete dishes."
            "\n4 to search dishes."
            "\n5 to modify discount."
            "\n0 to exit\n\nPlease enter: ";
}

void LM_menu()//little menu for manager
{
    cout << "\nEnter 1: Manage operation"
            "\nEnter 2: Restaurant food management"
            "\nEnter 3: Statistics of sales records of a certain day"
            "\nEnter 4: Customer data management"
            "\nEnter 0: Exit the system\n\nPlease enter: ";
}

void Control(int op1)
{
    int a = 0;
    int b = 0;
    Menu *m;
    m = new Menu;
    m -> MENU();
    CustomerData *c;
    c = new CustomerData;
    //c -> REGISTER();//test
    int op;
    time_t timer;
    time (&timer);
    tm* t = localtime(&timer);
    Date* d;
    d = new Date(t -> tm_year + 1900, t -> tm_mon + 1, t -> tm_mday);
    cout << endl << "Today is " << t -> tm_year + 1900 << "-" << t -> tm_mon + 1 << "-" << t -> tm_mday << endl;
    m -> Crazy_Thursday();//😁
    cout << "----------------------------------------------------\n";
    cout << "Welcome to Restaurant Management System v 5.11! ^_^\n";
    L_menu();
    cin >> op;
    while (op != 0)
    {
        while (!(op == 1 || op == 2 || op == 3))
        {
            cout << "\nThe instruction you entered does not exist! :(\nPlease re-enter.\n";
            L_menu();
            cin >> op;
        }
        if (op == 1)
        {
            cout << "\nWelcome to the buffet ordering system! ^_^\n\n";

            /*cout << "Enter 1 to log in\nEnter 2 to register\n\nPlease enter: ";
            int temp;
            cin >> temp;
            switch (temp)
            {
                case 1:
                    c -> LOGIN();
                    break;
                case 2:
                    c->REGISTER();
            }*/
            cout << "----------------------------------------------------\n";
            m -> print();//TEST
            cout << "----------------------------------------------------\n\n";
            cout << "The above are all menus.\n\n1: Consumption in the store\n2: Delivery service\n3: Exit the system\n\nPlease enter: ";
            int op_;
            cin >> op_;
            while (!(op_ == 1 || op_ == 2 || op_ == 3))
            {
                cout << "The instruction you entered does not exist! :(\nPlease re-enter.\n";
                cout << "----------------------------------------------------\n";
                cout << "\n1: Consumption in the store\n2: Delivery service\n3: Exit the system\n\nPlease enter: ";
                cin >> op_;
            }
            while (op_ != 3)
            {
                if (op_ == 1)
                {
                    a++;
                    InOrder* in;
                    in = new InOrder(d);
                    in -> order();//?
                }
                else if (op_ == 2)
                {
                    b++;
                    OutOrder* out;
                    out = new OutOrder(d);

                    cout << "\nEnter 1 to log in\nEnter 2 to register\n\nPlease enter: ";
                    int temp;
                    cin >> temp;
                    switch (temp)
                    {
                        case 1:
                            c -> LOGIN();
                            break;
                        case 2:
                            c -> REGISTER();
                    }
                    out -> order();//
                }
                cout << "\n1: Consumption in the store\n2: Delivery service\n3: Exit the system\n\nPlease enter: ";
                cin >> op_;
            }
            L_menu();
        }

        else if (op == 2)//Chef
        {
            string account;
            bool power = 0;
            cout << "\nPlease enter your chef account: (enter 0 to exit): ";
            cin >> account;
            while (account != "0")
            {
                string password;
                cout << "Please enter your chef password: ";
                cin >> password;
                ifstream admin;
                string temp = m -> ADDRESS(3);//?
                //cout << temp << endl;//test
                admin.open(temp);
                {
                    string admin_account, admin_password;
                    admin >> admin_account >> admin_password;
                    if (admin_account == account && admin_password == password)
                    {
                        power = 1;
                        cout << "\n--------------------------------------------\n";
                        cout << "Login to chef system successfully! ^_^\n";
                        cout << "------------------------------------------\n";
                        break;
                    }
                    else
                    {
                        cout << "\nYour chef account or password is wrong. :(\nPlease try again.\n";
                        cout << "Enter 0 to exit.\n";
                        cout << "Please enter your chef account: ";
                    }
                }
                admin.close();
                cin >> account;
            }
            if (power)
            {
                bool flag = 1;
                if (flag)
                {
                    m -> print_for_adm();
                    flag = 0;
                }
                LC_menu();
                cin >> op1;
                while (op1 != 0)
                {
                    if (op1 != 1 && op1 != 2 && op1 != 3 && op1 != 4 && op1 != 5)
                    {
                        cout << "Instruction input error. :(\nPlease re-enter\n";
                        break;
                    }
                    if (op1 == 1)
                        m -> add();
                    else if (op1 == 2)
                    {
                        cout << "This function is disabled. Please contact the administrator for solution\n";
                        //m -> modify();
                    }
                    else if (op1 == 3)
                        m -> sub();
                    else if (op1 == 4)
                        m -> search();
                    else if (op1 == 5)
                    {
                        double x;
                        cout << "Please enter the discount you want to set: \n(for example, enter 50 is a 1/2 discount)\n";
                        cin >> x;
                        m -> Discount(x);
                    }
                    m -> MENU();
                    m -> print_for_adm();
                    LC_menu();
                    cin >> op1;
                }
            }
            L_menu();
        }

        else if (op == 3)//manager
        {
            string account;
            bool power = 0;
            cout << "\nPlease enter your manager account: (enter 0 to exit): ";
            cin >> account;
            while (account != "0")
            {
                string password;
                cout << "Please enter your manager password: ";
                cin >> password;
                ifstream admin;
                string temp = m -> ADDRESS(4);//?
                //cout << temp << endl;//test
                admin.open(temp);
                {
                    string admin_account, admin_password;
                    admin >> admin_account >> admin_password;
                    if (admin_account == account && admin_password == password)
                    {
                        power = 1;
                        cout << "\n----------------------------------------------\n";
                        cout << "Login to manager system successfully! ^_^\n";
                        cout << "----------------------------------------------\n";
                        break;
                    }
                    else
                    {
                        cout << "\nYour manager account or password is wrong. :(\nPlease try again.\n";
                        cout << "Enter 0 to exit.\n";
                        cout << "Please enter your manager account: ";
                    }
                }
                admin.close();
                cin >> account;
            }
            if (power)
            {
                bool flag = 1;
                LM_menu();
                int Op;
                cin >> Op;
                while (Op != 0)
                {
                    if (!(Op == 1 || Op == 2 || Op == 3 || Op == 4 || Op == 0))
                    {
                        cout << "\nThe instruction you entered does not exist! :(\nPlease re-enter.\n";
                        cout << "----------------------------------------------------\n";
                        LM_menu();
                    }
                    else if (Op == 1)
                    {
                        int year, month, day;
                        char c;
                        cout << "Please enter the date you want to query,\nIn the format of 2022/4/29\n";
                        cin >> year >> c >> month >> c >> day;
                        Date* date = new Date(year, month, day);
                        m -> search_file(date);
                    }

                    else if (Op == 2)
                    {
                        if (flag)
                        {
                            m -> print_for_adm();
                            flag = 0;
                        }
                        LC_menu();
                        cin >> op1;
                        while (op1 != 0)
                        {
                            if (op1 != 1 && op1 != 2 && op1 != 3 && op1 != 4 && op1 != 5)
                            {
                                cout << "Instruction input error. :(\nPlease re-enter\n";
                                break;
                            }
                            if (op1 == 1)
                                m -> add();
                            else if (op1 == 2)
                            {
                                cout << "This function is disabled. Please contact the administrator for solution\n";
                                //m -> modify();
                            }
                            else if (op1 == 3)
                                m -> sub();
                            else if (op1 == 4)
                                m -> search();
                            else if (op1 == 5)
                            {
                                double x;
                                cout << "Please enter the discount you want to set: \n(for example, enter 50 is a 1/2 discount)\n";
                                cin >> x;
                                m -> Discount(x);
                            }
                            m -> MENU();
                            m -> print_for_adm();
                            LC_menu();
                            cin >> op1;
                        }
                    }

                    else if (Op == 3)
                    {
                        int year, month, day;
                        char c;
                        cout << "Please enter the date you want to query in the format of 2022/4/29" << endl;
                        cin >> year >> c >> month >> c >> day;
                        Date* date = new Date(year, month, day);
                        m -> statistics(a, b);
                    }

                    else if (Op == 4)
                    {
                        if (flag)
                        {
                            c -> read();
                            for (int i = 0; i < c -> Get_Num(); i ++)
                                c -> print(i);
                            flag = 0;
                        }
                        cout << "Please enter the instructions:\n\n1 to delete customer data.\n2 to search customer data.\n0 to exit\n\nPlease enter: ";
                        cin >> op1;
                        while (op1 != 0)
                        {
                            if (op1 != 1 && op1 != 2)
                            {
                                cout << "Instruction input error. :(\nPlease re-enter\n";
                                break;
                            }
                            if (op1 == 1)
                                c -> sub();
                            else if (op1 == 2)
                            {
                                c -> read();
                                c -> search();
                            }
                            for (int i = 0; i < c -> Get_Num(); i ++)
                                c -> print(i);

                            cout << "Please enter the instructions:\n\n1 to delete customer data.\n2 to search customer data.\n0 to exit\n\nPlease enter: ";
                            cin >> op1;
                        }
                    }
                    LM_menu();
                    cin >> Op;
                }
            }
            L_menu();
        }
        cin >> op;
    }
}

#endif //RES_TEST_CONTROL_H
