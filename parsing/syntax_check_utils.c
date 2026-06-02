/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:15:00 by mhaizan           #+#    #+#             */
/*   Updated: 2026/06/02 12:15:00 by mhaizan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	check_braces_error(char *value)
{
	if (ft_strcmp(value, "{") == 0)
	{
		ft_putendl_fd("minishell: syntax error: "
			"unexpected end of file", 2);
		return (false);
	}
	if (ft_strcmp(value, "}") == 0)
	{
		ft_putendl_fd("minishell: syntax error near "
			"unexpected token `}'", 2);
		return (false);
	}
	return (true);
}

bool	check_braces(t_token *tokens)
{
	t_token	*curr;
	bool	is_first;

	curr = tokens;
	is_first = true;
	while (curr)
	{
		if (curr->type == PIPE || curr->type == AND || curr->type == OR)
			is_first = true;
		else if (curr->type == CMD && curr->quote_type == 0)
		{
			if (is_first)
			{
				if (!check_braces_error(curr->value))
					return (false);
				is_first = false;
			}
		}
		curr = curr->next;
	}
	return (true);
}
