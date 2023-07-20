/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 16:36:41 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/20 09:26:24 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

char	*createreturnstring(char **strarray)
{
	char	*returnstr;
	int		i;
	int		j;
	int		alloc;

	j = 0;
	alloc = 0;
	while (*(strarray + j) != (NULL))
	{
		i = strlenornewline(*(strarray + j));
		if (*(*(strarray + j) + i) == '\n')
			i++;
		alloc = alloc + i;
		j++;
	}
	returnstr = (char *)malloc((alloc + 1) * sizeof(char));
	if (returnstr == (NULL))
		return (freeing(&strarray, (NULL)), (NULL));
	i = 0;
	j = 0;
	while (*(strarray + j) != (NULL))
	{
		i = i + stringcpy(returnstr + i, *(strarray + j), BUFFER_SIZE);
		j++;
	}
	freeing(&strarray, (NULL));
	return (returnstr);
}

char	**allocdouble(char **strarray, char *buff, int newlineornot)
{
	char	**newstrarray;
	int		i;

	i = 0;
	while (strarray != (NULL) && *(strarray + i) != (NULL))
		i++;
	newstrarray = (char **)malloc((i + 2) * sizeof(char *));
	if (newstrarray == (NULL))
	{
		freeing(&strarray, NULL);
		return (NULL);
	}
	*(newstrarray + i + 1) = (NULL);
	*(newstrarray + i) = substr(buff, 0, newlineornot, 0);
	if (*(newstrarray + i) == (NULL))
	{
		freeing(&strarray, NULL);
		free(newstrarray);
		return (NULL);
	}
	while (i > 0)
	{
		i--;
		*(newstrarray + i) = *(strarray + i);
	}
	return (free(strarray), newstrarray);
}

char	**nextlinenobuffer(int fd, char **strarray, char **strtemp, char *buff)
{
	int		i;
	int		check;

	i = 1;
	while (i)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i == -1)
			return (freeing(&strarray, (NULL)));
		*(buff + i) = '\0';
		check = strlenornewline(buff);
		if (check < i)
		{
			strarray = allocdouble(strarray, buff, 1);
			if (strarray == (NULL))
				return (NULL);
			*strtemp = substr(buff, check + 1, 0, 0);
			if (*strtemp == (NULL))
				return (freeing(&strarray, (NULL)));
			return (strarray);
		}
		strarray = allocdouble(strarray, buff, 0);
		if (strarray == (NULL))
			return (NULL);
	}
	return (strarray);
}

char	**nextlinewithbuffer(char **strtemp, char **strarray)
{
	int	strtemplenornewline;

	strtemplenornewline = strlenornewline(*strtemp);
	if (*(*strtemp + strtemplenornewline) == '\n')
	{
		strarray = allocdouble(strarray, *strtemp, 1);
		if (strarray == (NULL))
			return (freeing(NULL, strtemp));
		*strtemp = substr(*strtemp, strtemplenornewline + 1, 0, 1);
		if (*strtemp == (NULL))
			return (freeing(&strarray, (NULL)));
		return (strarray);
	}
	strarray = allocdouble(strarray, *strtemp, 0);
	freeing(NULL, strtemp);
	return (strarray);
}

char	*get_next_line(int fd)
{
	char		**strarray;
	char		*returnstr;
	static char	*strtemp = (NULL);
	char		buff[BUFFER_SIZE + 1];

	if (fd < 0 || fd > FD_SETSIZE)
		return (NULL);
	strarray = (NULL);
	if (strtemp != (NULL))
	{
		strarray = nextlinewithbuffer(&strtemp, strarray);
		if (strtemp == (NULL) && strarray != (NULL))
			strarray = nextlinenobuffer(fd, strarray, &strtemp, buff);
	}
	else
		strarray = nextlinenobuffer(fd, strarray, &strtemp, buff);
	if (strarray == (NULL))
		return (NULL);
	returnstr = createreturnstring(strarray);
	if (returnstr == (NULL))
		return (freeing((NULL), &strtemp), (NULL));
	if ((strtemp != (NULL) && *strtemp == '\0'))
		freeing(NULL, &strtemp);
	if (returnstr != (NULL) && *returnstr == '\0')
		return (free(returnstr), (NULL));
	return (returnstr);
}
