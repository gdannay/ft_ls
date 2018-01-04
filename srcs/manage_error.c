/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 12:06:20 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/04 14:31:47 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				usage(int flag)
{
	ft_printf("ls: illegal option -- %c\n", flag * -1);
	write(2, "usage: ls [-Ralrt] [file ...]\n", 30);
	return (0);
}

static int		manage_fail(char **av, int flag, t_file **file, t_file **tmp)
{
	struct dirent	*fichier;
	char			*path;
	char			*rest;

	fichier = NULL;
	if ((path = manage_path(*av, &rest)) == NULL)
		return (0);
	if ((fichier = check_file(path, rest, *av)) == NULL)
		*av = NULL;
	else if (flag & F_L)
	{
		*tmp = get_file(fichier, *tmp, path, flag);
		if (*file == NULL)
			*file = *tmp;
		if (*tmp == NULL)
		{
			ft_strdel(&path);
			ft_strdel(&rest);
			return (0);
		}
		*av = NULL;
	}
	ft_strdel(&path);
	ft_strdel(&rest);
	return (1);
}

static void		print_det_files(t_file *file, int flag,
		t_length **length, int last)
{
	display_file(file, flag, length, 1);
	if (last != 0)
		ft_printf("\n");
}

int				manage_error(char **av, int flag, int i, int ac)
{
	DIR				*rep;
	t_file			*file;
	t_file			*tmp;
	t_length		*length;

	file = NULL;
	length = NULL;
	if ((flag & F_L) && (length = create_l()) == NULL)
		return (0);
	while (++i < ac)
	{
		if ((rep = opendir(av[i])) == NULL
				&& manage_fail(&(av[i]), flag, &file, &tmp) == 0)
			return (0);
		if (rep == NULL && (flag & F_L))
			compute_length(length, tmp);
		else if (rep && closedir(rep) == -1)
			return (0);
	}
	if ((flag & F_L) && file)
		print_det_files(file, flag, &length, get_last(av, ac, flag));
	if (length)
		free(length);
	return (1);
}
