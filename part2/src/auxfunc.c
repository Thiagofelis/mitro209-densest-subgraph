#include "../inc/auxfunc.h"

int read(FILE* fp, char* buffer)
{
    int i = 0;
    char temp;
    do{
        temp = fgetc(fp);
    } while ((temp == ' ') || (temp == '\n') || (temp == '\r'));

    while ((temp != ' ') && (temp != '\n') && (temp != '\r') && (temp != EOF))
    {
        buffer[i] = temp;
        i++;
        temp = fgetc(fp);
    }
    buffer[i] = '\0';

    if (buffer[0] == '\0')
    {
        printf("problema na formatacao\n");
        return EOF;
    }
    return 0;
}
