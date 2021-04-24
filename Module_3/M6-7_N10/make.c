/* Напишите две программы, осуществляющие взаимодействие через разделяемую память. 
Первая программа должна создавать сегмент разделяемой памяти и копировать туда свой собственный исходный текст, 
вторая программа должна брать оттуда этот текст, печатать его на экране и удалять сегмент разделяемой памяти из системы. */


#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Rus");
    int *ptr;
    int shmid;
    int fd;
    int rd;
    int i = 0;
    key_t key;
    system("touch sysvkey.txt");

    // Генерируем IPC ключ
    key = ftok("sysvkey.txt", 0);
    if (key < 0) {
        printf("Не удалось сгенерировать ключ.\n");
        exit(-1);
    }
    
    // Выделяем сегмент памяти Sys V
    shmid = shmget(key, 8192*sizeof(int), 0777 | IPC_CREAT | IPC_EXCL);
    if (shmid < 0) {
        if (errno != EEXIST) {
            printf("Невозможно выделить память.\n");
            exit(-1);
        }
        else {
            shmid = shmget(key, 8192*sizeof(int), 0);
            if (shmid < 0) {
                printf("Невозможно найти память.\n");
                exit(-1);
            }
        }
    }

    /* Присоединение сегмента совместно используемой памяти к адресному пространству вызывающего процесса.
    Первый аргумент shmid - ID сегмента разделяемой памяти (shmget())
    Второй аргумент shmaddr -  адрес присоединения, NULL - система сама выбирает адрес
    Третий аргумент shmflg - флаги общей памяти */
    
    ptr = (int *)shmat(shmid, NULL, 0);
    if (ptr == (int *)(-1)) {
        printf("Невозможно оторбазить разделяемую память.\n");
        exit(-1);
    }

    fd = open("./make.c", O_RDONLY);
    while ((rd = read(fd, &ptr[i], 1)) > 0) {
        i++;
    }
    ptr[i+1]=EOF;

    if (rd < 0) {
        printf("Не удалось прочитать файл.\n");
        exit(1);
    }
    
    printf("\nЗапись произведена успешно.\n\n");
    return 0;
}