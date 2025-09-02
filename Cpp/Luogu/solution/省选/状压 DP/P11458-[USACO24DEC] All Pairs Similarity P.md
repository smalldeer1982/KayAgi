# [USACO24DEC] All Pairs Similarity P

## 题目描述

**注意：本题的内存限制为 512MB，通常限制的 2 倍。**

Farmer John 的 $N$（$1\le N\le 5\cdot 10^5$）头奶牛都被分配了一个长度为 $K$ 的非全零位串（$1\le K\le 20$）。不同的奶牛可能被分配到相同的位串。

两个位串的 Jaccard 相似度定义为它们的按位与的结果中 $\texttt{1}$ 的数量除以它们的按位或的结果中 $\texttt{1}$ 的数量。例如，位串 $\texttt{11001}$ 和 $\texttt{11010}$ 的 Jaccard 相似度为 $2/4$。

对于每头奶牛，输出她的位串与每头奶牛（包括她自己）的位串的 Jaccard 相似度之和，对 $10^9+7$ 取模。具体地说，如果总和等于一个有理数 $a/b$，其中 $a$ 和 $b$ 是互质的整数，则输出范围 $[0,10^9+7)$ 内的唯一整数 $x$，使得 $bx-a$ 被 $10^9+7$ 整除。

## 说明/提示

奶牛们分配到了以下的位串：$[\texttt{01}, \texttt{01}, \texttt{10}, \texttt{11}]$。

对于第一头奶牛，总和为 $\text{sim}(1,1)+\text{sim}(1,1)+\text{sim}(1,2)+\text{sim}(1,3)=1+1+0+1/2\equiv 500000006\pmod{10^9+7}$。

第二头奶牛的位串与第一头奶牛相同，所以她的总和也与第一头奶牛相同。

对于第三头奶牛，总和为 $\text{sim}(2,1)+\text{sim}(2,1)+\text{sim}(2,2)+\text{sim}(2,3)=0+0+1+1/2\equiv 500000005\pmod{10^9+7}$。

- 测试点 $2\sim 15$：对于每一个 $K\in \{10,15,16,17,18,19,20\}$ 有两个测试点。

## 样例 #1

### 输入

```
4 2
1
1
2
3```

### 输出

```
500000006
500000006
500000005
500000006```

# 题解

## 作者：min_inf (赞：25)

来点神秘做法。

首先有 $\frac{|S \cap T|}{|S \cup T|}=\frac{|S|+|T|}{|S \cup T|}-1$。每个位置的答案就是 $|a_i|\sum\frac{1}{|a_i \cup a_j|}+\sum\frac{|a_j|}{|a_i \cup a_j|}-n$。两部分可以用差不多的方法算，这里就只考虑第一部分。

如果求所有 $\sum\frac{1}{|a_i \cup a_j|}$ 的和，显然可以将出现次数数组和自己做 FWT。然后考虑把一边看作常数，另一边每个位置对答案的贡献是一个常数（也就是把转移画成 DAG 的形式，每条边有一个常数边权，这个就是所有路径权值积的和），然后发现我们要求的就是这个。

然后统计路径权值和正着和倒着是一样的，所以我们把这个 FWT 整个倒过来写就行了。时间复杂度 $O(n+k2^k)$。

```cpp
cin>>n>>k;
rep(i,1,n)cin>>a[i],++cnt[a[i]];
repn(S,1<<k)if(S)f[S]=Z(1)/popcnt(S);
repn(i,k)repn(S,1<<k)if(S>>i&1)f[S^(1<<i)]-=f[S];
repn(S,1<<k)scnt[S]=cnt[S],ssum[S]=cnt[S]*popcnt(S);
repn(i,k)repn(S,1<<k)if(S>>i&1)scnt[S]+=scnt[S^(1<<i)],ssum[S]+=ssum[S^(1<<i)];
repn(S,1<<k)g[S]=f[S]*ssum[S],f[S]*=scnt[S];
repn(i,k)repn(S,1<<k)if(S>>i&1)f[S^(1<<i)]+=f[S],g[S^(1<<i)]+=g[S];
repn(S,1<<k)res[S]=f[S]*popcnt(S)+g[S]-n;
rep(i,1,n)cout<<res[a[i]].val()<<'\n';
```

---

## 作者：spdarkle (赞：7)

先看一点基本推导。

## $f_S=\sum_Tg_{S\cap T}h_T$

$$
\begin{aligned}
f_S&=\sum_Tg_{S\cap T}h_T\\
&=\sum_{T\subseteq S}g_{T}\sum_{I}[I\cap S=T]h_I\\
&=\sum_{T\subseteq S}g_{T}\sum_{I}h_I\sum_{T\subseteq N\subseteq I\cap S}(-1)^{|N|-|T|}\\
&=\sum_{N\subseteq S}(-1)^{|N|}\sum_{T\subseteq N}g_T(-1)^{|T|}\sum_{S\subseteq I}h_I\\
&=\sum_{N\subseteq S}(-1)^{|N|}\left(\sum_{T\subseteq N}g_T(-1)^{|T|}\right)\left(\sum_{N\subseteq I}h_I \right)
\end{aligned}
$$

## $f_S=\sum_{T}g_{S\cup T}h_T$

$$
\begin{aligned}
f_S&=\sum_{T}g_{S\cup T}h_T\\
&=\sum_{S\subseteq T}g_T\sum_{I\subseteq T}[S\cup I=T]h_I\\
&=\sum_{S\subseteq T}g_T\sum_{I\subseteq T}h_I\sum_{S\cup I\subseteq N\subseteq T}(-1)^{|T|-|N|}\\
&=\sum_{S\subseteq N}(-1)^{|N|}\sum_{I\subseteq N}h_I\sum_{N\subseteq T}g_T(-1)^{|T|}
\end{aligned}
$$



## $f_S=\sum_{T}g_{S\cap T}h_{S\cup T}$

$$
\begin{aligned}
f_S&=\sum_{T}g_{S\cap T}h_{S\cup T}\\
&=\sum_{T\subseteq S}g_{T}\sum_{S\subseteq I}h_I
\end{aligned}
$$

## 正题

回到正题，我们需要计算的是：

$$
f_S=\sum_{T}\frac{|S\cap T|}{|S\cup T|}cnt_T
$$

而 $|S\cap T|=|S|+|T|-|S\cup T|$。

拆开后相当于计算两个东西：

$$
\sum_{T}\frac{|T|cnt_T}{|S\cup T|}
$$

以及 

$$
|S|\sum_{T}\frac{1}{|S\cup T|}
$$

这在第二个情形里有讨论，带入即可。

---

## 作者：luoguhandongheng (赞：6)

极其优雅的转置原理。

对于第 $i$ 头奶牛，要求的答案为 $\sum_{1\le j\le n}{{|A_i \cap A_j|} \over {|A_i \cup A_j|}}=\sum_{1\le j\le n}{{|A_i|+|A_j|} \over {|A_i \cup A_j|}}-n=|A_i|\sum_{1\le j\le n}{1 \over {|A_i \cup A_j|}}+\sum_{1\le j\le n}{{|A_j|} \over {|A_i \cup A_j|}}-n$。

先考虑求 $\sum_{1\le j\le n}{1 \over {|A_i \cup A_j|}}$。令 $a_j = |\set{1\le x\le n|A_x=j}|$，$b_k=\frac{1}{|k|}$。只要求出 $c_i = \sum_{i \cup j =k} a_j \times b_{k}$，那么所求即为 $c_{A_i}$。

把 $a$ 视为常量，**观察到 $c_i = \sum a_j \times b_{i \cup j}$ 的转置为 $b_{i \cup j}= \sum a_j \times c_i$**，直接卷积。然后再套用“机械”的办法，把 FWT 倒序，倍加操作互换即可。注意由于 $a$ 是常量，不需要变动。

求 $\sum_{1\le j\le n}{{|A_j|} \over {|A_i \cup A_j|}}$ 类似，只需要把 $a_j$ 的定义稍改一下即可。

[Elegant Code.](https://www.luogu.com.cn/record/206752614)

复杂度 $O(n+ k\times 2^k)$。

---

## 作者：yuanruiqi (赞：6)

题意：$\forall i\in[1,n],ans_i=\sum_{j=1}^n\frac{|a_i\cap a_j|}{|a_i\cup a_j|}$。

问题核心是处理分数的贡献，首先它关于分子是线性的，所以考虑枚举数位 $i$ 并只保留满足第 $i$ 位为 $1$ 的数，如下做 $k$ 遍。

接下来就只要求 $\sum_{j=1}^n\frac{1}{|a_i\cup a_j|}$ 了。补集转化，令 $b_i$ 为 $a_i$ 按位取反的结果，可以等价的求 $\sum_{j=1}^n\frac{1}{k-|b_i\cap b_j|}$。令 $g(i)=\frac{1}{k-i}$，考虑容斥原理，拆成 $g(|b|)=\sum_{s\subset b}h(|s|)$。其中 $h$ 为容斥系数，并满足 $g(i)=\sum_{j=0}^{i}\binom{i}{j}h(j)$，所以 $h$ 可以通过 DP 预处理出来。

对于一个 $b_i$，令所有满足 $s\sub b_i$ 的 $f(s)$ 加上 $h(|s|)$。容易发现 $b_j$ 对 $ans_i$ 的贡献恰好为 $\sum_{s\subset b_i} f(s)$。于是可以利用高位前缀和做到单次复杂度 $O(k2^k)$。最终得到总复杂度 $O(n+k^22^k)$ 的做法。

阅读官方题解后发现遗漏了关键性质：$\frac{|a\cap b|}{|a\cup b|}=\frac{|a|}{|a\cup b|}+\frac{|b|}{|a\cup b|}-1$，利用这个性质，可以去掉第一步的枚举数位，优化到时间复杂度 $O(k2^k)$，空间复杂度 $O(2^k)$。

---

## 作者：qczrz6v4nhp6u (赞：5)

简单题啊，为啥我去年不会呢？

### Solution

首先 $\frac{|x\cap y|}{|x\cup y|}=\frac{|x|+|y|}{|x\cup y|}-1$，于是原题即求 $|a_i|\sum_j\frac{1}{|a_i\cup a_j|}+\sum_j\frac{|a_j|}{|a_i\cup a_j|}-n$。

这个分数看起来是没啥有用的性质的，我们直接将原问题强化为如下问题：

> 给定集合幂级数 $f,g$，$\forall S\subseteq U=\{0,1,\cdots,k-1\}$ 求 $h_S=\sum\limits_{T\subseteq U}f_Tg_{S\cup T}$。

考虑容斥掉 $S\cup T$ 的限制。进行一点简单的推导：

$$\begin{aligned}
h_S&=\sum_{T\subseteq U}f_Tg_{S\cup T}\\
&=\sum_{S\subseteq R}g_R\sum_{T\subseteq R}f_T[S\cup T=R]\\
&=\sum_{S\subseteq R}g_R\sum_{T\subseteq R}f_T\sum_{P\subseteq R}(-1)^{|R|-|P|}[S\cup T\subseteq P]\\
&=\sum_{S\subseteq R}g_R\sum_{T\subseteq R}f_T\sum_{P\subseteq R}(-1)^{|R|-|P|}[S\subseteq P][T\subseteq P]\\
&=\sum_{S\subseteq P}\Big(\sum_{P\subseteq R}(-1)^{|R|-|P|}g_R\Big)\Big(\sum_{T\subseteq P}f_T\Big)
\end{aligned}$$

这些都是可以直接算的，复杂度 $O(k2^k)$。

### Code

```cpp
bool Mst;
#include<bits/stdc++.h>
using namespace std;
using ui=unsigned int;
using ll=long long;
using ull=unsigned long long;
using i128=__int128;
using u128=__uint128_t;
using pii=pair<int,int>;
#define fi first
#define se second
#define popc __builtin_popcount
constexpr int N=5e5+5,M=20,mod=1e9+7;
inline ll add(ll x,ll y){return (x+=y)>=mod&&(x-=mod),x;}
inline ll Add(ll &x,ll y){return x=add(x,y);}
inline ll sub(ll x,ll y){return (x-=y)<0&&(x+=mod),x;}
inline ll Sub(ll &x,ll y){return x=sub(x,y);}
inline ll qpow(ll a,ll b){
	ll res=1;
	for(;b;b>>=1,a=a*a%mod)
		if(b&1)res=res*a%mod;
	return res;
}
int n,m,U,a[N];ll inv[M+1],f[1<<M],g[1<<M],h[1<<M],ans1[1<<M],ans2[1<<M];
inline void PreSum(ll *f){
	for(int i=1;i<=U;i<<=1)
		for(int j=0;j<=U;j+=i<<1)
			for(int k=0;k<i;k++)
				Add(f[i|j|k],f[j|k]);
}
inline void PreDif(ll *f){
	for(int i=1;i<=U;i<<=1)
		for(int j=0;j<=U;j+=i<<1)
			for(int k=0;k<i;k++)
				Sub(f[i|j|k],f[j|k]);
}
inline void SufSum(ll *f){
	for(int i=1;i<=U;i<<=1)
		for(int j=0;j<=U;j+=i<<1)
			for(int k=0;k<i;k++)
				Add(f[j|k],f[i|j|k]);
}
inline void SufDif(ll *f){
	for(int i=1;i<=U;i<<=1)
		for(int j=0;j<=U;j+=i<<1)
			for(int k=0;k<i;k++)
				Sub(f[j|k],f[i|j|k]);
}
inline void work(const ll *f,const ll *g,ll *h){
	static ll F[1<<M],G[1<<M];
	for(int i=0;i<=U;i++)F[i]=f[i];
	for(int i=0;i<=U;i++)G[i]=g[i];
	PreSum(F),SufDif(G);
	for(int i=0;i<=U;i++)F[i]=F[i]*G[i]%mod;
	SufSum(F);
	for(int i=0;i<=U;i++)h[i]=F[i];
}
bool Med;
int main(){
	cerr<<abs(&Mst-&Med)/1048576.0<<endl;
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m,U=(1<<m)-1;
	inv[1]=1;
	for(int i=2;i<=m;i++)inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	for(int i=1;i<=n;i++)cin>>a[i],++f[a[i]],g[a[i]]+=popc(a[i]);
	for(int i=0;i<=U;i++)h[i]=inv[popc(i)];
	work(f,h,ans1),work(g,h,ans2);
	for(int i=1;i<=n;i++)cout<<sub(add(popc(a[i])*ans1[a[i]]%mod,ans2[a[i]]),n)<<'\n';
	return 0;
}
```

---

## 作者：irris (赞：5)

> 不需要使用注意力，不需要设计容斥系数，不需要转置原理，复杂度还一样是目前最优的题解！

#### P11458 [USACO24DEC] All Pairs Similarity P

> 给出 $n$ 个 $k$ 位二进制数 $a_1, \ldots, a_n$，你需要对 $1 \leq i \leq n$ 求 $\sum_{j=1}^n \frac{\operatorname{pop}(a_i\;\&\;a_j)}{\operatorname{pop}(a_i\;|\;a_j)}$。$1 \leq n \leq 5\cdot 10^5$，$1 \leq k \leq 20$，2 秒 / 512 MB。

首先 $\sum\limits_{j=1}^n \frac{P(a_i\&a_j)}{P(a_i|a_j)} = P(a_i)\sum\limits_{j=1}^n \frac{1}{P(a_i|a_j)} + \sum\limits_{j=1}^n \frac{P(a_j)}{P(a_i|a_j)} - n$。

搞笑 $\mathcal O(n + 2^k k^2)$ 做法：考虑对于每个 $0 \leq s \leq k$ 求出有多少个 $P(a_i|a_j) = s$（同样还要求出 $\sum P(a_j)[P(a_i|a_j) = s]$，但是方法是相同的）。一个肯定能算重的做法是，先让 $b_k = \sum_j [a_j = k]$，对 $b$ 先做高维后缀和，保留 $\operatorname{popcount}$ 恰好为 $s$ 的元素后，再做高维前缀和，在 $x$ 处统计答案。但是可以反演。

$$ \begin{aligned} g_i &= \sum_{j=0}^i {k-j \choose i-j} f_j \\ g_i \cdot (k-i)! &= \sum_{j=0}^i \frac{f_j \cdot (k-j)!}{(i-j)!} \\ \\ G(x) &= F(x) \cdot e^x \\ F(x) &= G(x) \cdot e^{-x} \\ \\ f_i \cdot (k-i)! &= \sum_{j=0}^i g_j \cdot (k-j)! \cdot \frac{(-1)^{i-j}}{(i-j)!} \\ f_i &= \sum_{j=0}^i (-1)^{i-j} {k-j \choose i-j} g_j \end{aligned} $$

其实复杂度不变，但是给了我们一点可以 NTT 的理性愉悦。

现在考虑怎么做到 $\mathcal O(n + 2^kk)$，大概不能对每个 $s$ 拆分来做而是要整体做了。这里考虑直接容斥，换句话说

$$\begin{aligned} f_x &= \sum_y \sum_S [(x\;|\;y) = S]c_y \cdot \frac{1}{P(S)}\\ &= \sum_y c_y \sum_T [(x\;|\;y) \subseteq T] \sum_{T \subseteq S} (-1)^{\lvert S\rvert - \lvert T\rvert}\frac{1}{P(S)} \end{aligned} $$

对每个 $T$ 求出 $w_T$ 表示 $\sum_{T \subseteq S} (-1)^{\lvert S\rvert - \lvert T\rvert} \frac{1}{P(S)}$，高维后缀和即可；随后先将 $c_y$ 做高维前缀和，然后点乘 $w$，最后做高维前缀和即得到 $f$（remark：这是因为 $[(x\;|\;y) \subseteq T] = [x \subseteq T][y \subseteq T]$）。

```cpp
int main() {
	int n = read<int>(), k = read<int>(), z = (1 << k);
	for (int i = 0; i < z; ++i) 
		pop[i] = __builtin_popcount(i);
	for (int j = 1; j <= k; ++j) 	
		iv[j] = modint(j).inverse();
	for (int i = 1; i <= n; ++i) {
		x[i] = read<int>();
		c[x[i]] += 1, d[x[i]] += pop[x[i]];
	}
	for (int j = 1; j < z; ++j) 
		w[j] = modint(pop[j] & 1 ? -1 : 1) * iv[pop[j]];
	for (int i = 0; i < k; ++i) 
		for (int j = 0; j < z; ++j) if ((j >> i) & 1)
			w[j ^ (1 << i)] += w[j];
	for (int j = 0; j < z; ++j) 
		w[j] *= modint(pop[j] & 1 ? -1 : 1);
	auto process = [&](modint c[], modint w[]) -> void {
		for (int i = 0; i < k; ++i) 
			for (int j = 0; j < z; ++j) if ((j >> i) & 1) 
				c[j] += c[j ^ (1 << i)];
		for (int j = 0; j < z; ++j) 
			c[j] *= w[j];
		for (int i = 0; i < k; ++i) 
			for (int j = 0; j < z; ++j) if ((j >> i) & 1) 
				c[j ^ (1 << i)] += c[j];
	};
	process(c, w), process(d, w); 
	for (int i = 1; i <= n; ++i) 
		print<int>((modint(pop[x[i]]) * c[x[i]] + d[x[i]] - n).get(), '\n');
	return 0;
}
```

---

## 作者：Petit_Souris (赞：5)

来个逆天做法。先报复杂度：$\mathcal O(n2^{\frac{k}{2}})$。

考虑将所有二进制位分成两半，下面我们称他们为**高位**和**低位**。设查询的是 $x$，另一个数是 $y$。我们的主要思路是：

- 预处理 $y$ 的高位为 $y_0$ 时，所有 $x$ 的低位 $x_1$ 的答案。

- 查询 $x$ 时，枚举高位 $y_0$，直接调用 $x_1$ 的答案。

预处理的方法很简单：首先高位确定后，只有高位的 or / and 的 popcount 有用了，因此只需要算 $f_{y_0}(x_1,a,b)$ 表示高位 $y_0$ 的前提下，低位 $x_1$，高位的 or / and 的 popcount 分别为 $a,b$ 时的答案之和。进一步观察到最后只是做了 $\frac{a}{b}\to \frac{a+c}{b+d}$ 这样一件事情，那么 $c$ 可以在贡献中乘掉，记录 $d$ 一维就行了。

也就是说，现在要预处理出高位 $y_0$ 的 $y$ 与所有 $x_1$ 的 $(c,d)$ 元组。这个直接暴力做就行了，把非零位置拿出来两两计算，复杂度是 $\mathcal O(n2^{\frac{k}{2}})$ 的。然后要把所有贡献合并起来，方便后面 $\mathcal O(1)$ 查询。这个容易做，且不是复杂度瓶颈。最后查询直接调用 $f$ 就行了。

总复杂度 $\mathcal O(n2^{\frac{k}{2}})$。

有个问题是直接做空间好像也是这个复杂度的。不过我们求的信息具有可加性，因此可以像数据结构题中的分块技巧一样，逐块处理，这样空间就是线性的了。

~~稍微~~狠狠卡卡常就能过啦。代码仅供参考，如果你写了这个做法，说明你已经和我差不多笨了。

不是最劣解，胜利！

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define per(i,a,b) for(register int i=(a);i>=(b);--i)
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
const ll N=5e5+9,Mod=1e9+7;
int n,K,a[N],inv[25],b[N],tmp[N],tot,rs[(1<<20)+5],pos[N],len;
ll ans[(1<<20)+5];
int bin[(1<<20)+5],tcnt[(1<<11)+5];
int cnt[(1<<10)+2][12][2];
ll pre[(1<<10)+2][12][2],contri[(1<<10)+2][12][12];
ll pw(ll x,ll p){
    ll res=1;
    while(p){
        if(p&1)res=res*x%Mod;
        x=x*x%Mod,p>>=1;
    }
    return res;
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    n=read(),K=read();
    rep(i,1,n)a[i]=read(),bin[a[i]]++;
    rep(i,1,(1<<K)-1){
        if(bin[i])b[++tot]=i;
    }
    rep(i,1,K)inv[i]=pw(i,Mod-2);
    ll top=min(10,K),top2=K-top;
    rep(i,0,(1<<top)-1){
        memset(cnt,0,sizeof(cnt));
        memset(pre,0,sizeof(pre));
        len=0;
        rep(j,0,(1<<top2)-1){
            tcnt[j]=bin[(i<<top2)|j];
            if(tcnt[j])pos[++len]=j;
        }
        rep(j,0,(1<<top2)-1){
            rep(k,1,len){
                int tpc=__builtin_popcount(j|pos[k]),tc=tcnt[pos[k]];
                cnt[j][tpc][0]+=tc;
                cnt[j][tpc][1]+=tc*__builtin_popcount(j&pos[k]);
            }
        }
        rep(j,0,(1<<top2)-1){
            rep(hig1,0,top){
                rep(k,0,top2){
                    pre[j][hig1][0]+=1ll*cnt[j][k][0]*inv[hig1+k];
                    pre[j][hig1][1]+=1ll*cnt[j][k][1]*inv[hig1+k];
                }
                rep(hig0,0,hig1)contri[j][hig1][hig0]=pre[j][hig1][0]*hig0+pre[j][hig1][1];
            }
        }
        rep(j,1,tot){
            int hig0=__builtin_popcount((b[j]>>top2)&i);
            int hig1=__builtin_popcount((b[j]>>top2)|i);
            int low=b[j]&((1<<top2)-1);
            ll &res=ans[j];
            res+=contri[low][hig1][hig0];
        }
    }
    rep(i,1,tot)rs[b[i]]=ans[i]%Mod;
    rep(i,1,n)write(rs[a[i]]),putchar('\n');
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

## 作者：Mirasycle (赞：4)

好题，感觉挺难的，为什么不评黑啊/fn，我瞪了好久题解，自己理解了半天。

如果只有分子的话，就是对于每一位拆贡献就行了。

推广到有分母的情况，还是拆分子贡献，枚举分子每一位把该位置有 $1$ 的分母放在一起处理。

于是对于分母，我们只需要算出 $\dfrac{1}{\vert a_i\cup a_j \vert}$ 的贡献就行了，因为对于分子我们已经拆掉贡献了（其实这一步是可以通过 $\vert a_i\cap a_j\vert=\vert a_i\vert+\vert a_j\vert-\vert a_i\cup a_j\vert$ 直接去掉分母的，不过未必能注意到）。

先是做一步转化，将 $a_i$ 按位取反，那么贡献也发生了变化 $\dfrac{1}{\vert a_i\cup a_j \vert}\to \dfrac{1}{k-|a_i\cap a_j|}$，之后的容斥我一开始没怎么看懂啊，感觉和之前见过的长的不太像/ll。

考虑 $j\to i$ 的贡献，可以发现 $a_i\cap a_j$ 是 $a_i$ 的子集，也是 $a_j$ 的子集。所以贡献法的流程应该是 $a_j$ 贡献给自己的所有子集，$a_i$ 再从自己所有的子集中求和。

不过这么做肯定会算重的，具体来说 $\sum\limits_{s\subset a_i\cap a_j} \dfrac{1}{k-|s|}$ 被我们计算了多次。而我们只希望其贡献出 $\dfrac{1}{|a_i\cap a_j|}$。因此设计出一个容斥系数 $f(|s|)$ 和贡献函数 $g(|t|)=\dfrac{1}{k-|t|}$，我们希望 $\sum\limits_{s\subset t}f(|s|)=g(|t|)$，也就是说 $\sum\limits_{j=0}^i{i\choose j}f_j=g_i$。$k$ 很小，所以这个式子是可以 $O(k^2)$ 递推的。

于是我们只需要对于 $a_j$ 的所有子集 $s$ 都加上 $f(|s|)$，再对于 $a_i$ 的所有子集求和即可。

对于前者就是对于超集做一遍高维前缀和，后者就是对于子集做一遍高维前缀和。问题就做完了。

时间复杂度 $O(nk+k^22^k)$。


```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef long long ll;
const int maxn=5e5+10;
const int maxk=22;
const int maxs=(1<<20)+5;
const int mod=1e9+7;
void add(int &x,int y){ x=x+y>=mod?x+y-mod:x+y; }
void sub(int &x,int y){ x=x<y?x-y+mod:x-y; }
void cmax(int &x,int y){ x=x>y?x:y; }
void cmin(int &x,int y){ x=x<y?x:y; }
int a[maxn],b[maxn],pc[maxs],U,n,k;
int f[maxk],g[maxk],C[maxk][maxk];
int h[maxs],F[maxs],ans[maxn]; vector<int> vec;
int lowbit(int x){ return x&-x; }
int qpow(int x,int k){
	int res=1;
	for(;k;k>>=1){
		if(k&1) res=1ll*res*x%mod;
		x=1ll*x*x%mod;
	}
	return res;
}
void init(){
	U=(1<<k)-1; pc[0]=0; C[0][0]=1;
	for(int i=1;i<=(1<<k);i++) pc[i]=pc[i^lowbit(i)]+1;
	for(int i=1;i<=k;i++){
		C[i][0]=1;
		for(int j=1;j<=k;j++)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
	for(int i=0;i<=k;i++) g[i]=qpow(k-i,mod-2);
    for(int i=0;i<=k;i++){
    	int res=0;
    	for(int j=0;j<i;j++) add(res,1ll*C[i][j]*f[j]%mod);
    	f[i]=g[i]; sub(f[i],res);
	}
}
int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n>>k; init();
	for(int i=1;i<=n;i++) cin>>a[i],b[i]=U^a[i];
	for(int i=0;i<k;i++){
		vec.clear();
		for(int j=1;j<=n;j++)
			if((a[j]>>i)&1) vec.pb(j);
		for(int s=0;s<(1<<k);s++)
			h[s]=F[s]=0;
		for(auto z:vec) h[b[z]]++;
		for(int j=0;j<k;j++)
			for(int s=0;s<(1<<k);s++)
				if(!((s>>j)&1)) add(h[s],h[s^(1<<j)]);
		for(int s=0;s<(1<<k);s++) add(F[s],1ll*h[s]*f[pc[s]]%mod);
		for(int j=0;j<k;j++)
			for(int s=0;s<(1<<k);s++)
				if((s>>j)&1) add(F[s],F[s^(1<<j)]);				
		for(auto z:vec)
			add(ans[z],F[b[z]]);
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<"\n";
	return 0;
}
```

---

## 作者：Judgelight (赞：4)

[传送门](https://www.luogu.com.cn/problem/P11458)

---

我有一个不可优化的 $O(2^kk^2)$ 的勾巴做法。

不妨设分子为 $a$，分母为 $b$，然后因为用到了 $a$，所以设第 $i$ 个数为 $A_i$。

直接设 $f_{i,S,a,b}$ 表示只考虑前 $i$ 位，$S$ 的答案的分子为 $a$，分母为 $b$ 的方案数，那么答案显然为 $ans_i=\sum\limits_{a=0}\limits^{k}\sum\limits_{b=1}\limits^{k}f_{k,A_i,a,b}\times\frac{a}{b}$。DP 的话考虑从 $i$ 转移到 $i+1$，考虑 $i$ 位的值，进行高维前缀和，得到方程：

1. $S_i=0:f_{i+1,S,a,b}\leftarrow f_{i,S,a,b},f_{i+1,S+2^{i},a,b+1}\leftarrow f_{i,S,a,b}$
2. $S_i=1:f_{i+1,S-2^i,a,b+1}\leftarrow f_{i,S,a,b},f_{i+1,S,a+1,b+1}\leftarrow f_{i,S,a,b}$

转移可以看作我们在枚举下一位的值，假如是 $x=0/1,y=0/1$，那么分子的增量就是 $x\&y$，分母的增量就是 $x|y$。

这么做是 $O(2^kk^3)$ 的，并且空间就算把 $i$ 滚掉也是 $O(2^kk^2)$ 的。

但是我们考虑可以把分子在 DP 过程中直接记录，我们只需要记一下答案的 $0$ 次方（方案数），答案的 $1$ 次方即可，复杂度就变成 $O(2^kk^2)$ 了。

---

## 作者：Yuzu_Soft (赞：4)

为什么大家都在高维前缀和和组合数qwq

我们考虑拆一下题目的式子：
$$
ans[i]=\left(\sum_j \frac{cnt[j]\operatorname{popcount}(j)}{\operatorname{popcount}(j\lor a[i])}\right)+\operatorname{popcount}(a[i])\left(\sum_j \frac{cnt[j]}{\operatorname{popcount}(j\lor a[i])}\right)-n
$$
其中 $cnt[x]$ 表示 $x$ 的出现次数。

那么我们相当于要对每个 $x=a[i]$ 解决如下形式的问题：
$$
\sum_j \frac{val[j]}{\operatorname{popcount}(j\lor x)}
$$
考虑一个 DP。设 $f[i][mask][cnt]$ 表示 $x$ 与 $mask$ 的末尾 $i$ 位相等，$j$ 与 $mask$ 的开头 $20-i$ 位相等，$j\lor x$ 的前 $20-i$ 位中有 $cnt$ 位为 $1$，满足以上条件所有的的 $j$ 对**一个**满足条件的 $x$ 的贡献的和。

预处理：$f[0][j][k]=\frac{val[j]}{k}$。

然后转移的时候枚举 $j$ 的第 $i$ 位为多少，
$$
\begin{aligned}
f[i][mask][cnt]
&=f[i-1][mask][cnt+(\lfloor\frac{mask}{2^{i-1}}\rfloor\bmod 2)]
\\
&+f[i-1][mask\oplus (j2^{i-1})][cnt+1]
\end{aligned}
$$
最后使用开头的式子即可。

时间复杂度为 $O(n+2^kk^2)$，使用滚动数组后空间复杂度为 $O(k2^k)$，能过。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
inline int mul(int x,int y){return 1ll*x*y%mod;}
inline int add(int x,int y){return (x+=y)>=mod?x-mod:x;}
inline int sub(int x,int y){return (x-=y)<0?x+mod:x;}
inline int qpow(int x,int y){int ret=1;while(y){if(y&1)ret=mul(ret,x);x=mul(x,x),y>>=1;}return ret;}
inline int inv(int x){return qpow(x,mod-2);}
int n;
int in[500005];
int cnt[1<<20];
struct node
{
    int val1,val2;
};
inline node operator+(node x,node y)
{
    return node{add(x.val1,y.val1),add(x.val2,y.val2)};
}
inline node operator*(node x,int y)
{
    return node{mul(x.val1,y),mul(x.val2,y)};
}
node g[2][1<<20][21];
int calc(int x)
{
    return sub(add(g[0][x][0].val2,mul(g[0][x][0].val1,__builtin_popcount(x))),n);
}
int main()
{
    scanf("%d%*d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&in[i]);
        cnt[in[i]]++;
    }
    for(int x=0;x<=20;x++)
    {
        int invx=inv(x);
        for(int j=0;j<(1<<20);j++)
        {
            g[0][j][x]={mul(cnt[j],invx),mul(mul(cnt[j],invx),__builtin_popcount(j))};
        }
    }
    for(int i=1,opt=1;i<=20;i++,opt^=1)
    {
        for(int j=0;j<(1<<20);j++)
        {
            for(int x=0;x<=20-i;x++)
            {
                int c=(j>>i-1)&1;
                if(c==0)g[opt][j][x]=g[opt^1][j][x]+g[opt^1][j^(1<<i-1)][x+1];
                else g[opt][j][x]=g[opt^1][j][x+1]+g[opt^1][j^(1<<i-1)][x+1];
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        printf("%d\n",calc(in[i]));
    }
    return 0;
}
/*
4 2
1 1 2 3
*/
```

---

## 作者：Doqe (赞：3)

所谓的转置原理，只不过是“旋转”的特例罢了。

首先正常的操作：$\frac{|S\cap T|}{|S\cup T|}=-1+\frac{|S|+|T|}{|S\cap T|}$，这样我们将问题转化为 $\sum_j \frac{|S_i\cap S_j|}{|S_i\cup S_j|}$，适度分离 $S_i$ 得到 $|S_i|\sum\frac1{|S_i\cup S_j|}+\sum_j\frac{|S_j|}{|S_i\cup S_j|}$。

接下来把问题放在 $\sum_j \frac{1}{|S_i\cup S_j|}g(j)$ 的求解上。

这个如果考虑 $a_S=\frac{1}{|S|},b(T)=\sum_i[S_i==T]$，我们有 $c_U=\sum_{S=U\cup T}a_Sb_T$，其是 $S_i=U$ 的答案。

接下来大部分题解发现 $S=U\cup T$ 交换 $S,U$ 可以变成 $U=S\cup T$，进而将 $b_T$ 视作常值采用转置原理，本质上是对多线性函数（这里算三维）的特殊处理，不能拓展到一般情况。

阅读 [快速数列变换这个词怎么造出来的 - 洛谷专栏](https://www.luogu.com.cn/article/76llxu54) 可能能够对这里的理解有点帮助。这里是“进一步？”中的具体展开。

接下来的分析由于每一位相同，只考虑一维度的情况，即数组长度为 $2$。

三维的“转置原理”自然需要使用三维的结构来说明，而不是使用矩阵。我们引入张量来表示常见的 OR 操作运算函数：

$$X^{or}_{i,j,k}=[i\cup j=k]$$

和本题的

$$X_{i,j,k}=[k\cup j=i]$$

这里可以理解为 $a_ib_j\to c_k$ 的贡献，并且这里保证 $i,j,k\in\{0,1\}$。

我们有如果 $C[(Aa)\cdot(Bb)]=c$，其中 $\cdot$ 是按位乘法，这描述了 FWT 类型的底层逻辑。那么对应的张量可以分解成 $X=\sum A_i\circ B_i\circ C^T_i$。其中 $A_i$ 意思是取出第 $i$ 行。$(a\circ b\circ c)_{i,j,k}=a_ib_jc_k$，加法按位加。

我们进行一个“旋转”操作。具体来说，我们先依据 OR 运算的算法流程获得 $X^{or}$ 的一个 CP 分解：

$$X^{or}=(1,0)\circ(1,0)\circ(1,-1)+(1,1)\circ(1,1)\circ(0,1)$$


注意 $X^{or}$ 和 $X$ 的区别是交换了一三维度。我们自然得出：

$$X=(1,-1)\circ(1,0)\circ(1,0)+(0,1)\circ(1,1)\circ(1,1)$$


那么这里 $A=\begin{pmatrix}1&-1\\0&1\end{pmatrix}$，对应做 IAND 的时候的 FWT 变换矩阵。

那么这里 $C=\begin{pmatrix}1&1\\0&1\end{pmatrix}$，对应做 AND 的时候的 FWT 变换矩阵。

因此我们有抽象的 $c=AND(IAND(a)\cdot OR(b))$。

复杂度 $O(2^kk+n)$。

至于为什么叫做“旋转”，如果你将张量看作三维立方体，顶点处有值。等价性可以直观的看成立方体旋转。

> 附加说明，[快速数列变换这个词怎么造出来的 - 洛谷专栏](https://www.luogu.com.cn/article/76llxu54) 中提到的 Baur-Strassen's Algorithm 可以解释这里所涉及的内容，但是这里的分析会更加直观的告诉为什么可以转换获得其他情况的做法。

---

## 作者：nullqtr_pwp (赞：3)

pp_orange 好牛啊。


本题可以被强化为如下问题：

> 给定下标为 $[0,2^k-1]$ 的数组 $f,g$，预处理所有 $h_S=\sum_{T=0}^{2^k-1} f_Tg_{s\text{ or }T}$，要求 $\mathcal O(2^kk)$。

首先考虑令 $(S\cup T)\subseteq U$，等价于 $S\subseteq U,T\subseteq U$，做一个类似分步转移的东西，那么令 $d_S=\sum_{T\subseteq S}f_T$，那么相当于对所有 $S\subseteq U$，令 $h_S\to h_S+g_Ud_U$。但问题是可能 $(S\cup T)$ 是 $U$ 的一个真子集，那么我们钦定其是 $P\subseteq U$ 的子集时，给它带上一个容斥系数 $(-1)^{|U|-|P|}$，然后对于所有 $S\subseteq P$，令 $h_S\to h_S+(-1)^{|U|-|P|}g_Pd_P$。此时对于一个确定的 $U,T$，考虑 $|S\cup T|=k<|U|$ 时，计算的系数恰好是 $0$（组合数一些基础的恒等式），那么这个是正确的。

$d$ 是好求的。然后对于 $(U,P)$ 的贡献，考虑在时间复杂度上优化这个东西，你发现魔改一下高维前缀和过程就好了，也就是考虑 $U-P$ 的每一个元素 $x$，令其带来 $-1$ 的系数。然后在变换后的数组做点积。对于在 $h$ 上子集加这个东西，相当于高维打 tag 然后最后通过高维后缀和再进行下传。时间复杂度 $\mathcal O(2^kk)$。

```  cpp
const int mx=(1<<k)-1;
F(i,0,k-1)F(s,0,mx)if((s>>i)&1)inc(f[s],f[s^(1<<i)]),dec(g[s^(1<<i)],g[s]);
F(s,0,mx)h[s]=1ll*f[s]*g[s]%mod;
F(i,0,k-1)F(s,0,mx)if((s>>i)&1)inc(h[s^(1<<i)],h[s]);
```

上述参考代码的 ```inc``` 指的是模意义下的 $x\to x+y$，```dec``` 指的是模意义下的 $x\to x-y$。

---

## 作者：lzytag (赞：3)

水个 $O(2^KK)$ 的题解。

记 $\operatorname {count}(i)$ 为 $i$ 的二进制表示中 $1$ 的个数，容易发现 $\frac{\operatorname {count}(i \And j)}{\operatorname {count}(i|j)}=\frac{\operatorname {count}(i)+\operatorname {count}(j)}{\operatorname {count}(i|j)}-1$。

于是我们只用管分母就好了，也就是要对于 $a_i$ 求出：
$$\sum_{k|a_i=k} \sum_{k|a_j=k} \frac{[a_i|a_j=k]}{\operatorname {count}(k)} $$
以及
$$\sum_{k|a_i=k} \sum_{k|a_j=k} \frac{[a_i|a_j=k]\operatorname {count}(a_j)}{\operatorname {count}(k)}$$
不考虑 $[a_i|a_j=k]$ 的限制，以上两个式子都可以视作做一遍按位或的 FMT，将得到的数组每一位除以 $\operatorname {count}(k)$，再做一遍按位与的 FMT 得到的结果，但是加上这个限制之后，我们就不能直接除以该值，考虑乘上一个容斥系数，容易发现这个容斥系数只与 $\operatorname {count}(k)$ 有关。设 $\operatorname {count}(k) = x$ 时容斥系数为 $f_x$。

对于容斥系数要求满足对于任意 $y$，$\sum_{x=y}^{K} C_{K-y}^{K-x}f_x = \frac{1}{y}$，移项即可得到递推式 $f_K = \frac{1}{K}$，$f_x=\frac{1}{k}-\sum_{y=x+1}^{K}C_{K-x}^{K-y}f_y$，直接递推求即可。

然后就做完了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1<<20,mod = 1e9+7;
int n,K;
int a[N];
ll s1[N],s2[N];
ll V[21],C[21][21],inv[21];
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n>>K;
    for(int i = 1;i <= n;i++)
    {
        int x;cin>>x;
        a[i] = x;
        s1[x]++;
        s2[x] += __builtin_popcount(x);
    }
    inv[1] = 1;
    for(int i = 2;i <= K;i++) inv[i] = mod - mod/i*inv[mod%i]%mod;
    for(int i = 0;i <= K;i++)
    {
        C[i][0] = 1;
        for(int j = 1;j <= i;j++) C[i][j] = (C[i-1][j] + C[i-1][j-1])%mod;
    }
    V[K] = inv[K];
    for(int i = K-1;i;i--)
    {
        V[i] = inv[i];
        for(int j = i+1;j <= K;j++) V[i] = (V[i] + mod - V[j]*C[K-i][K-j]%mod)%mod;
    }
    for(int i = 1;i < (1<<K);i<<=1)
        for(int j = 0;j < (1<<K);j += i<<1)
            for(int k = 0;k < i;k++)
            {
                s2[i+j+k] += s2[j+k];
                s1[i+j+k] += s1[j+k];
            }
    for(int i = 1;i < (1<<K);i++)
    {
        s2[i] = s2[i]*V[__builtin_popcount(i)]%mod;
        s1[i] = s1[i]*V[__builtin_popcount(i)]%mod;
    }
    for(int i = 1;i < (1<<K);i<<=1)
        for(int j = 0;j < (1<<K);j += i<<1)
            for(int k = 0;k < i;k++)
            {
                s2[j+k] += s2[i+j+k];
                s1[j+k] += s1[i+j+k];
            }
    for(int i = 1;i <= n;i++)
    {
        cout<<(__builtin_popcount(a[i])*s1[a[i]] + s2[a[i]]-n+mod)%mod<<"\n";
    }
    return 0;
}
```

---

## 作者：Purslane (赞：3)

# Solution

不打 usaco 的小朋友只能度过绝对失败的 OI 生涯。

给个 $O(k^22^k+nk)$ 的憨憨做法。

考虑 $\dfrac{|a \cap b|}{|a \cup b|}$ 可以转化为，枚举 $a$ 和 $b$ 都是 $1$ 的位，求出 $\sum \dfrac{1}{|a \cup b|}$ 并求和。

--------

考虑怎么求 $\sum_b \dfrac{1}{|a \cup b|}$，并且要求 $x \in a \cap b$。

首先，我们可以求出 $U / a$，则 $b / (b \cap a)$ 一定是它的子集。

然后可以求出 $f_i$ 表示**钦定了 $|b / (b \cap a)| \ge i$ 且 $x \in a \cap b$ 的方案数**。显然 $g_i$ 表示**实际上 $|b / (b \cap a)| = i$ 且 $x \in a \cap b$** 的方案数。$g$ 可以通过 $f$ 进行二项式反演得到。

注意到当 $\text{popcount}(a)$ 一定时，$g_i$ 只和 $i$ 有关，预处理即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=(1<<20)+5,MOD=1e9+7;
int n,k,a[MAXN],pre[MAXN][21],C[50][50],tmp[MAXN],mul[50][50],f[MAXN];
ll qpow(ll base,int p) {
	ll ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>k;
	ffor(i,1,n) cin>>a[i];
	ffor(i,0,k) {C[i][0]=1;ffor(j,1,i) C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;}
	ffor(i,1,n) tmp[a[i]]++;
	ffor(i,0,k-1) ffor(j,0,(1<<k)-1) if(j&(1<<i)) tmp[j-(1<<i)]+=tmp[j];
	ffor(i,0,(1<<k)-1) pre[i][__builtin_popcount(i)]=tmp[i];
	ffor(i,0,k-1) ffor(j,0,(1<<k)-1) if(j&(1<<i)) ffor(t,0,k) pre[j][t]=(pre[j][t]+pre[j-(1<<i)][t])%MOD;
	ffor(t,0,k) ffor(j,0,k) {
		ffor(i,0,j) {
			if((j-i)%2==0) mul[t][j]=(mul[t][j]+1ll*C[j][i]*qpow(i+t,MOD-2))%MOD;
			else mul[t][j]=(mul[t][j]-1ll*C[j][i]*qpow(i+t,MOD-2))%MOD;
		}
	}
	ffor(i,1,n) {
		ll ans=0,pc=__builtin_popcount(a[i]);
		ffor(j,0,k-1) if(a[i]&(1<<j)) {
			int ot=(1<<k)-1-a[i]+(1<<j);
			ffor(t,1,k) f[t-1]=(pre[ot][t]-pre[ot-(1<<j)][t])%MOD;
			ffor(t,0,k) ans=(ans+1ll*f[t]*mul[pc][t])%MOD;
		}
		cout<<(ans%MOD+MOD)%MOD<<'\n';
	}
	return 0;
}
```

---

## 作者：nullqtr_pwp (赞：3)

这是一个状压的形式，可以用集合的语言描述。考虑查询 $a_i$，记其所有为 $1$ 的位构成的集合为 $S$，全集为 $U$。那么考虑枚举 $t=\text{popcount}(a_i\text{ or }a_j)$，那么等价于获取，所有 $|a_i\cap (U/S)|=t-|S|$ 的所有 $a_i$ 的信息。问题来到预处理：

- $f(S,r)=\sum_T[|S\cap T|=r]c_r$。
- $g(S,r)=\sum_T[|S\cap T|=r]c_rs_r$。

我们希望找出所有 $K\subseteq S,K\subseteq T$ 的子集 $K$ 的信息，因为交集是恰好就很烦。考虑 $K\subseteq S$ 作为查询，$K\subseteq a_i$ 作为修改。设计一个容斥系数即可。考虑先提取出 $r$，然后考虑容斥系数 $coef_p$，容斥系数基于 $p=|S|$。那么令实际交集为 $q=|S\cap T|$，就要求 $\sum_{p\leq i\leq q}\binom{q}{i}coef_i=[p=q]$，显然有 $coef_p=1$，而后可以用 $\mathcal O(k^2)$ 的递推求 $coef$。子集加子集和容易用高维前缀和处理。时间复杂度 $\mathcal O(2^kk^2)$。


- 官方题解声明 $\frac{|a\cap b|}{|a\cup b|}=\frac{|a|+|b|}{|a\cup b|}-1$，可以整体做，复杂度消到 $\mathcal O(2^kk)$。
- [@tzl_dedicatus545](https://www.luogu.com.cn/user/308854) 指出，在 $t$ 的 $coef_i$ 事实上就是 $\binom{t}{i}(-1)^{t-i}$，因为这是一个二项式反演。
```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
#define ll long long
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define inf 1000000000
#define infll 1000000000000000000ll
#define pii pair<int,int>
#define rep(i,a,b,c) for(int i=(a);i<=(b);i+=(c))
#define per(i,a,b,c) for(int i=(a);i>=(b);i-=(c))
#define F(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
#define dF(i,a,b) for(int i=a,i##end=b;i>=i##end;i--)
#define cmh(sjy) while(sjy--)
#define lowbit(x) (x&(-x))
#define HH printf("\n")
#define eb emplace_back
#define poly vector<int>
#define SZ(x) ((int)x.size())
using namespace std;
const int mod=1e9+7,maxn=500005;
inline int qpow(int x,ll y){ int res=1; for(;y;y>>=1,x=1ll*x*x%mod)if(y&1)res=1ll*res*x%mod; return res; }
inline void inc(int &x,const int y){ x=(x+y>=mod)?(x+y-mod):(x+y); }
inline void dec(int &x,const int y){ x=(x>=y)?(x-y):(x+mod-y); }
inline int add(const int x,const int y){ return (x+y>=mod)?(x+y-mod):(x+y); }
inline int sub(const int x,const int y){ return (x>=y)?(x-y):(x+mod-y); }
int n,k,a[maxn],inv[22];
#define ppc __builtin_popcount
int res[21][1<<20],f[1<<20],g[1<<20],init_f[1<<20],init_g[1<<20],coef[22],C[22][22];
void solve(){
	cin>>n>>k;
	F(i,0,k)C[i][0]=1;
	F(i,1,k)F(j,1,i)C[i][j]=add(C[i-1][j-1],C[i-1][j]);
	const int mx=(1<<k)-1;
	F(i,1,k)inv[i]=qpow(i,mod-2);
	F(i,1,n)cin>>a[i],++init_f[a[i]],init_g[a[i]]+=ppc(a[i]);
	F(i,0,k-1)F(s,0,mx)if((s>>i)&1)inc(init_f[s^(1<<i)],init_f[s]),inc(init_g[s^(1<<i)],init_g[s]);
	F(t,0,k){
		F(i,0,k)coef[i]=(i==t);
		F(i,t+1,k)F(j,t,i-1)dec(coef[i],1ll*C[i][j]*coef[j]%mod);
		F(s,0,mx)f[s]=1ll*init_f[s]*coef[ppc(s)]%mod,g[s]=1ll*init_g[s]*coef[ppc(s)]%mod;
		F(i,0,k-1)F(s,0,mx)if(!((s>>i)&1))inc(f[s^(1<<i)],f[s]),inc(g[s^(1<<i)],g[s]);
		F(s,0,mx)res[t][s]=sub(g[s],1ll*t*f[s]%mod);
	}
	F(i,1,n){
		int ans=0,tmp=ppc(a[i]),s=mx^a[i];
		F(j,0,ppc(s))inc(ans,1ll*inv[tmp+j]*res[j][s]%mod);
		cout<<ans<<'\n';
	}
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int zsy=1;
	F(____,1,zsy)solve();
}
```

---

## 作者：ningago (赞：2)

转置原理练习题！！！

首先自然地把 $\dfrac{|a\cap b|}{|a\cup b| }$ 改写成 $\dfrac{|a|}{|a\cup b|}+\dfrac{|b|}{|a\cup b|}-1$，这样就省去了一维限制。

难以处理的肯定是分母，并且分母还是或的形式，所以考虑直接用或卷积把分母处理掉。

你发现如果求「分母 $=S$ 的答案之和」的话是好算的，直接卷积即可。

首先 FWT 是个线性运算（把点值乘起来那部分看作乘常数），根据转置原理，把这个过程转置过来就可以得到「$a=S$ 的答案之和」。

把或卷积进行转置，即 $\begin{bmatrix}1&1\\0&1\end{bmatrix}$ 改写成 $\begin{bmatrix}1&0\\1&1\end{bmatrix}$， $\begin{bmatrix}1&-1\\0&1\end{bmatrix}$ 改写成 $\begin{bmatrix}1&0\\-1&1\end{bmatrix}$（其实就是与卷积）。

于是把「分母 $=S$」的算法倒着做一遍即可，复杂度和或卷积一样，是 $O(2^kk)$ 的。

```cpp
#define N 1000100
int n, m, f[1 << 20], g[1 << 20], a[N], pp[1 << 20], inv[N], ans[1 << 20];

void solve()
{
	// memset(h, idx = -1, sizeof(h));
	n = read(), m = read();
	for(int i = 0; i < (1 << m); i++) pp[i] = pp[i >> 1] + (i & 1);
	for(int i = 1; i <= m; i++) inv[i] = ksm(i, mod - 2);
	for(int i = 1; i <= n; i++) a[i] = read();

	for(int i = 0; i < (1 << m); i++) g[i] = f[i] = 0;
	for(int i = 1; i <= n; i++) g[a[i]] += pp[a[i]];
	for(int j = 0; j < m; j++) for(int i = 0; i < (1 << m); i++) if(i >> j & 1) plus_(g[i], g[i ^ (1 << j)]);
	for(int i = 0; i < (1 << m); i++) f[i] = inv[pp[i]];
	for(int j = 0; j < m; j++) for(int i = 0; i < (1 << m); i++) if(i >> j & 1) plus_(f[i ^ (1 << j)], mod - f[i]);
	for(int i = 0; i < (1 << m); i++) mul_(f[i], g[i]);
	for(int j = 0; j < m; j++) for(int i = 0; i < (1 << m); i++) if(i >> j & 1) plus_(f[i ^ (1 << j)], f[i]);
	for(int i = 0; i < (1 << m); i++) plus_(ans[i], f[i]);

	for(int i = 0; i < (1 << m); i++) g[i] = f[i] = 0;
	for(int i = 1; i <= n; i++) g[a[i]]++;
	for(int j = 0; j < m; j++) for(int i = 0; i < (1 << m); i++) if(i >> j & 1) plus_(g[i], g[i ^ (1 << j)]);
	for(int i = 0; i < (1 << m); i++) f[i] = inv[pp[i]];
	for(int j = 0; j < m; j++) for(int i = 0; i < (1 << m); i++) if(i >> j & 1) plus_(f[i ^ (1 << j)], mod - f[i]);
	for(int i = 0; i < (1 << m); i++) mul_(f[i], g[i]);
	for(int j = 0; j < m; j++) for(int i = 0; i < (1 << m); i++) if(i >> j & 1) plus_(f[i ^ (1 << j)], f[i]);
	for(int i = 0; i < (1 << m); i++) plus_(ans[i], 1ll * f[i] * pp[i] % mod);

	for(int i = 1; i <= n; i++) print(sm(ans[a[i]] + mod - n), '\n');
}
```

---

## 作者：_fairytale_ (赞：2)

取 $T_i=\overline{S_i}$，有：

$\sum_{j}\dfrac{|S_i\cap S_j|}{|S_i\cup S_j|}=|S_i|\sum_{j}\dfrac{1}{|S_i\cup S_j|}+\sum_{j}\dfrac{|S_j|}{|S_i\cup S_j|}-n=|S_i|\sum_{j}\dfrac{1}{k-|T_i\cap T_j|}+\sum_{j}\dfrac{|S_j|}{k-|T_i\cap T_j|}-n$。

我们通过容斥求出 $\sum_{j}\dfrac{1}{k-|T_i\cap T_j|}$，后面一项同理。

具体地，我们考虑这样一个错得离谱的算法：

对于每个 $T_i$，我们首先对它的所有子集 $T_i'$ 做 $f_{T_i'}\gets f_{T_i'}+\dfrac{1}{k-|T_i'|}$，然后对 $f$ 做高维前缀和。最后查询时直接查 $f_{T_i}$。

这个算法错误的原因是，设 $T=T_i\cap T_j$，每个 $T'\subseteq T$ 都对答案有 $\dfrac{1}{k-|T'|}$ 的贡献，而我们希望总的贡献是 $\dfrac{1}{k-|T|}$。其实我们只关心集合大小，于是考虑给每个大小为 $t$ 的集合分配一个系数 $a_t$，使之满足我们的期望，即对于每个 $T$，都有 $\sum_{T'\subseteq T}\dfrac{1}{k-|T'|}=\sum_{t=0}^{|T|}{|T|\choose t}a_t=\dfrac{1}{k-|T|}$。

显然 $a_0=\dfrac{1}{k}$，而上面的式子可以得出 $a_t=\dfrac{1}{k-t}-\sum_{i=0}^{t-1}{t\choose i}a_i$，因此可以递推 $a_i$。

于是我们改为对于每个 $T_i$，对它的所有子集 $T_i'$ 做 $f_{T_i'}\gets f_{T_i'}+a_{|T_i'|}$，然后对 $f$ 做高维前缀和。最后查询时直接查 $f_{T_i}$。

你问怎么“对于每个 $T_i$，对它的所有子集 $T_i'$ 做 $f_{T_i'}\gets f_{T_i'}+a_{|T_i'|}$”？可以转成对于 $S$，用高维后缀和求出有 $x$ 个 $T$ 是 $S$ 的超集，那么 $f_{S}$ 就是 $xa_{|S|}$ 呀！

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ppc(x) __builtin_popcount(x)
#define rep(x,qwq,qaq) for(int x=(qwq);x<=(qaq);++x)
#define per(x,qwq,qaq) for(int x=(qwq);x>=(qaq);--x)
using namespace std;
#define m107 1000000007
#define maxn 1051000
#define mod m107
template<typename Tp>
int qp(int x,Tp y) {
	assert(y>=0);
	x%=mod;
	int res=1;
	while(y) {
		if(y&1)res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return res;
}
int inv(int x) {
	return qp(x,mod-2);
}
struct Combinatorics {
#define Lim 2000000
	int fac[Lim+10],invfac[Lim+10];
	Combinatorics() {
		fac[0]=invfac[0]=1;
		rep(i,1,Lim)fac[i]=1ll*fac[i-1]*i%mod;
		invfac[Lim]=inv(fac[Lim]);
		per(i,Lim-1,1)invfac[i]=1ll*invfac[i+1]*(i+1)%mod;
	}
	int C(int n,int m) {
		if(n<m||n<0||m<0)return 0;
		return 1ll*fac[n]*invfac[m]%mod*invfac[n-m]%mod;
	}
	int A(int n,int m) {
		if(n<m||n<0||m<0)return 0;
		return 1ll*fac[n]*invfac[n-m]%mod;
	}
} comb;
template<int MOD>
struct modint {
	int x;
	modint() {
		x=0;
	}
	template<typename T>
	int norm(T y) {
		return (y%MOD+MOD)%MOD;
	}
	template<typename T>
	modint(T y) {
		x=norm(y);
	}
	friend modint operator +(modint a,modint b) {
		return a.x+b.x;
	}
	friend modint operator -(modint a,modint b) {
		return a.x-b.x;
	}
	friend modint operator *(modint a,modint b) {
		return 1ll*a.x*b.x;
	}
	modint& operator +=(modint b) {
		return x=norm(x+b.x),*this;
	}
	modint& operator -=(modint b) {
		return x=norm(x-b.x),*this;
	}
	modint& operator *=(modint b) {
		return x=norm(1ll*x*b.x),*this;
	}
	friend istream& operator >>(istream&is,modint &x) {
		ll v;
		return is>>v,x.x=norm(v),is;
	}
	friend ostream& operator <<(ostream&os,modint x) {
		return os<<x.x,os;
	}
};
using mint=modint<m107>;
int n,k;
int S[maxn],T[maxn];
mint a[maxn],b[maxn];
mint f[maxn],g[maxn];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>k;
	int U=(1<<k)-1;
	rep(i,1,n)cin>>S[i];
	rep(i,1,n) {
		T[i]=U^S[i];
		f[T[i]]+=1,g[T[i]]+=ppc(S[i]);
	}
	rep(i,0,k-1) {
		rep(mask,0,U) {
			if(~(mask>>i)&1)f[mask]+=f[mask^(1<<i)],g[mask]+=g[mask^(1<<i)];
		}
	}
	a[0]=inv(k);
	rep(s,1,k) {
		a[s]=inv(k-s);
		rep(i,0,s-1)a[s]-=a[i]*comb.C(s,i);
	}
	rep(mask,0,U)f[mask]*=a[ppc(mask)],g[mask]*=a[ppc(mask)];
	rep(i,0,k-1) {
		rep(mask,0,U) {
			if((mask>>i)&1)f[mask]+=f[mask^(1<<i)],g[mask]+=g[mask^(1<<i)];
		}
	}
	rep(i,1,n)cout<<f[T[i]]*ppc(S[i])+g[T[i]]-n<<'\n';
	return 0;
}
```

---

## 作者：zhenjianuo2025 (赞：2)

题目让我们对所有 $i$ 求 $\sum_j\frac{|a_i\cap a_j|}{|a_i\cup a_j|}$。

枚举一位 $k\in a_i\cap a_j$，那么式子变成 $\sum_k\sum_j[k\in a_i][k\in a_j]|a_i\cup a_j|^{-1}$。

对所有 $i$ 求 $f_{i,j}$ 表示有多少 $a_k$ 和 $a_i$ 的并大小恰好是 $j$。

求 $f_{i,j}$ 不好求，转而求 $g_{i,j}=\sum_{k=1}^{i}\binom{K-k}{K-j}f_{i,k}$，然后做一遍二项式反演。

求 $g_{i,j}$ 好办，只要钦定 $S$ 使得 $a_i$ 和 $a_k$ 都被包含并给 $i$ 贡献 $k$ 的数量，可以 $O(K2^K)$ 子集和。需要对不同 popcount 的 $S$ 分别处理，这样时间复杂度只能 $O(K^32^K+KN)
$。

进一步，注意到只需要求反演之后 $g_{i,k}$ 带上某个系数 $a_{i,k}$ 的和 $\sum_k a_{i,k}g_{i,k}$，可以带着贡献合在一起做子集和，复杂度 $O(K^22^K+N)$。

UPD：$|a_i\cap a_j|=|a_i|+|a_j|-|a_i\cup a_j|$，拆成三项来做，不用枚举交的一位，复杂度只带一个 $K$。

---

## 作者：xieziheng (赞：2)

这个月 USACO 打的有点太答辩了，就过了一题，智障的 T3，哈哈哈，我是不可能写的出来的。

今天我把这道题喂给了 deepseek，给我生成了个 30000 字的思考，最后生成的代码显然还是错的，乐。

所以就补了下这个题，上次我空间 $\mathcal{O}(2^kk^2)$ 在 $k=20$ 的两个点被卡了，不知道我咋想的。。。来个 $\mathcal{O}(2^kk^2)$ 的塘鲺做法。

注意到 $\frac {|S\cap T|} {|S\cup T|}=\frac {|S|+|T|} {|S\cup T|}-1$，所以记等于 $i$ 的有 $a_i$ 个，我们就是对每个 $i$ 求 $(\sum_{j=0}^{2^k-1}\frac {a_j(\operatorname{popcount}(i)+\operatorname{popcount}(j))} {\operatorname{popcount}(i|j)})-n$ 拆开，两部分是类似的，只考虑第一部分。

直接 FWT，记 $f_{i,j}$ 表示当前分治层 $i$ 的求和那个东西的分母为 $j$ 的时候分子的和，转移是显然的。

复杂度 $\mathcal{O}(2^kk^2)$，经过一些卡常跑的飞快，几乎和 $\mathcal{O}(2^kk)$ 一样快。

---

## 作者：_Ch1F4N_ (赞：0)

处理分母中的 $|A \cap B|$ 是难以避免的，不妨考虑枚举这个值，那分子中的 $|A \cup B|$ 就必须变成一个好看的形式，不难发现的是 $|A \cup B| = |A| + |B| - |A \cap B|$，原式变成 $\frac{|A|+|B|}{|A \cap B|} - 1$。减 $1$ 可以提出来最后算。所以先不管。

考虑枚举 $A$，计算贡献，是 $\sum_{B} \frac{|A|+|B|}{|A \cap B|}$，枚举 $B$ 和 $|A \cap B| = C$，式子变成 $\sum_{B,C A \cap B = C} \frac{|A|+|B|}{|C|}$，由于 $A$ 在计算贡献的时候和 $B,C$ 关系不大，所以我们不妨维护多项式 $f_A(x) = \sum_{B,C A \cap B = C} \frac{x+|B|}{|C|}$，最后 $f_A(|A|)$ 就是答案。

我们需要解决这样一个问题，给定 $a,b$，求解 $c_i = \sum_{i \cap j = k} a_j \times b_k$。

注意到这个过程与或卷积很相似，实际上，我们可以考虑这样一个问题。

给定数组 $a,c$，$b$ 为 $a,c$ 或卷积的结果，我们将 $b_i$ 以 $b'_i$ 的系数贡献到 $ans$ 上，$c$ 数组每个位置给定，求 $a$ 数组每个位置对 $ans$ 的贡献 $a'$。

手搓贡献过程一下不难发现这个问题和原问题等价。

考虑或卷积的过程，求出 $a,c$ 的高维前缀和数组 $A,C$，$B_i = A_i \times C_i$，求出 $B$ 的高维前缀差分数组 $b$。

考虑一步步推回去从 $b'$ 得到 $a'$。

首先考察 $B$ 贡献到 $b$ 的过程，显然有 $b_i = \sum_{j \subseteq i} B_j \times (-1)^{|i-j|}$。

于是可以得到 $B'$ 与 $b'$ 的关系，也就是 $B'_i  = \sum_{i \subseteq j} b'_j \times (-1)^{|j-i|}$，不难发现这是一个高维后缀差分形式。

然后有 $B_i = A_i \times C_i$，所以说 $a'_i = b'_i \times C_i$，这里求解 $C$ 数组需要一次高维前缀和。

最后考察 $a$ 贡献到 $A$ 的过程，有 $A_i = \sum_{j \subseteq i} a_j$，所以得到 $a'$ 与 $A'$ 的关系也就是 $a'_i = \sum_{i \subseteq j} A'_j$，这是一个高维后缀和的形式。

于是问题在 $O(n+k \times 2^k)$ 的时间复杂度内解决。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1e9+7;
const int maxv = (1<<20);
const int maxn = 5e5+114;
int dp[maxv],k[maxv],b[maxv],f[maxv],popc[maxv];
int n,K,st[maxn];
int qpow(int a,int b){
    if(b==0) return 1;
    if(b==1) return a;
    int res=qpow(a,b/2);
    res=res*res%mod;
    if(b%2==1) res=res*a%mod;
    return res;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>K;
    for(int i=1;i<maxv;i++){
        popc[i]=popc[i>>1]+(i&1);
        f[i]=qpow(popc[i],mod-2);
    }    
    for(int i=1;i<=n;i++) cin>>st[i],k[st[i]]++,b[st[i]]=(b[st[i]]+popc[st[i]])%mod;
    for(int i=0;i<K;i++){
        for(int j=0;j<maxv;j++){
            if((1<<i)&j){
                f[j-(1<<i)]=(f[j-(1<<i)]+mod-f[j])%mod;
            }
        }
    }
    for(int i=0;i<K;i++){
        for(int j=maxv-1;j>=0;j--){
            if((1<<i)&j){
                k[j]=(k[j]+k[j-(1<<i)])%mod;
                b[j]=(b[j]+b[j-(1<<i)])%mod;
            }
        }
    }
    for(int i=0;i<maxv;i++){
        k[i]=k[i]*f[i]%mod;
        b[i]=b[i]*f[i]%mod;
    }
    for(int i=0;i<K;i++){
        for(int j=maxv-1;j>=0;j--){
            if((1<<i)&j){
                k[j-(1<<i)]=(k[j-(1<<i)]+k[j])%mod;
                b[j-(1<<i)]=(b[j-(1<<i)]+b[j])%mod;
            }
        }
    }
    for(int i=1;i<=n;i++){
        cout<<(k[st[i]]*popc[st[i]]%mod+b[st[i]]+mod-n)%mod<<'\n';
    }
    return 0;
}
/*
2 2
1
1
*/
```

---

## 作者：Sharpsmile (赞：0)

### USACO24DEC P T1 题解

## 题面

给定集合序列 $A_i$，求出序列 $c_i=\sum\limits _{j}\frac{|A_i\cap A_j|}{|A_i\cup A_j|}$。

总元素个数 $k \leq 20$。$n\leq 10^5$。

## 解法

感觉上同时处理取交和取并感觉不简单。所以我们拆开交的贡献，我们枚举交的每个元素，只在包含元素 $k$ 的集合 $S_k=\{A_i|k\in A_i\}$中求 $c'_{k,i}=\begin{cases}\sum\limits _{j,A_j\in A_k}\frac{1}{|A_i\cup A_j|} & A_i\in S_k \\0 & A_i\not \in S_k\end{cases}$ 。接下来我们默认所有计算的范围都是在某个 $S_k$ 内部的。

感觉可以做一点容斥。你可以钦定 $S\cup T$ 是什么。先对他做一个高维前缀和。令 $c_S$ 为满足 $A_i\subseteq S$ 的集合数量。然后我们令 $g_{S,t}$ 表示满足 $|T|=t,T\subseteq S$ 的 $c_T$ 的和。这个用 $k$ 次高位后缀和可以做。然后会发现可以用 $g_S$ 求出 $f_S$。

我们按照 $t$ 从小到大求出 $f_{S,t}$。会发现对于一个实际贡献的 $|S\cup T|=t$ 的 $T$，他会在 “钦定 $|S\cup T|=w$” 的部分中产生 $\binom{k-t}{w-t}$ 的贡献，相当于在包含实际上的并的所有集合都会有额外的贡献。所以 $f_{S,t}=g_{S,t}-\sum\limits_{w<t}\binom{k-t}{w-t}f_{S,w}$。有了 $f_{S,t}$，我们直接把他以 $\frac{1}{t}$ 的系数加到对应的答案上就好了。

瓶颈在于要枚举 $k$ 个位，每次要做 $k$ 次高位后缀和。我们的复杂度是 $O(k^32^k)$ 的。

你把 $t$ 在后缀和那部分的维上不要分开，把他想成一个整体，不要用 “做 $k$ 次高位后缀和的角度思考”，当做就像是一个“多项式”。容斥我们相当于把一开始在 $i$ 的位置以 $p_{i,j}$ 的系数贡献到了 $j$ 上，然后按照 $\frac{1}{j}$ 的系数进行贡献。而且对于一个位置是否贡献只和 $S$ 有关，而和 $i,j$ 无关。

所以实际上初始在 $i$ 位置的数只是以 $h_i=\sum \frac{p_{i,j}}{j}$ 的系数贡献到了该贡献的答案上。我们不在关心这个 “多项式” 具体长什么样子。而只关心他的系数和。所以我们不用再做多次高位后缀和，一次就够了。

这个系数可以在 $O(k^3)$ 的复杂度内算出，很简单。我们现在降到了 $O(k^22^k)$ 了。已经完全可以通过了。

看官方题解还可以发现有另一种优化方法，注意到 $\frac{|A\cap B|}{|A\cup B|}=\frac{|A|+|B|}{|A\cup B|}-1$。我们不用再枚举交的位了，只需要按照 $\frac{1}{|A_i\cup A_j|}$ 和 $\frac{|A_j|}{|A_i\cup A_j|}$ 分别做一次即可。后者就是在求 $c$ 之前乘个系数就行了。

这个也可以做成 $O(k^22^k)$。两部分优化似乎并不冲突，用在一起就是 $O(k2^k)$ 的了。

---

