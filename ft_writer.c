/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maparmar <maparmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 12:09:18 by maparmar          #+#    #+#             */
/*   Updated: 2019/05/22 12:15:39 by maparmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ssl.h"

void	write_file_error(char *file, t_opt *opt)
{
	ft_putstr("ft_ssl: ");
	ft_putstr(HASH_STRING[opt->hash_pos]);
	ft_putstr(": ");
	ft_putstr(file);
	ft_putendl(": No such file or directory");
}

void	write_prefix(t_opt *opt, t_arg *arg)
{
	if (ft_strequ(HASH_STRING[opt->hash_pos], "md5") == 1)
		ft_putstr("MD5 (");
	if (ft_strequ(HASH_STRING[opt->hash_pos], "sha256") == 1)
		ft_putstr("SHA256 (");
	(arg->is_string) ? (ft_putchar('"')) : 0;
	ft_putstr(arg->str);
	(arg->is_string) ? (ft_putchar('"')) : 0;
	ft_putstr(") = ");
}

void	write_suffix(t_arg *arg)
{
	ft_putchar(' ');
	(arg->is_string) ? (ft_putchar('"')) : 0;
	ft_putstr(arg->str);
	(arg->is_string) ? (ft_putchar('"')) : 0;
}

void	write_output_md5(t_mem *mem)
{
	uint8_t			*p;
	int				i;
	int				y;
	char			*tmp;

	i = -1;
	while (++i < 4)
	{
		y = -1;
		p = (uint8_t *)&mem->h[i];
		while (++y < 4)
		{
			tmp = ft_itoa_base((int)p[y], 16);
			if (ft_strlen(tmp) == 1)
				ft_putchar('0');
			ft_putstr(tmp);
			ft_strdel(&tmp);
		}
	}
}

void	write_output_sha256(t_mem *mem)
{
	unsigned int	*p;
	int				i;
	int				y;
	char			*tmp;

	i = -1;
	while (++i < 8)
	{
		p = (unsigned int *)&mem->h[i];
		tmp = ft_itoa_base((uintmax_t)mem->h[i], 16);
		y = ft_strlen(tmp);
		while (y++ < 8)
			ft_putchar('0');
		ft_putstr(tmp);
		ft_strdel(&tmp);
	}
}
