# [JRKSJ R5] Concvssion

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/no6azjmn.png?x-oss-process=image)

你很喜欢 Concvssion，但这并不妨碍你来做一道并不困难的有趣题目。

（题目背景图片来自 Phigros 曲绘，如有侵权，请告知出题人。）

## 题目描述

给定长度为 $n$ 的序列 $a,b$，满足 $\forall i\in[1,n],a_i,b_i\in[1,n]$。

定义一次操作为，$\forall i\in[1,n],b_i\gets a_{b_i}$。

你需要依次进行 $n$ 次操作，每次操作后求出 $\displaystyle\sum_{i=1}^n b_i$ 对 $998244353$ 取模的答案。

## 说明/提示

Idea：cyffff，Solution：Ntokisq / WhisperingSnowflakes，Code：cyffff / WhisperingSnowflakes，Data：cyffff

**Concvssion - Halv (Insane15.5)**
### 数据规模
本题采用捆绑测试。

| $\text{Subtask}$ | $n\le$ | 特殊限制 | $\text{Score}$ |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $10^4$ | 无 | $10$ |
| $2$ | $10^5$ | $\forall i\in[1,n],a_i\le10^3$ | $10$ |
| $3$ | $10^5$ | $\forall i\in[1,n],a_i=i\bmod n+1$ | $10$ |
| $4$ | $10^5$ | $a$ 是一个 $[1,n]$ 的排列 | $15$ |
| $5$ | $10^5$ | $a_1=1,\forall i\in[2,n],a_i< i$ | $25$ |
| $6$ | $10^5$ | 无 | $20$ |
| $7$ | $3\times10^5$ | 无 | $10$ |

对于 $100\%$ 的数据，$1\le a_i,b_i\le n\le 3\times10^5$。
### 特殊评分方式
本题开启子任务依赖，具体如下：
- 对于子任务 $i\in\{1,2,3,5\}$，您只需答对子任务 $i$ 即可获得子任务 $i$ 的分数。
- 对于子任务 $i=4$，您需要答对所有 $j\in[3,4]$ 的子任务 $j$ 才能获得子任务 $i$ 的分数。
- 对于子任务 $i\in\{6,7\}$，您需要答对所有 $j\in[1,i]$ 的子任务 $j$ 才能获得子任务 $i$ 的分数。

## 样例 #1

### 输入

```
5
2 3 4 5 1
2 2 3 1 1```

### 输出

```
14
19
19
14
9```

## 样例 #2

### 输入

```
5
3 5 1 4 2
2 2 3 1 1```

### 输出

```
17
9
17
9
17```

## 样例 #3

### 输入

```
5
1 1 2 2 4
2 2 3 1 1```

### 输出

```
6
5
5
5
5```

## 样例 #4

### 输入

```
5
3 1 5 3 4
2 2 1 3 3```

### 输出

```
15
19
20
21
19```

# 题解

## 作者：cyffff (赞：11)

[$\text{Link}$](https://www.luogu.com.cn/problem/P8852)

## 题意
给定长度为 $n$ 的序列 $a,b$，满足 $\forall i\in[1,n],a_i,b_i\in[1,n]$。

定义一次操作为，$\forall i\in[1,n],b_i\gets a_{b_i}$。

你需要依次进行 $n$ 次操作，每次操作后求出 $\displaystyle\sum_{i=1}^n b_i$ 对 $998244353$ 取模的答案。

$a_i,b_i\le n\le 3\times10^5$.
****
不断被爆标。

## 思路
### $a$ 为排列

建出 $(i,a_i)$ 组成的图，可知是若干个环。

问题变为给出若干个关键点 $b_i$（可重），每次将所有关键点走向连向的点并求所有关键点的编号和。设 $c_i$ 为编号为 $i$ 的结点上有多少个关键点。

对于一个环考虑：设其长度为 $l$，则时刻 $i$ 的答案就是时刻 $i\bmod l$ 的答案，只需处理出 $1\sim l$ 时刻的答案。先断环为链，第 $d$ 个时刻的答案 $\displaystyle f_d=\sum_{i=1}^lc_ia_{i+d}$。这个是差卷积形式。具体地，我们令 $a'_i=a_{2l-i+1}$，则 $f_d=\displaystyle\sum_{i=1}^lc_ia'_{2l-d+1-i}$。显然是卷积。我们可以 $O(l\log l)$ 算出 $1\sim l$ 时刻的答案。（这里的 $a$ 是断环为链后链上编号组成的序列）

现在用 $O(n\log n)$ 的时间将每个环的答案都求出了，我们考虑计算最终答案。对于 $\text{Subtask }3$，答案直接求了出来，但是对于 $\text{Subtask }4$ ，显然不能对于每一个环枚举时刻。我们考虑将 $l$ 相同的环对应位置的答案相加。考虑到 $l$ 的种类是 $O(\sqrt n)$ 种，此时我们枚举时刻即可。

时间复杂度 $O(n\sqrt n)$。

### $O(n\sqrt n\log n)$

本部分是原做法，与最终做法并无太大关联，如需要可跳过。

对于树的部分，考虑转换贡献，考虑一个关键点每个时刻对答案的贡献。

取出关键点到根的路径上的编号，可以对应地加到答案序列中。

考虑对树进行轻重链剖分，建立出 $\text{dfs}$ 序对应形成的序列，让一条重链上的编号在序列中连续。考虑将关键点向上跳重链，每次为将序列中的一个区间一一对应地加到答案序列的一段区间中。

问题形式地说就是给出长为 $n$ 的序列 $a,b$，$m$ 次操作，每次给出 $a$ 中的一个区间 $[l,r]$ 与 $L$，执行 $\forall i\in[l,r],b_{i+L-l}\gets b_{i+L-l}+a_i$。

对于这个问题，我们有如下算法：

对序列 $a$ 按照块长为 $B$ 分块，对于一次操作，若 $l,r$ 同块，则直接加，否则先对散块暴力，整块存下来暂不处理。

所有询问的散块处理完之后，处理整块。对于每个块 $[bL,bR]$，我们记录 $c_i$ 表示这个块加到 $b$ 序列中以 $i$ 开始的等长区间的次数，$d_i=a_{bL+i}(i\le bR-bL)$。令这个块对 $b_i$ 的贡献为 $res_i$，则有 $\displaystyle res_i=\sum_{j=1}^i c_jd_{i-j}$，可以卷积。

复杂度为 $O(mB+\dfrac{(n\log n+m)n}B)$，取 $B=O(\sqrt\dfrac{n^2\log n+nm}m)$ 得到最优复杂度 $O(n\sqrt{m\log n}+m\sqrt n)$，此处 $m=O(n\log n)$，得到 $B=O(\sqrt n)$，时间复杂度 $O(n\sqrt n\log n)$。

建出 $(i,a_i)$ 组成的图，可知是基环树森林。

考虑把上面那两个拼起来，分开的部分分别处理，你会发现还有一个问题：会有点从树上跳到环上。

考虑时间分块（根号重构）：选定 $B$，每过 $B$ 个时刻重新按照 $\text{Subtask }4$ 的方式预处理一遍所有的环，并将答案加到这次重构到下次重构的 $O(B)$ 个询问中，在这组询问中跳入环中的点（通过深度判断）暴力维护到组末。一次重构的时间复杂度是 $O(n\log n+B\sqrt n)$，每个点会被暴力维护 $O(B)$ 次，所以环部分的总时间复杂度是 $O(\dfrac{n^2\log n}B+nB)$，取 $B=O(n\sqrt{n\log n})$，得到 $O(n\sqrt{n\log n})$。

树上部分不变，但建树要把环的部分删掉，总时间复杂度 $O(n\sqrt n\log n)$，空间复杂度 $O(n\log n)$。

一些卡常技巧：
1. 调块长，树上部分 $3000$，环上部分 $1500$；
2. 对于树上部分，如果一个块内没有操作，跳过这个块；
3. 对于环上部分，如果一次重构内没有点跳入环中，与上一个块合并处理。

这三个卡常作用都非常显著，都用上可以把 $n\le10^5$ 的所有点搞进 2s。

这个做法很暴力，并不优美。
### $O(n\sqrt n)$

对树部分进行长链剖分。

对于一个结点，我们考虑将其非长子树内的结点当做长链上同样深度的结点来计算。这样计算显然是不对的，但是我们用非长链上的结点编号减去长链上深度相同的结点编号能得到这个关键点在这个时刻对答案贡献的偏差值。

考虑对于这个结点 $x$，将其所有非长儿子 $q$ 的所在的长链的结点合并到长儿子 $p$ 所在的长链上。令 $f_i$ 为 $q$ 的 $i-1$ 级长儿子编号减 $p$ 的 $i-1$ 级长儿子编号，$g_i$ 为 $q$ 的 $i-1$ 级长儿子上的关键点数。那么将 $q$ 的所在的长链的结点合并到 $p$ 所在的长链上对时刻 $i$ 答案的偏差就是 $\displaystyle\sum_{k=1}^{l}f_{k}g_{k+i}$，这是差卷积形式，可以 $O(l\log l)$ 计算。

这么说可能有些难以理解，放张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/zd3li0v5.png?x-oss-process=image/resize,m_lfit,h_300,w_400)

图中，对于结点 $3$，其有长儿子 $6$ 和非长儿子 $4$，$l=2$，$f_1=4-6=-2$，$f_2=5-7=-2$。如在 $5$ 处有一个关键点，则 $g_2=1$，我们会将其看作在 $7$ 处，则对进行了一次操作后的答案的影响为 $f_1g_2=-2$。

通过以上计算，我们可以将所有树上的关键点合并到所在树的最长链上。考虑将其合并到树所连接的环上，可以将环不断展开至链长，通过以上同样的方法进行偏差的计算。

对于每一个连通块，设其大小为 $s$，我们做到了 $O(s\log s)$ 的复杂度。

此时总时间复杂度做到了 $O(n\sqrt n)$，瓶颈在于环的按长度分类算贡献，常数小，在 $3\times 10^5$ 的数据范围下可跑进 1s。

（这里环长分类完加到答案里的时候用指令集加速速度可以起飞。[具体实现](https://www.luogu.com.cn/record/94306502)。）

### $O(n\log^2 n)$

考虑瓶颈是合并若干个连通块的答案，并不优美。

假设我们最终求出第 $i$ 个连通块环大小为 $l$，第 $0\sim l$ 时刻的答案为 $s_{i,p}$，考虑写出其生成函数 $S_i(x)$。

设答案的生成函数是 $F(x)$，则：
$$\begin{aligned}F(x)&=\sum_{i=1}^{cnt}S_i(x)\sum_{j=0} x^{jl_i}\\
&=\sum_{i=1}^{cnt}\dfrac{S_i(x)}{1-x^{l_i}}\end{aligned}$$

设 $F(x)=\dfrac{P(x)}{Q(x)}$，则：
$$P(x)=\sum_{i=1}^{cnt}S_i(x)\prod_{j\ne i}(1-x^{l_j})$$
$$Q(x)=\prod_{i=1}^{cnt}(1-x^{l_i})$$

分别可以分治 FFT 求出。

实现后发现这个其实跑不过上面那个常数的按环长分类。

再见 qwq~

---

## 作者：IdnadRev (赞：3)

挺自闭的，做麻烦了。

下文阐述 std 做法，我的原做法可以在[此](https://www.luogu.com.cn/paste/ajn3m5j7)查看。

建出基环树，只需分树上/环上点贡献考虑。

树上贡献比较简单，长剖，自下而上依次考虑每条长链贡献即可，每次都是一次卷积。

环上若不考虑走多遍环，只需断环为链做一遍卷积。由于最后需乘上一个 $\frac{1}{1-x^c}$（$c$ 为环长）并求和，我们只需分环长讨论（不同环长只有根号种），每次做一遍前缀和即可。

复杂度 $O(n\sqrt n)$。

---

## 作者：ducati (赞：1)

有趣的图论 + 多项式题，这里提供一种不一样的做法。

# Description

[传送门](https://www.luogu.com.cn/problem/P8852)

# Solution

考虑对 $\forall x \in [1,n]$ 连边 $x \to a_x$，得到内向基环树森林。令 $w_u$ 为 $b$ 中其出现次数，$ans_i$ 为第 $i$ 个答案，则 $u$ 能对 $ans_1,ans_2,\cdots$ 分别产生 $w_u \times a_u, w_u \times a_{a_u},\cdots$ 的贡献。

考虑将一棵基环树看做内向树加一条从根出发的边，则不断令 $u \leftarrow a_u$，可以分成不断向根走，和不断绕环两个部分。

先考虑前者。考虑点分治，令当前点分治的根为 $x$，重心为 $y$，则我们考虑所有一端在 $y$ 子树中，另一端为 $y$ 或 $y$ 祖先的点对 $(p,q)$ 的贡献。令 $d_u$ 表示 $u$ 到 $y$ 的距离，则 $(p,q)$ 会对 $ans_{d_p+d_q}$ 产生 $p \times w_q$ 的贡献。显然是卷积的形式，NTT 即可，总复杂度 $O(n \log^2 n)$。

再考虑后者。对于每个 $u$，其会在不断向上走的过程中，于时刻 $dep_u$ 到达根，其中 $dep_u$ 表示 $u$ 到根的距离。令 $c_t$ 为所有 $dep_u=t$ 的 $w_u$ 之和，环上的点依次为 $ord_0,ord_1,\cdots,ord_{k-1}$，其中 $ord_0$ 为根，$ord_{i}(1 \le i < k)=a_{ord_{i-1}}$，则 $(t,t')$ 能对 $ans_{t+t'},ans_{t+t'+k},ans_{t+t'+2k},\cdots$ 产生 $c_t ord_{t'}$ 的贡献。卷积过后，需要对下标的每个模 $k$ 的剩余系做前缀和，若对于每棵树都 $O(n)$ 地跑一遍，复杂度最劣是 $O(n^2)$ 的，无法接受。

但注意到，本质不同的环长只有 $O(\sqrt n)$ 种，于是对每一种环长一起跑即可。总复杂度 $O(n \sqrt n+n \log^2 n)$，本题被解决。

# Code

注意不要把根的贡献重复算了。

```cpp
#include <bits/stdc++.h>
#define eb emplace_back
#define il inline
#define ll long long
using namespace std;
const int N=3e5+5,M=1048580,mod=998244353,Gb=3,Gi=(mod+1)/Gb;

int read(){
	int s=0,w=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-')  w=-w;ch=getchar();}
	while (ch>='0'&&ch<='9'){s=(s<<1)+(s<<3)+(ch^'0');ch=getchar();}
	return s*w;
}
int n,d,mxd,tot,rot,f[M],g[M],ans[M]; vector<int> GA[N],vec[N];
int a[N],w[N],anc[N],sz[N],dep[N],rev[M],res[N]; bitset<N> is_root,vis;

il int quick_power(ll x,int y){
	ll res=1;
	for (;y;y=y>>1,x=(x*x)%mod){
		if (y&1)  res=(res*x)%mod;
	}
	return res;
}
il int Up(int x){return (x<0)?(x+mod):x;}
il int Down(int x){return (x>=mod)?(x-mod):x;}
il int getinv(int x){return quick_power(x,mod-2);}
il void chksum(int x,int &y){y+=x;if(y>=mod)y-=mod;}
namespace poly{
	int h[M]; ll pw1[M],pw2[M];
	void init(int n){
		for (int i=2;i<=n;i<<=1){
			int t=(mod-1)/i,x=quick_power(Gb,t),y=quick_power(Gi,t); pw1[i>>1]=pw2[i>>1]=1;
			for (int j=(i>>1)+1;j<i;j++)  pw1[j]=(pw1[j-1]*x)%mod,pw2[j]=(pw2[j-1]*y)%mod;
		}
	}
	void NTT(int *A,int len,int flag){
		for (int i=0;i<len;++i){
			if (i>rev[i])  swap(A[i],A[rev[i]]);
		}
		for(int mid=1;mid<len;mid<<=1)for(int i=0;i<len;i+=(mid<<1))for(int j=0;j<mid;j++){
			int u=A[i+j],v=(flag==1?pw1:pw2)[mid+j]*A[i+j+mid]%mod;
			A[i+j]=Down(u+v),A[i+j+mid]=Up(u-v);
		}
		if (flag==-1){
			ll val=getinv(len);
			for (int i=0;i<len;++i)  A[i]=(A[i]*val)%mod;
		}
	}
	void poly_mul(int n,int m){
		int p=1,cnt=0;
		while (p<=n+m)  p<<=1,cnt++;
		for (int i=0;i<=p;++i)  rev[i]=(rev[i>>1]>>1)|((i&1)<<(cnt-1));
		fill(f+n+1,f+p+1,0),fill(g+m+1,g+p+1,0);
		NTT(f,p,1),NTT(g,p,1);
		for (int i=0;i<=p;++i)  h[i]=((ll)f[i]*g[i])%mod;
		NTT(h,p,-1);
		for (int i=0;i<=p;i++)  f[i]=g[i]=0;
	}
	void Mul(int n,int m,bool flg){
		poly_mul(n,m);
		for (int i=0;i<=n+m;i++){
			if (!flg)  chksum(h[i],ans[i]);
			else chksum(h[i],vec[m][i]);
		}
	}
}
int Find(int x){return(anc[x]==x)?x:(anc[x]=Find(anc[x]));}
void dfs(int u){
	tot++;
	for (int v:GA[u]) {if(!vis[v])dfs(v);}
}
void dfs2(int u){
	int mx=0; sz[u]=1;
	for (int v:GA[u]) {if(!vis[v])dfs2(v),sz[u]+=sz[v],mx=max(mx,sz[v]);}
	mx=max(mx,tot-sz[u]);
	if ((mx<<1)<=tot)  rot=u;
}
void dfs_g(int u,int d){
	g[d]+=w[u],mxd=max(mxd,d);
	for (int v:GA[u]) {if(!vis[v])dfs_g(v,d+1);}
}
void work(int u){
	tot=d=mxd=0,dfs(u);
	if (tot==1)  return;
	dfs2(u);
	for (int i=rot;i!=u;i=a[i],d++)  f[d]=i;
	f[d]=u,dfs_g(rot,0),poly::Mul(d,mxd,0),vis[rot]=1;
	int sv_rot=rot;
	if (u^rot)  work(u);
	for (int v:GA[sv_rot]){
		if (!vis[v])  work(v);
	}
}
void get_dep(int u,int rot){
	int d=dep[u]; chksum(w[u],f[d]),mxd=max(mxd,d);
	for (int v:GA[u])  dep[v]=d+1,get_dep(v,rot);
	ans[d]=(ans[d]+(ll)(mod-w[u])*rot)%mod;
}
signed main(){
	n=read(),poly::init(M-4);
	for (int i=1;i<=n;i++)  a[i]=read(),anc[i]=i;
	for (int i=1;i<=n;i++)  w[read()]++;
	for (int i=1;i<=n;i++){
		int x=i,y=a[i],fx=Find(x),fy=Find(y);
		if (fx^fy)  anc[fx]=fy,GA[y].eb(x);
		else is_root[x]=1;
	}
	for (int u=1;u<=n;u++)if(is_root[u]){
		work(u),mxd=d=0,get_dep(u,u); g[0]=u;
		for (int i=a[u];i!=u;i=a[i])  g[++d]=i;
		d++;
		while ((int)vec[d].size()<=mxd+d+1)  vec[d].eb(0);
		poly::Mul(mxd,d,1);
	}
	for (int d=1;d<=n;d++)if(!vec[d].empty()){
		for (int i=0;i<(int)vec[d].size();i++)  res[i]=vec[d][i];
		for (int i=d;i<=n;i++)  chksum(res[i-d],res[i]);
		for (int i=0;i<=n;i++)  chksum(res[i],ans[i]),res[i]=0;
	}
	for (int i=1;i<=n;i++)  printf("%d\n",ans[i]);
	return 0;
}
```


---

## 作者：yyyyxh (赞：1)

考虑 $i\to a_i$ 连边形成的内向基环森林，相当于每个点有个权值 $val_i$，每过一个时刻 $val_i$ 就会沿有向边移动移动到下一个节点，每次询问 $\sum_i val_i\times i$。

先考虑解决一条链上的情况，发现过了时刻 $t$ 之后的答案是 $\sum_i val_i(i+t)$。这是一个减法卷积的形式，`reverse` 一下直接卷即可。

再考虑解决树的情况，既然链的情况好做我们可以考虑树剖，但是如果是重剖的话会出现轻儿子中有节点比重链还深的情况，这样对每条重链卷的卷积长度之和就不一定是 $O(n)$ 的了，于是我们应该长剖。

具体来说可以求出每个长链链顶关于 $dep$ 的权值之和 $sum$，然后先拿整颗子树的 $sum$ 树组卷一遍，再对每一个轻儿子卷一遍减去多算的贡献。由于每条链只会被它的父亲链卷一次，复杂度是 $O(n\log n)$ 的。

权值从树上移动到环上形成的贡献较为平凡，直接对每一颗基环树的 $sum$ 树组和环上的编号卷一遍。

于是只剩下所有点都移动到环上的情况了，由于一个权值会在环上永远绕圈圈，跟链的情况相似，所以这一部分可以做一遍循环卷积。

发现这个部分的贡献会贡献到一个等差数列位置的答案数组上，公差为环长。这个东西可以直接根号分治，也可以注意到本质不同的环长是 $O(\sqrt n)$ 级别的，于是 $O(n\sqrt n)$ 解决，成为了复杂度瓶颈？如果有哪位大佬会快速做这个东西欢迎指教。

时间复杂度 $O(n\sqrt n)$。

代码细节略多，就当 $\text{NOIP}$ 前的代码能力复健了。

```cpp
//read() add() qp() NTT()
int sn[N],dp[N];
void dfs(int u){
	for(int i=hd[u];i;i=nxt[i]){
		int v=ver[i];
		dfs(v);
		if(dp[v]+1>dp[u]){
			dp[u]=dp[v]+1;
			sn[u]=v;
		}
	}
}
vector<int> sum[N];
void calcs(int u,int dep){
	f[dep]+=b[u];
	if(++dep>=mod) dep-=mod;
	for(int i=hd[u];i;i=nxt[i]) calcs(ver[i],dep);
}
int res[N],seq[N];
void solve(int u){
	sum[u].resize(dp[u]+1,0);
	for(int p=u,d=0;p;p=sn[p],++d){
		sum[u][d]+=b[p];
		for(int i=hd[p];i;i=nxt[i]){
			int v=ver[i];
			if(v==sn[p]) continue;
			solve(v);
			for(int t=0;t<len;++t) g[t]=0;
			for(int t=0,q=sn[p];t<=dp[v];++t,q=sn[q]){
				sum[u][t+d+1]+=sum[v][t];g[dp[v]-t]=q;
			}
			NTT(g,0);
			for(int t=0;t<len;++t) f[t]=(ll)f[t]*g[t]%P;
			NTT(f,1);
			for(int t=0;t<=dp[v];++t) dec(res[t],f[t+dp[v]]);
		}
	}
	init(dp[u]<<1|1);
	for(int i=0;i<len;++i) f[i]=g[i]=0;
	for(int p=u,d=0;p;p=sn[p],++d) g[dp[u]-d]=p;
	for(int i=0;i<=dp[u];++i) f[i]=sum[u][i];
	NTT(f,0);NTT(g,0);
	for(int i=0;i<len;++i) g[i]=(ll)f[i]*g[i]%P;
	NTT(g,1);
	for(int i=0;i<=dp[u];++i) inc(res[i],g[i+dp[u]]);
}
typedef pair<int,int> pii;
vector<pii> vec[Lim+3];
void opt(int x,int v){
	if(mod>Lim){
		for(int i=x;i<=n;i+=mod) inc(res[i],v);
	}
	else vec[mod].emplace_back(x,v);
}
int main(){
	n=read();
	for(int i=1;i<=n;++i) a[fath[i]=i]=read();
	for(int i=1;i<=n;++i) ++b[read()];
	for(int i=1;i<=n;++i)
		if(rt(i)==rt(a[i])) del[i]=1;
		else{
			fath[rt(i)]=rt(a[i]);
			add(a[i],i);
		}
	for(int x=1;x<=n;++x)
		if(rt(x)==x){
			dfs(x);solve(x);
			for(int i=0;i<len;++i) g[i]=0;
			for(int i=0,p=x;i<=dp[x];++i,p=a[p]) g[i]=p;
			g[0]=0;NTT(g,0);
			for(int i=0;i<len;++i) f[i]=(ll)f[i]*g[i]%P;
			NTT(f,1);
			for(int i=0;i<=dp[x];++i) inc(res[i],f[i]);
			init(dp[x]<<1|1);
			for(int i=0;i<len;++i) f[i]=g[i]=0;
			mod=0;
			for(int p=a[x];;p=a[p]){g[++mod]=p;if(p==x) break;}
			calcs(x,0);
			NTT(f,0);NTT(g,0);
			for(int i=0;i<len;++i) f[i]=(ll)f[i]*g[i]%P;
			NTT(f,1);
			for(int i=0;i<mod;++i) seq[i]=0;
			for(int i=0;i<len;++i) inc(seq[i%mod],f[i]);
			for(int i=1;i<=mod&&dp[x]+i<=n;++i) opt(dp[x]+i,seq[(dp[x]+i)%mod]);
		}
	for(mod=1;mod<=Lim;++mod){
		if(vec[mod].empty()) continue;
		for(int i=1;i<=n;++i) seq[i]=0;
		for(pii cur:vec[mod]) inc(seq[cur.first],cur.second);
		for(int i=1;i<=n;++i){
			if(i>mod) inc(seq[i],seq[i-mod]);
			inc(res[i],seq[i]);
		}
	}
	for(int i=1;i<=n;++i) printf("%d\n",res[i]);
	return 0;
}
```

---

