/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/13 20:22:09 by jmolenaa      #+#    #+#                 */
/*   Updated: 2022/11/24 11:30:59 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

char	**freeing(char ***strarray, char **strtemp)
{
	int	j;

	j = 0;
	if (strarray != (NULL) && *strarray != (NULL))
	{
		if (**strarray != (NULL))
		{
			while (*(*strarray + j) != (NULL))
			{
				free(*(*strarray + j));
				j++;
			}
		}
		free(*strarray);
		*strarray = (NULL);
	}
	if (strtemp != (NULL) && *strtemp != (NULL))
	{
		free(*strtemp);
		*strtemp = (NULL);
	}
	return (NULL);
}

int	stringcpy(char *dest, char *src, int size)
{
	int	i;

	i = 0;
	while (src != (NULL) && i < size && *(src + i) != '\0')
	{
		*(dest + i) = *(src + i);
		i++;
	}
	*(dest + i) = '\0';
	return (i);
}

char	*substr(char *str, int start, int newlineornot, int freecheck)
{
	char	*substr;
	int		length;

	length = 0;
	if (newlineornot)
	{
		while (*(str + length) != '\n')
			length++;
		length++;
	}
	else
	{
		while (*(str + length) != '\0')
			length++;
	}
	substr = (char *)malloc((length + 1) * sizeof(char));
	if (substr == (NULL))
	{
		if (freecheck)
			free(str);
		return (NULL);
	}
	stringcpy(substr, str + start, length);
	if (freecheck)
		free(str);
	return (substr);
}

int	strlenornewline(char *str)
{
	int	check;

	check = 0;
	while (*(str + check) != '\0')
	{
		if (*(str + check) == '\n')
			return (check);
		check++;
	}
	return (check);
}

char	*join(char *str, char *buff, int check)
{
	int		i;
	char	*joined;

	i = 0;
	while (str && *(str + i) != '\0')
		i++;
	joined = (char *)malloc((i + check + 1) * sizeof(char));
	if (joined == (NULL))
	{
		if (str != (NULL))
			free(str);
		return (NULL);
	}
	stringcpy(joined, str, i);
	stringcpy(joined + i, buff, check);
	if (str != (NULL))
		free(str);
	return (joined);
}
