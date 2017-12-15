/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_flag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 12:23:25 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/15 20:02:18 by gdannay          ###   ########.fr       */
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

static void		check_file(char *path, char *file, char *error)
{

	struct dirent	*fichier;
	DIR				*rep;

	if ((rep = opendir(path)) == NULL)
	{
		ft_printf("ls: %s: ", error);
		perror("");
		return;
	}
	fichier = readdir(rep);
	while (fichier && ft_strcmp(fichier->d_name, file) != 0)
		fichier = readdir(rep);
	if (fichier == NULL)
	{
		ft_printf("ls: %s: ", error);
		perror("");
	}
	else
		ft_printf("%s\n", file);
}

static void		manage_args(char *av, int flag)
{
	DIR			*rep;
	char		*path;
	char		*rest;
	t_file		*file;

	rest = NULL;
	(void)flag;
	if ((rep = opendir(av)) == NULL)
	{
		path = manage_path(av, &rest);
		check_file(path, rest, av);
	}
	else
	{
		file = parse_rep(rep, av, flag);
		display_file(file, flag);
		if (closedir(rep) == -1)
			return;
	}
}

int		check_args(int ac, char **av)
{
	int 	i;
	int		flag;

	flag = 0;
	i = 1;
	if (av[1][0] == '-')
	{
		if ((flag = check_flag(av[1])) < 0)
			return (usage(flag));
	}
	if (flag > 0)
		i++;
	while (i < ac)
	{
		manage_args(av[i], flag);
		i++;
	}
	return (0);
}
