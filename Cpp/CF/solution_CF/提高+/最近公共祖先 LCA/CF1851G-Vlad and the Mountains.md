# Vlad and the Mountains

## 题目描述

Vlad decided to go on a trip to the mountains. He plans to move between $ n $ mountains, some of which are connected by roads. The $ i $ -th mountain has a height of $ h_i $ .

If there is a road between mountains $ i $ and $ j $ , Vlad can move from mountain $ i $ to mountain $ j $ by spending $ h_j - h_i $ units of energy. If his energy drops below zero during the transition, he will not be able to move from mountain $ i $ to mountain $ j $ . Note that $ h_j - h_i $ can be negative and then the energy will be restored.

Vlad wants to consider different route options, so he asks you to answer the following queries: is it possible to construct some route starting at mountain $ a $ and ending at mountain $ b $ , given that he initially has $ e $ units of energy?

## 样例 #1

### 输入

```
2
7 7
1 5 3 4 2 4 1
1 4
4 3
3 6
3 2
2 5
5 6
5 7
5
1 1 3
6 2 0
4 7 0
1 7 4
1 7 2
6 5
4 7 6 2 5 1
1 3
5 3
1 5
2 4
6 2
5
1 5 1
1 3 1
1 2 1000
6 2 6
6 2 5```

### 输出

```
YES
NO
YES
YES
NO

YES
NO
NO
YES
NO```

## 样例 #2

### 输入

```
2
3 2
1 3 9
1 2
2 3
5
1 1 1
3 2 2
1 1 2
3 3 0
1 2 1
3 3
1 4 1
1 2
2 3
1 3
5
3 3 9
1 3 6
1 1 2
3 3 6
3 3 4```

### 输出

```
YES
YES
YES
YES
NO

YES
YES
YES
YES
YES```

## 样例 #3

### 输入

```
1
6 10
7 9 2 10 8 6
4 2
6 1
4 5
3 5
6 4
1 3
2 6
6 5
1 2
3 6
5
4 4 8
3 3 1
5 5 9
2 1 7
6 6 10```

### 输出

```
YES
YES
YES
YES
YES```

# 题解

## 作者：Pengzt (赞：12)

[CF1851G](https://www.luogu.com.cn/problem/CF1851G)

一眼题。

发现如果从 $i\to j\to k$，则要满足 $h_j-h_i\le e$ 且 $h_j-h_i+h_k-h_j\le e$，也就是 $h_k-h_i\le e$。然后就发现能不能到那个点与路径上的其它点没关系，只需满足不大于 $h_i+e$ 即可。这时候问题就变为了只经过权值 $\le h_i+e$ 的点能否从 $s$ 到达 $t$。这时候按 $h_i+e$ 排序后离线，变为加点和查询连通性，用并查集维护即可。

[评测记录](https://codeforces.com/contest/1851/submission/226510313)

---

## 作者：E1_de5truct0r (赞：6)

简单题。

由于这个两点之间走来走去的权值 $h_i-h_j$ 不带绝对值，所以不难发现从 $u$ 出发，能量为 $e$ 的时候，无论怎么走，能到达的 $h$ 最大的点不超过 $h_u+e$。

那么问题就转化为给定 $q$ 次询问，每次询问求能否只通过走 $h_i \leq h_a+e$ 的点，从 $a$ 到达 $b$。

不难发现可以按照 $h_a+e$ 排序，每次对图进行加边，并查集维护即可。复杂度 $O(n \log n)$。

[Code & Submission](https://codeforces.com/contest/1851/submission/216516177)

---

## 作者：_sunkuangzheng_ (赞：5)

为什么不强制在线！(恼

Kruskal 重构树板题捏，虽然有神奇的离线做法。

**【题目分析】**

首先分析一条 $u \to v$ 的路径 $p_1 \to p_2 \to p_3 \to \ldots \to p_k$，其中 $p_1 = u,p _k = v$，它的代价是 $-h_{p_1} + h_{p_2} - h_{p_2} + h_{p_3} - \ldots +h_{p_{k-1}} - h_{p_{k-1}} + h_{p_k} = h_{v} - h_u$。也即从 $u$ 到 $v$ 的路径不论经过什么中间点，最后消耗的是定值 $h_v - h_u$。于是你可能就会有这样的想法：

```cpp
cin >> u >> v >> w;
if(h[v] - h[u] <= w) puts("YES"); 
else puts("NO");
```

然而你 WA 了，因为题目要求任意时刻体力值都要大于等于 $0$。

于是题意转化为是否存在从 $u$ 到 $v$ 的路径使得经过的所有点权都不超过 $h_u + w$。

这就是 Kruskal 重构树的板子啊！

我们令每条边的边权 $w = \max(h_u,h_v)$，建树跑即可。这个算法是在线的捏！

代码实现上，注意图可能不连通，需要特判一下。注意多测清空问题。

最后推荐两道重构树~~阴间~~好题：

- [P7834 Peaks](https://www.luogu.com.cn/problem/P7834)

- [P5573 星际 kfc 篮球赛](https://www.luogu.com.cn/problem/P5573)

**【代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 8e5+5;
struct edge{int to,nxt,w,u,v;}e[maxn],g[maxn];
int t,head[maxn],cnt,n,m,a[maxn],u,v,f[maxn],fa[maxn],dep[maxn],tot,w,top[maxn],siz[maxn],son[maxn],q,b[maxn];
void add(int u,int v){e[++cnt].to = v,e[cnt].nxt = head[u],head[u] = cnt;}
bool cmp(edge a,edge b){return a.w < b.w;}
int find(int x){return x == f[x] ? x : f[x] = find(f[x]);}
void dfs(int u,int fat){
    fa[u] = fat,dep[u] = dep[fat] + 1,siz[u] = 1,son[u] = 0;
    for(int i = head[u],v;v = e[i].to,i;i = e[i].nxt){
        if(v == fat) continue;dfs(v,u),siz[u] += siz[v];
        if(siz[v] > siz[son[u]]) son[u] = v;
    }
}void dfs2(int u,int tp){
    top[u] = tp;if(son[u]) dfs2(son[u],tp);
    for(int i = head[u],v;v = e[i].to,i;i = e[i].nxt) if(v != fa[u] && v != son[u]) dfs2(v,v);
}int lca(int u,int v){
    while(top[u] != top[v])
        if(dep[top[u]] > dep[top[v]]) u = fa[top[u]]; else v = fa[top[v]];
    return dep[u] < dep[v] ? u : v;
}
void work(){
    cnt = 0;
    for(int i = 1;i <= 2*n;i ++) head[i] = dep[i] = 0;
    cin >> n >> m;
    for(int i = 1;i <= n;i ++) cin >> a[i];
    for(int i = 1;i <= m;i ++) cin >> u >> v,g[i] = {0,0,max(a[u],a[v]),u,v};
    sort(g+1,g+m+1,cmp),tot = n;
    for(int i = 1;i <= 2*n;i ++) f[i] = i,b[i] = 0;
    for(int i = 1;i <= m;i ++){
        int u = find(g[i].u),v = find(g[i].v);
        if(u == v) continue;f[u] = f[v] = ++tot,b[tot] = g[i].w;
        add(tot,u),add(tot,v),add(u,tot),add(v,tot);
    }for(int i = 1;i <= 2*n;i ++) if(find(i) == i) dfs(i,0),dfs2(i,i);
    cin >> q;
    while(q --){
        cin >> u >> v >> w;
        if(b[lca(u,v)] > a[u] + w || find(u) != find(v)) cout << "NO\n";
        else cout << "YES\n";
    }
}
int main(){
    cin >> t;
    while(t --) work();
}
```

---

## 作者：紊莫 (赞：2)

我是小丑之模拟赛推出条件没切。


------------


首先题目要求这个初始能量为 $e$ 且不能为零，意思就是说你上上下下不管到哪里，都不能去 $h_j>h_s+e$ 的点。证明显然。

那么也就是说对于一个 $h_s+e$，图中能走的边显然是固定的。考虑增大这个值，图中能走的边显然也不减，所以考虑按照这个排序，从小到大考虑。

我们使用并查集维护图的连通性，每次就在之前未选的边（按照边权排序）中选出 $h<h_s+e$ 的边。

这样时间复杂度是 $\mathcal{O(n\log n)}$ 的，代码是赛时改，所以变量名会有出入。

```cpp
const int N=200005,M=(N<<1),inf=0x3f3f3f3f,mod=1e9+7;
int n,m,h[N],ans[N],f[N];
struct edge{
	int u,v,w,id;
}e[N],q[N];
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
void merge(int x,int y){f[find(x)] = find(y);}
void solve(){
	n = rd();m = rd();F(i,1,n) h[i] = rd(),f[i]=i;
	F(i,1,m){
		int u=rd(),v=rd();
		e[i]={u,v,max(h[u],h[v]),0};
	}
	sort(e+1,e+m+1,[](edge a,edge b){
		return a.w<b.w;
	});
	int Q = rd();F(i,1,Q){
		int a = rd(),b = rd(),v = rd();
		q[i]={a,b,v,i};ans[i]=0;
	}sort(q+1,q+Q+1,[](edge a,edge b){
		return h[a.u]+a.w<h[b.u]+b.w;
	});
	int now = 1;	
	F(i,1,Q){
		while(now<=m&&e[now].w<=h[q[i].u]+q[i].w)
			merge(e[now].u,e[now].v),now ++;
		if(find(q[i].u)==find(q[i].v))ans[q[i].id] = 1;
	}
	for(int i=1;i<=Q;i++)puts(ans[i]?"YES":"NO");puts("");
}
```


---

## 作者：CWzwz (赞：1)

诸位大佬把思路讲的很清晰了，我主要补充一下实现。

### 思路

考虑：如果一个询问的答案是肯定的，它对路径上所有点的要求。

询问为 `a b e`。

因为只有 $e$ 点能量，所以能走到的最大高度只有 $h_a + e$，没有最小高度。若路径上所有点的点权都在这个范围内，这个询问成立。

问题转化成：$a$ 到 $b$ 是否存在一条路径，使得其上的所有点权都小于等于 $h_a + e$。

那么就很简单了，把询问离线下来，按照 $h_a + e$ 从小到大排序，再依次处理每个询问。

每次询问，在新图中加上刚刚满足点权 $>h_a + e$ 的点，若一条边的两端点都被加上了，才连边。

### 时间复杂度

套了三层循环，但是第二层总共只会执行 $n$ 次，第三层总共只会执行 $2m$ 次左右。

复杂度 $O(n\cdot\log n+q\cdot\log q+m\cdot\operatorname{\alpha}(n))$。

代码有注释。

```cpp
//Problem: CF1851G
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f3f
#define i32 INT_MAX
#define i64 LONG_LONG_MAX
#define pii pair<int, int>
#define pll pair<long long, long long>
#define push_back pb
typedef long long ll;
using namespace std;
const int N = 2e5 + 10;
ll read(){ll x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}return x*f;}
void print(ll x){if(x<0)putchar('-'),x=-x;if(x>9)print(x/10);putchar(x%10+48);}

int t, n, m, que, cnte;
int a[N], b[N], head[N], rt[N], ans[N], vst[N];

struct edge {
    int v, nxt;
} e[N << 1];
struct query {
    int u, v, e, id; //离线询问
} q[N];

void adde(int u, int v) {
    e[++cnte] = (edge){v, head[u]};
    head[u] = cnte;
}
bool cmp(query x, query y) {
    return a[x.u] + x.e < a[y.u] + y.e; //按 h_a + e 排序询问
}
bool cmp1(int x, int y) {
    return a[x] < a[y];
}
int find(int x) {
    if(rt[x] == x) return x;
    return rt[x] = find(rt[x]);
}
void merge(int u, int v) {				//并查集 
    // cout << "merge: " << u << ' ' << v << '\n';
    if(find(u) != find(v)) rt[find(u)] = find(v);
}

int main() {
	// std::ios::sync_with_stdio(false);
	cin >> t;
    while(t--) {
        memset(vst, 0, sizeof vst);
        cnte = 0;
        memset(head, 0, sizeof head);  //多测不清空，___
        n = read(), m = read();
        for(int i = 1; i <= n; i++) {
            a[i] = read();
            b[i] = i;  // b 数组：实现对点权的排序
            rt[i] = i; //并查集
        }
        for(int i = 1; i <= m; i++) {
            int u = read(), v = read();
            adde(u, v);
            adde(v, u);
        }
        que = read();
        for(int i = 1; i <= que; i++)
            q[i].u = read(), q[i].v = read(), q[i].e = read(), q[i].id = i;
            sort(q + 1, q + que + 1, cmp); //排序离线询问
            sort(b + 1, b + n + 1, cmp1);  //点权排序，b数组记录按点权排序后的顺序。
            int j = 1;
            for(int i = 1; i <= que; i++) { //循环询问
                for(; j <= n; j++) { //这里是按点权大小顺序遍历每个点
                if(a[b[j]] > a[q[i].u] + q[i].e)//如果满足: 点权 > h_a + e
                    break;
                    vst[b[j]] = 1; // 标记已被加入
                    for(int k = head[b[j]]; k; k = e[k].nxt) {
                        if(vst[e[k].v]) merge(b[j], e[k].v);//判断另一端点若也被加入了，则连边。
                    }
                }
                ans[q[i].id] = (find(q[i].u) == find(q[i].v));
            }
        for(int i = 1; i <= que; i++) 
            if(ans[i]) puts("YES");
            else puts("NO");
    }
    return 0;
}
```

---

## 作者：Cosine_Func (赞：0)

板。

容易发现，当只存在 $3$ 个点时，设路径为 $i\to j\to k$，需要满足 $h_j-h_i\le e$ 且 $h_j-h_i+h_k-h_j\le e$，即 $h_k-h_i\le e$。数学归纳法易证点数大于 $3$ 时也条件同上。显然答案只与源点和汇点相关，因此直接按 $h_i+e$ 排序离线，用并查集维护即可。时间复杂度 $O\left(N\times\log N\right)$。

参考代码如下：
```cpp
#include<bits/stdc++.h>
#define pb push_back
#define ll long long
#define endl '\n'
#define itn int
#define pi pair<int,int>
//#define int ll
using namespace std;
const int MOD1=1e9+7;
const int MOD2=998244353;
const int N=2e5+5;
struct Query{
	int u,v,e,id;
	bool operator<(const Query &b)const{
		return e<b.e;
	}
}query[N];
struct Edge{
	int u,v,w;
	bool operator<(const Edge &b)const{
		return w<b.w;
	}
}edge[N];
int n,m,q,h[N],fa[N],ans[N];
int find(int u){
	return fa[u]==u?u:fa[u]=find(fa[u]);
}
inline void Solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		fa[i]=i;
	for(int i=1;i<=n;i++)
		cin>>h[i];
	for(int i=1;i<=m;i++){
		cin>>edge[i].u>>edge[i].v;
		edge[i].w=max(h[edge[i].u],h[edge[i].v]);
	}
	cin>>q;
	for(int i=1;i<=q;i++){
		cin>>query[i].u>>query[i].v>>query[i].e;
		query[i].id=i;
		query[i].e+=h[query[i].u];
	}
	sort(edge+1,edge+m+1);
	sort(query+1,query+q+1);
	int j=1;
	for(int i=1;i<=q;i++){
        while(j<=m and edge[j].w<=query[i].e){
            int u=edge[j].u;
            int v=edge[j].v;
            fa[find(u)]=find(v);
			j++;
        }
        if(find(query[i].u)==find(query[i].v))
            ans[query[i].id]=1;
        else ans[query[i].id]=0;
	}
	for(int i=1;i<=q;i++)
		cout<<(ans[i]?"Yes":"No")<<endl;
}
signed main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    int T=1;
	cin>>T;
    while(T--)
    	Solve();
    return 0;
}
```

---

## 作者：_Weslie_ (赞：0)

板，但是值得蓝。

对于我这种处于间期复健的选手来说，这个题再合适不过了（

## Solution CF1851G

### Idea

这题最难的一步是转化。

我们计算一条路径 $\{u_1,u_2,u_3,u_4,\cdots,u_s\}$。

以下设 $a$ 为原题中 $h$。

我们对于 $i\in [2,s]$，路径 $(u_1,u_i)$ 的能量剩余为 $e+a_{u_1}-a_{u_2}+a_{u_2}-a_{u_3}+\cdots+a_{u_{i-1}}-a_{u_i}=e-a_{u_i}+a_{u_1}$。

因为对于路径上任何一个点，$e-a_{u_i}+a_{u_1}\ge 0$，则必须有 $a_{u_i}\le e+a_{u_1}$。

设询问 $(u,v,e)$。不难发现，路径中每一个点 $i$ 都必须满足 $a_i\le e+a_u$。我们设一条边 $(u,v)$ 的边权 $w$ 为 $\max(a_u,a_v)$，则必须有 $w\le e+a_u$ 时，这条边才可以被加入这个询问。

因为并查集不好删除，所以我们按照 $e+a_u$ 将询问排序，这样可以保证每条边只会被加入而不会被删除。我们按照 $w$ 将边排序，使得可以 $\operatorname{O}(n)$ 双指针加边。

剩下的离线操作非常简单，[题解：AT_abc040_d [ABC040D] 道路の老朽化対策について](https://www.luogu.com.cn/article/bkalve4u)也有涉及，就不多讲了。

```
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int n,m,fa[N],a[N],q;
int findd(int now){
    if(fa[now]==now)return now;
    return fa[now]=findd(fa[now]);
}
void vnion(int u,int v){
    u=findd(u);v=findd(v);
    if(u==v)return;
    fa[u]=v;
}
struct node{
    int u,v,w;
    friend bool operator <(node _,node __){
        return _.w<__.w;
    }
}e[N];
struct ask{
    int u,v,w,id;
    friend bool operator <(ask _,ask __){
        return _.w<__.w;
    }
}s[N];
int ans[N];
void solve(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        fa[i]=i;
    }
    for(int i=1;i<=m;i++){
        scanf("%d%d",&e[i].u,&e[i].v);
        e[i].w=max(a[e[i].u],a[e[i].v]);
    }
    sort(e+1,e+m+1);
    scanf("%d",&q);
    for(int i=1;i<=q;i++){
        scanf("%d%d%d",&s[i].u,&s[i].v,&s[i].w);
        s[i].id=i;
        s[i].w+=a[s[i].u];
    }
    sort(s+1,s+q+1);
    for(int i=1,j=1;i<=q;i++){
        while(j<=m&&e[j].w<=s[i].w){
            vnion(e[j].u,e[j].v);j++;
        }
        if(findd(s[i].u)==findd(s[i].v)){
            ans[s[i].id]=1;
        }
        else ans[s[i].id]=0;
    }
    for(int i=1;i<=q;i++){
        ans[i] ? printf("YES\n") : printf("NO\n");
    }
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--)solve();
}
```

---

## 作者：eb0ycn (赞：0)

传送门：[CF1851G](https://www.luogu.com.cn/problem/CF1851G)。

我是小丑之模拟赛暴力都能写挂……

## 题意

给出 $n$ 个点 $m$ 条边的无向图，每个点有点权 $h_i$。从点 $i$ 走到点 $j$ 会消耗 $h_j-h_i$ 的能量，如果小于 $0$ 就是**恢复**对应绝对值的能量。给出 $q$ 个询问，每个询问包含起点 $s$，终点 $t$，能量 $e$，能量值在移动的过程中不能低于 $0$，问能否从 $s$ 走到 $t$。

$n,m\le 2\times 10^5$。

## 分析

这个翻译有点形式化了，实际上你可以把点权 $h$ 看成重力势能，把体力值 $e$ 看成动能。

显然，在走的过程中，当前点权和当前体力值之和一定等于 $h_s+e$。这个可以用机械能守恒来理解。你肯定走不到点权大于 $h_s+e$ 的点，你就暂且把它们看成孤立的点，不与其他点连通。那这样所有与 $s$ 连通的点都能走到了。其实不仅是 $s$，对于其他点来说都是如此。很容易想到用并查集维护，每次把点权小于等于 $h_s+e$ 且相互连通的点合并。

由于更大的 $h_s+e$ 意味着更多的点可能相互能走到（如果本来不能互相连通的两点都跟点权更大的点连通，增大 $h_s+e$ 它们就可能会通过那个点连通），所以对每次询问按 $h_s+e$ 排序，离线处理。每次扩大并查集，把两个点权都小于等于 $h_s+e$ 的点合并，这样后一次询问就能继承前一次的结果，能保证每条边至多被访问一次，时间复杂度（大约）是 $O(m \log m + q \log q)$，反正能过……

## 上代码！

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,t,q,fa[200001],siz[200001],x,y,h[200001],ans[200001],ret,now;
struct node{int a,b,w,id;bool operator< (const node& cwx)const{return w<cwx.w;}}v[200001],p[200001];
inline int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
inline void merge(int x,int y)
{
	x=find(x),y=find(y);
	if(x==y)return;
	if(siz[x]>siz[y])swap(x,y);
	fa[x]=y,siz[y]+=siz[x];
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m),now=0;
		for(int i=1;i<=n;++i)siz[i]=1,fa[i]=i,scanf("%d",h+i);
		for(int i=1;i<=m;++i)scanf("%d%d",&x,&y),v[i]={x,y,max(h[x],h[y]),-1};
		sort(v+1,v+m+1);
		scanf("%d",&q);
		for(int i=1;i<=q;++i)scanf("%d%d%d",&x,&y,&ret),p[i]={x,y,h[x]+ret,i};
		sort(p+1,p+q+1);
		for(int i=1;i<=q;++i)
		{
			ret=p[i].w;
			while(now<m&&v[now+1].w<=ret)++now,merge(v[now].a,v[now].b);
			ans[p[i].id]=find(p[i].a)==find(p[i].b);
		}
		for(int i=1;i<=q;++i)printf("%s",ans[i]?"YES\n":"NO\n");
	}
	return 0;
}
```


---

## 作者：未来姚班zyl (赞：0)

## 题目大意

给定一个 $n$ 个节点，$m$ 条边的无向图，每个点有点权 $h_i$，走一条边 $i\rightarrow j$ 的能量**消耗**为 $h_j-h_i$。若干次询问初始携带 $e$ 的能量，能否从 $s$ 走到 $t$，使得过程中能量不会小于 $0$。

## 题目分析

典。一条路径相当于一条链，而这种相减的式子可以很容易想到通过求和消除其中的项。$i\rightarrow j\rightarrow k$ 可行的条件为 $h_j-h_i\le e$，$h_k-h_j+h_j-h_i\le e$。所以 $h_j,h_k\le h_i+e$。所以得到路径上的点 $x$ 只需要满足 $h_x\le h_s+e$。离线查询并用并查集维护连通性即可，边 $(x,y)$ 的边权可以当做 $\max (h_x,h_y)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L xd[x].l
#define R xd[x].r
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define OK Ll<=l&&r<=Rr
#define Root 1,1,n
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define pb push_back
#define ull unsigned ll
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =2e5+5,M=5e6+5,inf=(1LL<<31)-1;
const ll llf=1e18,mod=1e9+7;
using namespace std;
int T=read(),n,m,q,a[N];
struct edge{
	int x,y,w;
}e[N];
int s[N],tp,f[N],out[N];
inline int find(int x){
	return f[x]==x?x:f[x]=find(f[x]);
}
struct node{
	int s,t,w,id;
}sol[N];
inline bool cmp(edge a,edge b){
	return a.w<b.w;
}
inline bool Cmp(node c,node d){
	return a[c.s]+c.w<a[d.s]+d.w;
}
signed main(){
	while(T--){
		n=read(),m=read();
		rep(i,1,n)a[i]=read(),f[i]=i;
		rep(i,1,m)e[i].x=read(),e[i].y=read(),e[i].w=max(a[e[i].x],a[e[i].y]);
		sort(e+1,e+m+1,cmp);
		q=read();
		rep(i,1,q)sol[i].s=read(),sol[i].t=read(),sol[i].w=read(),sol[i].id=i;
		sort(sol+1,sol+q+1,Cmp);
		int Ll=1;
		rep(i,1,q){
			while(Ll<=m&&e[Ll].w<=a[sol[i].s]+sol[i].w)f[find(e[Ll].x)]=find(e[Ll].y),Ll++;
			out[sol[i].id]=(find(sol[i].s)==find(sol[i].t));
		}
		rep(i,1,q)if(out[i])cout <<"Yes\n";
		else cout <<"No\n";
		cout <<'\n';
	}
	return 0;
}
```


---

## 作者：Rei_Sen (赞：0)

题目第一遍没读懂捏，感觉铃仙的语文要重修了。

首先，题目有一个很重要的条件，就是 $h_i \in [1, 10^9]$，这使得我们可以将原问题转化为：

> 是否存在一条 $S$ 到 $T$ 的路线，使得路线上的所有点都小于等于 $h_s + e$。

证明考虑类比物理上的能量守恒定律，因为没有负数的存在，所以我们不会凭空增加能量，只会转移。

然后就好办了，考虑将询问离线，对边按权排序，然后对于某个询问，我们让两端点小于等于 $h_s + e$ 的边全部加入并查集中，然后判断连通性，如果不能联通则为 `NO`，否则为 `YES`。

由于我们对边和询问都排序了，所以只会加边，不会删边，然后做完了，复杂度 $O(n \log n)$。

实现上还是有点小细节的，不过无伤大雅。

```cpp
pii h1[MAX_SIZE];
int h2[MAX_SIZE];
int fa[MAX_SIZE];
int siz[MAX_SIZE];
void init(int n) {
	for(int i = 1; i <= n; i++){
		fa[i] = i;
		siz[i] = 1;
	}
}

int find(int x){
	if(fa[x] == x)
		return fa[x];
	return fa[x] = find(fa[x]);
}

void merge(int x, int y) {
	int fx = find(x);
	int fy = find(y);
	if(siz[fx] >= siz[fy]) {
		fa[fy] = fx;
		siz[fx] += siz[fy];
	} else {
		fa[fx] = fy;
		siz[fy] += siz[fx];
	}
}

int head[MAX_SIZE << 1];
int ver[MAX_SIZE << 1];
int Next[MAX_SIZE << 1];
int tot = 1;
void add_edge(int u, int v) {
	ver[++tot] = v;
	Next[tot] = head[u];
	head[u] = tot;
}

struct QUERY{
	int id;
	int s;
	int t;
	int e;
	bool operator < (const QUERY &oth) {
		return h2[s] + e < h2[oth.s] + oth.e;
	}
};
bitset<MAX_SIZE> ans;

void solve(){
	int n = read();
	int m = read();
	init(n);
	tot = 1;
	for(int i = 1; i <= n; i++) {
		h2[i] = h1[i].x = read();
		h1[i].y = i;
	}
	sort(h1 + 1, h1 + n + 1);
	for(int i = 1; i <= m; i++) {
		int u, v;
		read(u, v);
		add_edge(u, v);
		add_edge(v, u);
	}
	int q = read();
	vector<QUERY> qwq;
	for(int i = 1; i <= q; i++) {
		int s,t,e;
		read(s,t,e);
		qwq.push_back({i, s, t, e});
	}
	sort(qwq.begin(), qwq.end());
	int pos = 1;
	for(auto e : qwq) {
		int limit = h2[e.s] + e.e;
		while(pos <= n && h1[pos].x <= limit) {
			int u = h1[pos].y;
			for(int i = head[u]; i; i = Next[i]) {
				int v = ver[i];
				if(find(u) == find(v))
					continue;
				if(h2[v] > limit)
					continue;
				merge(u, v);
			}
			++pos;
		}
		
		ans[e.id] = (bool)(find(e.s) == find(e.t));
	}
	for(int i = 1; i <= q; i++){
		puts(ans[i] ? "YES" : "NO");
	}
	for(int i = 1; i <= n; i++){
		head[i] = 0;
	}
}

int main() {
	int T = read();
	while(T--){
		solve();
	}
	return 0;
}
```

---

## 作者：jasonliujiahua (赞：0)

# CF1851G

[题目传送门](https://www.luogu.com.cn/problem/CF1851G)
## 题意简述：
共 $T$ 组测试用例，每组测试用例给出 $n$ 个点 $m$ 条边的无向图，每个点有点权 $h_i$。从点 $i$ 走到点 $j$ 会消耗 $h_j - h_i$ 的能量，如果小于 $0$ 就是恢复对应绝对值的能量。给出 $q$ 个询问，每个询问包含起点 $s$、终点 $t$，能量 $e$，能量值在移动的过程中不能低于 $0$，问能否从 $s$ 走到 $t$。

$1\le T\le 10^4,2\le n\le 2\times 10^5,1\le m\le \min(\frac{n(n-1)}{2},2\times 10^5),1\le h_i\le 10^9,1\le q\le 2\times 10^5,$
## 题目分析：
### Step 1：问题转化
显然若从 $s$ 碰到了一个 $h$ 值大于 $h_s+e$ 的点，那么该点及其之后的点都不会在答案的路径上。因此，可得结论：**从 $s$ 到 $t$ 的过程中只能走点权小于等于 $h_s+e$ 的点。**
### Step 2：解决策略
可以发现应贪心地尽可能走权值小的点，看能不能走到，即：
$$\left ( \max_{j=s \rightarrow t} h_j \right ) \le h_s +e$$
因此想到类似于 kruskal 的算法以方便知道 $( \max_{j=s \rightarrow t} h_j )$。因此，按点权从小到大排序，依次合并并查集，来限制路径的最大数值和统计连通性。

还有，由于我们对点权进行了排序，因此也应将询问离线下来同样进行一遍排序。
### Step 3：反思经验
有很多限制两点间最大值的问题其实都可以用类似于 kruskal 的算法求解，其本质思想是通过排序以方便得知当前的路径最大值。
## 参考代码：

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+10;
int T,n,m,Q,cnt,fa[maxn],sz[maxn],b[maxn],ans[maxn];
struct query
{
    int s,t,E,id;
}q[maxn];
struct node
{
    int h,id;
}a[maxn];
struct edge
{
    int u,v,nxt;
}e[maxn<<1];
int head[maxn];
inline void add(int x,int y)
{
    e[++cnt].u=x;
    e[cnt].v=y;
    e[cnt].nxt=head[x];
    head[x]=cnt;
}
inline int val(query x)
{
    return b[x.s]+x.E;
}
inline bool cmp1(query x,query y)
{
    return val(x)<val(y);
}
inline bool cmp2(node x,node y)
{
    return x.h<y.h;
}
inline int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
inline void merge(int x,int y)
{
    int fx=find(x),fy=find(y);
    if(sz[fx]<sz[fy])
    {
        fa[fx]=fy;
        sz[fy]+=sz[fx];
    }
    else
    {
        fa[fy]=fx;
        sz[fx]+=sz[fy];
    }
}
void init()
{
    cin>>n>>m; 
    cnt=0; 
    for(int i=1;i<=n;i++) head[i]=0;
    for(int i=1;i<=n;i++) 
    {
        cin>>a[i].h;
        a[i].id=i;
        b[i]=a[i].h;
        fa[i]=i;
        sz[i]=1;
    }
    for(int i=1;i<=m;i++)
    {
        int x,y;
        cin>>x>>y;
        add(x,y);
        add(y,x);
    }
    cin>>Q;
    for(int i=1;i<=Q;i++)
    {
        cin>>q[i].s>>q[i].t>>q[i].E;
        q[i].id=i;
    }
    sort(q+1,q+Q+1,cmp1);
    sort(a+1,a+n+1,cmp2);
}
void work()
{
    int j=1;
    for(int i=1;i<=Q;i++)
    {
        while(j<=n && a[j].h<=val(q[i]))
        {
            int u=a[j].id;
            for(int w=head[u];w;w=e[w].nxt)
            {
                int v=e[w].v;
                if(find(u)==find(v)) continue;
                if(b[v]>val(q[i])) continue;
                merge(u,v);
            }
            j++;
        }
        ans[q[i].id]=(find(q[i].s)==find(q[i].t));
    }
    for(int i=1;i<=Q;i++)
    {
        if(ans[i]) cout<<"YES\n";
        else cout<<"NO\n";
    }
}
signed main()
{
    cin>>T;
    while(T--)
    {
        init();
        work();
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：Wf_yjqd (赞：0)

算比较简单的 G 吧，虽然我不会。

------------

考虑转化问题为从不经过高于 $h_a+e$ 的点，$a$，$b$ 是否连通。

考虑无向图连通性可以用并查集维护。

由于并查集无法删除，考虑将每条边和询问都按高度排序。

然后对建边合并，对询问查找即可。

复杂度 $\operatorname{O}(n\log n)$。

------------

越想越觉得这题简单了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=4e5+84;
struct Query{
    int from,to,height,op,id,ans;
    friend bool operator<(Query xy,Query zb){
        if(xy.height==zb.height)
            return !xy.op;
        return xy.height<zb.height;
    }
}Q[maxn];
int T,n,m,q,h[maxn],fa[maxn],a,b,e;
inline bool cmp(Query xy,Query zb){
    if(xy.op==1&&zb.op==1)
        return xy.id<zb.id;
    return xy.op;
}
inline int Find(int x){
    return fa[x]=x==fa[x]?x:Find(fa[x]);
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++){
            scanf("%d",&h[i]);
            fa[i]=i;
        }
        for(int i=1;i<=m;i++){
            scanf("%d%d",&a,&b);
            Q[i]={a,b,max(h[a],h[b]),0,168,168};
        }
        scanf("%d",&q);
        for(int i=1;i<=q;i++){
            scanf("%d%d%d",&a,&b,&e);
            Q[m+i]={a,b,h[a]+e,1,i,168};
        }
        sort(Q+1,Q+m+q+1);
        for(int i=1;i<=m+q;i++){
            if(Q[i].op)
                Q[i].ans=Find(Q[i].from)==Find(Q[i].to);
            else
                fa[Find(Q[i].from)]=Find(Q[i].to);
        }
        sort(Q+1,Q+m+q+1,cmp);
        for(int i=1;i<=q;i++)
            puts(Q[i].ans?"Yes Sherry":"No");
    }
    return 0;
}
```


---

## 作者：N_z_ (赞：0)

## 题意

给你 $h$ 和 $m$ 条无向边，从 $i$ 走到 $j$ 花费 $h_j-h_i$ 能量，$q$ 次询问，你初始有 $e$ 能量，判断是否可以从 $s$ 走到 $t$，路上没有一个点能量为负数。

## 思路

提供一个在线做法。首先我们注意到，无论中间过程如何，$i$ 到 $j$ 恒定需要 $h_j-h_i$ 能量，因此路径能量最低点取在路径中 $h$ 最大的那个点。

从而，按照 $\max(h_u,h_v)$ 的顺序加入边 $(u,v)$，建立 kruskal 重构树即可。

## 代码

[215601542](https://codeforces.com/contest/1851/submission/215601542)。

---

## 作者：AlicX (赞：0)

## Solution 

假设由 $u$ 走到 $v$ 的一条满足路径为：$r_1 \to r_2 \to \dots \to r_k$，其中 $r_1=u,r_k=v$，代价则是 $h_{r_1}-h_u+h_{r_2}-h_{r_1}+\dots +h_{v}-h_{r_k}=h_{v}-h_{u}$。满足对于任意 $i \in [1,k]$，$e \geq h_{r_i}-h_u \Longleftrightarrow h_i \leq h_u+e$。

于是将询问按 $h_u+e$ 排序，并查集维护联通即可。

```cpp
#include<bits/stdc++.h> 
#define ll long long 
#define x first 
#define y second 
#define il inline 
#define db double 
#define debug() puts("-----") 
using namespace std; 
typedef pair<int,int> pii; 
il int read(){ 
	int x=0,f=1; char ch=getchar(); 
	while(ch<'0'||ch>'9'){ if(ch=='-') f=-1; ch=getchar(); } 
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar(); 
	return x*f; 
} 
const int N=2e5+10; 
int n,m; 
int p[N];  
pii a[N]; 
int b[N]; 
int h[N],idx=0; 
struct Edge{
	int to,ne; 
}e[N<<1]; 
struct Que{ 
	int u,v,e,id;  
	il bool operator<(const Que& dwy)const{ 
		return b[u]+e<b[dwy.u]+dwy.e; 
	} 
}q[N]; int k; 
il void add(int u,int v){ 
	e[idx].to=v,e[idx].ne=h[u],h[u]=idx++; 
} 
il int find(int x){ 
	if(p[x]!=x) p[x]=find(p[x]); 
	return p[x]; 
} 
bool st[N],ans[N]; 
il void solve(){ 
	n=read(),m=read(); 
	for(int i=1;i<=n;i++) b[i]=a[i].x=read(),a[i].y=i,h[i]=-1,p[i]=i,st[i]=false; 
	for(int i=1,u,v;i<=m;i++) u=read(),v=read(),add(u,v),add(v,u); k=read(); 
	for(int i=1;i<=k;i++) q[i].u=read(),q[i].v=read(),q[i].e=read(),q[i].id=i; 
	sort(a+1,a+n+1); sort(q+1,q+k+1); 
	for(int i=1,j=1;i<=k;i++){ 
		while(j<=n&&a[j].x<=b[q[i].u]+q[i].e){ 
			st[a[j].y]=true; 
			for(int l=h[a[j].y];l!=-1;l=e[l].ne){
				int to=e[l].to; 
				if(st[to]){ 
					int pa=find(a[j].y),pb=find(to); 
					if(pa!=pb) p[pa]=pb; 
				} 
			} j++; 
		} int pa=find(q[i].u),pb=find(q[i].v); 
		if(pa==pb) ans[q[i].id]=true; else ans[q[i].id]=false; 
	} for(int i=1;i<=k;i++) if(ans[i]) puts("YES"); else puts("NO"); 
} 
signed main(){ 
	int T=read(); 
	while(T--) solve(); 
	return 0; 
} 
```

---

