/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 20:00:17 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/19 18:07:56 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			lstlen(t_file *file)
{
	t_file	*tmp;
	int		size;

	tmp = file;
	size = 0;
	while (tmp)
	{
		tmp = tmp->next;
		size++;
	}
	return (size);
}

t_file		*delete_file(t_file *file, t_file *del)
{
	t_file	*tmp;

	tmp = file;
	if (file == del)
		file = file->next;
	else
	{
		while (tmp && tmp->next != del)
			tmp = tmp->next;
		tmp->next = del->next;
	}
	ft_strdel(&(del->name));
	ft_strdel(&(del->grp_name));
	ft_strdel(&(del->pw_name));
	ft_strdel(&(del->d_link));
	free(del);
	return (file);
}
