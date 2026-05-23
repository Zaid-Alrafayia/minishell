/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-hezan <mohammad-hezan@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 11:02:04 by mohammad-he       #+#    #+#             */
/*   Updated: 2026/05/23 09:31:28 by mohammad-he      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	child_pipe_exec(t_shell *shell, t_cmd *cmd, int *pipe_fd,
		int fd_in)
{
	exec_signals();
	if (fd_in != STDIN_FILENO)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (pipe_fd[1] != -1)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	child_process(shell, cmd);
}

static void	parent_pipe_next(t_cmd **cmd, int *pipe_fd, int *fd_in)
{
	close_cmd_fds(*cmd);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	if (*fd_in != STDIN_FILENO)
		close(*fd_in);
	if (pipe_fd[0] != -1)
		*fd_in = pipe_fd[0];
	else
		*fd_in = STDIN_FILENO;
	*cmd = (*cmd)->next;
}

static void	wait_pipeline(t_shell *shell, pid_t last_pid)
{
	int		status;
	pid_t	pid;

	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		if (pid == last_pid)
			set_exit_status(shell, status);
		pid = waitpid(-1, &status, 0);
	}
}

static int	fork_and_exec(t_shell *shell, t_cmd *cmd, int *pipe_fd, int fd_in)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		child_pipe_exec(shell, cmd, pipe_fd, fd_in);
	return (pid);
}

void	exec_pipe(t_shell *shell)
{
	t_cmd	*cmd;
	int		fd_in;
	int		pipe_fd[2];
	pid_t	last_pid;

	cmd = shell->current_cmd;
	fd_in = STDIN_FILENO;
	last_pid = -1;
	while (cmd)
	{
		pipe_fd[0] = -1;
		pipe_fd[1] = -1;
		if (cmd->next && pipe(pipe_fd) == -1)
			break ;
		last_pid = fork_and_exec(shell, cmd, pipe_fd, fd_in);
		if (last_pid == -1)
			break ;
		parent_pipe_next(&cmd, pipe_fd, &fd_in);
	}
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (last_pid != -1)
		wait_pipeline(shell, last_pid);
}
