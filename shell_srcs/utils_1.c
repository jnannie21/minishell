/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 13:08:31 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/26 14:05:03 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_from_env(char *to_find, char **env)
{
	int		i;
	size_t	len;

	len = ft_strlen(to_find);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], to_find, len) == 0)
			return (env[i]);
		i++;
	}
	return (0);
}

void		get_env(t_shell *shell, char **env)
{
	int		env_len;
	char	**new_env;
	int		i;

	env_len = get_array_len(env);
	new_env = (char **)(malloc(sizeof(char *) * (env_len + 1)));
	if (!new_env)
		exit_shell(shell, EXIT_FAILURE);
	new_env[env_len] = NULL;
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	shell->env = new_env;
	shell->env_len = env_len;
}

void		get_buildin_commands(t_shell *shell)
{
	shell->buildin_commands = (char **)malloc(sizeof(char *) * 8);
	if (!shell->buildin_commands)
		exit_shell(shell, EXIT_FAILURE);
	shell->buildin_commands[7] = NULL;
	shell->buildin_commands[0] = ft_strdup("echo");
	shell->buildin_commands[1] = ft_strdup("cd");
	shell->buildin_commands[2] = ft_strdup("pwd");
	shell->buildin_commands[3] = ft_strdup("export");
	shell->buildin_commands[4] = ft_strdup("unset");
	shell->buildin_commands[5] = ft_strdup("env");
	shell->buildin_commands[6] = ft_strdup("exit");
}

t_shell		*init_shell(char **env)
{
	t_shell		*shell;

	if (!(shell = ft_calloc(1, sizeof(t_shell))))
		exit_shell(shell, EXIT_FAILURE);
	get_env(shell, env);
	get_shell_path(shell, env);
	get_shell_cwd(shell);
	get_buildin_commands(shell);
	shell->fd_stdin = dup(0);
	shell->fd_stdout = dup(1);
	return (shell);
}

void		print_prompt(void)
{
	char	cwd[PATH_MAX];

	if (PATHINPROMPT && getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s $ ", cwd);
	else
		ft_printf(SHELL_PROMPT);
}
