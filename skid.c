#include <stdio.h>
#include <stdlib.h>

int cmpi(const void *a, const void *b) { return *(int *)a - *(int *)b; }

/* FCFS */
int fcfs(int r[], int n, int head) {
    int m = 0, cur = head;
    for (int i = 0; i < n; i++) {
        m += abs(r[i] - cur);
        cur = r[i];
    }
    return m;
}

/* SSTF */
int sstf(int r[], int n, int head) {
    int v[20] = {0}, cur = head, m = 0;

    for (int k = 0; k < n; k++) {
        int pos = -1, best = 1e9;

        for (int i = 0; i < n; i++) if (!v[i] && abs(r[i] - cur) < best) {
            best = abs(r[i] - cur);
            pos = i;
        }

        v[pos] = 1;
        m += best;
        cur = r[pos];
    }

    return m;
}

int main() {
    int n, head;
    int r[20];

    printf("Number of requests: ");
    scanf("%d", &n);

    printf("Enter request sequence:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &r[i]);

    printf("Initial head position: ");
    scanf("%d", &head);

    int fcfs_m = fcfs(r, n, head);
    int sstf_m = sstf(r, n, head);

    printf("\nFCFS total movement = %d\n", fcfs_m);
    printf("SSTF total movement = %d\n", sstf_m);

    return 0;
}
