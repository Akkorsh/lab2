// main.cpp
#include <iostream>
#include <locale>
#include <codecvt>
#include "transpositioncipher.h"

int main() {
    std::locale::global(std::locale(""));

    std::wstring plaintext;
    int key;
    unsigned op;

    std::wcout << L"Введите количество столбцов: ";
    std::wcin >> key;
    std::wcin.ignore();

    TranspositionCipher cipher(key);

    do {
        std::wcout << L"Шифр готов. Введите операцию (0-выход, 1-шифрование, 2-дешифрование): ";
        std::wcin >> op;

        if (op > 2) {
            std::wcout << L"Недопустимая операция\n";
        } else if (op > 0) {
            std::wcout << L"Введите текст: ";
            std::wcin.ignore();
            std::getline(std::wcin, plaintext);

            try {
                if (op == 1) {
                    std::wstring ciphertext = cipher.encrypt(plaintext);
                    std::wcout << L"Зашифрованный текст: " << ciphertext << std::endl;
                } else {
                    std::wstring decryptedText = cipher.decrypt(plaintext);
                    std::wcout << L"Расшифрованный текст: " << decryptedText << std::endl;
                }
            } catch (const cipher_error& e) {
                std::wcerr << L"Error: " << e.what() << std::endl;
            }
        }
    } while (op != 0);

    return 0;
}
