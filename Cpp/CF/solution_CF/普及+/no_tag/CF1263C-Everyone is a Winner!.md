# Everyone is a Winner!

## 题目描述

给定$n$ 对于所有正整数$k$求出$\lfloor \frac{n}{k} \rfloor$可以有多少种不同的值 并求出所有可能的值

## 样例 #1

### 输入

```
4
5
11
1
3
```

### 输出

```
4
0 1 2 5 
6
0 1 2 3 5 11 
2
0 1 
3
0 1 3 
```

# 题解

## 作者：Rainbow_qwq (赞：7)

[CF1263C Everyone is a Winner!](https://www.luogu.com.cn/problem/CF1263C)

---

# 思路

题意：求所有$\lfloor\dfrac{n}{k}\rfloor\ (k\geq 1)$的值。

先打一个$O(n)$的暴力试一试。

```cpp
int n;
vector<int>res;
void work()
{
	res.clear();
	n=read();
	res.push_back(n);
	For(i,1,n)
		 if(i>1&&n/i!=n/(i-1))
		 	res.push_back(n/i);
	res.push_back(0);
	cout<<res.size()<<endl;
	Rep(i,res.size()-1,0)printf("%d ",res[i]);
	puts("");
}
```
因为$1\leq n\leq 10^9$，所以上面的代码无法AC。

但我们可以打几个小数据出来找找规律。

```cpp
1 : 0 1 
2 : 0 1 2 
3 : 0 1 3 
4 : 0 1 2 4 
5 : 0 1 2 5 
6 : 0 1 2 3 6 
7 : 0 1 2 3 7 
8 : 0 1 2 4 8 
9 : 0 1 2 3 4 9 
10 : 0 1 2 3 5 10 
11 : 0 1 2 3 5 11 
12 : 0 1 2 3 4 6 12 
13 : 0 1 2 3 4 6 13 
14 : 0 1 2 3 4 7 14 
15 : 0 1 2 3 5 7 15 
16 : 0 1 2 3 4 5 8 16 
17 : 0 1 2 3 4 5 8 17 
18 : 0 1 2 3 4 6 9 18 
19 : 0 1 2 3 4 6 9 19 
20 : 0 1 2 3 4 5 6 10 20 
21 : 0 1 2 3 4 5 7 10 21 
22 : 0 1 2 3 4 5 7 11 22 
23 : 0 1 2 3 4 5 7 11 23 
24 : 0 1 2 3 4 6 8 12 24 
25 : 0 1 2 3 4 5 6 8 12 25 
```

~~经观察~~发现，

1. 对于$0\leq x\leq \sqrt{n}$，$x$都是一个正确答案。
2. 对于$1\leq x\leq \sqrt{n}$，$\lfloor\frac{n}{x}\rfloor$都是一个正确答案。

所以只要枚举$0\leq x\leq \sqrt{n}$即可，最后排序一遍。时间复杂度$O(\sqrt{n} \log{\sqrt{n}})$（因为要排序）。

代码：
```cpp
int n;
vector<int>res;
void work()
{
	res.clear();
	n=read();
	int sqn=sqrt(1.0*n);//sqn=sqrt(n)
	For(i,0,sqn){//枚举
		res.push_back(i);
		if(i&&i!=n/i)res.push_back(n/i);
	}
	sort(res.begin(),res.end());//排序
	cout<<res.size()<<endl;
	For(i,0,res.size()-1)printf("%d ",res[i]);
	puts("");
}
```
2019/12/2:上午突然想出了证明方法，过来补一下。

1. $0$肯定是一个正确答案
2. 对于$1\leq x\leq \sqrt{n}$，$\frac{n}{x}$都是一个正确答案，非常显然。
3. 对于$1\leq x\leq \sqrt{n}$，$x$都是一个正确答案。

对于3：我们构造$a=\lfloor\frac{n}{x}\rfloor$，则$a\geq x$

所以$\lfloor\frac{n}{a}\rfloor =x$，那$x$就是一个答案。

---

## 作者：Karry5307 (赞：5)

### 题意

有$T$组数据，每组数据给定一个$n$，让你求对于所有正整数$k$，$\lfloor\frac{n}{k}\rfloor$的取值有多少种，并从小到大输出每一种可能的取值。

$\texttt{Data Range:}1\leq T\leq 10,1\leq n\leq 10^9$

### 题解

FST B,E 了，与 Expert 无缘。

整除分块入门好题，其实也是一道裸题。

所以我下定决心来写一篇新手向的题解，顺便复习复习。

如果你还不知道整除分块的话，可以这样理解

首先我们可以先写出所有$\lfloor\frac{n}{k}\rfloor$，比如$n=12$的时候，有（第$i$个数为$k=i$时的答案）

$12,6,4,3,2,2,1,1,1,1,1,1,0,0,0\cdots$

于是，你会发现我们可以按照$\lfloor\frac{n}{k}\rfloor$的取值对$k$分块，像这样：

$12:1\sim 1,6:2\sim 2,4:3\sim 3,3:4\sim 4,2:5\sim 6,1:7\sim 12,0:k\geq 13$

接着考虑那些取值非零的块的左右端点，首先考虑取值为$x$时的右端点。

假设我们现在已经知道了这个块的左端点，那么就知道这个块的取值为$\lfloor\frac{n}{l}\rfloor$。

**所以说，满足与这个块取值的最大的$r$为$\lfloor\frac{n}{\lfloor\frac{n}{l}\rfloor}\rfloor$。**

然后下一个块的$l$等于这一个块的$r$加上$1$。

取值的种数很明显为块的数量。

因为是从小到大，所以我这里用了递归。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
const ll MAXN=1;
ll test,x,res;
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
} 
inline void dfs2(ll l,ll r,ll x)
{
	if(l>x)
	{
		return;
	}
	dfs2(x/(x/l)+1,x/(x/l),x),res++;
}
inline void dfs(ll l,ll r,ll x)
{
	if(l>x)
	{
		return;
	}
	dfs(x/(x/l)+1,x/(x/l),x);
	printf("%d ",x/l);
}
inline void solve()
{
	x=read(),res=0,dfs2(2,0,x);
	printf("%d\n0 ",res+2),dfs(2,0,x),printf("%d\n",x);
}
int main()
{
	test=read();
	for(register int i=0;i<test;i++)
	{
		solve();
	}
}
```

---

## 作者：woshishei (赞：4)

题目大意：给定一个整数$n$，求集合$\{[\frac{n}{i}]\}(i\in \mathbb{N}_+)$中的所有元素（$[x]$表示不大于$x$的最大整数，下同）。

------------

因为题目给出的$n$的数据范围很大，所以不能从$1$到$n$一个一个枚举。

但是容易发现$[\frac{n}{i}]$等于某一个数值时，$i$可能有多个，并且一定是一段连续的整数。这样我们可以尝试从$[\frac{n}{i}]$中最小的$i$直接跳到最大的$i$。

那么怎么实现呢？其实我们如果知道了$[\frac{n}{i}]$的值，就可以$\Theta(1)$求出$i$的最大值。例如$n=16$，$[\frac{n}{i}]=3$，则$i$的最大值就等于$[\frac{16}{3}]=5$。把这个最大值加一$(5+1=6)$就是满足下一个$[\frac{n}{i}]$（此时等于$2$）的最小值了。

这就是**整除分块**的思想。可以证明使用这种方法的时间复杂度约为$\Theta(\sqrt{n})$。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;
int n,a[100010],cnt,cur;
void solve()
{
	scanf("%d",&n);
	cnt=0;
	cur=1;//cur表示题解中的i
	while(cur<=n)
	{
		a[++cnt]=n/cur;//将n/cur记录到答案中
		cur=n/(n/cur)+1;//更新cur变量，使之变成满足下一个n/cur的最小值
	}
	a[++cnt]=0;//别忘了0也是答案
	printf("%d\n",cnt);
	for(int i=cnt;i>=1;i--)//按照升序输出，所以要逆序
		printf("%d ",a[i]);
	printf("\n");
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
		solve();
	return 0;
}
```

---

