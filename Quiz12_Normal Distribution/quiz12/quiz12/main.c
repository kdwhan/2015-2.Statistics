/*****************************************************************************
* Name		:	김대환
* Student ID:	20123338
* Quiz 12	:	Normal Distribution

* Description: 데이터를 정규화 하고 표준정규분포표를 사용하여 표쥰정규분포 즉
				연속확률분포의 확률을 구하는 프로그램.
*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#ifndef BOOL
typedef int BOOL;
#define FALSE 0
#define TRUE !FALSE
#endif

//데이터의 출력 형식과, 입력 형식을 설정하는 부분
#ifndef DATATYPE
#define DATATYPE
#define SCANFORMAT "%f"
#define PRNFORMAT "%f"
typedef float EType;
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

#ifndef NDIST
#define NDIST(mat, row, col) (mat->elem[row*(mat->cols) + cols])
#endif

/*****************************************************************************
* Function : CreateNormDist(const int rowsDataSet, const int colsDataSet)
* Description: 표준정규분포표를 만들어 주는 함수. 행, 열을 인자로 받는다.
*******************************************************************************/
static DataSet *CreateNormDist(const int rowsDataSet, const int colsDataSet);

/*****************************************************************************
* Function : DestoryData(DataSet *dataSet)
* Description: dataSet의 동적할당을 풀어주는 함수
*******************************************************************************/
static void DestroyDataSet(DataSet *dataSet);

/*****************************************************************************
* Function : PrintDataSet(DataSet *dataSet)
* Description: dataSet을 받아와 데이터를 출력해주는 함수
*******************************************************************************/
static void PrintDataSet(DataSet *dataSet);

/*****************************************************************************
* Function : FindNormDist(const DataSet *dataSet, const float value)
* Description: 표준정규분포표에서 알맞은 값을 찾아주는 함수
				인자로 받은 value를 dataSet에서 찾아 반환한다.
*******************************************************************************/
static float FindNormDist(const DataSet *dataSet, const float value);

/*****************************************************************************
* Function : Standardize(const float mean, const float sd, const float v)
* Description: 인자로 받은 mean(평균)과 sd(분산)을 사용하여 v를 정규화 하는 함수
*******************************************************************************/
static float Standardize(const float mean, const float sd, const float v);


static float ComputeNormDistGt(const DataSet *dataSet, const float mean, const float sd, const float v);
static float ComputeNormDistGtLt(const DataSet *dataSet, const float mean, const float sd, const float v1, const float v2);
static float ComputeNormDistLt(const DataSet *dataSet, const float mean, const float sd, const float v1);

int main(int argc, char argv[])
{
	FILE *inFile = NULL;
	DataSet *setData = NULL;
	int i = 0;
	int rows = 0, cols = 0;
	inFile = fopen("normdist.txt", "r");
	if (!inFile) abort();
	fscanf(inFile, "%d%d", &rows, &cols);
	setData = CreateNormDist(rows, cols);
	
	for (i = 0; i < rows*cols; i++)
	{
		fscanf(inFile, "%f", &(setData->elem[i]));
	}
	fclose(inFile);
	
	PrintDataSet(setData);
	printf("\n");
	printf("\n");
	float mean = 500.f;
	float sd = 5.f;

	float prov = ComputeNormDistGt(setData, mean, sd, 510.f);
	printf("P(X > 510) = %f\n", prov);
	printf("\n");
	
	prov = ComputeNormDistLt(setData, mean, sd, 498.f);
	printf("P(X < 498) = %f\n", prov);
	printf("\n");
	
	prov = ComputeNormDistGtLt(setData, mean, sd, 491.f, 498.f);
	printf("P(491 < X < 498) = %f\n", prov);
	printf("\n");
	
	prov = ComputeNormDistGtLt(setData, mean, sd, 492.f, 514.f);
	printf("P(492 < X < 514) = %f\n", prov);
	printf("\n");
	DestroyDataSet(setData);
}


static DataSet *CreateNormDist(const int rowsDataSet, const int colsDataSet)
{
	DataSet *out = (DataSet*)malloc(sizeof(DataSet)); // return
	out->rows = rowsDataSet;
	out->cols = colsDataSet;
	out->length = rowsDataSet * colsDataSet;

	out->elem = (EType *)malloc(out->length * sizeof(EType));
	if (!out->elem)
	{
		abort();
	}
	memset(out->elem, 0x00, (out->length * sizeof(EType)));

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
static void PrintDataSet(DataSet *dataSet)
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

	printf("Print DataSet\n");

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
//평균 500 , 표준편차 5
static float FindNormDist(const DataSet *dataSet, const float value)
{
	int index = (value * 100);
	if (index < 0)
	{
		index = -index;
	}
	return dataSet->elem[index];
}
static float Standardize(const float mean, const float sd, const float v)
{
	return (v - mean) / sd;
}
static float ComputeNormDistGt(const DataSet *dataSet, const float mean, const float sd, const float v)
{
	float gt = Standardize(mean, sd, v);
	return 0.5 - FindNormDist(dataSet, gt);
}
static float ComputeNormDistGtLt(const DataSet *dataSet, const float mean, const float sd, const float v1, const float v2)
{
	float gt = Standardize(mean, sd, v1);
	float lt = Standardize(mean, sd, v2);

	if (gt < 0 && lt < 0)
		return FindNormDist(dataSet, gt) - FindNormDist(dataSet, lt);
	else if (gt > 0 && lt > 0)
		return FindNormDist(dataSet, lt) - FindNormDist(dataSet, gt);
	else
		return FindNormDist(dataSet,gt) + FindNormDist(dataSet,lt);
}
static float ComputeNormDistLt(const DataSet *dataSet, const float mean, const float sd, const float v)
{
	float lt = Standardize(mean, sd, v);
	return 0.5 - FindNormDist(dataSet, lt);
}

