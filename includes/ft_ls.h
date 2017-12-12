#ifndef FT_LS_H
# define FT_LS_H

# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <grp.h>
# include <pwd.h>

typedef struct		s_rep
{
	struct s_file	*infos;
	struct s_rep	*sub;
	struct s_rep	*next;
}					t_rep;

typedef struc		s_file
{
	char			*name;
	int				uid;
	int				gid;
	int				size;
	int				atime;
	int				mtime;
	int				ctime;
	unsigned char	type;
	struct s_file	*next;
}					t_file;

#endif
