# [ARC153B] Grid Rotations

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc153/tasks/arc153_b

縦 $ H $ 行，横 $ W $ 列のグリッドがあります．はじめ，上から $ i $ 行目，左から $ j $ 列目のマスには英小文字 $ A_{i,j} $ が書かれています．

このグリッドに対して $ Q $ 回の操作を行います．$ i $ 回目の操作では，$ 1\leq\ a_i\ \leq\ H-1 $, $ 1\leq\ b_i\leq\ W-1 $ を満たす整数 $ a_i,\ b_i $ が与えられ，次を行います．

- グリッド内の長方形領域 $ R_1,\ R_2,\ R_3,\ R_4 $ を次で定める：
  - 上から $ a_i $ 行，左から $ b_i $ 列の部分を $ R_1 $ とする．
  - 上から $ a_i $ 行，右から $ W-b_i $ 列の部分を $ R_2 $ とする．
  - 下から $ H-a_i $ 行，左から $ b_i $ 列の部分を $ R_3 $ とする．
  - 下から $ H-a_i $ 行，右から $ W-b_i $ 列の部分を $ R_4 $ とする．
- $ R_1,\ R_2,\ R_3,\ R_4 $ のそれぞれを $ 180 $ 度回転する．
 
ただし，グリッド内の長方形領域 $ R $ の $ 180 $ 度回転とは，$ R $ において上から $ i $ 番目，左から $ j $ 番目のマスに書かれた文字を，$ R $ において 下から $ i $ 番目，右から $ j $ 番目のマスに移すことをいいます．入出力例の図も参考にしてください．

$ Q $ 回すべての操作を行ったとき，操作後のグリッドの状態を出力してください．

## 说明/提示

### 制約

- $ 2\leq\ H,\ W $ かつ $ HW\ \leq\ 5\times\ 10^5 $
- $ A_{i,j} $ は英小文字
- $ 1\leq\ Q\leq\ 2\times\ 10^5 $
- $ 1\leq\ a_i\leq\ H\ -\ 1 $
- $ 1\leq\ b_i\leq\ W\ -\ 1 $
 
### Sample Explanation 1

グリッドの状態は次の図のように変化します． !\[\](https://img.atcoder.jp/arc153/5503f0a5f92e488238556b943aa1d6b7.png)

### Sample Explanation 2

グリッドの状態は次の図のように変化します． !\[\](https://img.atcoder.jp/arc153/353f0b30a9561e38967fb3aedf5767c5.png)

### Sample Explanation 3

グリッドの状態は次の図のように変化します． !\[\](https://img.atcoder.jp/arc153/655a0ac98f0625e806f6abc97853a437.png)

## 样例 #1

### 输入

```
4 5
abcde
fghij
klmno
pqrst
1
3 3```

### 输出

```
mlkon
hgfji
cbaed
rqpts```

## 样例 #2

### 输入

```
3 7
atcoder
regular
contest
2
1 1
2 5```

### 输出

```
testcon
oderatc
ularreg```

## 样例 #3

### 输入

```
2 2
ac
wa
3
1 1
1 1
1 1```

### 输出

```
ac
wa```

# 题解

## 作者：Feyn (赞：9)

提示：由于本人写作习惯，矩阵认为是 $m$ 行 $n$ 列，与题面有出入，见谅。

显然对于 $x$ 和 $y$ 这两维分别考虑。

然后呢到这一步可以有不优雅的想法是，你矩形旋转半周可以看成是矩形范围内的横纵坐标分别反转。而反转操作可以用文艺平衡树方便的维护，于是就可以通过这道题了。

另外有一种方法是这样的：考虑 $x$ 这一维，有一个操作是 $(a,b)$，那么对 $x,a$ 的相对大小分类讨论（我是下标从 $0$ 开始编号，所以输入的时候 $a$ 会减一）。如果 $x\le a$，那么发现 $x'=a-x$；否则会发现 $x'=a+(m-x)=a-x+m$。观察柿子，会发现两个柿子是本质相同的，都是在求 $a-x$ 在模 $m$ 意义下的余数。然后事情就变得简单了，我们便可以不分类讨论，直接考虑拆柿子：

$$
\begin{aligned}
x_1&\equiv a_1-x_0\\
x_2&\equiv a_2-x_1\equiv a_2-a_1+x_0\\
x_3&\equiv a_3-x_2\equiv a_3-a_2+a_1-x_0\\
\dots
\end{aligned}
$$

于是结论十分显然了。只需要找出前面那一堆 $a$ 的和以及 $x_0$ 的系数就可以 $O(1)$ 找出某个 $x$ 经过变换后的行号。$y$ 那个维度同理，复杂度 $O(mn)$。

```cpp
#include<bits/stdc++.h>
//#define feyn
#define int long long
using namespace std;
const int N=500010;
inline void read(int &wh){
    wh=0;int f=1;char w=getchar();
    while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
    while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
    wh*=f;return;
}

int m,n,num,sa,sb,in;
char w[N];
vector<char>a[N],b[N];

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	read(m);read(n);
	for(int i=0;i<m;i++){
		scanf("%s",w);
		for(int j=0;j<n;j++)a[i].push_back(w[j]),b[i].push_back('0');
	}
	read(num); 
	for(int i=1;i<=num;i++){
		read(in);in--;if(i%2==num%2)sa+=in;else sa-=in;
		read(in);in--;if(i%2==num%2)sb+=in;else sb-=in;
	}
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			int ii=i,jj=j;
			ii=((sa+(num%2==0?1:-1)*ii)%m+m)%m;
			jj=((sb+(num%2==0?1:-1)*jj)%n+n)%n;
			b[ii][jj]=a[i][j];
		}
	}
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++)putchar(b[i][j]);
		putchar('\n');
	}
	
	return 0;
}
```

---

## 作者：ForgotDream_CHN (赞：2)

# ATARC153B Grid Rotations

纪念我人生的第一场 ARC。

### 题意

给定一个大小为 $h \times w$ 的字符矩阵与 $q$ 次操作，其中 $h \times w \le 5 \times 10 ^ 5$，$q \le 2 \times 10 ^ 5$。每次操作的流程如下：

* 给定两个整数 $x$，$y$ 满足 $1 \le x \le h - 1$，$1 \le y \le w - 1$；
*  以第 $x$ 行与第 $y$ 列为分界线，将矩阵划分为四个部分；
*  将四个部分上下、左右分别翻转。

输出 $q$ 次操作后的矩阵。

### 思路

首先，这个操作是可以分为两个部分的：行翻转与列翻转。有了这个想法之后再来看这道题，就不显得那么棘手。

我的第一个思路是用 ``vector`` 存 ``string`` 然后暴力模拟，再加上 STL 数据结构吸氧跑的飞快的特点强行卡常，时间复杂度为 $O(qhw)$，显然这个 naive 做法 T 飞了，最终测出来的结果是 AC 12，TLE 20。

自然地，我并不想丢掉这宝贵的 500 pts，于是我着眼于改善每次修改的时间复杂度。看到区间反转，联想到再熟悉不过的序列操作模板例题：文艺平衡树。于是我有了第二个思路：对每一行都建立一棵 FHQ Treap 维护每一列的交换，再建立一棵 FHQ 用于维护行与行之间的交换。但正当我兴致勃勃地写好代码、粘贴提交一气呵成后，我又被结果整蒙了：AC 15，TLE 17。终于，我发现了问题所在：虽然行反转的复杂度将为了单次操作 $O(\log h)$，但列反转的复杂度，由于对每一行都需要操作，其单次复杂度为 $O(h \log w)$！
这样，总的复杂度就是 $O(q(h\log w + \log h))$，并没有改善多少。

思考许久之后，我有了第三个思路。首先意识到对于每一列来说，行与行的变化都是相同的，而对于每一行来说，列与列的变化也是相同的。这启发我们将行变化、列变化分别看作一个整体，这样我们只用建立两棵 FHQ 就可以表示出所有行列的变化，时间复杂度为 $O(q(\log h + \log w))$，足以通过此题了。

提交这道题的正解时，离比赛结束只有一分钟时间，不得不说还是相当的极限。

### 代码

Talk is cheap, show me the code!

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 50;
struct FHQTreap {
	vector<int> val, prm, size, rev;
	vector<vector<int>> ch;
 	int cnt, root;
	int l, r, p;

	FHQTreap() { 
		val.push_back(0), prm.push_back(0), size.push_back(0), rev.push_back(false);
		ch.push_back(vector<int>(2, 0));
		root = 0; 
	};

	void init(int x) {
		val.push_back(x), prm.push_back(rand()), size.push_back(1), rev.push_back(0);
		ch.push_back(vector<int>(2, 0)), cnt++;
		return;
	}

	void update(int u) {
		return (void)(size[u] = size[ch[u][0]] + size[ch[u][1]] + 1);
	}

	void pushdown(int u) {
		if (!rev[u]) return;
		swap(ch[u][0], ch[u][1]), rev[ch[u][0]] ^= 1, rev[ch[u][1]] ^= 1;
		rev[u] = false;
		return;
	}

	void split(int u, int x, int &l, int &r) {
		if (!u) return (void)(l = r = 0);
		pushdown(u);
		if (size[ch[u][0]] < x) 
			l = u, split(ch[u][1], x - size[ch[u][0]] - 1, ch[u][1], r);
		else r = u, split(ch[u][0], x, l, ch[u][0]);
		update(u);
		return;
	}

	int merge(int l, int r) {
		if (!l || !r) 
			return l + r;
		if (prm[l] > prm[r]) 
			return pushdown(l), ch[l][1] = merge(ch[l][1], r), update(l), l;
		else return pushdown(r), ch[r][0] = merge(l, ch[r][0]), update(r), r;
	}

	void inorderTraverse(int u) {
		if (!u) return;
		pushdown(u);
		inorderTraverse(ch[u][0]); 
		// putchar(val[u]); 
		cout << (char) val[u];
		inorderTraverse(ch[u][1]);
		return;
	}

	void modify(int x, int y) {
		split(root, y, l, r);
		split(l, x - 1, l, p);
		rev[p] ^= 1;
		root = merge(merge(l, p), r);
		return;
	}

	int query(int x) {
		split(root, x + 1, l, r), split(l, x, l, p);
		int res = val[p];
		root = merge(merge(l, p), r);
		return res;
	}
};
FHQTreap line, row;
int h, w, q;
vector<vector<char>> e;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> h >> w;
	
	e.resize(h + 1);
	for (int i = 1; i <= h; i++) {
		e[i].resize(w + 1);
		for (int j = 1; j <= w; j++) cin >> e[i][j];
	}

	for (int i = 1; i <= h; i++) line.init(i), line.root = line.merge(line.root, line.cnt);
	for (int i = 1; i <= w; i++) row.init(i), row.root = row.merge(row.root, row.cnt);

	cin >> q;
	while (q--) {
		int x, y;
		cin >> x >> y;
		line.modify(1, x), line.modify(x + 1, h);   // 分别对行列进行翻转操作
		row.modify(1, y), row.modify(y + 1, w);
	}

	for (int i = 0; i < h; i++) { 
		for (int j = 0; j < w; j++) {
			int x = line.query(i), y = row.query(j);   // 得到变化后的横纵坐标
			cout << e[x][y];
		}
		cout << endl;
	}
	return 0;
}
```

---

## 作者：123asdf123 (赞：1)

[在我的博客查看](https://www.cnblogs.com/123asdf123/p/18778544)

之前只在博客里发了，忘在洛谷发了……
- - -
很久以前打第一场 ARC 时的 B 题，现在差点都还没做出来……

不会写平衡树，因此考虑其它做法。

观察样例二，发现答案好似就是把串往下和往右滚动了几下。

再想一下，发现每两次旋转都可以视为滚动，考虑两次两次计算贡献，如果是奇数次最后一次单独处理。

假设每一个数代表一小块，那么滚动好像是这样的（由于内部旋转了也要旋转回来，就不画了）：

![](https://cdn.luogu.com.cn/upload/image_hosting/9csetmap.png)

但是分析样例发现假如直接按照它下标来划分块会出问题，会被切断。

![](https://cdn.luogu.com.cn/upload/image_hosting/n456ds69.png)

发现分段应该推出第二根分割线在第一根之前的位置，再划分：

![](https://cdn.luogu.com.cn/upload/image_hosting/z59fyl39.png)

显然，滚动可以先不看字符，最后直接加上偏移量，然后就做完了。

虽然说着简单，实际上旋转后坐标推着和写着很麻烦，写了 2 个小时！（因此到了考场还是做不出来……）

代码下标有时候是从 0 开始的，因此很屎。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace estidi{
	string s[500003];
	int main(){
		int h,w,q,x,y,xx,yy;
		long long rr=0,dr=0;
		scanf("%d%d",&h,&w);
		for(int i=0;i<h;i++)
			cin>>s[i];
		scanf("%d",&q);
		for(int i=2;i<=q;i+=2){
			scanf("%d%d%d%d",&x,&y,&xx,&yy);
			x--;
			y--;
			xx--;
			yy--;
			if(xx<=x)
				xx=x-xx;
			else
				xx=h-xx+x;
			if(yy<=y)
				yy=y-yy;
			else
				yy=w-yy+y;
//			cerr<<xx<<" "<<yy<<endl;
//			cerr<<x<<" "<<y<<endl;
			dr+=h-xx;
			rr+=w-yy;
//			cerr<<dr<<" "<<rr<<endl;
		}
		dr=(dr%h+h)%h;
		rr=(rr%w+w)%w;
		if(q%2==1){
			scanf("%d%d",&x,&y);
			x--;
			y--;
			for(int i=0;i<h;i++){
				for(int j=0;j<w;j++){
					int nx,ny;
					if(i<=x)
						nx=x-i;
					else
						nx=h-i+x;
					if(j<=y)
						ny=y-j;
					else
						ny=w-j+y;
//					cerr<<i<<" "<<j<<" "<<nx<<" "<<ny<<" "<<dr<<" "<<rr<<" "<<s[nx][ny]<<endl;
					printf("%c",s[(nx-dr+h)%h][(ny-rr+w)%w]);
				}
				printf("\n");
			}
		}
		else{
			for(int i=0;i<h;i++){
				for(int j=0;j<w;j++)
					printf("%c",s[(i-dr+h)%h][(j-rr+w)%w]);
				printf("\n");
			}
		}
		return 0;
	}
}
int main(){
	estidi::main();
	return 0;
}

---

## 作者：Statax (赞：1)

## 前言

比赛出了这题，赛时只打了暴力。

当时其实看到题就想到了文艺平衡树，但我想成二维平衡树就没打…

## 解析

很明显，翻转半周等同于交换一个矩形中相对的行的字符，相对的列的字符。

由于行很好交换，可以轻松写出 $O(q (h \log w + \log h))$，可惜这份代码时间复杂度过不了。

思考发现，列和行实际上是可以独立处理的，也就是我们开两个平衡树分别维护行和列就行了，最后统一输出即可，时间复杂度 $O(q (\log h + \log w))$。

## 代码

```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
#include <ctime>
#include <random>
#include <vector>
#include <iostream>
using namespace std;

#define x first
#define y second
#define db double
#define pb push_back
#define ll long long
#define i128 __int128
#define ull unsigned ll
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

const int MAXN = 5e5 + 5;
const int inf = 2147483627;
const int mod = 998244353;
const db eps = 1e-9;

template <typename T> inline void read (T &x) {
	x = 0; T f = 1; char ch = getchar ();
	while (!isdigit (ch)) { if (ch == '-') f = -1; ch = getchar (); }
	while (isdigit (ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar ();
	x *= f;
}

template <typename T, typename ...Arp> inline void read (T &x, Arp &...arp) {
	read (x), read (arp...);
}

int n, m, q;
string ch[MAXN];
vector <int> pathr, pathc;

struct Node {
	int l, r;
	int v, rd, sz, rv; 
};

mt19937 rng (time (0));

struct FHQ {
	int rt, tot;
	int x, y, z;
	Node tr[MAXN];
	
	int newnode (int _v) {
		tr[++tot].v = _v;
		tr[tot].rd = rng ();
		tr[tot].sz = 1;
		return tot;
	}
	
	void push_up (int x) {
		tr[x].sz = tr[tr[x].l].sz + tr[tr[x].r].sz + 1;
	}
	
	void push_down (int x) {
		if (tr[x].rv) {
			tr[x].rv = 0;
			tr[tr[x].l].rv ^= 1;
			tr[tr[x].r].rv ^= 1;
			swap (tr[x].l, tr[x].r);
		}
	}
	
	void split (int u, int k, int &x, int &y) {
		if (!u) return x = y = 0, void ();
		push_down (u);
		if (k <= tr[tr[u].l].sz) {
			y = u;
			split (tr[u].l, k, x, tr[u].l);
		} else {
			x = u;
			split (tr[u].r, k - tr[tr[u].l].sz - 1, tr[u].r, y);
		} push_up (u);
	}
	
	int merge (int u, int v) {
		if (!u || !v) return u | v;
		if (tr[u].rd < tr[v].rd) {
			push_down (u);
			tr[u].r = merge (tr[u].r, v);
			return push_up (u), u;
		} else {
			push_down (v);
			tr[v].l = merge (u, tr[v].l);
			return push_up (v), v;
		}
	}
	
	void reverse (int l, int r) {
		split (rt, r, x, y);
		split (x, l - 1, x, z);
		tr[z].rv ^= 1;
		rt = merge (merge (x, z), y);
	}
	
	void build (int u, vector <int>& path) {
		push_down (u);
		if (tr[u].l) build (tr[u].l, path);
		path.pb (u);
		if (tr[u].r) build (tr[u].r, path);
	}
} row, col;

signed main () {
//	freopen ("rotation.in", "r", stdin);
//	freopen ("rotation.out", "w", stdout);
	read (n, m);
	for (int i = 0; i < n; ++i) cin >> ch[i];
	for (int i = 0; i < n; ++i) row.rt = row.merge (row.rt, row.newnode (i));
	for (int i = 0; i < m; ++i) col.rt = col.merge (col.rt, col.newnode (i));
	read (q);
	for (int x, y; q; --q) {
		read (x, y);
		row.reverse (1, x), row.reverse (x + 1, n);
		col.reverse (1, y), col.reverse (y + 1, m);
	}
	
	row.build (row.rt, pathr);
	col.build (col.rt, pathc);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j)
			putchar (ch[pathr[i] - 1][pathc[j] - 1]);
		puts ("");
	}
		
	return 0;
}
```

---

## 作者：Otue (赞：1)

### 题目大意

有一个 $H$ 行 $W$ 列的矩阵，矩阵中每个位置都有一个小写字母。每次操作给出 $a,b$，含义是在第 $a,a+1$ 行之间切一刀，再在 $b,b+1$ 列之间切一刀，这样能得到四个矩阵；每个矩阵旋转半周，最后把四个矩阵拼起来得到新矩阵。

有 $n$ 次操作，每次形如 $a_i,b_i$，希望输出操作后的矩阵。

### 题目翻译

因为四个矩阵每个矩阵都翻转 $180$ 度，等价于对应的横纵坐标翻转。如果操作给出 $a,b$：那么等价于将横坐标 $[1,a]$ 翻转，$[a+1,n]$ 翻转。也同时将纵坐标 $[1,b]$ 翻转，$[b+1,m]$ 翻转。

那么对于纵坐标和横坐标开两颗平衡树，维护区间翻转即可。复杂度相当对！

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define PII pair<int, int>
#define _for(i, a, b) for (int i = (a); i <= (b); i++)
#define _pfor(i, a, b) for (int i = (a); i >= (b); i--)
#define int long long

const int N = 5e5 + 5, mod = 998244353, INF = 2e9;

int n, m;
vector<char> a[N];

struct stu {
	int root, idx;
	struct edge {
		int s[2], val, p, sz, lazy;
		void init(int _val, int _p) {
			val = _val; p = _p;
			sz = 1;
		}
	}tree[N];
	
	void push_up(int p) {
		tree[p].sz = tree[tree[p].s[0]].sz + tree[tree[p].s[1]].sz + 1;
	} 
	
	void push_down(int p) {
		if (tree[p].lazy) {
			swap(tree[p].s[0], tree[p].s[1]);
			tree[tree[p].s[0]].lazy ^= 1;
			tree[tree[p].s[1]].lazy ^= 1;
			tree[p].lazy = 0;
		}
	}
	
	int get(int x) {
		return tree[tree[x].p].s[1] == x;
	}
	
	void rotate(int x) {
		int y = tree[x].p, z = tree[y].p;
		int kx = get(x), ky = get(y);
		tree[z].s[ky] = x, tree[x].p = z;
		tree[y].s[kx] = tree[x].s[kx ^ 1]; tree[tree[x].s[kx ^ 1]].p = y;
		tree[x].s[kx ^ 1] = y; tree[y].p = x;
		push_up(y); push_up(x);
	}
	
	void splay(int x, int k) {
		while (tree[x].p != k) {
			int y = tree[x].p, z = tree[y].p;
			if (z != k) {
				if (get(x) ^ get(y)) rotate(x);
				else rotate(y);
			}
			rotate(x);
		}
		if (!k) root = x;
	}
	
	void insert(int v) {
		int u = root, p = 0;
		while (u) p = u, u = tree[u].s[v > tree[u].val];
		u = ++idx;
		if (p) tree[p].s[v > tree[p].val] = u;
		tree[u].init(v, p);
		splay(u, 0);
	}
	
	int get_k(int k) {
		int u = root;
		while (1) {
			push_down(u);
			if (tree[tree[u].s[0]].sz >= k) u = tree[u].s[0];
			else if (tree[tree[u].s[0]].sz + 1 == k) return u;
			else {
				k -= tree[tree[u].s[0]].sz + 1;
				u = tree[u].s[1];
			}
		}
		splay(u, 0);
		return -1;
	}
	
	void rev(int l, int r) {
		l = get_k(l), r = get_k(r + 2);
		splay(l, 0); splay(r, l);
		tree[tree[r].s[0]].lazy ^= 1;
	}
	
	int ID[N], tot;
	
	void output(int u) {
		push_down(u);
		if (tree[u].s[0]) output(tree[u].s[0]);
		if (tree[u].val >= 1 && tree[u].val <= max(n, m)) ID[++tot] = tree[u].val;
		if (tree[u].s[1]) output(tree[u].s[1]);
	}
}tr1, tr2;


signed main() {
	cin >> n >> m;
	_for(i, 1, n) {
		a[i].push_back(' ');
		_for(j, 1, m) {
			char c;
			cin >> c;
			a[i].push_back(c);
		}
	}
	tr1.insert(-INF); _for(i, 1, n) tr1.insert(i); tr1.insert(INF);
	tr2.insert(-INF); _for(i, 1, m) tr2.insert(i); tr2.insert(INF);
	int Q; cin >> Q;
	while (Q--) {
		int x, y;
		cin >> x >> y;
		tr1.rev(1, x); tr1.rev(x + 1, n);
		tr2.rev(1, y); tr2.rev(y + 1, m);
	}
	tr1.output(tr1.root); tr2.output(tr2.root);
	_for(i, 1, n) {
		_for(j, 1, m) cout << a[tr1.ID[i]][tr2.ID[j]];
		puts("");
	}
}
```

---

## 作者：CarroT1212 (赞：1)

### 题目大意

给定一个 $H$ 行 $W$ 列的仅含小写字母的字符矩阵 $A$ 和 $Q$ 次操作。每次操作给定 $a_i,b_i$，令 $R_1$ 为 $A$ 中以 $(1,1),(a_i,b_i)$ 为对角的矩阵，$R_2$ 为以 $(1,b_i+1),(a_i,W)$ 为对角的矩阵，$R_3$ 为以 $(a_i+1,1),(H,b_i)$ 为对角的矩阵，$R_4$ 为以 $(a_i+1,b_i+1),(H,W)$ 为对角的矩阵，然后将这四个矩阵分别沿着对角进行一次 $180\degree$ 翻转。输出 $Q$ 次操作之后的 $A$。

数据范围：$2 \le H,W$，$HW \le 5\times 10^5$，$1 \le Q \le 2\times 10^5$，$1 \le a_i < H$，$1 \le b_i < W$。

------------

### 解法分析

注意到翻转满足性质：操作前在同一行的元素在操作后一定仍在同一行，列同理。

所以我们可以把行与列分开单独处理。对于行，问题就转化成了“有一段从 $1$ 到 $H$ 的升序排列，给定 $Q$ 次操作，每次操作给定 $a_i$，你需要把 $[1,a_i]$ 与 $[a_i+1,H]$ 分别翻转，求最后的序列”，列也同理。最后对于每个位置就输出 $A$ 中之前求得的翻转后的对应行与翻转后的对应列相交位的元素。

转化后的问题主要有两种做法：

+ 无脑上两棵文艺平衡树。
+ 转化后问题中的翻转还满足一个性质：假设序列两头的元素也相邻，则翻转前相邻的元素翻转后一定仍然相邻。于是由这个性质我们就可以知道，不管怎么翻转，这个序列一定是循环移位后的 $1\sim N$ 的升序排列或降序排列（升序排列的反串）。所以我们只需要记录序列中的两个相邻位置在 $Q$ 次翻转后的位置，比如第 $1,2$ 位，我们就可以得知序列的排列顺序、起点，并把整个序列还原出来了。

------------

### 代码

文艺平衡树（赛时做法）：

```cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pii pair<int,int>
using namespace std;
const int N=5e5+7;
struct node { int s[2],sz,v,f,tag; } t[N];
int h,w,q,hh[N],ww[N],rt,sz,a[N],cnt1,aa[N],bb[N],n;
char inp[N];
vector <char> str[N];
int getsn(int x) { return t[t[x].f].s[1]==x; }
void upd(int x) { t[x].sz=t[t[x].s[0]].sz+t[t[x].s[1]].sz+1; }
void pshdn(int x) {
	if (!x||!t[x].tag) return;
	t[t[x].s[0]].tag^=1,t[t[x].s[1]].tag^=1,
	swap(t[x].s[0],t[x].s[1]),t[x].tag=0;
}
void trn(int x) {
	int y=t[x].f,z=t[y].f,c=getsn(x);
	pshdn(y),pshdn(x),t[y].s[c]=t[x].s[!c],t[t[x].s[!c]].f=y,t[x].s[!c]=y,
	t[y].f=x,t[x].f=z;
	if (z) t[z].s[t[z].s[1]==y]=x;
	upd(y),upd(x);
}
void splay(int x,int to) {
	while (t[x].f!=to) {
		int y=t[x].f,z=t[y].f;
		if (z!=to) trn(getsn(x)^getsn(y)?x:y);
		trn(x);
	}
	if (!to) rt=x;
}
int getrkx(int x) {
	int y=rt;
	while (1) {
		pshdn(y);
		if (x<=t[t[y].s[0]].sz) y=t[y].s[0];
		else {
			x-=t[t[y].s[0]].sz+1;
			if (x<1) return y;
			y=t[y].s[1];
		}
	}
}
int bui(int l,int r,int f) {
	if (l>r) return 0;
	int mid=l+r>>1,pos=++sz;
	t[pos].v=a[mid],t[pos].f=f,
	t[pos].s[0]=bui(l,mid-1,pos),t[pos].s[1]=bui(mid+1,r,pos),upd(pos);
	return pos;
}
void dfs(int pos) {
	if (!pos) return;
	pshdn(pos),dfs(t[pos].s[0]);
	if (t[pos].v&&t[pos].v<=n) a[++cnt1]=t[pos].v;
	dfs(t[pos].s[1]);
}
void swp(int l,int r) {
	l=getrkx(l),r=getrkx(r+2),splay(l,0),splay(r,l),
	t[t[t[rt].s[1]].s[0]].tag^=1;
}
int main() {
	scanf("%d%d",&h,&w);
	for (int i=1;i<=h;i++) {
		scanf("%s",inp+1),str[i].pb('~');
		for (int j=1;j<=w;j++) str[i].pb(inp[j]);
	}
	scanf("%d",&q);
	for (int i=1;i<=q;i++) scanf("%d%d",&aa[i],&bb[i]);
	// 行
	for (int i=0;i<=h;i++) a[i+1]=i;
	bui(1,h+2,0),rt=1;
	for (int i=1;i<=q;i++) swp(1,aa[i]),swp(aa[i]+1,h);
	n=h,dfs(rt);
	for (int i=1;i<=h;i++) hh[i]=a[i];
	// 列
	memset(t,0,sizeof(t)),memset(a,0,sizeof(a));
	for (int i=0;i<=w;i++) a[i+1]=i;
	sz=0,bui(1,w+2,0),rt=1;
	for (int i=1;i<=q;i++) swp(1,bb[i]),swp(bb[i]+1,w);
	n=w,cnt1=0,dfs(rt);
	for (int i=1;i<=w;i++) ww[i]=a[i];
	for (int i=1;i<=h;i++) {
		for (int j=1;j<=w;j++) printf("%c",str[hh[i]][ww[j]]);
		printf("\n");
	}
	return 0;
}
```

定位：

```cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pii pair<int,int>
using namespace std;
const int N=5e5+7;
int h,w,q,ha=1,hb=2,wa=1,wb=2,hh[N],ww[N];
char inp[N];
vector <char> str[N];
int main() {
	scanf("%d%d",&h,&w);
	for (int i=1;i<=h;i++) {
		scanf("%s",inp+1),str[i].pb('~');
		for (int j=1;j<=w;j++) str[i].pb(inp[j]);
	}
	scanf("%d",&q);
	for (int x,y;q--;)
		scanf("%d%d",&x,&y),
		ha=ha<=x?x-ha+1:h-ha+x+1,hb=hb<=x?x-hb+1:h-hb+x+1,
		wa=wa<=y?y-wa+1:w-wa+y+1,wb=wb<=y?y-wb+1:w-wb+y+1; // 模拟行列各两个位置的翻转
	// 行
	if (hb!=ha-1) { // 是循环移位后的升序排列
		for (int i=ha;i<=h;i++) hh[i]=i-ha+1;
		for (int i=1;i<ha;i++) hh[i]=i+h-ha+1;
	}
	else { // 是循环移位后的降序排列（升序排列的反串）
		for (int i=ha;i;i--) hh[i]=ha-i+1;
		for (int i=h;i>ha;i--) hh[i]=h-i+ha+1;
	}
	// 列
	if (wb!=wa-1) { // 升序排列
		for (int i=wa;i<=w;i++) ww[i]=i-wa+1;
		for (int i=1;i<wa;i++) ww[i]=i+w-wa+1;
	}
	else { // 降序排列
		for (int i=wa;i;i--) ww[i]=wa-i+1;
		for (int i=w;i>wa;i--) ww[i]=w-i+wa+1;
	}
	for (int i=1;i<=h;i++) {
		for (int j=1;j<=w;j++) printf("%c",str[hh[i]][ww[j]]);
		printf("\n");
	}
	return 0;
}
```

---

## 作者：spire001 (赞：0)

## AT_arc153_b 

### 题目大意

给你一个 $n\times m$ 的矩阵，有 $Q$ 次操作，每次操作给 $a,b$ 两个参数，你需要翻转 $(1,1)$ 与 $(a,b)$，$(a+1,1)$ 与 $(n,b)$，$(1,b+1)$ 与 $(a,m)$，$(a+1,b+1)$ 与 $(n,m)$ 之间形成的矩形。

### 思路

文艺平衡树。

平凡的想法是每一行的处理。

维护一个横坐标序列，每个横坐标维护纵坐标对应的字母。

$\mathcal O(n\log_2m) $ 交换即可。

总复杂度 $\mathcal O(nQ\log_2m)$。

注意到 $\min(n,m)\le \sqrt{nm}$。

如果交换矩阵长宽以及询问的 $a,b$，并不影响结果。

所以适当交换 $n,m$ 复杂度降为 $\mathcal O(Q\sqrt{nm}\log_2m )$。

### 不能通过的代码

```cpp
#pragma GCC optimize("-Ofast", "-fno-stack-protector")
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>
#include <numeric>
#include <ext/rope>

using namespace std;
using namespace __gnu_cxx;

typedef long long LL;
template <typename T1, typename T2> inline void cmax(T1 &A, const T2 &B)  { if (A < B) A = B; return; }
template <typename T1, typename T2> inline void cmin(T1 &A, const T2 &B)  { if (A > B) A = B; return; }
template <typename T1, typename T2, int mod = 998244353> inline void ad(T1 &A, const T2 &B) { A = (A + B) % mod; return; }
template <typename T1, typename T2, int mod = 998244353> inline void sb(T1 &A, const T2 &B) { A = (A + mod - B) % mod; return; }

int swap_tag;

constexpr int N = 500010;
int n, m;

crope cr[N][2];
rope<int> ir[2];
rope<int> gs(rope<int> &r, int l, int _r) { return r.substr(r.begin() + l, r.begin() + _r + 1); }
crope gs(crope &r, int l, int _r) { return r.substr(r.begin() + l, r.begin() + _r + 1); }

void askc(int l, int r, int pos)
{
	const crope tmp = gs(cr[pos][0], l, r);
	cr[pos][0] = gs(cr[pos][0], 0, l - 1) + gs(cr[pos][1], m - r + 1, m - l + 1) + gs(cr[pos][0], r + 1, m);
	cr[pos][1] = gs(cr[pos][1], 0, m - r) + tmp + gs(cr[pos][1], m - l + 2, m);
	return;
}
template<typename T> void print(T&);
void aski(int l, int r)
{
	const rope<int> tmp = gs(ir[0], l, r);
//	print(tmp);
	ir[0] = gs(ir[0], 0, l - 1) + gs(ir[1], n - r + 1, n - l + 1) + gs(ir[0], r + 1, n);
	ir[1] = gs(ir[1], 0, n - r) + tmp + gs(ir[1], n - l + 2, n);
	return;
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr); cout.tie(nullptr);

  cin >> n >> m;
  
  vector<vector<char>> s = vector<vector<char>>(n + 1, vector<char>(m + 1));
  
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      cin >> s[i][j];
  
  ir[0].append(0); ir[1].append(0);
  
  if (n > m) 
  {
    for (int i = 1; i <= m; i++)
    {
      ir[0].append(i);
      ir[1].append(m - i + 1);
      cr[i][0].append('$');
      cr[i][1].append('$');
      for (int j = 1; j <= n; j++)
      {
        cr[i][0].append(s[j][i]);
        cr[i][1].append(s[n - j + 1][i]);
      }
    }
    swap(n, m);
    swap_tag = 1;
  }
  else 
  {
    for (int i = 1; i <= n; i++)
    {
      ir[0].append(i);
      ir[1].append(n - i + 1);
      cr[i][0].append('$');
      cr[i][1].append('$');
      for (int j = 1; j <= m; j++)
      {
        cr[i][0].append(s[i][j]);
        cr[i][1].append(s[i][m - j + 1]);  
      }
    }
  }
  
  int T; cin >> T;
  
  while (T--)
  {
    int x, y;
    
    cin >> x >> y;
    
    if (swap_tag) swap(x, y); 
    
    aski(1, x);
    aski(x + 1, n);
    
    for (int i = 1; i <= n; i++)
    {
      askc(1, y, i);
      askc(y + 1, m, i);
    }
  }
  if (swap_tag)
  {
    s = vector<vector<char>>(n + 1, vector<char>(m + 1));
  }
  for (int i = 1; i <= n; i++)
  {
    int x = ir[0][i];
    for (int j = 1; j <= m; j++)
      s[i][j] = cr[x][0][j];
  }
  
  if (swap_tag)
    for (int i = 1; i <= m; i++, cout << '\n')
      for (int j = 1; j <= n; j++)
        cout << s[j][i];
  else 
    for (int i = 1; i <= n; i++, cout << '\n')
      for (int j = 1; j <= m; j++)
        cout << s[i][j];
  
  return 0;
}
```

理论上能过，但是卡常，况且我为了简单（其实是因为我不会 `FHQ Treap`）写的是常数巨大的 `rope`。

但是从上面的代码看出每一行的的变换都是相同的，所以只需要维护两个文艺平衡树就可以了。

所以改进以后复杂度就是 $\mathcal O(nm\log_2m)$，常数巨大仍可以通过此题。

### 代码

```cpp
#pragma GCC optimize("-Ofast", "-fno-stack-protector")
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>
#include <numeric>
#include <ext/rope>

using namespace std;
using namespace __gnu_cxx;

typedef long long LL;
template <typename T1, typename T2> inline void cmax(T1 &A, const T2 &B)  { if (A < B) A = B; return; }
template <typename T1, typename T2> inline void cmin(T1 &A, const T2 &B)  { if (A > B) A = B; return; }
template <typename T1, typename T2, int mod = 998244353> inline void ad(T1 &A, const T2 &B) { A = (A + B) % mod; return; }
template <typename T1, typename T2, int mod = 998244353> inline void sb(T1 &A, const T2 &B) { A = (A + mod - B) % mod; return; }

int swap_tag;

constexpr int N = 500010;
int n, m;

crope cr[N][2];
rope<int> ir[2], ir1[2];
rope<int> gs(rope<int> &r, int l, int _r) { return r.substr(r.begin() + l, r.begin() + _r + 1); }
crope gs(crope &r, int l, int _r) { return r.substr(r.begin() + l, r.begin() + _r + 1); }

template<typename T> void print(T&);
void aski1(int l, int r)
{
	const rope<int> tmp = gs(ir1[0], l, r);
	ir1[0] = gs(ir1[0], 0, l - 1) + gs(ir1[1], m - r + 1, m - l + 1) + gs(ir1[0], r + 1, m);
	ir1[1] = gs(ir1[1], 0, m - r) + tmp + gs(ir1[1], m - l + 2, m);
	return;
}
template<typename T> void print(T&);
void aski(int l, int r)
{
	const rope<int> tmp = gs(ir[0], l, r);
	ir[0] = gs(ir[0], 0, l - 1) + gs(ir[1], n - r + 1, n - l + 1) + gs(ir[0], r + 1, n);
	ir[1] = gs(ir[1], 0, n - r) + tmp + gs(ir[1], n - l + 2, n);
	return;
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr); cout.tie(nullptr);

  cin >> n >> m;
  
  vector<vector<char>> s = vector<vector<char>>(n + 1, vector<char>(m + 1));
  
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      cin >> s[i][j];
  
  ir[0].append(0); ir[1].append(0);
  ir1[0].append(0); ir1[1].append(0);
  for (int i = 1; i <= n; i++)
  {
    ir[0].append(i);
    ir[1].append(n - i + 1);
  }
  for (int i = 1; i <= m; i++)
  {
    ir1[0].append(i);
    ir1[1].append(m - i + 1);
  }
  
  int T; cin >> T;
  
  while (T--)
  {
    int x, y;
    
    cin >> x >> y;
    
    aski(1, x);
    aski(x + 1, n);
    aski1(1, y);
    aski1(y + 1, m);
  }
  
  for (int i = 1; i <= n; i++, cout << '\n')
  {
    int x = ir[0][i];
    for (int j = 1; j <= m; j++)
      cout << s[x][ir1[0][j]];
  }
    
  return 0;
}
```

---

## 作者：XYQ_102 (赞：0)

发现行和列实际上是独立的，每次操作 $a,b$ 实际上我们相当于依次做了这四步：把第 $1\cdots a$ 行翻转（注意是行与行之间的顺序翻转，不是把每行的内容翻转，后面的"翻转"同理）；把第 $a+1\cdots n$ 行翻转；把第 $1\cdots b$ 列翻转；把第 $b+1\cdots m$ 列翻转。如果我们能求出两个数组 $r,c$，$r_i$ 表示所有操作做完后，原来的第 $i$ 行被移到了第 $r_i$ 行，第 $j$ 列被移到了第 $c_j$ 列，那么原来的 $a_{i,j}$ 就被移动到了 $(r_i,c_j)$。用两个平衡树维护两维的翻转情况即可。
## Code
```cpp
#include <bits/stdc++.h>
 
#define rep(i,n) for(int i=0;i<n;++i)
#define repn(i,n) for(int i=1;i<=n;++i)
#define LL long long
#define pii pair <int,int>
#define fi first
#define se second
#define mpr make_pair
#define pb push_back
 
void fileio()
{
  #ifdef LGS
  freopen("in.txt","r",stdin);
  freopen("out.txt","w",stdout);
  #endif
}
void termin()
{
  #ifdef LGS
  std::cout<<"\n\nEXECUTION TERMINATED";
  #endif
  exit(0);
}
 
using namespace std;
 
int to[2][500010];
 
mt19937 rndtr(114514);
struct node{int val,key,ls,rs,sz,tag;};
struct tr
{
	int len;
	node a[1000000];
	int newNode(int x){a[++len].val=x;a[len].key=rndtr();a[len].ls=a[len].rs=a[len].tag=0;a[len].sz=1;return len;}
  void addTag(int x)
  {
    if(x==0) return;
    swap(a[x].ls,a[x].rs);a[x].tag^=1;
  }
  void pushDown(int x)
  {
    if(x==0||a[x].tag==0) return;
    addTag(a[x].ls);addTag(a[x].rs);
    a[x].tag=0;
  }
	void calc(int x){if(x==0) return;a[x].sz=a[a[x].ls].sz+1+a[a[x].rs].sz;}
	int merge(int x,int y)
	{
		if(x==0||y==0) return max(x,y);
    pushDown(x);pushDown(y);
		int ret;
		if(a[x].key<=a[y].key){ret=x;a[ret].rs=merge(a[ret].rs,y);}
		else{ret=y;a[ret].ls=merge(x,a[ret].ls);}
		calc(ret);return ret;
	}
	pii splitSz(int x,int y)//左边y个
	{
		if(x==0) return mpr(0,0);if(y==0) return mpr(0,x);if(y==a[x].sz) return mpr(x,0);
    pushDown(x);
		int ret1,ret2;
		if(a[a[x].ls].sz>=y){pii p=splitSz(a[x].ls,y);ret1=p.fi;ret2=x;a[ret2].ls=p.se;}
		else{pii p=splitSz(a[x].rs,y-1-a[a[x].ls].sz);ret1=x;a[ret1].rs=p.fi;ret2=p.se;}
		calc(ret1);calc(ret2);return mpr(ret1,ret2);
	}
  void build(int x,int frt,int w)
  {
    if(x==0) return;
    to[w][a[x].val]=frt+a[a[x].ls].sz;
    pushDown(x);
    build(a[x].ls,frt,w);build(a[x].rs,frt+a[a[x].ls].sz+1,w);
  }
}row,col;
 
int n,m;
string a[500010],ans[500010];
char c[500010];
 
int main()
{
  fileio();
 
  cin>>n>>m;
  rep(i,n)
  {
    scanf("%s",c);
    a[i]=ans[i]=c;
  }
  row.len=0;col.len=0;
  int rootr=0,rootc=0;
  rep(i,n) rootr=row.merge(rootr,row.newNode(i));
  rep(i,m) rootc=col.merge(rootc,col.newNode(i));
  int q;cin>>q;
  rep(qn,q)
  {
    int x,y;
    scanf("%d%d",&x,&y);
    pii p=row.splitSz(rootr,x);
    row.addTag(p.fi);row.addTag(p.se);
    rootr=row.merge(p.fi,p.se);
    p=col.splitSz(rootc,y);
    col.addTag(p.fi);col.addTag(p.se);
    rootc=col.merge(p.fi,p.se);
  }
  row.build(rootr,0,0);
  col.build(rootc,0,1);
  rep(i,n) rep(j,m) ans[to[0][i]][to[1][j]]=a[i][j];
  rep(i,n) printf("%s\n",ans[i].c_str());
 
  termin();
}
```

---

## 作者：NaN_HQJ2007_NaN (赞：0)

[[ARC153B] Grid Rotations](https://www.luogu.com.cn/problem/AT_arc153_a)

有思维含量的一题。

我们横纵坐标分开考虑，对于每一个矩形，每次操作会使其内部元素的横坐标上下对调。

纵坐标也同理，左右对调。

而这种反转操作我们显然可以直接用两棵文艺平衡树维护，复杂度 $O(n\log n)$。

标程的做法更巧妙一下。我们可以把一条链收尾相接，两段序列的反转就相当于圆的反转。

所以我们可以只定位其中两个点，然后根据其最终位置填补出剩下元素。复杂度 $O(n)$。

代码是第一种做法。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;
int n, m, q, a[N], b[N], rt = 0, x[N], y[N], tot = 0;
char c[N];
struct node{
	int l, r, siz, v, lazy, pri;
}t[N];
int d(int i, int j) {
	return (i - 1) * m + j;
}
void add(int x) {t[x].v = x; t[x].pri = rand(); t[x].siz = 1; t[x].l = t[x].r = 0;}
void pushdown(int id) {
	if (t[id].lazy == 0) return;
	swap(t[id].l, t[id].r);
	t[t[id].l].lazy ^= 1;
	t[t[id].r].lazy ^= 1;
	t[id].lazy = 0;
}
void pushup(int id) {
	t[id].siz = t[t[id].l].siz + t[t[id].r].siz + 1;
}
void split(int id, int k, int &l, int &r) {
	if (id == 0) {
		l = r = 0;
		return;
	}
	pushdown(id);
	int tmp = t[t[id].l].siz + 1;
	if (tmp <= k) {
		l = id;
		split(t[id].r, k - tmp, t[id].r, r);
	} else {
		r = id;
		split(t[id].l, k, l, t[id].l);
	}
	pushup(id);
}
int merge(int l, int r) {
	if (!l || !r) return l + r;
	if (t[l].pri < t[r].pri) {
		pushdown(l);
		t[l].r = merge(t[l].r, r);
		pushup(l);
		return l;
	} else {
		pushdown(r);
		t[r].l = merge(l, t[r].l);
		pushup(r);
		return r;
	}
}
void dfs1(int u) {
	pushdown(u);
	if (t[u].l) dfs1(t[u].l);
	x[++tot] = t[u].v;
	if (t[u].r) dfs1(t[u].r);
}
void dfs2(int u) {
	pushdown(u);
	if (t[u].l) dfs2(t[u].l);
	y[++tot] = t[u].v;
	if (t[u].r) dfs2(t[u].r);
}
void huan(int l, int r) {
	int t1, t2, t3, tt;
	split(rt, r, t1, t2);
	split(t1, l - 1, t1, t3);
	t[t3].lazy ^= 1;
	rt = merge(merge(t1, t3), t2);
}
int main() {
	srand(time(0));
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> c[d(i, j)];
		}
	}
	for (int i = 1; i <= n; ++i) {
		add(i);
		rt = merge(rt, i);
	}
	cin >> q;
	for (int i = 1; i <= q; ++i) {
		cin >> a[i] >> b[i];
		huan(1, a[i]); huan(a[i] + 1, n);
	}
	dfs1(rt);
	rt = tot = 0;
	for (int i = 1; i <= m; ++i) {
		add(i);
		rt = merge(rt, i);
	}
	for (int i = 1; i <= q; ++i) {
		huan(1, b[i]); huan(b[i] + 1, m);
	}
	dfs2(rt);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cout << c[d(x[i], y[j])];
		}
		cout << endl;
	}
	return 0;
}

```


---

## 作者：rui_er (赞：0)

一次操作是把四个子矩形分别旋转 $180^\circ$。不难发现，可以横纵坐标分别考虑，则该操作变为横坐标的两段区间分别翻转、纵坐标的两段区间分别翻转。

区间翻转操作、最后输出数列是 [文艺平衡树](https://www.luogu.com.cn/problem/P3391) 的基本操作，搞两棵平衡树维护即可。

时间复杂度 $\Theta(nm+(n+q)\log n+(m+q)\log m)$。

实际上有解法可以做到 $\Theta(nm+q)$，但本解法足以通过本题。

```cpp
// Problem: B - Grid Rotations
// Contest: AtCoder - AtCoder Regular Contest 153
// URL: https://atcoder.jp/contests/arc153/tasks/arc153_b
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;
const int N = 5e5+5;

int n, m, q;
vector<int> ppr, ppc;
vector<string> s;
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}
struct Node {
	int val, rnd, sz, lc, rc, rev;
	Node(int a=0, int b=0) : val(a), rnd(rand()), sz(b), lc(0), rc(0), rev(0) {}
	~Node() {}
};
struct FHQTreap {
	Node t[N];
	int sz, rt, L, M, R;
	int newNode(int x) {
		t[++sz] = Node(x, 1);
		return sz;
	}
	void pushup(int u) {
		t[u].sz = t[t[u].lc].sz + t[t[u].rc].sz + 1;
	}
	void pushdown(int u) {
		if(!t[u].rev) return;
		if(t[u].lc) t[t[u].lc].rev ^= 1;
		if(t[u].rc) t[t[u].rc].rev ^= 1;
		swap(t[u].lc, t[u].rc);
		t[u].rev = 0; 
	}
	void split(int u, int lim, int& x, int& y) {
		if(!u) x = y = 0;
		else {
			pushdown(u);
			if(t[t[u].lc].sz < lim) {
				x = u;
				split(t[u].rc, lim-t[t[u].lc].sz-1, t[u].rc, y);
			}
			else {
				y = u;
				split(t[u].lc, lim, x, t[u].lc);
			}
			pushup(u);
		}
	}
	int merge(int u, int v) {
		if(!u || !v) return u | v;
		if(t[u].rnd < t[v].rnd) {
			pushdown(u);
			t[u].rc = merge(t[u].rc, v);
			pushup(u);
			return u;
		}
		else {
			pushdown(v);
			t[v].lc = merge(u, t[v].lc);
			pushup(v);
			return v;
		}
	}
	void reverse(int l, int r) {
		split(rt, l-1, L, R);
		split(R, r-l+1, M, R);
		t[M].rev ^= 1;
		rt = merge(L, merge(M, R));
	}
	void get(int u, vector<int>& a) {
		pushdown(u);
		if(t[u].lc) get(t[u].lc, a);
		a.push_back(t[u].val);
		if(t[u].rc) get(t[u].rc, a);
	}
}pr, pc;

int main() {
	scanf("%d%d", &n, &m);
	s.resize(n);
	rep(i, 0, n-1) cin>>s[i];
	rep(i, 0, n-1) pr.rt = pr.merge(pr.rt, pr.newNode(i));
	rep(j, 0, m-1) pc.rt = pc.merge(pc.rt, pc.newNode(j));
	for(scanf("%d", &q); q; q--) {
		int x, y;
		scanf("%d%d", &x, &y);
		pr.reverse(1, x); pr.reverse(x+1, n);
		pc.reverse(1, y); pc.reverse(y+1, m);
	}
	pr.get(pr.rt, ppr);
	pc.get(pc.rt, ppc);
	rep(i, 0, n-1) {
		rep(j, 0, m-1) putchar(s[ppr[i]][ppc[j]]);
		puts("");
	}
	return 0;
}
```

---

