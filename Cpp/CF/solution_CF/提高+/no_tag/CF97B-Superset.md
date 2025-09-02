# Superset

## 题目描述

A set of points on a plane is called good, if for any two points at least one of the three conditions is true:

- those two points lie on same horizontal line;
- those two points lie on same vertical line;
- the rectangle, with corners in these two points, contains inside or on its borders at least one point of the set, other than these two. We mean here a rectangle with sides parallel to coordinates' axes, the so-called bounding box of the two points.

You are given a set consisting of $ n $ points on a plane. Find any good superset of the given set whose size would not exceed $ 2·10^{5} $ points.

## 样例 #1

### 输入

```
2
1 1
2 2
```

### 输出

```
3
1 1
2 2
1 2
```

# 题解

## 作者：银杉水杉秃杉 (赞：7)

最近学分治，然后找到了这道简单的构造题。

这道题很简单，主要思想：分治（平面上的）

先将每个点按照 $x$ 坐标为第一关键字，$y$ 坐标为第二关键字从小到大进行排序。

然后进行分治。对于一个区间 $[l,r]$，以中间点 $mid$ 的 $x$ 坐标为新增的点的 $x$ 坐标，$[l,r]$ 内每个点的 $y$ 坐标为新增的点的 $y$ 坐标，共构造出 $r-l+1$ 个点。

最后将原来的点和新增的点一起进行排序，去重，输出即可。

看看代码吧：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m;
struct point
{
    int x, y;
    bool operator<(point b)//sort函数要重新定义<符号
    {
        if (x != b.x)
            return x < b.x;
        return y < b.y;
    }
    bool operator==(point b)//unique函数要重新定义==符号
    {
        return x == b.x && y == b.y;
    }
} a[200010];
void solve(int l, int r)
{
    if (l == r)//保证l<r
        return;
    int mid = (l + r) >> 1;
    for (int i = l; i <= r; i++)
        a[++n] = (point){a[mid].x, a[i].y};
    solve(l, mid);//分治
    solve(mid + 1, r);
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &a[i].x, &a[i].y);
    sort(a + 1, a + n + 1);
    solve(1, n);
    sort(a + 1, a + n + 1);//排序
    m = unique(a + 1, a + n + 1) - a - 1;//去重
    printf("%d\n", m);
    for (int i = 1; i <= m; i++)
        printf("%d %d\n", a[i].x, a[i].y);
    return 0;
}
```



---

## 作者：mrclr (赞：3)

刚开始我看成了对于一个点$i$，存在一个点$j$满足三个条件之一，而不是任意的$j$。结果自然$gg$了，第二个点就$WA$了。

也不知怎么来的思路：平面分治。

先把所有点按$x$排序，然后规定一个中间点$a_{mid}$。两边的点向中间点作投影，这样对于任意的在左半部分的点$i$和任意的在右半部分的点$j$，必定满足条件。

然后我们在分治到$[L, mid - 1]$和$[mid + 1, R]$中，解决同侧点的问题。
```c++
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<vector>
#include<stack>
#include<queue>
#include<map>
using namespace std;
#define enter puts("") 
#define space putchar(' ')
#define Mem(a, x) memset(a, x, sizeof(a))
#define rg register
typedef long long ll;
typedef double db;
const int INF = 0x3f3f3f3f;
const db eps = 1e-8;
const int maxn = 2e5 + 5;
inline ll read()
{
  ll ans = 0;
  char ch = getchar(), last = ' ';
  while(!isdigit(ch)) last = ch, ch = getchar();
  while(isdigit(ch)) ans = (ans << 1) + (ans << 3) + ch - '0', ch = getchar();
  if(last == '-') ans = -ans;
  return ans;
}
inline void write(ll x)
{
  if(x < 0) x = -x, putchar('-');
  if(x >= 10) write(x / 10);
  putchar(x % 10 + '0');
}

int n, cnt;
struct Node
{
  int x, y;
  bool operator < (const Node& oth)const
  {
    return x < oth.x || (x == oth.x && y < oth.y);
  }
  bool operator == (const Node& oth)const
  {
    return x == oth.x && y == oth.y;
  }
}a[maxn];

void solve(int L, int R)
{
  if(L > R) return;
  int mid = (L + R) >> 1;
  for(int i = L; i <= R; ++i)
    a[++n] = (Node){a[mid].x, a[i].y};
  solve(L, mid - 1); solve(mid + 1, R);
}

int main()
{
  n = read();
  for(int i = 1; i <= n; ++i) a[i].x = read(), a[i].y = read();
  sort(a + 1, a + n + 1);
  solve(1, n);
  sort(a + 1, a + n + 1);
  int _n = unique(a + 1, a + n + 1) - a - 1;
  write(_n), enter;
  for(int i = 1; i <= _n; ++i) write(a[i].x), space, write(a[i].y), enter;
  return 0;
}
```

---

## 作者：xxseven (赞：2)

注意到允许构造的点数在 $O(n \log n)$ 级别，因此考虑分治构造。

将所有点按 $x$ 排序，找到中位数为分界线，我们希望在分界线上加点，使**分属分界线左右**的点对满足条件。

最简单的方法就是将两边的所有点都投射到分界线上。  
由于一个在分界线一边的点 $(x_i,y_i)$ 与另一边的点形成了矩形，这个矩形必然会经过分界线上纵坐标为 $y_i$ 的点。

这样，我们每次用 $O(n)$ 个点将点集分为了两半，这样有 $T(n)=2T(\frac{n}{2})+O(n)$，可得总点数为 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=10005;
int n,x[N],y[N];
int c[N];
map<pair<int,int>,int> mp;
void solve(int L,int R){
	if(L>=R) return;
	int mid=L+R>>1,p=mid,q=mid;
	while(x[c[q]]==x[c[mid]]&&q<=R) q++;
	while(x[c[p]]==x[c[mid]]&&p>=L) p--;
	for(int i=L;i<=p;++i) mp[{x[c[mid]],y[c[i]]}]=1;
	for(int i=q;i<=R;++i) mp[{x[c[mid]],y[c[i]]}]=1;
	solve(L,p); solve(q,R);
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i) {
		cin>>x[i]>>y[i],c[i]=i;
		mp[{x[i],y[i]}]=1;
	}
	sort(c+1,c+n+1,[&](int a,int b){
		return x[a]<x[b];
	});
	solve(1,n);
	cout<<mp.size()<<'\n';
	for(auto e:mp) cout<<e.first.first<<' '<<e.first.second<<'\n';
	return 0;
}


```

希望这篇题解能够帮到你！

---

## 作者：离散小波变换° (赞：1)

## 题解

平面上一堆点的点对题，首先想到平面分治（什）

我们将所有点按照 $x$ 作为第一关键字进行排序。假设现在需要构造一个方案使得 $[l,r]$ 内所有点加上新加的点构成了一个 Superset。

选取区间中点 $p=\left\lfloor\dfrac{l+r}{2}\right\rfloor$。那么这个区间 $[l,r]$ 就被剖成了两个区间 $[l,p]$ 和 $[p+1,r]$。现在假定对左边的点集构造了一个合法的超集 $P$，对右边的点击构造了一个合法的超集 $Q$。那么对于点对 $(\alpha,\beta)\in P$ 一定合法，对于点对 $(\alpha,\beta)\in Q$ 一定合法，不过还不确定 $\alpha\in P,\beta\in Q$ 是否合法。

一种构造方案是，考虑竖直线 $x=p_x$，我们将 $P$ 和 $Q$ 里面所有的点都向 $x=p_x$ 做垂线，垂足作为新添加的点。不妨将现在 $x=p_x$ 上的点放在集合 $K$ 里。

容易发现，对于任意 $\alpha\in P,\beta \in Q$，如果 $\alpha$ 和 $\beta$ 的 $y$ 值相同则一定合法；否则这个矩形一定跨过 $x=p_x$，由于我们的构造方案，矩形与 $x=p_x$ 的交点都在 $K$ 里面，所以是合法的。

对于 $\alpha\in P$ 和 $\beta\in K$，若水平则直接合法，否则一定有 $(\beta _x,\alpha_y)\in K$ 合法；  
对于 $\alpha\in Q$ 和 $\beta\in K$，若水平则直接合法，否则一定有 $(\beta _x,\alpha_y)\in K$ 合法。

然后对于均来自 $K$ 的点对，由于在同一条竖直线上，所以一定合法。

$P\cup Q\cup K$ 里面不同的 $y$ 坐标个数是和 $P\cup Q$ 相同的，由此可以推知，归并过程中新加入的点的个数不会超过原来的点集 $A$ 在 $[l, r]$ 区间上的点数。所以最终整个点集的大小为 $\mathcal O(n\log n)$，可以通过。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l, r, i) for(int i = l, END##i = r;i <= END##i;++ i)
#define dn(r, l, i) for(int i = r, END##i = l;i >= END##i;-- i)
using namespace std;
typedef long long i64;
const int INF = 2147483647;
int qread(){
    int w = 1, c, ret;
    while((c = getchar()) >  '9' || c <  '0') w = (c == '-' ? -1 : 1); ret = c - '0';
    while((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + c - '0';
    return ret * w;
}
const int MAXN = 1e4 + 3;
const int MAXM = 2e5 + 3;
using pii = pair<int, int>;
map<pii, bool> M;
int n, m; pii P[MAXN], Q[MAXM];
void solve(int l, int r){
    if(l > r) return;
    int t = P[l + r >> 1].first;
    int u = l + r >> 1; while(u > l && P[u - 1].first == t) -- u;
    int v = l + r >> 1; while(v < r && P[v + 1].first == t) ++ v;
    solve(l, u - 1), solve(v + 1, r);
    up(l, r, i) if(i < u || i > v){
        auto p = make_pair(t, P[i].second);
        if(!M.count(p))
            M[p] = true, Q[++ m] = p;
    }
}
int main(){
    n = qread();
    up(1, n, i)
        P[i].first  = qread(),
        P[i].second = qread();
    up(1, n, i) Q[++ m] = P[i], M[P[i]] = true;
    sort(P + 1, P + 1 + n), solve(1, n);
    printf("%d\n", m);
    up(1, m, i)
        printf("%d %d\n", Q[i].first, Q[i].second);
    return 0;
}
```

---

## 作者：优秀的渣渣禹 (赞：1)

因为题告诉我们随意一组解就可以，于是我们想到暴力->把点填满。

but（题中有点数限制）

我们通过二分平面，对于
$mid$
点，每个在
$l-r$
中的其他的点与该点所在直线的投影就是我们需要添加的点

同时为了防止我们添加重复的点我们用
$set$
维护一下。

我们只需要在区间中的点的投影,因为我们知道在大区间内我们已经把所有的点投影到了$mid$，那么我们画图后发现我们对于右边的区间和左边的区间中的点一定满足上面的两种条件，故不需要加点。

```cpp
#define B cout << "BreakPoint" << endl;
#define O(x) cout << #x << " " << x << endl;
#define O_(x) cout << #x << " " << x << " ";
#define Msz(x) cout << "Sizeof " << #x << " " << sizeof(x)/1024/1024 << " MB" << endl;
#include<cstdio>
#include<cmath>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
#include<set>
#define LL long long
#define inf 1000000009
#define N 200005
#define x first  
#define y second  
using namespace std;
inline int read() {
	int s = 0,w = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-')
			w = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		s = s * 10 + ch - '0';
		ch = getchar();
	}
	return s * w;
}
typedef pair<int,int>ii;
ii p[N];
set<ii>s;
void solve(int l,int r){
    if(l >= r) return;
    int mid = (l + r) >> 1;
    for(int i = l;i <= r;i++) s.insert(ii(p[mid].x,p[i].y));
    solve(l,mid);
    solve(mid + 1,r);
    return;
}
int n;
void init(){
	n = read();
	for(int i = 1;i <= n;i++){
		p[i].x = read();
    	p[i].y = read();
    	s.insert(p[i]);
    }
    sort(p + 1,p + n + 1);
    return ;
}
void solv(){
	 solve(1,n);
    printf("%d\n",(int)s.size());
    for(auto i = s.begin();i != s.end();i++){
    	printf("%d %d\n",i->x,i->y);
    }
    return ;
}
int main(){
    init();
	solv();
    return 0;
}
```

---

## 作者：wangyibo201026 (赞：0)

## solution

首先你发现第一眼我并不会做，于是我们打开 CF，看眼标签。

分治！好我会了。

考虑按照 $x$ 坐标排序，然后我们去分治处理，假设目前分治区间 $[l, r]$，中点为 $mid$，那么我们对于每一个在 $[l, r]$ 内的 $i$ 新添加点 $( x_{mid}, y_i)$。

首先矩形应该是边长都 $\ge 1$ 的，也就是说对角两个点的 $x$ 与 $y$ 都不相同的。

不难发现不再两个同一分治区间的点所构成的矩形一定有包含 $1$ 个点以上，因为如果分治区间不一样就会至少经过 $1$ 个分治中点。

然后如果在一个分治区间内的点，由于我们可以添加与初始节点相同的节点，所以我们如果是新点与旧点的矩形肯定会包含一个新点，然后如果是新点与新点的矩形我会包含一个新点或者 $mid$ 点。

## code

code：

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define fir first
#define sec second
#define mkp make_pair 
#define pb push_back
#define lep( i, l, r ) for ( int i = ( l ); i <= ( r ); ++ i )
#define rep( i, r, l ) for ( int i = ( r ); i >= ( l ); -- i )

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair < int, int > pii;

char _c; bool _f; template < class type > inline void read ( type &x ) {
	_f = 0, x = 0;
	while ( _c = getchar (), !isdigit ( _c ) ) if ( _c == '-' ) _f = 1;
	while ( isdigit ( _c ) ) x = x * 10 + _c - '0', _c = getchar (); if ( _f ) { x = -x; }
}

template < class type > inline void chkmin ( type &x, type y ) { x = ( x <= y ? x : y ); }
template < class type > inline void chkmax ( type &x, type y ) { x = ( x >= y ? x : y ); }

const int N = 2e5 + 5;

int n;

struct Node {
  int x, y;
} a[N];

map < pii, bool > mp;

vector < Node > ans;

void cdq ( int l, int r ) {
  if ( l >= r ) {
    return ;
  }
  int mid = l + r >> 1;
  for ( int i = l; i <= r; i ++ ) {
    pii tmp = { a[mid].x, a[i].y };
    if ( !mp[tmp] ) {
      mp[tmp] = 1;
      ans.push_back ( { a[mid].x, a[i].y } );
    }
  }
  cdq ( l, mid - 1 ), cdq ( mid + 1, r );
}

void Solve () {
  cin >> n;
  for ( int i = 1; i <= n; i ++ ) {
    cin >> a[i].x >> a[i].y;
  }
  sort ( a + 1, a + 1 + n, [] ( Node x, Node y ) { return x.x < y.x; } );
  cdq ( 1, n );
  for ( int i = 1; i <= n; i ++ ) {
    if ( !mp[{ a[i].x, a[i].y }] ) {
      mp[{ a[i].x, a[i].y }] = 1;
      ans.push_back ( a[i] );
    }
  }
  cout << ans.size () << '\n';
  for ( Node x : ans ) {
    cout << x.x << " " << x.y << '\n';
  }
}

signed main () {
#ifdef judge
	freopen ( "Code.in", "r", stdin );
	freopen ( "Code.out", "w", stdout );
	freopen ( "Code.err", "w", stderr );
#endif
	Solve ();
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

注意到给出的 $n$ 为 $10^4$ 而给出的构造上限是 $2 \times 10^5$，中间差了一个 $20$ 倍，大概是 $\log n$ 倍，所以考虑带 $\log n$ 的构造。

于是所有点按照 $x$ 排序，对所有点做分治，每次取出中点所在的平行于 $y$ 轴的直线，将分治区间中所有点投射在这条直线上，容易证明这样的构造是符合条件的，因为满足了中点到分治区间中所有点，以及横跨分治中心的所有点对的限制，且一个点最多被投射 $\log_2 10^4$ 次，可以通过。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+114;
int n;
pair<int,int> P[maxn];
set< pair<int,int> > S;
void solve(int l,int r){
	if(l>=r) return ;
	int mid=(l+r)>>1;
	for(int i=l;i<=r;i++){
		S.insert(make_pair(P[mid].first,P[i].second));
	}
	solve(l,mid-1);
	solve(mid+1,r);
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>P[i].first>>P[i].second;
		S.insert(P[i]);
	}
	sort(P+1,P+n+1);
	solve(1,n);
	cout<<S.size()<<'\n';
	for(pair<int,int> now:S) cout<<now.first<<' '<<now.second<<'\n';
	return 0;
}

```

---

## 作者：SJH__qwq (赞：0)

分治简单题。

首先有一个很简单的思路：找到最小的矩阵满足所有点都在矩阵里。但是题目要求 $m\le 2\times 10^5$，所以不行。

然后就考虑对于一个平面上分治。有一个很简单的套路就是把所有平面上的点按照 $x$ 坐标排序，然后只考虑 $y$ 坐标对答案的贡献。

然后考虑分治。假设现在分到了 $[l,r]$ 这一段点的区间，且满足 $l<r$。则令 $p=\lfloor\frac{l+r}{2}\rfloor$，以 $p$ 点为横坐标，$i\in [l,r]\cap\textbf{N}_+$ 的点作为纵坐标构造 $r-l+1$ 个点即可满足条件。证明很显然。

时间复杂度为 $O(n\log n)$。很好写。

---

