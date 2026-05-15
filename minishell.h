/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa </var/spool/mail/zaalrafa>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 15:36:41 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/05/14 00:09:44 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "42_libft/libft.h"
# include "structs.h"
//------------utils--------------//
void	free_arr(char **arr);
void	error_message(char *str, int errno);
int		count_env(t_env *env);
void	free_env_node(t_env *tmp);

//------------execution----------//
char	*cmd_path(t_shell *shell, char *cmd);
char	*check_path(t_shell *shell, char *cmd);
char	**rebuild_env(t_shell *shell);
bool	change_env_value(t_env *env, char *key, char *value);
char	*get_env_value(t_env *env, char *key);
t_env	*get_env_by_key(t_env *env, char *key);
//--builtin--//
void	ft_env(t_shell *shell);
void	ft_unset(t_shell *shell, t_cmd *cmd);
void	ft_export(t_shell *shell, t_cmd *cmd);
void	ft_exit(t_shell *shell);
void	ft_pwd(void);
void	ft_cd(t_cmd *cmd);

//------------parsing------------//
#endif
