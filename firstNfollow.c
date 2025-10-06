#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PROD 20
#define MAX_LEN 50
#define MAX_RESULT 50

int n;
char a[MAX_PROD][MAX_LEN];   // productions

// Function declarations
void follow(char Result[], char c);
void first(char Result[], char c);
void addToResultSet(char Result[], char val);

int main() {
    int i, j;
    char Result[MAX_RESULT];

    printf("Enter the number of productions: ");
    scanf("%d", &n);

    printf("Enter %d productions (use ->, epsilon as #):\n", n);
    for (i = 0; i < n; i++) {
        scanf("%s", a[i]);
        // remove "->" by shifting RHS
        memmove(a[i] + 1, a[i] + 3, strlen(a[i]) - 2);
    }

    // Find all nonterminals
    char nonTerminals[MAX_PROD];
    int ntCount = 0;
    for (i = 0; i < n; i++) {
        char nt = a[i][0];
        int found = 0;
        for (j = 0; j < ntCount; j++) {
            if (nonTerminals[j] == nt) {
                found = 1;
                break;
            }
        }
        if (!found) nonTerminals[ntCount++] = nt;
    }

    printf("\nFIRST sets:\n");
    for (i = 0; i < ntCount; i++) {
        Result[0] = '\0';
        first(Result, nonTerminals[i]);
        printf("FIRST(%c) = { ", nonTerminals[i]);
        for (j = 0; Result[j] != '\0'; j++)
            printf("%c, ", Result[j]);
        printf("}\n");
    }

    printf("\nFOLLOW sets:\n");
    for (i = 0; i < ntCount; i++) {
        Result[0] = '\0';
        follow(Result, nonTerminals[i]);
        printf("FOLLOW(%c) = { ", nonTerminals[i]);
        for (j = 0; Result[j] != '\0'; j++)
            printf("%c, ", Result[j]);
        printf("}\n");
    }

    return 0;
}

void follow(char Result[], char c) {
    int i, j;
    char subResult[MAX_RESULT];

    if (a[0][0] == c)   // start symbol
        addToResultSet(Result, '$');

    for (i = 0; i < n; i++) {
        for (j = 1; j < strlen(a[i]); j++) {
            if (a[i][j] == c) {
                int k = j + 1;

                while (a[i][k] != '\0') {
                    subResult[0] = '\0';
                    first(subResult, a[i][k]);

                    int m, hasEps = 0;
                    for (m = 0; subResult[m] != '\0'; m++) {
                        if (subResult[m] == '#')
                            hasEps = 1;
                        else
                            addToResultSet(Result, subResult[m]);
                    }

                    if (!hasEps)
                        break;

                    k++;
                }

                // Add FOLLOW(LHS) if we reached end of RHS or all following symbols are nullable
                if (a[i][k] == '\0' && a[i][0] != c)
                    follow(Result, a[i][0]);
            }
        }
    }
}


void first(char Result[], char c) {
    int i;
    if (!isupper(c) && c != '#') {
        addToResultSet(Result, c);
        return;
    }

    for (i = 0; i < n; i++) {
        if (a[i][0] == c) {
            if (a[i][1] == '#') {  // epsilon production
                addToResultSet(Result, '#');
            } else {
                int k = 1;
                while (a[i][k] != '\0') {
                    char subResult[MAX_RESULT];
                    subResult[0] = '\0';
                    first(subResult, a[i][k]);

                    int m;
                    int hasEps = 0;
                    for (m = 0; subResult[m] != '\0'; m++) {
                        if (subResult[m] == '#')
                            hasEps = 1;
                        else
                            addToResultSet(Result, subResult[m]);
                    }
                    if (!hasEps) break; // stop if epsilon not found
                    k++;
                    if (a[i][k] == '\0')
                        addToResultSet(Result, '#');
                }
            }
        }
    }
}

void addToResultSet(char Result[], char val) {
    int k;
    for (k = 0; Result[k] != '\0'; k++)
        if (Result[k] == val)
            return; // already exists

    Result[k] = val;
    Result[k + 1] = '\0';
}
