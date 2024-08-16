#include "src/minishell.h"
#include "sys/stat.h"

unsigned int    ft_getuid()
{
    int fd = open("/tmp", O_CREAT | O_WRONLY | __O_TMPFILE, S_IRUSR | S_IWUSR);
    struct stat st;
    if (fstat(fd, &st) == -1)
        return 1;
    uid_t uid = st.st_uid;
    printf("%u\n", uid);
    close(fd);
    return (uid);
}

int	gethomer(char ***buff, char **str, char *uid)
{
	*buff = ft_split(*str, ':');
	if (!(*buff))
		return (0);
	if (!ft_strncmp((*buff)[2], uid, -1))
		return (1);
	free(*str);
	*str = NULL;
	return (0);
}

char    *gethome(char   *uid)
{
    int     fd = open("/etc/passwd", O_RDONLY, 0777);
    char    buf[2];
    char    **splitbuf;
    char    *str;

	str = NULL;
    while (read(fd, buf, 1))
    {
        buf[1] = '\0';
        if (!str)
            str = ft_strdup(buf);
        else
            str = ft_strjoin(str, buf);
        if (buf[0] == '\n')
        {
            if (gethomer(&splitbuf, &str, uid))
				return (splitbuf[5]);
        }
    }
    return (NULL);
}

int main()
{
    unsigned int    uid = getuid();
    char            *home = gethome(ft_itoa((int) uid));
	printf("%s\n", home);
}