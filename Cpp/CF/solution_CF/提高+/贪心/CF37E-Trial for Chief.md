# Trial for Chief

## 题目描述

Having unraveled the Berland Dictionary, the scientists managed to read the notes of the chroniclers of that time. For example, they learned how the chief of the ancient Berland tribe was chosen.

As soon as enough pretenders was picked, the following test took place among them: the chief of the tribe took a slab divided by horizontal and vertical stripes into identical squares (the slab consisted of $ N $ lines and $ M $ columns) and painted every square black or white. Then every pretender was given a slab of the same size but painted entirely white. Within a day a pretender could paint any side-linked set of the squares of the slab some color. The set is called linked if for any two squares belonging to the set there is a path belonging the set on which any two neighboring squares share a side. The aim of each pretender is to paint his slab in the exactly the same way as the chief’s slab is painted. The one who paints a slab like that first becomes the new chief.

Scientists found the slab painted by the ancient Berland tribe chief. Help them to determine the minimal amount of days needed to find a new chief if he had to paint his slab in the given way.

## 样例 #1

### 输入

```
3 3
WBW
BWB
WBW
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 3
BBB
BWB
```

### 输出

```
1
```

# 题解

## 作者：Hercules (赞：5)

## 题解：CF37E Trial for Chief

看完第一眼手痒想直接爆搜做，冷静下来发现不可，得T飞，于是就想到了建图跑最短路。

估记很多人问为啥要建图啊，咋看出来的？~~（其实最主要还是多做题。。。）~~

对于相邻的位置来说，如果相邻的颜色不一样，那么显然需要一次涂色从而产生贡献。

我们通过遍历这个矩阵，可以判断出当前$s[i][j]$的上、下、左、右四个方向的颜色是否与它相同，

如果颜色相同，边权为0；如果颜色不同，边权为1。

### 注意：



1.用$SPFA$不要用$Dijkstra$，否则会$TLE$，边权不是1就是0；

2.注意初始时$dis[x]$为1，因为需要一次染色；

3.数组开的大一点，不要卡着题给的那个范围。

```
//#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>

const int MAXN = 7200;
const int INF = 0x3f3f3f3f;
bool vis[MAXN];
char s[55][55];
struct Edge {
	int x, y, z, nxt;
} e[MAXN << 1];
int dx[5] = {0, 0, 1, -1};
int dy[5] = {1, -1, 0, 0};
int n, m, cnt, tot, ans = INF, head[MAXN], dis[MAXN], NUM[55][55];

inline void add_edge(int x, int y, int z) {
	e[++cnt].x = x, e[cnt].y = y, e[cnt].z = z;
	e[cnt].nxt = head[x], head[x] = cnt;
}

inline void spfa(int nowx) {
	for (register int i = 1; i <= tot; i++)
		dis[i] = INF, vis[i] = false;
	std::queue< int > q;
	dis[nowx] = 1, vis[nowx] = true, q.push(nowx);
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (register int i = head[x]; i; i = e[i].nxt) {
			int to = e[i].y;
			if (dis[to] > dis[x] + e[i].z) {
				dis[to] = dis[x] + e[i].z;
				if (!vis[to])
					q.push(to), vis[to] = true;
			}
		}
		vis[x] = false;
	}
	int res = 0;
	for (register int i = 1; i <= n; i++)
		for (register int j = 1; j <= m; j++)
			if (s[i][j] == 'B')
				res = std::max(res, dis[NUM[i][j]]);
	ans = std::min(ans, res);
}

signed main() {
#ifndef ONLINE_JUDGE
#ifdef LOCAL
	freopen("testdata.in", "r", stdin);
	freopen("testdata.out", "w", stdout);
#endif
#ifndef LOCAL
	freopen("CF37E.in", "r", stdin);
	freopen("CF37E.out", "w", stdout);
#endif
#endif
	scanf("%d %d", &n, &m);
	for (register int i = 1; i <= n; i++)
		scanf("%s", s[i] + 1);
	for (register int i = 1; i <= n; i++)
		for (register int j = 1; j <= m; j++)
			NUM[i][j] = ++tot;
	for (register int i = 1; i <= n; i++) {
		for (register int j = 1; j <= m; j++) {
			for (register int k = 0; k < 4; k++) {
				int nowx = i + dx[k], nowy = j + dy[k];
				nowx = i + dx[k], nowy = j + dy[k];
				if (nowx < 1 or nowx > n or nowy < 1 or nowy > m)
					continue;
				if (s[i][j] == s[nowx][nowy])
					add_edge(NUM[i][j], NUM[nowx][nowy], 0);
				if (s[i][j] != s[nowx][nowy])
					add_edge(NUM[i][j], NUM[nowx][nowy], 1);
			}
		}
	}
	for (register int i = 1; i <= tot; i++)
		spfa(i);
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：jianhe (赞：4)

**upd**：修改了两处笔误。

第一次独立想出了一道 *2600，写篇题解纪念一下。

和 [qoj 5416](https://qoj.ac/problem/5416) 类似的思路，考虑将得到给定图案的过程 **倒过来** 做，则题面变成了：对于给定的图案，每次可以把一个相同颜色的四连通区域染成白色或黑色，求最少的染色次数使颜色均为白色。

那我们考虑给定图案中 **黑色图案组成的连通块**，其实要求的就是：把连通块 **合并** 所需的最少染色次数。

那么我们就对于每一个单元格，与周围四个方格连边，若颜色相同边权为 $0$，否则为 $1$。

然后跑最短路即可。注意 `dijkstra` 会被卡常，而 `spfa` 可轻松通过。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
const ll N=55,M=500010,inf=1e9;
ll n,m,px,py,ct,ans=1e9,h[M],dis[M],a[N][N];
ll dx[]={-1,0,0,1};
ll dy[]={0,-1,1,0};
bool vis[M];
char c;
vector<pair<ll,ll> > e[M];
bool check(ll x,ll y){return 1<=x&&x<=n&&1<=y&&y<=m;}
void add(ll u,ll v,ll w){e[u].push_back({v,w});}
void spfa(ll s){
	ll res=0;
	for(int i=1;i<=n*m;i++) dis[i]=inf,vis[i]=0;
	dis[s]=vis[s]=1;
	queue<ll> q;q.push(s);
	while(!q.empty()){
		int u=q.front();
    	q.pop(),vis[u]=0;
    	for(auto ed:e[u]){
      		int v=ed.fi,w=ed.se;
      		if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
        		if(!vis[v]) q.push(v),vis[v]=1;
      		}
    	}
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(!a[i][j]) res=max(res,dis[(i-1)*m+j]);
	ans=min(ans,res);
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			cin>>c;
			if(c=='W') a[i][j]=1;
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k=0;k<4;k++)
				if(check(px=i+dx[k],py=j+dy[k]))
					add((i-1)*m+j,(px-1)*m+py,(a[i][j]!=a[px][py]));
	for(int i=1;i<=n*m;i++) spfa(i);
	cout<<ans;
	return 0;
}
```

---

## 作者：XL4453 (赞：3)

### 题意：

给一张全白的图，每一次可以选一块连续的染成黑色或白色，求到给定的最终结果的最少染色次数。

---
### 解题思路：

提供一种不一样的理解方式。

由于原问题中是每一次是将一片染成一样的颜色，那么我们考虑这个过程的逆过程，也就是将最终状态还原到白色的，容易发现每一个正操作都有唯一的逆操作与之对应（也就是每一种涂色都可以还原）。

显然每一次涂色（还原）一定是涂连续的一整块，否则有可能会在后面要求重新补上，方案数一定不会更优。

那么每一次涂色就是将一个连续的块和两边的不一样的颜色连在了一起（注意这里可以重复在一块上操作，也就是样例一的那一种操作方式），考虑将所有的联通块连到一起，然后在每两个之间建立一条边权为 $1$ 的边，最后对于每一个点跑一遍最短路到最远的联通块的距离就是以这个点为第一次染色需要用的最少染色次数。

随后发现，其实没有必要那么复杂，求出联通块并将其连到一起其实可以直接用建立边权为 $0$ 的边来代替。  

本题数据范围很小，没有必要用堆优化。

---

注意不要用 next 作为变量名。

---
### 代码：
```cpp
#include<queue>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=500005;
int n,m,f[55][55],head[MAXN],next_[MAXN],num[MAXN],w[MAXN],d[MAXN],B,dx[5]={1,-1,0,0},dy[5]={0,0,1,-1},tot,ans=2147483647;
bool v[MAXN];
queue<int> q;
char c;
char get(){
	char c1=getchar();
	while(c1==' '||c1=='\n'||c1=='\r')c1=getchar();
	return c1;
}
int id(int x,int y){return (x-1)*m+y;}
void add(int x,int y,int z){
	next_[++tot]=head[x];head[x]=tot;num[tot]=y;w[tot]=z;
	next_[++tot]=head[y];head[y]=tot;num[tot]=x;w[tot]=z;
}
void SPFA(int s){
	for(int i=1;i<=n*m;i++)d[i]=1e9;
	q.push(s);
	d[s]=1;v[s]=1;
	while(!q.empty()){
		int now=q.front();
		q.pop();
		v[now]=0;
		for(int i=head[now];i;i=next_[i]){
			if(d[now]+w[i]<d[num[i]]){
				d[num[i]]=d[now]+w[i];
				if(v[num[i]]==0){
					q.push(num[i]);
					v[num[i]]=1;
				}
			}
		}
	}
	int now_ans=0;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	if(f[i][j]==0)
	now_ans=max(now_ans,d[id(i,j)]);
	ans=min(ans,now_ans);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++){
		c=get();
		if(c=='W')f[i][j]=1;
		else f[i][j]=0,B=1;
	}
	if(B==0)return 0&printf("0\n");
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	for(int k=0;k<=3;k++)
	if(i+dx[k]<=n&&i+dx[k]>=1&&j+dy[k]<=m&&j+dy[k]>=1)
	add(id(i,j),id(i+dx[k],j+dy[k]),(f[i][j]==f[i+dx[k]][j+dy[k]]?0:1));
	for(int i=1;i<=n*m;i++)SPFA(i);
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：i207M (赞：2)

~~此题竟然没有题解，赶快来一发~~

题意是给你一张$NM$的图，每个点有黑色和白色，初始全为白色，每次可以把一个相同颜色的连续区域染色，求最少的染色次数；

首先是结论：每个点向四个方向建边，如果颜色一样边权为0，否则为1，从每个点出发，跑一遍最短路，答案即为$min(maxDistoBlackPoint)+1$；（特判全白）

证明可以这么想：

每经过一个不同的颜色，就要多染一次色，于是图上的点到最远的黑点的距离+1就是至少染色的次数；

染色这样，先染距离<=mx的，再染<=ans-1...<=0的，一共mx+1次；

为啥是黑色？因为初始是白的；

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<stack>
#include<bitset>
#include<deque>
using namespace std;
#define ll long long
#define inf 0x3f3f3f3f
#define ri register int
#define il inline
#define fi first
#define se second
#define mp make_pair
#define pi pair<int,int>
#define mem0(x) memset((x),0,sizeof (x))
#define mem1(x) memset((x),0x3f,sizeof (x))
#define gc getchar
template<class T>void in(T &x) {
    x = 0; bool f = 0; char c = gc();
    while (c < '0' || c > '9') {if (c == '-') f = 1; c = gc();}
    while ('0' <= c && c <= '9') {x = (x << 3) + (x << 1) + (c ^ 48); c = gc();}
    if (f) x = -x;
}
#undef gc
#define N 10000
#define M N<<3
int n, m;
bool hvb;
bool p[N][N];
int ans = inf;
int xx[] = { -1, 0, 1, 0}, yy[] = {0, 1, 0, -1};
il getn(int x, int y) {
    return m * (x - 1) + y;
}
int v[M], u[M], w[M], nx[M];
int cnt, head[N];
il void add(int uu, int vv, int ww) {
    u[++cnt] = uu, v[cnt] = vv, w[cnt] = ww, nx[cnt] = head[uu];
    head[uu] = cnt;
}
int d[N];
int vis[N];
void spfa(int s) {
    mem1(d);
    mem0(vis);
    queue<int>q;
    d[s] = 0;
    vis[s] = 1;
    q.push(s);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (ri i = head[x]; i; i = nx[i]) {
            if (d[v[i]] > d[x] + w[i]) {
                d[v[i]] = d[x] + w[i];
                if (!vis[v[i]]) {
                    vis[v[i]] = 1;
                    q.push(v[i]);
                }
            }
        }
        vis[x] = 0;
    }
}
vector<int> bl;
signed main() {
    in(n), in(m);
    char tc[3];
    for (ri i = 1; i <= n; ++i) {
        for (ri j = 1; j <= m; ++j) {
            scanf("%1s", tc);
            p[i][j] = (tc[0] == 'B');
            hvb |= p[i][j];
            if (p[i][j]) bl.push_back(getn(i, j));
        }
    }
    if (!hvb) {
        puts("0");
        return 0;
    }
    for (ri i = 1; i <= n; ++i) {
        for (ri j = 1; j <= m; ++j) {
            for (ri k = 0; k < 4; ++k) {
                int tx = i + xx[k], ty = j + yy[k];
                if (tx < 1 || tx > n || ty < 1 || ty > m) continue;
                add(getn(i, j), getn(tx, ty), p[i][j] != p[tx][ty]);
            }
        }
    }
    for (ri i = 1; i <= n; ++i) {
        for (ri j = 1; j <= m; ++j) {
            int k = getn(i, j);
            spfa(k);
            int tmp = 0;
            for (ri h = 0, hi = bl.size(); h < hi; ++h) {
                tmp = max(tmp, d[bl[h]]);
            }
            ans = min(ans, tmp);
        }
    }
    printf("%d", ans + 1);
    return 0;
}
```

---

## 作者：thecold (赞：1)

[CF37E Trial for Chief](https://www.luogu.com.cn/problem/CF37E)

本题做法为最短路连边方式为每个点向上下左右四个点进行连边，如果颜色相同则为0，不同则为1.

原因：我们可以认为边权的含义是已经将当前节点染成目标颜色，将其相邻格子也染成目标颜色的所需代价，那么相同颜色的我们就一起染了不就好了

所以我们枚举最后一个染色的格子，跑一遍单源最短路

### 其中每跑一遍要记录一些最远的黑色格点的距离，并对每次枚举出来的结果取最小值。



------------

## 每次跑一边记录最远黑色格点是为了干啥呢？

为了看一下当我最后一次染色为（i ， j）时，所需要的最小代价。

## 而对这些最远黑色格点的距离取min干啥？

为了找到最优解

但是最后别忘了加1，因为我们枚举的那个点其实也是需要被染上色的

分为两种情况：

第一种是最后染上黑色，那肯定最后也是需要染色的

第二种是最后染成了白色，为什么这个时候可能成为最优解呢，我们看第一个样例即可

### 这个样例也就充分证明了为啥不是求连通块个数

所以最后一个枚举到的一定会染色，所以要ans + 1

# 但是全白就特判成0就好了


$$Code$$

```
#include<cstdio>
#include<cctype>
#include<algorithm>
#include<queue>
#include<cstring>
#include<map>
#include<vector>
using namespace std;
inline int read()
{
	int res = 0;
	char c;
	bool flag = true;
	c = getchar();
	while(!isdigit(c))
	{
		if(c == '-')	flag = false;
		c = getchar();
	}
	while(isdigit(c))
	{
		res = res * 10 + (c ^ 48);
		c = getchar();
	}
	return flag ? res : -res;
}
const int Max_n = 55;
char c[Max_n][Max_n];
int n , m , tmp , ans = 0x3f3f3f3f, dx[4] = {0 , 0 , 1 , -1} , dy[4] = {1 , -1 , 0 , 0} , dis[Max_n][Max_n];
int con[Max_n][Max_n][Max_n][Max_n];
struct node{
	int x , y;
	node(int a , int b)
	{
		x = a , y = b;
	}
	node()
	{
	}
};
vector<node> v[Max_n][Max_n];
bool vis[Max_n][Max_n];
int main()
{
	n = read() , m = read();
	for(int i = 0 ; i < n ; ++ i)
		scanf("%s" , c[i]);
	for(int i = 0 ; i < n ; ++ i)
		for(int j = 0 ; j < m ; ++ j)
			for(int k = 0 ; k < 4; ++ k)
			{
				int nexi = i + dx[k] , nexj = j + dy[k];
				if(nexi < 0 || nexi >= n || nexj < 0 || nexj >= m)	continue;
				v[i][j].push_back((node){nexi , nexj});
			}
	for(int i = 0 ; i < n ; ++ i)
		for(int j = 0 ; j < m ; ++ j)
		{
			memset(dis , 0x3f3f3f3f , sizeof(dis));
			memset(vis , false , sizeof(vis));
			tmp = 0;
			dis[i][j] = 1;
			deque<node> q;
			q.push_front(node(i , j));
			while(!q.empty())
			{
				node now = q.front();
				q.pop_front();
				if(vis[now.x][now.y])	continue;
				vis[now.x][now.y] = true;
				if(c[now.x][now.y] == 'B')	tmp = max(tmp , dis[now.x][now.y]);
				int sz = v[now.x][now.y].size();
				for(int i = 0 ; i < sz ; ++ i)
				{
					node nex = v[now.x][now.y][i];
					if(vis[nex.x][nex.y])	continue;
					dis[nex.x][nex.y] = min(dis[nex.x][nex.y] , dis[now.x][now.y] + (c[now.x][now.y] != c[nex.x][nex.y]));
					c[now.x][now.y] != c[nex.x][nex.y] ? q.push_back(nex) : q.push_front(nex);
				}
			}
			ans = min(ans , tmp);
		}
	printf("%d" , ans);
	return 0;
}
```


---

## 作者：JimmyLee (赞：0)

# 题目分析

## 题意

给一张全白的图，每次可以将一个四联通块染黑或染白，求转化到目标最少染色次数。

## 分析

考虑倒着想，由目标染回原图。

易得倒着染回去和正着染的最少**染色次数相同**。

所以我们考虑从最后的图入手。

---

考虑从某一个点 $(i,j)$ 开始染色。

尝试进行建图。

在同样的颜色间转移的代价是 $0$。

如果颜色不同，就需要至少进行一次染色，所以代价是 $1$。

建图跑最短路即可。

每次跑完后用距离最大的**黑**点更新答案。（因为原图是白色，所以只统计黑点）

并且默认一开始需染一次色，所以 $dis_s=1$。

---

发现边权只有 $0$ 和 $1$。

可以考虑使用 [0-1 BFS](https://oi-wiki.org/graph/bfs/#%E5%8F%8C%E7%AB%AF%E9%98%9F%E5%88%97-bfs) 求最短路。（其实用 0-1BFS 求的话可以不用建图）

时间复杂度 $O((nm)^2)$。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 52

string tmp;

int mp[maxn][maxn];

#define pos(i, j) (m*((i)-1)+j)
#define chk(i, j) ((i)&&(j)&&(i<=n)&&(j<=m))

vector<pair<int, int> > e[maxn*maxn];

deque<int> dq;
int dis[maxn*maxn];
int bfs(int x, int n, int m)
{
    memset(dis, 0x3f, sizeof dis);
    dis[x]=1;
    dq.emplace_back(x);
    while(!dq.empty())
    {
        auto u=dq.front();
        dq.pop_front();
        for(auto [v, w]:e[u])
            if(dis[v]>dis[u]+w)
            {
                dis[v]=dis[u]+w;
                if(w) dq.emplace_back(v);
                else dq.emplace_front(v);
            }
    }
    int ans=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(mp[i][j]) ans=max(ans, dis[pos(i, j)]);
    return ans;
    
}

int main()
{
    int n, m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>tmp;
        for(int j=1;j<=m;j++)
            mp[i][j]=(tmp[j-1]=='B');
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            if(chk(i-1, j)) e[pos(i, j)].emplace_back(pos(i-1, j), mp[i][j]!=mp[i-1][j]);
            if(chk(i+1, j)) e[pos(i, j)].emplace_back(pos(i+1, j), mp[i][j]!=mp[i+1][j]);
            if(chk(i, j-1)) e[pos(i, j)].emplace_back(pos(i, j-1), mp[i][j]!=mp[i][j-1]);
            if(chk(i, j+1)) e[pos(i, j)].emplace_back(pos(i, j+1), mp[i][j]!=mp[i][j+1]);
        }
    int ans=numeric_limits<int>::max();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            ans=min(ans, bfs(pos(i, j), n, m));
    cout<<ans;
}
```

---

