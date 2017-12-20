/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_flag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 12:23:25 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/19 18:51:13 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		get_last(char **av, int ac, int flag)
{
	int i;
	int j;

	if (flag > 0)
		i = 2;
	else
		i = 1;
	j = 0;
	while (i < ac)
	{
		if (av[i] != NULL)
			j = i;
		i++;
	}
	return (j);
}

int		check_flag(char *str)
{
	int		i;
	int 	flag;

	i = 1;
	flag = 0;
	while (str[i] == 'l' || str[i] == 'r' || str[i] == 'R'
			|| str[i] == 't' || str[i] == 'a')
	{
		if (str[i] == 'l')
			flag = flag | F_L;
		else if (str[i] == 'r')
			flag = flag | F_R;
		else if (str[i] == 'R')
			flag = flag | F_BR;
		else if (str[i] == 't')
			flag = flag | F_T;
		else if (str[i] == 'a')
			flag = flag | F_A;
		i++;
	}
	if (str[i] != '\0')
		return (str[i] * -1);
	return (flag);
}

struct dirent	*check_file(char *path, char *file, char *error)
{

	struct dirent	*fichier;
	DIR				*rep;

	if (ft_strcmp(error, "") == 0)
	{
		ft_printf("ft_ls: fts_open: ");
		perror("");
		return (NULL);
	}
	if ((rep = opendir(path)) == NULL)
	{
		ft_printf("ft_ls: %s: ", error);
		perror("");
		return (NULL);
	}
	fichier = readdir(rep);
	while (fichier && ft_strcmp(fichier->d_name, file) != 0)
		fichier = readdir(rep);
	if (closedir(rep) == -1)
		return (NULL);
	if (fichier == NULL)
	{
		ft_printf("ft_ls: %s: ", error);
		perror("");
		return (NULL);
	}
	return (fichier);
}

static int		manage_args(char *av, int flag, int several)
{
	DIR			*rep;
	t_file		*file;
	char		*path;
	char		*rest;
	t_length	*length;

	rest = NULL;
	path = NULL;
	length = NULL;
	file = NULL;
	if (flag & F_L)
	{
		if ((length = create_l()) == NULL)
			return (0);
	}
	if (av && (rep = opendir(av)) == NULL)
	{
		if ((path = manage_path(av, &rest)) == NULL)
			return (0);
		if (check_file(path, rest, av) != NULL)
			ft_printf("%s\n", rest);
		ft_strdel(&path);
		ft_strdel(&rest);
	}
	else if (av && rep)
	{
		if (several)
			ft_printf("%s:\n", av);
		file = parse_rep(rep, av, flag, length);
		if (flag & F_BR)
			display_bigr(file, flag, length, av);
		else
			display_file(file, flag, length, 0);
	}
	return (1);
}

int		check_args(int ac, char **av)
{
	int 	i;
	int		flag;
	int		last;

	flag = 0;
	i = 1;
	while (av[i] && av[i][0] == '-')
	{
		if ((flag = flag | check_flag(av[i])) < 0)
			return (usage(flag));
		i++;
	}
	if (av[i] == NULL)
	{
		if ((manage_args(".", flag, 0)) == 0)
			return (0);
		return (1);
	}
	if (manage_error(av, flag, i, ac) == 0)
		return (0);
	i = 1;
	while (av[i][0] == '-')
		i++;
	last = get_last(av, ac, flag);
	while (i < ac)
	{
		if (manage_args(av[i], flag, ac - 3 + !(flag)) == 0)
			return (0);
		if (i < last && av[i])
			ft_printf("\n");
		i++;
	}
	return (1);
}
