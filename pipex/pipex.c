/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truthe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 19:38:36 by truthe            #+#    #+#             */
/*   Updated: 2021/12/16 19:38:44 by truthe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"pipex.h"

char	*find_cmd(char *cmd, char **env)
{
	int		i;
	char	*jn;
	char	*str;
	char	**splt;

	i = 0;
	while (ft_strnstr(env[i], "PATH=", 5) == 0)
	i++;
	splt = ft_split(env[i] + 5, ':');
	i = 0;
	while (splt[i])
	{
		jn = ft_strjoin(splt[i], "/");
		str = ft_strjoin(jn, cmd);
		free(str);
		if (access(str, F_OK) == 0)
			return (str);
		i++;
	}
	return (0);
}

void	ft_execve(char *argv, char **env)
{
	char	*put;
	char	**cmd;

	cmd = ft_split(argv, ' ');
	put = find_cmd(cmd[0], env);
	if (execve(put, cmd, env) == -1)
	{
		perror ("error execve\n");
		exit(0);
	}
}

void	ft_child(char *argv[], char **env, int *fd)
{
	int	fdfile;

	if (access(argv[1], F_OK) == -1)
	{
		perror ("pipex: no such file or directory\n");
		exit(0);
	}
	else if (access(argv[1], R_OK) == -1)
	{
		perror ("pipex: permission denied\n");
		exit(0);
	}
	fdfile = open(argv[1], O_RDONLY);
	dup2(fdfile, 0);
	dup2(fd[1], 1);
	close(fd[0]);
	ft_execve(argv[2], env);
}

void	ft_parent(char *argv[], char **env, int *fd)
{
	int	out;

	out = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (out == -1)
	{
		perror("pipex: permission denied\n");
		exit(0);
	}
	dup2(fd[0], 0);
	dup2(out, 1);
	close(fd[1]);
	ft_execve(argv[3], env);
}

int	main(int argc, char *argv[], char **env)
{
	int		fd[2];
	pid_t	id;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
		{
			perror ("pipe error\n");
			exit(0);
		}
		id = fork();
		if (id == -1)
		{
			perror ("fork error\n");
			exit(0);
		}
		if (id == 0)
			ft_child(argv, env, fd);
		waitpid(id, 0, 0);
		ft_parent(argv, env, fd);
		close(fd[0]);
		close(fd[1]);
	}
	return (0);
}
