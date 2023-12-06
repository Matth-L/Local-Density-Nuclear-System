# Local Density Nuclear System

This project is a class assignment for the HPC course at ENSIIE. Our goal is to plot the local density of a nuclear system.

## Table of Contents

- [Local Density Nuclear System](#local-density-nuclear-system)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Requirements](#requirements)
  - [Installation](#installation)
  - [Usage](#usage)
  - [Commands](#commands)

## Introduction

TODO 
![Local Density Nuclear System](/pres/image/resultat.png)

## Requirements

This project uses the following libraries:
- C++11
- armadillo (C++ library)
- cxxtest (C++ library)
- Python 3
- matplotlib (Python library)
- astyle (code formatter)
- doxygen (documentation generator)
- povray 

## Installation

for Debian distributions, you can install the libraries using the following command:
```sh
sudo apt-get install libarmadillo-dev cxxtest python3 python3-matplotlib build-essential astyle doxygen povray
```

To install this project on your computer, you can clone the repository using the following command:

```sh
git clone https://gitlab.pedago.ensiie.fr/romeo.louati/local-density-nuclear-system
```

## Armadillo's library

We use the armadillo's library to do most of our calculations. This library is one of the fastest available to do linear algebra, it uses LAPACK, BLAS ...

See more here : http://arma.sourceforge.net/

## Commands

Here are the main commands you can run using the makefile:

- Compile the entire project, including doxygen documentation: `make`
- Compile the code only: `make code`
- Compile the documentation only: `make doc`
- View the result: `make pov`
- Clean the project: `make clean`
- Run tests before any commit: `make tests`
- Format the code: `make style`

We use astyle to format our code, you can find the configuration file in the makefile
See more : http://astyle.sourceforge.net/