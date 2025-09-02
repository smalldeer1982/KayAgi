# Nuts for nuts..

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=21&page=show_problem&problem=1885

[PDF](https://uva.onlinejudge.org/external/109/p10944.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10944/eab44d58cb45ad772b3f67192aa37528e61e5fe1.png)

## 样例 #1

### 输入

```
5 5
L....
#....
#....
.....
#....
5 5
L....
#....
#....
.....
#....```

### 输出

```
8
8```

# 题解

## 作者：jdsb (赞：3)

## 题意

- 给定一个 $n*m$ 的地图，出发点为  ‘L’ ，要经过每个 ‘#’，最后返回‘L’，求最小路程。
- $n,m≤20$，‘#’ 的个数$≤15$

## 分析

- 首先我们发现，这个地图其实是不重要的，有用的信息其实只有 ‘#’ 和  ‘L’ 的位置，因此，我们可以把 ‘#  和 ‘L’ 当成一个个点，直接预处理出任意两点的距离，注意，松鼠是可以斜着走的，所以两点的距离不是两点的哈夫曼距离，而是两点的横纵坐标差值的最大值。

- 然后观察数据范围，我们可以发现这是一个状压DP的题，设 $f[i][S]$ 表示从出发点到 $i$ 号点时，已经经过的点的状态为 $S$ 时的最小路程，用 $d[i][j]$表示 $i$ 号点与 $j$ 号点的距离，则有 
  $$f[i][S]=min\{f[j][S-2^i]+d[i][j]\}\left(i\in S,j\in S,i≠j\right)$$

- 分析一下上面的转移方程，从 $j$ 号点转移到 $i$ 号点,经过 $i$ 号点的状态是为 $S$，那么不经过 $i$ 号点时的状态就为 $S-2^i$，然后直接加上 $j$ 到 $i$ 的距离即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^'0');c=getchar();}
	return x*f;
}
const int N=20,S=1<<N,inf=1e9;
int f[N][S],ans,d[N][N];
char mp[N][N];
struct node
{
	int x,y;
}a[N];
int dis(int i,int j)
{
	return max(abs(a[i].x-a[j].x),abs(a[i].y-a[j].y));
}
int n,m,tot;
int main()
{
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		tot=0;
		ans=inf;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			{
				cin>>mp[i][j];
				if(mp[i][j]=='L') a[0]={i,j};
				if(mp[i][j]=='#') a[++tot]={i,j};
			}
		n=tot+1;
		for(int i=0;i<n;i++)
			for(int j=i+1;j<n;j++)
				d[i][j]=d[j][i]=dis(i,j);
		memset(f,0x3f,sizeof(f));
		f[0][1]=0;
		for(int s=1;s<(1<<n);s+=2)
			for(int i=0;i<n;i++)
			{
				if((s>>i&1)==0) continue;
				for(int j=0;j<n;j++)
				{
					if(s>>j&1==0||i==j) continue;
					f[i][s]=min(f[i][s],f[j][s-(1<<i)]+d[j][i]);
				}
			}
		for(int i=0;i<n;i++)
			ans=min(ans,f[i][(1<<n)-1]+d[i][0]);
		printf("%d\n",ans);	
	}
	return 0;
}
```

---

## 作者：lajioj (赞：3)

### 比较经典的$TSP$问题

题意：松鼠位于$L$点，需要采集所有#点的松果，最后返回$L$点，问此过程的最短距离（松鼠有8种转移方式，即上下左右+对角线1个单位）

-思路：一看此题就是和[售货员的难题](https://www.luogu.org/problemnew/show/P1171)如出一辙，只是输入方法不一样，如果做过的可以直接套版转化  
- 用二进制数表示坚果的收集状态，$0$表示未收集，$1$已收集；$dis$[$i$][$j$]表示节点$i$和$j$的相对距离；$f$[$i$][$j$]表示在收集状态为$j$是收集$i$的最小步数；  
- 显然，收集每颗坚果的最小步数为$f$[$i$][$2^{i-1}$]=$dis$[$0$][$i$];
递增枚举状态值$i$，状态$i$中最后被收集的坚果$j$，枚举$i$外的坚果$k$。
$f$[$k$][$i$+$1$<<($k$-$1$)] = $min$($f$[$k$][$i$+$1$<<($k$-$1$)], $f$[$j$][$i$] + $dis$[$j$][$k$]);  
- 所有坚果收集后，若最后一颗为$i$,则到$i$的最小步数为$f$[$i$][$1$<<($n$)-$1$],加上返回起点的步数$map$[$0$][$i$],找到最少步数；
$ans$=$min$($f$[$i$][$1$<<($n$)-$1$]+$dis$[$0$][$i$]);(枚举$i$)


本题数据范围可能有误，建议数组**稍微**开大一点

```cpp
#include<stdio.h>
#include<cmath>
#include<cstring>
#include<algorithm>
#define inf 0x3f3f3f3f
using namespace std;

int n,m;const int MAXN = 30;
char map[MAXN][MAXN];int u;int dis[MAXN][MAXN];
int l[MAXN];int f[MAXN][1<<20];

struct edge{
	int i,j;
}e;edge nut[MAXN];

inline void init(){
	getchar();
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			scanf("%c",&map[i][j]);
			if(map[i][j] == '#'){
				e.i = i;e.j = j;
				nut[++u] = e;
			}
			if(map[i][j] == 'L'){
				e.i = i;e.j = j;
				nut[1] = e;
			}
		}
		getchar();
	}
}

inline void work(){
	for(int i=1;i<=u;++i){
		for(int j=i+1;j<=u;++j){
			dis[i][j] = dis[j][i] = max(abs(nut[i].i - nut[j].i) , abs(nut[i].j - nut[j].j));
		}
	}
}

inline void get(){
	memset(f,inf,sizeof f);
    f[1][1]=0;int p=(1<<u);
    for(int i=0;i<p;++i){
        for(int j=1;j<=u;++j){
            if(i&l[j]){
                for(int k=1;k<=u;++k){
                    if(!(i&l[k])){
                        f[k][i|l[k]] = min(f[k][i|l[k]],f[j][i] + dis[j][k]);
                    }
                }
            }
        }
    }
}

inline void clear(){
	u = 1;
	memset(f,0,sizeof f);
	memset(dis,0,sizeof dis);
	memset(l,0,sizeof l);
}

int main(){
	while(~scanf("%d%d",&n,&m)){
		clear();
		init();
		work();
		for(int i=1;i<=u;++i) l[i] = (1<<i-1);
		get();
		int ans=inf;
    	for(int i=1;i<=u;++i){
        	ans = min(ans,f[i][(1<<u)-1] + dis[i][1]);
    	}
    	printf("%d\n",ans);
	}
	return 0;
}

```

---

## 作者：OldDriverTree (赞：1)

# 题意
+ 给定一个 $n\times m$ 的地图，出发点为 'L'，要经过每个 '#'，最后返回 'L'。
+ 每次可以走到 $8$ 个方向上的相邻的格子。
+ 求最少需要走多少步。

# 思路
这道题其实和 [售货员的难题](https://www.luogu.com.cn/record/101801794) 基本上一样。

所以我们考虑如何转化为那道题。

由于可以走上下左右或斜着走 $1$ 个格子，那么两颗坚果 $(x_1,y_1)$ 到 $(x_2,y_2)$ 的距离就是 $\max(\vert x_1-x_2\vert,\vert y_1-y_2\vert)$。

那么剩下的就和刚才那题一样了。

考虑状压 dp ，设 $\mathit{f}_{S,x}$ 表示经过的点的状态为 $S$ 且目前最后到达的点为 $x$ 时需要走的最短步数。

状态转移方程就是：$\mathit{f}_{S,x}=\min_{y=0}^{y<n} \mathit{f}_{S-2^x,y}+dis(x,y)$。

由于最后还要再回到起点，那么 dp 完答案就是 $\min_{i=0}^{i<n} \mathit{f}_{2^n-1,i}+dis(0,i)$。

记得再特判没有坚果的情况。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=16;
int tot,ans;
int n,m,f[1<<N][N];
pair<int,int> a[N];

int dis(int x,int y) { //x->y 的距离 
	return max(abs(a[x].first-a[y].first),abs(a[x].second-a[y].second));
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	while (cin>>n>>m)
	{
		memset(f,0x3f,sizeof f);
		f[1][0]=0,tot=1,ans=114514;
		
		for (int i=0;i<n;i++)
			for (int j=0;j<m;j++) {
				char ch; cin>>ch;
				if (ch=='L') a[0]=make_pair(i,j);
				if (ch=='#') a[tot++]=make_pair(i,j);
			} n=tot;
		
		for (int S=2;S<(1<<n);S++)
			for (int v=0;v<n;v++)
				if (S>>v&1)
				{
					for (int u=0;u<n;u++)
						if (u!=v&&(S>>u&1))
							f[S][v]=min(f[S][v],f[S^(1<<v)][u]+dis(u,v));
					if (S==(1<<n)-1) ans=min(ans,f[S][v]+dis(0,v));
				}
		if (n<2) printf("0\n"); //特判
		else printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：CYZZ (赞：1)

# [Nuts for nuts..](https://www.luogu.com.cn/problem/UVA10944)
## 思路分析
- 题面有坑，本题中松鼠可以**八向移动**，所以两个坚果之间的距离是它们的[切比雪夫距离](https://baike.baidu.com/item/%E5%88%87%E6%AF%94%E9%9B%AA%E5%A4%AB%E8%B7%9D%E7%A6%BB/8955729)（参考百度百科）。把起点看成第一个坚果。
- 我们不需要图，只需要预处理出任意两个坚果之间的距离即可，此时的 $n$ 变为总坚果数。
- 坚果总数 $\le15$ 很容易让人想起**状压 DP**，这题和[售货员的难题](https://www.luogu.com.cn/problem/P1171)类似。

## 状压 DP
### 状态
我们以一个**二进制数**来表示当前松鼠已经走过的点的集合（状态），第 $i$ 位是 $1$ 就代表走过，是 $0$ 则是没走过。

可以设状态 $dp_{i,j}$ 为当前走到了 $i$ 号点且状态恰好为 $j$ 的最短距离。
### 方程
显然 $dp_{i,j}$ 由在 $i$ 之前已经到达的点 $k$ 转移过来。所以方程就是：
$$dp_{i,j+2^{i-1}}=\min(dp_{i,j+2^{i-1}},dp_{k,j}+dis_{k,i}),(i \notin j,k \in j)$$
分析一下，上面的方程其实是松鼠从 $k$ 走到 $i$ 的转移。其中在 $k$ 以前没到过 $i$，所以 $i \notin j$。走到以后 $j$ 就变成了 $j+2^{i-1}$。$dis_{k,i}$ 为前面预处理出的从 $k$ 走到 $i$ 的距离。
### 初始化
初始值 $dp_{1,1}=0$，其余为 $\inf$，因为最开始松鼠只到过 $1$ 号起点。最后松鼠走完所有点要回到起点，所以最终答案就是 $\min\{dp_{i,2^n-1}+dis_{i,1}\}(i\in[1,n])$。

本题中两点之间的距离公式是 $dis_{i,j}=\max(|x_i-x_j|,|y_i-y_j|)$。
## 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,a[25][2],dis[25][25],tot,dp[17][1<<16];//数组要开2^16
int getdis(int x,int y)
{
	return max(abs(a[x][0]-a[y][0]),abs(a[x][1]-a[y][1]));//切比雪夫距离 
}
int main()
{
	while(~scanf("%d%d",&n,&m))
	{
		tot=1;
		for(int i=1;i<=n;i++)
		{
			getchar();
			for(int j=1;j<=m;j++)
			{
				char c=getchar();
				if(c=='L')
					a[1][0]=i,a[1][1]=j;
				if(c=='#')
					a[++tot][0]=i,a[tot][1]=j;
			}
		}
		n=tot;//n变为坚果数 
		for(int i=1;i<=n;i++)
		{
			for(int j=i+1;j<=n;j++)
			{
				dis[i][j]=dis[j][i]=getdis(i,j);//求出距离 
			}
		}
		memset(dp,0x3f,sizeof dp);
		dp[1][1]=0;//初始值 
		for(int j=0;j<(1<<n);j++)
		{
			for(int k=1;k<=n;k++)
			{
				if((1<<k-1)&j)
				for(int i=1;i<=n;i++)
				{
					if((1<<i-1)&j)
						continue;
					dp[i][j|(1<<i-1)]=min(dp[i][j|(1<<i-1)],dp[k][j]+dis[k][i]);//转移 
				}
			}
		}
		int ans=INT_MAX;
		for(int i=1;i<=n;i++)
		{
			ans=min(ans,dp[i][(1<<n)-1]+dis[i][1]);//求出答案 
		}
		printf("%d\n",ans);
	}
	return 0;
} 
```
本人的第一道黑题题解，希望能帮到大家！！！

---

## 作者：EastPorridge (赞：1)

### 题目概述：

给你一张 $n \times m$ 的图，让你求从给定起点出发，经过所有题目要求的必经点，返回起点的最短距离是多少。

数据范围：$1 \le n,m \le 20$。必经点少于 $15$ 个。

### 题目分析：

大家好啊，我非常喜欢爆搜，所以我用 bfs 把这道状压 dp 过了。

考虑对必经点进行状压，对必经点进行编号，对应在一个数字的二进制下 $0$ 或 $1$，表示当前这个点是否已经被经过，$1$ 表示经过了，$0$ 表示没有。

我们考虑 bfs 结束的状态，应为到达初始点且所有必经点被经过，记必经点从 $0$ 开始标号的数量为 $cnt$，即合法状态为 $2^{(cnt+1)}-1$。

再考虑一下剪枝，一个点不用进队了，当且仅当到当前点时这个状态已经入队过了，所以开一个 $st[x][y][sta]$ 表示对于当前点 $(x,y)$，状压过后的 $sta$ 这个状态是否被标记过了，如果没有，就标记，入队。 

最后一个小技巧就是方向数组，记录八个方向的 $(x,y)$ 偏移量，可以有效精炼代码。

计算一下复杂度，单次下来每个点最多有 $2^{16}-1$ 种状态，整个图最多有 $400$ 个点，整张图跑满最多 $2 \times 10^7$，且事实上根本跑不满，所以是可以通过的。

最后，[喜 提 最 劣 解](https://www.luogu.com.cn/record/89640023)。

### Code.

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=25;
int n,m,ma[N][N],nut[N][N],st[N][N][(1<<16)+1],cnt,sx,sy,dx[]={0,-1,-1,-1,0,0,1,1,1},dy[]={0,-1,0,1,-1,1,-1,0,1};
struct node {int x,y,sta,sum;};
inline int bfs()
{
	memset(st,0,sizeof st); queue<node> q;
	q.emplace(node{sx,sy,0,0}); st[sx][sy][0]=1;
	while(! q.empty())
	{
		auto u=q.front(); q.pop();
		if(ma[u.x][u.y] == 2 && u.sta == (1<<cnt)-1) return u.sum;
		for(int i=1;i<=8;i++)
		{
			int x=u.x+dx[i],y=u.y+dy[i],pl=u.sta;
			if(x < 1 || x > n || y < 1 || y > m) continue ;
			if(ma[x][y] == 1) pl|=(1<<nut[x][y]); if(st[x][y][pl]) continue ;
			st[x][y][pl]=1; q.emplace(node{x,y,pl,u.sum+1});
		}
	}
	return 0;
}
int main()
{
	while(~scanf("%d%d",&n,&m))
	{
		cnt=0; memset(nut,0,sizeof nut); memset(ma,0,sizeof ma);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			{
				char x; cin>>x;
				if(x == 'L') sx=i,sy=j,ma[i][j]=2;
				else if(x == '#') ma[i][j]=1,nut[i][j]=cnt++;
			}
		if(! cnt) {puts("0"); continue ;}
		printf("%d\n",bfs());
	}
	return 0;
}
```

---

## 作者：cyc001 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/UVA10944)

[PDF](https://onlinejudge.org/external/109/p10944.pdf)

## 思路：
首先，我们不难发现，地图中除了 ```#``` 和 ```L``` 以外的点都没有用，此时可以考虑将 ```#``` 点离散化，将原图简化为一张完全图，并将出发点设为点 $0$ (在后续分析中， ```#``` 的数量记为 $m$ )。

离散化完成后，就该考虑算法了。在最优解中，图中的每一个点一定只会经过一次，且 $m\le 15$ ，所以可以使用状压 DP 依次枚举每一个可行的状态，在每个状态中尝试枚举可行的出发点，并更新 D 数组。

最终答案为 $\min_{1\le i\le m}(D_{i,\ 2^m-1}+dist_{i,0})$ 。

注意当 $\ m=0\ $ 时需要特判答案为 $\ 0\ $。

时间复杂度: $O(q2^mm^2)$


## Code
```cpp
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct pl { int x, y; };
int dist(pl& a, pl& b) { return max(abs(a.x - b.x), abs(a.y - b.y)); }
int D[17][(1 << 16) + 3], dis[17][17];
int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; char ipt;
	while (cin >> n >> m) {
		pl start = { -1,-1 }; deque<pl> nut;
		memset(D, 0x3f, sizeof D), memset(dis, 0, sizeof dis);
		cir(i, 0, n) cir(j, 0, m) {
			cin >> ipt;
			if (ipt == 'L') start = { i,j };
			if (ipt == '#') nut.push_back({ i,j });
		} nut.push_front(start);
		const int sz = nut.size(); const int kk = 1 << sz;
		cir(i, 0, sz) cir(j, 0, sz) dis[i][j] = dist(nut[i], nut[j]);
		D[0][1] = 0; int ans = 1e9 + 7;
		cir(i, 1, kk) cir(j, 0, sz){
			if (!(i & (1 << j))) continue;
			cir(k, 0, sz) {
				if (k == j || (!(i & (1 << k)))) continue;
				D[j][i] = min(D[j][i], D[k][i - (1 << j)] + dis[j][k]);
			}
		}
		cir(i, 1, sz) ans = min(ans, D[i][kk - 1] + dis[0][i]);
		cout << (sz == 1 ? 0 : ans) << endl;
	}
	return 0;
}

```
PS: [AC 记录](https://vjudge.net/solution/37178843) (Vjudge) 

---

## 作者：Rainsleep (赞：0)

**前置芝士：状压dp**

## 题意：

+ 给定一张 $n \times m$ 的地图，地图中 ``L`` 表示起始点，``#`` 表示该地存在一颗坚果。
+ 求拾取所有坚果，并且最多经过每个坚果一次，最后返回 ``L`` 的最短路径。

### 数据范围
+ $n,m < 20.$
+ 坚果数量 $\le 15.$ 

## $\text{Solution}$

题面令人感觉非常熟悉，极其类似于[P1171 售货员的难题](https://www.luogu.com.cn/problem/P1171)，实际上这一类问题，我们一般称作 $\text{TSP}$ 问题，即旅行商问题，详细可参考[百度百科](https://baike.baidu.com/item/TSP%E9%97%AE%E9%A2%98/840008)。

考虑使用状压dp，对于状态的设计，我们令 $dp_{i,j}$ 表示当状态为 $i$ 时，最后一个到达的点是 $j$ 的最短路径长度，此时考虑如何转移。

+ 以下我们约定 $dist_{i,j}$ 表示 $i,j$ 两点间的距离。

对于每个不为 $0$ 的状态来说，我们枚举其中的每一位作为最后一次到达的点，再枚举将要转移到的点，那么显然此时的最短路径长度即为**状态为 $i$ 时到达 $j$ 的最短路径长度$\ + \ dist_{j, k}$**，我们对于所有能转移的方案取 $\min$，既得状态转移方程：

$$dp[i | 2^{k-1}][k] = \min(dp[i | 2^{k-1}][k], dp[i][j] + dist[j][k])$$

其中的 $dist_{j,k}$ 需要我们提前预处理出任意两点间距离。

### 答案

实际上通过状态设计我们可以得到答案为 $dp[2^n-1][1]$，即经过所有点后最后回到起点的最短路径。

**但是这是错误的。**

实际上我们的答案应该是：
$$\min{{dp[2^n-1][i]+dist[i][1]}} \ (i \le n)$$

我们每个坚果**只能经过一次**，然而实际上**从终点转移到起点时，我们有可能经过了某些坚果，为了限制这种情况的发生，我们令答案为以每一颗坚果作为终点的最短路径长度 $+ \ dist_{i,1}$。**

### 一些注意的点

+ 本题中松鼠可以**斜着走**，注意到此时两点间距离并非曼哈顿距离，而是**两点间横纵坐标之差的较大值。**
+ 多组数据。

下面就是代码啦：
```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 20;
const int S = 1 << N;

int n, m;
typedef pair<int, int> PII;

#define x first
#define y second

PII pt[N];
int dist[N][N];

inline double max(int x, int y)
{
	return x > y ? x : y;
}

inline int abs(int x)
{
	return x < 0 ? -x : x;
}

inline int min(int x, int y)
{
	return x < y ? x : y;
}

inline int get_dis(PII a, PII b)
{
	int dx = abs(a.x - b.x);
	int dy = abs(a.y - b.y);
	return max(dx, dy);
}

int dp[S][N];

int main()
{
	
	while(~scanf("%d %d", &n, &m))
	{
		int cnt = 1;
	
		for(int i(1);i <= n; ++ i)
			for(int j(1);j <= m; ++ j)
			{
				char c;
				cin >> c;
				if(c == 'L')
					pt[1] = {i, j};
				else if (c == '#')
					pt[++ cnt] = {i, j};
			}
		
     //预处理两点间距离
		for(int i(1);i <= cnt; ++ i)
			for(int j(1);j <= cnt; ++ j)
				dist[i][j] = get_dis(pt[i], pt[j]);
			
		memset(dp, 0x3f3f3f3f, sizeof dp);
		
		for(int i(1);i <= cnt; ++ i)
			dp[1 << (i - 1)][i] = dist[1][i];
			
      //状态转移
		for(int i(1);i < (1 << cnt); ++ i)
			for(int j(1);j <= cnt; ++ j)
				if(i & (1 << (j - 1)))
					for(int k(1);k <= cnt; ++ k)
						if(!(i & (1 << (k - 1))))
							dp[i | (1 << (k - 1))][k] = min(dp[i | (1 << (k - 1))][k], dp[i][j] + dist[j][k]);
		
		//return 0;
		
		int res = INT_MAX;
		
     //上文中对答案的分析
		for(int i(1);i <= cnt; ++ i)
			res = min(res, dp[(1 << cnt) - 1][i] + dist[i][1]);
			
		printf("%d\n", res);
	}
	
	return 0;
}
```





---

## 作者：Wilson_Lee (赞：0)

~~很好奇这道题是怎么评成黑的……~~

这明显是一道货郎担板子，看数据范围直接上状压 dp。

首先预处理图：两两之间连边，边权为 $\max\{|x_i-x_j|,|y_i-y_j|\}$。

然后 dp，转移方程（这里用刷表法）：

$dp[S][i]$ 表示当前走的点集为 $S$，最后一个点为 $i$，走的最短路程为多少。

则有： $dp[S][i]=\min\{dp[S-2^j][j]+G[j][i]\},i,j\in S$。

讲完了，一道非常简单的状压不知为啥评成黑题。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define x first
#define y second
typedef pair<int,int> pa;
const int MAXN=25;
char maps[MAXN][MAXN];
int G[16][16],dp[1<<16][16];
pa pos[16];
int main()
{
    int n,m;
    while(scanf("%d %d",&n,&m)!=EOF)
    {
        for(int i=1;i<=n;++i) scanf("%s",maps[i]+1);
        int cnt=0;
        for(int i=1;i<=n;++i)
            for(int j=1;j<=m;++j)
                if(maps[i][j]=='#') pos[++cnt]={i,j};
                else if(maps[i][j]=='L') pos[0]={i,j};
        if(!cnt)
        {
            printf("0\n");
            continue;
        }
        ++cnt;
        for(int i=0;i<cnt;++i)
            for(int j=i+1;j<cnt;++j)
                G[i][j]=G[j][i]=max(abs(pos[i].x-pos[j].x),abs(pos[i].y-pos[j].y));
        memset(dp,0x3f,sizeof(dp));
        dp[1][0]=0;
        for(int i=1;i<(1<<cnt);++i)
        {
            for(int j=0;j<cnt;++j)
            {
                if(!(i&(1<<j))) continue;
                for(int k=0;k<cnt;++k)
                {
                    if(i&(1<<k)) continue;
                    dp[i|(1<<k)][k]=min(dp[i|(1<<k)][k],dp[i][j]+G[j][k]);
                }
            }
        }
        int ans=0x3f3f3f3f;
        for(int i=1;i<cnt;++i) ans=min(ans,dp[(1<<cnt)-1][i]+G[i][0]);
        printf("%d\n",ans);
    }
    return 0;
}
```


---

## 作者：Ray662 (赞：0)

[洛谷 传送门](https://www.luogu.com.cn/problem/UVA10944) | [UVA 传送门](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=21&page=show_problem&problem=1885)

[更好的阅读体验](https://www.luogu.com.cn/blog/sunrize/solution-uva10944)

题目大意：

- 有 $n$ 个城市，两两之间均有道路直接相连。给出每两个城市 $i$ 和 $j$ 之间的道路长度 $l_{i, j}$；

- 求一条经过每个点一次且仅一次，最后回到起点的路线，使得道路的总长度最短；

- $n \le 15$，城市编号为 $0 \sim (n - 1)$。

---

### 分析

我写的是记忆化状压 DP。

由于每个点有且仅有一次被经过，且图中的点是两两直接相连，所以每个点的地位是相同的。

所以，为了简化题目，我们从 $0$ 号点出发。

状态设计：$f(i, st)$，当前在 $i$，还需访问集合 $st$ 中的点各一次后回到 $0$ 的最短长度。

方程如下：

$$
f(i, st) = min\{f(j, st - \{j\}) + \text{dist}(i, j) | j \in st\}
$$

其中，$\text{dist}(i, j)$ 表示 $i, j$ 两点的距离。

注意这里是**曼哈顿距离**，也就是 $\text{dist}(i, j) = |x_i - x_j| + |y_i - y_j|$。

注意**初始化**：$f(i, \emptyset) = \text{dist}(0, i)$。

最终答案是 $f(0, \{1, 2, 3, \cdots (n - 1)\})$。

---

总体复杂度 $O(n^22^n)$。

AC 代码：

```cpp
#include <bits/stdc++.h>
#define _all(i, a, b) for (int i = (int)a; i <= (int)b; i ++ )
using namespace std;
const int N = 16, INF = 2e9;
int n, m, t, f[N][1 << N];
struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) { }  // 构造一个新的点
};
vector<Point> G;
int dist(int i, int j) {
    const Point & pi = G[i], & pj = G[j];
    return max(abs(pi.x - pj.x), abs(pi.y - pj.y));
}  // 计算距离
int dp(int i, int s) {
    int & F = f[i][s];
    if (F != -1) return F;
    F = INF;
    if (s == 0) return F = dist(i, 0);
    _all (j, 0, t - 1)  if (i != j && ((1 << j) & s))  F = min(F, dp(j, s ^ (1 << j)) + dist(i, j));
    return F;
}  // 记忆化
int main() {
    ios::sync_with_stdio(false), cin.tie(0);
	string str;
    while (cin >> n >> m) {
    	G.clear();
        memset(f, -1, sizeof(f));
        _all (i, 0, n - 1) {
            cin >> str;
            _all(j, 0, m - 1)  if (str[j] != '.')  G.push_back(Point(i, j));
        }
        t = G.size();
        if (t == 1)  puts("0");
        else  printf("%d\n", dp(0, (1 << t) - 1));
    }
    return 0;
}
```

---

