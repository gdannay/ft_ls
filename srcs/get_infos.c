/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 10:58:11 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/03 21:07:23 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	fill_details(struct stat filestat, t_file *file, char *dir)
{
	struct group	*grp;
	struct passwd	*uid;
	char			*path;
	ssize_t			len;
	char			buff[1024];

	file->protec = filestat.st_mode;
	if ((grp = getgrgid(filestat.st_gid)) == NULL
			|| (uid = getpwuid(filestat.st_uid)) == NULL
			|| (file->grp_name = ft_strdup(grp->gr_name)) == NULL
			|| (file->pw_name = ft_strdup(uid->pw_name)) == NULL)
		return (0);
	if (file->type == DT_LNK)
	{
		if ((path = joindir(dir, file->name)) == NULL)
			return (0);
		if ((len = readlink(path, buff, 1023)) == -1)
			return (0);
		buff[len] = '\0';
		file->d_link = ft_strdup(buff);
		ft_strdel(&path);
	}
	else
		file->d_link = NULL;
	return (1);
}

t_file		*get_file(struct dirent *fichier, t_file *tmp, char *dir, int flag)
{
	struct stat		filestat;
	t_file			*file;
	char			*file_dir;

	if ((file_dir = joindir(dir, fichier->d_name)) == NULL
			|| (file = (t_file *)malloc(sizeof(t_file))) == NULL
			|| lstat(file_dir, &filestat) < 0
			|| (file->name = ft_strdup(fichier->d_name)) == NULL)
		return (NULL);
	file->mtime = filestat.st_mtime;
	file->type = fichier->d_type;
	file->size = filestat.st_size;
	file->links = filestat.st_nlink;
	file->blocks = filestat.st_blocks;
	file->grp_name = NULL;
	file->pw_name = NULL;
	file->next = NULL;
	file->d_link = NULL;
	if (flag & F_L && !(fill_details(filestat, file, dir)))
		return (NULL);
	if (tmp != NULL)
		tmp->next = file;
	ft_strdel(&file_dir);
	return (file);
}

t_file		*parse_rep(DIR *rep, char *dir, int flag, t_length *length)
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
				file = tmp;
			tmp = get_file(fichier, tmp, dir, flag);
			if (tmp == NULL)
				return (NULL);
			if (flag & F_L)
				compute_length(length, tmp);
		}
	}
	if (closedir(rep) == -1)
		return (NULL);
	return (file);
}
