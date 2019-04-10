#include <stdio.h>
#include <math.h>

double fun4(double a, double b, double c)
{
	double result = 0;
	const double pi = 3.14;
	for (int i = 1; i <= 90; ++i)
	{
		result += a*(sin((pi*i/4) + b));
	}
	return result;
}
double fun5(int n)

{
	
	double x[n];
	x[0] = 1, x[1] = 2;
	for (int i = 0; i < n; ++i)
	{
		x[i] = 2 * x[i - 1] - x[i - 2];
	}
	return exp(x[n]);
}
int main()
{
	int n;
	
	
	double x, y, z;
	scanf("%lf, %lf, %lf", &x, &y, &z);
	scanf("%d", &n);

	fun4(x, y, z);
	fun5(n);
		return 0;

}