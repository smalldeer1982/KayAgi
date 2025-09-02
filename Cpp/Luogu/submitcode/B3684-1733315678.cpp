#include <iostream>
using namespace std;
int x,y;
int main(){
    cin>>x>>y;
    if(x+y<=100){
        if(x>y){
			cout<<"NO"<<endl;
		}
        else if(x<y){
			cout<<"YES"<<endl;
		}
        else if(x==y){
			cout<<"equal probability"<<endl;
		}
    }
    return 0;
}