/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 15:33:44 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/18 09:24:32 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static void	expand_command(t_vector *tokens)
{
	t_token			*tk;
	char			*word;
	t_token_type	old_token_type;
	size_t			i;

	i = 0;
	old_token_type = NONE;
	while (i < tokens->length)
	{
		tk = (t_token*)tokens->array[i]->content;
		if (tk->type == WORD &&
			old_token_type != DLESS && old_token_type != DLESSDASH)
		{
			word = expand_word(tk->data);
			free(tk->data);
			tk->data = ft_strtrim(word);
			free(word);
			tokens_to_fileds(tokens, &i);
		}
		old_token_type = tk->type;
		++i;
	}
}

void		expansion(t_vector *commands)
{
	t_command	*cmd;
	size_t		i;

	i = 0;
	while (i < commands->length)
	{
		cmd = (t_command*)commands->array[i]->content;
		expand_command(cmd->tokens);
		++i;
	}
}
