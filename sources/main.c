/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 20:45:11 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/10/06 17:05:48 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "parser.h"
#include "exec.h"
#include "sem.h"

t_opt		g_opt;
int			g_res_exec;
char		*g_project_name;
char		*g_shell_path;
char		**g_var;
char		**g_prefix_vars;
char		**g_var_names;
char		**g_func_defs;
t_pjobs		*g_pjobs;
t_pjobs		*g_subjob;
int			g_line_num;
int			g_eof;
int			g_wait_flags;
char		*g_tty;
int			*g_open_fd;
int			*g_pipe_pid;
t_alias		*g_alias;		/* TODO: move definitions to appropriate places */

void		main_loop(void)
{
	char		*line;
	char		*project_name;
	int			i;

	i = 0;
	project_name = ft_xstrdup(g_project_name);
	while (!g_eof)
	{
		init_sem();
		if (!(line = ft_readline((g_opt.rl_gnl == 0 ?
							get_var_value("PS1") : ""), RL_DEFAULT)))
		{
			clear_sem();
			continue ;
		}
		execute_line(line);
		clear_sem();
	}
	ft_strdel(&project_name);
}

int			main(int ac, char **av)
{
	signal_monitor();
	shell_init(ac, av);
	main_loop();
	shell_clear();
	return (g_res_exec);
}
