# [USACO11JAN] Roads and Planes G

## 题目描述

### 题面描述

Farmer John 正在一个新的销售区域对他的牛奶销售方案进行调查。他想把牛奶送到 $T$ 个城镇 ( $1 \le T \le 25,000$ )，编号为 $1$ 到 $T$ 。这些城镇之间通过 $R$ 条道路 ( $1 \le R \le 50,000$ ，编号为 $1$ 到 $R$ ) 和 $P$ 条航线 ( $1 \le P \le 50,000$ ，编号为 $1$ 到 $P$ ) 连接。每条道路 $i$ 或者航线 $i$ 连接城镇 $A_i$ ( $1 \le A_i \le T$ )到 $B_i$ ( $1 \le B_i \le T$ )，花费为 $C_i$ 。

对于道路 $0 \le C_i \le 10,000$ ;然而航线的花费很神奇，花费 $C_i$ 可能是负数( $-10,000 \le C_i \le 10,000$ )。道路是双向的，可以从 $A_i$ 到 $B_i$，也可以从 $B_i$ 到 $A_i$ ，花费都是 $C_i$ 。然而航线与之不同，只可以从 $A_i$ 到 $B_i$ 。

事实上，由于最近恐怖主义太嚣张，为了社会和谐，出台 了一些政策保证：如果有一条航线可以从 $A_i$ 到  $B_i$，那么保证不可能通过一些道路和航线从 $B_i$ 回到 $A_i$ 。由于 $FJ$ 的奶牛世界公认十分给力，他需要运送奶牛到每一个城镇。他想找到从发送中心城镇 $S$ ( $1 \le S \le T$) 把奶牛送到每个城镇的最便宜的方案，或者知道这是不可能的。

## 样例 #1

### 输入

```
6 3 3 4 
1 2 5 
3 4 5 
5 6 10 
3 5 -100 
4 6 -100 
1 3 -10 
```

### 输出

```
NO PATH 
NO PATH 
5 
0 
-95 
-100 
```

# 题解

## 作者：zhzh2001 (赞：85)

## 思路


这题要求的是带负权边的最短路，显然不能直接用Dijkstra。然而Bellman-Ford或SPFA的时间复杂度最坏$O(NM)$，而且众所周知，USACO总是卡SPFA的。尽管这题数据比较老，因此SPFA+SLF可以水过，但是正解并不是如此。


顺便说一下，用优先队列优化SPFA并不有效(来自[模板]单源最短路-题解)，在这题比普通SPFA更慢。然而在某些边权为正的卡SPFA的图中，几乎和Dijkstra不相上下。


可以发现，图有一个很强的性质：对于无向边，边权总是正的，因此每个无向边联通块是强联通的。而可能的负权边保证不能反向联通，因此把无向边联通块缩点后，得到的就是DAG。这样就可以在块内使用Dijkstra，块间利用拓扑排序更新答案。时间复杂度$O(M\log N)$。


## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=25005,INF=0x3f3f3f3f;
typedef pair<int,int> pii;
vector<pii> roads[N],planes[N];
vector<int> comp[N];
//联通分量中的点
int belong[N],indeg[N],d[N];
//belong[]表示每个点所属的联通分量，indeg[]表示联通分量的入度
bool vis[N];
void dfs(int k,int num)
{
    belong[k]=num;
    comp[num].push_back(k);
    for(auto e:roads[k])
        if(!belong[e.first])
            dfs(e.first,num);
}
//dfs洪水填充
int main()
{
    int n,m,p,s;
    cin>>n>>m>>p>>s;
    while(m--)
    {
        int u,v,w;
        cin>>u>>v>>w;
        roads[u].push_back(make_pair(v,w));
        roads[v].push_back(make_pair(u,w));
    }
    while(p--)
    {
        int u,v,w;
        cin>>u>>v>>w;
        planes[u].push_back(make_pair(v,w));
    }
    int c=0;
    for(int i=1;i<=n;i++)
        if(!belong[i])
            dfs(i,++c);
    for(int i=1;i<=n;i++)
        for(auto e:planes[i])
            indeg[belong[e.first]]++;
    fill(d+1,d+n+1,INF);
    d[s]=0;
    queue<int> Q;
    for(int i=1;i<=c;i++)
        if(!indeg[i])
            Q.push(i);
    while(!Q.empty())
    {
        int k=Q.front();Q.pop();
        priority_queue<pii,vector<pii>,greater<pii>> PQ;
        for(auto i:comp[k])
            if(d[i]<INF)
                PQ.push(make_pair(d[i],i));
        while(!PQ.empty())
        {
            pii k=PQ.top();PQ.pop();
            if(vis[k.second])
                continue;
            vis[k.second]=true;
            for(auto e:roads[k.second])
                if(d[k.second]+e.second<d[e.first])
                    PQ.push(make_pair(d[e.first]=d[k.second]+e.second,e.first));
            for(auto e:planes[k.second])
                d[e.first]=min(d[e.first],d[k.second]+e.second);
        }
        for(auto i:comp[k])
            for(auto e:planes[i])
                if(--indeg[belong[e.first]]==0)
                    Q.push(belong[e.first]);
    }
  //拓扑排序和Dijkstra
    for(int i=1;i<=n;i++)
        if(d[i]==INF)
            cout<<"NO PATH\n";
        else
            cout<<d[i]<<endl;
    return 0;
}
```

## 拓展：生成数据


这题很有趣，因此我思考了如何生成数据。直接随机显然不符合题意，需要一定的构造。我的方法是：可以先确定每个点所属的连通分量，然后在连通分量中生成树保证连通，再在连通分量内随机添加边。然后在连通分量间生成树保证连通，再随机加边。只要规模足够大，用这种方法生成的数据足以卡掉SPFA了。


附代码供参考(C++11)：


```cpp
#include<bits/stdc++.h>
using namespace std;
ofstream fout("roadplane.in");
const int n=100000,m=300000,w=50000,cn=1000,W=100000;
int belong[n+5];
vector<int> comp[cn+5];
int f[n+5];
int getf(int x)
{
    return f[x]==x?x:f[x]=getf(f[x]);
}
int main()
{
    minstd_rand gen(time(NULL));
    for(int i=1;i<=n;i++)
    {
        uniform_int_distribution<> dc(1,cn);
        belong[i]=dc(gen);
        comp[belong[i]].push_back(i);
    }
    assert(comp[1].size());
    uniform_int_distribution<> d(0,comp[1].size()-1);
    fout<<n<<' '<<m<<' '<<w<<' '<<comp[1][d(gen)]<<endl;
    for(int i=1;i<=cn;i++)
    {
        int cnt=0;
        for(int j=0;j<comp[i].size();j++)
            f[j]=j;
        while(cnt+1<comp[i].size())
        {
            uniform_int_distribution<> did(0,comp[i].size()-1);
            int u=did(gen),v=did(gen),ru=getf(u),rv=getf(v);
            if(ru!=rv)
            {
                f[ru]=rv;
                cnt++;
                uniform_int_distribution<> dw(0,W);
                fout<<comp[i][u]<<' '<<comp[i][v]<<' '<<dw(gen)<<endl;
            }
        }
    }
    for(int i=n-cn+1;i<=m;i++)
    {
        uniform_int_distribution<> dc(1,cn);
        int c=dc(gen);
        if(!comp[c].size())
        {
            i--;
            continue;
        }
        uniform_int_distribution<> did(0,comp[c].size()-1),dw(0,W);
        fout<<comp[c][did(gen)]<<' '<<comp[c][did(gen)]<<' '<<dw(gen)<<endl;
    }
    for(int i=1;i<=cn;i++)
        f[i]=i;
    for(int i=1;i<cn;)
    {
        uniform_int_distribution<> dc(1,cn-1);
        int cu=dc(gen);
        uniform_int_distribution<> dc1(cu+1,cn);
        int cv=dc1(gen),rcu=getf(cu),rcv=getf(cv);
        if(rcu==rcv)
            continue;
        f[rcu]=rcv;
        if(!comp[cu].size()||!comp[cv].size())
            continue;
        uniform_int_distribution<> didu(0,comp[cu].size()-1),didv(0,comp[cv].size()-1),dw(-W,W);
        fout<<comp[cu][didu(gen)]<<' '<<comp[cv][didv(gen)]<<' '<<dw(gen)<<endl;
        i++;
    }
    for(int i=cn;i<=w;)
    {
        uniform_int_distribution<> dc(1,cn-1);
        int cu=dc(gen);
        uniform_int_distribution<> dc1(cu+1,cn);
        int cv=dc1(gen);
        if(!comp[cu].size()||!comp[cv].size())
            continue;
        uniform_int_distribution<> didu(0,comp[cu].size()-1),didv(0,comp[cv].size()-1),dw(-W,W);
        fout<<comp[cu][didu(gen)]<<' '<<comp[cv][didv(gen)]<<' '<<dw(gen)<<endl;
        i++;
    }
    return 0;
}
```


---

## 作者：heyuhhh (赞：24)

# 思路
题中给出的图有单向边和双向边，其中单向边边权可能为负，这其实就说明我们不能直接用dijkstra。（貌似可以双端队列优化的spfa水过去= =

注意到无向边边权是非负的，这提示我们可以在无向边上跑最短路。并且我们可以知道，如果将无向边连接的点缩为一点，最后图中只剩下有向边的话，这个图就是一个DAG，DAG上更新最短路还是很容易的。

所以我们就可以分开考虑，首先求出若干个由无向边组成的连通块，对于块内的点，通过堆优化的dijkstra算法更新最短路；然后在块与块之间，类似于拓扑排序，一层一层地进行更新，最后就可以求出源点$s$到所有点的最短路了。

但这里有个细节就是，对于不能到达的点，要删去它们相应的出边，否则拓扑排序就不能正常执行（脑补一下就知道了）。这也就是为什么一开始加入$s$所在块时，还要把其它入度为0的块也算进去的原因。（~~我一开始就是这里卡了好久~~

还有就是代码中最后判不可到达时，因为题目中路径长度最多为$25000*10000=2.5*10^8$。那么能到达的点的最短路值一定小于$2.5*10^8$。一开始我们将$d$数组置为无穷大(也就是$2e9$左右)，$0x3f3f3f3f$大小为$1e9$，如果最后的最短路长度大于$0x3f3f3f3f$，那么一定是不可到的。

# 详见代码
```cpp
#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;
const int N = 50005, M = 100005;
int n, r, p, s;
struct Edge{
    int v, next, w;
}e[M << 1];
struct node{
    int d, u;
    bool operator < (const node &A) const {
        return d > A.d;
    }
};
int head[N], tot;
void adde(int u, int v, int w) {
    e[tot].v = v; e[tot].w = w; e[tot].next = head[u]; head[u] = tot++;
}
bool vis[N] ;
int cnt;
int bl[N], in[N];
int d[N] ;
vector <int> block[N];
void dfs(int u) {
    vis[u] = 1;
    bl[u] = cnt;
    block[cnt].push_back(u) ;
    for(int i = head[u]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if(vis[v]) continue ;
        dfs(v) ;
    }
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> r >> p >> s;
    memset(head, -1, sizeof(head)) ;
    for(int i = 1; i <= r; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adde(a, b, c);
        adde(b, a, c);
    }
    for(int i = 1; i <= n; i++) {
        if(!vis[i]) {
            cnt++;
            dfs(i) ;
        }
    }
    for(int i = 1; i <= p; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adde(a, b, c) ;
        in[bl[b]]++;
    }
    memset(vis, 0, sizeof(vis)) ;
    memset(d, 0x7f, sizeof(d)) ;
    d[s] = 0;
    queue <int> Q;
    Q.push(bl[s]) ;
    for(int i = 1; i <= cnt; i++) if(!in[i]) Q.push(i) ;
    priority_queue <node> q;
    while(!Q.empty()) {
        int blo = Q.front();Q.pop() ;
        for(auto u : block[blo])
            q.push(node{d[u], u}) ;
        while(!q.empty()) {
            node now = q.top(); q.pop();
            int u = now.u;
            if(vis[u]) continue ;
            vis[u] = 1;
            for(int i = head[u]; i != -1; i = e[i].next) {
                int v = e[i].v;
                if(d[v] > d[u] + e[i].w) {
                    d[v] = d[u] + e[i].w;
                    if(bl[v] == bl[u]) q.push(node{d[v],v}) ;
                }
                if(bl[v] != bl[u] && (--in[bl[v]]) == 0) Q.push(bl[v]) ;
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        if(d[i] > INF) cout << "NO PATH" << '\n' ;
        else cout << d[i] << '\n' ;
    }
    return 0;
}

```


---

## 作者：jzqjzq (赞：23)

就是一个朴素的最短路问题，因为有负边但是没有负环，所以可以SPFA求解

只不过一般的SPFA会TLE大约1~2个点，所以加上SLF优化就可以过了

SLF是什么？把普通队列换成双端队列，然后每次插入时和队头比较，如果更优插到队头否则插队尾，这样时间可以优化很多

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
#include<cstdlib>
#include<string>
#include<ctime>
#include<queue>
#include<climits>
using namespace std;
deque<int>q;//双端队列
bool vis[100001];
int n,m1,m2,s,dist[100001];
int nedge=0,p[200001],c[200001],nex[200001],head[200001];
inline void addedge(int x,int y,int z){
    p[++nedge]=y;c[nedge]=z;
    nex[nedge]=head[x];head[x]=nedge;
}
inline void spfa(int x){
    for(int i=1;i<=n;i++)dist[i]=1e9;
    memset(vis,0,sizeof vis);
    dist[x]=0;vis[x]=1;q.push_back(x);
    while(!q.empty()){
        int now=q.front();q.pop_front();
        for(int k=head[now];k;k=nex[k])if(dist[p[k]]>dist[now]+c[k]){
            dist[p[k]]=dist[now]+c[k];
            if(!vis[p[k]]){
                if(!q.empty()&&dist[p[k]]>=dist[q.front()])q.push_back(p[k]);//与队头比较
                else q.push_front(p[k]);
                vis[p[k]]=1;
            }
        }
        vis[now]=0;
    }
}
int main()
{
    scanf("%d%d%d%d",&n,&m1,&m2,&s);
    for(int i=1;i<=m1;i++){
        int x,y,z;scanf("%d%d%d",&x,&y,&z);
        addedge(x,y,z);addedge(y,x,z);
    }
    for(int i=1;i<=m2;i++){
        int x,y,z;scanf("%d%d%d",&x,&y,&z);
        addedge(x,y,z);
    }
    spfa(s);
    for(int i=1;i<=n;i++)if(dist[i]<1e9)printf("%d\n",dist[i]);
    else puts("NO PATH");
    return 0;
}
```

---

## 作者：木木！ (赞：16)

拍个只要一遍Dijkstra的题解QwQ。

观察到我们不能直接Dijkstra，但是可以魔改一下。如果可以保证所有到一个强连通分量的飞机的最短路径都已经结算了的话，是可以在这个强连通分量里面使用Dijkstra的。

所以，我的做法是先利用并查集维护强连通分量，然后执行一遍拓扑排序，求出每个强联通分量的拓扑序。在Dijkstra的时候，将拓扑序作优先队列的第一关键字，而距离作为第二关键字进行Dijkstra。最后只需要一遍Dijkstra就可以了。

时间复杂度$\Theta(n+m+nlogm)$，耗时……和我一个不加快读的人比什么耗时QwQ。

附AC代码：

```cpp
#include <queue>
#include <cstdio>
using namespace std;

int st[25005];

int getfa(int x)
{
	return st[x]==x?x:st[x]=getfa(st[x]);
}

void unio(int a,int b)
{
	st[getfa(a)] = getfa(b);
}

int stbeg[25005];
int beg[25005];
int ed[200005];
int nxt[200005];
int len[200005];
int top;

void addedge(int* beg,int a,int b,int l)
{
	++top;
	ed[top] = b;
	len[top] = l;
	nxt[top] = beg[a];
	beg[a] = top;
}

int stdeg[25005];
int stvis[25005];

void dfs(int x)
{
	stvis[x] = 1;
	for(int p=stbeg[x]; p; p=nxt[p])
	{
		++stdeg[ed[p]];
		if(!stvis[ed[p]])
		{
			dfs(ed[p]);
		}
	}
}

int sttopn[25005];

void toposort(int x)
{
	queue<int> q;
	q.push(x);
	
	while(!q.empty())
	{
		int th = q.front();
		q.pop();
		
		for(int p=stbeg[th]; p; p=nxt[p])
		{
			--stdeg[ed[p]];
			if(!stdeg[ed[p]])
			{
				sttopn[ed[p]] = sttopn[th]+1;
				q.push(ed[p]);
			}
		}
	}
}

int n;
int dist[25005];
int vis[25005];

void dijkstra(int s)
{
	for(int i=1; i<=n; ++i)
	{
		dist[i] = 0x7f7f7f7f;
	}
	dist[s] = 0;
	
	priority_queue<pair<pair<int,int>,int> > pq;
	pq.push(make_pair(make_pair(0,0),s));
	
	while(!pq.empty())
	{
		int th = pq.top().second;
		pq.pop();
		if(vis[th])
		{
			continue;
		}
		
		vis[th] = 1;
		
		for(int p=beg[th]; p; p=nxt[p])
		{
			if(dist[ed[p]] > dist[th]+len[p])
			{
				dist[ed[p]] = dist[th]+len[p];
				pq.push(make_pair(make_pair(-sttopn[getfa(ed[p])],-dist[ed[p]]),ed[p]));
			}
		}
	}
}

int main()
{
	int r,p,s;
	scanf("%d%d%d%d",&n,&r,&p,&s);
	for(int i=1; i<=n; ++i)
	{
		st[i] = i;
	}
	for(int i=1; i<=r; ++i)
	{
		int a,b,l;
		scanf("%d%d%d",&a,&b,&l);
		addedge(beg,a,b,l);
		addedge(beg,b,a,l);
		unio(a,b);
	}
	for(int i=1; i<=p; ++i)
	{
		int a,b,l;
		scanf("%d%d%d",&a,&b,&l);
		addedge(beg,a,b,l);
		addedge(stbeg,getfa(a),getfa(b),l);
	}
	
	dfs(getfa(s));
	toposort(getfa(s));
	
	dijkstra(s);
	
	for(int i=1; i<=n; ++i)
	{
		if(!vis[i])
		{
			printf("NO PATH\n");
		}
		else
		{
			printf("%d\n",dist[i]);
		}
	}
}
```

---

## 作者：Horadrim (赞：7)

### 思路
这题是一道单源最短路题，而且有负权边，乍一看用SPFA；但是，众所周知，USACO卡SPFA，所以只能用Dijkstra (不考虑SPFA+SLF的情况下)。

因为有负权边，但只有有向边是负权边，所以我们考虑将无向边连接的联通块看作一个点，在这里面跑Dijkstra，拓扑排序一下（拓扑排序又不管边权是正是负），然后这个图就变成强联通的了。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,r,p,s,cnt;
int ind[25011],d[25011],a[25011],c[25011],v[25011];
struct node {
	int y,v;
};
typedef pair <int,int> P;
priority_queue <P,vector<P>,greater<P> > Q;
vector <node> g[25011];
vector <int> b[25011];
queue <int> q;
void dfs (int x) {
	c[x]=cnt;
	b[cnt].push_back(x);
	for (int i=0;i<g[x].size();i++) {
		if (c[g[x][i].y]) continue;
		dfs(g[x][i].y);
	}
}
//求联通块
void Dijkstra () {
	while (!Q.empty()) {
		pair <int,int> p=Q.top();
		int x=p.second;
		Q.pop();
		if (v[x]) continue;
		v[x]=1;
		for (int i=0;i<g[x].size();i++) {
			node e=g[x][i];
			if (d[e.y]>d[x]+e.v) {
				d[e.y]=d[x]+e.v;
				if (c[x]==c[e.y]) Q.push(make_pair(d[e.y],e.y));
			}
			if (c[x]!=c[e.y]) {
				ind[c[e.y]]--;
				if (!ind[c[e.y]]) q.push(c[e.y]);
			}
		} 
	}
}
//Dijkstra堆优化版本
void topsort (int s) {
	q.push(c[s]);
	for (int i=1;i<=cnt;i++) if (ind[i]==0) q.push(i);
	memset(d,0x7f,sizeof(d));
	d[s]=0;
	while (!q.empty()) {
		int u=q.front();
		q.pop();
		for (int i=0;i<b[u].size();i++) 
			Q.push(make_pair(d[b[u][i]],b[u][i]));
		Dijkstra();
	}
}
//拓扑排序
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin>>t>>r>>p>>s;
	for (int i=1;i<=r;i++) {
		int a,b,c;
		cin>>a>>b>>c;
		g[a].push_back(node{b,c});
		g[b].push_back(node{a,c});
	}
  	//输入
	for (int i=1;i<=t;i++) {
		if (!c[i]) {
			cnt++;
			dfs(i);
		}
	}
 	//求联通块
	for (int i=1;i<=p;i++) {
		int a,b,z;
		cin>>a>>b>>z;
		ind[c[b]]++;
		g[a].push_back(node{b,z});
	}
  	//求入度，准备拓扑排序
	topsort(s);
	for (int i=1;i<=t;i++) {
    	if (d[i]>=0x3f3f3f3f) cout<<"NO PATH\n";
        else cout<<d[i]<<'\n';
    }
  	//输出

	return 0;
}
```
第一次写题解，有待改进，勿喷

---

## 作者：koreyoshi_lemon (赞：4)

显然本题是一道单源最短路

题中可能会存在负权边，所以不能使用 Heap-Dijkstra。若直接使用 SPFA，因为数据的特殊构造，实测会被卡到 $O(NM)$，不能通过这一题。但题目中有一个特殊性质：双向边总是非负的，单向边可能为负数但不会构成环。

如果只把双向边加到图里，那么就会形成若干连通块，我们把连通块整体看作“点”，将单向边看作边，那么这就是一个妥妥的 DAG。无论边权正负，我们总能使用拓扑排序线性求出最短距离。至于连通块内部，由于不存在负权边，可以使用 Dijkstra。

算法流程如下：

1.  把双向边加入途中，dfs 统计每个点所属的连通块 $c_x$

2.  将单向边加入图中，统计每个连通块总入度 $deg_i$

3. 建立队列拓扑排序，包含入度为零的连通块及源点所在连通块。其中，令 $d_S=0$，其他为正无穷。

4. 取出对头连通块 $i$，在连通块内部使用 Heap-Dijkstra。

时间复杂度：$O(T+P+R\log T)$

有人可能对时间复杂度存在异议，我这里解释一下。所有点的总数是确定的，每个点只会被 Heap-Dijkstra 计算一次，所以无论有多少个连通块，总能在 $O(R\log T)$ 的时间内完成。而对于每个连通块，我可以用一个 vector 存储其内部的点然后放入堆中，同样是因为点的总数确定，所以这个过程同样不会卡到 $O(T^2)$。

贴上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+7;
int T,R,P,S;
struct edge{
	int to,next,w;
}a[N<<1];
int tot,l[N];
inline void add(int u,int v,int w)
{
	a[++tot].to=v;
	a[tot].next=l[u];
	a[tot].w=w;
	l[u]=tot;
}
int c[N],cnt,deg[N];
void dfs(int x,int num)	{
	c[x]=num;
	for(int i=l[x];i;i=a[i].next)	{
		int y=a[i].to;
		if(c[y]) continue;
		dfs(y,num);
	}
	return;
}
queue<int> q;
priority_queue<pair<int,int> >q1;
int d[N],v[N];
vector<int> ct[N]; 
inline void dijkstra(int block)
{
	for(int i=0;i<ct[block].size();i++)	{
		int y=ct[block][i];
		q1.push(make_pair(-d[y],y));
	}
	while(!q1.empty())	{
		int x=q1.top().second;
		q1.pop();
		if(v[x]) continue;
		v[x]=1;
		for(int i=l[x];i;i=a[i].next)	{
			int y=a[i].to;
			if(v[y]) continue;
			if(d[y]>d[x]+a[i].w)	{
				d[y]=d[x]+a[i].w;
				if(c[x]==c[y]) q1.push(make_pair(-d[y],y));
			}
			if(c[x]!=c[y]&&--deg[c[y]]==0)
//由于计算机的运算性质，如果 c[x]==c[y] 就会直接忽略 --deg[c[y]]==0 的语句，所以没有问题 
				q.push(c[y]);
		}
	}
	return;
}
int main(void)
{
	scanf("%d%d%d%d",&T,&R,&P,&S);
	for(int i=1;i<=R;i++)	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w); add(v,u,w);
	}
	for(int i=1;i<=T;i++)
		if(!c[i]) dfs(i,++cnt);
	for(int i=1;i<=T;i++)
		ct[c[i]].push_back(i);
	for(int i=1;i<=P;i++)	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
		++deg[c[v]];
	}
	q.push(c[S]);
	for(int i=1;i<=cnt;i++)
		if(!deg[i]) q.push(i);
	memset(d,0x3f,sizeof(d));
	d[S]=0;
	while(!q.empty())	{
		int x=q.front();
		q.pop();
		dijkstra(x);
	}
	for(int i=1;i<=T;i++)	{
		if(d[i]>1e7) printf("NO PATH\n");
		else printf("%d\n",d[i]);
	}
	return 0;
}
```


---

## 作者：hzoi_liuchang (赞：4)


## 分析

### 正解

我们可以发现题目中有两种边，一种是双向边，边权非负，另一种是单向边，边权可能为正

如果我们用Dij直接去跑最短路，显然是不可以的，因为题目中有负权

如果我们用SPFA 呢，显然会被卡掉

所以我们考虑一下它所具有的的某种性质

双向建的边是非负的，跑Dij是没有问题的，但是问题就是题目中还有单项负权边

我们仔细读一下题就可以发现一个重要的性质：负权的边不会出现环

那么我们就可以把强连通分量缩点，这样缩点之后的图就变成了一个有向无环图

这样就可以在强连通分量内使用Dij，分量外使用拓扑排序更新答案

### 代码

```` cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<queue>
#include<vector>
#define INF 0x3f3f3f3f
using namespace std;
const int maxn=150005;
int t,r,p,s,head[maxn],tot=1,cnt;
struct asd{
    int to,next,val;
}b[maxn];
void ad(int aa,int bb,int cc){
    b[tot].to=bb;
    b[tot].val=cc;
    b[tot].next=head[aa];
    head[aa]=tot++;
}
bool vis[maxn];
int shuyu[maxn],dis[maxn];
vector<int> jl[maxn];
void dfs(int now){
    shuyu[now]=cnt,vis[now]=1,jl[cnt].push_back(now);
    for(int i=head[now];i!=-1;i=b[i].next){
        int u=b[i].to;
        if(vis[u])continue;
        dfs(u);
    }
}
struct jie{
    int num,jz;
    jie(int aa=0,int bb=0){
        num=aa,jz=bb;
    }
    bool operator < (const jie& A) const {
        return jz>A.jz;
    }
};
int ru[maxn];
queue<int> q;
priority_queue<jie> Q;
void dij(){
    dis[s]=0;
    while(!q.empty()) {
        int xx=q.front();
        q.pop();
        for(int i=0;i<jl[xx].size();i++){
            Q.push(jie(jl[xx][i],dis[jl[xx][i]]));
        }
        while(!Q.empty()){
            int now = Q.top().num;
            Q.pop();
            if(vis[now]) continue;
            vis[now]=1;
            for(int i=head[now];i!=-1;i=b[i].next){
                int u=b[i].to;
                if(dis[u]>dis[now]+b[i].val){
                    dis[u]=dis[now]+b[i].val;
                    if(shuyu[now]==shuyu[u]) Q.push(jie(u,dis[u]));
                }
                if(shuyu[u]!=shuyu[now] && (--ru[shuyu[u]]==0)) q.push(shuyu[u]); 
            }
        }
    }
}
int main(){
    memset(head,-1,sizeof(head));
    scanf("%d%d%d%d",&t,&r,&p,&s);
    for(int i=1;i<=r;i++){
        int aa,bb,cc;
        scanf("%d%d%d",&aa,&bb,&cc);
        ad(aa,bb,cc);
        ad(bb,aa,cc);
    }
    for(int i=1;i<=t;i++){
        if(!vis[i]) cnt++,dfs(i);
    }
    for(int i=1;i<=p;i++){
        int aa,bb,cc;
        scanf("%d%d%d",&aa,&bb,&cc);
        ad(aa,bb,cc);
        ru[shuyu[bb]]++;
    }
    memset(vis,0,sizeof(vis));
    memset(dis,0x7f,sizeof(dis));
    for(int i=1;i<=cnt;i++) if(ru[i]==0) q.push(i);
    dij();
    for(int i=1;i<=t;i++){
        if(dis[i]>INF) printf("NO PATH\n");
        else printf("%d\n",dis[i]);
    }
    return 0;
}
````

### 水过

当然，如果是在考试的时候，正解肯定是很难想到

即使是想到了，又是缩点又是拓扑排序，又是Dij，分起来写还好点，如果合在一起，难免有点代码量

而且，如果最后你调试了半天还没有暴力分高，岂不是很尴尬

所以我们就尝试这用SPFA水一下

其实SPFA本质上还是Bellman Ford的优化版本

那么Bellman Ford是怎么运作的呢

实际上它是使用全部的边对于起点到其他n-1个点的路径进行松弛,重复n-1次

算法复杂度为O(VE)

这样的复杂度几千条边还勉强可以接受，但是十万以上的边是肯定不可以的

于是就有了优化版本SPFA，它的优化之处在哪里呢

实际上我们来想一下，对于普通的Bellman Ford，其实有些边是根本松弛不动的

所以我们优化的方向就是把肯定不能松弛其它节点的节点排除在外

我们不去考虑哪些节点不能松弛其它节点，而是考虑哪些节点可以松弛其它节点

很显然，只有当前已经松弛成功过的节点才有可能松弛其它的节点

因此这时，我们就用一个栈来记录那些已经松弛成功的节点

每次我们只要从栈中取出节点松弛就可以了

那么时间复杂度呢？

SPFA算法的时间复杂度是不可靠的，一般情况下为O(E)，而在极限情况下也有可能达到Bellman-ford算法的复杂度，即O(V*E)

其实，想要把SPFA卡掉还是很容易的，我们可以随便建一个网格图

因为网格图中的边比较稠密，所以SPFA稍有不慎变会误入歧途，然后多走很多条边

但是，网上也有很多关于SPFA的优化，其实就是想让普通的栈更接近优先队列

因为如果你的栈里有很多个已经松弛过的节点，你肯定希望拿出一个值比较小的节点去松弛其他的节点

因为这样一次松弛成功的几率比较大

所以，我们尽量使维护的栈更接近一个优先队列，也就是权值小的先出栈

目前比较常见的有两种方法，一种是把要插入的元素的值和栈顶元素比较，如果比栈顶元素小，那么就把这个元素放在占栈顶，否则放在栈底

另一种方法就是把与队首元素比较改成了与队中元素的平均值比较，思路差不多

对于这道题，我们可以用第一种方法水过

``` cpp
#include<cstdio>
#include<iostream>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const int maxn=150005;
struct asd{
	ll from,to,next,val;
}b[maxn];
ll head[maxn],tot=1;
void ad(ll aa,ll bb,ll cc){
	b[tot].from=aa;
	b[tot].to=bb;
	b[tot].next=head[aa];
	b[tot].val=cc;
	head[aa]=tot++;
}
deque<ll> q;
bool vis[maxn];
ll dis[maxn];
void SPFA(ll xx){
	memset(dis,0x3f,sizeof(dis));
	dis[xx]=0,vis[xx]=1;
	q.push_back(xx);
	while(!q.empty()){
		ll now=q.front();
		q.pop_front();
		vis[now]=0;
		for(ll i=head[now];i!=-1;i=b[i].next){
			ll u=b[i].to;
			if(dis[u]>dis[now]+b[i].val){
				dis[u]=dis[now]+b[i].val;
				if(!vis[u]){
					if(!q.empty()&&dis[u]>=dis[q.front()]) q.push_back(u);
                    else q.push_front(u);
					vis[u]=1;
				}
			}
		}
	}
}
int main(){
	memset(head,-1,sizeof(head));
	ll t,r,p,s;
	scanf("%lld%lld%lld%lld",&t,&r,&p,&s);
	for(ll i=1;i<=r;i++){
		ll aa,bb,cc;
		scanf("%lld%lld%lld",&aa,&bb,&cc);
		ad(aa,bb,cc),ad(bb,aa,cc);
	}
	for(ll i=1;i<=p;i++){
		ll aa,bb,cc;
		scanf("%lld%lld%lld",&aa,&bb,&cc);
		ad(aa,bb,cc);
	}
	SPFA(s);
	for(ll i=1;i<=t;i++){
		if(dis[i]==0x3f3f3f3f3f3f3f3f) printf("NO PATH\n");
		else printf("%lld\n",dis[i]);
	}
	return 0;
}
```

其实大家还可以想一下，如果我们把用优先队列，改成用小根堆去维护，会变成什么样子

或者是裸的Bellman Ford加点特判，又会是什么样子

最后提醒大家一下，正权最短路尽量用DIJ

负权最短路和最长路千万不要用DIJ，卡成0分都有可能



---

## 作者：Gary818 (赞：2)

## [题目地址](https://www.luogu.com.cn/problem/P3008)

## Solution
板子题……  
负边权—>裸的$Dijkstra$肯定过不了  
然后随便敲了一个$Spfa$的板子拿到了88分的好成绩？  
~~感觉数据有亿点水~~  
~~要是卡$Spfa$就卡成10分啊倒是~~  
然后然后随便换了个$deque$优化了一手就过了  
时间复杂度$O(nlog_n)$  
最坏情况可以被卡成$O(nm)$  
不过这个题似乎问题不大   
根据以往的经验来看  
双端队列优化的$Spfa$不太容易被卡  
也很好实现，在$Spfa$的板子上每次判断一下队头队尾的dis值谁大谁小，更换一下进队方式。  
如果小于队头，就把这个点放入队首，这也可以避免多余的松弛，有点类似于$Dijkstra$的建议思想？建议学习    

再一个就是正解，在每个强联通分量里跑$Dijkstra$然后$Topsort$
时间复杂度$O(mlog_n)$  


懒得写第二种了，其他大佬也有讲，放个deque的板子得了，过单源最短路也没问题，可以直接食用
```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

inline int read(){
	int x = 0, w = 1;
	char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
	return x * w;
}

const int ss = 1000010;

struct node{
	int to, nxt, w;
}edge[ss << 1];

int head[ss << 1], tot;
inline void add(int u, int v, int w){
	edge[++tot].to = v; 
	edge[tot].nxt = head[u];
	edge[tot].w = w;
	head[u] = tot;
}

deque<int> q;
bool vis[ss];
int dis[ss];

inline void spfa(int s){
	memset(vis, 0, sizeof vis);
	memset(dis, 0x3f, sizeof dis);
	q.push_back(s);
	dis[s] = 0;
	while(!q.empty()){
		int u = q.front();
		q.pop_front();
		vis[u] = 0;
		for(int i = head[u]; i; i = edge[i].nxt){
			int v = edge[i].to;
			if(dis[v] > dis[u] + edge[i].w){
				dis[v] = dis[u] + edge[i].w;
				if(!vis[v]){
					if(!q.empty() && dis[v] >= dis[q.front()]) q.push_back(v);
					else q.push_front(v);
					vis[v] = 1;
				}
			}
		}
	}
}

signed main(){
	int n = read(), r = read(), p = read(), s = read();
	for(int i = 1; i <= r; i++){
		int u = read(), v = read(), w = read();
		add(u, v, w);
		add(v, u, w);
	}
	for(int i = 1; i <= p; i++){
		int u = read(), v = read(), w = read();
		add(u, v, w);
	}
	spfa(s);
	for(int i = 1; i <= n; i++){
		if(dis[i] == 0x3f3f3f3f) puts("NO PATH");
		else cout << dis[i] << endl;
	}
	return 0;
}
```

---

## 作者：hdgfgs (赞：2)

## 前言

首先看到这题有负边权，可能都会认为直接SPFA，
~~但显然出题人不可能这么sb~~，所以SPFA直接被特殊构造数据卡掉了。

#### 但，还是能被SPFA+SLF(双端队列)水过......


------------
##  思路
 
 因为每条道路（双向）都是非负的，航线（单向）可正可负，且**不存在“航环”（边至少由一条航线组成的环）**。

首先将道路（双向）加入图中，形成若干个联通块。
此时我们会发现**剩下的航线均为原图中的桥**。

（下证：若设航线起点为$u$，终点为$v$，且$u$，$v$处在同一联通块内，**故原必有一条由道路组成的路径联通（$u$，$v$），与航线构成环**，由题意可知不存在“航环”，矛盾，所以航线均为桥）

此时，我们在每个联通块中用$dijkstra$跑最短路，再采用**缩点**的思想，将每个联通块看成一个点，在加
入航线，组成有向无环图，在按照**拓扑排序**进行扫
描，可以在线性时间求出单源最短路。


时间复杂度：$O$($r+p+t*logt$)

------------
### 代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=25010,M=50010; 
ll t,r,p,s,a,b,c,cnt,num,INF;
ll bl[N],head[N],dist[N],in[N];
struct Edge{
	ll nxt,to,val;
}edge[M<<1];
struct node{
	ll rt,d;
	bool operator <(const node& op)const {
		return d>op.d; 
	}
};
vector <node> awy[N];
vector <ll> comp[N];
queue <ll> que;
priority_queue <node> q;
inline void add(ll u,ll v,ll w){edge[++cnt]=(Edge){head[u],v,w};head[u]=cnt;}
void dfs(ll u,ll c){
	bl[u]=c;
	comp[c].push_back(u);
	for(ll i=head[u];i;i=edge[i].nxt){
		ll v=edge[i].to;
		if(!bl[v]) dfs(v,c); 
	}
}
void dijkstra(ll er){
	while(q.size()){
		node u=q.top(); q.pop();
		if(u.d!=dist[u.rt]) continue;
		for(ll i=head[u.rt];i;i=edge[i].nxt){
			ll v=edge[i].to;
			if(dist[v]>dist[u.rt]+edge[i].val && dist[u.rt]<INF){
				dist[v]=dist[u.rt]+edge[i].val;
				q.push((node){v,dist[v]});
			}
		}
		for(ll i=0;i<awy[u.rt].size();i++){
			ll v=awy[u.rt][i].rt,w=awy[u.rt][i].d;
			if(dist[v]>dist[u.rt]+w && dist[u.rt]<INF) dist[v]=dist[u.rt]+w;
			//航线为桥，所以更新后不用加入优先队列。
        in[bl[v]]--; if(in[bl[v]]==0) que.push(bl[v]);
        //入度为0加入队列，拓扑排序
		}	
	}	
}	

void solve(){
	memset(dist,0x3f,sizeof(dist));
	INF=dist[0],dist[s]=0;
	while(que.size()){
		ll tt=que.front(); que.pop();
		for(ll i=0;i<comp[tt].size();i++){
			ll hh=comp[tt][i];
			q.push((node){hh,dist[hh]});//将每个联通块的点加入优先队列
		}
		dijkstra(tt);
	}
}
inline ll read(){
	ll x=0,f=1; char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while('0'<=ch && ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
int main(){
	t=read(),r=read(),p=read(),s=read();
	for(ll i=1;i<=r;i++){
		a=read(),b=read(),c=read();
		add(a,b,c),add(b,a,c);
	}
	for(ll i=1;i<=p;i++){
		a=read(),b=read(),c=read();
		awy[a].push_back((node){b,c});
	} 
	for(ll i=1;i<=t;i++) if(!bl[i]) dfs(i,++num);//深搜划分联通块	
	for(ll i=1;i<=t;i++)
		for(ll j=0;j<awy[i].size();j++)
			if(bl[i]!=bl[awy[i][j].rt]) in[bl[awy[i][j].rt]]++;
		
	for(ll i=1;i<=num;i++) if(in[i]==0) que.push(i);	
    //入度为0加入队列，拓扑排序
	
	solve();
	for(ll i=1;i<=t;i++){
		if(dist[i]==INF) puts("NO PATH");
		else printf("%lld\n",dist[i]);
	}
}
```


---

## 作者：封禁用户 (赞：2)

看到好多大佬的题解都是SPFA变形 我的想法是先判断处连通图 先把无向边加进去（全为正） 之后在内部用
使用dijkstra求最短路缩点开vector数组记录点 用一个普通队列记录所有把所有入度为0的连通图加进去 不断操作当入度为零时就加入队列
最后判断一下就是答案
```cpp
#include<bits/stdc++.h>
#define PII pair<int,int>
using namespace std;
int read() {
	int x=0,y=1;
	char ch=getchar();
	while(ch>'9'||ch<'0') {
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x*y;
}
const int maxn=3e5+7;
vector<int>a[maxn];
bool vis[maxn];
int col[maxn],dis[maxn],head[maxn],d[maxn];
int n,r,p,ss,en;
struct edge {
	int nxt,v,w;
} eg[maxn<<1];

void insert(int u,int v,int w) {
	eg[++en].nxt=head[u];
	eg[en].v=v;
	eg[en].w=w;
	head[u]=en;
//	d[col[v]]++;
}
queue<int>q;
void dfs(int u,int fa,int cnt) {
	if(col[u])return;
	col[u]=cnt;
	a[cnt].push_back(u);
	for(int i=head[u]; i; i=eg[i].nxt) {
		int v=eg[i].v;
		if(v!=fa){
			dfs(v,u,cnt);
		}
	}
}
int main() {
	int n=read(),r=read(),p=read(),ss=read();
	for(int i=1; i<=r; i++) {
		int u=read(),v=read(),w=read();
		insert(u,v,w);
		insert(v,u,w);
	}
	int cnt=0;
	for(int i=1; i<=n; i++) {
		if(!col[i]) {
			++cnt;
			dfs(i,i,cnt);
		}
	}
	for(int i=1; i<=p; i++) {
		int u,v,w;
		u=read(),v=read(),w=read();
		insert(u,v,w);
		d[col[v]]++;
	}
	memset(dis,0x3f,sizeof(dis));
		memset(vis,0,sizeof(vis));
	dis[ss]=0;
	for(int i=1;i<=cnt;i++){
		if(d[i]==0)q.push(i);
	}	
	while(q.size()){
		int x=q.front();q.pop();
		set<PII,less<PII> >s;
		int len=a[x].size();
		for(int i=0;i<len;i++){
			s.insert(make_pair(dis[a[x][i]],a[x][i]));
		} 
		while(!s.empty()){
			set<PII,less<PII> >::iterator it=s.begin();
			int u=it->second;s.erase(*it);
			for(int i=head[u];i;i=eg[i].nxt){
				int v=eg[i].v,w=eg[i].w;
				if(dis[u]+w<dis[v]){
					if(col[u]==col[v]){
						s.erase(make_pair(dis[v],v));
						dis[v]=dis[u]+w;
						s.insert(make_pair(dis[v],v));
					}
				}
				if(col[u]!=col[v]){
					dis[v]=min(dis[v],dis[u]+w);
					d[col[v]]--;
					if(d[col[v]]==0)q.push(col[v]); 
				}  
			}
			
		}
	}
	
	for(int i=1; i<=n; i++) {
			if(dis[i]>=1e9)puts("NO PATH");
		else
			cout<<dis[i]<<endl;
	}
	return 0;
}
```


---

## 作者：HMP_Haoge (赞：1)

此题正解是Tarjan缩点+连通块内Dij ~~（麻烦）~~，于是我们准备用**最短路**水过去！

最短路有Dijkstra和SPFA可供选择，但是呢题目告诉我们有负权边，所以基于贪心的Dij就裂开了，然而Dij能过样例 ~~（不要问我怎么知道的，我才不会告诉你我自己第一次就写的Dij）~~，于是我们就用上了SPFA，T飞了

### 怎么办呢？

### SLF优化！

由于本蒟蒻也是第一次用SLF优化，所以给来看题解却也不会SLF优化的巨佬和神犇们稍微讲解一下：

以下均为蒟蒻的一些见解，若有错误请各位大佬指正！

#### 首先是队列不同：

在普通的SPFA内，我们一般会定义这样的队列
```cpp
queue< int >q;
```
但是呢，SLF优化需要这个
```cpp
deque< int >q;
```
deque相比于queue可以支持双端的插入和退出操作，分别为
```cpp
q.push_front(a);
q.push_back(a);
q.pop_front();
q.pop_back();
```

#### 第二是SLF优化思想

普通的SPFA是只会在队头插入值，而SLF优化会在插入前与队头元素进行比较。

如果当前点比队头元素的dis值小，则将其插入到队头，否则将其插入到队尾。

原因是优先拓展更优的点可以减少拓展不优的点，从而减少总的入队次数，使SPFA更快地收束。

核心代码如下
```cpp
if(!q.empty()&&dist[v]>=dist[q.front()]) q.push_back(v);
else q.push_front(v);
```


讲的差不多了，放一下完整代码
```
#include<bits/stdc++.h>
using namespace std;
#define ri register int
#define MAXM 1000100
#define MAXN 100010

struct node
{
	int from,to,dis;
} edge[MAXM];
int head[MAXM],cnt,n,r,p,s,dist[MAXN];
bool vis[MAXN];

template< typename T >inline void read(T &x)
{
	x=0;
	char c=getchar();
	int f=1;
	for(; !isdigit(c); c=getchar()) if(c=='-') f=-1;
	for(; isdigit(c); c=getchar()) x=((x<<3)+(x<<1)+(c^48));
	x*=f;
}
template< typename T >inline void write(T x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
inline void add(int from,int to,int dis)
{
	edge[++cnt].from=head[from];
	edge[cnt].to=to;
	edge[cnt].dis=dis;
	head[from]=cnt;
}
inline void SPFA(int s)
{
	deque< int >q;
	memset(dist,0x3f,sizeof(dist));
	dist[s]=0;
	q.push_back(s);
	vis[s]=1;
	while(!q.empty())
	{
		int now=q.front();
		q.pop_front();
		for(ri i=head[now]; i; i=edge[i].from)
		{
			int v=edge[i].to;
			if(dist[v]>dist[now]+edge[i].dis)
			{
				dist[v]=dist[now]+edge[i].dis;
				if(!vis[v])
				{
					if(!q.empty()&&dist[v]>=dist[q.front()]) q.push_back(v);
					else q.push_front(v);
					vis[v]=1;
				}
			}
		}
		vis[now]=0;
	}
}

int main()
{
	read(n);
	read(r);
	read(p);
	read(s);
	int u,v,w;
	for(ri i=1; i<=r; ++i)
	{
		read(u);
		read(v);
		read(w);
		add(u,v,w);
		add(v,u,w);
	}
	for(ri i=1; i<=p; ++i)
	{
		read(u);
		read(v);
		read(w);
		add(u,v,w);
	}
	SPFA(s);
	for(ri i=1; i<=n; ++i)
	{
		if(dist[i]==1061109567) //注意这里不能直接写dist[i]==0x3f 
		{
			printf("NO PATH");
			putchar('\n');
		}
		else
		{
			write(dist[i]);
			putchar('\n');
		}
	}
	return 0;
}
```

---

## 作者：crh1272336175 (赞：1)

本题是一题很明显的最短路，而且不能直接使用Dijkstra算法。如果直接使用SPFA会TLE。于是蒟蒻只能挖掘题目信息

本题有一个特殊条件——双向边非负，单向边可能为负。所以可以先将所有双向边添加到图里，形成若干个连通块。把每一个联通块看成一个点，再把单向边加入图中。接下去可以使用拓扑排序的框架。具体请看代码：

```cpp
#include<bits/stdc++.h>
#pragma GCC opitimize(3)
using namespace std;
const int N=25005,M=50005;
int n,m,p,s,tot,cnt;
int head[N],Next[M<<2],des[M<<2],len[M<<2];
int c[N],dist[M<<2],deg[M<<2],v[N];
queue<int> qu;
vector<int> out[N];
inline int read()
{
    int s=0,f=1; char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)) s=s*10+(ch^48),ch=getchar();
    return s*f;
}
inline void write(int x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
inline void add(int a,int b,int c)
{
	Next[++tot]=head[a]; des[tot]=b; len[tot]=c;
	head[a]=tot;
}
int dfs(int x)
{
	c[x]=cnt;
	out[cnt].push_back(x);//一个小优化：记录出边。这样不会被卡掉，否则会被特殊数据卡掉 
	for(register int i=head[x]; i; i=Next[i])
	{
		int y=des[i];
		if(!c[y]) dfs(y);
	}
}//求连通块 
struct node
{
	int x; double p;
	bool operator < (node &B) const 
	{
		return p<B.p;
	}
};
struct prique
{
	node q[M<<2];
	int tot;
	int size(){return tot;}
	int top(){return q[1].x;}
	void push(int x,double z){
		q[++tot].x=x;q[tot].p=z;
		int p=tot;
		while(p>1){
			if(q[p]<q[p>>1]){swap(q[p],q[p>>1]);p>>=1;}
			else break;
		}
	}
	void pop(){
		int p=1,s=2;
		q[1]=q[tot],tot--;
		while(s<=tot){
			if(s<tot&&q[s+1]<q[s])s++;
			if(q[s]<q[p]){swap(q[s],q[p]);p=s,s<<=1;}
			else break;
		}
	}
}q;//手写堆效率更高 
int main()
{
	n=read(),m=read(),p=read(),s=read();
	for(register int i=1; i<=m; i++)
	{
		int a=read(),b=read(),c=read();
		add(a,b,c); add(b,a,c);//添加无向边 
	}
	for(register int i=1; i<=n; i++)//寻找连通块 
	    if(!c[i])
	    {
	    	cnt++;
	    	dfs(i);
		}
	for(register int i=1; i<=p; i++)
	{
		int x=read(),y=read(),z=read();
		add(x,y,z);
		++deg[c[y]];//拓扑思想 
	}
	qu.push(c[s]);
	for(register int i=1; i<=cnt; i++)
	    if(deg[i]==0) qu.push(i);
	memset(dist,0x7f,sizeof dist);
	dist[s]=0;
	while(!qu.empty())
	{
		int now=qu.front(); qu.pop();
		for(int i=0; i<out[now].size(); i++)//将所有该连通块的点加入堆 
		{
			int t=out[now][i];
			q.push(t,dist[t]);
		}
		while(q.size())
		{
			int x=q.top(); q.pop();
			if(v[x]) continue;
			v[x]=1;
			for(int i=head[x]; i; i=Next[i])
			{
				int y=des[i],z=len[i];
				if(dist[y]>dist[x]+z)
				{
					dist[y]=dist[x]+z;
					if(c[x]==c[y]) q.push(y,dist[y]);//如果还在连通块内部 
				}
				if(c[x]!=c[y]) 
				{
					deg[c[y]]--;
					if(deg[c[y]]==0) qu.push(c[y]);//拓扑思想 
				}
			}
		}
	}
	for(register int i=1; i<=n; i++)
	    if(dist[i]>0x3f3f3f3f) puts("NO PATH");
	    else write(dist[i]),puts(" ");
	return 0;
} 
```


---

## 作者：Adam_Ng (赞：1)

非正解解法：Johnson算法（大材小用）

不会Johnson的各位可以自行学习一下，或者跳过这篇题解。

先用Bellman-Ford+SLF求出re-weight所用的数组h

于是就把负权边变正了，再跑一遍Dijkstra就出来了。

还好这题没把Bellman-Ford卡死。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 25010, M = 100005;
typedef pair<int, int> pii;
int n, r, p, s;

struct node {
	int nxt, to, dis;
}e[M << 2];
int head[N], cnt = 0;
void add(int nxt, int to, int dis) {
	e[++cnt].nxt = head[nxt];
	e[cnt].to = to;
	e[cnt].dis = dis;
	head[nxt] = cnt;
}

int h[N], dis[N], vis[N];

void BellmanFord() {
	int S = n + 1;
	for(int i = 1; i <= n; ++i) add(S, i, 0);
	memset(h, 0x3f, sizeof(h));
	memset(vis, 0, sizeof(vis));
	deque<int> dq;
	dq.push_back(S); vis[S] = 1; h[S] = 0;
	while(!dq.empty()) {
		int u = dq.front(); dq.pop_front();
		vis[u] = 0;
		for(int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if(h[v] > h[u] + e[i].dis) {
				h[v] = h[u] + e[i].dis;
				if(!vis[v]) {
					vis[v] = 1;
					if(!dq.empty() && h[v] >= h[dq.front()]) dq.push_back(v);
					else dq.push_front(v);
				}
			}
		}
	}
}

void Dijkstra() {
	memset(vis, 0, sizeof(vis));
	memset(dis, 0x3f, sizeof(dis));
	priority_queue<pii, vector<pii>, greater<pii> > que;
	dis[s] = 0;
	que.push(pii(0, s));
	while(!que.empty()) {
		int u = que.top().second; que.pop();
		vis[u] = 1;
		for(int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if(dis[v] > dis[u] + e[i].dis + h[u] - h[v]) {
				dis[v] = dis[u] + e[i].dis + h[u] - h[v];
				que.push(pii(dis[v], v));
			}
		}
	}
}

void Johnson() {
	BellmanFord(); Dijkstra();
}
int main() {
	scanf("%d%d%d%d", &n, &r, &p, &s);
	for(int i = 1; i <= r; ++i) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		add(a, b, c); add(b, a, c);
	}
	for(int i = 1; i <= p; ++i) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		add(a, b, c);
	}
	Johnson();
	for(int i = 1; i <= n; ++i) {
		if(dis[i] == 0x3f3f3f3f) printf("NO PATH\n");
		else printf("%d\n", dis[i] + h[i] - h[s]);
	}
}
```


---

## 作者：Partial (赞：1)

- 最短路（因为有负权所以用SPFA）
- 然后又T了两个点（#7#8）所以用了deque
- 具体实现如下
```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
using namespace std;
const int N=30005;
int n,m,r,p,s;
int dis[N],vis[N];
vector<pii>G[N];
int read()
{
	int w=1,q=0;char ch=' ';
	while(ch!='-'&&(ch<'0'||ch>'9'))ch=getchar();
	if(ch=='-')w=-1,ch=getchar();
	while(ch>='0'&&ch<='9')q=10*q+ch-'0',ch=getchar();
	return w*q;
}
int main()
{
	n=read();r=read();p=read();s=read();
	for(int i=1;i<=r;++i){
		int x=read(),y=read(),w=read();
		G[x].push_back(make_pair(y,w));
		G[y].push_back(make_pair(x,w));
	}
	for(int i=1;i<=p;++i)
	{
		int x=read(),y=read(),w=read();
		G[x].push_back(make_pair(y,w));
	}
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0;vis[s]=1;
	deque<int>q;
	q.push_back(s);
	while(!q.empty())
	{
		int x=q.front(),len=G[x].size();q.pop_front();vis[x]=0;
		for(int i=0;i<len;++i)
		{
			int y=G[x][i].first,w=G[x][i].second;
			if(dis[y]>dis[x]+w)
			{
				dis[y]=dis[x]+w;
				if(!vis[y]){
					vis[y]=1;
					if(q.empty()||dis[y]>=dis[q.front()])q.push_back(y);
					else q.push_front(y);
				}
			}
		}
	}
	for(int i=1;i<=n;++i)
	{
		if(dis[i]==0x3f3f3f3f)printf("NO PATH\n");
	    else printf("%d\n",dis[i]);
	}
	return 0;
} 
```



---

## 作者：公元某年的猫 (赞：1)

应该算是比较水的省选题了，可用SPFA+SLF即可。

楼下神犇说的很清楚了，但有些地方不够准确，就是在用双端队列时要与队头比较，如果小于队头，就把这个点放入队首，这也可以避免多余的松弛。

要注意读入优化，下面的程序加优化可以800多ms，不加的话900多ms







```cpp
#include<iostream>
#include<cstring>
#include<queue>
#include<cstdio>
using namespace std;
const int MAX_N = 1e5, MAX_M = 1e5, INF = 1<<30;
deque<int> q;
struct edge {
    int v, w, next;
} e[MAX_M * 2];
int n, r, p, s, count, dis[MAX_N], head[MAX_N];
bool vis[MAX_N];
inline int read() {
    int x = 0, w = 1;
    char ch = 0;
    while (ch < '0' || ch > '9') {
        if (ch == '-') w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x<<3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return x * w; 
}
/*inline void write(int x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
    return ; 
}*/
void init() {
    int i;
    for (i = 1; i <= n; i++) {
        head[i] = -1;
        dis[i] = INF;
    }
    return ;
}
void add(int a, int b, int c) {
    e[++count].v = b;
    e[count].w = c;
    e[count].next = head[a];
    head[a] = count;
    return ; 
}
void spfa(int u) {
    int i;
    dis[u] = 0;
    q.push_back(u);
    vis[u] = true;
    while (!q.empty()) {
        int k = q.front();
        q.pop_front();
        for (i = head[k]; i + 1; i = e[i].next) {
            if (dis[e[i].v] > dis[k] + e[i].w) {
                dis[e[i].v] = dis[k] + e[i].w;
                if (!vis[e[i].v]) {
                    if (!q.empty() && dis[e[i].v] < dis[q.front()]) {
                        q.push_front(e[i].v);
                        vis[e[i].v] = true;
                    }
                    else {
                        q.push_back(e[i].v);
                        vis[e[i].v] = true;
                    }
                }
            }
        }
        vis[k] = false;
    }
    return ;
}
int main() {
    n = read(), r = read(), p =read(), s = read();
    int i, x, y, z;
    init();
    for (i = 1; i <= r; i++) {
        x = read(), y =read(), z = read();
        add(x, y, z);
        add(y, x, z);
    }
    for (i = 1; i <= p; i++) {
        x = read(), y = read(), z = read();
        add(x, y, z);
    }
    spfa(s);
    for (i = 1; i <= n; i++) {
        if (dis[i] == INF) printf("NO PATH\n");
        else printf("%d\n", dis[i]);
    }
    return 0;
}
```

---

## 作者：_LHF_ (赞：1)

### 大家好，我非常喜欢暴力，于是我用 SPFA 通过了此题。
听说有人用 SPFA 的 SLF 优化碾过去了。

众所周知： SPFA+堆 在负权图上的复杂度是指数级的，所以堆优就别想了。

但是可以用模拟退火思想呀。

啊！？啥事模拟退火？

具体是这样的：

首先先选择一个值，跑一遍普通的 SPFA，要求每个点入队的次数小于某个值。

显然，这样子跑出来的不一定是最优解。

怎么办？再跑一次呗。

可这，复杂度好像没有变呀。

等等，我们刚才已经求出的一些有用的东西：目前从原点到该点的最短路（不一定是真正的最短路），把点按距离从小到大排序，再加入队列中。

然后再加点 SPFA 的常见优化，详见 [UNVRS的博客（比较详细）](https://www.luogu.com.cn/blog/UNVRS/SPFA-PMF) 和 [本蒟蒻的博客（比较简略）](https://www.luogu.com.cn/blog/LHF/fu-huo-spfa)。

剩下的就是调整参数的问题了。

代码：
```cpp
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#define ll long long
#define N 200010
#define ri register int
using namespace std;
int k[N],n,f[N],K;
ll ans;
bool cmp(int a,int b)
{
	return f[a]<f[b];
}
struct my_queue{
	private:
	int q[26214000],p[N],head,tail,w,i,cnt;
	void change(int&x,int&y){
		x^=y^=x^=y;
	}
	public:
	void push(int x)
	{
		if(p[x]) return;
		p[x]=1;
		q[tail++]=x;
		if(head<tail-1&&f[q[tail-1]]>f[q[tail-2]])
			change(q[tail-1],q[tail-2]);
	}
	int top()
	{
		for(i=1;i<=K&&head+i<tail-i;i++)
		{
			if(f[q[tail-i]]<f[q[head+i]]) change(q[tail-i],q[head+i]);
			if(f[q[head+i]]<f[q[head]]) change(q[head+i],q[head]);
		}
		p[q[head]]=0;
		return q[head++];
	}
	void clear(){for(ri i=1;i<=n;i++) p[i]=0;head=tail=1;}
	bool empty(){return head==tail;}
}q;
struct edge{
	int next,to,s;
}e[N<<2];
int first[N],len,s,x,y,z,c[N],bz;
void add(int a,int b,int c)
{
	e[++len].to=b;
	e[len].next=first[a];
	first[a]=len;
	e[len].s=c;
}
void spfa(int x,int B)
{
	f[x]=0;
	q.push(x);
	while(!q.empty())
	{
		x=q.top();
		for(int i=first[x],v;i;i=e[i].next)
			if(f[x]+e[i].s<f[(v=e[i].to)]&&++c[v]<=B)
			{
				f[v]=f[x]+e[i].s;
				q.push(v);
			}
	}
	q.clear();
}
int m1,m2;
int main()
{
	q.clear();
	scanf("%d%d%d%d",&n,&m1,&m2,&s);
	for(int i=1;i<=n;i++) k[i]=i;
	for(int i=1;i<=m1;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
		add(y,x,z);
	}
	for(int i=1;i<=m2;i++)
		scanf("%d%d%d",&x,&y,&z),
		add(x,y,z);
	for(int j=1;j<=n;j++) f[j]=1e9;
	for(int i=1;i<=20;i++)
	{
		K=(i+10)/8;
		spfa(s,30);
		sort(k+1,k+n+1,cmp);
		for(int j=1;j<=n&&f[k[j]]<1e9;j++)
			c[k[j]]=0,q.push(k[j]);
	}
	K=1;
	spfa(s,1e9);
	for(int i=1;i<=n;i++)
	{
		if(f[i]<1e9) printf("%d\n",f[i]);
		else printf("NO PATH\n");
	}
}
```
~~喜欢就点个赞呗~~

---

## 作者：lzcjoe (赞：1)

### 题面

1503：道路和航线

时间限制: 1000 ms 内存限制: 65536 KB

【题目描述】

原题来自：USACO 2011 Jan. Gold

Farmer John 正在一个新的销售区域对他的牛奶销售方案进行调查。他想把牛奶送到T个城镇 ，编号为1到T。这些城镇之间通过R条道路（编号为1到R）和P条航线（编号为1到P）连接。每条道路i或者航线i连接城镇Ai到Bi，花费为Ci。

对于道路，0≤Ci≤10^4，然而航线的花费很神奇，花费Ci可能是负数。道路是双向的，可以从Ai到Bi，也可以从Bi到Ai，花费都是Ci。然而航线与之不同，只可以从Ai到Bi。

事实上，由于最近恐怖主义太嚣张，为了社会和谐，出台了一些政策保证：如果有一条航线可以从Ai到Bi，那么保证不可能通过一些道路和航线从Bi回到Ai。由于 FJ 的奶牛世界公认十分给力，他需要运送奶牛到每一个城镇。他想找到从发送中心城镇S把奶牛送到每个城镇的最便宜的方案，或者知道这是不可能的。

【输入】

第一行为四个空格隔开的整数：T,R,P,S；

第二到第R+1行：三个空格隔开的整数（表示一条道路）：Ai,Bi和Ci；第R+2到R+P+1行：三个空格隔开的整数（表示一条航线）：Ai,Bi和Ci。

【输出】

输出T行，第i行表示到达城镇i的最小花费，如果不存在输出 NO PATH。

【输入样例】

6 3 3 4 

1 2 5 

3 4 5 

5 6 10 

3 5 -100 

4 6 -100 

1 3 -10

【输出样例】

NO PATH 
NO PATH 
5 
0 
-95 
-100

【提示】

样例说明

一共六个城镇。在1和2，3和4，5和6之间有道路，花费分别是5,5,10。同时有三条航线：3→5，4→6和1→3，花费分别是-100,−100,−10。FJ 的中心城镇在城镇4。FJ 的奶牛从4号城镇开始，可以通过道路到达3号城镇。然后他们会通过航线达到5和6号城镇。但是不可能到达1和2号城镇。

数据范围：

对于全部数据，1≤T≤2.5×10^4,1≤R,P≤5×10^4,1≤Ai,Bi,S≤T。保证对于所有道路，0≤Ci≤10^4,对于所有航线，−10^4≤Ci≤10^4。

### 算法

SPFA优化

本题是简单的单源最短路的问题，有负权边，需要用SPFA算法解决。实际操作时发现SPFA运行此题数据会超时，因而需要进行优化。

**常见简单优化**

1. SLF优化

将队列建成双端队列，在遇到要插入的点的最短路比当前的队头的最短路短就插入队首，否则插入队尾。

若最短路较短，则更容易松弛，也更容易获得最短路，这个点的“使用效率”高，则队列操作次数就会减少。

双端队列用STL deque 实现。

2. LLL优化

在抽出队首时，如果队首的最短路比全体最短路平均值大，将其放至队尾，不断迭代直到找到不符合条件的再进行算法。

一样是使队首对应的最短路较短。

本题使用SLF优化即可通过，代码为SLF优化版本。

### 代码

```cpp
#include<cstdio>
#include<cstring>
#include<deque>
int t,r,p,s;
struct node
{
	int to;
	int w;
	int next;
}edge[150005];
int cnt;
int head[25005];
inline void add(int u,int v,int w)
{
	cnt++;
	edge[cnt].to=v;
	edge[cnt].next=head[u];
	head[u]=cnt;
	edge[cnt].w=w;
}//链式前向心建图
int dis[25005];
char book[25005];
std::deque<int> q;//双端队列
int main()
{
	scanf("%d%d%d%d",&t,&r,&p,&s);
	int a,b,c;
	for(int i=1;i<=r;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		add(a,b,c);
		add(b,a,c);
	}
	for(int i=1;i<=p;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		add(a,b,c);
	}
	memset(dis,0x3f,sizeof(dis));
	//读入、建图、初始化
    dis[s]=0;
	q.push_back(s);
	while(!q.empty())
	{
		int i=q.front();
		q.pop_front();
		book[i]=0;
		for(int j=head[i];j!=0;j=edge[j].next)
		{
			if(dis[edge[j].to]>dis[i]+edge[j].w)
			{
				dis[edge[j].to]=dis[i]+edge[j].w;
				if(book[edge[j].to]==0)
				{
					book[edge[j].to]=1;
					if(!q.empty() && dis[q.front()]>dis[edge[j].to])
					{
						q.push_front(edge[j].to);
					}
					else
					{
						q.push_back(edge[j].to);
					}//SLF双端队列优化
				}
			}
		}
	}
	for(int i=1;i<=t;i++)
	{
		if(dis[i]==0x3f3f3f3f)
		{
			puts("NO PATH");
		}
		else
		{
			printf("%d\n",dis[i]);
		}
	}//输出
	return 0;
}
```

#### 运行结果

一本通OJ：

1503

通过 100分

测试点1: 答案正确 536KB 1MS 

测试点2: 答案正确 532KB 1MS 

测试点3: 答案正确 536KB 1MS 

测试点4: 答案正确 556KB 1MS 

测试点5: 答案正确 588KB 2MS 

测试点6: 答案正确 812KB 8MS 

测试点7: 答案正确 1316KB 31MS 

测试点8: 答案正确 1644KB 45MS 

测试点9: 答案正确 2052KB 65MS 

测试点10: 答案正确 2548KB 151MS 

测试点11: 答案正确 2468KB 111MS 

测试点12: 答案正确 2512KB 113MS 

测试点13: 答案正确 2084KB 101MS 

测试点14: 答案正确 1940KB 49MS 

测试点15: 答案正确 1352KB 205MS 

测试点16: 答案正确 2528KB 395MS 

洛谷：

用时 2.53s 内存 2.78MB

测试点信息

3ms/816.00KB 
AC #1

300ms/2.64MB 
AC #2

171ms/2.38MB 
AC #3

181ms/2.78MB 
AC #4

201ms/2.12MB 
AC #5

74ms/1.88MB 
AC #6

533ms/1.41MB 
AC #7

862ms/2.50MB 
AC #8

3ms/632.00KB 
AC #9

3ms/808.00KB 
AC #10

3ms/644.00KB 
AC #11

4ms/760.00KB 
AC #12

9ms/1.00MB 
AC #13

43ms/1.54MB 
AC #14

58ms/1.90MB 
AC #15

85ms/2.13MB 
AC #16

---

## 作者：HH_Halo (赞：0)

## 思路分析
* 题意很明确，求带负边的最短路。~~诶，别上去就跑 spfa 啊，这可是 USACO~~。
* 众所周知，USACO 喜欢卡 $spfa$，可是有负边有不能用 $Dijkstra$ ，这怎么搞？
* 还是先说一下 $Dijkstra$ 为什么不能跑负边吧。$Dijkstra$ 的核心是由贪心得来的，即长边是有最短的边松弛的，而在有负边的图中，因为负边不论多长都会使长边更短，所以贪心不成立
* 但是这道题的负边很特殊，是单向的，如果先不考虑负边的呢？那么这时候整个图的联通性是无法保证的，会形成许多个由无向边形成的联通块。
* 在联通块内没有负边，所以是可以跑 $Dijkstra$ 的，其实这时加上负边，对不同的联通块跑 $Dijkstra$ 也是不会出问题的，因为这条负边是桥，也就是不可或却、必定经过的。
* 接下来就很简单了，用拓扑排序依次更新每个联通块。哦，对了，题目给了中心城市，所以先把中心城市所在的联通块加进去

## $Code$
```c++
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#include<queue>
#define R register
#define N 200010
using namespace std;
inline int read(){
	int x = 0,f = 1;
	char ch = getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
int n,r,p,s,cnt,head[N],dis[N],in[N],belong[N];
bool vis[N];
struct edge{
	int to,next,dis;
}e[N<<2];
int len;
void addedge(int u,int v,int w){
	e[++len].to = v;
	e[len].dis = w;
	e[len].next = head[u];
	head[u] = len;
}
vector<int>sta[N];
void dfs(int u){//求出每个点所在的联通块
	belong[u] = cnt;
	sta[cnt].push_back(u);
	for(R int i = head[u];i;i = e[i].next){
		int v = e[i].to;
		if(belong[v])continue;
		dfs(v);
	}
}
struct node{
	int dis,id;
	node(){}
	node(int _dis,int _id){dis = _dis,id = _id;}
	inline bool operator <(const node &a)const{
		return dis > a.dis;
	}
};
priority_queue<node>q;
queue<int>qq;
void Dij(){
	while(!q.empty()){
		int u = q.top().id;q.pop();
		if(vis[u])continue;
		vis[u] = 1;
		for(R int i = head[u];i;i = e[i].next){
			int v = e[i].to;
			if(dis[v]>dis[u]+e[i].dis){
				dis[v] = dis[u] + e[i].dis;
				if(belong[u]==belong[v])q.push(node(dis[v],v));
			}
			if(belong[u]!=belong[v]){
				in[belong[v]]--;
				if(!in[belong[v]])qq.push(belong[v]);
			}
		}
	}
}
void Topo(){//拓扑排序以此更新每个联通块最短路
	qq.push(belong[s]);
	for(R int i = 1;i <= cnt;i++)if(!in[i])qq.push(i);
	memset(dis,0x7f,sizeof(dis));//0x3f会wa的
	dis[s] = 0;
	while(!qq.empty()){
		int u = qq.front();qq.pop();
		for(R int i = 0;i < sta[u].size();i++)q.push(node(dis[sta[u][i]],sta[u][i]));
		Dij();
	}
}
int main(){
	n = read(),r = read(),p = read(),s = read();
	for(R int i = 1;i <= r;i++){
		int a = read(),b = read(),c = read();
		addedge(a,b,c);
		addedge(b,a,c);
	}
	for(R int i = 1;i <= n;i++){
		if(!belong[i]){
			cnt++;
			dfs(i);
		}
	}
	for(R int i = 1;i <= p;i++){
		int a = read(),b = read(),c = read();
		in[belong[b]]++;//入度++
		addedge(a,b,c);
	}
	Topo();
	for(R int i = 1;i <= n;i++){
		if(dis[i]>=0x3f3f3f3f)puts("NO PATH");
		else printf("%d\n",dis[i]);
	}
	return 0;
}
```

---

