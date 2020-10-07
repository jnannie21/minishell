/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 15:02:11 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/07 17:41:14 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int				ft_isspace(char ch)
{
	if ((ch == '\t') || (ch == '\n') || (ch == '\r') ||
			(ch == '\v') || (ch == '\f') || (ch == ' '))
		return (1);
	return (0);
}

void					*free_tokens(t_token *token_start)
{
	t_token		*temp;

	while (token_start)
	{
		temp = token_start;
		token_start = token_start->next;
		free(temp);
	}
	return (0);
}

static t_token			*token_init(size_t len)
{
	t_token		*token;

	token = 0;
	if (!(token = ft_calloc(1, sizeof(t_token))) ||
		!(token->data = ft_calloc(len + 1, sizeof(char))))
	{
		free(token);
		return (0);
	}
	return (token);
}

static t_token			*create_next_token(t_token *token_start, t_token *token, char *line)
{
	if (*line &&
		!(token->next = token_init(ft_strlen(line))))
		return (free_tokens(token_start));
	return (token->next);
}

t_token					*parse_line(char *line)
{
	int			double_quoted;
	int			single_quoted;
	int			i;
	t_token		*token;
	t_token		*token_start; //save it maybe in some global structure

	double_quoted = 0;
	single_quoted = 0;
	i = 0;
	if (!(token_start = token_init(ft_strlen(line))))
		return (0);
	token = token_start;
	while (*line)
	{
		if (*line == '"')
		{
			if (!single_quoted)
				double_quoted = !double_quoted;
			token->data[i++] = *line++;
		}
		else if (*line == '\'')
		{
			if (!double_quoted)
				single_quoted = !single_quoted;
			token->data[i++] = *line++;
		}
		else if (double_quoted || single_quoted)
		{
			token->data[i++] = *line++;
		}
		else if (!double_quoted && !single_quoted)
		{
			if (ft_strchr(";|<", *line))
			{
				if (i)
				{
					token->data[i] = '\0';
					i = 0;
					if (!(token->next = token_init(1)))
						return (free_tokens(token_start));
					token = token->next;
				}
				token->data[0] = *line++;
				token = create_next_token(token_start, token, line);
			}
			else if (ft_isspace(*line))
			{
				while (ft_isspace(*line))
					line++;
				if (i)
				{
					token->data[i] = '\0';
					i = 0;
					token = create_next_token(token_start, token, line);
				}
			}
			else if (*line == '>')
			{
				if (i)
				{
					token->data[i] = '\0';
					i = 0;
					if (*(line + 1) == '>')
					{
						if (!(token->next = token_init(2)))
							return (free_tokens(token_start));
					}
					else if (!(token->next = token_init(1)))
						return (free_tokens(token_start));
					token = token->next;
				}
				token->data[0] = '>';
				line++;
				if (*line == '>')
				{
					token->data[1] = '>';
					line++;
				}
				token = create_next_token(token_start, token, line);
			}
			else
				token->data[i++] = *line++;
		}
	}
	if (double_quoted || single_quoted)
	{
		free_tokens(token_start);
		ft_printf("all quotes must be enclosed\n");
		return (0);
	}
	return (token_start);
}
