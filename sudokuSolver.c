#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 9

int judge();
void error(int);
void makeOriginalTable();
void makeUseTable();
void show();
void solve();
void makeCheckArray();
int checkCheckArray();
void saiki(int);
int isDuplicate(int, int);

int originalTable[N][N];
int useTable[N][N];
int check[N + 1];
char *problemFilePath = "./Problems/p6.txt";

int main()
{
    clock_t c_start, c_end;
    c_start = clock();
    solve();
    c_end = clock();
    printf("%f\n", (double)(c_end - c_start) / CLOCKS_PER_SEC);
    return 0;
}
int judge()
{
    int i, j, k, l;
    makeCheckArray();
    // block
    for (i = 0; i < N; i += 3)
    {
        for (j = 0; j < N; j += 3)
        {
            makeCheckArray();
            for (k = i; k < i + (N / 3); k++)
                for (l = j; l < j + (N / 3); l++)
                    check[useTable[k][l]]--;
            if (checkCheckArray() == 0)
                return 0;
        }
    }
    // row
    for (i = 0; i < N; i++)
    {
        makeCheckArray();
        for (j = 0; j < N; j++)
        {
            check[useTable[i][j]]--;
        }
        if (checkCheckArray() == 0)
            return 0;
    }
    // column
    for (i = 0; i < N; i++)
    {
        makeCheckArray();
        for (j = 0; j < N; j++)
        {
            check[useTable[j][i]]--;
        }
        if (checkCheckArray() == 0)
            return 0;
    }
    return 1;
}
void error(int num)
{
    switch (num)
    {
    case 0:
    {
        printf("init(): fp == NULL");
        exit(0);
        break;
    }
    case 1:
    {
        printf("init(): buf == EOF");
        exit(1);
        break;
    }
    default:
        break;
    }
}
void makeOriginalTable()
{
    FILE *fp = fopen(problemFilePath, "r");
    char buf;
    int i, j;
    if (fp == NULL)
        error(0);
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            fscanf(fp, "%c,", &buf);
            if (buf == ',' || buf == '\n')
            {
                j--;
                continue;
            }
            originalTable[i][j] = atoi(&buf);
        }
    }
}
void makeUseTable()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            useTable[i][j] = originalTable[i][j];
}
void show()
{
    for (int i = 0; i < N; i++)
    {
        if (i % (N / 3) == 0)
            printf("  - - -   - - -   - - -  \n");
        for (int j = 0; j < N; j++)
        {
            if (j % (N / 3) == 0)
                printf("| ");
            printf("%d ", useTable[i][j]);
        }
        printf("|\n");
    }
    printf("  - - -   - - -   - - -  \n\n");
}
void solve()
{
    makeOriginalTable();
    makeUseTable();
    saiki(0);
}
void makeCheckArray()
{
    check[0] = 0; // 0は各ブロック各列各行に0個でいてほしい
    for (int i = 1; i < N + 1; i++)
        check[i] = 1;
}
int checkCheckArray()
{
    for (int i = 0; i < N; i++)
    {
        if (check[i] != 0)
            return 0; //
    }
    return 1;
}
void saiki(int num)
{
    // system("cls"); ////////////////////////////////////////////// for fun!
    int r = num / N, c = num % N, i;
    if (num >= N * N)
        return;
    if (originalTable[r][c] != 0)
    {
        saiki(num + 1);
        return;
    }
    while (useTable[r][c] < N)
    {
        if (isDuplicate(num, ++useTable[r][c]))
            continue;
        // show(); /////////////////////////////////////////////// for fun!
        if (judge() == 1)
        {
            show();
            return;
        }
        saiki(num + 1);
    }
    useTable[r][c] = originalTable[r][c];
}
int isDuplicate(int place, int num)
{
    int r = place / N, c = place % N, i, j, cnt = 0;
    for (i = 0; i < N; i++)
    {
        if (useTable[r][i] == num)
            cnt++;
    }
    if (cnt != 1)
        return 1;
    cnt = 0;
    for (i = 0; i < N; i++)
    {
        if (useTable[i][c] == num)
            cnt++;
    }
    if (cnt != 1)
        return 1;
    cnt = 0;
    while ((r--) % (N / 3) != 0)
        ;
    while ((c--) % (N / 3) != 0)
        ;
    r++;
    c++;
    for (i = r; i < (r + (N / 3)); i++)
    {
        for (j = c; j < (c + (N / 3)); j++)
        {
            if (useTable[i][j] == num)
                cnt++;
        }
    }
    if (cnt != 1)
        return 1;
    return 0;
}