/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:29:04 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/02/21 11:01:59 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_first_pipes(t_vars *va)
{
	if (pipe(va->p1) == -1)
		exit_msg("pipe error\n", 2, NULL);
	if (pipe(va->p2) == -1)
		exit_msg("pipe error\n", 2, NULL);
}

void	set_pipes(t_vars *va, int i)
{
	if (i % 2 != 0)
	{
		close(va->p1[1]);
		close(va->p2[0]);
		dup2(va->p1[0], 0);
		dup2(va->p2[1], 1);
	}
	else if (i % 2 == 0)
	{
		close(va->p2[1]);
		close(va->p1[0]);
		dup2(va->p2[0], 0);
		dup2(va->p1[1], 1);
	}
}

void	set_pipes_parent(t_vars *va, int i)
{
	if (i % 2 != 0)
	{
		close (va->p2[0]);
		close (va->p2[1]);
		close (va->p1[1]);
		dup2 (va->p1[0], 0);
	}
	else if (i % 2 == 0)
	{
		close (va->p1[0]);
		close (va->p1[1]);
		close (va->p2[1]);
		dup2 (va->p2[0], 0);
	}
}

void	open_pipes(t_vars *va, int i)
{
	if (i % 2 != 0)
	{
		close(va->p1[0]);
		close(va->p1[1]);
		pipe(va->p1);
	}
	else if (i % 2 == 0)
	{
		close(va->p2[0]);
		close(va->p2[1]);
		pipe(va->p2);
	}
}
