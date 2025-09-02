# 苗条的生成树 Slim Span

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4141

[PDF](https://uva.onlinejudge.org/external/13/p1395.pdf)

# 题解

## 作者：henrytb (赞：14)

### 刘汝佳大法好！

我henrytb又来宣传刘汝佳紫书大法了QAQ

这道题类似最小生成树，只不过是让最大边权减最小边权最小

采用Kruskal求解最小生成树，只不过我们只是对于每一个边都从它开始Kruskal一遍，来算全所有情况。

每一遍都更新一下答案

code:

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
struct edge{
    int a,b,w;
}e[100005];
int n,m,a[100005],b[100005],w[100005],fa[100005],ans,maxed;
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
bool cmp(edge a,edge b){
    return a.w<b.w;
}
bool merg(int x,int y){
    x=find(x),y=find(y);
    if(x==y)return 0;
    else fa[y]=x;
    return 1;
}
void init(){
    ans=2147483647;
    rep(i,1,n)fa[i]=i;
    sort(e+1,e+m+1,cmp);
}
bool kruskal(int ed){
    int now=0;
    rep(i,1,n)fa[i]=i;
    maxed=-1;
    rep(i,ed,m){
        if(merg(e[i].a,e[i].b)){
            maxed=e[i].w;
            if(++now==n-1)return true;
        }
    }
    return false;
}
int main(){
    while(~ scanf("%d%d",&n,&m)&&n){
        rep(i,1,m) scanf("%d%d%d",&e[i].a,&e[i].b,&e[i].w);
        init();
        rep(i,1,m){
            if(kruskal(i)){
                ans=min(ans,maxed-e[i].w);
            }
        }
        printf("%d\n",ans==2147483647?-1:ans);
    }
    return 0;
}
```

---

## 作者：Plus_Ultra (赞：7)

一. 题 目 大 意 :

求 最 大 边 权 与 最 小 边 权 差 值 最 小 的 生 成 树 ， 输 出 它 们 的 差 值 .

二. 解 法 :

入 手 这 道 题 , 我 们 可 以 想 到 暴 力 的 做 法 : 求 出 每 个 生 成 树 的 边 权 差 值 , 最 后 取 个 $min$ ,

所 以 按 照 $Kruskal$ 的 思 想 , 我 们 首 先 对 边 排 个 序,

从 小 到 大 枚 举 $K$ , 每 次 只 使 用 $K-M$ 中 的 边 跑 $Kruskal$ ( 这 样 可 以 涵 盖 所 有 答 案 , 想 想 为 什 么 ) , 答 案 取 $ min$ 即 可 .

三. 代 码 :

```
#include<bits/stdc++.h>

using namespace std;

int n,m,f[10010],tot,ans;
struct node
{
	int from,to,w;
}E[10010];

int find(int x)
{
	return f[x]==x?x:f[x]=find(f[x]);
}

void add(int x,int y,int z)
{
	E[++tot].from=x;
	E[tot].to=y;
	E[tot].w=z;
}

bool cmp(node a,node b)
{
	return a.w<b.w;
}

int main()
{
	while(cin>>n>>m)
	{
		if(n==0&&m==0) return 0;
		
		tot=0,ans=0x3f3f3f3f;
		for(int i=1,u,v,w;i<=m;i++)
		{
			cin>>u>>v>>w;
			add(u,v,w);
		}	
		
		sort(E+1,E+m+1,cmp);
		
		for(int i=1;i<=m;i++)
		{
			for(int k=1;k<=n;k++) f[k]=k;
			int cnt=0,maxx=0;
			
			for(int k=i;k<=m;k++)
			{
				int x=E[k].from,y=E[k].to;
				int fx=find(x),fy=find(y);
				if(fx==fy) continue;
				f[fx]=fy,cnt++;
				maxx=max(E[k].w-E[i].w,maxx);
				if(cnt==n-1) break;
			}
			
			if(cnt<n-1) continue;
			ans=min(ans,maxx);
		}
		
		if(ans==0x3f3f3f3f) cout<<"-1"<<endl;
		else cout<<ans<<endl;
	} 
}

```


---

## 作者：Sham_Sleep (赞：5)

刚刚干完我们学校网站的这个题 来干洛谷上的了qwq

其实这道题很简单，肯定是生成树没跑了，但你看那三秒的时限，你想到了什么qwq

没错当然是暴力啦qwq

生成树的算法我目前已知有两种：

1.Kruskal算法，简称k算法

核心思想：【贪心】 + 【并查集】 + 【排序】

适用：稀疏图

Kruskal算法就是讲已给边sort一遍，然后遍历每条边，将单个的块或者点连起来，而并查集就是判断两个点是否在一个集合



本蒟蒻代码
```
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

struct point{
	int e , s;
	int val;
};

int m , n;
int f;
long long ans;
int boss[50005];
point g[50005];

int find(int x)//并查集操作
{
	if(boss[x] == x) return x;
	int fa = find(boss[x]);
	return boss[x] = fa;
}

int cmp(point &a , point &b)//排序函数
{
	return a.val < b.val;
}

int main()
{
	scanf("%d %d" , &m , &n);
	for(int i = 1; i <= m; ++i) boss[i] = i;
	for(int i = 1; i <= n; ++i){
		scanf("%d %d %d" , &g[i].e , &g[i].s , &g[i].val);
	} 
	sort(g + 1 , g + 1 + n , cmp);
	for(int i = 1; i <= n; ++i){
		if(f == m - 1) break;//构成一个最小生成树只用点的个数-1条边就可以了
		int t1 = find(g[i].s);
		int t2 = find(g[i].e);
		if(t1 != t2)//进行图的合并，因为当前边是可以选中的最小的那个，所以不用考虑其他的
		{
			ans += g[i].val;
			boss[t1] = t2;
			++f;
		}
	}
	if(f == m - 1) printf("%d" , ans);
}
```
2.Prim算法，简称p算法

核心思想：【贪心】 + 【邻接表】/voctor/【邻接矩阵】（可加堆进行优化）

适用于：稠密图

Prim算法类似于Dij算法，但不同的是所用的距离数组含义不同，一个连接这个点的最小权值，一个是到这个点的最短路。但都是贪心算法，由一个点出发，将可以到的点纳入一个集合，再从这个集合里最短的点出发继续遍历。

本蒟蒻代码
```
#include <stdio.h>
#include <iostream>
#include <memory.h>
using namespace std;

struct node{
	int p;
	int val;
};

struct point{
	int pre;
	int to;
	int val;
};

int m , n;
int x , y , w;
int top;
int d[305];
int v[305];
int f[305];//表示状态，0代表没走过，1代表可以到达，2表示已经走过
point g[300 * 299 / 2];

void qxx(int fa , int child , int va)//邻接表
{
	g[++top].pre = v[fa];
	g[top].to = child;
	g[top].val = va;
	v[fa] = top;
}

int main()
{
	scanf("%d %d" , &m , &n);
	for(int i = 1; i <= m; ++i) d[i] = 0x7fffffff / 2;
	for(int i = 1; i <= n; ++i){
		scanf("%d %d %d" , &x , &y , &w);
		qxx(x , y , w);
		qxx(y , x , w);
	}
	d[1] = 0;
	f[1] = 1;
	int now = 1;
	for(int i = 1; i <= n; ++i){
		for(int j = v[now]; j; j = g[j].pre){
			int t = g[j].to;
			if(f[t] == 2) continue;
			d[t] = min(d[t] , g[j].val);
			f[t] = 1;
		}
		f[now] = 2;
		int minn = 0x7fffffff;
		for(int j = 1; j <= m; ++j){
			if(f[j] == 1 && d[j] < minn)
			{
				minn = d[j];//进行权值的更新，可以到达他的边的最小值
				now = j;
			}
		}
	}
	int ans = 0;
	for(int i = 1; i <= m; ++i){
		if(!f[i])
		{
			printf("no");
			return 0;
		}
		ans += d[i];
	}
	printf("%d" , ans); 
}
```

接下来进入正题，那么这道题该怎么做呢？？

其实根据Kruskal算法原理，我们可以知道k算法是由图中的最小边出发的，然后构建最小生成树

所以，我们可以枚举这个最小边，不断往下滑，这样，就可以不停的构成以第i条边为最小的生成树

所以，思路就很明显了，在原来生成树的代码下加上一层循环，枚举最小边

本蒟蒻代码
```
#include <stdio.h>
#include <iostream>
#include <memory.h>
#include <algorithm>
using namespace std;

struct point {
	int a;
	int b;
	int val;
};

int m , n;
int ans;
int boss[305];
point g[44855 * 2];

int cmp(point x , point y)//排序函数
{
	return x.val < y.val; 
}

int find(int x)//并查集操作
{
	if(boss[x] == x) return x;
	int fa = find(boss[x]);
	return boss[x] = fa;
}

int kr()//k算法
{
	ans = 0x7fffffff;
	memset(g , 0 , sizeof(g));
	scanf("%d %d" , &m , &n);
	if(m == 0 && n == 0) return 0;
	for(int i = 1; i <= n; ++i){
		scanf("%d %d %d" , &g[i].a , &g[i].b , &g[i].val);
	}
	sort (g + 1 , g + 1 + n , cmp);
	for(int i = 1; i <= n - m + 1; ++i){//进行枚举最小边
		int k = 0;
		int last;
		for(int j = 1; j <= m; ++j) boss[j] = j;
 		for(int j = i; j <= n; ++j){
			if(k == m - 1)
			{
				last = j - 1;
				break;
			} 
			int t1 = find(g[j].a);
			int t2 = find(g[j].b);
			if(t1 != t2)
			{
				boss[t1] = t2;
				++k;
			}
		}
		if(k < m - 1) break;
		ans = min(ans , g[last].val - g[i].val);
	}
	if(ans == 0x7fffffff) printf("-1\n");
	else printf("%d\n" , ans);
	return 1;
}

int main()
{
	while(kr());
	return 0;
}
```
支持一下本蒟蒻吧QAQ

---

## 作者：月影舞纵丶 (赞：3)

# 蒟蒻的第一篇题解
### 这个题不需要用Kruskal或者Prim去求解最小生成树

题目并没有要求生成树的权值之和最小，而是苗条度（最大边权减最小边权的值）最小。

【分析】
此题数据规模不大，因此可以直接枚举苗条度。

可以假设有一个边集区间【L,R】,这个边集中的边能够使得图中的节点全部连通，则存在一个苗条度不超过W[R]-W[L]的生成树（W[i]表示排序之后第i条边的权值）

【做法】只需采用并查集进行点的合并和查询，不需要求解最小生成树

直接枚举L，对于每个确定的L，从小到大枚举R，将边集【L,R】中所有边的两个端点合并，直到全部点连通，则该L下的苗条度可以确定，若直到R=m全部点还没有连通，则说明该L不能生成一棵连通的树。

每次换用下一个L的时候将R重置为L。

AC代码：

```cpp
#include "bits/stdc++.h"
using namespace std; 
const int MAXN=210;
struct Edge{
	int u;
	int v;
	int w;
}edge[MAXN*MAXN];//定义边 
bool cmp(Edge a,Edge b){return a.w<b.w;}
int s[MAXN];
int find(int u){
	if(s[u]!=u) s[u]=find(s[u]);
	return s[u];
}//并查集查找 
void unio(int x,int y){
	x=find(x);y=find(y);
	if(x!=y) s[x]=y;
}//并查集合并 
int n,m;
void init(){for(int i=1;i<=n;i++) s[i]=i;}//初始化 
bool pd(){
	for(int i=2;i<=n;i++)
	    if(find(i)!=find(i-1)) return false;
	    return true;
}//判断是否生成了一颗连通的树 
int main(){
	for(;;){
		cin>>n>>m;
		if(n==0&&m==0) break;
		init();
		int ans=0x7fffffff;
		for(int i=1;i<=m;i++) cin>>edge[i].u>>edge[i].v>>edge[i].w;
		sort(edge+1,edge+1+m,cmp);//从小到大将边进行排序 
		for(int l=1;l<=m;l++){// 从小到大枚举L，对于每个L，从小到大枚举R，用并查集合并边集[L,R]中所有边的两端点 
			init();
			int r=l;
			unio(edge[r].u,edge[r].v);
			while(!pd()){
				 r++;
				 if(r>m) break;
				 unio(edge[r].u,edge[r].v);
			}
			if(pd()) ans=min(ans,edge[r].w-edge[l].w);//如果对于枚举的L，可以生成一颗连通的树，则将答案更新 
		}
		if(ans==0x7fffffff) cout<<"-1"<<endl;
		else cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：sel_fish (赞：3)

这道题一看就是暴力，n≤100，随便搞搞就A了

1. 因为题目中要求在所有生成树中让我们求最大值和最小值差值最小，我们可以枚举每一个生成树

2. 思考如何更好的求出差值？我们可以把所有边从大到小排一次序，那么我们求出生成树之后，我们只需要将最开始的那条边的权值减去最后那条的边的权值和ans取更小值即可，因为我们已经排过序了，所以这样时正确的

3. 关于最小生成树，我就不多bb了，但我还是怕有一些跳级生不懂如何求最小生成树，我在这儿讲一下kruscal算法，kruscal算法的辅助算法是并查集

4. 由于一棵树的边数为点数减1，所以我们要求出一颗树的最小生成树，只需要将边权从小到大排好序之后，每次取出一条边的两端，如果没有在一个集合里，我们就合并在一起，然后把当前边权加到ans里即可

AC代码

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define re register int
using namespace std;
struct edge {
	int a,b,w;
}e[20010];
int n,m,k,ans,fa[10010];
inline int read() {
	char ch=getchar();
	int x=0,cf=1;
	while(ch<'0'||ch>'9') {
		if(ch=='-') cf=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*cf;
}
inline int min(int A,int B) { return A<B?A:B; }
inline bool cmp(edge A,edge B) { return A.w>B.w; }
inline int find(int x) {
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
int main() {
	while(scanf("%d%d",&n,&m)!=EOF) {
		if(!n&&!m) break;
		ans=0x3f3f3f3f;
		for(re i=1;i<=m;i++) {
			e[i].a=read(),e[i].b=read();
			e[i].w=read();
		}
		sort(e+1,e+m+1,cmp);
		for(re i=1;i<=m;i++) {
			for(re j=1;j<=n;j++) fa[j]=j; k=0;
			for(re j=i;j<=m;j++) {
				int x=e[j].a,y=e[j].b;
				if(find(x)!=find(y)) {
					fa[find(x)]=find(y); k++;
					if(k==n-1) {
						ans=min(ans,e[i].w-e[j].w);
						break;
					}
				}
			}
		}
		if(ans==0x3f3f3f3f) printf("-1\n");
		else printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：hulean (赞：1)

## 【题意】

给出一个$n(n<=100)$个节点的的图，求最大边减最小边尽量小的生成树。

## 【算法】

$Kruskal$

## 【分析】

首先把边按边权从小到大进行排序。对于一个连续的边集区间$[L,R]$，如果这些边使得$n$个点全部联通，则一定存在一个苗条度不超过$W[R]-W[L]$的生成树（其中$W[i]$表示排序后第$i$条边的权值）。

从小到大枚举$L$，对于每个$L$，从小到大枚举$R$，同时用并查集将新进入$[L,R]$的边两端的点合并成一个集合，与$Kruskal$算法一样。当所有的点都联通是停止枚举$R$，换下一个$L$(并且把$R$重置为$L$)，继续枚举。

## 【代码】

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=100+10;
const int MAXM=10000+10;
int n,m;
int fa[MAXN];
int maxn,ans=0x3f3f3f3f;
struct Node
{
    int u,v,w;
}edge[MAXM];
inline int read()
{
    int tot=0;
    char c=getchar();
    while(c<'0'||c>'9')
        c=getchar();
    while(c>='0'&&c<='9')
    {
        tot=tot*10+c-'0';
        c=getchar(); 
    }
    return tot;
}
inline bool cmp(Node x,Node y)
{
    return x.w<y.w;
}
inline int find(int k)//并查集
{
    if(fa[k]==k)return k;
    else return fa[k]=find(fa[k]);
}
inline bool kruskal(int k)//判断是否能形成生成树
{
    maxn=0;
    int tot=0;
    for(int i=1;i<=n;i++)
        fa[i]=i;
    for(int i=k;i<=m;i++)
    {
        if(fa[find(edge[i].u)]!=fa[find(edge[i].v)])
        {
            maxn=edge[i].w;
            fa[find(edge[i].u)]=fa[find(edge[i].v)];
            tot++;
        }
        if(tot==n-1)return 1;//如果所有点都联通，则返回true
    }
    return 0;//否则返回false
}
int main()
{
    while(1)
    {
        ans=0x3f3f3f3f;
        n=read();m=read();
        if(!n&&!m)break;
        for(int i=1;i<=m;i++)
        {
            edge[i].u=read();
            edge[i].v=read();
            edge[i].w=read();
        }
        sort(edge+1,edge+1+m,cmp);//给边进行从小到大排序
        for(int i=1;i<=m;i++)//枚举L
        {
            if(kruskal(i))
            {
                ans=min(ans,maxn-edge[i].w);//更新最小值
            }
        }
        if(ans!=0x3f3f3f3f)cout<<ans<<endl;
        else cout<<-1<<endl;//特判
    }
    return 0;
}
```

**刘汝佳大法好！**

---

## 作者：小闸蟹 (赞：1)

```cpp
// 首先按权值把边从小到大排序
// 然后我们不断地向并查集里面加入新的边
// 一开始加入的边为L，最后加入的边为R
// 类似Krushal，直到所有边都联通了为止
// 然后计算d[R] - d[L]，更新答案，L向前推进
// 再把R重置为L，重复上面的过程直到走到底
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>

constexpr int MaxN = 100 + 10;
constexpr int INF = 999999999;

int n, m;   // n：点的个数   m：边的个数
std::array<int, MaxN> p{ 0 };

// 并查集的查找操作
int Find(int x)
{
    if (p[x] == x)
    {
        return x;
    }
    else
    {
        return p[x] = Find(p[x]);
    }
}

// 快读
int Read()
{
    int n = 0, k = 1;
    char ch = getchar();
    while ((ch > '9' || ch < '0') && ch != '-')
        ch = getchar();

    if (ch == '-')
    {
        k = -1;
        ch = getchar();
    }

    while (ch <= '9' && ch >= '0')
    {
        n = n * 10 + ch - '0';
        ch = getchar();
    }

    return n * k;
}

class Edge
{
public:
    int u, v, d;

    Edge() = default;
    Edge(int u, int v, int d) : // 从u到v有一条权值为d的无向边
        u(u), v(v), d(d)
    {
    }
};

std::vector<Edge> e;

int Solve()
{
    // 首先把边按权值从小到大排序
    std::sort(e.begin(), e.end(), [](const Edge &a, const Edge &b)
    {
        return a.d < b.d;
    });

    int Ans = INF;
    for (int L = 0; L < m; ++L)
    {
        for (int i = 1; i <= n; ++i)
        {
            p[i] = i;   // 初始化并查集
        }

        auto cnt = n;
        for (int R = L; R < m; ++R)
        {
            auto u = Find(e[R].u);
            auto v = Find(e[R].v);
            if (u != v) // 如果不在一个集合里
            {
                p[u] = v;   // 那就加入并查集
                --cnt;
                if (cnt == 1)   // 如果已经联通了，那就更新一下答案，立即退出循环
                {
                    Ans = std::min(Ans, e[R].d - e[L].d);
                    break;
                }
            }
        }
    }

    return (Ans == INF ? -1 : Ans);
}

int main()
{
    while (std::cin >> n >> m && n)
    {
        e.clear();
        for (int i = 0; i < m; ++i)
        {
            int u, v, d;
            u = Read();
            v = Read();
            d = Read();
            e.emplace_back(u, v, d);
        }

        std::cout << Solve() << std::endl;
    }

    return 0;
}
```

---

## 作者：Kendrick_Z (赞：1)

## 先宣传自己的博客

欢迎大佬来踩来hack

## [点一下玩一年](https://www.luogu.org/blog/142373/)

紫书（P358最上方）
在某地培训写了这道题于是写一波题解

感觉前面的题解代码不是特别好理解

于是自己写一篇

# Kruskal+枚举

首先按照求最小生成树的套路
那么我们一定要给边权排序

那么我们思考一下

要求最大减去最小最小 

根据最小生成树一定是瓶颈生成树

（瓶颈生成树：最大边权值最小）

那么我们只需要从最小开始枚举 每次比较 边权最大值和最小值进行比对就切了

记得判断最小生成树是否生成和并查集初始化和每次清空

贴下代码（拒绝抄袭）

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
const int N=1e6;
const int INF=1E7; 
int n,m,f[N];
struct Edge{
	int from,w,to;
}e[N];
bool cmp(Edge a,Edge b){
	return a.w<b.w;
}
int find(int x){
	if(f[x]!=x){
		f[x]=find(f[x]);
		return f[x];
	} else
		return x;
}
using namespace std;
int main(){
	while(scanf("%d%d",&n,&m)!=EOF&&(n||m)){
	memset(e,0,sizeof(e));
		for(int i=1;i<=m;i++){
			scanf("%d%d%d",&e[i].from,&e[i].to,&e[i].w);
		}
		sort(e+1,e+m+1,cmp); 
		int ans=INF;
		int maxx=0;
		int minn=INF;
		int cnt=n;
		for(int i=1;i<=m;i++){
			for(int p=1;p<=n;p++) f[p]=p;
			for(int j=i;j<=m;j++){
				int fx=find(e[j].from);
				int fy=find(e[j].to) ;
				if(fx!=fy){
					f[fy]=fx;
					maxx=max(maxx,e[j].w);//取边权最大值 
					cnt--;
				}	
			}
			if(cnt==1){//最小生成树是否生成 
			ans=min(ans,maxx-e[i].w);}//最小 
		}
		if(ans==INF){
		ans=-1;}
		printf("%d\n",ans);
	}
	return 0;
} 
```

---

## 作者：ynzzr (赞：0)

这道题是一道经典的 _最小生成树_ ，可以用**kruskal**算法来解决。

Kruskal

•把所有边排序，记第i小的边为e[i]（1<=i<m）

•初始化MST为空

•初始化连通分量，让每个点自成一个独立的连通分量
```pascal
•for i:=1 to m do
   if(e[i].u和e[i].v不在同一个连通分量) begin
    把边e[i]加入MST
    合并e[i].u和e[i].v所在的连通分量
    end;
```
```pascal
Kruskal算法伪代码
•循环n-1次，n表示节点数{

▫找相关节点未在同一棵树中的最小边E find(i)<>find(j)//find函数返还的是树的顶点

▫连接E相关的两棵树 union(i,j)——father[i]:=j;
•}

•function find(i){Father[i]表示树中i节点的前继节点

▫if father[i]=i then exit(i);
▫ find:=find(father[i]);

▫ father[i]:=find;

•}
```
代码如下：
```pascal
var u,v,w:array[1..5000]of longint;//u数组记录一条边的起点，v数组记录一条边的终点，w数组记录一条边的长度
    p:array[1..100]of longint;//记录该点所在的集合的根
    f:boolean;//判断是否有解
    i,j,n,sum,m,x,y,cnt:longint;
    procedure sort(l,r: longint);//按边的长度由小到大排序
      var
         i,j,y: longint;x,t:longint;
      begin
         i:=l;
         j:=r;
         x:=w[(l+r) div 2];
         repeat
           while w[i]<x do
            inc(i);
           while x<w[j] do
            dec(j);
           if not(i>j) then
             begin
                t:=w[i];
                w[i]:=w[j];
                w[j]:=t;
                y:=u[i];
                u[i]:=u[j];
                u[j]:=y;
                y:=v[i];
                v[i]:=v[j];
                v[j]:=y;
                inc(i);
                j:=j-1;
             end;
         until i>j;
         if l<j then
           sort(l,j);
         if i<r then
           sort(i,r);
      end;
function find(x:longint):longint;//寻找该点所在的集合根
begin
  if p[x]=x then exit(x)
   else begin p[x]:=find(p[x]);exit(p[x]);end;//如果自身不是这个集合的根，就直接和这个集合的根连起来，节省之后的查询时间
end;
begin
  read(n,m);
  while (n<>0) do//多组数据
  begin
  for i:=1 to m do
   read(u[i],v[i],w[i]);
  if m=0 then writeln(-1)//如果一条路都没有，进行特判，输出-1
  else begin
  sort(1,m);//排序
  sum:=maxlongint;//sum的值是最长边与最短边之差，为了使它们之差尽量小，初始成无穷大
  f:=false;//初始成无解，若有解，就更改为true
  for i:=1 to m do//枚举最短的边
  begin
   for j:=1 to n do p[j]:=j;//每次初始成每个点都没相连，即这个点所在的集合根为自己
   cnt:=n;//判断有没有全部连上
   for j:=i to m do//求出最大边
   begin
    x:=find(u[j]);//寻找该边起点的所在集合的根
    y:=find(v[j]);//寻找该边终点的所在集合的根
    if x<>y then//判断有没有联通
    begin
     dec(cnt);//如果没联通，就把他们联通
     p[x]:=y;//两个集合合并成一个集合
    end;
    if cnt=1 then//当cnt=1时，即所有点都联通时
    begin
     f:=true;//更改为有解
     if w[j]-w[i]<sum then//判断这个解是否比之前解小
      sum:=w[j]-w[i];//更新解
     break;//已找到最大值，跳出循环
    end;
   end;
  end;
  if f then writeln(sum) else writeln(-1);
  end;
  read(n,m);
 end;


end.
```

---

