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

    printf("\n===---Server is running---===\n");

    while(1) {
        buf.mtype = 1;
        if ((len = msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0)) < 0) {
            perror("msgrcv");
            exit(-1);
        }
        printf("[RCV_MSG]: Message type = %ld, CLIENT_ID %d\n", buf.mtype, buf.request_id);
        buf.mtype = buf.request_id;
        len = strlen(buf.mtext) + 1;
        strcpy(buf.mtext, "___[Message from server]___:\n");

        // if (buf.request_id == 2) {
        //     len = strlen(buf.mtext) + 1;
        //     strcpy(buf.mtext, "Message from server to ID = 2:\n");
        // }
        
        // else if (buf.request_id == 3) {
        //     len = strlen(buf.mtext) + 1;
        //     strcpy(buf.mtext, "Message from server to ID = 2:\n");
        // }
        if (msgsnd(msqid, &buf, sizeof(buf.mtext), 0) < 0) {
            perror("msgsnd");
            msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
            exit(1);
        }  
    }


    return 0;
}