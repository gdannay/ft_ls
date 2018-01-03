/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bigr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 11:50:35 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/03 20:17:10 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_rep			*keep_rep(char *name, t_rep **first, t_rep *tmp)
{
	t_rep	*rep;

	if ((rep = (t_rep *)malloc(sizeof(t_rep))) == NULL)
		return (NULL);
	rep->name = ft_strdup(name);
	rep->next = NULL;
	if (*first == NULL)
		(*first) = rep;
	else
		tmp->next = rep;
	return (rep);
}

t_rep			*delete_rep(t_rep *first)
{
	t_rep	*tmp;

	tmp = first;
	first = first->next;
	ft_strdel(&(tmp->name));
	free(tmp);
	return (first);
}

static int		parse_repo(char *new_path, DIR *repo, int flag)
{
	t_length	*length;
	t_rep		*sub;
	t_file		*file;

	length = NULL;
	if (flag & F_L && (length = create_l()) == NULL)
		return (0);
	if (new_path[0] && new_path[1] && new_path[0] == '/')
		ft_printf("\n%s:\n", new_path + 1);
	else
		ft_printf("\n%s:\n", new_path);
	if ((file = parse_rep(repo, new_path, flag, length)) == NULL)
		free(length);
	if (file && (sub = display_file(file, flag, length, 0)))
		algo(sub, flag, new_path);
	return (1);
}

int				algo(t_rep *rep, int flag, char *path)
{
	char	*new_path;
	DIR		*repo;

	if (rep == NULL)
		return (0);
	if ((new_path = joindir(path, rep->name)) == NULL)
		return (0);
	if ((repo = opendir(new_path)) == NULL)
		check_file(new_path, NULL, new_path);
	else if (repo && parse_repo(new_path, repo, flag) == 0)
		return (0);
	rep = delete_rep(rep);
	algo(rep, flag, path);
	ft_strdel(&new_path);
	return (0);
}

int				display_bigr(t_file *file, int flag,
		t_length *length, char *path)
{
	t_rep	*rep;

	if ((rep = display_file(file, flag, length, 0)) == NULL)
		return (0);
	algo(rep, flag, path);
	return (1);
}
