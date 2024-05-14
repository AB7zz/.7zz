using namespace std;

#include "iostream"
#include "stdio.h"
bool something(int a){for (int i= 0;i< a;i++){cout<< i;cout<< '\n';} return (true);} int main() {int a;bool b;a= 5;b= something(a);cout<< b;} 