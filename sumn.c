// parent.c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main() {

    int n;
    printf("Enter number of students: ");
    scanf("%d",&n);

    int id[n], pages[n];

    for(int i=0;i<n;i++){
        printf("Enter Student ID: ");
        scanf("%d",&id[i]);

        printf("Enter pages to print: ");
        scanf("%d",&pages[i]);
    }

    printf("\nStudentID\tPages\n");
    for(int i=0;i<n;i++)
        printf("%d\t\t%d\n",id[i],pages[i]);

    int fd[2];
    pipe(fd);

    pid_t pid = fork();

    if(pid>0)  // parent
    {
        close(fd[0]);

        write(fd[1],&n,sizeof(int));
        write(fd[1],id,sizeof(int)*n);
        write(fd[1],pages,sizeof(int)*n);

        close(fd[1]);

        wait(NULL);
    }

    else       // child
    {
        close(fd[1]);

        dup2(fd[0],0); // redirect pipe to stdin

        execl("./printerAccess","printerAccess",NULL);

        perror("exec failed");
    }

    return 0;
}

//printeraccess.c

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define MAX 50
#define PRINTERS 3

sem_t printers;

int id[MAX];
int pages[MAX];
int n;

void* print_job(void *arg)
{
    int i = *(int*)arg;

    printf("\nStudent %d requesting printer\n",id[i]);

    if(sem_trywait(&printers)!=0)
    {
        printf("All printers busy. Student %d waiting...\n",id[i]);
        sem_wait(&printers);
    }

    int printer_no = (i % PRINTERS) + 1;

    printf("Student %d allocated Printer %d\n",id[i],printer_no);
    printf("Student %d printing %d pages\n",id[i],pages[i]);

    sleep(2);

    printf("Student %d finished printing and released printer\n",id[i]);

    sem_post(&printers);

    return NULL;
}

int main()
{
    read(0,&n,sizeof(int));
    read(0,id,sizeof(int)*n);
    read(0,pages,sizeof(int)*n);

    pthread_t t[n];
    int index[n];

    sem_init(&printers,0,PRINTERS);

    for(int i=0;i<n;i++)
    {
        index[i]=i;
        pthread_create(&t[i],NULL,print_job,&index[i]);
    }

    for(int i=0;i<n;i++)
        pthread_join(t[i],NULL);

    sem_destroy(&printers);

    return 0;
}
