/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgibier <tgibier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:59:35 by tgibier           #+#    #+#             */
/*   Updated: 2023/07/07 14:12:01 by tgibier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_free(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

int	clean_exit(char *str, t_data *hoid)
{
	if (str)
		ft_putstr(str);
	if (hoid->path)
		ft_free(hoid->path);
	if (hoid->path1)
		free(hoid->path1);
	if (hoid->path2)
		free(hoid->path2);
	if (hoid->file1)
		free(hoid->file1);
	if (hoid->file2)
		free(hoid->file2);
	if (hoid->cmd1)
		ft_free(hoid->cmd1);
	if (hoid->cmd2)
		ft_free(hoid->cmd2);
	if (hoid->in_fd > 2 || hoid->in_fd < 0)
		close(hoid->in_fd);
	if (hoid->out_fd > 2 || hoid->out_fd < 0)
		close(hoid->out_fd);
	exit (0);
}

void	clean_init(t_data *hoid)
{
	hoid->file1 = NULL;
	hoid->file2 = NULL;
	hoid->path = NULL;
	hoid->path1 = NULL;
	hoid->path2 = NULL;
	hoid->cmd1 = NULL;
	hoid->cmd2 = NULL;
	hoid->in_fd = 0;
	hoid->out_fd = 1;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	hoid;

	clean_init(&hoid);
	handle_args(&hoid, argc, argv, envp);
	pipex(&hoid);
	clean_exit(NULL, &hoid);
	return (0);
}
