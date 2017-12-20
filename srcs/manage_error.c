/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 12:06:20 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/19 18:22:50 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		usage(int flag)
{
	ft_printf("ls: illegal option -- %c\n", flag * -1);
	write(2, "usage: ls [-Ralrt] [file ...]\n", 30);
	return (0);
}

int		manage_error(char **av, int flag, int i, int ac)
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
			return (0);
	}
	while (++i < ac)
	{
		if ((rep = opendir(av[i])) == NULL)
		{
			if ((path = manage_path(av[i], &rest)) == NULL)
				return (0);
			if ((fichier = check_file(path, rest, av[i])) == NULL)
			{
				if (ft_strcmp(rest, "") == 0)
				{
					return (0);
				}
				av[i] = NULL;
			}
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
					return (0);
				compute_length(length, tmp);
				av[i] = NULL;
			}
			ft_strdel(&path);
			ft_strdel(&rest);
		}
		else if (rep && closedir(rep) == -1)
			return (0);
	}
	if (flag & F_L && file)
	{
		display_file(file, flag, length, 1);
		if (get_last(av, ac, flag) != 0)
			ft_printf("\n");
	}
	if (flag & F_L)
		free(length);
	return (1);
}
