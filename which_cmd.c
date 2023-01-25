/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:59:39 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/01/25 20:01:38 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
	{
		free(s1);
		s1 = NULL;
		return (0);
	}
	i = -1;
	j = 0;
	while (s1 && s1[++i])
		str[i] = s1[i];
	while (s2 && s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	s1 = NULL;
	return (str);
}

void	check_print_errors(char *path, char *cmd, char c)
{
	if (access(path, F_OK) && c == 'c')
		exit_msg(ft_strjoin("pipex: command not found: ", cmd), COM_N);
	else if (access(path, F_OK) && c == 'p')
		exit_msg(ft_strjoin("pipex: no such file or directory: ", cmd), NF_ND);
	else if (access(path, X_OK))
		exit_msg(ft_strjoin("pipex: permission denied: ", cmd), PERM_D);
}

void	which_cmd(char **env, char *path, char **cmd)
{
	if (cmd[0][0] == '/' || cmd[0][0] == '.')
	{
		check_print_errors(cmd[0], cmd[0], 'p');
		execve(cmd[0], cmd, env);
		exit_msg(ft_strjoin("pipex: permission denied: ", cmd[0]), PERM_D);
	}
	else
	{
		path = get_path(env, cmd[0]);
		path = join_path_to_cmd(path, cmd[0]);
		check_print_errors(path, cmd[0], 'c');
		execve(path, cmd, env);
	}
}
