/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maparmar <maparmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 20:30:39 by maparmar          #+#    #+#             */
/*   Updated: 2019/05/29 18:41:40 by maparmar         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>

# define HASH_STRING (const char*[3]){"md5", "sha256", "NULL"}
# define BUFFER 1024
# define F(b, c, d) ((b & c) | (~(b) & d))
# define G(B, C, D) ((B & D) | (C & ~D))
# define H(B, C, D) (B ^ C ^ D)
# define I(B, C, D) (C ^ (B | ~D))
# define LROT(x, c) (((x) << (c)) | ((x) >> (32 - (c))))
# define RROT(x, c) (((x) >> (c)) | ((x) << (32 - (c))))
# define A H_5[0]
# define B H_5[1]
# define C H_5[2]
# define D H_5[3]
# define CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
# define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
# define SHR(x, n) ((x) >> n)
# define AA(x) (RROT(x, 2) ^ RROT(x, 13) ^ RROT(x, 22))
# define BB(x) (RROT(x, 6) ^ RROT(x, 11) ^ RROT(x, 25))
# define CC(x) (RROT(x, 7) ^ RROT(x, 18) ^ SHR(x, 3))
# define DD(x) (RROT(x, 17) ^ RROT(x, 19) ^ SHR(x, 10))

typedef struct		s_a_256
{
	unsigned int	H_A;
	unsigned int	H_B;
	unsigned int	H_C;
	unsigned int	H_D;
	unsigned int	H_E;
	unsigned int	H_F;
	unsigned int	H_G;
	unsigned int	H_H;
	unsigned int	t[2];
}					h_a;

typedef struct		s_arg
{
	char			*str;
	int				is_string;
	struct s_arg	*next;
}					t_arg;


typedef struct		s_opt
{
	int				hash_pos;
	struct s_arg	*arg;
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

typedef t_mem			*(*t_padding)(t_mem *mem);
typedef void			(*t_hash)(t_mem *mem);
typedef void			(*t_print)(t_mem *mem);

// Fuctions Prototype
int			Error_print(char *str);
t_opt		*opt_checker(t_opt *opt, char **argv);
t_mem		*stdin_read_fd(int fd);
void		read_stdin(t_opt *opt);
t_mem		*ft_memjoin(t_mem *dest, t_mem *src);
void		ft_free_mem(t_mem *mem);
void		hash_md5(t_mem *mem);
t_mem		*padding_md5(t_mem *mem);
void		write_file_error(char *file, t_opt *opt);
void		write_prefix(t_opt *opt, t_arg *arg);
void		write_suffix(t_arg *arg);
void		write_md5(t_mem *mem);
void		write_sha256(t_mem *mem);
void		hash_sha256(t_mem *mem);
t_mem		*padding_sha256(t_mem *mem);
char		*ft_itoa_base(intmax_t n, int base);
uint64_t	swap_uint64(uint64_t val);

// main struct for all operation
# endif