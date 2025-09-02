# [ICPC 2018 Qingdao R] Soldier Game

## 题目描述

DreamGrid 和 BaoBao 正在玩一个游戏。游戏中有 $n$ 名士兵，编号从 $1$ 到 $n$。第 $i$ 个士兵的战斗力为 $a_i$。DreamGrid 和 BaoBao 将根据以下规则把士兵分成若干个队伍：

- 一个队伍必须由 1 或 2 名士兵组成。
- 每个士兵必须属于且仅属于一个队伍。
- 如果一个队伍由两名士兵组成（假设他们是第 $i$ 个和第 $j$ 个士兵），则必须满足 $|i - j| = 1$。

一个队伍的战斗力定义为队伍成员的战斗力之和。为了公平起见，他们希望在分组后最大队伍战斗力与最小队伍战斗力之间的差值最小化。你需要找出这个最小的差值。

## 说明/提示

我们现在解释第一个样例测试用例。所有可能的分组如下所示。

| 分组 | 差值 | 分组 | 差值 |
| :-: | :-: | :-: | :-:|
|[-1], [4], [2], [1], [1] | 4 - (-1) = 5| [-1, 4], [2], [1], [1] | 3 - 1 = 2 |
| [-1], [4], [2], [1, 1] | 4 - (-1) = 5 | [-1], [4, 2], [1, 1] | 6 - (-1) = 7 |
| [-1], [4], [2, 1], [1] | 4 - (-1) = 5 |  [-1, 4], [2], [1, 1] | 3 - 2 = 1 |
| [-1], [4, 2], [1], [1] | 6 - (-1) = 7 | [-1, 4], [2, 1], [1] | 3 - 1 = 2 |

所以答案是 $\min(5, 5, 5, 7, 2, 7, 1, 2) = 1$。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3
5
-1 4 2 1 1
4
1 3 2 4
1
7```

### 输出

```
1
2
0```

# 题解

## 作者：sidekick257 (赞：4)

### 简述题意

给数列分组，可以一个一组也可以两个一组，两个一组必须要挨着，定义一个组的权值是这个组内所有数字的权值的和，问你所有分组方案中权值最大的组减去权值最小的组得到的值的最小值。

### 做法

观察到最大值只有 $O(n)$ 种，具体的说是 $2n-1$ 种。

于是考虑枚举最大值，判断能找到的最大的最小值。

找最小值的时候你会规定一些分组不能选，一些分组可以选。

考虑动态规划，$f_{i,0/1}$ 表示考虑到第 $i$ 个数，最后一个数是不是完整的一组。

然后你会发现转移是一个矩阵，分组哪些可以选和不可以选也可以用矩阵的单点修来表示，于是这题就做完了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,inf=1e18;
char buf[1<<23],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
int read(){
    int x=0,f=1;
    char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
	return x*f;
}
int n,a[N],m;
struct mxr{
	int v,x,op;
}b[N];
struct martix{
	int a00,a01,a10,a11;
	martix operator * (martix a){
		return{
			max(min(a00,a.a00),min(a01,a.a10)),
			max(min(a00,a.a01),min(a01,a.a11)),
			max(min(a10,a.a00),min(a11,a.a10)),
			max(min(a10,a.a01),min(a11,a.a11))
		};
	}
}t[N*4],e[N];
struct martix1{
    int a0,a1;
	martix1 operator * (martix a){
		return{
			max(min(a0,a.a00),min(a1,a.a10)),
			max(min(a0,a.a01),min(a1,a.a11))
		};
	}
}I={inf,inf};
#define ls(x) (x<<1)
#define rs(x) ((x<<1)|1)
void up(int x){
	t[x]=t[ls(x)]*t[rs(x)];
}
void build(int x,int l,int r){
    if(l==r){
		t[x]=e[l];
        return;
    }
    int mid=(l+r)>>1;
    build(ls(x),l,mid),build(rs(x),mid+1,r);
	up(x);
}
void update(int x,int st,int ed,int k,int v,int op){
    if(st==ed){
        if(op) t[x].a00=v;
        else t[x].a10=v;
        return;
    }
    int mid=(st+ed)>>1;
    if(k<=mid) update(ls(x),st,mid,k,v,op);
    else update(rs(x),mid+1,ed,k,v,op);
	up(x);
}
void solve(){
    m=0;
	n=read();
	for(int i=1;i<=n;i++){
        a[i]=read();
        b[++m]={a[i],i,1};
        e[i]={-inf,inf,-inf,-inf};
    }
    if(n==1||n==2){
        cout<<0<<"\n";
        return;
    }
	for(int i=2;i<=n;i++){
        b[++m]={a[i]+a[i-1],i,0};
    }
	sort(b+1,b+m+1,[](mxr a,mxr b){return a.v<b.v;});
    build(1,1,n);
	int ans=inf;
	for(int i=1;i<=m;i++){
		update(1,1,n,b[i].x,b[i].v,b[i].op);
        ans=min(ans,b[i].v-(I*t[1]).a0);
	}
    cout<<ans<<"\n";
}
signed main(){
    int t=read();
    while(t--) solve();
	return 0;
}
```



---

## 作者：苏联小渣 (赞：3)

考虑问题的弱化版，如果固定最大和最小值怎么做？

那么问题就转化成了，有一些 $a_i$ 可以单独选，有一些 $a_i,a_{i-1}$ 可以一起选，问是否存在一组可行解。

容易想到 dp，设 $f_i$ 表示是否存在以 $i$ 为末尾的可行划分。有转移，$f_i=f_{i-2} \times [l \le a_{i-1}+a_i \le r] \text{ or } f_{i-1} \times [l \le a_i \le r]$。

对于极差最小，可以考虑双指针。由于有用的决策数只有 $2n$ 个，所以可以直接跑双指针。固定 $l$，我们要找到一个最小的 $r$，使得只保留在 $[l,r]$ 中的数，存在一组可行解。

那么每次增加和删除，都会使得一些位置的某个转移系数从 $0$ 变成 $1$ 或者从 $1$ 变成 $0$。而修改次数的总数是 $O(n)$ 级别的（每个数最多被加一次删一次），所以可以直接想办法维护这个 dp。

动态修改，维护 dp，可以考虑用矩阵维护。我们把 dp 转移方程写成矩阵形式：

$$
\begin{bmatrix}
f_i\\f_{i-1}
\end{bmatrix}

=

\begin{bmatrix}
[l \le a_i \le r] & [l \le a_{i-1}+a_i \le r] \\
1 & 0
\end{bmatrix}

 \times \begin{bmatrix}
f_{i-1}\\f_{i-2}
\end{bmatrix}
$$

用线段树维护这个矩阵乘法，然后查询 $f_n$ 就相当于查询所有矩阵乘起来后左上角的那个值。由于我不知道或和乘法结合起来有没有结合律，所以我是直接加起来取模的（因为最坏退化到斐波那契数列，所以必须要找一个质数取模）。时间复杂度 $O(cn \log n)$，其中 $c$ 是矩阵乘法的常数，这里 $c=2^3$。
### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define lc(x) x<<1
#define rc(x) x<<1|1
int t, n, m, cnt, a[100010], b[200010];
ll ans;
struct matrix{
	int c[2][2];
}tag[400010];
const int mo = 998244353;
map <int, int> mp;
map <int, int> :: iterator it;
vector <int> posx[200010], posy[200010];
matrix mul(matrix x, matrix y){
	matrix ret;
	for (int i=0; i<2; i++){
		for (int j=0; j<2; j++){
			ret.c[i][j] = 0;
			for (int k=0; k<2; k++){
				ret.c[i][j] = (ret.c[i][j] + 1LL * x.c[i][k] * y.c[k][j] % mo) % mo;
			}
		}
	}
	return ret;
}
matrix operator * (matrix x, matrix y){
	return mul(x, y);
}
void pushup(int k){
	tag[k] = tag[rc(k)] * tag[lc(k)];
}
void build(int k, int l, int r){
	if (l == r){
		tag[k].c[0][0] = tag[k].c[0][1] = tag[k].c[1][1] = 0;
		tag[k].c[1][0] = 1;
		return ;
	}
	int mid = l + r >> 1;
	build(lc(k), l, mid);
	build(rc(k), mid+1, r);
	pushup(k); 
}
void modify(int k, int l, int r, int x, int y, int op){
	if (l == r){
		if (y == 1) tag[k].c[0][0] = op;
		else tag[k].c[0][1] = op;
		return ;
	}
	int mid = l + r >> 1;
	if (x <= mid) modify(lc(k), l, mid, x, y, op);
	else modify(rc(k), mid+1, r, x, y, op);
	pushup(k);
}
int main(){
	scanf ("%d", &t);
	while (t --){
		scanf ("%d", &n);
		for (int i=1; i<=cnt; i++){
			posx[i].clear(); posy[i].clear();
		}
		mp.clear(); cnt = m = 0;
		for (int i=1; i<=n; i++){
			scanf ("%d", &a[i]);
			if (i > 1) mp[a[i]+a[i-1]] = 1;
			mp[a[i]] = 1;
		} 
		for (it=mp.begin(); it!=mp.end(); it++){
			it->second = ++cnt;
			b[++m] = it->first;
		}
		for (int i=1; i<=n; i++){
			posx[mp[a[i]]].push_back(i);
			if (i > 1) posy[mp[a[i]+a[i-1]]].push_back(i);
		}
		build(1, 1, n);
		ans = 1e18;
		for (int i=1, j=0; i<=m; i++){
			while (j < m && !tag[1].c[0][0]){
				j ++;
				int now = mp[b[j]];
				for (int k=0; k<posx[now].size(); k++){
					modify(1, 1, n, posx[now][k], 1, 1);
				}
				for (int k=0; k<posy[now].size(); k++){
					modify(1, 1, n, posy[now][k], 0, 1);
				}
			}
			if (j == m && !tag[1].c[0][0]) break;
			ans = min(ans, (ll)b[j] - (ll)b[i]);
			int now = mp[b[i]];
			for (int k=0; k<posx[now].size(); k++){
				modify(1, 1, n, posx[now][k], 1, 0);
			}
			for (int k=0; k<posy[now].size(); k++){
				modify(1, 1, n, posy[now][k], 0, 0);
			}
		}
		printf ("%lld\n", ans);
	}
	return 0;
}

```

---

## 作者：Conan15 (赞：2)

## 题意简述

有一个长度为 $n$ 的数列 $a$，你需要把它分成若干组，使得每组都只有**一个或两个元素**。

每个组的权值定义为该组所有元素之和，请求出**最大组权值**与**最小组权值**的**差值**。

有多测，$1 \leq n \leq 10^5$，$-10^9 \leq a_i \leq 10^9$，$\sum n \leq 10^6$。

## 题解

这题可以采用**广义矩阵快速幂**（本质上是“动态”DP）做，但有另一种更简单的方法。

如果暴力对每一个元素进行分组，时间复杂度显然是过不了的，所以考虑优化。


------------


由于要求出最大和最小组权值的差值，然而在遍历数组的过程中这两个值都会不断变化，所以我们考虑**固定最小值**，并求出**最大值的最小值**使得差值最小。

如何固定最小值？**枚举**即可。把每个元素单独一组和两个元素一组的权值都求出来，再枚举这些权值。

容易发现只有 $O(n)$ 个权值，准确地说是有 $2 \times n - 1$ 个。


------------


然后我们对这些权值进行**排序**。

显然，我们固定了最小值，接下来的分组产生的组权值**就不能比目前最小值小**。所以对权值排序，保证权值的有序性，使得后续分组的权值都不小于当前固定的最小值。


------------


问题就转化为了：知道最小值，如何求出后续分组**最小的最大组权值**？（即如何分组使得最大值最小？）

考虑从**区间**扩展到**全局数列**，发现最大组权值可以通过两个小区间合并出大区间的答案。具有“归并”的性质，所以尝试用**线段树**处理。

- 由于肯定要求出整个区间的答案，所以用 `all` 来记录它。
- 由于两个区间需要合并，而合并有一种**特殊情况**：两个区间相邻的端点合并为一组，所以我们需要记录如下信息：
    - 除了右端点的区间答案 `ls`（`left`）、除了左端点的区间答案 `rs`（`right`），除去左右端点的答案 `md`（由于重名缩写 `mid`）。
    - 这四个值显然都可以通过两个子区间求出。
- 这四个值的转移方式都一样，对以下两个值取min：
    - 合并相邻端点为一个组，两个较短子区间和新的一组（端点）拼在一起。
    - 不创建新的组，直接两个区间拼在一起

```cpp
void pushup(int u) {
	int mid = tr[u].l + tr[u].r >> 1;   //mid 为左子区间的右端点，mid + 1 为右子区间的左端点
	long long val = a[mid + n]; //这两个端点的权值和
	
	tr[u].ls = min(max({val, tr[u << 1].ls, tr[u << 1 | 1].md}), max(tr[u << 1].all, tr[u << 1 | 1].ls));
	tr[u].rs = min(max({val, tr[u << 1].md, tr[u << 1 | 1].rs}), max(tr[u << 1].rs, tr[u << 1 | 1].all));
	tr[u].md = min(max({val, tr[u << 1].md, tr[u << 1 | 1].md}), max(tr[u << 1].rs, tr[u << 1 | 1].ls));
	tr[u].all = min(max({val, tr[u << 1].ls, tr[u << 1 | 1].rs}), max(tr[u << 1].all, tr[u << 1 | 1].all));
}
```

那么就可以直接遍历排序后的权值，分别以每个数作为**当前最小值**。

后续分组最大权值即为 `tr[1].all`，也就是整个区间的 `all` 最大值。

由于建树的时候把所有权值都插入到线段树中，所以每次计算完一个最小值，就要把它从线段树中删除。

### 注意事项

1. 不开 `long long` 见祖宗。
2. 正无穷如果取 `0x3f3f3f3f` 太小。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 15;
long long INF = 1e15;
int n;
long long a[N << 1];

struct Tree {
	int l, r;
	long long ls, rs, md, all;	//无右端点、无左端点、无左右端点、有左右端点	的最大权值
} tr[N << 2];

void pushup(int u) {
	int mid = tr[u].l + tr[u].r >> 1;
	long long val = a[mid + n];
	tr[u].ls = min(max({val, tr[u << 1].ls, tr[u << 1 | 1].md}), max(tr[u << 1].all, tr[u << 1 | 1].ls));
	tr[u].rs = min(max({val, tr[u << 1].md, tr[u << 1 | 1].rs}), max(tr[u << 1].rs, tr[u << 1 | 1].all));
	tr[u].md = min(max({val, tr[u << 1].md, tr[u << 1 | 1].md}), max(tr[u << 1].rs, tr[u << 1 | 1].ls));
	tr[u].all = min(max({val, tr[u << 1].ls, tr[u << 1 | 1].rs}), max(tr[u << 1].all, tr[u << 1 | 1].all));
}

void update(int u) {
	tr[u].ls = tr[u].rs = -INF;
	tr[u].md = INF;
	tr[u].all = a[tr[u].l];
}

void build(int u, int l, int r) {
	tr[u].l = l, tr[u].r = r;
	if (l == r) {
		update(u);
		return;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	pushup(u);
}

void change(int u, int x) {
	if (tr[u].l == tr[u].r) {
		update(u);
		return;
	}
	int mid = tr[u].l + tr[u].r >> 1;
	if (x <= mid) change(u << 1, x);
	else change(u << 1 | 1, x);
	pushup(u);
}

long long b[N << 1], m = 0, ans;

bool cmp(int x, int y) {
	return a[x] < a[y];
}

int main() {
	long long T; scanf("%lld", &T);
	while (T--) {
		scanf("%lld", &n); m = n;
		for (register int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		for (register int i = 1; i < n; i++) a[++m] = a[i] + a[i + 1];
		for (register int i = 1; i <= m; i++) b[i] = i; a[m + 1] = INF;
		sort(b + 1, b + 1 + m, cmp);
		build(1, 1, n);
		ans = INF;
		for (register int i = 1; i <= m; i++) {
			if (tr[1].all == INF) break;
			ans = min(ans, tr[1].all - a[b[i]]);
			a[b[i]] = INF;
			change(1, (b[i] > n) ? (b[i] - n) : b[i]);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：Sampson_YW (赞：2)

分组方案一共只有 $2n-1$ 种：单人 $n$ 种，相邻两个组一队 $n-1$ 种。

那么就可以枚举最小值，求出最小的最大值。可以用线段树维护。

具体地，设 $f(l,r,0/1,0/1)$ 表示区间 $[l,r]$ 的答案（$[l,r]$ 是线段树上的某个节点）。其中，第一个 $0/1$ 表示 $l$ 是不是和 $l-1$ 组队，第二个 $0/1$ 表示 $r$ 是不是和 $r+1$ 组队。转移为：

$$
f(l,r,x,y)=\min_{k\in\{0,1\}}\left\{\max\left(f(l,mid,x,k),f(mid+1,r,k,y)\right)\right\}
$$

只需要初始化线段树的叶子节点 $(i,i)$：$(0,0)$ 是单人，$(0,1)$ 是和 $i+1$ 组队，$(1,0)$ 是和 $i-1$ 组队，$(1,1)$ 不合法，设为 $+\infty$。

在枚举最小值的时候，将小于当前最小值的组队方案设为不合法即可，即 $+\infty$。最后求解出来的最小的最大值为 $f(1,n,0,0)$。

[code](https://www.luogu.com.cn/paste/998ck4mc)

---

## 作者：nullqtr_pwp (赞：1)

ddp 做法菜了。

原问题可以转化成，给定 $n-1$ 个二元组和 $n$ 个单元组，权值为每个组里所有数的和，可以将所有的 $2n-1$ 个组按照权值排序，那么原问题可以转化成一个双指针判定问题。也就是钦定组里面的最大值，然后维护另一个指针维护最小值，要求能恰好覆盖 $n$ 个数。直接暴力移动并判定是 $\mathcal O(n^2)$ 的。考虑优化。如果相邻两个点可以成为一队，就把他们连起来。这样序列就可以变成很多段。每一段里，如果段长是偶数；或者段长是奇数，并且段内存在某个 $x$，其位置与这一段的左端点同奇偶，而且它可以自成一队。那么这一段就可以分队，否则就不能分队。这样的话，可以用一个 ```set``` 维护所有段的端点 （这样就可以 每次修改相邻两点能否能分队的时候利用 ```lower_bound``` 找到涉及到的段），另外再用一个 ```set``` 维护所有位置为奇数的可以自成一队的点，还有一个维护偶数的。这样就可以快速判断上面那个第二条判断条件。时间复杂度 $\mathcal O(n\log n)$ 。

---

## 作者：immortal_immortals (赞：1)

## 思路
1. 将区间按权值从小到大排序。
1. 枚举，将该区间权值作为最小值，后在线段树上查询最大值。枚举后，则删掉此区间（去掉在线段树上的贡献）。
1. 对于每个区间，变量 $m$ 为不包含左右边界划分的最大权值，$lm$ 为不包含右边界元素划分的最大权值，$mr$ 为不包含左边界元素划分的最大权值，$lmr$ 为包含左右边界元素划分的最大权值，则可在 $O(1)$ 内合并两个区间的信息。合并时，考虑两区间交界处包含左区间右边界，和右区间左边界的区间贡献。
1. 每删掉一个区间，线段树上仅有包含该区间的区间受影响，所以更新的时间复杂度只要 $O(\log n)$。

总时间复杂度 $O(n \log n)$。
## 代码
```
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*w;
}
long long ans,a[10000005][5];
int t,n,n2;
struct aaa
{
	long long m,lm,mr,lmr;
}s[40000005];
struct aa
{
    int x,y;
    bool operator<(aa b)
	{
		return a[x][y]<a[b.x][b.y];
	}
}b[20000005];
void pd(int u,int l,int r)
{
    s[u].m=min(max(a[((l+r)>>1)][1],max(s[(u<<1)].m,s[(u<<1|1)].m)),max(s[(u<<1)].mr,s[(u<<1|1)].lm));
    s[u].lm=min(max(a[((l+r)>>1)][1],max(s[(u<<1)].lm,s[(u<<1|1)].m)),max(s[(u<<1)].lmr,s[(u<<1|1)].lm));
    s[u].mr=min(max(a[((l+r)>>1)][1],max(s[(u<<1)].m,s[(u<<1|1)].mr)),max(s[(u<<1)].mr,s[(u<<1|1)].lmr));
    s[u].lmr=min(max(a[((l+r)>>1)][1],max(s[(u<<1)].lm,s[(u<<1|1)].mr)),max(s[(u<<1)].lmr,s[(u<<1|1)].lmr));
}
void df(int u=1,int l=0,int r=n-1)
{
    if(l==r)
	{
		s[u].m=99999999;
		s[u].lm=s[u].mr=-99999999;
		s[u].lmr=a[l][0];
		return;
	}
    df((u<<1),l,((l+r)>>1));
	df((u<<1|1),((l+r)>>1)+1,r);
	pd(u,l,r);
}
void work(int p,int u=1,int l=0,int r=n-1)
{
    if(l==r)
	{
		s[u].m=99999999;
		s[u].lm=s[u].mr=-99999999;
		s[u].lmr=a[l][0];
		return;
	}
    if(p<=((l+r)>>1))
	{
		work(p,(u<<1),l,((l+r)>>1))	
	}
	else 
	{
		work(p,(u<<1|1),((l+r)>>1)+1,r);
	}
	pd(u,l,r);
}
int main()
{
	t=read();
    for(int ll=1;ll<=t;ll++)
	{
        n=read();
        for(int i=0;i<n;i++)
		{
			a[i][0]=read();
		}
        for(int i=0;i<n-1;i++)
		{
			a[i][1]=a[i][0]+a[i+1][0];
		}
        a[n-1][1]=99999999;
        df();
        n2=0;
        for(int i=0;i<n;i++)
		{
			b[n2++]={i,0};
			b[n2++]={i,1};
		}
        sort(b,b+n2);
        ans=99999999;
        for(int i=0;i<n2&&s[1].lmr!=9999999;i++)
		{
            ans=min(ans,s[1].lmr-a[b[i].x][b[i].y]);
            a[b[i].x][b[i].y]=99999999;
			work(b[i].x);
        }
        cout<<ans<<endl;
    }
    return 0;
}
```


---

## 作者：Gaode_Sean (赞：0)

似乎是一道挺套路的题？

先充分挖掘题目的性质，不难发现：最小团队力量值值只有 $\mathcal{O}(n)$ 种取值。

于是我们可以考虑枚举最小团队力量值，并用 dp 求出最小的最大团队力量值。

很容易设计出一个 dp：$f_i$ 表示考虑到第 $i$ 个士兵，此时最大团队力量值的最小值。

有转移：$\max(f_{i-2}$，$a_{i-1}+a_i) \to f_i$（$mn \leq a_{i-1}+a_i$），$\max(f_{i-1}$，$a_i) \to f_i$（$mn \leq a_i$）。

可以使用矩阵乘法进行转移，并用线段树维护转移矩阵。

为了每次只需要在线段树上修改一个矩阵，我们可以将最小团队力量值从小到大排序。

放一份代码，以免有人说我口胡。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+5;
int T,n;
ll ans;
ll a[N];
struct node
{
	ll val; int pos,id;
}b[N*2];
struct matrix
{
	ll g[2][2];
	matrix()
	{
		for(int i=0;i<2;i++)
		{
			for(int j=0;j<2;j++) g[i][j]=1e18;
		}
	}
	matrix operator*(matrix b)
	{
		matrix c;
		for(int i=0;i<2;i++)
		{
			for(int j=0;j<2;j++)
			{
				for(int k=0;k<2;k++) c.g[i][j]=min(c.g[i][j],max(g[i][k],b.g[k][j]));
			}
		}
		return c;
	}
}t[N<<2],mt,res;
bool cmp(node a,node b){return a.val<b.val;}
void pushup(int p){t[p]=t[p<<1]*t[p<<1|1];}
void build(int p,int l,int r)
{
	if(l==r)
	{
		t[p].g[0][0]=a[l],t[p].g[0][1]=-1e18,t[p].g[1][1]=1e18;
		if(l==1) t[p].g[1][0]=1e18;
		else t[p].g[1][0]=a[l]+a[l-1];
		return;
	}
	int mid=(l+r)>>1; build(p<<1,l,mid),build(p<<1|1,mid+1,r),pushup(p);
}
void update(int p,int l,int r,int pos,int id)
{
	if(l==r) return (void)(t[p].g[id][0]=1e18);
	int mid=(l+r)>>1;
	if(pos<=mid) update(p<<1,l,mid,pos,id);
	else update(p<<1|1,mid+1,r,pos,id);
	pushup(p);
}
int main()
{
	scanf("%d",&T),mt.g[0][0]=-1e18;
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%lld",&a[i]),b[i].val=a[i],b[i].pos=i,b[i].id=0;
		for(int i=1;i<n;i++) b[n+i].val=a[i]+a[i+1],b[n+i].pos=i+1,b[n+i].id=1;
		build(1,1,n),sort(b+1,b+2*n,cmp),ans=1e18;
		for(int i=1;i<2*n;i++)
		{
			res=mt*t[1],ans=min(ans,max(0ll,res.g[0][0]-b[i].val));
			update(1,1,n,b[i].pos,b[i].id);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

