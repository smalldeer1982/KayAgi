# Lord of the Values

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1523B/98f109d71d38cfa25029619d650ed4d2b886de82.png)While trading on his favorite exchange trader William realized that he found a vulnerability. Using this vulnerability he could change the values of certain internal variables to his advantage. To play around he decided to change the values of all internal variables from $ a_1, a_2, \ldots, a_n $ to $ -a_1, -a_2, \ldots, -a_n $ . For some unknown reason, the number of service variables is always an even number.

William understands that with his every action he attracts more and more attention from the exchange's security team, so the number of his actions must not exceed $ 5\,000 $ and after every operation no variable can have an absolute value greater than $ 10^{18} $ . William can perform actions of two types for two chosen variables with indices $ i $ and $ j $ , where $ i < j $ :

1. Perform assignment $ a_i = a_i + a_j $
2. Perform assignment $ a_j = a_j - a_i $

 William wants you to develop a strategy that will get all the internal variables to the desired values.

## 说明/提示

For the first sample test case one possible sequence of operations is as follows:

1. "2 1 2". Values of variables after performing the operation: \[1, 0, 1, 1\]
2. "2 1 2". Values of variables after performing the operation: \[1, -1, 1, 1\]
3. "2 1 3". Values of variables after performing the operation: \[1, -1, 0, 1\]
4. "2 1 3". Values of variables after performing the operation: \[1, -1, -1, 1\]
5. "2 1 4". Values of variables after performing the operation: \[1, -1, -1, 0\]
6. "2 1 4". Values of variables after performing the operation: \[1, -1, -1, -1\]
7. "1 1 2". Values of variables after performing the operation: \[0, -1, -1, -1\]
8. "1 1 2". Values of variables after performing the operation: \[-1, -1, -1, -1\]

For the second sample test case one possible sequence of operations is as follows:

1. "2 1 4". Values of variables after performing the operation: \[4, 3, 1, -2\]
2. "1 2 4". Values of variables after performing the operation: \[4, 1, 1, -2\]
3. "1 2 4". Values of variables after performing the operation: \[4, -1, 1, -2\]
4. "1 2 4". Values of variables after performing the operation: \[4, -3, 1, -2\]
5. "1 3 4". Values of variables after performing the operation: \[4, -3, -1, -2\]
6. "1 1 2". Values of variables after performing the operation: \[1, -3, -1, -2\]
7. "1 1 2". Values of variables after performing the operation: \[-2, -3, -1, -2\]
8. "1 1 4". Values of variables after performing the operation: \[-4, -3, -1, -2\]

## 样例 #1

### 输入

```
2
4
1 1 1 1
4
4 3 1 2```

### 输出

```
8
2 1 2
2 1 2
2 1 3
2 1 3
2 1 4
2 1 4
1 1 2
1 1 2
8
2 1 4
1 2 4
1 2 4
1 2 4
1 3 4
1 1 2
1 1 2
1 1 4```

# 题解

## 作者：Froranzen (赞：2)

## CF1523B


------------

### 思路

因为题目保证 $n$ 是偶数，所以我们尝试找一下两个数之间的关系。

设 $a_i$，$a_j$，且 $i < j $。

1. 执行操作 1 或操作 2 都无所谓，笔者选择执行操作 2。   
两个数变为 $a_i$， $a_j - a_i$。

2. 执行操作 1 ， 因为可以消掉第一个数里的 $a_i$。   
两个数变为 $a_j$， $a_j - a_i$。

3. 执行操作 2， 因为可以消掉第二个数里的 $a_j$。  
两个数变为 $a_j$，$-a_i$。

4. 执行操作 1，因为可以把 $-a_i$ 移到第一个数里。   
两个数变为 $a_j - a_i$， $-a_i$。

5. 执行操作 2 ，因为可以把第二个数里的 $a_i$ 消掉的同时把 $-a_j$ 移到第二个数里。   
两个数变为 $a_j - a_i$， $-a_j$。

6. 执行操作 1 ， 可以把第一个数里的 $a_j$ 消掉。  
两个数变为 $-a_i$， $-a_j$。

事实上有很多种方法可以在 6 步内使两个数变为它们的相反数，笔者只是提出了一种做法，各位大佬可以自己尝试一下别的方法。

所以总操作数为 $3n$。

### 代码

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
#define max_(a, b) a > b ? a : b
#define min_(a, b) a < b ? a : b
#define rep(i, f, t) for(register int i(f); i <= t; ++i)
#define per(i, f, t) for(register int i(t); i >= f; --i)
typedef long long ll;
 
 
/***************??***************/

namespace IO {
char buf[1<<21], *p1 = buf, *p2 = buf, buf1[1<<21];
inline char gc () {return p1 == p2 && (p2 = (p1 = buf) + fread (buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++;}

#ifndef ONLINE_JUDGE
#endif

template<class I>
inline void read(I &x) {
    x = 0; I f = 1; char c = gc();
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = gc(); }
    while(c >= '0' && c <= '9') {x = x * 10 + c - '0'; c = gc(); }
    x *= f;
}

template<class I>
inline void write(I x) {
    if(x == 0) {putchar('0'); return;}
    I tmp = x > 0 ? x : -x;
    if(x < 0) putchar('-');
    int cnt = 0;
    while(tmp > 0) {
        buf1[cnt++] = tmp % 10 + '0';
        tmp /= 10;
    }
    while(cnt > 0) putchar(buf1[--cnt]);
}

#define in(x) read(x)
#define outn(x) write(x), putchar('\n')
#define out(x) write(x), putchar(' ')

} using namespace IO;

/***************??***************/

int t, n;
int val[1003];

int main () {
    read(t);
    while(t--) {
        read(n);
        rep(i, 1, n) read(val[i]);
        int ans = n*3;
        outn(ans);
        for(int i(1); i <= n; i += 2) {
            rep(j, 1, 6) {
                if(j & 1) {
                    out(2), out(i), outn(i+1);
                }
                else out(1), out(i), outn(i+1);
            }
        }
    }
}

/*

2 ai aj - ai  
1 aj aj - ai  
2 aj -ai  
1 aj - ai -ai
2 aj - ai -aj 
1 -ai -aj
*/
```

------------


感谢您能阅读本篇博客~

---

## 作者：Lijunzhuo (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1523B)。

从方案入手，考虑对于两个数进行操作，使得它们变成相反数。因为次数最多为 $5000$ 种，所以最多每两个点进行运算 $10$ 次。可以打出如下代码（使用迭代加深搜索算法简化版）：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,ansa,ansb,A[17];
void print(int n)
{
	for(int i=1;i<=n;i++)
		printf("%d ",A[i]);
	putchar('\n');
	return ;
}
void idDFS(int x,int y,int dep,int maxdep)
{
	if(dep>maxdep) return ;
	if(x==ansa&&y==ansb)
	{
		print(dep-1);
		return ;
	}
	//暴力枚举两种可能。 
	A[dep]=1;idDFS(x+y,y,dep+1,maxdep);
	A[dep]=2;idDFS(x,y-x,dep+1,maxdep);
}
int main()
{
	a=11/*这只是一个例子*/,b=10/*同左*/;
	ansa=-a,ansb=-b;
	for(int i=1;i<=10;i++)
		idDFS(a,b,1,i);
	return 0;
}
```
随便调整变量 $a$ 和 $b$ 的值，我们发现最坏情况下最少需 $6$ 次才能变成相反数（[方案](https://www.luogu.com.cn/paste/6q1f4abf)），小于 $10$。所以这道题就可以通过了：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a,ans[32][6]={{1,1,2,1,1,2},{1,2,1,1,2,1},{1,2,1,2,1,2},{1,2,2,1,2,2},{2,1,1,2,1,1},{2,1,2,1,2,1},{2,1,2,2,1,2},{2,2,1,2,2,1},{1,1,2,1,1,2},{1,2,1,1,2,1},{1,2,1,2,1,2},{1,2,2,1,2,2},{2,1,1,2,1,1},{2,1,2,1,2,1},{2,1,2,2,1,2},{2,2,1,2,2,1},{1,1,2,1,1,2},{1,2,1,1,2,1},{1,2,1,2,1,2},{1,2,2,1,2,2},{2,1,1,2,1,1},{2,1,2,1,2,1},{2,1,2,2,1,2},{2,2,1,2,2,1},{1,1,2,1,1,2},{1,2,1,1,2,1},{1,2,1,2,1,2},{1,2,2,1,2,2},{2,1,1,2,1,1},{2,1,2,1,2,1},{2,1,2,2,1,2},{2,2,1,2,2,1}};
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		srand(T*n*n);
		for(int i=1;i<=n;i++)
			scanf("%d",&a);
		printf("%d\n",n*3);
		for(int i=1;i<=n;i+=2)
		{
			int x=rand()%32;
			for(int j=0;j<6;j++)
				printf("%d %d %d\n",ans[x][j],i,i+1);
		}
	}
	return 0;
}//随机代码qaq 
```
[提交记录](https://codeforces.com/contest/1523/submission/287665333)。

---

## 作者：cmll02 (赞：1)

$n$ 是偶数这个条件很奇怪对吧。。

这提示我们两个数一起处理。

枚举 $2^{10}$ 种操作序列之后我们发现：

对两个数进行 $1,2,1,1,2,1$ 可以让两个数变成它们自身的相反数。

操作长度为 $3n$。

```cpp
// Problem: B. Lord of the Values
// Contest: Codeforces - Deltix Round, Spring 2021 (open for everyone, rated, Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/1523/problem/B
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <stdio.h>
#include <string.h> 
#include <algorithm>
#include <queue>
#define od(x) printf("%d",x)
#define odb(x) printf("%d ",x)
#define odl(x) printf("%d\n",x)
#define odp(x,y) printf("%d %d\n",x,y)
#define ol(x) puts("")
#define old(x) printf("%lld",x)
#define oldb(x) printf("%lld ",x)
#define oldl(x) printf("%lld\n",x)
#define oldp(x,y) printf("%lld %lld\n",x,y)
//#define int long long
inline int read()
{
	int num=0,f=1;char c=getchar();
	while(c<48||c>57){if(c=='-')f=-1;c=getchar();}
	while(c>47&&c<58)num=num*10+(c^48),c=getchar();
	return num*f;
}
inline int re1d()
{
	char c=getchar();
	while(c<48||c>49)c=getchar();
	return c&1;
}
inline int min(int a,int b){return a>b?b:a;}
inline int max(int a,int b){return a<b?b:a;}
signed main()
{
	int T=read();
	while(T--)
	{
		int n=read();
		for(int i=0;i<n;i++)read();
		printf("%d\n",n*3);
		for(int i=1;i<=n;i+=2)
		{
			printf("1 %d %d\n",i,i+1);
			printf("2 %d %d\n",i,i+1);
			printf("1 %d %d\n",i,i+1);
			printf("1 %d %d\n",i,i+1);
			printf("2 %d %d\n",i,i+1);
			printf("1 %d %d\n",i,i+1);
		}
	}
	return 0;
}
```

---

## 作者：AK_400 (赞：0)

这个题我想了几分钟，发现不是很会，于是重新读题，注意到 $n$ 是偶数，于是~~猜测出题人不会做奇数情况~~，考虑偶数性质，尝试将每两个元素分一组，对组内做一些操作，以下操作是可行的（设 $a$ 在 $b$ 前）：


|初始|$a$|$b$|
|:-:|:-:|:-:|
|做操作二|$a$|$b-a$|
|做操作一|$b$|$b-a$|
|做操作二|$b$|$-a$|
|做操作二|$b$|$-b-a$|
|做操作一|$-a$|$-b-a$|
|做操作二|$-a$|$-b$|

于是我们对每两个数做 $6$ 次操作即可变为相反数，共计 $\frac{n}{2}\times 6\le 3000 <5000$ 次，可通过。

---

