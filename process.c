/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:33:16 by tchaloei          #+#    #+#             */
/*   Updated: 2024/06/09 16:33:16 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_cmd(char **va, char ***cmd, int *i, char *av)
{
	if (av[0] == ' ' || av[ft_strlen(av) - 1] == ' ')
	{
		*va = ft_strtrim(av, " ");
		*cmd = ft_split(*va, ' ');
		*i = 2;
	}
	else
		*cmd = ft_split(av, ' ');
}

void	execute_cmd1(int read_fd, int write_fd[2], char **av, char **en)
{
	char	**cmd;
	char	*program;
	char	*va;
	int		i;

	if (access(av[1], R_OK) == -1 || read_fd == -1)
		close_fd(write_fd);
	if (ft_strlen(av[2]) == 0 || check_space_cmd(av[2]) == ft_strlen(av[2]))
		error_cmd(read_fd, write_fd, en);
	i = 0;
	va = av[2];
	get_cmd(&va, &cmd, &i, av[2]);
	process_pipe(read_fd, write_fd[1], write_fd[0]);
	program = program_and_cmd(av[2], va, i, en);
	if (!program)
	{
		check_builtin_cmd1(cmd, va, i);
		error_path(cmd, va, i, en);
	}
	else if (execve(program, cmd, en) == -1)
		free_program(program, cmd, va, i);
}

void	execute_cmd2(int read_fd[2], int write_fd, char **av, char **en)
{
	char	**cmd;
	char	*program;
	char	*va;
	int		i;

	if (access(av[4], W_OK) == -1 || write_fd == -1)
		close_fd(read_fd);
	if (ft_strlen(av[3]) == 0 || check_space_cmd(av[3]) == ft_strlen(av[3]))
		error_cmd(write_fd, read_fd, en);
	i = 0;
	va = av[3];
	get_cmd(&va, &cmd, &i, av[3]);
	process_pipe(read_fd[0], write_fd, read_fd[1]);
	program = program_and_cmd(av[3], va, i, en);
	if (!program)
	{
		check_builtin_cmd2(cmd, va);
		close_outfile(write_fd, read_fd);
		error_path(cmd, va, i, en);
	}
	else if (execve(program, cmd, en) == -1)
	{
		close_outfile(write_fd, read_fd);
		free_program(program, cmd, va, i);
	}
}

void	process_pipe(int fd1, int fd2, int fd_pipe)
{
	if (dup2(fd1, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd1);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd2, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd2);
		exit(EXIT_FAILURE);
	}
	close(fd_pipe);
	close(fd1);
	close(fd2);
}

char	*program_and_cmd(char *av, char *va, int i, char **en)
{
	char	*program;

	if (i == 0)
		program = program_name(av, en);
	else
		program = program_name(va, en);
	return (program);
}
