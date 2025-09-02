# Contact ATC

## 题目描述

Arkady the air traffic controller is now working with $ n $ planes in the air. All planes move along a straight coordinate axis with Arkady's station being at point $ 0 $ on it. The $ i $ -th plane, small enough to be represented by a point, currently has a coordinate of $ x_{i} $ and is moving with speed $ v_{i} $ . It's guaranteed that $ x_{i}·v_{i}<0 $ , i.e., all planes are moving towards the station.

Occasionally, the planes are affected by winds. With a wind of speed $ v_{wind} $ (not necessarily positive or integral), the speed of the $ i $ -th plane becomes $ v_{i}+v_{wind} $ .

According to weather report, the current wind has a steady speed falling inside the range $ [-w,w] $ (inclusive), but the exact value cannot be measured accurately since this value is rather small — smaller than the absolute value of speed of any plane.

Each plane should contact Arkady at the exact moment it passes above his station. And you are to help Arkady count the number of pairs of planes $ (i,j) $ ( $ i<j $ ) there are such that there is a possible value of wind speed, under which planes $ i $ and $ j $ contact Arkady at the same moment. This value needn't be the same across different pairs.

The wind speed is the same for all planes. You may assume that the wind has a steady speed and lasts arbitrarily long.

## 说明/提示

In the first example, the following $ 3 $ pairs of planes satisfy the requirements:

- $ (2,5) $  passes the station at time $ 3/4 $ with $ v_{wind}=1 $ ;
- $ (3,4) $  passes the station at time $ 2/5 $ with $ v_{wind}=1/2 $ ;
- $ (3,5) $  passes the station at time $ 4/7 $ with $ v_{wind}=-1/4 $ .

In the second example, each of the $ 3 $ planes with negative coordinates can form a valid pair with each of the other $ 3 $ , totaling $ 9 $ pairs.

## 样例 #1

### 输入

```
5 1
-3 2
-3 3
-1 2
1 -3
3 -5
```

### 输出

```
3
```

## 样例 #2

### 输入

```
6 1
-3 2
-2 2
-1 2
1 -2
2 -2
3 -2
```

### 输出

```
9
```

# 题解

## 作者：Genius_Star (赞：1)

[**或许更好的阅读体验。**](https://www.cnblogs.com/rgw2010/p/18373297)

### 思路：

考虑函数 $\operatorname{F}(v_0)_i$ 表示风速为 $v_0$ 时，$i$ 到达原点的时间，易得：

$$\operatorname{F}(v_0)_i = \frac{x_i}{v_i+v_0}$$

则若 $(i,j)$ 满足条件，需要满足 $\operatorname{F}(v_0)_i$ 与 $\operatorname{F}(v_0)_j$ 的交点的横坐标在 $[-m,m]$ 间，那么若 $\operatorname{F}(v_0)_i=\operatorname{F}(v_0)_j$，即 $\operatorname{F}(v_0)_i-\operatorname{F}(v_0)_j=0$。

根据**零点存在定理**：若区间 $[l,r]$ 满足 $\operatorname{f}(l) \le 0$ 且 $\operatorname{f}(r) \ge 0$，且函数连续，则 $[l,r]$ 至少有一个 $\operatorname{f}(x)$ 的零点。

那么判定 $\operatorname{F}(v_0)_i-\operatorname{F}(v_0)_j=0$ 在 $[-w,w]$ 是否有零点，只需要满足 $\operatorname{F}(-w)_i-\operatorname{F}(-w)_j \le 0$ 且 $\operatorname{F}(w)_i-\operatorname{F}(w)_j \ge 0$。

注意到 $\operatorname{F}(x)_i$ 有单调性，则设 $l_i=\operatorname{F}(-w)_i,r_i=\operatorname{F}(w)_i$。

则需要满足 $l_i \le l_j<0$ 即 $l_i \le l_j$，且 $r_i-r_j \ge 0$ 即 $r_i \ge r_j$。

那么若 $[l_i,r_i]$ 将 $[l_j,r_j]$ 包含，则 $(i,j)$ 是有贡献的，这个问题是简单题，不作多说，直接树状数组维护即可。

时间复杂度为 $O(N \log N)$。

**注意离散化。**

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define pi pair<ll,ll>
#define pii pair<ll,pair<ll,ll>>
#define iip pair<pair<ll,ll>,ll>
#define ppii pair<pair<ll,ll>,pair<ll,ll>>
#define fi first
#define se second
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define Full(a) memset(a,0,sizeof(a))
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
#define For(i,l,r) for(int i=l;i<=r;i++)
#define _For(i,l,r) for(int i=r;i>=l;i--)
using namespace std;
typedef long double ld;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const ll N=1e6+10;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
struct Node{
    ll l,r;
	bool operator<(const Node&rhs)const{
		if(r!=rhs.r)
		  return r<rhs.r;
		return l>rhs.l;
	}
}A[N];
ll T,n,m,l1,l2,ans;
ld L[N],R[N],h1[N],h2[N];
ll x[N],v[N],a[N];
void add(ll x){
	for(int i=x;i<=l1;i+=lowbit(i))
	  a[i]++;
}
ll query(ll x){
	ll ans=0;
	for(int i=x;i;i-=lowbit(i))
	  ans+=a[i];
	return ans;
}
void work(ld &x){
	x=floor(x*1e11)/1e11;
}
void solve(){
    l1=l2=ans=0;
    n=read(),m=read();
    For(i,1,n){
        x[i]=-read();
        v[i]=read();
        L[i]=(ld)x[i]/((ld)v[i]-m);
        R[i]=(ld)x[i]/((ld)v[i]+m);
        work(L[i]),work(R[i]);
        h1[++l1]=L[i];
        a[l1]=0;
        h2[++l2]=R[i];
    }
    sort(h1+1,h1+l1+1);
    l1=unique(h1+1,h1+l1+1)-(h1+1);
    sort(h2+1,h2+l2+1);
    l2=unique(h2+1,h2+l2+1)-(h2+1);
    For(i,1,n){
        A[i].l=lower_bound(h1+1,h1+l1+1,L[i])-h1;
        A[i].r=lower_bound(h2+1,h2+l2+1,R[i])-h2;
        //cerr<<A[i].l<<' '<<A[i].r<<'\n';
    }
    sort(A+1,A+n+1);
	for(int i=1;i<=n;i++){
		ans+=i-1-query(A[i].l-1);
		add(A[i].l);
	}
    write(ans);
    putchar('\n');
}
bool End;
int main(){
    //open("wind.in","wind.out");
    T=1;
    while(T--)
      solve();
	return 0;
}
```

---

## 作者：攀岩高手 (赞：0)

设 $f_i(v_{wind})$ 表示风速为 $v_{wind}$ 时飞机 $i$ 到达原点的时间，则有 $f_i(v_{wind})=\frac{x_i}{v_i+v_{wind}}$。

对于一对飞机 $(i,j)(i<j)$，它对答案有贡献当且仅当 $f_i$ 与 $f_j$ 在区间 $[-w,w]$ 内有交点。容易发现函数 $f$ 具有单调性，因此可以设 $l_i=f_i(-w),r_i=f_i(w)$，则上述条件等价于 $(l_i\leq l_j\wedge r_i\geq r_j)\vee (l_i\geq l_j\wedge r_i\leq r_j)$。可以理解为区间 $[l_i,r_i]$ 与 $[l_j,r_j]$ 间存在包含关系。如果要统计这样的 $(i,j)$ 的数量，可以用扫描线 + 数据结构来处理。这里的数据结构需要支持插入操作和查询有多少个数大于等于给定的数的操作，可以选择平衡树。注意讨论去重时要谨慎，精度要求为 $10^{-10}$ 可能需要使用 long double。下面是代码：

```cpp
#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;
typedef long long ll;
typedef long double ld;
const int MAXN=110000;
const ld EPS=1E-11;
int dcmp(ld x)
{
	if (fabs(x)<EPS) return 0;
	return x<0?-1:1;
}
struct Splay
{
	struct Node
	{
		int c[2], fa, siz;
		ld val;
	} tr[MAXN];
	int cnt, root;
	inline int newNode(ld k)
	{
		int x=++cnt;
		tr[x].c[0]=tr[x].c[1]=tr[x].fa=0;
		tr[x].val=k; tr[x].siz=1;
		return x;
	}
	inline void init()
	{
		cnt=root=0;
	}
	#define lc tr[x].c[0]
	#define rc tr[x].c[1]
	#define par tr[x].fa
	inline void pushup(int x)
	{
		tr[x].siz=tr[lc].siz+tr[rc].siz+1;
	}
	inline bool getlr(int x)
	{
		return tr[par].c[1]==x;
	}
	inline void rotate(int x)
	{
		int y=par, z=tr[y].fa;
		bool k=getlr(x); int w=tr[x].c[k^1];
		if (z) tr[z].c[getlr(y)]=x; par=z;
		tr[y].c[k]=w; if (w) tr[w].fa=y;
		tr[x].c[k^1]=y; tr[y].fa=x; pushup(y); 
	}
	void splay(int x, int y)
	{
		while (par!=y)
		{
			if (tr[par].fa!=y)
				rotate(getlr(x)^getlr(par)?x:par);
			rotate(x);
		}
		pushup(x);
		if (!y) root=x;
	}
	// 查找第一个值大于等于 k 的结点 
	int find(ld k)
	{
		int x=root, y=0;
		while (x)
			if (~dcmp(tr[x].val-k)) y=x, x=lc;
			else x=rc;
		if (y) splay(y, 0);
		return y;
	}
	// 插入一个值为 k 的结点 
	void insert(ld k)
	{
		if (!root)
		{
			root=newNode(k);
			return;
		}
		int x=find(k);
		if (!x)
		{
			x=root; while (rc) x=rc;
			rc=newNode(k);
			tr[rc].fa=x; splay(rc, 0);
		}
		else if (!lc)
		{
			lc=newNode(k);
			tr[lc].fa=x; pushup(x);
		}
		else
		{
			x=lc; while (rc) x=rc;
			rc=newNode(k);
			tr[rc].fa=x; splay(rc, 0);
		}
	}
	// 查询值小于 k 的结点数
	inline int rank(ld k) 
	{
		int x=find(k);
		if (!x) return tr[root].siz;
		return tr[lc].siz;
	}
	#undef lc
	#undef rc
	#undef par
} splay;
struct Plane
{
	int x, v;
	ld l, r;
	bool operator < (const Plane& rhs) const
	{
		return dcmp(l-rhs.l)==-1||dcmp(l-rhs.l)==0&&dcmp(r-rhs.r)==-1;
	}
};
bool cmpl(const Plane& lhs, const Plane& rhs)
{
	return lhs.l<rhs.l;
}
bool cmpr(const Plane& lhs, const Plane& rhs)
{
	return lhs.r<rhs.r;
}
ll calc(vector<Plane> a)
{
	ll res=0;
	sort(a.begin(), a.end(), cmpl);
	splay.init();
	for (int i=0, j=0; i<a.size(); i++)
	{
		while (j<a.size()&&dcmp(a[j].l-a[i].l)!=1)
			splay.insert(a[j++].r);
		res+=j-splay.rank(a[i].r);
	}
	sort(a.begin(), a.end(), cmpr);
	splay.init();
	for (int i=0, j=0; i<a.size(); i++)
	{
		while (j<a.size()&&dcmp(a[j].r-a[i].r)!=1)
			splay.insert(a[j++].l);
		res+=j-splay.rank(a[i].l);
	}
	map<Plane, int> dic;
	for (Plane p:a) dic[p]++;
	for (Plane p:a)
		if (dic.count(p)) res-=dic[p];
	return res;
}
vector<Plane> pla;
int main()
{
//	freopen("D.in", "r", stdin);
//	freopen("D.out", "w", stdout);
	int n, w;
	scanf("%d%d", &n, &w);
	for (int i=1; i<=n; i++)
	{
		Plane t;
		scanf("%d%d", &t.x, &t.v);
		pla.push_back(t);
	}
	for (Plane& p:pla)
	{
		p.l=-(ld)p.x/(p.v-w);
		p.r=-(ld)p.x/(p.v+w);
	}
	printf("%lld\n", (calc(pla)-(int)pla.size())/2);
	return 0;
}
```

可能也可以分治做，这样可以省掉写平衡树。

---

## 作者：Mortidesperatslav (赞：0)

（因为我懒，直接搬模拟赛 AC 代码了，测试我题解的时候记得删掉文件和多测。）

模拟赛做到了，过来水一篇题解。

我们考虑预处理出每个点到原点的最小时间 $a_i$ 和最大时间 $b_i$。显然只有 $a_j \le a_i$ 且 $b_j \ge b_i$ 的一对点 $(i,j)$ 可以相遇。

这就变成了二维偏序。

我们考虑按照 $a_i$ 为第一关键字，$b_i$ 为第二关键字排序。排完之后因为 $a_i$ 已经有序，离散化一下，把 $b_i$ 变成一个数组，归并排序求逆序对就好了。

因为 `long double` 一直 T 飞，我就用了 `__int128`，写得非常鬼畜……

时间复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T, n;
long long m;
long long ans;
__int128 x[2000005], v[2000005];
struct node{
	__int128 xx, sx;
}a[2000005];
void msort(int l, int r){//归并排序
	if (l == r)
		return;
	int m = (l + r) >> 1, i = l, j = m + 1, k = l;
	msort(l, m);
	msort(m + 1, r);
	while (i <= m && j <= r)
		if (x[i] < x[j])
			v[k++] = x[i++];
		else
			v[k++] = x[j++], ans += m - i + 1;
	while (i <= m)
		v[k++] = x[i++];
	while (j <= r)
		v[k++] = x[j++];
	for (int ii = l; ii <= r; ii++)
		x[ii] = v[ii];
}
int main(){
	freopen("wind.in", "r", stdin);
	freopen("wind.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> T;
	while (T--){
		ans = 0;
		cin >> n >> m;
		for (int i = 1; i <= n; i++){
			long long xx;
			cin >> xx;
			x[i] = xx;
		}
		for (int i = 1; i <= n; i++){
			long long vv;
			cin >> vv;
			v[i] = vv;
		}
		for (int i = 1; i <= n; i++){//乘上一个巨大的值，防止浮点数龟速运算和精度误差
			a[i].xx = -(__int128)x[i] * 1000000000000000000ll / (v[i] + m);
			a[i].sx = -(__int128)x[i] * 1000000000000000000ll / (v[i] - m);
		//	cout << i << " " << a[i].xx << " " << a[i].sx << "\n";
		}
		sort(a + 1, a + 1 + n, [](node a, node b){return ((a.xx != b.xx) ? (a.xx < b.xx) : (a.sx > b.sx));});//排完序
		for (int i = 1; i <= n; i++)
			x[i] = a[i].sx;//离散化
		msort(1, n);//跑归并
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：Tony2 (赞：0)

很好奇旁边那位老哥为什么要用平衡树。

思路相同，将要查询的内容离散化即可。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define ___ ((ld)0.0000000001)
using namespace std;
const int N = 1e5+5;
int n, w, tot;
ll ans;
ld l[N], r[N], b[N];
int l2[N], r2[N];
pair<int, int> a[N];
struct tree{
	int a[N];
	void add(int x, int k){
		for (; x <= tot; x += x&-x) a[x] += k;
	}
	int ask(int x){
		int res = 0;
		for (; x; x -= x&-x) res += a[x];
		return res;
	} 
}T;
bool eq(ld x, ld y){
	return fabs(x-y) < ___;
}
void work(ld &x){
	x = floor(x*1e11)/1e11;
}
int uq(ld *a, int *c){
	for (int i = 1; i <= n; i++) work(a[i]), b[i] = a[i];
	sort(b+1, b+1+n);
	int tot = unique(b+1, b+1+n)-b-1;
	for (int i = 1; i <= n; i++) c[i] = lower_bound(b+1, b+1+tot, a[i])-b;
	return tot;
}
bool cmp(pair<int, int> x, pair<int, int> y){
	return x.second == y.second ? x.first > y.first : x.second < y.second;
}
int main(){
	std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	freopen("in.txt", "r", stdin);
//	freopen("out.out", "w", stdout);
	cin >> n >> w;
	for (int i = 1; i <= n; i++){
		int x, v;
		cin >> x >> v;
		x = -x;
		l[i] = (ld)x/((ld)v-w), r[i] = (ld)x/((ld)v+w);
	}
	tot = uq(l, l2);
	uq(r, r2);
	for (int i = 1; i <= n; i++) a[i] = make_pair(l2[i], r2[i]);
	sort(a+1, a+1+n, cmp);
	for (int i = 1; i <= n; i++){
		ans += T.ask(tot)-T.ask(a[i].first-1);
		T.add(a[i].first, 1);
	}
	cout << ans;
	return 0;
}
```

---

