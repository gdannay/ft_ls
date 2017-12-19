/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 18:25:50 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/19 19:08:22 by gdannay          ###   ########.fr       */
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

char		*display_f(t_file **file, int(*f)(t_file*, t_file*, int), int flag, t_length *length)
{
	t_file	*tmp;
	t_file	*comp;
	char	*name;
	int		rev;

	tmp = *file;
	comp = NULL;
	name = NULL;
	rev = (flag & F_R) ? -1 : 1;
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
	if ((flag & F_BR) && tmp->type == DT_DIR)
		name = ft_strdup(tmp->name);
	*file = delete_file(*file, tmp);
	return (name);
}

t_rep	*display_file(t_file *file, int flag, t_length *length, int files)
{
	int		size;
	int		j;
	t_rep	*first;
	t_rep	*tmp;
	char	*name;

	j = 0;
	size = lstlen(file);
	first = NULL;
	name = NULL;
	tmp = NULL;
	if (flag & F_L && !(files) && length && size)
		ft_printf("total %d\n", length->blocks);
	while (j < size)
	{
		if (flag & F_T)
			name = display_f(&file, &timecmp, flag, length);
		else
			name = display_f(&file, &namecmp, flag, length);
		if ((flag & F_BR) && name)
		{
			if ((tmp = keep_rep(name, &first, tmp)) == NULL)
				return (NULL);
		}	
		ft_strdel(&name);
		j++;
	}
	if (length)
		free(length);
	return (first);
}
