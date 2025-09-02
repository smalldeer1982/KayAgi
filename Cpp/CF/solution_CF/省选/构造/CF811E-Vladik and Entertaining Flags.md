# Vladik and Entertaining Flags

## 题目描述

In his spare time Vladik estimates beauty of the flags.

Every flag could be represented as the matrix $ n×m $ which consists of positive integers.

Let's define the beauty of the flag as number of components in its matrix. We call component a set of cells with same numbers and between any pair of cells from that set there exists a path through adjacent cells from same component. Here is the example of the partitioning some flag matrix into components:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF811E/9c3d5d03c8614a33f231cd8f8efd0e706383885b.png)But this time he decided to change something in the process. Now he wants to estimate not the entire flag, but some segment. Segment of flag can be described as a submatrix of the flag matrix with opposite corners at $ (1,l) $ and $ (n,r) $ , where conditions $ 1<=l<=r<=m $ are satisfied.

Help Vladik to calculate the beauty for some segments of the given flag.

## 说明/提示

Partitioning on components for every segment from first test case:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF811E/d3d891fc856386c8b0c1e1a004521369cd8ed774.png)

## 样例 #1

### 输入

```
4 5 4
1 1 1 1 1
1 2 2 3 3
1 1 1 2 5
4 4 5 5 5
1 5
2 5
1 2
4 5
```

### 输出

```
6
7
3
4
```

# 题解

## 作者：fade_away (赞：9)

## Solution

刚想出来的时候以为很高妙，写完感觉不如直接线段树。。。

看到网格图连通块个数，一个基本的套路是平面图欧拉公式，即在网格图上相邻且颜色不同的格子之间连边，然后把要求的连通块个数 $C$ 转化为 $V-E+F-1$ ，其中 $V$ 表示点数，$E$ 表示边数， $F
$ 表示被边分割成的区域个数。

点数即为 $(r-l+1)\times n$。

边数直接前缀和一波即可。

区域个数怎么求呢？我一开始以为直接统计四元环个数就可以了（因为以前做过一道类似思路的题），然后发现假得离谱。

事实上我们可以把平面图转对偶图，把原先网格图上的边转化为格点之间的边（把四个格子中间的点当成格点）。

这样就得到关于所有格点的图，我们可以用并查集统计每个连通块的最左和最右延伸到哪里，设其为 $(l,r)$，那么对于询问 $(Ql,Qr)$，我们要求的就是有多少个 $(l,r)$ 满足 $Ql\leq l\leq r\leq Qr$。

这个显然可以扫描线+树状数组解决，总时间复杂度为 $O(nm\log m)$。

实测跑得很快， CF 上排 Rank2 （发现被 EI 在两年前用同种做法吊打了 QWQ）。

## Code

```cpp
vector<int> C[MAXN];
vector<PR> Q[MAXN];
int s1[MAXN], s2[MAXN], a[12][MAXN], Ans[MAXN], n, m, K;
int f[MAXM], flag[MAXM];
PR A[MAXM];

int s[MAXN];
int getid(int x, int y) { return (x - 1) * (m - 1) + y; }
void add(int x) {
	for (; x <= m ; x += x & (-x)) ++ s[x];
}
int query(int x) {
	int ans = 0;
	for (; x ; x -= x & (-x)) ans += s[x];
	return ans;
}
int find(int x) { return f[x] == x ? f[x] : f[x] = find(f[x]); }
void merge(int x, int y) {
	x = find(x), y = find(y);
	if (x == y) return;
	flag[y] |= flag[x], f[x] = y;
	upmin(A[y].fi, A[x].fi);
	upmax(A[y].se, A[x].se);
}
signed main() {
#ifndef ONLINE_JUDGE
	freopen("a.in", "r", stdin);
#endif
	read(n), read(m), read(K);
	for (int i = 1; i <= n ; ++ i)
		for (int j = 1; j <= m ; ++ j) read(a[i][j]);
	for (int i = 1; i <= n ; ++ i) 
		for (int j = 1; j <= m ; ++ j) {
			if (a[i][j] == a[i][j + 1]) ++ s1[j];
			if (a[i][j] == a[i + 1][j]) ++ s2[j];
		}
	for (int i = 1; i <= m ; ++ i) s1[i] += s1[i - 1], s2[i] += s2[i - 1];

	for (int i = 1; i <= n - 1 ; ++ i)
		for (int j = 1; j <= m - 1 ; ++ j) {
			int t = getid(i, j);
			f[t] = t, A[t] = MP(j, j + 1);
		}
	for (int i = 1; i < n ; ++ i) {
		if (a[i][1] != a[i + 1][1]) flag[getid(i, 1)] = 1;
		if (a[i][m] != a[i + 1][m]) flag[getid(i, m - 1)] = 1;
	}
	for (int i = 1; i < m ; ++ i) {
		if (a[1][i] != a[1][i + 1]) flag[getid(1, i)] = 1;
		if (a[n][i] != a[n][i + 1]) flag[getid(n - 1, i)] = 1;
	}
	for (int i = 2; i < n ; ++ i)
		for (int j = 1; j < m ; ++ j) 
			if (a[i][j] != a[i][j + 1]) merge(getid(i - 1, j), getid(i, j));	
	for (int i = 1; i < n ; ++ i)
		for (int j = 2; j < m ; ++ j) 
			if (a[i][j] != a[i + 1][j]) merge(getid(i, j - 1), getid(i, j));

	for (int i = 1; i <= (n - 1) * (m - 1) ; ++ i)
		if (f[i] == i && !flag[i]) C[A[i].fi].PB(A[i].se);

	for (int i = 1, l, r; i <= K ; ++ i) 
		read(l), read(r), Q[l].PB(MP(r, i)), Ans[i] = (r - l + 1) * n - (s2[r] - s2[l - 1]) - (s1[r - 1] - s1[l - 1]);
	for (int i = m; i >= 1 ; -- i) {
		for (auto v : C[i]) add(v);
		for (auto v : Q[i]) Ans[v.se] += query(v.fi);
	}
	for (int i = 1; i <= K ; ++ i) print(Ans[i]), putc('\n');
	return 0;
}
```


---

## 作者：enucai (赞：7)

## Analysis

区间查询？**线段树**！

考虑线段树上的一个点 $c$ 表示 $[L,R]$ 区间，我们需要记录最左边一列每个点所属的连通块 $\{l\}$，最右边一列每个点所属的连通块 $\{r\}$ 与当前的连通块个数 $val$。

考虑合并。先将总连通块个数相加，再减去算重的，即属于**同一个连通块**的。由于两块合并过程中使原来不连通的两个连通块连通只有可能是交界线左右的点颜色相同，因此枚举交界线上的每一对点，用**并查集**维护即可。

时间复杂度 $O(n\alpha (n)q\log m)$，$\alpha(n)$ 为并查集时间复杂度。

## Code

**Talk is cheap, show me the code.**

[Codeforces Status](https://codeforces.com/contest/811/submission/153384616)

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define For(i,j,k) for(int i=(j);i<=(k);i++)
#define Rof(i,j,k) for(int i=(j);i>=(k);i--)
#define mid (l+r)/2
int n,m,q,a[11][100010],tot=0,fa[1100010];
struct node{
	int l[11],r[11],val;
}tr[400010];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
node add(node x,node y,int l,int r){
	node res;res.val=x.val+y.val;
	For(i,1,n) res.l[i]=x.l[i],res.r[i]=y.r[i];
	For(i,1,n) fa[x.l[i]]=x.l[i],fa[x.r[i]]=x.r[i];
	For(i,1,n) fa[y.l[i]]=y.l[i],fa[y.r[i]]=y.r[i];
	For(i,1,n) if(a[i][l]==a[i][r]){
		int fx=find(x.r[i]),fy=find(y.l[i]);
		if(fx!=fy) res.val--,fa[fx]=fy;
	}
	For(i,1,n) res.l[i]=find(res.l[i]),res.r[i]=find(res.r[i]);
	return res;
}
void build(int c,int l,int r){
	if(l==r){
		For(i,1,n){
			if(a[i][l]==a[i-1][l]) tr[c].l[i]=tr[c].r[i]=tr[c].l[i-1];
			else tr[c].l[i]=tr[c].r[i]=++tot,tr[c].val++;
		}
		return;
	}
	build(c*2,l,mid),build(c*2+1,mid+1,r);
	tr[c]=add(tr[c*2],tr[c*2+1],mid,mid+1);
}
node qry(int c,int l,int r,int x,int y){
	if(l==x&&r==y) return tr[c];
	if(y<=mid) return qry(c*2,l,mid,x,y);
	if(x>mid) return qry(c*2+1,mid+1,r,x,y);
	else return add(qry(c*2,l,mid,x,mid),qry(c*2+1,mid+1,r,mid+1,y),mid,mid+1);
}
signed main(){
	ios::sync_with_stdio(false),cin.tie(0);
	cin>>n>>m>>q;
	For(i,1,n) For(j,1,m) cin>>a[i][j];
	build(1,1,m);
	while(q--){
		int l,r;cin>>l>>r;
		cout<<qry(1,1,m,l,r).val<<'\n';
	}
}
```

---

## 作者：hwk0518 (赞：5)

#### 运用线段树，线段树每个节点维护两个信息：

#### (1)该区间中有多少个连通块；

#### (2)该区间左边一列和右边一列的节点属于哪个集合。两个节点在同一个集合当且仅当它们能够通过区间中的点互相连通。

#### 合并节点的时候，将相邻两列中相邻且颜色相同的点所在的集合用并查集合并即可。

#### 代码：#### 

```

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<algorithm>
#include<math.h>
using namespace std;

const int N=12;
const int M=1e5+5;
int n,m,q,a[N][M],fa[N*M],seg_tot;
struct node
{
	int l[N],r[N],sum;
};
node seg[M<<2],ans;

int getfa(int x)
{
	if(fa[x]!=x) fa[x]=getfa(fa[x]);
	return fa[x];
}

void newseg(node &x,int pos)
{
	int i;
	for(i=1;i<=n;++i)
		if(a[i][pos]==a[i-1][pos])
			x.l[i]=x.r[i]=x.l[i-1];
		else
			x.l[i]=x.r[i]=++seg_tot,++x.sum;
}

void merge(node &x,node lsn,node rsn,int rb,int lb)
{
	int i;
	x.sum=lsn.sum+rsn.sum;
	for(i=1;i<=n;++i) x.l[i]=lsn.l[i],x.r[i]=rsn.r[i];
	for(i=1;i<=n;++i)
	{
		fa[lsn.l[i]]=lsn.l[i],fa[lsn.r[i]]=lsn.r[i];
		fa[rsn.l[i]]=rsn.l[i],fa[rsn.r[i]]=rsn.r[i];
	}
	
	for(i=1;i<=n;++i)
		if(a[i][rb]==a[i][lb])
		{
			int fx=getfa(lsn.r[i]);
			int fy=getfa(rsn.l[i]);
			if(fx!=fy)
				--x.sum,fa[fx]=fy;
		}
	
	for(i=1;i<=n;++i)
		x.l[i]=getfa(x.l[i]),x.r[i]=getfa(x.r[i]);
}

void build(int l,int r,int rt)
{
	if(l==r)
	{
		newseg(seg[rt],l);
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,rt<<1),build(mid+1,r,rt<<1|1);
	merge(seg[rt],seg[rt<<1],seg[rt<<1|1],mid,mid+1);
}

void query(int l,int r,int rt,int L,int R)
{
	if(L<=l&&r<=R)
	{
		if(!ans.l[1]) ans=seg[rt];
		else merge(ans,ans,seg[rt],l-1,l);
		return;
	}
	int mid=(l+r)>>1;
	if(L<=mid) query(l,mid,rt<<1,L,R);
	if(R>mid) query(mid+1,r,rt<<1|1,L,R);
}

void init()
{
	int i,j;
	scanf("%d%d%d",&n,&m,&q);
	for(i=1;i<=n;++i)
		for(j=1;j<=m;++j)
			scanf("%d",&a[i][j]);
}

void work()
{
	int i,l,r;
	build(1,m,1);
	while(q--)
	{
		for(i=1;i<=n;++i) ans.l[i]=0;
		scanf("%d%d",&l,&r);
		query(1,m,1,l,r);
		printf("%d\n",ans.sum);
	}
}

int main()
{
	init();work();
	return 0;
}

```

---

## 作者：fast_photon (赞：1)

**0. 前言**  
啊，终于做到在线输入复杂度了。虽然跑了 EI 四倍时间。哭哭。  

**1. 思路**   
就还是平面图欧拉定理。  
顶点是所有在接下来操作中获得至少一条边的格点。  
边是，在相邻不同的格子公用的两个格点之间连一条边（分开这两个字符）。认为网格的外边都是 $0$。  
对于连通平面图，有 $V-E+F=1$（不含外边不封闭的区域），那么对于每个连通块求和，就有 $V-E+F=C$，其中 $C$ 为连通块个数。  
```plaintext
ab
cd
```
把点按度数分类。当然不能存在 $1$ 度点。否则就会有 $a=b=d=c\neq a$。矛盾。  
那么用 $V_i$ 表示度数为 $i$ 的点的个数。  
$$V_2+V_3+V_4-E+F=C$$  
每个点的度数和，恰好是边数的两倍。  
$$V_2+V_3+V_4-\frac{2V_2+3V_3+4V_4}{2}+F=C$$  
移项化简，得：
$$F=\frac{V_3+2V_4}{2}+C$$  
要求 $F$。区间查询相当于需要统计区间内的 $V$ 和 $C$ 的信息，再处理一些边界情况。  
$V$ 的边界情况很简单，边界上当 $a_{i,j}\neq a_{i,j+1}$ 会产生 $3$ 度点。
所以要考虑统计 $C$。  
为了方便，先给格点编号，$(x,y)$ 的格子左上角的格点坐标是 $(x,y)$。  

先看看“保留 $l$ 到 $r$ 的格子”这一操作发生了什么。实际上是把 $[l,r]$ 之外的部分全都变成 $0$。在格点图上，就是 $l-1,l$ 之间纵向全连上，$r,r+1$ 之间纵向全连上，多的边去掉。  
什么时候会形成与最外圈边不连通的连通块？首先原图中必然要有这样一个和最外圈不连通的连通块。  

然后，若连通块的横向范围为 $[L,R]$，那么 $l<L,R<r$ 是充要条件。因为当且仅当这时这个连通块会被保留，而新加的边不会把它和最外层连通。  

对于原图中的连通块，可以直接 $O(nm)$ 搜出来。  

问题就转化成了，有若干堆在一起的线段，每次询问一个区间包含了多少线段。  
这个问题显然不能直接做。考虑找找性质。  
我们发现，一个连通块若范围是 $[L,R]$，那么对于任意的 $x\in [L,R]$，这个连通块必然包含了第 $x$ 列的至少一个点。  
接下来可以证明至少有两个点。考虑反证，如果只有一个点，由于不存在 $0,1$ 度点，它只能是一个向左右都连边的 $2$ 度点。但是一个连通块的最外边一圈向外都没有边，所以它最外圈的格子都是相同的。而这一条边上下一样，就不应该连边，矛盾。  

所以在“线段覆盖问题”中，同一个位置的线段不超过 $\lfloor\frac{m}{2}\rfloor$ 条。  
那么这样就会重新变回二维问题，所以可以考虑压到一个二进制数里。怎么分配每个线段是第几位呢？考虑把线段按左端点排序（**桶排**），从左向右考虑，若某个位置没有被分配，且前一列这个位置没有被分配，就分配给这条线段。  
第二个限制是为了在二进制压缩后区分 $[1,2],[3,4]$ 和 $[1,4]$。   
这样分配一定是不超过 $m$ 个位置的。不能被分配的位置只有这一位有的和上一位有的，$\le 2\lfloor\frac{m}{2}\rfloor\le m$。  
假定压好了的序列是 $b_i$。

怎么求呢？还是考虑调整法。显然完全包含线段的个数等于其端点个数的一半。  
先前缀和统计区间内所有端点。  
然后看 $\operatorname{popcount}(b_l \operatorname{and} b_{l+1})$ 以确定左边捅进区间的线段个数，把它们减去。右边同理。与一下是为了避免有区间端点落在这里的情况。这就是刚才第二条限制的用处。  
但是这样会去掉完全包含询问区间的线段。需要加上它们的二倍。  
由于分配方案保证有重叠的线段不同层，所以它一定是独占这一整层。又由于可以首尾相接的线段不同层，所以如果没有被独占，某一层一定有空隙。  
所以贯穿的线段数量等于 $[l,r+1]$ 区间与的 $\operatorname{popcount}$。  

这一部分怎么做到输入复杂度呢？ $O(1)$ 查询区间与的数据结构很多。可以先用 [sqrt tree](https://oi-wiki.org/ds/sqrt-tree/) 做掉 $m>\log\log n$ 的情况。  
若 $m$ 很小，感性理解，如果分块的话，每一块所有数的总共组合是很少的，所以可以打表然后 $O(1)$。  
还是考虑 sqrt tree。但是这次我们按 $b=\log\log n$ 把原序列分块。然后每个块求一个与。块间信息丢去建 sqrt tree。一个块内的数压到一个数里（在二进制下补前导 $0$ 到 $\log$ 位，首尾拼接）。  
因为有 $m<\log\log n$，所以有 $m<\frac{\log n}{\log\log n}$，一个块里的信息可以用和 $n$ 相同个数的整型存下。  
那么一个块压到一起的块内信息和散块信息可以位运算，提取出想要的区间，然后查表。一个块的值域是 $n$，可以 $O(n)$ 打表。  

就，没了。最终复杂度 $O(nm+q)$。  

**2. 代码**  
```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<cmath>
#include<cassert>
#define maxn 15
#define maxm 132005
#define AND_ONE 16777215 //2^24-1
#define l2_maxm 18

using namespace std;

int n, m, q, ql, qr, a[maxn][maxm], sf[maxn][maxm], sr[maxn][maxm], sc[maxn][maxm], vis[maxn][maxm], sl[maxm], usd[maxn], val[maxm];
int l2[(1 << l2_maxm) + 5], cnt[maxm];

int lp = maxm - 3, rp = 0, u = maxn, d = 0;

const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1}, px[4] = {-1, -1, 0, 0}, py[4] = {-1, 0, 0, -1};  
//这里的方向偏移，若某个点在 dx 中 d 的方向上有边，则网格图中它在 px 的 d 和 d+1 方向的格子不同。

vector<int> g[maxm], p[maxm];

struct sqrt_tree { //sqrt tree板子
	int n, m, dat[maxm], sum[maxm][l2_maxm + 1], pre[maxm][l2_maxm + 1], suf[maxm][l2_maxm + 1], b[l2_maxm + 1];
	sqrt_tree() {
		for(int i = 0; i < maxm - 5; i++) {
			dat[i] = AND_ONE;
			for(int j = 0; j < l2_maxm; j++) {
				sum[i][j] = pre[i][j] = suf[i][j] = AND_ONE;
			}
		}
	}
	int build(int *a, int nn) {
		n = nn;
		for(int i = 0; i < n; i++) dat[i] = a[i];
		b[0] = 1;
		m = 0;
		for(int i = 1; b[i - 1] && ((n >> (b[i - 1] << 1))); i++) {
			m = i;
			if(i == 1) b[i] = 1;
			else b[i] = b[i - 1] << 1;
		}
		n = ((n + (1 << b[m]) - 1) >> b[m]) << b[m];
		for(int i = 0; i <= m; i++) {
			for(int j = 0; j < n; j += (1 << b[i])) {
				for(int k = 0; k < (1 << b[i]); k++) {
					sum[j][i] &= dat[j + k];
					pre[j + k][i] = dat[j + k];
					if(k) pre[j + k][i] &= pre[j + k - 1][i];
				}
				for(int k = (1 << b[i]) - 1; k >= 0; k--) {
					suf[j + k][i] = dat[j + k];
					if(k ^ ((1 << b[i]) - 1)) suf[j + k][i] &= suf[j + k + 1][i]; 
				}
				for(int k = 1; k < (1 << b[i]); k++) {
					if(j + (k << b[i]) >= n) break;
					sum[j + k][i] = sum[j + k - 1][i] & sum[j + (k << b[i])][i]; 
				}
			}
		}
		return n;
	}
	int query(int l, int r) {
		int p = l2[l ^ r];
		if(~p) {
			int i = l2[p] + 1;
			if((l >> b[i]) + 1 == (r >> b[i])) return suf[l][i] & pre[r][i];
			else return suf[l][i] & pre[r][i] & sum[(((l + (1 << b[i])) >> b[i]) << b[i]) + (r >> b[i]) - (l >> b[i]) - 2][i];
		}
		else return dat[l];
	} 
} sqt;

struct ras { //数据分治，是直接 sqrt tree 还是 sqrt tree+分块打表
	int n, dat[maxm], V, mode, dta[maxm], adt[maxm], pre[maxm], suf[maxm], sum[(1 << l2_maxm) + 5], b;
	ras() {
		for(int i = 0; i < maxm - 5; i++) dat[i] = dta[i] = AND_ONE, adt[i] = 0;
		for(int i = 0; i < (1 << l2_maxm); i++) sum[i] = AND_ONE;
	}
	void build(int *a, int nn) {
		n = nn;
		V = 1;
		for(int i = 1; i <= n; i++) V = max(V, a[i]);
		V = ceil(log2(V));
		b = ceil(log2(log2(n)));
		if(V * b >= 30) mode = 1, n = sqt.build(a, nn);
		else {
			mode = 2;
			for(int i = 0; i < n; i++) dat[i] = a[i];
			n = (n + b - 1) / b;
			for(int j = 0; j < n; j++) {
				for(int i = 0; i < b; i++) {
					dta[j] &= dat[j * b + i];
				}
			}
			n = b * sqt.build(dta, n);
			for(int j = 0; j < n; j += b) {
				for(int i = 0; i < b; i++) {
					adt[j] |= dat[i + j] << ((b - i - 1) * V);
					pre[i + j] = dat[i + j];
					if(i) pre[i + j] &= pre[i + j - 1];
				}
				for(int i = b - 1; i >= 0; i--) {
					suf[i + j] = dat[i + j];
					if(i ^ (b - 1)) suf[i + j] &= suf[i + j + 1];
				}
				for(int i = 1; i < b; i++) adt[i + j] = adt[i];
			}
			sum[(1 << (V * b)) - 1] = ((1 << V) - 1);
			int mx = (1 << (V * b));
			for(int i = mx - 2; i >= 0; i--) {
				sum[i] = sum[(i >> V) | (((1 << V) - 1) << ((b - 1) * V))] & i;
			}
		}
	}
	int query(int l, int r) {
		if(mode == 1) return sqt.query(l, r);
		else {
			if(l / b == r / b) {
				return sum[adt[l / b * b] & (((1 << (V * (b - l % b))) - 1) ^ ((1 << (V * (b - r % b - 1))) - 1))];
			}
			else if(l / b + 1 == r / b) {
				return suf[l] & pre[r];
			}
			else return suf[l] & pre[r] & sqt.query(l / b + 1, r / b - 1);
		}
	}
} ra; 

void dfs(int i, int j) {
	if(vis[i][j]) {
		return ;
	}
	vis[i][j] = 1;
	lp = min(lp, j), rp = max(rp, j);
	u = min(u, i), d = max(d, i);
	for(int d = 0; d < 4; d++) {
		int x = i + dx[d], y = j + dy[d];
		if(x >= 1 && x <= n + 1 && y >= 1 && y <= m + 1) {
			if(a[i + px[d]][j + py[d]] != a[i + px[(d + 1) & 3]][j + py[(d + 1) & 3]]) {
				dfs(x, y);
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m >> q;
	l2[0] = -1;
	for(int i = 1; i < (1 << l2_maxm); i++) l2[i] = l2[i >> 1] + 1;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) cin >> a[i][j];
	}
	for(int i = 1; i <= n + 1; i++) {
		for(int j = 1; j <= m + 1; j++) {
			sf[i][j] = (a[i][j] != a[i][j - 1]) + (a[i][j - 1] != a[i - 1][j - 1]) + (a[i - 1][j - 1] != a[i - 1][j]) + (a[i - 1][j] != a[i][j]);
			sr[i][j] = a[i][j] != a[i][j - 1];
			sc[i][j] = a[i][j] != a[i - 1][j];
			if(!vis[i][j] && sf[i][j]) {
				lp = maxm - 3, rp = 0, u = maxn, d = 0;
				dfs(i, j);
				if(lp != 1 && rp != m + 1 && u != 1 && d != n + 1) {
					g[lp].push_back(rp);
					cnt[lp]++, cnt[rp]++;
				}
			}
			sf[i][j] = max(sf[i][j] - 2, 0);
			sf[i][j] += sf[i - 1][j] - sf[i - 1][j - 1] + sf[i][j - 1]; 
			sr[i][j] += sr[i][j - 1];
			sc[i][j] += sc[i - 1][j];
		}
	}
	for(int i = 1; i <= m + 1; i++) {
		cnt[i] += cnt[i - 1];
	}
	for(int i = 1; i <= m + 1; i++) {
		int ptr = 0;
		for(int r : g[i]) {
			while(usd[ptr] && ptr <= n) ptr++;
			if(usd[ptr]) break;
			usd[ptr] = 1;
			p[r + 1].push_back(ptr);
		}
		for(int x : p[i]) usd[x] = 0;
		for(int j = 0; j <= n; j++) {
			val[i] |= (usd[j] << j);
		}
	}
	val[0] = AND_ONE;
	ra.build(val, m + 2);
	while(q--) {
		cin >> ql >> qr;
		int ans = sf[n][qr] - sf[n][ql] + sf[1][ql] - sf[1][qr];
		ans += sc[n][qr] - sc[1][qr] + sc[n][ql] - sc[1][ql];
		ans += sr[n][qr] - sr[n][ql] + sr[1][qr] - sr[1][ql];
		if(ql != qr) {
			ans += cnt[qr] - cnt[ql];
			ans -= __builtin_popcount(val[ql] & val[ql + 1]) + __builtin_popcount(val[qr] & val[qr + 1]);
			ans += 2 * __builtin_popcount(ra.query(ql, qr + 1) & ((1 << (n + 1)) - 1));
		}
		cout << (ans >> 1) + 1 << '\n';
	}
}
```

**3. 后记**  
dfs 常数太大。sqrt tree 我写的常数太大。  
跑了之前写的 $nm+qn$ 的 $1.5$ 倍，跑了 EI 的四倍。不做人了啦！

---

## 作者：岂非 (赞：1)

## 题意

给定一个 $n\leq 10$，$m\leq 10^5$ 的颜色矩阵，每次询问求某两列之间的连通块数。

## 分析

看到 $m\leq 10^5$，再加上维护的是连通块这种不寻常东西，第一时间想到分块。

考虑对于每个整块维护连通块个数，散块暴力算，最后把所有块的连通块个数加起来，再减去块与块合并减少的连通块数量就是答案。块内连通块数量使用并查集即可解决。

考虑预处理块间合并减少的连通块个数。先把两个块最右端一列与最左端一列在块内的连通情况记下来。两个块合并时，若相邻两点颜色相同且不处于同一集合，那么代表答案多算了一次，将答案减一并合并两集合。

注意散块与整块/散块合并时不能直接调用该值，因为散块与原整块的块内连通情况显然不一样。需要重新计算。

设块长为 $B$，时间复杂度为 $O(\alpha(nB)nm+q(\alpha(nB)nB+\frac{m}{B}))$。

取 $B=100$ 即可通过本题。

## 代码

这份代码时间复杂度有误，并查集没有按秩合并，但是能过。

调代码的时候本着能加新的就不改旧的的原则写的比较长，实际可以通过在函数里面加几个特判省去不少码量。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
int n,m,q,a[11][100010],ans[1010],cnt,tx,ty,f[2010],t1,t2,lt[1010][2][11],kj[1010],l,r,res,spj;
const int kc=100,lu[2][2]={{-1,0},{0,-1}};
int ff0(int x){
	if(f[x]==x) return x;
	return f[x]=ff0(f[x]);
}
int gt(int x,int y){
	int ly=y/kc*kc;
	return n*(y-ly)+x;
}
void sk(int l,int r){
	r=min(r,m-1);
	for(int i=1;i<=2000;i++){
		f[i]=i;
	}
	for(int i=1;i<=n;i++){
		for(int j=l;j<=r;j++){
			res++;
			for(int w=0;w<2;w++){
				tx=i+lu[0][w];ty=j+lu[1][w];
				if(!tx) continue;
				if(ty<l) continue;
				if(a[tx][ty]==a[i][j]){
					t1=ff0(gt(tx,ty));t2=ff0(gt(i,j));
					if(t1!=t2){
						f[t2]=t1;res--;
					}
				}
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++){
		for(int j=0;j<m;j++){
			cin>>a[i][j];
		}
	}
	for(int i=0;i*kc<m;i++){
		for(int j=1;j<=n*kc;j++){
			f[j]=j;
		}
		for(int k=1;k<=n;k++){
			for(int j=i*kc;j<(i+1)*kc&&j<m;j++){
				ans[i]++;
				for(int w=0;w<2;w++){
					tx=k+lu[0][w];ty=j+lu[1][w];
					if(!tx) continue;
					if(ty<i*kc) continue;
					if(a[tx][ty]==a[k][j]){
						t1=ff0(gt(tx,ty));t2=ff0(gt(k,j));
						if(t1!=t2){
							f[t2]=t1;ans[i]--;
						}
					}
				}
			}
		}
		for(int k=1;k<=n;k++){
			lt[i][0][k]=ff0(gt(k,i*kc));
			lt[i][1][k]=ff0(gt(k,min(m-1,(i+1)*kc-1)));
		}
	}
	for(int i=1;i*kc<m;i++){
		for(int j=1;j<=2000;j++){
			f[j]=j;
		}
		for(int j=1;j<=n;j++){
			if(a[j][i*kc-1]==a[j][i*kc]){
				t1=ff0(lt[i-1][1][j]);
				t2=ff0(lt[i][0][j]+1000);
				if(t1!=t2){
					f[t1]=t2;
					kj[i]++;
				}
			}
		}
	}
	while(q--){
		cin>>l>>r;
		l--;r--;
		res=0;
		if(r/kc==l/kc){
			sk(l,r);
		}
		else{
			if(l/kc+1==r/kc){
				sk(l,(l/kc+1)*kc-1);
				for(int i=1;i<=n;i++){
					for(int j=r/kc*kc;j<=r;j++){
						res++;
						for(int w=0;w<2;w++){
							tx=i+lu[0][w];ty=j+lu[1][w];
							if(!tx) continue;
							if(ty<r/kc*kc) continue;
							if(a[tx][ty]==a[i][j]){
								t1=ff0(gt(tx,ty)+1000);t2=ff0(gt(i,j)+1000);
								if(t1!=t2){
									f[t2]=t1;res--;
								}
							}
						}
					}
				}
				for(int i=1;i<=n;i++){
					if(a[i][r/kc*kc-1]==a[i][r/kc*kc]){
						t1=ff0(gt(i,r/kc*kc-1));t2=ff0(gt(i,r/kc*kc)+1000);
						if(t1!=t2){
							f[t2]=t1;res--;
						}
					}
				}
			}
			else{
				sk(l,(l/kc+1)*kc-1);
				for(int i=1;i<=n;i++){
					if(a[i][(l/kc+1)*kc-1]==a[i][(l/kc+1)*kc]){
						t1=ff0(gt(i,(l/kc+1)*kc-1));
						t2=ff0(lt[l/kc+1][0][i]+1000);
						if(t1!=t2){
							res--;
							f[t1]=t2;
						} 
					}
				}
				for(int i=l/kc+1;i<r/kc;i++){ 
					if(i!=l/kc+1)
					res-=kj[i];
					res+=ans[i];
				}
				sk(r/kc*kc,r);
				if(r/kc-1!=l/kc)
				for(int i=1;i<=n;i++){
					if(a[i][r/kc*kc-1]==a[i][r/kc*kc]){
						t2=ff0(lt[r/kc-1][1][i]+1000);
						t1=ff0(gt(i,r/kc*kc));
						if(t1!=t2){
							res--;
							f[t1]=t2;
						} 
					}
				}
			}
		}
		cout<<res<<'\n';
	}
	return 0;
}
```

---

## 作者：I_am_Accepted (赞：1)

### Analysis

$n\le 10$，懂了，是一维问题（doge）。

接下来的讲解中所有 $n,m$ 交换一下。

区间询问想到线段树，维护啥呢？

首先是左右端点下标，要知道两边「端口」地形。

再是区间内的连通块数量。

然后就是重点：

```
2 2        2 2
2 1 -link- 1 2
2 2        2 2
```

和

```
2 2        2 2
2 1 -link- 1 1
2 2        2 2
```

接口处相同但连通块个数分别减少 $2,3$。

所以对于线段树每个节点，记录左右两端每个元素所在并查集，这样才能正确 merge。

大概长这样↓

```cpp
friend node operator+(node x,node y){
	node res=(node){x.cnt+y.cnt,x.l,y.r};
	For(i,0,m-1) f[x.L[i]]=x.L[i];
	For(i,0,m-1) f[x.R[i]]=x.R[i];
	For(i,0,m-1) f[y.L[i]]=y.L[i];
	For(i,0,m-1) f[y.R[i]]=y.R[i];
	For(i,0,m-1){
		if(a[x.r][i]!=a[y.l][i] || gf(x.R[i])==gf(y.L[i])) continue;
		res.cnt--;
		f[gf(x.R[i])]=gf(y.L[i]);
	}
	For(i,0,m-1) res.L[i]=gf(x.L[i]);
	For(i,0,m-1) res.R[i]=gf(y.R[i]);
	return res;
}
```

注意这里 `f` 数组是公用的，避免 MLE。

时间 $O(nm-qm\log n)$

### Code

[Link](https://codeforces.com/contest/811/submission/153419979)

```cpp
//Said no more counting dollars. We'll be counting stars.
#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")//DONT use rashly,I have suffered
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")//DONT use rashly,I have suffered
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define mem(x,y) memset(x,y,sizeof(x))
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Rof(i,j,k) for(int i=j;i>=k;i--)
#define Fe(x,y) for(int x=head[y];x;x=e[x].nxt)
#define ckmx(a,b) a=max(a,b)
#define ckmn(a,b) a=min(a,b)
#define fin(s) freopen(s,"r",stdin)
#define fout(s) freopen(s,"w",stdout)
#define file(s) fin(s".in");fout(s".out")
#define cerr cerr<<'_'
#define debug cerr<<"Passed line #"<<__LINE__<<endl
template<typename T>T ov(T x){cerr<<"Value: "<<x<<endl;return x;}
#define ll long long
const ll mod=1000000007;
inline ll pw(ll x,ll y){ll r=1;while(y){if(y&1)r=r*x%mod;x=x*x%mod;y>>=1;}return r;}
inline void mad(ll &a,ll b){a=(a+b)%mod;while(a<0)a+=mod;}
inline void mmu(ll &a,ll b){a=a*b%mod;while(a<0)a+=mod;}
#define inv(a) pw(a,mod-2)
#define int long long
#define N 100010
#define M 10
#define mid ((l+r)>>1)
#define ls (rt<<1)
#define rs (rt<<1|1)
//CF811E
int n,m,q,a[N][M];
int f[N*M];
inline int gf(int x){return x==f[x]?x:f[x]=gf(f[x]);}
inline int num(int x,int y){return (x-1)*m+y+1;}
struct node{
	int cnt,l,r,L[M],R[M];
	void asg(int id){
		l=r=id;
		cnt=1;
		L[0]=R[0]=num(id,0);
		For(i,1,m-1){
			if(a[id][i]==a[id][i-1]) L[i]=R[i]=L[i-1];
			else cnt++,L[i]=R[i]=num(id,i);
		}
	}
	friend node operator+(node x,node y){
		node res=(node){x.cnt+y.cnt,x.l,y.r};
		For(i,0,m-1) f[x.L[i]]=x.L[i];
		For(i,0,m-1) f[x.R[i]]=x.R[i];
		For(i,0,m-1) f[y.L[i]]=y.L[i];
		For(i,0,m-1) f[y.R[i]]=y.R[i];
		For(i,0,m-1){
			if(a[x.r][i]!=a[y.l][i] || gf(x.R[i])==gf(y.L[i])) continue;
			res.cnt--;
			f[gf(x.R[i])]=gf(y.L[i]);
		}
		For(i,0,m-1) res.L[i]=gf(x.L[i]);
		For(i,0,m-1) res.R[i]=gf(y.R[i]);
		return res;
	}
}t[4*N];
void build(int rt,int l,int r){
	if(l==r){
		t[rt].asg(l);
		return ;
	}
	build(ls,l,mid);
	build(rs,mid+1,r);
	t[rt]=t[ls]+t[rs];
}
node que(int rt,int l,int r,int x,int y){
	if(l==x && r==y) return t[rt];
	if(y<=mid) return que(ls,l,mid,x,y);
	if(x>mid) return que(rs,mid+1,r,x,y);
	return que(ls,l,mid,x,mid)+que(rs,mid+1,r,mid+1,y);
}
signed main(){IOS;
	cin>>m>>n>>q;
	For(j,0,m-1)
		For(i,1,n)
			cin>>a[i][j];
	build(1,1,n);
	int l,r;
	while(q--){
		cin>>l>>r;
		cout<<que(1,1,n,l,r).cnt<<endl;
	}
return 0;}
```

---

## 作者：lfxxx (赞：0)

为什么 $n$ 这么小。

考虑平面图欧拉公式：对于一个连通的平面图而言，不算最外面的大面，点减去边加面等于 $1$，故对于一个平面图而言，点减边加面等于连通块数。

数点和边都是二维数点，现在来看怎么处理面，不难发现，一个面一定是一个极小环（只认为相同颜色的点之间有边），怎么找平面图极小环呢？考虑转对偶图后，极小环变成了极大连通块，这个 dfs 求出来就行，然后对于询问的贡献还是一个关于极小环上最左边点和最右边点的二维数点，离线扫描线即可，时间复杂度 $O((n \times m + q) \log m)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxm = 1e5+114;
const int maxn = 14;
int col[maxn][maxm];
int n,m,q;
int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
int bit[maxm];
void add(int u,int v){
    while(u<=m) bit[u]+=v,u+=(u&(-u));
}
int pre(int u){
    int res=0;
    while(u>0) res+=bit[u],u-=(u&(-u));
    return res;
}
vector< pair<int,int> > P[maxm];
int L,R;
int vis[maxn][maxm];
bool line;
int ql[maxm],qr[maxm];
vector<int> Q[maxm];
int ans[maxm];
void dfs(int x,int y){
    L=min(L,y);
    R=max(R,y+1);
    vis[x][y]=1;
    for(int d=0;d<4;d++){
        int nx=x+dx[d],ny=y+dy[d];
        bool flag=false;
        if(d==0){
            if(col[x+1][y]!=col[x+1][y+1]) flag=true;
        }else if(d==1){
            if(col[x][y]!=col[x][y+1]) flag=true;
        }else if(d==2){
            if(col[x][y+1]!=col[x+1][y+1]) flag=true;
        }else{
            if(col[x][y]!=col[x+1][y]) flag=true;
        }
        if(flag==true){
            if(nx<1||nx>=n||ny<1||ny>=m) line=true;
            else if(vis[nx][ny]==0) dfs(nx,ny); 
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) cin>>col[i][j];
    }
    for(int i=1;i<=q;i++){
        cin>>ql[i]>>qr[i];
        Q[ql[i]].push_back(i);
    }
    for(int i=1;i<n;i++){
        for(int j=1;j<m;j++){
            if(vis[i][j]==0){
                L=m+1,R=0;
                line=false;
                dfs(i,j);
                if(line==false) P[L].push_back(make_pair(R,1)); 
            }
        }
    }
    for(int x=1;x<=n;x++){
        for(int y=1;y<=m;y++){
            for(int d=0;d<4;d++){
                int nx=x+dx[d],ny=y+dy[d];
                if(nx>x||ny>y){
                    if(nx<=n&&ny<=m&&col[x][y]==col[nx][ny]){
                        P[min(y,ny)].push_back(make_pair(max(y,ny),-1));
                    }
                }
            }
        }
    }
    for(int l=m;l>=1;l--){
        for(pair<int,int> x:P[l]) add(x.first,x.second);
        for(int id:Q[l]){
            ans[id]=pre(qr[id])+n*(qr[id]-ql[id]+1);
        }
    }
    for(int i=1;i<=q;i++) cout<<ans[i]<<'\n';
    return 0;
}
```

---

## 作者：QuakeHearts (赞：0)

### Step 1 题意
在一个 $n \times m$ 的网格上每个格子都有颜色，$q$ 次询问，每次询问只保留 $l$ 至 $r$ 列时有多少个四连通的颜色块。两个格子同色但不连通算在不同的颜色块内。

### Step 2 分析
这道题我首先大力找到一个错误规律，这个暂且不说，直接上正解。

对于每一列的格子搞线段树，记录每列有几个连通块，每列的最左侧和最右侧的节点属于哪个连通块。

合并的时候合并两个连通块相邻的两列，如果颜色一致并且 $fa$ 不一样，总连通块的数量减一。不过需要初始化一下相邻两列格子的并查集。

### Step 3 代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=1e5+10;
int n,m,q,mapi[15][N],fa[N*15];
int tot;
struct node{
	int x,y,L[15],R[15],sum;
}t[N<<4];

inline int read(){
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch<='9'&&ch>='0'){
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*w;
}
inline int find(int x){
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
inline node update(node x,node y,int l,int r){
	node ans;
	ans.sum=x.sum+y.sum;
	for(int i=1;i<=n;i++)
	fa[x.L[i]]=x.L[i],fa[x.R[i]]=x.R[i],
	fa[y.L[i]]=y.L[i],fa[y.R[i]]=y.R[i];
	for(int i=1;i<=n;i++)ans.L[i]=x.L[i],ans.R[i]=y.R[i];
	for(int i=1;i<=n;i++)
	if(mapi[i][l]==mapi[i][r]){
		int xi=find(fa[x.R[i]]);
		int yi=find(fa[y.L[i]]);
		if(xi!=yi)fa[xi]=yi,--ans.sum;
	}
	for(int i=1;i<=n;i++)
	ans.L[i]=find(ans.L[i]),ans.R[i]=find(ans.R[i]);
	return ans;
}
inline void build(int x,int l,int r){
	if(l==r){
		for(int i=1;i<=n;i++)
		if(mapi[i][l]==mapi[i-1][l])
		t[x].L[i]=t[x].R[i]=t[x].L[i-1];
		else t[x].L[i]=t[x].R[i]=++tot,++t[x].sum;
		return ;
	}
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	t[x]=update(t[x<<1],t[x<<1|1],mid,mid+1);
}
inline node query(int x,int l,int r,int L,int R){
	if(l>=L&&r<=R)return t[x];
	int mid=(l+r)>>1;
	int flaga=0,flagb=0;
	node a,b,ans;
	if(L<=mid)a=query(x<<1,l,mid,L,R),flaga=1;
	if(R>mid)b=query(x<<1|1,mid+1,r,L,R),flagb=1;
	if(flaga&&!flagb)ans=a;
	else if(flagb&&!flaga)ans=b;
	else if(flaga&&flagb)ans=update(a,b,mid,mid+1);
	return ans;
}

signed main(){
	n=read();m=read();q=read();
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)mapi[i][j]=read();
	//cout<<"Case 1 "<<endl;
	build(1,1,m);
	//cout<<"Case 2 "<<endl;
	for(int i=1;i<=q;i++){
		int u,v;
		u=read();v=read();
		node fin=query(1,1,m,u,v);
		cout<<fin.sum<<endl; 
	}
	return 0;
}
//不要抄代码/nk
```

---

## 作者：daniEl_lElE (赞：0)

考虑线段树，要记录什么。

我们正常情况下需要知道所有点所处的并查集编号。然而目前我们已经知道一个区间的连通块数，合并的时候只需要知道最左一列和最右一列的编号。于是只需要记录 $20$ 个位置的所处并查集编号即可。

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2,3,"Ofast","inline")
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
int n,m,q;
int a[11][100005];
struct node{
	int f[21],l,r,cnt;
};
int fa[41],rem[41];
node pre[100005];
int find(int i){
	return fa[i]==i?fa[i]:fa[i]=find(fa[i]);
}
node merge(node x,node y){
	node z; z.l=x.l,z.r=y.r,z.cnt=x.cnt+y.cnt;
	for(int i=1;i<=4*n;i++) fa[i]=i,rem[i]=0;
	for(int i=1;i<=2*n;i++) y.f[i]+=2*n;
	for(int i=1;i<=n;i++){
		if(a[i][x.r]==a[i][y.l]){
			int X=find(x.f[i+n]),Y=find(y.f[i]);
			if(X!=Y) fa[X]=Y,z.cnt--;
		}
	}
	int cnt=0;
	for(int i=1;i<=n;i++){
		int P;
		P=find(x.f[i]);
		if(!rem[P]) rem[P]=++cnt;
		z.f[i]=rem[P];
		P=find(y.f[i+n]);
		if(!rem[P]) rem[P]=++cnt;
		z.f[i+n]=rem[P];
	}
	return z;
}
struct sgt{
	node f[400005];
	void build(int i,int l,int r){
		if(l==r){
			f[i]=pre[l];
			return ;
		}
		build(i*2,l,mid),build(i*2+1,mid+1,r);
		f[i]=merge(f[i*2],f[i*2+1]);
	}
	node qry(int i,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return f[i];
		if(qr<=mid) return qry(i*2,l,mid,ql,qr);
		if(ql>mid) return qry(i*2+1,mid+1,r,ql,qr);
		return merge(qry(i*2,l,mid,ql,qr),qry(i*2+1,mid+1,r,ql,qr));
	}
}tree;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>a[i][j];
	for(int j=1;j<=m;j++){
		pre[j].l=pre[j].r=j;
		for(int i=1;i<=n;i++) pre[j].f[i]=pre[j].f[i+n]=(a[i][j]==a[i-1][j])?pre[j].f[i-1]:pre[j].f[i-1]+1;
		pre[j].cnt=pre[j].f[n];
	}
	tree.build(1,1,m);
	while(q--){
		int l,r; cin>>l>>r;
		cout<<tree.qry(1,1,m,l,r).cnt<<"\n";
	}
	return 0;
}

```

---

