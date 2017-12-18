/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 10:30:17 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/16 17:30:25 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# define F_L 1
# define F_R 2
# define F_BR 4
# define F_T 8
# define F_A 16

# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <grp.h>
# include <pwd.h>
# include <time.h>

typedef struct		s_rep
{
	struct s_file	*infos;
	struct s_rep	*sub;
	struct s_rep	*next;
}					t_rep;

typedef struct		s_file
{
	char			*name;
	char			*pw_name;
	char			*grp_name;
	int				size;
	int				protec;
	int				links;
	int				atime;
	time_t			mtime;
	int				ctime;
	unsigned char	type;
	char			*d_link;
	struct s_file	*next;
}					t_file;

typedef struct		s_length
{
	int				l_links;
	int				l_pwname;
	int				l_grpname;
	int				l_size;
}					t_length;

t_file				*parse_rep(DIR *rep, char *dir, int flag, t_length *length);
int					check_flag(char *str);
int					check_args(int ac, char **av);
char				*joindir(char *dir, char *name);
char				*manage_path(char *str, char **rest);
int					display_file(t_file *file, int flag, t_length *length);
int					lstlen(t_file *file);
void				delete_file(t_file **file, t_file *del);
int					usage(int flag);
void				manage_error(char **av, int flag, int i, int ac);
struct dirent		*check_file(char *path, char *file, char *error);
t_length			*create_l();
void				print_det(t_file *tmp, t_length *length);
void				compute_length(t_length *length, t_file *tmp);
int					get_last(char **av, int ac, int flag);
t_file				*get_file(struct dirent *fichier, t_file *tmp, char *dir, int flag);

#endif
