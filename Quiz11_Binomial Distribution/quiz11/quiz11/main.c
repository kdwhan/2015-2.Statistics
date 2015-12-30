/*****************************************************************************
* Name		:	김대환
* Student ID:	20123338
* Quiz 11-1	:	Binomial Distribution

* Description: 이항분포의 확률, 평균, 분산을 구하는 프로그램
*******************************************************************************/
#include<stdio.h>
#include<stdlib.h>

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
* Description: 조합을 구하는 함수. 인자로 받은 n 개중 r을 뽑는 것. nCr.
*******************************************************************************/
static double ComputeCombination(const double n, const double r);

/*****************************************************************************
* Function : ComputeBinomialDist(const double success, const double trial, const double prob, const BOOL cumulative);
* Description: 성공횟수, 시도횟수, 성공 확률, Cumulative(확률함수는 0, 누적분포함수는 1)를 인자로 받아 이항분포의 확률을 구하는 함수
				엑셀의 BINOM.DIST 함수와 같은 역할
*******************************************************************************/
static double ComputeBinomialDist(const double success, const double trial, const double prob, const BOOL cumulative);

/*****************************************************************************
* Function : ComputeMeanBinomialDist(const double trial, const double prob)
* Description: 이항분포의 평균을 구하는 함수, 인자로 시도횟수와 성공확률을 받는다.
				이항분포의 평균 = trial * prob
*******************************************************************************/
static double ComputeMeanBinomialDist(const double trial, const double prob);

/*****************************************************************************
* Function : ComputeVarBinomialDist(const double trial, const double prob);
* Description: 이항분포의 분산을 구하는 함수, 인자로 시도횟수와 성공확률을 받는다.
이항분포의 평균 = trial * prob * (1-prob)
*******************************************************************************/
static double ComputeVarBinomialDist(const double trial, const double prob);


int main(int argc, char argv[])
{
	double Number_s = 4;//성공횟수
	double Trials = 8;//시도횟수
	double Probability_s = 0.5;//성공할 확률
	BOOL Cumulative = 1;//확률함수는 0, 누적분포함수는 1

	double BinomialDist, MeanBinomialDist, VarBinomialDist;

	printf("Number_s = %f\n", Number_s);
	printf("Trials = %f\n", Trials);
	printf("Probability_s = %f\n", Probability_s);
	printf("Cumulative = %s\n", (Cumulative == FALSE ? "False":"True"));

	BinomialDist = ComputeBinomialDist(Number_s, Trials, Probability_s, Cumulative);
	printf("\nBinomial Distribution Probability\n = %f\n", BinomialDist);

	MeanBinomialDist = ComputeMeanBinomialDist(Trials, Probability_s);
	printf("\nMean of Binomial Distribution\n = %f\n", MeanBinomialDist);

	VarBinomialDist = ComputeVarBinomialDist(Trials, Probability_s);
	printf("\nVariance of Binomial Distribution\n = %f\n", VarBinomialDist);

	return 0;
}

static double ComputeFactorial(const double f)
{
	double e = 1, i;

	for (i = 1; i <= f; i++)
	{
		e = e*i;
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

static double ComputeBinomialDist(const double success, const double trial, const double prob, const BOOL cumulative)
{
	double out_false, out_true = 0;
	int i;

	if (cumulative == 0)
	{
		out_false = ComputeCombination(trial, success);

		for (i = 0; i < success; i++)
			out_false *= prob;

		for (i = 0; i < trial - success; i++)
			out_false *= (1 - prob);

		return out_false;
	}
	else
	{
		for (i = 0; i <= success; i++)
			out_true += ComputeBinomialDist(i, trial, prob, 0);

		return out_true;
	}
}

static double ComputeMeanBinomialDist(const double trial, const double prob)
{
	return trial*prob;
}
static double ComputeVarBinomialDist(const double trial, const double prob)
{
	return trial*prob*(1 - prob);
}