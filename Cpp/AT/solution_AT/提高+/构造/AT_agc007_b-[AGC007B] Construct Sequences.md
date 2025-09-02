# [AGC007B] Construct Sequences

## 题目描述

# 题意简述
给你一段长度为n的数列$P_1$,$P_2$,,$P_n$.
让你构造两个新的数列a与b,且满足：   
1.    1<$a_i$,$b_i$<10^9                     
2.    $a_1$<$a_2$<…<$a_n$
3.    $b_1$>$b_2$>…>$b_n$
4.    $a_{p_1}$+$b_{p_1}$<$a_{p_2}$+$b_{p_2}$<…<$a_{p_n}$+$b_{p_n}$
求出满足条件的数列a,b；

## 样例 #1

### 输入

```
2
1 2```

### 输出

```
1 4
5 4```

## 样例 #2

### 输入

```
3
3 2 1```

### 输出

```
1 2 3
5 3 1```

## 样例 #3

### 输入

```
3
2 3 1```

### 输出

```
5 10 100
100 10 1```

# 题解

## 作者：ytb2024 (赞：12)

[题目传送门](https://www.luogu.com.cn/problem/AT_agc007_b)

附：[AT原题目](https://atcoder.jp/contests/agc007/tasks/agc007_b)

题意：构造两个长度为 $n$ 的正整数序列 $a$,$b$，$a$ 需要严格升序，$b$ 要严格降序。同时，有一个 $p$ 序列，其中如果 $i<j$，则 $a_{p_i} + b_{p_i} < a_{p_j} + b_{p_j}$。

首先，我们抛开 $a$ 需要严格升序，$b$要严格降序不谈。那么，如何使另一个条件成立呢？

有一个很简单的方法，我们可以将 $a_{p_i}$ 加上 $i-1$ (对 $b$ 进行操作效果相同)。
```cpp
for(int i=1;i<=n;i++)a[p[i]]+=i-1;
```
这里遗留了两个问题：

- $a_i$ 与 $b_i$ 均有可能为 $0$。
- 前两个条件无法成立。

我们考虑对 $a$ 与 $b$ 赋初值，为了使最开始时能让任一 $a_i + b_i$ 相同，且 $a$ 能严格升序，$b$ 能严格降序。我们可以让 $a_i \gets add \times i$,$b_i \gets add \times \left(n-i\right)$，是不是很妙？

但这里还有两个细节

- $add$ 要确保相邻两个 $a$ 数值不同，应大于 $n - 1$，所以 $add = \max\left(n\right) = 2 \times 10^4$。
- $b_n$ 有可能为 $0$，所以再给 $b$ 赋初值时 $+ 1$。

```cpp
int add=2e4;
for(int i=1;i<=n;i++)a[i]=add*i,b[i]=add*(n-i)+1;
```

最后输出 $a$,$b$ 序列就能 AC 啦。

## AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p[20001],a[20001],b[20001],add=2e4;
inline void init()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>p[i];
	for(int i=1;i<=n;i++)a[i]=add*i,b[i]=add*(n-i)+1;
	for(int i=1;i<=n;i++)a[p[i]]+=i-1;
}
inline void solve()
{
	for(int i=1;i<=n;i++)cout<<a[i]<<" ";
	cout<<'\n';
	for(int i=1;i<=n;i++)cout<<b[i]<<" ";
}
int main()
{
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	init(),solve();
	return 0;
}
```
```
```

---

## 作者：ETHANK (赞：5)

构造题。先思考如何让 $a_{p_i}+b_{p_i}$ 为定值，考虑到递增和递减的性质，不难发现 $a_i=i,b_i=n-i$ 即满足要求。

下面让 $a_{p_i}+b_{p_i}$ 递增即可，把 $b_{p_i}$ 加上 $i$ 就行了，但这会破坏我们 $b_i$ 的递增性质。注意到两个数组同时乘以一个大数 $k$ 后仍满足原性质，所以可以设 $a_i=ki,b_i=k(n-i)$ 再把 $b_{p_i}$ 加上 $i$ 即可。只要 $k\ge n$ 即满足要求，且 $a_i,b_i\le 10^9$ 。

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define ll long long
using namespace std;
inline ll read(){
    ll x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
const int N=2e4+5;
int a[N],b[N],n,p;
int main(){
    n=read();
    rep(i,1,n)a[i]=i*N,b[i]=(n-i)*N;
    rep(i,1,n)p=read(),b[p]+=i;
    rep(i,1,n)printf("%d ",a[i]);
    puts("");
    rep(i,1,n)printf("%d ",b[i]);
    return 0;
}
```



---

## 作者：myee (赞：4)

### 前言

我的做法好像和大家都不一样，感觉会更自然一点。

### 思路

看到单调性的构造，考虑差分。

则我们有

$$a_j=\sum_{k\le j}x_k$$

$$b_j=\sum_{k\ge j}y_k$$

$$a_j+b_j=\sum_{k\le j}x_k+\sum_{k\ge j}y_k$$

$$x,y\ge1$$

$$\sum x,\sum y\le10^9$$

我们尝试令

$$a_{p_j}+b_{p_j}=C+j$$

或者，设 $q_{p_k}=p_{q_k}=k$，则

$$a_k+b_k=C+q_k$$

从而

$$x_k-y_{k-1}=(a_k+b_k)-(a_{k-1}+b_{k-1})=q_k-q_{k-1}$$

然后容易构造一组合法的 $x,y$ ：$x_k=y_k=q_k$。

则 $a_j=\sum_{k=1}^jq_k,b_j=\sum_{k=j}^nq_k$，即可。

权值在 $1\sim n(n+1)/2$ 内。

总复杂度 $O(n)$。

### Code

核心代码很短。

```cpp
int Q[20005];
int main()
{
    int n,v=0;scanf("%d",&n);
    for(int i=1,p;i<=n;i++)scanf("%d",&p),Q[p]=i;
    for(int i=1;i<=n;i++)printf("%d%c",v+=Q[i]," \n"[i==n]);
    for(int i=1;i<=n;i++)printf("%d%c",v," \n"[i==n]),v-=Q[i];
    return 0;
}
```


---

## 作者：Jsxts_ (赞：3)

给出一个贪心的思想：最小的位置随便分配一组数，然后后面的位置就把这两个数上下调整，使其满足在自己的序列里递增或递减的要求，同时使得和不变。之后在细微调整满足第四个条件。

考虑到值域是 $10^9$，$n$ 只有 20000， 我们可以给每一个数分配 20001 的空间，让它有充足的上下调整空间，初始值分别设为 $20001x$ 和 $20001(n-x+1)$ 就可以了。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int a[20010],b[20010];
int main() {
	scanf("%d",&n);
	for (int i = 1,x;i <= n;i ++ ) {
		scanf("%d",&x);
		if (i == 1) a[x] = x * 20001, b[x] = (n-x+1) * 20001;//初始值 
		else {
			a[x] = x * 20001 - 1, b[x] = (n-x+1) * 20001 + i;//每一个加进来，就稍微将和提升一点 
		}
	}
	for (int i = 1;i <= n;i ++ ) printf("%d ",a[i]);
	puts("");
	for (int i = 1;i <= n;i ++ ) printf("%d ",b[i]);
	return 0;
}
//1e8+1 1e8 1e8-4 1e8-100
//1e5-3 1e5 1e5+1 1e5+99
```


---

## 作者：yizcdl2357 (赞：2)

# 题意

给定 $n$ 及长为 $n$ 的排列 $p$，构造两个长为 $n$ 的序列 $a,b$：

- 每个元素位于 $[1,10^9]$ 中。
- $a$ 严格单调递增，$b$ 严格单调递减。
- 若 $i<j$ 则 $a_{p_i}+b_{p_i}<a_{p_j}+b_{p_j}$。

$n\le 20000$。

# 思考

注意到 $20000^2<10^9$，因此本题难点为将构造的最大数控在平方量级内。

下设 $x_{p_i}=i$，即 $x$ 是 $p$ 的逆排列。

# 解法 1

若只需满足条件 1 和 3，则令诸 $a_i=1,b_i=x_i$ 即可。

若需满足三个条件，想到在此基础上进行调整 $a,b$ 两数组使诸 $a_i+b_i$ 的大小关系不变。

容易发现 $a_i\leftarrow a_i+ni,b_i\leftarrow b_i+n(n-i)$ 是可行的。

代码不赘述。

# 解法 2

上述做法的最大数的量级是 $n^2+O(n)$，大部分题解止步于此，但其实改进空间很大。

待定数组 $s_{1\sim n-1}$，设 $a_i=1+\sum_{j=1}^{i-1}s_j,b_i=x_i+\sum_{j=i}^{n-i}s_j$。

$a_i$ 递增要求 $s_i\ge1$，$b_i$ 递增要求 $s_i+x_i>x_{i+1}$。

故 $s_i=\max(1,x_{i+1}-x_i-1)$ 满足题意。

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 20000
using namespace std;
int n,p[N+5],x[N+5],s[N+5],a[N+5],b[N+5];
signed main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>p[i];
	for(int i=1;i<=n;i++) x[p[i]]=i;
	for(int i=1;i<n;i++) s[i]=max(1ll,x[i+1]-x[i]+1);
	a[1]=1;for(int i=2;i<=n;i++) a[i]=a[i-1]+s[i-1];
	b[n]=0;for(int i=n-1;i>=1;i--) b[i]=b[i+1]+s[i];
	for(int i=1;i<=n;i++) b[i]+=x[i];
	for(int i=1;i<=n;i++) cout<<a[i]<<' ';cout<<'\n';
	for(int i=1;i<=n;i++) cout<<b[i]<<' ';
	return 0;
}
```

该做法中最大数的量级是多少呢？

容易发现最大数是 $b_1$。以下考量之：

$$
\begin{aligned}
b_1&=O(n)+\sum_{i=1}^{n-1}\max(1,x_{i+1}-x_i+1)\\
&=O(n)+\sum_{i=1}^{n-1}\max(0,x_{i+1}-x_i)\\
&=O(n)+\sum_{i=1}^{n-1}\max(x_i,x_{i+1})-\sum_{i=1}^{n-1} x_i\\
&=O(n)-\dfrac{1}{2}n^2+\sum_{i=1}^{n-1}\max(x_i,x_{i+1})
\end{aligned}
$$

而 $\sum_{i=1}^{n-1}\max(x_i,x_{i+1})\le n+n+(n-1)+(n-1)+\dots+\dfrac{n}{2}=\dfrac{3}{4}n^2+O(n)$。

因此，我们做到了 $\dfrac{1}{4}n^2+O(n)$！

# 还能更好吗？

是否能将 $n^2$ 的系数继续优化呢？

取 $x_{1\sim2k}=\{1,2k,2,2k-1,\dots,k,k+1\}$。则：

由 $(a_2+b_2)-(a_1+b_1)\ge n-1$ 知 $a_2-a_1\ge n-1$；

显然 $a_3-a_2\ge 1$；

由 $(a_4+b_4)-(a_3+b_3)\ge n-3$ 知 $a_4-a_3\ge n-3$；

显然 $a_5-a_4\ge 1$；

……

以上累加，有 $a_n=\dfrac{1}{4}n^2+O(n)$。

综上，$\dfrac{1}{4}$ 是最优常数！

# 后记

这是一名高联爆炸的数竞生回归信竞后做的第一道复健题，个人认为这个寻求最优常数的过程就算放在数竞里也着实优雅而美好。

已经高一的我觉得数竞、信竞、文化课三管齐下实在太累，于是决定在信竞上最后拼一把，明年进了省队就好好准备国赛，进不了省队就只好回归于数竞——或者是文化课了。谁知道呢？

不论如何，明天就是初赛，祝我 RP++。

---

## 作者：zsyzsy_2012 (赞：1)

一道思路比较巧妙的构造题。

思路可能和楼上大佬的方法一样，但是这里给出了蒟蒻的思考过程，希望能够帮到大家。

首先，$P$ 数组是给定的，但不一定覆盖所有的下标，所以想到针对性处理每一个 $P$ 数组的值。

我们考虑预处理部分，我们可以想到：

既然让 $a_i + b_i$ 这种合值满足题目里的大小关系的操作是上述的对 $P$ 数组每个值的针对性处理，那我们的预处理部分只需让所有和值在初期相同并使 $a$ 和 $b$ 数组满足递增 $/$ 递减的题目条件，以及使后面的操作无法影响到他们的递增 $/$ 递减关系。

很容易想到，初期两数组的值如下：


$a_i = N × i 
$

$b_i = N × (n - i + 1) 
$

其中 $N$ 为对于此题的 “无限大”。

针对性处理部分也很简单，即：每次把 $a_{p_i}$ 的值加上 $i$ 。

在这里有一个巧妙的事情，就是前面的 $P$ 值加上的下标一定小于后面 $P$ 值的下标，因为初期相同，加上的少即意味着数小，反之亦然。

在检查了一堆题目的繁琐限制之后，我们就可以愉快的开始写代码了，你会发现你轻松地过了一道蓝题。

最后贴上代码：

```
#include "bits/stdc++.h"
#define N 20010
//N 不仅是 maxn ，还是对于此题的无限大
using namespace std ;
int n , a[N] , b[N] ;
int main() {
	scanf("%d" , &n) ;//预处理
	for(int i = 1 ; i <= n ; i++) {
		a[i] = i * N ; b[i] = (n - i + 1) * N ;
	}
	for(int i = 1 ; i <= n ; i++) {
		int p ; scanf("%d" , &p) ;
		a[p] += i ;//针对处理
	}//输出
	for(int i = 1 ; i <= n ; i++) printf("%d " , a[i]) ;
	puts("") ;
	for(int i = 1 ; i <= n ; i++) printf("%d " , b[i]) ;
	return 0 ;
}
```

完结撒花~~

---

## 作者：OneLeft (赞：0)

## 题意
要求你构造两个长度为 $N$ 的序列 $a$ 和 $b$，满足 $1\le a_i\le 10^9$ 且 $a$ 单调递增，$1\le b_i\le 10^9$ 且 $b$ 单调递减，$a_{p_1}+b_{p_1}<a_{p_2}+a_{p_2}<\cdots<a_{p_n}+b_{p_n}$。

## 思路
先考虑什么时候满足 $a_{p_1}+b_{p_1}<a_{p_2}+a_{p_2}<\cdots<a_{p_n}+b_{p_n}$，若 $b_i=0$，显然有 $a_{p_i}=i-1$ 满足该条件，接下来考虑如何才能满足 $a$ 单调递增，$b$ 单调递减。

考虑给每个 $a_i$ 和 $b_i$ 都增加一个数，设 $a_i$ 增加的为 $x_i$，$b_i$ 增加的为 $y_i$，发现当 $x_1+y_1=x_2+y_2=\cdots=x_n+y_n$ 时，原来的件依然满足，但是 $a$ 有可能不满足单调递增（此处及后文的 $a$ 均为增加以前的 $a$），不过我们发现 $a$ 中最大的数为 $n-1$，所以若 $\forall1\le i<N,x_{i+1}-x_i=n$，就可以避免增加后的 $a$ 出现不单调递增的情况，于是我们令 $x_i=n\times i,y_i=n\times(n-i+1)$ 即可，增加后 $a$ 中最大的数为 $n^2+n-1$，最大为 $4\times 10^8+2\times 10^4-1$，$a$ 中最小的数为 $n$，最小为 $2$，均在 $1$ 和 $10^9$ 之间。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e4+5;
int a[N],ans[2][N];
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)ans[0][i]=i*n,ans[1][i]=(n-i+1)*n;
    for(int i=1;i<=n;i++)ans[0][a[i]]+=i-1;
    for(int i=1;i<=n;i++)cout<<ans[0][i]<<' ';
    cout<<'\n';
    for(int i=1;i<=n;i++)cout<<ans[1][i]<<' ';
    cout<<'\n';
    return 0;
}
```

---

## 作者：ty_mxzhn (赞：0)

注意到 $n$ 不是 $10^5$ 而是 $2\times 10^4$，猜测我们需要一个 $a_i,b_i=O(n^2)$ 的构造。

将 $a_i,b_i$ 表示成 $n$ 进制数。则猜测我们最后构造出的序列 $n$ 进制数的高位相同低位偏序。（这是合情合理的，因为如果高位构造会对 $a_i,b_i$ 的偏序关系产生较大影响）

则考虑 $a_i,b_i$ 的升序降序关系用高位构造，低位根据 $p_i$ 构造。

这里给出一种合法构造：

$$
a_{p_i}=p_in+(i-1),b_i=(n-i)n+1
$$

---

## 作者：summ1t (赞：0)

蛮简单的构造题，甚至我都能切掉。

既然是比较 $a_i+b_i$ 的大小，肯定考虑令 $a_i+b_i$ 都等于一个定值，这样才方便操作。

具体地，可以令 $a_i=(i+1)\times n,b_i=(n-i+2)\times n$，这样所有 $a_i+b_i=(n+3)\times n$。

然后对于某个 $p_j=x$，令 $b_x$ 减去 $n-j+1$，
因为 $j\in[1,n]$，$b$ 中两个数至少差 $n$，所以都减去 $n-j+1$ 后依然满足单调性。

由此，我们构造出了合法的 $a,b$ 数列。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rd read()
#define gc getchar()
#define dg(ch) isdigit(ch)
#define _mul(x) ((x<<3)+(x<<1))
#define int long long
#define FOR(i,j,k) for(int i=j;i<=k;i++)
#define ROF(i,j,k) for(int i=j;i>=k;i--)
int read(){int x=0,f=1;char ch=gc;while(!dg(ch)){if(ch=='-')f=-1;ch=gc;}while(dg(ch)){x=_mul(x)+(ch^48),ch=gc;}return x*f;}
const int N=20010;
int n,p[N],a[N],b[N];
signed main(){
	n=rd;FOR(i,1,n) p[i]=rd;
	FOR(i,1,n) a[i]=(i+1)*n;FOR(i,1,n) b[i]=(n-i+2)*n;
	ROF(i,n,1) b[p[i]]-=(n-i+1);
	FOR(i,1,n) printf("%lld ",a[i]);cout<<'\n';
	FOR(i,1,n) printf("%lld ",b[i]);cout<<'\n';
	return 0;
}
```

---

## 作者：_Kenma_ (赞：0)

# AT_agc007_b 解题报告

## 前言

挺有意思的构造题，就当锻炼思维了。

## 思路分析

首先可以将 $a$ 设为 $1,2,3,\cdots,n-2,n-1,n$，将 $b$ 设为 $n,n-1,n-2,\cdots,3,2,1$。此时 $a_i+b_i$ 都是相等的，并且满足 $a$ 序列单调递增，$b$ 序列单调递减的性质。

然后考虑在这个数列上做一些变换。

注意到如果我们将区间 $[1,i]$ 中 $a$ 序列上的数加 $1$，区间 $[i,n]$ 中 $b$ 序列上的数减 $1$，可以在满足 $a,b$ 单调性的同时，使得 $a_i+b_i$ 比其他数大 $1$。

本质上，上面的操作使得 $a_i+b_i$ 相对增加 $1$，并保证了 $a,b$ 的单调性。

考虑推广到让 $a_i+b_i$ 增加 $k$，操作是同理的。

然后就做完了。

按 $p$ 数组的顺序从小到大操作，每次操作使得 $a_{p_i}+b_{p_i}$ 相对增加 $i$，就保证了 $a_i+b_i$ 的相对大小。

## 代码实现

```cpp

#include<bits/stdc++.h>
using namespace std;
int n,p[20005],a[20005],b[20005];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(register int i=1;i<=n;i++){
		cin>>p[i];
	}
	for(register int i=1;i<=n;i++){
		a[i]=i;
		b[i]=n-i;
	}
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=p[i];j++){
			b[j]+=i;
		}
		for(register int j=p[i];j<=n;j++){
			a[j]+=i;
		}
	}
	for(register int i=1;i<=n;i++){
		cout<<a[i]<<' ';
	}
	cout<<'\n';
	for(int i=1;i<=n;i++){
		cout<<b[i]<<' ';
	}
	return 0;
}

```

## 后记

构造题想要做的好，和出题人对脑电波少不了！

---

## 作者：快斗游鹿 (赞：0)

有趣的构造题。

先不管其他限制。当所有的 $a_i+b_i$ 相同时，显然可以通过对每个 $b_{p_i}$ 加 $i$ 来满足第四条限制。

接下来考虑第二第三条限制。要使 $a_i$ 严格递增，$b_i$ 严格递减，最简单的构造方法就是令 $a_i=i,b_i=n-i+1$。但是这样每个 $b_i$ 之间都只差 $1$，同时增加 $i$ 会导致不满足严格递减限制。怎么办呢？观察到最多给每个 $b_i$ 加 $n$，故只要让每个 $b_i$ 之间的差大于 $n$ 即可，最简单的方法就是把每个 $a_i,b_i$ 都乘上 $n+1$，这样两两之间就差了 $n+1$。

至于 $a_i,b_i\le 10^9$ 的限制，因为 $n$ 小于 $2\times 10^4$，所以最大值肯定不会超过

这题就做完了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e4+5;
int n,p[N],a[N],b[N];
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
signed main(){
	n=read();
	for(int i=1;i<=n;i++)p[i]=read();
	for(int i=1;i<=n;i++)a[i]=i*(n+1),b[i]=(n-i+1)*(n+1);
	for(int i=1;i<=n;i++)b[p[i]]+=i;
	for(int i=1;i<=n;i++)cout<<a[i]<<" ";
	cout<<endl;
	for(int i=1;i<=n;i++)cout<<b[i]<<" ";
}

```


---

## 作者：SJH__qwq (赞：0)

没看题解一眼秒了。感觉最多绿。

题目只要求了 $a_i+b_i$ 的大小关系，但是没有要求具体的差值。所以考虑构造 $a_i+b_i-a_{i-1}-b_{i-1}=1$。

那就很简单了。构造 $a_1=1$，$b_1=10^9$，令 $a_i+b_i=10^9+i$。具体的，$a_i=a_{i-1}+30000$，$b_i=b_{i-1}-29999$ 即可满足条件（$n\le 20000$）。

时间复杂度为 $O(n)$。

---

## 作者：KyleShen1213 (赞：0)

## 引入
这是一道巧妙的很好的构造题，希望大家可以做一下。
## 思路
首先，$P$ 数组是给定的，但不一定覆盖所有的下标，所以想到针对性处理每一个下标为这些数的 $a$ 数组的值。
先设立一个持续上升数列 $a$ 和一个持续下降数列 $b$。
```cpp
for(int i=1;i<=n;i++)
{
	a[i]=i*20005;
	b[i]=(n-i+10)*20005;
}
```
接下来是针对性处理的部分：
```cpp
for(int i=1;i<=n;i++)
{
	int p;
	cin>>p;
	a[p]+=i;//让a[p]加上i 
}
```
处理完之后输出就行了。
## AC code
```cpp
#include<bits/stdc++.h>
using namespace std ;
int n,a[20005],b[20005];//定义 
int main()
{
	cin>>n;//输入 
	for(int i=1;i<=n;i++)
	{
		a[i]=i*20005;//a数列持续上升 
		b[i]=(n-i+10)*20005;//b数列持续下降 
	}
	for(int i=1;i<=n;i++)
	{
		int p;
		cin>>p;
		a[p]+=i;//让a[p]加上i 
	}
	for(int i=1;i<=n;i++)   cout<<a[i]<<" ";//输出a数列 
	cout<<"\n";
	for(int i=1;i<=n;i++)  cout<<b[i]<<" ";//输出b数列 
	return 0;//好习惯 
}
```

---

