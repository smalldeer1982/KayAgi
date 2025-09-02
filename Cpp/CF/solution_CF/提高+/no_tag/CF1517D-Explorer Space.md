# Explorer Space

## 题目描述

You are wandering in the explorer space of the 2050 Conference.

The explorer space can be viewed as an undirected weighted grid graph with size $ n\times m $ . The set of vertices is $ \{(i, j)|1\le i\le n, 1\le j\le m\} $ . Two vertices $ (i_1,j_1) $ and $ (i_2, j_2) $ are connected by an edge if and only if $ |i_1-i_2|+|j_1-j_2|=1 $ .

At each step, you can walk to any vertex connected by an edge with your current vertex. On each edge, there are some number of exhibits. Since you already know all the exhibits, whenever you go through an edge containing $ x $ exhibits, your boredness increases by $ x $ .

For each starting vertex $ (i, j) $ , please answer the following question: What is the minimum possible boredness if you walk from $ (i, j) $ and go back to it after exactly $ k $ steps?

You can use any edge for multiple times but the boredness on those edges are also counted for multiple times. At each step, you cannot stay on your current vertex. You also cannot change direction while going through an edge. Before going back to your starting vertex $ (i, j) $ after $ k $ steps, you can visit $ (i, j) $ (or not) freely.

## 说明/提示

In the first example, the answer is always $ 10 $ no matter how you walk.

In the second example, $ answer_{21} = 10 $ , the path is $ (2,1) \to (1,1) \to (1,2) \to (2,2) \to (2,1) $ , the boredness is $ 4 + 1 + 2 + 3 = 10 $ .

## 样例 #1

### 输入

```
3 3 10
1 1
1 1
1 1
1 1 1
1 1 1```

### 输出

```
10 10 10
10 10 10
10 10 10```

## 样例 #2

### 输入

```
2 2 4
1
3
4 2```

### 输出

```
4 4
10 6```

## 样例 #3

### 输入

```
2 2 3
1
2
3 4```

### 输出

```
-1 -1
-1 -1```

# 题解

## 作者：BorisDimitri (赞：10)

# 题意

给出一个 $n \times m$ 的矩阵，这个图是 [**四联通**](https://blog.csdn.net/qq_38619342/article/details/86510602) 的。

而且每个位置可以 **重复走** 且可以取得一样的值。

求在走了 $k$ 步后能否回到原点，如果不能输出 $-1$ ，否则输出取得的最小值。

# 分析
1. **不能回到原点** 的情况。
>显然，当且仅当 $k$ 为偶数时，走了 $k$ 步后一定可以回到原点。
>
>反之，当 $k$ 为奇数时，则不可能回到原点 (直接输出 $-1$ 矩阵)。

2. **可以回到原点** 的情况。 (**重点！！！**)

> - 由于走出 $k$ 步之后要回到原点，所以只能向外走 $\frac{k}{2}$ 步。
>
> - 由于要求的是最小取值，且每个位置可以多次经过，所以走 **过来** 和走 **回去** 的路径是一样的。

**于是，我们便将问题转化为了 : 从原点向外走 $\frac{k}{2}$ 的最小取值。**

这个明显可以采用 `DP` 来做。

设 $f[i][j][d]$ 为从 $(i,j)$ 点出发，走了 $d$ 步时的最小取值。

设 $(x_i,y_i)$ 为与 $(i,j)$ 相连的点，与点 $(i,j)$ 相连的数有 $m$个 。

则有 : $f[i][j][d]$ = $\min_{1}^{m} (f[x][y][d-1])$

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 505;
const int INF = 0x3f3f3f3f;

int dedge[N][N];
int redge[N][N];
int ans[N][N];

int f[N][N][30];//编号为i,j的点在第d步被经过的花费

int n,m; // 图的大小为n*m
int k; // 共走k步

int main()
{
	scanf("%d%d%d",&n,&m,&k);

	for(int i=1; i<=n; i++)
		for(int j=1; j<=m-1; j++)
			scanf("%d",&redge[i][j]);

	for(int i=1; i<=n-1; i++)
		for(int j=1; j<=m; j++)
			scanf("%d",&dedge[i][j]);

	//INPUT

	if(k & 1)   //如果k为奇数
	{
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++)
				printf("-1 ");
		printf("\n");
		return 0;
	}

	for(int d = 1; d<=(k>>1); d++) // k<<1等价于k/2 
		for(int i=1; i<=n; i++)
			for(int j=1; j<=m; j++)
			{
				f[i][j][d] = INF;
				if(j > 1) f[i][j][d] = min(f[i][j][d], f[i][j-1][d-1] + redge[i][j-1]);
                if(j < m) f[i][j][d] = min(f[i][j][d], f[i][j+1][d-1] + redge[i][j]);
                if(i > 1) f[i][j][d] = min(f[i][j][d], f[i-1][j][d-1] + dedge[i-1][j]);
                if(i < n) f[i][j][d] = min(f[i][j][d], f[i+1][j][d-1] + dedge[i][j]);
			}
	
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
			printf("%d ",f[i][j][k>>1] * 2);
		printf("\n");
	}
		
	return 0;
	
}
```

---

## 作者：littlebug (赞：1)

## Solution

- 注意到若 $k$ 为奇数则一定无解，否则一定有解。

- 注意到一条路可以重复走，所以沿某一条路走一个来回一定是最优的，于是问题就转化成了对于每一个 $(i,j)$，从这个格子开始走 $\frac k 2$ 步的最短路径。

- 注意到 $k$ 很小，只有 $20$，于是考虑直接 dp。

- 很自然地可以想到设 $f_{k',i,j}$ 为从 $(i,j)$ 开始走 $k'$ 格的答案。转移考虑分讨四个方向取 $\min$ 即可。

- 复杂度 $O(nmk)$，还有一个常数 $4$，可过。

## Code

```cpp
int n,m,K,f[11][MAXN][MAXN],a[MAXN][MAXN],b[MAXN][MAXN];

signed main()
{
	read(n,m,K);
	if(K&1)
	{
		rep(i,1,n) {rep(j,1,m) write(-1ll,' '); write('\n');}
		return fast_io::ot(),0;
	}
	
	_::r(a,n,m-1),_::r(b,n-1,m);
	
	memset(f,0x3f,sizeof(f)),memset(f[0],0,sizeof(f[0]));
	int x,y,now;
	rep(k,1,K>>1) rep(i,1,n) rep(j,1,m) rep(kk,1,4)
	{
		x=i+dx[kk],y=j+dy[kk];
		if(x<1 || x>n || y<1 || y>m) continue;
		
		now=f[k-1][x][y];
		switch(kk)
		{
			case 1: now+=a[i][j]; break;
			case 2: now+=b[i][j]; break;
			case 3: now+=a[i][j-1]; break;
			case 4: now+=b[i-1][j]; break;
		}
		
		f[k][i][j]=min(f[k][i][j],now);
	}
	
	rep(i,1,n) {rep(j,1,m) write(f[K>>1][i][j]<<1,' '); write('\n');}
	
	return 0;
}
```

---

华风夏韵，洛水天依！

---

## 作者：Engulf (赞：1)

当 $k$ 是奇数时，显然无法走一圈回来。

注意一下，**路径是可以重复的**。也就是说，最优的情况一定是往外走 $\dfrac{k}{2}$ 次的最小权值，然后再原路返回。

这样一来，每次的行走都只和上一次有关，可以使用动态规划求解。

设 $f_{i, j, s}$ 表示 $s$ 步走到格子 $(i, j)$ 的最小步数。

然后就可以从上一步（$s - 1$）转移过来了。

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

const int inf = 0x3f3f3f3f;
const LL infLL = 0x3f3f3f3f3f3f3f3fLL;

const int N = 505;
int n, m, k;
int rght[N][N];
int down[N][N];
int f[N][N][25];

int main()
{
	scanf("%d%d%d", &n, &m, &k);
	if (k & 1)
	{
		for (int i = 1; i <= n; i ++ , puts(""))
			for (int j = 1; j <= m; j ++ )
				printf("-1 ");
		return 0;
	}
	memset(f, 0x3f, sizeof f);
	for (int i = 1; i <= n; i ++ )
		for (int j = 1; j <= m; j ++ )
			f[i][j][0] = 0;
	for (int i = 1; i <= n; i ++ )
		for (int j = 1; j < m; j ++ )
			scanf("%d", &rght[i][j]);
	for (int i = 1; i < n; i ++ )
		for (int j = 1; j <= m; j ++ )
			scanf("%d", &down[i][j]);
	for (int s = 1; s <= k / 2; s ++ )
		for (int i = 1; i <= n; i ++ )
			for (int j = 1; j <= m; j ++ )
			{
				f[i][j][s] = min(f[i][j][s], f[i - 1][j][s - 1] + down[i - 1][j]);
				f[i][j][s] = min(f[i][j][s], f[i + 1][j][s - 1] + down[i][j]);
				f[i][j][s] = min(f[i][j][s], f[i][j - 1][s - 1] + rght[i][j - 1]);
				f[i][j][s] = min(f[i][j][s], f[i][j + 1][s - 1] + rght[i][j]);
			}
	for (int i = 1; i <= n; i ++ , puts(""))
		for (int j = 1; j <= m; j ++ )
			printf("%d ", f[i][j][k / 2] * 2);
	return 0;
}
```

---

## 作者：Ryo_Yamada (赞：1)

首先，当 $k$ 为奇数时显然走不回去。 

对于 $k$ 为偶数时，考虑将路程分为两个 $\dfrac{k}{2}$ 步的路径，一次从 $(i,\,j)$ 到 $(x,\,y)$，一次从 $(x,\,y)$ 回到 $(i,\,j)$。

首先是结论：最优情况是由原点走 $\dfrac{k}{2}$ 步的路径长度最小值 $\times 2$。也就是由原点走 $\dfrac{k}{2}$ 步之后按原路走回原点。

如何证明呢？可以假设最优情况是由两条不同路径组成：如果这两个路径的长度不同（如果路径不同但是长度相同也是最优的），由于边是双向的，我们显然可以取其中较短的路径，然后将每次走的路反转方向，组成的路径替换较长的那条路径，这样是最优的。

例如：$(1,\,1) \to (1,\,2) \to (2,\,2) \to (2,\,3)$ 反转后变为 $(2,\,3) \to (2,\,2) \to (1,\,2) \to (1,\,1)$。

考虑使用 $\text{dp}$ 求出这个最优答案。可以直接暴力 $\text{dp}$：$dp_{i,j,k}$ 表示从 $(i,\,j)$ 走 $k$ 步的最小路径长度。暴力从四个方向转移即可。

时间复杂度 $O(nmk)$。

$\text{Code}$：

```cpp
int n, m, k;
int dp[505][505][11];
int x[505][505], y[505][505];
 
int main() {
	qread(n, m, k);
	if(k & 1) {
		rep(i, 1, n) {
			rep(j, 1, m) printf("-1 ");
			puts("");
		}
		return 0;
	}
	k /= 2;
	memset(dp, 0x3f, sizeof dp);
	rep(i, 1, n) rep(j, 1, m - 1) qread(x[i][j]);
	rep(i, 1, n - 1) rep(j, 1, m) qread(y[i][j]);
	rep(i, 1, n) rep(j, 1, m) dp[i][j][0] = 0;
	rep(K, 1, k) {
		rep(i, 1, n) rep(j, 1, m) {
			if(i != 1) To_min(dp[i][j][K], dp[i - 1][j][K - 1] + y[i - 1][j]);
			if(i != n) To_min(dp[i][j][K], dp[i + 1][j][K - 1] + y[i][j]);
			if(j != 1) To_min(dp[i][j][K], dp[i][j - 1][K - 1] + x[i][j - 1]);
			if(j != m) To_min(dp[i][j][K], dp[i][j + 1][K - 1] + x[i][j]);
		}
	}
	rep(i, 1, n) {
		rep(j, 1, m) {
			printf("%d ", dp[i][j][k] * 2);
		}
		puts("");
	}
 	return 0;
}
```


---

## 作者：_Lazy_whr_ (赞：0)

显而易见的 DP。

令 $dp_{i, j, d}$ 代表起点为 $(i, j)$，最多走了 $d$ 步的最小取值。

此时，设于与 $(i, j)$ 相连的有 $c$ 个，为 $(x_t, y_t)$ 那么容易得到：
$$dp_{i, j, d} = min_{i = 1} ^ {m} {dp_{x_t, y_t, d - 1}}$$

[AC Link](https://codeforces.com/problemset/submission/1517/308276568)。

---

## 作者：LouYiYang1 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1517D)

因为把路线一定可以转化成长方形，而长方形的边长一定是偶数，若 $k$ 是偶数，发现若走 $\displaystyle \frac{k}{2}$ 步时最优的，则剩下的 $\displaystyle \frac{k}{2}$ 步肯定会选择原路返回，因为这样返回的路程也是最优的。所以问题转化成了在这个点**走 $\displaystyle \frac{k}{2}$ 步最优需要的代价**。所以我们用动态规划来做，用 $dp_{i,j,k}$ 表示此点走 $k$ 步最少代价，答案不要忘记翻倍，因为还有返回的代价。
## AC Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,g,dp[505][505][25],r[505][505],d[505][505];
int main(){
	ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	memset(dp,1e9+7,sizeof dp);
	cin>>n>>m>>g;
	if(g%2==1){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cout<<"-1 ";
			}
			cout<<"\n";
		}return 0;
	}
	for(int i=1;i<=n;i++) for(int j=1;j<m;j++) cin>>r[i][j];
	for(int i=1;i<n;i++) for(int j=1;j<=m;j++) cin>>d[i][j];
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) dp[i][j][0]=0;
	for(int k=1;k<=g/2;k++){
//		cout<<k<<":\n";
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(i>1) dp[i][j][k]=min(dp[i][j][k],dp[i-1][j][k-1]+d[i-1][j]);
				if(i<n) dp[i][j][k]=min(dp[i][j][k],dp[i+1][j][k-1]+d[i][j]);
				if(j>1) dp[i][j][k]=min(dp[i][j][k],dp[i][j-1][k-1]+r[i][j-1]);
				if(j<m) dp[i][j][k]=min(dp[i][j][k],dp[i][j+1][k-1]+r[i][j]);
//				cout<<dp[i][j][k]<<" ";
			}
//			cout<<"\n";
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cout<<dp[i][j][g/2]*2<<" ";
		}
		cout<<"\n";
	}
	return 0;
}

```

---

## 作者：_H17_ (赞：0)

## 题目分析

考虑走 $k$ 步回到本身的最短路，“回到本身”这个东西很恶心，不过既然要求最短，肯定走出去一个最短的之后原路走回来，所以问题变成了每个点走 $\frac{k}{2}$ 步的最短路径，可以通过 DP 求解。

奇数的情况显然没法回去，即无解。

DP 怎么做？考虑 $f_{i,j,k}$ 表示位置 $(i,j)$ 走了 $k$ 步的最短路，从 $k-1$ 步四个方向转移即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,m,k,f[501][501][11],u[501][501],d[501][501],l[501][501],r[501][501],ans=0x3f3f3f3f3f3f3f3fll;
bool check(int x,int y,int step){
    return 1<=x&&x<=n&&1<=y&&y<=m&&f[x][y][step-1]!=0x3f3f3f3f3f3f3f3fll;
}
signed main(){
    memset(u,-1,sizeof(u)),
    memset(d,-1,sizeof(d)),
    memset(l,-1,sizeof(l)),
    memset(r,-1,sizeof(r));
    memset(f,0x3f,sizeof(f));
    cin>>n>>m>>k;
    if(k&1){
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                cout<<"-1"<<" \n"[j==m];
        return 0;
    }
    k/=2;
    for(int i=1,k;i<=n;i++)
        for(int j=1;j<m;j++){
            cin>>k;
            r[i][j]=l[i][j+1]=k;
        }
    for(int i=1,k;i<n;i++)
        for(int j=1;j<=m;j++){
            cin>>k;
            d[i][j]=u[i+1][j]=k;
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            f[i][j][0]=0;
    for(int s=1;s<=k;s++){
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++){
                if(check(i-1,j,s))
                    f[i][j][s]=min(f[i][j][s],f[i-1][j][s-1]+u[i][j]);
                if(check(i+1,j,s))
                    f[i][j][s]=min(f[i][j][s],f[i+1][j][s-1]+d[i][j]);
                if(check(i,j-1,s))
                    f[i][j][s]=min(f[i][j][s],f[i][j-1][s-1]+l[i][j]);
                if(check(i,j+1,s))
                    f[i][j][s]=min(f[i][j][s],f[i][j+1][s-1]+r[i][j]);
            }
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cout<<f[i][j][k]*2<<" \n"[j==m];
    return 0;
}
```

---

## 作者：Lcm_simida (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1517D)

分类：

1. 若 $k$ 是奇数，则不可能从原点绕回至原点，因为把路线一定可以转化成长方形，而长方形的边长一定是偶数
2. 若 $k$ 是偶数，发现若走 $\displaystyle \frac{k}{2}$ 步时最优的，则剩下的 $\displaystyle \frac{k}{2}$ 步肯定会选择原路返回，因为这样返回的路程也是最优的。所以问题转化成了在这个点**走 $\displaystyle \frac{k}{2}$ 步最优需要的代价**。所以我们用动态规划来做，用 $dp_{i,j,k}$ 表示此点走 $k$ 步最少代价，答案不要忘记翻倍，因为还有返回的代价
## AC Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,g,dp[505][505][25],r[505][505],d[505][505];
int main(){
	ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	memset(dp,1e9+7,sizeof dp);
	cin>>n>>m>>g;
	if(g%2==1){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cout<<"-1 ";
			}
			cout<<"\n";
		}return 0;
	}
	for(int i=1;i<=n;i++) for(int j=1;j<m;j++) cin>>r[i][j];
	for(int i=1;i<n;i++) for(int j=1;j<=m;j++) cin>>d[i][j];
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) dp[i][j][0]=0;
	for(int k=1;k<=g/2;k++){
//		cout<<k<<":\n";
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(i>1) dp[i][j][k]=min(dp[i][j][k],dp[i-1][j][k-1]+d[i-1][j]);
				if(i<n) dp[i][j][k]=min(dp[i][j][k],dp[i+1][j][k-1]+d[i][j]);
				if(j>1) dp[i][j][k]=min(dp[i][j][k],dp[i][j-1][k-1]+r[i][j-1]);
				if(j<m) dp[i][j][k]=min(dp[i][j][k],dp[i][j+1][k-1]+r[i][j]);
//				cout<<dp[i][j][k]<<" ";
			}
//			cout<<"\n";
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cout<<dp[i][j][g/2]*2<<" ";
		}
		cout<<"\n";
	}
	return 0;
}

```

---

## 作者：tZEROちゃん (赞：0)

显然，当 $k$ 为奇数的时候走不回去，直接全输出 $-1$。

因为是无向图，所以我们可以找到一条 $\dfrac k 2$ 的路径，沿着这条路径往返。

考虑 dp。设 $dp_{d, x, y}$ 表示从一个点 $(x, y)$ 走 $\dfrac d 2$ 步的最小值，按照题目转移即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i, l, r) for(auto i = (l); i <= (r); ++i)
#define per(i, r, l) for(auto i = (r); i >= (l); --i)
#define _rep(i, l, r) for(auto i = (l); i < (r); ++i)
#define _per(i, r, l) for(auto i = (r); i > (l); --i)
#define pb push_back

const int N = 510;
int a[N][N], b[N][N], dp[N/2][N][N];

int main() {
  int n, m, k; cin >> n >> m >> k;
  rep (i, 1, n) _rep (j, 1, m) cin >> a[i][j];
  _rep (i, 1, n) rep (j, 1, m) cin >> b[i][j];
  if (k & 1) {
    rep (i, 1, n) {
      rep (j, 1, m) printf("-1 ");
      puts("");
    } return 0;
  }
  int K = k / 2;
  rep (i, 1, K) rep (j, 1, n) rep (k, 1, m) {
    dp[i][j][k] = 0x3f3f3f3f;
    if (k > 1) dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j][k - 1] + a[j][k - 1]);
    if (k < m) dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j][k + 1] + a[j][k]);
    if (j > 1) dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j - 1][k] + b[j - 1][k]);
    if (j < n) dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j + 1][k] + b[j][k]);
  }
  rep (i, 1, n) {
    rep (j, 1, m) 
      cout << (dp[K][i][j] << 1) << ' ';
    puts("");
  }
}
```

---

## 作者：封禁用户 (赞：0)

### 显而易见的DP问题
#### 分析: 
我们先想想无解的情况:    
很明显，若 $k\bmod 2=1$ 则无解(则你不可能走回原点)，否则必然有解。    
故可以先排除无解：
```cpp
if (k&1){//位运算
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++)
			printf("-1 ");
		puts("");
	}
	return 0;
}
```
接着，我们定义DP状态 $f_{i,j,p}$ 表示从 $\text{i,j}$ 点出发，走了 p 步时的最小值。    
可得转移式：   
$f_{i,j,p} = \begin{cases}
  f_{i,j,p}=\min{f_{i,j,p},f_{i,j-1,p-1}+a_{i,j-1}} &j>1   \\
  f_{i,j,p}=\min{f_{i,j,p},f_{i,j+1,p-1}+a_{i,j}} &j<m   \\
  f_{i,j,p}=\min{f_{i,j,p},f_{i-1,j,p-1}+a_{i-1,j}} &i>1   \\
  f_{i,j,p}=\min{f_{i,j,p},f_{i+1,j,p-1}+a_{i,j}} &i<n\\
\end{cases}$     
注意初始值需赋值为一个极大值    
于是，可以放代码了!
#### AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,a[505][505],b[505][505],f[505][505][12];
int main(){
	scanf("%d%d%d",&n,&m,&k);
   if (k&1){
		for (int i=1;i<=n;i++){
			for (int j=1;j<=m;j++)
				printf("-1 ");
			puts("");
		}
		return 0;
	} for (int i=1;i<=n;i++)
		for (int j=1;j<m;j++)
			scanf("%d",&a[i][j]);
	for (int i=1;i<n;i++)
		for (int j=1;j<=m;j++)
			scanf("%d",&b[i][j]);
	for (int p=1;p<=k>>1;p++)
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++){
				f[i][j][p]=INT_MAX;
				if(j>1) f[i][j][p]=min(f[i][j][p],f[i][j-1][p-1]+a[i][j-1]);
                if(j<m) f[i][j][p]=min(f[i][j][p],f[i][j+1][p-1]+a[i][j]);
                if(i>1) f[i][j][p]=min(f[i][j][p],f[i-1][j][p-1]+b[i-1][j]);
                if(i<n) f[i][j][p]=min(f[i][j][p],f[i+1][j][p-1]+b[i][j]);
			}
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++)
			printf("%d ",f[i][j][k>>1]<<1);
		puts("");
	} return 0;
}
```

---

## 作者：Luciylove (赞：0)

- #### Solution(题面)：

给定一个 $n\times m$ 的四联通带权网格图，对于每个格点求**恰好** $k$ 步回到自身的最短路径，若无法到达，输出$-1$

$n,m\leq 500,k\leq 20$

- #### 解法 :

首先我们先有一个结论:

- $k$不是$2$的倍数时，没有解。

证明: 设 $k=2x+1$,$x$ 为整数,走了一个来回,来的步数即是 $\frac{2x+1}{2}$，因为上式为 $x+\frac{1}{2}$ ,没有 $\frac{1}{2}$ 步，所以仅当 $k$ 是 $2$ 的倍数有解。

接下来我们考虑另一个结论：

- 对于从 $(x_i,y_i)$ 开始的一个来回   (长度为$k$)，答案为从 $(x_i,y_i)$ 走出去 $k/2$ 步的最短路径 $\times2$

证明：我们设走的来回由路径 $x$ 和 $y$ 组成。若 $x<y$,则我们可以将 $x$ 反转方向，代替 $y$,取得更优秀的解。

介于题解都是空间复杂度 $O(nmk)$ 的，此处给出一篇 $O(nm)$ 的代码实现。

我们可以考虑循环 $\frac{k}{2}$ 次，每次对每个点暴力扩展求出解   $dp_{i,j,k/2}$ ,最后输出 $dp_{i,j,k/2}\times2$ 即可。

由于每一个 $dp_{i,j,k}$ 都由可转移的点 $u,v$ 的 $dp_{u,v,k-1}$ 而来，所以我们可以用 $f_{i,j}$ 来记录由上一次转移过来的这一次的值$dp_{i,j}$只记录上一次更新的值即可,转移完成后 $dp_{i,j}$ 又记录$f_{i,j}$ 的值即可。

此处参考了 [George1123](https://codeforces.com/contest/1517/submission/114001418) 的解法。

其余就是注意存图，给出一下转移方程：

### $f_{i,j}=\underset{(u,v)\in expand((i,j))}{min} {\{dp_{u,v}+val_{(u,v)\to{(i,j)}}\}}$

其中 $expand((i,j))$ 表示所有 $(u,v)$ 可以转移到 $(i,j)$。

贴个代码:
```cpp
#include <bits/stdc++.h>
#define N 505
int dp[N][N],f[N][N],n,m,k,inf=1e9;
int val[N][N],edge[N][N];
using namespace std;
void clear(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            f[i][j]=inf; //f数组初始化
        }
    }
}
void update(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            dp[i][j]=f[i][j]; //复制f数组到dp上
        }
    }
}
int main(){
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
      for(int j=1;j<=m-1;j++){
        cin>>val[i][j];
      }
    }
    for(int i=1;i<=n-1;i++){
      for(int j=1;j<=m;j++){
       cin>>edge[i][j];
      }
    }
    //输入
    if(k&1){ //没有解
      for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cout<<-1<<' ';
        }
        cout<<endl; 
      }
      return 0;
    }
    k>>=1; //求出k/2
    while(k--){ //开始求解
        clear(); //将f数组初始化
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(j>1) f[i][j]=min(f[i][j],dp[i][j-1]+val[i][j-1]);
                if(j<m) f[i][j]=min(f[i][j],dp[i][j+1]+val[i][j]);
                if(i>1) f[i][j]=min(f[i][j],dp[i-1][j]+edge[i-1][j]);
                if(i<n) f[i][j]=min(f[i][j],dp[i+1][j]+edge[i][j]);
                //转移
            }
        }
        update(); //f数组复制到dp数组上
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cout<< (dp[i][j]<<1) <<' ';
        }
        cout<<endl;
    }
    //输出
    return 0;
}
```
谢谢!



---

