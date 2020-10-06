/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:07:15 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/06 14:51:08 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/syslimits.h>
#include "minishell.h"

// extern char **environ;

// static void			cb_print_env(char **envp)
// {
// 	while (*envp)
// 	{
// 		write(1, *envp, ft_strlen(*envp));
// 		write(1, "\n", 1);
// 		envp++;
// 	}
// }

static void			print_prompt(void)
{
	char	cwd[PATH_MAX];

	errno = 0;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_printf("%s $ ", cwd);
	}
	else
	{
		perror("getcwd() error");
		ft_printf(" $ ");
	}
}

// static int			run_command(const char *filename, char *const argv[],
// 							char *const envp[])
// {
// 	pid_t pid;
// 	int status;

// 	pid = fork();

// 	if (pid == -1)
// 	{
// 		return (-1);
// 	}
// 	else if (pid > 0)
// 	{
// 		waitpid(pid, &status, 0);
// 	}
// 	else
// 	{
// 		execve(filename, argv, envp);
// 		exit(EXIT_FAILURE);
// 	}
// 	return (0);
// }

static t_command	*parse_line(char *line)
{
	line = 0;
	return ((t_command *)line);
}

static int			execute_commands(t_command *commands)
{
	commands = 0;
	return ((int)commands);
}

void				quit_handler(int signum)
{
	write(1, "\b\b  \b\b", 6);
	(void)signum;
}

void				int_handler(int signum)
{
	write(1, "\b\b  \b\b", 6);
	ft_printf("\n");
	print_prompt();
	(void)signum;
}

void				set_signals_handlers(void)
{
	signal(SIGQUIT, quit_handler);
	signal(SIGINT, int_handler);
}

// static void			tty_setup(char *envp[])
// {
// 	//stty -echoctl
// 	pid_t		pid;
// 	int			status;
// 	char		*argv;

// 	argv = "-echoctl";
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		execve("/bin/stty", &argv, envp);
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (pid > 0)
// 	{
// 		wait(&status);
// 	}
// 	else
// 	{
// 		perror("fork failed");
// 		exit(EXIT_FAILURE);
// 	}
// }

static int			read_line_from_stdin(char **line, int newline)
{
	int			ret;

	ret = 0;
	if (newline)
		print_prompt();
	if ((ret = get_next_line(0, line)) == -1)
		write(1, "\n", 1);
	else if (ret == 1)
		newline = 1;
	else if (ret == 0)
	{
		if (**line != '\0')
			newline = 0;
		else if (**line == '\0' && newline)
		{
			ft_printf("exit\n");
			exit(EXIT_SUCCESS);
		}
	}
	return (newline);
}

int					main(int argc, char *argv[], char *envp[])
{
	char		*line;
	t_command	*commands;
	int			newline;

	set_signals_handlers();
	// tty_setup(envp);
	newline = 1;
	while (1)
	{
		line = 0;
		// errno = 0;
		newline = read_line_from_stdin(&line, newline);
		commands = parse_line(line);
		execute_commands(commands);
		free(line);
	}
	return (argc && (void **)argv && (void **)envp);
}
