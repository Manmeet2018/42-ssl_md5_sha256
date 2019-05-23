/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maparmar <maparmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 13:47:39 by maparmar          #+#    #+#             */
/*   Updated: 2019/05/23 11:26:32 by maparmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ssl.h"

int32_t h_s[64] = {
    7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17,
	22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16, 23,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15, 21,
    6, 10, 15, 21, 6, 10, 15, 21
};

int32_t h_k[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

t_mem	*padding_md5(t_mem *mem)
{
	t_mem		*msg;
	size_t		newlen;
	size_t		len;
    uint32_t	bitlen;
    int         i;
    
    i = -1;
    msg = (t_mem *)malloc(sizeof(t_mem));
    while(++i < 4)
        mem->h[i] = H_5[i];
	len = mem->len;
	bitlen = len * 8;
	newlen = len + 1;
	while (newlen % 64 != 56)
		newlen++;
	msg->data = (unsigned char *)ft_strnew(newlen + 64);
	msg->len = newlen;
	ft_memcpy(msg->data, mem->data, mem->len);
	msg->data[len] = (char)128;
	while (++len <= newlen)
		msg->data[len] = 0;
	ft_memcpy(msg->data + newlen, &bitlen, 4);
	ft_free_mem(mem);
	return (msg);
}
static void     hash_md5_solver_helper(uint32_t *f, uint32_t *g, uint32_t *M, int i)
{
    *f = *f + A + h_k[i] + M[*g];
    A = D;
    D = C;
    C = B;
    B += LROT(*f, h_s[i]);
    H_5[0] += A;
    H_5[1] += B;
    H_5[2] += C;
    H_5[3] += D;
    
}
static void     md5_hash_solver(uint32_t *M, int i)
{
    uint32_t g;
    uint32_t f;
    
    if (i < 16)
    {
        f = F(B, C, D);
        g = i;
    }
    else if( 16 <= i <= 31)
    {
        f = G(B, C, D);
        g = (5 * i + 1) % 16;
    }
    else if ( 32 <=i <= 47)
	{
		f = H(B, C, D);
		g = (3 * i + 5) % 16;
	}
	else
	{
		f = I(B , C, D);
		g = (7 * i) % 16;
    }
    hash_md5_solver_helper(&f, &g, M, i);
}


void            hash_md5(t_mem *mem)
{
	int			block_jump;
	int			i;  
    uint32_t	*M;
    int         j;

	block_jump = 0;
	while (block_jump < mem->len)
	{
        M = (uint32_t*)(mem->data + block_jump);
        i = -1;
		while (++i < 64)
            md5_hash_solver(M, i);
        j = -1;
        while(++j < 4)
            mem->h[j] += H_5[j];
        block_jump += 64;
	}
}