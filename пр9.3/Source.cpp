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
        cout << "����� " << i + 1 << ":" << endl;
        cout << "������� ��������: ";
        cin >> array[i].platnika;
        cout << "������� ����������: ";
        cin >> array[i].oderz;
        cout << "����: ";
        cin >> array[i].suma;
    }
}

void Print(const Bill* array, int size) {
    cout << "===========================================================" << endl;
    cout << "|  ������� ��������  |  ������� ����������  |  ����, ���  |" << endl;
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
            cout << "������������� ������� ��������: " << array[i].platnika << ", " << endl;
            cout << "������������� ������� ����������: " << array[i].oderz << ", ����: " << array[i].suma << " ���" << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "���������� ��� ���� '" << sum << "' �� ��������." << endl;
    }
}

// ������� ��� ���������� ����� � �����
void LoadFromFile(Bill*& p, int& N, const char* filename)
{
    delete[] p;                                   // ������� �������� ��� 

    ifstream fin(filename, ios::binary);           // ������� ������� ���� ���������� 

    fin.read((char*)&N, sizeof(N));                // ��������� ������� �������� 

    p = new Bill[N];                          // �������� ��������� ����� 

    for (int i = 0; i < N; i++)
        fin.read((char*)&p[i], sizeof(Bill)); // ��������� �������� ������ 

    fin.close();                                   // ������� ���� 
}

// ������� ��� ������ ����� � ����
void SaveToFile(Bill* p, const int N, const char* filename) {
    ofstream fout(filename, ios::binary);            // ������� ������� ���� ������ 

    fout.write((char*)&N, sizeof(N));                // �������� ������� �������� 

    for (int i = 0; i < N; i++)
        fout.write((char*)&p[i], sizeof(Bill)); // �������� �������� ������ 

    fout.close();                                    // ������� ���� 
}
int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int N;
    cout << "������ N: "; cin >> N;

    Bill* p = new Bill[N];

    int found;
    char filename[100];
    string iproduct;
    double sum;

    int menuItem;
    do {
        cout << endl << endl << endl;
        cout << "������� ��:" << endl << endl;
        cout << "  [1] - �������� ����� � ���������" << endl;
        cout << "  [2] - ���� ����� �� �����" << endl;
        cout << "  [3] - ������� ������������ �����" << endl;
        cout << "  [4] - ����� ����" << endl;
        cout << "  [5] - ����� ����� � ����" << endl;
        cout << "  [6] - ���������� ����� �� �����" << endl << endl;
        cout << "  [0] - ����� �� ���������� ������ ��������" << endl << endl;
        cout << "������ ��������: "; cin >> menuItem;
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
            cout << "������ ����� ������:" << endl;
            cin.get();
            cin.sync();

            cout << "    ����: "; cin >> sum;
            cout << endl;
            SearchSum(p, N, sum);
            break;
        case 5:
            cin.get();
            cin.sync();

            cout << "������ ��'� �����: "; cin.getline(filename, 99);
            SaveToFile(p, N, filename);

            break;
        case 6:
            cin.get();
            cin.sync();

            cout << "������ ��'� �����: "; cin.getline(filename, 99);
            LoadFromFile(p, N, filename);

            break;
        case 0:
            break;
        default:
            cout << "�� ����� ��������� ��������! "
                "��� ������ ����� - ����� ��������� ������ ����" << endl;
        }
    } while (menuItem != 0);

    return 0;
}