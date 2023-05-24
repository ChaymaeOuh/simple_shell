#include "shell.h"

/**
 * my_set_zeros - sets all the bytes of an integer array to 0
 * @arr: Array to be initialized.
 * @size: Size of the array.
 *
 * Return: Nothing
 */

void my_set_zeros(unsigned int *arr, size_t size)
{
	size_t x;

	for (x = 0; x < size; x++)
		arr[x] = 0;
}

/**
 * my_set_nulls - sets all the characters in a char array to nulls
 * @arr: Array to be initialized.
 * @size: Size of the array.
 *
 * Return: Nothing
 */

void my_set_nulls(char *arr, size_t size)
{
	size_t x;

	for (x = 0; x < size; x++)
		arr[x] = '\0';
}
