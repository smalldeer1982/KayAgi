# Flowers

## 题目描述

[problemUrl]: https://atcoder.jp/contests/dp/tasks/dp_q

$ N $ 本の花が横一列に並んでいます。 各 $ i $ ($ 1\ \leq\ i\ \leq\ N $) について、左から $ i $ 番目の花の高さは $ h_i $ で、美しさは $ a_i $ です。 ただし、$ h_1,\ h_2,\ \ldots,\ h_N $ はすべて相異なります。

太郎君は何本かの花を抜き去ることで、次の条件が成り立つようにしようとしています。

- 残りの花を左から順に見ると、高さが単調増加になっている。

残りの花の美しさの総和の最大値を求めてください。

## 说明/提示

### 制約

- 入力はすべて整数である。
- $ 1\ \leq\ N\ \leq\ 2\ ×\ 10^5 $
- $ 1\ \leq\ h_i\ \leq\ N $
- $ h_1,\ h_2,\ \ldots,\ h_N $ はすべて相異なる。
- $ 1\ \leq\ a_i\ \leq\ 10^9 $

### Sample Explanation 1

左から $ 2,\ 4 $ 番目の花を残せばよいです。 すると、高さは左から順に $ 1,\ 2 $ となり、単調増加になっています。 また、美しさの総和は $ 20\ +\ 40\ =\ 60 $ となります。

### Sample Explanation 2

最初から条件が成り立っています。

### Sample Explanation 3

答えは 32-bit 整数型に収まらない場合があります。

### Sample Explanation 4

左から $ 2,\ 3,\ 6,\ 8,\ 9 $ 番目の花を残せばよいです。

## 样例 #1

### 输入

```
4
3 1 4 2
10 20 30 40```

### 输出

```
60```

## 样例 #2

### 输入

```
1
1
10```

### 输出

```
10```

## 样例 #3

### 输入

```
5
1 2 3 4 5
1000000000 1000000000 1000000000 1000000000 1000000000```

### 输出

```
5000000000```

## 样例 #4

### 输入

```
9
4 2 5 8 3 6 1 7 9
6 8 8 4 6 3 5 7 5```

### 输出

```
31```

# 题解

## 作者：Orange_qwq (赞：18)

## 前言

前置知识：[树状数组](https://www.luogu.com.cn/problem/P3368)

写 树状数组 会比 线段树 简单一些，也比较容易调（更重要的是它比较短（逃

## 思路分析

令 $f_i$ 为前 $i$ 个花满足题目“高度单调递增”的条件，花权值之和的最大值。 易得转移方程为：

$$ f_i=\max\limits_{j=1}^{i-1} \{f_j \ | \ h_j < h_i\} + a_i$$

由于 $n$ 到 $2 \times 10^5$，$n^2$ 的 dp 会炸，需要优化。

于是我们可以敏锐地发现里面有个要求 $f_1$ 至 $f_{i-1}$ 最大值的东西！单点询问，区间查询，除了 ~~代码比较长的~~ 线段树，我们还可以用树状数组！

**注意：** 本题需要用 `long long`。

## $\texttt{AC Code}$

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long
int n, h[200010], a[200010];
ll tr[200010], f, cnt;

void add(int x, ll y) {
	for (int i = x; i <= n; i += i & (-i)) tr[i] = max(tr[i], y);
}

ll _(int x) {
	ll ans = 0;
	for (int i = x; i; i -= i & (-i)) ans = max(ans, tr[i]);
	return ans;
} 

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &h[i]);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for (int i = 1; i <= n; ++i) {
		f = _(h[i] - 1) + a[i]; // 区间查询最大值
		add(h[i], f);           // 塞入当前 f 的值
		cnt = max(cnt, f);      // 记录答案
	}
	printf("%lld", cnt);
	return 0;
}
```


---

## 作者：SIXIANG32 (赞：7)

一道良心 dp。  
闲话少说，切入正题——  

---
概括版题意——  

> 有 $n$ 个二元组 $(h_i, a_i)$，按顺序其中任意一些二元组使得 $h_i$ 单调递增且 $a_i$ 的和最大。  

显然这是个有手就行的 dp，状态 $f_i$ 代表前 $i$ 个二元组的最大价值，状态转移方程是 $f_i = \max\limits_{j = 1}^{i- 1}\{f_j\}(h_j < h_i) + a_i$。  

定睛一看数据范围，$n\le 2\times 10^5$，必炸无疑，考虑优化。

发现 $h$ 都比较小，在 $n$ 以内，我们可以在 $h$ 上做文章。维护一个 DS，将 $h_i$ 作为下标，$f_i$ 作为存储的值。这样求最大值的时候就能查 $[1, h_i]$ 这个区间了。支持单点修改，区间求最大值，首选线段树啦。  

*PS：为什么明明是单调不降然后取 $[1, h_i]$ 这个的最大值？不应该是 $[1, h_i-1]$ 吗？但是考虑到 $h_i$ 互不相同，$h_i$ 这里是没有数字的，都一样，这样也不用特判 $h_i = 1$ 的情况*  

```cpp
#include <iostream>
#define MAXN 200000
#define int long long
#define QWQ cout << "QWQ" << endl;
using namespace std;
int max(int x, int y) {return ((x > y) ? (x) : (y));}
//---qwqaquq---
int M[MAXN * 4 + 10];
int ls(int now) {return (now << 1);}
int rs(int now) {return (now << 1 | 1);}
void push_up(int now) {
	M[now] = max(M[ls(now)], M[rs(now)]);
}
void updata(int l, int r, int pos, int now, int val) {//单点修改
	if(l == r) {
		M[now] = val;
		return ;
	}
	int mid = (l + r) >> 1;
	if(pos <= mid) updata(l, mid, pos, ls(now), val);
	else updata(mid + 1, r, pos, rs(now), val);
	push_up(now);
	return ;
}
int query(int l, int r, int s, int t, int now) {//区间查询
	if(l <= s && t <= r) return M[now];
	int mid = (s + t) >> 1, res = 0;
	if(l <= mid) res = max(res, query(l, r, s, mid, ls(now)));
	if(r > mid) res = max(res, query(l, r, mid + 1, t, rs(now)));
	return res;
} 
//---qwqaquq---
int n, a[MAXN + 10], h[MAXN + 10], f[MAXN + 10], maxn = 0;
signed main() {
	cin >> n;
	for(int p = 1; p <= n; p++) cin >> h[p];
	for(int p = 1; p <= n; p++) cin >> a[p], f[p] = a[p];
	for(int p = 1; p <= n; p++) {
		int res;
		res = query(1, h[p], 1, n, 1);
		f[p] = res + a[p];//转移
		maxn = max(f[p], maxn);
		updata(1, n, h[p], 1, f[p]);
	}
	cout << maxn << endl;
}
```

---

## 作者：云浅知处 (赞：4)

其实就是把 LIS 加了一个权而已。

仍然设 $F(i)$ 为以第 $i$ 个元素结尾的价值最大的子序列，那么转移方程就是：

$$
F(i)=\max\{F(j)|h_j\le h_i\}+a_i
$$

用一下 LIS 的套路，转到值域上开一个线段树维护区间最大值即可。

~~我没看到 $\sout{1\le h_i\le n}$ 还去写了一个萌萌的离散化qwq~~

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdlib>

#define lson(o) (o<<1)
#define rson(o) (o<<1|1)
#define int long long
const int MN=2e5+5;

using namespace std;

inline int read(){
    int x=0,f=1;char c=getchar();
    for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
    for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
    return x*f;
}

struct SegTree{

    int d[MN<<2];

    inline void clr(){memset(d,0,sizeof(d));}

    inline void pushup(int o){
        d[o]=max(d[lson(o)],d[rson(o)]);
    }

    inline void modify(int pos,int k,int ql,int qr,int o){
        if(ql==qr){d[o]=k;return;}
        int mid=(ql+qr)>>1;
        if(pos<=mid)modify(pos,k,ql,mid,lson(o));
        else modify(pos,k,mid+1,qr,rson(o));
        pushup(o);
    }

    inline int query(int l,int r,int ql,int qr,int o){
        if(l<=ql&&qr<=r){return d[o];}
        int mid=(ql+qr)>>1,ans=-1;
        if(l<=mid)ans=max(ans,query(l,r,ql,mid,lson(o)));
        if(r>mid)ans=max(ans,query(l,r,mid+1,qr,rson(o)));
        return ans;
    }

};

SegTree tree;

int a[MN],w[MN],n,b[MN],dp[MN];

signed main(void){

    tree.clr();

    n=read();
    for(int i=1;i<=n;i++)b[i]=a[i]=read();
    for(int i=1;i<=n;i++)w[i]=read();

    sort(b+1,b+n+1);int len=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+len+1,a[i])-b;

    for(int i=1;i<=n;i++){
        dp[i]=tree.query(1,a[i],1,n,1)+w[i];
        tree.modify(a[i],dp[i],1,n,1);
    }

    cout<<tree.query(1,n,1,n,1)<<endl;

    return 0;
}
```

---

## 作者：Hisaishi_Kanade (赞：2)

简单动态规划。

设 $f_i$ 表示选择 $1\sim i$ 中若干花的最大价值，必须选 $i$。

容易想到动态规划转移方程 $f_i=\max\{f_j\}+\omega_i\mid j<i,h_j\le h_i$。

直接模拟是 $O(n^2)$ 的，我们考虑优化动态规划转移方程。

发现 $i$ 的枚举必不可少，那么考虑优化求 $\max\{f_j\}$ 的复杂度。

单点修改，区间查，怎么做？

线段树。

在线段树上维护最大值，每次 `query` 区间 $[1,h_i]$ 的最大值即可。

最后输出 $\max \{f_i\}$，没说以什么结尾。

[通过记录](https://atcoder.jp/contests/dp/submissions/38318606)

```cpp
#include <stdio.h>
#define int long long//数据范围可知，要long long
#define lc(id) (id<<1)
#define rc(id) (id<<1|1)
int tree[4000005];
int i,n,val,ret;
int v[1000005],h[1000005];
inline int max(int x,int y)
{
	return x>y?x:y;
}
inline void push_up(int id)
{
	tree[id]=max(tree[lc(id)],tree[rc(id)]);
	return ;
}
inline void update(int id,int l,int r,int pos,int nxt)
{
	if(l==r&&l==pos)
	{
		tree[id]=nxt;
		return ;
	}
	int mid=l+r>>1;
	if(pos<=mid)
		update(lc(id),l,mid,pos,nxt);
	if(mid<pos)
		update(rc(id),mid+1,r,pos,nxt);
	push_up(id);
	return ;
}//将 pos 的值改为 nxt
inline int query(int id,int ql,int qr,int l,int r)
{
//	printf("%d %d %d %d %d\n",id,ql,qr,l,r);
	if(ql<=l&&r<=qr)
	{
		return tree[id];
	}
	int mid=l+r>>1,res=-1;
	if(ql<=mid)
		res=max(res,query(lc(id),ql,qr,l,mid));
	if(qr>mid)
		res=max(res,query(rc(id),ql,qr,mid+1,r));
	return res;
}//查询 [ql,qr] 最大值
signed main()
{
	int n;scanf("%lld",&n);
	for(i=1;i<=n;++i)
		scanf("%lld",h+i);
	for(i=1;i<=n;++i)
		scanf("%lld",v+i);
//	build(1,1,n);
//	此题比较特殊，节点初始均为0。
//	由于我的写法，可以不 build。
	for(i=1;i<=n;++i)
	{
		val=query(1,1,h[i],1,n)+v[i];//当前的 f[i]
		ret=max(ret,val);
		update(1,1,n,h[i],val);
	}
	printf("%lld",ret);
	return 0;
}
```

---

## 作者：Lates (赞：2)

看完题目可以发现这是个“最大价值子序列”。

可以像求 LIS 一样做。

设 $f[i]$ 表示以 $i$ 为结尾的最大价值。

那么 $f[i]=\max\{f[j]\}+v[i]\ \ ( j<i,a[j]<a[i])$

朴素做法是 $\mathcal{O(n^2)}$ 的。

这实际上是维护个二维偏序，也就是正序对。

所以可以用 BIT 维护。

这里的 $h$ 数组，良心出题人已经帮忙离散化了，可以直接做。

时间复杂度 $\mathcal{O(n\log n)}$。






---

## 作者：ChenRH (赞：1)

## 简化题意

给定权值 $a_i$ 和高度 $h_i$，按顺序选择其中一些 $i$ 使得 $h_i$ 单调递增且 $a_i$ 的和最大。

## 数据范围

- $1≤N≤2×10^5$
- $1≤h_i≤N$
- $h_1,\ h_2,\ \ldots,\ h_N$ 互异
- $1≤a_i≤10^9$


## 解题思路

一眼 $Θ(n^2)$dp，$f_i=\max\limits_{j=1}^{i-1}f_j(h_j<h_i)$，$ans=f_n$，但是显然时间复杂度不对。

考虑用单调思想优化，如果 $h_i<h_j$ 且 $f_i>f_j$ 那么 $j$ 就一定不会被选中，所以我们维护一个 $h$ 单调递增 $f$ 单调递增的编号数组 $st$，每次二分更新答案然后维护 $st$。

时间复杂度 $Θ(n \log n)$。

## 参考代码


```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 200005
#define ll long long

using namespace std;

ll n, h[N], a[N], f[N], st[N], top, t[N], ma;

inline ll read(){
	ll x = 0, f = 1; char c = getchar();
	while(c < '0' || c > '9'){if(c == '-')f = -1; c = getchar();}
	while(c >= '0' && c <= '9'){x = (x << 1) + (x << 3) + c - '0'; c = getchar();}
	return x * f;
}

int main(){
	n = read();
	for(int i = 1; i <= n; ++i){
		h[i] = read();
	} 
	for(int i = 1; i <= n; ++i){
		a[i] = read();
	}
	f[1] = ma = a[1];//初始化
	st[++top] = 1;
	t[top] = h[1];
	for(int i = 2; i <= n; ++i){
		if(h[i] > t[top]){//如果h[i]比当前最高的还要高就直接加进去
			f[i] = f[st[top]] + a[i];
			ma = max(ma, f[i]);
			st[++top] = i;
			t[top] = h[i];
			continue;
		}
		int j = lower_bound(t + 1, t + 1 + top, h[i]) - t - 1;//二分找到最后一个比h[i]矮的
		f[i] = f[st[j]] + a[i];//计算f[i]
		ma = max(ma, f[i]);//更新答案
		++j;
		int tmp = j;
		while(j <= top && (t[j] >= h[i] && f[st[j]] < f[i])){//更新单调数组
			++j;
		}
		if(j > tmp){
			st[tmp] = i;
			t[tmp] = h[i];
			for(int k = tmp + 1; k + (j - tmp - 1) <= top; ++k){
				st[k] = st[k + (j - tmp - 1)];
				t[k] = t[k + (j - tmp - 1)];
			} 
			top -= (j - tmp - 1);
		}
		else{
			++top;
			for(int k = top; k > j; --k){
				st[k] = st[k - 1];
				t[k] = t[k - 1];
			}
			st[j] = i;
			t[j] = h[i];
		} 
	}
	printf("%lld\n", ma);//输出答案
	return 0;
}
```

---

## 作者：luckydrawbox (赞：1)

## 题意

一个长度为 $n$ 的序列，每个元素有两个权值 $h_i,a_i$，从这个序列中选出一个子序列，并满足以下要求：

- $h_i$ 单调递增。

- 在满足上一条的情况下，这个子序列的 $a_i$ 之和最大。

## 分析

设 $dp_i$ 表示以 $i$ 结尾的符合要求的子序列。

根据题意，则：

$$dp_i=\max_{j=1}^{i-1}\{dp_j\}(h_j<h_i)+a_i$$

这样做是 $O(n^2)$ 的，显然过不了，不过题目中 $h_i$ 比较小，所以我们从 $h_i$ 入手。

其实，我们要找的 $dp_j$ 就是 $i$ 之前所有高度在 $1\sim h_i-1$ 之间的 $dp_j$ 中最大的一个。

这个显然可以用数据结构维护，我们需要一个支持**单点修改，区间查询最大值**的数据结构，树形结构比较麻烦，我们可以用**分块**来做。

本题只要维护一个前缀最大值，所以查询的区间中只有右边是散块，这样就很好写了，前面部分统计整块最大值，后面部分暴力统计。

单点修改更是简单，两行解决，把 $h_i$ 所在的点和块更新即可。

## 代码

时间复杂度 $O(n\sqrt n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
long long read(){
	long long x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
const int N=2e5+10,M=600;
int n;
ll dp[N],b[N],k[N],h[N],a[N],len,mx;
void change(int x,ll y){
	b[x]=max(b[x],y);
	k[x/len]=max(k[x/len],y);
}
ll ask(int x){
	ll mx=0;
	for(int i=0;i<x/len;i++)
		mx=max(mx,k[i]);
	for(int i=x/len*len;i<=x;i++)
		mx=max(mx,b[i]);
	return mx;
}
int main(){
	n=read();
	len=sqrt(n);
	for(int i=1;i<=n;i++)
		h[i]=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=1;i<=n;i++){
		dp[i]=ask(h[i]-1)+a[i];
		change(h[i],dp[i]);
		mx=max(mx,dp[i]);
	}
	cout<<mx;
	return 0;
}
```

---

## 作者：chlchl (赞：0)

纪念一下通过的第一道线段树优化 DP（~~其实只是优化了一半吧~~）。

## 题意简述
有 $n$ 个数对 $(h_i,a_i)$，需要去掉若干个数对，使得剩下数对 $h_i$ 递增，问剩下的数对 $a_i$ 之和的最大值。

## 做法
线段树优化 DP。

这个题的状态很容易得出，~~通过 $n\leq 2\times 10^5$ 的数据范围~~，我们可以得出 $f_i$ 为前 $i$ 个数对剩下的最大值，转移就是 $f_i=\max_{j=1}^{i-1}\{f_j+1\},h_j<h_i$。

输出就是 $\max_{i=1}^{n}f_i$。

但这样转移是 $O(n)$ 的，我们需要考虑优化。

注意到每次转移都是取一段的最大值，考虑倍增或线段树（~~啊对对对，树状数组也行~~）。

但是这个最大值还得有要求，$h_j$ 必须小于 $h_i$，所以考虑开一棵值域线段树，存下 $h_j$ 在不同值域范围内 $f_j$ 的最大值。

由于我们是从 $1$ 求到 $n$，所以每次求出 $f_i$ 后直接扔进线段树中，这样我们直接查询，就能保证查询的是 $f_1$ 到 $f_{i-1}$ 的最大值。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 2e5 + 10;
int n, h[N];
ll ans, a[N], f[N];
ll val[N << 2];//不要懒标记，不要写pushdown！！！
//单点修改，区间查询！！！ 

#define ls(o) (o << 1)
#define rs(o) (o << 1 | 1)

void update(int o, int l, int r, int p, ll v){
	if(l == r){
		val[o] = max(val[o], v);
		return ;
	}
	int mid = (l + r) >> 1;
	if(p <= mid)
		update(ls(o), l, mid, p, v);
	else
		update(rs(o), mid + 1, r, p, v);
	val[o] = max(val[ls(o)], val[rs(o)]);
}

ll query(int o, int l, int r, int s, int t){
	if(l >= s && r <= t)
		return val[o];
	int mid = (l + r) >> 1;
	ll res = 0;
	if(s <= mid)
		res = max(res, query(ls(o), l, mid, s, t));
	if(t > mid)
		res = max(res, query(rs(o), mid + 1, r, s, t));
	return res;
}

int main(){
	scanf("%d", &n);
	for(int i=1;i<=n;i++)
		scanf("%d", &h[i]);
	for(int i=1;i<=n;i++)
		scanf("%lld", &a[i]);
	for(int i=1;i<=n;i++){
		f[i] = query(1, 1, n, 1, h[i]) + a[i];//查的当然是 1~h[i]-1，但是题目保证 h[i] 互不相同
		//所以 h[i] 当然没有 f 值啦！查询 1~h[i] 是为了防止越界 
		ans = max(ans, f[i]);
		update(1, 1, n, h[i], f[i]);//扔进线段树 
	}
	printf("%lld\n", ans);
	return 0;
}
```


---

## 作者：happybob (赞：0)

## 题意

带权值最长上升子序列。

## 解法

考虑 dp，和普通最长上升子序列一样，设 $dp_i$ 表示以 $i$ 为结尾的最长上升子序列的权值和，则有 $dp_i = (\max_{j=1}^{i-1} \begin{cases} dp_j & h_j < h_i \\ 0 & h_j \ge h_i\end{cases}) + h_i$，显然这个转移是 $O(n^2)$ 的，而 $\max$ 可以值域线段树维护，支持单点修改区间查询，复杂度 $O(n \log n)$。

---

## 作者：activeO (赞：0)

## 题目大意

有一排花，共 n 个，第 i 个的高度是 $ h_i $，权值是 $ a_i $，保证高度互不相同。现在拿走一些花，使剩下的花高度单调递增，问剩下的花权值之和最大是多少。

## 思路

第一眼看上去有点像 LIS，但是数据：$ 1 \leq a_i \leq 10^9 $。显然不能以价值作为状态。发现只需要关心**上一个取的花的高度是多少**，所以考虑一个朴素的 $ dp_i $ 表示以第 i 个花为结尾的最大价值。

就可以得到状态转移方程：$ dp_i = \max \limits_{1 \leq j \leq i-1} dp_j + a_i $。

这个 dp 复杂度是 $ O(n^2) $ 的，会超时，又发现每一次 dp 是由最大值转移过来的，所以我们用线段树（也可以用树状数组）维护区间最大值，单点修改，区间查询即可。（具体看代码）总时间复杂度 $ O(n \log n) $

## 代码

```cpp
#include <bits/stdc++.h>//祝大家学习愉快！

#define int long long

using namespace std;

const int maxn=2e5+5;
int tr[maxn<<2],dp[maxn];
int h[maxn],a[maxn],n,ans=0;

inline void pushup(int now){
	tr[now]=max(tr[now<<1],tr[now<<1|1]);
}
void update(int now,int l,int r,int x,int v){
	if(l==r){
		tr[now]=max(tr[now],v);
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid) update(now<<1,l,mid,x,v);
	else update(now<<1|1,mid+1,r,x,v);
	pushup(now);
}
int query(int now,int l,int r,int ql,int qr){
	if(ql<=l&&qr>=r) return tr[now];
	int mid=(l+r)>>1;
	int sum=0;
	if(ql<=mid) sum=max(sum,query(now<<1,l,mid,ql,qr));
	if(qr>mid) sum=max(sum,query(now<<1|1,mid+1,r,ql,qr));
	return sum;
}

//线段树优化

signed main(){
	
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&h[i]);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	
	for(int i=1;i<=n;i++){
		dp[h[i]]=query(1,0,n,0,h[i]-1)+a[i];//状态转移
		update(1,0,n,h[i],dp[h[i]]);
		ans=max(ans,dp[h[i]]);
	}
	
	printf("%lld\n",ans);
	
	return 0;
}
```


---

## 作者：AmamiyaYuuko (赞：0)

上面那篇题解用 BIT 维护，蒟蒻表示不是很明白怎么用正常的 BIT 维护最大值...

设 $f(i)$ 表示以 $i$ 结尾的最大收益，那么答案即为 $\max \limits_{i = 1}^n f(i)$。

考虑怎么维护 $f(i)$，这个其实很好想，就是 $f(i) = \max\limits_{j < i \land h_j < h_i} f(j) + a_i$。

直接暴力是 $O(n^2)$ 的，如果能知道这个最大值是什么就好了。想到这里应该就会写了。

我们只需要一个能查询最值，能修改的数据结构就行了。由于蒟蒻太弱了，只会写线段树。

代码：

```cpp
struct Node {
    int l, r;
    LL v;
} t[800010];

LL h[200010], a[200010], f[200010];
LL ans;
int n, len;

inline int lson(int x) { return x << 1; }
inline int rson(int x) { return x << 1 | 1; }

void buildTree(int x, int l, int r) {
    t[x].l = l, t[x].r = r;
    if (l == r)    return ;
    int mid = (l + r) >> 1;
    buildTree(lson(x), l, mid), buildTree(rson(x), mid + 1, r);
}

void modify(int x, int p, LL v) {
    if (t[x].l == t[x].r) {
        t[x].v = v;
        return ;
    }
    int mid = (t[x].l + t[x].r) >> 1;
    if (p <= mid)    modify(lson(x), p, v);
    else    modify(rson(x), p, v);
    t[x].v = std::max(t[lson(x)].v, t[rson(x)].v);
}

LL query(int x, int l, int r) {
    if (l <= t[x].l && t[x].r <= r)    return t[x].v;
    int mid = (t[x].l + t[x].r) >> 1;
    LL s = 0;
    if (l <= mid)    s = std::max(s, query(lson(x), l, r));
    if (r > mid)     s = std::max(s, query(rson(x), l, r));
    return s;
}

int main() {
    read(n);
    buildTree(1, 1, n);
    for (int i = 1; i <= n; ++i)    read(h[i]);
    for (int i = 1; i <= n; ++i)    read(a[i]);
    for (int i = 1; i <= n; ++i) {
        LL max = query(1, 1, h[i]);
        f[i] = max + a[i];
        ans = std::max(ans, f[i]);
        modify(1, h[i], f[i]);
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：FelFa_1414666 (赞：0)

~~呦呦呦，这不是 LIS 最长上升子序列吗，几日不见，数据范围这么大了。~~

[atcoder 题目传送门](https://atcoder.jp/contests/dp/tasks/dp_q)。

[更好的阅读体验](https://www.luogu.com.cn/blog/xesssb10108899/solution-at4538)。

### 题意

有 $n$ 朵顺序排列的花，每朵花有高度 $h_i$ 和价值 $a_i$，高度两两不同。选取一些花使得这些花的高度依次**递增**，求选取花**最大的总价值**

- $1\le n\le 2\times 10^5$

- $1\le h_i\le n$ 且 $h_i\ne h_j,\forall i\ne j$

- $1\le a_i\le 10^9$

------------

### 分析

这题类似最长上升子序列，但是价值的数据范围太大了啊，没法以价值为状态。

对于这个问题，我们还得老老实实从头想起。问一问自己：我们关心的是什么？

在取花的过程中，要保证高度是递增的。我们唯一需要考虑的就是**之前取的那朵花高度是多少**，然后当前的花要更高。

- 考虑一个朴素的 dp 状态：

$dp(i)$ 表示以高度为 $i$ 的花结尾的子序列的最大价值

- 转移公式：
$$dp(i)=\max\limits_{j=1}^{i-1} \{dp(j)
\}+a_i$$                          
这种朴素的 dp 时间复杂度为 $O(n^2)$，会超时，我们的优化策略要通过观察转移公式来得到。

- 优化：观察转移公式可以发现：**每个 dp 值都由这段 dp 值前连续的一段 dp 值中最大值转移而来**。但是因为为花的高度是无序的，前缀 max 来维护最大值并不理想。考虑使用**线段树**维护区间最大值。这样每次转移进行**区间查询**和**单点修改**即可。

如果不了解线段树的同学可以看这篇博客[线段树详解](https://blog.csdn.net/zearot/article/details/48299459)。

时间复杂度：状态 $O(n)$，转移 $O(\log n)$，总复杂度 $O(n\log n)$。

空间复杂度：$O(n)$


------------

### 代码
```cpp
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pii pair<int,int>
#define mp make_pair
#define F first
#define S second
using namespace std;
int n,h[200005];
ll a[200005],dp[200005],mx[800005],ans;
//以下到33行的部分都是维护区间最大值的线段树
void PushUp(int rt)//上推{mx[rt]=max(mx[rt<<1],mx[rt<<1|1]);}
void Update(int L,ll C,int l,int r,int rt)
{//单点修改
	if (l==r){
		mx[rt]=max(mx[rt],C);
		return;
	}
	int mid=(l+r)>>1;
	if (L<=mid) Update(L,C,l,mid,rt<<1);
	else Update(L,C,mid+1,r,rt<<1|1);
	PushUp(rt);
}
ll Query(int L,int R,int l,int r,int rt)
{//区间查询
	if (L<=l&&r<=R)
		return mx[rt];
	int mid=(l+r)>>1;
	ll res=0;
	if (L<=mid) res=max(res,Query(L,R,l,mid,rt<<1));
	if (R>mid) res=max(res,Query(L,R,mid+1,r,rt<<1|1));
	return res;
}
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>h[i];
	for(int i=0;i<n;i++)
		cin>>a[i];
	for(int i=0;i<n;i++)
	{//转移同时维护线段树
		dp[h[i]]=Query(0,h[i]-1,0,n,1)+a[i];
		Update(h[i],dp[h[i]],0,n,1);
		ans=max(ans,dp[h[i]]);
	}
	cout<<ans<<endl;
	return 0;
}
```
~~我承认我有复制板子的成分。~~ 如果你有兴趣，可以上 atcoder 看一下[巨佬 Errichto 的代码](https://atcoder.jp/contests/dp/submissions/4303731)，
他的线段树写的很飘逸。

希望题解对你有帮助！

---

