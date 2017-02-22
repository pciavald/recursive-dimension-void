#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void	freetab(void * tab, int currentD, int originalD)
{
	unsigned int		addr = (unsigned int)tab;

	printf("--FREET %d\n%p\n%d\n\n", currentD, (char *)addr, addr);
	if (currentD != 0)
	{
		addr = *((unsigned int *)addr);
		freetab((void *)addr, --currentD, originalD);
	}
	else
	{
		printf("%c", *(char *)addr);
		free((void *)addr);
		return ;
	}
	freetab((void *)(((unsigned int *)++addr)), --currentD, originalD);
	// ++ logic
}


int		main(void)
{
	char ***	target = NULL;
	char ***	tmp;
	int			dimension = 3;
	char		c = 'a';

	target = malloc(sizeof(char **));
	tmp = target;
	for (int i = 0; i < 3; i++)
	{
		*tmp = malloc(sizeof(char *));
		for(int i = 0; i < 3; i++)
		{
			**tmp = malloc(sizeof(char));
			for(int i = 0; i < 3; i++)
			{
				**tmp = malloc(sizeof(char));
				***tmp = c++;
				*tmp++;
			}
			*tmp++;
		}
		tmp++;
	}

	***target = 'a';

	printf("--MAIN\n%p\n%d\n\n", target, (unsigned int) target);
	freetab(target, dimension - 1, dimension - 1);

	return (0);
}
