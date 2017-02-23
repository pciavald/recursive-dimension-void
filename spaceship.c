#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void		freetab(void * tab, int currentD, int originalD)
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

void 		free_data(int ***data, size_t xlen, size_t ylen)
{
	size_t	i, j;

	for (i=0; i < xlen; ++i) {
		if (data[i] != NULL) {
			for (j=0; j < ylen; ++j)
				free(data[i][j]);
			free(data[i]);
		}
	}
	free(data);
}

int 		***alloc_data(size_t xlen, size_t ylen, size_t zlen)
{
	int		***p;
	size_t	i, j;

	if ((p = malloc(xlen * sizeof *p)) == NULL) {
		perror("malloc 1");
		return NULL;
	}

	for (i=0; i < xlen; ++i)
		p[i] = NULL;

	for (i=0; i < xlen; ++i)
		if ((p[i] = malloc(ylen * sizeof *p[i])) == NULL) {
			perror("malloc 2");
			free_data(p, xlen, ylen);
			return NULL;
		}

	for (i=0; i < xlen; ++i)
		for (j=0; j < ylen; ++j)
			p[i][j] = NULL;

	for (i=0; i < xlen; ++i)
		for (j=0; j < ylen; ++j)
			if ((p[i][j] = malloc(zlen * sizeof *p[i][j])) == NULL) {
				perror("malloc 3");
				free_data(p, xlen, ylen);
				return NULL;
			}

	return p;
}

int		main(void)
{
	int		***target;
	int		dimension = 3;
	size_t	xlen = 8;
	size_t	ylen = 8;
	size_t	zlen = 8;
	size_t	i, j, k;
	char	val;

	if ((target = alloc_data(xlen, ylen, zlen)) == NULL)
		return EXIT_FAILURE;

	for (i=0; i < xlen; ++i)
	{
		val = 0;
		for (j=0; j < ylen; ++j)
		{
			for (k=0; k < zlen; ++k)
			{
				target[i][j][k] = val;
				val++;
			}
		}
	}

	printf("%d\n", target[1][2][7]);
	printf("--MAIN\n%p\n%d\n\n", target, (unsigned int) target);
	freetab(target, dimension - 1, dimension - 1);
	//free_data(target, xlen, ylen);
	return EXIT_SUCCESS;
}
