#include <stdio.h>

/* LRU */
void lru(int p[], int n, int fs) {
    int f[20], t[20], clk = 0, faults = 0, hits = 0;
    for (int i = 0; i < fs; i++) f[i] = -1, t[i] = 0;
    for (int i = 0; i < n; i++) {
        int hit = 0;
        for (int j = 0; j < fs; j++) if (f[j] == p[i]) {
            t[j] = ++clk;
            hits++;
            hit = 1;
            break;
        }
        if (!hit) {
            int pos = -1;
            for (int j = 0; j < fs; j++) if (f[j] == -1) { pos = j; break; }
            if (pos == -1) {
                pos = 0;
                for (int j = 1; j < fs; j++) if (t[j] < t[pos]) pos = j;
            }
            f[pos] = p[i];
            t[pos] = ++clk;
            faults++;
        }
    }
    printf("LRU faults=%d hits=%d\n", faults, hits);
}

/* LFU */
void lfu(int p[], int n, int fs) {
    int f[20], freq[20], faults = 0, hits = 0;

    for (int i = 0; i < fs; i++) f[i] = -1, freq[i] = 0;

    for (int i = 0; i < n; i++) {
        int hit = 0;

        for (int j = 0; j < fs; j++) if (f[j] == p[i]) {
            freq[j]++;
            hits++;
            hit = 1;
            break;
        }

        if (!hit) {
            int pos = -1;

            for (int j = 0; j < fs; j++) if (f[j] == -1) {
                pos = j;
                break;
            }

            if (pos == -1) {
                pos = 0;
                for (int j = 1; j < fs; j++)
                    if (freq[j] < freq[pos]) pos = j;
            }

            f[pos] = p[i];
            freq[pos] = 1;
            faults++;
        }
    }

    printf("LFU faults=%d hits=%d\n", faults, hits);
}

/* MFU */
void mfu(int p[], int n, int fs) {
    int f[20], freq[20], faults = 0, hits = 0;

    for (int i = 0; i < fs; i++) f[i] = -1, freq[i] = 0;

    for (int i = 0; i < n; i++) {
        int hit = 0;

        for (int j = 0; j < fs; j++) if (f[j] == p[i]) {
            freq[j]++;
            hits++;
            hit = 1;
            break;
        }

        if (!hit) {
            int pos = -1;

            for (int j = 0; j < fs; j++) if (f[j] == -1) {
                pos = j;
                break;
            }

            if (pos == -1) {
                pos = 0;
                for (int j = 1; j < fs; j++)
                    if (freq[j] > freq[pos]) pos = j;
            }

            f[pos] = p[i];
            freq[pos] = 1;
            faults++;
        }
    }

    printf("MFU faults=%d hits=%d\n", faults, hits);
}

int main() {
    int n, fs;
    int p[50];

    printf("Number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &p[i]);

    printf("Number of frames: ");
    scanf("%d", &fs);

    printf("\n");

    lru(p, n, fs);
    lfu(p, n, fs);
    mfu(p, n, fs);

    return 0;
}
