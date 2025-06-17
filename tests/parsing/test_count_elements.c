#include <stdio.h>
#include <stdint.h>


int	ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\f' || c == '\r'
		|| c == '\t' || c == '\v');
}

uint8_t count_elements(const char *map)
{
    uint8_t count;

    count = 0;
    while (*map)
    {
        while (*map && ft_isspace(*map) && *map != '\n')
            map++;
        if (*map && *map != '\n')
            count++;
        while (*map && *map != '\n')
            map++;
        if (*map == '\n')
            map++;
    }
    return (count);
}

int main()
{
	char *map =
		"A 0.2 255,255,255\n"
		"C -50,0,20 0,0,0 70\n"
		// "L -40,0,30 0.7 255,255,255\n"
		"pl 0,0,0 0,1.0,0 255,0,225\n"
		"sp 0,0,20 20 255,0,0\n\n"
		"\n"
		"cy 50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255\n";

	uint8_t e = count_elements(map);

    printf("Elements counted: %i\n", e);

    return 0;
}
