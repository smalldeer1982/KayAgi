# [ABC341E] Alternating String

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc341/tasks/abc341_e

`0` と `1` のみからなる文字列であって、文字列中のどの連続する $ 2 $ 文字も異なるようなものを **良い文字列** とよびます。  
`0` と `1` のみからなる長さ $ N $ の文字列 $ S $ が与えられます。 $ Q $ 個のクエリが与えられるので、順に処理してください。  
クエリは次の $ 2 $ 種類です。

- `1 L R` : $ S $ の $ L $ 文字目から $ R $ 文字目までの `0` と `1` を反転させる。すなわち、$ L\leq\ i\leq\ R $ をみたす整数 $ i $ について、$ S $ の $ i $ 文字目が `0` ならば `1` に、`1` ならば `0` に変更する。
- `2 L R` : $ S $ の $ L $ 文字目から $ R $ 文字目までを（順番を変えずに）抜き出した長さ $ (R-L+1) $ の文字列を $ S' $ とする。$ S' $ が良い文字列ならば `Yes` を、そうでないならば `No` を出力する。

## 说明/提示

### 制約

- $ 1\leq\ N,\ Q\leq\ 5\times\ 10^5 $
- $ S $ は `0` と `1` のみからなる長さ $ N $ の文字列
- $ 1,2 $ 種類目のクエリについて、$ 1\leq\ L\leq\ R\leq\ N $
- $ 2 $ 種類目のクエリが少なくとも $ 1 $ つ存在する。
- $ N $, $ Q $, $ L $, $ R $ は整数

### Sample Explanation 1

最初、$ S= $`10100` です。このとき、クエリを与えられた順に処理すると以下のようになります。 - $ 1 $ 番目のクエリについて、$ S $ の $ 1 $ 文字目から $ 3 $ 文字目までを抜き出した文字列は $ S'= $`101` です。これは良い文字列なので `Yes` を出力します。 - $ 2 $ 番目のクエリについて、$ S $ の $ 1 $ 文字目から $ 5 $ 文字目までを抜き出した文字列は $ S'= $`10100` です。これは良い文字列でないので `No` を出力します。 - $ 3 $ 番目のクエリについて、$ S $ の $ 1 $ 文字目から $ 4 $ 文字目までの `0` と `1` を反転させます。文字列 $ S $ は $ S= $`01010` となります。 - $ 4 $ 番目のクエリについて、$ S $ の $ 1 $ 文字目から $ 5 $ 文字目までを抜き出した文字列は $ S'= $`01010` です。これは良い文字列なので `Yes` を出力します。 - $ 5 $ 番目のクエリについて、$ S $ の $ 3 $ 文字目の `0` と `1` を反転させます。文字列 $ S $ は $ S= $`01110` となります。 - $ 6 $ 番目のクエリについて、$ S $ の $ 2 $ 文字目から $ 4 $ 文字目までを抜き出した文字列は $ S'= $`111` です。これは良い文字列でないので `No` を出力します。

### Sample Explanation 2

`0` または `1` の $ 1 $ 文字からなる文字列は良い文字列の条件をみたすことに注意してください。

## 样例 #1

### 输入

```
5 6
10100
2 1 3
2 1 5
1 1 4
2 1 5
1 3 3
2 2 4```

### 输出

```
Yes
No
Yes
No```

## 样例 #2

### 输入

```
1 2
1
1 1 1
2 1 1```

### 输出

```
Yes```

# 题解

## 作者：Otue (赞：11)

### 做法 $1$:

赛时做法，纯属搞笑。

考虑将询问转化成前缀和的形式，定义 $s_i$ 表示前 $i$ 个字符有多少个相邻字符相同。那么 $[l,r]$ 满足条件则说明 $s_l=s_r$。

考虑翻转，发现翻转给答案带来影响的只有 $a_{l-1},a_l,a_r,a_{r+1}$ 这四个数。中间的根本没有影响。

* 如果 $a_{l-1}$ 和 $a_l$ 之前相同，翻转后则会对 $s_l,s_{l+1},\dots,s_n$ 这些数产生 $-1$ 的贡献。
* 如果 $a_{l-1}$ 和 $a_l$ 之前不同，翻转后则会对 $s_l,s_{l+1},\dots,s_n$ 这些数产生 $1$ 的贡献。
* 如果 $a_{r}$ 和 $a_{r+1}$ 之前相同，翻转后则会对 $s_{r+1},s_{r+2},\dots,s_n$ 这些数产生 $-1$ 的贡献。
* 如果 $a_{r}$ 和 $a_{r+1}$ 之前不同，翻转后则会对 $s_{r+1},s_{r+2},\dots,s_n$ 这些数产生 $1$ 的贡献。

用两颗线段树维护，第一颗线段树维护经过修改后的 $a_i$ 的值，第二颗线段树维护经过修改后 $s_i$ 的值。

```c++
#include <bits/stdc++.h>
using namespace std;

#define ls p << 1
#define rs p << 1 | 1
#define int long long
const int N = 1e6 + 5;

int n, m, b[N];
char a[N]; 

struct edge {
	int l, r, sum, lazy;
}tree[2][N * 4];

void push_up(int op, int p) {
	tree[op][p].sum = tree[op][ls].sum + tree[op][rs].sum;
}

void push_down(int op, int p) {
	if (tree[op][p].lazy) {
		tree[op][ls].lazy += tree[op][p].lazy;
		tree[op][rs].lazy += tree[op][p].lazy;
		tree[op][ls].sum += (tree[op][ls].r - tree[op][ls].l + 1) * tree[op][p].lazy;
		tree[op][rs].sum += (tree[op][rs].r - tree[op][rs].l + 1) * tree[op][p].lazy; 
		tree[op][p].lazy = 0;
	}
}

void build(int op, int p, int l, int r) {
	tree[op][p].l = l, tree[op][p].r = r;
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(op, ls, l, mid);
	build(op, rs, mid + 1, r);
}

void modify(int op, int p, int l, int r, int v) {
	if (l <= tree[op][p].l && tree[op][p].r <= r) {
		tree[op][p].lazy += v;
		tree[op][p].sum += (tree[op][p].r - tree[op][p].l + 1) * v;
		return; 
	}
	push_down(op, p); 
	int mid = (tree[op][p].l + tree[op][p].r) >> 1;
	if (l <= mid) modify(op, ls, l, r, v);
	if (r > mid) modify(op, rs, l, r, v);
	push_up(op, p);
}

int query(int op, int p, int l, int r) {
	if (l <= tree[op][p].l && tree[op][p].r <= r) return tree[op][p].sum;
	push_down(op, p); 
	int mid = (tree[op][p].l + tree[op][p].r) >> 1, res = 0;
	if (l <= mid) res += query(op, ls, l, r);
	if (r > mid) res += query(op, rs, l, r);
	return res; 
}

signed main() {
	cin >> n >> m >> (a + 1);
	for (int i = 1; i <= n; i++) b[i] = a[i] - '0';
	build(0, 1, 1, n);
	build(1, 1, 1, n);
	int t = 0; 
	for (int i = 1; i <= n; i++) {
		if (i > 1) t += (b[i] == b[i - 1]);
		modify(1, 1, i, i, t);
	}
	for (int i = 1; i <= m; i++) {
		int oo, l, r;
		cin >> oo >> l >> r;
		if (oo == 1) {
			int t1 = -1; if (l - 1 >= 1) t1 = (b[l - 1] ^ (query(0, 1, l - 1, l - 1) % 2)); // t1求出a_{l-1}的值 
			int t2 = (b[l] ^  (query(0, 1, l, l) % 2)); // t2求出a_l值 
			int t3 = (b[r] ^ (query(0, 1, r, r) % 2)); // t3求出a_r值 
			int t4 = -1; if (r + 1 <= n) t4 = (b[r + 1] ^ (query(0, 1, r + 1, r + 1) % 2)); // t4求出a_{r+1}的值 
			if (t1 != -1 && t1 == t2) modify(1, 1, l, n, -1);
			else if (t1 != -1) modify(1, 1, l, n, 1);
			if (t4 != -1 && t3 == t4) modify(1, 1, r + 1, n, -1);
			else if (t4 != -1) modify(1, 1, r + 1, n, 1);
			modify(0, 1, l, r, 1);
		} 
		else {
			if (query(1, 1, r, r) == query(1, 1, l, l)) puts("Yes");
			else puts("No");
		}
	} 
}
```
### 做法 $2$:

考虑直接在线段树内部加一个变量 $flg$ 表示这个区间是否满足相邻都不同的性质。转移：`tree[p].flg = tree[ls].flg & tree[rs].flg & (tree[ls].R != tree[rs].L);`。

其中 $L,R$ 代表这个区间的左端点的值和右端点的值。

代码：

```c++
#include <bits/stdc++.h>
using namespace std;

#define ls p << 1
#define rs p << 1 | 1
#define int long long
const int N = 5e5 + 5;

int n, q;
char a[N]; 

struct edge {
	int l, r, rev, flg, L, R;
}tree[N * 4];

void push_up(int p) {
	tree[p].flg = tree[ls].flg & tree[rs].flg & (tree[ls].R != tree[rs].L);
	tree[p].L = tree[ls].L;
	tree[p].R = tree[rs].R;
}

void push_down(int p) {
	if (tree[p].rev) {
		tree[ls].rev ^= 1; tree[rs].rev ^= 1;
		tree[ls].L ^= 1, tree[ls].R ^= 1;
		tree[rs].L ^= 1, tree[rs].R ^= 1;
		tree[p].rev = 0;
	}
}

void build(int p, int l, int r) {
	tree[p].l = l, tree[p].r = r;
	if (l == r) {
		tree[p].flg = 1;
		tree[p].L = tree[p].R = (int)a[l] - '0';
		return;
	}
	int mid = (l + r) >> 1; 
	build(ls, l, mid);
	build(rs, mid + 1, r);
	push_up(p);
}

void modify(int p, int l, int r) {
	if (l <= tree[p].l && tree[p].r <= r) {
		tree[p].rev ^= 1;
		tree[p].L ^= 1, tree[p].R ^= 1;
		return;
	}
	push_down(p);
	int mid = (tree[p].l + tree[p].r) >> 1;
	if (l <= mid) modify(ls, l, r);
	if (r > mid) modify(rs, l, r);
	push_up(p);
}

struct node {
	int flg, L, R;
};

node query(int p, int l, int r) {
	if (tree[p].l > r || tree[p].r < l) return {-1, 0, 0};
	if (l <= tree[p].l && tree[p].r <= r) return {tree[p].flg, tree[p].L, tree[p].R};
	push_down(p);
	node x = query(ls, l, r), y = query(rs, l, r);
	if (x.flg == -1) return y;
	if (y.flg == -1) return x;
	return {x.flg & y.flg & (x.R != y.L), x.L, y.R};
}

signed main() {
	cin >> n >> q >> (a + 1);
	build(1, 1, n);
	for (int i = 1; i <= q; i++) {
		int op, l, r;
		cin >> op >> l >> r;
		if (op == 1) modify(1, l, r);
		else puts((query(1, l, r).flg) ? "Yes" : "No");
	}
}
```

### 做法 $3$:

用 STL 的 set，将所有 $s_i=s_{i+1}$ 的下标 $i$ 加入 set。翻转只需要看 $[l,r]$ 两侧即可。

```c++
set<int> I;
for (int i = 0; i < N - 1; i++) if (s[i] == s[i + 1]) I.insert(i);
for (int i = 0; i < Q; i++) {
	int x, l, r;
	cin >> x >> l >> r;
	l--; r--;
	if (x == 1) {
		if (I.find(l - 1) == I.end()) I.insert(l - 1);
		else I.erase(l - 1);
		if (I.find(r) == I.end()) I.insert(r);
		else I.erase(r);
	}
	else {
		auto it = I.lower_bound(l);
		if (it == I.end() || *it >= r) cout << "Yes" << endl;
		else cout << "No" << endl;
	}
}
```

祝大家学习愉快！

---

## 作者：nr0728 (赞：9)

### 前言

一道比较简单的思维题，场切很容易。

此外，本题解**不**使用分块、线段树、树状数组等方法，使用 **`bitset`**。

### 思路

定义 $b_2,b_3,\cdots,b_n$。$\forall 2\leq i\leq n$，若 $S_i=S_{i-1}$，则 $b_i=1$，否则 $b_i=0$。

**操作 1：**

$\forall L\leq i\leq R,S_i\leftarrow \neg S_i$。在这个操作中，$\forall L\leq i\lt R$，$S_i$ 与 $S_{i+1}$ 的“是否相同”关系一定不改变，即 $b_{i+1}$ 不变。而 $S_{L-1}$ 与 $S_{L}$ 以及 $S_R$ 与 $S_{R+1}$ 的“是否相同”关系一定改变。所以我们在执行此操作时，只需修改 $b_L$ 与 $b_{R+1}$。此外，注意判断边界情况。

**操作 2：**

容易发现，按照 $b_i$ 的定义，如果 $b_{L+1}=b_{L+2}=\cdots=b_{R}=0$，则 $S_L,S_{L+1},\cdots,S_R$ 相邻两项均不等。所以我们只需查询在 $b_L$ 的后面（不包括 $b_L$）第一个出现 $b_i=1$ 的位置是否大于 $R$ 即可。若大于 $R$，那么满足条件。

**如何快速地查询 $\bm{b_L}$ 的后面（不包括 $\bm{b_L}$）第一个出现 $\bm{b_i=1}$ 的位置？**

在 `bitset` 中，有一个内置的 `_Find_next` 函数。具体地，设有一个名为 $b$ 的 `bitset` 且 $s$ 为其长度，`b._Find_next(p)` 会返回在 $b_{p+1},b_{p+2},\cdots,b_{s}$ 中第一个出现 $b_i=1$ 的 $i$。如果找不到，会返回 $s+1$。

因为 `bitset` 会压位处理，所以这个操作的时间复杂度是  $\mathcal O(\dfrac s \omega)$ 的，其中，$\omega$ 通常为 $32$，并且可以使用 [这篇 Codeforces 博客](https://codeforces.com/blog/entry/77480) 的方法使用 `long long` 压位，以达到 $\omega=64$，使运行速度更快。

**复杂度分析：**

单次操作 1 的时间复杂度为 $\mathcal O(1)$（最多只需修改左、右端点的值），单次操作 2 的时间复杂度为 $\mathcal O(\dfrac n \omega)$（已在上方分析），综上，时间复杂度最高为 $\mathcal O(\dfrac {qn} \omega)$。

空间复杂度为 $\mathcal O(n)$。

### 代码

详见 [AtCoder 提交记录](https://atcoder.jp/contests/abc341/submissions/50372566)。

注：不使用 64 位 `bitset` 等优化的代码也能通过本题。[AtCoder 提交记录](https://atcoder.jp/contests/abc341/submissions/50468994)。

---

## 作者：KSCD_ (赞：6)

# 题意
给出一个只包含 $0$ 和 $1$ 的字符串，要实现区间取反和检查区间内是否有相邻的相同字符两个操作。
# 思路
若暴力修改、暴力判断，时间复杂度太大，无法通过本题。

考虑优化，发现题目为区间修改和区间查询，自然想到用线段树来做。

首先考虑区间合并，发现当且仅当左右两区间本身合法，且两区间相邻处不同时，合并后的区间合法。因此线段树要维护区间是否合法和区间左右两端的值。

接着是区间取反，与线段树模板区别不大，只是修改时只需把区间左右两端的值取反，区间的合法性并不改变，最后打上标记即可。

然后是标记的维护与下放。标记也用取反来维护，因为取反偶数次相当于没操作。下放标记时也像修改一样，把两个儿子的左右两端都取反即可。

最后是区间查询，这里需要把左右两部分区间都查询出来再合并，才能得到最终结果。

具体请看代码实现。
# 代码
其实是比较裸的线段树题，这里用了异或 $1$ 来取反。
```cpp
#include<iostream>
using namespace std;
const int N=5e5+10;
int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){ if(ch=='-') w=-1; ch=getchar();}
    while(ch>='0'&&ch<='9'){ s=s*10+ch-'0'; ch=getchar();}
    return s*w;
}
int n,Q,t=1,aa[N]; 
char c[N];
struct nod
{
	int l,r;//左儿子编号，右儿子编号 
	bool lf,rf,f,tag;//左右端点的值，区间是否合法，懒惰标记 
}a[N*2];//线段树记得开两倍空间
void pushup(nod &u,nod lc,nod rc)
{
	if(lc.rf!=rc.lf&&lc.f&&rc.f)
		u.f=true;
	else
		u.f=false; 
	u.lf=lc.lf,u.rf=rc.rf;
} //合并操作 
void pushdown(int u)
{
	if(a[u].tag==0)
		return;
	int lc=a[u].l,rc=a[u].r;
	a[lc].lf^=1,a[rc].lf^=1,a[lc].rf^=1,a[rc].rf^=1;
	a[lc].tag^=1,a[rc].tag^=1,a[u].tag=0;
} //标记下放 
void build(int u,int l,int r)
{
	if(l==r)
	{
		a[u].lf=a[u].rf=aa[l],a[u].f=true;
		return;
	}
	int mid=(l+r)/2;
	a[u].l=++t;
	build(t,l,mid);
	a[u].r=++t;
	build(t,mid+1,r);
	pushup(a[u],a[a[u].l],a[a[u].r]);
} //建树 
void change(int u,int l,int r,int ll,int rr)
{
	if(l>=ll&&r<=rr)
	{
		a[u].lf^=1,a[u].rf^=1,a[u].tag^=1;
		return;
	}
	int mid=(l+r)/2;
	pushdown(u);
	if(ll<=mid)
		change(a[u].l,l,mid,ll,rr);
	if(rr>mid)
		change(a[u].r,mid+1,r,ll,rr);
	pushup(a[u],a[a[u].l],a[a[u].r]);
} //区间取反 
nod check(int u,int l,int r,int ll,int rr)
{
	if(l>=ll&&r<=rr)
		return a[u];
	int mid=(l+r)/2;
	pushdown(u);
	if(rr<=mid)
		return check(a[u].l,l,mid,ll,rr);
	if(ll>mid)
		return check(a[u].r,mid+1,r,ll,rr);
	nod ta=check(a[u].l,l,mid,ll,rr),tb=check(a[u].r,mid+1,r,ll,rr),res;
	pushup(res,ta,tb);
	return res;
} //区间判断 
signed main()
{
	n=read(),Q=read();
	cin>>c;
	for(int i=1;i<=n;i++)
		aa[i]=c[i-1]-'0';
	build(1,1,n);
	while(Q--)
	{
		int opt=read(),l=read(),r=read();
		if(opt==1)
			change(1,1,n,l,r);
		else
		{
			nod ans=check(1,1,n,l,r);
			if(ans.f)
				cout<<"Yes"<<"\n";
			else
				cout<<"No"<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：2c_s (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc341_e)

## 思路

看到这题是求是否有连续的 ``1`` 和 ``0``，很容易想到线段树，并且和[这道题](https://www.luogu.com.cn/problem/P6492)很像。

我们在线段树中保存下面几个变量：

``l``：当前线段左端点。

``r``：当前线段右端点。

``len``：当前线段长度。

``lp``：当前线段左端点的值。

``rp``：当前线段右端点的值。

``tag``：当前线段是否需要翻转的 lazytag。

``ma``：当前线段**最长的**没有连续的 ``1`` 和 ``0`` 的长度。

``lm``：当前线段**从左端开始**没有连续的 ``1`` 和 ``0`` 的长度。

``rm``：当前线段**从右端开始**没有连续的 ``1`` 和 ``0`` 的长度。

- 线段树需要 $4$ 倍的空间。

### 1. 建线段树

和普通的线段树建树一样，不过要加上左端点和右端点的判断。

```cpp
void build(int i,int l,int r){
	tr[i].l=l;
	tr[i].r=r;
	tr[i].len=r-l+1;
	if(l==r){
		if(a[l])tr[i].lp=tr[i].rp=1;//a[x] 存的是 x 位置为 1 还是 0。
        tr[i].ma=tr[i].lm=tr[i].rm=1;//叶子节点满足要求的长度肯定为一。
		return ;
	}
	int mid=l+r>>1;
	build(i<<1,l,mid);
	build(i<<1|1,mid+1,r);
	pushup(i);//见 2.
	return ;
}
```

### 2. 上推（pushup）操作

这是这个题的核心部分，也是最难写的部分。我们要上推的变量有：``ma``、``lm``、``rm``、``lp``、``rp``。

``ma`` 具体做法：如果两个子线段连接处的两个点（左边 ``rp`` 和右边 ``lp``）不一样，那么值为左边 ``ma``、右边 ``ma``、左边 ``rm`` $+$ 右边 ``lm`` 的最大值；否则为前两者的最大值。

``lm`` 具体做法：如果左边整个子线段都满足要求，且两个子线段连接处的两个点不一样，那么值为左边子线段长度 $+$ 右边子线段的 ``lm``；否则为左边子线段的 ``lm``。

``rm`` 具体做法：如果右边整个子线段都满足要求，且两个子线段连接处的两个点不一样，那么值为右边子线段长度 $+$ 左边子线段的 ``rm``；否则为右边子线段的 ``rm``。

``lp`` 为左边子线段的 ``lp``；``rp`` 为右边子线段的 ``rp``。

```cpp
void pushup(int i){
	if(tr[i<<1].rp^tr[i<<1|1].lp)tr[i].ma=tr[i<<1].rm+tr[i<<1|1].lm;
	else tr[i].ma=0;
	tr[i].ma=max({tr[i].ma,tr[i<<1].ma,tr[i<<1|1].ma});
    
	if(tr[i<<1].ma==tr[i<<1].len&&tr[i<<1].rp^tr[i<<1|1].lp)tr[i].lm=tr[i<<1].len+tr[i<<1|1].lm;
	else tr[i].lm=tr[i<<1].lm;
    
	if(tr[i<<1|1].ma==tr[i<<1|1].len&&tr[i<<1].rp^tr[i<<1|1].lp)tr[i].rm=tr[i<<1|1].len+tr[i<<1].rm;
	else tr[i].rm=tr[i<<1|1].rm;
    
	tr[i].lp=tr[i<<1].lp;
	tr[i].rp=tr[i<<1|1].rp;
	return ;
}
```

### 3. 区间翻转操作

这个和普通线段树区间修改没有太大区别，只需要注意 lazytag **也是取反**，而非直接赋值。

```cpp
void change(int i,int l,int r){
	if(l<=tr[i].l&&tr[i].r<=r){
		rev(i);//见 4.
        return ;
	}
    pushdown(i);//见 5.
	int mid=tr[i].l+tr[i].r>>1;
	if(l<=mid)change(i<<1,l,r);
	if(mid<r)change(i<<1|1,l,r);
	pushup(i);//见 2.
	return ;
}
```

### 4. 每条线段的翻转

只需要翻转 ``lp``、``rp`` 和 ``tag`` 三个变量。

```cpp
inline void rev(int i){
    tr[i].tag^=1;
    tr[i].lp^=1;
    tr[i].rp^=1;
    return ;
}
```

### 5. 下传懒标记（pushdown）操作

下传时翻转这个线段的左右两条子线段即可。

```cpp
inline void pushdown(int i){
    if(tr[i].tag){//如果需要翻转再操作。
        rev(i<<1);
        rev(i<<1|1);
        tr[i].tag=0;//别忘将懒标记清零。
    }
    return ;
}
```

### 6. 区间查询是否满足要求

这也是这道题的难点之一，需要我们特殊处理（合并）。

我们分类讨论：

- 如果这条线段被完全包含，那么返回这条线段。

- 如果这条线段的其中**一条**子线段被完全包含，那么递归这一边的子线段。

- 否则进行合并操作。

合并时我们需要处理的变量有：``ma``、``lm``、``rm``、``lp``、``rp``、``len``。

我们保存向左边和右边递归的结果，之后仿照上推操作，把这几个变量处理好，最后返回即可。

由于要访问左边和右边的线段的值，所以这个递归的返回值类型是**结构体。**

```cpp
node query(int i,int l,int r){
    if(l<=tr[i].l&&tr[i].r<=r)return tr[i];//完全包含。
    pushdown(i);//见 5.
    int mid=tr[i].l+tr[i].r>>1;
    if(r<=mid)return query(i<<1,l,r);//恰有一边被完全包含。
    else if(mid<l)return query(i<<1|1,l,r);
    else{
        node a=query(i<<1,l,r),b=query(i<<1|1,l,r);//递归两边保存。
        node k;
        k.len=tr[i].len;
        
        if(a.rp^b.lp)k.ma=a.rm+b.lm;
        else k.ma=0;
        k.ma=max({k.ma,a.ma,b.ma});
        
        if(a.ma==a.len&&a.rp^b.lp)k.lm=a.len+b.lm;
        else k.lm=a.lm;
        
        if(b.ma==b.len&&a.rp^b.lp)k.rm=b.len+a.rm;
        else k.rm=b.rm;
        
        k.lp=a.lp;
        k.rp=b.rp;
        return k;
    }
}
```

### 7. 主函数

由于线段树常数很大，所以在主函数这里优化一下常数。

```cpp
int main(){
	cin>>n>>m;
    for(int i=1;i<=n;++i){
        char c;
        cin>>c;
        a[i]=c-'0';//转化为整型存储。
    }
	build(1,1,n);
	while(m--){
        int op=read(),l=read(),r=read();//快读。
        if(op==1)change(1,l,r);
        else{
            int k=query(1,l,r).ma;
            if(k==r-l+1)puts("Yes");//如果等于查询长度说明完全包含。
            else puts("No");//用 puts() 更快
        }
	}
	return 0;
}
```

## 完整无注释版代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll read(){
	ll k=0,flag=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')flag=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		k=(k<<1)+(k<<3)+(c^48);
		c=getchar();
	}
	return k*flag;
}
const int N=5e5+10;
int n,m,a[N];
struct node{
	int l,r,lp,rp,len,tag,ma,lm,rm;
}tr[N<<2];
void pushup(int i){
	if(tr[i<<1].rp^tr[i<<1|1].lp)tr[i].ma=tr[i<<1].rm+tr[i<<1|1].lm;
	else tr[i].ma=0;
	tr[i].ma=max({tr[i].ma,tr[i<<1].ma,tr[i<<1|1].ma});
    
	if(tr[i<<1].ma==tr[i<<1].len&&tr[i<<1].rp^tr[i<<1|1].lp)tr[i].lm=tr[i<<1].len+tr[i<<1|1].lm;
	else tr[i].lm=tr[i<<1].lm;
    
	if(tr[i<<1|1].ma==tr[i<<1|1].len&&tr[i<<1].rp^tr[i<<1|1].lp)tr[i].rm=tr[i<<1|1].len+tr[i<<1].rm;
	else tr[i].rm=tr[i<<1|1].rm;
    
	tr[i].lp=tr[i<<1].lp;
	tr[i].rp=tr[i<<1|1].rp;
	return ;
}
void build(int i,int l,int r){
	tr[i].l=l;
	tr[i].r=r;
	tr[i].len=r-l+1;
	if(l==r){
		if(a[l])tr[i].lp=tr[i].rp=1;
        tr[i].ma=tr[i].lm=tr[i].rm=1;
		return ;
	}
	int mid=l+r>>1;
	build(i<<1,l,mid);
	build(i<<1|1,mid+1,r);
	pushup(i);
	return ;
}
inline void rev(int i){
    tr[i].tag^=1;
    tr[i].lp^=1;
    tr[i].rp^=1;
    return ;
}
inline void pushdown(int i){
    if(tr[i].tag){
        rev(i<<1);
        rev(i<<1|1);
        tr[i].tag=0;
    }
    return ;
}
void change(int i,int l,int r){
	if(l<=tr[i].l&&tr[i].r<=r){
		rev(i);
        return ;
	}
    pushdown(i);
	int mid=tr[i].l+tr[i].r>>1;
	if(l<=mid)change(i<<1,l,r);
	if(mid<r)change(i<<1|1,l,r);
	pushup(i);
	return ;
}
node query(int i,int l,int r){
    if(l<=tr[i].l&&tr[i].r<=r)return tr[i];
    pushdown(i);
    int mid=tr[i].l+tr[i].r>>1;
    if(r<=mid)return query(i<<1,l,r);
    else if(mid<l)return query(i<<1|1,l,r);
    else{
        node a=query(i<<1,l,r),b=query(i<<1|1,l,r);
        node k;
        k.len=tr[i].len;
        
        if(a.rp^b.lp)k.ma=a.rm+b.lm;
        else k.ma=0;
        k.ma=max({k.ma,a.ma,b.ma});
        
        if(a.ma==a.len&&a.rp^b.lp)k.lm=a.len+b.lm;
        else k.lm=a.lm;
        
        if(b.ma==b.len&&a.rp^b.lp)k.rm=b.len+a.rm;
        else k.rm=b.rm;
        
        k.lp=a.lp;
        k.rp=b.rp;
        return k;
    }
}
int main(){
	cin>>n>>m;
    for(int i=1;i<=n;++i){
        char c;
        cin>>c;
        a[i]=c-'0';
    }
	build(1,1,n);
	while(m--){
        int op=read(),l=read(),r=read();
        if(op==1)change(1,l,r);
        else{
            int k=query(1,l,r).ma;
            if(k==r-l+1)puts("Yes");
            else puts("No");
        }
	}
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/147272953)

---

## 作者：cjh20090318 (赞：3)

赛时用的线段树，赛后发现可以差分后用树状数组。

## 题意

给一个长度为 $N$ 由 $0/1$ 组成的数列，有 $Q$ 次操作。

1. 将区间 $[L,R]$ 的所有数按位翻转。
2. 查询 $[L,R]$ 中是否相邻两个数都不同。

## 分析

### 线段树做法

看到区间修改区间查询，很容易想到线段树。

用线段树维护区间信息：

- $L$ 表示该节点最左端的数值。
- $R$ 表示该节点最右端的数值。
- $ans$ 表示该节点是否两两不同。
- $lazy$ 表示该节点的懒标记（是否被翻转）。

区间的左端点和右端点不需要特别的存储，在递归的时候可以直接带上端点。

一个区间的按位翻转不会影响到这个区间是否相邻两个数两两不同，所以下放懒标记时不需要特别处理 $ans$，只需要处理 $L,R$。

上传的时候该区间是否两两不同需要判断左儿子、右儿子是否两两不同，且左儿子的最右端不等于右儿子的最左端。

特别的，只有一个节点也算作两两不同，建树时需要注意。

### 差分 + 树状数组做法

前后两个数不同则差分为 $1$，否则为 $0$。

修改一个区间 $[L,R]$ 只需要在差分数组 $L$ 和 $R+1$ 上取反。

如果一个区间 $[L,R]$ 两两不同，则差分数组 $[L+1,R]$ 都为 $1$，即差分数组上这一段的和为 $R-L$。

于是这个问题变成了单点修改区间查询，可以用树状数组解决。

两种解法的时间复杂度均为 $O(Q \log N)$，但是后者常数更小所以运行效率较高。

## 代码

### 线段树做法

```cpp
//the code is from chenjh
#include<cstdio>
#define MAXN 500005
#define lson (rt<<1)
#define rson (rt<<1|1)
using namespace std;
using ci=const int;
int n,q;
bool a[MAXN];
struct Node{
	bool L,R,ans,lazy;
	Node(bool _L=0,bool _R=0,bool _ans=0,bool _lazy=0):L(_L),R(_R),ans(_ans),lazy(_lazy){} 
}t[MAXN<<2];
void build(ci rt,ci l,ci r){//建树。
	if(l==r){
		t[rt].L=t[rt].R=a[l];
		t[rt].ans=1;//只有一个点也算作两两不同。
		return;
	}
	int mid=(l+r)>>1;
	build(lson,l,mid),build(rson,mid+1,r);
	t[rt].L=t[lson].L,t[rt].R=t[rson].R;
	t[rt].ans=t[lson].ans&&t[rson].ans&&t[lson].R!=t[rson].L;//上传答案。
}
void pd(ci rt,ci l,ci r){
	if(t[rt].lazy){//下放懒标记。
		t[lson].lazy^=1,t[lson].L^=1,t[lson].R^=1;
		t[rson].lazy^=1,t[rson].L^=1,t[rson].R^=1;
		t[rt].lazy=0;
	}
}
void update(ci rt,ci l,ci r,ci L,ci R){
	if(L<=l && r<=R){
		t[rt].lazy^=1,t[rt].L^=1,t[rt].R^=1;
		return;
	}
	pd(rt,l,r);
	int mid=(l+r)>>1;
	if(L<=mid) update(lson,l,mid,L,R);
	if(mid<R) update(rson,mid+1,r,L,R);
	t[rt].L=t[lson].L,t[rt].R=t[rson].R;
	t[rt].ans=t[lson].ans&&t[rson].ans&&t[lson].R!=t[rson].L;
}
Node query(ci rt,ci l,ci r,ci L,ci R){
	if(L<=l && r<=R) return t[rt];
	pd(rt,l,r);
	int mid=(l+r)>>1;
	Node ret;
	if(L<=mid && mid<R){//左右儿子区间都要查询。
		Node rl=query(lson,l,mid,L,R),rr=query(rson,mid+1,r,L,R);
		ret=Node(rl.L,rr.R,rl.ans&&rr.ans&&rl.R!=rr.L,0);//合并两个区间。
	}
	else if(L<=mid)//只有左儿子需要查询。
		ret=query(lson,l,mid,L,R);
	else if(mid<R)//只有右儿子需要查询。
		ret=query(rson,mid+1,r,L,R);
	return ret;
}
int main(){
	scanf("%d %d ",&n,&q);
	for(int i=1;i<=n;i++) a[i]=getchar()&1;
	build(1,1,n);
	for(int op,l,r;q--;){
		scanf("%d%d%d",&op,&l,&r);
		if(op==1) update(1,1,n,l,r);
		else if(op==2) puts(query(1,1,n,l,r).ans?"Yes":"No");
	}
	return 0;
}
```

### 差分 + 树状数组做法

```cpp
//the code is from chenjh
#include<cstdio>
#include<cstring>
#define MAXN 500005
using namespace std;
template<typename T>
struct fenwick_tree{
	public:
		fenwick_tree(int _SIZE=0):SIZE(_SIZE){dt=new T[SIZE+1]();memset(dt,0,sizeof(T)*(SIZE+1));}
		fenwick_tree(const fenwick_tree& y):SIZE(y.size()),dt(new T[y.size()+1]){memcpy(dt,y.get_dt(),sizeof(T)*(SIZE+1));}
		~fenwick_tree(){delete[] dt;}
		const T&operator [] (const int&x)const{return dt[x];}
		fenwick_tree&operator = (const fenwick_tree&y){if(this!=&y){SIZE=y.size();T*new_dt=new T[SIZE+1]();memcpy(new_dt,y.get_dt(),sizeof(T)*(SIZE+1));delete[] dt;dt=new_dt;}return *this;}
		void resize(int _SIZE){T*new_dt =new T[_SIZE+1]();memcpy(new_dt,dt,sizeof(T)*((SIZE<_SIZE?SIZE:_SIZE)+1));delete[] dt;dt=new_dt,SIZE=_SIZE; }
		void clear(){SIZE=0;delete[] dt;dt=new T[SIZE+1]();memset(dt,0,sizeof(T)*(SIZE+1));}
		int size()const{return SIZE;}
		T* get_dt()const{return dt;}
		void add(int x,const T&v){for(;x<=SIZE;x+=x&-x)dt[x]+=v;}
		T sum(const int&l,const int&r)const{return sum(r)-sum(l-1);}
	private:
		T*dt=nullptr;
		int SIZE;
		T sum(int x)const{T ret(0);for(;x;x^=x&-x)ret+=dt[x];return ret;}
};
int n,q;
bool a[MAXN];
int main(){
	scanf("%d %d ",&n,&q);
	for(int i=1;i<=n;i++) a[i]=getchar()^'0';
	fenwick_tree<int> T(n);//树状数组。
	for(int i=n;i>0;--i)if(a[i]^=a[i-1])T.add(i,1);//求出差分数组。
	for(int p,l,r;q--;){
		scanf("%d%d%d",&p,&l,&r);
		if(p==1){
			T.add(l,T.sum(l,l)?-1:1);//如果为 1 就修改为 0，否则修改为 1.
			if(r<n) T.add(r+1,T.sum(r+1,r+1)?-1:1);
		}
		else if(p==2) puts(l==r||T.sum(l+1,r)==r-l?"Yes":"No");//特判只有一个点的情况。
	}
	return 0;
}
```



---

## 作者：Alear (赞：2)

~~线段树是什么，能吃吗？~~

题面传送门：[洛谷](https://www.luogu.com.cn/problem/AT_abc341_e)，[Atcoder](https://atcoder.jp/contests/abc341/tasks/abc341_e)。

简明题意：维护一个 01 串，支持区间反转，查询一个字串是否满足所有相邻元素不同。

注意到一个好串的等价表述是，不包含连续相同元素，我们只需要用一个 set 维护整个串上所有相邻相等元素对的位置，查询的时候在 set 上二分查找。对于修改，只会影响到边界元素对，反转边界即可。

```cpp
#include<bits/stdc++.h>
#define TLE {int sum=0;for(int i=0;i<1e10;i++)sum+=i;cout<<sum;}
#define int long long
#define endl '\n'
#define rep(i, x, y) for(int i=(x), _=(y);i<=_;i++)
#define rrep(i, x, y) for(int i=(x), _=(y);i>=_;i--)
// #pragma GCC optimize(2)
using namespace std;
const int mod = 998244353;
const double eps = 1e-6;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

inline int read(){int c;cin>>c;return c;}
template<typename T, typename... Args>
void print(const T& first, const Args&... args) {
    cout << first;
    ((cout << ' ' << args), ...);
    cout << endl;
}
const int N=1e6 + 20,M=N*2;
int n, m, k;
char out[2][10] = {"No", "Yes"};
int a[N], b[N];

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	int n = read(), q = read();
	string s;
	cin >> s;

	set<int> st;
	rep(i, 0, s.size() - 1){
		if(s[i] == s[i + 1])
			st.insert(i + 1);
	}
	while(q--){
		int op = read(), l = read(), r = read();
		auto flip = [&](int x){
			if(st.count(x))
				st.erase(x);
			else
				st.insert(x);
		};
		if(op == 1){
			if(l > 1){
				flip(l - 1);
			}
			if(r < n)
				flip(r);
		}else{
			auto j = st.lower_bound(l);
			print(out[j == st.end() or *j >= r]);
		}
	}
}
```


---

## 作者：__Floze3__ (赞：2)

## 思路简述

看到题目中有着区间修改，区间查询的要求，不难想到此题可以利用线段树通过。

首先，对于一个区间的合法性，反转后并不会改变；同时我们注意到，一个区间的合法性，只与它的两个子区间的合法性，以及左儿子区间最右边的值是否等于右儿子区间最左边的值有关。不难想到，我们的线段树上要维护的是这个区间是否合法，区间最左边的元素的值以及区间最右边的元素的值。

代码如下：

```cpp
struct node {
    // 左端点，右端点，最左边元素的值，最右边元素的值，懒标记
	int l, r, lv, rv, tag; 
	bool islegal; //区间是否合法
} tree[N << 2];
```

那么，我们不难写出 `pushup` 函数:

```cpp
inline void pushup(int p) {
	tree[p].lv = tree[ls].lv, tree[p].rv = tree[rs].rv;
    // 要求为两个子区间都合法，以及左儿子区间最右边的值不等于右儿子区间最左边的值
	if (tree[ls].islegal && tree[rs].islegal && (tree[ls].rv != tree[rs].lv)) tree[p].islegal = true;
	else tree[p].islegal = false;
	return ;
}
```

如果我们需要更新一个区间，我们只需要修改三个值：最左边元素的值，最右边元素的值，懒标记。那么，我们不难想到下放一个懒标记，也只需要更改这三个值即可。那么我们可以写出这样的 `pushdown` 函数以及 `update` 函数。

```cpp
inline void pushdown(int p) {
	if (tree[p].tag) {
		tree[ls].tag ^= 1, tree[rs].tag ^= 1; // 下放标记
		tree[ls].lv ^= 1, tree[ls].rv ^= 1; // 更改区间左右端点元素值
		tree[rs].lv ^= 1, tree[rs].rv ^= 1;
		tree[p].tag = 0; // 清空懒标记
	}
	return ;
} 

void update(int p, int l, int r) {
	if (tree[p].l >= l && tree[p].r <= r) {
		tree[p].tag ^= 1;
		tree[p].lv ^= 1, tree[p].rv ^= 1;
		return ;
	}
	pushdown(p);
	int mid = (tree[p].l + tree[p].r) >> 1;
	if (l <= mid) update(ls, l, r);
	if (r > mid) update(rs, l, r);
	pushup(p);
	return ;
}
```

本题的查询方式比较复杂，不能通过两个子区间是否合法来判断区间是否合法，我们不妨直接返回一段区间，合并后判断这个区间的合法性。代码如下：

```cpp
node query(int p, int l, int r) {
	if (tree[p].l >= l && tree[p].r <= r) return tree[p];
	pushdown(p);
	int mid = (tree[p].l + tree[p].r) >> 1;
	if (r <= mid) return query(ls, l, r); // 查询区间在左儿子下
	else if (l > mid) return query(rs, l, r); // 查询区间在右儿子下
	else { // 需要两端区间合并
		node queryl = query(ls, l, r), queryr = query(rs, l, r);
		node tmp;
		tmp.lv = queryl.lv, tmp.rv = queryr.rv;
		tmp.islegal = (queryl.islegal && queryr.islegal && (queryl.rv != queryr.lv)); // 类似于pushup函数的更新
		return tmp;
	}
}
```

这样的话，我们就能以一种简单的方式解决这个问题。

## 完整代码

[赛时提交记录](https://atcoder.jp/contests/abc341/submissions/50381659)

---

## 作者：QWQ_123 (赞：2)

## 思路：
区间修改，考虑线段树。

然后我们发现两个区间合并若左子树右子树合法，并且中间两个不相同那么他也合法。

所以每个区间就记一下它最左边以及最右边是什么值，以及它是否合法。

然后合并即可。

然后对于区间修改，对一个区间是否合法没有影响，有影响的只有内部的值，所以递归到一个完整的区间时，用 lazy_tag 记一下并将最左边的值，最右边的值翻转即可。

## Code:
赛时代码，写的不好请见谅（

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 500010;

int n, q;
struct Node {
	int l, r;
	int add;
	bool flag = false;
} tr[N << 2];
char s[N];

void pushup(int u) {
	tr[u].l = tr[u << 1].l;
	tr[u].r = tr[u << 1 | 1].r;
	if (tr[u << 1].r == tr[u << 1 | 1].l) tr[u].flag = false;
	else tr[u].flag = tr[u << 1].flag & tr[u << 1 | 1].flag;
}

void pushdown(int u) {
	if (tr[u].add) {
		tr[u << 1].add ^= tr[u].add;
		tr[u << 1 | 1].add ^= tr[u].add;
		tr[u << 1].l ^= 1;
		tr[u << 1].r ^= 1;
		tr[u << 1 | 1].l ^= 1;
		tr[u << 1 | 1].r ^= 1;
		tr[u].add = 0;
	}
}

void build(int u, int l, int r) {
	if (l == r) {
		tr[u].l = tr[u].r = s[l] - '0';
		tr[u].flag = true;
		return;
	}

	int mid = (l + r) >> 1;

	build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);

	pushup(u);
}

void modify(int u, int l, int r, int ql, int qr) {
	if (l >= ql && r <= qr) {
		tr[u].add ^= 1;
		tr[u].l ^= 1;
		tr[u].r ^= 1;
		return;
	}

	pushdown(u);

	int mid = (l + r) >> 1;

	if (ql <= mid) modify(u << 1, l, mid, ql, qr);
	if (qr > mid) modify(u << 1 | 1, mid + 1, r, ql, qr);

	pushup(u);
}

Node query(int u, int l, int r, int ql, int qr) {
	if (l >= ql && r <= qr) {
		return tr[u];
	}

	pushdown(u);
	int mid = (l + r) >> 1;

	if (qr <= mid) return query(u << 1, l, mid, ql, qr);
	else if (ql > mid) return query(u << 1 | 1, mid + 1, r, ql, qr);
	else {
		auto t1 = query(u << 1, l, mid, ql, qr), t2 = query(u << 1 | 1, mid + 1, r, ql, qr);

		Node res;

		res.l = t1.l, res.r = t2.r;

		if (t1.r == t2.l) res.flag = false;
		else res.flag = t1.flag & t2.flag;

		return res;
	}
}

int main() {
	scanf("%d%d%s", &n, &q, s + 1);
	build(1, 1, n);
	for (int i = 1; i <= q; ++i) {
		int opt, l, r;

		scanf("%d%d%d", &opt, &l, &r);

		if (opt == 1) modify(1, 1, n, l, r);
		else puts(query(1, 1, n, l, r).flag ? "Yes" : "No");
	}
	return 0;
}
```

---

## 作者：JuRuoOIer (赞：2)

# 题解 ABC341E Alternating String

### 前排提醒

本题解为**分块**做法，不是线段树。

### 背景

赛时从 $30$ min 过 D 开始就写，一直调到那天十一点半也没过。今天看了 AT 上某大佬的[题解](https://atcoder.jp/contests/abc341/editorial/9333)知道了这种神奇的转化方式，于是发现这是最近刚做的一道[原题](https://www.luogu.com.cn/problem/P3870)。

你没看错，是**原题**！

### 题意

已提交翻译。

给出一个长度为 $n$ 的 01 串 $S$ 和 $m$ 次操作，每次操作可能是：

- `1 l r`：将 $[l,r]$ 中所有位置上的数取反（$1$ 变 $0$，$0$ 变 $1$）。
- `2 l r`：求子串 $[l,r]$ 是否是好串。定义一个 01 串是好串，当且仅当其中任意相邻两个位置上的数不同。特别的，长度为 $1$ 的 01 串是好串。

### 转化问题

题目定义好串为任意相邻两项不相同的串，也就是说它肯定是 `010101...` 或者 `101010...`。于是我们在开始时把所有奇数（或偶数）位的数异或 $1$，好串不就是**所有位置全部相同**的串了吗？

### [原题](https://www.luogu.com.cn/problem/P3870)题解

做过原题的跳过这部分即可。

原题要求支持区间取反和区间求和。如果分块做的话，可以这样想：

- 先复制一份区间加法和区间求和的模板。
- 注意到整块取反会使 `lazy`（块的懒标记）取反，而此时原来的 $1$ 变成 $0$，$0$ 变成 $1$，`sum`（块内元素和）就会变成块长减原来的 `sum`，也就是原来 $0$ 的数量。

然后求和的时候散块肯定暴力，整块具体怎么处理看你修改怎么写的，如果你修改时 `sum` 和 `lazy` 都变化，整块就直接加 `sum` 即可；否则就得判断是否需要串长减 `sum`。这样这题就做完了。

### 本题题解

问题转化完以后，我们发现好串中 $1$ 的数量之和一共两种可能：等于 $0$（全 $0$）或者等于串长（全 $1$）。最重要的是，这两个值**分别只能对应一种情况**（就是刚才说的），这也是为什么**不转化的话不能这么做**的原因。

于是原题改改数组大小、输入输出就过了。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll int
#define ull unsigned long long
#define lf double
#define ld long double
using namespace std;
ll n,m,op,u,v,w,sum[800],bel[500010];
bool a[500010],lazy[800];
//数组记得开够哦~
//注：lazy 改变时 sum 同步改变。
int main(){
	cin>>n>>m;
	ll len=sqrt(n);
	for(int i=0;i<n;i++){//别忘了加输入
		char ch;
		cin>>ch;
		a[i]=ch-'0';
		a[i]^=(i&1);//别忘了所有奇数（或偶数）的位置取反
		bel[i]=i/len;//bel[i] 表示 i 所在的块
		sum[bel[i]]+=a[i];//别忘了维护区间和
	}
	while(m--){
		cin>>op>>u>>v;
		u--;v--;
		if(op==1){//这里改成 1
			if(bel[v]==bel[u]){//l,r 在同一块内，暴力
				for(int i=u;i<=v;i++){
					a[i]^=1;
					if(a[i]^lazy[bel[i]])sum[bel[i]]++;
					else sum[bel[i]]--;
				}
				continue;
			}
			ll l=bel[u]+1,r=bel[v]-1;
			for(int i=l;i<=r;i++){//整块 lazy
				lazy[i]^=1;
				sum[i]=len-sum[i];//我的 sum 跟着 lazy 动
			}
			for(int i=u;bel[i]==bel[u];i++){//散块暴力
				a[i]^=1;
				if(a[i]^lazy[bel[i]])sum[bel[i]]++;
				else sum[bel[i]]--;
			}
			for(int i=v;bel[i]==bel[v];i--){
				a[i]^=1;
				if(a[i]^lazy[bel[i]])sum[bel[i]]++;
				else sum[bel[i]]--;
			}
		}
		else{
			ll ans=0;
			if(bel[v]==bel[u]){//l,r 在同一块内
				for(int i=u;i<=v;i++){
					ans+=a[i]^lazy[bel[i]]; 
				}
				cout<<(ans==0||ans==v-u+1?"Yes":"No")<<endl;//这里别忘了改输出
				continue;
			}
			ll l=bel[u]+1,r=bel[v]-1;
			for(int i=l;i<=r;i++){//整块
				ans+=sum[i];
			}
			for(int i=u;bel[i]==bel[u];i++){//散块
				ans+=a[i]^lazy[bel[i]];
			}
			for(int i=v;bel[i]==bel[v];i--){
				ans+=a[i]^lazy[bel[i]];
			}
			cout<<(ans==0||ans==v-u+1?"Yes":"No")<<endl;
		}
	}
	return 0;
}
```

---

## 作者：CleverPenguin (赞：1)

## 区间修改：我会线段树！

考虑在线段树的每个节点上存储这一段的第一个值，最后一个值，是否为好字符串。
```cpp
struct did{
	int op,fir,las,l,r,lazy;
}e[2000005];
```

接下来是修改操作： \
实际上，如果当前区间被全部包括，并不会对这个串是否是好的造成影响，影响的只有首尾两个值，因为它们要去和其它字符串判断，实际上，所有值都是改变了的，但在这一层节点，只改变了首尾，所以要使用懒标记，在递归到下一层节点时下传。同样，在每回处理完之后，都要更新它是否是好的。
```cpp
void change(int k,int l,int r){
	if(e[k].l>r||e[k].r<l)return ;
	if(e[k].l>=l&&e[k].r<=r){
		e[k].fir^=1;
		e[k].las^=1;
		e[k].lazy++;
		e[k].lazy%=2;
		return ;
	}
	if(e[k].lazy)pd(k);
	change(2*k,l,r);
	change(2*k+1,l,r);
	e[k].fir=e[2*k].fir;
	e[k].las=e[2*k+1].las;
	if(e[2*k].las!=e[2*k+1].fir&&e[2*k].op&&e[2*k+1].op){
		e[k].op=1;
	}else{
		e[k].op=0;
	}
}
```

最后是询问，注意，我们需要存储上一段的最后一个，不能与这一段的相同。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,s[500005],x,y,opt,flag,last,ans;
struct did{
	int op,fir,las,l,r,lazy;
}e[2000005];
char c;
void pd(int k){
	e[k].lazy=0;
	e[2*k].lazy++;
	e[2*k].lazy%=2;
	e[2*k+1].lazy++;
	e[2*k+1].lazy%=2;
	e[2*k].fir^=1;
	e[2*k].las^=1;
	e[2*k+1].fir^=1;
	e[2*k+1].las^=1;
}
void build(int k,int l,int r){
	e[k].l=l;
	e[k].r=r;
	if(l==r){
		e[k].fir=s[l];
		e[k].las=s[l];
		e[k].op=1;
		e[k].lazy=0;
		return ;
	}
	build(2*k,l,(l+r)/2);
	build(2*k+1,(l+r)/2+1,r);
	e[k].fir=e[2*k].fir;
	e[k].las=e[2*k+1].las;
	if(e[2*k].las!=e[2*k+1].fir&&e[2*k].op&&e[2*k+1].op){
		e[k].op=1;
	}else{
		e[k].op=0;
	}
}
void change(int k,int l,int r){
	if(e[k].l>r||e[k].r<l)return ;
	if(e[k].l>=l&&e[k].r<=r){
		e[k].fir^=1;
		e[k].las^=1;
		e[k].lazy++;
		e[k].lazy%=2;
		return ;
	}
	if(e[k].lazy)pd(k);
	change(2*k,l,r);
	change(2*k+1,l,r);
	e[k].fir=e[2*k].fir;
	e[k].las=e[2*k+1].las;
	if(e[2*k].las!=e[2*k+1].fir&&e[2*k].op&&e[2*k+1].op){
		e[k].op=1;
	}else{
		e[k].op=0;
	}
}
void ask(int k,int l,int r){
	if(e[k].l>r||e[k].r<l)return;
	if(e[k].l>=l&&e[k].r<=r){
		if(e[k].op==0)ans=0;
		else if(flag!=0){
			if(last==e[k].fir)ans=0;
		}
		last=e[k].las;
		flag++;
		return ;
	}
	if(e[k].lazy)pd(k);
	ask(2*k,l,r);
	ask(2*k+1,l,r);
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		cin>>c;
		if(c=='1')s[i]=1;
		else s[i]=0;
	}
	build(1,1,n);
	for(int i=1;i<=q;i++){
		scanf("%d%d%d",&opt,&x,&y);
		if(opt==1){
			change(1,x,y);
		}else{
			if(e[1].op){
				printf("Yes\n");
				continue;
			}
			flag=last=0;
			ans=1;
			ask(1,x,y);
			if(ans==1){
				printf("Yes\n");
			}else{
				printf("No\n");
			}
		}
	}
	return 0;
}
```

~~$abc$ 首切 $e$ 题~~

---

## 作者：EityDawn (赞：1)

# 思路
非常浅显的区间合并操作，可以用线段树维护。

怎样向上传递子节点信息？

我们记录一下区间的四个信息：是否是好区间 $flag$ ，区间左右儿子值 $lc,rc$ ，以及区间的懒标记 $tag$。

合并左右区间时，如果左右区间满足都是好区间，且 $rc_{lson} \ne lc_{ron}$ ,则合并出来的区间就是好区间。区间取反估计就无需多讲。

区间询问就得分情况讨论

![](https://cdn.luogu.com.cn/upload/image_hosting/7fqlx195.png?)

像这种情况，我们需要合并左右区间

![](https://cdn.luogu.com.cn/upload/image_hosting/8qtsr1n5.png)

这种情况我们只需要继续朝右区间查找即可

同理，另一种情况也无需我多讲。

看代码。

## code

```cpp
#include<iostream>
using namespace std;
const int N=5e5+10;
struct node{
	bool flag;
	int lc,rc;
	int tag;
} t[N<<2];
char s[N];
#define ls i<<1
#define rs i<<1|1
#define lc(i) t[i].lc
#define rc(i) t[i].rc
#define tag(i) t[i].tag
#define f(i) t[i].flag
void push_up(int i)
{
	f(i)=(f(ls)&&f(rs)&&rc(ls)!=lc(rs));
	lc(i)=lc(ls),rc(i)=rc(rs);//注意上传时更新 lc 和 rc 
}
void addtag(int i)
{lc(i)^=1,rc(i)^=1,tag(i)^=1;}
void push_down(int i)
{
	if(!tag(i)) return;
	addtag(ls),addtag(rs),tag(i)=0;
}
void build(int l,int r,int i)
{
	if(l==r){f(i)=true;lc(i)=rc(i)=s[l]-'0';return;}
	int mid=(l+r)>>1;
	build(l,mid,ls),build(mid+1,r,rs);
	push_up(i);
}
void updata(int p,int q,int l,int r,int i)
{
	if(p<=l&&q>=r){addtag(i);return;}
	push_down(i);
	int mid=(l+r)>>1;
	if(p<=mid) updata(p,q,l,mid,ls);
	if(q>mid) updata(p,q,mid+1,r,rs);
	push_up(i);
}
node merge(node l,node r)//合并左右区间 
{return {l.flag&&r.flag&&l.rc!=r.lc,l.lc,r.rc};}
node query(int p,int q,int l,int r,int i)
{
	if(p<=l&&q>=r) return t[i];
	push_down(i);
	int mid=(l+r)>>1;
	if(q<=mid) return query(p,q,l,mid,ls);//查询对应三种不同情况 
	if(p>mid) return query(p,q,mid+1,r,rs);
	return merge(query(p,q,l,mid,ls),query(p,q,mid+1,r,rs));
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int n,m;
	cin>>n>>m;
	cin>>s+1;
	build(1,n,1);
	while(m--)
	{
		int op,l,r;
		cin>>op>>l>>r;
		if(op&1) updata(l,r,1,n,1);
		else {
			node q=query(l,r,1,n,1);
			if(q.flag) cout<<"Yes\n";
			else cout<<"No\n";
		}
	}
	return 0;
}
```

---

## 作者：zengziqvan (赞：1)

观察发现：对于每个不合法的大区间，其必定有一段子区间不合法。

于是我们就可以用线段树维护，每个子节点维护其当前区间的区间左边的值、区间右边的值、以及一个 bool 类型的是否合法。

对于当前区间：

- 若当前区间为元区间（长度为 $1$），直接合法。

- 否则，若当前区间的左子区间不合法或者右子区间不合法，再或者左子区间的右端点与右子区间的左端点相同，则不合法。

对于区间取反操作只需要写懒标记维护即可。

查询合并的时候还要再合并一次。

时间复杂度 $\operatorname{O}(N\log N)$。

```c++
#include <bits/stdc++.h>
#define FOR(i,l,r) for(int i=l;i<=r;++i)
using namespace std;
const int N=5e5+10;
int n,q;
char s[N];
struct SegmentTree {
	int l,r;
	int che,tag,lnum,rnum;
}t[N<<2];
void push_up(int p) {
	t[p].che=0;
	t[p].che|=(t[p<<1].rnum^t[p<<1|1].lnum^1);
	t[p].che|=t[p<<1].che,t[p].che|=t[p<<1|1].che;
	t[p].lnum=t[p<<1].lnum;
	t[p].rnum=t[p<<1|1].rnum;
}
void push_down(int p) {
	if(t[p].tag) {
		t[p<<1].tag^=1;
		t[p<<1|1].tag^=1;
		t[p<<1].lnum^=1;
		t[p<<1].rnum^=1;
		t[p<<1|1].lnum^=1;
		t[p<<1|1].rnum^=1;
		t[p].tag=0;
	}
}
void Build(int p,int l,int r) {
	t[p].l=l;t[p].r=r;
	if(l==r) {
		t[p].lnum=t[p].rnum=s[l]-'0';
		t[p].che=0;
		return ;
	}
	int mid=l+r>>1;
	Build(p<<1,l,mid);
	Build(p<<1|1,mid+1,r);
	push_up(p);
}
void change(int p,int l,int r) {
	if(l<=t[p].l&&t[p].r<=r) {
		t[p].tag^=1;
		t[p].lnum^=1;
		t[p].rnum^=1;
		return ;
	}
	push_down(p);
	int mid=t[p].l+t[p].r>>1;
	if(l<=mid) change(p<<1,l,r);
	if(r>mid) change(p<<1|1,l,r);
	push_up(p);
}
int ask(int p,int l,int r) {
	if(l<=t[p].l&&t[p].r<=r) return t[p].che;
	push_down(p);
	int mid=t[p].l+t[p].r>>1,val=0;
	if(l<=mid) val|=ask(p<<1,l,r);
	if(r>mid) val|=ask(p<<1|1,l,r);
	if(l<=mid&&r>mid) val|=(t[p<<1].rnum^t[p<<1|1].lnum^1);
	return val;
}
int main(){
	cin>>n>>q;
	scanf("%s",s+1);
	Build(1,1,n);
	while(q--) {
		int op,l,r;
		scanf("%d%d%d",&op,&l,&r);
		if(op==1) change(1,l,r);
		else printf((ask(1,l,r)?"No\n":"Yes\n"));
//		else cout<<ask(1,l,r)<<"\n";
	}
	return 0;
}
```

---

## 作者：Shunpower (赞：1)

## Statement

维护长度为 $n$ 的 01 串 $a$：

1. 区间反转（$a_i\gets a_i\oplus 1$）
2. 定义不存在两个相等的相邻位置的 01 串是好的，查询区间是否好。

$1\leq n,q\leq 5\times 10^5$。

## Solution

线段树板子。

考虑在线段树上维护区间是否好、区间最左端的数、区间最右端的数，后两者容易在 `pushup` 时维护，而区间好的充分必要条件显然是线段树上两个儿子的区间都好，并且左儿子最右端的数不等于右儿子最左端的数，于是区间是否好也能在 `pushup` 时维护。

考虑区间反转。可以发现区间反转不影响对应区间是否好，只需要反转左右端的数就完事了。于是 `pushdown` 下传标记和打标记都是容易的。

剩下的就是线段树区间修改区间查询模板了。

---

## 作者：Genius_Star (赞：1)

~~全场就我一个写平衡树？~~

### 题意：

由 $0$ 和 $1$ 组成的字符串，如果其中两个连续字符总是不同，则称为**好字符串**。  

给你一个长度为 $N$ 的字符串 $S$ ，由 $0$ 和 $1$ 组成。

将给出 $Q$ 个查询，必须按顺序处理。  

查询有两种类型：

- ``1 L R``：取反 $S$ 中 $[L,R]$ 的每个字符；也就是说，对于每个满足 $L\leq i\leq R$ 的整数 $i$，如果 $S$ 的 $i$ 个字符是 $1$，则将其改为 $0$，反之亦然。
- ``2 L R``：判断 $[L,R]$ 范围是否是**好字符串**。

### 思路：

简单题，考虑用 FHQ 平衡树维护。

每个节点维护 $l,r,L,R,data,f,tag$，分别表示：左子树编号；右子树编号；子树最左边字符；子树最右边字符；当前节点字符；子树是否是**好字符串**；取反懒标记。

讲讲 ``pushup`` 的细节处理，主要如下：

$$tr[x].L = \begin{cases} tr[tr[x].l].L & tr[x].l = \emptyset \\ tr[x].data & te[x].l \ne \emptyset\end{cases}$$

$$tr[x].R = \begin{cases} tr[tr[x].r].R & tr[x].r = \emptyset \\ tr[x].data & te[x].r\ne \emptyset\end{cases}$$


然后要判一下中间字符和两个子树右左两边的字符是否相等。

时间复杂度为 $O(N \log N)$。

~~感觉跑的挺慢……~~

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=500500;
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
ll n,q,op,l,r,cnt=0;
char c;
mt19937 R(time(0));
struct Node{
	ll l,r;
	char data,L,R;
	bool f;
	ll key;
	ll siz;
	ll tag;
}X[N];
class FHQ{
public:
	ll root=0;
	void check(char &v){
		if(v=='0')
		  v='1';
		else
		  v='0';
	}
	ll newnode(char v){
		++cnt;
		X[cnt].data=X[cnt].L=X[cnt].R=v;
		X[cnt].key=R();
		X[cnt].siz=1;
		X[cnt].f=1;
		return cnt;
	}
	void pushup(ll k){
		if(X[k].l)
		  X[k].L=X[X[k].l].L;
		else
		  X[k].L=X[k].data;
		if(X[k].r)
		  X[k].R=X[X[k].r].R;
		else
		  X[k].R=X[k].data;
		X[k].siz=X[X[k].l].siz+1ll+X[X[k].r].siz;
		if(X[k].data!=X[X[k].l].R&&X[k].data!=X[X[k].r].L)
		  X[k].f=1;
		else
		  X[k].f=0;
		if(X[k].l)
		  X[k].f&=X[X[k].l].f;
		if(X[k].r)
		  X[k].f&=X[X[k].r].f;
	}
	void reverse(ll k){
		if(!k)
		  return ;
		check(X[k].data);
		check(X[k].L);
		check(X[k].R);
		X[k].tag^=1ll;
	}
	void push_down(ll k){
		if(X[k].tag){
			reverse(X[k].l);
			reverse(X[k].r);
			X[k].tag=0;
		}
	}
	inline void split(ll k,ll v,ll &x,ll &y){
		if(!k){
			x=y=0;
			return ;
		}
		push_down(k);
		if(v>X[X[k].l].siz){
			v-=X[X[k].l].siz+1;
			x=k;
			split(X[k].r,v,X[k].r,y);
		}
		else{
			y=k;
			split(X[k].l,v,x,X[k].l);
		}
		pushup(k);
	}
	inline ll merge(ll x,ll y){
		if(!x||!y)
		  return x+y;
		if(X[x].key<X[y].key){
			push_down(x);
			X[x].r=merge(X[x].r,y);
			pushup(x);
			return x;
		}
		else{
			push_down(y);
			X[y].l=merge(x,X[y].l);
			pushup(y);
			return y;
		}
	}
	void insert(char v){
		root=merge(root,newnode(v));
	}
	void reverse(ll l,ll r){
		ll x,y,z;
		split(root,r,x,z);
		split(x,l-1,x,y);
		reverse(y);
		root=merge(merge(x,y),z);
	}
	ll qurey(ll l,ll r){
		ll x,y,z,ans;
		split(root,r,x,z);
		split(x,l-1,x,y);
		ans=X[y].f;
		root=merge(merge(x,y),z);
		return ans;
	}
}T;
int main(){
	n=read(),q=read();
	for(int i=1;i<=n;i++){
		scanf("%c",&c);
		T.insert(c);
	}
	while(q--){
		op=read(),l=read(),r=read();
		if(op==1)
		  T.reverse(l,r);
		else{
			if(T.qurey(l,r))
			  puts("Yes");
			else
			  puts("No");
		}
	}
	return 0;
}
```


---

## 作者：xiao7_Mr_10_ (赞：1)

题目意思不多赘述，如果您没看建议看完再看这篇题解谢谢。

读完题目思考性质，对于一个区间如果它是一个合法的区间那么如果整个区间进行了取反后它仍然是一个合法的区间，反之如果不是那么取反后也一定不是一个合法的区间。

这就可以使用线段树维护每个区间的答案了，因为我们不在意当前区间反转成了什么样，只在意原先它是否合法，可以合并标记。

讲一下如何判断线段树里一个区间是否合法，很简单，如果线段树内一个区间是合法的那么它的左儿子区间和右儿子区间一定也是合法的，并且左区间的最右端点不等于右区间的最左端点，如果没有满足上述条件则肯定不合法。

所以只需要记录一个区间的最左端点的值和最右端点的值以及该区间是否合法即可，当然还有是否反转的懒标记。

代码如下:　
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n,m,op,l,r;
char x;
int a[N];
struct Point{
	int lval;
	int rval;
	int flag;
	int tag;
}c[N];
void updata(int x){
	c[x].lval=c[x<<1].lval;
	c[x].rval=c[x<<1|1].rval;
	c[x].flag=(bool)(c[x<<1].rval!=c[x<<1|1].lval&&c[x<<1].flag&&c[x<<1|1].flag);
}
void build(int x,int l,int r){
	c[x].tag=0;
	if(l==r){
		c[x].lval=c[x].rval=a[l];
		c[x].flag=1;
		return;
	}
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	updata(x);
}
void pushdown(int x){
	c[x].lval^=1;
	c[x].rval^=1;
	c[x].tag^=1;
}
void down(int x){
	if(c[x].tag){
		pushdown(x<<1);
		pushdown(x<<1|1);
		c[x].tag=0;
	}
}
void change(int x,int l,int r,int s,int t){
	if(l>=s&&r<=t){
		c[x].tag^=1;
		c[x].lval^=1;
		c[x].rval^=1;
		return;
	}
	down(x);
	int mid=(l+r)>>1;
	if(s<=mid)change(x<<1,l,mid,s,t);
	if(t>mid)change(x<<1|1,mid+1,r,s,t);
	updata(x);
}
Point query(int x,int l,int r,int s,int t){
	if(l>=s&&r<=t)return c[x];
	down(x);
	int mid=(l+r)>>1;
	if(t<=mid)return query(x<<1,l,mid,s,t);
	else{
		if(s>mid)return query(x<<1|1,mid+1,r,s,t);
		Point ans,ans1=query(x<<1,l,mid,s,t),ans2=query(x<<1|1,mid+1,r,s,t);
		ans.lval=ans1.lval;
		ans.rval=ans2.rval;
		ans.flag=(bool)(ans1.rval!=ans2.lval&&ans1.flag&&ans2.flag);
		return ans;
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for(int i = 1;i <= n;i++){
		cin >> x;
		a[i]=(int)(x-'0');
	}
	build(1,1,n);
	for(int i = 1;i <= m;i++){
		cin >> op >> l >> r;
		if(op==1){
			change(1,1,n,l,r);
		}
		else{
			Point ans=query(1,1,n,l,r);
			if(ans.flag)cout << "Yes\n";
			else cout << "No\n";
		}
	}
	return 0;
}
```


---

## 作者：Lele_Programmer (赞：1)

# AT_abc341_e 题解

## 题目大意

给定一个 `01` 串，给出两种操作：

1. 选定一个区间，每一位取反，即 $0$ 变成 $1$，$1$ 变成 $0$
2. 选定一个区间，问这个区间里，是否符合每个 $1$ 之间都有一个 $0$，每个 $0$ 之间都有一个 $1$ 这一条件。

## 题目分析

暴力做法，时间复杂度：$O(N^2)$，而 $N \le 5 \times 10^5$，显然会 TLE。

可以开一个数组 $a$，若 $S_{i} \neq S_{i+1}$，则 $a_i = 1$，反之，则 $a_i = 0$，也就是说，$a_i$ 表示 $S_i$ 与 $S_{i+1}$ 是否相同。

举个例子：

样例：$S=10100$，那么 $a=1110$。

这样一来，判断区间 $[l,r]$ 是否符合条件，也就是判断 $S_l$ 到 $S_r$ 之间是否由一个 $0$ 一个 $1$ 一个 $0$ ... 组成，也就是判断 $a_l$ 到 $a_{r-1}$ 之间的每一个数是否都是 $1$。

每次对区间 $[l,r]$ 取反，只会改变 $a$ 中的两个值，即改变 $a_{l-1}$ 与 $a_r$ 两个值。

单点修改，区间查询，显然线段树是非常合适的！

时间复杂度：$O(N \log N)$

一棵可爱的线段树：

```cpp
struct node {
    int l,r; // 节点表示的区间
    int sum; // 区间总和
    int add; // 懒标记（这题可以不用懒标记）
} tr[N*4];
```

pushup 操作：

```cpp
void pushup(int u) { // 本题只需要维护一个 sum 信息
    tr[u].sum=tr[u<<1].sum+tr[u<<1|1].sum;
}
```

pushdown 操作：（如果不用懒标记的话就不需要 pushdown）

```cpp
void pushdown(int u) {
    auto &root=tr[u],&left=tr[u<<1],&right=tr[u<<1|1];
    left.add+=root.add; // 更新左儿子懒标记
    right.add+=root.add; // 更新右儿子懒标记
    left.sum+=(left.r-left.l+1)*root.add; // 更新左子树区间和
    right.sum+=(right.r-right.l+1)*root.add; // 更新右子树区间和
    root.add=0; // 当前懒标记清空
}
```

build 初始化，建立线段树

```cpp
void build(int u,int l,int r) { // 当前节点编号，左界，右界
    if (l==r) tr[u]={l,r,a[l],0}; // 长度为 1，就是叶子节点了
    else {
        tr[u]={l,r,0,0}; // 这里要初始化 l 和 r
        int mid=l+r>>1;
        build(u<<1,l,mid);
        build(u<<1|1,mid+1,r);
        pushup(u); // 子节点信息上传
    }
}
```

modify 区间修改，这题只需要单点修改，所以调用时 $l$ 和 $r$ 是一样的：

```cpp
void modify(int u,int l,int r,int k) {
    if (tr[u].l>=l && tr[u].r<=r) {
        tr[u].sum+=(tr[u].r-tr[u].l+1)*k;
        tr[u].add=k;
    } else {
        pushdown(u); // 下传懒标记
        int mid=tr[u].l+tr[u].r>>1;
        if (l<=mid) modify(u<<1,l,r,k);
        if (r>mid) modify(u<<1|1,l,r,k);
        pushup(u); // 上传子节点信息
    }
}
```

query 查询操作：

```cpp
int query(int u,int l,int r) {
    if (tr[u].l>=l && tr[u].r<=r) return tr[u].sum;
    pushdown(u);
    int mid=tr[u].l+tr[u].r>>1;
    int res=0;
    if (l<=mid) res+=query(u<<1,l,r);
    if (r>mid) res+=query(u<<1|1,l,r);
    return res;
}
```

## 代码

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N=1000005;

int n,q;
string s;
int a[N],pre[N];

struct node {
    int l,r;
    int sum;
    int add;
} tr[N*4];

void pushup(int u) {
    tr[u].sum=tr[u<<1].sum+tr[u<<1|1].sum;
}

void pushdown(int u) {
    auto &root=tr[u],&left=tr[u<<1],&right=tr[u<<1|1];
    left.add+=root.add;
    right.add+=root.add;
    left.sum+=(left.r-left.l+1)*root.add;
    right.sum+=(right.r-right.l+1)*root.add;
    root.add=0;
}

void build(int u,int l,int r) {
    if (l==r) tr[u]={l,r,a[l],0};
    else {
        tr[u]={l,r,0,0};
        int mid=l+r>>1;
        build(u<<1,l,mid);
        build(u<<1|1,mid+1,r);
        pushup(u);
    }
}

void modify(int u,int l,int r,int k) {
    if (tr[u].l>=l && tr[u].r<=r) {
        tr[u].sum+=(tr[u].r-tr[u].l+1)*k;
        tr[u].add=k;
    } else {
        pushdown(u);
        int mid=tr[u].l+tr[u].r>>1;
        if (l<=mid) modify(u<<1,l,r,k);
        if (r>mid) modify(u<<1|1,l,r,k);
        pushup(u);
    }
}

int query(int u,int l,int r) {
    if (tr[u].l>=l && tr[u].r<=r) return tr[u].sum;
    pushdown(u);
    int mid=tr[u].l+tr[u].r>>1;
    int res=0;
    if (l<=mid) res+=query(u<<1,l,r);
    if (r>mid) res+=query(u<<1|1,l,r);
    return res;
}

signed main() {
    scanf("%lld %lld",&n,&q);
    cin>>s;
    for (int i=0;i<n-1;++i) {
        if (s[i]!=s[i+1]) a[i+1]=1;
        else a[i+1]=0;
    }
    build(1,1,n);
    while (q--) {
        int op,b,c;
        scanf("%lld %lld %lld",&op,&b,&c);
        if (op==1) {
            // 这里要判定 b 是否大于等于 2，赛时没想到，WA 了一大片，赛后才调出来
            if (b-1) modify(1,b-1,b-1,a[b-1]?-1:1),a[b-1]^=1;
            modify(1,c,c,a[c]?-1:1),a[c]^=1;
        } else {
            if (b==c) {puts("Yes"); continue;}
            // 区间和 == 区间长度
            if (query(1,b,c-1)==c-1-b+1) puts("Yes");
            else puts("No");
        }
    }
    return 0;
}
```

---

## 作者：_anll_ (赞：1)

~~第一次差点场切 E 题。~~
## 题目大意
给你长度为 $n$ 的 $01$ 串以及 $m$ 次操作。对于操作 $1$，你需要将 $l$ 到 $r$ 之间的 $01$ 串反转。对于操作 $2$，你需要判断 $l$ 到 $r$ 之间的 $01$ 串中连续的两个字符是否总是不同并输出。
## 大体思路
使用线段树进行维护的想法大同小异，这里提供一种单点修改区间查询的想法。

令 $01$ 串为 $s$，我们拿一个数组 $num$ 来存两点之间是否相同。对于 $s_i$ 和 $s_{i+1}$，如果它们相等，那 $num_i=1$，否则 $num_i=0$。

对于操作 $1$，进行反转的区间内部同异是不会发生改变的。举个例子：$0101000$ 反转后会成为 $1010111$，它们对应的 $num$ 均为 $000011$。所以每次操作 $1$ 只会改变 $s_{l-1}$ 和 $s_l$ 以及 $s_r$ 和 $s_{r+1}$ 之间的同异，换言之，只会改变 $num_{l-1}$ 和 $num_r$，而且每次改变必是反转关系。于是只需要用线段树维护单点修改，每次异或一下就好啦。

对于操作 $2$，我们只需要判断 $num_l$ 到 $num_{r-1}$ 之间是否出现过 $1$。如果出现过，就说明存在相邻两点相同的情况，反之亦然。

需要注意的是，因为我们更改的是 $num_{l-1}$，所以可能会涉及到对 $num_0$ 的修改，因此我们建线段树时需要从 $0$ 开始，而不是从 $1$。~~此时因为这个点导致没能场切的某人流下一滴泪水。~~

## 代码演示
大体思路就是这样，如果有不清晰的地方还请结合代码和注释理解。
```cpp
#include<iostream>
#define int long long
#define lc p<<1
#define rc (p<<1)+1
using namespace std;
struct Tr{
	int l,r,sum;
}tr[2000005];
int n,q,num[500005];
string s;
void pushup(int p){
	tr[p].sum=tr[lc].sum+tr[rc].sum;
}
void build(int l,int r,int p){
	tr[p]={l,r,0};
	if(l==r){
		tr[p].sum=num[l];
		return;
	}
	int m=(l+r)/2;
	build(l,m,lc);build(m+1,r,rc);
	pushup(p);
}
void update(int k,int p){
	if(tr[p].l==k&&k==tr[p].r){
		tr[p].sum^=1;
		return;
	}
	int m=(tr[p].l+tr[p].r)/2;
	if(k<=m) update(k,lc);
	if(m<k) update(k,rc);
	pushup(p);
}
int Find(int l,int r,int p){
	if(l<=tr[p].l&&tr[p].r<=r) return tr[p].sum;
	int m=(tr[p].l+tr[p].r)/2,an=0;
	if(l<=m) an+=Find(l,r,lc);
	if(m<r) an+=Find(l,r,rc);
	return an;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int op,l,r;
	cin>>n>>q;
	cin>>s;s='6'+s;
	for(int i=1;i<s.size()-1;i++){
		num[i]=(s[i]==s[i+1]);
	}
	build(0,n,1);//一定一定要从0开始
	while(q--){
		cin>>op>>l>>r;
		if(op==1){
			update(l-1,1);
			update(r,1);
		}
		else{
			int awa=Find(l,r-1,1);
			if(awa) cout<<"No"<<endl;
			else cout<<"Yes"<<endl;
		}
	}
	return 0;
}
```


---

## 作者：2huk (赞：1)

## Problem Statement

给定一个长度为 $n$ 的 $01$ 字符串 $s$。

你需要处理 $Q$ 次询问：

- `1 L R`：将 $S$ 中 $l \sim r$ 的数翻转，即 $0$ 变 $1$，$1$ 变 $0$。
- `2 L R`：问 $S$ 的子串 $l \sim r$ 是否每两个连续字符都不同。

## Solution

我们令 $a_i = s_i \operatorname{xor} s_{i + 1}$，即如果 $s_i = s_{i + 1}$ 则 $a_i = 0$，反之为 $1$。那么如果区间 $[l, r]$ 满足条件相当于每一个 $l \le i < r$ 都满足 $a_i = 1$，即 $\sum_{i = l}^{r - 1} a_i = r - l$。那么询问操作就解决了。

对区间 $[l, r]$ 进行翻转操作，不难发现所有的 $a_i (l \le i < r)$ 都不会发生变化。发生变化的只有两个边界，即  $a_{l - 1}$ 和 $a_r$，显然这两个值会变成它们相反的数。

所以需要维护一颗单点修改（取反）区间求和的线段树，就做完了。

## Code

```cpp
int n, m;
bool s[N];

struct Tree {
	int l, r, s;
}tr[N << 2];

void pushup(int u) {
	tr[u].s = tr[ls].s + tr[rs].s;
}

void build(int u, int l, int r) {
	tr[u] = {l, r};
	if (l == r) tr[u].s = s[l] != s[l + 1];
	else {
		int mid = l + r >> 1;
		build(ls, l, mid), build(rs, mid + 1, r);
		pushup(u);
	}
	return;
}

void modify(int u, int x) {
	if (tr[u].l == tr[u].r) tr[u].s ^= 1;
	else {
		int mid = tr[u].l + tr[u].r >> 1;
		if (x <= mid) modify(ls, x);
		else modify(rs, x);
		pushup(u);
	}
}

int query(int u, int l, int r) {
	if (tr[u].l >= l && tr[u].r <= r) return tr[u].s;
	int mid = tr[u].l + tr[u].r >> 1, res = 0;
	if (l <= mid) res = query(ls, l, r);
	if (r > mid) res += query(rs, l, r);
	return res;
}

signed main()
{
	n = read(), m = read();
	fup (i, 1, n) {
		char c;
		cin >> c;
		s[i] = c == '1';
	}
	
	if (n == 1) {
		while (m -- ) {
			int op = read(), l = read(), r = read();
			if (op == 2) puts("Yes");
		}
		return 0;
	}
	
	build(1, 1, n - 1);
	
	while (m -- ) {
		int op = read(), l = read(), r = read();
		if (op == 1) {
			if (l != 1) modify(1, l - 1);
			if (r != n) modify(1, r);
		}
		else {
			if (l == r || query(1, l, r - 1) == r - l) puts("Yes");
			else puts("No");
		}
	}
	
	return 0;
}
```

---

## 作者：atomic_int (赞：1)

## Statement

一个只包含 `0` 和 `1` 的字符串 $S$，如果其中没有连续的 `0` 或 `1`，则称 $S$ 是好的。

给定一个长度为 $n$ 的只包含 `0` 和 `1` 的字符串 $S$，接下来 $q$ 次操作，有如下两种操作：
- `1 l r` 把 $[l,r]$ 内的数字取反，$0$ 变成 $1$，$1$ 变成 $0$。
- `2 l r` 设 $S'=[S_l S_{l+1} \dots S_r]$，长度为 $r-l+1$，回答 $S'$ 是不是一个好的字符串，如果是则输出 `Yes`，否则输出 `No`。  


数据范围：$1 \le n,q \le 5 \times 10^5$。

## Analysis

我们发现 $S$ 如果本身就不是好的，无论取反多少次也不可能变成好的。

考虑线段树，维护这个区间是否是好的，以及区间两端的值。在合并信息时，如果左儿子和右儿子都是好的，且左儿子的右端点和右儿子的左端点也是不同的，那么这个区间是好的。查询时要记录下三个值：该区间是不是好的、左端点的值、右端点的值，然后判断有没有不好的区间、区间交界处是否有相等的情况。详细细节请看代码。

## Code

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef __int128_t i128;
typedef __uint128_t ui128;
typedef pair<int, int> pii;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<ll, ll> pll;

// const int mod = 1000000007;
const int mod = 998244353;
// const ll inf = 1e18;
const int inf = 1e9;

const int N = 5e5 + 5;

int n, q, a[N];

struct Info {
  int l, r;
  int lv, rv, tag;
  bool ok;
};

struct SegmentTree {
  Info info[N << 2];
  
  #define lson p * 2
  #define rson p * 2 + 1
  
  void pushup(int p) {
    info[p].lv = info[lson].lv, info[p].rv = info[rson].rv;
    if (info[lson].ok && info[rson].ok && (info[lson].rv ^ info[rson].lv) == 1) {
      info[p].ok = true;
    } else {
      info[p].ok = false;
    }
  }
  
  void pushdown(int p) {
    if (info[p].tag) {
      info[lson].lv ^= 1, info[lson].rv ^= 1;
      info[rson].lv ^= 1, info[rson].rv ^= 1;
      info[lson].tag ^= 1, info[rson].tag ^= 1;
      info[p].tag ^= 1;
    }
  }
  
  void build(int p, int l, int r) {
    info[p].l = l, info[p].r = r;
    if (l == r) {
      info[p].lv = a[l], info[p].rv = a[l];
      info[p].ok = true;
      return;
    }
    int mid = (l + r) / 2;
    build(lson, l, mid);
    build(rson, mid + 1, r);
    pushup(p);
  }
  
  void modify(int p, int l, int r) {
    if (l <= info[p].l && r >= info[p].r) {
      info[p].lv ^= 1, info[p].rv ^= 1;
      info[p].tag ^= 1;
      return;
    }
    pushdown(p);
    int mid = (info[p].l + info[p].r) / 2;
    if (l <= mid) modify(lson, l, r);
    if (r > mid) modify(rson, l, r);
    pushup(p);
  }
  
  array<int, 3> query(int p, int l, int r) {
    if (l <= info[p].l && r >= info[p].r) {
      return {info[p].ok, info[p].lv, info[p].rv};
    }
    pushdown(p);
    int mid = (info[p].l + info[p].r) / 2;
    array<int, 3> x = {-1}, y = {-1};
    if (l <= mid) x = query(lson, l, r);
    if (r > mid) y = query(rson, l, r);
    array<int, 3> ans;
    if (x[0] == -1) {
      ans = y;
    } else if (y[0] == -1) {
      ans = x;
    } else {
      ans[1] = x[1], ans[2] = y[2];
      if (x[0] == 1 && y[0] == 1 && (x[2] ^ y[1]) == 1) {
        ans[0] = 1;
      } else {
        ans[0] = 0;
      }
    }
    return ans;
  }
  
  #undef lson
  #undef rson
} tr;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    char c;
    cin >> c;
    a[i] = c - '0';
  }
  tr.build(1, 1, n);
  while (q--) {
    int op, l, r;
    cin >> op >> l >> r;
    if (op == 1) {
      tr.modify(1, l, r);
    } else {
      cout << (tr.query(1, l, r)[0] ? "Yes" : "No") << "\n";
    }
  }

  return 0;
}
```

---

## 作者：MrPython (赞：0)

在我的代码中，下标一般从 0 开始，大部分函数/类的方法最寻左闭右开原则。

------------

我们维护一个布尔数组 $f$，$f_i$ 表示 $S_i$ 与 $S_{i-1}$ 是否相等，相等为 $1$，不相等为 $0$。至于 $f$ 的首项，他对答案不会产生影响，设置成什么都无所谓。

对于操作二，显然 $S$ 中区间 $[L+1,R]$ 元素全部与它前面的值不相同时，字符串是“好的”。只需要判读 $f$ 中这一段区间和是否为 $0$ 就好。

对于操作一，可以发现：$S$ 内部的元素与其前继元素是否相等不会因为区间反转而改变。我们要改变的只有 $f_L$ 与 $f_{R+1}$。

单点修改、区间求和……我会了，树状数组/线段树！
```cpp
#include<bits/extc++.h>
using namespace std;
namespace pbds=__gnu_pbds;
using ui=unsigned int;
using uli=unsigned long long int;
using li=long long int;
template<typename T> class FenwickTree{
    vector<T> tree;
    // To get sum in interval [0,p) (no p).
    T prefix_sum(size_t p){
        T res=0;
        for (--p;p<tree.size();--(p&=(p+1))) res+=tree[p];
        return res;
    }
public:
    FenwickTree(size_t n):tree(n){}
    void add(size_t p,T const& val){
        for (;p<tree.size();p|=p+1) tree[p]+=val;
    }
    T get_sum(size_t l,size_t r){
        return prefix_sum(r)-prefix_sum(l);
    }
    T get(size_t p){return get_sum(p,p+1);}
};
int main(void){
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    size_t n,m;cin>>n>>m;
    vector<bool> a(n);
    for (vector<bool>::reference i:a){char c;cin>>c;i=c=='1';}
    FenwickTree<ui> same_as_prev(n);
    for (size_t i=1;i<n;++i) same_as_prev.add(i,a[i]==a[i-1]);
    while (m--){
        char op;size_t l,r;cin>>op>>l>>r;
        if (op=='1')
            same_as_prev.add(l-1,same_as_prev.get(l-1)?-1:1),
            same_as_prev.add(r,same_as_prev.get(r)?-1:1);
        else if (op=='2')
            cout<<(same_as_prev.get_sum(l,r)?"No\n":"Yes\n");
        else throw;
    }
    return 0;
}
```

---

## 作者：zzk2010 (赞：0)

我们定义一个数组 $a$，其中如果 $S_i$ 等于 $S_{i+1}$，那么 $a_i = 1$，否则 $a_i = 0$。形象一点的说，这个 $a$ 数组就像是“插”在两个字符之间，判断它们是否相等。

这么一来，对于区间 $L,R$，$S_{L..R}$ 是一个合法的字符串，当且仅当 $a_L+a_{L+1}+\cdots+a_{R-1} = 0$ （注意这里是 $a_{R-1}$ 而不是 $a_R$）。

代码中，我们用树状数组 $bit$ 维护 $a$ 数组的前缀和，那么 $2$ 操作就相当于询问 $query(R-1)-query(L-1)$ 是否等于 $0$。

那 $1$ 操作怎么办呢？不妨想一下 $1$ 操作会对 $a$ 数组产生什么影响。对于 $S_{L..R}$，内部的 $01$ 反转并不会对内部的 $a$ 数组的值造成影响——相邻的两个字符，该一样的还是一样，该不一样的还是不一样。对于 $S_{1..L-1}$ 和 $S_{R+1..N}$ 同理。

所以真正改变的 $a$ 数组的值是在**交界处**，也就是 $a_{L-1}$ （判断 $S_{L-1}$ 和 $S_{L}$ 是否相等）和 $a_R$ （判断 $S_R$ 和 $S_{R+1}$ 是否相等）。**更进一步的，其实就是反转了 $a_{L-1}$ 和 $a_{R}$ 的值——原本一样的，其中一个反转后就不一样了，反之亦然。**

然后就是简单的实现，注意 $1$ 操作中 $L=1$ 的特判，改 $a_0$ 没有意义，但改了的话这个树状数组的写法会超时。

不懂可以配合代码食用：

```cpp
#include <bits/stdc++.h>
#define int long long
#define N 500005
using namespace std;
char s[N];
int bit[N], a[N], n, q;
void add(int x, int v) {
	while (x < N) bit[x] += v, x += x & -x;
	return;
}
int query(int x) {
	int res = 0;
	while (x) res += bit[x], x -= x & -x;
	return res;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n >> q >> (s+1);
	for(int i = 2; i <= n; i++) if (s[i-1] == s[i]) add(i-1, 1), a[i-1] = 1;
	for(int i = 1, op, l, r; i <= q; i++) {
		cin >> op >> l >> r;
		if (op == 1) {
			if (a[l-1] == 1) add(l-1, -1), a[l-1] = 0;
			else if (l != 1) add(l-1, 1), a[l-1] = 1;
			if (a[r] == 1) add(r, -1), a[r] = 0;
			else add(r, 1), a[r] = 1;
		}
		else {
			int res = query(r-1)-query(l-1);
			if (res == 0) cout << "Yes\n";
			else cout << "No\n";
		}
	}
	return 0;
}
```

---

## 作者：kczw (赞：0)

# 题意
给定一个长为 $N$ 的由 $0$ 及 $1$ 组成的序列和 $Q$ 次操作。

操作一将区间 $[l,r]$ 的元素异或 $1$，操作二询问区间 $[l,r]$ 内相邻元素是否两两不相等。
# 思路
这里我选择用线段树维护，分别维护：

- 区间的左右端点位置（若使用代参写法则不用维护）
- 区间的左右端点元素
- 区间是否保证相邻元素两两不相等
- 区间修改的懒标记

每次合并信息时：
- 根据左右儿子区间左右端点元素更新父亲区间左右端点元素
- 根据左右儿子区间是否满足相邻元素是否两两不相等更新父亲节点

然后将上述内容代入线段树，需要注意的是在查询时左右儿子区间的信息不一定全部需要，可能需要查询的区间刚好只需要某一个儿子区间，这个时候便不需要判断两儿子区间相邻元素是否相当了。

最后放上代码。
# 实现
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
struct tree{int l,r,lz,im,L,R;}tr[N<<2];
int n,q;
char c[N];
inline void pushup(int p){
    tr[p].L=tr[p<<1].L;
    tr[p].R=tr[p<<1|1].R;
    if(tr[p<<1].im&&tr[p<<1|1].im&&tr[p<<1].R!=tr[p<<1|1].L)
        tr[p].im=1;
    else 
        tr[p].im=0;
}
inline void build(int p,int l,int r){
    tr[p]={l,r,0,0};
    if(l==r){
        tr[p].L=tr[p].R=c[l]-'0';
        tr[p].im=1;
        return;
    }
    build(p<<1,l,l+r>>1);
    build(p<<1|1,(l+r>>1)+1,r);
    pushup(p);
}
inline void uplz(int p){
    tr[p].L^=1;
    tr[p].R^=1;
    tr[p].lz^=1;
}
inline void pushdown(int p){
    if(tr[p].lz){
        uplz(p<<1);
        uplz(p<<1|1);
        tr[p].lz=0;
    }
}
int op,l,r;
inline void modify(int p){
    if(tr[p].l>r||tr[p].r<l)
        return;
    if(l<=tr[p].l&&tr[p].r<=r)
        return uplz(p);
    pushdown(p);
    modify(p<<1);
    modify(p<<1|1);
    pushup(p);
}
inline bool query(int p){
    if(tr[p].l>r||tr[p].r<l)
        return 1;
    if(l<=tr[p].l&&tr[p].r<=r)
        return tr[p].im;
    pushdown(p);
    return query(p<<1)&&query(p<<1|1)&&(tr[p<<1].R!=tr[p<<1|1].L||(tr[p<<1].l>r||tr[p<<1].r<l||tr[p<<1|1].l>r||tr[p<<1|1].r<l));
}
int main(){
    scanf("%d%d%s",&n,&q,c+1);
    build(1,1,n);
    for(int i=1;i<=q;i++){
        scanf("%d%d%d",&op,&l,&r);
        if(op==1)
            modify(1);
        else 
            printf(query(1)?"Yes\n":"No\n");
    }
    return 0;
}
```

---

## 作者：No_Rest (赞：0)

## 思路

一眼线段树题。甚至没看到翻译（~~主要是 ABC E 出多少次线段树了~~）。

法一：

赛时做法。

我们可以维护一个区间的左端点，右端点和区间是否是好的。

那么易知若当前区间左儿子区间和右儿子区间都是好的，且左儿子的右端点和右儿子的左端点不一样，那么当前区间也是好的。

懒标记下传时，要修改左右儿子区间的左右端点，但不会影响左右儿子区间是否为好的。

用一个区间修改区间查询的线段树维护即可，时间复杂度 $\mathcal O(q \log n)$，代码长度 $1.8$ KB。

优点：暴力，好想。

法二：

实现更为简单的做法。

让线段树维护 $a_i \oplus a_{i-1}$，这样如果一个区间 $[l,r]$ 是好的，那么线段树中 $[l + 1, r]$ 的总和就等于 $r - l$。

对于修改，易知只有线段树中 $l$ 和 $r + 1$ 的两个位置需要修改。

这样只用一棵单点修改区间查询的线段树即可，时间复杂度 $\mathcal O(q \log n)$，代码长度 $1.6$ KB。

注意修改和 $n = 1$ 时需要特判。

优点：代码短，单点修改更为好调。

法三：

更为巧妙的做法。

输入时让 $a_i \gets a_i \oplus (i \bmod 2)$，这样一个好的区间 $[l, r]$ 的总和就是 $0$ 或 $r - l + 1$。

这样用一个区间异或区间查询的线段树板子维护即可，时间复杂度 $\mathcal O(q \log n)$，代码长度 $1.65$ KB。

优点：直接复制板子，不用多调。

## 代码

法一：

```cpp
#include<iostream>
#define ls x << 1
#define rs x << 1 | 1
using namespace std;
typedef long long ll;
const ll maxn = 5e5 + 5;
ll read(){
	char ch;
	ll f = 0, r = 0;
	ch = getchar();
	while(ch > '9' || ch < '0') f |= ch == '-', ch = getchar();
	while(ch <= '9' && ch >= '0') r = (r << 3) + (r << 1) + (ch ^ 48), ch = getchar();
	return f ? -r : r;
}
struct st{
	ll l, r, L, R, flag, tag;
}t[maxn << 2];
ll n = read(), q = read();
string s;
void pushup(ll x){ t[x].L = t[ls].L, t[x].R = t[rs].R, t[x].flag = (t[ls].flag && t[rs].flag && t[ls].R ^ t[rs].L); }
void build(ll x, ll l, ll r){
	t[x].l = l, t[x].r = r;
	if(l == r){
		t[x].L = t[x].R = s[l] - '0', t[x].flag = 1;
		return;
	}
	ll mid = (l + r) >> 1;
	build(ls, l, mid), build(rs, mid + 1, r);
	pushup(x);
}
void pushdown(ll x){
	if(t[x].tag){
		t[ls].L ^= 1, t[ls].R ^= 1, t[rs].L ^= 1, t[rs].R ^= 1;
		t[ls].tag ^= 1, t[rs].tag ^= 1;
		t[x].tag = 0;
	}
}
void update(ll x, ll l, ll r){
	if(l <= t[x].l && t[x].r <= r){
		t[x].L ^= 1, t[x].R ^= 1, t[x].tag ^= 1;
		return;
	}
	pushdown(x);
	ll mid = (t[x].l + t[x].r) >> 1;
	if(l <= mid) update(ls, l, r);
	if(r > mid) update(rs, l, r);
	pushup(x);
}
st query(ll x, ll l, ll r){
	if(l <= t[x].l && t[x].r <= r) return t[x];
	pushdown(x);
	ll mid = (t[x].l + t[x].r) >> 1;
	st ans, lans, rans;
	if(r <= mid) return query(ls, l, r);
	if(l > mid) return query(rs, l, r);
	lans = query(ls, l, r), rans = query(rs, l, r);
	ans.L = lans.L, ans.R = rans.R, ans.flag = (lans.flag && rans.flag && lans.R ^ rans.L);
	return ans;
}
int main(){
	cin >> s;
	s = ' ' + s;
	build(1, 1, n);
	for(ll op, l, r; q; --q){
		op = read(), l = read(), r = read();
		if(op == 1) update(1, l, r);
		else puts(query(1, l, r).flag ? "Yes" : "No");
	}
    return 0;
}
```

法二：

```cpp
#include<iostream>
#define ls x << 1
#define rs x << 1 | 1
using namespace std;
typedef long long ll;
const ll maxn = 5e5 + 5;
ll read(){
	char ch;
	ll f = 0, r = 0;
	ch = getchar();
	while(ch > '9' || ch < '0') f |= ch == '-', ch = getchar();
	while(ch <= '9' && ch >= '0') r = (r << 3) + (r << 1) + (ch ^ 48), ch = getchar();
	return f ? -r : r;
}
struct st{
	ll l, r, sum;
}t[maxn << 2];
ll n = read(), q = read(), a[maxn];
void pushup(ll x){ t[x].sum = t[ls].sum + t[rs].sum; }
void build(ll x, ll l, ll r){
	t[x].l = l, t[x].r = r;
	if(l == r){
		t[x].sum = a[l] ^ a[l - 1];
		return;
	}
	ll mid = (l + r) >> 1;
	build(ls, l, mid), build(rs, mid + 1, r);
	pushup(x);
}
void update(ll x, ll id){
	if(t[x].l == t[x].r){
		t[x].sum ^= 1;
		return;
	}
	ll mid = (t[x].l + t[x].r) >> 1;
	if(id <= mid) update(ls, id);
	else update(rs, id);
	pushup(x);
}
ll query(ll x, ll l, ll r){
	if(l <= t[x].l && t[x].r <= r) return t[x].sum;
	ll ans = 0, mid = (t[x].l + t[x].r) >> 1;
	if(l <= mid) ans += query(ls, l, r);
	if(r > mid) ans += query(rs, l, r);
	return ans;
}
int main(){
	for(ll i = 1; i <= n; ++i) scanf("%1lld", &a[i]);
	if(n == 1){//n = 1 时无论如何都是好的
		for(ll op, l, r; q; --q){
			op = read(), l = read(), r = read();
			if(op == 2) puts("Yes");
		}
	}
	build(1, 1, n);
	for(ll op, l, r; q; --q){
		op = read(), l = read(), r = read();
		if(op == 1){
			update(1, l);
			if(r < n) update(1, r + 1);//特判
		} else puts(query(1, l + 1, r) == r - l ? "Yes" : "No");//如果 [l + 1, r] 的总和等于 r - l
	}
    return 0;
}
```

法三：

```cpp
#include<iostream>
#define ls x << 1
#define rs x << 1 | 1
using namespace std;
typedef long long ll;
const ll maxn = 5e5 + 5;
ll read(){
	char ch;
	ll f = 0, r = 0;
	ch = getchar();
	while(ch > '9' || ch < '0') f |= ch == '-', ch = getchar();
	while(ch <= '9' && ch >= '0') r = (r << 3) + (r << 1) + (ch ^ 48), ch = getchar();
	return f ? -r : r;
}
struct st{
	ll l, r, sum, tag;
}t[maxn << 2];
ll n = read(), q = read(), a[maxn];
void pushup(ll x){ t[x].sum = t[ls].sum + t[rs].sum; }
void build(ll x, ll l, ll r){
	t[x].l = l, t[x].r = r;
	if(l == r){
		t[x].sum = a[l] ^ (l & 1);//维护 a[i] ^ (i & 1)
		return;
	}
	ll mid = (l + r) >> 1;
	build(ls, l, mid), build(rs, mid + 1, r);
	pushup(x);
}
void pushdown(ll x){
	if(t[x].tag){
		t[ls].sum = t[ls].r - t[ls].l + 1 - t[ls].sum, t[rs].sum = t[rs].r - t[rs].l + 1 - t[rs].sum;
		t[ls].tag ^= 1, t[rs].tag ^= 1;
		t[x].tag = 0;
	}
}
void update(ll x, ll l, ll r){
	if(l <= t[x].l && t[x].r <= r){
		t[x].sum = t[x].r - t[x].l + 1 - t[x].sum, t[x].tag ^= 1;
		return;
	}
	pushdown(x);
	ll mid = (t[x].l + t[x].r) >> 1;
	if(l <= mid) update(ls, l, r);
	if(r > mid) update(rs, l, r);
	pushup(x);
}
ll query(ll x, ll l, ll r){
	if(l <= t[x].l && t[x].r <= r) return t[x].sum;
	pushdown(x);
	ll ans = 0, mid = (t[x].l + t[x].r) >> 1;
	if(l <= mid) ans += query(ls, l, r);
	if(r > mid) ans += query(rs, l, r);
	return ans;
}
int main(){
	for(ll i = 1; i <= n; ++i) scanf("%1lld", &a[i]);
	build(1, 1, n);
	for(ll op, l, r; q; --q){
		op = read(), l = read(), r = read();
		if(op == 1) update(1, l, r);
		else puts(!query(1, l, r) || query(1, l, r) == r - l + 1  ? "Yes" : "No");//如果 [l, r] 的总和等于 0 或 r - l + 1，那么它是好的
	}
    return 0;
}
```

---

## 作者：lhc0707 (赞：0)

这是一种线段树做法。个人认为比较好想。

对于线段树每个节点，维护区间右端点类型，左端点类型，以及区间是否是好的。合并的时候，如果左儿子或右儿子不是好的，那这个大的节点肯定也不是好的；如果两个儿子都是好的，大的节点是好的区间的条件是左儿子的右端点和右儿子的左端点不同。所谓区间修改，其实救是区间异或，打个标记就行了。

场上 AC 代码，比较丑陋。

```cpp
#include<iostream>
#include<string>
using namespace std;
const int N=5e5+10;
int n,q,a[N];
string s;
struct Node{
	int l,r,tag;
	bool ok;
}t[N<<2];
Node push_up(Node l,Node r)
{
	Node res;
	res.l=l.l,res.r=r.r;
	res.ok=l.ok and r.ok;
	if(l.r==r.l)res.ok=false;
	return res;
}
void build(int p,int pl,int pr)
{
	if(pl==pr)
	{
		t[p].l=t[p].r=a[pl];
		t[p].ok=true;
		return;
	}
	int mid=(pl+pr)>>1;
	build(p*2,pl,mid);
	build(p*2+1,mid+1,pr);
	t[p]=push_up(t[p*2],t[p*2+1]);
} 
void push_down(int p,int pl,int pr)
{
	if(!t[p].tag)return ;
	t[p*2].tag^=t[p].tag;
	t[p*2].l^=t[p].tag,t[p*2].r^=t[p].tag;
	t[p*2+1].tag^=t[p].tag;
	t[p*2+1].l^=t[p].tag,t[p*2+1].r^=t[p].tag;
	t[p].tag=0;
}
void update(int p,int pl,int pr,int L,int R)
{
	if(L<=pl&&pr<=R){t[p].tag^=1,t[p].l^=1,t[p].r^=1;return;}
	int mid=(pl+pr)>>1;push_down(p,pl,pr);
	if(L<=mid)update(p*2,pl,mid,L,R);
	if(R>mid)update(p*2+1,mid+1,pr,L,R);
	t[p]=push_up(t[p*2],t[p*2+1]);
}
Node query(int p,int pl,int pr,int L,int R)
{
	if(L<=pl&&pr<=R)return t[p];
	int mid=(pl+pr)>>1;push_down(p,pl,pr);
	if(R<=mid)return query(p*2,pl,mid,L,R);
	else if(L>mid)return query(p*2+1,mid+1,pr,L,R);
	else return push_up(query(p*2,pl,mid,L,R),query(p*2+1,mid+1,pr,L,R));
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>q>>s;
	for(int i=1;i<=n;i++)a[i]=s[i-1]-'0';
	build(1,1,n);
	while(q--)
	{
		int op,l,r;
		cin>>op>>l>>r;
		if(op==1)update(1,1,n,l,r);
		else
		{
			Node res=query(1,1,n,l,r);
			if(res.ok)cout<<"Yes\n";
			else cout<<"No\n";
		}
	}
	return 0;
}
```

望过审。

---

## 作者：int_R (赞：0)

[原题链接](https://www.luogu.com.cn/problem/AT_abc341_e)

普通的做法没啥意思，考虑维护 $b_i=[a_i\not=a_{i+1}]$。

区间取反只会取反 $b_{l-1}$ 和 $b_r$，相当于单点修改。

判断区间是否合法就是判断 $\forall i\in[l,r-1],b_i=1$，就是求一段区间是不是全是 $1$，区间查询 $1$ 的个数判断。

单点修改，区间查询，树状数组。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=5e5+10;
int n,q,a[MAXN],t[MAXN];char c[MAXN];
inline int lowbit(int x){return x&(-x);}
inline void change(int x,int a)
{
    while(x<=n)
        t[x]+=a,x+=lowbit(x);
    return ;
}
inline int query(int x)
{
    int ans=0;
    while(x)
        ans+=t[x],x-=lowbit(x);
    return ans;
}
int main()
{
#ifdef ONLINE_JUDGE
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);
#endif
    cin>>n>>q;
    for(int i=1;i<=n;++i) cin>>c[i];
    for(int i=1;i<n;++i)
        a[i]=(c[i]!=c[i+1]),change(i,a[i]);
    while(q--)
    {
        int opt,l,r;cin>>opt>>l>>r;
        if(opt==1)
        {
            if(l>1)
            {
                change(l-1,-a[l-1]);
                a[l-1]^=1;
                change(l-1,a[l-1]);
            }
            if(r<n)
            {
                change(r,-a[r]);
                a[r]^=1;
                change(r,a[r]);
            }
        }
        else
        {
            cout<<((l==r||query(r-1)-query(l-1)==r-l)?"Yes":"No")<<'\n';
        }
    }
    return 0;
}
```


---

## 作者：Night_sea_64 (赞：0)

来一种很不同的**树状数组**做法 qwq。

考虑维护每相邻两个字符是否相同。$a_i$ 表示 $s_i$ 与 $s_{i-1}$ 是否相同（$s$ 下标从 $1$ 开始）。为 $0$ 表示相同，为 $1$ 表示不相同。

发现在取反一段区间时，只有 $a_l$ 和 $a_{r+1}$ 会改变。查询一段区间时只需要判断 $\sum\limits_{i=l+1}^ra_i$ 是否等于 $r-l$ 即可。于是这个可以用树状数组维护！

```cpp
#include<iostream>
using namespace std;
int n,q;
int a[500010];
int lowbit(int x)
{
  return x&(-x);
}
void pre()
{
  for(int i=2;i<=n;i+=2)
  {
      int mul=1,x=lowbit(i);
      while(mul<x)a[i]+=a[i-mul],mul<<=1;
  }
}
void add(int x,int k)
{
  while(x<=n)a[x]+=k,x+=lowbit(x);
}
int query(int x)
{
  int sum=0;
  while(x)sum+=a[x],x-=lowbit(x);
  return sum;
}
int main()
{
  cin>>n>>q;
  string s;
  cin>>s;
  s=' '+s;
  for(int i=2;i<=n;i++)
    a[i]=(s[i]!=s[i-1]);
  pre();
  while(q--)
  {
    int op,l,r;
    cin>>op>>l>>r;
    if(op==1)
    {
      if(query(l)-query(l-1))add(l,-1);
      else add(l,1);
      if(query(r+1)-query(r))add(r+1,-1);
      else add(r+1,1);
    }
    else
    {
      if(query(r)-query(l)==r-l)cout<<"Yes"<<endl;
      else cout<<"No"<<endl;
    }
  }
  return 0;
}
```

---

## 作者：yyrwlj (赞：0)

## 题意简述

给定一个 $01$ 序列，每次要么将一段区间内取反，要么查询区间内有没有 $00$ 或者 $11$ 这样的子段。

## 思路

区间问题，考虑使用线段树维护。

区间取反是一道经典的线段树题：[开关](https://www.luogu.com.cn/problem/P3870)。maketag 时将懒标记取反，也就是异或 $1$。

再考虑处理查询，合并答案时不能只看两个子树内部的答案，还要看左子树的右端点跟右子树的左端点相不相同。

pushup 两个端点信息就很简单了，左端点就是左子树的左端点，右端点就是右子树的右端点。

maketag 时，不要忘记将节点的左右端点取反。

这个过程很像一道线段树维护区间最大子段和的题目：[小白逛公园](https://www.luogu.com.cn/problem/P4513)。

那么这道题目就通过合并两道经典题目的做法解决了。

## Code

```cpp
#include <iostream>
using namespace std;
const int N = 2000005;
int tag[N];
char s[500005], lc[N], rc[N];
bool yes[N];
inline void maketag(int u)
{
    tag[u] ^= 1;
    if (lc[u] == '0')
        lc[u] = '1';
    else
        lc[u] = '0';
    if (rc[u] == '0')
        rc[u] = '1';
    else
        rc[u] = '0';
}
inline void pushup(int u)
{
    yes[u] = yes[u << 1] && yes[u << 1 | 1] && (rc[u << 1] != lc[u << 1 | 1]);
    lc[u] = lc[u << 1];
    rc[u] = rc[u << 1 | 1];
}
inline void pushdown(int u)
{
    maketag(u << 1);
    maketag(u << 1 | 1);
    tag[u] = 0;
}
void build(int u,int l,int r)
{
    if (l == r)
    {
        lc[u] = rc[u] = s[l];
        yes[u] = true;
        return;
    }
    int mid = (l + r) >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    pushup(u);
}
void update(int u,int l,int r,int L,int R)
{
    if (L <= l && r <= R)
    {
        maketag(u);
        return; 
    }
    int mid = (l + r) >> 1;
    if (tag[u])
        pushdown(u);
    if (L <= mid)
        update(u << 1, l, mid, L, R);
    if (mid < R)
        update(u << 1 | 1, mid + 1, r, L, R);
    pushup(u);
}
bool query(int u,int l,int r,int L,int R)
{
    if (L <= l && r <= R)
        return yes[u];
    int mid = (l + r) >> 1;
    bool ans = true;
    if (tag[u])
        pushdown(u);
    if (R <= mid)
        return query(u << 1, l, mid, L, R);
    if (mid < L)
        return query(u << 1 | 1, mid + 1, r, L, R);
    return query(u << 1, l, mid, L, R) && query(u << 1 | 1, mid + 1, r, L, R) && (rc[u << 1] != lc[u << 1 | 1]);
}
int main()
{
    int n, q;
    scanf("%d%d%s", &n, &q, s + 1);
    build(1, 1, n);
    while (q--)
    {
        int op, l, r;
        scanf("%d%d%d", &op, &l, &r);
        if (op == 1)
            update(1, 1, n, l, r);
        else
        {
            if (query(1, 1, n, l, r))
                puts("Yes");
            else
                puts("No");
        }
    }
    return 0;
}
```

---

## 作者：xz001 (赞：0)

首先一段区间合法仅当区间最长连续 $1$ 和最长连续 $0$ 长度均小于等于 $1$。

所以我们用线段树维护，维护区间最长前缀 $1$，最长前缀 $0$，最长后缀 $1$，最长后缀 $0$，最长 $1$，最长 $0$，维护一个懒标记表示区间是否进行了 $01$ 翻转。

合并两个区间代码：

```cpp
void push_up (int p) {
	t[p].lm0 = (t[ls(p)].lm0 == t[ls(p)].r - t[ls(p)].l + 1) ? t[ls(p)].lm0 + t[rs(p)].lm0 : t[ls(p)].lm0;  //最长前缀 0
	t[p].rm0 = (t[rs(p)].rm0 == t[rs(p)].r - t[rs(p)].l + 1) ? t[rs(p)].rm0 + t[ls(p)].rm0 : t[rs(p)].rm0;  //最长后缀 0
	t[p].lm1 = (t[ls(p)].lm1 == t[ls(p)].r - t[ls(p)].l + 1) ? t[ls(p)].lm1 + t[rs(p)].lm1 : t[ls(p)].lm1;  //最长前缀 1
	t[p].rm1 = (t[rs(p)].rm1 == t[rs(p)].r - t[rs(p)].l + 1) ? t[rs(p)].rm1 + t[ls(p)].rm1 : t[rs(p)].rm1;  //最长后缀 1
	t[p].m0  = max(max(t[ls(p)].m0, t[rs(p)].m0), t[ls(p)].rm0 + t[rs(p)].lm0);   //最长 0
	t[p].m1  = max(max(t[ls(p)].m1, t[rs(p)].m1), t[ls(p)].rm1 + t[rs(p)].lm1);   //最长 1
	return;
}
```

打懒标记代码：

```cpp
void lazy_tag (int p) { //01 翻转就是交换 01 的信息
	swap(t[p].lm0, t[p].lm1);
	swap(t[p].rm0, t[p].rm1);
	swap(t[p].m0 , t[p].m1 );
	t[p].fz ^= 1;
	return;
}
```

询问比较特殊，我们没办法直接合并，所以我们可以利用线段树询问时的顺序是从左到右的，维护四个全局变量，分别为后缀最长 $0$，区间最长 $0$，后缀最长 $1$，区间最长 $1$，对于每个被访问到的完全覆盖的区间，更新即可。

```cpp
int rm0, len0, rm1, len1;

void query (int l, int r, int p) {
	if (l <= t[p].l && t[p].r <= r) {
		len0 = max(max(len0, t[p].m0), rm0 + t[p].lm0);
		len1 = max(max(len1, t[p].m1), rm1 + t[p].lm1);
		rm0 = (t[p].rm0 == t[p].r - t[p].l + 1) ? rm0 + t[p].rm0 : t[p].rm0;
		rm1 = (t[p].rm1 == t[p].r - t[p].l + 1) ? rm1 + t[p].rm1 : t[p].rm1;
		len0 = max(len0, rm0);
		len1 = max(len1, rm1);
		return;
	}
	push_down(p);
	int mid = (t[p].l + t[p].r) >> 1;
	if (l <= mid) query (l, r, ls(p));
	if (r >  mid) query (l, r, rs(p));
	return;
}
```

时间复杂度 $O(n\log n)$。

赛时代码：[https://atcoder.jp/contests/abc341/submissions/50370606](https://atcoder.jp/contests/abc341/submissions/50370606)

---

## 作者：aaron0919 (赞：0)

# [AT_abc341_e の题解](https://www.luogu.com.cn/problem/AT_abc341_e)

### 理性分析

我们可以用一种类似差分的思路来做：对于每个位置，我们记录它和下一个一不一样，如果我们更改，只需要将头和尾修改一下。

线段树维护，$O(n\log n)$ 的复杂度。

### code

```cpp
#include <bits/stdc++.h>
#include <atcoder/segtree>
using namespace std;
using namespace atcoder;
using ll = long long;

const int N = 5e5 + 10;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;

int op(int a, int b)
{
    return a + b;
}

int e()
{
    return 0;
}

int n, q;
char s[N];
int x, l, r;

int main(void)
{
    scanf("%d%d", &n, &q);
    scanf("%s", s);
    segtree<int, op, e> seg(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        if (s[i] != s[i + 1])
        {
            seg.set(i + 1, 1);
        }
    }
    for (int i = 0; i < q; i++)
    {
        scanf("%d%d%d", &x, &l, &r);
        if (x == 1)
        {
            seg.set(l - 1, 1 - seg.get(l - 1));
            seg.set(r, 1 - seg.get(r));
        }
        else
        {
            if (seg.prod(l, r) == (r - l))
            {
                puts("Yes");
            }
            else
            {
                puts("No");
            }
        }
    }
    return 0;
}
```

---

## 作者：HappyJaPhy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc341_e)

[原题传送门](https://atcoder.jp/contests/abc341/tasks/abc341_e)

# 题意

给出长为 $n$ 的 `01` 串，如果一个子串 `01` 交替出现，则称其为“好的”。有 $q$ 次询问，把 $[x,y]$ 中的每一位反转或者询问 $[x,y]$ 是否是“好的”。

# 分析

一眼线段树。

用线段树维护区间是否是“好的”，每个节点维护最左段和最右端的值，`pushup` 和 `query` 向上合并区间时判断即可。

下面的代码有比较详细的注释，具体看代码即可，看不懂可以画图辅助理解。

# 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define N 500005
using namespace std;
int n, q, a[N];

inline int read(int &x) {
	char ch = x = 0;
	int m = 1;
	while (ch < '0' || ch > '9') {
		ch = getchar();
		if (ch == '-') m *= -1;
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + ch - 48;
		ch = getchar();
	}
	x *= m;
	return x;
}

struct node {
	int l, r, lval, rval, tag, isg;
};

struct segtre {
	node tre[N << 1]; //动态开点节省空间
	int root, tot;
	inline void pushup(int rt) { //合并两个区间
		int l = tre[rt].l, r = tre[rt].r;
		tre[rt].isg = (tre[l].rval ^ tre[r].lval) & tre[l].isg & tre[r].isg; //左右两个区间都是好的并且左区间右侧和右区间左侧不同时当前的区间才是好的
		tre[rt].lval = tre[l].lval;
		tre[rt].rval = tre[r].rval;
		return ;
	}
	inline void pushdown(int rt) { //下传反转标记
		if (!tre[rt].tag) return ;
		int l = tre[rt].l, r = tre[rt].r;
		tre[l].tag ^= 1, tre[r].tag ^= 1;
		tre[l].lval ^= 1, tre[l].rval ^= 1;
		tre[r].lval ^= 1, tre[r].rval ^= 1; //全都反转
		tre[rt].tag = 0;
		return ;
	}
	void build(int &rt, int l, int r) { //建树
		if (!rt) rt = ++tot;
		if (l == r) {
			tre[rt].lval = tre[rt].rval = a[l]; //底层初值
			tre[rt].isg = 1; //长度为 1 的区间应该是好的
			return ;
		}
		int mid = (l + r) >> 1;
		build(tre[rt].l, l, mid);
		build(tre[rt].r, mid + 1, r);
		pushup(rt);
		return ;
	}
	void update(int rt, int l, int r, int L, int R) {
		if (L <= l && r <= R) { //包含就打上 tag 返回
			tre[rt].tag ^= 1;
			tre[rt].lval ^= 1;
			tre[rt].rval ^= 1;
			return ;
		}
		pushdown(rt);
		int mid = (l + r) >> 1;
		if (L <= mid) update(tre[rt].l, l, mid, L, R);
		if (R > mid) update(tre[rt].r, mid + 1, r, L, R);
		pushup(rt);
		return ;
	}
	int query(int rt, int l, int r, int L, int R) {
		if (L <= l && r <= R) {
			return tre[rt].isg;
		}
		pushdown(rt);
		int mid = (l + r) >> 1, lr = tre[rt].l, rr = tre[rt].r;
		if (L <= mid && R > mid) { //如果跨越 mid 就要合并左右两个询问区间，合并可以参考 pushup 函数里的注释
			if ((tre[lr].rval ^ tre[rr].lval) == 0) return 0;
			return query(lr, l, mid, L, R) && query(rr, mid + 1, r, L, R);
		} else if (L <= mid) { //没有跨越就直接返回就好了
			return query(lr, l, mid, L, R);
		} else {
			return query(rr, mid + 1, r, L, R);
		}
	}
} tre;

signed main() {
	read(n), read(q);
	char ch = 0;
	while (ch != '0' && ch != '1') ch = getchar();
	for (int i = 1; i <= n; i++, ch = getchar()) {
		if (ch == '1') a[i] = 1;
	}
	tre.build(tre.root, 1, n);
	int opt, l, r;
	while (q--) {
		read(opt), read(l), read(r);
		if (opt == 1) {
			tre.update(tre.root, 1, n, l, r);
		} else {
			if (tre.query(tre.root, 1, n, l, r)) {
				printf("Yes\n");
			} else {
				printf("No\n");
			}
		}
	}
	return 0;
}
```


---

## 作者：incra (赞：0)

### Solution
线段树模板题，考虑线段树（雾。

在一个节点中，维护以下四个量：

- `lnode`，当前区间的最左边的点的权值。
- `rnode`，当前区间的最右边的点的权值。
- `ans`，当前区间是否是好的。
- `tag`，区间翻转懒标记。

那么这题就想得差不多了，简单讲一下 `push_up` 和 `push_down` 的过程。

对于 `push_up`：
 
- 当前区间的 `lnode` 显然等于左边区间的 `lnode`，当前区间的 `rnode` 同理。
- 左边区间的 `ans`、右边区间 `ans` 和左边区间的 `rnode` 不等于右边区间的 `lnode` 同时成立时，当前区间的 `ans`  为 `true` 否则为 `false`。

对于 `push_down`：

- 唯一会变化的量就是 `lnode` 和 `rnode`，直接取反即可。
- 注意给子节点打上标记。

注意叶子节点一定是好的。
### Code
```cpp
#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
#include <queue>
#include <bitset>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cassert>
#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define pf push_front
#define desktop "C:\\Users\\incra\\Desktop\\"
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
bool LAST = false;
istream& operator >> (istream& in,char* s) {
    if (LAST) return in;
	char ch = in.get ();
	while ((isspace (ch) || ch == '\n') && ch != EOF) ch = in.get ();
	int n = 0;
	while (!(isspace (ch) || ch == '\n') && ch != EOF) s[n++] = ch,ch = in.get ();
	s[n] = '\0';
	if (ch == EOF) LAST = true;
	return in;
}
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
const int N = 500010;
int n,q;
int a[N];
struct node {
	int l,r;
	int lnode,rnode;
	bool ans;
	bool tag;
}tr[4 * N];
void push_up (node &root,node left,node right) {
	root.lnode = left.lnode,root.rnode = right.rnode;
	root.ans = left.ans && right.ans && (left.rnode != right.lnode);
}
void push_up (int u) {
	push_up (tr[u],tr[u << 1],tr[u << 1 | 1]);
}
void opt_tag (int u) {
	tr[u].lnode ^= 1,tr[u].rnode ^= 1;
	tr[u].tag ^= 1;
}
void push_down (int u) {
	if (tr[u].tag) {
		opt_tag (u << 1),opt_tag (u << 1 | 1);
		tr[u].tag = false;
	}
}
void build (int u,int l,int r) {
	tr[u] = {l,r,a[l],a[r],true,false};
	if (l == r) return ;
	int mid = l + r >> 1;
	build (u << 1,l,mid),build (u << 1 | 1,mid + 1,r);
	push_up (u);
}
void modify (int u,int l,int r) {
	if (l <= tr[u].l && tr[u].r <= r) {
		opt_tag (u);
		return ;
	}
	push_down (u);
	int mid = tr[u].l + tr[u].r >> 1;
	if (l <= mid) modify (u << 1,l,r);
	if (r >= mid + 1) modify (u << 1 | 1,l,r);
	push_up (u);
}
node query (int u,int l,int r) {
	if (l <= tr[u].l && tr[u].r <= r) return tr[u];
	push_down (u);
	int mid = tr[u].l + tr[u].r >> 1;
	if (r <= mid) return query (u << 1,l,r);
	if (l >= mid + 1) return query (u << 1 | 1,l,r);
	node ans;
	push_up (ans,query (u << 1,l,r),query (u << 1 | 1,l,r));
	return ans;
}
int main () {
	scanf ("%d%d",&n,&q);
	for (int i = 1;i <= n;i++) scanf ("%1d",&a[i]);
	build (1,1,n);
	while (q--) {
		int op,l,r;
		scanf ("%d%d%d",&op,&l,&r);
		if (op == 1) modify (1,l,r);
		else {
			if (query (1,l,r).ans) puts ("Yes");
			else puts ("No");
		}
//		for (int i = 1;i <= n;i++) cout << query (1,i,i).lnode << ' ';
//		cout << endl;
	}
	return 0;
}
```

---

## 作者：kkxacj (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc341_e)

#### 思路

很明显的线段树板题，对于一段序列**不是好字符串**当且仅当这一段中存在两个相同的数连在一起的情况，那么可以对于每个点记录一下左右的数是多少，更新时就看如果左边一段不是好字符串，或右边一段不是好字符串，或着两个拼起来不是好字符串，则这一段不是好字符串，实现如下：

```
if(a[p * 2].ans || a[p * 2 + 1].ans || a[p * 2].rc == a[p * 2 + 1].lc) a[p].ans = 1;
//lc是最左边的数，rc是最右边的数
```
然后我们在想想对于第一个翻转操作究竟是干了个什么。

不难发现，翻转完这一段，那就是把这些数取反后在重新计算，如果每次重算肯定很浪费时间。

考虑新建一个与原串的每个数都相反的新串，按之前的操作计算一遍答案，所谓的翻转操作就是把这两个的答案翻转，左右的数翻转，就可以用懒标记了。

求答案的时候就类似与最上面那个代码，不在细讲。

**code**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y,z,k,b[500010],l,l1,ans;
string s;
struct w
{
	int l,r,ans,ans1;
	long long dat,bj,lc,rc,lc1,rc1;
}a[500010 * 4];
void gx(int p)
{
	a[p].lc = a[p * 2].lc,a[p].rc = a[p * 2 + 1].rc;
	a[p].lc1 = a[p * 2].lc1,a[p].rc1 = a[p * 2 + 1].rc1;
	if(a[p * 2].ans || a[p * 2 + 1].ans || a[p * 2].rc == a[p * 2 + 1].lc) a[p].ans = 1;
	else a[p].ans = 0;
	if(a[p * 2].ans1 || a[p * 2 + 1].ans1 || a[p * 2].rc1 == a[p * 2 + 1].lc1) a[p].ans1 = 1;
	else a[p].ans1 = 0;
}
void build(int p,int l,int r)
{
	a[p].l = l; a[p].r = r;
	if(l == r) 
	{
		a[p].lc = a[p].rc = b[l];
		a[p].lc1 = a[p].rc1 = !b[l];
		return;
	}
	int mid = (l + r) / 2;
	build(p * 2,l,mid); build(p * 2 + 1,mid + 1,r);
	gx(p);
}
void bj(int p)
{
	a[p * 2].lc = !a[p * 2].lc; a[p * 2].rc = !a[p * 2].rc;
	a[p * 2 + 1].lc = !a[p * 2 + 1].lc; a[p * 2 + 1].rc = !a[p * 2 + 1].rc;
	a[p * 2].lc1 = !a[p * 2].lc1; a[p * 2].rc1 = !a[p * 2].rc1;
	a[p * 2 + 1].lc1 = !a[p * 2 + 1].lc1; a[p * 2 + 1].rc1 = !a[p * 2 + 1].rc1;
	a[p * 2].bj ^= 1,a[p * 2 + 1].bj ^= 1;
	swap(a[p * 2].ans,a[p * 2].ans1);
	swap(a[p * 2 + 1].ans,a[p * 2 + 1].ans1);
	a[p].bj = 0;
}
void change(int p,int l,int r)
{
	if(l <= a[p].l && a[p].r <= r)
	{
		a[p].bj ^= 1; 
		swap(a[p].ans,a[p].ans1);
		a[p].lc = !a[p].lc; a[p].rc = !a[p].rc;
		a[p].lc1 = !a[p].lc1; a[p].rc1 = !a[p].rc1;
		return;
	}
	if(a[p].bj)bj(p);
	int mid = (a[p].l + a[p].r) / 2;
	if(l <= mid) change(p * 2,l,r);
	if(mid < r) change(p * 2 + 1,l,r);
	gx(p);
}
void ask(int p,int l,int r)
{
	if(l <= a[p].l && a[p].r <= r)
	{
		if(a[p].ans) ans = 1;
		return;
	}
	if(a[p].bj) bj(p);
	int mid = (a[p].l + a[p].r) / 2;
	if(l <= mid && mid < r) 
	{
		ask(p * 2,l,r); ask(p * 2 + 1,l,r);
		if(a[p * 2].rc == a[p * 2 + 1].lc) ans = 1;//考虑拼起来是否满足
	}
	else if(l <= mid) ask(p * 2,l,r);
	else ask(p * 2 + 1,l,r);
}
int main()
{
	scanf("%d%d",&n,&m); cin >> s;
	for(int i = 1;i <= n;i++) b[i] = s[i - 1] - '0';
	build(1,1,n);
	for(int i = 1;i <= m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		if(x == 1) change(1,y,z);
		else
		{
			ans = 0;
			ask(1,y,z);
			if(ans) puts("No");
			else puts("Yes");
		}
	}
	return 0;
}
```


---

## 作者：Double_Light (赞：0)

显然可以用线段树维护。

对于每个节点，维护四个值：左边界的数字 $l$，右边界的数字 $r$，是否满足是“好串”，以及一个懒标记，即该区间是否被翻转过。

对于查询操作，每次到一个节点，如果需要访问左儿子且需要访问右儿子，记得记录的时候判断左儿子的右端点和右儿子的左端点的数字是否不相同。如果相同，尽管左右儿子可能是“好串”，这依然不是一个“好串”。

修改懒标记时，应该将原标记取反而不是改成 $1$。我因为这个赛时没调出来。当然 pushdown 的时候直接把父节点的懒标记改成 $0$ 就行了。

这样就可以当成板子题来做了。

代码：

```cpp
#include<iostream>
#define mid ((l+r)/2)
#define int long long
using namespace std;
int n,m,opt;
char ch[500005];
int a[500005];
struct node{
	bool a,l,r;
	bool tag;
}tr[2000005];
void pushup(int x){
	if(tr[2*x].r!=tr[2*x+1].l&&tr[2*x].a&&tr[2*x+1].a)tr[x].a=1;
	else tr[x].a=0;
	tr[x].l=tr[2*x].l;
	tr[x].r=tr[2*x+1].r;
}
void build(int x,int l,int r){
	if(l==r){
		tr[x].a=1;
		tr[x].l=a[l];
		tr[x].r=a[r];
		return ;
	}
	build(2*x,l,mid);
	build(2*x+1,mid+1,r);
	pushup(x);
}
void pushdown(int x,int l,int r){
	if(l==r)return ;
	if(tr[x].tag==0)return ;
	tr[x].tag=0;
	tr[2*x].tag=!tr[2*x].tag;tr[2*x+1].tag=!tr[2*x+1].tag;
	tr[2*x].l=!tr[2*x].l;//注意左右端点也需要取反
	tr[2*x].r=!tr[2*x].r;
	tr[2*x+1].l=!tr[2*x+1].l;
	tr[2*x+1].r=!tr[2*x+1].r;
}
void update(int x,int l,int r,int from,int to){
	if(from<=l&&r<=to){
		tr[x].l=!tr[x].l;
		tr[x].r=!tr[x].r;
		tr[x].tag=!tr[x].tag;
		return ;
	}
	pushdown(x,l,r);
	if(from<=mid)update(2*x,l,mid,from,to);
	if(to>mid)update(2*x+1,mid+1,r,from,to);
	pushup(x);
}
int query(int x,int l,int r,int from,int to){
	if(from<=l&&r<=to)return tr[x].a;
	pushdown(x,l,r);
	int ans=1;
	if(from<=mid&&to>mid&&tr[2*x].r==tr[2*x+1].l)return 0;
	if(from<=mid)ans=ans&query(2*x,l,mid,from,to);
	if(to>mid)ans=ans&query(2*x+1,mid+1,r,from,to);
	return ans;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>ch[i],a[i]=ch[i]-'0';//不能直接输入int数组
	build(1,1,n);
	for(int i=1;i<=m;i++){
		cin>>opt;
		int l,r;
		cin>>l>>r;
		if(opt==1){
			update(1,1,n,l,r);
		}
		if(opt==2){
			if(query(1,1,n,l,r))cout<<"Yes\n";
			else cout<<"No\n";
		}
	}
	return 0;
} 
```

---

## 作者：ilibilib (赞：0)

## 分析：

简单分块题。

用 $f[i]$ 记录第 $i$ 块内是否存在连续相等的子串。用 $lz[i]$ 记录第 $i$ 块是否翻转。

初始化函数如下：

```cpp
void solve(int i)
{
	f[i]=false;
	for(int j=bg[i]+1;j<=ed[i]&&!f[i];++j) f[i]|=(s[j]==s[j-1]);
}//处理第i块是否存在连续相等子串
```

```cpp
void bld(int n)
{
	int fk=sqrt(n),t=(n-1)/fk+1;
	for(int i=1;i<=n;++i) pos[i]=(i-1)/fk+1;
	for(int i=1;i<=t;++i) bg[i]=(i-1)*fk+1,ed[i]=i*fk;
	ed[t]=n;
	for(int i=1;i<=t;++i) solve(i);
}//常规
```

`change` 函数也很常规

```cpp
void change(int l,int r)
{
	int p=pos[l],q=pos[r];
	if(p==q)
	{
		for(int i=l;i<=r;++i) s[i]=!s[i];
		solve(p);
        //散块修改可能改变 f 的情况，所以重新处理
	}
	else
	{
		for(int i=p+1;i<q;++i) lz[i]=!lz[i];
		change(l,ed[p]);change(bg[q],r);
        //显然，整块修改不会改变 f 的情况
	}
}
```

`ask` 需要检查每块块首和上一块块末的关系，此时还要注意两块翻转的情况

```cpp
bool ask(int l,int r)
{
	int p=pos[l],q=pos[r];
	bool ans=false;
	if(p==q)
	{
		for(int i=l+1;i<=r&&!ans;++i) ans|=(s[i]==s[i-1]);
		return ans;//散块暴力询问
	}
	else
	{
		for(int i=p+1;i<q&&!ans;++i) ans|=f[i];//每个块内
		for(int i=p+1;i<=q&&!ans;++i) ans|=(!lz[i])^(!lz[i-1])^(s[bg[i]]==s[ed[i-1]]);//每个块首和上一块末
		if(!ans) ans|=ask(l,ed[p]);if(!ans) ans|=ask(bg[q],r);//散块询问 
		return ans;
	}
}

```

## 完整代码：

```cpp
#include<bits/stdc++.h>
#define N 1000010
#define M 1010
using namespace std;
int pos[N],bg[M],ed[M],lz[M],f[M];
bool s[N];
void solve(int i)
{
	f[i]=false;
	for(int j=bg[i]+1;j<=ed[i]&&!f[i];++j) f[i]|=(s[j]==s[j-1]);
}
void bld(int n)
{
	int fk=sqrt(n),t=(n-1)/fk+1;
	for(int i=1;i<=n;++i) pos[i]=(i-1)/fk+1;
	for(int i=1;i<=t;++i) bg[i]=(i-1)*fk+1,ed[i]=i*fk;
	ed[t]=n;
	for(int i=1;i<=t;++i) solve(i);
}
void change(int l,int r)
{
	int p=pos[l],q=pos[r];
	if(p==q)
	{
		for(int i=l;i<=r;++i) s[i]=!s[i];
		solve(p);
	}
	else
	{
		for(int i=p+1;i<q;++i) lz[i]=!lz[i];
		change(l,ed[p]);change(bg[q],r);
	}
}
bool ask(int l,int r)
{
	int p=pos[l],q=pos[r];
	bool ans=false;
	if(p==q)
	{
		for(int i=l+1;i<=r&&!ans;++i) ans|=(s[i]==s[i-1]);
		return ans;
	}
	else
	{
		for(int i=p+1;i<q&&!ans;++i) ans|=f[i];
		for(int i=p+1;i<=q&&!ans;++i) ans|=(!lz[i])^(!lz[i-1])^(s[bg[i]]==s[ed[i-1]]);
		if(!ans) ans|=ask(l,ed[p]);if(!ans) ans|=ask(bg[q],r);
		return ans;
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n,q,l,r,op;
	string ss;
	cin>>n>>q>>ss;
	for(int i=0;ss[i];++i) s[i+1]=ss[i]-'0';
	bld(n);
	while(q--)
	{
		cin>>op>>l>>r;
		if(op==1) change(l,r);
		else
		{
			if(!ask(l,r)) cout<<"Yes"<<'\n';
			else cout<<"No"<<'\n';
		}
	}
}
```

---

## 作者：fydj (赞：0)

# [ABC341E] Alternating String

### 题目大意

给定 $N$，$Q$，和一个 ```01``` 串 $S$，有 $Q$ 次询问。询问 ```1 L R``` 表示反转 $L$ 到 $R$ 的数字，把 $0$ 变成 $1$，把 $1$ 变成 $0$；询问 ```2 L R``` 表示问 $L$ 到 $R$ 的子串是不是一个 ```01``` 相间的串。

### 思路

线段树模板题。

线段树每个节点对应一个区间，记录这个区间最左边的值、最右边的值、是不是 ```01``` 相间的串。

一个区间最左边的值等于左儿子最左边的值，最右边的值等于右儿子最右边的值，如果左儿子和右儿子都是 ```01``` 相间的串、并且左儿子最右边的值不等于右儿子最左边的值，那么这个区间就是 ```01``` 相间的串。

再用一个标记记录一下区间反转情况，区间反转只影响最左边的值和最右边的值，不影响它是不是 ```01``` 相间的串。

用线段树基本操作维护即可。

时间复杂度 $O(n \log n)$。

### 代码

```cpp
#define lson (x<<1)
#define rson (x<<1|1)
void push(int x) { tag[x]^=1; front[x]^=1; back[x]^=1; }
void update(int x) { front[x]=front[lson]; back[x]=back[rson]; is[x]=is[lson]&&is[rson]&&back[lson]!=front[rson]; return ; }
void downtag(int x,int l,int r) { if(tag[x]) { if(l<r) push(lson),push(rson); tag[x]=false; } return ; }
void maketree(int x,int l,int r) {
	if(l==r) { front[x]=back[x]=a[l]; is[x]=1; return ; }
	int mid=l+r>>1;
	maketree(lson,l,mid),maketree(rson,mid+1,r);
	update(x);
	return ;
}
void change(int x,int l,int r,int L,int R) {
	downtag(x,l,r);
	if(r<L||R<l) return ;
	if(L<=l&&r<=R) { push(x); downtag(x,l,r); return ; }
	int mid=l+r>>1;
	change(lson,l,mid,L,R),change(rson,mid+1,r,L,R);
	update(x);
	return ;
}
int solve(int x,int l,int r,int L,int R) {
	downtag(x,l,r);
	if(L<=l&&r<=R) return is[x];
	int mid=l+r>>1;
	if(L<=mid&&mid<R) return solve(lson,l,mid,L,R)&&solve(rson,mid+1,r,L,R)&&back[lson]!=front[rson];
	if(L<=mid) return solve(lson,l,mid,L,R);
	if(mid<R) return solve(rson,mid+1,r,L,R);
}
int main()
{
	int i;
	read(n,q);
	for(i=1;i<=n;++i) {
		do chart=getchar();
		while(chart!='0'&&chart!='1');
		a[i]=chart=='1';
	}
	maketree(1,1,n);
	for(i=1;i<=q;++i) {
		read(opt,l,r);
		if(opt==1) change(1,1,n,l,r);
		else printf("%s\n",solve(1,1,n,l,r)?"Yes":"No");
	}
	return 0;
}
```



---

