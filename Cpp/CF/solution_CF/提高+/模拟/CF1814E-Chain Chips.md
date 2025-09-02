# Chain Chips

## 题目描述

You are given an undirected graph consisting of $ n $ vertices and $ n-1 $ edges. The $ i $ -th edge has weight $ a_i $ ; it connects the vertices $ i $ and $ i+1 $ .

Initially, each vertex contains a chip. Each chip has an integer written on it; the integer written on the chip in the $ i $ -th vertex is $ i $ .

In one operation, you can choose a chip (if there are multiple chips in a single vertex, you may choose any one of them) and move it along one of the edges of the graph. The cost of this operation is equal to the weight of the edge.

The cost of the graph is the minimum cost of a sequence of such operations that meets the following condition:

- after all operations are performed, each vertex contains exactly one chip, and the integer on each chip is not equal to the index of the vertex where that chip is located.

You are given $ q $ queries of the form:

- $ k $ $ x $ — change the weight of the $ k $ -th edge (the one which connects the vertices $ k $ and $ k+1 $ ) to $ x $ .

After each query, print the cost of the graph. Note that you don't actually move any chips; when you compute the cost, the chips are on their initial positions.

## 样例 #1

### 输入

```
10
12 6 12 15 20 8 17 12 15
8
4 10
7 3
6 14
9 9
2 10
3 5
4 11
7 11```

### 输出

```
126
108
120
108
112
98
98
114```

# 题解

## 作者：chenxumin1017 (赞：11)

# 性质
1. 每条边要么被经过两次，要么不被经过。
1. 相邻的两条边必须有一条被经过两次。
1. 在两个区间合并时，合并是否合法只取决于他们相邻的那两条边是否有一条边被经过了。

# 做法

有了这些性质，我们每个区间就只用统计四种情况。
1. 最左边的边不经过，最右边的边不经过。
1. 最左边的边经过，最右边的边不经过。
1. 最左边的边不经过，最右的边边经过。
1. 最左边的边经过，最右边的边经过。

接着就可以用线段树维护了！

# 复杂度

时间复杂度：$O(N\ \log\ N)$ 。

空间复杂度：$O(N)$ 。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5, INF = 1e18;
int n, tr[N * 4][2][2], a[N], q;
void j(int l, int r, int id){
  if(l == r){
    tr[id][1][1] = a[l];
    tr[id][0][1] = tr[id][1][0] = INF;
    return;
  }
  int mid = (l + r) >> 1;
  j(l, mid, id * 2);
  j(mid + 1, r, id * 2 + 1);
  tr[id][0][0] = tr[id][1][0] = tr[id][0][1] = tr[id][1][1] = INF;
  for(int i = 0; i < 2; i++){
    for(int j = 0; j < 2; j++){
      for(int k = 0; k < 2; k++){
        for(int e = 0; e < 2; e++){
          if(k || j)tr[id][i][e] = min(tr[id][i][e], tr[id * 2][i][j] + tr[id * 2 + 1][k][e]);
        }
      }
    }
  }
}
void g(int l, int r, int id, int px, int x){
  if(l == r){
    tr[id][1][1] = x;
    tr[id][0][1] = tr[id][1][0] = INF;
    return;
  }
  int mid = (l + r) >> 1;
  if(px <= mid)g(l, mid, id* 2, px, x);
  else g(mid + 1, r, id * 2 + 1, px, x);
  tr[id][0][0] = tr[id][1][0] = tr[id][0][1] = tr[id][1][1] = INF;
  for(int i = 0; i < 2; i++){
    for(int j = 0; j < 2; j++){
      for(int k = 0; k < 2; k++){
        for(int e = 0; e < 2; e++){
          if(k || j)tr[id][i][e] = min(tr[id][i][e], tr[id * 2][i][j] + tr[id * 2 + 1][k][e]);
        }
      }
    }
  }
}
signed main(){
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> n;
  for(int i = 1; i < n; i++){
    cin >> a[i];
  }
  j(1, n - 1, 1);
  cin >> q;
  for(int x, y; q; q--){
    cin >> x >> y;
    g(1, n - 1, 1, x, y);
    cout << tr[1][1][1] * 2 << '\n';
  }
  return 0;
}
```

~~十年OI一场空，______________。~~

---

## 作者：baoyangawa (赞：6)

[原题链接](https://www.luogu.com.cn/problem/CF1814E)

## 第一部分·状态&转移式

我们先考虑不带修改时，这个问题怎么做。

对于 $i\in [1,n)$，记 $s_i=\sum\limits_{i=1}^{i} w_i$。令 $s_n=s_{n-1}$。

我们令 $dp_i$ 为前 $i$ 个车互相交换需要的最小代价。

可以考虑存在一个位置 $j\in [0,i-2]$，将位于 $j+1\sim i-1$ 这些位置的车集体向右移动一步，位于 $i$ 的车向左移动到 $j+1$，这一部分车互相移动的代价为 $2\times (s_{i-1} - s_j)$。

此时 $1\sim j$ 这部分车辆互相移动的代价为 $dp_j$。

这时候我们就可以写出转移式了：

$$dp_i= \min\limits_{j=0}^{i-2} (2\cdot  s_{i-1}-2\cdot s_j+dp_j)=2\cdot s_{i-1}+\min\limits_{j=0}^{i-2} (dp_j-2\cdot s_j)$$

初值：$dp_0=0,dp_1=\infty $。此时答案就是 $dp_n$。

## 第二部分·优化状态&转移式

如果想要带修，可以考虑矩阵优化转移。

但这个式子里一堆 $s$，前缀和这个东西不好维护，于是我们考虑把转移式改一改。

我们发现原转移式中，$\min$ 函数中的结构都是 $dp_j-2\cdot s_j$。于是我们令 

$$\begin{aligned}dp'_i&=dp_i-2\cdot s_i\ \\
&=2\cdot s_{i-1}+\min\limits_{j=0}^{i-2} (dp_j-2\cdot s_j)-2 \cdot s_i\\
&=\min\limits_{j=0}^{i-2} (dp'_j) - 2*w_i\end{aligned}$$

此时答案为 $dp'_n+2\cdot s_n$。这里给出一份这部分暴力做法的核心代码：（以后 $dp'$ 均简写为 $dp$，最开始的 $dp$ 数组没有任何用了，可以忘记了）

```cpp
dp[1]=INF;
ll minn=0;
for(int i=2;i<=n;i++){
	dp[i]=minn-2*w[i];
	minn=min(minn,dp[i-1]);
}printf("%lld %lld\n",dp[n],2*s[n]);
```
## 第三部分-优化转移

接下来，我们可以考虑如何使用矩阵进行优化了。

观察暴力做法的核心代码，发现每次只有两个元素在更新：`dp[i]`，`minn`。

于是我们考虑构造这么一个初始矩阵：$\begin{bmatrix} minn&dp_i \end{bmatrix}$，这里的 $minn=\min\limits_{j=0}^{i-1}dp_j$。

关于为什么上界是 $i-1$，因为此时这个 $minn$ 代表着 $dp_i$ 转移后，经历了 `minn=min(minn,dp[i-1]);` 这行代码的 $minn$，所以自然上界是 $i-1$。这一点非常重要，编者因为这个 $minn$ 的含义混乱而调了好久。

我们这里定义一个广义上的矩阵乘法：将普通矩阵乘法中的乘换成加，加换成 $\min$。

考虑这个矩阵乘上一个什么样的系数矩阵可以转移到 $\begin{bmatrix} minn'&dp_{i+1} \end{bmatrix}$。（为了区分，我们这里记新的 $minn$ 为 $minn'$）

是这样的一个矩阵：

$$P_{i+1}=\begin{bmatrix} \;0&-2\cdot w_{i+1} \\\ 0  &\infty \end{bmatrix}$$

解释一下这个矩阵的具体含义：

- 第一列：转移 $minn'$

乘以这个矩阵的含义是 $dp_i$ 向 $dp_{i+1}$ 转移，故转移后的 $minn'$ 应为 $\min\limits_{j=0}^{i}dp_j$。

我们已经有了 $minn=\min\limits_{j=0}^{i-1}$ 和 $dp_i$，所以将「代表 $minn$ 的第一行第一列」和「代表 $dp_i$ 的第二行第一列」赋值为 $0$。

- 第二列：转移 $dp_{i+1}$

由转移式：$dp_{i+1}= minn - 2\cdot w_{i+1}$，所以将「代表 $minn$ 的第二行第一列」赋值为 $-2\cdot w_{i+1}$，其余赋值为 $\infty$。

此时，我们已经得到了这么一系列转移矩阵了。我们令转移最初的矩阵 $A_0=\begin{bmatrix} minn&dp_0 \end{bmatrix}=\begin{bmatrix} \infty&0 \end{bmatrix}$，乘上了 $P=\prod\limits_{i=1}^{n} P_i$ 后，就得到了 $A_n=\begin{bmatrix} minn&dp_n \end{bmatrix}$。

## 第四部分-处理修改

关于每一次修改，我们发现只会修改这个连乘式中的某一项，相当于一个**单点修改**。每一次计算答案，我们只需要求得这个连乘式本身，相当于一个**区间查询**。

关于维护这两个操作，我们自然而然就会想到：线段树！

我们建一颗值域为 $[1,n]$ 的线段树，区间为 $[i,i]$ 的叶子节点保存矩阵 $P_i$。这样子，我们就能够在 $O(T\log n)$ 的复杂度内完成修改和查询的操作（$T$ 为矩阵乘法的常数）。

这样，我们维护的一系列操作就完成了。输出答案为 $dp_n + 2\cdot sum$ （$sum$ 是一个实时维护的区间总和）。

总时间复杂度：$O((n+q)\log n)$。

这里放上 AC 代码：
```cpp
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
//#pragma GCC optimize("Ofast","inline")
#include<bits/stdc++.h>
#define fr(a) freopen(a,"r",stdin)
#define fw(a) freopen(a,"w",stdout)
#define MP(a,b) make_pair(a,b)
#define DEBUG
using namespace std;
typedef long long ll;
const int N=2e5+10;
const long long INF=0x3f3f3f3f3f3f3f3f;
struct node{
	ll l,r;
	ll p[2][2];
	void Init(){memset(p,0x3f,sizeof p);}
}tr[4*N];
ll n,q,w[N],sum;
node PUSH(node L,node R){
	node res;res.l=L.l,res.r=R.r;res.Init();
	for(int i=0;i<2;i++)
		for(int j=0;j<2;j++)
			for(int k=0;k<3;k++)
				res.p[i][j]=min(res.p[i][j],L.p[i][k]+R.p[k][j]);
	return res;
}
void build(ll x,ll l,ll r){
	tr[x].l=l,tr[x].r=r;
	if(l==r){
		tr[x].p[0][0]=0,tr[x].p[0][1]=-2*w[l];
		tr[x].p[1][0]=0,tr[x].p[1][1]=INF;
		return;
	}
	ll mid=(l+r)>>1;
	build(x*2,l,mid),build(x*2+1,mid+1,r);
	tr[x]=PUSH(tr[2*x],tr[2*x+1]);
	return;
}
void add(ll x,ll pos,ll val){
	if(tr[x].l==tr[x].r){
		tr[x].p[0][1]=-2*val;
		return;
	}
	ll mid=(tr[x].l+tr[x].r)>>1;
	if(pos<=mid) add(2*x,pos,val);
	else add(2*x+1,pos,val);
	tr[x]=PUSH(tr[2*x],tr[2*x+1]);
	return;
}
int main(){
	scanf("%lld",&n);
	for(int i=1;i<n;i++) scanf("%lld",&w[i]),sum+=w[i];
	build(1,1,n);
	scanf("%lld",&q);
	while(q--){
		ll pos,val;scanf("%lld%lld",&pos,&val);
		sum+=val-w[pos]; w[pos]=val;
		add(1,pos,val);
		printf("%lld\n",tr[1].p[1][1] + 2*sum);
		//tr[1] 上维护的就是题解中的 P。
		//一个 [∞,0] 的 A0 乘上 P，得到的结果为 An，它的第二项其实就是P[1][1]。
		//所以直接输出即可。 
	}
	return 0;
}
```

---

## 作者：TanX_1e18 (赞：2)

由于题目只需要每个点上棋子编号与点编号不同，所以观察可以发现每条边要么没有被走过，要么来回恰好各走一次。

于是操作转化为 **每次选择一条边 $i$，花费 $2a_i$ 的代价交换 $i$ 号点和 $i+1$ 号点上的棋子**

于是对于一个点，只要这个所连接的边至少有一条被执行过操作，则这个点一定合法。

接下来考虑对于一个区间 $[l,r]$ 求出局部答案，考虑一个点 $mid\in (l,r)$ ，于是可以通过 $[l,mid]$，$[mid+1,r]$，$[l,mid)$ 和 $(mid+1,r]$ 四个区间的答案分类讨论来求出 $[l,r]$ 的答案。

考虑线段树维护即可。计算类似 $[l,r)$ 的区间答案时，需要用到 $(mid+1,r)$ 的答案，所以线段树对于区间 $[l,r]$要维护四个值。

注意：对于长度为 $2$ 或 $3$ 的区间要特判。

附代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+9;
int v[N];
struct Node
{
	int val,nl,nr,nn;
}d[N<<2];
void pushup(int p,int l,int r)
{
	int mid=(l+r)/2;
	d[p].nl=min(d[p<<1].nn+v[mid]+min(d[p<<1|1].nl,d[p<<1|1].val),min(d[p<<1].nl+v[mid]+d[p<<1|1].nl,d[p<<1].nl+d[p<<1|1].val));
	d[p].nr=min(d[p<<1|1].nn+v[mid]+min(d[p<<1].nr,d[p<<1].val),min(d[p<<1|1].nr+v[mid]+d[p<<1].nr,d[p<<1|1].nr+d[p<<1].val));
	d[p].nn=min(d[p<<1].nl+d[p<<1|1].nr,v[mid]+min(d[p<<1].nl,d[p<<1].nn)+min(d[p<<1|1].nr,d[p<<1|1].nn));
	d[p].val=min(d[p<<1].val+d[p<<1|1].val,v[mid]+min(d[p<<1].val,d[p<<1].nr)+min(d[p<<1|1].val,d[p<<1|1].nl));
}
void update(int p,int l,int r,int x)
{
	if(r==l+2)
	{
		d[p].val=v[l]+v[l+1];
		d[p].nl=v[l+1];
		d[p].nr=v[l];
		d[p].nn=1e13;
		return;
	}
	if(r==l+1)
	{
		d[p].nl=1e13;
		d[p].nr=1e13;
		d[p].nn=0;
		d[p].val=v[l];
		return;
	}
	int mid=(l+r)/2;
	if(x<=mid)
	update(p<<1,l,mid,x);
	else
	update(p<<1|1,mid+1,r,x);
	pushup(p,l,r);
}
int n,q;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<n;i++)
	{
		cin>>v[i];
		update(1,1,n,i);
	}
	for(int i=1;i<n;i++)
	update(1,1,n,i);
	cin>>q;
	while(q--)
	{
		int x,k;
		cin>>x>>k;
		v[x]=k;
		update(1,1,n,x);
		cout<<d[1].val*2<<'\n';
	}
	return 0;
}
```

---

## 作者：Jordan_Pan (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1814E)

## 题目大意

一条 $n$ 个点的链，每个点停着一辆车，每次修改一条边的边权（修改不独立）。有 $m$ 次修改，询问修改后，通过这些道路移动车辆，使得每一辆车都不停在它的初始位置上，同时每个位置最终也仅有一辆车，并且车的移动总距离尽可能小。输出最小总距离。

数据范围：$n,m\leq 2\times 10^5$。

## Analysis

题解区好多神犇用特别高级的做法，可是蒟蒻并不会那些。

我们发现，不能有相邻的两条边都没有车经过（不然中间那辆车就移不了）。特殊地，链的两端必须有车经过。

进一步发现，对于每一条有车经过的边，必然被至少经过两次（不然只能移一部分车了），且必然存在恰好经过两次的方案（比如往右移一条边，最右边的车移到最左边）。

看到数据范围，什么东西支持动态修改、查询，且可以承受 $2\times 10^5$ 呢？

**线段树！**

令 $f_{i,0/1,0/1}$ 为结点 $i$，最左的边选/不选，最右的边选/不选的最小距离。这样，在 Pushup 的时候维护，答案就是 $f_{root,1,1}$。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int _=2e5+5;
int n,m;
long long t[_<<2][2][2];
void Pup(int x){
	t[x][0][0]=min(t[x<<1][0][1]+t[x<<1|1][1][0],
		min(t[x<<1][0][1]+t[x<<1|1][0][0],
			t[x<<1][0][0]+t[x<<1|1][1][0]));
	t[x][1][0]=min(t[x<<1][1][1]+t[x<<1|1][1][0],
		min(t[x<<1][1][1]+t[x<<1|1][0][0],
			t[x<<1][1][0]+t[x<<1|1][1][0]));
	t[x][0][1]=min(t[x<<1][0][1]+t[x<<1|1][1][1],
		min(t[x<<1][0][1]+t[x<<1|1][0][1],
			t[x<<1][0][0]+t[x<<1|1][1][1]));
	t[x][1][1]=min(t[x<<1][1][1]+t[x<<1|1][1][1],
		min(t[x<<1][1][1]+t[x<<1|1][0][1],
			t[x<<1][1][0]+t[x<<1|1][1][1]));
}//有点庞大，不要在意 
void Bld(int x,int L,int R){
	if(L==R){
		scanf("%lld",&t[x][1][1]);
		t[x][1][1]*=2;t[x][0][0]=0;
		t[x][1][0]=t[x][0][1]=1e15;
		return;
	}
	int M=L+R>>1;
	Bld(x<<1,L,M);
	Bld(x<<1|1,M+1,R);
	Pup(x);
}
void Chg(int x,int L,int R,int k,int v){
	if(L==R){
		t[x][1][1]=v*2;
		return;
	}
	int M=L+R>>1;
	if(k<=M)Chg(x<<1,L,M,k,v);
	else Chg(x<<1|1,M+1,R,k,v);
	Pup(x);
}
//线段树基本操作 
int main(){
	scanf("%d",&n);
	Bld(1,1,n-1);
	scanf("%d",&m);
	while(m--){
		int k,x;
		scanf("%d%d",&k,&x);
		Chg(1,1,n-1,k,x);
		printf("%lld\n",t[1][1][1]);
		//答案即为 1 号结点，两边都选。 
	}
	return 0;
}
```
时间复杂度 $O(m\log n)$。

跑的也不慢，最慢的点 702ms。

---

## 作者：hgzxwzf (赞：2)

## [CF1814E](https://www.luogu.com.cn/problem/CF1814E)

### 解题思路：

先选中哪些边被经过，那么对于极长的权值和为 $s$ 的连续边，显然可以用 $2s$ 的代价将所有点错排，而这是最小的代价，因为每条边只能经过偶数次，既然钦定了这些边被经过，那么被经过 $2$ 次就是最小的。

设 $dp_{i,0/1}$ 表示第 $i$ 条边选还是不选。

$dp_{0,0}=0,dp_{0,1}=+\infty$；

$dp_{i,0}=dp_{i-1,1},dp_{i,1}=\min(dp_{i-1,0,dp_{i-1,1}})+2\times a_i$。

用 ddp 优化即可。

[Code](https://codeforces.com/contest/1814/submission/201088720)。

---

## 作者：hcywoi (赞：2)

> 性质：如果要使 $i, i+1,\cdots, j$ 这几个点错排，则最小权值为 $2\times \displaystyle\sum_{k=i}^{j-1} w_k$（$w_k$ 表示第 $k$ 条边的权值）。

进一步可发现这一性质：

> 如果连续两条边都没有选择，必定不能使这 $n$ 个点错排。

$f_{i, 0}$ 表示不选第 $i$ 条边的最小权值；

$f_{i, 1}$ 表示选第 $i$ 条边的最小权值。

考虑转移：

- 第 $i$ 条边不选，则第 $i-1$ 条边必选，所以 $f_{i, 0}=f_{i-1, 1}$；
- 第 $i$ 条边选，则第 $i-1$ 条边可选可不选，所以 $f_{i, 1}=\min\{f_{i-1, 0}, f_{i - 1, 1}\}+2\times a_i$。

本题带修改，因此我们考虑 ddp。

我们新定义矩阵乘法。

我们令 $C=A\times B$。

则 $C_{i, j}=\displaystyle\min_{k=1}^{p}\{a_{i, k}+b_{k, j}\}$。

我们构造矩阵：

- $f_{i, 0}=\min\{f_{i-1, 0}+\infty, f_{i-1, 1}\}$；

- $f_{i, 1}=\min\{f_{i-1, 0}+2\times a_i, f_{i-1, 1}+ 2\times a_i\}$。

构造出如下矩阵：
$$
\begin{bmatrix}

\infty, 2\times a_i\\
0, 2\times a_i\\

\end{bmatrix}\times\begin{bmatrix}
f_{i - 1, 0}\\
f_{i - 1, 1}\\
\end{bmatrix}=\begin{bmatrix}
f_{i, 0}\\
f_{i, 1}
\end{bmatrix}
$$
答案就为 $\displaystyle\prod_{i=1}^{n}m_{n-i+1}$。

[代码。](https://codeforces.com/contest/1814/submission/202141327)

---

## 作者：skyskyCCC (赞：1)

## 前言。
[双倍经验](https://www.luogu.com.cn/problem/CF750E)。

这两道题都是典型的动态规划：用来解决带修改或者多次区间询问的动态规划问题，同时均可以将转移写成矩阵的形式，然后利用线段树求解相应的单点修改和区间查询问题。
## 分析。
注意到，每一条边要么不被经过，要么被从左边经过一次，右边经过一次，所以一个边要么选 $2$ 次要么选 $0$ 次，则第一条边一定被选了 $2$ 次。同时如果有一个边没有移动，那么显然这个边两边的边一定被操作了。这样我们就可以考虑一个动态规划的状态了。

设 $dp_i$ 为当考虑到第 $i$ 条边，并且这条边必定被操作时对答案的贡献。那么根据边的可选情况，就有：
$$dp_i=\min(dp_{i-1},dp_{i-2})+w_i$$
这就是这条边被选一次的结果，但是因为这个边必然被操作，所以一定被操作了两次，所以在一个式子的基础上在乘上一个二即可。

考虑广义矩阵乘法的形式为 $C_{i,j}=\min(A_{i,k},B_{k,i})$。我们可以用一个递推的思路进行求解：

初始化 $\begin{cases}dp_{-1}=0\\dp_{0}=+\infty\\dp_{1}=w_1\\dp_{2}=w_1+w_2\end{cases}$

那么我们显然可以将递推式一步步化简，首先考虑 $dp_1$ 和 $dp_0$ 之间的转移。可化为：
$$\left[dp_1,dp_0\right]=\left[dp_0,dp_{-1}\right]\begin{bmatrix}w_1&0\\w_1&+\infty\end{bmatrix}$$

同理有
$$\left[dp_2,dp_1\right]=\left[dp_1,dp_0\right]\begin{bmatrix}w_2&0\\w_2&+\infty\end{bmatrix}$$

那么我们就可以总结出规律：
$$\left[dp_i,dp_{i-1}\right]=\left[dp_{i-1},dp_{i-2}\right]\begin{bmatrix}w_i&0\\w_i&+\infty\end{bmatrix}$$

那么答案就可以转化为求每一个点的矩阵，最终的答案就是 $f_{n-1}$ 也就是 $X_{0,1}$。其中 $X_{0,1}$ 指的是从 $1$ 到 $n-1$ 的广义矩阵乘积。这样这个转移方程就转化为了维护每个点的矩阵，只需要单点修改或者区间查询。显然的线段树维护，就是把线段树上对应点的矩阵修改即可就可以转移了。事实上，这还可以优化，具体的优化方法不再赘述，具体可以见代码。

代码如下，仅供参考：
```
#include<iostream>
#include<cmath>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,q,k;
long long x;
long long w[800005];
struct node{
	long long a[3][3];
	node(){
	    memset(a,0x3F,sizeof(a));
	}
}dp[800005];
node operator * (node x,node y){
	node z;
	for(int i=1;i<=2;i++){
		for(int j=1;j<=2;j++){
			for(int k=1;k<=2;k++){
				z.a[i][j]=min(z.a[i][j],x.a[i][k]+y.a[k][j]);
			}
		}
	}
	return z;
}
void change(int now,int l,int r,int k,long long num){
	if(l==r){
		dp[now].a[1][1]=num;
		dp[now].a[2][1]=num;
		dp[now].a[1][2]=0;
		return;
	}
	int mid=(l+r)/2;
	if(k<=mid){
	    change(now*2,l,mid,k,num);
	}
	else change(now*2+1,mid+1,r,k,num);
	dp[now]=dp[now*2]*dp[now*2+1];
}
int main(){
	cin>>n;
	for(int i=1;i<=n-1;i++){
		cin>>w[i];
		change(1,1,n-1,i,w[i]);
	}
	cin>>q;
	for(int i=1;i<=q;i++){
		cin>>k>>x;
		change(1,1,n-1,k,x);
		cout<<2*dp[1].a[2][1]<<"\n";
	}
	return 0;
}
```
## 后记。
第 $100$ 篇题解，献给这个很有意思的动态规划。

大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：ax_by_c (赞：0)

先考虑单次询问怎么做，发现是选择一些边经过两次，且每个点的邻边至少选一个。

显然考虑 DP，设 $f_{i,0/1}$ 表示考虑了前 $i$ 个点且第 $i$ 个点前面的那条边是否选时的最小答案。

转移：$f_{i,0}+2w_i\rightarrow f_{i+1,1},f_{i,1}+2w_i\rightarrow f_{i+1,1},f_{i,1}\rightarrow f_{i+1,0}$。

这个东西显然可以写成广义矩阵乘法的形式，ddp 即可。

时间复杂度 $O((n+m)\log n)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define per(i,r,l) for(int i=(r);i>=(l);i--)
#define repll(i,l,r) for(ll i=(l);i<=(r);i++)
#define perll(i,r,l) for(ll i=(r);i>=(l);i--)
#define pb push_back
#define ins insert
#define clr clear
using namespace std;
namespace ax_by_c{
typedef long long ll;
const ll llinf=3e18;
const int N=2e5+5;
struct matr{
	ll a[2][2];
	int n,m;
	void clr(){
		rep(i,0,n-1)rep(j,0,m-1)a[i][j]=llinf;
	}
};
matr operator * (const matr &a,const matr &b){
	matr c;
	c.n=a.n;
	c.m=b.m;
	c.clr();
	rep(i,0,a.n-1)rep(k,0,b.m-1)rep(j,0,a.m-1)c.a[i][k]=min(c.a[i][k],a.a[i][j]+b.a[j][k]);
	return c;
}
struct DS1{
	matr tr[N*4];
	void pu(int u){
		tr[u]=tr[u<<1]*tr[u<<1|1];
	}
	void upd(int u,int l,int r,int p,matr x){
		if(l==r){
			tr[u]=x;
			return ;
		}
		int mid=l+((r-l)>>1);
		if(p<=mid)upd(u<<1,l,mid,p,x);
		else upd(u<<1|1,mid+1,r,p,x);
		pu(u);
	}
}tr;
int n,q;
matr a_;
void slv(){
	scanf("%d",&n);n--;
	rep(i,1,n){
		int x;
		scanf("%d",&x);
		a_.n=a_.m=2;
		a_.clr();
		a_.a[0][1]=x*2;
		a_.a[1][1]=x*2;
		a_.a[1][0]=0;
		tr.upd(1,1,n,i,a_);
	}
	scanf("%d",&q);
	rep(_,1,q){
		int k,x;
		scanf("%d %d",&k,&x);
		a_.n=a_.m=2;
		a_.clr();
		a_.a[0][1]=x*2;
		a_.a[1][1]=x*2;
		a_.a[1][0]=0;
		tr.upd(1,1,n,k,a_);
		a_.n=1,a_.m=2;
		a_.clr();
		a_.a[0][0]=0;
		a_=a_*tr.tr[1];
		printf("%lld\n",a_.a[0][1]);
	}
}
void main(){
	int T=1;
//	scanf("%d",&T);
	while(T--)slv();
}
}
int main(){
	ax_by_c::main();
	return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
比较一眼的 ddp 题。

摘自 [杂题选做](https://www.luogu.com.cn/training/518105)。
## 思路分析
我们知道一个显然的结论，一条边只会被经过 $0/2$ 次。

这个手模下就可以得出来了。

但是还有一个条件就是把经过 $2$ 次的边都连上后，不能存在孤立点。

考虑使用线段树维护这个东西。

那么我们只需要考虑区间维护什么东西才能合并为大区间。

维护出右端点连住最小值，左端点连住最小值，目前答案，整个区间连住可能最小值然后合并即可。
## 代码

```cpp
#include<bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=2e5+10,INF=0x3f3f3f3f3f3f3f3f,mod=998244353;
int n,m,a[N],t[N<<2][2][2];
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
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'||c=='&'||c=='|'||c=='('||c==')'); }
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
inline void pushup(int p)
{
    t[p][0][0]=t[p][1][0]=t[p][0][1]=t[p][1][1]=INF;
    for(int i=0;i<2;i++) for(int j=0;j<2;j++)
        for(int k=0;k<2;k++) for(int l=0;l<2;l++)
            if(k||j) t[p][i][l]=min(t[p][i][l],t[ls][i][j]+t[rs][k][l]);
}
inline void build(int p,int l,int r)
{
    if(l==r) return t[p][1][1]=a[l],t[p][1][0]=t[p][0][1]=INF,void();
    build(ls,l,mid);build(rs,mid+1,r);pushup(p);
}
inline void modify(int p,int l,int r,int x,int w)
{
    if(l==r) return t[p][1][1]=w,t[p][1][0]=t[p][0][1]=INF,void();
    if(mid>=x) modify(ls,l,mid,x,w);else modify(rs,mid+1,r,x,w);pushup(p);
}
inline void solve()
{
    n=read()-1;for(int i=1;i<=n;i++) a[i]=read();build(1,1,n);m=read();
    for(int i=1,x;i<=m;i++) x=read(),modify(1,1,n,x,read()),print(t[1][1][1]<<1),put('\n');
}
signed main()
{
    int T=1;while(T--) solve();
    genshin:;flush();return 0;
}
```

---

## 作者：Retired_lvmao (赞：0)

### 题意

在一条长度为 $n$ 的链上，有 $1\sim n$ 这 $n$ 个点，第 $i$ 条边连接着第 $i$ 个点到第 $i+1$ 个点，边权是 $w_i$。

在一开始，在第 $i$ 个点上都停着一辆车 $i$。现在，你需要通过这些道路，移动一些车辆，使得每一辆车都不停在它的初始位置上，使得每个位置最终也**仅有一辆车**，并且车的移动总距离尽可能小。

接下来会有 $m$ 组询问，每组询问会修改一条边的边权，你需要输出修改后的车的移动的最小距离。修改不独立，车并不会真的移动。

$n,m\leq 2\times 10^5$

### 题解

首先可以观察到，每一条边要么不被经过，要么被从左边经过一次，右边经过一次。因为如果被经过多次的话，那么左边过去的两个点和右边过去的两个点自己内部交换肯定会更优，不如不跨过。因此，我们只关心一条边有没有被经过。

考虑怎么样的方案是不合法的。假如有相邻的两条边没有被经过，那么他们的交点所在的车一定只能停在自己原来的位置，这样的方案显然不合法。特别的，最左边的边和最右边的边一定要被选。容易发现只要满足了这个条件，就一定合法。

然后，上面的问题就转化成了链上最大独立集问题，可以使用线段树简单优化 DP，时间复杂度 $O(n\log n)$，可能要乘上一个比较大的常数。

### 代码
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[200010],q;
struct node
{
	int f[2][2]; 
};
node t[800010];
int sum=0;
node operator +(node x,node y)
{
	node res;
	for(int i=0;i<=1;i++)
		for(int j=0;j<=1;j++)
			res.f[i][j]=-1e18;
	for(int i=0;i<=1;i++)
	{
		for(int j=0;j<=1;j++)
		{
			for(int k=0;k<=1;k++)
			{
				for(int l=0;l<=1;l++)
					if(j==0||k==0)
						res.f[i][l]=max(x.f[i][j]+y.f[k][l],res.f[i][l]);	
			}
		} 
	}
	return res;
}
void build(int x,int l,int r)
{
	if(l==r)
	{
		t[x].f[0][0]=0,t[x].f[0][1]=-1e18;
		t[x].f[1][0]=-1e18;t[x].f[1][1]=a[l];
		return ;
	}
	int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	t[x]=t[x<<1]+t[x<<1|1];
}
void update(int x,int l,int r,int p,int v)
{
	if(p<l||p>r)
		return ;
	if(l==r)
	{
		t[x].f[0][0]=0,t[x].f[0][1]=-1e18;
		t[x].f[1][0]=-1e18;t[x].f[1][1]=v;
		return ;
	}
	int mid=(l+r)/2;
	update(x<<1,l,mid,p,v);
	update(x<<1|1,mid+1,r,p,v);
	t[x]=t[x<<1]+t[x<<1|1]; 
}
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<n;i++)
		scanf("%lld",&a[i]),sum+=a[i];
	build(1,1,n-1);
	scanf("%lld",&q);
	while(q--)
	{
		int x,v;
		scanf("%lld%lld",&x,&v);
		sum-=a[x];
		a[x]=v;
		sum+=a[x];
		update(1,1,n-1,x,v); 
		printf("%lld\n",(sum-t[1].f[0][0])*2);
	}
}
```

---

## 作者：DerrickLo (赞：0)

如果将一个区间 $[l,r]$ 中的所有车错排，则需要 $2\times \displaystyle{\sum_{i=l}^{r}a_i}$ 的距离。

设 $f_{i,0/1}$ 表示第 $i$ 条边选不选，那么：

$$f_{i,0}=f_{i-1,1}$$

$$f_{i,1}=\max(f_{i-1,0},f_{i-1,1})+a_i$$

答案即为 $2\times \max(f_{n-1,0},f_{n-1,1})$。

考虑优化，利用 $(\min,+)$ 的矩阵乘法，显然可以得到

$$\begin{bmatrix}f_{i,0} & f_{i,1}\end{bmatrix}=\begin{bmatrix}f_{i-1,0} & f_{i-1,1}\end{bmatrix}\begin{bmatrix}+\infin & a_i\\0 & a_i\end{bmatrix}$$

直接用线段树维护矩阵即可，复杂度 $\mathcal O(k^3n\log n)$，其中 $k=2$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[200005],q,f[200005],k,x;
struct tree{
	int l,r,a[5][5];
	friend tree operator+(const tree&a,const tree&b){
		tree c;
		if(a.l==-1&&a.r==-1)return b;
		c.l=a.l,c.r=b.r;
		for(int i=1;i<=2;i++)for(int j=1;j<=2;j++)c.a[i][j]=1e18;
		for(int i=1;i<=2;i++)for(int j=1;j<=2;j++)for(int k=1;k<=2;k++)c.a[i][j]=min(c.a[i][j],a.a[i][k]+b.a[k][j]);
		return c;
	}
	friend tree operator+=(tree&a,const tree&b){
		a=a+b;
	}
}tr[800005];
void build(int u,int l,int r){
	if(l==r){
		tr[u].l=l,tr[u].r=r;
		tr[u].a[1][1]=1e18,tr[u].a[1][2]=a[l];
		tr[u].a[2][1]=0,tr[u].a[2][2]=a[l];
		return;
	}
	int mid=l+r>>1;
	build(u<<1,l,mid),build(u<<1|1,mid+1,r);
	tr[u]=tr[u<<1]+tr[u<<1|1];
}
void change(int u,int pos,int x,int y,int k){
	if(tr[u].l==tr[u].r){
		tr[u].a[x][y]=k;return;
	}
	int mid=tr[u].l+tr[u].r>>1;
	if(pos<=mid)change(u<<1,pos,x,y,k);
	else change(u<<1|1,pos,x,y,k);
	tr[u]=tr[u<<1]+tr[u<<1|1];
}	
tree query(int u,int l,int r){
	if(tr[u].l>=l&&tr[u].r<=r)return tr[u];
	int mid=tr[u].l+tr[u].r>>1;
	tree ans;ans.l=ans.r=-1;
	if(l<=mid)ans+=query(u<<1,l,r);
	if(r>mid)ans+=query(u<<1|1,l,r);
	return ans;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n,n--;
	for(int i=1;i<=n;i++)cin>>a[i];
	build(1,1,n);
	cin>>q;
	while(q--){
		cin>>k>>x,a[k]=x;
		if(n==1){cout<<a[1]*2<<"\n";continue;}
		if(n==2){cout<<a[1]*2+a[2]*2<<"\n";continue;}
		change(1,k,1,2,a[k]),change(1,k,2,2,a[k]);
		tree res=query(1,2,n-1);
		cout<<2*(min({res.a[1][1],res.a[1][2],res.a[2][1],res.a[2][2]})+a[1]+a[n])<<"\n";
	}
	return 0;
}
```

---

