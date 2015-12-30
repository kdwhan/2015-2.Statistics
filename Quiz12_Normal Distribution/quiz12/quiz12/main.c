/*****************************************************************************
* Name		:	���ȯ
* Student ID:	20123338
* Quiz 12	:	Normal Distribution

* Description: �����͸� ����ȭ �ϰ� ǥ�����Ժ���ǥ�� ����Ͽ� ǥ�����Ժ��� ��
				����Ȯ�������� Ȯ���� ���ϴ� ���α׷�.
*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#ifndef BOOL
typedef int BOOL;
#define FALSE 0
#define TRUE !FALSE
#endif

//�������� ��� ���İ�, �Է� ������ �����ϴ� �κ�
#ifndef DATATYPE
#define DATATYPE
#define SCANFORMAT "%f"
#define PRNFORMAT "%f"
typedef float EType;
#endif

//DataSet����ü, �������� ��, ��, ������ �����͸� ����.
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
* Description: ǥ�����Ժ���ǥ�� ����� �ִ� �Լ�. ��, ���� ���ڷ� �޴´�.
*******************************************************************************/
static DataSet *CreateNormDist(const int rowsDataSet, const int colsDataSet);

/*****************************************************************************
* Function : DestoryData(DataSet *dataSet)
* Description: dataSet�� �����Ҵ��� Ǯ���ִ� �Լ�
*******************************************************************************/
static void DestroyDataSet(DataSet *dataSet);

/*****************************************************************************
* Function : PrintDataSet(DataSet *dataSet)
* Description: dataSet�� �޾ƿ� �����͸� ������ִ� �Լ�
*******************************************************************************/
static void PrintDataSet(DataSet *dataSet);

/*****************************************************************************
* Function : FindNormDist(const DataSet *dataSet, const float value)
* Description: ǥ�����Ժ���ǥ���� �˸��� ���� ã���ִ� �Լ�
				���ڷ� ���� value�� dataSet���� ã�� ��ȯ�Ѵ�.
*******************************************************************************/
static float FindNormDist(const DataSet *dataSet, const float value);

/*****************************************************************************
* Function : Standardize(const float mean, const float sd, const float v)
* Description: ���ڷ� ���� mean(���)�� sd(�л�)�� ����Ͽ� v�� ����ȭ �ϴ� �Լ�
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
//��� 500 , ǥ������ 5
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

