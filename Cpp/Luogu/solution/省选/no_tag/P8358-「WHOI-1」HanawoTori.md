# 「WHOI-1」HanawoTori

## 题目背景

春天到了，花园里的花竞相开放。樱花、梅花、梨花、桃花、牡丹都开放了。

你需要在花园里采花。

日文版题面：[JP 版リンク](https://www.luogu.com.cn/problem/T239022)。

如果你只会 `cout << 1` 这样骗分，建议不要浪费时间在这里。

## 题目描述

这个花园是由位于最左边的两个 $\texttt{start}$ 格子加上 $2 \times n$ 个方格组成的一个长列。如下图，$n=6$：


![](https://i.bmp.ovh/imgs/2022/04/07/405bb9192e6cf6d9.png)

注意 $n$ 并不包括最左边的两个 $\texttt{start}$ 格子。每个格子里面都有一棵花，花的美丽程度（下称“**美丽值**”）用一个整数表示，在上图中已经写在格子里了。


从**最左边任选**一个 $\texttt{start}$ 格子开始，每个时刻，你可以走到当前格子**右**、**右上**或**右下**的格子（只要不走出界），并采走里面的花。当走到花园**尽头**时结束。

然后你需要把采到的花按照美丽程度**升序排列**，组成一串花。记**排序过后的**花串中第 $i$ 朵花的美丽值为 $f_i$，那么这串花的“和谐度”$F$ 等于：

$$F = \min_{i=1}^{n-1} \begin{cases} k \times |f_i-f_{i+1}| && |f_i-f_{i+1}| \bmod  b = a \\ |f_i-f_{i+1}| && |f_i-f_{i+1}| \bmod  b  \not = a\\\end{cases}$$

现在知道了花园中每个格子内的花的美丽值，你需要计算出可能的**最大** $F$。即在所有可能的行走方案中，可能出现的最大的 $F$ 值。

## 说明/提示

**应要求，本题提供一个大样例，链接在下方。**

样例 #1 解释：

一条路径如下图：![](https://i.bmp.ovh/imgs/2022/04/07/84cfe7c13c0d33c1.png)

按时间顺序，得到的花的美丽值为 $\{1,2,4,6,5,10\}$；排序后为 $\{1,2,4,5,6,10\}$，可以计算出 $F=1$，这是能得到最大的 $F$ 了。

如果您无法写出能够得到满分的程序，可参考如下数据范围获取部分分值：

| 编号 | 特殊限制 | 分值 | 时限 | 
| :----------: | :----------: | :----------: | :----------: |
| 1 | $n \leq 30$ | 10 | 1s |
| 2 | $n\leq 100$ | 10 | 1s |
| 3 | $n \leq 2500$ | 40 | 1s |
| 4 | $n \leq 100000$ | 40 | 2s |

对于所有数据，$0 \leq f_i,k \leq 10^{8},1  \leq b < a \leq 10^8,n \ge 2$。

提示：

- 可能需要注意常数因子带来的效率差异。
- 本题存在 $O(n \log V)$ 的做法。


## 样例 #1

### 输入

```
6 5 4 3
1 3 4 6 10 10
1 2 7 8 5 9```

### 输出

```
1```

# 题解

## 作者：Prean (赞：6)

一个 $O(n\log V)$ 的做法。

首先这个走路径明显没用，实际上相当于每一列只能选一个元素。

考虑排序后的序列。我们先将 $2n$ 个元素排序去重，然后枚举点对检查是否可能为答案。

设 $g(i,j)$ 代表 $|f_i-f_j|$，那么我们只需要令所有 $g(x,y)<g(i,j)$ 的 $(x,y)$ 不能够同时选取即可。

可以大力枚举 $(x,y)$，然后建立 2-SAT 模型。正确性显然，复杂度 $O(n^4)$。

发现枚举 $(i,j)$ 没有什么意义，所以直接枚举 $g(i,j)$。

然后发现判定是有单调性什么的东西。。。于是直接二分就可以得到 $O(n^2\log V)$ 的做法了。

发现一件事情，在排序后的 $x$，对于 $y$ 来说 $x$ 一定是连续的一段。

也就是说在 2-sat 的加边中需要做一个区间加边。

这个线段树容易做到 $O(n\log n\log V)$，猫树容易做到 $O(n\log V)$，但是 $O(n\log n)$ 空间。

不过我们还有 $O(n)$ 空间的做法。

需要用到一个 trick（好像叫 baka's trick？）

大概就是说，对于 $y$ 递增，$x$ 一定也递增。所以是一个尺取的过程。

具体地，我们设有三个变量：$L,R,mid$，对于 $i\in[L,mid]$ 有 $S[i]=merge(S[i+1],F[i])$，对于 $i\in(mid,R]$ 有 $S[i]=merge(S[i-1],F[i])$。然后 $S[mid]=F[mid],S[mid-1]=F[mid-1]$。

然后在尺取的时候会出现 $L\geq mid$，这个时候令 $mid=R-1$，重构即可。

这个 $merge$ 在这里对应的就是连边什么的东西。

容易知道这个的空间和时间都是线性的，所以能够做到 $O(n\log V)$ 时间 $O(n)$ 空间。

~~但是因为各种常数导致空间和时间只比线段树略优~~
```cpp
#include<algorithm>
#include<cstdio>
#include<cctype>
#define For(o) for(int o=0;o^2;++o)
const int M=1e5+5,N=M*12;
int n,tot,id[2][M],val[2][M],f[M<<1][2],g[M<<1][2];int len,CB[M<<1],lsh[M<<1];
int tp,dfc,SCC,bl[N],stk[N],dfn[N],low[N];
bool itk[N];int cnt,h[N];
struct Edge{
	int v,nx;
}e[N*4];
inline void Add(const int&u,const int&v){
	e[++cnt]=(Edge){v,h[u]};h[u]=cnt;
}
inline int min(const int&a,const int&b){
	return a>b?b:a;
}
inline void Tarjan(const int&u){
	dfn[u]=low[u]=++dfc;itk[stk[++tp]=u]=true;
	for(int v,E=h[u];E;E=e[E].nx){
		!dfn[v=e[E].v]?Tarjan(v),low[u]=min(low[u],low[v]):itk[v]&&(low[u]=min(low[u],dfn[v]));
	}
	if(low[u]==dfn[u]){
		int v;++SCC;do itk[v=stk[tp--]]=false,bl[v]=SCC;while(u!=v);
	}
}
inline void Clear(){
	for(int i=1;i<=tot;++i)h[i]=bl[i]=dfn[i]=low[i]=0;tot=cnt=dfc=SCC=0;
}
inline int read(){
	int n(0);char s;while(!isdigit(s=getchar()));while(n=n*10+(s&15),isdigit(s=getchar()));return n;
}
inline bool check(const int&k){
	Clear();for(int i=1;i<=len;++i)For(x)f[i][x]=++tot;
	for(int i=1;i<=n;++i){
		Add(f[id[0][i]][1],f[id[1][i]][0]);Add(f[id[1][i]][1],f[id[0][i]][0]);
		Add(f[id[0][i]][0],f[id[1][i]][1]);Add(f[id[1][i]][0],f[id[0][i]][1]);
	}
	For(t)g[1][t]=++tot;
	Add(g[1][0],f[1][0]);Add(g[1][1],f[1][1]);
	Add(f[1][0],g[1][0]);Add(f[1][1],g[1][1]);
	for(int mid(0),L(1),i=2;i<=len;++i){
		while(L<i&&lsh[i]-lsh[L]>=k)++L;if(L==i)continue;
		if(L>mid){
			for(int k=L;k<=i;++k)For(t)g[k][t]=++tot;
			Add(g[i][0],f[i][0]);Add(g[i-1][0],f[i-1][0]);
			Add(f[i][1],g[i][1]);Add(f[i-1][1],g[i-1][1]);
			for(int k=i-2;k>=L;--k){
				Add(g[k][0],g[k+1][0]);Add(g[k][0],f[k][0]);
				Add(g[k+1][1],g[k][1]);Add(f[k][1],g[k][1]);
			}
			mid=i-1;
		}
		else{
			For(t)g[i][t]=++tot;
			Add(g[i][0],g[i-1][0]);Add(g[i][0],f[i][0]);
			Add(g[i-1][1],g[i][1]);Add(f[i][1],g[i][1]);
			Add(f[i][1],g[i-1][0]);Add(g[i-1][1],f[i][0]);
		}
		Add(f[i][1],g[L][0]);Add(g[L][1],f[i][0]);
	}
	For(o)for(int i=1;i<=len;++i)if(!dfn[f[i][o]])Tarjan(f[i][o]);
	for(int i=1;i<=len;++i)if(bl[f[i][0]]==bl[f[i][1]])return false;return true;
}
signed main(){
	n=read();read();read();read();
	For(o)for(int i=1;i<=n;++i)lsh[++len]=val[o][i]=read();std::sort(lsh+1,lsh+len+1);
	For(o)for(int i=1;i<=n;++i)id[o][i]=std::lower_bound(lsh+1,lsh+len+1,val[o][i])-lsh,id[o][i]+=CB[id[o][i]]++;
	int L(0),R(100000000/(n-1)+5),mid,ans(0);while(L<=R)check(mid=L+R>>1)?L=mid+1,ans=mid:R=mid-1;
	printf("%d",ans);
}
```

---

## 作者：FubukiShirakami (赞：1)


Update `2022/06/27`：修复 $\LaTeX$ 无法正常显示的问题。

***

WHOI 官方题解。

读题：

$$F = \min_{i=1}^{n-1}
\begin{cases}
k \times |f_i-f_{i+1}| && |f_i-f_{i+1}| \bmod  b= a \\
 |f_i-f_{i+1}| && |f_i-f_{i+1}| \bmod  b  \not = a\\
\end{cases}
$$

对于所有数据，均有 $0 \leq f_i,k \leq 10^{8}$、$1  \leq b < a \leq 10^8$。

由于 $b < a$，本题根本不会出现第一种 $|f_i-f_{i+1}| \bmod  b= a$ 的情况，所以其实只有第二种情况，也就是说，

$$F = \min_{i=1}^{n-1}|f_i-f_{i+1}|$$

题目中要求“最小值最大”，很明显需要二分最终答案 $p$。于是本题转化成：给定 $p$，判断是否存在一种行走方式，使得 $F \leq p$。

由于需要进行排序，动态规划比较难做，考虑其他的做法。不难发现，不论行走方式如何，一定会在每列里各取一个数，而每一列只有两个格子；设第一**行**的格子里的数为 $a_1,a_2,a_3,...,a_n$，第二行的格子里的数为 $b_1,b_2,b_3,...,b_n$，则取数的过程可以形式化描述为：对于 $i \in [1, n]$，令 $c_i=a_i$ 或 $b_i$，再将序列 $c$ 排序之后得到 $f$。

关键点来了：由于 $[1, n]$ 中每个 $i$ 都只有两种选择，就可以使用一个 $\texttt{bool}$ 变量 $x_i$ 来存储，为真表示选择 $a_i$，为假表示选择 $b_i$。那么本题转化为求出能够符合要求的一组 $x$ 的解，可以使用 $\texttt{2-SAT}$ 解决。

思考如何进行变量的约束。观察 $F$ 的表达式，发现它其实是在计算**相邻两个数的差值**的最小值。现在假定 $f$ 是已经升序排列好的。如果在 $f$ 中，相邻两个数的差大于 $p$，可推知**任意两个数的差也大于 $p$**。

利用这个性质就能推出变量约束方式。对于 $i,j \in [1, n]$：

- 如果 $|a_i-a_j|\leq p$，约束 $x_i=\texttt{false}$，$x_j=\texttt{false}$；
- 如果 $|a_i-b_j|\leq p$，约束 $x_i=\texttt{false}$，$x_j=\texttt{true}$；
- 如果 $|b_i-a_j|\leq p$，约束 $x_i=\texttt{true}$，$x_j=\texttt{false}$；
- 如果 $|b_i-b_j|\leq p$，约束 $x_i=\texttt{true}$，$x_j=\texttt{true}$；

约束数量在 $O(n^2)$ 级别。算上二分，总时间复杂度为 $O(n^2 \log R)$。其中 $R$ 是二分上界，这里取出现的最大的差值就可以了。只需要稍微注意一下常数。

```
#include <bits/stdc++.h>

using namespace std;

const int maxn = 2500 * 2 + 5;

int len[maxn];
int sons[maxn][maxn];
inline void add(int x, int y) {
	sons[x][len[x]++] = y;
}

int scc_cnt;
int dfn[maxn], low[maxn], vis[maxn], scc[maxn];
int clc;
stack<int> stk;

void tarjan(int x) {
	clc++, dfn[x] = low[x] = clc;
	vis[x] = true, stk.push(x);
	for (int i = 0; i < len[x]; i++) {
		int to = sons[x][i];
		if (!dfn[to]) {
			tarjan(to);
			low[x] = min(low[x], low[to]);
		}
		else if (vis[to]) {
			low[x] = min(low[x], dfn[to]);
		}
	}
	if (dfn[x] == low[x]) {
		scc_cnt++;
		int y;
		do {
			y = stk.top();
			vis[y] = false, scc[y] = scc_cnt;
			stk.pop();
		} while (y != x);
	}
}

int line1[maxn], line2[maxn];

int mid, a, b, k;
int n;

inline bool f(int x, int y) {
	return abs(x - y) < mid;
}

void addc(int x, int xval, int y, int yval) {
	if (xval == 0 && yval == 0) add(x + n, y), add(y + n, x);
	if (xval == 1 && yval == 0) add(x, y), add(y + n, x + n);
	if (xval == 0 && yval == 1) add(x + n, y + n), add(y, x);
	if (xval == 1 && yval == 1) add(x, y + n), add(y, x + n);
}

bool solve() {
	for (int i = 1; i <= 2 * n; i++) {
		if (!dfn[i]) tarjan(i);
	}
	for (int i = 1; i <= n; i++) {
		if (scc[i] == scc[i + n]) return false;
	}
	return true;
}

int siz;
void reset() {
	scc_cnt = clc = 0;
	memset(dfn, 0, sizeof(dfn));
	memset(low, 0, sizeof(low)), memset(vis, 0, sizeof(vis));
	memset(len, 0, sizeof(len));
}

bool check() {
	reset();
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (f(line1[i], line1[j])) {
				addc(i, 1, j, 1);
			}
			if (f(line2[i], line1[j])) {
				addc(i, 0, j, 1);
			}
			if (f(line1[i], line2[j])) {
				addc(i, 1, j, 0);
			}
			if (f(line2[i], line2[j])) {
				addc(i, 0, j, 0);
			}
		}
	}
	return solve();
}

int read() {
    int s = 0, f = 0;
    char ch = getchar();
    while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
    while (isdigit(ch)) s = (s << 1) + (s << 3) + (ch xor 48), ch = getchar();
    return f ? -s : s;
}

int main() {
	int L = 0, R = 0;
	n = read(), a = read(), b = read(), k = read();
	siz = n + n + 1;
	int minn = 0x3f3f3f3f, maxn = -0x3f3f3f3f;
	for (int i = 0; i < n; i++) line1[i] = read(), maxn = max(maxn, line1[i]), minn = min(minn, line1[i]);
	for (int i = 0; i < n; i++) line2[i] = read(), maxn = max(maxn, line2[i]), minn = min(minn, line2[i]);
	R = maxn - minn;
	while (L < R) {
		mid = (L + R + 1) / 2;
		if (check()) L = mid;
		else R = mid - 1;
	}
	printf("%d", L);
	return 0;
}
```

本题的暴力建边其实还可以用线段树优化，时间复杂度可以降到 $O(n\log n  \log R)$，实测能够比标准算法快大约 $10$ 倍。可看 @dottle 的[评测记录](https://www.luogu.com.cn/record/75817535)。

***

### 关于本题


![](https://i.bmp.ovh/imgs/2022/05/15/dfe6e0c8a369be7b.png)

---

