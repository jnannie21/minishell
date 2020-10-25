/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 20:27:24 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/24 13:32:05 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tokens)
{
	printf("tockens:\n");
	while (tokens)
	{
		write(1, tokens->data, ft_strlen(tokens->data));
		write(1, "\n", 1);
		tokens = tokens->next;
	}
}

void	print_argv(char **argv)
{
	if (!argv || !*argv || !**argv)
		return ;
	while (argv && *argv)
	{
		write(1, *argv, ft_strlen(*argv));
		if (**argv)
			write(1, " ", 1);
		argv++;
	}
	write(1, "\n", 1);
}
