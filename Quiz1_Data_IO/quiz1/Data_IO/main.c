/*****************************************************************************
* Main Heading
* Name		:	김대환
* Student ID:	20123338
* Quiz 1	:	Data Input and Output
* Description:	행과 열의 개수, 데이터의 개수 와 데이터를 그대로 출력하는 프로그램.
*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#define PATH_FILE "input.txt"

//데이터의 출력 형식과, 입력 형식을 설정하는 부분
#ifndef DATATYPE
#define DATATYPE

#define SCANFORMAT "%f"		
#define PRNFORMAT "%10.6f"
typedef float EType;// 데이터의 자료형
//#define SCANFORMAT "%d"
//#define PRNFORMAT "%2d"
//typedef int EType;
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

/*****************************************************************************
* Function : ReadData(const char *fileName)
* Description: 파일의 이름을 받아와 그 파일의 데이터 구조체를 만들어 반환하는 함수
*******************************************************************************/
static DataSet *ReadData(const char *fileName);

/*****************************************************************************
* Subheading
* Function : DestoryData(DataSet *dataSet)
* Description: parameter로 받은 dataSet의 동적할당을 풀어주는 함수
*******************************************************************************/
static void DestoryData(DataSet *dataSet);

/*****************************************************************************
* Subheading
* Function : PrintData(DataSet *dataSet)
* Description: dataSet을 받아와 데이터를 출력해주는 함수
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
	begin = out->elem;// begin을 elem의 시작주소로 초기화
	end = out->elem + length;// end를 elem의 끝 주소로 초기화

	//파일의 끝 까지 데이터를 읽어 elem에 저장
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
	int col = 0, length = 0;

	setData = dataSet;
	if (!setData) return;

	rows = setData->rows;
	cols = setData->cols;
	length = setData->length;

	begin = setData->elem; // begin을 elem의 시작주소로 초기화
	if (!begin) return;

	end = begin + length;// end를 elem의 끝 주소로 초기화


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