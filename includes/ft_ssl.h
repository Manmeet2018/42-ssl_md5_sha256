/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maparmar <maparmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 20:30:39 by maparmar          #+#    #+#             */
/*   Updated: 2019/05/22 12:15:41 by maparmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdint.h>
# include <stdio.h>
# include "../libft/libft.h"
# include <errno.h>
# include <string.h>
# include <fcntl.h>

# define HASH_STRING (const char*[3]){"md5", "sha256", "NULL"}
# define BUFFER 2048
typedef struct		s_arg
{
	char			*str;
	int				is_string;
	struct s_arg	*next;
}					t_arg;


typedef struct		s_opt
{
	int				hash_pos;
	t_arg			*arg;
	int				p;
	int				q;
	int				r;
	int				s;
}					t_opt;

typedef struct		s_mem
{
	unsigned char	*data;
	unsigned int	h[8];
	int				len;
}					t_mem;

typedef t_mem		*(*t_padding)(t_mem *mem);
typedef void		(*t_hash)(t_mem *mem);
typedef void		(*t_print)(t_mem *mem);

t_padding		s_paddings[] = {padding, padding_sha256};
t_hash			s_hash_value[] = {hash_md5, hash_sha256};
t_print			s_writer[] = {write_output_md5, write_output_sha256};

int		Error_print(char *str);
t_opt	*opt_checker(t_opt *opt, char **argv);
t_mem	*stdin_read_fd(int fd);
void	read_stdin(t_opt *opt);
t_mem	*ft_memjoin(t_mem *dest, t_mem *src);
void	ft_free_mem(t_mem *mem);

# endif