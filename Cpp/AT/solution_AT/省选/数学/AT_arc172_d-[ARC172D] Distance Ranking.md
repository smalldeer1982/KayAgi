# [ARC172D] Distance Ranking

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc172/tasks/arc172_d

$ N $ 次元空間上に $ N $ 個の点 $ p_1,\ p_2,\ \dots,\ p_N $ を以下の条件を満たすように配置してください。

> **条件 1** 点の座標は $ 0 $ 以上 $ 10^8 $ 以下の整数で構成される。
> 
> **条件 2** 入力で指定された $ (A_1,\ B_1),\ (A_2,\ B_2),\ \dots,\ (A_{N(N-1)/2},\ B_{N(N-1)/2}) $ について、$ d(p_{A_1},\ p_{B_1})\ <\ d(p_{A_2},\ p_{B_2})\ <\ \dots\ <\ d(p_{A_{N(N-1)/2}},\ p_{B_{N(N-1)/2}}) $ を満たす。ここで、$ d(x,\ y) $ は点 $ x,\ y $ のユークリッド距離を示す。

なお、本問題の制約下では答えが存在することが証明できます。また、答えが複数通りある場合でも、そのうち $ 1 $ つを出力すればよいです。

  ユークリッド距離とは $ n $ 次元空間上の点 $ x,\ y $ のユークリッド距離は、$ x $ の座標を $ (x_1,\ x_2,\ \dots,\ x_n) $、$ y $ の座標を $ (y_1,\ y_2,\ \dots,\ y_n) $ として、$ \sqrt{(x_1-y_1)^2\ +\ (x_2-y_2)^2\ +\ \dots\ +\ (x_n-y_n)^2} $ と計算されます。

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 20 $
- $ 1\ \leq\ A_i\ <\ B_i\ \leq\ N\ (1\ \leq\ i\ \leq\ \frac{N(N-1)}{2}) $
- $ (A_1,\ B_1),\ (A_2,\ B_2),\ \dots,\ (A_{N(N-1)/2},\ B_{N(N-1)/2}) $ はすべて異なる
 
### Sample Explanation 1

この出力例では座標の第 $ 3 $、第 $ 4 $ の成分がすべて $ 0 $ なので、以下の $ 2 $ 次元の図で表すことができます。 $ d(p_1,\ p_2)\ =\ \sqrt{37},\ d(p_1,\ p_3)\ =\ \sqrt{40},\ d(p_2,\ p_4)\ =\ \sqrt{49},\ d(p_3,\ p_4)\ =\ \sqrt{64},\ d(p_1,\ p_4)\ =\ \sqrt{72},\ d(p_2,\ p_3)\ =\ \sqrt{113} $ であり、正しい順番になっています。 !\[\](https://img.atcoder.jp/arc172/2df65ad4071e638a89d365f0aaecf25f.png)

## 样例 #1

### 输入

```
4
1 2
1 3
2 4
3 4
1 4
2 3```

### 输出

```
3 2 0 0
9 1 0 0
1 8 0 0
9 8 0 0```

# 题解

## 作者：_LHF_ (赞：18)

很有意思的构造题/诈骗题。

首先我们知道 $n$ 个点确定一个 $n-1$ 维平面，但出题人硬要出成 $n$ 维空间，这是为什么呢？

首先先考虑一个简单的构造：如果我们要求任意两点间的距离全相等，我们能怎么构造。

显然是令 $p_{i,j}=[i=j]$。

然后考虑如何调整使得题目的要求能被满足。

首先不妨令 $p_{i,j}=10^8[i=j]$，注意到 $K=10^8$ 很大，我们可以近似看作 $+\infty$，然后我们进行一些微调。

如果不进行调整，有 $dis(p_i,p_j)=\sum_{k=1}^n(p_{i,k}-p_{j,k})^2=2K^2$，如果我们把 $p_{i,j}$ 加上 $1$ 的话答案就变成了 $2K^2-2K+O(1)$，注意到后面的 $O(1)$ 是远小于 $2K$ 和 $K^2$ 的。

再看对于 $x\not=i,x\not=j$，$dis(p_i,p_x)$ 的变化量也只是 $O(1)$ 的，也就是说我们如果给每一个 $dis(p_i,p_j)$ 都减去一个 $c_{i,j}\times K$，那么剩下的 $O(1)$ 变化量就可以忽略不计了，而 $2K^2$ 是不会改变的，所以说如果我们保证 $c_{i,j}$ 互不相同，那么影响 $dis(p_i,p_j)$ 的排名的就只有 $c_{i,j}$ 了，直接构造即可。

写出来就是：
```cpp
scanf("%d",&n);
for(int i=1;i<=n*(n-1)/2;i++) scanf("%d%d",&a[i],&b[i]);
for(int i=1;i<=n;i++) ans[i][i]=1e8;
for(int i=1,s=n*(n-1)/2;i<=n*(n-1)/2;i++) ans[b[i]][a[i]]+=s,s--;
```

~~然后我因为 a,b 数组开小了结果罚时两发。~~

---

## 作者：lsj2009 (赞：4)

省选前来写一篇人类智慧题的题解，避免考场上降智/kel

### Solution

我们不妨先来考虑 $n=3$，便于手膜。

发现 $<$ 的限制比较宽松，我们改变约束为 $d(p_{A_1},p_{B_1})=d(p_{A_2},p_{B_2})=d(p_{A_3},p_{B_3})$。

手膜易得其中一个解为：

$$
\begin{bmatrix}
 1 & 0 & 0 \\
 0 & 1 & 0 \\
 0 & 0 & 1
\end{bmatrix}
$$

事实上，可以证明的是，对于任意的 $n\ge 3$

$$
\begin{bmatrix}
 1 & 0 & 0 & \cdots & 0\\
 0 & 1 & 0 & \cdots & 0\\
 0 & 0 & 1 & \cdots & 0\\
\vdots & \vdots & \vdots & \vdots & \vdots\\
 0 & 0 & 0 & \cdots & 1
\end{bmatrix}
$$

都是一个合法解，显然任意两点距离均为 $\sqrt{2}$。

接下来我们再将等号变换为小于号，考虑微扰，设答案矩阵为：

$$
\begin{bmatrix}
 1+\epsilon_{1,1} & 0+\epsilon_{1,2} & 0+\epsilon_{1,3} \\
 0+\epsilon_{2,1} & 1+\epsilon_{2,2} & 0+\epsilon_{2,3} \\
 0+\epsilon_{3,1} & 0+\epsilon_{3,2} & 1+\epsilon_{3,3}
\end{bmatrix}
$$

则 $d(p_i,p_j)$ 为（便于讨论，记 $(i,j)=(1,2)$）：

$$\sqrt{((1+\epsilon_{1,1})-\epsilon_{2,1})^2+(\epsilon_{1,2}-(1+\epsilon_{2,2}))^2+(\epsilon_{1,3}-\epsilon_{2,3})^2}$$

事实上，当 $n,i,j$ 更大时，我们会得到一个根号下 $(\epsilon_1+1-\epsilon_2)^2+(\epsilon_3-1-\epsilon_4)^2+\sum (\epsilon'_i-\epsilon''_i)^2$ 的形式。

展开得：

$$(\epsilon_1^2+\epsilon_2^2+1+2\epsilon_1-2\epsilon_2-2\epsilon_1\epsilon_2)+(\epsilon_3^2+\epsilon_4^2+1-2\epsilon_3+2\epsilon_4-2\epsilon_3\epsilon_4)+\sum (\epsilon'_i)^2+(\epsilon''_i)^2-2\epsilon'_i\epsilon''_i$$

由于常数项固定，我们只需要关心一次和二次项得值；而我们约定 $\epsilon$ 远小于 $1$，所以 $\epsilon^2$ 远小于 $\epsilon$，故二次项的值相对于一次项微不足道，可以忽略。

故得：

$$d_{p_i,p_j}\approx \sqrt{2-(2\epsilon_{i,i}-2\epsilon_{j,i}-2\epsilon_{j,j}+2\epsilon_{i,j})}$$

观察到 $\epsilon_{i,i}$ 会在不同的 $j$ 的柿子里多次出现，不具有唯一性，较难处理，但是 $2\epsilon_{i,j}-2\epsilon_{j,i}$ 确是唯一的；我们不妨令 $\epsilon_{i,i}=0$，则让 $\epsilon_{j,i}-\epsilon_{i,j}$ 成为 $(i,j)$ 排序的关键字即可。

那么现在的构造已经非常显然了，我们简单粗暴的将上面矩阵里的 $1$ 直接扩大到 $10^8$，则 $\epsilon_{i,j}$ 已经可以用较小的正整数表示，对于一个 $(A_k,B_k)$，我们令 $\epsilon_{B_k,A_K}=0$，$\epsilon_{A_k,B_K}=\frac{n(n-1)}{2}-k+1$ 即可。

复杂度不超过读入时间。

### Code

```cpp
#include<bits/stdc++.h>
//#pragma GCC optimize(3,"Ofast","inline")
//#define int long long
#define i128 __int128
#define ll long long
#define ull unsigned long long
#define ld double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
void file_IO() {
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
}
bool M1;
const int N=25;
int ans[N][N],n;
void solve() {
	scanf("%d",&n);
	rep(i,1,n)
		ans[i][i]=1e8;
	rep(i,1,n*(n-1)/2) {
		int a,b;
		scanf("%d%d",&a,&b);
		if(a>b)
			swap(a,b);
		ans[a][b]=n*(n-1)/2-i+1;
	}
	rep(i,1,n) {
		rep(j,1,n)
			printf("%d ",ans[i][j]);
		puts("");
	}
}
bool M2;
signed main() {
	//file_IO();
	int testcase=1;
	//scanf("%d",&testcase);
	while(testcase--)
		solve();
	cerr<<"used time = "<<1000*clock()/CLOCKS_PER_SEC<<"ms\n";
	cerr<<"used memory = "<<(&M1-&M2)/1024/1024<<"MB\n";
	return 0;
}
```

---

## 作者：L_Hospital_ (赞：3)

随机化的大胜利！

我们考虑先给每个点一个随机位置，并计算现在每条边长度的排名（从小到大排序）。如果排名太大，表示这条边太长，于是给两个点各一个指向对方的位移向量，向量的长度等于实际排名和预计排名的差。如果排名太小，同理，给一个相反方向的向量。计算完每条边给每个点的位移向量后，每个点沿着自己收到位移向量的和进行位移。循环往复地做下去，直到有一组合法解。

前面的步骤用 double 存点坐标，算出合法解之后将所有点坐标最小值设成 $0$，最大值设成 $10^8$，其他点坐标按照同比例缩放直接对应到 $[0,10^8]$ 最靠近的整数上，误差较小，难以使边长排名发生变化。

没有任何调参就过了，且最慢点 84ms。感觉是因为刚开始点的坐标我设成 $[0,1]$ 范围内，相对于每次计算出的位移向量是很小的，故前几次调整能将点的离散程度恰好扩大到合适的大小。

```cpp
#include<bits/stdc++.h>
# define int long long
# define rep(i, j, k) for (int i = j; i <= k; ++i)
using namespace std;

struct dt
{
	int u, v;
	double dis;
	bool operator<(const dt &x)const{return dis < x.dis;}
} tst[205];
int n, a[205], b[205], rk[25][25], cnt;
double d[25][25], det[25][25];
int ddd[25][25];
mt19937 rng;
uniform_real_distribution < double > dk(0, 1);
signed main()
{
	ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
	cin >> n;
	rep(i, 1, n * (n - 1) / 2) cin >> a[i] >> b[i], rk[a[i]][b[i]] = i;
	rep(i, 1, n) rep(j, 1, n) d[i][j] = dk(rng);//初始化点坐标
	while (true)
	{
		cnt = 0;
		rep(i, 1, n) rep(j, i + 1, n) 
		{
			tst[++cnt] = (dt) {i, j, 0};
			rep(k, 1, n) tst[cnt].dis += (d[i][k] - d[j][k]) * (d[i][k] - d[j][k]);
		}
		sort(tst + 1, tst + cnt + 1);//计算每条边的排名
		bool b = true;
		rep(i, 1, n) rep(j, 1, n) det[i][j] = 0;
		rep(i, 1, cnt) if (rk[tst[i].u][tst[i].v] != i)
		{
			b = false;
			rep(j, 1, n) 
				det[tst[i].u][j] += (rk[tst[i].u][tst[i].v] - i) * (d[tst[i].u][j] - d[tst[i].v][j]) / sqrt(tst[i].dis), 
				det[tst[i].v][j] += (rk[tst[i].u][tst[i].v] - i) * (d[tst[i].v][j] - d[tst[i].u][j]) / sqrt(tst[i].dis);//计算每个点收到的位移向量之和
		}
		if (b)
		{//找到了符合要求的解，进行输出
			double minn = 1e15, maxx = -1e15;
			rep(i, 1, n) rep(j, 1, n)
        	    minn = min(minn, d[i][j]), maxx = max(maxx, d[i][j]);
			rep(i, 1, n) rep(j, 1, n)//同比例缩放
        	    ddd[i][j] = round(100000000 * (d[i][j] - minn) / (maxx - minn));
			rep(i, 1, n)
        	    {rep(j, 1, n) cout << ddd[i][j] << ' '; cout << '\n';}
			return 0;
		}
		rep(i, 1, n) rep(j, 1, n) d[i][j] += det[i][j];//将每个点进行位移
	}
	return 0;
}
```


---

## 作者：Purslane (赞：2)

# Solution

有趣的构造题。

考虑 $\text{dis}(i,j)^2 = \sum_{t=1}^n (p_{i,t}-p_{j,t})^2$，它的结构相当复杂。

考虑 $p_{i,i}$，它应当不怎么受 $\text{rank}_{i,j}$ 的影响，将其待定为 $C$。

则 

$$
\text{dis}(i,j)^2 = \sum_{1 \le t \le n, t \neq i,j} (p_{i,t}-p_{j,t})^2 + 2C^2 - 2C(p_{i,j}+p_{j,i}) + p_{i,j}^2 + p_{j,i}^2
$$

当 $C$ 很大时，这个值就几乎只受 $-(p_{i,j}+p_{j,i})$ 影响。

因此令 $p_{i,j} = \text{rank}_{i,j}$（$i<j$），$p_{j,i} = 0$（$i<j$），$C = 10^8$ 即可。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=20+10;
int n,ans[MAXN][MAXN]; 
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) ans[i][i]=100000000;
	roff(i,n*(n-1)/2,1) {
		int x,y;
		cin>>x>>y,ans[x][y]=i;	
	}
	ffor(i,1,n) {
		ffor(j,1,n) cout<<ans[i][j]<<' ';
		cout<<'\n';	
	}
	return 0;
}
```

---

## 作者：Jerrywang09 (赞：1)

人类智慧构造题。

看到输入中给的大小关系，想到图论，邻接矩阵。因此我果断猜测：答案一定与邻接矩阵有关。

那么问题来了：如何保证这些点之间距离的大小关系呢？看到题目中的值域，想到：我可以通过 $10^8$ 来拉开差距。具体如何实现呢？

下面是本题的神仙构造：先令 $a_{i,i}=10^8$。对于距离第 $k$ **大**的一对 $i,j$，先保证 $i<j$，然后 $a_{i,j}=k$。因此矩阵的左下角填的都是 $0$。

这样就能保证大小关系。原因是，将矩阵的第 $i$ 行与第 $j$ 行相减，会得到大数 $10^8-k$。平方过后就是 $10^{16}-2\cdot 10^8 k+k^2$。对于 $k+1$ 的情况则是 $10^{16}-2\cdot 10^8(k+1)+(k+1)^2=10^{16}-2\cdot 10^8 k-2\cdot 10^8+(k+1)^2$。这个 $-2\cdot 10^8$ 的差距，且 $n\le 20$，就注定了第 $k+1$ 对点对的距离一定比第 $k$ 对点对的距离小。

具体实现中，第 $i$ 小的是第 $\frac {n(n-1)} 2 -i$ 大的。

```cpp
// [ARC172D] Distance Ranking
#include <cstdio>
#include <iostream>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
const int N=22;
using namespace std;
char buf[1<<23], *p1=buf, *p2=buf;
#define gc() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read()
{
    int x=0, f=1; char c=gc();
    while(c<'0' || c>'9') c=='-' && (f=-1), c=gc();
    while('0'<=c && c<='9') x=(x<<3)+(x<<1)+c-'0', c=gc();
    return x*f;
}

int n, g[N][N];

int main()
{
#ifdef Jerrywang
    freopen("in.txt", "r", stdin);
#endif
    n=read();
    rep(i, 1, n*(n-1)>>1)
    {
        int u=read(), v=read();
        g[u][v]=(n*(n-1)>>1)-i;
    }
    rep(i, 1, n) g[i][i]=1e8;
    rep(i, 1, n)
    {
        rep(j, 1, n) printf("%d ", g[i][j]);
        puts("");
    }

    return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc172_d)

**题目大意**

> 给定 $n$ 个 $n$ 维空间中的点，已知他们两两之间距离的大小关系（不存在相等的距离），在 $[1,10^8]$ 范围内构造一组可能的方案。
>
> 数据范围：$n\le 20$。

**思路分析**

先考虑如何构造若干个距离两两相等的点，可以设 $x_{i,i}=1$，其他 $x_{i,j}=0$，这样两两距离都为 $1$。

然后考虑调整，如果给某个 $x_{i,j}$ 加上 $\epsilon$，那么 $\mathrm{dis}(x_i,x_j)$ 减去 $2\epsilon-\epsilon^2$，其他 $\mathrm{dis}(x_i,x_k),\mathrm{dis}(x_j,x_k)$ 变化量都是 $\epsilon^2$。

因此我们发现当 $\epsilon$ 足够小的时候，$\epsilon^2$ 可以完全忽略不计，此时就相当于让 $\mathrm{dis}(x_i,x_j)$ 小于其他的距离。

我们可以取 $x_{i,i}=10^8$，然后距离最大的一对点 $(i,j)$ 取 $x_{i,j}=1$，次大的取 $x_{i,j}=2$，其他的以此类推。

容易发现 $\epsilon^2$ 项的累计误差最大值接近 $\dfrac {n^6}6$，小于 $10^8$，因此这样的构造是合法的。

时间复杂度 $\mathcal O(n^2)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int K=1e8;
int n,a[25][25];
signed main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i) a[i][i]=K;
	for(int i=n*(n-1)/2,x,y;i;--i) scanf("%d%d",&x,&y),a[x][y]=i;
	for(int i=1;i<=n;++i,puts("")) for(int j=1;j<=n;++j) printf("%d ",a[i][j]);
	return 0;
}
```

---

## 作者：XYQ_102 (赞：0)

## D - Distance Ranking

> Place $N$ points $p_1, p_2, \dots, p_N$ in an $N$-dimensional space to satisfy the following conditions:
> 
> > **Condition 1** The coordinates of the points consist of integers between $0$ and $10^8$, inclusive.
> > 
> > **Condition 2** For $(A_1, B_1), (A_2, B_2), \dots, (A_{N(N-1)/2}, B_{N(N-1)/2})$ specified as input, $d(p_{A_1}, p_{B_1}) \lt d(p_{A_2}, p_{B_2}) \lt \dots \lt d(p_{A_{N(N-1)/2}}, p_{B_{N(N-1)/2}})$ must hold. Here, $d(x, y)$ denotes the Euclidean distance between points $x$ and $y$.
> 
> It can be proved that a solution exists under the constraints of the problem. If multiple solutions exist, just print one of them.
> 
> What is Euclidean distance? The Euclidean distance between points $x$ and $y$ in an $n$-dimensional space, with coordinates $(x_1, x_2, \dots, x_n)$ for $x$ and $(y_1, y_2, \dots, y_n)$ for $y$, is calculated as $\sqrt{(x_1-y_1)^2 + (x_2-y_2)^2 + \dots + (x_n-y_n)^2}$.
> 
> $1 \le n \le 20$

好题！

首先，$\lt$ 是不好计算的，所以我们先把它转化成 $=$。

容易发现有一种很明显的构造方式：

$$p_1={1,0,0,0,\cdots,0}$$
$$p_2={0,1,0,0,\cdots,0}$$
$$p_3={0,0,1,0,\cdots,0}$$
$$\cdots$$
$$p_n={0,0,0,0,\cdots,1}$$

于是我们尝试把它转化成 $\lt$ 的连接，这个其实只需要在原基础上面加上很小很小的数 $\epsilon$ 就可以实现，

（这里我们忽略整数这个条件，因为最后乘上 $10^8$ 就可以了）。

而由于这个 $\epsilon$ 非常小，所以之后的运算中，它的平方项都可以被忽略不计。（类似于求极限）

现在，我们得到的点是：

$$ p_1={1+\epsilon_{1,1},\epsilon_{1,2},\cdots,\epsilon_{1,n}}$$
$$p_2 = {\epsilon_{2,1},1+\epsilon_{2,2},\dots,\epsilon_{2,n}}$$
$$\cdots$$

那么我们再对 $d(x,y)$ 表示，直接化简并去掉平方项就可以得到：

$$d(x,y)=\sqrt{2-2(\epsilon_{x,y}+\epsilon_{y,x})}$$

于是我们发现影响这个的只是后面的 $\epsilon_{x,y}$，那么一种构造方式就非常明显了，我们直接让一个为  $0$，另一个按照越在后面输入的越小即可，具体来说，对于第 $i$ 组输入的 $x,y$，我们让 $\epsilon_{x,y}=n-i+1$ 即可（这里乘上了一个 $10^8$）。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int n,a[21][21],m;

int main(){
  scanf("%d",&n);m=n*(n-1)/2;
  for(int i=1;i<=n;i++) a[i][i]=1e8;
  for(int i=1,x,y;i<=m;i++) scanf("%d%d",&x,&y),a[x][y]=m-i+1;
  for(int i=1;i<=n;i++,puts("")) for(int j=1;j<=n;j++) printf("%d ",a[i][j]);
  return 0;
}
```

---

