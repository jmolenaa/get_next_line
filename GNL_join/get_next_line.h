/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 16:31:08 by jmolenaa      #+#    #+#                 */
/*   Updated: 2022/11/17 09:17:38 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
int		strlenornewline(char *str, int check);
char	*join(char *str, char *buff, int check);
char	*nextlinewithbuffer(char **strtemp, char **str);
char	*nextlinenobuffer(int fd, char *str, char **strtemp, char *buff);
char	*substr(char **strtemp, int strtemplenornewline);
char	*freeing(char **str, char **strtemp);
void	stringcpy(char *dest, char *src, int size);

#endif