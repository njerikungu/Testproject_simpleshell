#include "test_shell.h"

/**
 * _which - flushes out command by appending it to a matching PATH directory
 * @str: first command user typed into shell (e.g. "ls" if user typed "ls -l")
 * @env: environmental variable
 * Return: a copy of fleshed out command (e.g. "/bin/ls" if originally "ls")
 */
char *_which(char *str, list_t *env)
{

	/*** NOTE: REPLACE "cAT" WITH "CAT_sTR"* ***/
	/*** NOTE: REPLACE "TOKS" WITH "TOKENS"* ***/
	
	char *path, *cat_str = NULL, **tokens;
	int i = 0;

	/* tokenize path dirs */
	path = _getenv("PATH", env);
	tokens = c_str_tok(path, ":");
	free(path);

	/* append "/cmd" to each token to see it's legit */
	i = 0;
	while (tokens[i] != NULL)
	{
		if (tokens[i][0] == '\0')
			cat_str = getcwd(cat_str, 0);
		else
			cat_str = _strdup(tokens[i]);
		cat_str = _strcat(cat_str, "/");
		cat_str = _strcat(cat_str, str);
		if (access(cat_str, F_OK) == 0)
		{
			/* free tokens before returning legit fleshed path */
			free_double_ptr(tokens);
			return (cat_str);
		}
		free(cat_str); /* free concatenated string if cmd is never found */
		i++;
	}
	free_double_ptr(tokens);
	return (str); /* return string if not found; won't pass execve */
}