/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_flag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 12:23:25 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/04 19:05:33 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		openfail(char *av)
{
	char		*path;
	char		*rest;

	rest = NULL;
	if ((path = manage_path(av, &rest)) == NULL)
		return (0);
	if (check_file(path, rest, av) != NULL)
		ft_printf("%s\n", rest);
	ft_strdel(&path);
	ft_strdel(&rest);
	return (1);
}

static int		manage_args(char *av, int flag, int several)
{
	DIR			*rep;
	t_file		*file;
	t_length	*length;

	length = NULL;
	rep = NULL;
	if (av && (rep = opendir(av)) == NULL
			&& openfail(av) == 0)
		return (0);
	else if (av && rep)
	{
		if ((flag & F_L) && (length = create_l()) == NULL)
			return (0);
		if (several)
			ft_printf("%s:\n", av);
		if ((file = parse_rep(rep, av, flag, length)) == NULL)
			return (0);
		if (flag & F_BR)
			display_bigr(file, flag, &length, av);
		else
			display_file(file, flag, &length, 0);
	}
	return (1);
}

static int		order_alpha(char **av, int ac, int i)
{
	int	index;

	index = 0;
	while (i < ac)
	{
		if (av[i] && index == 0)
			index = i;
		if (av[index] && av[i] && ft_strcmp(av[i], av[index]) < 0)
			index = i;
		i++;
	}
	return (index);
}

static int		parse_args(char **av, int ac, int flag, int i)
{
	int		j;
	int		index;

	j = i;
	index = 1;
	while ((index = order_alpha(av, ac, j)))
	{
		if (av[index] && manage_args(av[index], flag, ac - 3 + !(flag)) == 0)
			return (0);
		av[index] = NULL;
		if (get_last(av, ac))
			ft_printf("\n");
		i++;
	}
	return (1);
}

int				check_args(int ac, char **av)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (av[++i])
	{
		if (!(ft_strcmp(av[i], "")))
			return (fts_error());
	}
	i = 0;
	while (av[++i] && av[i][0] == '-' && av[i][1])
	{
		if ((flag = check_flag(av[i], flag)) < 0)
			return (usage(flag));
		av[i] = NULL;
	}
	if (av[i] == NULL)
		return (manage_args(".", flag, 0) == 0 ? 0 : 1);
	if (manage_error(av, flag, 1, ac) == 0)
		return (0);
	if (parse_args(av, ac, flag, i) == 0)
		return (0);
	return (1);
}
