#ifndef PUBLIC_H
#define PUBLIC_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iomanip>

class MipsRegister
{
  public:
    uint32_t general[2] = {0};
    uint32_t hi = 0;
    uint32_t lo = 0;

    void mult(uint32_t reg1, uint32_t reg2)
    {
        // static_cast<Type>(expression) 是一个类型转换操作符，
        // 用于显式地将一个表达式的类型转换为另一个类型。
        uint64_t result = static_cast<uint64_t>(general[reg1]) * static_cast<uint64_t>(general[reg2]);

        // >> 是位移运算。向右移动32位, 意味着舍弃低32位，仅保留高32位。
        hi = static_cast<uint32_t>(result >> 32); // High 32 bits
        lo = static_cast<uint32_t>(result);       // Low 32 bits
    }
    
    void div(uint32_t reg1, uint32_t reg2)
    {
        uint32_t quotient = general[reg1] / general[reg2];
        uint32_t remainder = general[reg1] % general[reg2];

        lo = quotient;   // Store the quotient in lo
        hi = remainder;  // Store the remainder in hi
    }
};

// class data
// {
// public:
//     unsigned int addr = 0x10000000;
//     int val;
// }

extern std::vector<std::string> instructions;
extern std::string registers[32];
extern std::unordered_map<std::string, unsigned int> labels;
extern std::unordered_map<std::string, int> reg;
extern unsigned int address;
extern unsigned int data_address;
extern int high;
extern int low;
extern bool read_int;
extern bool read_str;
extern bool print_int;
extern bool print_str;
extern bool exit_mips;
extern bool exit_program;
extern std::unordered_map<unsigned int, std::string> records;
extern std::unordered_map<unsigned int, unsigned int> data_store;    
#endif
