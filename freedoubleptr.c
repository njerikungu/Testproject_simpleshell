#include "test_shell.h"

/**
 * freeptr - free malloced arrays
 * @str: array of strings
 */

/*void free_double_ptr(char **str)*/
void freeptr(char **str)
{
	/*int i = 0;*/
  int i;  

	/*while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}*/
  for (i = 0; str[i] != NULL; i++)
  {
        free(str[i]);
  }
	free(str);
}