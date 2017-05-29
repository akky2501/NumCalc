
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


	// ピボッティングなしドゥーリトル法
	void DoolittleWithoutPivoting(Matrix<N,M,T>* l,Matrix<N,M,T>* u){
		for(int k=0;k<N-1;k++){ // if submat = 2x2 then finish
			for(int j=k+1;j<M;j++) m[k][j] = m[k][j] / m[k][k];
			
			for(int i=k+1;i<N;i++){
				for(int j=k+1;j<M;j++){
					m[i][j] = m[i][j] - m[i][k]*m[k][j];
				}
			}
		}

		for(int i=0;i<N;i++)
			for(int j=0;j<=i;j++)
				l->m[i][j] = m[i][j];

		for(int i=0;i<N;i++)
			for(int j=i+1;j<M;j++)
				u->m[i][j] = m[i][j];
		for(int i=0;i<N;i++)
			u->m[i][i] = 1;
	}

	void solveL(Matrix<N,1,T>* v){
		for(int t=0;t<N;t++){
			(*v)(t,0) = (*v)(t,0) / m[t][t];
			m[t][t] = m[t][t] / m[t][t]; // 1

			for(int k=t+1;k<N;k++) (*v)(k,0) = (*v)(k,0) - m[k][t] * (*v)(t,0);
			for(int i=t+1;i<N;i++)
				m[i][t] = m[i][t] - m[i][t]*m[t][t]; // 0
		}
	}

	void solveU(Matrix<N,1,T>* v){
		for(int t=N-1;t>=0;t--){
			(*v)(t,0) = (*v)(t,0) / m[t][t];
			m[t][t] = m[t][t] / m[t][t]; // 1

			for(int k=t-1;k>=0;k--) (*v)(k,0) = (*v)(k,0) - m[k][t] * (*v)(t,0);
			for(int i=t-1;i>=0;i--)
				m[i][t] = m[i][t] - m[i][t]*m[t][t]; // 0
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
};



int main(void){

	std::cout << "Dolittle for LU decomposition." <<std::endl;
	
	Matrix<4,4,int> m,l,u;
	m(0,0) = 1; m(0,1) =  8; m(0,2) =  1; m(0,3) =  0;
	m(1,0) = 1; m(1,1) = 12; m(1,2) =  9; m(1,3) = 20;
	m(2,0) = 5; m(2,1) = 41; m(2,2) = 11; m(2,3) = 13;
	m(3,0) = 1; m(3,1) = 17; m(3,2) = 20; m(3,3) = 56;

	std::cout <<"input"<< std::endl;
	m.show();

	m.DoolittleWithoutPivoting(&l,&u);
	
	std::cout <<"output L"<< std::endl;
	l.show();
	
	std::cout <<"output U"<< std::endl;
	u.show();

	std::cout << "" <<std::endl;
	Matrix<4,1,int> b;
	b(0,0) = 20;
	b(1,0) = 132;
	b(2,0) = 172;
	b(3,0) = 319;
	b.show();
	
	l.solveL(&b);
	b.show();

	u.solveU(&b);
	b.show();


	return 0;
}


