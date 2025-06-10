#include "minirt.h"

int main(void)
{
    t_matrix inverted;  // To store the inverse of m_b
    t_matrix m_a;       // Original matrix A
    t_matrix m_b;       // Original matrix B
    t_matrix m_c;       // Result of A × B
    t_matrix result;    // Final result: (A × B) × B⁻¹ → should equal A

    // Data for matrix A (4x4)
    float data[16] = {
        3, -9, 7, 3,
        3, -8, 2, -9,
        -4, 4, 4, 1,
        -6, 5, -1, 1
    };

    // Data for matrix B (4x4)
    float data_2[16] = {
        8, 2, 2, 2,
        3, -1, 7, 0,
        7, 0, 5, 4,
        6, -2, 0, 5
    };

    // Create and display matrix A
    create_matrix_4x4(&m_a, data);
    printf("Matrix A:\n");
    print_matrix(m_a);
    printf("\n");

    // Create and display matrix B
    create_matrix_4x4(&m_b, data_2);
    printf("Matrix B:\n");
    print_matrix(m_b);
    printf("\n");

    // Multiply A × B → store in m_c
    mult_matrices(&m_c, m_a, m_b);

    // Invert matrix B → store in inverted
    invert_matrix(&inverted, m_b);

    // Multiply (A × B) × B⁻¹ → should result in A
    mult_matrices(&result, m_c, inverted);

    // Display the resulting matrix
    printf("Result:\n");
    print_matrix(result);

    // Check if final result is equal to original matrix A
    int equal = are_matrices_equal(m_a, result);
    if (equal)
        printf("\nMatrices are equal.\n");
    else
        printf("\nMatrices are not equal.\n");

    return (0);
}
