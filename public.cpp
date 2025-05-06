#include <string>
#include <vector>
#include <unordered_map>
#include <iomanip>

#include "public.h"

std::vector<std::string> instructions = {"syscall", "li", "move", 
                                         "add", "addi", "addiu", "addu",
                                         "sub", "subu",
                                         "mult", "mfhi", "mflo", "multu",
                                         "div", "divu",
                                         "j", "jal", "jr",
                                         "beq", "bne", "bgt", "bge",
                                         "blt", "ble", "slt", "slti"};

// 寄存器的名字集合，用来检测输入的变量名是否正确
std::string registers[32] = {"$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"};

// 标签名称和标签所在地址一一对应的字典
std::unordered_map<std::string, unsigned int> labels;

// 寄存器名称和存储内容一一对应的字典
std::unordered_map<std::string, int> reg;

// 输入界面的地址和初始化
unsigned int address = 0x400000;

// 存储指令记录的地址
unsigned int data_address = 0x10000000;

int high = 0;
int low = 0;
bool read_int = false;
bool read_str = false;
bool print_int = false;
bool print_str = false;
bool exit_mips = false;
bool exit_program = false;

std::unordered_map<unsigned int, std::string> records;

std::unordered_map<unsigned int, unsigned int> data_store;

// address ???
