/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-hezan <mohammad-hezan@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 22:48:57 by mohammad-he       #+#    #+#             */
/*   Updated: 2026/05/15 22:48:58 by mohammad-he      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_env	*create_env_node(char *str)
{
	t_env	*node;
	char	*eq;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	eq = ft_strchr(str, '=');
	if (eq)
	{
		node->key = ft_substr(str, 0, eq - str);
		node->value = ft_strdup(eq + 1);
	}
	else
	{
		node->key = ft_strdup(str);
		node->value = NULL;
	}
	node->next = NULL;
	return (node);
}

static void	update_shlvl(t_env **head)
{
	t_env	*shlvl;
	int		lvl;
	char	*new_lvl;

	shlvl = get_env_by_key(*head, "SHLVL");
	if (shlvl && shlvl->value)
	{
		lvl = ft_atoi(shlvl->value);
		if (lvl < 0)
			lvl = 0;
		else
			lvl++;
		new_lvl = ft_itoa(lvl);
		free(shlvl->value);
		shlvl->value = new_lvl;
	}
	else if (shlvl && !shlvl->value)
		shlvl->value = ft_strdup("1");
	else
		add_env_back(head, make_env_node(ft_strdup("SHLVL"), ft_strdup("1")));
}

static void	add_default_env(t_env **head)
{
	char	cwd[4096];
	t_env	*pwd_node;

	pwd_node = get_env_by_key(*head, "PWD");
	if (getcwd(cwd, sizeof(cwd)))
	{
		if (!pwd_node)
			add_env_back(head,
				make_env_node(ft_strdup("PWD"), ft_strdup(cwd)));
		else if (!pwd_node->value || ft_strcmp(pwd_node->value, cwd) != 0)
		{
			if (pwd_node->value)
				free(pwd_node->value);
			pwd_node->value = ft_strdup(cwd);
		}
	}
	update_shlvl(head);
	if (!get_env_by_key(*head, "_"))
		add_env_back(head,
			make_env_node(ft_strdup("_"), ft_strdup("/usr/bin/env")));
	if (!get_env_by_key(*head, "OLDPWD"))
		add_env_back(head,
			make_env_node(ft_strdup("OLDPWD"), NULL));
}

t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*curr;
	int		i;

	head = NULL;
	i = 0;
	while (envp && envp[i])
	{
		if (!head)
		{
			head = create_env_node(envp[i]);
			curr = head;
		}
		else
		{
			curr->next = create_env_node(envp[i]);
			curr = curr->next;
		}
		i++;
	}
	add_default_env(&head);
	return (head);
}
