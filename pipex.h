/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 10:45:37 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/01/23 11:52:07 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>

//test ms7 dakchi
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	**ft_split(char const *s, char c);
char	*ft_strjoin_2(char *s1, char *s2);
void	ft_free(char **str, int i);
void	exit_msg(char *str);
void	free_exit(char *str);

//func
char	*get_path(char **env);
char	*join_path_to_cmd(char *path, char *cmd);
char	*check_errors(int ac, char **av, char **env, char *path);
void	which_cmd(char *av, char **env, char *path, char **cmd);
int		check_bash(char *str);

#endif