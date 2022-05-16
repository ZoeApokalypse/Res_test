//
// Created by Zoe Apokalypse on 2022/4/21.
//

#ifndef RES_TEST_CUSTOMERDATA_H
#define RES_TEST_CUSTOMERDATA_H

#define MAX 48
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

class CustomerData
        {
        private:
            int num;
            string line;
            string Split[4];
            string Phone_Number[MAX];
            string UserName[MAX];
            string Password[MAX];
            string address = "data/User_Data.txt";
        public:
            void REGISTER ();
            void LOGIN ();
            void write (int i, ofstream &temp);
            void read ();
            void print (int i);
            void sub();
            void search();
            static bool pass (string temp0);//判断，电话号码是否为11位
            static bool pass1 (string temp);//判断，密码为5到16位到数字和字母到组合。必须有数字和字母。不能包含其他特殊字符
            static uint64_t LEN (uint64_t num);//获取int长度
            int Get_Num ();
            string Get_Phone_Num(int i);
            string Get_Username(int i);
            string Get_Password(int i);
        };

void CustomerData::REGISTER()
{
    int phone_flag;
    int username_flag;
    //cout << num << endl;//test
    read();
    num ++;//test
    //cout << num << endl;//test
    ofstream add;
    add.open(address, ios::app);

    cout << "\nPlease enter your phone number.\nEnter 0 to exit.\n";
    string Phone;
    loop: cin >> Phone;
    phone_flag = 0;//initialize
    for (int i = 0; i < num; i ++)
    {
        if (Phone == Phone_Number[i])
            phone_flag += 1;//判断电话号码是否重复
    }
    while (Phone != "0")
    {
        if (phone_flag != 0)
        {
            cout << "\nThe phone number you entered has been registered. :(\nPlease re-enter.\n";
            goto loop;
        }
        else if (pass(Phone))
            Phone_Number[num] = Phone;
        else
        {
            cout << "\nThe format of the phone number you entered is incorrect. :(\nPlease re-enter.\n";
            goto loop;
        }

        cout << "\nPlease enter your User Name: (without spaces) ";
        string username;
        loop1: cin >> username;
        username_flag = 0;//initialize
        for (int i = 0; i < num; i ++)
        {
            if (username == UserName[i])
                username_flag += 1;//判断用户名是否重复
        }
        if (username_flag != 0)
        {
            cout << "\nThe username you entered has been registered. :(\nPlease re-enter.\n";
            goto loop1;
        }

        cout << "\nPlease enter your Password: ";
        string password;
        loop2: cin >> password;
        if (pass1(password))
        {
            //cout << num <<endl;//test
            UserName[num] = username;
            Password[num] = password;
            cout << "\nPassword set successfully! :)\n\n";
            add << endl;//换行
            write(num,add);//&
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

void CustomerData::LOGIN()
{
    int flag = 0;
    int temp = 0;
    cout << "\nTo log in, Please enter your phone number.\nEnter 0 to exit.\n";
    read();
    num ++;
    //for (int i = 0; i < num; i ++)
    //    print(i);//tset
    string Phone;
    cin >> Phone;
    while (Phone != "0")
    {
        for (int i = 0; i < num; i ++)
        {
            if (Phone_Number[i] == Phone)
                flag += 1;
        }
        if (flag == 0)
        {
            cout << "New user? Try registering :)\n";
            REGISTER();
        }
        else
        {
            //检测手机号是否在文件中
            cout << "Please enter your password: ";
        }
        string password;
        cin >> password;
        for (int i = 0; i < num; i ++)
        {
            if (Phone_Number[i] == Phone)
                temp = i;
        }
        if (Password[temp] == password)
        {
            cout << "\nLog in successfully! :)\nWelcome, " + UserName[temp] + ".\n\n";
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

void CustomerData::write(int i, ofstream &temp)
{
    temp << i + 1 << "," << Phone_Number[i] << "," << UserName[i] << "," << Password[i] << ",";
}

void CustomerData::read()
{
    ifstream read (address.c_str());
    if (!read.is_open())
        cout << "Can't open the customer file!" << endl;
    num = 0;
    while (std::getline(read, line))
    {
        int m = 0;
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == ',')//split
            {
                Split[m] = line.substr(0, i);
                line.erase(0, i+1);
                i = 0;
                m++;
            }
            else if (i == line.length()-1)  // Last word
                Split [m] = line.substr(0, i+1);
        }
        Phone_Number [num] = Split[1];
        UserName [num] = Split [2];
        Password [num] = Split [3];
        num ++;
    }
}

void CustomerData::print(int i)
{
    cout << i << Phone_Number[i] + '\t';
    cout << UserName[i] + '\t' + Password[i] + '\n';
}

void CustomerData::sub()
{
    ofstream customer;
    customer.open(address);
    int temp;
    cout << "Please enter the number of the customer you want to delete: (enter 0 to exit)\n";
    cin >> temp;
    while (temp != 0)
    {
        if (temp < 0 || temp > num)
            cout << "The customer number you entered does not exist\n";
        else
        {
            num --;
            for (int i = temp - 1; i < num; i++)
            {
                Phone_Number[i] = Phone_Number[i + 1];
                UserName[i] = UserName[i + 1];
                Password[i] = Password[i + 1];
            }
        }
        cout << "Please enter the number of the customer you want to delete: (enter 0 to exit)\n";
        cin >> temp;
    }
    for (int i = 0; i < num; i++)
    {
        write(i, customer);//write in
        customer << endl;
    }
    customer.close();
}

void CustomerData::search()
{
    ifstream customer;
    customer.open(address);
    int temp;
    cout << "Please enter the number of the customer you want to find: (enter 0 to exit)\n";
    cin >> temp;
    while (temp != 0)
    {
        if (temp < 0 || temp > num)
            cout << "The customer number you entered does not exist\n";
        else
        {
            cout << "No.\t\tPhone\t\tName\t\tPassword\n";
            cout << temp << '\t';
            print(temp - 1);
        }
        cout << "Please enter the number of the customer you want to find: (enter 0 to exit)\n";
        cin >> temp;
    }
    customer.close();
}

bool CustomerData::pass(string temp0)//检查电话号码格式
{
    if (temp0.length() != 11)
    {
        //cout << "The format of the phone number you entered is incorrect. :(\nPlease re-enter.\n";
        return false;
    }
    else
        return true;
}

bool CustomerData::pass1(string temp)//检查密码格式
{
    int i = temp.length();
    int a = 0;
    int b = 0;
    int c = 0;

    for (int j = 0; j < i; j++)//判断是否有其他字符
    {
        bool flag = isalnum(temp.at(j));
        a += !flag;//如果字符串仅包含字母和数字，那么a一定等于0
        //cout << a << endl;//test
        bool flag1 = isalpha(temp.at(j));
        b += flag1;//如果字符串全是字母，那么b一定等于i，b不能等于i
        //cout << b << endl;//test
        bool flag2 = isdigit(temp.at(j));
        c += flag2;//如果字符串全是数字，那么c一定等于i，c不能等于i
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
        //cout << "Password set successfully";
        return true;
    }
}

uint64_t CustomerData::LEN(uint64_t num)
{
    uint64_t len = 0;
    for(; num > 0; ++len) // 判断num是否大于0，否则长度+1
        num /= 10;
    return len;
}

int CustomerData::Get_Num()
{
    return num;
}

string CustomerData::Get_Phone_Num(int i)
{
    return Phone_Number[i];
}

string CustomerData::Get_Username(int i)
{
    return UserName[i];
}

string CustomerData::Get_Password(int i)
{
    return Password[i];
}

#endif //RES_TEST_CUSTOMERDATA_H
