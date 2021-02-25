/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 17:18:11 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/25 19:08:01 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static void	check_ambiguous_redirect(char *str)
{
	if (str == NULL || *str == '\0')
	{
		g_errno = EAMBIGREDIRECT;
		ft_perror(NULL, NULL, FALSE);
	}
}

void		perform_redirections(t_vector *tokens)
{
	t_token	*tk;
	t_token	*tmp_tk;
	int		io_number;
	size_t	i;

	i = 0;
	io_number = -1;
	while (i < tokens->length)
	{
		tk = (t_token*)tokens->array[i]->content;
		if (tk->type == IO_NUMBER)
			io_number = *(int*)tk->data;
		else if (tk->type == GREAT || tk->type == DGREAT)
		{
			if (io_number == -1)
				io_number = STDOUT_FILENO;
			tmp_tk = (t_token*)tokens->array[i + 1]->content;
			check_ambiguous_redirect(tmp_tk->data);
			redirect_output(tmp_tk->data, io_number, tk->type == DGREAT);
		}
		else if (tk->type == ANDGREAT || tk->type == ANDDGREAT)
		{
			tmp_tk = (t_token*)tokens->array[i + 1]->content;
			check_ambiguous_redirect(tmp_tk->data);
			redirect_output(tmp_tk->data, STDOUT_FILENO, tk->type == ANDDGREAT);
			fd_aggregation(STDOUT_FILENO, STDERR_FILENO);
		}
		else if (tk->type == GREATAND)
		{
			if (io_number == -1)
				io_number = STDOUT_FILENO;
			tmp_tk = (t_token*)tokens->array[i + 1]->content;
			fd_aggregation(ft_atoi(tmp_tk->data), io_number);
		}
		else if (tk->type == GREATANDDASH)
		{
			if (io_number == -1)
				io_number = STDOUT_FILENO;
			close(io_number);
		}
		else if (tk->type == LESS)
		{
			if (io_number == -1)
				io_number = STDIN_FILENO;
			tmp_tk = (t_token*)tokens->array[i + 1]->content;
			redirect_input(tmp_tk->data, io_number);
		}
		else if (tk->type == DLESS)
		{
			if (io_number == -1)
				io_number = STDIN_FILENO;
			tmp_tk = (t_token*)tokens->array[i + 1]->content;
			here_document(io_number, tmp_tk->data);
		}

		++i;
	}
	remove_redirections_tokens(tokens);
}
