/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 22:27:00 by mohammad-he       #+#    #+#             */
/*   Updated: 2026/06/02 12:09:26 by mhaizan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exit_error(t_cmd *cmd, char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	free_shell(cmd->shell);
	exit(2);
}

static void	exit_no_args(t_cmd *cmd)
{
	long	code;

	code = cmd->shell->exit_status;
	free_shell(cmd->shell);
	exit((unsigned char)code);
}

void	ft_exit(t_cmd *cmd)
{
	long	code;
	char	*arg;
	int		i;

	i = 1;
	if (cmd->args[i] && ft_strcmp(cmd->args[i], "--") == 0)
		i++;
	if (!cmd->args[i])
		exit_no_args(cmd);
	arg = cmd->args[i];
	if (!is_exit_numeric(arg))
		exit_error(cmd, arg);
	if (cmd->args[i + 1])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		cmd->shell->exit_status = 1;
		return ;
	}
	code = ft_atoi(arg);
	free_shell(cmd->shell);
	exit((unsigned char)code);
}
