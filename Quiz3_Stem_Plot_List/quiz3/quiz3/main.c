/*****************************************************************************
* Name		:	김대환
* Student ID:	20123338
* Quiz 3-1	:	Stem and leaf

* Description: 십의 자리 숫자를 줄기(stem)으로 하여 작은 수부터 순서대로 나열하고
				오른쪽에는 각 줄기에 해당하는 일의 자리 숫자를 잎(leaf)로 가로로 나열한다.
				중복된 자료의 값은 중복된 횟수만큼 나열한다.
*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

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

} DataSet;
#endif

//StemNode구조체, 줄기, 잎의개수, 잎, 다음 줄기를 저장.
#ifndef STEMNODE
#define STEMNODE
typedef struct stemnode
{
	int stem;
	int freq;
	EType *leaf;
	struct stemnode *next;
}StemNode;
#endif

//StemPlotList구조체, StemNode들을 관리, 시작 StemNode와 끝 StemNode를 저장.
#ifndef STEMLOTLIST
#define STEMPLOSTLIST
typedef struct
{
	StemNode *head;
	StemNode *tail;
}StemPlotList;
#endif

/*****************************************************************************
* Function : CreateDataSet(const int rowsDataSet, const int colsDataSet, const int lengthDataSet)
* Description: 데이터의 행과 열 그리고 개수를 받아 dataSet구조체를 만들어 반환하는 함수.
*******************************************************************************/
static DataSet *CreateDataSet(const int rowsDataSet, const int colsDataSet, const int lengthDataSet);

/*****************************************************************************
* Function : DestoryData(DataSet *dataSet)
* Description: dataSet의 동적할당을 풀어주는 함수
*******************************************************************************/
static void DestroyDataSet(DataSet *dataSet);

/*****************************************************************************
* Function : CreateStemNode(const int elemSize, const int stemValue)
* Description: StemNode 구조체를 만들어 반환하는 함수. 줄기 값과 빈도수를 받아와 설정한다.
*******************************************************************************/
static StemNode *CreateStemNode(const int elemSize, const int stemValue);

/*****************************************************************************
* Function : DestoryStemNode(StemNode *stemNode)
* Description: stemNode의 동적할당을 풀어주는 함수
*******************************************************************************/
static void DestroyStemNode(StemNode *stemNode);

/*****************************************************************************
* Function : CreateStemNode(const int elemSize, const int stemValue)
* Description: StemPlotList 구조체를 만들어 반환하는 함수.
*******************************************************************************/
static StemPlotList *CreateStemPlotList(void);

/*****************************************************************************
* Function : DestoryStemPlotList(StemPlotList *stemPlotList)
* Description: stemPlotList의 동적할당을 풀어주는 함수
*******************************************************************************/
static void DestroyStemPlotList(StemPlotList *stemPlotList);

/*****************************************************************************
* Function : ComputeStemPlotList(StemPlotList *stemPlotList, DataSet * dataSet)
* Description: dataSet을 사용하여 StemNode를 만들어 StemPlotList에 추가해 StemPlotList를 완성하는 함수
*******************************************************************************/
static StemPlotList* ComputeStemPlotList(DataSet * dataSet);

/*****************************************************************************
* Function : AddStemNode(StemPlotList *stemPlotList, StemNode *stemNode)
* Description: StemNode를 StemPlotList에 추가해 주는 함수.
*******************************************************************************/
static void AddStemNode(StemPlotList *stemPlotList, StemNode *stemNode);

/*****************************************************************************
* Function : PrintLeaf(StemNode *stemNode)
* Description: stemNode의 leaf(잎)을 출력해주는 함수
*******************************************************************************/
static void PrintLeaf(StemNode *stemNode);

/*****************************************************************************
* Function : PrintStemPlotList(StemPlotList *stemPlotList)
* Description: StemPlotList를 출력하는 함수. 전체 출력 format.
*******************************************************************************/
static void PrintStemPlotList(StemPlotList *stemPlotList);

/*****************************************************************************
* Function : PrintData(DataSet *dataSet)
* Description: dataSet을 받아와 데이터를 출력해주는 함수
*******************************************************************************/
static void PrintData(DataSet *dataSet);

/*****************************************************************************
* Function : SortQuick(EType *dataSet, const int posLeft, const int posRight)
* Description: 퀵정렬 함수이다. partition함수를 사용하여 범위를 나누고 합치며 정렬 해 나간다.
*******************************************************************************/
static void SortQuick(EType *dataSet, int posLeft, int posRight);

/*****************************************************************************
* Function : partition(EType *src, const int posLeft, const int posRight)
* Description: pivot을 설정하고 pivot보다 작은 값을 왼쪽, 큰 값을 오른쪽으로 옮긴다.
마지막으로 pivot의 위치를 반환하여 SortQuick에서 pivot 기준으로
양쪽으로 나눠 다시 반복 실행 할 수 있도록 한다.
*******************************************************************************/
int partition(EType *src, const int posLeft, const int posRight);

int main(void)
{
	StemPlotList* stemPlotList;
	DataSet *dataSet;

	dataSet = CreateDataSet(5, 10, 50);
	printf("Print DataSet \n");
	PrintData(dataSet);

	stemPlotList = CreateStemPlotList();
	stemPlotList = ComputeStemPlotList(dataSet);
	PrintStemPlotList(stemPlotList);

	return 0;
}
static DataSet *CreateDataSet(const int rowsDataSet, const int colsDataSet, const int lengthDataSet)
{
	FILE *infile;
	DataSet *dataSet = NULL; //return
	EType *bgn = NULL, *end = NULL;

	infile = fopen("Sample.dat", "r");
	dataSet = (DataSet*)malloc(sizeof(DataSet)); 
	fscanf(infile, "%d %d %d", &dataSet->rows, &dataSet->cols, &dataSet->length); 

	dataSet->elem = (EType*)malloc(sizeof(EType*)*dataSet->length);
	memset(dataSet->elem, 0x00, (dataSet->length * sizeof(EType))); 

	bgn = dataSet->elem; // begin을 elem의 시작주소로 초기화
	end = dataSet->elem + dataSet->length;// end를 elem의 끝 주소로 초기화

	while (fscanf(infile, "%d", bgn++) != EOF)
	{
		if (bgn == end)// 시작주소가 끝 주소와 같아지면 종료
			break;
	}
	fclose(infile);
	return dataSet;
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
static StemNode *CreateStemNode(const int elemSize, const int stemValue)
{
	StemNode *out;//return

	out = (StemNode*)malloc(sizeof(StemNode));
	out->stem = stemValue;
	out->freq = elemSize;
	out->leaf = (EType*)malloc(sizeof(EType) * elemSize);
	out->next = NULL;

	return out;
}
static void DestroyStemNode(StemNode *stemNode)
{
	if (!stemNode)
		return;

	if (!stemNode->leaf)
		goto DESTROY;

	free(stemNode->leaf);
	stemNode->leaf = NULL;

DESTROY:
	free(stemNode);
	stemNode = NULL;
}
static StemPlotList *CreateStemPlotList(void)
{
	StemPlotList* out;//return

	out = (StemPlotList*)malloc(sizeof(StemPlotList));
	out->head = NULL;;
	out->tail = NULL;
	return out;
}
static void DestroyStemPlotList(StemPlotList *stemPlotList)
{
	if (!stemPlotList)
		return;
	if (stemPlotList->head)
		DesStemNode(stemPlotList->head);
	if (stemPlotList->tail)
		DestroyStemNode(stemPlotList->tail);

	free(stemPlotList);
}
static StemPlotList *ComputeStemPlotList(DataSet * dataSet)
{
	StemPlotList *out;//return
	int i = 0, n = 0;
	int stem_temp = 0, stem_size = 1;
	StemNode *stn;
	int cnt = 0;
	out = CreateStemPlotList();

	SortQuick(dataSet->elem, 0, dataSet->length - 1);

	stem_temp = dataSet->elem[n] / 10;

	while (1)
	{
		if (n == dataSet->length)
			break;
		if (stem_temp == dataSet->elem[++n] / 10)
		{
			stem_size++;
		}
		else
		{
			stn = CreateStemNode(stem_size, stem_temp);

			for (i = 0; i < stem_size; i++)
			{
				stn->leaf[i] = dataSet->elem[cnt] % 10;
				cnt++;
			}
			AddStemNode(out, stn);
			stem_temp = dataSet->elem[n] / 10;
			stem_size = 1;
		}
	}

	return out;
}
static void AddStemNode(StemPlotList *stemPlotList, StemNode *stemNode)
{
	if (stemPlotList->head == NULL)// 빈 경우
	{
		stemPlotList->head = stemNode;
		stemPlotList->tail = stemNode;
	}
	else if (stemPlotList->head == stemPlotList->tail)//하나만 들어있는 경우
	{
		stemPlotList->tail = stemNode;
		stemPlotList->head->next = stemNode;
	}
	else// 둘다 들어 있는 경우
	{
		stemPlotList->tail->next = stemNode;
		stemPlotList->tail = stemNode;
	}
}
static void PrintLeaf(StemNode *stemNode)
{
	int i;

	printf("\t%d ( %2d) : ", stemNode->stem, stemNode->freq);
	for (i = 0; i < stemNode->freq; i++)
	{
		printf(" %d", stemNode->leaf[i]);
	}
	printf("\n");
}

static void PrintStemPlotList(StemPlotList *stemPlotList)
{
	StemNode* bgn = stemPlotList->head;

	printf("Stem Plot List \n\n");
	printf("   Stem (Freq'):           Leaf\n");
	printf("-----------------------------------------------\n");
	while (bgn != NULL) // 주소값이 null을 만날때 까지
	{
		PrintLeaf(bgn);// 잎을 출력한다.
		bgn = bgn->next; // 다음 stemnode로 이동
	}
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

	for (col = 0; begin != end; begin++, col++)
	{
		if (col >= cols)//개행을 위한 조건, 열의 개수만큼 되면 개행을 한다.
		{
			col = 0;// 다음 개행을 위해 초기화
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