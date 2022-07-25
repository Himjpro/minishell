/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:48:15 by mjafari           #+#    #+#             */
/*   Updated: 2022/07/25 21:55:57 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "./libft/libft.h"
#include <fcntl.h>

enum redirection_input_output_type
{
	e_input = 0,
	e_output = 1,
};

typedef struct s_red
{
	int id;
	int type; // in_red, out_red
	int is_apnd;
	char *f_name;
} t_red;

typedef struct s_cmd
{
	int id;
	int end_of_c;
	int cmd_n;
	int re_n;
	char *c_pre_parse;
	int pipe_flag_before;
	int pipe_flag_after;
	char *c;
	char **op;
	char *c_buf;
	// char		**re;
	int fd_in;
	int fd_out;
	t_red *re;
} t_cmd;

// first read number of redirections and malloc for the size of s_red pointer;
char **split_command(char *cb);
int cmd_num(char *cmd);
void cmd_fill(t_cmd *cmd_s, char *cmd);
void cmd_init(t_cmd *cmd, char *cmd_buff, int n);
void cmd_c(t_cmd *cmd, int n);
int cmd_count(char *c, int i, int count);
void pipe_splitter(t_cmd *t_cmd, char *cmd, int i, int j);
void dollar_with_q(t_cmd *cmd, int i, int j, int start);
void dollar_no_q(t_cmd *cmd, int i, int j, int start);
void heredoc_input(t_cmd *cmd, int i, int j, int start);
void ft_redirection(t_cmd *cmd, int i);
char *find_file_name(char *c, int *j);
void args_selector(t_cmd *cmd, int n);
int find_next_q(char *c, int q, int i);
int is_q_closed(char *c, int i);
char *remove_f_cmd_pre(char *cmd, int start, int end);
void free_cmd(t_cmd *cmd, int i);
int	is_heredoc(char *c, int j);
int	heredoc_str(t_cmd *cmd, char *first_str, int start, int j);
char	*ft_new_read(char *dlm, char *ret, int l);
int	dollar_str_env(t_cmd *cmd, int start, int *j, char *first_str);
void	no_dollar_var(t_cmd *cmd, int j, char *first_str);

#endif