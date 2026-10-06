#define _CRT_SECURE_NO_WARNINGS

#include "Marsh.h"
#include "sort.h"

#include <iostream>
#include <cstdio>
#include <cstring>
#include <clocale>
#include <windows.h>
#include <fstream>

using namespace std;

void fixConsoleEncoding()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    setlocale(LC_ALL, "russian");
}

void readFromTextFile(
    const char* filename,
    Marsh arr[],
    int size
)
{
    ifstream file(filename);

    if (!file)
    {
        cerr << "Ошибка открытия файла "
            << filename << endl;

        exit(1);
    }

    for (int i = 0; i < size; i++)
    {
        if (!(file >> arr[i]))
        {
            cerr << "Ошибка чтения данных из файла!"
                << endl;

            file.close();
            exit(1);
        }
    }

    file.close();
}

void writeToBinaryFile(
    const char* filename,
    Marsh arr[],
    int size
)
{
    FILE* file = fopen(filename, "wb");

    if (!file)
    {
        cerr << "Ошибка открытия бинарного файла!"
            << endl;

        exit(1);
    }

    fwrite(
        arr,
        sizeof(Marsh),
        size,
        file
    );

    fclose(file);
}

void readFromBinaryFile(
    const char* filename,
    Marsh arr[],
    int size
)
{
    FILE* file = fopen(filename, "rb");

    if (!file)
    {
        cerr << "Ошибка открытия бинарного файла!"
            << endl;

        exit(1);
    }

    size_t readCount = fread(
        arr,
        sizeof(Marsh),
        size,
        file
    );

    if (readCount != size)
    {
        cerr << "Прочитано "
            << readCount
            << " элементов вместо "
            << size << endl;
    }

    fclose(file);
}

void printByDestination(
    Marsh arr[],
    int size,
    const char* dest
)
{
    bool found = false;

    for (int i = 0; i < size; i++)
    {
        if (strcmp(arr[i].name2, dest) == 0)
        {
            cout << arr[i] << endl;

            found = true;
        }
    }

    if (!found)
    {
        cout << "Нет маршрутов, следующих в пункт "
            << dest << endl;
    }
}

int main()
{
    fixConsoleEncoding();

    const int SIZE = 8;

    Marsh marshes[SIZE];

    readFromTextFile(
        "text.txt",
        marshes,
        SIZE
    );

    cout << "Исходные данные:" << endl;

    for (int i = 0; i < SIZE; i++)
    {
        cout << marshes[i] << endl;
    }

    insertionSort(
        marshes,
        SIZE,
        Marsh::compareNumber
    );

    // Другие варианты сортировки:

    // bubbleSort(
    //     marshes,
    //     SIZE,
    //     Marsh::compareNumber
    // );

    // selectionSort(
    //     marshes,
    //     SIZE,
    //     Marsh::compareNumber
    // );

    // shellSort(
    //     marshes,
    //     SIZE,
    //     Marsh::compareNumber
    // );

    // combSort(
    //     marshes,
    //     SIZE,
    //     Marsh::compareNumber
    // );

    cout << "\nПосле сортировки:" << endl;

    for (int i = 0; i < SIZE; i++)
    {
        cout << marshes[i] << endl;
    }

    writeToBinaryFile(
        "marsh.bin",
        marshes,
        SIZE
    );

    cout << "\nМассив записан в marsh.bin"
        << endl;

    Marsh marshesFromBin[SIZE];

    readFromBinaryFile(
        "marsh.bin",
        marshesFromBin,
        SIZE
    );

    cout << "\nДанные из бинарного файла:"
        << endl;

    for (int i = 0; i < SIZE; i++)
    {
        cout << marshesFromBin[i] << endl;
    }

    char dest[20];

    cout << "\nВведите пункт назначения: ";

    cin >> dest;

    cout << "Маршруты, следующие в "
        << dest << ":" << endl;

    printByDestination(
        marshesFromBin,
        SIZE,
        dest
    );

    return 0;
}
