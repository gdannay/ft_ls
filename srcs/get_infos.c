/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 10:58:11 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/15 15:19:35 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

static	t_file	*get_file(struct dirent* fichier, t_file *tmp, char *dir)
{
	struct stat		fileStat;
	struct group	*grp;
	struct passwd	*uid;
	t_file			*file;
	char			*file_dir;

	if ((file_dir = joindir(dir, fichier->d_name)) == NULL)
		return (NULL);
	if(stat(file_dir, &fileStat) < 0)
		return (NULL);
	if ((file = (t_file *)malloc(sizeof(t_file))) == NULL)
		return (NULL);
	grp = getgrgid(fileStat.st_gid);
	uid = getpwuid(fileStat.st_uid);
	file->name = fichier->d_name;
	file->type = fichier->d_type;
	file->grp_name = grp->gr_name;
	file->pw_name = uid->pw_name;
	file->protec = fileStat.st_mode;
	file->size = fileStat.st_size;
	file->mtime = fileStat.st_mtime;
	file->links = fileStat.st_nlink;
	file->next = NULL;
	if (tmp != NULL)
		tmp->next = file;
	return (file);
}

t_file			*parse_rep(DIR *rep, char *dir)
{
	struct dirent	*fichier;
	t_file			*file;
	t_file			*tmp;

	file = NULL;
	tmp = NULL;
	while ((fichier = readdir(rep)))
	{
		if (file == NULL)
		{
			file = get_file(fichier, file, dir);
			tmp = file;
		}
		else
			tmp = get_file(fichier, tmp, dir);
		if (tmp == NULL)
			return (NULL);
	}
	return (file);
}
