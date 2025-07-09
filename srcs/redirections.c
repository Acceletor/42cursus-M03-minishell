/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuebtha <ksuebtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:48:01 by eeravci           #+#    #+#             */
/*   Updated: 2025/07/09 23:02:09 by ksuebtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_single_redirect(t_redirect *redir, t_redirect *last_heredoc)
{
	int	fd;

	fd = -1;
	if (redir->type == TOKEN_REDIR_OUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == TOKEN_APPEND)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->type == TOKEN_REDIR_IN)
		fd = open(redir->file, O_RDONLY);
	else if (redir->type == TOKEN_HEREDOC)
		fd = ft_atoi(redir->file);
	if (fd < 0)
		return (-1);
	if (redir->type == TOKEN_HEREDOC && redir != last_heredoc)
		close(fd);
	else if (redir->type == TOKEN_REDIR_IN || redir->type == TOKEN_HEREDOC)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	if (!(redir->type == TOKEN_HEREDOC && redir != last_heredoc))
		close(fd);
	return (0);
}

void	handle_redirections(t_redirect *redir)
{
	t_redirect	*tmp;
	t_redirect	*last_heredoc;

	last_heredoc = NULL;
	tmp = redir;
	while (tmp)
	{
		if (tmp->type == TOKEN_HEREDOC)
			last_heredoc = tmp;
		tmp = tmp->next;
	}
	while (redir)
	{
		if (handle_single_redirect(redir, last_heredoc) == -1)
		{
			perror("minishell: redirection");
			exit(0);
		}
		redir = redir->next;
	}
}

int	handle_heredoc(const char *delimiter)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

int	heredoc_prepare(t_command *cmd)
{
	t_redirect	*redir;
	int			fd;

	redir = cmd->redirects;
	while (redir)
	{
		if (redir->type == TOKEN_HEREDOC)
		{
			fd = handle_heredoc(redir->file);
			if (fd < 0)
			{
				perror("heredoc");
				return (1);
			}
			free(redir->file);
			redir->file = ft_itoa(fd);
		}
		redir = redir->next;
	}
	return (0);
}
