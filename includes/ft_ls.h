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
	struct s_file	*next;
}					t_file;

t_file				*parse_rep(DIR *rep, char *dir);
int					check_flag(char *str);
int					check_args(int ac, char **av);
char				*joindir(char *dir, char *name);
char				*manage_path(char *str, char **rest);

#endif
