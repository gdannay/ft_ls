/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 10:49:20 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/18 10:41:21 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_printf.h"
#include "libft.h"

int		main(int ac, char **av)
{
	DIR*	rep;
	t_file	*file;
	char	*dir;

	dir = NULL;
	if (ac > 1)
	{
		if (check_args(ac, av) == 0)
			return (0);
	}
	else
	{
		dir = ft_strdup(".");
		if ((rep = opendir(dir)) == NULL)
			return (0);
		file = parse_rep(rep, dir, 0, NULL);
		display_file(file, 0, NULL, 0);
		if (closedir(rep) == -1)
			return (0);
	}
}
