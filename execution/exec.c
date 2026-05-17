/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa </var/spool/mail/zaalrafa>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 22:09:29 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/05/17 12:03:47 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_process(t_shell *shell, t_cmd *cmd)
{
	char	*cmd_pt;

	cmd_pt = cmd_path(shell, cmd->args[0]);
	execve(cmd_pt, cmd->args, shell->env_array);
	exit(1);
}

void	exec_external(t_shell *shell)
{
	*shell->pids = fork();
	if (shell->pids == 0)
	{
	}
}

void	exec(t_shell *shell)
{
	if (check_built_in(shell->current_cmd))
		built_in(shell->current_cmd);
	else if (shell->current_cmd[0].pipe)
		exec_pipe(shell);
	else
		exec_external(shell);
}
