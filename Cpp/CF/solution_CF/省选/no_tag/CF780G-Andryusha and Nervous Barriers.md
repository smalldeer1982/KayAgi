# Andryusha and Nervous Barriers

## 题目描述

你在玩一个游戏：游戏的界面是一个网格，高度为$h$，宽度为$w$，玩家可以从网格正上方（高度为$h+1$）的位置释放小球。

网格中有$n$个水平隔板，第$i$个隔板高度为$u_i$，挡住了$[l_i,r_i]$这段区间。没有两个隔板位于同一高度。当球落到隔板上的时候，球会分裂成两个球，分别从隔板的左右（$l_i=1$和$r_i+1$）掉落。特别地，如果隔板与网格的左右边缘挨着，则生成的两个球都会在不与网格边缘挨着的位置掉落。

但是，球不一定会落到隔板上。当球的速度过快时，它可能会直接穿过隔板。具体地，对于隔板$i$，如果球在到达隔板前所掉落的高度严格大于$s_i$（即，从严格大于$u_i+s_i$的高度开始掉落），它就会直接穿过隔板，同样也不会分裂。你在每个坐标为$(h+1,i)$的位置都释放了一个球，你想要知道，最后一共有多少个球掉落到最底部了。

## 样例 #1

### 输入

```
10 5 1
3 2 3 10
```

### 输出

```
7
```

## 样例 #2

### 输入

```
10 5 2
3 1 3 10
5 3 5 10
```

### 输出

```
16
```

## 样例 #3

### 输入

```
10 5 2
3 1 3 7
5 3 5 10
```

### 输出

```
14
```

## 样例 #4

### 输入

```
10 15 4
7 3 9 5
6 4 10 1
1 1 4 10
4 11 11 20
```

### 输出

```
53
```

# 题解

## 作者：xfrvq (赞：6)

[$\tt Link$](/problem/CF780G)。

有些球在某次掉落后会处于相同高度，相同位置，我们将它们组合为一个「节点」。

假设扫描线到隔板 $l,r,u,s$，我们询问 $[l,r]$ 里高度 $\le\min\{h+1,u+s\}$ 的「节点」的点总数并将这些「节点」删除，记点的总数为 $v$，然后将 $u$ 为高，$v$ 为点数组成的节点加入 $[l,r]$ 两端。

辅助上述操作的数据结构是线段树。线段树的底层维护按高度排序的所有节点。（你可以用 `set`，`priority_queue`）。插入就暴力插，$\mathcal O(\log w)$。询问，因为已经按高度排好序，所以容易按照高度删除。

但是你询问不能暴力遍历然后删除啊，这样复杂度是错的。考虑线段树维护子树深度最小值 $v$，如果 $v\gt$ 询问的高度，那么这个子树就没用了。

复杂度分析见下。

```cpp
const int N = 1e5 + 5;
const int S = N << 2;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

int h,w,n,L[N],R[N],T[S];

struct barrier{ int u,l,r,s; } B[N];
using node = pair<int,int>;

priority_queue<node> Q[N];

#define lc (i << 1)
#define rc (i << 1 | 1)
#define mid ((L + R) >> 1)
#define ls lc,L,mid
#define rs rc,mid + 1,R
#define id int i = 1,int L = 1,int R = w
#define psu T[i] = min(T[lc],T[rc])

void build(id){
	if(L == R) return Q[L].emplace(-(T[i] = h + 1),-1);
	build(ls); build(rs); psu;
}

void upd(int p,int h,int v,id){
	if(L == R){
		Q[L].emplace(-h,-v);
		return void(T[i] = -Q[L].top().first);
	}
	p <= mid ? upd(p,h,v,ls) : upd(p,h,v,rs); psu;
}

int qry(int l,int r,int x,id){
	if(T[i] > x) return 0;
	int sum = 0;
	if(L == R){
		while(Q[L].size() && -Q[L].top().first <= x)
			(sum += -Q[L].top().second) %= mod,Q[L].pop();
		T[i] = Q[L].size() ? -Q[L].top().first : inf;
		return sum;
	}
	if(l <= mid) sum += qry(l,r,x,ls);
	if(r > mid) (sum += qry(l,r,x,rs)) %= mod;
	psu; return sum;
}

int main(){
	read(h,w,n);
	rep(i,1,n) read(B[i].u,B[i].l,B[i].r,B[i].s);
	sort(B + 1,B + n + 1,[](auto a,auto b){return a.u > b.u;});
	build();
	rep(i,1,n){
		int x = qry(B[i].l,B[i].r,min(h + 1,B[i].s + B[i].u));
		if(B[i].l != 1) upd(B[i].l - 1,B[i].u,x * ((B[i].r == w) + 1) % mod);
		if(B[i].r != w) upd(B[i].r + 1,B[i].u,x * ((B[i].l == 1) + 1) % mod);
	}
	print(qry(1,w,inf));
	return 0;
}
```

+ 我们认为 $n,w$ 同阶。
+ 初始球的数量是 $\mathcal O(w)$，而让球数量发生变化的 `upd` 函数只会进行 $\mathcal O(n)$ 次，所以球的总数是 $\mathcal O(n)$ 的。
+ 对于落到一块隔板的球，它们会合并为一个
+ 对于没落到一块隔板的球，它们不会被再用到（因为隔板按高度降序）
+ 所以复杂度正确

---

## 作者：rzh123 (赞：3)

在挡板之间建图，拓扑排序。  

从下往上扫，用一个数据结构维护这一行每个点往下落会落到哪个板，每扫到一行就删除不能到这一行的板，把当前行的板向覆盖 $l-1,r+1$ 的最靠上的板连边，再加入当前行的板。  

支持插入线段、删除线段、查询覆盖某个点的线段编号 $\min$，用线段树套 `multiset`。  

拓扑排序，$f_u$ 表示经过 $u$ 的球数，$f_v=\sum\limits_{(u,v)\in E} f_u$。  

$O(n\log n\log w)$

```cpp
#include <bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
constexpr int N=4e5+25,P=1e9+7;
int h,w,n,vx,vs[N],ec,eh[N],deg[N];
struct{int nxt,to,dis;}e[N<<1];
bool flg2{true};
struct Ba{
    int u,l,r,s;
    bool operator<(const Ba &b)const{
        return u>b.u;
    }
}a[N];
struct Seg{
    struct{
        int l,r;
        multiset<int> s;
    }tr[N];
    inline int gget(int k){
        if(tr[k].s.empty()) return n+2;
        return *tr[k].s.begin(); 
    }
    void build(int k,int l,int r){
        tr[k].l=l,tr[k].r=r,tr[k].s.clear();
        if(l==r) return;
        int md((l+r)>>1);
        build(k<<1,l,md),build(k<<1|1,md+1,r);
    }
    int query(int k,int x){
        if(tr[k].l==tr[k].r) return gget(k);
        int md((tr[k].l+tr[k].r)>>1),s=gget(k);
        if(x<=md) return min(s,query(k<<1,x));
        else return min(s,query(k<<1|1,x));
    }
    void modify(int k,int l,int r,int v,int d){
        if(tr[k].l>=l&&tr[k].r<=r){
            if(d>0) tr[k].s.emplace(v);
            else tr[k].s.erase(tr[k].s.find(v));
            return;
        }
        int md((tr[k].l+tr[k].r)>>1);
        if(l<=md) modify(k<<1,l,r,v,d);
        if(r>md) modify(k<<1|1,l,r,v,d);
    }
}seg;
void disc(){
    for(int i{1};i<=n;++i){
        vs[++vx]=a[i].l,vs[++vx]=a[i].r;
        if(a[i].l>1) vs[++vx]=a[i].l-1;
        if(a[i].r<w) vs[++vx]=a[i].r+1;
    }
    vs[++vx]=1;
    sort(vs+1,vs+vx+1);
    vx=unique(vs+1,vs+vx+1)-vs-1;
    for(int i{1};i<=n;++i){
        a[i].l=lower_bound(vs+1,vs+vx+1,a[i].l)-vs;
        a[i].r=lower_bound(vs+1,vs+vx+1,a[i].r)-vs;
    }
    vs[vx+1]=w+1;
}
priority_queue<pii,vector<pii>,greater<pii> > q;
void adde(int u,int v,int w){
    e[++ec]={eh[u],v,w},eh[u]=ec;
    ++deg[v];
}
int topo(){
    static int f[N];
    vector<int> q;
    for(int i{1};i<=n;++i){
        if(!deg[i]){
            f[i]=0;
            q.emplace_back(i);
        }
    }
    f[n+1]=1,q.emplace_back(n+1);
    for(unsigned i{0u};i<q.size();++i){
        int u{q[i]};
        for(int j{eh[u]};j;j=e[j].nxt){
            int v{e[j].to},w{e[j].dis};
            f[v]=(f[v]+1ll*w*f[u])%P;
            if(!(--deg[v])) q.emplace_back(v);
        }
    }
    return f[n+2];
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>h>>w>>n;
    for(int i{1};i<=n;++i){
        int u,l,r,s; cin>>u>>l>>r>>s;
        a[i]={u,l,r,s};
    }
    if(!n){cout<<w<<'\n';return 0;}
    sort(a+1,a+n+1);
    disc();
    seg.build(1,1,vx);
    for(int i{n};i>=1;--i){
        while(!q.empty()&&q.top().first<a[i].u){
            auto t=q.top().second;
            q.pop();
            seg.modify(1,a[t].l,a[t].r,t,-1);
        }
        int vl{0},vr{0};
        if(vs[a[i].l]!=1) vl=seg.query(1,a[i].l-1);
        if(vs[a[i].r]!=w) vr=seg.query(1,a[i].r+1);
        if(vs[a[i].l]==1) adde(i,vr,2);
        else if(vs[a[i].r]==w) adde(i,vl,2);
        else adde(i,vl,1),adde(i,vr,1);
        seg.modify(1,a[i].l,a[i].r,i,+1);
        q.emplace(a[i].u+a[i].s,i);
    }
    while(!q.empty()&&q.top().first<h+1){
        auto t=q.top().second; q.pop();
        seg.modify(1,a[t].l,a[t].r,t,-1);
    }
    for(int i{1};i<=vx;++i){
        int v=seg.query(1,i);
        adde(n+1,v,vs[i+1]-vs[i]);
    }
    cout<<topo()<<'\n';
    return 0;
}
```

---

## 作者：大菜鸡fks (赞：3)

dp[i]表示一个小球从第i个障碍下落最后会分解成dp[i]个

考虑用树套树（线段树套set）维护扫描线，从底往上扫更新dp值。

```cpp
#include<cstdio>
#include<algorithm>
#include<set>
#define int long long
using namespace std;
inline int read(){int x=0,f=1; char ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void write(int x){if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10); putchar(x%10+'0');}
inline void writeln(int x){write(x); puts("");}
const int maxn=1e5+5,mod=1e9+7;
struct node{
	int h,l,r,s;
}e[maxn];
struct event{
	int id,h,opt;
}b[maxn<<1];
struct tree{
	int h,id;
	bool operator <( const tree a)const {
		return h>a.h;
	}
};
set<tree> a[maxn<<2];
int height,ID,tot,H,w,n,dp[maxn];
inline void init(){
	H=read(); w=read(); n=read();
	for (int i=1;i<=n;i++){
		int h=read(),l=read(),r=read(),s=read();
		e[i]=(node){h,l,r,s};
		b[++tot]=(event){i,h,1};
		if (h+s<=H) b[++tot]=(event){i,h+s+1,0};
	}
}
inline bool cmp(event a,event b){
	if (a.h==b.h) return a.opt<b.opt;
	return a.h<b.h;
}
void update(int k,int l,int r,int x,int y,int opt){
	int mid=(l+r)>>1;
	if (l==x&&r==y){
		if (opt==0) a[k].erase((tree){height,ID});
			else a[k].insert((tree){height,ID}); 
		return;
	}
	if (mid>=y) update(k<<1,l,mid,x,y,opt);
		else if (mid<x) update(k<<1|1,mid+1,r,x,y,opt);
			else update(k<<1,l,mid,x,mid,opt),update(k<<1|1,mid+1,r,mid+1,y,opt);
}
tree ans;
void query(int k,int l,int r,int x){
	if (!a[k].empty()){
		tree temp=* a[k].begin();
		if (temp<ans) {
			ans=temp;
		}
	}
	if (l==r){
		return;
	}
	int mid=(l+r)>>1;
	if (mid>=x) query(k<<1,l,mid,x);
		else query(k<<1|1,mid+1,r,x);
}
inline int query(int x){
	ans=(tree){-1,-1};
	query(1,1,w,x);
	if (ans.id==-1) return 1;
		else return dp[ans.id];
}
inline void solve(){
	sort(b+1,b+1+tot,cmp);
	for (int i=1;i<=tot;i++){
		ID=b[i].id;
		node now=e[ID];
		height=now.h;
		if (b[i].opt==0){
			update(1,1,w,now.l,now.r,0);
		}else{
			if (now.l==1) dp[ID]=query(now.r+1)*2%mod;
				else if (now.r==w) dp[ID]=query(now.l-1)*2%mod;
					else (dp[ID]=query(now.l-1)+query(now.r+1))%=mod;
			update(1,1,w,now.l,now.r,1);
		}
	}
	int res=0;
	for (int i=1;i<=w;i++){
		(res+=query(i))%=mod;
	}
	writeln(res);
}
signed main(){
	init();
	solve();
	return 0;
}
```

---

## 作者：SunsetSamsara (赞：2)

## 题意

有一个高 $h$，宽 $w$ 的地图，有一些球从高度为 $h + 1$ 的直线处开始下落。同时会有 $n$ 个挡板，每一个挡板都有左右端点 $l_i, r_i$ 和一个高度 $u_i$。到达挡板时，如果小球从上次分裂前下落的高度大于 $s_i$，就会直接穿过；否则会分裂后从挡板的两侧边缘处分别下落（如果有一侧到了边界，那么就会都从另一侧边缘下落）

## 分析

发现这个问题似乎可以扫描线，于是考虑如何用线段树维护小球的总数和当前下落的高度。为了使用线段树，我们维护一个位置上所有小球的集合（只在叶子节点处维护）。这时我们可以发现：一个挡板会减少至少 $1$ 个集合，同时至多新增 $2$ 个集合。不难看出，最多会有 $w + n$ 个集合。那么，我们就在每一个位置维护一个 `priority_queue`，用小根堆维护当前的最低高度。从上到下对于每一个挡板，维护在这个挡板区间内的球的数量，在将它们 `pop` 掉的同时在两边新增两个球的集合。注意，这里对于一模一样的球（位置与开始下落位置相同），要直接记录数量而不是一个个 `push` 进入 `priority_queue`。这样的话就可以不炸空间了。

但是，发现此时的复杂度并不是非常的正确，于是考虑使用一个剪枝：维护当前区间内的最小高度值。因为每一个有用的挡板都会至少少掉一个集合，所以最多 $n$ 次撞击之后就会全变成 `inf`。这时我们就会拥有一个正确的 $O(n\log n)$ 的复杂度了。

## 代码

```cpp
// ...快读...
#include <algorithm>
#include <queue>
const int mod = 1e9 + 7;
int h, w, n;
inline int min(const int &x, const int &y) { return x < y ? x : y; }
inline int max(const int &x, const int &y) { return x < y ? y : x; }
struct barrier {
	int h, l, r, s;
} a[100010];
inline bool operator < (const barrier &x, const barrier &y) { return x.h > y.h; }
int L[400010], R[400010];
int minh[400010];
std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int> >,
					std::greater<std::pair<int, int> > > pq[400010]; // 在每一个位置维护 priority_queue
inline void build(int k, int l, int r) {
	L[k] = l, R[k] = r;
	if (l == r) {
		pq[k].push({h + 1, 1});
		minh[k] = h + 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	minh[k] = min(minh[k << 1], minh[k << 1 | 1]); // 维护最小值
}
inline int query(int k, int l, int r, int x) {
	if (minh[k] > x) return 0; // 剪枝
	if (L[k] == R[k]) {
		int res = 0;
		for (; pq[k].size() && pq[k].top().first <= x; )
			res = (res + pq[k].top().second) % mod, pq[k].pop();
		if (!pq[k].size()) minh[k] = 0x3f3f3f3f;
		else minh[k] = pq[k].top().first;
		return res;
	}
	int mid = (L[k] + R[k]) >> 1, res = 0;
	if (l <= mid) res = (res + query(k << 1, l, r, x)) % mod;
	if (mid < r) res = (res + query(k << 1 | 1, l, r, x)) % mod;
	minh[k] = min(minh[k << 1], minh[k << 1 | 1]);
	return res;
}
inline void modify(int k, int pos, int h, int val) {
	if (L[k] == R[k]) {
		pq[k].push({h, val});
		minh[k] = pq[k].top().first;
		return;
	}
	int mid = (L[k] + R[k]) >> 1;
	if (pos <= mid) modify(k << 1, pos, h, val);
	else modify(k << 1 | 1, pos, h, val);
	minh[k] = min(minh[k << 1], minh[k << 1 | 1]);
}
int main() {
	cio.scan(h, w, n);
	for (int i = 1; i <= n; ++ i)
		cio.scan(a[i].h, a[i].l, a[i].r, a[i].s);
	std::sort(a + 1, a + n + 1);
	build(1, 1, w);
	for (int i = 1, v; i <= n; ++ i) {
		v = query(1, a[i].l, a[i].r, min(h + 1, a[i].h + a[i].s));
		if (a[i].l == 1) modify(1, a[i].r + 1, a[i].h, 2 * v % mod);
		else if (a[i].r == w) modify(1, a[i].l - 1, a[i].h, 2 * v % mod);
		else modify(1, a[i].r + 1, a[i].h, v), modify(1, a[i].l - 1, a[i].h, v);
	}
	cio.print(query(1, 1, w, 0x3f3f3f3f));
}
```

---

## 作者：绝顶我为峰 (赞：2)

模拟赛考了这题，写了个树套树没调出来/px

这道题几乎没有什么思维难度，是一个三维数点的板子，每个板子可以接住正上方一个 $s_i\times(r_i-l_i+1)$ 的矩形内的球，可以用树套树维护。

但是内层再开一个线段树会炸空间（我们模拟赛限制 256MB），~~并且不好写，不好调~~，我们考虑换个方法。

注意到对于每个位置上所有球，一个板子能接到的一定是一个区间，所以可以用堆直接维护每个位置上球的高度，数量即可。

然后需要维护每个区间的最小高度用来剪枝，防止在无用区间浪费时间。

对于每个板子，我们直接在矩形内查询，统计答案，然后分别在板子两侧加入同样数量的球即可。

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
#define int long long
const int mod=1000000007;
struct board
{
	int h,l,r,s;
	bool operator <(const board &other) const
	{
		return h>other.h;
	}
}a[100001];
int maxn,w,n,sum,ans[100001<<2];
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q[100001];
inline int read()
{
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x;
}
inline int ls(int k)
{
	return k<<1;
}
inline int rs(int k)
{
	return k<<1|1;
}
inline void push_up(int k)
{
	ans[k]=min(ans[ls(k)],ans[rs(k)]);
}
void build(int k,int l,int r)
{
	if(l==r)
	{
		q[l].push(make_pair(maxn+1,1));
		ans[k]=maxn+1;
		return;
	}
	int mid=(l+r)>>1;
	build(ls(k),l,mid);
	build(rs(k),mid+1,r);
	push_up(k);
}
void update(int node,int l,int r,int k,int p,int h)
{
	if(l==r)
	{
		q[l].push(make_pair(h,p));
		ans[k]=min(ans[k],h);
		return;
	}
	int mid=(l+r)>>1;
	if(node<=mid)
		update(node,l,mid,ls(k),p,h);
	else
		update(node,mid+1,r,rs(k),p,h);
	push_up(k);
}
int query(int nl,int nr,int l,int r,int k,int h,int s)
{
	if(ans[k]>h+s)
		return 0;
	if(l==r)
	{
		int res=0;
		while(!q[l].empty()&&q[l].top().first<=h+s)
		{
			res=(res+q[l].top().second)%mod;
			q[l].pop();
		}
		ans[k]=q[l].empty()? 1e10+7:q[l].top().first;
		return res;
	}
	int mid=(l+r)>>1,res=0;
	if(nl<=mid)
		res=(res+query(nl,nr,l,mid,ls(k),h,s))%mod;
	if(nr>mid)
		res=(res+query(nl,nr,mid+1,r,rs(k),h,s))%mod;
	push_up(k);
	return res;
}
signed main()
{
	maxn=read(),w=read(),n=read();
	for(register int i=1;i<=n;++i)
		a[i].h=read(),a[i].l=read(),a[i].r=read(),a[i].s=read();
	sum=w;
	build(1,1,w);
	sort(a+1,a+n+1);
	for(register int i=1;i<=n;++i)
	{
		int tmp=query(a[i].l,a[i].r,1,w,1,a[i].h,a[i].s);
		sum=(sum+tmp)%mod;
		if(a[i].l==1)
			update(a[i].r+1,1,w,1,(tmp<<1)%mod,a[i].h);
		else
			if(a[i].r==w)
				update(a[i].l-1,1,w,1,(tmp<<1)%mod,a[i].h);
			else
			{
				update(a[i].l-1,1,w,1,tmp,a[i].h);
				update(a[i].r+1,1,w,1,tmp,a[i].h);
			}
	}
	printf("%lld\n",sum);
	return 0;
}
```


---

## 作者：yanghanyv (赞：1)

来个不一样的做法：扫描线，线段树上二分。

### 思路
我们发现只需找到小球落到每个挡板后的下一个挡板，就可以建出一张 DAG，在 DAG 上简单 DP 即可求方案。  
所以我们考虑怎么建图。  
大多人用扫描线是从下到上扫描的，但我们考虑从左到右扫描。  
我们在挡板左端做加入操作，右端做删除操作，对于扫描中每一个横坐标，我们可以用线段树维护出每个高度的挡板编号。  
对于第 $i$ 号挡板，我们需要在横坐标为 $l_i-1$ 和 $r_i+1$ 时，找到最高的挡板 $j$，满足 $u_j < u_i$ 且 $u_j + s_j \geq u_i$。  
显然，我们只要在线段树上维护区间 $u_j + s_j$ 的最大值，就可以线段树上二分，对每个 $i$ 求出对应的 $j$。  
时间复杂度 $O((n + w)\log{n})$。  

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
const int MOD=1e9+7;
int Add(int a,int b){
	return (a+b)%MOD;
}
int Mul(int a,int b){
	return 1ll*a*b%MOD;
}
int h,w,n,u[N],s[N],ord[N],rk[N],cnt,f[N];
vector<int> lh,ne[N];
struct operation{
	int t,id,x;
	bool operator < (const operation &B) const{
		//注意排序时的优先级，这个需要全面的考虑 
		if(x!=B.x){
			return x<B.x;
		}else{
			if(t!=B.t){
				return t<B.t;
			}else{
				if(t){
					return u[id]>u[B.id];
				}else{
					return u[id]<u[B.id];
				}
			}
		}
	}
}op[2*N];
struct SGT{//线段树 
	struct node{
		int l,r,val;
	}tree[4*N];
	void pushup(int p){
		tree[p].val=max(tree[2*p].val,tree[2*p+1].val);
	}
	void build(int p,int l,int r){
		tree[p]={l,r,0};
		if(l<r){
			int mid=(l+r)/2;
			build(2*p,l,mid);
			build(2*p+1,mid+1,r);
		}
	}
	void modify(int p,int x,int v){
		int l1=tree[p].l,r1=tree[p].r;
		if(l1==r1){
			tree[p].val=u[v]+s[v];
		}else{
			int mid=(l1+r1)/2;
			if(x<=mid){
				modify(2*p,x,v);
			}else{
				modify(2*p+1,x,v);
			}
			pushup(p);
		}
	}
	int query(int p,int x,int v){
		int res=0;
		if(x){
			int l1=tree[p].l,r1=tree[p].r;
			if(l1==r1){
				if(tree[p].val>=v){
					res=r1;
				}
			}else{
				int mid=(l1+r1)/2;
				if(x>mid){
					res=query(2*p+1,x,v);
				}
				if(!res&&tree[2*p].val>=v){
					res=query(2*p,x,v);
				}
				//线段树上二分的精髓在于上面的两个if，如果写错复杂度就会不对 
			}
		}
		return res;
	}
}tr;
int main(){
	scanf("%d%d%d",&h,&w,&n);
	for(int i=1;i<=n;i++){
		int l,r;
		scanf("%d%d%d%d",&u[i],&l,&r,&s[i]);
		ord[i]=i;
		if(l-1){
			op[++cnt]={1,i,l-1};
		}else{
			lh.push_back(i);//所有靠到1的挡板特殊处理 
		}
		if(r+1<=w){
			op[++cnt]={0,i,r+1};
		}
	}
	sort(ord+1,ord+n+1,[&](int x,int y){
		return u[x]<u[y];
	});
	for(int i=1;i<=n;i++){
		rk[ord[i]]=i;
	}
	//ord[i]指第i低的挡板编号，rk[i]指挡板i的高度排名 
	sort(op+1,op+cnt+1);
	tr.build(1,1,n);
	for(int i=0;i<lh.size();i++){
		tr.modify(1,rk[lh[i]],lh[i]);//一定要加入靠到1的挡板 
	}
	for(int i=1,j=1;i<=w;i++){
		while(j<=cnt&&op[j].x==i&&!op[j].t){
			int idx=op[j].id;
			tr.modify(1,rk[idx],0);//删除挡板 
			ne[rk[idx]].push_back(tr.query(1,rk[idx]-1,u[idx]));
			j++;
		}
		f[tr.query(1,n,h+1)]++;
		while(j<=cnt&&op[j].x==i&&op[j].t){
			int idx=op[j].id;
			ne[rk[idx]].push_back(tr.query(1,rk[idx]-1,u[idx]));
			tr.modify(1,rk[idx],idx);//加入挡板 
			j++;
		}
	}
	for(int i=n;i>=1;i--){
		if(ne[i].size()==1){
			f[ne[i][0]]=Add(f[ne[i][0]],Mul(2,f[i]));
		}else{
			f[ne[i][0]]=Add(f[ne[i][0]],f[i]);
			f[ne[i][1]]=Add(f[ne[i][1]],f[i]);
		}
	}
	//DAG上DP 
	printf("%d",f[0]);
	return 0;
}
```

---

## 作者：cyffff (赞：1)

[$\text{Link}$](https://www.luogu.com.cn/problem/CF780G)

提供一个暴力做法，模拟赛时过了。
## 题意
有一个 $h\times w$ 的屏幕，屏幕上方每列有一个小球，你可以认为它们的初始高度为 $h+1$。小球会沿所在列竖直下落。

屏幕上有 $n$ 个挡板，第 $i$ 个挡板在 $u_i$ 的高度，位于 $[l_i,r_i]$ 之间的列，拥有属性 $s_i$。

具体地，当一个从高度 $t$ 开始掉落的小球落在挡板 $i$ 上时，
- 若 $i>u_i+s_i$，则 $i$ 会直接穿过当前挡板（不重新计算开始掉落高度）；
- 否则，该球会分裂为两个小球，分别在 $l_i-1$ 和 $r_i+1$ 列，从高度为 $u_i$ 的地方开始下落。若上面两列有一个不在屏幕内，则对应的小球变到另一边。

保证一行最多只有一个挡板。

$n,w\le 10^5$，$h_i\le 10^9$。

## 思路
声明：本题解仅为比较优秀的暴力，过了 CF 数据。如有需要请忽略本题解。

考虑到除了 $h+1$ 行，每一行都最多只有 $2$ 列有小球。

对于第 $h+1$ 行，维护并查集以支持快速删除/查找区间剩余小球位置。和[这个](https://www.luogu.com.cn/discuss/372365)一样。（这部分复杂度是正确的）

对于其余行，对所有有球的行维护 `set`，每次查询、删除时遍历符合条件的所有行，并将其区间内的点删去。

复杂度正确的做法有 `KD-Tree`，线段树对列维护 `set` 之类，其余题解有讲，且都较为直观，本题解便不做说明。

代码：

甚至跑到了最优解。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
namespace IO{//by cyffff
	
}
const int N=3e5+10,mod=1e9+7;
int h,w,n;
struct block{
	int u,l,r,s;
	inline friend bool operator<(const block &a,const block &b){
		return a.u>b.u;
	}
}b[N];
vector<int>num;
inline int find(int x){
	return lower_bound(num.begin(),num.end(),x)-num.begin()+1;
}
int f[N];
inline int findf(int x){
	return x==f[x]?x:f[x]=findf(f[x]);
}
struct node{
	int u;
	mutable int p1,p2,c;
	int cc;
	inline friend bool operator<(const node &a,const node &b){
		return a.u>b.u;
	}
	inline friend bool operator<(const node &a,const int &b){
		return a.u>b;
	}
};
set<node>hx;
inline bool ins(int x,int l,int r){
	return l<=x&&x<=r;
}
int main(){
	h=read(),w=read(),n=read();
	for(int i=1;i<=n;i++)
		b[i].u=read(),b[i].l=read(),
		b[i].r=read(),b[i].s=read()+b[i].u;
	for(int i=1;i<=w+1;i++)	
		f[i]=i;
	sort(b+1,b+n+1);
	num.push_back(h+1);
	for(int i=1;i<=n;i++)
		num.push_back(b[i].u),
		num.push_back(b[i].s);
	sort(num.begin(),num.end());
	num.resize(unique(num.begin(),num.end())-num.begin());
	int tmp=find(h+1),L=num.size()+10;
	for(int i=1;i<=n;i++){
		int u=find(b[i].u),l=b[i].l,r=b[i].r,s=find(b[i].s);
		int c=0;
		if(s>=tmp){
			for(int i=findf(l);i<=r;i=findf(i))
				c++,f[i]=i+1;
		}
		int t=s;
		auto it=hx.lower_bound({t,0,0,0,0});
		for(;it!=hx.end();){
			node tmp=*it;
			if(tmp.p1&&ins(tmp.p1,l,r)) tmp.p1=0,tmp.c--,c=(c+tmp.cc)%mod;
			if(tmp.p2&&ins(tmp.p2,l,r)) tmp.p2=0,tmp.c--,c=(c+tmp.cc)%mod;
			t=tmp.u-1;
			if(tmp.c==0) hx.erase(it);
			else it->p1=tmp.p1,it->p2=tmp.p2,it->c=tmp.c;
			it=hx.lower_bound({t,0,0,0,0});
		}
		if(!c) continue;
		if(l<=1) hx.insert({u,r+1,r+1,2,c}); 
		else if(r>=w) hx.insert({u,l-1,l-1,2,c}); 
		else hx.insert({u,l-1,r+1,2,c}); 
	}
	int ans=0;
	for(int i=findf(1);i<=w;i=findf(i+1))
		ans++,f[i]=i+1;
	for(auto x:hx)
		ans=(ans+1ll*x.cc*x.c)%mod;
	write(ans);
	flush();
}
```
再见 qwq~

---

## 作者：Rubyonly (赞：1)

不妨考虑一个球从一个坐标 $(x,y)$ 下落的答案，但是 $h\leq 10^9, w\leq 10^5$，直接定义并不可行

容易发现，有用的状态只有起始的 $w$ 个点和 $n$ 个障碍的左右两个点 $(l_i-1,u_i),(r_i+1,u_i)$，所以状态数是 $\mathcal{O} (n)$ 级别的

然后对于每个点，找到下面第一个能挡住它（即满足 $u_i< h \leq u_i+s_i$）的障碍，直接 $dp$ 转移是 $\mathcal{O} (n^2)$ 的

考虑对转移进行优化，不妨按高度从上往下考虑每个障碍的左右能有多少个球到达，其实就是对所有满足 $l_i\leq x\leq r_i,u_i\leq r\leq u_i+s_i$ 的点的权值求和并清零，然后更新到当前障碍的左右端点上，这个用 $\text{KD-Tree}$ 维护一下就行了

```c++
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 3e5 + 50, INF = 0x3f3f3f3f, mod = 1e9 + 7;

inline int read () {
	register int x = 0, w = 1;
	register char ch = getchar ();
	for (; ch < '0' || ch > '9'; ch = getchar ()) if (ch == '-') w = -1;
	for (; ch >= '0' && ch <= '9'; ch = getchar ()) x = x * 10 + ch - '0';
	return x * w;
}

inline int addmod (register int a, register int b) {
	return a += b, a >= mod ? a - mod : a;
}

int h, w, n, rt, now, len, nowans, p[maxn], mp[maxn];

struct Node {
	int id, h, l, r, s;
	inline friend bool operator < (register const Node &a, register const Node &b) { return a.h > b.h; }
} a[maxn];

struct Tree {
	int fa, lch, rch, val, sumval, id, d[2], maxx[2], minn[2];
	bool lazy;
	Tree () {}
	Tree (register int x, register int y, register int z) { lch = rch = val = sumval = 0, d[0] = x, d[1] = y, id = z; }
	inline friend bool operator < (register const Tree &a, register const Tree &b) { return a.d[now] < b.d[now]; }
} b[maxn], tree[maxn];

inline void Pushup (register int rt) {
	register int lch = tree[rt].lch, rch = tree[rt].rch;
	tree[rt].sumval = addmod (tree[rt].val, addmod (tree[lch].sumval, tree[rch].sumval));
	for (register int i = 0; i < 2; i ++) {
		tree[rt].maxx[i] = tree[rt].minn[i] = tree[rt].d[i];
		if (lch) tree[rt].maxx[i] = max (tree[rt].maxx[i], tree[lch].maxx[i]), tree[rt].minn[i] = min (tree[rt].minn[i], tree[lch].minn[i]);
		if (rch) tree[rt].maxx[i] = max (tree[rt].maxx[i], tree[rch].maxx[i]), tree[rt].minn[i] = min (tree[rt].minn[i], tree[rch].minn[i]);	
	}
}

inline void Update (register int rt) {
	tree[rt].val = tree[rt].sumval = 0, tree[rt].lazy = 1;
}

inline void Pushdown (register int rt) {
	if (! tree[rt].lazy) return;
	if (tree[rt].lch) Update (tree[rt].lch);
	if (tree[rt].rch) Update (tree[rt].rch);
	tree[rt].lazy = 0;
}

inline int Build (register int l, register int r, register int typ, register int fa) {
	register int mid = (l + r) >> 1; now = typ;
	nth_element (b + l, b + mid, b + r + 1);
	tree[mid] = b[mid], tree[mid].fa = fa, mp[b[mid].id] = mid;
	if (b[mid].id == 0) tree[mid].val = 1;
	if (l < mid) tree[mid].lch = Build (l, mid - 1, typ ^ 1, mid);
	if (r > mid) tree[mid].rch = Build (mid + 1, r, typ ^ 1, mid);
	return Pushup (mid), mid;
}

inline void Modify (register int rt, register int val) {
	register int u = rt, num = 0;
	while (u) p[++ num] = u, u = tree[u].fa;
	for (register int i = num; i >= 1; i --) Pushdown (p[i]);
	tree[rt].val = addmod (tree[rt].val, val);
	for (register int i = 1; i <= num; i ++) Pushup (p[i]);
}

inline void Query (register int rt, register int xl, register int xr, register int yl, register int yr) {
	if (! tree[rt].sumval) return;
	if (tree[rt].maxx[0] < xl || tree[rt].minn[0] > xr) return;
	if (tree[rt].maxx[1] < yl || tree[rt].minn[1] > yr) return;
	if (xl <= tree[rt].minn[0] && tree[rt].maxx[0] <= xr && yl <= tree[rt].minn[1] && tree[rt].maxx[1] <= yr) return nowans = addmod (nowans, tree[rt].sumval), Update (rt), void ();
	if (xl <= tree[rt].d[0] && tree[rt].d[0] <= xr && yl <= tree[rt].d[1] && tree[rt].d[1] <= yr) nowans = addmod (nowans, tree[rt].val), tree[rt].val = 0;
	Pushdown (rt);
	register int lch = tree[rt].lch, rch = tree[rt].rch;
	if (lch) Query (lch, xl, xr, yl, yr);
	if (rch) Query (rch, xl, xr, yl, yr);
	Pushup (rt);
}

int main () {
	h = read(), w = read(), n = read();
	for (register int i = 1; i <= w; i ++) b[++ len] = Tree (i, h + 1, 0);
	for (register int i = 1; i <= n; i ++) {
		a[i].id = i, a[i].h = read(), a[i].l = read(), a[i].r = read(), a[i].s = read();
		if (a[i].l > 1) b[++ len] = Tree (a[i].l - 1, a[i].h, i);
		if (a[i].r < w) b[++ len] = Tree (a[i].r + 1, a[i].h, i + n);
	}
	rt = Build (1, len, 0, 0), sort (a + 1, a + n + 1);
	for (register int i = 1, id; i <= n; i ++) {
		nowans = 0, id = a[i].id, Query (rt, a[i].l, a[i].r, a[i].h + 1, a[i].h + a[i].s);
		a[i].l == 1 ? Modify (mp[id + n], nowans) : Modify (mp[id], nowans);
		a[i].r == w ? Modify (mp[id], nowans) : Modify (mp[id + n], nowans);
	}
	return printf ("%d\n", tree[rt].sumval), 0;
}
```

---

## 作者：qfpjm (赞：1)

# 题解

- 开始以为是个模拟，结果 $1\leq h\leq 10^9,1\leq w,n\leq 10^5$。那么我们只能考虑 $O(n)$ 或 $O(n\log n)$ 的做法。

- 由于我们初始有 $w$ 个小球，穿过屏障时最有会多一个小球，而每一高度最多只有一个屏障，所以小球的个数在 $n+w$ 之内。

- 所以，我们可以每一列维护一个栈，记录该列还存在的小球。屏障的话，我们需要知道哪一些球会落在上面。可以用线段树维护区间中最低的球，判断其会不会落在屏障上，是则将球记录在栈中，并退栈；否则，处理完当前屏障。

- 最后的答案即为每个栈中的球的个数和。

- 由于我们需要对每个球用线段树进行处理，所以最终的时间复杂度为 $O((n+w)\log w)$。

- 代码懒得写了。

---

## 作者：BYR_KKK (赞：0)

做 ds 做傻了。

将落到木板上分裂的球称为一类球，直接穿过的称为二类球。

观察到对于一个木板，只关注有多少一类球落到它上面而不关心具体坐标。维护球所在坐标是不可行的。考虑维护木板，维护有多少一类球落到这个木板上。按照高度枚举所有木板，能得到某个坐标某个高度上新增出来的球。这些球作为一类球落到木板 $i$ 的条件是 $h_i<now$，$u_i+s_i>=now$，并且 $i$ 是该坐标上最高的满足条件的木板。乍一看很像一个偏序形式，但是我并不会维护。

考虑枚举木板的同时加入 $u_i+s_i>now$ 的木板，在线段树上维护 `set` 代表覆盖区间坐标的所有 $(h_i,i)$，标记永久化维护，查询时单点查询即可。

注意取模！

[代码](https://codeforces.com/contest/780/submission/277850584)。

---

## 作者：Fan_sheng (赞：0)

这里提供一个线段树分治解法。

首先把所有板子按高度从小到大排序，$dp[i]$ 表示一个球落到 $i$ 号板上，最终分裂出的小球个数。

考虑 $i$ 上的球下一步会落到哪个板子上。容易发现，它们满足以下条件。

向左落到 $j$ 上（此时 $l[i]>1$）：

一定有 $l[j]\le l[i]-1\le r[j]\land u[i]-s[j]\le u[j]\le u[i]$。如果不存在这样的 $j$，落到地面上；否则取 $u[j]$ 最大的那个 $j$。

向右落到 $k$ 上（此时 $r[i]<w$）：

一定有 $l[k]\le r[i]+1\le r[k]\land u[i]-s[k]\le u[k]\le u[i]$。如果不存在这样的 $k$，落到地面上，否则取 $u[k]$ 最大的那个 $k$。

知道了 $j,k$ 后，可以简单地计算出 $dp[i]$。

如果没有 $s$ 的限制，就可以直接从下往上扫描，并在线段树上区间覆盖来找到 $j,k$。

有限制就是这样一个问题：往线段树上插入和删除若干条水平线段（扫到高度 $u[j]$ 后就加入线段 $j$，扫到大于 $u[j]+s[j]$ 的高度之后就删除线段 $j$），求出与直线 $x=i$ 相交的线段中，最高的那条线段的编号。这基本就是 [[HEOI2013]Segment](https://www.luogu.com.cn/problem/P4097)，李超树板子。

李超树是不支持删线段的，但是支持撤销线段，这启发我们将操作离线下来进行线段树分治，用 $\mathbb O(n\log^2n)$ 的时间解决问题。

最后计算答案也是类似的。先把所有板子都插入李超树中，对于 $i\in[1,w]$，找出满足 $l[j]\le i\le r[j]\land u[j]+s[j]\le h+1$ 且 $u[j]$ 最大的 $j$，$dp$ 值加和一下即可。

code

由于只有水平线段，所以都不用整个李超树，普通的标记永久化线段树就好了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int h,w,n,tag[100005],b[100005],ans;
struct star{
	int u,l,r,s;
	friend bool operator<(const star&x,const star&y){return x.u<y.u;}
}bot[100005];
namespace LC{
	int tree[100003<<2];
	vector<pair<int,int>>cl;
	#define cmp(x,y) bot[x].u>bot[y].u
	void update(int id,int l,int r,int ql,int qr,int upd){
		if(l>qr||r<ql)return;
		if(l>=ql&&r<=qr){
			if(cmp(upd,tree[id]))
			cl.emplace_back(id,tree[id]),tree[id]=upd;
			return;
		}
		int mid=(l+r)>>1;
		update(id<<1,l,mid,ql,qr,upd),update(id<<1|1,mid+1,r,ql,qr,upd);
	}
	int query(int id,int l,int r,int pos){
		if(l>pos||r<pos)return 0;
		if(l==r)return tree[id];
		int mid=(l+r)>>1;
		int res1=query(id<<1,l,mid,pos),res2=query(id<<1|1,mid+1,r,pos);
		res1=cmp(res1,res2)?res1:res2;
		return cmp(res1,tree[id])?res1:tree[id];
	}
}using namespace LC;
namespace ST{
	vector<int>uuz[100005<<2];
	void update(int id,int l,int r,int ql,int qr,int t){
		if(l>qr||r<ql)return;
		if(l>=ql&&r<=qr){uuz[id].emplace_back(t);return;}
		int mid=(l+r)>>1;
		update(id<<1,l,mid,ql,qr,t),update(id<<1|1,mid+1,r,ql,qr,t);
	}
	void query(int id,int l,int r){
		int back=cl.size();
		for(int v:uuz[id])LC::update(1,1,w,bot[v].l,bot[v].r,v);
		if(l==r){
			int a=tag[LC::query(1,1,w,bot[l].r+1)];
			int b=tag[LC::query(1,1,w,bot[l].l-1)];
			tag[l]=((bot[l].l==1?a:b)+(bot[l].r==w?b:a))%mod;
		}else{
			int mid=(l+r)>>1;
			query(id<<1,l,mid),query(id<<1|1,mid+1,r);
		}
		while(cl.size()!=back)
		tree[cl.back().first]=cl.back().second,cl.pop_back();
	}
}
int main(){
	scanf("%d%d%d",&h,&w,&n);
	for(int i=1;i<=n;i++)
	scanf("%d%d%d%d",&bot[i].u,&bot[i].l,&bot[i].r,&bot[i].s);
	if(!n)printf("%d",w),exit(0);
	sort(bot+1,bot+n+1);
	for(int i=1;i<=n;i++)b[i]=bot[i].u;
	for(int i=1;i<=n;i++)
	ST::update(1,1,n,i+1,upper_bound(b+1,b+n+1,bot[i].u+bot[i].s)-b-1,i);
	ST::query(tag[0]=1,1,n);
	for(int i=1;i<=n;i++)if(bot[i].u+bot[i].s>=h+1)
	update(1,1,w,bot[i].l,bot[i].r,i);
	for(int i=1;i<=w;i++)ans=(ans+tag[query(1,1,w,i)])%mod;
	printf("%d",ans);return 0;
}
```


---

## 作者：orz_z (赞：0)

### CF780G Andryusha and Nervous Barriers

考虑树套树。

一维维护区间列，另一维维护列上的球的高度，保证点数正确。

维护单点加，区间查。

扫描线高度从大到小维护到每一个板时的情况。

优化：区间查是判区间球高度最小都只能穿过挡板就结束掉。

时间复杂度 $\mathcal O(n\log^2n)$。


```cpp
#include<bits/stdc++.h>

using namespace std;

#define int long long
typedef long long ll;

#define ha putchar(' ')
#define he putchar('\n')

inline int read() {
	int x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')
			f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
		x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return x * f;
}

inline void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)
		write(x / 10);
	putchar(x % 10 + 48);
}

const int _ = 1e5 + 10, mod = 1e9 + 7;

int h, w, n, N;

ll ans[_ << 2];

priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q[_];

struct abc {
	int u, l, r, s;
	bool operator < (const abc &t) const {
		return u > t.u;
	}
} k[_];

void build(int o, int l, int r) {
	if (l == r) {
		q[l].push({h + 1, 1});
		ans[o] = h + 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(o << 1, l, mid), build(o << 1 | 1, mid + 1, r);
	ans[o] = min(ans[o << 1], ans[o << 1 | 1]);
}

void upd(int o, int l, int r, int pos, int p, int h) {
	if (l == r) {
		q[l].push({h, p});
		ans[o] = min(ans[o], (ll)h);
		return;
	}
	int mid = (l + r) >> 1;
	if (pos <= mid) upd(o << 1, l, mid, pos, p, h);
	else upd(o << 1 | 1, mid + 1, r, pos, p, h);
	ans[o] = min(ans[o << 1], ans[o << 1 | 1]);
}

int qry(int o, int l, int r, int L, int R, int h, int s) {
	if (ans[o] > h + s) return 0;
	if (l == r) {
		int res = 0;
		while (!q[l].empty() && q[l].top().first <= h + s) {
			res = (res + q[l].top().second) % mod;
			q[l].pop();
		}
		ans[o] = q[l].empty() ? 1e10 + 7 : q[l].top().first;
		return res;
	}
	int mid = (l + r) >> 1, res = 0;
	if (L <= mid) res = qry(o << 1, l, mid, L, R, h, s);
	if (R > mid) res = (res + qry(o << 1 | 1, mid + 1, r, L, R, h, s)) % mod;
	ans[o] = min(ans[o << 1], ans[o << 1 | 1]);
	return res;
}

signed main() {
	h = read(), w = read(), n = read();
	for (int i = 1; i <= n; ++i) k[i].u = read(), k[i].l = read(), k[i].r = read(), k[i].s = read();
	N = w;
	build(1, 1, w);
	sort(k + 1, k + n + 1);
	for (int i = 1; i <= n; ++i) {
		int t = qry(1, 1, w, k[i].l, k[i].r, k[i].u, k[i].s);
		N = (N + t) % mod;
		if (k[i].l == 1) upd(1, 1, w, k[i].r + 1, (t << 1) % mod, k[i].u);
		else if (k[i].r == w) upd(1, 1, w, k[i].l - 1, (t << 1) % mod, k[i].u);
		else {
			upd(1, 1, w, k[i].l - 1, t, k[i].u);
			upd(1, 1, w, k[i].r + 1, t, k[i].u);
		}
	}
	write(N), he;
	return 0;
}
```

---

