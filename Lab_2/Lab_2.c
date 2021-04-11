/* Разработать две функции, одна из которых вводит с клавиатуры набор данных в произвольной последовательности
и размещает в памяти в заданном формате.
Другая функция читает эти данные и выводит на экран. 
Программа запрашивает и размещает в памяти несколько наборов данных при помощи первой функции,
а затем читает их и выводит на экран при помощи второй. 
Размещение данных производить в выделенном массиве байтов с контролем его переполнения. 
Последовательность строк символов. Каждая строка предваряется целым - счетчиком символов. 
Ограничение последовательности - счетчик со значением 0.*/


#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

int DataInput(char* p) {
      int i = 0;
      char c;
      while ((c = getchar()) != '0') {
        p[i] = c;
        i++;
      }
    return i;
}
void DataOutput(char* p, int m){
    int i;
    int j = 0;
    printf("\n");
    for (i = 0; i < m + 1; i++) {
        printf("%c", p[i]);
        j++;
    
        if (p[i] == '\n') {
            printf("elem v stroke [%d] \n", j - 1);
            j = 0;
        }
        if (p[i] == '\0') {
            printf("\nelem v stroke [%d] ", j - 1);
            j = 0;
        }
            //printf("[%d] ", i);
        //else printf("[%d] ", i);
    }
    //printf("%d %s", i, p);
    printf("\n");
}


int main() {
    
    char *p = NULL;
    unsigned i, j;
    int m = 1; // размерность массива
    printf("Write row: \n");
    p = (char*) malloc(m * sizeof(char));

    m = DataInput(p);
    DataOutput (p, m);
  
    free(p);
    return 0;
}