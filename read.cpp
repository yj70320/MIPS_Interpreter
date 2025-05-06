#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include "macro_def.h"
#include "public.h"
#include "read.h"
#include "execute.h"

std::vector<std::string> read();
void check_label(std::vector<std::string> &tokens);
std::vector<std::string> split(const std::string &input);
bool validation(std::vector<std::string> &tokens);
bool validation(std::vector<std::string> &tokens);
bool is_number(const std::string& token);

std::string input_copy;

std::vector<std::string> read()
{
    std::string input;
    std::getline(std::cin, input);
    
    input_copy = input;
    
    std::vector<std::string> tokens = split(input);

    return tokens;
}

void check_label(std::vector<std::string> &tokens)
{
    if (tokens[0].back() == ':')
    {
        tokens[0].pop_back();
        labels[tokens[0]] = address;
        // std::cout << "label " << tokens[0] << ": "
        //           << address << std::endl;
        tokens.erase(tokens.begin());
    }
}

std::vector<std::string> split(const std::string &input)
{
    std::vector<std::string> tokens;
    const std::string delimiters = ", ";
    size_t start = 0, end = 0;
    
    //std::string::npos 是一个常量，代表 std::string 类中一个不可能的索引。
    // 是 size_t 类型的最大可能值，通常用来表示字符串中没有找到子串或字符的情况。
    while ((end = input.find_first_of(delimiters, start)) != std::string::npos)
    {
        if (end != start)
        {
            tokens.push_back(input.substr(start, end - start));
        }
        start = end + 1; // 移动到下一个字符，跳过分隔符
    }

    if (start < input.length())
    { // 添加最后一个token
        tokens.push_back(input.substr(start));
    }

    return tokens;
}

bool is_number(const std::string& token)
{
    if (token.empty()) return false;

    // 检查可选的正负号
    // size_t 是一个无符号整数类型，通常用来表示对象的大小和索引。
    std::size_t start = (token[0] == '+' || token[0] == '-') ? 1 : 0;

    // 如果只有正负号，没有数字，返回false
    if (start == 1 && token.size() == 1) return false;

    // 检查剩余的字符是否都是数字
    for (std::size_t i = start; i < token.size(); ++i)
    {
        if (token[i] < '0' || token[i] > '9')
        {
            return false;
        }
    }

    return true;
}

bool validation(std::vector<std::string> &tokens)
{
    // 第一个token是指令, 如果在指令集中没找到对应的指令, 返回false
    if (std::find(instructions.begin(), instructions.end(), tokens[0]) == instructions.end())
    {
        return false;
    }
    
    else if (tokens[0] == "j" || tokens[0] == "jal")
    { //后面接标签的指令
        if (labels.empty() || tokens[1].empty())
        {
            return false;
        }
        // vector 和 map 的查找某个元素的方式不同
        else if (labels.find(tokens[1]) == labels.end())
        {
            return false;
        }
    }
    
    else if (tokens[0] == "jr")
    {
        if (tokens[1] != registers[31]) return false;
        if (tokens.size() != 2) return false;
    }
    
    else if (tokens[0] == "li")
    {
        //std::cout << "read.cpp line 83" << std::endl;
        if (tokens.size() != 3) return false;

        // 检查tokens[1]是否在寄存器数组中
        if (std::find(std::begin(registers), std::end(registers), tokens[1]) == std::end(registers)) return false;
        
        if (!is_number(tokens[2])) return false;
    }
    
    else if (tokens[0] == "move")
    {
        if (tokens.size() != 3) return false;
        if (std::find(std::begin(registers), std::end(registers), tokens[1]) == std::end(registers)) return false;
        if (std::find(std::begin(registers), std::end(registers), tokens[2]) == std::end(registers)) return false;
    }
    
    else if (tokens[0] == "add" || tokens[0] == "addu" 
             || tokens[0] == "sub" || tokens[0] == "subu")
    {
        if (tokens.size() != 4) return false;
        if (std::find(std::begin(registers), std::end(registers), tokens[1]) == std::end(registers)) return false;
        if (std::find(std::begin(registers), std::end(registers), tokens[2]) == std::end(registers)) return false;
        if (std::find(std::begin(registers), std::end(registers), tokens[3]) == std::end(registers)) return false;
    }
    
    else if (tokens[0] == "addi" || tokens[0] == "addiu")
    {
        if (tokens.size() != 4) return false;
        if (std::find(std::begin(registers), std::end(registers), tokens[1]) == std::end(registers)) return false;
        if (std::find(std::begin(registers), std::end(registers), tokens[2]) == std::end(registers)) return false;
        if (!is_number(tokens[3])) return false;
    }
    
    else if (tokens[0] == "mult" || tokens[0] == "multu")
    {
        if (tokens.size() != 3) return false;
        if (std::find(std::begin(registers), std::end(registers), tokens[1]) == std::end(registers)) return false;
        if (std::find(std::begin(registers), std::end(registers), tokens[2]) == std::end(registers)) return false;
    }
    
    else if (tokens[0] == "div" || tokens[0] == "divu")
    {
        if (tokens.size() != 3) return false;

        // 除数不能为零
        if (reg[tokens[2]] == 0)
        {
            std::cout << tokens[2] << " cannot be 0." << std::endl;
            return false;
        }

        if (std::find(std::begin(registers), std::end(registers), tokens[1]) == std::end(registers)) return false;
        if (std::find(std::begin(registers), std::end(registers), tokens[2]) == std::end(registers)) return false;
    }

    else if (tokens[0] == "mfhi")
    {
        if (tokens.size() != 2) return false;
        if (std::find(std::begin(registers), std::end(registers), tokens[1]) == std::end(registers)) return false;
    }

    else if (tokens[0] == "mflo")
    {
        if (tokens.size() != 2) return false;
        if (std::find(std::begin(registers), std::end(registers), tokens[1]) == std::end(registers)) return false;
    }

    else if (tokens[0] == "syscall")
    {
        if (tokens.size() != 1) return false;
    }
    
    else if (tokens[0] == "slt")
    {
        if (tokens.size() != 4) return false;
        if (std::find(std::begin(registers), std::end(registers), tokens[1]) == std::end(registers)) return false;
        if (std::find(std::begin(registers), std::end(registers), tokens[2]) == std::end(registers)) return false;
        if (std::find(std::begin(registers), std::end(registers), tokens[3]) == std::end(registers)) return false;
        
    }
    
    else if (tokens[0] == "slti")
    {
        if (tokens.size() != 4) return false;
        if (std::find(std::begin(registers), std::end(registers), tokens[1]) == std::end(registers)) return false;
        if (std::find(std::begin(registers), std::end(registers), tokens[2]) == std::end(registers)) return false;
        
        if (!is_number(tokens[3])) return false;
    }

    else if (tokens[0] == "beq")
    {
        if (tokens.size() != 4) return false;
        if (std::find(std::begin(registers), std::end(registers), tokens[1]) == std::end(registers)) return false;
        if (std::find(std::begin(registers), std::end(registers), tokens[2]) == std::end(registers)) return false;

        if (labels.find(tokens[1]) == labels.end())
        {
            return false;
        }
    }
    
    else if (tokens[0] == "bne")
    {
        if (tokens.size() != 4) return false;
        if (std::find(std::begin(registers), std::end(registers), tokens[1]) == std::end(registers)) return false;
        if (std::find(std::begin(registers), std::end(registers), tokens[2]) == std::end(registers)) return false;

        if (labels.find(tokens[1]) == labels.end())
        {
            return false;
        }
    }

    else if (tokens[0] == "bgt")
    {
        if (tokens.size() != 4) return false;
        if (std::find(std::begin(registers), std::end(registers), tokens[1]) == std::end(registers)) return false;
        if (std::find(std::begin(registers), std::end(registers), tokens[2]) == std::end(registers)) return false;

        if (labels.find(tokens[1]) == labels.end())
        {
            return false;
        }
    }
    
    else if (tokens[0] == "bge")
    {
        if (tokens.size() != 4) return false;
        if (std::find(std::begin(registers), std::end(registers), tokens[1]) == std::end(registers)) return false;
        if (std::find(std::begin(registers), std::end(registers), tokens[2]) == std::end(registers)) return false;

        if (labels.find(tokens[1]) == labels.end())
        {
            return false;
        }
    }

    else if (tokens[0] == "blt")
    {
        if (tokens.size() != 4) return false;
        if (std::find(std::begin(registers), std::end(registers), tokens[1]) == std::end(registers)) return false;
        if (std::find(std::begin(registers), std::end(registers), tokens[2]) == std::end(registers)) return false;

        if (labels.find(tokens[1]) == labels.end())
        {
            return false;
        }
    }
    
    else if (tokens[0] == "ble")
    {
        if (tokens.size() != 4) return false;
        if (std::find(std::begin(registers), std::end(registers), tokens[1]) == std::end(registers)) return false;
        if (std::find(std::begin(registers), std::end(registers), tokens[2]) == std::end(registers)) return false;

        if (labels.find(tokens[1]) == labels.end())
        {
            return false;
        }
    }

    records[address] = input_copy;
    // std::cout << address << ": " << records[address];
    
    return true;
}
