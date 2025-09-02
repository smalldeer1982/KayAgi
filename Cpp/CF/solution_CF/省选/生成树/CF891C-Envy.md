# Envy

## 题目描述

For a connected undirected weighted graph $ G $ , MST (minimum spanning tree) is a subgraph of $ G $ that contains all of $ G $ 's vertices, is a tree, and sum of its edges is minimum possible.

You are given a graph $ G $ . If you run a MST algorithm on graph it would give you only one MST and it causes other edges to become jealous. You are given some queries, each query contains a set of edges of graph $ G $ , and you should determine whether there is a MST containing all these edges or not.

## 说明/提示

This is the graph of sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF891C/d7f37868e211da76f9c523f75a033c3f4d56f21c.png)Weight of minimum spanning tree on this graph is $ 6 $ .

MST with edges $ (1,3,4,6) $ , contains all of edges from the first query, so answer on the first query is "YES".

Edges from the second query form a cycle of length $ 3 $ , so there is no spanning tree including these three edges. Thus, answer is "NO".

## 样例 #1

### 输入

```
5 7
1 2 2
1 3 2
2 3 1
2 4 1
3 4 1
3 5 2
4 5 2
4
2 3 4
3 3 4 5
2 1 7
2 1 2
```

### 输出

```
YES
NO
YES
NO
```

# 题解

## 作者：wuzhaoxin (赞：38)

# Kruskal + 并查集

关于同一张图上的最小生成树，有一些性质：

- 对于任意权值的边，所有最小生成树中这个权值的边的数量是一定的
- 对于任意正确加边方案，加完小于某权值的所有边后图的连通性是一样的

据以上性质，判断某些边是否能够在同一最小生成树中同时出现时，不同权值的边之间不互相影响。

所以我们可以对于每一条边用Kruskal预处理出加完小于这条边的权值后的所有边后，这条边的两个端点所在的连通块，然后对于每个询问，每种权值分开考虑，看这些边连接的连通块是否构成环（注意不要漏掉自环），这里可以直接并查集

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int gi() {
	register int x; register char c, op = 0;
	while(c = getchar(), c < '0' || c > '9') if(c == '-') op = !op;
	x = c ^ 48;
	while(c = getchar(), c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48);
	return op ? -x : x;
}
int fa[500001];
int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void merge(int x, int y) {
	fa[find(x)] = find(y);
}
struct edge {
	int x, y, val, id;
	int tx, ty;
	bool operator < (const edge a)const {
		return val < a.val;
	}
} e[500001];
int n, m;
bool cmp(const edge x, const edge y) {
	return x.id < y.id;
}
int main() {
	n = gi(), m = gi();
	for(int i = 1; i <= n; i ++) fa[i] = i;
	for(int i = 1; i <= m; i ++) e[i].x = gi(), e[i].y = gi(), e[i].val = gi(), e[i].id = i;
	sort(e + 1, e + m + 1);
	e[0].val = -1;
	for(int i = 1; i <= m;) {
		int j = i;
		do {
			e[j].tx = find(e[j].x);
			e[j].ty = find(e[j].y);
			j ++;
		} while(j <= m && e[j].val == e[j - 1].val);
		while(i < j) {
			while(find(e[i].x) == find(e[i].y) && i < j) i ++;
			if(i < j) merge(e[i].x, e[i].y);
		} 
	}
	int q = gi();
	sort(e + 1, e + m + 1, cmp);
	for(int i = 1; i <= n; i ++) fa[i] = i;
	while(q --) {
		int k = gi();
		vector<edge>v;
		for(int i = 1; i <= k; i ++) {
			int a = gi();
			v.push_back({e[a].tx, e[a].ty, e[a].val});
		}
		sort(v.begin(), v.end());
		bool flag = 1;
		for(int i = 0, sz = v.size() - 1; i <= sz && flag;) {
			if(v[i].x == v[i].y) { flag = 0; break;}
			merge(v[i].x, v[i].y);
			int j = i + 1;
			while(j <= sz && v[j].val == v[i].val) {
				if(find(v[j].x) == find(v[j].y)) { flag = 0; break;}
				merge(v[j].x, v[j].y), j ++;
			}
			while(i < j) fa[v[i].x] = v[i].x, fa[v[i].y] = v[i].y, i ++;
		}
		puts(flag ? "YES" : "NO");
	}
	return 0;
}
```



---

## 作者：tommymio (赞：25)

题解区对于 $\text{MST}$ 性质的描述，有些奇怪。

以至于：
![](https://cdn.luogu.com.cn/upload/image_hosting/vmcvm8rm.png)

咳咳，稍微打个岔（

**这题确实是个性质题**。
我们先考虑只有一组询问的情况。将这组询问中的边按边权排序。对于当前的 $w_i$ ，确保 $< w_i$ 边权的边已被加入 $\text{Kruskal}$ 的贡献中，再尝试加入当前的 $w_i$。如果询问中有多个与 $w_i$ 边权相同的边则全部试图加入，若其中一条无法加入则说明不可行。

这样为什么是对的呢？**对于所有的最小生成树，其中每种权值的边的数量是一定的**。如果我们加入了 $<w_i$ 的所有边（**因为这些边中的一些边不加入进最小生成树只会得到更劣解**）而使边权与 $w_i$ 相同的边无法加入，则说明这条边不在最小生成树上。同样的，如果我们将询问中边权相同的边加入，其中有边无法加入，则说明他们无法同时存在于一棵最小生成树上。

于是我们发现，**对于一组询问中，不同边权之间其实并不存在影响**。因为对于询问中的任意两条边 $w_i,w_j$ ，不妨设 $w_i$ 的边权 $<$ $w_j$ 的边权，那么所有 $<w_j$ 边权的边（包括 $w_i$）在此前都已被加入进 $\text{Kruskal}$ 的贡献中。

根据上述结论，我们将每组询问拆成若干组边权相同的询问。对于每组边权相同的询问分别处理，然后统计其对每组询问的贡献。具体来说就是将每组边权相同的询问按询问中的边权排序，按只存在一次询问的做法处理这些询问，需要用上一些常规的离线技巧（

值得注意的是，加入一组询问中边权相同的边后需要撤回这组边，因为可能会对后续询问产生影响。这需要我们使用一个支持 **撤销上一次操作的并查集**：用按秩合并实现能够保留树的结构，用栈记录修改信息，暴力修改，查询，撤销即可。

不知道啥是可撤销并查集的可以去我 [$\text{Blog}$](https://www.cnblogs.com/tommy0103/p/13749379.html) 看看，~~不过都来做这题了应该不会不知道吧~~（

代码写的非常生草，随便看看就好，嘤嘤嘤（

**Show the Code**

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
int top=0;
std::vector<int> ask[500005];
int x[500005],y[500005],z[500005],fa[500005],size[500005],tmp[500005],res[500005];
struct edge {int x,y,val;} e[500005]; 
struct state {int x,y,fx,fy;} st[500005];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline void swap(int &x,int &y) {int tmp=y;y=x;x=tmp;}
inline bool cmp1(const edge &x,const edge &y) {return x.val<y.val;}
inline bool cmp2(const int &x,const int &y) {return z[x]<z[y];}
inline bool cmp3(const std::vector<int> &x,const std::vector<int> &y) {return z[x[1]]<z[y[1]];}
inline int find(int x) {while(x!=fa[x]) x=fa[x]; return x;}
inline void merge(int x,int y) {
	int fx=find(x),fy=find(y);
	if(fx!=fy) {
		if(size[fx]>size[fy]) swap(fx,fy);
		st[++top]=(state){x,y,fx,fy};
		size[fy]+=size[fx]; fa[fx]=fy;
	} 
}
int main() {
	int n=read(),m=read(),num=0,cur=1,Q=0;
	for(register int i=1;i<=n;++i) {fa[i]=i;size[i]=1;}
	for(register int i=1;i<=m;++i) {
		x[i]=read();y[i]=read();z[i]=read();
		e[i].x=x[i];e[i].y=y[i];e[i].val=z[i];
	}
	std::sort(e+1,e+1+m,cmp1); Q=read();
	for(register int t=1;t<=Q;++t) {
		int len=read(); res[t]=1;
		for(register int i=1;i<=len;++i) tmp[i]=read();
		std::sort(tmp+1,tmp+1+len,cmp2);
		for(register int i=1;i<=len;++i) {
			if(z[tmp[i]]!=z[tmp[i-1]]) ask[++num].push_back(t);
			ask[num].push_back(tmp[i]);
		}
	}
	std::sort(ask+1,ask+1+num,cmp3);
	for(register int i=1;i<=num;++i) {
		int flag=1;
		while(cur<=m&&e[cur].val<z[ask[i][1]]) {merge(e[cur].x,e[cur].y); ++cur;}
		for(register int j=1;j<ask[i].size();++j) {int id=ask[i][j]; if(find(x[id])==find(y[id])) {flag=0;} else {merge(x[id],y[id]);}}
		for(register int j=ask[i].size()-1;j>=1;--j) {
			int id=ask[i][j]; while(top>0&&st[top].x==x[id]&&st[top].y==y[id]) {fa[st[top].fx]=st[top].fx;size[st[top].fy]-=size[st[top].fx];--top;}
		} 
		res[ask[i][0]]&=flag;
	}
	for(register int t=1;t<=Q;++t) printf("%s\n",res[t]? "YES":"NO");
	return 0;
}
```

---

## 作者：GKxx (赞：12)

%前面的虚树大佬

然而其实这题并不需要虚树，只要一个并查集就好了

实际上还是考了并查集kruskal算法

考虑如果只有一组询问：假设这组询问的所有边的边权从小到大排序并去重之后是$w_1,w_2,w_3,...,w_k$。我们按边权从小到大来考虑，假设现在正在考虑的边权是$w_i$，首先用原图中所有边权小于$w_i$的边建出一个森林；然后将询问中边权为$w_i$的边依次尝试加入森林，在加入的过程中如果发现某条边加进去会成环（这个可以用并查集判断），就说明这组询问不行；然后接着看下一个边权即可。

如果有多组询问：可以把询问离线下来，对于每个边权$w_i$，依次去检查每个询问里边权为$w_i$的边即可。注意，检查完某个询问之后要将由这个询问在并查集上引起的改动全部撤销，所以我们需要一个可撤销的并查集，就不能路径压缩而应该按秩合并/启发式合并。

具体看代码

```cpp
#include <cctype>
#include <cstdio>
#include <climits>
#include <algorithm>
#include <vector>
#include <utility>

#define rep(I, A, B) for (int I = (A); I <= (B); ++I)
#define dwn(I, A, B) for (int I = (A); I >= (B); --I)
#define erp(I, X) for (int I = head[X]; I; I = next[I])

template <typename T> inline void read(T& t) {
    int f = 0, c = getchar(); t = 0;
    while (!isdigit(c)) f |= c == '-', c = getchar();
    while (isdigit(c)) t = t * 10 + c - 48, c = getchar();
    if (f) t = -t;
}
template <typename T, typename... Args>
inline void read(T& t, Args&... args) {
    read(t); read(args...); 
}
template <typename T> void write(T x) {
    if (x < 0) x = -x, putchar('-');
    if (x > 9) write(x / 10);
    putchar(x % 10 + 48);
}
template <typename T> void writeln(T x) {
    write(x);
    puts("");
}
template <typename T> inline bool chkMin(T& x, const T& y) { return y < x ? (x = y, true) : false; }
template <typename T> inline bool chkMax(T& x, const T& y) { return x < y ? (x = y, true) : false; }

const int maxn = 5e5 + 207;
struct Edge {
    int from, to, weight;
};
Edge e[maxn];
struct Query_edge {
    int id, from, to, weight;
    Query_edge(int i, int u, int v, int w)
        : id(i), from(u), to(v), weight(w) {}
    Query_edge() : id(0), from(0), to(0), weight(0) {}
};
std::vector<Query_edge> qe[maxn];
int fa[maxn], size[maxn];
int ans[maxn];
int n, m, q, mv;

int stk[maxn], top;

inline int findf(int x) {
    while (fa[x] != x) x = fa[x];
    return x;
}
inline bool merge(int x, int y) {
    int fx = findf(x), fy = findf(y);
    if (fx == fy) return 0;
    if (size[fx] > size[fy]) std::swap(fx, fy);
    fa[fx] = fy;
    size[fy] += size[fx];
    stk[++top] = fx;
    return true;
}

int main() {
    read(n, m);
    rep(i, 1, m) {
        read(e[i].from, e[i].to, e[i].weight);
        chkMax(mv, e[i].weight);
    }
    read(q);
    rep(i, 1, q) {
        int k; read(k);
        rep(j, 1, k) {
            int x; read(x);
            qe[e[x].weight].emplace_back(i, e[x].from, e[x].to, e[x].weight);
        }
    }
    std::sort(e + 1, e + m + 1, [](const Edge &lhs, const Edge &rhs) -> bool { return lhs.weight < rhs.weight; });
    rep(i, 1, n) fa[i] = i, size[i] = 1;
    rep(i, 1, q) ans[i] = 1;
    rep(i, 1, m) {
        int val = e[i].weight;
        top = 0;
        // 依次检查边权为val的每一条询问中涉及的边
        for (unsigned j = 0; j < qe[val].size(); ++j) {
            if (!ans[qe[val][j].id]) continue;
            if (j > 0 && qe[val][j].id != qe[val][j - 1].id) {
                // 说明进入了新的一组询问，要撤销上一组询问的影响
                while (top) {
                    int x = stk[top--];
                    size[fa[x]] -= size[x];
                    fa[x] = x;
                }
            }
            if (!merge(qe[val][j].from, qe[val][j].to))
                ans[qe[val][j].id] = 0;
        }
        // 边权为val的询问边全部检查完毕，将原图中的所有边权为val的边加入并查集
        while (e[i].weight == val) {
            merge(e[i].from, e[i].to);
            ++i;
        }
        if (e[i].weight != val) --i;
    }
    rep(i, 1, q) puts(ans[i] ? "YES" : "NO");
    return 0;
}
```

如果你比较懒，不想写这个带撤销的并查集，LCT当然也是可以的！QAQ

---

## 作者：Maxwei_wzj (赞：7)

居然没看题解想出来了这道神题，非常开心。

首先，判断$k$条边是不是能同时在最小生成树中，实际上只要求出包含这些边的边权和最小的生成树的权值，再和最小生成树比对即可。

怎么求呢？首先把$k$条边先连上，形成一些连通块，注意到一个性质：要连通两个连通块，使用最小生成树上的边一定是最优的。证明可以用反证法，如果用的不是最小生成树上的边而且更优，那么这个“最小生成树”就不是最小的。这时我们想到先用并查集维护连通性，然后再暴力做一次最小生成树。这样算出的结果肯定是对的，但时间复杂度爆炸，因此我们需要优化。

注意到已经和其他点连通的点至多有$2k$个，我们想到使用虚树。这时我们发现，虚树外的那些最小生成树的边是一定要连的，不然就不连通，因此我们只需考虑虚树内的连通性。虚树上一条边就代表原图中的一条路径，且这些路径上的点都没有和其它点连通。我们尝试把这条路径缩成一条边。首先，路径内的点要连通，那么肯定是从路径的两端连树边，直到中间还有一条边没连上为止。这时，如果我们要求路径的两端不连通，那么我们就贪心地选择最大的边割掉即可，这条最大边显然可以通过倍增找到。于是要求路径两端连通就相当于在不连通的基础上，连通了那条最大的边，因此我们发现只有这条最大的边和这条路径的最优解有关，这样我们就把一条路径缩成了一条边。于是虚树中就只有$O(k)$条边了，这时候再做最小生成树，时间复杂度就是$O(k\log k)$，因此总的复杂度为$O(\sum k\log \sum k)$，可以接受。

**代码：**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m,q,first[500010]={0},tot=0,totke,pos[500010],tim=0;
int ma[500010],mb[500010],pre[500010][21]={0},dep[500010]={0};
int p[2000010],totp,pe[500010],tote,fa[500010];
int st[500010],top;
ll mw[500010],mx[500010][21]={0},dis[500010]={0};
struct kruskaledge
{
	int a,b;
	ll w;
}me[500010];
struct treeedge
{
	int v,next;
	ll w;
}e[1000010];

bool cmp(kruskaledge a,kruskaledge b)
{
	return a.w<b.w;
}

void insert(int a,int b,ll w)
{
	e[++tot].v=b;
	e[tot].next=first[a];
	e[tot].w=w;
	first[a]=tot;
}

int find(int x)
{
	int r=x,i=x,j;
	while(r!=fa[r]) r=fa[r];
	while(i!=r) j=fa[i],fa[i]=r,i=j;
	return r;
}

void merge(int x,int y)
{
	int fx=find(x),fy=find(y);
	fa[fx]=fy;
}

ll kruskal(ll init,bool type)
{
	ll tot=init;
	sort(me+1,me+totke+1,cmp);
	for(int i=1;i<=totke;i++)
		if (find(me[i].a)!=find(me[i].b))
		{
			tot+=me[i].w;
			merge(me[i].a,me[i].b);
			if (type)
			{
				insert(me[i].a,me[i].b,me[i].w);
				insert(me[i].b,me[i].a,me[i].w);
			}
		}
	return tot;
}

void dfs(int v)
{
	pos[v]=++tim;
	for(int i=first[v];i;i=e[i].next)
		if (e[i].v!=pre[v][0])
		{
			pre[e[i].v][0]=v;
			dep[e[i].v]=dep[v]+1;
			mx[e[i].v][0]=e[i].w;
			dis[e[i].v]=dis[v]+e[i].w;
			dfs(e[i].v);
		}
}

bool cmpp(int a,int b)
{
	return pos[a]<pos[b];
}

int lca(int a,int b)
{
	if (dep[a]<dep[b]) swap(a,b);
	for(int i=20;i>=0;i--)
		if (dep[pre[a][i]]>=dep[b])
			a=pre[a][i];
	if (a==b) return a;
	for(int i=20;i>=0;i--)
		if (pre[a][i]!=pre[b][i])
			a=pre[a][i],b=pre[b][i];
	return pre[a][0];
}

ll findmx(int a,int b)
{
	ll ans=0;
	for(int i=20;i>=0;i--)
		if (dep[pre[a][i]]>=dep[b])
		{
			ans=max(ans,mx[a][i]);
			a=pre[a][i];
		}
	return ans;
}

void solve()
{
	int newp=totp;
	sort(p+1,p+totp+1,cmpp);
	for(int i=1;i<totp;i++)
		p[++newp]=lca(p[i],p[i+1]);
	totp=newp;
	sort(p+1,p+totp+1,cmpp);
	newp=0;
	for(int i=1;i<=totp;i++)
		if (i==1||p[i]!=p[newp])
			p[++newp]=p[i];
	totp=newp;
	
	ll basis=0,bestval=0;
	for(int i=1;i<=totp;i++)
		fa[p[i]]=p[i];
	for(int i=1;i<=tote;i++)
	{
		if (find(ma[pe[i]])==find(mb[pe[i]]))
		{
			printf("NO\n");
			return;
		}
		merge(ma[pe[i]],mb[pe[i]]);
		basis+=mw[pe[i]];
	}
	
	top=0;
	totke=0;
	for(int i=1;i<=totp;i++)
	{
		while(top&&lca(st[top],p[i])!=st[top]) top--;
		st[++top]=p[i];
		if (top>1)
		{
			ll sum,mx;
			sum=dis[st[top]]-dis[st[top-1]];
			mx=findmx(st[top],st[top-1]);
			bestval+=sum;
			basis+=sum-mx;
			if (find(st[top])!=find(st[top-1]))
			{
				me[++totke].a=st[top];
				me[totke].b=st[top-1];
				me[totke].w=mx;
			}
		}
	}
	
	if (kruskal(basis,0)==bestval) printf("YES\n");
	else printf("NO\n");
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%lld",&ma[i],&mb[i],&mw[i]);
		me[i].a=ma[i],me[i].b=mb[i],me[i].w=mw[i];
	}
	
	totp=n;
	totke=m;
	for(int i=1;i<=totp;i++)
		fa[i]=i;
	kruskal(0,1);
	
	dep[1]=1;
	dfs(1);
	for(int i=1;i<=20;i++)
		for(int j=1;j<=n;j++)
		{
			pre[j][i]=pre[pre[j][i-1]][i-1];
			mx[j][i]=max(mx[j][i-1],mx[pre[j][i-1]][i-1]);
		}
	
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		scanf("%d",&tote);
		totp=0;
		for(int i=1;i<=tote;i++)
		{
			scanf("%d",&pe[i]);
			p[++totp]=ma[pe[i]],p[++totp]=mb[pe[i]];
		}
		solve();
	}
	
	return 0;
}
```

---

## 作者：CDFLS_mao_zx (赞：6)

## $\text{CF891C}$

### 废话：

感谢 [plate_let](https://www.luogu.com.cn/user/177524) 奆佬，在她的帮助下，对 $\text{MST}$ 的理解深入了不少。

### 思路：

首先，不同权值的边相互之间是不影响的，所以我们可以对每一个权值分开考虑，这个结论将在下文证明。然后，每次选完小于等于一个固定值的所有边后，图的连通性是固定的（当然，选定的边需要构成一颗 $\text{MST}$ ），这个结论也将在下面证明。

有了这两个结论，问题就变得简单起来了，我们对询问的所有边离线，按照权值和询问编号排序，其中权值为第一关键字。

跑 $\text{Kruscal}$ 枚举每种权值的边之前先考虑询问的边，看看询问的边加入和是否会成环，这里需要一个可撤销的并查集，因为不同询问间独立，需要排除上一个询问的影响。由于无论怎么选，连通性都是相同的，所以我们大可直接使用 $\text{Kruscal}$ 算法进行时的并查集。如果成环，那么这个询问的回答就是 $\text{NO}$。

我们接下来证明提出的两个结论。

结论 $\text{2}$（每次选完小于等于一个固定值的所有边后，图的连通性是固定的）：

假设现在考虑最小的权值 $x$ ，如果有两种不同的连通性 $G_1,G_2$ 那么找出其中的不同，我们假设这个不同是这样的形式：在 $G_1$ 中 $u,v$  联通，在 $G_2$ 中则不然，那么将 $G_2$ 中的边试图加入 $G_1$ 则一定可以找到一条满足条件的边加入，由于有新的边加入，所以还没有选完边，所以连通性相同。

将所有联通块缩成一个点，由数学归纳法，结论成立。

结论 $\text{1}$ （不同权值的边相互之间是不影响）

有了结论 $\text{2}$，它是显然的，因为选到固定权值后连通性相同，所以不同权值的边不会相互影响。

### 代码和细节：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<set>
#include<queue>
#include<cmath>
#include<string>
#include<cstring>
#include<ctime>
#include<vector>
#define next nxt
#define itn int
#define y1 y3647
#define LL long long
using namespace std;
inline void read(int &x)
{
	x=0;
	int f=1;
	char ch=getchar();
	while((ch<'0'||ch>'9')&&ch!='-')
	ch=getchar();
	if(ch=='-')
	{
		f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	x*=f;
}
int i,j,m,n,s,t,k[2];
const int N=1e6+10;
int fa[N],size[N],p[N],top;
struct fu{
	int v,val,rk,u;
}a[2][N];
struct opr{
	int fa,size,u,v;
}st[N];
void work(int aa,int bb,int cc,int op)
{
	a[op][++k[op]].v=bb;
	a[op][k[op]].val=cc;
	a[op][k[op]].rk=i;
	a[op][k[op]].u=aa;
}
int find(int x)
{
	return fa[x]==x?x:find(fa[x]);
}
void put(int u,int v,int c)
{
	if(size[u]>size[v])
	swap(u,v);
	if(c==1)
	{
		st[++top].u=u;
		st[top].fa=fa[u];
		st[top].v=v;
		st[top].size=size[v];
	}
	fa[u]=v;
	size[v]+=size[u];
}
void cancel()
{
	while(top)
	{
		fa[st[top].u]=st[top].fa;
		size[st[top].v]=st[top].size;
		top--;
	}
}
bool cmp(fu aa,fu bb)
{
	if(aa.val!=bb.val)
	return aa.val<bb.val;
	return aa.rk<bb.rk;
}
void kru()
{
	for(i=1;i<=n;i++)
	fa[i]=i,size[i]=1;
	int now=1;
	for(i=1;i<=m;i++)
	{
		while(a[1][now].val==a[0][i].val)
		{
			int start=now;
			while(a[1][now].rk==a[1][start].rk&&a[1][now].val==a[0][i].val)//一定记得判掉第二个条件
			//不然我保证你WA 48
            {
				int u=find(a[1][now].u),v=find(a[1][now].v);
				now++;
				if(u==v)
				{
					p[a[1][now-1].rk]=1;
					continue;
				}
				put(u,v,1);
			}
			cancel();
		}
		int u=find(a[0][i].u),v=find(a[0][i].v);
		if(u==v)
		continue;
		put(u,v,0);//这里不用撤销
	}
}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//freopen(".ans","w",stdout);
	int q;
	read(n),read(m);
	for(i=1;i<=m;i++)
	{
		int x,y,z;
		read(x),read(y),read(z);
		work(x,y,z,0);
	}
	read(q);
	int all=0;
	for(i=1;i<=q;i++)
	{
		read(s);
		for(j=1;j<=s;j++)
		{
			int x;
			read(x);
			work(a[0][x].u,a[0][x].v,a[0][x].val,1);
		}
		all+=s;
	}
	sort(a[0]+1,a[0]+m+1,cmp);
	sort(a[1]+1,a[1]+all+1,cmp);//对边排序
	kru();
	for(i=1;i<=q;i++)
	puts(p[i]?"NO":"YES");
	return 0;
}
```























---

## 作者：da32s1da (赞：6)

考虑lct做法。

先随便找一棵最小生成树出来，然后对于每个询问的边$(u,v,w)$，查找$u,v$之间的最大权值，如果小于$w$，那么是$NO$，否则把$(u,v,w)$这条边插入，并令边权为$-inf$(防止被替换)，最后恢复边权即可。

另：[lct是大常数做法，可能会T](https://www.luogu.org/recordnew/show/17604648)（见第26点）

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2e6+50;
int n,m,x,y,p,q,opt,qwq;
int b[N],c[N],zn[N],cnt;
inline void rad(int &_){
    static char ch;
    while(ch=getchar(),ch<'0'||ch>'9');_=ch-48;
    while(ch=getchar(),ch<='9'&&ch>='0')_=_*10+ch-48;
}
inline void swap(int &u,int &v){int o=u;u=v;v=o;}
struct node{
	int x,y,w,id;
}a[N];
struct lct{
	int ch[N][2],fa[N],tagrev[N],val[N],sum[N];
	bool isrot(int x){
		return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
	}
	void rev(int x){
		tagrev[x]^=1;
		swap(ch[x][0],ch[x][1]);
	}
	void update(int x){
		sum[x]=max({val[x],sum[ch[x][0]],sum[ch[x][1]]});
	}
	void rotate(int x){
		int y=fa[x],z=fa[y],opt=(ch[y][1]==x),w=ch[x][opt^1];
		if(!isrot(y))ch[z][ch[z][1]==y]=x;fa[x]=z;
		ch[y][opt]=w;fa[w]=y;
		ch[x][opt^1]=y;fa[y]=x;
		update(y);update(x);
	}
	void splay(int x){
		int y,z;
		for(y=x,zn[++cnt]=x;!isrot(y);y=fa[y],zn[++cnt]=y);
		for(;cnt;--cnt){
			if(zn[cnt]&&tagrev[zn[cnt]])
			tagrev[zn[cnt]]=0,rev(ch[zn[cnt]][0]),rev(ch[zn[cnt]][1]);
		}
		while(!isrot(x)){
			y=fa[x];z=fa[y];
			if(!isrot(y))
			rotate(((ch[y][0]==x)^(ch[z][0]==y))?x:y);
			rotate(x);
		}
	}
	void access(int x){
		for(int y=0;x;y=x,x=fa[x])
		splay(x),ch[x][1]=y,update(x);
	}
	void mktrot(int x){
		access(x);splay(x);rev(x);
	}
	void mkvrot(int x){
		access(x);splay(x);
	}
	void cut(int x,int y){
		mktrot(x);mkvrot(y);
		ch[y][0]=fa[x]=0;
		update(y);
	}
	void link(int x,int y){
		mktrot(x);mkvrot(y);
		fa[x]=y;
	}
	int query(int x,int y){
		mktrot(x);mkvrot(y);
		while(y&&(sum[ch[y][0]]==sum[y]||sum[ch[y][1]]==sum[y]))
		if(sum[ch[y][0]]==sum[y])y=ch[y][0];
		else y=ch[y][1];
		return y>n?y:n;
	}
}s;
int Fa[N];
int find(int x){return x==Fa[x]?x:Fa[x]=find(Fa[x]);}
int main(){
	rad(n);rad(m);
	for(int i=1;i<=m;i++){
		rad(a[i].x);rad(a[i].y);rad(a[i].w);
		a[i].id=n+i;
		s.val[n+i]=s.sum[n+i]=a[i].w;
	}
	for(int i=1;i<=n;i++)Fa[i]=i;
	for(int i=1;i<=m;i++){
		x=find(a[i].x);y=find(a[i].y);
		if(x==y){
			x=s.query(a[i].x,a[i].y)-n;
			if(a[x].w<=a[i].w)continue;
			s.cut(a[x].x,a[x].id);
			s.cut(a[x].id,a[x].y);
			s.link(a[i].x,a[i].id);
			s.link(a[i].id,a[i].y);
		}else Fa[x]=y,s.link(a[i].x,a[i].id),s.link(a[i].id,a[i].y);
	}
	a[0].w=-1;
	for(rad(q);q;q--){
		rad(p);opt=1;qwq=0;
		for(int i=1;i<=p;i++){
			rad(b[i]);
			if(opt){
				x=s.query(a[b[i]].x,a[b[i]].y)-n;
				if(a[x].w<a[b[i]].w){opt=0;continue;}
				c[++qwq]=s.val[a[b[i]].id];
				if(x!=b[i]){
					s.cut(a[x].x,a[x].id);
					s.cut(a[x].id,a[x].y);
					s.val[a[b[i]].id]=0;
					s.link(a[b[i]].x,a[b[i]].id);
					s.link(a[b[i]].id,a[b[i]].y);
				}else s.val[a[b[i]].id]=0,s.splay(a[b[i]].id);
			}
		}
		puts(opt?"YES":"NO");
		for(int i=1;i<=qwq;i++)s.val[a[b[i]].id]=c[i],s.splay(a[b[i]].id);
	}
}
```

---

## 作者：Y_B_X (赞：3)

[题目链接](https://www.luogu.com.cn/problem/CF891C)

题意：给定一张无向连通图，每次给出一些边，询问这些边能否同时在一个最小生成树中出现。

这是一个没太大思维难度的 $\text{LCT}$ 做法，有点卡常。

先建出任意一个最小生成树，对树上与非树上的边讨论。

首先，如果询问的边会构成一个环，那就完全不可能在同一最小生成树中。

其次，考虑一条非树边 $(x,y,w)$ 什么时候能替换一条在原先最小生成树上的边。

那就必须满足 $x,y$ 两个点在原先最小生成树路径上的边的**最大值** $\geq w$，不然不可行。

那这时候这条边就能将这条边权最大的边替换掉。

但如果这条边权最大的边被要求了必须出现，就需要另外的边去替换。

由于有动态的替换与求路径最大值，可以考虑 $\text{LCT}$ **化边为点**实现。

先将询问中**在原最小生成树上的边**的权值设为 $0$ 保证不会被替换。

再对**非树边**查路径最大值看能否替换，并记录下被替换过的边，在最终要复原回去。

这样的时间复杂度是 $O(n\log n)$ 的（默认 $n,m$ 同阶）。

但由于 $\text{LCT}$ 的巨大常数，且为了查路径最值的化边为点，点数已去到 $1e6$ 级别。

所以这种方法会有点卡常，但个人实现上所有数据都能在 $1s$ 内跑完：[记录详情](https://www.luogu.com.cn/record/60301701)。

最终代码：

```cpp
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n,m,q,x,y,v,k,ax,ay,tot;bool flag,bb[N];
int w[N],ww[N],xx[N],yy[N],a[N],f[N],id[N];
inline int getf(int x){while(x^f[x])x=f[x]=f[f[x]];return x;}
struct pre_state{int x,y;}ps[N<<1];
namespace FastIO
{//此处省略带缓存的 FastIO
}
using namespace FastIO;
struct lct{
	int mxid[N],son[N][2],tmpid,anc[N],rev[N],i,y,_y,_x,_id,rx,ry,mxy;bool b;
	inline bool nroot(int x){return son[anc[x]][0]==x||son[anc[x]][1]==x;}
	inline bool p(int x){return son[anc[x]][1]==x;}
	inline void rev_(int x){rev[x]^=1;son[x][0]^=son[x][1]^=son[x][0]^=son[x][1];}
	inline void fix(int x){
		mxid[x]=x;
		if(w[tmpid=mxid[son[x][0]]]>w[x])mxid[x]=tmpid;
		if(w[tmpid=mxid[son[x][1]]]>w[mxid[x]])mxid[x]=tmpid;
	}
	inline void pushdown(int x){
		if(rev[x]){if(son[x][0])rev_(son[x][0]);if(son[x][1])rev_(son[x][1]);rev[x]=0;}
	}
	void pushall(int x){if(nroot(x))pushall(anc[x]);pushdown(x);}
	inline void rotate(int x){
		y=anc[x];_x=anc[y];b=p(x);
		if(nroot(y))son[_x][p(y)]=x;
		anc[x]=_x;
		anc[son[y][b]=son[x][!b]]=y;
		anc[son[x][!b]=y]=x;
		fix(y);fix(x);fix(_x);
	}
	inline void splay(int x){
		pushall(x);for(;i=anc[x],nroot(x);rotate(x))if(nroot(i))rotate(p(x)==p(i)?i:x);
	}
	inline void access(int x){
		for(_y=0;x;_y=x,x=anc[x])splay(x),son[x][1]=_y,fix(x);
	}
	inline void makeroot(int x){access(x);splay(x);rev_(x);}
	inline void split(int x,int y){makeroot(x);access(y);splay(y);}
	inline void link(int x,int y){makeroot(x);anc[x]=y;}
	inline void cut(int x,int y){split(x,y);son[y][0]=anc[x]=0;fix(y);}
	inline void link(int x,int y,int id){
		split(x,y);mxy=mxid[y];
		if(w[mxy]>=w[id]){
			_id=mxy;
			cut(xx[_id],_id);cut(_id,yy[_id]);
			link(x,id);link(id,y);
			ps[++tot]=(pre_state){_id,id};
		}
		else flag=1;
	}
	inline void recover(){
		for(;tot;--tot){
			ry=ps[tot].y,rx=ps[tot].x;
			cut(xx[ry],ry);cut(yy[ry],ry);
			link(xx[rx],rx);link(yy[rx],rx);
		}
	}
}L;
bool cmp(int a,int b){return w[a]<w[b];}
main(){
	qin>>n>>m;register int i;
	for(i=1;i<=m;++i)qin>>xx[i]>>yy[i]>>w[i];
	for(i=1;i<=m;++i)xx[i]+=m,yy[i]+=m,ww[i]=w[i],id[i]=i;
	for(i=1;i<=n;++i)f[i]=i;
	sort(id+1,id+m+1,cmp);
	for(i=1;i<=m;++i){
		x=xx[id[i]]-m,y=yy[id[i]]-m;
		ax=getf(x),ay=getf(y);
		if(ax==ay)continue;
		f[ax]=ay;bb[id[i]]=1;
		L.link(x+m,id[i]);L.link(y+m,id[i]);
	}//老老实实打kruskal
	tot=0;qin>>q;
	for(i=1;i<=n;++i)f[i]=i;
	while(q--){
		qin>>k;flag=1;
		for(i=1;i<=k;++i)qin>>a[i],flag&=bb[a[i]];
		if(flag){puts("YES");continue;}//全部在原MST的边显然可行
		flag=0;
		for(i=1;i<=k;++i){
			ax=getf(xx[a[i]]-m);
			ay=getf(yy[a[i]]-m);
			if(ax==ay)flag=1;
			else f[ax]=ay;
		}//并查集判环
		for(i=1;i<=k;++i)x=xx[a[i]]-m,f[x]=x,y=yy[a[i]]-m,f[y]=y;
		if(flag){puts("NO");continue;}
		for(i=1;i<=k;++i)if(bb[a[i]])w[a[i]]=0,L.splay(a[i]);
		for(i=1;i<=k;++i)if(!bb[a[i]]){
			L.link(xx[a[i]],yy[a[i]],a[i]);
			if(flag)break;
		}
		for(i=1;i<=k;++i)if(bb[a[i]])w[a[i]]=ww[a[i]],L.splay(a[i]);
		L.recover();//复原
		if(flag)puts("NO");
		else puts("YES");
	}
}
```


---

## 作者：Leap_Frog (赞：3)

### P.S.
![](https://cdn.luogu.com.cn/upload/image_hosting/rmtulew0.png)  
然后就来做这题了。  
一道 2300 写了我一个晚上，真是自闭自闭。  
白天想了一天，想了两个假做法，晚上从 9:00 写到 10:20。  
### Problem.
多次询问，查询几条边是否可能同时出现在最小生成树上。  
### Solution.
#### Fake Solution1.
根据环路性质，一棵树加上一条边，然后切掉这条边两个点路径上的任意一条边后，它仍然是树。  
所以我们随便找出一棵生成树，再用 LCT 维护链上最小值，每组询问直接暴力断边就好了。  
**Fake 原因：** 至少笔者不会用 LCT 支持链上断掉最小边。  
#### Fake Solution2.
对于每组询问，我们从小到大加边。  
然后对于当前加入的边我们优先取它，如果已经联通了就无解。  
**Fake 原因：** 严格小于当前需要判断边权的边无法处理。  
#### Real Solution.
根据 **Fake Solution2.**，正解已经呼之欲出了。  
首先，某组询问，肯定可以把它分开成互不干扰的不同询问。  
因为如果边权不同，那么肯定不会互相干扰，你肯定会先把所有小的边全部处理。  
所以我们直接对值域处理，询问离线。  
然后，我们只需要对每次询问，用一个 DSU 维护就好了。  

不过，与此同时，因为询问之间互相独立，所以我们只需要让这个 DSU 可撤销就结束了。  

### Coding.
代码应该还是挺清晰易懂的qwq
```cpp
//是啊……你就是那只鬼了……所以被你碰到以后，就轮到我变成鬼了
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<48||c>57;c=getchar()) if(!(c^45)) f=1;
	for(;c>=48&&c<=57;c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	f?x=-x:0;
}
int n,m,Q,fa[500005],de[500005],nid[500005],a[500005];char rs[500005];
struct edge{int x,y,w,id;char tg;}e[500005];int ut,tn[500005];
struct node{int id;vector<int>v;};vector<node>q[500005];
struct dsub{int x,y,de;}st[500005];int tp;
inline char cmp(edge a,edge b) {return a.w<b.w;}
inline char cpp(int a,int b) {return e[a].w<e[b].w;}
inline int getf(int x) {return fa[x]==x?x:getf(fa[x]);}
inline void mrg(int x,int y)
{
	x=getf(x),y=getf(y);if(x==y) return;else if(de[x]>de[y]) swap(x,y);
	st[++tp]=(dsub){x,y,de[y]},fa[x]=y,de[y]+=de[x]==de[y];
}
inline void pop() {fa[st[tp].x]=st[tp].x,de[st[tp].y]=st[tp].de,tp--;}
int main()
{
	read(n),read(m);for(int i=1;i<=m;i++) read(e[i].x),read(e[i].y),read(e[i].w),e[i].id=i;
	read(Q),sort(e+1,e+m+1,cmp);for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=m;i++) nid[e[i].id]=i,tn[++ut]=e[i].w;
	sort(tn+1,tn+ut+1),ut=unique(tn+1,tn+ut+1)-tn-1;
	for(int i=1;i<=m;i++) e[i].w=lower_bound(tn+1,tn+ut+1,e[i].w)-tn;
	for(int K,xtw=1;xtw<=Q;xtw++)
	{
		read(K);for(int i=1;i<=K;i++) read(a[i]),a[i]=nid[a[i]];
		vector<int>v;sort(a+1,a+K+1,cpp);
		//for(int i=1;i<=n;i++) printf("%d%c",a[i],i==n?'\n':' ');
		for(int l=1,r=l;l<=K;l=++r)
		{
			while(e[a[l]].w==e[a[r+1]].w) r++;
			vector<int>v;for(int i=l;i<=r&&i<=K;i++) v.push_back(a[i]);
			q[e[a[l]].w].push_back((node){xtw,v});
		}
	}
	//puts("------------");for(int i=1;i<=m;i++) printf("%d %d %d\n",e[i].x,e[i].y,e[i].w);
	for(int i=1,j=1;j<=ut;j++)
	{
		//printf("nwj : %d\n",j);
		//for(int i=1;i<=n;i++) printf("%d%c",getf(i),i==n?'\n':' ');
		int qwq=tp;for(auto &nw:q[j])
		{
			for(auto &x:nw.v) if(getf(e[x].x)==getf(e[x].y)) rs[nw.id]=1;else mrg(e[x].x,e[x].y);
			//printf("%d : ",nw.id);{for(auto x:nw.v) printf("%d ",x);}putchar('\n');
			while(tp>qwq) pop();
		}
		for(;e[i].w==j;i++) if(getf(e[i].x)!=getf(e[i].y)) mrg(e[i].x,e[i].y);
	}
	for(int i=1;i<=Q;i++) if(rs[i]) puts("NO");else puts("YES");
	return 0;
}
```

---

## 作者：ZCETHAN (赞：3)

[CF891C Envy](http://codeforces.com/problemset/problem/891/C)
# 题目大意
>给出一个$n$个点$m$条边的无向图，每条边有边权，共$Q$次询问，每次给出$k_i$条边，问这些边能否同时在一棵最小生成树上。

# Solution
首先明确两件事：

- 连通图中所有最小生成树中，所有权值的边的数量都是相等的。
- 各权值的边之间是无影响的。

分别说明：对于第一点，显然，由于用$Kruskal$求出来的结果一定是最优的，如果某一权值的边少了，势必会多出一条权值更大的边，如果多了，那么势必会导致后面的边会无法加入，最终导致答案更劣。

对于第二点，我们考虑每一条边是否能加入生成树中，当权值小于当前边的边都处理过后，整张图会变成一个森林，并且各个连通块之间是没有权值小于当前边的(~~这不是显然吗~~)，所以，当处理到当前的边时，如果当前边不能加入，是不可能通过改变之前的连接方式，使得方案仍然合法并且当前边能够加入生成树。换言之，之前所有权值的边的连接方式和当前边能否加入生成树是没有关系的，所以各权值的边之间是无影响的。

---
明确上述两点之后，就可以思考这题。首先我们一定可以将边按权值进行分类，每次都处理同一权值的边。根据上述的性质，如果能知道每次询问的边的权值时，并查集的状态，就可以方便地判断这条边是否能在生成树中。但是现在棘手的问题就是如何维护这个做到一半的并查集。

其实很简单，可以先预处理出连接完**小于**某个权值的边时，这个权值的边所连接的连通块的编号，根据性质二，这个编号是唯一的(除非是并查集合并时产生的差异，但是所指的连通块时同一个)。然后拿一个**崭新**的并查集去维护每个权值，在处理完一个权值后就还原**改变过**的并查集就可以了。

两个注意点：
由于要连接小于某一权值的边，所以在$Kruskal$的时候必须要先存下同一权值的边，然后在预处理完所需要的东西之后(~~至于什么东西，懂得都懂~~)，才能将边加入生成树。

同时注意，为什么不能用朴素的并查集，但是这样精准的复原就可以。因为题目中给出询问个数是$5\times10^5$，显然，如果每次都是$O(n)$的话，想不$T$都难。但是有这么一句话
>It is guaranteed that the sum of $k_{i}$  for $1<=i<=q$ does not exceed $5·10^{5}$.

这就显然，只要每次是$O(k)$，总的复杂度是不会超出$O(n)$的，可以通过。

---
综上，我们总结出一个可行的方案：
首先用$Kruskal$来预处理出，小于当前边权的所有边都处理后，当前边所连接的连通块编号。
然后处理询问，对于每个询问，都先对边排序，然后对于同一边权的边，判断是否可以加入生成树中，利用预处理出的编号即可。
如果有边无法加入，即形成了环(用并查集判断即可)，那么就是不合法的。
最后复原并查集即可。

# Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf 1ll<<60
using namespace std;
const int MAXN=5e5+10;
struct node{
	int u,v,w,id;
	void input(){
		scanf("%d%d%d",&u,&v,&w);
	}
	bool friend operator<(node a,node b){
		return a.w<b.w;
	}
}e[MAXN];
bool cmp(node x,node y){return x.id<y.id;}
int f[MAXN],conx[MAXN],cony[MAXN];
vector<node> cur;
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
int main()
{
	int n,m,q;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		e[i].input();
		e[i].id=i;
	}
	for(int i=1;i<=n;i++) f[i]=i;
	sort(e+1,e+1+m);
	int pre=e[1].w,lst=1;
	for(int i=1;i<=m;i++){
		if(e[i].w==pre) continue;//如果和上一次的权值相等，那么先存着
		else{
			for(int j=lst;j<i;j++){
				int fu=find(e[j].u),fv=find(e[j].v);
				conx[e[j].id]=fu;cony[e[j].id]=fv;//否则先处理连接的连通块
			}
			for(int j=lst;j<i;j++){
				int fu=find(e[j].u),fv=find(e[j].v);
				if(fu!=fv) f[fu]=fv;//然后加入生成树
			}
			pre=e[i].w;lst=i;
		}
	}
	for(int j=lst;j<=m;j++){
		int fu=find(e[j].u),fv=find(e[j].v);
		conx[e[j].id]=fu;cony[e[j].id]=fv;
	}
	for(int j=lst;j<=m;j++){
		int fu=find(e[j].u),fv=find(e[j].v);
		if(fu!=fv) f[fu]=fv;
	}
	sort(e+1,e+1+m,cmp);
	scanf("%d",&q);
	for(int i=1;i<=n;i++) f[i]=i;
	while(q--){
		int k,id;
		scanf("%d",&k);
		cur.clear();
		for(int i=1;i<=k;i++){
			scanf("%d",&id);
			cur.push_back(e[id]);
		}
		sort(cur.begin(),cur.end());
		bool fl=1;
		for(int i=0;i<cur.size()&&fl;){
			int u=conx[cur[i].id],v=cony[cur[i].id],j=i+1;
			if(u==v){fl=0;break;}
			f[u]=v;
			for(j=i+1;j<cur.size()&&cur[j].w==cur[i].w;j++){//把同权值的边进行处理
				u=find(conx[cur[j].id]),v=find(cony[cur[j].id]);
				if(u==v){fl=0;break;}//成环就退出
				f[u]=v;
			}
			while(i<j)
				f[conx[cur[i].id]]=conx[cur[i].id],
				f[cony[cur[i].id]]=cony[cur[i].id],i++;//复原并查集
		}
		if(fl) puts("YES");
		else puts("NO");
	}
}
```

---

## 作者：Yuby (赞：2)

[题面](https://www.luogu.com.cn/problem/CF891C)

点数：2300

upd 2022.08.03：修正了一处笔误。

#### 前置知识

最小生成树（kruskal）

#### 题目分析

很明显的最小生成树。

注意到题目中的 $n,m,q,\sum k_i\leq 5\times10^5$，对于所有查询需要用 $O(k\log n)$ 或者 $O(k\log k)$ 左右的复杂度完成。

首先，选出的一些边不是最小生成树的话有两种可能性：

1.权值不是最小

2.图不连通或者有环

考虑暴力怎么处理，也就是 $O(q(m+k)\log n)$ 的算法。我们可以把这 $k$ 条边直接加到一个并查集，然后直接跑最小生成树判断是否有环即可。

考虑优化这个方法。

不难发现我们每次会重复考虑每一条边，如果只考虑每次查询的边的话直接就是 $O(k\log n)$ 的。

##### 引入最小生成树的两个性质：

（默认按照 kruskal 的加边方式且读者了解其正确性）

一、对于任意正确加边方案，加完小于某权值 $w$ 的所有边后图的连通性是一样的。证明如下：

​	如果图的连通性改变，必然存在一个点 $u$ 不在第一个加边方案，而在第二个加边方案上。此时必然存在一个点 $v$ 已经加入第一个加边方案，且存在边 $(u,v)$ 使得 $w(u,v)<w$，否则两图不同。那么	这个点必然应该在第一个方案的最小生成树上，与其正确性不符。故成立。

二、对于任意权值的边，所有最小生成树中这个权值的边的数量是一定的。证明如下：

​	设存在两颗最小生成树，边按编号分别为两个集合 $s1,s2$。如果结论不成立则有边 $i\in s1$ 且 $i\notin s2$ 并且有边 $j\notin s1,j\in s2$，不妨设 $w(i)<w(j)$。那么在加入 $j$ 这一条边时必然已经考虑过 $i$ 这条边，由性质一可得 $i$ 这条边加入最小生成树中是因为这条边的两端是两个连通块，那么在第二颗最小生成树中必然也包含这条边。矛盾。故成立。

结合上面两个性质，不难发现可以把每个边权 $w$ 分开思考。唯一要处理的是在加入一条权值为 $w$ 的边时，如何 $O(\log n)$ 得到加入了所有权值小于 $w$ 的边后的图的连通状态。

在查询前，我们先跑一遍最小生成树，并把加入当前权值前的每条边两端的连通块编号记录。这里采用第一个加入该连通块的点作为它的编号，方便写代码。在查询时我们把每条边直接考虑为这两个的连通块之间的边，并把这条边加入看是否存在环即两端是否已经在同一连通块内。

至于权值最小由最小生成树的建树过程和性质一容易发现如果两端已经在同一连通块内就不可行，否则可行。

注意在重置并查集时应该只重置使用的部分，否则复杂度将退化为 $O(qn\log n)$，运用双指针解决重置问题。

总复杂度：$O(m\log m+\sum k_i(\log k_i+\log n))$，可以通过此题。


```cpp
#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a));
#define pc putchar
#define fast_iostream ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef double db;
const ld EPS=1e-8;
const ll INF=ll(1e9+7);
const ll LLINF=ll(1e18+7);
const ld LDEPS=1e-18;
inline ll max(ll x,ll y){return x>y?x:y;}
inline ll min(ll x,ll y){return x<y?x:y;}
inline ld dmax(ld x,ld y){return x>y?x:y;}
inline ld dmin(ld x,ld y){return x<y?x:y;}
inline ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
inline ll lcm(ll a,ll b){return a*b/gcd(a,b);}
inline ll lowbit(ll x){return x&(-x);}
inline ll read(){ll read_result=0,is_below_0=0;char now_ch=0;while(!isdigit(now_ch)){is_below_0|=now_ch=='-';now_ch=getchar();}while(isdigit(now_ch)){read_result=(read_result<<3)+(read_result<<1)+(now_ch^48);now_ch=getchar();}return is_below_0?-read_result:read_result;}
inline ld dread(){ld x=0,d=0.1;char f=0,ch=getchar();while(!isdigit(ch))f|=(ch=='-'),ch=getchar();while(isdigit(ch)) x=x*10+ch-48,ch=getchar();if(ch=='.'){ch=getchar();while(isdigit(ch))x+=d*(ch^48),d*=0.1,ch=getchar();}return f?-x:x;}
inline void write(ll x){if(x<0){putchar('-');x=-x;}if(x>9){write(x/10);}putchar(x%10+'0');}
const ll MAXN=5e5+7,MAXM=5e5+7;
ll fa[MAXN],n,m,q,k,head[MAXN],edgenum;
bool book[MAXN];
struct node
{
	ll u,v,nxt,w,id,x,y;
	bool operator<(const node& xx)const
	{
		return w<xx.w;
	}
}edge[MAXM];
vector<node>e;
void add_edge(ll u,ll v,ll w)
{
	edgenum++;
	edge[edgenum].nxt=head[u];
	edge[edgenum].v=v;
	edge[edgenum].u=u;
	edge[edgenum].w=w;
	head[u]=edgenum;
}
ll find(ll x)
{
	if(x!=fa[x])fa[x]=find(fa[x]);
	return fa[x];
}
void us(ll x,ll y)
{
	ll xx=find(x),yy=find(y);
	if(xx!=yy)
	{
		fa[xx]=fa[yy]; 
	}
}
bool cmp(const node& xx,const node& yy)
{
	return xx.id<yy.id;
}
int main()
{
 	//freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    n=read(),m=read();
    for(ll i=1;i<=m;i++)
    {
    	ll u=read(),v=read(),w=read();
    	add_edge(u,v,w);
    	edge[i].id=i;
	}
	sort(edge+1,edge+m+1);
	edge[0].w=-1;
	for(ll i=1;i<=n;i++)fa[i]=i;
	for(ll i=1;i<=m;)
	{
		ll j=i;
		do
		{
			edge[j].x=find(edge[j].u),edge[j].y=find(edge[j].v);
			j++;
		}while(j<=m&&edge[j].w==edge[j-1].w);
		while(i<j)
		{
			while(find(edge[i].u)==find(edge[i].v)&&i<j)i++;
			if(i<j)us(edge[i].u,edge[i].v);
		}
	}
	q=read();
	sort(edge+1,edge+m+1,cmp);
	for(ll i=1;i<=n;i++)fa[i]=i;
	while(q--)
	{
		k=read();
		for(ll i=1;i<=k;i++)
		{
			ll pos=read();
			node tmp;
			tmp.u=edge[pos].x,tmp.v=edge[pos].y,tmp.w=edge[pos].w;
			e.push_back(tmp);
		}
		sort(e.begin(),e.end());
		bool ans=1;
		for(ll i=0;i<e.size()&&ans;)
		{
			if(find(e[i].u)==find(e[i].v))
			{
				ans=0;
				break;
			}
			us(e[i].u,e[i].v);
			ll j=i+1;
			while(j<e.size()&&e[i].w==e[j].w)
			{
				if(find(e[j].u)==find(e[j].v))
				{
					ans=0;
					break;
				}
				us(e[j].u,e[j].v);j++;
			}
			while(i<j)fa[e[i].u]=e[i].u,fa[e[i].v]=e[i].v,i++;
		}
		puts(ans?"YES":"NO");
		e.clear();
	}
	return 0;
}
```



---

## 作者：Endt (赞：1)

# Envy-题解

## 题面

[Envy](https://codeforces.com/contest/892/problem/E)

输入一个 $m$ 条边的无向图，有 $q$ 个询问，每次询问一组边集，问是否存在一个最小生成树包含这组边集。

## 前置知识

若一个连通图中，比边 $e$ 边权小的所有边组成的图中 $e$ 的两个端点不连通，则 $e$ 在这个图的一个最小生成树中。

若一个连通图中，边 $i$ 在这个图的一个最小生成树中，边 $j$ 在这个图的一个最小生成树中，且 $i,j$ 权值不同，则 $i,j$ 同在这个图的一个最小生成树中。

##### 可以自己画图感性理解，也可以找资料理性理解。

---

###### 被某人~~wēixié~~建议帮助大家理解一下。

![](https://cdn.fzoi.top/upload/user/c20230122/22040809135873.png)

1. 如上图，使用在准备连接中间的那条权值为 $3$ 的边时，发现两个端点已经连通了。虽然按照 $Kruskal$ 的算法，中间的那条权值为 $2$ 的边并不会被实际连接，但最小生成树一点包含红边中的若干条，且使所有红边相连点都被包含（$Kruskal$ 是在两个端点已被连通的情况下才不连接）。而如果不连通（右侧的那条权值为 $3$ 的边），$Kruskal$ 自然是会连接的。
2. 如果 $i,j$ 边权不同，它们是在不同的阶段待连接，完全独立。如果 $i,j$ 边权相同，它们就有可能连接相同的两个曾经独立连通块，不合法。

## 分析

根据前置知识，按照 $Kruskal$ 的步骤，将所有边按权值从小到大连接，使用并查集记录连通性。一个询问集中如有权值等的边，就全部插入后撤销操作。

快捷的方式是将所有被询问的边排序，同询问集的排在一起。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

inline int read_int(){//快速读入
	register int x=0;register char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c<='9'&&c>='0'){
		x=(x<<3)+(x<<1)+c-'0';
		c=getchar();
	}
	return x;
}

int n,m,QQ,k;
class EDGE{
	public:
		int u,v,w;
}e[500005];
int e_cnt;
void add_edge(){
	int u=read_int();int v=read_int();int w=read_int();
	++e_cnt;
	e[e_cnt].u=u;e[e_cnt].v=v;e[e_cnt].w=w;
}

class Q{
	public:
		EDGE edge;
		int id;
}q[500005];
int q_cnt;

bool cmp_E(EDGE x,EDGE y){
	return x.w<y.w;
}
bool cmp_Q(Q x,Q y){
	if(x.edge.w!=y.edge.w)return x.edge.w<y.edge.w;
	else return x.id<y.id;
}

int fa[500005],s[500005];
bool ans[500005];
stack<pair<int,int>> M;
stack<bool> N;
int Find_fa(int x){
	while(fa[x]!=x)x=fa[x];
	return x;
}
void Merge(int x,int y){
	x=Find_fa(x),y=Find_fa(y);
	if(x==y){
		M.push(make_pair(0,0));
		N.push(0);
		return;
	}
	if(s[x]<s[y]){
		M.push(make_pair(x,y));
		N.push(0);
		fa[x]=y;
	}else if(s[x]>s[y]){
		M.push(make_pair(y,x));
		N.push(0);
		fa[y]=x;
	}else{
		M.push(make_pair(x,y));
		++s[y];
		N.push(1);
		fa[x]=y;
	}
}
void Unmerge(int X){
	while(~--X){
		int x=M.top().first,y=M.top().second,z=N.top();
		M.pop(),N.pop();
		fa[x]=x;if(z)--s[y];
	}
}

int main(){
	n=read_int();m=read_int();
	for(int i=1;i<=m;++i)add_edge();
	QQ=read_int();
	for(int i=1;i<=QQ;++i){
		k=read_int();
		for(int j=1;j<=k;++j){
			int EE=read_int();
			++q_cnt;
			q[q_cnt].edge=e[EE];
			q[q_cnt].id=i;
		}
	}
	sort(e+1,e+1+e_cnt,cmp_E);sort(q+1,q+1+q_cnt,cmp_Q);//排序
	
	for(int i=1;i<=n;++i)fa[i]=i,s[i]=1;
	e_cnt=1;
	for(int i=1;i<=q_cnt;){
		while(e[e_cnt].w<q[i].edge.w){Merge(e[e_cnt].u,e[e_cnt].v);++e_cnt;}//插入所有比当前边权值小的边
		int j;
		for(j=i;j<=q_cnt;++j){
			if(q[j].edge.w!=q[i].edge.w||q[j].id!=q[i].id)break;
			if(Find_fa(q[j].edge.u)==Find_fa(q[j].edge.v)){//NO
				ans[q[j].id]=1;
			}
			Merge(q[j].edge.u,q[j].edge.v);
		}
		Unmerge(j-i);//撤销
		i=j;
	}
	for(int i=1;i<=QQ;++i){
		printf(ans[i]?"NO\n":"YES\n");
	}
	
	return 0;
}
```





---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 2300}$
----
### 解题思路：

一开始想的 $\text{LCT}$，结果有更巧妙的做法，果然我还是太菜了。

---
#### $\text{LCT}$ 做法：

先建立任意一棵最小生成树，每一次要更换边的时候，查询新的两个点之间权值最大的边是不是恰好等于更换边的权值，如果没有说明如果把这个边加上去会使得代价增大，不可取。不可能出现最大值比当前要加入的边还要大的情况。

然后将那一条边断开，连接上新的边，由于新的边不能被换下来，不妨将权值设置为无限小，最后恢复原样。这个过程用 $\text{LCT}$ 做一下就好了。

肉眼可见的麻烦，所以换一种做法。

---
#### 并查集做法

利用 $\text{kruskal}$ 的性质，一定是按照边的权值依次处理，而且无论按照什么样的顺序加边，在处理完一种权值之后形成的若干块一定是一样的。因为假设有在一种方式使得两个点可以在同一个连通块中，那么在另一个顺序中，这个链接两个点的边也一定能加入，最后使得两个点联通。对于不在一起的也是同理。

那么对于每一个边，在考虑到这个边所在的权值的时候，它所连接的两个连通块（有可能是同一个）就是固定的，预处理出这个，然后每一次询问的时候就直接用这些连通块的编号进行操作，效果和用整个并查集是一样的。

当出现了环的时候，这个边就一定不能被加入，也就是整个方案不可行。反之则在当前可行。

明显比上一种简单。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=500005;
int n,m,Q,fa[MAXN],K,flag,x;
int find(int x){
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
void merge(int x,int y){
	fa[find(x)]=find(y);
}
struct edge{
	int x,y,v,id;
	bool operator <(const edge a)const{
		return v<a.v;
	}
}e[MAXN],v[MAXN];
bool cmd(edge a,edge b){
	return a.id<b.id;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].v);
		e[i].id=i;
	}
	sort(e+1,e+m+1);
	e[0].v=-1;
	for(int i=1;i<=m;){
		int j=i;
		e[i].x=find(e[i].x);
		e[i].y=find(e[i].y);
		i++;
		while(e[i].v==e[i-1].v){
			e[i].x=find(e[i].x);
			e[i].y=find(e[i].y);
			i++;
		}
		for(;j<i;j++){
			if(find(e[j].x)==find(e[j].y))continue;
			merge(e[j].x,e[j].y);
		}
	}
	for(int i=1;i<=n;i++)fa[i]=i;
	sort(e+1,e+m+1,cmd);
	scanf("%d",&Q);
	while(Q--){
		flag=1;
		scanf("%d",&K);
		for(int i=1;i<=K;i++){
			scanf("%d",&x);
			v[i]=e[x];
		}
		sort(v+1,v+K+1);
		v[K+1].v=-1;
		for(int i=1;i<=K;){
			int j=i;
			if(v[i].x==v[i].y){flag=0;break;}
			merge(v[i].x,v[i].y);
			i++;
			while(v[i].v==v[i-1].v){
				if(find(v[i].x)==find(v[i].y)){flag=0;break;}
				merge(v[i].x,v[i].y);
				i++;
			}
			for(;j<i;j++)fa[v[j].x]=v[j].x,fa[v[j].y]=v[j].y;
		}
		if(flag)printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```


---

