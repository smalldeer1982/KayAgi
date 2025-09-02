# A Museum Robbery

## 题目描述

初始有 $n$ 件展品（标号 $1$ 到 $n$），其中第 $i$ 件展品有大小为 $v_i$ 的**价值**，$w_i$ 的**质量**。

接下来会发生 $q$ 个事件，每个事件为以下三种类型之一：

- 添加一个价值为 $v$，质量为 $w$ 的展品。记上一次该操作添加展品的编号为 $t$（如果这是第一次，则默认为 $t = n$），则本次添加的展品的编号为 $t+1$；
- 删除编号为 $x$ 的展品；
- 进行一次询问，其中询问方式如下。

对于最开始给定的正整数 $k$，请你输出：
$$
\sum \limits_{m = 1}^k s(m) \times p^{m-1} \bmod q
$$
（其中 $p = 10^7 + 19, q = 10^9 + 7$）

$s(m)$ 的定义如下：

设当前展品编号集合为 $D$，$S$ 是 $D$ 的一个子集，且满足 $\sum \limits_{i \in S} w_i \leq m$，则 $s(m)$ 是 $\sum \limits_{i \in S} v_i$ 的最大值。

## 说明/提示

$1 \leq n \leq 5 \times 10^3$，$1 \leq q \leq 3 \times 10^4$，$1 \leq k, w_i, w \leq 10^3$，$1 \leq v_i, v \leq 10^6$。

## 样例 #1

### 输入

```
3 10
30 4
60 6
5 1
9
3
1 42 5
1 20 3
3
2 2
2 4
3
1 40 6
3
```

### 输出

```
556674384
168191145
947033915
181541912
```

## 样例 #2

### 输入

```
3 1000
100 42
100 47
400 15
4
2 2
2 1
2 3
3
```

### 输出

```
0
```

# 题解

## 作者：Doubeecat (赞：6)

> [CF601E A Museum Robbery](http://codeforces.com/problemset/problem/601/E)
>
> 最初给定 $n$ 个物品以及背包容量 $k$，有 $q$ 次操作，操作有三种：
>
> - `1 v w` 在背包里添加一个体积为 $v$ 价值为 $w$ 的物品
> - `2 x` 删除编号为 $x$ 的物品
> - `3` 查询背包总和，以 $\sum\limits_{m=1}^{k}{s(m)*p^{m-1}\ \bmod\ q}$ 的形式输出
>
> $n \leq 5000,k \leq 1000,q \leq 30000$ ，保证操作 $1$ 的个数不超过 $10000$，且至少有一个操作 $3$。

<!--more-->

## 解题思路：

首先我们考虑，在背包里加入一个物品是 $\mathcal{O}(n)$ 的，但是删除一个物品并不好处理，只想到了重做一遍背包的方法，但是这样是 $\mathcal{O}(n^2)$ 的，显然会寄。

接下来观察题目的前两个操作，发现如果我们把最开始的物品看作在时间点 $0$，那么实际上所有物品可以考虑成在一个时间段上出现，这个就很符合**线段树分治**的套路了。

确定了算法之后，就开始考虑怎么写。首先我们记操作 $3$ 的个数有 $cnt$ 个，首先线段树建在 $[1,cnt]$ 上，每个线段树节点上考虑开一个 `vector` 来保存这个节点代表的区间存在的物品。我们发现这里实际上不好合并，所以我们采用**标记永久化**的方法。

在分治过程中，我们每访问到一个节点考虑一个额外的 $g$ 数组作背包用，将 $f$ 拷贝到 $g$ 后对于 $g$ 进行新增物品的背包操作。而在分治之后直接下传 $g$ 数组，于是我们可以写出一个伪代码框架了：

```cpp
void solve(int p,ll *f) {
    ll g[N];
    for (int i = 0;i <= sto;++i) g[i] = f[i];
    for (auto now : tree[p].vec) {
        Add(g,now);//将物品 now 添加到 g 中。
    }
    if (tree[p].l == tree[p].r) {
        Output();
        return ;
    } else {
        //注意此处下传是 g 数组，已经添加过物品了。
        solve(p << 1,g);
        solve(p << 1 | 1,g);
    }
}
```

时间复杂度 $\mathcal{O}((n+q)\log (n+q) + q)$。注意数组如果开的较大不要使用 `memset`。

## 代码：

```cpp
const int N = 1e5 + 10;
const ll base = 1e7 + 19;
const ll mod = 1e9 + 7;

struct item {
    int x,y,v,w;
}E[N];

struct node {
    int l,r;
    vector <item> vec;
}tree[N<<2];

ll qwq[N];
int tot,n,q,sto;

void build(int p,int l,int r) {
    tree[p].l = l,tree[p].r = r;
    if (l == r) {
        return ;
    }
    int mid = (l + r) >> 1;
    build(p << 1,l,mid);
    build(p << 1 | 1,mid + 1,r);
}

void change(int p,int x,int y,int num) {
    if (tree[p].l >= x && tree[p].r <= y) {
        tree[p].vec.push_back(E[num]);
        return ;
    }
    int mid = (tree[p].l + tree[p].r) >> 1;
    if (x <= mid) change(p << 1,x,y,num);
    if (y > mid) change(p << 1 | 1,x,y,num);
}

void solve(int p,ll *f) {
    ll g[N];
    for (int i = 0;i <= sto;++i) g[i] = f[i];
    for (auto now : tree[p].vec) {
        for (int j = sto;j >= now.v;--j) {
            g[j] = max(g[j],g[j - now.v] + now.w); 
        }
    }
    if (tree[p].l == tree[p].r) {
        ll ans = 0;
        for (int i = sto;i >= 1;--i) ans = (ans * base + g[i]) % mod;
        printf("%lld\n",ans);
    } else {
        solve(p << 1,g);
        solve(p << 1 | 1,g);
    }
}


signed main() {
    read(n,sto);
    for (int i = 1;i <= n;++i) {
        int v,w;read(w,v);
        E[++tot] = {1,-1,v,w};
    }
    int tt = 1;
    read(q);
    for (int i = 1;i <= q;++i) {
        int opt;read(opt);
        if (opt == 1) {
            int v,w;read(w,v);
            E[++tot] = {tt,-1,v,w};
        }
        if (opt == 2) {
            int x;read(x);
            E[x].y = tt - 1;
        }
        if (opt == 3) {
            ++tt;
        }
    }
    --tt;
    build(1,1,tt);
    for (int i = 1;i <= tot;++i) {
        if (E[i].y == -1) E[i].y = tt;
        if (E[i].x <= E[i].y) {
            change(1,E[i].x,E[i].y,i);
        }
    }
    solve(1,qwq);
	return 0;
}
```

AD：![](https://cdn.luogu.com.cn/upload/image_hosting/cns1ec5k.png)

---

## 作者：漠寒 (赞：4)

## 分析

第一道线段树分治题祭。

线段树分治呢，处理的好像就是这些基于时间上的物品加入删除问题，我们将所有事件离线处理，每一个询问代表一个时刻，对于每一个物品，处理它所存在的时段，概括一下就是用线段树来处理每一个物品能对哪些询问起作用。

所以线段树每一个节点就代表了一个时段，而在询问中我们通常是找某一个时间点，所以类似于标记永久化的思想，在从上到下的过程中，如果能覆盖一个区间，那区间内的点也能同样造成影响，所以我们先将每一个物品加到它对应的区间，用 vector 存储完全覆盖某一区间的物品有哪些。

然后以此题为例，在从上到下的过程中将包含整个区间的物品从线段树中提出，再进行背包问题的处理，再将背包数组传给左右两区间，继续分治下去。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ls rt<<1
#define rs rt<<1|1
inline void read(int &res){
	res=0;
	int f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')res=(res<<1)+(res<<3)+c-48,c=getchar();
	res*=f;
}
const int base=1e7+19,mod=1e9+7;
int n,k,q,ti;
int csf[1005];
int l[15005],r[15005],v[15005],w[15005],cnt;
vector<int>V[120005];
void modify(int rt,int l,int r,int L,int R,int k){
	if(L>R)return;
	if(l>=L&&R>=r){
		V[rt].push_back(k);
		return;
	}
	int mid=(l+r)>>1;
	if(mid>=L)modify(ls,l,mid,L,R,k);
	if(mid<R)modify(rs,mid+1,r,L,R,k);
}
void solve(int rt,int l,int r,int f[]){
	for(int i=0;i<V[rt].size();i++){
		int x=V[rt][i];//提取物品 
		for(int j=k;j>=w[x];j--){//01背包 
			f[j]=max(f[j],f[j-w[x]]+v[x]);
		}
	}
	if(l==r){
		if(l==1)return;//起始点，因为ti初始为1线段树会方便一点，所以在这里多了一个特判 
		int b=1,sum=0;
		for(int i=1;i<=k;i++){
			sum=(sum+f[i]*b)%mod;
			b=b*base%mod;
		}
		printf("%lld\n",sum);
		return;
	}
	int mid=(l+r)>>1;
	int g[k+1];
	for(int i=0;i<=k;i++)g[i]=f[i];
	//这里下去会直接在子任务中修改f数组，所以不能直接将f传给右分治任务，所以新建g以存储 
	solve(ls,l,mid,f);
	solve(rs,mid+1,r,g);
}
signed main()
{
	read(n);read(k);
	cnt=n;
	ti=1;
	for(int i=1;i<=n;i++){
		read(v[i]);read(w[i]);
		l[i]=ti;//起始时间 
	}
	read(q);
	while(q--){
		int op,x,y,z;
		read(op);
		if(op==1){
			read(x);read(y);
			v[++cnt]=x;w[cnt]=y;
			l[cnt]=ti+1;//前面那个询问它管不到，所以+1 
		}
		else if(op==2){
			read(x);
			r[x]=ti;
		}
		else ti++;//多一询问，时间点++ 
	}
	for(int i=1;i<=cnt;i++){
		if(r[i])modify(1,1,ti,l[i],r[i],i);
		else modify(1,1,ti,l[i],ti,i);//寻找该物品所能完全覆盖的每一个最大区间，加入对应vector 
	}
	solve(1,1,ti,csf);//开始分治 
}

```


---

## 作者：daniEl_lElE (赞：1)

不难发现每种展品出现的时间是连续段。

考虑离线，相当于有若干个物品出现在若干段时间，求每个时间的背包答案。

考虑线段树分治，将一个物品拆成 $O(\log q)$ 段，在计算的时候分治，每个点暴力加入一个物品。复杂度是 $O(nk\log q+qk)$ 的。

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2,3,"Ofast","inline")
#define int long long
#define mid ((l+r)>>1)
using namespace std;
const int mod=1e9+7,base=1e7+19;
int n,k;
int v[15005],w[15005],l[15005],r[15005];
int tagq[30005];
vector<pair<int,int>> add[120005];
void anum(int i,int l,int r,int ql,int qr,pair<int,int> dat){
	if(ql<=l&&r<=qr){
		add[i].push_back(dat); return ;
	}
	if(ql<=mid) anum(i*2,l,mid,ql,qr,dat);
	if(qr>mid) anum(i*2+1,mid+1,r,ql,qr,dat);
}
int rl[50][1005];
void cal(int i,int l,int r,int dep){
	for(auto v:add[i]){
		for(int j=k;j>=v.second;j--){
			rl[dep][j]=max(rl[dep][j],rl[dep][j-v.second]+v.first);
		}
	}
	if(l==r){
		if(tagq[l]){
			int ans=0,now=1;
			for(int j=1;j<=k;j++) (ans+=rl[dep][j]*now)%=mod,(now*=base)%=mod;
			cout<<ans<<"\n";
		}
		return ;
	}
	for(int j=0;j<=k;j++) rl[dep+1][j]=rl[dep][j];
	cal(i*2,l,mid,dep+1);
	for(int j=0;j<=k;j++) rl[dep+1][j]=rl[dep][j];
	cal(i*2+1,mid+1,r,dep+1);
}
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>v[i]>>w[i];
		l[i]=1;
	}
	int q; cin>>q;
	for(int i=1;i<=n;i++) r[i]=q;
	for(int i=1;i<=q;i++){
		int opt; cin>>opt;
		if(opt==1){
			n++;
			l[n]=i,r[n]=q;
			cin>>v[n]>>w[n];
		}
		else if(opt==2){
			int pos; cin>>pos;
			r[pos]=i;
		}
		else{
			tagq[i]=1;
		}
	}
	for(int i=1;i<=n;i++) anum(1,1,q,l[i],r[i],make_pair(v[i],w[i]));
	cal(1,1,q,1);
	return 0;
}

```

---

## 作者：GavinZheng (赞：1)

考虑线段树分治。

线段树分治实际上就是将把时间按照线段树的方法分治下去。线段树的每个节点都是一个时间区间，预处理的时候如果一个操作的“存活时间”完全覆盖这个时间区间，就给这个时间区间打上标记并返回。然后在线段树上DFS，每次向下走到一个节点将这个节点的操作加入，离开时删除即可。

线段树分治大多数情况就是用来解决：加入某个元素之后删除这个元素很麻烦，但是按照插入的顺序从后到前“撤销”很方便。（类似栈的结构：只能弹出顶部，不能删除中间的。）

而这道题 是满足这个条件的。每次递归之前只需要把递归之前的状态复制一个“备份”。然后暴力的把“备份”还原即可。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
#include<queue>
#define vi vector<int>
#define pb push_back
#define mk make_pair
#define pii pair<int,int>
#define rep(i,a,b) for(int i=(a),i##end=(b);i<=i##end;i++)
#define fi first
#define se second
typedef long long ll;
using namespace std;
const int maxn=41000;
const int p=1e7+19;
const int q=1e9+7;
int ed[maxn],st[maxn];
pii item[maxn];
bool query[maxn];
int pro[maxn];
int k;
vi add[maxn*4];
void update(int l,int r,int rt,int tl,int tr,int node){
    if(tl<=l&&r<=tr){
        add[rt].pb(node);return;
    }
    int mid=(l+r)>>1;
    if(tl<=mid)update(l,mid,rt<<1,tl,tr,node);
    if(tr>=mid+1)update(mid+1,r,rt<<1|1,tl,tr,node);
}
ll ksm(ll num,ll t){
    ll res=1;num%=q;
    for(;t;t>>=1,num=num*num%q){
        if(t&1)res=res*num%q;
    }
    return res;
}
int tmp[1005];
void solve(int l,int r,int rt){
    int buc[1005]={0};
    rep(i,0,(int)add[rt].size()-1){
        int id=add[rt][i];
        for(int j=k;j>=0;j--){
            if(j+item[id].se<=k)tmp[j+item[id].se]=max(tmp[j+item[id].se],tmp[j]+item[id].fi);
        }
    }
    if(l==r){
        if(query[l]){
            ll ans=0;
            rep(m,1,k){
                ans+=1ll*tmp[m]*pro[m-1]%q;ans%=q;
            }
            printf("%lld\n",ans);
        }
        return;
    }
    int mid=(l+r)>>1;
    memcpy(buc,tmp,sizeof(tmp));
    solve(l,mid,rt<<1);
    memcpy(tmp,buc,sizeof(tmp));
    solve(mid+1,r,rt<<1|1);
}
int main(){
    rep(i,0,1005)pro[i]=ksm(p,i);
    int n;scanf("%d%d",&n,&k);
    rep(i,1,n)
    {scanf("%d%d",&item[i].fi,&item[i].se);st[i]=1;}
    int q;scanf("%d",&q);int item_cnt=n;
    rep(i,1,q){
        int ty;scanf("%d",&ty);
        if(ty==1){
            ++item_cnt;scanf("%d%d",&item[item_cnt].fi,&item[item_cnt].se);st[item_cnt]=i;
        }
        else if(ty==2){
            int x;scanf("%d",&x);ed[x]=i;
        }
        else query[i]=1;
    }
    rep(i,1,item_cnt)if(!ed[i])ed[i]=q;
    rep(i,1,item_cnt)
    update(1,q,1,st[i],ed[i],i);
    solve(1,q,1);
    return 0;
}
```



---

## 作者：pldzy (赞：0)

Happy New Year!

## Solution

删除任意编号的存在物品，不强制在线，先扔一个线段树分治上去。

发现是背包，~~想到猫树~~。背包是典型的合并复杂度非常高的信息。发现我们能承受的复杂度是加入一个物品的 $O(k)$，而非合并两个背包的 $O(k^2)$。

另一个有趣的性质是背包信息支持撤销。

那比起在每个节点维护物品构成的背包，我们选择类似 `dfs()` 的过程，每次加入物品然后继续递归，回溯的时候撤销即可。算是利用上“保证物品总数不超过 $1e4$”的条件了。

时间复杂度 $O(nk\log q)$。

## Code

````cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

#define rep(i, a, b) for(int i = (a); i <= (b); ++i)
#define per(i, a, b) for(int i = (a); i >= (b); --i)
#define pii pair<int, int>
#define fi first
#define se second
#define mkp make_pair

const int maxn = 3e4 + 5, maxm = 1e3 + 5;

int n, k, q, op[maxn];
int L[maxn], R[maxn]; pii a[maxn];

vector<pii> t[maxn << 2];

#define ls (x << 1)
#define rs (x << 1 | 1)

inline void updtr(int x, int l, int r, int L, int R, pii v){
	if(l >= L and r <= R) return t[x].push_back(v), void();
	int mid = l + r >> 1;
	if(L <= mid) updtr(ls, l, mid, L, R, v);
	if(R > mid) updtr(rs, mid + 1, r, L, R, v);
}

const ll p = 1e7 + 19, mod = 1e9 + 7;

ll st[maxn][maxm], ans[maxn]; int tp;

inline void qry(int x, int l, int r){
	int tp0 = tp;
	for(auto nw : t[x]){
		++tp; 
		rep(i, 1, k) 
			st[tp][i] = max(st[tp - 1][i], i >= nw.se ? st[tp - 1][i - nw.se] + nw.fi : 0ll);
	}
	int mid = l + r >> 1;
	if(l == r){
		if(op[l] == 3){
			ll fac = 1ll; 
			rep(m, 1, k) 
				(ans[l] += st[tp][m] * fac % mod) %= mod, (fac *= p) %= mod;
		}
		goto bre;
	}
	qry(ls, l, mid); qry(rs, mid + 1, r);
	bre:;
	while(tp != tp0) --tp;
}

signed main(){
	ios_base::sync_with_stdio(0); cin.tie(NULL);
	
	cin >> n >> k;
	rep(i, 1, n) cin >> a[i].fi >> a[i].se;
	cin >> q;
	rep(i, 1, n) L[i] = 1, R[i] = q;
	rep(i, 1, q){
		cin >> op[i];
		if(op[i] == 1){
			++n; cin >> a[n].fi >> a[n].se;
			L[n] = i, R[n] = q;
		}
		if(op[i] == 2){
			int x; cin >> x; R[x] = i;
		}
	}
	rep(i, 1, n) updtr(1, 1, q, L[i], R[i], a[i]);
	qry(1, 1, q);
	rep(i, 1, q) if(op[i] == 3) cout << ans[i] << '\n';
	return 0;
}
````

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

我们注意到，每一个展品总是存在一定的时间，然后消失不见。这很符合线段树分治的套路。考虑一下。

动规转移方程很好想，$dp_i=\max(dp_{i-w_j}+v_j)$。然后，我们只需要预处理一下 $p^{m-1}$ 的那些幂，到下一层时记录 $dp$ 数组的值，然后更改，去下一层询问。返回时再把原 $dp$ 值拷回来。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define inn long long
constexpr inn p = 1e7 + 19, md = 1e9 + 7;
struct exh { int v, w; }v[40005]; int vid, tp[40005];
int n, m, k, o, x, cl; queue<int>q; set<int>s;
inn dp[1005], ans, tv[1005];
inline void adde(const exh& v) {
	for (int i = m;i >= v.w;--i)
		dp[i] = max(dp[i], dp[i - v.w] + v.v);
}
struct seg_tree {
	struct node {
		int l, r; vector<exh>ade;
	}re[40005 << 2];
	inline void build(int l, int r, int p) {
		re[p].l = l; re[p].r = r;
		if (l == r) return; build(l, (l + r >> 1), p << 1);
		build((l + r >> 1) + 1, r, p << 1 | 1);
	}
	inline void ins(int l, int r, int c, int p) {
		if (re[p].l >= l && re[p].r <= r)
			return void(re[p].ade.emplace_back(v[c]));
		if (l <= re[p << 1].r) ins(l, r, c, p << 1);
		if (r > re[p << 1].r) ins(l, r, c, p << 1 | 1);
	}
	inline void sol(int p) {
		if (!q.size() || re[p].r < q.front()) return;
		inn tmp[1005]; memcpy(tmp, dp, sizeof tmp);
		for (const exh& av : re[p].ade) adde(av);
		if (re[p].l == re[p].r) {
			q.pop(); ans = 0;
			for (int i = 1;i <= m;++i)
				ans = (ans + dp[i] * tv[i - 1]) % md;
			cout << ans << endl;
		}
		else sol(p << 1), sol(p << 1 | 1);
		memcpy(dp, tmp, sizeof dp);
	}
}sgt;
signed main() {
	ios::sync_with_stdio(0);
	cin >> n >> m; vid = n; tv[0] = 1;
	for (int i = 1;i <= m;++i) tv[i] = tv[i - 1] * p % md;
	for (int i = 1;i <= n;++i)
		cin >> v[i].v >> v[i].w, s.emplace(i);
	cin >> k; sgt.build(0, k + 1, 1);
	while (k--)
		if (cin >> o, o == 3) q.emplace(++cl);
		else if (o & 2) cin >> x, sgt.ins(tp[x], ++cl, x, 1), s.erase(x);
		else ++vid, tp[vid] = ++cl, cin >> v[vid].v >> v[vid].w, s.emplace(vid);
	for (int nv : s) sgt.ins(tp[nv], cl + 1, nv, 1); sgt.sol(1);
}
//私は猫です
```

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF601E)

# 前置知识

[线段树与离线询问](https://oi-wiki.org/topic/segment-tree-offline/)

# 解法

普通的回退背包无法处理本题中的删除操作，考虑线段树分治后转化为只进行添加的背包。

具体实现时可以对每个深度开一个背包的转移数组，时间复杂度为 $O(nk \log q+qk)$，可以接受。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
const ll mod=1000000007,base=10000019;
ll st[15010],ed[15010],v[30010],w[30010],f[18][1010],jc[1010],ans[30010],k;
struct SMT
{
	struct SegmentTree
	{
		vector<ll>info;
	}tree[120010];
	#define lson(rt) (rt<<1)
	#define rson(rt) (rt<<1|1)
	void update(ll rt,ll l,ll r,ll x,ll y,ll id)
	{
		if(x<=l&&r<=y)
		{
			tree[rt].info.push_back(id);
			return;
		}
		ll mid=(l+r)/2;
		if(x<=mid)
		{	
			update(lson(rt),l,mid,x,y,id);
		}
		if(y>mid)
		{
			update(rson(rt),mid+1,r,x,y,id);
		}
	}
	void solve(ll rt,ll l,ll r,ll dep)
	{
		for(ll i=1;i<=k;i++)
		{
			f[dep][i]=f[dep-1][i];
		}
		for(ll i=0;i<tree[rt].info.size();i++)
		{
			for(ll j=k;j>=w[tree[rt].info[i]];j--)
			{
				f[dep][j]=max(f[dep][j],f[dep][j-w[tree[rt].info[i]]]+v[tree[rt].info[i]]);
			}
		}
		if(l==r)
		{
			for(ll i=1;i<=k;i++)
			{
				ans[l]=(ans[l]+f[dep][i]*jc[i-1]%mod)%mod;
			}
		}
		else
		{
			ll mid=(l+r)/2;
			solve(lson(rt),l,mid,dep+1);
			solve(rson(rt),mid+1,r,dep+1);
		}
	}
}T;
int main()
{
// #define Isaac
#ifdef Isaac
	freopen("in.in","r",stdin);
	freopen("out.out","w",stdout);
#endif
	ll n,m,pd,x,tim=0,i;
	cin>>n>>k;
	for(i=1;i<=n;i++)
	{
		cin>>v[i]>>w[i];
		st[i]=1;
		ed[i]=-1;
	}
	cin>>m;
	for(i=1;i<=m;i++)
	{
		cin>>pd;
		if(pd==1)
		{
			n++;
			cin>>v[n]>>w[n];
			st[n]=tim+1;
			ed[n]=-1;
		}
		if(pd==2)
		{
			cin>>x;
			ed[x]=tim;
		}
		if(pd==3)
		{
			tim++;
		}
	}
	for(i=1;i<=n;i++)
	{
		ed[i]=(ed[i]==-1)?tim:ed[i];
		if(st[i]<=ed[i])
		{
			T.update(1,1,tim,st[i],ed[i],i);
		}
	}
	for(i=0;i<=k-1;i++)
	{
		jc[i]=(i==0)?1:jc[i-1]*base%mod;
	}
	T.solve(1,1,tim,1);
	for(i=1;i<=tim;i++)
	{
		cout<<ans[i]<<endl;
	}
	return 0;
}
```

---

## 作者：MornStar (赞：0)

## CF601E A Museum Robbery题解
[宣传自己写的线段树分治博客。](https://www.luogu.com.cn/article/8wdkvd1x)

一件展品出现有时间限制，是很明显的线段树分治。

看 $s(m)$ 的计算方式，大概就是线段树分治套背包了。

令 $dp_i$ 为总重量为 $i$ 时的最大价值，问题就转化为一个经典的 01 背包问题。统计答案时做一个前缀和就可以了。

背包撤销时可以用退背包，也可以 $O(n)$ 记录修改之前的背包状态。我这里用的是后者。

### code
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N=1.5e4+5,M=3e4+5,W=1e3+5,p=1e7+19,mod=1e9+7;
int n,m,k,cnt,la[N];
long long power[W];
bool q[M];
struct exhabit{int c,w;}a[N];
struct segment_tree{
	int dp[W];
	struct segment_tree_node{vector<exhabit>v;}t[M<<2];
	inline int ls(int x){return x<<1;};
	inline int rs(int x){return x<<1|1;};
#define mid ((l+r)>>1)
	void change(int p,int l,int r,int re_l,int re_r,exhabit val){
		if(re_l<=l&&r<=re_r)	return t[p].v.push_back(val),void();
		else{
			if(re_l<=mid)	change(ls(p),l,mid,re_l,re_r,val);
			if(mid<re_r)	change(rs(p),mid+1,r,re_l,re_r,val);
		}
	}
	void query(int p,int l,int r){
		vector<int> pre(k+1,0);
		for(int i=1;i<=k;i++)	pre[i]=dp[i];
		for(auto it:t[p].v){
			for(int i=k;i>=it.w;i--)	dp[i]=max(dp[i],dp[i-it.w]+it.c);
		}
		if(l==r){
			if(q[l]){
				long long ma=-1,ans=0;
				for(int i=1;i<=k;i++){
					ma=max(ma,1ll*dp[i]);
					ans=(ans+ma*power[i-1]%mod)%mod;
				}
				cout<<ans<<"\n";
			}
		}else	query(ls(p),l,mid),query(rs(p),mid+1,r);
		for(int i=1;i<=k;i++)	dp[i]=pre[i];
	}
}T;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>k;cnt=n;
	power[0]=1;
	for(int i=1;i<=k;i++)	power[i]=power[i-1]*p%mod;
	for(int i=1;i<=n;i++)	cin>>a[i].c>>a[i].w,la[i]=1;
	cin>>m;
	for(int i=1,opt,num;i<=m;i++){
		cin>>opt;
		if(opt==1){
			cnt++;
			cin>>a[cnt].c>>a[cnt].w;
			la[cnt]=i;
		}else if(opt==2){
			cin>>num;
			T.change(1,1,m,la[num],i,a[num]);
			la[num]=0;
		}else	q[i]=1;
	}
	for(int i=1;i<=cnt;i++){
		if(la[i])	T.change(1,1,m,la[i],m,a[i]);
	}
	T.query(1,1,m);
}
```
时间复杂度 $O((n+m)k\log{m}+km)$。

---

## 作者：LJ07 (赞：0)

电信诈骗题。

考虑每次操作暴力怎么做，考虑暴力背包，以混乱度为重量，价值为价值。

如果你不仔细看英文题面，你会发现背包容量 $\le 10^6$。结果你发现有一个 $k\le 1000$，这是题目查询的背包最大容量。。。所以背包容量最大只有 $1000$。

又加入又撤销，并且加入一个物品复杂度仅为 $O(k)$，线段树分治离线处理。

复杂度 $O((n+q)k\log n)$。

~~自己都被自己代码丑到了（吐~~


```cpp
#include <bits/stdc++.h>
#define ve vector
#define eb emplace_back
#define LL long long
using namespace std;
const int P(1e7+19),Q(1e9+7);
int n,k,q;
#define pii pair<int,int>
#define fi first
#define se second
struct SGT
{
	#define Ts int rt=1,int L=0,int R=q
	#define mid (L+R>>1)
	#define Ls rt<<1,L,mid
	#define Rs rt<<1|1,mid+1,R
	ve<ve<int>> tr;
	void push(int l,int r,int id,Ts)
	{
		if (l<=L&&R<=r) return tr[rt].eb(id),void();
		if (l<=mid) push(l,r,id,Ls);
		if (r>mid) push(l,r,id,Rs);
	}
	void solve(ve<LL>dp,ve<pii>&ths,ve<int>&pw,ve<bool>&ask,Ts)
	{
		for (int i:tr[rt]) 
			for (int j(k);j>=ths[i].se;--j) 
				dp[j]=max(dp[j],dp[j-ths[i].se]+ths[i].fi);
		if (L==R)
		{
			if (ask[L])
			{
				int ans(0);
				for (int i(1);i<=k;++i) (ans+=1ll*dp[i]*pw[i-1]%Q)%=Q;
				cout<<ans<<'\n';
			}
			return ;
		}
		solve(dp,ths,pw,ask,Ls),solve(dp,ths,pw,ask,Rs);
	}
	#undef Ts
	#undef mid
	#undef Ls
	#undef Rs
	SGT(int q):tr(q+5<<2) {}
};
int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>k;
	ve<pii> ths(n);
	ve<int> ti(n),pw(k);
	pw[0]=1;
	for (int i(1);i<k;++i) pw[i]=1ll*pw[i-1]*P%Q;
	for (pii &i:ths) cin>>i.fi>>i.se;
	cin>>q;
	SGT sgt(q);
	ve<bool> ask(q+1);
	for (int i(1),op,x,y;i<=q;++i)
	{
		cin>>op;
		if (op==1) 
		{
			cin>>x>>y,ths.eb(x,y),ti.eb(i);
		}else if (op==2)
		{
			cin>>x,--x,sgt.push(ti[x],i-1,x),ti[x]=-1;
		}else ask[i]=1;
	}
	for (int i(0),l(ths.size());i<l;++i)
		if (~ti[i]) sgt.push(ti[i],q,i);
	sgt.solve(ve<LL>(k+1),ths,pw,ask);
	return 0;
}
```

---

## 作者：寒鸽儿 (赞：0)

**题意**

维护一个物品的集合，物品有重量和价值，刚开始有 $n$ 个物品，有 $q$ 个询问：

1. 插入一个新物品
2. 删除一个物品
3. 询问 $\sum_{1 \le x \le k} s(x) a^{x - 1} \bmod b$，其中 $s(x)$ 为重量不超过 $x$ 的物品的最大价值，$a = 10^7 + 19, b = 10^9 + 7$，$k$ 由询问给出。

$n \le 5 \times 10^3, 1 \le k \le 10^3, 1 \le v \le 10^6, q \le 3 \times 10^4$，至多插入 $C = 10^4$ 件物品。

**题解**

实际上就是动态维护集合的背包，支持插入和删除。

背包的插入和复制是 $\mathcal{O}(k)$ 的，合并是 $\mathcal{O}(k^2)$ 的，物品在时间区间上有贡献，所以用线段树分治来避免合并，将某时刻的贡献和转化为分治结构路径上元素的贡献和。  

每个贡献被切分成 $\log$ 个结点，采用类似标记永久化的思想把贡献元素都存在线段树的结点上。每个结点的所有元素进行了一次插入，所有左侧结点的背包还进行了一次复制。元素共进行了 $\log$ 次插入（在每个结点）。总的复制次数不多于总的插入次数。

复杂度为 $\mathcal{O}((n + C)k \log (n + C) + q)$。

```cpp
int pp[maxk];
struct obj { int v, w; };
struct segTDiv {
    vector< vector<obj> > v;
    vector<int> ans;
    int k, mt;
    void init(int mxtim, int kk) {
        v.resize(mxtim << 2 | 1);
        ans.resize(mxtim << 2 | 1);
        k = kk, mt = mxtim;
    }
    void insert(int p, int lp, int rp, int l, int r, obj &ob) {
        if(l <= lp && rp <= r) { 
            v[p].push_back(ob);
            return ; 
        }
        register int mid = (lp + rp) >> 1;
        if(l <= mid) insert(p << 1, lp, mid, l, r, ob);
        if(r > mid) insert(p << 1 | 1, mid + 1, rp, l, r, ob);
    }
    void qry() {
        vector<int> f(k + 1);
        dfs(1, 1, mt, f);
    }
    void dfs(int p, int lp, int rp, vector<int> &f) {
        for(auto ob : v[p])	
            for(int i = k; i - ob.w >= 0; -- i)
                f[i] = max(f[i], f[i - ob.w] + ob.v);
        if(lp == rp) {
            int tmp = 0, tf = 0;
            rep(i,1,k) { tf = max(tf, f[i]); tmp = (tmp + 1ll * tf * pp[i - 1] % q) % q;  }
            ans[lp] = tmp;
            return ;
        }
        register int mid = (lp + rp) >> 1;
        vector<int> g = f;
        dfs(p << 1, lp, mid, g);
        dfs(p << 1 | 1, mid + 1, rp, f);
    }
} tree;

obj ob[maxn + maxq], tms[maxn + maxq];
int main() {
    // ... 省略输入和预处理，结果是物品信息放入 ob ，作用时间放入 tms，询问时间点放入 qtm，timer存储最大时间。
    tree.init(timer, k);
    rep(i,1,pob)
        tree.insert(1, 1, timer, tms[i].v, tms[i].w == 0 ? timer : tms[i].w, ob[i]);	tree.qry();
    for(int tm : qtm) printf("%d\n", tree.ans[tm]);
    return 0;
}
```



---

## 作者：金春来 (赞：0)

题意：动态加/删除物品、动态进行背包DP

考虑离线做法，线段树分治（类似于CDQ分治）

对 **物品存在的时间** 建线段树， **加/删除物品** 的操作会使该物品存在于一段时间（区间），也就是说一个物品最多会被存进组成时间区间的**每个节点的vector上记录了该物品**

建好树之后递归每一个叶节点，每到当前节点就用**vector里存的物品**更新背包的DP数组，并把这个DP数组传给它的儿子

每个叶节点的方案就是对于当前询问的背包的结果

```cpp
#include<cstdio>
#include<cctype>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

const int maxn = 4e4 + 7;
const int maxk = 1e3 + 7;
const int base = 1e7 + 19;
const int MOD = 1e9 + 7;
typedef pair<int, int> pii;
typedef vector<pii>::iterator vit;

struct exhibits {
	int v, w, l, r;
} exb[maxn];
int k;
vector<pii> seg[maxn<<2];
long long DP[maxk];

int qr();

void add (int p, int l, int r, int ql, int qr, int v, int w)  // 离线处理加/删除物品操作
{
	if(ql <= l && r <= qr)
	{
		seg[p].push_back(make_pair(v, w));
		return ;
	}
	int mid = (l+r)>>1;
	if(ql <= mid) add(p<<1, l, mid, ql, qr, v, w);
	if(mid < qr) add(p<<1|1, mid+1, r, ql, qr, v, w);
}

void solve (int p, int l, int r, long long * dp)  // 线段树分治+DP
{
	for(vit pp = seg[p].begin(); pp != seg[p].end(); pp++)
		for(int j = k; j >= pp->second; j--) dp[j] = max(dp[j], dp[j-pp->second]+pp->first);
	if(l == r)
	{
		long long ans = 0;
		for(int i = k; i; i--) ans = (ans * base + dp[i]) % MOD;
		printf("%lld\n",ans);
		return ;
	}
	int mid = (l+r)>>1;
	long long f[maxk];
	memcpy(f, dp, sizeof(f));
	solve(p<<1, l, mid, f);
	memcpy(f, dp, sizeof(f));
	solve(p<<1|1, mid+1, r, f);
}

int main ()
{
	int n, q, opt, u, v, t = 1;
	n = qr(); k = qr();
	for(int i = 1; i <= n; i++)  // 原物品存在的时间是[1, m],其中m代表询问的数量（暂时未知，计作-1）
	{
		u = qr(); v = qr();
		exb[i] = (exhibits){u, v, t, -1};
	}
	scanf("%d",&q);
	while(q--)
	{
		opt = qr();
		if(opt == 1) {  u = qr(); v = qr(); exb[++n] = (exhibits){u, v, t, -1};  }  // 添加物品，物品消失时间未知
		else if(opt == 2) exb[qr()].r = t-1;  // 删除物品，物品不复存在
		else t++;  // 询问操作
	}
	t--;
	for(int i = 1; i <= n; i++)
	{
		exb[i].r = exb[i].r == -1 ? t : exb[i].r;
		if(exb[i].l <= exb[i].r) add(1, 1, t, exb[i].l, exb[i].r, exb[i].v, exb[i].w);
	}
	solve(1, 1, t, DP);
	return 0;
}

inline int qr ()
{
	int num = 0;
	char ch = getchar();
	while(!isdigit(ch)) ch = getchar();
	while(isdigit(ch)) num = (num<<1) + (num<<3) + ch - 48, ch = getchar();
	return num;
}
```


还有一道类似的题目[P5416 \[CTSC2016\]时空旅行](https://www.luogu.org/problem/P5416)，也是线段树分治

---

