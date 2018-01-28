Asu MathLab Project
====================
## Table of Contents
- [Intro](#intro)
- [Setup](#setup)
- [Take it for a spin](#take-it-for-a-spin)
- [Phase 1](#phase-1-description)
- [Features](#features)
- [Phase 2](#phase-2-description)
- [ToDo](#todo)
- [Additional](#additional)

## Intro

<h4 align="center">Another mathematical library software similar to Matlab and Octave.</h4>
Asu MathLab Project is written in C++ using Object Oriented Programming (OOP) Concepts

The aim of the software is to
take any File containing Matlab or Octave Command and execute it

Asu Mathlab will try to extract the following information:

-  Matrix Definition Commands
-  Operation Lines on Given Matrices

## Setup

Clone this repository on your linux machine.

    git clone https://github.com/MinaMourice/AsuMathLabG14.git
Open your terminal and navigate to the repo's directory.

    cd AsuMathLabG14
Run make command to compile the library:    
    
    make
    
Run ./matrix command to run the library in your terminal:

    ./matrix
    
    
## Take it for a spin

    >A = [2.2 7.3 4.8 2.4; 2.3 6.5 8.9 1.2; 4.9 3.8 7.2 7.5; 9.8 3.4 7.5 8.9]
    >B = [3.4 5.7 4.2 1.4; 6.3 2.5 8.1 3.1; 6.4 2.8 7.1 8.1; 3.2 5.1 7.2 6.2]
    >C = A + B
    >D = A - B
    >E = A * B
    >H = C'
    >G = 1 ./ A
    >F = A / B 


## Phase 1 Description

- Implement C++ class for matrix
- Support dynamic creation and destruction of matrices of any size
- Support addition, subtraction, multiplication, transpose and division
- Process input user commands and show results directly 
- Process input file, show each step result then exit


## Features
* [x] Reading scripts support.
* [x] Command line support.
* [x] Complex numbers support.
* [x] Matrix addition and subtraction.
* [x] Matrix determinant and inverse.
* [x] Matrix multiplication and division.
* [x] Matrix transpose.


## Phase 2 Description

- Support mathematical functions. 
    * Trigonometric, Logarithmic, Roots, Power
- Support mathematical expressions.
    * Either with (dot) or not.
- Support flexible matrix parser.
    * Accept matrix in matrix, expressions and variables 
- Support error handling.
    * Do not crash for invalid input.




## Phase 2 Description

- Support mathematical functions. 
    * Trigonometric, Logarithmic, Roots, Power
- Support mathematical expressions.
    * Either with (dot) or not.
- Support flexible matrix parser.
    * Accept matrix in matrix, expressions and variables 
- Support error handling.
    * Do not crash for invalid input.


## ToDo

* [x] Matrix trigonometric functions.
* [x] Matrix inverse trigonometric functions.
* [x] Matrix hyperbolic functions.
* [x] Matrix inverse hyperbolic functions.
* [x] Matrix bitWise functions.
* [x] Matrix logarithmic and exponential functions.
* [X] Matrix roots and power functions.
* [X] Error Handling.





## Additional
You can always check [the doctor's project charter](https://docs.google.com/presentation/d/1UIO4qOuu7vfbQWdxS-UbUa06dTc-YmUGgjZ1Gn9T0Bo/), [our google drive spreadsheet](
https://docs.google.com/spreadsheets/d/1DseCvOymkYyLX0A7mNgsOQ_dZ9WUEAJQ0_6GCJYxdfg/) , or [our ZenHub Issues Management Board](https://app.zenhub.com/workspace/o/minamourice/asumathlabg14/boards).

