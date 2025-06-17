#include <stdio.h>

float ft_strtof(char *start)
{
    float   result;
    float   fraction;
    float   divider;
    int     dot_seen;

    result = 0.0f;
    fraction = 0.0f;
    divider = 10.0f;
    dot_seen = 0;
    while (*start)
    {
        if (*start == '.')
        {
            if (dot_seen)
                break ;
            dot_seen = 1;
            start++;
            continue ;
        }
        if (*start >= '0' && *start <= '9')
        {
            if (!dot_seen)
                result = result * 10.0f + (*start - '0');
            else
            {
                fraction += (*start - '0') / divider;
                divider *= 10.0f;
            }
        }
        else
            break ;

        start++;
    }
    return (result + fraction);
}

int main(int ac, char **av)
{
    if (ac < 2)
    {
        printf("Usage: %s <float_string>\n", av[0]);
        return 1;
    }

    float f = ft_strtof(av[1]);
    printf("Result: %f\n", f);

    return 0;
}
