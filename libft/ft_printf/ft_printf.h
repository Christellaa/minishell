/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:03:37 by cde-sous          #+#    #+#             */
/*   Updated: 2024/05/29 08:03:39 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int				print_char(char c);
int				print_str(char *s);
int				print_int(long long nb);
int				print_unsigned(unsigned int nb);
int				print_hex(unsigned int nb, char current);
int				print_hex_long(unsigned long nb, char current);
int				print_pointer(void *p);
int				ft_printf(const char *format, ...);

#endif
