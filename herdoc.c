/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 09:45:39 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/05/03 15:42:43 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

void	heredoc_func(char **av, t_vars *va)
{
	char	*str;
	char	*line;
	int		tmp;

	line = NULL;
	tmp = open("tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	va->split_with = 'h';
	while (1)
	{
		write(2, "heredoc> ", 9);
		str = get_next_line(0);
		if (ft_strcmp(str, av[2], '\n'))
			line = ft_strjoin(line, str);
		if (!ft_strcmp(str, av[2], '\n'))
		{
			write (tmp, line, ft_strlen(line));
			free(str);
			free(line);
			break ;
		}
		free(str);
	}
	close(tmp);
}

void	open_file_or_herdoc(char **av, int ac, t_vars *va)
{
	if (ac >= 6 && !ft_strcmp(av[1], "here_doc", '0') && ft_strlen(av[1]) == 8)
	{
		va->loop = ac - 5;
		heredoc_func(av, va);
		va->fd = open("tmp", O_RDONLY);
		if (va->fd == -1)
			print_msg_error(ft_strjoin(ft_strdup("pipex: "), av[1]));
	}
	else
	{
		va->loop = ac - 4;
		va->fd = open(av[1], O_RDONLY);
		if (va->fd == -1)
			print_msg_error(ft_strjoin(ft_strdup("pipex: "), av[1]));
	}
}

void	print_msg_error(char *str)
{
	perror(str);
	free(str);
}
