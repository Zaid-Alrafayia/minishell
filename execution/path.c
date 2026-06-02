/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 10:26:14 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/06/02 17:44:57 by mhaizan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static char	*get_paths_str(t_shell *shell)
{
	char	*paths;

	paths = get_path(shell->env_array);
	if (!paths)
	{
		if (get_env_by_key(shell->env, "__UNSET_PATH__"))
			return (NULL);
		paths = "/usr/local/bin:/usr/bin:/bin:/usr/local/sbin:/usr/sbin:/sbin";
	}
	return (paths);
}

char	*check_path(t_shell *shell, char *cmd)
{
	char	*paths;
	char	**arr;
	char	*search_path;

	if (!cmd || cmd[0] == '\0'
		|| ft_strcmp(cmd, ".") == 0 || ft_strcmp(cmd, "..") == 0)
		return (NULL);
	paths = get_paths_str(shell);
	if (!paths)
		return (NULL);
	arr = ft_split(paths, ':');
	if (!arr)
		return (NULL);
	search_path = search_func(NULL, arr, cmd);
	if (search_path)
	{
		free_arr(arr);
		return (search_path);
	}
	free_arr(arr);
	return (NULL);
}

char	*cmd_path(t_shell *shell, char *cmd)
{
	char	*path;

	if (cmd && ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == -1)
			return (NULL);
		path = ft_strdup(cmd);
	}
	else
		path = check_path(shell, cmd);
	return (path);
}
