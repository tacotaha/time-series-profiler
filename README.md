# time-series-profiler
> A tool for generating time series data about the performance of a program

## Description

Given an executable, this tool runs it and queries prov cs about ifddexecution throughout its runtime. The profiler outputs a comma separated stream of data to stdout which can be redirected to a file for later analysis

## Installation

GNU/Linux & OS X:

```
  $ git clone https://github.com/tazzaoui/time-series-profiler.git
  $ cd time-series-profiler
  $ make
```
## Example Usage

The program expects as arguments the path to an executable and optionally an argument to run along the executable. For example
```
    ./profile sleep 1 > outout.csv
```
