/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:33:08 by tchaloei          #+#    #+#             */
/*   Updated: 2024/06/09 16:33:08 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

//--------err_msg--------//
void	error_msg(char *cmd);
void	error_cmd(int in_out_file, int fds[2], char **en);
void	error_path_msg(char **cmd, char **msg, int *j, char **en);
void	error_path(char **cmd, char *va, int i, char **en);
//--------split--------//
char	**ft_split(const char *s, char c);
//--------extend--------//
int		open_infile(const char *av);
int		open_outfile(const char *av);
char	*sep_cmd_front(char *av);
size_t	check_space_cmd(char *av);
void	close_fd(int fds[2]);
//--------process--------//
void	get_cmd(char **va, char ***cmd, int *i, char *av);
void	execute_cmd1(int read_fd, int write_fd[2], char **av, char **en);
void	execute_cmd2(int read_fd[2], int write_fd, char **av, char **en);
void	process_pipe(int fd1, int fd2, int fd_pipe);
char	*program_and_cmd(char *av, char *va, int i, char **en);
//--------main--------//
void	create_child1(int pipefd[2], char **en, char **av, pid_t *pid1);
void	create_child2(int pipefd[2], char **av, char **en, pid_t *pid2);
//--------find_env--------//
char	*program_name(char *av, char **en);
int		check_path(char **path);
char	*path_en(char **en, char *cmd);
char	**get_path(char **en);
//--------free--------//
void	ft_free_split(char **split);
void	free_program(char *program, char **cmd, char *va, int i);
void	close_outfile(int outfile, int fds[2]);
void	check_builtin_cmd1(char **cmd, char *va, int i);
void	check_builtin_cmd2(char **cmd, char *va);
//--------utils--------//
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *str, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(const char *s, unsigned int start, size_t len);
//--------utils2--------//
char	*ft_strdup(const char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strtrim(char const *s1, char const *set);

#endif