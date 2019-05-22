/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maparmar <maparmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 11:13:38 by maparmar          #+#    #+#             */
/*   Updated: 2019/05/22 12:15:38 by maparmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ssl.h"

t_mem	*ft_memjoin(t_mem *dest, t_mem *src)
{
	t_mem *ret;

	ret = (t_mem *)malloc(sizeof(t_mem));
	if (!dest)
	{
		ret->data = (unsigned char *)ft_strnew(src->len);
		ft_memcpy(ret->data, src->data, src->len);
		ret->len = src->len;
		return (ret);
	}
	ret->len = dest->len + src->len;
	ret->data = (unsigned char *)ft_strnew(ret->len);
	ft_memcpy((void*)ret->data, dest->data, dest->len);
	ft_memcpy((void*)&ret->data[dest->len], src->data, src->len);
	ft_free_mem(dest);
	return (ret);
}


void	ft_free_mem(t_mem *mem)
{
	free(mem->data);
	free(mem);
}