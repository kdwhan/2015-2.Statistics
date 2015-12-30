/*****************************************************************************
* Name		:	김대환
* Student ID:	20123338
* Quiz  6	:	Linear Regression

* Description: 이변량 dataset을 사용하여 공분산과 상관계수를 계산하고
				최소제곱 회귀방정식을 사용하여 값을 구하는 프로그램입니다.
*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PATH_FILE "b.txt"

//데이터의 출력 형식과, 입력 형식을 설정하는 부분
#ifndef DATATYPE
#define DATATYPE
#define SCANFORMAT "%f"
#define PRNFORMAT "%7.3f "
typedef float EType;
#endif

//MultiVariateSet 구조체, 모든 데이터를 관리.
#ifndef MULTIVARIATE
#define MULTIVARIATE
typedef struct
{
	int rows;
	int cols;
	char **headers;
	int length;
	EType **elem;

	float meanX, meanY;
	float sdX, sdY;

} MultiVariateSet;
#endif

/*****************************************************************************
* Function : CreateMultiVariateSet(const char *filename)
* Description: 파일경로를 인자로 받아 파일안의 데이터를 multivariateSet 구조체로
				만들어 반환하는 함수.행과 열을 반대로 데이터를 만든다.
*******************************************************************************/
static MultiVariateSet *CreateMultiVariateSet(const char *filename);
/*****************************************************************************
* Function : DestroyMultiVariateSet(MultiVariateSet *variateSet)
* Description: multivariateSet의 동적할당을 풀어주는 함수
*******************************************************************************/
static void DestroyMultiVariateSet(MultiVariateSet *variateSet);

/*****************************************************************************
* Function : PrintMultiVariateSet(MultiVariateSet *variateSet)
* Description: 데이터를 출력해주는 함수. 데이터의 행과열을 반대로 출력해준다.
*******************************************************************************/
static void PrintMultiVariateSet(MultiVariateSet *variateSet);

/*****************************************************************************
* Function : ComputeCovariance(MultiVariateSet *variateSet)
* Description: 데이터셋의 공분산을 계산하여 반환하는 함수
*******************************************************************************/
static float ComputeCovariance(MultiVariateSet *variateSet);

/*****************************************************************************
* Function : ComputeCorrelation(MultiVariateSet *variateSet)
* Description: 데이터셋의 상관계수를 계산하여 반환하는 함수
*******************************************************************************/
static float ComputeCorrelation(MultiVariateSet *variateSet);

/*****************************************************************************
* Function : CalcuCheck(MultiVariateSet *variateSet)
* Description: 기울기와 intercept를 구하고 계산결과를 검증해보는 함수
*******************************************************************************/
static void CalcuCheck(MultiVariateSet *variateSet);

int main(int argc, char *argv[])
{
	MultiVariateSet *setVariate = NULL;

	setVariate = CreateMultiVariateSet(PATH_FILE);
	PrintMultiVariateSet(setVariate);
	printf("\n");
	
	printf("Covariance = %6.3f\n", ComputeCovariance(setVariate));
	printf("Correlation = %6.3f\n", ComputeCorrelation(setVariate));
	printf("\n");
	
	CalcuCheck(setVariate);
	DestroyMultiVariateSet(setVariate);

	return 0;
}

static MultiVariateSet *CreateMultiVariateSet(const char *filename)
{
	MultiVariateSet *mvs = NULL;//return
	FILE *inFile = NULL;
	int i, j;

	inFile = fopen(filename, "r");
	mvs = (MultiVariateSet*)malloc(sizeof(MultiVariateSet));
	fscanf(inFile, "%d %d %d", &mvs->rows, &mvs->cols, &mvs->length);
	
	mvs->headers = (char**)malloc(sizeof(char*) * 2);
	mvs->headers[0] = (char*)malloc(sizeof(char) * 3);
	mvs->headers[1] = (char*)malloc(sizeof(char) * 3);
	fgets(mvs->headers[0], 3, inFile);
	fgets(mvs->headers[0], 4, inFile);
	fgets(mvs->headers[1], 3, inFile);

	mvs->elem = (EType**)malloc(sizeof(EType*) * mvs->rows);
	mvs->elem[0] = (EType*)malloc(sizeof(EType) * mvs->cols);
	mvs->elem[1] = (EType*)malloc(sizeof(EType) * mvs->cols);

	for (i = 0; i < 2; i++)
		for (j = 0; j < 6; j++)
			fscanf(inFile, "%f", &mvs->elem[i][j]);

	return mvs;
}

static void DestroyMultiVariateSet(MultiVariateSet *variateSet)
{
	for (int i = 0; i < variateSet->rows; i++)
	{
		free(variateSet->elem[i]);
	}
	free(variateSet);
}

static void PrintMultiVariateSet(MultiVariateSet *variateSet)
{
	int i;
	printf("  (x)   |  (y)\n");
	printf("---------------------\n");

	for (i = 0; i < variateSet->cols; i++)
	{
		printf(PRNFORMAT, variateSet->elem[0][i]);
		printf(PRNFORMAT, variateSet->elem[1][i]);
		printf("\n");
	}
}

static float ComputeCovariance(MultiVariateSet *variateSet)
{
	float covar = 0;//return
	int i;

	variateSet->meanX = 0;
	variateSet->meanY = 0;
	for (i = 0; i < variateSet->cols; i++)
	{
		variateSet->meanX += variateSet->elem[0][i];
		variateSet->meanY += variateSet->elem[1][i];
	}
	variateSet->meanX /= 6;
	variateSet->meanY /= 6;

	for (int i = 0; i < variateSet->cols; i++)
	{
		covar += (variateSet->elem[0][i] - variateSet->meanX)*(variateSet->elem[1][i] - variateSet->meanY);
	}
	covar /= 6;

	return covar;
}

static float ComputeCorrelation(MultiVariateSet *variateSet)
{
	float correl = 0;//return
	int i;

	variateSet->sdX = 0;
	variateSet->sdY = 0;

	for (i = 0; i < variateSet->cols; i++)
	{
		variateSet->sdX += (variateSet->elem[0][i] - variateSet->meanX) * (variateSet->elem[0][i] - variateSet->meanX);
		variateSet->sdY += (variateSet->elem[1][i] - variateSet->meanY) * (variateSet->elem[1][i] - variateSet->meanY);
	}
	variateSet->sdX = sqrtf(variateSet->sdX);
	variateSet->sdY = sqrtf(variateSet->sdY);
	correl = (ComputeCovariance(variateSet) * 6) / (variateSet->sdX * variateSet->sdY);
	return correl;
}

static void CalcuCheck(MultiVariateSet *variateSet)
{
	int j = 0;
	float slope = 0;
	float intercept = 0;

	slope = ComputeCorrelation(variateSet) * variateSet->sdY / variateSet->sdX;//기울기
	intercept = variateSet->meanY - (slope * variateSet->meanX);

	printf("slope = %f\nintercept = %f\n\n", slope, intercept);

	//검증 계산
	for (j = 0; j < 6; j++)
	{
		printf("y = %6.3f \n", slope * variateSet->elem[0][j] + intercept);
	}
}