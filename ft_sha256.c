/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maparmar <maparmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 16:13:49 by maparmar          #+#    #+#             */
/*   Updated: 2019/05/30 01:39:49 by maparmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ssl.h"

unsigned int g_m[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

t_mem			*padding_sha256(t_mem *mem)
{
	t_mem		*message;
	size_t		newlen;
	size_t		len;
	uint64_t	bitlen;

	message = (t_mem *)malloc(sizeof(t_mem));
	len = mem->len;
	bitlen = len * 8;
	newlen = len + 1;
	while (newlen % 64 != 56)
		newlen++;
	message->data = (unsigned char *)malloc(sizeof(unsigned char) * newlen);
	message->len = newlen;
	memcpy(message->data, mem->data, mem->len);
	message->data[len] = (unsigned char)128;
	while (++len <= newlen)
		message->data[len] = 0;
	bitlen = swap_uint64(bitlen);
	memcpy(message->data + newlen, &bitlen, 8);
	ft_free_mem(mem);
	return (message);
}

void			sha256_hash_solver_helper(t_a *a, unsigned int *w, int i)
{
	H_T = H_H_H + BB(E_E) + CH(E_E, F_F, G_G) + g_m[i] + w[i];
	H_T_T = AA(A_A) + MAJ(A_A, B_B, C_C);
	H_H_H = G_G;
	G_G = F_F;
	F_F = E_E;
	E_E = D_D + H_T;
	D_D = C_C;
	C_C = B_B;
	B_B = A_A;
	A_A = H_T + H_T_T;
}

unsigned int	*get_cell(unsigned char *offset)
{
	int				i;
	unsigned int	*w;

	i = -1;
	w = (unsigned int *)malloc(sizeof(unsigned int) * 64);
	while (++i < 64)
	{
		if (i < 16)
			w[i] = (offset[i * 4] << 24) |
				(offset[i * 4 + 1] << 16) |
				(offset[i * 4 + 2] << 8) |
				(offset[i * 4 + 3]);
		else
			w[i] = DD(w[i - 2]) + w[i - 7] + CC(w[i - 15]) + w[i - 16];
	}
	return (w);
}

void			sha256_hash_solver(t_a *a, unsigned int *w, t_mem *mem)
{
	int				i;

	i = -1;
	(*a).g_a = mem->h[0];
	(*a).g_b = mem->h[1];
	(*a).g_c = mem->h[2];
	(*a).g_d = mem->h[3];
	(*a).g_e = mem->h[4];
	(*a).g_f = mem->h[5];
	(*a).g_g = mem->h[6];
	(*a).g_h = mem->h[7];
	while (++i < 64)
		sha256_hash_solver_helper(a, w, i);
}

void			hash_sha256(t_mem *mem)
{
	int				block_jump;
	unsigned int	*w;
	t_a				a;

	block_jump = 0;
	w = NULL;
	init_hash_mem(mem);
	while (block_jump < mem->len)
	{
		w = get_cell(mem->data + block_jump);
		sha256_hash_solver(&a, w, mem);
		mem->h[0] += a.g_a;
		mem->h[1] += a.g_b;
		mem->h[2] += a.g_c;
		mem->h[3] += a.g_d;
		mem->h[4] += a.g_e;
		mem->h[5] += a.g_f;
		mem->h[6] += a.g_g;
		mem->h[7] += a.g_h;
		block_jump += 64;
	}
}
