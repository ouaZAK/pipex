/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_it.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 09:58:27 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/05/01 09:58:30 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	initializing(t_vars *va)
{
	va->cmd = NULL;
	va->s = NULL;
	va->i = 0;
	va->x = 0;
	va->y = 0;
	va->count = 0;
}

static int	word_count(char *str, int i, int count, char split_with)
{
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			split_with = str[i];
			i++;
			if (str[i])
				count++;
			while (str[i] && str[i] != split_with)
				i++;
			i++;
		}
		else
		{
			if (str[i])
				count++;
			while (str[i] && str[i] != ' ')
				i++;
		}
		while (str[i] && str[i] == ' ')
			i++;
	}
	return (count);
}

static char	*quote_split(char *str, char c)
{
	char	*s;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (str[i] && str[i] != c)
	{
		i++;
		count++;
	}
	s = ft_calloc(sizeof(char), count + 1);
	s = cpy(s, str, count);
	return (s);
}

static void	skip_word(t_vars *va, char *str, char which)
{
	if (which == 'q')
	{
		va->i++;
		while (str[va->i] && str[va->i] != va->split_with)
			va->i++;
		va->i++;
	}
	else if (which == ' ')
	{
		while (str[va->x] && str[va->x] != ' ')
		{
			va->x++;
			va->count++;
		}
	}
}

char	**split_it(char *str, t_vars va)
{
	initializing(&va);
	va.cmd = ft_calloc(sizeof(char *), (word_count(str, va.i, \
					va.x, va.split_with) + 1));
	while (str[va.i])
	{
		va.count = 0;
		va.x = va.i;
		if (str[va.i] == '\'' || str[va.i] == '"')
		{
			va.split_with = str[va.i];
			va.cmd[va.y++] = quote_split(&str[va.i + 1], va.split_with);
			skip_word(&va, str, 'q');
		}
		else if (str[va.i] != ' ')
		{
			skip_word(&va, str, ' ');
			va.cmd[va.y] = ft_calloc(sizeof(char), va.count + 1);
			va.cmd[va.y] = cpy(va.cmd[va.y], &str[va.i], va.count);
			va.y++;
			va.i = va.x;
		}
		while (str[va.i] && str[va.i] == ' ')
			va.i++;
	}
	return (va.cmd);
}
