/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/13 20:22:09 by jmolenaa      #+#    #+#                 */
/*   Updated: 2022/11/17 09:23:05 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

char	*freeing(char **str, char **strtemp)
{
	if (str != (NULL))
	{
		if (*str != (NULL))
		{
			free(*str);
			*str = (NULL);
		}
	}
	if (*strtemp != (NULL))
	{
		free(*strtemp);
		*strtemp = (NULL);
	}
	return (NULL);
}

void	stringcpy(char *dest, char *src, int size)
{
	int	i;

	i = 0;
	while (src != (NULL) && i < size && *(src + i) != '\0')
	{
		*(dest + i) = *(src + i);
		i++;
	}
	*(dest + i) = '\0';
}

char	*substr(char **strtemp, int strtemplenornewline)
{
	int		i;
	char	*substr;

	i = 0;
	while (*(*strtemp + strtemplenornewline + i) != '\0')
		i++;
	substr = (char *)malloc((i + 1) * sizeof(char));
	if (substr == (NULL))
	{
		free(*strtemp);
		return (NULL);
	}
	stringcpy(substr, *strtemp + strtemplenornewline, BUFFER_SIZE);
	free(*strtemp);
	return (substr);
}

int	strlenornewline(char *str, int i)
{
	int	check;

	check = 0;
	while (check < i && *(str + check) != '\0')
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
