
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>


template<int N,int M,typename T = double> // N:col M:row
class Matrix{
public:
	Matrix(){
		m.resize(N);
		for(auto& it : m) it.resize(M);
	}

	~Matrix(){}

	T& operator()(size_t i,size_t j){ return m[i][j]; }

	// 単純ガウス法
	void Gauss(bool is_use_pivotting){

		// 上三角行列への変形
		for(int k=0;k<N;k++){
			if(is_use_pivotting) pivotting(k);
			
			for(int j=M-1;j>=k;j--)
				m[k][j] = m[k][j] / m[k][k];
			
			for(int i=k+1;i<N;i++)
				for(int j=M-1;j>=k;j--)
					m[i][j] = m[i][j] - m[i][k]*m[k][j];
		}
		
		// 後退代入
		for(int k=N-1;k>=0;k--)
			for(int i=k-1;i>=0;i--) 
				for(int j=M-1;j>=0;j--)
					m[i][j] = m[i][j] - m[i][k]*m[k][j];
		
	}
	
	// ガウス・ジョルダン法
	void GaussJordan(bool is_use_pivotting){
	
		for(int k=0;k<N;k++){
			if(is_use_pivotting) pivotting(k);
			
			for(int j=M-1;j>=k;j--)
				m[k][j] = m[k][j] / m[k][k];
			
			for(int i=0;i<N;i++)
				for(int j=M-1;j>=k;j--)
					if(i != k) m[i][j] = m[i][j] - m[i][k]*m[k][j];
			show();
		}
		
	}

	void show(void){
		for(auto& p:m){
			for(auto& q:p) 
				std::cout<< " " 
						<< std::scientific << std::setprecision(7)
						<< std::setw(12)   << q;
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

private:
	std::vector<std::vector<T>> m;

	void pivotting(int i){
		auto* max_row = &(m[i]);

		for(int h=i+1;h<N;h++){
			if(m[h][i] > (*max_row)[i]) max_row = &(m[h]); 
		}

		m[i].swap(*max_row);
	}
};

template<typename T>
class Num{
public:
	Num(){}
	Num(T num){ set(num); }
	Num(const Num<T>& num){ set(num.n); }

	void set(T t){ n = t; round();}

	const Num<T>& operator=(const Num<T>& num){ n = num.n;  return *this; }
	const Num<T>& operator=(const T& num){ set(num);  return *this; }
	const Num<T> operator+(const Num<T>& num){ return Num<T>(n + num.n); }
	const Num<T> operator-(const Num<T>& num){ return Num<T>(n - num.n); }
	const Num<T> operator*(const Num<T>& num){ return Num<T>(n * num.n); }
	const Num<T> operator/(const Num<T>& num){ return Num<T>(n / num.n); }
	bool operator>(const Num<T>& num){ return n > num.n; }
	
	friend std::ostream& operator<<(std::ostream& os,const Num<T>& num){
		os << std::scientific << std::setprecision(7) << std::setw(12) << num.n; 
		return os;
	}

private:
	T n;
	void round(void){
		char s[50];
		sprintf(s,"%.7e",n);
		n = atof(s);
		//printf("%.10e\n",n);
	}
};


int main(void){

	/*std::cout << "Q 1 Gauss no pivotting" <<std::endl;
	Matrix<3,4> m;
	m(0,0) = 3; m(0,1) = 1; m(0,2) = 2; m(0,3) = 13;
	m(1,0) = 5; m(1,1) = 1; m(1,2) = 3; m(1,3) = 20;
	m(2,0) = 4; m(2,1) = 2; m(2,2) = 1; m(2,3) = 13;

	std::cout <<"拡大係数行列(入力)"<< std::endl;
	m.show();
	m.Gauss(false);
	std::cout <<"拡大係数行列(解)"<< std::endl;
	m.show();
*/
	
	std::cout << "Q 2" <<std::endl;
	Matrix<3,4,Num<double>> m2 , m2p;
	m2(0,0) = 4; m2(0,1) = 2; m2(0,2) = 1; m2(0,3) = 11;
	m2(1,0) = 3; m2(1,1) = 1.500001; m2(1,2) = 2; m2(1,3) = 12.000002;
	m2(2,0) = 5; m2(2,1) = 1; m2(2,2) = 3; m2(2,3) = 16;

	m2p = m2;

	std::cout <<"拡大係数行列(入力)"<< std::endl;
	m2.show();

	m2.GaussJordan(false);
	std::cout <<"出力 pivottingなし"<< std::endl;
	m2.show();
	
	m2p.GaussJordan(true);
	std::cout <<"出力 pivottingあり"<< std::endl;
	m2p.show();

/*
	std::cout << "Q 3 inverse matrix (Gauss-Jordan pivotting)" <<std::endl;
	Matrix<4,4*2> m3;
	m3(0,0) = 1; m3(0,1) = 1; m3(0,2) = 1;  m3(0,3) = 1;
	m3(1,0) = 1; m3(1,1) = 2; m3(1,2) = 3;  m3(1,3) = 4; 
	m3(2,0) = 1; m3(2,1) = 3; m3(2,2) = 6;  m3(2,3) = 10; 
	m3(3,0) = 1; m3(3,1) = 4; m3(3,2) = 10; m3(3,3) = 20; 
	
	m3(0,4) = 1; m3(0,5) = 0; m3(0,6) = 0; m3(0,7) = 0;
	m3(1,4) = 0; m3(1,5) = 1; m3(1,6) = 0; m3(1,7) = 0;
	m3(2,4) = 0; m3(2,5) = 0; m3(2,6) = 1; m3(2,7) = 0;
	m3(3,4) = 0; m3(3,5) = 0; m3(3,6) = 0; m3(3,7) = 1;
	

	std::cout <<"右:入力　左:単位行列"<< std::endl;
	m3.show();
	m3.GaussJordan(true);
	std::cout <<"右:単位行列　左:出力(逆行列)"<< std::endl;
	m3.show();
*/	
	return 0;
}


