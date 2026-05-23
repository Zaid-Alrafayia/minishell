/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-hezan <mohammad-hezan@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 12:05:00 by mohammad-he       #+#    #+#             */
/*   Updated: 2026/05/23 09:32:48 by mohammad-he      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env_array(t_shell *shell)
{
	if (!shell->env_edited)
		return ;
	if (shell->env_array)
		free_arr(shell->env_array);
	shell->env_array = rebuild_env(shell);
	shell->env_edited = false;
}

void	set_exit_status(t_shell *shell, int status)
{
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		shell->exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(1, "Quit (core dumped)\n", 19);
	}
}

void	exec_single_builtin(t_shell *shell, t_cmd *cmd)
{
	shell->exit_status = 0;
	if (!apply_redirs(cmd))
		shell->exit_status = 1;
	else
		built_in(cmd);
	restore_stdio(shell);
	close_cmd_fds(cmd);
}

void	exec_empty_cmd(t_shell *shell, t_cmd *cmd)
{
	if (apply_redirs(cmd))
		shell->exit_status = 0;
	else
		shell->exit_status = 1;
	restore_stdio(shell);
	close_cmd_fds(cmd);
}
