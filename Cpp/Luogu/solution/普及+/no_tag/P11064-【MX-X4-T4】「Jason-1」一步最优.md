# 【MX-X4-T4】「Jason-1」一步最优

## 题目背景

原题链接：<https://oier.team/problems/X4E>。

## 题目描述

对于如下问题：

- 给定长度为 $n$ 的数列 $a_1, \ldots, a_n$（其中 $a_i$ 可能为负数）以及一个正整数 $m$。
- 你需要选择不超过 $m$ 个数列 $a$ 的下标区间 $[l_j, r_j]$，且确保它们互不相交。
- 你需要最大化选择的区间中的元素之和的总和，即最大化 $\sum_j \sum_{i = l_j}^{r_j} a_i$。

考虑该贪心算法（并不正确）：

- 重复如下过程 $m$ 次：
- 在所有与当前已选择的区间不相交的区间（包括空区间）中，选择一个元素之和最大的区间。
  - **如果有多个元素之和最大的区间，从中任意选择一个。**
  - 注：若选择了空区间，等价于中止过程，即选择的区间数量不超过 $m$ 个。
- 将如上过程中选择的所有非空区间中的元素之和作为答案。

现给定 $n$ 和数列 $a_1, \ldots, a_n$，对于每个 $m \in [1, n]$，请求出该算法可能得到的答案（即区间和的总和）的最大值和最小值。

## 说明/提示

**【样例解释】**

对于第一组数据，

- 一种取到最大值的方案为，依次选择区间 $[1,1],[3,3],[5,5],\varnothing, \varnothing$；
- 一种取到最小值的方案为，依次选择区间 $[1,5],\varnothing,\varnothing,\varnothing,\varnothing$。

对于第二组数据，

- 一种取到最大值的方案为，依次选择区间 $[3,5],[1,1],\varnothing,\varnothing,\varnothing$；
- 一种取到最小值的方案为，依次选择区间 $[1,5],\varnothing,\varnothing,\varnothing,\varnothing$。

需要注意：在第一次更新时，无法选择区间 $[1,1],[1,3],[3,3]$ 等，因为它们不满足区间和在所有 $S$ 中的区间内最大（即 $= 3$）。在任意一次更新时，都无法选择区间 $[2,2]$，因为其区间和为 $-2$，而 $-2 < 0$（即空区间的区间和）。

对于第三组数据，只有唯一的选择方案，即依次选择区间 $[6,6],[1,2],[4,4],\varnothing,\varnothing,\varnothing$。


**【数据范围】**

**本题采用捆绑测试。**

| 子任务 | $n \le$ | $\sum n \le$ | 分值 |
| :----------: | :----------: | :----------: | :----------: |
| 1 | $10$ | $50$ | $17$ |
| 2 | $100$ | $500$ | $24$ |
| 3 | $2000$ | $10^4$ | $13$ |
| 4 | $10^4$ | $5 \times 10^4$ | $9$ |
| 5 | $10^5$ | $5 \times 10^5$ | $37$ |

对于 $100 \%$ 的数据，$1 \le T \le 10^4$，$1 \le n \le 10^5$，$\sum n \le 5 \times 10^{5}$，$|a_i| \le 10^9$。

## 样例 #1

### 输入

```
5
5
1 -1 1 -1 1
5
2 -2 2 -1 2
6
3 1 -4 1 -5 9 
13
1 1 -4 5 -1 -4 1 9 1 9 -8 1 0
16
1 -8 2 -7 3 -6 4 -5 5 -4 4 -3 3 -2 2 -1
```

### 输出

```
1 2 3 3 3
1 1 1 1 1
3 5 5 5 5
3 3 3 3 3
9 13 14 14 14 14
9 13 14 14 14 14
20 25 27 28 28 28 28 28 28 28 28 28 28
20 22 23 23 23 23 23 23 23 23 23 23 23
5 9 13 16 19 21 23 24 24 24 24 24 24 24 24 24
5 9 12 14 15 15 15 15 15 15 15 15 15 15 15 15
```

# 题解

## 作者：qfy123 (赞：9)

# P11064
Update on $2025.8.6$：大修。

[传送门](https://www.luogu.com.cn/problem/P11064)

前置知识：[线段树维护动态区间最大子段和](https://www.bilibili.com/video/BV1AN4y1d724/)以及[一道例题](https://www.luogu.com.cn/problem/P4513)。
## 思路
### 分析
首先有个贪心策略是显然的：当要使这个算法得到的答案最大时，每次取元素之和最大的区间中长度最短的那个区间；反之，每次取元素之和最大的区间中长度最长的那个区间。这很显然，因为每次增加值是 $\ge 0$ 的，所以在求最大或最小值时要尽量使选择次数多或少。

然后有个结论：在按照上述贪心选择的过程中，每次选择的区间一定是不交的，即，前面选择的区间不会影响后面的区间。

为何？试着证明一下：

假设能够在多个元素之和最大的区间中任取两个**不同的**区间 $[l_1,r_1]$ 和 $[l_2,r_2]$，满足这两个区间**有交而无包含关系**，即 $l_1 < l_2, r_1 < r_2$。

设他们的交为 $[l,r]$，记 $S = s_{l_1,r_1} = s_{l_2,r_2}$，现在考虑区间 $[l_1,r_2]$，根据容斥原理，$s_{l_1,r_2} = 2S - s_{l,r}$，而根据假设，$S \ge s_{l,r}$。综上 $s_{l_1,r_2} \ge S$。

对于 $s_{l_1,r_2} > S$ 的情况，与原假设矛盾，显然是选择 $[l_1,r_2]$ 更好。

对于相等的情况，不难发现，$[l,r]$ 的长度一定比区间 $[l_1,r_1]$ 和 $[l_2,r_2]$ 短，$[l_1,r_2]$ 的长度一定比区间 $[l_1,r_1]$ 和 $[l_2,r_2]$ 的长。那么对于贪心策略而言，一定是优先考虑 $[l,r]$ 或 $[l_1, r_2]$。

所以说无论如何，假设在一次选择中出现了一对相交而不包含的极大区间，那么一定会有更优的答案（区间的交或并），而像这样的有交集的区间会被排除，最终每次选择的区间就是无交集的了。
### 做法
有了这个结论，这道题就变成线段树维护动态区间最大子段和板子的加强版了。相比于板子题，这道题多了维护整个数组的所有的最大子段和中，长度最短和长度最长的区间最大子段和的左右端点。

那如何维护呢？其实就是在上传的时候分讨即可。如果不想分讨，也可以自己写一个比较函数来减小代码难度。

最后再说一下用完一个区间怎么处理的问题。其实就只要给这个区间的每个点的值改成 $-inf$。发现均摊下来每个点最多被修改一次，因此每次暴力单点修改即可。关于 $-inf$ 的取值，由于 $- 10 ^ 9 \times 10 ^ 5 = - 10 ^{14}$，并且要防止爆 long long。综上，$-inf$ 的取值最好是 $-10^{14}$。
## Code
```cpp
#include<bits/stdc++.h>
#define int long long 
#define ull unsigned long long
#define ri register int
#define rep(i,j,k) for(ri i=(j);i<=(k);++i) 
#define per(i,j,k) for(ri i=(j);i>=(k);--i)
#define repl(i,j,k,l) for(ri i=(j);(k);i=(l))
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define pc(x) putchar(x)
#define fir first
#define se second 
#define MP pair<int,int>
#define PB push_back
#define lson p << 1
#define rson p << 1 | 1
using namespace std;
char BUFFER[100000],*P1(0),*P2(0);
#define gtc() (P1 == P2 && (P2 = (P1 = BUFFER) + fread(BUFFER,1,100000,stdin), P1 == P2) ? EOF : *P1++)
inline int R(){
    int x;char c;bool f = 0;
	while((c = gtc()) < '0') if(c == '-') f = 1;
	x = c ^ '0';
	while((c = gtc()) >= '0') x = (x << 3) + (x << 1) + (c ^ '0');
	return f?(~x + 1):x;
}
inline void O(int x){
    if(x < 0) pc('-'),x = -x;
    if(x < 10) pc(x + '0');
    else O(x / 10),pc(x % 10 + '0');
}
inline void out(int x,int type){
	if(type == 1) O(x),pc(' ');
	if(type == 2) O(x),pc('\n');
	if(type == 3) O(x);
}
inline void OI(){
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
}
const int N = 2e5 + 10;
const int inf = 1e14;
struct S{
	int l, r, val;
};
//重写比较函数，避免分讨
S gmx1(S a, S b){
	if(a.val == b.val) return a.r - a.l > b.r - b.l? b : a;
	return a.val > b.val? a : b;
} 
S gmx2(S a, S b){
	if(a.val == b.val) return a.r - a.l < b.r - b.l? b : a;
	return a.val > b.val? a : b;
}

struct Tr{
	int l, r, sum;
	S mx, lmx, rmx;
}t1[N << 2],t2[N << 2];//t1：维护这种贪心方法所能取到的最大值，t2反之
int a[N],n,T,ans;
//pushup 大体和维护区间最大子段和是相同的，不做过多阐述
void pushup1(int p){
	t1[p].sum = t1[lson].sum + t1[rson].sum;
	t1[p].lmx = gmx1(t1[lson].lmx, (S){t1[lson].l, t1[rson].lmx.r, t1[lson].sum + t1[rson].lmx.val});
	t1[p].rmx = gmx1(t1[rson].rmx, (S){t1[lson].rmx.l, t1[rson].r, t1[rson].sum + t1[lson].rmx.val});
	t1[p].mx = gmx1(gmx1(t1[lson].mx, t1[rson].mx), (S){t1[lson].rmx.l, t1[rson].lmx.r, t1[lson].rmx.val + t1[rson].lmx.val});
}
void pushup2(int p){
	t2[p].sum = t2[lson].sum + t2[rson].sum;
	t2[p].lmx = gmx2(t2[lson].lmx, (S){t2[lson].l, t2[rson].lmx.r, t2[lson].sum + t2[rson].lmx.val});
	t2[p].rmx = gmx2(t2[rson].rmx, (S){t2[lson].rmx.l, t2[rson].r, t2[rson].sum + t2[lson].rmx.val});
	t2[p].mx = gmx2(gmx2(t2[lson].mx, t2[rson].mx), (S){t2[lson].rmx.l, t2[rson].lmx.r, t2[lson].rmx.val + t2[rson].lmx.val});
}
void build(int l, int r, int p, int mode){//mode = 1：处理最大值情况；mode = 2：处理最小值情况
	if(mode == 1){
		t1[p].l = l, t1[p].r = r;
		if(l == r){
			t1[p].sum = a[l];
			t1[p].mx = t1[p].lmx = t1[p].rmx = (S){l,l,a[l]};
			return;
		}
		int mid = (l + r) >> 1;
		build(l, mid, lson, mode);
		build(mid + 1, r, rson, mode);
		pushup1(p);
	}else{
		t2[p].l = l, t2[p].r = r;
		if(l == r){
			t2[p].sum = a[l];
			t2[p].mx = t2[p].lmx = t2[p].rmx = (S){l,l,a[l]};
			return;
		}
		int mid = (l + r) >> 1;
		build(l, mid, lson, mode);
		build(mid + 1, r, rson, mode);
		pushup2(p);		
	}
}
void modify(int l, int r, int p, int v, int mode){
	if(mode == 1){
		if(l == r){
			t1[p].sum = -inf;
			t1[p].rmx.val = t1[p].lmx.val = t1[p].mx.val = -inf;
			return;
		}
		int mid = (l + r) >> 1;
		if(v <= mid) modify(l, mid, lson, v, mode);
		else modify(mid + 1, r, rson, v, mode);
		pushup1(p);		
	}else{
		if(l == r){
			t2[p].sum = -inf;
			t2[p].rmx.val = t2[p].lmx.val = t2[p].mx.val = -inf;
			return;
		}
		int mid = (l + r) >> 1;
		if(v <= mid) modify(l, mid, lson, v, mode);
		else modify(mid + 1, r, rson, v, mode);
		pushup2(p);			
	}
}
signed main(){
	T = R();
	while(T--){
		n = R();
		rep(i, 1, n) a[i] = R();
		build(1, n, 1, 1);build(1, n, 1, 2);
		rep(i, 1, n){
			S x = t1[1].mx;//答案在线段树根结点处取得
			if(x.val > 0){
				ans += x.val;
				rep(j, x.l, x.r) modify(1, n, 1, j, 1);//每个点至多修改一次，因此暴力单点修改即可
			}
			out(ans, 1);
		}
		pc('\n'); ans = 0;
		rep(i, 1, n){
			S x = t2[1].mx;
			if(x.val > 0){
				ans += x.val;
				rep(j, x.l, x.r) modify(1, n, 1, j, 2);
			}
			out(ans, 1);
		}
		pc('\n'); ans = 0;
	}
	return 0;
}
```

---

## 作者：Crosser (赞：7)

提供一个不用任何区间查询 DS 的做法。

## Preface

$\text{*2300, Data Structure, Observation.}$

**如果你已经知道结论如何证明就直接跳到结论之后阅读**。

## Solution

注意到我们同时遇到几个最大区间的时候可能会有重叠，这样就会破坏掉所有有重叠的最大区间。如果没法全部取到 $\max,\min$ 就可以产生分歧。

- 对于孤立的区间没有所谓。
- 对于有交集但是没有被包含的区间。
	- 我们假定是 $xxxxyyyyzzzz$，两个区间分别是 $xxxxyyyy$ 和 $yyyyzzzz$。
	- 首先 $S(xxxx)=S(zzzz)> 0$，$S(yyyy) > 0$。
	- $S(xxxxyyyyzzzz)>S(xxxxyyyy)$，矛盾。
	- 说明没有，如果有就必须往两边取和为 $0$ 的区间，这就会被包含了。
- 被包含的区间。
	- 取了包含别人的，坏文明，取了最干净的，好文明。

**结论**：$\min$ 是要取最长的极大区间，$\max$ 就是要取最短的极大区间。

**接下来考虑如何快速实现。**

从大到小删是肯定慢的，我们只能考虑在扫一遍的时候把我们要删的区间找出来。我们来看这个问题具有什么性质。

考虑钦定区间的开头，要钦定区间结尾，某个位置它又小又近，那么就一定会被后面更大更远的位置给包含进去。你会发现这是一个**单调栈**的形式。钦定区间的结尾也是同理。

因此扫一遍，因为左端点要尽量小，所以维护一个**单调递减**的栈。同时应维护每个元素最优左端点的位置，在加入它时和栈顶元素轮流比较即可。此时如果**从右往左**贪心地取最优左端点就是我们想要的区间了。

两行输出之间只差了一些等号取舍问题。

## Implementation

[Link](https://www.luogu.com.cn/paste/blkyk40t)

为什么不封装？为什么不封装？

---

## 作者：ADNAP (赞：1)

**截止到2024.09.19 11:00保持着全场最劣解！**

### 思路
首先观察样例，例如第二组样例：

```
5
2 -2 2 -1 2
```

钦定想要最大化最大值，选择区间 $[1,3]$ 和 $[3,3]$ 或者是 $[1,1]$ 是贡献相同的，那我们当然优先选择 $[1,1]$ 或者 $[3,3]$，因为这样后续我们很可能两个区间都可以用到，但是如果我们选择了 $[1,3]$，剩下两个区间都不可选了。

感性地认知，可以得到结论：当一个区间包含另一个区间的时候，我们选择小的区间，这样剩下的部分还可能提供选择，总比没有选择要不劣。

接下来我们试图将这个结论拓展：

- 当两个区间没有交集的时候，我们确实可以任选，因为两个区间互不影响。当这两个区间为当前最大贡献时，不管我们怎么换顺序，都必然都会在后续操作中选择上。

- 如果两个区间不存在包含关系但又有交集时。不妨设两个区间分别是 $[l_1,r_1]$、$[l_2,r_2]$，并且有 $l_1 \le l_2 \le r_1 \le r_2$。那么对于区间 $[r_1,r_2]$，其贡献有两种情况：贡献为正，那么区间 $[l_1,r_1]$ 的贡献不如 $[l_1,r_2]$；贡献为负，那么区间 $[l_2,r_2]$ 的贡献不如 $[l_2,r_1]$。所以当我们考虑最优贡献的时候，不会产生两个区间不存在包含关系但又有交集的情况。

### 结论
因此最大值的求解方法是每次找贡献最大的区间，假若有多个就选择长度较小的；同理可以得到最小值的求解方法，每次找贡献最大的区间，假若有多个就选择较大的。

### Solution
**智商不够，数据结构来凑！**

先打个前缀和来计算区间和，记前缀和数组为 $sa$。

下面的分析以最大值为例。

对于每个右端点，我们将其当前最优的区间存到优先队列中，当然，如果贡献为负就不需要存到优先队列中了。

一开始，对于端点 $i$，我们要找到最优的左端点 $l$，使得 $sa_i-sa_{l-1}$ 最大，也就是找到最小的 $sa_{l-1}$，静态的区间最值问题，我们打一个 ST 表即可。

开一个结构体，存储优先队列中的元素信息，包括区间左端点 $l$、区间右端点 $r$、区间和 $s$。重载一下运算符，以贡献为第一关键字，区间长度为第二关键字重载小于号和大于号。

在计算贡献和时，取出优先队列队头元素，如果区间没有被标记，累加贡献，并用树状数组标记区间。如果区间被标记，我们更新右端点的最优区间，用二分法找到极大的未被标记的区间。再用一遍 ST 表即可。


```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> PLL;
#define x first
#define y second
#define mkp make_pair
const ll N=5e5+1e2;
ll T;
ll n;
ll a[N],sa[N];
ll lg2[N];
PLL stable_Max[20][N];
PLL stable_Min[20][N];
void init()
{
    for(ll i=2;i<N;i++)lg2[i]=lg2[i>>1]+1;
}
void build_ST()
{
    for(ll i=1;i<=n;i++)stable_Max[0][i]=mkp(sa[i],i);
    for(ll i=1;i<=lg2[n];i++)
        for(ll j=1;j+(1<<i)-1<=n;j++)
        {
            if(stable_Max[i-1][j].x<stable_Max[i-1][j+(1<<(i-1))].x)
                stable_Max[i][j]=stable_Max[i-1][j];
            else if(stable_Max[i-1][j].x>stable_Max[i-1][j+(1<<(i-1))].x)
                stable_Max[i][j]=stable_Max[i-1][j+(1<<(i-1))];
            else
            {
                if(stable_Max[i-1][j].y>stable_Max[i-1][j+(1<<(i-1))].y)
                    stable_Max[i][j]=stable_Max[i-1][j];
                else if(stable_Max[i-1][j].y<stable_Max[i-1][j+(1<<(i-1))].y)
                    stable_Max[i][j]=stable_Max[i-1][j+(1<<(i-1))];
                
            }
            
        }
    
    for(ll i=1;i<=n;i++)stable_Min[0][i]=mkp(sa[i],i);
    for(ll i=1;i<=lg2[n];i++)
        for(ll j=1;j+(1<<i)-1<=n;j++)
        {
            if(stable_Min[i-1][j].x<stable_Min[i-1][j+(1<<(i-1))].x)
                stable_Min[i][j]=stable_Min[i-1][j];
            else if(stable_Min[i-1][j].x>stable_Min[i-1][j+(1<<(i-1))].x)
                stable_Min[i][j]=stable_Min[i-1][j+(1<<(i-1))];
            else
            {
                if(stable_Min[i-1][j].y<stable_Min[i-1][j+(1<<(i-1))].y)
                    stable_Min[i][j]=stable_Min[i-1][j];
                else if(stable_Min[i-1][j].y>stable_Min[i-1][j+(1<<(i-1))].y)
                    stable_Min[i][j]=stable_Min[i-1][j+(1<<(i-1))];
            }
            
        }
    
}
PLL query_Max(ll l,ll r)
{
    ll lenth=lg2[r-l+1];
    if(stable_Max[lenth][l].x<stable_Max[lenth][r-(1<<lenth)+1].x)
        return stable_Max[lenth][l];
    else return stable_Max[lenth][r-(1<<lenth)+1];
}
PLL query_Min(ll l,ll r)
{
    ll lenth=lg2[r-l+1];
    if(stable_Min[lenth][l].x>stable_Min[lenth][r-(1<<lenth)+1].x)
        return stable_Min[lenth][r-(1<<lenth)+1];
    else return stable_Min[lenth][l];
}
struct Queue_Min
{
    ll l,r;
    ll s;
    bool operator < (const Queue_Min&P)const
    {
        if(s!=P.s)return s>P.s;
        return r-l+1>P.r-P.l+1;
    }
    bool operator > (const Queue_Min&P)const
    {
        if(s!=P.s)return s<P.s;
        return r-l+1<P.r-P.l+1;
    }
};
struct Queue_Max
{
    ll l,r;
    ll s;
    bool operator < (const Queue_Max&P)const
    {
        if(s!=P.s)return s>P.s;
        return r-l+1<P.r-P.l+1;
    }
    bool operator > (const Queue_Max&P)const
    {
        if(s!=P.s)return s<P.s;
        return r-l+1>P.r-P.l+1;
    }
};
priority_queue<Queue_Min,vector<Queue_Min>,greater<Queue_Min> >qmin;
priority_queue<Queue_Max,vector<Queue_Max>,greater<Queue_Max> >qmax;
ll ans_min[N],ans_max[N];
ll idx_min,idx_max;
ll tr[N];
ll lowbit(ll x)
{
    return x&(-x);
}
void modify(ll x,ll v)
{
    for(ll i=x;i<N;i+=lowbit(i))
        tr[i]+=v;
}
ll query(ll x)
{
    ll res=0;
    for(ll i=x;i;i-=lowbit(i))
        res+=tr[i];
    return res;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>T;
    init();
    while(T--)
    {
        cin>>n;
        for(ll i=1;i<=n;i++)cin>>a[i];
        for(ll i=1;i<=n;i++)sa[i]=sa[i-1]+a[i];
        build_ST();
        for(ll i=1;i<=n;i++)
        {
            PLL Qmin=mkp(0,0),Qmax=mkp(0,0);
            if(i-1>=1)
            {
                PLL Qmin_=query_Min(1,i-1);
                if(Qmin.x>Qmin_.x)Qmin=Qmin_;
                
                PLL Qmax_=query_Max(1,i-1);
                if(Qmax.x>=Qmax_.x)Qmax=Qmax_;
            }
            if(sa[i]-Qmin.x>0)
                qmin.push((Queue_Min){Qmin.y+1,i,sa[i]-Qmin.x});
            if(sa[i]-Qmax.x>0)
                qmax.push((Queue_Max){Qmax.y+1,i,sa[i]-Qmax.x});
        }
        ll res=0;
        idx_max=idx_min=0;
        while(!qmax.empty())
        {
            auto hh=qmax.top();
            qmax.pop();
            ll temp=query(hh.r)-query(hh.l-1);
            if(temp==0)
            {
                for(ll i=hh.l;i<=hh.r;i++)modify(i,1);
                res+=hh.s;
                ans_max[++idx_max]=res;
            }
            else
            {
                ll L=hh.l+1,R=hh.r;
                while(L<R)
                {
                    ll Mid=(L+R)>>1;
                    if(query(hh.r)-query(Mid-1)==0)R=Mid;
                    else L=Mid+1;
                }
                if(query(hh.r)-query(R-1)==0)
                {
                    auto tot=query_Max(R-1,hh.r-1);
                    if(sa[hh.r]-tot.x>0)
                        qmax.push(Queue_Max{tot.y,hh.r,sa[hh.r]-tot.x});
                }
            }
        }
        memset(tr,0,sizeof tr);
        res=0;
        while(!qmin.empty())
        {
            auto hh=qmin.top();
            qmin.pop();
            ll temp=query(hh.r)-query(hh.l-1);
            if(temp==0)
            {
                for(ll i=hh.l;i<=hh.r;i++)modify(i,1);
                res+=hh.s;
                ans_min[++idx_min]=res;
            }
            else
            {
                ll L=hh.l+1,R=hh.r;
                while(L<R)
                {
                    ll Mid=(L+R)>>1;
                    if(query(hh.r)-query(Mid-1)==0)R=Mid;
                    else L=Mid+1;
                }
                if(query(hh.r)-query(R-1)==0)
                {
                    auto tot=query_Min(R-1,hh.r-1);
                    if(sa[hh.r]-tot.x>0)
                        qmin.push(Queue_Min{tot.y,hh.r,sa[hh.r]-tot.x});
                }
            }
        }
        memset(tr,0,sizeof tr);
        for(ll i=1;i<=idx_max;i++)cout<<ans_max[i]<<" ";
        for(ll i=idx_max+1;i<=n;i++)cout<<ans_max[idx_max]<<" ";
        cout<<"\n";
        for(ll i=1;i<=idx_min;i++)cout<<ans_min[i]<<" ";
        for(ll i=idx_min+1;i<=n;i++)cout<<ans_min[idx_min]<<" ";
        cout<<"\n";
    }
}
```

---

## 作者：sbno333 (赞：1)

其实每次就是贪心的选择最大子段和，最大就是每次找一个短的（即没有权值一样大的区间**包含于**这个）（有效让那些数在之后发挥作用），最小就是找长的（即没有权值一样的**包含**这个）（有效的让那些数在之后失去作用，使得答案变小），但是可能最大最小决策时如果之想到这里会发现可能会影响后面的决策，导致这个贪心是假的，考虑证明没有干扰。

设 $|a|$ 为区间 $a$ 的和。

考虑最短或最长区间之间有包含，不交，和其他三种。

发现不可能为其它情况，现在有两个区间 $a+b$ 和 $b+c$。

考虑证明，发现 $|a+b|>|b|$ 当且仅当 $|a|>0$。同理，$|c|>0$，因此 $|a+b+c|>|a+b|$，显然就不对了。

此时证明段区间满足，长区间就是大于等于，同理证明。

然后每次选择区间后与之后的抉择显然就没关系了，进一步证明，发现每次同一个权值的长（短）区间互不相交，然后就只能被迫选完这些区间才能进入下一步，而且如果不是长（短），这一步毕竟坚持的时间不如之前优秀，之后的影响也是。

于是就是贪心的找长（短）区间，线段树维护即可，注意常数，实现的时候发现每次删除都是把一个区间变成负无穷，调用只有根，并且也用不到这个节点的子节点，所以不需要懒标记，可以有效节省常数。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
int a[100009];
struct st{
	int sum,ans;
	int ans1,ans2;
	int l,r;
	int l1,r1;
	int ll,rr;
}f[400009];
void pushup(int t){
	int l1,r1;
	l1=f[t].ll;
	r1=f[t].rr;
	if(l1==r1){
		f[t].sum=a[l1];
		if(a[l1]>0){//
			f[t].ans1=f[t].ans2=f[t].ans=a[l1];
			f[t].l=l1,f[t].r=r1;
			f[t].l1=l1,f[t].r1=r1;
		}else{
			f[t].ans1=f[t].ans2=f[t].ans=0;
			f[t].l=l1+1,f[t].r=r1-1;
			f[t].l1=l1+1,f[t].r1=r1-1;
		}
		return;
	}
	f[t].sum=f[2*t].sum+f[2*t+1].sum;
	if(f[2*t].ans<f[2*t+1].ans){
		f[t].ans=f[2*t+1].ans;
		f[t].l=f[2*t+1].l,f[t].r=f[2*t+1].r;
	}else{
		f[t].ans=f[2*t].ans;
		f[t].l=f[2*t].l,f[t].r=f[2*t].r;
	}
	if(f[2*t].ans1+f[2*t+1].sum>f[2*t+1].ans1){//
		f[t].l1=f[2*t].l1;
		f[t].ans1=f[2*t].ans1+f[2*t+1].sum;
	}else{
		f[t].l1=f[2*t+1].l1;
		f[t].ans1=f[2*t+1].ans1;
	}
	if(f[2*t+1].ans2+f[2*t].sum>f[2*t].ans2){//
		f[t].r1=f[2*t+1].r1;
		f[t].ans2=f[2*t+1].ans2+f[2*t].sum;
	}else{
		f[t].r1=f[2*t].r1;
		f[t].ans2=f[2*t].ans2;
	}
	if(f[2*t].ans1+f[2*t+1].ans2>f[t].ans){//
		f[t].ans=f[2*t].ans1+f[2*t+1].ans2;
		f[t].l=f[2*t].l1,f[t].r=f[2*t+1].r1;
	}
}
void pushup1(int t){
	int l1,r1;
	l1=f[t].ll;
	r1=f[t].rr;
	if(l1==r1){
		f[t].sum=a[l1];
		if(a[l1]>=0){//
			f[t].ans1=f[t].ans2=f[t].ans=a[l1];
			f[t].l=l1,f[t].r=r1;
			f[t].l1=l1,f[t].r1=r1;
		}else{
			f[t].ans1=f[t].ans2=f[t].ans=0;
			f[t].l=l1+1,f[t].r=r1-1;
			f[t].l1=l1+1,f[t].r1=r1-1;
		}
		return;
	}
	f[t].sum=f[2*t].sum+f[2*t+1].sum;
	if(f[2*t].ans<f[2*t+1].ans){
		f[t].ans=f[2*t+1].ans;
		f[t].l=f[2*t+1].l,f[t].r=f[2*t+1].r;
	}else{
		f[t].ans=f[2*t].ans;
		f[t].l=f[2*t].l,f[t].r=f[2*t].r;
	}
	if(f[2*t].ans1+f[2*t+1].sum>=f[2*t+1].ans1){//
		f[t].l1=f[2*t].l1;
		f[t].ans1=f[2*t].ans1+f[2*t+1].sum;
	}else{
		f[t].l1=f[2*t+1].l1;
		f[t].ans1=f[2*t+1].ans1;
	}
	if(f[2*t+1].ans2+f[2*t].sum>=f[2*t].ans2){//
		f[t].r1=f[2*t+1].r1;
		f[t].ans2=f[2*t+1].ans2+f[2*t].sum;
	}else{
		f[t].r1=f[2*t].r1;
		f[t].ans2=f[2*t].ans2;
	}
	if(f[2*t].ans1+f[2*t+1].ans2>=f[t].ans){//
		f[t].ans=f[2*t].ans1+f[2*t+1].ans2;
		f[t].l=f[2*t].l1,f[t].r=f[2*t+1].r1;
	}
}
void build(int l,int r,int t,bool ss){
	f[t].ll=l;
	f[t].rr=r;
	if(l<r){
		int mi;
		mi=l+r;
		mi/=2;
		build(l,mi,2*t,ss);
		build(mi+1,r,2*t+1,ss);
	}
	if(!ss)
	pushup(t);
	else
	pushup1(t);
	//cout<<t<<":"<<f[t].ll<<"~"<<f[t].rr<<"--- "<<f[t].sum<<" "<<f[t].ans<<" "<<f[t].l1<<" "<<f[t].r1<<" "<<f[t].ans1<<" "<<f[t].ans2<<" "<<f[t].l<<" "<<f[t].r<<endl; 
}
void rebd(int t,int l,int r,bool ss){
	if(f[t].ll==l&&f[t].rr==r){
		f[t].sum=(r-l+1)*-1e9,f[t].ans=0;
		f[t].ans1=0,f[t].ans2=0;
		f[t].l=f[t].rr+1,f[t].r=f[t].ll-1;
		f[t].l1=f[t].rr+1,f[t].r1=f[t].ll-1;
		return;
	}
	int mi;
	mi=f[t].ll+f[t].rr;
	mi/=2;
	if(r<=mi){
		rebd(2*t,l,r,ss);
	}else if(l>mi){
		rebd(2*t+1,l,r,ss);
	}else{
		rebd(2*t,l,mi,ss);
		rebd(2*t+1,mi+1,r,ss);
	}
	if(!ss)
	pushup(t);
	else
	pushup1(t);
}


void _main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	build(1,n,1,0);
	int ans;
	ans=0;
	for(int i=1;i<=n;i++){
		//cout<<i<<endl;
		int l,r;
		l=f[1].l,r=f[1].r;
		ans+=f[1].ans;cout<<ans<<" ";
		if(l<=r)
		rebd(1,l,r,0);
		//for(int t=1;t<=9;t++){
		//	cout<<t<<":"<<f[t].ll<<"~"<<f[t].rr<<"--- "<<f[t].sum<<" "<<f[t].ans<<" "<<f[t].l1<<" "<<f[t].r1<<" "<<f[t].ans1<<" "<<f[t].ans2<<" "<<f[t].l<<" "<<f[t].r<<endl; 
		//}
	}
	cout<<endl;
	build(1,n,1,1);
	ans=0;
	for(int i=1;i<=n;i++){
		int l,r;
		l=f[1].l,r=f[1].r;
		ans+=f[1].ans;cout<<ans<<" ";
		if(l<=r)
		rebd(1,l,r,1);
		
	}
	cout<<endl;
}
signed main() {
	int t;
	cin>>t;
	while(t--){
		_main();
	}
	return 0;
}
```

---

## 作者：gghack_Nythix (赞：0)

## 前言：

[题目传送门](https://www.luogu.com.cn/problem/P11064)

主要是为了梳理思路，有什么不对的请指出。

## 分析：

首先拿到题目，也许你会注意到一个神奇的性质：

- 如果 $\sum\limits_{i=l_1}^{r_1}a_i=\sum\limits_{i=l_2}^{r_2}a_i$ 的话，我们显然取长度更短的区间能使得贪心算法得到最大值。

- 反之，如果要让其取到最小值，则取长度最大的区间。

考虑感性证明：

如果 $[l,r]$ 是孤立的区间那显然无所谓。

然后 $[l,r]$ 显然不可能与其他的区间相交，那么假设他相交于 $[l_1,r_1]$，则区间可以被划分为 $[l,l_1]$，$(l_1,r]$，$(r,r_1]$，他们的和分别设为 $A$，$B$，$C$。如果相交则两个都取不到最大值，所以一定是包含或者不交。

那如果是包含的话，我的区间长度小一点包含的不就少了对吧。

所以说这应该是对的。

基于此即可写出[41pts暴力](https://www.luogu.com.cn/record/178238457)，卡卡常就有[54pts](https://www.luogu.com.cn/record/178245964)。

然后考虑正解。显然区间和可以被表示成前缀和的形式，那么对于第一问我们可以考虑做一个单调栈，维护前面我能到达的最近最小的 $l$ 即可，第二问同理，只需要搞成维护最远最小的 $l$ 即可。

然后由于不可能相交，所以统计区间时如果区间合法，直接跳到他的左端点就可以了，这样子就可以跳过有交集的了。

然后的话代码随便写写就可以了。

给出部分代码：


```cpp
	in >> n;
	for (int i = 1;i <= n;++i) {
        in >> a[i];
        a[i] += a[i - 1];
	}
	for (int i = 0;i <= n;++i) pre[i] = dq[i] = fail[i] = 0;
	sz = 0;
	for (int i = 1;i <= n;++i) {
		while (sz && dq[sz] < a[i]) {
			if (sz - 1 >= 0) if (a[pre[sz - 1]] >= a[pre[sz]]) pre[sz - 1] = pre[sz];//将要弹出去的栈顶比下一个栈顶更优
			sz--;
		}
		fail[i] = pre[sz]; //最近的极大区间
		++sz,dq[sz] = a[i],pre[sz] = i;
	}
	vector<int> res;
	for (int pos = n;pos >= 1;) {

		if (a[pos] - a[fail[pos]] > 0) {
			res.push_back(a[pos] - a[fail[pos]]);
			pos = fail[pos] - 1;
		}
		else --pos;
	}
	sort(res.begin(),res.end(),greater<int>()) ;
	int sum = 0;
	for (int i = 1;i <= n;++i) { 
		if(i <= res.size()) sum += res[i - 1];
		ot << sum << " ";
	}
	ot << '\n';
```

---

