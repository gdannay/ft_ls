/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 18:25:50 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/15 20:34:21 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include "ft_printf.h"

static int		timecmp(t_file *tmp, t_file *comp, int rev)
{
	return ((tmp->mtime - comp->mtime) * rev);
}

static int		namecmp(t_file *tmp, t_file *comp, int rev)
{
	return (ft_strcmp(comp->name, tmp->name) * rev);
}

static void		display_f(t_file **file, int(*f)(t_file*, t_file*, int), int rev, int flag)
{
	t_file	*tmp;
	t_file	*comp;

	flag = 0;
	tmp = *file;
	comp = NULL;
	if (tmp)
		comp = tmp->next;
	while (comp)
	{
		if ((*f)(tmp, comp, rev) < 0)
			tmp = comp;
		comp = comp->next;
	}
//	if (flag & F_R)
//		print_det(tmp);
//	else
		ft_printf("%s\n", tmp->name);
	delete_file(file, tmp);
}

int		display_file(t_file *file, int flag)
{
	int		size;
	int		j;
	t_file	*tmp;
	int		rev;

	j = 0;
	if (flag & F_R)
		rev = -1;
	else
		rev = 1;
	tmp = file;
	size = lstlen(file);
	while (j < size)
	{
		if (flag & F_T)
			display_f(&file, &timecmp, rev, flag);
		else
			display_f(&file, &namecmp, rev, flag);
		j++;
	}	
	return (0);
}