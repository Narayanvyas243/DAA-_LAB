#include<stdio.h>
#include<ctype.h>
int main()
{
    char s[1000];
    int alph=0,dig=0,spe=0;
    gets(s);
    for (int i=0; s[i] != '\0';i++){
        if (isalpha(s[i])){
            alph++;
        }
        else if (isdigit(s[i])){
            dig++;
        }
        else {
            spe++;
        }
        
    }
    printf("%d apphabets=",alph);
    printf("%d digits= ",dig);
    printf("%d special=",spe);
    return 0;
}
