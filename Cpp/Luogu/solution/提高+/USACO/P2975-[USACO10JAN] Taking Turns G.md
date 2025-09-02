# [USACO10JAN] Taking Turns G

## 题目描述

Farmer John has invented a new way of feeding his cows. He lays out N (1 <= N <= 700,000) hay bales conveniently numbered 1..N in a long line in the barn. Hay bale i has weight W\_i (1 <= W\_i <=

2,000,000,000). A sequence of six weights might look something like:

17 5 9 10 3 8

A pair of cows named Bessie and Dessie walks down this line after examining all the haybales to learn their weights. Bessie is the first chooser. They take turns picking haybales to eat as they walk (once a haybale is skipped, they cannot return to it). For instance, if cows Bessie and Dessie go down the line, a possible scenario is:

\* Bessie picks the weight 17 haybale

\* Dessie skips the weight 5 haybale and picks the weight 9 haybale \* Bessie picks the weight 10 haybale

\* Dessie skips the weight 3 haybale and picks the weight 8 haybale

Diagrammatically:

Bessie   |      | 
17 5 9 10 3 8

Dessie       |      | 
This scenario only shows a single skipped bale; either cow can skip as many as she pleases when it's her turn.

Each cow wishes to maximize the total weight of hay she herself consumes (and each knows that the other cow has this goal).

Furthermore, a cow will choose to eat the first bale of hay that maximimizes her total weight consumed.

Given a sequence of hay weights, determine the amount of hay that a pair of cows will eat as they go down the line of hay.

两头奶牛 Bessi 和 Dessie 走过一条路吃草，共 $n(1\le n \le 7\times 10 ^ 5)$ 个格子，第 $i$ 个格子有重量为 $W_i(1 \le W_i \le 2 \times 10 ^{9})$ 的草，两牛轮流走，一旦某头牛走过了一格，那么这格的草再也不可能被任一头奶牛吃，每格的草只能被吃一次，所以两头牛只能往后走。Bessi 先走，每头牛每次都往最终自己能吃到最多草的格子走（若有多个格子则选择第一个能吃到最多草的格子），他们都知道对方也想吃到最多的草，问最后 Bessi 和 Dessie 各吃到的草的重量。

输入格式：

第一行一个正整数 $n(1\leq n\le 7\times 10 ^ 5)$，接下来有 $n$ 行，第 $i+1$ 行为 $W_i(1 \le W_i \le 2 \times 10 ^{9})$。

## 样例 #1

### 输入

```
6 
17 
5 
9 
10 
3 
8 
```

### 输出

```
27 17 
```

# 题解

## 作者：WZWZWZWY (赞：2)

好题！有点像博弈论的 DP。


### 题目描述

两头奶牛 Bessi 和 Dessie 走过一条路吃草，共 $n(1\le n \le 7\times 10 ^ 5)$ 个格子，第 $i$ 个格子有重量为 $W_i(1 \le W_i \le 2 \times 10 ^{9})$ 的草，两牛轮流走，一旦某头牛走过了一格，那么这格的草再也不可能被任一头奶牛吃，每格的草只能被吃一次，所以两头牛只能往后走。Bessi 先走，每头牛每次都往最终自己能吃到最多草的格子走（若有多个格子则选择第一个能吃到最多草的格子），他们都知道对方也想吃到最多的草，问最后 Bessi 和 Dessie 各吃到的草的重量。


---

### 思路

其他题解的状态定义似乎没表述清楚。

用 $f_i$ 表示到了现在这头牛吃（先手），吃 $i$ 及以后的草堆所能获得的最大价值。

用 $g_i$ 表示下头牛吃（后手），吃 $i$ 及以后的草堆所能获得的最大价值。

假设现在该 $A$ 牛吃（先手），$A$ 吃完后，此时 $B$ 成了先手，$A$ 成了后手。$B$ 吃完后 $A$ 又成为先手……一头牛的先后手是交替的。

草堆从 $n$ 循环到 $1$，初始 $f_{n+1}=g_{n+1}=0$。

先手先选（废话），先手肯定选择 $f_{i+1}$ 和 $g_{i+1}+w_i$ 中最大的（即不选或者选择草堆 $i$）。

+ 如果不选 $i$，那么就相当于没操作，$f_i=f_{i+1}$，$g_i=g_{i+1}$。

+ 如果选择 $i$，此时先手和后手互换，$f_i=g_{i+1}+w_i$，$g_i=f_{i+1}$。

最后输出 $f_1$（先手最优）和 $g_1$（后手最优）就行了。

---

## 作者：羚羊WANG (赞：2)

相信大家看到这里的时候，已经理解了题目意思

题目中有$（n<=700,000）$，希望大家不要害怕，应该是一个O(n)的时间复杂度

我们发现，每一个点都是有后面的点转移而来

所以我们可以考虑$dp$

用$f[i]$表示最大收益

用$num[i]$表示$f[i]$用干草的最后编号

大致思路：

```cpp
for(register int i=n-1;i;--i)
		{
			if(a[i]+f[tot[i+1]+1]>=f[i+1])
				{
					f[i]=a[i]+f[tot[i+1]+1];
					tot[i]=i;
				}
			else
				{
					f[i]=f[i+1];
					tot[i]=tot[i+1];
				}
		}
```

最后，总代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int x=0;
	bool f=0;
	char c=getchar();
	while (!isdigit(c))
		  f|=(c=='-'),c=getchar();
	while (isdigit(c))
		  x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
void write(int x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int n;
int f[700010];
int a[700010];
int tot[700010];
signed main(){
	n=read();
	for(register int i=1;i<=n;++i)
		a[i]=read();
	f[n]=a[n];
	tot[n]=n;
	for(register int i=n-1;i;--i)
		{
			if(a[i]+f[tot[i+1]+1]>=f[i+1])
				{
					f[i]=a[i]+f[tot[i+1]+1];
					tot[i]=i;
				}
			else
				{
					f[i]=f[i+1];
					tot[i]=tot[i+1];
				}
		}
	write(f[1]);
	putchar(' ');
	write(f[tot[1]+1]);
	return 0;
}

```


---

## 作者：kexinyu (赞：2)

这题，有点像是最优策略。

既然是同时走到某个点，可以记f[i],g[i]

f[i]表示i点之后包括i点的那一段（i~n）第一只牛所取的最大值。

g[i]表示i点之后包括i点的那一段（i~n）第二只牛所取的最大值。

对于点i，f[i]可以直接从f[i+1]来，也就是i不优，不拿。f[i]=f[i+1]; g[i]=g[i+1];

拿的话，f[i]=g[i+1]+a[i]，g[i]=f[i+1];

最后判断从哪一个开始第一次拿f[]最优，即可。

代码：








```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define imin(a,b) ((a<b)?(a):(b))
#define imax(a,b) ((a>b)?(a):(b))
using namespace std;
typedef long long ll;
const int N=710000;
int n,d[N];
ll f[N],g[N],mx,my;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&d[i]);
    f[n]=d[n]; g[n]=0ll;
    for(int i=n-1;i>=1;i--)
    {
        ll x=g[i+1]+d[i],y=f[i+1];
        if(x>=f[i+1]) f[i]=x,g[i]=y; else f[i]=f[i+1],g[i]=g[i+1];
    }
    mx=0;
    for(int i=1;i<=n;i++)
    if(f[i]>mx)
    {
        mx=f[i];
        my=g[i];
    }
    printf("%lld %lld\n",mx,my);
    return 0;
}

```

---

## 作者：QianRan_GG (赞：1)

## 题目大意

有一条路有 $n$ 格，编号 $1$ 到 $n$ ，每格都有草。  
两只牛（牛一，牛二）从起点开始，轮流（牛一先）走到任意一格并吃掉当前格的草。  
牛只能从编号小的格到编号大的格。  
它们想吃到重量最大的草，且都知道对方也想吃到最多的草。  
问两头牛最终吃到的草的重量。

## 解题思路

我们发现路线其实是定好的。  
牛在每个格吃或不吃只与它后面的格有关。  
因为 $n \le 7 \times 10^5$，所以复杂度 $\mathcal{O(n)}$ 或 $\mathcal{O(\log n)}$

所以我们从后往前遍历。  
设 $n1_i$ 为牛一从 $n$ 到 $i$ 取的最大值，  
$n2_i$ 为牛二从 $n$ 到 $i$ 取的最大值。  
因为是轮流操作，所以把牛一牛二各操作一次设为一次总操作。  
考虑 $i$ 格吃不吃。

若不吃，则两只牛都不变： $n1_i = n1_{i + 1}$，$n2_i = n2_{i + 1}$。

若吃，因为牛一先手，所以牛一吃。  
此时牛二相当于成为了先手，可以走牛一本来要走的格，而牛一接下来走牛二本来要走的路。  
所以 $n1_i = n2_{i + 1} + a_i$，$n2_i = n1_{i + 1}$。

因为 $n1$，$n2$ 从后往前是单调递增的，所以输出 $n1_1$ 和 $n2_1$ 就好了。

这样就能过掉这题了。

## 代码

```cpp
#include <iostream>

using namespace std;

const int N = 7e5 + 5;

int a[N];
long long n1[N], n2[N];

inline int read()
{
	char c = getchar();
	int f = 1, sum = 0;
	while(c < '0' || c > '9')
	{
		if(c == '-') f = (~f) + 1;
		c = getchar();
	}
	while(c >= '0' && c <= '9')
	{
		sum = (sum << 1) + (sum << 3) + (c ^ 48);
		c = getchar();
	}
	return sum * f;
}

int main()
{
	int n; n = read();
	for(int i = 1; i <= n; ++ i)
		a[i] = read();
	n1[n] = a[n], n2[n] = 0ll;
	for(int i = n - 1; i; -- i)
	{
		if(n2[i + 1] + a[i] >= n1[i + 1])
			n1[i] = n2[i + 1] + a[i], n2[i] = n1[i + 1];
		else
			n1[i] = n1[i + 1], n2[i] = n2[i + 1];
	}
	printf("%lld %lld", n1[1], n2[1]);
}
```

---

## 作者：Zory (赞：1)

那个，推广一下个人网站。。


http://zory.cf/2017-12/轮流Taking\_Turns.html

## 来源和评测点

USACO10JAN


[Luogu2975](https://daniu.luogu.org/problemnew/show/2975)

## 题目

**【题目大意】**

两头奶牛Bessi和Dessie走过一条路吃草，共n（n<=700,000）个格子，

第i个格子有重量为Wi（1<=Wi<=2,000,000,000）的草，

两牛轮流走，一旦某头牛走过了一格，那么这格的草再也不可能被任一头奶牛吃，

每格的草只能被吃一次，所以两头牛只能往后走。


Bessi先走，每头牛每次都往最终自己能吃到最多草的格子走

（若有多个格子则选择第一个能吃到最多草的格子），

他们都知道对方也想吃到最多的草，问最后Bessi和Dessie各吃到的草的重量。

**【输入格式】**

第一行一个正整数n（n<=700,000）

接下来有n行，第i+1行是Wi（1<=Wi<=2,000,000,000）

**【输出格式】**

答案
**【输入样例】**

6
17
5
9
10
3
8
**【输出样例】**

27 17

## 分析

类似博弈，倒退DP


f[i]=从i到n最大收益

id[i]=达到f[i]用了的干草堆最后编号

对于干草堆i，存在两种选择：

1)用i，id[i]=i,f[i]=w[i]+f[id[i+1]+1] 即本堆干草+舍弃f[i+1]后最大收益

2)不用i，id[i]=id[i+1],f[i]=f[i+1]


## 代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
ll w[710000],f[710000],id[710000];
int main()
{
    int n;scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&w[i]);
    f[n]=w[n];id[n]=n;f[n+1]=0;
    for(int i=n-1;i>=1;i--)
    {
        if(w[i]+f[id[i+1]+1]>=f[i+1])
        {
            f[i]=w[i]+f[id[i+1]+1];
            id[i]=i;
        }
        else
        {
            f[i]=f[i+1];
            id[i]=id[i+1];
        }
    }
    printf("%lld %lld",f[1],f[id[1]+1]);
}
```

---

## 作者：kuikuidadi (赞：0)

# 思路
设 $f_i$ 表示从 $i$ 开始选先手最大的和是多少 $id_i$ 表示从 $i$ 开始选最优情况下下一个选的位置是什么。那么从后往前推，根据先手是不是选 $a_i$ 分类讨论一下就好了。

注意：对手也有最优策略。

# code

```cpp
#include<bits/stdc++.h>
#define int long long//记得开longlong
using namespace std;
int n,a[1000001],f[1000001],id[10000001];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	f[n]=a[n];
	id[n]=n;
	for(int i=n-1;i>=1;i--){
		f[i]=f[i+1];
		id[i]=id[i+1];
		if(a[i]+f[id[i+1]+1]>=f[i]){
			f[i]=a[i]+f[id[i+1]+1];
			id[i]=i;
		}
	}
	cout<<f[1]<<" "<<f[id[1]+1];
}
```

---

