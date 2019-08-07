/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_reset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwisoky <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 17:08:30 by dwisoky           #+#    #+#             */
/*   Updated: 2019/08/07 21:15:39 by dwisoky          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void			redir_reset(void)
{
	char		*file;
	int			fd;
	int			i;

	if (!(file = ttyname(0)))
	{
		fd = open(g_tty, O_WRONLY);
		dup2(fd, 0);
		close(fd);
	}
	else
		free(file);
	i = 0;
	while (++i <= 2)
	{
		if (!(file = ttyname(i)))
		{
			fd = open(g_tty, O_RDONLY);
			dup2(fd, i);
			close(fd);
		}
		else
			free(file);
	}
	free(g_tty);
}
