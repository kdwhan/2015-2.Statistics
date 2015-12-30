/*****************************************************************************
* Name		:	���ȯ
* Student ID:	20123338
* Quiz 7	:	Set Operations

* Description: ����(set) ����ü�� ������ ����� ������, ������, ������, ������
				Difference, SymmetricDifference, Cartesian ���� ���Ͽ� ����ϴ� 
				���α׷��̴�. 
*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//set����ü, ������ ũ���, ���ҵ��� ������ �ִ�.
typedef struct set 
{
	int size;
	int *elem;
}Set;

//pair����ü, ������ ���� 'x''y'�� ������ �ִ�.
typedef struct pair 
{
	int x;
	int y;
}Pair;

//cartesian����ü, pair���� ���հ� ũ�⸦ ������ �ִ�.
typedef struct cartesian
{
	int size;
	Pair **values;
}Cartesian;

/*****************************************************************************
* Function : isExist(Set* set, int elem)
* Description: ����(set)���� ���� elem�� �����ϴ��� Ȯ���ϴ� �Լ�
*******************************************************************************/
int isExist(Set* set, int elem);

/*****************************************************************************
* Function : getCardinality(Set* set)
* Description: ����(set)�� ũ�⸦ ��ȯ�ϴ� �Լ�
*******************************************************************************/
int getCardinality(Set* set);

/*****************************************************************************
* Function : getUnion(Set* a, Set* b, Set** unionSet)
* Description: ���հ� Union�� ���ϴ� �Լ�
				������ a ���հ� b ������ �������� ����Ͽ� unionSet�� �����ϴ� �Լ�
*******************************************************************************/
void getUnion(Set* a, Set* b, Set** unionSet);

/*****************************************************************************
* Function : getIntersection(Set* a, Set* b, Set** intersectionSet);
* Description: ���հ� Intersection�� ���ϴ� �Լ�
				������ a ���հ� b ������ �������� ����Ͽ� intersectionSet�� �����ϴ� �Լ�
*******************************************************************************/
void getIntersection(Set* a, Set* b, Set** intersectionSet);

/*****************************************************************************
* Function : getComplement(Set* u, Set* a, Set** complementSet)
* Description: ���հ� Complement�� ���ϴ� �Լ�
				������ u �������� ���� a ������ �� ����� complementSet�� �����ϴ� �Լ�
*******************************************************************************/
void getComplement(Set* u, Set* a, Set** complementSet);

/*****************************************************************************
* Function : getDifference(Set* a, Set* b, Set** differenceSet)
* Description: ���հ� Difference�� ���ϴ� �Լ�
				������ a �������� ���� b ���հ��� ����� ���Ҹ� ������ ���Ҹ� 
				differenceSet�� �����ϴ� �Լ�
*******************************************************************************/
void getDifference(Set* a, Set* b, Set** differenceSet);

/*****************************************************************************
* Function : getSymmetricDifference(Set* a, Set* b, Set** symDifferenceSet)
* Description: SymmetricDifference�� ���ϴ� �Լ�
				������ a ���հ� b ������ �������� ������ ��� ���Ҹ� symDifferenceSet�� �����ϴ� �Լ�
*******************************************************************************/
void getSymmetricDifference(Set* a, Set* b, Set** symDifferenceSet);

/*****************************************************************************
* Function : getCartesianProduct(Set* a, Set* b, Cartesian** cartesianSet)
* Description: ������ CartesianProduct�� ���ϴ� �Լ�
				������ a ���հ� b ������ Cartesian�� ���Ͽ� cartesianSet�� �����ϴ� �Լ�
*******************************************************************************/
void getCartesianProduct(Set* a, Set* b, Cartesian** cartesianSet);

/*****************************************************************************
* Function : PrintSet(Set* set)
* Description: ������ ���ҵ��� ����ϴ� �Լ�
*******************************************************************************/
void PrintSet(Set* set);

/*****************************************************************************
* Function : printCartesian(Cartesian* set)
* Description: CartesianSet�� ���ҵ��� ����ϴ� �Լ�
*******************************************************************************/
void printCartesian(Cartesian* set);

/*****************************************************************************
* Function : freeSet(Set* set)
* Description: set ����ü�� �����Ҵ��� �����ϴ� �Լ�
*******************************************************************************/
void freeSet(Set* set);

/*****************************************************************************
* Function : freeCartesian(Cartesian* set)
* Description: Cartesian ����ü�� �����Ҵ��� �����ϴ� �Լ�
*******************************************************************************/
void freeCartesian(Cartesian* set);

int main(int argc, char* argv[])
{
	int u[] = { 0,1,2,3,4,5,6,7,8,9,10 };
	int a[] = { 1,2,3,4,5 };
	int b[] = { 4,5,6,7,8 };
	int c[] = { 100, 200 };

	Set setU = { (sizeof(u) / sizeof(int)), u };
	Set setA = { (sizeof(a) / sizeof(int)), a };
	Set setB = { (sizeof(b) / sizeof(int)), b };
	Set setC = { (sizeof(c) / sizeof(int)), c };

	Set* unionSet = NULL;
	Set* intersectionSet = NULL;
	Set* complementSet1 = NULL;
	Set* complementSet2 = NULL;
	Set* differenceSet1 = NULL;
	Set* differenceSet2 = NULL;
	Set* symDifferenceSet = NULL;
	Cartesian* cartesianSet = NULL;

	getUnion(&setA, &setB, &unionSet);
	getIntersection(&setA, &setB, &intersectionSet);
	getComplement(&setU, &setA, &complementSet1);
	getComplement(&setU, &setB, &complementSet2);
	getDifference(&setA, &setB, &differenceSet1);
	getDifference(&setB, &setA, &differenceSet2);
	getSymmetricDifference(&setA, &setB, &symDifferenceSet);
	getCartesianProduct(&setA, &setC, &cartesianSet);

	printf("         <<Set Operations>>\n");
	printf("1.Union A and B\n");
	printf("= ");
	PrintSet(unionSet);
	printf("2. Intersection A and B\n");
	printf("= ");
	PrintSet(intersectionSet);
	printf("3.Complement A\n");
	printf("= ");
	PrintSet(complementSet1);
	printf("4.Complement B\n");
	printf("= ");
	PrintSet(complementSet2);
	printf("5. Difference A and B\n");
	printf("= ");
	PrintSet(differenceSet1);
	printf("6. Difference A and A\n");
	printf("= ");
	PrintSet(differenceSet2);
	printf("7.SymmetricDifference A and B\n");
	printf("= ");
	PrintSet(symDifferenceSet);
	printf("8. Cartesian Product A and C\n");
	printf("= ");
	printCartesian(cartesianSet);

	freeSet(unionSet);
	freeSet(intersectionSet);
	freeSet(complementSet1);
	freeSet(complementSet2);
	freeSet(differenceSet1);
	freeSet(differenceSet2);
	freeSet(symDifferenceSet);
	freeCartesian(cartesianSet);

	return 0;
}


int isExist(Set* set, int elem)
{
	return set->elem[elem];
}
int getCardinality(Set* set)
{
	return set->size;
}

void getUnion(Set* a, Set* b, Set** unionSet) 
{
	int i = 0;// unionSet�� elem �ε���
	int ai=0, bi=0;// a,b �� elem �ε���

	(*unionSet) = (Set*)malloc(sizeof(Set)); // set�� �� ũ�� �����Ҵ�
	(*unionSet)->elem = malloc(sizeof(int) * (a->size + b->size));
	(*unionSet)->size = 0;
	while (ai < a->size && bi < b->size) // a �� b�� �ε��� �ȳѾ�� ����
	{	

		if (a->elem[ai] == b->elem[bi])// a �� b �� ������ 
		{
			(*unionSet)->elem[i] = a->elem[ai];
			ai++;
			bi++;
		}
		else if (a->elem[ai] < b->elem[bi])//a�� ������
		{
			(*unionSet)->elem[i] = a->elem[ai];
			ai++;
		}
		else//b�� ������
		{
			(*unionSet)->elem[i] = b->elem[bi];
			bi++;
		}
		i++;
		(*unionSet)->size++;
	}

	//a �� ��������
	if (ai < a->size) {
		while (ai < a->size)
		{
			(*unionSet)->elem[i] = a->elem[ai];
			ai++;
			i++;
			(*unionSet)->size++;
		}
	}
	//b�� ��������
	if (bi < b->size) {
		while (bi < b->size) 
		{
			(*unionSet)->elem[i] = b->elem[bi];
			bi++;
			i++;
			(*unionSet)->size++;
		}
	}
	
}

void getIntersection(Set* a, Set* b, Set** intersectionSet)
{
	int i, j;
	int s=0;// intersectionSet �� index
	int temp;
	(*intersectionSet) = (Set*)malloc(sizeof(Set));

	if (a->size < b->size) temp = a->size;
	else temp = b->size;
	(*intersectionSet)->elem = (int*)malloc(sizeof(int) * temp); // ���� ���Ҵ� ���ƾ� ���� �迭�� ���Ҽ� 

	(*intersectionSet)->size = 0;
	for (i = 0; i < a->size; i++)
	{
		for (j = 0; j < b->size; j++)
		{
			if (a->elem[i] == b->elem[j])
			{
				(*intersectionSet)->elem[s] = a->elem[i];//������ ����ְ� ��������
				(*intersectionSet)->size++;
				s++;
				break;
			}
		}
	}
}
void getComplement(Set* u, Set* a, Set** complementSet)
{
	int i, j, check;
	int ci=0;
	(*complementSet) = (Set*)malloc(sizeof(Set));
	(*complementSet)->elem = (int*)malloc(sizeof(int)*((u->size)-(a->size)));
	(*complementSet)->size = 0;
	for (i = 0; i < u->size; i++)
	{
		check = 0;
		for (j = 0; j < a->size; j++)
		{// a�� �������� Ȯ��
			if (a->elem[j] == u->elem[i]) {
				check = 1;
				break;
			}
		}

		if (check != 1) { // �Ȱ������� ���� �ֱ�
			(*complementSet)->elem[ci] = u->elem[i];
			ci++;
			((*complementSet)->size)++;
		}
	}

}
void getDifference(Set* a, Set* b, Set** differenceSet)
{
	int i, j, check;
	int ci = 0;
	(*differenceSet) = (Set*)malloc(sizeof(Set));
	(*differenceSet)->elem = (int*)malloc(sizeof(int)*a->size);
	(*differenceSet)->size = 0;
	for (i = 0; i < a->size; i++)
	{
		check = 0;
		for (j = 0; j < b->size; j++)
		{
			if (a->elem[i] == b->elem[j]) {
				check = 1;
				break;
			}
		}

		if (check != 1) { // �Ȱ������� ���� �ֱ�
			(*differenceSet)->elem[ci] = a->elem[i];
			ci++;
			((*differenceSet)->size)++;
		}
	}
}
void getSymmetricDifference(Set* a, Set* b, Set** symDifferenceSet)
{
	int ai=0, bi=0;
	int k = 0; //index
	int temp = a->size + b->size;
	(*symDifferenceSet) = (Set*)malloc(sizeof(Set));
	(*symDifferenceSet)->elem = (int*)malloc(sizeof(int) * temp); // ������ ������ �� a �� b�� �� 
	(*symDifferenceSet)->size = 0;

	while (ai < a->size && bi < b->size) // a �� b�� �ε��� �ȳѾ�� ����
	{

		if (a->elem[ai] == b->elem[bi])// a �� b �� ������ 
		{
			ai++;
			bi++;
			continue;
		}
		else if (a->elem[ai] < b->elem[bi])//a�� ������
		{
			(*symDifferenceSet)->elem[k] = a->elem[ai];
			ai++;
		}
		else//b�� ������
		{
			(*symDifferenceSet)->elem[k] = b->elem[bi];
			bi++;
		}
		k++;
		(*symDifferenceSet)->size++;
	}

	//a �� ��������
	if (ai < a->size) {
		while (ai < a->size)
		{
			(*symDifferenceSet)->elem[k] = a->elem[ai];
			ai++;
			k++;
			(*symDifferenceSet)->size++;
		}
	}
	//b�� ��������
	if (bi < b->size) {
		while (bi < b->size)
		{
			(*symDifferenceSet)->elem[k] = b->elem[bi];
			bi++;
			k++;
			(*symDifferenceSet)->size++;
		}
	}

}
void getCartesianProduct(Set* a, Set* b, Cartesian** cartesianSet)
{
	int temp = a->size * b->size;
	int i, j, k = 0;
	(*cartesianSet) = (Cartesian*)malloc(sizeof(Cartesian));
	(*cartesianSet)->size = temp;
	(*cartesianSet)->values = (Pair**)malloc(sizeof(Pair*) * temp);

	for (i = 0; i < a->size; i++)
	{
		for (j = 0; j < b->size; j++)
		{
			(*cartesianSet)->values[k] = (Pair*)malloc(sizeof(Pair));
			(*cartesianSet)->values[k]->x = a->elem[i];
			(*cartesianSet)->values[k]->y = b->elem[j];
			k++;
		}
	}
}

void PrintSet(Set* set)
{
	int i;

	printf("< ");
	for (i = 0; i < set->size; i++)
	{
		printf("%d, ", set->elem[i]);
	}
	printf(">\n");
}
void printCartesian(Cartesian* set)
{
	int i;
	printf("< ");

	for (i = 0; i < set->size; i++)
	{
		printf("<%d,%d>", set->values[i]->x, set->values[i]->y);
	}
	printf(" >\n");

}
void freeSet(Set* set)
{
	free(set->elem);
	free(set);
}
void freeCartesian(Cartesian* set)
{
	int i;

	for (i = 0; i < set->size; i++)
	{
		free(set->values[i]);
	}
	free(set->values);
	free(set);
}