# [COCI 2017/2018 #7] Dostavljač

## 题目描述

自从 Krešo 开始种植辣椒以来，克罗地亚各地的 $N$ 家餐馆都对他的辣椒感兴趣，因此他们可以用真正的香料来丰富他们的菜肴。由于需求量很大，Krešo 决定开始作为辣椒的送货员。

餐馆用从 $1$ 到 $N$ 的数字表示，并且与 $N - 1$ 个道路相互连接，使得可以在任何两个餐馆之间旅行。Krešo 在 $1$ 号餐厅开始他的旅程。在一个单位的时间里，他可以开车到相邻的餐厅或将辣椒送到现在的餐馆。对于每家餐厅，我们都知道所需的辣椒数量 $A_i$。

由于交付货物很累，Krešo 决定在交付和旅行上花费总共 $M$ 个单位的时间，之后他计划休息一下。

确定 Krešo 在给定时间范围内可以提供的最大辣椒数量。你可以假设 Krešo 总是带有无限量的辣椒。

## 样例 #1

### 输入

```
3 5
9 2 5
1 2
1 3
```

### 输出

```
14```

## 样例 #2

### 输入

```
4 5
1 1 1 2
1 2
2 3
3 4
```

### 输出

```
3```

## 样例 #3

### 输入

```
5 10
1 3 5 2 4
5 2
3 1
2 3
4 2```

### 输出

```
15```

# 题解

## 作者：JK_LOVER (赞：8)

## 题意
给你一棵节点个数为 $n$ 的有根树，求出在所给时间内的 $ans$ 最大值。[QWQ](https://www.luogu.com.cn/blog/xzc/solution-p5054)
## 分析
对于每一个节点来看


- 停在这个节点了。

- 去遍历子树了。

- 一系列操作之后，返回父亲了。

那么我们可以定义状态。 $dp[x][i][0/1]$ 对于节点 $x$ 考虑，使用了 大小为 $i$ 的时间。其中 $0$ 表示去遍历子树了， $1$ 表示停在这个节点了。 而返回父亲则可以用 $dp[x][i+1][1]$ 表示，因为再走一步就可以返回父亲。有如下转移方程：
$$
dp[x][i+j+2][1] = \max(dp[x][i][1] +dp[y][j][1])
$$
$$
dp[x][i+j+1][0] = \max(dp[x][i][1]+dp[y][j][0])
$$
$$
dp[x][i+j+2][0] = \max(dp[x][i][0]+dp[y][j][1])
$$
分别表示：

- 儿子返回父亲，父亲停下。

- 父亲停下，去儿子子树。 

- 儿子返回，去父亲子树。

时间复杂度为 $O(nm^2)$ 。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return f?-x:x;
}
const int N = 1100;
int dp[N][N][2],n,m,val[N];
vector<int> G[N];
void dfs(int x,int fa)
{
	for(int i = 0;i < G[x].size();i++)
	{
		int y = G[x].at(i);
		if(y == fa) continue;
		dfs(y,x);
		for(int j = m;j >= 0;j--)
		{
			for(int k = m;k >= 0;k--)
			{
				if(k + j + 2 <= m) 
				dp[x][j+k+2][0] = max(dp[x][j+k+2][0],dp[x][j][0]+dp[y][k][1]);
				dp[x][j+k+2][1] = max(dp[x][j+k+2][1],dp[x][j][1]+dp[y][k][1]);	
				if(k + j + 1 <= m)
				dp[x][j+k+1][0] = max(dp[x][j+k+1][0],dp[x][j][1]+dp[y][k][0]);
			}
		}
	}
	for(int i = m;i >= 1;i--)
	dp[x][i][1] = max(dp[x][i][1],dp[x][i-1][1]+val[x]),
	dp[x][i][0] = max(dp[x][i][0],dp[x][i-1][0]+val[x]);
//	for(int i = 1;i <= m;i++)
//	{
//		cout<<"x:: " <<x<<"   i:: "<<i<<"  dp::"<<dp[x][i][0]<<endl;
//	}
}
int main()
{
	n = read();m = read();
	for(int i = 1;i <= n;i++) val[i] = read();
	for(int i = 1;i < n;i++)
	{
		int a = read(),b = read();
		G[a].push_back(b);
		G[b].push_back(a);
	}
	dfs(1,0);
	cout<<dp[1][m][0]<<endl;
	return 0;
}
```




---

## 作者：0zhouyq (赞：2)

## 思路
很明显这是一道树形 $DP$ 的题。状态转移方程和楼上大佬的一样：

$dp[x][i+j+2][1] = \max(dp[x][i][1] +dp[y][j][1])$

$dp[x][i+j+1][0] = \max(dp[x][i][1]+dp[y][j][0])$

$dp[x][i+j+2][0] = \max(dp[x][i][0]+dp[y][j][1])$

我用了链式前向星来存图，因为题目给了边的最大数量为 $2 \times n-1$ 。

## AC CODE
```cpp
#include<stdio.h>
int n,m,cnt;
int v[501],dp[501][501][2],head[501];
struct edge{
	int v,next;
}e[999];
inline int read(){//快读。
    register int x=0;
    char c=getchar();
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
    return x;
}
inline void write(int x)//快写。
{
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+48);
}
inline void add(int u,int v){//链式前向星存图。
	e[++cnt].v=v;
	e[cnt].next=head[u];
	head[u]=cnt;
}
inline int Max(int a,int b){//最大值函数，比STL库里的max函数要快一点。
	return a>b?a:b;
}
inline void dfs(int u,int fa){//后序排列+树形DP。
	for(register int i=head[u];i;i=e[i].next){
		int v=e[i].v;
		if(v==fa) goto bck;//相当于continue，但比它快。
		dfs(v,u);
		for(register int j=m;j>=0;--j){
			for(register int k=m;k>=0;--k){
				if(k+j<m-1){
					dp[u][j+k+2][0]=Max(dp[u][j+k+2][0],dp[u][j][0]+dp[v][k][1]);
					dp[u][j+k+2][1]=Max(dp[u][j+k+2][1],dp[u][j][1]+dp[v][k][1]);
				}
				if(k+j<m)dp[u][j+k+1][0]=Max(dp[u][j+k+1][0],dp[u][j][1]+dp[v][k][0]);
			}
		}
		bck:;
	}
	for(register int i=m;i>=1;--i){
		dp[u][i][0]=Max(dp[u][i][0],dp[u][i-1][0]+v[u]);
		dp[u][i][1]=Max(dp[u][i][1],dp[u][i-1][1]+v[u]);
	}
}
int main(){
	n=read();
	m=read();
	for(register int i=1;i<=n;++i) v[i]=read();
	for(register int i=1;i<n;++i){
    	int x,y;
		x=read();
		y=read();
		add(x,y);
		add(y,x);
	}
	dfs(1,0);
	write(dp[1][m][0]);
}
```


---

## 作者：ningago (赞：1)

## 题意

给你一棵 $n$ 个点的无向树，和每个点的权值 $a_i$，初始你在 $1$ 号节点，每次操作可以在这两种操作中选一个：

- 移动到一个相邻节点；

- 留在这个点（记作 $i$），并对答案做出 $a_i$ 的贡献。

求 $m$ 次操作后最多做出多少贡献。

冷知识：题面翻译来自 Google 翻译。

## 题解

数据范围提示我们可以使用类背包的算法：把已操作次数记作 DP 状态。

又考虑到：假如 $u$ 有两个子树 $B,C$，如果我们想要在 $B$ 里瞎跑后再去 $C$ 瞎跑，那么必须在跑完 $B$ 后回到 $u$，然后从 $u$ 跑到 $C$。

而特殊的是你可以在任意节点结束，并非起点。

于是可以设计 DP 状态：$f[i][j][k] (i\in[1,n],j\in[0,m],k\in[0,1])$。

$f[i][j][1]$ 表示在 $j$ 的时间内，在 $i$ 的子树内瞎跑后回到了 $i$ 节点的最大贡献。

$f[i][j][0]$ 表示在 $j$ 的时间内，在 $i$ 的子树内瞎跑后停在 $i$ 子树内的任意节点的最大贡献。

枚举 $i$ 的子树 $nx$。

$f[i][j][1]$ 的最大值就是先从 $i$ 跑到 $nx$，在 $nx$ 子树内瞎跑，回到 $nx$，回到 $i$ ，这个过程的最大贡献。

$$f[i][j + k + 2][1] = \max\{f[i][j][1] + f[nx][k][1]\}$$

$f[i][j][0]$ 的最大值就是先从 $i$ 跑到 $nx$，在 $nx$ 子树内瞎跑，停在任意节点，这个过程的最大贡献。

$$f[i][j + k + 1][0] = \max\{f[i][j][1] + f[nx][k][0]\}$$

还有一种情况，$f[i][j][0]$ 先从 $i$ 任意子树内瞎跑，回到 $i$，再选任意子树瞎跑并停在任意节点，这个过程的最大贡献。

$$f[i][j + k + 2][0] = \max\{f[nx][k][1] + f[i][j][0]\}$$

其中 $k$ 为枚举子树里瞎跑的时间。

答案显然为 $dp[1][m][0]$。

## Code

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>

#define N 510

int dp[N][N][2];
int a[N],n,m;
int h[N],e[N << 1],ne[N << 1],idx;

void add_edge(int x,int y)
{
	ne[++idx] = h[x];
	h[x] = idx;
	e[idx] = y;
}

void add(int x,int y)
{
	add_edge(x,y);
	add_edge(y,x);
}

void dfs(int u,int fa)
{
	for(int p = h[u];~p;p = ne[p])
	{
		int nx = e[p];
		if(nx == fa)
			continue;
		dfs(nx,u);
		for(int i = m;i >= 0;i--)
		{
			for(int j = m;j >= 0;j--)
			{
				if(i + j + 2 <= m)
				dp[u][i + j + 2][1] = std::max(dp[u][i + j + 2][1],dp[u][i][1] + dp[nx][j][1]);
				if(i + j + 1 <= m)
				dp[u][i + j + 1][0] = std::max(dp[u][i + j + 1][0],dp[u][i][1] + dp[nx][j][0]);
				if(i + j + 2 <= m)
				dp[u][i + j + 2][0] = std::max(dp[u][i + j + 2][0],dp[nx][j][1] + dp[u][i][0]);
			}
		}
	}
	for(int i = m;i >= 1;i--)
	{
		dp[u][i][0] = std::max(dp[u][i][0],dp[u][i - 1][0] + a[u]);
		dp[u][i][1] = std::max(dp[u][i][1],dp[u][i - 1][1] + a[u]);
	}
}

int main()
{
	memset(h,-1,sizeof(h));
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++)
		scanf("%d",&a[i]);
	for(int i = 1,x,y;i < n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	dfs(1,0);
	printf("%d\n",dp[1][m][0]);
	return 0;
}
```

---

## 作者：Cipher0128 (赞：0)

一看就是背包 dp，于是设状态 $f_{x,i}$ 为 $x$ 节点有 $i$ 时间的答案，每个点都可以往下走，同时也可以花费时间把当前点权加上……然后发现样例过不了。因为忘记考虑了一个限制：只有一个送货员。如果他走到了子树，想要去别的地方还要原路走回来，也可以停在那里。状态不够了，升一维。记 $f_{x,i,0/1}$ 表示 $x$ 节点有 $i$ 时间，是否还能回来的答案。即如果是 $0$，那么停在 $x$ 字数内，如果是 $1$，那么还要走回 $x$ 点。

转移就很简单了：如果停在子树内，那么要从一些子树回来然后在另一个子树中停，如果走回来，那么每一个子树都得走回来。还要考虑当前点权是否加上。

代码如下：
```cpp
#include<bits/stdc++.h>
#define for_(a,b,c) for(int a=b;a<=c;++a)
#define For_(a,b,c) for(int a=b;a>=c;--a)
using namespace std;
int n,m;
const int N=510;
vector<int>e[N];
long long a[N],f[N][N<<1][2];
void dfs(int x,int pa){
	for(auto y:e[x]){
		if(y==pa)continue;
		dfs(y,x);
		For_(i,m,0)for_(j,0,m){
			f[x][i+j+1][0]=max(f[x][i+j+1][0],f[x][i][1]+f[y][j][0]);
			f[x][i+j+2][0]=max(f[x][i+j+2][0],f[x][i][0]+f[y][j][1]);
			f[x][i+j+2][1]=max(f[x][i+j+2][1],f[x][i][1]+f[y][j][1]);
		}
	}
	For_(i,m,1)f[x][i][0]=max(f[x][i-1][0]+a[x],f[x][i][0]),f[x][i][1]=max(f[x][i-1][1]+a[x],f[x][i][1]);
}
int main(){
	cin>>n>>m; 
	for_(i,1,n)cin>>a[i];
	for_(i,1,n-1){
		int x,y;cin>>x>>y;
		e[x].push_back(y);e[y].push_back(x);
	}
	dfs(1,0);
	cout<<max(f[1][m][0],f[1][m][1]);
	return 0;
}
```

---

## 作者：Engulf (赞：0)

经典树形背包。

设 $f_{u, j}$ 表示从 $u$ 出发，在子树内走，最后在时刻 $j$ 回到 $u$，能获得的最大价值。

设 $g_{u, j}$ 表示从 $u$ 出发，在子树内走，最后在时刻 $j$ **停在子树内部**，能获得的最大价值。

$$f_{u, j} = \max(f_{u, k}, f_{v, j - 2 - k})$$

这个意思是，前面的子树乱走回到 $u$，然后往 $v$ 的子树里走，走回 $v$，走回 $u$。这条边要走两次，所以是 $-2$。

$$g_{u, j} = \max(g_{u, j}, f_{u, k} + g_{v, j - 1 - k}, g_{u, k} + f_{v, j - 2 - k})$$

这个意思是，前面的子树乱走走回到 $u$，再往 $v$ 里走不回来了，所以边只经过一次，是为 $-1$。这是 $f_{u, k} + g_{v, j - 1 - k}$。

或者在 $v$ 子树内走，走回来，再往前面的子树乱走不回来了，边经过两次，是为 $-2$。这是 $g_{u, k} + f_{v, j - 2 - k}$。

最终答案就是 $g_{1, m}$（往里走肯定比走回来优）。

注意注意，每次 dp 的 $u$ 不是必须取的，要跟有依赖的背包问题区分开来。

$O(nm^2)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 505;

int n, m;
int a[N];

vector<int> e[N];

int f[N][N], g[N][N];

void chkmax(int &x, int y) {x = max(x, y);}

void dfs(int u, int fa) {
    for (auto v: e[u]) {
        if (v == fa) continue;
        dfs(v, u);

        for (int j = m; j >= 1; j--)
            for (int k = j - 1; k >= 0; k--) {
                chkmax(g[u][j], f[u][k] + g[v][j - 1 - k]);
                if (j - 2 - k >= 0) {
                    chkmax(g[u][j], g[u][k] + f[v][j - 2 - k]);
                    chkmax(f[u][j], f[u][k] + f[v][j - 2 - k]);
                }
            }
    }

    for (int j = m; j >= 1; j--) {
        chkmax(f[u][j], f[u][j - 1] + a[u]);
        chkmax(g[u][j], g[u][j - 1] + a[u]);
    }
    f[u][0] = g[u][0] = 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int i = 1, x, y; i < n; i++) {
        cin >> x >> y;
        e[x].emplace_back(y);
        e[y].emplace_back(x);
    }

    dfs(1, 0);
    cout << g[1][m] << "\n";
    return 0;
}
```

---

## 作者：Unnamed114514 (赞：0)

省流：好典啊

$1\le n,m\le 500$，大胆猜测这应该是一个 $O(nm^2)$ 的树上背包。

容易想到 $f_{i,j}$ 表示 $i$ 为根的子树一共要用掉 $j$ 的时间。

但是我们这道题是在树上反复横跳，所以上述 dp 式不能满足确定位置。

注意到最后一棵子树是不用回去的，并且如果你进入了一棵子树就不会再进去一次，可以在状态后加入 $0/1$ 表示是否必须要回到根节点。

当前一坨是 $u$，新加入子树是 $v$，有如下转移：

- 到 $v$ 就不回来了：$dp_{u,i,0}\gets\max\{dp_{u,i,0},dp_{u,i-j-1,1}+dp_{v,j,0}\}$。

- 到 $v$ 回来，$u$ 原来的子树用不回去：$dp_{u,i,0}\gets\max\{dp_{u,i,0},dp_{u,i-j-2,0}+dp_{v,i,0}\}$。

- 到 $v$ 回来，$u$ 原来的子树也要回来：$dp_{u,i,0}\gets\max\{dp_{u,i,1},dp_{u,i-j-2,1}+dp_{v,i,0}\}$。

$i,j$ 就是树上背包枚举的体积。

答案就是 $dp_{1,m,0}$，初始化就是每个节点的 $A$。

时间 $O(nm^2)$，空间 $O(nm)$。

---

