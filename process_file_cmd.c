#include "simpleshell.h"

/**
 * cant_open - If the file doesn't exist or lacks proper permissions, print
 * throw error.
 * @path_name: Path to the supposed file.
 * Return: 127.
 */

int cant_open(char *path_name)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (127);

	len = _strlen(name) + _strlen(hist_str) + _strlen(path_name) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (127);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": Can't open ");
	_strcat(error, path_name);
	_strcat(error, "\n");

	free(hist_str);
	write(STDERR_FILENO, error, len);
	free(error);
	return (127);
}

/**
 * process_file_cmd - Takes a file and attempts to run the commands stored
 * within.
 * @path_name: Path to the file.
 * @ret_val: Return value of the last executed command.
 * Return: If file couldn't be opened - 127.
 * if malloc fails - -1. Otherwise the return last command.
 */
int process_file_cmd(char *path_name, int *ret_val)
{
	ssize_t file, b_read, i;
	unsigned int line_size = 0;
	unsigned int old_size = 120;
	char *line, **args, **front;
	char buffer[120];
	int val;

	hist = 0;
	file = open(path_name, O_RDONLY);
	if (file == -1)
	{
		*ret_val = cant_open(path_name);
		return (*ret_val);
	}
	line = malloc(sizeof(char) * old_size);
	if (!line)
		return (-1);
	do {
		b_read = read(file, buffer, 119);
		if (b_read == 0 && line_size == 0)
			return (*ret_val);
		buffer[b_read] = '\0';
		line_size += b_read;
		line = _realloc(line, old_size, line_size);
		_strcat(line, buffer);
		old_size = line_size;
	} while (b_read);
	for (i = 0; line[i] == '\n'; i++)
		line[i] = ' ';
	for (; i < line_size; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = ';';
			for (i += 1; i < line_size && line[i] == '\n'; i++)
				line[i] = ' ';
		}
	}
	variable_replacement(&line, ret_val);
	handle_line(&line, line_size);
	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (0);
	if (check_args(args) != 0)
	{
		*ret_val = 2;
		free_args(args, args);
		return (*ret_val);
	}
	front = args;

	for (i = 0; args[i]; i++)
	{
		if (_strncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			val = call_args(args, front, ret_val);
			args = &args[++i];
			i = 0;
		}
	}

	val = call_args(args, front, ret_val);

	free(front);
	return (val);
}