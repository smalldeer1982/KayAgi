# [POI 2011] DYN-Dynamite

## 题目描述

Byteotian 洞穴由 $n$ 个房间和连接它们的 $n-1$ 条走廊组成。对于每一对房间，有一条唯一的路径可以在不离开洞穴的情况下从一个房间移动到另一个房间。

某些房间中设置了炸药。

每条走廊上都铺设了导火索。

在每个房间中，相邻走廊的导火索在一个点相遇，并进一步连接到房间内的炸药（如果房间内有炸药）。导火索在两个相邻房间之间燃烧需要恰好一个时间单位，当火焰到达房间时，房间内的炸药立即爆炸。

我们希望在 $m$ 个房间（导火索的连接点）点燃导火索，使得所有炸药在点燃导火索后以最短的时间爆炸。编写一个程序来确定可能的最短时间。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
7 2
1 0 1 1 0 1 1
1 3
2 3
3 4
4 5
5 6
5 7```

### 输出

```
1
```

# 题解

## 作者：tommymio (赞：55)

从我认真记录以来第 $3$ 道由于读错题面而**GG**的题目（

观察题目，显然有一个外层二分的模型，二分距离的最大值作为上界。

问题就转化成了：**一棵树上选 $m$ 个点，使得这 $m$ 个点与关键节点的最小距离不超过$mid$。**

然后发现上面那个问题是不好解决的，根据二分判定，问题还可以进一步转化：**一棵树上选 $tot$ 个点，使得这 $tot$ 个点与关键节点的最小距离不超过mid，最小化 $tot$。**

这大概就是一个最小点覆盖的问题，用最少的点覆盖所有关键节点。

下面是我对于这道题目给出的一些定义：

> 称点 $x$ 覆盖点 $y$，当且仅当点 $x$ 与点 $y$的距离不超过给定的距离限制 $mid$。（以下就直接使用这两个概念，不再重复）

>  而最小点覆盖的定义是，对于每个关键节点 $y$ ，选定的 $tot$ 个点中有**任意**一个点 $x$ 到点 $y$ 的距离不大于给定的距离限制 $mid$，令 $tot$ 最小。

> 选定节点为你选择的节点，关键节点同题目定义。

接下来怎么解决呢？我们发现，如果一棵子树的根 $root$ 到最远的关键节点的距离小于 $mid$ ，那意味着这整棵子树是可以被这个 $root$ 覆盖的.并且如果以这种方式自底而上递归，一定能够得出一种方案来解决这个问题，但这个方案很明显不是最优解。

为什么呢？经过观察，我们可以发现，如果每次贪心的采取这种方式，我们每次会重复覆盖一些点，这样就会得不到最优解，那怎么办呢？我们可以记录下每次未被之前覆盖的关键节点到 $root$ 的最远距离，这样就可以减少掉多余的覆盖。

为什么说叫做**减少**多余的覆盖，而不是**消除**所有多余的覆盖呢？经过思考，我们可以发现，我们覆盖整颗子树 $root$ 时，不一定会选定 $root$ 作为用来覆盖这棵子树的点，我们可能会使用 $root$ 下的子孙 $y$ 来覆盖整颗子树，从而得到更优解。

根据上面的两个思路，我们就可以想到设 $f_{root}$ 表示距 $root$ 最远的未被覆盖的关键节点到 $root$ 的距离，$g_{root}$为 $root$ 到该子树下的被选定节点的最小距离。

DP过程就为：

- 初值：$f_{root}=-\infty,g_{root}=\infty$

- $f_x=\max \{f_y+1\}$，$g_x=\min\{f_y+1\}$

这样就结束了么？是不是很好奇为什么没有用到$d_i$？

我们还需要特判几种情况以及统计最小点覆盖。

- 当$f_x+g_x<=mid$ ，说明只用已选定节点中到 $x$ 距离最小的点就能够覆盖到最远的关键节点，整棵子树自然可以被完全覆盖。就有$f_x=-\infty$
- 当$f_x = mid$ ，说明最远的关键节点到根的距离刚好为$mid$，如果我们此时不将 $x$ 节点作为被选定节点，那么这个最远的关键节点将永远无法被覆盖。所以我们只能选定 $x$ 节点作为选定节点。既然选定了我们也要把它计算到 $tot$ 里。$f_x=-\infty$，$g_x=0$，$++tot$(自身被选定了显然是 $0$ 啊)
- 当$g_x>mid \text{且} d_i=1$，说明到 $root$ 最近的选定节点无法被使用，$root$ 自身也是一个关键节点。所以这棵子树无法被它的子孙覆盖，也就是说这棵子树可能无法被完全覆盖，可以丢给它的父亲处理。$f_x=\max(f_x,0)$ (想一想，为什么)。

以上DP过程大概解释一下，当我们将 $f_x$ 置为 $-\infty$ 时，说明该子树已被完全覆盖，就不会影响其祖先的 $f$ 值。

**一定要记得特判根啊！！！**

**Show the Code**

```cpp
#include<cstdio>
//f[i] 以i为根的子树未被覆盖的最远距离
//g[i] 以i为根的子树被选择的点的最近距离
#define max(a,b) ((a)>(b)? (a):(b))
#define min(a,b) ((a)<(b)? (a):(b))
typedef long long ll;
const ll inf=1e8;
int n,m,res=0,cnt=0,tot=0;
int b[300005];
ll f[300005],g[300005];
int h[300005],to[600005],ver[600005];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline void add(int x,int y) {
	to[++cnt]=y;
	ver[cnt]=h[x];
	h[x]=cnt;
}
void dfs(int x,int fa,int mid) {
	f[x]=-inf;g[x]=inf;
	for(register int i=h[x];i;i=ver[i]) {
		int y=to[i];
		if(y==fa) continue;
		dfs(y,x,mid);
		f[x]=max(f[x],f[y]+1);
		g[x]=min(g[x],g[y]+1);
	}
	if(f[x]+g[x]<=mid) f[x]=-inf;//不需要再被覆盖，直接置为-inf
	if(g[x]>mid&&b[x]==1) f[x]=max(f[x],0);//当前无法覆盖，需要父亲帮忙
	if(f[x]==mid) f[x]=-inf,g[x]=0,++tot;//不需要再被覆盖
}
int check(int x) {
	tot=0;
	dfs(1,-1,x);
	if(f[1]>=0) ++tot;
	return tot<=m;
}
int main() {
	n=read(),m=read();
	for(register int i=1;i<=n;++i) b[i]=read();
	for(register int i=1;i<n;++i) {
		int x=read(),y=read();
		add(x,y);add(y,x);
	}
	int L=0,R=n;
	while(L<=R) {
		int mid=L+R>>1;
		if(check(mid)) {R=mid-1;res=mid;}
		else {L=mid+1;}
	}
	printf("%d\n",res);
	return 0;
}
```



---

## 作者：Kelin (赞：27)

题意:给一棵树,树上有一些关键节点,选m个点,使得关键节点到这些点中距离的最小值的最大值最小

最大值最小,果断二分答案

我们只需要判定是否存在m个点能够在mid范围内到达所有关键点

暴力:从每个点bfs一遍看看mid范围能是否能覆盖到所有的点,o(n^2logn)

发现可以贪心,一个关键点要么被它的子树内的点管理,要么被它子树外的点管理,于是我们记录个pair/struct

first表示以x为根的子树中目前还没有人管理的关键点距离x的最远的距离,second表示以x为根的子树中选择了的点距离x的最近的距离.

①if(first+second<=mid)以x为根的树是可以自己处理的

②if(first==mid)就意味着必须要选择x这个点了

因为再向上一个点距离就超过mid了,这时候强制选择x这个点,并更新first，second即可

③if(这个点是关键点&&second>mid)就要更新first了

注意出来的时候要特判1(树根)


---

## 作者：奇米 (赞：14)

## 题解- P3523 DYN-Dynamite

* **题目意思**
	
    就是在一颗树中选$m$个点使得这$m$个点到关键点的距离最大值最小。
    
* $Sol$
	
    * [双倍经验](https://www.luogu.com.cn/problem/P3942)
    
    总算看懂题解来重新理解一遍，加深记忆。。
    
    回归正题，因为题目要我们求最大值最小显然会想到二分。
    
    首先我们设几个变量：
    
    $f_i$表示以$i$为子树最近选择节点的距离
    
    $g_i$表示以$i$为子树最远还没有选择的关键点距离
    
    $mid$表示我们二分出来的答案
    
    对于求$f_i,g_i$还是比较基础的：
    	
    $f_u=\min\{f_v+1,f_u\},v∈u$
    
    $g_u=\max\{g_v+1,g_u\},v∈u$
    
    但是重点来了！
    
    要分$3$种情况来讨论：
    
    $(i) f_u>mid$并且$u$为关键点\
		$g_u=\max\{g_u,0\}$
        
     如何理解呢？因为最近的点暂时无法满足条件
     
    $(ii) f_u+g_u\leq mid $
    
    现在$g_u=-oo$,因为以$u$为子树的所有点都可以被覆盖，所以没有无法覆盖的点故$g_u=-oo$
    
    $(iii) g_u=mid$
    
    现在这个点已经最远，无法选择更远的啦。所以这个点必须要选，故$f_u=0$因为自己选自己最近为$0$，$g_u=-oo$。
    
    但是最后还要判断根节点的情况就可以了。
    
```cpp

#include <bits/stdc++.h>
using namespace std;

inline int read()
{
	int sum=0,ff=1; char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(isdigit(ch))
		sum=sum*10+(ch^48),ch=getchar();
	return sum*ff;
}

const int N=5e5+5;

int n,m,cnt,f[N],g[N],is[N],head[N],ans,gs;

struct nood
{
	int nex,to;
};
nood e[N*2];

inline void jia(int u,int v)
{
	e[++cnt].nex=head[u];
	head[u]=cnt;
	e[cnt].to=v;
}

inline void dfs(int u,int fa,int x)
{
	f[u]=1e9;
	g[u]=-1e9;
	for ( int i=head[u];i;i=e[i].nex )
	{
		int v=e[i].to;
		if(v==fa) continue;
		dfs(v,u,x);
		f[u]=min(f[v]+1,f[u]);
		g[u]=max(g[v]+1,g[u]);
	}
	if(is[u]&&f[u]>x) g[u]=max(g[u],0);
	if(g[u]+f[u]<=x) g[u]=-1e9;
	if(g[u]==x)
		gs++,g[u]=-1e9,f[u]=0;
}

inline bool check(int mid)
{
	gs=0;
	dfs(1,0,mid);
	gs+=(g[1]>=0);
	return gs<=m;
}

int main()
{
	n=read();
	m=read();
	for ( int i=1;i<=n;i++ ) 
		is[i]=read();
	for ( int i=1;i<n;i++ )
	{
		int x,y;
		x=read(),y=read();
		jia(x,y);
		jia(y,x);
	}
	int l=0,r=n;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(check(mid))
		{
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}
	
```

    

---

## 作者：ddwqwq (赞：11)

看到令最大值最小很自然地想到二分。又~~很套路地~~想到这个贪心：按深度从大到小依次考察所有关键结点，假如离它最近的已选择结点距离其超过当前二分的答案，则再选择一个它的尽量靠近根结点的祖先。最后判断选择的结点总数是否小于$M$。  
但是有一个问题，那就是难以快速找出当前点集中距离某个给定结点最近的元素。很多人正是因为这个问题才放弃了这个做法的。但事实上我们可以通过某些办法解决这个问题。下面是两个实现该功能的方法。  
一.根号重构法  
根号重构经常被用来解决各种动态维护问题，比如P2137 Gty的妹子树 和 朝鲜树 都用到了这个思想。  
具体到本题，首先，对于一个固定的点集，我们可以通过两次dfs（一次处理子树，一次处理祖先）来轻松$O(n)$找出距离每个树上结点最近的点集元素。现在需要实现向点集中加入元素的操作。我们可以这样：  
当收到一个修改操作，先不急着更新每个结点对应的最近元素，而是把它储存进一个待修改队列，等到攒够$\sqrt{n}$个操作后统一dfs修改。期间每次收到查询操作，都要遍历整个队列，考虑加入队列中的元素后的影响。为了加快速度，我们使用欧拉序来$O(1)$求LCA和结点间距离。  
这样，均摊复杂度可以达到$O(n\sqrt{n})$。通过均值不等式，很容易可以证明，这是最优的。算上二分查找的开销，总共$O(n\sqrt{n}logn)$。经本人测试，三十万的数据需要运行六秒左右，提交上去能得到80分。~~或许有人能卡过呢？~~  
代码最后一起放。  
二.动态点分治  
其实了解过动态点分治的人不难想到这个做法。   
首先建立点分治树，在树上的每个结点用线段树维护这个联通块的所有结点中每个属于点集的结点到分治中心的最短距离。查询和修改都是一路从操作结点爬到根结点修改。  
每个操作$O(log^2n)$，但对于并非专门构造的数据常数不大。所以算上二分查找的开销，总共$O(nlog^3n)$，但对于极限数据的实际运行时间已经很接近通过了。不过我实现的不够好，只骗到了90分。如果有大佬把zkw线段树之类的东西都用上，应该是可以过去的。  
  
 下面是两份代码。首先是根号重构法。
 ```
#include <stdio.h>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <time.h>

#pragma warning(disable:4996)

template<typename T> T min(T x, T y)
{
    return x < y ? x : y;
}
template<typename T> T max(T x, T y)
{
    return x > y ? x : y;
}

const int MAXN = 300005;
const int B = 400;
const int INF = 2000000005;

struct node {
    int to;
    node *next;
};
void addnode(node *&head, int to)
{
    node *p = new node;
    p->to = to;
    p->next = head;
    head = p;
}

int N, M;
node *edge[MAXN];
int deep[MAXN], fa[MAXN][25], key[MAXN], cnt;
int rank[MAXN], st[MAXN * 2][25], len;
int f[MAXN], list[MAXN], num;
bool mark[MAXN];

bool cmp(const int u, const int v)
{
    return deep[u] > deep[v];
}

int anc(int x, int k)
{
    for (int i = 0; i < 25; i++)
        if (k&(1 << i))
            x = fa[x][i];
    return x;
}
int LCA(int x, int y)
{
    x = rank[x];
    y = rank[y];
    if (x > y)
        std::swap(x, y);
    int len = y - x + 1;
    int t = 0;
    while (1 << t <= len)
        t++;
    t--;
    y = y - (1 << t) + 1;
    return deep[st[x][t]] > deep[st[y][t]]? st[y][t] : st[x][t];
}
int dis(int x, int y)
{
    return deep[x] + deep[y] - 2 * deep[LCA(x, y)];
}

int nearest(int v)
{
    int x = f[v];
    for (int i = 1; i <= num; i++)
        x = min(x, dis(v, list[i]));
    return x;
}

void dfs1(int v)
{
    f[v] = mark[v]? 0: INF;
    for (node *p = edge[v]; p; p = p->next)
        if (p->to != fa[v][0])
        {
            dfs1(p->to);
            f[v] = min(f[v], f[p->to] + 1);
        }
}
void dfs2(int v)
{
    f[v] = min(f[v], f[fa[v][0]] + 1);
    for (node *p = edge[v]; p; p = p->next)
        if (p->to != fa[v][0])
            dfs2(p->to);
}

void insert(int v)
{
    list[++num] = v;
    if (num == B)
    {
        for (int i = 1; i <= num; i++)
            mark[list[i]] = true;
        dfs1(1);
        dfs2(1);
        num = 0;
    }
}

bool judge(int d)
{
    int i, n = 0;
    num = 0;
    memset(mark, 0, sizeof(mark));
    memset(f, 63, sizeof(f));

    for (i = 1; i <= cnt; i++)
    {
        if (nearest(key[i]) > d)
        {
            n++;
            insert(anc(key[i], min(d, deep[key[i]])));
        }
    }
    return n <= M;
}

void dfs(int v)
{
    st[++len][0] = v;
    rank[v] = len;
    for (int i = 1; i < 25; i++)
        fa[v][i] = fa[fa[v][i - 1]][i - 1];
    for (node *p = edge[v]; p; p = p->next)
        if (p->to != fa[v][0])
        {
            fa[p->to][0] = v;
            deep[p->to] = deep[v] + 1;
            dfs(p->to);
            st[++len][0] = v;
        }
}

void init()
{
    int i, j, u, v;
    
    scanf("%d %d", &N, &M);
    for (i = 1; i <= N; i++)
    {
        scanf("%d", &u);
        if (u)
            key[++cnt] = i;
    }
    for (i = 1; i < N; i++)
    {
        scanf("%d %d", &u, &v);
        addnode(edge[u], v);
        addnode(edge[v], u);
    }

    dfs(1);
    std::sort(key + 1, key + cnt + 1, cmp);

    deep[0] = INF;
    for (i = 1; i < 25; i++)
    {
        int r = min(1 << (i - 1), len);
        for (j = 1; j <= len; j++)
        {
            if (r < len)
                r++;
            st[j][i] = cmp(st[j][i - 1], st[r][i - 1]) ?
                st[r][i - 1] : st[j][i - 1];
        }
    }
}

int main()
{
    int l = -1, r = MAXN;

    init();
    while (r - l > 1)
    {
        int mid = (l + r) / 2;
        if (judge(mid))
            r = mid;
        else
            l = mid;
    }

    printf("%d\n", r);

    return 0;
}
 ```  
 接下来是动态点分治
 ```
#include <stdio.h>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <time.h>

#pragma warning(disable:4996)

template<typename T> T min(T x, T y)
{
    return x < y ? x : y;
}
template<typename T> T max(T x, T y)
{
    return x > y ? x : y;
}

const int MAXN = 300005;
const int INF = 2000000005;

struct tree{
private:
    int l;
    int r;
    int mn;
    tree *lson;
    tree *rson;
public:
    tree(int L, int R)
    {
        l = L;
        r = R;
        mn = INF;
        lson = rson = NULL;
    }	
    void fixup()
    {
        mn = INF;
        if(lson)
            mn = min(mn, lson->mn);
        if(rson)
            mn = min(mn, rson->mn);
    }
    void update(int id, int k)
    {
        if(l == r)
        {
            mn = k;
            return;
        }
        int mid = (l + r) / 2;
        if(id <= mid)
        {
            if(!lson)
                lson = new tree(l, mid);
            lson->update(id, k);
        }
        else
        {
            if(!rson)
                rson = new tree(mid + 1, r);
            rson->update(id, k);
        }
        fixup();
    }
    int query(int L, int R)
    {
        if(l >= L && r <= R)
            return mn;
        int mid = (l + r) / 2;
        int x = INF;
        if(L <= mid && lson)
            x = min(x, lson->query(L, R));
        if(R > mid && rson)
            x = min(x, rson->query(L, R));
        return x;
    }
    void clear()
    {
        mn = INF;
        if(lson)
            lson->clear();
        if(rson)
            rson->clear();
    }
};

struct node {
    int to;
    node *next;
};
void addnode(node *&head, int to)
{
    node *p = new node;
    p->to = to;
    p->next = head;
    head = p;
}

int N, M;
node *edge[MAXN];
int deep[MAXN], fa[MAXN][25], key[MAXN], cnt;
int rank[MAXN], st[MAXN * 2][25], len;

bool cmp(const int u, const int v)
{
    return deep[u] > deep[v];
}

int anc(int x, int k)
{
    for (int i = 0; i < 25; i++)
        if (k&(1 << i))
            x = fa[x][i];
    return x;
}
int LCA(int x, int y)
{
    x = rank[x];
    y = rank[y];
    if (x > y)
        std::swap(x, y);
    int len = y - x + 1;
    int t = 0;
    while (1 << t <= len)
        t++;
    t--;
    y = y - (1 << t) + 1;
    return deep[st[x][t]] > deep[st[y][t]]? st[y][t] : st[x][t];
}
int dis(int x, int y)
{
    return deep[x] + deep[y] - 2 * deep[LCA(x, y)];
}

namespace DIV
{
    int fa[MAXN], cnt[MAXN];
    bool mark[MAXN];
    tree *T[MAXN];
    int *list[MAXN];
    
    bool vis[MAXN];
    int size[MAXN], mxs[MAXN], root, tot;
    void dfs(int v, int fa)
    {
        size[v] = 1;
        mxs[v] = 0;
        for(node *p = edge[v]; p; p = p->next)
            if(p->to != fa && !vis[p->to])
            {
                dfs(p->to, v);
                size[v] += size[p->to];
                mxs[v] = max(mxs[v], size[p->to]);
            }
        mxs[v] = max(mxs[v], tot - size[v]);
        if(!root || mxs[root] > mxs[v])
            root = v;
    }
    int getr(int v)
    {
        dfs(v, 0);
        tot = size[v];
        root = 0;
        dfs(v, 0);
        return root;
    }
    void pushin(int v, int fa, int *a, int &cur)
    {
        a[++cur] = v;
        for(node *p = edge[v]; p; p = p->next)
            if(p->to != fa && !vis[p->to])
                pushin(p->to, v, a, cur);
    }
    void build(int v)
    {
        dfs(v, 0);
        cnt[v] = size[v];
        T[v] = new tree(1, cnt[v]);
        list[v] = new int[cnt[v] + 2];
        cnt[v] = 0;
        pushin(v, 0, list[v], cnt[v]);
        std::sort(list[v] + 1, list[v] + cnt[v] + 1);	
        
        vis[v] = true;
        for(node *p = edge[v]; p; p = p->next)
            if(!vis[p->to])
            {
                int t = getr(p->to);
                fa[t] = v;
                build(t);
            }
    }
    void update(int v)
    {
        mark[v] ^= 1;
        int p = std::lower_bound(list[v] + 1, list[v] + cnt[v] + 1, v) - list[v];
        if(mark[v])
            T[v]->update(p, 0);
        else
            T[v]->update(p, INF);
        int x = v;
        while(fa[v])
        {
            v = fa[v];
            p = std::lower_bound(list[v] + 1, list[v] + cnt[v] + 1, x) - list[v];
            T[v]->update(p, mark[x]? dis(v, x): INF);
        }
    }
    int query(int v)
    {
        if(mark[v])
            return 0;
        int x = v;
        int d = T[v]->query(1, cnt[v]);
        while(fa[v])
        {
            v = fa[v];
            d = min(d, dis(v, x) + T[v]->query(1, cnt[v]));
        }
        return d;
    }
    void clear()
    {
        memset(mark, 0, sizeof(mark));
        for(int i = 1; i <= N; i++)
            T[i]->clear();
    }
}

bool judge(int d)
{
    int i, n = 0;
    DIV::clear();

    for (i = 1; i <= cnt; i++)
    {
        if (DIV::query(key[i]) > d)
        {
            n++;
            DIV::update(anc(key[i], min(d, deep[key[i]])));
        }
    }
    return n <= M;
}

void dfs(int v)
{
    st[++len][0] = v;
    rank[v] = len;
    for (int i = 1; i < 25; i++)
        fa[v][i] = fa[fa[v][i - 1]][i - 1];
    for (node *p = edge[v]; p; p = p->next)
        if (p->to != fa[v][0])
        {
            fa[p->to][0] = v;
            deep[p->to] = deep[v] + 1;
            dfs(p->to);
            st[++len][0] = v;
        }
}

void init()
{
    int i, j, u, v;
    
    scanf("%d %d", &N, &M);
    for (i = 1; i <= N; i++)
    {
        scanf("%d", &u);
        if (u)
            key[++cnt] = i;
    }
    for (i = 1; i < N; i++)
    {
        scanf("%d %d", &u, &v);
        addnode(edge[u], v);
        addnode(edge[v], u);
    }

    dfs(1);
    std::sort(key + 1, key + cnt + 1, cmp);

    deep[0] = INF;
    for (i = 1; i < 25; i++)
    {
        int r = min(1 << (i - 1), len);
        for (j = 1; j <= len; j++)
        {
            if (r < len)
                r++;
            st[j][i] = cmp(st[j][i - 1], st[r][i - 1]) ?
                st[r][i - 1] : st[j][i - 1];
        }
    }
    
    DIV::build(DIV::getr(1));
}

int main()
{
    int l = -1, r = MAXN;

    init();
    while (r - l > 1)
    {
        int mid = (l + r) / 2;
        if (judge(mid))
            r = mid;
        else
            l = mid;
    }

    printf("%d\n", r);

    return 0;
}
 ``` 
 就这么多啦！~~然而我最后还是写的正解才卡过。。~~

---

## 作者：Captain_Paul (赞：4)

这道题乍一看非常毒瘤~~（其实我连题都没看懂）~~

看到最大值最小，可以想到二分答案

我们直接二分出题目所求的“关键节点到这些点中距离的最小值的最大值”

然后题意转化成为：已知一个点可以覆盖的范围，判断能否用不超过m个点覆盖整棵树

那么如何check二分的答案呢？

可以用贪心解决~~（虽然我也是看了题解）~~

从1号节点开始dfs，直到当前节点k与关键节点的距离达到mid，就把k选中

贪心的正确性是比较显然的：

如果在k的子树中选择了节点，则其向上能覆盖的范围一定不会超过k的覆盖范围

楼下Kelin大佬讲得非常详细~~（太强了）~~

丑陋的代码：

```cpp
#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
#define reg register
using namespace std;
const int N=3e5+5;
struct edge
{
	int to,nxt;
}edge[N<<1];
int n,m,num,t,tot,f[N],fa[N],cnt[N],head[N];
bool ex[N];
inline int read()
{
	int x=0,w=1;
	char c=getchar();
	while (!isdigit(c)&&c!='-') c=getchar();
	if (c=='-') c=getchar(),w=-1;
	while (isdigit(c))
	{
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*w;
}
inline void add_edge(int from,int to)
{
	edge[++num].nxt=head[from];
	edge[num].to=to;
	head[from]=num;
}
void dfs(int k)//已知覆盖范围，用最少的点覆盖整棵树（从下向上贪心，必须选才选） 
{
	int tmp1=ex[k]?0:-1e7,tmp2=-1e7;
	for (reg int i=head[k];i;i=edge[i].nxt)
	{
		int v=edge[i].to;
		if (v==fa[k]) continue;
	    fa[v]=k; dfs(v);
	    if (cnt[v]==1) tmp1=max(tmp1,f[v]+1);
	    if (cnt[v]==2) tmp2=max(tmp2,f[v]-1);
	}
	if (tmp1>tmp2)
	  if (tmp1==t) ++tot,cnt[k]=2,f[k]=t;
	  else cnt[k]=1,f[k]=tmp1;
	else cnt[k]=2,f[k]=tmp2;
}
inline bool check(int k)//即一个选择点能覆盖的范围 
{
	t=k; tot=0; dfs(1);
	if (f[1]>=0&&cnt[1]==1) ++tot;
	return tot<=m;
}
int main()
{
	n=read(),m=read();
	for (reg int i=1;i<=n;ex[i++]=read());
	for (reg int i=1;i<n;i++)
	{
		int x=read(),y=read();
		add_edge(x,y);
		add_edge(y,x);
	}
	int l=0,r=n,ans=0;
	while (l<=r)
	{
		int mid=(l+r)>>1;//关键点与选择点之间距离最小值的最大值 
		if (check(mid))
		{
			ans=mid; r=mid-1;
		}
		else l=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Apricot (赞：1)

### [POI2011]DYN-Dynamite

我们看到最大值最小，自然地想到二分，我们二分一个最大值，题目就转化为了一个点能覆盖mid范围内的点，求要有几个点能全部覆盖所有的特殊点。想到消防局的设立：但是这道题目又不能那么做。考虑DP，设F[i]表示
以i为根节点的子树中没有被覆盖的最远的点，g[i]表示以i为根的子树中距离i最近的已设立的点（为什么要这么操作?考虑树形dp一般是倒着跑dfs的，我们抉择要不要设立点肯定要考虑距离它最远的未被覆盖的点，而距离该点较远的已设立的点一定已经在之前考虑过了）这有无后效性呢？基于一个贪心：如果F[i]==mid,我们必须选这个点（正确性显然）。最后，如果该点必须要被覆盖但g[i]>mid,我们就要更新一下f[i],最后特判一下根节点。
## code：
```
#include<iostream>
#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
const int maxn=700006;
int n,m;
bool pan[maxn];
struct hzw
{
	int to,next,v;
}e[maxn];
int head[maxn],cur,tot,noc[maxn],hc[maxn];
inline void add(int a,int b)
{
	e[cur].to=b;
	e[cur].next=head[a];
	head[a]=cur++;
}
inline void dfs(int s,int k,int fa)
{
	noc[s]=-0x3f3f3f3f,hc[s]=0x3f3f3f3f;
	for (int i=head[s];i!=-1;i=e[i].next)
	{
		if (e[i].to==fa) continue;
		dfs(e[i].to,k,s);
		noc[s]=max(noc[s],noc[e[i].to]+1);
		hc[s]=min(hc[s],hc[e[i].to]+1);
	}
	if (pan[s]&&hc[s]>k) noc[s]=max(noc[s],0);
	if (hc[s]+noc[s]<=k) noc[s]=-0x3f3f3f3f;
	if (noc[s]==k) {tot++;hc[s]=0,noc[s]=-0x3f3f3f3f;}
}
inline bool check(int mid)
{
	tot=0;
	dfs(1,mid,1);
	if (noc[1]>=0) tot++;
	return tot<=m;
}
int main()
{
	memset(head,-1,sizeof(head));
	cin>>n>>m;
	for (int i=1;i<=n;++i) scanf("%d",&pan[i]);
	for (int i=1,a,b;i<=n-1;++i)
	{
		scanf("%d%d",&a,&b);
		add(a,b);
		add(b,a);
	}
	int l=0,r=n,ans=n;
	while (l<=r)
	{
		
		int mid=(l+r)>>1;
		if (check(mid))
		{
			r=mid-1;
			ans=min(ans,mid);
		}
		else 
		{
			l=mid+1;
		}
	}	
	cout<<ans;
	return 0;
}
```

---

