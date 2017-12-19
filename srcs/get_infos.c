/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 10:58:11 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/19 10:56:24 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_printf.h"
#include "libft.h"

t_file	*get_file(struct dirent* fichier, t_file *tmp, char *dir, int flag)
{
	struct stat		fileStat;
	struct group	*grp;
	struct passwd	*uid;
	t_file			*file;
	char			*file_dir;
	char			*path;
	ssize_t 		len;
	char			buff[1024];

	if ((file_dir = joindir(dir, fichier->d_name)) == NULL)
		return (NULL);
	if ((file = (t_file *)malloc(sizeof(t_file))) == NULL)
		return (NULL);
	if(lstat(file_dir, &fileStat) < 0)
		return (NULL);
	file->protec = fileStat.st_mode;
	file->name = ft_strdup(fichier->d_name);
	file->type = fichier->d_type;
	grp = getgrgid(fileStat.st_gid);
	uid = getpwuid(fileStat.st_uid);
	file->grp_name = ft_strdup(grp->gr_name);
	file->pw_name = ft_strdup(uid->pw_name);
	if (!(file->name) || !(file->grp_name) || !(file->pw_name))
		return (NULL);
	file->size = fileStat.st_size;
	file->mtime = fileStat.st_mtime;
	file->links = fileStat.st_nlink;
	file->blocks = fileStat.st_blocks;
	if (file->type == DT_LNK && (flag & F_L))
	{
		if ((path = joindir(dir, file->name)) == NULL)
			return (NULL);
		if ((len = readlink(path, buff, 1023)) == -1)
			return (NULL);
		buff[len] = '\0';
		file->d_link = ft_strdup(buff);
		ft_strdel(&path);
	}
	else
		file->d_link = NULL;
	file->next = NULL;
	if (tmp != NULL)
		tmp->next = file;
	return (file);
}

t_file			*parse_rep(DIR *rep, char *dir, int flag, t_length *length)
{
	struct dirent	*fichier;
	t_file			*file;
	t_file			*tmp;

	file = NULL;
	tmp = NULL;
	while ((fichier = readdir(rep)))
	{
		if ((flag & F_A && fichier->d_name[0] == '.')
				|| fichier->d_name[0] != '.')
		{
			if (file == NULL)
			{
				file = get_file(fichier, file, dir, flag);
				tmp = file;
			}
			else
				tmp = get_file(fichier, tmp, dir, flag);
			if (tmp == NULL)
				return (NULL);
			if (flag & F_L)
				compute_length(length, tmp);
		}
	}
	return (file);
}
