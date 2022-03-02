/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfelwood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:54:13 by tfelwood          #+#    #+#             */
/*   Updated: 2022/03/02 13:31:56 by tfelwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minitalk.h"

static int	ft_addchar(t_message *message)
{
	char	*copy;
	int		count;

	count = 0;
	if (!message->size)
		count = 8;
	else if ((int)ft_strlen(message->text) >= message->size - 1)
		count = 2 * message->size;
	if (count)
	{
		copy = (char *) malloc(count * sizeof(char));
		if (!copy)
			return (-1);
		message->size = count;
		ft_strlcpy(copy, message->text, message->size);
		free(message->text);
		message->text = copy;
	}
	count = ft_strlen(message->text);
	message->text[count] = message->symb;
	message->text[count + 1] = 0;
	return (0);
}

static void	ft_write_message(t_message *message)
{
	if (message->text)
		write(1, "\n", 1);
	ft_putstr_fd(message->text, 1);
	free(message->text);
	message->text = NULL;
	message->size = 0;
}

static void	ft_change_client(t_message *message)
{
	ft_write_message(message);
	message->count = 0;
	message->symb = 0;
}

void ft_get_message(int signal, siginfo_t *info, void *data)
{
	static t_message message;

	(void) data;
	if (message.last_pid && info->si_pid != message.last_pid)
		ft_change_client(&message);
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
	if (kill(info->si_pid, SIGUSR2) < 0)
	{
		ft_change_client(&message);
		message.last_pid = 0;
	}
	message.last_pid = info->si_pid;
}

static int ft_signal_init(struct sigaction *signal)
{
	sigset_t			block;

	if (sigemptyset(&block) < 0 || sigaddset(&block, SIGUSR1) < 0
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

int	main()
{
	struct sigaction	signal;

	if (!ft_signal_init(&signal))
	{
		ft_putstr_fd("My PID is: ", 1);
		ft_rec_putnbr(getpid(), 1);
		//write(1, "\n", 1);
		while (1)
			pause();
	}
	else
		ft_putstr_fd("Error\n",2);
}