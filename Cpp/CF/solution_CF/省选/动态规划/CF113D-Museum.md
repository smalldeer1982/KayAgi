# Museum

## 题目描述

有一天，Petya 和他的朋友 Vasya 在一次旅行中，决定参观一座博物馆城堡。这个博物馆有一个特殊的结构：它由 $n$ 个房间和 $m$ 条走廊组成，任意两个房间之间都可以通过走廊互相到达。

两位朋友在博物馆里逛了一会儿后，决定分开各自欣赏感兴趣的艺术品。他们约定在下午六点在某个房间见面。然而，他们忘记了一个很重要的事情：没有指定具体的见面地点。等到时间到了，他们开始在博物馆里四处寻找对方（由于漫游费用太高，他们无法打电话联系）。

即便如此，他们依然沉迷于艺术品，因此每个人都有如下的行动策略：每分钟，他会做出决定——以概率 $p_i$，他会留在当前房间不动；以概率 $1-p_i$，他会等概率地选择一个相邻的房间，并通过走廊前往那里。这里 $i$ 表示当前所在房间的编号。由于古代建筑成本高昂，每条走廊只连接两个不同的房间，且任意两房间之间最多只有一条走廊。

两个人是同时行动的。由于走廊很黑，他们无法在走廊里相遇；不过，走廊是双向通行的，并且两个人可以同时走在同一条走廊上而不会遇见。两人会一直这样行动，直到他们在同一个房间相遇。更正式地说，当某一时刻两人都出现在同一个房间时，他们就算相遇了。

对于每个房间，求出两人最终在该房间相遇的概率。已知六点时，Petya 和 Vasya 分别在房间 $a$ 和 $b$。

## 说明/提示

在第一个样例中，博物馆是对称的，因此在房间 1 和房间 2 相遇的概率相等，并且它们的和为 1。所以每个概率都是 $0.5$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 1 1 2
1 2
0.5
0.5
```

### 输出

```
0.5000000000 0.5000000000 ```

## 样例 #2

### 输入

```
4 4 1 2
1 2
2 3
3 4
4 1
0.5
0.5
0.5
0.5
```

### 输出

```
0.3333333333 0.3333333333 0.1666666667 0.1666666667 ```

# 题解

## 作者：dsidsi (赞：11)

# [「Codeforces113D」Museum-高斯消元](http://codeforces.com/contest/113/problem/D)

## Description

有一个$n$个点$m$条边的无向图，两个人分别从$x,y$出发，每个人每分钟有$p_i$的概率不动, 有$1−p_i$的概率走到随机一个相邻的点。

当他们在同一时刻选择前往同一个房间, 他们就会在那个房间相遇并停止。

求在每个点相遇的概率。

$n \leq 22$

## Solution

这道题有两种做法。

第一种做法，枚举终点，然后高斯消元即可。直接这样做是$O(n^7)$的，显然无法通过。考虑每次修改终点只会修改$f(i,i)$的值，所以可以把$f(i,i)$视为常数，那么列出方程组后高斯消元可以得出$f(i,j)=\sum_{k=1}^n A_{i,j,k} f(k,k)$。每次枚举终点暴力计算即可。

第二种做法，设$f(i,j)$表示第一个人在$i$第二个人在$j$的期望出现次数，由于终止状态$(i,i)$的出现次数只可能为$0/1$，所以概率即期望。直接解方程即可。

注意初始点的方程为

$$f(a,b)-1=\sum_{i=1}^n\sum_{j=1}^n A(i,j)f(i,j)$$

其余点的方程为

$$f(a,b)=\sum_{i=1}^n\sum_{j=1}^n A(i,j)f(i,j)$$

其中$A(i,j)$表示从$(a,b)$转移到$(i,j)$的概率。

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int gi()
{
    char c = getchar();
    while(c < '0' || c > '9') c = getchar();
    int sum = 0;
    while('0' <= c && c <= '9') sum = sum * 10 + c - 48, c = getchar();
    return sum;
}

const double eps = 1e-7;
const int maxn = 25, maxm = maxn * maxn;

int n, m, a, b, deg[maxn], Id[maxn][maxn];
vector<int> to[maxn];
double p[maxn], mat[maxm][maxm], ans[maxm], f[maxn][maxn];

void pre()
{
    m = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            Id[i][j] = ++m;
    mat[Id[a][b]][m + 1] = -1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            int x = Id[i][j];
            --mat[x][x];
            if (i != j) mat[x][x] += p[i] * p[j];
            for (int u : to[i])
                for (int v : to[j]) {
                    if (u == v) continue;
                    mat[x][Id[u][v]] = (1 - p[u]) * (1 - p[v]) / deg[u]  / deg[v];
                }
            for (int u : to[i]) {
                if (u == j) continue;
                mat[x][Id[u][j]] = (1 - p[u]) * p[j]/ deg[u];
            }
            for (int v : to[j]) {
                if (v == i) continue;
                mat[x][Id[i][v]] = p[i] * (1 - p[v]) / deg[v];
            }
        }
}

int dcmp(double a)
{
    if (-eps < a && a < eps) return 0;
    else if (a > 0) return 1;
    else return -1;
}

/*int gauss()
{
    for (int i = 1; i < m; ++i) {
        int p = i;
        for (int j = i + 1; j <= m; ++j)
            if (abs(mat[j][i]) > abs(mat[p][i])) p = j;
        if (p != i)
            for (int j = i; j <= m + 1; ++j) swap(mat[i][j], mat[p][j]);
        for (int j = i + 1; j <= m; ++j) {
            if (!dcmp(mat[j][i])) continue;
            double t1 = mat[j][i], t2 = mat[i][i];
            for (int k = i; k <= m + 1; ++k) mat[j][k] -= mat[i][k] * t1 / t2;
        }
    }
    for (int i = m; i >= 1; --i) {
        if (!dcmp(mat[i][i])) return 0;
        for (int j = i + 1; j <= m; ++j)
            mat[i][m + 1] -= ans[j] * mat[i][j];
        ans[i] = mat[i][m + 1] / mat[i][i];
    }
    return 1;
}*/

void gauss()
{
    for (int i = 1; i <= m; ++i) {
        int p = i;
        for (int j = i; j <= m; ++j)
            if (abs(mat[j][i]) > abs(mat[p][i])) p = j;
        if (p != i) 
            for (int j = i; j <= m; ++j) swap(mat[p][j], mat[i][j]);
        for (int j = 1; j <= m; ++j) {
            if (p == j) continue;
            double t = mat[j][i] / mat[i][i];
            for (int k = i; k <= m + 1; ++k) mat[j][k] -= mat[i][k] * t;
        }
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            f[i][j] = mat[Id[i][j]][m + 1] / mat[Id[i][j]][Id[i][j]];
}

int main()
{
    n = gi(); m = gi(); a = gi(); b = gi();
    for (int u, v, i = 1; i <= m; ++i) {
        u = gi(); v = gi();
        to[u].push_back(v); ++deg[u];
        to[v].push_back(u); ++deg[v];
    }
    for (int i = 1; i <= n; ++i) scanf("%lf", &p[i]);

    pre();
    gauss();

    for (int i = 1; i <= n; ++i) printf("%.10lf ", f[i][i]);
    
    return 0;
}
```

---

## 作者：Lonely_NewYear (赞：8)

# CF113D 题解

## 题目大意

有一个无向图，有两个人在图上互相寻找，如果有一个人在第 $i$ 个点，那么他有 $p_i$ 的概率这一分钟停留在这个点，有 $1-p_i$ 的概率随机选择一条边花费一分钟走到另一个点。如果两个人**同时位于同一个点**，那么寻找结束，求在每个点结束的概率。

## 题目分析

设 $f_{i,j}$ 表示两个人分别在点 $i$ 和点 $j$ 这种情况的期望出现次数，那么易得：

$$\begin{cases}
{f_{i,j}=
\sum\limits_{(i,u)\in G}\!
\sum\limits_{(j,v)\in G}\!
\frac{1-p_u}{deg_u}\!\frac{1-p_v}{deg_v}\!f_{u,v}+
\sum\limits_{(i,u)\in G}\!
\frac{1-p_u}{deg_u}\!p_j\!f_{u,j}+
\sum\limits_{(j,v)\in G}\!
\frac{1-p_v}{deg_v}\!p_i\!f_{i,v}+
p_ip_jf_{i,j}+1}
&i=a,j=b\\
{f_{i,j}=
\sum\limits_{(i,u)\in G}\!
\sum\limits_{(j,v)\in G}\!
\frac{1-p_u}{deg_u}\!\frac{1-p_v}{deg_v}\!f_{u,v}+
\sum\limits_{(i,u)\in G}\!
\frac{1-p_u}{deg_u}\!p_j\!f_{u,j}+
\sum\limits_{(j,v)\in G}\!
\frac{1-p_v}{deg_v}\!p_i\!f_{i,v}+
p_ip_jf_{i,j}}
&otherwise
\end{cases}$$

（注意任何一个 $f_{i,i}$ 都不会产生贡献，因为到了 $f_{i,i}$ 寻找就截止了。）

每次都是对一组点对进行处理会不太方便，所以可以把 $(i,j)$ 换成 $(i-1)\times n+j$。

这样就列出了 $n\times n$ 个方程，直接高斯消元即可。

时间复杂度 $O(n^6)$。

# 代码

```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
struct edge
{
	int to,next;
}g[500];
int n,m,x,y,num;
int cnt,head[30],deg[30];
double p[30],f[500][500];
void add(int u,int v)
{
	g[++cnt]=(edge){v,head[u]};
	head[u]=cnt;
}
int fun(int a,int b)
{
	return (a-1)*n+b;
}
void build()
{
	for(int a=1;a<=n;a++)
	for(int b=1;b<=n;b++)
	{
		int u=fun(a,b);
		f[u][u]=-1;
		if(a!=b)f[u][u]+=p[a]*p[b];
		for(int i=head[a];i;i=g[i].next)
		for(int j=head[b];j;j=g[j].next)
		{
			int c=g[i].to,d=g[j].to;
			if(c==d)continue;
			int v=fun(c,d);
			f[u][v]=(1-p[c])/deg[c]*(1-p[d])/deg[d];
		}
		for(int i=head[a];i;i=g[i].next)
		{
			int c=g[i].to;
			if(c==b)continue;
			int v=fun(c,b);
			f[u][v]=(1-p[c])/deg[c]*p[b];
		}
		for(int j=head[b];j;j=g[j].next)
		{
			int d=g[j].to;
			if(a==d)continue;
			int v=fun(a,d);
			f[u][v]=p[a]*(1-p[d])/deg[d];
		}
	}
	f[fun(x,y)][num+1]=-1;
}
void gauss()
{
	for(int i=1;i<=num;i++)
	{
		int pos=i;
		for(int j=i+1;j<=num;j++)
			if(fabs(f[j][i])>fabs(f[pos][i]))
				pos=j;
		swap(f[i],f[pos]);
		for(int j=1;j<=num;j++)
		{
			if(i==j)continue;
			double div=f[j][i]/f[i][i];
			for(int k=i;k<=num+1;k++)
				f[j][k]-=f[i][k]*div;
		}
	}
	for(int i=1;i<=num;i++)
		f[i][num+1]/=f[i][i];
}
int main()
{
	scanf("%d%d%d%d",&n,&m,&x,&y);
	num=n*n;
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
		deg[u]++,deg[v]++;
	}
	for(int i=1;i<=n;i++)
		scanf("%lf",&p[i]);
	build();
	gauss();
	for(int i=1;i<=n;i++)
		printf("%.10lf ",f[fun(i,i)][num+1]);
	return 0;
}
```

谢谢观看！

---

## 作者：AuCloud (赞：6)

N <= 22就意味着我们可以搞一些复杂度惊人的算法

设$f_{i,j}$表示整个过程中，A在i，B在j的期望次数

于是转移方程是十分好列的：

设$p_{a,b}$表示从a走到b的概率

则有：

$$
f_{i,j}=\sum_{a=1}^{N}\sum_{b=1}^{N}p_{a,i}\times p_{b,j}\times f_{i,j}
$$

当然最初状态也要算上，所以初始位置期望次数要+1

然后您收获了一个无限递归的方程，~~大概~~解不出来

于是就不去解，考虑高斯消元，一共$N^2$项，总复杂度$N^6$

**然而能过……**

--------

## 但是！

> 高斯消元太难了，不会！

怎么办

可以用直觉看出来，这个无限迭代的式子会一点一点收敛，而我们要做的就是让这个收敛到误差接近于0

先考虑把状态都存起来：$N^2$枚举两人的编号并进行标号，设状态总数为$M$。

考虑设$p_{i,a,b}$表示在第$i$步由状态$a$转移至状态$b$的概率

转移方程很显然：

$$
p_{i,a,b}=\sum_{k=1}^{M}p_{i-1,a,k}\times p_{i-1,k,b}
$$

然后发现这就是个矩阵自己乘以自己

考虑让它自己乘个$2^{30}$遍，误差就会很小很小，把最终答案输出就行（

复杂度$N^6\times30$，算了一下有些悬

但是CF评测机十分强大，拿C++17(64位)居然过了……

~~但是RemoteJudge并不支持C++17(64位)~~

```cpp
#include <bits/stdc++.h>
using namespace std;
double ls[700][700];
int head[50], nxt[700], to[700], tot;
int qwq;
int du[1000];
int id[1000][1000];
struct hehe{
    double p[700][700];
}a[51];
double p[50];
void jc(int x, int y)
{
    for(int i = 1; i <= qwq; i++)
    {
        for(int j = 1; j <= qwq; j++)
        {
            for(int k = 1; k <= qwq; k++)
            {
                ls[i][k] += a[y].p[i][j] * a[y].p[j][k];
            }
        }
    }
    for(int i = 1; i <= qwq; i++)for(int j = 1; j <= qwq; j++) a[x].p[i][j] = ls[i][j], ls[i][j] = 0;
}
void add(int x, int y)
{
    nxt[++tot] = head[x];
    head[x] = tot;
    to[tot] = y;
}
int main()
{
    int n, m;
    cin >> n >> m;
    int fr, frr;
    cin >> fr >> frr;
    for(int i = 1; i <= m; i++)
    {
        int x, y;
        cin >> x >> y;
        add(x, y);
        add(y, x);
        du[x]++;
        du[y]++;
    }
    for(int i = 1; i <= n; i++)
    {
        for(int j = i; j <= n; j++)
        {
            id[j][i] = id[i][j] = ++qwq;//因为两个人是相同的所以顺序无所谓
        }
    }
    for(int i = 1; i <= n; i++) cin >> p[i], a[0].p[id[i][i]][id[i][i]] = 1;
    for(int i = 1; i <= n; i++)
    {
        for(int j = i + 1; j <= n; j++)
        {
            double p1 = p[i], p2 = p[i] * p[j];
            a[0].p[id[i][j]][id[i][j]] += p2;
            for(int k = head[i]; k; k = nxt[k])
            {
                int y = to[k];
                a[0].p[id[i][j]][id[y][j]] += (1 - p[i]) / du[i] * p[j];
                for(int l = head[j]; l; l = nxt[l])
                {
                    int yy = to[l];
                    a[0].p[id[i][j]][id[y][yy]] += (1 - p[i]) / du[i] * (1 - p[j]) / du[j];
                }
            }
            for(int k = head[j]; k; k = nxt[k])
            {
                int y = to[k];
                a[0].p[id[i][j]][id[i][y]] += p[i] * (1 - p[j]) / du[j];
            }
        }
    }
    for(int i = 1; i <= 30; i++) jc(i, i - 1);
    // for(int c = 1; c <= 50; c++)for(int i = 1; i <= n; i++) for(int ii = 1; ii <= n; ii++) for(int iii = 1; iii <= n; iii++) for(int iiii = 1;  iiii <= n; iiii++) cout << i << ' ' << ii << ' ' << iii << ' ' << iiii << ' ' << a[c].p[id[i][ii]][id[iii][iiii]] << endl;
    for(int i = 1; i <= n; i++) printf("%.10f ", a[30].p[id[fr][frr]][id[i][i]]);
}

```

---

## 作者：shao0320 (赞：5)

#### 题意简述：

给定一个无向图，从$a$节点和$b$节点开始随机游走，走到每个点时有两种可能，在第$i$个点有$p_i$的可能停下，或者随机找一条出边出去，两个点走到同一个点时停止。

分析：

听说正解是高斯消元，这里给出一种玄学做法。

由于时间满足单调性，因此容易想到一种$dp$。

设$f(i,x,y)$表示，第$i$轮游走，第$1$个人停在了$x$号节点，第$2$个人停在了$y$号节点的概率。

转移很简单，有四种情况，第一个人走/不走、第二个人走/不走。

时间复杂度为$O(TN^4)$，其中$T$表示游走次数。

问题就是这个$T$该取多少。

首先，肯定是$T$取的越大，结果越精确，注意到有$10^{-6}$的可接受误差，因此可以考虑取一个常数。

但常数过大这样会$TLE$，注意到如果当前状态的概率过小，也就不会对后续状态产生非常大的影响了，因此可以设一个$eps$值，当当前状态概率$\leq eps$时就不计算这个状态的贡献了。

经过作者多次调参，发现$T=150000,eps=1e^{-30}$时可以通过。


---

## 作者：封禁用户 (赞：4)

![](https://cdn.luogu.com.cn/upload/pic/40872.png)
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <inttypes.h>
#include <iomanip>
#define debug(x) std::cout << #x << " = " << x << std::endl;

typedef int int_t;
typedef long double real_t;
const int_t LARGE = 22;

const real_t EPS = 1e-6;

using std::cin;
using std::endl;
using std::cout;

real_t mat[501][501];

bool graph[23][23];
int_t degree[LARGE + 1];
real_t prob[LARGE + 1];
int_t n,m,a,b;
template<class T>
T xabs(T x) {
	if(x<0) return -x;
	return x;
}
int_t encode(int_t a,int_t b) {
//	cout<<"encode "<<a<<" "<<b<<" to "<< n * (a - 1) + b - ((a>b)?(a-1):a)<<endl;
	return n * (a - 1) + b - ((a>b)?(a-1):a);
}
real_t cost(int_t i,int_t j ,int_t x,int_t y) {
	real_t result = 0;
	if(i == x && j == y) result = prob[i] * prob[j];
	if(i == x && j != y) {
		result = prob[i] * (1 - prob[j]) * (1.0 / degree[j]) * graph[j][y];
	}
	if(i != x && j == y) result = (1 - prob[i]) * (1.0 / degree[i]) * graph[i][x] * prob[j];
	if(i != x && j != y) result = (1 - prob[i]) * (1.0 / degree[i]) * graph[i][x] * (1 - prob[j]) * (1.0 / degree[j]) * graph[j][y];
	return result;
}
int main() {
	cin >> n >> m >> a >> b;
	if(a == b) {
		for(int_t i=1; i<=n; i++) {
			if(i==a) cout<<1<<" ";
			else cout<<0<<" ";
		}
		return 0;
	}
	for(int_t i = 1; i <= m; i++) {
		int_t from,to;
		cin >> from >> to;
		graph[from][to] = graph[to][from] = 1;
		degree[from] += 1;
		degree[to] += 1;
	}
	for(int_t i = 1 ; i <= n; i++) {
		cin >> prob[i];
	}
	int_t len = n * n - n;
	for(int_t i = 1 ; i <= n; i++) {
		for(int_t j = 1; j<= n ; j++) {
			if(i == j) continue;
			int_t curr = encode(i,j);
			mat[curr][curr] = -1;
			for(int_t x = 1 ; x <= n; x++) {
				for(int_t y = 1; y <= n ; y++) {
					if(x == y) {
						mat[curr][len + x] -= cost(i,j,x,y);
					} else {
						mat[curr][encode(x,y)] += cost(i,j,x,y);
					}
				}
			}
		}
	}
	for(int_t i = 1; i <= len; i++) {
		if(xabs(mat[i][i]) < EPS) {
			int_t pos = -1;
			for(int_t j = i + 1; j <= len ; j++) {
				if(xabs(mat[j][i]) >= EPS) {
					pos = j;
					break;
				}
			}
			if(pos != -1) {
				std::swap(mat[i],mat[pos]);
			} else {
				cout <<" exm ?? "<< endl;
				return 0;
			}
		}
		for(int_t j = i + 1; j <= len ; j++) {
			real_t f = mat[j][i] / mat[i][i];
			for(int_t k = i ; k <= n * n; k++) {
				mat[j][k] -= f* mat[i][k];
			}
		}
	}
	for(int_t i = len ; i >=1 ; i--) {
		real_t f = mat[i][i];
		for(int_t j = len + 1; j <= n * n ; j++) {
			mat[i][j] /= f;
		}
		mat[i][i] /= f;
		for(int_t j = i - 1; j >= 1; j--) {
			real_t f2 =  mat[j][i];
			mat[j][i] = 0;
			for(int_t k = len + 1; k<= n * n; k++) {
				mat[j][k] -= f2 * mat[i][k];
			}
		}
	}
//	print();
	for(int_t i = 1; i <= n; i++) {
		cout.setf(std::ios::fixed);
		cout << std::setprecision(10) << mat[encode(a,b)][len + i] << " ";
	}
	return 0;
}

```

---

## 作者：STrAduts (赞：3)

记 $S(u)$ 表示 $u$ 结点的相邻结点的集合。

又记 $p(u)$ 表示走到了 $u$ 且下一步继续留在 $u$ 结点的概率，那么下一步离开 $u$ 结点的概率即为 $1 - p(u)$。

设 $f(i, j)$ 表示 Petya 在 $i$ 且 Vasya 在 $j$ 的概率。

可知所有的形如 $f(i, i)$ 的状态都是不能用于转移的，因为它们已经是末状态了。

故有

$$f(i, j) = \sum_{k \in S(i), k \neq j} f(k, j) \times \frac{1 - p(k)} {|S(k)|} \times p(j) + \sum_{k \in S(j), k \neq i} f(i, k) \times \frac{1 - p(k)} {|S(k)|} \times p(i) + \sum_{u \in S(i), v \in S(j), u \neq v} f(u, v) \times \frac{1 - p(u)} {|S(u)|} \times \frac{1 - p(v)} {|S(v)|}$$

显然这个转移是有后效性的，无法用简单的递推做。

故考虑高斯消元，将该式转换为我们熟悉的方程形式进行求解即可。

共有 $n ^ 2$ 只方程，时间复杂度 $O(n ^ 6)$。

注意边界条件，即初始状态时，转移式需要加 $1$，感性理解一下。

```cpp
#include <cstdio>
#include <vector>
using namespace std;

int Abs(int x) { return x < 0 ? -x : x; }
int Max(int x, int y) { return x > y ? x : y; }
int Min(int x, int y) { return x < y ? x : y; }

int read() {
    int x = 0, k = 1;
    char s = getchar();
    while (s < '0' || s > '9') {
        if (s == '-')
            k = -1;
        s = getchar();
    }
    while ('0' <= s && s <= '9') {
        x = (x << 3) + (x << 1) + (s ^ 48);
        s = getchar();
    }
    return x * k;
}

void write(int x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}

void print(int x, char c) {
    write(x);
    putchar(c);
}

const int MAXN = 23 * 23 + 5;

struct Elimination {
    bool free[MAXN];
    int n, m, rk, opt;
    double a[MAXN][MAXN], eps;
    Elimination() { eps = 1e-15; }
    Elimination(int N, int M) {
        n = N;
        m = M;
    }
    double Abs(double x) { return x < eps ? -x : x; }
    void Swap(double &x, double &y) {
        double t = x;
        x = y;
        y = t;
    }

    void clear() {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) a[i][j] = 0;
    }

    void calc() {
        int r = 1, c = 1;
        for (; r <= n && c <= m; r++, c++) {
            int pos = r;
            for (int i = r + 1; i <= n; i++)
                if (Abs(a[i][c]) > Abs(a[pos][c]))
                    pos = i;
            if (Abs(a[pos][c]) < eps) {
                r--;
                continue;
            }
            if (pos != r)
                for (int i = c; i <= m; i++) Swap(a[r][i], a[pos][i]);
            double t;
            for (int i = 1; i <= n; i++)
                if (i != r && Abs(a[i][c]) > eps) {
                    t = a[i][c] / a[r][c];
                    for (int j = m; j >= c; j--) a[i][j] -= t * a[r][j];
                }
        }
        rk = r;
    }
};

int deg[MAXN];
double p[MAXN];
vector<int> mp[MAXN];

void Add_Edge(int u, int v) {
    mp[u].push_back(v);
    mp[v].push_back(u);
}

struct node {
    int x, y;
    node() {}
    node(int X, int Y) {
        x = X;
        y = Y;
    }
    int Get(int n) { return (x - 1) * n + y; }
};

int main() {
    int n = read(), m = read(), x = read(), y = read();
    for (int i = 1, u, v; i <= m; i++) {
        u = read(), v = read();
        Add_Edge(u, v);
        deg[u]++, deg[v]++;
    }
    for (int i = 1; i <= n; i++) scanf("%lf", &p[i]);
    Elimination q;
    q.n = n * n;
    q.m = q.n + 1;
    q.clear();
    q.a[node(x, y).Get(n)][q.m] = -1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            int pos = node(i, j).Get(n);
            q.a[pos][pos]--;
            if (i != j)
                q.a[pos][pos] += p[i] * p[j];
            for (size_t k1 = 0; k1 < mp[i].size(); k1++)
                for (size_t k2 = 0; k2 < mp[j].size(); k2++) {
                    int u = mp[i][k1], v = mp[j][k2];
                    if (u == v)
                        continue;
                    q.a[pos][node(u, v).Get(n)] += (1 - p[u]) * (1 - p[v]) / deg[u] / deg[v];
                }
            for (size_t k = 0; k < mp[i].size(); k++)
                if (mp[i][k] != j)
                    q.a[pos][node(mp[i][k], j).Get(n)] += (1 - p[mp[i][k]]) / deg[mp[i][k]] * p[j];
            for (size_t k = 0; k < mp[j].size(); k++)
                if (mp[j][k] != i)
                    q.a[pos][node(i, mp[j][k]).Get(n)] += (1 - p[mp[j][k]]) / deg[mp[j][k]] * p[i];
        }
    q.calc();
    for (int i = 1; i <= n; i++)
        printf("%.9f\n", q.a[node(i, i).Get(n)][q.m] / q.a[node(i, i).Get(n)][node(i, i).Get(n)]);
    return 0;
}
```

---

## 作者：Ace_FutureDream (赞：2)

## 题目大意

有 $n$ 个点 $m$ 条无向边的无重边连通图，初始两个人在点 $x$ 和 $y$。每一单位时间，假设两个人在点 $i$ 和 $j$，那么分别有 $p_i$ 和 $p_j$ 的概率原地不动，$1−p_i$ 和 $1-p_j$ 的概率等概率移动到相邻的点。求两个人在每个点相遇的概率，一旦相遇两人立刻停止移动。

## 题解：
首先不难想到设 $f_{i,x,y}$ 表示目前已经到了第 $i$ 轮，两人分别来到了 $x$ 和 $y$ 的期望是多少，转移十分显然。但是复杂度不对，因为两个人可以一直在某个地方转圈，过了 $114514$ 轮之后再在某个点相遇，又因为要精确到 $10^{-6}$，所以这部分不可忽视。

考虑把 $i$ 的限制去掉，那么显然 $f_{i,j}$ 的贡献由 $4$ 部分组成：

$$
val_1=p_i\times p_j\times f_{i,j}\\

{}\\

val_2=\sum \limits _{k_1\to i,k_1\ne j}\dfrac{(1-p_{k_1})\times p_j}{ d_{k_1}}\times f_{k_1,j}\\

{}\\

val_3=\sum \limits _{k_2\to j,i\ne k2}\dfrac{p_i\times (1-p_{k_2})}{ d_{k_2}}\times f_{i,k_2}\\

{}\\

val_4=\sum \limits _{k_1\to i,k_2\to j,k_1\ne k_2}\dfrac{(1-p_{k_1})\times (1-p_{k_2})}{d_{k_1}\times d_{k_2}}\times f_{k_1,k_2}\\
$$

看起来比较难转移，但你发现 $n\le 22$，所以可以直接列方程跑高斯消元求解，复杂度为 $O(n^6)$。

实现时可以先搜出来所有的合法状态然后再列方程，并且要注意以下细节；

- 因为一开始一定在 $(x,y)$，所以关于 $f_{x,y}$ 的方程常数项为 $1$.

- 列方程时若 $i=j$ 那么 $val_1$ 的系数应该设为 $0$ 之后再进行移项，因为两个人相遇之后会立即停止，所以无法转移。

- 在转移 $val_2,val_3,val_4$ 的时候不能从 $i=j$ 的 $f_{i,j}$ 转移过来，因为两个人相遇之后会立即停止。

## code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

double d[25],p[25];
int id[25][25];
int cnt,n;
int vis[50][50];
double a[1010][1010];
double ans[50];
pair<int,int>v[1000];
vector<int>g[25];
const double eps=1e-12;
void dfs(int a,int b){
	if(vis[a][b])return;
	vis[a][b]=1;
	//记录合法状态 
	v[++cnt]={a,b};
	id[a][b]=cnt;
	if(a==b)return;
	for(auto v1:g[a])
		dfs(v1,b);
	//只有a走了 
	for(auto v2:g[b])
		dfs(a,v2);
	//只有b走了 
	for(auto v1:g[a])
		for(auto v2:g[b])
			dfs(v1,v2);
	//两个都走了 
}
void gauss(){
	for(int i=1;i<=cnt;i++){
		int k=i;
		for(int j=i+1;j<=cnt;j++){
		    if(fabs(a[j][i])>fabs(a[k][i]))
				k=j;   
		}
		for(int j=1;j<=cnt+1;j++)
			swap(a[i][j],a[k][j]);
		double tmp=a[i][i];
		if(fabs(tmp)<=eps)
			continue;
		for(int k=1;k<=cnt;k++){
			if(k==i)continue;
			double tmp=a[k][i]/a[i][i];
			for(int j=1;j<=cnt+1;j++){
				a[k][j]-=a[i][j]*tmp;
			}
		}
	}
	//高斯消元 
}
signed main(){
	int m,x,y;
	cin>>n>>m>>x>>y;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
		d[u]++,d[v]++;
	}
	for(int i=1;i<=n;i++)
		cin>>p[i];
	dfs(x,y);
	for(int sp=1;sp<=cnt;sp++){
		int i=v[sp].first,j=v[sp].second;
		//将右边的fi,j移过来后系数为-1 
		a[sp][sp]=-1;
		if(i!=j)a[sp][sp]+=p[i]*p[j];
		for(auto v1:g[i]){
			if(v1==j)continue;
			a[sp][id[v1][j]]+=(1-p[v1])*p[j]/d[v1];
		}
		for(auto v2:g[j]){
			if(v2==i)continue;
			a[sp][id[i][v2]]+=(1-p[v2])*p[i]/d[v2];
		}
		for(auto v1:g[i]){
			for(auto v2:g[j]){
				if(v1==v2)continue;
				a[sp][id[v1][v2]]+=(1-p[v1])*(1-p[v2])/d[v1]/d[v2];
			}
		}
	}
	//移项后变成-1 
	a[id[x][y]][cnt+1]=-1; 
	gauss();
	for(int i=1;i<=cnt;i++){
		if(v[i].first==v[i].second)
			ans[v[i].first]=a[i][cnt+1]/a[i][i];
		//如果有合法状态记录答案 
	}
	for(int i=1;i<=n;i++)
		printf("%.10lf ",ans[i]);
	cout<<'\n';
	return 0;
}
```

---

## 作者：I_am_Accepted (赞：2)

两个人位置状态共 $n^2$ 种，一个时刻后每种状态概率转移可以用 $n^2\times n^2$ 的矩阵 $A$ 表示，设上一个时刻 $n^2$ 种状态分别的概率为列向量 $v$，时刻后为 $v'$，则
$$
Av=v'
$$
设答案向量为 $t$，初始向量为 $v_0$，则可以有
$$
t=A^{\infty}v_0
$$
但是这样不好算，由于到终态时不会再跑出去，所以可以改写成
$$
t=\sum_{i=0}^{\infty}A^iv_0
$$
注意两个式子的 $t$ 不相等。

无穷求和经典套路
$$
\begin{aligned}
t&=\sum_{i=0}^{\infty}A^iv_0
\\&=v_0+\sum_{i=1}^{\infty}A^iv_0
\\&=v_0+A\sum_{i=0}^{\infty}A^iv_0
\\&=v_0+At
\end{aligned}
$$
即
$$
(A-I)t=-v_0
$$
高斯消元，启动！$O(n^6)$。

---

## 作者：Z1qqurat (赞：1)

其实这个题来自于一个概率期望经典模型——随机游走问题。有一张 $n$ 个点，$m$ 条边的无向图，丁真从起点 $s$ 出发，每次有相等的概率往邻近的一个点走。现有 $k$ 个终点 $t_1, t_2, \dots, t_k$，当他到达任意一个终点时他就会停下来，结束游走，求丁真最终停在每一个终点的概率。这个问题看起来很好做，我们试着定义状态 $f_i$ 表示丁真到达点 $i$ 的概率，但是我们会发现**一个非终点的点可能被经过多次**，我们无法做到确定他的经过次数（这里引出随机游走问题的一种骗分技巧：假定一个很大的终止时间，比如 $10^{18}$，然后我们假设他最多走这么久，把他的转移方式写成一个矩阵，矩阵快速幂求出概率，这只适用于答案概率取一个实数的情况，如果它要取模的话我们就不能这么骗了）。这时候有一个很神奇的转化：**虽然说一般的题目都是概率比期望好求，但是这个问题中期望比概率好求一些，我们设 $f_i$ 为第 $i$ 个点的期望经过次数**，然后对于我们要求的终点，因为最多经过一次，所以终点处的 $f_i$ 就是停在这个终点的概率。于是我们这样转移 $f_i$，将其列成 $n$ 个 $n$ 元一次方程，[高斯消元](https://www.luogu.com.cn/blog/Tsukinaga-Ichiyo/Gauss)即可。

那这个题怎么做？你发现他只是复杂了一点，首先游走的变成了两个人，并且到了每个点有 $p_i$ 的概率不动， $1 - p_i$ 的概率向相邻点等概率游走。于是我们设 $f_{i, j}$ 表示丁真和丁假分别在 $i, j$ 点的这种情况的期望出现次数，那么 $f_{i, i}, i \in [i, n]$ 便是终止状态，我们就可以分情况讨论：

* 如果丁真和丁假都在原地不动，那么贡献的期望值为 $p_i p_j \times f_{i, j}$；
* 如果丁真不动，而丁假向相邻点游走，那么贡献为 $\sum\limits_{(j, v) \in E, v \ne i}p_i\frac{1 - p_j}{deg_j} \times f_{i, v}$；
* 如果丁真向相邻点游走，而丁假不动，那么贡献为 $\sum\limits_{(i, u) \in E, u \ne j}p_j\frac{1 - p_i}{deg_i} \times f_{u, j}$；
* 如果丁真和丁假都向相邻点游走，那么贡献为 $\sum\limits_{(i, u), (j, v) \in E, u \ne v} \frac{1 - p_i}{deg_i} \frac{1 - p_j}{deg_j} \times f_{u, v}$；
* 如果 $i = sa, j = sb$，也就是说这是一个初始状态，两人都在各自的起点处，那么期望值额外加上 $1$，因为起点肯定会被无条件经过一次。

最后我们列出式子，并试着将其转化为高斯消元的线性方程组形式：
$$
\begin{aligned}f_{i, j} &= \sum\limits_{(i, u), (j, v) \in E, u \ne v} \frac{1 - p_i}{deg_i} \frac{1 - p_j}{deg_j} \times f_{u, v}
+ \sum\limits_{(j, v) \in E, v \ne i}p_i\frac{1 - p_j}{deg_j} \times f_{i, v} + \sum\limits_{(i, u) \in E, u \ne j}p_j\frac{1 - p_i}{deg_i} \times f_{u, j} + p_i p_j \times f_{i, j} + [i = sa \& j = sb] \\

-[i = sa \& j = sb] &= \sum\limits_{(i, u), (j, v) \in E, u \ne v} \frac{1 - p_i}{deg_i} \frac{1 - p_j}{deg_j} \times f_{u, v}
+ \sum\limits_{(j, v) \in E, v \ne i}p_i\frac{1 - p_j}{deg_j} \times f_{i, v} + \sum\limits_{(i, u) \in E, u \ne j}p_j\frac{1 - p_i}{deg_i} \times f_{u, j} + (p_i p_j - 1) \times f_{i, j} \end{aligned}
$$
这就是一个标准的高斯消元形式，我们把它放进矩阵就可以消元了！为了方便，我们将 $f_{i, j}$ 转化为 $f_{(i - 1)n + j}$，变成一维。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define db double
using namespace std;
const int N = 500;
int n, m, nn, sta, stb, deg[N];
double p[N], f[N], a[N][N];
vector <int> G[N];

int trans(int i, int j) {
    return (i - 1) * n + j;
} 

void build() {
    nn = n * n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int x = trans(i, j), y;
            for (int u : G[i]) {
                for (int v : G[j]) {
                    if(v == u) continue;
                    y = trans(u, v);
                    a[x][y] += 1.0 * (1 - p[u]) * (1 - p[v]) / (deg[u] * deg[v]);
                }
            }
            for (int u : G[i]) {
                if(u == j) continue;
                y = trans(u, j);
                a[x][y] += 1.0 * (1 - p[u]) / deg[u] * p[j];
            }
            for (int v : G[j]) {
                if(v == i) continue;
                y = trans(i, v);
                a[x][y] += 1.0 * (1 - p[v]) / deg[v] * p[i];
            }
            a[x][x] = -1;
            if(i != j) a[x][x] += p[i] * p[j];
        }
    }
    a[trans(sta, stb)][nn + 1] = -1;
    return ;
}

void Gauss() {
    for (int j = 1; j <= nn; ++j) {
        int maxi = j;
        for (int i = j + 1; i <= nn; ++i) {
            if(fabs(a[i][j]) > fabs(a[maxi][j])) maxi = i;
        }
        swap(a[j], a[maxi]);
        for (int i = 1; i <= nn; ++i) {
            if(i == j) continue;
            db d = a[i][j] / a[j][j];
            for (int k = 1; k <= nn + 1; ++k) {
                a[i][k] -= d * a[j][k];
            }
        }
    }
    for (int i = 1; i <= nn; ++i) {
        a[i][nn + 1] /= a[i][i];
    }
    return ;
}

int main() {
    scanf("%d %d %d %d", &n, &m, &sta, &stb);
    for (int i = 1; i <= m; ++i) {
        int u, v; scanf("%d %d", &u, &v);
        G[u].emplace_back(v), G[v].emplace_back(u);
        deg[u]++, deg[v]++;
    }
    for (int i = 1; i <= n; ++i) scanf("%lf", &p[i]);
    build();
    Gauss();
    for (int i = 1; i <= n; ++i) {
        printf("%.10lf ", a[trans(i, i)][nn + 1]);
    }
    return 0;
}
```



---

## 作者：Mr_H2T (赞：1)

# CF113D Museum 题解

首黑祭。

---

前置知识：高斯消元。

---
## 题目大意：

给定一个无向连通图，开始时两个人在其中两个结点上，人在每个点上分别有一定的概率留在原地，或者等概率得随机通过结点连接的一条边走向另一个结点。求两人在每一个结点相遇的概率。

## 分析

设 $g[i][j][k]$ 表示走 $i$ 步后两人分别在 $j,k$ 时的概率, $deg_x$ 表示结点 $x$ 的度数。

容易列出如下 dp 方程:

$$
\begin{gathered}
g[i][j][k]=g[i-1][j][k]
\cdot p_j \cdot p_k
\\
+\sum_{x\rightarrow j}g[i-1][x][k]\cdot (1-p_x)\cdot p_k\cdot \dfrac 1{deg_x}
\\
+\sum_{y\rightarrow k}g[i-1][j][y]\cdot p_j\cdot (1-p_y)\cdot\dfrac1{deg_y}
\\
+\sum_{x\rightarrow j,y\rightarrow k}
g[i-1][x][y]\cdot(1-p_x)\cdot(1-p_y)\cdot\dfrac1{deg_x\cdot deg_y}
\end{gathered}
$$

设 $f[i][j]$ 表示两个人分别在 $i,j$ 的总的概率。
$$
f[j][k]=\sum_{i=1}^{\infty}g[i][j][k]
$$
这并不好求，但我们注意到对于相同的 $j,k$ ， $g[i][j][k]$ 的值只与 $i$ 有关，则当我们求和至无穷时，可以把所有的 $g$ 也同时累加至无穷，这样关于 $g$ 的式子就转化为：
$$
\begin{gathered}
f[j][k]=f[j][k]\cdot p_j\cdot p_k
\\
+\sum_{x\rightarrow j}f[x][k]\cdot (1-p_x)\cdot p_k\cdot \dfrac 1{deg_x}
\\
+\sum_{y\rightarrow k}f[j][y]\cdot p_j\cdot (1-p_y)\cdot\dfrac1{deg_y}
\\
+\sum_{x\rightarrow j,y\rightarrow k}
f[x][y]\cdot(1-p_x)\cdot(1-p_y)\cdot\dfrac1{deg_x\cdot deg_y}
\\
+[j=s\land k=t]
\end{gathered}
$$

其中最后一项的 $[j=s\land k=t]$ 中 $s,t$ 分别表示两个起点。因为  $g[0][s][t]=1$ , $g[0][j][k]=0\ ,\  (j,k)\neq (s,t)$ 。 我们的 $f[s][t]$ 需额外加上它，故产生了最后一项。

然后由于这题 $n$ 巨小 $(n\leq 22)$ ，我们可以直接跑一遍 $O((n^2)^3)$ 的高斯消元对所有的 $f$ 进行求解。

**注意实现时当 $i=j$ 时，表达式第一项应写作 $f[j][k]$ 而不应乘上两个概率，因为相遇时不会继续转移而是留在原地。**


## 代码实现

```cpp
#include <bits/stdc++.h>
#define rint register int
#define fu(i, a, b, d, c) for (rint i = a; i <= (b) && c; i += d)
#define fd(i, a, b, d, c) for (rint i = a; i >= (b) && c; i -= d)
using namespace std;
inline int read()
{
    char c = 0, f = 1;
    int num = 0;
    while (c < '0' || c > '9' && c != '-')
        ((c = getchar()) == '-') && (f = -f);
    while (c >= '0' && c <= '9')
        num = (num << 1) + (num << 3) + (c ^ 48), c = getchar();
    return num * f;
}
int n, m, s, t;
const int MAXN = 30, MAXM = 900;
int head[MAXN], nxt[MAXM * 2], to[MAXM * 2], cnt;
void add(int u, int v) { nxt[++cnt] = head[u], head[u] = cnt, to[cnt] = v; }
double p[MAXN], a[MAXN * MAXN][MAXN * MAXN], b[MAXN * MAXN];
int getid(int x, int y) { return (x - 1) * n + y; } //获得每个状态的编号
int deg[MAXN];
signed main()
{
    n = read(), m = read(), s = read(), t = read();
    fu(i, 1, m, 1, 1)
    {
        int u = read(), v = read();
        add(u, v), add(v, u);
        deg[u]++, deg[v]++;     //记录每个点度数
    }
    fu(i, 1, n, 1, 1) scanf("%lf", &p[i]);
    fu(i, 1, n, 1, 1)
    {
        fu(j, 1, n, 1, 1)
        {
            int idnow = getid(i, j);
            if (i == j)     //注意 : 当 i == j 时不应乘以停留的概率，因为此时不会继续移动进行转移
                a[idnow][idnow] = 1.0f;
            else
                a[idnow][idnow] = 1.0f - p[i] * p[j];
            // 如题解式子所示
            for (int k = head[i]; k; k = nxt[k])    
                if (to[k] != j)
                    a[idnow][getid(to[k], j)] += -(1.0f - p[to[k]]) * p[j] / double(deg[to[k]]);
            
            for (int k = head[j]; k; k = nxt[k])
                if (to[k] != i)
                    a[idnow][getid(i, to[k])] += -(1.0f - p[to[k]]) * p[i] / double(deg[to[k]]);
            
            for (int x = head[i]; x; x = nxt[x])
                for (int y = head[j]; y; y = nxt[y])
                {
                    if (to[x] != to[y])
                        a[idnow][getid(to[x], to[y])] += -(1.0f - p[to[x]]) * (1.0f - p[to[y]]) / double(deg[to[x]]) / double(deg[to[y]]);
                }
        }
    }
    b[getid(s, t)] = 1;  //状态 f[s][t] 需额外加上 1
    int n1 = n * n;     //枚举 n*n 个状态

    //高斯消元板子
    fu(i, 1, n1, 1, 1)
    {
        fu(j, i, n1, 1, 1)
        {
            if (a[j][i] > 1e-8)
            {
                fu(t, 1, n1, 1, 1) swap(a[i][i], a[j][i]);
                swap(b[i], b[j]);
                break;
            }
        }
        fu(j, 1, n1, 1, 1)
        {
            if (j == i)
                continue;
            double rate = -a[j][i] / a[i][i];
            fu(t, 1, n1, 1, 1) a[j][t] += rate * a[i][t];
            b[j] += rate * b[i];
        }
    }
    fu(i, 1, n, 1, 1) printf("%lf ", b[getid(i, i)] / a[getid(i, i)][getid(i, i)]);
}

```

---

## 作者：chihik (赞：1)

$f_{i,j}$：两人分别在房间 $i,j$ 的概率。初始状态 $f_{a,b}=1$

$$f_{i,j}=p_ip_jf_{i,j}+\sum_{(i,u) \in E}\sum_{(j,v) \in E} \frac{1-p_u}{\deg_u} \frac{1-p_v}{\deg_v}f_{u,v}$$

$$+\sum_{(i,u) \in E} \frac{1-p_u}{\deg_u} p_jf_{u,j}+\sum_{(j,v) \in E} p_i\frac{1-p_v}{\deg_v} f_{i,v}$$

注意当后继状态的 $u=v$ 相等时不能转移。房间 $i$ 相遇的概率即为 $f_{i,i}$。

直接高斯消元即可,时间复杂度 $\mathcal O(n^6)$ 。

```cpp
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
#define eps 1e-8

template<typename _T>
void Read( _T &x ) {
	x = 0; char s = getchar();
	for( ; s < '0' || s > '9' ; s = getchar() );
	for( ; s >= '0' && s <= '9' ; s = getchar() ) x = x * 10 + s - '0';
}
template<typename _T>
void Write( _T x ) {
	if( x >= 10 ) Write( x / 10 );
	putchar( x % 10 + '0' ); 
}

const int MAXN = 22;
int n , m , w , deg[ MAXN + 5 ]; double p[ MAXN + 5 ];
bool Graph[ MAXN + 5 ][ MAXN + 5 ];

double a[ MAXN * MAXN + 5 ][ MAXN * MAXN + 5 ];

int hs( int x , int y ) { return ( x - 1 ) * n + y; }
void print( ) {
	printf("------");
	for( int i = 1 ; i <= w ; i ++ )
		for( int j = 1 ; j <= w + 1 ; j ++ )
			printf("%.2f%c", a[ i ][ j ] , j == w + 1 ? '\n' : ' ' );
	printf("--------");
}

void Gauss( ) {
	for( int i = 1 ; i <= w ; i ++ ) {
		int pos = i;
		for( int j = i + 1 ; j <= w ; j ++ )
			if( fabs( a[ j ][ i ] ) > fabs( a[ pos ][ i ] ) ) pos = j;
		swap( a[ pos ] , a[ i ] );
		if( fabs( a[ i ][ i ] ) < eps ) continue;
		for( int j = 1 ; j <= w ; j ++ )
			if( i != j ) {
				double d = a[ j ][ i ] / a[ i ][ i ];
				for( int k = i ; k <= w + 1 ; k ++ )
					a[ j ][ k ] -= a[ i ][ k ] * d;
			}
	}
	for( int i = 1 ; i <= w ; i ++ ) a[ i ][ m + 1 ] /= a[ i ][ i ];
}

int x , y;
int main( ) {
	scanf("%d %d %d %d",&n,&m,&x,&y);
	for( int i = 1 , u , v ; i <= m ; i ++ ) {
		scanf("%d %d",&u,&v); deg[ u ] ++ , deg[ v ] ++;
		Graph[ u ][ v ] = Graph[ v ][ u ] = 1;
	}
	for( int i = 1 ; i <= n ; i ++ ) scanf("%lf",&p[ i ]);
	
	w = n * n;
	a[ hs( x , y ) ][ w + 1 ] = 1;
	for( int i = 1 ; i <= n ; i ++ )
		for( int j = 1 ; j <= n ; j ++ ) {
			a[ hs( i , j ) ][ hs( i , j ) ] = 1 - ( i == j ? 0 : p[ i ] * p[ j ] ); 
			for( int u = 1 ; u <= n ; u ++ )
				for( int v = 1 ; v <= n ; v ++ )
					if( u != v && Graph[ i ][ u ] && Graph[ j ][ v ] )
						a[ hs( i , j ) ][ hs( u , v ) ] = - ( 1 - p[ u ] ) / deg[ u ] * ( 1 - p[ v ] ) / deg[ v ]; 
			for( int u = 1 ; u <= n ; u ++ )
				if( u != j && Graph[ i ][ u ] )
					a[ hs( i , j ) ][ hs( u , j ) ] = - ( 1 - p[ u ] ) / deg[ u ] * p[ j ]; 
			for( int v = 1 ; v <= n ; v ++ )
				if( i != v && Graph[ j ][ v ] )
					a[ hs( i , j ) ][ hs( i , v ) ] = - p[ i ] * ( 1 - p[ v ] ) / deg[ v ]; 
		}
	
	Gauss();
	for( int i = 1 ; i <= n ; i ++ ) printf("%.9f\n", a[ hs( i , i ) ][ w + 1 ] );
	return 0;
}
```


---

## 作者：hgzxwzf (赞：0)

## [CF113D](https://www.luogu.com.cn/problem/CF113D)

### 解题思路：

枚举终点 $en$，设 $dp_{i,j}$ 表示目前第一个人在 $i$，第二个人在 $j$ ，最后两个人在 $en$ 相遇的概率。

$dp_{i,j}=\sum_{i',j'}P(i,i')\times P(j,j')\times dp_{i',j'}$。

其中，$P(x,y)$ 表示从 $x$ 下一步走到 $y$ 的概率。

显然有 $n\times n$ 个变量，$n\times n$ 个一次方程，高斯消元求出 $dp_{a,b}$ 就是最后在 $en$ 相遇的概率。

时间复杂度为 $O(n^7)$，理论上无法通过，但 codeforces 神机名不虚传，可以 AC。

注意特判 $a=b$ 和 $i'=j'$ 的情况。

### Code：

```cpp
const int N=25;

vector<int>e[N];
int deg[N],n;
double k[N*N][N*N],p[N];
const double eqs=1e-7;

void guass()
{
	int r=1;
	rep(c,1,n*n)
	{
		int mx=r;
		rep(i,r,n*n) if(fabs(k[i][c])>fabs(k[mx][c])) mx=i;
		if(fabs(k[mx][c])<=eqs) continue;
		rep(i,c,n*n+1) swap(k[r][i],k[mx][i]);
		per(i,c,n*n+1) k[r][i]/=k[r][c];
		rep(i,r+1,n*n)
			per(j,c,n*n+1)
				k[i][j]-=k[i][c]*k[r][j];
		r++;
	}
	per(i,1,n*n)
		rep(j,i+1,n*n)
			k[i][n*n+1]-=k[i][j]*k[j][n*n+1];
}

int main()
{
	int m,a,b;
	scanf("%d%d%d%d",&n,&m,&a,&b);
	if(a==b)
	{
		rep(i,1,n) 
		{
			if(i==a) printf("1 ");
			else printf("0 ");
		}
		return 0;
	}
	rep(i,1,m)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
		deg[u]++;
		deg[v]++;
	}
	rep(i,1,n) scanf("%lf",&p[i]);
	rep(en,1,n)
	{
		memset(k,0,sizeof(k));
		rep(i,1,n)
			rep(j,1,n)
			{
				int x=(i-1)*n+j;
				for(auto &vi: e[i])
					for(auto &ui: e[j])
					{
						if(vi==ui&&vi!=en) continue;
						int y=(vi-1)*n+ui;
						k[x][y]+=((1-p[i])/deg[i])*((1-p[j])/deg[j]);
					}
				for(auto &vi: e[i])
				{
					if(vi==j&&vi!=en) continue;
					int y=(vi-1)*n+j;
					k[x][y]+=((1-p[i])/deg[i])*p[j];
				}
				for(auto &vi: e[j])
				{
					if(vi==i&&vi!=en) continue;
					int y=(i-1)*n+vi;
					k[x][y]+=((1-p[j])/deg[j])*p[i];
				}
				k[x][x]=-1;
				if(i!=j) k[x][x]+=p[i]*p[j];
			}
		rep(i,1,n*n) k[(en-1)*n+en][i]=0;
		k[(en-1)*n+en][n*n+1]=k[(en-1)*n+en][(en-1)*n+en]=1;
		guass();
		printf("%.15lf ",k[(a-1)*n+b][n*n+1]);
	}
	return 0;
}
```


---

## 作者：__stick (赞：0)

## 题意

两个人分别从 $a,b$ 开始随机游走，在每个点每个人有 $p_i$ 的概率不动，$1-p_i$ 的概率随机向当前点的出边移动，两个人相遇时立即停止移动，问在时间无限的情况下，停在每个点的概率。

## 思路
其实这道题是高斯消元的模板题。

首先，我们设立状态 $F_{i,j}$ 表示第一个人在 $i$，第二个人在 $j$ 的概率，则我们可以发现：

$$

F_{i,j}=\sum_{v\in edge(i)}F_{v,j} \cdot (1-p_v)p_j/deg(v)+\sum_{v\in edge(j)} F_{i,v} \cdot(1-p_v)p_i/seg(v)+ 

\sum_{u\in edge(i)} \sum_{v\in edge(j)}F_{u,v} \cdot(1-p_u)(1-p_v)/deg(u)
/deg(v)
+p_i p_j[i\neq j]
$$

这里一步一步解释一下。

前两个 $\sum$ 表示一个人不动的方案数，此时另一个人移动，可以从所有出边中移动过来，然后从对应点移动过来的概率就是 $(1-p_v)/deg(v)$ 原因简单，首先要移动，然后还要正好移动到当前点，所以就是 $\frac{1}{deg(v)}$ 的概率，当然还要算上另一人不动的概率。

后边 $\sum\sum$ 就是两个人一起动的方案数，同理，一个人移动到当前点就是 $(1-p_v)/deg(v),v\in edge(i)$，乘起来即可。

最后一个就是不动的概率，这里注意因为相遇即停止，所以 $i=j$ 的时候不能不动（会过不了样例）。

当然 $F_{a,b}$ 还要加上 $1$。

但是写完了会发现无法 dp，这玩意是有环的，但是数据范围非常小，仅有 $n\le 22$ ，状态数也只有 $n^2=484$ ，所以可以使用高斯消元来做。

将 $F_{i,j}$ 移动到右边，就是一个线性方程组。

直接高斯消元即可，复杂度 $O(n^6)$，可以通过。

注意有点卡精度，稍微开小一点即可。

## code

```cpp
int mod;
const int MAXN=23;
vi e[MAXN];
long double p[MAXN];
long double a[MAXN*MAXN][MAXN*MAXN+1];
const long double eps=1e-10;
void work(int n)
{
	int r=1;
	for(int c=1;c<=n;c++)
	{
		int id=r;
		for(int i=r+1;i<=n;i++)if(fabs(a[i][c])>fabs(a[id][c]))id=i;
		if(fabs(a[id][c])<=eps)continue;
		for(int i=c;i<=n+1;i++)swap(a[r][i],a[id][i]);
		for(int i=1+n;i>c;i--)a[r][i]/=a[r][c];
		a[r][c]=1;
		for(int i=r+1;i<=n;i++)if(fabs(a[i][c])>eps)
			for(int j=n+1;j>c;j--)
			{
				a[i][j]-=a[i][c]*a[r][j];
			}
		r++;
	}
	for(int i=n-1;i>=1;i--)
	{
		for(int j=i+1;j<=n;j++)
		{
			a[i][n+1]-=a[i][j]*a[j][n+1];
		}
	}
}
int main()
{		
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int n,m,s,t;
	cin>>n>>m>>s>>t;
	int u,v;
	for(int i=1;i<=m;i++)cin>>u>>v,e[u].push_back(v),e[v].push_back(u);
	for(int i=1;i<=n;i++)cin>>p[i];
	int N=n*n;
	auto getid=[&](int x,int y)
	{
		return (x-1)*n+y;	
	};
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			for(auto&v:e[i])a[getid(i,j)][getid(v,j)]=(1.0-p[v])*p[j]/e[v].size();
			for(auto&v:e[j])a[getid(i,j)][getid(i,v)]=(1.0-p[v])*p[i]/e[v].size();
			for(auto&u:e[i])
				for(auto&v:e[j])
					a[getid(i,j)][getid(u,v)]=(1.0-p[u])*(1.0-p[v])/(e[u].size()*e[v].size());
			for(int k=1;k<=n;k++)a[getid(i,j)][getid(k,k)]=0;
			a[getid(i,j)][getid(i,j)]=-1;
			if(i!=j)a[getid(i,j)][getid(i,j)]+=p[i]*p[j];//判断 i!=j
		}
	}
	a[getid(s,t)][N+1]=-1;// 记得加上初始值 1
	work(N);
	cout<<fixed<<setprecision(12);
	for(int i=1;i<=n;i++)cout<<a[getid(i,i)][N+1]<<' ';
	return 0;
} 
```




---

## 作者：cirnovsky (赞：0)

## 题意简述

[这题改成双人版](https://www.luogu.com.cn/problem/P2973)

## 题解

双人看起来挺吓人的。

但是因为数据范围比 [这题](https://www.luogu.com.cn/problem/P2973) 小了一圈，所以我们可以直接把两个人的位置记录入状态。

设 $f_{u,v}$ 表示同一时刻 Petya 在点 $u$，Vasya 在点 $v$ 的概率。

那么方程为：
$$
f_{u,v}=p_{u}p_{v}f_{u,v}+\sum_{(u,u')\in E}\sum_{(v,v')\in E}\frac{1-p_{u'}}{d_{u'}}\frac{1-p_{v'}}{d_{v'}}f_{u',v'}+\sum_{(u,u')\in E}p_{v}\frac{1-p_{u'}}{d_{v'}}f_{u',v}+\sum_{(v,v')\in E}p_{u}\frac{1-p_{v'}}{d_{v'}}f_{u,v'}
$$
无向图会出现环，所以需要高斯消元一下。

```cpp
#include <cstdio>

const double EPS = 1e-8;
const int MAXN = 500 + 5, MAXM = MAXN * MAXN;

template<typename _T> _T ABS ( const _T x ) { return x > 0 ? x : -x; }
template<typename _T> void swapp ( _T &x, _T &y ) { _T w = x; x = y; y = w; }

struct GraphSet {
	int to, nx;
	GraphSet ( int T = 0, int N = 0 ) { to = T, nx = N; }
} as[MAXM];

int n, m, s, t, cnt, upper, d[MAXN], begin[MAXN];
double mat[MAXN][MAXN], p[MAXN];

int has ( const int x, const int y ) { return ( x - 1 ) * n + y; }
void makeEdge ( const int u, const int v ) { as[++ cnt] = GraphSet ( v, begin[u] ), begin[u] = cnt; }

void Eradicate () {
	for ( int i = 1; i <= upper; ++ i ) {
		int p = i;
		for ( int j = i + 1; j <= upper; ++ j ) {
			if ( ABS ( mat[p][i] ) < ABS ( mat[j][i] ) )	p = i;
		}
		for ( int j = i + 1; j <= upper + 1; ++ j )	swapp ( mat[p][j], mat[i][j] );
		if ( ABS ( mat[i][i] ) < EPS )	continue;
		for ( int j = 1; j <= upper; ++ j ) {
			if ( i == j )	continue;
			double d = mat[j][i] / mat[i][i];
			for ( int k = 1; k <= upper + 1; ++ k )	mat[j][k] -= mat[i][k] * d;
		}
	}
	for ( int i = 1; i <= upper; ++ i )	mat[i][upper + 1] /= mat[i][i];
}

int main () {
	scanf ( "%d%d%d%d", &n, &m, &s, &t ), upper = n * n;
	for ( int i = 1, u, v; i <= m; ++ i ) {
		scanf ( "%d%d", &u, &v );
		makeEdge ( u, v ), makeEdge ( v, u );
		d[u] ++, d[v] ++;
	}
	for ( int i = 1; i <= n; ++ i )	scanf ( "%lf", &p[i] );
	for ( int i = 1; i <= n; ++ i ) {
		for ( int j = 1; j <= n; ++ j ) {
			if ( i == j )	mat[has ( i, j )][has ( i, j )] = 1;
			else	mat[has ( i, j )][has ( i, j )] = 1 - p[i] * p[j];
			for ( int ii = begin[i]; ii; ii = as[ii].nx ) {
				int u = as[ii].to;
				for ( int iii = begin[j]; iii; iii = as[iii].nx ) {
					int v = as[iii].to;
					if ( u == v )	continue;
					mat[has ( i, j )][has ( u, v )] = -( 1 - p[u] ) / d[u] * ( 1 - p[v] ) / d[v];
				}
			}
			for ( int ii = begin[i]; ii; ii = as[ii].nx ) {
				int u = as[ii].to;
				if ( u == j )	continue;
				mat[has ( i, j )][has ( u, j )] = -p[j] * ( 1 - p[u] ) / d[u];
			}
			for ( int ii = begin[j]; ii; ii = as[ii].nx ) {
				int v = as[ii].to;
				if ( i == v )	continue;
				mat[has ( i, j )][has ( i, v )] = -p[i] * ( 1 - p[v] ) / d[v];
			}
		}
	}
	mat[has ( s, t )][upper + 1] = 1;
	Eradicate ();
	for ( int i = 1; i <= n; ++ i )	printf ( "%.9lf ", mat[has ( i, i )][upper + 1] );
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

模拟赛又玉玉了，来写一点简单题。

-----------

设 $f_{u,v}$ 为第一个人在 $u$、第二个人在 $v$ 这种局面出现的期望次数。由于 $u=v$ 时过程直接结束，因此 $f_{u,v}$ 不能转移到其他点。

设点 $u$ 转移到点 $v$ 的概率是 $w_{u,v}$。

- $u=v$ 时，$w_{u,v}=p_u$；
- $u \neq v$ 时，$w_{u,v} = \dfrac{1-p_u}{\deg u} [(u,v) \in E]$。

则：

$$
f_{u,v}  = [u=s \text{ and } v=t]+\sum_{i=1}^n \sum_{j=1}^n [i \neq j]w_{i,u}w_{j,v}f_{i,j}
$$

使用高斯消元即可 $O(n^6)$ 解决问题。

```cpp
#include<bits/stdc++.h>
#define ld long double
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=23,MAXM=MAXN*MAXN+5;
int n,m,s,t,id[MAXN][MAXN];
ld p[MAXN],x[MAXM],mt[MAXM][MAXM];
vector<int> G[MAXN];
void Gauss(void) {
	ffor(i,1,n*n) {
		if(abs(mt[i][i])<=1e-9) ffor(j,i+1,n*n) if(abs(mt[j][i])>1e-9) {swap(mt[i],mt[j]);break ;}	
		ffor(j,i+1,n*n) {
			ld mul=mt[j][i]/mt[i][i];
			ffor(k,i,n*n+1) mt[j][k]-=mt[i][k]*mul;	
		}
	}
	roff(i,n*n,1) {
		ffor(j,i+1,n*n) mt[i][n*n+1]-=mt[i][j]*x[j];
		x[i]=mt[i][n*n+1]/mt[i][i];	
	}
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m>>s>>t;
	ffor(i,1,m) {
		int u,v;
		cin>>u>>v,G[u].push_back(v),G[v].push_back(u);	
	}
	ffor(i,1,n) cin>>p[i];
	ffor(i,1,n) ffor(j,1,n) id[i][j]=(i-1)*n+j;
	ffor(i,1,n) ffor(j,1,n) {
		mt[id[i][j]][id[i][j]]=1;
		vector<pair<int,ld>> L,R;
		for(auto u:G[i]) L.push_back({u,1.0*(1-p[u])/G[u].size()});
		for(auto u:G[j]) R.push_back({u,1.0*(1-p[u])/G[u].size()});
		L.push_back({i,p[i]}),R.push_back({j,p[j]});
		for(auto pr1:L) for(auto pr2:R) {
			int u=pr1.first,v=pr2.first;
			ld w=pr1.second*pr2.second;
			if(u!=v) mt[id[i][j]][id[u][v]]-=w;	
		}
		if(i==s&&j==t) mt[id[i][j]][n*n+1]=1;
	}
	Gauss();
	ffor(i,1,n) cout<<fixed<<setprecision(10)<<x[id[i][i]]<<' ';
	return 0;
}
```

---

## 作者：Zi_Gao (赞：0)

## 题意

给一个无向图，两个人从两个点出发，对于每个人，每个时刻若在 $i$ 点，则有 $p_i$ 的概率留在这个点；否则随机等概率选出边到下一个点。若两人相遇则停止，问在每个点相遇概率

$n\leq 22$

## 题解

根据图上随机游走的套路，先设一个 dp 状态，然后消元求解。这道题是两个人游走，并且用概率作为状态并不号做，所以状态设两维 $dp_{i,j}$ 表示两人同时到 $dp_{i,j}$ 表示两人分别到达 $i,j$ 的期望次数，那么答案就是 $dp_{i,i}$，为什么期望变成了概率？因为到结束状态次数的随机变量只有可能是 $0$ 或者 $1$，这种情况期望就是概率。

转移非常简单，记相邻两个点 $u,v$ 某一个时刻从 $u$ 到 $v$ 的概率是 $P_{u,v}=\frac{1-p_u}{deg_u}$，分类讨论一下即可，假设当前在 $a,b$，并且 $x,y$ 是 $a,b$ 分别的相邻点：

1. 从 $x,y$ 转移，$x\not =y$，那么概率就是 $P_{x,a}P_{y,b}$。
2. 从 $x,v$ 转移，$x\not =v$，那么概率就是 $P_{x,a}p_v$。
3. 从 $u,y$ 转移，$u\not =y$，那么概率就是 $P_{y,b}p_u$。
4. 从 $u,v$ 转移，$u\not =v$，那么概率就是 $p_up_v$。

高斯消元求解即可，时间复杂度 $\mathcal{O}\left(n^6\right)$。

```cpp
#include<bits/stdc++.h>
// #define ONLINE_JUDGE
#define INPUT_DATA_TYPE int
#define OUTPUT_DATA_TYPE int
inline __attribute((always_inline)) INPUT_DATA_TYPE read(){register INPUT_DATA_TYPE x=0;register char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_DATA_TYPE x){if(x<0)x=-x,putchar('-');if(x>9)print(x/10);putchar(x%10^48);return;}

std::vector<int> e[22];
std::vector<long double> mat[22*22];
long double p[22];
int deg[22],id[22][22];

void addEdge(int u,int v){
    e[u].push_back(v);
    e[v].push_back(u);
    ++deg[u],++deg[v];
    return;
}

#define GJ_TYPE long double
GJ_TYPE eps=1e-9;
/*
-1:infinite solutions
0: no solution
1: only one solution
*/
int GJSolve(std::vector<GJ_TYPE> *mat,int n){
    register int r,c,i,j,maxR;
    for(r=c=0;c<n;++c){
        maxR=r;
        for(i=r+1;i<n;++i) if(fabs(mat[i][c])>fabs(mat[maxR][c])) maxR=i;
        if(maxR!=r) mat[maxR].swap(mat[r]);

        if(fabs(mat[r][c])<eps) continue;

        for(i=n;i>=c;--i) mat[r][i]/=mat[r][c];
        for(i=0;i<n;++i)
            if(i!=r&&fabs(mat[i][c])>eps)
                for(j=n;j>=c;--j)
                    mat[i][j]-=mat[r][j]*mat[i][c];
        ++r;
    }
    if(r<n)
        for(i=r;i<n;++i)
            if(fabs(mat[i][n])>eps)
                return 0;

    return r<n?r-n:1;
}

int main(){
	#ifndef ONLINE_JUDGE
	freopen("name.in", "r", stdin);
	freopen("name.out", "w", stdout);
	#endif

    register int i,u,v,x,y,cnt=0,idu,idv;
    int n=read();
    int m=read();
    int a=read()-1;
    int b=read()-1;

    for(i=0;i<m;++i){
        u=read()-1;v=read()-1;
        addEdge(u,v);
    }

    for(i=0;i<n;++i) scanf("%Lf",p+i);

    for(u=0;u<n;++u)for(v=0;v<n;++v) id[u][v]=cnt++;

    for(u=0;u<n;++u)for(v=0;v<n;++v){
        idu=id[u][v];
        mat[idu].resize(cnt+2);

        mat[idu][idu]-=1;
        if(u!=v) mat[idu][idu]+=p[u]*p[v];
        for(auto x:e[u])
            for(auto y:e[v]){
                if(x==y) continue;
                idv=id[x][y];
                mat[idu][idv]+=(1-p[x])/deg[x]*(1-p[y])/deg[y];
            }
        for(auto x:e[u]){
            if(x==v) continue;
            idv=id[x][v];
            mat[idu][idv]+=(1-p[x])/deg[x]*p[v];
        }
        for(auto y:e[v]){
            if(u==y) continue;
            idv=id[u][y];
            mat[idu][idv]+=(1-p[y])/deg[y]*p[u];
        }
    }

    mat[id[a][b]][cnt]=-1;

    GJSolve(mat,cnt);

    for(i=0;i<n;++i) printf("%.10Lf ",mat[id[i][i]][cnt]);

	#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
	#endif
    return 0;
}
```

---

