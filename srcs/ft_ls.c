#include "ft_ls.h"

int	main(void)
{
	DIR* rep;

	struct dirent* fichier;
	rep = opendir("..");
	if (rep == NULL)
		return (0);
	while ((fichier = readdir(rep)))
		printf("OKAY s'appelle %s\n", fichier->d_name);
	if (closedir(rep) == -1)
		return (0);
	printf("ICI");
}
