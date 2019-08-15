/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 19:51:08 by gmelisan          #+#    #+#             */
/*   Updated: 2019/08/15 10:15:08 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTIONS_H
# define ACTIONS_H

# include "ft_readline.h"
# include "ft_qsort.h"

# define	COMPLETION_QUERY_ITEMS		100
# define	TMP_PATH					"/tmp/42sh_tmp"

void		self_insert(t_line *line);
void		backward_delete_char(t_line *line);
void		delete_char(t_line *line);

void		forward_char(t_line *line);
void		backward_char(t_line *line);
void		forward_word(t_line *line);
void		backward_word(t_line *line);
void		forward_line(t_line *line);
void		backward_line(t_line *line);

void		history_prev(t_line *line);
void		history_next(t_line *line);

void		undo(t_line *line);

void		clear_screen(t_line *line);

void		beginning_of_line(t_line *line);
void		end_of_line(t_line *line);

void		transpose_chars(t_line *line);
void		transpose_words(t_line *line);
void		tw_trans_words(char *str, char *add, int len, t_line *line);

void		overwrite_mode(t_line *line);

void		previous_history(t_line *line);
void		next_history(t_line *line);
void		kill_line(t_line *line);
void		unix_line_discard(t_line *line);
void		unix_word_rubout(t_line *line);
void		yank(t_line *line);

void		reverse_search_history(t_line *line);
void		reset_history_search(t_line *line);
void		reset_line(t_line *line);

void		vi_command(t_line *line);
void		vi_insert_at(t_line *line);
void		vi_insert_after(t_line *line);
void		vi_insert_beginning(t_line *line);
void		vi_insert_end(t_line *line);
void		vi_insert_overwrite(t_line *line);
void		vi_beginning_of_line_nonblank(t_line *line);
void		vi_delete_to_motion(t_line *line);
void		vi_delete_to_end(t_line *line);
void		vi_clear_line(t_line *line);
void		vi_comment(t_line *line);
void		vi_vi(t_line *line);
void		vi_goto_char(t_line *line);

t_vector	get_filenames(t_line *line);
t_vector	get_variables(t_string query);
t_string	find_common_part(t_vector vec);
t_string	get_command_query(t_line *line, int *start);
t_string	get_variable_query(t_line *line, int *start);
void		show_completions(t_vector vec, void (*mod_str)(t_string *));

void		complete(t_line *line);
void		complete_filename(t_line *line);
void		possible_filename_completions(t_line *line);
void		complete_command(t_line *line);
void		possible_command_completions(t_line *line);
void		complete_variable(t_line *line);
void		possible_variable_completions(t_line *line);


#endif
