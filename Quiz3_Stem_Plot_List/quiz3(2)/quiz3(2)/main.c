/*****************************************************************************
* Name		:	���ȯ
* Student ID:	20123338
* Quiz 3-2	:	Back to Back Stem and Leaf Plot

* Description: �ΰ��� dataset�� ����Ͽ� Stem �� leaf�� �������� ����� �ִ� ���α׷��̴�.
				���� �ڸ� ���ڸ� �ٱ�(stem)���� �Ͽ� ���� ������ ������� ��� �����ϰ�
				���ʿ��� �� �ٱ⿡ �ش��ϴ� �� dataSet�� ���� �ڸ� ���ڸ� ��(leaf)���� ���η� �����Ѵ�.
				�ߺ��� �ڷ��� ���� �ߺ��� Ƚ����ŭ �����Ѵ�.
*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

#define PATH_FILE "b.txt"

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
}DataSet;
#endif

//StemNode����ü, �ٱ�, ���ǰ���, ��, ���� �ٱ⸦ ����.
#ifndef STEMNODE
#define STEMNODE
typedef struct
{
	int stem;
	int freq;
	EType *leaf;
	struct StemNode *next;
}StemNode;
#endif

//StemPlotList����ü, StemNode���� ����, ���� StemNode�� �� StemNode�� ����.
#ifndef STEMPLOTLIST
#define STEMPLOTLIST
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
static DataSet *CreateDataSet(const char *fileName);

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
static StemPlotList *ComputeStemPlotList(DataSet * dataSet);

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
static void PrintStemPlotList(StemPlotList *leftPlotList, StemPlotList *rightPlotList);

/*****************************************************************************
* Function : PrintData(DataSet *dataSet)
* Description: dataSet�� �޾ƿ� �����͸� ������ִ� �Լ�
*******************************************************************************/
static void PrintData(DataSet *dataSet);

/*****************************************************************************
* Function : SortQuick(EType *dataSet, const int posLeft, const int posRight)
* Description: ������ �Լ��̴�. partition�Լ��� ����Ͽ� ������ ������ ��ġ�� ���� �� ������.
				������ �����ͼ°� ���� �ε����� ������ �ε����� ���ڷ� �޴´�.
*******************************************************************************/
static void SortQuick(EType *dataSet, const int posLeft, const int posRight);

/*****************************************************************************
* Function : partition(EType *src, const int posLeft, const int posRight)
* Description: pivot�� �����ϰ� pivot���� ���� ���� ����, ū ���� ���������� �ű��.
���������� pivot�� ��ġ�� ��ȯ�Ͽ� SortQuick���� pivot ��������
�������� ���� �ٽ� �ݺ� ���� �� �� �ֵ��� �Ѵ�.
*******************************************************************************/
static int partition(EType *src, const int posLeft, const int posRight);

int main()
{
	DataSet *left = CreateDataSet("hbp.txt");
	DataSet *right = CreateDataSet("nbp.txt");

	StemPlotList *left_list = CreateStemPlotList();
	StemPlotList *right_list = CreateStemPlotList();

	printf("Print Left\n");
	PrintData(left);
	printf("Print Right\n");
	PrintData(right);

	left_list = ComputeStemPlotList(left);
	right_list = ComputeStemPlotList(right);

	PrintStemPlotList(left_list, right_list);

	return 0;
}

static DataSet *CreateDataSet(const char *fileName)
{
	DataSet *out = NULL;//return
	FILE *inFile = NULL;
	EType *begin = NULL;
	EType *end = NULL;

	inFile = fopen(fileName, "r");
	if (!inFile )
		abort();

	out = (DataSet*)malloc(sizeof(DataSet));

	if (!out)
		abort();

	fscanf(inFile, "%d %d %d", &out->rows, &out->cols, &out->length);

	out->elem = (EType*)malloc(sizeof(EType)*out->length);
	if (!out->elem)
		abort();
	memset(out->elem, 0x00, (out->length * sizeof(EType)));

	begin = out->elem;// begin�� elem�� �����ּҷ� �ʱ�ȭ
	end = out->elem + out->length;// end�� elem�� �� �ּҷ� �ʱ�ȭ

	while (fscanf(inFile, "%d", begin++) != EOF)
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
	for (i = 0; i < stemNode->freq; i++)
	{
		printf(" %d", stemNode->leaf[i]);
	}
	printf("\n");
}
static void PrintStemPlotList(StemPlotList *leftPlotList, StemPlotList *rightPlotList)
{
	int i, len;
	char *str;
	printf("\t\t\t  Left |     Stem     | Right\n");
	printf("------------------------------------------------------------------\n");
	str = (char*)malloc(sizeof(char) * leftPlotList->head->freq + 1);
	
	while ((leftPlotList->head != NULL) && (rightPlotList->head != NULL))
	{

		if (leftPlotList->head->stem == rightPlotList->head->stem) // ���� stem �� ���
		{
			len = 0;
			for (i = leftPlotList->head->freq - 1; i >= 0; i--)
			{
				len += sprintf(str + len, "%d ", leftPlotList->head->leaf[i]);
			}
			printf(" %30s", str);
			printf("| <%2d> %2d <%2d> | ", leftPlotList->head->freq, leftPlotList->head->stem, rightPlotList->head->freq);
			PrintLeaf(rightPlotList->head);

			leftPlotList->head = leftPlotList->head->next;
			rightPlotList->head = rightPlotList->head->next;
		}
		else if (leftPlotList->head->stem < rightPlotList->head->stem)// left�� ������ �������
		{
			len = 0;
			for (i = leftPlotList->head->freq - 1; i >= 0; i--)
			{
				len += sprintf(str + len, "%d ", leftPlotList->head->leaf[i]);
			}
			printf(" %30s", str);
			printf("| <%2d> %2d < 0> | \n", leftPlotList->head->freq, leftPlotList->head->stem);

			leftPlotList->head = leftPlotList->head->next;
		}
		else//right�� stem�� �������
		{
			printf(" %30c| < 0> %2d <%2d> | ", NULL, rightPlotList->head->stem, rightPlotList->head->freq);
			PrintLeaf(rightPlotList->head);
		
			rightPlotList->head = rightPlotList->head->next;
		}
	}

	if (leftPlotList->head == NULL && rightPlotList->head != NULL) // �� �ߴµ� ������ data �� ������ ���
	{
		while (rightPlotList->head != NULL)
		{
			printf(" %30c| < 0> %2d <%2d> | ", NULL,rightPlotList->head->stem, rightPlotList->head->freq);
			PrintLeaf(rightPlotList->head);

			rightPlotList->head = rightPlotList->head->next;
		}

	}
	else if (leftPlotList->head != NULL && rightPlotList->head == NULL) // ������ �������� ���
	{
		while (leftPlotList->head != NULL)
		{
			len = 0;
			for (i = leftPlotList->head->freq - 1; i >= 0; i--)
			{
				len += sprintf(str + len, "%d ", leftPlotList->head->leaf[i]);
			}
			printf(" %30s", str);
			printf("| <%2d> %2d < 0> | \n", leftPlotList->head->freq, leftPlotList->head->stem);

			leftPlotList->head = leftPlotList->head->next;
		}
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