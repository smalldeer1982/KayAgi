# Police Stations

## 题目描述

Inzane finally found Zane with a lot of money to spare, so they together decided to establish a country of their own.

Ruling a country is not an easy job. Thieves and terrorists are always ready to ruin the country's peace. To fight back, Zane and Inzane have enacted a very effective law: from each city it must be possible to reach a police station by traveling at most $ d $ kilometers along the roads.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF796D/3d1a9e2d88191523d4bc40bc87e14f9eb6074cc0.png)There are $ n $ cities in the country, numbered from $ 1 $ to $ n $ , connected only by exactly $ n-1 $ roads. All roads are $ 1 $ kilometer long. It is initially possible to travel from a city to any other city using these roads. The country also has $ k $ police stations located in some cities. In particular, the city's structure satisfies the requirement enforced by the previously mentioned law. Also note that there can be multiple police stations in one city.

However, Zane feels like having as many as $ n-1 $ roads is unnecessary. The country is having financial issues, so it wants to minimize the road maintenance cost by shutting down as many roads as possible.

Help Zane find the maximum number of roads that can be shut down without breaking the law. Also, help him determine such roads.

## 说明/提示

In the first sample, if you shut down road $ 5 $ , all cities can still reach a police station within $ k=4 $ kilometers.

In the second sample, although this is the only largest valid set of roads that can be shut down, you can print either 4 5 or 5 4 in the second line.

## 样例 #1

### 输入

```
6 2 4
1 6
1 2
2 3
3 4
4 5
5 6
```

### 输出

```
1
5
```

## 样例 #2

### 输入

```
6 3 2
1 5 6
1 2
1 3
1 4
1 5
5 6
```

### 输出

```
2
4 5 ```

# 题解

## 作者：lenlen (赞：15)

### Problem

题目大意：给定一棵树，树上有一些点是警察局，保证任意一个点到其最近的警察局的距离小于 $d$，求最多能删掉几条边使这个条件依然成立（警察局可能重复）。

数据范围： $n \leq 3 \times 10^5,d \leq n-1$。

### Solution

一个很简单的贪心（~~所以为什么会在 DP 专栏里~~），因为保证最开始的时候满足，所以 $d$ 其实就没什么用了，我们可以把所有警察局（去重之后）丢到队列里面进行广搜，然后给每个点染色。由于广搜的性质，可以发现给每一个节点染色的警察局一定是离这个节点最近的警察局。那么我们就可以让两个染色不同的节点之间的边断掉，这样的话我们仍保证了两端节点仍有一个警察局相连，也就满足条件。

### Code

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+7232;
int n,m,d,dis[N],ans;
int x,y;
struct len{
    int u,v;
}t[N];
struct hl{
    int v,nxt;
}e[N<<1];
int cnt,h[N];
void add(int u,int v)
{
    e[++cnt].v=v,e[cnt].nxt=h[u],h[u]=cnt;
}
struct llt{
    int x,op;//op代表给它染色的警察局
}tmp;
queue<llt> q;
int main()
{
    scanf("%d%d%d",&n,&m,&d);
    for(int i=1;i<=m;++i) 
    {
        scanf("%d",&x);
        if(!dis[x]) dis[x]=x,q.push((llt){x,x});//记得去重
    }
    for(int i=1;i<n;++i)
    {
        scanf("%d%d",&t[i].u,&t[i].v);
        add(t[i].u,t[i].v),add(t[i].v,t[i].u);
    }
    while(!q.empty())//广搜
    {
        tmp=q.front(),q.pop();
        for(int i=h[tmp.x],v;i;i=e[i].nxt)
        {
            if(dis[(v=e[i].v)]) continue;
            dis[v]=tmp.op;
            q.push((llt){v,tmp.op});
        }
    }
    for(int i=1;i<n;++i)
    if(dis[t[i].u]!=dis[t[i].v]) ++ans;//统计答案
    printf("%d\n",ans);
    for(int i=1;i<n;++i)
    if(dis[t[i].u]!=dis[t[i].v]) printf("%d ",i);
}
```


---

## 作者：lukelin (赞：5)

这题就是一个贪心思想，把所有有警察局的点扔进出始队列里广搜，并把从不同的警察局搜索到的点染不同的色  
枚举任意两条边，如果它的两端颜色不同，把它加入ans数组  
完结撒花

贴个代码
```cpp
#include <cstdio>
#include <algorithm>
#include <queue>
#define max(a,b) ((a>b)?a:b)

using namespace std;

inline int read(){
    int x = 0; int zf = 1; char ch = ' ';
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') zf = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); return x * zf;
}

struct Edge{
    int to, next;
} edges[600005];
int head[300005], edge_num = 0;

void addEdge(int from, int to){
    edges[++edge_num] = (Edge){to, head[from]};
    head[from] = edge_num;
}

struct Node{
    int id;
    int clr;
};

queue<Node> que;
int vis[300005];

int ans[300005], ans_num = 0;

void BFS(){
    Node u;
    while (!que.empty()){
        u = que.front(), que.pop();
        for (int c_e = head[u.id]; c_e; c_e = edges[c_e].next){
            int v = edges[c_e].to;
            if (!vis[v]){
                vis[v] = u.clr;
                que.push((Node){v, u.clr});
            }
        }
    }
}

int u[300005], v[300005];

int main(){
    int n = read(), k = read(), d = read();
    int clr = 0, kk = 0;
    for (int i = 1; i <= k; ++i){
        int pol = read();
        if (!vis[pol]){
            ++kk;
            que.push((Node){pol, ++clr});
            vis[pol] = clr;
        }
    }
    for (int i = 1; i < n; ++i){
        u[i] = read(), v[i] = read();
        addEdge(u[i], v[i]), addEdge(v[i], u[i]);
    }
    BFS();
    for (int i = 1; i < n; ++i)
        if (vis[u[i]] != vis[v[i]])
            ans[++ans_num] = i;
    printf("%d\n", ans_num);
    for (int i = 1; i <= ans_num; ++i){
        if(i != 1)
            printf(" ");
        printf("%d", ans[i]);
    }
    return 0;
}
```

---

## 作者：mot1ve (赞：3)

一道挺巧妙的树上问题。树上有一些警察局，求所有点到警察局距离不超过 $d$ 的情况下最多能删多少条边。此题其实用不到 $d$ 这个条件，因为题目已经保证原始树是满足要求的。那么要求距离最短，还是在树上，很容易想到广搜，如果把所有警察局放到一个队列里开始广搜，根据广搜的性质，每次被标记到的点一定是这个点离所有警察局最近的距离。那么我们可以考虑染色，每个警察局都赋予一种颜色。如何判断哪些边可以删呢？这条边两端点颜色不同就可以了。因为颜色不同保证了这个边被删去后，端点依然可以到达其中一个警察局，并且由于广搜的性质，这个警察局一定是离他最近的，而题目又保证了离他最近的警察局距离一定不超过 $d$ ，所以压根不需要考虑 $d$ 。


```
//bfs染色 
#include<bits/stdc++.h>
using namespace std;
int n,k,d,idx,col;
int vis[1000010],head[1000010],u[1000010],v[1000010];
struct node{
	int nxt,to;
}edge[1000010];
vector<int> g;
void add(int u,int v)
{
	edge[++idx].nxt=head[u];
	edge[idx].to=v;
	head[u]=idx;
}
queue< pair<int,int> > q;
void bfs()
{
	while(q.size())
	{
		int x=q.front().first;
		int y=q.front().second;
		q.pop();
		for(int i=head[x];i;i=edge[i].nxt)
		{
			int v=edge[i].to;
			if(!vis[v])
			{
				vis[v]=y;
				q.push(make_pair(v,y));
			}
		}
	}
}
int main()
{
	cin>>n>>k>>d;
	for(int i=1;i<=k;i++)
	{
		int x;
		scanf("%d",&x);
		if(vis[x])
		continue;
		vis[x]=++col;
		q.push(make_pair(x,col));
	}
	for(int i=1;i<=n-1;i++)
	{
		scanf("%d%d",&u[i],&v[i]);
		add(u[i],v[i]);
		add(v[i],u[i]);
	}
	bfs();
	for(int i=1;i<=n-1;i++)
	{
		if(vis[u[i]]!=vis[v[i]])
		g.push_back(i);
	}
	cout<<g.size()<<endl;
	for(auto i : g)
	{
		printf("%d ",i);
	}
	return 0;
}
```

---

## 作者：泠小毒 (赞：3)

# Police Stations
给定一棵树，树上有一些点是警察局，要求所有点到最近的警察局的距离不大于d，求最多能删几条边
## 广告插入
在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190516/)

[博客园(同步更新)](https://www.cnblogs.com/muronglin/p/hgoi-20190516.html)
## 解法
建一个超级源连着所有警察局，或者一开始就把所有警察局压入队列，跑bfs

如果这条边过去的点被访问过，那这条边就可以删除

bfs的退出条件不是点有没有被搜过，而是边有没有被搜索和距离是否超过d
## ac代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{int to,next,v;}e[600010];
struct Node{int num,d;};
int n,k,d,cnt=1,ans=0,x,y,head[300010],vis[300010],flg[300010],res[300010];
queue<Node>q;
void add(){e[++cnt]={y,head[x],0},head[x]=cnt,e[++cnt]={x,head[y],0},head[y]=cnt;}
void bfs()
{
	while(!q.empty())
	{
		Node u=q.front();
		q.pop();
		flg[u.num]=0;
		if(u.d>d)continue;
		for(int i=head[u.num];i;i=e[i].next)
		{
			if(e[i].v)continue;
			e[i].v=e[i^1].v=1;
			if(vis[e[i].to])res[++ans]=i/2;
			if(!flg[e[i].to])q.push({e[i].to,u.d+1}),flg[e[i].to]=vis[e[i].to]=1;
		}
	}
}
int main()
{
	scanf("%d%d%d",&n,&k,&d);
	for(int i=1;i<=k;i++)scanf("%d",&x),q.push({x,0}),vis[x]=1;
	for(int i=1;i<n;i++)scanf("%d%d",&x,&y),add();
	bfs(),printf("%d\n",ans);
	for(int i=1;i<=ans;i++)printf("%d ",res[i]);
	return 0;
}
```

---

## 作者：仙肉粽子 (赞：1)

# CF796D Police Stations 题解

## 思路

其实这道题就是一个染色，因为题目保证最近的警察局一定距离小于等于 $d$，所以我们可以直接忽略 $d$，直接染色，然后记录有多少条边的 $u$ 和 $v$ 颜色不相同，就是答案。

## 代码

```cpp
#include<bits/stdc++.h>
#define rep(i,s1,s2,s3) for(i = s1;i <= s2;i += s3)
#define r(i,s1,s2,s3) for(i = s1;i >= s2;i -= s3)
#define ull unsigned ll
#define INF 0x7f7f7f7f
#define ll long long
using namespace std;
int n,m,d,id,ans,col[300010],head[300010];
struct edge{
    int u,v,next;
}e[600010];
void add(int u,int v){
    e[++id] = edge{u,v,head[u]};
    head[u] = id;
}
struct node{
    int u,col;
};
queue <node> q;
int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#ifdef ONLINE_JUDGE
#else
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
#endif
    cin>>n>>m>>d;
    int i,u,v,c;
    rep(i,1,m,1){
        cin>>u;
        q.push({u,i});
    }
    rep(i,2,n,1){
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    while(q.size()){
        u = q.front().u;
        c = q.front().col;
        q.pop();
        if(col[u]) continue;
        col[u] = c;
        for(i = head[u];i;i = e[i].next){
            v = e[i].v;
            q.push(node{v,c});
        }
    }
    rep(i,1,id,2) ans += (col[e[i].u]  != col[e[i].v]);
    cout<<ans<<'\n';
    rep(i,1,id,2) if(col[e[i].u] != col[e[i].v]) cout<<(i + 1 >> 1)<<' ';
    return 0;
}
```

---

## 作者：Graph_Theory (赞：0)

### 题意
我们先来看看题意。

树状图上有 $n$ 个点，求最多能将树断开几条边，使得图上任意一点到距离该点最近的特殊点的距离小于等于 $d$，并且保证图上任意一点到距离该点最近的特殊点的距离小于等于 $d$。


### 思路

广搜所有特殊点，对广搜到的点记录他的警察局的编号，当某一条边左边和右边都是不同的编号，这条边就可以拆掉。

好，到这里就会发现这个 $d$ 一点用都没有，又解决了问题
### 代码


```cpp
#include <bits/stdc++.h>
#define int long long
#define maxn 300010
using namespace std;

struct ed{int u,v;} a[maxn];//建图
vector<int> e[maxn];
void add_point(int u,int v) {e[u].push_back(v);}

int vis[maxn],col=0;//记录点的颜色

queue<pair<int,int> > q;
void bfs()
{
	while(q.size())
	{
		int x=q.front().first;
		int color=q.front().second;
		q.pop();
		int siz=e[x].size();
		for(int i=0;i<siz;i++)
		{
			int v=e[x][i];
			if(!vis[v])
			{
				vis[v]=color;
				q.push(make_pair(v,color));
			}
		}
	}
}

int n,k,d;
signed main()
{
	cin>>n>>k>>d;
	for(int i=1;i<=k;i++)
	{
		int x;
		cin>>x;
		if(vis[x]) continue;
		vis[x]=x;
		q.push(make_pair(x,x));
	}
	for(int i=1;i<=n-1;i++)
	{
		cin>>a[i].u>>a[i].v;
		add_point(a[i].u,a[i].v);
		add_point(a[i].v,a[i].u);
	}
	bfs();
	vector<int> ans;
	for(int i=1;i<=n-1;i++)
	{
		if(vis[a[i].u]!=vis[a[i].v])
			ans.push_back(i);
	}
	cout<<ans.size()<<endl;
	for(int i=0;i<ans.size();i++) cout<<ans[i]<<" ";
	return 0;
}
```

---

## 作者：Roshin (赞：0)

## CF796D Police Stations 多源 BFS 构造

**题意**

给定一棵 $n$ 节点树，树上有 $k$ 个点是警察局，要求所有点到最近的警察局的距离不大于d，求最多能删几条边。

**数据范围**  

保证所有点距离最近的警察局不超过 $d$  。
$1\leq n,k \leq 3 * 10^5$  
$0\leq d \leq n - 1$ 

**思路** 
+ 首先所有点距离最近的警察局距离不超过 $d$ ，我们需要删除多余的边。
+ 可以尝试多源 BFS，将所有警察局点放入队列中，然后开搜，如果遇到一个点已经被访问过，根据bfs的性质，我们现在处于的边就是可以删掉的边。
+ 注意对遍历过的边的反向边特判，具体见代码。

**Solution**  


```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> PII;
typedef std::pair<ll, ll> PLL;
typedef double db;
#define arr(x) (x).begin(),(x).end()
#define x first
#define y second
#define pb push_back
#define mkp make_pair
#define endl "\n"
using namespace std;
const int N = 3e5 + 10;
bool st[N << 1];
int dist[N];
int n, k, d;
vector<PII> edge[N];

int main(){
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> k >> d;
	memset(dist, 0x3f, sizeof dist);
	queue<int> q;
	for(int i = 0; i < k; i++){
		int x;
		cin >> x;
		dist[x] = 0;
		q.push(x);
	}
	int cnt = 2;
	for(int i = 1; i < n; i++){
		int a, b;
		cin >> a >> b;
		edge[a].pb({b, cnt++});
		edge[b].pb({a, cnt++});
	}
	vector<int> res;
    while(q.size()){
		auto u = q.front();
		q.pop();
		for(auto v: edge[u]){
			if(st[v.y]) continue;
			if(dist[v.x] != 0x3f3f3f3f){
				res.pb(v.y / 2);
				st[v.y] = st[v.y ^ 1] = true;
				continue;
			}
			st[v.y] = st[v.y ^ 1] = true;
			dist[v.x] = dist[u] + 1;
			q.push(v.x);
		}
	}
	cout << res.size() << endl;
	for(auto t: res)
		cout << t << " ";
    return 0;
}	
```


---

## 作者：BootsH (赞：0)

此题 bfs 即可。

## 做法：

将每个警察局染上不同的颜色。然后跑一遍 bfs，将所经过的点染上色。在此之后，统计每条边。若这条边两端点颜色不同，这条边可以删去。

## 做法原因

此题不需要用到题目中的 $d$，因为数据满足非警察局的点到最近的警察局距离不超过 $d$（这点在翻译里没有体现，望说明），而 bfs 保证了  _被搜到的点_ 离 _其颜色对应的警察局_ 的距离必定最小。因此，当枚举到一条边的两个端点颜色不同时，必然能够删去这条边，且能够保证到最近警察局的距离不超过 $d$。

## 代码
```cpp
#include <iostream>
#include <fstream>

std::streambuf* inbuf, *outbuf;
char ibuf[1 << 23], *i1 = ibuf, *i2 = ibuf;
#define gc() (i1 == i2 && (i2 = (i1 = ibuf) + inbuf->sgetn(ibuf, 1 << 23), i1 == i2) ? EOF : *i1++)
#define pc(x) (outbuf->sputc(x))

int iget()
{
    int x = 0;
    bool f = false;
    char c = gc();
    while (c < '0' || c > '9')
    {
        f |= c == '-';
        c = gc();
    }
    while (c >= '0' && c <= '9')
    {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = gc();
    }
    return f ? -x : x;
}

void ipr(int x)
{
    if (x == 0)
    {
        pc('0');
        return ;
    }
    if (x < 0)
    {
        pc('-');
        x = -x;
    }
    static char stk[25];
    int top = 0;
    while (x)
    {
        stk[top++] = x % 10 + 48;
        x /= 10;
    }
    while (top--)
    {
        pc(stk[top]);
    }
}

void iwsp(int x) // Int Write with Space 
{
    ipr(x);
    pc(' ');
}

void iwln(int x) // Int Write with LiNe
{
    ipr(x);
    pc('\n');
}

#include <vector>
#include <algorithm>

namespace Solution
{

    const int maxn = 1000005;

    struct Point  
    {
        int pos, col;
        Point(int p = 0, int c = 0):
            pos(p), col(c) {}
    };

    std::vector<int> g[maxn]; 
    Point qaq[maxn];
    int head = 1, tail = 0;
    int vis[maxn];
    int u[maxn], v[maxn];

    void bfs()
    {
        while (head <= tail)
        {
            int u = qaq[head].pos;
            int c = qaq[head++].col;
            for (int v : g[u])
            {
                if (!vis[v])
                {
                    vis[v] = c;
                    qaq[++tail].pos = v;
                    qaq[tail].col = c;
                }
            }
        }
    }


    int main()
    {
        #ifndef ONLINE_JUDGE
            std::ifstream cin("main.in");
            std::ofstream cout("main.out");
        #else
            std::ios::sync_with_stdio(false);
            std::cin.tie(nullptr);
            std::cout.tie(nullptr);
            using std::cin;
            using std::cout;
        #endif
        inbuf = cin.rdbuf();
        outbuf = cout.rdbuf();


        int n = iget(), k = iget(), d = iget(), num = 0;
        for (int i = 1; i <= k; ++i)
        {
            int p = iget();
            if (vis[p])
            {
                continue;
            }
            vis[p] = ++num;
            qaq[++tail].pos = p;
            qaq[tail].col = num;
        }
        for (int i = 1; i < n; ++i)
        {
            u[i] = iget(), v[i] = iget();
            g[u[i]].push_back(v[i]);
            g[v[i]].push_back(u[i]);
        }
        bfs();
        std::vector<int> pos;
        for (int i = 1; i < n; ++i)
        {
            if (vis[u[i]] != vis[v[i]])
            {
                pos.push_back(i);
            }
        }
        iwln(pos.size());
        for (int p : pos)
        {
            iwsp(p);
        }


        #ifndef ONLINE_JUDGE
            cin.close();
            cout.close();
        #endif
        return 0;
    }
} // namespace Solution


int main(int argc, const char* argv[])
{
    Solution::main();
    return 0;
}
```

## 注意

本题若有多种方案，输出其任意一种即可。因此，第一个样例输出 `1 (\n) 5` 和 `1 (\n) 3` 均可。其中 `(\n)` 指换行。



---

