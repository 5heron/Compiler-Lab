// Grammar:
// E  → T E'
// E' → (+|-) T E' | ε
// T  → F T'
// T' → (*|/) F T' | ε
// F  → (E) | id        

#include <stdio.h>
#include <ctype.h>

char s[128];
int cnt = 0;
int E(), E_(), T(), T_(), F();

int E() {
    if (T())
        if (E_())
            return 1;
    return 0;
}

int E_() {
    if (s[cnt] == '+' || s[cnt] == '-') {
        cnt++;
        if (T())
            if (E_())
                return 1;
        return 0;
    }
    return 1;   
}

int T() {
    if (F())
        if (T_())
            return 1;
    return 0;
}

int T_() {
    if (s[cnt] == '*' || s[cnt] == '/') {
        cnt++;
        if (F())
            if (T_())
                return 1;
        return 0;
    }
    return 1;   
}

int F() {
    if (s[cnt] == '(') {
        cnt++;
        if (E()) {
            if (s[cnt] == ')') {
                cnt++;
                return 1;
            }
        }
        return 0;
    } else if (isalnum((unsigned char)s[cnt])) {
        cnt++;                  
        return 1;
    }
    return 0;
}

int main() {
    printf("Enter Expression to Validate: ");
    scanf("%127s", s);          
    if (E() && s[cnt] == '\0')
        printf("Expression is Valid.\n");
    else
        printf("Expression is Invalid.\n");
    return 0;
}
