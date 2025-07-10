/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuebtha <ksuebtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:33:42 by ksuebtha          #+#    #+#             */
/*   Updated: 2025/07/10 23:04:35 by ksuebtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_welcome_message(void)
{
	printf("                 ▗▖  ▗▖▄ ▄▄▄▄  ▄  ▄▄▄ ▐▌   ▗▞▀▚▖█ █ \n");
	printf("                 ▐▛▚▞▜▌▄ █   █ ▄ ▀▄▄  ▐▌   ▐▛▀▀▘█ █ \n");
	printf("                 ▐▌  ▐▌█ █   █ █ ▄▄▄▀ ▐▛▀▚▖▝▚▄▄▖█ █ \n");
	printf("                 ▐▌  ▐▌█       █      ▐▌ ▐▌     █ █ \n");
	printf("                                                     \n");
}

int	check_input_and_exit(char *input)
{
	if (!input)
	{
		write(1, "exit\n", 5);
		return (1);
	}
	return (0);
}

void	free_msh(t_msh *msh, int exit_code)
{
	free(msh->input);
	free_env_list(&msh->dict_env);
	free_command_list(msh->cmds);
	exit(exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	t_msh	msh;

	if (argc > 1 && argv)
		exit(1);
	ft_bzero(&msh, sizeof(t_msh));
	msh.dict_env = init_env(envp);
	setup_signals();
	print_welcome_message();
	while (true)
	{
		msh.input = readline("\033[1;35mminishell> \033[0m");
		if (check_input_and_exit(msh.input))
			break ;
		add_history(msh.input);
		msh.tokens = token_stream(&msh);
		msh.cmds = parser(msh.tokens);
		free_tokens(&msh.tokens);
		execute(&msh);
		free_command_list(msh.cmds);
		free(msh.input);
	}
	free_env_list(&msh.dict_env);
	return (0);
}
// print_command_list(msh.cmds);

