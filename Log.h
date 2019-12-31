#pragma once
#include <iostream>
#include <vector>

struct Log
{
public:
    Log();
    ~Log();
    
    void PrintVector(std::vector<int> vect) const
    {
        for (int i : vect)
        {
            std::cout << i << ' ';
        }
    }
    void PrintName(std::string name) const
    {
        std::cout << name;
    }
    void PrintCard(int cardNum) const
    {
        switch (cardNum)
        {
            case 0:
                std::cout << "SPY[0]";
                break;
            case 1:
                std::cout << "GUARD[1]";
                break;
            case 2:
                std::cout << "PRIEST[2]";
                break;
            case 3:
                std::cout << "BARON[3]";
                break;
            case 4:
                std::cout << "HANDMAID[4]";
                break;
            case 5:
                std::cout << "PRINCE[5]";
                break;
            case 6:
                std::cout << "CHANCELLOR[6]";
                break;
            case 7:
                std::cout << "KING[7]";
                break;
            case 8:
                std::cout << "COUNTESS[8]";
                break;
            case 9:
                std::cout << "PRINCESS[9]";
                break;
        }
    }
    void PrintVectSize(std::vector<int> vect) const
    {
        unsigned long int size = vect.size();
        std::cout << '[' << size << ']';
    }
};
