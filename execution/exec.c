/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 22:09:29 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/06/02 12:09:07 by mhaizan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_cmd	*exec_cmd_node(t_shell *shell, t_cmd *cmd)
{
	update_env_array(shell);
	if (cmd->pipe)
	{
		ignore_signals();
		cmd = exec_pipe(shell, cmd);
	}
	else if (check_built_in(cmd))
		exec_single_builtin(shell, cmd);
	else
	{
		ignore_signals();
		if (!cmd->args || !cmd->args[0])
			exec_empty_cmd(shell, cmd);
		else
			exec_external(shell, cmd);
	}
	return (cmd);
}

void	exec(t_shell *shell)
{
	t_cmd	*cmd;
	int		skip;

	cmd = shell->current_cmd;
	skip = 0;
	while (cmd)
	{
		if (skip)
		{
			while (cmd && cmd->pipe)
				cmd = cmd->next;
		}
		else
			cmd = exec_cmd_node(shell, cmd);
		if (cmd->logical_op == OP_AND && shell->exit_status != 0)
			skip = 1;
		else if (cmd->logical_op == OP_OR && shell->exit_status == 0)
			skip = 1;
		else
			skip = 0;
		cmd = cmd->next;
	}
}
