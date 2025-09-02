# [JOI 2022 Final] 沙堡 2 / Sandcastle 2

## 题目描述

JOI 君在沙滩上玩耍。他建造了一座沙堡。这座由 JOI 君建造的沙堡位于沙滩上的一个矩形区域内。这个矩形区域有 $H$ 行 $W$ 列。位于从上往下的第 $i$ 行、从左往右的第 $j$ 列的格子的高度为 $A_{i, j}$。**注意所有 $\boldsymbol{A_{i, j}}$ 的值互不相同。**

在沙堡上，JOI 君执行了下列动作。

1. 首先，JOI 君选择一个格子，他从该格子开始移动。
2. 然后，他从当前格子出发朝上下左右四个方向之一移动到相邻的格子上。他必须移动到低于当前格子的格子上。他可以重复此动作零次或更多次。

最终，如果我们从上往下看，他经过的格子将形成一个矩形。

给定每个格子的高度信息 $A_{i, j}$，写一个程序计算所有可能的由 JOI 君经过的格子组成的矩形的数量。

## 说明/提示

**【样例解释 \#1】**

由于有 $10$ 个可能的由 JOI 君经过的格子组成的矩形，输出 $10$。

![](https://cdn.luogu.com.cn/upload/image_hosting/ctry6t23.png)

这个样例满足所有子任务的限制。

**【样例解释 \#2】**

由于有 $15$ 个可能的由 JOI 君经过的格子组成的矩形，输出 $15$。

![](https://cdn.luogu.com.cn/upload/image_hosting/2zaim5fy.png)

这个样例满足子任务 $2, 3, 4, 5$ 的限制。

**【样例解释 \#3】**

举个例子，如下矩形可以由 JOI 君经过的格子组成。由于总共有 $65$ 个可能的矩形，输出 $65$。

![](https://cdn.luogu.com.cn/upload/image_hosting/q6y9c6d5.png)

这个样例满足子任务 $2, 3, 4, 5$ 的限制。

----

**【数据范围】**

**本题采用捆绑测试。**

对于 $100 \%$ 的数据，$1 \le H, W, H \cdot W \le 5 \times {10}^4$，$1 \le A_{i, j} \le {10}^7$，$A_{i_1, j_1} \ne A_{i_2, j_2}$（$(i_1, j_1) \ne (i_2, j_2)$）。

- 子任务 $1$（$9$ 分）：$H = 1$。
- 子任务 $2$（$10$ 分）：$H \cdot W \le 100$。
- 子任务 $3$（$5$ 分）：$H \cdot W \le 1500$。
- 子任务 $4$（$56$ 分）：$H \cdot W \le 7000$。
- 子任务 $5$（$20$ 分）：无特殊限制。

----

**译自 [JOI 2022 Final](https://www.ioi-jp.org/joi/2021/2022-ho/index.html) T5「[砂の城 2 ](https://www.ioi-jp.org/joi/2021/2022-ho/2022-ho-t5.pdf) / [Sandcastle 2](https://www.ioi-jp.org/joi/2021/2022-ho/2022-ho-t5-en.pdf)」**

## 样例 #1

### 输入

```
1 5
2 4 7 1 5
```

### 输出

```
10
```

## 样例 #2

### 输入

```
3 2
18 10
19 12
17 13
```

### 输出

```
15
```

## 样例 #3

### 输入

```
3 5
83 47 36 38 40
13 10 26 68 67
15 19 20 70 90
```

### 输出

```
65
```

# 题解

## 作者：dead_X (赞：6)

## 思路
勾吧题，[狗](https://www.luogu.com.cn/user/111055)都不[写](https://www.luogu.com.cn/record/71553571)。

首先如果给定矩形，我们肯定从最大的数开始走，然后每次在能走的格子里挑一个最大的。

这样可以判定一个矩形是否合法，具体地，矩形合法当且仅当只有一个点没有入度。

于是我们可以分 $25$ 类来判断，如下图：

![joi2022finalt5.png](https://s2.loli.net/2022/03/16/64HnVLfEFcPBlmb.png)

于是我们就可以用 $25$ 次二维前缀和来求一个矩形的答案了，时间复杂度 $O(n^2m^2)$，常数巨大。

然后看到网格题枚举子矩形套路地想到优化成 $O(n^2m)=O(S\sqrt S)$。

首先大力枚举行的两个端点，然后考虑快速统计列。

对于长度小于 $4$ 的子矩阵，我们仍然暴力解决。

对于长度大于等于 $4$ 的子矩阵，此时我们只需要将贡献拆成右端点有关和左端点有关的部分就可以前缀和优化了。

直接开桶记录左端点贡献为 $x$ 的端点数量，然后扫到一个贡献为 $y$ 的右端点时，将贡献为 $y-1$ 的左端点数量加入答案即可。

实现上，因为预处理是 $O(S)$ 的，可以把所有 $81$ 种情况全处理出来，实现可以枚举上下左右分别有 $0\sim 2$ 格后计算是否存在入度。
## 代码
虽然看着很长，但是只有 3KB？

```cpp
// Problem: P8164 [JOI 2022 Final] 沙堡 2 (Sandcastle 2)
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8164
// Memory Limit: 1096 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//And in that light,I find deliverance.
#include<bits/stdc++.h>
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
using namespace std;
#define ll long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
vector<int> a[233],f[81][233];
int g[9][50003],vis[100003];
inline int check(int u,int d,int l,int r,int x,int y)
{
	if(!(u<=x&&x<=d&&l<=y&&y<=r)) return 0;
	int res=0;
	if(u<x&&a[x-1][y]<a[x][y]) res=max(res,a[x-1][y]);
	if(x<d&&a[x+1][y]<a[x][y]) res=max(res,a[x+1][y]);
	if(l<y&&a[x][y-1]<a[x][y]) res=max(res,a[x][y-1]);
	if(y<r&&a[x][y+1]<a[x][y]) res=max(res,a[x][y+1]);
	return res;
}
inline bool calc(int u,int d,int l,int r,int x,int y)
{
	return 
		check(u,d,l,r,x-1,y)==a[x][y]||
		check(u,d,l,r,x+1,y)==a[x][y]||
		check(u,d,l,r,x,y-1)==a[x][y]||
		check(u,d,l,r,x,y+1)==a[x][y];
}
signed main()
{
	int n=read(),m=read();
	ll ans=0;
	if(n>m) 
	{
		swap(n,m);
		for(int i=1; i<=n; ++i)
			a[i].resize(m+3);
		for(int i=1; i<=m; ++i)
			for(int j=1; j<=n; ++j)
				a[j][i]=read();
	}
	else
	{
		for(int i=1; i<=n; ++i)
			a[i].resize(m+3);
		for(int i=1; i<=n; ++i)
			for(int j=1; j<=m; ++j)
				a[i][j]=read();
	}
	for(int i=0; i<81; ++i)
		for(int j=1; j<=n; ++j)
			f[i][j].resize(m+3);
	for(int L=0; L<3; ++L)
		for(int R=0; R<3; ++R)
			for(int U=0; U<3; ++U)
				for(int D=0; D<3; ++D)
					for(int i=U+1; i+D<=n; ++i)
						for(int j=L+1; j+R<=m; ++j)
							f[U*27+D*9+L*3+R][i][j]=
								!calc(i-U,i+D,j-L,j+R,i,j);
	for(int d=72; d<81; ++d)
		for(int i=2; i<=n; ++i)
			for(int j=1; j<=m; ++j)
				f[d][i][j]+=f[d][i-1][j];
	for(int l=1; l<=n; ++l)
		for(int r=l; r<=n; ++r)
		{
			for(int d=0; d<9; ++d)
				for(int i=1; i<=m; ++i) 
					g[d][i]=0;
			if(r-l<4)
				for(int d=0; d<9; ++d)
					for(int i=1; i<=m; ++i)
						for(int j=l; j<=r; ++j)
						 g[d][i]+=f[min(j-l,2)*27+min(r-j,2)*9+d][j][i];
			else
				for(int d=0; d<9; ++d)
					for(int i=1; i<=m; ++i)
						g[d][i]=
							f[0*27+2*9+d][l][i]
							+f[1*27+2*9+d][l+1][i]
							+f[2*27+2*9+d][r-2][i]
							-f[2*27+2*9+d][l+1][i]
							+f[2*27+1*9+d][r-1][i]
							+f[2*27+0*9+d][r][i];
			for(int i=1; i<=m; ++i)
				for(int j=i; j<=i+2&&j<=m; ++j)
				{
					int s=0;
					for(int k=i; k<=j; ++k)
						s+=g[min(k-i,2)*3+min(j-k,2)][k];
					ans+=(s==1);
				}
			for(int i=1; i<=m; ++i) g[8][i]+=g[8][i-1];
			for(int i=2; i+2<=m; ++i)
				++vis[50001+g[8][i]-g[5][i]-g[2][i-1]],
				ans+=vis[50000+g[8][i]+g[7][i+1]+g[6][i+2]];
			for(int i=2; i+2<=m; ++i) 
				--vis[50001+g[8][i]-g[5][i]-g[2][i-1]];
		}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Loser_King (赞：4)

~~能不写成答辩题的题就不要用答辩做法！！1~~

---

想起来补了 z 宝模拟赛，JOI22 本选去掉第一题组成提高组模拟赛（

官方题解里有个特别抽象的图，实际上感觉不用那么多 case 啊。

intro：小课题 1 扫过去，找大于小于号连续段。小课题 2 枚举矩形按值排序，观察在值上相邻的格子在原位置上是否相邻。

---

同样考虑走的路径，发现在走链的路径的过程中，恰好有一个点没有入度，一个点没有出度，其他点都是出度为一，入度为一，这个和官方题解是一样的。

而且在确定了当前矩形边界的情况下，可以发现它只可能走四周比它小的最大格子，这个可以通过小课题 2 的暴力 $O(n^2m^2\log(nm))$ 做法得出。

有了上面两个结论以后，在确定了当前矩形边界的情况下，我们把一个格子 $(i,j)$ 的权 $v_{i,j}$ 定义为：

记 $l$ 表示 $(i,j)$ 四周比 $A_{i,j}$ 小的最大值（没有就记为 $0$），$r$ 为 $(i,j)$ 四周比这个格子权大的最小值（没有就记为 $X$，表示一个充分大的值），那么 $v_{i,j}=\operatorname{R}(r<X,A_{i,j},X)-l$。其中 $\operatorname{R}(P,x,y)$ 表示条件 $P$ 为真时值为 $x$，否则为 $y$。

根据上面的结论，一条合法路径上所有格子的权值和应该是 $X$。（在链上的非端点都抵掉了，链尾剩下个 $0$，链头贡献 $X$）

后面就是转棋盘，枚举上下行的范围，然后扫过去，问题变成了满足左右列之间格子权值和为 $X$ 的对数，这个可以差分后 $O(m\log m)$ 解决。

剩下的部分是枚举长或宽为一的矩阵，这个在小课题 1 里已经解决。

总时间复杂度 $O((nm)^{1.5}\log m)$。

求 $v_{i,j}$ 的时候需要做五次前缀和，枚举左右列的时候根据靠边情况权值需要拆成六部分，别的应该没什么难写的。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int const N=400010,X=500000000000ll,dx[]={0,-1,1,0},dy[]={-1,0,0,1};
int n,m,ans;
vector<vector<int> >a,l,r,u,d,s;
void init(vector<vector<int> >&a){
	a.resize(n+2);
	for(int i=0;i<=n+1;i++)
		a[i].resize(m+2);
}
int calc(int x,int y,int s){
	int l=0,r=X;
	for(int i=0;i<4;i++)
		if(s>>i&1){
			int tx=x+dx[i],ty=y+dy[i];
			if(tx<1||ty<1||tx>n||ty>m)
				continue;
			if(a[tx][ty]>a[x][y])
				r=min(r,a[tx][ty]);
			else l=max(l,a[tx][ty]);
		}
	return(r<X?a[x][y]:X)-l;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>m,ans=n*m;
	if(n>m){
		swap(n,m),init(a);
		for(int j=1;j<=m;j++)
			for(int i=1;i<=n;i++)
				cin>>a[i][j];
	}else{
		init(a);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				cin>>a[i][j];
	}
	init(l),init(r),init(u),init(d),init(s);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			l[i][j]=l[i-1][j]+calc(i,j,14),
			r[i][j]=r[i-1][j]+calc(i,j,7),
			u[i][j]=u[i][j-1]+calc(i,j,13),
			d[i][j]=d[i][j-1]+calc(i,j,11),
			s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+calc(i,j,15);
	for(int pl=1;pl<=n;pl++)
		for(int pr=pl+1;pr<=n;pr++){
			map<int,int>f;
			for(int i=1;i<=m;i++){
				ans+=f[X-r[pr-1][i]+r[pl][i]-u[pl][i-1]-d[pr][i-1]-s[pr-1][i-1]+s[pl][i-1]-calc(pl,i,5)-calc(pr,i,3)];
				f[l[pr-1][i]-l[pl][i]-u[pl][i]-d[pr][i]-s[pr-1][i]+s[pl][i]+calc(pl,i,12)+calc(pr,i,10)]++;
			}
		}
	for(int i=1;i<=n;i++)
		for(int t=1,j=2;j<=m;j++)
			if(t++,j==m||(a[i][j]-a[i][j-1])*(a[i][j+1]-a[i][j])<0)
				ans+=t*(t-1)/2,t=1;
	for(int j=1;j<=m;j++)
		for(int t=1,i=2;i<=n;i++)
			if(t++,i==n||(a[i][j]-a[i-1][j])*(a[i+1][j]-a[i][j])<0)
				ans+=t*(t-1)/2,t=1;
	cout<<ans<<"\n";
}
```

---

## 作者：xlpg0713 (赞：3)

提供一个比较聪明的做法。

首先考虑一个子矩形合法的条件，这当且仅当他在值域上的前驱和后继都和他直接相邻，我们从最大的点出发，每次选小于自己的最大的点出发。根据这个条件暴力判断可以做到 $O(H^3W^2)$。

不妨动用我们的人类智慧，对每一个点的状态做一个哈希，具体地：

令 $x$ 为一个极大的值，$f_{i,j}$ 为和 $(i,j)$ 这个点相邻的点中，小于 $a_{i,j}$ 的最大的点的值，不存在值为 $0$。如果四周的点都不比这个点大，这个点的哈希值为 $x-f_{i,j}$，否则为 $a_{i,j}-f_{i,j}$。

这样哈希之后，我们发现：一个合法的矩形的权值和为 $x$。这其实就是存在一条哈密顿路径。

这个条件是充要的，如果矩形不能被一条哈密顿路径覆盖，他的权值和一定大于 $x$。否则，每个点都会向 $f_{i,j}$ 所在的方向走，这样每个点的权值就可以被恰好抵消。

枚举想计算的子矩形的上下边界，对矩形的右端点坐标进行扫描，每个点有作为左边界上的点，右边界上的点，中间的点三种不同的权值，可以预处理。

在对右边进行扫描的过程中维护每个位置的权值，使用哈希表或者 `std::map` 即可实现 $O(H^2W)$ 或者 $O(H^2W\log W)$。

注意到 $\min(H,W)\le\sqrt{HW}$，选择较短的那一边作为 $H$ 可以做到 $O(HW\sqrt{HW})$。

这个做法不适用与矩形长/宽为 $1$，需要特殊处理。

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
using ll = long long; const int N = 1e5; const ll inf = 2e18;
std::vector<std::vector<int>> a; std::unordered_map<ll, int> mp;
int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0}, n, m, t[N], ct; ll sm, rs;
ll hs(int l, int r, int x, int y, int op){
    int mx = 0, mn = 0; for(int i = 0; i < 4; i++){
        int tx = x + dx[i], ty = y + dy[i];
        if(tx >= l && tx <= r && ty >= 1 && ty <= m &&
            (op == 1 ? (dy[i] != -1) : (op == 2 ? (dy[i] != 1) : 1)))
        a[tx][ty] > a[x][y] ? mx = a[tx][ty] : mn = std::max(mn, a[tx][ty]);
    } return mx ? a[x][y] - mn : inf - mn;
}
int main(){
    //freopen("sand.in", "r", stdin), freopen("sand.out", "w", stdout);
    std::ios::sync_with_stdio(false), std::cin.tie(0);
    std::cin >> n >> m; a.resize(n + 1, std::vector<int>(m + 1));
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) std::cin >> a[i][j];
    if(n > m){
        std::vector<std::vector<int>> b(m + 1, std::vector<int>(n + 1));
        for(int i = 1; i <= m; i++) for(int j = 1; j <= n; j++)
            b[i][j] = a[j][i]; std::swap(n, m), std::swap(a, b);
    }
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) t[++ct] = a[i][j];
    std::sort(t + 1, t + ct + 1); ct = std::unique(t + 1, t + ct + 1) - t;
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++)
        a[i][j] = std::lower_bound(t + 1, t + ct + 1, a[i][j]) - t + 1;
    std::vector<std::vector<ll>> f(n + 1, std::vector<ll>(m + 1)),
        g(n + 1, std::vector<ll>(m + 1)), h(n + 1, std::vector<ll>(m + 1));
    std::vector<ll> F(m + 1), G(m + 1), H(m + 1); for(int l = 1; l <= n; l++){ 
        for(int i = 1; i <= m; i++) F[i] = f[l][i] = hs(l, l, l, i, 0),
            G[i] = g[l][i] = hs(l, l, l, i, 1), H[i] = h[l][i] = hs(l, l, l, i, 2);
        for(int r = l + 1; sm = 0, mp = std::unordered_map<ll, int>(), r <= n; r++){
            for(int i = 1; i <= m; i++){
                F[i] += hs(l, r, r - 1, i, 0) - f[r - 1][i] + (f[r][i] = hs(l, r, r, i, 0));
                G[i] += hs(l, r, r - 1, i, 1) - g[r - 1][i] + (g[r][i] = hs(l, r, r, i, 1));
                H[i] += hs(l, r, r - 1, i, 2) - h[r - 1][i] + (h[r][i] = hs(l, r, r, i, 2));
                rs += mp[inf - sm - H[i]]; sm += F[i], ++mp[G[i] - sm];
            }
        }
    }
    for(int i = 1; i <= n; i++){
        int x = 0, y = 0; for(int j = 1; j < m; j++)
            a[i][j] < a[i][j+1] ? (rs += j-y, x = j) : (rs += j-x, y = j);
    }
    for (int i = 1; i <= m; ++i) {
        int x = 0, y = 0; for(int j = 1; j < n; j++)
            a[j][i] < a[j+1][i] ? (rs += j-y, x = j) : (rs += j-x, y = j);
    }
    std::cout << rs + 1ll * n * m << '\n';
}
```

---

## 作者：Autre (赞：2)

惊为天人的做法，来自 [_YangZj](https://www.luogu.com/article/yyxh4qm2)。

如何判断一个矩形是否存在如题所述的哈密顿路径？我们首先站在最大值的位置上，每次走向相邻的位置中，比自己小的最大者，若相邻的位置都大于当前所在的位置则停止，检查是否遍历整个矩形即可。

这启示我们把每个位置向它相邻的位置中比自己小的最大者连边，我们会得到一个森林，我们需要检查它是否是一条链。

设 $a_i$ 为点 $i$ 在原矩阵中的值，$f_i$ 为 $i$ 的父亲在原矩阵中的值，若 $i$ 为根则 $f_i=0$。点分成两类：

1. 对于一个四周都小于它的位置（可能成为起点的位置），我们对它赋权 $X-f_i$，其中 $X$ 是一个足够大的值；
2. 否则对它赋权 $a_i-f_i$。

首先所有点的点权 $>0$，因为我们的连边保证 $a_i>f_i$，且 $X$ 足够大。并且显然森林中至少有一个 1 类点，该点到根的路径上的点权之和为 $X$。

所以这个森林为一条链当且仅当这样赋权后所有点权之和为 $X$。

所以我们枚举矩形的上下边界，对于每个右端点可以 $O(1)$ 统计有多少左端点合法。

```C++
#include<unordered_map>
#include<iostream>

const int N = 233, M = 5e4, X = 1e9;
int n, m, a[N][M];
long long s, sm, l[N][M], c[N][M], r[N][M];
std::unordered_map<long long, int>ct;
int inline f(int x, std::initializer_list<int>il) {
	int s = X, mx = 0;
	for (int y : il) y < x ? mx = std::max(mx, y) : s = x;
	return s - mx;
}
int main() {
	if (int i, j; std::cin >> n >> m, n < m) for (i=0; i<n; i++)
		for (j=0; j<m; j++) std::cin >> a[i][j];
	else for (std::swap(n, m), i=0; i<m; i++)
		for (j=0; j<n; j++) std::cin >> a[j][i];
	for (int i=1, j; i<n-1; i++) {
		for (j=0; j<m-1; j++) l[i][j] = l[i-1][j] + f(a[i][j], {a[i-1][j], a[i][j+1], a[i+1][j]});
		for (j=1; j<m; j++) r[i][j] = r[i-1][j] + f(a[i][j], {a[i-1][j], a[i][j-1], a[i+1][j]});
		for (j=1; j<m-1; j++) c[i][j] = c[i-1][j] + f(a[i][j], {a[i-1][j], a[i][j-1], a[i+1][j], a[i][j+1]});
	}
	for (int i=0, j, k; i<n; i++) for (j=i+1; j<n; j++, ct.clear()) for (k=s=1; k<m; k++) {
		ct[l[i][k-1] - l[j-1][k-1] - f(a[i][k-1], {a[i+1][k-1], a[i][k]}) - f(a[j][k-1], {a[j-1][k-1], a[j][k]}) + s]++;
		auto it = ct.find(s + f(a[i][k], {a[i+1][k], a[i][k-1]}) + f(a[j][k], {a[j-1][k], a[j][k-1]}) + r[j-1][k] - r[i][k] - X);
		if (it != ct.end()) sm += it->second;
		s += c[j-1][k] - c[i][k] + f(a[i][k], {a[i+1][k], a[i][k-1], a[i][k+1]}) + f(a[j][k], {a[j-1][k], a[j][k-1], a[j][k+1]});
	}
	for (int i=0, j, x, y; i<n; i++) for (j=1, x=y=0; j<m; sm+=x+y, j++) if (a[i][j] < a[i][j-1]) x++, y = 0; else y++, x = 0;
	for (int j=0, i, x, y; j<m; j++) for (i=1, x=y=0; i<n; sm+=x+y, i++) if (a[i][j] < a[i-1][j]) x++, y = 0; else y++, x = 0;
	std::cout << sm + n * m;
}
```

---

点评：这我哪会啊

---

## 作者：rangers_meteor (赞：2)


考虑一个位置。

在被足够大的子矩形框柱之后。

他的朝向是固定的（即一定固定指向一个格子）。

不妨将这个指向 看成格子之间的连边。

考虑到一个子矩阵 存在一条曼哈顿路径 ，当且仅当 只有一个格子满足入度为 $0$ 。

那么就有个想法--------快速维护子矩阵内 是否有一个格子的入读为 $0$ 。

考虑对于一个子矩阵。

贴着边界的格子，以及靠近边界的格子， 距离边界的距离 $>=2$ 的格子 这三种情况的格子的入度的计算是不一样的。

贴着边界的格子，以及靠近边界的格子，他们的入度 需要预处理快速得到。

并且对于 距离边界的距离 $>= 2$ 的格子 也预处理一下。

所以需要预处理出 $16$ 种情况的（上下左右是否贴着边界）。

然后就好做了。

考虑一个一般化的子矩阵。


只用分 $25$ 种矩形的前缀和做做就好了。

会做 $nm \times nm$ 的话，对于全部的数据，要做完并不难吧。


---

## 作者：Erine (赞：0)

##### [JOI 2022 Final] Sand Castle 2.

弱智题。到底怎么评上黑的。

考虑怎么 check 一个子矩阵是否合法。令每个点指向自己在子矩阵的邻居中小于自己的最大的点。对每个点指向的点求和，如果等于总和去掉子矩阵最大值，则合法。因为合法形态总是构成一条链，这样得到的总和是最大的，若没有取到链肯定会减少总和。

考虑令 $H\le W$，若 $n=HW\le 5\times 10^4$，如此 $H\le \sqrt n$。枚举两行作为矩阵的上边界和下边界，然后计算有多少左右边界满足条件。

预处理一堆东西，最后转化出来的条件形如

$$a_l+b_r=\max_{i=l}^r c_i$$

直接对 $c$ 建立笛卡尔树，然后做启发式合并即可。这样单次是 $\Theta(W\log W)$。

所以总复杂度是 $\Theta(\min(H,W)HW\log \max(H,W))=\Theta(n\sqrt n\log n)$，可以通过。

---

## 作者：happybob (赞：0)

题意：

给定一个 $n \times m$ 的矩阵，每个点上写有权值 $a_{i,j}$，保证任意两个点的点权不同。求有多少子矩阵，使得存在一条四联通路径恰好覆盖子矩阵每个点一次，不覆盖子矩阵外任何点，且路径上点权单调下降。

$1 \leq n, m, n \times m \leq 5\times 10^4$，$1 \leq a_{i,j}\leq 10^7$，$4$ 秒。

解法：

我们先考虑怎么判定一个子矩阵合法。

首先路径起点必然是子矩阵最大值，其次我们每一步应该向相邻的点中比这个点小的最大值走。

我们对每个点赋一个权值。设 $s=10^{12}$，对于每个点，求出 $x$ 表示相邻的小于这个点的最大点权，若不存在则 $x=0$。若这个点为相邻中的最大值，我们设其权值为 $s-x$，否则设其权值为 $a_{i,j}-x$。因为 $s$ 足够大，一个矩阵合法当且仅当矩阵权值和为 $s$。

我们枚举矩阵的上下边界，然后对左边界扫描线，使用哈希维护每种权值和出现次数。扫描线的时候要维护左侧和右侧边界的权值和。

这样复杂度为 $O(n^2m)$，注意到 $n>m$ 时可以交换 $n,m$，于是复杂度为 $O(nm\sqrt{nm})$，可以通过。


```cpp
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <array>
#include <set>
#include <map>
#include <unordered_map>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;

using ll = long long;

constexpr int N = 5e4 + 5;
constexpr ll INF = (ll)1e12;

array<vector<int>, N> c, tc;
int n, m;

inline ll query(int x, int y, vector<pair<int, int>> pos)
{
	bool tag = 1;
	for (auto&& [i, j] : pos)
	{
		if (i < 1 || i > n || j < 1 || j > m) continue;
		tag &= (c[i][j] < c[x][y]);
	}
	int maxn = 0;
	for (auto&& [i, j] : pos)
	{
		if (i < 1 || i > n || j < 1 || j > m) continue;
		if (c[i][j] < c[x][y]) maxn = max(maxn, c[i][j]);
	}
	if (tag) return INF - maxn;
	return c[x][y] - maxn;
}

array<vector<ll>, N> sl, sr, sm;
array<ll, N> val, sv;
ll ans;

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		c[i].resize(m + 2);
		for (int j = 1; j <= m; j++) cin >> c[i][j];
	}
	if (n > m)
	{
		swap(n, m);
		tc = c;
		for (int i = 1; i <= n; i++)
		{
			c[i].clear(), c[i].shrink_to_fit();
			c[i].resize(m + 2);
			for (int j = 1; j <= m; j++) c[i][j] = tc[j][i];
		}
	}
	c[0].resize(m + 2);
	c[n + 1].resize(m + 2);
	for (int j = 1; j <= m; j++)
	{
		sl[j].resize(n + 2), sm[j].resize(n + 2), sr[j].resize(n + 2);
		for (int i = 1; i <= n; i++)
		{
			sl[j][i] = sl[j][i - 1] + query(i, j, { {i - 1, j}, {i + 1, j}, {i, j + 1} });
			sm[j][i] = sm[j][i - 1] + query(i, j, { {i - 1, j}, {i + 1, j}, {i, j + 1}, {i, j - 1} });
			sr[j][i] = sr[j][i - 1] + query(i, j, { {i - 1, j}, {i + 1, j}, {i, j - 1} });
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			val[1] = sl[1][j] - sl[1][i - 1];
			val[1] -= query(i, 1, { {i - 1, 1}, { i + 1, 1}, {i, 2} });
			val[1] += query(i, 1, { { i + 1, 1}, {i, 2} });
			val[1] -= query(j, 1, { {j - 1, 1}, { j + 1, 1}, {j, 2} });
			val[1] += query(j, 1, { { j - 1, 1}, {j, 2} });
			gp_hash_table<ll, int> cnt;
			for (int x = 2; x <= m; x++)
			{
				ll v = sm[x][j] - sm[x][i - 1];
				v -= query(i, x, { {i - 1, x}, {i + 1, x}, {i, x - 1}, {i, x + 1} });
				v += query(i, x, { {i + 1, x}, {i, x - 1}, {i, x + 1} });
				v -= query(j, x, { {j - 1, x}, {j + 1, x }, {j, x + 1}, {j, x - 1} });
				v += query(j, x, { {j - 1, x}, {j, x - 1}, {j, x + 1} });
				val[x] = val[x - 1] + v;
				ll nval = val[x] - v + sr[x][j] - sr[x][i - 1];
				nval -= query(i, x, { {i - 1, x}, {i, x - 1}, {i + 1, x} });
				nval += query(i, x, { {i + 1, x}, {i, x - 1} });
				nval -= query(j, x, { {j - 1, x}, {j, x - 1}, {j + 1, x} });
				nval += query(j, x, { {j - 1, x}, {j, x - 1} });
				cnt[nval]++;
				sv[x] = nval;
			}
			ll res = 0;
			for (int x = 1; x < m; x++)
			{
				ans += cnt[INF - res];
				cnt[sv[x + 1]]--;
				ll v = sl[x][j] - sl[x][i - 1];
				v -= query(i, x, { {i - 1, x}, { i + 1, x}, {i, x + 1} });
				v += query(i, x, { {i + 1, x}, {i, x + 1} });
				v -= query(j, x, { {j - 1, x}, { j + 1, x}, {j, x + 1} });
				v += query(j, x, { {j - 1, x}, {j, x + 1} });
				res -= v;
				v = sm[x + 1][j] - sm[x + 1][i - 1];
				v -= query(i, x + 1, { {i - 1, x + 1}, {i, x}, {i, x + 2}, {i + 1, x + 1} });
				v += query(i, x + 1, { {i, x + 2}, {i + 1, x + 1}, {i, x} });
				v -= query(j, x + 1, { {j - 1, x + 1}, {j + 1, x + 1}, {j, x}, {j, x + 2} });
				v += query(j, x + 1, { {j - 1, x + 1}, {j, x + 2}, {j, x} });
				res -= v;
				v = sl[x + 1][j] - sl[x + 1][i - 1];
				v -= query(i, x + 1, { {i - 1, x + 1}, {i + 1, x + 1}, {i, x + 2} });
				v += query(i, x + 1, { {i + 1, x + 1}, {i, x + 2} });
				v -= query(j, x + 1, { {j - 1, x + 1}, {j + 1, x + 1}, {j, x + 2} });
				v += query(j, x + 1, { {j - 1, x + 1}, {j, x + 2} });
				res += v;
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			bool gg = c[i][j] < c[i][j + 1];
			for (int k = j + 1; k <= m + 1; k++)
			{
				if (k == m + 1 || (c[i][k - 1] < c[i][k]) != gg)
				{
					int len = k - j;
					ans += 1ll * len * (len - 1) / 2;
					j = k - 2;
					if (k == m + 1) j = m + 2;
					break;
				}
			}
		}
	}
	for (int j = 1; j <= m; j++)
	{
		for (int i = 1; i <= n; i++)
		{
			bool gg = c[i][j] < c[i + 1][j];
			for (int x = i + 1; x <= n + 1; x++)
			{
				if (x == n + 1 || (c[x - 1][j] < c[x][j]) != gg)
				{
					int len = x - i;
					ans += 1ll * len * (len - 1) / 2;
					i = x - 2;
					if (x == n + 1) i = n + 2;
					break;
				}
			}
		}
	}
	cout << ans + n * m << "\n";
	return 0;
}
```

```

---

## 作者：StayAlone (赞：0)

xlpg 太强了。

对于一个子矩形，一定是从最大值开始走，每次往四周最大的比它小的位置走。

考虑给每个位置赋权值，设极大值 $x$。

对于 $(i, j)$，设四周最小的比它大的数为 $t$，若不存在则 $t=x$。若存在比它小的数，则权值为 $t-a_{i, j}$，否则为 $t$。发现一个子矩形合法，当且仅当该矩形的权值和为 $x$。

注意，赋权值是在子矩形确定的前提下进行的，因为边界上的“四周”并不完整。

定义函数 $f(u,d,l,r,x,y)$ 表示，若矩形的上边界为 $u$，下边界为 $d$，左边界为 $l$，右边界为 $r$，此时点 $(x, y)$ 的权值。显然可以 $\mathcal O(1)$ 算。

枚举上边界，扩展下边界的同时，对每一列分别维护其作为左边界、右边界和中间时的权值和。此时枚举右边界，左边界的值为定值，配合哈希表即可做到查询 $\mathcal O(1)$。总时间复杂度 $\mathcal O(n^2m)$。钦定 $n\leq m$，则有 $n\leq \sqrt{nm}$，时间复杂度为 $\mathcal O(nm\sqrt{nm})$。

面对行数或列数为 $1$ 的子矩形，上述方法特判繁杂，不如单独提出来用双指针解决。

提交时是最优解前 5，稍微卡常应该能更快。

[record](https://www.luogu.com.cn/record/189255067)

```cpp
int n, m; vector <int> a[MAXN];
const ll inf = 1e12;
ll ans; unordered_map <ll, int> cnt;
ll M[MAXN], L[MAXN], R[MAXN];

il ll get(int u, int d, int l, int r, int x, int y) {
	int mn = 0; ll mx = inf;
	rep1(i, 0, 3) {
		int nx = x + dx[i], ny = y + dy[i];
		if (nx >= u && nx <= d && ny >= l && ny <= r) {
			if (a[nx][ny] > a[x][y]) gmin(mx, (ll)a[nx][ny]);
			if (a[nx][ny] < a[x][y]) gmax(mn, a[nx][ny]);
		}
	} return mn ? mx - a[x][y] : mx;
}

int main() {
	read(n, m);
	if (n <= m) {
		rep1(i, 1, n) {
			a[i].resize(m + 1);
			rep1(j, 1, m) read(a[i][j]);
		}
	} else {
		rep1(i, 1, m) a[i].resize(n + 1);
		rep2(j, n, 1) rep1(i, 1, m) read(a[i][j]);
		swap(n, m);
	}
	rep1(i, 1, n - 1) {
		rep1(j, 1, m) {
			M[j] = get(i, i + 1, 1, m, i, j) + get(i, i + 1, 1, m, i + 1, j);
			L[j] = get(i, i + 1, j, m, i, j) + get(i, i + 1, j, m, i + 1, j);
			R[j] = get(i, i + 1, 1, j, i, j) + get(i, i + 1, 1, j, i + 1, j);
		}
		rep1(j, i + 1, n) {
			cnt.clear(); ll sm = M[1]; cnt[L[1] - sm] = 1;
			rep1(r, 2, m) {
				ll val = inf - sm - R[r];
				ans += cnt.count(val) ? cnt[val] : 0;
				sm += M[r]; ++cnt[L[r] - sm];
			}
			if (j < n) rep1(x, 1, m) {
				M[x] += get(i, j + 1, 1, m, j + 1, x) + get(i, j + 1, 1, m, j, x) - get(i, j, 1, m, j, x);
				L[x] += get(i, j + 1, x, m, j + 1, x) + get(i, j + 1, x, m, j, x) - get(i, j, x, m, j, x);
				R[x] += get(i, j + 1, 1, x, j + 1, x) + get(i, j + 1, 1, x, j, x) - get(i, j, 1, x, j, x);
			}
		}
	}
	rep1(i, 1, n) {
		for (int j = 1, k = 1, tg; j < m; ++j) {
			if (k == j) ++k, tg = a[i][k] - a[i][k - 1] > 0 ? 1 : -1;
			while (k < m && (a[i][k + 1] - a[i][k]) * tg > 0) ++k;
			ans += k - j + 1;
		} ++ans;
	}
	rep1(j, 1, m) {
		for (int i = 1, k = 1, tg; i < n; ++i) {
			if (k == i) ++k, tg = a[k][j] - a[k - 1][j] > 0 ? 1 : -1;
			while (k < n && (a[k + 1][j] - a[k][j]) * tg > 0) ++k;
			ans += k - i + 1;
		} ++ans;
	} printf("%lld", ans -= n * m);
	return 0;
}
```

---

## 作者：qiuzx (赞：0)

## 题意

有一个 $n\times m$ 的网格，每个格子有互不相同的数 $a_{i,j}$。定义一条路径合法，当且仅当每一步都是从更大的 $a_{i,j}$ 走向更小的 $a_{i,j}$。求有多少条合法路径的形态是一个子矩形。$nm\le 5\times 10^4$。

## 思路

先考虑怎么判定一个子矩形是否合法。显然我们的移动路径一定是从整个矩形的最大的元素开始依次降低。但如果直接将元素排序之后判定不好拓展到所有子矩形的问题。注意到若我们在一个格子上，那么下一步一定是走到能走到的点中 $a_{i,j}$ 最大的，否则一定不可能合法。如果记 $nxt_{i,j}$ 表示这样的下一个格子，并从 $(i,j)$ 向 $nxt_{i,j}$ 连边，那么这个子矩形合法当且仅当这个连出来的图形成一条链。如何更好地刻画一条链呢？若所有点中有超过 $1$ 个入度为 $0$ 的点则显然不是一条链。另一方面，若只有 $1$ 个入度为 $0$ 的点，那么由于每个点出度至多为 $1$，所以直接从这个点开始顺着出边走就能走完一条链。如果此时还没有走完所有的点，那么剩余的点中最大的一个的入度一定为 $0$，这就和只有一个入度为 $0$ 的点矛盾了。因此我们只需要判定入度为 $0$ 的点个数是否为 $1$ 即可。

而一个点的入度和矩形本身没有太大的关系，因为它只依赖于和它曼哈顿距离不超过 $2$ 的点的大小 ，所以在矩形充分大的时候一个中间的点的入度和矩形的边界无关，因此可以提前预处理之后求二维前缀和 $O(1)$ 查询一个矩形是否合法。然而问题在于矩形并不一定是充分大的，如果一个点靠近边界，那么可能有一些实际上会影响它入度的点根本就不在矩形内。具体来说，如果一个点与边界的距离 $<2$，那么它是需要被特殊处理的。但注意到只要确定了一个点距离矩形四个边界的距离（和 $2$ 取 $\min$），那么它的入度是固定的。因此可以预处理出 $f_{i,j,c_0,c_1,c_2,c_3}$ 表示 $(i,j)$ 这个格子在与四个边界距离分别为 $c_0,c_1,c_2,c_3$ 时的入度。这部分预处理的复杂度是 $O(nm3^4)$。

考虑现在怎么算一个子矩形是否合法。若矩形足够大（即长和宽都至少为 $4$），那么根据 $c_0,c_1,c_2,c_3$ 的不同可以分为 $25$ 种情况，其中对于 $f_{i,j,*,2,*,2}$ 和 $f_{i,j,2,*,2,*}$ 需要分别做行和列的前缀和，对 $f_{i,j,2,2,2,2}$ 需要做二维前缀和。这样就可以 $O(1)$ 查询了。对于长宽都 $<4$ 的情况可以直接暴力，对于长 $<4$ 的情况，枚举每一行，然后在一行内相当于是 $c_0,c_2$ 的值已经确定，这个一维的问题可以根据 $c_1,c_3$ 的不同用前面算出的前缀和处理即可。列也是同理。这样就在 $O(1)$​ 的时间内完成了一个子矩形的判定。下图中即是一个较大的矩形的分块情况，其中 $1\sim 16$ 这些块是单点，$17,18,23,24$ 是行前缀和，$19,20,21,22$ 是列前缀和，$25$ 是二维前缀和。

![](https://cdn.luogu.com.cn/upload/image_hosting/icly2ytq.png)

回到原问题，现在需要对所有子矩形进行计数。注意到上述判定需要用到的量和四个边界都有关，但每个需要用到的值都一定是由一个与 $x$ 有关的量和一个与 $y$ 有关的量组成。所以如果我们确定了行的上下边界，那么列的左右两个端点是独立的。可以看作一个 $l,r$ 的入度之和为 $f(r)+g(l)$，其中 $f,g$ 根据上下边界的大小可以直接求出。这样直接扫描 $r$，开桶记录 $g(l)$ 的出现次数，然后对于一个 $r$ 在桶里查 $1-f(r)$ 的 $g(l)$ 的个数即可。注意需要特别处理 $r-l<4$ 的情况，但这种情况直接暴力枚举 $l,r$ 用最开始的判定即可。

这样做的复杂度是 $O(n^2m)$，若 $n>m$ 则可以矩形旋转 $90$ 度，所以复杂度实际上是 $O(\min(n,m)^2\max(n,m))$，即 $O(nm\sqrt{nm})$。

[代码](https://www.luogu.com.cn/paste/jdfihh76)

---

## 作者：intel_core (赞：0)

JOI 组题人不恶心选手就难受。

看到 $HW\le 5\times 10^4$，所以不妨设 $H\le W$，立刻得到 $H\le \sqrt{5\times 10^4}$。

注意到如果一个矩形满足条件，那么将其中的数排序后在排完序的序列上相邻就必然等价于在矩阵上相邻；也就是说在值域上连续并且在矩阵上相邻的数对有 $S-1$ 个，其中 $S$ 表示该矩形的面积。

而又因为 $A_{i,j}$ 两两不同，所以若值域上相邻的数对有 $S-1$ 个，那么从最大值出发一直走就一定是一种合法方案。

故我们发现了一个矩形合法的等价条件：把其中元素排序后，在排序后的数组上任意相邻两个数在矩阵上都相邻。

接着考虑如何对于一个确定的左上角 $(x,y)$ 计算合法的右下角 $(i,j)$ 的数量，相当于就是如何维护上述数对的数量与 $S$ 的差 $d_{i,j}$，然后我们要数 $d_{i,j}$ 为 $-1$ 的 $(i,j)$ 个数。

先对于所有 $(x,W)$ 暴力计算出所有 $d_{i,j}$，这部分是 $O(H^3)$ 或者 $O(H^2\log H)$ 的。

然后考虑从 $(x,y+1)$ 推到 $(x,y)$ 的情况。我们先把 $d_{i,j}$ 减掉 $i-x+1$，也就是面积 $S$ 的增量。

再接着考虑增加第 $y$ 列造成的线段对 $d_{i,j}$ 造成的正贡献，每条线段两侧的数在值域上是相邻的等价于没有数大小处于中间；我们对于第 $i$ 行算出第一个在中间的数的位置 $p_i$，那么把 $y\le j\le \min \{p_k\}-1$ 的 $d_{i,j}$ 全部 $+1$ 即可。

这一部分的复杂度是 $O(H^2W \log W)$ 的，故总复杂度为 $O(V\sqrt{V}\log V)$，其中 $V=HW$。

---

