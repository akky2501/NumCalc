
#include<stdio.h>
#include<math.h>
#include<float.h>

// 対象の関数
double f(double x){
	return cos(x) - pow(x,4.0);
}

// 導関数
double f_(double x){
	return -sin(x) - 4.0 * pow(x,3.0);
}

// 二分法
double bisection(double a, double b){
	int n = 0;
	double x,fx;
	
	while(1){
		x = (a + b)/2.0;
		fx = f(x);

		if(    fabs(fx)    < DBL_EPSILON
			|| fabs(b - a) < DBL_EPSILON )
			break;

		if(fx*f(a) > 0) a = x;
		if(fx*f(b) > 0) b = x;

		n++;
	}

	printf("x = %e , n = %d \n",x,n);

	return x;
}

// 反復法で用いるphi(x)
double phi_newton(double x){
	return f_(x);
}

double phi_von_mises(double x){
	const double x0 = 1.4;
	return f_(x0);
}

double phi_secant_method(double x){
	double x0 = 1.4;
	return (f(x) - f(x0)) / (x - x0);
}

// 反復法
double iterative_method(double x,double (*phi)(double)){
	int n = 0;
	double gx;

	while(1){
		gx = x - f(x) / phi(x);

		if(    fabs(gx - x)   < DBL_EPSILON
			|| fabs((gx-x)/x) < DBL_EPSILON
			|| fabs(f(x))     < DBL_EPSILON )
			break;

		x = gx;
		n++;
	}
	
	printf("x = %e , n = %d \n",x,n);

	return x;
}

int main(void){

	printf("BisectionMethod : ");
	bisection(0.4,1.4);

	printf("NewtonMethod    : ");
	iterative_method(1.4, phi_newton);

	printf("VonMisesMethod  : ");
	iterative_method(1.4, phi_von_mises);

	printf("SecantMethod    : ");
	/* 割線法だけはx(1)から反復する*/
	double x = iterative_method(0.4, phi_secant_method);

	printf("\nDBL_EPS = %e \n", DBL_EPSILON);
	printf("f(x) = %e \n",f(x));

	return 0;
}

