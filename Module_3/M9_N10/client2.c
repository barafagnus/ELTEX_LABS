#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf {
   long mtype;
   int request_id;
   char mtext[200];
};

int main() {
    struct msgbuf buf;
    int msqid;
    int len;
    key_t key;

    system("touch msgq.txt");

    if ((key = ftok("msgq.txt", 0)) < 0) {
        perror("ftok");
        exit(-1);
    }

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
        perror("mssget");
        exit(-1);
    }

    while(1) {
        buf.mtype = 1;
        buf.request_id = 3;
        len = strlen(buf.mtext);

        if (buf.mtext[len-1] == '\n') 
            buf.mtext[len-1] = '\0';

        if (msgsnd(msqid, &buf, sizeof(buf.mtext), 0) < 0) {
            perror("msgsnd");
            msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
            exit(1);
        }
        
        if ((len = msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0)) < 0) {
            perror("msgrcv");
            exit(-1);
        }
        printf("%sMessage type = %ld, CLIENT_ID %d\n", buf.mtext, buf.mtype, buf.request_id);


    return 0;
    }
}