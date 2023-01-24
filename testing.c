/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 10:19:50 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/01/24 10:07:36 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int ac, char **av, char **env)
{
	// int i = execve("/bin/ls", av, env);
	// if (i == -1)
	// {
	// 	printf("errrrror");
	// 	return (1);
	// }
	
	
	/* ################ send tsb
	int	i;
	int fd[2];
	int	pid;
	int	tab[3] =  {2, 1, 3};
	int	y;
	int	x;
	char *str;

	i = -1;
	if (pipe(fd) == -1)
	{
		printf("eror in pipe");
		return (1);
	}
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		x = 3;
		if (write(fd[1], &x, sizeof(int)) == -1)
		{
			printf("error in write");
			return (1);
		}
		while (++i < x)
			ft_putnbr_fd(tab[i], fd[1]);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		int	t[3];
		
		i = -1;
		read(fd[0], &y, sizeof(int));
		while (++i < y)
			read(fd[0], &t[i], 3);
		i = -1;
		while (++i < 3)
			printf("tab[%d] = %d \n", i , tab[i]);
	}
	*/
	
	/* ################################ sum arr
	int	arr[] = {1,2,3,4,5,6,7};
	int	fd[2];
	int	id;
	int	start;
	int	end;
	int	sum;
	int	size;
	int	sumFromChild;

	size = sizeof(arr) / sizeof(int);
	if (pipe(fd) == -1)
	{
		printf("pipe error\n");
		return (1);
	}
	id = fork();
	if (id == 0)
	{
		start = 0;
		end = size / 2;
	}
	else
	{
		start = size / 2;
		end = size;
	}
	sum = 0;
	while(start < end)
		sum += arr[start++];
	if (id == 0)
	{
		close(fd[0]);
		if (write(fd[1], &sum, sizeof(sum)) == -1)
		{
			printf("error from write\n");
			return (1);
		}
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		if(read(fd[0], &sumFromChild, sizeof(int)) == -1)
		{
			printf("error from read\n");
			return (1);
		}
		sum += sumFromChild;
		printf("sum = %d", sum);
	}
*/

	/*
	// ########################################### sending string trough pipe
	char	*str = NULL;
	char 	c;
	int		id;
	int		fd[2];
	// fd[0] for reading
	// fd[1] for writing
	if (pipe(fd) == -1)
	{
		printf("error\n");
		return (1);
	}
	id = fork();
	if (id == 0)
	{
		close(fd[0]);
		c = 'Z';
		str = strdup("ZAK");
		ft_putstr_fd(str, fd[1]);
		// if (write(fd[1], &c, sizeof(char)) == -1)
		// {
		// 	printf("error\n");
		// 	return (1);
		// }
		close(fd[1]);
	}
	else
		{
			char *s = malloc(sizeof(4));
			close(fd[1]);
			// read(fd[0], &c, 1);
			// printf("sis = %c\n", c);
			if (read(fd[0], s, sizeof(s)) == -1)
			{
				printf("erroooooor\n");
				return (1);
			}
			close(fd[0]);
			printf("string receaved from child is = %s", s);
				wait(NULL);
		}
*/
}