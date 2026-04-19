#include <stdio.h>

typedef struct { int size, rem; } Hole;
typedef struct { int size, hole; } Proc;

/* First Fit */
void firstfit(Hole h[], int nh, Proc p[], int np) {
    for (int i = 0; i < nh; i++) h[i].rem = h[i].size;
    for (int i = 0; i < np; i++) {
        p[i].hole = -1;
        for (int j = 0; j < nh; j++)
            if (h[j].rem >= p[i].size) { p[i].hole = j; h[j].rem -= p[i].size; break; }
    }
}

/* Best Fit */
void bestfit(Hole h[], int nh, Proc p[], int np) {
    for (int i = 0; i < nh; i++) h[i].rem = h[i].size;
    for (int i = 0; i < np; i++) {
        int best = -1;
        for (int j = 0; j < nh; j++)
            if (h[j].rem >= p[i].size && (best == -1 || h[j].rem < h[best].rem))
                best = j;
        p[i].hole = best;
        if (best != -1) h[best].rem -= p[i].size;
    }
}

/* Worst Fit */
void worstfit(Hole h[], int nh, Proc p[], int np) {
    for (int i = 0; i < nh; i++) h[i].rem = h[i].size;
    for (int i = 0; i < np; i++) {
        int worst = -1;
        for (int j = 0; j < nh; j++)
            if (h[j].rem >= p[i].size && (worst == -1 || h[j].rem > h[worst].rem))
                worst = j;
        p[i].hole = worst;
        if (worst != -1) h[worst].rem -= p[i].size;
    }
}

/* helper to print result */
void printres(char *name, Hole h[], int nh, Proc p[], int np) {
    printf("\n%s:\n", name);

    for (int i = 0; i < np; i++) {
        if (p[i].hole != -1)
            printf("P%d (%d) -> H%d\n", i, p[i].size, p[i].hole);
        else
            printf("P%d (%d) -> Not Allocated\n", i, p[i].size);
    }

    printf("Remaining holes: ");
    for (int i = 0; i < nh; i++)
        printf("%d ", h[i].rem);
    printf("\n");
}

int main() {
    int nh, np;

    printf("Number of holes: ");
    scanf("%d", &nh);

    Hole h[20];
    printf("Enter hole sizes:\n");
    for (int i = 0; i < nh; i++)
        scanf("%d", &h[i].size);

    printf("Number of processes: ");
    scanf("%d", &np);

    Proc p[20];
    printf("Enter process sizes:\n");
    for (int i = 0; i < np; i++)
        scanf("%d", &p[i].size);

    /* First Fit */
    firstfit(h, nh, p, np);
    printres("First Fit", h, nh, p, np);

    /* Best Fit */
    bestfit(h, nh, p, np);
    printres("Best Fit", h, nh, p, np);

    /* Worst Fit */
    worstfit(h, nh, p, np);
    printres("Worst Fit", h, nh, p, np);

    return 0;
}
