//
// Created by Zoe Apokalypse on 2022/4/21.
//

#ifndef RES_TEST_WIN_CUSTOMERDATA_H
#define RES_TEST_WIN_CUSTOMERDATA_H

#define MAX 48
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <cstdint>

using namespace std;

class WIN_CustomerData
        {
        private:
            int num_win;
            string line_win;
            string Split_win[4];
            string Phone_Number_win[MAX];
            string UserName_win[MAX];
            string Password_win[MAX];
            string user_address_win = "data\\User_Data.txt";
        public:
            void REGISTER_win ();
            void LOGIN_win ();
            void write_win (int i, ofstream &temp);
            void read_win ();
            void print_win (int i);
            void sub_win();
            void search_win();
            static bool pass_win (string temp0);//�жϣ��绰�����Ƿ�Ϊ11λ
            static bool pass1_win (string temp);//�жϣ�����Ϊ5��16λ�����ֺ���ĸ����ϡ����������ֺ���ĸ�����ܰ������������ַ�
            static uint64_t LEN_win (uint64_t num);//��ȡint����
            int Get_Num_win ();
            string Get_Phone_Num_win(int i);
            string Get_Username_win(int i);
            string Get_Password_win(int i);
        };

void WIN_CustomerData::REGISTER_win()
{
    int phone_flag;
    int username_flag;
    //cout << num_win << endl;//test
    read_win();
    num_win ++;//test
    //cout << num_win << endl;//test
    ofstream add;
    add.open(user_address_win, ios::app);

    cout << "\nPlease enter your phone number.\nEnter 0 to exit.\n";
    string Phone;
    loop: cin >> Phone;
    phone_flag = 0;//initialize
    for (int i = 0; i < num_win; i ++)
    {
        if (Phone == Phone_Number_win[i])
            phone_flag += 1;//�жϵ绰�����Ƿ��ظ�
    }
    while (Phone != "0")
    {
        if (phone_flag != 0)
        {
            cout << "\nThe phone number you entered has been registered. :(\nPlease re-enter.\n";
            goto loop;
        }
        else if (pass_win(Phone))
            Phone_Number_win[num_win] = Phone;
        else
        {
            cout << "\nThe format of the phone number you entered is incorrect. :(\nPlease re-enter.\n";
            goto loop;
        }

        cout << "\nPlease enter your User Name: (without spaces)";
        string username;
        loop1: cin >> username;
        username_flag = 0;//initialize
        for (int i = 0; i < num_win; i ++)
        {
            if (username == UserName_win[i])
                username_flag += 1;//�ж��û����Ƿ��ظ�
        }
        if (username_flag != 0)
        {
            cout << "\nThe username you entered has been registered. :(\nPlease re-enter.\n";
            goto loop1;
        }

        cout << "\nPlease enter your Password:";
        string password;
        loop2: cin >> password;
        if (pass1_win(password))
        {
            //cout << num_win <<endl;//test
            UserName_win[num_win] = username;
            Password_win[num_win] = password;
            cout << "\nPassword set successfully! :)\n\n";
            add << endl;//����
            write_win(num_win, add);//&
            add.close();
            break;
        }
        else
        {
            cout << "\nThe password you entered is in the wrong format. :(\nPlease re-enter it\n"
                    "Password must contain numbers and letters and cannot contain other characters.";
            goto loop2;
        }
    }
}

void WIN_CustomerData::LOGIN_win()
{
    int flag = 0;
    int temp = 0;
    cout << "\nTo log in, Please enter your phone number.\nEnter 0 to exit.\n";
    read_win();
    num_win ++;
    //for (int i = 0; i < num_win; i ++)
    //    print_win(i);//tset
    string Phone;
    cin >> Phone;
    while (Phone != "0")
    {
        for (int i = 0; i < num_win; i ++)
        {
            if (Phone_Number_win[i] == Phone)
                flag += 1;
        }
        if (flag == 0)
        {
            cout << "New user? Try registering :)\n";
            REGISTER_win();
        }
        else
        {
            //����ֻ����Ƿ����ļ���
            cout << "Please enter your password: ";
        }
        string password;
        cin >> password;
        for (int i = 0; i < num_win; i ++)
        {
            if (Phone_Number_win[i] == Phone)
                temp = i;
        }
        if (Password_win[temp] == password)
        {
            cout << "\nLog in successfully! :)\nWelcome, " + UserName_win[temp] + ".\n\n";
            break;
        }
        else
        {
            cout << "\nYour phone number or password is wrong. :(\nPlease try again.\n";
            cout << "Please enter your phone number: \n";
            cout << "Enter 0 to exit.\n";
        }
        cin >> Phone;
    }
}

void WIN_CustomerData::write_win(int i, ofstream &temp)
{
    temp << i + 1 << "," << Phone_Number_win[i] << "," << UserName_win[i] << "," << Password_win[i] << ",";
}

void WIN_CustomerData::read_win()
{
    ifstream read (user_address_win.c_str());
    if (!read.is_open())
        cout << "Can't open the MENU file!" << endl;
    num_win = 0;
    while (std::getline(read, line_win))
    {
        int m = 0;
        for (int i = 0; i < line_win.length(); i++)
        {
            if (line_win[i] == ',')//split
                {
                    Split_win[m] = line_win.substr(0, i);
                line_win.erase(0, i + 1);
                i = 0;
                m++;
                }
            else if (i == line_win.length() - 1)  // Last word
                Split_win [m] = line_win.substr(0, i + 1);
        }
        Phone_Number_win [num_win] = Split_win[1];
        UserName_win [num_win] = Split_win [2];
        Password_win [num_win] = Split_win [3];
        num_win ++;
    }
}

void WIN_CustomerData::print_win(int i)
{
    cout << Phone_Number_win[i] + '\t';
    cout << UserName_win[i] + '\t' + Password_win[i] + '\n';
}

void WIN_CustomerData::sub_win()
{
    ofstream customer;
    customer.open(user_address_win);
    int temp;
    cout << "Please enter the number of the customer you want to delete: (enter 0 to exit)\n";
    cin >> temp;
    while (temp != 0)
    {
        if (temp < 0 || temp > num_win)
            cout << "The customer number you entered does not exist\n";
        else
        {
            num_win --;
            for (int i = temp - 1; i < num_win; i++)
            {
                Phone_Number_win[i] = Phone_Number_win[i + 1];
                UserName_win[i] = UserName_win[i + 1];
                Password_win[i] = Password_win[i + 1];
            }
        }
        cout << "Please enter the number of the customer you want to delete: (enter 0 to exit)\n";
        cin >> temp;
    }
    for (int i = 0; i < num_win; i++)
    {
        write_win(i, customer);//write_win in
        customer << endl;
    }
    customer.close();
}

void WIN_CustomerData::search_win()
{
    ifstream customer;
    customer.open(user_address_win);
    int temp;
    cout << "Please enter the number of the customer you want to find: (enter 0 to exit)\n";
    cin >> temp;
    while (temp != 0)
    {
        if (temp < 0 || temp > num_win)
            cout << "The customer number you entered does not exist\n";
        else
        {
            cout << "No.\t\tPhone\t\tName\t\tPassword\n";
            cout << temp << '\t';
            print_win(temp - 1);
        }
        cout << "Please enter the number of the customer you want to find: (enter 0 to exit)\n";
        cin >> temp;
    }
    customer.close();
}

bool WIN_CustomerData::pass_win(string temp0)//���绰�����ʽ
{
    if (temp0.length() != 11)
    {
        cout << "The format of the phone number you entered is incorrect. :(\nPlease re-enter.\n";
        return false;
    }
    else
        return true;
}

bool WIN_CustomerData::pass1_win(string temp)//��������ʽ
{
    int i = temp.length();
    int a = 0;
    int b = 0;
    int c = 0;

    for (int j = 0; j < i; j++)//�ж��Ƿ��������ַ�
    {
        bool flag = isalnum(temp.at(j));
        a += !flag;//����ַ�����������ĸ�����֣���ôaһ������0
        //cout << a << endl;//test
        bool flag1 = isalpha(temp.at(j));
        b += flag1;//����ַ���ȫ����ĸ����ôbһ������i��b���ܵ���i
        //cout << b << endl;//test
        bool flag2 = isdigit(temp.at(j));
        c += flag2;//����ַ���ȫ�����֣���ôcһ������i��c���ܵ���i
        //cout << c << endl;//test
    }

    if (!(i >= 5 && i <= 16) || a != 0 || b == i || c == i)
    {
        //cout << "The password you entered is in the wrong format. :(\nPlease re-enter it\n"
                //"The password must contain numbers and letters and cannot contain other characters.";
        return false;
    }
    else
    {
        //cout << "Password_win set successfully";
        return true;
    }
}

uint64_t WIN_CustomerData::LEN_win(uint64_t num)
{
    uint64_t len = 0;
    for(; num > 0; ++len) // �ж�num�Ƿ����0�����򳤶�+1
        num /= 10;
    return len;
}

int WIN_CustomerData::Get_Num_win()
{
    return num_win;
}

string WIN_CustomerData::Get_Phone_Num_win(int i)
{
    return Phone_Number_win[i];
}

string WIN_CustomerData::Get_Username_win(int i)
{
    return UserName_win[i];
}

string WIN_CustomerData::Get_Password_win(int i)
{
    return Password_win[i];
}

#endif //RES_TEST_WIN_CUSTOMERDATA_H
