/*****************************************************************************
* Name		:	���ȯ
* Student ID:	20123338
* Quiz 9	:	Permutation and Combination
* Description: ���ڿ��� ������ ������ ����ϴ� ���α׷�
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct setstrings SetStrings;
typedef struct setchars SetChars;

//setchars����ü, �����̳� ������ �Ѱ��� ��츦 �����ϴ� ����ü
struct setchars {
	int size;
	char* elems;
};

//setstrings����ü, �����̳� ���� ��ü�� �����ϴ� ����ü
struct setstrings {
	int size;
	SetChars* elems;
};

/*****************************************************************************
* Function : GetCardinality(SetChars* set)
* Description: ���ڷ� �޴� setstring ����ü�� ũ�⸦ ��ȯ�ϴ� �Լ�. ���� �̳� ���� ���� ���.
*******************************************************************************/
int GetCardinality(SetChars* set);

/*****************************************************************************
* Function : Combination(int n, int r)
* Description: Combination(����)�� ���ϴ� �Լ�. nCr.
*******************************************************************************/
int Combination(int n, int r);

/*****************************************************************************
* Function : Permutation(int n, int r)
* Description: Permutation(����)�� ���ϴ� �Լ�. nPr.
*******************************************************************************/
int Permutation(int n, int r);

/*****************************************************************************
* Function : *MakeCombination(SetChars *set, const int r)
* Description: ���ڿ��� Combination(����)�� ���ϴ� �Լ�.
*******************************************************************************/
SetStrings *MakeCombination(SetChars *set, const int r);

/*****************************************************************************
* Function : MakePermutation(SetChars *set, const int r)
* Description: ���ڿ��� Permutation(����)�� ���ϴ� �Լ�.
*******************************************************************************/
SetStrings *MakePermutation(SetChars *set, const int r);

/*****************************************************************************
* Function : PrintSetStrings(SetStrings* set)
* Description: ���ڿ��� ��� ���� Ȥ�� ������ ����ϴ� �Լ�
*******************************************************************************/
void PrintSetStrings(SetStrings* set);

/*****************************************************************************
* Function : PrintSetChars(SetChars* set)
* Description: ���ڿ��� ���� Ȥ�� ������ �� ��츦 ����ϴ� �Լ�
*******************************************************************************/
void PrintSetChars(SetChars* set);

/*****************************************************************************
* Function : DestroySetStrings(SetStrings* set)
* Description: ���ڷ� �޴� setStrings�� ����ü�� �����Ҵ��� �����ϴ� �Լ�
*******************************************************************************/
void DestroySetStrings(SetStrings* set);

/*****************************************************************************
* Function : DestroyChars(SetChars* set)
* Description: ���ڷ� �޴� setChars�� ����ü�� �����Ҵ��� �����ϴ� �Լ�
*******************************************************************************/
void DestroyChars(SetChars* set);

int main(void)
{
	SetChars setChars = { 4, "abcd" };
	SetStrings *permutationStrings = NULL;
	SetStrings *combinationStrings = NULL;

	permutationStrings = MakePermutation(&setChars, 2);
	combinationStrings = MakeCombination(&setChars, 3);

	printf("Permutation Strings = \n");
	PrintSetStrings(permutationStrings);
	//printf("Combination Strings = \n");
	//PrintSetStrings(combinationStrings);

	DestroySetStrings(permutationStrings);
	DestroySetStrings(combinationStrings);

	return 0;
}

int GetCardinality(SetChars* set)
{
	return set->size;
}

int Combination(int n, int r)
{
	int i;
	int total = Permutation(n, r);

	for (i = r; i > 0; --i)
		total /= i;

	return total;
}

int Permutation(int n, int r)
{
	int total = 1;
	int i;

	for (i = n; i >= n - r; --i)
		total *= i;

	return total;
}

SetStrings *MakeCombination(SetChars *set, const int r)
{
	int i, j;
	int k;
	int count;

	SetStrings *tempStrings = (SetStrings*)malloc(sizeof(SetStrings));
	tempStrings->size = Combination(set->size, r);
	tempStrings->elems = (SetChars*)malloc(sizeof(SetChars) * tempStrings->size);

	for (i = 0; i < tempStrings->size; ++i)
	{
		tempStrings->elems[i].size = r;
		tempStrings->elems[i].elems = (char*)malloc(sizeof(char) * (r + 1));
		k = i % set->size;
		count = 0;
		for (j = 0; j < set->size; ++j)
		{
			if (j != k)
			{
				tempStrings->elems[i].elems[count++] = set->elems[j];
				tempStrings->elems[i].elems[count] = '\0';
			}
		}
	}
}

SetStrings *MakePermutation(SetChars *set, const int r)
{
	int i;
	int k;
	SetStrings *tempStrings = (SetStrings*)malloc(sizeof(SetStrings));

	tempStrings->size = Permutation(set->size, r);
	tempStrings->elems = (SetChars*)malloc(sizeof(SetChars) * tempStrings->size);

	tempStrings->elems[0].elems = (char*)malloc(sizeof(char)*(set->size + 1));
	tempStrings->elems[0].size = set->size;
	strcpy(tempStrings->elems[0].elems, set->elems);

	for (i = 1; i < tempStrings->size; i++)
	{
		tempStrings->elems[i].size = set->size;
		tempStrings->elems[i].elems = (char*)malloc(sizeof(char)*(set->size + 1));
		strcpy(tempStrings->elems[i].elems, tempStrings->elems[i - 1].elems);

		k = i % (set->size - 1);
		if (k == 0) k = set->size - 1;

		Swap(tempStrings->elems[i].elems, 0, k);
	}
}

void PrintSetStrings(SetStrings* set)
{
	int i;

	for (i = 0; i < set->size; i++)
	{
		printf("%d. ", i);
		PrintSetChars(&set->elems[i]);
	}
	printf("\n");
}

void PrintSetChars(SetChars* set)
{
	printf("%s\n", set->elems);
}

void DestroySetStrings(SetStrings* set)
{
	int i;

	if (set == NULL)
		return;

	for (i = 0; i < set->size; i++)
	{
		DestroyChars(&set->elems[i]);
	}
	free(set->elems);
	free(set);
}

void DestroyChars(SetChars* set)
{
	if (set == NULL)
		return;
	free(set->elems);
}

void Swap(char *elem, int i, int j)
{
	char temp;
	temp = elem[i];
	elem[i] = elem[j];
	elem[j] = temp;
}
//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//////////////////////////////////////
//typedef struct setstring SetStrings;
//typedef struct setchars SetChars;
//typedef struct setchars {
//	int size;
//	char* elems;
//}SetChars;
//typedef struct setstring{
//	int size;
//	SetChars *elems;
//}SetStirngs;
/////////////////////////////////
//typedef struct set
//{
//	int size;
//	int *elem;
//}Set;
//
//typedef struct pair
//{
//	int x;
//	int y;
//}Pair;
//
//typedef struct cartesian // pair�� ������ ��� �ִ°�
//{
//	int size;
//	Pair **values;
//}Cartesian;
/////////////////////////////////////////////
//int getCardinality(Set* set);//�ϼ�
//int Combination(int n, int r);
//int Permutation(int n, int r);
//SetStrings *MakeComvination(SetChars *set, const int r);
//SetStrings *MakePermutation(SetChars *set, const int r);
//
//void PrintSetStrings(SetStrings* set);
//void PrintSetChars(SetChars* set);
//void DestroySetStrings(SetStrings* set);
//void DestroyChars(SetChars* set);
//
//
///////////////////////////////////////////
//int isExist(Set* set, int elem);
//
//void getUnion(Set* a, Set* b, Set** unionSet);
//void getIntersection(Set* a, Set* b, Set** intersectionSet);
//void getComplement(Set* u, Set* a, Set** complementSet);
//void getDifference(Set* a, Set* b, Set** differenceSet);
//void getSymmetricDifference(Set* a, Set* b, Set** symDifferenceSet);
//void getCartesianProduct(Set* a, Set* b, Cartesian** cartesianSet);
//
//void PrintSet(Set* set);
//void printCartesian(Cartesian* set);
//void freeSet(Set* set);
//void freeCartesian(Cartesian* set);
//
//int main(int argc, char* argv[])
//{
//	SetChars *sc1;
//	SetStrings *ss1;
//	int p1;
//
//	sc1 = (SetChars*)malloc(sizeof(SetChars));
//	sc1->size = 3;
//	sc1->elems = (char*)malloc(sizeof(char)*sc1->size);
//	sc1->elems[0] = 'a';
//	sc1->elems[1] = 'b';
//	sc1->elems[2] = 'c';
//
//	p1 = Permutation(sc1->size, sc1->size);
//
//	ss1 = MakePermutation(sc1, p1);
//
//	PrintSetStrings(ss1);
//
//	return 0;
//}
//
//int Combination(int n, int r)
//{
//
//	
//}
//int Permutation(int n, int r)
//{
//	int i, out=1;
//	for (i = 0; i < r; i++)
//	{
//		out *= n;
//
//		n -= 1;
//	}
//
//	return out;
//}
//SetStrings *MakeComvination(SetChars *set, const int r)
//{
//
//}
//SetStrings *MakePermutation(SetChars *set, const int r)
//{
//	int i, j;
//	int cnt;
//
//	SetStrings *out;// result
//
//	out = (SetStrings*)malloc(sizeof(SetStrings));
//
//	out->size = r;
//
//	out->elems = (SetChars*)malloc(sizeof(SetChars)*out->size);
//
//	cnt = out->size*set->size;
//
//	out->elems->elems = (char*)malloc(sizeof(char) * cnt);
//
//	
//	for (i = 0; i < out->size;i++)
//	{
//		for (j = 0; j < set->size; j++)
//		{
//
//		}
//	}
//
//	
//
//
//
//
//
//
//
//
//}
//
//void PrintSetStrings(SetStrings* set)
//{
//	int i;
//
//	printf("{" );
//
//	for (i = 0; i < set->size; i++)
//	{
//		
//	}
//}
//void PrintSetChars(SetChars* set)
//{
//
//}
//void DestroySetStrings(SetStrings* set)
//{
//
//}
//void DestroyChars(SetChars* set)
//{
//
//}
//
///////////////////////////////////////////////
//int isExist(Set* set, int elem)
//{
//	return set->elem[elem];
//}
//int getCardinality(Set* set)
//{
//	return set->size;
//}
//
//void getUnion(Set* a, Set* b, Set** unionSet)
//{
//	int i = 0;// unionSet�� elem �ε���
//	int ai = 0, bi = 0;// a,b �� elem �ε���
//
//	(*unionSet) = (Set*)malloc(sizeof(Set)); // set�� �� ũ�� �����Ҵ�
//	(*unionSet)->elem = malloc(sizeof(int) * (a->size + b->size));
//	(*unionSet)->size = 0;
//	while (ai < a->size && bi < b->size) // a �� b�� �ε��� �ȳѾ�� ����
//	{
//
//		if (a->elem[ai] == b->elem[bi])// a �� b �� ������ 
//		{
//			(*unionSet)->elem[i] = a->elem[ai];
//			ai++;
//			bi++;
//		}
//		else if (a->elem[ai] < b->elem[bi])//a�� ������
//		{
//			(*unionSet)->elem[i] = a->elem[ai];
//			ai++;
//		}
//		else//b�� ������
//		{
//			(*unionSet)->elem[i] = b->elem[bi];
//			bi++;
//		}
//		i++;
//		(*unionSet)->size++;
//	}
//
//	//a �� ��������
//	if (ai < a->size) {
//		while (ai < a->size)
//		{
//			(*unionSet)->elem[i] = a->elem[ai];
//			ai++;
//			i++;
//			(*unionSet)->size++;
//		}
//	}
//	//b�� ��������
//	if (bi < b->size) {
//		while (bi < b->size)
//		{
//			(*unionSet)->elem[i] = b->elem[bi];
//			bi++;
//			i++;
//			(*unionSet)->size++;
//		}
//	}
//
//}
//
//void getIntersection(Set* a, Set* b, Set** intersectionSet)
//{
//	int i, j;
//	int s = 0;// intersectionSet �� index
//	int temp;
//	(*intersectionSet) = (Set*)malloc(sizeof(Set));
//
//	if (a->size < b->size) temp = a->size;
//	else temp = b->size;
//	(*intersectionSet)->elem = (int*)malloc(sizeof(int) * temp); // ���� ���Ҵ� ���ƾ� ���� �迭�� ���Ҽ� 
//
//	(*intersectionSet)->size = 0;
//	for (i = 0; i < a->size; i++)
//	{
//		for (j = 0; j < b->size; j++)
//		{
//			if (a->elem[i] == b->elem[j])
//			{
//				(*intersectionSet)->elem[s] = a->elem[i];//������ ����ְ� ��������
//				(*intersectionSet)->size++;
//				s++;
//				break;
//			}
//		}
//	}
//}
//void getComplement(Set* u, Set* a, Set** complementSet)
//{
//	int i, j, check;
//	int ci = 0;
//	(*complementSet) = (Set*)malloc(sizeof(Set));
//	(*complementSet)->elem = (int*)malloc(sizeof(int)*((u->size) - (a->size)));
//	(*complementSet)->size = 0;
//	for (i = 0; i < u->size; i++)
//	{
//		check = 0;
//		for (j = 0; j < a->size; j++)
//		{// a�� �������� Ȯ��
//			if (a->elem[j] == u->elem[i]) {
//				check = 1;
//				break;
//			}
//		}
//
//		if (check != 1) { // �Ȱ������� ���� �ֱ�
//			(*complementSet)->elem[ci] = u->elem[i];
//			ci++;
//			((*complementSet)->size)++;
//		}
//	}
//
//}
//void getDifference(Set* a, Set* b, Set** differenceSet)
//{
//	int i, j, check;
//	int ci = 0;
//	(*differenceSet) = (Set*)malloc(sizeof(Set));
//	(*differenceSet)->elem = (int*)malloc(sizeof(int)*a->size);
//	(*differenceSet)->size = 0;
//	for (i = 0; i < a->size; i++)
//	{
//		check = 0;
//		for (j = 0; j < b->size; j++)
//		{
//			if (a->elem[i] == b->elem[j]) {
//				check = 1;
//				break;
//			}
//		}
//
//		if (check != 1) { // �Ȱ������� ���� �ֱ�
//			(*differenceSet)->elem[ci] = a->elem[i];
//			ci++;
//			((*differenceSet)->size)++;
//		}
//	}
//}
//void getSymmetricDifference(Set* a, Set* b, Set** symDifferenceSet)
//{
//	int ai = 0, bi = 0;
//	int k = 0; //index
//	int temp = a->size + b->size;
//	(*symDifferenceSet) = (Set*)malloc(sizeof(Set));
//	(*symDifferenceSet)->elem = (int*)malloc(sizeof(int) * temp); // ������ ������ �� a �� b�� �� 
//	(*symDifferenceSet)->size = 0;
//
//	while (ai < a->size && bi < b->size) // a �� b�� �ε��� �ȳѾ�� ����
//	{
//
//		if (a->elem[ai] == b->elem[bi])// a �� b �� ������ 
//		{
//			ai++;
//			bi++;
//			continue;
//		}
//		else if (a->elem[ai] < b->elem[bi])//a�� ������
//		{
//			(*symDifferenceSet)->elem[k] = a->elem[ai];
//			ai++;
//		}
//		else//b�� ������
//		{
//			(*symDifferenceSet)->elem[k] = b->elem[bi];
//			bi++;
//		}
//		k++;
//		(*symDifferenceSet)->size++;
//	}
//
//	//a �� ��������
//	if (ai < a->size) {
//		while (ai < a->size)
//		{
//			(*symDifferenceSet)->elem[k] = a->elem[ai];
//			ai++;
//			k++;
//			(*symDifferenceSet)->size++;
//		}
//	}
//	//b�� ��������
//	if (bi < b->size) {
//		while (bi < b->size)
//		{
//			(*symDifferenceSet)->elem[k] = b->elem[bi];
//			bi++;
//			k++;
//			(*symDifferenceSet)->size++;
//		}
//	}
//
//}
//void getCartesianProduct(Set* a, Set* b, Cartesian** cartesianSet)
//{
//	int temp = a->size * b->size;
//	int i, j, k = 0;
//	(*cartesianSet) = (Cartesian*)malloc(sizeof(Cartesian));
//	(*cartesianSet)->size = temp;
//	(*cartesianSet)->values = (Pair**)malloc(sizeof(Pair*) * temp);
//
//	for (i = 0; i < a->size; i++)
//	{
//		for (j = 0; j < b->size; j++)
//		{
//			(*cartesianSet)->values[k] = (Pair*)malloc(sizeof(Pair));
//			(*cartesianSet)->values[k]->x = a->elem[i];
//			(*cartesianSet)->values[k]->y = b->elem[j];
//			k++;
//		}
//	}
//}
//
//void PrintSet(Set* set)
//{
//	int i;
//
//	printf("< ");
//	for (i = 0; i < set->size; i++)
//	{
//		printf("%d, ", set->elem[i]);
//	}
//	printf(">\n");
//}
//void printCartesian(Cartesian* set)
//{
//	int i;
//	printf("< ");
//
//	for (i = 0; i < set->size; i++)
//	{
//		printf("<%d,%d>", set->values[i]->x, set->values[i]->y);
//	}
//	printf(" >");
//
//}
//void freeSet(Set* set)
//{
//	free(set->elem);
//	free(set);
//}
//void freeCartesian(Cartesian* set)
//{
//	int i;
//
//
//	for (i = 0; i < set->size; i++)
//	{
//		free(set->values[i]);
//	}
//	free(set->values);
//	free(set);
//
//
//}