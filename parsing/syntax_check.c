/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 22:49:13 by mohammad-he       #+#    #+#             */
/*   Updated: 2026/06/02 12:35:00 by mhaizan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	print_op_err(char *val)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (!val)
		ft_putstr_fd("newline", 2);
	else
		ft_putstr_fd(val, 2);
	ft_putendl_fd("'", 2);
	return (false);
}

static bool	check_pipe_syntax(t_token *curr)
{
	if (!curr->next || curr->next->type == PIPE
		|| curr->next->type == AND || curr->next->type == OR)
	{
		if (!curr->next)
		{
			ft_putendl_fd("minishell: syntax error: unexpected end of file", 2);
			return (false);
		}
		return (print_op_err(curr->next->value));
	}
	return (true);
}

static bool	check_redirection_syntax(t_token *curr)
{
	if (!curr->next)
		return (print_op_err("newline"));
	if (is_redirection(curr->next->type) || curr->next->type == PIPE
		|| curr->next->type == AND || curr->next->type == OR)
		return (print_op_err(curr->next->value));
	return (true);
}

static bool	check_tokens_loop(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	if (curr && (curr->type == PIPE || curr->type == AND || curr->type == OR))
		return (print_op_err(curr->value));
	while (curr)
	{
		if (curr->type == CMD && curr->quote_type == 0
			&& ft_strcmp(curr->value, ";") == 0)
			return (print_op_err(";"));
		if (is_redirection(curr->type))
		{
			if (!check_redirection_syntax(curr))
				return (false);
		}
		else if (curr->type == PIPE || curr->type == AND || curr->type == OR)
		{
			if (!check_pipe_syntax(curr))
				return (false);
		}
		curr = curr->next;
	}
	return (true);
}

bool	check_syntax(t_token *tokens)
{
	if (!tokens)
		return (false);
	if (!check_tokens_loop(tokens))
		return (false);
	if (!check_braces(tokens))
		return (false);
	if (!check_unclosed_quotes(tokens))
		return (false);
	return (true);
}
