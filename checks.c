/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:12:29 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/01/24 10:07:54 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*check_errors(int ac, char **av, char **env, char *path)
{
	if (ac > 5)
		exit_msg("wrong args\n");
	if (access(av[1], R_OK) == -1)
		exit_msg("file has no permission to read\n");
	path = get_path(env);
	return (path);
}

int	check_bash(char *str)
{
	char	**cpy;
	char	*tmp;
	int		i;
	int		y;

	i = 0;
	y = 0;
	cpy = NULL;
	tmp = "bash";
	if (str[i] == '/')
	{
		cpy = ft_split(str, '/');
		while (cpy[i] && cpy[i + 1])
			i++;
		while (cpy[i][y] && tmp[y] && cpy[i][y] == tmp[y])
		y++;
		ft_free(cpy, 0);
		if (!tmp[y])
			return (1);
	}
	while (str[i] && tmp[i] && str[i] == tmp[i])
		i++;
	if (!tmp[i])
		return (1);
	return (0);
}
