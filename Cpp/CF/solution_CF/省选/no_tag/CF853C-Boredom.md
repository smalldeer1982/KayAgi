# Boredom

## 题目描述

### 题意

给定一个$\ n*n(1\leq n\leq 200,000)\ $的矩阵$A$，矩阵所在的直角坐标系以向上、向右为正方向。

从 $A$ 的第 $i$ 行中选出第$s_i$个格子标记为黑色,保证被选中的 $n$ 个格子不在同一列

再给定该矩阵的一个子矩阵 $B$ 

$B$ 的**左、右**边界横坐标分别为$l,r$,**下、上**边界纵坐标分别为$d,u(1\leq l\leq r\leq n,1\leq d\leq u\leq	n)$.



请你回答:有几个好的矩阵与 $B$ 相交？

会有 $T(1\leq T\leq 200,000)$ 组离线询问.

我们称一个矩阵为好的矩阵，当且仅当该矩阵至少存在一条对角线使其两个端点上的格子为黑色格子。

## 样例 #1

### 输入

```
2 3
1 2
1 1 1 1
1 1 1 2
1 1 2 2
```

### 输出

```
1
1
1
```

## 样例 #2

### 输入

```
4 2
1 3 2 4
4 1 4 4
1 1 2 3
```

### 输出

```
3
5
```

# 题解

## 作者：hh20080501hh (赞：4)

# 题目
[题目戳我哦](https://www.luogu.com.cn/problem/CF853C)

题意简述：给定 $n$ 个黑点，有 $m$ 个矩形，统计每个矩形与任意两个黑点作为对角线组成的矩形有交的数量。

# 分析
我们发现统计有交不好统计，因为这样有很多情况，例如上边相交，下边相交，包含等等情况。但是我们找没有交是很好找的，因为这样就四种情况。为了更好的表述，我们记询问矩形为 $A$，黑点矩形为 $B$，四种情况即为：$A$ 在 $B$ 上方，$A$ 在 $B$ 下方，$A$ 在 $B$ 左方，$A$ 在 $B$ 右方。

我们考虑怎么计数每一种情况：显然是从这类黑点中选 $2$ 个黑点，即 $n\times(n-1)\div2$。

但是这样会计重，因为左边和上边会有左上方重叠的点，其余同理，所以我们要把算重的贡献减掉。那我们只需要做一遍扫描线就可以很容易的减掉了。

# 代码
思路理清楚了，代码就很好写，但是毕竟有扫描线，可能会有一点点长。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

typedef long long ll;

const int N = 2e5+10;

int n , m;
struct Square
{
	int l , r , u , d;
	ll dl , dr , ul , ur;
}square[N];
struct Point
{
	int x , y;
}a[N];
struct Seg
{
	int y , x1 , x2 , op;
	int id , ud;
	bool operator <(const Seg &o) const
	{
		if (y==o.y) return op<o.op;
		return y<o.y;
	}
}seg[N<<2];
int idx;
struct node 
{
	int l , r;
	ll sum;
}tr[N<<2];

inline void pushup (int u)
{
	tr[u].sum = tr[u<<1].sum + tr[u<<1|1].sum;
}

void build (int u , int l , int r)
{
	tr[u] = {l , r , 0};
	if (l==r) return;
	int mid = (l+r)>>1;
	build(u<<1 , l , mid) , build(u<<1|1 , mid+1 , r);
}

void modify(int u , int id)
{
	if (tr[u].l==id && tr[u].r==id)
	{
		tr[u].sum++;
	}
	else 
	{
		int mid = (tr[u].l+tr[u].r)>>1;
		if (id<=mid) modify(u<<1 , id);
		else modify(u<<1|1 , id);
		pushup(u);
	}
}

int query (int u , int l , int r)
{
	if (l<=tr[u].l && tr[u].r<=r)
	{
		return tr[u].sum;
	}
	else
	{
		int mid = (tr[u].l+tr[u].r)>>1;
		int res = 0;
		if (l<=mid) res += query(u<<1 , l , r);
		if (r>mid) res += query(u<<1|1 , l , r);
		return res;
	}
}

inline void work(int i)
{
	if (!seg[i].op)
	{
		modify(1 , seg[i].x1);
	}
	else 
	{
		int tmpl , tmpr;
		if (seg[i].x1-1>=1) tmpl = query(1 , 1 , seg[i].x1-1);
		else tmpl = 0;
		if (seg[i].x2+1<=n) tmpr = query(1 , seg[i].x2+1 , n);
		else tmpr = 0;
		if (!seg[i].ud)
		{
			square[seg[i].id].dl = tmpl;
			square[seg[i].id].dr = tmpr;
		}
		if (seg[i].ud)
		{
			square[seg[i].id].ul = tmpl;
			square[seg[i].id].ur = tmpr;
		}
	}	
}

inline ll calc (int x)
{
	return (ll)x*(x-1ll)/2ll;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
	
	cin >> n >> m;
	for (int i=1 ; i<=n ; i++) 
	{
		a[i].y = i , cin >> a[i].x;
		seg[++idx] = {a[i].x , i , i , 0 , i , 0};
	}
	for (int i=1 ; i<=m ; i++)
	{
		cin >> square[i].l >> square[i].d >> square[i].r >> square[i].u;
		seg[++idx] = {square[i].d-1 , square[i].l , square[i].r , 1 , i , 0};
		seg[++idx] = {square[i].u , square[i].l , square[i].r , 1 , i , 1};
	}
	build(1 , 1 , n+1);
	sort(seg+1 , seg+1+idx);
	for (int i=1 ; i<=idx ; i++)
	{
		if (seg[i].y==seg[i+1].y)
		{
			work(i);
			i++;
		}
		work(i);
	}
	for (int i=1 ; i<=m ; i++)
	{
		auto t = square[i];
		ll ans = calc(n);
		ans -= (ll)calc(t.l-1)+calc(n-t.r)+calc(t.d-1)+calc(n-t.u);
		ans += (ll)calc(t.l-1-t.ul)+calc(n-t.r-t.ur)+calc(t.dl)+calc(t.dr);
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：7KByte (赞：3)

简单容斥。

观察一下不难发现答案为总方案数$\dfrac{N(N+1)}{2}$，减去在矩形一边的贡献，再加上在矩形一角的贡献。

我们只考虑在矩形左边和在矩形左下角的贡献。

由于是个排列，矩形左边的贡献就是$\dfrac{(l-1)(l-2)}{2}$。

矩形右下角是个模板二维数点，离线树状数组即可。

我们要求四边和四角的贡献，只用将整个网格进行四次旋转$90$°，然后统计贡献即可。

$\rm O((N+M)\log N)$

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 200005
using namespace std;
int a[N],c[N],n,m,T,b[N];long long ans[N];
struct node{
	int op,x,y,l,r;
	bool operator<(const node o)const{return l<o.l;}
}u[N];
inline void add(int x){for(;x<=n;x+=x&-x)c[x]++;}
inline int ask(int x){int sum=0;for(;x;x-=x&-x)sum+=c[x];return sum;}
void calc(){
	sort(u+1,u+m+1);int j=1;
	memset(c,0,sizeof(c));
	rep(i,1,n){
		while(j<=m&&u[j].l==i){
			int cur=ask(u[j].x-1);
			ans[u[j].op]+=1LL*cur*(cur-1)/2-1LL*(i-1)*(i-2)/2;
			j++;
		}
		add(a[i]);
	}
}
void rev(){
	rep(i,1,n)b[a[i]]=n+1-i;
	rep(i,1,n)a[i]=b[i];
	rep(i,1,m){
		int x=u[i].x,y=u[i].y;
		u[i].x=n+1-u[i].r,u[i].y=n+1-u[i].l;
		u[i].l=x,u[i].r=y;
	}
}
int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,n)scanf("%d",&a[i]);
	rep(i,1,m)scanf("%d%d%d%d",&u[i].l,&u[i].x,&u[i].r,&u[i].y),u[i].op=i,ans[i]=1LL*(n-1)*n/2;
	calc();rev();
	calc();rev();
	calc();rev();
	calc();
	rep(i,1,m)printf("%lld \n",ans[i]);
	return 0;
}
```

---

## 作者：Populus_euphratica (赞：1)

## 『CF853C』Boredom

### 做法

因为保证每行每列都只有一个黑点，那么如果有 $n$ 个黑点，总方案数一定是 $\frac{n \times(n - 1)}{2}$ 这么多的。

证明是显然的，先选取一个点后，再任意选取另一个点都可以构成矩形，所以方案数是这么多。

对于这种问题，有一个很经典的容斥思路：

用总共的减去四边之外的再加上被多减去的四个角的。

四个方向以及四个角可以通过旋转解决，所以现在来考虑如何统计单个边和单个角的。

边外很好办，排个序就行，来考虑角上的。

很明显的一个二维数点问题，排序消一维，树状数组消以为，刚好在排序的时候把边外面的也统计一下。

没啥实现难度，注意下输入的顺序以及在旋转处的细节即可。

时间复杂度 $O(n\log n)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int Maxn = 200010;
int m, n;
int a[Maxn], b[Maxn];
struct node{
    int id, l, r, d, u;
}c[Maxn];
int sum[Maxn];
int lowbit(int x){return x & (-x);}
void add(int x){
    while(x <= n){
        sum[x]++;
        x += lowbit(x);
    }
}
int ask(int x){
    int s = 0;
    while(x){
        s += sum[x];
        x -= lowbit(x);
    }
    return s;
}
void change(){
    for(int i = 1 ; i <= n ; i++) b[a[i]] = n + 1 - i;
    for(int i = 1 ; i <= n ; i++) a[i] = b[i];
    for(int i = 1 ; i <= m ; i++){
        int x = c[i].d, y = c[i].u;
        c[i].d = n + 1 - c[i].r;
        c[i].u = n + 1 - c[i].l;
        c[i].l = x, c[i].r = y;
    }
}
int ans[Maxn];
bool cmp(node x, node y){return x.l < y.l;}
void solve(){
    for(int i = 1 ; i <= n ; i++) sum[i] = 0;
    sort(c + 1, c + m + 1, cmp);
    for(int i = 1, j = 1 ; i <= n ; i++){
        while(j <= m && c[j].l == i){
            int s = ask(c[j].d - 1);
            ans[c[j].id] += s * (s - 1) / 2 - (i - 1) * (i - 2) / 2;
            j++;
        }
        add(a[i]);
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for(int i = 1 ; i <= n ; i++) cin >> a[i];
    for(int i = 1 ; i <= m ; i++){
        cin >> c[i].l >> c[i].d >> c[i].r >> c[i].u;
        c[i].id = i;
        ans[i] = n * (n - 1) / 2;
    }
    solve(); change();
    solve(); change();
    solve(); change();
    solve();
    for(int i = 1 ; i <= m ; i++) cout << ans[i] << '\n';
    cout << '\n';
    return 0;
}
```

---

## 作者：RainFestival (赞：1)

先考虑 $1$ 组询问的情况。

直接算合法方案不好算，我们可以考虑容斥。

注意到题面中 $\texttt{no two marked squares share the same row or the same column}$，翻译成中文就是**没有两个被标记的格子在同一行或同一列**，这是解决问题的关键。

答案 $=$ 总方案 $-$ 不合法方案。

记 $s(n)$ 为 $n$ 个不在同一行同一列的点构成的矩形数量，显然~~从题面中得知~~ $n\times (n-1)/2$。

**总方案**很简单，就是 $s(n)$。

不合法方案只有**四种情况**，分别是矩形两个角都在给定方位上面，下面，左边，右边。

记上面的点有 $n_1$ 个，左边的点有 $n_2$ 个，右边的点有 $n_3$ 个，下面的点有 $n_4$ 个，则答案为 $s(n_1)+s(n_2)+s(n_3)+s(n_4)$。

考虑到如果矩形的两个角都在左上或左下或右上或右下，则会**计算两次**，所以记左上的点有 $n_5$ 个，左下的点有 $n_6$ 个，右上的点有 $n_7$ 个，右下的点有 $n_8$ 个，则答案还需要减去 $s(n_5)+s(n_6)+s(n_7)+s(n_8)$。

所以总答案就是 $s(n)-( s(n_1)+s(n_2)+s(n_3)+s(n_4)-(s(n_5)+s(n_6)+s(n_7)+s(n_8)))$

$n,n_1,n_2,n_3,n_4$ 都可以 $O(1)$ 计算，可是 $n_5,n_6,n_7,n_8$ 都需要 $O(n)$。

考虑将询问离线，可以使用 $\texttt{BIT}$，将总复杂度优化到 $O((n+q)\log n)$。虽然带有 $4$ 倍常数，即要分别计算 $s_5,s_6,s_7,s_8$ 共计 $4$ 次，但是 $n,q$ 只有 $2\times 10^5$，时限 $2s$ 并且 $\texttt{codeforces}$ 的机器跑得非常快，不需要卡常。

代码如下，写得很丑，注意读入格式：

```cpp
#include<cstdio>
#include<cstdlib>
#include<utility>
#include<algorithm> 
struct node
{
	int lft,rgt,lst,fst;
};
struct bit
{
	int n,s[600005];
	int lowbit(int x){return x&(-x);}
	int query(int x){int ans=0;for (;x>=1;x=x-lowbit(x)) ans=ans+s[x];return ans;}
	void add(int x,int y){for (;x<=n;x=x+lowbit(x)) s[x]=s[x]+y;}
	int full(int x,int y){return query(y)-query(x-1)==y-x+1;}
	void clear(){for (int i=1;i<=n;i++) s[i]=0;n=0;}
};
bit t;
node g[200005];
int n,q,s[200005],s1[200005],s2[200005],s3[200005],s4[200005];
long long ans[200005];
std::pair<std::pair<int,int>,int> f[200005];
int main()
{
	scanf("%d%d",&n,&q);
	for (int i=1;i<=n;i++) scanf("%d",&s[i]);
	for (int i=1;i<=q;i++) scanf("%d%d%d%d",&g[i].lst,&g[i].lft,&g[i].fst,&g[i].rgt);
	for (int i=1;i<=q;i++) ans[i]=ans[i]+1ll*(g[i].lft-1)*(g[i].lft-2)/2+1ll*(n-g[i].rgt)*(n-g[i].rgt-1)/2;
	for (int i=1;i<=q;i++) ans[i]=ans[i]+1ll*(g[i].lst-1)*(g[i].lst-2)/2+1ll*(n-g[i].fst)*(n-g[i].fst-1)/2;
	t.clear();t.n=n;
	for (int i=1;i<=q;i++) f[i]=std::make_pair(std::make_pair(g[i].fst+1,g[i].lft-1),i);
	std::stable_sort(f+1,f+q+1);std::reverse(f+1,f+q+1);
	int x;
	x=1;
	for (int i=n+1;i>=0;i--)
	{
		if (i!=n+1&&i!=0) t.add(s[i],1);
		for (;x<=q;x++)
		{
			if (f[x].first.first<i) break;
			int y=t.query(f[x].first.second);
			s1[f[x].second]=y;
		}
	}
	t.clear();t.n=n;
	for (int i=1;i<=q;i++) f[i]=std::make_pair(std::make_pair(g[i].fst+1,g[i].rgt+1),i);
	std::stable_sort(f+1,f+q+1);std::reverse(f+1,f+q+1);
	x=1;
	for (int i=n+1;i>=0;i--)
	{
		if (i!=n+1&&i!=0) t.add(s[i],1);
		for (;x<=q;x++)
		{
			if (f[x].first.first<i) break;
			int y=t.query(n)-t.query(f[x].first.second-1);
			s2[f[x].second]=y;
		}
	}
//	return 0;
	t.clear();t.n=n;
	for (int i=1;i<=q;i++) f[i]=std::make_pair(std::make_pair(g[i].lst-1,g[i].lft-1),i);
	std::stable_sort(f+1,f+q+1);
	x=1;
	for (int i=0;i<=n+1;i++)
	{
		if (i!=n+1&&i!=0) t.add(s[i],1);
		for (;x<=q;x++)
		{
			if (f[x].first.first>i) break;
			int y=t.query(f[x].first.second);
			s3[f[x].second]=y;
		}
	}
	t.clear();t.n=n;
	for (int i=1;i<=q;i++) f[i]=std::make_pair(std::make_pair(g[i].lst-1,g[i].rgt+1),i);
	std::stable_sort(f+1,f+q+1);
	x=1;
	for (int i=0;i<=n+1;i++)
	{
		if (i!=n+1&&i!=0) t.add(s[i],1);
		for (;x<=q;x++)
		{
			if (f[x].first.first>i) break;
			int y=t.query(n)-t.query(f[x].first.second-1);
			s4[f[x].second]=y;
		}
	}
	for (int i=1;i<=q;i++) ans[i]=ans[i]-1ll*s1[i]*(s1[i]-1)/2-1ll*s2[i]*(s2[i]-1)/2-1ll*s3[i]*(s3[i]-1)/2-1ll*s4[i]*(s4[i]-1)/2;
	for (int i=1;i<=q;i++) printf("%lld\n",1ll*n*(n-1)/2-ans[i]);
	return 0;
}
```

跑了 $11.15s$ 在目前的 $20$ 份 $\texttt{AC}$ 记录中排名第 $5$。

---

## 作者：__Floze3__ (赞：1)

## 思路简述

这里给出一个较为暴力，但想与写都比较方便的方法。

对于每一个矩形的询问，为了不重不漏，我们可以以矩形的四条边为参考，将整个大矩形划分为 $9$ 个小矩形，如下图（其中黑色小矩形为询问的矩形）：

![](https://cdn.luogu.com.cn/upload/image_hosting/j4mwb4m2.png)

我们统计出每个小矩形内部的黑点个数，记为 $S_i$，那么我们可以得出与这个矩形有公共点的好的矩阵的计算公式：

$$
S_1 \times (S_5 + S_6 + S_8 + S_9) + S_2 * (S_4 + S_5 + S_6 + S_7 + S_8 + S_9) \\
+ S_3 \times (S_4 + S_5 + S_7 + S_8) + S_4 \times (S_5 + S_6 + S_8 + S_9) \\
+ S_5 \times (S_6 + S_7 + S_8 + S_9) + S_6 \times(S_7 + S_8)  + S_5 \times (S_5 - 1) \div 2
$$

那么只要把询问离线下来跑二维数点即可。

由于要把一个询问拆成 $9$ 个询问，理论上常数会很大，但实际上跑起来还挺快？

## 代码

```cpp
#include <bits/stdc++.h>
#define mp(x, y) std::make_pair(x, y)
#define eb emplace_back
#define fi first
#define se second
#define il inline
#define file(name)                 \
  freopen(name ".in", "r", stdin); \
  freopen(name ".out", "w", stdout);

typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef std::pair<int, int> pii;
typedef std::vector<int> vi;

const int N = 2e5 + 5;
const int mod = 998244353;
const int inf = 0x3f3f3f3f;
const ll infll = 0x3f3f3f3f3f3f3f3f;

int n, q, b[N], t[N], res[N][10];

il void add(int p, int v) {
  for (; p <= n; p += p & -p) t[p] += v;
  return ;
}

il int ask(int p) {
  int res = 0;
  for (; p; p -= p & -p) res += t[p];
  return res;
}

struct query {
  int x, y, id, type;
} qu[10 * N];

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
  std::cin >> n >> q;
  for (int i = 1; i <= n; ++i) {
    int x;
    std::cin >> x;
    b[x] = i;
  }
  int cnt = 0;
  for (int i = 1; i <= q; ++i) {
    int l, d, r, u;
    std::cin >> l >> d >> r >> u;
    qu[++cnt] = {n, l - 1, i, 1};
    qu[++cnt] = {u, l - 1, i, 2};
    qu[++cnt] = {d - 1, l - 1, i, 3};
    qu[++cnt] = {n, r, i, 4};
    qu[++cnt] = {u, r, i, 5};
    qu[++cnt] = {d - 1, r, i, 6};
    qu[++cnt] = {n, n, i, 7};
    qu[++cnt] = {u, n, i, 8};
    qu[++cnt] = {d - 1, n, i, 9};
  }
  for (int i = 1; i <= n; ++i) qu[++cnt] = {i, b[i], 0, 0};
  std::sort(qu + 1, qu + 1 + cnt, [](query x, query y) {
    return x.x ^ y.x ? x.x < y.x : x.id < y.id;
  });
  for (int i = 1; i <= cnt; ++i) {
    if (!qu[i].id) add(qu[i].y, 1);
    else res[qu[i].id][qu[i].type] = ask(qu[i].y);
  }
  for (int i = 1; i <= q; ++i) {
    int s1 = res[i][1] - res[i][2];
    int s2 = res[i][2] - res[i][3];
    int s3 = res[i][3];
    int s4 = res[i][4] - res[i][1] - res[i][5] + res[i][2];
    int s5 = res[i][5] - res[i][2] - res[i][6] + res[i][3];
    int s6 = res[i][6] - res[i][3];
    int s7 = res[i][7] - res[i][4] - res[i][8] + res[i][5];
    int s8 = res[i][8] - res[i][5] - res[i][9] + res[i][6];
    int s9 = res[i][9] - res[i][6];
    ll ans = 0;
    ans += 1ll * s1 * (s5 + s6 + s8 + s9);
    ans += 1ll * s2 * (s5 + s6 + s8 + s9 + s4 + s7);
    ans += 1ll * s3 * (s4 + s5 + s7 + s8);
    ans += 1ll * s4 * (s5 + s6 + s8 + s9);
    ans += 1ll * s5 * (s6 + s7 + s8 + s9);
    ans += 1ll * s6 * (s7 + s8);
    ans += 1ll * s5 * (s5 - 1) / 2;
    std::cout << ans << '\n';
  }
  return 0;
}

/*
all the things you do
the words you say
will all come back to you
*/

```

---

## 作者：Hoks (赞：0)

## 前言
简单容斥题，duel 一半有事没写，补一下。

摘自 [杂题选做](https://www.luogu.com.cn/training/597433)。
## 思路分析
数和矩阵交也太 hard 了。

容斥下变成数和矩阵不交的。

对于不交的数法，画个图就很清楚了：
![](https://cdn.luogu.com.cn/upload/image_hosting/4pu0sc58.png)

在这个图里面，黄色的是要计算的矩阵。

然后我们的计算就是在黄色上/下/左/右的矩形减去重复部分。

重复部分就是蓝色部分。

对于红色矩形并上旁边两个蓝色矩形这种数数是平凡的，只需要考虑蓝色的计数即可。

然后这就变成了一个二维偏序问题，我们需要数出蓝色的矩形数量。

离线下来直接树状数组扫描线扫一遍就行了。
## 代码
注意这个题目的读入很史，别看错了。
```cpp
#include<bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
#define calc(x) ((x-1)*(x)>>1)
#define int long long
using namespace std;
const int N=2e5+10,V=315,M=23,INF=1e9,mod=998244353;
char qwq;
struct BIT//binary_indexed_tree
{
    int c[N],n;BIT(){memset(c,0,sizeof c);}
    void modify(int x,int v){for(;x<=n;x+=x&-x) c[x]+=v;}
    int query(int x){int res=0;for(;x>0;x-=x&-x) res+=c[x];return res;}
    void mdf(int l,int r,int v){modify(l,v),modify(r+1,-v);}
    int qry(int l,int r){return query(r)-query(l-1);}
}tt;
int n,m,a[N],x[N],y[N],xx[N],yy[N],ans[N];
tuple<int,int,int>q[N];
char qwqq;
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'||c=='|'||c=='-'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void solve()
{
    tt.n=n=read(),m=read();for(int i=1;i<=n;i++) a[read()]=i;
    for(int i=1;i<=m;i++)
    {
        y[i]=read(),x[i]=read(),yy[i]=read(),xx[i]=read();
        ans[i]=calc(n)-calc(x[i]-1)-calc(y[i]-1)-calc(n-xx[i])-calc(n-yy[i]);
        q[i]={x[i]-1,y[i]-1,i};
    }sort(q+1,q+1+m);
    for(int i=1,j=1;i<=m;i++)
    {
        while(j<=get<0>(q[i])) tt.modify(a[j],1),j++;
        ans[get<2>(q[i])]+=calc(tt.query(get<1>(q[i])));
    }for(int i=1;i<=n;i++) tt.c[i]=0;
    for(int i=1;i<=m;i++) q[i]={xx[i]+1,y[i]-1,i};sort(q+1,q+1+m);reverse(q+1,q+1+m);
    for(int i=1,j=n;i<=m;i++)
    {
        while(j>=get<0>(q[i])) tt.modify(a[j],1),j--;
        ans[get<2>(q[i])]+=calc(tt.query(get<1>(q[i])));
    }for(int i=1;i<=n;i++) tt.c[i]=0;
    for(int i=1;i<=m;i++) q[i]={xx[i]+1,yy[i]+1,i};sort(q+1,q+1+m);reverse(q+1,q+1+m);
    for(int i=1,j=n;i<=m;i++)
    {
        while(j>=get<0>(q[i])) tt.modify(n-a[j]+1,1),j--;
        ans[get<2>(q[i])]+=calc(tt.query(n-get<1>(q[i])+1));
    }for(int i=1;i<=n;i++) tt.c[i]=0;
    for(int i=1;i<=m;i++) q[i]={x[i]-1,yy[i]+1,i};sort(q+1,q+1+m);
    for(int i=1,j=1;i<=m;i++)
    {
        while(j<=get<0>(q[i])) tt.modify(n-a[j]+1,1),j++;
        ans[get<2>(q[i])]+=calc(tt.query(n-get<1>(q[i])+1));
    }for(int i=1;i<=m;i++) print(ans[i]),put('\n');
}
signed main()
{
    int T=1;
    // cout<<(&qwqq-&qwq)/1024.0/1024.0;
    // T=read();
    while(T--) solve();
    genshin:;flush();return 0;
}
```

---

## 作者：hellolin (赞：0)

显然所有好的矩形数是 $\frac{n(n-1)}{2}$，硬算每个矩形的交就爆了，考虑优化。

正难则反，考虑没有交的好矩形数量。两个黑点确定一个好矩形，知如果两个黑点都在查询矩形外，那么这个好矩形一定和当前矩形没有交。

于是考虑容斥，这个数量为上下左右好矩形数减去四个角方向的好矩形数。

上下左右直接 $O(1)$ 算，四个角方向可以用 BIT 维护一下做到 $O(\log n)$。

嫌求四个方向太麻烦可以旋转九十度，每次求左边减左下角即可。

矩形可以离线，故总时间复杂度 $O(n\log n)$。

``` cpp
static constexpr int N = 2e5 + 5;
int n, q;
i64 ans[N];

struct coor {
  int x, y;
  void rev() { *this = {y, n - x + 1}; } // 顺时针旋转九十度
  bool operator<(const coor &p) const { return x < p.x; }
};
struct rect {
  coor a, b; // top-left, bottom-right
  int idx;
  bool operator<(const rect &p) const { return a.x < p.a.x; }
} r[N];
coor b[N];
int tr[N];

void add(int x) {
  for (; x <= n; x += x & -x)
    ++tr[x];
}
int query(int x) {
  int res = 0;
  for (; x >= 1; x -= x & -x)
    res += tr[x];
  return res;
}

void work() {
  for (int i = 0; i < N; ++i)
    tr[i] = 0;
  sort(&r[1], &r[q + 1]);
  for (int i = 1, j = 1; i <= n; ++i) {
    for (; j <= q && r[j].a.x == i; ++j) {
      int k = query(r[j].b.y - 1); // 注意要减一，求他下面的黑点数量
      ans[r[j].idx] += (i64) (k - 1) * k / 2 - (i64) (i - 1) * (i - 2) / 2;
    }
    add(b[i].y);
  }
}
void rotate() {
  for (int i = 1; i <= n; ++i)
    b[i].rev();
  sort(&b[1], &b[n + 1]);
  for (int i = 1; i <= q; ++i) {
    r[i].a.rev(), r[i].b.rev();
    swap(r[i].a.x, r[i].b.x);
  }
}

void main() {
  io.read(n, q);
  for (int i = 1; i <= n; ++i)
    b[i].x = i, io.read(b[i].y);
  for (int i = 1; i <= q; ++i) {
    r[i].idx = i;
    io.read(r[i].a.x, r[i].b.y, r[i].b.x, r[i].a.y);
    ans[i] = (i64) n * (n - 1) / 2;
  }
  for (int i = 1; i <= 4; ++i)
    work(), i == 4 ? void() : rotate();
  for (int i = 1; i <= q; ++i)
    io.writeln(ans[i]);
}
```

---

## 作者：C_Pos_Princess (赞：0)

## 简要题意
给定一个矩形和一些点，求任意两个点构成的矩形中，与给定的矩形相交的有多少。

## 题解
我们很容易观察到，（容斥原理），求与矩形不相交的更好求。

那么如何求与矩形不相交的呢。

对于一个矩形，它上下左右都有与他不相交的，那按照四个方向统计又太麻烦，我们不如考虑将整个图旋转，转四次，每次统计左侧的就好了。

假设一个矩形左面的边横坐标为 $i$ ，则一共会有 $(i-1)\times (i-2) \div 2$ 个，这样我们会多加上四个角的贡献，那么我们统计左下角的，设一共有 $r$ 个点，则需要减去 $r \times (r-1) \div 2$ 个矩形的贡献。

关于点的个数，我们用二维数点维护就行，树状数组也好写。

### 代码分块（核心）
#### 旋转矩形
```
void change(){
	for(int i = 1;i<=n;i++) b[a[i]] = n+1-i;
	for(int i = 1;i<=n;i++) a[i] = b[i];
	for(int i = 1;i<=m;i++){
		int x = q[i].x,y = q[i].y;
		q[i].x = n+1-q[i].r;
		q[i].y = n+1-q[i].l;
		q[i].l = x,q[i].r = y;
	}	
}
```
#### 计算答案
```
void solve(){
	memset(tr,0,sizeof tr);
	sort(q+1,q+1+m);
	for(int i = 1,j = 1;i<=n;i++){
		while(j<=m && q[j].l == i){
			int res = query(q[j].x-1);
			ans[q[j].id]+=res*(res-1)/2-(i-1)*(i-2)/2;
			j++;
		}
		add(a[i]);
	}
}

```


## 完整代码

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
const int N= 2e5+10;
int a[N];
struct qus{
	int id;
	int l,r,x,y;
	bool operator<(const qus &t)const{
		return l<t.l;
	} 
}q[N];
int ans[N],b[N],tr[N];
int lowbit(int x){
	return x&(-x);
}
void add(int x){
	for(int i = x;i<=n;i+=lowbit(i))
		tr[i]+=1;
}

int query(int x){
	int res = 0;
	for(int i = x;i;i-=lowbit(i))
		res+=tr[i];
	return res;
}

void change(){
	for(int i = 1;i<=n;i++) b[a[i]] = n+1-i;
	for(int i = 1;i<=n;i++) a[i] = b[i];
	for(int i = 1;i<=m;i++){
		int x = q[i].x,y = q[i].y;
		q[i].x = n+1-q[i].r;
		q[i].y = n+1-q[i].l;
		q[i].l = x,q[i].r = y;
	}	
}

void solve(){
	
	memset(tr,0,sizeof tr);
	
	sort(q+1,q+1+m);
	
	for(int i = 1,j = 1;i<=n;i++){
		while(j<=m && q[j].l == i){
			int res = query(q[j].x-1);
			ans[q[j].id]+=res*(res-1)/2-(i-1)*(i-2)/2;
			j++;
		}
		add(a[i]);
	}
}



signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i = 1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i = 1;i<=m;i++){
		scanf("%lld%lld%lld%lld",&q[i].l,&q[i].x,&q[i].r,&q[i].y);
		q[i].id = i;
		ans[i] = n*(n-1)/2;	
	}
	solve();
	change();
	
	solve();
	change();
	
	solve();
	change();
	
	solve();
	for(int i = 1;i<=m;i++){
		printf("%lld\n",ans[i]);
	}
	return 0;
} 

```

---

