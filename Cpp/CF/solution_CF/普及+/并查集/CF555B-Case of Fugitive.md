# Case of Fugitive

## 题目描述

有$n$个区间，分别为$[l_i,r_i]$，$r_i<l_{i+1}$

有$m$条线段，长度分别为$a_i$，当线段的两个端点分别在两个相邻的区间内是，线段可以连接这两个区间。

询问能否将所有区间联通。

## 说明/提示

$2\le n\le2\times10^5,1\le m\le2\times10^5$

$1\le l_i\le r_i\le10^{18},1\le a_i\le10^{18}$

## 样例 #1

### 输入

```
4 4
1 4
7 8
9 10
12 14
4 5 3 8
```

### 输出

```
Yes
2 3 1 
```

## 样例 #2

### 输入

```
2 2
11 14
17 18
2 9
```

### 输出

```
No
```

## 样例 #3

### 输入

```
2 1
1 1
1000000000000000000 1000000000000000000
999999999999999999
```

### 输出

```
Yes
1 
```

# 题解

## 作者：Plozia (赞：4)

宣传博客 $\to$ [link](https://blog.csdn.net/BWzhuzehao/article/details/119715220)

一道思维题。

首先我们需要转化一下题意。

对于两个相邻的区间 $[l_i,r_i],[l_{i+1},r_{i+1}]$，我们将这两个区间合并一下，得到能够连接这两个区间的线段长度：$[l_{i+1}-r_i,r_{i+1}-l_i]$。

这样，问题就变成了有若干个固定位置的点，用这些点去覆盖区间的问题。

将点按照其坐标进行排序，将这些区间按照左端点升序排序。

然后枚举每个点，对于所有左端点在这个点左边且没有使用过的区间，从中选出一条右端点最小但是大于这个点坐标的区间，用这个点覆盖这个区间。

上述过程可以使用优先队列来维护。

无解情况有哪些呢？

1. 维护的时候出现了最小右端点比这个点坐标还要小。
2. 能用的都用了，发现还有区间没有被覆盖。

这个贪心应该是一个比较常见的套路了，但是思维难度相对较高。

Code：[GitHub CodeBase-of-Plozia CF555B Case of Fugitive.cpp](https://github.com/Plozia/CodeBase-of-Plozia/blob/main/Codeforces%20%E5%88%B7%E9%A2%98%E5%90%88%E9%9B%86/CF555B%20Case%20of%20Fugitive.cpp)

```cpp
/*
========= Plozia =========
	Author:Plozia
	Problem:CF555B Case of Fugitive
	Date:2021/8/14
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::priority_queue;

typedef long long LL;
const int MAXN = 2e5 + 5;
int n, m;
LL l[MAXN], r[MAXN], ans[MAXN];
struct node1
{
	LL l, r, id;
	bool operator <(const node1 &fir)const { return r > fir.r; }
} a[MAXN];
struct node2 { LL d, id; } q[MAXN];
priority_queue <node1> pq;

LL Read()
{
	LL sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum * 10) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
bool cmp1(const node1 &fir, const node1 &sec) { return (fir.l < sec.l); }
bool cmp2(const node2 &fir, const node2 &sec) { return fir.d < sec.d; }

int main()
{
	n = Read(), m = Read();
	for (int i = 1; i <= n; ++i) l[i] = Read(), r[i] = Read();
	for (int i = 1; i <= m; ++i) q[i].d = Read(), q[i].id = i;
	for (int i = 1; i < n; ++i) a[i].l = l[i + 1] - r[i], a[i].r = r[i + 1] - l[i], a[i].id = i;
	std::sort(a + 1, a + n, cmp1); std::sort(q + 1, q + m + 1, cmp2);
	int j = 1;
	for (int i = 1; i <= m; ++i)
	{
		while (j < n && a[j].l <= q[i].d) pq.push(a[j++]);
		if (pq.empty()) continue ;
		if (pq.top().r < q[i].d) { printf("No\n"); return 0; }
		node1 x = pq.top(); pq.pop(); ans[x.id] = q[i].id;
	}
	if (!pq.empty() || j != n) { printf("No\n"); return 0; }
	printf("Yes\n");
	for (int i = 1; i < n; ++i) printf("%lld ", ans[i]); printf("\n"); return 0;
}
```

---

## 作者：jianhe (赞：3)

### 前言：
duel 到的一个大水题，然后疯狂 `CE` 喜提 $-23$。

### 题意：
给定 $n$ 个不相交的区间和 $m$ 条线段，要求用这些线段将所有区间连通。其中，一条线段连接两个相邻区间当且仅当这条线段的两个 **端点** 分别在两个相邻的区间 **内**（包括端点）。

### 思路：
线段只能连接相邻区间，那么必然是相邻区间两两相连形成一整个连通块（废话）。

那么可以枚举每个相邻区间，贪心选取线段，如果不能选就输出 `No`。

如何贪心呢？

将 **相邻区间** 按第一关键字 **总长度**（第二个的右端点减第一个的左端点），第二关键字 **两者之间距离**，从小到大排序，每次二分一个长度 $\ge$ 两者之间距离的线段来取即可。

因为长的线段如果在总长度长的区间不选，在短的线段中一定不优（这条线段的两个 **端点** 要分别在两个相邻的区间内，如果区间总长度太短这条线段就用不了）。

如何实现呢？

我们需要一种能快速二分和快速删除的数据结构，很容易想到 `set`。那么用 `set` 维护每条线段的长度以及下标就可以了。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=2e5+10;
ll n,m,x,ans[N];
struct PP{ll x,i;};
struct cmp{bool operator()(const PP&a,const PP&b){return a.x<b.x;}};
set<PP,cmp> s;
struct P{ll x,y;}p[N];
struct Q{
	ll v,i,up;
	bool operator<(const Q& B){return up==B.up?v<B.v:up<B.up;}
}a[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>p[i].x>>p[i].y;
	for(int i=1;i<=m;i++) cin>>x,s.insert({x,i});
	for(int i=1;i<n;i++) a[i].v=p[i+1].x-p[i].y,a[i].i=i,a[i].up=p[i+1].y-p[i].x;
	sort(a+1,a+n);
	for(int i=1;i<n;i++){
        auto it=s.lower_bound({a[i].v,0});
		if(it==s.end()){cout<<"No";return 0;}
		ll x=it->x;
		if(x>a[i].up){cout<<"No";return 0;}
		ans[a[i].i]=it->i;s.erase(it);
	}
	cout<<"Yes\n";
	for(int i=1;i<n;i++) cout<<ans[i]<<" ";
	return 0;
}
```

---

## 作者：Trimsteanima (赞：1)

**题意**：有n个岛，m座桥，如果桥的长度能够满足能架在岛上，并且不超过岛的长度，那么可以，问所有的岛能不能联通起来。

**思路**：每个岛(l,r)，应该尽量找大于等于l，并且小于等于r，跟r相差最小的，那么可以对岛进行排序，然后维护一个set，用来找离r最近的是哪座桥。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=200010;
int N,M;
struct A
{
    LL l,r;
    int id;
    bool operator<(const A &a)const
    {
        return l<a.l;
    }
}a[maxn];
pair<LL,int> p[maxn];
set<pair<LL,int>> st;
int ans[maxn];
int main()
{
    scanf("%d%d",&N,&M);
    if(M<N-1){printf("No\n");return 0;}
    LL l,r,ll=0,lr=0;
    N--;
    cin>>ll>>lr;
    for(int i=1;i<=N;i++)
    {
        cin>>l>>r;
        a[i].l=l-lr;
        a[i].r=r-ll;
        a[i].id=i;
        ll=l,lr=r;
    }
    for(int i=1;i<=M;i++)
    {
        cin>>l;
        p[i]=make_pair(l,i);
    }
    sort(a+1,a+1+N);
    sort(p+1,p+1+M);
    for(int j=M,i=N;i>0;i--)
    {
        while(j>0&&p[j].first>=a[i].l)
            st.insert(p[j]),j--;
        set<pair<LL,int>>::iterator it=st.upper_bound(make_pair(a[i].r+1,0));
        if(it==st.begin())
        {
            printf("No\n");
            return 0;
        }
        it--;
        ans[a[i].id]=it->second;
        st.erase(it);
    }
    printf("Yes\n");
    for(int i=1;i<=N;i++)
        printf("%d ",ans[i]);
    printf("\n");
    return 0;
}
```

---

## 作者：Tx_Lcy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF555B)
## 思路
也许是一道较水的 $\verb!greedy!$？

不妨把问题转化一下，原题要求我们把线段套到区间里，这个做起来有点麻烦，所以我们不妨算出每两个相邻区间能接受的线段长度范围，把点套到区间里。

接下来很好做了，不妨先把区间按照左端点排个序，点也排个序，每次把所有 $l_j<a_i$ 的数的右端点 $r_i$ 全都丢进一个小根堆里，然后每次取出 $r_i$ 最小的覆盖即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=2e5+10;
int n,m,l[N],r[N],b[N];
struct node{int l,r,id;}a[N];
struct ccc{int x,id;}w[N];
inline bool cmp1(ccc x,ccc y){return x.x<y.x;}
inline bool cmp(node x,node y){return x.l<y.l;}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for (int i=1;i<=n;++i) cin>>l[i]>>r[i];
    for (int i=1;i<n;++i) a[i].l=l[i+1]-r[i],a[i].r=r[i+1]-l[i],a[i].id=i;
    sort(a+1,a+n,cmp);
    for (int i=1;i<=m;++i) cin>>w[i].x,w[i].id=i;
    if (n-1>m) return cout<<"No\n",0;
    sort(w+1,w+m+1,cmp1);
    int l=0;priority_queue<
    pair<int,int>,deque< pair<int,int> >,
    greater< pair<int,int> > >q;
    int solved=0;
    for (int i=1;i<=m;++i){
        while (a[l+1].l<=w[i].x && l+1<n) ++l,q.push({a[l].r,a[l].id});
        if (q.empty()) continue;
        if (q.top().first<w[i].x) return cout<<"No\n",0;
        b[q.top().second]=w[i].id;
        q.pop();++solved;
    }
    if (q.size() || solved!=n-1) return cout<<"No\n",0;
    cout<<"Yes\n";
    for (int i=1;i<n;++i) cout<<b[i]<<' ';cout<<'\n';
    return 0;
}
```


---

## 作者：忘怀星 (赞：0)

按照题意，在岛屿 $i$ 与 $i+1$ 间，需要长度在 $[l_{i+1}-r_i,r_{i+1}-l_i]$ 的桥连接。

我们将一共 $n-1$ 座桥需要的区间拿出来，试着用给我们的桥长度去覆盖这些区间。

问题转化为了给一些区间和一些点，询问一个点最多覆盖一个区间，能否将区间全覆盖。

按照一般的贪心套路，将所有区间按照左端点排序，点也排序。每一次点覆盖我们覆盖右端点最靠左的区间。可以证明这样贪心是对的。使用堆维护即可。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define int long long

using namespace std;

int read()
{
	int a = 0,x = 1;char ch = getchar();
	while(ch > '9' || ch < '0') {if(ch == '-') x = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9') {a = a*10 + ch-'0';ch = getchar();}
	return a*x;
}
const int N=1e6+7;
int n,m,L[N],R[N],ans[N];
struct node{int l,r,id;friend bool operator < (node a,node b) {return a.r > b.r;}}a[N];
bool cmp(node a,node b) {return a.l != b.l ? a.l < b.l : a.r < b.r;};
struct bri{int l,id;friend bool operator <(bri a,bri b) {return a.l < b.l;}}b[N];
priority_queue<node>q;
signed main()
{
	// freopen("random.in","r",stdin);
	// freopen("sol.out","w",stdout);
	n = read(),m = read();
	for(int i = 1;i <= n;i ++) {
		L[i] = read(),R[i] = read();
		if(i>1) a[i-1] = (node){L[i]-R[i-1],R[i]-L[i-1],i-1};
	}
	sort(a+1,a+n,cmp);
	for(int i = 1;i <= m;i ++) b[i].l = read(),b[i].id = i;
	sort(b+1,b+1+m);int j = 1;
	for(int i = 1;i <= m;i ++) {
		while(j < n && a[j].l <= b[i].l) {q.push(a[j]),++j;}
		if(q.size()) {
			if(q.top().r < b[i].l) {puts("No");return 0;}
			else {
				ans[q.top().id] = b[i].id;q.pop();
			}
		}
	}
	if(q.size() || j < n) printf("No");
	else {puts("Yes");for(int i = 1;i < n;i ++) printf("%lld ",ans[i]);}
	return 0;
}
```

---

## 作者：LJC00118 (赞：0)

我们把相邻的两个区间用一个二元组 $ (l, r) $ 来表示

它的涵义是需要一块木板，这块木板的长度在 $ [l, r] $ 范围内

我们把二元组按照 $ r $ 排序，相同按照 $ l $ 排序，每次取 **最大的在 [l, r] 范围内的数**，用一个 set 来维护这个东西即可

```cpp
#include <bits/stdc++.h>
#define Fast_cin ios::sync_with_stdio(false), cin.tie(0);
#define rep(i, a, b) for(register int i = a; i <= b; i++)
#define per(i, a, b) for(register int i = a; i >= b; i--)
#define DEBUG(x) cerr << "DEBUG" << x << " >>> " << endl;
using namespace std;

typedef unsigned long long ull;
typedef pair <int, int> pii;
typedef long long ll;

template <typename _T>
inline void read(_T &f) {
    f = 0; _T fu = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') fu = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
    f *= fu;
}

template <typename T>
void print(T x) {
    if(x < 0) putchar('-'), x = -x;
    if(x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
    print(x); putchar(t);
}

template <typename T>
struct hash_map_t {
    vector <T> v, val, nxt;
    vector <int> head;
    int mod, tot, lastv;
    T lastans;
    bool have_ans;

    hash_map_t (int md = 0) {
        head.clear(); v.clear(); val.clear(); nxt.clear(); tot = 0; mod = md;
        nxt.resize(1); v.resize(1); val.resize(1); head.resize(mod);
        have_ans = 0;
    }

    bool count(int x) {
        int u = x % mod;
        for(register int i = head[u]; i; i = nxt[i]) {
            if(v[i] == x) {
                have_ans = 1;
                lastv = x;
                lastans = val[i];
                return 1;
            }
        }
        return 0;
    }

    void ins(int x, int y) {
        int u = x % mod;
        nxt.push_back(head[u]); head[u] = ++tot;
        v.push_back(x); val.push_back(y);
    }

    int qry(int x) {
        if(have_ans && lastv == x) return lastans;
        count(x);
        return lastans;
    }
};

const int N = 2e5 + 5;

struct ele {
    ll l, r; int id;
    ele (ll L = 0, ll R = 0, int d = 0) : l(L), r(R), id(d) {}
    bool operator < (const ele A) const {
        if(r != A.r) return r < A.r;
        return l < A.l;
    }
} p[N];

set < pair <ll, int> > wxw;
set < pair <ll, int> > :: iterator it;
ll l[N], r[N];
int ans[N];
int n, m;

int main() {
    read(n); read(m);
    for(register int i = 1; i <= n; i++) read(l[i]), read(r[i]);
    for(register int i = 1; i <= m; i++) {
        ll t; read(t);
        wxw.insert(make_pair(t, i));
    }
    for(register int i = 1; i < n; i++) p[i] = ele(l[i + 1] - r[i], r[i + 1] - l[i], i);
    sort(p + 1, p + n);
    for(register int i = 1; i < n; i++) {
        it = wxw.lower_bound(make_pair(p[i].l, 0));
        if(it == wxw.end() || it -> first > p[i].r) {
            cout << "No" << endl;
            return 0;
        }
        ans[p[i].id] = it -> second;
        wxw.erase(it);
    }
    cout << "Yes" << endl;
    for(register int i = 1; i < n; i++) print(ans[i], ' ');
    putchar('\n');
    return 0;
}
```

---

