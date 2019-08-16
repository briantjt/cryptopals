#include <iostream>
#include <string>

const std::string BASE64_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int main()
{
    std::string s, base64_string;
    std::cin >> s;
    // Hexadecimal string has to be even or the resulting
    // base64 string cannot be encoded since padding is either
    // 1 or 2 bytes and 1 hex character is only 4 bits
    if (s.size() % 2 != 0)
    {
        return -1;
    }

    // Pad hexadecimal string with '0's if there aren't enough characters
    // since hex to base64 conversion is done in groups of 3 chars
    int leftover_hex_chars = s.size() % 3;
    if (leftover_hex_chars)
    {
        s += std::string(3 - leftover_hex_chars, '0');
    }
    std::string base64 = "";
    for (int i = 0; i < s.size(); i += 3)
    {
        int bits = std::stoi(s.substr(i, 3), nullptr, 16);
        base64 += BASE64_CHARS[bits >> 6];
        base64 += BASE64_CHARS[bits & 0b111111];
    }

    // Base64 is done in 24 bit chunks and the remainder is
    // padded with zeroes. Each hexadecimal character represents 4 bits
    // Padding is added to the resulting base64 string
    int padding = 0;
    int remaining_bits = (s.size() * 4) % 24;
    if (remaining_bits)
    {
        padding = (24 - remaining_bits) / 8;
    }
    for (int i = 0; i < padding; i++)
    {
        base64 += "=";
    }
    std::cout << base64 << std::endl;
}