/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 15:18:48 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/03 19:05:58 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*joindir(char *dir, char *name)
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

static int	last_slash(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '/')
			j = i;
		i++;
	}
	return (j);
}

char		*manage_path(char *str, char **rest)
{
	int		j;
	char	*path;
	char	*dir;

	j = last_slash(str);
	if (str == NULL || rest == NULL)
		return (NULL);
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
