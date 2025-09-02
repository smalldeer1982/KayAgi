# Little Pony and Lord Tirek

## 题目描述

Lord Tirek is a centaur and the main antagonist in the season four finale episodes in the series "My Little Pony: Friendship Is Magic". In "Twilight's Kingdom" (Part 1), Tirek escapes from Tartarus and drains magic from ponies to grow stronger.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF453E/643ac83a27b2195ea33883fd4f5562486272f6c4.png)The core skill of Tirek is called Absorb Mana. It takes all mana from a magic creature and gives them to the caster.

Now to simplify the problem, assume you have $ n $ ponies (numbered from 1 to $ n $ ). Each pony has three attributes:

- $ s_{i} $ : amount of mana that the pony has at time 0;
- $ m_{i} $ : maximum mana that the pony can have;
- $ r_{i} $ : mana regeneration per unit time.

Lord Tirek will do $ m $ instructions, each of them can be described with three integers: $ t_{i},l_{i},r_{i} $ . The instruction means that at time $ t_{i} $ , Tirek will use Absorb Mana on ponies with numbers from $ l_{i} $ to $ r_{i} $ (both borders inclusive). We'll give you all the $ m $ instructions in order, count how much mana Tirek absorbs for each instruction.

## 说明/提示

Every pony starts with zero mana. For the first instruction, each pony has 5 mana, so you get 25 mana in total and each pony has 0 mana after the first instruction.

For the second instruction, pony 3 has 14 mana and other ponies have mana equal to their $ m_{i} $ .

## 样例 #1

### 输入

```
5
0 10 1
0 12 1
0 20 1
0 12 1
0 10 1
2
5 1 5
19 1 5
```

### 输出

```
25
58
```

# 题解

## 作者：_LPF_ (赞：16)

分块信仰（

[CF453E Little Pony and Lord Tirek](https://www.luogu.com.cn/problem/CF453E)

> 给定 $n$ 个点及其初始值 $s_i$，以及最大值 $m_i$ 和增长值 $k_i$。
>
> 每个时间单位进行操作：$s_i=\min(s_i+k_i,m_i)$，同时支持区间求和并清零。

考虑分块，预处理出 $f(i,k)$ 表示第 $i$ 块从全零开始，$k$ 个单位时间后的和。

- 我们称一个块是“非限制”的，当且仅当它在某一历史时刻被清零，且从未有过单点修改。

  这些块可以利用预处理的 $f$ 快速计算贡献，并可将时间挂在最左边节点上。

- 否则称一个块是“限制”的，它只能暴力统计贡献。

一开始所有块都是“限制”的，每次修改至多将两个块变成“限制”的，所以复杂度没有问题。

预处理部分，可以利用两次前缀和达到 $O(N^2/M)$ 的复杂度，其中 $M$ 为块长。

为了避免空间爆炸，应当适当调整块长，而非一定是 $\sqrt N$，这里取 $M=400$。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long LL;
const int N = 1e5 + 10, T = 1e5;
const int M = 400, S = N / M + 10;

int n, tim[N];
int t, L[S], R[S], pos[N];
bool limit[S];
LL f[S][N], g[N], s[N], m[N], k[N];

int read(){
	int x = 0, f = 1; char c = getchar();
	while(c < '0' || c > '9') f = (c == '-') ? - 1 : 1, c = getchar();
	while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
	return x * f;
}

void Pre_Work() {
	t = n / M;
	for(int i = 1; i <= t; i ++)
		L[i] = R[i - 1] + 1, R[i] = M * i; 
	if(R[t] < n) t ++, L[t] = R[t - 1] + 1, R[t] = n;

	for(int i = 1; i <= t; i ++) {
		for(int j = L[i]; j <= R[i]; j ++)
			if(k[j]) g[1] += k[j], g[m[j] / k[j] + 1] -= k[j];
		for(int j = 1; j <= T; j ++) g[j] += g[j - 1];
		for(int j = L[i]; j <= R[i]; j ++)
			if(k[j]) g[m[j] / k[j] + 1] += m[j] % k[j];

		for(int j = 1; j <= T; j ++) g[j] += g[j - 1];
		f[i][0] = 0;
		for(int j = 1; j <= T; j ++) f[i][j] = g[j], g[j] = 0;
		
		for(int j = L[i]; j <= R[i]; j ++) pos[j] = i;
		limit[i] = true;
	}
}

LL Modify(int t, int l, int r, int nxt) {
	LL ans = 0;
	if(limit[t]) {
		for(int i = l; i <= r; i ++)
			ans += min(m[i], s[i] + k[i] * (nxt - tim[i])), s[i] = 0, tim[i] = nxt;
		return ans;
	}
	else {
		limit[t] = true; int rec = tim[L[t]];
		for(int i = l; i <= r; i ++)
			ans += min(m[i], k[i] * (nxt - rec)), s[i] = 0, tim[i] = nxt;
		for(int i = L[t]; i < l; i ++) tim[i] = rec, s[i] = 0;
		for(int i = r + 1; i <= R[t]; i ++) tim[i] = rec, s[i] = 0;
		return ans;
	}
}

LL Query(int t, int l, int r) {
	int p = pos[l], q = pos[r]; LL ans = 0;
	if(p == q) return Modify(p, l, r, t);
	ans += Modify(p, l, R[p], t) + Modify(q, L[q], r, t);
	if(p == q - 1) return ans;

	for(int i = p + 1; i <= q - 1; i ++) {
		if(!limit[i]) {
			ans += f[i][min(t - tim[L[i]], T)];
			tim[L[i]] = t;
		}
		else {
			for(int j = L[i]; j <= R[i]; j ++)
				ans += min(m[j], s[j] + k[j] * (t - tim[j]));
			tim[L[i]] = t, limit[i] = false;
		}
	}
	return ans;
}

int main() {
	n = read();
	for(int i = 1; i <= n; i ++)
		s[i] = read(), m[i] = read(), k[i] = read();
	Pre_Work();
	int q = read();
	while(q --) {
		int t = read(), l = read(), r = read();
		printf("%lld\n", Query(t, l, r));
	}
	return 0;
}
```

跑得可能比大常数的 $O(n\log^2 n)$ 的做法还快一点 QwQ。

---

## 作者：Alan_Zhao (赞：12)

## CF453E 题解

终于过了这题，写篇题解纪念一下。

### 思路

考虑颜色段均摊的做法，用一个 set 维护被更改的时间相同的颜色段。

由于只有区间赋值操作，且查询后立即赋值，所以每个颜色段只会对后面的一次查询产生影响。而且每次赋值只会增加 $O(1)$ 个颜色段，所以总的颜色段数量是 $O(m)$ 级别的。

我们对于整体建立两棵可持久化权值线段树（主席树），一棵在相应的 $\frac{m_i}{r_i}$ 处存 $r_i$ 的和，另一棵存 $m_i$ 的和。

对于一个 $(l,r,t)$ 的询问，将 $[l,r]$ 通过 set 中的颜色段分成一些区间，每个区间内被修改的时间相同。

- 假如一个区间没有被修改过（也就意味着它有初值）：直接暴力算即可。

- 假如一个区间被修改过，且上次修改的时间为 $t_0$：此时初值对答案已经没有影响了，所以显然当小马的 $\frac{m_i}{r_i}<t-t_0$ 时，答案会加上 $m_i$；当小马的 $\frac{m_i}{r_i}\ge t-t_0$ 时，答案会加上 $(t-t_0)r_i$。对于这两种情况在主席树上查询即可。

然后还有一些代码的细节问题，导致我调了好几个小时。

时间复杂度 $O((n+m)\log n)$。

### 代码

```cpp
#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <set>
using namespace std;
#define For(Ti,Ta,Tb) for(int Ti=(Ta);Ti<=(Tb);++Ti)
#define Dec(Ti,Ta,Tb) for(int Ti=(Ta);Ti>=(Tb);--Ti)
template<typename T>
inline bool chkmax(T &i,const T&j){return i<j?(i=j,1):0;}
template<typename T>
inline bool chkmin(T &i,const T&j){return i>j?(i=j,1):0;}
template<typename T> void Read(T &x){
	x=0;int f=1;
	char ch=getchar();
	while(!isdigit(ch)) f=(ch=='-'?-1:f),ch=getchar();
	while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
	x=x*f;
}
typedef long long ll;
#define INF 0x3f3f3f3f
const int N=1e5+5,SIZ=1e7+5,V=1e5+5;
int n,s[N],mx[N],r[N];
#define ls(xx) t[xx].ls
#define rs(xx) t[xx].rs
int tot=0,root[N],root1[N];
struct Node{
	int l,r,ls,rs;ll v;
}t[SIZ];
void Pushup(int p){t[p].v=t[ls(p)].v+t[rs(p)].v;}
void Build(int p,int l,int r){//建立一棵空的主席树
	t[p].l=l,t[p].r=r;
	if(t[p].l==t[p].r) return;
	int mid=(l+r)>>1;
	Build(ls(p)=++tot,l,mid);Build(rs(p)=++tot,mid+1,r);
}
int Add(int p,int x,ll k){//在上一个版本的基础上进行单点修改
	int np=++tot;t[np]=t[p];
	if(t[np].l==t[np].r){
		t[np].v+=k;return np;
	}int mid=(t[np].l+t[np].r)>>1;
	if(x<=mid) ls(np)=Add(ls(p),x,k);
	else rs(np)=Add(rs(p),x,k);
	Pushup(np);return np;
}
ll QLe(int p,int x){//查找主席树中≤x的和
	if(t[p].r<=x) return t[p].v;
	int mid=(t[p].l+t[p].r)>>1;ll res=0;
	if(ls(p)) res+=QLe(ls(p),x);
	if(x>mid) res+=QLe(rs(p),x);
	return res;
}
ll QGe(int p,int x){//查找主席树中≥x的和
	if(t[p].l>=x) return t[p].v;
	int mid=(t[p].l+t[p].r)>>1;ll res=0;
	if(x<=mid) res+=QGe(ls(p),x);
	if(rs(p)) res+=QGe(rs(p),x);
	return res;
}
struct Seg{//orig用来存区间是否有初值（是否被区间赋值过），lst记录区间上次被修改的时间
	int l,r,orig,lst;
};
bool operator<(const Seg &x,const Seg &y){
	return x.l<y.l;
}
typedef set<Seg>::iterator Iter;
set<Seg> st;
ll Bf(const Seg &it,int t){//暴力
	ll res=0;
	For(i,it.l,it.r){
		res+=min(1LL*mx[i],s[i]+1LL*(t-it.lst)*r[i]);
		s[i]=0;
	}return res;
}
ll Qry(const Seg &it,int t){
	if(it.orig) return Bf(it,t);
	t-=it.lst;
	return 1LL*t*(QGe(root1[it.r],t)-QGe(root1[it.l-1],t))+QLe(root[it.r],t-1)-QLe(root[it.l-1],t-1);
}
int m;
int main(){
	Read(n);
	root[0]=tot=1;t[tot].l=0,t[tot].r=V;
	Build(root[0],0,V);
	root1[0]=++tot;t[tot].l=0,t[tot].r=V;
	Build(root1[0],0,V);
	For(i,1,n){
		Read(s[i]);Read(mx[i]);Read(r[i]);
		if(r[i]==0){//对于r[i]==0的情况要特判
			root[i]=Add(root[i-1],0,0);
			root1[i]=Add(root1[i-1],0,0);
			continue;
		}
		root[i]=Add(root[i-1],mx[i]/r[i],mx[i]);
		root1[i]=Add(root1[i-1],mx[i]/r[i],r[i]);
	}
	Read(m);
	st.insert(Seg{1,n,1,0});
	int t=0,l,r;
	while(m--){
		Read(t);Read(l);Read(r);
		ll ans=0;
		Iter it1=--st.upper_bound(Seg{l,0,0,0}),it2=--st.upper_bound(Seg{r,0,0,0});
		if(it1==it2){//l,r在set内处于同一个区间
			ans+=Qry(Seg{l,r,it1->orig,it1->lst},t);
			Seg is=*it1;
			st.erase(it1);
			if(l!=is.l) st.insert(Seg{is.l,l-1,is.orig,is.lst});
			st.insert(Seg{l,r,0,t});
			if(r!=is.r) st.insert(Seg{r+1,is.r,is.orig,is.lst});
		}else{
			ans+=Qry(Seg{l,it1->r,it1->orig,it1->lst},t);
			Seg is1=*it1,is2=*it2;
			for(Iter it=st.erase(it1);it!=it2&&it!=st.end();it=st.erase(it)){
				ans+=Qry(*it,t);
			}
			ans+=Qry(Seg{it2->l,r,it2->orig,it2->lst},t);
			st.erase(it2);
			if(is1.l<=l-1) st.insert(Seg{is1.l,l-1,is1.orig,is1.lst});
			if(is2.r>=r+1) st.insert(Seg{r+1,is2.r,is2.orig,is2.lst});
			st.insert(Seg{l,r,0,t});
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```



---

## 作者：yzy1 (赞：10)

## 题目大意

- 维护一个长度为 $n(1\le n \le 10^5)$ 的数组 $s$，初值给定且 $0 \le s_i \le 10^5$。
- 每过 $1$ 单位时间，都会对于所有 $[1,n]$ 之间的整数 $i$，执行 $s_i \gets \min\{m_i,s_i+r_i\}$。其中 $m_i$ 和 $r_i$ 给定且 $0 \le m_i, r_i \le 10^5$。
- 维护 $m(1\le m \le 10^5)$ 次操作，每次操作时会将时间设为 $t(0 \le t \le 10^9)$，并且查询 $s$ 数组 $[l,r]$ 区间和。每次操作结束后会将 $s$ 数组的 $[l,r]$ 区间推平为 $0$，保证每次询问的 $t$ 严格递增。
- 初始没有进行操作时时间为 $0$。

## 简要做法

题解区里好像都是些神奇 polylog 做法，我这里讲一个比较好想的根号做法吧。

首先对 $s$ 序列分块，对于每一块维护一个推平 tag 和这个块上次被操作的时间戳。查询时分三种情况：

- 对于散块，直接暴力做。
- 对于没有推平 tag 的整块，同散块一样暴力加和，然后把这个块打上一个推平 tag。
- 对于有推平 tag 的整块，我们需要一个 $O(1)$ 的方法来求出它的答案，具体方法下面再说。

容易发现，由于每次查询都会做一次区间推平，即每次操作均摊下来只会修改 $O(1)$ 个块的 tag。所以这个做法时间复杂度均摊 $O(n\sqrt n)$。

现在的问题是怎么让第三种情况 $O(1)$ 计算贡献。考虑在最开始的时候对所有块进行预处理：假设这个块在时间戳为 $0$ 的时候区间推平为 $0$，预处理出该块在时间戳 $k$ 的时候的区间和 $pre(\text{block},k)$。注意到 $k$ 没有必要取到 $10^9$ 级别，因为题目保证 $0\le s_i,m_i,r_i \le 10^5$，即该块在推平后 $10^5$ 个单位时间后区间和就不会变了。

然后你会发现如果你对 $[0,10^5]$ 之间的每个时间戳都暴力计算每个块的贡献，复杂度将退化为 $O(n^2)$。换一种方法，考虑每个元素对于不同时间戳的贡献。我们发现，对于元素 $(s_i,m_i,r_i)$，在第 $\left\lfloor\dfrac {m_i} {r_i} \right\rfloor$ 单位时间或之前，该元素贡献为 $r_i$，在第 $\left\lfloor\dfrac {m_i} {r_i} \right\rfloor+1$ 单位时间，该元素贡献为 $m_i \bmod r_i$，之后该元素贡献都为 $0$。考虑维护 $pre(\text{block},k)$ 的差分的差分，此时每个元素只会对差分的差分改变至多三个数。对于块内所有元素都计算出贡献后，做两遍前缀和，就能得到原数组。时间复杂度下降为 $O(n\sqrt n)$。

## 代码参考

```cpp
const int N=1e5+9;
const int B=409;
struct Node{int mx,dl;}a[N];
int n,sz,bl[N],lbl[N],rbl[N],pre[B][N],tim[B],c[N];
bool typ[B];

void Init(){
  sz=min<int>(sqrt(n),250);
  re(i,n)bl[i]=(i-1)/sz+1,lbl[i]=(bl[i]-1)*sz+1,rbl[i]=min(bl[i]*sz,n);
  static int cnt[N],lst[N],qzh[N];
  ste(x,1,n,sz){
    int b=bl[x];
    memset(qzh,0,sizeof qzh);
    rep(i,lbl[x],rbl[x])if(a[i].dl)
      cnt[i]=a[i].mx/a[i].dl,lst[i]=a[i].mx%a[i].dl,qzh[1]+=a[i].dl,qzh[cnt[i]+1]-=a[i].dl-lst[i],qzh[cnt[i]+2]-=lst[i];
    re(t,1e5)qzh[t]+=qzh[t-1];
    re(t,1e5)qzh[t]+=qzh[t-1],pre[b][t]=qzh[t];
  }
}

void Down(int t,int x){
  int b=bl[x];
  if(typ[b]){
    typ[b]=0;
    rep(i,lbl[x],rbl[x])c[i]=0;
  }
  int delt=min<int>(1e5,t-tim[b]);
  rep(i,lbl[x],rbl[x])c[i]=min<ll>(a[i].mx,1ll*delt*a[i].dl+c[i]);
  tim[b]=t;
}

ll Ask(int t,int l,int r){
  ll res=0;
  if(bl[l]==bl[r]){
    Down(t,l);
    rep(i,l,r)res+=c[i],c[i]=0;
    return res;
  }
  res+=Ask(t,l,rbl[l]);
  ste(i,lbl[l]+sz,rbl[r]-sz,sz){
    int b=bl[i],delt=min<int>(1e5,t-tim[b]);
    if(typ[b])res+=pre[b][delt];
    else res+=Ask(t,lbl[i],rbl[i]);
    typ[b]=1,tim[b]=t;
  }
  res+=Ask(t,lbl[r],r);
  return res;
}

signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin>>n;re(i,n)cin>>c[i]>>a[i].mx>>a[i].dl;
  Init();
  int m;cin>>m;while(m--){
    int t,l,r;cin>>t>>l>>r;
    ll res=Ask(t,l,r);
    cout<<res<<'\n';
  }
  return 0;
}
```



---

## 作者：Owen_codeisking (赞：9)

想了一个乱搞做法写了一个晚上……写篇题解纪念一下逝去的一个晚上……

### `FBI WARNING: Please don't imitate.`

我们预处理出每个位置的数需要多少时间达到满魔力值，先称为 $b$ 吧。若 $r=0$, $b=+\infty$

因为有区间清零操作，所以我们对初始值为 $s$ 和 $0$ 都需要做一次。

如果一个位置是在 $t_0$ 被清零的，它需要 $b$ 秒达到满魔力值，我们可以知道在 $[t,t+b)$ 这段时间内是没满的，$[t+b,+\infty)$ 是满的。

如果一个段 $t_0$ 相同，我们是可以在主席树讨论一下 $\log n$ 得到的。

那么解法就很暴力了吧……用 $\text{ODT}$ + 主席树可以得到看似 $O(n\log^2 n)$ 的解法。

后来我发现居然是 $O(n\log n)$ 的！

下面是复杂度分析：

你一次操作最多增加两个 $t_0$ 相同的段，每次遍历完 $[l,r]$ 中相同的段后会把这些段删掉，所以最多会有 $2\times n$ 次询问，时间复杂度 $O(n\log n)$

$Code\ Below:$

```cpp
// Why always UKE???
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=100000+10;
const int inf=0x3f3f3f3f;
int n,m,S[maxn],M[maxn],R[maxn],b[maxn],c[maxn];ll sumM[maxn];

#define pll pair<ll,ll>
inline pll operator + (pll a,pll b) {return make_pair(a.first+b.first,a.second+b.second);}

struct CM
{
    int op,rt[maxn],ls[maxn*20],rs[maxn*20],sz;
    ll val[maxn*20],sum[maxn*20],w[maxn*20];
    void update(int &x,int y,int l,int r,int pos,int p)
    {
        x=++sz;ls[x]=ls[y];rs[x]=rs[y];val[x]=val[y]+R[p];sum[x]=sum[y]+M[p]-((op==0)?S[p]:0);
        if(l == r) return ;
        int mid=(l+r)>>1;
        if(pos <= mid) update(ls[x],ls[y],l,mid,pos,p);
        else update(rs[x],rs[y],mid+1,r,pos,p);
    }
    pll query(int u,int v,int L,int R,int l,int r)
    {
        if(L <= l && r <= R) return make_pair(val[v]-val[u],sum[v]-sum[u]);
        int mid=(l+r)>>1;pll ans=make_pair(0,0);
        if(L <= mid) ans=ans+query(ls[u],ls[v],L,R,l,mid);
        if(R > mid) ans=ans+query(rs[u],rs[v],L,R,mid+1,r);
        return ans;
    }
}T[2];

struct node
{
    int l,r,val;
    node(int _l=0,int _r=0,int _val=0):l(_l),r(_r),val(_val){}
};
set<node> s;
inline bool operator < (const node &a,const node &b) {return a.l<b.l;}
#define IT set<node>::iterator
inline IT split(int x)
{
    IT it=s.lower_bound(node(x));
    if(it!=s.end()&&it->l==x) return it;
    it--;
    int l=it->l,r=it->r,val=it->val;
    s.erase(it);
    s.insert(node(l,x-1,val));
    return s.insert(node(x,r,val)).first;
}
inline ll ask(int t,int x,int y)
{
    IT R=split(y+1),L=split(x);
    int l,r,val;ll ans=sumM[y]-sumM[x-1];pll res;
    for(IT it=L;it!=R;it++)
    {
        l=it->l;r=it->r;val=it->val;
        if(val==0) res=T[0].query(T[0].rt[l-1],T[0].rt[r],min(100001,t-val+1),100001,0,100001);
        else res=T[1].query(T[1].rt[l-1],T[1].rt[r],min(100001,t-val+1),100001,0,100001);
        ans+=res.first*(t-val)-res.second;
    }
    s.erase(L,R);
    s.insert(node(x,y,t));
    return ans;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d%d",&S[i],&M[i],&R[i]);
    for(int i=1;i<=n;i++)
    {
        b[i]=(R[i]==0)?100001:(M[i]-S[i])/R[i]+((M[i]-S[i])%R[i]>0);
        c[i]=(R[i]==0)?100001:M[i]/R[i]+(M[i]%R[i]>0);
        sumM[i]=sumM[i-1]+M[i];
    }
    T[0].op=0;T[1].op=1;
    for(int i=1;i<=n;i++) T[0].rt[i]=T[0].rt[i-1],T[0].update(T[0].rt[i],T[0].rt[i],0,100001,b[i],i);
    for(int i=1;i<=n;i++) T[1].rt[i]=T[1].rt[i-1],T[1].update(T[1].rt[i],T[1].rt[i],0,100001,c[i],i);
    s.insert(node(1,n,0));s.insert(node(n+1,n+1,0));
    scanf("%d",&m);
    int t,l,r;
    while(m--)
    {
        scanf("%d%d%d",&t,&l,&r);
        printf("%I64d\n",ask(t,l,r));
    }
    return 0;
}
```

---

## 作者：Leap_Frog (赞：6)

### P.S.
前情回顾：  
去年 9 月份，@[$\color{gray}\text{leapfrog}$](https://www.luogu.com.cn/user/44805) 刚学 Chtholly Tree，Chtholly 没什么好题，都被毒瘤初题人卡光了。  
这句话被经过的 @[$\color{black}\text{F}\color{red}\text{lying2018}$](https://www.luogu.com.cn/user/52902) 神仙听到了，就给 @[$\color{gray}\text{leapfrog}$](https://www.luogu.com.cn/user/52902) 推了这道神仙题。  
然后菜菜的 @[$\color{gray}\text{leapfrog}$](https://www.luogu.com.cn/user/44805) 不会做，只能加入收藏计划。  
当时还是黑题，现在回来一看，发现紫了，@[$\color{gray}\text{leapfrog}$](https://www.luogu.com.cn/user/44805) 看了题解才会做。  
~~求赞~~

### Description.
有 $n$ 个数，每秒第 $i$ 个数 $x_i$ 会变成 $\min(m_{i},x_i+k_i)$。  
每次操作询问区间和，并把区间 $x_i$ 清零。  

### Solution.
我们考虑一个子问题，每次操作都针对整个序列。  
我们可以按照 $x_i$ 是否等于 $m_i$ 分类。  
$x_i$ 等于 $m_i$ 的一类，我们可以直接统计区间 $m_i$ 和。  
$x_i$ 不等于 $m_i$ 的一类，我们直接统计区间 $k_i$ 和，乘上时间差就好了。  
问题是怎么分类。~~这不是有手就行~~  
按照 $\frac{m_i}{k_i}$ 排序，然后每次肯定是一个前缀 $x_i$ 不等于 $m_i$，后缀都等于。  
直接二分找到第一个 $k_i=x_i$ 的位置。  
然后前缀和计算 $\sum k_i$，后缀和计算 $\sum m_i$ 即可。  

但是现在是对某个子区间进行操作。  
我们并不能对整个序列排序求前缀和。  
我们现在相当于要求 $\frac{m_i}{k_i}\le qwq,pos\in[l,r]$ 的所有 $k_i$ 和。  
我们可以按照 $\frac{m_i}{k_i}$ 排序并离散化，然后一位一位加入主席树。  
这样就相当于查询主席树上一个前缀的和了。  
这边还有一个 tips，就是一颗主席树可以同时维护那两个值。  

还有另外一个问题，就是因为修改并不对于整个序列。  
所以每次询问所有的上一次时间是不一定一样的。  
而上一次时间是决定了某一个数应该贡献入 $k$ 还是 $m$ 的。  
相当于上面的 $qwq$ 和上一次时间是有关系的。  
所以我们只能暴力维护，直接上 Chtholly Tree。  
而因为这题每次询问之后会对询问区间区间覆盖，所以 Chtholly Tree 时间复杂度正确。  
证明就考虑，每次修改至多多 $O(1)$ 个区间，每次查询遍历到的所有区间都会被删除。  
所以时间复杂度正确。  

这边还有一个小 tips，有些小马初始有权值，可以当做上一次修改是负时间。  

### Coding.
```cpp
//是啊……你就是那只鬼了……所以被你碰到以后，就轮到我变成鬼了{{{
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	if(f) x=-x;
}/*}}}*/
int n,Q,K[100005],M[100005],id[100005];
struct data{ll k,b;inline data operator+(data x) const {return(data){k+x.k,b+x.b};}};
struct node{int ls,rs;data vl;}T[2000005];int tt,rt[100005];
inline void pushup(int x) {T[x].vl=T[T[x].ls].vl+T[T[x].rs].vl;}
inline void build(int &x,int l,int r)
{
	int md=(l+r)>>1;x=++tt;if(l==r) return T[x].vl=(data){K[l],0},void();
	build(T[x].ls,l,md),build(T[x].rs,md+1,r),pushup(x);
}
inline void modif(int &x,int y,int l,int r,int dw)
{
	T[x=++tt]=T[y];if(l==r) return T[x].vl=(data){0,M[l]},void();
	if(dw<=((l+r)>>1)) modif(T[x].ls,T[y].ls,l,(l+r)>>1,dw),pushup(x);
	else modif(T[x].rs,T[y].rs,((l+r)>>1)+1,r,dw),pushup(x);
}
inline data query(int x,int l,int r,int dl,int dr)
{
	if(l>dr||dl>r) return(data){0,0};else if(dl<=l&&r<=dr) return T[x].vl;
	return query(T[x].ls,l,(l+r)>>1,dl,dr)+query(T[x].rs,((l+r)>>1)+1,r,dl,dr);
}
struct Chtholly{int l,r;mutable double v;char operator<(Chtholly b) const {return l<b.l;}};
typedef set<Chtholly>::iterator IT;set<Chtholly>S;
inline IT split(int wh)
{
	IT it=S.lower_bound((Chtholly){wh,114,514});
	if(it!=S.end()&&it->l==wh) return it;else it--;
	int l=it->l,r=it->r;double v=it->v;S.erase(it);
	return S.insert((Chtholly){l,wh-1,v}),S.insert((Chtholly){wh,r,v}).first;
}
inline data calc(double vl,int l,int r)
{
	int le=1,ri=n,rs=0;
	while(le<=ri) {int md=(le+ri)>>1;if(M[id[md]]<=vl*K[id[md]]) rs=md,le=md+1;else ri=md-1;}
	return query(rt[rs],1,n,l,r);
}
set<pair<int,int> >s;
inline char cmp(int a,int b) {return 1ll*M[a]*K[b]<1ll*M[b]*K[a];}
int main()
{
	read(n);for(int i=1,x;i<=n;i++)
	{
		read(x),read(M[i]),read(K[i]),id[i]=i;
		if(!M[i]&&!K[i]) M[i]=1;
		if(K[i]) S.insert((Chtholly){i,i,-1.0*x/K[i]});
		else S.insert((Chtholly){i,i,0}),s.insert(make_pair(i,x));
	}
	s.insert(make_pair(n+1,0)),build(rt[0],1,n),sort(id+1,id+n+1,cmp);
	for(int i=1;i<=n;i++) modif(rt[i],rt[i-1],1,n,id[i]);
	for(read(Q);Q--;)
	{
		set<pair<int,int> >::iterator it;int t,l,r;ll res=0;read(t),read(l),read(r);
		while(s.size()>1ull&&(it=s.lower_bound(make_pair(l,0)))->first<=r) res+=it->second,s.erase(it);
		IT ir=split(r+1),il=split(l);for(IT i=il;i!=ir;i++)
			{data x=calc(t-i->v,i->l,i->r);res+=x.b+(ll)(x.k*(t-i->v)+0.5);}
		S.erase(il,ir),S.insert((Chtholly){l,r,1.0*t}),printf("%lld\n",res);
	}
	return 0;
}
```

---

## 作者：tzc_wk (赞：4)

[Codeforces 题目传送门](https://codeforces.com/contest/453/problem/E) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF453E)

一道难度 *3100 的 DS，而且被我自己搞出来了！

不过我终究还是技不如人，因为这是一个 $n\log^2n$ + 大常数的辣鸡做法，几乎是卡着时空限制过去的……

首先注意到对于每个小马，在任意时刻它的法力值只有三种可能：

- $s_i+kr_i(k\in\mathbb{Z})$
- $kr_i(k\in\mathbb{Z})$
- $m_i$

我们考虑对这三种情况一一分析，对于第一种情况这里的 $k$ 只可能等于我们待查询的 $t$，并且这种情况可能发生当且仅当 $i$ 没有被清空过，并且 $s_i+kr_i\le m_i$，第二个条件好办，我们如果设 $a_i=\lfloor\dfrac{m_i-s_i}{r_i}\rfloor$（如果 $r_i=0$ 那么 $a_i=\infty$），那么 $i$ 符合第二个条件当且仅当 $a_i\ge t$，第一个条件虽然看起来棘手，但是我们可以维护一个 `set` 表示没有被清空过的集合，每次进行查询操作就将这个 `set` 中属于 $[l,r]$ 的元素全部删除，不难发现每个数最多被删除一次，因此复杂度是 $n\log n$ 的。接下来问题就转化为如何维护这个值，显然它可以转化为 $\sum\limits_{i=l}^r[a_i\ge t]s_i+t\sum\limits_{i=l}^r[a_i\ge t]r_i$，两部分结构类似，因此维护方法也类似，注意到这里涉及两维，$i\in[l,r]$ 和 $a_i\ge t$，那么该操作相当于查询矩形 $(l,a_i),(r,\infty)$ 中权值的和，这个离散化+建立二维线段树就可以搞定了，具体来说先将所有 $(i,a_i)$ 看作一个点并更新其在二维线段树上的权值，每次我们将一个数从 `set` 中删除就将对应的 $(i,a_i)$ 的贡献撤销掉，正确性显然。

搞清楚这个情况后，我们也可以顺带着把 $i$ 没有被清空过的贡献都搞清楚，若 $i$ 没有被清空过，可以分两种情况，$a_i\ge t$ 那么贡献为 $s_i+tr_i$，这个刚刚已经探究过了，$a_i<t$ 那么贡献为 $m_i$，不难发现这个也可以写成矩形和的形式，同样二维线段树维护即可，这里就不再赘述了。

$i$ 没有被清空过的情况搞清楚了，接下来考虑 $i$ 被清空过的情况，显然对于一个被清空过的 $i$ 它都有一个上次被清空的时间 $T_i$，在这 $t-T_i$ 分钟内它的法力值最多可以上涨 $r_i(t-T_i)$，那么它的贡献就是 $\min(m_i,r_i(t-T_i))$，还是按照之前的套路，记 $b_i=\lfloor\dfrac{m_i}{r_i}\rfloor$，还是分两种情况，若 $b_i\ge t-T_i$，那么贡献为 $r_i(t-T_i)$，否则贡献为 $m_i$，这样还是不好做，因为这里的 $T_i$ 都是互不相同的，无法直接维护。不过不难发现一个性质，那就是任意时刻 $T_i$ 都是成段分布的，也就是说相同的 $T_i$ 都是一段一段的，我们记三元组 $(l,r,t)$ 表示 $\forall i\in[l,r],T_i=t$，我们考虑开一个 `set` 维护所有三元组并对每个三元组计算贡献——这个就可以按照上面的套路二维线段树了，相信如果理解了前面的部分那这边应该的相当容易的。我们还可以发现所有计算过贡献的三元组 $(l',r',t')$ 必定满足 $l\le l'\le r'\le r$，这样的三元组在查询过后都会从 `set` 中删除，标准的 ODT 模型，按照 P4690 [Ynoi2016] 镜中的昆虫 的套路 维护即可。

时间复杂度 $n\log^2n$，由于要维护五个二维线段树，常数巨大，但还好卡过去了（（（

最后说一句，wtm 不是 sb，又拿未去重的数组离散化，话说[恰好一年前的今天](https://www.cnblogs.com/ET2006/p/12731774.html)也犯过这个错误来着的？

```cpp
const int MAXN=1e5;
const int MAXP=MAXN*20;
const int INF=0x3f3f3f3f;
int n,s[MAXN+5],r[MAXN+5],mx[MAXN+5],lim1[MAXN+5],lim2[MAXN+5];
int key1[MAXN+5],key2[MAXN+5],uni1[MAXN+5],uni2[MAXN+5],num1=0,num2=0;
struct seg2d{
	struct node{int ch[2];ll sum;} s[MAXP+5];
	int rt[MAXN+5],ncnt;
	seg2d(){ncnt=0;memset(rt,0,sizeof(rt));}
	void add_in(int &k,int l,int r,int x,int v){
		if(!k) k=++ncnt;s[k].sum+=v;
		if(l==r) return;int mid=l+r>>1;
		if(x<=mid) add_in(s[k].ch[0],l,mid,x,v);
		else add_in(s[k].ch[1],mid+1,r,x,v);
	}
	ll query_in(int k,int l,int r,int ql,int qr){
		if(ql>qr||!k) return 0;int mid=l+r>>1;
		if(ql<=l&&r<=qr) return s[k].sum;
		if(qr<=mid) return query_in(s[k].ch[0],l,mid,ql,qr);
		else if(ql>mid) return query_in(s[k].ch[1],mid+1,r,ql,qr);
		else return query_in(s[k].ch[0],l,mid,ql,mid)+query_in(s[k].ch[1],mid+1,r,mid+1,qr);
	}
	void add_out(int x,int p,int v){
		for(int i=x;i<=n;i+=(i&(-i))) add_in(rt[i],1,max(num1,num2),p,v);
	}
	ll query_out(int x,int l,int r){
		ll ret=0;
		for(int i=x;i;i&=(i-1)) ret+=query_in(rt[i],1,max(num1,num2),l,r);
		return ret;
	}
	ll query(int l1,int r1,int l2,int r2){return query_out(r1,l2,r2)-query_out(l1-1,l2,r2);}
} t_s,t_r,t_m,T_r,T_m;
set<int> fst;
struct event{
	int l,r,t;
	event(int _l=0,int _r=0,int _t=0):l(_l),r(_r),t(_t){}
	bool operator <(const event &rhs) const{return l<rhs.l;}
};
set<event> st;
void split(int x){
	if(st.empty()) return;
	set<event>::iterator it=st.lower_bound(event(x+1,0,0));
	if(it==st.begin()) return;
	--it;event val=*it;if(val.r<=x) return;
	st.erase(st.find(val));
	st.insert(event(val.l,x,val.t));
	st.insert(event(x+1,val.r,val.t));
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d%d",&s[i],&mx[i],&r[i]);
	for(int i=1;i<=n;i++){
		if(r[i]){
			lim1[i]=mx[i]/r[i];
			lim2[i]=(mx[i]-s[i])/r[i];
		} else lim1[i]=lim2[i]=INF;
	}
	for(int i=1;i<=n;i++) key1[i]=lim1[i],key2[i]=lim2[i];
	sort(key1+1,key1+n+1);sort(key2+1,key2+n+1);key1[0]=-INF;key2[0]=-INF;
	for(int i=1;i<=n;i++) if(key1[i-1]!=key1[i]) uni1[++num1]=key1[i];
	for(int i=1;i<=n;i++) if(key2[i-1]!=key2[i]) uni2[++num2]=key2[i];
	for(int i=1;i<=n;i++){
		lim1[i]=lower_bound(uni1+1,uni1+num1+1,lim1[i])-uni1;//remember to unique
		lim2[i]=lower_bound(uni2+1,uni2+num2+1,lim2[i])-uni2;
//		printf("%d %d\n",lim1[i],lim2[i]);
	}
	for(int i=1;i<=n;i++) fst.insert(i);
	for(int i=1;i<=n;i++){
		t_s.add_out(i,lim2[i],s[i]);
		t_r.add_out(i,lim2[i],r[i]);
		t_m.add_out(i,lim2[i],mx[i]);
	} int qu;scanf("%d",&qu);
	while(qu--){
		int t,L,R;scanf("%d%d%d",&t,&L,&R);
		int pos=lower_bound(uni2+1,uni2+num2+1,t)-uni2;
		ll sums=t_s.query(L,R,pos,num2);
		ll sumr=t_r.query(L,R,pos,num2);
		ll summ=t_m.query(L,R,1,pos-1);
//		printf("%d %lld %lld %lld\n",pos,sums,sumr,summ);
//		printf("%lld\n",summ+sums+sumr*t);
		ll sum=summ+sums+sumr*t;
		if(L!=1) split(L-1);split(R);
		while(1){
			set<event>::iterator it=st.lower_bound(event(L,0,0));
			if(it==st.end()||(it->l)>R) break;event val=*it;
			int pp=lower_bound(uni1+1,uni1+num1+1,t-val.t)-uni1;
			ll ssumr=T_r.query(val.l,val.r,pp,num1);
			ll ssumm=T_m.query(val.l,val.r,1,pp-1);
//			printf("%d %d %d %d\n",val.l,val.r,t-val.t,pp);
//			printf("%lld %lld\n",ssumr,ssumm);
			sum+=ssumm+ssumr*(t-val.t);st.erase(st.find(val));
		} st.insert(event(L,R,t));
		while(1){
			set<int>::iterator it=fst.lower_bound(L);
			if(it==fst.end()||(*it)>R) break;
			int x=(*it);
			t_s.add_out(x,lim2[x],-s[x]);
			t_r.add_out(x,lim2[x],-r[x]);
			t_m.add_out(x,lim2[x],-mx[x]);
			T_r.add_out(x,lim1[x],r[x]);
			T_m.add_out(x,lim1[x],mx[x]);
			fst.erase(fst.find(x));
		} printf("%lld\n",sum);
	}
	return 0;
}
/*
10
0 4 2
0 3 0
0 96 7
0 25 9
0 90 4
0 93 5
0 87 3
0 58 3
0 65 8
0 30 0
10
3 3 4
10 1 7
11 8 9
19 4 9
28 3 10
33 5 10
38 4 5
45 5 7
48 5 9
58 1 4
*/
```



---

## 作者：do_while_true (赞：3)

可能我比较蠢，一看到题解区里写的 polylog 的描述就头大，于是编了个思路比较简单的做法。

先上个 set 维护颜色段，初始的那个特殊处理一下。现在问题变成了 $\mathcal{O}(n+m)$ 次询问初始全 $0$，区间 $[l,r]$ 在时间 $k$ 时候的和，差分成 $[1,r]$ 的减去 $[1,l-1]$ 的。

扫描线扫序列维，在时间维上每次就是一个等差数列加和一个区间加。然后询问一个单点的和。对差分数组就是一个 区间加 前缀和 问题，上线段树就行。时间复杂度 $\mathcal{O}((n+m)\log m)$．

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<random>
#include<assert.h>
#include<set>
#define pb emplace_back
#define mp make_pair
#define fi first
#define se second
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n';
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n';
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef pair<ll,int>pli;
typedef pair<ll,ll>pll;
typedef pair<int,ll>pil;
typedef vector<int>vi;
typedef vector<ll>vll;
typedef vector<pii>vpii;
typedef vector<pil>vpil;
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
template<typename T>T cmin(T &x, T y){return x=x<y?x:y;}
template<typename T>
T &read(T &r){
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	return r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x,T2& ...y){read(x);read(y...);}
const int mod=998244353;
inline void cadd(int &x,int y){x=(x+y>=mod)?(x+y-mod):(x+y);}
inline void cdel(int &x,int y){x=(x-y<0)?(x-y+mod):(x-y);}
inline int add(int x,int y){return (x+y>=mod)?(x+y-mod):(x+y);}
inline int del(int x,int y){return (x-y<0)?(x-y+mod):(x-y);}
const int N=100010;
const int M=100000;
int n,m;
int chu[N],lim[N],dt[N];
ll ans[N];
struct Node{
	int l,r,c;
	bool operator<(const Node &y)const{
		return l==y.l?r<y.r:l<y.l;
	}
};
set<Node>S;
auto split(int pos){
	if(pos==n+1)return S.end();
	auto it=S.lower_bound({pos,0,0});
	if(it->l==pos)return it;
	--it;
	int L=it->l,R=it->r,C=it->c;
	S.erase(it);
	S.insert({L,pos-1,C});
	return S.insert({pos,R,C}).fi;
}
vpii vec[N];
#define ls (x<<1)
#define rs ((x<<1)|1)
struct SGT{
	ll sum,tag;
}tree[N<<2];
inline void pushup(int x){
	tree[x].sum=tree[ls].sum+tree[rs].sum;
}
inline void pushdown(int x,int l,int r){
	if(tree[x].tag){
		ll p=tree[x].tag,mid=(l+r)>>1;tree[x].tag=0;
		tree[ls].sum+=(mid-l+1)*p;tree[rs].sum+=(r-mid)*p;
		tree[ls].tag+=p;tree[rs].tag+=p;
	}
}
void modify(int x,int tl,int tr,int l,int r,ll v){
	if(tl>=l&&tr<=r){
		tree[x].sum+=(tr-tl+1)*v;
		tree[x].tag+=v;
		return ;
	}
	int mid=(tl+tr)>>1;pushdown(x,tl,tr);
	if(mid>=l)modify(ls,tl,mid,l,r,v);
	if(mid<r)modify(rs,mid+1,tr,l,r,v);
	pushup(x); 
}
ll query(int x,int tl,int tr,int l,int r){
	if(tl>=l&&tr<=r)return tree[x].sum;
	int mid=(tl+tr)>>1;pushdown(x,tl,tr);ll s=0;
	if(mid>=l)s+=query(ls,tl,mid,l,r); 
	if(mid<r)s+=query(rs,mid+1,tr,l,r);
	pushup(x);
	return s;
}
signed main(){
	#ifdef do_while_true
//		assert(freopen("data.in","r",stdin));
//		assert(freopen("data.out","w",stdout));
	#endif
	read(n);
	for(int i=1;i<=n;i++)read(chu[i],lim[i],dt[i]);
	S.insert({1,n,0});
	read(m);
	for(int i=1;i<=m;i++){
		int t,l,r;read(t,l,r);
		auto itr=split(r+1),itl=split(l),it=itl;
		for(;it!=itr;++it){
			int l=it->l,r=it->r,c=it->c;
			if(c==0){
				for(int j=l;j<=r;j++)
					ans[i]+=min(chu[j]+1ll*dt[j]*t,1ll*lim[j]);
			}
			else{
				vec[r].pb(mp(i,min(M,t-c)));
				if(l>1)vec[l-1].pb(mp(-i,min(M,t-c)));
			}
		}
		S.erase(itl,itr);
		S.insert({l,r,t});
	}
	for(int i=1;i<=n;i++){
		if(dt[i]){
			if(dt[i]<=lim[i]){
				//[1,p] +dt +2dt +3dt + ... + p*dt
				//[p+1,M] : +lim[i]
				int p=lim[i]/dt[i];
				modify(1,1,M,1,p,dt[i]);
				if(p<M)
					modify(1,1,M,p+1,p+1,lim[i]-dt[i]*p);
			}
			else{
				modify(1,1,M,1,1,lim[i]);
			}
		}
		for(auto j:vec[i]){
			int id=j.fi,p=j.se;
			if(id>0)ans[id]+=query(1,1,M,1,p);
			else ans[-id]-=query(1,1,M,1,p);
		}
	}
	for(int i=1;i<=m;i++)cout << ans[i] << '\n';
    #ifdef do_while_true
		cerr<<'\n'<<"Time:"<<1.0*clock()/CLOCKS_PER_SEC*1000<<" ms"<<'\n';
	#endif
	return 0;
}
```

---

## 作者：__stick (赞：3)

提供一种不需要主席树的离线单 log 做法。

# 题意
给出数组 $lim,c$。

维护一个数组 $s$，每一秒钟，$s_i=\min(lim_i,s_i+c_i)$，每次区间询问，给出当前时间 $t$，问 $s$ 当前时刻的区间和是多少。

**每次询问完后将 $s$ 数组区间置为 $0$**

## 思路

首先我们看到推平操作不难想到 odt，我们使用 odt 维护区间时间，将询问拆成一个一个颜色段来解决，每次 assign 的时候遍历当前区间中的段看当前段时间较上次更改改变了多少，由于每次操作最多产生两个区间，所以区间总数一定是 $O(m)$ 级别的。

经过这一次转化后我们就只需要处理一段数经过 $dt$ 时间变化后的和了，区间中的 $dt$ 都相同，初始值都为 $0$ （除了初始状态）,形式化的，我们只要求出下面这个式子即可：
$$
\sum_{i=l}^r\min(lim_i,dt\cdot c_i)
$$
这里，处理方式就非常多了。

这里由于 $s$ 数组初始有值，可以特判第一次修改到当前区间的情况，此时直接暴力即可，暴力复杂度之和一定是 $O(n)$ 的，原因显然，每个位置最多被暴力计算一次。

然后其他的区间都是一样的处理方式，我们知道每一个位置都会有一个分界时刻，在这个时刻之前 $\min$ 取后面一部分，之后取后面一部分，解不等式得出 $dt\ge\frac{lim_i}{c_i}$，即：$\left\lceil\frac{lim_i}{c_i}\right\rceil$。



这里代价就变成了：
$$
dt\cdot\sum_{i=l}^r c_i[dt<\left\lceil\frac{lim_i}{c_i}\right\rceil]+\sum_{i=l}^rlim_i[dt\ge\left\lceil\frac{lim_i}{c_i}\right\rceil
$$

这里将询问离线下来按照 $dt$ 排序，位置按照 $\left\lceil\frac{lim_i}{c_i}\right\rceil$ 排序，按顺序处理询问，每次处理询问前考虑计算方式发生变化的位置，这里用一个指针维护一下即可。

两个$\sum$ 可以考虑使用两个树状数组维护，每个位置只会改变一次计算方式，所以这一段的复杂度是 $O(n\log n+m\log n)$
 的。

于是可以用树状数组+排序的小 log 通过这道题。


## code
没有卡常，在洛谷上算跑的比较快的。
```cpp
struct node
{
	int l,r;
	mutable int w;
	inline node(int L,int R=0,int w=0):l(L),r(R),w(w){}
	inline bool operator<(const node& b)const{return l<b.l;}
};
set<node>s;
inline set<node>::iterator split(int pos)
{
	auto ii=s.lower_bound(node(pos));
	if(ii!=s.end()&&ii->l==pos)return ii;ii--;
	int l,r,w;l=ii->l,r=ii->r,w=ii->w;
	s.erase(ii);
	s.insert(node(l,pos-1,w));
	return s.insert(node(pos,r,w)).X;
}
struct ask
{
	int l,r,t,i;
	inline bool operator<(const ask&b)const
	{
		return t<b.t;
	}	
};
vector<ask>v;
const int MAXN=1e5+10;
int a[MAXN],lim[MAXN],c[MAXN];
pii op[MAXN];
ll ans[MAXN];
inline void baoli(int l,int r,int t,int id)
{
	for(int i=l;i<=r;i++)ans[id]+=min((ll)lim[i],(ll)a[i]+(ll)c[i]*t);	
}
struct BIT
{
	ll t[MAXN];
	inline void add(int x,ll k)
	{
		for(;x<MAXN;x+=x&-x)t[x]+=k;
	}
	inline ll ask(int x)
	{
		ll ans=0;
		for(;x;x-=x&-x)ans+=t[x];
		return ans;
	}
	inline ll ask(int ii,int it){return ask(it)-ask(ii-1);}
}t[2];
signed main()
{	
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int n;cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i]>>lim[i]>>c[i];
		if(c[i]) op[i]={(lim[i]+c[i]-1)/c[i],i};
		else op[i]={(int)1e9,i};
	}
	s.insert(node(1,n,-1));
	sort(op+1,op+n+1);
	int m;cin>>m;
	for(int i=1;i<=m;i++)
	{
		int l,r,t;
		cin>>t>>l>>r;
		auto rr=split(r+1),L=split(l);
		for(auto ii=L;ii!=rr;ii++)
		{
			if(ii->w>=0) v.push_back({ii->l,ii->r,t-ii->w,i});
			else baoli(ii->l,ii->r,t,i);
		}
		s.erase(L,rr);
		s.insert(node(l,r,t));
	}
	sort(v.begin(),v.end());
	for(int i=1;i<=n;i++) t[0].add(i,c[i]);
	int j=1;
	for(auto&p:v)
	{
		cmin(p.t,100000);
		while(j<=n&&op[j].X<=p.t)
		{
			t[0].add(op[j].Y,-c[op[j].Y]);
			t[1].add(op[j].Y,lim[op[j].Y]);
			j++;
		}
		ans[p.i]+=t[0].ask(p.l,p.r)*p.t+t[1].ask(p.l,p.r);
	}
	for(int i=1;i<=m;i++)cout<<ans[i]<<'\n';
	return 0;
} 
```


---

## 作者：_sys (赞：3)

为了和我的代码统一，$r_i$ 表示的是上限，$k_i$ 表示的是增长速度。

我们考虑，如果一个区间 $[l, r]$ 在 $t$ 需要清零，而上一次清零的时间 $t_0$ 也相同，那么这一次的答案为对于 $\frac{r_i}{k_i}\geq t-t_0$ 的位置 $i$ 的 $(t-t_0)\sum k_i$ 加上 $\frac{r_i}{k_i}<t-t_0$ 的位置 $i$ 的 $\sum r_i$。

这是一个二维数点问题，我们可以使用主席树解决。

之后，我们还需要知道哪些区间的 $t_0$ 相同。就像 $\text{ODT}$ 的那样，考虑用 `std::set` 维护，每次区间清零就把旧区间删除，新的区间插入。每次只会插入一个，所以元素个数是 $O(n)$ 的。

初始值不太好搞，我们另开一个 set 计算就好（并查集，线段树，啥都行）。

注意 $k_i=0$ 以及 $k_i=r_i=0$ 两种情况的特判。

时间复杂度：$O(n\log n)$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int Maxn = 100005;
int n, q, tree_ct, k[Maxn], r[Maxn], ord[Maxn], Head[Maxn];
struct Tree
{
	int lson, rson;
	long long k, b;
} tree[24 * Maxn];
void build_first(int root, int lt, int rt)
{
	if (lt + 1 == rt)
		tree[root].k = k[lt], tree[root].b = 0;
	else
	{
		int mid = (lt + rt) >> 1;
		tree[root].lson = ++tree_ct;
		tree[root].rson = ++tree_ct;
		build_first(tree[root].lson, lt, mid);
		build_first(tree[root].rson, mid, rt);
		tree[root].k = tree[tree[root].lson].k + tree[tree[root].rson].k;
		tree[root].b = tree[tree[root].lson].b + tree[tree[root].rson].b;
	}
}
void build(int root, int las, int lt, int rt, int pos)
{
	if (lt + 1 == rt)
		tree[root].k = 0, tree[root].b = r[lt];
	else
	{
		int mid = (lt + rt) >> 1;
		if (pos >= mid)
		{
			tree[root].rson = ++tree_ct;
			tree[root].lson = tree[las].lson;
			build(tree[root].rson, tree[las].rson, mid, rt, pos);
		}
		else
		{
			tree[root].lson = ++tree_ct;
			tree[root].rson = tree[las].rson;
			build(tree[root].lson, tree[las].lson, lt, mid, pos);
		}
		tree[root].k = tree[tree[root].lson].k + tree[tree[root].rson].k;
		tree[root].b = tree[tree[root].lson].b + tree[tree[root].rson].b;
	}
}
pair <long long, long long> operator + (pair <long long, long long> a, pair <long long, long long> b)
{
	return make_pair(a.first + b.first, a.second + b.second);
}
pair <long long, long long> ask(int root, int lt, int rt, int L, int R)
{
	if (lt == L && rt == R) return make_pair(tree[root].k, tree[root].b);
	else
	{
		int mid = (lt + rt) >> 1;
		if (L >= mid) return ask(tree[root].rson, mid, rt, L, R);
		else if (R <= mid) return ask(tree[root].lson, lt, mid, L, R);
		else return ask(tree[root].lson, lt, mid, L, mid) + ask(tree[root].rson, mid, rt, mid, R);
	}
}
struct sta
{
	int lt, rt;
	double t;
	bool operator < (const sta &tmp) const
	{
		return lt < tmp.lt;
	}
};
set <sta> Se;
set <sta> :: iterator spilt(int x)
{
	if (x > n) return Se.end();
	sta tmp = *(--Se.upper_bound((sta){x, 0, 0}));
	Se.erase(tmp);
	if (tmp.lt != x) Se.insert((sta){tmp.lt, x - 1, tmp.t});
	return Se.insert((sta){x, tmp.rt, tmp.t}).first;
}
pair <long long, long long> cal(double t, int lt, int rt)
{
	int L = 0, R = n;
	while (L + 1 <= R)
	{
		int mid = (L + R + 1) >> 1;
		if (r[ord[mid]] > t * k[ord[mid]]) R = mid - 1;
		else L = mid;
	}
	return ask(Head[L], 1, n + 1, lt, rt + 1);
}
set <pair <int, int> > S;
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d%d%d", &x, &r[i], &k[i]), ord[i] = i;
		if (!r[i] && !k[i]) r[i] = 1;
		if (k[i])
			Se.insert((sta){i, i, -x / (double) k[i]});
		else Se.insert((sta){i, i, 0}), S.insert(make_pair(i, x));
	}
	S.insert(make_pair(n + 1, 0));
	Head[0] = ++tree_ct;
	build_first(Head[0], 1, n + 1);
	sort(ord + 1, ord + 1 + n, [](int x, int y){return r[x] * (long long) k[y] < r[y] * (long long) k[x];});
	for (int i = 1; i <= n; i++)
		Head[i] = ++tree_ct, build(Head[i], Head[i - 1], 1, n + 1, ord[i]);
	scanf("%d", &q);
	while (q--)
	{
		int t, lt, rt;
		long long ans = 0;
		scanf("%d%d%d", &t, &lt, &rt);
		set <pair <int, int> > :: iterator it;
		while (S.size() > 1 && (it = S.lower_bound(make_pair(lt, 0))) -> first <= rt)
		{
			ans += it -> second;
			S.erase(it);
		}
		set <sta> :: iterator it_r = spilt(rt + 1), it_l = spilt(lt), tmp_it;
		tmp_it = it_l;
		for (; it_l != it_r; it_l++)
		{
			pair <long long, long long> now = cal(t - it_l -> t, it_l -> lt, it_l -> rt);
			ans += now.second + (long long) (now.first * (t - it_l -> t) + 0.5);
		}
		Se.erase(tmp_it, it_r);
		Se.insert((sta){lt, rt, (double) t});
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：珈乐唯毒 (赞：2)

做法就是考虑从第 $1$ 号马向第 $n$ 离线处理，当扫到一个询问的左端点时将其加入，扫到右端点时将其删除。~~这很扫描线~~

现在我们需要考虑维护这样一个东西：对于第 $k$ 个对于一个询问 $i$ ，我们定义 $val_i$ 为其与上一个询问之间的询问差。那么新增的答案显然只与 $val_i$ 有关。

对于 $val_i \leq \lceil \frac{m_k}{r_k} \rceil$，$k$ 对 $i$ 的贡献为 $val_i \cdot r_k$。

对于 $val_i > \lceil \frac{m_k}{r_k} \rceil$，$k$ 对 $i$ 的贡献为 $m_i$。

可以利用一颗平衡树来解决，用两种tag来维护实现。

插入的时候只会有一个询问的 $val$ 发生改变，我们把它删掉，统计答案，改变 $val$ 再插回去即可。

删除时同理，只有一个 $val$ 会发生变化，删掉后加入即可。

时间复杂度 $O(n\log{n})$ 

代码如下
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=100005,INF=1e9+7;
int n;
map<int,int> ori;
int s[N],r[N],m[N],t[N];
vector<int> add[N],del[N];

inline int read(){
	int ans=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')ans=(ans<<1)+(ans<<3)+c-'0',c=getchar();
	return ans;
}

int son[N][2],f[N],sz[N],pd1[N],pd2[N],val[N],as[N],root;
int ss[N],sl;
bool get_s(int x){return son[f[x]][1]==x;}
void ad1(int x,int vl){
	pd1[x]+=vl;
	as[x]+=vl*val[x];
}
void ad2(int x,int vl){
	pd2[x]+=vl;
	as[x]+=vl;
}
void pushdown(int x){
	if(son[x][1]){
		ad1(son[x][1],pd1[x]);
		ad2(son[x][1],pd2[x]);
	}
	if(son[x][0]){
		ad1(son[x][0],pd1[x]);
		ad2(son[x][0],pd2[x]);
	}
	pd1[x]=pd2[x]=0;
}
void rotate(int x){
	int fx=f[x],k=get_s(x);
	f[x]=f[fx];if(f[fx])son[f[fx]][get_s(fx)]=x;
	if(son[x][k^1])f[son[x][k^1]]=fx;son[fx][k]=son[x][k^1];
	son[x][k^1]=fx;f[fx]=x;
}
void splay(int x,int aim=0){
	int y=x;
	ss[sl=1]=y;
	while(f[y])ss[++sl]=y=f[y];
	while(sl)pushdown(ss[sl--]);
	while(f[x]!=aim){
		if(f[f[x]]!=aim){
			if(get_s(f[x])==get_s(x))rotate(f[x]);
			else rotate(x);
		}
		rotate(x);
	}
	if(!aim)root=x;
}
void build(){
	root=N-2;
	val[root]=-INF;
	son[root][1]=N-1;
	f[N-1]=root;
	val[N-1]=INF;
}
bool cmp(int x,int y){
	if(val[x]==val[y])return x<y;
	return val[x]<val[y];
}
int pre(){
	int nw=son[root][0];
	while(son[nw][1])nw=son[nw][1];
	return nw;
}
int suf(){
	int nw=son[root][1];
	while(son[nw][0])nw=son[nw][0];
	return nw;
}
void insert(int x){
	int nw=root;
	pushdown(nw);
	while(son[nw][cmp(nw,x)])nw=son[nw][cmp(nw,x)],pushdown(nw);
	son[nw][cmp(nw,x)]=x;
	f[x]=nw;
	splay(x);
}
void dfss(int u){
	pushdown(u);
	if(son[u][0])dfss(son[u][0]);
	if(son[u][1])dfss(son[u][1]);
}
void delet(int x){
	splay(x);
	int sf=suf(),pr=pre();
	splay(sf);
	splay(pr,sf);
	son[pr][1]=0;
}
set<int> st;
set<int>::iterator it;
void ad(int x){
	it=st.lower_bound(t[x]);
	if(it!=st.end()){
		int nxt=ori[*it];
		delet(nxt);
		val[nxt]=t[nxt]-t[x];
		insert(nxt);
	}
	int nm=*(--it);
	val[x]=t[x]-nm;
	insert(x);
	st.insert(t[x]);
}
void de(int x){
	it=st.lower_bound(t[x]);
	int nm=*(--it);
	++it;++it;
	if(it!=st.end()){
		int nxt=ori[*it];
		delet(nxt);
		val[nxt]=t[nxt]-nm;
		insert(nxt);
	}
	delet(x);
	st.erase(t[x]);
}
void solve(int x){
	if(r[x]){
		val[N-3]=m[x]/r[x];
		insert(N-3);
		ad1(son[root][0],r[x]);
		ad2(son[root][1],m[x]);
		delet(N-3);
		it=st.begin();
		it++;if(it==st.end())return;
		int nm=ori[*it];
		if(t[nm]>val[N-3])as[nm]-=m[x];
		else as[nm]-=r[x]*t[nm];
		as[nm]+=min(r[x]*t[nm]+s[x],m[x]);	
	}
	else{
		it=st.begin();
		it++;if(it==st.end())return;
		int nm=ori[*it];
		as[nm]+=s[x];
	}
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		s[i]=read();
		m[i]=read();
		r[i]=read();
	}
	int mm;
	scanf("%lld",&mm);
	for(int i=1;i<=mm;i++){
		t[i]=read();
		int l=read(),r=read();
		add[l].push_back(i);
		del[r].push_back(i);
		ori[t[i]]=i;
	}
	st.insert(0);
	build();
	for(int i=1;i<=n;i++){
		for(int j=0;j<(int)add[i].size();j++)ad(add[i][j]);
		solve(i);
		for(int j=0;j<(int)del[i].size();j++)de(del[i][j]);
	}
	for(int i=1;i<=mm;i++)printf("%lld\n",as[i]);
	return 0;
}
```


---

## 作者：elijahqi (赞：2)

 http://www.elijahqi.win/archives/3943
 https://blog.csdn.net/elijahqi/article/details/81013860
 
 题目背景

半人马提雷克是“我的小马驹：友谊是魔法”第四季最后两集的大反派。在“闪闪王国（上）”中，提雷克从塔他洛斯逃了出来。为了变得更加强大，他还吸取了小马们的魔法。

题目描述

提雷克的核心技能是法力吸取。这个技能可以吸收一个魔法生物的所有魔力并把它们交给施法者。

现在我们把这个问题简化，假设你有n只小马（编号从1到n）。每只小马有三种属性。

si：时间为0时这只小马拥有的法力值

mi：这只小马可以拥有的最大法力值

ri：这只小马单位时间内回复的法力值

提雷克会给出m条指令，每一条都可以被描述为3个整数：ti，li，ri。表示在时间为ti时，提雷克会从编号为li~ri的小马中吸取魔力（包括li，ri），我们会有序地给出m条指令，请你算出每一条指令之后提雷克可以吸取多少点魔力。

输入输出格式

输入格式：

第一行包含一个整数N（1 ≤ N ≤ 1e5）-小马的编号。接下来的n行每行包含三个整数Si， mi， ri（0 ≤ si ≤ mi ≤ 1e5；0 ≤ ri ≤ 1e5），表示 一只小马。

下一行包含一个整数m（1 ≤ M ≤ 1e5）-指令数。接下来的m行包含三个整数Ti， li， ri（0 ≤ ti ≤ 1e9；1 ≤ li ≤ ri ≤ N），表示提雷克的指令。所有的指令在ti递增的顺序下给出。

输出格式：

对于每一个指令，输出一行，包含一个整数：提雷克这一次一共吸收了多少魔力。

设tag表示 一个区间是否被从初始状态修改过 如果修改过 这个区间是否被完整的修改过

如果完整的修改过 那么就针对整个区间内生长时间排序 然后二分出我上一次修改到这次询问时间在哪里 然后前面的就是全部都长满的 后面就是没有长满的 那么预处理出关于m的前缀和再预处理出关于r的后缀和 回答的时候二分一下再o(1)回答即可

如果两个区间被修改成一样的需要合并标记 只有当标记不同的时候才需要下放 如果区间标记不同则需要继续分治下去做 这样复杂度可以证明是$n\times log(n)^2$的 考虑每次覆盖一个区间最多把一个区间变成两个 我如果需要暴力去做这样很多段的区间的话我后面一定会把他们再合成一段的
```
#include<bits/stdc++.h>
#define lc (x<<1)
#define rc (x<<1|1)
#define ll long long
using namespace std;
inline char gc(){
	static char now[1<<16],*S,*T;
	if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
	return *S++;
}
inline int read(){
	int x=0,f=1;char ch=gc();
	while(!isdigit(ch)) {if (ch=='-')f=-1;ch=gc();}
	while(isdigit(ch)) x=x*10+ch-'0',ch=gc();
	return x*f;
}
const int N=1e5+10;
const int inf=0x3f3f3f3f;
struct node1{
	int s,m,r,t;
}a[N];
struct node{
	vector<ll> pre,suc;vector<node1> f;vector<int> tim;
	int tag;
	inline void merge(const vector<node1> &a,const vector<node1> &b){
		int n1=a.size(),n2=b.size();int now1=0,now2=0;
		while(now1<n1&&now2<n2){
			if (a[now1].t<b[now2].t) f.push_back(a[now1]),++now1;
			else f.push_back(b[now2]),++now2;
		}
		while(now1<n1) f.push_back(a[now1]),++now1;
		while(now2<n2) f.push_back(b[now2]),++now2;ll pre1=0,suc1=0;
		for (int i=0;i<f.size();++i) pre1+=f[i].m,pre.push_back(pre1),tim.push_back(f[i].t);
		suc.resize(f.size()+10);for (int i=f.size()-1;~i;--i) suc1+=f[i].r,suc[i]=suc1;
	}
	inline ll gao(int t){
		t=t-tag;int p=lower_bound(tim.begin(),tim.end(),t)-tim.begin();
		ll tmp=0;if (p) tmp+=pre[p-1];
		if(p!=tim.size()) tmp+=(ll)suc[p]*t;return tmp;
	}
}tree[N<<2];
int n,t,m;
inline void update(int x){
	if (tree[lc].tag==-2||tree[rc].tag==-2) {tree[x].tag=-2;return;}
	if (tree[lc].tag==tree[rc].tag&&tree[lc].tag>=0) {tree[x].tag=tree[lc].tag;return;}
	tree[x].tag=-1;
}
inline void build(int x,int l,int r){
	tree[x].tag=-2;
	if(l==r) {
		tree[x].f.push_back(a[l]);tree[x].pre.push_back(a[l].m);
		tree[x].tim.push_back(a[l].t);tree[x].suc.push_back(a[l].r);return;
	}int mid=l+r>>1;
	build(lc,l,mid);build(rc,mid+1,r);
	tree[x].merge(tree[lc].f,tree[rc].f);
}
inline void pushdown(int x){
	if (tree[x].tag>=0) tree[lc].tag=tree[rc].tag=tree[x].tag;
}
inline ll query(int x,int l,int r,int l1,int r1){
	if (l==r&&tree[x].tag==-2){
		ll tmp=a[l].s;tmp+=(ll)t*a[l].r;tmp=min(tmp,(ll)a[l].m);
		tree[x].tag=t;return tmp;
	}
	if (l1<=l&&r1>=r&&tree[x].tag>=0){
		ll tmp=tree[x].gao(t);tree[x].tag=t;return tmp;
	}
	int mid=l+r>>1;pushdown(x);ll tmp=0;
	if (l1<=mid) tmp+=query(lc,l,mid,l1,r1);
	if (r1>mid) tmp+=query(rc,mid+1,r,l1,r1);
	update(x);return tmp;
}
int main(){
	freopen("cf.in","r",stdin);
	n=read();
	for (int i=1;i<=n;++i) {
		a[i].s=read(),a[i].m=read(),a[i].r=read();
		a[i].t=a[i].r?a[i].m/a[i].r:inf;
	}build(1,1,n);m=read();
	for (int i=1;i<=m;++i){
		int l,r;t=read();l=read();r=read();
		printf("%lld\n",query(1,1,n,l,r));
	}
	return 0;
}
```

---

## 作者：QWQ_SenLin (赞：1)

首先考虑简单的情况：假如 $a_i$ 均为 $0$ ，可以算出这个点最小需要几时才能到最大值 $m_i$，记为 $f_i$，显然 $f_i = \lceil \dfrac{m_i}{r_i}\rceil$，注意特判 $r_i=0$。

由于操作完 $s_i$ 清空，可以看作推平操作，于是容易想到用珂朵莉树维护修改的时间，那么下一次这个块的增长的时间是一致的。

于是问题变为：求一段区间 $s_i$ 均为 $0$，过 $t$ 秒后的和。可以发现每个点分两种情况：

- $t\ge f_i$：这个点加到上限了，为 $m_i$。

- $t < f_i$：这个点为 $tr_i$。

由于 $t$ 相同，第二类的点可以把 $t$ 提出来，变成求满足 $f_i > t$ 的点的 $t_i$ 和。

可以预先把每个点放到横坐标代表 $i$，纵坐标代表 $f$ 的二维平面上，第 $i$ 个点的坐标则为 $(i,f_i)$，权值为 $m_i$ 或 $r_i$（如图，图中放一个平面了，比较好看）。

![](https://cdn.luogu.com.cn/upload/image_hosting/vk25jvmo.png)

那么每次询问相当于可以分开求这两类点，对于第一类点，可以在维护 $m$ 的二维平面中求 $[l,1,t-1,MAX]$ 矩形的点权和。对于第二类点，就是在维护 $r$ 的二维平面内 $[l,t,r,MAX]$ 矩形的点权和。于是离线下来扫描线，扫描线可以用树状数组比较快。

然后当 $a_i\not = 0$ 时，处理也很简单，只需要在第一次修改时暴力处理，之后便都可以看成 $0$ 了。

[code](https://codeforces.com/problemset/submission/453/316031253)

---

## 作者：xyvsvg (赞：1)

不妨先考虑没有初值的情况。

注意到每次查询后会推平区间，这启发我们使用珂朵莉树维护将上次被推平的时间相同的数放在同一个颜色段，计算答案时，我们分段计算。

现在考虑一个段的答案。不妨令 $\Delta t$ 表示这次询问的 $t$ 减去上次被推平的时间。如果没有 $m$ 的限制，那么显然答案为 $\Delta t\sum k_i$，这启发我们先求出没有 $m$ 限制的值，再将多余的值减去。

考虑对第 $i$ 个元素而言，什么样的 $\Delta t$ 计算出的 $k_i*\Delta t$ 会恰大于等于 $m_i$？显然是 $\Delta t_i=\lfloor \frac{k_i}{m_i}\rfloor$。即 $ \sum max(k_i\Delta t,\ m_i)= \sum\limits_{\Delta t\leq\Delta t_i}{m_i}+\sum\limits_{\Delta t\gt\Delta t_i}{k_i\Delta t}$。

因此，我们可以开一颗权值主席树来维护，使用差分得到当前区间的答案，其中下标 $\Delta t_i$ 上存储 $k_i$ 与 $m_i$。于是我们计算出了答案。

结束了么？没有。我们还有两个细节需要处理：一是，当 $k_i$ 等于 $0$ 时，我们直接让 $root_i=root_{i-1}$ 即可；二是我们还没考虑初值 $s_i$，不过这是容易解决的，我们只需对于未进行任何一次操作的 $i$，令它在珂朵莉树中的权值为 $-1$，在计算时特判即可，初始时，每个数单独成段。

代码比较简洁：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5;
typedef long long ll;
typedef pair<ll,ll> P;
P operator+(const P&x,const P&y)
{
    return {x.first+y.first,x.second+y.second};
}
P operator-(const P&x,const P&y)
{
    return {x.first-y.first,x.second-y.second};
}
struct Info
{
    int l=0,r=0;
    ll k=0,m=0;
};
Info sgt[N*40];
int root[N+10],tot;
void upd(int p,int q,int l,int r,int k,int x,int y)
{
    sgt[q]=sgt[p];
    if(l+1==r)
        sgt[q].k+=x,sgt[q].m+=y;
    else
    {
        int mid=l+r>>1;
        if(k<mid)
            upd(sgt[p].l,sgt[q].l=++tot,l,mid,k,x,y);
        else
            upd(sgt[p].r,sgt[q].r=++tot,mid,r,k,x,y);
        sgt[q].k=sgt[sgt[q].l].k+sgt[sgt[q].r].k;
        sgt[q].m=sgt[sgt[q].l].m+sgt[sgt[q].r].m;
    }
}
P qry(int p,int l,int r,int x,int y)
{
    if(x<=l&&r<=y)
        return {sgt[p].k,sgt[p].m};
    else if(r>x&&l<y)
    {
        int mid=l+r>>1;
        return qry(sgt[p].l,l,mid,x,y)+qry(sgt[p].r,mid,r,x,y);
    }
    return {0,0};
}
int main()
{
    int n;
    cin>>n;
    vector<int>s(n+10),m(n+10),k(n+10);
    vector<ll>pref(n+10);
    map<int,int>odt;
    root[0]=++tot;
    for(int i=1;i<=n;++i)
    {
        cin>>s[i]>>m[i]>>k[i],odt[i]=-1;
        pref[i]=k[i]+pref[i-1];
        if(k[i])
            upd(root[i-1],root[i]=++tot,0,N+1,m[i]/k[i],k[i],m[i]);
        else
            root[i]=root[i-1];
    }
    auto[ks,ms]=qry(root[n],0,N+1,0,14);
    auto rg=[&](int l,int r)
    {
        return pref[r]-pref[l-1];
    };
    odt[n+1]=-1;
    auto odiv=[&](int k)
    {
        auto it=prev(odt.upper_bound(k));
        odt.insert(it,make_pair(k,it->second));
    };
    auto operform=[&](int l,int r,int t,int T)
    {
        ll ret=0;
        if(~t)
        {
            T-=t;
            auto[ks,ms]=qry(root[r-1],0,N+1,0,T)-qry(root[l-1],0,N+1,0,T);
            ret=(rg(l,r-1)-ks)*T+ms;
        }
        else
            ret=min(m[l]*1LL,s[l]+1LL*T*k[l]);
        return ret;
    };
    auto oassign=[&](int l,int r,int t)
    {
        odiv(l);
        odiv(r);
        ll ret=0;
        for(auto it=odt.lower_bound(l);it->first!=r;it=odt.erase(it))
            ret+=operform(it->first,next(it)->first,it->second,t);
        odt[l]=t;
        return ret;
    };
    int Q;
    cin>>Q;
    while(Q--)
    {
        int t,l,r;
        cin>>t>>l>>r;
        cout<<oassign(l,r+1,t)<<endl;
    }
    return 0;
}

```

---

## 作者：Purslane (赞：1)

# Solution

这道题是我很久之前留下的坑，现在考虑把补上。![](https://pic3.zhimg.com/v2-436240247bafdfd2a10eff19371b3676_b.webp)

考虑使用颜色段均摊：对于每个位置，维护它最后一次清空的时间。在询问的过程中，我们对每个颜色段单独计算答案，则总的颜色段计算数为 $O(n+q)$。（势能分析法，注意第一次的初始值为 $s$，那么可以单独暴力计算，每个位置只会计算一次）

剩下的问题变成了：不考虑清空操作，查询某一段区间在时间 $t$ 的权值和。差分之后变成查询前缀在时间 $t$ 的前缀和。考虑对于位置进行扫描线，维护时间，那么每个位置对于某一段时间有 $r_ix$ 的贡献，对后一段时间有 $m_i$ 的贡献，实现一个区间加等差序列、单点查询的线段树即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10;
int n,q,s[MAXN],m[MAXN],r[MAXN],ans[MAXN];
vector<pair<int,pair<int,int>>> qr[MAXN]; //{time,mul,id}
struct Node {int l,r;mutable int id;};
bool operator <(Node A,Node B) {return A.l<B.l;}
set<Node> odt;
set<Node>::iterator split(int pos) {
	if(pos>n) return odt.end();
	auto it=--odt.upper_bound({pos,0,0});
	int l=it->l,r=it->r,id=it->id;
	if(l==pos) return it;
	odt.erase(it),odt.insert({l,pos-1,id});
	return odt.insert({pos,r,id}).first;
}
int tagk[MAXN<<2],tagb[MAXN<<2],sum[MAXN<<2];
#define lson (k<<1)
#define rson (k<<1|1)
#define mid (l+r>>1)
void apply(int k,int l,int r,int tk,int tb) {return tagk[k]+=tk,tagb[k]+=tb,sum[k]+=tb*(r-l+1)+tk*(l+r)*(r-l+1)/2,void();}
void push_down(int k,int l,int r) {return apply(lson,l,mid,tagk[k],tagb[k]),apply(rson,mid+1,r,tagk[k],tagb[k]),tagk[k]=tagb[k]=0,void();}
void update(int k,int l,int r,int x,int y,int tk,int tb) {if(x<=l&&r<=y) return apply(k,l,mid,tk,tb),void();push_down(k,l,r);if(x<=mid) update(lson,l,mid,x,y,tk,tb);if(y>mid) update(rson,mid+1,r,x,y,tk,tb);return sum[k]=sum[lson]+sum[rson],void();}
int query(int k,int l,int r,int pos) {if(l==r) return sum[k];push_down(k,l,r);if(pos<=mid) return query(lson,l,mid,pos);return query(rson,mid+1,r,pos);}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n; ffor(i,1,n) cin>>s[i]>>m[i]>>r[i];
	odt.insert({1,n,0});
	cin>>q;
	ffor(i,1,q) {
		int L,R,t; cin>>t>>L>>R;
		auto it2=split(R+1),it1=split(L);
		for(auto it=it1;it!=it2;it++) {
			if(it->id==0) ffor(pos,it->l,it->r) ans[i]+=min(m[pos],s[pos]+t*r[pos]);
			else qr[it->r].push_back({min(100000ll,t-it->id),{1,i}}),qr[it->l-1].push_back({min(100000ll,t-it->id),{-1,i}});
		}
		odt.erase(it1,it2),odt.insert({L,R,t});
	}
	ffor(i,1,n) {
		if(r[i]) {
			int t=m[i]/r[i];
			if(t) update(1,1,100000,1,t,r[i],0);
			if(t<100000) update(1,1,100000,t+1,100000,0,m[i]);
		}
		for(auto pr:qr[i]) ans[pr.second.second]+=pr.second.first*query(1,1,100000,pr.first);
	}
	ffor(i,1,q) cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：freoepn (赞：0)

考虑分块，可以预处理出每一个块被全部刷为 $0$ 之后过去任意时间的和，但对于没有被刷过或只有部分被刷过的块不好维护权值，只能暴力求值，但可以发现每次询问顶多产生两个这样的块，最多也只用暴力求值 $n+2m$ 个这样的块，暴力做即可。


```cpp
#include <bits/stdc++.h>
using namespace std;
const int kMaxN = 1e5 + 5, B = 350;
long long a[kMaxN], b[kMaxN], c[kMaxN], n, m, p;
long long bl[B], br[B], ti[kMaxN], check[kMaxN];
int qt[B][kMaxN];
pair<int, int> q[B];
signed  main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i] >> b[i] >> c[i], ti[i] = -1;
  }
  for (long long i = 1; i <= n; i += B) {
    bl[++p] = i, br[p] = min(n, i + B - 1);
    //	if(n >= 1000){
    //	cout << p << " "<< bl[p]<< " "<< br[p]<< '\n';
    //}
    int sum = 0, siz = 0, e = 0, u = 0;
    for (int j = bl[p]; j <= br[p]; j++) {
      if (c[j] != 0) {
        sum += c[j];
        q[++siz] = make_pair((b[j] / c[j]) + 1, j);
      }
    }
    sort(q + 1, q + 1 + siz);
    for (int j = 1; j < kMaxN; j++) {
      u = 0;
      while (e + 1 <= siz && q[e + 1].first == j) {
        e++;
        sum -= c[q[e].second];
        u += b[q[e].second] % c[q[e].second];
      }
      qt[p][j] = qt[p][j - 1] + sum + u;
      // if (j <= 20) {
      //   cout << p << " " << j << " " << qt[p][j] << " " << sum << " " << u <<" "<< e << " "<< q[e+1].first <<  '\n'
      //        << '\n';
      // }
    }
  }
  cin >> m;
  while (m--) {
    int x, l, r;
    cin >> x >> l >> r;
    long long ans = 0;
    for (int i = 1; i <= p; i++) {
      // cout << x << " "<< l << " "<< r << " "<< bl[i]<< " "<< br[i]<< '\n';
      // for(int i = 1;i <= n;i++){
      //	cout << ti[i]<< " ";
      // }
      // cout << '\n';
      //	if(n >= 1000){
      //	cout <<  i << " "<< bl[i]<< " "<< br[i]<< " "<< l << " "<< r << '\n';
      // }
      if (l <= bl[i] && br[i] <= r) {
        if (check[i]) {
          //	cout << x - ti[bl[i]] << '\n';
          ans += (long long)(qt[i][min(x - ti[bl[i]],(long long)kMaxN-1)]);
        } else {
          // cout << bl[i]<< " "<< br[i]<< '\n';
          for (int j = bl[i]; j <= br[i]; j++) {
            // cout << x - ti[j]<< '\n';
            if (ti[j] != -1) {
              ans += (long long)min(b[j], (x - ti[j]) * c[j]);
            } else {
              ans += (long long)min(b[j], (x - ti[j] - 1) * c[j] + a[j]);
            }
          }
        }
        check[i] = 1, ti[bl[i]] = x;
      } else if (bl[i] <= l && r <= br[i]) {
        //	cout << "!!\n";
        for (int j = br[i]; j >= bl[i]; j--) {
          if (check[i] == 1) {
            //		cout << j << ":\n";
            ti[j] = ti[bl[i]];
          }
        }
        for (int j = br[i]; j >= bl[i]; j--) {
          if (l <= j && j <= r) {
            //	cout << j << " "<< ti[j]<< '\n';
            if (ti[j] != -1) {
              ans += (long long)min(b[j], (x - ti[j]) * c[j]);
            } else {
              ans += (long long)min(b[j], (x - ti[j] - 1) * c[j] + a[j]);
            }
            ti[j] = x;
          }
        }
        check[i] = 0;
      } else if (br[i] >= l && bl[i] <= l) {
        for (int j = br[i]; j >= bl[i]; j--) {
          if (check[i] == 1) {
            //		cout << j << ":\n";
            ti[j] = ti[bl[i]];
          }
        }
        for (int j = bl[i]; j <= br[i]; j++) {
          if (j >= l) {
            if (ti[j] != -1) {
              ans += (long long)min(b[j], (x - ti[j]) * c[j]);
            } else {
              ans += (long long)min(b[j], (x - ti[j] - 1) * c[j] + a[j]);
            }
            ti[j] = x;
          } 
        }
        check[i] = 0;
      } else if (bl[i] <= r && br[i] >= r) {
        for (int j = br[i]; j >= bl[i]; j--) {
          if (check[i] == 1) {
            //		cout << j << ":\n";
            ti[j] = ti[bl[i]];
          }
        }
        for (int j = br[i]; j >= bl[i]; j--) {
          if (j <= r) {
            if (ti[j] != -1) {
              ans += (long long)min(b[j], (x - ti[j]) * c[j]);
            } else {
              ans += (long long)min(b[j], (x - ti[j] - 1) * c[j] + a[j]);
            }
            ti[j] = x;
          } 
        }
        check[i] = 0;
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
```

---

## 作者：ty_mxzhn (赞：0)

## 题意简述

- 维护一个长度为 $n(1\le n \le 10^5)$ 的数组 $s$，初值给定且 $0 \le s_i \le 10^5$。
- 每过 $1$ 单位时间，都会对于所有 $[1,n]$ 之间的整数 $i$，执行 $s_i \gets \min\{m_i,s_i+r_i\}$。其中 $m_i$ 和 $r_i$ 给定且 $0 \le m_i, r_i \le 10^5$。
- 维护 $m(1\le m \le 10^5)$ 次操作，每次操作时会将时间设为 $t(0 \le t \le 10^9)$，并且查询 $s$ 数组 $[l,r]$ 区间和。每次操作结束后会将 $s$ 数组的 $[l,r]$ 区间推平为 $0$，保证 $t_i$ 递增。
- 初始没有进行操作时时间为 $0$。

## 题解

发现查询以后区间都会推平，这是一个很重要的性质。虽然可能有点牵强？

那么每一时刻的小马，被推平了以后就会按照一个规律反复的循环。具体的来说，被推平以后前 $y_i$ 时刻每次增长 $r_i$，后面一直恒定在 $m_i$，等待下一次被推平。

对于还没有被推平过的小马，这一部分的贡献显然可以直接用 set 把他们暴力查找并推平。复杂度显然正确，为 $O(n \log n)$。

对于已经被推平过至少一次的小马呢？他们分为两种，未到上界和到了。如果我们颜色段均摊，对于每一个颜色段就可以直接用主席树暴力查询。

时间复杂度 $O((n+m)\log n)$。

值得注意的是，初学颜色段均摊的人容易犯的错误就是以为颜色段均摊支持一般查询。实际上显然复杂度会退化。只有像这道题一样一次查询带一次刷颜色才能支持查询。

---

## 作者：Luciylove (赞：0)

Friendship is magic！！

前置简单题： [[ABC255Ex] Range Harvest Query](https://www.luogu.com.cn/problem/AT_abc255_h)。

考虑维护 $t$ 相同的颜色段。

然后注意到一个颜色段被取出后必然被推平，所以一个段只会被遍历一次。

一次只会增加一个颜色段，可以 $O(q \log n)$ 来维护。

然后我们考虑对于没有推平过和推平过的分类：

- 没有推平过：

考虑计算 $s_i + t \times r_i < m_i$ 的左式总和，然后再计算 $s_i + t \times r_i > m_i$ 的右式总和。

可以考虑的办法是对于左边大于右边的阈值 $t_i$ 上二位数点，然后再结合前缀和计算。

具体来说是维护 $t_i \leq t$ 的所有 $m_i$ 以及 $t_i > t$ 的所有 $s_i$ 和 $r_i$，然后就可以分类计算贡献。

- 推平过：
即原来的 $s_i \to 0$ 的情况。

不难用两个主席树维护。复杂度 $O((n + q) \log n)$。

代码很丑。

```cpp
// LUOGU_RID: 139435454
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = l; i <= r; i ++)
#define per(i, r, l) for (int i = r; i >= l; i --)

using namespace std;
bool s1;

typedef long long ll;
const int _ = 1e5 + 5, lim = 1e5 + 5, mod = 998244353;
int power (int x, int y) {
	int ret = 1;
	for ( ; y; y >>= 1, x = 1ll * x * x % mod)
		if (y & 1) ret = 1ll * ret * x % mod;
	return ret;
}

struct node {
	int l, r, t;
	node (int _l = -1, int _r = -1, int _t = -1) {
		l = _l, r = _r, t = _t;
	}
	bool operator < (const node & x) const { return l < x.l; }
};
set <node> s;
auto split (int x) {
	auto it = s.lower_bound(node(x));
	if (it != s.end() && it -> l == x) return it;
	-- it;
	node tmp(*it);
	s.erase(tmp), s.insert(node(tmp.l, x - 1, tmp.t));
	return s.insert(node(x, tmp.r, tmp.t)).first;
}

int tot[2], rt[_], rtp[_];
namespace dataStructure {
	struct Info { 
		ll sums = 0, suma = 0, sumr = 0;
	} initp;
	Info operator + (Info x, Info y) { return {x.sums + y.sums, x.suma + y.suma, x.sumr + y.sumr}; }
	Info operator - (Info x, Info y) { return {x.sums - y.sums, x.suma - y.suma, x.sumr - y.sumr}; }
	struct SegMent {
		int op;
		int lc[_ * 20], rc[_ * 20];
		Info t[_ * 20];
		void ins (int &x, int p, int l, int r, int v, Info k) {
			x = ++ tot[op], lc[x] = lc[p], rc[x] = rc[p], t[x] = t[p] + k;
			if (l == r) return ;
			int mid = (l + r) >> 1;
			v <= mid ? ins(lc[x], lc[p], l, mid, v, k) : ins(rc[x], rc[p], mid + 1, r, v, k);
		}
		Info query (int x, int l, int r, int ql, int qr) {
			if (!x) return initp;
			if (ql <= l && r <= qr) return t[x];
			int mid = (l + r) >> 1;
			Info ret = initp;
			if (ql <= mid) ret = ret + query(lc[x], l, mid, ql, qr);
			if (qr > mid) ret = ret + query(rc[x], mid + 1, r, ql, qr);
			return ret;
		}
	} t1, t2;
	
} using namespace dataStructure;
int n, q;
int a[_], m[_], r[_];
ll suma[_], sumr[_];

bool s2;
int main () {
	cin >> n;
	t1.op = 0, t2.op = 1;
	rep(i, 1, n) {
		scanf("%d%d%d", & a[i], & m[i], & r[i]);
		
		if (r[i]) {
			int t = (m[i] - a[i]) / r[i];
			if (t * r[i] + a[i] < m[i]) 
				t1.ins(rt[i], rt[i - 1], 0, lim, t + 1, {m[i], a[i], r[i]});
			else 
				t1.ins(rt[i], rt[i - 1], 0, lim, t, {m[i], a[i], r[i]});			
		} else t1.ins(rt[i], rt[i - 1], 0, lim, 0, {a[i], a[i], 0});
		
		sumr[i] = sumr[i - 1] + r[i], suma[i] = suma[i - 1] + a[i];
		
		if (r[i]) {
			int t = m[i] / r[i];
			if (t * r[i] < m[i]) 
				t2.ins(rtp[i], rtp[i - 1], 0, lim, t + 1, {m[i], 0, r[i]});
			else 
				t2.ins(rtp[i], rtp[i - 1], 0, lim, t, {m[i], 0, r[i]});			
		} else t2.ins(rtp[i], rtp[i - 1], 0, lim, 0, {0, 0, 0});
		
	}
	s.insert(node(1, n, 0));
	cin >> q;
	while (q --) {
		int l, r, t;
		ll ret = 0;
		scanf("%d%d%d", & t, & l, & r);
		auto itr = split(r + 1), itl = split(l);
		for (auto it = itl; it != itr; it ++) {
			int l = it -> l, r = it -> r, c = it -> t;
			if (!c) {
				c = t;
				Info res = t1.query(rt[r], 0, lim, 0, c) - t1.query(rt[l - 1], 0, lim, 0, c);
				ret += res.sums;
				ret += 1ll * c * (sumr[r] - sumr[l - 1] - res.sumr);
				ret += (suma[r] - suma[l - 1] - res.suma);
			} else {
				c = min(lim, t - c);
				Info res = t2.query(rtp[r], 0, lim, 0, c) - t2.query(rtp[l - 1], 0, lim, 0, c);
				ret += res.sums;
				ret += 1ll * c * (sumr[r] - sumr[l - 1] - res.sumr);
			}
		}
		s.erase(itl, itr), s.insert(node(l, r, t));
		printf("%lld\n", ret);
	}
	return 0;
}
```



---

## 作者：Larry76 (赞：0)

这是一个离线做法。

考虑每一次询问都会导致一部分直接推平，然后推平后我们就成了简单的分段函数型（一次函数与常值函数）了，我们设时间为每个位置的颜色，则此时每一次区间查询就被我们转换到区间染色，这样贡献被拆成了若干染色段的同时也方便我们维护时间差。

考虑 $m,r$ 的范围比较小，仔细算算我们最多最多只需要维护 $10^5$ 长度的时间，这样就好办了，考虑扫描线扫描序列维，然后分段函数就被我们变成了在时间维上的等差数列加（当函数值 $\le m$ 时）和区间染色（当函数值 $\ge m$ 时），然后查询是一个单点的查询，所以不难想到进行一个差分，然后将「等差数列加」和「区间染色」转变成「区间加」和「单点加」，然后将单点查变为「两次前缀和的差」。

```cpp
int lim[MAX_SIZE];
int k[MAX_SIZE];
int b[MAX_SIZE];

int n, m;
const int TIME_LIMIT = 1e5;
struct SegmentTree{
	int val;
	int lazy;
};

SegmentTree seg[MAX_SIZE << 2];

// This is Yellow Duck Debug Way
void pushdown(int p, int tl, int tr) {
	if(seg[p].lazy) {
		int mid = (tl + tr) >> 1;
		seg[p<<1].val += seg[p].lazy * (mid - tl + 1); // Update Left subtree's value.
		seg[p<<1|1].val += seg[p].lazy * (tr - mid); // Update Right subtree's value.
		seg[p<<1].lazy += seg[p].lazy; // Update Left subtree's lazy tag.
		seg[p<<1|1].lazy += seg[p].lazy; // Update Right subtree's lazy tag.
		seg[p].lazy = 0; // Clear now tree's lazy tag.
	}
}

void pushup(int p) {
	seg[p].val = seg[p<<1].val + seg[p<<1|1].val;
}

void modify(int p, int l, int r, int tl, int tr, int val) {
	if(l <= tl && r >= tr){
		seg[p].val += val * (tr - tl + 1);
		seg[p].lazy += val;
		return ;
	}
	pushdown(p, tl, tr);
	int mid = (tl + tr) >> 1;
	if(l <= mid)
		modify(p<<1, l, r, tl, mid, val);
	if(r > mid)
		modify(p<<1|1, l, r, mid + 1, tr, val);
	pushup(p);
}

int query(int p, int l, int r, int tl, int tr) {
	if(l <= tl && r >= tr) {
		return seg[p].val;
	}
	pushdown(p, tl, tr);
	int mid = (tl + tr) >> 1;
	int ans = 0;
	if(l <= mid) {
		ans += query(p<<1, l, r, tl, mid);
	}
	if(r > mid) {
		ans += query(p<<1|1, l, r, mid + 1, tr);
	}
	return ans;
}

struct node{
	int l,r;
	mutable int col;
	bool operator <(const node &oth) const {
		return l < oth.l;
	}
};

set<node> tree;
auto split(int pos) {
	if(pos == n + 1)
		return tree.end();
	auto it = tree.lower_bound({pos, 0, 0});
	if(it->l == pos)
		return it;
	--it;
	int l = it->l;
	int r = it->r;
	int c = it->col;
	tree.erase(it);
	tree.insert({l, pos - 1, c});
	return tree.insert({pos, r, c}).first;
}

vector<pii> qwq[MAX_SIZE];
int ans[MAX_SIZE];

void process(int id, int t, int l, int r) {
	auto itr = split(r + 1);
	auto itl = split(l);
	for(auto it = itl; it != itr; ++it) {
		if(!(it->col)) {
			fore(i, it->l, it->r) {
				ans[id] += min(lim[i], t * k[i] + b[i]);
			}
		} else {
			qwq[it->r].push_back({id, min(TIME_LIMIT, t - it->col)});
			if(it->l > 1) {
				qwq[it->l - 1].push_back({-id, min(TIME_LIMIT, t - it->col)});
			}
		}
	}
	tree.erase(itl, itr);
	tree.insert({l, r, t});
}

void solve() {
	n = read();
	fore(i, 1, n) {
		read(b[i],lim[i],k[i]);
	}
	tree.insert({1, n, 0});
	m = read();
	fore(i, 1, m) {
		int t = read();
		int l = read();
		int r = read();
		process(i, t, l, r);
	}
	fore(i, 1, n) {
		if(k[i]) {
			if(k[i] <= lim[i]) {
				int p = min(lim[i] / k[i], TIME_LIMIT);
				modify(1, 1, p, 1, TIME_LIMIT, k[i]);
				if(p < TIME_LIMIT) {
					modify(1, p + 1, p + 1, 1, TIME_LIMIT, lim[i] - p * k[i]);
				}
			} else {
				modify(1, 1, 1, 1, TIME_LIMIT, lim[i]);
			}
		}
		for(auto e : qwq[i]) {
			int id = e.x;
			int t = e.y;
			if(id > 0) {
				ans[id] += query(1, 1, t, 1, TIME_LIMIT);
			} else {
				ans[-id] -= query(1, 1, t, 1, TIME_LIMIT);
			}
		}
	}
	fore(i, 1, m) {
		write(ans[i], '\n');
	}
}

void main() {
//		int T = read();
	int T = 1;
	while (T--) {
		solve();
	}
	return void();
}
```

---

## 作者：_SeeleVollerei_ (赞：0)

对一个上限取 $\min$ 感觉很恶心，所以拿最暴力的分块去搞。

散块暴力搞就行。

整块的话，我们可以把每个东西到达的上限的时间算出来，然后放到块里排序。假设块里上次的接触时间是统一的，那么这次查询会是排序后一段前缀的上限的和，和一段后缀的增长速度的和。由于这些东西是不会变的所以我们预处理即可。然后二分。

不统一怎么办？我们考虑还是直接暴力遍历整个块。因为每次询问至多只会贡献 $O(1)$ 个不整的块。所以这样的复杂度是正确的。

总复杂度是 $O(n\sqrt n\log n)$。可以通过。

https://codeforces.com/contest/453/submission/190186598

发现复杂度瓶颈在二分。

我们发现每次新增的时间如果 $\ge 10^5$，那其实和 $10^5$ 没啥区别。这启发我们对每个块预处理。

直接记录一个 $pre_{p,i}$ 和 $suf_{p,i}$ 表示在块 $p$ 里查询 $i$ 时查询到的前缀和后缀的值即可。

这样理论复杂度为 $O(n\sqrt n)$。但是由于空间问题所以要适当调大块长，最终效率不如 $O(n\sqrt n\log n)$。

https://codeforces.com/contest/453/submission/190189004

---

