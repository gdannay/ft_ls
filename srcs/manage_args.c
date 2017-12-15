/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_flag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 12:23:25 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/15 21:09:50 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"
#include "ft_printf.h"

static int	usage(int flag)
{
	ft_printf("ls: illegal option -- %c\n", flag * -1);
	ft_printf("usage: ls [-Ralrt] [file ...]\n");
	return (0);
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

static int		check_file(char *path, char *file, char *error, int check)
{

	struct dirent	*fichier;
	DIR				*rep;

	if ((rep = opendir(path)) == NULL)
	{
		ft_printf("ls: %s: ", error);
		perror("");
		return (1);
	}
	fichier = readdir(rep);
	while (fichier && ft_strcmp(fichier->d_name, file) != 0)
		fichier = readdir(rep);
	if (fichier == NULL)
	{
		ft_printf("ls: %s: ", error);
		perror("");
		return (1);
	}
	else if (fichier && !(check))
		ft_printf("%s\n\n", file);
	return (0);
}

static void		manage_args(char *av, int flag)
{
	DIR			*rep;
	t_file		*file;
	char		*path;
	char		*rest;

	if (av && (rep = opendir(av)) == NULL)
	{
		path = manage_path(av, &rest);
		check_file(path, rest, av, 0);
	}
	if (av && (rep = opendir(av)) != NULL)
	{
		ft_printf("%s:\n", av);
		file = parse_rep(rep, av, flag);
		display_file(file, flag);
		if (closedir(rep) == -1)
			return;
		printf("\n");
	}
}

static void		manage_error(char **av)
{
	DIR		*rep;
	char	*path;
	char	*rest;

	rest = NULL;
	if ((rep = opendir(*av)) == NULL)
	{
		path = manage_path(*av, &rest);
		if (check_file(path, rest, *av, 1))
			*av = NULL;
	}
}

int		check_args(int ac, char **av)
{
	int 	i;
	int		flag;

	flag = 0;
	i = 0;
	if (av[1][0] == '-')
	{
		if ((flag = check_flag(av[1])) < 0)
			return (usage(flag));
	}
	if (flag > 0)
		i++;
	while (++i < ac)
		manage_error(&(av[i]));
	i = 1;
	if (flag > 0)
		i++;
	while (i < ac)
	{
		manage_args(av[i], flag);
		i++;
	}
	return (0);
}
