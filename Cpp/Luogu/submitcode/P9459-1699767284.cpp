#include<bits/stdc++.h>
using namespace std;
int n;//n组测试数据
string a,b,c,d;//定义a,b,c,d字符串
int main()
{
	cin>>n;//输入测试数据
	for(int i=1;i<=n;i++)
	{
		cin>>a>>b>>c>>d;//输入a,b,c,d四个字符串
		if(a[0]==b[0] && a[0]=='y' && c=="ding" && d=="zhen")//依次判定3个条件
			cout<<"Yes"<<endl;//如果全都满足，输出Yes
		else
			cout<<"No"<<endl;//否则输出No
	}
    return 0;
}
