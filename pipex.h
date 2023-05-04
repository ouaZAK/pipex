/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 09:55:51 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/05/03 15:40:48 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>
# include "get_next_line_bonus.h"

# define PERM_D 126
# define COM_N 127
# define NF_ND 127

typedef struct s_vars{
	pid_t	wpid;
	char	**cmd;
	char	*str;
	char	*s;
	char	*path;
	int		*pid;
	int		fd;
	int		p1[2];
	int		p2[2];
	int		i;
	int		y;
	int		x;
	int		exit;
	int		loop;
	int		count;
	int		status;
	char	split_with;
}t_vars;

//func
int		check_sub_dir(char *str);
char	*get_path(char **env);
char	*join_path_to_cmd(char *path, char *cmd);
char	**which_split(char **av, t_vars va, int ac, int i);
char	**split_it(char *str, t_vars va);
char	*add_point(char *str);
void	set_first_pipes(t_vars *va);
void	set_pipes(t_vars *va, int i);
void	set_pipes_parent(t_vars *va, int i);
void	check_errors(char *path, char **cmd, t_vars *va);
void	open_pipes(t_vars *va, int i);
void	last_child(char **av, char **env, t_vars va, int ac);
void	middle_childs(char **env, t_vars va);
void	first_child(char **env, t_vars va);
void	close_fds(t_vars *va);
void	heredoc_func(char **av, t_vars *va);
void	open_file_or_herdoc(char **av, int ac, t_vars *va);
void	check_empty_cmd(char **av, t_vars *va);

// utils
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
char	*ft_strjoin_2(char *s1, char *s2);
char	*ft_strjoin(char *s1, char *s2);
char	*cpy(char *dst, char *src, int len);
char	*ft_strdup(char *str);
void	print_msg_error(char *str);
void	ft_putstr_fd(char *s, int fd);
void	*ft_calloc(size_t count, size_t size);
int		ft_strstr(char *haystack, char *needle);
int		ft_strcmp(char *s1, char *s2, char c);

// exit func
void	ft_free(char **str, int i);
void	exit_msg(char *str, int nb, char **cmd);
void	free_exit_msg(char *str, int nb, t_vars *va);

#endif
