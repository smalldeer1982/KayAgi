# Sum Over Zero

## 题目描述

You are given an array $ a_1, a_2, \ldots, a_n $ of $ n $ integers. Consider $ S $ as a set of segments satisfying the following conditions.

- Each element of $ S $ should be in form $ [x, y] $ , where $ x $ and $ y $ are integers between $ 1 $ and $ n $ , inclusive, and $ x \leq y $ .
- No two segments in $ S $ intersect with each other. Two segments $ [a, b] $ and $ [c, d] $ intersect if and only if there exists an integer $ x $ such that $ a \leq x \leq b $ and $ c \leq x \leq d $ .
- For each $ [x, y] $ in $ S $ , $ a_x+a_{x+1}+ \ldots +a_y \geq 0 $ .

The length of the segment $ [x, y] $ is defined as $ y-x+1 $ . $ f(S) $ is defined as the sum of the lengths of every element in $ S $ . In a formal way, $ f(S) = \sum_{[x, y] \in S} (y - x + 1) $ . Note that if $ S $ is empty, $ f(S) $ is $ 0 $ .

What is the maximum $ f(S) $ among all possible $ S $ ?

## 说明/提示

In the first example, $ S=\{[1, 2], [4, 5]\} $ can be a possible $ S $ because $ a_1+a_2=0 $ and $ a_4+a_5=1 $ . $ S=\{[1, 4]\} $ can also be a possible solution.

Since there does not exist any $ S $ that satisfies $ f(S) > 4 $ , the answer is $ 4 $ .

In the second example, $ S=\{[1, 9]\} $ is the only set that satisfies $ f(S)=9 $ . Since every possible $ S $ satisfies $ f(S) \leq 9 $ , the answer is $ 9 $ .

In the third example, $ S $ can only be an empty set, so the answer is $ 0 $ .

## 样例 #1

### 输入

```
5
3 -3 -2 5 -4```

### 输出

```
4```

## 样例 #2

### 输入

```
10
5 -2 -4 -6 2 3 -6 5 3 -2```

### 输出

```
9```

## 样例 #3

### 输入

```
4
-1 -2 -3 -4```

### 输出

```
0```

# 题解

## 作者：Usada_Pekora (赞：12)

嗯，五分钟推完然后写了个暴力发现 wa on pretest4 就弃了，结果是对的。

题意：选出一些连续的区间，满足每个选出的区间的数的和都是非负的，求选出区间的最大长度总和。

维护一个前缀和 $s$，若 $s_i-s_{j}\geq 0$，则 $[j+1,i]$ 是一个合法的区间，此时再加上 $[0,j]$ 的最优长度即可。即，令 $dp_i$ 表示以 $i$ 为结尾的最长合法区间，$pre_i$ 表示以 $[0,i]$ 中某个点为结尾的最长合法区间，有 $dp_i=\max\limits^{i-1}_{j=0,s_i-s_j\geq 0}{pre_j+i-j},{pre_i}=\max\limits_{j=0}^i {dp_j}$，枚举 $i$，枚举 $j$，复杂度 $O(n^2)$。

$pre$ 的快速求法可以用前缀最大值解决，至于 $dp$，我们考虑把对应的值存到值域而不是下标里，即，对于每个相等的 $s_j$，存下最大的 $pre_j-j$，然后就变成了查询 $(-\infty,s_i]$ 里的最大值，用线段树解决就好了。

```cpp
#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int N = 2e5 + 5;
/*
ez to solve:
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < i; j++)
			if (sum[i] - sum[j] >= 0)
				dp[i] = max(dp[i], pre[j] + i - j);
		pre[i] = max(pre[i - 1], dp[i]);
	}
	cout << pre[n] << endl;
but i give up

si ma le, bi xu li san hua.
*/
int a[N];
int ls[N << 5], rs[N << 5], val[N << 5], n, idx, rt, dp[N], pre[N];
ll sum[N];
inline void modify(int &p, int l, int r, int x, int k) {
	if (!p)
		val[p = ++idx] = INT_MIN;
	val[p] = max(val[p], k);
	if (l == r)
		return;
	int mid = (l + r) >> 1;
	if (x <= mid)
		modify(ls[p], l, mid, x, k);
	else
		modify(rs[p], mid + 1, r, x, k);
}
inline int query(int p, int l, int r, int L, int R) {
	if (!p)
		return INT_MIN;
	if (L <= l && r <= R)
		return val[p];
	int mid = (l + r) >> 1, res = INT_MIN;
	if (L <= mid)
		res = max(res, query(ls[p], l, mid, L, R));
	if (R > mid)
		res = max(res, query(rs[p], mid + 1, r, L, R));
	return res;
}
signed main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++) 
		sum[i] = sum[i - 1] + a[i];
	vector<ll> lsh;
	for (int i = 0; i <= n; i++)
		lsh.emplace_back(sum[i]);
	sort(lsh.begin(), lsh.end());
	unique(lsh.begin(), lsh.end());
	int k = lsh.size();
	for (int i = 0; i <= n; i++)
		sum[i] = lower_bound(lsh.begin(), lsh.end(), sum[i]) - lsh.begin() + 1;
	modify(rt, 1, k, sum[0], 0);
	for (int i = 1; i <= n; i++) {
		dp[i] = query(rt, 1, k, 1, sum[i]) + i;
		pre[i] = max(pre[i - 1], dp[i]);
		modify(rt, 1, k, sum[i], pre[i] - i);
	}
	cout << pre[n] << endl;
	return 0;
}
```

---

## 作者：_cyle_King (赞：8)

> 血的教训：CF 上千万不要和 C/D 死磕，不然可能 E 送分都拿不到。

$\tiny{\color{White}\text{并且你连 D 都没有磕出来。}}$

## 题意
给定一个长度为 $n$ 的整数序列 $a$。定义一个二元组集合 $S=\{(x,y)|1\leq x\leq y\leq n\}$ 是合法的，当且仅当：
1. 对于任意的一个 $t(1\leq x\leq n)$，不存在 $1\leq i<j\leq |S|$，使得 $x_i\leq t\leq y_i\And x_j\leq t\leq y_j$。
2. $\forall 1\leq i\leq |S|,\sum\limits_{j=x_i}^{y_i}a_j\geq 0$。

定义 $S$ 的价值为 $\sum\limits_{i=1}^{|S|}(y_i-x_i+1)$，求所有合法的 $|S|$ 的最大价值。
### 数据范围
$1\leq n\leq 2\times10^5,|a_i|\leq 10^9$

## 分析
显然，就是从 $[1,n]$ 中扣掉一些点，使得剩下的点组成的极长子串的和都不小于 $0$。

考虑 dp，设 $f_i$ 为考虑区间 $[1,i]$ 的 $S$ 的最大价值，分 $i$ 选/不选考虑，枚举上一段区间的结尾，有
$$
f_i=\max\{f_{i-1},\max_{0\leq j<i,\sum\limits_{k=j+1}^{i-1}a_k\geq 0}\{f_j+i-j\}\}
$$
边界 $f_0=0$。

显然直接转移是 $O(n^2)$ 的。

转移中最烦人的地方就是那个字段和为非负数的限制了，因为这个限制与 $a$ 的值相关，考虑使用值域上的数据结构维护。

令当前计算的是 $f_i$，设 $sum_j=\sum_{k=j}^ia_k$，则能转移到 $i$ 的 $j$ 要满足 $sum_{j}\geq 0$，即
$$
f_i=\max\{f_{i-1},i+\max_{sum_j\geq 0}\{f_j-j\}\}
$$
转移前，要动态维护全局的 $sum_j$，即全局 $sum_j$ 加上一个 $a_i$。转移后，要动态插入一个点，权值为 $a_i$，映射值 $f_i-i$。

因此我们要使用的数据结构要能支持：
1. 全局加上一个数。
2. 动态插入一个数。
3. 查询大于或等于 $0$ 的数的映射值的最大值。

集合类数据结构，果断使用平衡树。
### Code
赛后打完的，CF 上可以 AC。$\tiny{\color{White}{\text{前提是去掉防抄袭。}}}$
```cpp
#include<cstdio>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cmath>
#include<climits>
#include<ctime>
#include<chrono>
#include<cassert>
#include<algorithm>
#include<iterator>
#include<numeric>
#include<vector>
#include<queue>
#include<stack>
#include<set>
#include<map>
#include<bitset>
#include<functional>
#include<random>

using namespace std;
template<class T1,class T2>inline bool cmax(T1 &a,T2 b) {return a<b?a=b,1:0;}
template<class T1,class T2>inline bool cmin(T1 &a,T2 b) {return b<a?a=b,1:0;}
typedef pair<int,int> pii;
typedef long long LL;

const int N=2e5+10,INF=0x3f3f3f3f;

mt19937 gen(chrono::system_clock::now().time_since_epoch().count());
//mt19937 gen(114514);
uniform_int_distribution<int>dist(1,1e9);

int n,a[N+1];
struct 
FHQ{
    int ls,rs,dp,key,sdp;
    LL sum,tag;
}tree[N+1];
int f[N+1];
#define ls(p) tree[p].ls
#define rs(p) tree[p].rs
#define dp(p) tree[p].dp
#define key(p) tree[p].key
#define sdp(p) tree[p].sdp
#define sum(p) tree[p].sum
#define tag(p) tree[p].tag
int root,tot;

inline void
push_up(int p){
    sdp(p)=dp(p);
    if(ls(p))cmax(sdp(p),sdp(ls(p)));
    if(rs(p))cmax(sdp(p),sdp(rs(p)));
    return ;
}

inline void
update(int p,int x){
    sum(p)+=x,tag(p)+=x;
}

inline void
push_down(int p){
    if(!tag(p))return ;
    if(ls(p))update(ls(p),tag(p));
    if(rs(p))update(rs(p),tag(p));
    tag(p)=0;
    return ;
}

inline void
split(int p,int &x,int &y,LL v){
    if(!p)return void(x=y=0);
    push_down(p);
    while(1)cout<<"Never gonna give you up, never gonna let you down."<<endl;
    if(sum(p)>=v)y=p,split(ls(p),x,ls(y),v);
    else x=p,split(rs(p),rs(x),y,v);
    push_up(p);
}

inline int
merge(int x,int y){
    if(!x||!y)return x+y;
    int p;
    push_down(x),push_down(y);
    if(key(x)<key(y))p=x,rs(x)=merge(rs(x),y);
    else p=y,ls(y)=merge(x,ls(y));
    push_up(p);
    return p;
}

inline int
newnode(int x,int y){
    int p=++tot;
    key(p)=dist(gen),dp(p)=sdp(p)=x,sum(p)=y;
    return p;
}

int
main(){
    //freopen("QWQ.in","r",stdin);
    //freopen("WQW.out","w",stdout);
    ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    sdp(0)=dp(0)=-INF;
    root=merge(root,newnode(0,0));
    for(int i=1,x,y;i<=n;i++){
        update(root,a[i]);
        split(root,x,y,a[i]);
        root=merge(merge(x,newnode(f[i-1]-i+1,a[i])),y);
        split(root,x,y,0);
        f[i]=max(f[i-1],sdp(y)+i);
        root=merge(x,y);
    }
    //for(int i=1;i<=n;i++)cout<<f[i]<<' ';
    //cout<<'\n';
    cout<<f[n]<<endl;
    return 0;
}

```
$\tiny{\color{White}{\text{Never gonna give you up, never gonna let you down.}}}$
## 后话
1. ~~不要妄想最后 15 分钟一棵平衡树（带调试），你不是 lxl~~。
2. 请不要 Ctrl A + Ctrl C + Ctrl V。一是违规，二是这样不利于提升能力。$\tiny{\color{White}{\text{三是有防抄袭代码片段，四是不想让你看见隐藏文字}}}$。

# End







---

## 作者：洛浔 (赞：4)

## E 题解

### 一些声明

$dp_i$ 表示到位置 $i$ 为止有多少点**没有选**。

$sum_i$ 表示 $\sum_{i=1}^{n}a_i$。

关于为什么要令 $dp_i$ 是没有选的最优解：$dp$ 表示选与不选在复杂度 $O(n^2)$ 时是都可以实现的，但是在复杂度 $O(n\log{n})$ 时，由于要将之前的信息放到数据结构里，这个信息是不能随位置而改变的，但是如果是 $dp_i$ 表示选的话，dp 转移方程就是 $dp_i=\max(dp_j+i-j)$，这个信息会改变所以不适合用数据结构维护。这也是“正难则反”的思想。

### 朴素 dp

$dp_i$ 可以由两种方法转移:

1. $dp_i$ 不取，此时 $dp_i=dp_{i-1}+1$。
2. $dp_i$ 取，从 $1$ 到 $i-1$ 枚举 $j$。考虑什么样的 $j$ 可以转移，即 $j+1$ 到 $i$ 这一段都取了，即 $sum_i-sum_j\geq0$。此时 $dp_i=\min(dp_j)$。

复杂度 $O(n^2)$。

```cpp
for(int i=1;i<=n;i++){
    dp[i]=dp[i-1]+1;
    for(int j=1;j<i;j++)
        if(sum[i]>=sum[j])
            dp[i]=min(dp[i],dp[j+1]);
}
```

### 如何优化

这个 dp 的复杂度不够优秀，我们考虑用数据结构维护。

发现对于 $i$ 查询的是，位置在 $i$ 之前，前缀和小于 $i$ 的所有 $dp$ 的最小值。用线段树（其他数据结构也可以）维护这个信息。

将前缀和离散化，更新时查询比当前前缀和小的最小值，在完成 $dp_i$ 的更新之后将其插入线段树。

复杂度 $O(n\log{n})$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
template<class T>void read(T &x){
    x=0;long long f=0;char ch=getchar();
    while(ch<'0'||ch>'9')  {f|=(ch=='-');ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x=f?-x:x;return;
}
const long long N=2e5+5;
long long n,val[N],dp[N],sum[N],cpy[N];
struct node{
    long long val;
}a[N*20];
void build(long long p,long long l,long long r){
    a[p].val=0x3f3f3f3f;
    if(l==r) return ;
    long long mid=l+r>>1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
}
void update(long long p,long long l,long long r,long long pos,long long val){
    if(l==r){a[p].val=min(a[p].val,val);return ;}
    long long mid=(l+r)>>1;
    if(pos<=mid) update(p<<1,l,mid,pos,val);
    else update(p<<1|1,mid+1,r,pos,val);
    a[p].val=min(a[p<<1].val,a[p<<1|1].val);
}
long long query(long long p,long long l,long long r,long long L,long long R){
    if(L<=l&&R>=r) return a[p].val;
    long long mid=l+r>>1,ret=0x3f3f3f3f;
    if(L<=mid) ret=min(ret,query(p<<1,l,mid,L,R));
    if(R>mid) ret=min(ret,query(p<<1|1,mid+1,r,L,R));
    return ret;
}
main(){
    read(n);
    for(long long i=1;i<=n;i++)read(val[i]),sum[i]=val[i]+sum[i-1],cpy[i]=sum[i];
    sort(cpy,cpy+n+1);
    long long len=unique(cpy,cpy+n+1)-cpy;
    build(1,0,len);
    long long rnk_0=lower_bound(cpy,cpy+len,0)-cpy;
    update(1,0,len,rnk_0,0);
    for(long long i=1;i<=n;i++){
        dp[i]=dp[i-1]+1;
        if(sum[i]>=0) dp[i]=0;
        long long pos=lower_bound(cpy,cpy+len,sum[i])-cpy;
        long long tmp=query(1,0,len,0,pos);
        dp[i]=min(dp[i],tmp);
        update(1,0,len,pos,dp[i]);
    }
    printf("%lld\n",n-dp[n]);
    return 0;
}
```


---

## 作者：yuanruiqi (赞：2)

## 题意简述

给定一个数组，找到几个不重合的，且元素和不小于 $0$ 的子串，最大化长度和。

## 题目分析

先将数组求前缀和，那么从中找到两点使得后面的值大于等于前面的值，就等价于找到一个符合题意的子串。可以考虑 DP。将数组离散化，构建线段树维护最大值，遍历数组第 $i$ 个元素时向线段树第 $a_{i}$ 项插入 $i-1$
 时的答案减 $i$，查询线段树 $1$ 到 $a_{i}$ 的最大值并加上 $i$ 即为当前的答案。
## 代码

```cpp
const int maxn = 200000 + 10;
struct segtree
{
    long long t[maxn<<2];
    void init()
    {
        memset(t, 0xcf, sizeof(t));
    }
    void pushup(int rt)
    {
        t[rt] = max(t[rt<<1], t[rt<<1|1]);
    }
    long long query(int rt, int l, int r, int L, int R)
    {
        if (L <= l && r <= R) return t[rt];
        long long ans = 0xcfcfcfcfcfcfcfcf;
        int mid = (l + r) >> 1;
        if (L <= mid) ans = query(rt<<1, l, mid, L, R);
        if (mid < R) ans = max(ans, query(rt<<1|1, mid+1, r, L, R));
        return ans;
    }
    void update(int rt, int l, int r, int q, long long v)
    {
        if (l == r)
        {
            t[rt] = max(t[rt], v);
            return;
        }
        int mid = (l + r) >> 1;
        if (q <= mid) update(rt<<1, l, mid, q, v);
        else update(rt<<1|1, mid+1, r, q, v);
        pushup(rt);
    }
} T;
void solve()
{
    int n;
    cin >> n;
    vector<long long> a(n+1, 0), h(n+1, 0);
    for (int i=1;i<=n;++i)
        cin >> a[i];
    for (int i=1;i<=n;++i)
        a[i] += a[i-1], h[i] = a[i];
    sort(h.begin(), h.end());
    auto x = unique(h.begin(), h.end());
    for (int i=0;i<=n;++i)
        a[i] = lower_bound(h.begin(), x, a[i]) - h.begin() + 1;
    long long ans = 0;
    T.init();
    T.update(1, 1, n+1, a[0], 0);
    for (int i=1;i<=n;++i)
    {
        T.update(1, 1, n+1, a[i], ans - i);
        ans = max(ans, T.query(1, 1, n+1, 1, a[i]) + i);
    }
    cout << ans << '\n';
}
```


---

## 作者：ImALAS (赞：2)

[Link.](https://www.luogu.com.cn/problem/CF1788E)

令 $s_i=\sum\limits_{k=1}^i a_k$。

定义 $dp_i$ 表示前 $i$ 个数中所能组成的集合的 $f(S)$ 最大值，并且强制选中点 $i$。

转移方程：

$$
dp_i=\max\{dp_{i-1},\max_{j\in [0,i-1],s_j\le s_i}\{\{\max_{k\in [0,j]}dp_k\}+i-j\}\}
$$

令 $sum_i=\max\limits_{k\in [0,i]} dp_k$，则可以将上式优化至 $\mathcal O(n^2)$。

然后我们发现，$j\lt i,s_j\le s_i$ 是典型的偏序关系，因此不难想到用 CDQ 分治和单调栈优化这个 DP 过程。

一个小细节，CDQ 分治中，要先 `solve(l,mid)`，然后处理左半区间对右边的贡献，最后再 `solve(mid+1,r)`。这是因为左区间对右边的影响若不先计算，则右区间的决策点集合不完整。

感觉这样的计算顺序似乎无法归并排序，就用了 `std::sort`，时间复杂度 $\mathcal O(n\log^2 n)$，跑得还是挺快的。有 CDQ 的 $\mathcal O(n\log n)$ 做法欢迎提出 qwq。

```cpp
// Problem: Sum Over Zero
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1788E
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using i64 = long long;

const int maxn = 2e5 + 5;
int n,f[maxn],sum[maxn],b[maxn],c[maxn],stk[maxn],tp;
i64 s[maxn];

void solve(int l,int r) {
	if(l == r) {
		sum[l] = f[l];
		if(l)
			sum[l] = std::max(sum[l] , sum[l - 1]);
		return ;
	}
	int mid = (l + r) >> 1;
	solve(l , mid);
	for(int i = l;i <= mid;++ i)
		c[i] = i;
	for(int i = mid + 1;i <= r;++ i)
		b[i] = i;
	std::sort(c + l , c + 1 + mid , [&](const int& x,const int &y) {
		return s[x] < s[y];
	});
	std::sort(b + mid + 1 , b + r + 1 , [&](const int& x,const int& y) {
		return s[x] < s[y];
	});
	stk[tp = 0] = 0;
	for(int i = l,k = mid + 1;k <= r;++ k) {
		while(i <= mid&&s[c[i]] <= s[b[k]]) {
			while(tp > 0&&sum[stk[tp]] - stk[tp] <= sum[c[i]] - c[i])
				stk[tp --] = 0;
			stk[++ tp] = c[i ++];
		}
		if(tp > 0)
			f[b[k]] = std::max(f[b[k]] , sum[stk[1]] + b[k] - stk[1]);
	}
	solve(mid + 1 , r);
	return ;
}

int main() {
	scanf("%d",&n);
	for(int i = 1;i <= n;++ i)
		scanf("%lld",&s[i]),s[i] += s[i - 1];
	solve(0 , n);
	printf("%d\n",sum[n]);
	return 0;
}
```

---

## 作者：EBeason (赞：1)

### 思路
首先我们观察题，先考虑 $\mathcal{O}(N^2)$ 做法，我们很容易就可以列一个转移方程。  
先求一下前缀和 `sum`。    
如果 $sum_i \ge sum_j$，则有 $F_i = \max(F_i, F_j + i - j)$。  
如果 $sun_i < sum_j$，则有 $F_i = \max(F_i, F_j)$。  
得到这个之后再考虑怎么进行优化，很明显我们将 $F_i - i$ 添加到平衡树中，然后用 $sum_i$ 作为平衡树的排序关键词。   
最后献上我丑陋的代码。  
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll
const int MaxN = 1e6 + 100;
const int INF = 1e18;
int T, N, M, a[MaxN];
int F[MaxN], sum[MaxN];
int num, rt, t1, t2, t3, ans;
struct Point
{
	int p, v, l, r, maxn;
	int ts;
} tree[MaxN];
inline void updata(int x)
{
	tree[x].maxn = max(tree[tree[x].l].maxn, tree[tree[x].r].maxn);
	tree[x].maxn = max(tree[x].maxn, tree[x].ts);
}
inline int add1(int v, int ts)
{
	int x = ++num;
	tree[x].l = tree[x].r = 0;
	tree[x].v = v;
	tree[x].maxn = tree[x].ts = ts;
	tree[x].p = rand();
	return x;
}
void split(int x, int k, int &l, int &r)
{
	if (!x)
	{
		l = r = 0;
		return;
	}
	if (tree[x].v <= k)
	{
		l = x;
		split(tree[x].r, k, tree[x].r, r);
	}
	else
	{
		r = x;
		split(tree[x].l, k , l, tree[x].l);
	}
	updata(x);
}
int hebin(int x, int y)
{
	if (!x || !y)
		return x + y;
	if (tree[x].p < tree[y].p)
	{
		tree[x].r = hebin(tree[x].r, y);
		updata(x);
		return x;
	}
	else
	{
		tree[y].l = hebin(x, tree[y].l);
		updata(y);
		return y;
	}
}
inline void Solve()
{
	cin >> N;
	tree[0].maxn = -INF;
	for (int i = 1 ; i <= N; i++)
	{
		cin >> a[i];
		sum[i] = sum[i - 1] + a[i];
	}
	rt = add1(0, 0);
	for (int i = 1; i <= N; i++)
	{
		F[i] = ans;
		split(rt, sum[i], t1, t3);
		int jg = tree[t1].maxn;
		F[i] = max(F[i], i + jg);
		rt = hebin(hebin(t1, add1(sum[i], F[i] - i)), t3);
		ans = max(ans, F[i]);
	}
	cout << F[N];
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	T = 1;
	while (T--)
		Solve();
}
```

---

## 作者：whdywjd (赞：1)

这篇题解试图讲得浅显易懂一些。

首先先感谢 @一个程序员 @Max_s_xaM 和我讨论出这个解法。

考虑 dp。

设 $dp[i]$ 表示只考虑前 $i$ 个数时最多能选多少数。$dp[n]$ 即为答案。

则 $dp[i]=\max(dp[i-1],dp[j]+i-j)$（需满足 $\sum_{k=j+1}^ia[k]\geq0$）

什么意思呢？

首先，继承 $dp[i-1]$ 表示不选 $i$，直接按前 $i-1$ 个数的最优方案来。

其次，如果 $a$ 数组 $[j+1,i]$ 中数的和非负（$\sum_{k=j+1}^ia[k]\geq0$），则可以在 $dp[j]$ 的基础上加上 $[j+1,i]$ 的长度，表示选中这段区间。

可惜该做法是 $O(n^2)$ 的，需要优化。

我们之后暂不考虑转移方程里 $dp[i-1]$ 的部分，因为这部分比较好搞。

设 $pre[i]=\sum_{j=1}^ia[i]$，即为前缀和数组。

我们发现，$\sum_{k=j+1}^ia[k]\geq0$ 与 $pre[i]\geq pre[j]$ 等价。


所以，如果 $dp[j]$ 能转移到 $dp[i]$，则有：
- $j<i$
- $pre[j]\leq pre[i]$

我们发现，只用考虑 $[1,i-1]$ 中 $pre[j]$ 的值比较小的那些位置。

这让我们想到从 $dp[1]$ 到 $dp[n]$ 依次求出，用数据结构（线段树/树状数组）在 $pre[j]$ 的值域上维护。

方便起见，设该数据结构为 $T$，$T[i]$ 表示 $T$ 维护的第 $i$ 个位置，$T.\max[l,r]$ 表示 $T$ 中 $[l,r]$ 位置的最大值。

所以，先对 $pre[0\dots n]$ 离散化，设 $v[i]$ 表示 $pre[i]$ 离散化后的值。

初始化时，对于任意 $i$，$T[i]=0$。

确定 $dp[j]$ 之后，根据转移方程中的式子 $dp[j]+i-j$，我们发现 $dp[j]-j$ 是个关键量。如果要把某个 $dp[j]$ 继承到 $dp[i]$，只需在 $\max(dp[j]-j)$ 的基础上加上 $i$ 即可。因此，将 $T[v[j]]$ 改为 $\max(T[v[j]],dp[j]+n-j)$（加 $n$ 是为了避免结果为负数）。

由此得到初始条件：$dp[0]=0,T[v[0]]=n$。

然后是求 $dp[i]$。

由于是顺序遍历，当前 $T$ 中的非 $0$ 位置都是在遍历到 $i$ 之前赋值的，因此求 $T.\max$ 能保证 $j<i$。

要保证 $pre[j]\leq pre[i]$（即 $v[j]\leq v[i]$），只需求 $T.\max[1,v[i]]$ 即可。它的意义是，在满足 $v[j]\leq v[i]$ 的前提下，最大的 $dp[j]+n-j$。为了把式子转化成 $dp[j]+i-j$，需要在 $T.\max[1,v[i]]$ 的基础上加上 $i-n$ 。

所以这就是核心部分：

1. $dp[i]\gets\max(dp[i-1],T.\max[1,v[i]]-n+i)$
2. $T[v[i]]\gets\max(T[v[i]],dp[i]+n-i)$

注意一点，就是当 $pre[j]\leq pre[i]$ 不存在时，$T.\max$ 会得到 $0$，所以不影响结果。

上代码：

```cpp
#include <algorithm>
#include <bitset>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#define ll long long
#define lf double
#define eps 1e-8
#define inf (1ll << 60)
#define pi 3.1415926535897932
#define _pb push_back
#define _mp make_pair
#define _1 first
#define _2 second
#define MAX_N 324304

using namespace std;

ll read(){ll x=0;char c=0,v=1;while(c<'0'||c>'9'){c=getchar();if(c=='-')v=-1;}while(!(c<'0'||c>'9')){x=(x<<1)+(x<<3)+c-'0';c=getchar();}return x*v;}void write(ll p){if(p<0){putchar('-');write(-p);return;}if(p<10){putchar(p+'0');return;}write(p/10);putchar((p%10)+'0');}
lf Read(){char c=0,v=1;lf x=0,u=1;while(48>c||57<c){c=getchar();if(c==45)v=-1;}while(47<c&&58>c){x=10.0*x+c-48.0;c=getchar();}if(c!='E'&&c!='e'&&c!='.')return v*x;else if(c=='.'){c=getchar();while(48>c||57<c)c=getchar();while(47<c&&58>c){x=10.0*x+c-48.0;c=getchar();u*=10;}}if(c!='E'&&c!='e')return v*x/u;ll y=0;lf e=1;char w=1;while(48>c||57<c){c=getchar();if(c==45)w=0;}while(47<c&&58>c){y=10*y+c-48;c=getchar();}if(w)while(y--)e*=10.0;else while(y--)e/=10.0;return v*x*e/u;}
char gtc(){char c;do c = getchar();while(c < 33);return c;}

template<size_t N, int s>
struct jnode // 离散化结构体
{
    int n, m;
    pair<ll, int> jv[N];
    int ja[N];
    ll jo[N];
    jnode() { n = s; }
    void insert(ll x) { jv[n] = _mp(x, n), n++; }
    void rebuild()
    {
        sort(jv + s, jv + n);
        for(int i = s; i < n; i++)
            if(i == s || jv[i]._1 != jv[i - 1]._1)
                jo[++m] = jv[i]._1, ja[jv[i]._2] = m;
            else
                ja[jv[i]._2] = m;
    }
    int operator [] (int x) { return ja[x]; }
    ll operator () (int id) { return jo[id]; }
    void upper_bound(ll x) { return upper_bound(jo + 1, jo + m + 1, x) - jo; }
    void lower_bound(ll x) { return lower_bound(jo + 1, jo + m + 1, x) - jo; }
}; // 离散化结构体

template<size_t N>
struct BIT1mx // 树状数组
{
    ll t[N];
    void update(int x, ll k) // T[x] = max(T[x], k);
    {
        for( ; x < N; x += (x & -x))
            t[x] = max(t[x], k);
    }

    ll query(int x) // max(T[1...x])
    {
        ll ans = 0;
        for( ; x; x -= (x & -x))
            ans = max(ans, t[x]);
        return ans;
    }
}; // 树状数组

jnode<MAX_N, 0> jc; // 离散化：jc[i] 表示pre[i]离散化后的结果，即 v[i]
BIT1mx<MAX_N> t;
int n;
ll a[MAX_N], dp[MAX_N];

void MAIN()
{
    n = read();
    jc.insert(0);
    for(int i = 1; i <= n; i++)
        jc.insert(a[i] = a[i - 1] + read()); // 计算前缀和并加入离散化结构体
    jc.rebuild();
    dp[0] = 0; // 初始化 dp[0]
    t.update(jc[0], n); // 将 T[v[0]] 赋值为 n
    for(int i = 1; i <= n; i++) // 顺序遍历求 dp 值
    {
        dp[i] = max(dp[i - 1], t.query(jc[i]) - n + i);
        t.update(jc[i], dp[i] + n - i);
    }
    printf("%lld\n", dp[n]);
}

void CLEAR()
{
    ;
}

void EXPERIMENT()
{
    ;
}

int main()
{
    //freopen("a.in", "r", stdin);
    //freopen("a.out", "w", stdout);
    EXPERIMENT();
    int T = 1;
    while(T--)
    {
        MAIN();
        CLEAR();
    }
    return 0;
}
```

---

