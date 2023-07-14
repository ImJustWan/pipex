/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgibier <tgibier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:51:53 by tgibier           #+#    #+#             */
/*   Updated: 2023/07/05 16:59:46 by tgibier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_envp(char **envp)
{
	int		i;
	int		j;
	int		len;
	// char	*str;

	printf("check envp\n");
	j = 0;
	i = 0;
	len = 0;
	while (envp[j++] && envp[j][i + 6])
	{
		if (envp[j][i] == 'P' && envp[j][i + 1] == 'A' && envp[j][i + 2] == 'T'
			&& envp[j][i + 3] == 'H' /*&& envp[j][i + 5] == 'm'*/)
		{
			// while (envp[j][i] && envp[j][i] != '\n')
			// {
			// 	// printf("str is %c\n", envp[j][i]);
			// 	len++;
			// 	i++;
			// }
			printf("len is %d\n", len);
			return (0);
			// str = malloc (sizeof(char) * (ft_strlen(envp[j]) - 3));
			// if (!str)
			// 	return (0);
			// i = 0;
			// while (envp[j][i + 4])
			// {
			// 	str[i] = envp[j][i + 4];
			// 	i++;
			// }
			// str[i] = '\0';
			// printf("str is %s\n", str);
		}
		i++;
		// return (1);

	}
	return (0);
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
		return (clean_exit(NULL, hoid));
	if (!creating_hoid(hoid, argc, argv))
		return (clean_exit(NULL, hoid));
	if (!check_envp(envp))
	{
		ft_printf("pipex: %s: No such file or directory\n", hoid->cmd2[0]);
		ft_printf("pipex: %s: No such file or directory\n", hoid->cmd1[0]);
		return (clean_exit(NULL, hoid));
	}
	return (1);
}
