/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 10:49:20 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/19 19:13:35 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	DIR*	rep;
	t_file	*file;
	char	*dir;

	dir = NULL;
	if (ac > 1)
	{
		if (check_args(ac, av) == 0)
			return (1);
	}
	else
	{
		dir = ft_strdup(".");
		if ((rep = opendir(dir)) == NULL)
			return (1);
		if ((file = parse_rep(rep, dir, 0, NULL)) != NULL)
			display_file(file, 0, NULL, 0);
		ft_strdel(&dir);
	}
	return (0);
}
