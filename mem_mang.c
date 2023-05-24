#include "shell.h"

/**
 * my_memset - fills memory with a constant byte
 * @s: the pointer to the memory area
 * @b: the byte to fill *s with
 * @n: the amount of bytes to be filled
 *
 * Return: s- a pointer to the memory area of s
 */
char *my_memset(char *s, char b, unsigned int n)
{
unsigned int i;
for (i = 0; i < n; i++)
s[i] = b;
return (s);
}

/**
 * my_free_vector - frees memory allocated to a 2D character array
 * @vec: Vector to be freed.
 *
 * Return: Nothing.
 */
void my_free_vector(char **vec)
{
char **ptr = vec;
if (!vec)
return;
while (*vec)
free(*vec++);

free(ptr);
}

/**
 * my_realloc - reallocates a block of memory
 * @ptr: pointer to previous memory allocated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer of old block
 */
void *my_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
char *p;
if (!ptr)
return (malloc(new_size));
if (!new_size)
return (free(ptr), NULL);
if (new_size == old_size)
return (ptr);
p = malloc(new_size);
if (!p)
return (NULL);
old_size = old_size < new_size ? old_size : new_size;
while (old_size--)
p[old_size] = ((char *)ptr)[old_size];
free(ptr);
return (0);
}

/**
 * my_bfree - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 (freed) 0 Otherwise
 */
int my_bfree(void **ptr)
{
if (ptr && *ptr)
{
free(*ptr);
*ptr = NULL;
return (1);
}
return (0);
}

