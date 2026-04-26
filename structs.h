/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa </var/spool/mail/zaalrafa>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 01:29:23 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/04/24 01:47:23 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdbool.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_cmd
{
	char			*main_cmd;
	char			**flags;
	int				infile;
	int				outfile;
	bool			append;
	char			*limiter;
	struct s_cmd	*next;
}					t_cmd;
typedef struct s_shell
{
	char			**history;
	char			**env_array;
	struct s_env	*env;
	struct s_cmd	*current_cmd;
	int				exit_status;
}					t_shell;
