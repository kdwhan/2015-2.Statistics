/*****************************************************************************
* Main Heading
* Name		:	김대환
* Student ID:	20123338
* Quiz 4	: 도수, 상대도수, 누적도수, 상대 누적도수	

* Description: data를 받아 계급별 도수, 상대도수, 누적도수, 상대 누적도수
				그리고 합(1)을 출력하는 프로그램
*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

#define PATH_FILE "Personality.dat"

//데이터의 출력 형식과, 입력 형식을 설정하는 부분
#ifndef DATATYPE
#define DATATYPE
//#define SCANFORMAT "%f"
//#define PRNFORMAT "%10.6f"
#define SCANFORMAT "%d"
#define PRNFORMAT " %2d"
typedef int EType;
#endif

//DataSet구조체, 데이터의 행, 열, 개수와 데이터를 저장.
#ifndef DATASET
#define DATASET
typedef struct
{
	int rows;
	int cols;
	int length;
	EType *elem;
}DataSet;
#endif

//Personality구조체, 정렬된 데이터와 데이터의 도수, 상대도수, 계급수, 합(데이터의 수와 상대도수의 합)을 저장
#ifndef PERSONALITY
#define PERSONALITY
typedef struct
{
	EType *num;
	EType *freq;
	float *rel_freq;
	EType sum_freq, sum_rel, max;
}Personality;
#endif

/*****************************************************************************
* Function : CreateDataSet(const int rowsDataSet, const int colsDataSet, const int lengthDataSet)
* Description: 데이터의 행과 열 그리고 개수를 받아 dataSet구조체를 만들어 반환하는 함수.
*******************************************************************************/
static DataSet *CreateDataSet(const char *fileName);

/*****************************************************************************
* Function : DestoryData(DataSet *dataSet)
* Description: dataSet의 동적할당을 풀어주는 함수
*******************************************************************************/
static void DestroyDataSet(DataSet *dataSet);

/*****************************************************************************
* Function : static Personality *CreatePersonality(DataSet * dataSet)
* Description: data를 받아와 Personality 구조체를 만들어주는 함수
				정렬된 data를 저장하고 data의 도수, 상대도수, 계급수, 합들을 
				계산하여 저장한다.
*******************************************************************************/
static Personality *CreatePersonality(DataSet * dataSet);

/*****************************************************************************
* Function : static void PrintPersonality(Personality *p)
* Description: 계급별 개수, 도수, 상대도수, 누적도수, 상대 누적도수를 출력해주는 함수.
				전체 출력 format.
*******************************************************************************/
static void PrintPersonality(Personality *p);

/*****************************************************************************
* Function : PrintData(DataSet *dataSet)
* Description: dataSet을 받아와 데이터를 출력해주는 함수
*******************************************************************************/
static void PrintData(DataSet *dataSet);

/*****************************************************************************
* Function : SortQuick(EType *dataSet, const int posLeft, const int posRight)
* Description: 퀵정렬 함수이다. partition함수를 사용하여 범위를 나누고 합치며 정렬 해 나간다.
*******************************************************************************/
static void SortQuick(EType *dataSet, const int posLeft, const int posRight);

/*****************************************************************************
* Function : partition(EType *src, const int posLeft, const int posRight)
* Description: pivot을 설정하고 pivot보다 작은 값을 왼쪽, 큰 값을 오른쪽으로 옮긴다.
마지막으로 pivot의 위치를 반환하여 SortQuick에서 pivot 기준으로
양쪽으로 나눠 다시 반복 실행 할 수 있도록 한다.
*******************************************************************************/
static int partition(EType *src, const int posLeft, const int posRight);

int main(int argc, char argv[])
{
	DataSet *dt = CreateDataSet(PATH_FILE);
	PrintData(dt);

	Personality *personality;
	personality = CreatePersonality(dt);

	PrintPersonality(personality);

	return 0;
}

static Personality *CreatePersonality(DataSet * dataSet)
{
	Personality *out;// return
	int i=0, cnt=0, j=0;
	float sum;

	out = (Personality*)malloc(sizeof(Personality));

	SortQuick(dataSet->elem, 0, dataSet->length - 1);

	out->sum_freq = dataSet->length;
	out->sum_rel =0;
	out->max = dataSet->elem[dataSet->length - 1];

	out->num = (EType*)malloc(sizeof(EType) * out->max);
	out->freq = (EType*)malloc(sizeof(EType) * out->max);
	out->rel_freq = (float*)malloc(sizeof(float) * out->max);

	sum = out->sum_freq;

	while (1)
	{
		if (i == dataSet->length)
			break;
		else if (dataSet->elem[i] == dataSet->elem[i + 1])
		{
			cnt++;
			i++;
		}
		else
		{
			out->num[j] = dataSet->elem[i];
			out->freq[j] = cnt + 1;
			out->rel_freq[j] = (cnt+1) / sum;

			cnt = 0;
			j++;
			i++;
		}
	}
	return out;
}

static void PrintPersonality(Personality *p)
{
	int i;
	int i_sum = 0; // 누적도수
	float f_sum = 0; // 상대 누적도수

	printf("\nClass | Freq' | Rel-Freq' | Cum-Freq' | RelCum-Freq'\n");
	printf("------------------------------------------------------------------\n");

	i_sum = p->freq[0];
	f_sum = p->rel_freq[0];

	for (i = 0; i < p->max; i++)
	{

		printf("   %2d |\t   %2d |\t %f | \t  %3d |\t %f\n", p->num[i], p->freq[i], p->rel_freq[i], i_sum, f_sum);

		if (i != p->max - 1)
		{//누적도수, 상대누적도수 계산
			i_sum += p->freq[i + 1];
			f_sum += p->rel_freq[i + 1];
		}
	}
	printf("------------------------------------------------------------------\n");
	printf("  Sum |\t   %d|\t %f\n", p->sum_freq, f_sum);

}
static DataSet *CreateDataSet(const char *fileName)
{
	DataSet *out = NULL;//return
	FILE *inFile = NULL;
	EType *begin = NULL;
	EType *end = NULL;

	inFile = fopen(fileName, "r");
	if (!inFile)
		abort();

	out = (DataSet*)malloc(sizeof(DataSet));
	if (!out)
		abort();

	fscanf(inFile, "%d %d %d", &out->rows, &out->cols, &out->length);

	out->elem = (EType*)malloc(sizeof(EType)*out->length);
	if (!out->elem)
		abort();
	memset(out->elem, 0x00, (out->length * sizeof(EType)));

	begin = out->elem;
	end = out->elem + out->length;

	printf("%d %d %d\n", out->rows, out->cols, out->length);

	while (fscanf(inFile, "%d", begin++) != EOF)
	{
		if (begin == end)
			break;
	}
	fclose(inFile);
	return out;
}
static void DestroyDataSet(DataSet *dataSet)
{
	if (!dataSet)
		return;
	if (!dataSet->elem)
		goto DESTROY;

	free(dataSet->elem);
	dataSet->elem = NULL;

DESTROY:
	free(dataSet);
	dataSet = NULL;
}

static void PrintData(DataSet *dataSet)
{
	DataSet *setData = NULL;
	EType *begin = NULL;
	EType *end = NULL;

	int rows = 0, cols = 0;
	int col = 0;
	int length = 0;

	setData = dataSet;
	if (!setData) return;

	rows = setData->rows;
	cols = setData->cols;
	length = setData->length;

	begin = setData->elem;
	if (!begin) return;

	end = begin + length;

	for (col = 0; begin != end; begin++, col++)
	{
		if (col >= cols)
		{
			col = 0;
			printf("\n");
		}
		printf(PRNFORMAT, *begin); printf(" ");
	}
	printf("\n");
}

static void SortQuick(EType *dataSet, const int posLeft, const int posRight)
{
	int j;

	if (posLeft < posRight)
	{
		// divide and conquer
		j = partition(dataSet, posLeft, posRight);
		SortQuick(dataSet, posLeft, j - 1);//partition에서 받환한 값을 기준으로 왼쪽
		SortQuick(dataSet, j + 1, posRight);//pratition에서 반환한 값을 기준으로 오른쪽
	}
}
int partition(EType *src, const int posLeft, const int posRight)
{
	int pivot, l, r, t;

	pivot = src[posLeft];// 가장 왼쪽의 값을 pivot으로 설정
	l = posLeft; r = posRight + 1;// l=왼쪽 , r=오른쪽

	while (1)
	{
		do ++l; while (src[l] <= pivot && l <= posRight);
		do --r; while (src[r] > pivot);
		if (l >= r) break;
		t = src[l]; src[l] = src[r]; src[r] = t;
	}
	t = src[posLeft]; src[posLeft] = src[r]; src[r] = t;
	return r;
}