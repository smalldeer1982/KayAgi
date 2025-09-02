# Swapping Problem

## 题目描述

You are given 2 arrays $ a $ and $ b $ , both of size $ n $ . You can swap two elements in $ b $ at most once (or leave it as it is), and you are required to minimize the value $ $$$\sum_{i}|a_{i}-b_{i}|. $ $$$

Find the minimum possible value of this sum.

## 说明/提示

In the first example, we can swap the first and fifth element in array $ b $ , so that it becomes $ [ 5, 2, 3, 4, 1 ] $ .

Therefore, the minimum possible value of this sum would be $ |5-5| + |4-2| + |3-3| + |2-4| + |1-1| = 4 $ .

In the second example, we can swap the first and second elements. So, our answer would be $ 2 $ .

## 样例 #1

### 输入

```
5
5 4 3 2 1
1 2 3 4 5```

### 输出

```
4```

## 样例 #2

### 输入

```
2
1 3
4 2```

### 输出

```
2```

# 题解

## 作者：henryhu2006 (赞：20)

## CF1513F Swapping Problem
## 题意
给定 $n$ 和两个长度为 $n$ 的数组 $a,b$，最多交换一次 $b$ 中的两个位置的值。

最小化 $\sum_{i=1}^{n}|a_i-b_i|$。

$n \le 2\times10^5$；$a_i,b_i\le 10^9$。

## 分析
将抽象的数组 $a,b$ 形象化。将每一对 $(a_i,b_i)$ 看做一段一维**开**区间，那么代价就是区间的长度。

目标是选择两个区间，交换 $b$ 端点后，使得原长度减去产生的新区间的长度尽量大。

将所有 $a_i=b_i$ 的点对忽略（长度为 $0$ 不影响结果）。

对两段区间的关系进行分类讨论：

1. 相离
	
    无论每个区间的 $a$ 在左边还是右边，都不可能比原来更优。

2. 包含
	
    不妨认为大的区间的 $a_i < b_i$。
    
    若小区间 $a_j < b_j$，交换长度和不变。
    
    若反过来，交换更优。

3. 相交
		
      不妨认为左边的区间 $a_i < b_i$。
      
      若右边的区间 $a_j< b_j$，交换长度和不变。
      
      若反过来，交换更优。
      
从分类讨论中可以得到结论：

- 所有交换 $b$ 可以产生贡献的两个区间的方向一定相反，即 $(a_i-b_i)(a_j-b_j)<0$。
- 由于区间重叠的部分原来会被计算 $2$ 次，最后的答案为 
	$$(\sum_{i=1}^{n}|a_i-b_i|)-2\times\max_{1\le i,j \le n,i\neq j}|(a_i,b_i)\cap(a_j,b_j)|$$

## 算法
将所有区间分类，然后默认 $a_i<b_i$，按照 $b_i$ 的大小排序。

按 $b_i$ 从大到小枚举，对于每个 $i$ ，查询和它**不同**的类型中，已经访问过的区间（即 $b_j>b_i$），可以得到最小的 $a_j$ 是多少，从而计算出最大的交集。计算完后要将自己加入所对应的类型。

细节见代码。

## 代码
```cpp
int m,n,l[2],len,x[N],y[N]; ll ans;
struct node{
	int a,b,t;
	 bool operator < (const node &a)const{return b<a.b;}
} p[N];
int main(){
	cin>>m,l[0]=l[1]=2e9;
	for(int i=1;i<=m;++i) scanf("%d",x+i);
	for(int i=1;i<=m;++i) scanf("%d",y+i);
	for(int i=1,a,b;i<=m;++i){
		a=x[i],b=y[i];
		if(a==b) continue;
		++n; if(a>b) p[n].t=1,swap(a,b);
		p[n].a=a,p[n].b=b,ans+=b-a;
	}
	sort(p+1,p+n+1);
	for(int i=n,val;i>=1;--i){
		int tp=p[i].t;
		if(l[tp^1]<p[i].b) len=max(len,p[i].b-max(p[i].a,l[tp^1]));
		l[tp]=min(l[tp],p[i].a);
	}
	cout<<ans-2*len;
}
```

---

## 作者：jun头吉吉 (赞：3)

## 题意
给定 $n$ 和两个长度为 $n$ 的数组 $a,b$，最多交换一次 $b$ 中的两个位置的值（可以不交换）。

最小化 $\sum_{i=1}^{n}|a_i-b_i|$
## 题解
给一个比较套路的解法。

先跑一遍得到原来的值 $sum$，记 $x_i=|a_i-b_i|$

考虑交换 $i,j$ 的 $b$ ，那么差值满足：
$$\triangledown= |a_i-b_j|+|b_i-a_j|-x_i-x_j$$
当 $i=j$ 时上式仍然成立。

把前面两个绝对值看作是 $(a_i,b_i)$ 与 $(b_j,a_j)$ 的曼哈顿距离，那么可以转化一下题意。

找曼哈顿距离最小是经典问题。看作是有点 $(a_1,b_1),\ldots,(a_n,b_n)$，对 $(b_1,a_1),\ldots,(b_n,a_n)$ 分别找最小的 $\triangledown$。绝对值拆成四个方向就不用考虑了。

## 代码
```cpp
#include<bits/stdc++.h>
#define pb push_back
typedef long long ll;
using namespace std;
const int N=2e5+10;
const ll inf=0x3f3f3f3f3f3f3f3f;
struct tree{
	ll t[N<<3];
	#define mid (l+r>>1)
	#define lc (x<<1)
	#define rc (x<<1|1)
	void init(int x,int l,int r){
		t[x]=inf;
		if(l==r)return;
		init(lc,l,mid);
		init(rc,mid+1,r);
	}
	void upd(int x,int l,int r,int pos,ll val){
		t[x]=min(t[x],val);
		if(l==r)return;
		if(pos<=mid)upd(lc,l,mid,pos,val);
		else upd(rc,mid+1,r,pos,val);
	}
	ll qry(int x,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr)return t[x];
		if(qr<=mid)return qry(lc,l,mid,ql,qr);
		else if(mid<ql)return qry(rc,mid+1,r,ql,qr);
		else return min(qry(lc,l,mid,ql,qr),qry(rc,mid+1,r,ql,qr));
	}
}t1,t2;
int n,a[N],b[N],x[N];
int aa[N],bb[N];
vector<int>num;
ll sum=0;
vector<int>add[N<<1],qry[N<<1];
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&b[i]),x[i]=abs(a[i]-b[i]),num.push_back(a[i]),num.push_back(b[i]),sum+=x[i];
	num.push_back(-998244353);sort(num.begin(),num.end());num.resize(unique(num.begin(),num.end())-num.begin());int tot=num.size()-1;
	//事实上就是一个平面最近点对(带权)
	//找到两个点 a,b 使得 MHDDis(a,b)-val[a]-val[b]最小
	//事实上就是 排序扫描。
	for(int i=1;i<=n;i++){
		aa[i]=lower_bound(num.begin(),num.end(),a[i])-num.begin();
		bb[i]=lower_bound(num.begin(),num.end(),b[i])-num.begin();
		add[aa[i]].pb(i);qry[bb[i]].pb(i);
	}
	t1.init(1,1,tot);t2.init(1,1,tot);
	//t1是低的，t2是高的 
	long long mn=inf;
	for(int i=1;i<=tot;i++){
		for(auto j:add[i]){
			t1.upd(1,1,tot,bb[j],-a[j]-b[j]-x[j]);
			t2.upd(1,1,tot,bb[j],-a[j]+b[j]-x[j]);
		} 
		for(auto j:qry[i]){
			mn=min(mn,b[j]+a[j]+t1.qry(1,1,tot,1,aa[j])-x[j]);
			mn=min(mn,b[j]-a[j]+t2.qry(1,1,tot,aa[j],tot)-x[j]);
		}
	}
	t1.init(1,1,tot);t2.init(1,1,tot);
	for(int i=tot;i>=1;i--){
		for(auto j:add[i]){
			t1.upd(1,1,tot,bb[j],a[j]-b[j]-x[j]);
			t2.upd(1,1,tot,bb[j],a[j]+b[j]-x[j]);
		} 
		for(auto j:qry[i]){
			mn=min(mn,-b[j]+a[j]+t1.qry(1,1,tot,1,aa[j])-x[j]);
			mn=min(mn,-b[j]-a[j]+t2.qry(1,1,tot,aa[j],tot)-x[j]);
		}
	}
	printf("%lld",sum+mn);
}
```

---

## 作者：timmark (赞：1)

# CF1513F 题解

考虑把 $\lvert a_i-b_i\rvert$ 变成 $\max(a_i,b_i)-\min(a_i,b_i)$，即左闭右开区间的长度，那么交换 $b_i$ 和 $b_j$ 就是交换 $2$ 个区间的“$b$ 端点”。

## 大力讨论
~~一天不赤石我浑身难受~~

先崩掉 $a_i=b_i$ 的，这堆东西屁用没有。

对于两个区间 $a_i,b_i$ 和 $a_j,b_j$（**因不确定 $a$ 和 $b$ 的大小关系，所以没有括号**），讨论关系。

### 相离

当 $a_j<b_j$ 时，考虑 $a_i$ 与 $b_i$ 大小关系。

| 关系 | 示意图 |
| :-: | :-: |
| $a_i<b_i$ | ![](https://img.picgo.net/2025/03/20/image7309582d89da4f12.md.png) |
| $a_i>b_i$ | ![](https://img.picgo.net/2025/03/20/image696a5ebb20f920a4.md.png) |

对于 $a_j>b_j$ 同理。

综上，相离的情况下，交换必定更劣。

### 包含

钦定 $a_j<b_j$ 且 $a_j,b_j$ 包含 $a_i,b_i$。

讨论 $a_i$ 与 $b_i$。

| 关系 | 示意图 |
| :-: | :-: |
| $a_i<b_i$ | ![](https://img.picgo.net/2025/03/20/image1165961da65ff868.md.png) |
| $a_i>b_i$ | ![](https://img.picgo.net/2025/03/20/image9453feda63fd6389.md.png) |

综上，当 $a_i,b_i$ 与 $a_j,b_j$ 大小关系不同时，交换更优。
### 相交

钦定 $a_j,b_j$ 在右，且 $a_j<b_j$。

讨论 $a_i$ 与 $b_i$。

| 关系 | 示意图 |
| :-: | :-: |
| $a_i<b_i$ | ![](https://img.picgo.net/2025/03/20/image3cbfd0e05a311a30.md.png) |
| $a_i>b_i$ | ![](https://img.picgo.net/2025/03/20/image2cb13ec913ae0c74.md.png) |

综上，当 $a_i,b_i$ 与 $a_j,b_j$ 大小关系不同时，交换更优。

### 总结

当 $a_i,b_i$ 和 $a_j,b_j$ 不相离且 $a_i,b_i$ 与 $a_j,b_j$ 大小关系不同时，交换更优。

## 实现

对每一对 $a_i,b_i$，记录其 $a_i,b_i$ 大小关系，容易发现更优的情况下，优化掉的都是一段交的 $2$ 倍。

那么我们将一个区间记为 $(l_i,r_i,typ_i)$，其中 $l_i<r_i$，$typ_i$ 表示在输入的 $a_i$、$b_i$ 中，$a_i$ 是否大于 $b_i$。

将区间按照 $b$ 从小到大排序，从后往前遍历，并尝试与已遍历过的、满足 $typ_j\ne typ_i$ 和 $l_j<r_i$ 的区间 $j$ 取交，更新 $ans$。

最终的答案即为

$$
\sum \limits_{i=1}^{i=n} \lvert a_i-b_i\rvert-2\times ans
$$

## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
typedef long long ll;
const int maxn=2e5+5;
int n,a[maxn],b[maxn],s[2]={1ll << 45,1ll << 45},m,sum,ans;
struct node{int l,r;bool typ;}c[maxn];
bool cmp(node x,node y){return x.r<y.r;}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n ;
	for(int i=1;i<=n;i++) cin >> a[i] ;
	for(int i=1;i<=n;i++) cin >> b[i] ;
	for(int i=1;i<=n;i++){
		if(a[i]==b[i]) continue;
		++m,c[m]={min(a[i],b[i]),max(a[i],b[i]),a[i]>b[i]},sum+=c[m].r-c[m].l;		
	}sort(c+1,c+m+1,cmp);
	for(int i=m;i;i--){
		if(s[!c[i].typ]<c[i].r) ans=max(ans,c[i].r-max(s[!c[i].typ],c[i].l));
		s[c[i].typ]=min(s[c[i].typ],c[i].l);
	}cout << sum-2*ans ;
	return 0;
}//给予我们比赛，却放任我们赤石的人,必将为此付出代价!
```

给个赞吧。

---

## 作者：Diaоsi (赞：1)

[Swapping Problem](https://www.luogu.com.cn/problem/CF1513F)

提供一个好想好写的做法

把 $a_i<b_i$ 的二元组按照 $[a_i,b_i]$ 划入集合 $P$，$a_i>b_i$ 的二元组按照 $[b_i,a_i]$ 划入集合 $Q$，把两个集合中的二元组看作区间。原问题转化为从集合 $P$ 和集合 $Q$ 中各找出一个区间使得两个区间的交最大。

答案就是 $\sum\limits_{i=1}^n\left|a_i-b_i\right|$ 减去两倍的最大区间交。

将集合 $P,Q$ 中的区间按照右端点排序，对于任意一个 $P$ 中区间 $[l_i,r_i]$ ，考虑以下两种 $Q$ 中的区间。

- 横跨 $r_i$ 的区间

- 被 $[l_i,r_i]$ 完全包含的区间

前者可以用扫描线维护，把所有横跨 $r_i$ 的区间的左端点在线段树上加一，然后查询 $[l_i,r_i]$ 中最前面的大于零的位置。

后者只需要将 $Q$ 中右端点小于 $r_i$ 的区间的左端点覆盖成该区间的长度，然后在线段树上查询 $[l_i,r_i]$ 的最大值。

把 $P,Q$ 交换然后重复上述过程，就做完了，时间复杂度 $\mathcal{O}(n\log n)$。

```Code:```

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll N=500010,M=5000010,INF=0x3f3f3f3f;
inline ll max(ll x,ll y){return x>y?x:y;}
inline ll min(ll x,ll y){return x<y?x:y;}
inline void swap(ll &x,ll &y){x^=y^=x^=y;}
ll n,ls,rs,cnt,ans,val,a[N],b[N],c[N<<1];
vector<ll> add[N],del[N];
struct node{
	ll l,r;
	bool operator <(const node &x)const{
		return r<x.r;
	}
}p[N],q[N];
struct SegmentTree{
	ll l,r;
	ll dat,tag,pos;
	#define l(x) tree[x].l
	#define r(x) tree[x].r
	#define dat(x) tree[x].dat
	#define tag(x) tree[x].tag
	#define pos(x) tree[x].pos
}tree[N<<2];
void pushup(ll x){
	dat(x)=max(dat(x<<1),dat(x<<1|1));
	if(pos(x<<1))pos(x)=pos(x<<1);
	else if(pos(x<<1|1))pos(x)=pos(x<<1|1);
	else pos(x)=0;
}
void build(ll x,ll l,ll r){
	l(x)=l;r(x)=r;
	dat(x)=pos(x)=0;tag(x)=-1;
	if(l==r)return;
	ll mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	pushup(x);
}
void pushdown(ll x){
	if(tag(x)<0)return;
	dat(x<<1)=tag(x);
	dat(x<<1|1)=tag(x);
	tag(x<<1)=tag(x);
	tag(x<<1|1)=tag(x);
	if(!tag(x))pos(x<<1)=pos(x<<1|1)=0;
	tag(x)=-1;
}
void insert(ll x,ll pos,ll d){
	ll l=l(x),r=r(x);
	if(l==r){
		dat(x)+=d;
		pos(x)=dat(x)?l:0;
		return;
	}
	ll mid=(l+r)>>1;
	pushdown(x);
	if(pos<=mid)insert(x<<1,pos,d);
	else insert(x<<1|1,pos,d);
	pushup(x);
}
void change(ll x,ll L,ll R,ll d){
	ll l=l(x),r=r(x);
	if(L<=l&&r<=R){
		dat(x)=tag(x)=d;
		if(!d)pos(x)=0;
		return;
	}
	ll mid=(l+r)>>1;
	pushdown(x);
	if(L<=mid)change(x<<1,L,R,d);
	if(R>mid)change(x<<1|1,L,R,d);
	pushup(x);
}
ll ask(ll x,ll L,ll R){
	ll l=l(x),r=r(x);
	if(L<=l&&r<=R)return pos(x);
	ll mid=(l+r)>>1,ql=0,qr=0;
	pushdown(x);
	if(L<=mid)ql=ask(x<<1,L,R);
	if(R>mid)qr=ask(x<<1|1,L,R);
	if(!ql||!qr)return ql+qr;
	else return min(ql,qr);
}
ll query(ll x,ll L,ll R){
	ll l=l(x),r=r(x);
	if(L<=l&&r<=R)return dat(x);
	ll mid=(l+r)>>1,tmp=-INF;
	pushdown(x);
	if(L<=mid)tmp=max(tmp,query(x<<1,L,R));
	if(R>mid)tmp=max(tmp,query(x<<1|1,L,R));
	return tmp;
}
void ADD(ll k){for(ll z:add[k])insert(1,z,1);}
void DEL(ll k){for(ll z:del[k])insert(1,z,-1);}
void solve(){
	change(1,1,cnt,0);
	sort(p+1,p+ls+1);
	sort(q+1,q+rs+1);
	for(ll i=1;i<=cnt;i++)
		add[i].clear(),del[i].clear();
	for(ll i=1;i<=ls;i++){
		add[p[i].l].push_back(p[i].l);
		del[p[i].r+1].push_back(p[i].l);
	}
	ll k=1;
	for(ll i=1;i<=rs;i++){
		while(k<=q[i].r){ADD(k),DEL(k),++k;}
		ll pos=ask(1,q[i].l,q[i].r);
		if(pos)val=max(val,c[q[i].r]-c[pos]);
	}
	change(1,1,cnt,0);
	for(ll i=1,j=1;j<=rs;j++){
		while(i<=ls&&p[i].r<q[j].r)
			change(1,p[i].l,p[i].l,c[p[i].r]-c[p[i].l]),++i;
		val=max(val,query(1,q[j].l,q[j].r));
	}
}
int main(){
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++)
		scanf("%lld",&a[i]),c[++cnt]=a[i];
	for(ll i=1;i<=n;i++)
		scanf("%lld",&b[i]),c[++cnt]=b[i];
	sort(c+1,c+cnt+1);
	cnt=unique(c+1,c+cnt+1)-c-1;
	for(ll i=1;i<=n;i++){
		ll l=lower_bound(c+1,c+cnt+1,a[i])-c;
		ll r=lower_bound(c+1,c+cnt+1,b[i])-c;
		if(a[i]<b[i])p[++ls]=(node){l,r},ans+=b[i]-a[i];
		else q[++rs]=(node){r,l},ans+=a[i]-b[i];
	}
	build(1,1,cnt);
	solve();
	std::swap(p,q);
	std::swap(ls,rs);
	solve();
	printf("%lld\n",ans-(val<<1));
	return 0;
}
```


---

## 作者：tZEROちゃん (赞：1)

构造集合 $X, Y$，$X$ 包含所有 $A_i < B_i$ 的下标，$Y$ 包含所有 $A_i > B_i$ 的下标。

将每一对 $(A_i, B_i)$ 转化成线段，其中左端点是 $\min(A_i, B_i)$，右端点是 $\max(A_i, B_i)$。

那么题目就变换成了这些线段长度之和。

思考，怎么样才能让这个长度变小呢？

答案是，$i\in X,j\in Y$，且第 $i$ 条和第 $j$ 条线段有交集。

为什么。其实很显然。这样他们的交集就可以很自然的被删掉了。

举个例子，$A_i = 3, B_i = 5, A_j = 9, B_j = 2$。本来绝对值是 $|5 - 3| + |9 - 2| = 9$，交换之后就会变成 $|2 - 3| + |9 - 5| = 5$，他们交集的长度是 $[3, 5]$ 这一段，长度是 $2$，因此答案减小了 $2\times 2= 4$，之所以乘 $2$ 是因为两个线段都包含这一段。

当然，这只是一种情况，其实还有四种情况（笑。

那么我们继续，我们可以固定 $A_i$ 和 $B_i$，从而确定这两条线段直接到底有什么关系。

- $B_j \le A_i \le A_j \le B_i$
- $B_j \le A_i \le B_i \le A_j$
- $A_i \le B_j \le A_j \le B_i$
- $A_i \le B_j \le B_i \le A_j$

其实第 $1,4$ 种和第 $2,3$ 种长得差不多（。

第 $1,4$ 种是 $[B_j, A_j]$ 和 $[A_i, B_i]$ 存在公共部分，但都有不属于另一线段的部分；第 $2,3$ 种分别是 $[B_j, A_j]$ 完全包含 $[A_i, B_i]$ 和 $[A_i, B_i]$ 完全包含 $[B_j, A_j]$ 的情况。

我们可以证明一下第 $1$ 种，$2,3, 4$ 同理。

- 不改变时，两个的长度和是 $L_1 = A_j - B_j + B_i - A_i$。
- 改变后，两个的长度和是 $L_2 = B_i - A_j + A_i - B_j$。
- 那么差就是 $M = L_1 - L_2 = 2(A_j - A_i)$。

因此这样改一下答案就会变成原答案减去 $2$ 倍交集长度。

我们想尽可能让交集大，可以用 `std::map` 来维护，每次扫描 $i$ 的时候在另一个集合中 `upper_bound` 即可。




---

## 作者：tzc_wk (赞：1)

[Codeforces 题目传送门](https://codeforces.com/contest/1513/problem/F) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF1513F)

简单题，难度 *2500 的 D2F，就当调节一下一模炸裂了的自闭的心情，稍微写写吧。

首先我看到这题的第一反应是分类讨论+数据结构，即枚举其中一个被交换的位置然后用树状数组或类似的数据结构维护另一个决策的贡献，细节似乎挺多的，大概硬刚个大分类讨论上去也可以？不过显然此题有更简便的方法所以这种方法就没写了。

我们来观察一下这个“交换”有什么性质，这个绝对值有点烦，我们不妨将所有 $i$ 分为两类：$a_i<b_i$ 和 $a_i>b_i$。至于 $a_i=b_i$ 的情况，显然它进行交换之后答案不会更优，所以我们姑且就不用考虑它了。

一个 observation 是对于满足 $a_i<b_i,a_j<b_j$ 的情况，交换 $i,j$ 的情况肯定是不优的，具体证明就考虑将每个 $a_i,b_i$ 看作一个区间 $[a_i,b_i]$，对两个区间 $[a_i,b_i],[a_j,b_j]$ 的位置关系分情况讨论：

- 相离，不妨设 $a_i\le b_i\le a_j\le b_j$，那么交换前贡献为 $b_i-a_i+b_j-a_j$，交换后贡献为 $b_j-a_i+a_j-b_i$，前者 $\le$ 后者。
- 相交，不妨设 $a_i\le a_j\le b_i\le b_j$，那么交换前贡献为 $b_i-a_i+b_j-a_j$，交换后贡献为 $b_j-a_i+b_j-a_i$，前者 $=$ 后者。
- 内含，不妨设 $a_i\le a_j\le b_j\le b_i$，那么交换前贡献为 $b_i-a_i+b_j-a_j$，交换后贡献为 $b_j-a_i+a_j-b_i$，前者 $=$ 后者。

也就是说我们只会选择 $a_i<b_i$ 和 $a_j>b_j$ 的 $i,j$ 进行交换，那么这个贡献该怎么算呢？还是将它们看作一个个区间 $[a_i,b_i]$ 和 $[b_j,a_j]$，我们从**变化量**的角度入手，即记交换后贡献为 $W'$，原来的贡献为 $W$，转而讨论 $W'-W$ 的最小值，这个也可以分三种情况讨论：

- 相离，不妨设 $a_i\le b_i\le b_j\le a_j$，那么交换前贡献为 $a_j-b_j+b_i-a_i$，交换后贡献为 $a_j-b_i+b_j-a_i$，变化量 $\Delta=2(b_j-b_i)$，不难发现这恒为非负，也就是说我们肯定不会交换这两个值，故我们可姑且将这种情况的贡献看作 $0$。
- 相交，不妨设 $a_i\le b_j\le b_i\le a_j$，那么交换前贡献为 $a_j-b_j+b_i-a_i$，交换后贡献为 $a_j-b_i+b_j-a_i$，$\Delta=2(b_j-b_i)$
- 内含，不妨设 $a_i\le b_j\le a_j\le b_i$，那么交换前贡献为 $a_j-b_j+b_i-a_i$，交换后贡献为 $b_j-a_i+b_i-a_j$，$\Delta=2(b_j-a_j)$

不难发现，对于上面的情况，变化量的最小可能值恰为 $[a_i,b_i]$ 和 $[b_j,a_j]$ 的交集的长度，于是随便排个序 two pointers 乱搞搞即可，时间复杂度 $n\log n$

~~1A，就 nm 爽~~

```cpp
const int MAXN=2e5;
int n,a[MAXN+5],b[MAXN+5],ans=0;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) scanf("%d",&b[i]);
	vector<int> v1,v2;
	for(int i=1;i<=n;i++){
		if(a[i]<b[i]) v1.pb(i);
		if(a[i]>b[i]) v2.pb(i);
	}
	sort(v1.begin(),v1.end(),[](int x,int y){return a[x]<a[y];});
	sort(v2.begin(),v2.end(),[](int x,int y){return b[x]<b[y];});
	for(int i=0,j=0,mx=0;i<v1.size();i++){
		while(j<v2.size()&&b[v2[j]]<=a[v1[i]]){
			chkmax(mx,a[v2[j]]);j++;
		} chkmax(ans,min(mx-a[v1[i]],b[v1[i]]-a[v1[i]]));
	}
	for(int i=0,j=0,mx=0;i<v2.size();i++){
		while(j<v1.size()&&a[v1[j]]<=b[v2[i]]){
			chkmax(mx,b[v1[j]]);j++;
		} chkmax(ans,min(mx-b[v2[i]],a[v2[i]]-b[v2[i]]));
	} ll sum=0;
	for(int i=1;i<=n;i++) sum+=abs(a[i]-b[i]);
	printf("%lld\n",sum-(ans<<1));
	return 0;
}
```



---

## 作者：E1_de5truct0r (赞：0)

分类讨论。

一开始差点去写二位偏序了/oh

## 思路

首先，对于 $|a_i-b_i|$，我们可以把它想象成直线上的两点 $a_i,b_i$ 之间的距离。

那么题意就是给定 $n$ 个区间 $(a_i,b_i)$ **或** $(b_i,a_i)$（此时 $b_i<a_i$），可以交换两个 $b_i$ 或者不交换，使得所有区间长度和最小。

首先，不难发现，如果存在两个区间 $(a_i,b_i)$ 和 $(a_j,b_j)$ 那么我们交换 $b_i,b_j$ 之后答案不会更小，因为中间产生重复贡献的重叠部分和这两个 $b$ 是否交换是没有关联的。同理，如果是两个 $(b_i,a_i)$ 和 $(b_j,a_j)$ 也不会有新的贡献。

所以唯一一种可能产生贡献的可能就是这两个区间的 $a$ 和 $b$ 大小关系不同。这也很好理解：相当于交换异侧端点，这样有可能消去中间重叠的部分。

那么有三种情况：

- 相离

	明显交换之后不会更优。
    
- 相交

	如果左边的是 $(a_i,b_i)$，右边的是 $(b_j,a_j)$，此时交换之后更优。
    
    反过来可以同理地处理。
    
- 包含

	如果大的区间是 $(a_i,b_i)$，小的是 $(b_j,a_j)$，那么交换更优。
    
	反过来也是同理地。
    
具体的实现上，我们不需要进行分类讨论。

首先我们可以把 $a_i$ 和 $b_i$ 的大小关系存储下来，然后全部变成 $a_i<b_i$ 的区间，然后在算贡献的时候注意不要算到 $a_i$ 和 $b_i$ 大小关系和自己相同的即可。这个可以分成 0/1 两种状态存储。

那么，接下来我们只需要处理两种情况。

第一种情况，也就是相交，贡献为 $2 \times (b_i-b_j)$；

第二种情况，也就是包含，贡献为 $2 \times (a_j-b_j)$。

我们可以看成 $2 \times (\min\{b_i,a_j\}-b_j)$ 一并处理。注意到这个式子里 $j$ 的限制更多，我们可以考虑枚举较小的区间，方便处理。

我们只需要找到所有 $b_j>b_i$ 中 $a_j$ 最小的即可算贡献，贡献为 $b_i-\max\{a_j,a_i\}$。所以我们考虑对区间按照 $b_i$ 排序，倒序扫一遍，边计算边添加即可。

复杂度 $O(n \log n)$。

## 代码

记得开 long long（（（

[Code & Submission](https://codeforces.com/contest/1513/submission/219106782)

---

