/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:32:25 by salaoui           #+#    #+#             */
/*   Updated: 2024/12/01 16:44:52 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# ifndef INT_MAX
#  define INT_MAX 2147483647
# endif
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>

char		*get_next_line(int fd);
char		*ft_read_line(int fd, char *line_saved, char *buffer);
char		*save_line(char *s);
char		*save_next_line(char *str);
char		*ft_strchr_get(char *s, int c);
char		*ft_strjoin_get(char *s1, char *s2);
char		*ft_strdup_get(char *src);
size_t		ft_strlen_get(char *str);

#endif
