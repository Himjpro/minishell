/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 19:57:21 by mjafari           #+#    #+#             */
/*   Updated: 2022/07/26 12:46:12 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_file_name(char *c, int *j)
{
	int	start;
	int	end;

	while (c[*j] == ' ')
		(*j)++;
	start = *j;
	while (c[*j] && !ft_strchr("< >|", c[*j]))
		(*j)++;
	end = *j;
	return (ft_substr(c, start, end - start));
}

void	update_append_re_vars(t_cmd *cmd, int *id, int *j, int start)
{
	cmd->re[*id].id = *id;
	cmd->re[*id].type = 1;
	cmd->re[*id].is_apnd = 1;
	cmd->re[*id].f_name = find_file_name(cmd->c_pre_parse, j);
	cmd->c_pre_parse = remove_f_cmd_pre(cmd->c_pre_parse, start, *j - 1);
	(*id)++;
	*j = -1;
}

void	update_in_out_re_vars(t_cmd *cmd, int *id, int *j, int start)
{
	cmd->re[*id].id = *id;
	cmd->re[*id].type = 1;
	if (cmd->c_pre_parse[*j - 1] == '<')
		cmd->re[*id].type = 0;
	cmd->re[*id].is_apnd = 0;
	cmd->re[*id].f_name = find_file_name(cmd->c_pre_parse, j);
	cmd->c_pre_parse = remove_f_cmd_pre(cmd->c_pre_parse, start, *j - 1);
	(*id)++;
	*j = -1;
}

void	init_cmd_re(t_cmd *cmd, int i, int j, int id)
{
	int	start;

	while (i < cmd->re_n)
	{
		id = 0;
		while (cmd->c_pre_parse[j])
		{
			if (cmd->c_pre_parse[j] == '\'' || cmd->c_pre_parse[j] == '"')
				j = find_next_q(cmd->c_pre_parse, cmd->c_pre_parse[j], j);
			else if (is_output_append(cmd->c_pre_parse, j))
			{
				start = j - 1;
				j += 2;
				update_append_re_vars(cmd, &id, &j, start);
			}
			else if (is_in_or_out_re(cmd->c_pre_parse, j))
			{
				start = j - 1;
				j++;
				update_in_out_re_vars(cmd, &id, &j, start);
			}
			j++;
		}
		i++;
	}
}

void	redirection(t_cmd *cmd, int i)
{
	while (i < cmd[0].cmd_n)
	{
		cmd[i].re_n = read_n_re(&cmd[i], 0, 0);
		cmd[i].re = (t_red *)malloc(cmd[i].re_n * sizeof(t_red));
		init_cmd_re(&cmd[i], 0, 0, 0);
		// for (size_t j = 0; j < cmd[i].re_n; j++)
		// {
		// 	printf("id = %d type = %d is_append = %d, file_name= %s\n",
		// 		   cmd[i].re[j].id, cmd[i].re[j].type, cmd[i].re[j].is_apnd, cmd[i].re[j].f_name);
		// }
		// i++;
	}
}
