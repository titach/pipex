/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:32:25 by tchaloei          #+#    #+#             */
/*   Updated: 2024/06/09 16:32:25 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_infile(const char *av)
{
	int		fd;
	char	*msg;
	char	*msg2;

	fd = open(av, O_RDONLY);
	if (fd == -1)
	{
		msg = ft_strjoin("bash", ": ");
		msg2 = ft_strjoin(msg, (char *)av);
		free(msg);
		perror(msg2);
		free(msg2);
		return (fd);
	}
	return (fd);
}

int	open_outfile(const char *av)
{
	int		fd;
	char	*msg;
	char	*msg2;

	fd = open(av, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		msg = ft_strjoin("bash", ": ");
		msg2 = ft_strjoin(msg, (char *)av);
		free(msg);
		perror(msg2);
		free(msg2);
		return (fd);
	}
	return (fd);
}

char	*sep_cmd_front(char *av)
{
	char	*cmd;
	int		i;
	int		j;

	i = 0;
	while (av[i] && av[i] != ' ')
		i++;
	cmd = (char *)malloc(sizeof(char) * i + 1);
	if (!cmd)
		return (NULL);
	j = 0;
	while (j < i)
	{
		cmd[j] = av[j];
		j++;
	}
	cmd[j] = '\0';
	return (cmd);
}

size_t	check_space_cmd(char *av)
{
	int	i;

	i = 0;
	while (av[i] && av[i] == ' ')
		i++;
	return (i);
}

void	close_fd(int fds[2])
{
	close(fds[0]);
	close(fds[1]);
	exit(EXIT_FAILURE);
}
