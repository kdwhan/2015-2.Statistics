/*****************************************************************************
* Name		:	���ȯ
* Student ID:	20123338
* Quiz 11-2	:	Negative Binomial Distribution

* Description: �����׺����� Ȯ��, ���, �л��� ���ϴ� ���α׷�
*******************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#ifndef BOOL
typedef int BOOL;
#define FALSE 0
#define TRUE !FALSE
#endif

/*****************************************************************************
* Function : ComputeFactorial(const double f)
* Description: ���ڷ� ���� ��(f)�� factorial�� ���ϴ� �Լ�
*******************************************************************************/
static double ComputeFactorial(const double f);

/*****************************************************************************
* Function : ComputeCombination(const double n, const double r)
* Description: Combination(����)�� ���ϴ� �Լ�. nCr.
*******************************************************************************/
static double ComputeCombination(const double n, const double r);

/*****************************************************************************
* Function : ComputePermutation(const double n, const double r)
* Description: Permutation(����)�� ���ϴ� �Լ�. nPr.
*******************************************************************************/
static double ComputePermutation(const double n, const double r);

/*****************************************************************************
* Function : ComputeNegativeBinomialDist(const double success, const double trial, const double prob, const BOOL cumulative);
* Description: ����Ƚ��, �õ�Ƚ��, ���� Ȯ��, Cumulative(Ȯ���Լ��� 0, ���������Լ��� 1)�� ���ڷ� �޾� �����׺����� Ȯ���� ���ϴ� �Լ�
				������ NEGBINOM.DIST �Լ��� ���� ����
*******************************************************************************/
static double ComputeNegativeBinomialDist(const double failure, const double success, const double prob, const BOOL cumulative);

/*****************************************************************************
* Function : ComputeMeanNegativeBinomialDist(const double success, const double prob)
* Description: �����׺����� ����� ���ϴ� �Լ�, ���ڷ� ����Ƚ���� ����Ȯ���� �޴´�.
				�����׺����� ��� = success / prob
*******************************************************************************/
static double ComputeMeanNegativeBinomialDist(const double success, const double prob);

/*****************************************************************************
* Function : ComputeVarBinomialDist(const double success, const double prob);
* Description: �����׺����� �л��� ���ϴ� �Լ�, ���ڷ� ����Ƚ���� ����Ȯ���� �޴´�.
				�����׺����� �л� = success * (1-prob) / (prob * prob)
*******************************************************************************/
static double ComputeVarNegativeBinomialDist(const double success, const double prob);

int main(int argc, char argv[])
{
	double Number_f = 2; //����Ƚ��
	double Number_s = 3; //����Ƚ��
	double Probability_s = 0.4;//����Ȯ��
	BOOL Cumulative = 1;
	
	double NegativeBinomialDist, MeanNegativeBinomialDist, VarNegativeBinomialDist;

	printf("Number_f = %f\n", Number_f);
	printf("Number_s = %f\n", Number_s);
	printf("Probability_s = %f\n", Probability_s);
	printf("Cumulative = %s\n", (Cumulative == FALSE ? "False" : "True"));

	NegativeBinomialDist = ComputeNegativeBinomialDist(Number_f, Number_s, Probability_s, Cumulative);
	printf("\nNegative Binomial Ditribution Probability\n = %f\n", NegativeBinomialDist);

	MeanNegativeBinomialDist = ComputeMeanNegativeBinomialDist(Number_s, Probability_s);
	printf("\nMean of Negative Binomial Ditribution\n = %f\n", MeanNegativeBinomialDist);

	VarNegativeBinomialDist = ComputeVarNegativeBinomialDist(Number_s, Probability_s);
	printf("Variance of Negative Binomial Ditribution\n = %f\n", VarNegativeBinomialDist);
	
	return 0;
}

static double ComputeFactorial(const double f)
{
	double e = 1, i;

	for (i = 1; i <= f; i++)
	{
		e *= i;
	}

	return e;
}

static double ComputeCombination(const double n, const double r)
{
	double out;

	if (r == 0)
		return 1;

	out = ComputeFactorial(n) / (ComputeFactorial(r) * ComputeFactorial(n - r));

	return out;
}

static double ComputePermutation(const double n, const double r)
{
	int i;
	int out = 1;

	for (i = n; i > n - r; --i)
	{
		out *= i;
	}
	return out;
}

static double ComputeNegativeBinomialDist(const double failure, const double success, const double prob, const BOOL cumulative)
{
	int i;
	double out = 0;

	if (!cumulative)
	{
		out = ComputeCombination(success + failure - 1, success - 1) * pow(prob, success) * pow(1 - prob, failure);
	}
	else
	{
		for (i = 0; i <=failure; i++)
			out += ComputeCombination(success + i - 1, success - 1) * pow(prob, success) * pow(1 - prob, i);
	}
	return out;

}
static double ComputeMeanNegativeBinomialDist(const double success, const double prob)
{
	return success / prob;
}
static double ComputeVarNegativeBinomialDist(const double success, const double prob)
{
	return (success*(1 - prob)) / (prob*prob);
}