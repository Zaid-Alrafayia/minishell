/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa </var/spool/mail/zaalrafa>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 13:14:24 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/05/10 13:27:11 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
 we can create this function by reading the data from stdin and then save it to a variable in the cmd struct
 this function down here is something you can take some ideas from.
 */
void	lim_handler(t_shell *shell)
{
	char	*str;
	size_t	len;
	int		fd[2];

	//	if (pipe(fd) == -1)
	// 	needs a error_message function that stops the execution
	len = ft_strlen(shell->tokens[3].value);
	// index needs to be changed based on parsing
	while (1)
	{
		printf("here_doc> ");
		str = get_next_line(0);
		if (!str)
			break ;
		if (ft_strncmp(str, shell->tokens[3].value, len) == 0
			&& str[len] == '\n')
		{
			free(str);
			break ;
		}
		write(fd[1], str, ft_strlen(str));
		free(str);
	}
	close(fd[1]);
	// shell-> = fd[0]; here should be where we save the pipe fd input to our input for the cmd
}
