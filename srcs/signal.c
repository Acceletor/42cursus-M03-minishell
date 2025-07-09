/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 22:49:18 by eeravci           #+#    #+#             */
/*   Updated: 2025/07/07 21:27:16 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// volatile sig_atomic_t	g_signal = 0;

// void	handle_sigint(int sig)
// {
// 	(void)sig;
// 	g_signal = SIGINT;
// 	write(1, "\n", 1);
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// }

// void	handle_sigquit(int sig)
// {
// 	(void)sig;
// 	g_signal = SIGQUIT;
// }

// void	setup_signals(void)
// {
// 	signal(SIGINT, handle_sigint);
// 	signal(SIGQUIT, SIG_IGN);
// }
