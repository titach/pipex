/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:32:34 by tchaloei          #+#    #+#             */
/*   Updated: 2024/06/09 16:32:34 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*program_name(char *av, char **en)
{
	char	*program;
	char	*cmd;
	int		i;

	i = 0;
	cmd = sep_cmd_front(av);
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (cmd);
		i++;
	}
	program = path_en(en, cmd);
	free(cmd);
	return (program);
}

int	check_path(char **path)
{
	while (*path)
	{
		if (ft_strncmp(*path, "/usr/bin", 8) == 0)
			return (1);
		else if (ft_strncmp(*path, "/usr/bin/", 9) == 0)
			return (1);
		else if (ft_strncmp(*path, "/bin/", 5) == 0)
			return (1);
		else if (ft_strncmp(*path, "/bin", 4) == 0)
			return (1);
		path++;
	}
	return (0);
}

char	**get_path(char **en)
{
	char	**path;
	int		i;

	if (!en || !*en || !**en)
		return (NULL);
	path = NULL;
	while (*en)
	{
		if (ft_strncmp(*en, "PATH=", 5) == 0 && ft_strlen(*en) > 5)
		{
			path = ft_split(*en + 5, ':');
			i = check_path(path);
			if (i == 0)
			{
				ft_free_split(path);
				return (NULL);
			}
			return (path);
		}
		en++;
	}
	return (path);
}

char	*path_en(char **en, char *cmd)
{
	int		i;
	char	**paths;
	char	*program;
	char	*path;

	paths = get_path(en);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		program = ft_strjoin(path, cmd);
		free(path);
		if (access(program, X_OK) == 0)
		{
			ft_free_split(paths);
			return (program);
		}
		free(program);
		i++;
	}
	ft_free_split(paths);
	program = ft_strjoin("/bin/", cmd);
	return (program);
}
