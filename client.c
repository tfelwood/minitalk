/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfelwood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:54:02 by tfelwood          #+#    #+#             */
/*   Updated: 2022/03/02 15:15:49 by tfelwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static volatile sig_atomic_t	g_signal;

static void	ft_response(int sig)
{
	(void) sig;
	g_signal = 0;
}

static void	ft_error(const char *er_mes)
{
	ft_putstr_fd(er_mes, 2);
	exit(0);
}

static void	ft_send_message(int pid, char *message)
{
	int	count;
	int	size;
	//int	wait;

	size = (int)ft_strlen(message) + 1;
	while (size--)
	{
		count = 8;
		while (count--)
		{
			g_signal = 1;
			//wait = 0;
			if (((*message & (1 << count)) && kill(pid, SIGUSR2) < 0)
				|| (!(*message & (1 << count)) && kill(pid, SIGUSR1) < 0))
				ft_error("Error: check PID of server\n");
			while (g_signal)
			{
				//if (wait >= MAX_WAIT)
				//	ft_error("Error: waiting too long\n");
				usleep(SLEEP_TIME);
				//wait += SLEEP_TIME;
			}
		}
		++message;
	}
}

int	main(int argc, char **argv)
{
	int		pid;

	if (argc == 3)
	{
		pid = ft_strtoi(argv[1]);
		if (pid > 0)
		{
			signal(SIGUSR2, ft_response);
			ft_send_message(pid, argv[2]);
		}
		else
			ft_error("format: incorrect pid\n");
	}
	else
		ft_error("format: \n./client pid \"message\"\n");
	return (0);
}
