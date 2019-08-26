#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

std::vector<double> table = {0.0651738, 0.0124248, 0.0217339, 0.0349835, 0.1041442, 0.0197881, 0.0158610, 0.0492888, 0.0558094, 0.0009033, 0.0050529, 0.0331490, 0.0202124, 0.0564513, 0.0596302, 0.0137645, 0.0008606, 0.0497563, 0.0515760, 0.0729357, 0.0225134, 0.0082903, 0.0171272, 0.0013692, 0.0145984, 0.0007836, 0.1918182};

char CHARACTERS [] = "abcdefghijklmnopqrstuvwxyz ";

std::vector<char> StringToByteVector(std::string s)
{
    std::vector<char> bytes;
    for (int i = 0; i < s.size(); i += 2)
    {
        char byte = (char)std::strtol(s.substr(i, 2).c_str(), NULL, 16);
        bytes.push_back(byte);
    }
    return bytes;
}

std::string SingleCharXOR(std::vector<char> bytes, int XORValue)
{
    std::string output;
    for (char byte : bytes)
    {
        output += std::tolower((char)(byte ^ XORValue));
    }
    return output;
}

std::vector<std::string> GenerateXORStrings(std::vector<char> bytes)
{
    std::vector<std::string> XORStrings;
    for (int i = 0; i < 256; i++)
    {
        XORStrings.push_back(SingleCharXOR(bytes, i));
    }
    return XORStrings;
}

std::vector<double> GenLetterFrequencies(std::string s)
{
    std::vector<double> letterFrequencies;
    int totalLetters = s.size();
    for (auto i : CHARACTERS)
    {
        int letters = std::count_if(s.cbegin(), s.cend(), [&i](char a) { return a == i; });
        letterFrequencies.push_back(letters);
    }
    return letterFrequencies;
}

double LetterScore(std::vector<double> letterFrequencies)
{
    double value = 0;
    for (int i = 0; i < letterFrequencies.size(); i++)
    {
        value += table[i] * letterFrequencies[i];
    }
    return value;
}

std::map<std::string, double> ScoreTable(std::vector<std::string> inputs)
{
    std::map<std::string, double> table;
    for (auto input : inputs)
    {
        table[input] = LetterScore(GenLetterFrequencies(input));
    }
    return table;
}

std::string DecodeHex(std::string input)
{
    std::vector<char> bytes = StringToByteVector(input);
    auto XORStrings = GenerateXORStrings(bytes);
    auto freqTable = ScoreTable(XORStrings);
    auto bestGuess = std::max_element(freqTable.cbegin(), freqTable.cend(),
                                      [](auto p1, auto p2) { return p1.second < p2.second; });
    return bestGuess->first;
}

int main()
{
    std::string test = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    auto letters = DecodeHex(test);
    std::cout << letters;
}