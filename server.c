/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfelwood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:54:13 by tfelwood          #+#    #+#             */
/*   Updated: 2022/03/02 15:03:02 by tfelwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_write_message(t_message *message)
{
	write(1, "\n", 1);
	ft_putstr_fd(message->text, 1);
	free(message->text);
	message->text = NULL;
	message->size = 0;
}

static void	ft_change_client(t_message *message, int pid)
{
	if (pid != 0)
	{
		if (pid != -1)
			message->last_pid = pid;
		if (message->text)
		{
			free(message->text);
			message->text = NULL;
		}
		message->count = 0;
		message->size = 0;
		message->symb = 0;
	}
	else if (message->last_pid == 0)
	{
		free(message->text);
		ft_putstr_fd("Error: incorrect PID\n");
		exit(0);
	}
	
}

static void	ft_get_message(int signal, siginfo_t *info, void *data)
{
	static t_message	message;

	(void) data;
	if (!info->si_pid || info->si_pid != message.last_pid)
		ft_change_client(&message, info->si_pid);
	if (signal == SIGUSR2)
		message.symb |= 1 << (7 - message.count);
	if (++message.count == 8)
	{
		if (!message.symb)
			ft_write_message(&message);
		else if (ft_addchar(&message) < 0)
		{
			free(message.text);
			ft_putstr_fd("Error\n", 2);
			exit(0);
		}
		message.count = 0;
		message.symb = 0;
	}
	if (kill(message.last_pid, SIGUSR2) < 0)
		ft_change_client(&message, -1);
}

static int	ft_signal_init(struct sigaction *signal)
{
	sigset_t			block;

	if (sigemptyset(&block) < 0|| sigaddset(&block, SIGUSR1) < 0
		|| sigaddset(&block, SIGUSR2) < 0)
		return (-1);
	ft_memset(signal, 0, sizeof(struct sigaction));
	signal->sa_mask = block;
	signal->sa_flags = SA_SIGINFO;
	signal->sa_sigaction = ft_get_message;
	if (sigaction(SIGUSR1, signal, NULL) < 0
		|| sigaction (SIGUSR2, signal, NULL) < 0)
		return (-1);
	return (0);
}

int	main(void)
{
	struct sigaction	signal;

	if (!ft_signal_init(&signal))
	{
		ft_putstr_fd("My PID is: ", 1);
		ft_rec_putnbr(getpid(), 1);
		while (1)
			pause();
	}
	else
		ft_putstr_fd("Error\n", 2);
}
