# sudokuloeser

## About

sudokuloeser is a simple sudoku solver written in C. It is optimized for speed.

## Features

With sudokuloeser you can easily solve sudokus.

Optional you can specify a file, where to save the solution.

For better usage the Output is colored.

## Requirements

* Linux
* Windows: some restrictions  
  `make ARCH=win`
* C Compiler

## Installation

    ./configure
    make
    make install

## Usage

    Usage:
      ./sudokuloeser [options] <input_file>
    Options
      -U         Unicode borders
      -h         This help
      -H         HTML-Output
      -o <file>  Output-File
      -O <file>  Overlay for non-standard files
      -c         No colors
      -p         Plaintext
      -n         Dont solve, just print
      -s         silent
