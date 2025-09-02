# 「EZEC-9」Yet Another Easy Problem

## 题目描述

给定 $n,m$，你需要输出一个长度为 $n$ 的排列，满足该排列进行不超过 $m$ 次操作可以得到的最小的字典序最大。

定义一次操作为交换排列中的两个数。

若有多个符合要求的排列，输出任意一个均可。

## 说明/提示

【样例 $1$ 说明】

使得字典序最小的操作方案为:

$4\ 3\ 1\ 2\to1\ 3\ 4\ 2\to1\ 2\ 4\ 3$。

可以证明无法得到更小的字典序，以及其他初始排列无法得到更大的最小字典序。

【样例 $2$ 说明】

显然可以通过操作得到任何排列，输出任意长度为 $3$ 的排列均可。

【数据规模与约定】

**本题采用捆绑测试**。

- Subtask 1（10 points）：$m=0$。
- Subtask 2（10 points）：$m\ge n-1$。
- Subtask 3（25 points）：$m=1$。
- Subtask 4（25 points）：$T\le100$，$n\le6$。
- Subtask 5（30 points）：无特殊限制。

对于 $100\%$ 的数据，$1\le T\le 10^5$，$1\le n\le10^5$，$0\le m\le n$，$\sum n\le10^5$。

## 样例 #1

### 输入

```
2
4 2
3 3
```

### 输出

```
4 3 1 2
1 2 3
```

# 题解

## 作者：银杉水杉秃杉 (赞：22)

虽说这次月赛比较阴间，但这道题并不是想象的那么难（虽然月赛中这T1花了我半小时QwQ）

我们需要逆向推理一下，对于一个长度为 $n$ 的排列，进行不超过 $m$ 次操作过后的最小字典序最大是什么。

对于每一次操作，肯定是把后面的最小数移到前面去，例如：第一次操作把 $1$ 放到第 $1$ 位，第二次操作把 $2$ 放到第 $2$ 位，以此类推。
最后我们经过 $m$ 次操作后，得到的排列前 $m$ 项必然为 $\{1, 2, 3, \dots, m-1, m\}$，为了使后面的字典序最大，后 $n-m$ 项必然为 $\{n, n-1, n-2, \dots, m+2, m+1\}$。
整体排列（下文称此为最终排列）为 $\{1, 2, 3, \dots, m-1, m, n, n-1, n-2, \dots, m+2, m+1\}$。
（比如：当 $n=5,m=3$ 时，最终的排列为 $\{1,2,3,5,4\}$）

现在，我们要做的就是把这个最终排列还原成 $m$ 次操作前的初始排列。
还原的方式有很多很多种（所以这道题才会是Special Judge），
下面介绍其中两种。

第一种：由于我们会把 $1\sim m$ 移到前 $m$ 项，不如刚开始时把最终的第 $m+1$ 项也就是 $n$ 放到开头，$1\sim m$ 放在第 $2\sim m+1$ 项。
初始排列为 $\{n,1,2,3,\dots,m-1,m,n-1,n-2,\dots,m+2,m+1\}$。
需要注意的是当 $n=m$ 时，排列为 $\{n,1,2,3,\dots,n-2,n-1\}$。

第一种方法的代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int T, n, m;
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        printf("%d ", n);//先输出n
        for (int i = 1; i <= min(m, n - 1); i++)//min的作用是来特判n=m
            printf("%d ", i);//输出1-m
        for (int i = n - 1; i >= m + 1; i--)
            printf("%d ", i);//输出n-1到m+1
        printf("\n");//记得换行
    }
    return 0;
}

```

第二种：这种方法有点小玄学，是我比赛时想到的。
构造好最终排列后，我们要进行 $m$ 次交换将其还原，不如我们就一次一次交换回去。
从第 $m$ 项开始，将其与第 $n$ 项交换（也就是将 $m$ 和 $m+1$ 交换），第 $m-1$ 项与第 $n-1$ 项交换，以此类推，直至第 $1$ 项与第 $n-m+1$ 项交换，共 $m$ 次操作。

个人还是推荐用第一种方法，第二种实在不好想到。

第二种方法的代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int T, n, m;
int a[100010];
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= m; i++)
            a[i] = i;
        for (int i = m + 1; i <= n; i++)//先构造最终排列
            a[n - i + m + 1] = i;
        for (int i = m; i >= 1; i--)//从m项开始一次次交换
            swap(a[i], a[n + i - m]);
        for (int i = 1; i <= n; i++)
            printf("%d ", a[i]);
        printf("\n");//记得换行
    }
    return 0;
}
```

如果你觉得这篇题解还不错，点个赞再走呗OwO

---

## 作者：Eason_AC (赞：6)

## Content
给定 $n,m$，你需要输出一个长度为 $n$ 的排列，满足该排列进行不超过 $m$ 次交换操作可以得到的最小的字典序最大。

**数据范围：$T$ 组数据，$1\leqslant T\leqslant 10^5$，$1\leqslant n\leqslant 10^5$，$\sum n\leqslant 10^5$，$0\leqslant m\leqslant n$。**
## Solution
算是一道比较小清新的构造题，接下来教你如何弄出正确的构造方案。

首先，要如何分配这 $m$ 次交换，使得 $m$ 次交换后的数列字典序最小？经分析不难得知，第 $i$ 次交换的时候就应该把数字 $i$ 和第 $i$ 个位置上的数字进行交换，才能够达到最小字典序的目的。

那么如何构造出数列使得 $m$ 次交换后的数列的最小字典序最大？既然 $m$ 次交换后前面交换完的数已经是字典序最小了，那么就应当使得后面的部分的字典序最大。同时，为了尽可能多地消耗交换次数，不应该将数字 $i(1\leqslant i\leqslant m)$ 放在第 $i$ 个位置上面。

那么构造方案就呼之欲出了：$\{n,1,2,\dots,m,n-1,n-2,\dots,m+1\}$。这样构造既可以保证前 $m$ 个要交换的数字不在自己的数字所表示的位置上面，又可以在 $m$ 次交换之后使得最小字典序最大。因为后面的数不用进行交换，我们就先按照字典序最大给它排列好了，这样交换完以后后面的 $n-m$ 个数字就一定可以保证是字典序最大的（前 $m$ 个数字已经确定是 $1,2,\dots,m$ 了）。

## Code
```cpp
namespace Solution {
    const int N = 1e5 + 7;
    int n, m;

    iv Main() {
        MT {
            read(n, m);
            if(n == m) F(int, i, 1, n) printf("%d%c", i, " \n"[i == n]);
            else {
                printf("%d", n);
                F(int, i, 1, m) printf(" %d", i);
                R(int, i, n - 1, m + 1) printf(" %d", i);
                puts("");
            }
        }
        return;
    }
}
```

---

## 作者：gyh20 (赞：5)

#### $\textrm{Subtask1}$
由于不能操作，直接给出一个 $n\sim 1$ 的排列即可。

#### $\textrm{Subtask2}$
可以发现此时一定能通过 $n-1$ 次交换得到任意排列，故任意排列都可以成为答案。

#### 性质分析

先考虑这个问题，给定一个排列，如何求出其交换不超过 $k$ 次得到的字典序最小的排列？

##### 解法
令排列为 $p$，每次操作找到最小的 $p_k\neq k$ 的最小的 $k$，若不存在，则已经成为字典序最小的排列，否则，将数字 $k$ 换到位置 $k$，可以发现这样一定是最优的。 

也就是说，交换之后可以保证前 $k$ 个数一定是 $1\sim k$，但完全无法保证后面数的顺序，可以尝试构造一个排列使得最后交换只能得到 $1,2,\dots k-1,k,n,n-1,\dots k+2,k+1$。

#### $\textrm{Solution}$

先特判 $m\geq n-1$ 的情况。

令一个排列 $p$ 初始为 $1,2,\dots m-1,m,n,n-1,\dots m+2,m+1$。

从 $m$ 至 $1$ 依次执行交换 $p_i,p_{i+1}$ ，可以发现若要还原排列一定会得到， $1,2,\dots m-1,m,n,n-1,\dots m+2,m+1$。

---

## 作者：wwlw (赞：2)

签到。

对于一个置换，要使得其字典序最小，一定是按升序还原成
$$1,2,3,\dots$$
的形式。那么如果可以操作 $m$ 次，最坏的情况就是
$$1,2,\dots,m,n,n-1,\dots,m+1$$
简单观察可得，最优策略的一次操作实际上就是增加了一个不动点，从而增加一个轨道。所以考虑逆向操作，减少轨道，把前面 $m$ 个不动点合并到大轨道里即可。这样操作 $m$ 次，一定会还原成上述最坏情况。

```cpp
#include<stdio.h>
#include<algorithm>
using namespace std;

inline int read(){
    int x=0,flag=1; char c=getchar();
    while(c<'0'||c>'9'){if(c=='-') flag=0;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-48;c=getchar();}
    return flag? x:-x;
}

const int N=1e5+7;

int T,a[N];
int main(){
    T=read();
    while(T--){
        int n=read(),m=min(n-1,read());
        for(int i=1;i<=m;i++) a[i]=i;
        for(int i=m+1;i<=n;i++) a[i]=n-(i-m)+1;
        for(int i=1;i<=m;i++) swap(a[n],a[i]);
        for(int i=1;i<=n;i++) printf("%d ",a[i]);
        putchar('\n');
    }
}
```

---

## 作者：言琢დ (赞：2)

不需要分开讨论。只是考虑 SPJ 如何写就可以：

SPJ 一定是先把 $1$ 放到 $1$ 位置，再把 $2$ 放到 $2$ 位置……

那么它只能放前 $m$ 个数，剩下的数倒序一定最优。

本质上就是这样摆放：

```cpp
n 1 2 3 4 5 .. n-1
```

然后把后面 $n-(m+1)$ 个数倒着放一遍

```cpp
n 1 2 3 4 5 .. m n-1 .. m+1
```

就可以

AC 代码

```cpp
#include<cstdio>
#include<algorithm>
inline int in();
inline void wr(int);
const int N=(int)1e5+5;
int a[N];
inline void swap(int&,int&);
inline bool cmp(int,int);
int main(int argc,char**argv){
#ifndef ONLINE_JUDGE
    freopen("A.in","r",stdin);
    freopen("A.out","w",stdout);
#endif
    register int T=in();
    while(T--){
        register int n=in(),m=in();
        a[1]=n;
        for(register int i=1;i<n;++i)
            a[i+1]=i;
        //n 1 2 3 4 5 .. n-1
        //n 1 2 3 4 5 .. m m+1 .. n-1
        if(m+2<=n+1)std::stable_sort(a+m+2,a+n+1,cmp);
        for(register int i=1;i<=n;++i)
            wr(a[i]),putchar(' ');
        putchar('\n');
    }
}
inline bool cmp(int x,int y){
    return x>y;
}
inline void swap(int&x,int&y){
    x^=y^=x^=y;
}
inline int in(){
    register char c=getchar();
    register int x=0,f=1;
    for(;c<'0'||c>'9';c=getchar())
        if(c=='-')f=-1;
    for(;c>='0'&&c<='9';c=getchar())
        x=(x<<1)+(x<<3)+(c&15);
    return x*f;
}
inline void wr(int x){
    if(x<0)putchar('-'),x=-x;
    if(x/10)wr(x/10);
    putchar(x%10+'0');
}
```

---

## 作者：MY（一名蒟蒻） (赞：2)

[P7852 「EZEC-9」Yet Another Easy Problem](https://www.luogu.com.cn/problem/P7852)

题目质量还是很高的，我赛时交了 11 发才过这道橙题，我真是太逊了。

分 Subtask 来讲。
## Subtask 1
直接从 $n$ 到 $1$ 输出 $n$ 个数即可。
## Subtask 2
输出任意一个排列，反正他绝对能通过交换把你所输出的排列变成一个从 $1$ 到 $n$ 的排列。
## Subtask 3
是一个提示正解的子任务。

我一开始不想开一个数组，但是这样需要大量的分类讨论。这个子任务通过分类讨论可以通过。

后面的子任务只在数据范围有变化，下面直接讲正解。
## Solution
考虑最终操作完之后的排列。一定长这样：

$1 \dots m,n \dots m+1$

那么我们只要先把这个排列构造出来，再对它进行一定顺序的交换，保证无法通过更少的交换次数达到交换后的状态即可。

如果直接分类讨论的话会非常繁琐。

交换的顺序？构造方式不止一种，这里提供我的思路。从 $1$  到 $m$ 依次扫描，每次交换当前的第 $i$ 个数和第 $n$ 个数。可以证明这样是可以接受的。

注意如果使用的是 `a[i]^=a[j]^=a[i]^=a[j];` 这样的交换方式，那么在 $i=j$ 的时候会出现问题。
## Talk is cheap, show me the code.
因为没啥核心代码，直接粘整个了，建议大家不要观看而是根据思路自己写一遍，代码难度极低。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

int a[100010];

int main()
{
// 	freopen("work.in","r",stdin); freopen("work.out","w",stdout);
	int n,m,t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++) a[i]=i;
		for(int i=m+1,j=n;i<=n;i++,j--) a[i]=j;
		for(int i=1;i<=m;i++)
		{
			swap(a[i],a[n]);
			printf("%d ",a[i]);
		}
		for(int i=m+1;i<=n;i++) printf("%d ",a[i]);
		puts("");
	}
// 	fclose(stdin); fclose(stdout);
	return 0;
}
```

***Thanks for your reading !***

---

## 作者：Kobe_Bryant824 (赞：1)

构造排列，即将每 $m$ 次的第 $m$ 个数还原成初始即可。其实就是把第 $1-m$ 项移到前 $m$ 个位置，第 $m+1$ 个移到第$n$个位置。循环模拟一下移动过程就可以了。
```cpp
#include <bits/stdc++.h>
using namespace std;
int T, n, m;
int main()
{
    cin >> T;
    while (T--)
    {
        cin >> n >> m;
        cout << n << ' ';	//先输出n
        for (int i = 1; i <= min(m, n - 1); i++)//min的作用是来特判n=m
            cout << i << ' ';//输出1-m
        for (int i = n - 1; i >= m + 1; i--)
            printf("%d ", i);	//输出n-1到m+1
        cout << endl;	//换行
    }
    return 0;
}

```


---

## 作者：ycw123 (赞：1)

**关键**：定义一次操作为交换排列中的两个数。

这个交换原则其实就是选择排序。

因为要使字典序最小，那一定是优先把最前面的数变得更小，仔细想一下就能知道，第 $i$ 次操作就是把第 $i$ 位变成 $i$（前提是每次交换只有一个数回到正确的位置上）。

也就是说进行m次操作后，字典序最大的排列为： 

$$1,2,3,\cdots,m-1,m,n,n-1,n-2,\cdots,m+1$$

## 分情况讨论 $m$ :

### $m=0,m \ge n-1$

当 $m=0$ 时，无法操作，此时倒序输出 1 到 $n$ 即可。

当 $m \ge n-1$ 时，显然可以通过操作得到任何排列，输出任意长度为 $n$ 的排列均可，不妨与 $m=0$ 的输出保持同步。

```cpp
if(m==0||m>=n-1){
	for(int i=n;i>=1;--i) printf("%d ",i);
	puts("");
}
```
### $m \le n/2$

最终的排列一定是
$$1,2,3,\cdots,m,n,n-1,n-2,\cdots,2m+1,2m,2m-1,2m-2,\cdots,m+1$$

我们考虑在最终排列的基础上两两配对交换它们，一共找出 $m$ 对，这样每一次操作实际上就是把其中一对再交换回来，我们不妨把 $m,m+1 \hspace{5mm}  m-1,m+2 \hspace{5mm} m-2,m+3 \hspace{2mm}\cdots\hspace{2mm} 1,2m$ 两两配对并交换，这样我们就得到了一种正确答案：

$$2m,2m-1,2m-2,\cdots,m+1,n,n-1,n-2,\cdots,2m+1,1,2,3,\cdots,m$$


```cpp
else if(m<=n/2){
	int j=2*m;
	for(;j>m;--j) printf("%d ",j);
	for(int i=n;i>2*m;--i) printf("%d ",i);
	for(int i=1;i<=j;++i) printf("%d ",i);
	puts("");
}
```

### $n/2<m < n-1$

能否沿用 $m \le n/2$ 时的方法呢？

尝试一下

当 $n=7,m=5$ 时，最终排列长这样：

$$1,2,3,4,5,7,6$$

两两配对并交换，发现没有可以与 3 配对的

$$1,2,3,7,6,4,5$$

要不试着与最后一个换一下？

$$1,2,5,7,6,4,3$$
$$1,3,5,7,6,4,2$$
$$3,2,5,7,6,4,1$$

都换完发现恰好满足要求，多组数据试几次就基本能确定不会出错。

```cpp
else{
	for(int i=1;i<=m;++i) a[i]=i;
	for(int i=m+1;i<=n;++i) a[i]=n+m+1-i;//最终序列
	int j=n;
	for(int i=m;i>=1;--i){
		if(j==m) swap(a[i],a[n]);
		else {
			swap(a[i],a[j]);
			--j;
		}
	}
	for(int i=1;i<=n;++i) printf("%d ",a[i]);
	puts("");
}
```
## 都讨论完了，完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m;
int a[1000010];
int main(){
	cin>>t;
	while(t--){
		scanf("%d %d",&n,&m);
		if(m==0||m>=n-1){
			for(int i=n;i>=1;--i) printf("%d ",i);
			puts("");
		}
		else if(m<=n/2){
			int j=2*m;
			for(;j>m;--j) printf("%d ",j);
			for(int i=n;i>2*m;--i) printf("%d ",i);
			for(int i=1;i<=j;++i) printf("%d ",i);
			puts("");
		}
		else{
			for(int i=1;i<=m;++i) a[i]=i;
			for(int i=m+1;i<=n;++i) a[i]=n+m+1-i;
			int j=n;
			for(int i=m;i>=1;--i){
				if(j==m) swap(a[i],a[n]);
				else {
					swap(a[i],a[j]);
					--j;
				}
			}
			for(int i=1;i<=n;++i) printf("%d ",a[i]);
			puts("");
		}
	}
}
```

---

## 作者：wcarry (赞：1)

## 思路：
构造题。

对于 $m\ge n-1$ 时，随意输出排列即可。

对于 $m<n-1$ 时：

首先一个长度为 $n$ 的字典序最小的排列应该是长这样的：

$1,2,3,4,5,\dots,n$。

一个性质：对于一个长度为 $n$ 的排列，操作 $m$ 次过后，必然能使序列前 $m$ 项最优，即前 $m$ 项为 $1,2,3,\dots,m$。

我们先尝试找出这个最小的字典序最大的排列。

第一步，想要让一个排列在 $m$ 次操作后有最小字典序，一定可以让至少前 $m$ 项最优。

第二步，在所有前 $m$ 项最优的排列中选出一个使其字典序最大的排列作为操作后的排列，显然最终选出的排列应该是：

$1,2,3,\dots,m,n,n-1,n-2,\dots,m+1$。

于是我们再从答案推最初的排列。

简单地构造一下最初排列（即将 $n$ 取出，放在了第一个）。

$n,1,2,3,\dots,m,n-1,n-2,\dots,m+1$。

这样可以刚好花费 $m$ 次操作，使最终能得到的最小的字典序最大。

## 代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

#define inf 0x3f3f3f3f
#define LL long long

typedef pair<int,int> PII;

template<typename T>
inline void read(T &x){
	register char ch=getchar();register bool f=false;x=0;
	while(!isdigit(ch)){if(ch=='-'){f=true;}ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	x=f?-x:x; return ;
}

template<typename T>
inline void write(T x){
	if(x<0){putchar('-');x=-x;}
	if(x>=10){write(x/10);}
	putchar(x%10+'0');
}

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int t; read(t);
	while(t--){
		int n,m; read(n),read(m);
		if(m==n||m==n-1){
			for(register int i=1;i<=n;++i){
				write(i),putchar(' ');
			}puts("");
			continue;
		}
		write(n),putchar(' ');
		for(register int i=1;i<=m;++i)
			write(i),putchar(' ');
		for(register int i=n-1;i>=m+1;--i)
			write(i),putchar(' ');
		puts("");
	}
	return 0;
}
```

---

## 作者：QuAckB33 (赞：0)

蒟蒻没找到什么万能的构造方法，~~因为这是蒟蒻啊qwq。~~

题面挺清晰的吧，话不多说直接分析。

### 分析

首先我们考虑，交换数时的目标是想让字典序最小，也就是说我们会尽可能让排列变为 $1,2,3,\cdots,n$ 。所以在有限步数内会优先将 1 与此时的 $a_1$ 交换，2 与 $a_2$ ，以此类推。

那么接下来可以从后考虑，$m$ 次操作后字典序最大的序列便是

$\underbrace{1,2,3,\cdots,m }_{m}, $ $\underbrace{n,n-1,\cdots,m+1}_{n-m}$。

将它存在 a 数组里，作为目标状态。

那么接下来的任务就是把顺序打乱了。我们需要使前 $m$ 个数都不在它的目标位置上。

于是数列可以被切成两份，左边是未被交换的，右边是已经交换过或无需交换的。而未被交换的可以和已经交换过或无需交换的数进行交换。

将剩余需要交换的数记为 $rest$ , 则初始时 $rest=m$。

- 当 $rest<=n-rest$ 时，可以单纯地将 $a_i$ 与 $a_{i+rest}$ 交换 ( $1 \leqslant i \leqslant rest$ )。代码如下：

```cpp
if(rest<=n-rest)
	f(j,1,rest){
		swap(a[j],a[rest+j]);
	}
```
- 当 $rest>n-rest$ 时，先把能与右边交换的数都交换，即 $a_i$ 与 $a_{i+n-rest}$ 交换 ( $rest-(n-rest)+1\leqslant i \leqslant rest$ )。然后 $rest$ 便可以减去 $n-rest$，直到 $rest<=n-rest$ 为止。代码：

```cpp
while(rest>=n-rest){
	f(j,rest-(n-rest)+1,rest){
		swap(a[j],a[n-rest+j]);
	}
		rest-=(n-rest);
}	
```

接下来就是愉快的输出啦~~ 这部分应该不需要代码吧。

**另外需要一个特判：$m=n$ 时，直接 n 到 1 倒序输出就完事儿了。**



------------


若有不明白可以看下这个栗子：

$n=7$，$m=5$

- 分界线：

![qwq1](https://z3.ax1x.com/2021/09/04/h2T9v6.png)

- $rest>n-rest$ 时的交换

![qwq2](https://z3.ax1x.com/2021/09/04/h2TiDO.png)

- $rest<=n-rest$ 时的交换

![qwq3](https://z3.ax1x.com/2021/09/04/h2TPKK.md.png)

- 最后

![qwq4](https://z3.ax1x.com/2021/09/04/h2Tpgx.png)

最后的最后：如果发现有问题请及时告知！！！Thanks♪(･ω･)ﾉ


---

## 作者：Cocoly1990 (赞：0)

考虑交换的贪心，对于每次交换，假设前 $x$ 个数已经排好，第 $x+1$ 次应该将 $x+1$ 排在第 $x+1$ 位，否则字典序不会最小。

那么交换完 $m$ 次以后，前 $m$ 个数肯定是 $1,2,3,...,m$，那么现在只需要让后 $n-m$ 个数的字典序最大，那么显然应该是 $n,n-1,n-2,...,m+1$.

由之前所说的贪心策略，我们可以搞出一组方案 
$$n,1,2,3,...,m,n-1,n-1,...,m+1$$
显然根据上述的交换策略，交换了 $m$ 次后会使得最小的字典序最大。注意要特判 $n\leq m$ 的情况。

---

## 作者：C_S_L (赞：0)

良心签到题。

分两种情况讨论：

情况一：$m\geqslant n-1$ ，即Subtask 2。

首先，$n$ 一定放在第一位。

因为 $m\geqslant n-1$ ，所以交换 $m$ 次后排列一定为 $1,2,3,\cdots,n$ 。

故$1\sim n-1$可以任意排列。

情况二：$m\leqslant n-2$。

对于此类情况，要使最小字典序最大，那么交换应为这样：

若 $1$ 不为第 $1$ 位，那么将 $1$ 与第 $1$ 位交换。

若 $2$ 不为第 $2$ 位，那么将 $2$ 与第 $2$ 位交换。

以此类推。

因为可以交换 $m$ 次，所以交换的一定是最小的 $m$ 个数，而我们要让做小字典序最大，则应该这样排列：

首先，$n$ 一定放在第一位。

然后，将 $1\sim m$ 从小到大排列。

剩下的 $m+1\sim n-1$ 从大到小排列。

所以这个排列为：

$n,1,2,\cdots,m,n-1,n-2,\cdots,m+1$ 。

完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m;
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d",&n,&m);
		if(m>=n-1) {
			printf("%d ",n);
			for(int i=1; i<=n-1; ++i) {
				printf("%d ",i);
			}
			printf("\n");
		} else {
			printf("%d ",n);
			for(int i=1; i<=m; ++i) {
				printf("%d ",i);
			}
			for(int i=n-1; i>=m+1; --i) {
				printf("%d ",i);
			}
			printf("\n");
		}
	}
	return 0;
}
```

比较正常的签到题。

---

