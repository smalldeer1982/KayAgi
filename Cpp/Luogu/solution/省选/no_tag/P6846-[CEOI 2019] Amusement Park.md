# [CEOI 2019] Amusement Park

## 题目描述

有一个含 $n$ 个点，$m$ 条边的有向图，图无重边，无自环，两点之间不成环。

现在我们想改变一些边的方向，使得该有向图无环。

您需要求出，每一种改变方向后使得该有向图无环的方案的需改变边的数量之和 $\bmod\ 998244353$ 之后的答案。

## 说明/提示

#### 样例解释
#### 样例 1 解释
有如下两种方案：
- 改变方向。
- 不改变方向。

所以输出 $1+0=1$。
#### 样例 2 解释
共有六种可行的方案：
- $1\to2,2\to3,1\to3$
- $1\to2,3\to2,1\to3$
- $1\to2,3\to2,3\to1$
- $2\to1,2\to3,1\to3$
- $2\to1,2\to3,3\to1$
- $2\to1,3\to2,3\to1$

所以输出 $0+1+2+1+2+3=9$。
#### 数据范围
对于 $100\%$ 的数据，保证 $1\le n\le 18$，$0\le m\le \frac{n\times (n-1)}{2}$，$1\le a_i,b_i\le n$，$a_i\not=b_i$，对于 $i\not=j$，均有 $a_i\not=a_j$ 或者 $b_i\not=b_j$，无序数对 $\{a_i,b_i\}$ 互不相同。

详细子任务限制及分值如下表：

| 子任务编号 | 限制 | 分值 |
| :-: |:-:|:-:|
| 1 | $n\le 3$ | $7$ | 
| 2 | $n\le 6$ | $12$ | 
| 3 | $n\le 10$ | $23$ | 
| 4 | $n\le 15$ | $21$ | 
| 5 | 无特殊限制 | $37$ | 
#### 说明
本题译自 [Central-European Olympiad in Informatics 2019](https://ceoi.sk/) [Day 2](https://ceoi.sk/tasks/) [T1 Amusement Park](https://ceoi.sk/static/statements/amusementpark-ENG.pdf)。

## 样例 #1

### 输入

```
2 1
1 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 3
1 2
2 3
1 3```

### 输出

```
9```

# 题解

## 作者：Shattered_Shade (赞：18)

这篇题解主要补充一下容斥系数的~~比较笨的~~推导。

设 $f_s$ 为集合 $s$ 构成的子图的方案数，转移可以枚举 DAG 的入度为 0 的点，则有转移 $f_S=\sum_{T\subseteq S,T\neq \empty}g_T$，$g_T$ 为 $S$ 组成的 DAG 中入度为 0 的点集恰好为 $T$ 的方案数。

设 $w(S)=[S为独立集]$，则子集反演有

$$g_{T}=\sum_{T\subseteq H,H\subseteq S}(-1)^{|H|-|T|}f_{S/H}w(H)$$
其中 $f_{S/H}w(H)$ 为 DAG 中至少有 H 集合的点入度为 0 的方案数。

代回转移方程有

$$f_S=\sum_{T\subseteq S,T\neq\empty}\sum_{T\subseteq H,H\subseteq S}(-1)^{|H|-|T|}f_{S/H}w(H)$$

变换求和顺序枚举 H 有

$$f_S=\sum_{H\subseteq S,H\neq\empty}f_{S/H}w(H)(-1)^{|H|}\sum_{T\subseteq H,T\neq \empty}(-1)^{|T|}$$

同时有 $\sum_{T\subseteq H,T\neq \empty}(-1)^{|T|}=\sum_{i=1}^{|H|}{|H|\choose i}(-1)^i=-1$，代入即得
$$f_S=\sum_{H\subseteq S,H\neq\empty}f_{S/H}w(H)(-1)^{|H|+1}$$

这样就求出了容斥系数。

---

## 作者：syzf2222 (赞：17)

首先发现，若用 $x$ 次变为了 $\text{DAG}$，那么一定可以用 $m-x$ 次将其变为它的反图。于是题意转化为给无向边定向成 $\text{DAG}$ 的方案数乘以 $\frac{m}{2}$。

考虑设 $f_S$ 为将集合 $S$ 内的边定向使得其成为 $DAG$ 的方案数。考虑转移，枚举一个子集 $T$ 作为 $S$ 中的第一层，显然 $T$ 必定为独立集。然而这样有可能会算重，于是容斥，系数为 $(-1)^{|T|+1}$。

于是我们得到了一个 $O(3^n+2^nm)$ 的算法，问题解决。

```
#include<bits/stdc++.h>
using namespace std;
#define inf 1e9
const int maxn=2e5+10;
const int N=19; 
const int mod=998244353;
const int iv2=(mod+1)/2;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
int n,m,a[N*N],b[N*N];
int op[1<<N],all,f[1<<N],d[1<<N];
int main(){
	n=read(),m=read();
	op[0]=mod-1,all=(1<<n)-1,f[0]=1;
	for(int i=1;i<=all;i++)
		op[i]=mod-op[i&(i-1)];
	for(int i=1;i<=m;i++)
		a[i]=read()-1,b[i]=read()-1;
	for(int i=1;i<=all;i++)
		for(int j=1;j<=m;j++)
			if((i>>a[j]&1)&&(i>>b[j]&1)){d[i]=1;break;}
	for(int i=1;i<=all;i++)
		for(int j=i;j;j=((j-1)&i))
			if(!d[j])f[i]=(f[i]+1ll*f[i^j]*op[j])%mod;
	printf("%d\n",1ll*f[all]*m%mod*iv2%mod);
    return 0;
}

```

深深地感到自己的弱小。

---

## 作者：Froggy (赞：11)

先考虑如何求 DAG 的方案数。

设 $f_S$ 表示集合 $S$ 中的点构成的导出子图为 DAG 的方案数。

考虑一个 $S$ 的子集 $T$ ，钦定 $T$ 中的点在 $S$ 的导出子图上入度为 $1$，那么该情况对 $f_S$ 的贡献就是 $f_{S \setminus T}$。**显然 $T$ 必须是独立集**。

容易发现直接做会算重，所以需要进行容斥，那么：

$$f_S=\sum\limits_{T\subseteq S} (-1)^{|T|-1}[T \text{是独立集}]f_{S\setminus T}$$

暴力转移即可做到 $\mathcal{O}(3^n)$，不知道能不能过。

考虑继续优化。

设 $g_S=\sum\limits_{T\subseteq S} (-1)^{|T|-1}[T \text{是独立集}]$，那么 $f=f*g+1$（这里的乘法定义为子集卷积）。

解出 $f=\frac{1}{1-g}$，套个子集卷积求逆板子即可。

对于原问题，发现对于任意一种 DAG 的方案，假设该方案翻转了 $x$ 条边，那么把所有边再翻转一遍仍然是个 DAG 并且在原图基础上是翻转了 $m-x$ 条边。

所以把 $f_{U}$ 乘上 $\frac{m}{2}$ 就是答案。

时间复杂度：$\mathcal{O}(2^nn^2)$。

---

***code:***

```cpp
#define N 1<<19
const int mod=998244353;
typedef long long ll;
int n,m,G[N],A[20][N],B[20][N];
inline int bits(int x){
	return __builtin_popcount(x);
}
void FMT(int *f,int x,int n){
	for(int i=0;(1<<i)<n;++i)
		for(int j=0;j<n;++j)
			if(j>>i&1)
				f[j]=(f[j]+(x?f[j^(1<<i)]:mod-f[j^(1<<i)]))%mod;
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=m;++i){
		int u=read()-1,v=read()-1;
		G[(1<<u)|(1<<v)]++;
	}
	FMT(G,1,1<<n);
	for(int i=1;i<(1<<n);++i){
		if(!G[i]){
			A[bits(i)][i]=bits(i)&1?1:mod-1;
		}
	}
	for(int i=1;i<=n;++i){
		FMT(A[i],1,1<<n);
	}
	for(int s=0;s<(1<<n);++s){
		for(int i=1;i<=n;++i){
			A[i][s]=mod-A[i][s];
		}
		B[0][s]=A[0][s]=1;
		for(int i=1;i<=n;++i){
			for(int j=1;j<=i;++j){
				B[i][s]=(B[i][s]-1LL*A[j][s]*B[i-j][s]%mod+mod)%mod;
			}
		}
	}
	FMT(B[n],0,1<<n);
	printf("%d\n",1LL*B[n][(1<<n)-1]*m%mod*((mod+1)/2)%mod);
	return 0;
}
```

*[Froggy’s blog](https://www.luogu.com.cn/blog/froggy/)*

#### 呱！



---

## 作者：cmk666 (赞：9)

[题目传送门](/problem/P6846)

有一个显然的结论：把一个 DAG 反向仍然是 DAG。因为把每一条边都反向后，只有环才会变成环，因此 DAG 反向后不会有环。

所以如果我们能花 $x$ 步把原图变成 DAG，那我们就可以花 $m-x$ 步变成另一个 DAG。

所以原题等价于：给无向图定向成 DAG 的方案数 $\times\dfrac m2$ 的值。

发现点数 $n$ 只有 $18$，考虑状压 dp。

我们可以把 DAG 拆成所有入度为 $0$ 的点构成的独立集，和一个更小的 DAG。这样就可以转移了。

但是这样可能会重复计算，套个简单容斥即可。

具体的，设 $f_S$ 表示点集为 $S$ 的导出子图的方案数，那么枚举 $S$ 的子独立集 $P$，则有：
$$f_S=\sum_P(-1)^{\lvert P\rvert}f_{S-P},f_0=1$$
转移是 $O(3^n)$ 的，预处理合法的 $P$ 是 $O(m\times 2^n)$ 的。

常数很小，轻松通过。核心代码如下：
```cpp
int n, m, u[209], v[209], cnt[300009], dp[300009];
bool p[300009];
inline bool f(int x, int y) { return x & ( 1 << ( y - 1 ) ); }
int main()
{
	read(n), read(m), dp[0] = 1;
	For(i, 1, m) read(u[i]), read(v[i]);
	For(i, 0, ( 1 << n ) - 1)
	{
		cnt[i] = ( __builtin_popcount(i) & 1 ) ? 1 : mod - 1;
		For(j, 1, m) if ( f(i, u[j]) && f(i, v[j]) ) { p[i] = true; break; }
	}
	For(i, 1, ( 1 << n ) - 1) for ( int j = i ; j ; j = i & ( j - 1 ) )
		if ( !p[j] ) dp[i] = add(dp[i], mul(cnt[j], dp[i ^ j]));
	return printf("%d\n", mul(dp[( 1 << n ) - 1], m, inv(2))), 0;
}
```

---

## 作者：封禁用户 (赞：8)

## 题意

对于一个有向图，翻转一些边使得其无环，问所有方案的总翻转边数对某个数取模后的结果。

## 分析

由题目，$m\le\dfrac{n(n-1)}{2}$。

对于前两个 $n\le6$ 的子任务，$m\le15$，所以可以枚举每条边是否翻转。

判断一个有向图是否存在环，可以使用[拓扑排序](https://oi-wiki.org/graph/topo/)，若原图为有向无环图 （DAG），则就能 push 进去所有的点，则 $sum=n$。

时间复杂度 $O(n2^m)$。

## Code（19ppt）

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 998244353
#define N 22
#define M 400 
ll ans = 0;
vector<int> g[N];
int x[M],y[M],deg[N],n,m;
int main()
{
	//freopen("park.in","r",stdin);
	//freopen("park.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i = 0;i < m;++i)
	{
		scanf("%d%d",&x[i],&y[i]);	
		g[x[i]].push_back(y[i]);
		g[y[i]].push_back(x[i]);
	}
	for(int t = 0;t < 1<<m;++t)
	{
		int cnt = 0,sum = 0;
		for(int i = 1;i <= n;++i) g[i].clear();
		for(int i = 1;i <= n;++i) deg[i] = 0;
		for(int i = 0;i < m;++i)
		{
			if(t & (1<<i))
			{
				++cnt;	
				g[y[i]].push_back(x[i]);
				++deg[x[i]];
			}	
			else
			{
				g[x[i]].push_back(y[i]);
				++deg[y[i]];
			}
		}
		queue<int> q;
		for(int i = 1;i <= n;++i)
			if(!deg[i])
				q.push(i);
		while(q.size())
		{
			++sum;
			int u = q.front();
			q.pop();
			for(auto v:g[u])
				if(--deg[v] == 0)
					q.push(v);		
		} 
		if(sum == n) ans = (ans + cnt) % mod;
	}
	printf("%lld",ans);
	return 0;
}
```

## 推导结论

先前置一个结论：**对于一个有向无环图 （DAG），翻转所有边后仍是有向无环图 （DAG）**。

简单地证明一下：对于有向图中的一个环，翻转所有边，肯定是一个环，只是方向反了一下。所以一个有向图中的一个环也必然要由一个环翻转过来。

所以原图存在环是反图存在环的充分必要条件。

所以一个有向无环图 （DAG） 翻转后不可能存在环，即还是有向无环图 （DAG）。

有了这个结论，就可以进行优化了。

## 优化

对于一个有向图，如果翻转 $p$ 条边是一个有向无环图 （DAG），那么其反图，翻转 $m-p$ 条边也必然是一个有向无环图 （DAG）。

这两种情况，平均翻转了 $\frac{m}{2}$ 条边。

所以题目就转化成了：翻转一些边，求出成为有向无环图 （DAG） 的方案个数乘上 $\frac{m}{2}$ 对某个数取模的结果。

## 思路

这样就可以进行状态压缩 DP 了。

设 $dp_i$ 为状态 $i$ 成为有向无环图 （DAG） 的方案数量。

枚举 $i$ 的子集 $j$ 进行转移，**显然 $j$ 必定为独立集**（老生常谈了）
。

但是这样有个严重的问题：会算重。

所以我们使用容斥原理，根据集合的大小进行容斥。大小为奇数则加，大小为偶数则减。

![容斥原理](https://imgconvert.csdnimg.cn/aHR0cDovL3d3dy5jcHBibG9nLmNvbS9pbWFnZXMvY3BwYmxvZ19jb20vdmljaS8wMDAucG5n?x-oss-process=image/format,png)

原因比较套路，这里不详细讲容斥原理了，具体可以简单地查看[这个帖子](https://www.luogu.com.cn/discuss/451465)。

最终代码的时间复杂度为 $O(3^n+m2^n)$。

注意在最后答案的计算中使用逆元，不然会输出错误的答案。

## AC code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define maxn 262145
#define M 400
#define N 22
constexpr int mod = 998244353;
bitset<maxn> p;
ll dp[maxn];
int n,m,cnt[maxn],x[M],y[M];
int main()
{
	scanf("%d%d",&n,&m);
	int k = 1<<n;
	for(int i = 1;i <= m;++i) scanf("%d%d",&x[i],&y[i]);
	for(int i = 0;i < k;++i)
	{
		int sum = 0;
		for(int j = i;j;j&=(j-1)) ++sum;
		if(sum & 1) cnt[i] = 1;
		else cnt[i] = -1;
		for(int j = 1;j <= m;++j)
			if(i&(1<<x[j]-1)&&i&(1<<y[j]-1))
			{
				p[i] = 1;
				break;		
			}
	}
	dp[0] = 1ll;
	for(int i = 1;i < k;++i)
		for(int j = i;j;j = i&(j-1))
			if(!p[j])
				dp[i] = (dp[i] + dp[i^j] * cnt[j] + mod) % mod;
	printf("%lld",dp[k-1]*(mod+1)/2%mod*m%mod);
	return 0;
}
```

---

## 作者：Feyn (赞：5)

[link](https://www.luogu.com.cn/problem/P6846) & [博客园食用](https://www.cnblogs.com/dai-se-can-tian/p/16420278.html)

题外话。昨天学了二项式反演，感觉好玄乎的亚子。其实蒟蒻觉得二项式反演就是为了证明小学奥数的那个容斥原理的系数为什么是 $(-1)^{|S|}$ ，目前为止还没看到它的其它用处。既然如此，记个结论就好啦。

说回题目。首先我们需要思考的是最后得到的有向无环图到底应该是什么样子的。正如其它题解所说，假如能用 $i$ 次变化变换出一个合法的图，那么必然可以用 $m-i$ 次变化变换出前者的反图。于是会发现最后的答案会等于变换出合法图的方案数乘上 $\frac{m}{2}$ 。

然后考虑如何求方案数。点数很小考虑状压。用 $f(S)$ 来代表某个点集形成有向无环图的方案数，根据拓扑排序的经验，这个有向无环图肯定会有一些出度为 $0$ 的点，而删去这些点剩下的图也应该是一个有向无环图。所以考虑枚举这些点的点集作为转移的依据。就这样转移的话复杂度是 $O(3^n)$ 的，复杂度证明见[这个帖子](https://www.luogu.com.cn/discuss/451390)，用组合意义或者纯推柿子都可以证。

最后来考虑重复的问题。举个栗子。假如有一张图，$3$ 个点，连边方式是 $3$ 和其它两个点有边。那么会发现枚举 $\{1,2\}$ 集合时和枚举到 $\{1\}$ 集合时会有重复情况，其中之一是 $\{3\leftarrow 1,3\leftarrow 2\}$ 的方案，毕竟这个方案满足两个集合内元素入度为 $0$ ，所以会被重复计算。

既然有重复就想到通过容斥来解决问题。这一部分其它题解有详细阐述，不再多说。

最后提醒一句，这种题目要注意取模。

```cpp
#include<bits/stdc++.h>
//#define zczc
#define int long long
const int mod=998244353;
const int N=18;
const int S=1<<N;
using namespace std;
inline void read(int &wh){
    wh=0;int f=1;char w=getchar();
    while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
    while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
    wh*=f;return;
}

inline int qpow(int s1,int s2){
	if(s2==1)return s1;
	int an=qpow(s1,s2>>1);
	if(s2&1)return an*an%mod*s1%mod;
	else return an*an%mod;
}
int m,n,a[N*N],b[N*N],f[S],cnt[S];
bool c[S];

signed main(){
	
	#ifdef zczc
	freopen("in.txt","r",stdin);
	#endif
	
	read(m);read(n);
	for(int i=1;i<=n;i++){
		read(a[i]);read(b[i]);
		a[i]--,b[i]--;
	}
	for(int i=1;i<(1<<m);i++){
		cnt[i]=cnt[(i>>1)]+(i&1);
		for(int j=1;j<=n;j++){
			if((i&(1<<a[j]))&&(i&(1<<b[j])))c[i]=true;
		}
	}
	f[0]=1;
	for(int i=1;i<(1<<m);i++){
		for(int j=i;j;j=(j-1)&i){
			if(c[j])continue;
			f[i]=(f[i]+f[i-j]*((cnt[j]&1)?1:-1)%mod)%mod;
		}
	}
	printf("%lld",(f[(1<<m)-1]*qpow(2,mod-2)%mod*n%mod+mod)%mod);
	
	return 0;
}
```

---

## 作者：OrinLoong (赞：4)

## LGP6846_1 [CEOI 2019] 游乐园 学习笔记
[Luogu Link](https://www.luogu.com.cn/problem/P6846)

### 前言
图计数的入门题，大概？

### 题意简述
给定一个 $n$ 点 $m$ 边的有向图 $G$。可以任意反转 $G$ 中的边。问所有定向使得图 $G$ 为 DAG 的方案需要反转的边数的和。对 $998244353$ 取模。

$n\le 18$。

### 做法解析
~~如果你足够善于观察题面或题解，你会~~发现对于每一种合法定向方案 $A$ 而言，将其所有边反转得到的另一种方案 $A'$ 也合法，而且 $A$ 和 $A'$ 需要反转的边数加起来刚好等于 $m$（每一条边如果在 $A$ 是正着的，那在 $A'$ 就是反着的；反之亦然）。所以题目就转化为求合法方案数乘上 $\frac{m}{2}$。

合法方案数怎么求？$n\le 18$，这启示我们使用状压 DP。关于 DAG 状压计数一个常见套路（必记！）是：**钦定零度点集，简单容斥去重**。什么意思呢？

我们设 $F_S$ 为 定向点集 $S$ 内的边使得 $S$ 为 DAG 的方案数。我们既然要考虑其转移，就要分析 DAG 的性质：每一个 DAG 肯定都包含一些入度为 $0$ 的点（也就是做拓扑排序时最先入队列的那一批点），这些点必须是一个独立集（即两两没有边相连）。如下图中的 $T$ 就是一个独立集。

![pEYHMDK.png](https://s21.ax1x.com/2025/03/06/pEYHMDK.png)

因为每个方案都有其零度点点集，我们就考虑通过枚举零度点点集 $T$ 来计数。

我们钦定 $T$ 和 $S-T$ 间的所有边都由 $T$ 连向 $S-T$。对于一种合法方案而言，$S-T$ 也得是个 DAG。这样我们就有：$F_S=\sum_{T\subset S}F_{S-T}$。

对吗？不对，会算重。比如下图的这种方案就被算了三次。

![pEYHmg1.md.png](https://s21.ax1x.com/2025/03/06/pEYHmg1.md.png)

解决办法？上容斥。由容斥原理，当点集 $T$ 的大小为奇数时，我们令它贡献为正，否则贡献为负。

然后，这道题就做完了！

### 代码实现
代码内 `dp` 数组即为上文的 $F$。  
`vis[s]` 指点集 `s` 是否为独立集。对其判断可以在 $O(m2^n)$ 的时间复杂度内完成，详见代码。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MaxN=18,MaxA=1<<18;
int N,M,alf,X,Y,Gr[MaxN];
int ppc[MaxA];bool vis[MaxA];
void addudge(int u,int v){
    Gr[u]|=(1<<v),Gr[v]|=(1<<u);
}
mint dp[MaxA];
int main(){
    readi(N),readi(M),alf=(1<<N)-1;
    for(int i=1;i<=alf;i++)ppc[i]=ppc[i/2]+(i&1);
    for(int i=1;i<=M;i++)readi(X),readi(Y),addudge(X-1,Y-1);
    vis[0]=1;
    for(int s=1;s<=alf;s++){
        for(int u=0;u<N;u++){
            if(((1<<u)&s)&&(!(Gr[u]&(s-(1<<u)))))vis[s]|=vis[s-(1<<u)];
        }
    }
    dp[0]=1;
    for(int s=1;s<=alf;s++){
        for(int t=s;t;t=(t-1)&s){
            if(vis[t])dp[s]+=dp[s-t]*(ppc[t]&1?1:-1);
        }
    }
    writi(miti(dp[alf]*M/2));
    return 0;
}
```

### 反思总结
DAG 状压计数套路：**钦定零度点集，简单容斥去重**！！！

---

## 作者：Richard_Whr (赞：4)

为啥都用到了什么 DAG 反向还是 DAG，因此平均每两次花费 $m$ 这个神秘结论啊。

直接做他不好吗？

设 $f_s$ 表示集合 $s$ 中的点构成 DAG 的方案数，$g_s$ 表示 $s$ 中的点的答案。

考虑钦定入度为 $0$ 的集合 $t$，集合反演一下你会发现容斥系数是 $op_t=(-1)^{|t|+1}$。

写出转移方程：

$$f_s=\sum\limits_{t \subseteq s}op_t \times f_t$$

$$g_s=\sum\limits_{t \subseteq s}op_t \times (f_t \times E(s-t,t)+g_t)$$

其中 $E(A,B)$ 表示集合 $A$ 连向集合 $B$ 的边的数量。

这个稍微上点手法就能在 $O(3^n)$ 的复杂度内求出来了。

因此整体复杂度 $O(3^n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=18,mod=998244353;
int In[N],Out[N];
int val[1<<N];
int f[1<<N],g[1<<N];
bool st[1<<N];
int n,m;

signed main()
{
	cin>>n>>m;
	for(int i=1,a,b;i<=m;i++)
	{
		cin>>a>>b;
		a--,b--;
		Out[a]|=(1<<b);
		In[b]|=(1<<a);
	}
	
	for(int s=1;s<(1<<n);s++)
	{
		int cnt=0;
		for(int i=0;i<n;i++)
		{
			if((s>>i)&1) cnt+=(In[i]&s),cnt+=(Out[i]&s);
		}	
		if(cnt) st[s]=false;
		else st[s]=true;
	}	
	
	f[0]=1,g[0]=0;
	for(int s=1;s<(1<<n);s++)
	{
		for(int t=s;t;t=(t-1)&s)
		{
			if(t==s) val[t]=0;
			else
			{
				int j=__builtin_ctz(s^t);
				int s1=s^t^(1<<j);
				val[t]=val[t|(1<<j)]-__builtin_popcount(In[j]&s1)+__builtin_popcount(Out[j]&t);	
			}
			if(!st[t]) continue;
			int op=(__builtin_popcount(t)&1)?1:-1;
			f[s]=(f[s]+op*f[s^t])%mod;
			g[s]=(g[s]+op*(f[s^t]*val[t]%mod+g[s^t]))%mod;
		}
	}
	
	cout<<(g[(1<<n)-1]+mod)%mod<<"\n";
	
	return 0; 
}
```

---

## 作者：伟大的王夫子 (赞：4)

首先，我们将原题转化为求最后形成一个 DAG 的方案数。我们假设我们翻转了 $x$ 条边，那么我们翻转剩下 $m - x$ 条边，相当于是把原 DAG 所有得边方向反一下，显然还是个 DAG。于是答案就是方案数乘上 $\dfrac{m}{2}$。原问题便转化为：给定一个无向图，现在要将其中的每条边定一个方向，要求最终形成的有向图没有环，请问有多少种方案？

对一个有向无环图而言，肯定存在一些节点入度为 0，而我们删除这些点后，剩下的图一定也是个 DAG。只要这些点是独立集（互相之间没有边相连，可以 $O(2 ^ n \times n^2)$ 预处理），那么就一定可以找到一种方式确定与这些点相连的边的方向，并且这种方案有且仅有一种。那我们可以枚举这些入度为 0 的点进行统计。但是，我们可以进行容斥。设这些入度为 0 的点数量为 $cnt$，那么容斥系数为 $(-1)^{cnt - 1}$。就相当于是加上除去这些入度为 0 的点的 DP 值，再乘上这个系数。具体的，我们采用枚举子集的方法，时间复杂度为 $O(3^n + 2^n \times n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
int n, m, dp[1 << 18], a[20], g[1 << 18];
bool in_s[1 << 18];
int main() {
	cin >> n >> m;
	for (int i = 1, x, y; i <= m; ++i) {
		scanf("%d%d", &x, &y);
		--x, --y;
		a[x] |= 1 << y;
		a[y] |= 1 << x;
	}
	for (int s = 0; s < (1 << n); ++s)  {
		in_s[s] = 1;
		g[s] = __builtin_popcount(s) & 1 ? 1 : -1;
		for (int i = 0; i < n; ++i)
			for (int j = i + 1; j < n; ++j)
				if ((s >> i & 1) && (s >> j & 1) && (a[i] >> j & 1)) {
					in_s[s] = 0;
					break;
				}
	}
	dp[0] = 1;
	for (int s = 1; s < (1 << n); ++s)
		for (int i = s; i; i = (i - 1) & s)
			if (in_s[i]) {
				dp[s] += g[i] * dp[s ^ i];
				if (dp[s] < 0) dp[s] += mod;
				dp[s] %= mod;
			}
	cout << 1ll * dp[(1 << n) - 1] * (mod + 1 >> 1) % mod * m % mod << endl;
}
```

---

## 作者：Genius_Star (赞：3)

[**或许更好的阅读体验。**](https://www.cnblogs.com/rgw2010/p/18746782)

### 思路：

DAG 计数这个知识点以前学过一点，但是没认真，忘干净了，然后省选就炸完了，于是现在回来补。

注意到，若能进行 $x$ 次操作使得原图是一个 DAG，则这个图的反图（即将所有边反向后的图）肯定也是一个 DAG，需要翻转 $m - x$ 次。

故我们只需要求将边定向后使得原图是一个 DAG 的方案数乘上一个 $\frac{m}{2}$。

注意到范围很小，考虑状压，定义 $f_{S}$ 表示若使得 $S$ 这个点集的导出子图成为 DAG 的方案数。

我们注意到，考虑 topo 排序的过程，那么可以把一个 DAG 拆成一些入度为 $0$ 的独立集（如果不是独立集那么不可能入度为 $0$）和一个更小的 DAG。

故转移的时候我们可以枚举点集 $S$ 的子集 $T$，使得 $T$ 是一个独立集，然后用 $dp_{S - T}$ 去转移；看起来很对，然后这样可能会算重。

因为若一个 DAG 有 $cnt$ 个入度为 $0$ 的点，那么会算重 $2^{cnt} - 1$ 次，于是考虑容斥，容斥系数为 $(-1)^{|T| + 1}$，因为此时 $\sum\limits_{i = 1}^{cnt} \binom{cnt}{i}(-1)^{i + 1} = 1$。

定义 $f_T$ 表示 $T$ 是否是独立集，故有转移：

$$dp_S = \sum_{T \subset S} (-1)^{|T| + 1} f_T dp_{S - T}$$

时间复杂度为 $O(3^n + 2^nm)$。

[**link**](https://www.luogu.com.cn/record/205654431)

注意到可以 FWT 子集卷积优化至 $O(n^22^n)$。

[**link**](https://www.luogu.com.cn/record/205656481)

但是怎么比 $3^n$ 要慢很多。。。

### 枚举子集：

```cpp
int n, m, inv2 = (mod + 1) >> 1;
int u[M], v[M], cnt[M], dp[M];
bool f[M];
int main(){
	n = read(), m = read();
	for(int i = 1; i <= m; ++i)
	  u[i] = read() - 1, v[i] = read() - 1;
	for(int i = 0; i < (1 << n); ++i){
		f[i] = 1;
		for(int j = 0; j < n; ++j)
		  cnt[i] += (i >> j) & 1; 
		for(int j = 1; j <= m; ++j){
		    if(((i >> u[j]) & 1) && ((i >> v[j]) & 1)){
		        f[i] = 0;
		        break;		    	
			}			
		}
	}
	dp[0] = 1;
	for(int S = 1; S < (1 << n); ++S){
		for(int T = S; T; T = (T - 1) & S){
			if(!f[T])
			  continue;
			if(cnt[T] & 1)
			  dp[S] = (dp[S] + dp[S ^ T]) % mod;
			else
			  dp[S] = (dp[S] - dp[S ^ T] + mod) % mod;
		}
	}
	write(1ll * m * dp[(1 << n) - 1] % mod * inv2 % mod);
	return 0;
}
```

### 子集卷积：

```cpp
int n, m, inv2 = (mod + 1) >> 1;
int u[M], v[M], f[N][M], g[N][M];
namespace FWT{
	inline void FWT_or(int *A, int n){
		for(int i = 1; i < n; i <<= 1)
		  for(int j = 0; j < n; j += (i << 1))
		    for(int k = 0; k < i; ++k)
		      A[i + j + k] = (A[i + j + k] + A[j + k]) % mod;
	}
	inline void IFWT_or(int *A, int n){
		for(int i = 1; i < n; i <<= 1)
		  for(int j = 0; j < n; j += (i << 1))
		    for(int k = 0; k < i; ++k)
		      A[i + j + k] = (A[i + j + k] + mod - A[j + k]) % mod;
	}
};
int main(){
	n = read(), m = read();
	for(int i = 1; i <= m; ++i)
	  u[i] = read() - 1, v[i] = read() - 1;
	for(int i = 0; i < (1 << n); ++i){
		int cnt = 0;
		bool F = 1;
		for(int j = 0; j < n; ++j)
		  cnt += (i >> j) & 1; 
		for(int j = 1; j <= m; ++j){
		    if(((i >> u[j]) & 1) && ((i >> v[j]) & 1)){
		        F = 0;
		        break;		    	
			}			
		}
		if(!F)
		  continue;
		if(cnt & 1)
		  g[cnt][i] = 1;
		else
		  g[cnt][i] = (mod - 1) % mod;
	}
	for(int i = 0; i <= n; ++i)
	  FWT::FWT_or(g[i], 1 << n);
	f[0][0] = 1;
	FWT::FWT_or(f[0], 1 << n);
	for(int i = 1; i <= n; ++i){
	    for(int j = 0; j < i; ++j)
		  for(int k = 0; k < (1 << n); ++k)
		    f[i][k] = (f[i][k] + 1ll * f[j][k] * g[i - j][k] % mod) % mod;
		FWT::IFWT_or(f[i], 1 << n);
		for(int j = 0; j < (1 << n); ++j)
		  f[i][j] = (popcnt(j) == i ? f[i][j]: 0);
		if(i != n)
		  FWT::FWT_or(f[i], 1 << n);
	}
	write(1ll * m * f[n][(1 << n) - 1] % mod * inv2 % mod);
	return 0;
}
```

---

## 作者：Caiest_Oier (赞：3)

# [P6846](https://www.luogu.com.cn/problem/P6846)    

首先，对于一个 DAG，将所有边反转能得到另一个 DAG，所以可以将 DAG 之间建立对应关系，最终答案就是 DAG 数 $\times \frac{m}{2}$。          

对于求 DAG 数，考虑 DP，令 $dp_S$ 表示将 $S$ 的导出子图定为 DAG 的方案数。考虑枚举按拓扑序，最外面一层的集合，则 $dp_S=\sum_{T\subseteq S}check(T)dp_{S-T}$，$check(T)$ 表示 $T$ 是否为独立集。    

发现这样会算重，原因在于我们没有钦定在剩下的 $S-T$ 中不能再剥离出与 $T$ 没有连边的独立集作为同一层的点。于是为其加上一个容斥系数。考虑将其拓扑序第一层的点全部去掉后，点集为 $X$，则对于每个 $dp_X$，都只应贡献一次。其贡献的计算式为 $\sum_{T\subseteq (S-X)}check(T)\times v_{|T|}=1$，当 $check(S-X)=0$ 的时候，按原来的算法就是对的，贡献为 0，否则 $check(T)$ 必定等于 1，于是贡献可以变为 $\sum_{T\subseteq (S-X)}\times v_{|T|}=\sum_{i=1}^{|S-X|}{C^{i}_{|S-X|}v_i}=1$，令 $v_i=(-1)^{i+1}$ 即可。      

于是最后的式子就是： 

$$dp_S=\sum_{T\subseteq S}check(T)dp_{S-T}(-1)^{|T|+1}$$     

用子集卷积可以做到 $O(2^n\times n^2)$，不过 $O(3^n)$ 也可以过。

代码：    

```cpp
#include<bits/stdc++.h>
#define int long long
#define MOD 998244353
using namespace std;
int n,m,G[23],dp[(1<<19)],f[(1<<19)],lg[1000003],cnt[1000003],k1,k2,k3,k4,k5,k6,k7,k8,k9;
int lowbit(int X){return (X&(-X));}
signed main(){
    ios::sync_with_stdio(false);
    for(int i=1;i<=1000000;i++)cnt[i]=cnt[i-lowbit(i)]+1;
    for(int i=2;i<=1000000;i++)lg[i]=lg[i>>1]+1;
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>k1>>k2;
        G[k1]|=(1<<(k2-1));
        G[k2]|=(1<<(k1-1));
    }
    f[0]=1;
    for(int i=1;i<(1<<n);i++){
        f[i]=f[i-lowbit(i)];
        if((G[lg[lowbit(i)]+1]&(i-lowbit(i)))!=0)f[i]=0;
    }
    dp[0]=1;
    for(int i=1;i<(1<<n);i++){
        for(int j=i;j;j=((j-1)&i)){
            if(f[j]==0)continue;
            if(cnt[j]%2==1)dp[i]=(dp[i]+dp[i-j])%MOD;
            else dp[i]=(dp[i]-dp[i-j])%MOD;
        }
    }
    k1=(dp[(1<<n)-1]*m%MOD)*((MOD+1)/2)%MOD;
    k1+=MOD;
    k1%=MOD;
    cout<<k1;
    return 0;
}
```

---

## 作者：_Ch1F4N_ (赞：3)

任意合法定向方案，反转所有边后一定也合法，而且两种方案的贡献和是 $m$，因此答案就是定向方案数量乘上 $\frac{m}{2}$。

不妨 $dp_{S}$ 表示将 $S$ 中的点构成的导出子图定向为 DAG 的方案，考虑每次将 DAG 中所有零度点剥去以递归到子状态，但是你发现钦定剩下的点度数大于 $0$ 不太现实，考虑一个非常牛的容斥，枚举零度点的一个非空子集 $T$ 然后 $dp_{S} \gets dp_{S} + dp_{S - T} \times (-1)^{|T|+1}$，你发现对于所有的 DAG 其零度点的每个子集都对这个 DAG 产生了一次贡献，又因为带了容斥系数所以每个 DAG 刚好就被算了一遍，对于 $T$ 的限制是将给定的有向边视作无向边后其为一个独立集，可以在 $O(n \times 2^n)$ 的时间复杂度内预处理，而 dp 的复杂度是 $O(3^n)$ 的，因此总复杂度就是 $O(n \times 2^n + 3^n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;
const int maxv = (1<<18);
int dp[maxv],pop[maxv];
int n,m;
int E[maxv];
int vis[maxv];
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
signed main(){
	cin>>n>>m;
	for(int i=1;i<(1<<n);i++) pop[i]=pop[i/2]+(i&1);
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		E[u-1]|=((1<<(v-1)));
		E[v-1]|=((1<<(u-1)));
	}
	vis[0]=1;
	for(int i=1;i<(1<<n);i++){
		for(int j=0;j<n;j++){
			if((1<<j)&i){
				if((E[j]&(i-(1<<j)))==0) vis[i]|=vis[i-(1<<j)];
			}
		}
	}
	dp[0]=1;
	for(int i=1;i<(1<<n);i++){
		for(int j=i;j;j=(j-1)&i){
			if(vis[j]==1) dp[i]=(dp[i]+dp[i-j]*(pop[j]%2==0?mod-1:1)%mod)%mod;
		}
	}
	cout<<dp[(1<<n)-1]*m%mod*((mod+1)/2)%mod<<'\n';
	return 0;
}
```

---

## 作者：AC_love (赞：2)

考虑一个 DAG 在边全部反转之后仍然会是 DAG，那么如果有一种反转 $x$ 条边的方案，就一定有一种与之对应的反转另外 $m - x$ 条边的方案。所以我们只需要求出总方案数，然后乘上 $\dfrac{m}{2}$ 即可。

那么怎么求总方案数呢？

考虑状压 DP，设 $f(S)$ 表示 $S$ 点集的导出子图反转之后变成 DAG 的方案数。

我们知道 DAG 里一定有一些入度为 $0$ 的点，删除这些入度为 $0$ 的点后，我们会得到一个小的 DAG。考虑枚举这些入度为 $0$ 的点，然后可以从小 DAG 转移。

枚举 $S$ 的子集 $T$，将 $S$ 拆成 $T$ 和 $S - T$，当 $T$ 是一个独立集的时候，$f(S)$ 可以从 $f(S - T)$ 转移而来。

但问题是这样做会算重复。比如我们枚举的一个合法的 $T$ 是 $0011$，那么 $0010$ 和 $0001$ 一定也是合法的，这样同一种方案就被记重了。

考虑一个老生常谈的容斥，当 $T$ 中点的个数是奇数个时，令它有 $1$ 的贡献，当点的个数是偶数个时，令它有 $-1$ 的贡献。

于是做完了，最终复杂度 $O(3^n + n^22^n)$。

---

## 作者：Phartial (赞：2)

首先注意到，对于一种改变 $x$ 条边的 DAG 定向方案，将其中所有边反向，就能一一对应到另一种改变 $m-x$ 条边的 DAG 定向方案。于是我们只需要计数有多少种定向方案能得到一个 DAG，并将其乘上 $\frac{m}{2}$ 即可。

设 $f(S)$ 为有多少种定向方案使得点导出子图 $S$ 为一个 DAG。转移考虑枚举所有入度为 $0$ 的点，但是入度为 $0$ 的点集恰好为 $T$ 不好算，尝试容斥。设 $g(S,T)$ 为有多少种定向方案使得点导出子图 $S$ 为一张入度为 $0$ 的点**恰好**是 $T$ 的 DAG。那么有 $\displaystyle f(S)=\sum_{T\subseteq S,T\ne\varnothing} g(S,T)$。同时设 $h(S,T)$ 为有多少种定向方案使得点导出子图 $S$ 为一张入度为 $0$ 的点**至少**是 $T$ 的 DAG，有 $h(S,T)=w(T)f(S\setminus T)$（其中 $w(T)=[T\text{ 是独立集}]$），同时有 $\displaystyle h(S,T)=\sum_{G\supseteq T} g(S,G)$，对其做子集反演可知 $\displaystyle g(S,T)=\sum_{G\supseteq T} h(S,G)(-1)^{|G|-|T|}$。

于是有：

$$
\begin{aligned}
  f(S)
  &=\sum_{T\subseteq S,T\ne\varnothing} g(S,T)\\
  &=\sum_{T\subseteq S,T\ne\varnothing}\sum_{G\supseteq T} h(S,G)(-1)^{|G|-|T|}\\
  &=\sum_{G\subseteq S,G\ne\varnothing} h(S,G)\sum_{T\subseteq G,T\ne\varnothing}(-1)^{|G|-|T|}\\
  &=\sum_{G\subseteq S,G\ne\varnothing} h(S,G)(0-(-1)^{|G|})\\
  &=-\sum_{G\subseteq S,G\ne\varnothing} w(G)f(S\setminus G)(-1)^{|G|}\\
\end{aligned}
$$

直接做就是 $\Theta(3^n)$ 的，能不能再给力一点啊？

设 $t(S)=-w(S)(-1)^{|S|}$，那么有 $f=f\times t+1$，这里的 $\times$ 是子集卷积，于是有 $f=\frac{1}{1-t}$，用集合幂级数求逆即可做到 $\Theta(2^n n^2)$。

下面的代码是 $\Theta(3^n)$ 的。

```cpp
#include <iostream>

using namespace std;

const int kN = 18, kM = 998244353;

int n, m, f[1 << kN];
bool e[kN][kN], w[1 << kN];

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  for (int i = 1, x, y; i <= m; ++i) {
    cin >> x >> y, --x, --y;
    e[x][y] = e[y][x] = 1;
  }
  for (int i = 0; i < (1 << n); ++i) {
    w[i] = 1;
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < n; ++k) {
        w[i] &= !(i >> j & 1) || !(i >> k & 1) || !e[j][k];
      }
    }
  }
  f[0] = 1;
  for (int i = 1; i < (1 << n); ++i) {
    for (int j = i; j; j = j - 1 & i) {
      f[i] = (f[i] + w[j] * f[i ^ j] * (__builtin_parity(j) ? 1 : -1)) % kM;
    }
  }
  cout << 1LL * (f[(1 << n) - 1] + kM) * m % kM * ((kM + 1) / 2) % kM;
  return 0;
}
```

---

## 作者：Genius_Star (赞：2)

### 定义：

- 独立集：由两两互不相邻的顶点构成的集合。

- 导出子图：选择原图中若干个顶点，以及所有两端点都在这些顶点集中的边组成的子图。

### 思路：

首先有一个性质：

- 若图 $G$ 是一个有向无环图（DAG），则其的反图也是一个有向无环图（DAG）。

-----
**证明：**

若原图中有环 $a \to b \to c \to a$，进行翻转后只是变为了 $a \to c \to b \to a$。

则只有环才可以翻转成环，那么一个有向无环图（DAG）翻转后不会有环。

----

考虑到，若我们翻转了 $a$ 条边使得原图为有向无环图（DAG），利用上面的性质，将原图翻转另外的 $m-a$ 条边也会使得原图为有向无环图（DAG）。

所以在所有方案中，总能找到一种方案的反方案，两者总共翻转了 $m$ 条边，设翻转某些边使得成为有向无环图（DAG）的方案数为 $ans$，则我们要求 $ans \times \frac{m}{2}$。

因为 $n \le 18$，考虑状态压缩 DP。

令 $dp_S$ 表示点集为 $S$ 时其可翻转导出子图为有向无环图（DAG）的方案数。

因为当一个有向无环图（DAG）中添加一些全部出度为 $0$ 的点或全部入度为 $0$ 的点，原图还是一个有向无环图（DAG）。

那么考虑枚举 $S$ 的子集 $T$，且 $T$ 是一个独立集，因为 $T$ 中的点并不相邻，所以对于 $S-T$ 状态的导出子图添加上 $T$ 这些点并不会构成环。

令 $f(S)$ 表示状态 $S$ 的点集是否是独立集，则状态转移方程为：

$$dp_S = \sum_{T \subseteqq S} f(T) dp_{S-T}$$

容易发现，这个会算重，考虑使用容斥定理，因为是求并集，即容斥系数 $g(i)$ 要满足：

$$\sum_{i=1}^n C_n^i g(i) = 1$$

易得 $g(i)=(-1)^{i+1}$，则状态转移方程为：

$$dp_S = \sum_{T \subseteqq S} (-1)^{|T|+1}f(T) dp_{S-T}$$

时间复杂度为 $O(N \times 3^N + 2^n \times m)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=19,mod=998244353;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
int n,m,ans;
int a[N*N],b[N*N];
int dp[1ll<<N],sum[1ll<<N];
bool f[1ll<<N];
int qpow(int a,int b){
	int ans=1;
	while(b){
		if(b&1ll)
		  ans=(1ll*ans*a)%mod;
		a=(1ll*a*a)%mod;
		b>>=1ll;
	}
	return ans;
}
int main(){
	dp[0]=1;
	n=read(),m=read();
	for(int i=1;i<=m;i++)
	  a[i]=read(),b[i]=read();
	for(int i=0;i<(1ll<<n);i++){
		for(int j=1;j<=n;j++)
		  if((i>>(j-1))&1ll)
		    sum[i]++;
		if(sum[i]&1ll)
		  sum[i]=1;
		else
		  sum[i]=mod-1;
		for(int j=1;j<=m;j++){
			if(((i>>(a[j]-1))&1ll)&&((i>>(b[j]-1))&1ll)){
				f[i]=1;
				break;
			}
		}
	}
	for(int i=1;i<(1ll<<n);i++)
	  for(int j=i;j;j=i&(j-1))
	    if(!f[j])
	      dp[i]=(dp[i]+1ll*dp[i^j]*sum[j]%mod+mod)%mod;
	ans=1ll*dp[(1ll<<n)-1]*qpow(2ll,mod-2)%mod*m%mod;
	write(ans);
	return 0;
}
```

---

## 作者：Eric998 (赞：1)

典题喵。

注意到每个反转 $x$ 个边的方案都唯一对应一个反转 $m-x$ 个边的方案。因此全部方案的平均反转数是 $\frac m2$。

套路的对于点集 $S$ 钦定零入度子集 $T$。$T$ 内两两不能有边，转移为 $\displaystyle dp_s=-\sum_{|T|>0,T\in S}(-1)^{|T|}dp_{s/t}$。

---

## 作者：Missa (赞：1)

发现好像没有题解把容斥系数说的很清楚，尝试稍微写一下自己弄懂的。

注意到，把一个 DAG 完全反向，得到的还是 DAG。因此求定向成 DAG 的方案数即可。

考虑怎么生成一个 DAG，发现可以逐步剥一层点。但是这样会算重。不妨假设每次剥掉所有没有出度的点，设没有出度的点的全集为 $S$，考虑枚举 $S$ 的子集 $T$ 进行容斥。

设当前考虑的全集为 $S$，对于 $S$ 的所有子集 $T$，设 $f_{S, T}$ 表示定向使得集合 $S$ 中所有无出度的点恰好为集合 $T$ 的方案数，$T$ 不合法时为 $0$，$g_{S, T}$ 表示定向使得集合 $S$ 中所有无出度的点被钦定为集合 $T$，$f(S) = \sum_{T \in S} f_{S, T}$，含义即为定向 $S$ 为 DAG 的方案数，那么有

$$
g_{S, T} = coef(S, T) f(S / T) = coef(S, T) \sum_{T \in T' \in S} f_{S, T'} 
$$

这里钦定的含义是，所有包含 $T$ 的集合，均会让 $T$ 产生贡献。具体产生几次贡献呢，因为已经确定 $T'$ 为极大无出度点集合，$T$ 为 $T'$ 的子集，因此，确定过 $T'$ 和 $T$ 之后，每个 $f_{S, T'}$ 对应了唯一一个 $f(S/T)$，即有 $coef(S, T)$ 在 $T$ 合法时恒为 $1$，否则为 $0$，这里的合法为。这符合子集反演的形式，可以得到

$$
f_{S, T} = \sum_{T \in T' \in S} (-1)^{|S|-|T'|} g_{S, T'} = \sum_{T \in T' \in S} (-1)^{|S|-|T'|} f(S/T')
$$

可以解出

$$
f(S) = \sum_{T \in S} (-1)^{|T|+1} f(S/T)
$$

事实上是对 $coef$ 进行了求逆。

推荐阅读：[浅谈集合划分容斥 - xiaoziyao](https://www.cnblogs.com/xiaoziyao/p/17533907.html)。

---

## 作者：Erica_N_Contina (赞：1)

预备结论：

对于一种 DAG 方案，将所有边翻转后还是一个合法的 DAG。因为所有边都被翻转了，所以两种方法对于原图要翻转的边数为 $m$。

设翻转某些边使得成为有向无环图（DAG）的方案数为 $ans$，则我们要求 $ans×m\div 2$。

所以本题和原图的边的方向无关。

于是原题在转化为：给你一个无向图，要求给边定向，求最后得到的 DAG 的数量。



这里我们考虑状态压缩。

$f_i$ 表示将 $i$ 集合内的点和边变成一个 DAG 的方案数量。

那么我们怎么样才可以转移呢？首先我们要知道初始状态：对于每一个左右一个点的集合，其方案数为 $1$。

于是现在我们就需要从一个或者几个小的 DAG 转移到一个大的 DAG 上。可以考虑**拓扑排序**的流程，是逐个从 DAG 中剔除入度为 $0$ 的点。这种方法可以把一个大的 DAG 转移成一个更小的子 DAG。那么我们反向这个过程。

我们采用填表法，用 $i$ 的子集来更新 $i$。

那么这个子集是随便选的吗？不是！我们每次都需要选择一些入度为 $0$ 的点的集合 $j$，也就是说我们要选择的子集上一个**独立集**。具体来说，就是没有任何边链接了这个子集 $j$ 内的两个点。这样可以保证向 $i-j$ 这个集合内加入 $j$ 这些点后不会产生环。



于是我们就有 $f_i =\sum_{j⫅i} f(j)dp_{i-j}$。但是很显然会算重，因为我们枚举的一些 $j$ 可能又是另外一些 $j$ 的子集（下称更大的为 $j'$），而 $j'$ 又是从 $j$ 转移来的，这样就多转移了。

那么我们就上容斥呗，咋容斥？我们按子集大小来看：

大小为 $2$ 的子集包含大小为 $1,2$ 的子集，大小为 $3$ 的子集包含大小为 $1,2,3$ 的子集……那么我们把大小为 $i$ 的子集看作 $\{1,2,\dots,i\},\dots,\{n-i+1,n-i+2,\dots,n\}$，现在我们要容斥得一个集合 $\{1,2\dots,n\}$，就是加上所有大小为奇数的集合，减去所有大小为偶数的集合！

所以容斥就出来了。

```C++
/*                                                                                
                      Keyblinds Guide
     				###################
      @Ntsc 2024

      - Ctrl+Alt+G then P : Enter luogu problem details
      - Ctrl+Alt+B : Run all cases in CPH
      - ctrl+D : choose this and dump to the next
      - ctrl+Shift+L : choose all like this
      - ctrl+K then ctrl+W: close all
      - Alt+la/ra : move mouse to pre/nxt pos'
	  
*/
#include <bits/stdc++.h>
#include <queue>
using namespace std;

#define rep(i, l, r) for (int i = l, END##i = r; i <= END##i; ++i)
#define per(i, r, l) for (int i = r, END##i = l; i >= END##i; --i)
#define pb push_back
#define mp make_pair
#define int long long
#define ull unsigned long long
#define pii pair<int, int>
#define ps second
#define pf first

// #define innt int
#define itn int
// #define inr intw
// #define mian main
// #define iont int

#define rd read()
int read(){
    int xx = 0, ff = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
		if (ch == '-')
			ff = -1;
		ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
      xx = xx * 10 + (ch - '0'), ch = getchar();
    return xx * ff;
}
void write(int out) {
	if (out < 0)
		putchar('-'), out = -out;
	if (out > 9)
		write(out / 10);
	putchar(out % 10 + '0');
}

#define ell dbg('\n')
const char el='\n';
const bool enable_dbg = 1;
template <typename T,typename... Args>
void dbg(T s,Args... args) {
	if constexpr (enable_dbg){
    cerr << s;
    if(1)cerr<<' ';
		if constexpr (sizeof...(Args))
			dbg(args...);
	}
}

#define zerol = 1
#ifdef zerol
#define cdbg(x...) do { cerr << #x << " -> "; err(x); } while (0)
void err() { cerr << endl; }
template<template<typename...> class T, typename t, typename... A>
void err(T<t> a, A... x) { for (auto v: a) cerr << v << ' '; err(x...); }
template<typename T, typename... A>
void err(T a, A... x) { cerr << a << ' '; err(x...); }
#else
#define dbg(...)
#endif


const int N = 20;
const int INF = 1e18;
const int M = 1e7;
const int MOD = 998244353;


int op[1<<N],f[1<<N];
int n,m;

struct node{
    itn a,b;
}t[400];

int ban[1<<N];

void init(){
    op[0]=MOD-1;
    for(int i=1;i<(1<<n);i++){
        op[i]=MOD-op[i&(i-1)];
    }
}

inline int ksm(int a,int b){
    int res=1;
    while(b){
        if(b&1)res=res*a%MOD;
        b>>=1;
        a=a*a%MOD;
    }
    return res;
}



void solve(){
     n=rd,m=rd;
    //  if (n!=10)assert(0);

    init();


    for(int i=1;i<=m;i++){
        t[i].a=rd-1;
        t[i].b=rd-1;
    }

    for(int i=1;i<(1<<n);i++){
        for(int j=1;j<=m;j++){
            if((i&(1<<t[j].a))&&(i&(1<<t[j].b))){
                ban[i]=1;
                break;
            }
        }
    }

    f[0]=1;
    for(int i=1;i<(1<<n);i++){
        for(int j=i;j;j=((j-1)&i)){
            //枚举i的子集，参考了https://oi-wiki.org/math/binary-set/#遍历所有掩码的子掩码
            if(ban[j])continue;
            // ban[j]=0表示j集合内的点完全独立
            f[i]+=f[i^j]*op[j]%MOD;
            f[i]%=MOD;
        }
    }

    int ans=f[(1<<n)-1];
    ans=ans*m%MOD*ksm(2,MOD-2)%MOD;
    
// 在所有方案中，总能找到一种方案的反方案，两者总共翻转了 
// m 条边，设翻转某些边使得成为有向无环图（DAG）的方案数为 
// ans，则我们要求 ans×m/2

    cout<<ans<<endl;
}


signed main() {
    // freopen(".in","r",stdin);
    // freopen(".in","w",stdout);

    int T=1;
    while(T--){
    	solve();
    }
    return 0;
}
```

---

## 作者：cike_bilibili (赞：1)

首先将一个 DAG 的边整体反向也是一个 DAG，所以答案是方案数乘上 $\frac{m}{2}$，我们考虑如何统计方案数。

有 $n\le 17$，直接考虑状压DP，设 $f_s$ 表示仅包含 $s$ 这些点的方案数，我们回顾 topo 排序的过程，**每次将入度为 $0$ 的点剔除过后就变成了新的小 DAG**，从这里可以划分子问题，我们在 $s$ 中选独立集（不然公用一条边就至少有一个点入度不为 $0$），也就是枚举合法子集转移即可。

这样显然算重了，我们还是发现 $n $ 较小，直接容斥，加上至少选一个点的方案数，减去至少选两个点的方案数，以此类推。

---

## 作者：Add_Catalyst (赞：0)

# P6846 [CEOI 2019] Amusement Park 题解

------

## 知识点

状压计数 DP，DAG 计数，容斥，FWT。

## 分析

首先，如果我们可以花 $c$ 把原图转成一张 DAG，那么就会有另一种 $m-c$ 的方案。所以答案就变成了 $\frac{m}{2}$ 倍的**无向图定向 DAG 计数**。现在考虑 DAG 计数：设 $f_{S}$ 表示导出子图为 $S$ 时，DAG 的数量。

有一个最基本的思路，要把 $S$ 分成两部分，代表的意义是：在**确定为 DAG 的第一部分**中加入**第二部分**，生成一个新的 DAG 的方案。发现为了形成 DAG，我们第二部分必须为一个独立集 $T$，即其中**没有可以通过边相连的节点**。

我们可以通过 $O(n2^n)$ 的复杂度预处理出每个集合是否为独立集，记为 $p_{S}$（这里定义如果 $S$ 是独立集，则 $p_S = 1$）。

那么现在有转移式：（注意 $T\subset S$ 表示 $T$ 是 $S$ 的真子集）
$$
f_S = \sum_{T \subseteq S,T \neq \varnothing} f_{S\setminus T} [p_{T}] \\
$$
但是这是一个会重复计数的转移式，所以我们对其进行容斥，现在推导其容斥系数：

设 $g_T$ 表示限定了导出子图点集 $S$ 下，选出的**第二部分**恰好为 $T$ 时的方案数，那么实际上有：
$$
f_S = \sum_{T \subseteq S,T \neq \varnothing} g_{S} \\
g_T = \sum_{T\subseteq V\subseteq S} (-1)^{|V| - |T|} f_{S\setminus V} [p_{V}] \\
$$
所以我们代入：
$$
\begin{aligned}
f_S &= 
\sum_{T\subseteq S,T \neq \varnothing} 
\sum_{T\subseteq V\subseteq S} (-1)^{|V| - |T|} f_{S\setminus V} [p_{V}] \\
f_S &= 
\sum_{V\subseteq S,V \neq \varnothing} (-1)^{|V|} f_{S\setminus V} [p_{V}] 
\sum_{T\subseteq V,T \neq \varnothing} (-1)^{|T|}
\\
\end{aligned}
$$
众所周知，有二项式定理：（$|U| = n > 0$）
$$
\begin{aligned}
& \because
(1 - 1)^{n} = \sum_{i=0}^{n} {n\choose i} (-1)^i
\Leftrightarrow
\sum_{S\subseteq U}(-1)^{|S|}
\\
& \therefore
\sum_{S\subseteq U}(-1)^{|S|} = 0\\
& \therefore
\sum_{S\subseteq U,S\neq \varnothing}(-1)^{|S|} = -1\\
\end{aligned}
$$
所以上式可以化为：
$$
\begin{aligned}
f_S &= 
\sum_{V\subseteq S,V \neq \varnothing} (-1)^{|V|+1} f_{S\setminus V} [p_{V}] 
\\
\end{aligned}
$$
容斥系数可以在 $O(2^n)$ 的时间复杂度内算出，总复杂度子集枚举为 $O(3^n + n2^n)$，如果 FWT 则可以优化到 $O(n^22^n)$。

## 代码

（子集枚举。）

```cpp
#define Plus_Cat "park"
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define ll long long
#define RCL(a,b,c,d) memset(a,b,sizeof(c)*(d))
#define FOR(i,a,b) for(int i(a);i<=(int)(b);++i)
#define DOR(i,a,b) for(int i(a);i>=(int)(b);--i)
#define tomax(a,...) ((a)=max({(a),__VA_ARGS__}))
#define tomin(a,...) ((a)=min({(a),__VA_ARGS__}))
#define EDGE(g,i,x,y) for(int i=(g).h[(x)],y=(g)[(i)].v;~i;y=(g)[(i=(g)[i].nxt)>0?i:0].v)
#define main Main();signed main(){ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);return Main();}signed Main
using namespace std;
constexpr int N(18+10),M(153+10),St((1<<18)+10);

namespace IOEcat {
    //Fast IO...
} using namespace IOEcat;

namespace Modular {
    //Mod Int...
} using namespace Modular;

bool p[St];
int n,m,U;
int u[M],v[M],c[St],f[St];

signed main() {
#ifdef Plus_Cat
	freopen(Plus_Cat ".in","r",stdin),freopen(Plus_Cat ".out","w",stdout);
#endif
	I(n,m),U=(1<<n)-1,f[0]=1,c[0]=Mod-1;
	FOR(i,1,m)I(u[i],v[i]),p[1<<(u[i]-1)|1<<(v[i]-1)]=1;
	FOR(S,1,U)c[S]=(S&1?Mod-c[S^1]:c[S>>1]);
	FOR(S,1,U)FOR(i,1,n)if((S&1<<(i-1))&&(p[S]|=p[S^1<<(i-1)]))break;
	FOR(S,1,U)for(int T(S); T; T=(T-1)&S)if(!p[T])toadd(f[S],mul(c[T],f[S^T]));
	O(mul(f[U],m,Inv2),'\n');
	return 0;
}
```

------

---

## 作者：gdf_yhm (赞：0)

[P6846](https://www.luogu.com.cn/problem/P6846)

### 思路

对于一个 DAG，把所有边反向后也是 DAG。即 $x$ 步做出一个 DAG，就可以 $m-x$ 步做出对应的另一个。所以答案为 DAG 数乘 $\frac{m}{2}$。

状压 $dp_S$ 表示 $S$ 的导出子图的 DAG 数。枚举 $S$ 的子集 $T$，认为 $T$ 是无入度点集合，则 $T$ 中无边，变为 $S-T$ 的子问题。但 $T$ 可能是真正的无入度点集合的子集，尝试容斥。赋 $(-1)^{|T|+1}$ 的容斥系数，对于真正的无入度点集合 $S$，$\sum_{T\subseteq S,T\neq \emptyset}(-1)^{|T|+1}=\sum_{i=1}^{|S|}\binom{|S|}{i}(-1)^{i+1}=\binom{|S|-1}{0}=1$。

设 $e_S$ 表示 $S$ 内是否有边。然后 $O(3^n)$ 枚举子集即可：$dp_S=\sum_{T\subseteq S,T\neq \emptyset} [e_T=0](-1)^{|T|+1} dp_{S-T}$。

进一步，可以看成从空集开始每次加上一个集合（有序），集合带有 $0/1/-1$ 的系数。对于集合幂级数 $f$，$f_T=[e_T=0](-1)^{|T|+1}$ 且 $f_0=0$，设 $g(x)=\sum_{i=0}x^i=\frac{1}{1-x}$，等价于求 $g(f)$ 在全集的系数。也即求集合幂级数 $1-f$ 的 [逆](https://www.luogu.com.cn/problem/P12232)，逆着子集卷积做即可。复杂度 $O(2^nn^2)$，还是能快一点的。

### code

```cpp
int n,m;
int e[1<<maxn],f[1<<maxn],g[1<<maxn];
void fmt(int *a,int n,int w){
	for(int i=0;i<n;i++){
		if(w==1){
			for(int s=0;s<(1<<n);s++)if(s&(1<<i))(a[s]+=a[s^(1<<i)])%=mod;
		}
		else{
			for(int s=0;s<(1<<n);s++)if(s&(1<<i))(a[s]+=mod-a[s^(1<<i)])%=mod;
		}
	}
}
int ff[maxn+1][1<<maxn],hh[maxn+1];
void xorni(int *a,int *b,int n){//g=1/(1-f)
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s];
	for(int i=0;i<=n;i++)fmt(ff[i],n,1);
	for(int s=0;s<(1<<n);s++){
		ff[0][s]=mod+1-ff[0][s];for(int i=1;i<=n;i++)ff[i][s]=mod-ff[i][s];
		int nif=ksm(ff[0][s]);
		for(int i=0;i<=n;i++){
			hh[i]=1;
			for(int j=1;j<=i;j++)(hh[i]+=mod-ff[j][s]*hh[i-j]%mod)%=mod;
			hh[i]=hh[i]*nif%mod;
		}
		for(int i=0;i<=n;i++)ff[i][s]=hh[i];
	}
	for(int i=0;i<=n;i++)fmt(ff[i],n,-1);
	for(int s=0;s<(1<<n);s++)b[s]=ff[__builtin_popcount(s)][s];
}
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read()-1,v=read()-1;
		e[(1<<u)|(1<<v)]++;
	}
	fmt(e,n,1);
	f[0]=0;for(int s=1;s<(1<<n);s++){
		if(e[s])f[s]=0;
		else f[s]=((__builtin_popcount(s)+1)&1)?-1:1;
	}
	xorni(f,g,n);
	printf("%lld\n",g[(1<<n)-1]*m%mod*(mod+1)/2%mod);
}
```

---

## 作者：__ycx2010__ (赞：0)

## Solution

若改变了 $k$ 条边能变为有向无环图，那么反转另外 $m-k$ 条边也一定能得到有向无环图，所以平均反转 $\frac{m}{2}$ 条边，转化为求有向无环图的个数。

设 $f_S$ 表示原图 $G$ 中包含点集 $S$ 的导出子图的方案数。

假设 $T$ 为拓扑图上的第一层点，也就是没有入边的点，那么这些点一定要满足 $T$ 为独立集，发现这样会有重复，所以用容斥得到

$$f_S = \sum _{T\subseteq S} (-1)^{|T|+1} f_{S\backslash T}$$

时间复杂度 $O(3^n)$。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 20, mod = 998244353;
int g[N][N], bit[1 << N], f[1 << N], ok[1 << N];

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i ++ ) {
		int a, b;
		scanf("%d%d", &a, &b);
		g[a][b] = g[b][a] = 1;
	}
	vector<int> v;
	for (int i = 1; i < (1 << n); i ++ ) {
		for (int j = 0; j < n; j ++ )
			if (i >> j & 1)
				bit[i] ++ ;
		ok[i] = 1;
		for (int j = 0; j < n; j ++ )
			if (i >> j & 1)
				for (int k = j + 1; k < n; k ++ )
					if ((i >> k & 1) && g[j + 1][k + 1])
						ok[i] = 0;
	}
	f[0] = 1;
	for (int i = 1; i < (1 << n); i ++ )
		for (int j = i; j; j = (j - 1) & i)
			if (ok[j])
				f[i] = (f[i] + ((bit[j] & 1) ? f[i ^ j] : 1ll * (mod - 1) * f[i ^ j] % mod)) % mod;
	printf("%d\n", 1ll * f[(1 << n) - 1] * m % mod * (mod + 1 >> 1) % mod);
	return 0;
}
```

---

