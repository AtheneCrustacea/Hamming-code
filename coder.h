#pragma once
#include <string>
class coder
{
private:
    int coded;
    int decoded;
    int polynomal1;
    int polynomal2;
public:
    coder(int input_polynomal1, int input_polynomal2);///< конструктор
    int encrypt(int num_s);
    int decrypt(int num_s);
};
