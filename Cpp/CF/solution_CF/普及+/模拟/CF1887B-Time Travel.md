# Time Travel

## 题目描述

### 题意简述

给定一张 $ n $ 个点的无向完全图和 $ t $ 组边集，边集 $ i $ 的大小为 $ m_i $。每到达一个结点，你都必须**至少**等待 $ 1 $ 秒，才能继续前进。每条边的通过时间都是 $ 0 $ 秒。第 $ i $ 秒时，边集 $ a_i $ 中的边可以通行，其余边不能通行。第 $ 0 $ 秒时，你从结点 $ 1 $ 出发。判断是否可以在 $ k $ 秒内到达结点 $ n $。如果可以，求出从结点 $ 1 $ 到结点 $ n $ 的最少用时。

注：当你在结点 $ 1 $ 时，也必须至少等待 $ 1 $ 秒才能出发。

## 样例 #1

### 输入

```
5 2
4
1 2
2 3
3 4
4 5
2
2 3
3 5
6
2 1 2 1 2 1```

### 输出

```
5```

## 样例 #2

### 输入

```
5 2
3
1 2
3 1
4 3
2
2 1
4 5
5
1 2 1 1 1```

### 输出

```
-1```

# 题解

## 作者：FFTotoro (赞：7)

这题可以使用经过改动的最短路 Dijkstra 算法。

建图的时候把时间标记也打上。考虑怎么进行这个 Dijkstra 算法：假设走到点 $u$，当前的最短时间为 $d_u$，枚举所有出边连接的点 $i$，如果 $i$ 的时间标记有在 $d_u$ 之后出现（假设最早的那个是 $x$），那么就可以更新 $d_i\leftarrow\min\{d_i,x\}$。这个可以将每个标记存一下在 $a$ 数组中出现的所有位置，需要查找的时候 `upper_bound` 即可。

笔者在考场上 $k$ 写成 $n$ 吃了一发罚，警钟撅烂。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
typedef pair<int,int> pii;
main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int n,t; cin>>n>>t;
  vector<vector<pii> > g(n);
  for(int i=1;i<=t;i++){
    int m; cin>>m;
    while(m--){
      int u,v; cin>>u>>v;
      g[--u].emplace_back(i,--v);
      g[v].emplace_back(i,u);
    }
  } // 建图
  int k; cin>>k;
  vector<vector<int> > a(t+1);
  for(int i=1;i<=k;i++){
    int x; cin>>x;
    a[x].emplace_back(i);
  } // 存位置
  vector<int> d(n,1e7); d[0]=0;
  vector<bool> b(n);
  priority_queue<pii,vector<pii>,greater<pii> > q;
  q.emplace(0,0);
  while(!q.empty()){
    int u=q.top().second; q.pop();
    if(b[u])continue; b[u]=true;
    for(auto [w,i]:g[u]){
      auto l=upper_bound(a[w].begin(),a[w].end(),d[u]);
      if(l!=a[w].end()&&*l<d[i])q.emplace(d[i]=*l,i);
    }
  } // Dijkstra 过程
  cout<<(d[n-1]==1e7?-1:d[n-1])<<endl;
  return 0;
}
```

---

## 作者：c1ampy (赞：6)

## 简化题意

给定一张 $ n $ 个点的无向完全图和 $ t $ 组边集，边集 $ i $ 的大小为 $ m_i $。每到达一个结点，你都必须**至少**等待 $ 1 $ 秒，才能继续前进。每条边的通过时间都是 $ 0 $ 秒。第 $ i $ 秒时，边集 $ a_i $ 中的边可以通行，其余边不能通行。第 $ 0 $ 秒时，你从结点 $ 1 $ 出发。判断是否可以在 $ k $ 秒内到达结点 $ n $。如果可以，求出从结点 $ 1 $ 到结点 $ n $ 的最少用时。

注：当你在结点 $ 1 $ 时，也必须至少等待 $ 1 $ 秒才能出发。

$ n, t, \sum m_i, k \le 2 \times 10^5 $。

## 解题思路

本题显然应使用最短路算法。（本题解以 Dijkstra 算法为例）

设到达结点 $ u $ 所的最短用时为 $ d_u $ 秒。

正如常规的 Dijkstra 算法流程，我们每次选出一个未被标记的，$ d $ 值最小的结点 $ u $，将其标记，并尝试通过它松弛与其相邻的结点。

从结点 $ u $ 开始移动，我们有以下两类选择：

- 直接从边集 $ a_{d_u} $ 中选择一条连接着结点 $ u $ 的边移动。
- 在结点 $ u $ 等待至第 $ d^\prime $ 秒，并在边集 $ a_{d^\prime} $ 中选择一条连接着结点 $ u $ 的边移动。

直接遍历所有可行边的时间复杂度是 $ \mathcal{O}\left(m\right) $ 的，不可接受，考虑优化。

对于每一组边集，我们将其所有可以通行的时间记录下来。例如，对于样例 $ 1 $，边集 $ 1 $ 可以通行的时间集合为 $ [ 2, 4, 6 ] $，边集 $ 2 $ 可以通行的时间集合为 $ [ 1, 3, 5 ] $。

照常使用邻接表存图，对于从结点 $ u $ 出发的每条边，存储其所指向的结点 $ v $ 和其所属的边集 $ i $。

执行最短路算法时，遍历结点 $ u $ 对应邻接表的所有边。对于一条指向结点 $ v $，属于边集 $ i $ 的边，我们只需求出这条边从第 $ d_u $ 秒算起，最近一次可以通行的时间 $ T $，即可进行松弛操作：$ d_v \gets \min\{d_v, T\} $。通过在边集 $ i $ 所对应的通行时间集合中二分查找，可以在 $ \mathcal{O}\left(\log k\right) $ 的时间内求出 $ T $。

至此，总时间复杂度已经被优化为 $ \mathcal{O}\left(m \left(\log n + \log k\right)\right) $，可以通过。

## 代码实现

```cpp
#include <iostream>
#include <vector>
#include <queue>

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n, t; std::cin >> n >> t;
	std::vector<std::vector<std::pair<int, int>>> edge(n);
	for (int i = 0, m; i < t; ++i)
	{
		std::cin >> m;
		for (int j = 0, u, v; j < m; ++j)
		{
			std::cin >> u >> v; --u, --v;
			edge[u].push_back(std::make_pair(v, i));
			edge[v].push_back(std::make_pair(u, i));
		}
	}

	int k; std::cin >> k;
	std::vector<std::vector<int>> pos(t);
	for (int i = 0, a; i < k; ++i)
	{
		std::cin >> a; --a;
		pos[a].push_back(i);
	}

	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> heap;
	std::vector<int> dis(n, -1);

	heap.push(std::make_pair(0, 0));
	while (!heap.empty())
	{
		auto [d, cur] = heap.top();
		heap.pop();

		if (dis[cur] != -1)
			continue;
		dis[cur] = d;
		
		for (const auto &[to, i] : edge[cur])
		{
			auto it = std::lower_bound(pos[i].begin(), pos[i].end(), d);
			if (it != pos[i].end())
				heap.push(std::make_pair(*it + 1, to));
				// 由于代码实现使用“0下标”，松弛操作的式子与文字分析处略有不同
		}
	}

	std::cout << dis[n - 1] << std::endl;

	return 0;
}
```

---

## 作者：iiiiiyang (赞：3)

[逆天的阅读体验](https://www.cnblogs.com/LittleTwoawa/p/17781582.html)

[题目链接](https://www.luogu.com.cn/problem/CF1887B)

刚从 modinte 那里学到的广义 dijkstra。注意到一定不会有路径形如 $x \to y \to x$，这样等价于 $x$ 在原地等上两个时刻，我们记 $d_i$ 表示到达 $i$ 节点需要的最少时间。建图，边权为当前这一条边在哪一个历史时刻。然后用一个 set 来存下每个历史时刻在第几次时间旅行后是这个时刻，那么直接跑最短路，转移是对于一条边 $(u,v,w)$，当前 $d_u = x$，那要找到最小的 $i > x$ 且第 $i$ 次时间旅行到达的是历史时刻 $w$，然后就有 $d_{v} = \min \{ d_v,i + 1 \}$，这个过程可以直接在 set 里做一个 lower_bound。根据 dijkstra 的特性，每次从堆中取出的一定是当前最优的节点，因此正确性显然，复杂度 $\mathcal O(m (\log n + \log t))$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
#define ui unsigned int
#define ld long double
#define power(x) ((x)*(x))
#define eb emplace_back
#define pb pop_back
#define mp make_pair
#define fi first
#define se second
#define TT template<typename T>
#define TA template<typename T,typename ...Args>
#define dbg(x) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<'\n';
using namespace std;
using pii=pair<int,int>;
using pdi=pair<double,int>;
using piii=pair<pair<int,int>,int>;

bool Mbe;

namespace IO
{
    inline int read()
    {
        int s=0,w=0; char c=getchar();
        while(!isdigit(c)) w|=c=='-',c=getchar();
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        return s*(w?-1:1);
    }
    TT inline void read(T &s)
    {
        s=0; int w=0; char c=getchar();
        while(!isdigit(c)) w|=c=='-',c=getchar();
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        s*=w?-1:1;
    }
    TA inline void read(T &x,Args &...args) {read(x),read(args...);}
    TT inline void write(T x,char ch=' ')
    {
        if(x<0) x=-x,putchar('-');
        static char stk[30]; int top=0;
        do stk[top++]=x%10+'0',x/=10; while(x);
        while(top) putchar(stk[--top]);
        if(ch!='~') putchar(ch);
    }
}
using namespace IO;

namespace MTool
{
    static const int Mod=998244353;
    TT inline void Swp(T &a,T &b) {static T t=a;a=b;b=t;}
    TT inline void cmax(T &a,T b) {a=max(a,b);}
    TA inline void cmax(T &a,T b,Args ...args) {a=max({a,b,args...});}
    TT inline void cmin(T &a,T b) {a=min(a,b);}
    TA inline void cmin(T &a,T b,Args ...args) {a=min({a,b,args...});}
    TT inline T Cadd(T a,T b) {return a+b>=Mod?a+b-Mod:a+b;}
    TT inline T Cdel(T a,T b) {return a-b<0?a-b+Mod:a-b;}
    TT inline T Cmul(T a,T b) {return a*b%Mod;}
    TT inline T Cmod(T a)     {return (a%Mod+Mod)%Mod;}
    TT inline void Madd(T &a,T b) {a=a+b>=Mod?a+b-Mod:a+b;}
    TT inline void Mdel(T &a,T b) {a=a-b<0?a-b+Mod:a-b;}
    TT inline void Mmul(T &a,T b) {a=a*b%Mod;}
    TT inline void Mmod(T &a)     {a=(a%Mod+Mod)%Mod;}
    TA inline T Cadd(T a,T b,Args ...args) {return Cadd(Cadd(a,b),args...);}
    TA inline T Cdel(T a,T b,Args ...args) {return Cdel(Cdel(a,b),args...);}
    TA inline T Cmul(T a,T b,Args ...args) {return Cmul(Cmul(a,b),args...);}
    TA inline void Madd(T &a,T b,Args ...args) {Madd(a,Cadd(b,args...));}
    TA inline void Mdel(T &a,T b,Args ...args) {Mdel(a,Cadd(b,args...));}
    TA inline void Mmul(T &a,T b,Args ...args) {Mmul(a,Cmul(b,args...));}
    TT inline T qpow(T a,T b) {int res=1; while(b) {if(b&1) Mmul(res,a); Mmul(a,a); b>>=1;} return res;}
    TT inline T qmul(T a,T b) {int res=0; while(b) {if(b&1) Madd(res,a); Madd(a,a); b>>=1;} return res;}
    TT inline T spow(T a,T b) {int res=1; while(b) {if(b&1) res=qmul(res,a); a=qmul(a,a); b>>=1;} return res;}
    TT inline void exgcd(T A,T B,T &X,T &Y) {if(!B) return X=1,Y=0,void(); exgcd(B,A%B,Y,X),Y-=X*(A/B);}
    TT inline T Ginv(T x) {T A=0,B=0; exgcd(x,Mod,A,B); return Cmod(A);}
}
using namespace MTool;

inline void file()
{
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
}

namespace LgxTpre
{
    constexpr int MAX=200010;
    constexpr int inf=2147483647;
    constexpr int INF=4557430888798830399;
    
    int n,t,m,x,y;
    vector<pii> G[MAX];
    set<int> s[MAX];
    priority_queue<pii> q;
    int dis[MAX],vis[MAX];

    inline void lmy_forever()
    {
    	read(n,t);
    	for(int i=1;i<=t;++i) {read(m); for(int j=1;j<=m;++j) read(x,y),G[x].eb(mp(y,i)),G[y].eb(mp(x,i));}
    	read(m),memset(dis,0x3f,sizeof dis),q.emplace(mp(0,1)),dis[1]=0;
    	for(int i=1;i<=m;++i) read(x),s[x].insert(i-1);
    	while(!q.empty())
    	{
    		auto [_,now]=q.top(); q.pop();
    		if(vis[now]) continue;
    		vis[now]=1;
    		for(auto [to,tim]:G[now])
    		{
    			auto D=s[tim].lower_bound(dis[now]);
    			if(D==s[tim].end()) continue;
    			if(dis[to]>*D+1) dis[to]=*D+1,q.emplace(mp(-dis[to],to));
			}
		}
		write(dis[n]==INF?-1:dis[n],'\n');
    }
}

bool Med;

signed main()
{
//  file();
    int Tbe=clock();
    LgxTpre::lmy_forever();
    int Ted=clock();
    fprintf(stderr,"\nMemory: %.3lf MB",abs(&Mbe-&Med)/1024.0/1024.0);
    fprintf(stderr,"\nTime: %.3lf ms",1e3*(Ted-Tbe)/CLOCKS_PER_SEC);
    return (0-0);
}
```

---

## 作者：AC_love (赞：1)

直接跑 Dijkstra 即可。

我们到达某个点的时间一定越早越好，那么我们可以从起点开始跑 Dijkstra。

具体方法是：如果你在 $t$ 时刻到达了一个点，考虑它能走的边，每条边被走的时间应该是大于 $t$ 的最小值。我们维护每条边在哪些时刻出现，那么我们可以直接用 `upper_bound` 来帮我们查找当前这条边下一次出现的时刻。

[code](https://codeforces.com/contest/1887/submission/250575264)

---

## 作者：by_chance (赞：1)

分享一个赛时想到的抽象做法。

考虑维护集合 $S_i$，表示在第 $i$ 次时间旅行之后能到达的点。设定一个阈值 $B$，遇到一个时刻 $a_i$，分情况处理。
- 如果 $m_{a_i}\le B$，可以直接遍历时刻 $a_i$ 的所有边，对 $S_i$ 进行扩展。这种情况的时间复杂度为 $O(nB)$，空间复杂度容易做到 $O(n)$。
- 如果 $m_{a_i}\gt B$，可以考虑 $S_i$ 与上一次到达时刻 $a_i$ 时的 $S$ 的差，显然只用再遍历这些点的出边。这样均摊下来每条边最多遍历一次，时间复杂度是 $O(n)$。空间似乎不好做到 $O(n)$，给出一种 $O(\frac{n^2}{B})$ 的方法：用 `vector` 存下每个点所有时刻的出边，同种时刻放在一起。然后开数组记下每个 $m_j\gt B$ 的时刻 $j$ 在各个 `vector` 中的位置。

时间复杂度 $O(nB+\frac{n^2}{B})$，空间复杂度 $O(\frac{n^2}{B})$，理论上取 $B=\sqrt n$ 最优，但空间可能无法承受。实际上取了 $B=\frac{n}{300}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
bool mem1;
typedef pair<int,int> pii;
const int N=2e5+5,M=305;
int n,t,m[N],rev[N],cnt,B,k,lst[N],vis[N],L[N][M],R[N][M];
vector<int> G[N],now;
vector<pii> e[N];
bool mem2;
int main(){
    cerr<<(&mem2-&mem1)/1024/1024<<endl;
    scanf("%d%d",&n,&t);
    B=max(10.0,ceil(1.0*n/M));
    for(int i=1;i<=t;i++){
        scanf("%d",m+i);
        if(m[i]>B){
            rev[i]=++cnt;
            for(int j=1;j<=n;j++)L[j][cnt]=G[j].size();
        }
        for(int j=1,u,v;j<=m[i];j++){
            scanf("%d%d",&u,&v);
            if(m[i]<=B)e[i].push_back({u,v});
            else G[u].push_back(v),G[v].push_back(u);
        }
        if(m[i]>B)for(int j=1;j<=n;j++)R[j][cnt]=G[j].size();
    }
    now.push_back(1);vis[1]=1;
    scanf("%d",&k);
    for(int i=1,a;i<=k;i++){
        scanf("%d",&a);
        int len=now.size();
        if(m[a]>B){
            for(int x=lst[a];x<len;x++){
                int u=now[x],l=L[u][rev[a]],r=R[u][rev[a]];
                for(int j=l;j<r;j++){
                    int v=G[u][j];
                    if(!vis[v])now.push_back(v),vis[v]=now.size();
                }
            }lst[a]=len;
        }
        else{
            for(auto x:e[a]){
                int u=x.first,v=x.second;
                if(vis[u]&&vis[u]<=len&&!vis[v])
                    now.push_back(v),vis[v]=now.size();
                if(!vis[u]&&vis[v]&&vis[v]<=len)
                    now.push_back(u),vis[u]=now.size();
            }
        }
        if(vis[n]){printf("%d\n",i);return 0;}
    }
    printf("-1\n");
    return 0;
}
```

---

## 作者：RainWetPeopleStart (赞：0)

VP 时切了此题，一遍过了样例和所有测试数据。

首先，发现这题和最短路有些像，所以考虑一手 Dijkstra。

记 $d_i$ 表示到第 $i$ 个点的最短用时。

更新 $d$ 时，设当前考虑边 $u\rightarrow v$。记 $w$ 表示时刻 $d_u$ **以后**，第一个 $u\rightarrow v$ 可以走的时刻，有 $d_v=min(d_v,w)$。

接下来的问题是 $w$ 怎么求。可以把相同的 $a_i$ 存在一起在二分查找，复杂度 $O(m\log m\log n)$。

你发现这个可以优化，因为堆里弹出来的值不降，此时可以用链表维护 $a$，更新时跳 next 即可。

复杂度 $O(m\log m)$。

代码：


```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define mk make_pair
using namespace std;
const int N=2e5+10,INF=1e9+10;
int a[N];
priority_queue<pii> q;
vector<pii> E[N];
int d[N];
int it[N];
int nxt[N];
int hd[N],tot=0;bool vis[N];
int n,m;
void dij(){
    for(int i=1;i<=n;i++) d[i]=INF;
    d[1]=0;q.push(mk(0,1));
    int it=1;
    while(!q.empty()){
        pii p=q.top();q.pop();
        if(vis[p.se]) continue;
        int w=-p.fi,u=p.se;
        vis[u]=1;
        while(it<=w){
            hd[a[it]]=nxt[it];it++;
        }for(auto ed:E[u]){
            int v=ed.fi,w2=ed.se;
            if(vis[v]) continue;
            int tmp=hd[w2];
            if(tmp==0) continue;
            if(tmp<d[v]) d[v]=tmp,q.push(mk(-d[v],v));
        }
    }
}int k;
void slv(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int x;cin>>x;
        for(int j=1;j<=x;j++){
            int u,v;cin>>u>>v;
            E[u].push_back(mk(v,i));
            E[v].push_back(mk(u,i));
        }
    }cin>>k;
    for(int i=1;i<=k;i++) cin>>a[i];
    for(int i=k;i>=1;i--){
        nxt[i]=hd[a[i]];
        hd[a[i]]=i;
    }dij();
    if(d[n]==INF) cout<<-1;
    else cout<<d[n];
}
int main(){
    int t;/*cin>>t;*/t=1;
    while(t--) slv();
    return 0;
}
```

---

## 作者：henrytb (赞：0)

如果一个点能在 $i$ 次穿梭后到达，它也一定能在 $\ge i$ 次穿梭后到达（因为可以一直停在 $i$ 身上）。换句话说，每个点的可达状态具有单调性，所以设 $d_i$ 为能从 $1$ 到达 $i$ 点的最小穿梭次数，跑一个最短路即可。这里从一个 $i$ 走到 $j$ 的时候需要考虑 $d_i$ 这个穿梭次数之后这条边是在哪个穿梭次数的时候第一次可以使用的，用一个二分即可。

```cpp
#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define per(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
const int N = 2e5 + 5;
int n, t, k;
vector<pair<int, int>> e[N]; 
vector<int> tims[N];
int dis[N];
bool vis[N];
typedef pair<int, int> PII;
priority_queue<PII, vector<PII>, greater<PII>> pq;
int main() {
    scanf("%d%d", &n, &t);
    rep(i, 1, t) {
        int mm;
        scanf("%d", &mm);
        rep(j, 1, mm) {
            int u, v;
            scanf("%d%d", &u, &v);
            e[u].emplace_back(v, i);
            e[v].emplace_back(u, i);
        }
    }
    scanf("%d", &k);
    rep(i, 1, k) {
        int p;
        scanf("%d", &p);
        tims[p].emplace_back(i);
    }
    memset(dis, 0x3f, sizeof(dis));
    dis[1] = 1; pq.emplace(1, 1);
    while (!pq.empty()) {
        int u = pq.top().second; pq.pop();
        if (vis[u]) continue;
        vis[u] = 1; int nowt = dis[u];
        for (auto &[v, tim]: e[u]) {
            auto pos = lower_bound(tims[tim].begin(), tims[tim].end(), nowt) - tims[tim].begin();
            if (pos < tims[tim].size()) {
                if (dis[v] > tims[tim][pos] + 1) {
                    dis[v] = tims[tim][pos] + 1;
                    pq.emplace(dis[v], v);
                }
            }
        }
    }
    printf("%d\n", dis[n] > k + k ? -1 : dis[n] - 1);
    return 0;
}
```

---

