/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-hezan <mohammad-hezan@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 13:29:45 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/06/01 22:27:00 by mohammad-he      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_shell *shell)
{
	int	i;

	i = 0;
	update_env_array(shell);
	while (shell->env_array[i])
	{
		ft_putendl_fd(shell->env_array[i], 1);
		i++;
	}
}

static int	cd_checks(t_cmd *cmd, char **path)
{
	*path = cmd->args[1];
	if (!*path)
		*path = get_env_value(cmd->shell->env, "HOME");
	if (!*path)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		cmd->shell->exit_status = 1;
		return (0);
	}
	if (cmd->args[1] && cmd->args[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		cmd->shell->exit_status = 1;
		return (0);
	}
	return (1);
}

static void	update_oldpwd(t_shell *shell, char *old_pwd)
{
	if (old_pwd)
	{
		if (!change_env_value(shell->env, "OLDPWD", old_pwd))
			free(old_pwd);
	}
}

void	ft_cd(t_cmd *cmd)
{
	char	*path;
	char	cwd[4096];
	char	*new_pwd;
	char	*old_pwd;

	if (!cd_checks(cmd, &path))
		return ;
	old_pwd = get_env_value(cmd->shell->env, "PWD");
	if (old_pwd)
		old_pwd = ft_strdup(old_pwd);
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		cmd->shell->exit_status = 1;
		if (old_pwd)
			free(old_pwd);
		return ;
	}
	if (getcwd(cwd, sizeof(cwd)))
	{
		new_pwd = ft_strdup(cwd);
		change_env_value(cmd->shell->env, "PWD", new_pwd);
	}
	update_oldpwd(cmd->shell, old_pwd);
	cmd->shell->exit_status = 0;
}

void	ft_pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)))
		ft_putendl_fd(cwd, 1);
	else
		perror("minishell: pwd");
}
