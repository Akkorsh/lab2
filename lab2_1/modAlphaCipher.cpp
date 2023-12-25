#include "modAlphaCipher.h"
#include <cwctype>

modAlphaCipher::modAlphaCipher(const std::wstring& skey)
{
    for (unsigned i = 0; i < numAlpha.size(); i++)
    {
        alphaNum[towlower(numAlpha[i])] = i; // добавляем также для символов в нижнем регистре
    }
    key = convert(skey);
}

std::wstring modAlphaCipher::encrypt(const std::wstring& open_text)
{
    std::vector<int> work = convert(open_text);
    for (unsigned i = 0; i < work.size(); i++)
    {
        work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}

std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text)
{
    std::vector<int> work = convert(cipher_text);
    for (unsigned i = 0; i < work.size(); i++)
    {
        work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) %
                   alphaNum.size();
    }
    return convert(work);
}

inline std::vector<int> modAlphaCipher::convert(const std::wstring& s)
{
    std::vector<int> result;
    for (auto c : s)
    {
        if (!iswalpha(c))
        {
            throw std::invalid_argument("Обнаружен недопустимый символ во входных данных");
        }
        result.push_back(alphaNum[towupper(c)]);
    }
    return result;
}

inline std::wstring modAlphaCipher::convert(const std::vector<int>& v)
{
    std::wstring result;
    for (auto i : v)
    {
        result.push_back(numAlpha[i]);
    }
    return result;
}
