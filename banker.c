#include <stdio.h>
#include <stdbool.h>

/* your function 그대로 */
void banker(int n, int m, int alloc[n][m], int max[n][m], int total[m]) {
    int need[n][m], avail[m], work[m], seq[n];
    bool done[n];

    for (int j = 0; j < m; j++) {
        int sum = 0;
        for (int i = 0; i < n; i++) sum += alloc[i][j];
        avail[j] = total[j] - sum;
        work[j] = avail[j];
    }

    for (int i = 0; i < n; i++) done[i] = false;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    int c = 0;

    while (c < n) {
        int found = 0;

        for (int i = 0; i < n; i++) if (!done[i]) {
            int ok = 1;

            for (int j = 0; j < m; j++)
                if (need[i][j] > work[j]) ok = 0;

                if (ok) {
                    for (int j = 0; j < m; j++)
                        work[j] += alloc[i][j];

                    seq[c++] = i;
                    done[i] = true;
                    found = 1;
                }
        }

        if (!found) {
            printf("Unsafe\n");
            return;
        }
    }

    printf("Safe: ");
    for (int i = 0; i < n; i++) printf("P%d ", seq[i]);
    printf("\n");
}

int main() {
    int n, m;

    printf("Processes: ");
    scanf("%d", &n);

    printf("Resources: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], total[m];

    printf("Enter Allocation matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Max matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Total resources:\n");
    for (int j = 0; j < m; j++)
        scanf("%d", &total[j]);

    banker(n, m, alloc, max, total);

    return 0;
}
