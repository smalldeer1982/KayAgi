# [POI 2019/2020 R1] Przedszkole / 幼儿园

## 题目背景

幼儿园的早上，老师们要给小孩子发玩具。

## 题目描述

有些小孩子玩玩具是自己一个人玩，有些小孩子是成对玩耍。

现在有 $n$ 个小孩子，这 $n$ 个小孩子可以分为 $m$ 对。

有 $k$ 种玩具，要发放给这些小孩子，必须保证在一对内的小孩子拿到的玩具不同。

求一共有多少种发放方案。

因为要发放的天数很多，所以给定 $z$ 组询问，这 $z$ 组询问中 $n,m$ 和对应的对是不变的，变的是 $k$。

## 说明/提示

#### 样例说明

两个附加样例请见附加文件中的 sample 1/2.in 和 sample 1/2.out。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（8 pts）：$n,k \le 8$，$z \le 50$。
- Subtask 2（26 pts）：$n \le 15$。
- Subtask 3（33 pts）：$m \le 24$。
- Subtask 4（33 pts）：一个小朋友恰好在两对小朋友。

对于 $100\%$ 的数据，$1 \le n \le 10^5$，$0 \le m \le \min(10^5,\dfrac{n^2-n}{2})$，$1 \le z \le 1000$，$1 \le k \le 10^9$。

对于其中 $50\%$ 的数据，$z=1$。

#### 说明

翻译自 [POI 2019](https://sio2.mimuw.edu.pl/c/oi27-1/dashboard/) D [Przedszkole](https://sio2.mimuw.edu.pl/c/oi27-1/p/prz/)。

## 样例 #1

### 输入

```
4 4 1
1 2
2 3
1 3
3 4
3```

### 输出

```
12```

## 样例 #2

### 输入

```
5 10 2
1 2
1 3
1 4
1 5
2 3
2 4
2 5
3 4
3 5
4 5
5
6```

### 输出

```
120
720```

## 样例 #3

### 输入

```
11 40 1
8 1
4 1
3 8
2 6
9 8
11 5
2 5
2 1
11 4
10 6
11 10
9 7
10 4
6 9
9 10
2 11
6 7
8 2
10 8
3 6
11 9
1 10
4 3
6 11
3 11
4 5
8 7
10 3
11 7
9 2
8 6
2 3
3 7
8 4
9 5
4 9
7 2
5 10
10 2
6 4
15```

### 输出

```
142679253```

# 题解

## 作者：MatrixCascade (赞：4)

没意思的缝合怪。

Subtask1 直接暴力 dfs，好像还得剪枝不然过不去。

Subtask2 直接状压 dp，设 $dp_{i,j}$ 表示 i 这个状态中的所有小孩用了**正好** j 种玩具的方案数，预处理出 $f_i$ 表示 $i$ 这个集合里面可以用同一种玩具，$dp$ 转移的时候使用子集枚举加速即可，虽然查询中的玩具总数会很多，但是你最多用到 $n$ 种。$dp$ 数组预处理出来，查询再加个组合数即可。

Subtask3 是边数很小，这提示我们用边数相关的做法。直接枚举 **钦定 $S$ 集合里面的边强制同种颜色的方案数**，答案就是 $k^w$，$w$ 是连通块个数，于是你只要把连通块个数为 $j$ 的系数预处理出来就行了，每次查询就是 $O(m)$ 的。

注意预处理的实现要精细一点，可以用 dfs 枚举状态+可撤销并查集。如果实现不好很容易被卡常。

Subtask4 不难发现是形成若干个环，但是你只需要考虑环的长度即可。然后就有一个用烂了的套路是本质不同的环的个数只有 $\sqrt n$ 个，把同类环合并就可以了。

在考虑如何求 $f(n,k)$ (n 个点的环用 k 种颜色的方案数，相邻不同色)先看看这个东西能不能递推。考虑枚举第一个点和第 $n-1$ 个点颜色是否一样，如果颜色一样，那么首先 $n$ 号点有 $k-1$ 种取值，然后你可以把 $1,n,n-1$ 合并起来看成一个点，剩下的就为 $f(n-2,k)$ ; 如果颜色不一样，那么 $n$ 号点有 $k-2$ 种取值，然后你可以把 $n$ 号点扔掉，就变成了 $f(n-1,k)$。 (因为你强制了 1 号不等于 n-1 号)

于是就有了递推式 : $f(n,k)=(k-2)f(n-1,k)+(k-1)f(n-2,k)$。

发现是只与前两项有关的递推 ! 解一下特征方程就可以得到 $f(n,k)=(k-1)^n+(k-1)
\times(-1)^n$。

再加上本质不同的环合并，每次查询就可以在 $\sqrt n \times \log$ 时间下完成。

---

## 作者：北射天狼 (赞：2)

# 目录



### subtask #1

### subtask #2

### subtask #3

### subtask #4

### 完整代码

----
[题目链接](https://www.luogu.com.cn/problem/P6662)

本题解主要借鉴了大佬 [7KByte](https://www.luogu.com.cn/user/119261) 的博客。


### subtask#1

观察到 $n,k\le 8$，可以并入 subtask#2 或者 subtask#3，在这里不做讨论。

### subtask#2

观察到 $n\le 15$，考虑枚举每一个点的颜色，由于点数较少，考虑状态压缩。

设当前状态为集合 $S$，用来表示图中每一个点有没有在集合中。若有状态集合 $K$，满足 $K \subseteq S$，且 $K$ 不为空集，其内部点也没有连边，则说明我们可以将 $S$ 中所有在 $K$ 中节点填上一种新的颜色。考虑预处理出所有像这样的 $K$，以方便进行状态转移。

显然我们可以用 $n$ 位二进制表示 $S$ 和 $K$。也就是对 $\forall_{1\le i \le n}$，有 $S$ 或 $K$ 的第 $i$ 位为 $1$，则说明点 $i$ 在 $S$ 或 $K$ 中。

考虑用数组 $check_{i}$ 维护节点 $i$ 能通过一条边能到达的点（不包括点 $i$，也同样用二进制表示）。显然，如果有状态 $K$ 对于任意节点 $i$ 有：```(K>>i) & 1```，则说明 $K$ 中包含点 $i$。此时如果 $K$ 又满足```(check[i] & k) == 1```，则说明 $K$ 中包含节点 $i$ 能一步到达的点，并且 $K$ 内部还有 $i$ 这个节点，说明其内部有点与 $i$ 连边。由上文可知，这样的 $K$ 明显是不符合要求的，用 ```vis[k] = 1```标记。


给出判断 $K$ 的代码：
```
for (int i=0;i<(1<<n);i++){//显然为 K 的值域
    for (int j=0;j<n-1;j++){ // 对节点数减去一方便进行二进制操作。
	    if (((i >> j) & 1) && (check[j] & i))//见上
	    vis[i] = 1;
	}
}
```

用数组 $f[i][S]$ 表示填了 $i$ 种颜色，当前状态为 $S$ 时的方案总数。

对于所有符合要求的状态 $K$，如果要将这些属于 $K$ 的点改变颜色，则就相当于求剩下的点的方案，由于 $K \subseteq S$，则去掉 $K$ 中的 $1$，也就是去掉属于 $K$ 的节点的 $S$，其结果显然为 $ K\oplus S$。因为 $S$ 中去掉 $K$ 后，填的颜色肯定也少一种。则我们得到了状态转移方程：

$$f[i][S] = \sum f[i-1][K \oplus S]$$

特别的 $f[0][0] = 1$。

那最后的答案是多少呢？

考虑枚举选择的颜色数 $j$，显然就有 $C_k^j$ 种选择方案。答案即为：

$$ans = \sum_{j=1}^n \space C^j_k \times f[j][2^n-1]$$

其中 $2^n - 1$ 为最终状态。

给出部分核心代码：
```
    void main(){
		f[0][0] = 1;
		for (int i=1,u,v;i<=m;i++){
			u = read(); v = read();
			u--,v--;
			check[u] |= (1 << v);
			check[v] |= (1 << u);
		}
		for (int i=0;i<(1<<n);i++){
			for (int j=0;j<n-1;j++){
				if (((i >> j) & 1) && (check[j] & i))//k has a circle inside
				    vis[i] = 1;
			}
		}
		for (int i=1;i<=n;i++){
			for (int j=1;j<(1<<n);j++){//非空子集
				for (int k = j;k;k = (k-1)&j){
					if (!vis[k]) f[i][j] = (f[i][j] + f[i - 1][j ^ k]) % Mod;
				}
			}
		}
		while (T--){
			int x,ans = 0;x = read();
			for (int i=1;i<=n;i++){
				ans = (ans + c(x,i) * f[i][(1 << n) - 1] % Mod) % Mod;
			}
			printf("%lld\n",ans);
		}
	}
```

总时间复杂度约为 $O(n3^n + Tn^2)$。

* Q.为什么枚举子集的复杂度为 $n3^n$ 次方？

* A.由[这篇讨论](https://www.luogu.com.cn/discuss/643825)可知，对于每一个 $n$ 位二进制数，枚举他的子集。假设它**有** $i$ 位是 $1$，他就有 $C_n^i$ 种情况，他的子集也就有 $2^i-1$ 种情况（空集不被计算在内），枚举了 $n$ 次。则最后的复杂度为 $O(n\sum_{i=1}^n C_n^i \times 2^i) = O(n(2+1)^n) = O(n3^n)$。枚举空集的复杂度可以忽略不计，所以不被计算在内。

---
### subtask3

观察到 $m\le 24$，则边就比较小，比较容易想到 $O(2^n)$ 的做法。

枚举每一条边的两个节点的状态是否相同，计算出不符合题目要求的方案数，用总方案减去即可。

但如果仅仅是这样做容易重复，考虑容斥原理。设有 $i$ 个点**及以上**不符合题目的方案为集合 $A_i$。

显然 $\vert A_i\vert = c_{n-i} \times k^{n-i}$，其中 $c_{n-i}$ 是有 $i$ 个点不合法的方案数。除了这 $i$ 个点其余点什么颜色都可以（注意看 $A$ 的定义），所以乘上 $k^{n-i}$。

如果你实在是不理解，建议可以看一下 [OI-WIKI](https://oiwiki.org/math/combinatorics/inclusion-exclusion-principle/)。

最后的结论是这样的：

$$\vert \bigcup_{i=1}^n A_i  \vert = \sum_{j=1}^n(-1)^{j-1} \vert A_{j}\vert$$

加了绝对值的集合表示集合的大小。

显然最后的答案是 $k^n - \vert \bigcup_{i=1}^{\min\{m,n\}} A_i  \vert$，因为总方案数是 $k^n$，不符合题目的总数是 $\vert \bigcup_{i=1}^{\min\{m,n\}} A_i  \vert$。即若 $n\ge m$，就不可能会有 $m+1$ 个点不符合题意（每条边至多产生一个不符合题意点点）。

将其化简：
$k^n - \vert \bigcup_{i=1}^{\min\{m,n\}} A_i  \vert$

$ =\vert \bigcup_{i=0}^{\min\{m,n\}} A_i  \vert$

$= \sum_{i=0}^{\min\{m,n\}}(-1)^ic_{n-i}\times k^{n-i}$

递归遍历每一条边，分为两端节点相同或不相同两种情况递归，如果最后遍历了偶数次，说明改变了偶数条边，由上可知要加方案数，否则减去方案数。

预处理出 $c_i$ 即可。

考虑使用可撤销并查集维护每一个点的相同状态，在递归每一条边的时候，如果这条边的两个端点已经是同一种颜色了，则直接返回，因为没有什么需要更新的了，是一种重复的情况。

如果不为空，则我们用可撤销并查集连边，表示这两个点是同种颜色，进行递归，再回滚回历史状态，再次递归即可预处理出 $c_i$。

注意，千万不可以写路径压缩，写一个见祖宗。

* Q.为什么不能写啊？

* A.因为我们要维护这个并查集树的结构，想一想，如果我们进行回滚历史状态操作时，发现有一些父亲为 $x$ 的节点，因为路径压缩，父亲节点变成了 $y$ ，无法维护 $x$ 所在的联通块不变，回滚历史状态操作自然也就错了。

递归代码：

```
	void dfs(int x,int cnt,int op){
    //x为边，cnt为下标，op就是把上面的公式正负号滚到下面了。
		if (x == m+1){
			c[cnt] += op;
			return ;
		}
		int fatheru = find(edge[x].u);
		int fatherv = find(edge[x].v);
		if (fatheru == fatherv){
		    return ;
		} else {
			dfs(x+1,cnt,op);
			f[fatheru] = fatherv;//ji fu ou zheng
			dfs(x+1,cnt-1,-op);
			f[fatheru] = fatheru;
		}
	}
```

---

### subtask 4#

观察一下，发现图变成了一堆环。

这不就好做了吗？统计每一个环的大小和个数，相乘即可。

假设这个长度为 $n$ 的环有 $f[n]$ 种填法，显然有：

$$f[3] = k(k-1)(k-2)$$

假如第 $1$ 个点和第 $n-1$ 个点颜色相同，第 $n$ 个点有 $k-1$ 种选法，则第 $2$ 个点的颜色和第 $1$，$n-1$ 个点不同。相当于把 $1$，$n-1$ 这两个点去掉后点环，因此方案数为 $(k-1)\times 
f[n-2]$。

假如第 $1$ 个点的颜色和第 $n-1$ 个点的颜色不同。则 $n$ 有 $k-2$ 种取值。相当于一个长度为 $n-1$ 的环。即 $(k-2)\times f[n-1]$。

综上：

$$f[n] = (k-1)f[n-2] +(k-2)f[n-1]$$

构造

$$f[n]+xf[n-1]=y(f[n-1]+xf[n-2])$$

所以： $y - x = k-2,yx = k-1$

用眼睛都能看出来：$x = 1,y = k-1$

所以 $\{f[n] +f[n-1]\}$ 为等比数列，公比为 $k-1$，第三项为 $(k-1)^3 -(k-1)$。

不妨用手推出 $f[4]$。若第 $1$ 点和 $3$ 颜色相同，则点 $4$ 和点 $2$ 各有 $k-1$ 种取法，为 $k\times(k-1)^2$，若不同，则各有 $k-2$ 种取法，化简知：

$f[4] = k\times(k-1)^2+(k-2)^2\times k\times (k-1)$

$= k\times(k-1)(k^2-4\times k + 4 + k-1)$

$=(k-1)(k^3-3k^2+3k -1) +(k-1)$

$= (k-1)^4 + (k-1)$

若 $n$ 是偶数：

$f[n] = -f[3] + \sum_{i=4}^{n} (-1)^i\times(f[i]  +f[i-1]) $

不难看出公比是 $1-k$，由等比数列求和公式：

$f[n] = -f[3] + (f[3]+f[4])\times \frac{1 - (1-k)^{n-3}}{1-(1-k)}$

$=-(k-1)^3+(k-1) + ((k-1)^3 +(k-1)^4)\times  \frac{1 - (1-k)^{n-3}}{k}$

$=-(k-1)^3+(k-1) + (k-1)^3k\times  \frac{1 + (k-1)^{n-3}}{k}$

$=-(k-1)^3+(k-1) + (k-1)^3 + (k-1)^{n}$

$=(k-1)^n + (k-1)$


当 $n$ 是奇数：

$f[n] = f[3] + \sum_{i=3}^{n-1} (-1)^i\times(f[i]  +f[i+1]) $

不难看出公比是 $1-k$，由等比数列求和公式：

$f[n] = f[3] -(f[3]+f[4])\times \frac{1 - (1-k)^{n-3}}{1-(1-k)}$

$=(k-1)^3-(k-1) - ((k-1)^3 +(k-1)^4)\times  \frac{1 - (1-k)^{n-3}}{k}$

$=(k-1)^3-(k-1) - (k-1)^3k\times  \frac{1 - (k-1)^{n-3}}{k}$

$=(k-1)^3-(k-1) - (k-1)^3 + (k-1)^{n}$

$=(k-1)^n - (k-1)$

综上：

$$f[n] = (k-1)^n + (-1)^n(k-1)$$

用一遍 dfs 统计出各个环的个数，代入计算即可。


### 完整代码
```
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int Mod = 1e9 + 7;
const int N = 1e5 + 5;
inline int read(){
	int s = 0,f = 1;char c = getchar();
	while (!isdigit(c)){if (c == '-')f = -1;c = getchar();}
	while (isdigit(c)){s = (s << 3) + (s << 1) + (c ^ 48);c = getchar();}
	return s*f;
}
int T,n,m;
namespace task1{
	int check[23];
	int vis[1 << 15];
	int f[16][1 << 15];
	int qpow(int x,int y){
		int res = 1;
		for (;y;y>>=1,x = x * x % Mod)
		    if (y & 1)
		        res = res * x % Mod;
		return res;
	}
	int c(int x,int y){
		if (x < y)
		    return 0;
		int sum = 1;
		for (int i=1;i<=y;i++){//y!/x! * (y - x)!
			sum = sum * (x-i+1) % Mod * qpow(i,Mod-2) % Mod;
		}
		return sum;
	}
	void main(){
		f[0][0] = 1;
		for (int i=1,u,v;i<=m;i++){
			u = read(); v = read();
			u--,v--;
			check[u] |= (1 << v);
			check[v] |= (1 << u);
		}
		for (int i=0;i<(1<<n);i++){
			for (int j=0;j<n-1;j++){
				if (((i >> j) & 1) && (check[j] & i))//k has a circle inside
				    vis[i] = 1;
			}
		}
		for (int i=1;i<=n;i++){
			for (int j=1;j<(1<<n);j++){
				for (int k = j;k;k = (k-1)&j){
					if (!vis[k]) f[i][j] = (f[i][j] + f[i - 1][j ^ k]) % Mod;
				}
			}
		}
		while (T--){
			int x,ans = 0;x = read();
			for (int i=1;i<=n;i++){
				ans = (ans + c(x,i) * f[i][(1 << n) - 1] % Mod) % Mod;
			}
			printf("%lld\n",ans);
		}
	}
}
namespace task2{
	int f[N],c[N];
	struct node{
		int u,v;
	}edge[N<<1];
	int qpow(int x,int y){
		int res = 1;
		for (;y;y>>=1,x = x * x % Mod)
		    if (y & 1)
		        res = res * x % Mod;
		return res;
	}
	int find(int x){
		if (x == f[x])
            return f[x];
        return find(f[x]);
	}
	void dfs(int x,int cnt,int op){
		if (x == m+1){
			c[cnt] += op;
			return ;
		}
		int fatheru = find(edge[x].u);
		int fatherv = find(edge[x].v);
		if (fatheru == fatherv){
		    return ;
		} else {
			dfs(x+1,cnt,op);
			f[fatheru] = fatherv;//ji fu ou zheng
			dfs(x+1,cnt-1,-op);
			f[fatheru] = fatheru;
		}
	}
	void main(){
		for (int i=1;i<=m;i++)
		    edge[i].u = read(),edge[i].v = read();
		for (int i=1;i<=n;i++)
		    f[i] = i;
		dfs(1,n,1);
		while (T--){
			int x,ans = 0;
			x = read();
			for (int i=0;i<=min(n,m);i++)
			    ans = (ans + c[n - i] * qpow(x,n - i) % Mod + Mod) % Mod;
			printf("%lld\n",(ans + Mod) % Mod);
		}
	}
}
namespace task3{
	struct node{
		int v,next;
	}tree[N<<1];
	int head[N],cnt,c[N],q[N],top=0;
	int vis[N];
	int qpow(int x,int y){
		int res = 1;
		for (;y;y>>=1,x = x * x % Mod)
		    if (y & 1)
		        res = res * x % Mod;
		return res;
	}
	int dfs(int u){
		vis[u] = 1;
		int sz = 1;
		for (int i=head[u];i;i=tree[i].next){
			int v = tree[i].v;
			if (vis[v])
			    continue;
			sz += dfs(v);
		}
		return sz;
	}
	int calc(int x,int y){
		return (qpow(x-1,y) + ((y&1)?-1:1) * (x-1)) % Mod;
	}
	void add(int u,int v){
		tree[++cnt].next = head[u];
		tree[cnt].v = v;
		head[u] = cnt;
	}
	void main(){	
		for (int i=1,u,v;i<=m;i++){
			u = read();v = read();
			add(u,v);
			add(v,u);
		}
		for (int i=1;i<=n;i++){
			if (!vis[i])
				c[dfs(i)]++;
		}
		for (int i=1;i<=n;i++)
			if (c[i])
			    q[++top] = i;
		while (T--){
			int x,ans = 1;
			x = read();
			for (int i=1;i<=top;i++){
				ans = ans * qpow(calc(x,q[i]),c[q[i]]) % Mod;
			}
			printf("%lld\n",(ans + Mod) % Mod);
		}
	}
}
signed main()
{
    n = read(); m = read(); T = read();
    if (n <= 15)
        task1::main();
    else if (m <= 24)
        task2::main();
    else 
	    task3::main();
	return 0;
}
```


---

## 作者：EuphoricStar (赞：1)

$k$ 染色问题。给定 $n$ 个点 $m$ 条边无向图，求有多少种给每个点赋点权 $a_u \in [1, k]$ 的方案，使得 $\forall (u, v) \in E, a_u \ne a_v$。

### Subtask $1$：$n \le 15$。

考虑因为最终只会用到最多 $n$ 种颜色，所以设恰好用了 $t$ 种颜色，把 $k$ 种颜色映射到 $[1, t]$ 中，方案数为 $\binom{k}{t}$；然后再状压 dp，设 $f_{i, S}$ 表示已经用了前 $i$ 种颜色，当前 $S$ 集合中的点已经染色。转移枚举 $S$ 的严格超集即可。时间复杂度 $O(n3^n + qn)$。

### Subtask $2$：$m \le 24$。

实际上这是 [ABC294Ex K-Coloring](https://www.luogu.com.cn/problem/AT_abc294_h)。 考虑一些与边数有关的指数级算法。考虑容斥，钦定 $S \subseteq E$ 中的 $(u, v)$ 必须满足 $a_u = a_v$。设最后连完 $S$ 中的边后连通块数为 $c$，答案即 $\sum\limits_{S \subseteq E} (-1)^{|S|} k^c$。对于每个 $c$ 预处理有多少个边集最后会形成 $c$ 个连通块，即可 $O(m)$ 回答单次询问。同时因为 $m$ 很大要注意实现精细。可以 dfs 枚举每条边是否进入 $S$，一个简单的剪枝是递归到一条边时 $u, v$ 在同一个连通块就立刻退出，因为选和不选的贡献抵消。时间复杂度 $O(n2^m + qm \log n)$。

### Subtask $3$：每个连通块是一个环。

这是 [ABC307E Distinct Adjacent](https://www.luogu.com.cn/problem/AT_abc307_e)。每个环相互独立，所以只用考虑一个环，最后方案数乘起来。设 $f_n$ 为 $n$ 个点的环的方案数，转移考虑删掉点 $n$，如果点 $1$ 和点 $n - 1$ 颜色相同那么把它们缩起来，同时点 $n$ 有 $n - 1$ 种选颜色的方案；否则点 $n$ 有 $k - 2$ 种选颜色的方案，因为点 $1$ 和点 $k - 1$ 颜色不同所以可以直接删掉点 $n$。因此有 $f_n = (k - 1) f_{n - 2} + (k - 2) f_{n - 1}$。这个东西还有通项公式 $f_n = (k - 1)^n + (k - 1) (-1)^n$。时间复杂度 $O(nq + m)$。

```cpp
// Problem: P6662 [POI 2019] Przedszkole
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6662
// Memory Limit: 128 MB
// Time Limit: 1500 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<int, int> pii;

const int maxn = 100100;
const ll mod = 1000000007;

inline ll qpow(ll b, ll p) {
	ll res = 1;
	while (p) {
		if (p & 1) {
			res = res * b % mod;
		}
		b = b * b % mod;
		p >>= 1;
	}
	return res;
}

ll n, m, q;
pii E[maxn];
vector<int> G[maxn];

inline void upd(ll &x, ll y) {
	((x += y) >= mod ? x -= mod : 0);
}

namespace Sub1 {
	const int maxm = (1 << 15) + 50;
	
	ll f[19][maxm], fac[maxn], ifac[maxn];
	bool g[maxm];
	
	inline ll C(ll n, ll m) {
		if (n < m || n < 0 || m < 0) {
			return 0;
		} else {
			ll res = ifac[m];
			for (ll i = n - m + 1; i <= n; ++i) {
				res = res * i % mod;
			}
			return res;
		}
	}
	
	void solve() {
		for (int S = 1; S < (1 << n); ++S) {
			g[S] = 1;
			for (int i = 1; i <= n; ++i) {
				if (S & (1 << (i - 1))) {
					for (int j : G[i]) {
						if (S & (1 << (j - 1))) {
							g[S] = 0;
							break;
						}
					}
				}
			}
		}
		f[0][0] = 1;
		for (int i = 0; i < n; ++i) {
			for (int S = 0; S < (1 << n); ++S) {
				if (!f[i][S]) {
					continue;
				}
				for (int T = (S + 1) | S; T < (1 << n); T = (T + 1) | S) {
					if (g[S ^ T]) {
						upd(f[i + 1][T], f[i][S]);
					}
				}
			}
		}
		fac[0] = 1;
		for (int i = 1; i <= n; ++i) {
			fac[i] = fac[i - 1] * i % mod;
		}
		ifac[n] = qpow(fac[n], mod - 2);
		for (int i = n - 1; ~i; --i) {
			ifac[i] = ifac[i + 1] * (i + 1) % mod;
		}
		while (q--) {
			ll x, ans = 0;
			scanf("%lld", &x);
			for (int i = 1; i <= min(n, x); ++i) {
				ans = (ans + C(x, i) * f[i][(1 << n) - 1]) % mod;
			}
			printf("%lld\n", ans);
		}
	}
}

namespace Sub2 {
	ll f[maxn];
	int fa[maxn];
	
	int find(int x) {
		return fa[x] == x ? x : find(fa[x]);
	}
	
	void dfs(int d, int cnt, int op) {
		if (d > m) {
			f[cnt] += op;
			return;
		}
		int x = find(E[d].fst), y = find(E[d].scd);
		if (x == y) {
			return;
		}
		fa[x] = y;
		dfs(d + 1, cnt - 1, -op);
		fa[x] = x;
		dfs(d + 1, cnt, op);
	}
	
	void solve() {
		for (int i = 1; i <= n; ++i) {
			fa[i] = i;
		}
		mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
		for (int i = 1; i <= m; ++i) {
			if (rnd() & 1) {
				swap(E[i].fst, E[i].scd);
			}
		}
		dfs(1, n, 1);
		while (q--) {
			ll x, ans = 0;
			scanf("%lld", &x);
			for (int i = n; i >= max(1LL, n - 60); --i) {
				ans = (ans + (f[i] + mod) * qpow(x, i)) % mod;
			}
			printf("%lld\n", ans);
		}
	}
}

namespace Sub3 {
	int fa[maxn], sz[maxn];
	
	int find(int x) {
		return fa[x] == x ? x : fa[x] = find(fa[x]);
	}
	
	inline void merge(int x, int y) {
		x = find(x);
		y = find(y);
		if (x != y) {
			fa[x] = y;
			sz[y] += sz[x];
		}
	}
	
	inline ll calc(ll n, ll m) {
		return (qpow(m - 1, n) + ((n & 1) ? mod - (m - 1) : m - 1)) % mod;
	}
	
	void solve() {
		for (int i = 1; i <= n; ++i) {
			fa[i] = i;
			sz[i] = 1;
		}
		for (int i = 1; i <= m; ++i) {
			merge(E[i].fst, E[i].scd);
		}
		vector<ll> vc;
		for (int i = 1; i <= n; ++i) {
			if (fa[i] == i) {
				vc.pb(sz[i]);
			}
		}
		while (q--) {
			ll x;
			scanf("%lld", &x);
			ll ans = 1;
			for (ll y : vc) {
				ans = ans * calc(y, x) % mod;
			}
			printf("%lld\n", ans);
		}
	}
}

void solve() {
	scanf("%lld%lld%lld", &n, &m, &q);
	for (int i = 1, u, v; i <= m; ++i) {
		scanf("%d%d", &u, &v);
		G[u].pb(v);
		G[v].pb(u);
		E[i] = mkp(u, v);
	}
	if (n <= 15) {
		Sub1::solve();
		return;
	}
	if (m <= 24) {
		Sub2::solve();
		return;
	}
	Sub3::solve();
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}

```


---

## 作者：Fishing_Boat (赞：1)

## subtask #1 ##
直接暴搜。
## subtask #2 ##
设 $dp_{i,j}$ 表示正好用了 $i$ 种颜色且状态为 $j$ 的方案数，记录哪些点可以选择同一种颜色。答案即为
$$ \sum\limits_{i=1}^nC_{k}^{i}\times dp_{i,2^n-1} $$
时间复杂度 $O(n\times3^n)$。
### 代码 ###
```cpp
const int P(1e9+7);

int Pow(int x,int k){
	int res=1;
	while(k){
		if(k&1) res=res*x%P;
		x=x*x%P;
		k>>=1;
	}
	return res;
}

void add(int &x,int y){
	x=(x+y)%P;
}
struct subtask1{
	int C(int x,int y){
		if(x<y) return 0;
		int res=1;
		for(int i=1;i<=y;i++){
			res=res*(x-i+1)%P*Pow(i,P-2)%P;
		}
		return res;
	} 
	bool vis[20][20],check[1<<15|1];
	int dp[20][1<<15|1];
	void solve(){
		for(int i=1;i<=m;i++){
			int x,y;cin>>x>>y;
			vis[x][y]=vis[y][x]=1;
		}
		for(int i=0;i<(1<<n);i++){
			check[i]=1;
			for(int j=1;j<=n;j++){
				if(!(i&(1<<j-1))) continue;
				for(int k=1;k<=n;k++){
					if(!(i&(1<<k-1))) continue;
					if(vis[j][k]) check[i]=0;
				}
			}
		}
		dp[0][0]=1;
		for(int i=1;i<=n;i++){
			for(int j=1;j<(1<<n);j++){
				for(int k=j;k;k=(k-1)&j){// 注意不能为空集，因为 dp 的定义是正好用了 i 种颜色
					if(check[k]) add(dp[i][j],dp[i-1][j^k]);
				}
			}
		}
		while(t--){
			int x,res=0;cin>>x;
			for(int i=1;i<=n;i++){
				add(res,C(x,i)*dp[i][(1<<n)-1]%P);
			}
			cout<<res<<'\n';
		}
	}
}sub1;

```
## subtask #3 ##
枚举每一对小孩玩具是否相同，然后进行简单容斥，即奇加偶减。可以使用可撤销并查集来维护，假设共有 $x$ 种方案使得最终有 $y$ 对小孩玩具相同，则对答案的贡献是
$$(-1)^y\times x\times k^{n-x+1}$$
时间复杂度 $O(m\times 2^m)$。
### 代码 ###
```cpp
struct subtask2{
	struct edge{
		int u,v;
	}e[30];
	int fa[100005],cnt[100005];
	int get(int x){
		if(x==fa[x]) return x;
		return get(fa[x]);
	}
	void dfs(int dep,int x,int op){// 这里的 x 指的是形成的联通块数
		if(dep==m+1){
			cnt[x]+=op;
			return ;
		}
		int u=get(e[dep].u),v=get(e[dep].v);
		if(u==v) return ;
		dfs(dep+1,x,op);
		fa[u]=v;
		dfs(dep+1,x-1,-op);
		fa[u]=u;
	}
	void solve(){
		for(int i=1;i<=m;i++){
			cin>>e[i].u>>e[i].v;
		}
		for(int i=1;i<=n;i++){
			fa[i]=i;
		}
		dfs(1,n,1);
		while(t--){
			int x,res=0;cin>>x;
			for(int i=0;i<=min(n,m);i++){
				add(res,cnt[n-i]*Pow(x,n-i)%P);
			}
			cout<<(res+P)%P<<'\n';
		}
	}
}sub2;
```
## subtask #4 ##
容易发现图变成了许多相互独立的环。设 $f_i$ 表示一个大小为 $i$  的环方案数。则 
$$f_1=k,f_2=k\times (k-1),f_3=k\times(k-1)\times(k-2)$$
自第 $4$ 项以后，
$$f_i=(k-2)\times f_{i-1}+(k-1)\times f_{i-2}$$
这是一个经典的小奥问题，可以理解为新加入一个点，若与其相邻的两个同色，则可以将这两个点看作一个点，从而形成一个环，而新加入的点共有 $k-1$ 种选择，若与其相邻的两个点不同色，则可以直接看作一个环，新加入的点共有 $k-2$ 种选择。

这样就可以做到 $O(nz)$，当然这里还可以优化，不过已经足以通过本题了。
###
```cpp
struct subtask3{
	vector <int> G[100005];
	int tot,sz,f[100005];
	bool vis[100005];
	vector <int> v;
	void dfs(int u){
		sz++;vis[u]=1;
		for(int v:G[u]){
			if(!vis[v]) dfs(v);
		}
	}
	void solve(){
		for(int i=1;i<=m;i++){
			int u,v;cin>>u>>v;
			G[u].push_back(v);
			G[v].push_back(u);
		}
		for(int i=1;i<=n;i++){
			if(!vis[i]){
				sz=0;	
				dfs(i);
				v.push_back(sz);
			}
		}
		while(t--){
			int x,res=1;cin>>x;
			f[1]=x;f[2]=x*(x-1)%P;f[3]=x*(x-1)%P*(x-2)%P;
			for(int i=4;i<=n;i++){
				f[i]=((x-1)*f[i-2]%P+(x-2)*f[i-1]%P)%P;
			}
			for(int i:v){
				res=res*f[i]%P;
			}
			cout<<res<<'\n';
		}
	}
}sub3;
```

---

## 作者：yuanruiqi (赞：0)

比较无趣的一道缝合怪。下面将数据分三类解决：

- $n\le 15$：启发我们枚举子集，故有 $f_{s,i}$ 表示用恰好 $i$ 种颜色染集合 $s$ 中的点的方案数，转移可以枚举 $s$ 的所有包含 $\operatorname{lowbit}(s)$ 且构成独立集的子集。DP 复杂度为 $O(3^nn)$。对于每个询问得到 $k$ 之后枚举 $n$ 个点的总颜色数，$ans=\sum_{i=1}^{\min(k,n)}k^{\underline{i}}f_{2^n-1,i}$。询问复杂度 $O(qn)$。
- $m\le 24$：先只考虑单词询问。将边视作一个不合法事件，对其容斥，即钦定了边集 $S$ 连通后，贡献则为 $(-1)^{|S|}k^c$，其中 $c$ 为连通块数。由于只需要保留 $O(m)$ 个关键点，朴素实现是 $O(2^mm)$。考虑优化，注意到在 $S$ 中加入某条新边造成的贡献是容易处理的，所以可以使用可撤销并查集做到 $O(2^m\log m)$。$O(\log m)$ 为按秩合并的并查集复杂度。多次询问，我们只要对每个 $c$ 预处理出系数和即可。预处理复杂度如上，询问 $O(q(m+\log k))$。

- 构成若干个不交的环：只考虑有一个环的问题，令 $f_n$ 为欢长为 $n$ 的答案，有一个策略是第一个位置有 $k$ 种取法，接下来都与上一个位置不同，即 $(k-1)^{n-1}$。不合法情况当且仅当第一个位置和最后一个位置的颜色取等，不妨将它们视为合并。则方案为 $f_{n-1}$。故有 $f_n=k(k-1)^{n-1}-f_{n-1}$。需要注意的是，$f_1=0$，组合意义是自环不合法。有显然的通项公式为：
  $$
  \begin{align}
  f_n&=k(-1)^{n-1}\sum_{i=1}^{n-1}(1-k)^i\\
  f_n&=k(-1)^{n-1}(1-k)\frac{1-(1-k)^{n-1}}{1-(1-k)}\\
  f_n&=(-1)^{n}(k-1)+(k-1)^{n}
  \end{align}
  $$
  有一个著名结论是只有 $O(\sqrt{n})$ 种长度的环，所以复杂度为 $O(q\sqrt{n}\log n)$。

---

## 作者：7KByte (赞：0)

数数综合题。

对于子任务 $1$ 直接枚举所有点的颜色，同时记录一下当前是否满足条件，时间复杂度 $\mathcal{O}(nk^n)$ 。

对于子任务 $2$ 点数很小，考虑状压 $\rm DP$ 。

我们定义状态 $f[i][S]$ 表示使用恰好 $i$ 种颜色，其中状态 $S$ 中的点已经被染色的方案数。

初值 $f[0][0]=1$ ，转移 $f[i][j]=\sum f[i-1][j \oplus k]$ ，其中 $k$ 为 $j$ 的非空子集且 $k$ 中的点两两之间没有边。

最后再从 $k$ 种颜色中选出 $i$ 种颜色，答案为 $\sum\limits_{1\le i\le n} \dbinom{k}{i}f[i][2^n-1]$ 。

枚举子集的复杂度是 $\mathcal{O}(3^n)$ ，所以时间复杂度是 $\mathcal{O}(n3^n+Tn^2)$ 。

```cpp
namespace task1{
	int f[16][1<<15],ban[16],v[1<<15];
	int C(int x,int y){
		if(x<0||y<0||x<y)return 0;
		int cur=1;rep(i,1,y)cur=1LL*cur*(x-i+1)%P*Pow(i,P-2)%P;
		return cur;
	}
	void main(){
		int T;scanf("%d",&T);
		f[0][0]=1;int w=1<<n;
		rep(i,1,m){
			int x,y;scanf("%d%d",&x,&y);
			ban[x-1]|=1<<(y-1),ban[y-1]|=1<<(x-1);
		}
		rep(i,0,w-1)rep(j,0,n-1)if(((i>>j)&1)&&(ban[j]&i))v[i]=1;
		rep(i,1,n)rep(j,1,w-1)for(int k=j;k;k=(k-1)&j)
			if(!v[k])f[i][j]=(f[i][j]+f[i-1][j^k])%P;
		while(T--){
			int x,ans=0;scanf("%d",&x);
			rep(i,1,n)ans=(ans+1LL*f[i][w-1]*C(x,i))%P;
			printf("%d\n",ans);
		}
	}
}
```



对于子任务 $3$ ，边数很小 。

根据数据范围，考虑 $2^m$ 算法，除了状压 $\rm DP$ ，直接容斥的复杂度也是 $2^m$ 的。

所以我们钦定哪些边的两端相等，将答案乘以容斥系数即可。

具体我们可以用并查集维护，注意这里并查集不能路径压缩。

时间复杂度 $\mathcal{O}(m2^m+Tm\log P)$ 。

```cpp
namespace task2{
	int u[N],v[N],fa[N],c[N];
	inline int get(int x){
		while(x!=fa[x])x=fa[x];
		return x;
	}
	void dfs(int x,int cnt,int op){
		if(x>m)c[cnt]+=op;
		else{
			int p=get(u[x]),q=get(v[x]);
			if(p==q){
				dfs(x+1,cnt,op),dfs(x+1,cnt,-op);
			}
			else{
				dfs(x+1,cnt,op);fa[p]=q;dfs(x+1,cnt-1,-op);fa[p]=p;
			}
		}
	}
	void main(){
		int T;scanf("%d",&T);
		rep(i,1,m)scanf("%d%d",&u[i],&v[i]);
		rep(i,1,n)fa[i]=i;dfs(1,n,1);
		while(T--){
			int k,ans=0;scanf("%d",&k);
			rep(i,max(1,n-m),n)ans=(ans+1LL*c[i]*Pow(k,i))%P;
			printf("%d\n",(ans+P)%P);
		}
	}
}
```

对于子任务 $4$ ，图退化成若干个环。

不同的环之间互不相干，考虑对每个环单独计算。

我们定义状态 $f[i]$ 表示长度为 $i$ 的环染色方案数。

有初始状态 $f[3]=k(k-1)(k-2)$ 。

转移：如果第 $n-1$ 个点与第一个点颜色相同，第 $n$ 个点有 $k-1$ 种取值，方案数为 $(k-1)f[n-2]$ ，否则第 $n$ 个点有 $k-2$ 种取值，方案数为 $(k-2)f[n-1]$ 。

$$f[n]=(k-2)f[n-1]+(k-1)f[n-2]$$

这已经可以利用矩阵快速计算，也可以解递推式得到 $f[n]=(k-1)^n+(-1)^n(k-1)$ 。

环的个数可能很多，但是本质不同的环不超过 $\sqrt{n}$ ，所以我们将本质相同的环合并即可。

时间复杂度 $\mathcal{O}(T\sqrt{n}\log P)$ 。

```cpp
namespace task3{
	int h[N],tot,v[N],c[N],sta[N],top;
	struct edge{int to,nxt;}e[N<<1];
	void add(int x,int y){e[++tot].nxt=h[x];h[x]=tot;e[tot].to=y;}
	int dfs(int x){
		v[x]=1;int sz=1;
		for(int i=h[x];i;i=e[i].nxt)if(!v[e[i].to])sz+=dfs(e[i].to);
		return sz;
	}
	inline int calc(int x,int y){
		return (Pow(x-1,y)+(y&1?-1:1)*(x-1))%P;
	}
	void main(){
		int T;scanf("%d",&T);
		rep(i,1,m){
			int x,y;scanf("%d%d",&x,&y);
			add(x,y);add(y,x);
		}
		rep(i,1,n)if(!v[i])c[dfs(i)]++;
		rep(i,1,n)if(c[i])sta[++top]=i;
		while(T--){
			int k,ans=1;scanf("%d",&k);
			rep(i,1,top){
				ans=1LL*ans*Pow(calc(k,sta[i]),c[sta[i]])%P;
			}
			printf("%d\n",(ans+P)%P);
		}
	}
}
```



---

## 作者：船酱魔王 (赞：0)

# P6662 [POI 2019] Przedszkole 题解

## 题意回顾

求出 $ n $ 点 $ m $ 边无向图有多少种 $ k $ 种颜色的染色方案使得相邻边不同色。

多测，$ z $ 次给定 $ k $ 的值，单测试点内图的规模和结构不变。

$ n,m \le 10^5 $，$ z \le 1000 $，$ k \le 10^9 $。

## 分析

图着色问题不存在多项式时间复杂度做法，因此本题不存在对于普适性解决方法，观察数据范围可以发现每个子任务都满足一定的特殊限制，即我们要对于不同特殊限制下的简化问题分别求解，这类 OI 题目我们通常称为『多合一』。

### Subtask 1~2：$ n \le 15 $（34 分）

因为 $ k $ 很大，显然不能直接暴力，但 $ n $ 这么小可以设计巧妙的暴力。

我们考虑把点分为 $ k $ 类，每一类都要染上同一种颜色，不同类颜色不同，分完类后问题染色方案数可以用乘法原理轻松解决。

为了避免算重，显然不能存在空类，类的编号必须连续地从 $ 1 $ 标到 $ n $，因为交换两类的所有点后本质上一样，所以我们规定编号小的类的最小点号必须小于编号大的类的最小点号。

本题解中所示代码使用的实现方法为：按照点号小到大考虑每个点，先排除掉相邻点的归属类，再依次考虑归属于之前出现过的类还是新开辟一类。

因为 $ z $ 次改变 $ k $，所以我们实现时不能直接统计答案，要记录每一种类数的总方案数，询问时再统计答案。

爆搜时间复杂度玄学，我们考虑对于每个连通块分别爆搜，这样边数很少时每个连通块都很小，边数很多时大量不合法状态被剪枝，可以过。

### Subtask 3：$ m \le 24 $（33 分）

如果你对于算法复杂度能在合理时间内解决问题的规模上界很熟悉的话，可以发现 $ m $ 的范围比较适合 $ O(2^m) $ 附带一个比较小变量规模因子或一个合理范围的常数。

$ n $ 很大，但是很多点都是无意义的孤点，最后快速幂把孤点对于答案的贡献乘上即可。

让相连的点颜色不同很难，但我们让相邻的点颜色相同很好做，考虑容斥原理钦定某些边两端颜色相同，某些边不作限制。

注意需要将点离散化，要不然初始化并查集会浪费很多时间。

复杂度 $ O(2^mm) $。

可以加一个优化节约一半常数：当二进制枚举最后一位由 $ 0 $ 变 $ 1 $ 无进位时，显然可以直接在上一次枚举的基础上加边，不用再初始化并查集。

### Subtask 4：每个点度数为 $ 2 $（33 分）

可以发现每个连通块都是环。

$ n $ 点环上的 $ k $ 染色方案数记为 $ F_n $。

显然有 $ F_1=k $，$ F_2=k(k-1) $。

对于 $ n $ 个点的环，断环为链后方案数为 $ k(k-1)^{n-1} $，断点两边相同颜色的方案数需要减去，可以当成合并为一个点，则方案数为 $ F_{n-1} $。

故递推式为 $ F_n=k(k-1)^{n-1}-F_{n-1} $。

显然递推的复杂度是 $ O(n) $ 的，所有环互相独立，把方案数乘起来即可。

因为常数不大，所以 $ O(zn) $ 每次暴力递推可行。

判断三种数据点特性，按照所具有特性依以上方法分类处理即可。

## AC 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
const int N = 1e5 + 5;
const int mod = 1e9 + 7;
int n, m, z;
int col[N];
int fp[33][33];
int bf[N];
vector<int> g[N];
int popc[65536];
int vs[N];
void block(int u, int clr) {
    if(vs[u] == clr) return;
    vs[u] = clr;
    for(int i = 0; i < g[u].size(); i++) block(g[u][i], clr);
}
void brute(int u, int ci) {
    if(u > n) {
        bf[ci]++;
        return;
    }
    if(vs[u] != 1) {
        brute(u + 1, ci);
        return;
    }
    int used = 0;
    for(int i = 0; i < g[u].size(); i++) {
        used |= (1 << col[g[u][i]]);
    }
    for(int i = 1; i <= ci; i++) {
        if(!(used & (1 << i))) {
            col[u] = i;
            brute(u + 1, ci);
        }
    }
    col[u] = ci + 1;
    brute(u + 1, ci + 1);
    col[u] = 0;
}
int fa[53];
int getfa(int u) {
    if(fa[u] == u) return u;
    return fa[u] = getfa(fa[u]);
}
int pl = 0;
int lp[N];
int loop(int u, int fath) {
    if(vs[u] == 1) return 0;
    vs[u] = 1;
    for(int i = 0; i < g[u].size(); i++) {
        if(g[u][i] != fath) return loop(g[u][i], u) + 1;
    }
    return 114514;
}
int dp[N];
int ksm(int x, int y) {
    int res = 1;
    int mul = x;
    while(y) {
        if(y & 1) res = (long long)res * mul % mod;
        mul = (long long)mul * mul % mod, y >>= 1;
    }
    return res;
}
int main() {
    for(int i = 0; i < 65536; i++) {
        popc[i] = 0;
        int ii = i;
        while(ii) {
            popc[i]++;
            ii = (ii - 1) & ii;
        }
    }
    scanf("%d%d%d", &n, &m, &z);
    if(n <= 15) {
        int u, v;
        for(int i = 1; i <= m; i++) {
            scanf("%d%d", &u, &v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        for(int i = 1; i <= n; i++) {
            if(vs[i] == 2) continue;
            for(int j = 1; j <= n; j++) bf[j] = 0;
            block(i, 1);
            brute(i, 0);
            block(i, 2);
            fp[i][0] = 1;
            for(int j = 1; j <= n; j++) fp[i][j] = bf[j];
        }
        int cl;
        for(int i = 1; i <= z; i++) {
            scanf("%d", &cl);
            int tot = 1;
            int ans = 0;
            for(int ii = 1; ii <= n; ii++) {
                if(fp[ii][0] != 1) continue;
                ans = 0;
                for(int j = 1; j <= n; j++) {
                    int now = fp[ii][j];
                    for(int k = cl; k >= cl - j + 1; k--) now = (long long)now * k % mod;
                    ans += now;
                    ans %= mod;
                }
                tot = (long long)tot * ans % mod;
            }
            printf("%d\n", tot);
        }
        return 0;
    }
    if(m <= 24) {
        int u[33];
        int v[33];
        for(int i = 0; i < m; i++) scanf("%d%d", &u[i], &v[i]);
        int ct = 0;
        int sav[53];
        for(int i = 1; i <= 2 * m; i++) sav[i] = 0;
        int tl = 0;
        int tp[53];
        for(int i = 0; i < m; i++) tp[++tl] = u[i], tp[++tl] = v[i];
        map<int, int> mp;
        mp.clear();
        for(int i = 1; i <= tl; i++) {
            mp[tp[i]] = i;
        }
        for(int i = 0; i < m; i++) u[i] = mp[u[i]], v[i] = mp[v[i]];
        if(m > 0) {
            for(int i = 0; i < (1 << m); i++) {
                if(i & 1) {
                    if(getfa(u[0]) != getfa(v[0])) ct--;
                } else {
                    for(int j = 1; j <= tl; j++) fa[j] = j;
                    ct = tl;
                    for(int j = 1; j < m; j++) {
                        if((1 << j) & i) {
                            int uu = getfa(u[j]);
                            int vv = getfa(v[j]);
                            if(uu != vv) ct--, fa[uu] = vv;
                        }
                    }
                }
                if((popc[i / 65536] + popc[i & 65535]) & 1) sav[ct]--;
                else sav[ct]++;
            }
        }
        int cl;
        for(int i = 1; i <= z; i++) {
            scanf("%d", &cl);
            int now = 1;
            int ans = 0;
            for(int j = 1; j <= tl; j++) {
                now = (long long)now * cl % mod;
                ans = (ans + (long long)now * sav[j] % mod) % mod;
                ans = (ans + mod) % mod;
            }
            if(m == 0) ans = 1;
            ans = (long long)ans * ksm(cl, n - tl) % mod;
            printf("%d\n", ans);
        }
        return 0;
    }
    for(int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i = 1; i <= n; i++) {
        if(!vs[i]) lp[++pl] = loop(i, 0);
    }
    int cl;
    for(int i = 1; i <= z; i++) {
        scanf("%d", &cl);
        long long kk = (long long)cl * (cl - 1) % mod;
        dp[1] = cl, dp[2] = kk;
        for(int j = 3; j <= n; j++) {
            kk = (long long)kk * (cl - 1) % mod;
            dp[j] = (kk - dp[j - 1] + mod) % mod;
        }
        int ans = 1;
        for(int j = 1; j <= pl; j++) {
            ans = (long long)ans * dp[lp[j]] % mod;
        }
        printf("%d\n", ans);
    }
    return 0;
}

```

## 总结与评价

以往 OI 赛事的题目均以现有的算法与复杂度为限制来选择，这在一定程度上限制了选手们的思维和创新性，束缚了他们探索未知世界的勇气和信心。

本题对于激发同学们的想象力和创新性，鼓励同学们用掌握的知识探索题目完成的边界是有积极意义的，打破了算法复杂度计算以往的墨守成规，固定数据规模套用固定的算法复杂度。这个题目是一道有创新性的好题目。

这算不算『挑战 NPC』类型题目的始祖呢？

---

