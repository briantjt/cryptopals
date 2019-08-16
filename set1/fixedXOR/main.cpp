#include <iostream>
#include <string>
#include <sstream>

std::string FixedXOR(std::string buff1, std::string buff2)
{
    if (buff1.size() != buff2.size())
    {
        return "";
    }
    int int1, int2;
    std::stringstream XORed_output;
    for (int i = 0; i < buff1.size(); i += 8)
    {
        int1 = std::stoi(buff1.substr(i, 8), nullptr, 16);
        int2 = std::stoi(buff2.substr(i, 8), nullptr, 16);
        XORed_output << std::hex << (int1 ^ int2);
    }
    return XORed_output.str();
}

int main()
{
    std::string buff1, buff2;
    std::cout << "Key in first hexadecimal string\n";
    std::cin >> buff1;
    std::cout << "Key in second hexadecimal string\n";
    std::cin >> buff2;
    std::cout << FixedXOR(buff1, buff2);
    return 0;
}
