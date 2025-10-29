#include <stdio.h>
#include <ctype.h>

char input[128];
int i = 0;

// Forward declarations
int S(); // Start symbol
int A();
int B();

int match(char c) {
    if (input[i] == c) {
        i++;
        return 1;
    }
    return 0;
}

// Example Grammar (you replace these with your own):
// S → a A
// A → b B | ε
// B → c
int S() {
    if (match('a'))
        if (A())
            return 1;
    return 0;
}

int A() {
    if (match('b')) {
        if (B())
            return 1;
        return 0;
    }
    return 1; // ε
}

int B() {
    if (match('c'))
        return 1;
    return 0;
}

int main() {
    printf("Enter input: ");
    scanf("%127s", input);
    if (S() && input[i] == '\0')
        printf("String is valid.\n");
    else
        printf("String is invalid.\n");
}