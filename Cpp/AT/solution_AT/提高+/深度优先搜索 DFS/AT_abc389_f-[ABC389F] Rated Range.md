# [ABC389F] Rated Range

## 题目描述

高桥君计划参加 AtCoder 的 $ N $ 场竞赛。

在第 $ i $ 场竞赛（$ 1 \leq i \leq N $）中，若他的评分处于 $ L_i $ 到 $ R_i $ 的闭区间内，则评分会增加 $ 1 $ 分。

请回答以下形式的 $ Q $ 个查询：

- 给定整数 $ X $，假设高桥君的初始评分为 $ X $，求经过所有 $ N $ 场竞赛后的最终评分。

## 说明/提示

### 约束条件

- $ 1 \leq N \leq 2 \times 10^5 $
- $ 1 \leq L_i \leq R_i \leq 5 \times 10^5 $（$ 1 \leq i \leq N $）
- $ 1 \leq Q \leq 3 \times 10^5 $
- 每个查询满足 $ 1 \leq X \leq 5 \times 10^5 $
- 输入均为整数

### 样例解释 1

**第 1 个查询**的评分变化过程如下：
- 第 1 场竞赛：评分在 $ [1, 5] $ 内，增加 1 分 → 4 分
- 第 2 场竞赛：评分不在 $ [1, 3] $ 内，保持 4 分
- 第 3 场竞赛：评分在 $ [3, 6] $ 内，增加 1 分 → 5 分
- 第 4 场竞赛：评分不在 $ [2, 4] $ 内，保持 5 分
- 第 5 场竞赛：评分在 $ [4, 7] $ 内，增加 1 分 → 6 分

**第 2 个查询**中，第 1、2、3、5 场竞赛评分增加，最终评分为 6 分。

**第 3 个查询**中，第 1、3、5 场竞赛评分增加，最终评分为 8 分。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
1 5
1 3
3 6
2 4
4 7
3
3
2
5```

### 输出

```
6
6
8```

## 样例 #2

### 输入

```
10
1 1999
1 1999
1200 2399
1 1999
1 1999
1 1999
2000 500000
1 1999
1 1999
1600 2799
7
1
1995
2000
2399
500000
2799
1000```

### 输出

```
8
2002
2003
2402
500001
2800
1007```

## 样例 #3

### 输入

```
15
260522 414575
436426 479445
148772 190081
190629 433447
47202 203497
394325 407775
304784 463982
302156 468417
131932 235902
78537 395728
223857 330739
286918 329211
39679 238506
63340 186568
160016 361868
10
287940
296263
224593
101449
336991
390310
323355
177068
11431
8580```

### 输出

```
287946
296269
224599
101453
336997
390315
323363
177075
11431
8580```

# 题解

## 作者：Empty_Dream (赞：9)

## 题意

给出 $N$ 场比赛，对于第 $i$ 场比赛，如果当前分数在 $L_i\sim R_i$ 之间，分数就会增加 $1$。

给出 $Q$ 次查询，每次一个整数 $x$ 表示高桥的初始评分，求 $N$ 场比赛后的评分。

## 分析

观察题目，肯定不可能是对于每一个 $x$ 模拟一遍。

不难猜想到一个性质：每一个区间对答案的贡献是连续的，换句话说，只有初始评分在某个区间内，才能获得当前区间 $[L_i,R_i]$ 的加分。

证明其实不难，考虑反证法：

> 假设获得区间 $[L_i,R_i]$ 加分的初始评分不连续，那么必定有初始评分在 $[l_1,r_1]$ 和 $[l_2,r_2]$ 之间的能获得贡献，但在 $(r_1,l_2)$ 之间的不能。
>
> 考虑什么情况下 $(r_1,l_2)$ 无法获得贡献，最终 $x < L_i$ 或 $x > R_i$：
>
> - $x < L_i$：因为评分是每次加 $1$ 的，为了使初始在 $[l_1,r_1]$ 区间的达到 $[L_i,R_i]$，必定有一系列区间覆盖了 $[l_1,L_i)$。而如果 $x < L_i$，那么还是能取得这一系列区间的贡献，然后到达 $[L_i,R_i]$，矛盾。
> - $x>R_i$：同样的，如果 $x > R_i$ 那么有一系列区间覆盖了 $(r_1,R_i]$，而初始在 $[l_2,r_2]$ 的区间也能取得这一系列区间的贡献，最终跳出 $R_i$，矛盾。
>
> 感性理解其实就是 $(r_1,l_2)$ 挡在了 $[l_1,r_1]$ 的必经之路上，它们会一起到 $L_i$ 之后，另一种情况同理，$[l_2,r_2]$ 挡在了 $(r_1,l_2)$ 前面，限制了 $(r_1,l_2)$ 使得它必须在 $R_i$ 之内。

所以假设不成立，命题得证，只有初始评分在一个区间 $[l_i,r_i]$ 内的，才能取得当前 $[L_i,R_i]$ 的贡献。

之后可以考虑对每个区间处理，可以通过二分确定区间 $[l_i,r_i]$。具体的，维护 $sum_i$ 表示以 $i$ 为初始能获得多少区间的贡献，也就是增量，所以 $i$ 最终的位置就是 $i+sum_i$。以确定 $l_i$ 为例，二分 $mid$，如果 $mid + sum_{mid}\ge L_i$，$mid$ 就能向左移，$r_i$ 类似。这样确定了 $[l_i,r_i]$ 后再来更新这一区间的 $sum$，每次加一。

但是这样修改 $sum$ 的复杂度是 $\mathcal{O}(n^2)$ 的，无法通过。但是我们有**树状数组**可以很好地解决区间加单点查这类问题，最后前面部分的复杂度为 $\mathcal{O}(n\log^2V)$。

对于查询部分直接输出 $x + sum_x$ 就结束了，这里复杂度是 $\mathcal{O}(q\log V)$，可以接受。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define pii pair<int, int>
#define fir first
#define sec second
#define endl "\n"
#define memset(a, b) memset(a, b, sizeof(a))
using namespace std;

const int N = 5e5 + 5;
const int mod = 998244353;

int n, q;
int x[N], y[N];

namespace bit_tree{
	int tr[N];
	void update(int p, int k){
		for (; p < N; p += p & -p) tr[p] += k;
	}

	int query(int p){
		int res = 0;
		for (; p; p -= p & -p) res += tr[p];
		return res;
	}
}
using namespace bit_tree;//树状数组

signed main(){
    ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> x[i] >> y[i];
		int l = 1, r = x[i], tmp = 1, tmp1 = 1;
		while (l <= r){ //二分确定 l_i
			int mid = l + r >> 1;
			if (mid + query(mid) >= x[i]) r = mid - 1, tmp = mid;
			else l = mid + 1;
		}
		l = 1, r = y[i];
		while (l <= r){ //二分确定 r_i
			int mid = l + r >> 1;
			if (mid + query(mid) <= y[i]) l = mid + 1, tmp1 = mid;
			else r = mid - 1;
		}
		update(tmp, 1); update(tmp1 + 1, -1);//更新[l_i,r_i]的sum
	}
	cin >> q;
	while (q--){
		int x; cin >> x;
		cout << x + query(x) << endl;//输出答案
	}
    return 0;
}
```

---

## 作者：Noah2022 (赞：8)

### 思路

注：（只要封装平衡树，并查集即可乱切）

对于每次比赛，可以抽象成把一段区间向右移一位 $L\sim R$，可以用平衡树维护：把一段区间向右移一位可以理解成把 $R,R+1$ 合并，再在 $L$ 前插入一个数合并可以用并查集，把每个集的头给拿数组标记其实在哪一位平衡树查一个点，时间复杂度为 $O(\log N)$，并查集合并两个集合，时间复杂度也为 $O(\log N)$，在开始时插入值域 $W$ 个数，每次插入 1 个点，把两个点合并，时间复杂度是：$ O( ( W + M + N ) \log W) $。

### 实现

1. 插入（详细在上面）。

2. $n$ 个比赛：

    > 把 $r,r+1$ 个点的集合头取出，把 $r$ 合并到 $r+1$，把 $r+1$ 所对应分数设置成 $r+1$ 在平衡树的 rank 即 $\le r+1$ 的数。

   > 在 $l$ 前面插入一个数，要注意顺序，先合并后插入（不然费脑）。

3. $m$ 场比赛：直接输出输入所在集的头的所对应分数即可 AC。

   ### Code and [AC Link](https://atcoder.jp/contests/abc389/submissions/61850577)

```cpp
// LUOGU_RID: 199125151
# include<iostream>
#include <ext/rope>
# define int long long
using namespace __gnu_cxx;
using namespace std;
const int W=500005;
rope<int>a;
int n,m,fa[W*4+1],l,r,N,dz[W*4+1];
inline int faz(const int &x){
	if(fa[x]!=x)fa[x]=faz(fa[x]);
	return fa[x];
}
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	for(int i = 0;i<=W+10;i++)a.push_back(i);
	for(int i = 1;i<=W<<2;i++)fa[i]=i;
	N=W*3;
	cin>>n;
	while(n--){
		cin>>l>>r;
		fa[faz(a[r])]=faz(a[r+1]);
		a.erase(r,1);
		a.insert(l,++N);
	}
	for(int i = 1;i<=W+1;i++)dz[faz(a[i])]=i;
	cin>>m;
	while(m--){
		cin>>l;
		cout<<dz[faz(l)]<<"\n";
	}
}
```

---

## 作者：yhy2024 (赞：8)

做法：
直接维护答案序列；

初始答案为1 2 3 4 5 6 7 8……

经过区间 $[1,3]$ 后 **2 3 4** 4 5 6 7 8……

经过区间 $[2,4]$ 后 **3 4 5 5** 5 6 7 8……

经过区间 $[5,8]$ 后 3 4 **6 6 6 7 8 9** ......

发现答案序列总是不下降的。

使用二分查找需要修改的 $[l,r]$, 线段树修改。也可以用[线段树二分](https://cn.bing.com/search?q=%E7%BA%BF%E6%AE%B5%E6%A0%91%E4%BA%8C%E5%88%86\&form=QBLH\&sp=-1\&lq=0\&pq=%E7%BA%BF%E6%AE%B5%E6%A0%91%E4%BA%8C%E5%88%86\&sc=0-5\&qs=n\&sk=\&cvid=CDEE1A44DD264CCBB95F07A59A4913E3\&ghsh=0\&ghacc=0\&ghpl=) Code

```cpp
#include<bits/stdc++.h>
#define N 500005 
using namespace std;
int mx,x,tr[N*4],lazy[N*4],l[N*2],r[N*2],n,m,ans1,ans2; 
void add(int k,int l,int r,int v){//线段树，支持区间修改单点查询
	tr[k]+=(r-l+1)*v;
	lazy[k]+=v;
} 
void pushdown(int k,int l,int r){
	if(!lazy[k]) return;
	int mid=l+r>>1;
	add(k<<1,l,mid,lazy[k]);
	add(k<<1|1,mid+1,r,lazy[k]);
	lazy[k]=0;
}
void build(int k,int l,int r){
	if(l==r){
		tr[k]=l;
		return;
	}
	int mid=l+r>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
}
void modify(int k,int l,int r,int x,int y){
	if(x<=l&&r<=y){
		add(k,l,r,1);
		return;
	}
	int mid=l+r>>1;
	pushdown(k,l,r);
	if(x<=mid) modify(k<<1,l,mid,x,y);
	if(y>mid) modify(k<<1|1,mid+1,r,x,y);
}
int ask(int k,int l,int r,int x){
	if(l==r) return tr[k];
	int mid=l+r>>1;
	pushdown(k,l,r);
	if(x<=mid) return ask(k<<1,l,mid,x);
	else return ask(k<<1|1,mid+1,r,x);
}
void print(){
	for(int i=1;i<=mx;i++){
		cout<<ask(1,1,mx,i)<<' ';
	}
	cout<<'\n';
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>l[i]>>r[i];
		mx=max(mx,r[i]);
	}
	build(1,1,mx);
	for(int i=1;i<=n;i++){
		int L=1,R=mx;
		int x=1,y=0;//需要修改的区间
		while(L<=R){
			int mid=L+R>>1;
			if(ask(1,1,mx,mid)>=l[i]) x=mid,R=mid-1;
			else L=mid+1;
		}
		L=1,R=mx;
		while(L<=R){
			int mid=L+R>>1;
			if(ask(1,1,mx,mid)<=r[i]) y=mid,L=mid+1;
			else R=mid-1;
		}
		modify(1,1,mx,x,y);
	}
	cin>>m;
	for(int i=1;i<=m;i++){
		cin>>x;
		if(x>mx) cout<<x<<'\n';
		else cout<<ask(1,1,mx,x)<<'\n'; 
	}
	return 0;	
} 
```

---

## 作者：lilong (赞：8)

赛后发现漏了一个显然性质，然后就过了，还是要多练。

这个显然性质是：如果有两个人初始等级分分别为 $x,y$ 且 $x<y$，那么在经历若干次比赛后，则 $x\le y$，即相对大小不变化。为什么正确呢？对于一场比赛，如果 $x$ 加分，$y$ 不加分，则 $x$ 最多与 $y$ 相同；如果 $x$ 不加分，$y$ 加分，则还是 $x < y$。于是该性质是正确的。

有了这个性质，我们就可以解决这道题了。先将所有询问离线下来，并按初始等级分从小到大排序。修改时，**单调性不变**，**整个等级分序列的顺序不会改变**，因此可以在线段树上通过维护区间最大值和最小值来确定修改的区间，且**该区间是连续的**。最后再还原到答案数组即可。

于是这道题就以 $O(n\log n)$（$n,q$ 同阶）的复杂度完成了。


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define N 500001

using namespace std;

struct T
{
	int mx,mi,id,lzy;
}t[N * 4];

int n,m,ql[N],qr[N],ans[N];
struct Q
{
	int v,id;
}a[N];
int read( void )
{
	int x = 0;
	char ch = getchar();
	while( ch < '0' || ch > '9' )
		ch = getchar();
	while( ch >= '0' && ch <= '9' )
		x = x * 10 + ch - '0',ch = getchar();
	return x;
}

void write( int x )
{
	if( x <= 9 )
	{
		putchar( x + '0' );
		return;
	}
	write( x / 10 );
	putchar( x % 10 + '0' );
	return;
}

void pushup( int u )
{
	t[u].mx = max( t[u << 1].mx , t[u << 1 | 1].mx );
	t[u].mi = min( t[u << 1].mi , t[u << 1 | 1].mi );
	return;
}

void pushdown( int u )
{
	t[u << 1].lzy += t[u].lzy;
	t[u << 1].mx += t[u].lzy;
	t[u << 1].mi += t[u].lzy;
	t[u << 1 | 1].lzy += t[u].lzy;
	t[u << 1 | 1].mx += t[u].lzy;
	t[u << 1 | 1].mi += t[u].lzy;
	t[u].lzy = 0;
	return;
}

void build( int u , int l , int r )
{
	if( l == r )
	{
		t[u].mx = t[u].mi = a[l].v;
		t[u].id = a[l].id;
		return;
	}
	int mid = ( l + r ) >> 1;
	build( u << 1 , l , mid );
	build( u << 1 | 1 , mid + 1 , r );
	pushup( u );
	return;
}

void update( int u , int l , int r , int L , int R )
{
	if( l == r )
	{
		if( L <= t[u].mi && t[u].mx <= R )
			t[u].mx ++,t[u].mi ++;
		return;
	}
	if( L <= t[u].mi && t[u].mx <= R )
	{
//		cout << L << ' ' << R << ' ' << l << ' ' << r << ' ' << t[u].mi << ' ' << t[u].mx << '\n';
		t[u].mx ++,t[u].mi ++;
		t[u].lzy ++;
		return;
	}
	pushdown( u );
	int mid = ( l + r ) >> 1;
	if( L <= t[u << 1].mx ) update( u << 1 , l , mid , L , R );
	if( R >= t[u << 1 | 1].mi ) update( u << 1 | 1 , mid + 1 , r , L , R );
	pushup( u );
	return;
}

void rbuild( int u , int l , int r )
{
	if( l == r )
	{
		ans[t[u].id] = t[u].mx;
		return;
	}
	pushdown( u );
	int mid = ( l + r ) >> 1;
	rbuild( u << 1 , l , mid );
	rbuild( u << 1 | 1 , mid + 1 , r );
	return;
}

bool cmp( Q x , Q y )
{
	return x.v < y.v;
}

int main()
{
	m = read();
	for( int i = 1 ; i <= m ; i ++ )
		ql[i] = read(),qr[i] = read();
	n = read();
	for( int i = 1 ; i <= n ; i ++ )
		a[i].v = read(),a[i].id = i;
	sort( a + 1 , a + n + 1 , cmp );
	build( 1 , 1 , n );
	for( int i = 1 ; i <= m ; i ++ )
		update( 1 , 1 , n , ql[i] , qr[i] );
	rbuild( 1 , 1 , n );
	for( int i = 1 ; i <= n ; i ++ )
	{
		write( ans[i] );
		putchar( '\n' );
	}
	return 0;
}
```

---

## 作者：Nt_Tsumiki (赞：7)

贴一下赛时做法。

先说一些符合直觉的性质：

1. 答案是关于初始位置单调不降的；
2. 在二维平面上，不同位置出发的轨迹折线不会在除了结束位置以外的地方相交。

我们考虑对初始位置扫描线，然后维护轨迹穿过了哪些比赛对应的区间，那么不难得到一个推论就是**对于一场比赛穿过区间的轨迹对应的初始位置是连续的一段**。

也就是说对于一场比赛出现 穿过到不穿过 或者 不穿过到穿过 这种变化各最多只有一次。

那我们就考虑在扫描线过程中维护这些变化，假设折线在第 $i$ 场比赛位于 $pos$，那我们可以用 $l_i-pos$ 或者 $r_i+1-pos$ 来刻画，实现上就是找第一个非正数，线段树二分即可。

然后对于找到的比赛 $i$ 对轨迹在 $[i+1,n]$ 进行区间加一或者减一即可。

复杂度是均摊 $O(n\log n+V+q)$，应该是目前理论复杂度最优。

[submission](https://atcoder.jp/contests/abc389/submissions/61810705)

---

## 作者：Aegleseeker_ (赞：7)

我们令 $f_{i,j}$ 代表打第 $j$ 场公开赛前 rated 是 $i$，打之后的 rated，不难发现第二维可以舍去，我们迭代 $n$ 次公开赛即可。现在我们需要快速迭代每一轮的结果。

令当前的 rated 区间为 $[L,R]$，似乎无法很好的找到经过 $j-1$ 次迭代后区间在 $[L,R]$ 范围内的那些点，但我们注意到一个性质：若对于两个 rated 满足 $x<y$，则不管打完几场比赛后仍满足 $x\le y$，既 $f_{i}$ 是单调不降的。

做法变得显然了。我们二分出线段树上第一个大于等于 $L$ 的 rated 位置和第一个小于等于 $R$ 的 rated 位置，区间加一即可，查询时等价于单点查询。

直接做是 $\log^2$ 的，使用线段树二分可以做到单 $\log$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n,q;
struct tree{
	int l,r,sum,tag,mn,mx;
}a[N*4];
void build(int u,int l,int r){
	a[u].l=l,a[u].r=r;
	if(l==r){
		a[u].sum=a[u].mx=a[u].mn=l;return;
	}
	int mid=(l+r)/2;
	build(u*2,l,mid),build(u*2+1,mid+1,r);
	a[u].mx=max(a[u*2].mx,a[u*2+1].mx);
	a[u].mn=min(a[u*2].mn,a[u*2+1].mn);
}
void pushdown(int u){
	a[u*2].tag+=a[u].tag,a[u*2+1].tag+=a[u].tag;
	a[u*2].sum+=a[u].tag*(a[u*2].r-a[u*2].l+1),a[u*2+1].sum+=a[u].tag*(a[u*2+1].r-a[u*2+1].l+1);
	a[u*2].mx+=a[u].tag,a[u*2+1].mx+=a[u].tag,a[u*2].mn+=a[u].tag,a[u*2+1].mn+=a[u].tag;
	a[u].tag=0;
}
void update(int u,int L,int R){
	if(L<=a[u].mn&&a[u].mx<=R){
		a[u].tag++,a[u].sum+=(a[u].r-a[u].l+1),a[u].mx++,a[u].mn++;
		return;
	}
	if(a[u].mx<L||a[u].mn>R) return;
	if(a[u].l==a[u].r) return;
	pushdown(u);
	update(u*2,L,R),update(u*2+1,L,R);
	a[u].mx=max(a[u*2].mx,a[u*2+1].mx);
	a[u].mn=min(a[u*2].mn,a[u*2+1].mn);
	a[u].sum=a[u*2].sum+a[u*2+1].sum;
}
int query(int u,int x){
	if(a[u].l==a[u].r) return a[u].sum;
	pushdown(u);
	if(x<=a[u*2].r) return query(u*2,x);
	else return query(u*2+1,x);
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	build(1,1,N-1);
	cin>>n;
	for(int i=1;i<=n;i++){
		int L,R;
		cin>>L>>R;
		update(1,L,R);
	}
	cin>>q;
	for(int i=1;i<=q;i++){
		int x;
		cin>>x;
		cout<<query(1,x)<<'\n';
	}
	return 0;
}
```

---

## 作者：cheng2010 (赞：6)

前情提要：

![](https://cdn.luogu.com.cn/upload/image_hosting/w9s0hq9e.png)

## 思路

一个一个跳显然爆炸，要考虑优化。

对于每一次操作，只有值在 $l \sim r$ 中的数会加一，其余不变，这启发我们需要一个动态查询在值 $l \sim r$ 中的数据结构，平衡树呼之欲出。

具体的，维护一个 lazy 标记，在分裂合并时下传即可，记得最后要把标记全下传了。

时间：$O(n \log n)$。

看来平衡树还是 YYDS。

## code
```cpp
#include<bits/stdc++.h>
#define ls(p) tree[p].lson
#define rs(p) tree[p].rson
#define tp_rt treap.root
#define INF 2147483647
using namespace std;
const int N=1e6+7;
struct BST
{
	int lson,rson,val,rnd,siz,lazy;
}tree[N];
struct FHQ_Treap
{
	int cnt,root;
	inline void change(int x)
	{
		tree[x].siz=tree[ls(x)].siz+1+tree[rs(x)].siz;
	}
	inline void down(int p)
	{
		int x=tree[p].lazy;
		tree[p].lazy=0;
		if(ls(p))
		{
			tree[ls(p)].val+=x;
			tree[ls(p)].lazy+=x; 
		}
		if(rs(p))
		{
			tree[rs(p)].val+=x;
			tree[rs(p)].lazy+=x; 
		}
	}
	inline void split_val(int p,int &x,int &y,int key)
	{
		if(!p)
		{
			x=y=0;
			return;
		}
		down(p);
		if(tree[p].val<=key)
		{
			x=p;
			split_val(rs(p),rs(p),y,key);
			change(x);
		}
		else
		{
			y=p;
			split_val(ls(p),x,ls(p),key);
			change(y);
		}
	}
	inline int merge(int x,int y)
	{
		if(!x||!y)
			return x|y;
		down(x);
		down(y);
		if(tree[x].rnd<tree[y].rnd)
		{
			rs(x)=merge(rs(x),y);
			change(x);
			return x;
		}
		else
		{
			ls(y)=merge(x,ls(y));
			change(y);
			return y;
		}
	}
	inline int join(int x)
	{
		tree[++cnt].val=x;
		tree[cnt].siz=1;
		tree[cnt].rnd=rand();
		return cnt;
	}
	inline void ins(int &rt,int x)
	{
		int r1,r2;
		split_val(rt,r1,r2,x);
		rt=merge(merge(r1,join(x)),r2);
	}
	inline void update(int &rt,int l,int r)
	{
		int r1,r2,r3;
		split_val(rt,r2,r1,l-1);
		split_val(r1,r1,r3,r);
		tree[r1].val++;
		tree[r1].lazy++;
		rt=merge(r2,merge(r1,r3));
	}
	inline void down_all(int p)
	{
		down(p);
		if(ls(p))
			down_all(ls(p));
		if(rs(p))
			down_all(rs(p));
	}
}treap;
int n,q;
int l[N],r[N];
int main()
{
	srand(time(0));
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d %d",&l[i],&r[i]);
	}
	cin>>q;
	for(int i=1;i<=q;i++)
	{
		int x;
		scanf("%d",&x);
		treap.ins(tp_rt,x);
	}
	for(int i=1;i<=n;i++)
	{
		treap.update(tp_rt,l[i],r[i]);
	}
	treap.down_all(tp_rt);
	for(int i=1;i<=q;i++)
	{
		printf("%d\n",tree[i].val);
	}
}
```

---

## 作者：yy0707 (赞：6)

### 题目大意：

有 $n$ 场比赛，第 $i$ 场所有分数在 $l_i$ 到 $r_i$ 之间的人可以加 1 分。然后给你 $q$ 个询问，问如果一个人的初始分数是 $x$ 那么在这 $n$ 场比赛之后它的分数是多少。

### Solution：

我们可以将所有询问排好序，存进树状数组里，然后模拟 $n$ 场比赛，每次利用树状数组倍增求出第一个大于等于 $l_i$ 的位置以及最后一个小于等于 $r_i$ 的位置（觉得麻烦也可以用二分，但是时间是 $\log^2q$），然后区间加把这一段区间加上 1，前面几步都可以用树状数组维护差分数组来解决，最后把答案取出来输出就行了。  
时间复杂度 $O((q+n)\log q)$。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,l[200001],r[200001],ans[300001];
struct query{int x,id;}p[300001];
struct fenwick{
	private:
		int tr[300001];
		void add(int p,int x){for(;p<=q;p+=p&-p)tr[p]+=x;}
	public:
		void add(int l,int r,int x){add(l,x);add(r+1,-x);}
		int query(int p){
			int ans=0;
			for(;p;p-=p&-p)ans+=tr[p];
			return ans;
		}int first_ge(int x){
			int p=0,v=0;
			for(int i=20;i>=0;i--){
				if(p+(1<<i)<=q&&v+tr[p+(1<<i)]<x)p+=(1<<i),v+=tr[p];
			}return p+1;
		}int last_le(int x){
			int p=0,v=0;
			for(int i=20;i>=0;i--){
				if(p+(1<<i)<=q&&v+tr[p+(1<<i)]<=x)p+=(1<<i),v+=tr[p];
			}return p;
		}
}tr;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>l[i]>>r[i];
	cin>>q;
	for(int i=1;i<=q;i++)cin>>p[i].x,p[i].id=i;
	sort(p+1,p+q+1,[](query a,query b){return a.x<b.x;});
	for(int i=1;i<=q;i++)tr.add(i,i,p[i].x);
	for(int i=1;i<=n;i++){
		int x=tr.first_ge(l[i]);
		int y=tr.last_le(r[i]);
		tr.add(x,y,1);
	}for(int i=1;i<=q;i++)ans[p[i].id]=tr.query(i);
	for(int i=1;i<=q;i++)cout<<ans[i]<<'\n';
}
```

---

## 作者：Otue (赞：4)

定义 $f_i$ 表示初始分数为 $i$，经过比赛后的最终分数。初始值 $f_i=i$。

经过第一场比赛后，值域在 $L_1\sim R_1$ 中的所有 $f_i$ 都会加上 $1$。经过第二场比赛后，值域在 $L_2\sim R_2$ 中的所有 **更新后的 $f_i$ 值** 都会加上 $1$。故每次把值域在 $L_i\sim R_i$ 中的 $f_i$ 值加上一。

故线段树维护，每次找到大于等于 $L$ 的左端点和小于等于 $R$ 的右端点，再维护区间加操作即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define PII pair<int, int>
#define _for(i, a, b) for (int i = (a); i <= (b); i++)
#define _pfor(i, a, b) for (int i = (a); i >= (b); i--)
#define int long long
const int N = 5e5 + 5;

int n, Q;


struct edge {
	int l, r;
}ed[N]; 

struct stu {
	int ls[N << 2], rs[N << 2], maxn[N << 2], sum[N << 2], lazy[N << 2];
	void push_up(int p) {
		maxn[p] = max(maxn[p << 1], maxn[p << 1 | 1]);
		sum[p] = sum[p << 1] + sum[p << 1 | 1];
	}
	
	void push_down(int p) {
		if (lazy[p]) {
			lazy[p << 1] += lazy[p]; maxn[p << 1] += lazy[p];
			lazy[p << 1 | 1] += lazy[p]; maxn[p << 1 | 1] += lazy[p];
			sum[p << 1] += (rs[p << 1] - ls[p << 1] + 1) * lazy[p];
			sum[p << 1 | 1] += (rs[p << 1 | 1] - ls[p << 1 | 1] + 1) * lazy[p];
			lazy[p] = 0;
		}
	} 
	
	void build(int p, int l, int r) {
		ls[p] = l, rs[p] = r;
		if (l == r) {
			maxn[p] = sum[p] = l;
			return;		
		}
		int mid = (l + r) >> 1;
		build(p << 1, l, mid);
		build(p << 1 | 1, mid + 1, r);
		push_up(p);
	}
	
	void modify(int p, int L, int R, int l, int r) {
		if (l <= L && R <= r) {
			lazy[p]++;
			sum[p] += (R - L + 1); 
			maxn[p]++;
			return;
		}
		push_down(p);
		int mid = (L + R) >> 1;
		if (l <= mid) modify(p << 1, L, mid, l, r);
		if (r > mid) modify(p << 1 | 1, mid + 1, R, l, r);
		push_up(p);
	}
	
	int query_max(int p, int L, int R, int l, int r) {
		if (l <= L && R <= r) return maxn[p];
		push_down(p);
		int mid = (L + R) >> 1, res = 0;
		if (l <= mid) res = max(res, query_max(p << 1, L, mid, l, r));
		if (r > mid) res = max(res, query_max(p << 1 | 1, mid + 1, R, l, r));
		return res; 
	}
	
	int query_sum(int p, int L, int R, int l, int r) {
		if (l <= L && R <= r) return sum[p];
		push_down(p);
		int mid = (L + R) >> 1, res = 0;
		if (l <= mid) res += query_sum(p << 1, L, mid, l, r);
		if (r > mid) res += query_sum(p << 1 | 1, mid + 1, R, l, r);
		return res; 
	}
}tr;



int getl(int x) {
	int L = 1, R = N - 5;
	while (L < R) {
		int mid = (L + R) >> 1;
		if (tr.query_max(1, 1, N - 5, 1, mid) >= x) R = mid;
		else L = mid + 1;
	}
	return L;
}

int getr(int x) {
	int L = 1, R = N - 5;
	while (L < R) {
		int mid = (L + R + 1) >> 1;
		if (tr.query_max(1, 1, N - 5, 1, mid) <= x) L = mid;
		else R = mid - 1;
	}
	return L; 
}

signed main() {
	cin >> n;
	_for(i, 1, n) cin >> ed[i].l >> ed[i].r;
	tr.build(1, 1, N - 5);
	_for(i, 1, n) {
		tr.modify(1, 1, N - 5, getl(ed[i].l), getr(ed[i].r));
	}
	cin >> Q;
	while (Q--) {
		int x;
		cin >> x;
		cout << tr.query_sum(1, 1, N - 5, x, x) << endl; 
	}		 
}
```

---

## 作者：gcx114514 (赞：4)

一道平衡树版题，不会平衡树的建议先完成 [P3369 【模板】普通平衡树](https://www.luogu.com.cn/problem/P3369) 。

考虑将询问离线下来排好序，然后依次执行每个操作，每个操作其实等价于在平衡树上值在 $[l_i,r_i]$ 直接的数加 $1$，可以直接用 FHQ 分裂出这个区间打上区间加即可，最后遍历一边取出所有值即可。

[Submission #61813008 ](https://atcoder.jp/contests/abc389/submissions/61813008)

---

## 作者：emmoy (赞：3)

提供一个平衡树做法。

首先你可以将询问离线下来，排序后塞进一棵文艺平衡树里，然后枚举 $i\in[1,n]$，根据 $l_i-1$ 与 $r_i$ 将 FHQ `split` 开，打个加一的 `tag` 再 `merge` 回去，最后将所有 `tag` 下传就行了。

```cpp
#include<bits/stdc++.h>
#define N 700010
using namespace std;
int n,m,sz[N],ls[N],rs[N],val[N],lasy[N],f[N];
unsigned int rd[N];
mt19937 rnd(time(0));
int root,cnt;
int g(int x,int y)
{
	sz[++cnt]=1,val[cnt]=x,rd[cnt]=rnd();
	f[cnt]=y;
	return cnt;
}
void upd(int p)
{
	sz[p]=sz[ls[p]]+sz[rs[p]]+1;
}
void pushdown(int p)
{
	if(lasy[p])
	{
		if(ls[p]) lasy[ls[p]]+=lasy[p],val[ls[p]]+=lasy[p];
		if(rs[p]) lasy[rs[p]]+=lasy[p],val[rs[p]]+=lasy[p];
		lasy[p]=0;
	}
}
void split(int p,int k,int &x,int &y)
{
	if(!p) {x=y=0;return ;}
	pushdown(p);
	if(k<val[p]) y=p,split(ls[p],k,x,ls[p]);
	else x=p,split(rs[p],k,rs[p],y);
	upd(p);
}
int merge(int x,int y)
{
	if(!x||!y) return x+y;
	if(rd[x]<rd[y])
	{
		pushdown(x);
		rs[x]=merge(rs[x],y);
		upd(x);
		return x;
	}
	else{
		pushdown(y);
		ls[y]=merge(x,ls[y]);
		upd(y);
		return y;
	}
}
void solve(int l,int r)
{
	int x,y;
	split(root,l-1,x,y);
	int u,v;
	split(y,r-l+1,u,v);
	lasy[u]^=1;
	root=merge(x,merge(u,v));
}
int l[N],r[N];
struct node{
	int val,id;
}h[N];
int ans[N];
void solve(int p)
{
	if(!p) return;
	pushdown(p);
	ans[f[p]]=val[p];
	print(ls[p]);
	print(rs[p]);
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>l[i]>>r[i];
	cin>>m;
	for(int i=1;i<=m;i++) cin>>h[i].val,h[i].id=i;
	sort(h+1,h+1+m,[&](node x,node y){return x.val<y.val;});
	for(int i=1;i<=m;i++) root=merge(root,g(h[i].val,h[i].id));
	for(int i=1;i<=n;i++){
		int x,y,z;
		split(root,l[i]-1,x,y);
		split(y,r[i],y,z);
		lasy[y]++,val[y]++;
		root=merge(x,merge(y,z));
	}
	solve(root);
	for(int i=1;i<=m;i++) cout<<ans[i]<<"\n";
	return 0;
}
```

---

## 作者：liuhongyang123 (赞：2)

## 解题方法
一道分块板子。

我们可以看到数值的范围很小，所以考虑分块。

$b$ 数组代表大块，也就是 $b[i]$ 代表数值在第 $i$ 块范围中的 $x$ 经过操作后可以**共同**加的数值。

$a$ 数组代表小块，也就是 $a[x]$ 代表数值 $x$ 无法在大块中体现的部分。

可能有点绕，大家可结合代码理解。

说完数组定义后讲一下方法。

对于每一对 $l$ 和 $r$，我们二分把其可以影响到的数值上限和下限求出来，对应把这段范围在块上面加其贡献，也就是 $+1$。 

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define qk(x) ((x-1)/B+1)
//qk(x) 求出数值x在哪一个块当中
using namespace std;
const int N=6e5,B=sqrt(N)+1,MAXN=1e7+10;
//N 数值范围，B 块的个数与大小
int n,m,p,q,len,len1,a[MAXN],b[MAXN];
//a[x]+b[qk(x)] 就是当前x经过前面评分变化后的值
int ef(int x){ //二分求上限下限
	if(a[N]+b[qk(N)]<x) return N+1;
	int l=1,r=N;
	while(l<r){
		int mid=(l+r)/2;
		if(a[mid]+b[qk(mid)]<x) l=mid+1;
		else r=mid;
	}
	return l;
}
signed main(){
	cin>>n;
	for(int i=1;i<=N;i++) a[i]=i;
	for(int i=1;i<=n;i++) {
		int l,r;
		cin>>l>>r;
		int l1=ef(l),r1=ef(r+1)-1,kl=qk(l1),kr=qk(r1);
		if(kl==kr) for(int i=l1;i<=r1;i++) a[i]++;//在同一块中，小块直接加。
		else{
			//若上限下限不在同一块中
			for(int i=l1;i<=kl*B;i++) a[i]++;//把前面多出来的算上
			for(int i=kr*B-B+1;i<=r1;i++) a[i]++;//后面多的也算上
			for(int i=kl+1;i<=kr-1;i++) b[i]++;//中间整块整块的，直接大块中加
			//如果看不懂这里，建议复习一下分块模板
		}
	}
	cin>>m;
	for(int i=1,x;i<=m;i++){
		cin>>x;
		cout<<a[x]+b[qk(x)]<<endl;//单独贡献+同块贡献
	}
	return 0;
}
```

### 完结散花

---

## 作者：lzyqwq (赞：2)

> - 给出 $n$ 个区间 $[L_i,R_i]$，定义函数：
>   $$f(X,i)=\begin{cases}X,i=0\\f(X,i-1)+1,i\ne 0\land f(X,i-1)\in[L_i,R_i]\\f(X,i-1),\text{otherwise}\end{cases}$$
>  - $q$ 次询问 $f(X,n)$。
>  - $n\le 2\times 10^5$，$q\le 3\times 10^5$，$R_i,X\le 5\times 10^5$。

注意到 $f(X,i)$ 非降。给出证明：

> 考虑归纳法。
> - 当 $i=0$ 时显然非降。
> - 假设当 $i\in [0,m]$ 时非降，则当 $i=m+1$ 时，记最小、最大的满足 $f(X,m)\in[L_{m+1},R_{m+1}]$ 的 $X$ 分别为 $X_{\min},X_{\max}$，则由于非降的性质，$f(X,m)\in[L_{m+1},R_{m+1}]$ 的 $X$ 构成的集合等价于区间 $[X_{\min},X_{\max}]$，且 $f(X_{\max}+1,m)>f(X_{\max},m)$。则对于这个区间内的数 $X$ 而言，$f(X,m+1)=f(X,m)+1$，剩余 $X$ 的 $f(X,m+1)=f(X,m)$。由于当 $i=m$ 时 $f(X,i)$ 非降，因此对于 $[1,X_{\min}),[X_{\min},X_{\max}],(X_{\max},+\infty)$ 三个区间而言，其内部的 $f(X,m+1)$ 非降。且有 $f(X_{\min}-1,m)\le f(X_{\min},m)<f(X_{\min},m)+1$，$f(X_{\max},m)+1=f(X_{\max},m+1)\le f(X_{\max}+1,m+1)$。从而证明了临界点处非降。因此当 $i\in[1,m+1]$ 时 $f(X,i)$ 非降。
>   
> $\mathcal{Q.E.D.}$

然后就简单了。枚举 $i$ 维护当前的 $f(X,i)$，根据单调性可以二分出每次的 $X_{\min},X_{\max}$，然后区间加即可从 $f(X,i)$ 推到 $f(X,i+1)$。二分的检查以及询问均需要支持单点查询，使用 BIT 维护差分数组即可。

时间复杂度 $\mathcal{O}\left(n\log^2 X\right)$，空间复杂度为 $\mathcal{O}(X)$。

[AC Link & Code](https://atcoder.jp/contests/abc389/submissions/61801047)

---

## 作者：chenxi2009 (赞：2)

## 思路
考虑暴力预处理出每一个初始的分数 $1\le X\le 5\times10^5$ 对应的终分数，复杂度 $O(N\max X)$。

发现每一次比赛会给连续一段初始分数的情况加一分，考虑线段树，$s_i$ 表示初始分数为 $i$ 时的分数。初始令 $s_i=i(1\le i\le 5\times10^5)$。

发现任意时刻 $s$ 单调不减。所以对于每一次比赛，可以二分出这次比赛前在计分边界的 $s_i$，把它俩中间的 $s$ 全部加上一。复杂度较劣考虑线段树上二分，线段树维护区间最大/最小值。预处理复杂度 $O(N\log\max X)$。

最终每一次询问单点查询即可。询问复杂度 $O(Q\log\max X)$。

时间复杂度 $O((N+Q)\log\max X)$。
## 代码
### 省略线段树版代码
**此代码直接提交将不能通过题目。**
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mxr = 500000;
int n,q,l,r,x;
int main(){
	build(1,1,mxr);//建树
	scanf("%d",&n);
	for(int i = 1;i <= n;i ++){
		scanf("%d%d",&l,&r);
		l = lbd(1,1,mxr,l),r = lbd(1,1,mxr,r + 1) - 1;//lbd 会二分最后一个参数出现的位置中的最小值
		upd(1,1,mxr,l,r);//l 与 r 之间所有 s_i 加上一
	} 
	scanf("%d",&q);
	for(int i = 1;i <= q;i ++){
		scanf("%d",&x);
		printf("%d\n",qry(1,1,mxr,x));//查询 s_x
	}
	return 0;
}
```
### 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mxr = 500000;
int n,q,l,r,x,mx[2000000],add[2000000];
inline void pushup(int k){//上传信息 
	mx[k] = max(mx[k << 1],mx[k << 1 | 1]);
	return;
}
inline void pushdown(int k){//下传标记 
	mx[k << 1] += add[k],mx[k << 1 | 1] += add[k];
	add[k << 1] += add[k],add[k << 1 | 1] += add[k];
	add[k] = 0;
	return;
}
void build(int k,int l,int r){//建树 
	if(l == r){
		mx[k] = l;
		return;
	}
	int mid = l + r >> 1;
	build(k << 1,l,mid);
	build(k << 1 | 1,mid + 1,r);
	pushup(k);
	return;
}
void upd(int k,int l,int r,int x,int y){//更新 s_{x...y}
	if(l > r || y < l || x > r) return;
	if(x <= l && y >= r){
		mx[k] ++,add[k] ++;
		return;
	}
	pushdown(k);
	int mid = l + r >> 1;
	upd(k << 1,l,mid,x,y);
	upd(k << 1 | 1,mid + 1,r,x,y);
	pushup(k);
	return; 
}
int lbd(int k,int l,int r,int num){//二分 num 最左的位置 
	if(mx[k] < num) return mxr + 1;
	if(l == r) return l;
	pushdown(k);
	int mid = l + r >> 1;
	int rtn = lbd(k << 1,l,mid,num);
	if(rtn == mxr + 1) return lbd(k << 1 | 1,mid + 1,r,num);
	return rtn;
}
int qry(int k,int l,int r,int aim){//查询 s_aim 
	if(aim < l || aim > r) return 0;
	if(l == r) return mx[k];
	pushdown(k);
	int mid = l + r >> 1;
	return qry(k << 1,l,mid,aim) + qry(k << 1 | 1,mid + 1,r,aim); 
}
int main(){
	build(1,1,mxr);
	scanf("%d",&n);
	for(int i = 1;i <= n;i ++){
		scanf("%d%d",&l,&r);
		l = lbd(1,1,mxr,l),r = lbd(1,1,mxr,r + 1) - 1;
		upd(1,1,mxr,l,r);
	} 
	scanf("%d",&q);
	for(int i = 1;i <= q;i ++){
		scanf("%d",&x);
		printf("%d\n",qry(1,1,mxr,x));
	}
	return 0;
}
```

---

## 作者：CuFeO4 (赞：2)

和首切差了 $6$ 分钟，没有抢上，悲。提供一个不用脑子的平衡树做法。

对于每个询问，我们将其插入一颗平衡树中，记录其在平衡树上的节点编号。

然后从左往右做扫描线，对于每个形如 $[l,r]$ 的更改，将平衡树上值域在 $[l,r]$ 中的分裂出来进行区间加，最后在平衡树上遍历，统一查询答案即可。

由于每次只是加 $1$，可以做到 $O(n\log q)$ 的复杂度，比官方题解的 $(n+q)\log V$ 优，尽管跑得并不快罢了。

[AC Link](https://atcoder.jp/contests/abc389/submissions/61797274)。

---

## 作者：Eterna (赞：2)

记 $d_{i,j}$ 为 $x=i$ 时，经过前 $j$ 个区间的答案。

显然 $d_{i,0}=i,d_{i,j}=d_{i,j-1}+[l_j \le d_{i,j-1} \le r_j]$。

结论：对于任意一维的 $j$，答案在 $i$ 轴单调不减。

证明分两种情况讨论：

>1. 取 $i$ 与 $i+1$ 时，所匹配的区间一样，结论显然。
>2. 取 $i$ 与 $i+1$ 时，存在一个区间 $i \in [l_k,r_k]$，但是不 $i+1 \in [l_k,r_k]$，此时 $i+1$ 变成 $i$ 了，答案相同。
>3. 取 $i$ 与 $i+1$ 时，存在一个区间 $i+1 \in [l_k,r_k]$，但是不 $i \in [l_k,r_k]$，$i+1$ 的答案显然不会小于 $i$ 了。

考虑直接维护答案序列，每次加入区间 $[l_i,r_i]$ 即对于整个序列中大小在 $[l_i,r_i]$ 中的数加一。

根据单调性线段树二分，做区间加，然后询问即为单点查询。

时间复杂度 $O((n+q) \log V)$，[提交记录](https://atcoder.jp/contests/abc389/submissions/61847518)。

---

## 作者：imljw (赞：1)

~~这题是我场切的分值最高的题，记录一下~~

我们可以发现，直接暴力地去对于每个询问去重新算等级分，是铁定超时的，那我们可以换个方向，对于每个等级分修改范围，去找到一个区间，使得初始等级分在这个范围内的全都会在该区间加分，然后就可以预处理一个初始等级分会加多少分了。区间修改，单点查询，树状数组加差分就行了（傻傻的我写了线段树）。

那怎么找呢？很明显，我们算到了第 $i$ 个区间，现在的等级分改变数组存的就是把前 $i-1$ 场比赛打完会加多少分，那是不是直接二分就可以了？因为每次等级分只加 $1$，所以初始等级分 $x$ 任何时候一定不比初始为 $x-1$ 小。所以单调性是有的，二分就完了。

~~你们最想看的东西来了。~~
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node {
	int l,r;
} e[200005];
int T,n,k,m,tag[40000005],a[40000005];
void pushdown(int k, int l, int r) {
	if (tag[k]) {
		int mid = l + r >> 1;
		a[k << 1] += tag[k] * (mid - l + 1);
		a[k << 1 | 1] += tag[k] * (r - mid);
		tag[k << 1] += tag[k];
		tag[k << 1 | 1] += tag[k];
		tag[k] = 0;
	}
}
void addtag(int k, int l, int r, int x, int y, int v) {
	if (l >= x && r <= y) {
		a[k] += v * (r - l + 1);
		tag[k] += v;
		return;
	}
	pushdown(k, l, r);
	int mid = l + r >> 1;
	if (x <= mid)
		addtag(k << 1, l, mid, x, y, v);
	if (y > mid)
		addtag(k << 1 | 1, mid + 1, r, x, y, v);
	a[k] = a[k << 1] + a[k << 1 | 1];
}
void update(int k) {
	a[k] = a[k << 1] + a[k << 1 | 1];
}
void change(int k, int l, int r, int x, int y, int v) {
	if (r < l || r < x || l > y)
		return;
	if (l >= x && r <= y) {
		addtag(k, l, r, x, y, v);
		return;
	}
	pushdown(k, l, r);
	int mid = l + r >> 1;
	if (x <= mid)
		change(k << 1, l, mid, x, y, v);
	if (y > mid)
		change(k << 1 | 1, mid + 1, r, x, y, v);
	update(k);
}
int query(int k, int l, int r, int x, int y) {
	pushdown(k, l, r);
	if (l >= x && r <= y)
		return a[k];
	int res = 0, mid = l + r >> 1;
	if (x <= mid)
		res = query(k << 1, l, mid, x, y);
	if (y > mid)
		res += query(k << 1 | 1, mid + 1, r, x, y);
	return res;
}
bool check(int x,int i){
	int tt=x+query(1,1,1000000,x,x);
	return	tt>=e[i].l;
}
bool chec2(int x,int i){
	int tt=x+query(1,1,1000000,x,x);
	return	tt<=e[i].r;
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; i++) {
		scanf("%d%d",&e[i].l,&e[i].r);
	}
	change(1,1,1000000,e[1].l,e[1].r,1);
	for(int i=2; i<=n; i++){
		int l=1,r=e[i].r,p=0,p2=0;
		while(l<=r){
			int mid=l+r>>1;
			if(check(mid,i))p=mid,r=mid-1;
			else l=mid+1;
		}
		l=1,r=e[i].r;
		while(l<=r){
			int mid=l+r>>1;
			if(chec2(mid,i))p2=mid,l=mid+1;
			else r=mid-1;
		}
		if(p&&p2&&p<=p2)change(1,1,1000000,p,p2,1);
	}
	scanf("%d",&m);
	while(m--){
		int x;
		scanf("%d",&x);
		printf("%d\n",x+query(1,1,1000000,x,x));
	}
	return 0;
}
```

---

## 作者：Judgelight (赞：1)

[传送门](https://www.luogu.com.cn/problem/AT_abc389_f)

---

对于这道题，我们每次要做的操作是区间平移，所以平衡树维护即可。

然后这个做法可以扩展到 [PKUSC2024D2T2](https://qoj.ac/problem/8672)，你会发现这其实是一个题，所以我们套刚才的做法，做区间平移即可。但是这个做法比较烂，可能需要一定的卡常才能通过，反正比 $O(\log^2 n)$ 慢。

---

## 作者：ny_Dacong (赞：1)

# 思路

发现值域不大，因此可以开一个桶，计算初始评分为 $i$ 时，最终可以达到的评分 $g_i$。

首先初始化 $\forall i, g_i \gets i$。

那么对于一个区间，我们让所有在范围 $[L_i,R_i]$ 的 $g_i$ 都加一（注意不是 $i$）。

可以证明，$g$ 一定是单调不减的。因为改变 $g_i$ 的方式只有加一，如果 $i < j$ 但 $g_i > g_j$，那么就说明 $g_i$ 需要先变得等于 $g_j$ 然后才能超过它。然而如果 $g_i = g_j$，那么以后的所有操作一定会同时作用在它们二者的身上。所以 $g_i$ 永远不可能 $ > g_j$。

因此每次操作其实改变的是一段连续区间，只不过我们不知道这个区间的左右端点。不过 $g_i$ 有单调性，所以我们可以二分查找左右端点。

因此你需要维护区间修改，单点查询的数据结构。线段树当然是可以的，不过我懒得写。所以用差分思想把区间修改转化为单点修改，用树状数组维护即可。

令 $x$ 为值域的上界。由于树状数组的查询是 $O(\log x)$ 的，而且我们还在外面套了一个二分。所以处理一个区间的复杂度是 $O(\log^2 x)$，一共就是 $O(N \log^2 x)$。每次查询是 $O(\log x)$，所以最后的总复杂度是 $O(N \log^2 x+Q \log x)$。

# AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q;
int num[700050];
int lowbit(int x){
	return x&(-x);
}
void modify(int x,int pos){
	for(int i = pos; i <= 7e5; i += lowbit(i)){
		num[i] += x;
	}
	return;
}
int query(int pos){
	int res = 0;
	for(int i = pos; i >= 1; i -= lowbit(i)){
		res += num[i];
	}
	return res;
}
int lbd(int x){
	int l = 1,r = 7e5,mid,ans = 0,tp;
	while(l <= r){
		mid = l+((r-l)>>1);
		tp = query(mid);
		if(tp >= x){
			ans = mid;
			r = mid-1;
		}else{
			l = mid+1;
		}
	}
	return ans;
}
int ubd(int x){
	int l = 1,r = 7e5,mid,ans = 0,tp;
	while(l <= r){
		mid = l+((r-l)>>1);
		tp = query(mid);
		if(tp > x){
			ans = mid;
			r = mid-1;
		}else{
			l = mid+1;
		}
	}
	return ans;
}
int main(){
	scanf("%d",&n);
	for(int i = 1; i <= 7e5; i++){
		modify(1,i);
	}
	while(n--){
		static int tpa,tpb,tpc,tpd;
		scanf("%d%d",&tpa,&tpb);
		tpc = lbd(tpa);
		tpd = ubd(tpb);
		modify(1,tpc);
		modify(-1,tpd);
	}
	scanf("%d",&q);
	while(q--){
		static int tp;
		scanf("%d",&tp);
		printf("%d\n",query(tp));
	}
	return 0;
}
```

---

## 作者：MagicalGirl_0d00 (赞：1)

D 题怒战 1h 终战胜，20 分钟不懂 F 拼尽全力无法战胜。

感谢 run_away 大神的讲解，滚回来写题解了。
#### sol
这个题在对值域做文章，所以我搞个值域线段树，线段树结点维护最大最小值。

节点的含义是值域为 $l,r$ 时是的答案最大最小值为多少。

不难注意到对于一个值域 $l,r$ 里面的答案是单调不减的，所以下面的修改就对了。

然后比分在 $L_i,R_i$ 之间的全部加一可以看作最小值 大于等于 $L_i$ 且最大值 小于等于 $R_i$ 的全部值 $+1$。

由于值域上的答案单调不减，所以区间一定是连续的。

然后维护一个单点查就好了。
#### code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,lzy[2000001],x,y;
struct dcz{
	int mn,mx;
}tr[2000001];
void pushup(int root){
	tr[root].mn=min(tr[root<<1].mn,tr[root<<1|1].mn);
	tr[root].mx=max(tr[root<<1].mx,tr[root<<1|1].mx);
}
void build(int l,int r,int root){
	if(l==r){
		tr[root].mn=tr[root].mx=l;
		return;
	}
	int mid=l+r>>1;
	build(l,mid,root<<1);
	build(mid+1,r,root<<1|1);
	pushup(root);
}
void pushdown(int root){
	if(lzy[root]){
		lzy[root<<1]+=lzy[root];
		lzy[root<<1|1]+=lzy[root];
		tr[root<<1].mx+=lzy[root];
		tr[root<<1|1].mx+=lzy[root];
		tr[root<<1].mn+=lzy[root];
		tr[root<<1|1].mn+=lzy[root];
		lzy[root]=0;
	}
}
void update(int L,int R,int l,int r,int root){
	if(tr[root].mx<L||tr[root].mn>R) return;
	if(L<=tr[root].mn&&tr[root].mx<=R){
		lzy[root]++;
		tr[root].mn++,tr[root].mx++;
		return;
	}
	pushdown(root);
	int mid=l+r>>1;
	update(L,R,l,mid,root<<1),update(L,R,mid+1,r,root<<1|1);
	pushup(root);
}
int faq(int wh,int l,int r,int root){
	if(l==r) return tr[root].mn;
	int mid=l+r>>1;
	pushdown(root);
	if(wh<=mid) return faq(wh,l,mid,root<<1);
	return faq(wh,mid+1,r,root<<1|1);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	build(1,500000,1);
	for(int i=1;i<=n;i++){
		cin>>x>>y;
		update(x,y,1,500000,1);
	}
	cin>>m;
	while(m--){
		cin>>x;
		cout<<faq(x,1,500000,1)<<"\n";
	}
	return 0;
}
```

---

## 作者：lovely_nst (赞：1)

# [AT_abc389_f [ABC389F] RG](https://www.luogu.com.cn/problem/AT_abc389_f)

## 前置

1. 线段树 + 二分

2. 平衡树

## 正文

### 方法一（线段树）

将所有询问离线下来并排序，记为数组 $a$。可证得在操作中 $a$ 满足单调不降性。

证明：操作 $[l,r]$ 只会对 $[l,r]$ 范围内的 $a_i$ 加一，修改后最大只能到 $r + 1$。若原本 $a_i>r$，那就一定满足 $a_i\ge r+1$，一定排在修改为的后面；若原本 $a_i<l$，那一定排在修改位的前面。因为原数组满足单调不降性，因此修改后也满足。

将 $a$ 放入线段树，线段树维护区间最小值，最大值，每次通过二分（因为单调不降）找到满足 $l\le a_x \le r$ 的所有 $x$ 并加一。时间复杂度 $O(n\log^2 n)$。

### 方法二（平衡树）

用 FHQ_Treap 实现值分裂，将 $[l,r]$ 的节点打上标记，在分裂和合并时下传标记。时间复杂度 $O(n\log n)$。

---

## 作者：_wsq_ (赞：1)

直接求显然不行，考虑维护一个数组（记为 $ans_i$），表示如果初始 rating 是 $i$，那么当前的 rating 是 $ans_i$。

那么一场比赛的效果就是将所有满足 $l\le ans_i\le r$ 的 $ans_i$ 加上 $1$。

如果中途某一时刻 $ans_i>ans_j(i<j)$，因为而每一场比赛最多加 $1$，即每次 $ans_j-ans_i$ 最多减少 $1$，加上初始时 $ans_i<ans_j(i<j)$，所以必定存在某一时刻 $ans_i=ans_j$。但 $ans_i=ans_j$ 之后显然 $ans_i$ 和 $ans_j$ 会永远相等，矛盾，因此不会出现 $ans_i>ans_j(i<j)$ 的情况。所以 $ans$ 数组始终单调不降。

也就是说，每一次比赛所加 $1$ 的部分一定是 $ans$ 数组里连续的一段区间。所以可以二分出这一段区间，然后用树状数组维护即可。

代码：

```cpp
#include <iostream>
using namespace std;
#define maxn 500005
int n,q,c[maxn+5];
int lowbit(int x){
    return x&-x;
}
void add(int x,int k){
    while(x<=maxn){
        c[x]+=k;
        x+=lowbit(x);
    }
    return;
}
int get(int x){
    int ret=0;
    while(x){
        ret+=c[x];
        x-=lowbit(x);
    }
    return ret;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for(int i=1;i<=maxn;i++){
        add(i,i);
        add(i+1,-i);
    }
    for(int i=1;i<=n;i++){
        int x,y,l1=1,r1=maxn,l2=1,r2=maxn;
        cin>>x>>y;
        while(l1<r1){
            int mid=(l1+r1)>>1;
            if(get(mid)<x){
                l1=mid+1;
            }
            else{
                r1=mid;
            }
        }
        while(l2<r2){
            int mid=(l2+r2)>>1;
            if(get(mid)<=y){
                l2=mid+1;
            }
            else{
                r2=mid;
            }
        }
        add(l1,1);
        add(l2,-1);
    }
    cin>>q;
    for(int i=1;i<=q;i++){
        int x;
        cin>>x;
        cout<<get(x)<<'\n';
    }
    return 0;
}
```

---

## 作者：XCDRF_ (赞：1)

# AT_abc389_f [ABC389F] Rated Range

upd $2025/1/19$：换一下链接，更改了描述。

[原题传送门](https://atcoder.jp/contests/abc389/tasks/abc389_f)

[更好的阅读体验](https://www.luogu.com.cn/article/bevxdff6)

## 题目大意

Takahashi 计划参加 $n$ 场 AtCoder 比赛。

在第 $i$ 场比赛（$1 \leq i \leq n$）中，如果他的评分在 $l_i$ 和 $r_i$ 之间（闭区间），他的评分将增加 $1$。

总共 $q$ 次查询，每次给出一个整数 $x$。假设 Takahashi 的初始评分为 $x$，求参加完 $n$ 场比赛后的评分。

## 解题思路

首先想到暴力思路，对于每次查询做一次模拟，时间复杂度 $O(nq)$。

一次查询做一次模拟并不好优化，此时观察到 $x$ 的值域不是很大。于是我们可以对于每个初始评分，计算最终评分。

这样做每个比赛就转化成了一次区间操作，二分维护区间的左右端点可以（查每个点在做完前面的操作后值是否在加分范围内），并在这段区间上加 $1$。区间加，单点查，可以用线段树或差分树状数组维护。每次操作时间复杂度 $O(\log x)$，总时间复杂度 $O(n\log x)$，可以通过本题。

## 参考代码

```cpp
#include<iostream>
#define mid (L+R>>1)
#define lowbit(i) (i&(-i))
using namespace std;
const int N=5e5+10;
int n,low,high,q;
int a[N]; 
struct BIT{
	int c[N];
	void add(int x,int y){
		for(;x<N;x+=lowbit(x)) c[x]+=y;
	} 
	int ask(int x){
		int ans=0;
		for(;x;x-=lowbit(x)) ans+=c[x];
		return ans;
	}
}TR;
int main(){
	cin>>n;
	for(int i=1,l,r;i<=n;i++){
		cin>>l>>r;
		int L=1,R=5e5+5;
		while(L<R){
			int val=mid+TR.ask(mid);
			if(val>=l) R=mid;
			else L=mid+1;
		}
		low=L;
		L=1,R=5e5+5;
        while(L<R) {
            int val=mid+TR.ask(mid);
            if(val>r) R=mid;
            else L=mid+1;
        }
		high=L-1;
		if(low<=high){
			TR.add(low,1);
			TR.add(high+1,-1);
			a[low]++;
			a[high+1]--;
		}
	}
	for(int i=1;i<=5e5;i++) a[i]+=a[i-1];
	cin>>q;
	while(q--){
		int x;
		cin>>x;
		cout<<(x+a[x])<<'\n';
	}
	return 0;
}
```

[AC 记录](https://atcoder.jp/contests/abc389/submissions/61850098)

---

## 作者：bluewindde (赞：1)

难评 $\green{525}\red{(2)}$。

把询问的点插入一维空间，每一场比赛将在区间 $[l, r]$ 之间的点向正方向平移一个单位。

注意到 K-D Tree 是一棵树，所以平移操作可以在树上打标记完成。操作结束后下放所有标记即可得到答案。

分析时间复杂度，因为只移动一个单位，所以平移操作不改变点的相对顺序，也就不破坏 K-D Tree 的结构，时间复杂度为 $O(q \log q)$。

以下是场后进行了微调的代码。

```cpp
#include <algorithm>
#include <iostream>

using namespace std;

const int QMAX = 3e5 + 5;

int n, q;
struct node {
    int x, w;
    friend inline bool operator<(const node &x, const node &y) {
        return x.x < y.x;
    }
} a[QMAX];
int b[QMAX];

struct {
    int l, r;
} seg[QMAX];
int ans[QMAX];

int rt;
struct {
    int ls, rs, l, r, dx;
} kd[QMAX];
static inline void move(int p, int dx) {
    if (!p)
        return;
    a[p].x += dx;
    kd[p].l += dx;
    kd[p].r += dx;
    kd[p].dx += dx;
}
static inline void pushdown(int p) {
    move(kd[p].ls, kd[p].dx);
    move(kd[p].rs, kd[p].dx);
    kd[p].dx = 0;
}
static inline void maintain(int p) {
    kd[p].l = kd[p].r = a[p].x;
    kd[p].dx = 0;
    if (kd[p].ls) {
        kd[p].l = min(kd[p].l, kd[kd[p].ls].l);
        kd[p].r = max(kd[p].r, kd[kd[p].ls].r);
    }
    if (kd[p].rs) {
        kd[p].l = min(kd[p].l, kd[kd[p].rs].l);
        kd[p].r = max(kd[p].r, kd[kd[p].rs].r);
    }
}
static inline int build(int l, int r) {
    if (l > r)
        return 0;
    int mid = (l + r) >> 1;
    nth_element(a + l, a + mid, a + r + 1);
    kd[mid].ls = build(l, mid - 1);
    kd[mid].rs = build(mid + 1, r);
    maintain(mid);
    return mid;
}
static inline void dfs(int p) {
    if (!p)
        return;
    pushdown(p);
    dfs(kd[p].ls);
    dfs(kd[p].rs);
}
static inline void rebuild() { // 事实上不需要重构
    dfs(rt);
    rt = build(1, q);
}
static inline void move(int l, int r, int p) {
    if (!p || r < kd[p].l || l > kd[p].r)
        return;
    if (l <= kd[p].l && kd[p].r <= r)
        return move(p, 1);
    pushdown(p);
    if (l <= a[p].x && a[p].x <= r)
        ++a[p].x;
    move(l, r, kd[p].ls);
    move(l, r, kd[p].rs);
    maintain(p);
}

static inline void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> seg[i].l >> seg[i].r;
    cin >> q;
    for (int i = 1; i <= q; ++i) {
        int x;
        cin >> x;
        a[i] = {x, i};
    }
    rt = build(1, q);
    for (int i = 1; i <= n; ++i)
        move(seg[i].l, seg[i].r, rt);
    dfs(rt);
    for (int i = 1; i <= q; ++i)
        ans[a[i].w] = a[i].x;
    for (int i = 1; i <= q; ++i)
        cout << ans[i] << '\n';
}

signed main() {
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    cout.flush();
    return 0;
}
```

---

## 作者：AKPC (赞：0)

简单题。

注意到可以离线，那么不妨试试把 $X$ 全部从小到大排序之后做，发现无论多少次操作后序列是保持单调不降的。

利用这个性质，只需要用一个数据结构维护三种操作：

- 区间加 $1$。
- 找到第一个 $\geq k$ 的位置。
- 找到最后一个 $\leq k$ 的位置。

容易想到线段树维护，第一个操作打懒标记，第二、三个操作用线段树上二分维护。注意最后还需要查询每个位置最终的值，所以要在最后做一次全局 `pushdown` 操作。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define fr first
#define sc second
const int N=5e5+5;
int n,l[N],r[N],q,a[N],ans[N];
pair<int,int>qr[N];
struct sgmt{
    #define lc(x) (x<<1)
    #define rc(x) (x<<1|1)
    #define mid(l,r) ((l+r)>>1)
    struct dots{
        int mx,mn;
        dots operator+(dots _)const{
            return {max(_.mx,mx),min(_.mn,mn)};
        }
    }t[N<<4];
    int tag[N<<4];
    void build(int x,int l,int r){
        if (l==r){
            t[x].mx=t[x].mn=a[l];
            return;
        }
        build(lc(x),l,mid(l,r));
        build(rc(x),mid(l,r)+1,r);
        t[x]=t[lc(x)]+t[rc(x)];
    }
    void pd(int x){
        tag[lc(x)]+=tag[x],t[lc(x)].mx+=tag[x],t[lc(x)].mn+=tag[x];
        tag[rc(x)]+=tag[x],t[rc(x)].mx+=tag[x],t[rc(x)].mn+=tag[x];
        tag[x]=0;
    }
    int fdl(int x,int l,int r,int k){
        pd(x);
        if (l==r){
            if (t[x].mx<k) return q+1;
            return l;
        }
        if (t[lc(x)].mx<k) return fdl(rc(x),mid(l,r)+1,r,k);
        else return fdl(lc(x),l,mid(l,r),k);
    }
    int fdr(int x,int l,int r,int k){
        pd(x);
        if (l==r){
            if (t[x].mx>k) return 0;
            return l;
        }
        if (t[rc(x)].mn<=k) return fdr(rc(x),mid(l,r)+1,r,k);
        else return fdr(lc(x),l,mid(l,r),k);
    }
    void add(int x,int l,int r,int ql,int qr,int k){
        pd(x);
        if (ql<=l&&r<=qr){
            tag[x]+=k,t[x].mx+=k,t[x].mn+=k;
            return;
        }
        if (ql<=mid(l,r)) add(lc(x),l,mid(l,r),ql,qr,k);
        if (qr>mid(l,r)) add(rc(x),mid(l,r)+1,r,ql,qr,k);
        t[x]=t[lc(x)]+t[rc(x)];
    }
    void reset(int x,int l,int r){
        if (l==r) return;
        pd(x),reset(lc(x),l,mid(l,r)),reset(rc(x),mid(l,r)+1,r);
    }
    int get(int x,int l,int r,int k){
        if (l==r) return t[x].mx;
        if (k<=mid(l,r)) return get(lc(x),l,mid(l,r),k);
        else return get(rc(x),mid(l,r)+1,r,k);
    }
}book;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for (int i=1;i<=n;i++)
        cin>>l[i]>>r[i];
    cin>>q;
    for (int i=1;i<=q;i++)
        cin>>qr[i].fr,qr[i].sc=i;
    sort(qr+1,qr+q+1);
    for (int i=1;i<=q;i++)
        a[i]=qr[i].fr;
    book.build(1,1,q);
    for (int i=1;i<=n;i++){
        int L=book.fdl(1,1,q,l[i]);
        int R=book.fdr(1,1,q,r[i]);
        if (L<=R) book.add(1,1,q,L,R,1);
    }
    book.reset(1,1,q);
    for (int i=1;i<=q;i++)
        ans[qr[i].sc]=book.get(1,1,q,i);
    for (int i=1;i<=q;i++)
        cout<<ans[i]<<'\n';
    return 0;
}
```

---

## 作者：small_lemon_qwq (赞：0)

让 $f_x$ 表示初始 Rated 为 $x$ 参加完所有比赛能涨多少分。

证明 $\{x+f_x\}$ 有单调性：
> 设 $y\le x$
>
> 对于一场比赛 $[L,R]$，有如下情况：
> + $L\le y\le R<x$，参加完后仍然满足 $y+1\le x$
> + $L\le y \le x\le R$，参加完后仍然满足 $y+1\le x+1$
> + $ y \le x\le L$，参加完后仍然满足 $y\le x$
>
> 所以 $\{x+f_x\}$ 具有单调性。

因此可以二分比赛 $[L,R]$，原始 Rated $\in[l,r]$ 能涨分。

用树状数组维护即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,a[500005];
void add(int d,int x){
	while(d<=500000){
		a[d]+=x;
		d+=d&-d;
	}
}
int get(int d){
	int sum=0;
	while(d){
		sum+=a[d];
		d-=d&-d;
	}
	return sum;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		int l,r;
		cin>>l>>r;
		int L=1,R=500000;
		while(L<=R){
			int mid=(L+R)>>1;
			if(get(mid)+mid>=l)R=mid-1;
			else L=mid+1;
		}
		l=R+1;
		L=1,R=500000;
		while(L<=R){
			int mid=(L+R)>>1;
			if(get(mid)+mid<=r)L=mid+1;
			else R=mid-1;
		}
		r=L-1;
		if(r<l)continue;
		add(l,1);
		add(r+1,-1);
	}
	cin>>m;
	while(m--){
		int x;
		cin>>x;
		cout<<x+get(x)<<"\n";
	}
	return 0;
}
```

---

