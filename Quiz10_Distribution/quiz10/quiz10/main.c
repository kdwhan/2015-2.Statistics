/*****************************************************************************
* Name		:	김대환
* Student ID:	20123338
* Quiz 10	:	Discrete Random Variable and Probability Distribution Table 

* Description: 이산확률변수 데이터를 사용하여 확률분포표 구조체를 만들고
				확률분포의 평균과 분산을 구하여 출력하는 프로그램
*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//데이터의 출력 형식과, 입력 형식을 설정하는 부분
#ifndef DATATYPE
#define DATATYPE
typedef int		EType;
typedef float	PType;
#endif

//Pair 구조체, 개수와 확률이 한 쌍으로 이루어진 구조체
#ifndef PAIR
#define PAIR
typedef struct {
	EType num;
	PType prob;
}Pair;
#endif

//PTable구조체, 확률분포의 평균 분산, 크기, 데이터들이 들어있는 구조체
#ifndef PTABLE
#define PTABLE
typedef struct {
	int size;
	float mean;
	float var;
	Pair **elem;
}PTable;
#endif

/*****************************************************************************
* Function : MakePTable(const int size)
* Description: PTable 구조체를 초기화 해주는 함수이다.
				인자로 받은 size는 확률분포표의 확률변수 개수이다.
*******************************************************************************/
static PTable *MakePTable(const int size);

/*****************************************************************************
* Function : MakeProbabilityDistributionTable(const EType *v1, const PType *v2, const int length)
* Description: PTable 구조체에 값들을 집어넣어주는 함수이다.
				v1은 Pair의 num들의 배열이고 v2는 Pair의 prob들의 배열이다.
				length는 확률변수의 개수이다. 
*******************************************************************************/
static PTable *MakeProbabilityDistributionTable(const EType *v1, const PType *v2, const int length);

/*****************************************************************************
* Function : ComputeMean(PTable *ptable)
* Description: ptable을 인자로 받아 ptable안의 이산확률의 평균을 계산해 주는 함수.
*******************************************************************************/
static void ComputeMean(PTable *ptable);

/*****************************************************************************
* Function : ComputeVariance(PTable *ptable)
* Description: ptable을 인자로 받아 ptable의 왁률 분포의 분산을 계산해 주는 함수.
*******************************************************************************/
static void ComputeVariance(PTable *ptable);

/*****************************************************************************
* Function : PrintProbabilityDistributionTable(PTable *ptable)
* Description: ptable을 인자로 받아 확률분포표를 출력해 주는 함수.
				전체 출력 format.
*******************************************************************************/
static void PrintProbabilityDistributionTable(PTable *ptable);

/*****************************************************************************
* Function : DestroyPTable(PTable *ptable)
* Description: ptable의 동적할당을 풀어주는 함수
*******************************************************************************/
static void DestroyPTable(PTable *ptable);

/*****************************************************************************
* Function : DestroyPair(Pair *elem)
* Description: pair의 동적할당을 풀어주는 함수
*******************************************************************************/
static void DestroyPair(Pair *elem);

int main(int argc, char *argv[])
{
	int v1[] = { 0, 1, 2, 3, 4, 5 };
	float v2[] = { 0.05f, 0.1f, 0.2f, 0.4f, 0.15f, 0.1f };
	PTable *table = NULL;
	table = MakeProbabilityDistributionTable(v1, v2, (sizeof(v1) / sizeof(int)));
	PrintProbabilityDistributionTable(table);
	ComputeMean(table);
	printf("Mean = %6.3f\n", table->mean);
	ComputeVariance(table);
	printf("Variance = %6.3f\n", table->var);
	DestroyPTable(table);
	return 0;
}

static PTable *MakePTable(const int size)
{
	PTable *out; //return value

	out = (PTable*)malloc(sizeof(PTable));
	out->size = size;
	out->mean = 0;
	out->var = 0;

	out->elem = (Pair**)malloc(sizeof(Pair*) * size);

	return out;
}
static PTable *MakeProbabilityDistributionTable(const EType *v1, const PType *v2, const int length)
{
	PTable *out; //return value
	out = MakePTable(length);

	for (int i = 0; i < length; i++)
	{
		out->elem[i] = (Pair*)malloc(sizeof(Pair));
		out->elem[i]->num = v1[i];
		out->elem[i]->prob = v2[i];
	}
	
	return out;
}
static void ComputeMean(PTable *ptable)
{
	for (int i = 0; i < ptable->size; i++)
	{
		ptable->mean += (ptable->elem[i]->prob * ptable->elem[i]->num);
	}
}
static void ComputeVariance(PTable *ptable)
{
	int i;
	float m=0;

	for (i = 0; i < ptable->size; i++)
	{
		ptable->var += (ptable->elem[i]->num - ptable->mean)*(ptable->elem[i]->num - ptable->mean)*(ptable->elem[i]->prob);
	}
}
static void PrintProbabilityDistributionTable(PTable *ptable)
{
	printf("	Probalility Distribution Table\n-----------------------------------------------------------\n");
	
	printf("  x   |");
	for (int i = 0; i < ptable->size; i++)
	{
		printf(" %4d ", ptable->elem[i]->num);
	}
	
	printf("\n p(x) |");
	for (int i = 0; i < ptable->size; i++)
	{
		printf(" %4.2f ", ptable->elem[i]->prob);
	}

	printf("\n\n");

}
static void DestroyPTable(PTable *ptable)
{
	for (int i = 0; i < ptable->size; i++)
		DestroyPair(ptable->elem[i]);

	free(ptable->elem);
	free(ptable);
}
static void DestroyPair(Pair *elem) 
{
	free(elem);
}