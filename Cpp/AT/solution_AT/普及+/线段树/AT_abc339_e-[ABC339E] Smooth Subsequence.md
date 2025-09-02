# [ABC339E] Smooth Subsequence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc339/tasks/abc339_e

長さ $ N $ の数列 $ A\ =\ (A_1,\ A_2,\ \ldots,\ A_N) $ が与えられます。

$ A $ の部分列であって、隣接する $ 2 $ 項の差の絶対値が $ D $ 以下であるようなものの長さの最大値を求めてください。

ただし、数列 $ A $ の部分列とは、$ A $ の要素を $ 0 $ 個以上選んで削除し、残った要素を元の順序を保って並べた数列のことを指します。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 5\ \times\ 10^5 $
- $ 0\ \leq\ D\ \leq\ 5\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 5\ \times\ 10^5 $
- 入力される数値はすべて整数
 
### Sample Explanation 1

$ A $ の部分列 $ (3,\ 1,\ 2) $ は隣接する $ 2 $ 項の差の絶対値が $ 2 $ 以下です。

## 样例 #1

### 输入

```
4 2
3 5 1 2```

### 输出

```
3```

## 样例 #2

### 输入

```
5 10
10 20 100 110 120```

### 输出

```
3```

## 样例 #3

### 输入

```
11 7
21 10 3 19 28 12 11 3 3 15 16```

### 输出

```
6```

# 题解

## 作者：_JF_ (赞：9)

[Link](https://www.luogu.com.cn/problem/AT_abc339_e)

很一眼的题。

考虑动态规划，设 $dp_i$ 表示以当前这个位置为结尾能取到的最大值，满足条件的 $j$ 仅当 $|a_i-a_j|\le D$ 且 $i<j$，转移就是：

$$dp_i=\max(dp_i,dp_j+
1)$$

拆开那个绝对值的式子，发现 $a_j$ 的范围在 $[a_i-D,a_i+D]$ 之间，发现值域较小，考虑线段树优化，只用在枚举 $i$ 的时候对值域做线段树维护最大值，直接查询能取到的区间的最大值就没了，这时候线段树里面的值的更新时间都小于 $i$，所以符合我们的状态，然后对线段树进行更新就完了。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =2e6+10;
int n,D,ans=1;
int d[N],a[N],dp[N];
void update(int l,int r,int s,int t,int p,int change){
	if(l<=s&&t<=r)	{d[p]=max(d[p],change);return ;}
	int mid=(s+t)>>1;
	if(l<=mid)	update(l,r,s,mid,p<<1,change);
	if(r>mid)	update(l,r,mid+1,t,p<<1|1,change);
	d[p]=max(d[p<<1],d[p<<1|1]);
}
int Query(int l,int r,int s,int t,int p){
	if(l<=s&&t<=r)	return d[p];
	int mid=(s+t)>>1,ans=0;
	if(l<=mid)	ans=max(ans,Query(l,r,s,mid,p<<1));
	if(r>mid)	ans=max(ans,Query(l,r,mid+1,t,p<<1|1));
	return ans;
}
int main(){
	cin>>n>>D;
	for(int i=1;i<=n;i++)	cin>>a[i];
	for(int i=1;i<=n;i++){
		dp[i]=max(dp[i],Query(max(1,a[i]-D),min(a[i]+D,500000),1,500000,1))+1;
		update(a[i],a[i],1,500000,1,dp[i]);
		ans=max(ans,dp[i]);
	}
	cout<<ans<<endl;
} 
```

---

## 作者：cjh20090318 (赞：9)

简单的 E，使我先跳过 D。

## 题意

给一个 $N$ 个数的序列 $A$，你需要找到一个子序列满足相邻两个数之差的绝对值不超过 $D$，求子序列可能的最大长度。

## 分析

考虑动态规划。

### 状态设计

设 $f_i$ 表示以第 $i$ 个数结尾最长的子序列长度。

### 转移方程

$$
f_i = 1 + \max\limits_{j<i \land \vert A_i - A_j \vert \le D} f_j
$$

观察到这是一个 $O(n^2)$ 的转移，时间复杂度不可接受，考虑优化。

$1 \le A_i \le 5 \times 10^5$，并且转移方程中取最大值，可以用线段树优化。

时间复杂度 $O(n \log A_i)$，可以通过此题。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<algorithm>
#define MAXN 500005
#define lson (rt<<1)
#define rson (rt<<1|1)
using namespace std;
using ci=const int;
const int A=500000;//A 的最大值。
int n,d;
int mx[MAXN<<2];//线段树维护最大值
void update(ci rt,ci l,ci r,ci pos,ci val){
	if(l==r && l==pos){mx[rt]=max(mx[rt],val);return;}
	int mid=(l+r)>>1;
	if(pos<=mid) update(lson,l,mid,pos,val);
	else update(rson,mid+1,r,pos,val);
	mx[rt]=max(mx[lson],mx[rson]);
}
int query(ci rt,ci l,ci r,ci L,ci R){
	if(L<=l && r<=R) return mx[rt];
	int mid=(l+r)>>1,ret=0;
	if(L<=mid) ret=max(ret,query(lson,l,mid,L,R));
	if(mid<R) ret=max(ret,query(rson,mid+1,r,L,R));
	return ret;
}
int main(){
	scanf("%d%d",&n,&d);
	for(int i=1,a;i<=n;i++)
		scanf("%d",&a),update(1,1,A,a,query(1,1,A,max(a-d,1),min(a+d,A))+1);//求出 f_i 更新最大值。
	printf("%d\n",query(1,1,A,1,A));//查询整个动态规划数组的最大值。
	return 0;
}
```

---

## 作者：_determination_ (赞：4)

感觉比较版的 dp，建议评蓝。

我们设 $f_x$ 为以第 $x$ 个数为结尾的最长序列长度，那么我们可以枚举全部符合条件的位置进行转移。

大概是这样的？

$$ f_x=\max_{i=1}^{x-1}\left [ \left | a_i-a_x \right | \le  D \right ]\times (f_i+1) $$

然后我们发现转移只与 $a_i$ 有关，而值域比较小，所以我们可以建一颗线段树来维护，这样我们就得到了 $O(n\log n)$ 的做法。

[代码。](https://atcoder.jp/contests/abc339/submissions/49956772)

---

## 作者：No_Rest (赞：3)

ABC 第一次用线段树 AC 题，纪念一下。

# 思路

看到这道题，很容易想到 dp。

令 $f_i$ 表示前 $i$ 个数，选第 $i$ 个数的最长子序列，则 $f_i = \max\{f_j+1\}$ $(1 \le j \le i - 1,a_i - d \le a_j \le a_i + d)$，最后的答案是 $f_1 \cdots f_n$ 的最大值。

然后我看见 $1 \le a_i \le 5 \times 10^5$ 后就瞬间想到线段树优化 dp 了。

我们可以将每个算出的 $f_i$ 扔到线段树里第 $a_i$ 个位置，这样 $f_i$ 就等于线段树中第 $a_i - d \sim a_i + d$ 个位置中的最大值加 $1$（这些位置上的 $f_j$ 都是满足 $1 \le j \le i - 1,a_i - d \le a_j \le a_i + d$ 的）。维护一棵单点修改区间查询的线段树即可。

时间复杂度 $\mathcal O(n \log \max\{a_i\})$。

# 代码

代码很丑，勿喷 qwq。

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
	ll l, r, maxn;
}t[maxn << 2];
ll n = read(), d = read(), a[maxn], mx, f[maxn];
void pushup(ll x){ t[x].maxn = max(t[ls].maxn, t[rs].maxn); }//线段树部分蒟蒻就不加注释了
void build(ll x, ll l, ll r){
	t[x].l = l, t[x].r = r;
	if(l == r){
		t[x].maxn = 0;
		return;
	}
	ll mid = (l + r) >> 1;
	build(ls, l, mid), build(rs, mid + 1, r);
	pushup(x);
}
void update(ll x, ll id, ll v){
	if(t[x].l == t[x].r){
		t[x].maxn = max(t[x].maxn, v);
		return;
	}
	ll mid = (t[x].l + t[x].r) >> 1;
	if(id <= mid) update(ls, id, v);
	else update(rs, id, v);
	pushup(x);
}
ll query(ll x, ll l, ll r){
	if(l <= t[x].l && t[x].r <= r) return t[x].maxn;
	ll ans = 0, mid = (t[x].l + t[x].r) >> 1;
	if(l <= mid) ans = max(ans, query(ls, l, r));
	if(r > mid) ans = max(ans, query(rs, l, r));
	return ans;
}
int main(){
	for(ll i = 1; i <= n; ++i) a[i] = read(), mx = max(mx, a[i]);
	build(1, 1, mx);
	for(ll i = 1; i <= n; ++i){
		f[i] = query(1, max(1ll, a[i] - d), min(mx, a[i] + d)) + 1;//f[i] 等于线段树中第 a[i] - d ~ a[i] + d 个位置中的最大值加 1
		update(1, a[i], f[i]);//将 f[i] 扔进线段树第 a[i] 个位置上
	}
	printf("%lld", query(1, 1, mx));//f[1] ~ f[n] 都扔进去了，所以答案就是整棵线段树的最大值
    return 0;
}
```

---

## 作者：Milthm (赞：2)

注：以下称 $a$ 序列为 $b$。

看到这个最长子序列，就很容易想到动态规划。

所以我们设 $dp_i$ 表示前 $i$ 个数相邻两数绝对差不超过 $d$ 的最长子序列。设 $k_i$ 表示目前所有 $dp_j(j<i)$ 中 $b_j$ 值与 $b_i$ 绝对差不超过 $d$ 的最大值，则 $dp_i=k_i+1$。

这东西直接转移是 $O(n^2)$ 的，显然会超时。

考虑你有一个数组，此时如果当前 $dp_i$ 值转移完了，你就把它的值放到数组第 $b_i$ 个位置（与原来的数取最大值）。然后每次 $k_i$ 实际上就是数组上 $b_i-d$ 至 $b_i+d$ 之间的最大值。

你观察这个过程，发现可以用线段树优化（你甚至不需要建树）。时间复杂度 $O(n \log n)$。

### AC code

实现的时候 $b_i-d$ 要判越界。

```cpp
#include<bits/stdc++.h>
#define N 1000005
#define int long long
using namespace std;
int n,d,b[N],dp[N],ans,a[N*4];
void update(int x,int l,int r,int k,int qwq){
	if(l==r){
		a[x]=max(a[x],qwq);return;
	}
	int mid=(l+r)>>1;
	if(k<=mid)update(x*2,l,mid,k,qwq);
	else update(x*2+1,mid+1,r,k,qwq);
	a[x]=max(a[x*2],a[x*2+1]);
}
int query(int x,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr)return a[x];
	int mid=(l+r)>>1,ans=0;
	if(ql<=mid)ans=max(ans,query(x*2,l,mid,ql,qr));
	if(qr>mid)ans=max(ans,query(x*2+1,mid+1,r,ql,qr));
	return ans;
} 
signed main(){
	cin>>n>>d;
	for(int i=1;i<=n;++i)scanf("%lld",&b[i]);
	for(int i=1;i<=n;++i){
		dp[i]=query(1,1,N-4,max(1ll,b[i]-d),b[i]+d)+1;
		update(1,1,N-4,b[i],dp[i]);ans=max(ans,dp[i]);
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：Elairin176 (赞：2)

[传送门](https://www.luogu.com.cn/problem/AT_abc339_e)    
是一道[原题](https://www.luogu.com.cn/problem/AT_abl_d)。      
## 题面
求出 $a$ 中满足相邻两项绝对值之差不超过 $D$ 的最长**子序列**长度。     
## 解法
一眼 dp。  
我们设 $f_i$ 为表示以 $a_i$ 结尾的最长子序列长度，则有 $f_i=\max\limits_{1\le j<i}[\left|a_i-a_j\right|\le D](f_j+1)$，则答案为 $\max\limits_{i=1}^nf_i$。    
发现这个式子暴力求解是 $O(n^2)$ 的，所以考虑优化。    
我们可以对 $a_i$ 以 $f_i$ 为权值建一棵权值线段树，每次求 $f_i$ 只需要查询 $[\max(a_i-D,1),\min(a_i+D,n)]$ 区间内 $f$ 的最大值即可，处理完后需要将 $f_i$ 插进去。     
CODE：    
```cpp
//完整缺省源请见洛谷云剪贴板 jo5j6ogx
cst int N=5e5;
int ans,n,d,a[N+10],tree[(N<<2)+10],f[N+10];
il int lc(int x){
	ret x<<1;
}
il int rc(int x){
	ret x<<1|1;
}
il void pushup(int x){
	tree[x]=_max<int>(tree[lc(x)],tree[rc(x)]);
}
il void change(int x,int y,int l,int r,int k){
	if(l>x||r<x||l>r){
		ret;
	}
	if(l==r&&l==x){
		tree[k]=_max<int>(tree[k],y);
		ret;
	}
	int m=l+r>>1;
	change(x,y,l,m,lc(k));
	change(x,y,m+1,r,rc(k));
	pushup(k);
}
il int query(int x,int y,int l,int r,int k){
	if(l>y||r<x||l>r){
		ret 0;
	}
	if(l>=x&&r<=y){
		ret tree[k];
	}
	int m=l+r>>1;
	ret _max<int>(query(x,y,l,m,lc(k)),query(x,y,m+1,r,rc(k)));
}
int main(void){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	n=read<int>();
	d=read<int>();
	for(int i=1;i<=n;i++){
		a[i]=read<int>();
	}
	for(int i=1;i<=n;i++){
		int l=_max<int>(1,a[i]-d);
		int r=_min<int>(N,a[i]+d);
		f[i]=query(l,r,1,N,1)+1;
		change(a[i],f[i],1,N,1);
	}
	for(int i=1;i<=n;i++){
		ans=_max<int>(ans,f[i]);
	}
	write(ans);
	ret 0;
}
```


---

## 作者：fcy20180201 (赞：1)

## 思路
考虑 DP。$dp_i$ 表示考虑前 $i$ 个值，选择 $a_i$ 能获得的最大长度。转移方程为：
$$dp_i=(\max_{1 \le j \lt i \cap |a_i-a_j|\le d}dp_j)+1$$

其中 $j$ 相当于前一个选的值的下标。

发现 $a_j$ 是一段连续值，可以用权值线段树维护转移。线段树中区间 $[l,r]$ 上记录的是在考虑到 $a_i$ 之前满足 $l \le a_j \le r$ 的 $j$ 中 $dp_j$ 的最大值。得到 $dp_i$ 后在线段树上更新一下即可。

## 代码
本代码中省略了 $dp$ 数组。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ls cur<<1
#define rs cur<<1|1
const int inf=5e5;
int n,d,a[500005],tr[2000005];//线段树记得开 4 倍空间

void update(int cur,int l,int r,int loc,int val){//更新
	if(l==r){tr[cur]=max(tr[cur],val);return ;}
	int mid=(l+r)>>1;
	if(loc<=mid)update(ls,l,mid,loc,val);
	else update(rs,mid+1,r,loc,val);
	tr[cur]=max(tr[ls],tr[rs]);return ;
}

int query(int cur,int l,int r,int ql,int qr){//查询
	if(ql<=l && r<=qr)return tr[cur];
	int mid=(l+r)>>1,res=0;
	if(ql<=mid)res=max(res,query(ls,l,mid,ql,qr));
	if(qr>mid)res=max(res,query(rs,mid+1,r,ql,qr));
	return res;
}

int main(){
	scanf("%d%d",&n,&d);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	update(1,1,inf,a[1],1);//先更新第一个点
	for(int i=2;i<=n;i++)update(1,1,inf,a[i],query(1,1,inf,max(1,a[i]-d),min(inf,a[i]+d))+1);
	//转移 + 线段树上更新，别忘了判边界
	printf("%d",tr[1]);//直接输出所有 dp 值的最大值
	return 0;
}
```

---

## 作者：SJZ2010 (赞：1)

## 题意

给出一个序列 $A$，求满足相邻两项的绝对差 $\le D$ 的 $A$ 的最长子序列的长度。

## 做法

首先这题的 DP 非常一眼，转移方程也非常一眼，设 $dp_i$ 表示以 $A_i$ 结尾的最长子序列的长度，那么 $dp_i=\max\{dp_j|(1 \le j \le i) \wedge (|A_i-A_j| \le D)\}+1$。

这个 DP 是 $O(n^2)$ 的，考虑优化。

我们可以发现 $|A_i-A_j| \le D$ 所对应的 $A_j$ 在数轴上表示连续的一段，与 $1 \le j \le i$ 这个条件结合，我们可以考虑将数字一个一个加到数轴上，然后查询数轴上 $[A_i-D,A_i+D]$ 这一段的信息。

为了方便查询，我们稍微变动一下 DP 转移方程，改为 $dp_x$ 表示以**数字** $x$ 结尾的最长子序列长度。那么 $dp_x = \overset{x+D}{\underset{y=x-D}{\max}} dp_y+1$，刚好对应的是数轴上的一段，可以用线段树优化，最后的答案是 $\overset{n}{\underset{i=1}{\max dp_{A_i}}}$。时间复杂度 $O(n \log n)$。

代码：

```cpp
#include <cstdio>
#include <algorithm>

const int N = 5e5 + 5;

int n, d, a[N], T[N << 2];

inline void modify(int idx, int s, int t, int now, int v) // 修改点上的 DP 值
{
	if (s == t)
	{
		T[now] = std::max(T[now], v);
		return;
	}
	int mid = (s + t) >> 1;
	if (mid >= idx)
		modify(idx, s, mid, now << 1, v);
	else
		modify(idx, mid + 1, t, now << 1 | 1, v);
	T[now] = std::max(T[now << 1], T[now << 1 | 1]);
}
inline int query(int l, int r, int s, int t, int now) // 查询区间最大值
{
	if (l <= s && t <= r)
		return T[now];
	int mid = (s + t) >> 1;
	int res(0);
	if (mid >= l)
		res = query(l, r, s, mid, now << 1);
	if (mid < r)
		res = std::max(res, query(l, r, mid + 1, t, now << 1 | 1));
	return res;
}

int main()
{
	scanf("%d %d", &n, &d);
	int mx(0);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		mx = std::max(a[i], mx);
	}
	int ans(0), cur;
	for (int i = 1; i <= n; i++)
	{
		if (i == 1)
		{
			ans = 1;
			modify(a[1], 1, mx, 1, 1);
			continue;
		}
		cur = query(std::max(1, a[i] - d), std::min(mx, a[i] + d), 1, mx, 1) + 1; // 转移，query 返回的答案是 max(dp[a[i]-d] ... dp[a[i]+d])
		ans = std::max(cur, ans); // 更新最后答案
		modify(a[i], 1, mx, 1, cur); // 更新这个点的 DP 值
	}
	printf("%d\n", ans);
	return 0;
}

```

---

## 作者：Lucky_Cloud (赞：1)


[题传](https://www.luogu.com.cn/problem/AT_abc339_e)。

[更好的阅读体验](https://www.cnblogs.com/luckycloud/p/18005312)。

## 题意
给你一个长度为 $N$ 的序列 $A = (A_1, A_2, \ldots, A_N)$。

求长度为 $A$ 的子序列的最大长度，使得任意两个相邻项之间的绝对差最多为 $D$。

## 分析

设 $f[i]$ 为以 $A$ 中值为 $i$ 为结尾的子序列的最大长度。则有：

$$f[i] = \max(f[j]) + 1$$

其中 $i - d \le j \le i + d$。

代码很容易出来：

```cpp
for (int i = 1; i <= n; ++i) {
	int x = 0;
	for (int j = max(a[i] - d, 1); j <= min(a[i] + d, mx); ++j) x = min(f[j] + 1, x);
	f[a[i]] = x;
}
```
$mx$ 为 $A$ 中的最大值。

复杂度 $O(n^2)$。我们不能接受。

其中这一段：

```cpp
for (int j = max(a[i] - d, 1); j <= min(a[i] + d, mx); ++j) x = min(f[j] + 1, x);
```

相当于在找一个区间内的 $f$ 最大值。

但是，考虑到 $f[i]$ 会变化。我们使用线段树板子维护这个最大值。

时间复杂度：$O(n\log n)$

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define ls (p << 1)
#define rs ((p << 1) + 1)
using namespace std;

const int N = 5e5 + 5;
int n, d, f[N], a[N];
struct tree {
	int l, r;
	int mx;
} tr[N * 4];

void pushup(int p) {
	tr[p].mx = max(tr[ls].mx, tr[rs].mx);
}

void build(int l, int r, int p) {
	tr[p].l = l, tr[p].r = r, tr[p].mx = 0;
	if (l == r) { return ; }
	int mid = (l + r) >> 1;
	build(l, mid, ls);
	build(mid + 1, r, rs);
}

void change(int x, int p) {
	int l = tr[p].l, r = tr[p].r;
	if (l == r) {
		tr[p].mx = f[x];
		return ;
	}
	int mid = (l + r) >> 1;
	if (x <= mid) change(x, ls);
	else change(x, rs);
	pushup(p);
}

int que(int L, int R, int p) {
	int l = tr[p].l, r = tr[p].r;
	if (L <= l && r <= R) return tr[p].mx;
	int mid = (l + r) >> 1;
	int res = -1e9;
	if (L <= mid) res = max(res, que(L, R, ls));
	if (R > mid) res = max(res, que(L, R, rs));
	return res;
}

signed main() {
	cin >> n >> d;
	int mx = 0;
	for (int i = 1; i <= n; ++i) cin >> a[i], mx = max(mx, a[i]);
	build(1, mx, 1);
	int ans = -1e9;
	for (int i = 1; i <= n; ++i) {
		int x = a[i];
		f[x] = que(max(1ll, x - d), min(mx, x + d), 1) + 1;
		change(x, 1);
		ans = max(ans, f[x]);
	}
	cout << ans;
	return 0;
}
```

---

## 作者：BugGod (赞：0)

首先考虑朴素的 dp。设 $dp_i$ 代表前 $i$ 个数字的最大答案，则 $dp_i$ 可以由满足：$j<i,|a_i-a_j|\le d$ 的每一个 $j$ 转移，得到 $O(n^2)$ 的暴力代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define mp make_pair
#define fi first
#define se second
void IOS()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
void file(string file_name)
{
	freopen((file_name+".in").c_str(),"r",stdin);
	freopen((file_name+".out").c_str(),"w",stdout);
}
int n,d,a[500010],dp[500010],ans;
signed main()
{
	//IOS();
	//file("");
	cin>>n>>d;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)dp[i]=1;
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<i;j++)
		{
			if(abs(a[i]-a[j])<=d)dp[i]=max(dp[i],dp[j]+1);
		}
	}
	for(int i=1;i<=n;i++)ans=max(ans,dp[i]);
	cout<<ans;
	return 0;
}
```

成功的只过了样例的测试点。

考虑优化，我们发现每次转移 $dp_i$ 时都像是不认识 $dp_1\sim dp_{i-1}$ 一样，重新认识一遍，没有充分利用 $dp_{i-1}$ 转移时用到的信息，于是我们可以开一棵权值线段树。为什么时权值线段树？因为我们想要消去绝对值，所有转移范围在 $a_i-d\sim a_i+d$ 间，可以通过权值线段树轻松维护，每次查询这个范围内前面所有 $dp$ 的最大值即可。每次修改时，在 $a_i$ 的位置加上当前 $dp_i+1$（转移式子中的 $1$）即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define this_is_lyd_s_mark puts("Huangyuzhuo AKs IOI")
void IOS()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
void file(string file_name)
{
	freopen((file_name+".in").c_str(),"r",stdin);
	freopen((file_name+".out").c_str(),"w",stdout);
}
int n,d,a[500010];
#define ls(p)p<<1
#define rs(p)p<<1|1
#define val(p)tree[p].val
struct seg
{
	struct Tree
	{
		int val;
	}tree[2000010];
	void pushup(int p)
	{
		val(p)=max(val(ls(p)),val(rs(p)));
	}
	void build(int p=1,int l=1,int r=500000)
	{
		if(l==r)
		{
			val(p)=0;
			return ;
		}
		int mid=l+r>>1;
		build(ls(p),l,mid);
		build(rs(p),mid+1,r);
		pushup(p);
		//while(541254)this_is_lyd_s_mark;
	}
	void add(int x,int k,int p=1,int l=1,int r=500000)
	{
		if(l==r)
		{
			val(p)=max(val(p),k);
			return ;
		}
		int mid=l+r>>1;
		if(mid>=x)add(x,k,ls(p),l,mid);
		if(mid<x)add(x,k,rs(p),mid+1,r);
		pushup(p);
	}
	int query(int ql,int qr,int p=1,int l=1,int r=500000)
	{
		if(ql<=l&&r<=qr)return val(p);
		int mid=l+r>>1,ans=0;
		if(mid>=ql)ans=max(ans,query(ql,qr,ls(p),l,mid));
		if(mid<qr)ans=max(ans,query(ql,qr,rs(p),mid+1,r));
		return ans;
	}
}t;
signed main()
{
	//IOS();
	//file("");
	cin>>n>>d;
	for(int i=1;i<=n;i++)cin>>a[i];
	t.build();
	for(int i=1;i<=n;i++)
	{
		int l=max(1ll,a[i]-d),r=min(500000ll,a[i]+d);
		t.add(a[i],t.query(l,r)+1);
	}
	cout<<t.query(1,500000);
	return 0;
}
```

---

## 作者：lovely_hyzhuo (赞：0)

显然是一个 dp。

考虑 $O(n^2)$ 的暴力。

依据题意可得转移方程。

若 $|a_i-a_j| \leq d$，则 $dp_i=\max dp_j+1$。

考虑优化。

显然可以考虑建一颗权值线段树，在线段树上的合法位置上查询最大值。

完整代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[500010];
int dp[500010];
struct node
{
	int l,r;
	int sum;
	int lazy;
}tr[2000010];
void push_up(int p)
{
	tr[p].sum=max(tr[p*2].sum,tr[p*2+1].sum);
}
void build(int l,int r,int p)
{
	tr[p].l=l,tr[p].r=r;
	if(l==r)
	{
		return;
	}
	int mid=(l+r)/2;
	build(l,mid,p*2);
	build(mid+1,r,p*2+1);
	push_up(p);
}
void update(int l,int r,int k,int p)
{
	if(tr[p].l>=l&&tr[p].r<=r)
	{
		tr[p].sum=max(tr[p].sum,k);
		return;
	}
	int mid=(tr[p].l+tr[p].r)/2;
	if(mid>=l)
		update(l,r,k,p*2);
	if(mid<r)
		update(l,r,k,p*2+1);
	push_up(p);
}
int query(int l,int r,int p)
{
	if(tr[p].l>=l&&tr[p].r<=r)
		return tr[p].sum;
	int mid=(tr[p].l+tr[p].r)/2,sum=0;
	if(mid>=l)
		sum=max(sum,query(l,r,p*2));
	if(mid<r)
		sum=max(sum,query(l,r,p*2+1));
	return sum;
}
signed main()
{
	int n,d;
	cin>>n>>d;
	for(int i=1;i<=n;i++)
		cin>>a[i],dp[i]=1;
	build(0,500000,1);
	for(int i=n-1;i>=1;i--)
	{
		update(a[i+1],a[i+1],dp[i+1],1);
		dp[i]=max(dp[i],query(max(0LL,a[i]-d),min(500000LL,a[i]+d),1)+1);
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		ans=max(ans,dp[i]);
	cout<<ans;
	return 0;
}
```


---

## 作者：a1co0av5ce5az1cz0ap_ (赞：0)

## 题意
给出一个序列 $a$ 和一个数 $d$，求最长的相邻两项差不超过 $d$ 的子序列。
## 做法
有一个很一眼的 dp：设 $f_{i,j}$ 表示序列前 $i$ 个数中，选择子序列的最后一个数为 $j$ 时子序列的最大长度。

则 $f_{i,a_i}=\max\limits_{j=a_i-d}^{a_i+d}f_{i-1,j}+1$，其余 $f_{i,j}=f_{i-1,j}$。

答案为 $\max\limits_i f_{n,i}$。

首先可以发现，第一维可以直接去掉，这样每次就只有一个数的修改。

这是一个区间查 $\max$ 单点修改的问题，于是可以用线段树维护。

于是就做完了。

---

## 作者：LaoXu666 (赞：0)

这题很容易想得到 DP。

很容易想出暴力的转移方程：$f_i \gets \displaystyle \max f_j + 1 (0 \leqslant j < i,|a_j - a_i| \leqslant D)$ 

数据范围很大，这个 DP 的复杂度是 $\Theta(N^2)$ 的，肯定 TLE。

我们可以想到用线段树优化。

首先，因为转移方程是跟 $a_i$ 有关的，所以线段树编辑的时候可以用 $a_i$。然后，求最大值区间为 $[a_i -D, a_i+D]$。

现在就可以写出代码：

```cpp
#include <iostream>

typedef int LL;

class SegmentTree {
public:
	LL Max[2000005];

	void Edit(LL NodeId, LL L, LL R, LL Pos, LL Val) {
		if (L == R) {
			Max[NodeId] = std::max(Max[NodeId], Val);
			return;
		}
		LL Mid = (L + R) / 2;
		if (Pos <= Mid) {
			Edit(NodeId * 2, L, Mid, Pos, Val);
		} else {
			Edit(NodeId * 2 + 1, Mid + 1, R, Pos, Val);
		}
		Max[NodeId] = std::max(Max[NodeId * 2], Max[NodeId * 2 + 1]);
	}

	LL GetMax(LL NodeId, LL L, LL R, LL QueryL, LL QueryR) {
		if (QueryL <= L && R <= QueryR) {
			return Max[NodeId];
		}
		if (QueryL > R || QueryR < L) return 0;
		LL Mid = (L + R) / 2;
		return std::max(GetMax(NodeId * 2, L, Mid, QueryL, QueryR),
						GetMax(NodeId * 2 + 1, Mid + 1, R, QueryL, QueryR));
	}
} ABC339E;

int N, D;
int Arr[500005], DP[500005];

int main() {
	std::cin >> N >> D;
	for (int i = 1; i <= N; i++) std::cin >> Arr[i];
	int Res = 0;
	for (int i = 1; i <= N; i++) {
		DP[i] = ABC339E.GetMax(1, 1, 500000, std::max(Arr[i] - D, 1), std::min(Arr[i] + D, 500000)) + 1;
		ABC339E.Edit(1, 1, 500000, Arr[i], DP[i]);
		Res = std::max(Res, DP[i]);
	}
	std::cout << Res << '\n';
	return 0;
}

```

---

## 作者：Mingrui_Yang (赞：0)

### 题目大意

给定一个长度为 $n$ 的序列，求满足相邻元素的差的绝对值不超过 $d$ 的子序列的长度的最大值。

子序列由原序列删除零个或多个元素获得。

### Solution

考虑 DP。

观察数据范围。  
设计 $f_i$ 表示子序列中最后一个元素为 $i$ 的最长子序列的长度。

题目要求，在一个子序列中，相邻元素的差的绝对值不超过 $d$。   
所以，要使子序列合法，$i$ 只能与末尾元素为 $i-d\le j \le i+d$ 的子序列组成合法子序列。  
$$
f_i = \max\limits_{i-d\le j \le i+d} f_j + 1
$$

有以下代码。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10, LOGN = 25;
int n, d;
int a[N];
int f[N]; // 最后一项为i 
int ans;
signed main() {
	cin >> n >> d;
	for (int i = 1; i <= n; i ++ ) {
		cin >> a[i];
		int t = 0; // 可能存在相同元素，先找区间最大值 
		for (int j = max(1, a[i] - d); j <= min(N - 1, a[i] + d); j ++ ) t = max(t, f[j]);
		f[a[i]] = max(f[a[i]], t + 1); // 更新状态 
		ans = max(ans, f[a[i]]); // 更新答案 
	}
	cout << ans << endl;
	return 0;
}
```

显然，数据范围为 $5 \times 10^5$，这段代码会超时。

考虑优化。  
代码中需要用到单点修改与区间查询最大值。  
线段树可以解决。

时间复杂度为 $\mathcal{O}(n \log n)$。

### CODE

```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int N = 5e5 + 10, LOGN = 25;
int n, d;
int a[N];
int f[N]; // 最后一项为i 
int ans; // 存答案 
struct Node
{
    // 用结构体定义更方便
    int l, r; // 左右端点
    int v; // 最大值
}tr[N * 4]; // 数组得开 4*N

// 由子节点更新父节点
void pushup(int u)
{
    tr[u].v = max(tr[u << 1].v, tr[u << 1 | 1].v); // 取左右儿子的最大值 
}

 // 编号为u，左端点为l，右端点为r
void build(int u, int l, int r)
{
    tr[u].l = l, tr[u].r = r;
    if (l == r) return ; // 叶节点
    int mid = l + (r - l >> 1);
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r); // 递归构造左右子树，线段树是一个二叉树    
}

// 查找区间内的最大值 
int query(int u, int l, int r)
{
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].v; // tr[u]已被区间包含，直接返回 

    int mid = tr[u].l + (tr[u].r - tr[u].l >> 1);
    int v = 0;
    if (l <= mid) v = query(u << 1, l, r); // 区间与左子树有交集
    if (r > mid) v = max(v, query(u << 1 | 1, l, r)); // 区间与右子树有交集 
    return v;
}

// 叶节点x的值替换为v 
void modify(int u, int x, int v)
{
    if (tr[u].l == x && tr[u].r == x) tr[u].v = v; // 找到了
    else
    {
        int mid = tr[u].l + (tr[u].r - tr[u].l >> 1);
        if (x <= mid) modify(u << 1, x, v); // 在左子树 
        else modify(u << 1 | 1, x, v); // 在右子树
        pushup(u); // 更新 
    } 
}
signed main() {
	cin >> n >> d;
	build(1, 1, N - 1); // 构造线段树
	for (int i = 1; i <= n; i ++ ) {
		cin >> a[i];
		int t = query(1, max(1ll, a[i] - d), min(N - 1, a[i] + d)) + 1; // 查询区间最大值 
		f[a[i]] = max(f[a[i]], t); // 更新状态 
		ans = max(ans, f[a[i]]); // 更新答案 
		modify(1, a[i], f[a[i]]); // 更新线段树 
	}
	cout << ans << endl;
	return 0;
}
```


---

## 作者：RandomLife (赞：0)

# 题目大意

给定长度为 $N$ 的序列 $a$，求其最长子序列，使得该子序列任意相邻两个数的差不超过 $D$。

# 题解

一眼 DP，状态为 $f_i$ 表示以 $a_i$ 结尾的最长合法子序列。那么显然的，状态转移方程为：

$$
f_i=\max_{1\leq j<i,|a_i-a_j|\leq D}\{f_j\}
$$

答案为：

$$
\max_{1\leq i\leq N}\{f_i\}
$$

但更显然的，直接写会 T 飞。

我们先来看看它的双胞胎**最长上升子序列**是怎么优化的：

其状态转移式为：

$$
f_i=\max_{1\leq j<i,a_j<a_i}\{f_j\}
$$

此时，对于每个 $f_i$，前面只有 $a_j<a_i$ 的 $f_j$ 是对 $f_i$ 有贡献的，因此可以在权值上维护树状数组，以 $a_i$ 作为下标，$f_i$ 作为值。每次求前缀最大值即可。

同样的，在这道题里，只有 $a_i-D\leq a_j\leq a_i+D$ 的 $f_j$ 对 $f_i$ 有贡献。然而，这里需要求的是区间最大值，所以在权值上维护线段树。

# Code

```c++
#include<bits/stdc++.h>
#define lson p<<1
#define rson p<<1|1
using namespace std;
const int N=5e5+5;
struct SegmentTree{
	int l,r,Max;
	#define l(x)t[x].l
	#define r(x)t[x].r
	#define Max(x)t[x].Max
}t[N<<2];
int n,D,a[N],f[N],ans=0;
void pushUp(int p){
	Max(p)=max(Max(lson),Max(rson));
}
void build(int p,int l,int r){
	l(p)=l,r(p)=r;
	if(l==r){
		Max(p)=0;
		return;
	}
	int mid=(l+r)>>1;
	build(lson,l,mid),build(rson,mid+1,r);
	pushUp(p);
}
void update(int p,int x,int d){
	if(l(p)==r(p)){
		Max(p)=max(Max(p),d);
		return;
	}
	int mid=(l(p)+r(p))>>1;
	if(x<=mid)update(lson,x,d);
	else update(rson,x,d);
	pushUp(p);
}
int query(int p,int l,int r){
	if(l<=l(p)&&r>=r(p))return Max(p);
	int mid=(l(p)+r(p))>>1,res=0;
	if(l<=mid)res=max(res,query(lson,l,r));
	if(r>mid)res=max(res,query(rson,l,r));
	return res;
}
int main(){
	cin>>n>>D;
	for(int i=1;i<=n;++i)cin>>a[i];
	build(1,1,N-1);
	for(int i=1;i<=n;++i){
		f[i]=query(1,max(a[i]-D,1),min(a[i]+D,N-1))+1;
		update(1,a[i],f[i]),ans=max(ans,f[i]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Walrus (赞：0)

# [ABC339E](https://atcoder.jp/contests/abc339/tasks/abc339_e)

update：修改了下建议难度。

建议评绿，一道线段树优化 DP 好题，新手必做。


## 题意

给你 $n$ 个数，要求取其中几个数，其构成一个数列，满足相邻两个数之间的**绝对差**不超过 $k$。

- 形式意义上的要求：假设选 $m$ 个数，对于任意 $i(1< i\leq m)$，一定有 $|a_i-a_{i-1}|\leq k$。

## 做法

跟 LIS 问题相似，考虑 DP。我们发现，对于一个数 $x$，如果在其前曾经出现过一个数 $t$，满足 $x-k \leq t \leq x + k$，则其可通过前方的状态转移，同 LIS 问题一样，定义 $dp_i$ 表示以 $a_i$ 这个数字结尾最长的序列长度。

因为本题是维护某一个数字的存在与否，以及出现次数，考虑建**权值线段树**，因为 $1\leq A_i \leq 5\times 10^5$，空间足够，不需要离散化，况且因为要加减 $k$，也**不太方便**离散化（貌似把 $k$ 也离散化了也可做）。接下来几乎是板子了，权值线段树记录当前位置满足条件（当然是指在其之前的）出现次数，累加至每一个 $dp_i$，最后循环取 $\max$ 即可。

时间复杂度 $O(N \log N)$。

注意防越界。

## Code
```cpp
#include <bits/stdc++.h>
#define int long long
#define inf 0x7fffffff
using namespace std;
const int N = 5e5 + 5;


int n, k, a[N], dp[N], ans;

struct node {
	int l, r, mx;
	#define l(p) t[p].l
	#define r(p) t[p].r
	#define mx(p) t[p].mx
	#define ls (p << 1)
	#define rs (p << 1 | 1)
} t[N << 2];

void pushup(int p) {
	mx(p) = max(mx(ls), mx(rs));
}

void build(int p, int l, int r) {
	l(p) = l, r(p) = r;
	if(l == r) {
		return;
	}
	int mid = l + r >> 1;
	build(ls, l, mid);
	build(rs, mid + 1, r);
	pushup(p);
}

int ask(int p, int l, int r) {
	if(l <= l(p) && r(p) <= r)
		return mx(p);
	int mid = l(p) + r(p) >> 1,
		val = -inf;
	if(l <= mid)
		val = max(val, ask(ls, l, r));
	if(r > mid)
		val = max(val, ask(rs, l, r));
	return val;
}

void change(int p, int l, int r, int val) {
	if(l <= l(p) && r(p) <= r) {
		mx(p) = val;
		return;
	}
	int mid = l(p) + r(p) >> 1;
	if(l <= mid)
		change(ls, l, r, val);
	if(r > mid)
		change(rs, l, r, val);
	pushup(p);
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr), cout.tie(nullptr);
	
	cin >> n >> k;
	for(int i = 1; i <= n; ++i)
		cin >> a[i];
	int M = N - 1;
	build(1, 1, M);
	
	dp[1] = 1, change(1, a[1], a[1], 1);
	for(int i = 2; i <= n; ++i)
		dp[i] = ask(1, max(1ll, a[i] - k), min(M, a[i] + k)) + 1, change(1, a[i], a[i], dp[i]);
    for(int i = 1; i <= n; ++i)
        ans = max(ans, dp[i]);
    cout << ans;
	return 0;
}
```

赛时通过大佬同桌的教导下场切，所以这题真的很适合线段树优化 DP 新手练手。

讲个笑话：赛时权值线段树板板打错了狂炫三发罚时。

---

## 作者：DerrickLo (赞：0)

考虑一个朴素的 `dp`。

用 $dp_i$ 表示以 $i$ 结尾的平滑子序列最长是多少，那么很容易得到

$$dp_i=\max_{j\le i,|a_i-a_j|\le d}dp_j+1$$

我们发现当且仅当 $j\le i$ 且 $a_j\in[a_i-d,a_i+d]$ 时 $j$ 才会被用到，那么用一个值域线段树维护区间 $\max$ 即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,d,a[500005],dp[500005],ans;
struct tree{
	int l,r,maxx;
}tr[4000005];
void pushup(int u){
	tr[u].maxx=max(tr[u<<1].maxx,tr[u<<1|1].maxx);
}
void build(int u,int l,int r){
	tr[u]={l,r,0};
	if(l==r)return;
	int mid=l+r>>1;
	build(u<<1,l,mid),build(u<<1|1,mid+1,r);
}
void change(int u,int pos,int k){
	if(tr[u].l==tr[u].r){
		tr[u].maxx=max(tr[u].maxx,k);
		return;
	}
	int mid=tr[u].l+tr[u].r>>1;
	if(pos<=mid)change(u<<1,pos,k);
	else change(u<<1|1,pos,k);
	pushup(u);
}
int query(int u,int l,int r){
	if(tr[u].l>=l&&tr[u].r<=r)return tr[u].maxx;
	int mid=tr[u].l+tr[u].r>>1,res=-1e18;
	if(l<=mid)res=max(res,query(u<<1,l,r));
	if(r>mid)res=max(res,query(u<<1|1,l,r));
	return res;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>d;
	for(int i=1;i<=n;i++)cin>>a[i];
	build(1,0,1e6);
	for(int i=1;i<=n;i++){
		dp[i]=query(1,max(0ll,a[i]-d),a[i]+d)+1;
		change(1,a[i],dp[i]);
	}
	for(int i=1;i<=n;i++)ans=max(ans,dp[i]);
	cout<<ans;
	return 0;
}
```

---

## 作者：Crazyouth (赞：0)

## 分析

做过原。

不难想到一个类似 LIS 的 dp，$dp_i$ 表示前 $i$ 个数里面最长平滑子序列长度，则 $dp_i=\min\{dp_j(|a_j-a_i|\le k)\}+1$，考虑优化。注意到值域不大，可以开个线段树，表示值域区间内最大的 dp 值，单点修改，区间查询。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=5e5+10;
int mx[N<<2],a[N],dp[N];
void update(int k,int s,int t,int p,int c)
{
	if(s==t&&k==t)
	{
		mx[p]=max(mx[p],c);
		return;
	}
	if(s==t) return;
	int m=s+t>>1;
	if(k<=m) update(k,s,m,p<<1,c);
	else update(k,m+1,t,p<<1|1,c);
	mx[p]=max(mx[p<<1],mx[p<<1|1]);
}
int query(int l,int r,int s,int t,int p)
{
	if(l<=s&&t<=r) return mx[p];
	int m=s+t>>1;
	int ret=0;
	if(l<=m) ret=query(l,r,s,m,p<<1);
	if(r>m) ret=max(ret,query(l,r,m+1,t,p<<1|1));
	return ret;
}
int main() 
{
	int n,k,maxx=0;
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i],maxx=max(maxx,a[i]);
	dp[1]=1;
	update(a[1],1,maxx,1,1);
	for(int i=2;i<=n;i++) dp[i]=query(max(a[i]-k,0),min(a[i]+k,maxx),1,maxx,1)+1,update(a[i],1,maxx,1,dp[i]);
	int ans=0;
	for(int i=1;i<=n;i++) ans=max(ans,dp[i]);
	cout<<ans;
	return 0;
}

---

## 作者：Loser_Syx (赞：0)

对于每个 $a_i$，我们所接受的上一个 $a_j$ 的范围在 $[a_i-d,a_i+d]$ 之间，发现是一段连续的区间，而我们需要求出 $dp_{j}$ 的最大值以转移 $dp_i$，于是考虑值域线段树维护 $a_j$，以 $dp_{j}$ 作为值存储，每次查询区间的最大值转移即可。

[代码](https://atcoder.jp/contests/abc339/submissions/49943313)。

---

## 作者：c1ampy (赞：0)

### 题意简述

给定长度为 $ N $ 的序列 $ A = \left(A_1, A_2, \dots, A_N\right) $。请求出在 $ A $ 的**子序列**中，其**相邻两个**元素之差的绝对值**不大于** $ D $ 的子序列的**最大**长度。

$ A $ 的子序列是指从 $ A $ 中删去若干个（或零个）元素所得到的序列。

- $ 1 \le N \le 5 \times 10^5 $
- $ 0 \le D \le 5 \times 10^5 $
- $ 1 \le A_i \le 5 \times 10^5 $

### 解法分析

考虑 DP。

设 $ f_{i, j} $ 表示前 $ i $ 个元素组成的以 $ j $ 结尾的符合题意的子序列的最大长度。

不难得到状态转移方程：

$$
f_{i, j} = \begin{cases}
    \max_{k = j - D}^{j + D} f_{i - 1, k} + 1 & a_i = j \\
    f_{i - 1, j} & a_i \neq j
\end{cases}
$$

空间复杂度为 $ \mathcal{O}\left(n^2\right) $，无法接受。但我们不难发现第一维状态可以滚动优化，于是设 $ f_k $ 表示以 $ k $ 结尾的符合题意的子序列的最大长度。

状态转移方程变为：

$$
f_{a_i} \gets \max_{k = a_i - D}^{a_i + D} f_k + 1
$$

算法的空间复杂度已被降为 $ \mathcal{O}\left(n\right) $。但上述转移需进行 $ n $ 次，单次转移的时间复杂度为 $ \mathcal{O}\left(n\right) $，总时间复杂度为 $ \mathcal{O}\left(n^2\right) $，仍需继续优化。

观察状态转移方程，发现转移过程要求 $ f $ 数组的区间最大值，还要对 $ f $ 数组进行单点修改。如果我们使用线段树维护 $ f $ 数组，可以将单次转移的时间复杂度优化为 $ \mathcal{O}\left(\log n\right) $，总时间复杂度优化为 $ \mathcal{O}\left(n\log n\right) $，可以通过。

### 代码实现

注意实现细节：$ a_i - D $ 与 $ a_i + D $ 都有可能越界，注意特判。

代码如下：

```cpp
#include <iostream>
#include <vector>

class SegmentTree {
private:

	struct Node {
		Node *lc, *rc;
		int max;

		Node(const int max = 0) : lc(nullptr), rc(nullptr), max(max) {}

		void push_up() {
			this->max = 0;
			if (this->lc) this->max = std::max(this->max, this->lc->max);
			if (this->rc) this->max = std::max(this->max, this->rc->max);
		}
	};

	int size;
	Node *root;

	void modify(Node *&cur, const int l, const int r, const int idx, const int value) {
		if (!cur)
            cur = new Node();
		if (l + 1 == r) {
			cur->max = value;
			return;
		}
		
		int mid = (l + r) >> 1;
		if (idx < mid) modify(cur->lc, l, mid, idx, value);
		else modify(cur->rc, mid, r, idx, value);
		
		cur->push_up();
	}

	int query(Node *cur, const int l, const int r, const int ql, const int qr) {
		if (!cur)
			return 0;
		if (ql <= l && r <= qr)
			return cur->max;
		
		int mid = (l + r) >> 1, res = 0;
		if (ql < mid) res = std::max(res, query(cur->lc, l, mid, ql, qr));
		if (qr > mid) res = std::max(res, query(cur->rc, mid, r, ql, qr));
		
		return res;
	}

public:

	SegmentTree(const int size = 0) : root(nullptr), size(size) {}
	void modify(const int idx, const int value) { modify(root, 0, size, idx, value); }
	int query(const int l, const int r) { return query(root, 0, size, l, r); }
};

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n, d; std::cin >> n >> d;

	const int max_v = 5e5;
	SegmentTree dp(max_v + 1);
	for (int i = 0, v; i < n; ++i) {
		std::cin >> v;
		int l = v - d < 0 ? 0 : v - d;
		int r = v + d > max_v ? max_v + 1 : v + d + 1;
		dp.modify(v, dp.query(l, r) + 1);
	}

	std::cout << dp.query(0, max_v + 1) << std::endl;

    return 0;
}
```


---

## 作者：apiad (赞：0)

这是重题！

这种题显然是 dp，不太可能是贪心。因为你想，咋贪呢？

设一个转移方程 $dp_i$ 从 $dp_j$ 转移，并且 $a_i$ 和 $a_j$ 的差小于等于 $d$。

时间复杂度 $O(n^2)$。

出题人非常善良的，给了一个 $a_i \le 5\times 10^5$。那我们是不是在每一次转移后，记录一下这个最长的子序列，大概就是 $vis_{a_i} = \max(vis_{a_i},dp_i)$。这样，我们每一次转移的时候只需要遍历 $vis_{a_i-d}$ 到 $vis_{a_i+d}$ 取一个最大值，进行转移，然后再更新。

时间复杂度稍微优化了，$O(n \times d)$。但显然还是和 $O(n^2)$ 没啥区别。

再回想，我们是从 $vis_{a_i-d}$ 到 $vis_{a_i+d}$ 取一个最大值。对？线段树！

线段树可以在 $O(\log n)$ 的时间内进行区间最大值查询，修改也是一样的时间复杂度。那么，我们搬运过来线段树 1 的板子，然后稍作修改即可！

时间复杂度是 $O(n\log n)$。

[link](https://atcoder.jp/contests/abc339/submissions/49960186)。

---

## 作者：banned_gutongxing (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc339_e)

## 思路分析
看见这道题我们想到了最长上升子序列，所以我们可以试着使用DP。

定义：$dp_i$ 代表以第 $i$ 个数结尾的最长长度。

状态转移方程式：
$$dp_i=\max_{j<i,\mid a_i-a_j\mid\le d} dp_j+1$$

此时，它的时间复杂度为 $O(n^2)$。

考虑优化。

我们发现这个方程只会访问到前面的信息，所以我们用**扫描线**，从左到右依次进行枚举我们只用在当前扫过的 $dp$ 的值中询问区间 $[a_i-d,a_i+d]$ 的 $dp$ 值有多少个，并进行动态修改。此时考虑**动态开点+权值线段树**。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+10;
int n,d,a[MAXN];
//Segment tree
#define l(x) tree[x].ls
#define r(x) tree[x].rs
#define maxn(x) tree[x].maxn
int Segmentsum;
struct SegmentTree{
	int l,r,len,ls,rs,maxn;
}tree[MAXN*8];
void build(int l,int r){
	Segmentsum++;
	tree[Segmentsum].l = l;
	tree[Segmentsum].r = r;
	tree[Segmentsum].len = r-l+1;
	tree[Segmentsum].maxn = 0;
}
void pushup(int x){
	if(tree[x].l==tree[x].r) return;
	tree[x].maxn=max(tree[l(x)].maxn,tree[r(x)].maxn);
}
void pushdown(int x){
	if(tree[x].l==tree[x].r) return;
	int mid = (tree[x].l+tree[x].r)>>1;
	if(!l(x)){
		build(tree[x].l,mid);
		l(x) = Segmentsum;
	}
	if(!r(x)){
		build(mid+1,tree[x].r);
		r(x) = Segmentsum;
	}
}
void modify(int k,int x,int y){
	if(tree[k].l>x||tree[k].r<x) return;
	if(tree[k].l==x&&tree[k].r==x){
		tree[k].maxn = max(tree[k].maxn,y);
		return;
	}
	pushdown(k);
	modify(l(k),x,y);
	modify(r(k),x,y);
	pushup(k);
}
int ask(int k,int x,int y){
	if(tree[k].l>y||tree[k].r<x) return 0;
	if(tree[k].l>=x&&tree[k].r<=y) return tree[k].maxn;
	pushdown(k);
	int ans = max(ask(l(k),x,y),ask(r(k),x,y));
	pushup(k);
	return ans;
}
signed main(){
	scanf("%d%d",&n,&d);
	build(1,500000);
	for(int i = 1;i<=n;i++){
		scanf("%d",a+i);
		modify(1,a[i],ask(1,max(1,a[i]-d),min(500000,a[i]+d))+1);
	}
	printf("%d",ask(1,1,500000));
	return 0;
}
```

---

## 作者：Starrykiller (赞：0)

纪念一下首次 AK ABC。

题意：给定序列 $A$，求出最长的子序列（可以不连续），使得子序列中相邻的两项的差的绝对值不大于 $D$。

$N,A_i,D\leq 5\times 10^5$。

设 $f_i$ 为 $[1,i]$ 中最长的满足题意的子序列长度，我们有朴素的转移方程

$$f_i=\max\begin{cases}1, \\
\max_{j=1}^{i-1} (f_j+1) & (|a_i-a_j|\le D)
\end{cases}$$

观察第二个方程。到我们如果从小到大转移，循环顺序就自然地控制了 $j\lt i$ 的条件。然后我们不难将 $|a_i-a_j|\lt D$ 转化为 $a_i-D\leq a_j\leq a_i+D$，于是我们维护一颗值域上的线段树，每个单点 $[x,x]$ 维护子序列以**元素 $\boldsymbol{x}$** 结尾时的子序列长度最大值。于是只需要支持单点修改，区间取 max 即可。

注意边界情况，例如 $1\leq a_i-D\leq a_i+D\leq 5\times 10^5$。

```cpp
#include <bits/stdc++.h>
#include <atcoder/all>

using namespace std;

#define int long long 
using ll=atcoder::modint998244353;

constexpr int MAXN=5e5+10;
int a[MAXN], n, d, f[MAXN];

struct SG {
    #define ls(p) (p<<1)
    #define rs(p) (p<<1|1)
    #define val(p) tr[p].val
    #define ll(p) tr[p].l
    #define rr(p) tr[p].r
    struct node {
        int l, r, val;
    } tr[MAXN<<2];
    void pushup(int p) {
        val(p)=max(val(ls(p)),val(rs(p)));
    }
    void build(int l, int r, int p=1) {
        ll(p)=l, rr(p)=r; val(p)=0;
        if (l==r) return;
        int mid=(l+r)>>1;
        build(l,mid,ls(p)); build(mid+1,r,rs(p));
    }
    void change(int pos, int v, int p=1) {
        int cl=ll(p), cr=rr(p);
        if (cl==cr) {
            val(p)=max(v,val(p)); return;
        }
        int mid=(cl+cr)>>1;
        if (pos<=mid) change(pos,v,ls(p));
        else change(pos,v,rs(p));
        pushup(p);
    }
    int query(int l, int r, int p=1) {
        int cl=ll(p), cr=rr(p);
        if (l<=cl&&cr<=r) return val(p);
        int mid=(cl+cr)>>1, res=0;
        if (l<=mid) res=query(l,r,ls(p));
        if (r>mid) res=max(res,query(l,r,rs(p)));
        return res;
    }
} sg;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin>>n>>d; for (int i=1; i<=n; ++i) cin>>a[i];
    sg.build(1,5e5);
    int ans=0;
    for (int i=1; i<=n; ++i) {
        int cur=1;
        cur=max(cur,sg.query(max(1ll,a[i]-d),min(500000ll,a[i]+d))+1);
        sg.change(a[i],cur);
        ans=max(ans,cur);
    }
    cout<<ans<<'\n';
}

```

---

