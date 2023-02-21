/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:54:45 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/02/21 11:23:37 by zouaraqa         ###   ########.fr       */
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
# include "get_next_line.h"

# define PERM_D 126
# define COM_N 127
# define NF_ND 127

typedef struct s_vars{
	char	**cmd;
	char	*str;
	char	*s;
	int		fd;
	int		p1[2];
	int		p2[2];
	int		pid;
	int		i;
	int		j;
	int		y;
	int		x;
	int		count;
	char	split_with;
}t_vars;

//test ms7 dakchi
void	ft_putnbr_fd(int n, int fd);

void	set_first_pipes(t_vars *va);
void	set_pipes(t_vars *va, int i);
void	set_pipes_parent(t_vars *va, int i);
void	open_pipes(t_vars *va, int i);
void	the_parent(char **av, char **env, t_vars va, int ac);
void	middle_childs(char **av, char **env, t_vars va, int i);
void	first_child(char **av, char **env, t_vars va);

// utils
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
char	*ft_strjoin_2(char *s1, char *s2);
char	*ft_strjoin(char *s1, char *s2);
void	ft_putstr_fd(char *s, int fd);
void	*ft_calloc(size_t count, size_t size);
int		ft_strstr(char *haystack, char *needle);
char	*cpy(char *dst, char *src, int len);
int		ft_strcmp(char *s1, char *s2, char c);

// exit func
void	ft_free(char **str, int i);
void	free_exit_msg(char *str, int nb, char **s);
void	exit_msg(char *str, int nb, char **cmd);

//func
char	*get_path(char **env);
char	*join_path_to_cmd(char *path, char *cmd);
void	which_cmd(char **env, char *path, char **cmd);
char	**split_it(char *str, t_vars va);
#endif