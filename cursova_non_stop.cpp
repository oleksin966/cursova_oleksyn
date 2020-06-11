// cursova_non_stop.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <conio.h>
#include <locale>
#include "windows.h"
#include "Smartphones.h"
#include "Administrator.h"
#include "Clients.h"
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
void ch1()
{
    char ch_key;
    bool sub_menu1 = true;
    while (sub_menu1)
    {
        cout << "+---------------------+" << endl;
        cout << "| ВХІД В АДМІН-ПАНЕЛЬ |" << endl;
        cout << "+---------------------+" << endl;
        cout << "1 - Увійти" << endl;
        cout << "Пароль : admin   Логін: admin"<<endl;
        cout << "ESC - Вихід в головне меню" << endl;
        switch ((ch_key = _getch()))
        {
        case '1':
            admin.AuthorizationAdmin();
            break;
        case 27:
            sub_menu1 = false;
            cout << "Вихід в головне меню\n";
            break;
        default:
            cout << "Ключ не підтримується!\n";
            break;
        }
    }
};
void ch2()
{
    char ch_key;
    bool sub_menu1 = true;
    while (sub_menu1)
    {
        cout << "+-------------------------+" << endl;
        cout << "| ВХІД/РЕЄСТРАЦІЯ КЛІЄНТА |" << endl;
        cout << "+-------------------------+" << endl;
        cout << "1 - Реєстрація" << endl;
        cout << "2 - Вхід" << endl;
        cout << "ESC - Вихід в головне меню" << endl;
        switch ((ch_key = _getch()))
        {
        case '1':
            client.Registration();
            break;
        case '2':
            client.Authorization();
            break;
        case 27:
            sub_menu1 = false;
            cout << "Вихід в головне меню\n";
            break;
        default:
            cout << "Ключ не підтримується!\n";
            break;
        }
    }
}


int main()
{

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char ch_key;
    bool main_menu = true;
    string line;
    while (main_menu)
    {
        cout << "ТОПОВИЙ ОНЛАЙН-МАГАЗИН З ПРОДАЖУ СМАРТФОНІВ: " << endl;
        ifstream ifs(admin.banner);
        while (!ifs.eof())
        {
            getline(ifs, line);
            cout << "\t"<<line << endl;
        }
        ifs.close();
        cout << "ДЛЯ ТОГО ЩОБ РОЗПОЧАТИ УВІЙДІТЬ АБО ЗАРЕЄСТРУЙТЕСЯ!" << endl;
        cout << "\t+-----------------------+ \t +------------------------+" << endl;
        cout << "\t| *** АДМІНІСТРАТОР *** | \t |     *** КЛІЄНТ ***     |"<< endl;
        cout << "\t+-----------------------+ \t +------------------------+" << endl;

        cout << endl;

        cout << "\t      ***********          \t\t*********** " << endl;
        cout << "\t      *    1    *          \t\t*    2    *" << endl;
        cout << "\t      ***********          \t\t*********** " << endl;

        switch ((ch_key = _getch()))
        {
        case '1':
            ch1();
            break;
        case '2':
            ch2();
            break;
        case 27:
            main_menu = false;
            cout << "Вихід з програми\n";
            break;
        default:
            cout << "Ключ не підтримується!\n";
            break;
        }
    }
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
