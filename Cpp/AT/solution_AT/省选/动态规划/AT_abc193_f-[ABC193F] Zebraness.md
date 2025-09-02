# [ABC193F] Zebraness

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc193/tasks/abc193_f

縦 $ N $ マス、横 $ N $ マスのマス目があります。  
 上から $ i $ 行目、左から $ j $ 列目のマスをマス $ (i,\ j) $ と表すことにします。 マス $ (i,\ j) $ の色の情報が文字 $ c_{i,j} $ により与えられます。  
`B` はマスが黒で塗られていることを、 `W` はマスが白で塗られていることを、 `?` はマスにまだ色が塗られていないことを表します。

高橋くんは、まだ色が塗られていないマスをそれぞれ黒または白で塗り、白黒のマス目を作ります。  
 マス目の **しまうま度** を、辺で接する黒マスと白マスの組の個数と定義します。  
 高橋くんが達成できるしまうま度の最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ <\ = N\ <\ =\ 100 $
- $ c_{i,\ j} $ は `B`, `W`, `?` のいずれか

### Sample Explanation 1

辺で接する黒マスと白マスの組は、マス $ (1,\ 2) $ とマス $ (2,\ 2) $ 、マス $ (2,\ 1) $ とマス $ (2,\ 2) $ の $ 2 $ 組あるので、しまうま度は $ 2 $ です。

### Sample Explanation 2

マス $ (3,\ 2) $ を白で塗ったときのしまうま度は $ 3 $ 、黒で塗ったときのしまうま度は $ 4 $ です。

## 样例 #1

### 输入

```
2
BB
BW```

### 输出

```
2```

## 样例 #2

### 输入

```
3
BBB
BBB
W?W```

### 输出

```
4```

## 样例 #3

### 输入

```
5
?????
?????
?????
?????
?????```

### 输出

```
40```

# 题解

## 作者：Reunite (赞：5)

提供一个更简便的思路和做法（官方题解做法）。

---
## 一
把每个点确定为 $W$ 或者 $B$，显然是最小割的形式，$?$ 代表可以随意选择点集，所以我们建一个源点汇点 $S,T$，把所有确定为 $W$ 点与 $S$ 连 $\inf$ 的边，表示颜色一定为 $W$，同理，确定为 $B$ 的与 $T$ 连 $\inf$ 的边，$?$ 的点不连 $S,T$ 表示可以任选，然后我们对于所有相邻的点连 $1$ 的双向边，表示如果两个点分属不同的颜色就造成 $1$ 的贡献。

然后你测一下样例，发现傻了，这代码跑出来的是最小值，而题目求的是最大值。联想最小割经典套路，转化为总价值减去最小花费的模型，这题中就是总相邻的边数减去最少相邻相等的点数。

然后你还没写，发现这样没法做，我们不能很好的刻画相等的代价。联想到网格相邻题的经典套路，我们把矩阵黑白染色，这样同色点互相无影响，那么我们可以把染成黑或白的格子进行反转，即 $W \leftarrow B$，$B \leftarrow W$，然后我们就把相邻相等有 $1$ 代价，转化为相邻不等有 $1$ 的代价了，然后套用上面的做法即可。最后再用总对数减一下就行了。

点数边数都是 $O(n^2)$ 的。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <atcoder/maxflow>
#define id(x,y) ((x-1)*n+y)
using namespace std;

int n;
int dx[]={0,-1,0,1,0};
int dy[]={0,0,1,0,-1};
char c[105][105];
atcoder::mf_graph <int> g(10005);

inline void add(int u,int v,int w){g.add_edge(u,v,w);}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%s",c[i]+1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if((i+j)&1){
				if(c[i][j]=='B') c[i][j]='W';
				else if(c[i][j]=='W') c[i][j]='B';
			}
	int S=n*n+1,T=S+1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(c[i][j]=='B') add(S,id(i,j),1e9);
			if(c[i][j]=='W') add(id(i,j),T,1e9);
			for(int k=1;k<=4;k++){
				int x=i+dx[k],y=j+dy[k];
				if(x<1||y<1||x>n||y>n) continue;
				add(id(i,j),id(x,y),1);
			}
		}
	}
	printf("%d\n",2*n*(n-1)-g.flow(S,T));

	return 0;
}
```

---

## 作者：Fan_sheng (赞：5)

太好了，直接来抢一波题解首杀。

看上去没有什么很直观的解法，于是考虑网络流。

**我们来修改一下题目条件**。如果这个题是“相邻两个**同色**格子贡献为 $1$”，就可以套用一个很典的最小割模型：[P4313 文理分科](https://www.luogu.com.cn/problem/P4313)。

为了防止有些同学不知道，还是讲一下这个模型：

把每个格子看作点，划分到 $S$ 集合表示白色，划分到 $T$ 集合表示黑色。

- 格子是 ```?```：不用连边。或者理解成和 $S$ 和 $T$ 各连一条边权为 $0$ 的边也行。

- 格子是 ```B```：和 $T$ 连一条边权为 $inf$ 的边。

- 格子是 ```W```：和 $S$ 连一条边权为 $inf$ 的边。

对于每对**相邻**格子 $X,Y$，新建两个虚点 $A,B$，连边如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/5hq7nv62.png)

这里，保留 $S$ 到 $A$ 的边代表 $X,Y$ 都为白色，产生 $1$ 贡献；保留 $B$ 到 $T$ 的边代表 $X,Y$ 都为黑色，产生 $1$ 贡献。

为什么呢？假如保留 $S$ 到 $A$ 的边，而 $X,Y$ 中某个点选了黑色，由于 $inf$ 边不能被割，此时 $S,T$ 一定联通，不满足条件。因此，这条边保留当且仅当 $X,Y$ 都选白色。$B$ 也是同理。

此时的答案就是“边权为 $1$ 的边数-最小割”。

然后你会说：就这，你把题目条件都改了，然后做出来了，好棒棒哦。

嗯你说的不无道理，如果按原题条件来做的话，上面的模型就失效了，你无法保证两个格子异色时产生贡献 $1$。

这个问题很好解决：我们令所有“行编号+列编号为奇数”的格子反色，比如 $s[1][2]=B$，就改成 $s[1][2]=W$，而 $s[2][2]$ 的颜色不改变。这样就转化成之前那个可以解决的问题了。由于贡献只和相邻格子颜色有关，是不会产生什么额外影响的。

做完啦，上 Code

```cpp
#include<bits/stdc++.h>
#define p(x,y) (((x)-1)*n+(y))
using namespace std;
const int maxn=5e4,inf=0x3f3f3f3f;
int n,tot,N;
char s[103][103];
namespace Edge{
	int head[maxn+5],flag=1;
	struct star{int to,nxt,val;}edge[3000005];
	inline void add(int u,int v,int val){
		edge[++flag]=(star){v,head[u],val},head[u]=flag;
	}
	inline void exadd(int u,int v,int val){add(u,v,val),add(v,u,0);}
}using namespace Edge;
namespace min_cut{
	const int S=0,T=maxn+1;
	int depth[maxn+5],now[maxn+5];
	inline bool bfs(){
		memcpy(now,head,sizeof(now));
		memset(depth,0,sizeof(depth));
		queue<int>q;
		q.emplace(S),depth[S]=1;
		while(q.size()){
			int h=q.front();q.pop();
			for(int i=head[h];i;i=edge[i].nxt){
				int v=edge[i].to;
				if(depth[v]||!edge[i].val)continue;
				depth[v]=depth[h]+1,q.emplace(v);
				if(v==T)return 1;
			}
		}return 0;
	}
	int dfs(int id,int flow){
		if(id==T||!flow)return flow;
		int tot=0;
		for(int &i=now[id];i;i=edge[i].nxt){
			int v=edge[i].to;
			if(depth[v]!=depth[id]+1||!edge[i].val)continue;
			int res=dfs(v,min(flow,edge[i].val));
			edge[i].val-=res,edge[i^1].val+=res;
			tot+=res,flow-=res;
		}return tot;
	}
	inline int Dinic(){
		int res=0;
		while(bfs())res+=dfs(S,inf);
		return res;
	}
}using namespace min_cut;
int main(){
	scanf("%d",&n),N=p(n,n);
	for(int i=1;i<=n;i++)scanf("%s",s[i]+1);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++){
		if(s[i][j]=='B')((i+j)&1)?exadd(S,p(i,j),inf):exadd(p(i,j),T,inf);
		if(s[i][j]=='W')((i+j)&1)?exadd(p(i,j),T,inf):exadd(S,p(i,j),inf);
		if(i<n){
			++N,exadd(S,N,1);
			exadd(N,p(i,j),inf),exadd(N,p(i+1,j),inf);
			++N,exadd(N,T,1);
			exadd(p(i,j),N,inf),exadd(p(i+1,j),N,inf);
		}
		if(j<n){
			++N,exadd(S,N,1);
			exadd(N,p(i,j),inf),exadd(N,p(i,j+1),inf);
			++N,exadd(N,T,1);
			exadd(p(i,j),N,inf),exadd(p(i,j+1),N,inf);
		}
	}printf("%d",N-p(n,n)-Dinic());return 0;
}
```


---

## 作者：Conan15 (赞：1)

网络流。

题目相当于把这些点**分割**成两个集合，因此想到**最小割**。\
把源点和确定为 `W` 的相连，确定为 `B` 的和汇点相连，容量均为 $\infty$。相邻格子之间连 $1$。但显然这样跑出来的是 **最小割**。

因此想到**容斥**，转为求总边数减去相等边数。但相等的边就不是很好做了。\
于是把网格染色，使得相邻的两个格子异色。就又变成了不同边数，可以最小割。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 15, M = 4e5 + 15;
const long long INF = 0x3f3f3f3f;

int n, S, T;
int mp[115][115]; char ch[115];
int h[N], e[M], w[M], ne[M], idx = 0;
void add(int a, int b, int c) { e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++; }
void addedge(int a, int b, int c) { add(a, b, c), add(b, a, 0); }

long long ans = 0;

int d[N], cur[N];
bool bfs() {
    queue<int> q; while (q.size()) q.pop();
    for (int i = 1; i <= T; i++) d[i] = 0;
    cur[S] = h[S], d[S] = 1, q.push(S);
    while (q.size()) {
        int u = q.front(); q.pop();
        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            if (!w[i] || d[v]) continue;
            d[v] = d[u] + 1, cur[v] = h[v];
            q.push(v);
            if (v == T) return 1;
        }
    }
    return 0;
}
long long dfs(int u, long long rest) {
    if (u == T) return rest;
    if (rest == 0) return 0;
    long long flow = 0;
    for (int i = cur[u]; ~i; cur[u] = i = ne[i]) {
        int v = e[i];
        if (d[v] != d[u] + 1 || w[i] == 0) continue;
        long long now = dfs(v, min(w[i] * 1ll, rest - flow));
        if (now == 0) d[v] = -1;
        else w[i] -= now, w[i ^ 1] += now, flow += now;
        if (flow == rest) break;
    }
    return flow;
}

const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
int id(int x, int y) { return (x - 1) * n + y; }

int main() {
    memset(h, -1, sizeof h);

    scanf("%d", &n), S = n * n + 1, T = n * n + 2;
    for (int i = 1; i <= n; i++) {
        scanf("\n %s", ch + 1);
        for (int j = 1; j <= n; j++)
            if (ch[j] == 'B') mp[i][j] = 1;
            else if (ch[j] == 'W') mp[i][j] = 0;
            else mp[i][j] = -1;
        for (int j = 1; j <= n; j++)
            if (((i + j) & 1) && ch[j] != '?') mp[i][j] ^= 1;
    }
    
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            if (mp[i][j] == 1) addedge(S, id(i, j), INF);
            if (mp[i][j] == 0) addedge(id(i, j), T, INF);
            for (int k = 0; k < 4; k++) {
                int x = i + dx[k], y = j + dy[k];
                if (x < 1 || y < 1 || x > n || y > n) continue;
                addedge(id(i, j), id(x, y), 1);
            }
        }
    
    while (bfs()) ans += dfs(S, INF);
    printf("%lld\n", 2 * n * (n - 1) - ans);
    return 0;
}
```

---

## 作者：Ryan_Adam (赞：1)

## 题解：AT_abc193_f [ABC193F] Zebraness
### Tag
网络流
### Solution
我们要求相邻格子颜色不同的最多个数，可以转化为总边数减去相邻格子颜色相同的最少个数。

我们发现颜色相同这一性质很难建图，所以我们将原图黑白染色，染后将黑色格子的原本颜色反转，这样就保证了原本相邻的颜色相同格子变为了颜色不同格子，接下来就直接求修改后图中相邻格子颜色不同的最少个数。这下就最小割板子了，将所有 `W` 格子与源点 $s$ 相连，所有 `B` 与汇点 $t$ 相连，边权都为 `INF`。再把图中存在相邻关系的边一连，在建好的图中跑 `Dinic` 即可。

注意处理中的细节，需要把二维上的点转换为一维编号。

### Code
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=1e6+5;
const int INF=0x3f3f3f3f;
int n,m,s,t,k;
struct edge
{
    int nxt,to,val;
}e[N];
int ans;
int now[N];
int dis[N],head[N],cnt=1;

void add(int u,int v,int w)
{
    // cout<<u<<" "<<v<<" "<<w<<endl;
    e[++cnt].to=v;
    e[cnt].val=w;
    e[cnt].nxt=head[u];
    head[u]=cnt;

    e[++cnt].to=u;
    e[cnt].val=0;
    e[cnt].nxt=head[v];
    head[v]=cnt;
}

bool bfs()
{
    memset(dis,-1,sizeof(dis));
    queue<int> q;
    q.push(s);
    dis[s]=0;
    now[s]=head[s];
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=e[i].nxt)
        {
            int v=e[i].to;
            if(e[i].val>0&&dis[v]==-1)
            {
                q.push(v);
                dis[v]=dis[u]+1;
                now[v]=head[v];
                if(v==t)return 1;
            }
        }
    }
    return 0;
}

int dfs(int x,int sum)
{
    if(x==t)return sum;
    int k,res=0;
    for(int i=now[x];i&&sum;i=e[i].nxt)
    {
        now[x]=i;
        int v=e[i].to;
        if(e[i].val>0&&dis[v]==dis[x]+1)
        {
            k=dfs(v,min(sum,e[i].val));
            if(k==0)dis[v]=-1;
            e[i].val-=k;
            e[i^1].val+=k;
            sum-=k;
            res+=k;
        }
    }
    return res;
}

void Dinic()
{
    while(bfs())
        ans+=dfs(s,INF);
    return ;
}

char mp[105][105];
int id(int i,int j){return (i-1)*n+j;}
int dd[15][15]={{1,0},{-1,0},{0,1},{0,-1}};

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)
            cin>>mp[i]+1;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if((i+j)&1)
            {
                if(mp[i][j]=='W')mp[i][j]='B';
                else if(mp[i][j]=='B')mp[i][j]='W';
            }
        }
    }
    s=0,t=n*n+1;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            // cout<<"*"<<i<<" "<<j<<" "<<id(i,j)<<endl;
            if(mp[i][j]=='B')add(s,id(i,j),INF);
            if(mp[i][j]=='W')add(id(i,j),t,INF);
            for(int k=0;k<4;k++)
            {
                if(i+dd[k][0]>=1&&i+dd[k][0]<=n&&j+dd[k][1]>=1&&j+dd[k][1]<=n)
                    add(id(i,j),id(i+dd[k][0],j+dd[k][1]),1);
            }
        }
    }
    Dinic();
    // cout << ans << endl;
    cout<<2*n*(n-1)-ans<<endl;
    return 0;
}
```

---

## 作者：Crazyouth (赞：0)

## 分析

一个较为典的网络流建模题。

考虑到相邻点颜色一致产生贡献比这题好做，所以把行加列和为奇数或偶数的格子反色（这里取奇数），这样能简化题目也能

首先必须让每个有颜色的格子归到一个集合里（即连源点或连汇点），不妨令黑格连源，白格连汇，`?` 格谁都不连。对于每一对相邻的点，如果我们需要让它们产生贡献，那么它们必然会同时归入一个点集且都不归入另一个点集，因此考虑跑最小割，并使得对于一个 `?` 格染色时，可以使它刚好进入其中一个点集，构造出来的图是这样的：

- 对于两个相邻格子 $U,V$，建立虚点 $W,X$，加边 $(S,W,1),(W,U,\infty),(W,V,\infty),(U,X,\infty),(V,X,\infty),(X,T,1)$，这里 $(u,v,w)$ 指一条由 $u$ 连向 $v$ 的容量为 $w$ 的边，$S,T$ 分别为源和汇，$\infty$ 为一个极大值（这里取 $2^{31}-1$）。

这样一来，如果 $U,V$ 都有颜色（即都和源汇中的一个有连边），那么跑最小割时自然会判断出 $U,V$ 是否同色。否则令 $U$ 是未上色的那个格子，假设此时 $V$ 有颜色，那么切断 $U$ 和 $T$ 的连通就必须切掉 $(S,W,1)$（因为容量为 $\infty$ 的边不会断掉），实际意义是让 $U$ 和 $V$ 染同色；另一种情况是 $U,V$ 此时都无色，那么 $(S,W,1),(X,T,1)$ 中有一条断掉即可，实际意义是 $U,V$ 都染了同一种颜色。

最后，由于跑最小割的时候只能切容量为 $1$ 的边，所以没被切掉的边代表着这个颜色被留下来了，也就是这条边产生了贡献。答案即容量为 $1$ 的边的数量减去被切断的边（即最小割）。

注：本题可以使用 ac-lib 进行网络流。

## AC Code
```cpp
#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;
#define int long long
const int INF=INT_MAX;
string ori[110],s[110];
int n,dx[2]={0,1},dy[2]={1,0};
int h(int x,int y)
{
	return (x-1)*n+y;
}
signed main()
{
	mf_graph<int> G(500010);
	int cnt,tp=0;
	cin>>n;
	cnt=n*n+1;
	for(int i=1;i<=n;i++) cin>>ori[i],ori[i]=' '+ori[i],s[i]=ori[i];
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if((i+j)&1)
			{
				if(ori[i][j]=='B') s[i][j]='W';
				if(ori[i][j]=='W') s[i][j]='B';
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(s[i][j]=='B') G.add_edge(0,h(i,j),INF);
			else if(s[i][j]=='W') G.add_edge(h(i,j),n*n+1,INF);
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			for(int k=0;k<2;k++)
			{
				int x=i+dx[k],y=j+dy[k];
				if(x>n||y>n) continue;
				G.add_edge(0,++cnt,1);
				G.add_edge(cnt,h(i,j),INF);
				G.add_edge(cnt,h(x,y),INF);
				G.add_edge(h(i,j),++cnt,INF);
				G.add_edge(h(x,y),cnt,INF);
				G.add_edge(cnt,n*n+1,1);
				tp+=2;
			}
		}
	}
	cout<<tp-G.flow(0,n*n+1);
}

---

