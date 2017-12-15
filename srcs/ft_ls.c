/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 10:49:20 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/15 20:02:07 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
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
		file = parse_rep(rep, dir, 0);
		if (closedir(rep) == -1)
			return (0);
	}
/*	while (file)
	{
		printf("Name = %.8s\t", file->name);
		printf("grp_name =  %s\t", file->grp_name);
		printf("pw_name =  %s\t", file->pw_name);
		printf("Time =  %s\t", ctime(&(file->mtime)));
		printf("Size = %d\t", file->size);
		printf("Links = %d\t", file->links);
		printf("Protec = %d\n", file->protec);
		file = file->next;
	}*/
}
