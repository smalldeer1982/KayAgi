# [ABC347G] Grid Coloring 2

## 题目描述

有一个 $N\times N$ 的网格，每个格子上写有一个 $0$ 到 $5$ 之间的整数。第 $i$ 行第 $j$ 列的格子（$1\leq i,j\leq N$）记作格子 $(i,j)$，其中写着整数 $A_{i,j}$。

你可以对这个网格进行任意次如下操作（可以为 $0$ 次）：

- 选择一个写着 $0$ 的格子 $(i,j)$，以及一个 $1$ 到 $5$ 之间的整数 $x$，将该格子上的数改为 $x$。

操作结束后，格子 $(i,j)$ 上的整数记作 $B_{i,j}$。定义网格的**代价**为所有相邻格子上的整数差的平方和。即，代价由下式给出：

$$
\sum_{i=1}^N\sum_{j=1}^{N-1}(B_{i,j}-B_{i,j+1})^2+\sum_{i=1}^{N-1}\sum_{j=1}^N(B_{i,j}-B_{i+1,j})^2
$$

请你求出所有可能的操作结束后的网格中，代价最小的一个。

如果有多个代价最小的网格状态，输出其中任意一个即可。

## 说明/提示

### 限制条件

- $1\leq N\leq 20$
- $0\leq A_{i,j}\leq 5\ (1\leq i\leq N,1\leq j\leq N)$
- 输入均为整数

### 样例解释 1

给定的网格如下所示。  
![](https://img.atcoder.jp/abc347/0748d5e94455d9f4c627617596f61af6.png)  
通过将网格变为右图的状态，代价为 $2^2\times6+1^2\times18+0^2\times16=42$。  
无法使代价小于 $41$，因此输出对应的 $B_{i,j}$ 即为正确答案。

### 样例解释 2

初始状态的代价已经为 $0$，因此不进行操作即可达到最小代价。  
由于操作结束后的网格状态中有多个代价最小的情况，输出如下也可以：

```
2 2 2
2 2 2
2 2 2
```

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
0 2 1 0 4
4 0 0 0 2
3 1 0 3 0
1 0 0 0 0
0 0 2 0 5```

### 输出

```
3 2 1 2 4
4 2 2 2 2
3 1 2 3 3
1 1 2 3 4
1 1 2 3 5```

## 样例 #2

### 输入

```
3
0 0 0
0 0 0
0 0 0```

### 输出

```
0 0 0
0 0 0
0 0 0```

## 样例 #3

### 输入

```
10
1 0 0 3 0 0 0 0 0 0
1 0 0 4 0 1 0 5 0 0
0 0 0 0 0 0 2 0 3 0
0 0 2 0 0 0 4 0 0 3
0 3 4 3 3 0 3 0 0 5
4 1 3 4 4 0 2 1 0 0
2 0 1 0 5 2 0 1 1 5
0 0 0 5 0 0 3 2 4 0
4 5 0 0 3 2 0 3 5 0
4 0 0 5 0 0 0 3 0 5```

### 输出

```
1 2 3 3 3 2 3 4 4 4
1 2 3 4 3 1 3 5 4 4
2 2 2 3 3 2 2 3 3 3
2 2 2 3 3 3 4 3 3 3
3 3 4 3 3 3 3 2 3 5
4 1 3 4 4 3 2 1 2 4
2 2 1 4 5 2 2 1 1 5
3 3 3 5 4 3 3 2 4 5
4 5 4 4 3 2 3 3 5 5
4 4 4 5 4 3 3 3 4 5```

# 题解

## 作者：Nightingale_OI (赞：16)

### 思路

最小割太难懂了，我最大（小）权闭合子图建模给你看吧。

网格图这个性质不太重要，转一下编号看成任意图，此图中一条边 $(x,y)$ 对权值有 $(A_x-A_y)^2$ 的贡献，你要对 $A_i=0$ 的位置给 $A_i$ 赋值一个 $1\sim 5$ 的权值使得最后图的权值最小。

考虑最小权闭合子图，拆点，点 $nd_{i,t}$ 是否选择表示 $[A_i\geq t]$，显然 $nd_{i,t}\to nd_{i,t-1}$。

$$(A_x-A_y)^2=\sum_t[A_x\geq t](2t-1)+\sum_t[A_y\geq t](2t-1)-2\sum_p\sum_q[A_x\geq p][A_y\geq q])$$

于是对于一条边 $(x,y)$，为 $nd_{x,t},nd_{y,t}$ 的权值分别加上 $2t-1$。

枚举 $p,q$，建新点 $z$，权值为 $-2$，连 $z\to nd_{x,p},z\to nd_{y,q}$。

对于一个 $A_i\neq 0$，限制为 $nd_{i,A_i}$ 必须选，$nd_{i,A_i+1}$ 不能选；对于 $A_i=0$，限制为 $nd_{i,1}$ 必须选。

新建点 $X$ 权值为 $-\infty$，点 $Y$ 权值为 $+\infty$，则点 $X$ 一定选，点 $Y$ 一定不选。$X$ 向一定选的点 $x$ 连边，一定不选的点 $y$ 向 $Y$ 连边（有很多处理方式，看习惯）。

求最小权闭合子图然后输出方案即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define f(i,j,k) for(int i=j;i<=k;++i)
#define g(i,j,k) for(int i=j;i>=k;--i)
int n,m,s,l;
const int inf=1e17+289;
struct Dinic{
	//Dinic
};
struct Kazemaru{
	const static int N=202020;
	Dinic G;int v[N],w[N];
	vector<int>q[N];
	inline void add(int x,int y){q[x].push_back(y);}
	inline int clac(int n,int p=1){//最大权闭合子图建模（p=-1是最小权）
		int S=n+1,T=n+2,re=0,z;
		G.clear();G.add(S,T,0);
		f(i,1,n){
			if((z=w[i]*p)>0)G.add(S,i,z),re+=z;
			else G.add(i,T,-z);
		}
		f(x,1,n)for(int y:q[x])G.add(x,y,inf);
		f(i,0,n)q[i].clear(),w[i]=0;
		return (re-G.MF(S,T))*p;
	}
	inline int u(int x){return G.S(x);}//和源点联通的点是选出的闭合子图
	inline int&operator[](int x){return w[x];}
}K;
int a[99][99],b[99][99],c[999][9],d[999];
inline void add(int x,int y){
	f(p,1,5)K[c[x][p]]+=2*p-1,K[c[y][p]]+=2*p-1;
	f(p,1,5)f(q,1,5){
		K[++s]=-2;
		K.add(s,c[x][p]);
		K.add(s,c[y][q]);
	}
}
signed main(){
	cin>>n;
	f(i,1,n)f(j,1,n)cin>>a[i][j],d[b[i][j]=++m]=a[i][j];
	f(i,1,m)f(p,1,5)K.add(c[i][p]=++s,c[i][p-1]);
	f(i,1,n)f(j,2,n)add(b[i][j-1],b[i][j]);
	f(i,2,n)f(j,1,n)add(b[i-1][j],b[i][j]);
	int X=++s,Y=++s;K[X]=-1e9;K[Y]=1e9;
	f(i,1,m){
		if(d[i]){
			K.add(X,c[i][d[i]]);
			K.add(c[i][d[i]+1],Y);
		}else{
			K.add(X,c[i][1]);
		}
	}
	K.clac(s,-1);
	f(i,1,n){
		f(j,1,n){
			s=0;
			f(t,1,5)if(K.u(c[b[i][j]][t]))++s;
			cout<<s<<' ';
		}cout<<'\n';
	}
	return 0;
}
```

---

## 作者：XLao (赞：9)

谈谈该问题的一般形式！

[官方题解](https://atcoder.jp/contests/abc347/editorial/9689)里面提到了这个问题的形式化描述：

你要给 $n$ 个变量 $x_1\sim x_n$ 都赋一个 $[0,k-1]$ 内的整数，然后**最小化**下式：

$$\sum\limits_i f_i(x_i) + \sum\limits_{i<j} g_{i,j}(x_i,x_j)$$

本文将说明，如果所有代价矩阵 $g_{i,j}$ 都满足四边形不等式（蒙日矩阵），那么该问题可以最小割建模。

> 四边形不等式：$\forall a\le b\le c\le d,\space g(a,d)+g(b,c)\ge g(a,c)+g(b,d)$，该条件等价于 $\forall x,y,\space g(x,y+1)+g(x+1,y)\ge g(x,y)+g(x+1,y+1)$。

当 $k=2$ 时，这其实是我们熟知的一类最小割问题：有 $n$ 个商品，买一个有代价，某两个一起买有收益，求最大收益。

某两个一起买有收益，其实等价与一个买一个不买有代价；

注意到我们其实比较难处理“某两个一起买有代价”这件事，但若 $g_{i,j}$ 是蒙日的，我们可以通过调整物品单价归约到上述问题。这件事情后面会证明。

---

### 刻画 $f_i$

对于 $k$ 值一般的情况，我们对每个变量建立 $k-1$ 个点，$x_i^1,x_i^2,\cdots ,x_i^{k-1}$。

若 $x_i^d$ 与 $S$ 连通，则表明最后取值 $x_i\ge d$，连边 $x_i^d\to x_i^{d-1}$，边权 $+\infty$。最后与 $S$ 连通的总是一个前缀，前缀点的个数（可能是 0 个）则表示了该变量的最终取值。

先把 $f_i(0)$ 加到最终答案里，接着记 $\Delta_i(d)=f_i(d)-f_i(d-1)$。

- 若 $\Delta_i(d)<0$，把它加到最终答案里，并连边 $S\to x_i^d$，边权 $-\Delta_i(d)$。

- 若 $\Delta_i(d)>0$，连边 $x_i^d\to T$，边权 $\Delta_i(d)$。

盗一张图，$\theta$ 就是 $f_i$，然后 $\Delta_i$ 依次是 $-2,3,-3$：

![](https://cdn.luogu.com.cn/upload/image_hosting/rovyzglw.png)

考虑我们会先把 $f_i(0)$ 以及 $\Delta_i(1),\Delta_i(3)$ 加到答案里，若最后 $x_i$ 取 $2$，我们会割掉的边就是 $x^2\to T,S\to x^3$，最后答案为 $f_i(0)+\Delta_i(1)+\Delta_i(3)+\Delta_i(2)-\Delta_i(3)=f_i(0)+\Delta_i(1)+\Delta_i(2)=f_i(2)$ 。

---

### 刻画 $g_{i,j}$

对于每一对 $i<j$，我们只从 $x_i^d$ 向 $x_j^e$ 连边，我们要设计边权矩阵 $val(d,e)$ 表示 $x_i^d\to x_j^e$ 的边权。

假设 $x_i$ 取了 $p$，$x_j$ 取了 $q$，那么我们割掉的边形如：

![](https://cdn.luogu.com.cn/upload/image_hosting/mknfmkvs.png)

边权和为 $\sum\limits_{d=1}^p \sum\limits_{e=q+1}^{k-1}val(d,e)$。

即 $val$ 矩阵的前 $p$ 行，后 $k-1-q$ 列的所有元素之和。

考虑把 $val$ 矩阵构造成 $g_{i,j}$ 的自左下到右上的二维差分，$val(d,e)=g_{i,j}(d,e-1)-g_{i,j}(d,e)-g_{i,j}(d-1,e-1)+g_{i,j}(d-1,e)$。

由于 $g_{i,j}$ 是蒙日的，$val(d,e)$ 一定非负。

这样构造 $val$，如果所有 $g_{i,j}(0,d)$ 和 $g_{i,j}(d,k-1)$ 都是 $0$（$g_{i,j}$ 的右上边界都是 $0$），那么带入边权和的式子验证，发现就是 $g_{i,j}(p,q)$ 。

提取 $g_{i,j}$ 的第 $0$ 行，让 $f_j(d)\leftarrow f_j(d)+g_{i,j}(0,d)$。然后就可以让 $g_{i,j}$ 的每一行都减去第 $0$ 行，第 $0$ 行清零。

接着依次拿出每一行的末尾 $g_{i,j}(d,k-1)$，让 $f_i(d)\leftarrow f_i(d)+g_{i,j}(d,k-1)$，然后让该行所有数都减去末尾这个数。

注意到 每行减去一个数 和 每列减去一个数 都不会改变 $g_{i,j}$ 的蒙日性，且操作过后 $\forall d,g_{i,j}(0,d)=g_{i,j}(d,k-1)=0$。问题就解决了。

---

关于这题，由于 $g_{i,j}(d,d)=0$，官方题解里并没有采用上面的方式刻画 $g_{i,j}$，而是把主对角线上下两部分分别用 $i$ 向 $j$ 的边，和 $j$ 向 $i$ 的边刻画，构造边权仍然是二维差分，具体连边方式可以参照官方题解。

---

## 作者：adam01 (赞：6)

[更好的阅读体验](https://www.cnblogs.com/adam01/p/18106079)

非正解做法。

看到如此小的数据范围，想到退火。

大致思路就是每次随机选一个**初始**为 $0$ 的数置为 $1\sim 5$ 中的某个数，更新答案。显然网格中没有 $0$ 一定不比有 $0$ 劣（把所有 $0$ 改成同一个数一定不劣）。所以开始时把所有 $0$ 先赋值为 $1$。

然后把单次计算的复杂度从 $O(n^2)$ 变成 $O(1)$：只更新有变化位置的值。

调调参数就有概率能过了，赛时吃了 8 发。

自己赛时的参数是 $k=0.99993,T_{start}=10^{10},T_{end}=10^{-15}$。

记得多试几次。搭配 Ofast 食用 AC 概率更高！

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

using D = long double;

const int N = 25;
int a[N][N], b[N][N], ans = 1e9;
pair<int, int> pos[N * N];
int h, n;

mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

inline int p2(int x) {return x * x;}

int calc(int r, int x, int y, int v)
{
    for(int i = max(x - 1, 1); i <= min(x, n); i ++)
    for(int j = max(y - 1, 1); j <= min(y, n - 1); j ++)
        r -= p2(a[i][j] - a[i][j + 1]);
    for(int i = max(x - 1, 1); i <= min(x, n - 1); i ++)
    for(int j = max(y - 1, 1); j <= min(y, n); j ++)
        r -= p2(a[i][j] - a[i + 1][j]);
    a[x][y] = v;
    for(int i = max(x - 1, 1); i <= min(x, n); i ++)
    for(int j = max(y - 1, 1); j <= min(y, n - 1); j ++)
        r += p2(a[i][j] - a[i][j + 1]);
    for(int i = max(x - 1, 1); i <= min(x, n - 1); i ++)
    for(int j = max(y - 1, 1); j <= min(y, n); j ++)
        r += p2(a[i][j] - a[i + 1][j]);
    return r;
}

int init()
{
    int tans = 0;
    for(int i = 1; i <= n; i ++)
    for(int j = 1; j < n; j ++)
        tans += p2(a[i][j] - a[i][j + 1]);
    for(int i = 1; i < n; i ++)
    for(int j = 1; j <= n; j ++)
        tans += p2(a[i][j] - a[i + 1][j]);
    return tans;
}

D rnd01() {return rnd() * 1.L / UINT_MAX;}

void SA()
{
    int res = ans; memcpy(a, b, sizeof a);
    D T = 1e10, ed = 1e-15, k = 0.99993;
    while(T > ed)
    {
        int u = rnd() % h + 1;
        int v = rnd() % 5 + 1;
        int v0 = a[pos[u].first][pos[u].second];
        int now = calc(res, pos[u].first, pos[u].second, v);
        if(now <= ans)
        {
            ans = res = now;
            memcpy(b, a, sizeof a);
        }
        else if(rnd01() < exp((res - now) / T)) res = now;
        else a[pos[u].first][pos[u].second] = v0;
        T *= k;
    }
}

signed main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; i ++)
    {
        for(int j = 1; j <= n; j ++)
        {
            cin >> b[i][j];
            if(b[i][j] == 0) pos[++h] = {i, j}, b[i][j] = 1;
        }
    }
    memcpy(a, b, sizeof a);
    ans = init();
    // cerr << calc() << endl; 
    if(h) while(clock() * 1000.0 / CLOCKS_PER_SEC < 1780) SA();
    cerr << ans;
    for(int i = 1; i <= n; i ++)
    for(int j = 1; j <= n; j ++)    
        cout << b[i][j] << " \n"[j == n];

    return 0;
}
```

---

## 作者：Linge_Zzzz (赞：4)

# 说在前面

题意不再说明。

本人太菜了，想不到新的方法，就对上面 最小权闭合子图 的大佬做一下补充说明吧。

前置知识：最大权闭合子图模型。

最小权闭合子图，把点权取反，跑最大权闭合子图，答案取反即可。具体原因请自行思考。

# 题解

跟上面的题解一样，网格图不是必要的条件。我们可以看做在一个图上，每个点有点权 $a_i\in [1,5]$，每条边 $(u,v)$ 的贡献是 $(a_u-a_v)^2$ 可以设定一些点的点权，最小化贡献和。

不难想到对原图中每个点拆成 $5$ 个点 $C(u,1),C(u,2),C(u,3),C(u,4),C(u,5)$。在最小权闭合子图（后简称子图）中，若选择 $C(u,k)$ 则代表选择 $a_u\leq k$。对于每个 $i$，$C(u,k)$ 连向 $C(u,k-1)$ 是显然的。

考虑把式子 $(a_u-a_v)^2$ 表示到子图上。

我们都知道：$x^2=\sum_{i=1}^x (2i-1)$。

则可以做如下变形：

$ 
\begin{aligned}
(a_u-a_v)^2 
&= a_u^2+a_v^2-2a_ua_v\\
&= \sum_{i=1}^{a_u} (2i-1)+\sum_{i=1}^{a_v} (2i-1)-2\sum_{i=1}^{a_u} \sum_{j=1}^{a_v}1
\end{aligned}
$

则对于原图中每一条边 $(u,v)$，我们把 $C(u,i)$ 和 $C(v,i)$ 增加 $2i-1$。再枚举 $p,q\in[1,5]$，建立一个新点 $z$，权值为 $-2$，向 $C(u,p)$ 和 $C(v,q)$ 分别连边。

对于每个点 $u$，若这个点的点权 $a_u$ 已经给定，不可更改，则说明原图上 $C(u,a_u)$ 一定被选，$C(u,a_u+1)$ 不可能被选。

否则，则说明 $C(u,1)$ 一定被选。

如何在子图上表示点的一定被选与不可能被选？具体地，我们建立 $X$，权值为 $-inf$，再建立 $Y$，权值为 $\inf$。则 $X$ 一定被选，$Y$ 不管是主动还是间接都不可能被选。$X$ 向每个一定被选的点连边，每个一定不被选的点向 $Y$ 连边即可。

在此图上求最小权闭合子图得到的方案就是我们要求的答案。

下面来简要探讨这个建模方法的正确性。即证明以下两点：

1. 此闭合子图的任意一种合法选择方案都与原图中一种点权设定方案相对应。
2. 对于此闭合子图的任意一种合法选择方案，闭合子图的权值与此方案对应原图中方案所得的权值是等价的。

先证明第一点。

根据定义，对于原图中的点 $u$，其选择的权值为最大的 $k$ 使得任意的 $k'\leq k,C(u,k')$ 在子图中被选择。所以我们只用讨论子图中所有的 $C(u,k)$ 的选择情况。

因为对于每个 $i$，$C(u,k)$ 连向 $C(u,k-1)$，所以不可能存在 $C(u,k)$ 被选择而 $C(u,k-1)$ 不被选择的情况，得证。

再证明第二点。

首先要明确的是，子图中只包含：原图的点拆点后的点、所有的点 $z$、$X$、$Y$。

下面用 $D(u,v,p,q)$ 来表示分别连向 $C(u,p)$ 和 $C(v,q)$ 的点 $z$，用 $V(u)$ 来表示子图中 $u$ 点的权值。

不妨假设对于原图中一条边 $(u,v)$，在子图中选择了 $C(u,p)$ 和 $C(u,q)$。则 $\sum_{i=1}^p V(C(u,i))$ 能够正确表示为 $p^2$，同理，对于 $v$ 也可以表示为 $q^2$。

因为任意的 $p'\leq p,q'\leq q$，$V(D(u,v,p',q'))$ 的权值为负，所以一定会在能选的情况下尽量多选，换言之，所有的 $D(u,v,p',q')$ 一定会被选，所以其可以正确表示为 $-2pq$。得证。

综上，我们使用的建模方法可以给出一个解，且这个解最优。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
namespace mf{
	const int N=1e5+10,M=5e5+10;
	const ll INFL=0x3f3f3f3f3f3f3f3f;
	int s=N-2,t=N-3;
	struct edge{
		int v,nxt;
		ll w;
	}e[N*2];
	int head[N],cnt=2;
	void add(int u,int v,ll w){
		e[cnt].v=v;
		e[cnt].w=w;
		e[cnt].nxt=head[u];
		head[u]=cnt++;
	}
	void link(int u,int v,ll w){
		add(u,v,w);
		add(v,u,0);
	}
	int d[N],cur[N];
	bool bfs(){
		queue<int> q;
		q.push(s);
		memset(d,0,sizeof(d));
		d[s]=1,cur[s]=head[s];
		while(q.size()){
			int u=q.front();q.pop();
			for(int i=head[u];i;i=e[i].nxt){
				if(!d[e[i].v]&&e[i].w){
					d[e[i].v]=d[u]+1;
					cur[e[i].v]=head[e[i].v];
					if(e[i].v==t)return 1;
					q.push(e[i].v);
				}
			}
		}
		return 0;
	}
	ll dinic(int u,ll flow){
		if(u==t)return flow;
		ll rm=flow;
		for(int i=cur[u];i&&rm;i=e[i].nxt){
			cur[u]=i;
			if(d[e[i].v]==d[u]+1&&e[i].w){
				ll k=dinic(e[i].v,min(rm,e[i].w));
				if(!k)d[e[i].v]=0;
				rm-=k;
				e[i].w-=k;
				e[i^1].w+=k;
			}
		}
		return flow-rm;
	}
	ll Maxflow(){
		ll ans=0;
		while(bfs())ans+=dinic(s,INFL);
		return ans;
	}
}
namespace solve{
	const int N=1e5+10,M=5e5+10;
	const ll INFL=0x3f3f3f3f3f3f3f3f;
	ll v[N];
	struct edge{
		int v,nxt;
	}e[M];
	int head[N],cnt=2;
	void add(int u,int v){
		e[cnt].v=v;
		e[cnt].nxt=head[u];
		head[u]=cnt++;
	}
	ll calc(int cnt){
		ll sum=0;
		for(int i=1;i<=cnt;i++){
			for(int j=head[i];j;j=e[j].nxt)
				mf::link(i,e[j].v,INFL);
			int vv=-v[i];
			if(vv>0)mf::link(mf::s,i,vv),sum+=vv;
			else mf::link(i,mf::t,-vv);
		}
		return mf::Maxflow()-sum;
	}
}
using solve::v;
using solve::add;
using solve::calc;
using mf::d;
const int N=25;
const ll INFL=0x3f3f3f3f3f3f3f3f;
int n,a[N][N];
int cnt=0;
int pt(int i,int j,int k){return (i-1)*n+j+(k-1)*n*n;}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>a[i][j];
	cnt=n*n*5;
	int X=++cnt,Y=++cnt;
	v[X]=-1e9,v[Y]=1e9;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			for(int k=2;k<=5;k++)
				add(pt(i,j,k),pt(i,j,k-1));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(a[i][j]){
				add(X,pt(i,j,a[i][j]));
				if(a[i][j]!=5)add(pt(i,j,a[i][j]+1),Y);
			}else add(X,pt(i,j,1));
			for(int p=1;p<=5;p++){
				if(j!=n)v[pt(i,j,p)]+=2*p-1,v[pt(i,j+1,p)]+=2*p-1;
				if(i!=n)v[pt(i,j,p)]+=2*p-1,v[pt(i+1,j,p)]+=2*p-1;
				for(int q=1;q<=5;q++){
					if(j!=n){
						v[++cnt]=-2;
						add(cnt,pt(i,j,p));
						add(cnt,pt(i,j+1,q));
					}
					if(i!=n){
						v[++cnt]=-2;
						add(cnt,pt(i,j,p));
						add(cnt,pt(i+1,j,q));
					}
				}
			}
		}
	}
	calc(cnt);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			for(int k=5;k>=1;k--){
				if(d[pt(i,j,k)]){
					cout<<k<<' ';
					break;
				}
			}
		}
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：xiezheyuan (赞：2)

前排感谢我校金牌爷 [@Mashiroqwq](https://www.luogu.com.cn/user/753090)，是他教会了我这道题。为了让大家都能看懂这道题怎么做，遂写下这篇题解。

## 简要题意

给你一个 $n\times n$ 的网格，位置 $(i,j)$ 初始时填的数为 $a_{i,j}$。

你可以将任意个填有 $0$ 的数重新填一个 $1\sim 5$ 的数。你需要最小化相邻两格填的数的差的平方的和。

输出任意一组合法的方案。

$1\leq n\leq 20,0\leq a_{i,j}\leq 5$。

## 思路

考虑到对每个为 $0$ 的格子都重新赋权，一定是不劣的，这样可以少一些 corner case。

平方是一种非常难以处理的东西，考虑将其拆开，假设相邻的两个点是 $a_u$ 和 $a_v$：

$$
(a_u-a_v)^2=a_u^2+a_v^2-2a_ua_v
$$

然后你发现 $a_u^2$ 似乎也不太好处理的样子，考虑一个小学奥数知识：

$$
\sum_{i=1}^{x}2i-1 = x^2
$$

由于 $a_u$ 最大也只有 $5$，所以这个公式就有用武之地了。

我们将每个点 $u$ 拆成五个点，拆出的第 $i$ 个点 $u_i$ 表示这个格子填的数不小于 $i$。则我们若选择 $u_i$，必定选择 $u_{i-1}$。这种模型适合用最小权闭合子图来描述。

什么是最小权闭合子图？我们先要定义闭合子图的概念，对于一个图的一个点集，如果对于点集中的任意一个点 $u$ 和图中的任意一条有向边 $(u,v)$，若 $v$ 一定也在点集中，则称点集的导出子图为闭合子图。最小权闭合子图就是点权总和最小权闭合子图。

对于最小权闭合子图求解，我们一般先将其所有点权取相反数转换为最大权闭合子图，然后考虑建立最小割模型求解。

具体来说，对于原图上的边 $(u,v)$，连接弧 $(u,v,\infty)$。对于每一个点 $i$，若 $i$ 的点权大于 $0$，连接弧 $(S,i,w_i)$ 其中 $w_i$ 是 $i$ 的点权；否则连接弧 $(i,T,-w_i)$。用所有正权点的点权总和，减去这个图的最小割（数量上等于最大流），就是答案。

回到正题，我们可以对于每一个 $i$，连接 $(u_i,u_{i-1})$ 表示要选择 $u_{i}$，必须选择 $u_{i-1}$。

对于原先 $a_u\neq 0$ 的点，我们需要强制钦定 $u_{a_u}$ 必须选，$u_{a_u+1}$ 必须不选。为此，我们建立两个点 $M,\bar{M}$，其中 $M$ 点权为 $-\infty$ 表示一定会被选择，$\bar{M}$ 点权为 $\infty$ 表示一定不会被选择。然后连边 $(M,u_{a_u})$ 表示一定会选择 $u_{a_u}$，连边 $(u_{a_u+1},\bar{M})$ 表示选择 $u_{a_u+1}$ 会有极大的惩罚，不能选择。

对于原先 $a_u=0$ 的点，我们只需要简单的连边 $(M,u_1)$ 表示填的数至少需要是 $1$。

考虑对于每一个填的数 $i$，让 $u_i,v_i$ 点权增加 $2i-1$，表示平方带来的贡献。注意不要加重复了。

然后还剩下 $-2a_ua_v$，乘法同样是不适合网络流处理的问题，我们还需要将其转成加减法，根据乘法的定义，不难得到：

$$
-2a_ua_v=-2\sum_{i=1}^{a_u}a_v=-2\sum_{i=1}^{a_u}\sum_{j=1}^{a_v}1
$$

我们可以对着后面那个双重和式建图，枚举后面的 $i,j$，建立一个新点 $P(u,v,i,j)$，点权为 $-2$，连边 $(P(u,v,i,j),u_i)$ 以及 $(P(u,v,i,j),v_j)$。

这么做非常巧妙，第一是当我们将 $P(u,v,i,j)$ 加入到闭合子图时，一定会自动选择 $u_i,v_j$，第二是选择了 $u_i,v_j$，根据贪心的原理，一定会选择 $P(u,v,i,j)$，这样 $P(u,v,i,j)$ 就和 $u_i,v_j$ 绑在了一起。

同时这也展现出我们为什么要定义是填的数不小于 $i$ 了，因为这种方法建的图处理和式型贡献超级方便。

然后建图部分就结束了！按照我们以前说的方法建立最小割模型，一种最小割可以恰好对应一种最小权闭合子图方案，直接输出即可。

时间复杂度 $O(\mathrm{maxflow}(B^2n^2, B^2n^2))$，其中 $B=5$，可以通过本题。

Bonus：细心的读者可能发现了，这个做法不依赖于网格图，所以天生可以推广到一般图的情况。

## 代码

```cpp
#include <bits/stdc++.h>
#include <atcoder/maxflow>
#define X(i, j, k) ((((i) - 1) * n + (j) - 1) * 5 + (k) - 1)
#define int long long
using namespace std;

const int N = 25, M = 1e6 + 5;
int n, a[N][N], w[M];

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) cin >> a[i][j];
    }
    int tot = X(n, n, 5);
    vector<pair<int,int> > edges;
    int MUST = ++tot, MUST_NOT = ++tot; 
    w[MUST] = INT_MIN; w[MUST_NOT] = INT_MAX;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(a[i][j]){
                edges.emplace_back(MUST, X(i, j, a[i][j]));
                if(a[i][j] <= 4) edges.emplace_back(X(i, j, a[i][j] + 1), MUST_NOT);
            }
            else edges.emplace_back(MUST, X(i, j, 1));
            for(int k=1;k<=5;k++){
                if(k >= 2) edges.emplace_back(X(i, j, k), X(i, j, k - 1));
                if(i < n) w[X(i, j, k)] += ((k << 1) - 1), w[X(i + 1, j, k)] += ((k << 1) - 1);
                if(j < n) w[X(i, j, k)] += ((k << 1) - 1), w[X(i, j + 1, k)] += ((k << 1) - 1);
                for(int t=1;t<=5;t++){
                    if(i < n){
                        w[++tot] = -2;
                        edges.emplace_back(tot, X(i, j, k));
                        edges.emplace_back(tot, X(i + 1, j, t));
                    }
                    if(j < n){
                        w[++tot] = -2;
                        edges.emplace_back(tot, X(i, j, k));
                        edges.emplace_back(tot, X(i, j + 1, t));
                    }
                }
            }
        }
    }
    atcoder::mf_graph<int> g(tot + 3);
    int S = tot + 1, T = tot + 2, all = 0;
    for(int i=0;i<=tot;i++){
        w[i] = -w[i];
        if(w[i] > 0) g.add_edge(S, i, w[i]), all += w[i];
        else g.add_edge(i, T, -w[i]);
    }
    for(auto [u, v] : edges) g.add_edge(u, v, LLONG_MAX);
    cerr << (-(all - g.flow(S, T)) - INT_MIN) << '\n';
    vector<bool> min_cut = g.min_cut(S);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            for(int k=5;k;k--){
                if(min_cut[X(i, j, k)]){
                    cout << k << ' ';
                    break;
                }
            }
        }
        cout << '\n';
    }
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：juruo999 (赞：2)

# ABC 347G Grid Coloring 2

有趣的网络流题（ABC 放这个位置的很多都是网络流捏）。

### 题意

给一个矩阵，矩阵元素为 $0$ 到 $5$ 之间的整数。

你可以把其中的 $0$ 改成任意其他数，要最小化相邻元素差的平方和。

### 做法

首先考虑能不能利用平方的特殊性质，然而我推了半天没有什么实质性的进展。

换一种思路，我们可以把问题的形式变成这样：

$$
C=\sum_x f_x(B_x) + \sum_{x,y} g_{x,y}(B_x,B_y)

\tag{ * }
$$

*这里用 $x$ 来代表格子 $(i,j)$*

其中 $f_x(a)$ 在 $A_x=0$ 时或 $A_x=a$ 时为 $0$，否则为 $+\infty$，表示这些 $x$ 必须要有 $B_x=A_x$。

而 $g_{x,y}(a,b)$ 在 $x,y$ 相邻时取 $0$，否则取 $(a-b)^2$。

值域很小，所以考虑使用网络流或整数规划之类的做法。那么问题的关键在于如何刻画 $B_x$ **只能取一个值** 这一约束。事实上这一约束并不是线性的，这也是常规网络流做法难以解决此类问题的原因。

这题最巧妙的一点是用 **用最小割模型中的连通性** 来表示 $B_x$。具体来说，我们使用最小割模型。对每个位置 $x$ 建立四个点 $V_{x,t}$ （ $t=1,2,3,4$ ），连边 $V_{x,t}\to V_{x,t+1}$ ，权值为 $+\infty$。

这时，我们发现最小割中一定是 $V_{x,b},\cdots,V_{x,4}$ 这样连续的一段能与 $s$ 连通，剩下的与 $t$ 连通。那么我们可以用**哪一段前缀与** $s$ **连通**来表示 $B_x$ 取什么值。在这里，我们用 $b$ 来表示 $B_x$（如果所有点都和 $s$ 不连通则 $B_x$ 取 $5$）。

那么我们来依次刻画 $f_x$ 和 $g_{x,y}$。

对于 $A_x\not = 0$ 的格子，由于钦定了 $B_x$ 一定就是 $A_x$，我们连边 $s\to V_{x,A_x}$ 与 $V_{x,A_x-1}\to t$（边权 $+\infty$，不存在则不连），那么肯定是 $A_x$ 以下与 $s$ 连通，$A_x-1$ 以上与 $t$ 连通，这样我们就处理好了 $f_x$ 的约束。

![](https://cdn.luogu.com.cn/upload/image_hosting/budw07ie.png)

而又注意到在 $a>b$ 时有：

$$
\begin{aligned}
(a-b)^2&=(a-b)+\sum_{b<i\le j\le a} 2 \\
&=\sum_{b<i\le a}1+\sum_{b<i\le j\le a} 2
\end{aligned}
$$

*这个“注意到”其实本质上就是对 $g_{x,y}=(a-b)^2$ 做了个二维差分，而只要这个二维差分恒为正，这题的方法就能使用。*

我们只要对于相邻的格子 $x$ 与 $y$，连边 $V_{x,a}\to V_{y,a}$，权值为 $1$，再连边 $V_{x,a}\to V_{y,b}$ 与 $V_{x,b}\to V_{y,a}$（$a<b$），权值为 $2$。

这时可以发现，要使 $B_x=a$ 且 $B_y=b$（不妨 $a\ge b$），就一定要切断所有的边 $(V_{x,i},V_{y,j}),i\ge a,j<b$。这时我们会惊奇地发现，所有这些边的代价之和恰好就是 $(a-b)^2$ ！

总之，这张图长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/g6zu5wtq.png)

快乐地跑强而有力的最小割就行了。

### 代码

[完整版](https://www.luogu.com.cn/paste/ebrfxmyu)

核心部分：

```cpp
ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);

reset();
cin>>n;

s=4*n*n+1,t=4*n*n+2,V=4*n*n+10;	// s,t,V 为图的源、汇、点数

for(int i=1;i<=n;i++){  // 建图
    for(int j=1;j<=n;j++){
        int p=i*n+j-n-1;    // 4p+1,2,3,4
        int x;cin>>x;
        add(4*p+1,4*p+2,inf);   // x,a -> x,a+1
        add(4*p+2,4*p+3,inf);
        add(4*p+3,4*p+4,inf);
        if(x!=0){
            if(x<5) add(s,4*p+x,inf);   // s -> x,Ax
            if(x>1) add(4*p+x-1,t,inf); // x,Ax-1 -> t
        }
        if(j<n){                        // 相邻点连边
            for(int a=1;a<=4;a++){
                add(4*p+a,4*(p+1)+a,1);
                for(int b=a+1;b<=4;b++){
                    add(4*p+a,4*(p+1)+b,2);
                }
            }
        }
        if(j>1){
            for(int a=1;a<=4;a++){
                add(4*p+a,4*(p-1)+a,1);
                for(int b=a+1;b<=4;b++){
                    add(4*p+a,4*(p-1)+b,2);
                }
            }
        }
        if(i<n){
            for(int a=1;a<=4;a++){
                add(4*p+a,4*(p+n)+a,1);
                for(int b=a+1;b<=4;b++){
                    add(4*p+a,4*(p+n)+b,2);
                }
            }
        }
        if(i>1){
            for(int a=1;a<=4;a++){
                add(4*p+a,4*(p-n)+a,1);
                for(int b=a+1;b<=4;b++){
                    add(4*p+a,4*(p-n)+b,2);
                }
            }
        }
    }
}

// cout<<Flow()<<"\n";
Flow();

findp();    // 输出方案

for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
        int p=i*n+j-n-1;
        bool f=1;
        for(int a=1;a<=4;a++){
            if(h[4*p+a]!=0){ cout<<a<<" ";f=0;break; }
            // h 为该节点是否与 s 连通
        }
        if(f) cout<<5<<" ";
    }
    cout<<"\n";
}
```

### 碎碎念

事实上，不止这道题可以表示为 $(*)$ 的形式。对于所有二维差分恒为正的 $g_{x,y}(a,b)$（即构成一个蒙日矩阵的 $g$），都可以这样处理。类似的题目还有：

[ARC 107 Sum Abs](https://www.luogu.com.cn/problem/solution/AT_arc107_f)

**推荐阅读**

[官方题解](https://atcoder.jp/contests/abc347/editorial/9689)

[最小カット問題の k 値への一般化](https://noshi91.hatenablog.com/entry/2021/06/29/044225)

---

## 作者：pan_g (赞：1)

[传送门1](https://www.luogu.com.cn/problem/AT_abc347_g)
[传送门2](https://atcoder.jp/contests/abc347/tasks/abc347_g)

这题的话是个方格题，所以先考虑网络流（参考官方题解）。

~~官方题解中，有一个概念叫蒙日矩阵，可能能想出一个好的解决题目的方案，可惜我太菜了，我想不出来。~~

不过，这道题很显然是可以转化成一个最小割的模型，因为数据范围与值域都很小，可以暴力建点。

定义每个点（除源点与汇点外）为 $(i,j)_{>k}(i,j\in\{1,2,\cdots,N\}, k\in\{1,2,3,4\})$ 。

## 建图

**Condition 1:**

对于矩阵中同一点来讲，有 $(i,j)_{>k+1}\stackrel{+\infin}\to (i,j)_{>k}(k\in\{1,2,3\})$ ，这样对最终计数有帮助。

如果 $S$ 割内，包含了 $(i,j)_{>k}$ ，那也必然包含了比 $k$ 小的几个点，所以只要记录 $S$ 割内有几个 $(i,j)_{>k}$ ，就是最终矩阵的结果。

**Condition 2:**

对于 $A_{i,j} \neq 0$ ，即  $A_{i,j} = B_{i,j}$ 的情况。

可以直接 $S\stackrel{+\infin}\to (i,j)_{>A_{i,j}-1},(i,j)_{>A_{i,j}}\stackrel{+\infin}\to T$ 与汇点相连，其中对于 $A_{i,j} = 1$ 不连前一条，对于 $A_{i,j} = 5$ 不连后一条，因为无论如何，已经做到了 **Condition 1** 中想要的结果，即 $(i,j)_{>k}(k<A_{i,j})$ 在 $S$ 割内， $(i,j)_{>k}(k\geq A_{i,j})$ 在 $T$ 割内，达到了 $A_{i,j} = B_{i,j}$ 的目的。

**Condition 3:**

对于 $A_{i,j} = 0$ 的情况，考虑到 $k^2 = \sum_{x=0}^{k-1} 2x+1$ 。

于是可以如此建图：对于相邻两点 $x$ 与 $y$ ， $x_{>k}\stackrel{1}\to y_{>k}(1\leq k\leq 4),x_{>k}\stackrel{2}\to y_{>l}(1\leq l<k\leq 4)$ 。

这样建图的主要原因是，因为只有可能是 $S$ 到 $T$ 割，所以只需要将每个点的每个 $>k$ 对于邻点的 $>l(1\leq l<k\leq 4)$ 的贡献连出来，如果被割到同一个割内了，那么还是可以相应地减掉多余的贡献（具体可以自己画图理解）。

其实就是 $k-l$ 等价于上式的 $x$ 。

## 求解

图建完后，跑一遍最小割（也就是最大流），跑出的结果就是它的最小花费。

最终的矩阵，可以通过求 $S$ 割中的点用 **Condition 1** 的方式求出最终的矩阵。

因为数据范围很小， $|V| = 4N^2,|E| = 24N^2$ ，跑 Dinic 时间复杂度大概在 $O(N^6)$ ，常数在 $400$ 以内。

### AC CODE

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read(){
	ll res = 0, f = 1;
	char c = getchar();
	for(;!isdigit(c); c = getchar()) if(c == '-') f *= -1;
	for(;isdigit(c); c = getchar()) res = (res << 3) + (res << 1) + (c ^ 48);
	return res * f;
}
inline void write(ll x){
	if(x < 0) putchar('-'), x *= -1;
	if(x > 9) write(x/10);
	putchar(x%10+48); return ;
}

template <class Cap> struct net{ // 把最大流直接打包了
	public:
		net() : n(0) {}
		explicit net(int x) : n(x), g(n) {}
		int add(int u, int v, Cap cap){
			assert(0 <= u && u < n);
			assert(0 <= v && v < n);
			assert(0 <= cap);
			int id = (int)(pos.size());
			pos.emplace_back(make_pair(u, (int)(g[u].size())));
			int uid = (int)(g[u].size()), vid = (int)(g[v].size());
			if(u == v) vid ++;
			g[u].emplace_back(Edge{v, vid, cap});
			g[v].emplace_back(Edge{u, uid, 0});
			return id;
		}
		Cap MF(int S, int T){
			assert(0 <= S && S < n);
			assert(0 <= T && T < n);
			assert(S != T);
			vector<int> dep(n), cur(n);
			auto BFS = [&](){
				fill(dep.begin(), dep.end(), -1);
				fill(cur.begin(), cur.end(), 0);
				dep[S] = 0; queue<int> q; q.push(S);
				while(!q.empty()){
					int u = q.front(); q.pop();
					for(auto e : g[u]){
						int v = e.to;
						if(!e.cap || dep[v] != -1) continue;
						dep[v] = dep[u] + 1; q.push(v);
					}
				}
				return dep[T] != -1;
			};
			auto DFS = [&](auto self, int u, Cap flow){
				if(u == T) return flow;
				Cap res = 0, k;
				for(int i = cur[u];i < (int)(g[u].size()) && res < flow; i++){
					Edge e = g[u][i]; int v = e.to; cur[u] = i;
					if(dep[v] != dep[u] + 1 || !e.cap) continue;
					k = self(self, v, min(flow - res, e.cap));
					if(!k) dep[v] = -1; 
					g[u][i].cap -= k, g[v][e.rev].cap += k, res += k;
				}
				return res;
			};
			Cap maxflow = 0;
			while(BFS()) maxflow += DFS(DFS, S, numeric_limits<Cap>::max());
			return maxflow;
		} // 很板的 Dinic
		vector<bool> MC(int S){
			vector<bool> vis(n);
			queue<int> q;
			q.push(S);
			while(!q.empty()){
				int u = q.front(); q.pop();
				vis[u] = true;
				for(auto e : g[u]){
					if(!e.cap || vis[e.to]) continue;
					vis[e.to] = true, q.push(e.to);
				}
			}
			return vis;
		} // 求 S 割
	private:
		int n, tot = 1;
		struct Edge{
			int to, rev;
			Cap cap;
		};
		vector<vector<Edge> > g;
		vector<pair<int, int> > pos;
};
	
int n, s, t;
int main(){
	n = read(); net<int> G(4 * n * n + 2);
	s = 0, t = n * n * 4 + 1;
	auto id = [&](int i, int j, int v) { return (i * n + j) * 4 + v; }; 
	for(int i = 0;i < n;i++) for(int j = 0;j < n;j++) for(int v = 1;v < 4;v++) G.add(id(i, j, v + 1), id(i, j, v), homo);
	for(int i = 0;i < n;i++) for(int j = 0;j < n;j++) for(int v = 1;v <= 4;v++){
		if(i != n - 1){
			G.add(id(i, j, v), id(i + 1, j, v), 1), G.add(id(i + 1, j, v), id(i, j, v), 1);
			for(int u = 1;u < v;u++) G.add(id(i, j, v), id(i + 1, j, u), 2), G.add(id(i + 1, j, v), id(i, j, u), 2);
		}
		if(j != n - 1){
			G.add(id(i, j, v), id(i, j + 1, v), 1), G.add(id(i, j + 1, v), id(i, j, v), 1);
			for(int u = 1;u < v;u++) G.add(id(i, j, v), id(i, j + 1, u), 2), G.add(id(i, j + 1, v), id(i, j, u), 2);
		}
	}
	for(int i = 0;i < n;i++) for(int j = 0;j < n;j++){
		int a = read();
		if(a == 0) continue;
		if(a < 5) G.add(id(i, j, a), t, homo);
		if(a > 1) G.add(s, id(i, j, a - 1), homo);
	} // 按上面说的连即可
	G.MF(s, t); auto cut = G.MC(s);
	for(int i = 0;i < n;i++){
		for(int j = 0;j < n;j++){
			int b = 1; // 最开始应该是 1
			for(int v = 1;v <= 4;v++) b += cut[id(i, j, v)];
			write(b), putchar(' ');
		}
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：BINYU (赞：0)

和官方题解不一样的最小割建图方式。

用 $(i,j,k)$ 表示网络流中代表原图 $(i,j)$ 位置选 $k$ 的点。

拆贡献 $(A_i - A_j)^2 = A_i^2+A_j^2-2A_iA_j$。

发现 $- 2A_iA_j$ 割不了，考虑写成 $(5-A_i)A_j+(5-A_j)A_i-5A_j-5A_i$，则 $(A_i - A_j)^2 = (A_i^2-5A_i)+(A_j^2-5A_j)+(5-A_i)A_j+(5-A_j)A_i$，发现 $A_i^2-5A_i$ 还是割不了，直接加上 $25$ 即可。

因为一个数有多于两种选法，没法用集合划分模型，所以必须使用另一个模型：

从 $(i,j,k)$ 向 $(i,j,k+1)$ 连一条边，流量为选 $(i,j,k)$ 的代价，即 $(k^2-5k+25)(4-[i=1]-[i=n]-[j=1]-[j=n])$（注意这里 $k^2-5k+25$ 为一组相邻的点拆出来的代价，不是总代价）。

特别的 $(i,j,5)$ 向汇点连边，源点向 $(i,j,1)$ 连一条流量为 $+\infty$ 的边。

如果 $A_{i,j} \not = 0$，则把其他边的流量改成 $+\infty$ 即可。

从 $(i_1,j_1,k_1)$ 向 $(i_2,j_2,k_2)$ 连一条边，当且仅当 $(i_1,j_1)$ 和 $(i_2,j_2)$ 相邻，此时则源点和汇点之间会多出 $B_{i_1,j_1}(5-B_{i_2,j_2})+B_{i_2,j_2}(5-B_{i_1,j_1})$ 条边，每条边流量为 $1$ 即可。

统计答案很简单，看一下哪些点和源点联通即可。

Code：https://atcoder.jp/contests/abc347/submissions/57653021。

---

