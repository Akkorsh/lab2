// transpositioncipher.h
#pragma once

#include <string>
#include <vector>
#include <stdexcept>

class cipher_error : public std::invalid_argument {
public:
    explicit cipher_error(const std::string& what_arg) : std::invalid_argument(what_arg) {}
};

class TranspositionCipher {
public:
    TranspositionCipher(int numColumns);
    std::wstring encrypt(const std::wstring& plaintext);
    std::wstring decrypt(const std::wstring& ciphertext);

private:
    int numColumns;
    std::wstring getValidText(const std::wstring& text);
};
