/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-hezan <mohammad-hezan@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 12:02:07 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/05/23 09:06:43 by mohammad-he      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	write_echo_arg(t_cmd *cmd, int i)
{
	if (write(1, cmd->args[i], ft_strlen(cmd->args[i])) == -1)
	{
		perror("minishell: echo: write error");
		cmd->shell->exit_status = 1;
		return (0);
	}
	if (cmd->args[i + 1])
	{
		if (write(1, " ", 1) == -1)
		{
			perror("minishell: echo: write error");
			cmd->shell->exit_status = 1;
			return (0);
		}
	}
	return (1);
}

void	ft_echo(t_cmd *cmd)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (cmd->args[i] && is_n_flag(cmd->args[i]))
	{
		n_flag = 1;
		i++;
	}
	while (cmd->args[i])
	{
		if (!write_echo_arg(cmd, i))
			return ;
		i++;
	}
	if (!n_flag)
	{
		if (write(1, "\n", 1) == -1)
		{
			perror("minishell: echo: write error");
			cmd->shell->exit_status = 1;
		}
	}
}
