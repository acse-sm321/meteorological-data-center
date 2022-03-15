# Meteorological-data-center
A implementation for weather data centre written by C++. Inspired by the idea mentioned **[1]**, this project implement the simulation of data centre among geo-destributed nodes (data centers) and transfer/dispatch meteorological data.

## About
```
./meteorological-data-center
|
├── idc     <==> core logics of intermediate data center
├── pthread <==> thread writen by C++
├── public  <==> common file functions and ftp remote access
└── tools   <==> supplementary tools
```
- Techniques: 
    - C++
    - MySQL
    - PostgreSQL
    - other ...

## Configuration
Pre-assume C++ standard for this project is C++20. Built the files with g++ (GCC):
```
g++ (GCC) 4.8.5 20150623 (Red Hat 4.8.5-44)
```
All the datasets (both observed & synthetic) are collected from the internet and will be listed in references.

## Usage
```
$ git clone https://github.com/acse-sm321/cpp-weather-data-center.git
$ cd ./folder
$ make
$ ./exe
```

## Contribution
Feel free to fork and make pull requests. Issues and comments are welcomed.

## Acknowledgements
My family and friends.

## References
**[1]** Taheri, Somayyeh, Maziar Goudarzi, and Osamu Yoshie. “Learning-Based Power Prediction for Geo-Distributed Data Centers: Weather Parameter Analysis.” Journal of big data 7.1 (2020): 1–16. Web.


## License
- [GNU General Public License v3.0](https://github.com/acse-sm321/cpp-weather-data-center/blob/main/LICENSE)
