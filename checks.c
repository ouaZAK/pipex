/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:12:29 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/01/23 11:19:47 by zouaraqa         ###   ########.fr       */
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
	char *tmp;
	int	i;

	i = 0;
	tmp = "bash";
	while (str[i] && tmp[i] && str[i] == tmp[i])
		i++;
	if (!str[i] && !tmp[i])
		return (1);
	return (0);
}
