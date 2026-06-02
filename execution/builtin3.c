/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-hezan <mohammad-hezan@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 22:27:00 by mohammad-he       #+#    #+#             */
/*   Updated: 2026/06/01 22:27:00 by mohammad-he      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_overflow(char *s, int sign)
{
	int		len;
	char	*max;

	while (*s == '0')
		s++;
	len = ft_strlen(s);
	if (len > 19)
		return (0);
	if (len < 19)
		return (1);
	if (sign == 1)
		max = "9223372036854775807";
	else
		max = "9223372036854775808";
	if (ft_strncmp(s, max, 19) > 0)
		return (0);
	return (1);
}

static int	is_exit_numeric(char *s)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	if (s[0] == '-' || s[0] == '+')
		return (check_overflow(s + 1, sign));
	return (check_overflow(s, sign));
}

static void	exit_error(t_cmd *cmd, char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	free_shell(cmd->shell);
	exit(2);
}

void	ft_exit(t_cmd *cmd)
{
	long	code;
	char	*arg;

	if (!cmd->args[1])
	{
		code = cmd->shell->exit_status;
		free_shell(cmd->shell);
		exit((unsigned char)code);
	}
	arg = cmd->args[1];
	if (!is_exit_numeric(arg))
		exit_error(cmd, arg);
	if (cmd->args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		cmd->shell->exit_status = 1;
		return ;
	}
	code = ft_atoi(arg);
	free_shell(cmd->shell);
	exit((unsigned char)code);
}
