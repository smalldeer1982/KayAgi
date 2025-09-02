# [USACO18DEC] Sort It Out P

## 题目描述

FJ 有 $N$（$1 \leq N \leq 10^5$）头奶牛（分别用 $1 \ldots N$ 编号）排成一行。FJ 喜欢他的奶牛以升序排列，不幸的是现在她们的顺序被打乱了。在过去，FJ 曾经使用一些诸如“冒泡排序”的开创性算法来使他的奶牛排好序，但今天他想偷个懒。取而代之，他会每次对着一头奶牛叫道“按顺序排好”。当一头奶牛被叫到的时候，她会确保自己在队伍中的顺序是正确的（从她的角度看来）。当有一头紧接在她右边的奶牛的编号比她小，她们就交换位置。然后，当有一头紧接在她左边的奶牛的编号比她大，她们就交换位置。这样这头奶牛就完成了“按顺序排好”，在这头奶牛看来左边的奶牛编号比她小，右边的奶牛编号比她大。

FJ 想要选出这些奶牛的一个子集，然后遍历这个子集，依次对着每一头奶牛发号施令（按编号递增的顺序），重复这样直到所有 $N$ 头奶牛排好顺序。例如，如果他选出了编号为 $\{2,4,5\}$ 的奶牛的子集，那么他会喊叫奶牛 $2$，然后是奶牛 $4$，然后是奶牛 $5$。如果 $N$ 头奶牛此时仍未排好顺序，他会再次对着这几头奶牛喊叫，如果有必要的话继续重复。

由于 FJ 不确定哪些奶牛比较专心，他想要使得这个子集最小。此外，他认为 $K$ 是个幸运数字。请帮他求出满足重复喊叫可以使得所有奶牛排好顺序的最小子集之中字典序第 $K$ 小的子集。

我们称 $\{1, \ldots ,N\}$ 的一个子集 $S$ 在字典序下小于子集 $T$，当 $S$ 的所有元素组成的序列（按升序排列）在字典序下小于 $T$ 的所有元素组成的序列（按升序排列）。例如，$\{1,3,6\}$ 在字典序下小于 $\{1,4,5\}$。

## 说明/提示

开始的时候序列为 $ \mathtt{\:4\:\; 2\:\; 1\:\; 3\:} $ 。在FJ喊叫编号为 $ 1 $ 的奶牛之后，序列变为 $ \mathtt{\:1\:\; 4\:\; 2\:\; 3\:} $ 。在FJ喊叫编号为 $ 4 $ 的奶牛之后，序列变为 $ \mathtt{\:1\:\; 2\:\; 3\:\; 4\:} $ 。在这个时候，序列已经完成了排序。

## 子任务

对于占总分 $ 3/16 $ 的测试数据， $ N \leq 6 $ ，并且 $ K=1 $ 。

对于另外的占总分 $ 5/16 $ 的测试数据， $ K=1 $ 。

对于另外的占总分 $ 8/16 $ 的测试数据，没有其他限制。

## 样例 #1

### 输入

```
4 1
4 2 1 3
```

### 输出

```
2
1
4
```

# 题解

## 作者：Mirach (赞：8)

[屠龙宝刀,点击就送,一刀999](https://www.cnblogs.com/penth/p/10252032.html)

Problem
-------

题意概要：给定一个长为$n$的排列，可以选择一个集合$S$使这个集合内部元素排到自己在整个序列中应该在的位置（即对于集合$S$内的每一个元素$i$，使其排到第$i$号位置，使得整个排列在排序后为上升序列。求满足这样条件的，且集合大小最小的集合中字典序第$k$小的集合（可能总结不到位，看原题面吧）

$n\leq 10^5$

Solution
-------

不难发现出题人费尽心思写的题面就是在强烈暗示选取一个集合等价于将这个集合内所有元素排到自己该处于的位置（即元素$i$应该在位置$i$）

进一步发现集合内的元素很自觉的到了正确的位置，而集合外的元素不会更改相对位置，为了使最终整个排列单调递增，即要求集合外的元素必须满足在一开始就是单调递增的

求字典序第$k$小的满足题意的集合，取反一下，就是求序列中字典序第$k$大的最长上升子序列

（至此题目模型转化完成）

------

现在目标为求字典序第$k$大的最长上升子序列

在继续之前建议先将[最长递增子序列的数量](http://www.51nod.com/Challenge/Problem.html#!#problemId=1376)解决：

设置$f_i$表示以权值为$i$结尾的$LIS$的长度和数量，则权值$x$从$f_1...f_{x-1}$间转移，用树状数组维护前缀最大值和数量即可$O(n\log n)$解决

------

利用上面这题的思想，已经可以求得以每个元素开头的$LIS$长度和数量

这题和上面这题虽有不同，但本质类似，想想一般线段树求第 $k$ 大的过程，正是依次确定每一层的节点，而为了确定每一层的节点，就需要用到所有节点子树和

同理，假设当前要求的序列的$LIS$长度为 $t$，则求第$k$大$LIS$的一个思想就是先确定第$1$个数，再在确定第$1$个数的基础上确定下一个数……以此类推可以最终确定$LIS$的每一位

细化一下，就是将所有可能作为$LIS$的第$i$位的数 放进第$i$个vector里，将每个vector内部进行元素排序，在确定每一位时从大到小确定，若当前值后面牵扯的$LIS$数量小于$k$，则将$k$减去这个数量然后检查下一个值，否则将这个值确定下来并开始确认下一位

（值得注意的一点，若求$LIS$第$i$层选定了位置$R$的元素，则接下来都不能选择$R$左边的元素）

Code
-------

关于代码中的一些疑问：

- 我没有用vector，而是使用链式前向星替代
- 由于每个vector里的元素一定是按照位置递增而权值递减的，所以并不需要排序
- 很多人用线段树，而这题只需要树状数组即可
- 在求完以每个点开始的$LIS$后树状数组就没用了，可以节约大量时间

```cpp
#include <bits/stdc++.h>
typedef long long ll;

inline void read(int&x){
	char c11=getchar();x=0;while(!isdigit(c11))c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();
}

const int N=101000;
struct Edge{int v,nxt;}e[N];
int a[N],chs[N],head[N];
int n,_;ll k;

const ll lim=1e18;

struct node{
	int v;ll c;
	inline node(){}
	friend inline void operator + (node&A,const node B){
		if(A.v<B.v)A.v=B.v,A.c=B.c;
		else if(A.v==B.v)A.c=std::min(lim,A.c+B.c);
	}
}d[N],g[N],cl;

#define lb(x) (x&(-x))

inline node qy(int x){node p=cl;for(x;x<=n+1;x+=lb(x))p+d[x];return p;}
inline void add(int x,node y){for(;x;x-=lb(x))d[x]+y;}
inline void ae(int u,int v){e[++_].v=v,e[_].nxt=head[u],head[u]=_;}

int main(){
	scanf("%d%lld",&n,&k);
	for(int i=1;i<=n;++i)read(a[i]);
	cl.c=1,add(n+1,cl),cl.c=0;
	for(int i=n;i;--i){
		g[i]=qy(a[i]);
		++g[i].v;
		add(a[i],g[i]);
	}
	for(int i=n;i;--i)ae(g[i].v,i);
	for(int stp=qy(1).v,R=0;stp;--stp)
	for(int i=head[stp],v;i;i=e[i].nxt){
		v=e[i].v;
		if(g[v].c<k)k-=g[v].c;
		else {
			chs[a[v]]=true;
			while(R<v)g[R++]=cl;
			break;
		}
	}
	printf("%d\n",n-qy(1).v);
	for(int i=1;i<=n;++i)
		if(!chs[i])printf("%d\n",i);
	return 0;
}
```

---

## 作者：xianglingao (赞：8)

### 题目大意

有$n$个人排队，第$i$个人有编号$a_i$。$a_1, a_2, \dots, a_n$为$1$到$n$的一个排列。定义$\text{sort}(x)$表示编号为$x$的人出列并插到队伍的第$x$个位置。集合$S \in [1, n]$满足题意当且仅当依次调用$\text{sort}(i) (i \in S)$后队伍编号从小到大依次排列。问$\vert S \vert$的最小值和字典序第$k$小的集合。

### 思路分析

本题的模型看似难以处理，需要对其进行一些初步的转化。

我们发现调用$\text{sort}(x)$并不影响除了$x$以外的人的相对顺序。对于一个集合$S$，对它进行操作后不在$S$中的人的相对顺序也不会受到影响。那么不在$S$中的人必须构成一个升序的序列。那么$\vert S \vert$的最小值就是$\text{LIS}$的长度。

现在问题就转化成了：求序列$\text{LIS}$的长度和字典序第$k$大的$\text{LIS}$。（想想为什么？）

我们先构造一个新的序列$b$满足$b_{a_i} = i$。例如对于样例$a = 4, 2, 1, 3$，$b = 3, 2, 4, 1$。原问题等价于求出$b$下标序列字典序第$k$大的$\text{LIS}$。（想想为什么？）

考虑预处理出位置$i$开头的$\text{LIS}$长度以及$\text{LIS}$个数。考虑从后往前倒推。对于每个$i$维护开头位置在$i$之后且开头数字为$x$的$\text{LIS}$长度及$\text{LIS}$个数。位置$i$开头的信息就是以$[b_i + 1, n]$开头的$\text{LIS}$信息合并起来的结果。因为是一个后缀，所以可以用树状数组来维护。

然后，我们把所有以它开头$\text{LIS}$长度为$k$的位置$i$存进一个$\text{vector}$中。

最后，使用试填法的思想求解。每次，我们选择一个下标最大的位置使得这个位置合法。具体来说，从大到小枚举每一个$\text{vector}$，对于每个$\text{vector}$从大到小不断的枚举下标直到可用的$\text{LIS}$总数大于等于$k$。我们就可以选取当前枚举到的数来充当$\text{LIS}$的这一位。当然，每次填的数必须递增，可以通过跳过比上一位小的数来做到这点。试填完毕后按顺序输出不在$\text{LIS}$中数的下标即可。总时间复杂度$O(n \log n)$。

### 代码实现

为了避免$\text{LIS}$数量过大，每次我们要把它和极大值取$\min$。

```cpp
#include <cstdio>
#include <vector>
using namespace std;

typedef long long ll;
const int maxn = 1e5;
const ll inf = 1e18;
bool use[maxn + 3];
int n, m, a[maxn + 3], b[maxn + 3];
ll k, c[maxn + 3];

struct node {
	int mx;
	ll cnt;
	inline friend void operator += (node &a, const node &b) {
		if (a.mx < b.mx) a.mx = b.mx, a.cnt = b.cnt;
		else if (a.mx == b.mx) a.cnt = min(inf, a.cnt + b.cnt);
	}
} bit[maxn + 3];

vector<int> V[maxn + 3];

void add(int x, node y) {
	for (int i = x; i; i ^= i & -i) {
		bit[i] += y;
	}
}

node query(int x) {
	node res = {0, 1ll};
	for (int i = x; i <= n; i += i & -i) {
		res += bit[i];
	}
	return res;
}

int main() {
	#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
	scanf("%d %lld", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		b[a[i]] = i;
	}
	for (int i = n; i; i--) {
		node res = query(b[i] + 1);
		res.mx++;
		V[res.mx].push_back(i);
		c[i] = res.cnt;
		add(b[i], res);
	}
	m = query(1).mx;
	int cur = -1;
	for (int i = m; i; i--) {
		for (int j: V[i]) {
			if (b[j] < cur) continue;
			if (k <= c[j]) {
				use[j] = true;
				cur = b[j];
				break;
			} else {
				k -= c[j];
			}
		}
	}
	printf("%d\n", n - m);
	for (int i = 1; i <= n; i++) {
		if (!use[i]) printf("%d\n", i);
	}
	return 0;
}
```

---

## 作者：wheneveright (赞：5)

[原题链接](https://www.luogu.com.cn/problem/P5156)

## 分析

很容易想到对于一个可行集合 $A$，必然有不在 $A$ 中的所有数在原序列中单调增，故原题转化为求第 $K$ 大的最长上升子序列，最后输出补集。

用树状数组很容易求出每个点为起点的最长上升子序列长度，然后再求每个点为起点的最长上升子序列个数，这是重点。

我们用 $a_i$ 表示原序列、$LIS_i$ 表示第 $i$ 位为起点的最长上升子序列长度、$f_i$ 表示第 $i$ 位为起点的最长上升子序列个数，有转移方程：$f_i = \sum_{j = i + 1}^n [LIS_j + 1 = LIS_i\ \text{and}\ a_j > a_i] f_j$，暴力算是 $O(n^2)$ 的，需要更优秀的解法。

考虑用数据结构优化，我们可以用 $n$ 个树状数组来维护对于每一个相同 $LIS$ 的点集构成的 $f$ 的子序列的后缀和，然后再对每一个 $LIS$ 相同的点集关于 $a_i$ 进行降序排序，这样可以在枚举 $a_i$ 的同时用 $\log n$ 的复杂度计算出 $\sum_{j = i + 1}^n [LIS_j + 1 = LIS_i] f_j$ (枚举 $a_i$ 部分详见后文)。

这样时间是过得去的，但是空间是 $O(n^2)$ 的，显然会炸，所以考虑用更强的数据结构。考虑到用树状数组优化时每个点集是离散的，总的点数为 $n$，所以可以用动态开点线段树来优化掉这一部分的空间，然后就能做到空间 $O(n\log n)$ 时间 $O(n \log n)$ 了。

再回头来看枚举的部分，从大到小枚举 $LIS$ 点集，然后将这个点集内的点关于 $a_i$ 的大小降序排序，因为是降序排序，所以之前上一个取到的点一定是小于当前枚举的点的。然后注意在取点的时候如果在原序列上现取的点在上一个点之前是一定不可能的，拿个变量标记当前位置即可，接下来拼接就好了。注意最后输出的是升序的反集。

要注意的是 $f_i$ 可能会爆出 `long long`，所以当 $f_i$ 过大的时候让它等于 $k$ 的上限即可。

~~写完题解看了下别人的，我这个就算是比较蠢的解法了，码量上就输给别人了。~~

## 代码

```cpp
# include <bits/stdc++.h>
using namespace std;

const int maxn = 100005;
const long long INF = 1e18;

struct reader {
	template <typename Type>
	reader & operator >> (Type & ret) {
		int f = 1; ret = 0; char ch = getchar ();
		for (;!isdigit (ch); ch = getchar ()) if (ch == '-') f = -f;
		for (; isdigit (ch); ch = getchar ()) ret = (ret * 10) + ch - '0';
		ret *= f; return * this;
	}
} fin;

int n, m;
long long k;
int a[maxn], b[maxn];
int lis[maxn];

int T[maxn];
int get (int id) {
	int ret = 0;
	for (; id >= 1; id -= id & -id) ret = max (ret, T[id]);
	return ret;
}
void put (int id, int num) {
	for (; id <= n; id += id & -id) T[id] = max (T[id], num);
	return ;
}

// Segment Tree

struct Segment {
	long long sum;
	int l, r, ls, rs;
} p[maxn << 6];
int rot[maxn], now;

int ispos (int & pos, int ll, int rr) {
	if (pos) return pos;
	p[pos = ++now] = { 0, ll, rr, 0, 0 };
	return pos;
}

void update (int id, int pos, long long num) {
	if (p[id].l == pos && pos == p[id].r) return p[id].sum = num, void () ;
	int mid = (p[id].l + p[id].r) >> 1;
	if (pos <= mid) update (ispos (p[id].ls, p[id].l, mid), pos, num);
	else update (ispos (p[id].rs, mid + 1, p[id].r), pos, num);
	p[id].sum = min (INF, p[p[id].ls].sum + p[p[id].rs].sum);
	return ;
}

long long query (int id, int L, int R) {
	if (!id) return 0;
	if (L <= p[id].l && p[id].r <= R) return p[id].sum;
	int mid = (p[id].l + p[id].r) >> 1; long long ret = 0;
	if (L <= mid) ret += query (p[id].ls, L, R);
	if (mid < R) ret += query (p[id].rs, L, R);
	return min (ret, INF);
}

// Segment Tree

long long f[maxn];
vector < int > vec[maxn], res;
bool vis[maxn];

int main () {
	freopen ("itout.in", "r", stdin);
	freopen ("itout.out", "w", stdout);
	fin >> n >> k; now = n;
	for (int i = 1; i <= n; i++) fin >> a[i], rot[i] = i, p[i].l = 1, p[i].r = n;
	for (int i = n; i >= 1; i--) { // 计算 lis 和 f 数组
		put (n - a[i] + 1, lis[i] = get (n - a[i] + 1) + 1); m = max (m, lis[i]);
		update (rot[lis[i]], a[i], f[a[i]] = (lis[i] == 1 ? 1 : query (rot[lis[i] - 1], a[i] + 1, n)));
		vec[lis[i]].push_back (a[i]); b[a[i]] = i; // 这里存到点集中时存的就是 a[i]，然后用一个 b[i] 数组来回指 a[i]
	}
	for (int i = m, pos = 0; i >= 1; i--) { // 从大到小枚举 lis 点集
		sort (vec[i].begin (), vec[i].end ());
		reverse (vec[i].begin (), vec[i].end ());
		for (int j : vec[i]) {
			if (b[j] < pos) continue ; // 跳过拼接不上的点
			if (k > f[j]) k -= f[j];
			else { vis[j] = true; pos = b[j]; break ; }
		}
	}
	printf ("%d\n", n - m); // 最后是取反集输出
	for (int i = 1; i <= n; i++) if (!vis[i]) res.push_back (i);
	sort (res.begin (), res.end ());
	for (int i : res) printf ("%d\n", i);
	return 0;
}
```

---

## 作者：一只绝帆 (赞：2)

> 给定一个排列，你需要选出一个权值集合把它拿走使得剩余序列有序。
> 
> 你想让选出的集合大小最小，并在此基础上选出字典序第 $k$ 小的集合。
> 
> $n\le 10^5,k\le 10^{18}$。

首先说一下原题意如何转化成这个题意的。

他的操作说的很玄乎，但我们能明确两点：

- 若拿走这个集合后原序列无序，则最终一定无序，所以拿走之后原序列一定有序。

- 若拿走这个集合后原序列有序，则按照他的排序方式，最终一定有序。

如果觉得这两点不清晰的可以手模一下，还是很容易感性理解的。

这个集合的性质不大好，但其补集性质很好，是一个上升子序列。

集合大小最小就是最长上升子序列，集合字典序第 $k$ 小就是字典序第 $k$ 大的最长上升子序列。

那我们就来找这个东西。

考虑从前到后依次钦定最长上升子序列的每一位。

首先用树状数组求出每位开头的最长上升子序列长度及个数，树状数组每个节点需要记录子序列长度和个数，合并是朴素的。

然后我们从高到低枚举子序列长度，依次确定每位，具体的方式是把每个开头都挂到“对应的最长上升子序列的长度”上。

每个长度按照第一位权值降序枚举，找到 $k$ 了就确定下来。

然后每确定一位就把不可能作为后继的节点全部置成 $0$。

由于是从前往后确定，我们可以用一个指针来指向置成 $0$ 的最后一个位置，然后动指针。

这样看上去会有一些纰漏，比如说：枚举长度并不一定能保证下一位一定比这位大？

但由于你降序枚举长度，而题目又保证了存在这样的序列，所以下一位从高到低确定一定会找到合法解。

在实际的写法中，有一些需要注意的点：

- 发现如果按照确定每位“最长上升子序列长度及个数”的顺序来挂在长度上，下标一定是递减的，权值一定是递增的，所以不用排序，倒序枚举即可。

- 倒序枚举天然适合链式前向星，所以直接用链式前向星。

- 信息不可差分，要写后缀树状数组。

- 子序列个数理论上有 $2^n$ 个，所以我们不能直接加起来，要对一个很大的数取 $\min$。

Code（截至 $2023.10.25$ 最优解）：
```cpp
#include<bits/stdc++.h>
#define G(i,x) for(int i(start[x]);i;i=Next[i])
#define F(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
#define UF(i,a,b) for(int i=a,i##end=b;i>=i##end;i--)
using namespace std;typedef long long ll;
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char *p1,*p2,buf[1<<21];
ll read() {
	ll s=0,w=0;char ch=gc();
	while(ch<'0'||ch>'9') w|=(ch=='-'),ch=gc();
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48),ch=gc();
	return w?-s:s;
} const int N=1e5+5;const ll inf=1e18;
ll k;int n,p[N],vis[N],ans,start[N],Next[N],cnt,v[N];
struct S {
	ll mx,c;
	S(ll mx=0,ll c=0):mx(mx),c(c) {}
	S operator+(S b) {
		return S(max(mx,b.mx),min(inf,c*(mx==max(mx,b.mx))+b.c*(b.mx==max(mx,b.mx))));
	}
	S operator+(ll u) {return S(mx+u,c);}
} c[N],g[N];
void mo(int x,S v) {
	for(;x;x&=x-1) c[x]=c[x]+v;
}
S q(int x) {
	S res;for(;x<=n+1;x+=x&-x) res=res+c[x];
	return res;
}
void add(int x,int y) {
	v[++cnt]=y;Next[cnt]=start[x];start[x]=cnt;
}
int main() {
	n=read();k=read();mo(n+1,S(0,1));
	F(i,1,n) p[i]=read();
	UF(i,n,1) {
		mo(p[i],g[i]=q(p[i])+1);
		add(g[i].mx,i);
	}
	int now=0;UF(x,q(1).mx,1) G(i,x) {
		if(k>g[v[i]].c) k-=g[v[i]].c;
		else {
			while(now<v[i]) g[++now]=S();
			vis[p[v[i]]]=1;
			break;
		}
	}
	F(i,1,n) ans+=!vis[i];
	printf("%d\n",ans);
	F(i,1,n) if(!vis[i]) printf("%d\n",i);
	return 0;
}
```

---

## 作者：Graphcity (赞：1)

**观察一：** 除开集合 $S$ 中的数，其它数字的相对位置不变。

**观察二：** 根据观察一，如果序列中除 $S$ 以外的数均有序，那么局面合法。

考虑第一轮呼叫 $S$ 的最小值一定会放在开头，第二轮呼叫 $S$ 的次小值一定恰好在第二个位置，依次类推，所以只要 $S$ 以外的部分有序那一定合法。

**结论：** 最小的 $|S|$ 在序列的补集一定是最长上升子序列。

使用 [P3308 SDOI2014 LIS](https://www.luogu.com.cn/problem/P3308) 的套路，将整个序列按照以每个点为结尾的 LIS 长度来分层。我们需要每一层选择一个点，使得形成一个 LIS 的同时补集字典序最小。

**观察三：** 如果两个递增序列 $A,B$ 满足 $A<B$，那么这两个序列对于 $\{1,2,\cdots\}$ 的补集形成的序列 $A',B'$ 一定满足 $A'>B'$。

如果有 $A<B$，那么一定有一段前缀满足 $A_i=B_i$，且后一个位置有 $A_{last}<B_{last}$。放到补集上考虑，$\le A_{last}$ 的部分一定是相同的，而 $A'$ 的后一个数 $>A_{last}$，$B'$ 的后一个数 $=B_{last}$，所以有 $A'>B'$。

对每一层的结点按照 $a$ 从大往小排序后，求出每个点开始能够扩展出的 LIS 长度 $h_i$。根据观察三，我们需要找到第 $K$ 大的子序列。那我们逐层扫描，如果 $h_i\ge K$ 就选择它，否则 $K\gets K-h_i$ 就行了。

以上的所有求值操作都可以使用树状数组完成。总时间复杂度 $O(n\log n)$。

---

## 作者：_Cheems (赞：0)

题意：给一个排列 $a_1\dots a_n$，定义其中一个子集是合法的，当且仅当可以对子集内元素进行若干次操作，使得排列有序。对 $a_i=x$ 操作，先将其拎出来然后从左往右比较直到遇见比它大元素，然后插入。求字典序第 $k$ 小的大小最小合法子集。$n\le 10^5,k\le 10^{18}$。

合法的必要条件是剩下元素有序（因为无法改变它们内部顺序），容易发现这是充要的。貌似不好比较因为还要排序，注意到剩下元素的有序性，考虑通过它来比较。发现两个子集 $A<B$ 当且仅当 $\complement A>\complement B$。

求第 $k$ 大的最长上升子序列是容易的，预处理一下每个起点的最长上升子序列长度和方案。$O(n\log n)$。
#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int N = 1e5 + 5;
int n, k, a[N], rk[N], lis;  
struct node{int mx, cnt;} f[N];
bool vis[N];
vector<int> vc[N];

inline void ADD(node &A, node B){
	if(A.mx < B.mx) A = {B.mx, 0};
	if(A.mx == B.mx) A.cnt = min(A.cnt + B.cnt, k);
}
namespace BIT{
	node t[N];
	inline void upd(int a, node k) {for(; a < N; a += a & -a) ADD(t[a], k);}
	inline node qry(int a) {node res = {0, 0}; for(; a > 0; a -= a & -a) ADD(res, t[a]); return res;}
}using namespace BIT;
signed main(){
	cin >> n >> k;
	for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]), rk[a[i]] = i;	
	for(int i = n; i; --i){
		f[i] = qry(n - a[i] + 1);
		if(f[i].cnt == 0) f[i] = {1, 1}; 
		else ++f[i].mx;
		upd(n - a[i] + 1, f[i]);
		lis = max(lis, f[i].mx);
		vc[f[i].mx].push_back(a[i]);
	}
	for(int i = 1; i <= n; ++i) sort(vc[i].begin(), vc[i].end(), [](int a, int b){return a > b;});
	printf("%lld\n", n - lis);
	for(int len = lis, lst = 0; len; --len){
		for(auto i : vc[len]){
			if(lst > rk[i] || a[lst] > i) continue;
			if(f[rk[i]].cnt >= k){
				lst = rk[i], vis[i] = true;
				break;
			}
			else k -= f[rk[i]].cnt;
		}
	}
	for(int i = 1; i <= n; ++i)	if(!vis[i]) printf("%lld\n", i);
	return 0;
}
```

---

## 作者：legenc6y (赞：0)

没看懂其他几篇题解在写什么（处理方法），所以写点自己的理解。前面的充要条件都是一样的。

求第 $K$ 大，并且 $K$ 相当大，猜测一下这个操作是有很好的计数性质的。看一看怎么判定一个集合是否合法。

经过手摸，能感受出来两个性质：（设 $S$ 是钦定的子序列，$T$ 是没有钦定的子序列）

- 经过操作后 $T$ 内的元素相对位置不变。
  
- 经过操作后 $S$ 内部不存在逆序对。
  

第一条性质容易理解。从而引申出来一个性质：$T$ 必然是一个递增子序列。

进一步推导发现，不存在 $x\in S, y\in T,x<y,a_x>a_y$，也就是两子序列间没有逆序对。证明并不难，由于 $T$ 中元素递增，所以最容易和 $x$ 左右最近的 $T$ 中元素。而根据题中操作这种情况不可能出现。

可以注意到，对于 $S$ 中相邻两元素 $x,y$，若初始 $a_x>a_y$ 则经过操作可以消除这个逆序对。

上面说了很多，总结出来就是，$S$ 合法的充要条件是 $T$ 是递增子序列。所以第一问就是 $n - \mathrm{len(LIS)}$。

考虑第二问。$S$ 很牛魔，比较好利用上的是 $T$。根据题中的“字典序”比较方法，我们发现第 $K$ 小的 $S$ 对应第 $K$ 大的 $T$。这里的证明可以考虑画两条数轴，分别从上面扣几个数就能感受出来。

终于来到了处理。对于限制长度为 LIS 的问题，我们把原序列中元素按 $f$ 分层（$f_i$ 表示 $a_i$ 结尾的 LIS 长度）后，在层与层之间转移。

如果我们知道 $i$ 开头的 LIS 数量 $g_i$ 就可以得出答案。按层枚举，层内 $a$ 降序排序，若 $g_i<K$ 则 $K\gets K-g_i$，否则记录 $i$ 的位置然后继续往高层扫。

如何处理 $g_i$？限制是 $f_j=f_i+1,j>i,a_j>a_i$。因为我们层内按 $a$ 降序排序，所以分别用分层转移，树状数组，双指针维护即可。时间复杂度 $\mathcal O(n\log n)$。

感觉很鬼畜啊，太菜了理解不了正常的写法呃。注意 $g$ 可能会爆 `long long` 所以运算过程中不断和一个大整数 check min。

```cpp
#include <bits/stdc++.h>
#define pb emplace_back
#define fir first
#define sec second

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int maxn = 1e5 + 5, MAXN = 3e6;
constexpr i64 inf = 2e18;
int n, a[maxn], g[maxn], cnt, h[maxn];
std::vector<int> G[maxn];
i64 f[maxn], k;
bool vis[maxn];

void chkmax(i64& x, i64 y) { if (y > x) x = y; return ; }
void chkmin(i64& x, i64 y) { if (y < x) x = y; return ; }

struct Fenwick {
	i64 c[maxn];
	int stk[MAXN], tp;
	Fenwick() { memset(c, 0, sizeof(c)); }
	void clr() { for (int i = 1; i <= tp; ++i) for (int x = stk[i]; x; x -= x & -x) c[x] = 0; return void(tp = 0); }
	void add(int x, i64 y) {
		for (stk[++tp] = x; x; x -= x & -x)
			chkmin(c[x] += y, inf);
		return ;
	}
	i64 query(int x) {
		i64 ans = 0;
		for (; x <= n; x += x & -x)
			chkmin(ans += c[x], inf);
		return ans;
	}
} tr;

int main() {
	scanf("%d %lld", &n, &k); g[cnt = 0] = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		if (a[i] > g[cnt]) {
			g[++cnt] = a[i];
			G[h[i] = cnt].pb(i);
		} else {
			int x = std::upper_bound(g + 1, g + 1 + cnt, a[i]) - g;
			g[x] = a[i]; G[h[i] = x].pb(i);
		}
	}
	printf("%d\n", n - cnt);
	for (int i = cnt; i >= 1; --i) {
		std::sort(G[i].begin(), G[i].end(), [&](const int& lhs, const int& rhs) {
			return a[lhs] > a[rhs];
		});
		if (i == cnt) {
			for (auto& v : G[i])
				f[v] = 1;
			continue ;
		}
		tr.clr();
		int y = 0;
		for (int x = 0; x < G[i].size(); ++x) {
			for (; y < G[i + 1].size() && a[G[i][x]] < a[G[i + 1][y]]; ++y) tr.add(G[i + 1][y], f[G[i + 1][y]]);
			f[G[i][x]] = tr.query(G[i][x]);
		}
	}
	int now = 0;
	for (int i = 1; i <= cnt; ++i) {
		for (auto& v : G[i]) {
			if (v < now) continue ;
			if (k > f[v]) { 
				k -= f[v];
			} else {
				vis[a[v]] = true;
				now = v; break ;
			}
		}
	}
	for (int i = 1; i <= n; ++i)
		if (!vis[i]) printf("%d\n", i);
	return 0;
}
```

---

## 作者：wenjing233 (赞：0)

#### LIS数量统计
设f[i]代表以第i个数字为开头的LIS长度,g[i]代表方案数  
转移时从后往前 f[i]=f[i+1···n]中的最大值 g[i]为最大长度的方案数的和  
用树状数组维护即可，若需要维护以第i个数字为结尾的最长的LIS长度，正的做即可 
（代码和下面题解和在一起了，感觉还算简单）
#### P5156 [USACO18DEC]Sort It Out 题解
题目中的排序方式类似于快速排序，不会改变其他数的相对位置  
类似于之前模拟赛中的卡片重新插入排序类似的是，求出其最长子序列的长度，然后由n减去它即是集合大小  
但本题还需要我们求出字典序第K小的集合，即求字典序第K大的LIS，但这样会给下面的操作带来麻烦（不转也可以，但我看不懂不转的代码）
将a(i)=x转化为b(x)=i 即由下标映射权值转化为权值映射下标，则字典序第K大转换为下标字典序第K大方便接下来的操作（保证vector内有序（虽然听说不转换vector内依旧有序但我不会证明））  
然后我们用vector（或链表）来维护长度为 k 的LIS的开头有哪些，然后从长度k到1进行枚举  
若以当前枚举到的数字为开头的LIS方案数比k小则这个数字不能选（因为选了之后就算是最大的字典序也无法达到k）若比k大则往下选。  
注意：当前枚举到的数不能比之前枚举到的数还要小，需要特判  
这题由于权值和下标老是转来转去，故将详细的解释放在代码的注释里（其实是我自己理解能力低下）
# 注意：代码中的下标和权值为了方便理解，标的是依据b的下标和权值。实际上b的下标是a的权值，b的权值是a的下标
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long inf=1e18;
long long read()
{
    long long tot=0,fs=1;
    char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
    if(ch=='-') fs=-1,ch=getchar();
    while(ch>='0'&&ch<='9') tot=tot*10+ch-'0',ch=getchar();
    return tot*fs; 	
}
long long n,m;
long long a[100009],b[100009];
long long k,c[100009];//排名和下标为x的数为开头的LIS方案数
struct gzw
{
    long long mx,cnt;//LIS长度和方案数
    inline friend void operator += (gzw &a, const gzw &b)//状态转移
	{
        if (a.mx < b.mx) a.mx = b.mx, a.cnt = b.cnt;
        else if (a.mx == b.mx) a.cnt = min(inf, a.cnt + b.cnt);
    }
}bit[100009];
vector<long long> vec[100009];//LIS长度为x的所有开头的下标
bool use[100009];//x这个下标是否在LIS中
void add(long long x,gzw y)//更新
{
    for(long long i=x;i;i-=(i&-i))
    {
		bit[i]+=y;
    }
}
gzw query(long long x)//由于是从后往前做的，应当找权值比当前大的转移
{
    gzw re={0,1ll};
    for(long long i=x;i<=n;i+=(i&-i))
    {
		re+=bit[i];
    }
    return re;
}
int main()
{
    n=read(),k=read();
    //cin>>n>>k;
    for(long long i=1;i<=n;i++)
    {
        a[i]=read();
        //cin>>a[i];
        b[i]=a[i];
    }
    for(long long i=n;i;i--)
    {
		gzw ls=query(b[i]+1);
        ls.mx++;//更新后长度+1
        vec[ls.mx].push_back(i);//加入下标 因为i是从大到小枚举故必然有序
        c[i]=ls.cnt;
        add(b[i],ls);
    }
    m=query(1).mx;//查询最长子序列长度
    long long cur=-1;
    for(long long i=m;i;i--)
    {
        for(long long ii=0;ii<vec[i].size();ii++)
        {
            long long j=vec[i][ii]; //下标
            if(b[j]<cur) continue; //权值不能比之前的小
            if(k<=c[j])//往下走
            {
                use[b[j]]=1;
                cur=b[j];
                break;
            }
            k-=c[j];//再往后面找下标更小的	
        }
    }
    printf("%lld\n",n-m);
    for(long long i=1;i<=n;i++)
    {
        if(!use[i]) printf("%lld\n",i);	//输出答案
    }
    return 0;
}
```
花了一下午终于弄懂了QAQ，果然题解写的越复杂的人越菜QAQ

---

