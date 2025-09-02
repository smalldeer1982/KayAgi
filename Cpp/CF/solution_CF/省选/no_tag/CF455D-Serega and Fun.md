# Serega and Fun

## 题目描述

Serega loves fun. However, everyone has fun in the unique manner. Serega has fun by solving query problems. One day Fedor came up with such a problem.

You are given an array $ a $ consisting of $ n $ positive integers and queries to it. The queries can be of two types:

1. Make a unit cyclic shift to the right on the segment from $ l $ to $ r $ (both borders inclusive). That is rearrange elements of the array in the following manner: $ a[l],a[l+1],...,a[r-1],a[r]→a[r],a[l],a[l+1],...,a[r-1]. $
2. Count how many numbers equal to $ k $ are on the segment from $ l $ to $ r $ (both borders inclusive).

Fedor hurried to see Serega enjoy the problem and Serega solved it really quickly. Let's see, can you solve it?

## 样例 #1

### 输入

```
7
6 6 2 7 4 2 5
7
1 3 6
2 2 4 2
2 2 4 7
2 2 2 5
1 2 6
1 1 4
2 1 7 3
```

### 输出

```
2
1
0
0
```

## 样例 #2

### 输入

```
8
8 4 2 2 7 7 8 8
8
1 8 8
2 8 1 7
1 8 1
1 7 3
2 8 8 3
1 1 4
1 2 7
1 4 5
```

### 输出

```
2
0
```

# 题解

## 作者：Rubyonly (赞：27)

看到楼上有平衡树做法，可惜我平衡树不会几个，用得也不熟 ![](https://cdn.luogu.com.cn/upload/pic/62227.png)

其实用分块套一下还是比较好写的

对于每个块维护一个双端队列，用来进行支持右移操作

同时维护一个桶，记录一下每个块内不同值的个数，便于查询

然后直接操作就行了，细节也不算很多，注意特殊处理 $l$ 和 $r$ 都在同一个块内时的情况，而且双端队列可以像 $vector$ 一样进行下标查询，更加方便了我们的操作

```c++
#include <cstdio>
#include <algorithm>
#include <deque>
#include <cmath>

#define rint register int 

using namespace std;

const int maxn = 1e5 + 50;

inline int read () {
	rint x = 0, w = 1;
	char ch = getchar ();
	for (; ch < '0' || ch > '9'; ch = getchar ()) if (ch == '-') w = -1;
	for (; ch >= '0' && ch <= '9'; ch = getchar ()) x = x * 10 + ch - '0';
	return x * w;
}

int n, m, S, a[maxn], st[maxn];
int bel[maxn], L[maxn], R[maxn], buc[320][maxn];
deque <int> q[320];

inline void Init () {
	S = sqrt (n);
	for (rint i = 1; i <= n; i ++) a[i] = read();
	for (rint i = 1; i <= n; i ++) {
		bel[i] = (i - 1) / S + 1, R[bel[i]] = i;
		buc[bel[i]][a[i]] ++, q[bel[i]].push_back (a[i]);
		if (! L[bel[i]]) L[bel[i]] = i;
	}
}

inline void Modify (rint l, rint r, rint top = 0) {
	if (bel[l] == bel[r]) {
		rint now = bel[l];
		l -= L[now], r -= L[now], st[++ top] = q[now][r];
		for (rint i = l; i < r; i ++) st[++ top] = q[now][i];
		for (rint i = r; i >= l; i --) q[now][i] = st[top --];
		return;
	}
	rint cnt1 = R[bel[l]] - l + 1, cnt2 = r - L[bel[r]] + 1;
	while (cnt1 --) {
		rint x = q[bel[l]].back ();
		st[++ top] = x, buc[bel[l]][x] --, q[bel[l]].pop_back (); 
	}
	st[++ top] = q[bel[r]][cnt2 - 1];
	while (top > 1) {
		rint x = st[top];
		q[bel[l]].push_back (x), buc[bel[l]][x] ++, top --; 
	}
	for (rint i = bel[l] + 1; i <= bel[r] - 1; i ++) {
		rint x = st[top];
		q[i].push_front (x), buc[i][x] ++, top --;
		rint y = q[i].back ();
		st[++ top] = y, buc[i][y] --, q[i].pop_back();
	}
	while (cnt2 --) {
		rint x = q[bel[r]].front ();
		st[++ top] = x, buc[bel[r]][x] --, q[bel[r]].pop_front ();
	}
	top --;
	while (top > 0) {
		rint x = st[top];
		q[bel[r]].push_front (x), buc[bel[r]][x] ++, top --;
	}
}

inline int Query (rint l, rint r, rint k, rint ans = 0) {
	if (bel[l] == bel[r]) {
		rint now = bel[l];
		l -= L[now], r -= L[now];
		for (rint i = l; i <= r; i ++) ans += q[now][i] == k;	
		return ans;
	}
	rint cnt1 = R[bel[l]] - l + 1, cnt2 = r - L[bel[r]] + 1;
	for (rint i = q[bel[l]].size () - cnt1; i <= q[bel[l]].size () - 1; i ++) ans += q[bel[l]][i] == k;
	for (rint i = 0; i <= cnt2 - 1; i ++) ans += q[bel[r]][i] == k;	
	for (rint i = bel[l] + 1; i <= bel[r] - 1; i ++) ans += buc[i][k];
	return ans;
}

int main () {
	n = read(), Init (), m = read();
	rint last = 0;
	while (m --) {
		rint opt = read(), l = (read() + last - 1) % n + 1, r = (read() + last - 1) % n + 1, k;
		if (l > r) swap (l, r);
		if (opt == 1) Modify (l, r);
		else k = (read() + last - 1) % n + 1, printf ("%d\n", last = Query (l, r, k));
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：8)

可以用分块做，块的大小直接取sqrt(n)就行了，c(i,j)表示在第i个块里j的个数，对于每个块，开一个deque记录块里的元素，每次修改时，把最后一个元素，放到起始位置，对于包含的块，把最后一个元素放到下一个块的开头，查询就把完全包含的块加上，对于两边暴力跑一下即可。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005,M=355;
deque<int>a[N];
int n,m,s,q,z,L,R,k,l,r,x,ans,c[M][N];
void deal(int &x){x=(x+ans-1)%n+1;} 
int main()
{
	scanf("%d",&n);
	s=int(sqrt(n)),m=n/s+1;
	for(int i=0;i<n;i++)
	{
		scanf("%d",&x);
		a[i/s].push_back(x);
		c[i/s][x]++;
	}
	scanf("%d",&q);
	while(q--)
	{
		scanf("%d%d%d",&z,&L,&R);
		deal(L),deal(R);
		if(L>R) swap(L,R);
		L--,l=L/s,r=R/s;
		if(z==2)
		{
			scanf("%d",&k);
			deal(k);
			ans=0;
			if(l==r)
				for(int i=L%s;i<R%s;i++)
					ans+=a[l][i]==k;
			else
			{
				for(int i=l+1;i<r;i++)
					ans+=c[i][k];
				for(int i=L%s;i<a[i].size();i++)
					ans+=a[l][i]==k;
				for(int i=0;i<R%s;i++)
					ans+=a[r][i]==k;
			}
			printf("%d\n",ans);
		}
		else
		{
			if(l==r)
			{
				R=R%s-1,x=a[r][R];
				a[r].erase(a[r].begin()+R);
				a[l].insert(a[l].begin()+L%s,x);
			}
			else
			{
				for(int i=l;i<r;)
				{
					x=a[i].back(),a[i].pop_back(),c[i][x]--,i++;
					a[i].push_front(x),c[i][x]++;	
				} 
				R%=s,x=a[r][R];
				a[r].erase(a[r].begin()+R),c[r][x]--;
				a[l].insert(a[l].begin()+L%s,x),c[l][x]++;
			}
		}
	}
	return 0;
}

```


---

## 作者：yzy1 (赞：7)

考虑分块，每 $\sqrt n$ 个元素分成一块，每个块内维护 $cnt(b,i)$ 表示 $i$ 这个数在 $b$ 号块中出现了几次，维护 $dq(b)$ 用一个 `deque` 表示出 $b$ 号块内的所有元素。

对于 $1$ 操作，如果 $l$ 与 $r$ 在同一个块里，直接暴力去做即可。如果不在，则将最后一个元素 insert 进第一个元素所在的块中，接着 $(bl_l,bl_r]$ 之间的所有块，把上一个块的最后一个元素移到当前块中，并更新 $cnt$ 值。以保证块内元素数仍为 $\sqrt n$。

对于 $2$ 操作，零散块暴力查询，整块直接读 $cnt$ 值相加即可。

**另外需要特殊注意的是：** 如果你 RE on test 9，如果你写了类似

```cpp
dq[bl[r]].erase(dq[bl[r]].begin() + r - lbl[r]);
```

这种的语法，它会因为 `dq[bl[r]].begin() + r` 跑到了 deque 外面而 RE。

改成这样即可 AC：

```cpp
dq[bl[r]].erase(dq[bl[r]].begin() + (r - lbl[r]));
```

### Code

```cpp
constexpr int N = 1e5 + 9;
constexpr int B = 333;

int n, a[N], cnt[B][N], bl[N], lbl[N], rbl[N], sz;
deque<int> dq[B];

void Init() {
  sz = max(3, (int)sqrt(n));
  re (i, n)
    bl[i] = (i - 1) / sz + 1, lbl[i] = (bl[i] - 1) * sz + 1, rbl[i] = min(n, bl[i] * sz);
  ste(x, 1, n, sz) {
    rep (i, lbl[x], rbl[x])
      dq[bl[x]].push_back(a[i]), ++cnt[bl[x]][a[i]];
  }
}

void Mov(int l, int r) {
  if (bl[l] == bl[r]) {
    int b = bl[l];
    int x = dq[b][r - lbl[l]];
    dq[b].erase(dq[b].begin() + (r - lbl[l]));
    dq[b].insert(dq[b].begin() + (l - lbl[l]), x);
    return;
  }
  dq[bl[l]].insert(dq[bl[l]].begin() + (l - lbl[l]), dq[bl[r]][r - lbl[r]]);
  ++cnt[bl[l]][dq[bl[r]][r - lbl[r]]];
  --cnt[bl[r]][dq[bl[r]][r - lbl[r]]];
  dq[bl[r]].erase(dq[bl[r]].begin() + (r - lbl[r]));
  rep (b, bl[l] + 1, bl[r]) {
    int t = dq[b - 1].back();
    dq[b].push_front(t);
    ++cnt[b][t];
    dq[b - 1].pop_back();
    --cnt[b - 1][t];
  }
}

int Ask(int l, int r, int k) {
  int res = 0;
  if (bl[l] == bl[r]) {
    int b = bl[l];
    rep (i, l, r) {
      if (dq[b][i - lbl[l]] == k) ++res;
    }
    return res;
  }
  res += Ask(l, rbl[l], k);
  rep (b, bl[l] + 1, bl[r] - 1)
    res += cnt[b][k];
  res += Ask(lbl[r], r, k);
  return res;
}

signed main() {
  in(n)(a, n);
  Init();
  int lastans = 0;
  re (_, in()) {
    int op = in(), l = (in() + lastans - 1) % n + 1, r = (in() + lastans - 1) % n + 1;
    if (l > r) swap(l, r);
    if (op == 1)
      Mov(l, r);
    else {
      int k = (in() + lastans - 1) % n + 1;
      lastans = Ask(l, r, k);
      out(lastans)('\n');
    }
  }
  return 0;
}
```



---

## 作者：Clover_BY (赞：2)

# [CF455D  Serega and Fun](https://www.luogu.com.cn/problem/CF455D)  
提供一种比较另类的分块做法，没有使用双端队列实现。
## 题目描述
给定一个长度为 $n$ 的序列 $a$，你需要支持 $m$ 次以下操作：

1. 将区间 $[l, r]$ 整体右移一位。特别地，$r$ 位置上的元素需要移到 $l$ 位置上。  
2. 查询区间 $[l, r]$ 中 $x$ 出现的次数。  
  
数据范围：$n, m \leq 10^5,1 \leq a_i \leq n$。

## 题目分析
看到值域与 $n$ 同阶并且查询操作用一般数据结构不好实现，很容易会想到分块。  
对于查询操作，沿用正常的分块操作，以 `cnt` 数组记录每块中每个数出现的次数（空间足够），遍历各块统计答案即可。这个数组的统计独立于下面所述的操作。

我们重点考虑一下这个修改操作如何实现。  
~~由于本人脑子不大灵光~~， 我并没有考虑使用双端队列暴力改变整个块的形态，而是想了想能不能给修改的整块打上标记。  
结论是可行。不过代码复杂度可能较高。

我们使用 `vector` 来存储这些标记，意为“在当前块之前插入这个数”。这个 `vector` 并不负责删除元素，只负责处理向块中增加元素的过程。  
不过这样做有一个问题：既然没有改变块的形态，那我们在操作时无法马上找到处于上一块末尾位置的元素，这使得打标记存在障碍。我的处理方法是另开一个名为 `pos` 的数组，记录当前块末尾元素的位置，每打一个标记就把这个位置向前挪一位（因为当前这位已经移到下一块中了）。  
于是乎又出现一个问题：当某个块被打上的标记数超出块长时 `pos` 会越出块本身的左右界限。为避免这个问题，标记数量逼近块长时必须马上下放。

当修改散块时，`vector` 中的标记需要全部下放并清空。对于清空，设块边界为 $st$ 和 $ed$，标记数为 $tagnum$，则：

1. 对于块内 $[st + tagnum, ed]$ 区间的所有元素 $a_i$，将其赋为 $a_{i-tagnum}$。
2. 对于块内 $[st, st + tagnum - 1]$ 区间内的所有元素 $a_i$，将其倒序赋为 `vector` 中存储的各个元素。

之后暴力模拟即可。  
修改整块时，借助 `pos` 数组找到上一个块末尾元素的位置并作为标记插入 `vector` 即可。  
注意左右边界的处理。另外，  
**注意：上述修改、下放操作必须从右向左倒序处理。**

码量和常数都较大，如愿尝试此方法请保持细心和耐心。

## Code
```cpp
#include <cstdio>
#include <cctype>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

inline void qswap(int &a, int &b)
{
	int t = a; a = b;
	b = t; return ;
}

inline int read()
{
	int x = 0; char c;
	while(!isdigit(c = getchar()));
	do{
		x = (x << 1) + (x << 3) + (c ^ 48);
	}while(isdigit(c = getchar()));
	return x;
}

int top = 0, stk[20];
inline void write(int x)
{
	do{
		stk[++top] = x % 10;
		x /= 10;
	}while(x);
	for(register int i = top; i; --i)
		putchar(stk[i] | 48);
	putchar('\n'); top = 0;
	return ;
}

int n, m, ope, l, r, x;
int sq, siz, bl, br, ans = 0;
int sz[100010], bel[100010];
int st[345], ed[345], tagnum[345], posed[345];
int cnt[345][100010];
vector<int> tag[345];

inline void preblocks()
{
	sq = sqrt(n); siz = n / sq;
	for(register int i = 1; i < sq; ++i)
	{
		st[i] = ed[i - 1] + 1;
		posed[i] = ed[i] = st[i] + siz - 1;
		for(register int j = st[i]; j <= ed[i]; ++j)
		{
			sz[j] = read();
			bel[j] = i;
			++cnt[i][sz[j]];
		}
	}
	st[sq] = ed[sq - 1] + 1;
	posed[sq] = ed[sq] = n;
	for(register int i = st[sq]; i <= n; ++i)
	{
		sz[i] = read();
		bel[i] = sq;
		++cnt[sq][sz[i]];
	}
	return ;
}

inline void rebuild(int b)
{
	if(tag[b].empty()) return ;
	int rb = st[b] + tagnum[b] - 1;
	for(register int i = ed[b]; i > rb; --i)
		sz[i] = sz[i - tagnum[b]];
	for(register int i = st[b]; i <= rb; ++i)
		sz[i] = tag[b][tagnum[b] - i + st[b] - 1];
	tag[b].clear(); tagnum[b] = 0;
	posed[b] = ed[b]; return ;
}

inline void modify(int l, int r)
{
	bl = bel[l]; br = bel[r];
	if(bl == br)
	{
		rebuild(bl); int rec = sz[r];
		for(register int i = r; i > l; --i)
			sz[i] = sz[i - 1];
		sz[l] = rec; return ;
	}
	else
	{
		rebuild(bl); rebuild(br); int rec = sz[r];
		--cnt[bl][sz[ed[bl]]]; ++cnt[bl][rec];
		--cnt[br][rec]; ++cnt[br][sz[posed[br - 1]]];
		if(r == ed[br])
		{
			if(tagnum[br] >= siz - 1) rebuild(br);
			tag[br].push_back(sz[posed[br - 1]]);
			++tagnum[br]; --posed[br];
		}
		else
		{
			for(register int i = r; i > st[br]; --i)
				sz[i] = sz[i - 1];
			sz[st[br]] = sz[posed[br - 1]];
		}
		for(register int i = br - 1; i > bl; --i)
		{
			if(tagnum[i] >= siz - 1) rebuild(i);
			--cnt[i][sz[posed[i]]];
			++cnt[i][sz[posed[i - 1]]];
			tag[i].push_back(sz[posed[i - 1]]);
			++tagnum[i]; --posed[i];
		}
		if(l == st[bl])
		{
			if(tagnum[bl] >= siz - 1) rebuild(bl);
			tag[bl].push_back(rec);
			++tagnum[bl]; --posed[bl];
		}
		else
		{
			for(register int i = ed[bl]; i > l; --i)
				sz[i] = sz[i - 1];
			sz[l] = rec;
		}
	}
	return ;
}

inline int query(int l, int r, int x)
{
	bl = bel[l]; br = bel[r]; ans = 0;
	if(bl == br)
	{
		rebuild(bl);
		for(register int i = l; i <= r; ++i)
			ans += sz[i] == x;
	}
	else
	{
		if(l == st[bl]) --bl;
		else
		{
			rebuild(bl);
			for(register int i = l; i <= ed[bl]; ++i)
				ans += sz[i] == x;
		}
		if(r == ed[br]) ++br;
		else
		{
			rebuild(br);
			for(register int i = st[br]; i <= r; ++i)
				ans += sz[i] == x;
		}
		for(register int i = bl + 1; i < br; ++i)
			ans += cnt[i][x];
	}
	return ans;
}

int main()
{
	n = read(); preblocks(); m = read();
	for(register int i = 1; i <= m; ++i)
	{
		ope = read();
		l = (read() + ans - 1) % n + 1;
		r = (read() + ans - 1) % n + 1;
		if(l > r) qswap(l, r);
		if(ope == 1) modify(l, r);
		else
		{
			x = (read() + ans - 1) % n + 1;
			write(query(l, r, x));
		}
	}
	return 0;
}
```

---

## 作者：zesqwq (赞：2)

# CF455D Serega and Fun 题解

[题目传送门](https://www.luogu.com.cn/problem/CF455D)

一个比较另类的分块做法。

实际上你操作 $1$ 不就是把元素 $r$ 扔到下标为 $l$ 的位置对吧。

然后我们就可以把一个序列拆成 $\sqrt n$ 个块，就可以应付操作 $1$ 了，也就是插入的时候暴力找块暴力插入，删除也是一样，然后设置一个阈值，当块大小大于这个阈值的时候暴力重构就行了。

解决了操作 $1$，接下来我们看操作 $2$，根据套路，散块暴力处理行。对于整块，我们可以开一个桶来记录块内每个数的出现次数即可。

$\text{Code:}$

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
const int N = 1e5 + 10, M = 600, LIMIT = 500, S = 300;
struct Block {
    int cnt, a[M];
    int v[N];
    inline int &operator[](int x) { return a[x]; }
} f[M];
int tot, siz, g[N], n, m;
void print() {
    for (int i = 1; i <= tot; i++)
        for (int j = 1; j <= f[i].cnt; j++) g[++siz] = f[i][j];
}
void build() {
    for (int i = 1; i <= tot; i++) {
        for (int j = 1; j <= f[i].cnt; j++) --f[i].v[f[i][j]], f[i][j] = 0;
        f[i].cnt = 0;
    }
    int pos;
    for (int i = 1; i <= siz; i++) {
        pos = (i - 1) / S + 1;
        f[pos][++f[pos].cnt] = g[i], ++f[pos].v[g[i]];
    }
    tot = pos;
}
inline int find(int &x) {
    int nowpos = 1;
    while (f[nowpos].cnt < x && nowpos < tot) x -= f[nowpos].cnt, ++nowpos;
    return nowpos;
}
inline int del(int x) {
    int p = find(x), ans = f[p][x];
    --f[p].v[ans];
    for (int i = x; i < f[p].cnt; i++) f[p][i] = f[p][i + 1];
    f[p][f[p].cnt--] = 0;
    return ans;
}
void rebuild() {
    siz = 0, print();
    build();
}
void fins(int x, int v) {
    int p = find(x);
    ++f[p].cnt;
    for (int i = f[p].cnt; i > x; i--) f[p][i] = f[p][i - 1];
    f[p][x] = v, ++f[p].v[v];
    if (f[p].cnt >= LIMIT) rebuild();
}
int query(int l, int r, int k) {
    int pl = find(l), pr = find(r), ans = 0;
    if (pl == pr) {
        for (int i = l; i <= r; i++)
            if (f[pl][i] == k) ++ans;
        return ans;
    }
    for (int i = l; i <= f[pl].cnt; i++) ans += (f[pl][i] == k);
    for (int i = 1; i <= r; i++) ans += (f[pr][i] == k);
    for (int i = pl + 1; i < pr; i++) ans += f[i].v[k];
    return ans;
}
int main() {
    // freopen("out", "w", stdout);
    cin >> n, siz = n;
    for (int i = 1; i <= n; i++) scanf("%d", &g[i]);
    build();
    int op, l, r, k;
    int lstans = 0;
    cin >> m;
    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d", &op, &l, &r);
        l = (l + lstans - 1) % n + 1, r = (r + lstans - 1) % n + 1;
        if (l > r) swap(l, r);
        if (op == 1) {
            int v = del(r);
            fins(l, v);
        } else
            scanf("%d", &k), k = (k + lstans - 1) % n + 1, printf("%d\n", lstans = query(l, r, k));
    }
    return 0;
}
```

---

## 作者：Utilokasteinn (赞：1)

## [Link](https://www.luogu.com.cn/problem/CF455D)

一道比较板的分块，我居然一眼就知道怎么做了，感觉最多评蓝。

考虑用分块维护。分块后维护每个区间内 $k$ 的个数。

至于如何维护，每块开一个双向队列维护区间内数的顺序即可。因为区间是往右平移一次，可以发现每块中某个数字个数最多加或减 $1$。维护一下这个队列就容易知道哪个数要加，哪个数要减。

维护队列的时候要注意队首的下标为 $0$，而非 $1$。

代码实现不算很难。

注意事项，若你 RE on test 9，是删除或插入队列的时候越界了，例如以下代码：

```cpp
que[q].erase(que[q].begin()+r-L[q]+1);
```

这串代码在 ```que[q].begin()+r``` 的时候越界了，访问到了奇怪的地方，然后就 RE 了。

解决方法很简单，加个括号就好了。如下：

```cpp
que[q].erase(que[q].begin()+(r-L[q])+1);
```

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int s=0;char c=getchar();
	for(;!isdigit(c);c=getchar());
	for(;isdigit(c);c=getchar())
		s=s*10+c-'0';
	return s;
}
int n,m,a[100005],ans;
int block,L[320],R[320],pos[100005];
int cnt[320][100005];
deque<int>que[320];
void input()
{
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	block=sqrt(n);
	for(int i=1;i<=block;i++)
		L[i]=R[i-1]+1,R[i]=i*block;
	if(R[block]<n)
	{
		block++;
		L[block]=R[block-1]+1;
		R[block]=n;
	}
	for(int i=1;i<=block;i++)
		for(int j=L[i];j<=R[i];j++)
		{
			pos[j]=i,cnt[i][a[j]]++;
			que[i].push_back(a[j]);
		}
}
void update(int l,int r)
{
	int p=pos[l],q=pos[r];
	if(p==q)
	{
		int temp=que[p][r-L[p]];
		for(int i=r;i>l;i--)
			que[p][i-L[p]]=que[p][i-1-L[p]];
		que[p][l-L[p]]=temp;
		return;
	}
	for(int i=p+1;i<=q;i++)
	{
		int temp=que[i-1].back();
		que[i].push_front(temp);
		cnt[i][temp]++;
		que[i-1].pop_back();
		cnt[i-1][temp]--;
	}
	int temp=que[q][r-L[q]+1];
	que[q].erase(que[q].begin()+(r-L[q])+1);
	cnt[q][temp]--;
	que[p].insert(que[p].begin()+(l-L[p]),temp);
	cnt[p][temp]++;
}
int query(int l,int r,int val)
{
	int p=pos[l],q=pos[r],res=0;
	if(p==q)
	{
		for(int i=l;i<=r;i++)
			res+=que[p][i-L[p]]==val;
		return res;
	}
	for(int i=p+1;i<=q-1;i++)
		res+=cnt[i][val];
	for(int i=l;i<=R[p];i++)
		res+=que[p][i-L[p]]==val;
	for(int i=L[q];i<=r;i++)
		res+=que[q][i-L[q]]==val;
	return res;
}
void solve()
{
	m=read();
	while(m--)
	{
		int op=read(),l=(read()+ans-1)%n+1,r=(read()+ans-1)%n+1;
		if(l>r)swap(l,r);
		if(op==1)update(l,r);
		else
		{
			int k=(read()+ans-1)%n+1;
			ans=query(l,r,k);
			printf("%d\n",ans);
		}
	}
}
int main()
{
	input();
	solve();
	return 0;
}
```

NOIP 前夜的前夜写的题解，希望 RP++，也祝各位大佬 RP++，乱杀 NOIP。

谢谢观赏。

---

## 作者：AIskeleton (赞：1)

此题暴力可过。  
按照题意模拟即可。  
注意要用 C++20。  

```cpp
#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx,avx2")
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+100;
int n,a[N],lst,q;
signed main(){
  std::ios::sync_with_stdio(false);cin.tie(nullptr);
  cin>>n;for(int i=1;i<=n;i++) cin>>a[i];cin>>q;
  for(int i=1;i<=q;i++){
    int o,l,r;cin>>o>>l>>r;
    l=(l+lst-1)%n+1;r=(r+lst-1)%n+1;
    if(l>r) swap(l,r);
    if(o==1){
      int x=a[r];
      for(int i=r;i^l;--i) a[i]=a[i-1];
      a[l]=x;
    }else{
      int k;cin>>k;k=(k+lst-1)%n+1;int cnt=0;
      for(int i=l;i<=r;i++) cnt+=(a[i]==k);
      cout<<(lst=cnt)<<'\n';
    }
  }
}
```

-----

上面纯属娱乐。 

[博客园查看](https://www.cnblogs.com/AIskeleton/p/16904913.html)  

题解区里好像只有一篇平衡树的题解，剩下的包括 CF 官方题解都是分块，那蒟蒻就贡献一发 FHQ-Treap 的题解吧。  
显然，如果不强制在线，每个颜色维护个 `vector` 然后二分即可。  
不难发现，每次操作 1 都只影响到了 $a_r$ 的相对位置。  
考虑用平衡树维护。  
用 $n+1$ 棵平衡树，其中一棵平衡树维护相对顺序编号，$n$ 个平衡树维护每种颜色。  
时间复杂度：$O(n + q \log_2 n)$。  
思路不难想，代码比较复杂，具体可参考下面的代码。  

```cpp
// I forgot all the tragedies and all I saw were miracles.

/************************************
|* Author:  A.I.skeleton
|* Problem: D. Serega and Fun
|* Contest: Codeforces Round #260 (Div. 1)
|* URL:     https://codeforces.com/contest/455/problem/D
|* When:    2022-11-18 18:10:31
|* 
|* Memory:  256 MB
|* Time:    4000 ms
************************************/
#include <bits/stdc++.h>
using namespace std;
#define me(t,x) memset(t,x,sizeof(t))
#define L(i,j,k) for(int (i)=(j);i<=(k);(i)++)
#define R(i,j,k) for(int (i)=(j);i>=(k);(i)--)
#define FST ios::sync_with_stdio(false);cin.tie(nullptr);

namespace IO{
template<class A,class B>ostream&operator<<(ostream&X,const pair<A,B>&p)
{return X<<"{"<<F(p)<<","<<S(p)<<"}";}
template<class A>ostream&operator<<(ostream&X,const set<A>&v)
{X<<"{";for(auto i:v){if(i!=*v.begin()) X<<",";X<<i;}return X<<"}";}
template<class A,class B>ostream&operator<<(ostream&X,const map<A,B>&v)
{X<<"{";for(auto i:v){if(i!=*v.begin()) X<<",";X<<i;}return X<<"}";}
template<class A>ostream&operator<<(ostream&X,const vector<A>&v)
{X<<"{";L(i,0,si(v)-1){if(i)X<<",";X<<v[i];}return X<<"}";}
template<typename T>void rd(T &x){cin>>x;}template<typename T>void wr(T x){cout<<x;}
template<typename T,typename ...Args>void rd(T &x,Args&...g){rd(x),rd(g...);}
template<typename T,typename ...Args>void wr(T x,Args...g){wr(x),wr(g...);}
}using namespace IO;char x_x;clock_t S;

const int N=1e6,INF=1e9;
int n,q,cnt,lst,rt[N],a[N],id[N];
int pr[N],fa[N],val[N],ls[N],rs[N],si[N];
void pp(int p){si[p]=si[ls[p]]+si[rs[p]]+1;}
int nd(int v,int p=++cnt){val[p]=v;pr[p]=rand();si[p]=1;return p;}
int rk(int p){
  int s=si[ls[p]]+1;for(;p^rt[0];p=fa[p]) 
    s+=(rs[fa[p]]==p)*(si[ls[fa[p]]]+1);return s;
}void sps(int p,int v,int &x,int &y,int a,int b){
  if(!p) return x=y=0,void();
  if(si[ls[p]]+1<=v) fa[p]=a,sps(rs[x=p],v-si[ls[p]]-1,rs[p],y,p,b);
  else fa[p]=b,sps(ls[y=p],v,x,ls[p],a,p);pp(p);
}void spv(int p,int v,int &x,int &y,int a,int b){
  if(!p) return x=y=0,void();
  if(rk(val[p])<=v) fa[p]=a,spv(rs[x=p],v,rs[p],y,p,b);
  else fa[p]=b,spv(ls[y=p],v,x,ls[p],a,p);pp(p);
}int mer(int x,int y){
  if(!x||!y) return x|y;if(pr[x]>pr[y]) return fa[rs[x]=mer(rs[x],y)]=x,pp(x),x;
  else return fa[ls[y]=mer(x,ls[y])]=y,pp(y),y;
}void bud(int &p,int f,int l,int r){
  if(l>r) return p=0,void();int m=(l+r)>>1;fa[id[m]=p=nd(a[m])]=f;
  bud(ls[p],p,l,m-1);bud(rs[p],p,m+1,r);pp(p);
}void ins(int r,int v){int x,y;spv(rt[r],rk(v)-1,x,y,0,0);rt[r]=mer(mer(x,nd(v)),y);}
void del(int r,int v){int x,y,z;spv(rt[r],v-1,x,y,0,0);spv(y,v,y,z,0,0);rt[r]=mer(x,z);}
void spl(int l,int r){
  int w,x,y,z,pre;sps(rt[0],r-1,x,y,0,0);sps(y,1,y,z,0,0);
  pre=y;rt[0]=mer(mer(x,y),z);del(val[pre],r);
  sps(rt[0],l-1,w,x,0,0);sps(x,r-l,x,y,0,0);sps(y,1,y,z,0,0);
  rt[0]=mer(mer(mer(w,y),x),z);ins(val[pre],pre);
}int ask(int p,int l,int r){
  int x,y,z,s;spv(rt[p],l-1,x,y,0,0);spv(y,r,y,z,0,0);
    s=si[y];rt[p]=mer(mer(x,y),z);return s;
}char y_y;signed main(){
  rd(n);L(i,1,n) rd(a[i]);
  bud(rt[0],0,1,n);L(i,1,n) ins(a[i],id[i]);
  rd(q);L(i,1,q){
    int o,l,r,k;rd(o,l,r);l=(l+lst-1)%n+1;r=(r+lst-1)%n+1;if(l>r) swap(l,r);
    if(o==1&&l<r) spl(l,r);if(o==2) rd(k),k=(k+lst-1)%n+1,wr(lst=ask(k,l,r),'\n');
  }return 0;
}
```
卡常后排到了次优解，最优解是替罪羊树。

---

## 作者：一只绝帆 (赞：0)

一直 RE on #9 的人注意一下，对 `std::deque` 的迭代器进行数值运算时（例如 `it+a-b`）可能越界，需要改写成 `it+(a-b)`。

考虑分块。

每个块开一个 `deque`，然后操作相当于边界块插入一个元素删除一个元素，中间块左边右边动一个元素。

比块状链表好写多了。

Code:
```cpp
#include<bits/stdc++.h>
#define F(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
#define UF(i,a,b) for(int i=a,i##end=b;i>=i##end;i--)
#define gc getchar
#define l(x) ((x-1)*B+1)
#define r(x) min(n,l(x+1)-1)
#define id(x) ((x-1)/B+1)
using namespace std;
int read() {
	int s=0,w=0;char c=gc();
	while(c<'0'||c>'9') w|=(c=='-'),c=gc();
	while(c>='0'&&c<='9') s=s*10+(c&15),c=gc();
	return w?-s:s;
}
const int N=1e5+5,B=350;
int n,a[N],la,l,r,k,bn[B][N];
deque<int> q[B],tmpl,tmpr;
int main() {
	n=read();
	F(i,1,n) a[i]=read();
	F(i,1,id(n)) F(j,l(i),r(i)) q[i].push_back(a[j]),bn[i][a[j]]++;
	F(QAQ,1,read()) {
		if(read()==1) {
			int l=(read()+la-1)%n+1,r=(read()+la-1)%n+1;
			if(l>r) swap(l,r);
			if(id(l)==id(r)) {
				int p=id(l),tmp=q[p][r-l(p)];
				q[p].erase(q[p].begin()+(r-l(p)));
				q[p].insert(q[p].begin()+(l-l(p)),tmp);
				continue;
			}
			int tmp=q[id(r)][r-l(id(r))];
			bn[id(l)][tmp]++,bn[id(r)][tmp]--;
			q[id(r)].erase(q[id(r)].begin()+(r-l(id(r))));
			q[id(l)].insert(q[id(l)].begin()+(l-l(id(l))),tmp);
			F(i,id(l),id(r)-1) {
				tmp=*(q[i].rbegin());
				bn[i][tmp]--;bn[i+1][tmp]++;
				q[i].pop_back();q[i+1].push_front(tmp);
			}
		} else {
			l=(read()+la-1)%n+1;r=(read()+la-1)%n+1;k=(read()+la-1)%n+1;
			if(l>r) swap(l,r);
			int res=0;
			if(id(l)==id(r)) {
				F(i,l-l(id(l)),r-l(id(l))) res+=(*(q[id(l)].begin()+i)==k);
				cout<<(la=res)<<'\n';
				continue;
			}
			F(i,l-l(id(l)),r(id(l))-l(id(l))) res+=(*(q[id(l)].begin()+i)==k);
			F(i,0,r-l(id(r))) res+=(*(q[id(r)].begin()+i)==k);
			F(i,id(l)+1,id(r)-1) res+=bn[i][k];
			cout<<(la=res)<<'\n';
		}
	}
	return 0;
}
```

---

