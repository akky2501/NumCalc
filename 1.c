
#include<stdio.h>
#include<math.h>

int main(void){
	// x^2 - 2*10^3*x + 10^(-3) = 0
	const char* str1 = "b/a      = %+.4e , c/a   = %+.4e \n";
	const char* str2 = "x1       = %+.4e , x2    = %+.4e \n";
	const char* str3 = "-(x1+x2) = %+.4e , x1*x2 = %+.4e \n";
	const char* str4 = "      -b = %+.4e , sqrt(b*b-4*a*c) = %+.4e \n";
	const char* str5 = "x1:       x^2 - 2*10^3*x + 10^(-3) = %+.4e \n";
	const char* str6 = "x2:       x^2 - 2*10^3*x + 10^(-3) = %+.4e \n";
	
	{
		float a = 1.0f;
		float b = -2.0e3f;
		float c = 1.0e-3f;

		float x1 = ( -b + sqrt(b*b - 4*a*c) ) / (2*a);
		float x2 = ( -b - sqrt(b*b - 4*a*c) ) / (2*a);


		printf("float\n");
		printf(str1,(double)(b/a),(double)(c/a));
		printf(str2, (double)x1,(double)x2);
		printf(str3, (double)-(x1+x2),(double)(x1*x2));
		printf(str4,(double)-b,(double)sqrtf(b*b-4*a*c));
		printf(str5,(double)(a*x1*x1+b*x1+c));
		printf(str6,(double)(a*x2*x2+b*x2+c));
		printf("\n");
	}
	
	{
		double a = 1.0;
		double b = -2.0e3;
		double c = 1.0e-3;

		double x1 = ( -b + sqrt(b*b - 4*a*c) ) / (2*a);
		double x2 = ( -b - sqrt(b*b - 4*a*c) ) / (2*a);


		printf("double\n");
		printf(str1, b/a     , c/a);
		printf(str2, x1      , x2);
		printf(str3, -(x1+x2), x1*x2);
		printf(str4,-b,sqrt(b*b-4*a*c));
		printf(str5,(double)(a*x1*x1+b*x1+c));
		printf(str6,(double)(a*x2*x2+b*x2+c));
		printf("\n");
	}
	
	{
		float a = 1.0f;
		float b = -2.0e3f;
		float c = 1.0e-3f;

		float x1 = ( -b + sqrt(b*b - 4*a*c) ) / (2*a);
		float x2 = (4*a*c) / (2*a*(-b+sqrtf(b*b-4*a*c)));

		printf("float_improvement\n");
		printf(str1,(double)(b/a),(double)(c/a));
		printf(str2, (double)x1,(double)x2);
		printf(str3, (double)-(x1+x2),(double)(x1*x2));
		printf(str4,(double)-b,(double)sqrtf(b*b-4*a*c));
		printf(str5,(double)(a*x1*x1+b*x1+c));
		printf(str6,(double)(a*x2*x2+b*x2+c));
		printf("\n");
	}
	

	return 0;
}

