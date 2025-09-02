# LuoTianyi and the Function

## 题目描述

洛天依给你一个长度为 $n$ 的整数数组 $a$，下标从 $1$ 开始。

定义 $g(i,j)$ 如下：

- 当 $i \le j$ 时，$g(i,j)$ 是满足 $\{a_p:i\le p\le j\}\subseteq\{a_q:x\le q\le j\}$ 的最大整数 $x$；
- 当 $i>j$ 时，$g(i,j)=0$。

共有 $q$ 次查询。对于每次查询，给定四个整数 $l,r,x,y$，你需要计算 $\sum\limits_{i=l}^{r}\sum\limits_{j=x}^{y}g(i,j)$。

## 说明/提示

在第一个样例中：

第一次查询的答案是 $g(1,4)+g(1,5)=3+3=6$。

$x=1,2,3$ 满足 $\{a_p:1\le p\le 4\}\subseteq\{a_q:x\le q\le 4\}$，其中 $3$ 是最大的整数，因此 $g(1,4)=3$。

第二次查询的答案是 $g(2,3)+g(3,3)=3+3=6$。

第三次查询的答案是 $0$，因为所有 $i>j$ 且 $g(i,j)=0$。

第四次查询的答案是 $g(6,6)=6$。

在第二个样例中：

第二次查询的答案是 $g(2,3)=2$。

第四次查询的答案是 $g(1,4)+g(1,5)=2+2=4$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
6 4
1 2 2 1 3 4
1 1 4 5
2 3 3 3
3 6 1 2
6 6 6 6```

### 输出

```
6
6
0
6```

## 样例 #2

### 输入

```
10 5
10 2 8 10 9 8 2 1 1 8
1 1 10 10
2 2 3 3
6 6 6 6
1 1 4 5
4 8 4 8```

### 输出

```
4
2
6
4
80```

# 题解

## 作者：zesqwq (赞：16)

赛后发现没开 `long long`，痛失一千多分，呜呜呜。

先把询问差分。

我们定义 $f(l, r, x) = \sum_{i =l}^r \sum_{j=1}^y g(i, j)$。

我们先考虑对于同一个 $r$，如何快速计算 $\sum_{l=x}^y g(l, r)$，我们考虑扫描线，每次把当前位置戳成 $1$，把上一个和该元素相同的位置戳成 $0$，然后 $g(i, r)$ 就等于 $i$ 及以后第一个 $1$ 的位置，于是问题变为区间覆盖区间和。

当然你可以记 $dis_i$ 等于 $i$ 下一个 $1$ 的位置减去 $i$，这样就变为了区间加区间和。

然后我们发现求解 $f$ 变为了前 $x$ 个版本中的区间和，可以直接拉一个历史版本和线段树。

这样是不会很卡常的：）。

---

## 作者：Linnyx (赞：8)

考虑去拆 $\displaystyle \sum_{i=l}^{r}\sum_{j=x}^{y}g(i,j)$ 的贡献：


$$\displaystyle \sum_{i=l}^{r}\sum_{j=x}^{y}g(i,j)=\sum_{i=l}^{r}\sum_{j=1}^{y}g(i,j)-\sum_{i=l}^{r}\sum_{j=1}^{x-1}g(i,j)$$

题目告诉我们当 $i>j$ 时 $g(i,j)$ 的贡献为 $0$，所以我们可以进一步把式子写成：

$$\sum_{i=l}^{min(r,y)}\sum_{j=1}^{y}g(i,j)-\sum_{i=l}^{min(r,x-1)}\;\sum_{j=1}^{x-1}g(i,j)$$

这是一个历史版本和问题，多组询问离线用扫描线维护。

设 $ F_i $ 为在 $i$ 位置（包括 $i$ 位置）之后 $a_{i}$ 出现的次数。

假设我们现在处理到 $j$，$g(i,j)$ 的值为 $i$ 之后第一个出现 $F_x=1$ 的位置。

它影响的区间是从 $x$ 的位置之前再一个 $F_y=1$ 的位置的后一个位置到  $x$

（区间）即 $y+1\sim x$

我们从左向右依次加入 $a_{i}$，每次加入看作一个新的版本。

如果 $a_{i}$ 在之前出现过，我们考虑对其影响：

此时局面
![](https://cdn.luogu.com.cn/upload/image_hosting/i67pjzpy.png)

加入 $a_{i}$ 后，$F_{pre_{a_{i}}}$ 就不是 $1$ 了。

我们修改贡献，得：

![](https://cdn.luogu.com.cn/upload/image_hosting/49vbzkv8.png)

发现这是一个区间覆盖。

加入其贡献后，再使线段树上 $1\sim i$ 区间维护的当前版本加入历史版本和。

这是一个区间加。

所以我们需要一颗区间覆盖区间加线段树。

考虑推标记（懒可以直接矩阵，就是可能要卡常或者拆，我太菜了不会）

大佬 Ckain 的矩阵版：[blog](https://www.luogu.com.cn/blog/edisnimorF/post-2023-nian-6-yue-zuo-ti-ji-lu)

一共维护 $3$ 个标记：

$tga,tgc,tgcv\to$加法标记，常数标记，覆盖标记

因为 $tga$ 是依赖于当前版本，所以它的优先级应该高于 $tgcv$。

将每个节点的标记看作一个队列，同种可合并，但是相隔 $tgcv$ 的两个 $tga$ 并不可以合并，原因就是刚刚说的，$tga$ 是依赖于当前版本，$tgcv$ 更改了当前版本，两个 $tga$ 依赖的不是同一个版本，但是在 $tgcv$ 后的 $tga$ 会退化成 $tgc$（可直接算出，直接变成常数。

可以结合以下代码理解：


```cpp
void addx(int p,int x){//加法标记 
	t[p].hd+=x*t[p].d;
	if(t[p].tg.cx)t[p].tg.c1+=x*t[p].tg.cx;
	else t[p].tg.addx+=x; 
}
void addc(int p,int x){//常数标记
	t[p].hd+=x*t[p].len;
	t[p].tg.c1+=x;
}
void cx(int p,int x){//覆盖标记 
	t[p].d=x*t[p].len;
	t[p].tg.cx=x;
}
void pd(int p){
	if(t[p].tg.addx)addx(ls,t[p].tg.addx),addx(rs,t[p].tg.addx);
	if(t[p].tg.c1)addc(ls,t[p].tg.c1),addc(rs,t[p].tg.c1);
	if(t[p].tg.cx)cx(ls,t[p].tg.cx),cx(rs,t[p].tg.cx);
	t[p].tg={0,0,0};
}
```



还有细节问题可参考代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int rd(void){
	int s=0, f=1; char c=getchar();
	while(c<'0' || c>'9') {if(c=='-') f=0; c=getchar();}
	while(c>='0' && c<='9') {s=s*10+c-'0'; c=getchar();}
	return f? s:-s;
}
const int N=1e6+10;
int n,m;
int a[N];
struct tag{
	int addx,cx,c1;
};
struct node{
	tag tg;
	int hd,d,len,l,r;
}t[N<<2];
#define ls p*2
#define rs p*2+1
#define mid (t[p].l+t[p].r)/2
void build(int p,int l,int r){
	t[p].l=l;t[p].r=r;t[p].len=(r-l+1);
	if(l==r)return ;
	build(ls,l,mid);
	build(rs,mid+1,r);
}
void addx(int p,int x){//加法标记 
	t[p].hd+=x*t[p].d;
	if(t[p].tg.cx)t[p].tg.c1+=x*t[p].tg.cx;
	else t[p].tg.addx+=x; 
}
void addc(int p,int x){//常数标记
	t[p].hd+=x*t[p].len;
	t[p].tg.c1+=x;
}
void cx(int p,int x){//覆盖标记 
	t[p].d=x*t[p].len;
	t[p].tg.cx=x;
}
void pd(int p){
	if(t[p].tg.addx)addx(ls,t[p].tg.addx),addx(rs,t[p].tg.addx);
	if(t[p].tg.c1)addc(ls,t[p].tg.c1),addc(rs,t[p].tg.c1);
	if(t[p].tg.cx)cx(ls,t[p].tg.cx),cx(rs,t[p].tg.cx);
	t[p].tg={0,0,0};
}
void pu(int p){
	t[p].hd=t[ls].hd+t[rs].hd;
	t[p].d=t[ls].d+t[rs].d;
}
void upd(int p,int l,int r,int v,int f){
	//if(l>r)return ;
	if(t[p].l==l&&t[p].r==r){
		if(f)addx(p,v);
		else cx(p,v);
		return ;
	}
	pd(p);
	if(r<=mid)upd(ls,l,r,v,f);
	else if(l>mid)upd(rs,l,r,v,f);
	else{
		upd(ls,l,mid,v,f);upd(rs,mid+1,r,v,f);
	}
	pu(p);
}
int query(int p,int l,int r){
	//if(l>r)return 0;
	if(t[p].l==l&&t[p].r==r){
		return t[p].hd;
	}
	pd(p);
	if(r<=mid)return query(ls,l,r);
	else if(l>mid)return query(rs,l,r);
	else{
		return query(ls,l,mid)+query(rs,mid+1,r);
	}
}
#undef ls
#undef rs
#undef mid
struct Que{
	int l,r,f,id;
};
vector<Que> que[N];
set<int> st;
int pre[N],ans[N],pos[N];
signed main(){
	n=rd();m=rd();
	for(int i=1;i<=n;i++)a[i]=rd();
	for(int i=1;i<=m;i++){
		int l=rd(),r=rd(),x=rd(),y=rd();
		que[y].push_back({l,min(y,r),1,i});
		que[x-1].push_back({l,min(x-1,r),-1,i});
	}
	build(1,1,n);
	st.insert(0);
	for(int i=1;i<=n;i++){
		if(pre[a[i]]){
			auto it=st.lower_bound(pre[a[i]]);
			int l=*(--it);++it;
			int v=((++it)==st.end())?i:*it;--it;
			upd(1,l+1,pre[a[i]],v,0);
			st.erase(it);
		}
		pre[a[i]]=i;
		st.insert(i);
		upd(1,i,i,i,0);
		upd(1,1,i,1,1);
		for(Que k:que[i]){
			if(k.l<=k.r)ans[k.id]+=k.f*query(1,k.l,k.r);
		}
	}
	for(int i=1;i<=m;i++){
		printf("%lld\n",ans[i]);
	}
	return 0;
}
```


---

## 作者：orz_z (赞：5)

将询问差分，转成前缀和。

考虑扫描线维护，将右端点置为 $1$，它的 $lst$ 设为 $0$，则 $g(i,r)$ 为 $i$ 之后第一个 $1$，于是区间覆盖区间查询即可。

维护下一个 $1$ 与当前 $i$ 的差值，问题转化为区间加区间查询。

原问题答案即为，前缀版本历史和，套一棵区间价历史区间和线段树即可。

时间复杂度 $\mathcal O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef pair<int, int> pii;
#define F(i, a, b) for(int i = a; i <= (b); ++i)
#define F2(i, a, b) for(int i = a; i < (b); ++i)
#define dF(i, a, b) for(int i = a; i >= (b); --i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define Debug debug("Passing [%s] in LINS %d\n", __FUNCTION__, __LINE__)
#define pb push_back
#define fi first
#define se second
typedef long long ll;
//namespace Fread {const int SIZE = 1 << 17; char buf[SIZE], *S, *T; inline char getchar() {if (S == T) {T = (S = buf) + fread(buf, 1, SIZE, stdin); if (S == T) return '\n';} return *S++;}}
//namespace Fwrite {const int SIZE = 1 << 17; char buf[SIZE], *S = buf, *T = buf + SIZE; inline void flush() {fwrite(buf, 1, S - buf, stdout), S = buf;} inline void putchar(char c) {*S++ = c;if (S == T) flush();} struct NTR {~NTR() {flush();}} ztr;}
//#ifdef ONLINE_JUDGE
//#define getchar Fread::getchar
//#define putchar Fwrite::putchar
//#endif
inline int ri() {
	int x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return x * f;
}
inline void wi(int x) {
	if (x < 0) {
		putchar('-'), x = -x;
	}
	if (x > 9) wi(x / 10);
	putchar(x % 10 + 48);
}
inline void wi(int x, char s) {
	wi(x), putchar(s);
}
const int mod = 998244353;
const int inf = 0x3f3f3f3f;
const ll infll = 0x3f3f3f3f3f3f3f3f;
const int _ = 1e6 + 5;
int n, q;
struct node {
	int len, u, tg, mtg, s, ms;
	void add(int _tg, int _mtg, int _u) {
		ms += _u * s + _mtg * len;
		mtg += _u * tg + _mtg;
		tg += _tg;
		s += _tg * len;
		u += _u;
	}
} tr[_ << 2];
void up(int o) {
	tr[o].s = tr[o << 1].s + tr[o << 1 | 1].s;
}
void build(int o, int l, int r) {
	tr[o].len = r - l + 1;
	if (l == r) return void();
	int mid = (l + r) >> 1;
	build(o << 1, l, mid), build(o << 1 | 1, mid + 1, r);
	up(o);
}
void pd(int o) {
	if(tr[o].tg || tr[o].mtg || tr[o].u) {
		tr[o << 1].add(tr[o].tg, tr[o].mtg, tr[o].u);
		tr[o << 1 | 1].add(tr[o].tg, tr[o].mtg, tr[o].u);
		tr[o].tg = tr[o].mtg = tr[o].u = 0;
	}
}
void add(int o, int l, int r, int L, int R, int c) {
	if (L <= l && r <= R) return tr[o].add(c, 0, 0), void();
	int mid = (l + r) >> 1;
	pd(o);
	if (L <= mid) add(o << 1, l, mid, L, R, c);
	if (R > mid) add(o << 1 | 1, mid + 1, r, L, R, c);
	up(o);
}
int qry(int o, int l, int r, int L, int R) {
	if (L <= l && r <= R) return tr[o].ms;
	int mid = (l + r) >> 1, res = 0;
	pd(o);
	if (L <= mid) res = qry(o << 1, l, mid, L, R);
	if (R > mid) res += qry(o << 1 | 1, mid + 1, r, L, R);
	return res;
}
int lst[_], t[_], l[_], r[_], ans[_];
vector<pair<pair<int, int>, int>> qy[_];
signed main() {
	n = ri(), q = ri();
	int x;
	F(i, 1, n) x = ri(), lst[i] = t[x], t[x] = i;
	int y;
	F(i, 1, q) {
		int l, r;
		x = ri(), y = ri(), l = ri(), r = ri();
		qy[r].pb(make_pair(make_pair(x, y), i));
		qy[l - 1].pb(make_pair(make_pair(x, y), -i));
	}
	build(1, 1, n);
	F(i, 1, n) {
		x = lst[i], l[i] = i - 1, r[i] = i + 1;
		// delete lst[i]
		if(x) {
			// [l[x] + 1, x] += r[x] - x
			add(1, 1, n, l[x] + 1, x, r[x] - x);
			l[r[x]] = l[x], r[l[x]] = r[x];
		}
		// add i
		add(1, 1, n, i, i, i);
		tr[1].add(0, 0, 1);
		for(auto v : qy[i]) {
			int k = 1;
			if(v.se < 0) v.se = -v.se, k = -1;
			// calculate [x, y] [1, i]
			ans[v.se] += k * qry(1, 1, n, v.fi.fi, v.fi.se);
		}
	}
	F(i, 1, q) printf("%lld\n", ans[i]);
	return 0;
}
```

---

## 作者：min_inf (赞：4)

怎么题解都是线段树历史和。

考虑 $g(i,j)$ 的意义：假如我们从左往右扫描线扫到 $j$ 时，$i$ 最后出现的位置是 $lst_i$，则 $g(i,j)=\min\limits_{lst_i \ge i} lst_i$。

用一个 ODT 维护 $g(i,j)$ 连续段，考虑往后加入一个数的影响：后面加入一个节点，然后 $lst_{a_i}$ 改变，则原位置对应的节点和后面一个节点合并。

把 $g(i,j)$ 放到二维平面上，每个节点就对应一个矩形，表示的区间是左端点区间，存活时间区间是右端点区间。扫描线+树状数组维护矩形加矩形和即可，方法参考 [这题](https://www.luogu.com.cn/problem/P4514)。

$O((n+q) \log n)$ 没卡常也能吊打历史和线段树。

[code](https://codeforces.com/contest/1824/submission/241225751)

---

## 作者：yimuhua (赞：2)

卡常卡一天.jpg

首先考虑固定左端点，发现只需要保留每个数在右端点前最后一次出现的位置，假设是 $1$，其他的为 $0$，然后询问变成了左端点的下一个 $1$ 的位置，线段树维护区间加、区间和。

那么右端点从 $i-1$ 移动到 $i$ 时会把 $last_{a_i}$ 改成 $0$，$i$ 改成 $1$，其中 $last_i$ 表示 $i$ 上一次出现的位置。

也就是对一个区间加，然后将 $i$ 赋值为 $i$。线段树维护区间加、区间历史和即可。

然后这题卡常，因为我们发现用矩阵做要乘上 $3^3$ 的矩阵乘法复杂度，长成这样：

$\begin{bmatrix}a\\b\\len\end{bmatrix}$

区间加 $v$：

$\begin{bmatrix}a\\b\\len\end{bmatrix}\begin{bmatrix}1&0&0\\0&1&0\\v&0&1\end{bmatrix}=\begin{bmatrix}a+len*v\\b\\len\end{bmatrix}$

更新历史和：

$\begin{bmatrix}a\\b\\len\end{bmatrix}\begin{bmatrix}1&1&0\\0&1&0\\0&0&1\end{bmatrix}=\begin{bmatrix}a\\b+a\\len\end{bmatrix}$

观察可知在两个 $tag$ 矩阵相乘时，只有 $(1,2),(3,1),(3,2)$ 这三个位置会发生改变，而线段树 $tree$ 数组也只有三个信息需要维护，所以将 $3\times3$ 的数组改成三个变量。

然后发现乘的时候有一些位置相乘一定是 $0$，可以忽略。手动模拟矩乘，大概只剩下 $3$ 倍常数。

时间复杂度 $O(k\times (n+q) \log n)$，其中 $k$ 为矩乘复杂度，被缩减为一个 $3$ 左右的常数，差不多能过。实在过不掉可以开 C++20，$64$ 位真的很快！

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace IO {
	inline char gc() {
		static const int IN_LEN = 1 << 18 | 1;
		static char buf[IN_LEN], *s, *t;
		return (s == t) && (t = (s = buf) + fread(buf, 1, IN_LEN, stdin)), s == t ? -1 : *s++;
	}
	template <typename T>
	inline void read(T &x) {
		static char ch, ff;
		ch = gc(), ff = 0;
		for(; !isdigit(ch); ch = gc())
			ff |= ch == '-';
		for(x = 0; isdigit(ch); ch = gc())
			x = (x << 3) + (x << 1) + (ch ^ 48);
		ff && (x = -x);
		return;
	}
	template <typename T, typename ...t>
	void read(T&x, t& ...y) {
		read(x), read(y...);
		return;
	}
	template <typename T>
	inline void print(T x) {
		static int pr, pri[105], temp;
		pr = 0, temp = x;
		if(x < 0)
			fputc('-', stdout), x = -x;
		if(!x) {
			fputc(48, stdout);
			return;
		}
		while(x)
			pri[++pr] = x % 10, x /= 10;
		for(; pr; pr--)
			fputc(pri[pr] + 48, stdout);
		x = temp;
		return;
	}
	template <typename T, typename ...t>
	void print(T&x, t& ...y) {
		print(x), fputc(' ', stdout), print(y...);
		return;
	}
}
using namespace IO;
struct query {
	int l, r, v, id;
};
set<int> s;
long long ans[1000005];
vector<query> v[1000005];
int n, q, a[1000005], p[1000005];
struct Tree {
	struct Tag {
		long long x, y, z;
		Tag() {
			x = y = z = 0;
		}
		Tag(long long _x, long long _y, long long _z) {
			x = _x, y = _y, z = _z;
		}
		friend Tag operator * (Tag A, Tag B) {
			return Tag(A.x + B.x, A.y + B.y, A.z + B.z + A.y * B.x);
		}
	}tag[4000005];
	struct node {
		long long x, y, z;
		node() {
			x = y = z = 0;
		}
		node(long long _x, long long _y, long long _z) {
			x = _x, y = _y, z = _z;
		}
		friend node operator + (node A, node B) {
			return node(A.x + B.x, A.y + B.y, A.z + B.z);
		}
		friend node& operator *= (node &A, Tag B) {
			return A = node(A.x + A.z * B.y, A.x * B.x + A.y + A.z * B.z, A.z);
		}
	}t[4000005];
	void pushup(int x) {
		t[x] = t[x << 1] + t[x << 1 | 1];
		return;
	}
	void build(int x, int l, int r) {
		t[x].z = r - l + 1;
		if(l == r)
			return;
		int mid = l + r >> 1;
		return build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	void addtag(int x, Tag v) {
		t[x] *= v, tag[x] = tag[x] * v;
		return;
	}
	void pushdown(int x) {
		addtag(x << 1, tag[x]), addtag(x << 1 | 1, tag[x]), tag[x] = Tag(0, 0, 0);
		return;
	}
	void update(int cur, int l, int r, int x, int y, int v) {
		if(l > y || r < x)
			return;
		if(x <= l && r <= y)
			return addtag(cur, {0, v, 0});
		int mid = l + r >> 1;
		return pushdown(cur), update(cur << 1, l, mid, x, y, v), update(cur << 1 | 1, mid + 1, r, x, y, v), pushup(cur);
	}
	long long query(int cur, int l, int r, int x, int y) {
		if(l > y || r < x)
			return 0;
		if(x <= l && r <= y)
			return t[cur].y;
		int mid = l + r >> 1;
		return pushdown(cur), query(cur << 1, l, mid, x, y) + query(cur << 1 | 1, mid + 1, r, x, y);
	}
}T;
int main() {
	read(n, q), s.insert(0), T.build(1, 1, n);
	for(int i = 1; i <= n; i++)
		read(a[i]);
	for(int i = 1, l, r, x, y; i <= q; i++)
		read(l, r, x, y), v[x - 1].push_back({l, r, -1, i}), v[y].push_back({l, r, 1, i});
	for(int i = 1; i <= n; i++) {
		s.insert(i);
		if(p[a[i]]) {
			auto j = s.find(p[a[i]]);
			T.update(1, 1, n, *prev(j) + 1, *j, *next(j) - *j), s.erase(j);
		}
		T.update(1, 1, n, i, i, i), T.addtag(1, {1, 0, 0}), p[a[i]] = i;
		for(auto j : v[i])
			if(j.l <= i)
				ans[j.id] += j.v * T.query(1, 1, n, j.l, min(j.r, i));
	}
	for(int i = 1; i <= q; i++)
		print(ans[i]), fputc('\n', stdout);
	return 0;
}
```

---

## 作者：CaoXian (赞：2)

不会线段树历史版本区间和，~~学了好几个小时再加因为数组开小的几个小时的虚空调试终于过了~~。

这篇题解会更详细的讲解如何实现线段树历史版本求和。

也推荐一篇讲解[线段树历史版本区间和的博客](https://www.luogu.com.cn/blog/MuYC/xian-duan-shu-wei-hu-ou-jian-li-shi-ban-ben-hu)，我是从这里面学的。

---

观察函数 $g(i, j)$ 的定义，会发现 $j$ 这个右端点是不动的，于是考虑右端点确定的时候左端点（也就是答案）在哪里。

如果我们从第 $j$ 个数开始从后往前数，计算每种数的出现个数，那么可以发现左端点一定是落在**第** $i$ **个数右边（包含）第一个出现次数为** $1$ **的位置**。

知道了这一点再来考虑把第 $j + 1$ 个数加进来的时候的变化，很明显第 $j + 1$ 个数只会引起上一个 $a_{k} = a_{j + 1}$ 的位置 $k$ 的变化，于是记录一个 $last_{i}$ 表示数 $i$ 上一次出现的位置在哪里。

加入了 $a_{j + 1}$ 后，$a_{last_{a_{j + 1}}}$ 的出现次数也就从 $1$ 变到了 $2$，那么 $last_{a_{j + 1}}$ 前面的 $g(l, j)$ 也会变化，具体来说在 $k$ 的上一个出现次数为 $1$ 的位置到 $last_{a_{j + 1}}$ 这一段的函数值都会变化。这样我们可以用线段树区间推平来维护函数值，而记录前一个和后一个出现次数为 $1$ 的位置可以使用链表维护。

但是区间推平的标记并不如区间加法容易记录和计算，所以我们维护 $g(i, j) - i$ 的值，这样我们就可以把区间赋值变成区间加法了。

（上面虽然说是维护 $g(i, j) - i$ 的值，但是实际上在代码中我为了偷懒会把 $i$ 加进去，这一点其实无伤大雅。）

如果我们把 $j = 1$ 时的函数值写下来，排成一行，再把 $j = 2$ 时的函数值写下来，排成新的一行，以此类推，那么题目其实就是要我们矩阵求和。

但这样是不可做的，我们没有注意到第 $i$ 行是由第 $i - 1$ 行推过来的这一性质。如果把每一行看作线段树的一个版本，那么这道题是让我们做线段树历史版本区间求和。

因为这道题不要求强制在线，那么可以先把询问离线下来，差分成 $\sum\limits_{j = 1}^{x - 1}\sum\limits_{i = l}^{r}g(i, j)$ 和 $\sum\limits_{j = 1}^{y}\sum\limits_{i = l}^{r}g(i, j)$，按照所需的版本编号排序就可以了。

如果你会这个东西那么接下来的讲解就可以不用看了，如果不会的话那么建议你继续看下去。

暴力保存和查询每个版本的线段树慢的原因在于：直接保存了每个函数值最终的结果，没有利用到区间加法可以打标记维护的性质。

考虑一次单点加法对某个函数值以及接下来的一段时间的影响：假设这次加法的时间为 $t$，加的值为 $v$，当前时间为 $tim$，那么这次加法对于 $t \sim tim$ 这段时间的每个线段树都有贡献，每个贡献都是 $v$，那么对这一段版本和的贡献就是 $(tim - t)v$。

拓展到区间加法也是一样的道理：只需要再乘上一个区间长度即可。

那么再拓展到有许多次加法操作，那么对于 $tim$ 及其之前的历史版本和的贡献就是：

$$
\sum(tim - t_{i} + 1)v_{i}
$$

对于这种式子有一个很常见的套路就是用乘法分配律将式子展开分别维护，于是贡献就是：

$$
(tim + 1)\sum v_{i} - \sum t_{i}v_{i}
$$

（上面是对于单点的情况，对于区间那么在外面乘上区间长度就好。）

于是分别维护某个区间的标记 $\sum v_{i}$ 和 $\sum t_{i}v_{i}$ 即可，把这两个标记分别称为 $add$ 和 $del$，查询的时候计算 $(tim + 1)add - del$ 即可。

同时也要维护一个区间的和，也就是线段树递归到询问区间完全包含当前区间时直接返回，这样才能保证时间复杂度正确。

已有的标记不太好直接维护这个，那么直接再开一些标记： $sum$ 表示当前版本的区间和，$t$ 表示这个区间上次更新历史版本区间和在什么时候，$sumh$ 表示这个区间的历史版本区间和。（要注意区分这里的 $t$ 标记和上面的修改时间 $t$。）

一个区间在要被更新的时候，计算这一段版本的区间和（因为在这一段版本中它没有被修改过，而在接下来它马上就要被修改了），更新 $sumh$ 和 $t$。具体地，令 $sumh$ 加上 $(tim - t)sum$，令 $t$ 设为 $tim$，实际上是把这一段历史版本区间和加进到了 $sumh$ 里以后就可以不管了，可以避免许多复杂麻烦的标记合并。

具体可以看代码实现（使用了标记永久化）：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, q, l, r, x, y, cq, tim, now, pos, a[1000005], last[1000005], lt[1000005], rt[1000005];
ll ans[1000005];
struct query {
	int l, r, x, v, id;
	query(int L = 0, int R = 0, int X = 0, int V = 0, int Id = 0): l(L), r(R), x(X), v(V), id(Id) {}
	bool operator < (const query& _) const {
		return x < _.x;
	}
} qu[2000005];
struct Segment_Tree {
	struct segment {
		int l, r;
		ll sum, sumh, t, add, del;
		void operator += (const ll& _) {
			add += _, del += tim * _;
			sumh += (tim - t) * sum;
			sum += (r - l + 1) * _;
			t = tim;
		}
	} t[4000005];
	#define lc (k << 1)
	#define rc (lc | 1)
	#define mid ((t[k].l + t[k].r) >> 1)
	void build(int k) {
		if(t[k].l == t[k].r) return;
		t[lc].l = t[k].l, t[lc].r = mid, t[rc].l = mid + 1, t[rc].r = t[k].r;
		build(lc), build(rc);
	}
	void change(int k, const int& L, const int& R, const ll& v) {
		if(L <= t[k].l && t[k].r <= R) {
			t[k] += v;
			return;
		}
		t[k].sumh += t[k].sum * (tim - t[k].t);
		t[k].sum += (min(R, t[k].r) - max(L, t[k].l) + 1) * v;
		t[k].t = tim;
		if(L <= mid) change(lc, L, R, v);
		if(R > mid) change(rc, L, R, v);
	}
	ll ask(int k, const int& L, const int& R) {
		const ll len = min(R, t[k].r) - max(L, t[k].l) + 1;
		ll ret = t[k].add * len * (tim + 1) - t[k].del * len;
		if(L <= t[k].l && t[k].r <= R) return t[k].sumh + t[k].sum * (tim - t[k].t + 1);
		if(L <= mid) ret += ask(lc, L, R);
		if(R > mid) ret += ask(rc, L, R);
		return ret;
	}
} tree;
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> q;
	for(int i = 1; i <= n; ++i) {
		cin >> a[i];
		lt[i] = i - 1, rt[i] = i + 1;
	}
	for(int i = 1; i <= q; ++i) {
		cin >> l >> r >> x >> y;
		if(x > 1) qu[++cq] = query(l, r, x - 1, -1, i);
		qu[++cq] = query(l, r, y, 1, i);
	}
	stable_sort(qu + 1, qu + 1 + cq);
	tree.t[1].l = 1, tree.t[1].r = n;
	tree.build(1);
	for(tim = 1, now = 1; tim <= n; ++tim) {
		pos = last[a[tim]];
		if(pos) {
			tree.change(1, lt[pos] + 1, pos, rt[pos] - pos);
			rt[lt[pos]] = rt[pos], lt[rt[pos]] = lt[pos];
		}
		last[a[tim]] = tim;
		tree.change(1, tim, tim, tim);
		while(now <= cq && qu[now].x == tim) {
			ans[qu[now].id] += qu[now].v * tree.ask(1, qu[now].l, qu[now].r);
			++now;
		}
	}
	for(int i = 1; i <= q; ++i) cout << ans[i] << '\n';
	return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：2)

把询问差分下来，下面只讨论 $l=x=1$ 的情况。

考虑 $j$ 右移，会造成区间修改。很显然我们可以把它变成区间加。那么问题就变成了了区间加，求历史和的问题。随便啥数据结构维护，但是显然只能 $\log$，只有线段树。

谁爱写谁写。

[submission](https://codeforces.com/contest/1824/submission/221933088)

---

## 作者：Mingjunyi (赞：1)

## [CF1824D LuoTianyi and the Function](https://codeforces.com/contest/1824/problem/D)

### 分析

#### 拆式子

式子都给我们了，上手考虑拆贡献。

因为 $g(i,j)$ 是独立的，有：

$$
\sum\limits_{i=l}^r\sum\limits_{j=x}^y g(i,j) = \sum\limits_{i=l}^r\sum\limits_{j=1}^y g(i,j) - \sum\limits_{i=l}^r\sum\limits_{j=1}^{x-1} g(i,j)
$$

题目中说：当 $i > j$ 时，$g(i,j) = 0$。

所以有：

$$
\begin{aligned}
\sum\limits_{i=l}^r\sum\limits_{j=x}^y g(i,j) &= \sum\limits_{i=l}^r\sum\limits_{j=1}^y g(i,j) - \sum\limits_{i=l}^r\sum\limits_{j=1}^{x-1} g(i,j) \\
&= \sum\limits_{i=l}^{\min(r,y)}\sum\limits_{j=1}^y g(i,j) - \sum\limits_{i=l}^{\min(r,x - 1)}\sum\limits_{j=1}^{x-1} g(i,j)\\
&= \sum\limits_{j=1}^y\sum\limits_{i=l}^{\min(r,y)} g(i,j) - \sum\limits_{j=1}^{x-1}\sum\limits_{i=l}^{\min(r,x - 1)} g(i,j)
\end{aligned}
$$

对于外面这一维求和（即 $\sum\limits_{j = 1}$），我们可以扫描线去做。

里面这一维求和（即 $\sum\limits_{i = l}^{r^{\prime}}$），我们可以做一个历史和，也就是计算当 $i:l\sim r^{\prime}$ 时，$g(i,j)$ 对于   $j:1\sim k$ 产生的 $k$ 个版本的贡献的总和。

我们可以把询问离线下来，将询问拆开，分别插入到区间的右端点上，在遍历的时候计算答案。

因为我们做的是前缀和差分，插入的时候记得记录贡献的符号！

#### 贡献的计算

为了直观的体会贡献是如何变化的，可以手模一些例子：

如图：
![img](https://cdn.luogu.com.cn/upload/image_hosting/46zkf7bq.png)

这是当 $j = 8$ 时的 $g(i,j)$ 数组。

考虑 $j = 9$ 时的情况：

1. 当 $a_9 = 6$ 时，如图：
![img](https://cdn.luogu.com.cn/upload/image_hosting/czmsgekq.png)
此时上一个 $6$ 所在的颜色段和其下一个颜色段合并了，并且贡献变为其下一个颜色段的 $g(i,j)$，在末尾新增了一个 $g(i,j) = 9$ 的新颜色段。

2. 当 $a_9 = 4$ 时，如图：
![img](https://cdn.luogu.com.cn/upload/image_hosting/vrh40g9d.png)
由于先前没有 $a_i = 4$，所以只在末尾新增了一个 $g(i,j) = 4$ 的新颜色段。

所以，我们可以用set维护这些颜色段，在扫描的时候判断是否需要合并两个颜色段，并不断在末尾新增颜色段。

当两个颜色段合并时，用历史和线段树做区间覆盖操作。

在所有操作结束之后，更新历史和。

最后将答案输出即可。

#### 常数问题

我喜欢通过构造矩阵来计算历史和。

但这道题卡常。

显然，类似于 [[NOIP2022] 比赛](https://www.luogu.com.cn/problem/P8868)，我们需要将矩阵拆开。

我们一共有两种矩阵：
1. 覆盖矩阵

$$\begin{bmatrix}
1 & 0 & 0 \\
0 & 0 & d \\
0 & 0 & 1 \\
\end{bmatrix}
$$
2. 更新矩阵

$$\begin{bmatrix}
1 & 1 & 0 \\
0 & 1 & 0 \\
0 & 0 & 1 \\
\end{bmatrix}
$$

随机累乘矩阵，可以发现我们实际需要维护的位置只有 $(a,b,c,d)$ 这四个位置：
$$\begin{bmatrix}
1 & a & b \\
0 & c & d \\
0 & 0 & 1 \\
\end{bmatrix}
$$

那么手模矩阵乘法就可以将 $3^3$ 的常数减小到 $3\sim 4$ 左右。

### AC-code：

我的代码常数比较大，所以用快读和```C++20 64bits winlibs```选项才能过。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
namespace IO {
	inline char gc() {
		static const int IN_LEN = 1 << 18 | 1;
		static char buf[IN_LEN], *s, *t;
		return (s == t) && (t = (s = buf) + fread(buf, 1, IN_LEN, stdin)), s == t ? -1 : *s++;
	}
	template <typename T>
	inline void read(T &x) {
		static char ch, ff;
		ch = gc(), ff = 0;
		for(; !isdigit(ch); ch = gc())
			ff |= ch == '-';
		for(x = 0; isdigit(ch); ch = gc())
			x = (x << 3) + (x << 1) + (ch ^ 48);
		ff && (x = -x);
		return;
	}
	template <typename T, typename ...t>
	void read(T&x, t& ...y) {
		read(x), read(y...);
		return;
	}
	template <typename T>
	inline void print(T x) {
		static int pr, pri[105], temp;
		pr = 0, temp = x;
		if(x < 0)
			fputc('-', stdout), x = -x;
		if(!x) {
			fputc(48, stdout);
			return;
		}
		while(x)
			pri[++pr] = x % 10, x /= 10;
		for(; pr; pr--)
			fputc(pri[pr] + 48, stdout);
		x = temp;
		return;
	}
	template <typename T, typename ...t>
	void print(T&x, t& ...y) {
		print(x), fputc(' ', stdout), print(y...);
		return;
	}
}
using namespace IO;


struct tag{
    int x[7];
    inline void init() {
        x[1] = x[4] = x[6] = 1;
        x[2] = x[3] = x[5] = 0;
    }
    inline int& operator [](const int pos) {return x[pos];}
	inline friend tag operator * (tag& A,tag& B) {
        tag c;c.init();
        c[2] = A[2] * B[4] + B[2];
        c[3] = B[3] + A[2] * B[5] + A[3];
		c[4] = A[4] * B[4];
        c[5] = B[5] * A[4] + A[5];
        return c;
    }
    inline friend bool operator != (tag A,tag B) {
        for(int i = 0;i<7;i++)
            if(A[i] != B[i])
                return true;
        return false;
    }
    inline void print(string s) {
        cout<<"test for "<<s<<" matrix\n";
        cout<<x[1]<<' '<<x[2]<<' '<<x[3]<<'\n';
        cout<<0<<' '<<x[4]<<' '<<x[5]<<'\n';
        cout<<0<<' '<<0<<' '<<x[6]<<'\n'; 
   }
};

inline tag addtag(int k) {tag c;c.init();c[4] = 0;c[5] = k;return c;}
inline tag updtag() {tag c;c.init();c[2] = 1;return c;}
inline tag NONE(){tag c;c.init();return c;}

struct vet{
    int y[4];
    void init() {y[1] = y[2] = y[3] = 0;}
    int& operator [](const int pos) {return y[pos];}
    inline friend vet operator + (vet a,vet b) {
        vet c;c.init();
        c[1] = a[1] + b[1];
        c[2] = a[2] + b[2];
        c[3] = a[3] + b[3];
        return c;
    }
    inline void print(string s) {
        cout<<'\n';
        cout<<"test for "<<s<<" vector\n";
        cout<<y[1]<<'\n';
        cout<<y[2]<<'\n';
        cout<<y[3]<<'\n';
        cout<<'\n';
    }
};

inline vet operator * (tag A,vet B) {
    vet c;c.init();
    c[1] = B[1] + B[2] * A[2] +B[3] * A[3];
    c[2] = B[2] * A[4] + A[5] * B[3];
    c[3] = B[3];
    return c;
}

const int N = 1e6+5;
int n,q,a[N],ans[N],pre[N];
vector<array<int,4>> R[N];
set<int> s;

#define ls (p << 1)
#define rs (ls | 1)
#define mid ((pl + pr) >> 1)
tag T[N<<2];vet V[N<<2];
bool ext[N<<2];

inline void push_up(int p) {
	V[p] = V[ls] + V[rs];
}

inline void addtag(int p,tag x){
	V[p] = x * V[p];
	T[p] = x * T[p];
	ext[p] = true;
}

inline void push_down(int p){
	if(ext[p]) {
		addtag(ls,T[p]);
		addtag(rs,T[p]);
		T[p].init();
		ext[p] = false;
	}
}

inline void build(int p,int pl,int pr) {
	T[p].init();
	V[p].init();
	if(pl == pr) {
		V[p][3] = 1;
		return;
	}
	build(ls,pl,mid);
	build(rs,mid+1,pr);
	push_up(p);
}

inline void update(int p,int pl,int pr,int l,int r,tag x) {
	if(l <= pl && pr <= r) {addtag(p,x);return;}
	push_down(p);
	if(l <= mid) update(ls,pl,mid,l,r,x);
	if(r > mid) update(rs,mid+1,pr,l,r,x);
	push_up(p);
}

inline vet query(int p,int pl,int pr,int l,int r){
	if(l <= pl && pr <= r) return V[p];
	push_down(p);
	if(r <= mid) return query(ls,pl,mid,l,r);
	else if(l > mid) return query(rs,mid+1,pr,l,r);
	else return query(ls,pl,mid,l,r) + query(rs,mid+1,pr,l,r);
}

signed main() {
	read(n,q);
	for(int i = 1;i<=n;i++) read(a[i]);
	for(int i = 1,l,r,x,y;i<=q;i++) {
		read(l,r,x,y);
		R[x - 1].emplace_back((array<int,4>){-1,l,min(r,x - 1),i});
		R[y].emplace_back((array<int,4>){1,l,min(r,y),i});
	}
	s.insert(0);
	build(1,1,n);
	for(int i = 1;i<=n;i++) {
		auto it = s.lower_bound(pre[a[i]]);
		if(it != s.begin()) {
			int l = *(--it),v;
			++it;++it;
			v = (it == s.end()) ? i : (*it);
			if(l < pre[a[i]]) update(1,1,n,l+1,pre[a[i]],addtag(v));
		}
		update(1,1,n,i,i,addtag(i));
		if(pre[a[i]]) s.erase(pre[a[i]]);
		s.insert(i);
		pre[a[i]] = i;
		update(1,1,n,1,i,updtag());
		for(auto c:R[i]) 
			if(c[1] <= c[2]) 
				ans[c[3]] += c[0] * query(1,1,n,c[1],c[2])[1];
	}
	for(int i = 1;i<=q;i++) print(ans[i]), fputc('\n', stdout);
	return 0;
}
```

---

## 作者：Jerrycyx (赞：0)

## 前言

练习线段树历史版本和的绝佳好题，就是卡常有点恶心。

## 推式子

先观察每个询问拆成差分形式是怎样的：

$$\sum_{i=l}^{r} \sum_{j=x}^{y} g(i,j) = \sum_{i=l}^{r} \sum_{j=1}^{y} g(i,j) - \sum_{i=l}^{r} \sum_{j=1}^{x-1} g(i,j)$$

两式都是 $\sum_{i=l}^{r} \sum_{j=1}^{p} g(i,j)$ 的形式，设其为 $f(p,l,r)$，试着推下式子：

$$f(p,l,r) = \sum_{i=l}^{r} \sum_{j=1}^{p} g(i,j) = \sum_{j=1}^{p} \boxed{ \sum_{i=l}^{r} g(i,j)}$$

发现右侧（框起来的部分）只有一处出现了左侧的指标 $j$。那么我们设 $h_j (l,r) = \sum_{i = l}^{r} g(i,j)$，就有：

$$f(p,l,r) = \sum_{j=1}^{p} h_j (l,r)$$

**将所有询问离线。如果我们使用扫描线，从 $1$ 开始不断右移 $p$，那么这个式子就相当于是 $h (l,r)$ 直到 $p$ 时间的历史版本和**，设其为 $H_p (l,r) = f(p,l,r)$。

## $g$ 的变化

考虑当 $p$ 右移时，每个 $g(i,p)$ 如何变化。

首先需要一个辅助 $01$ 串 $b$，$b_i$ 标记 $a_i$ 是否是 $1 \sim p$ 中最后一个此种数，即 $b_i = [g(i,p) = i]$。

然后 $g(i,p)$ 就是 $i$ 及以后第一个 $b_j = 1$ 的 $j$。

举例，$p$ 由 $5$ 移向 $6$ 对数据的修改：

|编号 $i$|1|2|3|4|5($p$)|6($p'$)|...|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|$a_i$|$1$|$2$|$1$|$2$|$2$|$\it 1$|...|
|$b_i$|$0$|$0$|$\cancel{1}\ 0$|$0$|$1$|$\it 1$|...|
|$g(i,p)$|$\cancel{3}\ 5$|$\cancel{3}\ 5$|$\cancel{3}\ 5$|$5$|$5$|$\it 6$|...|

记前一个与 $a_i$ 相同数的位置为 $pre(i)$。可以发现，新加入一个数 $a_{p'}$ 对数据的影响是：

+ 加入 $b_{p'}$，值为 $1$；
+ $g(p',p')$ 的值就是 $p'$；
+ $b_{pre(p')}$ 置为 $0$；
+ $pre(p')$ 所在的 $b_i=0$ 的连续段 $[u,v]$ 的 $g(i,p)$ 全部覆盖为 $v+1$。

（最后一步实际上只有 $pre(p')$ 及以前的 $g$ 是有效修改）

维护 $b_i = 0$ 的连续段可以用并查集，连续为 $0$ 的 $b_i$ 为一个整块，每次单点修改 $b$ 时尝试将其与两侧合并。

## 线段树

要维护 $g(i,p)$，我们需要的线段树需要支持以下操作：

+ 区间覆盖
+ 区间历史版本和查询

我这里用矩阵来做，分别用 $his$、$sum$、$len$ 表示区间历史版本和、区间长度。一个区间内保存一个矩阵：

$$\begin{bmatrix}
his & sum & len
\end{bmatrix}$$

覆盖操作（用 $v$ 覆盖）：

$$
\begin{bmatrix}
his & sum & len
\end{bmatrix}
\times
\begin{bmatrix}
1 & 0 & 0 \\
0 & 0 & 0 \\
0 & v & 0
\end{bmatrix}
=
\begin{bmatrix}
his & v \times len & len
\end{bmatrix}
$$

更新历史和操作：

$$
\begin{bmatrix}
his & sum & len
\end{bmatrix}
\times
\begin{bmatrix}
1 & 0 & 0 \\
1 & 1 & 0 \\
0 & 0 & 1
\end{bmatrix}
=
\begin{bmatrix}
his+sum & sum & len
\end{bmatrix}
$$

然后就可以做了，注意延迟标记初始和重置都应为单位矩阵，还有**对于不在区间 $[1,n]$ 内的所有操作都应忽略**。

时间复杂度 $O(n \log n)$，快去吧。

```cpp
#include <cstdio>
#include <vector>
#include <cstring>
#include <cassert>
using namespace std;

namespace IO{
#ifndef JC_LOCAL
const int SIZE=1<<20; char buf[SIZE],*p1=buf,*p2=buf;
inline char _getchar() {return (p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZE,stdin),p1==p2))?EOF:*p1++;}
#else
inline char _getchar() {return getchar();}
#endif
template<typename TYPE> void read(TYPE &x)
{
	x=0; bool neg=false; char ch=_getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')neg=true;ch=_getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+(ch^'0');ch=_getchar();}
	if(neg){x=-x;} return;
}
template<typename TYPE> void write(TYPE x)
{
	if(!x){putchar('0');return;} if(x<0){putchar('-');x=-x;}
	static int sta[55];int statop=0; while(x){sta[++statop]=x%10;x/=10;}
	while(statop){putchar('0'+sta[statop--]);} return;
}
template<typename TYPE> void write(TYPE x,char ch){write(x);putchar(ch);return;}
} using IO::read; using IO::write;

typedef long long LL;

const int N = 1e6 + 5, Q = 1e6 + 5;
int n, q, a[N];

struct QueryStruct{
	int l, r;
	int id;
};
vector<QueryStruct> qrs[N];

namespace DSU{

int fa[N], mn[N], mx[N];
void init()
{
	for (int i = 1; i <= n; i++)
		fa[i] = mn[i] = mx[i] = i;
	return;
}
int query(int x)
{
	if (fa[x] == x) return x;
	else return fa[x] = query(fa[x]);
}
inline void merge(int x, int y)
{
	x = query(x), y = query(y);
	fa[y] = x;
	mx[x] = max(mx[x], mx[y]);
	mn[x] = min(mn[x], mn[y]);
	return;
}
inline int getmx(int x) {return mx[query(x)];}
inline int getmn(int x) {return mn[query(x)];}

} //namespace DSU

struct Matrix{
	int row, col;
	LL num[3][3];
	
	Matrix(bool _type, int _row, int _col) : row(_row), col(_col)
	{
		if(_type)
		{
			assert(_row == _col);
			for (int i = 0; i < _row; i++)
				for (int j = 0; j < _col; j++)
					num[i][j] = (i == j);
		}
		else memset(num, 0, sizeof num);
	}
	
	Matrix operator * (const Matrix &t) const
	{
		assert(col == t.row);
		Matrix res(false, row, t.col);
		for (int i = 0; i < row; i++)
			for (int j = 0; j < t.col; j++)
				for (int k = 0; k < col; k++)
					res.num[i][j] += num[i][k] * t.num[k][j];
		return res;
	}
	void operator *= (const Matrix &t)
	{
		*this = *this * t;
	}
	
	Matrix operator + (const Matrix &t) const
	{
		assert(row == t.row && col == t.col);
		Matrix res(false, row, col);
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				res.num[i][j] = num[i][j] + t.num[i][j];
		return res;
	}
};

namespace ST{

struct SegTree{
	int l, r;
	Matrix dat, lzy;
	SegTree() : dat(false, 1, 3), lzy(true, 3, 3) { }
	inline int mid() {return l + r >> 1;}
	inline void mul(const Matrix &t)
	{
		dat *= t, lzy *= t;
		return;
	}
} tr[N << 2];

inline void pushup(int p)
{
	tr[p].dat = tr[p << 1].dat + tr[p << 1 | 1].dat;
	return;
}
inline void pushdown(int p)
{
	tr[p << 1].mul(tr[p].lzy);
	tr[p << 1 | 1].mul(tr[p].lzy);
	tr[p].lzy = Matrix(true, 3, 3);
	return;
}

void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	if (l == r)
	{
		tr[p].dat.num[0][0] = 0;
		tr[p].dat.num[0][1] = 0;
		tr[p].dat.num[0][2] = 1;
		return;
	}
	int mid = tr[p].mid();
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	pushup(p);
	return;
}

void range_mul(int l, int r, const Matrix &v, int p)
{
	if (l <= tr[p].l && tr[p].r <= r)
	{
		tr[p].mul(v);
		return;
	}
	pushdown(p);
	int mid = tr[p].mid();
	if (l <= mid) range_mul(l, r, v, p << 1);
	if (r > mid) range_mul(l, r, v, p << 1 | 1);
	pushup(p);
	return;
}

LL his_sum(int l, int r, int p)
{
	if (l <= tr[p].l && tr[p].r <= r)
		return tr[p].dat.num[0][0];
	pushdown(p);
	int mid = tr[p].mid();
	LL res = 0;
	if (l <= mid) res += his_sum(l, r, p << 1);
	if (r > mid) res += his_sum(l, r, p << 1 | 1);
	return res;
}

void cover(int l, int r, int v)
{
	l = max(l, 1), r = min(r, n);
	if (l > r) return;
	v = min(v, n);
	Matrix tmp(false, 3, 3);
	tmp.num[0][0] = 1;
	tmp.num[2][1] = v;
	tmp.num[2][2] = 1;
	range_mul(l, r, tmp, 1);
	return;
}

void upd_his(int l, int r)
{
	Matrix tmp(true, 3, 3);
	tmp.num[1][0] = 1;
	range_mul(l, r, tmp, 1);
	return;
}

} //namespace ST

int pos[N], pre[N];
bool bt[N];
LL ans[Q];

int main()
{
	read(n), read(q);
	for (int i = 1; i <= n; i++)
		read(a[i]);
	for (int i = 1; i <= q; i++)
	{
		int l, r, x, y;
		read(l), read(r), read(x), read(y);
		qrs[y].push_back({l, r, i});
		qrs[x - 1].push_back({l, r, -i});
	}
	DSU::init();
	ST::build(1, 1, n);
	bt[0] = bt[n + 1] = true;
	for (int y = 1; y <= n; y++)
	{
		pre[y] = pos[a[y]], pos[a[y]] = y;
		int py = pre[y];
		
		if (py >= 1) bt[py] = false;
		bt[y] = true;
		
		if (py && !bt[py - 1]) DSU::merge(py - 1, py);
		if (!bt[py + 1]) DSU::merge(py + 1, py);
		
		ST::cover(DSU::getmn(pre[y]), DSU::getmx(py), DSU::getmx(py) + 1);
		ST::cover(y, y, y);
		ST::upd_his(1, n);
		
		for (QueryStruct p : qrs[y])
		{
			LL tmp = ST::his_sum(p.l, p.r, 1);
			if (p.id > 0) ans[p.id] += tmp;
			else ans[-p.id] -= tmp;
		}
	}
	for (int i = 1; i <= q; i++)
		write(ans[i], '\n');
	return 0;
}
```

## 拆矩阵

没错，你又回来了。

而且如果我没猜错的话，你收获了一个 $\color{#00a}\textsf{Time limit exceeded on test 9}$，或者一个 $\color{#00a}\textsf{Memory limit exceeded on test 1}$。

这是因为，这个矩阵线段树自带一个 $3^3=27$ 的时空常数。

那么，**是时候拆矩阵了**。

手算一下可以发现，无论是操作矩阵还是任意时刻的延迟标记矩阵，真正改变的都只有下面标记为“$?$”的数据，其它皆为常数：

$$\begin{bmatrix}
1 & 0 & 0 \\
? & ? & 0 \\
? & ? & 1
\end{bmatrix}$$

所以我们只需要在操作矩阵和标记矩阵中记录这四个数据即可。

做乘法的时候直接手动修改即可：

$$
\begin{bmatrix}
1 & 0 & 0 \\
a & b & 0 \\
c & d & 1
\end{bmatrix}
\times
\begin{bmatrix}
1 & 0 & 0 \\
w & x & 0 \\
y & z & 1
\end{bmatrix}
=
\begin{bmatrix}
1 & 0 & 0 \\
a+bw & bx & 0 \\
c+dw+y & dx+z & 1
\end{bmatrix}
$$

$$
\begin{bmatrix}
a & b & c
\end{bmatrix}
\times
\begin{bmatrix}
1 & 0 & 0 \\
w & x & 0 \\
y & z & 1
\end{bmatrix}
=
\begin{bmatrix}
a+bw+cy & bx+cz & c
\end{bmatrix}
$$

注意**修改时要保证所用数据是修改前的**，否则数据会交叉污染。

这样便可大大优化常数，但还是要开 C++20 或 C++ 23 才能过（CodeForces 的 C++17 这么烂吗？我本地 C++14 都能轻松跑过的 QwQ），各位大佬若有别的高效卡常技巧还望不吝赐教。

> 推荐一篇线段树矩阵乘法文章，讲得很好：**[这里](https://www.cnblogs.com/jeefy/p/17807239.html)**。

```cpp
#include <cstdio>
#include <vector>
using namespace std;

namespace IO{
#ifndef JC_LOCAL
const int SIZE=1<<20; char buf[SIZE],*p1=buf,*p2=buf;
inline char _getchar() {return (p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZE,stdin),p1==p2))?EOF:*p1++;}
#else
inline char _getchar() {return getchar();}
#endif
template<typename TYPE> void read(TYPE &x)
{
	x=0; bool neg=false; char ch=_getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')neg=true;ch=_getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+(ch^'0');ch=_getchar();}
	if(neg){x=-x;} return;
}
template<typename TYPE> void write(TYPE x)
{
	if(!x){putchar('0');return;} if(x<0){putchar('-');x=-x;}
	static int sta[55];int statop=0; while(x){sta[++statop]=x%10;x/=10;}
	while(statop){putchar('0'+sta[statop--]);} return;
}
template<typename TYPE> void write(TYPE x,char ch){write(x);putchar(ch);return;}
} using IO::read; using IO::write;

typedef long long LL;

const int N = 1e6 + 5, Q = 1e6 + 5;
int n, q, a[N];

struct QueryStruct{
	int l, r;
	int id;
};
vector<QueryStruct> qrs[N];

namespace DSU{

int fa[N], mn[N], mx[N];
void init()
{
	for (int i = 1; i <= n; i++)
		fa[i] = mn[i] = mx[i] = i;
	return;
}
int query(int x)
{
	if (fa[x] == x) return x;
	else return fa[x] = query(fa[x]);
}
inline void merge(int x, int y)
{
	x = query(x), y = query(y);
	fa[y] = x;
	mx[x] = max(mx[x], mx[y]);
	mn[x] = min(mn[x], mn[y]);
	return;
}
inline int getmx(int x) {return mx[query(x)];}
inline int getmn(int x) {return mn[query(x)];}

} //namespace DSU

namespace ST{

struct Dat{
	LL o11, o12, o13; //history, sum, len
	Dat operator + (const Dat &t) const
	{
		return {
			o11 + t.o11,
			o12 + t.o12,
			o13 + t.o13
		};
	}
};
struct Lzy{
	LL o21, o22, o31, o32;
};
struct SegTree{
	int l, r;
	Dat dat;
	Lzy lzy;
	inline int mid() {return l + r >> 1;}
	void operator *= (const Lzy &v)
	{
		dat.o11 += v.o21 * dat.o12 + v.o31 * dat.o13; // use dat.o12, dat.o13
		dat.o12 = v.o22 * dat.o12 + v.o32 * dat.o13; // use dat.o13
		
		lzy.o21 += v.o21 * lzy.o22; // use lzy.o22
		lzy.o22 = v.o22 * lzy.o22;
		lzy.o31 += v.o21 * lzy.o32 + v.o31; //use lzy.o32
		lzy.o32 = v.o22 * lzy.o32 + v.o32;
		return;
	}
} tr[N << 2];

inline void pushup(int p)
{
	tr[p].dat = tr[p << 1].dat + tr[p << 1 | 1].dat;
	return;
}
inline void pushdown(int p)
{
	tr[p << 1] *= tr[p].lzy;
	tr[p << 1 | 1] *= tr[p].lzy;
	tr[p].lzy = {0, 1, 0, 0};
	return;
}

void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	tr[p].lzy = {0, 1, 0, 0};
	if(l == r)
	{
		tr[p].dat.o11 = tr[p].dat.o12 = 0;
		tr[p].dat.o13 = 1;
		return;
	}
	int mid = tr[p].mid();
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	pushup(p);
	return;
}

void range_mul(int l, int r, const Lzy &v, int p)
{
	if (l <= tr[p].l && tr[p].r <= r)
	{
		tr[p] *= v;
		return;
	}
	pushdown(p);
	int mid = tr[p].mid();
	if (l <= mid) range_mul(l, r, v, p << 1);
	if (r > mid) range_mul(l, r, v, p << 1 | 1);
	pushup(p);
	return;
}

LL his_sum(int l, int r, int p)
{
	if (l <= tr[p].l && tr[p].r <= r)
		return tr[p].dat.o11;
	pushdown(p);
	int mid = tr[p].mid();
	LL res = 0;
	if (l <= mid) res += his_sum(l, r, p << 1);
	if (r > mid) res += his_sum(l, r, p << 1 | 1);
	return res;
}

inline void cover(int l, int r, int v)
{
	l = max(l, 1), r = min(r, n);
	if (l > r) return;
	v = min(v, n);
	range_mul(l, r, {0, 0, 0, v}, 1);
	return;
}

inline void upd_his(int l, int r)
{
	range_mul(l, r, {1, 1, 0, 0}, 1);
	return;
}

} //namespace ST

int pos[N], pre[N];
bool bt[N];
LL ans[Q];

int main()
{
	read(n), read(q);
	for (int i = 1; i <= n; i++)
		read(a[i]);
	for (int i = 1; i <= q; i++)
	{
		int l, r, x, y;
		read(l), read(r), read(x), read(y);
		qrs[y].push_back({l, r, i});
		qrs[x - 1].push_back({l, r, -i});
	}
	DSU::init();
	ST::build(1, 1, n);
	bt[0] = bt[n + 1] = true;
	for (int y = 1; y <= n; y++)
	{
		pre[y] = pos[a[y]], pos[a[y]] = y;
		int py = pre[y];
		
		if (py >= 1) bt[py] = false;
		bt[y] = true;
		
		if (py && !bt[py - 1]) DSU::merge(py - 1, py);
		if (!bt[py + 1]) DSU::merge(py + 1, py);
		
		ST::cover(DSU::getmn(pre[y]), DSU::getmx(py), DSU::getmx(py) + 1);
		ST::cover(y, y, y);
		ST::upd_his(1, n);
		
		for (QueryStruct p : qrs[y])
		{
			LL tmp = ST::his_sum(p.l, p.r, 1);
			if (p.id > 0) ans[p.id] += tmp;
			else ans[-p.id] -= tmp;
		}
	}
	for (int i = 1; i <= q; i++)
		write(ans[i], '\n');
	return 0;
}
```

## 后记

本文写作时，笔者正在练习双拼输入法，因不熟悉打字节奏的原因，文风可能略显奇怪，请读者见谅。

---

## 作者：modfisher (赞：0)

## 思路
看到计算多个区间的函数和，立马联想到扫描线加上历史和线段树。这点大部分题解都讲过了。

但是，我要提出一种更方便的写法。

正常来说，我们都是从前往后地扫描，这也是大部分这类题解的做法。不过这题，从后往前扫描似乎更简单些。

考虑现在已知 $g(i+1,i+1),g(i+1,i+2),\dots,g(i+1,n)$，在前面加入一个 $a_i$，这些值会产生什么变化呢？

让我们先来分析一下这个函数 $g(i,j)$。观察其定义：

> - 当 $i\le j$ 时，$g(i,j)$ 是满足 $\{a_p:i\le p\le j\}\subseteq\{a_q:x\le q\le j\}$ 的最大整数 $x$。
> - 否则 $g(i,j)=0$。

实际上，由于 $x=i$ 时满足要求，故 $g(i,j)\ge i$，则必有 $\{a_p:i\le p\le j\}\supseteq\{a_q:x\le q\le j\}$，结合两个条件可知 $\{a_p:i\le p\le j\}=\{a_q:x\le q\le j\}$，即两个区间值域相同。

由此可知，若 $g(i,j)>i$，则 $[i,g(i,j)-1]$ 中出现过的值在 $[g(i,j),j]$ 中必定也出现过，且 $a_{g(i,j)}$ 在 $[g(i,j)+1,j]$ 中没有出现过。

回到之前的问题，在前面加入一个 $a_i$，之会有什么变化呢？分两种情况讨论：

- $a_i$ 在 $[i+1,n]$ 中没有出现过。则对于任意 $i<j\le n$，不存在 $x>i$，满足 $[i,x-1]$ 中的所有值都在 $[x,j]$ 中出现过（因为 $a_i$ 自己就没有出现过）,所以，$g(i,i)=g(i,i+1)=\dots=g(i,n)=i$。

- $a_i$ 在 $[i+1,n]$ 中出现过。记其上一次出现的位置为 $k$，对于任意 $i<j<k$，也不存在 $x>i$，满足 $[i,x-1]$ 中的所有值都在 $[x,j]$ 中出现过；但是，对于任意 $k\le j\le n$，$[k,j]$ 中一定包含至少一个 $a_i$，所以 $a_i$ 的加入对其没有影响。于是，$g(i,i)=g(i,i+1)=\dots=g(i,k-1)=i$，而对于任意 $k\le j\le n$，有 $g(i,j)=g(i+1,j)$。

所以值的更新变得异常简单：记录下 $pre_i$ 表示数值 $i$ 上一次出现的位置（为 $0$ 则未出现过），扫描到第 $i$ 位时，若 $pre_{a_i}=0$，则将线段树中区间 $[i,n]$ 全部覆盖为 $i$；否则，将区间 $[i,pre_{a_i}-1]$ 全部覆盖为 $i$。随后更新 $pre_{a_i}$ 即可。

至于其他的，就和别的题解差不多了。将询问拆成 $(x,y,l)$ 和 $(x,y,r+1)$（这里与正着扫略有不同），用历史和线段树记录每一位的历史和，扫到某个三元组 $(x,y,p)$ 时，查询 $[x,y]$ 的历史和，然后贡献到答案中去。

注意区间覆盖的历史和线段树与区间加的略有不同，请仔细思考标记如何下传。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn = 1e6 + 5;

namespace seg{
#define l(x) (x << 1)
#define r(x) (x << 1 | 1)
ll sum[maxn << 2], _sum[maxn << 2], len[maxn << 2];
ll tag[maxn << 2], _tag[maxn << 2], rec[maxn << 2];
void up(int x){
	sum[x] = sum[l(x)] + sum[r(x)], _sum[x] = _sum[l(x)] + _sum[r(x)];
}
void down(int x){
	_sum[l(x)] += sum[l(x)] * rec[x] + len[l(x)] * _tag[x], _sum[r(x)] += sum[r(x)] * rec[x] + len[r(x)] * _tag[x];
	_tag[l(x)] += tag[l(x)] * rec[x] + _tag[x], _tag[r(x)] += tag[r(x)] * rec[x] + _tag[x];
	if(!tag[l(x)]) rec[l(x)] += rec[x];
	if(!tag[r(x)]) rec[r(x)] += rec[x];
	if(tag[x]){
		sum[l(x)] = len[l(x)] * tag[x], sum[r(x)] = len[r(x)] * tag[x];
		tag[l(x)] = tag[x], tag[r(x)] = tag[x];
	}
	tag[x] = _tag[x] = rec[x] = 0;
}
void build(int x, int l, int r){
	len[x] = r - l + 1;
	if(l == r) return;
	int mid = l + r >> 1;
	build(l(x), l, mid), build(r(x), mid + 1, r);
}
void cover(int x, int l, int r, int ql, int qr, ll k){
	if(ql <= l && r <= qr){
		sum[x] = len[x] * k, tag[x] = k;
		return;
	}
	down(x);
	int mid = l + r >> 1;
	if(ql <= mid) cover(l(x), l, mid, ql, qr, k);
	if(qr > mid) cover(r(x), mid + 1, r, ql, qr, k);
	up(x);
}
void record(int x, int l, int r, int ql, int qr){
	if(ql <= l && r <= qr){
		_sum[x] += sum[x], _tag[x] += tag[x];
		if(!tag[x]) rec[x] ++;
		return;
	}
	down(x);
	int mid = l + r >> 1;
	if(ql <= mid) record(l(x), l, mid, ql, qr);
	if(qr > mid) record(r(x), mid + 1, r, ql, qr);
	up(x);
}
ll query(int x, int l, int r, int ql, int qr){
	if(ql <= l && r <= qr) return _sum[x];
	down(x);
	int mid = l + r >> 1;
	ll res = 0;
	if(ql <= mid) res += query(l(x), l, mid, ql, qr);
	if(qr > mid) res += query(r(x), mid + 1, r, ql, qr);
	return res;
}}

struct node{
	int l, r, p, id, tp;
}qs[maxn << 1];

int a[maxn], pre[maxn];
ll ans[maxn];

bool cmp(node x, node y){
	return x.p > y.p;
}

int main(){
	int n, q;
	scanf("%d %d", &n, &q);
	for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
	for(int i = 1; i <= q; i ++){
		int l, r, x, y;
		scanf("%d %d %d %d", &l, &r, &x, &y);
		qs[i * 2 - 1] = (node){x, y, l, i, 1}, qs[i * 2] = (node){x, y, r + 1, i, 0};
	}
	seg::build(1, 1, n);
	sort(qs + 1, qs + q * 2 + 1, cmp);
	int k = 1;
	while(qs[k].p > n) k ++;
	for(int i = n; i >= 1; i --){
		if(pre[a[i]]) seg::cover(1, 1, n, i, pre[a[i]] - 1, i);
		else seg::cover(1, 1, n, i, n, i);
		seg::record(1, 1, n, i, n);
		pre[a[i]] = i;
		while(qs[k].p == i){
			if(qs[k].r < i){
				k ++;
				continue;
			}
			ll res = seg::query(1, 1, n, max(qs[k].l, i), qs[k].r);
			if(qs[k].tp) ans[qs[k].id] += res;
			else ans[qs[k].id] -= res;
			k ++;
		}
	}
	for(int i = 1; i <= q; i ++) printf("%lld\n", ans[i]);
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

题意：

已知一个由 $n$ 个整数组成的数组 $a$，索引从 $1$ 开始，$1≤a_i≤n$。
定义 $g(i,j)$ 如下：$g(i,j)$ 是满足$\left\{ a_p:i≤ p≤j\right\}=\left\{ a_q:x≤ q≤j\right\}$，而 $i≤j$ 的最大整数 $x$；并且 $g(i,j)=0$，而 $i>j$。

有 $q$ 个查询。对于每个查询，你得到四个整数 $l,r,x,y$，你需要计算 $\sum_{i=l}^{r}\sum_{j=x}^{y}g(i,j)$。
可以结合以下代码理解：

具有```TAG```的线段树和前缀和：
```cpp
#include<bits/stdc++.h>
#define fup(i,l,r) for(int i=l;i<=r;i++)
#define fdn(i,l,r) for(int i=r;i>=l;i--)
#define ll long long
#define L (k<<1)
#define R (L|1)
#define mid (l+r>>1)

#define N 1000010
using namespace std;


#define pll pair<ll,ll>

int n,q,x,y,l,r,a[N],lst[N],pre[N],len[N<<2];
ll ans[N];
pll tag[N<<2],f[N<<2];
set<int>S;
struct Node{
	int id,l,r,p;
};
vector<Node>v[N];
// 节点乘以一个整数
pll mul(pll x,int y){
	return make_pair(x.first  *y,x.second*y);
}
// 两节点加法
pll add(pll x,pll y){
	return make_pair(x.first+y.first,x.second+y.second);
}
// 更新一个节点，设置tag
void upd(int k,pll x){
	tag[k]=add(tag[k],x),f[k]=add(f[k],mul(x,len[k]));
}
// 利用tag向下更新，tag清0
void down(int k){
	if ((tag[k].first)||(tag[k].second))
		upd(L,tag[k]),upd(R,tag[k]),tag[k]=make_pair(0,0);
}
void build(int k,int l,int r){
	len[k]=r-l+1;
	if (l==r){
		f[k]=make_pair(a[l],0);
		return;
	}
	build(L,l,mid),build(R,mid+1,r);
	f[k]=add(f[L],f[R]);
}
// update  (1,1,n,             i,   i,   make_pair(-i,(ll)i*(n-i+1)));
void update(int k,int l,int r,int x,int y,pll z){
	if ((l>y)||(x>r))return;
	if ((x<=l)&&(r<=y)){upd(k,z);return;}
	down(k);
	update(L,l,mid,x,y,z),update(R,mid+1,r,x,y,z);
	f[k]=add(f[L],f[R]);
}
pll query(int k,int l,int r,int x,int y){
	if ((l>y)||(x>r))return make_pair(0,0);
	if ((x<=l)&&(r<=y))return f[k];
	down(k);
	return add(query(L,l,mid,x,y),query(R,mid+1,r,x,y));
}

void prin(int k,int l,int r){
	cout<<""<<k<<"=k, l= "<<l<<", r="<<r<<", "<<f[k].first<<", "<<f[k].second<<endl;
	if (l==r)
		return;
	prin(L,l,mid),prin(R,mid+1,r);
}

int main(){
		FILE *fi;
	freopen_s(&fi,"CF1824Din.txt","r",stdin);
	cin>>n,cin>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		pre[i]=lst[a[i]],lst[a[i]]=i;
	}

	for(int i=1;i<=n;i++)
		cout<<"i="<<i<<",  pre[i]="<<pre[i]<<", lst[a[i]]="<<lst[a[i]]<<endl;
	for(int i=1;i<=q;i++){
		cin>>l ,cin>>r ,cin>>x ,cin>>y ;
		// int id,l,r,p;
		Node tm;
		tm.id=i; tm.l=l;
		tm.r=r; tm.p=1;
		v[x].push_back(tm);
		tm.p=-1;// 前缀和，用作减法
		v[y+1].push_back(tm);
	}
	S.insert(0);
	for(int i=1;i<=n;i++)
		if (lst[i])S.insert(lst[i]);
	for(int i=n;i;i--)a[i]=(S.find(i)!=S.end() ? i : a[i+1]);
	for(int i=1;i<=n;i++)
		// a[i] 为g(i,n)的值
	cout<<"a[i]=  "<<a[i]<<endl;

	build(1,1,n); prin(1,1,n);
	for(int i=n;i;i--){
		for(Node j:v[i]){
			pll o=query(1,1,n,j.l,j.r);
			ans[j.id]+=(o.first*(n-i+1)+o.second)*j.p;
			cout<<o.first<<"=o.first, "<<o.second<<"=o.second, "<<j.id<<"=j.id, ans[j.id]="<<ans[j.id]<<", j.p="<<j.p<<", j.l="<<j.l<<", j.r="<<j.r<<",i="<<i<<endl;
			prin(1,1,n);
		}
		if (pre[i]){
			S.insert(pre[i]);
			int x=(*--S.find(pre[i])),y=(*S.upper_bound(pre[i]));
			update(1,1,n,x+1,pre[i],make_pair(pre[i]-y,(ll)(y-pre[i])*(n-i+1)));
			cout<<"i="<<i<<", pre[i]="<<pre[i]<<",x="<<x<<",y="<<y<<endl;

		}
		// g(i，j)是满足{ap:i≤p≤j}={aq:x≤q≤j}而i≤j的最大整数x；
		// j 小于当前的i时，x当然为0
		update(1,1,n,i,i,make_pair(-i,(ll)i*(n-i+1)));
		cout<<"i="<<i<<endl;
		prin(1,1,n);
	}

	for(int i=1;i<=q;i++)cout<<ans[i]<<endl;
	return 0;
}
``````

---

## 作者：forest114514 (赞：0)

直接维护版本和就行了，所以就是套路题啊，这种题的套路之外的难点就是如何更新扫描线时的每个以 $r$ 为右端点的区间的答案。

我们扫描线，维护每个颜色最右端的一个出现位置 $cur$，一个区间的答案就是区间内最左端的 $cur$，所以每一个 以 $cur$ 为答案的都是一段连续的区间，考虑用 $set$ 维护颜色段，每次删除一个元素并且添加一个元素，同时修改一段区间的端点下标即可，可以转化为区间加。

还是维护历史版本和，这很简单了，维护向量 $\begin{bmatrix}pos&sum&len\end{bmatrix}$，表示现在的颜色段右端点，历史右端点的版本和以及区间长，修改乘以 $\begin{bmatrix}1&0&0\\0&1&0\\k&0&1\end{bmatrix}$，更新版本和乘以 $\begin{bmatrix}1&1&0\\0&1&0\\0&0&1\end{bmatrix}$，还是找出有用的地方，维护对应的位置即可。

打表一下容易发现只有三个有效的位置，我们只用维护三个位置。

矩阵乘法：
$$
\begin{bmatrix}1&a&0\\0&1&0\\b&c&1\end{bmatrix}\times \begin{bmatrix}1&A&0\\0&1&0\\B&C&1\end{bmatrix}=\begin{bmatrix}1&A+a&0\\0&1&0\\b+B&Ab+c+C&1\end{bmatrix}
$$
向量乘矩阵：

$\begin{bmatrix}pos&sum&len\end{bmatrix}\times\begin{bmatrix}1&A&0\\0&1&0\\B&C&1\end{bmatrix}=\begin{bmatrix}pos+B\times len&A\times pos+sum+C\times len&len\end{bmatrix}$


注意到时间维也是可以差分的，询问可以处理一下变成差分的形式，就很简单了。

常数巨大的代码：
```cpp
const int N=2e6+100;
int n,q,col[N],pre[N];
set<int> cur; 
LL ans[N];
struct QUE{
	int l,r,id,op;
};
vector<QUE> qu[N];
namespace DS{
	struct Matrix{
		LL a,b,c;
		Matrix(LL A=0,LL B=0,LL C=0){
			a=A,b=B,c=C;
		}
		void clear(){a=0,b=0,c=0;}
		bool clean(){
			return a==0&&b==0&&c==0;
		} 
	};
	struct Vec{
		LL pos,sum,len;
		Vec(LL a=0,LL b=0,LL c=0){pos=a,sum=b,len=c;}
	};
	Matrix operator *(const Matrix X,const Matrix Y){
		return Matrix(X.a+Y.a,X.b+Y.b,X.c+Y.c+X.b*Y.a);
	}
	Vec operator *(const Vec X,const Matrix Y){
		return Vec(X.pos+Y.b*X.len,Y.a*X.pos+X.sum+Y.c*X.len,X.len);
	}
	Vec operator +(const Vec X,const Vec Y){
		return Vec(X.pos+Y.pos,X.sum+Y.sum,X.len+Y.len);
	}
	struct SGT{
		Vec mx;
		Matrix tag;
	}tr[N<<2];
	void pushup(int x){
		tr[x].mx=tr[ls(x)].mx+tr[rs(x)].mx;
	}
	void mdf(int x,Matrix T){tr[x].mx=tr[x].mx*T,tr[x].tag=tr[x].tag*T;}
	void pushdown(int x){
		if(tr[x].tag.clean()) return;
		mdf(ls(x),tr[x].tag);
		mdf(rs(x),tr[x].tag);
		tr[x].tag.clear();
	}
	void build(int x,int l,int r){
		tr[x].mx=Vec(0,0,r-l+1);
		if(l==r)return;
		int mid=l+r>>1;
		build(ls(x),l,mid);
		build(rs(x),mid+1,r);
	}
	void update(int x,int l,int r,int L,int R,const Matrix &v){
		if(L<=l&&r<=R){
			tr[x].mx=tr[x].mx*v;
			tr[x].tag=tr[x].tag*v;
			return;
		}	
		pushdown(x);
		int mid=l+r>>1;
		if(mid>=L) update(ls(x),l,mid,L,R,v);
		if(mid<R) update(rs(x),mid+1,r,L,R,v);
		pushup(x);
	}
	LL query(int x,int l,int r,int L,int R){
		if(L<=l&&r<=R) return tr[x].mx.sum;
		pushdown(x);
		int mid=l+r>>1;
		LL res=0;
		if(mid>=L) res=query(ls(x),l,mid,L,R);
		if(mid<R) res+=query(rs(x),mid+1,r,L,R);
		return res;
	}
}
using namespace DS;
Matrix ADD(int x){return Matrix(0,x,0);}
Matrix upd(){return Matrix(1,0,0);}
signed main(){
	read(n,q);
	rep(i,1,n) read(col[i]);
	rep(i,1,q){
		int l,r,x,y;
		read(l,r,x,y);
		qu[y].pb((QUE){l,r,i,1});
		qu[x-1].pb((QUE){l,r,i,-1});
	}
	build(1,1,n);
	cur.insert(0);
	rep(i,1,n){
		auto lst=(*--cur.end());
		update(1,1,n,lst+1,i,ADD(i));
		cur.insert(i);
		if(pre[col[i]]){
			auto nxt=(*cur.upper_bound(pre[col[i]]));
			auto lst=(*--cur.lower_bound(pre[col[i]]));
			update(1,1,n,lst+1,pre[col[i]],ADD(nxt-pre[col[i]]));
			cur.erase(pre[col[i]]);
		}
		pre[col[i]]=i;
		update(1,1,n,1,n,upd());
		for(auto que:qu[i]){
			ans[que.id]+=1ll*que.op*query(1,1,n,que.l,que.r);
		}
	}
	rep(i,1,q) write(ans[i],'\n');
	return 0;
}

```

---

