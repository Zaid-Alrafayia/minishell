/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 10:10:34 by mohammad-he       #+#    #+#             */
/*   Updated: 2026/06/02 02:09:12 by mhaizan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_heredoc_eof(char *limiter)
{
	ft_putstr_fd("minishell: warning: here-document at line 1 "
		"delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(limiter, 2);
	ft_putendl_fd("')", 2);
}

static char	*read_line_helper(void)
{
	char	*line;

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO)
		&& isatty(STDERR_FILENO))
		line = readline("> ");
	else
	{
		line = get_next_line(STDIN_FILENO);
		if (line && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
	}
	return (line);
}

static void	read_heredoc_lines(int fd, char *limiter)
{
	char	*line;

	while (1)
	{
		line = read_line_helper();
		if (!line)
		{
			print_heredoc_eof(limiter);
			break ;
		}
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

int	handle_heredoc(char *limiter)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror("minishell: pipe");
		return (-1);
	}
	read_heredoc_lines(fd[1], limiter);
	close(fd[1]);
	return (fd[0]);
}
