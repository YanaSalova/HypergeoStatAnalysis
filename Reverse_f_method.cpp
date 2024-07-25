#include "pch.h"
#include "Reverse_f_method.h"

/**
 * @brief Simulates drawing samples from a hypergeometric distribution using the reverse F method.
 *
 * This method leverages the reverse F method to simulate the process of drawing samples from a population
 * with 'a' successes and 'b' failures, observing the frequency of successes in samples of size 'removed'.
 * It calculates the cumulative probability distribution function in reverse, starting from the least likely
 * event of all successes, until the random number 'alpha', generated for each simulation, is exceeded.
 * Each iteration updates the observed frequency of successes for that particular simulation.
 */
void Reverse_f_method::Simulate() 
{
	int n = modeling_distr.Geta() + modeling_distr.Getb();

	double p, sum;


	for (int k = 0; k < sample_size; ++k)
	{
		std::uniform_real_distribution<double> distribution(0., 1.);
		double alpha = distribution(rngRadius);

		p = 1;
		for (int j = 0; j <= modeling_distr.Get_removed() - 1; ++j)
			p *= double((n - modeling_distr.Geta() - j)) / (n - j);

		int i = 0;
		sum = p;

		while (sum <= alpha)
		{
			p = p * double(modeling_distr.Geta() - i) * (modeling_distr.Get_removed() - i) /
			     ((i + 1) * (n - modeling_distr.Geta() - modeling_distr.Get_removed() + i + 1));
			sum += p;
			++i;
		}
		observed_frequences_modeling[k] = i;
	}

};