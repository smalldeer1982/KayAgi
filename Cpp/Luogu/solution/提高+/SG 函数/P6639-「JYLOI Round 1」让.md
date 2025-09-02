# 「JYLOI Round 1」让

## 题目描述

Alice 和 Bob 在玩游戏。

现在有多堆石子，其中第 $k$ 堆石子有 $p_k$ 个，先后手轮流操作。取石子时，可以选任意一堆进行操作。若记 $i$ 为在这次取之前这堆石子的个数，$j$ 为这次要取的石子数，$R$ 为给定的常数，则需满足以下条件：

$$1 \leq i + j \leq R,i \geq j \geq 1$$

使对方无法操作者即为胜者。游戏时，双方都采用最优策略。

有多次游戏，具体来说，共有 $T$ 个操作，分为两类：

1. “``change x``” 表示将 $R$ 更改为 $x$。

2. “``query n``” 表示进行一次游戏，接下来有 $n$ 行，这 $n$ 行中的第 $i$ 行有两个正整数 $l_i$ 和 $r_i$，表示这次游戏的石子的堆数和个数可以用这 $n$ 个区间来表示。第 $i$ 个区间表示这次游戏的石子的堆数新增了 $(r_i - l_i + 1)$ 堆，并且其中这个区间所表示的第 $j(1 \leq j \leq r_i - l_i + 1)$ 堆的石子个数为 $(l_i + j - 1)$。

	例如当这次游戏的 $n = 2$，并且两个区间分别为 $[1, 7]$ 和 $[2, 3]$ 的时候，这次游戏一共有 $[(7 - 1 + 1) + (3 - 2 + 1)] = 9$ 堆石子，这 $9$ 堆石子的个数分别为 $1, 2, 3, 4, 5, 6, 7, 2, 3$。

由于 Bob 和 Alice 都非常聪明，而 Bob 希望不赢太多次，在适当的时候让让 Alice。因而他希望你帮他编写一个程序，对于每次游戏，如果先手有必胜策略输出“``1``”，否则输出“``0``”，你能做到吗？

## 说明/提示

### 样例 1 说明

共有 $T=5$ 个操作。

第 1 个操作将 $R$ 改成了 3。

第 2 个操作表示进行了一次游戏，这次游戏的 $n=1$，区间为 $[2, 2]$，表示这次游戏共有 $(2 - 2 + 1) = 1$ 堆石子，这 1 堆石子的个数为 $(2 + 1 - 1) = 2$。因为 $R=3$，因此先手最多只能够取 1 个。若取 2 个则不满足 **题目描述** 中的条件 $1 \leq i + j \leq R$，若取 3 个及以上则不满足 **题目描述** 中的条件 $1 \leq i + j \leq R,i \geq j \geq 1$，其中 $i$、$j$、$R$ 的含义如题所述。先手取完后唯一的一堆只剩下 1 颗石子，因为后手取了 1 颗石子后使先手无法操作，所以先手落败，又因为这是唯一的一种取法，所以先手必败，因此先手无必胜策略，输出“``0``”。

第 3 个操作将 $R$ 改成了 4。

第 4 个操作表示进行了一次游戏，这次游戏的 $n=1$，区间为 $[2, 2]$，表示这次游戏共有 $(2 - 2 + 1) = 1$ 堆石子，这 1 堆石子的个数为 $(2 + 1 - 1) = 2$。先手最多可以取 2 颗石子，因为当先手取 3 颗或以上时，不满足 **题目描述** 中的条件 $1 \leq i + j \leq R,i \geq j \geq 1$，其中 $i$、$j$、$R$ 的含义如题所述。因为当先手选择取 2 颗石子时，先手取完了所有石子，使后手无法操作，所以先手必胜，输出“``1``”。

第 5 个操作将 $R$ 改成了 2。

____________

### 数据范围

对于 $100\%$ 的数据，满足 $1 \leq T \leq 10^5, 2 \leq R \leq 10^{15}, 0 \leq l_i \leq r_i < R, 1 \leq \sum{n} \leq 5 \times 10^5$，并且第一个操作一定是第 1 类操作。

对于测试点 1~2 ，满足 $T \leq 10, l_i \leq r_i \leq 3$，并且在一轮游戏中石子的堆数不会超过 4。

对于测试点 3~6 ，满足 $T \leq 100, R \leq 100, \sum{n} \leq 100$。

对于测试点 7~10 ，满足 $T \leq 10, R \leq 10^5, \sum{n} \leq 50$。

对于测试点 11~12 ，满足 $R \leq 5 \times 10^3, \sum{n} \leq 5 \times 10^5$，并且只有一次修改操作。

对于测试点 13~16 ，满足 $T \leq 10^5,R \leq 10^5,\sum{n} \leq 5 \times 10^5$。

共 20 个测试点，每个测试点 5 分。

## 题目来源

「JYLOI Round 1」 E

Idea / Solution / Data：abcdeffa

## 样例 #1

### 输入

```
5
change 3
query 1
2 2
change 4
query 1
2 2
change 2```

### 输出

```
01```

## 样例 #2

### 输入

```
5
change 11
change 68
query 15
15 16
54 64
49 55
33 38
27 52
20 30
45 46
29 60
58 64
11 55
17 40
15 58
41 63
7 30
15 37
query 14
15 57
13 34
4 13
35 43
12 20
16 62
63 65
17 29
19 67
48 63
25 49
1 8
1 37
44 49
query 14
15 24
6 50
49 60
30 53
33 52
4 44
1 5
44 59
4 40
45 48
1 20
12 27
44 63
21 39```

### 输出

```
001```

# 题解

## 作者：Mophie (赞：3)

初学 SG 函数，按标签搜题搜到这题就做掉了qwq

首先每一堆的石子是相互独立的，那么我们只要求出每堆石子的 SG 函数即可。

打表观察一下 SG 函数的规律就可以发现，大概是 $0-k_i$ 的循环。

那么现在考虑一下 $0$ 每次出现的位置，显然就是恰好走不到上一个 $0$ 的位置。

那么设上一个 $0$ 的位置为 $pos$，石子总数为 $R$。设这个 $0$ 的位置为 $x$

那么可以发现如果跳不到上一个 $0$ 的话要满足条件 $pos<x-(R-x)$ 也就是  $2x>pos+R$

所以下一个 $x$ 的位置就是 $pos+R+1$ 除 $2$ 向上取整。然后就是前缀和处理的问题了。

首先有个比较显然的性质 $2x \bigoplus 2x+1=1$。因为前面位数全部相同就末位不同故异或值是 $1$。

那么 $2x \bigoplus 2x+1 \bigoplus 2x+2 \bigoplus 2x+3=0$，所以以每四个为周期。

然后就是 $2x$ 的前缀和为 $2x$。

$2x+1$ 的前缀和为 $2x \bigoplus 2x+1=1$

$2x+2$ 的前缀和为 $2x \bigoplus 2x+1 \bigoplus 2x+2=1 \bigoplus 2x+2 =2x+3$

$2x+3$ 的前缀和就为 $0$。

然后直接做就好了。

代码如下（貌似还是最优解？）

```cpp
//红太阳zhouakngyang txdy!
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	int sum=0,nega=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')nega=-1;ch=getchar();}
	while(ch<='9'&&ch>='0')sum=sum*10+ch-'0',ch=getchar();
	return sum*nega;
}
inline int val(int x)
{
	if(x%4==1)return 1;
	else if(x%4==2)return x^1;
	else if(x%4==3)return 0;
	else return x;
}
int taxi,p,n,ans,l,r,now=0;
char a[19];
inline int solve(int x,int k)
{
	register int res=0,L=0,R=0,qwq;
	while(L<=x)
	{
		qwq=k/2;R=L+qwq;
		if(R>=x)
		{
			res=res^val(x-L);
			break;
		}
		res=res^val(R-L);
		L=R+1;k=p-L;
	}
	return res;
}

signed main()
{
	taxi=read();
	for(int ttt=1;ttt<=taxi;ttt++)
	{
		cin>>a;
		if(a[0]=='c')p=read();
		else
		{
			ans=0;
			n=read();
			for(int i=1;i<=n;i++)
			{
				l=read(),r=read();
				ans=ans^solve(r,p);ans=ans^solve(l-1,p);
			}
			if(ans)putchar('1');
			else putchar('0');
		}
	}
	return 0;
}


```


---

## 作者：VinstaG173 (赞：3)

```
++【tag=博弈论】;
todolist.push(P6639);
p=todolist.top();//p=P6639
solve(p);
```

感觉这题是这场比赛后三题里面最可做的（

我相信考场上大家是懒得做（毕竟这年头会 SG 定理的人太多了

前置知识：SG 定理

参见[我的博客](https://59388.blog.luogu.org/game-theory-1)。

然后解决这题要用到自然数前缀异或和。

由于异或 $0$ 不影响结果，所以这里说自然数或正整数都一样。

首先我们注意到三个简单的事实：

1. 相邻两个自然数中较小的是偶数时两数异或和为 $1$。

2. 连续四个自然数中最小的是偶数时四个数的异或和为 $0$。

3. 偶数 $x$ 异或 $1$ 得到的结果是 $x+1$。

于是我们就得到结论：从 $0$ 到 $i$ 的自然数的异或和 $f_i$ 的值有如下规律：

$$
f_i=
\begin{cases}
i, & i \bmod{4}=0\\
1, & i \bmod{4}=1\\
i+1,& i \bmod{4}=2\\
0,& i \bmod{4}=3
\end{cases}
$$

接着回到原问题。

我们容易根据题目给出的操作条件打出暴力计算 SG 函数的代码：

```cpp
sg[0]=0;
for(int i=1;i<r;++i)
{
	memset(v,0,sizeof(v));
	for(int j=1;j<=i&&i+j<=r;++j)
	{
		v[sg[i-j]]=1;
	}
	for(t=0;v[t]=1;++t);
	sg[i]=t;
}
```

然后我们会发现其实对于每个 $i<r$，有 $SG_i=\operatorname{mex}\{SG_j | \max(0,2i-r) \le j<i\}$。

那么，我们可以发现 $SG_i$ 由若干个从 $0$ 开始的连续自然数列构成。

接着我们发现对于一个数 $i$，当 $SG_{2i-r}>0$ 且 $SG_{2i-r-2}=0$ 或 $SG_{2i-r-1}=0$ 时，有 $SG_i=0$。

于是若上一个满足 $SG_i=0$ 的 $i=p$，下一个满足条件的 $i=\left\lfloor \dfrac{p+r}{2} \right\rfloor +1$。

于是我们可以对 SG 函数分段，由上式可知段数量是 $O(\log{r})$ 的。然后我们找到比某个数 $x$ 小的最大的满足 $SG_i=0$ 的 $i$，计算一次自然数前缀异或和就可以求出 SG 函数前缀异或和了，再差分一下就能计算区间异或和了。

复杂度 $O(R+N\log{\log{r}})$，其中 $R=\sum \log{r}$，$N=\sum n$。

Code:
```cpp
#include<cstdio>
#define ll long long
int t,n,cnt;
ll x,los[53],len[53],val[53],pos;
inline int lwbd(ll v)//二分找
{
	int l=0,r=cnt,m;
	while(l<r)
	{
		m=(l+r>>1)+1;
		if(los[m]<=v)l=m;
		else r=m-1;
	}
	return l;
}
inline ll cal(ll a)//这里的 cal(a) 返回的值为 f_{a-1}
{
	switch(a&3)
	{
		case 0:
			return 0;
			break;
		case 1:
			return a-1;
			break;
		case 2:
			return 1;
			break;
		case 3:
			return a;
			break;
	}
}
inline ll sol(ll p)
{
	int b=lwbd(p);
	return val[b-1]^cal(p-los[b]+1);
}
char opt[7];
int main()
{
	scanf(" %d",&t);
	while(t--)
	{
		scanf(" %s",opt);
		if(opt[0]=='c')//修改操作时预处理分段
		{
			scanf(" %lld",&x);
			cnt=los[0]=0;
			pos=x/2+1;
			len[cnt]=pos-los[cnt];
			val[cnt]=cal(len[cnt]);
			while(pos<x)
			{
				los[++cnt]=pos;
				pos=(pos+x)/2+1;
				len[cnt]=pos-los[cnt];
				val[cnt]=cal(len[cnt])^val[cnt-1];
			}
		}
		else
		{
			scanf(" %d",&n);
			ll l,r,res=0;
			while(n--)
			{
				scanf(" %lld %lld",&l,&r);
				res^=sol(l-1)^sol(r);
			}
			printf("%d",res?1:0);
		}
	}
	return 0;
}
```

---

