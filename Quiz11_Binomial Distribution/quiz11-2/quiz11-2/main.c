/*****************************************************************************
* Name		:	김대환
* Student ID:	20123338
* Quiz 11-2	:	Negative Binomial Distribution

* Description: 음이항분포의 확률, 평균, 분산을 구하는 프로그램
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
* Description: 인자로 받은 수(f)의 factorial을 구하는 함수
*******************************************************************************/
static double ComputeFactorial(const double f);

/*****************************************************************************
* Function : ComputeCombination(const double n, const double r)
* Description: Combination(조합)을 구하는 함수. nCr.
*******************************************************************************/
static double ComputeCombination(const double n, const double r);

/*****************************************************************************
* Function : ComputePermutation(const double n, const double r)
* Description: Permutation(순열)을 구하는 함수. nPr.
*******************************************************************************/
static double ComputePermutation(const double n, const double r);

/*****************************************************************************
* Function : ComputeNegativeBinomialDist(const double success, const double trial, const double prob, const BOOL cumulative);
* Description: 성공횟수, 시도횟수, 성공 확률, Cumulative(확률함수는 0, 누적분포함수는 1)를 인자로 받아 음이항분포의 확률을 구하는 함수
				엑셀의 NEGBINOM.DIST 함수와 같은 역할
*******************************************************************************/
static double ComputeNegativeBinomialDist(const double failure, const double success, const double prob, const BOOL cumulative);

/*****************************************************************************
* Function : ComputeMeanNegativeBinomialDist(const double success, const double prob)
* Description: 음이항분포의 평균을 구하는 함수, 인자로 성공횟수와 성공확률을 받는다.
				음이항분포의 평균 = success / prob
*******************************************************************************/
static double ComputeMeanNegativeBinomialDist(const double success, const double prob);

/*****************************************************************************
* Function : ComputeVarBinomialDist(const double success, const double prob);
* Description: 음이항분포의 분산을 구하는 함수, 인자로 성공횟수와 성공확률을 받는다.
				음이항분포의 분산 = success * (1-prob) / (prob * prob)
*******************************************************************************/
static double ComputeVarNegativeBinomialDist(const double success, const double prob);

int main(int argc, char argv[])
{
	double Number_f = 2; //실패횟수
	double Number_s = 3; //성공횟수
	double Probability_s = 0.4;//성공확률
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