# HypergeomStatAnalysis
Analyze hypergeometric distributions and compare them using chi-square tests. Features include parameter calculation, histogram and p-value plots, and power analysis against sample size. Easy-to-use interface for comprehensive statistical analysis.

### Features

1. **Set Distribution Parameters**: Allows setting parameters for the distribution, modeling method, and sample size.
2. **Sample Generation**: Simulate samples using two different methods: the Bernoulli method and the inverse transform method.
3.**Histogram Visualization**: Display histogram against theoretical distribution, chi-square value, degrees of freedom (d.f.), and significance level (p-level).
4. **p-Level Sampling**: Generate samples of p-levels by setting distribution parameters for both the model and the hypothesis, and specify the number of repetitions. Calculates true significance level or test power based on hypothesis parameters.
5. **Empirical Distribution Function**: Plot the empirical distribution function of p-levels against the theoretical uniform distribution.
6. **Power Analysis** Plotted power vs. sample size graphs for given significance levels and alternatives.

### Usage

1. **Set Hypergeometric Distribution Parameters**:
    - Input the total population size (N), the number of success states in the population (K), and the sample size (n).
    - The application will calculate and display the mean, variance, and other relevant statistics.

2. **Generate Samples**:
    - Choose between two different methods for generating samples: the Bernoulli method and the inverse transform method.
    - Input the necessary parameters for sample generation.

3. **Chi-Square Test**:
    - Input the parameters for two hypergeometric distributions.
    - The application will perform a chi-square test to compare the distributions and display the chi-square value, degrees of freedom, and p-value.

4. **Visualize Histograms**:
    - Generate histograms of the sample distributions.
    - Overlay the histogram with the theoretical distribution.

5. **p-Level Sampling**:
    - Input parameters for the distribution being modeled and the distribution being tested against.
    - Specify the number of repetitions.
    - The application will generate a sample of p-levels, calculate the empirical significance level or test power, and plot the empirical distribution function against the theoretical uniform distribution.

### Development

This application uses Microsoft Foundation Class (MFC) for the graphical user interface. Ensure you have the necessary development environment set up for building MFC applications.

### Documentation

- Documentation has been generated using Doxygen and includes:

    - **User Documentation**: A user manual detailing how to use the application, set parameters, generate samples, and interpret results. The interface is designed to be intuitive, but detailed instructions are provided for clarity.

   - **Developer Documentation**: Comprehensive documentation for developers, including:
        - ***Class Descriptions***: Detailed descriptions of each class, including purpose and functionality.
        - ***Method Descriptions***: Detailed descriptions of methods, including parameters, return values, and examples of usage.
        - ***Code Comments***: Inline comments throughout the code to explain complex logic and algorithms.
        - ***Doxygen Output***: Generated HTML and PDF documentation from comments in the code. The documentation can be found in the docs directory.
