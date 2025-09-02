# Blog Post Rating

## 题目描述

It's well-known that blog posts are an important part of Codeforces platform. Every blog post has a global characteristic changing over time — its community rating. A newly created blog post's community rating is 0. Codeforces users may visit the blog post page and rate it, changing its community rating by +1 or -1.

Consider the following model of Codeforces users' behavior. The $ i $ -th user has his own estimated blog post rating denoted by an integer $ a_{i} $ . When a user visits a blog post page, he compares his estimated blog post rating to its community rating. If his estimated rating is higher, he rates the blog post with +1 (thus, the blog post's community rating increases by 1). If his estimated rating is lower, he rates the blog post with -1 (decreasing its community rating by 1). If the estimated rating and the community rating are equal, user doesn't rate the blog post at all (in this case we'll say that user rates the blog post for 0). In any case, after this procedure user closes the blog post page and never opens it again.

Consider a newly created blog post with the initial community rating of 0. For each of $ n $ Codeforces users, numbered from 1 to $ n $ , his estimated blog post rating $ a_{i} $ is known.

For each $ k $ from 1 to $ n $ , inclusive, the following question is asked. Let users with indices from 1 to $ k $ , in some order, visit the blog post page, rate the blog post and close the page. Each user opens the blog post only after the previous user closes it. What could be the maximum possible community rating of the blog post after these $ k $ visits?

## 样例 #1

### 输入

```
4
2 0 2 2
```

### 输出

```
1
1
2
2
```

## 样例 #2

### 输入

```
7
2 -3 -2 5 0 -3 1
```

### 输出

```
1
0
-1
0
1
1
2
```

# 题解

## 作者：Alex_Wei (赞：8)

> [CF773E Blog Post Rating](https://www.luogu.com.cn/problem/CF773E)

首先可以证明 $a$ 单调不降一定是最优的，交换任意逆序对答案总不劣，分类讨论即可，具体细节略去。

根据 $a$ 的单调性，我们考虑当前帖子的评级，它一定是先单调减，再单调不降。如果我们知道了拐点 $p$，也就是评级的最低点，那么在 $p$ 之后的 $a_i$ 的贡献形如 “最终值不会超过 $a_i + (k - i)$”，拆成 $k + \min (a_i - i)$ 可权值线段树维护。因为 $a_i$ 表示值，$i$ 表示排名，所以线段树上每个叶子维护 $v_i$ 表示 $i - c_i$，其中 $c_i$ 表示 $\leq i$ 的值的个数，非叶子维护 $v_i$ 区间最小值。修改形如从 $a_i$ 开始的后缀 $-1$，打懒标记即可，查询时查从 $p$ 开始的后缀最小值。

问题变成了求解拐点 $p$。可知若 $-c_i \leq i$，则拐点一定在 $i$ 或 $i$ 之前，因为 $i$ 之后不会再减小了。如果在 $j > i$ 处继续减小，那么评级从 $-c_i$ 变成 $-c_i - 1$，必须满足 $j < -c_i$，这与 $-c_i \leq i < j$ 矛盾。因此，二分出第一个 $-c_p \leq p$ 的位置 $p$，则 $p$ 为拐点。

线段树二分实现上述过程，时间复杂度 $\mathcal{O}(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define TIME 1e3 * clock() / CLOCKS_PER_SEC
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ull = unsigned long long;
inline ll read() {
  ll x = 0, sgn = 0;
  char s = getchar();
  while(!isdigit(s)) sgn |= s == '-', s = getchar();
  while(isdigit(s)) x = x * 10 + s - '0', s = getchar();
  return sgn ? -x : x;
}
inline void print(int x) {
  if(x < 0) return putchar('-'), print(-x);
  if(x >= 10) print(x / 10);
  putchar(x % 10 + '0');
}
bool Mbe;
constexpr int N = 5e5 + 5;
int n, num[N << 3], val[N << 3], laz[N << 3];
void tag(int x, int v) {val[x] += v, laz[x] += v;}
void down(int x) {if(laz[x]) tag(x << 1, laz[x]), tag(x << 1 | 1, laz[x]), laz[x] = 0;}
void build(int l, int r, int x) {
  if(l == r) return val[x] = l, void();
  int m = l + r >> 1;
  build(l, m, x << 1), build(m + 1, r, x << 1 | 1);
  val[x] = min(val[x << 1], val[x << 1 | 1]);
}
void modify(int l, int r, int p, int x) {
  num[x]++;
  if(l == r) return;
  int m = l + r >> 1;
  if(p <= m) modify(l, m, p, x << 1);
  else modify(m + 1, r, p, x << 1 | 1);
}
void add(int l, int r, int p, int x) {
  if(p <= l) return tag(x, -1);
  int m = l + r >> 1;
  down(x);
  if(p <= m) add(l, m, p, x << 1);
  add(m + 1, r, p, x << 1 | 1);
  val[x] = min(val[x << 1], val[x << 1 | 1]);
}
int binary(int l, int r, int x, int pref) {
  if(-(pref + num[x]) > r) return -N;
  if(l == r) return l;
  int m = l + r >> 1;
  int res = binary(l, m, x << 1, pref);
  return res == -N ? binary(m + 1, r, x << 1 | 1, pref + num[x << 1]) : res;
}
int query(int l, int r, int p, int x) {
  if(p <= l) return val[x];
  int m = l + r >> 1, ans = 0;
  down(x);
  if(p <= m) ans = min(ans, query(l, m, p, x << 1));
  ans = min(ans, query(m + 1, r, p, x << 1 | 1));
  return ans;
}
bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  cin >> n, build(-N, N, 1);
  for(int i = 1; i <= n; i++) {
    int a = read();
    modify(-N, N, a, 1), add(-N, N, a, 1);
    int p = binary(-N, N, 1, 0);
    cout << i + query(-N, N, p, 1) << "\n";
  }
  cerr << TIME << " ms\n";
  return 0;
}
/*
2022/9/22
author: Alex_Wei
start coding at 
finish debugging at 10:09
*/
```

---

## 作者：shao0320 (赞：7)

#### CF773E Blog Post Rating

首先%前两篇题解，Orz。

先不考虑加入操作，考虑暴力求一次$F$的过程。

手玩即可发现，一定是到一个点之前一直减，而之后单调不降的。

那么显然$a[x]=-x$的时候是分界点。

于是考虑二分这个分界点。

设$f[i]$表示到$i$这个点，点赞的值，可以发现$f[i]=\min(f[i-1]+1,a[i])$

展开得$f[i]=\min(a[x]+i-x,...,a[i-2]+2,a[i-1]+1,a[i])$。

考虑多次操作，每次加入一个数，线段树维护后缀最小值和前缀的分界点位置即可。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1000005
#define MAXN 500005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
struct Segment1
{
	int tag[N*4],L[N*4],R[N*4],v[N*4];
	void build(int l,int r,int k)
	{
		L[k]=l;R[k]=r;
		if(l==r){v[k]=l;return;}
		int mid=(l+r)>>1;
		build(l,mid,k*2);build(mid+1,r,k*2+1);
		v[k]=max(v[k*2],v[k*2+1]);
	}
	void pushdown(int k)
	{
		v[k*2]+=tag[k];v[k*2+1]+=tag[k];
		tag[k*2]+=tag[k];tag[k*2+1]+=tag[k];
		tag[k]=0;
	}
	void modify(int l,int r,int k,int x,int y,int val)
	{
		if(l>=x&&r<=y){v[k]+=val;tag[k]+=val;return;}
		int mid=(l+r)>>1;pushdown(k);
		if(x<=mid)modify(l,mid,k*2,x,y,val);
		if(y>mid)modify(mid+1,r,k*2+1,x,y,val);
		v[k]=max(v[k*2],v[k*2+1]);
	}
	int query(int l,int r,int k)
	{
		if(l==r)return l;
		int mid=(l+r)>>1;pushdown(k);
		if(v[k*2]>=0)return query(l,mid,k*2);
		return query(mid+1,r,k*2+1);
	}
}S;
struct Segment2
{
	int tag[N*4],L[N*4],R[N*4],v[N*4];
	void build(int l,int r,int k)
	{
		L[k]=l;R[k]=r;
		if(l==r){v[k]=l;return;}
		int mid=(l+r)>>1;
		build(l,mid,k*2);build(mid+1,r,k*2+1);
		v[k]=min(v[k*2],v[k*2+1]);
	}
	void pushdown(int k)
	{
		v[k*2]+=tag[k];v[k*2+1]+=tag[k];
		tag[k*2]+=tag[k];tag[k*2+1]+=tag[k];
		tag[k]=0;
	}
	void modify(int l,int r,int k,int x,int y,int val)
	{
		if(l>=x&&r<=y){v[k]+=val;tag[k]+=val;return;}
		int mid=(l+r)>>1;pushdown(k);
		if(x<=mid)modify(l,mid,k*2,x,y,val);
		if(y>mid)modify(mid+1,r,k*2+1,x,y,val);
		v[k]=min(v[k*2],v[k*2+1]);
	}
	int query(int l,int r,int k,int x,int y)
	{
		if(l>=x&&r<=y)return v[k];
		int mid=(l+r)>>1,res=0x3f3f3f3f;pushdown(k);
		if(x<=mid)res=min(res,query(l,mid,k*2,x,y));
		if(y>mid)res=min(res,query(mid+1,r,k*2+1,x,y));
		return res;
	}
}T;
int n;
int main()
{
	S.build(-MAXN,0,1);T.build(-MAXN,MAXN,1);
	n=read();
	for(int i=1;i<=n;i++)
	{
		int x=read();
		if(x<0)S.modify(-MAXN,0,1,x,0,1);
		//cout<<"!!!!"<<i<<endl;
		T.modify(-MAXN,MAXN,1,-MAXN,x-1,1);
		int pos=S.query(-MAXN,0,1);
		//cout<<"!!!"<<pos<<endl;
		printf("%d\n",T.query(-MAXN,MAXN,1,pos,MAXN));
	}
	return 0;
}
```



---

## 作者：sry_ (赞：3)

假设 $\forall i,A_i>0$ ，保证 $A$ 排序，且初始时 $F=0$ ，我们如何计算最后的 $F$ 。

设 $F_i$ 表示通过 $i$ 这段区间的 $F$ ，$cnt_i$ 表示 $A$ 序列中有多少个 $i$ 。

则 $F_i=\min\{F_{i-1}+cnt_i,i\}$。 等价于 $F_i=\min\{F_{i-1},i-cnt_i\}+cnt_i$ 。

推导可得 $F_n=\sum_{i=0}^n cnt_i+\min_i\{i-\sum_{j=0}^i cnt_j\}$ 。

考虑一开始 $F_0$ 如果是负数，那么答案可以写成 $F_n=\sum_{i=0}^n cnt_i+\min\{\min_i\{i-\sum_{j=0}^i cnt_j\},F_0\}$ 。

这个算法为啥要保证 $A_i>0$ ，其实我们只要保证 $F\leq A_1$ 即可，即无 $3$ 操作的情况。

考虑有 $3$ 操作，即为 $\exists i,A_i<0$ 的情况，那么我们肯定能找到一个阀值使得后面均无 $3$ 操作。

最后一个 $3$ 操作出现的地方一定是满足单调性的，即找到 $A_i\geq -i$ ，然后二分即可。然后套用上述做法即可。

时间复杂度 $O(n\log^2 n)$ 。

---

## 作者：chenzida (赞：3)

这题首先谢谢中文翻译，帮我去掉了一个贪心难点（

这题借鉴了@sry_大佬的

首先声明，本人做法两个 $log$，能过纯属数据谁+CF的时间限制比较大。

我们可以发现，由于这个数列是有序的，所以我们可以发现，$F$ 一定是先降后增的，然后我们随便搞搞就可以发现一个柿子。

$$F[n]=\sum_{i=0}^{n}cnt_i+\min(\min_{i\le n}(i-\sum_{j=0}^{i}cnt_j),F[0])$$

然后我们二分一下断电并同值域线段树维护即可。

```
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
using namespace std;
const int NR=1e6+10;
const int MAX=5e5;
int n,q;
int a[NR];
struct Seg
{
	int tr[NR<<2],lz[NR<<2];
	void update(int rt){tr[rt]=min(tr[rt*2],tr[rt*2+1]);}
	void build(int rt,int l,int r) 
	{
		if(l==r){tr[rt]=l;return;}
		int mid=(l+r>>1);
		build(rt*2,l,mid),build(rt*2+1,mid+1,r);
		update(rt);
	}
	void push_down(int rt)
	{
		if(!lz[rt])return;int x=lz[rt];
		tr[rt*2]+=x,tr[rt*2+1]+=x;
		lz[rt*2]+=x,lz[rt*2+1]+=x;
		lz[rt]=0;
	}
	void change(int rt,int l,int r,int L,int R,int val)
	{
		if(l==L&&r==R){tr[rt]+=val,lz[rt]+=val;return;}
		int mid=(l+r>>1);push_down(rt);
		if(R<=mid)change(rt*2,l,mid,L,R,val);
		else if(L>mid)change(rt*2+1,mid+1,r,L,R,val);
		else change(rt*2,l,mid,L,mid,val),change(rt*2+1,mid+1,r,mid+1,R,val);
		update(rt);
	}
	int query(int rt,int l,int r,int L,int R)
	{
		if(l==L&&r==R)return tr[rt];
		int mid=(l+r>>1);push_down(rt);
		if(R<=mid)return query(rt*2,l,mid,L,R);
		else if(L>mid)return query(rt*2+1,mid+1,r,L,R);
		else return min(query(rt*2,l,mid,L,mid),query(rt*2+1,mid+1,r,mid+1,R));
		update(rt);
	}
}S;
struct Seg2
{
	int tr[NR<<2];void Init(){memset(tr,0,sizeof(tr));}
	void update(int rt){tr[rt]=tr[rt*2]+tr[rt*2+1];}
	void change(int rt,int l,int r,int x,int val)
	{
		if(l==r){tr[rt]+=val;return;}int mid=(l+r>>1);
		if(x<=mid)change(rt*2,l,mid,x,val);
		else change(rt*2+1,mid+1,r,x,val);
		update(rt);
	}
	int query(int rt,int l,int r,int L,int R)
	{
		if(l==L&&r==R)return tr[rt];int mid=(l+r>>1);
		if(R<=mid)return query(rt*2,l,mid,L,R);
		else if(L>mid)return query(rt*2+1,mid+1,r,L,R);
		else return query(rt*2,l,mid,L,mid)+query(rt*2+1,mid+1,r,mid+1,R);
	}
	int find(int rt,int l,int r,int x)
	{
		if(l==r)return l;int mid=(l+r>>1);
		if(tr[rt*2]<x)return find(rt*2+1,mid+1,r,x-tr[rt*2]);
		else return find(rt*2,l,mid,x);
	}
}T;
int all,min_n=0x3f3f3f3f;
void insert(int x)
{
	S.change(1,-MAX,MAX,x,MAX,-1);
	T.change(1,-MAX,MAX,x,1);
	all++;min_n=min(min_n,x);
}
int query(int pos,int num)
{
	int cnt=T.query(1,-MAX,MAX,pos,MAX);
	int min_n=min(num,S.query(1,-MAX,MAX,pos,MAX)+(all-cnt));
	return cnt+min_n;
}
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int main()
{
//	freopen(".in","r",stdin);
//	freopen("1.out","w",stdout);
	q=read();S.build(1,-MAX,MAX);T.Init();
	while(q--)
	{
		int x=read();insert(x);
		if(min_n>=0){printf("%d\n",query(0,0));continue;}
		int l=1,r=all,ans=-1;
		while(l<=r)
		{
			int mid=(l+r>>1);
			if(T.find(1,-MAX,MAX,mid)<=-mid)ans=mid,l=mid+1;
			else r=mid-1;
		}
		if(ans==-1||ans==all){printf("%d\n",-all);continue;}
		int now=T.find(1,-MAX,MAX,ans+1);
		printf("%d\n",query(now,-ans));
	}
	return 0;
}
```

---

## 作者：xfrvq (赞：1)

[$\tt Link$](/problem/CF773E)，$\tt^\ast3000$。

我们考虑对于一个序列它的 $F$ 值怎么算。

+ 首先是序列的负数部分，这里 $F$ 会一直减。
+ 到了某个位置 $p$ 后，不再会发生 $a_i\lt F$，$F$ 不降。

我们找到最小的位置 $j$ 使得 $j$ 与小于 $j$ 的数个数加起来 $\ge0$，这时有 $p=j$。

那么这个可以通过线段树区间 $+1$ 以及线段树上二分实现。

考虑记 $F_i$ 代表 $F(a_1,\cdots,a_i)$。

那么有 $F_i=\min\{F_{i-1}+1,a_i\}$，即 $F_i=\min\{a_i,a_{i-1}+1,a_{i-2}+2,\cdots\}$。

这个就是值域线段树的区间 $+1$ 区间 $\min$ 了。

---

## 作者：pitiless0514 (赞：1)

## Statement

有不错的翻译，看翻译吧。

## Solution

一个显然的贪心想法是对于每个 $i$，将 $1\sim i$ 的人按 $a_i$ 从小到大排序，在当前情况下会最优。

~~事实上这道题的洛谷翻译告诉了你这个结论~~！

注意到这样做 $F$ 会先减后增，对于一个排序后的序列前缀 $1\sim x$，这些元素都会带来 $-1$ 的贡献，后面的数的贡献会是 $0, 1$。

因为每次询问和上一次询问只会加入一个数，自然的考虑当前处理完了前 $i - 1$ 个询问，当前答案为 $ans$，这次询问 $1 \sim i$ 的答案。

我们加入元素的时候需要知道他和上一次的答案 $ans$ 之间的一个大小关系，这个在初始序列排序后建一课线段树可以维护。

然后用三个 $\text{set}$ 维护当前贡献为 $-1,0,1$ 的数的集合。

每次加入一个数的时候，我们首先询问他和 $ans$ 的差 $c$，然后分类讨论。

- $c=0$，两数相等，他会造成 $0$ 的贡献，将当前数加入 $s_0$ 即可。
- $c > 0$ ，当前加入的数比 $ans$ 大，于是他会造成 $1$ 的贡献，那么比他大的数和 $ans$ 之间的大小关系就会 $-1$，如果这些数中有些数变得比执行到他的时候的 $ans$ 小了，那么对于这些数中最左边的那个数的贡献会变成 $0$。
- $c < 0$，当前加入的数比 $ans$ 小，于是他会造成 $-1$ 的贡献，那么比他大的数和 $ans$ 之间的大小关系就会 $+1$，如果这些贡献为 $-1$ 的数中最右边的数，顺序操作到他的时候，和他所预期的值一样大了，那么他的贡献会变成 $0$，然后就可以结束了。否则的话，在最左边的 $0$ 的贡献会变成 $1$。

直接做就好了，复杂度是 $O(n \log n)$ 的。

```cpp
// 德丽莎你好可爱德丽莎你好可爱德丽莎你好可爱德丽莎你好可爱德丽莎你好可爱
// 德丽莎的可爱在于德丽莎很可爱，德丽莎为什么很可爱呢，这是因为德丽莎很可爱！
// 没有力量的理想是戏言，没有理想的力量是空虚
#include <bits/stdc++.h>
#define LL long long
using namespace std;
char ibuf[1 << 15], *p1, *p2;
#define getchar() (p1 == p2 && (p2 = (p1 = ibuf) + fread(ibuf, 1, 1 << 15, stdin), p1==p2) ? EOF : *p1++)
inline int read() {
  char ch = getchar();  int x = 0, f = 1;
  while (ch < '0' || ch > '9')  {  if (ch == '-')  f = -1;  ch = getchar();  }
  while (ch >= '0' && ch <= '9')  x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
  return x * f;
}
void print(LL x) {
  if (x > 9)  print(x / 10);
  putchar(x % 10 + '0');
}
template<class T> bool chkmin(T &a, T b) { return a > b ? (a = b, true) : false; }
template<class T> bool chkmax(T &a, T b) { return a < b ? (a = b, true) : false; }
#define rep(i, l, r) for (int i = (l); i <= (r); i++)
#define repd(i, l, r) for (int i = (l); i >= (r); i--)
#define REP(i, l, r)  for (int i = (l); i < (r); i++)
const int N = 2e6, inf = 2e7;
int n, pos[N], tag[N];
pair <int,int> a[N], s[N];
int ls(int p) {  return p << 1;  }
int rs(int p) {  return p << 1 | 1;  }
void pushup(int p) {  
  s[p] = min(s[ls(p)], s[rs(p)]);
}
void build(int p,int l,int r) {
  if (l == r) {  s[p] = {a[l].first, l};  return;  }
  int mid = (l + r) >> 1;   build(ls(p), l, mid), build(rs(p), mid + 1, r);  pushup(p);
}
void pushdown(int p) {
  if (!tag[p])  return;
  s[ls(p)].first += tag[p];  s[rs(p)].first += tag[p];
  tag[ls(p)] += tag[p];  tag[rs(p)] += tag[p];  tag[p] = 0;
}
void change(int p,int l,int r,int nx,int ny,int val) {
  if (nx <= l && r <= ny) {  s[p].first += val;  tag[p] += val;  return;  } 
  pushdown(p);
  int mid = (l + r) >> 1;
  if (nx <= mid)  change(ls(p), l, mid, nx, ny, val);
  if (ny > mid)  change(rs(p), mid + 1, r, nx, ny, val);  pushup(p);
}
pair <int,int> ask(int p,int l,int r,int nx,int ny) {
  if (nx <= l && r <= ny)  return s[p];
  pushdown(p);
  int mid = (l + r) >> 1;
  pair <int,int> ans = {inf, inf};
  if (nx <= mid)  chkmin(ans, ask(ls(p), l, mid, nx, ny));
  if (ny > mid)  chkmin(ans, ask(rs(p), mid + 1, r, nx, ny));  pushup(p);
  return ans;
}
set <int> s0, s1, sdel;
void solve() {
  n = read();
  rep (i, 1, n)  a[i].first = read(), a[i].second = i;
  sort(a + 1, a + n + 1);
  rep (i, 1, n)  pos[ a[i].second ] = i;
  build(1, 1, n);
  rep (j, 1, n) {
    int i = pos[j];
    auto p = ask(1, 1, n, i, i);
    if (!p.first) {  s0.insert(i);  }
    if (p.first > 0) {
      s1.insert(i);
      change(1, 1, n, i, n, -1);
      auto t = ask(1, 1, n, i, n);
      if (t.first < 0)  s1.erase(t.second), s0.insert(t.second), change(1, 1, n, t.second, n, 1);
    }
    if (p.first < 0) {
      sdel.insert(i);
      change(1, 1, n, i, n, 1);
      auto it = sdel.end();  --it;
      if (a[*it].first == 1 - sdel.size())  {
        int val = (*it);
        sdel.erase(it);
        s0.insert(val);
        change(1, 1, n, val, n, -1);
      }  else if (s0.size()) {
        auto it2 = s0.begin();
        int val = *it2;
        s0.erase(it2);
        s1.insert(val);
        change(1, 1, n, val, n, -1);
      }
    }
    printf("%d\n", s1.size() - sdel.size());
  }
}
signed main () {
#ifdef LOCAL_DEFINE
  freopen("1.s1", "r", stdin);
  freopen("1.ans", "w", stdout);
#endif
  int T = 1;  while (T--)  solve();
#ifdef LOCAL_DEFINE
  cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
  return 0;
}
```

---

## 作者：xcyyyyyy (赞：0)

相邻数调整法可知顺序的时候答案最大。

方便表述称序列 $a$ 里面的数为风向标。

先减后加，我们分成两个过程进行求解。

减的过程，需要二分最小的位置 $-x(x\gt 0)$，使得 $\leq-x$ 的风向标数量大于等于 $x$。减的过程最终一定会减到 $x$。

加的过程，可以看成位置和风向标的匹配，考虑霍尔定理：若 $x$ 合法，则 $\forall i\leq x$，$x-i+1\leq num$($num$ 为 $\geq i$ 的风向标的个数)。也就是说，$x$ 需要满足 $\forall i\leq x,x\leq i+num-1$。对每个 $i$ 维护 $i+num-1$ 即可。最大的 $x$ 即为答案。

两个过程均可以线段树二分。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ls u<<1
#define rs u<<1|1
#define N 1000005
int n,a[N];
int mn[N*4],num[N*4],tag[N*4];
//i+num-1->mn
void pull(int u){
	mn[u]=min(mn[ls],mn[rs]);
	num[u]=num[ls]+num[rs];
}
void push(int u){
	if(!tag[u])return;
	mn[ls]+=tag[u];
	tag[ls]+=tag[u];
	mn[rs]+=tag[u];
	tag[rs]+=tag[u];
	tag[u]=0;
}
void build(int u,int l,int r){
	if(l==r)return mn[u]=l-1,num[u]=0,void();
	int m=(l+r)>>1;
	build(ls,l,m),build(rs,m+1,r);
	pull(u);
}
void upd(int u,int l,int r,int L,int R){
	if(L<=l&&r<=R)return ++mn[u],++tag[u],void();
	int m=(l+r)>>1;push(u);
	if(m>=L)upd(ls,l,m,L,R);
	if(m<R) upd(rs,m+1,r,L,R);
	pull(u);
}
void upd(int u,int l,int r,int x){
	if(l==r)return ++num[u],void();
	int m=(l+r)>>1;push(u);
	if(m>=x)upd(ls,l,m,x);
	else upd(rs,m+1,r,x);
	pull(u);
}
int qry(int u,int l,int r,int lsum){
	if(l==r)return l;
	int m=(l+r)>>1;push(u);
	if(-m<=lsum+num[ls])return qry(ls,l,m,lsum);
	else return qry(rs,m+1,r,lsum+num[ls]);
}
int prmn;//init
int qry2(int u,int l,int r,int L,int R){//start from st+1
	// fprintf(stderr,"%d %d %d %d %d\n",u,l,r,L,R);
	if(L<=l&&r<=R){
		
		if(min(prmn,mn[u])>=r)return prmn=min(prmn,mn[u]),-1e9;
		while(l!=r){
			int m=(l+r)>>1;push(u);
			if(min(prmn,mn[ls])>=m)prmn=min(prmn,mn[ls]),u=rs,l=m+1;
			else u=ls,r=m;
		}
		return l-1;
	}
	int m=(l+r)>>1,ans=-1e9;push(u);
	if(m>=L)ans=qry2(ls,l,m,L,R);
	if(ans==-1e9&&m<R)ans=qry2(rs,m+1,r,L,R);
	return ans;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	build(1,-5e5,5e5);
	for(int i=1;i<=n;i++){
		upd(1,-5e5,5e5,a[i]);
		upd(1,-5e5,5e5,-5e5,a[i]);
		int s=qry(2,-5e5,0,0);
		prmn=1e9;
		printf("%d\n",qry2(1,-5e5,5e5,s+1,5e5));
	}
}
```

---

## 作者：liaoz123 (赞：0)

## 基本结论：
**从小到大**排序一定最优。  

感性证明一下：如果存在一个逆序对 $a_i>a_j,i<j$，如果在 $i,j$ 处均造成了 $+1$ 或 $-1$ 的贡献，交换之后影响不变。如果二者造成的贡献不同，则将 $a_i$ 放到后面，可以尽量使得 $-1$ 的次数更少，而 $+1$ 的贡献更多。因此从小到大排序一定最优。
## 做法
重排之后，我们的 $F$ 值呈现出先严格递减，再单调不降的一个 $V$ 字形，设这个分界点为 $pos$。

考虑在单调递增的一段，每个 $a_i$ 实际的作用，其实是限制了最终答案的取值，若当前序列长度为 $len$，则每个 $a_i$ 都限制了最终答案不会超过 $len-i+a_i$。则最终答案为：
$$\min_{i>=pos}{len-i+a_i}$$

这个东西可以使用权值线段树实现。考虑线段树上的一个权值点 $i$，设 $c_i$ 表示小于等于 $i$ 的数的个数，改写上述式子：
$$\min_{i>=pos}{len-c_i+i}=len+\min_{i>=pos}i-c_i$$

我们在线段树中只要维护 $i-c_i$ 即可。

初始建树，给每个节点 $i$ 赋上初始值 $i$。考虑加入一个数 $j$ 的影响，所有 $i>=j$ 的节点的 $c_i$ 都会增加 $1$，因此只需要在区间 $[j,N]$ 上加上 $-1$ 即可。

考虑如何求出这个分界点 $pos$。我们发现满足 $-c_i\le i$ 的最小的 $j$ 就是这个分界点。首先如果所有数都是正数，结论显然。那么对于负数，$-c_i\le i$ 说明小于等于 $i$ 的数已经大于等于 $|i|$，$F$ 的图像已经达到了一个转折点，已经不存在更小的数，使得 $F$ 的值可以继续 $-1$。从此往后 $F$ 单调不降。

有了这个结论以后，我们便可以在线段树上二分求得 $pos$。

至此，问题已经完全解决。
```cpp
#include<bits/stdc++.h>
#define mid (l+r>>1)
#define ls (k<<1)
#define rs (k<<1|1)
using namespace std;
const int M=5e5,N=1e6+5;
struct node{
	int mi,tag,c;
}s[N<<2];
void pushup(int k){
	s[k].mi=min(s[ls].mi,s[rs].mi);
	s[k].c=s[ls].c+s[rs].c;
}
void build(int k,int l,int r){
	if(l==r){
		s[k].mi=l;
		return;
	}
	build(ls,l,mid);
	build(rs,mid+1,r);
	pushup(k); 
}
void due(int k,int z){
	s[k].mi+=z;
	s[k].tag+=z;
}
void pushdown(int k){
	if(!s[k].tag)return;
	due(ls,s[k].tag);
	due(rs,s[k].tag);
	s[k].tag=0;
}
void insert(int k,int l,int r,int x){
	s[k].c++;
	if(l==r)return;
	pushdown(k);
	if(x<=mid)insert(ls,l,mid,x);
	else insert(rs,mid+1,r,x);
}
void change(int k,int l,int r,int x,int y,int z){
	if(l>y||r<x)return;
	if(l>=x&&r<=y){
		due(k,z);
		return;
	}
	pushdown(k);
	change(ls,l,mid,x,y,z);
	change(rs,mid+1,r,x,y,z);
	pushup(k);
}
int find(int k,int l,int r,int sum){
	if(-(sum+s[k].c)>r)return -M;
	if(l==r)return l;
	pushdown(k);
	int res=find(ls,l,mid,sum);
	if(res!=-M)return res;
	return find(rs,mid+1,r,sum+s[ls].c);
}
int query(int k,int l,int r,int x,int y){
	if(l>y||r<x)return 2e9;
	if(l>=x&&r<=y)return s[k].mi;
	pushdown(k);
	return min(query(ls,l,mid,x,y),query(rs,mid+1,r,x,y));
}
int n,a[N],pos;
int main(){
	//freopen("input.in","r",stdin);
	scanf("%d",&n);
	build(1,-M,M);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		insert(1,-M,M,a[i]);
		change(1,-M,M,a[i],M,-1);
		pos=find(1,-M,M,0);
		printf("%d\n",query(1,-M,M,pos,M)+i);
	}
	return 0;
}
```

---

## 作者：chlchl (赞：0)

题意翻译会害死人。

题意实际上是：对于序列 $A$，设 $x=0$，接着按顺序将 $x$ 与 $A_i$ 比较。
- $x<a_i$，$x\leftarrow x+1$；
- $x>a_i$，$x\leftarrow x-1$；
- $x=a_i$，$x$ 不变。

最后得到的 $x$ 就是 $A$ 的 $F$ 值。

现在给定一个序列 $a$，你要求出：对于 $a$ 的每一个前缀，重排后最大可能的 $F$ 值。

## Solution
这东西一看就得先找结论，考虑如何重排是最优的。

可以发现，当 $a_i>a_{i+1}$ 时，交换两个数显然不劣。先让 $x$ 经过小的肯定是比较优秀的。

所以最优答案肯定是将前缀递增排序后得到的 $x$。

考虑 $x$ 会如何变化。记 $x_i$ 为通过前 $i$ 个数后的 $F$ 值。

模拟样例可以发现，$x$ 一定先单调递减一段后单调不降，这其中存在一个拐点 $p$（$p$ 若不存在设为 $0$，即 $p$ 是下降的结束点）。

假设我们知道了 $p$，那么 $x_p=-p$。对于之后的每一个 $i$，都有 $x_{i-1}\le a_i$。
- $x_{i-1}<a_i$，那么 $x_i\leftarrow x_{i-1}+1$。
- $x_{i-1}=a_i$，那么 $x_i\leftarrow a_i$。

所以 $x_i=\min(x_{i-1}+1,a_i)$。

但我们对于每个前缀都要维护这个东西，并不方便，考虑将其展开。

$x_{i-1}+1=\min(x_{i-2}+2,a_{i-1}+1)$。你发现这是个递归式，可以直接展开到最后。

所以得到 $x_i=\min\{a_{k}+i-k\}=i+\min\{a_k-k\}$。

我们可以用一棵值域线段树维护 $a_k-k$ 的最小值。

将拐点的位置转变为值域。因为是从前往后遍历，所以每次插入一个数 $a_i$ 后，查询时必定是 $1\sim i$ 这个前缀的答案，区间查询 $[p,+\infty )$ 的最小值即可。

**这里注意，$k$ 代表的是 $a_i$ 在从小到大排序后所在的位置，所以 $k$ 是小于等于 $a_i$ 的数的个数。**

初始将线段树 $v$ 的位置赋成 $v$。每次加入 $a_i$ 时，我们要区间更新比它小的数，即将 $(-\infty,a_i)$ 区间 $+1$。

这个理解起来不难，比如你是 $3,10,2$，现在插入了 $5$，那么你需要把 $3,2$ 对应的位置都加上 $1$，这样 $a_4=5$ 对应的 $x_4=\min\{a_2+2,a_3+1,a_5\}$。

那么现在的问题只剩下，如何求 $p$。

$p$ 满足 $-p\le a_p$，$p$ 之前的位置都满足 $-i>a_i$，因此 $p$ 是第一个 $a_p+p\ge 0$ 的位置。

$p$ 仍然与上述 $k$ 的意义是相同的。

仍然用值域线段树维护 $a_p+p$ 的最大值。每次插入 $a_i$，就将 $[a_i+\infty)+1$。

查询时在线段树上二分即可。

总时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
const int M = 500000 + 5;
const int xyr = 5e5 + 10;
int n;
int a[M];
struct node{
	int num, id;
} b[M], c[M];

struct pos_segment_tree{
	int mx[N << 2], tag[N << 2];
	
	#define ls(o) (o << 1)
	#define rs(o) (o << 1 | 1)
	
	void build(int o, int l, int r){
		if(l == r){
			mx[o] = l;
			return ;
		}
		int mid = (l + r) >> 1;
		build(ls(o), l, mid);
		build(rs(o), mid + 1, r);
		mx[o] = max(mx[ls(o)], mx[rs(o)]);
	}
	
	void pushdown(int o){
		tag[ls(o)] += tag[o];
		tag[rs(o)] += tag[o];
		mx[ls(o)] += tag[o];
		mx[rs(o)] += tag[o];
		tag[o] = 0;
	}
	
	void update(int o, int l, int r, int s, int t, int x){
		if(l >= s && r <= t){
			mx[o] += x;
			tag[o] += x;
			return ;
		}
		pushdown(o);
		int mid = (l + r) >> 1;
		if(s <= mid)
			update(ls(o), l, mid, s, t, x);
		if(t > mid)
			update(rs(o), mid + 1, r, s, t, x);
		mx[o] = max(mx[ls(o)], mx[rs(o)]); 
	}
	
	int query(int o, int l, int r){
		if(l == r)
			return l;
		pushdown(o);
		int mid = (l + r) >> 1;
		if(mx[ls(o)] >= 0)
			return query(ls(o), l, mid);
		return query(rs(o), mid + 1, r);
	}
} Pos;
//用于寻找拐点 

struct val_segment_tree{
	int mn[N << 2], tag[N << 2];
	
	#define ls(o) (o << 1)
	#define rs(o) (o << 1 | 1)

	void build(int o, int l, int r){
		if(l == r){
			mn[o] = l;
			return ;
		}
		int mid = (l + r) >> 1;
		build(ls(o), l, mid);
		build(rs(o), mid + 1, r);
		mn[o] = min(mn[ls(o)], mn[rs(o)]);
	}
	
	void pushdown(int o){
		tag[ls(o)] += tag[o];
		tag[rs(o)] += tag[o];
		mn[ls(o)] += tag[o];
		mn[rs(o)] += tag[o];
		tag[o] = 0;
	}
	
	void update(int o, int l, int r, int s, int t, int x){
		if(l >= s && r <= t){
			mn[o] += x;
			tag[o] += x;
			return ;
		}
		pushdown(o);
		int mid = (l + r) >> 1;
		if(s <= mid)
			update(ls(o), l, mid, s, t, x);
		if(t > mid)
			update(rs(o), mid + 1, r, s, t, x);
		mn[o] = min(mn[ls(o)], mn[rs(o)]); 
	}
	
	int query(int o, int l, int r, int s, int t){
		if(l >= s && r <= t)
			return mn[o];
		pushdown(o);
		int mid = (l + r) >> 1, res = 1e9;
		if(s <= mid)
			res = min(res, query(ls(o), l, mid, s, t));
		if(t > mid)
			res = min(res, query(rs(o), mid + 1, r, s, t));
		return res;
	}
} Val;

int main(){
	scanf("%d", &n);
	for(int i=1;i<=n;i++)
		scanf("%d", &a[i]);
	Pos.build(1, -xyr, 0);
	Val.build(1, -xyr, xyr);
	for(int i=1;i<=n;i++){
		if(a[i] < 0)//a[i] 大于 0 对寻找拐点是没有意义的，所以只记录 a[i] < 0 的信息 
			Pos.update(1, -xyr, 0, a[i], 0, 1);//区间 +1
		Val.update(1, -xyr, xyr, -xyr, a[i] - 1, 1); 
		int pos = Pos.query(1, -xyr, 0);//找到拐点 
//		cout << pos << endl;
		printf("%d\n", Val.query(1, -xyr, xyr, pos, xyr));//查询后缀最小值 
	}
	return 0;
}
```

---

