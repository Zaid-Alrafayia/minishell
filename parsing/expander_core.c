/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-hezan <mohammad-hezan@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 22:52:13 by mohammad-he       #+#    #+#             */
/*   Updated: 2026/06/02 00:43:18 by mohammad-he      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*extract_var(char *str, int *i, t_shell *shell)
{
	int		len;
	char	*key;
	char	*val;

	(*i)++;
	if (!str[*i])
	{
		(*i)--;
		return (ft_strdup("$"));
	}
	len = get_var_len(str + *i);
	if (len == 0)
	{
		(*i)--;
		return (ft_strdup("$"));
	}
	key = ft_substr(str, *i, len);
	val = get_env_val(shell, key);
	free(key);
	*i += len - 1;
	return (val);
}

static void	handle_quotes(char c, int *state, t_token *tok)
{
	if (c == '\'' && *state != 2)
	{
		*state = 1 - *state;
		tok->quote_type = 1;
	}
	else if (c == '\"' && *state != 1)
	{
		*state = 2 - *state;
		tok->quote_type = 1;
	}
}

static char	*process_char(t_token *tok, t_shell *sh, int *i, int *st)
{
	char	t[2];

	if ((tok->value[*i] == '\'' && *st != 2)
		|| (tok->value[*i] == '"' && *st != 1))
	{
		handle_quotes(tok->value[*i], st, tok);
		return (NULL);
	}
	else if (tok->value[*i] == '$' && *st == 0
		&& (tok->value[*i + 1] == '\'' || tok->value[*i + 1] == '"'))
		return (NULL);
	else if (tok->value[*i] == '$' && *st != 1)
		return (extract_var(tok->value, i, sh));
	else if (tok->value[*i] == '\\' && *st == 0 && tok->value[*i + 1])
		(*i)++;
	t[0] = tok->value[*i];
	t[1] = '\0';
	return (ft_strdup(t));
}

static char	*process_str(t_token *tok, t_shell *shell)
{
	char	*res;
	char	*part;
	int		i;
	int		st;

	res = ft_strdup("");
	i = 0;
	st = 0;
	tok->quote_type = 0;
	while (tok->value[i])
	{
		part = process_char(tok, shell, &i, &st);
		if (part)
			res = join_and_free(res, part);
		i++;
	}
	return (res);
}

void	expand_tokens(t_shell *shell)
{
	t_token	*tok;
	char	*new_val;

	tok = shell->tokens;
	while (tok)
	{
		if (tok->type == CMD)
		{
			new_val = process_str(tok, shell);
			free(tok->value);
			tok->value = new_val;
		}
		tok = tok->next;
	}
}
