# Light Bulbs (Hard Version)

## 题目背景

这道题的简单版和困难版仅在 $ n $ 的约束条件上有所不同。在困难版中，所有测试用例的 $ n $ 之和不超过 $ 2 \cdot 10^5 $ 。此外，单个测试用例中的 $ n $ 没有额外限制。

## 题目描述

有 $ 2n $ 个灯泡排成一行。每个灯泡的颜色是 $ 1 $ 到 $ n $ 中的一个（每种颜色恰好有两个灯泡）。  
最初，所有灯泡都是关闭的。你需要选择一个初始打开的灯泡集合 $ S $。之后，你可以按任意顺序执行以下操作任意次数：  
- 选择两个颜色相同的灯泡 $ i $ 和 $ j $，且其中一个打开、另一个关闭，然后将关闭的灯泡打开；  
- 选择三个灯泡 $ i, j, k $，满足 $ i $ 和 $ k $ 是打开的且颜色相同，且灯泡 $ j $ 位于它们之间（即 $ i < j < k $），然后将灯泡 $ j $ 打开。  
你的任务是选择一个初始打开的灯泡集合 $ S $，使得通过执行上述操作，可以确保所有灯泡最终都被打开。

你需要计算两个数值：  
- 初始集合 $ S $ 的最小大小；  
- 满足最小大小的集合 $ S $ 的数量（结果对 $ 998244353 $ 取模）。

## 说明/提示

翻译由 [yanrs1019](https://www.luogu.com.cn/user/1304706) 提供。

## 样例 #1

### 输入

```
4
2
2 2 1 1
2
1 2 2 1
2
1 2 1 2
5
3 4 4 5 3 1 1 5 2 2```

### 输出

```
2 4
1 2
1 4
2 8```

# 题解

## 作者：Erica_N_Contina (赞：8)

## 思路

异或哈希。

需要注意的点：对于序列 `1 2 3 2 1 3` 只需要 $1$ 次操作。我们点亮一个 $1$，那么其会将两个 $1$ 里面的 `2 3 2` 都点亮。点亮了 $3$ 就代表着最右边的 $3$ 也被点亮了。

---

我们考虑一种特殊的序列，其满足序列中的每个数字的个数都是偶数。我们称之为**偶数序列**。如果一个偶数序列不能拆分成多个子偶数序列，那么我们称这个偶数序列为**最小偶数序列**。

那么最小偶数序列的性质是什么呢？

我们发现，一个最小偶数序列中只需要点亮一盏灯就可以让其他灯点亮。这个很好证明，发现无法举出反例，特别是很多反例无法满足**最小**。

可是一个最小偶数序列中的那个被点亮的灯也不是随便选的，它要满足一定的限制。

考虑以下定义：我们在上面定义的最小偶数序列仅仅是在“并列”层面进行了限制，但是没有在“嵌套”层面做出限制。事实上，一个最小偶数序列中可能包含另一个最小偶数序列（`1 2 2 1` 就是一个很好的例证）。所以我们在划分序列时，我们会吧 `1 2 2 1` 看出是一个最小偶数序列。但我们很显然可以发现中间的两个 $2$ 是不可能成为被点亮的灯的。

我们将序列划分后产生的最小偶数序列中，对于每个最小偶数序列，如果其内还包含了又一个或者多个最小偶数序列，那么我们将这些被包含的序列称为**最小偶数子序列**。那么结合上面的说明，我们在选择一个最小偶数序列中被点亮的那个灯时，不可以选择最小偶数子序列中的灯。

---

根据题目的要求，序列一定可以划分成若干个最小偶数序列，又因为不可能出现无解的情况，所以将序列划分为最小偶数序列的方法是最优的方法。

对于求最小可能的 $S$ 集合大小，我们只需要求出序列中有几个最小偶数序列即可。

对于求出情况数，我们可以使用乘法原理，但是要先剔除每个最小偶数序列中的最小偶数子序列中的灯。

## 实现

那么我们怎么样划分最小偶数序列呢？偶数的性质是什么呢？

我们可以想到，用 $res=0$ 异或偶数次的一个数字 $x$，结果还是 $0$。我们利用这个性质，对序列中的每一个数字的值分配一个独一无二的数字 $h_i$（即值相同，其 $h_i$ 也相同），从前往后扫描一遍即可。

对于剔除每个最小偶数序列中的最小偶数子序列中的灯，我们先抽离出每一个最小偶数序列。然后考虑对于一个最小偶数序列，我们从前往后按上面的方法扫描，并且记录一个桶。如果当前 $res$ 在桶中有值 $id$，那么 $id\sim i$（$i$ 是当前 $res$ 所在的位置）就是一个最小偶数子序列。

---

代码就不放了，和官方题解很像。



---

## 作者：未来姚班zyl (赞：6)

## 题目大意

有一个长度为 $2n$ 的带颜色序列，颜色 $1\sim n$ 各出现两次，初始你可以标记任意点集 $S$。

然后，你可以不断进行两个操作。

 1. 选择一个颜色，如果其中一个数被标记了，标记另一个数。
 
 2. 选择一个颜色，两个数都被标记了，标记中间的数。
 
如果要标记所有的数，求 $|S|$ 的最小值即此时的 $S$ 的可能个数。

## 题目分析

这道题一眼就**非常图论**。由于一操作的存在，我们只用考虑颜色和颜色之间的关系，故把每种颜色抽象成点。

如果颜色 $A$ 可以通过 2 操作染色颜色 $B$，则 $A$ 向 $B$ 连边。

那么问题变成了，在一个有向图中，你可以标记若干个点，要求每个点都可以由被标记的点达到。

缩点后图变为 DAG，显然只需要标记入度为 $0$ 的强连通分量，每个强连通分量内只需标记一个点，最小数量和方案数就求完了。

边数是 $O(n^2)$ ,能过 easy version。

注意到加边是对序列上的一个区间加边，线段树优化建边即可做到复杂度线性对数。

这里可能会有线段树节点组成的强连通分量，不过没关系，直接拓扑排序就能解决。

官方的做法也好牛啊，感觉这题都能下位紫了。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L (x<<1)
#define R (L|1)
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define OK Ll<=l&&r<=Rr
#define Root 1,1,n
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
bool S;
const int N =4e5+5,M=2.5e6+5,inf=(1LL<<31)-1,mod=998244353;
const ll llf=1e18;
inline void add(int &a,int b){((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,int b){if(!b)return 1;int c=qp(a,b>>1);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
int n,c[N];
struct node{
    int l,r;
}a[N];
int h[M],to[M<<1],nxt[M<<1],cnt;
inline void add_(int a,int b){
    //cerr<<a<<' '<<b<<'\n';
    to[++cnt]=b,nxt[cnt]=h[a],h[a]=cnt;
}
inline int id(int i){
    return i+n*4;
}
inline void build(int x,int l,int r){
    if(l==r)return add_(x,id(c[l])),void();
    add_(x,L),add_(x,R),build(lc),build(rc);
}
inline void modify(int x,int l,int r,int Ll,int Rr,int fr){
    if(Ll>Rr)return;
    if(OK)return add_(fr,x),void();
    if(Ll<=mid&&Rr>=l)modify(lc,Ll,Rr,fr);
    if(Ll<=r&&Rr>mid)modify(rc,Ll,Rr,fr);
}
int dfn[M],Time,rd[M],low[M],bel[M],s[M],tp,tot,Sz[M],siz[M];
bool instac[M];
vector<int>p[M];
bool vis[M];
inline void tarjan(int x){
    dfn[x]=low[x]=++Time,s[++tp]=x,instac[x]=1;
    e(x)if(!dfn[y])tarjan(y),low[x]=min(low[x],low[y]);
    else if(instac[y])low[x]=min(low[x],dfn[y]);
    if(dfn[x]==low[x]){
        tot++;
        for(int z=s[tp--];;z=s[tp--]){
            instac[z]=0,bel[z]=tot;
            if(z>n*4)Sz[tot]++;
            if(z==x)break;
        }
    }
}
inline void clear(){
    repn(i)a[i].l=a[i].r=0;
    rep(i,1,n*5)h[i]=dfn[i]=Sz[i]=instac[i]=rd[i]=0;
    rep(i,1,tot)p[i].clear(),vis[i]=0;
    cnt=tot=0;
}
inline void bfs(){
    int ans=0,sum=1;
    queue<int>q;
    rep(i,1,tot)if(!rd[i]){
        if(Sz[i])ans++,Mul(sum,mul(2,Sz[i])),vis[i]=1;
        q.push(i);
    }
    while(!q.empty()){
        int x=q.front();q.pop();
        E(x){
            rd[y]--;
            if(vis[x])vis[y]=1;
            if(!rd[y]){
                if(!vis[y]&&Sz[y])vis[y]=1,ans++,Mul(sum,mul(2,Sz[y]));
                q.push(y);
            }
        }
    }
    cout <<ans<<' '<<sum<<'\n';
}
bool t;
inline void Main(){
    n=read(),n<<=1;
    repn(i)c[i]=read(),a[c[i]].l?a[c[i]].r=i:a[c[i]].l=i;
    build(Root);
    rep(i,1,n>>1)modify(Root,a[i].l+1,a[i].r-1,id(i));
    tp=0;
    tarjan(1);
    rep(x,1,id(n/2))e(x)if(bel[x]^bel[y]){
        p[bel[x]].pb(bel[y]),rd[bel[y]]++;
    }
    bfs();
    clear();
}
int T;
signed main(){ 
    T=read();
    while(T--)Main();
    return 0;
}
```


---

## 作者：Eibon (赞：4)

对样例进行分析，不难发现，可以将区间分成一块块，每一块由一些相交的相同数字对构成。

当两个数字对区间包含时，小的区间显然不必要点亮。

否则当它们相交时，点亮其中任何一个即可，相当于将整个块点亮。

即，最后块的数量即为第一个答案。

判断一个数是否出现偶数次，可以使用异或哈希。

考虑如何统计答案二。

不妨开一个 map，记录最后一个某哈希值 $cur_{i}$ 出现的位置 $lst_{cur_{i}}$。

对每一个前缀异或哈希和为 $0$，即块的端点 $i$，我们从它的下一个点 $i+1$ 即 $j$ 开始跳，每次跳到 $lst_{cur_{j}}+1$，即下一个区间相交的位置，跳到 $cur_{j}$ 为 $0$ 即块的另一个端点停止。可以避免算到中间异或和为 $0$ 的块，因为中间跳得到的 $cur_{j}$ 都不等于 $0$。

这样，我们把每一个闭区间的贡献乘一起，就可以得到第二问的答案。


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=4e5+5;
const int mod=998244353;
int T=1,n,ans1,ans2;
int w[maxn],cur[maxn];
map<int,int>lst;
mt19937_64 rnd(random_device{}());
int get()
{
	int x=0;
	while(!x){
		x=rnd();
	}
	return x;
}
int Add(int x,int y){return ((x+y)%mod+mod)%mod;}
int Mul(int x,int y){return x*y%mod;}
void solve()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		w[i]=get();
	}
	lst.clear();
	ans1=0;ans2=1;
	for(int i=1;i<=2*n;i++){
		int x;
		scanf("%lld",&x);
		cur[i]=cur[i-1]^w[x];
		lst[cur[i]]=i;
		if(!cur[i]){
			ans1++;
		}
	}
	for(int i=0;i<2*n;i++){
		if(cur[i]){
			continue;
		}
		int j=i+1,res=1;
		while(cur[j]){
			j=lst[cur[j]]+1;
			res++;
		}
		ans2=Mul(ans2,res);
	}
	printf("%lld %lld\n",ans1,ans2);
}
signed main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	scanf("%lld",&T);
	while(T--){
		solve();
	}
	return 0;
}
//dyyyyds
```

---

## 作者：Mirage_Insane (赞：2)

来一个不需要什么思维含量的解法。

考虑记录颜色 $i$ 的两次出现位置分别为 $L_i$ 和 $R_i$。显然我们可以从 $i$ 出发，向 $L_i + 1$ 到 $R_i - 1$ 的所有颜色连边以表示选择 $i$ 后这些颜色也都会被选择。

然后缩点跑拓扑。显然入度为 0 的连通分量内部必须要选一个点，这样的话方案数也好算。

回顾上面的思路，发现只需要一个线段树优化建图就行了。

[线段树优化建图模板](https://www.luogu.com.cn/problem/CF786B)。

其实这玩意儿也不是很难，但是真的挺常用的，建议学一学。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define SF scanf
#define PF printf
struct Tree {
    int lson, rson;
}tree[400005 << 2];
int a[400005], root, tot;
struct Edge {
    int to, nxt;
}edge[20000005];
int head[5000005], cnt;
void add(int u, int v) {
    edge[++cnt].to = v;
    edge[cnt].nxt = head[u];
    head[u] = cnt;
}
void make_tree(int &i, int l, int r) {
    if(i == 0) i = ++tot;
    if(l == r) {
        add(i, a[l]);
        return;
    }
    int mid = l + r >> 1;
    make_tree(tree[i].lson, l, mid), make_tree(tree[i].rson, mid + 1, r);
    add(i, tree[i].lson), add(i, tree[i].rson);
}
void update(int i, int l, int r, int x, int ql, int qr) {
    if(ql > qr) return;
    if(ql <= l && r <= qr) {
        add(x, i);
        return;
    }
    int mid = l + r >> 1;
    if(mid >= ql) update(tree[i].lson, l, mid, x, ql, qr);
    if(mid + 1 <= qr) update(tree[i].rson, mid + 1, r, x, ql, qr);
}
void clear(int &i, int l, int r) {
    if(l == r) {
        i = 0;
        return;
    }
    int mid = l + r >> 1;
    clear(tree[i].lson, l, mid), clear(tree[i].rson, mid + 1, r);
    i = 0;
}
int n, L[400005], R[400005], dfn[5000005], Num, low[5000005], scc[5000005], num[5000005], scccnt, in[5000005];
stack<int> st;
void tarjan(int x) {
    dfn[x] = low[x] = ++Num;
    st.push(x);
    for(int i = head[x]; i; i = edge[i].nxt) {
        int to = edge[i].to;
        if(!dfn[to]) {
            tarjan(to);
            low[x] = min(low[x], low[to]);
        }
        else if(!scc[to]) low[x] = min(low[x], dfn[to]);
    }
    if(dfn[x] == low[x]) {
        scccnt++;
        int k;
        do {
            k = st.top();
            st.pop();
            num[scccnt] += (k <= n);
            scc[k] = scccnt;
        }while(k != x);
    }
}
vector<int> g[5000005];
int main() {
    int T;
    SF("%d", &T);
    while(T--) {
        SF("%d", &n);
        for(int i = 1; i <= n * 2; i++) {
            SF("%d", &a[i]);
            if(L[a[i]]) R[a[i]] = i;
            else L[a[i]] = i;
        }
        tot = n;
        make_tree(root, 1, n * 2);
        for(int i = 1; i <= n; i++) update(root, 1, n * 2, i, L[i] + 1, R[i] - 1);
        for(int i = 1; i <= tot; i++) {
            if(!dfn[i]) tarjan(i);
        }
        // for(int i = 1; i <= tot; i++) cout << scc[i] << " ";
        // cout << endl;
        for(int i = 1; i <= tot; i++) {
            for(int j = head[i]; j; j = edge[j].nxt) {
                int to = edge[j].to;
                // cout << i << "->" << to << " " << scc[i] << "->" << scc[to] << endl;
                if(scc[i] != scc[to]) in[scc[to]]++, g[scc[i]].push_back(scc[to]);
            }
        }
        int ans1 = 0, ans2 = 1;
        queue<int> q;
        for(int i = 1; i <= scccnt; i++) {
            if(in[i] == 0) q.push(i);
        }
        while(!q.empty()) {
            int tmp = q.front();
            q.pop();
            if(num[tmp]) {
                ans1++, ans2 = 1ll * ans2 * num[tmp] * 2 % 998244353;
                continue;
            }
            for(int to : g[tmp]) {
                if(--in[to] == 0) q.push(to);
            }
        }
        PF("%d %d\n", ans1, ans2);
        for(int i = 1; i <= n; i++) L[i] = R[i] = 0;
        clear(root, 1, n * 2);
        for(int i = 1; i <= tot; i++) head[i] = dfn[i] = low[i] = scc[i] = 0;
        tot = Num = cnt = 0;
        for(int i = 1; i <= scccnt; i++) num[i] = in[i] = 0, g[i].clear();
        scccnt = 0;
    }
    return 0;
}
```

---

## 作者：Fubaogege (赞：2)

## 题目大意及题解
对集合 $S$ 进行初始染色，只需要遵循以下两条规则就行：

- 如果一个数被染色了，则另一个相同的数也会被染色。
- 如果某两个相同的数被染色了，那么它们之间所有数都会被染色。

求出：

- 你要求出最小可能的 $S$ 集合大小使得所有数都被染色，并且求出有多少 $S$ 满足其大小到达最小。
- 结果对 $998244353$ 取模。

简化：我们只需按题目要求求出 $S$ 就行。

- 你可以标注一些点，要求每个点都可以由被标记的点达到。
- 使用扩展排序。
- 对一个区间加边，优化建边。

完结撒花。

---

## 作者：_Ink (赞：1)

官方的 std 做法是哈希+前缀异或处理。对此有需求的可以去 [CF官方题解](https://codeforces.com/blog/entry/123530) 下面看。

本处要介绍的是另一种相对不太难想，但比较难写的做法。

## 题解

我们可以考虑把原问题转化为一个图论问题。

如果数 $u$ 被染色，可以使得数 $v$ 也被染色，那么我们就连一条 $u$ 到 $v$ 的有向边表示这种关系。  

对于一个数 $k$，若其在集合中出现的位置为 $l_k, r_k$，那么将 $k$ 染色便可以使得区间 $[l_k+1, r_k-1]$ 内的所有数被染色。也就是说，我们可以把 $k$ 连向区间 $[l_k+1, r_k-1]$ 内的所有数。这样建图部分就完成了。  

怎么求得答案呢？不难发现，建图完成后，整个图被分为了数个连通块，并且每个连通块中，至少有一个点可以到达连通块中的所有点。那么最少需要染色的数的个数 即为连通块的个数。

对于要求的第二个答案，我们可以发现：对于一个连通块中，有一些点是不能到达全部的点的，这些点显然不能对答案产生贡献。而这些点都需要通过其他点来到达它们，所以这些不满足要求的点入度都不为 0。

可这样的条件是充分不必要的，满足要求的点入度也不一定为 0。但满足要求的点一定能到达其他所有点，如果其入度不为 0，那么它甚至能从其他点再到达到自己。换言之，这些满足要求的点**一定在一个强连通分量内**。

所以就可以考虑缩点了。缩完点后，这下入度为 0 的点就一定是满足要求的点了。我们只需要统计每个连通块中，缩点后入度为 0 的点的大小（大小即缩点前强连通分量包含了几个点），根据乘法原理，将这些值乘起来就是答案了。  

---

然而实际上，直接执行上述方案只能过这题的简单版本。因为如果我们暴力建边，将一个点与一个区间内的所有点建边，其复杂度是 $O(n^2)$ 的。

考虑优化这一过程。图论建模的区间建边，就需要用到线段树优化这个 trick 了。本处不对此作过多介绍，不会的同学可以移步网上 blog 或者[本题](https://www.luogu.com.cn/problem/CF786B)学习。优化过后，建边的复杂度可以降至 $O(n\log n)$。

优化建边会有一些实现上细节。我们仍然无法让某个数点直接连接某个区间内的所有数点，只能连接这些数所在的位置（也就是连接一个区间）。所以我们可以考虑把每个数所在位置抽象成 $2n$ 个点，然后把这些点连向对应的数点即可。

然后，在线段树优化建图后，所有的连通块都连在了一起，这也会影响统计答案的过程。

实际上，你可以把它看作有一个超级源点连接了所有的连通块，这个超级源点就是线段树的根。然后把**所有的数点**大小设为 1，在缩点后，我们拓扑处理整个图。当你第一次进入一个“有大小”的点时，也就是等同于进入了一个新连通块中入度为 0 的点。

按照上述统计方法统计即可。

---

## 作者：impuk (赞：1)

前排提醒，不是正解。刚板子贴到 cf 了我也贴板子我很喜欢贴板子。

先考虑求出最小值。很显然有一个正确的贪心是每次挑选最左边的没亮的灯，然后把所有可能灯弄亮，再选最左边的，直到计算出答案。

证明过程属于 G1 的内容，这里略去。

随后考虑优化，发现对于一个颜色 $i$ 的灯泡，其两个位置 $[l_i,r_i]$ 恰好可以构成一个区间，也就是说，如果 $i$ 被点亮了，那么整个区间都会被点亮，并且区间内还有对应的区间，以此类推。

这不是我们线段树优化建图板子吗？先把线段树优化建图板子贴上，然后对每个颜色都给 $[l_i,r_i]$ 连上，到这里是 $O(n\log n)$ 的。

对于一个图里的连通块，只要和连通块对应的边界能互达的，都是可能的答案。而不能互达的，选了就是亏了的，因为还要一个额外的步数去把边界点亮。

处理图上的互达信息，这就是经典的 SCC 内容，于是把 SCC 板子一贴，然后把所有连通块答案乘起来，就做完了。

```
#include"bits/stdc++.h"
using namespace std;
#pragma GCC optimize("Ofast","inline","-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#define MOD 998244353
namespace SCC {
   vector<vector<int>> graph,ugraph;
   void clear(int n){graph.clear();graph.resize(n+1);ugraph.clear();ugraph.resize(n+1);};
   void addedge(int u,int v){graph[u].push_back(v);ugraph[v].push_back(u);}
   vector<vector<int>> kosaraju(){vector<vector<int>>answer;vector<bool>vis(graph.size(),false);vector<int>vst;function<void(int)>dfs1=[&](int x){if(vis[x])return;vis[x]=true;for(int i:graph[x])dfs1(i);vst.push_back(x);};for(int i=1;i<(int)graph.size();++i)dfs1(i);reverse(vst.begin(),vst.end());function<void(int)>dfs2=[&](int x){if(!vis[x])return;vis[x]=false;answer.end()[-1].push_back(x);for(int i:ugraph[x])dfs2(i);};for(int i:vst)if(vis[i]){answer.push_back({});dfs2(i);}return answer;}
}
vector<int> b[400001];
int a[400001],n,flag[400001],qid[1000001];
int build(int l,int r,int &cnt,int val) {
	if(l==r) return l;
	cnt++;int id=cnt;qid[val]=cnt;
	int m=(l+r)/2;
	int left=build(l,m,cnt,val*2);
	int right=build(m+1,r,cnt,val*2+1);
	SCC::addedge(id,left);
	SCC::addedge(id,right);
	return id;
}
void interval(int l,int r,int L,int R,vector<int>& ans,int val) {
	if(L<=l&&r<=R) {
		ans.push_back(l!=r?qid[val]:l);
		return;
	}
	int m=(l+r)/2;
	if(L<=m) interval(l,m,L,R,ans,val*2);
	if(R>m)  interval(m+1,r,L,R,ans,val*2+1);
}
vector<int> interval(int l,int r) {
	vector<int> ans;
	interval(1,2*n,l,r,ans,1);
	return ans;
}
void _() {
	cin >> n;
	for(int i=1;i<=n;++i) {b[i].clear();flag[i]=0;}
	for(int i=1;i<=2*n;++i) {cin >> a[i];b[a[i]].push_back(i);}
	SCC::clear(4*n);
	{int cnt=2*n;build(1,2*n,cnt,1);}
	for(int i=1;i<=n;++i) {
		SCC::addedge(b[i][0],b[i][1]);
		SCC::addedge(b[i][1],b[i][0]);
		for(int j:interval(b[i][0],b[i][1])) SCC::addedge(b[i][0],j);
		cerr << endl;
	}
	vector<vector<int>> ans=SCC::kosaraju();
	int ans1=0,ans2=1;
	set<int> inter;
	for(int i=1,s=0,l=1;i<=2*n;++i) {
		flag[a[i]]^=1;
		if(flag[a[i]]) s++;
		else s--;
		if(s==0) {
			ans1++;
			inter.insert(l);
			inter.insert(i);
			l=i+1;
		}
	}
	for(vector<int> i:ans) {
		int s=0;
		for(int j:i) 
			if(j<=2*n)
				s++;
		for(int j:i)
			if(inter.count(j)) {
				ans2=(long long)ans2*s%MOD;
				break;
			}
	}
	cout << ans1 << ' ' << ans2 << '\n';
}
signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T=1;cin >> T;
	while(T--) _();
}

```

---

## 作者：Supor__Shoep (赞：0)

提供一个非常另类的解法，没有异或哈希，没有建图，没有缩点和强连通分量，而是使用了并查集和线段树的算法。

由于每个颜色恰好有两种，我们考虑把两个颜色的位置 $i,j$ 变成一段区间 $[i,j]$（$i<j$），然后每个颜色就能用一段区间 $[l,r]$ 表示。

根据题意，如果我们激活了一个区间 $[l,r]$，那么对于所有 $l'\in (l,r)\wedge r'>r$ 的，或者 $r'\in (l,r)\wedge l'<l$ 的区间 $[l',r']$，它们都会被自动激活。我们的目标就是激活最少的区间去覆盖 $[1,2n]$ 这个大的区间。

考虑使用**并查集**，把相交但不包含的任意两个区间合并到一个集合里面，即若 $[l_i,r_i]∩[l_j,r_j]\not= \varnothing$ 且 $[l_i,r_i],[l_j,r_j]$ 之间不存在包含关系，则把下标 $i,j$ 合并。合并了所有 $(i,j)$ 之后，我们发现对于一个集合 $S$，当我们激活了 $S$ 中的任意一个区间 $[l,r]$，那么 $S$ 的所有区间也必然都会被一起激活。也就是说，设 $S$ 中所有区间的并区间为 $[L,R]$，我们覆盖 $[L,R]$ 就只需要随意激活 $S$ 的任意一个区间。

由于题目保证了所有区间的并一定是 $[1,2n]$，要保证激活区间最少，我们只需要在不同的集合中各选择一个区间。但是有一种特殊情况，对于两个集合的区间并 $[L,R],[L',R']$，如果有 $L<L'<R'<R$，那么我们就只需要激活 $[L,R]$，因为这样就已经覆盖了 $[L',R']$ 这个子区间，我们就没有必要去专门激活 $[L',R']$。

而要处理这个特殊情况也很简单，只需要对每个集合求出它的区间并 $[L_i,R_i]$，然后判断哪些区间是被其余区间包含了的，如果被包含了，那就可以不用被激活。最后再求出所有必须被激活的区间的个数就行了。

不过题目还要询问方案数，这个问题也很简单，对于一个集合 $S$，它含有 $|S|$ 个区间，每个区间的两个端点只要被激活一个，那么整个区间就会被激活，因此我们对于每一个需要被激活的集合，求出它们的 $2|S|$ 之积就行了。

大致思路就是这样，接下来讨论一些实现方法。

- 如果判断一个区间是否被另一个区间包含？首先把这些区间按照 $l$ 从小到大排序，然后维护前缀的所有区间的 $r$ 最大值，若 $r_i<\max_{1\leq j<i}\{r_j\}$，则 $i$ 就会被 $j$ 这个区间包含。

- 如何快速把有交集且不包含的两个区间合并起来？我们可以对于每一个区间，按照 $l$ 从小到大排序，用线段树维护前 $i-1$ 个区间的右端点，当我们枚举到第 $i$ 个区间时，我们就查询 $[l_i,r_i]$ 范围内的右端点，然后把 $i$ 与这些右端点对应的区间编号合并。但是暴力对每一个区间合并是 $O(n^2)$ 的。

  我们可以在线段树维护的过程中，每次给 $r_j$ 的位置赋一个值，这个值就是 $r_j$ 这个右端点所对应的区间下标。每次要合并的时候，我们就查询一次 $[l_i,r_i]$ 中的最大值，只将 $i$ 和这个最大值合并。统计完之后，我们再将所有区间按照 $r$ 从大到小排序，用线段树维护区间 $l$ 的区间下标最大值，然后每次合并 $i$ 与 $[l_i,r_i]$ 中的最大值。这样下来就能完全地合并每一个 $(i,j)$。正确性大家可以尝试去证明一下，这里就不赘述了。

由于 CF 的 RMJ 挂掉了，我就放个 CF 上的 AC 记录，如果对上述讲解有所疑惑，可以参照代码进行理解。

#### [Submission](https://codeforces.com/contest/1914/submission/278898120)

---

