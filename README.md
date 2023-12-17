# Fuzzy Logic Systems for Exoplanet Likelihood Estimation in K-type Stars and M-dwarfs

This repository is dedicated to the exploration and application of fuzzy logic systems for estimating the likelihood of exoplanet presence in K-type stars and M-dwarfs. Utilizing Python notebooks and a C program, we delve into the transit data of these celestial bodies to calculate the probability of exoplanets orbiting them.

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

A C program that evaluates the likelihood of a celestial object being an exoplanet using fuzzification, rule evaluation, and defuzzification.

### Features

- **Fuzzification**: Transforms crisp inputs into fuzzy values.
- **Rule Evaluation**: Applies fuzzy rules to assess exoplanet likelihood.
- **Defuzzification**: Converts fuzzy likelihood to a crisp probability value.

### Usage

1. Input crisp values for depth, duration, and interval.
2. The program processes these values through fuzzification, rule application, and aggregation.
3. The defuzzified output indicates the exoplanet probability.

**How It Works**: The program includes functions for fuzzification, rule parsing, and the inference engine. It assumes a `rules.txt` file with fuzzy rules.

**Note**: Designed for users with knowledge of C programming and fuzzy logic.

---

## Fuzzy Logic Visualization for Exoplanet Analysis (`ExoplanetFuzzyDiscourse.py`)

A Python script that visualizes the fuzzy logic system used in the C program for exoplanet data analysis.

### Features

- **Universe Definition**: Sets universes of discourse for exoplanet characteristics.
- **Membership Functions**: Implements triangular functions for various linguistic variables.
- **Plotting**: Visualizes fuzzy sets with matplotlib.

**Purpose**: To aid in understanding the fuzzy logic in the C program as part of a larger exoplanet analysis project.