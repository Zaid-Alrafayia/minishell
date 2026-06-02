/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:05:00 by mhaizan           #+#    #+#             */
/*   Updated: 2026/06/02 12:05:00 by mhaizan          ###   ########.fr       */
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
	if (!get_env_value(shell->env, "PATH"))
		write(2, ": No such file or directory\n", 28);
	else
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

void	exec_external(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
		child_process(shell, cmd);
	waitpid(pid, &status, 0);
	set_exit_status(shell, status);
	close_cmd_fds(shell->current_cmd);
}
