/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:32:59 by tchaloei          #+#    #+#             */
/*   Updated: 2024/06/09 16:32:59 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_child1(int pipefd[2], char **en, char **av, pid_t *pid1)
{
	int	fd;

	fd = open_infile(av[1]);
	*pid1 = fork();
	if (*pid1 == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		if (fd != -1)
			close(fd);
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (*pid1 == 0)
	{
		execute_cmd1(fd, pipefd, av, en);
		exit(errno);
	}
	if (fd != -1)
		close(fd);
}

void	create_child2(int pipefd[2], char **av, char **en, pid_t *pid2)
{
	int	fd;

	fd = open_outfile(av[4]);
	*pid2 = fork();
	if (*pid2 == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		if (fd != -1)
			close(fd);
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (*pid2 == 0)
	{
		execute_cmd2(pipefd, fd, av, en);
		exit(errno);
	}
	if (fd != -1)
		close(fd);
}

int	main(int ac, char **av, char **en)
{
	int		pipefd[2];
	int		status;
	pid_t	pid1;
	pid_t	pid2;

	if (ac != 5)
		return (write(2, "Need 4 arguments.\n", 19), EINVAL);
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	create_child1(pipefd, en, av, &pid1);
	create_child2(pipefd, av, en, &pid2);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		return (WEXITSTATUS(status));
	return (0);
}
