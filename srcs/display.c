/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 18:25:50 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/05 11:16:53 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		print_actual(t_length *length, t_file *tmp, int flag)
{
	if (length)
		print_det(tmp, length, flag, -1);
	else if ((flag & F_P) && tmp->type == DT_DIR)
		ft_printf("%s/\n", tmp->name);
	else
		ft_printf("%s\n", tmp->name);
}

char			*display_f(t_file **file, int (*f)(t_file*, t_file*, int),
		int flag, t_length *length)
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
		if ((*f)(tmp, comp, rev) <= 0)
			tmp = comp;
		comp = comp->next;
	}
	print_actual(length, tmp, flag);
	if ((flag & F_BR) && tmp->type == DT_DIR)
		name = ft_strdup(tmp->name);
	*file = delete_file(*file, tmp);
	return (name);
}

static t_rep	*parse_list(t_file *file, int flag, t_length *length, int size)
{
	int		j;
	t_rep	*first;
	t_rep	*tmp;
	char	*name;

	j = 0;
	first = NULL;
	tmp = NULL;
	while (j < size)
	{
		if (flag & F_S)
			name = display_f(&file, &sizecmp, flag, length);
		else if (flag & F_T)
			name = display_f(&file, &timecmp, flag, length);
		else
			name = display_f(&file, &namecmp, flag, length);
		if ((flag & F_BR) && name
				&& ft_strcmp(name, ".")
				&& ft_strcmp(name, "..")
				&& (tmp = keep_rep(name, &first, tmp)) == NULL)
			return (NULL);
		ft_strdel(&name);
		j++;
	}
	return (first);
}

t_rep			*display_file(t_file *file, int flag,
		t_length **length, int files)
{
	t_rep	*first;

	if (flag & F_L && !(files) && *length && file)
		ft_printf("total %d\n", (*length)->blocks);
	if (length)
		first = parse_list(file, flag, *length, lstlen(file));
	else
		first = parse_list(file, flag, NULL, lstlen(file));
	if (length && *length)
	{
		free(*length);
		*length = NULL;
	}
	return (first);
}
