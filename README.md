# Fuzzy Logic Systems for Exoplanet Likelihood Estimation in K-type Stars and M-dwarfs

The two Python-based fuzzy logic systems (`exoktype.ipynb` and `exomdwarfs.ipynb`) designed to estimate the likelihood of exoplanet presence based on transit data. The systems use skfuzzy to create a control system that evaluates the depth and duration of light dips, as well as the interval between these dips, to calculate the likelihood of an exoplanet’s existence. Each system is tailored to a specific type of star: K-type stars and dwarf stars.

## Key Features

- **Universe of Discourse**: Tailored to K-type stars and M-dwarfs, the systems analyze transit data specific to these stars.
- **Linguistic Variables**: 'Small', 'medium', and 'large' for depth of dip; 'short', 'medium', and 'long' for duration and interval.
- **Fuzzy Rules**: 27 rules determine the likelihood of exoplanet existence.
- **Simulation**: Users can input observed values and compute the exoplanet likelihood.

## Usage

1. Open the relevant notebook (`exoktype.ipynb` for K-type stars, `exomdwarfs.ipynb` for M-dwarfs).
2. Import libraries and define the universe of discourse.
3. Set up linguistic variables and membership functions.
4. Define fuzzy rules and create a control system.
5. Run the simulation with observed values to compute the likelihood.

**Note**: The code is specifically designed for the unique transit signatures of K-type stars and M-dwarfs.

---

## Fuzzy Logic Inference System for Exoplanet Detection (`exoplanet_detection.c`)

This C program implements a fuzzy logic inference system designed to evaluate the likelihood of a celestial object being an exoplanet based on three linguistic variables: depth of dip in light intensity (measured in parts per million, ppm), duration of the dip (measured in hours), and interval between dips (measured in days). The program uses fuzzification, rule evaluation, and defuzzification to process the input values and produce a crisp output representing the probability of the celestial object being an exoplanet.

### Features

- **Fuzzification**: Converts crisp input values for depth, duration, and interval into fuzzy values.
- **Rule Evaluation**: Applies a set of fuzzy rules to determine the likelihood of the celestial object being an exoplanet.
- **Defuzzification**: Uses the centroid method to convert the fuzzy likelihood back into a crisp value.

### Usage

1. Input the crisp values for depth, duration, and interval.
2. The program will fuzzify these values, apply the fuzzy rules, and then aggregate the results.
3. The defuzzified output will indicate whether the celestial object is likely an exoplanet based on the given threshold.

**How It Works**: The program defines constants for the linguistic variables and their membership functions. It includes functions for fuzzification of each variable, cleaning strings, adding and parsing rules, and the inference engine which applies the fuzzy logic. The aggregation function combines the results of the rules, and the defuzzification function calculates the final crisp value.

**Note**: The program assumes the presence of a file named rules.txt containing the fuzzy rules, which should be loaded and parsed accordingly. The main function demonstrates the process from fuzzification to defuzzification with example input values. This code is designed for direct manipulation by a user with knowledge of C programming and fuzzy logic principles.

---

## Fuzzy Logic Visualization for Exoplanet Analysis (`ExoplanetFuzzyDiscourse.py`)

**Purpose**: This Python script, ExoplanetFuzzyDiscourse.py, provides a visualization for a fuzzy logic system implemented in a C program. The system is designed for analyzing exoplanet data.

### Features

- **Universe Definition**: Defines universes of discourse for depth, duration, interval, and likelihood of exoplanet characteristics.
- **Membership Functions**: Implements triangular membership functions for small, medium, and large depths; short, medium, and long durations and intervals; and unlikely and likely likelihoods.
- **Plotting**: Uses matplotlib to plot membership functions, providing a visual representation of the fuzzy sets used in the C program.

**Note**: This script is part of a larger project that includes a C program implementing a fuzzy logic system for exoplanet analysis. The Python script aids in understanding and interpreting the fuzzy logic used in the C program.
