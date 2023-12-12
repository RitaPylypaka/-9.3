#pragma execution_character_set("utf-8")
#include <fstream>
#include <iostream>
#include <iomanip> 
#include <string>
#include <Windows.h>
using namespace std;
struct Bill {
    string platnika;
    string oderz;
    double suma;
};
void EnterData(Bill* array, int size) {
    for (int i = 0; i < size; ++i) {
        cout << "Товар " << i + 1 << ":" << endl;
        cout << "Рахунок платника: ";
        cin >> array[i].platnika;
        cout << "Рахунок одержувача: ";
        cin >> array[i].oderz;
        cout << "Сума: ";
        cin >> array[i].suma;
    }
}

void Print(const Bill* array, int size) {
    cout << "===========================================================" << endl;
    cout << "|  Рахунок платника  |  Рахунок одержувача  |  Сума, грн  |" << endl;
    cout << "-----------------------------------------------------------" << endl;
    for (int i = 0; i < size; ++i) {
        cout << "| " << setw(17) << left << array[i].platnika << " | "
            << setw(18) << left << array[i].oderz << " | "
            << setw(15) << right << fixed << setprecision(2) << array[i].suma << " |" << endl;
    }
    cout << "============================================================" << endl;
}
void SortByPlatnik(Bill* array, int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (array[i].platnika > array[j].platnika) {
                swap(array[i], array[j]);
            }
        }
    }
}
void SearchSum(const Bill* array, int size, const double& sum) {
    bool found = false;
    for (int i = 0; i < size; ++i) {
        if (array[i].suma == sum) {
            cout << "Розрахунковий рахунок платника: " << array[i].platnika << ", " << endl;
            cout << "Розрахунковий рахунок одержувача: " << array[i].oderz << ", Сума: " << array[i].suma << " грн" << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Інформації про суму '" << sum << "' не знайдено." << endl;
    }
}

// Функція для зчитування даних з файлу
void LoadFromFile(Bill*& p, int& N, const char* filename)
{
    delete[] p;                                   // знищили попередні дані 

    ifstream fin(filename, ios::binary);           // відкрили бінарний файл зчитування 

    fin.read((char*)&N, sizeof(N));                // прочитали кількість елементів 

    p = new Bill[N];                          // створили динамічний масив 

    for (int i = 0; i < N; i++)
        fin.read((char*)&p[i], sizeof(Bill)); // прочитали елементи масиву 

    fin.close();                                   // закрили файл 
}

// Функція для запису даних у файл
void SaveToFile(Bill* p, const int N, const char* filename) {
    ofstream fout(filename, ios::binary);            // відкрили бінарний файл запису 

    fout.write((char*)&N, sizeof(N));                // записали кількість елементів 

    for (int i = 0; i < N; i++)
        fout.write((char*)&p[i], sizeof(Bill)); // записали елементи масиву 

    fout.close();                                    // закрили файл 
}
int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int N;
    cout << "Введіть N: "; cin >> N;

    Bill* p = new Bill[N];

    int found;
    char filename[100];
    string iproduct;
    double sum;

    int menuItem;
    do {
        cout << endl << endl << endl;
        cout << "Виберіть дію:" << endl << endl;
        cout << "  [1] - введення даних з клавіатури" << endl;
        cout << "  [2] - вивід даних на екран" << endl;
        cout << "  [3] - фізично впорядкувати масив" << endl;
        cout << "  [4] - пошук суми" << endl;
        cout << "  [5] - запис даних у файл" << endl;
        cout << "  [6] - зчитування даних із файлу" << endl << endl;
        cout << "  [0] - вихід та завершення роботи програми" << endl << endl;
        cout << "Введіть значення: "; cin >> menuItem;
        cout << endl << endl << endl;
        switch (menuItem)
        {
        case 1:
            EnterData(p, N);
            break;
        case 2:
            Print(p, N);
            break;
        case 3:
            SortByPlatnik(p, N);

            break;
        case 4:
            cout << "Введіть ключі пошуку:" << endl;
            cin.get();
            cin.sync();

            cout << "    сума: "; cin >> sum;
            cout << endl;
            SearchSum(p, N, sum);
            break;
        case 5:
            cin.get();
            cin.sync();

            cout << "Введіть ім'я файлу: "; cin.getline(filename, 99);
            SaveToFile(p, N, filename);

            break;
        case 6:
            cin.get();
            cin.sync();

            cout << "Введіть ім'я файлу: "; cin.getline(filename, 99);
            LoadFromFile(p, N, filename);

            break;
        case 0:
            break;
        default:
            cout << "Ви ввели помилкове значення! "
                "Слід ввести число - номер вибраного пункту меню" << endl;
        }
    } while (menuItem != 0);

    return 0;
}