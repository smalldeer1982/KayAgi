# [ARC165C] Social Distance on Graph

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc165/tasks/arc165_c

頂点に $ 1 $ から $ N $ の番号が付いた $ N $ 頂点からなる単純連結無向グラフがあります。グラフには重みを持つ辺が $ M $ 本あり、$ i $ 番目の辺は頂点 $ A_i,B_i $ を結ぶ重みが $ W_i $ の辺です。また、$ 2 $ 頂点を結ぶ単純パスの重みを、単純パスが含む辺の重みの総和とします。

各頂点に対し赤、青のいずれかの色を塗ります。以下の条件を満たす塗り分け方が存在するような整数 $ X $ の最大値を求めてください。

- 同じ色で塗られた相異なる $ 2 $ 頂点を結ぶどの単純パスについても、単純パスの重みは $ X $ 以上である。
 
  単純パスとは グラフ $ G $ 上の頂点 $ X,Y $ に対して、頂点列 $ v_1,v_2,\ \ldots,\ v_k $ であって、 $ v_1=X $, $ v_k=Y $ かつ、$ 1\leq\ i\leq\ k-1 $ に対して $ v_i $ と $ v_{i+1} $ が辺で結ばれているようなものを頂点 $ X $ から頂点 $ Y $ への **ウォーク** と呼びます。 さらに、$ v_1,v_2,\ \ldots,\ v_k $ がすべて異なるようなものを頂点 $ X $ から頂点 $ Y $ への **単純パス** (あるいは単に **パス**) と呼びます。

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ N-1\ \leq\ M\ \leq\ \min(\frac{N(N-1)}{2},2\ \times\ 10^5) $
- $ 1\ \leq\ A_i\ <\ B_i\ \leq\ N $
- $ 1\ \leq\ W_i\ \leq\ 10^9 $
- 与えられるグラフは単純連結無向グラフ
- 入力される値はすべて整数
 
### Sample Explanation 1

$ X=11 $ としたときに条件を満たす色の塗り方が存在するか考えます。頂点 $ 1,3 $ を赤、頂点 $ 2 $ を青で塗った場合、同じ色の頂点を結ぶ単純パス $ 1-2-3 $ の重みが $ 5+6=11 $ となります。これが同じ色の頂点を結ぶ単純パスの重みの最小値となるのでこの塗り分け方は条件を満たしています。 $ X $ が $ 12 $ 以上のとき、条件を満たす塗り分け方が存在しないことが示せます。よって答えは $ 11 $ となります。

## 样例 #1

### 输入

```
3 3
1 2 5
2 3 6
1 3 12```

### 输出

```
11```

## 样例 #2

### 输入

```
10 20
7 10 982219000
3 10 968366179
2 4 992330437
5 6 984414664
2 8 897295423
7 9 155604979
6 8 958833005
2 3 973209957
3 7 985173062
6 10 963895817
2 10 986243534
4 5 721724794
1 3 657562445
1 6 566370694
1 4 988050146
1 9 967817807
4 9 796531581
5 9 983960054
1 10 964450079
8 9 959369491```

### 输出

```
952136560```

## 样例 #3

### 输入

```
10 20
5 6 871895994
8 10 873709822
3 5 454175869
6 10 980782191
2 6 901290987
1 8 298092290
4 8 693116157
4 5 947939338
7 8 934395075
7 9 759563833
5 8 779870031
4 6 919637355
2 9 822858749
4 10 855497285
3 7 954942051
1 2 950411658
4 7 665939990
3 4 634533617
5 7 908372507
1 9 591466693```

### 输出

```
759563833```

# 题解

## 作者：翼德天尊 (赞：5)

写了很菜的二分答案。考虑如何判定。

首先有经典结论：若两条相邻的边边权和小于 $X$，一定无解。证明可以采用鸽巢原理。

所以我们可以由此结论先确定二分上界。

限制完这个之后我们发现此时对于任意长度大于等于 $2$ 的路径都是一定合法的，剩下的只有长度为 $1$ 的路径了。于是把所有边权 $<X$ 的边拉出来黑白染色，判断是否为二分图即可。

时间复杂度 $O(n\log V)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5;
int n,m,minn[N],cmin[N],col[N];
struct Edge{
    int to[N<<1],next[N<<1],head[N],tot,val[N<<1];
    void adde(int u,int v,int w){
        to[++tot]=v,next[tot]=head[u],val[tot]=w,head[u]=tot;
    }
}S;
ll read(){
    ll w=0,f=1;
    char c=getchar();
    while (c>'9'||c<'0'){
        if (c=='-') f=-1;
        c=getchar();
    }
    while (c>='0'&&c<='9'){
        w=(w<<3)+(w<<1)+(c^48);
        c=getchar();
    }
    return w*f;
}
void chan(int u,int w){
    if (w<minn[u]) cmin[u]=minn[u],minn[u]=w;
    else if (w<cmin[u]) cmin[u]=w;
}
bool flag=1;
void dfs(int u,ll x){
    for (int i=S.head[u];i;i=S.next[i]){
        int v=S.to[i];
        if (!col[v]){
            // cout<<x<<" "<<u<<" "<<v<<"\n";
            if (S.val[i]<x) col[v]=3-col[u],dfs(v,x);
        }else if (S.val[i]<x&&col[u]==col[v]){
            // cout<<x<<" "<<S.val[i]<<" "<<u<<" "<<v<<" "<<col[u]<<" "<<col[v]<<"\n";
            flag=0;
        }
    }
}
bool check(ll x){
    flag=1;
    for (int i=1;i<=n;i++) col[i]=0;
    for (int i=1;i<=n;i++)
        if (!col[i]) col[i]=1,dfs(i,x);
    return flag;
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif
    n=read(),m=read();
    for (int i=1;i<=n;i++) minn[i]=cmin[i]=1e9+5;
    for (int i=1;i<=m;i++){
        int u=read(),v=read(),w=read();
        S.adde(u,v,w),S.adde(v,u,w);
        chan(u,w),chan(v,w);
    }
    ll l=0,r=2e9,ans=0;
    for (int i=1;i<=n;i++)
        if (cmin[i]!=1e9+5) r=min(1ll*(minn[i]+cmin[i]),r);
    while (l<=r){
        ll mid=l+r>>1;
        if (check(mid)) ans=mid,l=mid+1;
        else r=mid-1; 
    }
    cout<<ans<<"\n";
    return 0;
}
```

---

## 作者：reclusive (赞：4)

[my blog](https://www.cnblogs.com/reclusive2007/p/17717056.html)

赛时：看不懂题，啊这！

赛后：就这？

---

## 题目描述

有一个简单相连的无向图，其顶点数为 $n$，编号为 $1$ 至 $n$。图中有 $m$ 条加权边，第 $i$ 条边连接顶点 $a_i$ 和 $b_i$，权重为 $w_i$。此外，连接两个顶点的简单路径的权重是简单路径中包含的边的权重之和。

我们给每个顶点涂上红色或蓝色。求满足以下条件的着色的整数 $x$ 的最大值：对于连接涂有相同颜色的两个不同顶点的每一条简单路径，简单路径的权重至少为 $x$。

## 具体思路

显然二分查找最大的 $x$，考虑 check 函数怎么打。

首先，对于权值大于 $x$ 的边，对答案不会造成任何影响，因为几条比 $x$ 大的边怎么加也不会比 $x$ 小。

然后，考虑权值小于 $x$ 的边，那么它连接的两个顶点一定不能染成一种颜色。于是我们给权值小于 $x$ 的边连接的所有点跑一遍二分图染色，能染色说明当前的 $x$ 可行，反之不行。

但是我们直接染色是不行的，因为我们还没考虑染色后，相同颜色的点之间的距离大于等于 $x$。

我们只需要考虑两条边即可，因为多条边也是一样的。我们可以预处理出每个点连着边的最小边权与次小边权的和，然后取一个最小值，这样选出来的最小值就是整个图里面任意两点距离的最小值。我们把这个东西设为二分的上界，就可以保证枚举的 $x$ 小于等于任意两条边的和，即任意相同颜色的点距离大于等于 $x$。

要注意一点的是，二分的 $l$ 和 $r$ 极限情况下是会到 $2e9$ 的，这个时候你 $mid=(l+r)/2$ 一加，就会爆 int，所以**记得要开 long long**。

设 $w$ 为二分上界，时间复杂度：$O(n \log w)$。

## Code
```
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL N=2e5+5;
const LL inf=0x3f3f3f3f;
struct edge{LL x,y,c,pre;}a[2*N];LL last[N],alen;
void ins(LL x,LL y,LL c){
	a[++alen]=edge{x,y,c,last[x]};
	last[x]=alen;
}
LL n,m,color[N];
LL minn[N],next_minn[N];
void solve(LL x,LL c){
	if(c<minn[x]){
		next_minn[x]=minn[x];
		minn[x]=c;
	}
	else if(minn[x]<=c&&c<next_minn[x]){
		next_minn[x]=c;
	}
}
bool dfs(LL x,LL mid,LL c){
	color[x]=c;
	for(LL k=last[x];k;k=a[k].pre){
		if(a[k].c>=mid)continue;
		LL y=a[k].y;
		if(color[x]==color[y])
			return false;
		if(!color[y]&&!dfs(y,mid,3-c))
			return false;
	}
	return true;
}
bool check(LL mid){
	memset(color,0,sizeof(color));
	for(LL i=1;i<=n;i++)
		if(!color[i])
			if(!dfs(i,mid,1))
				return false;
	return true;
}
int main(){
	scanf("%lld%lld",&n,&m);
	alen=1;memset(last,0,sizeof(last));
	memset(minn,0x3f,sizeof(minn));
	memset(next_minn,0x3f,sizeof(next_minn));
	for(LL i=1;i<=m;i++){
		LL x,y,c;scanf("%lld%lld%lld",&x,&y,&c);
		ins(x,y,c),ins(y,x,c);
		solve(x,c),solve(y,c);
	}
	LL l=0,r=2e9,ans;
	for(LL i=1;i<=n;i++){
		r=min(r,minn[i]+next_minn[i]);
	}
	while(l<=r){
		LL mid=(l+r)>>1;
		if(check(mid)){
			l=mid+1;
			ans=mid;
		}
		else r=mid-1;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：樱雪喵 (赞：3)

C < B，简单题。

## Description

给一张 $n$ 个点 $m$ 条边的无向带权图，你要给每个点染黑色或白色。要求对于任意起点终点同色的简单路径，路径的长度（即边权和）不小于 $X$。求 $X$ 的最大值。

保证图连通、无重边无自环，$N,M \le 2\times 10^5$，$1\le W_i\le 10^9$。

## Solution

长度最小的路径肯定是只有一条边的路径，我们希望这样的路径尽量不连接相同颜色的点，并让边权小的优先满足条件。

发现这个本质上是对原图跑最小生成树，跑完的这棵树一定是二分图，且优先令边权小的边满足了条件。对最小生成树黑白染色，判断未被加入的边两个端点颜色是否相同。若相同，则答案对该边权取 $\min$。

考虑路径长度不为 $1$ 的情况，发现最小生成树上路径长度为 $2$ 的边一定属于同一颜色。对每个点记录与它相连的最小边和次小边，并用它们更新答案。同时你发现这东西是答案上界，最多只有 $2\times 10^9$，不用开 long long。

```cpp
const int N=2e5+5,inf=2e9;
int n,m;
struct node{int u,v,w;}E[N];
bool cmp(node x,node y) {return x.w<y.w;}
struct edge{int to,w;};
vector<edge> e[N];
bool cmp1(edge x,edge y) {return x.w<y.w;}
int fa[N];
int find(int x) {return fa[x]==x?x:fa[x]=find(fa[x]);}
int col[N],flag[N];
void dfs(int u)
{
    for(auto i:e[u])
    {
        int v=i.to;
        if(col[v]==-1) col[v]=col[u]^1,dfs(v);
    }
}
int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++) E[i]={read(),read(),read()};
    sort(E+1,E+m+1,cmp);
    for(int i=1;i<=n;i++) fa[i]=i,col[i]=-1;
    for(int i=1;i<=m;i++)
    {
        int u=E[i].u,v=E[i].v,w=E[i].w;
        if(find(u)==find(v)) {flag[i]=1;continue;}
        fa[find(u)]=find(v);
        e[u].push_back({v,w}),e[v].push_back({u,w});
    }
    for(int i=1;i<=n;i++) if(find(i)==i) col[i]=0,dfs(i);
    int ans=inf;
    for(int i=1;i<=m;i++)
    {
        if(flag[i]) if(col[E[i].u]==col[E[i].v]) ans=min(ans,E[i].w);
    }
    for(int i=1;i<=n;i++) sort(e[i].begin(),e[i].end(),cmp1);
    for(int i=1;i<=n;i++)
        if(e[i].size()>1) ans=min(ans,e[i][0].w+e[i][1].w);
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：mjsdnz (赞：1)

+ 好像大家都用了二分，但是我没用，不知道我的方法是不是假了。

+ Tag：生成树

## 题目大意

给定一个简单加权无向图，并将图中节点染成红色或蓝色，要求每个点必须染色，设 $X$ 为两两相同颜色点之间最短路的最小值，要求求出使得 $X$ 最大的染色方案的 $X$。

## 思路

### 树的情况（虽然没有部分分）：

很明显，最优策略是红蓝交错染色，这样可以使得两个相同颜色点之间的最短路最大。求法如下：

$$
len_u=mindis_{son_u}+secmindis_{son_u}
$$
$$
ans=\min_{u\in G}len_u
$$

$mindis_{son_u}$ 表示最近的儿子节点，$secmindis_{son_u}$ 表示次近的儿子节点。

### 所有情况

和树的情况类似，也是交错涂色最优，但是可能有类似于三元环一样的情况，这时我们就可以先将整张图的最小生成树构建出来，算出 $ans$ ，并为每个节点涂色。之后考虑非树边，如果非树边两端点颜色不同直接跳过，若相同则 $ans=\min(ans,val_e)$。这样可以保证 $ans$ 取最优。（不理解的话可以从三元环的情况开始思考）

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 10;
int n, m;
vector<pair<int, int>> g[N];
struct edge {
    int u, v, val;
    bool operator<(const edge &a) const { return val < a.val; }
} e[N];
int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
bool used[N];
void kur() {
    for (int i = 1; i <= m; i++) {
        int u = find(e[i].u);
        int v = find(e[i].v);
        if (u == v)
            continue;
        used[i]=1;
        fa[u] = v;
        g[e[i].u].push_back({e[i].v, e[i].val});
        g[e[i].v].push_back({e[i].u, e[i].val});
    }
}
bool col[N];
int ans=1e18;
void dfs(int u,int fa){
    int mn=1e18,mnn=1e18;
    for(auto e:g[u]){
        int v=e.first;
        int val=e.second;
        if(val<=mn) mnn=mn,mn=val;
        else if(val<mnn) mnn=val;
        ans=min(ans,mn+mnn);
        if(v==fa) continue;
        col[v]=col[fa];
        dfs(v,u);
    }
}
signed main() {
    col[0]=1;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> e[i].u >> e[i].v >> e[i].val;
    }
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    sort(e + 1, e + 1 + m);
    kur();
    dfs(1,0);
    for(int i=1;i<=m;i++){
        if(used[i]) continue;
        if(col[e[i].u]==col[e[i].v]) ans=min(ans,e[i].val);
    }
    cout<<ans;
}
```

---

## 作者：233L (赞：1)

我们首先希望每条边两端异色，于是 $2$ 条边的路径两端一定同色，我们得到一个上界：所有 $2$ 条边的路径的最小值。

但是【每条边两端异色】不一定能被满足，我们考虑 Kruskal 建最小生成树的过程。先让权值最小的边的两端异色，接着是权值次小的边，以此类推。若出现冲突，那么答案就是当前边权，否则说明【每条边两端异色】被满足，答案就是一开始的上界。

什么？【让两个点异色】怎么做？并查集！详见 [P1525 [NOIP2010 提高组] 关押罪犯](https://www.luogu.com.cn/problem/P1525)，不赘述了。

[Submission](https://atcoder.jp/contests/arc165/submissions/45681858)

---

## 作者：BINYU (赞：1)

## 题意

给定 $n$ 个点 $m$ 条边，给每个点染上红蓝两色（想怎么染都行），让两个相同颜色的点之间距离的最小值最大，输出这个值。

## 思路

首先，看到本题要求将一个图上的点染成两种颜色，很容易就想到二分图，而最小值最大这个要求又容易想到二分，这个方法的确可做，但作者考场上没有想到……

于是作者选择~~瞎搞~~，贪心的想，如果我们让最小的边左右染上同样的颜色，那肯定不如染上不同的颜色优，所以，我们可以把边按边权从小到大排序，尽量给边权小的边左右染上不同的颜色。

这可以用并查集来实现：对于每个点，我们对应的在并查集中建立两个点，一个红点，一个蓝点，对于每一条边，当我们处理它时，我们把并查集中代表它两边点的**不同颜色**（即一个点的红点和另一个点的蓝点）放在同一个并查集内，代表他们将在同一个图中，如果一个点的红点和自己的蓝点被放在同一个并查集中，那么这张图就冲突了，所以，最后加进来的那条边左右的点就只能相同，否则会更劣。

还有最后一个问题：多条边组成的简单路径可能比一条边短，我们可以发现，任意三个点中，一定有两个点的颜色相同（抽屉原理），那么，对于一条边数超过二（即点数超过三）的简单路径，实际上它其中的一段就已经让染色冲突了，而对于边数为二的简单路径，我们不可能去为了它把它左右两个点的颜色染成不同的颜色，因为这样中间的点的颜色一定和某一边相同，这样会让答案变为一条边的边权，而非两条边边权之和，所以，对于多条边组成的简单路径，仅有（**不一定有**）两条边组成的简单路径可能影响答案，**且不会改变贪心策略**，只需对于每个点（以该点作为中点）取连接该点最小的两条边计算一下即可。

---

## 作者：_sunkuangzheng_ (赞：1)

**【题目大意】**

一张 $n$ 个点 $m$ 条边的无向图，边有权，对顶点进行黑白染色，使得每一条连接两个相同颜色的顶点的简单路径长度大于等于 $x$，求最大的 $x$。$n,m \le 2\times 10^5$。

**【题目分析】**

二分是很显然的，考虑如何 check 答案。

比较显然的结论是，我们只需要考虑边权严格小于 $x$ 的边，因为若干大于等于 $x$ 的数字的和不可能小于 $x$。那么这些边连接的两个顶点颜色一定不同。

如何处理同颜色之间的距离大于等于 $x$ 的条件？又有一个比较显然的结论是，我们只需要考虑只经过两条边的距离。但是怎么计算两条边的距离？我们想要在 bfs/dfs 的过程中计算这个可能略微麻烦。比较巧妙的方法是，将二分的上界设为**最小的点 $u$ 连接的最小的两条边的边权和**。即，设点 $u$ 连接的 $k$ 条边**从小到大排序后**边权依次为 $w_{u,1},w_{u,2},\ldots,w_{u.k}$，那么二分的上界是 $\min\limits_{u=1}^n\{w_{u,1}+w_{u,2}\}$。这样我们保证了答案一定小于等于任意两条边的和，即满足了上述条件。

我们先给边排序，然后 check 用 bfs 实现。假设 $n,m$ 同阶，总时间复杂度 $\mathcal O(n \log (nV))$。

**【代码】**

注意只考虑边权小于 $x$ 的边时图可能不连通。

二分时 mid 要开 long long，否则会 TLE $19$ 个点。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e5+5;
int t,n,m,u,v,w,col[maxn],mn = 2e9+7;
vector<pair<int,int>> g[maxn];
bool bfs(int s,int x){
    queue<int> q;
    q.push(s),col[s] = 0;
    while(!q.empty()){
        int u = q.front();q.pop();
        for(auto [w,v] : g[u]){
            if(w >= x) continue;
            if(col[v] == -1) col[v] = col[u] ^ 1,q.push(v);
            else if(col[u] == col[v]) return 0;
        }
    }return 1;
}bool ck(int x){
    memset(col,-1,sizeof(col));
    for(int i = 1;i <= n;i ++){
        if(col[i] != -1) continue;
        if(!bfs(i,x)) return 0;
    }return 1;
}
int main(){
    cin >> n >> m;
    for(int i = 1;i <= m;i ++) cin >> u >> v >> w,g[u].emplace_back(w,v),g[v].emplace_back(w,u);
    for(int i = 1;i <= n;i ++) sort(g[i].begin(),g[i].end());
    for(int i = 1;i <= n;i ++) if(g[i].size() >= 2) mn = min(mn,g[i][0].first + g[i][1].first);
    int l = 0,r = mn;
    while(l <= r){
        int mid = (1ll * l + 1ll * r) / 2;
        if(ck(mid)) l = mid + 1;
        else r = mid - 1;
    }cout << l - 1;
}
```

---

## 作者：MSavannah (赞：0)

**Solution**

先考虑树怎么做，显然黑白交错染色是最优的。

我们试着把它扩展到图上，发现对于每一条边，如果它的两个端点颜色相同，那么它一定是长度最短的路径。为了让 $X$ 尽可能大，我们要让边权小的边的两端颜色错开。进而想到可以先搞出个最小生成树然后对它染色。对于不在生成树上的边，我们判断它的端点是否同色然后更新答案，在生成树上的边，注意到染色后树上距离为 $2$ 的两个点一定同色，那么就记录一下每个点连出边的最大值和次大值更新答案就好了。

[code](https://www.luogu.com.cn/record/176021107)

---

## 作者：Supor__Shoep (赞：0)

首先不难想到二分答案，因此问题转换为判定 $p$ 是否为一个可行的答案。

设当前二分的答案为 $p$。我们要**尽可能地满足条件**，因此如果有一条边 $(x,y)$ 的边权 $w$ 满足 $w<p$，我们就需要让 $x,y$ 染上不同的颜色。原因显然：如果 $x,y$ 的颜色相同，那么它们的一条简单路径就是这条边，长度满足 $w<p$，就不满足条件了。而对于 $w≥p$ 的边，我们怎样染色都是符合条件的，因此不必去大费周章地想染色方案。

手玩一下可以发现，若存在连边 $(x,y),(y,z),(x,z)$ 满足其边权小于 $p$，那么这三条边的两端就应该染色不同的颜色，但是颜色只有两种，因此不能满足【三条边的两端染色不同】的条件。那么很明显，对于 $p$ 的这一个答案是不可能有满足条件的染色方案的。具体实现方式可以使用**扩展域并查集**，不会扩展域的建议先去学习一下。

然而这还没有结束。如果有两条边 $(x,y),(y,z)$，设边权分别为 $w_1,w_2$，若 $w_1<p$ 且 $w_2<p$ 且 $w_1+w_2<p$，由于两端颜色不能相同，那么 $x,z$ 的颜色就一定是相同的，此时就算按照最优的方案染色也不能满足条件。因此如果出现这种情况也说明 $p$ 不是合法的答案。

具体实现比较简单，我们删去边权大于等于 $p$ 的边，在**剩下的边构成的图中**，我们记录 $min1_x$ 表示连接了 $x$ 的剩下所有边中边权最小的边权，$min2_x$ 记录次小值。对于相邻的两个点 $x,y$，设 $(x,y)$ 的边权为 $w$。若 $w=min1_y$，则比较 $w+min2_y<p$，否则比较 $w+min1_y<p$。当然这种方式针对的是有向边，对于无向边 $(x,y)$，我们先从 $x$ 到 $y$，再从 $y$ 到 $x$ 就可以了。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+5;
int fa[MAXN<<1];
int n,m;
int xx[MAXN],yy[MAXN],zz[MAXN];
int find(int x)
{
	if(fa[x]==x)	return x;
	return fa[x]=find(fa[x]);
}
void work(int x,int y)
{
	x=find(x),y=find(y);
	if(x!=y)	fa[x]=y;
}
int min1[MAXN],min2[MAXN];
void solve(int x,int z)
{
	if(min1[x]==1e9)	min1[x]=z;
	else if(min2[x]==1e9)	min2[x]=max(min1[x],z),min1[x]=min(min1[x],z);
	else
	{
		if(z<min1[x])	min2[x]=min1[x],min1[x]=z;
		else if(z<min2[x])	min2[x]=z;
	}
}
int judge(int x,int y,int z,int mid)
{
	if(min2[y]==1e9)	return 1;
	if(min1[y]==z)	return min2[y]+z>=mid;
	return min1[y]+z>=mid;
}
int check(int x)
{
	for(int i=1;i<=n;i++)	fa[i]=i,fa[i+n]=i+n,min1[i]=min2[i]=1e9;
	for(int i=1;i<=m;i++)
	{
		if(zz[i]<x)
		{
			if(find(xx[i]+n)==find(yy[i]+n)||find(xx[i])==find(yy[i]))	return 0;
			work(xx[i],yy[i]+n),work(xx[i]+n,yy[i]);
		}
	}
	for(int i=1;i<=m;i++)
	{
		if(zz[i]<x)	solve(xx[i],zz[i]),solve(yy[i],zz[i]);
	}
	for(int i=1;i<=m;i++)
	{
		if(zz[i]<x)
		{
			if(!judge(xx[i],yy[i],zz[i],x))	return 0;
			if(!judge(yy[i],xx[i],zz[i],x))	return 0;
		}
	}
	return 1;
}
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)	cin>>xx[i]>>yy[i]>>zz[i];
	int l=0,r=2e9,res=0;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(check(mid))	res=mid,l=mid+1;
		else	r=mid-1;
	}
	cout<<res;
	return 0;
}
```

---

## 作者：Demeanor_Roy (赞：0)

- 怎么都在二分答案，来个直接了当的做法。

------------

看到黑白染色，不管三七二十一先按二分图染色考虑再说。

不难发现，若给定的图是二分图，按二分图染色得到的答案为**图上所有三个点的路径长度最小值**。

这是二分图答案的上界吗？显然是。证明考虑图上任意三个点的的路径，它们必有两个点同色，故答案不超过图上任意三个点的的路径的长度，得证。

现在考虑非二分图，显然奇环上必有相邻同色点。故答案又有了一个新的上界：所有奇环边权最大值的最小值。

我们来证明这个上界可以取到。考虑先将所有奇环**边权最大的边所连点染同色，其余间隔染色**，这是可以做到的，因为奇环之间的嵌套不会影响我们的染色。然后你将剩下的边连上，如果你发现边两点同色，就对一个点所在奇环进行黑白互换。最终得到的图就符合我们的要求。

考虑如何得到所有奇环边权最大值的最小值，将边按边权从小到大排序，在并查集判二分图时，若发现连上这条边会出现奇环，就将上界与当前边权取 $\min$，并取消连边即可。

[代码](https://atcoder.jp/contests/arc165/submissions/45792008)

---

## 作者：Zelotz (赞：0)

转化题意，对图进行黑白染色，求最大的 $X$ 满足所有 $u, v$ 间最短路径小于 $X$ 的 $u, v$ 异色。

很明显是二分答案，假设现在二分到 $mid$，转化为判定型问题。

直接 $n^2$ 枚举点肯定不对。

发现性质：如果 $u,v$ 的最短路径长度小于 $X$ 且最短路径上经过的边数大于 $1$，则一定无法染色。

所以对于所有由两条边组成的路径的最小值应该为二分上界 $r$。

确定上界后，只需考虑所有由一条边组成的最短路，即所有边权小于 $X$ 的边拿出来进行二分图判定。

这样拿出来的边一定是最短路，否则二分上界一定比它小。

本题巧妙运用了二分上界，使得 $\rm check$ 函数能在正确复杂度内执行。

```
#define int ll
typedef pair<int, int> PII;
const int N = 2e5 + 5; 
int n, m, mx[N], smx[N]; // 含义相反因为之前写成最大值了
vector <PII> E[N];
int color[N];
bool dfs(int x, int mid, int col)
{
	// cout << x << ' ' << color[x] << "!!!\n";
	if (~color[x]) return color[x] == col;
	color[x] = col;
	for (auto v : E[x])
	{
		if (v.second >= mid) continue;
		if (!dfs(v.first, mid, col ^ 1)) return 0;
	}
	return 1;
}
bool chk(int mid)
{
	R(i, 1, n) color[i] = -1;
	// cout << color[1] << '\n';
	bool res = 1; 
	R(i, 1, n) if (color[i] == -1) if (!dfs(i, mid, 0)) return false; //cout << i << ' ' <<res << endl;
	return true;
}
void solve()
{
	cin >> n >> m;
	int l = 1, r = INT_MAX;
	R(i, 1, n) mx[i] = smx[i] = INT_MAX;
	R(i, 1, m)
	{
		int u, v, w; cin >> u >> v >> w;
		E[u].pb({v, w}); E[v].pb({u, w});
		if (w < mx[u]) smx[u] = mx[u], mx[u] = w;
		else if (w < smx[u]) smx[u] = w;
		if (w < mx[v]) smx[v] = mx[v], mx[v] = w;
		else if (w < smx[v]) smx[v] = w;
	}
	R(i, 1, n) 
	{
		if (smx[i] == INT_MAX) continue;
		r = min(r, (mx[i] == INT_MAX ? 0 : mx[i]) + (smx[i] == INT_MAX ? 0 : smx[i])); 
		// cout << mx[i] << ' ' << smx[i] << endl;
		// cout << r << endl;
	}
	while (l < r)
	{
		int mid = l + r + 1 >> 1;
		if (chk(mid)) l = mid;
		else r = mid - 1;
	}
	cout << l << endl;
}
signed main() 
{
	int T = 1; 
	// read(T); 
	while (T--) solve();
    return 0;
}
```



---

## 作者：another_world (赞：0)

### 题目链接：[ARC 165-C](https://atcoder.jp/contests/arc165/tasks/arc165_c)


------------

### 法1：二分答案
1.  考虑二分枚举答案. 

2.  删去所有权值 $\ge mid$ 的边，经过这些边的路径一定会满足条件.

3.  剩下的边的权值 $<mid$，也就是说这些边的**两端必须是不同颜色的点**，否则一定不满足任意其答案条件.

4.  由此，长度最短的路径是由两条边组成的(颜色间隔分布)，因此只需要枚举所有**长度为 $2$** 的最短路径，与 $mid$ 进行比较. 

5.  最后虽然我们期望的是间隔分布，但这不是一定可以实现，有时两个相邻点一定是同种颜色(存在**奇环**)，这种时候一定不成立.

- **总结**：寻找最大的 $mid$，使其满足 $(4)$ ，且其余权值 $<mid$ 的边构成二分图.

------------
### 法2：边权值升序插入
- 继续思考 $(2)(3)(4)(5)$ 发现，答案无非是 原图所有**长度为 $2$ 的最短路径** $or$ 将所有边按**权值升序依次添边**，若当前边的添加使成为非二分图(存在奇环)，则为当前边权值.

------------
### Code：
 
```cpp
#include<bits/stdc++.h>
using namespace std; 
typedef long long ll;
#define inf 2e9+10
#define mkp make_pair
#define fir first
const int N=2e5+10;
int n,m,minn=inf,f[N*2];
struct EDGE { int u,v,w; } edge[N];
vector<pair<int,int> > path[N*2];
inline bool cmp(EDGE a,EDGE b) { return a.w<b.w; }
int get(int x) {
	if(x==f[x]) return x;
	return f[x]=get(f[x]);
}
void path_min() { // 寻找长度为 2 的最短路径 
	for(int u=1; u<=n; u++) {
		sort(path[u].begin(),path[u].end());
		if(path[u].size()>1) {
			minn=min(minn,path[u][0].fir+path[u][1].fir); 
		}
	}
}
int main() {
    scanf("%d%d",&n,&m);
    for(int i=1; i<=n*2; i++) f[i]=i;
	for(int i=1; i<=m; i++) {
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		path[x].push_back(mkp(z,y));
		path[y].push_back(mkp(z,x));
		edge[i]=(EDGE){x,y,z};
	}
	path_min();
	sort(edge+1,edge+m+1,cmp);
	int ans=inf;
	for(int i=1; i<=m; i++) {
		int x=edge[i].u,y=edge[i].v;
		if(get(x)==get(y)) { // 并查集判断二分图 
			ans=edge[i].w;
			break;
		}
		f[get(x)]=get(y+n),f[get(x+n)]=get(y); 
	}
	printf("%d",min(minn,ans));
	return 0;  
}
```


---

