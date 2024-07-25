#include "pch.h"
#include "Chi2Histogram.h"

/**
 * @brief Constructs a Chi2Histogram object as a deep copy of an existing one.
 * @param _h Reference to the Chi2Histogram object to copy.
 * Copies all the properties and deep copies the arrays for empirical and theoretical frequencies.
 */
Chi2Histogram::Chi2Histogram(const Chi2Histogram& _h) :
    pvalue(_h.Getpvalue()),
    df(_h.Getdf()),
    chi2(_h.Getchi2()),
    a(_h.a),
    b(_h.b),
    removed(_h.removed),
    sample_size(_h.sample_size),
    SizeTheoreticalFreq(_h.SizeTheoreticalFreq),
    SizeEmpiricalFreq(_h.SizeEmpiricalFreq),
    TheoreticalFreq(_h.TheoreticalFreq)
{
    EmpiricalFreq = new int[SizeEmpiricalFreq]{ 0 };
}

/**
 * @brief Constructs a Chi2Histogram object using a specified distribution and sample generator.
 * @param _d0 The distribution model used for theoretical frequencies.
 * @param _s Pointer to a HupergeomSampleGenerator for empirical frequencies.
 * Allocates memory for and initializes theoretical and empirical frequency arrays based on the provided inputs.
 */
Chi2Histogram::Chi2Histogram(const Distribution& _d0, const HupergeomSampleGenerator* _s) :
    pvalue(0),
    df(0), 
    chi2(0),
    a(_s->GetDist().Geta()),
    b(_s->GetDist().Getb()),
    removed(_s->GetDist().Get_removed()),
    sample_size(_s->Get_sample_size()),
    SizeTheoreticalFreq ( _d0.Get_removed() + 1),
    SizeEmpiricalFreq(_s->GetDist().Get_removed() + 1)
    ,TheoreticalFreq(nullptr)
    ,EmpiricalFreq(nullptr)
{
    TheoreticalFreq = new double[SizeTheoreticalFreq];
    for (int i = 0; i < SizeTheoreticalFreq; ++i)
    {
        TheoreticalFreq[i] = _d0.GetTheoretical_prob(i);
    }
 

    //delete[] EmpiricalFreq;

    EmpiricalFreq = _s->fill_observe_freq();
    //EmpiricalFreq = new int[SizeEmpiricalFreq];
    //for (int i = 0; i < SizeEmpiricalFreq; ++i)
    //{
    //    EmpiricalFreq[i] = _s->GetObservedFrequences(i);
    //}
    //EmpiricalFreq = _s->GetObservedFrequences();
}

/**
 * @brief Assigns this Chi2Histogram object the values from another.
 * @param other The Chi2Histogram object to copy from.
 * @return A reference to this Chi2Histogram object.
 * Ensures deep copy of arrays and properties. Previous resources are properly released.
 */
Chi2Histogram& Chi2Histogram::operator=(const Chi2Histogram& other)
{
    if (this == &other)
    {
        return *this;
    }

    delete[] TheoreticalFreq;
    delete[] EmpiricalFreq;

    df = other.df;
    chi2 = other.chi2;
    pvalue = other.pvalue;
    sample_size = other.sample_size;

    TheoreticalFreq = new double[other.SizeTheoreticalFreq];
    EmpiricalFreq = new int[other.SizeEmpiricalFreq];

    for (int i = 0; i < SizeTheoreticalFreq; ++i)
    {
        TheoreticalFreq[i] = other.TheoreticalFreq[i];
    }

    for (int i = 0; i < SizeEmpiricalFreq; ++i)
    {
        EmpiricalFreq[i] = other.EmpiricalFreq[i];
    }

    return *this;
}

/**
 * @brief Transfers the resources of a Chi2Histogram object to this object.
 * @param other The Chi2Histogram object to move from.
 * @return A reference to this updated object.
 * Moves arrays and properties, and resets the other object's properties to ensure it's left in a valid state.
 */
Chi2Histogram& Chi2Histogram::operator=(Chi2Histogram&& other)
{
    if (this == &other)
    {
        return *this;
    }

    delete[] TheoreticalFreq;
    delete[] EmpiricalFreq;

    df = other.df;
    chi2 = other.chi2;
    pvalue = other.pvalue;
    sample_size = other.sample_size;

    TheoreticalFreq = new double[other.SizeTheoreticalFreq];
    EmpiricalFreq = new int[other.SizeEmpiricalFreq];

    for (int i = 0; i < SizeTheoreticalFreq; ++i)
    {
        TheoreticalFreq[i] = other.TheoreticalFreq[i];
    }

    for (int i = 0; i < SizeEmpiricalFreq; ++i)
    {
        EmpiricalFreq[i] = other.EmpiricalFreq[i];
    }

    other.df = 0;
    other.chi2 = 0;
    other.pvalue = 0;
    other.sample_size = 0;

    other.SizeTheoreticalFreq = 0;
    other.SizeEmpiricalFreq = 0;

    other.TheoreticalFreq = nullptr;
    other.EmpiricalFreq = nullptr;

    return *this;
}

/**
 * @brief Computes the chi-squared statistic based on theoretical and empirical frequencies.
 * Calculates the chi-squared statistic, degrees of freedom, and p-value to evaluate the fit of the empirical data to the expected distribution.
 */
void Chi2Histogram::Chi2()
{
	double* expected_frequency_united = new double[removed + 1]{ 0 };
    double *observed_frequency_united = new double[removed + 1]{ 0 };

	double expected_frequency_sum = 0;
	double observed_frequency_sum = 0;

    double* theor = new double[removed + 1]{ 0 };
    double* emp = new double[removed + 1]{ 0 };

    if (SizeTheoreticalFreq < SizeEmpiricalFreq)
    {
        chi2 = -1;
        df = 0;
        pvalue = 0;

    }
    else
    {
        int k = 0;
        for (int i = 0; i < removed + 1; ++i)
        {
            if (SizeTheoreticalFreq > SizeEmpiricalFreq && i > SizeEmpiricalFreq)
            {
                theor[i] = sample_size * TheoreticalFreq[i];
                emp[i] = 0;
            }
            else
            {
                theor[i] = sample_size * TheoreticalFreq[i];
                emp[i] = EmpiricalFreq[i];
            }
        }

        for (int i = 0; i < removed + 1; ++i)
        {
            if (expected_frequency_sum > 5)
            {

                expected_frequency_united[k] = expected_frequency_sum;
                observed_frequency_united[k] = observed_frequency_sum;

                expected_frequency_sum = 0;
                observed_frequency_sum = 0;
                ++k;
            }

            expected_frequency_sum += theor[i];
            observed_frequency_sum += emp[i];
        }

        if (expected_frequency_sum)
        {
            observed_frequency_united[k - 1] += observed_frequency_sum;
            expected_frequency_united[k - 1] += expected_frequency_sum;
        }

        for (int i = 0; i < k; ++i)
        {
            if (expected_frequency_united[i] != 0)
                chi2 += ((expected_frequency_united[i] - observed_frequency_united[i]) *
                    (expected_frequency_united[i] - observed_frequency_united[i]))
                / expected_frequency_united[i];
        }

        df = k - 1;
        pvalue = 1 - pChi(chi2, df);

    }


    delete[] expected_frequency_united;
    delete[] observed_frequency_united;
    delete[] theor;
    delete[] emp;
}

