/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:51:38 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/06 13:07:15 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../../includes/minishell.h"

// exec_list.c
int	create_exec_list(t_data *data);
// expander.c
int	expand_tokens(t_data *data);
// lexer.c
int	lex_input(char *input, t_data *data);
// parser.c
int	parse_input(t_data *data, char *input);

#endif
