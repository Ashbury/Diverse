/*
** For an array of size n filled with random integers, find all sets
** of three values such as a + b + c = 0
** The complexity of the algorithm must not be greater than o(n^2).
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/*
** Here, I create this function in order to handle more values than atoi.
** Atoi returns an int. Here, I can deal with the largest number C can handle.
** Since I want to be simple, I decide the string must contain digits only.
** I will exit otherwise. I don't handle possible overlap.
*/

size_t	string_to_unsigned(const char *str)
{
	size_t	ret;
	size_t	i;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (!isdigit(str[i]))
		{
			printf("Error, the argument must contain digits only.");
			exit(1);
		}
		ret = ret * 10 + (str[i] - '0');
		i++;
	}
	return ret;
}

/*
** The syntax of this function might seem strange, but it is
** required to be accepted by the qsort() function.
*/

static int	int_cmp(const void *a, const void *b)
{
	return (*(int*)a - *(int*)b);
}

/*
** Here, I don't make a custom implementation of the sort function, and just use
** the native quicksort implementation, known as the average best for large and
** random distributions.
*/

static void	solve(int *array, size_t len)
{
	size_t	i = 0;
	size_t	j;
	size_t	k;
	ssize_t	sum;

	qsort(array, len, sizeof(int), int_cmp);

	while (i < len - 1)
	{
		j = i + 1;
		k = len - 1;
		while (j < k)
		{
			sum = array[i] + array[j] + array[k];
			if (sum == 0)
			{
				printf("%d + %d + %d = 0\n", array[i], array[j], array[k]);
				j++;
				k--;
			}
			else if (sum <= 0)
				j++;
			else
				k--;
		}
		i++;
	}
}

/*
** Here, the main will simply set-up the data, and call the
** solving function. The time it takes shall not be considered.
*/

int	main(int ac, char **av)
{
	size_t	len;
	int		*array;

	if (ac != 2)
	{
		printf("Usage: %s <number of values>\n", av[0]);
		return 1;
	}
	srand(time(NULL));
	len = string_to_unsigned(av[1]);
	array = malloc(sizeof(int) * len);
	for (size_t i = 0; i < len; i++)
	{
		array[i] = rand() - INT32_MAX / 2;
	}
	solve(array, len);
	free(array);
	return 0;
}
