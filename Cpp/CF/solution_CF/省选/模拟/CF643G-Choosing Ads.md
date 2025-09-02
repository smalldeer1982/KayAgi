# Choosing Ads

## 题目描述

One social network developer recently suggested a new algorithm of choosing ads for users.

There are $ n $ slots which advertisers can buy. It is possible to buy a segment of consecutive slots at once. The more slots you own, the bigger are the chances your ad will be shown to users.

Every time it is needed to choose ads to show, some segment of slots is picked by a secret algorithm. Then some advertisers are chosen. The only restriction is that it should be guaranteed for advertisers which own at least $ p $ % of slots composing this segment that their ad will be shown.

From the other side, users don't like ads. So it was decided to show no more than ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF643G/456b11767914a81261a6157d843e2701d3225d77.png) ads at once. You are asked to develop a system to sell segments of slots and choose ads in accordance with the rules described above.

## 说明/提示

Samples demonstrate that you actually have quite a lot of freedom in choosing advertisers.

## 样例 #1

### 输入

```
5 9 33
1 2 1 3 3
2 1 5
2 1 5
2 1 3
2 3 3
1 2 4 5
2 1 5
2 3 5
1 4 5 1
2 1 5
```

### 输出

```
3 1 2 3
2 1 3
2 2 1
3 1 1000 1000
1 5
2 5 3
2 1 5```

# 题解

## 作者：小粉兔 (赞：28)

如果 $p = 50 + \varepsilon$ 会怎么样？

这便是一个经典问题：长度为 $n$ 的数列中存在一个出现次数大于 $n / 2$ 的数，设计一个算法找到它。

只要每次删除两个不同的数，最后留下的那个数（或那些数，但这些数全部相同）就是要求的答案。

原理是，如果一个数出现了 $a$ 次，其中 $a > n - a$，则两边都减去 $1$，仍有 $a - 1 > n - a - 1 = (n - 2) - (a - 1)$。

对于拓展情况我们如法炮制，令 $\displaystyle k = \left\lfloor \frac{100}{p} \right\rfloor$。每次删除 $k + 1$ 个数，则对的数一定会留下来。

因为 $k$ 最大就是 $5$，建立一棵线段树，使用每次 $\mathcal O (k^2)$ 的时间合并区间，不难维护答案。

时间复杂度为 $\mathcal O (n k^2 \log n)$，[评测链接](https://codeforces.com/contest/674/submission/72281677)。

---

## 作者：George1123 (赞：16)

[$\Huge\color{#ffa030}{\tt My~Cnblogs}$](https://www.cnblogs.com/Wendigo/p/13026847.html)

---
> [CF643G Choosing Ads](https://www.luogu.com.cn/problem/CF643G)

> $n$ 和 $m$ 和 $p$ 和序列 $a_i(1\le i\le n)$。$m$ 种如下操作：
> 1. ``1 l r id`` 令 $i\in[l,r]:a_i=id$。
> 2. ``2 l r`` 输出至多 $\lfloor\frac{100}{p}\rfloor$ 个数，其中包括所有 $[l,r]$ 区间内出现 $\ge\lceil\frac{p(r-l+1)}{100}\rceil$ 次的 $a_i$。

> 数据范围：$1\le n,m,id,a_i\le 150000$，$20\le p\le 100$，$1\le l\le r\le n$

---
**一眼想法：搞个线段树，节点存该区间出现频率 $\ge\frac{p}{100}$ 的 $a_i$ 值和出现次数存下来，合并。**

**这个做法的依据：** 如果区间 $[l,r]$ 中 $a_i$ 出现频率 $\ge\frac{p}{100}$，$[l,mid]$ 或 $[mid+1,r]$ 必中有一个也满足。

**这个做法的 $\tt bug$：** 若 $a_i$ 存在于 $[l,mid]$ 的节点中而不存在于 $[mid+1,r]$ 的节点中（或反过来），节点的信息难以合并。

于是，我这个思维愚钝的大蒟蒻就没在考场上做出来。

---
这题的正解类似以前的一道经典题：一个序列求**众数（出现频率 $\ge \frac 12$）**，**空间复杂度** 只能 $\Theta(1)$。

做法是记录 $now$ 和 $cnt$。新加入数 $a$ 的时候，如果 $[now=a]$，$cnt++$；如果 $[now\not=a]$，$cnt--$，如果 $[cnt<0]$，$cnt=1$ 并且 $now=a$。

---
这题也类似。出现频率 $\ge\frac{p}{100}$ 的数至多 $\lfloor\frac{100}{p}\rfloor$ 个，所以可以记录 $\lfloor\frac{100}{p}\rfloor$ 个 $now_i$ 和 $cnt_i$。

每次加入 $a$，如果 $[now_i=a]$，$cnt_i++$；如果 $[now_i\not=a]$，$cnt_i--$，如果 $[cnt_i<0]$，$cnt_i=1$ 并且 $now_i=a$。

**这样的话虽然只存了 $\lfloor\frac{100}{p}\rfloor$ 种数，但已经完全反映了区间内数的数量对比，所以节点信息可以直接合并。**

最后每个节点或许会存下不满足出现频率 $\ge\frac{p}{100}$ 的值，但是输出只要包含答案就行了（题中说的）。

---
- **代码**

稍微长了点，但是没有坑人的细节，直接写就好了。

```cpp
#include <bits/stdc++.h>
using namespace std;

//Start
typedef long long ll;
typedef double db;
#define mp(a,b) make_pair(a,b)
#define x first
#define y second
#define b(a) a.begin()
#define e(a) a.end()
#define sz(a) int((a).size())
#define pb(a) push_back(a)
const int inf=0x3f3f3f3f;
const ll INF=0x3f3f3f3f3f3f3f3f;

//Data
const int N=150000;
int n,m,p,pl,a[N+7];

//Segmenttree
typedef vector<pair<int,int>> vpii;
#define mid ((l+r)>>1)
#define ls k<<1,l,mid
#define rs k<<1|1,mid+1,r
int mk[N<<2]; vpii ca[N<<2]; //pair.x 表示 now_i，pair.y 表示 cnt_i
void fill(vpii&v,int id,int c){v.clear(),v.pb(mp(id,c));}
vpii operator+(vpii p,vpii q){ //将 p 中的数一一加入 q
	vpii r;
	for(auto&u:p){
		int ok=0; for(auto&v:q)if(u.x==v.x){v.y+=u.y,ok=1;break;}
		if(ok) continue; q.pb(u); if(sz(q)<=pl) continue;
		int mn=n; for(auto&v:q) mn=min(mn,v.y);
		r.clear(); for(auto&v:q)if(v.y-mn) r.pb(mp(v.x,v.y-mn)); q=r; 
	}
	return q;
}
void down(int k,int l,int r){
	if(!mk[k]) return;
	fill(ca[k<<1],mk[k],mid-l+1),fill(ca[k<<1|1],mk[k],r-mid);
	mk[k<<1]=mk[k<<1|1]=mk[k],mk[k]=0;
}
void build(int k=1,int l=1,int r=n){
	if(l==r) return void(fill(ca[k],a[l],1));
	build(ls),build(rs),ca[k]=ca[k<<1]+ca[k<<1|1];
}
void fix(int x,int y,int z,int k=1,int l=1,int r=n){
	if(x<=l&&r<=y) return void((fill(ca[k],z,r-l+1),mk[k]=z)); down(k,l,r);
	if(mid>=x) fix(x,y,z,ls); if(mid<y) fix(x,y,z,rs);
	ca[k]=ca[k<<1]+ca[k<<1|1];
}
vpii query(int x,int y,int k=1,int l=1,int r=n){
	if(x<=l&&r<=y) return ca[k]; down(k,l,r);
	vpii res; if(mid>=x) res=res+query(x,y,ls); if(mid<y) res=res+query(x,y,rs);
	return res;
}
void Print(int k=1,int l=1,int r=n){ //调试用的，我这个蒟蒻，总是代码写挂
	printf("[%d,%d,%d]:mk=%d\n",k,l,r,mk[k]);
	for(auto&u:ca[k]) printf("(%d,%d)",u.x,u.y);puts("");
	if(l==r) return; down(k,l,r);
	Print(ls),Print(rs);
}

//Main
int main(){
	scanf("%d%d%d",&n,&m,&p),pl=100/p;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]); build();
	for(int i=1;i<=m;i++){
		int o; scanf("%d",&o);
		if(o==1){int l,r,id; scanf("%d%d%d",&l,&r,&id); fix(l,r,id);}
		else {
			int l,r; scanf("%d%d",&l,&r);
			vpii res=query(l,r); printf("%d",sz(res));
			for(auto&u:res) printf(" %d",u.x); puts("");
		}
//		puts("+++++");
//		Print();
//		puts("-----");
	}
	return 0;
}
```
---
**祝大家学习愉快！**

---

## 作者：xtx1092515503 (赞：7)

~~在冬令营上听了各路神仙的详细讲解后还是做不出来的我滚过来水题解了~~

首先，题意可以转化为：输出某个区间中出现次数前$k$多的数。其中$k=\left\lfloor\dfrac{100}{p}\right\rfloor$。因为哪怕输出一些奇奇怪怪的东西也无妨，所以这是正确的。

我们考虑当$k=1$的特例，即$p>50$的情况。我们发现，如果我们每次删除$2$个不同的数，一直删，直到只剩下小于等于$1$个数为止，则剩下的那个数即为答案。因为出现次数最多的数如果出现次数$>50\%$，则一定不会被删光，因为最多只能删去$\left\lfloor\dfrac{n}{2}\right\rfloor$对数，但这个数的出现次数是严格大于$\left\lfloor\dfrac{n}{2}\right\rfloor$次的。

当然，如果最多的数出现次数$\leq 50\%$，那就不好说了，可能会输出奇奇怪怪的东西，不过反正不存在这么个$>50\%$的数，奇奇怪怪就奇奇怪怪吧。

考虑当$k$为任意值时的一般情况。如果我们每次删去$k+1$个不同的数，一直删，直到只剩下小于等于$k$个数为止，剩下的数即为答案。证明同理，因为我们最多只能删去$\left\lfloor\dfrac{n}{k+1}\right\rfloor$组这样的数，而任意一个出现次数$\geq p\%$的数都至少出现了严格大于$\left\lfloor\dfrac{n}{k+1}\right\rfloor$次。

因为$p\geq 20$，所以$k\leq 5$。

我们考虑使用线段树进行区间修改和区间询问。

在线段树的每个节点上，我们维护它代表区间中出现次数前$k$多的数以及它们的出现次数（在进行完删除操作后）。

我们使用```std::vector<pair<int,int>>```维护这些东西。下面的代码中，```pii```指```pair<int,int>```，```vp```指```std::vector<pair<int,int>>```。代码中的$p$即为上文中的$k$。

这是合并操作：

```cpp
bool cmp(const pii &x,const pii &y){
	return x.second>y.second;
}
vp operator +(const vp &x,const vp &y){
	vp z=x;
	for(int i=0;i<y.size();i++){
		bool qwq=false;
		for(int j=0;j<z.size();j++)if(z[j].first==y[i].first){z[j].second+=y[i].second,qwq=true;break;}
		if(!qwq)z.push_back(y[i]);
	}
	sort(z.begin(),z.end(),cmp);
	while(z.size()>=p){
		for(int i=0;i<z.size();i++)z[i].second-=z.rbegin()->second;
		z.pop_back();
	}
	return z;
}
```
其中，first是数，second是出现次数。

我们首先合并所有相同的数；然后，我们把数按照出现次数大小从大到小排序。

```cpp
while(z.size()>=p){
	for(int i=0;i<z.size();i++)z[i].second-=z.rbegin()->second;
	z.pop_back();
}
```


按照这段话的意思，实际每组删去的数不止$p+1$个。但这是正确的，因为如果你一次删数的数量始终$\geq p+1$的话，则最终还是只会删掉$\leq\left\lfloor\dfrac{n}{p+1}\right\rfloor$组数，还是只会保留前$p$大的数。

然后剩下的就是常规线段树操作了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define lson x<<1
#define rson x<<1|1
#define mid ((l+r)>>1)
#define pii pair<int,int>
#define vp vector<pii>
int n,m,p,num[150010],tag[600100];
vp v[600100];
bool cmp(const pii &x,const pii &y){
	return x.second>y.second;
}
vp operator +(const vp &x,const vp &y){
	vp z=x;
	for(int i=0;i<y.size();i++){
		bool qwq=false;
		for(int j=0;j<z.size();j++)if(z[j].first==y[i].first){z[j].second+=y[i].second,qwq=true;break;}
		if(!qwq)z.push_back(y[i]);
	}
	sort(z.begin(),z.end(),cmp);
	while(z.size()>=p){
		for(int i=0;i<z.size();i++)z[i].second-=z.rbegin()->second;
		z.pop_back();
	}
	return z;
}
void build(int x,int l,int r){
	if(l==r){v[x].push_back(make_pair(num[l],1));return;}
	build(lson,l,mid),build(rson,mid+1,r),v[x]=v[lson]+v[rson]; 
}
void change(int x,int l,int r,int val){
	tag[x]=val;
	v[x].clear();
	v[x].push_back(make_pair(val,r-l+1));
}
void pushdown(int x,int l,int r){
	if(!tag[x])return;
	change(lson,l,mid,tag[x]);
	change(rson,mid+1,r,tag[x]);
	tag[x]=0;
}
void modify(int x,int l,int r,int L,int R,int val){
	if(l>R||r<L)return;
	if(L<=l&&r<=R){change(x,l,r,val);return;}
	pushdown(x,l,r),modify(lson,l,mid,L,R,val),modify(rson,mid+1,r,L,R,val),v[x]=v[lson]+v[rson];
} 
vp query(int x,int l,int r,int L,int R){
	if(l>R||r<L)return {};
	if(L<=l&&r<=R)return v[x];
	pushdown(x,l,r);
	return query(lson,l,mid,L,R)+query(rson,mid+1,r,L,R);
}
int main(){
	scanf("%d%d%d",&n,&m,&p),p=(100/p)+1;
	for(int i=1;i<=n;i++)scanf("%d",&num[i]);
	build(1,1,n);
	for(int i=1,t1,t2,t3,t4;i<=m;i++){
		scanf("%d%d%d",&t1,&t2,&t3);
		if(t1==1)scanf("%d",&t4),modify(1,1,n,t2,t3,t4);
		else{
			vp z=query(1,1,n,t2,t3);
			printf("%d ",z.size());
			for(auto j:z)printf("%d ",j.first);puts("");
		}
	}
	return 0;
}
```

---

## 作者：xht (赞：7)

> [CF643G Choosing Ads](https://codeforces.com/contest/643/problem/G)

## 题意

- 给定一个长度为 $n$ 的序列和一个整数 $p$。
- 有 $m$ 个操作，操作要么是区间赋值，要么是询问区间内出现次数至少占 $p\%$ 的数。
- 输出询问的答案时，可以包含错的数，也可以重复输出，但对的数一定要在答案中，且输出的数的个数不超过 $\lfloor \frac{100}{p} \rfloor$。
- $n,m \le 1.5 \times 10^5$，$20 \le p \le 100$。

## 题解

首先考虑 $p > 50$ 的情况，问题变成区间绝对众数。

对于这个问题，我们可以每次同时删除两个不同的数，则最后剩下的互不相同的数最多只有一个，这一个就是答案。

扩展到 $p \le 50$ 的情况也是这样的，我们每次同时删除 $\lfloor \frac{100}{p} \rfloor + 1$ 个互不相同的数，则最后剩下的互不相同的数最多只有 $\lfloor \frac{100}{p} \rfloor$ 个，这些数一定包含了所有答案。

由于 $p \ge 20$，因此 $\lfloor \frac{100}{p} \rfloor \le 5$，合并的部分可以当成常数。

考虑线段树维护序列，时间复杂度 $\mathcal O((n+m) \log n)$。

## 代码

```cpp
const int N = 1.5e5 + 7;
int n, m, p, k, a[N];
struct T {
	int l, r, z;
	vector<pi> c;
} t[N<<2];

inline vector<pi> merge(vector<pi> a, vector<pi> b) {
	for (pi o : b) {
		bool ok = 0;
		for (pi &p : a)
			if (p.fi == o.fi) {
				p.se += o.se, ok = 1;
				break;
			}
		if (ok) continue;
		a.pb(o);
		if ((int)a.size() <= k) continue;
		int x = n;
		for (pi p : a) x = min(x, p.se);
		vector<pi> c;
		for (pi p : a)
			if (p.se - x) c.pb(mp(p.fi, p.se - x));
		a = c;
	}
	return a;
}

void build(int p, int l, int r) {
	t[p].l = l, t[p].r = r;
	if (t[p].l == t[p].r) return t[p].c.pb(mp(a[l], 1)), void();
	build(ls, l, md), build(rs, md + 1, r);
	t[p].c = merge(t[ls].c, t[rs].c);
}

inline void setx(int p, int x) {
	t[p].z = x, t[p].c.clear(), t[p].c.pb(mp(x, t[p].r - t[p].l + 1));
}

inline void spd(int p) {
	if (t[p].z) setx(ls, t[p].z), setx(rs, t[p].z), t[p].z = 0;
}

void change(int p, int l, int r, int x) {
	if (t[p].l >= l && t[p].r <= r) return setx(p, x);
	spd(p);
	if (l <= md) change(ls, l, r, x);
	if (r > md) change(rs, l, r, x);
	t[p].c = merge(t[ls].c, t[rs].c);
}

vector<pi> ask(int p, int l, int r) {
	if (t[p].l >= l && t[p].r <= r) return t[p].c;
	spd(p);
	vector<pi> c;
	if (l <= md) c = ask(ls, l, r);
	if (r > md) c = merge(c, ask(rs, l, r));
	return c;
}

int main() {
	rd(n), rd(m), rd(p), k = 100 / p, rda(a, n);
	build(1, 1, n);
	for (int i = 1, o, l, r, x; i <= m; i++) {
		rd(o), rd(l), rd(r);
		if (o == 1) rd(x), change(1, l, r, x);
		else {
			auto ans = ask(1, l, r);
			print(ans.size(), ' ');
			for (pi o : ans) print(o.fi, ' ');
			prints("");
		}
	}
	return 0;
}
```

---

## 作者：shenmadongdong (赞：7)

这里给出一种乱搞做法。

对于它询问的要求，我们可以发现，其实就是在询问出现次数最多的前 $\lfloor{\frac{100}{p}}\rfloor$ 个数。由于有容错率的设置，我们不用关心它的出现频率是否达到了要求。

这个询问可以考虑用随机化来骗，随机几百次后，将它的出现频率排序，选取最大的几个即可。事实上由于如果有很多个数出现频率相近的话，它大概率要么全部取要么出现频率都没有达到 $p\%$，所以随多次时正确性还是比较有保障的。  

考虑到还存在区间赋值，所以我们需要维护这个序列。如果用线段树维护可以做到 区间赋值 $O(\log n)$ 单点查询 $O(\log n)$，但由于我们需要进行许多次单点查询，这个复杂度显然还不够优。考虑用分块做到 区间赋值 $O(\sqrt{n})$ 单点查询 $O(1)$。

具体用分块怎么维护大家想必都知道吧，整块赋同样的值的时候在上面打个 tag，零散块暴力处理即可。具体实现可以看代码。

~~事实证明有时候随机化还是有前途的~~

代码可能有点丑，不喜勿喷：

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,abm,mmx,avx,avx2")
#pragma GCC optimize("unroll-loops")
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define req(i,a,b) for(int i=(a);i>=(b);--i)
#define rep_(i,a,b) for(int i=(a);i<(b).size();++i)
#define F(a) rep(a,1,n)
#define ll long long
#define Z(a,b) sort(a+1,a+b+1)
using namespace std;
void rd(auto &x){x=0;int f=1;char ch=getchar();while(ch<48||ch>57){if(ch==45)f=-1;ch=getchar();}while(ch>=48&&ch<=57)x=x*10+ch-48,ch=getchar();x*=f;}
//缺省源
int n,m,p,a[150010],bl[150010],tag[10010],sz,op,l,r,x,vis[1500010],cnt[1500010],y;
inline int get(int x){return tag[bl[x]]?tag[bl[x]]:a[x];}//查询
int main()
{
    cin>>n>>m>>p;
    F(i) rd(a[i]);
    sz=sqrt(n);
    F(i) bl[i]=(i-1)/sz+1;
    mt19937_64 rnd(clock());//撒播随机种子,单推mt19937
    rep(_,1,m)
    {
        rd(op),rd(l),rd(r);
        if (op==1)
        {
            rd(x);
            int L=bl[l],R=bl[r];
            if (tag[L]) rep(i,L*sz-sz+1,L*sz) a[i]=tag[L];
            if (tag[R]) rep(i,R*sz-sz+1,R*sz) a[i]=tag[R];//tag下放
            tag[L]=tag[R]=0;//零散块tag清零
            rep(i,L+1,R-1) tag[i]=x;//整块打tag
            if (L!=R)
            {
                rep(i,l,L*sz) a[i]=x;
                rep(i,R*sz-sz+1,r) a[i]=x;
            }
            else rep(i,l,r) a[i]=x;//零散块暴力处理
        }//分块维护
        if (op==2)
        {
            y++;
            pair<int,int> A[1310];
            int tot=0,pq,qp[1310];
            rep(i,1,678)//如果松一点的话这里可以多rand几次 
            {
                pq=get(rnd()%(r-l+1)+l);
                if (vis[pq]!=y) vis[pq]=y,cnt[pq]=0,qp[++tot]=pq;
                cnt[pq]++;
            }//随机化统计次数
            rep(i,1,tot) A[i]={cnt[qp[i]],qp[i]};
            Z(A,tot);
            reverse(A+1,A+tot+1);
            rep(i,1,5) A[tot+i].second=A[tot].second;//防止总数不足100/p
            cout<<100/p<<' ';
            rep(i,1,100/p) cout<<A[i].second<<' ';
            putchar(10);//进行处理并输出
        }
    }
    return 0;
}
//这份代码不一定能一遍过，实在不行的话可以多交几发
```

---

## 作者：mrsrz (赞：5)

[可能更好的体验](https://mrsrz.github.io/2020/01/15/CF643G/)

以下是一种分块做法。

对原数列进行分块，并对值域进行分块。我们记录 $tot[i][k]$ 表示**前** $i$ 个块中，$k$ 的出现次数（分块前缀和思想）。并用一个数组记录每个块中出现过的元素。

用 set 维护所有**总**出现次数达到 $20\%S$（$S$ 为块大小，下同）的数。

对修改操作，边角直接暴力修改，整块的直接打修改标记。然后我们提取出所有出现次数产生变化的数值，对这些数值的前缀和数组暴力进行修改。单次求前缀和的复杂度是 $O(\frac n S)$ 的，但由于修改操作是区间赋值，所以重新求前缀和的总次数是 $O(n+m)$，复杂度均摊正确。

对查询操作，如果区间比较小，可以直接暴力求以减小常数。区间比较大时采用另外方法。

由于我们已经用 set 记录了**总**出现次数达到 $20\%S$（$S$ 为块大小，下同）的数，这样的数最多 $\frac {5n} S$ 个，我们需要对每个数，$O(1)$ 求其在区间内的出现次数。这些数在边角的出现次数，我们可以用一遍 $O(S)$ 的扫描求出对于全部数的出现次数。而在块间的出现次数，我们可以通过分块前缀和数组相减 $O(1)$ 求得。

不考虑 $20\%$ 带来的常数影响，容易得到当 $S=\sqrt n$ 时复杂度最优，为 $O((n+m)\sqrt n)$。

## Code：
```cpp
#include<cstdio>
#include<cctype>
#include<algorithm>
#include<set>
#include<ctime>
const int N=1.6e5,siz=600,M=N/siz+2,K=siz*2/5;
std::set<int>st;
char buf[(int)1e8],*ss=buf;
inline void init(){buf[fread(buf,1,(int)1e8-1,stdin)]='\n',fclose(stdin);}
inline int readint(){
	int d=0;
	while(!isdigit(*ss))++ss;
	while(isdigit(*ss))d=d*10+(*ss++^'0');
	return d;
}
#define bel(x)((x-1)/siz+1)
int n,m,p,a[N];
int L[M],R[M],blocks,sta[N],top,vis[N],tag[M];
int STA[M][siz+2],TP[N],cnt[N];
int sum[N][M];
int pre[N][M];
inline void prefix(int id){
	st.erase(id);
	int*sum=::sum[id];int*pre=::pre[id];
	for(int i=1;i<=blocks;++i)
	pre[i]=pre[i-1]+sum[i];
	if(pre[blocks]>=K)st.insert(id);
}
inline void pushdown(int id){
	const int v=tag[id];
	tag[id]=0;
	TP[id]=1;
	STA[id][1]=v;
	for(int i=L[id];i<=R[id];++i)a[i]=v;
}
inline void rebuild(int id){
	int*s=STA[id],&top=TP[id];
	top=0;
	for(int i=L[id];i<=R[id];++i)if(!vis[a[i]])vis[a[i]]=1,s[++top]=a[i];
	for(int i=1;i<=top;++i)vis[s[i]]=0;
}
struct ostream{
	char buf[15000005],*s;
	inline ostream(){s=buf;}
	inline ostream&operator<<(int d){
		if(!d){
			*s++='0';
		}else{
			static int w;
			for(w=1;w<=d;w*=10);
			for(;w/=10;d%=w)*s++=d/w^'0';
		}
		return*this;
	}
	inline ostream&operator<<(const char&c){*s++=c;return*this;}
	inline void flush(){
		fwrite(buf,1,s-buf,stdout);
		s=buf;
	}
	inline~ostream(){flush();}
}cout;
int main(){
	init();
	n=readint(),m=readint(),p=readint();
	blocks=bel(n);
	for(int i=1;i<=blocks;++i)L[i]=R[i-1]+1,R[i]=i*siz;R[blocks]=n;
	for(int i=1;i<=n;++i){
		a[i]=readint();
		++sum[a[i]][bel(i)];
	}
	for(int i=1;i<=n;++i)prefix(i);
	for(int x=1;x<=blocks;++x)rebuild(x);
	while(m--){
		if(readint()==1){
			int l=readint(),r=readint(),x=readint();
			const int bL=bel(l),bR=bel(r);
			if(bL==bR){
				if(tag[bL])pushdown(bL);
				top=0;
				for(int i=l;i<=r;++i){
					--sum[a[i]][bL];
					if(!vis[a[i]])vis[a[i]]=1,sta[++top]=a[i];
					++sum[a[i]=x][bL];
				}
				if(!vis[x])sta[++top]=x;
				for(int i=1;i<=top;++i)vis[sta[i]]=0,prefix(sta[i]);
				rebuild(bL);
			}else{
				if(tag[bL])pushdown(bL);
				top=0;
				for(int i=R[bL];i>=l;--i){
					--sum[a[i]][bL];
					if(!vis[a[i]])vis[a[i]]=1,sta[++top]=a[i];
					++sum[a[i]=x][bL];
				}
				if(tag[bR])pushdown(bR);
				for(int i=L[bR];i<=r;++i){
					--sum[a[i]][bR];
					if(!vis[a[i]])vis[a[i]]=1,sta[++top]=a[i];
					++sum[a[i]=x][bR];
				}
				for(int i=bL+1;i<bR;++i){
					if(tag[i]){
						sum[tag[i]][i]=0;
						if(!vis[tag[i]])vis[tag[i]]=1,sta[++top]=tag[i];
					}else{
						const int*s=STA[i],&tp=TP[i];
						for(int j=1;j<=tp;++j){
							sum[s[j]][i]=0;
							if(!vis[s[j]])vis[s[j]]=1,sta[++top]=s[j];
						}
					}
					sum[x][i]=R[i]-L[i]+1;
					tag[i]=x;
				}
				if(!vis[x])sta[++top]=x;
				for(int i=1;i<=top;++i)vis[sta[i]]=0,prefix(sta[i]);
				rebuild(bL),rebuild(bR);
			}
		}else{
			int l=readint(),r=readint();
			if(l>r)continue;
			const int LEN=r-l+1,C=LEN*p/100+!!(LEN*p%100),bL=bel(l),bR=bel(r);
			int ans[15],tans=0;
			if(r-l+1<=3*siz){
				top=0;
				for(int i=l;i<=r;++i){
					const int x=tag[bel(i)]?tag[bel(i)]:a[i];
					if(!vis[x])sta[++top]=x;
					++vis[x];
				}
				for(int i=1;i<=top;++i)
				if(vis[sta[i]]>=C)ans[++tans]=sta[i];
				if(tans)
				std::sort(ans+1,ans+tans+1);
				cout<<tans<<' ';
				for(int i=1;i<=tans;++i)
				cout<<ans[i]<<' ';
				cout<<'\n';
				for(int i=1;i<=top;++i)vis[sta[i]]=0;
			}else{
				top=0;
				if(tag[bL])pushdown(bL);
				if(tag[bR])pushdown(bR);
				for(int i:st)
				if(!vis[i])vis[i]=1,sta[++top]=i;
				for(int i=R[bL];i>=l;--i){
					if(!vis[a[i]])vis[a[i]]=1,sta[++top]=a[i];
					++cnt[a[i]];
				}
				for(int i=L[bR];i<=r;++i){
					if(!vis[a[i]])vis[a[i]]=1,sta[++top]=a[i];
					++cnt[a[i]];
				}
				for(int i=1;i<=top;++i){
					cnt[sta[i]]+=pre[sta[i]][bR-1]-pre[sta[i]][bL];
					if(cnt[sta[i]]>=C)ans[++tans]=sta[i];
				}
				if(tans)
				std::sort(ans+1,ans+tans+1);
				cout<<tans<<' ';
				for(int i=1;i<=tans;++i)
				cout<<ans[i]<<' ';
				cout<<'\n';
				for(int i=1;i<=top;++i)
				cnt[sta[i]]=vis[sta[i]]=0;
			}
		}
	}
//	fprintf(stderr,"%.3f\n",1.*clock()/CLOCKS_PER_SEC);
	return 0;
}
```

---

## 作者：wind_whisper (赞：4)

## $\text{Description}$
给定一个长度为 $n$ 的序列和一个整数 $p$。
- 有 $m$ 个操作，操作要么是区间赋值，要么是询问区间内出现次数至少占 $p\%$ 的数。
- 输出询问的答案时，可以包含错的数，也可以重复输出，但对的数一定要在答案中，且输出的数的个数不超过 $\lfloor \dfrac{100}{p} \rfloor$。
- $n,m \le 1.5 \times 10^5$，$20 \le p \le 100$。
## $\text{Solution}$
魔法操作。  
考虑 $p>50$ （严格众数）时如何做。  
每次删去两个不同的数，直到删到剩下的种类不超过一种时，如果有严格众数，显然会剩到最后。 

类似的，推广到 $p\ge 20$ 的情况。令 $k=\lfloor \dfrac{100}{p}\rfloor$，每次删去 $k+1$ 个不同的数，直到不能删为止，也易证如果有符合条件的数最后一定会剩下。  
现在要对于区间询问快速模拟这个过程，使用线段树即可，每次暴力 $O(k^2)$ 暴力合并区间，具体实现建议观看代码。  
## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=2e5+100;
#define ll long long
#define ui unsigned int
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)) {x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}

int n,k,m;

struct node{
  int val[6],num[6],tot;
}tr[N<<2];
node operator + (const node &a,const node &b){
  node res=a;
  for(int i=1;i<=b.tot;i++){
    bool jd(0);
    for(int j=1;j<=res.tot;j++){
      if(res.val[j]==b.val[i]){
	jd=1;res.num[j]+=b.num[i];break;
      }
    }
    if(jd) continue;
    if(res.tot<k){
      ++res.tot;res.val[res.tot]=b.val[i];res.num[res.tot]=b.num[i];
      continue;
    }
    int pl(1);
    for(int j=2;j<=res.tot;j++){
      if(res.num[j]<res.num[pl]) pl=j;
    }
    if(res.num[pl]>b.num[i]){
      for(int j=1;j<=res.tot;j++) res.num[j]-=b.num[i];
    }
    else{
      int o=res.num[pl];
      res.num[pl]=b.num[i];res.val[pl]=b.val[i];
      for(int j=1;j<=res.tot;j++) res.num[j]-=o;
    }
  }
  return res;
}

#define mid ((l+r)>>1)
#define ls (k<<1)
#define rs (k<<1|1)
int laz[N<<2];
inline void pushup(int k){tr[k]=tr[ls]+tr[rs];}
inline void tag(int k,int l,int r,int v){
  laz[k]=v;tr[k].tot=1;tr[k].num[1]=r-l+1;tr[k].val[1]=v;
  return;
}
inline void pushdown(int k,int l,int r){
  int o=laz[k];laz[k]=0;
  if(!o) return;
  tag(ls,l,mid,o);tag(rs,mid+1,r,o);
  return;
}
inline void change(int k,int l,int r,int x,int y,int v){
  if(x<=l&&r<=y){
    tag(k,l,r,v);return;
  }
  pushdown(k,l,r);
  if(x<=mid) change(ls,l,mid,x,y,v);
  if(y>mid) change(rs,mid+1,r,x,y,v);
  pushup(k);
}
node ask(int k,int l,int r,int x,int y){  
  if(x<=l&&r<=y) return tr[k];
  pushdown(k,l,r);
  if(y<=mid) return ask(ls,l,mid,x,y);
  else if(x>mid) return ask(rs,mid+1,r,x,y);
  else{
    node a=ask(ls,l,mid,x,y),b=ask(rs,mid+1,r,x,y);
    return a+b;
  }
}
int a[N];
void build(int k,int l,int r){
  if(l==r){
    tr[k].tot=1;tr[k].num[1]=1;tr[k].val[1]=a[l];
    return;
  }
  build(ls,l,mid);build(rs,mid+1,r);
  pushup(k);
}

signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();m=read();k=100/read();
  for(int i=1;i<=n;i++) a[i]=read();
  build(1,1,n);
  for(int i=1;i<=m;i++){
    int op=read(),l=read(),r=read();
    if(op==1){
      int x=read();
      change(1,1,n,l,r,x);
    }
    else{
      node res=ask(1,1,n,l,r);
      printf("%d ",res.tot);
      for(int j=1;j<=res.tot;j++) printf("%d ",res.val[j]);
      putchar('\n');
    }
  }
  return 0;
}
/*
*/

```


---

## 作者：cirnovsky (赞：3)

## 题意简述

够简单了。

## 题解

我觉得很有意思的一道题目。

第一个操作，嗯，不讲。

我们着重来看看第二个操作。

这个查询操作要我们输出所有出现次数的频率 $\ge p\%$ 的数字。

先考虑一种特殊情况，即当 $p>50$ 的情况，这时候这个问题的本质就成了求区间的绝对众数。

区间绝对众数有一个经典的 $\Theta(1)$ 空间的做法，摩尔投票。

这里简单介绍一下摩尔投票法。

举个例子，序列 $\texttt{7 5 7 6 7 7 4 7}$。

我们定义两个变量 `major,cnt`。

我们遍历一遍序列：

起初 `major=7,cnt=1`。

然后 $5\neq 7$，`cnt--`。

此时 `cnt==0`，我们令 `major=5,cnt=1`。

后面以此类推。

那么拓展到这道题目，我们的 `p` 最小是 20。

和普通的摩尔投票法类似，我们把 `major,cnt` 替换为 `major[5],cnt[5]`，用数组来求出分别的众数。

不过这样做有可能会出现出现频率不符合答案规范的数存进来，不过反正良心出题人允许我们输出无意义内容，所以就不用管了。

然后考虑用一个数据结构来加速这个过程。

区间推平、查询首选线段树。

那么要维护的信息就很明显了。

每个结点维护一个摩尔投票的结构体，然后再维护一个区间推平的 `tag`。

最后 `pushup` 合并左右儿子贡献时，直接把右区间合并到左边来即可。

下传标记很简单，不过要注意下传时因为时区间推平，所以摩尔投票的结构体里的 `cnt` 部分要设为 `r-l+1`。

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <assert.h>

using namespace std;

const int Maxn = 15e4 + 5;
int n, m, p, isa[Maxn];
struct Major_Voting // 摩尔投票的结构体
{
	int major[5], cnt[5];
	Major_Voting()
	{
		memset(major, 0, sizeof(major));
		memset(cnt, 0, sizeof(cnt));
	}
};
struct Segment_Tree
{
	Major_Voting val;
	int tag;
} t[Maxn << 2];

Major_Voting make_vote(int major) // 以 major 为关键字创建一个新的摩尔投票
{
	Major_Voting ret;
	memset(ret.major, 0, sizeof(ret.major));
	memset(ret.cnt, 0, sizeof(ret.cnt));
	ret.major[0] = major;
	ret.cnt[0] = 1;
	return ret;
}

Major_Voting merge(Major_Voting one, Major_Voting ano) // 合并区间，这一步的细节较多
{
	Major_Voting ret = one;
	for (int i = 0; i < p; ++i)
	{
		if (ano.cnt[i])
		{
			bool flag = 0;
			for (int j = 0; j < p; ++j)
			{
				if (ret.major[j] == ano.major[i])
				{
					ret.cnt[j] += ano.cnt[i];
					flag = 1;
					break;
				}
			}
			if (flag == 0)
			{
				for (int j = 0; j < p; ++j)
				{
					if (ret.cnt[j] == 0)
					{
						ret.major[j] = ano.major[i];
						ret.cnt[j] = ano.cnt[i];
						flag = 1;
						break;
					}
				}
			} // 把右区间的贡献算到左边来
			if (flag)	continue;
			int line = 2e9;
			for (int j = 0; j < p; ++j)	line = min(line, ret.cnt[j]);
			if (line >= ano.cnt[i])
			{
				for (int j = 0; j < p; ++j) 	ret.cnt[j] -= ano.cnt[i];
				continue;
			}
			bool book = 0;
			for (int j = 0; j < p; ++j)
			{
				if (ret.cnt[j] == line && book == 0)
				{
					ret.major[j] = ano.major[i];
					ret.cnt[j] = ano.cnt[i] - line;
					book = 1;
				}
				else	ret.cnt[j] -= line;
			} // 分类讨论最小值的处理
		}
	}
	return ret;
}

void maintain(int p)
{
	t[p].val = merge(t[p << 1].val, t[p << 1 | 1].val);
}


void spread(int p, int l, int r)
{
	if (t[p].tag)
	{
		int mid = (l + r) >> 1;
		t[p << 1].tag = t[p].tag;
		t[p << 1 | 1].tag = t[p].tag;
		t[p << 1].val = make_vote(t[p].tag);
		t[p << 1].val.cnt[0] = mid - l + 1;
		t[p << 1 | 1].val = make_vote(t[p].tag);
		t[p << 1 | 1].val.cnt[0] = r - mid;
		t[p].tag = 0;
	}
}

void build(int p, int l, int r)
{
	if (l == r)
	{
		t[p].val = make_vote(isa[l]);
		return ;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	maintain(p);
}

void change(int p, int l, int r, int x, int y, int v)
{
	if (l > y || r < x) 	return ;
	if (l >= x && r <= y)
	{
		t[p].tag = v;
		t[p].val = make_vote(v);
		t[p].val.cnt[0] = r - l + 1;
		return ;
	}
	int mid = (l + r) >> 1;
	spread(p, l, r);
	if (mid >= x)	change(p << 1, l, mid, x, y, v);
	if (mid < y)	change(p << 1 | 1, mid + 1, r, x, y, v);
	maintain(p);
}

Major_Voting query(int p, int l, int r, int x, int y)
{
	if (l > y || r < x) 	return make_vote(0);
	if (l >= x && r <= y)	return t[p].val;
	int mid = (l + r) >> 1;
	Major_Voting ret;
	spread(p, l, r);
	if (mid >= x)	ret = merge(ret, query(p << 1, l, mid, x, y));
	if (mid < y)	ret = merge(ret, query(p << 1 | 1, mid + 1, r, x, y));
	return ret;
} // 以上板子

signed main()
{
	scanf("%d %d %d", &n, &m, &p);
	assert(p >= 20 && p <= 100);
	p = 100 / p;
	for (int i = 1; i <= n; ++i)	scanf("%d", &isa[i]);
	build(1, 1, n);
	for (int i = 0, t, l, r, x; i < m; ++i)
	{
		scanf("%d %d %d", &t, &l, &r);
		if (t == 1)
		{
			scanf("%d", &x);
			change(1, 1, n, l, r, x);
		}
		else
		{
			Major_Voting ans = query(1, 1, n, l, r);
			printf("%d", p);
			for (int i = 0; i < p; ++i) 	printf(" %d", ans.major[i]); // 因为题目的特殊性，我们可以随便乱输出
			putchar('\n');
		}
	}
	return 0;
}
```

---

## 作者：EXODUS (赞：1)

# Part 1：前言
题解区出现了错误的随机化做法，在吃饭的时候想到了一个正确的，所以来补一个题解。

感谢 绝顶我为峰，275307894a 和 RainAir 三位大跌的帮助。

# Part 2：正文
首先来看看 shenmadongdong 这位老哥的题解。
>这个询问可以考虑用随机化来骗，随机几百次后，将它的出现频率排序，选取最大的几个即可。事实上由于如果有很多个数出现频率相近的话，它大概率要么全部取要么出现频率都没有达到 $p\%$，所以随多次时正确性还是比较有保障的。

很遗憾，这个的正确性并不高，反例是 huzhaoyang 在其评论区中给出的样例。在这个样例下，随机 $B$ 次后，选择 $k$ 次 $1$ 的概率是 $\binom{k}{B}(0.51)^k\times(0.49)^{1-k}$，那么正确的概率是 $\sum\limits_{k=\frac{B}{2}}^B\binom{k}{B}(0.51)^k\times(0.49)^{B-k}$。我不会展开这个和式，但国王饮水记的高精度小数告诉我这个东西的概率在 $B=1000$ 时是 $0.74$。我用 shenmadongdong 老哥的代码调到 1000 跑了一下，1000 组询问中只有 716 组是正确的结果，看起来吻合的还是比较好的。

那么，我们应该怎么用随机化正确的做出这个题？

考虑沿用 [CF840D](https://www.luogu.com.cn/problem/CF840D) 一题的做法。那么我们考虑现在随机 $B$ 次，每次检查当前随到的这个数是否满足题意。

那么现在变成了一个数据结构问题，支持两种操作，分别为：

- 区间推平。
- 区间求某个数字出现次数。

ODT。考虑拿 ODT 维护颜色连续段。开动态开点线段树维护一下每个颜色在该区间的出现次数。对于修改，暴力枚举 ODT 中的颜色段，对应的在线段树上修改，查询直接查。

分析一下复杂度。每次修改操作至多使颜色段增加一个，而每遍历到一个颜色段会让颜色段数量减一，故修改的均摊复杂度是 $O(q\log n)$ 的，这与 ODT 的复杂度分析相同。询问的复杂度是线段树的 $O(qB\log n)$。

再分析正确性，最极端的样例大概是 $p=21$，然后给出 $21$ 个 $1,2,3,4$ 和 $16$ 个 $5$。这样的话错误率是 $(0.79)^B$ 的。取 $B=100$，错误率是 $10^{-10}$ 级别的。这样看起来还是比较有保证的。

有一些细节，放在下面。

- ODT 最好先分裂右端点再分裂左端点，否则好像会出现 ub。
- 在随机位置求颜色的时候，不要在 ODT 中 upper_bound 再求前驱，而是再开一颗线段树维护颜色。不知道为什么 upper_bound 非常慢，也有我写挂的可能。

# Part 3：代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,l,r) for(int i(l);i<=(r);++i)
#define per(i,r,l) for(int i(r);i>=(l);--i)
#define eb emplace_back
#define Debug(...) fprintf(stderr,__VA_ARGS__)
#pragma GCC optimize(3)
namespace io {
	const int __SIZE = (1 << 22) + 1;
	char ibuf[__SIZE], *iS, *iT, obuf[__SIZE], *oS = obuf, *oT = oS + __SIZE - 1, __c, qu[55]; int __f, qr, _eof;
	#define Gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, __SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	inline void flush () { fwrite (obuf, 1, oS - obuf, stdout), oS = obuf; }
	inline void gc (char &x) { x = Gc(); }
	inline void pc (char x) { *oS ++ = x; if (oS == oT) flush (); }
	inline void pstr (const char *s) { int __len = strlen(s); for (__f = 0; __f < __len; ++__f) pc (s[__f]); }
	inline void gstr (char *s) { for(__c = Gc(); __c < 32 || __c > 126 || __c == ' ';)  __c = Gc();
		for(; __c > 31 && __c < 127 && __c != ' ' && __c != '\n' && __c != '\r'; ++s, __c = Gc()) *s = __c; *s = 0; }
	template <class I> inline bool read (I &x) { x = _eof = 0;
		for (__f = 1, __c = Gc(); (__c < '0' || __c > '9') && !_eof; __c = Gc()) { if (__c == '-') __f = -1; _eof |= __c == EOF; }
		for (x = 0; __c <= '9' && __c >= '0' && !_eof; __c = Gc()) x = x * 10 + (__c & 15), _eof |= __c == EOF; x *= __f; return !_eof; }
	template <class I> inline void print (I x) { if (!x) pc ('0'); if (x < 0) pc ('-'), x = -x;
		while (x) qu[++ qr] = x % 10 + '0',  x /= 10; while (qr) pc (qu[qr --]); }
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
} using io::pc; using io::gc; using io::pstr; using io::gstr; using io::read; using io::print;
template<typename T,typename... Args>
void read(T &x,Args &...args){read(x),read(args...);}
const int N=15e4+7,B=100;
mt19937 g(chrono::steady_clock::now().time_since_epoch().count());
int n,Q,P;
int a[N],mrk[N];
struct SegT{
#define ls(k) t[k].ls
#define rs(k) t[k].rs
	struct node{
		int ls,rs,siz,tag;
	}t[N*150];
	int rt[N],tot;
	void chg(int k,int v){t[k].tag+=v;}
	void update(int l,int r,int &k,int ql,int qr,int v){
		if(!k)k=++tot;
		t[k].siz+=(qr-ql+1)*v;
		// Debug("%d %d %d %d %d %d\n",l,r,k,ql,qr,v);
		if(ql==l&&r==qr)return chg(k,v);
		int mid=(l+r)>>1;
		if(ql<=mid){
			if(mid<qr)update(l,mid,ls(k),ql,mid,v),update(mid+1,r,rs(k),mid+1,qr,v);
			else update(l,mid,ls(k),ql,qr,v);
		}else if(mid<qr)update(mid+1,r,rs(k),ql,qr,v);
	}
	int query(int l,int r,int k,int ql,int qr,int flg){
		// Debug("%d %d %d %d %d %d %d %d\n",l,r,k,ql,qr,flg,t[k].tag,t[k].siz);
		if(!k&&!flg)return 0;
		if(!k)k=++tot;
		if(ql==l&&r==qr)return t[k].siz+flg*(r-l+1);
		int mid=(l+r)>>1,res=0;flg+=t[k].tag;
		if(ql<=mid){
			if(mid<qr)res=query(l,mid,ls(k),ql,mid,flg)+query(mid+1,r,rs(k),mid+1,qr,flg);
			else res=query(l,mid,ls(k),ql,qr,flg);
		}else if(mid<qr)res=query(mid+1,r,rs(k),ql,qr,flg);
		return res;
	}
	int query(int l,int r,int col){
		return query(1,n,rt[col],l,r,0);
	}
#undef ls
#undef rs
}sgt;
struct SegT2{
#define ls(k) ((k)<<1)
#define rs(k) (((k)<<1)|1)
	struct node{int val,tag;}t[N<<2];
	void build(int l,int r,int k){
		if(l==r)return t[k].val=a[l],void();
		int mid=l+r>>1;
		build(l,mid,ls(k));
		build(mid+1,r,rs(k));
	}
	void push_down(int k){
		if(!t[k].tag)return;
		t[ls(k)].val=t[rs(k)].val=t[ls(k)].tag=t[rs(k)].tag=t[k].tag;
		t[k].tag=0;
	}
	void update(int l,int r,int k,int ql,int qr,int c){
		if(ql<=l&&r<=qr)return t[k].val=t[k].tag=c,void();
		int mid=l+r>>1;push_down(k);
		if(ql<=mid)update(l,mid,ls(k),ql,qr,c);
		if(mid<qr)update(mid+1,r,rs(k),ql,qr,c);
	}
	int query(int l,int r,int k,int p){
		if(l==r)return t[k].val;
		int mid=l+r>>1;push_down(k);
		if(p<=mid)return query(l,mid,ls(k),p);
		else return query(mid+1,r,rs(k),p);
	}
#undef ls
#undef rs
}csgt;
struct Odt{
	struct node{
		int l,r;
		int col;
		node(int _l,int _r,int _col):l(_l),r(_r),col(_col){}
		bool operator<(const node &rhs)const{return l<rhs.l;};
	};
	set<node>s;
	void build(){
		for(int l=1,r=1;l<=n;l=r){
			while(a[r]==a[l]&&r<=n)r++;
			s.insert(node(l,r-1,a[l]));
			sgt.update(1,n,sgt.rt[a[l]],l,r-1,1);
		}
		// for(auto [l,r,c]:s)Debug("%d %d %d\n",l,r,c);
	}
	set<node>::iterator split(int x){
		// Debug("%d\n",x);
		auto it=s.lower_bound({x,0,0});
		if(it!=s.end()&&it->l==x)return it;
		it=prev(it);
		auto [l,r,v]=*it;
		s.erase(it);
		s.insert({l,x-1,v});
		return s.insert({x,r,v}).first;
	}
	void assign(int l,int r,int c){
		auto ed=split(r+1),bg=split(l);
		for(auto i=bg;i!=ed;++i){
			// Debug("%d %d %d\n",i->l,i->r,i->col);
			sgt.update(1,n,sgt.rt[i->col],i->l,i->r,-1);
		}
		s.erase(bg,ed);s.insert({l,r,c});sgt.update(1,n,sgt.rt[c],l,r,1);
	}
	int query(int p){
		auto it=prev(s.upper_bound({p,(int)1e9,(int)1e9}));
		return it->col;
	}
}odt;
int main(){
	read(n,Q,P);
	for(int i=1;i<=n;i++)read(a[i]);
	odt.build();csgt.build(1,n,1);
	for(int q=1;q<=Q;q++){
		// Debug("==========%d==========\n",q);
		// for(auto [l,r,c]:odt.s)Debug("%d %d %d\n",l,r,c);
		int op;read(op);
		if(op==1){
			int l,r,c;read(l,r,c);
			odt.assign(l,r,c);
			csgt.update(1,n,1,l,r,c);
		}else if(op==2){
			int l,r;read(l,r);
			uniform_int_distribution<>rng(l,r);
			vector<int>ans;
			for(int _=1;_<=B;_++){
				int c=csgt.query(1,n,1,rng(g));
				if(mrk[c]==q)continue;
				mrk[c]=q;
				// Debug("%d %d\n",c,sgt.query(l,r,c));
				if(sgt.query(l,r,c)>=((r-l+1)*P-1)/100+1)ans.eb(c);
				// Debug("\n");
			}
			print((int)ans.size()),pc(' ');
			for(auto x:ans)print(x),pc(' ');
			pc('\n');
		}
	}
	fflush(stdout);
	return 0;
}
```
# Part 4：后文
![](https://cdn.luogu.com.cn/upload/image_hosting/izkxvq0j.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/msj8wfbo.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/buy7kyqw.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/78d0hn2b.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/u5h0vc94.png)
超级小丑。

---

## 作者：tzc_wk (赞：1)

[Codeforces 题目传送门](https://codeforces.com/contest/643/problem/G) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF643G)

首先考虑 $p>50$ 的时候怎么处理，也就是求一个区间的**绝对众数**。我们知道众数这个东西是不能用线段树直接维护的，因为对于区间 $[l,r]$ 和 $x\in [l,r)$，区间 $[l,r]$ 的众数不一定是 $[l,x]$ 的众数或 $[x+1,r]$ 的众数。

不过此题有一个特殊之处，就是我们要求区间的**绝对众数**而不是区间的众数。这时候就可以用线段树维护了，因为区间 $[l,r]$ 的绝对众数一定至少是区间 $[l,x],[x+1,r]$ 中某个区间的绝对众数（提示：反证法）。

于是我们考虑这样一个思路，对于 $[l,r]$ 中的所有数组成一个可重集 $S$，每次选择两个数 $x,y\in S$ 且 $x\ne y$ 并将 $x,y$ 从 $S$ 中删除，直到 $S=\varnothing$ 或 $S$ 中所有数都相同为止。不难发现在任意时刻，原区间中的绝对众数还是 $S$ 中的绝对众数，因为对于 $[l,r]$ 中的绝对众数 $z$，我们设其出现次数为 $c$，若删去的两数满足 $x\ne z\land y\ne z$，那么删去 $x,y$ 后还剩 $n-2$ 个数，其中 $z$ 出现的次数为 $c$，$c>\lfloor\dfrac{n}{2}\rfloor>\lfloor\dfrac{n-2}{2}\rfloor$；若删去的两数满足 $x=z\lor y=z$，那么删去 $x,y$ 后 $z$ 出现的次数为 $c-1$，由 $c>\lfloor\dfrac{n}{2}\rfloor$ 知 $c-1>\lfloor\dfrac{n-2}{2}\rfloor$。我们建一棵线段树，区间 $[l,r]$ 表示的节点上维护两个值 $x,y$，$x$ 为将 $[l,r]$ 中所有数压入 $S$ 后对 $S$ 进行上文所说的操作后 $S$ 中剩余的数，如果最终 $S=\varnothing$ 则该值为 $0$，$y$ 是删完后 $x$ 的出现次数，合并两个区间 $[l,r]$ 时就将两个子区间的 $y$ 值作比较，并令当前区间的 $x$ 为两个子区间的 $y$ 值较大的 $x$，$y$ 值为两个子区间的 $y$ 值相减即可。

到这里你可能会有疑惑，那就是任意时刻 $x$ 为 $S$ 中的绝对众数并不是 $x$ 为原区间的绝对众数的**充要条件**，它仅仅只是**必要条件**。也就是说有可能出现最终留下的数不是原区间的绝对众数。但是注意到题目中有个奇奇怪怪的条件，叫做“输出的数中可以包含错误的数，但正确的数必须包含在输出中，并且输出的数不能超过 $\lfloor\dfrac{100}{p}\rfloor$”，在上述算法中我们最多输出一个数，并且可以保证若 $[l,r]$ 存在绝对众数，那么其绝对众数一定被输出，故这样是符合题意。

接下来考虑原题。我们记 $k=\lfloor\dfrac{100}{p}\rfloor$。由于 $p\geq 20$，一定有 $k\leq 5$，也就是说我们最多输出 $5$ 个数。我们还是考虑之前的算法，只不过把“每次删除 $2$ 个数”改为“每次删除 $k+1$ 个数”，然后用一个 ```std::vector<pair<int,int> >``` 维护该区间中的数执行上述操作后剩余的数，以及它们的出现次数。合并时候就暴力合并左右子区间的 ```vector```，取出现次数最大的 $k$ 个数即可。借鉴上面的分析可知输出的数仍可能包含错误的数，但正确的数一定被包含在答案中。

时间复杂度 $nk^2\log n$，其中 $k_{\max}=5$

不过似乎 ```std::vector<pair<int,int> >``` 常数有亿点点大？或许是 wtcl 罢，用 ```std::vector<pair<int,int> >``` 实现的代码 TLE 50 了，故这里是用结构体实现的代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int MAXN=1.5e5;
const int INF=0x3f3f3f3f;
int n,qu,p,a[MAXN+5];
struct seq{
	int cnt,x[8],y[8];
	seq(){cnt=0;fill0(x);fill0(y);}
};
struct node{int l,r,lz;seq v;} s[MAXN*4+5];
seq merge(seq a,seq b){
	for(int i=1;i<=b.cnt;i++){
		bool ok=0;
		for(int j=1;j<=a.cnt;j++){
			if(a.x[j]==b.x[i]){
				a.y[j]+=b.y[i];
				ok=1;break;
			}
		} if(ok) continue;
		a.x[++a.cnt]=b.x[i];a.y[a.cnt]=b.y[i];int mn=INF;
		if(a.cnt<=p) continue;
		for(int j=1;j<=a.cnt;j++) chkmin(mn,a.y[j]);
		seq c;
		for(int j=1;j<=a.cnt;j++) if(a.y[j]-mn)
			c.x[++c.cnt]=a.x[j],c.y[c.cnt]=a.y[j]-mn;
		a=c;
	} return a;
}
void pushup(int k){s[k].v=merge(s[k<<1].v,s[k<<1|1].v);}
void build(int k=1,int l=1,int r=n){
	s[k].l=l;s[k].r=r;if(l==r){s[k].v.cnt=1;s[k].v.x[1]=a[l];s[k].v.y[1]=1;return;}
	int mid=l+r>>1;build(k<<1,l,mid);build(k<<1|1,mid+1,r);pushup(k);
}
void pushdown(int k){
	if(s[k].lz){
		s[k<<1].v.cnt=1;s[k<<1].v.x[1]=s[k].lz;
		s[k<<1].v.y[1]=s[k<<1].r-s[k<<1].l+1;
		s[k<<1].lz=s[k].lz;
		s[k<<1|1].v.cnt=1;s[k<<1|1].v.x[1]=s[k].lz;
		s[k<<1|1].v.y[1]=s[k<<1|1].r-s[k<<1|1].l+1;
		s[k<<1|1].lz=s[k].lz;
		s[k].lz=0;
	}
}
void modify(int k,int l,int r,int x){
	if(l<=s[k].l&&s[k].r<=r){
		s[k].v.cnt=1;s[k].v.x[1]=x;
		s[k].v.y[1]=s[k].r-s[k].l+1;
		s[k].lz=x;return;
	} pushdown(k);int mid=s[k].l+s[k].r>>1;
	if(r<=mid) modify(k<<1,l,r,x);
	else if(l>mid) modify(k<<1|1,l,r,x);
	else modify(k<<1,l,mid,x),modify(k<<1|1,mid+1,r,x);
	pushup(k);
}
seq query(int k,int l,int r){
	if(l<=s[k].l&&s[k].r<=r) return s[k].v;
	int mid=s[k].l+s[k].r>>1;pushdown(k);
	if(r<=mid) return query(k<<1,l,r);
	else if(l>mid) return query(k<<1|1,l,r);
	else return merge(query(k<<1,l,mid),query(k<<1|1,mid+1,r));
}
int main(){
	scanf("%d%d%d",&n,&qu,&p);p=100/p;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);build();
	while(qu--){
		int opt;scanf("%d",&opt);
		if(opt==1){int l,r,x;scanf("%d%d%d",&l,&r,&x);modify(1,l,r,x);}
		else{
			int l,r;scanf("%d%d",&l,&r);seq ret=query(1,l,r);
			printf("%d ",ret.cnt);for(int i=1;i<=ret.cnt;i++) printf("%d ",ret.x[i]);
			printf("\n");
		}
	}
	return 0;
}
```



---

## 作者：ZigZagKmp (赞：1)

本文同步于我的 [cnblog](https://www.cnblogs.com/ZigZagKmp/p/14373762.html)

## 题意简述
给定长度为 $n$ 的序列和整数 $P$ ，有 $m$ 次操作。操作格式如下：
- `1 l r v` $[l,r]$ 区间赋值为 $v$ ；
- `2 l r` 查询 $[l,r]$ 中出现频率不少于 $P\%$ 的数。
询问2可以输出错误数字，也可以重复输出，但是总数不能超过 $\lfloor \frac{100}{P} \rfloor$。

$n,m\le 1.5\times 10^5,20\le P\le 100$。
## 算法分析
我的做法与题解中的主流做法似乎不同。

我们先考虑证明，如果能求出两个**长度相等**的区间内出现频率不小于 $P\%$ 的数集合$A,B$，那么这个集合的并中满足要求的数 $x\in A\cup B$。

这个不难证明，如果一个数在两个区间内出现的频率都小于 $P\%$ ，记分别出现 $x,y$ 次，则 $x<len\times P\%,y<len\times P\%$ 那么两边出现的次数和为 $x+y$ ，一定小于 $2\times len \times P\%$ ，因此这个数不符合要求，不一定要输出。

因此我们考虑维护每一个区间内出现次数最多的 $K=\lceil\frac{100}{P}\rceil$ 个元素及其出现次数，合并直接把相同的数次数累加，得到至多 $2K$ 个元素，取出现次数前 $K$ 大的即可。

具体实现时，我们首先把 $n$ 变成比 $n$ 大的第一个 $2^p$ 的数，这样我们建立的线段树就是一个满二叉树，并且每一次合并都是两个**相等长度**的区间的合并。

时间复杂度 $O\left((n+m)K^2\log n\right)$ ，K含义见上文。

## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 300005
#define maxm 2000005
#define inf 0x3f3f3f3f
#define LL long long
#define mod 1000000007
#define local
void file(string s){freopen((s+".in").c_str(),"r",stdin);freopen((s+".out").c_str(),"w",stdout);}
template <typename Tp> void read(Tp &x){
	int fh=1;char c=getchar();x=0;
	while(c>'9'||c<'0'){if(c=='-'){fh=-1;}c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c&15);c=getchar();}x*=fh;
}
int n,m,P;
int a[maxn];
struct nd{
	int id,vl;
	bool operator <(nd y)const{
		return vl>y.vl;
	}
};
nd tmp[20];int cnt;
#define lson ((x<<1))
#define rson ((x<<1)|1)
#define mid ((l+r)>>1)
struct node{
	nd nm[7];
	node operator +(node y)const{
		node z;
		cnt=0;
		for(int i=1;i<=P;++i)tmp[++cnt]=nm[i];
		for(int i=1;i<=P;++i){
			int flg=0;
			for(int j=1;j<=P;++j){
				if(y.nm[i].id==tmp[j].id){
					flg=j;break;
				}
			}//合并
			if(flg)tmp[flg].vl+=y.nm[i].vl;//处理相同元素
			else tmp[++cnt]=y.nm[i];//处理不同元素
		}
		sort(tmp+1,tmp+cnt+1);
		for(int i=1;i<=P;++i)z.nm[i]=tmp[i];//取前K大
		return z;
	}
}st[maxn<<2];
int laz[maxn<<2];
void pushup(int x){st[x]=st[lson]+st[rson];}
void build(int x,int l,int r){
	if(l==r){
		st[x].nm[1]=(nd){a[l],1};
		return;
	}
	build(lson,l,mid);
	build(rson,mid+1,r);
	pushup(x);
}
void pushc(int x,int l,int r,int v){memset(st[x].nm,0,sizeof(st[x].nm));st[x].nm[1]=(nd){v,r-l+1};laz[x]=v;}
// 下推懒标记直接保留一个就行了
void pushdown(int x,int l,int r){
	if(laz[x]){
		pushc(lson,l,mid,laz[x]);
		pushc(rson,mid+1,r,laz[x]);
		laz[x]=0;
	}
}
void upd(int x,int l,int r,int L,int R,int v){
	if(l>R||r<L)return ;
	if(l>=L&&r<=R){
		pushc(x,l,r,v);
		return;
	}
	pushdown(x,l,r);
	upd(lson,l,mid,L,R,v);
	upd(rson,mid+1,r,L,R,v);
	pushup(x);
}
node query(int x,int l,int r,int L,int R){
	if(l>=L&&r<=R)return st[x];
	pushdown(x,l,r);
	if(L>mid)return query(rson,mid+1,r,L,R);
	if(R<=mid)return query(lson,l,mid,L,R);
	return query(lson,l,mid,L,R)+query(rson,mid+1,r,L,R);
}
signed main(){
	read(n);read(m);read(P);
	P=100/P;++P;//这里直接+1，主要是后面输出个数处理方便
	for(int i=1;i<=n;++i)read(a[i]);
	
	int NN;for(NN=1;NN<n;NN<<=1);n=NN;//扩成2^p
	
	build(1,1,n);
	for(int i=1,op,l,r,v;i<=m;++i){
		read(op);read(l);read(r);
		if(op==1){
			read(v);upd(1,1,n,l,r,v);
		}
		else{
			printf("%d",P-1);
			node tt=query(1,1,n,l,r);
			for(int j=1;j<P;++j){
				printf(" %d",tt.nm[j].id?tt.nm[j].id:1);
			}
			puts("");
		}
	}
	return 0;
}

```

---

## 作者：YxYe (赞：0)

前言：本来想给学弟学妹们出一道随机化的题，结果被同学告知有这道类似的题，于是我就顺便用随机化切了~

甚至比同学的线段树快。

## Sol

这不就是区间修改嘛~

直接用分块维护，打标记基操。

这不就是查询占比超过 $k\%$ 的嘛~

直接随机化，每次在区间里随一个位置，统计这个位置上数的出现次数，然后最后排个序输出就好了。

## Code

就是这么简单，直接上代码~

```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<vector>
#define fo(i,a,b) for(int i=(a);i<=(b);i++)
#define pii pair<int, int>
#define pb push_back
#define fir first
#define sec second
using namespace std;
char buf[1<<21],*p1=buf,*p2=buf;
inline int getc(){
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
	int x=0,f=1;char ch=getc();
	while(!isdigit(ch)){
		if(ch=='-')f=-1;
		ch=getc();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getc();
	}
	return x*f;
}
const int maxn=2e6+10;
int n,m,p,a[maxn];
int len,id[maxn],bg[maxn],ed[maxn],tag[maxn];
pii b[maxn];
int c[maxn],cnt[maxn],vis[maxn];
void init(){
	int l=1,r=len;
	fo(i,1,n/len+2){
		bg[i]=l;ed[i]=r;
		fo(j,l,r){
			id[j]=i;
		}
		l=r+1;
		r=l+len-1;
	}
}
#include<ctime>
#include<random>
mt19937 rnd(time(0));
int main(){
	n=read();m=read();p=read();len=sqrt(n);
	fo(i,1,n)a[i]=read();
	init();
	fo(_,1,m){
		int op=read(),l=read(),r=read();
		if(op==1){
			int x=read();
			fo(i,id[l]+1,id[r]-1)tag[i]=x;
			if(tag[id[l]])fo(i,bg[id[l]],ed[id[l]])a[i]=tag[id[l]];
			if(tag[id[r]])fo(i,bg[id[r]],ed[id[r]])a[i]=tag[id[r]];
			tag[id[l]]=tag[id[r]]=0;
			if(id[l]^id[r]){
				fo(i,l,ed[id[l]])a[i]=x;
				fo(i,bg[id[r]],r)a[i]=x;
			}
			else{
				fo(i,l,r)a[i]=x;
			}
		}
		if(op==2){
			int tot=0;
			fo(i,1,700){
				int x=rnd()%(r-l+1)+l;
				int now=tag[id[x]]?tag[id[x]]:a[x];
				if(vis[now]^_)vis[now]=_,cnt[now]=0,c[++tot]=now;
				cnt[now]++;
			}
			fo(i,1,tot)b[i]=pii(cnt[c[i]],c[i]);
			sort(b+1,b+tot+1);
			reverse(b+1,b+tot+1);
			printf("%d ",100/p);
			fo(i,1,100/p)printf("%d ",b[i].sec);puts("");
		}
	}
	return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：0)

来补一下区间固定频率众数的做法，昨天才知道（                 

考虑摩尔投票法，我们如果求区间出现过一半以上的众数可以直接在线段树上维护残余值，合并时如果两边数相同就相加残余值，否则就将两边的数相互抵消返回残余值更大的那一个。           

考虑延展我们的操作，如果求出现次数在 $\lfloor \frac{n}{k + 1} \rfloor$ 以上的数，我们可以每次消掉 $k + 1$ 个不同的数，这样就能保证出现次数在 $\lfloor \frac{n}{k + 1}\rfloor$ 以上的众数最后仍能存活下来。    

实现时线段树上只维护残余值最大的 $k$ 个数，$O(k ^ 2)$ 实现合并 $2k$ 个后按照残余值重新从大到小排序（貌似 sort 在数组很小时是会手动调整，所以这里时间复杂度是常数），最后倒着内耗后再返回残余值最大的 $k$ 个数即可。

时间复杂度 $O(k^2n \log n)$。

```cpp
/*
因为我们每次只删不同的数
不妨先全部合起来后倒着内耗即可 
*/
#include "bits/stdc++.h"
using namespace std;
const int Len = 1.5e5 + 5;
int n,q,P,a[Len],tag[Len << 2];
struct Node
{
	int col,w;
	Node(){col = w = 0;}
	Node(int COL,int W){col = COL , w = W;}
	inline void clear(){col = w = 0;}
};
bool cmd(Node x,Node y){return x.w > y.w;}
struct node
{
	Node ch[6];
	node(){for(int i = 1 ; i < P ; i ++) ch[i].clear();}
	node(Node CH1){ch[1] = CH1;for(int i = 2 ; i < P ; i ++) ch[i].clear();}
	inline void clear(){for(int i = 1 ; i < P ; i ++) ch[i].clear();}
}Seg[Len << 2];
vector<Node> ud;
#define ls(x) x << 1
#define rs(x) x << 1 | 1
node merge(node x,node y)
{
	node pst;ud.clear();
	for(int i = 1 ; i < P ; i ++)
		for(int j = 1 ; j < P ; j ++) 
		{
			if(y.ch[j].col == x.ch[i].col) 
			{
				x.ch[i].w += y.ch[j].w , y.ch[j].col = 0;
				break;
			}
		}
	for(int i = 1 ; i < P ; i ++) if(x.ch[i].col > 0) ud.push_back(x.ch[i]);
	for(int i = 1 ; i < P ; i ++) if(y.ch[i].col > 0) ud.push_back(y.ch[i]);
	/*printf("%d\n",ud.size());
	for(int i = 0 ; i < ud.size() ; i ++) printf("(%d,%d) ",ud[i].col,ud[i].w);
	puts("");*/ 
	sort(ud.begin() , ud.end() , cmd);
	if(ud.size() <= P - 1)//数量不超过 P - 1，直接返回 
	{
		for(int i = 0 ; i < ud.size() ; i ++) pst.ch[i + 1] = ud[i];
		return pst;
	}
	for(int i = ud.size() - 1 ; i >= P - 1 ; i --)//选择 k + 1 个数，倒序内耗 
	{
		int del = ud[i].w;
		for(int j = i ; j >= i - P + 1 ; j --) ud[j].w -= del;
	}
	for(int i = 0 ; i < P - 1 ; i ++) pst.ch[i + 1] = ud[i];
	return pst;
}
void push_up(int p){Seg[p] = merge(Seg[ls(p)] , Seg[rs(p)]);}
void push_down(int p,int l,int r)
{
	if(tag[p])
	{
		int mid = (l + r) >> 1;
		tag[ls(p)] = tag[rs(p)] = tag[p];
		Seg[ls(p)] = node(Node(tag[p] , mid - l + 1)) , Seg[rs(p)] = node(Node(tag[p] , r - mid));
		tag[p] = 0;
	}
}
void build(int p,int l,int r)
{
	tag[p] = 0;
	if(l == r)
	{
		Seg[p] = node(Node(a[l] , 1));
		/*printf("%d:\n",l);
		for(int i = 1 ; i < P ; i ++) printf("(%d,%d) ",Seg[p].ch[i].col,Seg[p].ch[i].w);
		puts("");*/ 
		return;
	}
	int mid = (l + r) >> 1;
	build(ls(p) , l , mid);
	build(rs(p) , mid + 1 , r);
	push_up(p);
}
void update(int p,int l,int r,int nl,int nr,int w)
{
	if(nl <= l && nr >= r) 
	{
		tag[p] = w;
		Seg[p] = node(Node(w , r - l + 1));
		return;
	}
	push_down(p , l , r);
	int mid = (l + r) >> 1;
	if(nl <= mid) update(ls(p) , l , mid , nl , nr , w);
	if(nr > mid) update(rs(p) , mid + 1 , r , nl , nr , w);
	push_up(p);
}
node ans;int udd;
void query(int p,int l,int r,int nl,int nr)
{
	if(nl <= l && nr >= r)
	{
		//printf("!!!%d %d\n",l,r);
		/*printf("%d:\n",l);
		for(int i = 1 ; i < P ; i ++) printf("(%d,%d) ",Seg[p].ch[i].col,Seg[p].ch[i].w);
		puts("");*/ 
		if(!udd) ans = Seg[p] , udd = 1;
		else ans = merge(ans , Seg[p]);
		return;
	}
	push_down(p , l , r);
	int mid = (l + r) >> 1;
	if(nl <= mid) query(ls(p) , l , mid , nl , nr);
	if(nr > mid) query(rs(p) , mid + 1 , r , nl , nr);
	//push_up(p);
}
vector<int> Print;
int main()
{
	scanf("%d %d %d",&n,&q,&P);
	P = 100 / P;P ++;
	for(int i = 1 ; i <= n ; i ++) scanf("%d",&a[i]);
	build(1 , 1 , n);
	for(int i = 1 ; i <= q ; i ++)
	{
		int opt,l,r,id;scanf("%d %d %d",&opt,&l,&r);
		if(opt == 1)
		{
			scanf("%d",&id);
			update(1 , 1 , n , l , r , id);
		}
		else
		{
			ans.clear();Print.clear();
			udd = 0;
			query(1 , 1 , n , l , r);
			for(int j = 1 ; j < P ; j ++) if(ans.ch[j].col) Print.push_back(ans.ch[j].col);
			printf("%d ",Print.size());
			for(int j = 0 ; j < Print.size() ; j ++) printf("%d ",Print[j]); 
			puts("");
		}
	}
	return 0;
}
```

---

