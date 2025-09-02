# [POI 2006] MET-Subway

## 题目描述

A certain city has been coping with subway construction for a long time. The finances have been mismanaged and the costs have been underestimated to such extent that no funds were foreseen for the purchase of trains. As a result, too many stations and only some of the planned tunnels have been built - barely enough to allow a connection between any two stations to exist. The number of tunnels (each of them is bidirectional) is one less than the number of stations built. From the remaining funds only a handful of trains have been acquired.

To save their face, the board of directors have asked you to plan subway routes in such a way as to allow maximal number of stations to be connected. Each train travels on a specified route. The routes cannot branch (no three tunnels starting at a single station may belong to the same route). Distinct routes may comprise the same station or tunnel.

TaskWrite a programme which:

reads a description of the tunnel system and the number of subway lines, which are to be planned from the standard input,calculates the maximal number of stations which can be covered by the specified number of subway lines,writes the outcome to the standard output.

给定一棵树，选择l条路径覆盖最多的点的个数是多少。


## 样例 #1

### 输入

```
17 3
1 2
3 2
2 4
5 2
5 6
5 8
7 8
9 8
5 10
10 13
13 14
10 12
12 11
15 17
15 16
15 10```

### 输出

```
13```

# 题解

## 作者：Mirach (赞：19)

Thought
-----------

题目分析（直接看解法的请往下翻）：

这题一眼有点像最小路径覆盖（二分图or网络流），但实际上并不一样，因为全局最优与局部最优可能会有冲突

实际上观察这题的数据，推测复杂度$O(n)$

不难想到选取的$I$条路径都是从叶子到叶子存在最优解

那么发现貌似叶子节点中最多只有$I*2$个会被覆盖（每条路径从叶子到叶子，覆盖$2$个），类似的，发现从叶子节点往内推一层也是最多只有$I*2$个会被覆盖，那么大胆猜测，如果从叶子节点向内拓扑分层后每一层最多只有$I*2$个会被覆盖，考虑到每一层的节点并不一定有$I*2$个，所以每一层要考虑节点数的限制，最后将所有层加起来即可

这样做虽然没有直接考虑每一条路径，但由于路径之间是可相交的，所以可以保证每一层的点都可以满足覆盖 $min(I*2,tot)$ *$tot$为当前层点数* 个的要求

Solution
-----------

从叶子拓扑排序处理出节点的层，每一层对答案的贡献为$min(2*I,tot)$
$$ans=\sum_{depth}min(I*2,tot[depth])$$

Code
---------

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rg register
#define cl(x) memset(x,0,sizeof(x))
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
#define abs(x) ((x)>0?(x):(-(x)))

template <typename _Tp> inline _Tp read(_Tp&x){
	rg char c11=getchar(),ob=0;x=0;
	while(c11^'-'&&!isdigit(c11))c11=getchar();if(c11=='-')c11=getchar(),ob=1;
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();if(ob)x=-x;return x;
}

const int N=1005000;
struct Edge{int v,nxt;}a[N<<1];
int head[N],tot[N],deg[N],lay[N],vis[N];
int n,k,_(0);

inline void add(int u,int v){
	a[++_].v=v,a[_].nxt=head[u],head[u]=_;++deg[u];
	a[++_].v=u,a[_].nxt=head[v],head[v]=_;++deg[v];
}

void topology(){
	queue <int> q;
	for(rg int i=1;i<=n;++i)if(deg[i]==1)vis[i]=1,++tot[lay[i]=1],q.push(i);
	while(!q.empty()){
		rg int x=q.front();q.pop();
		for(rg int i=head[x];i;i=a[i].nxt)
			if(!vis[a[i].v])
			if((--deg[a[i].v])==1)
			vis[a[i].v]=1,++tot[lay[a[i].v]=lay[x]+1],q.push(a[i].v);
	}
	return ;
}

int main(){
	read(n);read(k);
	for(rg int i=1,x,y;i<n;++i)add(read(x),read(y));
	topology();
	rg int ans(0);
	for(rg int i=1;tot[i];++i)ans+=min(k<<1,tot[i]);
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：信息向阳花木 (赞：8)

【xxs 都能看懂的题解】


------------

贪心：选两个叶子结点作为路径的起点和终点，两个叶子结点离得越远越好。

于是这是具体步骤：
1. 算叶子结点的个数 $k$， $ans \gets ans + \min\{2 \times l, k\}$。
2. 删除 $k$ 个叶子结点
3. 回到步骤 $1$，直到没有叶子结点为止。

我们首先得明确，$ans$ 每次加的并不是一条路径对答案的贡献，而是一层对答案的贡献。注意，这里的层不等于深度，例如每次叶子结点我们视为它们在同一层，但不在同一深度。

然后为什么步骤 $1$ 中每层对答案的贡献是 $ans \gets ans + \min\{2 \times l, k\}$ 呢？

每条路径有 $2$ 个结点在叶子结点上，由此堆得每一条路径在每一层都有 $2$ 个结点。所以理论上每一层有 $2 \times l$ 个结点被覆盖，但这一层总共就 $k$ 个结点，所以这一层对答案的贡献要把 $2 \times l$ 和 $k$ 取个 $\min$。

![](https://cdn.luogu.com.cn/upload/image_hosting/1laswenb.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

所以我们一边宽搜一边求答案就可以了。

------------
代码：
```cpp
#include<iostream>
#include<queue>
using namespace std;
int n,l,cnt,ans;
int head[1000010],d[1000010];//d[i] 代表结点 i 的度。 
queue<int>q;//q 是宽搜所要用的队列。 
struct node{
	int to,next;
}e[2000010];
void add(int &x,int &y){//链式前向星加边操作，这里不再赘述。 
	e[++cnt]={y,head[x]};
	head[x]=cnt;
	return;
}
int read(){
	char ch=getchar();
	int x=0,f=1;
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int main(){
	cin>>n>>l;
	for(int i=1;i<n;i++){
		int x=read();
		int y=read(); 
		add(x,y);add(y,x);
		d[x]++;d[y]++;
	}
	for(int i=1;i<=n;i++)
		if(d[i]==1)q.push(i);//把叶子结点放入队列。 
	while(!q.empty()){
		int k=q.size();//叶子结点的数量。 
		ans+=min(2*l,k);//算每层的贡献。 
		for(int i=1;i<=k;i++){
			int u=q.front();//u 是 k 个叶子结点中的一个。
			q.pop();//删除叶子结点。
			for(int j=head[u];j;j=e[j].next){
				int v=e[j].to;
				d[v]--;//u 删除了，和它有连边的点的度要减 1。 
				if(d[v]==1)q.push(v);//把新的叶子结点放入队列。 
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：oscar (赞：7)

【POI补全计划#24 POI2006 MET】

智障选手oscar在拉低此题通过率后又来写题解啦！

首先猜结论，发现只需要第一条选直径，后面的每一条分两次选，每次找到一个离已经选过的点最远的点x，把x点到已经选过的点的路径上所有点全选上就能达到最优解

这是为什么呢？大胆猜想不需证明

接下来修复一个小bug，如果新选的两个点与之前选的部分没有交点，那么会多连一条新路径与已经选过的点之间的路径

只需要把新路径的一个端点和已经选过的端点交换一下就可以了

由于我的表述可能有问题，我们来画一个图

![1.png](https://user-images.githubusercontent.com/20551921/31261844-651836b6-aa89-11e7-88dc-5ccde4691ad1.png)

这个图中红色部分表示之前选的路径，蓝色部分表示新选的两个端点之间的连线

我们把这两条路径转换成下图这样，就可以覆盖中间的竖直路径

![2.png](https://user-images.githubusercontent.com/20551921/31261892-c1207dc4-aa89-11e7-8f19-dcc3bd80a3d2.png)

图中红色部分表示之前选的路径调整后的样子，蓝色表示新路径调整后的样子，紫色表示红蓝公共部分


这样应该就差不多解释清楚了

下面来考虑怎么维护离选过的点最远的点

我们把直径的端点设为根，然后从根开始进行dfs，过程中记录每个点往远离根的方向走最多能经过多少个点（以后简称为maxd），再记录沿着这个方向走的下一个点是哪个

接下来从大到小贪心（不需要用堆维护（TLE），直接将maxd作为下标存到数组里（类似计数排序）），不需要管路径是否已经选到这个点的祖先，因为在maxd小的点的所有祖先的maxd一定严格大于这个点


最后为了防止MLE，我们将内存动态开出来，使用完了就删除（见代码注释 ******************** 处）


波兰人真是脑洞大（逃）


最后贴代码：

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
const int MAXN=1000010;
struct edge
{
    int v;
    edge *next;
}*h[MAXN],*pool;
int top;
inline void addedge(int u,int v)
{
    edge *tmp=&pool[++top];tmp->v=v;tmp->next=h[u];h[u]=tmp;
    edge *pmt=&pool[++top];pmt->v=u;pmt->next=h[v];h[v]=pmt;
}
queue<int> q;
int dep[MAXN],maxd[MAXN],pa[MAXN],mson[MAXN];
int bfs()
{
    int maxd=1,maxn=1;
    q.push(1);
    dep[1]=1;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(edge *tmp=h[u];tmp;tmp=tmp->next)
        {
            if(!dep[tmp->v])
            {
                dep[tmp->v]=dep[u]+1;
                q.push(tmp->v);
                if(dep[tmp->v]>maxd)
                {
                    maxd=dep[tmp->v];
                    maxn=tmp->v;
                }
            }
        }
    }
    return maxn;
}
vector<int> nod[MAXN];
void dfs(int u)
{
    for(edge *tmp=h[u];tmp;tmp=tmp->next)
    {
        if(!dep[tmp->v])
        {
            dep[tmp->v]=dep[u]+1;
            pa[tmp->v]=u;
            dfs(tmp->v);
            if(maxd[tmp->v]+1>maxd[u])
            {
                maxd[u]=maxd[tmp->v]+1;
                mson[u]=tmp->v;
            }
        }
    }
}
int n,k;
bool vis[MAXN];
int main()
{
    pool=new edge[MAXN*2];//********************
    scanf("%d%d",&n,&k);
    int a,b;
    for(int i=1;i<n;i++)
    {
        scanf("%d%d",&a,&b);
        addedge(a,b);
    }
    int root=bfs();
    memset(dep,0,sizeof(dep));
    dep[root]=1;
    dfs(root);
    delete[] pool;//********************
    for(int i=1;i<=n;i++)
    {
        nod[maxd[i]].push_back(i);
    }
    int ans=0,left=k*2-1;
    for(int i=n;i>=0;i--)
    {
        for(auto x:nod[i])
        {
            if(!vis[x])
            {
                int cur=x;
                left--;
                while(cur)
                {
                    ans++;
                    vis[cur]=1;
                    cur=mson[cur];
                }
            }
            if(!left)break;
        }
        if(!left)break;
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：逢秋商独季 (赞：6)

哇……蒟蒻过紫题，暴力出奇迹

~~树链剖分快如闪电~~

先找出树的一条直径的起点，显然最优解中的其中一条路径一定是直径，然后开剖。

剖出来之后拿着最长重链的两端提起来，就像下面这样。![](https://cdn.luogu.com.cn/upload/pic/41260.png)

然后用预先记录的叶子数组排序，贪心处理每一片叶子所在的路径，比较参数是【这片叶子位于的重链的长度】，显然这个值越长，这条路径的长度就越长（轻链的数量是有上限的）

累加，完事。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
void iread(int &c)
{
    c=0;int k=1;char p='k';
    while((p<'0')||(p>'9')){if(p=='-')k=-1;p=getchar();}
    while((p>='0')&&(p<='9')){c=c*10+p-'0';p=getchar();}
    c*=k;
}
int n,l,ru,rv,ans,root;
int dis[1000001];
struct pc{int num,c;}leaf[1000001];int lta;
bool cmp(pc a,pc b){return a.c>b.c;}
bool ispick[1000001];
struct poi{int fa,son,size,head,top,tpl;}tree[1000001];//存树 
struct EDGE{int from,to,next;}e[2000002];int ct;//邻接表存图 
void adde(int st,int ed){ct++;e[ct].next=tree[st].head;tree[st].head=ct;e[ct].from=st;e[ct].to=ed;}
void dfs0(int st,int fa)//第一遍深搜，记录距离，找直径端点 
{
	for(int i=tree[st].head;i;i=e[i].next)
    {
        if(e[i].to==fa)continue;
        dis[e[i].to]=dis[st]+1;
		dfs0(e[i].to,st);
    }
}
void dfs1(int st,int fa)//树剖第一遍深搜 
{
    tree[st].fa=fa;
    tree[st].size=1;
    for(int i=tree[st].head;i;i=e[i].next)
    {
        if(e[i].to==fa)continue;
        dfs1(e[i].to,st);
        tree[st].size+=tree[e[i].to].size;
        if(tree[e[i].to].size>tree[tree[st].son].size)
        {
            tree[st].son=e[i].to;
        }
    }
    return;
}
void dfs2(int st,int fa)//树剖第二遍深搜 
{
    if(tree[fa].son==st)tree[st].top=tree[fa].top,tree[st].tpl=tree[fa].tpl+1;//记录每个点到所在重链顶端的距离 
    else tree[st].top=st;
    for(int i=tree[st].head;i;i=e[i].next)
    {
        if(e[i].to==fa)continue;
        dfs2(e[i].to,st);
    }
    if(!e[tree[st].head].next){lta++;leaf[lta].c=tree[st].tpl;leaf[lta].num=st;}
    return;
}
int main()
{
    iread(n);iread(l);
    for(register int i=2;i<=n;i++)
    {
        iread(ru);iread(rv);
        adde(ru,rv);
        adde(rv,ru);
    }
    dfs0(1,1);
    for(int i=1;i<=n;i++)if(dis[i]>dis[root])root=i;//找到与点1距离最大的点，即是直径顶点 
	dfs1(root,root);//树剖（这里直接用1当根只有33分，两个点） 
    dfs2(root,root);
    /*                //注释注释注释大法好 
    for(int i=1;i<=n;i++)
    {
        cout<<i<<":"<<tree[i].fa<<","<<tree[i].size<<","<<tree[i].son<<","<<tree[i].top<<","<<tree[i].tpl<<endl;
    }
    //*/
    sort(leaf+1,leaf+1+lta,cmp);//排序 
    /*
    for(int i=1;i<=n;i++)cout<<leaf[i].num<<","<<leaf[i].c<<" ";cout<<endl;
	//*/
	for(int i=1;i<=(l<<1)-1;i++)
    {
    	if(i==1)//最大的是最长重链的另一端 
    	{
    		ispick[root]=1;//标记以某点为顶端的重链是否被选择 
    		ans=leaf[i].c+1;
        }
        else
        {
            int k=leaf[i].num;
            while(!ispick[tree[k].top])//还没有跳到最长重链 
            {
            	ispick[tree[k].top]=1;
            	ans+=(tree[k].tpl+1);//看图 
                k=tree[tree[k].top].fa;
            }
        }
    }
    printf("%d",ans);//收工 
    return 0;
}
```

其实还是贪心思想……


---

## 作者：Waldin (赞：3)

由于要在树上尽可能多地覆盖节点，所以可以贪心地让路径的伊始节点和终焉节点都是树上最边缘的两个节点——度数为 $1$ 的节点。

在这种策略下，容易发现，对于所有度数为 $1$ 的节点，最多只有 $2l$ 个节点会被覆盖；此时再把所有度数为 $1$ 的节点删除，发现对于这时新产生的一批度数为 $1$ 的节点，也最多只有 $2l$ 个节点会被覆盖。如此继续往下推导，会发现一直如此……

也就是说，利用不同批次度数为 $1$ 的节点，可以对树进行分层——不同批次度数为 $1$ 的节点位于不同层，有多少批就有多少层。毫无疑问，每层被覆盖的节点数除了不会超过 $2l$ 外，肯定也不可能超过这层的节点总数，所以每层被覆盖的节点数为这层的节点数与 $2l$ 的较小值，最终答案为每层被覆盖的节点数之和。

现在考虑如何用代码实现分层。容易发现，分层的过程其实就是多起点拓扑排序（Topological Sort）的过程。

算法的总时间复杂度为 $\text O(n)$。示例代码如下，该代码为洛谷 Luogu 全站最优解：
```cpp
#include <bits/stdc++.h>
using namespace std;

#define typeof(...) __decltype(__VA_ARGS__)
constexpr size_t MAXn = 1e6;

#ifndef _getchar_nolock
#define _getchar_nolock getchar_unlocked
#endif
class FastIn_Base {
public:
	template<typename _Ty>
	FastIn_Base& operator>>(_Ty& __restrict__ int_var) noexcept {
		int c; bool f;
		if (is_signed<_Ty>::value)
			f = false;
		while (!isdigit(c = _getchar_nolock()))
			if (is_signed<_Ty>::value && c == 45)
				f = true;

		int_var = c - 48;
		while (isdigit(c = _getchar_nolock()))
			int_var = int_var * 10 + (c - 48);

		if (is_signed<_Ty>::value && f)
			int_var = -int_var;
		return *this;
	}
};
#define intIn ((FastIn_Base) {})
#define cin intIn

template<size_t MAXPNT,
	size_t MAXEDGE>
class Graph {
private:
	class Edge {
	public:
		uint32_t tail, nxt;
	};

	class Point {
	public:
		uint32_t edge, deg;
	};

	uint32_t idx;

public:
	Point pnt[MAXPNT + 1];
	Edge edges[MAXEDGE + 1];

	void addEdge(const uint32_t u, const uint32_t v) noexcept {
		++idx;
		edges[idx] = (Edge){ v, pnt[u].edge };
		pnt[u].edge = idx;
		++pnt[v].deg;
	}

	Graph(const size_t pnt_amt = MAXPNT, const size_t edg_amt = MAXEDGE) noexcept : idx(0) {
		memset(pnt, 0x00, (pnt_amt + 1) * sizeof(*pnt));
		for (Graph::Edge* i = edges + edg_amt; i > edges; (i--)->nxt = 0);
	}
};

int main(void) noexcept {
	ios::sync_with_stdio(false);

	uint32_t n, l;
	cin >> n >> l;

	Graph<MAXn, 2 * (MAXn - 1)> g(n, 2 * (n - 1));
	for (auto i = n; --i;) {
		typeof(n)a, b;
		cin >> a >> b;
		g.addEdge(a, b);
		g.addEdge(b, a);
	}

	typeof(n)cnt[MAXn + 1],  // 第 i 层的节点数
		tier[MAXn + 1];  // 第 i 号节点所属层的编号
	memset(cnt, 0x00, (n + 1) * sizeof(*cnt));
	queue<typeof(n)> q;
	bitset<MAXn + 1> vis;

	for (typeof(n)i = 1; i <= n; ++i)
		if (g.pnt[i].deg == 1) {
			vis[i] = true;
			++cnt[tier[i] = 0];
			q.push(i);
		}

	while (!q.empty()) {
		#define u (q.front())
		for (typeof(n)i = g.pnt[u].edge; i; i = g.edges[i].nxt) {
			#define v (g.edges[i].tail)
			if (!vis[v] && --g.pnt[v].deg == 1) {
				vis[v] = true;
				++cnt[tier[v] = tier[u] + 1];
				q.push(v);
			}
			#undef v
		}
		#undef u
		q.pop();
	}

	typeof(n)ans = 0;
	l *= 2;
	for (typeof(n)i = 0; cnt[i]; ++i)
		ans += min(l, cnt[i]);
	cout << ans;
	return 0;
}
```

---

## 作者：CYZZ (赞：2)

# [MET-Subway](https://www.luogu.com.cn/problem/P3441)
第一道没看题解做出来的紫色图论题~~蒟蒻老泪纵横~~。
# 思路分析
如果从整体上入手的话，很难确定选出边的依据，所以还是先考虑贪心。

首先注意到，每次选**叶子节点**到**叶子节点**的路径相对而言会最优，而且每条路径**最多**经过 $2$ 个叶子节点。也就是说：
> 理想情况下，每条路径不共用叶子，所以对于所有叶子节点，我们能最多覆盖 $2l$ 个叶子节点（$l$ 同题意）。

但是，万一那一层的总节点数还没有 $2l$ 多怎么办？于是第 $i$ 层的答案就变成了 $\min(2l,size_i)$，其中 $size_i$ 指第 $i$ 层的总节点数。

题目给的是一颗无根树，问题就转变成了求每一层节点的个数，我们可以**拓扑排序**的方法遍历：

- 把入度（就是连边数）为 $1$ 的点放入队列中。
- 取出队头，删除它（就是把和他有连边的点入度减 $1$）。
- 把新产生入度为 $1$ 的点入队。
- 重复操作 $2$ 和 $3$，直到队列空。
- 统计答案。

# 代码实现
```cpp
    #include <bits/stdc++.h>
    using namespace std;
    int n,l,head[1000005],in[1000005],tot,ans[1000005],cnt;
    bool bk[1000005];
    struct edge
    {
        int next,to;
    }e[2000005];
    void add_edge(int u,int v)
    {
        e[++tot].next=head[u];
        e[tot].to=v;
        head[u]=tot;
    }
    struct node
    {
        int id,dep;
    };
    queue<node>q;
    void topu()//拓扑排序 
    {
        for(int i=1;i<=n;i++)
        {
            if(in[i]==1)
            {
                q.push({i,1});//队列初始化 
                bk[i]=1;
            }
        }
        while(!q.empty())
        {
            node u=q.front();
            q.pop();
            ans[u.dep]++;//同一层的节点数加1 
            for(int i=head[u.id];i;i=e[i].next)
            {
                int v=e[i].to;
                if(!bk[v])
                {
                    in[v]--;//入度减1 
                    if(in[v]==1)
                    {
                        q.push({v,u.dep+1});//新的入队 
                        bk[v]=1;
                    }
                }
            }
        }
    }
    int main()
    {
        scanf("%d%d",&n,&l);
        for(int i=1;i<n;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            add_edge(u,v);
            add_edge(v,u);
            in[u]++;
            in[v]++;//初始化入度 
        }
        topu();
        for(int i=1;(i<=n)&&ans[i];i++)
        {
            cnt+=min(l*2,ans[i]);//计算答案 
        }
        printf("%d",cnt);
        return 0;
    }
```

希望本篇题解可以帮到大家！！！

---

## 作者：Inui_Sana (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P3441)

这道题如果要将所有路径找出来，需要考虑很多因素，难以找到最优。那么既然不能从整体入手，那就可以考虑分开算贡献。怎么分呢？

很容易发现，每一条路径最多覆盖到 $2$ 个叶子节点，一个起点一个终点。那么 $l$ 条最多覆盖 $2\times l$ 个。但可能叶子节点数量更少，所以设叶子节点数量为 $a$，则能覆盖的叶子节点数量为 $\min(2\times l,a)$。

进一步想，把叶子节点删去后，剩下的节点也符合这个性质。所以我们可以把这棵树按这个步骤分为若干层分别计算，第 $i$ 层有 $a_i$ 个节点，那么 $ans=\sum \min(2\times l,a_i)$。

最后就是怎么分这个层了。这整个过程是一个删叶子的过程，所以可以用拓扑排序，从下到上处理。

code：

```cpp
int n,m,dep[N],sum[N],in[N];
bool vis[N];
int tot,head[N];struct node{int to,nxt;}e[N<<1];
queue<int> q;
inline void add(int u,int v){e[++tot]={v,head[u]},head[u]=tot;}
signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<n;i++){
		scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
		in[u]++,in[v]++;
	}
	for(int i=1;i<=n;i++){
		if(in[i]==1)q.push(i),dep[i]=1;//因为是无向图，所以入度为1的就是叶子
	}
	while(q.size()){
		int u=q.front();q.pop();
		vis[u]=true,sum[dep[u]]++;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(vis[v])continue;
			in[v]--;
			if(in[v]==1)q.push(v),dep[v]=dep[u]+1;
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++)ans+=min(sum[i],2*m);
	printf("%d\n",ans);
}
```

---

## 作者：liunian (赞：2)

这是一道标准的图论综合题。

让我们看一下有哪些图论知识：结构体用前向星的基本方式；
初始化建树时用到了加边的基本知识；
加点按照深度排序时运用了拓扑排序的基本思想；
最后根据路径覆盖求出最多覆盖的点。

结构体中v表示当前节点，nxt表示下一个与之相连节点。

同时要注意a要开maxn的两倍，因为每一个i输入两个节点，否则就会RE。

加边的步骤可以独立出来成为一个模板：
```
void add(int x,int y) {
	a[++cnt].v=y,a[cnt].nxt=head[x],head[x]=cnt,d[x]++;
	a[++cnt].v=x,a[cnt].nxt=head[y],head[y]=cnt,d[y]++;
}
```
此处加的是双向边，若加的是从x到y有向边，只需改成
```
a[++cnt].v=x,a[cnt].nxt=head[y],head[y]=cnt,d[y]++;

```
即可。

其中a[++cnt].v=x表示当前节点为x，计数加1；
a[cnt].nxt=head[y]表示下一个与之相连的节点是y;
d[y]++表示y的度数加1。

拓扑的部分也很值得研究。首先把出度为1的节点推入队列，然后对于每一个在队列中的点寻找与之相连的节点，将边断去，同时将所搜的点的度数减1，深度加1，若减1后该点的出度为1，则该点就成为了新的“叶子节点”，如此循环下去，就能求出所有深度下的节点个数。

最后在计算答案的过程中，我们要知道两个小定理：在一棵树中，一条最长的路径的两个端点必定是两个叶子节点；同时，在一条路径中，同一个深度的节点最多被覆盖两个。那么，ans+=min(l<<1,tot[i])就表示若该深度节点的个数大于路径数*2，则覆盖的节点数就是路径数 *2，反之就等于节点的个数。

```
#include<iostream>
#include<stdio.h>
#include<queue>
using namespace std;
const int maxn=1e6+5;
int cnt=0;

struct node {
	int v,nxt;
} a[maxn<<1];

queue<int>q;
int head[maxn],tot[maxn],d[maxn],deep[maxn];
bool vis[maxn];

void add(int x,int y) {
	a[++cnt].v=y,a[cnt].nxt=head[x],head[x]=cnt,d[x]++;
	a[++cnt].v=x,a[cnt].nxt=head[y],head[y]=cnt,d[y]++;
}

int main() {
	int n,l;
	scanf("%d %d",&n,&l);
	for(int i=1,x,y; i<n; i++) {
		scanf("%d %d",&x,&y);
		add(x,y);
	}
	for(int i=1; i<=n; i++)if(d[i]==1)vis[i]=1,tot[deep[i]=1]++,q.push(i);
	while(!q.empty()) {
		int now=q.front();
		q.pop();
		for(int i=head[now]; i; i=a[i].nxt)
			if((--d[a[i].v])==1&&!vis[a[i].v])
				vis[a[i].v]=1,tot[deep[a[i].v]=deep[now]+1]++,q.push(a[i].v);
	}
	int ans=0;
	for(int i=1; tot[i]; i++)ans+=min(l<<1,tot[i]);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：破忆 (赞：1)

## 【题意】
给出一棵无根树，要求确定m条路径，使得被路径覆盖的点数最多，求最多的点数

## 【分析】

不妨先假设这是一棵有根数

对树进行分层，每层至多有$2m$个点

可以确定的是，每条路径的端点一定在叶节点上

既然是无根树，就反向处理

令叶节点都在同一层，再往上拓展

记录每一层的点数，与$2m$取$min$即可

拓展的过程可以用拓扑实现

## 【解法】
拓扑
## 【代码】
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5,maxe=maxn<<1;
int n,m;
int tot,lnk[maxn],d[maxn];
int cnt[maxn],maxd;
int que[maxn],dep[maxn];
int ans;
struct edge{
	int to,nxt;
}e[maxe];
char gc(){
	static char buf[10000],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
int read(){
	int ret=0,f=1;char ch=gc();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-f;ch=gc();}
	while(ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=gc();
	return ret*f;
}
void add_e(int x,int y){
	e[++tot]=(edge){y,lnk[x]};
	lnk[x]=tot,d[y]++;
}
void Topo(){
	int hed=0,til=0;
	for(int i=1;i<=n;i++){
		d[i]--;
		if(!d[i]) que[++til]=i,dep[i]=1;
	}
	while(hed!=til){
		int x=que[++hed];
		cnt[dep[x]]++;
		if(dep[x]>maxd) maxd=dep[x];
		for(int j=lnk[x];j;j=e[j].nxt){
			int y=e[j].to;
			d[y]--;
			if(!d[y]){
				que[++til]=y;
				dep[y]=dep[x]+1;
			}
		}
	}
}
int main(){
 	freopen("P3441.in","r",stdin);
 	freopen("P3441.out","w",stdout);
	n=read(),m=read()*2;
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		add_e(x,y),add_e(y,x);
	}
	Topo();
	for(int i=1;i<=maxd;i++) ans+=min(m,cnt[i]);
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：ty_mxzhn (赞：0)

一篇拓扑的题解。

观察题目性质。首先假设我们有一条路径的一段没有到叶子的话，肯定可以**调整**成叶子。这些叶子一定互不相同，所以一共要选出 $2x$ 个叶子。

然后假设我们有 $y$ 个叶子。

当 $2x \ge y$ 的时候，显然此时每个叶子都会被选到。我们可以证明此时任何一个点都可以被覆盖。

证明：假设有一个点 $u$ 没有被覆盖。如果我们删去 $u$，那么剩下的联通块里面总有两条被覆盖的路径，他们在不同的联通块内部，并且将他们**适当的交换**，总可以覆盖到 $u$ 而且不会让其他点失去覆盖。

用张去年的上古老图：

![](https://cdn.luogu.com.cn/upload/image_hosting/zht3bho4.png)

再放一张今年的丑陋新图：

![](https://cdn.luogu.com.cn/upload/image_hosting/4u0ycxxt.png)

然后我们就要处理 $2x < y$ 的情况了。对于叶子，肯定可以覆盖到 $2x$ 个，并且**无论我们怎么选择都可以**覆盖到 $2x$ 个。如果我们把这些选定的叶子同时**向唯一的出边走一步**，那么问题就可以转化成把所有叶子都删去，且 $x$ 和原问题完全一样的子问题。

这不就是拓扑吗？所以问题就做完了。

乱写的代码：

```cpp
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

int n,m,dp[1000007],dg[1000007],ans;
int sz[1000007];
bool vi[1000007];
vector<int> g[1000007];
queue<int> q;
signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<n;i++){
		scanf("%d%d",&u,&v);
		g[u].push_back(v),g[v].push_back(u);
		dg[u]++,dg[v]++;
	}
	for(int i=1;i<=n;i++) if(dg[i]==1) sz[0]++,q.push(i);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=0;i<g[u].size();i++){
			int v=g[u][i];
			if(vi[v]) continue;
			dg[v]--;
			if(dg[v]==1){
				vi[v]=true;
				dp[v]=dp[u]+1;
				sz[dp[v]]++;
				q.push(v);
			}
		}
	}
	for(int i=0;i<=n;i++) ans+=min(sz[i],2*m);
	printf("%d\n",ans);
	return 0;
}
```

总结：一道不错的贪心题目。

---

## 作者：AbsMatt (赞：0)

## [题目传送器](https://www.luogu.com.cn/problem/P3441)

# 题意
题目讲的很清楚，这里不过多解释了。

# 思路
本题使用的算法是**贪心**。

首先注意到，我们选择的路径一定是从叶子节点到叶子节点的。
假如我们要选 $a$ 条路径，那么也就是说，理想情况下，每个路径不共用叶子，所以对于叶子节点，我们能覆盖 $2 \times a$ 的点，然后我们把所有的叶子节点去掉，那么上一层的节点就变成了新的叶子节点。

然后我们发现是一样的问题：理想情况下我们还能覆盖 $2 \times a$ 的叶子，但是我们发现当叶子节点的数量不够 $2 \times a$，也就是有的路径会有相交，
那么就有一个贪心的做法：枚举叶子节点的数量 $s$，$\operatorname{min}(s,2 \times a)$ 就是我们这一次能覆盖的点数，然后我们把叶子节点去掉，会得到新的叶子节点，重复上面的做法直到去掉所有的。

当这个点的出度或入度为 $1$ 时（无向图），这个点就是叶子节点（我的代码中记录的是出度）。

思考完之后把这个找叶子节点和删叶子节点的过程放在一个 bfs 中就行了，时间复杂度就是 $O(n \times \operatorname{log}^2 n)$。

## AC Code
```cpp
#include<bits/stdc++.h>  // 开始了
using namespace std;
const int maxn=1e7+10;
int n,m,cnt=0,ans=0;
int head[maxn],out[maxn],dep[maxn],sum[maxn];
queue<int> q; 
struct edge{  // 建图
	int nxt,to;
}e[maxn];
void add(int x,int y){  // 加边
	out[x]++;
	e[++cnt]={head[x],y};
	head[x]=cnt;
}
int main(){
	scanf("%d%d",&n,&m);  // 输入
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	for(int i=1;i<=n;i++){
		if(out[i]==1)	q.push(i),dep[i]=1,sum[1]++; 
	}
	while(!q.empty()){  // BFS
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int t=e[i].to;
			if(!dep[t]){
				out[t]--;
				if(out[t]==1){
					dep[t]=dep[u]+1;
					sum[dep[t]]++;
					q.push(t);
				}
			}
		}
	}
	for(int i=1;i<=n;i++){  // 贪心
		ans+=min(m*2,sum[i]);
	}
	printf("%d",ans);  // 输出
	return 0;  // 再见
}
```

---

