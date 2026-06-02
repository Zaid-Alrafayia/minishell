/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:12:00 by mhaizan           #+#    #+#             */
/*   Updated: 2026/06/02 12:12:00 by mhaizan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	finish_pipe(t_shell *shell, int fd_in, pid_t last_pid)
{
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (last_pid != -1)
		wait_pipeline(shell, last_pid);
}
