/*****************************************************************************
* Name		:	���ȯ
* Student ID:	20123338
* Quiz 3-1	:	Stem and leaf

* Description: ���� �ڸ� ���ڸ� �ٱ�(stem)���� �Ͽ� ���� ������ ������� �����ϰ�
				�����ʿ��� �� �ٱ⿡ �ش��ϴ� ���� �ڸ� ���ڸ� ��(leaf)�� ���η� �����Ѵ�.
				�ߺ��� �ڷ��� ���� �ߺ��� Ƚ����ŭ �����Ѵ�.
*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//�������� ��� ���İ�, �Է� ������ �����ϴ� �κ�
#ifndef DATATYPE
#define DATATYPE
//#define SCANFORMAT "%f"
//#define PRNFORMAT "%10.6f"
#define SCANFORMAT "%d"
#define PRNFORMAT " %2d"
typedef int EType;
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

//StemNode����ü, �ٱ�, ���ǰ���, ��, ���� �ٱ⸦ ����.
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

//StemPlotList����ü, StemNode���� ����, ���� StemNode�� �� StemNode�� ����.
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
* Description: �������� ��� �� �׸��� ������ �޾� dataSet����ü�� ����� ��ȯ�ϴ� �Լ�.
*******************************************************************************/
static DataSet *CreateDataSet(const int rowsDataSet, const int colsDataSet, const int lengthDataSet);

/*****************************************************************************
* Function : DestoryData(DataSet *dataSet)
* Description: dataSet�� �����Ҵ��� Ǯ���ִ� �Լ�
*******************************************************************************/
static void DestroyDataSet(DataSet *dataSet);

/*****************************************************************************
* Function : CreateStemNode(const int elemSize, const int stemValue)
* Description: StemNode ����ü�� ����� ��ȯ�ϴ� �Լ�. �ٱ� ���� �󵵼��� �޾ƿ� �����Ѵ�.
*******************************************************************************/
static StemNode *CreateStemNode(const int elemSize, const int stemValue);

/*****************************************************************************
* Function : DestoryStemNode(StemNode *stemNode)
* Description: stemNode�� �����Ҵ��� Ǯ���ִ� �Լ�
*******************************************************************************/
static void DestroyStemNode(StemNode *stemNode);

/*****************************************************************************
* Function : CreateStemNode(const int elemSize, const int stemValue)
* Description: StemPlotList ����ü�� ����� ��ȯ�ϴ� �Լ�.
*******************************************************************************/
static StemPlotList *CreateStemPlotList(void);

/*****************************************************************************
* Function : DestoryStemPlotList(StemPlotList *stemPlotList)
* Description: stemPlotList�� �����Ҵ��� Ǯ���ִ� �Լ�
*******************************************************************************/
static void DestroyStemPlotList(StemPlotList *stemPlotList);

/*****************************************************************************
* Function : ComputeStemPlotList(StemPlotList *stemPlotList, DataSet * dataSet)
* Description: dataSet�� ����Ͽ� StemNode�� ����� StemPlotList�� �߰��� StemPlotList�� �ϼ��ϴ� �Լ�
*******************************************************************************/
static StemPlotList* ComputeStemPlotList(DataSet * dataSet);

/*****************************************************************************
* Function : AddStemNode(StemPlotList *stemPlotList, StemNode *stemNode)
* Description: StemNode�� StemPlotList�� �߰��� �ִ� �Լ�.
*******************************************************************************/
static void AddStemNode(StemPlotList *stemPlotList, StemNode *stemNode);

/*****************************************************************************
* Function : PrintLeaf(StemNode *stemNode)
* Description: stemNode�� leaf(��)�� ������ִ� �Լ�
*******************************************************************************/
static void PrintLeaf(StemNode *stemNode);

/*****************************************************************************
* Function : PrintStemPlotList(StemPlotList *stemPlotList)
* Description: StemPlotList�� ����ϴ� �Լ�. ��ü ��� format.
*******************************************************************************/
static void PrintStemPlotList(StemPlotList *stemPlotList);

/*****************************************************************************
* Function : PrintData(DataSet *dataSet)
* Description: dataSet�� �޾ƿ� �����͸� ������ִ� �Լ�
*******************************************************************************/
static void PrintData(DataSet *dataSet);

/*****************************************************************************
* Function : SortQuick(EType *dataSet, const int posLeft, const int posRight)
* Description: ������ �Լ��̴�. partition�Լ��� ����Ͽ� ������ ������ ��ġ�� ���� �� ������.
*******************************************************************************/
static void SortQuick(EType *dataSet, int posLeft, int posRight);

/*****************************************************************************
* Function : partition(EType *src, const int posLeft, const int posRight)
* Description: pivot�� �����ϰ� pivot���� ���� ���� ����, ū ���� ���������� �ű��.
���������� pivot�� ��ġ�� ��ȯ�Ͽ� SortQuick���� pivot ��������
�������� ���� �ٽ� �ݺ� ���� �� �� �ֵ��� �Ѵ�.
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

	bgn = dataSet->elem; // begin�� elem�� �����ּҷ� �ʱ�ȭ
	end = dataSet->elem + dataSet->length;// end�� elem�� �� �ּҷ� �ʱ�ȭ

	while (fscanf(infile, "%d", bgn++) != EOF)
	{
		if (bgn == end)// �����ּҰ� �� �ּҿ� �������� ����
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
	if (stemPlotList->head == NULL)// �� ���
	{
		stemPlotList->head = stemNode;
		stemPlotList->tail = stemNode;
	}
	else if (stemPlotList->head == stemPlotList->tail)//�ϳ��� ����ִ� ���
	{
		stemPlotList->tail = stemNode;
		stemPlotList->head->next = stemNode;
	}
	else// �Ѵ� ��� �ִ� ���
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
	while (bgn != NULL) // �ּҰ��� null�� ������ ����
	{
		PrintLeaf(bgn);// ���� ����Ѵ�.
		bgn = bgn->next; // ���� stemnode�� �̵�
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
	begin = setData->elem;// begin�� elem�� �����ּҷ� �ʱ�ȭ
	if (!begin) return;

	end = begin + length;// end�� elem�� �� �ּҷ� �ʱ�ȭ

	for (col = 0; begin != end; begin++, col++)
	{
		if (col >= cols)//������ ���� ����, ���� ������ŭ �Ǹ� ������ �Ѵ�.
		{
			col = 0;// ���� ������ ���� �ʱ�ȭ
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