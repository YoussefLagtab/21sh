/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 09:49:50 by ylagtab           #+#    #+#             */
/*   Updated: 2021/02/28 11:28:43 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '"'
# define BACK_SLASH '\\'

t_vector	*parse_command(char *cmd);
char		quote_type(char c);
int			is_space(char c, int quote);
void		remove_quotes(t_vector *tokens);

#endif
