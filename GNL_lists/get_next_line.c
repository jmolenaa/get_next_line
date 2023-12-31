/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 16:36:41 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/20 08:34:06 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

char	*createreturnstring(t_list *strlist)
{
	char	*retstr;
	int		totallen;
	int		i;
	t_list	*temp;

	totallen = 0;
	temp = strlist;
	while (temp != (NULL))
	{
		totallen = totallen + strlenornewline(temp->str, 0);
		temp = temp->next;
	}
	retstr = (char *)malloc((totallen + 1) * sizeof(char));
	if (retstr == (NULL))
		return (freeing(strlist, (NULL)), (NULL));
	*(retstr + totallen) = '\0';
	temp = strlist;
	while (temp != (NULL))
	{
		i = strlenornewline(temp->str, 0);
		totallen = totallen - stringcpy(retstr + totallen - i, temp->str, i);
		temp = temp->next;
	}
	freeing(strlist, (NULL));
	return (retstr);
}

t_list	*addnode(t_list *head, char *buff)
{
	t_list	*newnode;

	newnode = (t_list *)malloc(sizeof(t_list));
	if (newnode == (NULL))
	{
		freeing(head, NULL);
		return (NULL);
	}
	newnode->str = substr(buff, 0, 1, 0);
	if (newnode->str == (NULL))
	{
		freeing(head, NULL);
		free(newnode);
		return (NULL);
	}
	newnode->next = head;
	return (newnode);
}

t_list	*nextlinenobuffer(int fd, t_list *strlist, char **strtemp)
{
	int		i;
	int		check;
	char	buff[BUFFER_SIZE + 1];

	i = 1;
	while (i)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i == -1)
			return (freeing(strlist, (NULL)));
		*(buff + i) = '\0';
		strlist = addnode(strlist, buff);
		if (strlist == (NULL))
			return (NULL);
		check = strlenornewline(buff, 1);
		if (check < i)
		{
			*strtemp = substr(buff, check + 1, 0, 0);
			if (*strtemp == (NULL))
				return (freeing(strlist, (NULL)));
			return (strlist);
		}
	}
	return (strlist);
}

t_list	*nextlinewithbuffer(char **strtemp, t_list *strlist)
{
	int	strtemplenornewline;

	strtemplenornewline = strlenornewline(*strtemp, 1);
	if (*(*strtemp + strtemplenornewline) == '\n')
	{
		strlist = addnode(strlist, *strtemp);
		if (strlist == (NULL))
			return (freeing(NULL, strtemp));
		*strtemp = substr(*strtemp, strtemplenornewline + 1, 0, 1);
		if (*strtemp == (NULL))
			return (freeing(strlist, (NULL)));
		return (strlist);
	}
	strlist = addnode(strlist, *strtemp);
	freeing(NULL, strtemp);
	return (strlist);
}

char	*get_next_line(int fd)
{
	t_list		*strlist;
	char		*retstr;
	static char	*strtemp = (NULL);

	if (fd < 0 || fd > FD_SETSIZE)
		return (NULL);
	strlist = (NULL);
	if (strtemp != (NULL))
	{
		strlist = nextlinewithbuffer(&strtemp, strlist);
		if (strtemp == (NULL) && strlist != (NULL))
			strlist = nextlinenobuffer(fd, strlist, &strtemp);
	}
	else
		strlist = nextlinenobuffer(fd, strlist, &strtemp);
	if (strlist == (NULL))
		return (NULL);
	retstr = createreturnstring(strlist);
	if (retstr == (NULL))
		return (freeing((NULL), &strtemp), (NULL));
	if ((strtemp != (NULL) && *strtemp == '\0'))
		freeing(NULL, &strtemp);
	if (retstr != (NULL) && *retstr == '\0')
		return (free(retstr), (NULL));
	return (retstr);
}
