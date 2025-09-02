# Send the Fool Further! (hard)

## 题目描述

Heidi is terrified by your estimate and she found it unrealistic that her friends would collaborate to drive her into debt. She expects that, actually, each person will just pick a random friend to send Heidi to. (This randomness assumption implies, however, that she can now visit the same friend an arbitrary number of times...) Moreover, if a person only has one friend in common with Heidi (i.e., if that person is in a leaf of the tree), then that person will not send Heidi back (so that Heidi's travel will end at some point).

Heidi also found unrealistic the assumption that she can make all the travels in one day. Therefore now she assumes that every time she travels a route between two friends, she needs to buy a new ticket. She wants to know: how much should she expect to spend on the trips?

For what it's worth, Heidi knows that Jenny has at least two friends.

## 说明/提示

In the first example, with probability $ 1/2 $ Heidi will go to $ 1 $ from $ 0 $ , and with probability $ 1/2 $ she will go to $ 2 $ . In the first case the cost would be $ 10 $ , and in the second it would be $ 20 $ . After reaching $ 1 $ or $ 2 $ she will stop, as $ 1 $ and $ 2 $ are leaves of the social tree. Hence, the expected cost she has to pay is $ 10·1/2+20·1/2=15 $ .

In the third example, the expected cost is $ 81/5 $ . You should output $ 400000019 $ .

In her travels, Heidi has learned an intriguing fact about the structure of her social network. She tells you the following: The mysterious determinant that you might be wondering about is such that it does not cause strange errors in your reasonable solution... Did we mention that Heidi is a weird cow?

## 样例 #1

### 输入

```
3
0 1 10
0 2 20
```

### 输出

```
15
```

## 样例 #2

### 输入

```
4
0 1 3
0 2 9
0 3 27
```

### 输出

```
13
```

## 样例 #3

### 输入

```
7
0 1 3
0 5 7
1 2 2
1 3 1
1 4 5
5 6 8
```

### 输出

```
400000019
```

## 样例 #4

### 输入

```
11
1 0 6646
2 0 8816
3 2 9375
4 2 5950
5 1 8702
6 2 2657
7 2 885
8 7 2660
9 2 5369
10 6 3798
```

### 输出

```
153869806
```

## 样例 #5

### 输入

```
6
0 1 8
0 2 24
1 3 40
1 4 16
4 5 8
```

### 输出

```
39
```

# 题解

## 作者：zzw4257 (赞：6)

>给定一棵有边权的树求从$1$出发随机遍历到叶子结点的期望距离

$\displaystyle f_x=\frac{f_{fa_x}+v_{x,fa_x}+\sum\limits_{y}(f_y+v_{x,y})}{deg_x}$

设$out_x$表示$x$出边之和

则$\displaystyle f_x=\frac{f_{fa_x}+\sum\limits_{y}f_y+out_x}{deg_x}$

发现这个东西是自己包含自己的所以要高斯消元

但是经历过随机游走那题我们会知道树上这类$dp$的通用技巧是$f_x$一定能表示为$f_{fa_x}$的一次函数

于是设$f_{x}=k_xf_{fa_x}+b_x$

则
$$
\begin{aligned}
f_x&=\frac{f_{fa_x}+\sum\limits_{y}f_y+out_x}{deg_x}
\\&=\frac{f_{fa_x}+\sum\limits_{y}(k_yf_x+b_y)+out_x}{deg_x}
\\&=\frac{f_{fa_x}+sk_x f_x+sb_x+out_x}{deg_x}
\end{aligned}
$$
所以有
$$
\begin{aligned}
deg_xf_x=f_{fa_x}+sk_x f_x+sb_x+out_x
\\\Leftrightarrow (deg_x-sk_y)f_x=f_{fa_x}+sb_x+out_x
\\\Leftrightarrow f_x=\frac{1}{deg_x-sk_y}f_{fa_x}+\frac{sb_x+out_x}{deg_x-sk_y}
\end{aligned}
$$
$$\therefore \begin{cases}k_x=\frac{1}{deg_x-sk_y}\\b_x=\frac{sb_x+out_x}{deg_x-sk_y}\end{cases}$$

可以轻易发现当我们算出每个点$k/b$后第一个定下来的值就是$f_{rt}=b_{rt}$

本题并不要求但如果要求其他点反推即可

```cpp
#include<bits/stdc++.h>
#define N 100001 
#define mod 1000000007
using namespace std;
#define G if(++ip==ie)if(fread(ip=ibuf,1,L,stdin))
const int L=1<<19;
char ibuf[L],*ie=ibuf+L,*ip=ie-1;
inline char nc(void){G;return *ip;}
#define getchar nc
inline int read(void){
	char opt;int flag=1,res=0;
	while((opt=getchar())<'0')if(opt=='-')flag=-1;
	while(opt>='0'){res=(res<<3)+(res<<1)+opt-'0';opt=getchar();}
	return res*flag;
}
int n,f[N],b[N],k[N];
struct Edge{int to,v;};
vector<Edge>g[N];
inline int Mod(int x){return x>=mod?x-mod:x;}
inline int qpow(int a,int b){int res=1;while(b){if(b&1)res=1ll*res*a%mod;a=1ll*a*a%mod;b>>=1;}return res;}
inline void dfs(int x,int prt){
	int y,div=0;if(g[x].size()==1u)return k[x]=0,void();k[x]=1; 
	for(auto t:g[x]){if((y=t.to)^prt)dfs(y,x),div=Mod(div+k[y]),b[x]=Mod(b[x]+b[y]);b[x]=Mod(b[x]+t.v);}//b_x原来表示sb_x+out_x
	div=qpow(Mod(g[x].size()-div+mod),mod-2);//1/(deg_x-sk_x)
	k[x]=1ll*k[x]*div%mod;b[x]=1ll*b[x]*div%mod;
}
signed main(void){
	n=read();
	int i,x,y,z;for(i=1;i<n;++i)x=read()+1,y=read()+1,z=read(),g[x].push_back({y,z}),g[y].push_back({x,z});
	dfs(1,0);printf("%d\n",b[1]);
	return 0;
}

```

---

## 作者：Gold14526 (赞：2)

$\rm Problem:$ [Send the Fool Further!(hard)](https://www.luogu.com.cn/problem/CF802L)

$\rm Difficulty:2400$

树上随机游走板题。

### 题意

给定一棵 $n(1\le n\le10^5)$ 个节点的带权树，求从根节点开始随机游走，到叶子结点停下经过的期望距离。

### 做法

设 $dp_x$ 为从节点 $x$ 走到叶子结点的期望距离，$out_x$ 为 $x$ 出边之和。

显然有：

$$dp_x=\frac{out_x+dp_{father_x}+\sum\limits_{y\in son_x}dp_y}{degree_x}$$

注：这里的度数 $degree$ 不是子节点个数而是相邻节点的个数。

接下来我们证明，对于一个节点 $x$，除了以它为根的子树外的 $dp$ 值都未确定时，$dp_x$ 可表示为 $k\times dp_{father_x}+b$ 的形式。

对于任意一个非叶子结点 $x$，如果它的所有子节点都能表示为 $k\times dp_x+b$，那么将它们带入到开始求出的递推式中即可将 $dp_x$ 表示成 $k\times dp_{father_x}+b$ 的形式。

而对于每个叶子结点，显然可以表示成 $0dp_{father_x}+0$。

所以一定可以表示。

具体的，设 $k_x,b_x$ 分别表示对于 $x$ 的 $k$ 和 $b$。

将 $dp_x=k_x\times dp_{father_x}+b_x$ 带入开始的递推式可得：

$$dp_x=\frac{out_x+dp_{father_x}+\sum\limits_{y\in son_x}(k_y\times dp_x+b_y)}{degree_x}$$

移项可得：

$$dp_x=\frac{1}{degree_x-\sum\limits_{y\in son_x}k_y}\times dp_{father_x}+\frac{out_x+\sum\limits_{y\in son_x}b_y}{degree_x-\sum\limits_{y\in son_x}k_y}$$

则：

$$k_x=\frac{1}{degree_x-\sum\limits_{y\in son_x}k_y}$$

$$b_x=\frac{out_x+\sum\limits_{y\in son_x}b_y}{degree_x-\sum\limits_{y\in son_x}k_y}$$

发现 $out_x$ 和 $degree_x$ 都是已知的，所以可以从一个节点子节点的 $k$ 和 $b$ 递推出当前节点的 $k$ 和 $b$。

而对于根节点 $root$，$dp_{father_{root}}=0$，代入 $dp_{root}=k_{root}\times dp_{father_{root}}+b_{root}$ 可得 $dp_{root}=b_{root}$，通过上面的方法我们不难求出 $b_{root}$ 也就求出了 $dp_{root}$。

### 代码

```cpp
#include<bits/stdc++.h>
#define cint const int
#define iint inline int
#define ll long long
#define cll const long long
using namespace std;
int num;
char ch;
iint read()
{
	num=0;
	ch=getchar();
	while(ch<'0'||ch>'9')
	{
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		num=(num<<1)+(num<<3)+ch-'0';
		ch=getchar();
	}
	return num;
}
cint mod=1e9+7;
int n;
int head[100001];
int out[100001];
int degree[100001];
int k[100001],b[100001];
struct edge{
	int to,val,next;
}e[200000];
int tot;
inline void add_edge(cint u,cint v)
{
	cint c=read();
	e[++tot]=edge{u,c,head[v]};
	head[v]=tot;
	e[++tot]=edge{v,c,head[u]};
	head[u]=tot;
	out[u]=(out[u]+c)%mod;
	out[v]=(out[v]+c)%mod;
	++degree[u];
	++degree[v];
}
int qpow(cint x,cint y)
{
	if(y==0)return 1;
	cint t=qpow(x,y>>1);
	if(y&1)return 1ll*t*t%mod*x%mod;
	return 1ll*t*t%mod;
}
iint inv(cint x){return qpow(x,mod-2);}
void dfs(cint x,cint father)
{
	int sk=0,sb=0;
	if(degree[x]==1)return;
	for(int i=head[x];i;i=e[i].next)
	{
		if(e[i].to==father)continue;
		dfs(e[i].to,x);
		sb=(sb+b[e[i].to])%mod;
		sk=(sk+k[e[i].to])%mod;
	}
	k[x]=inv(degree[x]-sk+mod);
	b[x]=1ll*k[x]*(sb+out[x])%mod;
}
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read();
	for(int i=1;i<n;++i)
	{
		add_edge(read(),read());
	}
	dfs(0,0);
	printf("%d",b[0]);
	return 0;
}
```

---

## 作者：Zigh_Wang (赞：2)

推荐 **[博客](https://blog.csdn.net/YunYuanWang/article/details/126042175?spm=1001.2014.3001.5501)** 内食用更佳

题面自己去看

原版题面：[CF802L](https://www.codeforces.com/contest/802/problem/L)

洛谷中文题面：[CF802L](https://www.luogu.com.cn/problem/CF802L)

# 状态设计
我们令 $f[i]$ 表示从 $i$ 号节点开始**到达叶子节点**的期望距离。
当然我们可以得出对于叶子节点有 $f[leaf] = 0$。

# 暴力做法
显然对于每个节点 $x$ 我们都有以下转移方程 ( 以下方程中会以下标和中括号两种形式表示数组或函数值以体现更清晰的层次 ) ：
$$f[x] = \sum_{y \in \{\{son_x\},\; fa_x\}}\frac{f[y]+dis_{x,\;y}}{deg[x]}$$
通过观察可以发现这个式子中包含了未知量 $f[fa_x]$。但每个点都构成这样的一个方程，于是我们有 $n$ 个未知量和 $n$ 个方程，所以我们想到用**高斯消元**来求解，最终 $f[1]$ 就是答案。

# 钳制芝士
首先必须明确一点，对于任意一个节点 $x$ 都有一个关于自己父亲的一次函数表达形式:
$$f[x] = k_x \times f[fa_x] + b_x$$
至于为什么嘛，你自己画棵树自己手推两个你就知道了。

# 方程推导
我们注意到每个节点 $x$ 的方程中只有一个未知量 ( 除去他自己 ) 也就是 $f[fa_x]$，于是我们有了以下推导 ( ~~这句话我乱胡的，看不懂可以直接看下面的推导~~ )：

首先我们将上面的式子中节点 $x$ 的儿子部分和父亲部分分开：
$$f[x] = \sum_{y \in \{son_x\}}\frac{f[y]+dis_{x,\;y}}{deg[x]} + \frac{f[fa_x]+dis_{fa_x,\;x}}{deg[x]}$$ 
$$=\frac{\sum_{y \in \{son_x\}} (f[y]+dis_{x,\;y}) \;+ \;(f[fa_x]+dis_{fa_x,\;x})}{deg[x]}$$

然后我们移项，把 $deg[x]$ 乘到左边去：
$$f[x] \times deg[x] = \sum_{y \in \{son_x\}} (f[y]+dis_{x,\;y}) \;+ \;(f[fa_x]+dis_{fa_x,\;x})$$

然后我们将 $f[x] = k_x \times f[fa_x] + b_x$ 代入到上式的 $f[y]$ 上去得到：
$$f[x] \times deg[x] = \sum_{y \in \{son_x\}} (k_y * f[x]+ b_y + dis_{x,\;y}) \;+ \;(f[fa_x]+dis_{fa_x,\;x})$$

再将 $Sigma$ 中的东西拆开得：
$$f[x] \times deg[x] = \sum_{y \in \{son_x\}} k_y * f[x ] + \sum_{y \in \{son_x\}} (b_y +dis_{x,\;y}) \;+ \;(f[fa_x]+dis_{fa_x,\;x})$$

再把与 $f[x]$ 有关的式子全部扔到左边去得：
$$f[x] \times deg[x] - \sum_{y \in \{son_x\}} k_y * f[x ] = \sum_{y \in \{son_x\}} (b_y +dis_{x,\;y}) \;+ \;(f[fa_x]+dis_{fa_x,\;x})$$
$$\implies f[x] \times deg[x] - f[x] * \sum_{y \in \{son_x\}} k_y = \sum_{y \in \{son_x\}} (b_y +dis_{x,\;y}) \;+ \;(f[fa_x]+dis_{fa_x,\;x}) $$
$$\implies f[x] \times (deg[x] - \sum_{y \in \{son_x\}} k_y) = \sum_{y \in \{son_x\}} (b_y +dis_{x,\;y}) \;+ \;(f[fa_x]+dis_{fa_x,\;x}) $$

然后再移项把左边的 $deg[x] - \sum_{y \in \{son_x\}} k_y$ 除到右边去：
$$f[x] = \frac{\sum_{y \in \{son_x\}} (b_y +dis_{x,\;y}) \;+ \;(f[fa_x]+dis_{fa_x,\;x})}{deg[x] - \sum_{y \in \{son_x\}} k_y} $$

最后把式子整理成 $f[x] = k_x \times f[fa_x] + b_x$ 的形式：
$$f[x] = \frac{1}{deg[x] - \sum_{y \in \{son_x\}} k_y} \times f[fa_x] + \frac{\sum_{y \in \{son_x\}} (b_y +dis_{x,\;y}) \;+ \;dis_{fa_x,\;x}}{deg[x] - \sum_{y \in \{son_x\}} k_y} $$

于是我们可以得到递推式：
$$k_x = \frac{1}{deg[x] - \sum_{y \in \{son_x\}} k_y}$$
$$b_x = \frac{\sum_{y \in \{son_x\}} (b_y +dis_{x,\;y}) \;+ \;dis_{fa_x,\;x}}{deg[x] - \sum_{y \in \{son_x\}} k_y} $$

最后由于 根节点 1 号节点没有父亲，也就是说 $f[1] = b[1]$。所以我们只需要在 dfs 时递归求解 $k_x$ 和 $b_x$ 即可 ( $b_x$ 的方程中含有 $k_y$ ，所以两个都需要计算)，而不需要单独计算 $f_x$。

# 注意
原题中的标点是从 0 开始的！！！(~~什么恶心东西~~)

# dfs 部分关键代码
```cpp
void dfs(int x, int fa)
{
	if(deg[x] == 1 && x != 1) {
		k[x] = b[x] = 0;
		return ;
	}
	
	int sumk = 0;
	for(int i = e.hd[x]; i; i = e.nxt[i]) {
		int y = e.to[i], z = e.w[i];
		if(y == fa) {
			b[x] = pls(b[x], z);
			continue;
		}
		
		dfs(y, x);
		b[x] = pls(b[x], b[y]);//这里是加同时取模操作
		b[x] = pls(b[x], z);
		sumk = pls(sumk, k[y]);
	}
	
	k[x] = qpow(dec(deg[x], sumk), MOD - 2);
	b[x] = mul(b[x], k[x]);//同理
}
```
# 完整代码
```cpp
//省去头文件和快读

int n;
struct Edge {
	int hd[MAXN];
	int nxt[MAXN << 1], to[MAXN << 1];
	int w[MAXN << 1];
	int tot = 0;
	
	void Add(int x, int y, int z) {
		nxt[++tot] = hd[x];
		hd[x] = tot;
		to[tot] = y;
		w[tot] = z;
	}
}e;
int deg[MAXN];

//------------以下是一系列的取模操作------------
int pls(int x, int y)
{
	if(x + y >= MOD)
		return x + y - MOD;
	else
		return x + y;
}
int dec(int x, int y) 
{
	if(x - y < 0)
		return x - y + MOD;
	else
		return x - y;
}
int mul(int x, int y) 
{
	if(1ll * x * y >= 1ll * MOD)
		return 1ll * x * y % MOD;
	else
		return x * y;
}
int qpow(int x, int y)
{
	int val = 1;
	while(y) {
		if(y & 1)
			val = mul(val, x);
		
		x = mul(x, x);
		y >>= 1;
	}
	return val;
}
//------------以上是一系列的取模操作------------

int k[MAXN], b[MAXN];
void dfs(int x, int fa)
{
	if(deg[x] == 1 && x != 1) {
		k[x] = b[x] = 0;
		return ;
	}
	
	int sumk = 0;
	for(int i = e.hd[x]; i; i = e.nxt[i]) {
		int y = e.to[i], z = e.w[i];
		if(y == fa) {
			b[x] = pls(b[x], z);
			continue;
		}
		
		dfs(y, x);
		b[x] = pls(b[x], b[y]);
		b[x] = pls(b[x], z);
		sumk = pls(sumk, k[y]);
	}
	
	k[x] = qpow(dec(deg[x], sumk), MOD - 2);//注意要取逆元
	b[x] = mul(b[x], k[x]);
}

int main()
{
	n = inpt();
	for(int i = 1; i < n; i++) {
		int x = inpt() + 1, y = inpt() + 1, z = inpt();
		
		e.Add(x, y, z);
		e.Add(y, x, z);
		deg[x]++, deg[y]++;
	}//对于所有节点都可以式子化为f[x] = k[x] * f[fa] + b[x]
	
	dfs(1, 0);
	
	printf("%d", b[1]);//因为根节点没有父亲，所以 f[1] = b[1] 
	
	return 0;
}

```

第一次写题解，前面的公式或许有些眼花缭乱，还请诸位巨佬谅解QwQ

---

## 作者：happybob (赞：0)

树上随机游走。

考虑设 $f_u$ 为从 $u$ 出发的期望答案。则叶子节点 $f_{leaf}=0$。

考虑对于非叶子节点 $u$，设其度数为 $d_u$，所有邻居边权和为 $w_u$，则 $f_u = \dfrac{w_u}{d_u} + \dfrac{f_{fa}}{d_u} + \sum \limits_{v \in son_u} \dfrac{f_v}{d_u}$。

直接对式子高斯消元就可以得到一个 $O(n^3)$ 的做法，显然不优。

事实上可以发现每个 $f_u$ 都是一个关于 $f_{fa}$ 的一个 $k
_uf_{fa}+b_u$ 的一次函数形式。我们只需要维护 $k_u$ 与 $b_u$ 即可。

为什么呢？考虑叶子节点，$k_u=b_u=0$，每个非叶子节点，如果其所有儿子的 $f$ 值都是与 $u$ 相关的一次函数，那么把 $f_u = \dfrac{w_u}{d_u} + \dfrac{f_{fa}}{d_u} + \sum \limits_{v \in son_u} \dfrac{f_v}{d_u}$ 后面的 $f_v$ 变成 $k_vf_u+b_v$，然后合并同类项之后就只剩 $f_{fa}$ 和常数了，故可以直接一次 DFS 求出每个点 $k$ 与 $b$。答案即为 $b_0$。

---

