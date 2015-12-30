/******************************************************************************
* Name		:	���ȯ
* Student ID:	20123338
* Quiz 2	:	Histogram ���

* Description:	������ ������׷��� ����ϴ� ���α׷��̴�. �����͸� �ް�
				����� ���۰� ��, ��ް��� ���̸� �����Ͽ� ��޺� �󵵼��� 
				����ϰ� ���� ���� �󵵼��� ����ŭ ���� ����Ͽ� �׷����� 
				����� ���α׷�.
				QuickSort�� ����Ͽ� �����͸� ������ �� �����͸� ���ʴ�� ������ 
				��޿� ���� ���� ������ ���� histogram�� ������ �� ����Ѵ�.
*******************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define PATH_FILE "sample.dat"

//�������� ��� ���İ�, �Է� ������ �����ϴ� �κ�
#ifndef DATATYPE
#define DATATYPE
//#define SCANFORMAT "%f"
//#define PRNFORMAT "%10.6f"
//typedef float EType
#define SCANFORMAT "%d"
#define PRNFORMAT " %2d"
typedef int EType;// �������� �ڷ���
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

} DataSet;
#endif

//Histogram ����ü, ����� ����(length)�� ��޺� �������� ���� ����(elem)
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
* Description: �����Ϳ� ����� �޾ƿ� �� ��޺� �󵵼��� ����Ͽ� histogram ����ü��
����� ��ȯ�ϴ� �Լ�.
*******************************************************************************/
static Histogram *CreateHistogram(DataSet *dataSet, const int minLevel, const int maxLevel, const int intervalLevel);

/******************************************************************************
* Function : DestoryHistogram(Histogram *histogram)
* Description: histogram�� �����Ҵ��� Ǯ���ִ� �Լ�
*******************************************************************************/
static void DestoryHistogram(Histogram *histogram);

/******************************************************************************
* Function : PrintHistogram(Histogram *histogram, const int minLevel, const int maxLevel, const int intervalLevel)
* Description: histogram ��� format�̴�. histogram�� ����Ѵ�. ��޺��� *ǥ�ø� ����Ͽ� ������׷� ���̱�.
*******************************************************************************/
static void PrintHistogram(Histogram *histogram, const int minLevel, const int maxLevel, const int intervalLevel);

/******************************************************************************
* Function : SortQuick(EType *dataSet, const int posLeft, const int posRight)
* Description: ������ �Լ��̴�. partition�Լ��� ����Ͽ� ������ ������ ��ġ�� ���� �� ������.
*******************************************************************************/
static void SortQuick(EType *dataSet, const int posLeft, const int posRight);

/******************************************************************************
* Function : partition(EType *src, const int posLeft, const int posRight)
* Description: pivot�� �����ϰ� pivot���� ���� ���� ����, ū ���� ���������� �ű��.
���������� pivot�� ��ġ�� ��ȯ�Ͽ� SortQuick���� pivot ��������
�������� ���� �ٽ� �ݺ� ���� �� �� �ֵ��� �Ѵ�.
*******************************************************************************/
int partition(EType *src, const int posLeft, const int posRight);

/******************************************************************************
* Function : ReadData(const char *fileName)
* Description: ������ �̸��� �޾ƿ� �� ������ ������ ����ü�� ����� ��ȯ�ϴ� �Լ�
*******************************************************************************/
static DataSet *ReadData(const char *fileName);

/******************************************************************************
* Function : DestoryData(DataSet *dataSet)
* Description: dataSet�� �����Ҵ��� Ǯ���ִ� �Լ�
*******************************************************************************/
static void DestoryData(DataSet *dataSet);

/******************************************************************************
* Function : PrintData(DataSet *dataSet)
* Description: dataSet�� �޾ƿ� �����͸� ������ִ� �Լ�
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
	his->length = (maxLevel - minLevel) / intervalLevel + 2;//����� ����
	his->elem = (int*)malloc(sizeof(int) * his->length);

	for (i = 0; i < his->length; i++)
		his->elem[i] = 0;

	SortQuick(dataSet->elem, 0, dataSet->length-1);

	PrintData(dataSet);

	for (i = 0; i < his->length; i++)
	{
		while (dataSet->elem[cnt] <= min_temp)//��ް� ������ ��
		{
			his->elem[i]++;
			cnt++;
		}

		min_temp += intervalLevel; //���� ���

		if (cnt != dataSet->length - 1 && min_temp > maxLevel+intervalLevel)//etc ���� �߰�
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
		{//histogram���
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
		SortQuick(dataSet, posLeft, j - 1);//partition���� ��ȯ�� ���� �������� ����
		SortQuick(dataSet, j + 1, posRight);//pratition���� ��ȯ�� ���� �������� ������
	}
}
int partition(EType *src, const int posLeft, const int posRight)
{
	int pivot, l, r, t;

	pivot = src[posLeft];// ���� ������ ���� pivot���� ����
	l = posLeft; r = posRight + 1;// l=���� , r=������

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

	begin = out->elem;// begin�� elem�� �����ּҷ� �ʱ�ȭ
	end = out->elem + length;// end�� elem�� �� �ּҷ� �ʱ�ȭ

	while (fscanf(inFile, SCANFORMAT, begin++) != EOF)
	{
		if (begin == end)// �����ּҰ� �� �ּҿ� �������� ����
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

	begin = setData->elem;// begin�� elem�� �����ּҷ� �ʱ�ȭ
	if (!begin) return;

	end = begin + length;// end�� elem�� �� �ּҷ� �ʱ�ȭ

	printf("Print DataSet\n");

	//����� ���� �ݺ���
	for (col = 0; begin != end; begin++, col++)
	{
		if (col >= cols)//������ ���� ����, ���� ������ŭ �Ǹ� ������ �Ѵ�.
		{
			col = 0;// ���� ������ ���� �ʱ�ȭ
			printf("\n");
		}
		printf(PRNFORMAT, *begin); printf(" ");//���
	}
	printf("\n");
}