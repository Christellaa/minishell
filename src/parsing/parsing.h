/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:51:38 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/07 22:18:47 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../../includes/minishell.h"

// exec_list
int	create_exec_list(t_data *data);
// expander
int	expand_tokens_and_handle_quotes(t_data *data);
// lexer
int	lex_input(char *input, t_data *data);
// parser
int	parse_input(t_data *data, char *input);

#endif
