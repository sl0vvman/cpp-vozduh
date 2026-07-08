#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <algorithm>

const int nameLength = 30;
const int tabelNumberLength = 30;
const double tax = 0.12;
const int payPerHour = 100;
const int workerListSize = 30;
int counter = 0;

struct Rabotyaga
{
    char name[nameLength];
    char secondName[nameLength];
    char fatherName[nameLength];
    char tabelNumber[tabelNumberLength];
    int year, month, workHours, overtimeWorkHours;

    inline Rabotyaga() : year(0), month(0), workHours(0), overtimeWorkHours(0)
    {
        name[0] = '\0';
        secondName[0] = '\0';
        fatherName[0] = '\0';
        tabelNumber[0] = '\0';
    }

    inline Rabotyaga(const char* _name) : year(0), month(0), workHours(0), overtimeWorkHours(0)
    {
        strncpy(name, _name, nameLength);
        secondName[0] = '\0';
        fatherName[0] = '\0';
        tabelNumber[0] = '\0';
    }

    inline Rabotyaga(const char* _name, const char* _secondName, const char* _fatherName, const char* _tabelNumber, int _year, int _month, int _workHours)
        : year(_year), month(_month), workHours(_workHours), overtimeWorkHours(0)
    {
        strncpy(name, _name, nameLength);
        strncpy(secondName, _secondName, nameLength);
        strncpy(fatherName, _fatherName, nameLength);
        strncpy(tabelNumber, _tabelNumber, nameLength);

        if (workHours > 144)
        {
            overtimeWorkHours = workHours - 144;
            workHours = 144;
        }
    }
};

Rabotyaga* rabotyagaList = new Rabotyaga[workerListSize];

int salaryCalculation(const Rabotyaga& rabotyaga)
{
    return ((rabotyaga.workHours * payPerHour) + (rabotyaga.overtimeWorkHours * 2 * payPerHour)) * (1.00 - tax);
}
int dataCheck(int startYear, int startMonth, int endYear, int endMonth,int currYear,int currMonth) 
{
    if (currYear >= startYear && currYear <= endYear)
    {
        if (currYear == startYear)
        {
            if (currMonth>startMonth)
            {
                return 1;
            }
        }
        else if (currYear == endYear)
        {
            if (currMonth<endMonth)
            {
                return 1;
            }
        }
        else
        {
            return 1;
        }
    }
    return 0;
}
int salaryCalculationForPeriod(const char* _tabelnumber, int startYear, int startMonth, int endYear, int endMonth)
{
    int SumSalary = 0;
    for (int i = 0; i < counter; i++)
    {
        if (strcmp(rabotyagaList[i].tabelNumber, _tabelnumber) == 0)
        {
            if (dataCheck(startYear, startMonth, endYear, endMonth, rabotyagaList[i].year, rabotyagaList[i].month))
            {
                SumSalary += salaryCalculation(rabotyagaList[i]);
            }
        }
    }
    return SumSalary;
}

void AddToWorkerList(Rabotyaga& rabotyaga)
{
    if (counter < workerListSize)
    {
        rabotyagaList[counter] = rabotyaga;
        counter++;
    }
}

void RemoveFromWorkerList(const char* _tabelnumber)
{
    int indexToRemove = -1;
    for (int i = 0; i < counter; i++)
    {
        if (strcmp(rabotyagaList[i].tabelNumber, _tabelnumber) == 0)
        {
            indexToRemove = i;
            break;
        }
    }

    if (indexToRemove == -1) return;

    for (int i = indexToRemove; i < counter - 1; i++)
    {
        rabotyagaList[i] = rabotyagaList[i + 1];
    }
    counter--;
}

void printList() {
    for (size_t i = 0; i < counter; i++)
    {
        std::cout << "Сотрудник №" << i + 1 << std::endl;
        std::cout << "Имя: " << rabotyagaList[i].name << std::endl;
        std::cout << "Фамилия: " << rabotyagaList[i].secondName << std::endl;
        std::cout << "Отчество: " << rabotyagaList[i].fatherName << std::endl;
        std::cout << "Табельный номер: " << rabotyagaList[i].tabelNumber << std::endl;
        std::cout << "Год: " << rabotyagaList[i].year << std::endl;
        std::cout << "Месяц: " << rabotyagaList[i].month << std::endl;
        std::cout << "Проработанные часы: " << rabotyagaList[i].workHours << std::endl;
        if (rabotyagaList[i].overtimeWorkHours != 0) {
            std::cout << "Имеет сверхурочные" << std::endl;
        }
        std::cout << "\n\n\n\n";
    }
}
void saveToFile()
{
    FILE* f;
    errno_t err = fopen_s(&f, "workers.dat", "wb");
    if (err != 0)
    {
        std::cout << "anlak" << std::endl;
        return;
    }

    fwrite(&counter, sizeof(int), 1, f);

    for (int i = 0; i < counter; i++)
    {
        fwrite(&rabotyagaList[i], sizeof(Rabotyaga), 1, f);
    }

    fclose(f);
    std::cout << "Данные сохранены в файл workers.dat" << std::endl;
}

void loadFromFile()
{

    FILE* f;
    errno_t err = fopen_s(&f, "workers.dat", "rb");
    if (err != 0)
    {
        std::cout << "Файл не найден или поврежден" << std::endl;
        return;
    }

    fread(&counter, sizeof(int), 1, f);

    for (int i = 0; i < counter; i++)
    {
        fread(&rabotyagaList[i], sizeof(Rabotyaga), 1, f);
    }

    fclose(f);
    std::cout << "Данные загружены из файла workers.dat" << std::endl;
}

void secondNameSort() {
    for (size_t i = 0; i < counter - 1; i++)
    {
        int indexMax = 0;
        for (size_t j = 0; j < counter - 1; j++)
        {

            if (strcmp(rabotyagaList[j].secondName, rabotyagaList[indexMax].secondName) == 1)
            {
                indexMax = j;
            }
        }
        std::swap(rabotyagaList[i], rabotyagaList[indexMax]);

    }
}


int main()
{
    Rabotyaga a("evgen", "babaiko", "", "", 2000, 2000, 2000);
    Rabotyaga b("vlados", "cicka", "", "", 2000, 2000, 2000);
    AddToWorkerList(b);
    AddToWorkerList(a);
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    loadFromFile();

    secondNameSort();
    bool flag = true;
    do {
        int ans;
        std::cout << "1 - Добавить запись" << std::endl;
        std::cout << "2 - Удалить запись" << std::endl;
        std::cout << "3 - Рассчитать зар. плату за период" << std::endl;
        std::cout << "4 - Вывести всех сотрудников (отсортированы по фамилиям)" << std::endl;
        std::cout << "5 - Выход" << std::endl;
        std::cin >> ans;
        switch (ans) {
        case 1: {
            char _name[nameLength], _secondNamne[nameLength], _fatherName[nameLength], _tabelNumber[tabelNumberLength];
            int _year, _month, _workHours;
            std::cout << "Введите фамилию сотрудника: " << std::endl;
            std::cin >> _secondNamne;
            std::cout << "Введите имя сотрудника: " << std::endl;
            std::cin >> _name;
            std::cout << "Введите отчество сотрудника: " << std::endl;
            std::cin >> _fatherName;
            std::cout << "Введите табельный номер сотрудника: " << std::endl;
            std::cin >> _tabelNumber;
            std::cout << "Введите год: " << std::endl;
            std::cin >> _year;
            std::cout << "Введите за который месяц: " << std::endl;
            std::cin >> _month;
            std::cout << "Введите кол-во часов, проработанных сотрудником: " << std::endl;
            std::cin >> _workHours;
            Rabotyaga tmp(_name, _secondNamne, _fatherName, _tabelNumber, _year, _month, _workHours);
            AddToWorkerList(tmp);
            secondNameSort();
            break;
        }
        case 2:
        {
            char _tabelnumber[30];
            std::cout << "Введите табельный номер сотрудника, которого хотите удалить: " << std::endl;
            std::cin >> _tabelnumber;
            RemoveFromWorkerList(_tabelnumber);
            break;

        }
        case 3:
        {
            int _startYear, _startMonth, _endYear, _endMonth;
            char _tabelnumber[tabelNumberLength];
            std::cout << "Введите табельный номер сотрудника: " << std::endl;
            std::cin >> _tabelnumber;
            std::cout << "Введите начальный год: " << std::endl;
            std::cin >> _startYear;
            std::cout << "Введите начальный месяц: " << std::endl;
            std::cin >> _startMonth;
            std::cout << "Введите конечный год: " << std::endl;
            std::cin >> _endYear;
            std::cout << "Введите конечный месяц: " << std::endl;
            std::cin >> _endMonth;
            salaryCalculationForPeriod(_tabelnumber, _startYear, _startMonth, _endYear, _endMonth);
            break;
        }
        case 4: {
            printList();
            break;
        }
        case 5: {
            flag = false;
            break;
        }
        default: std::cout << "Неправильный номер операции" << std::endl;
       }

    } while (flag);

    saveToFile();

    delete[] rabotyagaList;
    return 0;
}
zhopa;