/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_pipe_sequence.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterry <jterry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:46:45 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/09/08 16:46:25 by jterry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

extern char	**g_var;

static char		*get_cmd_name(t_simple_cmd *cmd)
{
	if (cmd->cmd_pref)
	{
		if (cmd->cmd_word)
		{
			cmd->cmd_word = tdq(cmd->cmd_word);
			return (cmd->cmd_word);
		}
	}
	else
	{
		cmd->cmd_name = tdq(cmd->cmd_name);
		return (cmd->cmd_name);
	}
	return (NULL);
}

static void		handle_last_cmd_in_pipe(int fd, t_simple_cmd *cmd, char **env,
															int in_fork)
{
	pid_t		pid2;

	if ((pid2 = fork()) == 0)
	{
		dup2(fd, 0);
		close(fd);
		get_cmd_name(cmd);
		traverse_cmd(cmd, env, in_fork);
		exit(g_res_exec);
	}
	waitpid(pid2, &g_res_exec, 0);
}

static void		ast_handle_pipe(t_pipe_sequence *pipe_seq, int fd, char **env,
															int in_fork)
{
	extern char	**environ;
	pid_t		pid;
	int			pipefd[2];

	if (pipe(pipefd) == -1)
		exit(-1);
	if ((pid = fork()) == 0)
	{
		close(pipefd[0]);
		dup2(fd, 0);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		get_cmd_name(pipe_seq->command->simple_command);
		traverse_cmd(pipe_seq->command->simple_command, environ, in_fork);
		exit(g_res_exec);
	}
	close(pipefd[1]);
	pipe_seq = pipe_seq->next;
	if (pipe_seq->next)
		ast_handle_pipe(pipe_seq, pipefd[0], environ, in_fork);
	else
		handle_last_cmd_in_pipe(pipefd[0], pipe_seq->command->simple_command,
															env, in_fork);
	close(pipefd[0]);
	waitpid(pid, NULL, 0);
}

void		traverse_pipe_sequence(t_pipe_sequence *pipe_seq, char **env, t_pjobs *local)
{
	pid_t		pid;
	char		*cmd_name;
	int			flag;

	if (pipe_seq->next)
		ast_handle_pipe(pipe_seq, 0, env, 1);
	else
	{
		if ((cmd_name = get_cmd_name(pipe_seq->command->simple_command)))
		{
			if (is_builtin(cmd_name))
			{
				if (local->flag == 0)
					deletejob(&g_subjob, g_subjob->num);
				traverse_cmd(pipe_seq->command->simple_command, env, 0);
			}
			else if ((flag = check_cmd(cmd_name)) == 0)
			{
				hash_add_count(cmd_name);
				if ((pid = fork()) == 0)
				{
					if (local->flag == 1)
						setpgrp();
					traverse_cmd(pipe_seq->command->simple_command, env, 1);
				}
				else
				{
					ljobs_startet("name", local->flag, local->num, pid);
					if (local->flag == 0)
						ft_waitpid(pid);
					else
						ft_printf("[%d] [%d]\n", local->num, pid);
				}
			}
			else
			{
				printf ("");
				if (local->flag == 0)
					deletejob(&g_subjob, g_subjob->num);
				else
					deletejob(&g_pjobs, local->num);
			}
		}
		else
			traverse_cmd(pipe_seq->command->simple_command, env, 1);
	}
}