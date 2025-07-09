#include "minirt.h"

/**
 * @brief Check if the program received the correct number
 * of command-line arguments.
 *
 * The program expects exactly one argument: the path to a `.rt` scene file.
 *
 * @param argc The argument count passed to main().
 * @return true if argc == 2, false otherwise.
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
 * @brief Check if a file name ends with the ".rt" extension.
 *
 * @param filename The name of the file to check.
 * @return true if the file ends with ".rt", false otherwise.
 */
static bool	has_rt_extension(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (false);
	return (ft_strcmp(filename + len - 3, ".rt") == 0);
}

/**
 * @brief Validate that the file name is non-empty and has a `.rt` extension.
 *
 * @param filename The name of the file to validate.
 * @return true if the file name is valid and ends with ".rt", false otherwise.
 */
static bool	is_valid_filename(const char *filename)
{
	if (!filename || filename[0] == '\0')
	{
		err("Error: Filename is empty or null");
		return (false);
	}
	if (!has_rt_extension(filename))
	{
		err("Error: File must have a .rt extension");
		return (false);
	}
	return (true);
}

/**
 * @brief Check if a file is readable by attempting to open it.
 *
 * This helps verify that the file exists and the user
 * has read permissions.
 *
 * @param filename The name of the file to open.
 * @return true if the file can be opened for reading, false otherwise.
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
 * @brief Perform full validation of command-line input arguments.
 *
 * This function checks that:
 * - The correct number of arguments is provided.
 * - The file name is not empty and ends with ".rt".
 * - The file exists and can be opened for reading.
 *
 * @param argc The argument count from main().
 * @param argv The argument vector from main().
 * @return true if all input validations pass, false otherwise.
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
