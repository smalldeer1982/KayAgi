#include<iostream>
using namespace std;
int a,b,c,flag=1,d; 
int main()
{
    for(int i=1;i<=12;i++)
    {
        a+=300;  
        cin>>b;     
        a-=b;    
           if(a<0)     
           {     
              flag=0;      
              d=i;    
              break;             
           }
        c+=a/100;    
        a%=100;            
    }    
    if(flag==1)      
    {
        a+=c*120;   
        cout<<a;
    }            
    else
    {
        cout<<-d;
    }    
    return 0;
} 