#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>

const int nameLeangth = 30;
const int tabelNumberLeangth = 30;
const double tax = 0.12;
const int payPerHour = 100;
const int workerListSize = 30;
int counter = 0;


struct Rabotyaga
{
    char name[nameLeangth],secondNamne[nameLeangth],fatherName[nameLeangth],tabelNumber[tabelNumberLeangth];
    int year, month,workHours, overtimeWorkHours = 0;

    inline Rabotyaga() : year(0), month(0), workHours(0), overtimeWorkHours(0) 
    {
        name[0] = '\0';
        secondNamne[0] = '\0';
        fatherName[0] = '\0';
        tabelNumber[0] = '\0';
    }

    inline Rabotyaga(const char* _name) : year(0), month(0), workHours(0), overtimeWorkHours(0)
    {
        strncpy(name, _name, nameLeangth);
        secondNamne[0] = '\0';
        fatherName[0] = '\0';
        tabelNumber[0] = '\0';
    }

    inline Rabotyaga(const char* _name, const char* _secondName, const char* _fatherName, const char* _tabelNumber,int _year,int _month,int _workHours) :year(_year),month(_month),workHours(_workHours)
    {
        strncpy(name, _name, nameLeangth);
        strncpy(secondNamne, _secondName, nameLeangth);
        strncpy(fatherName, _fatherName, nameLeangth);
        strncpy(tabelNumber, _tabelNumber, nameLeangth);
        
        if (workHours>144)
        {
            overtimeWorkHours = workHours - 144;
            workHours = 144;
        }
    } 
};

Rabotyaga* rabotyagaList = new Rabotyaga[workerListSize];

int salaryCalculation(Rabotyaga rabotyaga)
{
    int salary = 0;
    salary = ((rabotyaga.workHours * payPerHour) + (rabotyaga.overtimeWorkHours * 2 * payPerHour)) * (1.00 - tax);

    return salary;
}

int salaryCalculationForPeriod(Rabotyaga rabotyaga,int startYear,int startMonth, int endYear, int endMonth)
{
    int SumSalary = 0;
    for (size_t i = 0; i < counter; i++)
    {
        if (strcmp(rabotyagaList[i].tabelNumber, rabotyaga.tabelNumber) == 0)
        {
            if (rabotyagaList[i].year>startYear&& rabotyagaList[i].year < endYear)
            {
                SumSalary += salaryCalculation(rabotyagaList[i]);
            }
        }
    }
    return SumSalary;
}

void AddToWorkerList(Rabotyaga& rabotyaga)
{
    rabotyagaList[counter] = rabotyaga;
    counter++;
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

    if (indexToRemove == -1) 
    {
        return;
    }

    for (int i = indexToRemove; i < counter - 1; i++) 
    {
        rabotyagaList[i] = rabotyagaList[i + 1];
    }

    counter--;
}

int main()
{
    Rabotyaga ivan("ivan1","ivanov","trampovich","1",2024,3,100);
    AddToWorkerList(ivan);
    Rabotyaga ivan2("ivan2", "ivanov", "trampovich", "1", 2025, 3, 120);
    AddToWorkerList(ivan2);
    Rabotyaga sanya("sanya", " ", " ", "2", 1, 1, 1);
    AddToWorkerList(sanya);
    Rabotyaga MishaXui("MishaXui", " ", " ", "3", 1, 1, 1);
    AddToWorkerList(MishaXui);

    RemoveFromWorkerList(MishaXui);
   
    for (size_t i = 0; i < counter; i++)
    {
        std::cout << rabotyagaList[i].name << " \n";
    }
    return salaryCalculationForPeriod(ivan,2020,1,2030,1);
}


