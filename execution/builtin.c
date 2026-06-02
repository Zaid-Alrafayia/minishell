/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 13:29:45 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/06/02 17:45:35 by mhaizan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cd_checks(t_cmd *cmd, char **path)
{
	*path = cmd->args[1];
	if (*path && ft_strcmp(*path, "--") == 0)
		*path = cmd->args[2];
	if (cmd->args[1] && cmd->args[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		cmd->shell->exit_status = 1;
		return (0);
	}
	if (!*path)
		*path = get_env_value(cmd->shell->env, "HOME");
	if (!*path)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		cmd->shell->exit_status = 1;
		return (0);
	}
	if ((*path)[0] == '\0')
	{
		cmd->shell->exit_status = 0;
		return (0);
	}
	return (1);
}

static void	update_oldpwd(t_shell *shell, char *old_pwd)
{
	if (old_pwd)
	{
		if (!change_env_value(shell->env, "OLDPWD", old_pwd))
		{
			if (!get_env_by_key(shell->env, "__UNSET_OLDPWD__"))
				add_env_back(&shell->env,
					make_env_node(ft_strdup("OLDPWD"), old_pwd));
			else
				free(old_pwd);
		}
		shell->env_edited = true;
	}
}

static int	cd_execute(t_cmd *cmd, char *path, char *old_pwd)
{
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		cmd->shell->exit_status = 1;
		if (old_pwd)
			free(old_pwd);
		return (0);
	}
	return (1);
}

static void	update_pwd(t_cmd *cmd)
{
	char	cwd[4096];
	char	*new_pwd;

	if (getcwd(cwd, sizeof(cwd)))
	{
		new_pwd = ft_strdup(cwd);
		if (!change_env_value(cmd->shell->env, "PWD", new_pwd))
		{
			if (!get_env_by_key(cmd->shell->env, "__UNSET_PWD__"))
				add_env_back(&cmd->shell->env,
					make_env_node(ft_strdup("PWD"), new_pwd));
			else
				free(new_pwd);
		}
		cmd->shell->env_edited = true;
	}
}

void	ft_cd(t_cmd *cmd)
{
	char	*path;
	char	cwd[4096];
	char	*old_pwd;

	if (!cd_checks(cmd, &path))
		return ;
	old_pwd = get_env_value(cmd->shell->env, "PWD");
	if (old_pwd)
		old_pwd = ft_strdup(old_pwd);
	else
	{
		if (getcwd(cwd, sizeof(cwd)))
			old_pwd = ft_strdup(cwd);
	}
	if (!cd_execute(cmd, path, old_pwd))
		return ;
	update_pwd(cmd);
	update_oldpwd(cmd->shell, old_pwd);
	cmd->shell->exit_status = 0;
}
