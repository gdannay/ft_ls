/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 10:30:17 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/04 14:14:19 by gdannay          ###   ########.fr       */
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
# include "../libft/libft.h"

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
	int				blocks;
	struct s_file	*next;
}					t_file;

typedef struct		s_rep
{
	char			*name;
	struct s_rep	*next;
}					t_rep;

typedef struct		s_length
{
	int				l_links;
	int				l_pwname;
	int				l_grpname;
	int				l_size;
	int				blocks;
}					t_length;

t_file				*parse_rep(DIR *rep, char *dir, int flag, t_length *length);
int					check_flag(char *str);
int					check_args(int ac, char **av);
char				*joindir(char *dir, char *name);
char				*manage_path(char *str, char **rest);
t_rep				*display_file(t_file *file, int flag,
					t_length **length, int files);
int					lstlen(t_file *file);
t_file				*delete_file(t_file *file, t_file *del);
int					usage(int flag);
int					manage_error(char **av, int flag, int i, int ac);
struct dirent		*check_file(char *path, char *file, char *error);
t_length			*create_l();
void				print_det(t_file *tmp, t_length *length);
void				compute_length(t_length *length, t_file *tmp);
int					get_last(char **av, int ac, int flag);
int					display_bigr(t_file *file, int flag,
					t_length **length, char *path);
t_file				*get_file(struct dirent *fichier, t_file *tmp,
					char *dir, int flag);
char				*display_f(t_file **file,
					int(*f)(t_file*, t_file*, int), int flag, t_length *length);
t_rep				*keep_rep(char *name, t_rep **first, t_rep *tmp);
t_rep				*delete_rep(t_rep *first);
int					get_last(char **av, int ac, int flag);
int					check_flag(char *str);
int					algo(t_rep *rep, int flag, char *path);
int					fts_error(void);

#endif
