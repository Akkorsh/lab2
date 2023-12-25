// transpositioncipher.cpp
#include "transpositioncipher.h"
#include <cwctype>

TranspositionCipher::TranspositionCipher(int numColumns) : numColumns(numColumns) {}

std::wstring TranspositionCipher::encrypt(const std::wstring& plaintext) {
    std::wstring modifiedText = getValidText(plaintext);
    std::wstring ciphertext;

    int numRows = (modifiedText.length() + numColumns - 1) / numColumns;
    std::vector<std::wstring> table(numRows, std::wstring(numColumns, L' '));
    int index = 0;

    for (int i = 0; i < numRows; i++) {
        for (int j = numColumns - 1; j >= 0; j--) {
            if (index < modifiedText.length()) {
                table[i][j] = modifiedText[index++];
            }
        }
    }

    for (int j = 0; j < numColumns; j++) {
        for (int i = 0; i < numRows; i++) {
            ciphertext += table[i][j];
        }
    }

    return ciphertext;
}

std::wstring TranspositionCipher::decrypt(const std::wstring& ciphertext) {
    std::wstring modifiedText = getValidText(ciphertext);
    std::wstring decryptedText;

    int numRows = (modifiedText.length() + numColumns - 1) / numColumns;
    std::vector<std::wstring> table(numRows, std::wstring(numColumns, L' '));
    uint index = 0;

    for (int j = numColumns - 1; j >= 0; j--) {
        for (int i = 0; i < numRows; i++) {
            if (index < modifiedText.length()) {
                table[i][j] = modifiedText[index++];
            }
        }
    }

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numColumns; j++) {
            decryptedText += table[i][j];
        }
    }

    return decryptedText;
}

std::wstring TranspositionCipher::getValidText(const std::wstring& text) {
    std::wstring tmp;
    for (auto c : text) {
        if (std::iswalpha(c)) {
            tmp.push_back(std::iswupper(c) ? c : std::towupper(c));
        } else {
            throw cipher_error(std::string("Invalid character: '") + static_cast<char>(c) + "'. Digits are not allowed.");
        }
    }
    if (tmp.empty()) {
        throw cipher_error("Empty text");
    }
    return tmp;
}
