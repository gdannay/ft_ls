/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 15:18:48 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/16 17:26:23 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*joindir(char *dir, char *name)
{
	char	*file_dir;
	size_t	l_d;
	size_t	l_n;
	int		i;
	int		j;

	i = -1;
	j = 0;
	l_d = ft_strlen(dir);
	l_n = ft_strlen(name);
	if ((file_dir = (char *)malloc(sizeof(char) * (l_d + l_n + 2))) == NULL)
		return (NULL);
	while (dir && dir[++i] != '\0')
		file_dir[i] = dir[i];
	file_dir[i] = '/';
	i++;
	while (name && name[j] != '\0')
	{
		file_dir[i] = name[j];
		i++;
		j++;
	}
	file_dir[i] = '\0';
	return (file_dir);
}

char	*manage_path(char *str, char **rest)
{
	int		i;
	int		j;
	char 	*path;
	char	*dir;
	
	i = 0;
	j = 0;
	if (str == NULL || rest == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '/')
			j = i;
		i++;
	}
	if (str[j] == '/')
	{
		if ((path = ft_strndup(str, j)) == NULL)
			return (NULL);
		if ((dir = joindir(".", path)) == NULL)
			return (NULL);
		j++;
		if ((*rest = ft_strsub(str, j, ft_strlen(str) - (size_t)j)) == NULL)
			return (NULL);
		ft_strdel(&path);
		return (dir);
	}
	if ((*rest = ft_strdup(str)) == NULL)
		return (NULL);
	return (ft_strdup("."));
}
