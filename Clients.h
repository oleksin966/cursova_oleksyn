#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <conio.h>
#include <locale>
#include "windows.h"
#include "Smartphones.h"
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <ctime>

class Client :  public Smartphone
{
    friend class Smartphone;
protected:
    int balance, purchases, session_id;
    int people_id, age;
    string data_people_string;
    string name, last_name, password, repeat_password, login, email, phone_number, country, adress;
    bool session;
public:
    Client() {};
    ~Client() {};
    void BuyPhone();
    void GenerateId();
    void ShowProfile();
    void ReplenishBalance();
    void Account();
    void AddFeedback();
    void ShowComments();
    void dividePhoneDataStrings();
    void Registration() ;
    void PeopleInfoString();
    void Authorization();
    void AddPeople() ;
    void divideDataStrings();
    void AddHistory();
    void SalesRevenue();
}client;
void Client::Registration()
{
    GenerateId();
    cout << "��������� ������ �������: " << endl;
    cout << "������ ��'�: "; cin >> name;
    cout << "������ �������: "; cin >> last_name;
    cout << "������ ��� ��: "; cin >> age;
    cout << "������ e-mail: "; cin >> email;
    cout << "������ ����� ��������: "; cin >> phone_number;
    cout << "������ �����: "; cin >> country;
    cout << "����: "; cin >> login;
    cout << "������: "; cin >> password;
    cout << "�������� ������: "; cin>>repeat_password;
    balance = 0;
    if (strcmp(password.c_str(),repeat_password.c_str()) == 0)
    {
        AddPeople();
        cout << "�������� " << last_name << " " << name << " ������ �������������!" << endl;
    }
    else
    {
        cout << "�������. ����� �� ����������" << endl;
    }

}
void Client::Authorization()
{
    string login_temp, password_temp;
    bool flag = false;

    cout << "������������� ��� ����� � ��� �������" << endl;
    cout << "��� ����������: ������: pass, ����: oleksin" << endl;
    cout << "����: "; cin >> login_temp;
    cout << "������: "; cin >> password_temp;

    ifstream ifs("clients.txt");
    while(!ifs.eof())
    {
        getline(ifs, data_people_string);
        divideDataStrings();
        if (strcmp(password.c_str(), password_temp.c_str()) == 0 && strcmp(login.c_str(), login_temp.c_str()) == 0)
        {
            break;
        }
        else
        {
            continue;
        }
    }
        ifs.close();
    if (people_id != 0)
    {
        Account();
    }
    else 
    {
        cout << "������� ������ ��� ����!" << endl;
    }
        
}
void Client::Account()
{
    session = true;
    session_id = people_id;
    char ch_key;
    cout << "�� ��ϲ��� �²���� � �²� ������! " << endl;
    cout << "+--------------+" << endl;
    cout << "| ���� �˲���� |" << endl;
    cout << "+--------------+" << endl;
    cout << "1 - �������� ��� �������" << endl;
    cout << "2 - ��������� ������" << endl;
    cout << "3 - ����������� ������ ���������" << endl;
    cout << "4 - ����� �� �������� + ������" << endl;
    cout << "5 - ������ ��������" << endl;
    cout << "6 - �������� �����/��������" << endl;
    cout << "7 - ����������� ������" << endl;
    cout << "ESC - �����" << endl;
    while (session)
    {
        switch ((ch_key = _getch()))
        {
        case '1':
            ShowProfile();
            break;
        case '2':
            ReplenishBalance();
            break;
        case '3':
            phone.printAllPhoneData();
            break;
        case '4':
            phone.phoneSearch();
            break;
        case '5':
            BuyPhone();
            break;
        case '6':
            AddFeedback();
            break;
        case '7':
            ShowComments();
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
void Client::ShowProfile() 
{
    cout << "+-------------+" << endl;
    cout << "| ̲� ���Բ�� |" << endl;
    cout << "+-------------+" << endl;
    ifstream ifs("clients.txt");
    while(!ifs.eof())
    {
        getline(ifs, data_people_string);
        divideDataStrings();
        if (session_id == people_id)
        {
            cout << "������� ������� " << login << " �� ������ �������� �������Ͳ� \"ANDROWORLD!!!\"" << endl;
            cout << "��� ID: " << people_id << endl;
            cout << "������:  ";  cout << balance << endl;
            cout << "��'�: "; cout << name << " " << last_name << endl;
            cout << "³� : "; cout << age << endl;
            cout << "�����: "; cout << country << endl;
            cout << "ʳ������ �������: "; cout << purchases << endl;
        }
    }
    ifs.close();
}
void Client::ReplenishBalance()
{
    cout << "+--------------------+" << endl;
    cout << "| ���������� ������� |" << endl;
    cout << "+--------------------+" << endl;
    int balance_temp;
    cout << "������ ���� �� ��� ������ ��������� ��� �������: " << endl; cin >> balance_temp;
    ifstream ifs("clients.txt");
    ofstream ofs("clientsTemp.txt");
    while (!ifs.eof())
    {
        getline(ifs, data_people_string);
        divideDataStrings();
        if (people_id != session_id)
        {
            ofs << data_people_string << endl;
            data_people_string.clear();
        }
        else
        {
            balance += balance_temp;
            PeopleInfoString();
            ofs << data_people_string;
            data_people_string.clear();
            cout << endl;
            cout <<"������ ������ ��������� �� ����: "<<balance_temp<<" �������!"<< endl;
        }
    }
    ofs.close();
    ifs.close();

    remove("clients.txt");
    rename("clientsTemp.txt", "clients.txt");

}
void Client::BuyPhone()
{
    cout << "+---------------------+" << endl;
    cout << "| ��������� ��������� |" << endl;
    cout << "+---------------------+" << endl;
    ifstream ifs("clients.txt");
    while (!ifs.eof())
    {
        getline(ifs, data_people_string);
        divideDataStrings();
        if (session_id == people_id)
        {
            cout << "�� ������ ������ " << balance << " �������" << endl;
        }
    }
    ifs.close();
   

    int id,temp_price,temp_num;
    bool buying;
    buying = true;
    ofstream ofs_phone("SmartphonesTemp.txt", ios::app);
    ofstream ofs_client("clientsTemp.txt",ios::app);
    ifstream ifs_phone("Smartphones.txt");
    phone.phoneSearch();
    cout << "ID ��������� ���� �� ������ ��������: "; cin >> id;
    while (buying)
    {
        while (!ifs_phone.eof())
        {
            getline(ifs_phone, data_phone_string);
            dividePhoneDataStrings();
            if (id != phone_id)
            {
                ofs_phone << data_phone_string << endl;
                data_phone_string.clear();
            }
            else
            {
                ifstream ifs_client("clients.txt");
                while (!ifs_client.eof())
                {
                    getline(ifs_client, data_people_string);
                    divideDataStrings();
                    if (session_id != people_id)
                    {
                        ofs_client << data_people_string << endl;
                        data_people_string.clear();
                    }
                    else
                    {
                        if (balance >= price)
                        {
                            AddHistory();
                            SalesRevenue();
                            balance -= price;
                            purchases++;
                            num_copies--;
                            PeopleInfoString();
                            ofs_client << data_people_string;
                            data_people_string.clear();
                            PhoneString();
                            ofs_phone << data_phone_string;
                            data_phone_string.clear();
                            cout << endl;
                            cout << "������� �������!!!" << endl;
                            buying = false;
                        }
                        else
                        {

                            ofs_client << data_people_string << endl;
                            data_people_string.clear();

                            ofs_phone << data_phone_string << endl;
                            data_phone_string.clear();

                            cout << "����������� ����� ��� ��������� �������!" << endl;
                            cout << "��� ��������� ��� ������ �������� 2" << endl;
                            buying = false;
                        }
                    }
                }
                ifs_client.close();
            }
        }
        if(!buying)
        {
            break;
        }
    }
    ifs_phone.close();
    ofs_client.close();
    ofs_phone.close();


    remove("clients.txt");
    rename("clientsTemp.txt", "clients.txt");

    remove("Smartphones.txt");
    rename("SmartphonesTemp.txt", "Smartphones.txt");
    
}
void Client::dividePhoneDataStrings()
{
    if (data_phone_string != "")
    {
        string strWords[11];
        for (int c = 0; c < 11; c++)
        {
            strWords[c].clear();
        }
        int counter = 0;
        for (int i = 0; i < data_phone_string.length(); i++)
        {
            if (data_phone_string[i] == ';')
                counter++;
            else
                strWords[counter] += data_phone_string[i];
        }
        phone_id = atoi(strWords[0].c_str());
        operation_sys = strWords[1];
        phone_name = strWords[2];
        model = strWords[3];
        release_date = atoi(strWords[4].c_str());
        phone_size = strWords[5];
        phone_proccesor = strWords[6];
        phone_memory = atoi(strWords[7].c_str());;
        num_of_camers = atoi(strWords[8].c_str());
        price = atoi(strWords[9].c_str());
        num_copies = atoi(strWords[10].c_str());
    }
    else
    {
        phone_id = -1;
        operation_sys.clear();
        phone_name.clear();
        model.clear();
        release_date = -1;
        phone_size.clear();
        phone_proccesor.clear();
        phone_memory = -1;
        num_of_camers = 1;
        num_copies = -1;
        price = -1;
    }
}
void Client::AddFeedback()
{
    cout << "+-----------------------------+" << endl;
    cout << "| ��������� ���������/²����� |" << endl;
    cout << "+-----------------------------+" << endl;
    string line;
    const int MAXLEN = 80;
    char s[MAXLEN];
    time_t t = time(0);
    strftime(s, MAXLEN, "%m/%d/%Y", localtime(&t));
    ifstream ifs("clients.txt");
    ofstream ofs("feedback.txt", ios::app);
    cout << "��� �������� �� ��������� ����� �������� ENTER" << endl;
    cout << "��� ����������� �������� �������� ���� ENTER" << endl;
    cout << "TEXT>";
    cin.ignore(255, '\n');
    while (!ifs.eof())
    {
        getline(ifs, data_people_string);
        divideDataStrings();
        if (people_id == session_id)
        {
            ofs << "�������� ������ " << s << " ������������ " << login << "\t" << endl;
            do
            {
                getline(cin, line);
                ofs << line << endl;
            } while (line != "");
            ofs << endl;
            ofs << "------------------------------------------------" << endl;
            cout << "�������� �����������!" << endl;
        }
    }

    ofs.close();
    ifs.close();
}
void Client::ShowComments()
{
    string line;
    ifstream ifs("feedback.txt");
    while(!ifs.eof())
    {
        getline(ifs, line);
        cout << line << endl;
    }
    ifs.close();
}
void Client::divideDataStrings()
{
    if (data_people_string != "")
    {
        string strWords[11];
        for (int c = 0; c < 11; c++)
        {
            strWords[c].clear();
        }
        int counter = 0;
        for (int i = 0; i < data_people_string.length(); i++)
        {
            if (data_people_string[i] == ';')
                counter++;
            else
                strWords[counter] += data_people_string[i];
        }
        people_id = atoi(strWords[0].c_str());
        name = strWords[1];
        last_name = strWords[2];
        age = atoi(strWords[3].c_str());
        email = strWords[4];
        phone_number = strWords[5];
        country = strWords[6];
        login = strWords[7];
        password = strWords[8];
        balance = atoi(strWords[9].c_str());
        purchases = atoi(strWords[10].c_str());
    }
    else
    {
        people_id = 0;
        name.clear();
        last_name.clear();
        age = 0;
        email.clear();
        phone_number.clear();
        country.clear();
        login.clear();
        password.clear();
        balance = 0;
        purchases = 0;
    }
}
void Client::PeopleInfoString()
{
    stringstream ss;
    if (!(people_id == -1))
    {
        ss << people_id << ';'
            << name << ';'
            << last_name << ';'
            << age << ';'
            << email << ';'
            << phone_number << ';'
            << country << ';'
            << login << ';'
            << password << ';'
            << balance << ';'
            << purchases << ';' << endl;

        data_people_string = ss.str();
    }
}
void Client::AddPeople()
{
    PeopleInfoString();
    ofstream ofs;
    ofs.open("clients.txt", ios::app);
    if (ofs.is_open() == true)
    {
        ofs << data_people_string;
    }
    ofs.close();
    data_people_string.clear();
}

void Client::GenerateId()  
{
    people_id = 0;
    ifstream ifstr("ClientId.txt");
    if (!ifstr.is_open())
    {
        ofstream ofstr1;
        ofstr1.open("ClientId.txt");
        people_id += 1;
        ofstr1.close();
    }
    else
    {
        ifstr >> people_id;
        ifstr.close();
        people_id += 1;
        ofstream ofstr;
        ofstr.open("ClientId.txt", ios::out | ios::trunc);
        ofstr << people_id;
        ofstr.close();
    }
}
void Client::AddHistory()
{
    const int MAXLEN = 80;
    char s[MAXLEN];
    time_t t = time(0);
    strftime(s, MAXLEN, "%m/%d/%Y", localtime(&t));

    ofstream ofs_history("history.txt", ios::app);
    ofs_history << "�볺�� " << name << " " << last_name << "(" << login << ")" << " ����� �������� "
        << phone_name << " " << model << " ����� " << price << ". ����: " << s << endl;
    ofs_history.close();
}
void Client::SalesRevenue()
{
    int sales_revenue = 0;
    ifstream ifs("sales_revenue.txt");
    ifs >> sales_revenue;
    ifs.close();
    sales_revenue += price;
    ofstream ofs("sales_revenue.txt", ios::out | ios::trunc);
    ofs << sales_revenue;
    ofs.close();
}


