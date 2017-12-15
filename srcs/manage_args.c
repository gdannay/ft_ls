/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_flag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 12:23:25 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/15 16:03:37 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"
#include "ft_printf.h"

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

int		check_args(int ac, char **av)
{
	int 			i;
	int 			flag;
	DIR				*rep;
	char			*path;
	struct dirent	*fichier;
	char			*rest;

	flag = 0;
	i = 1;
	rest = NULL;
	if (av[1][0] == '-')
		flag = check_flag(av[1]);
	if (flag < 0)
	{
		ft_printf("ls: illegal option -- %c\n", flag * -1);
		ft_printf("usage: ls [-Ralrt] [file ...]\n");
		return (0);
	}
	if (flag > 0)
		i++;
	while (i < ac)
	{
		path = manage_path(av[i], &rest);
		if ((rep = opendir(path)) == NULL)
		{
			if ((rep = opendir(".")) == NULL)
				return (0);
			fichier = readdir(rep);
			while (fichier && ft_strcmp(fichier->d_name, av[i]) != 0)
				fichier = readdir(rep);
			if (fichier == NULL)
			{
				ft_printf("ls: %s: ", av[i]);
				perror("");
			}
			else
				ft_printf("%s\n", av[i]);
		}
		else
		{


		}
		i++;
	}
	return (0);
}
