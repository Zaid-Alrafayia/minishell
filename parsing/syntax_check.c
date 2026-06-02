/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-hezan <mohammad-hezan@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 22:49:13 by mohammad-he       #+#    #+#             */
/*   Updated: 2026/05/23 09:32:51 by mohammad-he      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	check_pipe_syntax(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	if (curr && curr->type == PIPE)
		return (false);
	while (curr)
	{
		if (curr->type == PIPE)
		{
			if (!curr->next || curr->next->type == PIPE)
				return (false);
		}
		curr = curr->next;
	}
	return (true);
}

static bool	check_redir_syntax(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	while (curr)
	{
		if (is_redirection(curr->type))
		{
			if (!curr->next)
			{
				ft_putendl_fd("minishell: syntax error near unexpected token"
					" `newline'", 2);
				return (false);
			}
			if (is_redirection(curr->next->type) || curr->next->type == PIPE)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `",
					2);
				ft_putstr_fd(curr->next->value, 2);
				ft_putendl_fd("'", 2);
				return (false);
			}
		}
		curr = curr->next;
	}
	return (true);
}

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

static bool	check_braces(t_token *tokens)
{
	t_token	*curr;
	bool	is_first;

	curr = tokens;
	is_first = true;
	while (curr)
	{
		if (curr->type == PIPE)
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

bool	check_syntax(t_token *tokens)
{
	if (!tokens)
		return (false);
	if (!check_pipe_syntax(tokens))
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		return (false);
	}
	if (!check_redir_syntax(tokens))
	{
		return (false);
	}
	if (!check_braces(tokens))
		return (false);
	if (!check_unclosed_quotes(tokens))
		return (false);
	return (true);
}
