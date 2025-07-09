#include "minirt.h"

/**
 * @brief Print a message indicating a mode change in the application.
 *
 * Depending on `mode_1`, this function prints either "Start mode" or "End mode".
 * Then it matches `mode_2` to a human-readable string
 * representation of the mode:
 * CAM, SCALE, ROTATE, TRANSLATE, or an invalid fallback message.
 *
 * @param mode_1 Indicates the context of the mode (start or end).
 * @param mode_2 The mode being activated or deactivated.
 */
void	print_mode(int mode_1, int mode_2)
{
	char	*msg_1;
	char	*msg_2;

	if (mode_1 == MODE_NONE)
		msg_1 = "End mode: ";
	else if (mode_1 > MODE_NONE && mode_1 <= MODE_CAM)
		msg_1 = "Start mode:";
	else
		msg_1 = "Invalide action";
	if (mode_2 == MODE_CAM)
		msg_2 = "CAM";
	else if (mode_2 == MODE_SCALE)
		msg_2 = "SCALE";
	else if (mode_2 == MODE_ROTATE)
		msg_2 = "ROTATE";
	else if (mode_2 == MODE_TRANSLATE)
		msg_2 = "TRANSLATE";
	else
		msg_2 = "Invalide mode";
	printf("%s %s\n", msg_1, msg_2);
}
