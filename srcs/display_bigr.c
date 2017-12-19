/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bigr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 11:50:35 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/19 19:14:31 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_ls.h"

t_rep		*keep_rep(char *name, t_rep **first, t_rep *tmp)
{
	t_rep	*rep;

	if ((rep = (t_rep *)malloc(sizeof(t_rep))) == NULL)
		return (NULL);
	rep->name = ft_strdup(name);
	rep->sub = NULL;
	rep->next = NULL;
	if (*first == NULL)
		(*first) = rep;
	else
		tmp->next = rep;
	return (rep);
}

t_rep	*delete_rep(t_rep *first)
{
	t_rep	*tmp;

	tmp = first;
	first = first->next;
	ft_strdel(&(tmp->name));
	free(tmp);
	return (first);
}

int		algo(t_rep *rep, int flag, char *path)
{
	char	*new_path;
	t_rep	*sub;
	t_file	*file;
	DIR		*repo;
	t_length	*length;
	
	length = NULL;
	if (rep == NULL)
		return (0);
	if (flag & F_L)
		length = create_l();
	if ((new_path = joindir(path, rep->name)) == NULL)
		return (0);
	if ((repo = opendir(new_path)) == NULL)
	{
		check_file(new_path, NULL, new_path);
		return (0);
	}
	ft_printf("\n%s:\n", new_path);
	if ((file = parse_rep(repo, new_path, flag, length)) == NULL)
		free(length);
	if (file && (sub = display_file(file, flag, length, 0)))
		algo(sub, flag, new_path);
	rep = delete_rep(rep);
	algo(rep, flag, path);
	ft_strdel(&new_path);
	return (0);
}

int		display_bigr(t_file *file, int flag, t_length *length, char *path)
{
	t_rep	*rep;

	if ((rep = display_file(file, flag, length, 0)) == NULL)
		return (0);
	algo(rep, flag, path);	
	return (1);
}
