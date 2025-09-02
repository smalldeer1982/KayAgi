# [NWRRC 2017] Fygon 2.0

## 题目描述

心爱的编程语言 Fygon 的新版本发布了！全新的 Fygon 2.0 仍然只有两个语句。第一个语句是 lag。它几乎可以替代任何其他语句。第二个语句是一个 for 循环：

```
for <variable> in range(<from>, <to>):
    <body>
```

for 循环使得从 from 到 to 进行迭代，包含两端。

如果 from 大于 to，则循环体不执行。

<variable> 是从 a 到 z 的小写字母，除了 n，它是一个在给定代码片段之前定义的变量。

<from> 和 <to> 可以等于外层循环中定义的任何变量。此外，<from> 可以是 1，<to> 可以是 n。

循环体缩进四个空格，并且至少包含一个语句。

如果你熟悉 Fygon 1.0，你会注意到，秉承最佳编程实践的精神，Fygon 2.0 不向后兼容，因为 range 函数现在需要两个参数。

新版本的性能显著提高，因此你可以编写更多嵌套的 for 循环。这就是为什么我们不再关注操作的确切数量，而是关注程序的渐进复杂性。为简单起见，所有 for 循环都嵌套在一个链中，并且在所有 for 循环中恰好有一个 lag 语句。所有循环变量都不同，并且不等于 n。

让我们定义 $f(n)$ 为给定 Fygon 程序执行的 lag 操作的数量，作为 n 的函数。对于非负整数 $k$ 和正有理数 $C$，如果

$$\lim_{n \to \infty}{\frac{f(n)}{C \cdot n^k}} = 1$$

我们称 $C \cdot n^{k}$ 是程序的渐进复杂性。

给定一个 Fygon 2.0 程序，找出其渐进复杂性。

## 说明/提示

时间限制：3 秒，内存限制：512 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4
for i in range(1, n):
    for j in range(1, i):
        for k in range(j, n):
            lag```

### 输出

```
3 1/3
```

# 题解

## 作者：Starlight237 (赞：5)

首先介绍如何对 DAG 求拓扑序的个数。

$f_S$ 表示点集 $S$ 中拓扑序的个数，枚举拓扑序中最后面的点 $v$，则当 $v\in S$ 且 $v$ 不存在通往 $S$ 的出边时，容易建立从 $S-\{v\}$ 的拓扑序到 $S$ 的拓扑序的单射（直接把 $v$ 加到最后）。因而可以将 $f_S$ 加上 $f_{S-\{v\}}$。很显然，这覆盖了所有可能的情况。

下面回到本题：

> (**2021集训队作业 P7024 【[NWRRC2017]Fygon 2.0】**)给定 $m$ 层嵌套的 `for` 循环语句，每个循环包含循环变量和上下界，其中上下界是外层变量或 $1$ 和 $n$，求关于 $n$ 的渐进复杂度和最高次项系数（常数）。最内层是一个语句 `lag`，其复杂度被认为是 $O(1)$。

对所有涉及到的变量和上下界都建立结点（整数变量） $\{u_k\}$，将一个 `for ui in range(uj,uk)` 的循环视为两个整数不等式 $u_j\le u_i\le u_k$。则 `lag` 的执行次数就等于该不等式组的正整数解数。

考虑建立图论模型，若 `for` 循环中有 $u_i\le u_j$ 的约束（若其中有 $1$ 或 $n$，视为没有约束），则建边 $u_i\rightarrow u_j$。对该图进行缩点，形成一个由 SCC（强连通分量） 组成的 DAG。易见每个 SCC 中所有点的取值都是相同的，不妨设为 $v_1,v_2,...,v_k$（一共有 k 个 SCC）。我们只要求出了该 DAG 的一个拓扑序，则从小到大随意给 $v_1,...,v_k$ 赋值为 $[1..n]$ 中的互不相同的整数，便得到了该拓扑序对应的 $\binom nk$ 组解，于是总执行次数就是 $N\binom nk$，其中 $N$ 是拓扑序个数。从而渐进复杂度就是 $O(n^k)$。常数项为 $\lim_{n\rightarrow\infty}N\binom nk/n^k=N/k!$。

这里 $N$ 就可以用上述的方法，状压 DP 求出。

```cpp
#define ctz __builtin_ctz
const int S = 1048586;
int m, tab[128], tot;
ll f[S];
inline int newnode(int x) {
	return (x == '0' || x == 'n' ? 0 : tab[x] ? tab[x] : tab[x] = ++tot) - 1;
}
int eg[21], eg_[S], dfn[21], low[21], tim, ins, cnt = -1, rt[21];
stack<int>stk;
void tarjan(int x) {
	dfn[x] = low[x] = ++tim, stk.push(x), ins |= 1 << x;
	for (int v, i = eg[x]; i; i &= i - 1)
		if (!dfn[v = ctz(i)]) tarjan(v), low[x] = min(low[x], low[v]);
		else if (ins >> v & 1) low[x] = min(low[x], dfn[v]);
	if (dfn[x] == low[x]) {
		++cnt; int y;
		do y = stk.top(), rt[y] = cnt, ins &= ~(1 << y), stk.pop(); while (y != x);
	}
}
int main() {
	freopen("1.in", "r", stdin);
	m = rd();
	for (int i = 1; i <= m; ++i) {
		char ch = gtc();
		while (ch != 'f' && ch != 'l') ch = gtc();
		if (ch == 'f') {
			gtc(); gtc(); int x = gtc();
			gtc(); gtc(); gtc(); gtc(); gtc(); gtc(); gtc(); gtc();
			int l = gtc(); gtc(); int r = gtc();
			x = newnode(x), l = newnode(l), r = newnode(r);
			if (~l) eg[l] |= 1 << x;
			if (~r) eg[x] |= 1 << r;
		}
	}
	for (int i = 0; i < tot; ++i)
		if (!dfn[i]) tarjan(i);
	for (int i = 0; i < tot; ++i)
		for (int j = eg[i], v; j; j &= j - 1)
			if (rt[i] != rt[v = ctz(j)])
				eg_[rt[i]] |= 1 << rt[v];
	ll fac = 1;
	for (int i = 2; i <= cnt; ++i) fac *= i;
	f[0] = 1;
	for (int i = 1, all = ~(-1 << cnt); i <= all; ++i)
		for (int j = i, v; j; j &= j - 1)
			if (!(eg_[v = ctz(j)] & i)) f[i] += f[i & ~(1 << v)];
	ll fs = f[~(-1 << cnt)], g = __gcd(fs, fac);
	printf("%d %lld/%lld", cnt, fs / g, fac / g);
	return 0;
}
```

---

## 作者：「　」 (赞：4)

![](https://cdn.luogu.com.cn/upload/image_hosting/tr9vtl7f.png)

膜拜 $\text{h}\textcolor{red}{\text{ehezhou}}$ ！

## 题解

你发现相当于是给这 $m$ 个变量进行染色，每一个循环语句相当于是一个大小的限制比如说 $j\le i\le k$ 之类的，然后问你染色的方案数。

我们可以对于一个 $i\le j$ ，我们可以建一条有向边 $i->j$ ，表示在遍历这张图的时候 $i$ 需要出现在 $j$ 的前面，然后发现对于其中的强连通分量，他必须是全部相同的，你就直接缩点即可，然后剩下的就是一个 $DAG$ 。

然后就变成了 $DAG$ 上的染色方案数，这个东西好像可以状压~~，具体明天在想吧，我困了~~。

---

由于我们考虑的是渐进复杂度，所以虽然对于一个限制 $i\le j$ 存在 $i=j$ 的情况，我们可以不用考虑，因为他在其中所占的比例过于小，相对于极限来说。于是题目就变成了一张 $DAG$ 的 $top$ 序数量。（我在想是不是考虑了就错了？不是很明白。。。）

 我们考虑状压 $dp$ ，设 $f_i$ 表示在已经访问过的点的状态为 $i$ 的时候，其 $top$ 序数量是多少。然后拿头硬转移就可以了吧。

## 代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=25;
int n=0,m;char s[N];
int id[256];
struct Graph{
	struct Edge{int nxt,from,to;}e[N<<1];int fir[N],size=0;
	void add(int u,int v){e[++size]=(Edge){fir[u],u,v},fir[u]=size;}
}g1,g2;
int bel[N],tot=0;
int dfn[N],low[N],cnt=0;
stack<int> h;bool vis[N];
void tarjan(int u){
	dfn[u]=low[u]=++cnt;
	vis[u]=true,h.push(u);
	for(int i=g1.fir[u];i;i=g1.e[i].nxt){
		if(!dfn[g1.e[i].to]){
			tarjan(g1.e[i].to);
			low[u]=min(low[u],low[g1.e[i].to]);
		}
		else if(vis[g1.e[i].to]) low[u]=min(low[u],dfn[g1.e[i].to]);
	}
	if(dfn[u]==low[u]){
		++tot;
		while(h.top()!=u)
		vis[h.top()]=false,bel[h.top()]=tot,h.pop();
		vis[h.top()]=false,bel[h.top()]=tot,h.pop();
	}
}
int f[1<<N],deg[N];
int gcd(int a,int b){return b==0?a:gcd(b,a%b);}
signed main(){
	cin>>m;
	for(int i=1;i<m;++i){
		scanf("%s",s+1),scanf("%s",s+1),id[(int)s[1]]=++n;
		scanf("%s",s+1),scanf("%s",s+1);
		if('a'<=s[7]&&s[7]<='z') g1.add(id[(int)s[7]],n);
		scanf("%s",s+1);
		if('a'<=s[1]&&s[1]<='z'&&s[1]!='n') g1.add(n,id[(int)s[1]]);
	}
	scanf("%s",s+1);
	for(int i=1;i<=n;++i){
		if(dfn[i]) continue;
		tarjan(i);
	}
	for(int i=1;i<=g1.size;++i){
		if(bel[g1.e[i].from]!=bel[g1.e[i].to]){
			g2.add(bel[g1.e[i].to],bel[g1.e[i].from]);
		}
	}
	printf("%lld ",tot);
	f[0]=1;
	for(int now=0;now<(1<<tot);++now){
		for(int i=1;i<=tot;++i){
			if(now&(1<<(i-1))) continue;
			bool flag=true;
			for(int j=g2.fir[i];j;j=g2.e[j].nxt){
				flag&=(bool)(now&(1<<(g2.e[j].to-1)));
			}
			if(!flag) continue;
			// printf("%lld %lld %lld %lld\n",now,i,now|(1<<(i-1)),f[now]);
			f[now|(1<<(i-1))]+=f[now];
		}
	}
	int tmp,res=1;
	for(int i=1;i<=tot;++i) res*=i;
	tmp=gcd(res,f[(1<<tot)-1]);
	printf("%lld/%lld\n",f[(1<<tot)-1]/tmp,res/tmp);
	return 0;
}
```



---

