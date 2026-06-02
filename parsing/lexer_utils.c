/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-hezan <mohammad-hezan@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 22:51:19 by mohammad-he       #+#    #+#             */
/*   Updated: 2026/05/15 22:51:20 by mohammad-he      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_redirection(t_token_type type)
{
	if (type == REDIRECT_IN || type == REDIRECT_OUT
		|| type == TRUNCATE || type == APPEND || type == HEREDOC)
		return (true);
	return (false);
}

t_token	*create_tok(char *value, t_token_type type, int quote)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->value = ft_strdup(value);
	new_node->type = type;
	new_node->quote_type = quote;
	new_node->next = NULL;
	return (new_node);
}

int	add_token(t_token **tokens, t_token *new_node)
{
	t_token	*temp;

	if (!new_node)
		return (0);
	if (!*tokens)
	{
		*tokens = new_node;
		return (1);
	}
	temp = *tokens;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
	return (1);
}

static bool	check_unclosed_error(int q)
{
	if (q != 0)
	{
		ft_putstr_fd("minishell: unexpected EOF while "
			"looking for matching `", 2);
		ft_putchar_fd(q, 2);
		ft_putendl_fd("'", 2);
		return (false);
	}
	return (true);
}

bool	check_unclosed_quotes(t_token *tokens)
{
	t_token	*curr;
	int		i;
	int		q;

	curr = tokens;
	while (curr)
	{
		if (curr->type == CMD)
		{
			i = 0;
			q = 0;
			while (curr->value[i])
			{
				if ((curr->value[i] == '\'' || curr->value[i] == '\"') && !q)
					q = curr->value[i];
				else if (curr->value[i] == q)
					q = 0;
				i++;
			}
			if (!check_unclosed_error(q))
				return (false);
		}
		curr = curr->next;
	}
	return (true);
}
