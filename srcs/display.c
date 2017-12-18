/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 18:25:50 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/18 13:21:37 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_printf.h"
#include "libft.h"

static int		timecmp(t_file *tmp, t_file *comp, int rev)
{
	return ((tmp->mtime - comp->mtime) * rev);
}

static int		namecmp(t_file *tmp, t_file *comp, int rev)
{
	return (ft_strcmp(comp->name, tmp->name) * rev);
}

static void		display_f(t_file **file, int(*f)(t_file*, t_file*, int), int rev, t_length *length)
{
	t_file	*tmp;
	t_file	*comp;

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
	if (length)
		print_det(tmp, length);
	else
		ft_printf("%s\n", tmp->name);
	delete_file(file, tmp);
}

int		display_file(t_file *file, int flag, t_length *length, int files)
{
	int		size;
	int		j;
	int		rev;

	j = 0;
	if (flag & F_R)
		rev = -1;
	else
		rev = 1;
	size = lstlen(file);
	files = 0;
	if (flag & F_L && !(files) && length)
		ft_printf("total %d\n", length->blocks);
	while (j < size)
	{
		if (flag & F_T)
			display_f(&file, &timecmp, rev, length);
		else
			display_f(&file, &namecmp, rev, length);
		j++;
	}	
	return (0);
}
