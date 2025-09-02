# [ARC089E] GraphXY

## 题目描述

给出一个$A \times B$的矩阵，其中第$i$行第$j$列元素为$d_{i,j}$。试构造一个有向图，满足：

1、有向图点数$\leq 300$；

2、图中没有自环和重边；

3、图中边有边权，边权为 $[0,100]$ 中的整数，或者是未知数`X`或`Y`；

4、对于所有$x \in [1,A] , y \in[1,B]$，满足当未知数$X = x$，$Y = y$时，图中$S$到$T$的最短路为$d_{x,y}$。

## 样例 #1

### 输入

```
2 3
1 2 2
1 2 3```

### 输出

```
Possible
3 4
1 2 X
2 3 1
3 2 Y
1 3 Y
1 3```

## 样例 #2

### 输入

```
1 3
100 50 1```

### 输出

```
Impossible```

# 题解

## 作者：Suiseiseki (赞：15)

无耻地安利一发自己的博客：[Atcoder Regular Contest 089E - GraphXY题解](https://www.cnblogs.com/withhope/p/11740792.html)

题解：令$f[i][j]$表示从S到T的路径上有i个x和j个y时其余边的最小可能长度，若我们已知$f[i][j]$，则可以推出$d[x][y]=min\{f[i][j]+i*x+j*y\}$，那么对该式进行移项，得出$f[i][j]=max\{d[x][y]-i*x-j*y\}$，但该$f[i][j]$不一定符合条件，重新判断，若不符合则该情况一定无解，否则一定可以构造出一解。
考虑如何构造：连两条长度为100的链（显然，长度更长毫无意义），一条链所有边权为X，另一条链所有边权为Y，那么对于每一个$f[i][j]$，可以在X链上的第$i$个节点和Y链上的倒数第$j$个节点间连一条长度为$f[i][j]$的边。即可构造方案。
code:
```cpp
#include <cstdio>
#include <cstring>
#define Maxn 300
#define Maxk 10
#define Inf 0x3f3f3f3f
int f[Maxn+5][Maxn+5];
int d[Maxk+5][Maxk+5];
//f[i][j]表示从S到T的路径上有i个x和j个y时其余边的最小可能长度 
//d[x][y]=min{f[i][j]+i*x+j*y}
//f[i][j]=max{d[x][y]-i*x-j*y}
int mx(int a,int b){
	return a>b?a:b;
}
int mn(int a,int b){
	return a<b?a:b;
}
struct Edge{
	int u,v,w;
}edge[Maxn*Maxn+5];
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&d[i][j]);
		}
	}
	for(int i=0;i<=100;i++){
		for(int j=0;j<=100;j++){
			for(int x=1;x<=n;x++){
				for(int y=1;y<=m;y++){
					f[i][j]=mx(f[i][j],d[x][y]-i*x-j*y);
				}
			}
		}
	}
	int now;
	for(int x=1;x<=n;x++){
		for(int y=1;y<=m;y++){
			now=Inf;
			for(int i=0;i<=100;i++){
				for(int j=0;j<=100;j++){
					now=mn(now,f[i][j]+i*x+j*y);
				}
			}
			if(now!=d[x][y]){
				puts("Impossible");
				return 0;
			}
		}
	}
	puts("Possible");
	puts("202 10401");
	for(int i=1;i<=100;i++){
		printf("%d %d X\n",i,i+1);
	}
	for(int i=102;i<202;i++){
		printf("%d %d Y\n",i,i+1);
	}
	for(int i=0;i<=100;i++){
		for(int j=0;j<=100;j++){
			printf("%d %d %d\n",i+1,202-j,f[i][j]);
		}
	}
	puts("1 202");
	return 0;
}
```

---

## 作者：zhylj (赞：10)

为了更好的阅读体验，你可以前往[我的博客](http://zhylj.cc/index.php/archives/13/)。

## 分析

首先，注意到我们可以从 $S$ 开始拉一条链，上面权值均为 ``X``，再拉一条链到 $T$，其上权值均为 ``Y``。然后我们如果连一条从前者距离 $S$ 第 $k_1$ 个 ``X`` 后到后者距离 $T$ 第 $k_2$ 个 ``Y`` 后，设其权值为 $c$，则这条路径对最短路的贡献为 $k_1x+k_2y+c$（显然，最短路是所有路径贡献的 $\min$）.

这时，聪明的选手可能会想到，设 $k_1,k_2$ 之间连了 $f_{k_1,k_2}$，则 $f_{k_1,k_2} + k_1x+k_2y \ge d_{x,y} \Rightarrow f_{k_1,k_2} \ge d_{x,y} - k_1x - k_2y$，于是我们只需要取 $f_{k_1,k_2} = \max \{d_{x,y} + k_1x + k_2y\}$ 然后再 Check 一下就好了。

但是，像我这样不聪明的选手要怎么办呢？我们考虑数据范围超小，于是对每个 $d_{x,y}$ 我们枚举可能让它取到最小值的路径的 $k_1,k_2$，然后暴力对其它 $A\times B$ 个点 Check 一下这个路径是否合法（也即上面的不等式是否成立）。

然后就做完了。

## 代码

```cpp
const int kN = 3e2 + 5;

struct Edge {
	int u, v, w;
} E[kN];
int A, B, D[kN][kN], cnt = 0;
std::set <pii> S;
void Add(int k1, int k2, int b) {
	if(S.count(mkp(k1, k2))) return;
	S.insert(mkp(k1, k2));
	E[++cnt] = (Edge) { k1 + 1, k2 + 102, b };
}
bool Check(int k1, int k2, int b, int x, int y) {
	return b + x * k1 + y * k2 >= D[x][y];
}
int main() { 
	int T = 1; //rd(T);
	while(T--) {
		bool flag = true;
		rd(A, B);
		for(int i = 1; i <= A; ++i)
			for(int j = 1; j <= B; ++j) {
				rd(D[i][j]);
				if(D[i][j] < D[i - 1][j]) flag = false;
				if(D[i][j] < D[i][j - 1]) flag = false;
			}
		for(int i = 1; i <= A; ++i) D[i][B + 1] = D[i][B];
		for(int i = 1; i <= B; ++i) D[A + 1][i] = D[A][i];
		D[A + 1][B + 1] = std::max(D[A + 1][B], D[A][B + 1]);
		for(int i = 1; i <= A; ++i)
			for(int j = 1; j <= B; ++j) {
				int d = D[i][j]; bool found = false;
				for(int k1 = 0; !found && k1 <= 100; ++k1)
					for(int k2 = 0; d - k1 * i - k2 * j >= 0; ++k2) {
						int b = d - k1 * i - k2 * j; bool able = true;
						for(int x = 1; able && x <= A; ++x)
							for(int y = 1; able && y <= B; ++y)
								if(!Check(k1, k2, b, x, y)) able = false;
						if(able) {
							Add(k1, k2, b);
							found = true;
							break;
						}
					}
				if(!found) flag = false;
			}
		if(!flag) {
			printf("Impossible\n");
		} else if(flag) {
			printf("Possible\n");
			printf("300 %d\n", cnt + 201);
			for(int i = 1; i <= cnt; ++i)
				printf("%d %d %d\n", E[i].u, E[i].v, E[i].w);
			for(int i = 1; i <= 100; ++i)
				printf("%d %d X\n", i, i + 1);
			for(int i = 103; i <= 203; ++i)
				printf("%d %d Y\n", i, i - 1);
			printf("1 102\n");
		}
	} return 0;
}
```

---

## 作者：Kubic (赞：3)

这是一个与其他题解不太一样的思路。

令 $X_{x,y}$ 为 $d_{x,y}$ 经过的 $X$ 边的数量，$Y_{x,y}$ 同理。

那么 $d_{x,y}=x\times X_{x,y}+y\times Y_{x,y}+w_{x,y}$。

$d_{x,y}$ 这条路径在 $(x',y')$ 时刻的长度为 $d_{x,y}+(x'-x)X_{x,y}+(y'-y)Y_{x,y}$。显然这个值必须 $\ge d_{x',y'}$。

同时还需要满足 $X_{x,y},Y_{x,y},w_{x,y}\ge 0$。

利用这些关系我们就得到了关于 $X_{x,y},Y_{x,y}$ 的一个不等式组。容易发现这个不等式组的任何一组解都是合法的。

枚举 $X_{x,y}$，再利用不等式组计算 $Y_{x,y}$ 可以取到的区间。因为 $X_{x,y}\le \dfrac{d_{x,y}}{x}$，所以可以暴力完成这个过程。这样我们一定能得到一组解或判定不等式组无解。

利用上面的方法解出所有的 $X_{x,y},Y_{x,y}$ 或判定无解，并计算出 $w_{x,y}$。此时再考虑如何连边。

用 $X$ 边连一条起点为 $S$，长度为 $100$ 的有向链 $L_1$。

用 $Y$ 边连一条终点为 $T$，长度为 $100$ 的有向链 $L_2$。

对于每一组 $(x,y)$，用一条权值为 $w_{x,y}$ 的边连接 $L_1$ 上从 $S$ 开始（包括 $S$）第 $X_{x,y}+1$ 个点以及 $L_2$ 上从 $T$ 开始（包括 $T$）第 $Y_{x,y}+1$ 个点。

注意如果出现重边取其中一条即可，这种构造方法保证了重边的边权全部相等。

综上，我们得到了一个满足要求的构造。代码难度不高，但有一些细节。

参考代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 105
#define M 1000005
int n,m,cntE,a[N][N];bool vs[N][N];struct Edge {int u,v,w;}e[M];
void f(int u,int v,int w)
{if(!vs[u][v]) vs[u][v]=1,e[++cntE]=(Edge) {u+1,202-v,w};} 
int main()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) scanf("%d",&a[i][j]);
	for(int i=1,L1,R1,L2,R2,t;i<=n;++i) for(int j=1;j<=m;++j)
	{
		bool fl=0;L1=0;R1=a[i][j]/i;
		for(int i1=1;i1<=n;++i1)
		{
			t=a[i][j]-a[i1][j];
			if(i<i1) L1=max(L1,t/(i-i1)+(t<0 && t%(i-i1)));
			else if(i>i1) R1=min(R1,t/(i-i1)-(t<0 && t%(i-i1)));
		}
		for(int k=L1;k<=R1;++k)
		{
			L2=0;R2=(a[i][j]-i*k)/j;
			for(int i1=1;i1<=n;++i1) for(int j1=1;j1<=m;++j1)
			{
				t=a[i][j]-a[i1][j1]+(i1-i)*k;
				if(j<j1) L2=max(L2,t/(j-j1)+(t<0 && t%(j-j1)));
				else if(j>j1) R2=min(R2,t/(j-j1)-(t<0 && t%(j-j1)));
			}if(L2<=R2) {fl=1;f(k,L2,a[i][j]-i*k-j*L2);break;}
		}if(!fl) {puts("Impossible");return 0;}
	}printf("Possible\n202 %d\n",cntE+200);
	for(int i=1;i<101;++i) printf("%d %d X\n",i,i+1);
	for(int i=102;i<202;++i) printf("%d %d Y\n",i,i+1);
	for(int i=1;i<=cntE;++i) printf("%d %d %d\n",e[i].u,e[i].v,e[i].w);
	puts("1 202");return 0;
}
```

---

## 作者：To_our_starry_sea (赞：1)

### Solution

~~发现自己的做法似乎有点劣，被爆踩了。~~

首先，我们注意到对于任意一条从 $S$ 到 $T$ 的一条路径，其的权值为 $w = aX + bY + c$，其中 $a$，$b$ 与 $c$ 均为常数。那么本质上，我们就是要构造若干个二元函数，使得对于 $1 \le i \le A$，$1 \le j \le B$，$d_{i, j} = a_{i, j}i + b_{i, j}j + c_{i, j}$，对于 $i' \ne i$ 或 $j' \ne j$，$d_{i', j'} \le a_{i, j}i' + b_{i, j}j' + c_{i, j}$。

考虑 $d_{i, j}$ 很小，所以我们可以直接暴力枚举 $a_{i,j}$，$b_{i, j}$，再进行暴力检查。如果 $A$ 与 $B$ 同阶，那么这么做的复杂度是 $O(A^4 \max(d_{i,j}) ^ 2)$ 的，但实际上我们可以很容易的进行剪枝。对于一组合法的 $a_{i, j}$，$b_{i, j}$ 与 $c_{i, j}$，我们判断有多少 $d_{i', j'} = a_{i, j}i' + b_{i, j}j' + c_{i, j}$ 然后直接更新 $d_{i', j'}$ 的答案，并予以标记。

接下来，我们考虑如何利用这一系列二元函数构造图。考虑以 $S$ 为端点构造一条边权全部为 $X$ 的链，长度为 $\max(a_{i, j})$，称之为主链，编号依次为 $1$ 到 $\max(a_{i, j}) + 1$。我们发现对于每一种情况，我们需要在主链上第 $a_{i, j} + 1$ 个点处连一条长度为 $b_{i, j}$，边权全部为 $Y$ 的链，称之为支链，并在支链的末端向 $T$ 连一条边权为 $c_{i, j}$ 的边。容易发现这样构造的图满足要求。

实现的时候我们应注意一些细节，如不要重复建链。同时对于以主链上点 $k + 1$，我们只需要建出长度为满足 $a_{i, j} = k$ 的最大 $b_{i, j} + 1$ 的支链即可，这样以来可以保证点数不超过限制。

![](https://cdn.luogu.com.cn/upload/image_hosting/gfxwmq4f.png?x-oss-process=image/resize,m_lfit,h_238,w_315)

如上图所示，我们可以借助这个理解构造方法。

实现有一些细节，可以参考代码。

### Code


```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 15;
const int MAXM = 105;
int n, m, cnt = 0, d[MAXN][MAXN];
int A[MAXN][MAXN], B[MAXN][MAXN], C[MAXN][MAXN], vis[MAXN][MAXN];
int way[MAXM][MAXM];
struct edge {
	int u, v, w;
} e[MAXN * MAXN * MAXN];
inline void add(int u, int v, int w) {
	cnt++;
	e[cnt].u = u;
	e[cnt].v = v;
	e[cnt].w = w;
}
inline bool check(int x, int y, int a, int b, int c) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			int now = d[x][y] + a * (i - x) + b * (j - y);
			if (now < d[i][j]) return false; 
		}
	}
	return true;
}
inline void solve(int x, int y) {
	for (int i = x; i <= x; i++) {
		for (int j = y + 1; j <= m; j++) {
			if (A[x][y] * i + B[x][y] * j + C[x][y] == d[i][j]) {
				vis[i][j] = (x - 1) * m + y;
				A[i][j] = A[x][y], B[i][j] = B[x][y], C[i][j] = C[x][y];
			}
		}
	}
	for (int i = x + 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (A[x][y] * i + B[x][y] * j + C[x][y] == d[i][j]) {
				vis[i][j] = (x - 1) * m + y;
				A[i][j] = A[x][y], B[i][j] = B[x][y], C[i][j] = C[x][y];
			}
		}
	}
}
inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
		   f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	return x * f;
}
int main() {
	n = read(), m = read();
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) d[i][j] = read();
	}
	int maxA = 0, maxB = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (vis[i][j]) continue;
			vis[i][j] = (i - 1) * m + j;
			bool pd = false;
			for (int sum = 0; sum <= 100; sum++) {
				if (max(d[i][j] - sum * i, d[i][j] - sum * j) < 0) break;
				for (int a = 0; a <= sum; a++) {
					int b = sum - a, c = d[i][j] - a * i - b * j;
					if (c < 0) continue;
					if (check(i, j, a, b, c)) {
						pd = true;
						A[i][j] = a, B[i][j] = b, C[i][j] = c;
						break;
					}
				}
				if (pd) break;
			}
			if (pd) solve(i, j);
			if (!pd) {
				puts("Impossible");
				return 0;
			}
			maxA = max(maxA, A[i][j]), maxB = max(maxB, B[i][j]);
		}
	}
	puts("Possible");
	int S = 1, now = 1, T = 0;
	way[0][0] = 1;
	for (int i = 1; i <= maxA; i++) now++, way[i][0] = now, add(now - 1, now, -1);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (vis[i][j] != (i - 1) * m + j) continue;
			if (!T) T = ++now;
			if (way[A[i][j]][B[i][j]]) add(way[A[i][j]][B[i][j]], T, C[i][j]);
			else {
				int nxt = 0;
				for (int k = 1; k <= B[i][j]; k++) {
					if (!way[A[i][j]][k]) {
						nxt = k;
						break;
					}
				}
				for (int k = nxt; k <= B[i][j]; k++) way[A[i][j]][k] = ++now, add(way[A[i][j]][k - 1], way[A[i][j]][k], -2);
				add(way[A[i][j]][B[i][j]], T, C[i][j]);
			}
		}
	}
	printf("%d %d\n", now, cnt);
	for (int i = 1; i <= cnt; i++) {
		if (e[i].w == -1) printf("%d %d X\n", e[i].u, e[i].v);
		else if (e[i].w == -2) printf("%d %d Y\n", e[i].u, e[i].v);
		else printf("%d %d %d\n", e[i].u, e[i].v, e[i].w);
	}
	printf("%d %d\n", S, T);
	return 0;
}
```

---

## 作者：Erica_N_Contina (赞：0)

因为写博客的平台会自动转换小于等于号，所以就直接用了求审核放过 qAq。

## 我的博客

更多相关（或者不相关）知识点快戳：[oi-beats 构造](https://ntsc-yrx.github.io/oi-beats/site/%E7%AE%97%E6%B3%95%E7%AD%96%E7%95%A5/%E6%9E%84%E9%80%A0/)，[个人博客](https://ntsc.flowus.cn/)。

## 做法

看到构造题，还要满足这么多条件，头要大了。

但是唯一一个比较好的性质就是我们只有两个变量。为了方便讨论，我们可以把边权为 $x$ 的都放在最短路的一段前缀上，将 $y$ 都放在一段后缀上。

那么接下来怎么样去思考呢？如果可以构造出一个方案，那么应该是一段 $x$，一段 $y$，加上一段常数。但是我们怎么样知道需要多少个 $x$ 和 $y$ 呢？

于是我们请出我们万能的数学（不等式），定义 $f_{i,j}$ 为从 $S$ 到 $T$ 的路径上有 $i$ 个 $x$ 和 $j$ 个 $y$ 时，最小的合法的常数是多少。

这里约定一条 $S$ 到 $T$ 路径的长度为 $ix+jy+c$，其中 $c$ 称为常数。合法指的是：当取这个合法值时，满足 $d$ 数组的约束（即不会出现实际取 $i$ 个 $x$ 和 $j$ 个 $y$ 时最短路长度 $<d_{x,y}$ 的情况）。

当然，当我们枚举了 $x,y$ 的个数 $i,j$ 后，我们可以得到 $f_{i,j}$ 应该满足的条件。

假设一个我们求出了一组合法的 $f$，那么应该对于每一对 $x,y$ 都满足 $d_{x,y}=\min(f_{i,j}+ix+jy)$。因此一个 $f_{i,j}$ 如果合法，那么它应该满足 $f_{i,j}=\max(d_{x,y}-ix-jy)$。

不过……为什么？

其实就是数学题。写成 $d_{x,y}≤f_{i,j}+ix+jy$ 就看得懂了。就是 $f_{i,j}≥d_{x,y}-ix-jy$，为了满足 $f$ 定义中的**最小**，我们要保证有一个 $x,y$ 使得上式取等号。

### 判非法

求出 $f$ 为什么还有可能不合法？

但是注意，这样求出来的 $f_{i,j}$ 不一定是可行的。

这里我们定义的**可行**是：对于我们求出的一组合法的 $f$，因为我们的 $f$ 和 $d$ 是相互约束的，所以正常情况下对于每一个 $d$（我们称为 $d_0$，即下文的 $d_{x_0,y_0}$），至少有一个 $f$ 约束它。但是有可能出现如下情况：所有的 $f$ 都被其他的 $d$（我们这里称为 $d'$）约束了（感性理解的话就是我们关注 $f_{i,j}≥d_{x,y}-ix-jy$ 不等式，至少有一个 $x,y$ 使得式子取等；如果没有任何一个 $i,j$ 是在 $x=x_0,y=y_0$ 时取等的，也就是说所有的 $f_{i,j}$ 都要大于 $d_{x_0,y_0}-ix_0-jy_0$，那么上面的式子 $d_{x,y}=\min(f_{i,j}+ix+jy)$ 就会偏大），因此 $f$ 对于 $d$ 来说就普遍偏大，$d$ 又是在一众 $f$ 中取 $\min$ 的，所以 $d$ 会偏大。

如果出现了 $d$ 偏大的情况，就说明**不可行**。此时一定无解。有一点像物理里“被短路”的概念，即输入数据中的一个 $d$ 值不可能存在。

我们重新用 $f$ 求出 $d$，和输入的 $d$ 比较一下就行了。



怎么样构造呢？我们先构造两条链。第一条链是 $S$ 与很多条边权为 $x$ 的边相连，第二条链是很多条边权为 $y$ 的边和一个 $T$ 相连。对于每一个 $f_{i,j}$，我们在第一条链上经过了 $i$ 条边的点向第二条链上跳过 $j$ 条边到终点的点相连即可。

这样链接保证不会出现更短的道路，因为我们上面已经检验过了，每个 $d_{x,y}$ 都是 $d_{x,y}≤(f_{i,j}+ix+jy)$，并且存在一个 $f_{i,j}$ 使得等号成立，并且不存在任何 $f_{i,j}$ 使得可以取 $>$。

如果存在不合法的 $f_{i,j}$，那么 $f_{i,j}≥d_{x,y}-ix-jy$ 不成立，与构造条件矛盾。

```C++
#include<bits/stdc++.h>
using namespace std;


#define rd read()
inline int read(){
	int x;
	cin>>x;
	return x;
}

const int N=3e2+5;
const int INF=1e9;
int d[N][N];
int f[N][N];
/*

策略
看上去是一个很困难的构造


*/


#define add(a,b,c) cout<<a<<' '<<b<<' '<<c<<endl;

void solve(){
	
	int a=rd,b=rd;
	for(int i=1;i<=a;i++){
		for(int j=1;j<=b;j++){
			d[i][j]=rd;
		}
	}


	for(int k=0;k<=100;k++){
		for(int l=0;l<=100;l++){
			for(int i=1;i<=a;i++){
				for(int j=1;j<=b;j++){
					f[k][l]=max(f[k][l],d[i][j]-i*k-l*j);
				}
			}
		}
	}

	for(int i=1;i<=a;i++){
		for(int j=1;j<=b;j++){
			int d2=INF;
			for(int k=0;k<=100;k++){
				for(int l=0;l<=100;l++){
					d2=min(d2,f[k][l]+i*k+j*l);
				}
			}

			if(d2!=d[i][j]){
				puts("Impossible");
				exit(0);
			}
		}
	}

	puts("Possible");

	int T=1,S=202;

	cout<<202<<' '<<10401<<endl;//100+100+101*101

	for(int i=1;i<=100;i++){
		add(i,i+1,'X');
	}
	for(int i=102;i<=201;i++){
		add(i,i+1,'Y');
	}

	for(int i=0;i<=100;i++){
		for(int j=0;j<=100;j++){
			add(1+i,202-j,f[i][j]);
		}
	}

	cout<<S<<' '<<T<<endl;


}

signed  main(){
	int T=1;
	while(T--){
		solve();
	}
	return 0;
}
```


写一道题是很简单的，难在如何说服自己真的会了这道题。



码字证明不易求赞。（断句？）

---

## 作者：ast123 (赞：0)

[atc题目链接](https://atcoder.jp/contests/arc089/tasks/arc089_c) 
注：本题解的小写 $x,y$ 代表变量 $X,Y$ 的值，大写 $X,Y$ 为边上的符号，代表变量的名称。  
如果不知道经过了多少个 $X$ 和 $Y$，就不能知道其他边的边权。不妨设 $d_{x,y} = ax+by+c$， $a,b$ 为经过 $X,Y$ 的数量，因为 $1 \le d_{x,y} \le 100$，给出的 $x \in [1,A]$，$y \in [1,B]$，所以最多一共经过 100 个 $X$ 和 $Y$，即 $a,b \in [0,100]$。上式中的 $c$ 可以设为 $f_{i,j}$，表示 $s$ 到 $t$ 经过 $i$ 个 $X$ 和 $j$ 个 $Y$ 时 $x=y=0$ 时的最短路。因为 $d_{x,y} = ax+by+c$，所以有 $d_{x,y} \le ix+jy+f_{i,j}$，所以 $f_{i,j} \ge d_{x,y}-ix-jy,i,j \in [0,100]$，于是 $f_{i,j} = \max(d_{x,y}-ix-jy)$。如果要判断无解，则将 $f_{i,j}$ 的值用来求 $d_{x,y}$，如果不能取等则无解。

接下来，考虑如何构造满足条件的图。
+ 前 100 个点 $i$ 向 $i+1$ 连一条边，边权为变量 $X$ 的值；
+ 同理，后 100 个点 $i$ 向 $i+1$ 连一条边，边权为变量 $Y$ 的值；
+ 接下来，正数第 $i+1$ 个点向倒数第 $j+1$ 个点连一条权值为 $f_{i,j}$ 的边。

[代码链接](https://atcoder.jp/contests/arc089/submissions/56475402)

---

