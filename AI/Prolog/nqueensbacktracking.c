#include <stdio.h>

int a[50][50], n;

int safe(int r, int c)
{
	int i, j;
	for(i = 0; i < c; i++)
	{
		if(a[r][i])
			return 0;
	}
	for(i = r, j = c; i >= 0 && j >= 0; i--, j--)
	{
		if(a[i][j])
			return 0;
	}
	for(i = r, j = c; j >= 0 && i < n; i++, j--)
	{
		if(a[i][j])
			return 0;
	}
	return 1;
}

int solve(int c)
{
	int i, j;
	if (c >= n)
		return 1;
	for (i = 0; i < n; i++)
	{
		if (safe(i, c))
		{
			a[i][c] = 1;
			if(solve(c+1))
				return 1;
			a[i][c] = 0;
		}
	}
	return 0;
}

int main()
{
	int i, j;
	printf("Enter the value of n:");
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			a[i][j] = 0;
	if(solve(0) == 0)
		printf("No solution");
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
			printf(" %d ", a[i][j]);
		printf("\n");
	}
	return 0;
}
