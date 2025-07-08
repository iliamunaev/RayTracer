#include "minirt.h"

/**
 * is_valid_argc - Check if program receives exactly one argument.
 * @argc: Argument count.
 *
 * Return: true if argc == 2 (program name + 1 file), false otherwise.
 */
static bool	is_valid_argc(int argc)
{
	if (argc != 2)
	{
		err("Usage: ./miniRT <scene.rt>");
		return (false);
	}
	return (true);
}

/**
 * has_rt_extension - Check if filename ends with ".rt".
 * @filename: File name string.
 *
 * Return: true if file has .rt extension, false otherwise.
 */
static bool	has_rt_extension(const char *filename)
{
	size_t	len = ft_strlen(filename);

	if (len < 4)
		return (false);
	return (ft_strcmp(filename + len - 3, ".rt") == 0);
}

/**
 * is_valid_filename - Validate filename is not NULL and has .rt extension.
 * @filename: File name to validate.
 *
 * Return: true if valid, false otherwise.
 */
static bool	is_valid_filename(const char *filename)
{
	if (!filename || filename[0] == '\0')
	{
		err("Filename is empty or null");
		return (false);
	}
	if (!has_rt_extension(filename))
	{
		err("File must have a .rt extension");
		return (false);
	}
	return (true);
}

/**
 * is_file_readable - Check if a file can be opened for reading.
 * @filename: File name to test.
 *
 * Return: true if file can be opened, false otherwise.
 */
static bool	is_file_readable(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		err("Error: Cannot open the file");
		return (false);
	}
	close(fd);
	return (true);
}

/**
 * validate_input_args - Validate CLI arguments and input file.
 * @argc: Argument count.
 * @argv: Argument vector.
 *
 * Return: true if all validations pass, false otherwise.
 */
bool	validate_input_args(int argc, char **argv)
{
	if (!is_valid_argc(argc))
		return (false);
	if (!is_valid_filename(argv[1]))
		return (false);
	if (!is_file_readable(argv[1]))
		return (false);
	return (true);
}
