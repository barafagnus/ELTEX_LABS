/* 2. В строке найти последовательности цифр, каждую из них считать числом в той системе счисления
которая соответствует первой цифре, заменить числа в строке с символами с кодами, полученными из этих чисел. 
Пример: aaa2010101bbb8343ccc - двоичная и восьмеричная система счисления */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

#define STRINGLEN 255

char getnumber(char* massive_1, int i, char info) {
    char symbol;
    int n = 0;
    int m = 0;
    int intmas[STRINGLEN];
    int j = 0;
    int dec = 0;
    int info_int;
    char info_char;

    info_int = info - 48;
    info_char = info_int - 1 + 48;

    for (i + 1; i < STRINGLEN; i++){ 
        if ((massive_1[i] >= '0') && (massive_1[i] <= info_char)){
            intmas[j] = massive_1[i] - 48;
            n++;
            j++;
        }
    }
    n = n - 1;
    m = n + 1;
    for (j = 0; j < m; j++){ 
        dec += intmas[j] * pow(info_int, n);
        n--;   
    }
    symbol = dec;
    return symbol;
}

int main() {
    setlocale(LC_ALL, "");

    char result[STRINGLEN];
    char symbol;
    int i = 0;
    int n = 0;
    char info, c;
    char massive_1[STRINGLEN] = "aaa21011110bbb854ccc";
    // while ((c = getchar()) != '\n') {
    //     massive_1[i] = c;
    //     i++;
    // }

    for (i = 0; i < STRINGLEN; i++){
        info = massive_1[i];
        if (!((info >= '0') && (info <= '9'))){
            result[n] = massive_1[i];
            n++;    
        }

        if (info == '2') {
            symbol = getnumber(massive_1, i, info); 
            result[n] = symbol;
            n++;
        }
        if (info == '8') {
            symbol = getnumber(massive_1, i, info);
            result[n] = symbol;
            n++;
        }
    
}
printf("RESULT: %s\n", result);

return 0;
}

