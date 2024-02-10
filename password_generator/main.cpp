#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <windows.h>
using namespace std;

// ������� ��� ��������� ������
string generatePassword(int length, bool useUppercase, bool useDigits, bool useSpecialChars) {
    const string lowercaseChars = "abcdefghijklmnopqrstuvwxyz";
    const string uppercaseChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string digitChars = "0123456789";
    const string specialChars = "!@#$%^&*()_-+=<>?/";

    string allChars = lowercaseChars;
    if (useUppercase) allChars += uppercaseChars;
    if (useDigits) allChars += digitChars;
    if (useSpecialChars) allChars += specialChars;

    string password;
    int allCharsLength = allChars.length();

    srand(static_cast<unsigned int>(time(0)));

    for (int i = 0; i < length; ++i) {
        int randomIndex = rand() % allCharsLength;
        password += allChars[randomIndex];
    }

    return password;
}

// ������� ��� �������� "���" ��� "ͳ"
bool getYesOrNoInput(const string& message) {
    cout << message << " (y/n): ";
    char response;
    cin >> response;
    return (response == 'y' || response == 'Y');
}

int main() {
    // ������������ ������ ������� ��� ��������� ����
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int length;
    bool useUppercase, useDigits, useSpecialChars;

    // ��� ��������� ������
    cout << "������ ������� ������ (������������� �� 8 �� 128 �������): ";
    cin >> length;

    // �������� �� �������� ������� ������
    if (length < 8 || length > 128) {
        cerr << "������ ������� ������. ������������� �� 8 �� 128 �������. ������ �������� ��������." << endl;
        return 1; // ��������� ��� �������
    }

    useUppercase = getYesOrNoInput("��������������� ����� �����?");
    useDigits = getYesOrNoInput("��������������� �����?");
    useSpecialChars = getYesOrNoInput("��������������� ��������� �����?");

    // ��������� ������
    string password = generatePassword(length, useUppercase, useDigits, useSpecialChars);

    // ��������� ���������� �� �����
    cout << "������������ ������: " << password << endl;

    // ����� ���������� � ���� �� �������� �����������
    if (getYesOrNoInput("�������� ��������� � ����?")) {
        string filename;
        cout << "������ ��'� �����: ";
        cin >> filename;

        ofstream outputFile(filename);
        if (outputFile.is_open()) {
            outputFile << password << endl;
            cout << "��������� �������� � ���� '" << filename << "'" << endl;
            outputFile.close();
        }
        else {
            cerr << "������� �������� ����� ��� ������." << endl;
        }
    }

    return 0;
}
