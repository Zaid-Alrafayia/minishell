/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 22:09:29 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/06/02 01:33:33 by mhaizan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exec_not_found(t_shell *shell, t_cmd *cmd)
{
	int	code;

	code = 127;
	if (ft_strchr(cmd->args[0], '/'))
	{
		if (access(cmd->args[0], F_OK) == 0
			&& access(cmd->args[0], X_OK) != 0)
			code = 126;
		write(2, "minishell: ", 11);
		perror(cmd->args[0]);
		free_shell(shell);
		exit(code);
	}
	write(2, "minishell: ", 11);
	write(2, cmd->args[0], ft_strlen(cmd->args[0]));
	write(2, ": command not found\n", 20);
	free_shell(shell);
	exit(127);
}

static void	exec_dir_check(char *cmd_pt, t_cmd *cmd)
{
	struct stat	st;

	if (stat(cmd_pt, &st) == 0 && S_ISDIR(st.st_mode))
	{
		write(2, "minishell: ", 11);
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		write(2, ": Is a directory\n", 17);
	}
	else
		perror(cmd->args[0]);
}

void	child_process(t_shell *shell, t_cmd *cmd)
{
	char		*cmd_pt;

	exec_signals();
	if (!apply_redirs(cmd))
	{
		free_shell(shell);
		exit(1);
	}
	if (!cmd->args || !cmd->args[0])
	{
		free_shell(shell);
		exit(0);
	}
	exec_builtin_child(shell, cmd);
	cmd_pt = cmd_path(shell, cmd->args[0]);
	if (!cmd_pt)
		exec_not_found(shell, cmd);
	execve(cmd_pt, cmd->args, shell->env_array);
	exec_dir_check(cmd_pt, cmd);
	free(cmd_pt);
	free_shell(shell);
	exit(126);
}

void	exec_external(t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
		child_process(shell, shell->current_cmd);
	waitpid(pid, &status, 0);
	set_exit_status(shell, status);
	close_cmd_fds(shell->current_cmd);
}

void	exec(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = shell->current_cmd;
	if (!cmd)
		return ;
	update_env_array(shell);
	if (cmd->pipe || cmd->next)
	{
		ignore_signals();
		exec_pipe(shell);
	}
	else if (check_built_in(cmd))
		exec_single_builtin(shell, cmd);
	else
	{
		ignore_signals();
		if (!cmd->args || !cmd->args[0])
			exec_empty_cmd(shell, cmd);
		else
			exec_external(shell);
	}
}
