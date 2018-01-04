/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 16:59:31 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/04 16:58:25 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int						get_last(char **av, int ac, int flag)
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

int						check_flag(char *str)
{
	int	i;
	int	flag;

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

int						fts_error(void)
{
	ft_printf("ft_ls: fts_open: No such file or directory\n");
	return (0);
}

struct dirent			*check_file(char *path, char *file, char *error)
{
	struct dirent	*fichier;
	DIR				*rep;

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
