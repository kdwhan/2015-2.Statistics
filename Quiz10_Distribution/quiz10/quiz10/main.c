/*****************************************************************************
* Name		:	���ȯ
* Student ID:	20123338
* Quiz 10	:	Discrete Random Variable and Probability Distribution Table 

* Description: �̻�Ȯ������ �����͸� ����Ͽ� Ȯ������ǥ ����ü�� �����
				Ȯ�������� ��հ� �л��� ���Ͽ� ����ϴ� ���α׷�
*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//�������� ��� ���İ�, �Է� ������ �����ϴ� �κ�
#ifndef DATATYPE
#define DATATYPE
typedef int		EType;
typedef float	PType;
#endif

//Pair ����ü, ������ Ȯ���� �� ������ �̷���� ����ü
#ifndef PAIR
#define PAIR
typedef struct {
	EType num;
	PType prob;
}Pair;
#endif

//PTable����ü, Ȯ�������� ��� �л�, ũ��, �����͵��� ����ִ� ����ü
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
* Description: PTable ����ü�� �ʱ�ȭ ���ִ� �Լ��̴�.
				���ڷ� ���� size�� Ȯ������ǥ�� Ȯ������ �����̴�.
*******************************************************************************/
static PTable *MakePTable(const int size);

/*****************************************************************************
* Function : MakeProbabilityDistributionTable(const EType *v1, const PType *v2, const int length)
* Description: PTable ����ü�� ������ ����־��ִ� �Լ��̴�.
				v1�� Pair�� num���� �迭�̰� v2�� Pair�� prob���� �迭�̴�.
				length�� Ȯ�������� �����̴�. 
*******************************************************************************/
static PTable *MakeProbabilityDistributionTable(const EType *v1, const PType *v2, const int length);

/*****************************************************************************
* Function : ComputeMean(PTable *ptable)
* Description: ptable�� ���ڷ� �޾� ptable���� �̻�Ȯ���� ����� ����� �ִ� �Լ�.
*******************************************************************************/
static void ComputeMean(PTable *ptable);

/*****************************************************************************
* Function : ComputeVariance(PTable *ptable)
* Description: ptable�� ���ڷ� �޾� ptable�� �η� ������ �л��� ����� �ִ� �Լ�.
*******************************************************************************/
static void ComputeVariance(PTable *ptable);

/*****************************************************************************
* Function : PrintProbabilityDistributionTable(PTable *ptable)
* Description: ptable�� ���ڷ� �޾� Ȯ������ǥ�� ����� �ִ� �Լ�.
				��ü ��� format.
*******************************************************************************/
static void PrintProbabilityDistributionTable(PTable *ptable);

/*****************************************************************************
* Function : DestroyPTable(PTable *ptable)
* Description: ptable�� �����Ҵ��� Ǯ���ִ� �Լ�
*******************************************************************************/
static void DestroyPTable(PTable *ptable);

/*****************************************************************************
* Function : DestroyPair(Pair *elem)
* Description: pair�� �����Ҵ��� Ǯ���ִ� �Լ�
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