#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

#include "macro_def.h"
#include "public.h"
#include "read.h"
#include "execute.h"
#include "print.h"

void help();
void interact();
void load_mips();

int main()
{
    std::string input;
    std::cout << "MySPIM simulator 0.1" << std::endl
              << "? - help" << std::endl;

    while (1)
    {
        std::getline(std::cin, input);
        if (input == "?")
        {
            help();
            continue;
        }
        else if (input == "1")
        {
            interact();
            break;
        }
        else if (input == "2")
        {
            load_mips();
            break;
        }
        else if (input == "q")
        {
            break;
        }
        else
        {
            std::cout << "Sorry, I don't understand." << std::endl;
        }
    }
    
    return 0;
}

void help()
{
    std::cout << "Enter \"1\" for interactive mode." << std::endl
              << "Enter \"2\" to load a MIPS program." << std::endl
              << "Enter \"instruction\" to see previous instructions." << std::endl
              << "Enter \"label\" to see labels." << std::endl
              << "Enter \"q\" to quite." << std::endl;
}

void interact()
{
    while(1)
    {
        std::cout << "text:0x" << std::hex << address << " > ";
        std::vector<std::string> tokens = read();
        if (tokens.empty()) continue;
        if (tokens[0] == "instruction")
        {
            print_instruction();
            continue;
        }
        if (tokens[0] == "label")
        {
            print_label();
            continue;
        }
        if (tokens[0] == "q") break;

        // std::cout << "~~input: ";
        // for (std::string &token : tokens)
        // {
        //     std::cout << token << "~~";
        // }
        // std::cout << std::endl;
        // 检查是否有label，有的话就去掉标签，然后保存标签
        check_label(tokens);
        // 如果只有标签，就让用户继续输入
        if (tokens.empty()) continue;
        // 如果是无效命令，弹出说明, 继续输入
        if (!validation(tokens))
        {
            std::cout << "invalide instruction" << std::endl;
            continue;
        }
        // 有效命令，地址+4
        else
        {
            address += 4;
        }
        
        // std::cout << "correct: ";
        // for (std::string &token : tokens)
        // {
        //     std::cout << token << "~~";
        // }
        // std::cout << std::endl;

        execute(tokens);
        if (exit_program) break;
    }
}

void load_mips()
{
    std::string filename;
    std::cout << "filename: ";
    std::getline(std::cin, filename); // 使用getline来允许文件名中有空格

    // 打开文件
    std::ifstream file(filename);

    // 检查文件是否成功打开
    if (!file.is_open())
    {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return;
    }
    
    std::string line;

    while (std::getline(file, line))
    {
        std::string input_copy = line;
        std::vector<std::string> tokens0 = split(line);
        if (tokens0.empty()) continue;
        if (tokens0[0] == "main:")
        {
            check_label(tokens0);
            if (!validation(tokens0))
            {
                std::cout << "invalide instruction" << std::endl;
                break;
            }
            else
            {
                address += 4;
            }
        
            execute(tokens0);
            break;
        }
    }

    while (std::getline(file, line))
    {
        std::string input_copy = line;
        std::vector<std::string> tokens0 = split(line);
        if (tokens0.empty()) continue;
        check_label(tokens0);
        if (!validation(tokens0))
        {
            std::cout << "invalide instruction: " << line << std::endl;
            break;
        }
        else
        {
            address += 4;
        }
        
        execute(tokens0);
        if (exit_program) break;
    }

    // 关闭文件
    file.close();
}
