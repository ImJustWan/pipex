/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgibier <tgibier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:51:53 by tgibier           #+#    #+#             */
/*   Updated: 2023/07/07 15:15:09 by tgibier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	extract_path(char *str, t_data *hoid)
{
	char	*temp;
	int		i;

	(void)hoid;
	temp = malloc(sizeof(char) * ft_strlen(str) - 4);
	if (!temp)
		return (0);
	i = -1;
	while (str[++i + 5])
		temp[i] = str[i + 5];
	temp[i] = '\0';
	hoid->path = ft_split(temp, ':');
	if (!hoid->path)
		return (0);
	free(temp);
	return (1);
}

void	check_envp(char **envp, t_data *hoid)
{
	int	i;
	int	j;

	j = -1;
	while (envp[++j])
	{
		i = -1;
		while (envp[j][i + 6])
		{
			if (envp[j][i] == 'P' && envp[j][i + 1] == 'A'
				&& envp[j][i + 2] == 'T' && envp[j][i + 3] == 'H'
				&& envp[j][i + 6] == 'm')
				extract_path(envp[j], hoid);
			i++;
		}
	}
}

int	creating_hoid(t_data *hoid, int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		if (i == 1)
			hoid->file1 = ft_strdup(argv[i]);
		if (i == 2)
			hoid->cmd1 = ft_split(argv[i], ' ');
		if (i == 3)
			hoid->cmd2 = ft_split(argv[i], ' ');
		if (i == 4)
			hoid->file2 = ft_strdup(argv[i]);
		i++;
	}
	if (!hoid->file1 || !hoid->cmd1 || !hoid->cmd2)
		clean_exit(NULL, hoid);
	return (1);
}

int	handle_args(t_data *hoid, int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		ft_putstr_fd("\n\t\033[36;1m🦖 Invalid Arguments 🦖\033[0m\n\n", 1);
		ft_putstr_fd("   I only take 4 arguments, try again !\n", 1);
		return (clean_exit(NULL, hoid));
	}
	if (!creating_hoid(hoid, argc, argv))
		return (clean_exit(NULL, hoid));
	check_envp(envp, hoid);
	return (1);
}
