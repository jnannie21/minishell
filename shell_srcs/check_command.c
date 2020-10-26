/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 21:49:46 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/26 16:23:44 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				is_buildin_command(t_shell *shell, char *command)
{
	int	i;

	i = 0;
	while (shell->buildin_commands[i])
	{
		if (ft_strcmp(command, shell->buildin_commands[i]))
			return (1);
		i++;
	}
	return (0);
}

static void		command_is_found(t_shell *shell, t_command *command,
								char *total_path)
{
	if (!(command->correct_path = ft_strdup(total_path)))
	{
		free(total_path);
		exit_shell(shell, EXIT_FAILURE);
	}
	command->is_found = 1;
}

void			search_correct_command(t_shell *shell, t_command *command,
										char *data)
{
	int				i;
	struct stat		status_struct;
	char			*total_path;
	char			*not_exec;

	i = 0;
	not_exec = NULL;
	while (shell->path[i])
	{
		if (!(total_path = ft_strjoin(shell->path[i++], data)))
			exit_shell(shell, EXIT_FAILURE);
		if (stat(total_path, &status_struct) == 0 &&
			(status_struct.st_mode & S_IFMT) == S_IFREG)
		{
			if (status_struct.st_mode & S_IXUSR)
				return (command_is_found(shell, command, total_path));
			if (!not_exec)
				not_exec = ft_strdup(total_path);
		}
		free(total_path);
	}
	if (not_exec)
		command_is_found(shell, command, not_exec);
}

void			check_correct_command(t_shell *shell, t_command *command,
									char *data)
{
	if (prepath_check(shell, command, data))
		return ;
	search_correct_command(shell, command, data);
	if (command->is_found == 0)
	{
		g_last_exit_status = 127;
		print_error(data, "command not found", 1);
	}
}
