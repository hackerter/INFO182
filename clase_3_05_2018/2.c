
#include <sys/sem.h>


int* p = NULL;
int main(){
    struct sembuf sb[1];
    key_t k;
    int sem = semget(IPC_PRIVATE,1,IPC_CREAT|0666);
    semctl(sem,0,SETVAL,1);

    k = ftok("/home/laboratorio",0);
    int id = shmget(k,sizeof(int),IPC_CREAT|0600);
    p = (int*)shmat(id,NULL,0);
    if (fork() == 0){
        sb[0].sem_num = 0; sb[0].sem_op = -1; sb[0].sem_flg = 0;
        sem op(sem,sb,1);
        *p = 7;
        sb[0].sem_op = 1;
        semop(sem,sb,1);
    }
    else{
        sb[0].sem_num = 0; sb[0].sem_op = -1;sb[0].sem_flg = 0;
        sleep(1);
        semop(sem,sb,1);
        printf("%i\n",*p);
        sb[0].sem_op = 1;
        semop(sem,sb,1);
    }
    shmdt(p);    
    return 0;
    
}

    
//Resp. Implementación de memoria compartida que se accede en exclusión mutua por dos procesos mediante semáforos.

