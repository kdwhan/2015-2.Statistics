/*****************************************************************************
* Name		:	김대환
* Student ID:	20123338
* Quiz 7	:	Set Operations

* Description: 집합(set) 구조체를 여러개 만들어 합집합, 교집합, 차집합, 여집합
				Difference, SymmetricDifference, Cartesian 들을 구하여 출력하는 
				프로그램이다. 
*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//set구조체, 집합의 크기와, 원소들을 가지고 있다.
typedef struct set 
{
	int size;
	int *elem;
}Set;

//pair구조체, 정수형 변수 'x''y'를 가지고 있다.
typedef struct pair 
{
	int x;
	int y;
}Pair;

//cartesian구조체, pair들의 집합과 크기를 가지고 있다.
typedef struct cartesian
{
	int size;
	Pair **values;
}Cartesian;

/*****************************************************************************
* Function : isExist(Set* set, int elem)
* Description: 집합(set)안의 원소 elem이 존재하는지 확인하는 함수
*******************************************************************************/
int isExist(Set* set, int elem);

/*****************************************************************************
* Function : getCardinality(Set* set)
* Description: 집합(set)의 크기를 반환하는 함수
*******************************************************************************/
int getCardinality(Set* set);

/*****************************************************************************
* Function : getUnion(Set* a, Set* b, Set** unionSet)
* Description: 집합간 Union을 구하는 함수
				인자인 a 집합과 b 집합의 합집합을 계산하여 unionSet에 저장하는 함수
*******************************************************************************/
void getUnion(Set* a, Set* b, Set** unionSet);

/*****************************************************************************
* Function : getIntersection(Set* a, Set* b, Set** intersectionSet);
* Description: 집합간 Intersection을 구하는 함수
				인자인 a 집합과 b 집합의 교집합을 계산하여 intersectionSet에 저장하는 함수
*******************************************************************************/
void getIntersection(Set* a, Set* b, Set** intersectionSet);

/*****************************************************************************
* Function : getComplement(Set* u, Set* a, Set** complementSet)
* Description: 집합간 Complement를 구하는 함수
				인자인 u 집합으로 부터 a 집합을 뺀 결과를 complementSet에 저장하는 함수
*******************************************************************************/
void getComplement(Set* u, Set* a, Set** complementSet);

/*****************************************************************************
* Function : getDifference(Set* a, Set* b, Set** differenceSet)
* Description: 집합간 Difference를 구하는 함수
				인자인 a 집합으로 부터 b 집합과의 공통된 원소를 제외한 원소를 
				differenceSet에 저장하는 함수
*******************************************************************************/
void getDifference(Set* a, Set* b, Set** differenceSet);

/*****************************************************************************
* Function : getSymmetricDifference(Set* a, Set* b, Set** symDifferenceSet)
* Description: SymmetricDifference를 구하는 함수
				인자인 a 집합과 b 집합의 교집합을 제외한 모든 원소를 symDifferenceSet에 저장하는 함수
*******************************************************************************/
void getSymmetricDifference(Set* a, Set* b, Set** symDifferenceSet);

/*****************************************************************************
* Function : getCartesianProduct(Set* a, Set* b, Cartesian** cartesianSet)
* Description: 집합의 CartesianProduct를 구하는 함수
				인자인 a 집합과 b 집합의 Cartesian을 구하여 cartesianSet에 저장하는 함수
*******************************************************************************/
void getCartesianProduct(Set* a, Set* b, Cartesian** cartesianSet);

/*****************************************************************************
* Function : PrintSet(Set* set)
* Description: 집합의 원소들을 출력하는 함수
*******************************************************************************/
void PrintSet(Set* set);

/*****************************************************************************
* Function : printCartesian(Cartesian* set)
* Description: CartesianSet의 원소들을 출력하는 함수
*******************************************************************************/
void printCartesian(Cartesian* set);

/*****************************************************************************
* Function : freeSet(Set* set)
* Description: set 구조체의 동적할당을 해제하는 함수
*******************************************************************************/
void freeSet(Set* set);

/*****************************************************************************
* Function : freeCartesian(Cartesian* set)
* Description: Cartesian 구조체의 동적할당을 해제하는 함수
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
	int i = 0;// unionSet의 elem 인덱스
	int ai=0, bi=0;// a,b 의 elem 인덱스

	(*unionSet) = (Set*)malloc(sizeof(Set)); // set이 들어갈 크기 동적할당
	(*unionSet)->elem = malloc(sizeof(int) * (a->size + b->size));
	(*unionSet)->size = 0;
	while (ai < a->size && bi < b->size) // a 랑 b의 인덱스 안넘어가는 조건
	{	

		if (a->elem[ai] == b->elem[bi])// a 와 b 가 같을때 
		{
			(*unionSet)->elem[i] = a->elem[ai];
			ai++;
			bi++;
		}
		else if (a->elem[ai] < b->elem[bi])//a가 작을때
		{
			(*unionSet)->elem[i] = a->elem[ai];
			ai++;
		}
		else//b가 작을때
		{
			(*unionSet)->elem[i] = b->elem[bi];
			bi++;
		}
		i++;
		(*unionSet)->size++;
	}

	//a 가 남았을때
	if (ai < a->size) {
		while (ai < a->size)
		{
			(*unionSet)->elem[i] = a->elem[ai];
			ai++;
			i++;
			(*unionSet)->size++;
		}
	}
	//b가 남았을때
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
	int s=0;// intersectionSet 의 index
	int temp;
	(*intersectionSet) = (Set*)malloc(sizeof(Set));

	if (a->size < b->size) temp = a->size;
	else temp = b->size;
	(*intersectionSet)->elem = (int*)malloc(sizeof(int) * temp); // 같은 원소는 많아야 작은 배열은 원소수 

	(*intersectionSet)->size = 0;
	for (i = 0; i < a->size; i++)
	{
		for (j = 0; j < b->size; j++)
		{
			if (a->elem[i] == b->elem[j])
			{
				(*intersectionSet)->elem[s] = a->elem[i];//같은거 집어넣고 다음으로
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
		{// a랑 같은건지 확인
			if (a->elem[j] == u->elem[i]) {
				check = 1;
				break;
			}
		}

		if (check != 1) { // 안같을때만 집어 넣기
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

		if (check != 1) { // 안같을때만 집어 넣기
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
	(*symDifferenceSet)->elem = (int*)malloc(sizeof(int) * temp); // 교집합 없을때 는 a 와 b의 합 
	(*symDifferenceSet)->size = 0;

	while (ai < a->size && bi < b->size) // a 랑 b의 인덱스 안넘어가는 조건
	{

		if (a->elem[ai] == b->elem[bi])// a 와 b 가 같을때 
		{
			ai++;
			bi++;
			continue;
		}
		else if (a->elem[ai] < b->elem[bi])//a가 작을때
		{
			(*symDifferenceSet)->elem[k] = a->elem[ai];
			ai++;
		}
		else//b가 작을때
		{
			(*symDifferenceSet)->elem[k] = b->elem[bi];
			bi++;
		}
		k++;
		(*symDifferenceSet)->size++;
	}

	//a 가 남았을때
	if (ai < a->size) {
		while (ai < a->size)
		{
			(*symDifferenceSet)->elem[k] = a->elem[ai];
			ai++;
			k++;
			(*symDifferenceSet)->size++;
		}
	}
	//b가 남았을때
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