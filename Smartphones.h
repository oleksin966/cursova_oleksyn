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
    //Генерування унікальних ключів
    void generateId();

    //Добавити/видалити предмет з бази данних
    void addPhone();
    void deletePhone();
 
    //Функції для виводу данних
    void printAllPhoneData();
    void printData();
    void titleData();
    void dataPhoneData();

    //Функція для вводу данних
    void getPhoneInfo();

    //Допоміжні функції
    void dividePhoneDataStrings();
    void queryOutputPhones();
    void PhoneString();

    //Фільтри за полями та пошук
    void dataPhoneFilter();
    void filterByDate();
    void filterByMember();
    void filterByPrice();
    void filterByCamera();
    void phoneSearch();

    //Внести зміни в базу данних
    void changeCountPhones();

    //Облік
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
    cout << "Для знайдення потрібного Смартфона ви можете скористатися" << endl;
    cout << "пошуковим запитом(1) чи вивести таблицю Смартфонів(2)" << endl;
    phoneSearch();
    ifstream ifs("Smartphones.txt");
    ofstream ofs("SmartphonesTemp.txt");
    cout << "Введіть ID смартфона, якого бажаєте видалити: " << endl;
    cin >> id;
    cout << "Ви точно бажаєте видалити вибраний смартфон і всю про нього інформацію? Так (1) " << endl;
    cout << "Щоб відмінити операцію натисніть будь яку іншу цифру : " << endl;
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
        cout << "Смартфон видалено!" << endl;
    }
    else
    {
        ofs.close();
        remove("SmartphonesTemp.txt");
        cout << "Операцію відмінено!" << endl;
    }
    cin.ignore();
}
void Smartphone::changeCountPhones()
{
    cout << endl;
    cout << "Зміна кількості Смартфонів в базі данних" << endl;
    cout << endl;
    int a,b,id,new_num_copies;
    cout << "Для знайдення потрібного Смартфона ви можете скористатися" << endl;
    cout<< "пошуковим запитом(1) чи вивести таблицю Смартфонів(2)" << endl;
    phoneSearch();
    cout << "ID Смартфона: "; cin >> id;
    cout << "Нова кількість копій Смартфона з ID =  "<<id<<" : "; cin >> new_num_copies;
    cout << "Ви впевнені що хочете внестии зміни в базу данних? Так(1) Ні(2) ";
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
        cout << "Кількість успішно змінена!" << endl;
    }
    else
    {
        cout << "Операція скасована" << endl;
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
    cout << "ID смартфона: " << phone_id << endl;
    cout << "Введіть інформація про новий смартфон:\n";
    cout << "Операційна система:  ";  (cin >> operation_sys).ignore();
    cout << "Назва: "; getline(cin, phone_name);
    cout << "Модель : "; getline(cin, model);
    cout << "Розмір (формат: довжинаХширинаХвисота): "; getline(cin, phone_size);
    cout << "Процессор: "; getline(cin, phone_proccesor);
    cout << "Дата випуску: "; cin >> release_date;
    cout << "Загальна пам'ять : "; cin >> phone_memory;
    cout << "Кількість камер: "; cin >> num_of_camers;
    cout << "Ціна: "; cin >> price;
    cout << "Кількість на складі: "; cin >> num_copies;
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
    cout << "Операційна система";
    cout.width(15);
    cout << "Назва";
    cout.width(20);
    cout << "Модель";
    cout.width(15);
    cout << "Дата випуску";
    cout.width(15);
    cout << "Розмір";
    cout.width(15);
    cout << "Процессор";
    cout.width(20);
    cout << "Загальна пам'ять";
    cout.width(20);
    cout << "Кількість камер";
    cout.width(10);
    cout << "Ціна";
    cout.width(15);
    cout << "Kількість на складі" << endl;
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
    cout << "| ТАБЛИЦЯ СМАРТФОНІВ |" << endl;
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
    cout << "ID смартфона: " << phone_id << endl;
    cout << "Операційна система:  ";  cout << operation_sys << endl;
    cout << "Назва: "; cout << phone_name << endl;
    cout << "Модель : "; cout << model << endl;
    cout << "Дата випуску: "; cout << release_date << endl;
    cout << "Розмір (формат: довжинаХширинаХвисота): "; cout << phone_size << endl;
    cout << "Процессор: "; cout << phone_proccesor << endl;
    cout << "Загальна пам'ять : "; cout << phone_memory << endl;
    cout << "Кількість камер: "; cout << num_of_camers << endl;
    cout << "Ціна: "; cout << price << endl;
    cout << "Кількість на складі: "; cout << num_copies << endl;
};
void Smartphone::phoneSearch()
{
    char ch_key;
    cout << "+------------------+" << endl;
    cout << "| ПОШУК СМАРТФОНІВ |" << endl;
    cout << "+------------------+" << endl;
    cout << "Бажаєте здійснити пошук за введеним словом (1) чи за фільтром (2)?" << endl;
    cout << "1 - пошук за веденим словом" << endl;
    cout << "2 - використати фільтр" << endl;
    cout << "3 - вивести таблицю смартфонів(рекомендовано!!!)" << endl;
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
        cout << "Помилка." << endl;
        break;
    }

}
void Smartphone::queryOutputPhones()
{
    ifstream ifs("smartphones.txt");
    string temp, line;
    int k = 0;
    cout << "Введіть ключове слово або частину слова (назву, модель, ОС, процессор) щоб здійснити запит в БД" << endl;
    cin >> temp;
    cout << "Запит за введеним словом \"" << temp << "\"" << endl;
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
        cout << "За вашим запитом нічого не знайдено!" << endl;
    ifs.close();
};

void Smartphone::filterByDate()
{
    int year_start, year_finish;
    ifstream ifs("smartphones.txt");
    string line;
    cout << "Початковий рік: "; cin >> year_start;
    cout << "Кінцевий рік: "; cin >> year_finish;
    if (year_start <= year_finish)
    {
        cout << "Смартфони з " << year_start << " по " << year_finish << endl;
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
        cout << "Невірно заданий фільтр!" << endl;
    }

}
void Smartphone::filterByMember()
{
    int memory_min, memory_max;
    ifstream ifs("smartphones.txt");
    string line;
    cout << "МІНІМАЛЬНА кількість загальної пам'яті(в гігабайтах): "; cin >> memory_min;
    cout << "МАКСИМАЛЬНА кількість загальної пам'яті(в гігабайтах):: "; cin >> memory_max;
    cout << "Загальна пам'ять (в гігабайтах) від " << memory_min << " до " << memory_max << endl;
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
        cout << "Невірно заданий фільтр!" << endl;
    }
}
void Smartphone::filterByPrice()
{
    int price_min, price_max;
    ifstream ifs("smartphones.txt");
    string line;
    cout << "Мінімальна ціна: "; cin >> price_min;
    cout << "Максимальна ціна: "; cin >> price_max;
    cout << "Смартфони ціною від  " << price_min << " до " << price_max << endl;
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
        cout << "Невірно заданий фільтр!" << endl;
    }
}
void Smartphone::filterByCamera()
{
    int camera_count;
    ifstream ifs("smartphones.txt");
    string line;
    cout << "Кількість камер у смартфоні: "; cin >> camera_count;
    cout << "Смартфони з " << camera_count << " камерами" << endl;
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
    cout << "1 - Фільтр за датою випуску" << endl;
    cout << "2 - Фільтр за загальною пам'ятю" << endl;
    cout << "3 - Фільтр за ціною" << endl;
    cout << "4 - Фільтр за кількістю камер" << endl;
    cout << "ESC - Вихід в меню \"Робота з базою данних смартфонів\"" << endl;
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
            cout << "Ключ не підтримується!\n";
            break;
        }
    }
}
void Smartphone::Calculator()
{
    int phone_count = 0, total_price = 0, sales;
    cout << "+-------------+" << endl;
    cout << "| КАЛЬКУЛЯЦІЯ |" << endl;
    cout << "+-------------+" << endl;
    ifstream ifs("Smartphones.txt");
    cout.setf(ios::left);
    cout.fill(' ');
    cout.width(6);
    cout << "id";
    cout.width(15);
    cout << "Назва";
    cout.width(20);
    cout << "Модель";
    cout.width(10);
    cout << "Ціна";
    cout.width(25);
    cout << "Kількість на складі";
    cout.width(20);
    cout << "Ціна * Кількість" << endl;
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
    cout << "Смартфонів у магазині: " << phone_count << endl;
    cout << "Сумарна ціна всіх смартфонів: " << total_price << endl;
    ifstream ifs_sales("sales_revenue.txt");
    ifs_sales >> sales;
    cout << "Прибуток з продажу смартфонів: " << sales << endl;
    ifs_sales.close();
    ifs.close();
}