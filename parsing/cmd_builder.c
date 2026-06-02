/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 22:48:36 by mohammad-he       #+#    #+#             */
/*   Updated: 2026/06/02 12:08:36 by mhaizan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_args(t_token *tok)
{
	int	i;

	i = 0;
	while (tok && tok->type != PIPE && tok->type != AND && tok->type != OR)
	{
		if (tok->type == CMD)
		{
			if (tok->value[0] != '\0' || tok->quote_type != 0)
				i++;
		}
		else
			tok = tok->next;
		if (tok)
			tok = tok->next;
	}
	return (i);
}

static void	fill_args(t_cmd *cmd, t_token **tok)
{
	int	i;
	int	count;

	count = count_args(*tok);
	cmd->args = malloc(sizeof(char *) * (count + 1));
	if (!cmd->args)
		return ;
	i = 0;
	while (*tok && (*tok)->type != PIPE && (*tok)->type != AND
		&& (*tok)->type != OR)
	{
		if ((*tok)->type == CMD)
		{
			if ((*tok)->value[0] != '\0' || (*tok)->quote_type != 0)
				cmd->args[i++] = ft_strdup((*tok)->value);
			*tok = (*tok)->next;
		}
		else
			handle_redirection(cmd, tok);
	}
	cmd->args[i] = NULL;
}

static void	handle_cmd_operators(t_cmd *curr, t_token **tok)
{
	if (*tok && (*tok)->type == PIPE)
	{
		curr->pipe = true;
		*tok = (*tok)->next;
	}
	else if (*tok && (*tok)->type == AND)
	{
		curr->logical_op = OP_AND;
		*tok = (*tok)->next;
	}
	else if (*tok && (*tok)->type == OR)
	{
		curr->logical_op = OP_OR;
		*tok = (*tok)->next;
	}
}

t_cmd	*build_cmd_table(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*curr;
	t_token	*tok;

	head = NULL;
	tok = tokens;
	while (tok)
	{
		curr = create_cmd_node();
		fill_args(curr, &tok);
		add_cmd(&head, curr);
		handle_cmd_operators(curr, &tok);
	}
	return (head);
}
