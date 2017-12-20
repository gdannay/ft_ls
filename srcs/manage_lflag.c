/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_lflag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 12:17:51 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/19 19:04:56 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_length		*create_l()
{
	t_length	*length;

	if ((length = (t_length *)malloc(sizeof(t_length))) == NULL)
		return (0);
	length->l_links = 0;
	length->l_pwname = 0;
	length->l_grpname = 0;
	length->l_size = 0;
	length->blocks = 0;
	return (length);
}

void			compute_length(t_length *l, t_file *tmp)
{
	int	i;

	i = 0;
	while (tmp && tmp->pw_name && tmp->pw_name[i])
		i++;
	l->l_pwname = l->l_pwname > i ? l->l_pwname : i;
	while (tmp && tmp->grp_name && tmp->grp_name[i])
		i++;
	l->l_grpname = l->l_grpname > i ? l->l_grpname : i;
	i = length_nbr(tmp->size);
	l->l_size = l->l_size > i ? l->l_size : i;
	i = length_nbr(tmp->links);
	l->l_links = l->l_links > i ? l->l_links : i;
	l->blocks += tmp->blocks;
}

static void		fill_protec(char *protec, t_file *tmp)
{
	if (tmp->type == DT_REG)
		protec[0] = '-';
	else if (tmp->type == DT_DIR)
		protec[0] = 'd';
	else if (tmp->type == DT_LNK)
		protec[0] = 'l';
	else if (tmp->type == DT_FIFO)
		protec[0] = 'p';
	else if (tmp->type == DT_SOCK)
		protec[0] = 's';
	else if (tmp->type == DT_CHR)
		protec[0] = 'c';
	else if (tmp->type == DT_BLK)
		protec[0] = 'b';
	else
		protec[0] = '-';
	protec[1] = tmp->protec & S_IRUSR ? 'r' : '-';
	protec[2] = tmp->protec & S_IWUSR ? 'w' : '-';
	protec[3] = tmp->protec & S_IXUSR ? 'x' : '-';
	protec[4] = tmp->protec & S_IRGRP ? 'r' : '-';
	protec[5] = tmp->protec & S_IWGRP ? 'w' : '-';
	protec[6] = tmp->protec & S_IXGRP ? 'x' : '-';
	protec[7] = tmp->protec & S_IROTH ? 'r' : '-';
	protec[8] = tmp->protec & S_IWOTH ? 'w' : '-';
	protec[9] = tmp->protec & S_IXOTH ? 'x' : '-';
}

static void		print_time(t_file *tmp)
{
	char 	f_time[13];
	char 	*raw;
	int		i;

	i = -1;
	raw = ctime(&(tmp->mtime));
	while (++i < 6)
		f_time[i] = raw[i + 4];
	f_time[6] = ' ';
	if ((time(NULL) - tmp->mtime) > 15778800)
	{
		while (++i < 12)
			f_time[i] = raw[i + 12];	
	}
	else
	{
		while (++i < 12)
			f_time[i] = raw[i + 4];	
	}
	f_time[12] = '\0';
	ft_printf("%s", f_time);
}

void			print_det(t_file *tmp, t_length *length)
{
	char 	protec[11];
	int		i;

	i = -1;
	fill_protec(protec, tmp);
	protec[10] = '\0';
	ft_printf("%s", protec, tmp->links);
	while (++i < length->l_links - length_nbr(tmp->links) + 2)
		ft_printf(" ");
	ft_printf("%d %s", tmp->links, tmp->pw_name);
	i = -1;
	while (++i < length->l_pwname - (int)ft_strlen(tmp->pw_name))
		ft_printf(" ");
	ft_printf("  %s", tmp->grp_name);
	i = -1;
	while (++i < length->l_grpname - (int)ft_strlen(tmp->grp_name)
			+ length->l_size - length_nbr(tmp->size))
		ft_printf(" ");
	ft_printf("  %d ", tmp->size);
	print_time(tmp);
	ft_printf(" %s", tmp->name);
	if (tmp->type == DT_LNK)
		ft_printf(" -> %s", tmp->d_link);
	ft_printf("\n");
}
