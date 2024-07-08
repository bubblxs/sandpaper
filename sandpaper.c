#include <stdio.h>
#include <errno.h>
#include <sys/fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("error: invalid num of args. usage: sp <files> \n");
        return -1;
    }

    for (int i = 1; i < argc; i++)
    {
        char *fn = argv[i];
        int fd = open(fn, O_WRONLY);

        if (fd < 0)
        {
            perror("file open");
            return -1;
        }

        struct stat sb;

        if ((fstat(fd, &sb)) < 0)
        {
            perror("fstat");
            return -1;
        }

        if ((lseek(fd, 0, SEEK_SET)) < 0)
        {
            perror("fseek");
            return -1;
        }

        char b[1] = {"0"};
        long unsigned int fs = sb.st_size;

        for (int j = 0; j < 2; j++)
        {
            /* yes i am aware */
            for (long unsigned int k = 0; k < fs; k++)
            {
                write(fd, b, sizeof(b));
            }

            lseek(fd, 0, SEEK_SET);
        }

        close(fd);
    }

    return 0;
}