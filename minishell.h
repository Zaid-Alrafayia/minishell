/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-hezan <mohammad-hezan@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 22:38:19 by mohammad-he       #+#    #+#             */
/*   Updated: 2026/05/15 22:56:38 by mohammad-he      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "42_libft/libft.h"
# include "structs.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

t_token	*create_tok(char *value, t_token_type type, int quote);
int		add_token(t_token **tokens, t_token *new_node);
t_token	*tokenize_input(char *in);

bool	check_syntax(t_token *tokens);
bool	parse_input(t_shell *shell, char *input);

void	expand_tokens(t_shell *shell);
char	*get_env_val(t_shell *shell, char *key);
int		get_var_len(char *str);
char	*join_and_free(char *s1, char *s2);

t_cmd	*create_cmd_node(void);
void	add_cmd(t_cmd **cmds, t_cmd *new_cmd);
t_cmd	*build_cmd_table(t_token *tokens);

void	handle_redirection(t_cmd *cmd, t_token **tok);
int		handle_heredoc(char *limiter);

t_env	*init_env(char **envp);
void	init_shell(t_shell *shell, char **envp);
void	free_cycle(t_shell *shell);
void	free_shell(t_shell *shell);

void	init_signals(void);
void	exec_signals(void);

void	execute_commands(t_shell *shell);

#endif