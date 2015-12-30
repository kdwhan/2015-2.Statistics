/*****************************************************************************
* Main Heading
* Name		:	���ȯ
* Student ID:	20123338
* Quiz 1	:	Data Input and Output
* Description:	��� ���� ����, �������� ���� �� �����͸� �״�� ����ϴ� ���α׷�.
*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#define PATH_FILE "input.txt"

//�������� ��� ���İ�, �Է� ������ �����ϴ� �κ�
#ifndef DATATYPE
#define DATATYPE

#define SCANFORMAT "%f"		
#define PRNFORMAT "%10.6f"
typedef float EType;// �������� �ڷ���
//#define SCANFORMAT "%d"
//#define PRNFORMAT "%2d"
//typedef int EType;
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

/*****************************************************************************
* Function : ReadData(const char *fileName)
* Description: ������ �̸��� �޾ƿ� �� ������ ������ ����ü�� ����� ��ȯ�ϴ� �Լ�
*******************************************************************************/
static DataSet *ReadData(const char *fileName);

/*****************************************************************************
* Subheading
* Function : DestoryData(DataSet *dataSet)
* Description: parameter�� ���� dataSet�� �����Ҵ��� Ǯ���ִ� �Լ�
*******************************************************************************/
static void DestoryData(DataSet *dataSet);

/*****************************************************************************
* Subheading
* Function : PrintData(DataSet *dataSet)
* Description: dataSet�� �޾ƿ� �����͸� ������ִ� �Լ�
*******************************************************************************/
static void PrintData(DataSet *dataSet);

int main(int argc, char *argv[])
{
	DataSet *setData = NULL; 
	setData = ReadData(PATH_FILE);
	PrintData(setData);
	printf("\n");
	DestoryData(setData);
	return 0;
}
static DataSet *ReadData(const char *fileName)
{
	DataSet *out = NULL; // Return
	FILE *inFile = NULL;
	EType *begin = NULL;
	EType *end = NULL;

	int rows = 0, cols = 0, length = 0;

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
	{
		abort();
	}
	memset(out->elem, 0x00, (length * sizeof(EType)));
	begin = out->elem;// begin�� elem�� �����ּҷ� �ʱ�ȭ
	end = out->elem + length;// end�� elem�� �� �ּҷ� �ʱ�ȭ

	//������ �� ���� �����͸� �о� elem�� ����
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
	int col = 0, length = 0;

	setData = dataSet;
	if (!setData) return;

	rows = setData->rows;
	cols = setData->cols;
	length = setData->length;

	begin = setData->elem; // begin�� elem�� �����ּҷ� �ʱ�ȭ
	if (!begin) return;

	end = begin + length;// end�� elem�� �� �ּҷ� �ʱ�ȭ


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