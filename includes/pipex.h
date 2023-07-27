/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgibier <tgibier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:59:04 by tgibier           #+#    #+#             */
/*   Updated: 2023/07/07 12:00:18 by tgibier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include <string.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/includes/libft.h"

typedef struct s_data
{
	char	*file1;
	char	*file2;
	char	*path1;
	char	*path2;
	char	**path;
	char	**cmd1;
	char	**cmd2;
	char	**envp;
	int		in_fd;
	int		out_fd;
}	t_data;

int		clean_exit(char *str, t_data *hoid);
int		handle_args(t_data *hoid, int argc, char **argv, char **envp);

void	pipex(t_data *hoid);

#endif