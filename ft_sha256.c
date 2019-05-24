/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maparmar <maparmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 16:13:49 by maparmar          #+#    #+#             */
/*   Updated: 2019/05/23 17:03:13 by maparmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ssl.h"

unsigned int H_256[8];

unsigned int h_m[64] = {
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
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

// Padding for extra 0's 
t_mem	*padding_sha256(t_mem *mem)
{
	t_mem		*msg;
	size_t		newlen;
	size_t		len;
    uint32_t	bitlen;

    msg = (t_mem *)malloc(sizeof(t_mem));
	len = mem->len;
	bitlen = len * 8;
	newlen = len + 1;
	while (newlen % 64 != 56)
		newlen++;
	msg->data = (unsigned char *)ft_strnew(newlen + 64);
	msg->len = newlen;
	ft_memcpy(msg->data, mem->data, mem->len);
	msg->data[len] = (unsigned char)128;
	while (++len <= newlen)
		msg->data[len] = 0;
	ft_memcpy(msg->data + newlen, &bitlen, 8);
	ft_free_mem(mem);
	return (msg);
}

// Get block and it's size is of 64 bit.
unsigned int    *get_cell(unsigned char *offset)
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

//sha_hash_solver
static void		sha256_hash_solver(unsigned int *M, int i)
{
	unsigned int t[2];

	i = -1;
	while(++i < 64)
	{
		t[0] = H_H + BB(E_E) + CH(E_E, F_F, G_G) + h_m[i] + M[i];
		t[1] = AA(A_A) + MAJ(A_A, B_B, C_C);
		H_H = G_G;
		G_G = F_F;
		F_F = E_E;
		E_E = D_D + t[0];
		D_D = C_C;
		C_C = B_B;
		B_B = A_A;
		A_A = t[0] + t[1];
	}
}

// Digest sha_hash
static void		init_hash()
{
	H_256[0] = 0x6a09e667;
	H_256[1] = 0xbb67ae85;
	H_256[2] = 0x3c6ef372;
	H_256[3] = 0xa54ff53a;
	H_256[4] = 0x510e527f;
	H_256[5] = 0x9b05688c;
	H_256[6] = 0x1f83d9ab;
	H_256[7] = 0x5be0cd19;
}

// driver sha_hash_256
void            hash_sha256(t_mem *mem)
{
	int		    	block_jump;  
    unsigned int    *M;
    int             j;

    block_jump = 0;
	M = NULL;
	init_hash();
	while (block_jump < mem->len)
	{
        M = get_cell(mem->data + block_jump);
        sha256_hash_solver(M, block_jump);
        j = -1;
        while(++j < 8)
            mem->h[j] += H_256[j];
        block_jump += 64;
	}
}