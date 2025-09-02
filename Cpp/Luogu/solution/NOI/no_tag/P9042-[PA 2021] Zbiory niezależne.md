# [PA 2021] Zbiory niezależne

## 题目描述

树 $T = (V, E)$ 是一个无向连通且无环的简单图。在本题中，我们考虑 $c$ 色树，即树上每个节点有 $c$ 种颜色之一的树。

两棵有色树 $T_1 = (V_1, E_1), T_2 = (V_2, E_2)$ 相等，当且仅当：

- 存在双射 $\pi : V_1 \to V_2$，满足对于任意节点对 $(u, v) \in V_1$，满足 $\{u,v\} \in E_1$ 当且仅当 $\{\pi(u), \pi(v)\} \in E_2$。
- 对于任意节点 $v \in V_1$，$T_1$ 中 $v$ 节点的颜色和 $T_2$ 中 $\pi(v)$ 节点的颜色相同。

我们称一棵树 $T = (V, E)$ 的一个独立集为任意节点的子集 $S \subseteq V$，满足 $S$ 中没有两不同节点被一条边相连。独立集 $S$ 的大小等于属于 $S$ 集合的节点个数。

给定三个整数 $l, r, c$，求问有多少不同的 $c$ 色树满足其最大独立集的大小在 $[l, r]$ 中？由于答案可能会非常大，所以请求出它对 $998244353$ 取模后的值。

## 说明/提示

对于 $100\%$ 的数据，$1 \leq l \leq r \leq 5 \times 10^5$，$1 \leq c \leq 998244352$。

## 样例 #1

### 输入

```
1 3 1```

### 输出

```
9```

## 样例 #2

### 输入

```
1 3 2```

### 输出

```
149```

# 题解

## 作者：Aleph1022 (赞：8)

注意这个最大独立集不带权，因此我们可以贪心：如果儿子都不在最大独立集中就将父亲选入最大独立集中。  
这样我们先记 $G, H$ 分别是根是否被选中的树的 OGF，借助 Polya Exp（$\operatorname{Exp}(F(x)) = \prod_{i\ge 1} \frac1{(1-x^i)^{f_i}} = \exp\left(\sum_{i\ge 1} \frac{F(x^i)}i\right)$）可以写出方程

$$
\begin{cases}
H = cx \operatorname{Exp}(G) \\
G = c \operatorname{Exp}(G+H) - c \operatorname{Exp}(G) \\
\end{cases}
$$

考虑在线卷积维护 $\operatorname{Exp}(G)$ 和 $\operatorname{Exp}(G+H)$，借助 P5900 的手法即可解决。

接下来我们依然考虑重心为根即可，不过官方题解使用的是本质相同的 Otter's Formula，或许更为方便。以下直接给出结论，设答案为 $F$，有

$$
F(x) = G(x) + H(x) - \frac12 G^2(x) + \frac12 G(x^2) - G(x) H(x) - \frac1{2x} H^2(x) + \frac1{2x} H(x^2)
$$

写了个 $O(n\log^2 n/\log\log n)$，开 O2 后在洛谷上最慢的点不超过 1.2s。

---

## 作者：yyyyxh (赞：1)

首先这看起来是一个无标号无根树计数的加强版，所以我们回忆一下我们在无标号无根树计数使用的一些技巧：

无标号有根树的生成函数 $F$ 满足方程 $F=x\mathcal E(F)$，$\mathcal E(F)$ 是 $F$ 的欧拉变换，其等于 $\prod_{i=1}^{+\infin} (1-x^i)^{-[x^i]F}=\exp(\sum_{i=1}^{+\infin} \frac{F(x^i)}{i})$，组合意义就是完全背包。欧拉变换可以考虑暴力维护出 $\sum_{i=1}^{+\infin}\frac{F(x^i)}{i}$，并且用在线卷积维护 $\exp$。

无根树的情况考虑钦定无根树强制其在根为它的重心时统计一次，还要注意处理有两个重心的情况。

这道题带上了颜色，但这只不过是给每次拼上的根多了几种状态，所以只是乘了个 $c$：$F=cx\mathcal E(F)$。

这个题还要求刻画最大独立集，但是树形最大独立集有一个很好的贪心求法：自底向上，能选就选。这样的话，对于一颗有根树，我们考虑直接记录运行贪心算法后根是否会被选（记 $F$ 为根被选了的生成函数，$G$ 为根没被选的生成函数），再记录被选的点的个数。可是我们如果同时记录树的大小和独立集大小复杂度就炸了，我们只能扔掉树的大小一维处理。

此时这道题有根树的情况就已经解决完了：

$$
\begin{equation}
\begin{cases}
F=cx\mathcal E(G) \\
G=c\mathcal E(F+G)-c\mathcal E(G)
\end{cases}
\end{equation}
$$

此处需要注意在线卷积的更新顺序，因为 $[x^i]G$ 会同时贡献到 $[x^i]\mathcal E(F+G),[x^i]\mathcal E(G)$，而计算 $[x^i]G$ 需要用到这两个位置，但是系数都是 $1$ 抵消了。

这个题我觉得的难点在于将无根树转成有根树的细节处理。因为你扔掉了树的大小一维，树的重心定义模糊不清。注意到我们实质上只需要找到一个在绝大多数无根树意义下“唯一”的位置，要求这个位置能用子树最大独立集大小刻画出来，然后特殊处理少量 case。

一个自然的想法是扩展重心的定义，也就是说改成关于所有在最大独立集中的点带权重心。我们看下这个选择什么情况下会有多个重心：

称贪心方案选了的点为黑点否则是白点，称根被选择的有根树是黑子树否则是白子树，那么带权重心有多个的情况实际上就是独立集等大的两个白子树通过一条链连起来，或者两个独立集的等大黑子树通过一个白点串起来。其它的情况不会出现，否则可以扩大最大独立集。

我们考虑直接规避有三个带权重心的第二种情况，修改带权重心的定义，当根为黑点时，我们认为如果根存在一个最大独立集不小于全局最大独立集一半的子树，就不认为它是重心，这样的话第二种情况你只会认为中间的白点是重心。

然而我在写暴力 DP 时发现上面这个想法问题可大了去了！最好捕捉到的其实就是 $l=r=1$ 时的谬误，两个点通过一条边串起来，此时取哪个点都不是重心。

出现这种情况的原因在于，上面关于“重心”的定义不是良定的，因为在根不同时，所有在贪心选出最大独立集中的点是不相同的！但仔细想想，这种情况只会在两个最大独立集等大的黑子树（黑子树是良定的，因为有根，这里的黑不代表其在全局最大独立集中会被选，而是代表在这颗子树贪心时根被选了）直接相连时产生，其它的情况考虑扰动根时，黑白点的变化是很小的。

所以说这个题我们只需要修正两个白子树直接相连（有两个“重心”）和两个黑子树直接相连（一个“重心”都没有）的贡献即可。

被 zhy 教育了：本来关于如何容斥掉不是重心的根的贡献的时候打算再写一个分治 NTT 的，后来 zhy 让我想想这个题为什么是求最大独立集在 $[l,r]$ 之间的和而不是让你输出每一个位置……大家猜猜为什么……

暴力实现欧拉变换和容斥的代码：

```cpp
#include <cstdio>
using namespace std;
const int P=998244353;
const int N=500003;
typedef long long ll;
int read(){ /* reading... */ }
int lim,n,c;
int f[N],g[N],tf[N],tg[N],res[N],inv[N];
inline void inc(int &x,int v){if((x+=v)>=P) x-=P;}
inline void dec(int &x,int v){if((x-=v)<0) x+=P;}
void add(int *w,int x,int v){
	for(int t=n;~t;--t)
		for(int i=1,j=x,cur=1;t+j<=n;++i,j+=x){
			cur=(ll)cur*inv[i]%P*(v+i-1)%P;
			w[t+j]=(w[t+j]+(ll)cur*w[t])%P;
		}
}
int main(){
	lim=read();n=read();c=read();inv[1]=1;tf[0]=tg[0]=1;
	for(int i=2;i<=n;++i) inv[i]=(ll)inv[P%i]*(P-P/i)%P;
	for(int i=1;i<=n;++i){
		f[i]=(ll)tf[i-1]*c%P;
		inc(g[i],(ll)(tg[i]+f[i])*c%P);
		dec(g[i],(ll)tf[i]*c%P);
		add(tf,i,g[i]);add(tg,i,(f[i]+g[i])%P);
	}
	for(int i=1;i<=n;++i){
		inc(res[i]=f[i],g[i]);
		for(int j=(i+1)>>1;j<i;++j) dec(res[i],(ll)g[j]*f[i-j]%P);
		for(int j=(i+2)>>1;j<=i;++j){
			dec(res[i],(ll)(f[j]+g[j])*g[i-j]%P);
			dec(res[i],(ll)f[j]*f[i-j+1]%P);
		}
	}
	for(int i=1;2*i<=n;++i) if(g[i]) dec(res[2*i],((ll)g[i]*(g[i]-1)>>1)%P);
	for(int i=1;2*i-1<=n;++i) if(f[i]) inc(res[2*i-1],((ll)f[i]*(f[i]+1)>>1)%P);
	int ans=0;
	for(int i=lim;i<=n;++i) inc(ans,res[i]);
	printf("%d\n",ans);
	return 0;
}
```

在线卷积代码：

```cpp
// orz zhy
#include <cstdio>
#include <algorithm>
#define ADD(arr) for(int i=mid+1;i<=r;++i) inc((arr)[i],C[i-l])
using namespace std;
const int P=998244353;
const int N=500003,M=1<<20;
typedef long long ll;
int read(){ /* reading... */ }
int qp(int a,int b=P-2){ /* quick power */ }
int lim,n,c,len,ilen,bt;
int f[N],g[N],af[N],ag[N],tf[N],tg[N],inv[N],sf[N],sg[N];
int rev[M],cw[M|1];
inline void inc(int &x,int v){if((x+=v)>=P) x-=P;}
inline void dec(int &x,int v){if((x-=v)<0) x+=P;}
void NTT(int *E){ /* DFT */ }
void INTT(int *E){ /* IDFT */ }
void init(int cur){ /* init NTT */ }
int A[M],B[M],C[M];
void convol(int *Al,int *Ar,int *Bl,int *Br){
	++Ar;++Br;
	int Ap=0,Bp=0;
	do A[Ap++]=*Al++;while(Al!=Ar);
	do B[Bp++]=*Bl++;while(Bl!=Br);
	NTT(A);NTT(B);
	for(int i=0;i<len;++i) C[i]=(ll)A[i]*B[i]%P,A[i]=B[i]=0;
	INTT(C);
}
void solve(int l,int r){
	if(l==r){
		tf[r]=(ll)(tf[r]+af[r])*inv[r]%P;tg[r]=(ll)(tg[r]+ag[r])*inv[r]%P;
		f[r]=(ll)tf[r-1]*c%P;g[r]=((ll)f[r]+tg[r]+P-tf[r])*c%P;
		int vf=(ll)r*g[r]%P,vg=(ll)r*(f[r]+g[r])%P;
		for(int t=r;t<=n;t+=r) inc(af[t],vf),inc(ag[t],vg);
		inc(tf[r],g[r]);inc(tg[r],f[r]);inc(tg[r],g[r]);
		return;
	}
	int mid=(l+r)>>1;
	solve(l,mid);init(r-l);
	convol(tf+l,tf+mid,af,af+min(r-l,mid));ADD(tf);
	convol(af+l,af+mid,tf,tf+min(r-l,l-1));ADD(tf);
	convol(tg+l,tg+mid,ag,ag+min(r-l,mid));ADD(tg);
	convol(ag+l,ag+mid,tg,tg+min(r-l,l-1));ADD(tg);
	solve(mid+1,r);
}
int main(){
	lim=read();n=read();c=read();inv[1]=1;tf[0]=tg[0]=1;
	for(int i=2;i<=n;++i) inv[i]=(ll)inv[P%i]*(P-P/i)%P;
	solve(1,n);
	for(int i=1;i<=n;++i) inc(sf[i]=f[i],sf[i-1]),inc(sg[i]=g[i],sg[i-1]);
	int ans=0;
	for(int i=lim;i<=n;++i) inc(ans,f[i]),inc(ans,g[i]);
	for(int i=(lim+1)>>1;2*i<=n;++i) if(g[i]) dec(ans,((ll)g[i]*(g[i]-1)>>1)%P);
	for(int i=(lim+2)>>1;2*i-1<=n;++i) if(f[i]) inc(ans,((ll)f[i]*(f[i]+1)>>1)%P);
	for(int i=1;i<=n;++i){
		int l=max(lim-i,1),r=min(n-i,i);
		if(l<=r) ans=(ans+(ll)(sf[l-1]-sf[r]+P)*g[i])%P;
		l=max(lim-i,0);r=min(n-i,i-1);
		if(l<=r){
			ans=(ans+(ll)(sg[l-1]-sg[r]+P)*(f[i]+g[i]))%P;
			ans=(ans+(ll)(sf[l]-sf[r+1]+P)*f[i])%P;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

