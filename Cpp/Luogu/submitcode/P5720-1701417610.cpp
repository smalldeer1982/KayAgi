#include<iostream>
using namespace std;
int main(){
    long long a;
    int i;
    cin>>a;
    for(i=2;a!=1;i++)
    {
        a/=2;
    }
    cout<<i-1;
    return 0;
}