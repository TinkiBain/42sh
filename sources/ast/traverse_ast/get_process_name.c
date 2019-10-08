/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_process_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 22:01:59 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/10/08 16:15:46 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*get_process_name(t_command *command)
{
	t_simple_cmd *cmd;
	char		*str;

	if ((cmd = command->simple_command))
		str = get_job_name(cmd->lex_begin, cmd->lex_end);
	else
		str = ft_strdup("subjob");
	return (str);
}
