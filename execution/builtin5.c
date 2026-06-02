/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 11:55:00 by mhaizan           #+#    #+#             */
/*   Updated: 2026/06/02 11:55:00 by mhaizan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	swap_str(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	sort_export_arr(char **arr, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
				swap_str(&arr[j], &arr[j + 1]);
			j++;
		}
		i++;
	}
}

static void	print_export_arr(char **arr, int count)
{
	int		i;
	char	*eq;

	i = -1;
	while (++i < count)
	{
		ft_putstr_fd("declare -x ", 1);
		eq = ft_strchr(arr[i], '=');
		if (eq)
		{
			write(1, arr[i], eq - arr[i] + 1);
			write(1, "\"", 1);
			ft_putstr_fd(eq + 1, 1);
			ft_putendl_fd("\"", 1);
		}
		else
			ft_putendl_fd(arr[i], 1);
	}
}

static void	fill_export_arr(t_shell *shell, char **arr)
{
	t_env	*curr;
	int		i;
	char	*tmp;

	curr = shell->env;
	i = 0;
	while (curr)
	{
		if (ft_strncmp(curr->key, "__UNSET_", 8) != 0)
		{
			if (curr->value)
			{
				tmp = ft_strjoin(curr->key, "=");
				arr[i++] = ft_strjoin(tmp, curr->value);
				free(tmp);
			}
			else
				arr[i++] = ft_strdup(curr->key);
		}
		curr = curr->next;
	}
}

void	print_export(t_shell *shell)
{
	t_env	*curr;
	char	**arr;
	int		count;
	int		i;

	count = 0;
	curr = shell->env;
	while (curr)
	{
		if (ft_strncmp(curr->key, "__UNSET_", 8) != 0)
			count++;
		curr = curr->next;
	}
	arr = malloc(sizeof(char *) * count);
	if (!arr)
		return ;
	fill_export_arr(shell, arr);
	sort_export_arr(arr, count);
	print_export_arr(arr, count);
	i = -1;
	while (++i < count)
		free(arr[i]);
	free(arr);
}
