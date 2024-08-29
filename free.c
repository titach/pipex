/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:32:41 by tchaloei          #+#    #+#             */
/*   Updated: 2024/06/09 16:32:41 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_program(char *program, char **cmd, char *va, int i)
{
	int	j;

	j = 0;
	if (access(cmd[0], X_OK) == 0 && cmd[0][0] == '/')
		j = 2;
	error_msg(cmd[0]);
	ft_free_split(cmd);
	free(program);
	if (i == 2)
		free(va);
	if (j == 2)
		exit (126);
	exit(127);
}

void	close_outfile(int outfile, int fds[2])
{
	close(outfile);
	close(fds[0]);
	close(fds[1]);
}

void	check_builtin_cmd1(char **cmd, char *va, int i)
{
	char		*cmds[4];
	int			j;

	cmds[0] = "pwd";
	cmds[1] = "echo";
	cmds[2] = "printf";
	cmds[3] = NULL;
	j = 0;
	while (cmds[j])
	{
		if (ft_strncmp(cmds[j], cmd[0], sizeof(cmd[0])) == 0)
			break ;
		j++;
	}
	if (cmds[j] == NULL || j == 3)
		return ;
	ft_free_split(cmd);
	if (i == 2)
		free(va);
	exit(errno);
}

void	check_builtin_cmd2(char **cmd, char *va)
{
	char		*cmds[5];
	int			j;

	cmds[0] = "pwd";
	cmds[1] = "echo";
	cmds[2] = "printf";
	cmds[3] = NULL;
	j = 0;
	while (cmds[j])
	{
		if (ft_strncmp(cmds[j], cmd[0], sizeof(cmd[0])) == 0)
			break ;
		j++;
	}
	if (cmds[j] == NULL || j == 3)
		return ;
	cmds[0] = "/bin/sh";
	cmds[1] = "-c";
	cmds[2] = va;
	execve("/bin/sh", cmds, NULL);
}
