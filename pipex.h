/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 10:45:37 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/02/11 11:10:40 by zouaraqa         ###   ########.fr       */
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

# define PERM_D 126
# define COM_N 127
# define NF_ND 127

typedef struct s_vars{
	char	**args;
	char	*s;
	int		i;
	int		y;
	int		x;
	int		count;
	char	split_with;
}t_vars;

//test ms7 dakchi
void	print(char *str);
void	ft_putnbr_fd(int n, int fd);

// utils
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
char	*ft_strjoin_2(char *s1, char *s2);
char	*ft_strjoin(char *s1, char *s2);
void	ft_putstr_fd(char *s, int fd);
void	*ft_calloc(size_t count, size_t size);
int		ft_strstr(char *haystack, char *needle);
char	*cpy(char *dst, char *src, int len);

// exit func
void	ft_free(char **str, int i);
void	free_exit_msg(char *str, int nb, char **s);
void	exit_msg(char *str, int nb);

//func
char	*get_path(char **env, char *cmd, char *av);
char	*join_path_to_cmd(char *path, char *cmd);
void	which_cmd(char **env, char *path, char **cmd);
void	check_print_errors(char *path, char *cmd, char c, char **cmds);
void	check_quote(char *str, char **env, t_vars *va);
char	**split_it(char *str, t_vars *va);
#endif