#include <cmath>
#include <fstream>
#include <iostream>
#include<coder.h>
using namespace std;

int main()
{
    try{
        int polynomal1, polynomal2, switcher, counter = 0, input = 0, output = 0, bit = 0, prep = 0;
        char res = 0, buf;
        string space, path;
        ifstream cfin;
        ofstream cfout;
        cin >> switcher;
        cin >> polynomal1;
        cin >> polynomal2;
        coder worker(polynomal1, polynomal2);
        getline(cin,path);
        cfin.open(path, ios::binary);
        getline(cin,path);
        cfout.open(path, ios::binary);
        if(cfin.is_open() || cfout.is_open()) {//проверка файлов
        while(cfin.get(buf)) {
            space = space + buf;
        }
        } else {
        throw string("wrong path.\n");
        }
        if (space.length() == 0){//проверка: файл не пустой
            throw string("file is empty.\n");
        }
        switch (switcher)
        {
            case(0):
            {
                for(unsigned int i = 0; i < space.length(); i++) {//кодирование
                for(unsigned int bit = 1; bit <= (sizeof(char)*8); bit++) {
                    input = (input << 1) + ((space[i] >> ((sizeof(char)*8) - bit)) & 1);
                    counter++;
                    if(((counter % polynomal2) == 0) && (counter != 0))
                    {
                        output = worker.encrypt(input);
                        for (int i = 0; i <= polynomal1/8; i++){
                            res = output>>8*(polynomal1/8-i);
                            cfout.write((char*)&res,sizeof (char));
                        }
                        input = 0;
                    }
                }
            }
                if((counter % polynomal2) != 0)//дозапись последнего значения
            {
                input = input<<(polynomal2 - (counter%polynomal2));
                output = worker.encrypt(input);
                for (int i = 0; i <= polynomal1/8; i++){
                    res = output>>8*(polynomal1/8-i);
                    cfout.write((char*)&res,sizeof (char));
                }
            }
            }
            break;
            case (1):
            {
                for (unsigned int i = 0;i < space.length();i++) {//декодирование
                    for (int k = 0; k < 8;k++){
                        prep = (prep<<1) + ((space[i]>>(8 - k - 1))&1);
                    }
                    input = (input << 8) + prep;
                    prep = 0;
                    counter += 8;
                    if ((counter/8%(polynomal1/8 + 1) == 0) && (counter != 0)){
                        output = worker.decrypt(input);
                        input = 0;
                        for (int j = 0; j < polynomal2; ++j) {
                            res = (res << 1) + ((output >>( polynomal2 - j - 1)) & 1);
                            bit++;
                            if ((bit%8 == 0)&&(bit != 0)){
                                if (res != 0)
                                cfout.write((char*)&res,sizeof (char));
                                res = 0;
                                bit = 0;
                            }
                        }
                    }
                }
            }
            break;
            default:
            {
                throw string ("wrong operation.\n");
            }
        }
    }
    catch (string str){
        cerr << "Error:" << str;
    };
}
