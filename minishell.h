/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 01:40:03 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/07 15:28:13 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"

typedef struct			s_token
{
	char				*data;
	//char				type;
	struct s_token		*next;
}						t_token;

typedef struct			s_command
{
	char				*executable;
	char				**argv;
	struct t_command	*next;
}						t_command;

typedef struct			s_commands
{
	char				*correct_path;
	char				**args;
	short				is_out_in_file;
	short				is_append;
	char				*out_file_name;
	short				is_input_from_file;
	char				*input_file_name;
	short				is_pipe;
	struct s_commands	*next;
}						t_commands;

typedef struct			s_shell
{
	char				**path;
	t_commands			*commands;
	char				*cwd;
}						t_shell;

t_token					*parse_line(char *line);
void					*free_tokens(t_token *token_start);

#endif
