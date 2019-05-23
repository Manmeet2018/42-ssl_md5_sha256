/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maparmar <maparmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 20:30:39 by maparmar          #+#    #+#             */
/*   Updated: 2019/05/23 11:33:00 by maparmar         ###   ########.fr       */
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
# define BUFFER 128
# define F(b, c, d) ((b & c) | (~(b) & d))
# define G(B, C, D) ((B & D) | (C & ~D))
# define H(B, C, D) (B ^ C ^ D)
# define I(B, C, D) (C ^ (B | ~D))
# define LROT(x, c) (((x) << (c)) | ((x) >> (32 - (c))))
# define RROT(x, c) (((x) >> (c)) | ((x) >> (32 - (c))))
# define A H_5[0]
# define B H_5[1]
# define C H_5[2]
# define D H_5[3]
# define CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
# define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
# define SHR(x, n) ((x) >> n)
# define ROTR(x, n) (((x) >> (n)) | ((x) << (32 - (n))))
# define AA(x) (ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22))
# define BB(x) (ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25))
# define CC(x) (ROTR(x, 7) ^ ROTR(x, 18) ^ SHR(x, 3))
# define DD(x) (ROTR(x, 17) ^ ROTR(x, 19) ^ SHR(x, 10))
# define A_ H_256[0]
# define B_ H_256[1]
# define C_ H_256[2]
# define D_ H_256[3]
# define E_ H_256[4]
# define F_ H_256[5]
# define G_ H_256[6]
# define H_ H_256[7]

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


typedef t_mem			*(*t_padding)(t_mem *mem);
typedef void			(*t_hash)(t_mem *mem);
typedef void			(*t_print)(t_mem *mem);
unsigned int			H_5[4];
unsigned int			H_256[8];
//typedef unsigned 	Digest_sha256[4];

// main struct for all operation
t_padding		s_paddings[] = {padding_md5, padding_sha256};
t_hash			s_hash_value[] = {hash_md5, hash_sha256};
t_print			s_writer[] = {write_md5, write_sha256};

// digest for md5 & sha256
H_5 = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476 };
H_256 = {
	0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
	0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
};


// Fuctions Prototype
int		Error_print(char *str);
t_opt	*opt_checker(t_opt *opt, char **argv);
t_mem	*stdin_read_fd(int fd);
void	read_stdin(t_opt *opt);
t_mem	*ft_memjoin(t_mem *dest, t_mem *src);
void	ft_free_mem(t_mem *mem);
void	hash_md5(t_mem *mem);
t_mem	*padding_md5(t_mem *mem);
void	write_file_error(char *file, t_opt *opt);
void	write_prefix(t_opt *opt, t_arg *arg);
void	write_suffix(t_arg *arg);
void	write_md5(t_mem *mem);
void	write_sha256(t_mem *mem);
void	hash_sha256(t_mem *mem);
t_mem	*padding_sha256(t_mem *mem);
char	*ft_itoa_base(intmax_t n, int base);
# endif