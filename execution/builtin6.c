/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:00:00 by mhaizan           #+#    #+#             */
/*   Updated: 2026/06/02 12:00:00 by mhaizan          ###   ########.fr       */
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

static int	skip_spaces_and_sign(char *s, int *sign)
{
	int	i;

	i = 0;
	*sign = 1;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

int	is_exit_numeric(char *s)
{
	int	i;
	int	sign;

	i = skip_spaces_and_sign(s, &sign);
	if (!s[i])
		return (0);
	while (s[i] && ft_isdigit(s[i]))
		i++;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t')
			return (0);
		i++;
	}
	i = skip_spaces_and_sign(s, &sign);
	return (check_overflow(s + i, sign));
}

void	ft_pwd(t_shell *shell)
{
	char	cwd[4096];
	char	*env_pwd;

	if (getcwd(cwd, sizeof(cwd)))
		ft_putendl_fd(cwd, 1);
	else
	{
		env_pwd = get_env_value(shell->env, "PWD");
		if (env_pwd)
			ft_putendl_fd(env_pwd, 1);
		else
			perror("minishell: pwd");
	}
}
