// implement out of ls
#include <stdio.h>
#include <string.h>

int main()
{
    char buffer[50] = {0, };
    char readBuf[50] = {0, };
    FILE* pFp = NULL;
    printf("Enter a command!\n");
    fgets(buffer, sizeof(buffer), stdin);

    pFp = popen(buffer, "r");
    if (pFp) {
        while (fgets(readBuf, sizeof(readBuf), pFp) != NULL) {
            printf("%s", readBuf);
        }
    }

    int returnStatus = pclose(pFp);
    int n = strlen(buffer);
    if (buffer[n - 1] == '\n') {
        buffer[n - 1] = '\0';
    }
    printf("`%s` executed with status %d\n", buffer, returnStatus);
    pFp = NULL;
    return 0;
}
