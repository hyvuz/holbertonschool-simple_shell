#include "main.h"

/**
 * _strlen - returns length of a string
 * @s: input string
 * Return: length
*/
int _strlen(const char *s)
{
int i = 0;

while (s[i])
i++;

return (i);
}
