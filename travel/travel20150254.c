#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//20150254 오현규

void travel(int n, int **W);
int minimum(int **W, int **D, int *O, int i, int *jj, int A, int n);
int subset(int k, int *O, int n);

int main(void){
	int i;
	int **A = (int**)malloc(sizeof(int*) * 5); //A 그래프 생성
	for (i = 0; i < 5; i++)
		A[i] = (int*)malloc(sizeof(int) * 5);
	A[1][1] = 0;
	A[1][2] = 2;
	A[1][3] = 9;
	A[1][4] = 1000000; // 무한대의 값을 1000000으로 표현
	A[2][1] = 1;
	A[2][2] = 0;
	A[2][3] = 6;
	A[2][4] = 4;
	A[3][1] = 1000000;
	A[3][2] = 7;
	A[3][3] = 0;
	A[3][4] = 8;
	A[4][1] = 6;
	A[4][2] = 3;
	A[4][3] = 1000000;
	A[4][4] = 0;

	int **B = (int**)malloc(sizeof(int*) * 6); //B 그래프 생성
	for (i = 0; i < 6; i++)
		B[i] = (int*)malloc(sizeof(int) * 6);
	B[1][1] = 0;
	B[1][2] = 2;
	B[1][3] = 1000000;
	B[1][4] = 1000000;
	B[1][5] = 4;
	B[2][1] = 1000000;
	B[2][2] = 0;
	B[2][3] = 1;
	B[2][4] = 4;
	B[2][5] = 3;
	B[3][1] = 1000000;
	B[3][2] = 6;
	B[3][3] = 0;
	B[3][4] = 3;
	B[3][5] = 3;
	B[4][1] = 5;
	B[4][2] = 1000000;
	B[4][3] = 2;
	B[4][4] = 0;
	B[4][5] = 6;
	B[5][1] = 1;
	B[5][2] = 1000000;
	B[5][3] = 1000000;
	B[5][4] = 7;
	B[5][5] = 0;

	int **C = (int**)malloc(sizeof(int*) * 4); //C 그래프 생성
	for (i = 0; i < 4; i++)
		C[i] = (int*)malloc(sizeof(int) * 4);
	C[1][1] = 0;
	C[1][2] = 1;
	C[1][3] = 1;
	C[2][1] = 2;
	C[2][2] = 0;
	C[2][3] = 4;
	C[3][1] = 5;
	C[3][2] = 3;
	C[3][3] = 0;
	travel(5, A); // travel(마디 개수 + 1, 배열), 그래프 A 출력
	travel(6, B); // 그래프 B 출력
	travel(4, C); //그래프 C 출력
	return 0;
}

void travel(int n, int **W) {
	int i, j = 0, k;
	int jj;//최적경로 계산시 필요한 변수
	int A, B, V = 0; // 부분집합 A, A의 원소 검사시 필요한 B, 전체집합 V
	int minlength = 0; //최소길이

	for (i = 2; i < n; i++)  //전체집합 V 계산
		V += (int)pow(2, i - 1);
	V += 1;

	//집합은 2진수의 합으로 표현한다.
	//ex) 원소 1, 2, 4를 가진 부분집합 A의 값은
	//A = 2^(1-1) + 2^(2-1) + 2^(4-1) = 1 + 2 + 4 = 7

	int *O = (int*)malloc(sizeof(int) * n);// 부분집합의 어떤 원소의 유무를 
	//0, 1로 판별해줌
	//ex) 원소 1과 3이 있다면 O[1] = 1, O[3] = 1;
	for (i = 0; i < n; i++) // O[]배열 모든 원소 0으로 만들기
		O[i] = 0;

	int **D = (int**)malloc(sizeof(int*) * n); //D[][]배열 생성
	for (i = 0; i < n; i++)
		D[i] = (int*)malloc(sizeof(int) * (int)(pow(2, n-1)));
	
	for (i = 0; i < n; i++) //D[][] 배열 모든 원소 0으로 만들기
		for (j = 0; j < pow(2, n - 1); j++)
			D[i][j] = 0;

	int **P = (int**)malloc(sizeof(int*) * n); //P[][]배열 생성
	for (i = 0; i < n; i++)
		P[i] = (int*)malloc(sizeof(int) * (int)(pow(2, n-1)));
	
	for (i = 2; i < n; i++)
		D[i][0] = W[i][1];
	
	for (k = 1; k < n - 2; k++) { // k = 부분집합 원소의 개수
		for (i = 1; i <= k; i++)
		{
				O[i] = 1;//원소가 k개인 부분집합 A를 가장 숫자가 낮은 원소(1,2,3...)순으로 넣어서 만들고 O[]배열도 이에 맞춰 0,1을 할당한다.
				if (O[i] == 1)
				{
					if (i == 1) // O배열에 맞춰 A부분집합을 2의 배수의 합으로 생성
						A = 1;
					else
						A += (int)pow(2, i - 1);
				}
		}
		for (; A < pow(2, n-1); A = subset(k, O, n)) {
			if (A == 0) break; //해당 갯수의 부분집합을 다 세서 다음 갯수를 세게 한다.
			B = A; //집합 A의 원소 검사용 B 생성
			if ((A & 1) == 0) // 원소 1이 없는지 확인
			{
				i = 2;
				for (B = B >> 1; i < n; B = B >> 1)
				{
					if ((B & 1) == 0) // i가 A에 속하지 않는지 확인
					{
						D[i][A] = minimum(W, D, O, i, &j, A, n);
						P[i][A] = j;
					}
					i++;
				}
			}
		}
	}
			O[1] = 0; // minimum함수 호출시 원소 1을 빼고 모두 검사하기 위해 넣은 코드
			for (i = 2; i < n; i++)
				O[i] = 1;
			D[1][V - 1] = minimum(W, D, O, 1, &j, V - 1, n);
			P[1][V - 1] = j;
			minlength = D[1][V - 1];
			
			i = 1; // 최적 경로 출력 준비
			j = V - 1;

			printf("최적 경로 : [v1, ");
			while (1) {
				jj = j;
				printf("v%d", P[i][j]);
				printf(", ");
				if (((j - (int)pow(2,P[i][j] - 1)) == 0) || (j == 1))
					break;

				if (P[i][j] == 1)
					j = j - 1;
				else
					j = j - (int)pow(2, P[i][j]-1);
				i = P[i][jj];
				
						
			}
			printf("v1]\n");
			printf("최단길이 : %d\n", minlength);
}

int minimum(int **W, int **D, int *O, int i, int *jj, int A, int n) {
	int vj, j, answer = 10000000;
	for (j = 1; j < n; j++)
		if (O[j] == 1)
		{
			if (j == 1)
				vj = 1;
			else
				vj = (int)pow(2, j - 1);
			
			if (answer > W[i][j] + D[j][A - vj])
			{		
				answer = W[i][j] + D[j][A - vj];
				*jj = j; //P 배열에 할당해줄 j값
			}
		}
	return answer;
}

int subset(int k, int *O, int n) {
	int check = 0, A = 0, i, j = 0;
	
	for (i = n - 1; i > 0; i--) { //가장 큰 번호의 원소부터 검사한다.
		
		if ((j == k))//특정 갯수의 부분집합을 다 검사했으므로 다음 갯수의 부분집합으로 넘어간다
		{
			for (i = 1; i < n; i++)
				O[i] = 0;
			return 0; // 0을 리턴해 해당 개수의 부분집합은 더 이상 없다는 걸 알려줌
		}
		
		if ((O[i] == 1) && (O[i+1] == 0) && (i != (n-1)))//
		{
			O[i] = 0; // 해당 원소를 집합에서 제외한다.
			O[i + 1] = 1; //해당 원소 다음 번호의 원소를 집합에 넣는다.
			i = i + 2;
				while (i < n)
				{
					if (j > 0)// 검사해온 번호중에 지나쳐온 원소가 있다면 그걸 다음 번호에 채운다.
					//ex) 전체집합이 원소 1~7의 합이고 원소 2,6,7을 지닌 부분집합이 있다면
					//끝 번호의 원소부터 검사할 때 가장 끝에 차있는 6,7은 넘어가고(2개를 넘어가므로 j 값이 2가 됨)
					//이후 2를 검사할 때 2를 빼고 다음 번호인 3 원소를 넣게 된후
					//이전에 2개를 지나쳐서 j 값이 2가 됬으므로 그 다음 번호 원소 2개(j값)인 4, 5를 각각 넣고(1이 되고)
					//이후 남은 뒷번호의 원소인 6, 7은 빼버린다(0이 된다).
					{	
						O[i] = 1; // j값이 0이 될 때까지 다음 번호의 원소들을 넣는 과정
						j--;
					}
					else 
						O[i] = 0; //뒷번호를 0으로 하는 과정
					i++;
				}

			for (i = 1; i < n; i++)
				if (O[i] == 1) //O 배열을 채운 후 그에 맞춰 부분집합 A의 값을 할당.
				{
					if (i == 1)
						A += 1;
					else
						A += (int)pow(2, i-1);
				}
			
			break;
		}
		
		if ((O[i] == 1)&&((O[i+1] == 1)||(i == (n-1)))) //원소가 끝 번호에 차 있어서 j값에 1을 더하고 그냥 넘어감
			j++;
		
	}
	return A;
}
