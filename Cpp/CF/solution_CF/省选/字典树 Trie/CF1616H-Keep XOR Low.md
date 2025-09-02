# Keep XOR Low

## 题目描述

You are given an array $ a_1, a_2, \ldots, a_n $ and an integer $ x $ .

Find the number of non-empty subsets of indices of this array $ 1 \leq b_1 < b_2 < \ldots < b_k \leq n $ , such that for all pairs $ (i, j) $ where $ 1 \leq i < j \leq k $ , the inequality $ a_{b_i} \oplus a_{b_j} \leq x $ is held. Here, $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR). As the answer may be very large, output it modulo $ 998\,244\,353 $ .

## 样例 #1

### 输入

```
4 2
0 1 2 3```

### 输出

```
8```

## 样例 #2

### 输入

```
3 6
4 2 2```

### 输出

```
7```

## 样例 #3

### 输入

```
4 0
1 1 2 2```

### 输出

```
6```

# 题解

## 作者：FZzzz (赞：28)

挺有意思的题。

考虑把所有数插进 trie 里，然后在 trie 上进行 dp 或者说递归求解。经典按位计算限制，设 $f_u$ 表示在 $u$ 子树内选若干个点，两两之间异或不大于 $x$ 的方案数。考虑转移，设 $u$ 代表的位是 $d$：
1. 若 $x$ 的第 $d$ 位为 $0$，则不能在两个子树内同时选数，那么直接把两个子树的 dp 值加起来就行了；
2. 若 $x$ 的第 $d$ 位为 $1$，则在同一个子树内选的数之间没有限制，但是在不同子树内选的数之间有限制。这个时候我们发现这个 dp 寄了！

那怎么办呢。我们不妨再大胆一点，直接把这两个互相有限制的点都设进状态里，$g_{u_1,u_2}$ 表示在 $u_1$ 和 $u_2$ 里各选若干个数，两两异或不大于 $x$ 的方案数。

这个 dp 看起来非常扯淡，因为可能我们会发现再讨论一下就是三个甚至四个点互相限制。我赛时直接没敢往下想，但其实如果你大胆去讨论了，那么接下来的一切会顺理成章：
1. 若 $x$ 的第 $d$ 位为 $1$，那么 $u_1$ 的左儿子和 $u_2$ 的左儿子的子树内的数异或起来一定不会大于 $x$ 了， $u_1$ 的右儿子和 $u_2$ 的右儿子也是一样。所以现在我们只需要考虑 $u_1$ 的左儿子和 $u_2$ 的右儿子，以及 $u_1$ 的右儿子和 $u_2$ 的左儿子之间的限制。那么直接把两个 $g$ 值乘起来；
2. 若 $x$ 的第 $d$ 位为 $0$，$u_1$ 的左儿子和 $u_2$ 的右儿子里就不能同时有数，$u_1$ 的右儿子和 $u_2$ 的左儿子同理。所以我们把 $u_1$ 的左儿子和 $u_2$ 的左儿子的 dp 值，以及 $u_1$ 的右儿子和 $u_2$ 的右儿子的 dp 值加起来。还有一种情况：如果我只在 $u_1$ 或 $u_2$ 的子树里选数，那么我可以任意选，这种情况也加上。

于是美妙的事情发生了：这个 dp 真的是可行的，互相限制的子树真的只有两个！那么我们解决了本题，复杂度分析也是容易的，每个点只会被经过一遍，所以总时间复杂度就是 trie 数的点数即 $O(n\log n)$。

dp 式有一些细节。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll readint(){
	ll x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)&&c!='-') c=getchar();
	if(c=='-'){
		f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxn=1.5e5+5;
int n,x,cnt=1,ch[maxn*40][2],sz[maxn*40];
void insert(int x){
	int u=1;
	sz[1]++;
	for(int i=30;i>=0;i--){
		bool k=x>>i&1;
		if(!ch[u][k]) ch[u][k]=++cnt;
		sz[u=ch[u][k]]++;
	}
}
const ll mod=998244353;
ll pw[maxn];
ll dfs(int u1,int u2,int d){
	if(!u1) return pw[sz[u2]];
	if(!u2) return pw[sz[u1]];
	if(u1==u2){
		if(d<0) return pw[sz[u1]];
		int lc=ch[u1][0],rc=ch[u1][1];
		if(x>>d&1) return dfs(lc,rc,d-1);
		else return (dfs(lc,lc,d-1)+dfs(rc,rc,d-1)-1+mod)%mod;//减 1 是因为空集被算了两遍
	}
	else{
		if(d<0) return pw[sz[u1]+sz[u2]];
		int lc1=ch[u1][0],rc1=ch[u1][1],lc2=ch[u2][0],rc2=ch[u2][1];
		if(x>>d&1) return dfs(lc1,rc2,d-1)*dfs(rc1,lc2,d-1)%mod;
		else{
			ll res=(dfs(lc1,lc2,d-1)+dfs(rc1,rc2,d-1)-1+mod)%mod;//这里减一同理
			res=(res+(pw[sz[lc1]]-1+mod)*(pw[sz[rc1]]-1+mod)%mod)%mod;
			res=(res+(pw[sz[lc2]]-1+mod)*(pw[sz[rc2]]-1+mod)%mod)%mod;
			//要保证每个子树里都有数，否则被上一种情况算过了
			return res;
		}
	}
}
int main(){
	#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	#endif
	n=readint();
	x=readint();
	for(int i=1;i<=n;i++) insert(readint());
	pw[0]=1;
	for(int i=1;i<=n;i++) pw[i]=pw[i-1]*2%mod;
	printf("%lld\n",(dfs(1,1,30)-1+mod)%mod);//题目里说非空，减掉空集
	#ifdef LOCAL
	fprintf(stderr,"%f\n",1.0*clock()/CLOCKS_PER_SEC);
	#endif
	return 0;
}
```

---

## 作者：feecle6418 (赞：13)

> 给你 $n$ 个整数 $a_1,a_2,\cdots,a_n$ 和一个整数 $x$。
>
> 你需要求出 $\{1,2,\cdots,n\}$ 的一个子集 $S$，满足 $S$ 中任意两个不同的元素 $i,j$，满足 $a_i~{\rm xor}~a_j\le x$。
>
> 求选取 $S$ 的方案数，对 $998244353$ 取模的结果。
>
> $1\le n\le 150000,0\le a_i<2^{30}$

（交错题了，重新提交一遍

简单题，但我不会。（场上估计要掉大分！！）

容易发现在 $x$ 最高位之上的位分隔开的集合不能同时选，分别算再加起来。

每个集合内部，分最高位 01 考虑，需要解决如下问题：

- 有两个集合 $A,B$，你需要选一个 $A$ 的非空子集 $S$、$B$ 的非空子集 $T$，使得 $\forall i\in S,j\in T$，$i\mathrm{\ xor\ }j\le x$，求方案数。

设方案数为 $f(A,B,x)$。

对 $x$ 的最高位分类讨论。

设 $A$ 中这一位为 $0,1$ 的集合分别为 $A0,A1$，$B$ 中这一位为 $0,1$ 的集合分别为 $B0,B1$。

- 为 $0$，那么答案就是 $f(A0,B0,x)+f(A1,B1,x)$。

- 为 $1$，粗看好像设计不出什么简洁的形式……

  ~~经过阅读题解，~~ 惊奇地发现 $A0,B1$，$A1,B0$ 两边是独立的！

  这非常显然，选择其中一边的某个数不会对另一边任何数能否造成影响。

  于是答案就是 $f(A1,B0,x-highbit(x))f(A0,B1,x-highbit(x))$，加上一些集合为空的边界。

复杂度 $O(n\log a_i)$。

整个题唯一难点在于发现 $f$ 递归计算的方式，特别是 **独立** 这个结论，非常简洁优美。

---

## 作者：DengDuck (赞：13)

我认为是一道很好的题。

首先构建一棵 Trie 树。

$sz_i$ 表示 $i$ 子树表示了多少个元素。

$S(x)$ 表示 $x$ 子树中所有的选择方案，不一定可行，所以有 $S(x)=2^{sz_x}-1$。

$i_l,i_r$ 表示 $i$ 的左儿子和右儿子。

我们设 $f_{i,j}$ 表示在子树 $i,j$ 中选择，两边都强制选的方案数。

考虑边界条件，在叶节点时：

$$
f_{i,j}=\begin{cases}sz_i (i=j)\\sz_i\times sz_j(i\not=j)\end{cases}
$$

否则我们看这个限制条件 $X$ 当前位。

如果为 $0$，那么两边的子树显然只能选择同侧，也就是：

$$
f_{i,j}=f_{i_{l},j_{l}}+f_{i_{r},j_{r}}
$$

如果为 $1$，情况很复杂。

如果 $i=j$，那么异侧需要讨论，同侧直接随便选，答案为 $f_{i_l,i_r}+S(i_l)+S(i_r)$。

否则：

- 首先同侧肯定随便选了 $S(i)\times S(j)$。
- 只选择异侧的情况 $f_{i_l,j_r}+f_{i_r,j_l}$。
- 一边两个子树都选，一边只选一个子树 $f_{i_l,j_r}\times (S(i_r)+S(j_l))+f_{i_r,j_l}\times (S(i_l)+S(j_r))$。
- 两边异侧的情况可以相乘，表示四个子树都选 $f_{i_l,j_r}\times f_{i_r,j_l}$。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=3e5;
const LL mod=998244353;
LL n,X,tot,a[N],rt;
LL ksm(LL x,LL y)
{
	LL ans=1;
	while(y)
	{
		if(y&1)ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans;
}
struct node
{
	LL son[2],sz;
}t[N*30];
void ins(LL &rt,LL x,LL k)
{
	if(rt==0)rt=++tot;
	t[rt].sz++;
	if(k<0)return;
	if(x&(1<<k))ins(t[rt].son[1],x,k-1);
	else ins(t[rt].son[0],x,k-1);
}
LL S(LL x)
{
	return (ksm(2,t[x].sz)-1+mod)%mod;
}
LL dfs(LL x,LL y,LL k)
{
	if(!x||!y)return 0;
	if(k<0)
	{
		if(x==y)return S(x);
		return S(x)*S(y)%mod;
	}
	LL xl=t[x].son[0],xr=t[x].son[1],yl=t[y].son[0],yr=t[y].son[1],ans=0;
	if(X&(1<<k))
	{
		if(x==y)return (dfs(xl,xr,k-1)+S(xl)+S(xr))%mod;
		ans=(S(xl)*S(yl)%mod+S(xr)*S(yr)%mod)%mod;
		LL t1=dfs(xl,yr,k-1),t2=dfs(xr,yl,k-1);
		ans=(ans+t1+t2+t1*t2%mod)%mod;
		ans=(ans+t1*(S(xr)+S(yl))%mod)%mod;
		ans=(ans+t2*(S(xl)+S(yr))%mod)%mod;
	}
	else ans=(dfs(xl,yl,k-1)+dfs(xr,yr,k-1))%mod;
	return ans;
}
int main()
{
	scanf("%lld%lld",&n,&X);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		ins(rt,a[i],30);
	}
	cout<<dfs(rt,rt,30)<<endl;
	return 0;
}
```

最后贴上本文的 [参考题解](https://www.cnblogs.com/EricQian/p/16872419.html)。

---

## 作者：老莽莽穿一切 (赞：8)

[更好的阅读体验](https://www.cnblogs.com/LaoMang-no-blog/p/16399513.html)

---

[**CF link**](https://codeforces.com/problemset/problem/1616/H)

[**你谷 link**](https://www.luogu.com.cn/problem/CF1616H)

首先看到**两两异或**问题，考虑先把集合放在字典树上。

本着求什么设什么的原则，我们设 $f_x$ 表示 $x$ 的子树里满足要求的集合数，然后我们来试着转移一下：

- 当前位为 $0$ 时，我们不能只能在同侧子树中选，则 $f_x=f_{x_0}+f_{x_1}$（$x_0,x_1$ 分别表示 $x$ 的左右儿子编号）。
- 当前位为 $1$ 时，我们同侧子树中选择没有约束，但是异侧子树之间存在约束，而我们的 dp 状态只能接受一棵子树内部约束，所以得考虑重设状态。

我们重新设一个合理但又不合理的状态，考虑到当前位为 $1$ 时会产生异侧子树之间的互相约束，我们设 $f_x$ 表示 $x$ 子树里满足要求的集合数，再额外设一个 $g_{x,y}$ 表示 $x,y$ 子树里满足要求的集合数（强制要求 $x\ne y$），我们可以再考虑转移。

- 若当前位为 $0$：

$$
f_x=f_{x_0}+f_{x_1}-1
$$
$$
g_{x,y}=(g_{x_0,y_0}+g_{x_1,y_1}-1)+(2^{\mathrm{size}_{x_0}}-1)(2^{\mathrm{size}_{x_1}}-1)+(2^{\mathrm{size}_{y_0}}-1)(2^{\mathrm{size}_{y_1}}-1)
$$

- 若当前位为 $1$：

$$
f_x=g_{x_0,x_1}
$$
$$
g_{x,y}=g_{x_0,y_1}\times g_{x_1,y_0}
$$

答案是 $f_{\mathrm{root}}-1$。

我们来一个一个解释转移方程。

首先是 $f_x$ 的转移，当前位为 $0$ 时，我们不能在异侧子树中选数，故要么从左子树选，要么从右子树选，故两边加和，同时因为加和的过程中空集被算了两次。当前位为 $1$ 时，**同侧子树中选数没有要求**，异侧子树互相约束，根据定义即 $g_{x_0,x_1}$。

再来看 $g_{x,y}$ 的转移，首先我们应当明确一点，$g_{x,y}$ 的询问中，$x,y$ 子树内部选点之间不存在约束，这样的话两个转移也就很明显了，当前位为 $0$ 时，$x$ 与 $y$ 的异侧不能同时选点，所以是分别将同侧选点的方案加起来，同样的减去 $1$ 的空集贡献，后面部分，因为我们在询问 $g_{x_0,y_0}$ 和 $g_{x_1,y_1}$ 时还会再统计$x_0,x_1,y_0,y_1$ **单个子树内部选点的方案数**，所以要保证当前我们统计时不存在只在单侧选点的情况，故统计时还需加上 $(2^{\mathrm{size}_{x_0}}-1)(2^{\mathrm{size}_{x_1}}-1)+(2^{\mathrm{size}_{y_0}}-1)(2^{\mathrm{size}_{y_1}}-1)$。

时间复杂度分析方面，我们发现对于每个节点 $x$，它只会被 $f_x$ 遍历或存在一个唯一的 $y$ 被 $g_{x,y}$ 遍历，故时间复杂度正确，为 $\mathcal O\left(n\log|V|\right)$。

[代码](https://codeforces.com/contest/1616/submission/167919021)就相对简单多了。

---

## 作者：Kubic (赞：5)

首先建出 01Trie。

设 $k$ 满足 $2^k\le x< 2^{k+1}$，那么选出的所有数的比 $2^k$ 更高的位都是一样的。

第一种情况：选出的所有数 $2^k$ 位都是一样的。

这种情况比较简单，拿出所有满足这个条件的子树，每一个子树内部都可以任意选取，方案数 $2^{size}-1$。

第二种情况：存在两个选出的数，使得他们 $2^k$ 位不一样。

那么当前选出的数一定在 $p,q$ 两个节点的子树里面，其中 $p$ 子树中所有数 $2^k$ 位都是 $0$，$q$ 子树中所有数 $2^k$ 位都是 $1$。

设 $p_0,p_1$ 分别为 $p$ 的左儿子和右儿子，$q_0,q_1$ 分别为 $q$ 的左儿子和右儿子。

再设 $f(p,q)$ 表示 $p,q$ 子树中都至少选一个数的满足条件的方案数，$g(p)$ 表示 $p$ 子树中任意选出至少一个数的方案数，即 $2^{size_p}-1$。

考虑 $2^{k-1}$ 位：

- 如果 $x$ 的 $2^{k-1}$ 位是 $0$，那么两边选的数的 $2^{k-1}$ 位一定相同，即 $f(p,q)=f(p_0,q_0)+f(p_1,q_1)$
- 如果 $x$ 的 $2^{k-1}$ 位是 $1$，那么：

	- 如果两边都既有 $0$ 又有 $1$ 那么方案数是 $(p_0,q_1)f(p_1,q_0)$
   - 如果有一边既有 $0$ 又有 $1$，另一边只有 $0$ 或 只有 $1$，那么方案数是 $f(p1_0,p2_1)(g(p_1)+g(q_0))+f(p_1,q_0)(g(p_0)+g(q_1))$
   - 如果两边都只有 $0$ 或只有 $1$，那么方案数是 $f(p_0,q_1)+f(p_1,q_0)+g(p_0)g(q_0)+g(p_1)g(q_1)$
   
具体意义可以自己手推一下，应该比较容易。

那么我们可以仿照这个做法递归下去，就可以求出答案。

时间复杂度 $O(n\log w)$。其中 $w$ 是值域。

参考代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 150005
#define M 5000005
#define MOD 998244353
int n,m,cntP=1,a[N],w[N];struct Point {int vl,ch[2];}pt[M];
int add(int x,int y) {x+=y;return x<MOD?x:x-MOD;}
void ins(int vl)
{
	int p=1;++pt[p].vl;
	for(int i=29,t;i>=0;--i) {t=vl>>i&1;if(!pt[p].ch[t]) pt[p].ch[t]=++cntP;p=pt[p].ch[t];++pt[p].vl;}
}
int dfs(int p1,int p2,int d)
{
	if(!p1 && !p2) return 0;if(d<0) return p1==p2?w[pt[p1].vl]:1ll*w[pt[p1].vl]*w[pt[p2].vl]%MOD;
	if(m>>d&1)
	{
		if(p1==p2) return add(dfs(pt[p1].ch[0],pt[p2].ch[1],d-1),add(w[pt[pt[p1].ch[0]].vl],w[pt[pt[p2].ch[1]].vl]));
		int t1=dfs(pt[p1].ch[0],pt[p2].ch[1],d-1),t2=dfs(pt[p1].ch[1],pt[p2].ch[0],d-1),res=1ll*t1*t2%MOD;
		res=add(res,1ll*t1*add(w[pt[pt[p1].ch[1]].vl],w[pt[pt[p2].ch[0]].vl])%MOD);
		res=add(res,1ll*t2*add(w[pt[pt[p1].ch[0]].vl],w[pt[pt[p2].ch[1]].vl])%MOD);
		res=add(res,1ll*w[pt[pt[p1].ch[0]].vl]*w[pt[pt[p2].ch[0]].vl]%MOD);
		res=add(res,1ll*w[pt[pt[p1].ch[1]].vl]*w[pt[pt[p2].ch[1]].vl]%MOD);return add(res,add(t1,t2));
	}return add(dfs(pt[p1].ch[0],pt[p2].ch[0],d-1),dfs(pt[p1].ch[1],pt[p2].ch[1],d-1));
}
int main()
{
	scanf("%d %d",&n,&m);for(int i=1,vl;i<=n;++i) w[i]=add(w[i-1],w[i-1]+1),scanf("%d",&vl),ins(vl);
	printf("%d\n",dfs(1,1,29));return 0;
}
```

---

## 作者：LZDQ (赞：1)

搞了一两天了，看题解没看懂在扯什么，最后还是自己用 01trie 做出来了，皆大欢喜！！

考虑在 01trie 上选点的过程。在 $x$ 的最高位处开始分叉，这时候可以在左右子树都选至少一个数使得 左边的异或右边的不超过 $x$，或者只选左/右边。也就是我们需要设计一个 DP，$f_{i,j}$ 表示在这两棵子树内都选至少一个点使得异或和的后若干位不超过 $x$ 的方案数。

不难发现每个 $i$ 会唯一对应一个 $j$，令 $p_u$ 表示对应到的点。然后分几种情况。

* $x$ 当前位为 1，$u,p_u$ 一共 4 棵子树，可以都选、选 $lc_u,rc_{p_u}$ 同时在 $rc_u,lc_{p_u}$ 中选至多一棵子树、反过来、两组都选恰好一棵子树。
* $x$ 当前位为 0，$f_u=f_{lc_u}+f_{rc_u}$
* 叶子结点，$f_u=(2^{siz_u}-1)\times(2^{siz_{p_u}}-1)$
* $x$ 的最高位，对答案的贡献为 $f_{rc_u}+(2^{siz_{lc_u}}-1)+(2^{siz_{rc_u}}-1)$  （此处应有 $f_{lc_u}=f_{rc_u}$）

这种做法适用于 $<x$，因为懒得处理（也可能不能处理） $\le x$ 所以可以手动把 $x$ 后面填 1，其他数后面填 0。

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cassert>
using namespace std;
typedef long long ll;
const int MAXN=5e6,mod=998244353;
#define lc ch[u][0]
#define rc ch[u][1]
int n,x,cntp=1,ch[MAXN][2],siz[MAXN],p[MAXN],f[MAXN];
int ans;
ll pw[MAXN];
void Dfs(int u,int d){
	if(d<0){
		f[u]=(pw[siz[u]]-1)*(pw[siz[p[u]]]-1)%mod;
		return ;
	}
	int t=x>>d&1;
	if(lc){
		p[lc]=ch[p[u]][t];
		Dfs(lc,d-1);
	}
	if(rc){
		p[rc]=ch[p[u]][t^1];
		Dfs(rc,d-1);
	}
	if(t) f[u]=(1ll*f[lc]*f[rc]%mod+(pw[siz[rc]]+pw[siz[ch[p[u]][0]]]-1)%mod*f[lc]+(pw[siz[lc]]+pw[siz[ch[p[u]][1]]]-1)%mod*f[rc]+
			(pw[siz[lc]]-1)*(pw[siz[ch[p[u]][0]]]-1)%mod+(pw[siz[rc]]-1)*(pw[siz[ch[p[u]][1]]]-1)%mod)%mod;
	else f[u]=(f[lc]+f[rc])%mod;
	if(t&&u==p[u]) ans=(ans+f[rc]+pw[siz[lc]]+pw[siz[rc]]-2)%mod,assert(f[lc]==f[rc]);
	return ;
}
int main(){
	//freopen("in","r",stdin);
	scanf("%d%d",&n,&x);
	pw[0]=1;
	for(int i=1; i<=n; i++)
		pw[i]=pw[i-1]*2%mod;
	x=x<<1|1;
	while(n--){
		int a;
		scanf("%d",&a);
		a<<=1;
		int u=1;
		for(int i=30; ~i; i--){
			int t=a>>i&1;
			if(!ch[u][t]) ch[u][t]=++cntp;
			u=ch[u][t];
			siz[u]++;
		}
	}
	p[1]=1;
	Dfs(1,30);
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：tribool4_in (赞：0)

比较有意思的题。不过感觉自己做法比较混乱。

首先令 $x$ 的最高位为第 $m$ 位，按照高于 $m$ 位的前缀，将 $a$ 分成若干组。显然 $S$ 必然是其中某组的子集，否则可以产生出高于 $m$ 位的值，一定不合法。

于是对于每一组数，只保留低 $m$ 位，将其插入 01-Trie，然后从高位往低位考虑。下文中 $ls_u$ 指左子树（0 子树），$rs_u$ 指右子树（1 子树）。

首先对于最高位，$x$ 的该位显然为 $1$。此时若只取 0 子树或 1 子树内部的子集一定合法。否则选出的 $S$ 集合同时包含两棵子树内的数。考虑递归解决，设 $f(u,v,k)$ 表示此时前 $k-1$ 位都与 $x$ 相同，$u$ 和 $v$ 子树内都必须选出至少一个数的合法集合方案数。

考虑 $x$ 的第 $k$ 位。若为 $0$，则下一位两子树必须取相同的，于是有 $f(u,v,k)=f(ls_u,ls_v,k+1)+f(rs_u,rs_v,k+1)$。

若为 $1$，考虑若 $S$ 中当前位均相同，则剩余的位置可以乱填，贡献形如 $(2^{siz_{ls_u}}-1)(2^{siz_{ls_v}}-1)+(2^{siz_{rs_u}}-1)(2^{siz_{rs_v}}-1)$；若 $u$、$v$ 分别取不同子树，贡献形如 $f(ls_u,rs_v,k+1)+f(rs_u,ls_v,k+1)$；此外还有可能 $u$ 或 $v$ 的两个子树都取，应当注意到 $u$ 或 $v$ 内部的数异或后一定不会大于 $x$（因为其前 $k-1$ 位相同），可以用前面的信息简单计算。具体可以看代码。

叶子节点答案显然为 $(2^{siz_u}-1)(2^{siz_v}-1)$。没什么边界，就是式子比较诡异。

注意特判当 $x=0$ 时的情况。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1.5e5 + 10, mod = 998244353;
int n, m, x, a[N], pw2[N];
map<int, vector<int>> mp;
struct Trie {
    int ch[N * 30][2], siz[N * 30], tot = 1;
    void clear() { fill(&ch[0][0], &ch[tot + 1][0], 0), fill(&siz[0], &siz[tot + 1], 0), tot = 1; }
    void insert(int x, int mk) {
        int u = 1;
        siz[u] += 1;
        for (int i = mk; i >= 0; i--) {
            int c = x >> i & 1;
            if (!ch[u][c]) ch[u][c] = ++tot;
            u = ch[u][c], siz[u] += 1;
        }
    }
    int solve(int a, int b, int x, int k) {
        if (!a || !b) return 0;
        if (k < 0) return 1ll * (pw2[siz[a]] - 1) * (pw2[siz[b]] - 1) % mod;
        int res = 0;
        if (x >> k & 1) {
            int L = solve(ch[a][0], ch[b][1], x, k - 1), R = solve(ch[a][1], ch[b][0], x, k - 1);
            (res += 1ll * (pw2[siz[ch[a][0]]] - 1) * (pw2[siz[ch[b][0]]] - 1) % mod) %= mod;
            (res += 1ll * (pw2[siz[ch[a][1]]] - 1) * (pw2[siz[ch[b][1]]] - 1) % mod) %= mod;
            (res += L) %= mod, (res += R) %= mod;
            (res += 1ll * L * (pw2[siz[ch[b][0]]] - 1 + pw2[siz[ch[a][1]]] - 1) % mod) %= mod, (res += 1ll * R * (pw2[siz[ch[a][0]]] - 1 + pw2[siz[ch[b][1]]] - 1) % mod) %= mod;
            (res += 1ll * L * R % mod) %= mod;
        } else {
            (res += solve(ch[a][0], ch[b][0], x, k - 1)) %= mod, (res += solve(ch[a][1], ch[b][1], x, k - 1)) %= mod;
        }
        return res;
    }
} t;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> x;
    for (int i = pw2[0] = 1; i <= n; i++) pw2[i] = pw2[i - 1] * 2ll % mod;
    m = (x == 0 ? 0 : __lg(x) + 1);
    for (int i = 1; i <= n; i++) cin >> a[i], mp[a[i] >> m].push_back(i);
    int ans = 0;
    for (auto &[h, l] : mp) {
        if (m == 0) {
            (ans += (pw2[l.size()] - 1 + mod) % mod) %= mod;
            continue;
        }
        t.clear();
        for (auto i : l) t.insert(a[i], m - 1);
        (ans += (pw2[t.siz[t.ch[1][0]]] - 1 + mod) % mod) %= mod, (ans += (pw2[t.siz[t.ch[1][1]]] - 1 + mod) % mod) %= mod;
        (ans += t.solve(t.ch[1][0], t.ch[1][1], x, m - 2)) %= mod;
    }
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：EXODUS (赞：0)

# Part 1：前言
超级计数好题，主打的就是一个敢设状态。

# Part 2：正文
首先看到两两异或建出 01-trie 套路变成按位考虑，下文设 $l(i)$ 表示 $i$ 的左子树，$r(i)$ 表示 $i$ 的右子树。

尝试一个 dp，设 $f_i$ 表示以 $i$ 为根的子树的答案，那么对于一个位置 $i$，若 $x$ 的第 $i$ 位为 $0$，我们有转移 $f_i=f_{l(i)}+f_{r(i)}$。但是 $x$ 为 $1$ 就似了，因为这不是个子问题。

怎么办？考虑能不能继续往状态里扔垃圾。我们再加一个点，$f_{i,j}$ 表示考虑在 $i,j$ 的子树中选若干个数的答案，那么还是首先考虑边界，如果当前到达叶节点，有 $f_{i,j}=2^{siz_i+[i\neq j]siz_j}$，其中 $siz_i$ 表示 $i$ 的子树中点的数量。

现在考虑转移，对于当前的位置 $dep$，我们考虑如下转移：

- $x$ 的第 $dep$ 为 $0$。

  - $i=j$。

    这个时候只能选一侧子树，然后合并答案，有 $f_{i,j}=f_{l(i),l(i)}+f_{r(i),r(i)}-1$。

  - $i\neq j$。

    此时对于每颗子树的子树内任选，对于两颗子树之间，一定只能是 $l(i)$ 配对 $r(i)$ 或 $l(j)$ 配对 $r(j)$，转移即 $f_{i,j}=(2^{siz(l(i))}-1)(2^{siz(r(i))}-1)+(2^{siz(l(j))}-1)(2^{siz(r(j))}-1)+f_{l(i),l(j)}+f_{r(i),r(j)}-1$。

- $x$ 的第 $dep$ 为 $1$。

  - $i=j$。

    此时子树内任选，有 $f_{i,j}=f_{l(i),r(i)}$。

  - $i\neq j$。

    此时可以随便选，有 $f_{i,j}=f_{l(i),r(j)}f_{r(i),l(j)}$。

注意要考虑一些空集的边界情况。
# Part 3：代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,l,r) for(int i(l);i<=(r);++i)
#define per(i,r,l) for(int i(r);i>=(l);--i)
#define eb emplace_back
#define Debug(...) fprintf(stderr,__VA_ARGS__)
int read(){
	int ans=0,flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	return ans*flg;
}
template<typename T>
void read(T &x){
	x=0;T flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	x*=flg;
}
template<typename T,typename... Args>
void read(T &x,Args &...args){read(x),read(args...);}
const int N=2e5+7,mod=998244353;
int pw[N];
struct Trie{
#define ls(u) t[u].son[0]
#define rs(u) t[u].son[1]
	struct Tree{
		int son[2];
		int siz;
	}t[N*30];
	int tot;
	Trie(){tot=1;}
	void ins(int v){
		++t[1].siz;
		for(int i=30,u=1,bit;i>=0;i--){
			bit=((v>>i)&1);
			if(!t[u].son[bit])t[u].son[bit]=++tot;
			++t[u=t[u].son[bit]].siz;
		}
	}
	void dfs(int u){
		if(!u)return;
		Debug("%d(%d)->(%d,%d)\n",u,t[u].siz,ls(u),rs(u));
		dfs(ls(u)),dfs(rs(u));
	}
	int dfs(int u,int v,int dep,int lim){
		if(!u||!v)return pw[t[u|v].siz];
		if(u==v){
			if(dep<0)
				return pw[t[u].siz];
			if((lim>>dep)&1)
				return dfs(ls(u),rs(u),dep-1,lim);
			else
				return ((ll)dfs(ls(u),ls(u),dep-1,lim)+dfs(rs(u),rs(u),dep-1,lim)+mod-1)%mod;
		}else{
			if(dep<0)
				return pw[t[u].siz+t[v].siz];
			if((lim>>dep)&1)
				return (ll)dfs(ls(u),rs(v),dep-1,lim)*dfs(rs(u),ls(v),dep-1,lim)%mod;
			else
				return ((ll)(pw[t[ls(u)].siz]-1)*(pw[t[rs(u)].siz]-1)%mod
					   +(ll)(pw[t[ls(v)].siz]-1)*(pw[t[rs(v)].siz]-1)%mod
					   +dfs(ls(u),ls(v),dep-1,lim)+dfs(rs(u),rs(v),dep-1,lim)+mod-1)%mod;
		}
		return assert(0),0;
	}
#undef ls
#undef rs
}trie;
int n,v,a[N];
int main(){
	read(n,v);pw[0]=1;
	for(int i=1;i<=n;i++)read(a[i]),trie.ins(a[i]);
	for(int i=1;i<=n;i++)pw[i]=(pw[i-1]<<1)%mod;
	// trie.dfs(1);
	printf("%d\n",(trie.dfs(1,1,30,v)+mod-1)%mod);
	return 0;
}
```

---

