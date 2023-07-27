/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgibier <tgibier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:48:32 by tgibier           #+#    #+#             */
/*   Updated: 2023/07/07 15:03:08 by tgibier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*creating_paths(char *s1, char *s2)
{
	int		i;
	int		j;
	int		size1;
	int		size2;
	char	*final;

	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	final = malloc ((size1 + size2 + 2) * sizeof(char));
	if (!final)
		return (NULL);
	i = 0;
	j = 0;
	while (i < size1)
		final[i++] = s1[j++];
	final[i++] = '/';
	j = 0;
	while (i < size1 + size2 + 1)
		final[i++] = s2[j++];
	final[i] = '\0';
	return (final);
}

void	doing_smthg_hopefully(char **cmd, char *ze_path, t_data *hoid)
{
	int	i;

	if (execve(cmd[0], cmd, NULL) == -1)
	{
		i = -1;
		while (hoid->path[++i])
		{
			ze_path = creating_paths(hoid->path[i], cmd[0]);
			if (execve(ze_path, cmd, NULL) == -1)
			{
				free(ze_path);
				ze_path = NULL;
			}
		}
		perror(ze_path);
		clean_exit(NULL, hoid);
	}
}

void	second_child(t_data *hoid, int *fd)
{
	hoid->out_fd = open(hoid->file2, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (hoid->out_fd == -1)
	{
		perror(hoid->file2);
		close (fd[0]);
		close (fd[1]);
		clean_exit(NULL, hoid);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(hoid->out_fd, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (hoid->out_fd > 2)
		close(hoid->out_fd);
	doing_smthg_hopefully(hoid->cmd2, hoid->path2, hoid);
	exit (1);
}

void	first_child(t_data *hoid, int *fd)
{
	if (access(hoid->file1, R_OK) == -1 || access(hoid->file1, W_OK) == -1)
	{
		perror(hoid->file1);
		close (fd[0]);
		close (fd[1]);
		clean_exit(NULL, hoid);
	}
	hoid->in_fd = open(hoid->file1, O_RDONLY);
	dup2(hoid->in_fd, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(hoid->in_fd);
	close(fd[0]);
	close(fd[1]);
	doing_smthg_hopefully(hoid->cmd1, hoid->path1, hoid);
	exit (1);
}

void	pipex(t_data *hoid)
{
	int		fd[2];
	int		status;
	int		first_pid;
	int		second_pid;

	if (pipe(fd) == -1)
		clean_exit(NULL, hoid);
	first_pid = fork();
	if (first_pid == 0)
		first_child(hoid, fd);
	second_pid = fork();
	if (second_pid == 0)
		second_child(hoid, fd);
	close (fd[0]);
	close (fd[1]);
	waitpid(first_pid, &status, 0);
	waitpid(second_pid, &status, 0);
}
