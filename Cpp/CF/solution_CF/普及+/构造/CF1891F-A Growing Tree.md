# A Growing Tree

## 题目描述

You are given a rooted tree with the root at vertex $ 1 $ , initially consisting of a single vertex. Each vertex has a numerical value, initially set to $ 0 $ . There are also $ q $ queries of two types:

- The first type: add a child vertex with the number $ sz + 1 $ to vertex $ v $ , where $ sz $ is the current size of the tree. The numerical value of the new vertex will be $ 0 $ .
- The second type: add $ x $ to the numerical values of all vertices in the subtree of vertex $ v $ .

After all queries, output the numerical value of all of the vertices in the final tree.

## 说明/提示

In the first case, the final tree with the assigned numerical values will look like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1891F/450cfb88a93df41b0d4048df05e79ddc23a1fc76.png) The final tree with the assigned numerical values

## 样例 #1

### 输入

```
3
9
2 1 3
1 1
2 2 1
1 1
2 3 2
1 3
2 1 4
1 3
2 3 2
5
2 1 1
1 1
2 1 -1
1 1
2 1 1
5
1 1
1 1
2 1 1
2 1 3
2 2 10```

### 输出

```
7 5 8 6 2 
1 0 1 
4 14 4```

# 题解

## 作者：RsCb (赞：7)

水题。

一边添加结点一边子树修改比较困难。发现结点的权值只和它被加入之后的操作有关，因此可以建好树之后倒着处理所有操作，操作 $2$ 直接加，操作 $1$ 记录被添加的那个结点当前的权值作为答案。

于是问题变成了静态树上子树加以及单点查询，甚至不用树链剖分。先 dfs 记录结点的 dfn 序和子树大小，记作 $\textit{dfn}_u$ 和 $\textit{sz}_u$，根据 dfn 将结点排成一个序列，将 $u$ 的整棵子树加 $x$ 对应序列中 $[\textit{dfn}_u,\textit{dfn}_u+\textit{sz}_u)$ 区间加 $x$。区间修改和单点查询的序列可以用记录差分的树状数组维护。

温馨提示：十年 OI 一场空，不开 long long 见祖宗。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
const int N = 5e5+7;
int q, t[N], v[N], x[N];
int n, w[N];
std::vector<int> e[N];
int dfn[N], cnt, sz[N];
int dfs(int u){
    dfn[u] = ++cnt;
    sz[u] = 1;
    for(int v: e[u])
        sz[u] += dfs(v);
    return sz[u];
}
namespace st{
    int d[N];
    int lb(int x){return x & -x;}
    void upd(int i, int c){
        for(; i<=n; i+=lb(i))
            d[i] += c;
    }
    void upd(int l, int r, int c){
        upd(l, c); upd(r, -c);
    }
    int qry(int i){
        int res = 0;
        for(; i; i-=lb(i))
            res += d[i];
        return res;
    }
    void clear(){
        for(int i=1; i<=n; i++)
            d[i] = 0;
    }
}
void slv(){
    scanf("%lld", &q);
    n = 1;
    for(int i=1; i<=q; i++){
        scanf("%lld", t+i);
        if(t[i] == 1){
            scanf("%lld", v+i);
            e[v[i]].push_back(++n);
            v[i] = n;
        }
        else{
            scanf("%lld%lld", v+i, x+i);
        }
    }
    cnt = 0; dfs(1);
    t[0] = 1; v[0] = 1;
    for(int i=q; i>=0; i--){
        if(t[i] == 1){
            w[v[i]] = st::qry(dfn[v[i]]);
        }
        else{
            st::upd(dfn[v[i]], dfn[v[i]]+sz[v[i]], x[i]);
        }
    }
    for(int i=1; i<=n; i++)
        printf("%lld%c", w[i], " \n"[i==n]);
    for(int i=1; i<=n; i++){
        e[i].clear();
    }
    st::clear();
}
int T;
signed main(){
    scanf("%lld", &T);
    while(T--) slv();
    return 0;
}
```


---

## 作者：Svemit (赞：3)

Div 2F 放这个，有点奇异搞笑了。

不难发现一个节点的权值完全取决于他所有祖先节点在这个节点放置之后的操作。

通过 dfs，我们可以维护从根节点到当前节点这条链的所有操作，我们只关心在这个节点放置后的操作，于是在操作二时可以这样：在某个数组中第 $sz$ 个位置加上 $v$。那么这个节点的答案就是从当前这个节点的编号开始一直到数组最后的所有元素的和。

树状数组维护单点修，前缀和即可。

```cpp
int q, tot;
LL c[N];
void modify(int x, int v) {
    for(; x <= q; x += x & -x) {
        c[x] += v;
    }
}

LL query(int x) {
    LL res = 0;
    for(; x; x -= x & -x) {
        res += c[x];
    }
    return res;
}

vector<int> e[N];
vector<PII> g[N];
LL ans[N];

void dfs(int u) {
    for(auto k : g[u]) {
        modify(k.se, k.fi);
    }
    ans[u] = query(q) - query(u - 1);
    for(auto v : e[u]) {
        dfs(v);
    }
    for(auto k : g[u]) {
        modify(k.se, -k.fi);
    }
}

void solve() {
    tot = 1;
    cin >> q;
    for(int i = 1; i <= q; i ++) {
        e[i].clear();
        g[i].clear(); 
        ans[i] = 0;
        c[i] = 0;
    }
    for(int i = 1; i <= q; i ++) {
        int op, x, v;
        cin >> op >> x;
        if(op == 1) {
            tot ++;
            e[x].push_back(tot);
        }
        else {
            cin >> v;
            g[x].push_back({v, tot});
        }
    }
    dfs(1);
    for(int i = 1; i <= tot; i ++) {
        cout << ans[i] << " \n"[i == tot];
    }
}
```

---

## 作者：_Wind_Leaves_ShaDow_ (赞：2)

经典题。正着操作不好维护树大小我们可以倒序，然后删数。

显然子树加还是你的子树加，这里可以考虑 dfs 序拍平后变成序列。

然后思考怎么删点。我们能够想到在这个点被删掉的时候把它的真正答案记下来，然后继续假装这个点还在，不需要进行真正的删点。

也就是说需要支持单点查询和区间加。可以用树状数组或者线段树。这边用的是线段树。

复杂度 $O(n\log n)$。注意多测和 long long。

```cpp
#include <bits/stdc++.h>
#define int long long
#define ri register int
#define pb emplace_back

using namespace std;
const int N=5e5;

inline int read(){
	int x=0,f=1;char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	return x*f;
}

inline void write(int x){
	if(x<0){putchar('-');x=-x;}
	if(x>9)write(x/10);
	putchar(x%10+'0');
	return;
}

int T,Q,n,xp[N+5],vp[N+5],Ans[N+5];
int idd,ld[N+5],rd[N+5];
bool op[N+5];
vector<int>v[N+5];

inline void dfs(int p,int fr){
	ld[p]=++idd;
	for(ri i:v[p])dfs(i,p);
	rd[p]=idd;
	return;
}

int sg[(N<<2)+5],tg[(N<<2)+5];

inline void build(int l,int r,int p){
	tg[p]=sg[p]=0;
	if(l==r)return;
	int mid=(l+r)>>1;
	build(l,mid,p<<1);
	build(mid+1,r,p<<1|1);
	return;
}

inline void tgd(int p){
	tg[p<<1]+=tg[p];
	tg[p<<1|1]+=tg[p];
	sg[p<<1]+=tg[p];
	sg[p<<1|1]+=tg[p];
	tg[p]=0;
	return;
}

inline void add(int ql,int qr,int l,int r,int p,int K){
	if(ql<=l&&r<=qr){
		sg[p]+=K;
		tg[p]+=K;
		return;
	}
	tgd(p);
	int mid=(l+r)>>1;
	if(ql<=mid)add(ql,qr,l,mid,p<<1,K);
	if(qr>mid)add(ql,qr,mid+1,r,p<<1|1,K);
	sg[p]=sg[p<<1];
	return;
}

inline int sqr(int ps,int l,int r,int p){
	if(l==r)return sg[p];
	tgd(p);
	int mid=(l+r)>>1;
	return (ps<=mid?sqr(ps,l,mid,p<<1):sqr(ps,mid+1,r,p<<1|1));
}

inline void solve(){
	n=1;idd=0;
	Q=read();
	for(ri i=1;i<=Q;i++){
		op[i]=read()-1;xp[i]=read();
		if(op[i])vp[i]=read();
		else v[xp[i]].pb(++n);
	}
	dfs(1,0);
	build(1,idd,1);
	for(;Q;Q--){
		if(op[Q])add(ld[xp[Q]],rd[xp[Q]],1,idd,1,vp[Q]);
		else{
			Ans[n]=sqr(ld[n],1,idd,1);
			n--;
		}
	}
	Ans[1]=sqr(1,1,n,1);
	for(ri i=1;i<=idd;i++){
		write(Ans[i]);
		putchar(32);
	}
	puts("");
	for(ri i=1;i<=idd;i++)v[i].resize(0);
	return;
}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	T=read();
	while(T--)solve();
	return 0;
}
```

---

## 作者：Null_h (赞：2)

## 前言

提供一个离线但是正着处理的方法。看到大家都用的树状数组，毅然决然打了线段树。

~~线段树万岁！~~

## 思路

首先简化问题。本题让我们维护一个动态变化的树，中途向其中加节点或者给子树中的所有节点加权值。其实不难想到，如果是一个静态的树，那么可以求 dfn，用线段树或树状数组维护，那么问题就集中在如何化动为静。

再读题，发现并不强制在线，所以这棵树最后的结构是确定的，那我们就只需要在这棵树上维护，统计时减掉每个节点加入这棵树前产生的多余贡献就行了。

形象化地理解，给你一颗确定的树，一开始除了根节点以外都是虚的，但丝毫不影响我们直接在上面维护，加入一个节点时，该节点由虚变实，它的权值此时应为 $0$，但实际上它可能已经有值了，将其归零显然太麻烦，所以记录一下当前的值，最后减去即可。

所以正着处理也是可以的。

~~题目真的突出一个水。~~

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
vector<int> h[600000];//存树
pair<int,int> m[600000];//存询问
int dfn[600000],o=1,e[600000],sz[600000];//e存前面需要去掉的值
void dfs(int u){
	dfn[u]=o++;
	int s=1;
	for(int i=0;i<h[u].size();i++){
		dfs(h[u][i]);
		s+=sz[h[u][i]];
	}
	sz[u]=s;
	return ;
}//求字数大小和dfn
struct tree{
    int l,r;
    long long pre,add;
}t[2400000];
void build(int p,int l,int r){
    t[p].l=l;t[p].r=r;
	t[p].pre=0;
	t[p].add=0;
    if(l==r)return;
    int mid=(l+r)>>1;
    build(p*2,l,mid);
    build(p*2+1,mid+1,r);
} 
void pushdown(int p){
    if(t[p].add){
        t[p*2].pre+=t[p].add*(t[p*2].r-t[p*2].l+1);
        t[p*2+1].pre+=t[p].add*(t[p*2+1].r-t[p*2+1].l+1);
        t[p*2].add+=t[p].add;
        t[p*2+1].add+=t[p].add;
        t[p].add=0;
    }
}
void add(int p,int x,int y,int z){
    if(x<=t[p].l && y>=t[p].r){
        t[p].pre+=(long long)z*(t[p].r-t[p].l+1);
        t[p].add+=z;
        return;
    }
    pushdown(p);
    int mid=(t[p].l+t[p].r)>>1;
    if(x<=mid) add(p*2,x,y,z);
    if(y>mid) add(p*2+1,x,y,z);
    t[p].pre=t[p*2].pre+t[p*2+1].pre;   
}
int ask(int p,int x,int y){
    if(x<=t[p].l && y>=t[p].r) return t[p].pre;
    pushdown(p);
    int mid=(t[p].l+t[p].r)>>1;
    long long ans=0;
    if(x<=mid) ans+=ask(p*2,x,y);
    if(y>mid) ans+=ask(p*2+1,x,y);
    return ans;
}//线段树板子
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin>>t;
    while(t--){
		int q,p=2;
		cin>>q;
		o=1;
		for(int i=0;i<=q;i++){
			h[i].clear();
			dfn[i]=0;
			e[i]=0;
		}//多测不清空，爆零两行泪！
		for(int i=0;i<q;i++){
			int op,u,v;
			cin>>op;
			if(op==1){
				cin>>u;
				h[u].push_back(p++);
				m[i]={0,u};
			}else{
				cin>>u>>v;
				m[i]={u,v};
			}
		}
		dfs(1);
		build(1,1,sz[1]);
		p=2;
		for(int i=0;i<q;i++){
			if(m[i].first==0){
				e[p++]=ask(1,dfn[p],dfn[p]);//记录
			}else{
				add(1,dfn[m[i].first],dfn[m[i].first]+sz[m[i].first]-1,m[i].second);//更新
			}
		}
		for(int i=1;i<p;i++){
			cout<<ask(1,dfn[i],dfn[i])-e[i]<<' ';
		}
		cout<<'\n';
	}
	return 0;
}
```


---

## 作者：lzyqwq (赞：2)

Div.2 F 就这？

**[题目传送门](https://codeforces.com/problemset/problem/1891/F)**

> - 给出一棵以 $1$ 为根的树，有 $q$ 次操作，分为两种：
>
>     - $1\texttt{ }x$，设当前树中一共有 $n$ 个点，加入一个编号为 $n+1$ 的点，其父亲为 $x$。
>
>     - $2\texttt{ }x\texttt{ }y$，将当前树中以 $x$ 为根的子树内所有点的点权加 $y$。
>
> - 输出最终所有点的点权。
>
> - $T$ 组数据，$\sum q\le 5\times 10^5$。

考虑先离线把树建出来，一个点能受到 $2$ 操作的影响当且仅当 $x$ 是它的祖先且这个操作的时间戳晚于当前点被加入的时间戳。

所以 dfs 一遍，用树状数组维护当前点到根的路径上，时间戳为 $1\sim q$ 的 $2$ 操作的增量总和。查询时间戳大于当前点加入的时间戳的操作的贡献即可。

回溯的时候，将当前点的操作撤销掉。

时间复杂度为 $\mathcal{O}(\sum  q\log (\sum q))$，空间复杂度为 $\mathcal{O}(\sum q)$。

**[提交记录（含代码）](https://codeforces.com/problemset/submission/1891/230810352)**

---

## 作者：ForgotDream_CHN (赞：1)

[在我的博客园中查看](https://www.cnblogs.com/forgot-dream/p/17799473.html)

> 给定一棵以 $1$ 为根的有根树，支持以下两种操作共 $q$ 次：
>
> 1. 加入一个点；
> 2. 子树内点权加。
>
> $q \le 5 \times 10^5$。

最傻逼的一集，怎么会有这么简单的 d2f。

不难发现每个点存在的时间区间构成时间轴上的一段后缀，于是我们可以将所有操作离线下来，先把完整的树建出来，然后倒着处理每个操作。不难发现，处理每个点被插入的操作时该点的权值即为答案。

具体实现可以直接 DFS 序 + BIT，写树剖也不是不行。强制在线的话，还可以 LCT。

虽然这题很傻逼，但是没有场切的我才是真正的小丑。

[代码不是我写的](https://codeforces.com/contest/1891/submission/230613907)，码风估计不太一样，凑合着看吧。

---

## 作者：hikariyo_ (赞：1)

这大概是见过最水的 Div2 F 了。


大体翻译一下操作：

1. 给 $v$ 添加一个子结点，标号是当前树的大小加一，权值是 $0$。
2. 给 $v$ 的整个子树权值加 $x$。

在线不好操作，可以离线下来把整颗树建完之后考虑如何进行。

如果没有操作 $1$，像树剖那样直接给区间 $[\text{dfn}(v),\text{dfn}(v)+\text{sz}(v)-1]$ 加 $x$ 即可。

考虑操作 $1$，在刚建立这个结点的时候毫无疑问它的整颗子树点权全是 $0$，所以查询它的点权然后给整颗子树都减去即可。

最后查询出每个点的点权输出就是答案。

考虑到我们需要能支持区间修改和单点查询的数据结构，那么肯定是优先选择树状数组维护差分序列，这比线段树好写多了；同时，只有修改整颗子树的操作，不需要树剖，只要预处理出 DFS 序和子树大小即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
#define lowbit(x) ((x)&(-x))

struct BIT {
    vector<LL> tr;
    int n;

    BIT(int n): n(n) {
        tr.resize(n+1);
    }

    void add(int l, int r, LL x) {
        add(l, x);
        if (r < n) add(r+1, -x);
    }

    void add(int p, LL x) {
        for (; p <= n; p += lowbit(p))
            tr[p] += x;
    }

    LL query(int p) {
        LL res = 0;
        for (; p; p -= lowbit(p))
            res += tr[p];
        return res;
    }
};

struct Query {
    int t, u, p, x;
};

void solve() {
    int q;
    scanf("%d", &q);

    vector<Query> qry(q);
    int n = 1;
    for (int i = 0, tp, u, x; i < q; i++) {
        scanf("%d%d", &tp, &u);
        if (tp == 1) qry[i] = {tp, ++n, u, 0};
        else scanf("%d", &x), qry[i] = {tp, u, 0, x};
    }

    BIT bit(n);
    vector<vector<int>> G(n+1);
    for (int i = 0; i < q; i++) {
        int u = qry[i].u, p = qry[i].p;
        if (qry[i].t == 1) {
            G[u].emplace_back(p);
            G[p].emplace_back(u);
        }
    }

    vector<int> dfn(n+1), sz(n+1);
    int ts = 0;
    auto dfs1 = [&](auto&& self, int u, int father) -> void {
        dfn[u] = ++ts, sz[u] = 1;
        for (int to: G[u]) {
            if (to == father) continue;
            self(self, to, u);
            sz[u] += sz[to];
        }
    };

    dfs1(dfs1, 1, 0);
    for (int i = 0; i < q; i++) {
        int u = qry[i].u;
        if (qry[i].t == 1) {
            LL val = bit.query(dfn[u]);
            bit.add(dfn[u], dfn[u] + sz[u] - 1, -val);
        }
        else bit.add(dfn[u], dfn[u] + sz[u] - 1, qry[i].x);
    }

    for (int i = 1; i <= n; i++) printf("%lld ", bit.query(dfn[i]));
    puts("");
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) solve();
    return 0;
}
```


---

## 作者：_sunkuangzheng_ (赞：1)

做过最水的 Div.2 F。

因为树形固定且没有删除操作，我们考虑离线处理。先把整棵树建出来，然后要做的就是给 $u$ 的子树 $+x$。但是，因为加法时不一定所有子树内的点都建了出来，所以我们不能简单的给 dfn 序区间做加法。

我们给每个点增加一个属性 $t_i$ 表示点 $i$ 是什么时候出现的，那么本质上，一次操作 $(u,x)$ 等价于给满足 $dfn_u \le dfn_y \le dfn_u+siz_u-1,t_y \le t_u$ 的点 $y$ 做 $+x$。你发现这是一个二维区间加法，把它差分一下，变成了二维平面内单点修改区间求和。树状数组离线二维数点即可。时间复杂度 $\mathcal O(q \log q)$。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 30.10.2023 23:46:02
**/
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 5e5+5;
int T,n,q,dfn[N],po,u,v,re,st[N],siz[N],ans[N],dt,t[N];vector<tuple<int,int,int>> op;vector<int> g[N];
void upd(int x,int p){for(;x <= n + 1;x += x & -x) t[x] += p;}
int qry(int x){for(re = 0;x;x -= x & -x) re += t[x];return re;}
void dfs(int u,int f){
    dfn[u] = ++dt,siz[u] = 1;
    for(int v : g[u]) if(v != f) dfs(v,u),siz[u] += siz[v];
}signed main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> T;
    while(T --){
        n = 1,st[1] = 1,dt = 0;int ti = 1;op.clear();
        vector<tuple<int,int,int,int>> qu;
        for(int i = 1;i <= n + 1;i ++) t[i] = 0;
        cin >> q;while(q --){
            cin >> po >> u;++ti;
            if(po == 1) g[u].push_back(++n),st[n] = ti;
            else cin >> v,op.emplace_back(u,v,ti);
        }dfs(1,0);for(auto [u,v,ti] : op){
            qu.emplace_back(1,dfn[u],1,v),qu.emplace_back(ti+1,dfn[u]+siz[u],1,v),
            qu.emplace_back(1,dfn[u]+siz[u],1,-v),qu.emplace_back(ti+1,dfn[u],1,-v);
        }for(int i = 1;i <= n;i ++) qu.emplace_back(st[i],dfn[i],2,i);
        sort(qu.begin(),qu.end());
        for(auto [x,y,tp,z] : qu){
            if(tp == 1) upd(y,z);
            else ans[z] = qry(y); 
        }for(int i = 1;i <= n;i ++) cout << ans[i] << " ",g[i].clear();
        cout << "\n";
    }
}
```

---

## 作者：Wei_Han (赞：0)

~~合着放 Div.2 F 是因为卡常是吧~~

加点不好维护，既然没有在线查询，考虑离线下来建树。

比较显然，一个点最后的权值应该是它从加入开始到最后所有加的权值，那么我们倒序维护所有操作，到新加点的操作时，说明当前点从被添加到结束的权值我们已经统计完了，就是最后的答案，单独拿出来存一下就行了，然后再随便找个数据结构维护子树加就行了。

有点卡常，建树尽量不要双向边，时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define pr printf("\n")
#define pp printf(" ")
#define pii pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(ll i = a ; i <= b ; ++ i )
#define Fo(a,i,b) for(ll i = a ; i >= b ; -- i )
#define bug (x>=1&&x<=n&&y>=1&&y<=m) 
using namespace std;
typedef long long ll;
typedef __int128 i128;
typedef double db;
const int N=5e5+5,M=1e7+5;
const db eps=1e-7;
inline void read(int &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}
int n=1,m,head[N],tot,son[N],fa[N],dep[N],siz[N],top[N],rb[N],id[N],w[N],cnt;
ll bit[N];
struct Graph{ll ver,nxt,w;}g[N<<1];
inline void add(ll x,ll y){g[++tot].ver=y,g[tot].nxt=head[x];head[x]=tot;}
inline ll lowbit(ll x){return x&(-x);}
inline void upd(ll x,ll y){for(int i=x;i<=n;i+=lowbit(i)) bit[i]+=y;}
inline ll query(ll x){ll ans=0;for(int i=x;i;i-=lowbit(i)) ans+=bit[i];return ans;}
inline void dfs1(ll x,ll father,ll depth){
	dep[x]=depth,fa[x]=father,siz[x]=1,id[x]=++cnt,w[cnt]=x;
	ll zson=-1;
	for(ll i=head[x];i;i=g[i].nxt){
		ll y=g[i].ver;if(y==fa[x]) continue;
		dfs1(y,x,depth+1);siz[x]+=siz[y];
		if(siz[y]>zson) zson=siz[y],son[x]=y;
	}
	rb[x]=cnt;
}
struct Input{int op,u,v;}a[N];
ll num[N];
signed main(){
	int t;read(t);
	while(t--){
		n=1;
		read(m);fo(1,i,m){
			read(a[i].op);
			if(a[i].op==1) read(a[i].u),add(a[i].u,++n),a[i].v=n;
			else read(a[i].u),read(a[i].v);
		}
		dfs1(1,0,1);
		Fo(m,i,1){
			if(a[i].op==1) num[a[i].v]=query(id[a[i].v]);
			else upd(id[a[i].u],a[i].v),upd(rb[a[i].u]+1,-a[i].v);
		}
		num[1]=query(id[1]);
		fo(1,i,n) wr(num[i]),pp,bit[i]=top[i]=rb[i]=id[i]=w[i]=fa[i]=son[i]=dep[i]=siz[i]=num[i]=0;cnt=0;fo(1,i,tot) head[i]=0;tot=0;pr;
	}
	return 0;
}
``````

---

## 作者：huangrenheluogu (赞：0)

这么水的 F，赛时要是没看到就可惜了。

给每一个节点一个时间，然后可以从根节点 $1$ 开始算 $2$ 操作的贡献，注意这里的操作需要再生成这个节点之前。

记这个节点的时间为 $x$，需要计算时间是 $x\sim q$ 生成的权值。单点修改，区间查询，用树状数组即可。

从 $1$ 开始，向下累计放入树状数组，到一个节点就把贡献放到树状数组里，回溯的时候记得删除。

这道 F 就写完了。

[code](https://codeforces.com/contest/1891/submission/238108557)

---

## 作者：xiezheyuan (赞：0)

## 简要题意

你需要维护一个树，初始时只有一个点 $1$，点权为 $0$。

有 $q$ 次操作，支持：

- `1 p` 设 $s$ 为当前点数，则新建一个编号为 $s+1$ 的点，为 $p$ 的一个子节点。点权为 $0$。
- `2 p v` 将 $p$ 为根的子树内所有的点点权加上 $v$。

最后输出每个点的最终点权。

$T$ 组数据。

$1 \leq T \leq 10^4,1 \leq \sum q \leq 5\times10^5$

## 思路

Codeforces 思维训练第一题。

这道题看起来很水的样子（事实上也很水）。

我们考虑先离线下来看看树长什么样。然后考虑关键的问题在于在子树加的时候，可能某些点还没有存在。

如何解决这个问题？我们可以发现，对于每一个点，可以影响到它的操作时间戳一定是一个后缀。

于是我们可以找一个树状数组维护时间戳对应的加标记，然后操作离线完后我们 dfs 一遍到达每个点先加上这个点对应的子树加，然后离开这个点的时候撤销贡献即可。

时间复杂度 $O(q\log q)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define lowbit(x) ((x)&-((x)))
using namespace std;

const int N = 5e5+5;
int t[N],T,q,siz;

void update(int p, int v){
	while(p <= q){
		t[p] += v;
		p += lowbit(p);
	}
}

int query(int p){
	int ans = 0;
	while(p){
		ans += t[p];
		p -= lowbit(p);
	}
	return ans;
}

struct edge{
	int nxt,to;	
} g[N<<1];
int head[N], ec;
void add(int u, int v){
	g[++ec].nxt=head[u];
	g[ec].to = v;
	head[u] = ec;	
}
struct option{
	int t,v;
	option(int T, int V){t = T,v = V;}
};
vector<option> ops[N];
int ans[N], ttime[N];

void dfs(int u, int fa){
	for(option i : ops[u]) update(i.t, i.v);
	ans[u] = query(q) - query(ttime[u] - 1);
	for(int i=head[u];i;i=g[i].nxt){
		int v = g[i].to;
		if(v == fa) continue;
		dfs(v, u);
	}
	for(option i : ops[u]) update(i.t, -i.v);
}

void solve(){
	cin>>q;
	ttime[1] = 1;
	q++;siz = 1;
	for(int i=2;i<=q;i++){
		int op,x,v;
		cin>>op>>x;
		if(op == 1){
			add(x, ++siz);
			add(siz, x);
			ttime[siz] = i;
		}
		if(op == 2){
			cin>>v;
			ops[x].push_back(option(i, v));
		}
	}
	dfs(1, 0);
	for(int i=1;i<=siz;i++) cout<<ans[i]<<' ';
	cout<<'\n';
}

void clear(){
	for(int i=1;i<=ec;i++) g[i].nxt = g[i].to = 0;
	for(int i=1;i<=siz;i++) head[i] = 0;
	ec = 0;
	for(int i=1;i<=siz;i++) ops[i].clear();
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--) solve(), clear();
	return 0;		
}

```


---

## 作者：Iniaugoty (赞：0)

啊？这么简单的题，Div.2F，*2000？

动态加点是不好搞的，考虑把操作离线下来，先把树建好。然后因为是对子树操作的，子树这种东西在 dfs 序上是连续的，再把树挂到 dfs 序上。

发现正着不太好搞，不断加点使得子树对应区间不好确定，那就倒着搞。操作 2 就是区间加；操作 1 时，某个结点才刚被加入，所有对它权值有影响的操作 2 都在它后面已经被执行过了，所以此时这个点的值就是最终它的值（即答案）。

区间修改单点查询，经典树状数组维护差分数组。

时间复杂度 $\mathcal O (q \log n)$，空间复杂度 $\mathcal O (n)$。

```cpp
#include <bits/stdc++.h>

#define F(i, a, b) for(int i = (a); i <= (b); ++i)
#define dF(i, a, b) for(int i = (a); i >= (b); --i)

using namespace std;
typedef long long LL;
typedef unsigned long long ull;
const int N = 5e5 + 5;

int _, q, n;
int op[N], x[N], y[N];
vector<int> e[N];
void Addedge(int u, int v) {
	e[u].push_back(v);
	return ;
}

int cnt, dfn[N], siz[N];
void Dfs(int u) {
	dfn[u] = ++cnt;
	siz[u] = 1;
	for (auto v : e[u])
		Dfs(v), siz[u] += siz[v];
	return ;
}

LL t[N];
int lowbit(int x) { return x & -x; }
void Update(int x, int k) {
	for (int i = x; i <= n; i += lowbit(i))
		t[i] += k;
	return ;
}
LL Query(int x) {
	LL res = 0;
	for (int i = x; i; i -= lowbit(i))
		res += t[i];
	return res;
}

LL ans[N];

int main() {
	//freopen(".in", "r", stdin);
	//freopen(".out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> _;
	while (_--) {
		cin >> q, n = 1;
		F(i, 1, q) {
			cin >> op[i] >> x[i];
			if (op[i] == 1) Addedge(x[i], y[i] = ++n);
			else cin >> y[i];
		}
		Dfs(1);
		dF(i, q, 1)
			if (op[i] == 1) ans[y[i]] = Query(dfn[y[i]]);
			else
				Update(dfn[x[i]], y[i]),
				Update(dfn[x[i]] + siz[x[i]], -y[i]);
        ans[1] = Query(1);
		F(i, 1, n) cout << ans[i] << " ";
		cout << "\n";
		F(i, 1, n) t[i] = 0, e[i].clear();
		cnt = 0;
	}
	return 0;
}
```

---

## 作者：彭俊皓123 (赞：0)

# CF1891F 题解

看到题解里有许多直接树剖离线做的，这里提供一个 LCT 的在线做法。

## 一、简化题意

题目要求维护两种操作：在节点下接一个新的节点，对节点的子树加上一个权值。

在操作全部完成后输出所有点权。

## 二、分析

由于题目要求在所有操作结束后输出点权，可以对操作进行离线：

记录每个节点加入的实际时间，在加入前不对这个点做子树加即可。

然而，由于中间状态点间关系的不确定，也可以考虑一种动态树的在线做法。

在处理完操作后统计权值即可。

## 三、具体实现

考虑到直接丢 LCT 代码过于潦草，码一下子树操作的做法。

推一下自己的博客 [LCT(Link-Cut-Tree)](https://www.luogu.com.cn/blog/pengjunhao123/L-C-T)，其中大概简述了一下 LCT 的基本操作。

对于 LCT 中的子树加权，可以看作是对虚节点和实节点的加。

先考虑一个暴力做法：直接下传权值到每个节点，暴力加权。

很显然这种做法是 $O(n)$ 的。

然而众所周知，在学习线段树时有一个延迟标记（懒标记）的概念，

其通过延迟标记的下传以优化复杂度的思想很值得借鉴。

于是我们考虑对 LCT 也进行延迟下传操作。

由于虚结点并不与自己的父节点在同一棵 Splay 中，不是很好直接和实节点一起操作，于是考虑对两种修改分开进行。

为了统计子树答案，需要维护实子树、虚子树的大小以进行加权。

~~（当然，这题用不到统计子树答案）~~

而实节点和虚结点是可以互相转化的，因此也要在实链剖分的部分进行修改。

>也正因为可以互相转化，要把虚结点的权值和实节点的分开而不是直接放在一起

具体而言，只需要把实节点的影响加到虚结点上，再把新的实节点的影响更新下来即可。

代码如下，其中 $det$ 为作为虚结点新加的权值，$itag$ 为作为虚结点的延迟标记：

```cpp
void add(int k,ll query)
{
    tag(k)+=query;
    val(k)+=query;
    sum(k)+=query*tsiz(k);
}//对实节点加
void iadd(int k,ll query)
{
    itag(k)+=query;
    det(k)+=query;
    sum(k)+=query*sumsiz(k);
}//对虚结点加
void insert_(int x,int y)
{
    if(!y)return;
    add(y,-det(x));iadd(y,-det(x));
    isiz(x)+=siz(y),isum(x)+=sum(y);
}//加入新虚节点的影响（先做再加siz）
void delete_(int x,int y)
{
    if(!y)return;
    isiz(x)-=siz(y),isum(x)-=sum(y);
    add(y,det(x)),iadd(y,det(x));
}//删除旧虚节点的影响（先删siz再做）
void access(int k)
{
    int last=0;
    while(k)
    {
        splay(k);
        insert_(k,rs(k)),delete_(k,last);//修改的部分
        rs(k)=last,pushup(k);
        last=k,k=fa(k);
    }
}
```

考虑以上操作之后，我们还需要考虑如何对以某个节点为根的子树加权。

首先肯定要对节点和根之间的路径进行一遍 Split 以便于操作，

接着就类似线段树一样，对节点的虚实权值都加上，然后再维护一下和就行了
~~（这题并不需要的操作）~~。

具体代码如下：

```cpp
void addtree(int root,int k,ll query)
{
    split(root,k);det(k)+=query,val(k)+=query;
    sum(k)+=query*(isiz(k)+1);
}
```

最后来考虑一下查询所有节点的答案。

很显然，只需要把这个节点转到 LCT 根后查询即可。

整题实现代码如下（为了省时间把动态到封装进结构体去了）：

```cpp
#include<iostream>
#define ll long long
using namespace std;
const int MAXN=500005;
int a,b,c,T;
struct LCT
{
    struct nodes
    {
        int fa;
        int revtag;
        int son[2],siz,isiz,tsiz,sumsiz;
        //左右子节点，自身子树大小，虚子树大小，实子树大小，所在实子树的总虚子树大小
        ll val,sum,isum;
        ll tag,itag,det;
        //实子树标记，虚子树标记，已经加的值
        nodes():fa(0),revtag(false),val(0),sum(0),isum(0),tag(0),itag(0),det(0),siz(0),isiz(0),tsiz(0),sumsiz(0){son[0]=son[1]=0;}
        void clear()
        {
            fa=revtag=val=sum=isum=0;
            tag=itag=det=siz=isiz=tsiz=sumsiz=0;
            son[0]=son[1]=0;
        }
        #define fa(k) node[k].fa
        #define ls(k) node[k].son[0]
        #define rs(k) node[k].son[1]
        #define revtag(k) node[k].revtag
        #define siz(k) node[k].siz
        #define isiz(k) node[k].isiz
        #define tsiz(k) node[k].tsiz
        #define sumsiz(k) node[k].sumsiz
        #define val(k) node[k].val
        #define sum(k) node[k].sum
        #define isum(k) node[k].isum
        #define tag(k) node[k].tag
        #define itag(k) node[k].itag
        #define det(k) node[k].det
    }node[MAXN];
    void pushup(int k)
    {
        siz(k)=siz(ls(k))+siz(rs(k))+isiz(k)+1;
        tsiz(k)=tsiz(ls(k))+tsiz(rs(k))+1;
        sumsiz(k)=sumsiz(ls(k))+sumsiz(rs(k))+isiz(k);
        sum(k)=sum(ls(k))+sum(rs(k))+isum(k)+val(k)+isiz(k)*det(k);
    }
    void add(int k,ll query){tag(k)+=query,val(k)+=query,sum(k)+=query*tsiz(k);}
    void iadd(int k,ll query){itag(k)+=query,det(k)+=query,sum(k)+=query*sumsiz(k);}
    void rev(int k){swap(ls(k),rs(k));revtag(k)^=1;}
    void pushdown(int k)
    {
        if(revtag(k))rev(ls(k)),rev(rs(k)),revtag(k)=0;
        add(ls(k),tag(k)),add(rs(k),tag(k)),tag(k)=0;
        iadd(ls(k),itag(k)),iadd(rs(k),itag(k)),itag(k)=0;
    }
    bool check(int k){return rs(fa(k))==k;}
    bool isroot(int k){return ls(fa(k))!=k&&rs(fa(k))!=k;}
    void update(int k){if(!isroot(k))update(fa(k));pushdown(k);}
    void rotate_(int k)
    {
        int fath=fa(k),gath=fa(fath);
        int inv=check(k);
        if(!isroot(fath))node[gath].son[check(fath)]=k;
        node[fath].son[inv]=node[k].son[inv^1];
        fa(node[k].son[inv^1])=fath;
        node[k].son[inv^1]=fath;
        fa(fath)=k;
        fa(k)=gath;
        pushup(fath);pushup(k);
    }
    void splay(int k)
    {
        update(k);
        while(!isroot(k))
        {
            if(!isroot(fa(k)))rotate_(check(k)^check(fa(k))?k:fa(k));
            rotate_(k);
        }
    }//
    void insert_(int x,int y)
    {
        if(!y)return;
        add(y,-det(x));iadd(y,-det(x));
        isiz(x)+=siz(y),isum(x)+=sum(y);
    }
    void delete_(int x,int y)
    {
        if(!y)return;
        isiz(x)-=siz(y),isum(x)-=sum(y);
        add(y,det(x)),iadd(y,det(x));
    }
    void access(int k)
    {
        int last=0;
        while(k)
        {
            splay(k);
            insert_(k,rs(k)),delete_(k,last);
            rs(k)=last,pushup(k);
            last=k,k=fa(k);
        }
        //return last;
    }
    void makeroot(int k){access(k);splay(k);swap(ls(k),rs(k));revtag(k)^=1;}
    void split(int x,int y){makeroot(x);makeroot(y);splay(y);}
    void link(int x,int y){makeroot(x);makeroot(y);access(y);fa(x)=y,rs(y)=x;pushup(y);}
    void addtree(int root,int k,ll query)
    {
        split(root,k);det(k)+=query,val(k)+=query;
        sum(k)+=query*(isiz(k)+1);
    }
}lct;
inline int read()
{
    char x=getchar();int t=0,w=1;
    while(!isdigit(x))w=x=='-'?-1:w,x=getchar();
    while(isdigit(x))t=(t<<3)+(t<<1)+(x^48),x=getchar();
    return t*w;
}
int main()
{
    T=read();
    while(T--)
    {
        for(int i=1;i<=a;++i)lct.node[i].clear();
        a=read();
        int siz=1;
        for(int i=1;i<=a;++i)
        {
            int opt=read(),x=read(),y;
            switch(opt){
            case 1:
                lct.link(x,++siz);break;
            case 2:
                y=read();
                lct.addtree(1,x,y);
                break;
            }
        }
        for(int i=1;i<=siz;++i)
        {
            lct.makeroot(i);
            printf("%lld ",lct.val(i));
        }
        puts("");
    }
}

```



---

## 作者：Sevendays_Coder (赞：0)



~~为了限制篇幅，代码都放云剪贴板了~~。

## _Description_

>- $T$ 组数据

>- 给定一棵树，初始只含一个节点，编号为 $1$，初始权值为 $0$，设树的大小为 $sz$。

>- $q$ 次操作：
	
>	* $1\ x$，在 $s$ 下挂一个节点，编号为 $sz+1$，初始权值为 $0$。
    
>	* $2\ x\ v$，将 $x$ 子树中节点的权值加上 $v$。
    
>- 求所有操作完成后每个节点的点权。

>- $1\le T\le10^4$, $1\le\sum q\le5\times10^5$

## _Solution_

捡到一个比较简单的 Div2 F，切了水篇题解。

我的思想比较暴力。

考虑先把操作离线下来，直接将整颗树按照 DFS 序拍到线段树上，使得子树坐标连续。

对于每次修改操作，考虑时刻。

我们发现子树大小，即最大节点编号可以很好地反应时刻，于是在离线的时候我们将修改操作时的子树大小记录下来。

建树之后，对于每一次操作，给**该节点的完整树中的子树在线段树上的对应节点**打上两个标记，分别记录权值与时刻。

最后我们遍历每个节点，在查询时，对于时刻值**比该节点在原树上的编号**要**小**的修改操作直接忽略，将其它的权值累加起来，便得到了这个点的值。

上述操作暴力遍历区间肯定是不可取的，由于修改操作本就是按时刻有序，考虑对于每一个线段树节点的标记维护一个队列，查询时从小到大，对于时刻大于当前查询点编号的标记，直接出队就好了。

时间复杂度 $O(\sum q\log(\sum q))$。

**注意**：队列建议用 ```std::vector``` 实现，小心 ```std::queue``` 爆空间喜提 0pts。 

**Pass**: 这题好像没卡双 $\log$，赛时~~脑 can~~ 用了优先队列居然过了，只能说太水了。

[AC代码](https://www.luogu.com.cn/paste/ljmq5qte)

## _Update on 2th Nov._

还有一种异曲同工的做法（CF 正解）

考虑上面的做法是在考虑**阻止**，那我们可以考虑**挽回**，我们遍历每一个时刻，（其实也是遍历每个节点），这个时刻之前的修改操作可以直接作用在整颗子树上。对于当前时刻，开始修改之前可以先**手动**将当前节点的值清零，即 $val_i = val_i-\operatorname{Query}(i)$，就忽略了之前的贡献了。

时间复杂度 $O(\sum q\log(\sum q))$。

[AC代码](https://www.luogu.com.cn/paste/h2eltp35)

---

## 作者：沉石鱼惊旋 (赞：0)

# 前言

以此纪念 1:59:14 过的 Div.2 F。

# 题目翻译

有一棵以 $1$ 为根的有根树，一开始只有节点 $1$。

有 $q(1\leq q\leq 5\times 10^5)$ 个操作：

`1 u` 表示添加一条 $u\to sz+1$ 的边，其中 $sz$ 为目前树的大小。

`2 u w` 表示对于以 $u$ 为根的子树，对于所有节点添加 $w(-10^9\leq w\leq 10^9)$ 的权重。

$q$ 次操作后，输出当前树上每个节点的权重。

# 题目思路

题目不强制在线，我们考虑先离线操作。

离线之后先按操作建出最终状态的树。此时权重都为 $w$。

然后套路性的把这棵树按 Euler Tour 压成一段序列。压好之后同一子树内的节点肯定是连续出现的。

此时 2 操作维护区间加法。操作 1 维护区间清零，因为如果这个点没被建出不会存在以它为根的修改操作，也就是说区间内的数都是一样的，相当于区间加法了。

所以维护区间加法和单点查询操作即可。可以使用 BIT 或 SGT。代码使用的是 BIT。

# 完整代码

[CF submission 230573340](https://codeforces.com/contest/1891/submission/230573340)

**读入量巨大，建议使用快读！**

一些东西的用处：

`ll cur_tree_sz=1;` 当前树大小。

`vector<pii> a[2000020];` 建树。

`ll in[2000020];ll out[2000020];` Euler Tour 中的左右端点，即最早最晚的出现次数。

`ll times;` Euler Tour 的时间（长度）。

`ll c[4000020];` BIT 数组。`change` 进行单点修改，`query` 进行单点查询。区间修改只需要用单点修改差分即可。

赛时着急写得有点拉，上述没提到的部分东西其实没用。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define getchar() p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++
char buf[1000000], *p1 = buf, *p2 = buf;
template <typename T>
inline T read()
{
    register T x = 0;
    register int f = 1;
    register char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -f;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = (x << 1) + (x << 3) + (c ^ 48);
    return x * f;
}
typedef long long ll;
typedef pair<ll, ll> pii;
int Q;
ll cur_tree_sz = 1;
struct Query
{
    ll op, x, y, t;
} q[2000020];
vector<pii> a[2000020];
ll dep[2000020];
ll in[2000020];
ll out[2000020];
ll id[2000020];
ll times;
// 树按dfs拍成序列
void dfs(int u, int fa, int d)
{
    dep[u] = d;
    in[u] = ++times;
    id[++times] = u;
    for (pii p : a[u])
    {
        ll v = p.first, j = p.second;
        if (v == fa)
            continue;
        dfs(v, u, d + 1);
    }
    out[u] = ++times;
}
ll c[4000020];
const int N = 4000000;
ll lowbit(ll x)
{
    return x & -x;
}
ll query(ll x)
{
    ll ret = 0;
    while (x)
    {
        ret += c[x];
        x -= lowbit(x);
    }
    return ret;
}
void change(ll x, ll y)
{
    while (x <= N)
    {
        c[x] += y;
        x += lowbit(x);
    }
}
void solve()
{
    for (int i = 1; i <= cur_tree_sz + 10; i++)
        dep[i] = id[i] = in[i] = out[i] = 0, a[i].clear();
    for (int i = 1; i <= times + 10; i++)
        c[i] = 0;
    cur_tree_sz = 1;
    times = 0;
    Q = read<int>();
    for (int i = 1; i <= Q; i++)
    {
        q[i].op = read<int>();
        q[i].x = read<int>();
        if (q[i].op & 1)
        {
            a[q[i].x].push_back({++cur_tree_sz, ++times});
        }
        else
        {
            q[i].y = read<ll>();
        }
        q[i].t = i;
    }
    times = 0;
    dfs(1, 0, 1);
    cur_tree_sz = 1;
    for (int i = 1; i <= Q; i++)
    {
        if (q[i].op & 1)
        {
            cur_tree_sz++;
            ll res = query(in[cur_tree_sz]);
            change(in[cur_tree_sz], -res);
            change(out[cur_tree_sz], res);
        }
        else
        {
            change(in[q[i].x], q[i].y);
            change(out[q[i].x], -q[i].y);
        }
    }
    // for (int i = 1; i <= cur_tree_sz; i++)
    //     cout << id[i] << " ";
    // cout << endl;
    for (int i = 1; i <= cur_tree_sz; i++)
        printf("%lld ", query(in[i]));
    printf("\n");
}
int main()
{
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
```

---

