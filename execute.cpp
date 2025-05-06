#include <iostream>
#include <string>

#include "macro_def.h"
#include "public.h"
#include "execute.h"
#include "read.h"

// int str_to_num(const std::string& token)
// {
//     return std::stoi(token);
// }

void execute(std::vector<std::string> &tokens)
{
    if (tokens[0] == "j")
    {
        unsigned int j_addr = labels[tokens[1]];
        while (j_addr != address)
        {
            std::vector<std::string> tokens1 = split(records[j_addr]);
            execute(tokens1);
            j_addr++;
        }
    }
    else if (tokens[0] == "jal")
    {
        // if (tokens[0] == "jal") labels[tokens[1]] = record_address;
    }
    else if (tokens[0] == "jr")
    {
    }
    else if (tokens[0] == "li")
    {
        reg[tokens[1]] = std::stoi(tokens[2]);
        // std::cout << "register " << tokens[1] << ": "
        //           << std::stoi(tokens[2]) << std::endl;

        if (tokens[1] == "$v0" && tokens[2] == "1")
        {
            print_int = true;
        }
        else if (tokens[1] == "$v0" && tokens[2] == "4")
        {
            print_str = true;
        }
        else if (tokens[1] == "$v0" && tokens[2] == "5")
        {
            read_int = true;
        }
        else if (tokens[1] == "$v0" && tokens[2] == "8")
        {
            read_str = true;
        }
        else if (tokens[1] == "$v0" && tokens[2] == "10")
        {
            exit_mips = true;
        }
    }
    else if (tokens[0] == "syscall")
    {
        if (print_int)
        {
            std::cout << std::dec << reg["$a0"] << std::endl;
            print_int = false;
        }
        else if (print_str)
        {
            print_str = false;
        }
        else if (read_int)
        {
            int n;
            std::cout << "CONSOLE INTEGER INPUT > ";
            std::cin >> n;
            reg["$a0"] = n;
            read_int = false;
        }
        else if (read_str)
        {
            std::string string;
            unsigned int store_str_addr = reg["$a0"];
            std::cout << "CONSOLE STRING INPUT > ";
            std::cin >> string;
            for (char c: string)
            {
                data_store[store_str_addr] = static_cast<int>(c);
                store_str_addr++;
            }
            data_store[store_str_addr] = 10;
            read_str = false;
        }
        else if (exit_mips)
        {
            exit_program = true;
        }
    }
    else if (tokens[0] == "move")
    {
        reg[tokens[1]] = reg[tokens[2]];
        // std::cout << "register " << tokens[1] << ": " << reg[tokens[1]]
        //           << std::endl
        //           << "register " << tokens[2] << ": " << reg[tokens[2]]
        //           << std::endl;
    }
    else if (tokens[0] == "add" || tokens[0] == "addu")
    {
        reg[tokens[1]] = reg[tokens[2]] + reg[tokens[3]];
        // std::cout << "register " << tokens[1] << ": " << reg[tokens[1]]
        //           << std::endl
        //           << "register " << tokens[2] << ": " << reg[tokens[2]]
        //           << std::endl
        //           << "register " << tokens[3] << ": " << reg[tokens[3]]
        //           << std::endl;
    }
    else if (tokens[0] == "sub" || tokens[0] == "subu")
    {
        reg[tokens[1]] = reg[tokens[2]] - reg[tokens[3]];
        // std::cout << "register " << tokens[1] << ": " << reg[tokens[1]]
        //           << std::endl
        //           << "register " << tokens[2] << ": " << reg[tokens[2]]
        //           << std::endl
        //           << "register " << tokens[3] << ": " << reg[tokens[3]]
        //           << std::endl;
    }
    else if (tokens[0] == "addi" || tokens[0] == "addiu")
    {
        reg[tokens[1]] = reg[tokens[2]] + std::stoi(tokens[3]);
        // std::cout << "register " << tokens[1] << ": " << reg[tokens[1]]
        //           << std::endl
        //           << "register " << tokens[2] << ": " << reg[tokens[2]]
        //           << std::endl
        //           << "int: " << std::stoi(tokens[3])
        //           << std::endl;
    }
    else if (tokens[0] == "mult" || tokens[0] == "multu")
    {
        MipsRegister regs;
        regs.general[0] = reg[tokens[1]];
        regs.general[1] = reg[tokens[2]];

        regs.mult(0, 1);

        high = regs.hi;
        low = regs.lo;

        // std::cout << "register " << tokens[1] << ": "
        //           << std::dec << reg[tokens[1]]
        //           << std::endl
        //           << "register " << tokens[2] << ": "
        //           << std::dec << reg[tokens[2]]
        //           << std::endl
        //           << "high: " << std::dec << high << std::endl
        //           << "low: " << std::dec << low << std::endl;
    }
    else if (tokens[0] == "div" || tokens[0] == "divu")
    {
        MipsRegister regs;
        regs.general[0] = reg[tokens[1]];
        regs.general[1] = reg[tokens[2]];

        regs.div(0, 1);

        high = regs.hi;
        low = regs.lo;

        // std::cout << "register " << tokens[1] << ": " << reg[tokens[1]]
        //           << std::endl
        //           << "register " << tokens[2] << ": " << reg[tokens[2]]
        //           << std::endl
        //           << "remainder: " << std::dec << high << std::endl
        //           << "quotient: " << std::dec << low << std::endl;
    }
    else if (tokens[0] == "mfhi")
    {
        reg[tokens[1]] = high;

        // std::cout << "register " << tokens[1] << ": " 
        //           << std::dec << reg[tokens[1]]
        //           << std::endl;
    }
    else if (tokens[0] == "mflo")
    {
        reg[tokens[1]] = low;
        // std::cout << "register " << tokens[1] << ": "
        //           << std::dec << reg[tokens[1]]
        //           << std::endl;
    }
    else if (tokens[0] == "slt")
    {
        if (reg[tokens[2]] < reg[tokens[3]])
        {
            reg[tokens[1]] = 1;
        }
        else
        {
            reg[tokens[1]] = 0;
        }
        // std::cout << "register " << tokens[1] << ": "
        //           << std::dec << reg[tokens[1]]
        //           << std::endl;
    }
    else if (tokens[0] == "slti")
    {
        if (reg[tokens[2]] < std::stoi(tokens[3]))
        {
            reg[tokens[1]] = 1;
        }
        else
        {
            reg[tokens[1]] = 0;
        }
        // std::cout << "register " << tokens[1] << ": "
        //           << std::dec << reg[tokens[1]]
        //           << std::endl;
    }
    else if (tokens[0] == "beq")
    {
        if (reg[tokens[1]] == reg[tokens[2]])
        {
            unsigned int j_addr = labels[tokens[3]];
            while (j_addr != address)
            {
                std::vector<std::string> tokens1 = split(records[j_addr]);
                execute(tokens1);
                j_addr++;
            }
        }
    }
    else if (tokens[0] == "bne")
    {
        if (reg[tokens[1]] != reg[tokens[2]])
        {
            unsigned int j_addr = labels[tokens[3]];
            while (j_addr != address)
            {
                std::vector<std::string> tokens1 = split(records[j_addr]);
                execute(tokens1);
                j_addr++;
            }
        }
    }
    else if (tokens[0] == "bgt")
    {
        if (reg[tokens[1]] > reg[tokens[2]])
        {
            unsigned int j_addr = labels[tokens[3]];
            while (j_addr != address)
            {
                std::vector<std::string> tokens1 = split(records[j_addr]);
                execute(tokens1);
                j_addr++;
            }
        }
    }
    else if (tokens[0] == "bge")
    {
        if (reg[tokens[1]] >= reg[tokens[2]])
        {
            unsigned int j_addr = labels[tokens[3]];
            while (j_addr != address)
            {
                std::vector<std::string> tokens1 = split(records[j_addr]);
                execute(tokens1);
                j_addr++;
            }
        }
    }
    else if (tokens[0] == "blt")
    {
        if (reg[tokens[1]] < reg[tokens[2]])
        {
            unsigned int j_addr = labels[tokens[3]];
            while (j_addr != address)
            {
                std::vector<std::string> tokens1 = split(records[j_addr]);
                execute(tokens1);
                j_addr++;
            }
        }
    }
    else if (tokens[0] == "ble")
    {
        if (reg[tokens[1]] <= reg[tokens[2]])
        {
            unsigned int j_addr = labels[tokens[3]];
            while (j_addr != address)
            {
                std::vector<std::string> tokens1 = split(records[j_addr]);
                execute(tokens1);
                j_addr++;
            }
        }
    }
}
