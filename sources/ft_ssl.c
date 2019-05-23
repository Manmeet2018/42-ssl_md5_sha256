/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maparmar <maparmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 20:30:41 by maparmar          #+#    #+#             */
/*   Updated: 2019/05/23 12:54:18 by maparmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"


void	ft_hash(t_opt *opt, t_mem *msg, t_arg *arg)
{
	msg = s_paddings[opt->hash_pos](msg);
	s_hash_value[opt->hash_pos](msg);
	(!opt->r && !opt->q) ? (write_prefix(opt, arg)) : 0;
	s_writer[opt->hash_pos](msg);
	(opt->r && !opt->q) ? (write_suffix(arg)) : 0;
	ft_free_mem(msg);
	ft_putchar('\n');
}

void	handle_string(t_opt *opt, t_arg *arg)
{
	t_mem *msg;

	msg = (t_mem*)malloc(sizeof(t_mem));
	msg->data = (unsigned char*)ft_strdup(arg->str);
	arg->is_string = 1;
	msg->len = ft_strlen((char *)msg->data);
	ft_hash(opt, msg, arg);
}

void	read_args(t_opt *opt)
{
	t_arg	*arg;
	t_mem	*msg;
	int		fd;

	msg = NULL;
	arg = opt->arg;
	while (arg)
	{
		if (!arg->is_string && (fd = open(arg->str, O_RDONLY)) != -1)
		{
			msg = stdin_read_fd(fd);
			ft_hash(opt, msg, arg);
		}
		else
		{
			if (arg->is_string)
				handle_string(opt, arg);
			else
				(!opt->q) ? (write_file_error(arg->str, opt)) : 0;
		}
		arg = arg->next;
	}
}

int main(int argc, char **argv)
{
    t_opt   *opt;

    opt = NULL;
    if(argc < 2)
        return (Error_print(argv[0]));
    opt = opt_checker(opt, argv); // util_parser.c
    if (opt->p || !opt->arg)
        read_stdin(opt); // util_stdin_parser.c
    if (argc >= 3)
		read_args(opt);
	return (0);
}
