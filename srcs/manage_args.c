/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_flag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 12:23:25 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/16 17:24:47 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_printf.h"

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

	if ((rep = opendir(path)) == NULL)
	{
		ft_printf("ls: %s: ", error);
		perror("");
		return (NULL);
	}
	fichier = readdir(rep);
	while (fichier && ft_strcmp(fichier->d_name, file) != 0)
		fichier = readdir(rep);
	if (fichier == NULL)
	{
		ft_printf("ls: %s: ", error);
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
	else if (av && (rep = opendir(av)) != NULL)
	{
		if (several)
			ft_printf("%s:\n", av);
		file = parse_rep(rep, av, flag, length);
		display_file(file, flag, length);
		if (closedir(rep) == -1)
			return (0);
	}
	return (1);
}

int		check_args(int ac, char **av)
{
	int 	i;
	int		flag;
	int		last;

	flag = 0;
	i = 0;
	if (av[1][0] == '-')
	{
		if ((flag = check_flag(av[1])) < 0)
			return (usage(flag));
	}
	if (flag > 0)
		i++;
	if (ac == 2 && flag > 0)
	{
		if (manage_args(".", flag, 0) == 0)
			return (0);
	}
	manage_error(av, flag, i, ac);
	i = 1;
	if (flag > 0)
		i++;
//	if (flag & F_L)
//		print_files(&(av), ac, i);
	last = get_last(av, ac, flag);
	while (i < ac)
	{
		if (manage_args(av[i], flag, ac - 3 + !(flag)) == 0)
			return (0);
		if (i < last && av[i])
			printf("\n");
		i++;
	}
	return (0);
}
