/******************************************************************************
* Name		:	김대환
* Student ID:	20123338
* Quiz 2	:	Histogram 출력

* Description:	엑셀의 히스토그램을 출력하는 프로그램이다. 데이터를 받고
				계급의 시작과 끝, 계급간의 차이를 설정하여 계급별 빈도수를 
				출력하고 보기 쉽게 빈도수의 수만큼 별을 출력하여 그래프를 
				만드는 프로그램.
				QuickSort를 사용하여 데이터를 정렬한 후 데이터를 차례대로 설정한 
				계급에 맞춰 가며 개수를 세려 histogram에 저장한 후 출력한다.
*******************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define PATH_FILE "sample.dat"

//데이터의 출력 형식과, 입력 형식을 설정하는 부분
#ifndef DATATYPE
#define DATATYPE
//#define SCANFORMAT "%f"
//#define PRNFORMAT "%10.6f"
//typedef float EType
#define SCANFORMAT "%d"
#define PRNFORMAT " %2d"
typedef int EType;// 데이터의 자료형
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

} DataSet;
#endif

//Histogram 구조체, 계급의 개수(length)와 계급별 데이터의 개수 저장(elem)
#ifndef HISTOGRAM
#define HISTOGRAM
typedef struct
{
	int length;
	int *elem;
}Histogram;
#endif

/******************************************************************************
* Function : CreateHistogram(DataSet *dataSet, const int minLevel, const int maxLevel, const int intervalLevel)
* Description: 데이터와 계급을 받아와 각 계급별 빈도수를 계산하여 histogram 구조체로
만들어 반환하는 함수.
*******************************************************************************/
static Histogram *CreateHistogram(DataSet *dataSet, const int minLevel, const int maxLevel, const int intervalLevel);

/******************************************************************************
* Function : DestoryHistogram(Histogram *histogram)
* Description: histogram의 동적할당을 풀어주는 함수
*******************************************************************************/
static void DestoryHistogram(Histogram *histogram);

/******************************************************************************
* Function : PrintHistogram(Histogram *histogram, const int minLevel, const int maxLevel, const int intervalLevel)
* Description: histogram 출력 format이다. histogram을 출력한다. 계급별로 *표시를 사용하여 히스토그램 보이기.
*******************************************************************************/
static void PrintHistogram(Histogram *histogram, const int minLevel, const int maxLevel, const int intervalLevel);

/******************************************************************************
* Function : SortQuick(EType *dataSet, const int posLeft, const int posRight)
* Description: 퀵정렬 함수이다. partition함수를 사용하여 범위를 나누고 합치며 정렬 해 나간다.
*******************************************************************************/
static void SortQuick(EType *dataSet, const int posLeft, const int posRight);

/******************************************************************************
* Function : partition(EType *src, const int posLeft, const int posRight)
* Description: pivot을 설정하고 pivot보다 작은 값을 왼쪽, 큰 값을 오른쪽으로 옮긴다.
마지막으로 pivot의 위치를 반환하여 SortQuick에서 pivot 기준으로
양쪽으로 나눠 다시 반복 실행 할 수 있도록 한다.
*******************************************************************************/
int partition(EType *src, const int posLeft, const int posRight);

/******************************************************************************
* Function : ReadData(const char *fileName)
* Description: 파일의 이름을 받아와 그 파일의 데이터 구조체를 만들어 반환하는 함수
*******************************************************************************/
static DataSet *ReadData(const char *fileName);

/******************************************************************************
* Function : DestoryData(DataSet *dataSet)
* Description: dataSet의 동적할당을 풀어주는 함수
*******************************************************************************/
static void DestoryData(DataSet *dataSet);

/******************************************************************************
* Function : PrintData(DataSet *dataSet)
* Description: dataSet을 받아와 데이터를 출력해주는 함수
*******************************************************************************/
static void PrintData(DataSet *dataSet);

int main(int argc, char *argv[])
{
	DataSet *setData = NULL;
	Histogram *histogram = NULL;

	setData = ReadData(PATH_FILE);
	PrintData(setData);
	printf("\n");

	histogram = CreateHistogram(setData, 40, 80, 5);
	
	if (!histogram)
		abort();

	PrintHistogram(histogram, 40, 80, 5);
	printf("\n");

	DestoryHistogram(histogram); 
	DestoryData(setData);
	return 0;
}
static Histogram *CreateHistogram(DataSet *dataSet, const int minLevel, const int maxLevel, const int intervalLevel)
{
	Histogram *his = NULL; // return
	int i, cnt = 0;
	int min_temp = minLevel;

	his = (Histogram*)malloc(sizeof(Histogram));
	his->length = (maxLevel - minLevel) / intervalLevel + 2;//계급의 개수
	his->elem = (int*)malloc(sizeof(int) * his->length);

	for (i = 0; i < his->length; i++)
		his->elem[i] = 0;

	SortQuick(dataSet->elem, 0, dataSet->length-1);

	PrintData(dataSet);

	for (i = 0; i < his->length; i++)
	{
		while (dataSet->elem[cnt] <= min_temp)//계급과 데이터 비교
		{
			his->elem[i]++;
			cnt++;
		}

		min_temp += intervalLevel; //다음 계급

		if (cnt != dataSet->length - 1 && min_temp > maxLevel+intervalLevel)//etc 개수 추가
			his->elem[i] += dataSet->length - cnt;
	}
	return his;
}
static void DestoryHistogram(Histogram *histogram)
{
	if (!histogram)
		return;
	if (!histogram->elem)
		goto DESTROY;
	free(histogram->elem);
	histogram->elem = NULL;
DESTROY:
	free(histogram);
	histogram = NULL;
}

static void PrintHistogram(Histogram *histogram, const int minLevel, const int maxLevel, const int intervalLevel)
{
	
	int i, j;
	printf("\tLevel    |  Freq'\n");
	printf("------------------------------------------------------------------------\n");
	
	for (i = 0; i < histogram->length; i++)
	{
		if (i == histogram->length - 1)//etc
			printf("\tetc<%3d> | ", histogram->elem[i]);
		else
			printf("\t%d <%3d> | ", minLevel+intervalLevel*i, histogram->elem[i]);

		for (j = 0; j < histogram->elem[i]; j++)
		{//histogram출력
			printf("*");
		}
		printf("\n");
	}
}
static void SortQuick(EType *dataSet, const int posLeft, const int posRight)
{
	int j;

	if (posLeft < posRight)
	{
		j = partition(dataSet, posLeft, posRight);// divide and conquer
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
static DataSet *ReadData(const char *fileName)
{
	DataSet *out = NULL; // Return
	FILE *inFile = NULL;
	EType *begin = NULL;
	EType *end = NULL;

	int rows = 0, cols = 0;
	int col = 0, length = 0;

	if (!(inFile = fopen(fileName, "r")))
		abort();

	out = (DataSet *)malloc(sizeof(DataSet));
	if (!out)
		abort();

	memset(out, 0x00, sizeof(DataSet));
	fscanf_s(inFile, "%d%d%d", &rows, &cols, &length);

	out->rows = rows;
	out->cols = cols;
	out->length = length;

	printf("%d %d %d\n", rows, cols, length);
	printf("\n");

	out->elem = (EType  *)malloc(length * sizeof(EType));

	if (!out->elem)
		abort();
	memset(out->elem, 0x00, (length * sizeof(EType)));

	begin = out->elem;// begin을 elem의 시작주소로 초기화
	end = out->elem + length;// end를 elem의 끝 주소로 초기화

	while (fscanf(inFile, SCANFORMAT, begin++) != EOF)
	{
		if (begin == end)// 시작주소가 끝 주소와 같아지면 종료
			break;
	}

	fclose(inFile);
	return out;
}
void DestoryData(DataSet *dataSet)
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

	begin = setData->elem;// begin을 elem의 시작주소로 초기화
	if (!begin) return;

	end = begin + length;// end를 elem의 끝 주소로 초기화

	printf("Print DataSet\n");

	//출력을 위한 반복문
	for (col = 0; begin != end; begin++, col++)
	{
		if (col >= cols)//개행을 위한 조건, 열의 개수만큼 되면 개행을 한다.
		{
			col = 0;// 다음 개행을 위해 초기화
			printf("\n");
		}
		printf(PRNFORMAT, *begin); printf(" ");//출력
	}
	printf("\n");
}