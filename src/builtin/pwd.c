/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylini <cylini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 23:45:41 by cylini            #+#    #+#             */
/*   Updated: 2025/02/02 22:22:25 by cylini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("pwd: error retrieving current directory :No such file or directory");
		return (0);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (1);
}
