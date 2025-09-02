# Mammoth's Genome Decoding

## 题目描述

给定长度为 n 且只含有 A、T、C、G和? 的字符串s，其中?可以转换为任何一个字母，问是否存在一个字符串，使得将所有的?替换成字母后，A、T、C、G个数相等。

## 样例 #1

### 输入

```
8
AG?C??CT
```

### 输出

```
AGACGTCT
```

## 样例 #2

### 输入

```
4
AGCT
```

### 输出

```
AGCT
```

## 样例 #3

### 输入

```
6
????G?
```

### 输出

```
===
```

## 样例 #4

### 输入

```
4
AA??
```

### 输出

```
===
```

# 题解

## 作者：cq_loves_Capoo (赞：3)

这题好恶心qwq，专门恶心我这种蒟蒻    
  
题目里面写了：只含有 A T C G ? 五个字符，那么这题难度就缩小了很多。    
  
首先，由于目标字符串是四个字母个数一样，那么如果 $n$ 不是 4 的倍数，那么直接输出 `===` 退出程序。   
  
其次，每个字母出现次数都不能超过 $n / 4$，因为如果一旦超过，就不能完成四个字母个数一样了。   
   
不可能的情况都判断完了，剩下的就是重要的部分了qwq ：
   
1. 记录下每个字符出现的次数（除了问号）。   
  
2. 跑一遍整个字符串，假如该字符是个问号，那么就找一个还没到 $n / 4$ 的字符，把问号变为该字符。   
  
最后输出字符串就 ok 了qwq   
  
代码（感觉好短qwq）： 
   
```
#include <bits/stdc++.h>
#define endl '\n'
#pragma GCC optimize(3)

using namespace std;
int len, b[255];
char a[1005];

inline char find() {//找字符的函数 
	if (b['A'] < len / 4) return 'A';//如果 A 出现个数没到 n/4 就返回 A 
	if (b['T'] < len / 4) return 'T';//同上 
	if (b['C'] < len / 4) return 'C';
	if (b['G'] < len / 4) return 'G';
}

signed main() {
	ios::sync_with_stdio(false);
	cin >> len;
	if (len % 4 != 0) return cout << "===", 0;//如果不是 4 的倍数就可以退出程序了 
	for (int i=1; i<=len; i++) {
		cin >> a[i];
		if (a[i] != '?') {//问号不算 
			b[a[i]] ++;
			if (len / 4 < b[a[i]]) return cout << "===", 0;//假如出现次数 > n / 4 就退出程序 
		}
	}
	for (int i=1; i<=len; i++) {
		if (a[i] == '?') a[i] = find(), b[a[i]] ++;//假如是问号，就寻找该字符应该是什么，并且该字符出现次数 + 1. 
	}
	for (int i=1; i<=len; i++) cout << a[i];//输出 
	return 0;
}
``` 
   
再也不想做毒瘤模拟了/kk 

---

## 作者：Cambridge (赞：1)


升初一后提交的第一篇题解，本蒟蒻又来发题解了！

这道题其实没有省选题的难度，废话不多说，直接进入正题。这道题的大致意思就是将"?"全部，注意是全部换成字母后所有字母的个数都相等。问有没有转换的方法，如果有，输出转换后的字符串，如果没有，就输出“===”。

接下来我讲讲这道题的解法。首先，我们先统计这四种字母“A、T、C、G”分别有多少个，然后也统计"?"有多少个。我们再找字母最多有多少个，为什么要这样子做呢？因为我们要保证所有字母的个数都相等，但是我们不能删减字母，所以就只能将少的字母增加到最多的个数了。但是我们还要注意一点，有可能全部字母个数都相等了，但是还剩下了问号，我们就要继续转换。我们要判断剩下问号有多少个，看看个数%4是否为0。因为我们要保证最后个数相等。

以上就是这道题的解法了，如果还是看不懂，就接着看代码：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstdlib>
#include<algorithm>//文件头 
using namespace std;
long long n;
char a[100000];
int as,gs,cs,ts,wss,maxs,cha;//定义变量 
int main()
{
cin>>n;
for(int i=1; i<=n; i++)
{
	cin>>a[i];
	if(a[i]=='A')as++;
	if(a[i]=='G')gs++;
	if(a[i]=='C')cs++;
	if(a[i]=='T')ts++;
	if(a[i]=='?')wss++;//累计个数 
}
maxs=max(max(max(as,gs),cs),ts);//找最多的次数 
cha=(maxs-as)+(maxs-gs)+(maxs-cs)+(maxs-ts);//求差 
if(wss-cha<0){cout<<"===";return 0;}//如果问号不够 
if((wss-cha)%4==0)
{
	int gss=maxs+(wss-cha)/4;
	for(int i=1; i<=n; i++)
	{
		if(a[i]!='?')cout<<a[i];
		else
		{
			if(as<gss){cout<<"A";as++;continue;}
			if(gs<gss){cout<<"G";gs++;continue;}
			if(cs<gss){cout<<"C";cs++;continue;}
			if(ts<gss)cout<<"T",ts++;//输出 
		}
	}
}
else cout<<"===";
return 0;
}
```

好了，本蒟蒻就讲到这里，希望对读者有所帮助。

---

## 作者：Ink_Sakuya (赞：0)

本蒟蒻的第一篇题解，请多多关照。

## 正片开始

题面已经说的够清楚了，本人就不再复述了（[题面传送门](https://www.luogu.com.cn/problem/CF747B)）。

首先我们可以 Pass 掉下面两种情况：

> 1.$n$ 不能被 $4$ 整除;

> 2.$A,T,G,C$ 中任意字符在字符串中出现的次数大于 $n/4$ 。

于是，我们就可以先判断数据是否符合条件：
```cpp
int a=0,c=0,g=0,t=0,n;
char x[1010];
scanf("%d%s",&n,x);
if(n%4!=0) cout<<"===",exit(0);
int i;
for(i=0;i<n;i++)
{
	if(x[i]=='A') a++;
	if(x[i]=='C') c++;
	if(x[i]=='G') g++;
	if(x[i]=='T') t++;
}
if(a>n/4||c>n/4||g>n/4||t>n/4) cout<<"===",exit(0);
```
然后用 $n/4$ 减去 $A,T,G,C$ 在字符串中分别出现的次数，就得到了 $A,T,G,C$ 在字符串中还需要出现的次数。

然后就依次把 $?$ 替换成 $A,T,G,C$ 中的一个，使得 $A,T,G,C$ 在字符串中出现的次数都为 $n/4$ ，然后这道题就完事了。
```cpp
i=0;
while(a!=n/4)
{
	if(x[i]=='?') x[i]='A',a++;
	i++;
}
while(c!=n/4)
{
	if(x[i]=='?') x[i]='C',c++;
	i++;
}
while(g!=n/4)
{
	if(x[i]=='?') x[i]='G',g++;
	i++;
}
while(t!=n/4)
{
	if(x[i]=='?') x[i]='T',t++;
	i++;
}
```

然后输出字符串（`puts(x);`）。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define xiaogendui priority_queue <int,vector<int>,greater<int> >;
#define dagendui priority_queue <int,vector<int>,less<int> >;
int main()
{
	int a=0,c=0,g=0,t=0,n;
	char x[1010];
	scanf("%d%s",&n,x);
	if(n%4!=0) cout<<"===",exit(0);   //特判1
	int i;
	for(i=0;i<n;i++)
	{
		if(x[i]=='A') a++;
		if(x[i]=='C') c++;
		if(x[i]=='G') g++;
		if(x[i]=='T') t++;
	}     //统计出现次数
	if(a>n/4||c>n/4||g>n/4||t>n/4) cout<<"===",exit(0);     //特判2
	i=0;
	while(a!=n/4)
	{
		if(x[i]=='?') x[i]='A',a++;
		i++;
	}
	while(c!=n/4)
	{
		if(x[i]=='?') x[i]='C',c++;
		i++;
	}
	while(g!=n/4)
	{
		if(x[i]=='?') x[i]='G',g++;
		i++;
	}
	while(t!=n/4)
	{
		if(x[i]=='?') x[i]='T',t++;
		i++;
	}
	puts(x);
}
```

---

