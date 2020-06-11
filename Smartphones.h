#pragma once
#include <iostream>
#include <conio.h>
#include <locale>
#include "windows.h"
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
class Smartphone
{
protected:
    int price, phone_id, num_copies;
    string data_phone_string;
    int release_date;
    int  num_of_camers, phone_memory;
    string phone_name, model, phone_size, phone_proccesor, operation_sys;
public:
    Smartphone() { };
    ~Smartphone() { };
    //����������� ��������� ������
    void generateId();

    //��������/�������� ������� � ���� ������
    void addPhone();
    void deletePhone();
 
    //������� ��� ������ ������
    void printAllPhoneData();
    void printData();
    void titleData();
    void dataPhoneData();

    //������� ��� ����� ������
    void getPhoneInfo();

    //������� �������
    void dividePhoneDataStrings();
    void queryOutputPhones();
    void PhoneString();

    //Գ����� �� ������ �� �����
    void dataPhoneFilter();
    void filterByDate();
    void filterByMember();
    void filterByPrice();
    void filterByCamera();
    void phoneSearch();

    //������ ���� � ���� ������
    void changeCountPhones();

    //����
    void Calculator();


}phone;

void Smartphone::generateId()
{
    phone_id = 0;
    ifstream ifstr("PhoneId.txt");
    if (!ifstr.is_open())
    {
        ofstream ofstr1;
        ofstr1.open("PhoneId.txt");
        phone_id += 1;
        ofstr1.close();
    }
    else
    {
        ifstr >> phone_id;
        ifstr.close();
        phone_id += 1;
        ofstream ofstr;
        ofstr.open("PhoneId.txt", ios::out | ios::trunc);
        ofstr << phone_id;
        ofstr.close();
    }
}

void Smartphone::addPhone()
{
    PhoneString();
    ofstream ofs;
    ofs.open("smartphones.txt", ios::app);
    if (ofs.is_open() == true)
    {
        ofs << data_phone_string;
    }
    ofs.close();
    data_phone_string.clear();
}
void Smartphone::PhoneString()
{
    stringstream ss;
    if (!(phone_id == -1))
    {
        ss << phone_id << ';'
            << operation_sys << ';'
            << phone_name << ';'
            << model << ';'
            << release_date << ';'
            << phone_size << ';'
            << phone_proccesor << ';'
            << phone_memory << ';'
            << num_of_camers << ';'
            << price << ';'
            << num_copies << ';' << endl;

        data_phone_string = ss.str();
    }
}
void Smartphone::deletePhone()
{
    int a, id, b;
    cout << "��� ��������� ��������� ��������� �� ������ ������������" << endl;
    cout << "��������� �������(1) �� ������� ������� ���������(2)" << endl;
    phoneSearch();
    ifstream ifs("Smartphones.txt");
    ofstream ofs("SmartphonesTemp.txt");
    cout << "������ ID ���������, ����� ������ ��������: " << endl;
    cin >> id;
    cout << "�� ����� ������ �������� �������� �������� � ��� ��� ����� ����������? ��� (1) " << endl;
    cout << "��� ������� �������� �������� ���� ��� ���� ����� : " << endl;
    cin >> b;
    if (b == 1)
    {
        while (!ifs.eof())
        {
            getline(ifs, data_phone_string);
            dividePhoneDataStrings();
            if (phone_id != id)
            {
                ofs << data_phone_string << endl;
                data_phone_string.clear();
            }
        }
        ifs.close();
        ofs.close();
        remove("Smartphones.txt");
        rename("SmartphonesTemp.txt", "Smartphones.txt");
        cout << "�������� ��������!" << endl;
    }
    else
    {
        ofs.close();
        remove("SmartphonesTemp.txt");
        cout << "�������� �������!" << endl;
    }
    cin.ignore();
}
void Smartphone::changeCountPhones()
{
    cout << endl;
    cout << "���� ������� ��������� � ��� ������" << endl;
    cout << endl;
    int a,b,id,new_num_copies;
    cout << "��� ��������� ��������� ��������� �� ������ ������������" << endl;
    cout<< "��������� �������(1) �� ������� ������� ���������(2)" << endl;
    phoneSearch();
    cout << "ID ���������: "; cin >> id;
    cout << "���� ������� ���� ��������� � ID =  "<<id<<" : "; cin >> new_num_copies;
    cout << "�� ������� �� ������ ������� ���� � ���� ������? ���(1) ͳ(2) ";
    cin >> b;
    if (b == 1)
    {
        ifstream ifs("Smartphones.txt");
        ofstream ofs("SmartphonesTemp.txt");
        while (!ifs.eof())
        {
            getline(ifs, data_phone_string);
            dividePhoneDataStrings();
            if (phone_id != id)
            {
                ofs << data_phone_string << endl;
                data_phone_string.clear();
            }
            else
            {
                num_copies += new_num_copies;
                PhoneString();
                ofs << data_phone_string;
                data_phone_string.clear();
                cout << endl;
                printData();
                cout << endl;
            }
        }
        ifs.close();
        ofs.close();
        remove("Smartphones.txt");
        rename("SmartphonesTemp.txt", "Smartphones.txt");
        cout << "ʳ������ ������ ������!" << endl;
    }
    else
    {
        cout << "�������� ���������" << endl;
    }
}

   




void Smartphone::dividePhoneDataStrings()
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
void Smartphone::getPhoneInfo()
{
    generateId();
    cout << "ID ���������: " << phone_id << endl;
    cout << "������ ���������� ��� ����� ��������:\n";
    cout << "���������� �������:  ";  (cin >> operation_sys).ignore();
    cout << "�����: "; getline(cin, phone_name);
    cout << "������ : "; getline(cin, model);
    cout << "����� (������: ���������������������): "; getline(cin, phone_size);
    cout << "���������: "; getline(cin, phone_proccesor);
    cout << "���� �������: "; cin >> release_date;
    cout << "�������� ���'��� : "; cin >> phone_memory;
    cout << "ʳ������ �����: "; cin >> num_of_camers;
    cout << "ֳ��: "; cin >> price;
    cout << "ʳ������ �� �����: "; cin >> num_copies;
    cout << "\n";
    cin.ignore(255, '\n');
}
void Smartphone::titleData()
{
    cout.setf(ios::left);
    cout.fill(' ');
    cout.width(6);
    cout << "id";
    cout.width(20);
    cout << "���������� �������";
    cout.width(15);
    cout << "�����";
    cout.width(20);
    cout << "������";
    cout.width(15);
    cout << "���� �������";
    cout.width(15);
    cout << "�����";
    cout.width(15);
    cout << "���������";
    cout.width(20);
    cout << "�������� ���'���";
    cout.width(20);
    cout << "ʳ������ �����";
    cout.width(10);
    cout << "ֳ��";
    cout.width(15);
    cout << "K������� �� �����" << endl;
}
void Smartphone::dataPhoneData()
{
    cout.setf(ios::left);
    cout.fill(' ');
    cout.width(6);
    cout << phone_id;
    cout.width(20);
    cout << operation_sys;
    cout.width(15);
    cout << phone_name;
    cout.width(20);
    cout << model;
    cout.width(15);
    cout << release_date;
    cout.width(15);
    cout << phone_size;
    cout.width(15);
    cout << phone_proccesor;
    cout.width(20);
    cout << phone_memory;
    cout.width(20);
    cout << num_of_camers;
    cout.width(10);
    cout << price;
    cout.width(15);
    cout << num_copies;
    cout << endl;
}
void Smartphone::printAllPhoneData()
{
    cout << "+--------------------+" << endl;
    cout << "| ������� �������Ͳ� |" << endl;
    cout << "+--------------------+" << endl;
    titleData();
    ifstream ifs("smartphones.txt");
    while (!ifs.eof())
    {
        getline(ifs, data_phone_string);
        dividePhoneDataStrings();
        if (phone_id != -1)
        {
            dataPhoneData();
        }
        data_phone_string.clear();
    }
    ifs.close();
}
void Smartphone::printData()
{
    cout << "ID ���������: " << phone_id << endl;
    cout << "���������� �������:  ";  cout << operation_sys << endl;
    cout << "�����: "; cout << phone_name << endl;
    cout << "������ : "; cout << model << endl;
    cout << "���� �������: "; cout << release_date << endl;
    cout << "����� (������: ���������������������): "; cout << phone_size << endl;
    cout << "���������: "; cout << phone_proccesor << endl;
    cout << "�������� ���'��� : "; cout << phone_memory << endl;
    cout << "ʳ������ �����: "; cout << num_of_camers << endl;
    cout << "ֳ��: "; cout << price << endl;
    cout << "ʳ������ �� �����: "; cout << num_copies << endl;
};
void Smartphone::phoneSearch()
{
    char ch_key;
    cout << "+------------------+" << endl;
    cout << "| ����� �������Ͳ� |" << endl;
    cout << "+------------------+" << endl;
    cout << "������ �������� ����� �� �������� ������ (1) �� �� �������� (2)?" << endl;
    cout << "1 - ����� �� ������� ������" << endl;
    cout << "2 - ����������� ������" << endl;
    cout << "3 - ������� ������� ���������(�������������!!!)" << endl;
    switch ((ch_key = _getch()))
    {
    case '1':
        queryOutputPhones();
        cout << endl;
        break;
    case '2':
        dataPhoneFilter();
        cout << endl;
        break;
    case '3':
        printAllPhoneData();
        cout << endl;
        break;
    default:
        cout << "�������." << endl;
        break;
    }

}
void Smartphone::queryOutputPhones()
{
    ifstream ifs("smartphones.txt");
    string temp, line;
    int k = 0;
    cout << "������ ������� ����� ��� ������� ����� (�����, ������, ��, ���������) ��� �������� ����� � ��" << endl;
    cin >> temp;
    cout << "����� �� �������� ������ \"" << temp << "\"" << endl;
    titleData();
    while (!ifs.eof())
    {
        getline(ifs, line);
        if (line.find(temp) != string::npos)
        {
            k++;
            data_phone_string = line;
            dividePhoneDataStrings();
            dataPhoneData();
        }
    }
    data_phone_string.clear();
    if (k == 0)
        cout << "�� ����� ������� ����� �� ��������!" << endl;
    ifs.close();
};

void Smartphone::filterByDate()
{
    int year_start, year_finish;
    ifstream ifs("smartphones.txt");
    string line;
    cout << "���������� ��: "; cin >> year_start;
    cout << "ʳ������ ��: "; cin >> year_finish;
    if (year_start <= year_finish)
    {
        cout << "��������� � " << year_start << " �� " << year_finish << endl;
        titleData();
        while (!ifs.eof())
        {
            getline(ifs, line);
            data_phone_string = line;
            dividePhoneDataStrings();
            if (release_date >= year_start && release_date <= year_finish)
            {
                dataPhoneData();
            }
        }
        ifs.close();
    }
    else
    {
        cout << "������ ������� ������!" << endl;
    }

}
void Smartphone::filterByMember()
{
    int memory_min, memory_max;
    ifstream ifs("smartphones.txt");
    string line;
    cout << "̲Ͳ������ ������� �������� ���'��(� ���������): "; cin >> memory_min;
    cout << "����������� ������� �������� ���'��(� ���������):: "; cin >> memory_max;
    cout << "�������� ���'��� (� ���������) �� " << memory_min << " �� " << memory_max << endl;
    if (memory_min <= memory_max)
    {
        titleData();
        while (!ifs.eof())
        {
            getline(ifs, line);
            data_phone_string = line;
            dividePhoneDataStrings();
            if (phone_memory >= memory_min && phone_memory <= memory_max)
            {
                dataPhoneData();
            }
        }
        ifs.close();
    }
    else
    {
        cout << "������ ������� ������!" << endl;
    }
}
void Smartphone::filterByPrice()
{
    int price_min, price_max;
    ifstream ifs("smartphones.txt");
    string line;
    cout << "̳������� ����: "; cin >> price_min;
    cout << "����������� ����: "; cin >> price_max;
    cout << "��������� ����� ��  " << price_min << " �� " << price_max << endl;
    if (price_min <= price_max)
    {
        titleData();
        while (!ifs.eof())
        {
            getline(ifs, line);
            data_phone_string = line;
            dividePhoneDataStrings();
            if (price >= price_min && price <= price_max)
            {
                dataPhoneData();
            }
        }
        ifs.close();
    }
    else
    {
        cout << "������ ������� ������!" << endl;
    }
}
void Smartphone::filterByCamera()
{
    int camera_count;
    ifstream ifs("smartphones.txt");
    string line;
    cout << "ʳ������ ����� � ��������: "; cin >> camera_count;
    cout << "��������� � " << camera_count << " ��������" << endl;
    titleData();
    while (!ifs.eof())
    {
        getline(ifs, line);
        data_phone_string = line;
        dividePhoneDataStrings();
        if (camera_count == num_of_camers)
        {
            dataPhoneData();
        }
    }
    ifs.close();
}

void Smartphone::dataPhoneFilter()
{
    char change;
    bool filter_menu = true;
    cout << endl;
    cout << "1 - Գ���� �� ����� �������" << endl;
    cout << "2 - Գ���� �� ��������� ���'���" << endl;
    cout << "3 - Գ���� �� �����" << endl;
    cout << "4 - Գ���� �� ������� �����" << endl;
    cout << "ESC - ����� � ���� \"������ � ����� ������ ���������\"" << endl;
    while (filter_menu)
    {
        switch ((change = _getch()))
        {
        case '1':
            filterByDate();
            filter_menu = false;
            break;
        case '2':
            filterByMember();
            filter_menu = false;
            break;
        case '3':
            filterByPrice();
            filter_menu = false;
            break;
        case '4':
            filterByCamera();
            filter_menu = false;
            break;
        case 27:
            filter_menu = false;
            break;
        default:
            cout << "���� �� �����������!\n";
            break;
        }
    }
}
void Smartphone::Calculator()
{
    int phone_count = 0, total_price = 0, sales;
    cout << "+-------------+" << endl;
    cout << "| ��������ֲ� |" << endl;
    cout << "+-------------+" << endl;
    ifstream ifs("Smartphones.txt");
    cout.setf(ios::left);
    cout.fill(' ');
    cout.width(6);
    cout << "id";
    cout.width(15);
    cout << "�����";
    cout.width(20);
    cout << "������";
    cout.width(10);
    cout << "ֳ��";
    cout.width(25);
    cout << "K������� �� �����";
    cout.width(20);
    cout << "ֳ�� * ʳ������" << endl;
    cout << "+------------------------------------------------------------------------------------------+" << endl;
    while (!ifs.eof())
    {
        getline(ifs, data_phone_string);
        dividePhoneDataStrings();
        cout.setf(ios::left);
        cout.fill(' ');
        cout.width(6);
        cout << phone_id;
        cout.width(15);
        cout << phone_name;
        cout.width(20);
        cout << model;
        cout.width(10);
        cout << price;
        cout.width(25);
        cout << num_copies;
        cout.width(20);
        cout << num_copies * price;
        cout << endl;
        total_price += num_copies * price;
        phone_count += num_copies;
        data_phone_string.clear();

    }
    cout << "+------------------------------------------------------------------------------------------+" << endl;
    cout << "��������� � �������: " << phone_count << endl;
    cout << "������� ���� ��� ���������: " << total_price << endl;
    ifstream ifs_sales("sales_revenue.txt");
    ifs_sales >> sales;
    cout << "�������� � ������� ���������: " << sales << endl;
    ifs_sales.close();
    ifs.close();
}