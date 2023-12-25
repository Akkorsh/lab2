// main.cpp
#include <iostream>
#include <cctype>
#include <locale>
#include <stdexcept> // Добавьте эту строку
#include "modAlphaCipher.h"

using namespace std;

bool isValid(const wstring& s);

int main(int argc, char** argv)
{
    locale loc("ru_RU.UTF-8");
    locale::global(loc);
    wstring key;
    wstring text;
    unsigned op;
    wcout << L"Шифр готов. Введите ключ: ";
    wcin >> key;

    try
    {
        if (!isValid(key))
        {
            cerr << "Неверный ключ\n";
            return 1;
        }

        wcout << "Ключ загружен\n";
        modAlphaCipher cipher(key);
        do
        {
            wcout << L"Шифр готов. Введите операцию (0-выход, 1-шифрование, 2-дешифрование): ";
            wcin >> op;

            if (op > 2)
            {
                wcout << "Недопустимая операция\n";
            }
            else if (op > 0)
            {
                wcout << L"Шифр готов. Введите текст: ";
                wcin >> text;

                try
                {
                    if (isValid(text))
                    {
                        if (op == 1)
                        {
                            wcout << L"Зашифрованный текст: " << cipher.encrypt(text) << endl;
                        }
                        else
                        {
                            wcout << L"Дешифрованный текст: " << cipher.decrypt(text) << endl;
                        }
                    }
                    else
                    {
                        wcout << L"Операция прервана: неверный текст\n";
                    }
                }
                catch (const exception& e)
                {
                    wcerr << L"Ошибка: " << e.what() << endl;
                }
            }
        } while (op != 0);
    }
    catch (const exception& e)
    {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}

// Вставьте функцию isValid в этот файл
bool isValid(const wstring& s)
{
    for (auto c : s)
    {
        if (!iswalpha(c) || !iswupper(c))
        {
            wcerr << L"Ошибка: Введен недопустимый символ: " << c << endl;
            return false;
        }
    }
    return true;
}
