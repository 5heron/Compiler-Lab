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
    char nonTerminals[MAX_PROD]; //set of all unique nonterminals
    int ntCount = 0;
    for (i = 0; i < n; i++) { //go through productions
        char nt = a[i][0]; //Take LHS - Non terminals
        int found = 0;
        for (j = 0; j < ntCount; j++) { //go through set
            if (nonTerminals[j] == nt) { //if non terminal found
                found = 1;
                break;
            }
        }
        if (!found) nonTerminals[ntCount++] = nt; //add the new non terminal to char set
    }

    printf("\nFIRST sets:\n");
    for (i = 0; i < ntCount; i++) { //go through all non terminals
        Result[0] = '\0';
        first(Result, nonTerminals[i]); //find first
        printf("FIRST(%c) = { ", nonTerminals[i]); 
        for (j = 0; Result[j] != '\0'; j++) //print the resultant first set
            printf("%c, ", Result[j]);
        printf("}\n");
    }

    printf("\nFOLLOW sets:\n");
    for (i = 0; i < ntCount; i++) { //go through all non terminals
        Result[0] = '\0';
        follow(Result, nonTerminals[i]); //find follow
        printf("FOLLOW(%c) = { ", nonTerminals[i]);
        for (j = 0; Result[j] != '\0'; j++) //print the resultant follow set
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

    for (i = 0; i < n; i++) { //for each grammar production
        for (j = 1; j < strlen(a[i]); j++) { //traverse its RHS
            if (a[i][j] == c) { //Follow character is found
                int k = j + 1; //take next character

                while (a[i][k] != '\0') {
                    subResult[0] = '\0';
                    first(subResult, a[i][k]); //find first of next character
                    int m, hasEps = 0;
                    for (m = 0; subResult[m] != '\0'; m++) {
                        if (subResult[m] == '#') //if first has epsilon
                            hasEps = 1;
                        else
                            addToResultSet(Result, subResult[m]); //add non epsilon values to result
                    }

                    if (!hasEps) //if no epsilon dont take next character
                        break;

                    k++; //take next character (epsilon)
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

    for (i = 0; i < n; i++) { //for each production
        if (a[i][0] == c) { //take production of character(LHS)
            if (a[i][1] == '#') {  // epsilon production
                addToResultSet(Result, '#');
            } else {
                int k = 1; 
                while (a[i][k] != '\0') { //traverse RHS
                    char subResult[MAX_RESULT];
                    subResult[0] = '\0';
                    first(subResult, a[i][k]); //take first of characters in RHS

                    int m;
                    int hasEps = 0;
                    for (m = 0; subResult[m] != '\0'; m++) {
                        if (subResult[m] == '#') //if epsilon in first of character
                            hasEps = 1;
                        else
                            addToResultSet(Result, subResult[m]); //add non epsilon values to result
                    }
                    if (!hasEps) break; // stop if epsilon not found
                    k++; //take next character epsilon found!
                    if (a[i][k] == '\0')
                        addToResultSet(Result, '#'); //if RHS fully traversed, add epsilon to result 
                }
            }
        }
    }
}

void addToResultSet(char Result[], char val) {
    int k;
    for (k = 0; Result[k] != '\0'; k++) //result is a char array containing first or follow char set
        if (Result[k] == val)
            return; // already exists, exit

    Result[k] = val; //add new unique char to set
    Result[k + 1] = '\0'; //move end of string
}
