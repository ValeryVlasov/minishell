/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_syntax_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aizetta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 18:56:04 by aizetta           #+#    #+#             */
/*   Updated: 2022/01/15 18:56:06 by aizetta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	pipe_error(t_mini *main)
{
	t_word	*head;

	head = main->head_word;
	if (head->is_pipe)
		return (1);
	while (head)
	{
		if ((head->next != NULL) && (head->next->is_pipe && head->is_pipe))
			return (1);
		else if ((head->next != NULL) && (head->next->is_pipe && head->special))
			return (1);
		else if (head->next == NULL && head->is_pipe)
			return (1);
		head = head->next;
	}
	return (0);
}

static int	redir_error(t_mini *main)
{
	t_word	*head;

	head = main->head_word;
	while (head)
	{
		if (head->next == NULL && head->redir_out)
		{
			printf("Minishell:  syntax error near unexpected token `newline'\n");
			return (1);
		}
		if (head->next == NULL && head->heredoc)
		{
			printf("Minishell: syntax error near unexpected token `newline'\n");
			return (1);
		}
		head = head->next;
	}
	return (0);
}

static int	redir_error_2(t_mini *main)
{
	t_word	*head;

	head = main->head_word;
	while (head->next)
	{
		if (head->next->redir_out && head->redir_input)
		{
			printf("Minishell:  syntax error near unexpected token `>'\n");
			return (1);
		}
		else if (head->next->redir_input && head->redir_out)
		{
			printf("Minishell: syntax error near unexpected token `<'\n");
			return (1);
		}
		head = head->next;
	}
	return (0);
}

int	find_syntax_word(t_mini *main)
{
	if (pipe_error(main))
	{
		printf("Minishell: syntax error near unexpected token `|'\n");
		g_last_exit_code = 258;
		return (1);
	}
	if (redir_error(main))
	{
		g_last_exit_code = 258;
		return (1);
	}
	if (redir_error_2(main))
	{
		g_last_exit_code = 258;
		return (1);
	}
	return (0);
}
