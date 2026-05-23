/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_mock.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-hezan <mohammad-hezan@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 22:52:25 by mohammad-he       #+#    #+#             */
/*   Updated: 2026/05/23 09:06:43 by mohammad-he      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_kv_int(char *label, int value)
{
	ft_putstr_fd(label, 1);
	ft_putnbr_fd(value, 1);
	write(1, "\n", 1);
}

static void	print_cmd_args(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			ft_putstr_fd("  Arg[", 1);
			ft_putnbr_fd(i, 1);
			ft_putstr_fd("]: ", 1);
			ft_putstr_fd(cmd->args[i], 1);
			write(1, "\n", 1);
			i++;
		}
	}
}

void	execute_commands(t_shell *shell)
{
	t_cmd	*cmd;
	int		cmd_num;

	cmd = shell->current_cmd;
	cmd_num = 1;
	while (cmd)
	{
		ft_putstr_fd("--- CMD Node ", 1);
		ft_putnbr_fd(cmd_num++, 1);
		ft_putendl_fd(" ---", 1);
		print_cmd_args(cmd);
		print_kv_int("  Infile fd: ", cmd->infile);
		print_kv_int("  Outfile fd: ", cmd->outfile);
		print_kv_int("  Append mode: ", cmd->append);
		if (cmd->limiter)
		{
			ft_putstr_fd("  Heredoc Limiter: ", 1);
			ft_putendl_fd(cmd->limiter, 1);
		}
		cmd = cmd->next;
	}
}
