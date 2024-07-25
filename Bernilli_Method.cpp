#include "pch.h"
#include "Bernilli_Method.h"


/**
 * @brief Simulates drawing samples from a hypergeometric distribution using the Bernoulli method.
 *
 * This method simulates the process of drawing samples from a population comprising 'a' successes
 * and 'b' failures ('a' and 'b' being parameters of the distribution) to observe the frequency
 * of successes in samples of size 'removed'. The simulation runs for a number of iterations
 * equal to 'sample_size', with each iteration generating a sample and recording the number
 * of successes (j) observed. The outcome of each draw (success or failure) is determined
 * by generating a random number and comparing it to the probability of drawing a success
 * at that point in the sampling process.
 */
void Bernulli_Method::Simulate()
{
	
	int n = modeling_distr.Geta() + modeling_distr.Getb();

	
	for (int k = 0; k < sample_size; ++k)
	{
		int i = 0; 
		int j = 0; 

		
		while (i < modeling_distr.Get_removed())
		{
			std::uniform_real_distribution<double> distribution(0., 1.);
			double alpha = distribution(rngRadius);

			if (alpha < double(modeling_distr.Geta() - j) / (n - i))
				++j;
			++i;
		}

		
		observed_frequences_modeling[k] = j;
	}
}


 

