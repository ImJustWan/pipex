/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgibier <tgibier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:48:32 by tgibier           #+#    #+#             */
/*   Updated: 2023/07/05 16:15:23 by tgibier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	if (execve(hoid->cmd2[0], hoid->cmd2, NULL) == -1)
	{
		hoid->path2 = ft_strjoin("/bin/", hoid->cmd2[0]);
		if (execve(hoid->path2, hoid->cmd2, NULL) == -1)
		{
			perror(hoid->cmd2[0]);
			clean_exit(NULL, hoid);
		}
	}
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
	if (execve(hoid->cmd1[0], hoid->cmd1, NULL) == -1)
	{
		hoid->path1 = ft_strjoin("/bin/", hoid->cmd1[0]);
		if (execve(hoid->path1, hoid->cmd1, NULL) == -1)
		{
			perror(hoid->cmd1[0]);
			clean_exit(NULL, hoid);
		}
	}
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
