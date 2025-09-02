# 【MX-X5-T6】「GFOI Round 1」Abiogenesis

## 题目背景

原题链接：<https://oier.team/problems/X5G>。

---

> [Abiogenesis - Juggernaut.](https://music.163.com/#/song?id=1416321652)

本题为 [Codeforces 1981 E. Turtle and Intersected Segments](https://codeforces.com/contest/1981/problem/E) 改编。

## 题目描述

给 $n$ 条线段 $[l_i, r_i]$，第 $i$ 条线段有一组权值 $a_i, b_i$。

有一个无向图 $G$，其初始有 $n$ 个结点，$0$ 条边。对于每一对正整数 $i, j$ 满足 $1 \le i < j \le n$，若编号为 $i, j$ 的线段相交，就在 $G$ 中连一条两个端点分别为 $i, j$，边权为 $a_i + a_j + |b_i - b_j|$ 的边。

求 $G$ 最小生成树边权之和，或报告 $G$ 不连通。

如果两条线段 $[l_1, r_1]$ 和 $[l_2, r_2]$ 满足 $\max(l_1, l_2) \le \min(r_1, r_2)$，就认为它们是相交的。

## 说明/提示

**【样例解释】**

对于第一组数据，$G$ 的形态如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/sozig2ub.png)

$G$ 的其中一个最小生成树形态如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/2ymd3s7z.png)

**【数据范围】**

**本题采用捆绑测试且开启子任务依赖。**

| 子任务编号 | $n \le$ | $\sum n \le$ | 特殊性质 | 子任务依赖 | 分值 |
| :-: | :-: | :-: | :-: | :-: | :-: |
| $1$ | $100$ | $10^5$ | 无 | 无 | $11$ |
| $2$ | $10^5$ | $10^5$ | AC | 无 | $5$ |
| $3$ | $10^5$ | $10^5$ | A | $2$ | $14$ |
| $4$ | $10^5$ | $10^5$ | B | 无 | $14$ |
| $5$ | $10^5$ | $10^5$ | C | $2$ | $14$ |
| $6$ | $10^5$ | $10^5$ | D | 无 | $14$ |
| $7$ | $10^5$ | $10^5$ | 无 | $1, 2, 3, 4, 5, 6$ | $28$ |

- 特殊性质 A：$\forall i \in [1, n], l_i = 1$。
- 特殊性质 B：$\forall i \in [1, n - 1], l_i \le l_{i + 1}, r_i \le r_{i + 1}$。
- 特殊性质 C：$\forall i \in [1, n], b_i = 1$。
- 特殊性质 D：$\forall i \in [1, n], a_i = b_i$。

对于所有数据，满足 $1 \le T \le 10^4$，$1 \le n, \sum n \le 10^5$，$1 \le l_i, r_i, a_i, b_i \le 10^8$，$l_i \le r_i$。

## 样例 #1

### 输入

```
4
5
1 7 1 3
2 4 2 6
3 5 3 5
6 7 2 9
3 4 1 4
5
2 7 3 3
1 3 5 6
4 5 3 5
6 7 1 9
1 1 5 4
4
1 4 1 3
1 2 2 1
3 4 3 5
1 4 4 4
3
1 3 1 1
2 3 1 3
4 5 1 8```

### 输出

```
22
41
17
-1```

# 题解

## 作者：bluedream (赞：2)

模板题。

特殊图 MST，考虑 Boruvka 算法。算法流程为：
- 初始每个点是一个连通块。
- 接下来进行若干轮：
	- 求出每一个连通块与其它连通块之间的边权最小的边。
   - 将这些边加入最小生成树。
- 重复直到只剩一个连通块。

由于每一轮连通块数量必定除以 $2$，所以只会执行 $O(\log n)$ 轮。

那么相当于再给每个线段指定一个颜色 $c_i$，对每个 $i$ 求出一个 $j$，使得其满足 $[l_i,r_i]$ 与 $[l_j,r_j]$ 相交且 $c_i\ne c_j$ 且 $a_j+|b_i-b_j|$ 最小。拆掉绝对值，那么会加上一维对 $b$ 的限制；而 $c$ 不同的限制只需要同时维护 $c$ 不同的次小值。如果直接做三维偏序复杂度就去到 $\log^3$ 了，肯定是过不去的。

考虑扫描线，那么我们需要对一条线段求出它在的这段时间内的所有出现过的线段的信息。那么在插入的时候求一下当前存在的线段的信息，并且用新插入的这条线段更新当前存在的所有线段的信息，在删除时取出该信息。这样我们就对每个线段求出了与其相交的所有线段的信息，可以手玩验证正确性。

上述过程可以用线段树处理，将每条线段在其对应的 $b$ 处维护，不向空子树内下传标记即可。

时间复杂度 $O(n\log^2n)$，需要精细实现，花了非常久卡常之后擦着时限通过了本题。

注意清空、无解、离散化等问题。

核心代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
//read()
#define pii pair<int,int>
#define mpr make_pair
#define fir first
#define sec second
const int N=2e5+10,INF=1e9;
int n,l[N],r[N],a[N],b[N],d[N],fa[N],bel[N];
pii c[N],w[N];
vector<int>ins[N],del[N];
ll ans;
struct node{
	int a,ta,b,tb;
	node(){ a=b=INF,ta=tb=-1; }
	node(int x,int tx){ a=x,ta=tx,b=INF,tb=-1; }
	node(int x,int tx,int y,int ty){ a=x,ta=tx,b=y,tb=ty; }
	inline friend node operator+(const node &A,const node &B){
		node a=A,b=B;
		node c;
		if(a.a>b.a) swap(a,b);
		c.a=a.a,c.ta=a.ta;
		if(a.b<=b.a||b.ta==a.ta&&a.b<=b.b) c.b=a.b,c.tb=a.tb;
		else if(b.ta!=a.ta) c.b=b.a,c.tb=b.ta;
		else c.b=b.b,c.tb=b.tb;
		return c;
	}
	inline void add(int v){
		if(ta!=-1) a+=v;
		if(tb!=-1) b+=v;
	}
};
struct Segment_Tree{
	#define ls (rt<<1)
	#define rs (rt<<1|1)
	node res[N<<2],tag[N<<2];
	inline void pushup(int rt){
		res[rt]=res[ls]+res[rs];
	}
	inline void pushtag(int rt,node v){
		if(res[rt].ta==-1) return ;
		tag[rt]=tag[rt]+v;
	}
	inline void pushdown(int rt){
		if(tag[rt].ta!=-1){
			pushtag(ls,tag[rt]);
			pushtag(rs,tag[rt]);
			tag[rt]=node();
		}
	}
	inline void build(int rt,int l,int r){
		res[rt]=tag[rt]=node();
		if(l==r) return ;
		int mid=l+r>>1;
		build(ls,l,mid),build(rs,mid+1,r); 
	}
	inline node query(int rt,int l,int r,int p){
		if(l==r) return tag[rt];
		pushdown(rt);
		int mid=l+r>>1;
		if(p<=mid) return query(ls,l,mid,p);
		else return query(rs,mid+1,r,p);
	}
	inline node query(int rt,int l,int r,int L,int R){
		if(L>R||res[rt].ta==-1) return node();
		if(L<=l&&r<=R) return res[rt];
		pushdown(rt);
		int mid=l+r>>1;
		node res;
		if(L<=mid) res=res+query(ls,l,mid,L,R);
		if(R>mid) res=res+query(rs,mid+1,r,L,R);
		return res;
	}
	inline void modify(int rt,int l,int r,int p,node v){
		if(l==r){
			res[rt]=v;
			return ;
		}
		pushdown(rt);
		int mid=l+r>>1;
		if(p<=mid) modify(ls,l,mid,p,v);
		else modify(rs,mid+1,r,p,v);
		pushup(rt);
	}
	inline void modify(int rt,int l,int r,int L,int R,node v){
		if(res[rt].ta==-1) return ;
		if(L<=l&&r<=R) return pushtag(rt,v);
		pushdown(rt);
		int mid=l+r>>1;
		if(L<=mid) modify(ls,l,mid,L,R,v);
		if(R>mid) modify(rs,mid+1,r,L,R,v);
		//pushup(rt);
	}
}T1,T2;
inline int find(int x){ return x==fa[x]?x:fa[x]=find(fa[x]); }
inline void unnion(int x,int y,int w){
	int u=find(x),v=find(y);
	if(u==v) return ;
	fa[u]=v,ans+=w;
}
/*
T1 维护 a_p-d_{b_p}
T2 维护 a_p+d_{b_p} 
*/
int main(){
	int QT=read();
	while(QT--){
		n=read(),ans=0;
		vector<int>vec;
		for(int i=1;i<=n;i++)
			l[i]=read(),r[i]=read(),a[i]=read(),b[i]=read(),
			c[i]=mpr(b[i],i),vec.push_back(l[i]),vec.push_back(r[i]);
		sort(c+1,c+n+1);
		sort(vec.begin(),vec.end());
		vec.erase(unique(vec.begin(),vec.end()),vec.end());
		int lc=vec.size();
		for(int i=1;i<=n;i++)
			fa[i]=i,b[i]=lower_bound(c+1,c+n+1,mpr(b[i],i))-c,d[i]=c[i].fir,
			l[i]=lower_bound(vec.begin(),vec.end(),l[i])-vec.begin()+1,
			r[i]=lower_bound(vec.begin(),vec.end(),r[i])-vec.begin()+1;
		for(int i=1;i<=n;i++)
			ins[l[i]].push_back(i),del[r[i]].push_back(i);
		for(int i=1;i<=n;i++)
			w[i]=mpr(INF,-1);
		bool fl=0;
		for(int i=1,s=0;i<lc;i++){
			s+=ins[i].size()-del[i].size();
			if(!s) fl=1,ans=-1; 
		}
		if(!fl){
			while(1){
				int bc=0;
				for(int i=1;i<=n;i++)
					bel[i]=find(i),bc+=bel[i]==i;
				if(bc==1) break;
//				printf("%d\n",bc);
				T1.build(1,1,n),T2.build(1,1,n);
				for(int i=1;i<=lc;i++){
					for(auto p:ins[i]){
						node t1=T1.query(1,1,n,1,b[p]),t2=T2.query(1,1,n,b[p],n);
						t1.add(a[p]+d[b[p]]),t2.add(a[p]-d[b[p]]);
						node tp=t1+t2;
						pii res;
						if(tp.ta==bel[p]) res=mpr(tp.b,tp.tb);
						else res=mpr(tp.a,tp.ta);
	//					printf("ins %d %d (%d,%d)\n",p,bel[p],res.fir,res.sec);
						if(res.sec!=-1) w[bel[p]]=min(w[bel[p]],res);
						T1.modify(1,1,n,1,b[p],node(a[p]+d[b[p]],bel[p]));
						T2.modify(1,1,n,b[p],n,node(a[p]-d[b[p]],bel[p]));
						T1.modify(1,1,n,b[p],node(a[p]-d[b[p]],bel[p]));
						T2.modify(1,1,n,b[p],node(a[p]+d[b[p]],bel[p]));
					}
					for(auto p:del[i]){
						node t1=T1.query(1,1,n,b[p]),t2=T2.query(1,1,n,b[p]);
						t1.add(a[p]-d[b[p]]),t2.add(a[p]+d[b[p]]);
						node tp=t1+t2;
						pii res;
						if(tp.ta==bel[p]) res=mpr(tp.b,tp.tb);
						else res=mpr(tp.a,tp.ta);
	//					printf("del %d %d (%d,%d)\n",p,bel[p],res.fir,res.sec);
						if(res.sec!=-1) w[bel[p]]=min(w[bel[p]],res);
						T1.modify(1,1,n,b[p],node());
						T2.modify(1,1,n,b[p],node());
					}
				}
				for(int i=1;i<=n;i++)
					if(bel[i]==i)
						unnion(i,w[i].sec,w[i].fir);
				for(int i=1;i<=n;i++)
					w[i]=mpr(INF,-1);
			}
		}
		write(ans),putc('\n');
		for(int i=1;i<=lc;i++)
			ins[i].clear(),del[i].clear(),bel[i]=0;
	}
	flush();
}
```

---

## 作者：NATO (赞：1)

你聪明的，告诉我，你到底改了什么呢？（~~Boruvka 不是原题最直观但过不去的做法吗~~）

#### 思路浅析：

看到近乎完全图的生成树问题，立马想到 Boruvka。

边权的绝对值考虑拆开，对 $b$ 做扫描线维护之，下以枚举较大的 $b$ 为例叙述，反之是类似的。

查询与我的边权最小的点即是与我有交的中 $a-b$ 的最小值，现在问题就变成了如何快速找与我有交的点。

标记永久化的做法，感觉很聪明啊（不对啊，这玩意是不是就是线段树区间加查的方法，总之就是十分聪明！）！

考虑线段树的结构，区间询问和修改都被搞到了 $\log n$ 个区间上，而拆出来的询问对修改就要么无交，要么包含或被包含了。

被包含的修改考虑在所有经过经过的节点单独记录它的贡献，查询时调用询问拆出来的节点记录的被包含贡献即可，包含的修改就直接在被修改的节点记录，查询时查所有经过区间即可。

Boruvka 注意到要维护一个不同颜色次小来找不同色最小点。

时间复杂度 $O(n\log^2n)$。

### 参考代码：


```cpp
#include<bits/stdc++.h>
#define ll int
#define INF 1147483647
using namespace std;
ll t,n;
ll f[100005];
ll find(ll x)
{
	return x==f[x]?x:f[x]=find(f[x]);
}
struct px
{
	ll l,r,a,b;
	bool operator<(const px&bb)const
	{
		return b<bb.b;
	}
}s[100005];
struct xp
{
	ll val,col;
	bool operator<(const xp&b)const
	{
		return val<b.val;
	}
	xp(ll a=INF,ll b=0)
	{
		val=a;col=b;
	}
}minn[100005];
struct nv
{
	xp minn,smin;
};
struct tree
{
	nv mt,up;
}tr[800005];
#define ls(id) id*2
#define rs(id) id*2+1
nv merge(nv a,xp s)
{
	if(a.minn.col==s.col)a.minn=min(a.minn,s);
	else if(s<a.minn)swap(a.minn,a.smin),a.minn=s;
	else a.smin=min(a.smin,s);
	return a;
}
nv mg(nv a,nv b)
{
	a=merge(a,b.minn);
	a=merge(a,b.smin);
	return a;
}
void update(ll id,ll l,ll r,ll ml,ll mr,xp s)
{
	tr[id].up=merge(tr[id].up,s);
	if(ml<=l&&r<=mr)
	{
		
		tr[id].mt=merge(tr[id].mt,s);
		return;
	}
	ll mid=l+r>>1;
	if(ml<=mid)update(ls(id),l,mid,ml,mr,s);
	if(mr>mid)update(rs(id),1+mid,r,ml,mr,s);
}
nv query(ll id,ll l,ll r,ll ml,ll mr)
{
	if(ml<=l&&r<=mr)return tr[id].up;
	ll mid=l+r>>1;
	nv res=tr[id].mt;
	if(ml<=mid)res=mg(res,query(ls(id),l,mid,ml,mr));
	if(mr>mid)res=mg(res,query(rs(id),1+mid,r,ml,mr));
	return res;
}
ll p[200005],tot;
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n;
		tot=0;
		for(ll i=1;i<=n;++i)f[i]=i,cin>>s[i].l>>s[i].r>>s[i].a>>s[i].b,p[++tot]=s[i].l,p[++tot]=s[i].r;
		sort(s+1,s+1+n);
		sort(p+1,p+1+tot);
		tot=unique(p+1,p+1+tot)-p-1;
		for(ll i=1;i<=n;++i)
		{
			s[i].l=lower_bound(p+1,p+1+tot,s[i].l)-p;
			s[i].r=lower_bound(p+1,p+1+tot,s[i].r)-p;
		}
		long long res=0;
		ll cot=0;
		while(1)
		{
			ll lc=cot;
			for(ll i=1;i<=4*tot;++i)tr[i].mt.minn=tr[i].mt.smin=tr[i].up.minn=tr[i].up.smin=xp();
			unordered_set<ll>d;
			for(ll i=1;i<=n;++i)minn[i]=xp(),d.insert(find(i));
			for(ll i=1;i<=n;++i)
			{
				nv res=query(1,1,tot,s[i].l,s[i].r);
				res.minn.val+=s[i].a+s[i].b;
				res.smin.val+=s[i].a+s[i].b;
				if(res.minn.col==find(i))minn[find(i)]=min(minn[find(i)],res.smin);
				else minn[find(i)]=min(minn[find(i)],res.minn);
				update(1,1,tot,s[i].l,s[i].r,xp(s[i].a-s[i].b,find(i)));
			}
			for(ll i=1;i<=4*tot;++i)tr[i].mt.minn=tr[i].mt.smin=tr[i].up.minn=tr[i].up.smin=xp();
			for(ll i=n;i;--i)
			{
				nv res=query(1,1,tot,s[i].l,s[i].r);
				res.minn.val+=s[i].a-s[i].b;
				res.smin.val+=s[i].a-s[i].b;
				if(res.minn.col==find(i))minn[find(i)]=min(minn[find(i)],res.smin);
				else minn[find(i)]=min(minn[find(i)],res.minn);
				update(1,1,tot,s[i].l,s[i].r,xp(s[i].a+s[i].b,find(i)));
			}
			for(auto it:d)
			{
				if(minn[it].col==0)continue;
				ll u=find(it),v=find(minn[it].col);
				if(u!=v)
				{
					++cot;res+=minn[it].val;
					f[u]=v;
				}
			}
			if(cot==lc)break;
		}
		if(cot!=n-1)cout<<-1<<'\n';
		else cout<<res<<'\n';
	}
}
```

---

## 作者：Arghariza (赞：1)

特殊图求最小生成树，不难想到 Boruvka 算法。该算法流程如下：

1. 初始每个点作为一个单独的连通块。
2. 对每个连通块找出连向其余连通块的边中，边权最小的一条边。

3. 枚举每个连通块，把该连通块的最小边加进生成树中。
4. 重复 2~3 操作直到连通块数不再变化，此时若连通块数为 $1$ 则找到最小生成树；否则图不连通。

由于每次进行 2~3 操作之后，连通块数至少减半，所以至多反复 $O(\log n)$ 轮。

考虑某一轮中，如何对每个连通块求出连出去的最小边。发现只需对于每个点求出其连出去的最小边。

于是问题转化为：$n$ 个点中，每个点 $u$ 有一个颜色（所在连通块） $c_u$。对于每个 $u$，求出 $\min\limits_{c_u\neq c_v\land \max(l_u,l_v)\le \min(r_u,r_v)}a_u+a_v+|b_u-b_v|$。

先按照 $b_u$ 从小到大排序，不妨设 $b_u\ge b_v$。$b_u<b_v$ 的情况再反过来做一遍即可。

然后边的权值变成了 $(a_u+b_u)+(a_v-b_v)$。

先考虑没有颜色限制怎么做。按照 $b_u$ 从小到大枚举 $u$，查询 $u$ 的前缀中区间与 $(l_u,r_u)$ 有交的 $a_v-b_v$ 的最小值。需要维护区间对 $x$ 取 $\min$，区间求 $\min$。使用带懒标记的线段树或拆成若干个单点取 $\min$ 即可。

再考虑加上颜色的限制，维护区间最小值 $\min$ 和区间次小值 $\min'$，并强制让 $\min$ 和 $\min'$ 的点的颜色不同。这样的话 $u$ 要么是取 $\min$ 要么是取 $\min'$，判断 $c_u$ 是否是 $\min$ 的点的颜色即可。

时间复杂度 $O(n\log^2 n)$。常数较大。

``````cpp
// Problem: T497952 「GFOI Round 1」Abiogenesis
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T497952
// Memory Limit: 512 MB
// Time Limit: 3500 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define eb emplace_back
#define mt make_tuple
#define mp make_pair
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
bool Mbe;

const int N = 1e5 + 5;
const int inf = 1e9;

int n, sz, fa[N];
int len, tp[N << 1];
ll res;

int gf(int x) { return x == fa[x] ? x : fa[x] = gf(fa[x]); }
void mrg(int x, int y, ll w) { if ((x = gf(x)) != (y = gf(y))) fa[x] = y, res += w, sz--; }

struct P {
	int l, r, a, b;
	P () { }
	P (int _l, int _r, int _a, int _b) :
		l(_l), r(_r), a(_a), b(_b) { }
} a[N];

struct T { 
	int x, y, cx, cy;
	T () { }
	T (int _x, int _y, int _cx, int _cy) :
		x(_x), y(_y), cx(_cx), cy(_cy) { }
};

inline T ad(T l, T r) {
	if (l.x > r.x) swap(l, r);
	if (l.y > r.x && l.cx != r.cx) l.y = r.x, l.cy = r.cx;
	else if (l.y > r.y && l.cx != r.cy) l.y = r.y, l.cy = r.cy;
	return l;
}

struct SEG {
	T t[N << 3], z[N << 3], res;
	#define ls x << 1
	#define rs x << 1 | 1
	#define m ((l + r) >> 1)
	void bld(int l, int r, int x) {
		z[x] = t[x] = T(inf, inf, 0, 0);
		if (l == r) return;
		bld(l, m, ls), bld(m + 1, r, rs);
	}
	void cov(int l, int r, int L, int R, int p, int c, int x) {
		if (R < L) return;
		t[x] = ad(t[x], T(p, inf, c, 0));
		if (L <= l && r <= R) return z[x] = ad(z[x], T(p, inf, c, 0)), void();
		if (L <= m) cov(l, m, L, R, p, c, ls);
		if (R > m) cov(m + 1, r, L, R, p, c, rs);
	}
	void qry(int l, int r, int L, int R, int x) {
		if (R < L) return;
		res = ad(res, z[x]);
		if (L <= l && r <= R) return res = ad(res, t[x]), void();
		if (L > m) return qry(m + 1, r, L, R, rs);
		if (R <= m) return qry(l, m, L, R, ls);
		qry(l, m, L, R, ls), qry(m + 1, r, L, R, rs);
	}
	void c(int l, int r, int p, int c) { cov(1, len, l, r, p, c, 1); }
	void q(int l, int r) { res = T(inf, inf, 0, 0), qry(1, len, l, r, 1); }
} S;

pi out[N];

inline void chk(pi &x, pi y) {
	x = min(x, y);
}

void bolovka() {
	for (int i = 1; i <= n; i++) fa[i] = i;
	while (1) {
		int tsz = sz;
		S.bld(1, len, 1);
		for (int i = 1; i <= n; i++) out[i] = mp(inf, 0);
		for (int i = 1; i <= n; i++) {
			int u = gf(i);
			S.q(a[i].l, a[i].r); T res = S.res;
			ll v1 = res.x + a[i].a + a[i].b, v2 = res.y + a[i].a + a[i].b;
			if (res.cx != u) chk(out[u], mp(v1, res.cx)), chk(out[res.cx], mp(v1, u));
			else if (res.cy != u) chk(out[u], mp(v2, res.cy)), chk(out[res.cy], mp(v2, u));
			S.c(a[i].l, a[i].r, a[i].a - a[i].b, gf(i));
		}
		S.bld(1, len, 1);
		for (int i = n; i; i--) {
			int u = gf(i);
			S.q(a[i].l, a[i].r); T res = S.res;
			ll v1 = res.x + a[i].a - a[i].b, v2 = res.y + a[i].a - a[i].b;
			if (res.cx != u) chk(out[u], mp(v1, res.cx)), chk(out[res.cx], mp(v1, u));
			else if (res.cy != u) chk(out[u], mp(v2, res.cy)), chk(out[res.cy], mp(v2, u));
			S.c(a[i].l, a[i].r, a[i].a + a[i].b, gf(i));
		}
		for (int i = 1; i <= n; i++) {
			if (gf(i) != i || !out[i].se) continue;
			mrg(i, out[i].se, out[i].fi);
		}
		if (tsz == sz) { res = -1; break; }
		if (sz == 1) break;
	}
}

void solve() {
	cin >> n, res = len = 0, sz = n;
	for (int i = 1, l, r, a, b; i <= n; i++)
		cin >> l >> r >> a >> b, ::a[i] = P(l, r, a, b), tp[++len] = l, tp[++len] = r;
	if (n == 1) return cout << 0 << '\n', void();
	sort(a + 1, a + n + 1, [](P &x, P &y) { return x.b < y.b; });
	sort(tp + 1, tp + len + 1), len = unique(tp + 1, tp + len + 1) - tp - 1;
	for (int i = 1; i <= n; i++) 
		a[i].l = lower_bound(tp + 1, tp + len + 1, a[i].l) - tp,
		a[i].r = lower_bound(tp + 1, tp + len + 1, a[i].r) - tp;
	bolovka();
	cout << res << '\n';
}

bool Med;
int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cerr << (&Mbe - &Med) / 1048576.0 << " MB\n";
	#ifdef FILE
		freopen(".in", "r", stdin);
		freopen(".out", "w", stdout);
	#endif
	int T = 1;
	cin >> T;
	while (T--) solve();
	cerr << (int)(1e3 * clock() / CLOCKS_PER_SEC) << " ms\n";
	return 0;
}
``````

---

## 作者：C1942huangjiaxu (赞：0)

这种类似完全图的最小生成树问题，自然还是考虑 Boruvka 算法。

简单说一下 Boruvka 算法，每轮对于每个点，找到**不在同一连通块的最小边**，然后**同一连通块选择最小的边**连出去，可以发现这样每轮连通块数量至少减半，所以最多进行 $O(\log n)$ 轮。

那么问题就在于找到不在同一连通块的最小边，这和找最小边几乎相同，因为我们只需要在记录最小值的同时，记录**不与最小值在同一连通块的次小值**即可。

考虑怎么找最小值，首先将绝对值拆开。将点按照 $b_i$ 排序，从前到后扫一次，再从后到前扫一次。

那么相当于求前缀区间有交的最小值，区间有交可以离散化后用线段树来解决，就是区间取最小值，区间查询最小值。

如果一个连通块找不到出边，就是无解。

时间复杂度 $O(n\log^2 n)$。

参考代码（用了标记永久化的写法）：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
struct node{
	int a,b,l,r;
}t[N];
int T,n,p[N],m,fa[N],to[N],tv[N],id[N];
struct val{
	int c1,c2,v1,v2;
}v1[N<<2],v2[N<<2];
int gf(int x){
	return fa[x]==x?fa[x]:fa[x]=gf(fa[x]);
}
bool cmp(int x,int y){
	return t[x].b<t[y].b;
}
inline void upd(val &x,int c,int v){
	if(!x.c1){
		x.c1=c,x.v1=v;
		return;
	}
	if(v>=x.v1){
		if(c==x.c1)return;
		if(!x.c2||v<x.v2)x.c2=c,x.v2=v;
		return;
	}
	if(c==x.c1){
		x.v1=v;
		return;
	}
	x.c2=x.c1,x.v2=x.v1;
	x.c1=c,x.v1=v;
}
#define L k<<1
#define R k<<1|1
inline void build(int k,int l,int r){
	v1[k]=v2[k]={0,0,0,0};
	if(l==r)return;
	int mid=l+r>>1;
	build(L,l,mid),build(R,mid+1,r);
}
inline void Upd(int c1,int c2,int v){
	if(!c2)return;
	if(!to[c1]||tv[c1]>v){
		to[c1]=c2;
		tv[c1]=v;
	}
}
void qry(int k,int l,int r,int x,int y,int v,int w1,int w2){
	if(x<=l&&r<=y){
		if(v2[k].c1==fa[v])Upd(fa[v],v2[k].c2,v2[k].v2+w1);
		else Upd(fa[v],v2[k].c1,v2[k].v1+w1);
		upd(v1[k],fa[v],w2);
		upd(v2[k],fa[v],w2);
		return;
	}
	if(v1[k].c1==fa[v])Upd(fa[v],v1[k].c2,v1[k].v2+w1);
	else Upd(fa[v],v1[k].c1,v1[k].v1+w1);
	upd(v2[k],fa[v],w2);
	int mid=l+r>>1;
	if(x<=mid)qry(L,l,mid,x,y,v,w1,w2);
	if(y>mid)qry(R,mid+1,r,x,y,v,w1,w2);
}
void solve(){
	scanf("%d",&n);
	m=0;
	for(int i=1;i<=n;++i){
		fa[i]=id[i]=i;
		scanf("%d%d%d%d",&t[i].l,&t[i].r,&t[i].a,&t[i].b);
		p[++m]=t[i].l;
	}
	sort(p+1,p+m+1);
	m=unique(p+1,p+m+1)-p-1;
	sort(id+1,id+n+1,cmp);
	for(int i=1,x;i<=n;++i){
		x=id[i];
		t[x].l=lower_bound(p+1,p+m+1,t[x].l)-p;
		t[x].r=upper_bound(p+1,p+m+1,t[x].r)-p-1;
	}
	int cnt=n;
	long long ans=0;
	while(cnt>1){
		for(int i=1;i<=n;++i)if(gf(i)==i)to[i]=tv[i]=0;
		build(1,1,m);
		for(int i=1;i<=n;++i){
			int x=id[i];
			qry(1,1,m,t[x].l,t[x].r,x,t[x].a+t[x].b,t[x].a-t[x].b);
		}
		build(1,1,m);
		for(int i=n;i;--i){
			int x=id[i];
			qry(1,1,m,t[x].l,t[x].r,x,t[x].a-t[x].b,t[x].a+t[x].b);
		}
		for(int i=1;i<=n;++i)if(gf(i)==i){
			if(!to[i])return puts("-1"),void();
			if(gf(i)!=gf(to[i]))fa[i]=to[i],--cnt,ans+=tv[i];
		}
	}
	printf("%lld\n",ans);
}
int main(){
	scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```

---

