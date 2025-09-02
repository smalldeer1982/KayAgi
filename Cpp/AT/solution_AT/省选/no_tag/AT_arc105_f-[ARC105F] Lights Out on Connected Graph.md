# [ARC105F] Lights Out on Connected Graph

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc105/tasks/arc105_f

$ 1 $ から $ N $ の番号がついた $ N $ 個の頂点と、$ 1 $ から $ M $ の番号がついた $ M $ 本の辺からなる無向グラフ $ G $ が与えられます。$ G $ は連結で、自己ループや多重辺が存在しないことが保証されます。 辺 $ i $ は頂点 $ a_i $ と頂点 $ b_i $ を双方向につなぐ辺です。 それぞれの辺は赤か青のどちらかの色で塗ることができます。はじめ、全ての辺は赤で塗られています。

$ G $ から $ 0 $ 本以上の辺を取り除き新しいグラフ $ G^{\prime} $ を作ることを考えます。 $ G^{\prime} $ としてありうるグラフは $ 2^M $ 通りありますが、これらのうちよいグラフ(後述)であるようなものの個数を $ 998244353 $ で割ったあまりを求めてください。

$ G^{\prime} $ が以下の条件の両方を満たすとき、$ G^{\prime} $ は *よいグラフ* であるといいます。

- $ G^{\prime} $ は連結
- 以下の操作を $ 0 $ 回以上繰り返すことで、全ての辺の色を青色にできる
  - 頂点を $ 1 $ つ選び、その頂点に接続する全ての辺の色を変化させる。すなわち、辺の色が赤ならば青へ、青ならば赤へ変化させる。

## 说明/提示

### 制約

- 与えられる入力は全て整数
- $ 1\ \leq\ N\ \leq\ 17 $
- $ N-1\ \leq\ M\ \leq\ N(N-1)/2 $
- $ G $ は連結で、自己ループや多重辺が存在しない

### Sample Explanation 1

\- 辺 $ 1 $、辺 $ 2 $ のどちらも取り除かない場合のみ条件を満たします。 - 例えば、頂点 $ 2 $ に対して操作を行うことで、全ての辺を青色にすることが可能です。 - それ以外の場合はグラフが非連結になるため、条件を満たしません。

### Sample Explanation 3

\- $ 998244353 $ で割ったあまりを求めるのを忘れずに。

## 样例 #1

### 输入

```
3 2
1 2
2 3```

### 输出

```
1```

## 样例 #2

### 输入

```
4 6
1 2
1 3
1 4
2 3
2 4
3 4```

### 输出

```
19```

## 样例 #3

### 输入

```
17 50
16 17
10 9
16 10
5 17
6 15
5 9
15 11
16 1
8 13
6 17
15 3
16 15
11 3
7 6
1 4
11 13
10 6
10 12
3 16
7 3
16 5
13 3
12 13
7 11
3 12
13 10
1 12
9 15
11 14
4 6
13 2
6 1
15 2
1 14
15 17
2 11
14 13
16 9
16 8
8 17
17 12
1 11
6 12
17 2
8 1
14 6
9 7
11 10
5 14
17 7```

### 输出

```
90625632```

# 题解

## 作者：Yansuan_HCl (赞：14)

好题。

## I. 染色

枚举边复杂度显然过高，考虑枚举点。在点上，二分图有个很好的性质：有且仅有二分图能进行黑白染色。对应地，一个**连通**图的黑白染色方案**一一对应**一个极大可行边（不使其有奇环——即连接异色点的边）集合。

遂考虑转化为对每个点集的每个染色方案计数。

## II. 连通？

连通很难限制，假设暂时放弃连通。设 $g(S)$ 表示点集 $S$ 所有染色方案对应的可行边方案数。可以枚举子集确定染色方案。若 $T \subseteq S$ 为黑点集，则对应的可行边方案数为 $\displaystyle 2^{cnt_S-cnt_T-cnt_{S \backslash T}}$，其中 $cnt_U$ 为点集 $U$ 内部连接的边数。

但是，我们仍需求出连通的方案数。考虑钦点在某个顺序下“第一个”连通块 $T$，只要让 $T$ 与剩下的点不连通，就可以减掉这些方案。这里可以设 $T$ 含有 $S$ 中标号最小的点。设 $f(S)$ 为连通点集 $S$ 的相应方案数，则有  $f(S)=g(S)-\sum_{t\subset s}f(T)g(S\backslash T)$。

于是本题就做完了。值得注意的是，黑白染色可以翻转，因此最后答案要除以 $2$。

```cpp
const int N = 17;
const ll P = 998244353;
int n, m, mat[N][N], s, S;
inline int lowbit(int x) { return x & -x; }
ll f[1 << N], g[1 << N], pw[N * N];
int cnt[1 << N];

int main() {
	pw[0] = 1;
	U (i, 1, N * N - 1) pw[i] = pw[i - 1] * 2 % P;

	rd(n, m);
	S = (1 << n);
	U (i, 1, m) {
		int u, v; rd(u, v);
		--u; --v;
		mat[u][v] = mat[v][u] = 1;
		for (s = 0; s < S; ++s) if (((s >> u) & 1) && ((s >> v) & 1))
			++cnt[s]; // 点集 s 的边数和
	}
	
	for (s = 0; s < S; ++s) {
		g[s] = 1; // 全白点
		for (int t = s; t; (--t) &= s)
			(g[s] += pw[cnt[s] - cnt[t] - cnt[s ^ t]]) %= P;
	}
	for (s = 0; s < S; ++s) {
		f[s] = g[s];
		for (int t = s; t; (--t) &= s) if (lowbit(s ^ t) > lowbit(t)) // 钦点 t 是含有标号最小的点的连通块
			(f[s] -= f[t] * g[s ^ t] % P - P) %= P;
	}
	printf("%lld", f[S - 1] * ((P + 1) >> 1) % P);
}
```

---

## 作者：冰雾 (赞：5)

这是一个爆标做法。

直接计算二分图并不好做，但是我们可以仿照有标号二分图计数，先计算双色图（将每个点染为黑白颜色中的一种，且同色点之间不连边的图）的个数。

我们记一般双色图的集合幂级数为 $F$，记连通双色图的集合幂级数为 $G$，
再记连通二分图的集合幂级数为 $H$，并定义乘法为子集卷积。

可以知道的是 $G=2H$，同时根据 $\exp$ 的组合意义，有 $\exp G=F$。

所以 $H=\frac{1}{2}\ln F$，那么现在只要求出 $F$，然后对 $F$ 做集合幂 $\ln$ 就可以了。

对于 $F$，我们可以先枚举点集 $T$，显然我们可以钦定一部分为黑色，补集为白色。记 $w(T)$ 为子集 $T$ 在原图中含有的边数，不难得到：

$$
F(T)=\sum_{P\cap Q=\emptyset ,P\cup Q=T}2^{w(T)-w(P)-w(Q)}
$$

于是可以先把 $2^{w(T)}$ 提出来，再对里面做子集卷积。

两部分的复杂度都是 $O(n^22^n)$ 的，那么总复杂度也是 $O(n^22^n)$ 的。

---

## 作者：SoyTony (赞：3)

可以转化成点集不变，选取图中一些边，求构成联通二分图的个数。

容易想到容斥，要除去不是二分图或不连通的方案数。后者可以套路容斥计算，考虑如何算不要求连通二分图个数，枚举点集 $S$，枚举左部点 $S_1$，令 $S_2=S\setminus S_1$，那么方案数是 $\prod_{i\in S_1} 2^{|T_i\cap S_2|}$，$T_i$ 是与 $i$ 连边的点集。考虑固定 $S_2$ 枚举 $S_1$，就是每次增加一个 $i$，答案好算，用 $f_S$ 表示。

注意到这里每个方案会被算 $2^{cnt}$ 次，$cnt$ 是连通块个数，且考虑了孤立点的情况。

之后容斥就是枚举 $1$ 所在连通块即可，最后答案要除以 $2$。

提交记录：[Submission - AtCoder](https://atcoder.jp/contests/arc105/submissions/44398561)

---

## 作者：jijidawang (赞：3)

跟 SoyTony 交流了一下好像确实不是很困难。

对于一个点集 $S$，考虑有多少种连边方案使得其为连通二分图。那么容斥一下需要排掉不连通和不是二分图的情况，对于不连通的情况，套路地枚举 1 号点所在连通块即可，所以只需要计算对于某个点集随便选边中二分图的数量。

枚举左部点 $S_1\subseteq S$，那么答案就是：
$$\prod_{i\in S_1}2^{|T_i\cap(S\setminus S_1)|}$$
其中 $T_i$ 是与 $i$ 有边的点的集合。

转为先枚举 $S\setminus S_1$，然后枚举 $S_1$，进而确定 $S=(S\setminus S_1)\cup S_1$。只需要考虑每次 $S_1$ 中增加一个元素的影响，这是容易计算的。

注意这种计算方法对于每种二分图会重复计算 $2^b$ 次，其中 $b$ 为连通块个数。而且考虑了孤立点的情况。

这个做法的时间复杂度为 $\Theta(3^n)$，可以通过。

[Submission](https://atcoder.jp/contests/arc105/submissions/44400607)。

---

## 作者：Purslane (赞：2)

# Solution

这种题都能被评为铜牌题吗……

一种明显的想法是：将点进行黑白染色，只保留黑色和白色之间的边。

如果最终图有 $k$ 个连通块，那么就会被算重 $2^k$ 次。考虑容斥。

设 $dp_S$ 表示，只保留 $S$ 中的点，有多少个联通二分子图。

显然可以通过自己枚举算出，不容斥之前的答案，记为 $f_S$。

考虑 $u$ 为 $S$ 中一个元素，则考虑 **$u$ 所在的极大连通块**，则有：

$$
dp_S = f_S - \sum_{u \in T,T \subset S} dp_T f_{S-T}
$$

除以二即得答案。

复杂度为 $O(3^n)$，无压力通过。

```cpp
#include<bits/stdc++.h>
#define int long long 
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=18,MOD=998244353;
int n,m,flg[MAXN][MAXN],f[1<<MAXN],g[1<<MAXN],ans[1<<MAXN],pre[1<<MAXN],pw[MAXN*MAXN];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	pw[0]=1; ffor(i,1,17*17) pw[i]=pw[i-1]*2%MOD;
	ffor(i,1,m) {int u,v;cin>>u>>v,flg[u][v]=flg[v][u]=1;}
	ffor(s,0,(1<<n)-1) ffor(u,1,n) ffor(v,u+1,n) if((s&(1<<u-1))&&(s&(1<<v-1))) pre[s]+=flg[u][v];
	f[0]=0;
	ffor(s,1,(1<<n)-1) {
		for(int S=s;S;S=(S-1)&s) f[s]=f[s]+pw[pre[s]-pre[S]-pre[s-S]];
		f[s]=(f[s]+1)%MOD;
	}
	ffor(s,1,(1<<n)-1) {
		g[s]=f[s];
		int ot=s-(s&-s);
		for(int S=ot;S;S=(S-1)&ot) g[s]=(g[s]-f[S]*g[s-S])%MOD;
	}
	ffor(s,0,(1<<n)-1) g[s]=g[s]*(MOD+1)/2%MOD;
	cout<<(g[(1<<n)-1]%MOD+MOD)%MOD;
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：2)

二分图有一个优良性质：可以对原图进行二染色。

直接染色会算重，考虑去掉联通的限制。

定义 $g(S)$ 为选的点的状态为 $S$ 的方案数，枚举子集得到颜色为 $1$ 的点，其它的点颜色为 $0$，不同颜色的边之间能随便选，相同颜色之间的边不能选。

接下来考虑联通的限制。

定义 $f(S)$ 为选的点的状态为 $S$ 的方案数。

考虑容斥。

通过枚举子集找到编号最小的点的所在的连通块，然后剩下的部分并不要求联通，因为我们是通过 $g(S)$ 来减的。然后因为子集和全集减去子集的集合中的点之间没有边，所以不会算重。

时间复杂度 $O(3^n)$。

---

## 作者：Mirasycle (赞：1)

两个约束条件：图联通和二分图。

考虑先满足第二个条件，并对于第一个条件进行容斥。

设 $h_s$ 表示集合 $s$ 为若干个二分图的方案数。对于每个集合 $s$，我们将其划分为不相交的两个集合 $s_1,s_2$，设两个集合之间的连边为 $c$ 个，那么就有 $2^c$ 种方案。对于所有划分求和即可。

不过上述求出来的有点小问题，就是一个有 $k$ 个联通块的图会被计算 $2^k$ 次。因为上述区分了黑白，一个联通块为一个二分图，可能左白右黑，也可能左黑右白是被统计了两次的。所以我们 **考虑在区分黑白的意义下进行统计。** 

设 $f_s$ 表示联通块 $s$ 在区分黑白的意义下连成二分图的方案数。

那么根据经典图联通容斥，我们只需要用总方案数减去钦定 “最小点”所在联通块联通其他点任意的方案数即可。

最后注意需要答案除以 $2$，因为我们上面说了在区分黑白的意义下。

时间复杂度 $O(3^n)$。

---

## 作者：Petit_Souris (赞：1)

有一点计数基础的朋友们都知道二分图计数的基本套路：考虑去数染色的方案数，那么如果有 $c$ 个连通块，就会算出 $2^c$ 种染色方案。

那么我们考虑去进行容斥，设 $f_{S}$ 表示点集 $S$ 连出一个连通二分图的染色方案数（也就是答案的两倍），枚举 $S$ 中编号最小的点所在的连通块点集进行容斥。

推一下这个容斥的系数，对于一个点集，如果求他的不同染色数量，那就相当于选择一个子集染黑，剩下的染成白色，之间的边随便选，有一个 $2^{|E|}$ 的系数。预处理出来点集内部的边数就行了，时间复杂度 $\mathcal O(2^nn^2+3^n)$。

这样看来学了一点 GF 之后的第二年，水平不算完全没有长进啊，至少会做典题了。感觉初三的时候我可能不会做这个题，唉唉。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=18,Mod=998244353;
ll n,m,X[N*N],Y[N*N],e[(1<<N)+9],f[(1<<N)+9],g[(1<<N)+9],pw2[N*N];
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    n=read(),m=read();
    rep(i,1,m)X[i]=read(),Y[i]=read();
    pw2[0]=1;
    rep(i,1,m)pw2[i]=pw2[i-1]*2%Mod;
    rep(i,0,(1<<n)-1){
        rep(j,1,m){
            if((i>>(X[j]-1))&1)e[i]+=((i>>(Y[j]-1))&1);
        }
    }
    rep(i,1,(1<<n)-1){
        for(ll j=i;;j=(j-1)&i){
            f[i]=(f[i]+pw2[e[i]-e[j]-e[j^i]])%Mod;
            if(!j)break;
        }
    }
    rep(i,1,(1<<n)-1){
        ll t=i^(i&(-i));
        g[i]=f[i];
        for(ll j=t;j;j=(j-1)&t)g[i]=(g[i]-f[j]*g[i^j]%Mod+Mod)%Mod;
    }
    write(g[(1<<n)-1]*(Mod+1)/2%Mod);
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

## 作者：云浅知处 (赞：1)

设 $f(S),g(S)$ 分别表示从点集 $S$ 内选边，得到一个连通/任意二分图的方案数，其集合幂级数为 $F,G$。自然地，有 $G=e^{F}$。

考虑怎么算 $g$，发现有一个自然的想法是，钦定每个点的颜色，然后异色边任选，同色边一定不能选。但这样会有问题，对于一个有 $x$ 个连通块的二分图，我们会将其计算 $2^x$ 次。

记这样算出来的值是 $h(S)$，其集合幂级数为 $H$。那么实际上，我们发现有 $H=e^{2F}$，因为每多一个连通块，方案数就会再乘 $2$。于是 $F=\ln \sqrt{H}=\frac{1}{2}\ln H$。

$H$ 可以用一遍子集卷积算出，综上所述，总复杂度 $O(N^22^N)$。

下面是 $O(3^N)$ 的代码，由于 $N\le 17$ 所以也可以通过。

```cpp
#include<bits/stdc++.h>

#define ll long long
#define mk make_pair
#define fi first
#define se second

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

const int mod=998244353;
int ksm(int x,ll y,int p=mod){
	int ans=1;y%=(p-1);
	for(int i=y;i;i>>=1,x=1ll*x*x%p)if(i&1)ans=1ll*ans*x%p;
	return ans%p;
}
int inv(int x,int p=mod){return ksm(x,p-2,p)%p;}
void add(int &x,int v){x+=v;if(x>=mod)x-=mod;}
int cmod(int x){if(x>=mod)x-=mod;return x;}

template<typename T>void cmax(T &x,T v){x=max(x,v);}
template<typename T>void cmin(T &x,T v){x=min(x,v);}

const int N=18;
int f[1<<N],h[1<<N],w[1<<N],p2[N*N],n,m;

void FMT(int *A,int k){
	for(int i=0;i<k;i++){
		for(int S=0;S<(1<<k);S++)if(S&(1<<i))add(A[S],A[S^(1<<i)]);
	}
}

signed main(void){

#ifndef ONLINE_JUDGE
	freopen("in.in","r",stdin);
#endif

	n=read(),m=read();
	for(int i=1;i<=m;i++){
		int u=read()-1,v=read()-1;
		w[(1<<u)|(1<<v)]++;
	}
	FMT(w,n);p2[0]=1;for(int i=1;i<=m;i++)p2[i]=cmod(p2[i-1]+p2[i-1]);
	for(int S=0;S<(1<<n);S++){
		for(int T=S;;T=(T-1)&S){
			add(h[S],p2[w[S]-w[T]-w[S^T]]);
			if(T==0)break;
		}
	}
	for(int S=1;S<(1<<n);S++)if(S&1){
		f[S]=h[S];
		for(int T=S;T;T=(T-1)&S)if((S^T)&1)add(f[S],mod-1ll*h[T]*f[S^T]%mod);
	}
	cout<<1ll*inv(2)*f[(1<<n)-1]%mod<<endl;

	return 0;
}


```

---

## 作者：daniEl_lElE (赞：1)

一个图是二分图当且仅当其所有连通块都是二分图。

考虑钦定一些点是白点，一些点是黑点。容易计算出它们之间的边数 $cnt$，那么方案数就是 $2^{cnt}$。

然而这样会有重复计算。具体地讲，如果一个图有 $k$ 个连通块且为二分图，那么会被算重 $2^k$。

考虑容斥，记 $g_i=\sum2^{cnt}$，对 $g$ 进行容斥，计算出 $h_i$ 表示连通情况下的方案数。钦定一个包含 $\operatorname{lowbit}(i)$ 的子集 $j$，并将 $h_i$ 扣减 $h_j\times g_{i\oplus j}$。

总复杂度 $O(2^nm+3^n)$，可以通过。

```cpp
#include <bits/stdc++.h>
#define int long long
#define lowbit(i) (i&(-i))
#define add(i,j) ((i+j>=mod)?i+j-mod:i+j)
using namespace std;
const int mod=998244353;
int f[150005],g[150005],h[150005],pw[10005];
signed main(){
	int n,m; cin>>n>>m;
	pw[0]=1; for(int i=1;i<=m;i++) pw[i]=pw[i-1]*2%mod;
	for(int i=1;i<=m;i++){
		int u,v; cin>>u>>v;
		for(int j=0;j<(1<<n);j++){
			if((j>>(u-1))&(j>>(v-1))&1){
				f[j]++; 
			}
		}
	}
	for(int i=1;i<(1<<n);i++){
		for(int j=i;;j=(j-1)&i){
			(g[i]+=pw[f[i]-f[j]-f[i^j]])%=mod;
			if(!j) break;
		}
//		cout<<i<<" "<<g[i]<<"\n";
	}
	for(int i=1;i<(1<<n);i++){
		h[i]=g[i];
		int p=i-lowbit(i);
		for(int j=p;j;j=(j-1)&p){
			(h[i]+=mod-h[i^j]*g[j]%mod)%=mod;
		}
//		cout<<i<<" "<<h[i]<<"\n";
	}
	cout<<(h[(1<<n)-1]*(mod+1)/2)%mod;
	return 0;
}
```

---

## 作者：OrinLoong (赞：0)

## ATR105F_1 熄灯连通图 学习笔记
[Luogu Link](https://www.luogu.com.cn/problem/AT_arc105_f)

### 题意简述
给定一个 $n$ 点 $m$ 边的简单无向图 $G$。问有多少种 $E'\subset E$，满足 $G={V,E'}$ 为连通的二分图。

$n\le 17$。

### 做法解析
本题有两个约束条件：“连通”和“二分图”。“连通”好处理，采用经典的正难则反（见 ATB213G），此不赘述。考虑怎么让我们统计上的图都是二分图，也就是怎么算 $F_S$——只考虑点集 $S$ 时二分图（无论连通与否）的个数。

其实很好办：一个二分图的点集必然可以被黑白染色成一个黑点集和一个白点集，我们就来枚举 $S$ 的黑色点集 $T$。即有：$F_S=\sum_{T\subset S}2^{\text{ecnt}_{T\to S-T}}$。

然后这题就做完了。

### 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
using namespace obasic;
using namespace omodint;
using mint=M998;
const int MaxN=17,MaxNr=3e2,MaxA=1<<17;
int N,M,alf,Gr[MaxN],X,Y,lg2[MaxA],ecn[MaxA];
void addudge(int u,int v){Gr[u]|=(1<<v),Gr[v]|=(1<<u);}
int lowbit(int x){return x&(-x);}
mint pw2[MaxNr],f[MaxA],g[MaxA];
int main(){
    readi(N),readi(M),alf=(1<<N)-1;
    for(int i=2;i<=alf;i<<=1)lg2[i]=lg2[i/2]+1;
    pw2[0]=1;for(int i=1;i<=M;i++)pw2[i]=pw2[i-1]*2;
    for(int i=1;i<=M;i++)readi(X),readi(Y),addudge(X-1,Y-1);
    for(int s=1;s<=alf;s++){
        int l=lowbit(s),u=lg2[l],t=s-l;ecn[s]=ecn[t];
        for(int i=0;i<N;i++)if(t&(1<<i)&&(Gr[u]&(1<<i)))ecn[s]++;
    }
    for(int s=0;s<=alf;s++){
        for(int t=s;;t=(t-1)&s){
            g[s]+=pw2[ecn[s]-ecn[t]-ecn[s-t]];
            if(!t)break;
        }
    }
    for(int s=0;s<=alf;s++){
        int l=lowbit(s);f[s]=g[s];
        for(int t=(s-1)&s;t;t=(t-1)&s)if(t&l)f[s]-=f[t]*g[s-t];
    }
    writi(miti(f[alf]/2));
    return 0;
}
```

### 反思总结
见到无向图连通性状压计数，就正难则反处理连通性问题；看到二分图，想黑白染色！

---

## 作者：小超手123 (赞：0)

### 题意：

有一张 $n$ 个点 $m$ 条边的简单无向图，问选出一个边集，使得 $n$ 个点与这些边构成的图连通，并且图是二分图的方案数。

### 分析：

**有且仅有二分图**可以进行黑白染色（每条边的两个点必须是不同的颜色）。

但是连通这个条件不好处理。考虑容斥计算。

记 $g(S)$ 表示所有 $G'=(S,E'),E' \in E$ 的图的黑白染色方案（不要求 $G'$ 必须连通）。

 $f(S)$ 表示所有 $G'=(S,E'),E' \in E$ 的图的黑白染色方案（要求 $G'$ 必须连通）。

$g(S)$ 很好计算：
$$
g(S) = \sum_{T \in S}2^{cnt_{S}-cnt_{T}-cnt_{S \setminus T}}
$$
$cnt_{S}$ 表示包含于点集 $S$ 的边的个数。

计算连通的方案数有个经典的方法：

容斥计算不连通的方案数量，记 $x = min(S)$。枚举 $x$ 所属的连通块 $T$。那么：
$$
f(S) =g(S)-\sum_{T \in S,T \ne S,T \ne 0,x \in T} f(T) \times g(S \setminus T)
$$
由于连通二分图的黑白染色方案为 $2$，最后答案即为 $\frac{f(2^{n}-1)}{2}$。

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 1000006
#define mod 998244353
using namespace std;
int n, m, Pow[410];
int cnt[N];
int f[N], g[N]; 
int lowbit(int x) {
	return x & (-x);
}
int ksm(int a, int n) {
	if(n == 0) return 1;
	if(n == 1) return a % mod;
	int x = ksm(a, n / 2);
	if(n % 2 == 0) return x * x % mod;
	else return x * x % mod * a % mod;
}
signed main() {
	//ios::sync_with_stdio(false);
	//cin.tie(0); cout.tie(0);
	Pow[0] = 1;
	for(int i = 1; i <= 400; i++) Pow[i] = Pow[i - 1] * 2 % mod;
	cin >> n >> m;
	for(int i = 1, u, v; i <= m; i++) {
		cin >> u >> v;
		for(int S = 1; S < (1 << n); S++)
			if((S & (1 << (u - 1))) && (S & (1 << (v - 1))))
				cnt[S]++;
	}
	for(int i = 1; i < (1 << n); i++) {
		g[i] = 1;
		for(int j = i; j; j = (j - 1) & i)
			g[i] = (g[i] + Pow[cnt[i] - cnt[j] - cnt[i ^ j]]) % mod;
	}
	//cout << "e";
	for(int S = 1; S < (1 << n); S++) {
		f[S] = g[S];
		for(int T = S; T; T = (T - 1) & S) {
			if(T == S) continue;
			if(lowbit(S) == lowbit(T)) f[S] = (f[S] - f[T] * g[S ^ T] % mod + mod) % mod;
		}
	}
	cout << f[(1 << n) - 1] * ksm(2, mod - 2) % mod;
	return 0;
}
```



---

## 作者：User_Unauthorized (赞：0)

## 题意

给定一个 $N$ 个点 $M$ 条边的简单无向联通图 $G$。每个边有红和蓝两种颜色，初始时每条边均是红色。

现在通过移除 $G$ 中的一些边来获得一个新的无向图 $G^{\prime}$，求在所有的 $2^M$ 种方案中有多少种方案可以使得 $G^{\prime}$ 满足如下条件：

- $G^{\prime}$ 是联通图
- 通过采取如下操作可以使得所有的边变为蓝色：

    - 选择一个点 $u$，将与 $u$ 相邻的所有边变为蓝色

对 $998244353$ 取模。

- $1 \le N \le 17$
- $N - 1 \le M \le \frac{N\left(N - 1\right)}{2}$

## 题解

首先我们可以发现，符合要求的子图 $G^\prime$ 一定是二分图。

发现联通的要求很难满足，故考虑先计算不考虑联通限制下的答案。

设 $g(S)$ 表示仅考虑与点集 $S$ 相关的边，求使得图为二分图但不要求联通的方案数。

考虑对图进行黑白染色，通过枚举白色点集合 $T$ 可以完成计算：

$$g(S) = \sum\limits_{T \subseteq S} 2^{\operatorname{count}_{S} - \operatorname{count}_{T} - \operatorname{count}_{S \setminus T}}$$

其中 $\operatorname{count}_{S}$ 表示与点集 $S$ 相关的边的数量。可以发现上式中的指数项即连接黑色点和白色点的边的数量。

$\operatorname{count}_{S}$ 的值可以在通过对每个点集枚举所有边来实现，这里不多赘述。

下面考虑如何计算联通的方案数。

设 $f(S)$ 表示仅考虑与点集 $S$ 相关的边，求使得图为二分图且要求联通的方案数。

可以发现 $f(S)$ 中包含的方案实际上是 $g(S)$ 中去除了不联通的方案，因此可以考虑枚举出所有不联通的方案。

若不联通，那么图一定具有至少两个联通块，那么我们可以枚举 $S$ 中编号最小的点所在的联通块，然后枚举该联通块中的点集 $T$，那么 $S \setminus T$ 的连通性是没有限制。设 $u = \min\limits_{x \in S} x$，即点集 $S$ 中的最小元素，那么有转移

$$f(S) = g(S) - \sum\limits_{T \subset S \land u \in T} f(T) \times g(S \setminus T)$$

时间复杂度 $O(3^N + 2^NM)$，空间复杂度 $O(2^N + M)$，可以通过。

## Code

```cpp
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;
typedef std::pair<valueType, valueType> ValuePair;
typedef std::vector<ValuePair> PairVector;

namespace MODINT {
    constexpr valueType MOD = 998244353;

    template<typename T1, typename T2, typename T3 = valueType>
    void Inc(T1 &a, T2 b, const T3 &mod = MOD) {
        a = a + b;

        if (a >= mod)
            a -= mod;
    }

    template<typename T1, typename T2, typename T3 = valueType>
    void Dec(T1 &a, T2 b, const T3 &mod = MOD) {
        a = a - b;

        if (a < 0)
            a += mod;
    }

    template<typename T1, typename T2, typename T3 = valueType>
    T1 sum(T1 a, T2 b, const T3 &mod = MOD) {
        return a + b >= mod ? a + b - mod : a + b;
    }

    template<typename T1, typename T2, typename T3 = valueType>
    T1 sub(T1 a, T2 b, const T3 &mod = MOD) {
        return a - b < 0 ? a - b + mod : a - b;
    }

    template<typename T1, typename T2, typename T3 = valueType>
    T1 mul(T1 a, T2 b, const T3 &mod = MOD) {
        return (long long) a * b % mod;
    }

    template<typename T1, typename T2, typename T3 = valueType>
    void Mul(T1 &a, T2 b, const T3 &mod = MOD) {
        a = (long long) a * b % mod;
    }

    template<typename T1, typename T2, typename T3 = valueType>
    T1 pow(T1 a, T2 b, const T3 &mod = MOD) {
        T1 result = 1;

        while (b > 0) {
            if (b & 1)
                Mul(result, a, mod);

            Mul(a, a, mod);
            b = b >> 1;
        }

        return result;
    }

    constexpr valueType Inv2 = (MOD + 1) / 2;
}// namespace MODINT

using namespace MODINT;

bool check(valueType x, valueType k) {
    return x & (1 << (k - 1));
}

valueType lowBit(valueType n) {
    return n & -n;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType N, M;

    std::cin >> N >> M;

    PairVector edges(M);

    for (auto &iter : edges)
        std::cin >> iter.first >> iter.second;

    valueType const S = 1 << N;

    ValueVector count(S, 0);

    for (valueType s = 0; s < S; ++s) {
        for (valueType i = 0; i < M; ++i) {
            auto [u, v] = edges[i];

            if (check(s, u) && check(s, v))
                Inc(count[s], 1);
        }
    }

    ValueVector G(S, 0), F(S, 0);

    for (valueType s = 0; s < S; ++s) {
        G[s] = 1;

        for (valueType t = s; t > 0; t = (t - 1) & s)
            Inc(G[s], pow(2, count[s] - count[t] - count[s ^ t]));
    }

    for (valueType s = 0; s < S; ++s) {
        F[s] = G[s];

        for (valueType t = s; t > 0; t = (t - 1) & s)
            if (lowBit(t) < lowBit(s ^ t))
                Dec(F[s], mul(F[t], G[s ^ t]));
    }

    std::cout << mul(F[S - 1], Inv2) << std::endl;

    return 0;
}
```

---

## 作者：intel_core (赞：0)

注意到如果图联通，钦定一个点的颜色之后一种选边的方案与染色方案是一一对应的。

对于每个点集 $S$，我们先维护出 $e_S$ 表示 $S$ 的支撑子图上边的条数。

考虑计算 $f_S$ 表示在 $S$ 中的点的支撑子图上选边，且要求选出的边建出的新图仍然联通的选边方案数。$g_S$ 表示在 $S$ 中的点的支撑子图上选边，对于每一种方案，对 $2^{cnt}$ 求和，其中 $cnt$ 表示新图的连通块个数。

由 $g_S$ 的定义，我们可以很快得到 $g_S=\frac{\sum_{i \subseteq S}2^{e_s-e_i-e_{s \oplus i}}}{2}$。

再考虑计算 $g_S-f_S$，也就是新图不连通时的情况。我们先枚举一个包含 $S$ 中一个定点的点集 $i$，并要求新图中 $i$ 必须联通；此时对 $g_S-f_S$ 的贡献就是 $2\times f_i\times g_{s\oplus i}$。这个式子相当于我们取出了不连通方案中若干个连通块中的第一个。

对于每个 $S$ ，直接枚举子集计算 $f_S,g_S$ 即可。复杂度 $O(3^n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int NR=150;
const int MOD=998244353;
int n,m,x[NR],y[NR],cnt[1<<17],f[1<<17],g[1<<17],pw[NR];
void add(int &x,int y){x=(x+y)%MOD;}

signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++)
		cin>>x[i]>>y[i],cnt[(1<<(x[i]-1))|(1<<(y[i]-1))]++;
	pw[0]=1;
	for(int i=1;i<=m;i++)pw[i]=pw[i-1]*2%MOD;
	for(int i=1;i<=n;i++)
		for(int s=0;s<(1<<n);s++)
			if(!((s>>(i-1))&1))cnt[s|(1<<(i-1))]+=cnt[s];
	f[0]=g[0]=1;
	for(int s=1;s<(1<<n);s++){
		int tmp=0;
		for(int i=s;i>(s^i);i=(i-1)&s)add(tmp,2*f[i]*g[s^i]%MOD);
		for(int i=s;i>(s^i);i=(i-1)&s){
			add(g[s],pw[cnt[s]-cnt[i]-cnt[i^s]]); 
			if(!i)break;
		}
		f[s]=(g[s]-tmp)%MOD;
	}
	cout<<(f[(1<<n)-1]+MOD)%MOD<<endl; 
	return 0; 
}
```

---

