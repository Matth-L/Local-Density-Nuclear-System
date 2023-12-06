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

for Debian distributions, you can install the libraries using the following command:

```sh
sudo apt-get install libarmadillo-dev cxxtest python3 python3-matplotlib build-essential astyle doxygen povray
```

## Installation

To install this project on your computer, you can clone the repository using the following command:

```sh
git clone https://gitlab.pedago.ensiie.fr/romeo.louati/local-density-nuclear-system
```

## Usage

We use the armadillo's library to do most of our calculations. This library is one of the fastest available to do linear algebra, it uses LAPACK, BLAS ...

See more here : http://arma.sourceforge.net/

## Commands

There is different option that can be done using makefile : 

If you wish to compile the entire project, including doxygen documentation, run the following command:

```makefile
make 
```

If you wish to compile the code only, run the following command:

```makefile
make code
```

If you wish to compile the documentation only, run the following command:
```makefile
make doc
```

The documentation will be generated in the doc folder. You can open the index.html file to see the documentation. Our class being in French, the documentation is written in French. e.g : 
```sh 
firefox & doc/html/index.html
```

Our presentation is located in the pres folder, you can access it using the following command:
```sh
firefox & pres/index.html
```

If you intend to clean the project, run the following command:
```makefile
make clean
```
the makefile are recursive, so you can run the same command inside the different folders to clean the specific folder.

Before any commit, we ask that you run the following command to check if there is any error in the code:
```makefile
make tests
```

And also please , format your code using the following command :

```makefile
make style 
```
We use astyle to format our code, you can find the configuration file in the root folder.

See more : http://astyle.sourceforge.net/
