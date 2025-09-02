# [COCI 2023/2024 #2] Zatopljenje

## 题目描述

Mr. Malnar 有一张地形图，上面画着一个区域内每个位置的海拔高度。具体的，有 $n$ 个位置排成一排，第 $i$ 个位置高出海平面 $h_i$ 米。

海平面可能会上升。给定 $q$ 次询问，对于第 $i$ 次询问你需回答：如果海平面高度上升 $x_i$ 米，那么 $[l_i,r_i]$ 区间中会形成多少个岛？一个岛的定义为一个极长的，每个位置的高度都大于 $x_i$ 的段。

![](https://cdn.luogu.com.cn/upload/image_hosting/mffg52xn.png)

上图分别表示了样例 1 的第一组询问以及样例 2 的第二组询问。左图 $[2,5]$ 区间中有 $[2,2],[4,5]$ 两个岛，而右图中有 $[1,1],[4,4],[8,8],[10,10]$ 四个岛。

## 说明/提示

### 数据范围
|$\text{Subtask}$|分值|特殊性质|
|:-:|:-:|:-:|
|$1$|$10$|$n,q\le 2000$|
|$2$|$20$|$l_i=1,r_i=n$|
|$3$|$20$|存在 $p\in [1,n]$ 满足 $h_1\ge h_2\ge \cdots \ge h_p\le h_{p+1}\le \cdots \le h_n$|
|$4$|$60$|无|

对于所有数据，$1\le n,q\le 2\times 10^5$，$0\le h_i,x_i\le 10^9$，$1\le l_i\le r_i\le n$。

## 样例 #1

### 输入

```
6 3
2 4 2 3 4 1
2 5 2
3 5 3
3 4 4```

### 输出

```
2
1
0```

## 样例 #2

### 输入

```
10 3
5 0 3 4 2 0 1 6 3 5
3 9 1
1 10 3
1 10 2```

### 输出

```
2
4
3```

# 题解

## 作者：JimmyLee (赞：14)

# 解法

## 一组询问

先考虑一个简化版的情况，如果只有一组询问怎么处理。

~~那不直接打暴力~~

可以考虑一个常见的技巧：每个位置赋一个颜色 $c_i$，满足：
$$
c_i=\begin{cases}
1 & h_i>x\\
0 & h_i\leq x
\end{cases}
$$
这样我们就把原来的序列变成了一个 01 串。

问题就变成了 01 串上给定区间 $[l, r]$ 中连续的 $1$ 的区间的个数。

## 多组询问

有个显然的结论：如果 $x_i$ 单调下降，则生成的 01 串中只会有 $0$ 变成 $1$。 

在这种情况下问题就变成了单点修改，区间查询连续的 $1$ 的区间的个数。

直接线段树。解决。

---

所以做法就是先将询问离线，按 $x_i$ 从大到小排序。

每次先加入当前高度下新加入的节点， 然后查询 $[l_i, r_i]$ 间的连续的 $1$ 的区间的个数。

每次新加入的节点可以用桶预先统计好。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 200005

struct SegT
{
    struct node
    {
        int l=0, r=0, ans=0;
        node operator+(node b) {return {l, b.r, ans+b.ans-(r&&r==b.l)};}
        void operator=(int b) {l=r=ans=b;}
    }tr[maxn<<2];

    #define lc   (x<<1)
    #define rc   (x<<1|1)
    #define mid  ((l+r)>>1)
    #define lson lc, l, mid
    #define rson rc, mid+1, r
    #define rt   1, 1, n

    void push_up(int x) {tr[x]=tr[lc]+tr[rc];}

    void modify(int x, int l, int r, int p)
    {
        if(l==r) return tr[x]=1;
        if(p<=mid) modify(lson, p);
        if(p>mid)  modify(rson, p);
        push_up(x);
    }

    node query(int x, int l, int r, int L, int R)
    {
        if(L<=l&&r<=R) return tr[x];
        if(R<=mid) return query(lson, L, R);
        if(L>mid)  return query(rson, L, R);
        return query(lson, L, R)+query(rson, L, R);
    }
}tr; // 线段树部分

vector<tuple<int, int, int, int>> qrs; // 储存离线询问
vector<int> adds[maxn] /*存储每次新加入的节点*/, hgt;
int lis[maxn], ans[maxn];

int main()
{
    int n, q;
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>lis[i];
    for(int i=1, l, r, x;i<=q;i++)
        cin>>l>>r>>x, 
        qrs.emplace_back(x, l, r, i), 
        hgt.emplace_back(x);
    sort(qrs.begin(), qrs.end(), greater());
    sort(hgt.begin(), hgt.end(), greater());
    for(int i=1;i<=n;i++) 
        adds[upper_bound(hgt.begin(), hgt.end(), lis[i], greater())-hgt.begin()+1].emplace_back(i); // 向桶内添加节点
    int cnt=1;
    for(auto [h, l, r, i]:qrs)
    {
        for(auto v:adds[cnt++]) tr.modify(rt, v); 
        ans[i]=tr.query(rt, l, r).ans; // 先改再查
    }
    for(int i=1;i<=q;i++) cout<<ans[i]<<'\n';
}
```

---

## 作者：rsy_ (赞：11)

写一个和目前所有题解方法不太一样的做法。

这个题，我相信还是有人和我一样，想到直接暴力建小根笛卡尔树。

所以这篇题解将是给我这种只想到笛卡尔树的~~脑残选手~~人准备的。

**注意，如果想要学习正解，请跳过这一篇。**

首先对于原数组暴力建笛卡尔树，如果从上往下 bfs，发现其实就是类似于不断地拆点的一个操作，并不好维护。

所以考虑从下往上“加点”的操作，这样的话只需要对于询问离线下来，然后如果他的父节点选择了，就把这个节点的影响删掉就可以了。

于是我们现在需要支持的操作就是区间覆盖，查询一个区间内所覆盖的区间个数，不完整的区间也算覆盖。

然后用一个线段树维护一下就可以了。

于是就有了以下代码，这并不好写，我调了一年，有非常逆天边界

```cpp
#include <bits/stdc++.h>
#define lb(x) (x&-x)
#define L(i,j,k) for(int i=(j);i<=(k);++i)
#define R(i,j,k) for(int i=(j);i>=(k);--i)
#define swap(a,b) (a^=b^=a^=b)

using namespace std;
using i64 = long long;

typedef pair<int, int> pii;
typedef long long ll;
typedef unsigned long long ull;
void chmin(int &x, int c) {
  x = min(x, c);
}
void chmax(ll &x, ll c) {
  x = max(x, c);
}

namespace fast_IO{
#define IOSIZE 100000
int precision=3,POW[10]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};char ibuf[IOSIZE],obuf[IOSIZE],*p1=ibuf,*p2=ibuf,*p3=obuf;
#ifdef ONLINE_JUDGE
#define getchar()((p1==p2)and(p2=(p1=ibuf)+fread(ibuf,1,IOSIZE,stdin),p1==p2)?(EOF):(*p1++))
#define putchar(x)((p3==obuf+IOSIZE)&&(fwrite(obuf,p3-obuf,1,stdout),p3=obuf),*p3++=x)
#define isdigit(ch)(ch>47&&ch<58)
#define isspace(ch)(ch<33)
#endif
template<typename T>inline T read(){T s=0;int w=1;char ch;while(ch=getchar(),!isdigit(ch)&&(ch!=EOF))if(ch==45)w=-1;if(ch==EOF)return 0;while(isdigit(ch))s=s*10+ch-48,ch=getchar();return s*w;}template<typename T>inline bool read(T&s){s=0;int w=1;char ch;while(ch=getchar(),!isdigit(ch)&&(ch!=EOF))if(ch==45)w=-1;if(ch==EOF)return 0;while(isdigit(ch))s=s*10+ch-48,ch=getchar();return s*=w,1;}inline bool read(char&s){while(s=getchar(),isspace(s));return 1;}inline bool read(char*s){char ch;while(ch=getchar(),isspace(ch));if(ch==EOF)return 0;while(!isspace(ch))*s++=ch,ch=getchar();*s='\000';return 1;}template<typename T>inline void print(T x){if(x<0)putchar(45),x=-x;if(x>9)print(x/10);putchar(x%10+48);}inline void print(char x){putchar(x);}inline void print(char*x){while(*x)putchar(*x++);}inline void print(const char*x){for(int i=0;x[i];i++)putchar(x[i]);}inline bool read(std::string&s){s="";char ch;while(ch=getchar(),isspace(ch));if(ch==EOF)return 0;while(!isspace(ch))s+=ch,ch=getchar();return 1;}inline void print(std::string x){for(int i=0,n=x.size();i<n;i++)putchar(x[i]);}inline bool read(bool&b){char ch;while(ch=getchar(),isspace(ch));b=ch^48;return 1;}inline void print(bool b){putchar(b+48);}inline bool read(double&x){int a=0,b=0;char ch=getchar();bool f=0;while(ch<48||ch>57){if(ch==45)f=1;ch=getchar();}while(47<ch&&ch<58){a=(a<<1)+(a<<3)+(ch^48);ch=getchar();}if(ch!=46){x=f?-a:a;return 1;}ch=getchar();while(47<ch&&ch<58){b=(b<<1)+(b<<3)+(ch^48),ch=getchar();}x=b;while(x>1)x/=10;x=f?-a-x:a+x;return 1;}inline void print(double x){if(x<0){putchar(45),x=-x;}x=round((long double)x*POW[precision])/POW[precision],print((long long)x),putchar(46),x-=(long long)(x);for(int i=1;i<=precision;i++)x*=10,putchar(x+48),x-=(int)x;}template<typename T,typename...T1>inline int read(T&a,T1&...other){return read(a)+read(other...);}template<typename T,typename...T1>inline void print(T a,T1...other){print(a),print(other...);}struct Fast_IO{~Fast_IO(){fwrite(obuf,p3-obuf,1,stdout);}}io;template<typename T>Fast_IO&operator>>(Fast_IO&io,T&b){return read(b),io;}template<typename T>Fast_IO&operator<<(Fast_IO&io,T b){return print(b),io;}
#define cout io
#define cin io
#define endl '\n'
}using namespace fast_IO;
const int maxn = 4e5 + 10, mod = 1e9 + 7;
int N, Q, A[maxn], B[maxn], lg2[maxn];
int mn[maxn][20];
int mnl[maxn << 2], mnr[maxn << 2];
void init() {
	for (int i = 1; i <= N; i ++ ) {
		mn[i][0] = i;
	}
	for (int j = 1; j <= 19; j ++ )
		for (int i = 1; i + (1 << j) - 1 <= N; i ++ ) 
			if (A[mn[i][j - 1]] <= A[mn[i + (1 << (j - 1))][j - 1]])
				mn[i][j] = mn[i][j - 1];
			else
				mn[i][j] = mn[i + (1 << (j - 1))][j - 1];
}
int query (int l, int r) {
	int k = lg2[r - l + 1];
	if (A[mn[l][k]] <= A[mn[r - (1 << k) + 1][k]])
		return mn[l][k];
	return mn[r - (1 << k) + 1][k];
}
int lpos[maxn], rpos[maxn], fa[maxn];
int res[maxn], c[maxn], st[maxn];
struct qwq {
	int l, r, x, id;
} a[maxn];
struct node {
	int x, id;
} b[maxn];
vector<int> g[maxn];
void build (int u, int l, int r) {
	lpos[u] = l, rpos[u] = r;
	st[u] = 1;
	if (l >= r) {
		lpos[u] = rpos[u] = u; return;
	}
	int mid1 = query (l, u - 1);
	int mid2 = query (u + 1, r);
	if (mid1 != 0 && !st[mid1]) {
		g[u].push_back(mid1), fa[mid1] = u;
		build (mid1, l, u - 1);
	}
	if (mid2 != 0 && !st[mid2]) {
		g[u].push_back(mid2), fa[mid2] = u;
		build (mid2, u + 1, r);
	}
}
int sum[maxn << 2];
void upd (int u, int l, int r, int x, int w) {
	if (l == r) {
		sum[u] = w;
		if (w >= 1) mnl[u] = mnr[u] = l;
		else mnl[u] = mnr[u] = 0x3f3f3f3f; 
		return;
	}
	int mid = (l + r) >> 1;
	if (x <= mid) upd (u << 1, l, mid, x, w);
	else upd (u << 1 | 1, mid + 1, r, x, w);
	sum[u] = sum[u << 1] + sum[u << 1 | 1];
	if (mnl[u << 1] != 0x3f3f3f3f) {
		mnl[u] = mnl[u << 1];
	} else {
		mnl[u] = mnl[u << 1 | 1];
	}
	if (mnr[u << 1 | 1] != 0x3f3f3f3f) {
		mnr[u] = mnr[u << 1 | 1];
	} else {
		mnr[u] = mnr[u << 1];
	}
}
int query (int u, int l, int r, int ql, int qr) {
	if (ql <= l && qr >= r) {
		return sum[u];
	}
	int S = 0, mid = (l + r) >> 1;
	if (ql <= mid) S = query (u << 1, l, mid, ql, qr);
	if (qr > mid) S += query (u << 1 | 1, mid + 1, r, ql, qr);
	return S;
}
int qy_l (int u, int l, int r, int ql, int qr) {
	if (ql <= l && qr >= r) {
		return mnl[u];
	}
	int mid = (l + r) >> 1;
	if (ql <= mid) {
		int s = qy_l(u << 1, l, mid, ql, qr);
		if (s != 0x3f3f3f3f) return s;
	}
	return qy_l(u << 1 | 1, mid + 1, r, ql, qr); 
}
int qy_r (int u, int l, int r, int ql, int qr) {
	if (ql <= l && qr >= r) {
		return mnr[u];
	}
	int mid = (l + r) >> 1;
	if (qr > mid) {
		int s = qy_r(u << 1 | 1, mid + 1, r, ql, qr);
		if (s != 0x3f3f3f3f) return s;
	}
	return qy_r(u << 1, l, mid, ql, qr);
}
int tg[maxn];

void solve() {
	memset (mnl, 0x3f, sizeof mnl);
	memset (mnr, 0x3f, sizeof mnr);
	cin >> N >> Q;
	for (int i = 2; i <= N; i ++ ) {
		lg2[i] = lg2[i >> 1] + 1;
	}
	for (int i = 1; i <= N; i ++ ) {
		cin >> A[i];
		b[i].x = A[i], b[i].id = i;
	}
	init();
	build (query(1, N), 1, N);
	for (int i = 1; i <= Q; i ++ ) {
		cin >> a[i].l >> a[i].r >> a[i].x;
		a[i].id = i;
	}
	sort (a + 1, a + 1 + Q, [](qwq i, qwq j){
		return i.x > j.x;
	});
	sort (b + 1, b + 1 + N, [](node i, node j){
		return i.x == j.x ? i.id < j.id : i.x < j.x;
	});
	for (int i = 1; i <= N; i ++ ) c[i] = b[i].x;
//	for (int i = 1; i <= Q; i ++ ) {
//		cout << a[i].l << ' ' << a[i].r << ' ' << a[i].x << '\n';
//	}
//	for (int i = 1; i <= N; i ++ ) {
//		cout << c[i] << " \n"[i == N];
//	}
//	for (int i = 1; i <= N; i ++ ){
//		cout << i << ":\n";
//		for (int x : g[i]) {
//			cout << x << ' ';
//		}
//		cout << '\n';
//	} 
	int now = N;
//	for (int i = 1; i <= N; i ++ ) {
//		cout << i << '\n';
//		for (int x : g[i]) {
//			cout << x << ' ';
//		}
//		cout << '\n';
//	} 
//	for (int i = 1; i <= N; i ++ ) {
//		cout << lpos[i] << ' ' << rpos[i] << '\n';
//	}
	for (int i = 1; i <= Q; i ++ ) {
		int id = upper_bound(c + 1, c + 1 + N, a[i].x) - c;
		bool f = 0;
//		cout << id << ' ' << now << '\n';
		if (c[id] > a[i].x) {
			for (int j = now; j >= id; j -- ) {
				for (int v : g[b[j].id]) {
					upd (1, 1, N, lpos[v], 0);
					upd (1, 1, N, rpos[v], 0);
//					cout << "del:" << v << ' ' << lpos[v] << '\n';
					tg[lpos[v]] = tg[rpos[v]] = 0;
				}	
				if (lpos[b[j].id] != rpos[b[j].id]) {
					upd (1, 1, N, lpos[b[j].id], 1);
					upd (1, 1, N, rpos[b[j].id], 1);
					tg[lpos[b[j].id]] = 1;
//					cout << "rpos:" << b[j].id << ' ' << lpos[b[j].id] << ' ' << rpos[b[j].id] << '\n';
					tg[rpos[b[j].id]] = 2;
				} else {
					upd (1, 1, N, lpos[b[j].id], 2);
					tg[lpos[b[j].id]] = 3;
				}
//				cout << "ins:" << b[j].id << ' ' << lpos[b[j].id] << '\n';
				f = 1;
//		for (int j = 1; j <= N; j ++ ) {
//			cout << query (1, 1, N, j, j) << " \n"[j == N]; 
//		}
			}
			if (f) now = id - 1;
		} 
//		for (int j = 1; j <= N; j ++ ) {
//			cout << query (1, 1, N, j, j) << " \n"[j == N]; 
//		}
		int s = query (1, 1, N, a[i].l, a[i].r);
//		cout << s << '\n';
		if (s != 0) {
			int s1 = qy_l(1, 1, N, a[i].l, a[i].r);
			int s2 = qy_r(1, 1, N, a[i].l, a[i].r);
//			cout << s1 << ' ' << s2 << '\n';
//			cout << tg[s1] << ' ' << tg[s2] << '\n';
			if (s1 != 0x3f3f3f3f && tg[s1] == 2) s ++ ;
			if (s2 != 0x3f3f3f3f && tg[s2] == 1) s ++ ; 
		} else {
			if (a[i].l != 1 && a[i].r != N) {
				if (query (1, 1, N, 1, a[i].l - 1) > 0 && query (1, 1, N, a[i].r + 1, N) > 0) {
					int s1 = qy_r(1, 1, N, 1, a[i].l - 1);
					int s2 = qy_l(1, 1, N, a[i].r + 1, N);
//					cout << s1 << ' ' << s2 << '\n';
					if (s1 != 0x3f3f3f3f && tg[s1] == 1) s ++ ;
					if (s2 != 0x3f3f3f3f && tg[s2] == 2) s ++ ;
				}
			}
		}
//		cout << s << '\n';
		res[a[i].id] = s / 2;
	}
	for (int i = 1; i <= Q; i ++ ) {
		cout << res[i] << '\n';
	}
}

signed main() {
//	freopen ("data.in", "r", stdin);
//	freopen ("shaber.out", "w", stdout);
  int T = 1;
  while (T--)solve();
  return 0;
}
/*
5
1
5 4 2 3 1
4 4 1

2
*/
```

---

## 作者：liaoxingrui (赞：9)

## Content

有 $n$ 个位置排成一排，第 $i$ 个位置海拔 $h_i$ 米。有 $q$ 次询问，每次询问有三个数，$l_i$，$r_i$，$x_i$，表示在 $l_i$ 到 $r_i$ 的区间里有几个小岛（连在一起且每个位置高度都大于海平面 $x_i$）。

## Solution

这道题可用线段树做。

因为 $x_i$ 未经过排序，所以我们将它从高到低排序会更简单一点，就相当于海平面逐步下降，这样就可以保证之前高于海平面的位置现在依旧高于海平面，不用在搜一遍，只需保存原来搜索到的位置继续搜索。

因为 $h_i$ 也未经过排序，我们也可将它从高到低排序，如果这个位置低于海平面，我们可以马上退出（后面的位置海拔一定小于这个位置的海拔），不用再往下搜。

将 $x_i$ 和 $h_i$ 从高到低排序过后，就可以节省一些时间，这时我们再用线段树推出在 $l_i$ 到 $r_i$ 的区间内有多少个小岛。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,tot=1;
int ans[200005],tree[200005<<2],treel[200005<<2],treer[200005<<2];
bool bj[200005];
struct gd{
	int id,gao;
}h[200005];
struct xw{
	int id,l,r,x;
}a[200005];
inline bool cmp1(gd xx,gd yy){
	return xx.gao>yy.gao;
}
inline bool cmp2(xw xx,xw yy){
	return xx.x>yy.x;
}
inline void build(int node,int l,int r){
	treel[node]=l;
	treer[node]=r;
	if(l==r)
		return;
	int mid=l+((r-l)>>1);
	build(node<<1,l,mid);
	build(node<<1|1,mid+1,r);
//建树主要是记录左右儿子的位置，为下面的程序铺垫。 
}
inline void update(int node,int t){
	if(treel[node]==treer[node]){
		tree[node]=1;
		return;
	}
	int mid=treel[node]+((treer[node]-treel[node])>>1);
	if(t<=mid)
		update(node<<1,t);
	else
		update(node<<1|1,t);
	tree[node]=tree[node<<1]+tree[node<<1|1]-(bj[treer[node<<1]]&&bj[treel[node<<1|1]]);
//可能会左儿子的最右边与右儿子的最左边的海拔重复。 
}
inline int getsum(int node,int x,int y){
	if(x<=treel[node]&&treer[node]<=y)
		return tree[node];
	int mid=treel[node]+((treer[node]-treel[node])>>1),sum=0;
	if(x<=mid)
		sum+=getsum(node<<1,x,y);
	if(y>mid)
		sum+=getsum(node<<1|1,x,y);
	return sum-(bj[treer[node<<1]]&&bj[treel[node<<1|1]]&&x<=mid&&y>mid);
//同上，但是只有可能在 x<=mid 与 y>mid 的情况下。 
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>h[i].gao;
		h[i].id=i;
	}
	for(int i=1;i<=m;i++){
		cin>>a[i].l>>a[i].r>>a[i].x;
		a[i].id=i;
	}
	sort(h+1,h+n+1,cmp1);
//按海拔的高度从高到低排序。
	sort(a+1,a+m+1,cmp2);
//按海平面高度从高到低排序。
	build(1,1,n);
	for(int i=1;i<=m;i++){
		while(h[tot].gao>a[i].x&&tot<=n){
//因为按海拔的高度从高到低进行了排序，所以如果 h[tot].gao<=a[i].x 那么 h[tot+1].gao 一定小于等于 a[i].x。
			bj[h[tot].id]=true;
//记录哪些位置的海拔超过了海平面。 
			update(1,h[tot].id); 
			tot++;
		}
		ans[a[i].id]=getsum(1,a[i].l,a[i].r);
	}
	for(int i=1;i<=m;i++)
		cout<<ans[i]<<endl;
	return 0;
}
```

---

## 作者：BunDragon126 (赞：5)

**20240722更新：将无序列表中代码块的缩紧进行修改，请管理员重申，如果有其他问题麻烦一次性详细指出，谢谢你们?**

# Problem

[点击直达题目](https://www.luogu.com.cn/problem/P9912)

# Solution

## Step1. 分析

如果你对**区间修改与维护**有了解，那么你一定知道这个题目需要用**线段树**来维护。

## Step2. 思路 & 步骤

1.	定义和初始化：
    - 定义一些全局变量和结构体来存储数据和线段树节点信息。
    - 三个结构体：
     - 第一个结构体中定义一个 $a$ 数组用于存储线段树节点，每个节点包含区间的左边界 $l$、右边界 $r$、岛的长度  $len$、左端点类别 $lc$ 和右端点类别 $rc$。
       - 第二个结构体中定义一个 $b$ 数组用于存储询问，每个询问包含左边界 $l$、右边界 $r$、海平面上升高度 $x$ 和询问的 $ID$。
        - 第三个结构体定义一个 $c$ 数组用于存储每个位置的高度及其 $id$。

    ```C++
    int n, q, l, r, mid, x, sum, ma, ans[N], o, cnt, cnt1;
    map<int, int> m;
    
    // 结构体node用于存储线段树的节点信息
    struct node {
        int l, r, len, lc, rc;  // l和r表示区间左右边界, len表示区间内岛屿的数量, lc和rc表示区间左右端点的类别
    } a[N];
    
    // 结构体deno用于存储高度信息
    struct deno {
        int x, id;  // x表示高度, id表示高度对应的位置索引
    } c[N];
    
    // 结构体w用于存储查询信息
    struct w {
        int l, r, x, id;  // l和r表示查询区间, x表示海平面上升高度, id表示查询的索引
    } b[N];
    ```

2.	构建线段树：
    - `build` 函数用于构建线段树，将每个叶子节点初始化为长度为 $1$ 的岛屿。

    ```C++
    void build(int p, int l, int r) {
        a[p].l = l;
        a[p].r = r;
        if (l == r) {  // 叶子节点
            a[p].len = a[p].lc = a[p].rc = 1;  // 初始化为长度为1的岛屿
            return;
        }
        int mid = (l + r) / 2;
        build(p * 2, l, mid);  // 递归构建左子树
        build(p * 2 + 1, mid + 1, r);  // 递归构建右子树
        gx(p);  // 更新当前节点信息
    }
    ```

3. 更新操作：
    - `change` 函数用于更新区间内的节点，将对应的高度位置更新为新的类别。

    ```C++
    void change(int p, int l, int r) {
        if (l <= a[p].l && a[p].r <= r) {  // 完全覆盖
            a[p].len = 0;  // 将区间内的长度设置为0
            a[p].lc = a[p].rc = ++cnt1;  // 更新类别
            return;
        }
        int mid = (a[p].l + a[p].r) / 2;
        if (l <= mid) change(p * 2, l, r);  // 递归更新左子树
        if (mid < r) change(p * 2 + 1, l, r);  // 递归更新右子树
        gx(p);  // 更新当前节点信息
    }
    ```

4. 查询操作：
    - `ask` 函数用于查询指定区间内的岛屿数量。

    ```C++
    int ask(int p, int l, int r) {
        if (l <= a[p].l && a[p].r <= r)  // 完全覆盖
            return a[p].len;
        int mid = (a[p].l + a[p].r) / 2;
        int ans1 = 0;
        if (l <= mid && mid < r) {  // 跨区间查询
            ans1 = ask(p * 2, l, r) + ask(p * 2 + 1, l, r);  // 查询左右子树
            if (a[p * 2].rc == a[p * 2 + 1].lc)  // 如果左右子树的连接处高度相同，岛屿数量减少1
                ans1--;
        } else if (l <= mid) {  // 查询左子区间
            ans1 = ask(p * 2, l, r);
        } else if (mid < r) {  // 查询右子区间
            ans1 = ask(p * 2 + 1, l, r);
        }
        return ans1;
    }
    ```

5. 排序和处理：

    - 将高度数组和查询数组分别按高度和海平面上升高度进行排序。

   ```C++
   // 比较函数，用于排序查询
   bool cmp(w x, w y) {
       return x.x < y.x;
   }
   
   // 比较函数，用于排序高度
   bool cmp1(deno x, deno y) {
       return x.x < y.x;
   }
   sort(c + 1, c + 1 + n, cmp1);  // 按高度排序
   sort(b + 1, b + 1 + q, cmp);  // 按海平面上升高度排序
   ```

    - 遍历每个查询，根据当前海平面上升高度更新线段树，然后进行查询并存储结果。

   ```C++
   while (cnt <= n && c[cnt].x <= b[i].x) {
       change(1, c[cnt].id, c[cnt].id);  // 更新线段树
       cnt++;
   }
   ```

6. 输出结果：
    - 遍历每个查询的结果，按照原始顺序输出。

    ```C++
    for (int i = 1; i <= q; i++) {
        cout << ans[i] << endl;  // 输出结果
    }
    ```

## 时间复杂度计算

这段代码的时间复杂度主要由以下几个部分构成：

1. **构建线段树的时间复杂度**：
   - `build` 函数在初始化时对所有节点进行递归构建，其时间复杂度为 $\mathcal{O}(n)$。

2. **更新线段树的时间复杂度**：
   - `change` 函数在处理每次更新时需要递归更新相关节点，其时间复杂度为 $\mathcal{O}(\log n)$。

3. **查询线段树的时间复杂度**：
   - `ask` 函数在处理每次查询时需要递归查询相关节点，其时间复杂度为 $\Theta(\log n)$。

4. **排序的时间复杂度**：
   - `sort` 函数用于对高度数组和查询数组进行排序，其时间复杂度为 $\Theta(n \log n)$ 和 $\Theta(q \log q)$。

5. **主循环的时间复杂度**：
   - 主循环遍历每个查询，并在处理查询前对高度进行更新。由于每个高度更新和查询操作的复杂度为 $\Theta(\log n)$，并且每个高度只更新一次，因此这部分的总时间复杂度为 $\Theta((n + q) \log n)$。

综合来看，整个算法的时间复杂度为：
$$
\Theta((n + q) \log n)
$$
~~（所以是不会炸的）~~

# Code

```C++
#include <bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;

const int N = 10001005;

int n, q, l, r, mid, x, sum, ma, ans[N], o, cnt, cnt1;
map<int, int> m;

// 结构体node用于存储线段树的节点信息
struct node {
    int l, r, len, lc, rc;  // l和r表示区间左右边界, len表示区间内岛屿的数量, lc和rc表示区间左右端点的类别
} a[N];

// 结构体deno用于存储高度信息
struct deno {
    int x, id;  // x表示高度, id表示高度对应的位置索引
} c[N];

// 结构体w用于存储查询信息
struct w {
    int l, r, x, id;  // l和r表示查询区间, x表示海平面上升高度, id表示查询的索引
} b[N];

// 更新节点信息函数
void gx(int p) {
    a[p].len = a[p * 2].len + a[p * 2 + 1].len;  // 合并左右子区间的岛屿数量
    if (a[p * 2].rc == a[p * 2 + 1].lc)  // 如果左右子区间的连接处高度相同，岛屿数量减少1
        a[p].len--;
    a[p].lc = a[p * 2].lc;  // 更新左端点类别
    a[p].rc = a[p * 2 + 1].rc;  // 更新右端点类别
}

// 构建线段树函数
void build(int p, int l, int r) {
    a[p].l = l;
    a[p].r = r;
    if (l == r) {  // 叶子节点
        a[p].len = a[p].lc = a[p].rc = 1;  // 初始化为长度为1的岛屿
        return;
    }
    int mid = (l + r) / 2;
    build(p * 2, l, mid);  // 递归构建左子树
    build(p * 2 + 1, mid + 1, r);  // 递归构建右子树
    gx(p);  // 更新当前节点信息
}

// 更新线段树函数
void change(int p, int l, int r) {
    if (l <= a[p].l && a[p].r <= r) {  // 完全覆盖
        a[p].len = 0;  // 将区间内的长度设置为0
        a[p].lc = a[p].rc = ++cnt1;  // 更新类别
        return;
    }
    int mid = (a[p].l + a[p].r) / 2;
    if (l <= mid) change(p * 2, l, r);  // 递归更新左子树
    if (mid < r) change(p * 2 + 1, l, r);  // 递归更新右子树
    gx(p);  // 更新当前节点信息
}

// 查询线段树函数
int ask(int p, int l, int r) {
    if (l <= a[p].l && a[p].r <= r)  // 完全覆盖
        return a[p].len;
    int mid = (a[p].l + a[p].r) / 2;
    int ans1 = 0;
    if (l <= mid && mid < r) {  // 跨区间查询
        ans1 = ask(p * 2, l, r) + ask(p * 2 + 1, l, r);  // 查询左右子树
        if (a[p * 2].rc == a[p * 2 + 1].lc)  // 如果左右子树的连接处高度相同，岛屿数量减少1
            ans1--;
    } else if (l <= mid) {  // 查询左子区间
        ans1 = ask(p * 2, l, r);
    } else if (mid < r) {  // 查询右子区间
        ans1 = ask(p * 2 + 1, l, r);
    }
    return ans1;
}

// 比较函数，用于排序查询
bool cmp(w x, w y) {
    return x.x < y.x;
}

// 比较函数，用于排序高度
bool cmp1(deno x, deno y) {
    return x.x < y.x;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> q;
    cnt1 = n + 1;
    for (int i = 1; i <= n; i++) {
        cin >> c[i].x;
        c[i].id = i;
    }
    sort(c + 1, c + 1 + n, cmp1);  // 按高度排序
    for (int i = 1; i <= q; i++) {
        cin >> b[i].l >> b[i].r >> b[i].x;
        b[i].id = i;
    }
    sort(b + 1, b + 1 + q, cmp);  // 按海平面上升高度排序
    cnt = 1;
    build(1, 1, n);  // 构建线段树
    for (int i = 1; i <= q; i++) {
        while (cnt <= n && c[cnt].x <= b[i].x) {
            change(1, c[cnt].id, c[cnt].id);  // 更新线段树
            cnt++;
        }
        ans[b[i].id] = ask(1, b[i].l, b[i].r);  // 查询岛屿数量
    }
    for (int i = 1; i <= q; i++) {
        cout << ans[i] << endl;  // 输出结果
    }
    return 0;
}
```

---

## 作者：XuYueming (赞：4)

## UPDATE on 2024.4.25

改掉奇怪压行码风，并稍作排版。

## 题目分析

首先发现区间中的个数等于 $\texttt{高度大于 x 的位置的个数} - \texttt{连续两个位置都是大于 x 的位置的个数}$。具体令 $H_i = \min(h_i, h_{i+1}) (i \in [1, n-1])$，那么对于一次询问答案 $ans=\sum\limits_{i=l}^{r}[h_i > x] - \sum\limits_{i=l}^{r-1}[H_i > x]$，其中 $[a > b]$ 表示当 $a > b$ 时为 $1$，反之为 $0$。特别地，对于 $l=r$ 的情况，答案就是 $[h_i > x]$。

> 证明：一个岛屿一定是由一段连续的高度大于 $x$ 的位置组成，那么这一段连续两个位置都是大于 $x$ 的位置的个数正好是这一段区间的长度减一（可以想象这一段区间有多少个间隔，显然是区间长度减一），那么两者相减就是 $1$ ，求和之后就算出了 $1$ 的个数，也就是岛屿的个数。证毕。

很明显，原问题成了两个数组中区间内大于某个数的个数，具体来讲，就是 $h_l \sim h_r$ 大于 $x$ 的个数减去 $H_l \sim H_{r-1}$ 大于 $x$ 的个数。使用分块是个做法，但是由于 ~~不能过这道题~~ 我们要学习更优的 $\log$ 的算法，有以下两种解法。

### 离线使用线段树

考虑对原问题离线，将 $[l, r]$ 的询问拆成 $[1, r]$ 的询问减去 $[1, l-1]$ 的询问，这样从左到右扫一遍，同时维护一个数据结构能快速求得目前比 $x$ 大的个数。离散化使用树状数组是一种方法，或者直接使用权值线段树。

时间复杂度为 $\Theta((n+q)\log n)$ ~~以及一个线段树不小的常数？~~ 。

### 直接使用主席树

其实可以考虑使用可持久化的数据结构（主席树），这样可以在线解决，万一题目强制在线，那么离线的全都挂掉了。剩下的就是板子了。具体地，我们讲所有高度离散化，主席树里面存值域区间出现的数字个数。对于询问，我们在离散化之前所有高度中找到最后一个小于等于 $x$ 的高度（由于离散化要先排序，这一步可以用 `upper_bound` 二分，对时间复杂度没有影响），令这个高度为 $h_0$，那么就查询 $l \sim r$ 中大于 $h_0$ 的个数即可。

时间复杂度：$\Theta((n+q)\log n)$。

## 代码

### 离线使用线段树

```cpp
#include <cstdio>
#include <vector>
using namespace std;

int n, q, h[200010], H[200010], ans[200010];

struct node{
	int f, idx, x;
};
vector<node> qry1[200010], qry2[200010];

const int inf = 1000000000;

struct Segment_Tree{
	struct node{
		int lson, rson, sum;
	} tree[1000010 << 2];
	int tot, root;
	void pushup(int idx){
		tree[idx].sum = tree[tree[idx].lson].sum + tree[tree[idx].rson].sum;
	}
	int query(int &idx, int trl, int trr, int l, int r){
		if (!idx || trl > r || trr < l) return 0;
		if (l <= trl && trr <= r) return tree[idx].sum;
		int mid = (trl + trr) >> 1;
		return query(tree[idx].lson, trl, mid, l, r) + query(tree[idx].rson, mid + 1, trr, l, r);
	}
	void modify(int &idx, int trl, int trr, int p, int v){
		if (trl > p || trr < p) return;
		if (!idx) idx = ++tot, tree[idx] = {0, 0, 0};
		if (trl == trr) return tree[idx].sum += v, void();
		int mid = (trl + trr) >> 1;
		modify(tree[idx].lson, trl, mid, p, v), modify(tree[idx].rson, mid + 1, trr, p, v), pushup(idx);
	}
	void clear(){ tot = 0, root = 0; }
} yzh;

signed main(){
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; ++i) scanf("%d", &h[i]), H[i-1] = min(h[i-1], h[i]);
	for (int i = 1, l, r, x; i <= q; ++i){
		scanf("%d%d%d", &l, &r, &x);
		if (l == r) ans[i] = h[l] > x;
		else {
			qry1[r].push_back({1, i, x}), qry1[l - 1].push_back({-1, i, x});
			qry2[l - 1].push_back({1, i, x}), qry2[r - 1].push_back({-1, i, x});
		}
	}
	for (int i = 1; i <= n; ++i){
		yzh.modify(yzh.root, 0, inf, h[i], 1);
		for (const auto & [f, idx, x]: qry1[i])
			ans[idx] += f * yzh.query(yzh.root, 0, inf, x + 1, inf);
	}
	yzh.clear();
	for (int i = 1; i <= n - 1; ++i){
		yzh.modify(yzh.root, 0, inf, H[i], 1);
		for (const auto & [f, idx, x]: qry2[i])
			ans[idx] += f * yzh.query(yzh.root, 0, inf, x + 1, inf);
	}
	for (int i = 1; i <= q; ++i) printf("%d\n", ans[i]);
	return 0;
}
```

### 直接使用主席树

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int n, q, h[200010], real[200010], V;

struct Yzh_Is_The_President{
	struct node{
		int lson, rson;
		int val;
	} tree[200010 * 24];
	int root[200010], tot;
	void pushup(int idx){
		tree[idx].val = tree[tree[idx].lson].val + tree[tree[idx].rson].val;
	}
	void build(int &idx, int l, int r){
		tree[idx = ++tot] = {0, 0, 0};
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(tree[idx].lson, l, mid), build(tree[idx].rson, mid + 1, r);
	}
	void modify(int &idx, int oidx, int trl, int trr, int p, int v){
		if (trl > p || trr < p) return;
		tree[idx = ++tot] = tree[oidx];
		if (trl == trr) return tree[idx].val += v, void();
		int mid = (trl + trr) >> 1;
		modify(tree[idx].lson, tree[oidx].lson, trl, mid, p, v);
		modify(tree[idx].rson, tree[oidx].rson, mid + 1, trr, p, v);
		pushup(idx);
	}
	int query(int lidx, int ridx, int trl, int trr, int l, int r){
		if (trl > r || trr < l) return 0;
		if (l <= trl && trr <= r) return tree[ridx].val - tree[lidx].val;
		int mid = (trl + trr) >> 1;
		return query(tree[lidx].lson, tree[ridx].lson, trl, mid, l, r) + 
			   query(tree[lidx].rson, tree[ridx].rson, mid + 1, trr, l, r);
	}
} xym, yzh;

signed main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i) scanf("%d", &h[i]), real[i] = h[i];
    sort(real + 1, real + n + 1);
    V = unique(real + 1, real + n + 1) - real - 1;
    for (int i = 1; i <= n; ++i) h[i] = lower_bound(real + 1, real + V + 1, h[i]) - real;
    
    xym.build(xym.root[0], 1, V), yzh.build(yzh.root[0], 1, V);
    for (int i = 1; i <= n; ++i) xym.modify(xym.root[i], xym.root[i - 1], 1, V, h[i], 1);
    for (int i = 1; i <= n - 1; ++i) yzh.modify(yzh.root[i], yzh.root[i - 1], 1, V, min(h[i], h[i + 1]), 1);
    
    for (int i = 1; i <= q; ++i) {
        int l, r, x;
        scanf("%d%d%d", &l, &r, &x);
        if (l == r)
            printf("%d\n", real[h[l]] > x);
        else if (x < real[1])
			puts("1");
		else {
        	int v = upper_bound(real + 1, real + V + 1, x) - real - 1;
        	printf("%d\n", xym.query(xym.root[l - 1], xym.root[r], 1, V, v + 1, V
						 - yzh.query(yzh.root[l - 1], yzh.root[r - 1], 1, V, v + 1, V));
		}
    }
    return 0;
}
```

---

## 作者：_determination_ (赞：3)

更新内容：删除了错误的做法。

题面：多组询问，每组询问给出区间左右端点以及阈值 $x$，求区间内大于 $x$ 的数组成的连续段的个数。

显然离散化高度并离线，将询问按阈值从大到小排序（类似退潮？）

然后我们用线段树维护即可，节点内维护左边是不是陆地，右边是不是陆地，一共有几块岛屿，合并还是比较显然的。

---

## 作者：Getaway_Car (赞：3)

### 闲话

考前集训，每日一练做到的题，~我写挂了五次~。自己想到**分块**的做法，看题解区没有，于是来发一篇。

### 思路

我们注意到，当海水高度为 $x$ 时，区间 $[l, r]$ 的小岛的个数可以这么计算：

$$
[h_l \gt x] + \sum_{i = l}^{r - 1}[h_i \le x \lt h_{i + 1}]
$$

所以第 $i$ 个位置产生贡献**当且仅当** $h_i \le x \lt h_{i + 1}$ ，考虑分块并预处理出每个块的答案。由于 $0 \le h_i, x_i \le 10^9$ ，所以要**离散化**。时间复杂度 $O((n + q)(\sqrt{n} + \log{n}))$ ，虽然比不上线段树或树状数组，但是思路还是比较好想的。

具体细节见代码实现。

**Tip : 不要开``long long``，不然会MLE。**

### Code

```cpp
#include <bits/stdc++.h>
#define PII pair<int, int>
using namespace std;
template <typename _Tp>
inline void read(_Tp &x) {
	int neg = 1;
	char ch;
	while(ch = getchar(), !isdigit(ch)) if(ch == '-') neg = -1;
	x = ch - '0';
	while(ch = getchar(), isdigit(ch)) x = (x << 3) + (x << 1) + (ch ^ '0');
	x *= neg;
	return;
}
// bans[i][j] : 第 i 个块当 x = j 时的答案
int n, q, a[200005], blk, cnt, bans[505][200005], x, l, r;
PII p[200005];
signed main() {
	read(n), read(q);
	for(int i = 1; i <= n; ++i) read(a[i]);
	// 加一个 0 ，方便离散化
	a[0] = 0, ++n;
	// 离散化
	for(int i = 0; i < n; ++i) p[i] = {a[i], i};
	sort(p, p + n);
	for(int i = 0; i < n; ++i) {
		if(i == 0) a[p[i].second] = 1;
		else {
			if(p[i].first == p[i - 1].first) a[p[i].second] = a[p[i - 1].second];
			else a[p[i].second] = a[p[i - 1].second] + 1;
		}
	}
	// 分块
	blk = sqrt(n);
	cnt = (n - 1) / blk + 1;
	for(int i = 0; i < n - 1; ++i) if(a[i] < a[i + 1]) {
			// 差分计算答案
			++bans[i / blk][a[i]];
			--bans[i / blk][a[i + 1]];
		}
	// 前缀和
	for(int i = 0; i < cnt; ++i) for(int j = 1; j <= n; ++j) bans[i][j] += bans[i][j - 1];
	while(q--) {
		read(l), read(r), read(x);
		// 对 x 离散化，找到最后一个小于等于 x 的值
		int ind = lower_bound(p, p + n, (PII){x + 1, 0}) - p, ans;
		x = a[p[ind - 1].second];
		// l 点的答案
		ans = a[l] > x;
		if(l / blk == r / blk) {
			// 在同一个块中
			for(int i = l; i < r; ++i) ans += (a[i] <= x && a[i + 1] > x);
		}
		else {
			// 计算 l 所在块的答案
			for(int i = l; i < (l / blk + 1) * blk; ++i) ans += (a[i] <= x && a[i + 1] > x);
			// 计算 r 所在块的答案
			for(int i = r / blk * blk; i < r; ++i) ans += (a[i] <= x && a[i + 1] > x);
			// 计算中间块的答案
			for(int i = l / blk + 1; i < r / blk; ++i)ans += bans[i][x];
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

[Submisson](https://www.luogu.com.cn/record/183250736)

---

**完结撒花！！！✿✿ヽ(°▽°)ノ✿**

---

## 作者：Unordered_OIer (赞：3)

# Description

给定每个横坐标的海拔 $h_1 \sim h_n$，每次询问 $[l,r,x]$ 表示在 $[l,r]$ 内形成的岛屿有多少个（即 $h_j>x$ 的所有 $j \in [l,r]$ 构成了多少个连续段）。

# Solution

好像见过一个很像的题，忘了是哪道了，就当练一练线段树。

考虑一个“退潮”的过程，显然当 $x_1 < x_2$ 时，露出来的地方越来越多，所以离线下来按 $x$ 从大到小排序。

我们把 $>x$ 的地方设为 $1$，那么询问就是统计 $[l,r]$ 内的 $1$ 连续段个数。

考虑线段树，节点直接存储连续段个数。把 $h$ 从大到小排序下来单点更新，不需要 lazytag，合并的时候判一下两个区间中间是不是同一个连通块。

```cpp
void pushup(ll x){
  t[x].c=t[x<<1].c+t[x<<1|1].c-(a[t[x<<1].r]==1&&a[t[x<<1|1].l]==1);
}
void build(ll x,ll l,ll r,ll d){
  t[x]=(node){l,r,0};
  if(l==r){
    return;
  }
  ll mid=l+r>>1;
  build(x<<1,l,mid,d);
  build(x<<1|1,mid+1,r,d);
  pushup(x);
}
void up(ll x,ll i){
  if(t[x].l==t[x].r){
    t[x].c=1;
    return;
  }
  ll mid=t[x].l+t[x].r>>1;
  if(i<=mid)up(x<<1,i);
  else up(x<<1|1,i);
  pushup(x);
}
ll query(ll x,ll l,ll r){
  if(l<=t[x].l&&t[x].r<=r)return t[x].c;
  ll res=0;
  ll mid=t[x].l+t[x].r>>1;
  bool lq=0,rq=0;
  if(l<=mid)lq=1,res+=query(x<<1,l,r);
  if(r>mid){
    rq=1,res+=query(x<<1|1,l,r);
  }
  if(lq&&rq)if(a[t[x<<1].r]==1&&a[t[x<<1|1].l]==1){
      res--;
    }
  return res;
}
pair<ll,ll> pp[N];
ll ans[N];
int main(){
  n=read(),m=read();for(ll i=1;i<=n;i++)h[i]=read(),pp[i]=make_pair(h[i],i);
  for(ll i=1;i<=m;i++)q[q[i].id=i].l=read(),q[i].r=read(),q[i].x=read();
  sort(q+1,q+m+1,cmp);sort(pp+1,pp+n+1,greater<pair<ll,ll>>());
  ll pos=1;build(1,1,n,0);
  for(ll i=1;i<=m;i++){
    while(pp[pos].first>q[i].x&&pos<=n){
      a[pp[pos].second]=1;
      up(1,pp[pos].second);
      ++pos;
    }
    ans[q[i].id]=query(1,q[i].l,q[i].r);
  }
  for(ll i=1;i<=m;i++)cout<<ans[i]<<'\n';
  return 0;
}
```

---

## 作者：苏联小渣 (赞：2)

相当于只保留 $>x$ 的数，区间询问连续段个数。

有一类问题，就是只保留一个前后缀（中位数、$k$ 大值等只于临界状态大小有关）的问题，可以按照大小关系分类转化成 $01$ 序列。

考虑把询问按照 $x$ 从大到小排序，对于每组询问 $x$，我们加入所有满足 $a_i>x$ 的 $a_i$，在这个位置标记为 $1$，问题转化成了单点修改，区间数连续 $1$ 的个数。用线段树直接维护即可。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
#define lc(x) x<<1
#define rc(x) x<<1|1
int n, q, ans[200010];
struct node{
	int x, id;
	bool operator < (const node &A) const{
		return x > A.x;
	}
}a[200010];
struct Query{
	int l, r, x, id;
	bool operator < (const Query &A) const{
		return x > A.x;
	} 
}b[200010];
struct segment{
	int l, r, s;
}d[800010];
segment operator + (segment x, segment y){
	return (segment){x.l, y.r, x.s + y.s - (x.r == y.l && x.r == 1)};
}
void modify(int k, int l, int r, int x){
	if (l == r){
		d[k] = (segment){1, 1, 1};
		return ;
	}
	int mid = l + r >> 1;
	if (x <= mid) modify(lc(k), l, mid, x);
	else modify(rc(k), mid+1, r, x);
	d[k] = d[lc(k)] + d[rc(k)];
}
segment query(int k, int l, int r, int x, int y){
	if (x <= l && r <= y) return d[k];
	int mid = l + r >> 1;
	if (y <= mid) return query(lc(k), l, mid, x, y);
	if (x > mid) return query(rc(k), mid+1, r, x, y);
	return query(lc(k), l, mid, x, y) + query(rc(k), mid+1, r, x, y); 
}
int main(){
	scanf ("%d%d", &n, &q);
	for (int i=1; i<=n; i++){
		scanf ("%d", &a[i].x);
		a[i].id = i;
	}
	for (int i=1; i<=n*4; i++) d[i] = (segment){0, 0, 0};
	sort (a+1, a+n+1);
	for (int i=1; i<=q; i++){
		scanf ("%d%d%d", &b[i].l, &b[i].r, &b[i].x);
		b[i].id = i;
	}
	sort (b+1, b+q+1);
	for (int i=1, j=0; i<=q; i++){
		while (j < n && a[j+1].x > b[i].x){
			j ++;
			modify(1, 1, n, a[j].id);
		}
		ans[b[i].id] = query(1, 1, n, b[i].l, b[i].r).s;
	}
	for (int i=1; i<=q; i++){
		printf ("%d\n", ans[i]);
	}
	return 0;
}
```

---

## 作者：_AyachiNene (赞：1)

# 思路：
看到这个题容易想到转离线，因为海水高度和答案是有单调性的，在一个高度能成为岛的地方，显然在海水高度更低的时候肯定也能成为岛。那么把询问离线下来后，在用双指针跑一下，把能成为岛的地方记为一，问题就变成了，问一段区间中有多少段连续一。用线段树维护就行了。
# Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int res=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){res=(res<<1)+(res<<3)+(c^48);c=getchar();}
	return res*f;
}
void write(int x)
{
	if(x<0){putchar('-');x=-x;}
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
//----SegmentTreeBegin----
struct Elaina
{
	int l,r,val,lcol,rcol;
}t[114514<<3];
#define mid (t[root].l+t[root].r>>1)
#define ls (root<<1)
#define rs (root<<1|1)
void init(Elaina &x)
{
	x.val=x.lcol=x.rcol=-1;
}
Elaina merge(Elaina x,Elaina y)
{
	if(x.val==-1) return y;
	if(y.val==-1) return x;
	Elaina res;
	init(res);
	res.val=x.val+y.val-(x.rcol==y.lcol&&x.rcol==1);
	res.lcol=x.lcol,res.rcol=y.rcol;
	return res;
}
void update(int root)
{
	int l=t[root].l,r=t[root].r;
	t[root]=merge(t[ls],t[rs]);
	t[root].l=l,t[root].r=r;
}
void bld(int l,int r,int root)
{
	t[root].l=l;
	t[root].r=r;
	if(l==r) return;
	bld(l,mid,ls);
	bld(mid+1,r,rs);
}
void insert(int x,int root)
{
	if(t[root].l==t[root].r)
	{
		t[root].val=t[root].lcol=t[root].rcol=1;
		return;
	}
	if(x<=mid) insert(x,ls);
	else insert(x,rs);
	update(root);
}
Elaina query(int x,int y,int root)
{
	if(t[root].l>=x&&t[root].r<=y)
		return t[root];
	Elaina res;
	init(res);
	if(x<=mid) res=merge(res,query(x,y,ls));
	if(y>mid) res=merge(res,query(x,y,rs));
	return res;
}
//-----SegmentTreeEnd-----
struct node
{
	int h,pos;
}a[114514<<1];
bool cmp1(node x,node y)
{
	return x.h>y.h;
}
struct que
{
	int h,l,r,id;
}q[114514<<1];
bool cmp2(que x,que y)
{
	return x.h>y.h;
}
int n,m;
int ans[114514<<1];
int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		a[i].h=read(),a[i].pos=i;
	for(int i=1;i<=m;i++)
		q[i].l=read(),q[i].r=read(),q[i].h=read(),q[i].id=i;
	sort(a+1,a+n+1,cmp1);
	sort(q+1,q+m+1,cmp2);
	bld(1,n,1);
	int cur=1;
	for(int i=1;i<=m;i++)
	{
		while(q[i].h<a[cur].h&&cur<=n)
		{
			insert(a[cur].pos,1);
			++cur;
		}
		ans[q[i].id]=query(q[i].l,q[i].r,1).val;
	}
	for(int i=1;i<=m;i++)
		write(ans[i]),puts("");
	return 0;
}
```

---

## 作者：wvwit (赞：0)

# 题意
$n$ 个位置，每个位置高为 $h_i$，$q$ 个询问，每个询问求当海平面为 $x$，在 $[l,r]$ 区间有多少**小岛**。

小岛定义：连成一块的高于海平面的位置，如当海平面为 $5$，$h_i$ 到 $h_i+3$ 都为 $6$，则从 $i$ 到 $i+3$ 为一个小岛，且仅能视作一个小岛。
# 分析
## 询问
拿到多次询问的题目，先考虑能不能进行离线，离线能不能优化。很明显，这道题进行离线能带来优化。

原本在线做法，海平面的位置忽高忽低，相当于每次都要**重新处理**，但离线下来我们能通过排序**保证海平面单调递增或递减**。

这能带来什么，每个点只会加入（单调递减）或删除（单调递增）一次，这就能带来很大的时间复杂度优化。

那单调递减还是单调递增呢，这需要结合其他因素考虑，先放着。

## 区间
它不是全局查询，而是区间查询，这就带来一些问题。

在之前提到的离线中，答案同样可以继承，但是现在不行，因为可能两次询问提到的是两个区间。

那这个问题怎么解决呢，解决区间问题一个很好的方法是数据结构，这里我选择线段树，每次出现一个点或失去一个点，就通过 $change$ 函数改变对应位置的 $01$ 值，然后区间求和。

## 小岛
小岛并不难解决，我看大佬的题解里采用的是在线段树的操作中顺便解决了。

但我是蒟蒻，考试的时候只想到用并查集进行操作。

又因为是并查集，不方便进行分裂操作，于是我选择单调递减，这样就是加入与合并的操作。

具体为四个函数，一个新建，一个合并，一个左延伸，一个右延伸。

**注意**：为了判断旁边的节点是否属于一个块，我在最开始并未对并查集数组 $k$ 进行赋值，在新建时才将其祖先赋为自己，这样可以直接通过它判断。

## 代码
细节请看代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,q,l[N],r[N],ans[N];
int now,k[N],L[N],R[N];
struct noot
{
	int num,id;
}h[N],Q[N];
struct tree
{
	int l,r,sum;
}t[N<<2];
void son(int i) {t[i].sum=(t[i<<1].sum+t[(i<<1)|1].sum);}
void sth(int i,int l,int r)
{
	t[i].l=l;t[i].r=r;
	if(l==r)
	{
		t[i].sum=0;
		return;
	}
	int mid=(l+r)/2;
	sth(i<<1,l,mid);
	sth((i<<1)|1,mid+1,r);
	son(i);
}
void cg(int i,int x,int k)
{
	if(t[i].l==t[i].r)
	{
		t[i].sum+=k;
		return;
	}
	int mid=(t[i].l+t[i].r)/2;
	if(x<=mid) cg(i<<1,x,k);
	else cg((i<<1)|1,x,k);
	son(i);
}
int cgg(int i,int l,int r)
{
	if(t[i].l==l&&t[i].r==r) return t[i].sum;
	int mid=(t[i].l+t[i].r)/2;
	if(r<=mid) return cgg(i<<1,l,r);
	else if(l>mid) return cgg((i<<1)|1,l,r);
	else return cgg(i<<1,l,mid)+cgg((i<<1)|1,mid+1,r);
}
//以上为线段树
bool cmp(noot x,noot y)
{
	if(x.num==y.num) return x.id>y.id;
	return x.num>y.num;
}
//以下为并查集 
int find(int x)
{
	if(k[x]==x) return x;
	else k[x]=find(k[x]);
	return k[x];
}
//新建 
void add(int now)
{
	k[h[now].id]=h[now].id;
	L[h[now].id]=h[now].id;
	R[h[now].id]=h[now].id;
	cg(1,h[now].id,1);
}
//合并 
void merge(int now)
{
	k[h[now].id-1]=find(k[h[now].id-1]);
	k[h[now].id+1]=find(k[h[now].id+1]);
	int LL=k[h[now].id-1],RR=k[h[now].id+1];
	//启发式了一手，不知道有没有优化效果 
	if(R[k[h[now].id-1]]-L[k[h[now].id-1]]>=R[k[h[now].id+1]]-L[k[h[now].id+1]])
		k[k[h[now].id+1]]=k[h[now].id]=k[h[now].id-1];
	else k[k[h[now].id-1]]=k[h[now].id]=k[h[now].id+1];
	L[k[h[now].id]]=L[LL];
	R[k[h[now].id]]=R[RR];
	if(LL==k[h[now].id]) cg(1,RR,-1);
	else cg(1,LL,-1);
}
// 左边的块右延伸 
void get_l(int now)
{
	k[h[now].id-1]=find(h[now].id-1);
	k[h[now].id]=k[h[now].id-1];
	R[k[h[now].id]]++;
}
//右边的块左延伸 
void get_r(int now)
{
	k[h[now].id+1]=find(h[now].id+1);
	k[h[now].id]=k[h[now].id+1];
	L[k[h[now].id]]--;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>q;
	sth(1,1,n);
	for(int i=1;i<=n;i++)
		cin>>h[i].num,h[i].id=i;
	for(int i=1;i<=q;i++)
	{
		cin>>l[i]>>r[i]>>Q[i].num;
		Q[i].id=i;
	}
	sort(h+1,h+n+1,cmp);
	sort(Q+1,Q+q+1,cmp);
	now=1;
	for(int i=1;i<=q;i++)
	{
		while(h[now].num>Q[i].num)
		{
			if(k[h[now].id-1]&&k[h[now].id+1]) merge(now);
			else if(k[h[now].id-1]) get_l(now);
			else if(k[h[now].id+1]) get_r(now);
			else add(now);
			now++;
		}
		ans[Q[i].id]=cgg(1,l[Q[i].id],r[Q[i].id]);
		//我只给线段树中祖先的位置进行赋值
		//导致如果块在边上，祖先有概率在范围外
		//特判一下补回来 
		if(k[l[Q[i].id]])
		{
			k[l[Q[i].id]]=find(l[Q[i].id]);
			if(k[l[Q[i].id]]<l[Q[i].id]) ans[Q[i].id]++;
		}
		if(k[r[Q[i].id]])
		{
			k[r[Q[i].id]]=find(r[Q[i].id]);
			if(k[r[Q[i].id]]>r[Q[i].id]) ans[Q[i].id]++;
		}
	}
	for(int i=1;i<=q;i++)
		cout<<ans[i]<<endl;
	return 0;
}
```

---

## 作者：kkxacj (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9912)

#### 思路

先假设海平面高度永远为一个固定的数 $x$，该怎么解决这道题。

将小于等于 $x$ 的赋为 $0$，其余的赋为 $1$，那么求 $l$ 到 $r$ 有几块岛也就是求有几段连续的 $1$，不难想到用线段树维护，每次算就加上左边一段岛的个数和右边一段岛的个数，中间如果能连起来成为一个岛就将答案减一。

那如果 $x$ 不固定呢？

可以考虑把岛和询问按 $x$ 排序，每次将所有高度比 $x$ 小的颜色赋为 $0$，不难发现最多只用修改 $n$ 个数，然后计算一下就可以了。

#### 注意：将一个数赋为 $0$ 时得将颜色赋为一个与众不同的颜色，避免因判断到两个颜色都为 $0$ 而使答案变小。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,l,r,mid,x,sum,ma,ans[200010],o,cnt,cnt1;
map<int,int>m;
struct w2
{
	int l,r,len,lc,rc;
}a[1000010];
struct w1
{
	int x,id;
}c[200010];
struct w
{
	int l,r,x,id;
}b[200010];
void gx(int p)
{
	a[p].len = a[p * 2].len + a[p * 2 + 1].len;
	if(a[p * 2].rc == a[p * 2 + 1].lc) a[p].len--;
	a[p].lc = a[p * 2].lc,a[p].rc = a[p * 2 + 1].rc;
}
void build(int p,int l,int r)
{
	a[p].l = l; a[p].r = r;
	if(l == r) 
	{
		a[p].len = a[p].lc = a[p].rc = 1;
		return;
	}
	int mid = (l + r) / 2;
	build(p * 2,l,mid); build(p * 2 + 1,mid + 1,r);
	gx(p);
}
void change(int p,int l,int r)
{
	if(l <= a[p].l && a[p].r <= r)
	{
		a[p].len = 0;
		a[p].lc = a[p].rc = ++cnt1;
		return;
	}
	int mid = (a[p].l + a[p].r) / 2;
	if(l <= mid) change(p * 2,l,r);
	if(mid < r) change(p * 2 + 1,l,r);
	gx(p);
}
int ask(int p,int l,int r)
{
	if(l <= a[p].l && a[p].r <= r) return a[p].len;
	int mid = (a[p].l + a[p].r) / 2;
	int ans1 = 0;
	if(l <= mid && mid < r) 
	{
		ans1 = ask(p * 2,l,r) + ask(p * 2 + 1,l,r);
		if(a[p * 2].rc == a[p * 2 + 1].lc) ans1--;
	}
	else if(l <= mid) ans1 = ask(p * 2,l,r);
	else if(mid < r) ans1 = ask(p * 2 + 1,l,r);
	return ans1;
}
bool cmp(w x,w y){return x.x < y.x;}
bool cmp1(w1 x,w1 y){return x.x < y.x;}
int main()
{
	scanf("%d%d",&n,&q); cnt1 = n + 1;
	for(int i = 1;i <= n;i++) scanf("%d",&c[i].x),c[i].id = i;
	sort(c + 1,c + 1 + n,cmp1);
	for(int i = 1;i <= q;i++) scanf("%d%d%d",&b[i].l,&b[i].r,&b[i].x),b[i].id = i;
	sort(b + 1,b + 1 + q,cmp);
	cnt = 1; build(1,1,n);
	for(int i = 1;i <= q;i++)
	{
		while(cnt <= n && c[cnt].x <= b[i].x) change(1,c[cnt].id,c[cnt].id),cnt++;
		ans[b[i].id] = ask(1,b[i].l,b[i].r);
	}
	for(int i = 1;i <= q;i++) printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：zhangjiting (赞：0)

## 思路

先转换一下题目，对于每一次询问，如果 $a_i > x$，就把 $b_i$ 赋值为 $1$。求出 $b$ 在 $l\sim r$ 区间内有几段连续的 $1$。

这个问题用线段树可以解决，但是有多组询问，每次都重新建一遍线段树太慢了，考虑优化。

此题不强制在线，可以想到离线做法：对于 $a$ 按高度排序，从大到小，对于询问按 $x$ 从大到小排序。每次询问令 $a_i>x$ 的原坐标为 $x$，令 $b_x=1$。

为什么可以这样做？由于询问按 $x$ 从大到小排序，所以，修改过的 $b_i$ 一定不会再改变。而我们把 $a$ 按高度排序，就可以搞一根指针，保证不会超时。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,m,ans[N];
struct node1{
	int h,id;
}a[N];
struct node2{
	int l,r,x,id;
}que[N];
bool cmp1(node1 a,node1 b){
	return a.h>b.h;
}
bool cmp2(node2 a,node2 b){
	return a.x>b.x;
}
struct LEAF{
	int l,r,v;
}tree[N<<2];
LEAF operator + (LEAF a,LEAF b){
	return LEAF{a.l,b.r,a.v+b.v-(a.r==b.l&&a.r==1)};
}
void build(int p,int l,int r){
	if(l==r){
		tree[p]=LEAF{0,0,0};
		return;
	}
	int mid=(l+r)>>1;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	tree[p]=tree[p*2]+tree[p*2+1];
}
void change(int p,int l,int r,int x){
	if(l==r){
		tree[p]=LEAF{1,1,1};
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid) change(p*2,l,mid,x);
	if(x>mid) change(p*2+1,mid+1,r,x);
	tree[p]=tree[p*2]+tree[p*2+1];
}
LEAF ask(int p,int l,int r,int x,int y){
	if(x<=l&&r<=y) return tree[p];
	int mid=(l+r)>>1;
	if(y<=mid) return ask(p*2,l,mid,x,y);
	if(x>mid) return ask(p*2+1,mid+1,r,x,y);
	return ask(p*2,l,mid,x,y)+ask(p*2+1,mid+1,r,x,y);
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i].h;
		a[i].id=i;
	}
	sort(a+1,a+n+1,cmp1);
	for(int i=1;i<=m;i++){
		cin>>que[i].l>>que[i].r>>que[i].x;
		que[i].id=i;
	}
	sort(que+1,que+m+1,cmp2);
	for(int i=1,j=0;i<=m;i++){
		while(a[j+1].h>que[i].x&&j<n) change(1,1,n,a[++j].id);
		ans[que[i].id]=ask(1,1,n,que[i].l,que[i].r).v;
	}
	for(int i=1;i<=m;i++) cout<<ans[i]<<endl;
	return 0;
}

```

---

## 作者：Oracynx (赞：0)

## P9912 [COCI 2023/2024 #2] Zatopljenje 题解

### 思路分析

我考虑将题目的询问离线下来。按高度降序排序，模拟一个退潮的过程。

同时将岛的高度降序排序，使用 $cnt$ 记录当前的淹没的最高的山，每次不断更新。

使用线段树维护区间信息，我们只需要单点修改和区间查询，所以不需要懒标记。

区间类的定义如下：

```cpp
class node
{
  public:
    int size;
    int lc, rc;
    node()
    {
        lc = 0;
        rc = 0;
        size = 0;
    }
};
```

岛类的定义如下：

```cpp
class island
{
  public:
    int h;
    int id;
    island()
    {
        h = 0;
        id = 0;
    }
};
```

询问类的定义如下：

```cpp
class question
{
  public:
    int h;
    int id;
    int res;
    int l, r;
    question()
    {
        h = 0;
        l = 0;
        r = 0;
        id = 0;
        res = 0;
    }
};
```

合并区间的代码如下：

```cpp
node merge(node l, node r)
{
    node res;
    res.lc = l.lc;
    res.rc = r.rc;
    if (l.rc == 1 && r.lc == 1)
    {
        res.size = l.size + r.size - 1;
    }
    else
    {
        res.size = l.size + r.size;
    }
    return res;
}
```

### 代码如下

```cpp
#include <algorithm>
#include <cstdio>
constexpr int MaxN = 2e5 + 5;
class node
{
  public:
    int size;
    int lc, rc;
    node()
    {
        lc = 0;
        rc = 0;
        size = 0;
    }
};
class island
{
  public:
    int h;
    int id;
    island()
    {
        h = 0;
        id = 0;
    }
};
class question
{
  public:
    int h;
    int id;
    int res;
    int l, r;
    question()
    {
        h = 0;
        l = 0;
        r = 0;
        id = 0;
        res = 0;
    }
};
int n, q;
island p[MaxN];
question answer[MaxN];
node tree[MaxN * 4];
node merge(node l, node r)
{
    node res;
    res.lc = l.lc;
    res.rc = r.rc;
    if (l.rc == 1 && r.lc == 1)
    {
        res.size = l.size + r.size - 1;
    }
    else
    {
        res.size = l.size + r.size;
    }
    return res;
}
node mergeResult(node l, node r)
{
    if (l.lc == -1)
    {
        return r;
    }
    return merge(l, r);
}
void change(int cur, int s, int t, int w)
{
    if (s == t)
    {
        tree[cur].lc = 1;
        tree[cur].rc = 1;
        tree[cur].size = 1;
        return;
    }
    int mid = (s + t) / 2;
    if (w <= mid)
    {
        change(cur * 2, s, mid, w);
    }
    else
    {
        change(cur * 2 + 1, mid + 1, t, w);
    }
    tree[cur] = merge(tree[cur * 2], tree[cur * 2 + 1]);
}
node query(int cur, int s, int t, int l, int r)
{
    if (l <= s && t <= r)
    {
        return tree[cur];
    }
    int mid = (s + t) / 2;
    node res;
    res.lc = -1;
    if (l <= mid)
    {
        res = mergeResult(res, query(cur * 2, s, mid, l, r));
    }
    if (r > mid)
    {
        res = mergeResult(res, query(cur * 2 + 1, mid + 1, t, l, r));
    }
    return res;
}
int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i].h);
        p[i].id = i;
    }
    for (int i = 1; i <= q; i++)
    {
        scanf("%d%d%d", &answer[i].l, &answer[i].r, &answer[i].h);
        answer[i].id = i;
    }
    std::sort(p + 1, p + 1 + n, [](const island &__x, const island &__y) { return __x.h > __y.h; });
    std::sort(answer + 1, answer + 1 + q, [](const question &__x, const question &__y) { return __x.h > __y.h; });
    int cnt = 1;
    for (int i = 1; i <= q; i++)
    {
        for (; cnt <= n && p[cnt].h > answer[i].h;)
        {
            change(1, 1, n, p[cnt].id);
            cnt++;
        }
        answer[i].res = query(1, 1, n, answer[i].l, answer[i].r).size;
    }
    std::sort(answer + 1, answer + 1 + q, [](const question &__x, const question &__y) { return __x.id < __y.id; });
    for (int i = 1; i <= q; i++)
    {
        printf("%d\n", answer[i].res);
    }
    return 0;
}
```

---

## 作者：Mu_leaf (赞：0)

## [思路]

注意到每次操作没有对后面的操作没有影响，于是想到将海平面从高到低排序后，一个位置的高度一旦超过海平面，那么以后所有操作都会超过海平面，于是考虑离线操作。

考虑线段树维护，当该位置高度高于海平面时直接单点修改为 1。因为一个位置最多会被修改一遍，所以可以考虑用指针维护。

## Show me your code！

```cpp
#include <bits/stdc++.h>
#define int long long
#define ls (x<<1)
#define rs (x<<1|1)
#define mid ((l+r)>>1)
using namespace std;
inline int read(){
	int f=1,x=0;char c=getchar();
	while(c<'0' || c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0' && c<='9') x=(x<<1)+(x<<3)+c-48,c=getchar();
	return x*f;
}
void write(int x){
	if(x<0)x=-x,putchar('-');
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
const int N=2e5+5;
int n,q;
int h[N];
int ans[N];
struct node{
	int x,id;
}b[N];
struct Tree{
	int val,lc,rc;
}tr[N<<2];
void pushup(int x){
	tr[x].val=tr[ls].val+tr[rs].val-1;
	tr[x].lc=tr[ls].lc,tr[x].rc=tr[rs].rc;
	if(tr[ls].rc!=tr[rs].lc || !tr[rs].lc && !tr[ls].rc) tr[x].val++;
}
void change(int x,int l,int r,int v,int k){
	if(l==r){
		tr[x].lc=tr[x].rc=k;
		tr[x].val=1;
		return;
	}
	if(v<=mid) change(ls,l,mid,v,k);
	else change(rs,mid+1,r,v,k);
	pushup(x);
}
void init(Tree &ans){
	ans.lc=ans.rc=ans.val=0;
}
Tree query(int x,int l,int r,int lt,int rt){
	if(l>=lt && r<=rt){
		return tr[x];
	}
	Tree ans,lc,rc;
	init(ans);init(lc);init(rc);
	if(lt<=mid) lc=query(ls,l,mid,lt,rt);
	if(rt >mid) rc=query(rs,mid+1,r,lt,rt);
	ans.val=lc.val+rc.val;
	ans.lc=lc.lc,ans.rc=rc.rc;
	if(lc.rc && rc.lc) ans.val--;
	return ans;
}
struct Q{
	int l,r,x,id;
}qu[N];
bool cmp(Q a,Q b){
	return a.x>b.x; 
}
bool cmp1(node a,node b){
	return a.x>b.x;
}
signed main(){
//	freopen("island.in","r",stdin);
//	freopen("island.out","w",stdout);
	n=read(),q=read();
	for(int i=1;i<=n;i++) h[i]=read(),b[i].x=h[i],b[i].id=i;
	for(int i=1;i<=q;i++){
		qu[i]=(Q){read(),read(),read(),i};
	}
	sort(b+1,b+n+1,cmp1);
	sort(qu+1,qu+q+1,cmp);
	int l=1;

	for(int i=1;i<=q;i++){
		while(b[l].x>qu[i].x && l<=n){
			change(1,1,n,b[l].id,1);
			l++;
		}
		ans[qu[i].id]=query(1,1,n,qu[i].l,qu[i].r).val;
	} 
	for(int i=1;i<=q;i++) cout << ans[i] << "\n";
	return 0;
}


```

---

