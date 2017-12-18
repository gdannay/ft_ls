/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 12:06:20 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/16 17:47:12 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_printf.h"
#include "libft.h"

int		usage(int flag)
{
	ft_printf("ls: illegal option -- %c\n", flag * -1);
	ft_printf("usage: ls [-Ralrt] [file ...]\n");
	return (0);
}

void	manage_error(char **av, int flag, int i, int ac)
{
	DIR				*rep;
	char			*path;
	char			*rest;
	struct dirent	*fichier;
	t_file			*file;
	t_file			*tmp;
	t_length		*length;

	rest = NULL;
	path = NULL;
	file = NULL;
	if (flag & F_L)
	{
		if ((length = create_l()) == NULL)
			return;
	}
	while (++i < ac)
	{
		if ((rep = opendir(av[i])) == NULL)
		{
			if ((path = manage_path(av[i], &rest)) == NULL)
				return;
			if ((fichier = check_file(path, rest, av[i])) == NULL)
				av[i] = NULL;
			else if (flag & F_L)
			{
				if (file == NULL)
				{
					file = get_file(fichier, file, path, flag);
					tmp = file;
				}
				else
					tmp = get_file(fichier, tmp, path, flag);
				if (tmp == NULL)
					return;
				compute_length(length, tmp);
				av[i] = NULL;
			}
			ft_strdel(&path);
			ft_strdel(&rest);
		}
	}
	if (flag & F_L && file)
	{
		display_file(file, flag, length);
		if (get_last(av, ac, flag) != 0)
			ft_printf("\n");
	}
}
