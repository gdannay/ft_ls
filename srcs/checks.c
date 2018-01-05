/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 16:59:31 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/05 11:06:01 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int						get_last(char **av, int ac)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (av[i] != NULL)
			return (1);
		i++;
	}
	return (0);
}

static int				next_flag(char c)
{
	if (c == 'p')
		return (F_P);
	else if (c == 'S')
		return (F_S);
	else if (c == 'd')
		return (F_D);
	else if (c == 'a')
		return (F_A);
	return (0);
}

int						check_flag(char *str, int first)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (str[i] == 'l' || str[i] == 'r' || str[i] == 'R'
			|| str[i] == 't' || str[i] == 'a' || str[i] == 'p'
			|| str[i] == 'd' || str[i] == 'S')
	{
		if (str[i] == 'l')
			flag = flag | F_L;
		else if (str[i] == 'r')
			flag = flag | F_R;
		else if (str[i] == 'R')
			flag = flag | F_BR;
		else if (str[i] == 't')
			flag = flag | F_T;
		else
			flag = flag | next_flag(str[i]);
		i++;
	}
	if (str[i] != '\0')
		return (str[i] * -1);
	return (flag | first);
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
