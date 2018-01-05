/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 11:12:51 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/05 11:13:55 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		timecmp(t_file *tmp, t_file *comp, int rev)
{
	return ((tmp->mtime - comp->mtime) * rev);
}

int		namecmp(t_file *tmp, t_file *comp, int rev)
{
	return (ft_strcmp(comp->name, tmp->name) * rev);
}

int		sizecmp(t_file *tmp, t_file *comp, int rev)
{
	return ((tmp->size - comp->size) * rev);
}
