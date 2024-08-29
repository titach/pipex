/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:32:17 by tchaloei          #+#    #+#             */
/*   Updated: 2024/06/09 16:32:17 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_msg(char *cmd)
{
	char	*msg;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			j = 1;
		i++;
	}
	if (j != 0)
	{
		if (access(cmd, F_OK) == 0)
			msg = ft_strjoin("bash: Is a directory: ", cmd);
		else
			msg = ft_strjoin("bash: no such file or directory: ", cmd);
	}
	else
		msg = ft_strjoin("bash: command not found: ", cmd);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	free(msg);
}

void	error_cmd(int in_out_file, int fds[2], char **en)
{
	char	**path;

	path = get_path(en);
	if (!path)
		write(2, "bash: No such file or directory\n", 32);
	else
	{
		write(2, "bash: command not found:\n", 25);
		ft_free_split(path);
	}
	close(in_out_file);
	close(fds[0]);
	close(fds[1]);
	exit(127);
}

void	error_path_msg(char **cmd, char **msg, int *j, char **en)
{
	while (*en)
	{
		if (ft_strncmp(*en, "PATH=", 5) == 0 && ft_strlen(*en) > 5)
		{
			*msg = ft_strjoin("bash: command not found: ", cmd[0]);
			return ;
		}
		en++;
	}
	if (access(cmd[0], X_OK) != 0 && access(cmd[0], F_OK) == 0)
	{
		*msg = ft_strjoin("bash: Permission denied: ", cmd[0]);
		*j = 2;
	}
	else if (access(cmd[0], F_OK) != 0)
		*msg = ft_strjoin("bash: no such file or directory: ", cmd[0]);
	else
	{
		ft_free_split(cmd);
		exit(0);
	}
}

void	error_path(char **cmd, char *va, int i, char **en)
{
	char	*msg;
	int		j;

	j = 0;
	error_path_msg(cmd, &msg, &j, en);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	free(msg);
	ft_free_split(cmd);
	if (i == 2)
		free(va);
	if (j == 2)
		exit (126);
	exit(127);
}
