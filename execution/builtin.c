/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-hezan <mohammad-hezan@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 13:29:45 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/05/23 09:35:35 by mohammad-he      ###   ########.fr       */
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

void	ft_cd(t_cmd *cmd)
{
	char	*path;
	char	cwd[4096];

	path = cmd->args[1];
	if (!path)
		path = get_env_value(cmd->shell->env, "HOME");
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		cmd->shell->exit_status = 1;
		return ;
	}
	if (getcwd(cwd, sizeof(cwd)))
		change_env_value(cmd->shell->env, "PWD", cwd);
	cmd->shell->exit_status = 0;
}

// creat a cleanup_shell function that closes and frees everything
void	ft_exit(t_shell *shell)
{
	free_shell(shell);
	exit(EXIT_SUCCESS);
}

void	ft_pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)))
		ft_putendl_fd(cwd, 1);
	else
		perror("minishell: pwd");
}
