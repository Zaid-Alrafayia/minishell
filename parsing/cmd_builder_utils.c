/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:10:00 by mhaizan           #+#    #+#             */
/*   Updated: 2026/06/02 12:10:00 by mhaizan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*create_cmd_node(void)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->args = NULL;
	node->infile = STDIN_FILENO;
	node->outfile = STDOUT_FILENO;
	node->append = false;
	node->pipe = false;
	node->logical_op = OP_NONE;
	node->limiter = NULL;
	node->next = NULL;
	return (node);
}

void	add_cmd(t_cmd **cmds, t_cmd *new_cmd)
{
	t_cmd	*temp;

	if (!new_cmd)
		return ;
	if (!*cmds)
	{
		*cmds = new_cmd;
		return ;
	}
	temp = *cmds;
	while (temp->next)
		temp = temp->next;
	temp->next = new_cmd;
}
