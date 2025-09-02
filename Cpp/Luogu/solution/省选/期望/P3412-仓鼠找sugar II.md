# 仓鼠找sugar II

## 题目描述

小仓鼠和他的基（mei）友（zi）sugar 住在地下洞穴中，每个节点的编号为 $1\sim n$ 间的一个整数。地下洞穴是一个树形结构（两个洞穴间距离为 $1$）。这一天小仓鼠打算从从他的卧室 $a$（**是任意的**）走到他的基友卧室 $b$（还**是任意的**）（注意，$a$ 有可能等于 $b$）。然而小仓鼠学 OI 学傻了，不知道怎么怎么样才能用最短的路程走到目的地，于是他只能随便乱走。当他在一个节点时，会等概率走到这个点的母亲或者所有孩子节点（例如这个节点有一个母亲节点和两个子节点，那么下一步走到这 $3$ 个节点的概率都是 $\dfrac{1}{3}$），一旦走到了他基友的卧室，就会停下。

现在小仓鼠希望知道，他走到目的地时，走的步数的期望。这个期望本来是一个有理数，但是为了避免误差，我们要求输出这个有理数对 $998,244,353$ 取模的结果。

形式化地说，可以证明答案可以被表示为既约分数 $\dfrac{y}{x}$，其中 $x\not\equiv 0\pmod {998,244,353}$。可以证明存在一个唯一的整数 $z$（$0\le z\lt 998,244,353$），使得 $xz=y$，你只需要输出 $z$ 的值。


小仓鼠那么弱，还要天天被 JOHNKRAM 大爷虐，请你快来救救他吧！

## 说明/提示

样例解释：期望的真实值为 $\dfrac {16}{9}$。

如果 $a$ 是叶子，$b$ 是根，此时期望 $\mathbb{E}_1=1$，有 $2$ 种情况。

如果 $a$ 是根，$b$ 是叶子，则 $\displaystyle \mathbb{E}_2=\frac{1}{2}+\frac{3}{4}+\frac{5}{8}+\cdots=3$。有 $2$ 种情况。

如果 $a,b$ 是不同的叶子，则 $\mathbb{E}_3=\mathbb{E}_2+1=4$。有 $2$ 种情况。

如果 $a=b$，则 $\mathbb{E}_4=0$。有 $3$ 种情况。

所以答案为 $\displaystyle \frac{2\times 1+2\times 3+2\times 4+3\times 0}{2+2+2+3}=\frac{16}{9}$。

由于 $110,916,041\times 9=998,244,369\equiv 16\pmod {998,244,353}$，所以输出 $110,916,041$。

对于 $30\%$ 的数据，$n\le 5$；

对于 $50\%$ 的数据，$n\le 5000$；

对于所有数据，$n\le 100000$。

$\text{Statement fixed by @Starrykiller.}$

## 样例 #1

### 输入

```
3
1 2
1 3
```

### 输出

```
110916041```

# 题解

## 作者：学哥 (赞：24)

因为这一道题中的起点和终点都是不确定的，不好统计

于是**先考虑终点固定的情况**，此时我们把终点当作整棵树的$root$，**在$O(n)$算法之前的陈述中，直接以根节点代指终点，不做说明**

那么设$f[x]$表示节点$x$向根节点方向(即父亲方向)移动一步的概率

我们可以推出如下式子:

对于叶子节点:$f[leaf]=1$(只要再走一步就一定会走到其父亲)

对于根节点:$f[root]=0$(根本就不需要走)

对于其余节点(设$d[x]$表示其度数):$$f[x]=1+\frac{1}{d[x]}\times\sum_{son\in x}{(f[son]+f[x])}$$(有$\frac{1}{d[x]}$的概率走到$x$的儿子节点，再走回来)

上面的第三个式子再推一下:

$$f[x]=1+\frac{1}{d[x]}\times\sum_{son\in x}{f[son]}+\frac{d[x]-1}{d[x]}\times f[x]$$

$$\frac{1}{d[x]}\times f[x]=1+\frac{1}{d[x]}\times\sum_{son\in x}{f[son]}$$

$$f[x]=d[x]+\sum_{son\in x}{f[son]}$$

这样就比较好求了，因为对于每一个结点$x$，有$sz[x]$个点必须经过它才能到达终点，

那么直接根据这个树形DP$n$次，每次中推出$f[x]$然后$ans+=\sum_{i=1}^{n}f[i]\times sz[i]$($sz[i]$表示子树大小)就可以获得50分

接下来考虑$O(n)$的算法，稍作改进即可(接下来要说明的根节点和终点会有所不同)

我们**考虑在所有情况下的$f[x],sz[x]$及其贡献**

先以1号节点为根建立一棵有根树，对于每个节点维护其子树大小($s[x]$)和子树内度数和($sumd[x]$),并令$totd=\sum_{i=1}^{n}d[i]$

该节点就是终点点:$f[x]=0$，$sz[x]=n$,一次

终点在该节点的某一个儿子的子树$v$中：$f[x]=totd-sumd[v]$,$sz[x]=n-s[v]$,$s[v]$次

终点不在该节点的某一个儿子的子树中:
$f[x]=sumd[x]$,$sz[x]=s[v]$,$n-s[u]$次

最后对于每一个节点直接统计即可

```cpp
#include<bits/stdc++.h>
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<cstring>
#include<complex>
#include<vector>
#include<cstdio>
#include<string>
#include<bitset>
#include<cmath>
#include<queue>
#include<stack>
#include<map>
#include<set>
#define mp make_pair
#define pb push_back
#define RG register
#define il inline
using namespace std;
typedef unsigned long long ull;
typedef vector<int>VI;
typedef long long ll;
typedef double dd;
const dd eps=1e-10;
const int mod=998244353;
const int N=100010;
const int M=90000;
il ll read(){
	RG ll data=0,w=1;RG char ch=getchar();
	while(ch!='-'&&(ch<'0'||ch>'9'))ch=getchar();
	if(ch=='-')w=-1,ch=getchar();
	while(ch<='9'&&ch>='0')data=data*10+ch-48,ch=getchar();
	return data*w;
}

il ll poww(ll a,ll b){
	RG ll ret=1;
	for(a%=mod;b;b>>=1,a=a*a%mod)if(b&1)ret=ret*a%mod;
	return ret;
}

il void file(){
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
}

int n,rev,head[N],d[N],p[N],nxt[N<<1],to[N<<1],cnt,totd,ans;
il void add(int u,int v){
	to[++cnt]=v;
	nxt[cnt]=head[u];
	head[u]=cnt;
	d[v]++;
}

int sz[N],fa[N];
il void dfs(int u,int f){
	sz[u]=1;fa[u]=f;
	for(RG int i=head[u];i;i=nxt[i]){
		RG int v=to[i];if(v==f)continue;
		dfs(v,u);sz[u]+=sz[v];d[u]+=d[v];
	}
}

int main()
{
	file();
	n=read();rev=poww(1ll*n*n%mod,mod-2);
	for(RG int i=1,u,v;i<n;i++){
		u=read();v=read();
		add(u,v);add(v,u);
	}

	for(RG int i=1;i<=n;i++)totd+=d[i];
	dfs(1,0);
	
	for(RG int u=1;u<=n;u++)
		for(RG int i=head[u];i;i=nxt[i]){
			RG int v=to[i];
			if(v==fa[u]){
				ans=(ans+1ll*d[u]*sz[u]%mod*(n-sz[u])%mod)%mod;
			}
			else{
				ans=(ans+1ll*(totd-d[v])*(n-sz[v])%mod*sz[v]%mod)%mod;
			}
		}

	
	printf("%lld\n",1ll*ans*rev%mod);
	return 0;
}

```

---

## 作者：Rui_R (赞：16)

题意：给定一棵树，结点数为 $n$，一个人从起点 $s$ 出发，在上面等概率选当前能走的边走，直到走到终点 $t$ 。$s,t$ 未知。求他所经过边数的期望。

[原题](https://www.luogu.com.cn/problem/P3412)

令 $d_u$ 表示结点 $u$ 的度数，$f_u$ 表示 $u \to fa(u)$ 的期望步数，其中 $u \ne \text{root}$，$f_{\text{root}}$ 没有定义

$$
f_u = \frac{1}{d_u} [1+\sum_{fa(v)=u} (f_v+f_u+1)]
$$

解方程得到

$$
f_u = d_u + \sum_{fa(v) = u} f_v
$$

令 $g_u$ 表示 $fa(u)\to u$ 的期望步数，定义 $g_{\text{root}}=0$

当 $fa(u) \ne \text{root}$ ：

$$
g_u = \frac{1}{d_{fa(u)}}[1+(1+g_{fa(u)}+g_u)+\sum_{fa(v)=fa(u),v\ne u}(1+f_v+g_u)]
$$

解方程得到

$$
g_u=d_{fa(u)}+g_{fa(u)}+\sum_{fa(v)=fa(u),v\ne u} f_v=f_{fa(u)}-f_u+g_{fa(u)}
$$

当 $fa(u) = \text{root}$：

$$
g_u=\frac{1}{d_{fa(u)}}[1+\sum_{fa(v)=fa(u),v\ne u}(1+f_v+g_u)]
$$

解得

$$
g_u = d_u+\sum_{fa(v)=fa(u),v\ne u} f_v=f_{fa(u)}-f_u
$$

由于 $g_{\text{root}}=0$ ，两者可以合并：

$$
g_u = f_{fa(u)}-f_u+g_{fa(u)}
$$

令 $F(u,v)$ 表示 $u,v$ 这条链上所有点的 $f$ 的和，不含 $v$。

令 $G(u,v)$ 表示 $u,v$ 这条链上所有点的 $g$ 的和，不含 $u$。

$f,g$ 可以线性求出。这样，如果已知 $s,t$ ，就可以通过 $F(s,\text{lca}(s,t)) + G(\text{lca}(s,t),t)$ 求出期望。

考虑求答案：枚举 $\text{lca}(s,t)=u$ 

令 $u \in v$ 表示 $u$ 在 $v$ 的子树中，$u \notin v$ 表示 $u$ 不在 $v$ 的子树中。

那么此时所有情况的期望和就是

$$
\sum_{x \in u} G(u,x)+\sum_{fa(v)=u} ([size(u)-size(v)] \sum_{x \in v} F(x,u)+size(v)\sum_{x \notin v,x \in u} G(u,x) )
$$

意思是，分别计算 $s=x$ 时，$s \in v$ 时的期望和。

预处理 $v=1$ 时的 $F$ 和 $u=1$ 时的 $G$ ，并统计子树内这两个值的和。

那么答案可以 $O(n)$ 计算得到。最后除掉 $n^2$ 就好了。


---

## 作者：Created_equal1 (赞：13)

首先dp出每个点到其父亲的期望游走距离和每个点父亲到这个点的期望游走距离（可以自己推式子，可以直接拉经典结论），这样我们就相当于把一个双向边拆成两条单向边。然后考虑如何统计答案。


方法1：主要到s到t的期望游走距离为s到lca的期望游走距离+lca到t的期望游走距离，所以枚举每个点作为lca，然后利用树形dp+乘法原理统计答案。


方法2：考虑统计每条边对答案的贡献。枚举某条边E，其对答案产生的贡献就是在E一边的点数\*E在另一边的点数\*（E正着走的期望距离+E倒着走的期望距离）。


以上两种做法均可做到线性复杂度。


---

## 作者：JOHNKRAM (赞：11)

设f[u->v]表示u、v之间有边的情况下，从u到v的期望距离。考虑从u出发第一步走到哪里可以列出方程f[u->v]=1/d[u]+sum{(1+f[k->u]+f[u->v])/d[u]}(u、k之间有边且k!=v)，d[u]表示u的度数。解方程得f[u->v]=d[u]+sum{f[k->u]}(u、k之间有边且k!=v)。把f[k->u]一层层代入，可得f[u->v]=sum{d[i]}(i在以v为根时u的子树内)。考虑每条边被计算了多少次，化简得f[u->v]=2siz[v][u]-1，siz[v][u]表示以v为根时u的子树大小。只需要计算出所有的siz[1][i]，那么判断一下u和v谁是父亲就可以O(1)的计算出siz[v][u]，进而计算出f[u->v]。


接下来考虑如何计算答案。因为期望的线性性，路径长度的期望等于每条边长度期望的和，所以考虑每条边在多少条路径中出现过，即可得出一条有向边u->v对答案的贡献是siz[v][u]\*siz[u][v]\*f[u->v]/n/n。对每条边各计算一次即可，时间复杂度O(n)。


---

## 作者：suzhikz (赞：3)

对学哥的题解做点补充。

这种题目有个很套路的技巧，计算每个点到他的父亲期望走的次数，在[学哥的题解](https://www.luogu.com.cn/article/tuvsk8zd)里讲的很清楚了。这里主要讲另一种化简方式。

我们先以 $1$ 为根算一次儿子到父亲的期望次数，然后我们要考虑计算父亲到儿子走的期望次数。我们放张图。这是第一次 dfs 计算的边。

![](https://cdn.luogu.com.cn/upload/image_hosting/5fkt5j9n.png)

然后假设算 $2$ 到 $3$ 这条边，有关的值就变成这样了。

![](https://cdn.luogu.com.cn/upload/image_hosting/bayxvuss.png)

所以我们只需要计算一个点内儿子到他距离的和就可以和父亲到父亲的父亲的距离就能算这个点到父亲的距离。

大概的程序长这样。


```cpp
void dfs2(int x,int fa){
	if(x!=1){
		invto_fa[x]=(summ[fa]+invto_fa[fa]-to_fa[x])+g[fa].size();
		ans=ans+invto_fa[x]*siz[x]%mod*(n-siz[x])%mod;ans%=mod;
	}
	for(int i:g[x]){
		if(i==fa)continue;dfs2(i,x);
	}
}
```

然后我们把每条有向边（因为 $u$ 到 $v$ 和反过来的边权不一定一样，所以把无向边变成有向边）的权值都算出来。题目现在转化为任选两个点，求平均距离，这玩意非常的板子。

考虑每条边的贡献，就是可以在一条边内子树任选一个，另一个点的反子树内任选一个，即为经过次数，然后乘上权值加起来即为答案。

---

## 作者：RedreamMer (赞：3)

[$\huge\texttt{P3412}$](https://www.luogu.com.cn/problem/P3412)

[更好的体验](https://www.cnblogs.com/RedreamMer/p/14784021.html)

## 题意

给定一棵树，求任意一条路径从起点随机游走到终点的期望距离的期望。

## 思路

讨论求出每条边的贡献，当且仅当每条路径两个端点分别在这条边分成两个连通块中。

一些约定： $v\in u$ 表示 $v$ 是 $u$ 的子节点，$sum[u]=\sum_{v\in u} up[v]$，$p[u]$ 表示 $u$ 的连边数量，$fa[u]$ 表示 $u$ 的父亲。

对于每条边 $u\to v$ 它的两种期望：

向上走的期望可以由 $u\to fa[u]$ 或者 $u\to v\to u\to fa[u]$ 得到。

向下走的期望可以由 $u\to v$ 或者 $u\to v'
\to u\to v$ 或者 $u\to fa[u]\to u\to v$ 得到（$v'\in u\&v'\ne v$）。

然后发现这些都可以通过已知项求得，对其讨论即可。

列式子求解每条边向上走向下走的期望步数，为了方便标记每条边，$up[u]$ 和 $down[u]$ 都表示连 $u$ 的父边，而 $up$ 表示向上，$down$ 对应向下。

则会有下面的式子（感觉我推烦了，但还是比较清晰的吧）：
  
$$
  up[u]=\frac{1}{p[u]}+\frac{1}{p[u]}(\sum_{v\in u}(1+up[v]+up[u]))
$$
$$
  up[u]=\frac{1}{p[u]}+\frac{(p[u]-1)up[u]}{p[u]}+\frac{1}{p[u]}(\sum_{v\in u}(1+up[v]))
$$
$$
  up[u]=1+p[u]-1+\sum_{v\in u}up[v]
$$
$$
  up[u]=p[u]+\sum_{v\in u}up[v]
$$
  
$$
  down[u]=\frac{1}{p[fa[u]]}+\frac{1}{p[fa[u]]}(\sum_{v\in fa[u]\&v\ne u}1+up[v]+down[u])+\frac{1}{p[fa[u]]}(1+down[fa[u]]+down[u])
$$
$$
  donw[u]=1+\frac{(p-1)(down[u])}{p[fa[u]]}+\frac{1}{p[fa[u]]}(sum[fa[u]]-up[u]+down[fa[u]])
$$
$$
  down[u]=p[fa[u]]+sum[fa[u]]-up[u]+down[fa[u]]
$$

然后就很容易了。

## 代码

```cpp
int a, b, up[N + 5], sum[N + 5], down[N + 5], ans, siz[N + 5];
vector<int> st[N + 5];

void dfs(int n, int fa) {
	siz[n] = 1;
	rep(i, 0, siz(st[n]) - 1) {
		int v = st[n][i];
		if (v == fa) continue;
		dfs(v, n);
		siz[n] += siz[v];
		(sum[n] += up[v]) %= mod;
	}
	up[n] = (siz(st[n]) + sum[n]) % mod;
}

void Dfs(int n, int fa) {
	if (n != 1) down[n] = (siz(st[fa]) + sum[fa] - up[n] + down[fa] + mod) % mod;
	(ans += siz[n] * (a - siz[n]) % mod * (down[n] + up[n]) % mod) %= mod;
	rep(i, 0, siz(st[n]) - 1) {
		int v = st[n][i];
		if (v == fa) continue;
		Dfs(v, n);
	}
}

int qpow(int n, int m = mod - 2) {
	int res = 1;
	for (; m; m >>= 1) {
		if (m & 1) res = res * n % mod;
		n = n * n % mod;
	}
	return res;
}

signed main() {
	// freopen("in1.in", "r", stdin);
	// freopen("out.out", "w", stdout);
	a = read();
	int x, y;
	rep(i, 1, a - 1) {
		x = read();
		y = read();
		st[x].PB(y);
		st[y].PB(x);
	}
	dfs(1, 0);
	Dfs(1, 0);
	printf("%lld", ans * qpow(a * a % mod) % mod);
	return 0;
}
```

---

## 作者：P2441M (赞：2)

#### 题意
给定一棵 $n$ 个点的树，小仓鼠想从任意的起点 $s$ 走到任意的终点 $t$，每次会从所有相邻的节点中等概率随机选择一个走，问走的路径长度的期望，答案对 $998244353$ 取模。

对于所有数据，$1\leq n\leq 10^5$。

#### 题解
妙妙题。枚举终点 $t$ 作为树的根节点，然后你发现它可以往回走，导致你如果设计 $f_u=E(dis(u,t))$ 会有后效性，$n$ 的范围显然不允许我们做高斯消元。

考虑一些高妙的东西，注意到某个点 $u\rightarrow t$ 随机走出来的路径必然会包含 $path(u,t)$ 上的边，所以我们有
$$
E(dis(u,t))=\sum_{\substack{x\in path(u,t)\\x\neq t}}E(dis(x,fa_x))
$$

很自然地想到设计 $f_u=E(dis(u,fa_u))(u\neq t)$，但这个好像还是列不出普通的转移方程啊！但是我们仔细考虑 $u$ 如何能走到 $fa_u$。首先它有 $\frac{1}{deg_u}$ 的概率可以直接走到 $fa_u$，其次对于每个子节点 $v\in son_u$，它还有 $\frac{1}{deg_u}$ 的概率走到 $v$，然后再沿 $v\rightarrow u\rightarrow fa_u$ 走到 $fa_u$。于是我们可以列出一个神秘的方程：
$$
f_u=\frac{1}{deg_u}+\frac{1}{deg_u}\sum_{v\in son_u}f_v+f_u+1
$$
解方程可以得到
$$
f_u=deg_u+\sum_{v\in son_u}f_v
$$
于是我们可以树形 DP 求出所有 $f_u$ 了！然后对于一条边 $(u,fa_u)$，显然它是 $sz_u$ 个节点向上走的必经边。我们令 $f_t=0$，则 $ans_t=\sum_{u=1}^t sz_uf_u$。

枚举 $t$，把所有 $ans_t$ 加起来再除以 $n^2$ 就是答案，于是我们有了 $O(n^2)$ 的做法。转移方程是个和式，某个点的贡献容易增删，显然可以换根 DP 优化到 $O(n)$。实现时注意一下换根前后根节点的贡献即可。

其实我们也有不那么高妙的角度。我们回到令 $f_u=E(dis(u,t))$，转移方程就是 $f_u=\frac{1}{deg_u}\sum_{(u,v)\in E}f_v+1$。从叶子节点开始考虑，那么 $f_u$ 的值只和 $f_{fa_u}$ 有关，进一步扩展到某个叶子结点的父亲 $u'$，它的每个儿子都可以表示成有关 $f_{u'}$ 的一次函数，代入得到 $f_{u'}$ 的值又只与 $f_{fa_{u'}}$ 有关……这样向上递推，容易发现 $f_u$ 最终就是一个关于 $f_{fa_{u}}$ 的一次函数，可以记录系数树形 DP 求解。再去记录子树的 $f_u$ 和容易拓展到换根 DP 的形式。时间复杂度还是 $O(n)$ 的。显然两种角度本质相同。

---

## 作者：Maniac丶坚果 (赞：2)

难度适中的期望DP.

首先我们要弄明白这样一件事情:

如何求一棵树上在这样的随机游走的情况下从一个点$i$到相邻点$j$的期望步数;

这个问题显然是不能按照最朴素的"一步一步走"的思想去理解的.如果是这样,只能就是"先考虑链的情况". 设一排三个点$a,b,c$,从点$a$走到点$c$,第一步一定能走到$b$,然后第二步有$\frac{1}{2}$的概率直接走到,或者同样$\frac{1}{2}$的概率花两步走到1在走回来,然后又是$\frac{1}{2}$的概率(占总概率$\frac{1}{4}$)花四步走到....这样,最后我们得到的式子应该是$2 \times \frac{1}{2} + 4 \times \frac{1}{4} + 6 \times \frac{1}{8} ....$

对此加以计算需要用到一些技巧,注意到这是一个无穷项的差比数列.

根据差比数列求和公式

$$S_n=\frac{ae - [a+d(n-1)]eq^n}{1-q} + \frac{deq + deq^n}{{(1-q)}^2}$$

(其中$a$为等差数列首项,$d$为公差,$e$为等比数列首项,$q$为等比数列公比,$n$为项数)

此时显然N趋向于无穷大又由于公比Q为<1的实数,所以可以认为$q^n$是趋向于0的.

所以可以认为原式= $$\frac{ae}{1-q} + \frac{deq}{(1-q)^2} = \frac{2\times\frac{1}{2}}{\frac{1}{2}} + \frac{2\times\frac{1}{2}\times\frac{1}{2}}{\frac{1}{2}\times\frac{1}{2}} = 4$$

(为什么? 可以试试令原式= S,由于注意到公比是$\frac{1}{2}$,搞一个2S与其错位相减吧)

链更长,图更复杂的情况是可以推出来的.

**---------------------但是想要解决本题并不能用这么工匠式的瞎子登山法来做--------------------------**

**不妨考虑终点固定时的情况.**

假设终点在树根,那么我们令$f[i]$表示点$i$走到它父亲的期望步数.此时,

我们可以推出如下式子:

对于叶子节点:$f[leaf]=1$ (一定会走到其父亲)

对于根节点:$f[root]=0$(根本就不需要走)

对于其余节点(设$d[x]$ 表示其度数):
$f[x]=1+\frac{1}{d[x]}\times\sum_{(x,y)\in G}(f[y]+f[x])$

将最后一个算式进行移项得到$f[x] = d[x] + \sum_{(x,y) \in G}f[y]$

**到这里可以尝试画一张图并注上每个节点的f[x],是不是发现了什么?**

设$sz[x] =$子树大小,$son[x]=$儿子数目

考虑叶子结点的父亲节点,由于它们的儿子每个恰有1贡献并且儿子数一定是$sz[x] - 1 $所以$\sum_{(x,y) \in G}f[y] = sz[x]-1$,节点度数$d[x]$为儿子数+1 = $sz[x]$,
所以它们的贡献一定是$2 \times sz[x] - 1$

而再往上推,可以发现除了根节点没有贡献意外其他地方都有类似的结论: 每个节点源自儿子节点的贡献都是$ 2 \times (sz[x] - 1) - son[x] $,度数则是$son[x] + 1$.

所以不难得出,每个节点走到根节点的期望步数为 $ 2\times(sz[x] - 1)$.

在考虑所有节点的时候,显然对于节点$x$,总共会有$sz[x]$个人要向上走过这条边. 所以这个节点(也可以认为是这条边)的贡献 为$ 2 \times (sz[x] - 1) \times sz[x]$

让我们回到终点不固定的情况. 假设我们现在已经取了$1$号点为根并且算出了每个节点的$sz[x]$.

注意到上面的转换实际上是计算了每个节点与它父亲连接的边的贡献.

笔者的一种理解方式是考虑节点[x]的每棵子树,计其根为$son[x]$,当根节点落在这棵子树内时,$sz[x] = n - son[x]$.可以分别计算.

这样每条边会被算到两次,总复杂度为$O(M)$.

代码:
```
#include <bits/stdc++.h>
#define PB push_back
#define LL long long
using namespace std;
const int maxn = 100010;
const int mo = 998244353;
vector<int> G[maxn];
inline int read()
{
	int x = 0, f = 1;
	char ch = 0;
	for (;!isdigit(ch); ch = getchar()) if (ch == '-') f = -1;
	for (;isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
	return x * f;
}
inline int ksm(int p,int q)
{
	if (q == 0) return 1; if (q == 1) return p;
	int res = 1; int tmp = p;
	for (; q; q >>= 1, tmp = 1LL * tmp * tmp % mo) if (q & 1)res = 1LL * res * tmp %mo;
	return res;
}
int n,sz[maxn],a[maxn],fa[maxn],num;
LL ans;
void dfs(int u,int pre)
{
	sz[u] = 1;fa[u] = pre;
	for (int i = 0; i < G[u].size(); ++i) if (G[u][i] != pre) dfs(G[u][i],u),sz[u] += sz[G[u][i]];
}
inline int Mo(int &x){while (x >= mo) x -= mo; while (x < 0) x += mo;}
inline LL Mo1(LL &x){while (x >= mo) x -= mo; while (x < 0) x += mo;}
int main()
{
	n = read();
	for (int i = 1; i < n; ++i)
	{
		int u = read(), v = read();
		G[u].PB(v), G[v].PB(u);
	}
	dfs(1,0);
	for (int i = 1; i <= n; ++i)
	{
		int tot = n - 1;
		for (int j = 0; j < G[i].size(); ++j) 
		{
			if (G[i][j] == fa[i]) continue;
			LL pre = 0;int s = sz[G[i][j]];
			pre += (2LL * (n - s ) * (n - s ) - (n - s )) * s %mo; Mo1(pre);
			ans += pre, Mo1(ans);
			tot -= sz[G[i][j]];	
		}
		if (tot)
		{
			LL pre = 0;int s = tot;
			pre += (2LL * (n - s ) * (n - s ) - (n - s )) %mo * s; Mo1(pre);
			ans += pre, Mo1(ans);		
		}
	}
	int Tot = 1LL * n * n % mo;
	ans = 1LL * ans * ksm(Tot,mo - 2) %mo;
	printf("%lld\n",ans);
	
}
```

---

## 作者：Meteor_ (赞：1)

# P3412 仓鼠找sugar II 题解

~~大水题一个~~

## 题目大意

给定你一个树，设 $f_{u, v}$ 表示在树上随机游走的情况下从 $u$ 走到 $v$ 的期望步数，求 $\displaystyle \frac{\sum_{i = 1}^n \sum_{j = 1}^n f_{i, j}}{n^2}$。

## 题解

不难想到 dp，不过 $1e5$ 的范围差点让我怀疑我 $O(n)$ 的 dp。先设一下状态，设 $f_u$ 表示 $u$ 子树内的所有点全都走到点 $u$ 的期望步数。答案就是以每个点为根时根的 $f$ 值的和。

考虑怎么转移。

似乎不好直接转，于是想想我们转移时什么东西卡住了我们。假设现在 $u$ 子树内的所有点都走到了 $u$，那么我们现在想要让这些点再从 $u$ 结点走向它的父亲结点，这个期望步数不好直接求。

于是我们再设 $g_u$ 表示从 $u$ 结点走到它的父亲结点的期望步数。先来考虑它的转移。$deg_u$ 表示 $u$ 结点的度，即与它相连的边数，$son_u$ 表示 $u$ 结点的儿子构成的集合。

$$\begin{aligned}

g_u &= \frac{1}{deg_u} + \sum_{v \in son_u} \frac{1 + g_v + g_u}{deg_u}\\

deg_u \times g_u &= 1 + \sum_{v \in son_u} (1 + g_v + g_u)\\

&= 1 + (deg_u - 1) + (deg_u - 1) \times g_u + \sum_{v \in son_u} g_v\\

&= deg_u + (deg_u - 1) \times g_u + \sum_{v \in son_u} g_v\\

g_u &= deg_u + \sum_{v \in son_u} g_v

\end{aligned}$$

$g$ 的转移就没了，再来考虑 $f$。

$$\begin{aligned}

f_u &= \sum_{v \in son_u} f_v + size_v \times g_v

\end{aligned}$$

这个非常好理解。

于是可以打 $n^2$ 了。

换一下根，就 $O(n)$ 了。

设 $h(x)$ 为以 $x$ 为根时 $x$ 的 $f$ 值，那么有：

$$\begin{aligned}

h_u &= f_u + (h_{fa} - f_u - size_u \times g_u) + (n - size_u) \times (g_1 - g_u)

\end{aligned}$$

最终答案为 $\displaystyle \frac{\sum_i^n h_i}{n^2}$。

然后就没了。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int M = 100005;
const int mod = 998244353;
int n, f[M], g[M], siz[M], out[M], inv, ans, h[M];
int from[M << 1], to[M << 1], head[M], nex[M << 1], tot;

inline void add_edge(int u, int v) {
    from[++ tot] = u;
    to[tot] = v;
    nex[tot] = head[u];
    head[u] = tot;
}

void dfs1(int u, int fa) {
    g[u] = out[u];
    siz[u] = 1;
    for(int i = head[u]; i; i = nex[i]) {
        int v = to[i];
        if(v == fa)
            continue;
        dfs1(v, u);
        siz[u] += siz[v];
        g[u] = (g[u] + g[v]) % mod;
        f[u] = (f[u] + f[v] + siz[v] * g[v] % mod) % mod;
    }
}

void dfs2(int u, int fa) {
    h[u] = (f[u] + (h[fa] - f[u] + mod - siz[u] * g[u] % mod + mod) % mod + (n - siz[u]) * ((g[1] - g[u] + mod) % mod) % mod) % mod;
    ans = (ans + h[u]) % mod;
    for(int i = head[u]; i; i = nex[i]) {
        int v = to[i];
        if(v == fa)
            continue;
        dfs2(to[i], u);
    }
}

inline int quick_pow(int base, int ci, int pp) {
    int res = 1;
    while(ci) {
        if(ci & 1)
            res = res * base % pp;
        base = base * base % pp;
        ci >>= 1;
    }
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n;
    inv = quick_pow(n, mod - 2, mod);
    for(int i = 1; i < n; ++ i) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
        ++ out[u];
        ++ out[v];
    }
    dfs1(1, 0);
    ans = f[1];
    h[1] = f[1];
    for(int i = head[1]; i; i = nex[i]) 
        dfs2(to[i], 1);
    ans = ans * inv % mod * inv % mod;
    cout << ans;
}
```

---

## 作者：孤寂的时代 (赞：1)

网上没有C++的代码我就来一个吧

具体的推导过程可以参考下面管理员的题解我就不多说了

对任意选一个点对树dfs，求出每个点的它和它子树的size(点数)

然后考虑每个边的贡献

以下引用w\_yqts(<http://m.blog.csdn.net/w\_yqts/article/details/53158051>)的几句话:

"一条有向边u->v对答案的贡献是siz[v][u]\*siz[u][v]\*f[u->v]/n/n"

"f[u->v]表示u、v之间有边的情况下，从u到v的期望距离"

"f[u->v]=2siz[v][u]-1"

具体推导可以见该博客

那么我们把f=2siz-1代入贡献中，再加上反方向的边的同理的贡献

最后的式子为(siz[u]为当前点的它和它子树的size(点数))

siz[u]\*(n-siz[u])\*(2\*siz[u]+2\*(n-siz[u])-2)

至于分数取模，直接用扩展欧几里得即可，具体见代码







```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int INF=0x3f3f3f3f;
const int maxn=100005;
const int mod=998244353;
int head[maxn],to[maxn*2],nex[maxn*2],siz[maxn],tot,n;
long long a,b;
inline void add(int x,int y){
    nex[++tot]=head[x];
    to[tot]=y;
    head[x]=tot;
}
inline void dfs(int u,int fa){
    int v;
    siz[u]=1;
    for(int i=head[u];i;i=nex[i]){
        v=to[i];
        if(v!=fa){
            dfs(v,u);
            siz[u]+=siz[v];
        }
    }
    a=(a+(long long)siz[u]*(n-siz[u])%mod*(2*siz[u]+2*(n-siz[u])-2))%mod;
}
inline int exgcd(long long a,long long b,long long &x,long long &y){
    if(b==0){
        x=1;y=0;return a;
    }
    int t=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return t;
}
int main(){
    int x,y;
    scanf("%d",&n);
    b=(long long)n*n;
    for(int i=1;i<n;i++){
        scanf("%d%d",&x,&y);
        add(x,y);add(y,x);
    }
    dfs(1,0);
    long long k,c;
    exgcd(b,mod,k,c);
    k*=a;
    k=(k%mod+mod)%mod;
    printf("%lld",k);
    return 0;
}
```

---

## 作者：Priestess_SLG (赞：0)

显然是 dp 题。

先考虑 $O(n^2)$ 的暴力解法。枚举当前出发点为 $x$，设 $f_i$ 表示 $i$ 子树内所有点走到 $x$ 结点的期望步数的和。直接转移是困难的，因此套路的考虑列辅助 dp：设 $g_i$ 表示当前出发点为 $x$，从 $i$ 点走到其父亲结点所需要的期望步数。那么此时有两种转移：

+ 直接走到父亲结点。
+ 进入若干个儿子结点然后再到父亲结点。

因此显然可以列出转移：

$g_i=\dfrac{1}{\deg_i}+\dfrac{1}{\deg_i}{\large\sum\limits_{j\text{ is i's son}}}(1+g_i+g_j)$

感性理解，加号前面的部分是直接走到父亲结点（这里我们认为此时树的根节点为 $x$）的概率，加号后面的部分是枚举走到的哪一个儿子然后从儿子结点走到当前结点再从当前结点走到父亲结点所需的期望步数。

但是很显然这个转移带环。可以想到高消但是时间复杂度起飞了，因此使用另一种套路：

$$
\begin{aligned}
&g_i=\frac{1}{\deg_i}+\frac{1}{\deg_i}{\sum\limits_{j\text{ is i's son}}}(1+g_i+g_j)\\
&g_i=\frac{1}{\deg_i}({1+\sum\limits_{j\text{ is i's son}}}(1+g_i+g_j))\\
&g_i=\frac{1}{\deg_i}(\deg_i+\sum\limits_{j\text{ is i's son}}(g_i+g_j))\\
&g_i=1+\frac{1}{\deg_i}\sum\limits_{j\text{ is i's son}}(g_i+g_j)\\
&g_i=1+\frac{1}{\deg_i}((\deg_i-1)g_i+\sum\limits_{j\text{ is i's son}}g_j)\\
&\deg_ig_i=\deg_i+(\deg_i-1)g_i+\sum\limits_{j\text{ is i's son}}g_j\\
&g_i=\deg_i+\sum\limits_{j\text{ is i's son}}g_j
\end{aligned}
$$

此时转移结构形成 DAG，因此可以一次 dfs 在 $O(n)$ 的时间复杂度内求出 $g$ 数组。问题变为计算 $f$。

这个部分是容易的。考虑再做一次辅助 dp：设 $h_i$ 表示当前以 $x$ 结点为根结点的情况下，$i$ 为根的子树内结点的数量。转移十分平凡。因此可以简单列出 $f$ 的 dp 式：$f_i=\sum\limits_{j\text{ is i's son}}(f_j+g_jh_j)$，同样可以一次 dfs 求出答案。

于是得到了 $O(n^2)$ 的暴力 dp，需要继续优化：

对于需要计算多个根结点的 dp，考虑套路的换根优化。具体的，先对 $1$ 为根的情况暴力求出 $f,g,h$ 三个数组，然后设 $F_i$ 表示以 $i$ 结点为根答案是多少。那么 $F_1$ 可以直接计算，而 $F_i$ 则可以直接计算从其父亲到 $i$ 贡献会如何变化。设其父亲结点为 $j$，那么转移式为：

$$
F_i=F_j-g_ih_i+(n-h_i)(g_1-g_i)
$$

同样可以一次 dfs 在 $O(n)$ 的时间复杂度内求出答案，总时间复杂度为 $O(n)$ 可以通过该题。

```cpp
// #pragma GCC optimize(3, "Ofast", "inline", "unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/rope>
#define int long long
using namespace std;
const int inf = 2e18;
using ull = unsigned long long;
template<class _T>
using treap = __gnu_pbds::tree<_T, __gnu_pbds::null_type, less_equal<_T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
using POD = pair<double, double>;
const int N = 200010;
const int mod = 998244353;
int power(int a, int b, int c) {
    int ans = 1;
    while (b) {
        if (b & 1) ans = ans * a % c;
        a = a * a % c, b >>= 1;
    }
    return ans;
}
inline int inversion(int x) {
    return power(x, mod - 2, mod);
}
vector<int> adj[N];
int f[N], g[N], h[N], F[N], deg[N], n;
void dfs(int u, int fa) {
    h[u] = 1;
    for (int &v : adj[u])
        if (v != fa) {
            dfs(v, u);
            h[u] += h[v];
        }
}
void dfs2(int u, int fa) {
    g[u] = deg[u];
    for (int &v : adj[u])
        if (v != fa) {
            dfs2(v, u);
            g[u] += g[v];
            g[u] %= mod;
        }
}
void dfs3(int u, int fa) {
    f[u] = 0;
    for (int &v : adj[u])
        if (v != fa) {
            dfs3(v, u);
            f[u] = (f[u] + f[v] + g[v] * h[v] % mod) % mod;
        }
}
void dfs4(int u, int fa) {
    for (int &v : adj[u])
        if (v != fa) {
            F[v] = (F[u] - g[v] * h[v] % mod + (n - h[v]) * (g[1] - g[v]) % mod + mod * 2) % mod;
            dfs4(v, u);
        }
}
signed main() {
    // freopen("count.in", "r", stdin);
    // freopen("count.out", "w", stdout);
    // freopen("debug.err", "w", stderr);
    cin.tie(0)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    srand(time(0));
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].emplace_back(b);
        adj[b].emplace_back(a);
        ++deg[a], ++deg[b];
    }
    dfs(1, 0);
    dfs2(1, 0);
    dfs3(1, 0);
    F[1] = f[1];
    // cout << F[1] << '\n';
    dfs4(1, 0);
    int s = accumulate(F + 1, F + n + 1, 0ll) % mod;
    // for (int i = 1; i <= n; ++i) cout << g[i] << ' ';
    // cout << '\n';
    // cout << s << '\n';
    int all = n * n % mod;
    cout << s * inversion(all) % mod << '\n';
    return 0;
}

/*

5
2 1
3 1
4 3
5 3

*/

```

---

## 作者：山田リョウ (赞：0)

~~忘写了个回撤导致调了一晚上是不是还挺值得纪念的，某人简直是唐完了，太不牛了。~~

首先先将答案乘上 $n^2$ 转为求 $\sum\limits_{s,t}\operatorname{E}(\operatorname{dis}(s,t))$。

考虑对于终点为 $t$ 的情况，我们不妨将其设为根，设 $f_i=\operatorname{E}(\operatorname{dis}(i,t))$，则有

$$f_u=\begin{cases}0\quad&u=t\\\frac{\sum\limits_{(u,v)\in E}f_v}{\operatorname{deg}(u)}\quad&u\ne t\end{cases}$$

于是想要大力消元，但是复杂度爆了怎么办？？？

~~常见套路好像差分掉但是我不会。~~

考虑到在叶子结点的方程是一个二元的，变量分别为自己和父亲，于是考虑向上更新时代入进父亲的方程把自己消掉即可，这样可以求出每个非根结点和父亲的 $f$ 的一次函数关系。

进一步的，再维护个 $s_u=ax+b$ 表示当 $f_u=x$ 时子树中的 $f$ 之和，这样就可以继续换根跑出来对于所有的 $t$ 了。

```cpp
#include<stdio.h>
#include<vector>
const int p=998244353;
int sum(int a,int b,int P=p){return (P-a)>b?a+b:b-(P-a);}
int dif(int a,int b,int P=p){return a<b?P-(b-a):a-b;}
int pro(int a,int b,int P=p){return (long long)a*b%P;}
int pow(int a,int b,int P=p){int res=1;for(;b;b>>=1,a=pro(a,a,P))if(b&1)res=pro(res,a,P);return res;}
std::vector<int>edge[100001];
struct func{
    int k,c;
    func&operator+=(const func&o){return k=sum(k,o.k),c=sum(c,o.c),*this;}
    func operator+(const func&o)const{return {sum(k,o.k),sum(c,o.c)};}
    func&operator-=(const func&o){return k=dif(k,o.k),c=dif(c,o.c),*this;}
    func operator-(const func&o)const{return {dif(k,o.k),dif(c,o.c)};}
    func operator*(const func&o)const{return {pro(k,o.k),sum(pro(k,o.c),c)};}
    func inv()const{int t=pow(k,p-2);return {t,dif(0,pro(c,t))};}
}f[100001],s[100001];
void dfs1(int u,int fa){
    f[u]={(int)edge[u].size(),p-(int)edge[u].size()},s[u]={1,0};
    for(const auto&v:edge[u])
        if(v!=fa)
            dfs1(v,u),f[u]-=f[v],s[u]+=s[v]*f[v];
    if(fa)f[u]=f[u].inv();
}
int res;
void dfs2(int u,int fa){
    res=sum(res,s[u].c);
    for(const auto&v:edge[u])
        if(v!=fa){
            func a=s[u],b=s[v],c=f[u],d=f[v];
            s[u]-=s[v]*f[v],f[u]+=f[v],f[u]=f[u].inv();
            f[v]=f[v].inv(),f[v]-=f[u],s[v]+=s[u]*f[u];
            dfs2(v,u);
            s[u]=a,s[v]=b,f[u]=c,f[v]=d;
        }
}
int main(){
    int n;
    scanf("%d",&n);
    for(int i=1,u,v;i<n;++i)
        scanf("%d%d",&u,&v),edge[u].push_back(v),edge[v].push_back(u);
    dfs1(1,0),dfs2(1,0);
    printf("%d",pro(res,pow(n,p-3)));
    return 0;
}
```

---

