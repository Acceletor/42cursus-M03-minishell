/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuebtha <ksuebtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:33:42 by ksuebtha          #+#    #+#             */
/*   Updated: 2025/06/09 17:34:09 by ksuebtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
    t_msh msh;

    if (argc > 1 && argv)
        exit(1);
    ft_bzero(&msh, sizeof(t_msh));
    msh.dict_env = init_env(envp);
    print_env_list(msh.dict_env);
    free_env_list(&msh.dict_env);
	return (0);
}

