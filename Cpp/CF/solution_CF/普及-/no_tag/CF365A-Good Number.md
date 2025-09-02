# Good Number

## 题目描述

Let's call a number $ k $ -good if it contains all digits not exceeding $ k $ ( $ 0,...,k $ ). You've got a number $ k $ and an array $ a $ containing $ n $ numbers. Find out how many $ k $ -good numbers are in $ a $ (count each number every time it occurs in array $ a $ ).

## 样例 #1

### 输入

```
10 6
1234560
1234560
1234560
1234560
1234560
1234560
1234560
1234560
1234560
1234560
```

### 输出

```
10
```

## 样例 #2

### 输入

```
2 1
1
10
```

### 输出

```
1
```

# 题解

## 作者：Alex_Wei (赞：14)

### 一道简单的模拟题

具体思路见代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a,i,v[10],pd;//i:答案，v[x]:a中是否包含x，pd:是不是好数 
int main()
{
	cin>>n>>k;
	for(int x=1;x<=n;x++){
		cin>>a,memset(v,0,sizeof(v)),pd=1;//输入，清零，假设a是好数 
		while(a)v[a%10]=1,a/=10;//记录每一位上的数字 
		for(int y=0;y<=k;y++)if(!v[y])pd=0;//如果0-k之间有一个数不包含，就不是好数
		if(pd)i++;
	}
	cout<<i;
	return 0;
}//望管理员通过
```
#### 珍爱生命，远离抄袭！~~（这么简单的一道题应该不会有人抄袭吧）~~

如果愿意就点个赞吧，谢谢！

---

## 作者：teacup (赞：1)

# 题解 CF365A Good Number 第三篇题解
## 先看题：
若一个数的各位包含$($但不限于$)0$~$k$的每个数,则它是一个"$k$好数".
$(0\le k\le9)$.现给出一个有$n$个数的数列$a$，问其中有多少个数是"$k$好数"?
### 题意：
给你$n$个数，问你在这些数中，有多少个数的各个数位包括了从$0$到$k$所有的数。
### 思路：
对于一个数$a_i,$我们可以用循环+标记的方式判断它有没有$0$~$k$的每个数，如果有则ans++，否则直接继续。

上代码~:
```cpp
#include<cstdio>
using namespace std;
int i,n,t,k,sum=0,x;//i,x是循环变量
//n,k就是题目里的意思
//sum是k好数的数量
//t是题目输入的数
bool a[10],b;//若ai为1，表示当前这个数各个数位里有i这个数
//否则当前表示这个数各个数位里没有有i这个数
//若ai为1，表示当前这个数是k好数
//否则当前这个数不是k好数
int main(){
	scanf("%d%d",&n,&k);//读入n,k
	for(i=0;i<n;i++){
		scanf("%d",&t),b=1;//输入，假设t是k好数 
		for(x=0;x<=k;x++) a[x]=0;//清零a数组
		while(t) a[t%10]=1,t/=10;//循环标记
		for(x=0;x<=k;x++) if(!a[x]) b=0;//检查t是不是k好数
		if(b) sum++;//如果是，sum++
	}
	printf("%d",sum);//输出答案
    return 0;
}
```

---

## 作者：yuangq (赞：1)

# 这题只是需要按照它的规矩枚举即可


### 上代码
~~~
#include<iostream>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<stack>
#include<queue>
#include<set>
#include<map>
#include<ctime>
#include<climits>
#include<vector>
using namespace std;
int ss;
int s[100];
void if_good(int k,int a)//函数，算它是不是好数 
{
	for(int j=0;j<=13;j++)
	{
		s[j]=0;
	} 
	if(a==0)
	{
		s[0]++;//注意特判0的情况 
	}
	else
	{
		while(a!=0)
		{
			s[a%10]++;
			a=a/10; 
		}
	}
	for(int j=0;j<=k;j++)
	{
		if(s[j]==0)//如果有任何一个数字不满足直接跳出 
		{
			return;
		}
	}
	ss++;
	cout<<endl;
	return;
}
int main()
{
    int n,k;
    cin>>n>>k;
    for(int i=0;i<n;i++)
    {
    	int a;
    	cin>>a;
    	if_good(k,a);
    }
    cout<<ss;
    return 0;
}
~~~

---

## 作者：hensier (赞：0)

我们可以把读入进来的数当做字符串来处理。

假设这个字符串为$s$。

因为我们要检查这个字符串中是否包含$0$至$k$中的所有数位，所以不妨把这个字符串进行从小到大的排序。

例如，对于$s=182394,k=4$来说，我们用$sort$将$s$从小到大排列，即：

$s=182394\to s=123489$

通过一个$bool$数组$flag$来记录每一位的出现情况。

我们对字符串每一个字符进行判断，如果当前字符对应的数值已经超过$k$，就可以不必再继续下去。如果小于等于$k$，就标记$flag_{s_i-48}$为真。

最后判断在$i∈[0,k]$范围内，是否有$s_i=false$的情况。如果有的话，说明该数不是$\text{Good Number}$，否则该数就是$\text{Good Number}$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,ans;
string s;
bool check(string x)
{
    bool flag[10]={false};//初始全为false
    for(int i=0;x[i];i++)
    {
        if(x[i]>k+48)break;//判断是否已经超过k
        flag[x[i]^48]=true;//标记flag数组
    }
    for(int i=0;i<=k;i++)if(!flag[i])return false;//有一个为false就说明它不是满足条件的数，所以返回假
    return true;//返回真
}
int main()
{
    cin>>n>>k;
    while(n--)
    {
        cin>>s;
        sort(s.begin(),s.end());//从小到大排列
        ans+=check(s);//真就加1，假就加0
    }
    cout<<ans;
    return 0;
}
```

---

