/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa </var/spool/mail/zaalrafa>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 10:26:14 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/05/10 10:36:48 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	has_path(char *cmd)
{
	int	i;

	if (!cmd)
		return (0);
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static char	*get_path(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i]))
			&& (envp[i][0] == 'P'))
		{
			return (envp[i] + 5);
		}
		i++;
	}
	return (0);
}

static char	*search_func(char *search_path, char **arr, char *cmd)
{
	int		j;
	char	*tmp;

	j = 0;
	while (arr[j])
	{
		tmp = ft_strjoin(arr[j], "/");
		search_path = ft_strjoin(tmp, cmd);
		if (access(search_path, F_OK | X_OK) != -1)
		{
			free(tmp);
			return (search_path);
		}
		j++;
		free(tmp);
		free(search_path);
	}
	return (NULL);
}

char	*check_path(t_shell *shell, char *cmd)
{
	char	*paths;
	char	**arr;
	char	*search_path;

	search_path = NULL;
	paths = get_path(shell->env_array);
	if (!paths)
		return (NULL);
	arr = ft_split(paths, ':');
	if (!arr)
	{
		return (NULL);
	}
	search_path = search_func(search_path, arr, cmd);
	if (search_path)
		return (search_path);
	free_arr(arr);
	return (NULL);
}

char	*cmd_path(t_shell *shell, char *cmd)
{
	char	*path;

	if (has_path(cmd))
	{
		if (access(cmd, F_OK | X_OK) == -1)
			return (NULL);
		path = cmd;
	}
	else
		path = check_path(shell, cmd);
	return (path);
}
