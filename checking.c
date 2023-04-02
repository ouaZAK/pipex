
#include "pipex.h"

char	**which_split(char **av, t_vars va, int ac, int i)
{
	va.cmd = NULL;
	if ((i == 0) || (i != va.loop && i != 0))
	{
		if (va.split_with == 'h')
			va.cmd = split_it(av[i + 3], va);
		else
			va.cmd = split_it(av[i + 2], va);
	}
	else if (i == va.loop)
		va.cmd = split_it(av[ac - 2], va);
	return (va.cmd);
}

void	check_empty_cmd(char **av, t_vars *va)
{
	if (va->split_with == 'h')
	{
		if (!va->cmd[0])
			free_exit_msg(ft_strjoin(av[va->i + 3], \
				": command not found"), COM_N, va);
	}
	else
	{
		if (!va->cmd[0])
			free_exit_msg(ft_strjoin(av[va->i + 2], \
				": command not found"), COM_N, va);
	}
}
