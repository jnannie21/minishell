/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 21:49:46 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/26 00:31:09 by jnannie          ###   ########.fr       */
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

void			check_correct_command(t_shell *shell, t_command *command,
									char *data)
{
	int				i;
	struct stat		status_struct;
	char			*total_path;

	if (prepath_check(shell, command, data))
		return ;
	i = 0;
	while (shell->path[i])
	{
		if (!(total_path = ft_strjoin(shell->path[i++], data)))
			exit_shell(shell, EXIT_FAILURE);
		if (stat(total_path, &status_struct) == 0 &&
			(status_struct.st_mode & S_IFMT) == S_IFREG)
			command_is_found(shell, command, total_path);
		free(total_path);
	}
	if (command->is_found == 0)
	{
		g_last_exit_status = 127;
		print_error(data, "command not found", 1);
	}
}
