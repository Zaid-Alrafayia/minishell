/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 22:50:33 by mohammad-he       #+#    #+#             */
/*   Updated: 2026/06/02 18:35:42 by mhaizan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *shell, char **envp)
{
	shell->env = init_env(envp);
	shell->env_array = rebuild_env(shell);
	shell->history = NULL;
	shell->pids = NULL;
	shell->tokens = NULL;
	shell->current_cmd = NULL;
	shell->exit_status = 0;
	shell->env_edited = false;
	shell->stdin_backup = dup(STDIN_FILENO);
	shell->stdout_backup = dup(STDOUT_FILENO);
}

void	free_shell(t_shell *shell)
{
	t_env	*tmp;

	free_cycle(shell);
	while (shell->env)
	{
		tmp = shell->env->next;
		free(shell->env->key);
		if (shell->env->value)
			free(shell->env->value);
		free(shell->env);
		shell->env = tmp;
	}
	if (shell->env_array)
		free_arr(shell->env_array);
	close(shell->stdin_backup);
	close(shell->stdout_backup);
	rl_clear_history();
}

static char	*get_input_line(void)
{
	char	*input;

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO)
		&& isatty(STDERR_FILENO))
		input = readline("minishell$ ");
	else
	{
		input = get_next_line(STDIN_FILENO);
		if (input && input[ft_strlen(input) - 1] == '\n')
			input[ft_strlen(input) - 1] = '\0';
	}
	return (input);
}

static void	run_shell_loop(t_shell *shell)
{
	char	*input;

	while (1)
	{
		init_signals();
		input = get_input_line();
		if (!input)
			break ;
		if (*input)
			add_history(input);
		if (parse_input(shell, input))
			exec(shell);
		else if (!isatty(STDIN_FILENO) && shell->exit_status == 2)
		{
			free_cycle(shell);
			free(input);
			break ;
		}
		free_cycle(shell);
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	run_shell_loop(&shell);
	free_shell(&shell);
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && isatty(STDERR_FILENO))
		write(1, "exit\n", 5);
	return (shell.exit_status);
}
