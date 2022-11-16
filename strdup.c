#include "test_shell.h"

/**
 * _strdup - returns a pointer to a newly allocated space in memory,
 * which contains a copy of the string given as a parameter
 * @str: string to duplicate
 * Return: pointer to duplicated string in allocated memory
 */
char *_strdup(char *str)
{
	char *str_dup;
	int i, len = 0;

	if (str == NULL) /* validate str input */
		return (NULL);

	while (str[len])
		len++;
	len++; /* add null terminator to length */

	str_dup = malloc(sizeof(char) * len); /* allocate memory */
	if (str_dup == NULL)
		return (NULL);

	i = 0;
	while (i < len)
    /*for (i = 0; i < len; i++)
    */
	{
		str_dup[i] = str[i];
		i++;
	}

	return (str_dup);
}