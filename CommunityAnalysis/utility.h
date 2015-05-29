#ifndef UTILITY_H
#define UTILITY_H
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>   /* time */
#include <vector>
#include <stack>
#include "ReadWriteGraph.h"
#include "dense"

using Eigen::MatrixXd;
using namespace std;
using std::string;

//预定义几种颜色
string Color[] = { "rgb(255,0,0)", "rgb(0,255,0)", "rgb(0,0,255)", "rgb(255,255,0)"};
string NonCommunityColor[] = { "rgb(0,0,0)" };
string edgeColor = { "rgb(128,128,128)", "rgb(0,128,128)", "rgb(0,0,128)", "rgb(64,255,255)" };

#endif