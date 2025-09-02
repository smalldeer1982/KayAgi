# Islands and Bridges

## 题目描述

给定一张由岛屿和连接这些岛屿的桥梁构成的地图，众所周知，哈密顿路径是沿着桥梁的路径，能够恰好访问每个岛屿一次。在我们的地图中，每个岛屿还关联一个正整数值。我们定义一种哈密顿路径为 **最佳三角形哈密顿路径**，其最大化以下描述的值。

假设有 $n$ 个岛屿。哈密顿路径 $C_1,C_2,\dots,C_n$ 的值分为三部分计算。设 $V_i$ 为岛屿 $C_i$ 的值。第一部分为路径中每个岛屿的 $V_i$ 值的总和。第二部分，对于路径中的每条边 $C_i C_{i+1}$，加上 $V_i \times V_{i+1}$ 的积。第三部分，对于路径中的每三个连续岛屿 $C_i, C_{i+1}, C_{i+2}$，如果它们在地图中形成一个三角形（即 $C_i$ 和 $C_{i+2}$ 之间有桥），加上 $V_i \times V_{i+1} \times V_{i+2}$ 的积。

最佳三角形哈密顿路径很可能（但不一定）包含多个三角形。可能会存在多个最佳三角形哈密顿路径。你的第二个任务是找出这样的路径的数量。

---

## 样例 #1

### 输入

```
2
3 3
2 2 2
1 2
2 3
3 1 
4 6
1 2 3 4
1 2
1 3
1 4
2 3
2 4
3 4```

### 输出

```
22 3
69 1```

# 题解

## 作者：meifan666 (赞：3)

### 题目大意
给定一张有
$n$
个点和
$m$
条边的无向图，求最佳三角形哈密顿路径的最大值（计算方法不再赘述），并求出最优解的种类数。
### 思路
题目让我们求的是特殊哈密顿路径，加之
$n\le13$
的条件，不难想到**状压
dp**。

对于第一问，我们发现要想计算路径的值，就一定得知道连续三个点的联通情况，于是我们令
$dp[i][j][k]$
表示二进制状态（即走过的点）为
$i$，现在在
$j$
点，上一步在
$k$
点，此时的最大值。dp
时考虑点的联通情况并按题目条件模拟即可（具体的状态转移方程见代码）。

对于第二问，很容易想到类比[最短路计数](https://www.luogu.com.cn/problem/P1144)这题的思想，令
$sum[i][j][k]$表示二进制状态为
$i$，现在在
$j$
点，上一步在
$k$
点，最优解的数量，同
dp
数组一起变化。同时要注意的是，**如果一条路径的顺序反转，仍认为它是相同的路径**，所以要将结果除以
$2$，因为对于每一条路径，重复了且只重复算了
$1$
次它的反转形式。

下面贴上代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int T,n,m,dp[1<<14][15][15],sum[1<<14][15][15],v[15],x,y;
int ans1,ans2;
bool edge[15][15];
void init(){
	ans1=0,ans2=0;
	memset(edge,0,sizeof(edge));
	memset(dp,-0x3f,sizeof(dp));
	memset(sum,0,sizeof(sum));
} 
signed main(){
	cin>>T;
	while(T--){
		cin>>n>>m;init();
		for(int i=0;i<n;i++){
			cin>>v[i];
		}
		if(n==1){cout<<v[0]<<' '<<1<<'\n';continue;}
		while(m--){
			cin>>x>>y;--x,--y;
			edge[x][y]=edge[y][x]=1;
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(!edge[i][j])continue;
				dp[(1<<i)|(1<<j)][i][j]=v[i]+v[j]+v[i]*v[j];
				sum[(1<<i)|(1<<j)][i][j]=1;
			}
		}
		for(int i=0;i<(1<<n);i++){
			for(int j=0;j<n;j++){
				if((i&(1<<j))==0)continue;
				for(int k=0;k<n;k++){
					if((i&(1<<k))==0||!edge[k][j]||j==k)continue;
					for(int l=0;l<n;l++){
						if((i&(1<<l))==0||!edge[k][l]||j==l||k==l)continue;
						int t=dp[i^(1<<j)][k][l];
						t+=v[k]*v[j]+v[j];
						if(edge[l][j])t+=v[j]*v[k]*v[l];
						if(t>dp[i][j][k])
							dp[i][j][k]=t,sum[i][j][k]=sum[i^(1<<j)][k][l];
						else if(t==dp[i][j][k])
							sum[i][j][k]+=sum[i^(1<<j)][k][l];
					}
				}
			}
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(i==j)continue;
				if(dp[(1<<n)-1][i][j]>ans1)
					ans1=dp[(1<<n)-1][i][j],ans2=sum[(1<<n)-1][i][j];
				else if(dp[(1<<n)-1][i][j]==ans1)
					ans2+=sum[(1<<n)-1][i][j];
			}
		}
		cout<<ans1<<' '<<ans2/2<<'\n';
	}
	return 0;
}
```
最后要注意，如果你错在第
$4$
个点，记住特判
$n=1$
的情况。

---

## 作者：CommandSR (赞：2)

## 题意简述

给定一个由岛屿和桥梁组成的无向图，每个岛屿有一个正整数值。我们需要找到所有可能的哈密顿路径（即访问每个岛屿恰好一次的路径），并计算每条路径的"最佳三角形哈密顿值"。

路径值的计算分为三部分：

1. 路径中所有岛屿值的总和。
2. 路径中相邻岛屿值乘积的总和。
3. 路径中每三个连续岛屿如果形成三角形（即首尾岛屿有直接桥梁连接），则加上这三个岛屿值乘积的总和。

我们需要找出所有能达到最大值的路径，并统计这样的路径数量（注意：正向和反向的路径视为同一条路径）。

## 基本思路

提示：在尝试本题前，可以先通过经典的[最短 Hamilton 路径](https://www.luogu.com.cn/problem/P10447)。

注意到 $n \leq 13$，考虑状压 DP。

类比于经典的哈密尔顿路径问题，因为本题需要判连续三个点的联通情况，所以需要同时记录**当前最后一个到达的点**和**当前倒数第二个到达的点**。

不妨令 $f_{s, i, j}$ 为当前状态为 $s$，当前在第 $j$ 个点，上一步在第 $i$ 个点的三角形哈密顿路径最大值。令 $h_{s, i, j}$ 为当前状态为 $s$，当前在第 $j$ 个点，上一步在第 $i$ 个点的最佳三角形哈密顿路径数量。

根据基本的计数原理，状态转移方程如下：

```cpp
ll cur = f[s][k][j] + a[i]*a[j] + g[i][k]*a[i]*a[j]*a[k];
if (f[s|(1<<i)][j][i] < cur) {
    f[s|(1<<i)][j][i] = cur;
    h[s|(1<<i)][j][i] = h[s][k][j];
} else if (f[s|(1<<i)][j][i] == cur) {
    h[s|(1<<i)][j][i] += h[s][k][j];
}
```

即从 $k \rightarrow j$ 的路径对应状态转移到 $j \rightarrow i$ 的路径对应状态。

转移时要保证 $k \rightarrow j$ 和 $j \rightarrow i$ 有连边，$j$ 和 $k$ 都在 $s$ 集合里，而 $i$ 不在。

注意：正向和反向的路径视为同一条路径，第二问的答案统计完除以 $2$。



## AC Code

```cpp
#include <bits/stdc++.h>
#define F(i, a, b) for (int i = a; i <= b; ++i)
#define _F(i, a, b) for (int i = a; i >= b; --i)
#define ll long long
#define FULL ((1<<n)-1)
using namespace std;
int rd() {
	ll p = 0, f = 1; char ch = getchar();
	while (ch>'9' || ch<'0') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch>='0' && ch<='9') p = p*10+ch-'0', ch = getchar();
	return p * f;
}
ll n, m, a[16], f[(1<<14)+5][16][16], h[(1<<14)+5][16][16], ans, ans2, sum;
bool g[16][16];
void Solve() {
	memset(g, 0, sizeof g); memset(f, 0, sizeof f); memset(h, 0, sizeof f); ans2 = 0, ans = 0, sum = 0;
	n = rd(), m = rd(); F(i, 0, n-1) a[i] = rd(), sum += a[i];
	if (n == 1) {
		cout << 1 << ' ' << 1 << '\n';
		return ;
	}
	F(i, 1, m) {
		int u = rd()-1, v = rd()-1; g[u][v] = g[v][u] = 1;
	}
	F(k, 0, n-1) {
		F(j, 0, n-1) {
			if (g[k][j]) {
				f[1<<k|1<<j][k][j] = a[k]*a[j];
				h[1<<k|1<<j][k][j] = 1;
			}
		}
	}
	F(s, 0, FULL) {
		F(k, 0, n-1) {
			if (!s&(1<<k)) continue ;
			F(j, 0, n-1) {
				if (!s&(1<<j)) continue ;
				if (!g[k][j] || !f[s][k][j]) continue ;
				F(i, 0, n-1) {
					if (s&(1<<i) || !g[j][i]) continue ;
					ll cur = f[s][k][j] + a[i]*a[j] + g[i][k]*a[i]*a[j]*a[k];
					if (f[s|(1<<i)][j][i] < cur) {
						f[s|(1<<i)][j][i] = cur;
						h[s|(1<<i)][j][i] = h[s][k][j];
					} else if (f[s|(1<<i)][j][i] == cur) {
						h[s|(1<<i)][j][i] += h[s][k][j];
					}
				}
			}
		}
	}
	F(k, 0, n-1) {
		F(j, 0, n-1) {
			if (g[k][j]) {
				if (f[FULL][k][j] > ans) {
					ans = f[FULL][k][j];
					ans2 = h[FULL][k][j];
				} else if (f[FULL][k][j] == ans) {
					ans2 += h[FULL][k][j];
				}
			}
		}
	}
	cout << ans+sum*(ans>0) << ' ' << (ans2>>1) << '\n';
}
int main() {
	int T = rd(); while (T--) Solve();
	return 0;
}
```

---

## 作者：DrDuck (赞：1)

### 前置芝士：状压 DP
第一问：

这道题和普通哈密尔顿问题的不同点在于，当三个点组成一个三角形的时候，要加上三个点点权之积。很显然在状态中只记一个点是不行的，要记两个点。

因此我们仿照哈密尔顿问题的状态定义方式，设 $f_{i,j,k}$ 为最后一步为从节点 $j$ 走到节点 $i$，当前各节点访问情况为 $k$ 的最大值，其中 $k$ 中对应的点的二进制下的值，为 $0$ 代表没有访问，$1$ 代表已访问。定义 $v_{i, j}$ 为点 $i$ 与 $j$ 是否联通，每个点权值为 $a_i$，可以写出以下的状态转移方程：
$$
sum = \begin{cases}
a_i + a_i \times a_j + a_i \times a_j \times a_l ,& v_{i, l}\\
a_i + a_i \times a_j ,& \text{ otherwise.}\\
\end{cases}
$$
$$
f_{i, j, k} = \max(f_{j, l, p} + sum)
$$
其中 $p$ 表示状态 $k$ 挖去 $i$ 点后的状态。

注意如果 $f_{j, l, p}$ 不是一个合法状态，或 $i$ 与 $j$ 之间没有边时不要转移。

第二问：

题目还让我们求权值最大时的方案数。新开一个数组 $g_{i, j, k}$ 表示当 $f_{i, j, k}$ 取得最大时的方案数。每次按上述转移方程进行转移时：

* 若 $f_{j, l, p} + sum > f_{i, j, k}$，置 $g_{i, j, k} \gets g_{j, l, p}$。
* 若 $f_{j, l, p} + sum = f_{i, j, k}$，置 $g_{i, j, k} \gets g_{i, j, k} + g_{j, l, p}$。

当然你也可以先一口气把 $f$ 数组求出来，在加上所有 $f_{j, l, p} + sum = f_{i, j, k}$ 时 $g_{j, l, p}$ 的值。

由于如果一条路径的顺序反转，仍认为它是相同的路径，而这样的路径总是成对出现的，输出答案时将方案数除以 $2$ 即可。

初始状态：

* $f_{i, i, k} = a_i$，其中 $k$ 可通过 `1 << (i - 1)` 得到。
* $g_{i, i, k} = 1$。

注意特判只有一个点（即 $n = 1$）的情况。

# CODE

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 14;
int q, n, m;
int f[maxn][maxn][(1 << (maxn - 1)) + 2], g[maxn][maxn][(1 << (maxn - 1)) + 2], a[maxn];
bool v[maxn][maxn];
void init()
{
    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    memset(v, 0, sizeof(v));
}
bool get(int x, int y)
{
    return x & (1 << (y - 1));
}
void mx(int &x, int y, int &zx, int zy)
{
    if (x < y)
    {
        x = y;
        zx = zy;
    }
    else if (x == y)
    {
        zx += zy;
    }
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> q;
    while (q--)
    {
        cin >> n >> m;
        init();
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
            f[i][i][1 << (i - 1)] = a[i];
            g[i][i][1 << (i - 1)] = 1;
            v[i][i] = true;
        }
        if (n == 1)
        {
            cout << a[1] << " " << 1 << '\n';
            continue;
        }
        for (int i = 1; i <= m; i++)
        {
            int x, y;
            cin >> x >> y;
            v[x][y] = v[y][x] = true;
        }
        int full = (1 << n) - 1;
        for (int i = 1; i <= full; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (get(i, j))
                {
                    int man = i ^ (1 << (j - 1));
                    for (int k = 1; k <= n; k++)
                    {
                        if (get(man, k) && v[j][k])
                        {
                            for (int l = 1; l <= n; l++)
                            {
                                if (get(man, l) && f[k][l][man])
                                {
                                    int sum = a[j] + a[k] * a[j];
                                    if (v[l][j] && l != k)
                                    {
                                        sum += a[k] * a[j] * a[l];
                                    }
                                    mx(f[j][k][i], f[k][l][man] + sum, g[j][k][i], g[k][l][man]);
                                }
                            }
                        }
                    }
                }
            }
        }
        int ansa = 0, ansb = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                mx(ansa, f[i][j][full], ansb, g[i][j][full]);
            }
        }
        cout << ansa << " " << ansb / 2 << '\n';
    }
    return 0;
}
```

---

## 作者：lyas145 (赞：0)

题目在[这里](https://www.luogu.com.cn/problem/P10963)。

## 解题思路

$\sum n\le 13$，很明显：这是道**状态压缩 dp** 题。

本题解将会把*最佳三角形哈密顿路径*简说成*路径*。

先考虑怎么求出路径的最大值。

设 $f_{i,S}$ 表示目前路径最后一个岛的编号是 $i$ 且路径上岛的集合为 $S$ 时路径的最大值。

但是由于路径的值还有可能加上 $V_i\times V_{i+1}\times V_{i+2}$。

因此每当一个新经过的岛加入路径时（假设这是路径的第 $i$ 个岛），路径新加的值可能会牵扯到 $C_{i-2}$。

于是加入新状态：目前路径倒数第二个岛的编号。

于是 $f_{i,S}$ 变成了 $f_{i,j,S}$，$f_{i,j,S}$ 表示目前路径最后一个岛的编号是 $i$、倒数第二个岛的编号是 $j$ 且路径上岛的集合为 $S$ 时路径的最大值。

我认为本题用**邻接矩阵**存图或许会方便一点。设邻接矩阵数组为 $dis_{i,j}$，当 $dis_{i,j}=1$ 时，表示岛 $i$ 与岛 $j$ 之间有一座直接相连的桥，否则没有直接相连的桥。

转移方程也不难想，为：

$$f_{i,j,S}=\max\limits_{dis_{i,j}=1,dis_{j,k}=1}(\{f_{j,k,S\oplus2^{i-1}}+V_i+V_i\times V_j+
\begin{cases}
V_i\times V_j\times V_k & dis_{i,k}=1\\
0 & dis_{i,k}=0
\end{cases}\})
$$

方案数自然也好求了，设为 $g_{i,j,S}$，其含义与 $f_{i,j,S}$ 相似，只是 $g_{i,j,S}$ 的值是路径的值为 $f_{i,j,S}$ 时的方案数，转移方程为：

$$g_{i,j,S}=
\begin{cases}
g_{j,k,S\oplus2^{i-1}} & f_{i,j,S}<f_{j,k,S\oplus 2^{i-1}}+t\\
g_{i,j,S}+g_{j,k,S\oplus2^{i-1}} & f_{i,j,S}=f_{j,k,S\oplus 2^{i-1}}+t\\
g_{i,j,S} & f_{i,j,S}>f_{j,k,S\oplus 2^{i-1}}+t
\end{cases}
$$

其中 $t$ 表示 $f_{j,k,S\oplus 2^{i-1}}$ 转移到 $f_{i,j,S}$ 时所加的值。

初始化也能想到吧？为：

$$f_{i,j,2^{i-1}|2^{j-1}}=V_i+V_j+V_i\times V_j,g_{i,j,2^{i-1}|2^{j-1}}=1$$

要注意一下**是否能够转移过来**（[不然……](https://www.luogu.com.cn/record/202193345)），在这里给出一个判断方法：若 $g_{j,k,S\oplus2^{2^{i-1}}}$ 不为 $0$，则能转移过来，否则不能。

注意特判 $n=1$ 的情况。

~~然后你兴高采烈地写完了代码结果样例都没过。~~

题目原话：“注意：如果一条路径的顺序反转，仍认为它是相同的路径。”

对于一条路径，她的顺序对她的值是**没有影响的**，原因很简单：她的顺序对她的值的累加是**没有影响的**。所以这条路径我们会在方案数中把她加重，共收尾两次，除以 $2$ 就 OK 了。

## 码儿

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=15,M=1<<13,INF=0x3f3f3f3f;
int T,n,m;
ll an1,an2;
ll a[N];
bool dis[N][N];
ll f[N][N][M],g[N][N][M];
inline int read() {
	int x=0,f=1;
	char c=getchar();
	while (!isdigit(c)) {f=(c=='-'?-1:1);c=getchar();}
	while (isdigit(c)) {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int main() {
	T=read();
	while (T--) {
		memset(dis,0,sizeof dis);
		memset(f,0,sizeof f);
		memset(g,0,sizeof g);
		an1=an2=0;
		n=read();m=read();
		for (int i=1;i<=n;i++) {a[i]=read();}
		while (m--) {
			int a=read(),b=read();
			dis[a][b]=dis[b][a]=1;
		}
		if (n==1) {printf("%lld 1\n",a[1]);continue;}
		//对 n=1 的情况进行特判。
		for (int i=1;i<=n;i++) {       //初始化。
			for (int j=1;j<=n;j++) {
				if (i==j || !dis[i][j]) {continue;}
				f[i][j][(1<<i-1)|(1<<j-1)]=a[i]+a[j]+a[i]*a[j];
				g[i][j][(1<<i-1)|(1<<j-1)]=1;
			}
		}
		for (int i=0;i<1<<n;i++) {     //开始 dp！
			for (int j=1;j<=n;j++) {
				if (!(i>>j-1&1)) {continue;}
				for (int k=1;k<=n;k++) {
					if (!(i>>k-1&1)) {continue;}
					if (j==k || !dis[j][k]) {continue;}
					for (int l=1;l<=n;l++) {
						if (!(i>>l-1&1)) {continue;}
						if (j==l || k==l || !dis[k][l] || !g[k][l][i^(1<<j-1)]) {continue;}
						//!g[k][l][i^(1<<j-1)] 表示不能转移过来，直接 continue 掉。
						ll &v=f[j][k][i],&w=g[j][k][i];
						ll t=f[k][l][i^(1<<j-1)]+a[j]+a[j]*a[k]+(!!dis[l][j])*a[j]*a[k]*a[l];
						if (v==t) {w+=g[k][l][i^(1<<j-1)];}
						else if (v<t) {v=t;w=g[k][l][i^(1<<j-1)];}
					}
				}
			}
		}
		for (int i=1;i<=n;i++) {       //统计答案。
			for (int j=1;j<=n;j++) {
				if (i==j || !dis[i][j] || !g[i][j][(1<<n)-1]) {continue;}
				ll t=f[i][j][(1<<n)-1];
				if (an1==t) {an2+=g[i][j][(1<<n)-1];}
				else if (an1<t) {an1=t;an2=g[i][j][(1<<n)-1];}
			}
		}
		printf("%lld %lld\n",an1,an2>>1);  //方案数除以 2，排除掉计算重复的路径。
	}
	return 0;      //完美结束。
}
```

Thanks for reading！

---

## 作者：mirance2025 (赞：0)

## Solution
线形状态压缩 DP。
时间复杂度 $O(2^n \times n^3)$。

$n \leq 13$，可以直接状态压缩。

转移时每次线性向集合添加一个点，而不是向集合中添加一个集合，区间 dp 空间不够，然后是要考虑相邻三个点，故定义状态 $f_{s, i, j}$ 表示的意思是：

在第 $s$ 个集合中，倒数第二个点是 $i$，最后一个点是 $j$。
转移方程为：$f_{s, i, j} = \max (f_{s ^ {1 << k}, k, i} + d_{i, j} + g_{i, j, k})$。

$d_{i, j}$ 为预处理的 $dis(i, j)$，无边为 $0$。

$g_{i, j, k}$ 为预处理的三点权值，不成环为 $0$。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 15;
int f[1<<N][N][N],g[1<<N][N][N];
int w[N],a[N][N];
int n,m;

int main(){
    int q;
    cin >> q;
    while(q--,cin>>n>>m){
        memset(f,0,sizeof(f));
        memset(g,0,sizeof(g));
        memset(a,0,sizeof(a));
        int ans = 0,res = 0,sum = 0;
        for(int k=0;k<n;k++){
            scanf("%d",w+k);
            sum += w[k];
        }
        for(int k=1;k<=m;k++){
            int u,v;
            scanf("%d%d",&u,&v);
            u--,v--;
            a[u][v] = a[v][u] = 1;
        }
        for(int k=0;k<n;k++)
            for(int j=0;j<n;j++)
                if(a[k][j]){
                    f[1<<k|1<<j][k][j] = w[k]*w[j];
                    g[1<<k|1<<j][k][j] = 1;

                }
        for(int c=0;c<(1<<n);c++)
            for(int k=0;k<n;k++)
                if((c>>k)&1)
                    for(int j=0;j<n;j++) 
                        if(c>>j&1)
                            if(a[k][j]&&f[c][k][j])
                                for(int i=0;i<n;i++) 
                                    if(a[j][i]&&!((c>>i)&1)){
                                        int pre = f[c][k][j]+w[i]*w[j];
                                        if(a[k][i])
                                            pre += w[k]*w[j]*w[i];
                                        if(f[c|1<<i][j][i]<pre){
                                            f[c|1<<i][j][i] = pre;
                                            g[c|1<<i][j][i] = g[c][k][j];
                                        }
                                        else if(f[c|1<<i][j][i]==pre)
                                            g[c|1<<i][j][i] += g[c][k][j];
                                    }
        int tmp = (1<<n)-1;
        for(int k=0;k<n;k++)
            for(int j=0;j<n;j++)
                if(a[k][j]){
                    if(f[tmp][k][j]>ans){
                        ans = f[tmp][k][j];
                        res = g[tmp][k][j];
                    }
                    else if(f[tmp][k][j]==ans)
                        res += g[tmp][k][j];
                }
        printf("%d %d\n",ans+(ans>0)*sum,res>>1);
    }
    return 0;
}
```

---

