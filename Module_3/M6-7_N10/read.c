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
    int shmdel;
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

    printf("Чтение из write.c\n");
    while (ptr[i] != EOF) {
        putchar(ptr[i]);
        ++i;
    }
    
    /* int shmctl(int shmid, int cmd, struct shmid_ds *buf) - операция управления сегмента совместной памяти
    Первый аргумент shmid - ID сегмента разделяемой памяти (shmget())
    Второй аргумент cmd - команда выполнения операции - I
        PC_RMID - отмечает сегмент, подлежащий уничтожению. Сегмент уничтожается только после того, как последний процесс отключил его.
    Третий аргумент, buf, это указатель на структуру разделяемой памяти с именем struct shmid_ds. 
    Значения этой структуры будут использоваться для набора или получения согласно cmd.*/
    shmdel = shmctl(shmid, IPC_RMID, NULL);
    if (shmdel < 0) {
        printf("Не удается освободить общую память\n");
        exit(-1);
    }
    printf("\nПамять освобождена.\n");

    return 0;

}