/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfelwood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 05:17:48 by tfelwood          #+#    #+#             */
/*   Updated: 2022/03/04 05:29:52 by tfelwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# define SLEEP_TIME 5
# define MAX_WAIT   10000

typedef struct s_message
{
	char	*text;
	int		size;
	char	symb;
	int		count;
	int		last_pid;
}	t_message;

size_t	ft_strlen(const char *s);
void	ft_putstr_fd(const char *s, int fd);
void	ft_rec_putnbr(long long n, int fd);
void	*ft_memset(void *b, int c, size_t len);
int		ft_addchar(t_message *message);
int		ft_strtoi(const char *str);
#endif
