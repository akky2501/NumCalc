#include <stdio.h>
#include <math.h>

int main(void){
	const double k[] = {1.0, 1.0, 1.0/2.0, 1.0/6.0, 1.0/24.0, 1.0/120.0};	
	const int N = sizeof(k)/sizeof(double);
	const double x = 10.5;
	
	const double e = 2.7183;
	double e10 = 1.0;
	for(int i=0;i<10;i++) e10 *= e;

	const double e10_5 = exp(10.5);


	printf("exp(10.5) = %.4e \n",e10_5);
	
	printf("exp(10) = %.4e , e^10 = %.4e \n",exp(10.),e10);

	{ // Taylor(6,a=0)
		double a = 0.0;
		double ans = k[N-1];
		for(int i=N-2;i>=0;i--) {
			ans = ans*(x-a)+k[i];
		}
		ans = 1.0*ans;

		printf("Taylor(a=0) = %.4e err = %.4e err_up = %.4e\n"
				,ans,fabs(ans-e10_5)/e10_5,exp(2*(x-a))*pow((x-a),5)/120);
	}

	{ // Taylor(6,a=10)
		double a = 10.0;
		double ans = k[N-1];
		for(int i=N-2;i>=0;i--) {
			ans = ans*(x-a)+k[i];
		}
		ans = e10*ans;

		printf("Taylor(a=10) = %.4e err = %.4e err_up = %.4e\n"
				,ans,fabs(ans-e10_5)/e10_5,exp(2*(x-a))*pow((x-a),5)/120);
	}
		
	return 0;
}
