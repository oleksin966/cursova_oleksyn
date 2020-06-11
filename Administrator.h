#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <conio.h>
#include <locale>
#include "windows.h"
#include "Smartphones.h"
#include "Clients.h"
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <ctime>

class Administrator : public Smartphone , public Client
{
private:
    int session_id, calc_price;
    bool session;
public:
    string banner = "logo/logo1.txt";
    Administrator() {};
    ~Administrator() {};
    void AdminPanel();
    void AuthorizationAdmin() ;
    void ClientsInfo();
    void CheckHistory();
    void Banner();
    void ViewBanner();
    void ChangeBanner();

} admin;

void Administrator::AuthorizationAdmin()
{
    string login, password;
    cout << "���� � ����-������" << endl;
    cout << "����: "; cin >> login;
    cout << "������: "; cin >> password;
    if (login == "admin" && password == "admin")
    {
        AdminPanel();
    }
    else
    {
        cout << "������� ������ ��� ����!" << endl;
    }

}
void Administrator::AdminPanel()
{
    session = true;
    char ch_key;
    cout << "+--------------+" << endl;
    cout << "| ��̲�-������ |" << endl;
    cout << "+--------------+" << endl;
    cout << "1 - ����� �� ��" << endl;
    cout << "2 - �������� ����� ��������" << endl;
    cout << "3 - �������� ��������" << endl;
    cout << "4 - ������ ������� ��������� �� �����" << endl;
    cout << "5 - ����������� ������ �볺���" << endl;
    cout << "6 - ����������� ������ �������" << endl;
    cout << "7 - ³����� �� ��������" << endl;
    cout << "8 - �����������" << endl;
    cout << "9 - ������ ����� � ������" << endl;
    cout << "ESC - �����" << endl;
    while (session)
    {
        switch ((ch_key = _getch()))
        {
        case '1':
            phone.phoneSearch();
            break;
        case '2':
            phone.getPhoneInfo();
            phone.addPhone();
            phone.printData();
            break;
        case '3':
            phone.deletePhone();
            break;
        case '4':
            phone.changeCountPhones();
            break;
        case '5':
            ClientsInfo();
            break;
        case '6':
            CheckHistory();
            break;
        case '7':
            client.ShowComments();
            break;
        case '8':
            phone.Calculator();
            break;
        case '9':
            Banner();
            break;
        case 27:
            session = false;
            cout << "����� � ������� ����\n";
            break;
        default:
            cout << "���� �� �����������!\n";
            break;
        }
    }
}
void Administrator::ClientsInfo()
{
    cout.setf(ios::left);
    cout.fill(' ');
    cout.width(6);
    cout << "ID";
    cout.width(12);
    cout << "��'�";
    cout.width(15);
    cout << "�������";
    cout.width(5);
    cout << "³�";
    cout.width(20);
    cout << "Email";
    cout.width(20);
    cout << "����� ��������";
    cout.width(10);
    cout << "�����";
    cout.width(15);
    cout << "������";
    cout.width(8);
    cout << "������";
    cout.width(10);
    cout << "ʳ������ �������";
    cout << endl;
    ifstream ifs("clients.txt");
    while(!ifs.eof())
    {
        getline(ifs,data_people_string);
        divideDataStrings();
        cout.setf(ios::left);
        cout.fill(' ');
        cout.width(6);
        cout << people_id;
        cout.width(12);
        cout << name;
        cout.width(15);
        cout << last_name;
        cout.width(5);
        cout << age;
        cout.width(20);
        cout << email;
        cout.width(20);
        cout << phone_number;
        cout.width(10);
        cout << country;
        cout.width(15);
        cout << login;
        cout.width(8);
        cout << balance;
        cout.width(10);
        cout << purchases;
        cout << endl;
        data_people_string.clear();
    }
    ifs.close();
}
void Administrator::CheckHistory()
{
    cout << "+------------------+" << endl;
    cout << "| ����в� �����Ʋ� |" << endl;
    cout << "+------------------+" << endl;
    string line;
    ifstream ifs("history.txt");
    while (!ifs.eof())
    {
        getline(ifs, line);
        cout << line << endl ;
    }
    ifs.close();
}
void Administrator::Banner()
{
    char ch_key;
    bool sub_menu = true;
    cout << "+---------------------+" << endl;
    cout << "| ����������� ������� |" << endl;
    cout << "+---------------------+" << endl;
    cout << "1 - ����������� �� ������� �������" << endl;
    cout << "2 - ������� ������" << endl;
    cout << "ESC - �����" << endl;
    while (sub_menu)
    {
        switch ((ch_key = _getch()))
        {
        case '1':
            ViewBanner();
            break;
        case '2':
            ChangeBanner();
            break;
        case 27:
            sub_menu = false;
            cout << "�����\n";
            break;
        default:
            cout << "���� �� �����������!\n";
            break;
        }
    }
}
void Administrator::ViewBanner()
{
    string line;
    for (int i = 1; i < 5; i++) 
    {
        cout <<"BANNER #" <<i<<endl;
        ifstream ifs("logo/logo" + to_string(i) + ".txt");
        while (!ifs.eof()) 
        {
            getline(ifs, line);
            cout << line << endl;
        }
        ifs.close();
    }
}
void Administrator::ChangeBanner()
{
    int change;
    string line;
    cout << "����� ������� ���� ������ �������: "; cin >> change;
    for (int i = 1; i < 5; i++)
    {
        if (change == i)
        {
            banner = "logo/logo" + to_string(i) + ".txt";
            cout << "������ #" << i << " ������ �������!" << endl;
            cout << "��� ������ �� ����� ����� �������� ESC" << endl;
        }
    }

}