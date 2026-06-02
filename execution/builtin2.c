/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-hezan <mohammad-hezan@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 00:09:00 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/06/01 22:28:00 by mohammad-he      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_export(t_shell *shell)
{
	t_env	*curr;

	curr = shell->env;
	while (curr)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(curr->key, 1);
		if (curr->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(curr->value, 1);
			ft_putendl_fd("\"", 1);
		}
		else
			ft_putendl_fd("", 1);
		curr = curr->next;
	}
}

static int	export_invalid(t_cmd *cmd, int i, char *id_end)
{
	if (id_end)
		*id_end = '=';
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(cmd->args[i], 2);
	ft_putendl_fd("': not a valid identifier", 2);
	cmd->shell->exit_status = 1;
	return (1);
}

static void	export_one(t_shell *shell, char *arg)
{
	t_env	*node;
	char	*eq;
	char	*key;

	eq = ft_strchr(arg, '=');
	if (!eq)
	{
		if (!get_env_by_key(shell->env, arg))
			add_env_back(shell->env,
				make_env_node(ft_strdup(arg), NULL));
		return ;
	}
	key = ft_substr(arg, 0, eq - arg);
	node = get_env_by_key(shell->env, key);
	if (node)
	{
		free(node->value);
		node->value = ft_strdup(eq + 1);
		free(key);
	}
	else
		add_env_back(shell->env, make_env_node(key, ft_strdup(eq + 1)));
	shell->env_edited = true;
}

static void	process_export_arg(t_shell *shell, t_cmd *cmd, int *i)
{
	char	*eq;
	char	*id_end;

	eq = ft_strchr(cmd->args[*i], '=');
	if (eq)
	{
		id_end = eq;
		*id_end = '\0';
		if (!is_valid_id(cmd->args[*i]))
		{
			export_invalid(cmd, (*i)++, id_end);
			return ;
		}
		*id_end = '=';
	}
	else if (!is_valid_id(cmd->args[*i]))
	{
		export_invalid(cmd, (*i)++, NULL);
		return ;
	}
	export_one(shell, cmd->args[*i]);
	(*i)++;
}

void	ft_export(t_shell *shell, t_cmd *cmd)
{
	int	i;

	if (!cmd->args[1])
		return (print_export(shell));
	i = 1;
	while (cmd->args[i])
		process_export_arg(shell, cmd, &i);
}
