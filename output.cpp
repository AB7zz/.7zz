#include <iostream>
#include <stdlib.h>
using namespace std;

int factorial(int n){if (n == 0 || n == 1){return 1;}else{return n*factorial(n-1);}}int main(){cout<<factorial(5)<<endl;}