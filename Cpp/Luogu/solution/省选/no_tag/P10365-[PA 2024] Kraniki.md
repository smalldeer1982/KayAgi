# [PA 2024] Kraniki

## 题目背景

PA 2024 5B2

## 题目描述

**题目译自 [PA 2024](https://sio2.mimuw.edu.pl/c/pa-2024-1/dashboard/) Runda 5 [Kraniki](https://sio2.mimuw.edu.pl/c/pa-2024-1/p/kra/)**

*Radek and Friends* 公司的负责人 Radek 试图淹没竞争对手 *Mati and Company* 公司的所有货架。为了进行完美的破坏，他让他的朋友，水管工 Janusz 在每个架子都上安装了小水龙头。

为简单起见，*Mati and Company* 公司中的货架可以用平面上的线段来表示。每个货架都是一对点 $(l_i,h_i)$ 和 $(r_i,h_i)$ 之间的线段。水管工安装的水龙头是坐标为 $(\frac{l_i+r_i}{2}, h_i + 0.5)$ 的点。这个房间的地面用 $OX$ 轴表示。

只要打开第 $i$ 个货架上方的水龙头，该货架就会被水淹没。之后水会自然开始从货架的两端垂直向下滴落，并有可能淹没更多的货架，或自然滴落到地面上。

![](https://cdn.luogu.com.cn/upload/image_hosting/uwllkpr7.png)

在第二组样例中，当打开一个水龙头时，水流的可视化效果.

Radek 会按某个确定的顺序看水龙头的情况。当他看到第 $i$ 个水龙头时，当且仅当第 $i$ 个货架没被水淹，他才会打开这个水龙头。

Radek 还没确定他看水龙头的顺序。它会从 $n!$ 种顺序中均匀随机选择一种。Radek 想知道他平均会打开多少个水龙头。

你的任务是回答 Radek 的问题，给出答案对 $10^9+7$ 取模后的值。形式化地，令答案为 $\frac{p}{q}$，其中 $q\neq 0$ 且 $\gcd(p,q)=1$。你需要输出 $p\cdot q^{-1}\pmod{10^9+7}$，其中 $q^{-1}$ 是集合 $1,2,\ldots,10^9+6$ 中唯一满足 $q\cdot q^{-1}\equiv 1\pmod{10^9+7}$ 的整数。

可以证明对于所有满足题目条件的数据，结果是有理数，且分母不会被 $10^9+7$ 整除。

## 说明/提示

**样例解释 1**

让我们考虑在第一个样例中 Radek 看水龙头的所有顺序：

- 按 $1,2,3$ 的顺序，他会打开所有 $3$ 个水龙头。
- 按 $1,3,2$ 的顺序，他会先打开水龙头 $1$ 和 $3$。当他准备打开水龙头 $2$ 时，水已经淹了第 $2$ 个货架，所以他不需要打开水龙头 $2$ 了。
- 按 $2,1,3$ 的顺序，他会打开所有 $3$​ 个水龙头。
- 按 $2,3,1$ 的顺序，他会先打开水龙头 $2$ 和 $3$。当他准备打开水龙头 $1$ 时，水已经淹了第 $1$ 个货架，所以他不需要打开水龙头 $1$ 了。
- 按 $3,1,2$ 或 $3,2,1$ 的顺序，由于打开水龙头 $3$ 后，所有货架都会被淹，因此就不需要再打开剩下的两个水龙头了。

Radek 平均需要打开 $\frac{1}{6}\cdot(3+2+3+2+1+1)=2$ 个水龙头。

**样例解释 2**

第二组样例中 Radek 平均要打开 $\frac{91}{30}$ 个水龙头，由于 $30^{-1}\equiv 233333335\pmod{10^9+7}$，所以输出 $91\cdot 233333335\equiv 21233333485\equiv 233333338\pmod{10^9+7}$。

## 样例 #1

### 输入

```
3
4 6
1 3
2 5
```

### 输出

```
2```

## 样例 #2

### 输入

```
5
2 9
3 4
1 8
6 10
5 7
```

### 输出

```
233333338
```

# 题解

## 作者：int08 (赞：3)

## 前言

我们一场模拟赛的题，结果原题是新鲜出炉的。

小弟不才，感觉这题是做过的题中几乎最复杂的了。

既然搞懂了，就来写一发题解吧。

（题外话：目前最优解，我的常数真是小小又大大啊）

 _"Up and down,glowin' round..."_ 

# Solution

### 1、一个经典的 Trick

直接模拟每一种情况显然不可取，考虑计算每一条的贡献。

假设对于第 $i$ 条，一共有 $x_i$ 条线段能在开了水龙头后流到它（包括它自己，故 $x_i \ge 1$）。

那么容易发现，这个位置的水龙头要打开，当且仅当它是这 $x_i$ 条中排第一个的。

这个概率在全排列下为 $\frac{1}{x_i}$，容易发现其他的线段对这一条贡献无影响，故答案为 $\sum_{i=1}^{n}x_i$。

现在我们只需要求出每一条能被多少条流到即可。

### 2、模拟运行，得出结论

首先按照高度从小到大排序。（本题中已经排好）

发现第 $i$ 条（之后记为 $a_i$）可以**直接**流到 $a_j$（$i>j$）的条件是如下之一：

1. $a_i$ 左右完全在 $a_j$ 中间。

2. $a_i$ 覆盖了 $a_j$ 的某一个端点。（**下文将这种情况称 $a_i$ 为 $a_j$ 的左/右祖先**）

但本题可不止直接流，间接流到（$a_i$ 流 $a_j$，$a_j$ 流 $a_k$）这种也算。

经过想象和模拟，我们可以猜测能流到它的区域的两端大概是不断从左/右祖先一次一次流下来，而中间的部分都可以。

但是还有一种情况，如果 $a_i$ 完全覆盖 $a_j$ 以及它的所有左右祖先，那么 $a_i$ 上面的所有线段都**不可能**流到 $a_j$ 了，我们可以称 $a_i$ 支配 $a_j$。

于是能流到的部分就是它不断向左右祖先去，直到被支配它的线段挡住为止。

如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/ux7s5f8j.png)

现在依次出现四个问题在我们面前，下文一一解释。

 _"...I saw somehow you know..."_ 
### 3、解决四个问题

#### 找到每条线段的左右祖先

由于一条线段左祖先是覆盖它的左端点的线段中高度最低（且大于它本身）的，于是从大到小扫描并使用**线段树**区间推平单点查询，这是简单的。

#### 计算阴影内的线段个数

阴影部分看似是不规则的，但是我们可以用前缀相减的方式。

就像这样：
![](https://cdn.luogu.com.cn/upload/image_hosting/jhj4cj5e.png)

答案就是所有向右祖先跳的前缀减去所有向左祖先跳的前缀。

现在只需计算每个线段向它的祖先跳的这个 $\text{3-side}$ 内的线段个数，等价于数右端点个数。

经典**二维数点**，扫描线配合树状数组搞定。

#### 找到支配线段

为了使得每条线段都有支配线段，我们在最顶上加一条最大的线段，但是这并不影响下面的答案。

现在每条线段都被它上面的某一条支配，这形成了一棵树。

而每条线段的支配线段，就是它的左右祖先**在支配树上的 $\text{LCA}$**。

理由：要支配它得同时支配它的左右祖先，而且它左右祖先的所有祖先显然就是它的所有祖先。

而 $\text{LCA}$ 可以使用**倍增**解决，倍增也支持动态加点，无敌了。

#### 将计算答案和找到支配线段合并

很显然你可以在计算 $\text{LCA}$ 时**带权**，但不只是带上本身答案这么简单。

因为左右端点的答案可能重叠。

所以对于每个点，我们应该分别记录它到支配点的左右轮廓对应的前缀和，这样合并方便，相减得出答案也不会算重。

事实上，以上内容说着简单，严谨性却有缺失，大家可以自己再思考，再证明，作为对这道题目的再利用。

## AC code

代码有些难写，这题真的只有紫吗……

 _"...I might get down,you might not drown..."_ 
 
 _"...You might just fly away."_ 

```cpp
#include<bits/stdc++.h>
#define N 508032
#define mod 1000000007
using namespace std;
long long qp(long long x,long long y)
{
	long long ans=1;
	for(long long i=1,j=x;i<=y;i*=2,j=j*j%mod) if(i&y) ans=ans*j%mod;
	return ans;
}
//bit
int bit[2*N],n;
void change(int x,int y)
{
	for(;x<=2*n;x+=x&-x) bit[x]+=y;
}
int ask(int x)
{
	int ans=0;
	for(;x;x-=x&-x) ans+=bit[x];
	return ans;
}
//sgt
struct tree{
	int l,r,ans;
}sgt[8*N];
#define mid ((sgt[o].l+sgt[o].r)>>1)
#define ls (o*2)
#define rs (o*2+1)
void build(int l,int r,int o)
{
	sgt[o].l=l,sgt[o].r=r;
	if(l==r) return;
	build(l,mid,ls);
	build(mid+1,r,rs);
}
void pushdown(int o)
{
	if(sgt[o].ans&&sgt[o].l!=sgt[o].r)
	{
		sgt[ls].ans=sgt[rs].ans=sgt[o].ans;
		sgt[o].ans=0;
	}
}
void change(int l,int r,int v,int o)
{
	pushdown(o);
	if(sgt[o].l>=l&&sgt[o].r<=r)
	{
		sgt[o].ans=v;
		return;
	}
	if(l<=mid) change(l,r,v,ls);
	if(r>mid) change(l,r,v,rs);
}
int ask(int x,int o)
{
	pushdown(o);
	if(sgt[o].l==sgt[o].r) return sgt[o].ans;
	if(x<=mid) return ask(x,ls);
	else return ask(x,rs);
}
//LCA
struct Lca{
	int lc,la,ra;
};
int d[N];
Lca p[N][23];
Lca lca(int a,int b)
{
	int lans=0,rans=0;
	for(int i=21;i>=0;i--)
		if(d[a]<=d[b]-(1<<i))
			rans+=p[b][i].ra,b=p[b][i].lc;
	for(int i=21;i>=0;i--)
		if(d[b]<=d[a]-(1<<i))
			lans+=p[a][i].la,a=p[a][i].lc;
	if(a==b) return {a,lans,rans};
	for(int i=21;i>=0;i--)
	{
		if(p[a][i].lc==p[b][i].lc) continue;
		else lans+=p[a][i].la,rans+=p[b][i].ra,a=p[a][i].lc,b=p[b][i].lc; 
	}
	return {p[a][0].lc,lans+p[a][0].la,rans+p[b][0].ra};
}
//segment
int l[N],r[N],bel[2*N],i,j,val[N];
int lf[N],rf[N],lv[N],rv[N];
struct smx{
	int id,x,k;
};
inline int read()
{
	int ret=0;
	char ch=getchar();
	while(!isdigit(ch))
		ch=getchar();
	while(isdigit(ch))
		ret=(ret<<3)+(ret<<1)+(ch^48),ch=getchar();
	return ret;
}
vector<smx> s[N];
signed main()
{
	n=read();
	for(i=1;i<=n;i++) l[i]=read(),r[i]=read(),bel[++l[i]]=bel[++r[i]]=i;
	n++;l[n]=1,r[n]=2*n;bel[l[n]]=bel[r[n]]=n;
	build(1,2*n,1),change(1,2*n,n,1);
	for(i=n-1;i>=1;i--)
		lf[i]=ask(l[i],1),rf[i]=ask(r[i],1),change(l[i],r[i],i,1),
		s[lf[i]].push_back({0,l[i],-1}),s[i].push_back({0,l[i],1}),
		s[rf[i]].push_back({1,r[i],-1}),s[i].push_back({1,r[i],1});
	for(i=n;i>=1;i--)
	{
		change(r[i],1);
		for(auto v:s[i])
		if(!v.id) lv[bel[v.x]]+=v.k*ask(v.x);
		else rv[bel[v.x]]+=v.k*ask(v.x);
	}
	for(i=n-1;i>=1;i--)
	{
		Lca repair=lca(lf[i],rf[i]);
		int fa=repair.lc;
		val[i]=repair.ra-repair.la-lv[i]+rv[i];
		d[i]=d[fa]+1;
		p[i][0]={fa,repair.la+lv[i],repair.ra+rv[i]};
		for(j=1;(1<<j)<=d[i];j++) p[i][j]={p[p[i][j-1].lc][j-1].lc,p[p[i][j-1].lc][j-1].la+p[i][j-1].la,p[p[i][j-1].lc][j-1].ra+p[i][j-1].ra};
	}
	long long ans=0;
	for(i=1;i<=n-1;i++) (ans+=qp(val[i],mod-2))%=mod;
	cout<<ans;
	return 0;
}
```

# The End.

---

## 作者：小超手123 (赞：2)

##### 分析：

记 $cnt_{i}$ 表示能到达 $i$ 的平台的个数（包括本身），那么答案显然为 $\sum_{i=1}^{n} \frac{1}{cnt_{i}}$。因为 $cnt_{i}$ 个数随意排列，$i$ 在最后一个位置的概率为 $\frac{cnt_{i}}{1}$。

考虑计算 $cnt$：对于平台 $u$ 而言，高度从低往高更新，如果 $v$ 与 $u$ 有交且不是 $v$ 包含 $u$，那么 $u \leftarrow u \cup v$。最后 $cnt$ 就是被 $u$ 覆盖的区间。

记 $L2_{i},R2_{i}$ 分别表示覆盖 $i$ 的左右端点的在 $i$ 平台上面的高度最低的平台。

如何找天花板呢？记 $L1_{i},R1_{i}$ 分别表示 $i$ 平台的左右端点能覆盖到的在 $i$ 下面高度最高的平台。

再记一个 $Go_{i}$ 表示 $i$ 能跳到最高的平台，那么 $i$ 从大到小枚举，$Go_{L1_{i}} \leftarrow Go_{i},Go_{R1_{i}} \leftarrow Go_{i}$。

$Go_{i}$ 通过 $L2_{i}$ 往上跳一步就是平台。

![](https://pic.imgdb.cn/item/660393ed9f345e8d036475dd.png)

知道了平台的高度就可以很套路地使用倍增计算这个图形所围成的平台的个数。

时间复杂度 $O(n \log n)$。

##### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 1000005
#define mod 1000000007
using namespace std;
int n;
int Pow(int a, int n) {
	if(n == 0) return 1;
	if(n == 1) return a;
	int x = Pow(a, n / 2);
	if(n % 2 == 0) return x * x % mod;
	else return x * x % mod * a % mod;
}
int inv(int x) {
	return Pow(x, mod - 2);
}
int c[N * 4], tag[N * 4];
void maketag(int u, int x) {
	c[u] = x;
	tag[u] = x;
}
void pushdown(int u) {
	if(!tag[u]) return;
	maketag(u * 2, tag[u]);
	maketag(u * 2 + 1, tag[u]);
	tag[u] = 0;
}
void update(int u, int L, int R, int l, int r, int x) {
	if(R < l || r < L) return;
	if(l <= L && R <= r) {
		maketag(u, x);
		return;
	}
	int mid = (L + R) / 2;
	pushdown(u);
	update(u * 2, L, mid, l, r, x);
	update(u * 2 + 1, mid + 1, R, l, r, x);
}
int query(int u, int L, int R, int x) {
	if(L == R) return c[u];
	int mid = (L + R) / 2;
	pushdown(u);
	if(x <= mid) return query(u * 2, L, mid, x);
	else return query(u * 2 + 1, mid + 1, R, x);
}
int t[N];
int lowbit(int x) {
	return x & (-x);
}
void add(int x, int y) {
	for(int i = x; i <= 2 * n; i += lowbit(i)) 
		t[i] += y;
}
int query(int x) {
	int res = 0;
	for(int i = x; i; i -= lowbit(i))
		res += t[i];
	return res;
}
int ask(int L, int R) {
	if(L > R) return 0;
	return query(R) - query(L - 1);
}
int ans, l[N], r[N], Go[N]; //Go[i]表示i最高跳到的平台
int L1[N], R1[N]; //表示i能直接流到的高度最大的平台
int L2[N], R2[N]; //表示i头上与它有交集的高度最低的平台
int L[N][22], R[N][22], SL[N][22], SR[N][22];
struct node {
	int ll, rr, h;
}a[N];
bool cmp(node x, node y) {
	return x.rr < y.rr;
}
bool cmp2(node x, node y) {
	return x.ll < y.ll;
}
void init() {
	for(int i = 1; i <= n; i++) {
		L1[i] = query(1, 1, 2 * n, l[i]);
		R1[i] = query(1, 1, 2 * n, r[i]);
		update(1, 1, 2 * n, l[i], r[i], i);
	}
	for(int i = n; i >= 1; i--) {
		Go[L1[i]] = max(Go[L1[i]], Go[i]);
		Go[R1[i]] = max(Go[R1[i]], Go[i]);			
	}
	update(1, 1, 2 * n, 1, 2 * n, n + 1);
	for(int i = n; i >= 1; i--) {
		L[i][0] = L2[i] = query(1, 1, 2 * n, l[i]);
		R[i][0] = R2[i] = query(1, 1, 2 * n, r[i]);
		update(1, 1, 2 * n, l[i], r[i], i);
		//cout << i << " : " << L[i][0] << " , " << R[i][0] << endl;
	}
	sort(a + 1, a + n + 1, cmp);
	for(int i = 1; i <= n; i++) {
		//cout << a[i].h << endl;
		add(a[i].h, 1);
		SR[a[i].h][0] = ask(a[i].h, R[a[i].h][0]);
	}
	
	sort(a + 1, a + n + 1, cmp2);
	memset(t, 0, sizeof(t));
	for(int i = 1; i <= n; i++) {
		add(a[i].h, 1);
		SL[a[i].h][0] = ask(a[i].h + 1, L[a[i].h][0] - 1);
	}
	//for(int i = 1; i <= n; i++) cout << i << " : " << SL[i][0] << endl;
}
signed main() {
	//freopen("ex_water3.in", "r", stdin);
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> l[i] >> r[i];
		Go[i] = i;
		a[i].ll = l[i];
		a[i].rr = r[i];
		a[i].h = i;
	} 
	init();
	for(int j = 1; j <= 20; j++) {
		for(int i = 1; i <= n; i++) {
			L[i][j] = L[L[i][j - 1]][j - 1];
			R[i][j] = R[R[i][j - 1]][j - 1];
			SL[i][j] = SL[i][j - 1] + SL[L[i][j - 1]][j - 1];
			SR[i][j] = SR[i][j - 1] + SR[R[i][j - 1]][j - 1];
		}
	}
	for(int i = 1; i <= n; i++) {
		int cnt = 0, x = i;
		for(int dep = 20; dep >= 0; dep--) {
			if(R[x][dep] != 0 && R[x][dep] <= L[Go[i]][0]) {
				cnt += SR[x][dep];
				x = R[x][dep];
			}
		}
		x = i;
		for(int dep = 20; dep >= 0; dep--) {
			if(L[x][dep] != 0 && L[x][dep] <= L[Go[i]][0]) {
				cnt -= SL[x][dep];
				x = L[x][dep];
			}
		}
		ans = (ans + inv(cnt)) % mod;
	}
	cout << ans;
	return 0;
}
/*
5
2 9
3 4
1 8
6 10
5 7
*/
```

---

## 作者：nullqtr_pwp (赞：1)

由期望的线性性，可以将每个位置拆开来算，考虑有 $f_i$ 个点放水会流到 $i$，那么 $i$ 需要打开当且仅当，在打开的顺序中，它比这些 $f_i$ 个点都靠前，所以有 $\dfrac{1}{f_i}$ 的概率打开。显而易见，每个位置求和，答案就是 $\sum_{i=1}^n \dfrac{1}{f_i}$。

考虑求 $f_i$。考虑写成有向图的形式，$i$ 的连边最多有两条：往左边流第一个流到的，往右边流第一个流到的。如果有重复则需要只保留一条。找两端的后继，可以直接线段树实现。

建出来之后，$f_i$ 就是在这张图上可以抵达 $i$ 的点的个数。考虑到 $n$ 是无入度点，所以可以从 $n$ 开始自顶往下 dp，初始就是 $f_i=1$，因为是有它自己。转移显然有往后继 $v_l,v_r$ 都加上 $f_u$。如果有两个后继，需要在它们第一次共同流到的位置减去 $f_u$，不然会出现重复。

怎么找第一次共同流到的位置呢？其实就是支配树上 $v_l,v_r$ 的 $\text{LCA}$。我写的做法是，直接二分这个位置 $k$，**分别**倍增左右链跳到第一个 $k$ 之上的点，判定是否有当前位置在目标位置之下，看一下是否满足 $R_{u'}>L_{v'}$。（$L_i,R_i$ 是输入给定的线段），关于这个式子的解释：如果没有交点，它不会成立。正是因为有了这个交点，才导致，右侧尽量往左的水流的位置 $<$ 左侧尽量往右的水流。它们第一次相交就是在目标位置。

时间复杂度 $O(n\log^2n)$。[提交记录。](https://loj.ac/s/2051136)

---

## 作者：Larunatrecy (赞：1)

若货架 $i$ 的水可以一步流到货架 $j$，就从 $i$ 向 $j$ 连一条边，这样形成了一个 DAG，设其中可以到达点 $i$ 的点的个数为 $s_i$，那么根据期望的线性性可知答案为 $\sum_{i}\frac{1}{s_i}$。

问题就变成求 $s_i$，一般的图上只能用 `bitset` 做到 $O(\frac{n^2}{w})$，我们要利用这个图的特殊性。

考虑一种从低到高的过程，实时维护现在可以流到货架 $i$ 的水的位置构成的区间 $E_i$，从低到高扫描，加入区间 $i$ 时，对于 $j<i$ 的 $E_j$：

- 若 $l_i\in E_j \vee r_i\in E_j$，$E_j\cup [l_i,r_i]\to E_j$。
- 若 $E_j\subset [l_i,r_i]$，那么删除 $E_j$。

可以发现这是一个 $[l_j,r_j]$ 不断向左右拓展，直到被一个货架完全挡住的过程，并且可以流到 $j$ 的货架构成了一个 **阶梯状** 的形态，我们分成两部分求：

- 求出最高的可以流到 $i$ 的货架 $fa_i$，这个只需要从高到低扫描，用 `set` 维护当前还存在的端点，每次就是删掉 $[l_i,r_i]$ 中的端点，并把 $fa_i$ 对这些端点所属货架的 $fa_j$ 取 $\max$，然后加入端点 $l_i,r_i$。
- 求出阶梯状内的货架个数，首先从低到高扫描求出 $lfa_i,rfa_i$ 表示 $l_i,r_i$ 上方的第一个货架，这个可以类似上面过程用 `set` 维护，然后可以发现此时左端点和右端点的拓展是独立的，以左端点为例，我们不断跳 $lfa_i$，然后加上 $j\geq lfa_i,l_j\in [l_{lfa_i},l_i-1]$ 的 $j$ 个数，整个跳的过程就是倍增跳到 $fa_i$ 然后统计中间的贡献和，最后要扣除 $fa_i$ 更高的货架的贡献，都可以用主席树维护。

复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5e5+7;
template <typename T>inline void read(T &x)
{
    x=0;char c=getchar();bool f=0;
    for(;c<'0'||c>'9';c=getchar())f|=(c=='-');
    for(;c>='0'&&c<='9';c=getchar())x=((x<<1)+(x<<3)+(c^48));
    x=(f?-x:x);
}
typedef long long LL;
int n;
int l[N],r[N],lfa[N],rfa[N];
int up[N*2];
set<int> st;
int rot[N];
const int M = 2e7+7;
int lson[M],rson[M],num[M],idx=0;
int ins(int lst,int l,int r,int x)
{
    int k=++idx;
    lson[k]=lson[lst];
    rson[k]=rson[lst];
    num[k]=num[lst]+1;
    if(l==r)return k;
    int mid=(l+r)>>1;
    if(x<=mid)lson[k]=ins(lson[lst],l,mid,x);
    else rson[k]=ins(rson[lst],mid+1,r,x);
    return k;
}
int qry(int k,int l,int r,int L,int R)
{
    if(!k)return 0;
    if(L<=l&&r<=R)return num[k];
    int mid=(l+r)>>1,res=0;
    if(L<=mid)res+=qry(lson[k],l,mid,L,R);
    if(R>mid)res+=qry(rson[k],mid+1,r,L,R);
    return res;
}
int jumpl[N][20],jumpr[N][20];
int linel[N][20],liner[N][20];
int inv[N];
const int mod = 1e9+7;
int main()
{
    read(n);
    for(int i=1;i<=n;i++)read(l[i]),read(r[i]);
    for(int i=1;i<=n;i++)
    {
        auto itl=st.lower_bound(l[i]);
        auto itr=st.lower_bound(r[i]);
        for(;itl!=itr;)
        {
            int p=(*itl);
            int j=up[p];
            if(p==l[j])lfa[j]=i;
            else rfa[j]=i;
            itl++;
            st.erase(p);
        }
        st.insert(l[i]);up[l[i]]=i;
        st.insert(r[i]);up[r[i]]=i;
    }
    inv[1]=1;
    for(int i=2;i<=n;i++)inv[i]=1ll*inv[mod%i]*(mod-mod/i)%mod;
    st.clear();
    int ans=0;
    for(int i=n;i>=1;i--)
    {
        if(!lfa[i])lfa[i]=i;
        if(!rfa[i])rfa[i]=i;
        auto itl=st.lower_bound(l[i]);
        auto itr=st.lower_bound(r[i]);
        int fa=i;
        for(;itl!=itr;)
        {
            int p=(*itl);
            fa=max(fa,up[p]);
            itl++;
            st.erase(p);
        }
        st.insert(l[i]);up[l[i]]=fa;
        st.insert(r[i]);up[r[i]]=fa;
        rot[i]=ins(rot[i+1],1,2*n,l[i]);
        jumpl[i][0]=lfa[i];if(lfa[i]!=i)linel[i][0]=qry(rot[lfa[i]],1,2*n,l[lfa[i]],l[i]-1);
        jumpr[i][0]=rfa[i];if(rfa[i]!=i)liner[i][0]=qry(rot[rfa[i]],1,2*n,r[i]+1,r[rfa[i]]);
        for(int k=1;k<=19;k++)
        {
            int j=jumpl[i][k-1];
            jumpl[i][k]=jumpl[j][k-1];linel[i][k]=linel[i][k-1]+linel[j][k-1];
            j=jumpr[i][k-1];
            jumpr[i][k]=jumpr[j][k-1];liner[i][k]=liner[i][k-1]+liner[j][k-1];
        }
        int lx=i,rx=i;
        int res=0;
        for(int k=19;k>=0;k--)
        {
            if(jumpl[lx][k]!=lx&&jumpl[lx][k]<=fa)
            {
                res+=linel[lx][k];
                lx=jumpl[lx][k];
            }
            if(jumpr[rx][k]!=rx&&jumpr[rx][k]<=fa)
            {
                res+=liner[rx][k];
                rx=jumpr[rx][k];
            }
        }
        res+=qry(rot[i],1,2*n,l[i],r[i]);
        res-=qry(rot[fa+1],1,2*n,l[lx],r[rx]);
        ans=(ans+inv[res])%mod;
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：phil071128 (赞：0)

**笨蛋DAG支配树题解**

PS：本题被搬题人改了个模数后搬在了 2024 沙东一轮省集 Day1 中。
> 平面上有 $n$ 条线段，高度和左右端点两两不同，主动激活一个点后，会激活左端点正下方的线段和右端点正下方的线段（相当于水流），而且会一直激活下去。每次从未激活的线段中随机选择一个线段激活，问激活所有线段需要的主动激活次数的期望是多少。$n\le10^5$。

类似的，带着“在未流水的中选择一个”实际上不好处理。可以转换为：考虑这样的情况，但是不计算贡献。两者是等价的。因此操作序列便是一个 $1\sim n$ 的排列，一个点不被计算贡献当且仅当在排列中有其祖先，设祖先个数为 $f(i)$，根据期望的线性性只需要考虑这 $f(i)+1$ 个数。总排列是 $(f(i)+1)!$，其中有贡献的是 $f(i)!$，且贡献为 $1$，答案为 $\sum \frac{1}{f(i)}$。

需要做快速计算 $f(i)$，即一个点在 DAG 上祖先个数。考虑支配树，定义一个点 $v$ 是点 $u$ 的支配点，需要满足 $u$ 到 $rt$ 的所有路径中均经过 $v$。构造一颗支配树，需要满足 $u$ 在树上的祖先都是 $u$ 的支配点。

在本题中，按照高度递减建图，用线段树区间覆盖进行维护。具体的，分别维护 $u$ 从左端点**往上走**，能到达的点和从右端点走的情况。显然这样会形成两个树形结构。

此时，$u$ 的支配点就是完全覆盖 $u$，且在它上面的点不可能再到达 $u$，在 $dom[u]$ 到 $u$ 这段区间内，维护左链上每个点，完全在它左边减一的，且高度在它和它父亲之间的线段数量 $vL$，以及右链上每个点，完全在它左边的，且高度在它到它父亲之间的线段数量 $vR$。形成前缀和的形式，答案就是 $\sum_i^{dom[i]}vR[i]-vL[i]$，因为支配树同时还要动态维护 LCA，所以统一倍增即可。注意要实现三个数据结构。



```cpp
#include <bits/stdc++.h>
#define int long long
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
//const int N=1e5+500;
inline int read() {
	char c=getchar();int h=0,tag=1;
	while(!isdigit(c)) tag=(c=='-'?-1:1),c=getchar();
	while(isdigit(c)) h=(h<<1)+(h<<3)+(c^48),c=getchar();
	return h*tag;
}
void fil() {
	freopen("P2597_4.in","r",stdin); 
	freopen("tap.out","w",stdout);
}
const int N=1e6+5;int res[N];
struct seg{
	#define ls(x) (x<<1)
	#define rs(x) (x<<1|1)
	#define mid (l+r>>1) 
	int t[N*4];
	seg() { memset(t,-1,sizeof t); }
	void push_down(int p) {
		if(t[p]!=-1) t[ls(p)]=t[rs(p)]=t[p],t[p]=-1;
	}
	void update(int p,int l,int r,int nl,int nr,int k) {
		if(nl<=l&&r<=nr) {
			return t[p]=k,void();
		}
		push_down(p); 
		if(nl<=mid) update(ls(p),l,mid,nl,nr,k);
		if(mid<nr) update(rs(p),mid+1,r,nl,nr,k);
	}
	int query(int p,int l,int r,int x) {
		if(l==r) return t[p];
		push_down(p);
		if(x<=mid) return query(ls(p),l,mid,x);
		else return query(rs(p),mid+1,r,x); 
	}
}t;
int n;
struct Bit{
	#define lowbit(x) (x&-x)
	int t[N];
	void upd(int x,int k) {
		while(x<=2*n) t[x]+=k,x+=lowbit(x); 
	} 
	int qry(int x) {
		int res=0;
		while(x) res+=t[x],x-=lowbit(x);
		return res;
	}
}bit;
const ll mod=1e9+7;

struct tree{
	int fa[N][21],dep[N],siz[N];
	vector<int>s[N];
	void insert(int x,int _fa) {
		dep[x]=dep[_fa]+1;fa[x][0]=_fa;
		for(int i=1;i<20;i++) fa[x][i]=fa[fa[x][i-1]][i-1];
		s[_fa].push_back(x);s[x].push_back(_fa);
	}
	int lca(int x,int y) {
		if(dep[x]<dep[y]) swap(x,y); 
		int k=dep[x]-dep[y];
		for(int i=19;i>=0;i--) if(k>=(1<<i)) x=fa[x][i],k-=(1<<i);
		if(x==y) return x;
		for(int i=19;i>=0;i--) if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
		return fa[x][0];
	}
	int v[N],sum[N][20];
	void upd(int x,int val) {
		v[x]+=val;
	} 
	void init() {
		for(int i=1;i<=n;i++) {
			sum[i][0]=v[i];
			for(int j=1;j<20;j++) {
				sum[i][j]=sum[i][j-1]+sum[fa[i][j-1]][j-1];
			}
		}
	}
	void dfs(int x,int fa) {
		siz[x]=1;
		res[x]=res[fa]+1;
		for(int y:s[x]) {
			if(y==fa) continue;
			dfs(y,x); 
			siz[x]+=siz[y];
		}
	}
	int query(int x,int y) { //x is anc of y 
		int ans=0;
		for(int i=19;i>=0;i--) if(dep[fa[y][i]]>=dep[x]) ans+=sum[y][i],y=fa[y][i],ans%=mod;
		return ans; 
	}
}t1,t2,t3;
vector<int>s[N],g[N];
ll ksm(ll a,ll b) {
	if(b==1) return a;
	ll s=ksm(a,b/2);s=s*s%mod;
	if(b%2==1) s=s*a%mod;
	return s;
}
int ru[N];
struct node{
	int l,r,h;
}a[N];
vector<int>gL[N],gR[N];
int dom[N],vL[N],vR[N];
signed main() {
//	fil();
	n=read();
	for(int i=n;i>=1;i--) {
		a[i].l=read(),a[i].r=read(),a[i].h=i;
	}
	t.update(1,1,2*n,1,2*n,0);
	for(int i=1;i<=n;i++) {
		int L=t.query(1,1,2*n,a[i].l),R=t.query(1,1,2*n,a[i].r);
		t1.insert(i,L),t2.insert(i,R); 
		gL[L].push_back(i);gR[R].push_back(i);
		dom[i]=t3.lca(L,R);t3.insert(i,dom[i]);
		bit.upd(a[i].r,1);
		vL[i]=bit.qry(a[i].l-1),vR[i]=bit.qry(a[i].r);
		t.update(1,1,2*n,a[i].l,a[i].r,i);
	}
	memset(bit.t,0,sizeof bit.t);
	for(int i=1;i<=n;i++) {
		bit.upd(a[i].r,1);
		for(int y:gL[i]) {
			vL[y]-=bit.qry(a[y].l-1);
		}
		for(int y:gR[i]) {
			vR[y]-=bit.qry(a[y].r);
		}
	} 
	for(int i=1;i<=n;i++) {
		t1.upd(i,vL[i]);
		t2.upd(i,vR[i]);
	}
	ll res=0;
	t1.init(),t2.init();
	for(int i=1;i<=n;i++) {
		int cnt=t2.query(dom[i],i)-t1.query(dom[i],i);
		res=(res+ksm(cnt,mod-2)%mod)%mod;
	}
	cout<<res;
	return 0;
}
```

---

## 作者：是青白呀 (赞：0)

首先，拆期望得到我们要算的实际上是一块板子能被多少块板子上的水流到。设这个数为 $v_i$，则 $i$ 打开水龙头的期望为 $\frac{1}{v_i}$，答案即为所有期望求和。

主要问题在求 $v_i$。考虑哪些板子上的水可以流到 $i$？维护一个当前可接受到水并流到 $i$ 上去的范围 $(l_i,r_i)$，每次找到 $l_i$ 上方和 $r_i$ 上方的首个板子，它会扩展可接受到水的范围；当遇到一个板子将 $(l_i,r_i)$ 完全包含时，这块板子及上方的所有板子的水都流不到 $i$ 上了。若将一个板子左端点上方的首个和右端点上方的首个均向这个板子连边，则完全覆盖的那个板子就是图中 $i$ 的直接支配点。目标的板子数目就是左端点往上形成的轮廓，与右端点往上形成的轮廓，与支配板子之间的那部分板子的数目。可以用线段树维护求得上方的首个板子，然后隐式地建立支配树，倍增求得支配板子的编号。

对于这个不规则的塔形部分的板子计数，我们有必要进行拆分。我们先补全左侧的空白位置，变成求一条轮廓线的左侧的木板数；再对轮廓线上的每段横线进行拆分，最终就变成了要在 $O(n)$ 个矩形内数板子的问题，实际上就是矩形内数右端点的问题。用树状数组+扫描线即可求出每个板子的左右端点到其首个覆盖它的板子之间的这个矩形内部的板子数；然后再倍增求得左右轮廓线分别包裹的前缀木板数，相减即可。

总时间复杂度 $O(n\log n)$，需要实现一个线段树区间覆盖单点求值、一个扫描线树状数组的二位数点、一个支配树上的倍增数组、一组维护左右端点往上的木板编号及前缀木板数量的倍增数组。细节不多。

```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define ls(x) (x<<1)
#define rs(x) ((x<<1)|1)
#define mp make_pair
#define sec second
#define fir first
#define pii pair<int,int>
#define lowbit(i) i&-i
#define int long long
#define qingbai 666
using namespace std;
typedef long long ll;
const int N=5e5+5,M=105,inf=1e9+7,mo=1e9+7;
void read(int &p){
	int x=0,w=1;
	char ch=0;
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
}
int n,l[N],r[N],le[N][20],ri[N][20],suml[N][20],sumr[N][20],val[N];
int dep[N],fa[N][20];//支配树使用.
struct seg{
    int t[8*N];
    void pushdown(int x){
        if(!t[x])return;
        t[ls(x)]=t[x],t[rs(x)]=t[x],t[x]=0;
    }
    void modify(int x,int le,int ri,int ql,int qr,int v){
        if(ql<=le&&qr>=ri){
            t[x]=v;
            return;
        }
        pushdown(x);
        int mid=(le+ri)>>1;
        if(ql<=mid)modify(ls(x),le,mid,ql,qr,v);
        if(qr>mid)modify(rs(x),mid+1,ri,ql,qr,v);
    }
    int query(int x,int le,int ri,int p){
        if(le==ri)return t[x];
        pushdown(x);
        int mid=(le+ri)>>1;
        if(p<=mid)return query(ls(x),le,mid,p);
        else return query(rs(x),mid+1,ri,p);
    }
}T;
struct query{
    int pos,id;
};
vector<query>q[N];
int qres[4*N];
struct BIT{
    int t[2*N];
    void add(int x,int v){
        for(int i=x;i<=2*n;i+=lowbit(i))
            t[i]+=v;
    }
    int query(int x){
        int res=0;
        for(int i=x;i;i-=lowbit(i))
            res+=t[i];
        return res;
    }
}BIT;
int lca(int x,int y){
    if(dep[x]<dep[y])swap(x,y);
    repp(i,18,0)
        if(dep[fa[x][i]]>=dep[y])x=fa[x][i];
    if(x==y)return x;
    repp(i,18,0)
        if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
int quick_power(int base,int x){
    int res=1;
    while(x){
        if(x&1)res*=base,res%=mo;
        base*=base,base%=mo;
        x>>=1;
    }
    return res;
}
signed main(){
    read(n);
    rep(i,1,n)
        read(l[i]),read(r[i]);
    reverse(l+1,l+n+1),reverse(r+1,r+n+1);
    rep(i,1,n){//求上方的首个板子的编号，并做二维数点预处理
        le[i][0]=T.query(1,1,2*n,l[i]),ri[i][0]=T.query(1,1,2*n,r[i]);
        T.modify(1,1,2*n,l[i],r[i],i);
        q[le[i][0]].push_back((query){l[i],4*(i-1)+2});
        q[ri[i][0]].push_back((query){r[i],4*(i-1)+4});
        q[i].push_back((query){l[i],4*(i-1)+1});
        q[i].push_back((query){r[i],4*(i-1)+3});
    }
    rep(j,1,18){
        rep(i,1,n)
            le[i][j]=le[le[i][j-1]][j-1],ri[i][j]=ri[ri[i][j-1]][j-1];
    }
    rep(i,1,n){//隐式支配树
        int lcap=lca(le[i][0],ri[i][0]);
        fa[i][0]=lcap,dep[i]=dep[lcap]+1;
        rep(j,1,18)
            fa[i][j]=fa[fa[i][j-1]][j-1];
    }
    rep(i,1,n){//二维数点
        BIT.add(r[i],1);
        for(auto j:q[i])
            qres[j.id]=BIT.query(j.pos);
    }
    rep(i,1,n){
        suml[i][0]=qres[4*(i-1)+1]-qres[4*(i-1)+2];
        sumr[i][0]=qres[4*(i-1)+3]-qres[4*(i-1)+4];
        rep(j,1,18)
            suml[i][j]=suml[i][j-1]+suml[le[i][j-1]][j-1],sumr[i][j]=sumr[i][j-1]+sumr[ri[i][j-1]][j-1];
    }
    rep(i,1,n){
        int nw=i;
        repp(j,18,0)
            if(le[nw][j]>=fa[i][0])val[i]-=suml[nw][j],nw=le[nw][j];
        nw=i;
        repp(j,18,0)
            if(ri[nw][j]>=fa[i][0])val[i]+=sumr[nw][j],nw=ri[nw][j];
    }
    int ans=0;
    rep(i,1,n)
        ans+=quick_power(val[i],mo-2),ans%=mo;
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：qiuzx (赞：0)

[PA2024 题解全集](https://www.luogu.com.cn/article/gi139pd4)

利用期望的线性性，将期望次数转化为对每个木板，求考察它的时候它还没有被淹没的概率。若有 $x$ 个木板倒水后可以淹没这个木板（包含它自己），则这个概率显然是 $\frac1x$，因为要保证在排列中那 $x-1$ 个木板都在它后面。所以只要对每个 $i$ 求出 $f_i$ 表示能淹没到它的木板数量即可。

一个简单的想法就是对于这个木板找到左右两侧第一个它上面没有木板的位置，然后这中间的都是可以淹没它的。但这个想法最大的问题就是如果有一个木板特别大，完全包住了它，那么这上面所有木板都无法到达它了。所以需要一些更好的方式来刻画这个到达的问题。

那我们不妨从这个木板出发，向上一层一层考虑，这是因为当前层能否到达这个木板只和它们中间的木板形态有关。我们维护一个区间 $[l,r]$，表示当前从 $[l,r]$ 内的点开始竖直下落能够淹没这个木板。如果新的木板完全被 $[l,r]$ 包含或和它相离则不影响 $[l,r]$。否则若完全包含 $[l,r]$，则直接结束了，后面所有木板都不行了。剩下的情况，即有交但不包含时，$[l,r]$ 会和这个区间取并。

考虑一下这个过程的实际含义，发现左右端点的运动是相对独立的。我们可以从这个木板的左端点出发，一直向上走直到碰到第一块木板，然后改为从这个木板的左端点继续走。右端点也是同理。则第一块完全包含这个区间的木板就是左右端点的路径同时经过的第一块木板。而我们需要算的就是这两个端点路径中的木板个数。

先考虑怎么求这个覆盖的第一块木板，发现这相当于是求一个 DAG 上的支配点的问题，即将每个点左右端点向上的第一块木板反过来向下连边，则这个 DAG 上当前点的支配点就是需要求的木板。方便起见可以在最上面加一块覆盖所有木板的木板。这个 DAG 可以直接扫描线来求。而容易通过扫描线求出每次向上移动的时候这条线左边的木板个数，那么用倍增向上跳则可以记录这个区域左轮廓和右轮廓左侧的木板个数，减一下即可。复杂度 $O(n\log n)$。

``` c++
#include <bits/stdc++.h>
#define INF 1000000000
#define LINF 1000000000000000000
#define mod 1000000007
#define F first
#define S second
#define ll int
#define N 1000010
using namespace std;
struct BIT{
	ll val[N];
	void upd(ll x,ll v)
	{
		++x;
		while(x<N)
		{
			val[x]+=v;
			x+=x&(-x);
		}
		return;
	}
	ll qry(ll x)
	{
		++x;
		ll ret=0;
		while(x)
		{
			ret+=val[x];
			x-=x&(-x);
		}
		return ret;
	}
}bitl,bitr;
struct SegT{
	ll lo[N<<2],hi[N<<2],val[N<<2];
	void build(ll x,ll l,ll r)
	{
		lo[x]=l,hi[x]=r,val[x]=-1;
		if(l==r)
		{
			return;
		}
		ll mid=(l+r)>>1,a=x<<1;
		build(a,l,mid);
		build(a|1,mid+1,r);
		return;
	}
	void pushdown(ll x)
	{
		if(val[x]==-1)
		{
			return;
		}
		ll a=x<<1;
		val[a]=val[a|1]=val[x];
		val[x]=-1;
		return;
	}
	void update(ll x,ll l,ll r,ll v)
	{
		ll tl=lo[x],tr=hi[x];
		if(l<=tl&&tr<=r)
		{
			val[x]=v;
			return;
		}
		pushdown(x);
		ll mid=(tl+tr)>>1,a=x<<1;
		if(mid>=l)
		{
			update(a,l,r,v);
		}
		if(mid<r)
		{
			update(a|1,l,r,v);
		}
		return;
	}
	ll query(ll x,ll l)
	{
		ll tl=lo[x],tr=hi[x];
		if(tl==tr)
		{
			return val[x];
		}
		pushdown(x);
		ll mid=(tl+tr)>>1,a=x<<1;
		if(mid>=l)
		{
			return query(a,l);
		}
		return query(a|1,l);
	}
}segt;
ll n,lo[N],hi[N],inv[N],dep[N],nxtl[N],nxtr[N],to[20][N];
ll tol[20][N],tor[20][N],vl[20][N],vr[20][N];
vector<pair<ll,ll> > qryl[N],qryr[N];
vector<ll> updl[N],updr[N];
ll glca(ll x,ll y)
{
	if(dep[x]<dep[y])
	{
		swap(x,y);
	}
	ll i;
	for(i=19;i>=0;i--)
	{
		if(dep[to[i][x]]>=dep[y])
		{
			x=to[i][x];
		}
	}
	if(x==y)
	{
		return x;
	}
	for(i=19;i>=0;i--)
	{
		if(to[i][x]!=to[i][y])
		{
			x=to[i][x],y=to[i][y];
		}
	}
	return to[0][x];
}
int main(){
	ll i,j;
	inv[1]=1;
	for(i=2;i<N;i++)
	{
		inv[i]=(1ll*inv[mod%i]*(mod-mod/i))%mod;
	}
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d%d",&lo[i],&hi[i]);
	}
	lo[n]=0,hi[n]=n*2+1;
	segt.build(1,0,n*2+1);
	segt.update(1,0,n*2+1,n);
	for(i=n-1;i>=0;i--)
	{
		nxtl[i]=segt.query(1,lo[i]);
		nxtr[i]=segt.query(1,hi[i]);
		tol[0][i]=nxtl[i];
		tor[0][i]=nxtr[i];
		qryl[lo[i]].push_back(make_pair(i,nxtl[i]));
		qryr[hi[i]].push_back(make_pair(i,nxtr[i]));
		segt.update(1,lo[i],hi[i],i);
	}
	for(i=0;i<n;i++)
	{
		updl[lo[i]].push_back(i);
		updr[hi[i]].push_back(i);
	}
	for(i=1;i<=n*2;i++)
	{
		for(j=0;j<updl[i].size();j++)
		{
			bitl.upd(updl[i][j],1);
		}
		for(j=0;j<updr[i].size();j++)
		{
			bitr.upd(updr[i][j],1);
		}
		for(j=0;j<qryl[i].size();j++)
		{
			vl[0][qryl[i][j].F]=bitr.qry(qryl[i][j].S)-bitr.qry(qryl[i][j].F);
		}
		for(j=0;j<qryr[i].size();j++)
		{
			vr[0][qryr[i][j].F]=bitl.qry(qryr[i][j].S)-bitl.qry(qryr[i][j].F);
		}
	}
	for(i=0;i<20;i++)
	{
		to[i][n]=n;
		tol[i][n]=n;
		tor[i][n]=n;
	}
	for(i=1;i<20;i++)
	{
		for(j=0;j<n;j++)
		{
			tol[i][j]=tol[i-1][tol[i-1][j]];
			vl[i][j]=vl[i-1][j]+vl[i-1][tol[i-1][j]];
			tor[i][j]=tor[i-1][tor[i-1][j]];
			vr[i][j]=vr[i-1][j]+vr[i-1][tor[i-1][j]];
		}
	}
	dep[n]=0;
	for(i=n-1;i>=0;i--)
	{
		to[0][i]=glca(nxtl[i],nxtr[i]);
		dep[i]=dep[to[0][i]]+1;
		for(j=1;j<20;j++)
		{
			to[j][i]=to[j-1][to[j-1][i]];
		}
	}
	ll ans=0;
	for(i=0;i<n;i++)
	{
		ll req=to[0][i],tot=0;
		ll x=i;
		for(j=19;j>=0;j--)
		{
			if(tol[j][x]<=req)
			{
				tot-=vl[j][x];
				x=tol[j][x];
			}
		}
		x=i;
		for(j=19;j>=0;j--)
		{
			if(tor[j][x]<=req)
			{
				tot+=vr[j][x];
				x=tor[j][x];
			}
		}
		if(req==n)
		{
			tot++;
		}
		ans=(ans+inv[tot])%mod;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

