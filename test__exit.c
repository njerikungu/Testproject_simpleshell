#include "test_shell.h"

/**
 * cus_atoi - custom atoi converts string to int
 * @s: string
 * Return: number if success, -1 if string contains non-numbers
 */
int cus_atoi(char *s)
{
	int i = 0;
	unsigned int num = 0;

	while (s[i] != '\0')
	{
		/* calculate num */
		if (s[i] >= '0' && s[i] <= '9') 
			num = num * 10 + (s[i] - '0');
		if (s[i] > '9' || s[i] < '0') 
			return (-1);
		i++;
	}
	return (num);
}

/**
 * __exit - frees user input and then exits main program with a value
 * @str: user's command into shell (e.g. "exit 99")
 * @env: bring in environmental variable to free at error
 * @num: bring in nth user command line input to print in error message
 * @command: bring in command to free
 * Return: 0 if success 2 if fail
 */

/** NOTE: 
* REPLACED "COMMAND" WITH "CMD"
* REPLACED "E_VALUE" TO "EXIT_vALUE"
*/

int __exit(char **str, list_t *env, int num, char **cmd)
{
	int exit_value = 0;

	if (str[1] != NULL)
	/* if no value given after exit, return 0 */ 
		exit_value = cus_atoi(str[1]);

	if (exit_value == -1) 
	{
		/* print error msg */
		illegal_number(str[1], num, env);
		freeptr(str);
		return (2);
	}
	freeptr(str);
	free_linked_list(env);
	if (cmd != NULL)
		freeptr(cmd);
	exit(exit_value);
}