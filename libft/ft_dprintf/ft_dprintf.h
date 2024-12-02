/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:03:37 by cde-sous          #+#    #+#             */
/*   Updated: 2024/09/22 13:00:18 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

# include <unistd.h>
# include <stdarg.h>

int				print_char_fd(int fd, char c);
int				print_str_fd(int fd, char *s);
int				print_int_fd(int fd, long long nb);
int				print_unsigned_fd(int fd, unsigned int nb);
int				print_hex_fd(int fd, unsigned int nb, char current);
int				print_hex_long_fd(int fd, unsigned long nb, char current);
int				print_pointer_fd(int fd, void *p);
int				ft_dprintf(int fd, const char *format, ...);

#endif
