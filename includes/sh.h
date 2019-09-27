/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:44:12 by dwisoky           #+#    #+#             */
/*   Updated: 2019/09/27 19:06:49 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include <sys/wait.h>
# include <pwd.h>
# include "defs.h"
# include "libft.h"
# include "error.h"
# include "ast.h"
# include "hash.h"
# include "ft_readline.h"
# include "variables.h"
# include "lib_wtalea.h"
# include "xfuncs.h"
# include "jobs.h"
# include "builtins.h"
# include "expansion.h"

typedef struct	s_opt
{
	t_uint		vi_mode;
	t_uint		emacs_mode;
	t_uint		enable_color;
	t_uint		noclobber;
	t_uint		rl_in;
	t_uint		rl_out;
	t_uint		rl_gnl;
}				t_opt;

typedef struct	s_alias
{
	struct s_alias	*next;
	char			*head;
	char			*body_alias;
}				t_alias;

void			signal_monitor();
void			shell_init(int ac, char **av);
void			shell_clear(void);
void			execute_line(char *buf);

#endif
