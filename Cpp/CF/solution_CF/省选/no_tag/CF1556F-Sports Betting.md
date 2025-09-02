# Sports Betting

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1556F/019d3452101b513cd6bdfca73d0ad9bf76ce0ea0.png)William is not only interested in trading but also in betting on sports matches. $ n $ teams participate in each match. Each team is characterized by strength $ a_i $ . Each two teams $ i < j $ play with each other exactly once. Team $ i $ wins with probability $ \frac{a_i}{a_i + a_j} $ and team $ j $ wins with probability $ \frac{a_j}{a_i + a_j} $ .

The team is called a winner if it directly or indirectly defeated all other teams. Team $ a $ defeated (directly or indirectly) team $ b $ if there is a sequence of teams $ c_1 $ , $ c_2 $ , ... $ c_k $ such that $ c_1 = a $ , $ c_k = b $ and team $ c_i $ defeated team $ c_{i + 1} $ for all $ i $ from $ 1 $ to $ k - 1 $ . Note that it is possible that team $ a $ defeated team $ b $ and in the same time team $ b $ defeated team $ a $ .

William wants you to find the expected value of the number of winners.

## 说明/提示

To better understand in which situation several winners are possible let's examine the second test:

One possible result of the tournament is as follows ( $ a \rightarrow b $ means that $ a $ defeated $ b $ ):

- $ 1 \rightarrow 2 $
- $ 2 \rightarrow 3 $
- $ 3 \rightarrow 1 $
- $ 1 \rightarrow 4 $
- $ 1 \rightarrow 5 $
- $ 2 \rightarrow 4 $
- $ 2 \rightarrow 5 $
- $ 3 \rightarrow 4 $
- $ 3 \rightarrow 5 $
- $ 4 \rightarrow 5 $

Or more clearly in the picture:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1556F/6c25791d22e17c072eecc03de22b6a045c024954.png)In this case every team from the set $ \{ 1, 2, 3 \} $ directly or indirectly defeated everyone. I.e.:

- $ 1 $ st defeated everyone because they can get to everyone else in the following way $ 1 \rightarrow 2 $ , $ 1 \rightarrow 2 \rightarrow 3 $ , $ 1 \rightarrow 4 $ , $ 1 \rightarrow 5 $ .
- $ 2 $ nd defeated everyone because they can get to everyone else in the following way $ 2 \rightarrow 3 $ , $ 2 \rightarrow 3 \rightarrow 1 $ , $ 2 \rightarrow 4 $ , $ 2 \rightarrow 5 $ .
- $ 3 $ rd defeated everyone because they can get to everyone else in the following way $ 3 \rightarrow 1 $ , $ 3 \rightarrow 1 \rightarrow 2 $ , $ 3 \rightarrow 4 $ , $ 3 \rightarrow 5 $ .

Therefore the total number of winners is $ 3 $ .

## 样例 #1

### 输入

```
2
1 2```

### 输出

```
1```

## 样例 #2

### 输入

```
5
1 5 2 11 14```

### 输出

```
642377629```

# 题解

## 作者：暴力出奇迹 (赞：10)

题目链接：[https://www.luogu.com.cn/problem/CF1556F](https://www.luogu.com.cn/problem/CF1556F)

题解区里讲的 $O(3^n \times n^2)$ 的做法已经很详细了，**这里主要是讲一下怎么优化到 $O(3^n \times n)$。**

先口胡一下 $O(3^n \times n^2)$ 的做法，尽量简略一点。

考虑期望线性性，求 Winner 的期望数量就相当于是每个人成为 Winner 的概率之和，这里枚举每个人计算，复杂度是 $O(n)$ 的。

考虑设状态 $f_{i,S}$ 表示 $i$ 赢了 $S$ 中所有人的概率（这里规定 $i \in S$，但不要求 $i$ 赢自己）。**正难则反**，考虑 $i$ 什么时候赢不了 $S$ 中所有人，也就是他能赢一部分人（记为 $T$），但是这部分人完全输给了 $S-T$ 中的人。设 $g(S,T)$ 表示 $S$ 中的人完全败给 $T$ 中的人的概率（$S \cap T=\varnothing$），则有

$$f_{i,S}=1-\sum_{\{i\} \subseteq T \subset S}f_{i,T} \times g(T,S-T)$$

枚举 $S$ 再枚举其子集是 $O(3^n)$ 的，暴力计算 $g(T,S-T)$ 复杂度是 $O(n^2)$，总复杂度是 $O(3^n \times n^3)$（包括前面的枚举）。

考虑优化 $g(S,T)$ 的计算，题解区大多数说的是记 $h(i,S)$ 表示 $i$ 输给集合 $S$ 中所有人的概率，预处理 $h(i,S)$ 不难做到 $O(n)$ 求出 $g(S,T)$，复杂度变为 $O(3^n \times n^2)$，可以通过。

这里介绍一下如何优化成 $O(3^n \times n)$，其实也非常简单，我们发现 $g(S,T)$ 中 $S \cap T=\varnothing$，也就是这样的集合二元组 $(S,T)$ 数量是 $3^n$，那我们直接用上面的方法，$O(n)$ 求出 $g(S,T)$，就可以 $O(3^n \times n)$ 预处理出所有的 $g(S,T)$，转移的时候可以 $O(1)$ 查询。

这样就结束了吗？没有！$g(S,T)$ 数组开不下！算一下空间大概是 $\dfrac{2^{14} \times 2^{14} \times 4}{1024 \times 1024}=1024(MB)$，直接裂开来。

但是我们抓住本质，发现如果这样开数组，数组的很多位置都是空着的，那我们可以尝试**把这样的 $(S,T)$ 二元组压缩成三进制**，用数组存储，空间是 $\dfrac{3^{14} \times 4}{1024 \times 1024}=18(MB)$。

具体来说，将二元组 $(S,T)$ 压缩成三进制 $S'$，考虑每个二进制位，如果 $S$ 的这个二进制位上是 $1$，则 $S'$ 的这个位置是 $2$；如果 $T$ 的这个二进制位上是 $1$，则 $S'$ 的这个位置是 $1$；否则 $S'$ 的这个位置是 $0$。

我们考虑再开一个数组 $flect[S]$，记录把 $S$ 写成二进制后，所有 $1$ 的位置不变，但是把进制改为三进制，对应的数值，这显然可以 $O(2^n \times n)$ 或者 $O(2^n)$ 预处理所有的 $flect[S]$。

这样，一个二元组 $(S,T)$ 对应的三进制 $S'$ 可以这样计算：

$$S'=2flect[S]+flect[T]$$

到此为止，$O(3^n \times n)$ 的压缩、存储、提取方法就讲完了。代码如下：

```cpp
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 14;
const int M = 5000010; //比 3^14 略大一点
const int mod = 1e9 + 7;
int win[N][N]; //win[i][j] 表示 i 赢 j 的概率
int f[1 << N], flect[1 << N]; //观察到状态转移方程中，i 是一直不变的，所以直接省略 f 数组的第一维度
int a[N], g[M], h[N][1 << N], n;
inline int pow(int x, int y) {
	int ret = 1;
	while(y) {
		if(y & 1) ret = 1ll * ret * x % mod;
		x = 1ll * x * x % mod;
		y >>= 1;
	}
	return ret;
}
int main() {
	scanf("%d", &n);
	for(register int i = 0; i < n; ++i)
		scanf("%d", &a[i]); //从 0 开始标号
	for(register int i = 0; i < n; ++i)
		for(register int j = 0; j < n; ++j)
			if(i == j) win[i][j] = 1;
			else win[i][j] = 1ll * a[i] * pow(a[i] + a[j], mod - 2) % mod;
	for(register int S = 0; S < (1 << n); ++S)
		for(register int i = 0; i < n; ++i)
			if((S >> i) & 1) flect[S] += pow(3, i); //预处理 flect[S]
	for(register int i = 0; i < n; ++i) {
		h[i][0] = 0;
		for(register int S = 1; S < (1 << n); ++S)
			if(!((S >> i) & 1)) {
				h[i][S] = 1;
				for(register int j = 0; j < n; ++j)
					if((S >> j) & 1) h[i][S] = 1ll * h[i][S] * win[j][i] % mod; //预处理 h[i][S]
			}
	}
	for(register int S = 0; S < (1 << n); ++S) {
		int Us = (1 << n) - 1 - S;
		for(register int T = Us; T; T = (T - 1) & Us) {
			int x = flect[S] * 2 + flect[T]; g[x] = 1;
			for(register int i = 0; i < n; ++i)
				if((S >> i) & 1) g[x] = 1ll * g[x] * h[i][T] % mod; //预处理 g(S,T) 并且压缩
		}
	}
	int ans = 0;
	for(register int i = 0; i < n; ++i) {
		memset(f, 0, sizeof(f));
		for(register int S = 0; S < (1 << n); ++S) {
			if(!((S >> i) & 1)) continue;
			if(S == (1 << i)) f[S] = 1;
			else {
				int Ui = S ^ (1 << i), sum = 0;
				for(register int T = Ui; T >= 0; T = (T - 1) & Ui) { //这里的 T 是上面状态转移方程中，去掉 i 本身之后的 T，所以允许 T=0！
					if(T == Ui) continue;
					int Ut = Ui ^ T;
					int x = flect[T | (1 << i)] * 2 + flect[Ut];
					sum = (sum + 1ll * f[T | (1 << i)] * g[x]) % mod; //这里再把 i 补到 T 里面
					if(T == 0) break;
				}
				f[S] = (1 - sum + mod) % mod;
			}
		}
		ans = (ans + f[(1 << n) - 1]) % mod;
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：Cry_For_theMoon (赞：8)

[传送门](https://codeforces.com/contest/1556/problem/F)

思维上比 E 简单多了...

#### 分析：

首先套路化地，求最后获胜者的期望数，可以通过期望线性性，计算出每个人的获胜概率求和得出（因为权值为 $1$ 所以直接转成概率做）。

然后考虑状压 dp，我们设 $f(i,S)$ 是第 $i$ 个人，赢过了集合 $S$ 里的所有人的概率，其中必须满足 $i \in S$。那么答案就是 $\sum f(i,2^n-1)$。

首先考虑刷表，就是说对于一个 $f(i,S)$ 计算它对一个更大的 $T$ 的 $f(i,T)$ 的贡献。但注意到这是不可行的，因为会重复计算，举个例子，可能会出现 $f(i,S)\Longrightarrow f(i,T)\Longrightarrow f(i,T')$ 的情况，但是 $S$ 也是 $T'$ 的子集，它本身也会来一次 $f(i,S)\Longrightarrow f(i,T')$ 的计算所以会算重。

那么我们考虑填表，即考虑 $f(i,S)$ 的计算。我记得前两场的ABC G还考过这个经典的trick：考虑容斥，即 $f(i,S)=1-X$，其中 $X$ 为 $i$ 没有把 $S$ 集合里的所有人都赢了的概率。我们考虑如何计算 $X$：

$$
X=\sum f(i,T)g(T,S-T)
$$

其中，$T$ 是 $S$ 的真子集，且包含元素 $i$，$S-T$ 是 $T$ 在 $S$ 中的补集，$g(L,R)$ 定义为 $L$ 集合的人和 $R$ 集合的人之间，每场比赛都是 $R$ 集合的人获胜的概率。

这个式子的意义就是，枚举 $i$ 赢了的人的集合，然后让这个集合不能往外拓展就行了。

考虑计算 $g(T,S-T)$ 的复杂度是 $O(n^2)$ 的所以总复杂度是 $O(3^nn^3)$，显然跑不过去。考虑继续优化 $g$ 的计算，即预处理一些信息：设 $h(i,S)$ 是点 $i$ 和集合 $S$ 的人的比赛之间，每场比赛都是 $S$ 集合的人获胜的概率。$h$ 的计算显然是 $O(2^nn^2)$ 的，然后用 $h$ 可以 $O(n)$ 计算 $g$：

$$
g(L,R)=\prod_{i \in L}h(i,R)
$$

总复杂度降为 $O(3^nn^2)$，大概是 $8\times 10^9$ 级别的，加上对集合还带了个包含关系的限制，实际上是跑不满的，可以通过此题。

```
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=15,MAXM=(1<<14),mod=1e9+7;
int n,a[MAXN],inv[(int)(2e6+10)];
int ans,h[MAXN][MAXM],f[MAXN][MAXM];
il int g(int S,int T){
	int ret=1;
	rep(i,0,n-1){
		if(!(S&(1<<i)))continue;
		ret=1LL*ret*h[i][T]%mod;
	}
	return ret;
}
void solve(){
	//预处理h
	rep(i,0,n-1){
		rep(j,1,(1<<n)-1){
			if(j&(1<<i))continue;
			h[i][j]=1;
			rep(k,0,n-1){
				if(j&(1<<k)){
					h[i][j]=1LL*h[i][j]*a[k]%mod*inv[a[i]+a[k]]%mod;
				}
			}
		}
	} 
	rep(i,0,n-1){
		rep(j,1,(1<<n)-1){
			if(!(j&(1<<i)))continue;
			f[i][j]=1;
			for(int k=j;k;k=(k-1)&j){
				if(k==j || !(k&(1<<i)))continue;
				f[i][j]=(f[i][j]-1LL*f[i][k]*g(k,k^j)%mod+mod)%mod;
			}
		} 
	}
}
int main(){
	inv[1]=1;
	rep(i,2,2e6){
		inv[i]=((1LL*-(mod/i)*inv[mod%i])%mod+mod)%mod;
	}
	scanf("%d",&n);
	rep(i,0,n-1)scanf("%d",&a[i]);
	solve();
	rep(i,0,n-1){
		ans=(ans+f[i][(1<<n)-1])%mod;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：云浅知处 (赞：5)

设 $f(i,S)$ 为 $i$ 打败了 $S$ 中所有人的概率，其中限定 $i\in S$。那么设全集 $U=\{1,2,\cdots,n\}$，答案就是 $\sum f(i,U)$。

直接转移好像很难搞，我们考虑容斥：如果 $i$ 没有打败 $S$ 中的所有人，那么如果 $i$ 打败的人组成的集合为 $T$，概率就是
$$
f(i,T)\prod_{j\in T}\prod_{k\in S-T}\dfrac{a_k}{a_j+a_k}
$$
因此，我们得到转移方程：
$$
f(i,S)=1-\sum_{T\subset S}f(i,T)\prod_{j\in T}\prod_{k\in S-T}\dfrac{a_k}{a_j+a_k}
$$
考虑预处理一下 $g(i,S)=\prod_{j\in S}\dfrac{a_j}{a_i+a_j}$，那么转移方程就变为
$$
f(i,S)=1-\sum_{T\subset S}f(i,T)\prod_{j\in T}g(j,S-T)
$$
递推一下，预处理的复杂度就是 $O(n2^n)$。而转移的复杂度为 $O(n^23^n)$，故总的复杂度为 $O(n^23^n)$。

看上去 $3^{14}\cdot 14^2=937461924$ 很大，但理性分析一下可以发现这东西的实际操作数为
$$
n\cdot\left(\sum_{d=0}^nC_n^d\sum_{j=0}^{d-1}j\cdot C_d^j-\sum_{d=0}^{n-1}C_{n-1}^d\sum_{j=0}^{d-1}j\cdot C_d^j\right)
$$
算了一下发现 $n=14$ 的时候只有 $214904886$，也就 2e8，还是很稳的。

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

inline int read(){
    int x=0,f=1;char c=getchar();
    for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
    for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
    return x*f;
}

const int mod=1e9+7;
const int MN=17;
const int MC=2e6+5;

int n,a[1<<MN],inv[MC],f[MN][1<<MN],g[MN][1<<MN],Lg[1<<MN];

int lowbit(int x){
	return x&(-x);
}

int calc(int S,int T){
	int prod=1;
	while(S)prod=prod*g[Lg[lowbit(S)]][T]%mod,S&=S-1;
	return prod%mod;
}

signed main(void){
	
#ifndef ONLINE_JUDGE
	freopen("in.in","r",stdin);
#endif		
	
	n=read();int U=(1<<n)-1;
	for(int i=0;i<n;i++)a[1<<i]=read();
	Lg[1]=0;for(int i=2;i<=U;i++)Lg[i]=Lg[i>>1]+1;
	inv[1]=1;for(int i=2;i<=2000000;i++)inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	for(int i=0;i<n;i++){
		g[i][0]=1;
		for(int S=1;S<=U;S++)g[i][S]=g[i][S^lowbit(S)]%mod*a[lowbit(S)]%mod*inv[a[lowbit(S)]+a[1<<i]]%mod;
	}
	for(int i=0;i<n;i++){
		for(int S=0;S<=U;S++){
			if(!(S&(1<<i)))continue;
			f[i][S]=1;
			for(int T=S&(S-1);T;T=(T-1)&S)f[i][S]=(f[i][S]-f[i][T]*calc(T,S^T)%mod+mod)%mod; 
		}
	}
	int ans=0;
	for(int i=0;i<n;i++)ans=(ans+f[i][U])%mod;
	cout<<ans<<endl;

    return 0;
}
```

---

## 作者：juju527 (赞：4)

### 题意

给定一个大小为 $n$ 的竞赛图，和一个长度为 $n$ 的序列 $a$。

$i,j$ 之间的边为 $i\to j$ 的概率为 $\dfrac{a_i}{a_i+a_j}$，否则为 $\dfrac{a_j}{a_i+a_j}$。

求图强连通分量缩点后 SCC 链上最前的 SCC 的期望大小。

$n\leq 14,a_i\leq 10^6$

### 前置知识
**竞赛图的基本性质**

对于一个竞赛图，其 SCC 缩点后形如一条链。

链前端的点的所有出边指向链后端的点。

下文所有 SCC 链均指这一条缩完 SCC 后的链状物。
### $\texttt{Solution}$

我们考虑对于任意一个点集 $s$，求出其为链上第一个 SCC 的概率 $f(s)$。

最后的答案即为 $\sum_{s}|s|f(s)$。

显然，$f$ 并不好求，我们很难直接算一个点集为第一个 SCC 的概率。

比较好算的是一个点集为一个 SCC 链上前缀的概率。

我们记 $p(s,t)$ 表示点集 $s$ 与点集 $t$ 之间的边全部为 $s\to t$ 的概率。

$p(s,t)=\prod_{i\in s}\prod_{j\in t}\dfrac{a_i}{a_i+a_j}$。

设 $g(s)$ 表示点集 $s$ 为 SCC 链上一段前缀的概率。

显然，$g(s)=p(s,\overline s)$。

我们如何求得 $f$？

考虑 $g(s)$ 比 $f(s)$ 多算了点集 $s$ 被分成一条长度大于 1 的SCC 链的情况。

我们枚举该种情况的第一个 SCC，其点集为 $t$，那么

$f(s)=g(s)-\sum_{t\subsetneq s,t\neq \varnothing}\dfrac{f(t)g(s-t)}{p(s-t,t)}$。

式子的含义比较显然。

除掉 $p(s-t,t)$ 是因为点集 $t$ 与 $s-t$ 之间的边均为 $t\to (s-t)$，

而 $g(s-t)$ 多算了一边 $(s-t)\to t$ 的概率。

预处理以下逆元枚举子集就能做到 $O(2^nn^2+3^nn^2)$ 了。

显然这东西跑不满，实测 2s 内就能跑出来。

[code](https://codeforces.com/contest/1556/submission/127386281)

---

## 作者：tylon2006 (赞：3)

其他题解在干什么啊（

---

简单 $O(3^n)$。

竞赛图。缩点后为链，所求为链头强联通块大小。

因为边权各不相同，需要大力枚举已取点的状态。

一种状态的贡献即集合内构成强联通分量的概率乘上对外外向边的概率。

后者 $O(2^nn)$ 转移是 trivial 的。

前者可以子集 dp，大力枚举得到所有情况。

设 $f_{S}$ 为状态为 $S$ 时构成强联通分量的概率。

简单容斥得到 
$$
f_{S}=1-\sum_{T\subseteq S}f_T\cdot p_{T,\complement_ST}
$$

此处 $p_{T,\complement_ST}$ 表示 $T$ 中点向 $\complement_ST$ 中点连边的概率积。

直接暴力计算是 $O(3^nn^2)$ 的。

预处理单个点对一个集合的点可以做到时间 $O(3^nn)$，空间 $O(2^nn)$。

可以平衡复杂度，对所有 $S$ 预处理出 $p_{S,T}$，其中 $T\subseteq U$。

递推预处理复杂度是 
$$
\sum_{i=1}^n\binom{n}{i}2^{n-i}=\sum_{i=1}^n\binom{n}{i}2^{i}=3^n
$$

需要使用 unordered_map 保存，空间也是 $O(3^n)$ 的。

然后就爆了。

这部分可以再次容斥，用 $T$ 中每个点对 $S$ 连边的概率积再乘上 $T$ 内部连边的逆元解决。计算 $f$ 时用 $lowbit$ 递推，就可以每次加入一个点，还原旧贡献，乘上新贡献即可。

对每个 $S$ 保存一个双向边完全图概率积即可。

这样空间仍然是 $O(2^nn)$ 的。

但是怎么感觉这还是垃圾做法（）

不给代码了（只写了 $O(3^nn)$，懒得写优化）。

---

## 作者：Terminus_Est (赞：2)

### 【CF1556F】Sports Betting 解题报告

$O(3^n+n2^n)$ 喜提 CF rank1。

*做法和之前的题解不一样！*

原图是一个有向完全图，也就是说是一个竞赛图。而我们知道，竞赛图缩点后为一条链，根据题目描述，不难发现 winner 的数量就是链的头部的大小。于是我们只用求链头部的大小的期望。换句话说，我们需要求出每种大小的概率，乘上大小，就是我们要求的期望了。

我们枚举链头部的所有可能点集 $S$，并且算出他们全部指向点集 $T$ 中所有点 的概率，并记这个数组为 $g_{S,T}$。则一个初步的答案就是 $g_{S,all\bigoplus S}$。这个可以通过 $O(n2^n)$ 时间的预处理数组 $f_{i,S}$ 代表点 $i$ 指向 $S$ 中所有点的概率来求出。（这样空间复杂度是 $O(3^n)$ 的，而且非常难实现，具体如何优化在下面。）

但是，数组 $g$ 就是我们想要的答案了吗？并不是，因为点集 $S$ 中还有可能存在多个强联通分量。于是我们考虑容斥，记最后点集 $S$ 成为链头的真正概率为 $h_S$，则我们可以得到：

$$
h_S=g_{S,all\bigoplus S}-\sum_{T \subseteq S} h_T g_{S\bigoplus T,all\bigoplus S}
$$

然后你会发现，$g_{S\bigoplus T,all\bigoplus S}$ 的第二维是一样的，而你枚举子集的时候 $S\bigoplus T$ 是不断增大的，于是你就可以一边跑容斥一边利用 $f$ 数组处理出 $g$ 而不需要记录 $O(3^n)$ 种状态，你的空间就解决了，而且实现非常小清新。这部分只需要枚举子集，时间复杂度为 $O(3^n)$。

code below:

```cpp
#include<bits/stdc++.h>
using namespace std;
// #define int long long
typedef long long ll;
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
#define repg(i,u) for(int i=head[u];~i;i=edge[i].nxt)
#define lowbit(x) (x&(-x))
#define ls (o<<1)
#define rs (o<<1|1)
#define mp make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define db double
#define endl '\n'
#define push_back emplace_back
inline int read(){
	int num=0,f=1;char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')f=0;
		ch=getchar();
	}
	while(isdigit(ch)){
		num=num*10+ch-'0';
		ch=getchar();
	}
	return f?num:-num;
}
const int mod=1e9+7;
inline int add(int x,int y){return x+y>=mod?x+y-mod:x+y;}
inline int sub(int x,int y){return x<y?x-y+mod:x-y;}
inline int mul(int x,int y){return 1ll*x*y%mod;}
inline int qpow(int n,int k){
	int ret=1;
	while(k){
		if(k&1)ret=mul(ret,n);
		n=mul(n,n);
		k>>=1;
	}
	return ret;
}
const int MAXN=20;
const int MAXM=16384;
int n;
int a[MAXN];
int id[MAXM];
int val[MAXN][MAXN];
int trs[MAXN][MAXM];
int g[MAXM];
int dp[MAXM];
void solve(){
	n=read();
	rep(i,1,n)a[i]=read(),id[(1<<(i-1))]=i;
	rep(i,1,n){
		rep(j,1,n){
			if(i==j)continue;
			val[i][j]=mul(a[i],qpow(a[i]+a[j],mod-2));
		}
	}
	const int lim=(1<<n)-1;
	rep(i,1,n){
		trs[i][0]=1;
		rep(sta,1,lim){
			trs[i][sta]=mul(trs[i][sta^lowbit(sta)],val[i][id[lowbit(sta)]]);
		}
	}
	int ans=0;
	rep(s,1,lim){
		int els=lim^s;
		g[0]=1;
		for(int t=(s-1)&s;t;t=(t-1)&s){
			int st=s^t;
			g[st]=mul(g[st^lowbit(st)],trs[id[lowbit(st)]][els]);
			dp[s]=sub(dp[s],mul(dp[t],g[st]));
		}
		g[s]=mul(g[s^lowbit(s)],trs[id[lowbit(s)]][els]);
		dp[s]=add(dp[s],g[s]);
		ans=add(ans,mul(dp[s],__builtin_popcount(s)));
	}
	printf("%d\n",ans);
}
signed main(){
	// int T=read();
	int T=1;
	while(T--)solve();
}
```

---

## 作者：cmll02 (赞：2)

显然是状压。

设 $dp_i$ 表示**假设全集为** $i$，集合 $i$ 内部全是 winner 的概率。

这个东西不好求，反向求**假设全集为** $i$，集合 $i$ 内部**不**全是 winner 的概率。

枚举 $i$ 的子集 $j$，表示 $i$ 中 winner 集合为 $j$。

那么贡献为 $dp_j \times \text{(j 中所有队伍都打败了 j 以外 i 以内的队伍的概率)}$。

从 $dp_i$ 中减掉这份贡献就行了。

接下来求出答案。

若 winner 集合为 $i$，需要满足两个条件。

1. 全集为 $i$ 时 $i$ 内部全是 winner；
2. $i$ 的队伍吊打 $i$ 以外的所有队伍。

暴力算这部分就行。

贡献是 $size_i\times dp_i\times (\prod\limits_{x\in i}\prod\limits_{y\not\in i}\dfrac{a_x}{a_x+a_y})$。

代码太丑了，挂个 CF [链接](https://codeforces.com/contest/1556/submission/127390950)吧。

---

## 作者：E1_de5truct0r (赞：1)

好题，一眼想到了转化，但是那个容斥卡了我好久。

## 思路

首先这个期望是诈骗的，由期望的线性性质我们知道，最后的结果等于每个点成为 winner 的概率之和（因为每个点的权值为 1 所以甚至不需要加权）。

另外这个 $i$ 可选可不选很恶心，我们在一开始就强制它选上，避免转移出毛病。这样的话答案统计也更方便。

考虑到 $n \leq 14$，所以我们如果令 $f_{i,S}$ 表示 $i$ 击败了 $S$ 集合内的所有人的概率。

那么，我们每次的转移就考虑 $i$ 只击败了 $S$ 的某个子集 $T$，再考虑子集 $T$ 击败了子集 $S-T$ 的概率，二者乘起来就是答案。

前者显然为 $f_{i,T}$，后者直接算不好算，但是我们可以考虑容斥。我们枚举每一个 $T$ 的时候，可以考虑算出“$S-T$ 每一个元素都击败 $T$ 中每一个元素”的概率，这样加起来就是“$T$ 没有击败 $S-T$”的概率了，我们用 $1$ 减去之，即可得到我们要求的概率。

而上述的这个概率可以使用数学公式表示：

$$P=\sum_{T \subset S}f_{i,T}\prod_{p \in T}\prod_{q \in S-T}\dfrac{a_q}{a_p+a_q}$$

所以转移方程就为：$f_{i,S}=1-P$。

但是现在的复杂度太高了，我们考虑预处理之后加快计算 $P$。不难发现可以对每对 $(i,S)$ 维护 $\prod\limits_{j \in S}\dfrac{a_j}{a_i+a_j}$。然后 $P$ 计算的最后一维就被压缩掉了。

复杂度 $O(3^nn^2)$，但是跑不满，实际大概是 $O(\text{能过})$。

## 代码

Talk is chaep, show me the cdoe.

[Code & Submission](https://codeforces.com/contest/1556/submission/219915665)

---

## 作者：FjswYuzu (赞：0)

所以谁能告诉我为什么 $O(3^nn^2)$ 过 $14$。

考虑定义 $dp_S$ 为，所有玩家里只有 $S$ 里面的所有玩家都为赢家的概率。考虑枚举子集转移。要从 $dp_T$ 转移至 $dp_S$，似乎正着算比较困难，考虑是赢家的概率加上不是赢家的概率为 $1$，我们计算 $S$ 里面通过 $T$ 和剩下的一部分合并后 $S$ 里面存在玩家不是赢家的概率之和（相当于 $T$ 内的玩家强制定向至在 $S$ 但不在 $T$ 内的玩家，这样在 $S$ 但不在 $T$ 内的玩家就不是赢家），然后再用 $1$ 减去就是 $dp_S$。

处理完 $dp_S$ 之后，因为我们强制仅有 $S$ 内的元素为赢家，所以强制定向 $S$ 内的元素至不在 $S$ 内的元素，计算即可。

时间复杂度 $O(3^nn^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL MOD=1e9+7;
LL inv[2000005],a[15],n,dp[(1<<15)],cnt1,cnt2,p[15],q[15];
int main(){
	inv[1]=1;
	for(LL i=2;i<=2000000;++i)	inv[i]=MOD-(MOD/i)*inv[MOD%i]%MOD;
	scanf("%lld",&n);
	for(LL i=0;i<n;++i)	scanf("%lld",&a[i]);
	for(LL S=1;S<(1<<n);++S)
	{
		dp[S]=1;
		for(LL T=S&(S-1);T;T=S&(T-1))
		{
			LL Ts=T^S;
			cnt1=cnt2=0;
			for(LL i=0;i<n;++i)
			{
				if((T>>i)&1)	p[++cnt1]=i;
				if((Ts>>i)&1)	q[++cnt2]=i;
			}
			LL st=1;
			for(LL i=1;i<=cnt1;++i)	for(LL j=1;j<=cnt2;++j)	st=st*a[p[i]]%MOD*inv[a[p[i]]+a[q[j]]]%MOD;
			st=MOD-st;
			st=st*dp[T]%MOD;
			dp[S]=(dp[S]+st)%MOD;
		}
	}
	LL ans=0;
	for(LL S=1;S<(1<<n);++S)
	{
		cnt1=cnt2=0;
		for(LL i=0;i<n;++i)
		{
			if((S>>i)&1)	p[++cnt1]=i;
			else	q[++cnt2]=i;
		}
		LL st=1;
		for(LL i=1;i<=cnt1;++i)	for(LL j=1;j<=cnt2;++j)	st=st*a[p[i]]%MOD*inv[a[p[i]]+a[q[j]]]%MOD;
		ans=(ans+st*dp[S]%MOD*cnt1%MOD)%MOD;
	}
	printf("%lld",ans);
	return 0;
}
```

---

