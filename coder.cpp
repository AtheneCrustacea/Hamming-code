#include "coder.h"
#include <math.h>
coder::coder(int input_polynomal1, int input_polynomal2)
{
    if (((input_polynomal1 != 7) || (input_polynomal2 != 4)) &&
        ((input_polynomal1 != 15)|| (input_polynomal2 != 11))&&
        ((input_polynomal1 != 31)|| (input_polynomal2 != 26))){
        throw std::string ("wrong polynomal.");
    }
    polynomal1 = input_polynomal1;
    polynomal2 = input_polynomal2;
//    coded = 0;
//    decoded = 0;
}
int coder::encode(int num_s)
{
    if ((num_s >= unsigned((1<<polynomal2))) || (num_s<0))
        throw std::string ("insert correct number.");
    int decoded = num_s;
    int coded = 0;
    int counter = polynomal2 - 1;
    for(int i = 1; i <= polynomal1; i++) //создание шаблона
    {
        if(double(log(i) / log(2)) == (int)(log(i) / log(2))) // нули на позициях, номер которых является степенью двойки
        coded = coded << 1;
        else //запись битов из введенного числа
        {
        coded = (coded << 1) + ((decoded >> counter) & 1);
        counter--;
        }
    }
    int check_num[polynomal1 - polynomal2]; //Создание чисел для формирования контрольных битов (создание матрицы преобразования)
    int sth; //Вспомогательное число для проставления 0 и 1 (поменять название)
    int o;
    for(int i = 0; i < polynomal1 - polynomal2; i++)
        check_num[i] = 0;
    for(int j = 0; j < polynomal1 - polynomal2; j++) {
        o = 0;
        for(int i = 1; i <= polynomal1; i++) {
        sth = 1 << j;
        if((i % sth == 0))
            o = o ^ 1;
        check_num[j] = check_num[j] << 1;
        check_num[j] = check_num[j] + o;
        }
    }
    sth = 0; //подготовка вспомогательной переменной для записи в нее результатов вычисления контрольного бита
    for(int i = 0; i < polynomal1 - polynomal2; i++) //нахождение значений контрольных битов
    {
        check_num[i] = check_num[i] & coded; //создание числа для нахождения контрольного бита
            sth = 0;           //запись первого бита
        for(int j = 0; j < polynomal1; j++) //процесс формирования контрольного бита
            sth = sth ^ ((check_num[i] >> j)&1);
        check_num[i] = sth; //запись результата в соответствующую ячейку
    }
    sth = 0;
    for(int i = 1; i <= polynomal1; i++) {
        if(double(log(i) / log(2)) == (int)(log(i) / log(2))) //определение позиций для контрольных битов
        {
            coded = coded + (check_num[sth] << (polynomal1 - i));
            sth++;
        }
    }
    return coded;
}
int coder::decode(int num_s)
{
    if ((num_s >= unsigned((1<<polynomal1))) || (num_s<0))
		throw std::string ("insert correct number.");
    int coded = num_s;
    int decoded = 0;
    int check_num[polynomal1 - polynomal2]; //Создание чисел для формирования контрольных битов (создание матрицы преобразования)
    int sth; //Вспоманательное число для проставления 0 и 1 (поменять название)
    int o;
    for(int i = 0; i < polynomal1 - polynomal2; i++)
        check_num[i] = 0;
    for(int j = 0; j < polynomal1 - polynomal2; j++) {
        o = 0;
        for(int i = 1; i <= polynomal1; i++) {
        sth = 1 << j;
        if((i % sth == 0))
            o = o ^ 1;
        check_num[j] = check_num[j] << 1;
        check_num[j] = check_num[j] + o;
        }
    }
    sth = 0; //подготовка вспомогательной переменной для записи в нее результатов вычисления контрольного бита
    for(int i = 0; i < polynomal1 - polynomal2; i++) //нахождение значений контрольных битов
    {
        check_num[i] = check_num[i] & coded; //создание числа для нахождения контрольного бита
        sth = 0;           //запись первого бита
        for(int j = 0; j < polynomal1; j++) //процесс формирования контрольного бита (формируется неверно, исправить!!!)
            sth = sth ^ ((check_num[i] >> j)&0x1);
        check_num[i] = sth; //запись результата в соответствующую ячейку
    }
    sth = 0; //подготовка вспомогательной переменной к проверке значений матрицы синдромов
    for(int i = 0; i < polynomal1 - polynomal2; i++)
        sth = sth + (check_num[i]<<i);
    if(sth != 0) //исправление ошибки
        coded = coded ^ (1 << (polynomal1 - sth));
    sth = 0;
    for(int i = 1; i <= polynomal1; i++)
        if(!(double(log(i) / log(2)) == (int)(log(i) / log(2))))
        decoded = (decoded << 1) + ((coded >> (polynomal1 - i)) & 1);
    return decoded;
}
