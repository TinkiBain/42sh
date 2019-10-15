/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterry <jterry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 01:24:52 by gmelisan          #+#    #+#             */
/*   Updated: 2019/10/15 22:10:01 by jterry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "parser.h"
#include "builtins.h"

t_opt				g_opt;
int					g_res_exec;
char				*g_project_name;
char				*g_shell_path;
char				**g_var;
char				**g_prefix_vars;
char				**g_var_names;
t_pjobs				*g_pjobs;
t_pjobs				*g_subjob;
int					g_line_num;
int					g_eof;
int					g_wait_flags;
char				*g_tty;
char				*g_tty_name;
int					*g_open_fd;
int					*g_pipe_pid;
t_alias				*g_alias;
t_dict				*g_func_defs;
int					g_open;

void				preliminary_check_fd(void)
{
	extern char		*g_tty_name;
	extern t_opt	g_opt;

	if (fcntl(0, F_GETFL) < -1)
		exit(0);
	if (!isatty(0))
	{
		if (g_opt.vi_mode || g_opt.emacs_mode)
		{
			g_opt.vi_mode = 0;
			g_opt.emacs_mode = 0;
			g_opt.rl_gnl = 1;
		}
	}
	g_tty_name = ttyname(0);
	g_open = open(g_tty_name, O_RDWR);
}

static void			fill_options(int rl_in)
{
	extern t_opt	g_opt;

	g_opt.enable_color = 1;
	g_opt.noclobber = 1;
	g_opt.vi_mode = 0;
	g_opt.history = 1;
	g_opt.emacs_mode = (rl_in == 0 ? 1 : 0);
	g_opt.rl_in = rl_in;
	g_opt.rl_out = STDERR;
}

int					check_binary(char *path)
{
	int			fd;
	t_uint		magic;

	magic = 0;
	fd = open(path, O_RDONLY, S_IRWXU);
	read(fd, &magic, sizeof(magic));
	close(fd);
	if (magic == MH_MAGIC || magic == MH_MAGIC_64)
	{
		print_error(path, "cannot execute binary file");
		return (1);
	}
	return (0);
}

static int			get_fd(int ac, char **av)
{
	extern char		*g_project_name;
	extern t_opt	g_opt;
	char			*p;
	int				fd;

	p = (av[0]) ? ft_strrchr(av[0], '/') : NULL;
	g_project_name = ft_xstrdup((p) ? (p + 1) : av[0]);
	fd = -1;
	if (ac > 1)
	{
		if (check_file_errors(av[1], F_OK) || check_binary(av[1]) ||
							(fd = open(av[1], O_RDONLY)) < 0)
			exit(g_res_exec);
	}
	if (fd > -1)
	{
		ft_strdel(&g_project_name);
		g_project_name = ft_xstrdup(av[1]);
		g_opt.rl_gnl = 1;
		return (fd);
	}
	return (0);
}

void				shell_init(int ac, char **av)
{
	extern char		**environ;
	extern t_alias	*g_alias;
	int				fd;

	fd = get_fd(ac, av);
	g_alias = NULL;
	fill_options(fd);
	preliminary_check_fd();
	environ = create_copy_env(environ);
	init_g_var();
	g_shell_path = ft_xstrjoin(get_var_value("SHELLHOME"), "/");
	g_shell_path = ft_xstrrejoin(g_shell_path, g_project_name, 1);
	fill_g_var_names();
	fill_hash_table();
	logopen();
	g_history = ft_xmemalloc(sizeof(t_history));
	g_history->start_index = 1;
	history_load(g_history);
	init_g_func_defs();
}
