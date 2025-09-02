# [ICPC 2024 Xi'an I] Fix the Tree

## 题目描述

给定一棵由 $n$ 个顶点组成的树。树中每个顶点 $i$ 都有一个值 $w_i$。

现在顶点 $u$ 将被破坏。一旦被破坏，顶点 $u$ 和所有以 $u$ 为一端的边将从树中移除。

为了使树重新连通，你可以执行以下操作任意次（可能为零次），顺序不限：

- 首先从树中选择两个顶点 $u$ 和 $v$；
- 然后支付 $w_u + w_v$ 个硬币，并在顶点 $u$ 和 $v$ 之间添加一条边；
- 最后，将 $w_u + 1$ 替换为 $w_u$，将 $w_v + 1$ 替换为 $w_v$。

你的任务是计算需要支付的最小硬币数。

但你不知道哪个顶点是 $u$，所以你需要为每个 $1 \le u \le n$ 找到答案。请独立回答所有查询。

## 说明/提示

给定一个有 $n$ 个点组成的树，每个点有一个权值 $w_i$。
点 $u$ 和相邻的边被删除。
你可以进行以下操作任意次数（可以为 $0$），让树重新成为连通图：
1. 选择两个点 $u$、$v$；
2. 花费 $w_u + w_v$ 的代价连接一条边 $(u,v)$；
3. $w_u \leftarrow w_u+1, w_v \leftarrow w_v+1$。

对于每个 $u$ 计算最小代价。（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
6
1 1 1 1 1 1
1 2
1 3
1 4
2 5
2 6```

### 输出

```
4 4 0 0 0 0```

## 样例 #2

### 输入

```
4
1 2 3 4
1 2
1 3
1 4```

### 输出

```
12 0 0 0```

## 样例 #3

### 输入

```
7
1 2 3 4 5 6 7
1 2
1 3
2 4
2 5
3 6
3 7```

### 输出

```
5 12 16 0 0 0 0```

# 题解

## 作者：huangleyi0129 (赞：1)

直接考虑 $O(n)$ 的做法。

对于每个点 $u$，删去 $u$ 后形成的每一联通块都要有点被选择，显然选最小是不劣的，可以用换根 DP 解决。

设 $deg_u=d$，一共要连 $d-1$ 条边，故还要选 $res=d-3$ 个点，容易证明可以任意选择。

将所以点权扔进桶 $cnt$ 里，从最小非 $0$ 处开始扫，逐次删除，$res\Leftarrow res-cnt_i$，并将 $cnt_i$ 加到 $cnt_{i+1}$ 里。

因为 $res$ 每次操作至少减 $1$，所以单点复杂度 $O(deg_u)$。

$\sum O(deg_u)=O(n)$。目前最优解。

代码如下：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1000005;
vector<int>e[N],p;
int w[N],t[N],f[N],g[N],fa[N],n,mn=N,mn2=N;
void dfs(const int k)
{
	f[k]=w[k];
	int mn=w[k],mn2=w[k];
	for(int i:e[k])
		if(i!=fa[k])
		{
			fa[i]=k,dfs(i),f[k]=min(f[k],f[i]);
			if(f[i]<mn)
				mn2=mn,mn=f[i];
			else if(f[i]<mn2)
				mn2=f[i];
		}
	for(int i:e[k])
		if(i!=fa[k])
			if(f[i]==mn)
				g[i]=mn2;
			else
				g[i]=mn;
}
void dfs2(const int k)
{
	for(int i:e[k])
		if(i!=fa[k])
			g[i]=min(g[i],g[k]),dfs2(i);
}
void calc(const int k)
{
	if(p.size()==1)
		return cout<<0<<' ',void();
	int st=mn;
	long long ans=0,s=0,d=p.size()-2;
	if(w[k]==mn)
		st=mn2;
	--t[w[k]];
	for(int i:p)
		ans+=i,--t[i],++t[i+1];
	for(int i=st;d;++i)
	{
		if(d>t[i]+s)
			s+=t[i],d-=s,ans+=s*i;
		else
		{
			ans+=d*i;
			break;
		} 
	}
	for(int i:p)
		++t[i],--t[i+1];
	++t[w[k]];
	cout<<ans<<' ';
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n;
	int u,v;
	for(int i=1; i<=n; ++i)
	{
		cin>>w[i],++t[w[i]];
		if(w[i]<mn)
			mn2=mn,mn=w[i];
		else if(w[i]<mn2)
			mn2=w[i];
	}
	for(int i=1; i<n; ++i)
		cin>>u>>v,e[u].push_back(v),e[v].push_back(u);
	dfs(1);
	g[1]=n+1,dfs2(1);
	for(int i:e[1])
		p.push_back(f[i]);
	calc(1);
	for(int i=2;i<=n;++i)
	{
		p.clear();
		for(int j:e[i])
			if(j!=fa[i])
				p.push_back(f[j]);
		p.push_back(g[i]);
		calc(i);
	}
	return 0;
}
```

---

## 作者：honglan0301 (赞：1)

被 goodier 秒了。

## 分析

注意到删去一个点 $i$ 会把树分割成 $deg_i$ 个连通块，而 $O(\sum deg)=O(n)$，于是试图找到 $O(\text{poly}(deg))$ 处理单次询问的方法。

不妨先考虑每个连通块均只有一个点的情况。我们把代价 $w_u+w_v$ 拆到两个点上，于是只需关心每个点的度数 $d_i$。而显然地，一个度数序列合法当且仅当 $\sum d_i=2(deg-1)$ 且 $\forall i,\ d_i>0$。那么先强制将每个点都选一次，然后每次贪心选代价最小的点即可（选每个点的代价随着选该点的次数单调递增，因此贪心是正确的）。

原问题其实也基本一致。每个连通块可被视为整体，那么令连通块的代价为其中所有点代价的最小值，执行以上算法即可。

每个连通块要么是一棵子树，要么是一棵子树外的所有点，在 $\text{dfn}$ 区间上都只有 $O(1)$ 个连续段，可以线段树维护单点修区间 $\min$，时间复杂度 $O(\sum deg\log n)=O(n\log n)$。

## 代码

```cpp
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define int long long

int n,w[1000005],lw[1000005],u,v,fa[1000005],cntd,dfn[1000005],fdfn[1000005],sz[1000005];
vector <int> e[1000005];

void dfs0(int x,int fat)
{
	dfn[x]=++cntd; fdfn[cntd]=x; sz[x]=1;
	for(auto i:e[x])
	{
		if(i==fat) continue; fa[i]=x; dfs0(i,x); sz[x]+=sz[i];
	}
}

struct tree
{
	int mn;
}tree[4000005];

int getm(int x,int y) {return w[x]<w[y]?x:y;}
#define ls(x) (x<<1)
#define rs(x) ((x<<1)|1)
#define m(x) tree[x].mn
#define push_up(x) m(x)=getm(m(ls(x)),m(rs(x)))
#define md(x,y) ((x+y)>>1)

void build(int l,int r,int p)
{
	if(l==r) return m(p)=fdfn[l],void(); int mid=md(l,r);
	build(l,mid,ls(p)); build(mid+1,r,rs(p)); push_up(p);
}
void cz(int l,int r,int x,int p)
{
	if(l==r) return; int mid=md(l,r);
	if(mid>=x) cz(l,mid,x,ls(p)); else cz(mid+1,r,x,rs(p)); push_up(p);
}
int ask(int l,int r,int x,int y,int p)
{
	if(x>y) return 0;
	if(l>=x&&r<=y) return m(p); int mid=md(l,r);
	if(mid>=x&&mid<y) return getm(ask(l,mid,x,y,ls(p)),ask(mid+1,r,x,y,rs(p)));
	else if(mid>=x) return ask(l,mid,x,y,ls(p)); else return ask(mid+1,r,x,y,rs(p));
}

vector <int> usbh;
int calc(int x)
{
	if(e[x].size()==1) return 0;
	int cc=e[x].size(),na=0;
	for(auto i:e[x])
	{
		int num;
		if(i==fa[x])
		{
			num=getm(ask(1,n,1,dfn[x]-1,1),ask(1,n,dfn[x]+sz[x],n,1));
		}
		else
		{
			num=ask(1,n,dfn[i],dfn[i]+sz[i]-1,1);
		}
		na+=w[num]; w[num]++; usbh.pb(num); cz(1,n,dfn[num],1);
	}
	for(int i=1;i<=cc-2;i++)
	{
		int num=getm(ask(1,n,1,dfn[x]-1,1),ask(1,n,dfn[x]+1,n,1));
		na+=w[num]; w[num]++; usbh.pb(num); cz(1,n,dfn[num],1);
	}
	for(auto i:usbh) w[i]=lw[i],cz(1,n,dfn[i],1);
	usbh.clear();
	return na;
}

signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>w[i],lw[i]=w[i]; w[0]=1000000000;
	for(int i=1;i<=n-1;i++) cin>>u>>v,e[u].pb(v),e[v].pb(u);
	dfs0(1,1); build(1,n,1);
	for(int i=1;i<=n;i++) cout<<calc(i)<<" "; cout<<endl;
}
```

---

## 作者：Petit_Souris (赞：0)

先考虑树是一个菊花，我们删去中心点的情况。设剩余的权值为 $w_1,w_2\dots w_k$，这些点之间的度数序列为 $d_{1},d_2\dots d_{k}$。那么一个 $d$ 序列合法的条件为 $\sum d=2k-2,\forall i,1\le d_i\le k-1$。

对于这个下界，我们先把所有 $d_i$ 设为 $1$，并进行一次操作，这样剩下 $k-2$ 次操作每次选择最小值做一次操作就是最优的。

拓展到一般情况也是一样的：我们先对于每个分出来的连通块的最小值做一次最小值，然后再做 $k-2$ 次全局最小值的操作。每次操作都是子树查询 min 或者子树外查询 min，可以用线段树维护。对一个点求解的复杂度是 $\mathcal O(\deg\log n)$ 的，所以总复杂度为 $\mathcal O(n\log n)$。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=1e6+9,INF=1e15;
ll n,a[N],dfn[N],sz[N],tim,ord[N],fa[N];
vector<ll>to[N];
void dfs(ll x,ll f){
    fa[x]=f;
    dfn[x]=++tim,sz[x]=1,ord[tim]=x;
    for(ll y:to[x]){
        if(y==f)continue;
        dfs(y,x);
        sz[x]+=sz[y];
    }
}
pii tr[N<<2];
void Upd(ll x,ll l,ll r,ll u,ll v){
    if(l>u||r<u)return ;
    if(l==r){
        tr[x].first+=v;
        return ;
    }
    ll mid=(l+r)>>1;
    Upd(x<<1,l,mid,u,v);
    Upd(x<<1|1,mid+1,r,u,v);
    tr[x]=min(tr[x<<1],tr[x<<1|1]);
}
pii Query(ll x,ll l,ll r,ll ql,ll qr){
    if(ql>qr)return make_pair(INF,INF);
    if(ql<=l&&r<=qr)return tr[x];
    ll mid=(l+r)>>1;
    if(qr<=mid)return Query(x<<1,l,mid,ql,qr);
    if(ql>mid)return Query(x<<1|1,mid+1,r,ql,qr);
    return min(Query(x<<1,l,mid,ql,qr),Query(x<<1|1,mid+1,r,ql,qr));
}
void Build(ll x,ll l,ll r){
    if(l==r){
        tr[x]={a[ord[l]],l};
        return;
    }
    ll mid=(l+r)>>1;
    Build(x<<1,l,mid);
    Build(x<<1|1,mid+1,r);
    tr[x]=min(tr[x<<1],tr[x<<1|1]);
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    n=read();
    rep(i,1,n)a[i]=read();
    rep(i,2,n){
        ll x=read(),y=read();
        to[x].push_back(y);
        to[y].push_back(x);
    }
    dfs(1,0);
    Build(1,1,n);
    rep(i,1,n){
        ll ans=0,cnt=(ll)to[i].size();
        if(cnt==1){
            write(0),putchar(' ');
            continue;
        }
        cnt-=2;
        Upd(1,1,n,dfn[i],INF);
        vector<ll>opt;
        for(ll j:to[i]){
            if(j==fa[i]){
                pii mn=min(Query(1,1,n,1,dfn[i]-1),Query(1,1,n,dfn[i]+sz[i],n));
                ans+=mn.first;
                Upd(1,1,n,mn.second,1);
                opt.push_back(mn.second);
            }
            else {
                pii mn=Query(1,1,n,dfn[j],dfn[j]+sz[j]-1);
                ans+=mn.first;
                Upd(1,1,n,mn.second,1);
                opt.push_back(mn.second);
            }
        }
        while(cnt--){
            pii mn=tr[1];
            ans+=mn.first;
            Upd(1,1,n,mn.second,1);
            opt.push_back(mn.second);
        }
        write(ans),putchar(' ');
        Upd(1,1,n,dfn[i],-INF);
        for(ll x:opt)Upd(1,1,n,x,-1);
    }
    return 0;
}
```

---

