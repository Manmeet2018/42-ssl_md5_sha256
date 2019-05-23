/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maparmar <maparmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 10:56:01 by maparmar          #+#    #+#             */
/*   Updated: 2019/05/23 12:45:57 by maparmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

int		Error_print(char *str)
{
	ft_putstr("usage: ");
	ft_putstr(str);
	ft_putendl(" command [command opts] [command args]");
	return (-1);
}


int		ssl_hash_num(char *hash)
{
	int i;

	i = -1;
	while (HASH_STRING[++i])
	{
		if (ft_strequ(HASH_STRING[i], hash))
			return (i);
	}
	return (-1);
}

t_opt		*add_str_arg(t_opt *opt, char *str)
{
	t_arg *arg;
	t_arg *tmp;

	arg = (t_arg*)malloc(sizeof(t_arg));
	arg->str = ft_strdup(str);
	arg->is_string = 0;
	if (opt->s)
	{
		arg->is_string = 1;
		opt->s = 0;
	}
	arg->next = NULL;
	if (opt->arg == NULL)
		opt->arg = arg;
	else
	{
		tmp = opt->arg;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = arg;
	}
	return (opt);
}

t_opt		*flag_checker(t_opt *opt, char *str)
{
	int i;
	int flag;

	i = -1;
	flag = 0;
	while (str[++i])
	{
		if (str[0] == '-' && opt->arg == NULL)
			flag = 1;
		else
			return (add_str_arg(opt, str));
		if (flag)
		{
			(str[i] == 'p') ? (opt->p = 1) : 0;
			(str[i] == 'q') ? (opt->q = 1) : 0;
			(str[i] == 'r') ? (opt->r = 1) : 0;
			(str[i] == 's') ? (opt->s = 1) : 0;
		}
	}
	return (opt);
}

t_opt		*opt_checker(t_opt *opt, char **argv)
{
	int i;

	i = 1;
	opt = (t_opt*)malloc(sizeof(t_opt));
	opt->hash_pos = ssl_hash_num(argv[1]);
	opt->p = 0;
	opt->q = 0;
	opt->r = 0;
	opt->s = 0;
	opt->arg = NULL;
	if (opt->hash_pos == -1)
	{
		ft_putendl("ft_ssl: invalid hash algorithm");
		ft_putendl("\nMessage Digest Commands:\nmd5\nsha256\n\nCipher commands:");
		exit(1);
	}
	while (argv[++i])
		opt = flag_checker(opt, argv[i]);
	return (opt);
}