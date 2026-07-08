#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <windows.h>

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

int salaryCalculationForPeriod(Rabotyaga& rabotyaga, int startYear, int startMonth, int endYear, int endMonth)
{
    int SumSalary = 0;
    for (int i = 0; i < counter; i++)
    {
        if (strcmp(rabotyagaList[i].tabelNumber, rabotyaga.tabelNumber) == 0)
        {
            if (rabotyagaList[i].year >= startYear && rabotyagaList[i].year <= endYear)
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

void RemoveFromWorkerList(Rabotyaga& rabotyaga)
{
    int indexToRemove = -1;
    for (int i = 0; i < counter; i++)
    {
        if (strcmp(rabotyagaList[i].tabelNumber, rabotyaga.tabelNumber) == 0)
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

void saveToFile()
{
    FILE* f;
    errno_t err = fopen_s(&f, "workers.dat", "wb");
    if (err != 0)
    {
        std::cout << "Ошибка открытия файла для записи!" << std::endl;
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

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    loadFromFile();

    Rabotyaga ivan("ivan1", "ivanov", "trampovich", "1", 2024, 3, 100);
    AddToWorkerList(ivan);
    Rabotyaga ivan2("ivan2", "ivanov", "trampovich", "1", 2025, 3, 120);
    AddToWorkerList(ivan2);
    Rabotyaga sanya("sanya", " ", " ", "2", 1, 1, 1);
    AddToWorkerList(sanya);
    Rabotyaga MishaXui("MishaXui", " ", " ", "3", 1, 1, 1);
    AddToWorkerList(MishaXui);

    RemoveFromWorkerList(MishaXui);

    for (int i = 0; i < counter; i++)
    {
        std::cout << rabotyagaList[i].name << std::endl;
    }

    int result = salaryCalculationForPeriod(ivan, 2020, 1, 2030, 1);
    std::cout << "Зарплата за период: " << result << std::endl;

    saveToFile();

    delete[] rabotyagaList;
    return 0;
}