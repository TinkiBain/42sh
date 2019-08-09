/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errno.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 10:11:35 by gmelisan          #+#    #+#             */
/*   Updated: 2019/08/09 15:16:16 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_errno.h"

int		g_errno = 0;

static void	print(char *msg)
{
	ft_fdprintf(STDERR, PROJECT_NAME ": ");
	if (g_errinfo[0])
		ft_fdprintf(STDERR, "%s: ", g_errinfo);
	ft_fdprintf(STDERR, "%s\n", msg);
	if (g_errinfo[0])
		loginfo("%s (\"%s\")", msg, g_errinfo);
}

void	fatal(char *msg)
{
	extern int	g_logfd;

	term_restore();
	ft_putstr_fd(PROJECT_NAME ": Fatal error: ", STDERR);
	ft_putstr_fd(msg, STDERR);
	ft_putstr_fd("\n", STDERR);
	if (DEBUG && g_logfd >= 0)
	{
		ft_putstr_fd("Fatal error: ", g_logfd);
		ft_putstr_fd(msg, g_logfd);
		ft_putstr_fd("\n", g_logfd);
	}
	exit(-1);
}

void	printerr(void)
{
	if (!g_errno)
		return ;
	if (g_errno == ERROR_READ)
		print("Read error");
	else if (g_errno == ERROR_KEYBUF_OF)
		print("Key buffer overflow");
	else if (g_errno == ERROR_TERMCAP)
		print("Termcap error");
	else if (g_errno == ERROR_UNK_TERMTYPE)
		print("Unknown terminal");	
}
