#include "test_shell.h"

/**
 * _getline - stores into malloced buffer the user's command into shell
 * @str: buffer
 * Return: number of characters read
 */
size_t _getline(char **str)
{
	ssize_t nread = 0, size = 0, t = 0, t2 = 0, n = 0;
	char buff[1024];

	nread = read(STDIN_FILENO, buff, 1024 - 1);
	while (t2 == 0 && nread)
	{
		if (nread == -1)
			return (-1);
		buff[nread] = '\0';
		n = 0;
		while (buff[n] != '\0')
		{
			if (buff[n] == '\n')
				t2 = 1;
			n++;
		}

		if (t == 0)
		{
			nread++;
			*str = malloc(sizeof(char) * nread);
			*str = _strcpy(*str, buff);
			size = nread;
			t = 1;
		}
		else
		{
			size += nread;
			*str = _strcat(*str, buff);
		}
	}
	return (size);
}

// size_t get_line(char **str)
// {
// 	ssize_t i = 0, size = 0, t = 0, t2 = 0, n = 0;
// 	char buff[1024];

// 	while (t2 == 0 && (i = read(STDIN_FILENO, buff, 1024 - 1)))
// 	{
// 		if (i == -1) /* check if read errored */
// 			return (-1);

// 		buff[i] = '\0'; /* terminate buff with \0 to use with _strcat */

// 		n = 0; /* last loop if \n is found in the stdin read */
// 		while (buff[n] != '\0')
// 		{
// 			if (buff[n] == '\n')
// 				t2 = 1;
// 			n++;
// 		}

// 		/* copy what's read to buff into get_line's buffer */
// 		if (t == 0) /* malloc the first time */
// 		{
// 			i++;
// 			*str = malloc(sizeof(char) * i);
// 			*str = _strcpy(*str, buff);
// 			size = i;
// 			t = 1;
// 		}
// 		else /* _realloc via _strcat with each loop */
// 		{
// 			size += i;
// 			*str = _strcat(*str, buff);
// 		}
// 	}
// 	return (size);
// }