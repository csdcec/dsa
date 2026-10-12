#include <stdio.h>

void read_line(char *buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        int i = 0;
        while (buffer[i] != '\0' && buffer[i] != '\n') i++;
        if (buffer[i] == '\n') buffer[i] = '\0';
    }
}

int main(void) {
    char str[300], pat[100], rep[100], ans[1000];
    int i = 0, j = 0, found = 0;
    printf("Enter a main string:\n");
    read_line(str, sizeof(str));
    printf("Enter a pattern string:\n");
    read_line(pat, sizeof(pat));
    printf("Enter a replace string:\n");
    read_line(rep, sizeof(rep));
    if (pat[0] == '\0') {
        printf("Pattern not found\n");
        return 0;
    }
    while (str[i] != '\0' && j < (int)sizeof(ans) - 1) {
        int k = 0;
        while (pat[k] != '\0' && str[i + k] != '\0' && str[i + k] == pat[k]) k++;
        if (pat[k] == '\0') {
            int pattern_length = k;
            found = 1;
            for (k = 0; rep[k] != '\0' && j < (int)sizeof(ans) - 1; k++) ans[j++] = rep[k];
            i += pattern_length;
        } else {
            ans[j++] = str[i++];
        }
    }
    ans[j] = '\0';
    if (found) printf("The resultant string is:\n%s\n", ans);
    else printf("Pattern not found\n");
    return 0;
}
