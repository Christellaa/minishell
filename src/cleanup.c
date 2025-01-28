/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:01:56 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/28 11:02:49 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		get_err_code(int flag);
void	free_tokens(t_token *token);
void	free_exec(t_exec *exec);
void	free_env(t_env *pair);

int	print_error(int flag, char *error, char *option, t_data *data)
{
	data->exit_code = get_err_code(flag);
	if (flag == 0) // 2
		printf("%s '%s'\n", SYNTAX_ERR, error);
	else if (flag == 1) // 127
		printf("%s%s\n", error, CMD_ERR);
	else if (flag == 9) // 127
		printf("%s%s\n", error, CMD_PATH_ERR);
	else if (flag == 2) // 2
		printf("%s%s '%s'\n", error, OPTION_ERR, option);
	else if (flag == 3) // 1
		printf("%s%s\n", error, FILE_ERR);
	else if (flag == 4) // 1
		printf("%s%s\n", error, FILE_DENY);
	else if (flag == 5) // 2
		printf("%s\n", QUOTE_ERR);
	else if (flag == 6) // 1
		printf("%s\n", MALLOC_ERR);
	else if (flag == 7) // 1
		printf("%s\n", TOO_MANY_ARG);
	else if (flag == 8) // 1; function errors
		printf("%s error", error);
	return (data->exit_code);
}

int	get_err_code(int flag)
{
	int	code;

	if (flag == 3 || flag == 4 || flag == 6 || flag == 7 || flag == 8)
		code = 1;
	else if (flag == 0 || flag == 2 || flag == 5)
		code = 2;
	else if (flag == 1 || flag == 9)
		code = 127;
	return (code);
}

void	cleanup(t_data *data, int type)
{
	if (data)
	{
		if (type == 1)
		{
			if (data->token_list)
				free_tokens(data->token_list);
			data->token_list = NULL;
			if (data->exec_list)
				free_exec(data->exec_list);
			data->exec_list = NULL;
			if (data->env_list)
				free_env(data->env_list);
			free(data);
			rl_clear_history();
		}
		else if (type == 0)
		{
			if (data->token_list)
				free_tokens(data->token_list);
			data->token_list = NULL;
			if (data->exec_list)
				free_exec(data->exec_list);
			data->exec_list = NULL;
		}
	}
}

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->value);
		free(tmp);
	}
}

void	free_exec(t_exec *exec)
{
	t_exec	*tmp;
	t_arg	*arg;
	t_files	*file;

	while (exec)
	{
		tmp = exec;
		exec = exec->next;
		while (tmp->arg_list)
		{
			arg = tmp->arg_list;
			tmp->arg_list = tmp->arg_list->next;
			free(arg);
		}
		while (tmp->files)
		{
			file = tmp->files;
			tmp->files = tmp->files->next;
			free(file);
		}
		free(tmp);
	}
}

void	free_env(t_env *pair)
{
	t_env	*tmp;

	while (pair)
	{
		tmp = pair;
		pair = pair->next;
		free(tmp->raw);
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}
