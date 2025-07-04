#include "../include/minishell.h"

void	handle_redirections(t_redirect *redir)
{
	int	fd;

	while (redir)
	{
		fd = -1;
		if (redir->type == TOKEN_REDIR_OUT)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == TOKEN_APPEND)
			fd = open(redir->file, O_WRONLY | O_CREAT |O_APPEND, 0644);
		else if (redir->type == TOKEN_REDIR_IN)
			fd = open(redir->file, O_RDONLY);
		else if (redir->type == TOKEN_HEREDOC)
			fd = handle_heredoc(redir->file);
		if (fd < 0)
			perror ("minishell: redirection");
		else
		{
			if (redir->type == TOKEN_REDIR_IN || redir->type == TOKEN_HEREDOC)
				dup2(fd, STDIN_FILENO);
			else
				dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		redir = redir->next;
	}
}


int handle_heredoc(const char *delimiter)
{
	int pipefd[2];
	char *line;

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
			break;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}