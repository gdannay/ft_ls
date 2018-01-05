/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 10:58:11 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/05 10:03:55 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	fill_link(char *dir, t_file *file)
{
	char			*path;
	ssize_t			len;
	char			buff[1024];

	if ((path = joindir(dir, file->name)) == NULL)
		return (0);
	if ((len = readlink(path, buff, 1023)) == -1)
		return (0);
	buff[len] = '\0';
	file->d_link = ft_strdup(buff);
	ft_strdel(&path);
	return (1);
}

static int	fill_details(struct stat filestat, t_file *file, char *dir)
{
	struct group	*grp;
	struct passwd	*uid;

	grp = NULL;
	uid = NULL;
	file->protec = filestat.st_mode;
	file->links = filestat.st_nlink;
	file->blocks = filestat.st_blocks;
	if ((grp = getgrgid(filestat.st_gid)) == NULL
			&& !(file->grp_name = ft_itoa(filestat.st_gid)))
		return (0);
	else if (grp && !(file->grp_name = ft_strdup(grp->gr_name)))
		return (0);
	if ((uid = getpwuid(filestat.st_uid)) == NULL
			&& !(file->pw_name = ft_itoa(filestat.st_uid)))
		return (0);
	else if (uid && !(file->pw_name = ft_strdup(uid->pw_name)))
		return (0);
	if (file->type == DT_LNK)
	{
		if (!(fill_link(dir, file)))
			return (0);
	}
	return (1);
}

t_file		*get_file(struct dirent *fichier, t_file *tmp, char *dir, int flag)
{
	struct stat		filestat;
	t_file			*file;
	char			*file_dir;

	if ((file_dir = joindir(dir, fichier->d_name)) == NULL
			|| lstat(file_dir, &filestat) < 0
			|| (file = (t_file *)malloc(sizeof(t_file))) == NULL
			|| (file->name = ft_strdup(fichier->d_name)) == NULL)
	{
		ft_strdel(&file_dir);
		return (NULL);
	}
	file->mtime = filestat.st_mtime;
	file->type = fichier->d_type;
	file->size = filestat.st_size;
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
	t_file			*tmp2;

	file = NULL;
	tmp = NULL;
	while ((fichier = readdir(rep)))
	{
		if (((flag & F_A) && fichier->d_name[0] == '.')
				|| fichier->d_name[0] != '.')
		{
			if ((tmp2 = get_file(fichier, tmp, dir, flag)))
			{
				tmp = tmp2;
				if (file == NULL)
					file = tmp;
				if ((flag & F_L) && length)
					compute_length(length, tmp);
			}
		}
	}
	if (closedir(rep) == -1)
		return (NULL);
	return (file);
}
