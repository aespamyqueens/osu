#include <stdio.h>
#include <pthread.h>
#include <limits.h>

#define MAX 20
#define Q 3

struct Process {
    int pid, at, bt, pr;
};

struct Process p[MAX];
int n;

void* fcfs(void* arg)
{
    int ct[MAX], wt[MAX], tat[MAX];
    int t=0;

    printf("\n--- FCFS Scheduling ---\n");

    for(int i=0;i<n;i++)
    {
        if(t < p[i].at)
            t = p[i].at;

        t += p[i].bt;
        ct[i] = t;

        tat[i] = ct[i] - p[i].at;
        wt[i] = tat[i] - p[i].bt;
    }

    printf("PID AT BT CT WT TAT\n");

    for(int i=0;i<n;i++)
        printf("%d %d %d %d %d %d\n",
        p[i].pid,p[i].at,p[i].bt,
        ct[i],wt[i],tat[i]);

    pthread_exit(NULL);
}

void* round_robin(void* arg)
{
    int rem_bt[MAX], ct[MAX], wt[MAX], tat[MAX];
    int t=0, done;

    printf("\n--- Round Robin Scheduling ---\n");

    for(int i=0;i<n;i++)
        rem_bt[i] = p[i].bt;

    while(1)
    {
        done = 1;

        for(int i=0;i<n;i++)
        {
            if(rem_bt[i] > 0)
            {
                done = 0;

                if(rem_bt[i] > Q)
                {
                    t += Q;
                    rem_bt[i] -= Q;
                }
                else
                {
                    t += rem_bt[i];
                    ct[i] = t;
                    rem_bt[i] = 0;

                    tat[i] = ct[i] - p[i].at;
                    wt[i] = tat[i] - p[i].bt;
                }
            }
        }

        if(done)
            break;
    }

    printf("PID AT BT CT WT TAT\n");

    for(int i=0;i<n;i++)
        printf("%d %d %d %d %d %d\n",
        p[i].pid,p[i].at,p[i].bt,
        ct[i],wt[i],tat[i]);

    pthread_exit(NULL);
}

void* srtf(void* arg)
{
    int rt[MAX], ct[MAX], wt[MAX], tat[MAX];
    int completed=0,t=0;

    printf("\n--- SRTF Scheduling ---\n");

    for(int i=0;i<n;i++)
        rt[i] = p[i].bt;

    while(completed<n)
    {
        int shortest=-1;

        for(int i=0;i<n;i++)
        {
            if(p[i].at<=t && rt[i]>0)
            {
                if(shortest==-1 || rt[i]<rt[shortest])
                    shortest=i;
            }
        }

        if(shortest==-1)
        {
            t++;
            continue;
        }

        rt[shortest]--;
        t++;

        if(rt[shortest]==0)
        {
            completed++;

            ct[shortest]=t;
            tat[shortest]=ct[shortest]-p[shortest].at;
            wt[shortest]=tat[shortest]-p[shortest].bt;
        }
    }

    printf("PID AT BT CT WT TAT\n");

    for(int i=0;i<n;i++)
        printf("%d %d %d %d %d %d\n",
        p[i].pid,p[i].at,p[i].bt,
        ct[i],wt[i],tat[i]);

    pthread_exit(NULL);
}

void* priority_preemptive(void* arg)
{
    int rt[MAX], ct[MAX], wt[MAX], tat[MAX];
    int completed=0,t=0;

    printf("\n--- Preemptive Priority Scheduling ---\n");

    for(int i=0;i<n;i++)
        rt[i] = p[i].bt;

    while(completed<n)
    {
        int idx=-1;

        for(int i=0;i<n;i++)
        {
            if(p[i].at<=t && rt[i]>0)
            {
                if(idx==-1 || p[i].pr>p[idx].pr)
                    idx=i;
            }
        }

        if(idx==-1)
        {
            t++;
            continue;
        }

        rt[idx]--;
        t++;

        if(rt[idx]==0)
        {
            completed++;

            ct[idx]=t;
            tat[idx]=ct[idx]-p[idx].at;
            wt[idx]=tat[idx]-p[idx].bt;
        }
    }

    printf("PID AT BT PR CT WT TAT\n");

    for(int i=0;i<n;i++)
        printf("%d %d %d %d %d %d %d\n",
        p[i].pid,p[i].at,p[i].bt,p[i].pr,
        ct[i],wt[i],tat[i]);

    pthread_exit(NULL);
}

int main()
{
    pthread_t t1,t2,t3,t4;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(int i=0;i<n;i++)
    {
        p[i].pid=i+1;

        printf("\nProcess %d\n",i+1);

        printf("Arrival Time: ");
        scanf("%d",&p[i].at);

        printf("Burst Time: ");
        scanf("%d",&p[i].bt);

        printf("Priority: ");
        scanf("%d",&p[i].pr);
    }

    pthread_create(&t1,NULL,fcfs,NULL);
    pthread_join(t1,NULL);

    pthread_create(&t2,NULL,round_robin,NULL);
    pthread_join(t2,NULL);

    pthread_create(&t3,NULL,srtf,NULL);
    pthread_join(t3,NULL);

    pthread_create(&t4,NULL,priority_preemptive,NULL);
    pthread_join(t4,NULL);

    return 0;
}
