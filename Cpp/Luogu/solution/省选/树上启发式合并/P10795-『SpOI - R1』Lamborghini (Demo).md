# 『SpOI - R1』Lamborghini (Demo)

## 题目描述

给你一棵无根树，每个点 $i$ 有两个属性 $t_i,v_i$。

定义有向路径 $i\to j$ 的 $f_{i,j}$ 为：

- 若 $i\to j$ 上 $t_x$ 最小的点为 $x$ 且 $v_j\leq v_x\leq v_i$，则 $f_{i,j}=x$。
- 否则，$f_{i,j}=0$。

求 $\sum\limits_{i=1}^n\sum\limits_{j=1}^n f_{i,j}$。

## 说明/提示

#### 样例 #1 解释

- $f(1,1)=1$。
- $f(1,2)=0$。
- $f(1,3)=0$。
- $f(2,1)=1$。
- $f(2,2)=2$。
- $f(2,3)=0$。
- $f(3,1)=1$。
- $f(3,2)=2$。
- $f(3,3)=3$。

故 $\sum\limits_{i=1}^3\sum\limits_{j=1}^3 f(i,j)=10$。

### 数据范围

**本题开启子任务捆绑与子任务依赖。**

对于 $100\%$ 的数据，$t$ 互不相同，$1\leq n\leq 10^5$，$1\leq t_i,v_i\leq 10^9$。

| Subtask | $n\leq$ | $t_i,v_i\leq$ | 特殊性质 | 得分 | 子任务依赖 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| 1 | $300$ | $10^5$ | 无 | $15$ | 无 |
| 2 | $5000$ | $10^5$ | 无 | $15$ | 1 |
| 3 | $10^5$ | $10^9$ | $A$ | $15$ | 无 |
| 4 | $10^5$ | $10^9$ | $B$ | $15$ | 无 |
| 5 | $10^5$ | $10^9$ | 无 | $40$ | 1,2,3,4 |

特殊性质 $A$：**钦定 $1$ 号节点为树的根**，对于任意点对 $(x,y)$ 且 $x\neq y$，若 $x$ 是 $y$ 的祖先，则 $t_x<t_y$。

特殊性质 $B$：$\forall i\in[1,n),a_i=i,b_i=i+1$。

## 样例 #1

### 输入

```
3
1 2 3
1 3 5
1 2
2 3```

### 输出

```
10```

## 样例 #2

### 输入

```
5
1 3 5 8 10
1 5 3 2 8
2 1
3 1
4 1
5 3```

### 输出

```
22```

# 题解

## 作者：是青白呀 (赞：7)

树上笛卡尔树。

我们显然需要一个结构来表示“树上路径上点权最小的点”。在链上，可以选用笛卡尔树；在树上同理。具体的建树方式是：按点权从大往小枚举每个点 $i$，在它的所有相邻的点中，对于点权大于 $i$ 的点 $j$，我们连边 $(i,j)$。这样连边后最终会得到一棵树，且若以点权最小的点为根，则**新树上任意两点的 $lca$ 为原树上两点间路径上权值最小的点**。

则原问题转化为：对于每个点 $x$，求有多少个点对 $(i,j)$ 满足 $lca_{i,j}=x$ 且 $v_i\leq v_x\leq v_j$，对 $v$ 离散化后用权值线段树维护各个值的点的数量，线段树合并即可。复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define ls(x) lson[x]
#define rs(x) rson[x]
#define mp make_pair
#define fir first
#define sec second
#define pii pair<int,int>
#define lowbit(x) x&-x
#define int long long
#define qingbai 666
using namespace std;
typedef long long ll;
const int N=1e5+5,M=2e5+5,S=(1<<17)+2,mo=998244353,inf=1e18+7;
const double eps=1e-8;
void read(int &p){
	int x=0,w=1;
	char ch=0;
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
}
int n,lsh[N],cntl;
struct point{
	int v,a,id;
	friend bool operator<(point x,point y){
		return x.a>y.a;
	}
}p[N];
int ans;
struct tree{
	struct edge{
		int to,nxt;
	}e[N];
	int fir[N],np;
	void add(int x,int y){
		e[++np]=(edge){y,fir[x]};
		fir[x]=np;
	}
	struct seg{
		int t[40*N],lson[40*N],rson[40*N],rt[N],cnt;
		void pushup(int x){
			t[x]=t[ls(x)]+t[rs(x)];
		}
		void add(int &x,int le,int ri,int p){
			if(!x)x=++cnt;
			if(le==ri){
				t[x]++;
				return;
			}
			int mid=(le+ri)>>1;
			if(p<=mid)add(ls(x),le,mid,p);
			else add(rs(x),mid+1,ri,p);
			pushup(x); 
		}
		int query(int x,int le,int ri,int ql,int qr){
			if(ql>qr)return 0;
			if(!x)return 0;
			if(ql<=le&&qr>=ri)return t[x];
			int mid=(le+ri)>>1,ret=0;
			if(ql<=mid)ret+=query(ls(x),le,mid,ql,qr);
			if(qr>mid)ret+=query(rs(x),mid+1,ri,ql,qr);
			return ret;
		}
		int merge(int p,int q,int le,int ri){
			if(!p)return q;
			if(!q)return p;
			if(le==ri){
				t[p]+=t[q];
				return p;
			}
			int mid=(le+ri)>>1;
			ls(p)=merge(ls(p),ls(q),le,mid),rs(p)=merge(rs(p),rs(q),mid+1,ri); 
			pushup(p);
			return p;
		}
	}T;
	void dfs(int x){
		int res=0;
		T.add(T.rt[x],1,cntl,p[x].v);
		for(int i=fir[x];i;i=e[i].nxt){
			int j=e[i].to;
			dfs(j);
			int nw1=T.query(T.rt[j],1,cntl,1,p[x].v-1);
			int nw2=T.query(T.rt[j],1,cntl,p[x].v,p[x].v);
			int nw3=T.query(T.rt[j],1,cntl,p[x].v+1,cntl);
			res+=nw1*T.query(T.rt[x],1,cntl,p[x].v,cntl);
			res+=nw2*(T.query(T.rt[x],1,cntl,1,cntl)+T.query(T.rt[x],1,cntl,p[x].v,p[x].v));
			res+=nw3*T.query(T.rt[x],1,cntl,1,p[x].v);
			T.rt[x]=T.merge(T.rt[x],T.rt[j],1,cntl);
		}
		res++;
		ans+=res*p[x].id;
	}
}T;
int fa[N];
int find(int x){
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
struct edge{
	int to,nxt;
}e[2*N];
int fir[N],np,nid[N];
void add(int x,int y){
	e[++np]=(edge){y,fir[x]};
	fir[x]=np;
}
void merge(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx==fy)return;
	fa[fy]=fx,T.add(fx,fy);
}
map <int,int> ok;
signed main(){
	read(n);
	rep(i,1,n)
	    read(p[i].a),ok[p[i].a]=1,fa[i]=i,p[i].id=i;
	assert(ok.size()==n);
	rep(i,1,n)
	    read(p[i].v),lsh[++cntl]=p[i].v;
	sort(lsh+1,lsh+cntl+1),cntl=unique(lsh+1,lsh+cntl+1)-lsh-1;
	rep(i,1,n)
	    p[i].v=lower_bound(lsh+1,lsh+cntl+1,p[i].v)-lsh;
	sort(p+1,p+n+1);
	rep(i,1,n)
	    nid[p[i].id]=i;
	rep(i,1,n-1){
		int x,y;
		read(x),read(y),add(nid[x],nid[y]),add(nid[y],nid[x]);
	}
	rep(i,1,n){
		for(int p=fir[i];p;p=e[p].nxt){
			int j=e[p].to;
			if(i>j)merge(i,j);//i is the father of j.
		}
	}
	T.dfs(n);
	printf("%lld\n",ans);
	return 0; 
}
```

---

## 作者：Masterwei (赞：5)

提供一种线段树合并做法。

注意到 $t$ 是互不相同的，考虑按 $t$ 降序排列，每次枚举与它右边的节点，如果其的 $t$ 大于当前的 $t$，那么就算贡献。具体的，对于每个点开一颗值域线段树，维护题意中要求满足的条件，即 $v_j\le v_x\le v_i$。算出贡献后，线段树合并即可。

空间复杂度为 $O(n\log v)$，时间复杂度为 $O(n\log v+n\log n)$，其中 $V$ 表示 $v$ 的最大值。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0;bool f=0;char ch=getchar();
	while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
const int Maxn=1e5+5;
int n,a[Maxn],b[Maxn];
int head[Maxn],to[Maxn<<1],nxt[Maxn<<1],cnt1;
inline void add(int u,int v){
	to[++cnt1]=v;nxt[cnt1]=head[u];
	head[u]=cnt1;
}
int id[Maxn];
inline bool cmp(int i,int j){return a[i]>a[j];}
int root[Maxn],cnt;
struct Tree{
	int ls,rs,data;
}t[Maxn*100];
int V;
void change(int&x,int l,int r,int d){
	if(!x)x=++cnt;t[x].data++;
	if(l==r)return;
	int mid=l+r>>1;
	if(mid>=d)change(t[x].ls,l,mid,d);
	else change(t[x].rs,mid+1,r,d);
}
int merge(int x,int y,int l,int r){
	if(!x||!y)return x^y;
	if(l==r){t[x].data+=t[y].data;return x;}
	int mid=l+r>>1;
	t[x].ls=merge(t[x].ls,t[y].ls,l,mid);
	t[x].rs=merge(t[x].rs,t[y].rs,mid+1,r);
	t[x].data=t[t[x].ls].data+t[t[x].rs].data;
	return x;
}
int query(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R)return t[x].data;
	int mid=l+r>>1,res=0;
	if(mid>=L)res=query(t[x].ls,l,mid,L,R);
	if(mid<R)res+=query(t[x].rs,mid+1,r,L,R);
	return res;
}
int f[Maxn];
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
signed main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),f[i]=id[i]=i;
	for(int i=1;i<=n;i++)b[i]=read(),V=max(V,b[i]);
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v);add(v,u);
	}
	sort(id+1,id+1+n,cmp);
	int ans=0;
	for(int j=1;j<=n;j++){
		int tmp=ans;
		int u=id[j];
		change(root[u],1,V,b[u]);
		for(int i=head[u];i;i=nxt[i]){
			int y=find(to[i]);
			if(a[y]>a[u]){
				int tmp=0;
				ans+=u*query(root[y],1,V,1,b[u])*query(root[u],1,V,b[u],V);
				ans+=u*query(root[u],1,V,1,b[u])*query(root[y],1,V,b[u],V);
				f[y]=u;
				root[u]=merge(root[u],root[y],1,V);
			}
		}
		ans+=u;
	}printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：sunkuangzheng (赞：4)

$\textbf{P10975}$

路径问题直接点分治，我们在路径的 $\min$ 一侧统计贡献。记分治中心 $rt$ 到 $u$ 的最小值记为 $pr_u$，则相当于路径有 $pr$ 和 $b$ 两条限制，二维数点即可。注意 $\min$ 在分治中心时会算重，要减去多算的。

时间复杂度 $\mathcal O(n \log^2 n)$，需要轻度卡常。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 20.07.2024 13:06:11
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#else
#define debug(...) 0
#endif
using ll = int;
const int N = 5e5+5;
using namespace std;
int T,n,a[N],b[N],u,v,siz[N],rt,tt,f,vis[N],pre[N],fp[N]; vector<int> _g[N]; long long ans1,ans2,ans[N];
#define ff for(int v : _g[u]) if(!vis[v] && v != f)
vector<int> tp;
int mx = 0;
vector<tuple<int,int,int,int>> g;
struct fwt{
    ll t[N]; ll re;
    void upd(int x,ll p){for(;x <= n + 1;x += x & -x) t[x] += p;}
    ll qry(int x){for(re = 0;x;x -= x & -x) re += t[x]; return re;}
    ll sum(int l,int r){return (l <= r ? qry(r) - qry(l - 1) : 0);}
}t;
inline void add_p(int x,int y,int val){g.emplace_back(-x,0,y,val);};
inline void add_qry(int l,int r,int ql,int qr,int id){
    mx = max(mx,id); 
    g.emplace_back(-l,ql,qr,id);
}inline void solve(){
    sort(g.begin(),g.end());
    for(auto [x,tp,y,id] : g){
        if(!tp) t.upd(y,id); else ans[id] += (t.qry(y) - t.qry(tp - 1)); 
    }for(auto [x,tp,y,id] : g){
        if(!tp) t.upd(y,-id);
    }return ;
}void clr(){mx = 0; for(auto [x,t,y,id] : g) if(t) ans[abs(id)] = 0; g.clear();}
void dfs1(int u,int f,int sz){
    siz[u] = 1; int mx = 0;
    ff dfs1(v,u,sz),siz[u] += siz[v],mx = max(mx,siz[v]);
    if(mx = max(mx,sz - siz[u]),mx < tt) tt = mx,rt = u;
}void dfs3(int u,int f,int vl){vl = min(vl,a[u]),pre[u] = vl,tp.emplace_back(u); ff dfs3(v,u,vl);}
void slv(int u,int op,int vl){
    debug(u);
    if(op == -1) tp.clear(),dfs3(u,0,a[vl]);
    if(op == 1){ tp.clear(),tp.push_back(u),pre[u] = a[u]; ff dfs3(v,u,a[u]);}
    clr(); 
    for(int i : tp){
        add_p(pre[i],b[i],1); 
        int x = fp[pre[i]]; debug(pre[i],b[i],x);
        if(b[i] <= b[x]) add_qry(pre[i],n,b[x],n,i);
        if(b[i] >= b[x]) add_qry(pre[i],n,1,b[x],i);
        if(x == vl){
            if(b[i] <= b[x]) add_qry(pre[i],n,b[x],n,i + n);
            if(b[i] >= b[x]) add_qry(pre[i],n,1,b[x],i + n);
        }
    }solve(); 
    for(int i : tp)
        debug(i,ans[i]),
    	ans1 += op * fp[pre[i]] * ans[i],
		ans2 -= op * fp[pre[i]] * ans[i + n];
	debug(ans1,ans2);
}void dfs2(int u){
    vis[u] = 1,slv(u,1,u);
    ff slv(v,-1,u);
    ff tt = 1e9,dfs1(v,u,siz[v]),dfs2(rt);
}int main(){
    // freopen("1.in","r",stdin),freopen("1.out","w",stdout);
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> n; vector<int> c,d;
    for(int i = 1;i <= n;i ++) cin >> a[i],c.push_back(a[i]);
    for(int i = 1;i <= n;i ++) cin >> b[i],d.push_back(b[i]);
    pre[0] = n;
    sort(c.begin(),c.end()),sort(d.begin(),d.end()),d.erase(unique(d.begin(),d.end()),d.end());
    for(int i = 1;i <= n;i ++) a[i] = lower_bound(c.begin(),c.end(),a[i]) - c.begin() + 1,
                               b[i] = lower_bound(d.begin(),d.end(),b[i]) - d.begin() + 1,
                               fp[a[i]] = i; 
    for(int i = 1;i < n;i ++) cin >> u >> v,_g[u].push_back(v),_g[v].push_back(u);
    tt = 1e9,dfs1(1,0,n),dfs2(rt); 
    debug(ans2),assert(ans2 % 2 == 0),cout << ans1 + ans2 / 2 << "\n";
    fprintf(stderr,"%.3lf ms\n",1e3 * clock() / CLOCKS_PER_SEC);
}
```

---

## 作者：hlsnqdmz (赞：3)

一道练习所谓的点权多叉重构树的好题，可能这东西听起来有点奇怪，其实与 Kruskal 重构树差不多，只不过一个处理边权，一个处理点权，还有些像点分治。

## 这道题此方法的知识前置

1. Kruskal 重构树（思想）
2. 线段树合并
3. 点分治的部分思想
4. 并查集
5. 离散化

## 正式开始
看到题干，我们可以发现要对答案提供贡献要满足两个条件，而这两个条件与 $x$ 有紧密联系（~废话~），所以我们可以对 $x$ 下手，枚举 $x$ 再找到满足条件的点对，最后计算贡献，而 $x$ 是两个点路径上的 $t$ 最小的点，这样的 $x$ 我们想~不~到可以建一棵 Kruskal 重构树，这样两点的 LCA 就是它们路径上的最小值（此处和之后的最小值未说明都代表 $t$ 最小）了，然后我们减去在同一子树不应被计入答案的点，即容斥一下，再继续递归下去就可以了。这样做的原因是你并不好枚举 $i$ 或 $j$，但可以发现枚举 $x$ 有更好做的方法，然后想到此做法（~虽然不好想就是了~）。

## 方法一：
首先就是很像点分治的正常做法（虽然我最开始不是这么做的，但是题解没有多少讲这个的），构造 Kruskal 重构树后 dfs 一遍，求出每个节点的每个子树的满足条件的点对，但会有算重的部分，刚好是一颗子树大于等于 $v$ 和小于等于 $v$ 的点的乘积，最后减掉即可。维护 $v$ 可以用主席树。建树方式从 $t$ 值大到小枚举一个点，找与其相连的点，若相连的点已经访问过就让当前点成为相连点的连通块的根，那么 $t$ 最小的点就会成为整个树的根。

但是这个方法细节不少，调了我一个小时，具体细节代码中有注释。

这里具体讲解一下```ans += (size[u] - 1) * u;``` 和 ```ans += (query(root[dfn[u] + size[u] - 1], 1, len, w[dfn[u]], w[dfn[u]]) - query(root[dfn[u] - 1], 1, len, w[dfn[u]], w[dfn[u]])) * u;``` 两句，我们知道条件都有等于号，所以枚举到点 $u$ 时 $u$ 也会计入贡献，无论 $u$ 的子树的 $v_j$ 值是多少，都会有点对 $(i,j)$ 符合条件，而当 $v_j=v_i$ 时，点对 $(j,i)$ 也可以计入贡献，但是点对 $(i,i)$ 只能被计入一次，所以 $size[u]-1$ 是为了防止重复算入贡献。

给出代码：
```
//Just Sayori
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#define int long long
//↑懂的都懂
#define ll long long
#define rnt register int
#define N 200005
#define M 1000000007
using namespace std;
inline ll read()
{
    ll x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
struct edge
{
    int v, next;
} e[N << 1], _e[N << 2];//这里可以用别的命名，我为了好看就用了下划线
int head[N], cnt, _head[N], _cnt;
inline void tdd(int u, int v)
{
    e[++cnt] = {v, head[u]}, head[u] = cnt;
    e[++cnt] = {u, head[v]}, head[v] = cnt;
}
inline void _tdd(int u, int v)
{
    _e[++_cnt] = {v, _head[u]}, _head[u] = _cnt;
    _e[++_cnt] = {u, _head[v]}, _head[v] = _cnt;
}
struct node
{
    int t, id;//v 单独储存，不然排序后 a[i].v!=v[a[i].id]
} a[N];
int n, len, ans;
int b[N], t[N], v[N], w[N], fa[N], dfn[N], root[N], size[N];
bool vis[N];
int find(int a)
{
    return fa[a] == a ? a : fa[a] = find(fa[a]);
}
struct tree
{
    int lc, rc, num;
} s[N << 5];
inline bool cmp(node aa, node bb)
{
    return aa.t > bb.t;
}
void build(int &u, int l, int r)
{
    if (!u) u = ++cnt;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(s[u].lc, l, mid);
    build(s[u].rc, mid + 1, r);
}
void modify(int &u, int v, int l, int r, int x)
{
    u = ++cnt;//主席树每个节点都要新建
    s[u] = s[v];
    if (l == r) return s[u].num++, void();
    int mid = (l + r) >> 1;
    if (x <= mid) modify(s[u].lc, s[v].lc, l, mid, x);
    else modify(s[u].rc, s[v].rc, mid + 1, r, x);
    s[u].num = s[s[u].lc].num + s[s[u].rc].num;
}
int query(int u, int l, int r, int ls, int rs)
{
    if (ls <= l && r <= rs) return s[u].num;
    int mid = (l + r) >> 1, ans = 0;
    if (ls <= mid) ans += query(s[u].lc, l, mid, ls, rs);
    if (rs >= mid + 1) ans += query(s[u].rc, mid + 1, r, ls, rs);
    return ans;
}
void kruskal()
{
    for (rnt j = 1; j <= n; j++)
    {
        int u = a[j].id;
        for (rnt i = head[u]; i; i = e[i].next)
        {
            int v = find(e[i].v);//记得要 find
            if (!vis[v]) continue;
            fa[v] = u, _tdd(u, v);
        }
        vis[u] = 1;
    }
}
void dfs(int u, int f)
{
    dfn[u] = ++cnt;
    w[cnt] = v[u];
    size[u] = 1;
    for (rnt i = _head[u]; i; i = _e[i].next)
    {
        int v = _e[i].v;
        if (v == f) continue;
        dfs(v, u);
        size[u] += size[v];
    }
}
int q[N];
void work(int u, int f)
{
    int sum = 0;
    for (rnt i = _head[u]; i; i = _e[i].next)
    {
        int v = _e[i].v;
        if (v == f) continue;
        work(v, u);//这里的 w[dfn[u]] 可以用 v[u] 来代替前提是你要把 v[] 改成别的名字。
        int que = query(root[dfn[v] + size[v] - 1], 1, len, w[dfn[u]], len) - query(root[dfn[v] - 1], 1, len, w[dfn[u]], len);
        q[v] = query(root[dfn[v] + size[v] - 1], 1, len, 1, w[dfn[u]]) - query(root[dfn[v] - 1], 1, len, 1, w[dfn[u]]);
        ans -= q[v] * que * u;
        sum += que;
    }
    for (rnt i = _head[u]; i; i = _e[i].next)
    {
        int v = _e[i].v;
        if (v == f) continue;
        ans += q[v] * sum * u;
    }
    ans += (size[u] - 1) * u;
    ans += (query(root[dfn[u] + size[u] - 1], 1, len, w[dfn[u]], w[dfn[u]]) - query(root[dfn[u] - 1], 1, len, w[dfn[u]], w[dfn[u]])) * u;
}
signed main()
{
    n = read();
    for (rnt i = 1; i <= n; i++) a[i].t = read(), a[i].id = i;
    for (rnt i = 1; i <= n; i++) b[i] = v[i] = read(), fa[i] = i;//这里主要不要把 v 跟着去排序，不然无法找到 i 对应的 v。
    for (rnt i = 1; i < n; i++) tdd(read(), read());
    sort(b + 1, b + n + 1);//离散化和按 t 排序。
    len = unique(b + 1, b + n + 1) - b - 1;
    for (rnt i = 1; i <= n; i++)
        v[i] = lower_bound(b + 1, b + len + 1, v[i]) - b;
    sort(a + 1, a + n + 1, cmp);
    kruskal(), cnt = 0;//cnt 要清零，或者用多个变量
    int rt = a[n].id; //t 最小的点就是根
    dfs(rt, 0), cnt = 0;
    build(root[0], 1, len);
    for (rnt i = 1; i <= n; i++) modify(root[i], root[i - 1], 1, len, w[i]);
    work(rt, 0);
    cout << ans;
    return 0;
}
```

## 方法二：
但假如你不想用容斥，也不想建树，你也可以通过排序将 $t_i$ 从大到小枚举，每一次枚举当前点 $u$ 就 枚举与其相连接的点 $v$，如果点 $v$ 已经被访问过，就说明 $t_v \ge t_u$，那么 $v$ 子树上的点与 $u$ 子树上的点的路径上的 $t$ 最小的点就是 $u$，然后就可以计算贡献，这样就不会多算或者少算答案。之后将 $v$ 加入 $u$ 为根的树，使它们连通，这个可以用并查集来维护。

实际上我们是访问与 $u$ 相连的**连通块**，而寻找满足条件的点对就是从与 $u$ 相连且**已经访问过的**的连通块的点和 $v$ 所在的**未访问**连通块的点中分别寻找，设 $l1$ 是已经枚举过的与 $u$ 相连的连通块中 $v\le v_u$ 的个数， $l2$ 是 $v\ge v_u$ 的个数， $n1$ 和 $n2$ 是当前访问的连通块，即 $v$ 所在的连通块的满足条件的点的个数，那么 $ans+=(l1\times n2+l2\times n1)\times u$，然后建一条边使这两个连通块连通，然后 $n1$ 加入 $l1$， $n2$ 加入 $l2$。维护和查询每个点 $v$ 值可以用线段树，这样连通连通块就可以直接使用线段树合并且不需要动态开点，而且要记得离散化。

这个方法的正确性就如图所示：
![](https://cdn.luogu.com.cn/upload/image_hosting/hvqt9t6a.png)

最后给出代码
```
//Just Sayori
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#define int long long
#define ll long long
#define rnt register int
#define N 200005
#define M 1000000007
using namespace std;
inline ll read()
{
    ll x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
struct edge
{
    int v, next;
} e[N << 1];
int head[N], cnt;
void tdd(int u, int v)
{
    e[++cnt] = {v, head[u]}, head[u] = cnt;
    e[++cnt] = {u, head[v]}, head[v] = cnt;
}
struct node
{
    int t, v, id;
} a[N];
int n, len，ans;
int b[N], t[N], v[N], fa[N], root[N];
bool vis[N];
int find(int a)
{
    return fa[a] == a ? a : fa[a] = find(fa[a]);
}
struct tree
{
    int lc, rc, num;
} s[N << 4];//开八倍空间会 RE。
inline bool cmp(node aa, node bb)
{
    return aa.t > bb.t;
}
void modify(int &u, int l, int r, int x)
{
    if (!u) u = ++cnt;
    if (l == r) return s[u].num++, void();
    int mid = (l + r) >> 1;
    if (x <= mid) modify(s[u].lc, l, mid, x);
    else modify(s[u].rc, mid + 1, r, x);
    s[u].num = s[s[u].lc].num + s[s[u].rc].num;
}
void merge(int &u, int v, int l, int r)
{
    if (!u || !v) return u |= v, void();
    if (l == r) return s[u].num += s[v].num, void();
    int mid = (l + r) >> 1;
    merge(s[u].lc, s[v].lc, l, mid);
    merge(s[u].rc, s[v].rc, mid + 1, r);
    s[u].num = s[s[u].lc].num + s[s[u].rc].num;
}
int query(int u, int l, int r, int ls, int rs)
{
    if (ls <= l && r <= rs) return s[u].num;
    int mid = (l + r) >> 1, ans = 0;
    if (ls <= mid) ans += query(s[u].lc, l, mid, ls, rs);
    if (rs >= mid + 1) ans += query(s[u].rc, mid + 1, r, ls, rs);
    return ans;
}
signed main()
{
    n = read();
    for (rnt i = 1; i <= n; i++) a[i].t = read(), a[i].id = i;
    for (rnt i = 1; i <= n; i++) b[i] = a[i].v = read(), fa[i] = i;
    for (rnt i = 1; i < n; i++) tdd(read(), read());
    sort(b + 1, b + n + 1), sort(a + 1, a + n + 1, cmp);//离散化和按 t 排序。
    len = unique(b + 1, b + n + 1) - b - 1, cnt = 0;
    for (rnt i = 1; i <= n; i++)
        a[i].v = lower_bound(b + 1, b + len + 1, a[i].v) - b, modify(root[a[i].id], 1, len, a[i].v);
    for (rnt i = 1; i <= n; i++)
    {
        int u = a[i].id, l1 = 1, l2 = 1;
        ans += u, vis[u] = 1;
        for (rnt j = head[u]; j; j = e[j].next)//注意 i 和 j 不要写混淆了。
        {
            int v = find(e[j].v);
            if (!vis[v]) continue;
            int n1 = query(root[v], 1, len, 1, a[i].v);
            int n2 = query(root[v], 1, len, a[i].v, len);
            ans += (l1 *n2 + l2 *n1) * u, l1 += n1, l2 += n2;
            fa[v] = u, merge(root[u], root[v], 1, len);//线段树合并与并查集相通。
        }
    }
    cout << ans;
    return 0;
}
```

#### 十年OI一场空，不开```long long```见祖宗！

### 感谢您的观看！

#### 审核辛苦了

---

## 作者：_AyachiNene (赞：3)

# 思路：
由于 $t$ 的限制较弱，所以先只考虑 $v$ 的限制。发现枚举题目给的式子中的 $i$ 或 $j$ 是难以计算所有路径的贡献的，假设枚举 $i$，那么 $j$ 和 $x$ 会构成偏序关系难以维护。考虑枚举 $x$，发现这时答案就很好维护，假设 $v_x$ 是全局的最小值，那么只用找比 $v_x$ 小的点的个数和比 $v_x$ 大的个数乘起来，还有相反的路径也算上就行了。现在考虑 $t$ 的限制，由于要找最小的 $t$，想到 Kruskal，令一条边 $(x,y)$ 的边权为 $\min(t_x,t_y)$。发现只建最大生成树难以维护，想到建重构树，这样路径问题就转化为子树问题，随便什么算法都能做，这里就不讲了。
# Code:
用的线段树合并。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace IO
{
	char buff[1<<21],*p1=buff,*p2=buff;
	char getch(){return p1==p2&&(p2=((p1=buff)+fread(buff,1,1<<21,stdin)),p1==p2)?EOF:*p1++;}
	template<typename T>void read(T &x){char ch=getch();int fl=1;x=0;while(ch>'9'||ch<'0'){if(ch=='-')fl=-1;ch=getch();}while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getch();}x*=fl;}
	template<typename T>void read_s(T &x){char ch=getch();while(ch<'a'||ch>'z')ch=getch();while(ch>='a'&&ch<='z'){x+=ch;ch=getch();}}
	template<typename T,typename ...Args>void read(T &x,Args& ...args){read(x);read(args...);}
	char obuf[1<<21],*p3=obuf;
	void putch(char ch) {if(p3-obuf<(1<<21))*p3++=ch;else fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=ch;}
	char ch[100];
	template<typename T>void write(T x) {if(!x)return putch('0');if(x<0)putch('-'),x*=-1;int top=0;while(x)ch[++top]=x%10+48,x/=10;while(top)putch(ch[top]),top--;}
	template<typename T,typename ...Args>void write(T x,Args ...args) {write(x);write(args...);}
	void put(string s){for(int i=0;i<s.size();i++)putch(s[i]);}
	void flush(){fwrite(obuf,p3-obuf,1,stdout);}
}
using namespace IO;
struct node
{
	int nxt,to;
}e[200005];
int head[200005],cnt_edge;
void add_edge(int u,int v)
{
	e[++cnt_edge].to=v;
	e[cnt_edge].nxt=head[u];
	head[u]=cnt_edge;
}
int n;
int a[200005],b[200005];
struct edge
{
	int u,v,w;
	bool operator<(const edge &x)const{return a[w]>a[x.w];}
}edge[200005];
int cnt;
namespace Nene
{
	int f[200005];
	int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
}
namespace Elaina
{
	struct segt
	{
		int l,r,val;
	}t[1000005<<3];
	int cnt,rt[200005];
	#define mid (l+r>>1)
	void update(int root){t[root].val=t[t[root].l].val+t[t[root].r].val;}
	void insert(int x,int v,int &root,int l=1,int r=1e9)
	{
		if(!root) root=++cnt;
		if(l==r)
		{
			t[root].val+=v;
			return;
		}
		if(x<=mid) insert(x,v,t[root].l,l,mid);
		else insert(x,v,t[root].r,mid+1,r);
		update(root);
	}
	void merge(int &x,int y,int l=1,int r=1e9)
	{
		if(!x||!y){x=(x|y);return;}
		if(l==r)
		{
			t[x].val+=t[y].val;
			return;
		}
		merge(t[x].l,t[y].l,l,mid);merge(t[x].r,t[y].r,mid+1,r);
		update(x);
	}
	int query(int x,int y,int root,int l=1,int r=1e9)
	{
		if(!root) return 0;
		if(l>=x&&r<=y) return t[root].val;
		int res=0;
		if(x<=mid) res+=query(x,y,t[root].l,l,mid);
		if(y>mid) res+=query(x,y,t[root].r,mid+1,r);
		return res;
	}
}using Elaina::insert;using Elaina::query;using Elaina::merge;using Elaina::rt;
int ans;
int w[200005];
void dfs(int u)
{
	if(u<=n) insert(b[u],1,rt[u]);
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		dfs(v);	
		int wu1=query(1,b[w[u]],rt[u]),wu2=query(b[w[u]],1e9,rt[u]);
		int wv1=query(1,b[w[u]],rt[v]),wv2=query(b[w[u]],1e9,rt[v]);
		ans+=(wu1*wv2+wu2*wv1)*w[u];
//		cout<<u<<" "<<wu1<<" "<<wu2<<" "<<wu3<<endl;
//		cout<<v<<" "<<wv1<<" "<<wv2<<" "<<wv3<<" "<<(wu1*wv2+wu2*wv1-wu3*wv3)*w[u]<<endl<<endl;
		merge(rt[u],rt[v]);
	}
}
signed main()
{
	read(n);cnt=n;
	for(int i=1;i<=n;i++) read(a[i]);
	for(int i=1;i<=n;i++) read(b[i]);
	for(int i=1;i<=2*n;i++) Nene::f[i]=i;
	for(int i=1;i<n;i++) read(edge[i].u,edge[i].v),edge[i].w=a[edge[i].u]<a[edge[i].v]?edge[i].u:edge[i].v;
	sort(edge+1,edge+n);
	for(int i=1;i<=n;i++) ans+=i;
	for(int i=1;i<n;i++)
	{
		int fx=Nene::find(edge[i].u),fy=Nene::find(edge[i].v);
		if(fx==fy) continue;
		++cnt;
		Nene::f[fx]=Nene::f[fy]=cnt;
		w[cnt]=edge[i].w;
//		cout<<cnt<<' '<<fx<<" "<<edge[i].w<<"\n"<<cnt<<" "<<fy<<" "<<edge[i].w<<endl;
		add_edge(cnt,fx);add_edge(cnt,fy);
	}
	dfs(cnt);
	write(ans);
	flush();
}
```

---

## 作者：Shunpower (赞：3)

出题人题解。

考虑下面这种重构树方式：

按 $t_i$ 从大到小枚举每一个点，并枚举它的所有出边。假设枚举 $i$ 时找到点 $j$ 与点 $i$ 相邻，若 $j$ 已经被枚举过，则在重构树中在 $i$ 与 $j$ 所在连通块目前的根节点之间连一条边，使 $i$ 成为它们新的根节点。

这样重构出的树的好处是：任意两点的 LCA 的权值为原树上两点间点权最小的点的权值。

之后考虑枚举 LCA，也就是原树中的 $x$ 点，那么需要找到以它为 LCA 的路径中一端的 $v$ 小于等于自己，一端的 $v$ 大于等于自己的数量。

可以给每个儿子都跑出来这两个东西，然后枚举儿子，考虑它贡献路径的一端，把剩下的儿子对另一端的贡献求和（显然可以用总和减掉这一个子树）乘过来，对于每个儿子求和即可。注意有些实现可能还要加上以本身作为 LCA 的直上直下的路径对答案的贡献以及自己到自己的路径对答案的贡献。

此外，一些实现还要注意 $(i,j)$ 与 $(j,i)$ 的重复贡献与未能贡献的问题。

至于如何算出子树中 $\leq v$ 或者 $\geq v$ 的值的数量，可以直接拍平树到 DFS 序上做主席树，也可以离线后对 $2n$ 个询问进行 dsu on tree。做法很多，这里不再细讲。

-------------

下面是 std。

```cpp
int n;
int t[N],v[N];
pii rec[N];
vector <int> p[N];
vector <int> r[N];
int f[N];
bool vis[N];
int finder(int x){
    if(f[x]!=x) f[x]=finder(f[x]);
    return f[x];
}
int tot;
int dfn[N],siz[N];
int rv[N];
vector <int> tmp;
void dfs(int x,int fa){
    tot++;
    siz[x]=1;
    dfn[x]=tot;
    rv[tot]=v[x];
    for(auto y:r[x]){
        if(y==fa) continue;
        dfs(y,x);
        siz[x]+=siz[y];
    }
}
int rt[N];
#define mid (l+r>>1)
struct pre_sgt{
    int tot;
    int ls[N*80],rs[N*80],sum[N*80];
    void insert(int &rt,int las,int l,int r,int d){
        if(!rt){
            tot++;
            rt=tot;
        }
        sum[rt]=sum[las]+1;
        if(l==r) return;
        if(d<=mid){
            insert(ls[rt],ls[las],l,mid,d);
            rs[rt]=rs[las];
        }
        else{
            insert(rs[rt],rs[las],mid+1,r,d);
            ls[rt]=ls[las];
        }
    }
    int query(int p,int l,int r,int ml,int mr){
        if(ml<=l&&r<=mr) return sum[p];
        int ans=0;
        if(ml<=mid) ans+=query(ls[p],l,mid,ml,mr);
        if(mid<mr) ans+=query(rs[p],mid+1,r,ml,mr);
        return ans;
    }
} T;
#undef mid
int stquery(int tt,int l,int r){
    return T.query(rt[dfn[tt]+siz[tt]-1],1,n,l,r)-T.query(rt[dfn[tt]-1],1,n,l,r);
}
ll ans;
int ol[N];
void calc(int x,int fa){
    ll sum=0;
    for(auto y:r[x]){
        if(y==fa) continue;
        calc(y,x);
        ol[y]=stquery(y,rv[dfn[x]],n);
        sum+=ol[y];
    }
    for(auto y:r[x]){
        ans+=1ll*stquery(y,1,rv[dfn[x]])*(sum-ol[y])*x;
    }
    ans+=1ll*(siz[x]-1)*x+1ll*stquery(x,rv[dfn[x]],rv[dfn[x]])*x;
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n;
    fr1(i,1,n) cin>>t[i];
    fr1(i,1,n) cin>>v[i];
    fr1(i,2,n){
        int u,v;
        cin>>u>>v;
        p[u].pb(v);
        p[v].pb(u);
    }
    fr1(i,1,n) f[i]=i;
    fr1(i,1,n) rec[i]=mp(i,t[i]);
    sort(rec+1,rec+n+1,[](pii &x,pii &y){
        return x.se>y.se;
    });
    int trt=rec[n].fi;
    fr1(i,1,n){
        int x=rec[i].fi;
        for(auto j:p[x]){
            if(vis[j]){
                r[x].pb(finder(j));
                f[finder(j)]=finder(x);
            }
        }
        vis[x]=1;
    }
    dfs(trt,0);
    fr1(i,1,n) tmp.pb(rv[i]);
    sort(tmp.begin(),tmp.end());
    tmp.resize(unique(tmp.begin(),tmp.end())-tmp.begin());
    fr1(i,1,n) rv[i]=lower_bound(tmp.begin(),tmp.end(),rv[i])-tmp.begin()+1;
    fr1(i,1,n) T.insert(rt[i],rt[i-1],1,n,rv[i]);
    calc(trt,0);
    cout<<ans<<'\n';
    ET;
}
```

---

## 作者：Union_Find (赞：1)

这题要同时满足两个条件，且两个条件都与 $x$ 有关，答案也和 $x$ 有关，所以考虑枚举 $x$ 去求贡献。

我们知道，在确定 $x$ 时，满足 $t_y < t_x$ 的 $y$ 是要断开的。所以我们可以先将所有点按照 $t$ 排序，然后依次加入点，考虑贡献就比较简单了。

注意到 $x$ 的贡献只有 $v_i \le v_x \le v_j$ 这一个贡献了。所以我们可以把所有与 $x$ 相连的连通块取出来。假设我们考虑到一个连通块，前面所有连通块中 $v_y \le v_x$ 的 $y$ 的数量是 $sx1$，$v_y \ge v_x$ 的 $y$ 的数量是 $sx2$。这个连通块 $v_y \le v_x$ 的 $y$ 的数量是 $p1$，$v_y \ge v_x$ 的 $y$ 的数量是 $p2$。那么贡献会加上 $(p1\times sx2 + p2 \times sx1) \times x$。所以我们的问题就是快速求出 $p1$ 和 $p2$ 了。

注意到 $p1$ 和 $p2$ 与 $v$ 的权值有关系，加上是大小关系的限制，考虑权值线段树。每次加上一个点之后，就把两个连通块的线段树合并。当然，为了表示连通块，我们使用并查集，这样就可以用一个点代表一个连通块了。

最后注意，枚举邻居的时候，如果邻居还未考虑过，就不能参与计算贡献。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 100005
#define ls(x) (lower_bound(nls + 1, nls + cnt + 1, x) - nls)
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
ll n, u, v, nls[N], cnt, fa[N], ans, vis[N];
ll tr[N << 5], ls[N << 5], rs[N << 5], ep, rt[N];
il ll find(ll x){return fa[x] == x ? x : fa[x] = find(fa[x]);}
struct P{
	ll t, v, id;
}p[N];
il bool cmp(P a, P b){return a.t > b.t;}
vector <ll> e[N];
void add(ll &p, ll l, ll r, ll x, ll k){
	if (!p) p = ++ep;
	if (l == r) return tr[p] += k, void(0);
	ll mid = (l + r) >> 1;
	if (x <= mid) add(ls[p], l, mid, x, k);
	else add(rs[p], mid + 1, r, x, k);
	tr[p] = tr[ls[p]] + tr[rs[p]];
}ll ask(ll p, ll l, ll r, ll nl, ll nr){
	if (!p) return 0;
	if (nl <= l && r <= nr) return tr[p];
	ll mid = (l + r) >> 1, ans = 0;
	if (nl <= mid) ans += ask(ls[p], l, mid, nl, nr);
	if (nr > mid) ans += ask(rs[p], mid + 1, r, nl, nr);
	return ans;
}ll merge(ll u, ll v, ll l, ll r){
	if (!u || !v) return u | v;
	if (l == r) return tr[u] += tr[v], u;
	ll mid = (l + r) >> 1;
	ls[u] = merge(ls[u], ls[v], l, mid), rs[u] = merge(rs[u], rs[v], mid + 1, r);
	tr[u] = tr[ls[u]] + tr[rs[u]];
	return u;
}
int main(){
	n = rd();
	for (int i = 1; i <= n; i++) p[i].t = rd(), p[i].id = i;
	for (int i = 1; i <= n; i++) p[i].v = rd(), nls[i] = p[i].v;
	sort (p + 1, p + n + 1, cmp);
	sort (nls + 1, nls + n + 1);
	cnt = unique(nls + 1, nls + n + 1) - nls - 1;
	for (int i = 1; i <= n; i++)
		p[i].v = ls(p[i].v), add(rt[p[i].id], 1, cnt, p[i].v, 1), fa[i] = i;
	for (int i = 1; i < n; i++) u = rd(), v = rd(), e[u].push_back(v), e[v].push_back(u);
	for (int i = 1; i <= n; i++){
		ll u = p[i].id, sx1 = 1, sx2 = 1;
		ans += u;
		for (int v : e[u]){
			if (!vis[v]) continue;
			ll fv = find(v);
			ll p1 = ask(rt[fv], 1, cnt, p[i].v, cnt), p2 = ask(rt[fv], 1, cnt, 1, p[i].v);
			ans += (p1 * sx2 + p2 * sx1) * u, sx1 += p1, sx2 += p2;
		}for (int v : e[u]){
			if (!vis[v]) continue;
			ll fv = find(v);
			fa[fv] = u, rt[u] = merge(rt[u], rt[fv], 1, cnt);
		}vis[u] = 1;
	}printf ("%lld\n", ans);
	return 0;
}

```

---

## 作者：Richard_Whr (赞：1)

看到路径上最小权是关键，想到 Kruskal 重构树。

重定义边权： $w(u,v)=\min(t_u,t_v)$。

从大到小对边权排序后建重构树，这样问题转化为了在 lca 上统计不同子树之间的贡献了。

具体而言，对于当前节点 $u$，统计这样的对数 $(x,y)$，记为 $g_u$：

- $x,y$ 在 $u$ 的不同子树；
- $v_x \le v_u \le v_y \vee v_y \le v_u \le v_x$

$u$ 节点的贡献就是 $u \times g_u$

显然可以线段树合并或树上启发式合并。

复杂度根据实现可以是 $O(n \log n)$ 或者 $O(n \log^2n)$。

如果不建重构树，排序后直接用并查集在合并的时候算贡献应该也行。

放一个树上启发式合并的代码： 


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int t[N],w[N],id[N],val[N];
int dfn[N],L[N],R[N],sz[N],seq[N],son[N],ts;
vector<int> e[N];
int p[N];
struct edge
{
	int a,b,c;
	bool operator<(const edge &B)const
	{
		return c>B.c;
	}
}E[N];
int n,m,res;
vector<int> nums;
struct Bit
{
	int tr[N];
	int lowbit(int x)
	{
		return x&-x;
	} 
	void add(int x,int c)
	{
		for(int i=x;i<=m;i+=lowbit(i)) tr[i]+=c;
	}
	int sum(int x)
	{
		int res=0;
		for(int i=x;i;i-=lowbit(i)) res+=tr[i];
		return res;
	}
	int sum(int l,int r)
	{
		return sum(r)-sum(l-1);
	}
}Bit;

int find(int x)
{
	if(p[x]!=x) return p[x]=find(p[x]);
	return p[x];
}

void dfs(int u)
{
	if(u<=n) L[u]=R[u]=++ts,sz[u]=1,seq[ts]=u;
	else L[u]=n+1,R[u]=0,sz[u]=0;
	for(auto v:e[u])
	{
		dfs(v);
		L[u]=min(L[u],L[v]),R[u]=max(R[u],R[v]);
		if(sz[v]>sz[son[u]]) son[u]=v;
		sz[u]+=sz[v];
	}
}

void Dfs(int u,int c)
{
	for(auto v:e[u])
	{
		if(v==son[u]) continue;
		Dfs(v,0);
	}
	if(son[u]) Dfs(son[u],1);
	int P=val[u];
	for(auto v:e[u])
	{
		if(v==son[u]) continue;
		for(int i=L[v];i<=R[v];i++)
		{
			int x=seq[i];			
			if(w[x]>w[P]) res+=P*Bit.sum(1,w[P]);
			else if(w[x]<w[P]) res+=P*Bit.sum(w[P],m);
			else res+=P*Bit.sum(1,m)+P*Bit.sum(w[P],w[P]);
		}
		for(int i=L[v];i<=R[v];i++)
		{
			int x=seq[i];
			Bit.add(w[x],1);
		}
	}
	if(u<=n) Bit.add(w[u],1),res+=u;
	if(!c)
	{
		for(int i=L[u];i<=R[u];i++)
		{
			int x=seq[i];
			Bit.add(w[x],-1); 
		}
	}
}

signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	
	cin>>n;
	for(int i=1;i<=n;i++) cin>>t[i],nums.push_back(t[i]);
	sort(nums.begin(),nums.end());
	nums.erase(unique(nums.begin(),nums.end()),nums.end());
	for(int i=1;i<=n;i++) t[i]=lower_bound(nums.begin(),nums.end(),t[i])-nums.begin()+1; 
	
	nums.clear();
	for(int i=1;i<=n;i++) cin>>w[i],nums.push_back(w[i]);
	sort(nums.begin(),nums.end());
	nums.erase(unique(nums.begin(),nums.end()),nums.end());
	m=nums.size();
	for(int i=1;i<=n;i++) w[i]=lower_bound(nums.begin(),nums.end(),w[i])-nums.begin()+1;
	for(int i=1;i<=n;i++) id[t[i]]=i;
	
	for(int i=1,a,b;i<n;i++)
	{
		cin>>a>>b;
		E[i]={a,b,min(t[a],t[b])};
	}
	
	sort(E+1,E+n);
	for(int i=1;i<=n*2;i++) p[i]=i;
	
	int tot=n;
	for(int i=1;i<n;i++)
	{
		int a=E[i].a,b=E[i].b,c=E[i].c;
		val[++tot]=id[c];
		a=find(a),b=find(b);
		e[tot].push_back(a),e[tot].push_back(b);
		p[a]=tot,p[b]=tot;
	}	
	
	dfs(tot);
	
	Dfs(tot,1);
	
	cout<<res<<"\n";
	
	return 0;
}
```

---

## 作者：TLE_AK (赞：0)

一天在某群里看到了**树上笛卡尔树**这个奇妙的玩意，故此写篇题解。

~~所以出题人怎么想到这奇妙玩意的~~
### 题意


给你一棵无根树，每个点 $i$ 有两个属性 $t_i,v_i$。

令 $f_{i,j}=[v_j \le v_x \le v_i]$，其中 $x$ 为路径上 $t_i$ 最小的点。

求 $\sum\limits_{i=1}^n\sum\limits_{j=1}^n f_{i,j}$。

## 思路
观察到特殊性质 B 有链，考虑此时该怎么做。

我们意外的发现满足笛卡尔树的性质，所以对于每个笛卡尔树上的 lca 直接统计答案即可。

又注意到特殊性质 A，发现此时直接线段树合并或树上启发式合并即可。

回到原题，现在我们要构造出这样的树：
- 对于一个点 $x$，$t_x$ 小于子树内所有 $t_i$。
- 对于一个点对 $a,b$，其在树上的 lca 也在原图路径。

我们先根据 $t_i$ 降序排序，对于每个 $i$ 所连的边，如果 $t_j>t_i$ 且不在一个连通块，就连一条边。最后将根设为 $t_i$ 最小的点。

对于第一个限制，因为总是由小的连大的，所以能保证正确性。  
对于第二个限制，我们注意到连通块只是连着自己的儿子与父亲,所以满足题目限制的点对一定会经过新树上的 lca。

在新树上做线段树合并即可。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
#define int long long

namespace acac
{
	struct node
	{
		int t,v,id;
	}A[100010];
	
	bool cmp(node a,node b)
	{
		return a.t>b.t;
	}
	
	int ls[100010];
	map<int,int>mp;
	
	struct edge
	{
		int to,ne;
	}e[200010],e2[200010];
	int H[100010],H2[100010],T[100010];
	int cnt=0;
	//线段树
	void add(edge e[],int H[],int a,int b)
	{
	//	if(a<=b)cout<<a<<' '<<b<<endl;
		e[++cnt].to=b;
		e[cnt].ne=H[a];
		H[a]=cnt;
	}
	
	int tree[12800010][4],rt[100010],ys[100010];
	//sum,ls,rs
	int ds,n,tot,ans;
	
	void pu(int u)
	{
		tree[u][0]=tree[tree[u][1]][0]+tree[tree[u][2]][0];
	}
	
	void c(int &u,int l,int r,int w)
	{
		if(l>w||w>r)return ;
		if(!u)u=++ds;
		if(l==r)
		{
			tree[u][0]++;
			return ;
		}
		int mid=(l+r)>>1;
		c(tree[u][1],l,mid,w);
		c(tree[u][2],mid+1,r,w);
		pu(u);
	}
	
	int merge(int u,int u2,int l,int r)
	{
		if((!u)||(!u2))return u+u2;
		if(l==r)
		{
			tree[u][0]+=tree[u2][0];
			return u;
		}
		int mid=(l+r)>>1;
		tree[u][1]=merge(tree[u][1],tree[u2][1],l,mid);
		tree[u][2]=merge(tree[u][2],tree[u2][2],mid+1,r);
		pu(u);
		return u;
	}
	
	int q(int u,int l,int r,int L,int R)
	{
		if(!u||L>R||L>r||l>R)return 0;
		if(L<=l&&R>=r)return tree[u][0];
		int mid=(l+r)>>1;
		return q(tree[u][1],l,mid,L,R)+q(tree[u][2],mid+1,r,L,R);
	}
	//并查集
	int bcj[100010];
	int belong(int u)
	{
	//	cout<<u<<endl; 
		if(bcj[u]!=u)return bcj[u]=belong(bcj[u]);
		return u;
	}
	
	void build()
	{
//建树
		for(int i=1;i<=n;i++)
		{
			bcj[i]=i;
		}
		for(int i=1;i<=n;i++)
		{
			int u=A[i].id;
			T[u]=1;
//确定大小
		//	cout<<A[i].t<<endl;
			for(int j=H[u];j;j=e[j].ne)
			{
				int v=e[j].to;
				if(T[v])
				{
					int al=belong(u),bl=belong(v);
					if(al==bl)continue;//这句话也可以不加
					bcj[bl]=al;
					add(e2,H2,al,bl),add(e2,H2,bl,al);
				}
			}
		}
	}
	
	void dfs(int u,int fa)
	{
		int num=0;
		c(rt[u],1,tot,ys[u]);
		
		for(int i=H2[u];i;i=e2[i].ne)
		{
			int v=e2[i].to;
			if(v==fa)continue;
			dfs(v,u);
			num+=q(rt[u],1,tot,1,ys[u])*q(rt[v],1,tot,ys[u]+1,tot);//小于等于&大于
			num+=(q(rt[u],1,tot,1,tot)+q(rt[u],1,tot,ys[u],ys[u]))*q(rt[v],1,tot,ys[u],ys[u]);//不受限制（等于取两边）&等于
			num+=q(rt[u],1,tot,ys[u],tot)*q(rt[v],1,tot,1,ys[u]-1);//大于&小于
			
			rt[u]=merge(rt[u],rt[v],1,tot);
		}
		num++;
	//	cout<<u<<' '<<ys[u]<<' '<<num<<endl;
		ans+=num*u;
	}

	int main()
	{
		//n used
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%lld",&A[i].t);
			A[i].id=i;
		}
		for(int i=1;i<=n;i++)
		{
			scanf("%lld",&A[i].v);
			ls[i]=A[i].v;
		}
		for(int i=1;i<n;i++)
		{
			int a,b;
			scanf("%lld%lld",&a,&b);
			add(e,H,a,b),add(e,H,b,a);
		}
		cnt=0;
		sort(ls+1,ls+1+n);
		for(int i=1;i<=n;i++)
		{
			if(ls[i]!=ls[i-1])++tot;
			mp[ls[i]]=tot;
			
		}
		for(int i=1;i<=n;i++)
		{
			A[i].v=mp[A[i].v];
			ys[i]=A[i].v;
		}
		sort(A+1,A+1+n,cmp);
	//	cout<<"H\n";
		build();
		dfs(A[n].id,0);
		cout<<ans;
		return 0;
	}
}
#undef int
int main()
{
	acac::main();
	return 0;
}
/*
6
1 3 4 5 2 6
19 1 9 8 1 1
1 2
1 3
2 4
2 5
3 6
*/
```

---

## 作者：takanashi_mifuru (赞：0)

看这个形式容易发现和 $t$ 很相关，我们按 $t$ 从大到小排序，容易发现我们只需要统计我们当前所属联通块的路径的贡献。

那我们把 $v$ 插进权值线段树里面然后做一个线段树合并就可以了，注意这个东西有方向，别乱去重，还有记得用并查集存储联通块节点存储位置。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
struct node{
    int t,v,id;
    bool friend operator < (const node &a,const node &b){
        return a.t<b.t;
    }
}A[100005];
vector<int> ljb[100005];
int rnk[100005];
class SegTree{
    public:
    int rt[100005];
    int lson[100005<<5];
    int rson[100005<<5];
    int Tree[100005<<5];
    int tot;
    void pushup(int cur){
        return Tree[cur]=Tree[lson[cur]]+Tree[rson[cur]],void();
    }
    void insert(int &cur,int lt,int rt,int Q,int x){
        if(lt>Q||rt<Q)return;
        if(!cur)cur=++tot;
        if(lt==rt)return Tree[cur]=x,void();
        int mid=lt+rt>>1;
        insert(lson[cur],lt,mid,Q,x),insert(rson[cur],mid+1,rt,Q,x);
        pushup(cur);
        return;
    }
    int merge(int x,int y,int lt,int rt){
        if(!x||!y)return x|y;
        if(lt==rt){
            Tree[x]+=Tree[y];
            return x;
        }
        int mid=lt+rt>>1;
        lson[x]=merge(lson[x],lson[y],lt,mid);
        rson[x]=merge(rson[x],rson[y],mid+1,rt);
        pushup(x);
        return x;
    }
    int query(int cur,int lt,int rt,int qx,int qy){
        if(lt>qy||rt<qx)return 0;
        if(!cur)return 0;
        if(lt>=qx&&rt<=qy)return Tree[cur];
        int mid=lt+rt>>1;
        return query(lson[cur],lt,mid,qx,qy)+query(rson[cur],mid+1,rt,qx,qy);
    }
}P;
int father[100005];
int find(int x){
    return father[x]==x?x:father[x]=find(father[x]);
}
signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld",&A[i].t);
        rnk[i]=A[i].t;
        A[i].id=i;
    }
    for(int i=1;i<=n;i++){
        scanf("%lld",&A[i].v);
    }
    for(int i=1;i<=n;i++){
        P.insert(P.rt[i],1,1e9,A[i].v,1);
        father[i]=i;
    }
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%lld%lld",&u,&v);
        ljb[u].push_back(v);
        ljb[v].push_back(u);
    }
    sort(A+1,A+1+n);
    int ans=0;
    for(int i=n;i>=1;i--){
        int sum=1;
        int now=find(A[i].id);
        for(int j=0;j<ljb[A[i].id].size();j++){
            int v=ljb[A[i].id][j];
            if(rnk[v]<A[i].t)continue;
            v=find(v);
            sum+=(P.query(P.rt[now],1,1e9,A[i].v,1e9)*P.query(P.rt[v],1,1e9,1,A[i].v)+
            P.query(P.rt[now],1,1e9,1,A[i].v)*P.query(P.rt[v],1,1e9,A[i].v,1e9));
            P.rt[now]=P.merge(P.rt[now],P.rt[v],1,1e9);
            father[v]=now;
        }
        ans+=(sum)*A[i].id;
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

