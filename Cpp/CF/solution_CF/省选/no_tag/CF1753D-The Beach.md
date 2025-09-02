# The Beach

## 题目描述

## 题目大意

有一个 $n\times m$ 的网格图，场地上有许多不可移动的障碍，标记为 `#`，还有一些可以移动的障碍，如果他是横着的，定义它的一边为 `L`，另一边为 `R`；否则定义它的上边为 `U`，下边为 `D`，现在需要在这个网格图中空出一个 $1\times 2$ 的空位，可以移动的障碍移动如下：

- 选择固定它的一边，将其旋转 $90^\degree$，花费 $p$ 单位，前提是旋转后不准与其他障碍重合。
- 将其平移一个单位，花费 $q$ 单位，前提是平移后不准与其他障碍重合。

现在要求出在这个网格图里空出 $1\times 2$ 的空位，至少需要花费多少单位，如果不可能，输出 `-1`。

## 样例 #1

### 输入

```
2 5
5 2
.LR##
##LR.```

### 输出

```
4```

## 样例 #2

### 输入

```
2 3
4 5
LR.
#.#```

### 输出

```
-1```

## 样例 #3

### 输入

```
4 3
10 10
.LR
###
UU#
DD.```

### 输出

```
-1```

## 样例 #4

### 输入

```
3 6
10 7
.U##.#
#DLR##
.##LR.```

### 输出

```
24```

# 题解

## 作者：Alex_Wei (赞：13)

[相似题目](https://www.luogu.com.cn/problem/P7877)。

注意到一个位置可以空出来当且仅当对应的若干位置之一可以空出来，这种 **具有依赖关系** 的题目一看就是图论。

如果 $s_{i, j} = \texttt L$，那么从 $(i - 1, j + 1)$ 和 $(i + 1, j + 1)$ 向 $(i, j)$ 连边，权值为 $p$，表示如果 $(i, j)$ 要空出来，那么这两个位置需要有一个空出来，且花费 $p$ 的代价旋转这张床。同理，$(i, j + 2)$ 向 $(i, j)$ 连边，权值为 $q$。

对于 $s_{i, j}$ 为其它方向字符的情况同理。

我们发现连边只在 $i + j$ 奇偶性相同的位置之间进行，所以两张图互不影响。如果一张床的两个位置都要求被移动，我们可以先将对应目标位置变成空地，那么这张床周围与它四连通的位置有两个都是空地。此时可以只进行一次移动，然后就有 $1\times 2$ 的空地给我们摆放床了。

从 $s_{i, j} = \texttt .$ 的位置开始跑最短路，因为每条路径代表一个移动床的路径，所以 $f_{i, j}$ 表示为使得 $(i, j)$ 空出来的最小代价。我们发现连边枚举所有相邻位置 $(i, j), (i', j')(|i - i'| + |j - j'| = 1)$，则 $\min f_{i, j} + f_{i', j'}$ 即为所求。

时间复杂度 $\mathcal{O}(nm\log (nm))$。[代码](https://codeforces.com/contest/1753/submission/177583117)。

---

## 作者：stntn (赞：7)

## 简要题意

[原题有了](https://www.luogu.com.cn/problem/CF1753D)

## 最短路

这道题有个结论：

>**最后**对于每个障碍的两端操作后一定有至少一端位于原来的格子位置。

简单理解一下：若两端都移动则不移动比移动更优，因为如果都移动了相当于占了一个已经清空的 $2 \times n$ 方格，如果不移动，此时可直接将自己的椅子摆上去而减少花费。

假如我们知道把 $(i,j)$ 移为空地所需的花费，因为上述，所以**不存在把一个障碍移到其四联通格子的情况**，所以只需要找到 $\min \left \{ cost(i,j)+cost(i+1,j),cost(i,j)+cost(i,j+1) \right \}$，就行了。

建立源点 $s$，我们设 $cost(i,j)$ 为 $s \rightarrow (i,j)$ 的最短路，考虑建图。

- 若该点是空地，则连 $s \rightarrow (i,j)$ 边权 $0$，代表耗费 $0$ 代价将该点清空。

- 若该点是障碍的一端，则连 该点转 $90^{\circ} $ 到的位置 $\rightarrow (i,j)$ 边权 $p$，该点转 $180^{\circ} $ 到的位置 $\rightarrow (i,j)$ 边权  $q$，均代表将可旋转至点清空后即可将该点清空。

跑一边最短路统计答案即可。

```cpp
#include<bits/stdc++.h>
#define N 300010
#define int long long
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define tep(i,u) for(int i=head[u];~i;i=e[i].nxt)
#define INF 0x3f3f3f3f3f3f3f3f
#define id(i,j) ((i-1)*m+j)
#define pir pair<int,int>
#define mp(i,j) make_pair(i,j)
#define se second
using namespace std;
int n,m,v0,v1,s,head[N],cc,dis[N],ans=INF;
bool vis[N];
struct EDGE{int v,w,nxt;}e[N<<2];
inline void add_edge(int u,int v,int w)
{
	e[++cc]={v,w,head[u]};head[u]=cc;
}
string ch[N];
priority_queue<pir,vector<pir>,greater<pir> >q;
inline bool check(int x,int y)
{
	if(x<1||x>n||y<1||y>m||ch[x][y]=='#') return 0;
	return 1;
}
inline void dij(int s)
{
	rep(i,1,n*m) dis[i]=INF;
	q.push(mp(0,s));
	while(!q.empty())
	{
		int u=q.top().se;q.pop();
		if(vis[u]) continue;vis[u]=1;
		tep(i,u)
		{
			int v=e[i].v,w=e[i].w;
			if(dis[v]>dis[u]+w)
			{
				dis[v]=dis[u]+w;
				q.push(mp(dis[v],v));
			}
		}
	}
}
signed main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	memset(head,-1,sizeof(head));
	cin>>n>>m>>v0>>v1;s=n*m+1;
	rep(i,1,n) cin>>ch[i],ch[i]=' '+ch[i];
	rep(i,1,n) rep(j,1,m)
	{
		if(ch[i][j]=='.') add_edge(s,id(i,j),0);
		if(ch[i][j]=='L')
		{
			if(check(i-1,j+1)) add_edge(id(i-1,j+1),id(i,j),v0);
			if(check(i+1,j+1)) add_edge(id(i+1,j+1),id(i,j),v0);
			if(check(i,j+2)) add_edge(id(i,j+2),id(i,j),v1);
		}
		if(ch[i][j]=='R')
		{
			if(check(i-1,j-1)) add_edge(id(i-1,j-1),id(i,j),v0);
			if(check(i+1,j-1)) add_edge(id(i+1,j-1),id(i,j),v0);
			if(check(i,j-2)) add_edge(id(i,j-2),id(i,j),v1);
		}
		if(ch[i][j]=='U')
		{
			if(check(i+1,j+1)) add_edge(id(i+1,j+1),id(i,j),v0);
			if(check(i+1,j-1)) add_edge(id(i+1,j-1),id(i,j),v0);
			if(check(i+2,j)) add_edge(id(i+2,j),id(i,j),v1);
		}
		if(ch[i][j]=='D')
		{
			if(check(i-1,j+1)) add_edge(id(i-1,j+1),id(i,j),v0);
			if(check(i-1,j-1)) add_edge(id(i-1,j-1),id(i,j),v0);
			if(check(i-2,j)) add_edge(id(i-2,j),id(i,j),v1);
		}
	}
	dij(s);
	rep(i,1,n) rep(j,1,m) if(check(i,j))
	{
		if(check(i+1,j)) ans=min(ans,dis[id(i,j)]+dis[id(i+1,j)]);
		if(check(i,j+1)) ans=min(ans,dis[id(i,j)]+dis[id(i,j+1)]);
	}
	cout<<(ans==INF ? -1:ans)<<'\n';
	return 0;
}
```

---

## 作者：Genius_Star (赞：6)

## 思路：

注意到每一个障碍物的移动是相当于将一个空格移到另外一个地方，于是考虑以每一个空格能到的地方连边：

- 若 $s_{i,j}=L$，该障碍物有三种方式运动：

    - 平移：由 $[s_{i,j},s_{i,j+1}] \to [s_{i,j+1},s_{i,j+2}]$，即将 $s_{i,j}$ 这个位置空出来，将 $s_{i,j+2}$ 这个位置堵住，则我们可以 $(i,j+2) \to (i,j)$ 连一条边权为 $q$ 的单向边。
    
    - 顺时针旋转：由 $[s_{i,j},s_{i,j+1}] \to [s_{i-1,j+1},s_{i,j+1}]$，即将 $s_{i,j}$ 这个位置空出来，将 $s_{i-1,j+1}$ 这个位置堵住，则我们可以 $(i-1,j+1) \to (i,j)$ 连一条边权为 $p$ 的单向边。

    - 逆时针旋转：由 $[s_{i,j},s_{i,j+1}] \to [s_{i,j+1},s_{i+1,j+1}]$，即将 $s_{i,j}$ 这个位置空出来，将 $s_{i+1,j+1}$ 这个位置堵住，则我们可以 $(i+1,j+1) \to (i,j)$ 连一条边权为 $p$ 的单向边。

- 若 $s_{i,j}=R$，该障碍物有三种方式运动：

    - 平移：由 $[s_{i,j-1},s_{i,j}] \to [s_{i,j-2},s_{i,j-1}]$，即将 $s_{i,j}$ 这个位置空出来，将 $s_{i,j-2}$ 这个位置堵住，则我们可以 $(i,j-2) \to (i,j)$ 连一条边权为 $q$ 的单向边。
    
    - 顺时针旋转：由 $[s_{i,j-1},s_{i,j}] \to [s_{i,j-1},s_{i+1,j-1}]$，即将 $s_{i,j}$ 这个位置空出来，将 $s_{i+1,j-1}$ 这个位置堵住，则我们可以 $(i+1,j-1) \to (i,j)$ 连一条边权为 $p$ 的单向边。

    - 逆时针旋转：由 $[s_{i,j-1},s_{i,j}] \to [s_{i-1,j-1},s_{i,j-1}]$，即将 $s_{i,j}$ 这个位置空出来，将 $s_{i-1,j-1}$ 这个位置堵住，则我们可以 $(i-1,j-1) \to (i,j)$ 连一条边权为 $p$ 的单向边。

- 若 $s_{i,j}=U$，该障碍物有三种方式运动：

    - 平移：由 $[s_{i,j},s_{i+1,j}] \to [s_{i+1,j},s_{i+2,j}]$，即将 $s_{i,j}$ 这个位置空出来，将 $s_{i+2,j}$ 这个位置堵住，则我们可以 $(i+2,j) \to (i,j)$ 连一条边权为 $q$ 的单向边。
    
    - 顺时针旋转：由 $[s_{i,j},s_{i+1,j}] \to [s_{i+1,j},s_{i+1,j+1}]$，即将 $s_{i,j}$ 这个位置空出来，将 $s_{i+1,j+1}$ 这个位置堵住，则我们可以 $(i+1,j+1) \to (i,j)$ 连一条边权为 $p$ 的单向边。

    - 逆时针旋转：由 $[s_{i,j},s_{i+1,j}] \to [s_{i+1,j-1},s_{i+1,j}]$，即将 $s_{i,j}$ 这个位置空出来，将 $s_{i+1,j-1}$ 这个位置堵住，则我们可以 $(i+1,j-1) \to (i,j)$ 连一条边权为 $p$ 的单向边。

- 若 $s_{i,j}=D$，该障碍物有三种方式运动：

    - 平移：由 $[s_{i-1,j},s_{i,j}] \to [s_{i-2,j},s_{i-1,j}]$，即将 $s_{i,j}$ 这个位置空出来，将 $s_{i-2,j}$ 这个位置堵住，则我们可以 $(i-2,j) \to (i,j)$ 连一条边权为 $q$ 的单向边。
    
    - 顺时针旋转：由 $[s_{i-1,j},s_{i,j}] \to [s_{i-1,j-1},s_{i-1,j}]$，即将 $s_{i,j}$ 这个位置空出来，将 $s_{i-1,j-1}$ 这个位置堵住，则我们可以 $(i-1,j-1) \to (i,j)$ 连一条边权为 $p$ 的单向边。

    - 逆时针旋转：由 $[s_{i-1,j},s_{i,j}] \to [s_{i-1,j},s_{i-1,j+1}]$，即将 $s_{i,j}$ 这个位置空出来，将 $s_{i-1,j+1}$ 这个位置堵住，则我们可以 $(i-1,j+1) \to (i,j)$ 连一条边权为 $p$ 的单向边。

图建出来后，需要以每一个空格点为源点，跑单源最短路 Dijkstra 堆优化即可。

每次判断相邻两点都有空格到达的最短路径：$dis_{i,j}+dis_{i,j+1}$ 或 $dis_{i,j}+dis_{i+1,j}$。

时间复杂度为 $O(nm \log{nm})$。

**实现时注意判边界。**

## 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=300300;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
struct Node{
	ll y,x;
	bool operator<(const Node&rhs)const{
		return rhs.y<y;
	}
};
ll n,m,p,q,ans=1e18;
string s[N];
ll dis[N];
bool f[N];
priority_queue<Node> Q;
vector<pair<ll,ll>> E[N];
ll get(ll x,ll y){
	return (x-1)*m+y;
}
void add(ll u,ll v,ll w){
	E[u].push_back({v,w});
}
bool check(ll x,ll y){
	if(x<1||x>n||y<1||y>m)
	  return 0;
	if(s[x][y]=='#')
	  return 0;
	return 1;
}
void dijkstra(){
    while(!Q.empty()){
        Node t=Q.top();
        Q.pop();
        ll x=t.x;
        if(f[x])
          continue;
        f[x]=1;
        for(auto i:E[x]){
        	ll y=i.first;
            if(dis[y]>dis[x]+i.second){
                dis[y]=dis[x]+i.second;
                if(!f[y])
                  Q.push({dis[y],y});
            }
        }
    }
}
int main(){
	memset(dis,0x3f,sizeof(dis));
	n=read(),m=read(),p=read(),q=read();
    for(int i=1;i<=n;i++){
    	getline(cin,s[i]);
    	s[i]=" "+s[i];
	}
    for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
		    ll id=get(i,j); 
			if(s[i][j]=='.'){
				dis[id]=0;
				Q.push({0,id});
			}
		    if(s[i][j]=='L'){
		    	if(check(i-1,j+1))
		          add(get(i-1,j+1),id,p);
		    	if(check(i+1,j+1))
		          add(get(i+1,j+1),id,p);
		        if(check(i,j+2))
		         add(get(i,j+2),id,q);
		    }
			else if(s[i][j]=='R'){
				if(check(i-1,j-1))
		          add(get(i-1,j-1),id,p);
		        if(check(i+1,j-1))
				  add(get(i+1,j-1),id,p);
				if(check(i,j-2))
		          add(get(i,j-2),id,q);
		    }
			else if(s[i][j]=='U'){
				if(check(i+1,j-1))
		          add(get(i+1,j-1),id,p);
		        if(check(i+1,j+1))
				  add(get(i+1,j+1),id,p);
				if(check(i+2,j))
		          add(get(i+2,j),id,q);
		    }
			else if(s[i][j]=='D'){
				if(check(i-1,j-1))
		          add(get(i-1,j-1),id,p);
		        if(check(i-1,j+1))
				  add(get(i-1,j+1),id,p);
				if(check(i-2,j))
		          add(get(i-2,j),id,q);
		    }
	    }
	}
	dijkstra();
    for(int i=1;i<=n;i++){
	    for(int j=1;j<=m;j++){
	        if(i!=n) 
		      ans=min(ans,dis[get(i,j)]+dis[get(i+1,j)]);
	        if(j!=m)
			  ans=min(ans,dis[get(i,j)]+dis[get(i,j+1)]);
	    }
	}
    write(ans==1e18?-1:ans);
	return 0;
}
```

---

## 作者：Liuxizai (赞：3)

[My Blog](https://liuxizai.ac.cn/archives/solution-codeforces-round-829.html)

我猜想每张床最多只会被移动一次，如果有这个结论，这个题就很好做了，过程就像是在模拟寻找增广路。

对于每张床，每次移动可以被视作是，固定一个端点，释放一个格子，再占用一个格子，那么我们考虑枚举这个端点，**将占用的格子向释放的格子连长度为移动费用的边**，这样从任意一个空闲格到某个被占用格子的最短路长度就是释放这个空闲格的代价。

那么我们可以将图建出来后，将所有空闲点丢到队列里一起跑 Dijkstra，注意这不是多源最短路，是到任意一点的最短距离，所以可以一起跑。

于是我们可以枚举新来的床放的位置，将释放两个格子的费用加起来，取最小值即可。

复杂度 $O(nm\log(nm))$。

问题在于，释放这两个格子对应的路径又没有可能冲突。

考虑对网格黑白染色，不难发现我们的连边都在同色格子之间，而一张床占用的两个格子是异色的，所以释放路径一定不会冲突。

另外我们考虑能不能感性证明一下每张床最多只会被移动一次。

对于两次平移或者一次平移加上一次旋转的组合，也就是这样的情况：

![829-1](https://cos.liuxizai.ac.cn/829-1.png)

我们想要将橙色块移到蓝色块处，如果蓝色块本身没有被占用，那么我们的移动很劣，因为新床可以被直接放到蓝色块处。

如果蓝色块中任意部分被占用，我们就要将其释放，然后将橙色块移过去，容易发现这还是劣，因为蓝色块释放后就能够放新床了。

接下来考虑最复杂的 T 型情况：

![829-2](https://cos.liuxizai.ac.cn/829-2.png)

我们希望把 AB 通过两次旋转转到 BD 去，因为两次旋转的费用可能低于一次平移，我们的目的显然是释放 A。

假如 C 原本空闲，那么 AB 可以用一次移动旋转到 BC，这样更优。

假如 C 原本被占用，那么 AB 旋转到 BC 前，我们首先要释放 C。接下来，我们有必要将 BC 再旋转到 BD 当且仅当 C 再次被其他床占用，这种情况是不合法的，我们对格子的操作必须是一条链而不能是环，否则就构造不出有效的操作序列。所以 AB 还是可以用一次移动旋转到 BC。

我不知道以上证明是否严谨，但是我已经说服我自己相信这个结论了，如果有什么问题请务必告诉我。

```cpp
namespace Main{
    const int N = 300005;
    int n, m, p, q;
    ll dis[N];
    string s[N];
    vector<pair<int, int>> g[N];
    int m1[] = {0, 0, 1, -1};
    int m2[] = {1, -1, 0, 0};
    int bel[] = {0, 0, 1, 1};
    string dir = "RLDU";
    vector<int> free;
    bool vis[N];
    struct node{
        int u;
        ll dis;
        node() {}
        node(int u, ll dis): u(u), dis(dis) {}
        bool operator < (const node &b) const{
            return dis > b.dis;
        }
    };
    inline int id(int x, int y){
        return x * m + y;
    }
    void dijkstra(){
        priority_queue<node> q;
        memset(dis, 0x3f, sizeof(dis));
        for(int x: free){
            dis[x] = 0;
            q.emplace(x, 0);
        }
        while(!q.empty()){
            int u = q.top().u; q.pop();
            if(vis[u]) continue;
            vis[u] = true;
            for(pair<int, int> e: g[u]){
                int v = e.first, w = e.second;
                if(dis[u] + w < dis[v]){
                    dis[v] = dis[u] + w;
                    q.emplace(v, dis[v]);
                }
            }
        }
    }
    void Main(){
        input(n, m, p, q);
        for(int i = 0; i < n; i++) cin >> s[i];
        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++){
            if(s[i][j] == '.') free.push_back(id(i, j));
            if(s[i][j] == '.' || s[i][j] == '#') continue;
            int d = -1;
            for(int k = 0; k < 4; k++) if(dir[k] == s[i][j]) d = k;
            int x = i - m1[d], y = j - m2[d];
            for(int k = 0; k < 4; k++){
                if(k == d) continue;
                int nx = x + m1[k], ny = y + m2[k];
                if(nx < 0 || nx >= n || ny < 0 || ny >= m || s[nx][ny] == '#') continue;
                if(bel[d] == bel[k]) g[id(nx, ny)].emplace_back(id(i, j), q);
                else g[id(nx, ny)].emplace_back(id(i, j), p);
            }
        }
        dijkstra();
        ll ans = 1e18;
        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++){
            if(s[i][j] == '#') continue;
            if(s[i][j] != 'L' && j != m - 1 && s[i][j+1] != '#'){
                ans = min(ans, dis[id(i, j)] + dis[id(i, j + 1)]);
            }
            if(s[i][j] != 'U' && i != n - 1 && s[i+1][j] != '#'){
                ans = min(ans, dis[id(i, j)] + dis[id(i + 1, j)]);
            }
        }
        if(ans == 1e18) puts("-1");
        else write(ans);
        return;
    }
} // namespace
```

---

## 作者：Sword_K (赞：3)

要加一张床，无非是通过一些操作使得空格凑在一起，那可以想到一个 dp：$f_{i,j}$ 表示把 $(i,j)$ 这个格子变成空格子的最小代价。如果 $(i,j)$ 初始为空，那么 $f(i,j)=0$；如果是障碍，那么 $f(i,j)=+\infty$；如果是床，那么需要通过操作挪床。两个操作的本质都是固定床的一端，移动另一端，所以 $(i,j)$ 一定是挪动的一端，那转移就只有 $3$ 种情况，分类讨论即可。

dp 顺序怎么办呢？容易发现这个 dp 相当于是一个最短路，直接以所有空格子为起点，跑多源 dij 即可。

答案就是 $\min_{|x_1-x_2|+|y_1-y_2|=1}\{f_{x_1,y_1}+f_{x_2,y_2}\}$。

直接实现就可以通过此题，但是有一个问题，这个题是要凑出两个空格子，而跑最短路的时候是跑的一个空格，那会不会出现最后的答案里，同一张床被操作两次的情况呢（显然是不合法的操作）？答案是否定的，因为一旦出现了这种情况，这张床周围至少有 $2$ 个空格，那么最多只需要操作这张床一次就可以把两个空格挪到一起。即不合法的答案一定不优。


---

## 作者：pengyule (赞：2)

第一个观察：一张床不会动两次。

第二个观察：目标是空格移动到相邻位置，空格才是我们关心的。

第三个观察：空格在棋盘染色后的网格中位置颜色不会改变。也就是说，最后相邻的两个空格，它们的移动互相独立。

结合三个观察，我们可以用每张床连 $6$ 条有向边的方法描述空格在移床前后的位置变化。以空格初始位置为源点做多源最短路，枚举最后的相邻位置的两格子最短路大小之和，取其最小值为答案。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=3e5+5;
int n,m,p,q;
string mp[N];
ll dis[N];
vector<pair<int,int> >G[N];
priority_queue<pair<ll,int> >Q;
inline int id(int i,int j){if(!i||!j||i>n||j>m||mp[i][j-1]=='#')return -1;return (i-1)*m+j;}
inline void adde(int u,int v,int w){if(u<0||v<0)return;G[u].push_back(make_pair(v,w));}
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>m>>p>>q;
	memset(dis,0x3f,sizeof dis);
	for(int i=1;i<=n;i++)cin>>mp[i];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(mp[i][j-1]=='L')adde(id(i-1,j+1),id(i,j),p),adde(id(i+1,j+1),id(i,j),p),adde(id(i,j+2),id(i,j),q);
			if(mp[i][j-1]=='R')adde(id(i-1,j-1),id(i,j),p),adde(id(i+1,j-1),id(i,j),p),adde(id(i,j-2),id(i,j),q);
			if(mp[i][j-1]=='U')adde(id(i+1,j-1),id(i,j),p),adde(id(i+1,j+1),id(i,j),p),adde(id(i+2,j),id(i,j),q);
			if(mp[i][j-1]=='D')adde(id(i-1,j-1),id(i,j),p),adde(id(i-1,j+1),id(i,j),p),adde(id(i-2,j),id(i,j),q);
			if(mp[i][j-1]=='.')Q.push(make_pair(dis[id(i,j)]=0,id(i,j)));
		}
	}
	while(!Q.empty()){
		int x=Q.top().second;Q.pop();
		for(auto e:G[x]){
			int y=e.first,z=e.second;
			if(dis[y]>dis[x]+z){
				dis[y]=dis[x]+z;
				Q.push(make_pair(-dis[y],y));
			}
		}
	}
	ll ans=1e18;
	for(int i=1;i<=n;i++)for(int j=1;j<m;j++)if(id(i,j)>=0&&id(i,j+1)>=0)ans=min(ans,dis[id(i,j)]+dis[id(i,j+1)]);
	for(int i=1;i<n;i++)for(int j=1;j<=m;j++)if(id(i,j)>=0&&id(i+1,j)>=0)ans=min(ans,dis[id(i,j)]+dis[id(i+1,j)]);
	cout<<(ans==1e18?-1:ans)<<'\n';
}
```

---

## 作者：周子衡 (赞：2)

我们可以从“空格”的视角来考虑床的移动。例如，对于一张横放的床，如果它正右方的格子是空的，那么我们可以以 $q$ 的代价，将空格变成这张床占据的两个格子中左边的那一个。而最终我们的目标是让两个空格相邻。下面的示意图有助于辅助理解。

![](https://cdn.luogu.com.cn/upload/image_hosting/0nhwtwdp.png)

考虑按上图的方式建出有向图来，并用最短路算法计算出每个点变成空地的最小代价。我们断言答案即为所有相邻的方格对中，代价和的最小值。

证明的话，首先容易证出这是答案的下界，我们接着需要说明答案不超过这个值。考虑一对相邻的方格，我们追踪两个格子各自变成空格的过程。如果这个过程中出现的矛盾，可以发现一定已经出现了两个相邻空格，与最小性矛盾。

时间复杂度 $O(nm\log nm)$。

```cpp
#include<cstdio>
#include<vector>
#include<queue>

using namespace std;

#define ID(i,j)(((i)-1)*m+j)

const long long INF=1e18;

char mp[400000];
long long dis[400000];bool vis[400000];

vector<pair<int,int> > ed[400000];

int main()
{
	int n=0,m=0;scanf("%d%d",&n,&m);
	long long p=0,q=0;scanf("%lld%lld",&p,&q);
	
	priority_queue<pair<long long,int> > pq;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			scanf(" %c",&mp[ID(i,j)]);
			dis[ID(i,j)]=INF;
			
			//puts("??");
			if(mp[ID(i,j)]=='.'){dis[ID(i,j)]=0;pq.push(make_pair(0,ID(i,j)));}
			else if(mp[ID(i,j)]=='R')
			{
				if(j-2>=1)ed[ID(i,j-2)].push_back(make_pair(ID(i,j),q));
				if(i-1>=1)ed[ID(i-1,j-1)].push_back(make_pair(ID(i,j),p));
				if(i+1<=n)ed[ID(i+1,j-1)].push_back(make_pair(ID(i,j),p));
			}
			else if(mp[ID(i,j)]=='L')
			{
				if(j+2<=m)ed[ID(i,j+2)].push_back(make_pair(ID(i,j),q));
				if(i-1>=1)ed[ID(i-1,j+1)].push_back(make_pair(ID(i,j),p));
				if(i+1<=n)ed[ID(i+1,j+1)].push_back(make_pair(ID(i,j),p));
			}
			else if(mp[ID(i,j)]=='U')
			{
				if(i+2<=n)ed[ID(i+2,j)].push_back(make_pair(ID(i,j),q));
				if(j-1>=1)ed[ID(i+1,j-1)].push_back(make_pair(ID(i,j),p));
				if(j+1<=m)ed[ID(i+1,j+1)].push_back(make_pair(ID(i,j),p));
			}
			else if(mp[ID(i,j)]=='D')
			{
				if(i-2>=1)ed[ID(i-2,j)].push_back(make_pair(ID(i,j),q));
				if(j-1>=1)ed[ID(i-1,j-1)].push_back(make_pair(ID(i,j),p));
				if(j+1<=m)ed[ID(i-1,j+1)].push_back(make_pair(ID(i,j),p));
			}
		}
	}
	
	while(!pq.empty())
	{
		int u=pq.top().second;pq.pop();
		if(vis[u])continue;vis[u]=1;
		for(int i=0;i<ed[u].size();i++)
		{
			int v=ed[u][i].first;
			if(dis[v]>dis[u]+ed[u][i].second)
			{
				dis[v]=dis[u]+ed[u][i].second;pq.push(make_pair(-dis[v],v));
			}
		}
	}
	
	long long ans=INF;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)
	{
		if(i<n)ans=min(ans,dis[ID(i,j)]+dis[ID(i+1,j)]);
		if(j<m)ans=min(ans,dis[ID(i,j)]+dis[ID(i,j+1)]);
	}
	printf("%lld",ans==INF?-1:ans);
}
```

---

## 作者：GalwayGirl (赞：1)

## Solution

- 一开始觉得是贪心，直到我看到最后一个样例点才停止了这种错误的想法，因为我发现如果想把一个被障碍覆盖的格子空出来，还得将障碍移到另外一个空的格子里，试想一下如果没有另外的空格子了，那么就得将那些格子做相同的决策，这样一来就会有很多个从前面转移的决策，所以又可以联想到 dp，设 $f_{i,j}$ 为将 $(i,j)$ 格子空出来的最小代价，接下来考虑如何转移。

- 因为数据范围较大，转移时不能暴力去枚举前面的决策点，也不好去枚举。为了将这些决策点联系在一起，还有一个方法：建边，然后从每个本就空着的格子为起点跑最短路，接下来考虑如何建边。

- 我们先来讨论竖着的障碍：
```cpp
0 1 2 3 4 5
1 . . . . .
2 . . U . .
3 . . D . .
4 . . . . .
```
可以看见 U 为 $(2,3)$，D 为 $(3,3)$，在这里就只讨论 U：
1. 固定 D点，将 U 顺时针旋转 $90$ 度，代价为 $p$ ，所以 dp 是这样转移：

$$f_{2,3}=\min f_{3,4}+p$$

那就可以建一条从 $(3,4)$ 到 $(2,3)$ 边权为 $p$ 的有向边。

2. 固定 D点，将 U 逆时针旋转 $90$ 度，代价为 $p$ ，所以 dp 是这样转移：

$$f_{2,3}=\min f_{3,2}+p$$

那就可以建一条从 $(3,2)$ 到 $(2,3)$ 边权为 $p$ 的有向边。

3. 上下平移，这就有点不好处理，但其实是可以发现这个操作相当于是固定 D 点，将 U 旋转 $180$ 度，代价为 $q$，所以 dp 是这样转移：

$$f_{2,3}=\min f_{4,3}+q$$

那就可以建一条从 $(4,3)$ 到 $(2,3)$ 边权为 $q$ 的有向边。

4. 左右平移，但其实不用考虑，想想看这个障碍是竖着的，可以直接左右平移说明左右存在 $1\times2$ 的空位，那么答案就是 $0$，所以不用建边。

-  横着的障碍也是一样的，在此就不过多赘述。

最后贴上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+100,M=1e7;
const int dx[]{0,1,0,-1},dy[]={1,0,-1,0};
string a[N];
int n,m,cnt,head[N],c;
long long p,q,dis[N],min_=1e18;
map<pair<int,int>,int>id;
bool vis[N];
struct hh{
    int id;long long val;
    bool operator<(const hh&a)const{
        return a.val<val;
    }
};
struct xzh{
    int next,to,w;
}edge[M];
void add(int u,int v,int w){
    c++;
    edge[c].next=head[u];
    edge[c].to=v;
    edge[c].w=w;
    head[u]=c;
}
void Dij(){
    priority_queue<hh>q;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]=='.'){
                int x=id[make_pair(i,j)];
                q.push({x,0});dis[x]=0;
            }
        }
    }
    while(!q.empty()){
        int now=q.top().id;q.pop();
        if(vis[now])continue;
        vis[now]=true;
        for(int i=head[now];i;i=edge[i].next){
            int v=edge[i].to;
            if(dis[now]+edge[i].w<dis[v]){
                dis[v]=dis[now]+edge[i].w;
                q.push({v,dis[v]});
            }
        }
    }
}
void work(int x,int y){
    for(int i=0;i<4;i++){
        int xx=x+dx[i],yy=y+dy[i];
        if(xx<0||xx>=n||yy<0||yy>=m||a[xx][yy]=='#')continue;
        min_=min(min_,dis[id[make_pair(x,y)]]+dis[id[make_pair(xx,yy)]]);
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m>>p>>q;
    for(int i=0;i<n;i++)cin>>a[i];
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cnt++;id[make_pair(i,j)]=cnt; 
            dis[cnt]=1e18;
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]=='U'){
                if(a[i+1][j+1]!='#')add(id[make_pair(i+1,j+1)],id[make_pair(i,j)],p);
                if(a[i+2][j]!='#')add(id[make_pair(i+2,j)],id[make_pair(i,j)],q);
                if(j&&a[i+1][j-1]!='#')add(id[make_pair(i+1,j-1)],id[make_pair(i,j)],p);
            }
            if(a[i][j]=='D'){
                if(i&&a[i-1][j+1]!='#')add(id[make_pair(i-1,j+1)],id[make_pair(i,j)],p);
                if(i>=2&&a[i-2][j]!='#')add(id[make_pair(i-2,j)],id[make_pair(i,j)],q);
                if(i&&j&&a[i-1][j-1]!='#')add(id[make_pair(i-1,j-1)],id[make_pair(i,j)],p);
            }
            if(a[i][j]=='L'){
                if(i&&a[i-1][j+1]!='#')add(id[make_pair(i-1,j+1)],id[make_pair(i,j)],p);
                if(a[i][j+2]!='#')add(id[make_pair(i,j+2)],id[make_pair(i,j)],q);
                if(a[i+1][j+1]!='#')add(id[make_pair(i+1,j+1)],id[make_pair(i,j)],p);
            }
            if(a[i][j]=='R'){
                if(i&&a[i-1][j-1]!='#')add(id[make_pair(i-1,j-1)],id[make_pair(i,j)],p);
                if(j>=2&&a[i][j-2]!='#')add(id[make_pair(i,j-2)],id[make_pair(i,j)],q);
                if(j&&a[i+1][j-1]!='#')add(id[make_pair(i+1,j-1)],id[make_pair(i,j)],p);
            }
        }
    }
    Dij();
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            work(i,j);
    if(min_==1e18)cout<<-1;
    else cout<<min_;
    return 0;
}
```
祝大家 NOIP RP++


---

## 作者：ningago (赞：1)

操作有两种：翻转和平移。先换一种角度来考虑平移：翻转两次（因为床的两端本质无区别）。

容易发现一张床的两头不能都被操作，否则就一定空出了一块 $1\times 2$ 的地，这肯定是劣于不移动的。

所以记 $dp_{i,j}$ 表示 $(i,j)$ 上没有床的最小代价。

显然 $\forall a_{i,j}= \text{空地}$，$dp_{i,j}=0$。

否则，$dp_{i,j}=\min_{\text{(i,j)能操作到(ci,cj)}}\{dp_{ci,cj}+\text{操作代价p或q}\}$。

使用 dijkstra 算法即可。

答案就是 $\min_{\text{(x,y)与(z,w)相邻}}\{dp_{x,y}+dp_{z,w}\}$。

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

#define N 300010
#define int long long
#define id(x,y) (((x) - 1) * m + (y))

int n,m,p,q;
int S;
std::string mp[N];

bool cmp(int x,int y)
{
	return x >= 1 && x <= n && y >= 1 && y <= m && mp[x][y] != '#';
}

int h[N],e[N << 2],ne[N << 2],v[N << 2],idx;

void add(int x,int y,int z)
{
	ne[++idx] = h[x];
	h[x] = idx;
	e[idx] = y;
	v[idx] = z;
}

struct node
{
	int id,ds;
	bool operator < (const node &B)const
	{
		return ds > B.ds;
	}
};

std::priority_queue <node> qu;
int dis[N];
bool vis[N];

signed main()
{
	memset(h,-1,sizeof(h));
	scanf("%lld%lld%lld%lld",&n,&m,&p,&q);
	for(int i = 1;i <= n;i++)
	{
		std::cin >> mp[i];
		mp[i] = '#' + mp[i];
	}
	S = 0;
	for(int i = 1;i <= n;i++)
	{
		for(int j = 1;j <= m;j++)
		{
			if(mp[i][j] == '.')
			{
				add(S,id(i,j),0); 
			}
			else if(mp[i][j] == 'L')
			{
				if(cmp(i - 1,j + 1))
					add(id(i - 1,j + 1),id(i,j),p);
				if(cmp(i + 1,j + 1))
					add(id(i + 1,j + 1),id(i,j),p);
				if(cmp(i,j + 2))
					add(id(i,j + 2),id(i,j),q);
			}
			else if(mp[i][j] == 'R')
			{
				if(cmp(i - 1,j - 1))
					add(id(i - 1,j - 1),id(i,j),p);
				if(cmp(i + 1,j - 1))
					add(id(i + 1,j - 1),id(i,j),p);
				if(cmp(i,j - 2))
					add(id(i,j - 2),id(i,j),q);
			}
			else if(mp[i][j] == 'U')
			{
				if(cmp(i + 1,j - 1))
					add(id(i + 1,j - 1),id(i,j),p);
				if(cmp(i + 1,j + 1))
					add(id(i + 1,j + 1),id(i,j),p);
				if(cmp(i + 2,j))
					add(id(i + 2,j),id(i,j),q);
			}
			else if(mp[i][j] == 'D')
			{
				if(cmp(i - 1,j - 1))
					add(id(i - 1,j - 1),id(i,j),p);
				if(cmp(i - 1,j + 1))
					add(id(i - 1,j + 1),id(i,j),p);
				if(cmp(i - 2,j))
					add(id(i - 2,j),id(i,j),q);
			}
		}
	}
	memset(dis,0x3f,sizeof(dis));
	dis[S] = 0;
	qu.push((node){S,0});
	while(!qu.empty())
	{
		int t = qu.top().id;
		qu.pop();
		if(vis[t])
			continue;
		vis[t] = 1;
		for(int i = h[t];~i;i = ne[i])
		{
			int nx = e[i];
			int z = v[i];
			if(dis[nx] > dis[t] + z)
			{
				dis[nx] = dis[t] + z;
				qu.push((node){nx,dis[nx]});
			}
		}
	}
	int ans = 0x3f3f3f3f3f3f3f3f;
	for(int i = 1;i <= n;i++)
	{
		for(int j = 1;j <= m;j++)
		{
			if(cmp(i,j + 1) && dis[id(i,j)] + dis[id(i,j + 1)] < ans)
				ans = dis[id(i,j)] + dis[id(i,j + 1)];	
			if(cmp(i + 1,j) && dis[id(i,j)] + dis[id(i + 1,j)] < ans)
				ans = dis[id(i,j)] + dis[id(i + 1,j)];
		}
	}
	printf("%lld\n",ans == 0x3f3f3f3f3f3f3f3f ? -1 : ans);
	return 0;
}
```

---

## 作者：OrezTsim (赞：1)

看到这种要先满足某个条件才能满足另一个条件的题目，想到图论。

假设当前有一个 $c_{i,j}=$ `L`，$c_{i,j+1}=$ `R`，那么如果要把其右移一格就需要满足 $c_{i,j+2}$ 当前空出来。也就是说，我们需要先满足 $(i,j+2)$ 的条件才能满足 $(i,j)$ 的条件。可以抽象为由 $(i,j+2)$ 向 $(i,j)$ 连一条边，代价为 $q$。

同理，对于旋转操作，以 $(i,j)$ 为中心，可以将 $(i,j+1)$ 旋转到 $(i-1,j)$，那么要使其满足 $(i-1,j+1)$ 和 $(i+1,j+1)$ 必须有一个地方能空出来，所以从 $(i-1,j+1)$ 和 $(i+1,j+1)$ 向 $(i,j)$ 连边，代价为 $p$。

同理可以这样处理 `R`，`U`，`D`。

对于原本为 `.` 的地方可以作为起点。

跑 Dijkstra 即可。复杂度 $O((nm)\log(nm))$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define pii pair <int, int>
using namespace std;

const int N = 3e5 + 10;
int T, n, m, p, q, dis[N]; bool vis[N];
vector <char> Map[N]; vector <pii> g[N];
priority_queue <pii, vector <pii>, greater <pii> > que;
inline int chg(int x, int y) { return (x - 1) * m + y; }

inline void solve() {
  cin >> n >> m >> p >> q;
  memset(dis, 0x3f, sizeof(dis));
  for (int i = 1; i <= n; ++i) Map[i].resize(m + 1);
  for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) cin >> Map[i][j];
  for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
    int id = chg(i, j); if (Map[i][j] == '.') que.push({dis[id] = 0, id});
    auto addEdge = [&] (int x, int y, int val) {
      if (x < 1 || x > n || y < 1 || y > m) return ;
      g[chg(x, y)].push_back({id, val});
    };
    if (Map[i][j] == 'L') {
      addEdge(i - 1, j + 1, p), addEdge(i + 1, j + 1, p);
      addEdge(i, j + 2, q);
    } else if (Map[i][j] == 'R') {
      addEdge(i - 1, j - 1, p), addEdge(i + 1, j - 1, p);
      addEdge(i, j - 2, q);
    } else if (Map[i][j] == 'U') {
      addEdge(i + 1, j - 1, p), addEdge(i + 1, j + 1, p);
      addEdge(i + 2, j, q);
    } else if (Map[i][j] == 'D') {
      addEdge(i - 1, j - 1, p), addEdge(i - 1, j + 1, p);
      addEdge(i - 2, j, q);
    }
  }
  while (!que.empty()) {
    int cur = que.top().second; que.pop();
    if (vis[cur]) continue; vis[cur] = true;
    for (auto [to, val]: g[cur]) {
      if (dis[to] > dis[cur] + val) {
        dis[to] = dis[cur] + val;
        que.push({dis[to], to});
      }
    }
  }
  int res = 1e18;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) {
      if (i ^ n) res = min(res, dis[chg(i, j)] + dis[chg(i + 1, j)]);
      if (j ^ m) res = min(res, dis[chg(i, j)] + dis[chg(i, j + 1)]);
    }
  cout << (res == 1e18? -1 : res) << endl;
  return ;
}

signed main() {
  ios_base::sync_with_stdio(false); cin.tie(0), cout.tie(0);
  T = 1; while (T--) solve();
  return 0;
}
```

---

## 作者：zzzYheng (赞：0)

#### 题意：

给定一个 $n\times m$ 的网格，网格中有一些不可移动障碍，标记为 `#`，还有一些 $1\times2$ 的可移动障碍。

可移动障碍的移动方法如下：

- 固定一个位置，将其旋转 $90$ 度，代价为 $p$，前提是旋转后不与其他障碍重合。
- 沿其长边方向平移一位，即横着的障碍只能横向平移，竖着的障碍只能纵向平移，代价为 $p$，前提是平移后不与其他障碍重合。

你的目标是在这个网格中空出一个 $1\times 2$ 的空位，求达到目标的最小移动代价，或报告无解。

数据范围：$n \times m \le 3\times 10^5,1 \le p,q \le 10^9$。

#### 思路：

首先障碍的移动可以看成空位的移动。

一个位于 $(x,y)$ 的空位可能移动到 $(x-2,y),(x-1,y-1),(x,y-2),(x-1,y+1),(x+2,y),(x+1,y-1),(x+2,y+2),(x+1,y+1)$ 这些位置，容易发现这些位置在黑白染色后都与 $(x,y)$ 同色。

所以考虑黑白染色，那么位于黑色位置的空位只能移动到黑色位置，位于白色位置的空位只能移动到白色位置，并且最终相邻的两个空位一定是一黑一白。

既然黑白空位都只能在内部移动，那么考虑它们的移动是否是相互独立的。

观察发现如果一个可移动障碍在移动黑色格子 $(a,b)$ 时被使用，在之后又在移动白色格子 $(c,d)$ 时又被使用，那么 $(a,b)$ 和 $(c,d)$ 一定是两个相邻的位置，我们无需移动 $(c,d)$，只要把黑色格子的状态撤销到移动 $(a,b)$ 前的状态，就达成目标了，这样就得到了一个更优的策略。

更严谨的，为了保证撤销合法，我们考虑第一次冲突移动即可。

所以如果出现了冲突移动那么这个策略一定不优，所以我们只需要分别考虑黑格和白格的移动，求出将空位移动到每个位置的最小代价，答案就是所有相邻位置的代价和的最小值。

如何计算将空位移动到每个位置的最小代价？最大的问题是图上存在的移动边会随障碍的移动而动态变化。

但是考虑不能既移动黑点又移动白点这个限制其实大大限制了障碍的移动范围，所以边动态变化的情况数其实不多。

比如对于一个位于 $(x,y),(x,y+1)$ 的障碍，在考虑 $(x,y)$ 所在颜色时，其 $(x,y+1)$ 这个端点一定是固定的，每次一定是将 $(x,y),(x-1,y+1),(x+1,y+1),(x,y+2)$ 这四个位置中的一个空位移动到这个障碍的另一个端点上，代价为 $p$ 或 $q$。

注意到每次移动一定会移动到这个障碍的另一个端点上，如果不是第一次移动这个障碍，那就会移动到上一次移动前空位所在的位置，这样的移动看起来就不太优。

事实确实如此，考虑最后一次对某个障碍进行多次移动，假设从 $(a,b)\to (c,d)$，那上次对障碍进行移动一定是从 $(c,d)\to (e,f)$，我们直接撤销操作到上一次对这个障碍移动前，因为之后的移动都是对障碍的首次移动，所以仍然能进行，这样就得到一个更优的解。

所以每个障碍至多移动一次，所以边根本不会动态变化，我们直接把图建出来跑多源最短路即可。

但是还有个问题就是在我们建的图上跑出来的路径还是可能走一个点多次，这是不合法的，因为端点已经被移走了。

但是由于一个障碍的所有边入点相同，如果走多次的话就会走出环，这在最短路中一定是不存在的。

这样这道题就解决了，时间复杂度 $\Theta(nm\log nm)$。

---

## 作者：bwartist (赞：0)

[可能更好的阅读体验](https://www.cnblogs.com/bwartist/p/18001194)

---

因为最后要找的是“腾出空位”的最小代价。

所以不妨把“障碍的移动”转化为“空位的移动”。

令 $f_{x,y}$ 为：使得 $(x,y)$ 为空，至少需要多少代价。

下面来找转移方程，显然转移方程与空格子移动有关。所以观察空格子移动的规律。

若当前格子 $(x,y)$ 为 `L`。

- 以 $(x,y+1)$ 为顶点顺时针或逆时针旋转当前障碍，就可以使 $(x,y)$ 格子变为空。

![](https://cdn.luogu.com.cn/upload/image_hosting/otmehm43.png)

上图中，粉色格子为当前障碍，白色格子为空。如果按逆时针旋转90度，粉色障碍就会发生如上的变化，那么右下角的空格子就会移动到左上角。所以从有 $f_{x,y}=f_{x+1,y+1}+p$。同理，如果按顺时针旋转90度，$(x+1,y-1)$ 的空格子可以移动到 $(x,y)$（读者不妨在草稿本上自己画一下图）。所以有 $f_{x,y}=f_{x+1,y-1}+p$。

- 如果把当前障碍整体向右平移一格，那么 $(x,y+2)$ 的格子可以移动到 $(x,y)$，所以有式子 $f_{x,y}=f_{x,y+2}+q$。

现在把三个式子合并起来，取最小值，就是 $f_{x,y}=\min(f_{x+1,y-1}+p,f_{x+1,y+1}+p,f_{x,y+2})$。我们现在就已经得到了当前格子为 `L` 的转移。

另外三种障碍的情况也差不多，画一画图就能写出式子。注意 `#` 的情况设为 $inf$，`.` 的情况设为 $0$。

---

好了我们已经有 DP 式子了，但是怎我们找不到一个合适的顺序取遍历所有格子呀？一个常见的 trick 是把 DP 转化成图论问题。

如果有 $f_{x,y}=f_{x',y'}+v$。那么就从 $(x',y')$ 向 $(x,y)$ 连一条值为 $v$ 的边，最后在整个图上跑最短路就可以了。

> 一个小细节，在实现代码时可以建立虚拟源点 $s$。如果我们把 $f_{x,y}$ 设为 $0$，就从 $s$ 向 $(x,y)$ 连接一条值为 $0$ 的边。


Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=3e5+5;
int n,m,p,q;
struct node{int to;ll w;};
bool operator <(const node &x,const node &y){return x.w>y.w;}
vector<node> G[MAXN];
ll dis[MAXN];
bool vis[MAXN];
void dij(){
    priority_queue<node> q;
    q.push({0,0});
    memset(dis,0x3f,sizeof(dis));
    dis[0]=0;
    while(!q.empty()){
        int u=q.top().to;q.pop();
        if(vis[u])  continue;
        vis[u]=1;
        for(node t:G[u]){
            int v=t.to;
            if(dis[v]>dis[u]+t.w){
                dis[v]=dis[u]+t.w;
                q.push({v,dis[v]});
            }
        }
    }
}
int dir[8][2]={{0,1},{0,-1},{1,0},{-1,0}};
const ll INF=0x3f3f3f3f3f3f3f3f;
int main(){
    #ifndef ONLINE_JUDGE
        freopen(".in","r",stdin);
        freopen(".out","w",stdout);
    #endif
    scanf("%d%d%d%d\n",&n,&m,&p,&q);
    vector<string> mp(n);
    for(int i=0;i<n;i++)   cin>>mp[i];
    auto get=[&](int x,int y)->int {return x*m+y+1;};
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            
            auto link=[&](int x,int y,int w)->void {
                if(x<0||y<0||x>=n||y>=m)    return;
                G[get(x,y)].push_back({get(i,j),1ll*w});
                // cerr<<get(i,j)<<" "<<get(x,y)<<" "<<w<<endl;
            };

            if(mp[i][j]=='L')   link(i-1,j+1,p),link(i+1,j+1,p),link(i,j+2,q);
            if(mp[i][j]=='R')   link(i-1,j-1,p),link(i+1,j-1,p),link(i,j-2,q);
            if(mp[i][j]=='U')   link(i+1,j-1,p),link(i+1,j+1,p),link(i+2,j,q);
            if(mp[i][j]=='D')   link(i-1,j-1,p),link(i-1,j+1,p),link(i-2,j,q);
            if(mp[i][j]=='.')   G[0].push_back({get(i,j),0});
        }
    }
    dij();
    ll ans=INF;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            for(int k=0;k<4;k++){
                int di=i+dir[k][0],dj=j+dir[k][1];
                if(di<0||di>=n||dj<0||dj>=m)    continue;
                ans=min(ans,dis[get(i,j)]+dis[get(di,dj)]);
            }
        }
    }
    if(ans==INF)    ans=-1;
    printf("%lld",ans);
    return 0;
}
```

---

