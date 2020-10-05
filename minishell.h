/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 01:40:03 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/05 15:49:48 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"

// typedef	struct			s_list
// {
// 	void				*content;
// 	struct s_list		*next;
// }						t_list;

typedef struct			s_command
{
	char				*executable;
	char				**argv;
	struct t_command	*next;
}						t_command;

#endif
