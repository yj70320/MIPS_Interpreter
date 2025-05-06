#include <iostream>
#include <string>
#include <iomanip>
#include <unordered_map>

#include "macro_def.h"
#include "public.h"
#include "read.h"
#include "execute.h"
#include "print.h"

void print_data_segment()
{
    std::cout << "=================================================================" << std::endl
              << "Data Segment" << std::endl
              << "=================================================================" << std::endl
              << "  addr (int)|  addr (hex)| value (int)| value (hex)| value (char)" << std::endl
              << "------------+------------+------------+------------+------------+" << std::endl;
}

void print_label()
{
    std::cout << "=================================================================" << std::endl
              << "Labels" << std::endl
              << "=================================================================" << std::endl
              << "  addr (int)|  addr (hex)| label" << std::endl
              << "------------+------------+---------------------------------------" << std::endl;
    for (const auto& pair : labels)
    {
        unsigned int addr = pair.second;
        std::string label = pair.first;

        std::cout << std::setw(12) << std::right << std::dec << addr << "|"
                  << std::setw(6) << std::right << "0x" << std::hex << addr << "|"
                  << " " << label << std::endl;
    }
    std::cout << "------------+------------+---------------------------------------" << std::endl;
}

void print_instruction()
{
    unsigned int print_addr = 0x400000;
    std::cout << "=================================================================" << std::endl
              << "Instructions" << std::endl
              << "=================================================================" << std::endl
              << "  addr (int)|  addr (hex)| instructions" << std::endl
              << "------------+------------+---------------------------------------" << std::endl;
    while (print_addr != address)
    {
        std::cout << std::setw(12) << std::setfill(' ') << std::right << std::dec << print_addr << "|"
                  << std::setw(6) << std::setfill(' ') << std::right << std::hex << "0x" << print_addr << "|"
                  << "   " << std::left << records[print_addr] << std::endl;
        print_addr+=4;
    }
    std::cout << "------------+------------+---------------------------------------" << std::endl;
}
