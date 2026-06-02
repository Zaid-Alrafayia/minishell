/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 10:13:07 by mohammad-he       #+#    #+#             */
/*   Updated: 2026/06/02 10:26:50 by mhaizan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

typedef struct s_shell	t_shell;
typedef enum e_token_type
{
	REDIRECT_IN,
	REDIRECT_OUT,
	CMD,
	TRUNCATE,
	APPEND,
	HEREDOC,
	PIPE,
	AND,
	OR
}						t_token_type;

typedef enum e_logical_op
{
	OP_NONE,
	OP_AND,
	OP_OR
}						t_logical_op;

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	int					quote_type;
	struct s_token		*next;
}						t_token;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_cmd
{
	char				**args;
	int					infile;
	int					outfile;
	bool				append;
	bool				pipe;
	t_logical_op		logical_op;
	char				*limiter;
	struct s_cmd		*next;
	t_shell				*shell;
}						t_cmd;

typedef struct s_shell
{
	char				**history;
	pid_t				*pids;
	int					stdin_backup;
	int					stdout_backup;
	bool				env_edited;
	char				**env_array;
	struct s_env		*env;
	struct s_cmd		*current_cmd;
	struct s_token		*tokens;
	int					exit_status;
}						t_shell;
