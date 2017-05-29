
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <vector>


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
				//m[k][j] /= m[k][k];
				m[k][j] = m[k][j] / m[k][k];
			
			for(int i=k+1;i<N;i++)
				for(int j=M-1;j>=k;j--)
					//m[i][j] += -m[i][k]*m[k][j];
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
				//m[k][j] /= m[k][k];
				m[k][j] = m[k][j] / m[k][k];
			
			for(int i=0;i<N;i++)
				for(int j=M-1;j>=k;j--)
					//if(i != k) m[i][j] += -m[i][k]*m[k][j];
					if(i != k) m[i][j] = m[i][j] - m[i][k]*m[k][j];
		}
		
	}

	void show(void){
		for(auto& p:m){
			for(auto& q:p) std::cout<< " " 
									<< std::scientific << std::setprecision(7)
									<< std::setw(15)   << q;//printf(" %.7e",q);
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

int main(void){

	std::cout << "Q 1" <<std::endl;
	Matrix<3,4> m;
	m(0,0) = 3; m(0,1) = 1; m(0,2) = 2; m(0,3) = 13;
	m(1,0) = 5; m(1,1) = 1; m(1,2) = 3; m(1,3) = 20;
	m(2,0) = 4; m(2,1) = 2; m(2,2) = 1; m(2,3) = 13;

	m.show();
	m.GaussJordan(false);
	m.show();

	
	std::cout << "Q 2float" <<std::endl;
	Matrix<3,4,float> m2 , m2p;
	m2(0,0) = 4; m2(0,1) = 2; m2(0,2) = 1; m2(0,3) = 11;
	m2(1,0) = 3; m2(1,1) = 1.500001; m2(1,2) = 2; m2(1,3) = 12.000002;
	m2(2,0) = 5; m2(2,1) = 1; m2(2,2) = 3; m2(2,3) = 16;

	m2p = m2;

	m2.show();
	m2.GaussJordan(false);
	m2.show();

	m2p.show();
	m2p.GaussJordan(true);
	m2p.show();


	std::cout << "Q 3" <<std::endl;
	Matrix<4,4*2> m3;
	m3(0,0) = 1; m3(0,1) = 1; m3(0,2) = 1;  m3(0,3) = 1;
	m3(1,0) = 1; m3(1,1) = 2; m3(1,2) = 3;  m3(1,3) = 4; 
	m3(2,0) = 1; m3(2,1) = 3; m3(2,2) = 6;  m3(2,3) = 10; 
	m3(3,0) = 1; m3(3,1) = 4; m3(3,2) = 10; m3(3,3) = 20; 
	
	m3(0,4) = 1; m3(0,5) = 0; m3(0,6) = 0; m3(0,7) = 0;
	m3(1,4) = 0; m3(1,5) = 1; m3(1,6) = 0; m3(1,7) = 0;
	m3(2,4) = 0; m3(2,5) = 0; m3(2,6) = 1; m3(2,7) = 0;
	m3(3,4) = 0; m3(3,5) = 0; m3(3,6) = 0; m3(3,7) = 1;
	
	m3.show();
	m3.GaussJordan(true);
	m3.show();
	
	return 0;
}


