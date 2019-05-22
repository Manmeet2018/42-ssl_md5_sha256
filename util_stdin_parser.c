/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_stdin_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maparmar <maparmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 11:08:46 by maparmar          #+#    #+#             */
/*   Updated: 2019/05/22 12:15:36 by maparmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ssl.h"

t_mem	*stdin_read_fd(int fd)
{
	t_mem	*mem;
	t_mem	*buf;

	mem = NULL;
	buf = (t_mem *)malloc(sizeof(t_mem));
	buf->data = (unsigned char *)ft_strnew(BUFFER + 1);
	buf->len = 0;
	while ((buf->len = read(fd, buf->data, BUFFER)))
	{
		mem = ft_memjoin(mem, buf);
		ft_bzero(buf->data, buf->len);
		if (buf->len <= 0)
			break ;
		buf->len = 0;
	}
	if (!mem)
	{
		free(buf->data);
		buf->data = (unsigned char *)ft_strdup("\0");
		return (buf);
	}
	ft_free_mem(buf);
	return (mem);
}


void	read_stdin(t_opt *opt)
{
	t_mem *msg;

	msg = NULL;
	msg = stdin_read_fd(0);
	if (opt->p)
		ft_putstr((char *)msg->data);
	msg = s_paddings[opt->hash_pos](msg);
	s_hash_value[opt->hash_pos](msg);
	s_writer[opt->hash_pos](msg);
	ft_free_mem(msg);
	ft_putchar('\n');
}