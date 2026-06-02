/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-hezan <mohammad-hezan@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 22:28:00 by mohammad-he       #+#    #+#             */
/*   Updated: 2026/06/01 22:28:00 by mohammad-he      ###   ########.fr       */
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

static void	set_unset_flags(t_shell *shell, char *key)
{
	if (ft_strcmp(key, "PATH") == 0)
	{
		if (!get_env_by_key(shell->env, "__UNSET_PATH__"))
			add_env_back(&shell->env,
				make_env_node(ft_strdup("__UNSET_PATH__"), NULL));
		shell->env_edited = true;
	}
	if (ft_strcmp(key, "PWD") == 0)
	{
		if (!get_env_by_key(shell->env, "__UNSET_PWD__"))
			add_env_back(&shell->env,
				make_env_node(ft_strdup("__UNSET_PWD__"), NULL));
		shell->env_edited = true;
	}
	if (ft_strcmp(key, "OLDPWD") == 0)
	{
		if (!get_env_by_key(shell->env, "__UNSET_OLDPWD__"))
			add_env_back(&shell->env,
				make_env_node(ft_strdup("__UNSET_OLDPWD__"), NULL));
		shell->env_edited = true;
	}
}

static void	unset_one(t_shell *shell, char *key)
{
	t_env	*curr;
	t_env	*prev;

	set_unset_flags(shell, key);
	curr = shell->env;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				shell->env = curr->next;
			free_env_node(curr);
			shell->env_edited = true;
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	ft_unset(t_shell *shell, t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		unset_one(shell, cmd->args[i]);
		i++;
	}
}
