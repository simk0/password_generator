#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <windows.h>
using namespace std;

// Функція для генерації паролю
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

// Функція для введення "Так" або "Ні"
bool getYesOrNoInput(const string& message) {
    cout << message << " (y/n): ";
    char response;
    cin >> response;
    return (response == 'y' || response == 'Y');
}

int main() {
    // Встановлення кодової сторінки для української мови
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int length;
    bool useUppercase, useDigits, useSpecialChars;

    // Ввід параметрів паролю
    cout << "Введіть довжину паролю (рекомендовано від 8 до 128 символів): ";
    cin >> length;

    // Перевірка на валідність довжини паролю
    if (length < 8 || length > 128) {
        cerr << "Невірна довжина паролю. Рекомендовано від 8 до 128 символів. Введіть коректне значення." << endl;
        return 1; // Повертаємо код помилки
    }

    useUppercase = getYesOrNoInput("Використовувати великі літери?");
    useDigits = getYesOrNoInput("Використовувати цифри?");
    useSpecialChars = getYesOrNoInput("Використовувати спеціальні знаки?");

    // Генерація паролю
    string password = generatePassword(length, useUppercase, useDigits, useSpecialChars);

    // Виведення результату на екран
    cout << "Згенерований пароль: " << password << endl;

    // Запис результату в файл за бажанням користувача
    if (getYesOrNoInput("Записати результат в файл?")) {
        string filename;
        cout << "Введіть ім'я файлу: ";
        cin >> filename;

        ofstream outputFile(filename);
        if (outputFile.is_open()) {
            outputFile << password << endl;
            cout << "Результат записано в файл '" << filename << "'" << endl;
            outputFile.close();
        }
        else {
            cerr << "Помилка відкриття файлу для запису." << endl;
        }
    }

    return 0;
}
