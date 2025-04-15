#include "main.h"

/**
 * _strcmp - Compare two strings
 * @s1: first string
 * @s2: second string
 * Return: 0 if equal, non-zero otherwise
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}
