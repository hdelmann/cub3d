#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../getnext/get_next_line.h"


int main()
{
    char *line;
    int fd;
    fd = open("../bluestone.xpm", O_RDONLY);
    line = get_next_line(fd);
    while (strcmp(line, "/* pixels */\n") != 0)
    {
        line = get_next_line(fd);
    }
    printf("line = %s\n", line);
    line = get_next_line(fd);
    while (strcmp(line, ))
}