# パスワード

## 题目描述

题目：密码

# 题解

## 作者：Egg_eating_master (赞：2)

看到各位大佬都是手动模拟比较字符串。。。

手动比较干嘛啊。。。string不是自带了比较功能吗？！
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s[51],ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>s[i];
	ans=s[1]+s[2];//首先要给ans赋初值，因为系统给ans赋的初值为空串
	for(int i=1;i<=n;i++)
	    for(int j=1;j<=n;j++)
	        if(i!=j&&ans>s[i]+s[j])//要输出最小的所以不能忍受ans比别人更大
	            ans=s[i]+s[j];//更新
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：Leap_Frog (赞：0)

# AT167 【パスワード】（题解）

### PS.
看到这个数据范围$\texttt{n<=50}$就知道这是一道模拟题。  

### 具体解题过程
~~略~~  
看代码注释

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string ans,s[55];
inline char cmp(string s1,string s2)	//这个是判断函数
{
	for(int i=0,e=min(s1.size(),s2.size());i<e;i++)		//枚举每一位
		if(s1[i]!=s2[i])	//如果不相同直接返回
			return s1[i]<s2[i];
	return s1.size()<s2.size();	//返回字串长的大小关系
}
int main()
{
	ios::sync_with_stdio(false),cin>>n;		//全屏cin,cout，当然要开读优
	for(int i=1;i<=n;i++) cin>>s[i];	//输入
	ans=s[1]+s[2];		//赋初值
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(i!=j&&cmp(s[i]+s[j],ans)) ans=s[i]+s[j];		//枚举第一个字串与第二个字串
	return cout<<ans<<endl,0;	//输出答案并完美的结束
}
```

---

