#include "minirt.h"

int main()
{
    float data[16];
    int i = 0;


    fill_data_arr(data, 1.0f, 2.0f, 3.0f, 4.0f); // Pass 'data' directly, not '&data'

    while(i < 16)
    {
        printf("%f ", data[i]);
        i++;
    }
    printf("\n"); // Add a newline for cleaner output
    return 0;
}