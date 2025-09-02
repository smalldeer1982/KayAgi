# [ARC164E] Segment-Tree Optimization

## 题目描述

有一个长度为 $N$ 的序列，$Q$ 次询问，每一次询问会覆盖到一个区间 $[L,R]$。

你需要构造一个二叉树，满足以下条件：
- 每个节点对应一个区间 
- 根节点对应区间 $[1,N]$
- 叶子节点对应区间 $[i,i]$，同时对应区间 $[i,i]$ 的节点一定是叶子节点
- 每一个非叶子节点一定有两个子节点，如果一个非叶子节点对应 $[i,j]$，那么它的两个子节点对应区间分别为 $[i,k],[k+1,j](i \le k < j)$

对区间 $[L,R]$ 进行一次询问时，从根节点开始搜索，如果一个节点对应的区间被完全包含在 $[L,R]$ 中或该节点对应的区间与 $[L,R]$ 没有重叠，则不遍历其子节点，否则遍历其所有子节点。

记 $d$ 为遍历到的节点的最大深度，$c$ 为深度为 $d$ 的节点被遍历到的总次数，你需要在保证在 $d$ 最小的条件下 $c$ 最小，输出 $d$ 和 $c$。

translated by @[lelml](/user/372622)

## 说明/提示

$2 \le N \le 4000,1 \le Q \le 10^5,1 \le L_i \le R_i \le N(1\le i \le Q)$

## 样例 #1

### 输入

```
6 4
2 3
3 4
2 4
3 3```

### 输出

```
3 4```

## 样例 #2

### 输入

```
12 6
1 10
2 7
3 6
4 9
5 8
11 12```

### 输出

```
4 4```

# 题解

## 作者：EuphoricStar (赞：7)

妙妙题。

我们考虑如何方便地描述一棵广义线段树。不难想到使用断点描述，即对于一个结点 $[l, r]$，它的左右儿子分别是 $[l, mid], [mid + 1, r]$，其中 $mid \in [l, r - 1]$，然后把一层缩成一个 $2^{d - 1}$ 的序列，每一层都是上层对应结点的 $mid$，这样每对相邻断点组成了每个区间。

要令深度最小，我们将题中每个区间都拆成两个断点 $l_i - 1, r_i$，然后我们贪心地选择这些断点作为线段树的断点的一部分。设不同断点数量为 $k$，那么第一问的答案 $d$ 可以轻易得知，就是最小的满足 $2^d - 1 \ge k$ 的非负整数。因为第 $1 \sim d$ 层共有 $\sum\limits_{i = 1}^d 2^{i - 1} = 2^d - 1$ 个断点。

接下来我们考虑把这 $2^d - 1$ 个断点从小到大排成一个序列，易知下标为奇数的是第 $d$ 层的断点。我们现在要最小化第 $d$ 层的结点访问次数之和。

设第 $d$ 层的一个断点在 $i \in [1, q], l_i - 1, r_i$ 中出现 $t$ 次，可知这个断点对访问次数之和的贡献是 $2t$。因为这个断点两侧的区间各被访问 $t$ 次。

然后我们可以 dp 了，设 $f_{i, j}$ 为当前考虑到 $1 \sim d$ 层的所有断点中，第 $i$ 个断点，有 $j$ 个 $i \in [1, q], l_i - 1, r_i$ 中的断点被考虑，区间访问次数之和。根据上面得出的第 $d$ 层断点出现次数乘 $2$ 就是它对访问次数的贡献的结论，可以很容易地转移，考虑第 $i$ 个断点是否是 $i \in [1, q], l_i - 1, r_i$ 中地断点即可。注意若第 $i$ 个断点不是第 $d$ 层的断点，即 $i$ 为偶数，就对访问次数没有贡献。

时间复杂度 $O(q \log n + n^2)$。

[code](https://atcoder.jp/contests/arc164/submissions/43487859)

---

## 作者：Graphcity (赞：5)

首先可以发现一个性质：如果所有询问至多扫到某一层，那么这一层中的区间对于每个询问要么包含，要么相离。

所以，对于询问 $[l,r]$，这一层必然存在一个 $l-1\to l$ 的断点和一个 $r\to r+1$ 的断点。区间 $[1,n]$ 被所有断点切割后形成的区间个数就是这一层的结点个数。

既然我们知道了结点个数，由于第 $x$ 层至多有 $2^x$ 个结点，那么我们也能够知道它在哪一层。

接下来考虑最小化 $c$。对于这一层的所有区间，有两种决策：

1. 把这个区间拉到上一层，那么就不会造成贡献。
2. 把这个区间和一个相邻区间合并，然后放到上一层。

对于决策 2 的贡献，我们这样考虑：如果这两个区间是 $[l,mid)$ 和 $[mid,r]$，合并后的区间就是 $[l,r]$。根据题意，所有包含 $[l,r]$ 或者跟 $[l,r]$ 相离的区间都不会造成贡献。那么造成贡献的就是与 $[l,r]$ 相交或者被 $[l,r]$ 包含的区间，这些区间会造成 2 的贡献。

根据之前的断点可以发现一个小性质：这些造成贡献的区间要么右端点是 $mid-1$，要么左端点是 $mid$，且满足条件的区间必然会造成贡献。可以维护以某个下标为左端点或者右端点的区间个数来快速求出贡献。

唯一的限制是上一层的区间个数不能超过 $2^{d-1}$。设 $f_{i,j}$ 表示考虑到这一层从左往右第 $i$ 个区间，且上一层当前有 $j$ 个区间的贡献最小值。按照决策 DP 即可。

时间复杂度 $O(n^2+q)$。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=4e3,Maxk=2e5,inf=1e9;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,m,s,d,lim,h[Maxk+5],L[Maxk+5],R[Maxk+5];
int f[Maxn+5][Maxn+5],sl[Maxn+5],sr[Maxn+5];
inline int Find(int mid) {return 2*(sr[mid-1]+sl[mid]);}

int main()
{
    n=read(),m=read(),h[1]=1,h[2]=n+1,s=2;
    For(i,1,m)
    {
        int l=read(),r=read(); L[i]=l,R[i]=r;
        h[++s]=l,h[++s]=r+1,sl[l]++,sr[r]++;
    }
    sort(h+1,h+s+1),s=unique(h+1,h+s+1)-h-1;
    For(i,0,20) if((1<<i)>=s-1) {d=i; break;}
    if(d==0) {printf("0 %d\n",m); return 0;}
    lim=(1<<d-1);
    For(i,0,s-1) For(j,0,lim) f[i][j]=inf;
    f[0][0]=0;
    For(i,1,s-1)
    {
        For(j,1,lim) f[i][j]=f[i-1][j-1];
        if(i>1) For(j,1,lim) f[i][j]=min(f[i][j],f[i-2][j-1]+Find(h[i]));
    }
    int ans=inf; For(j,0,lim) ans=min(ans,f[s-1][j]);
    printf("%d %d\n",d,ans);
    return 0;
}
```

---

## 作者：UltiMadow (赞：5)

考场看错题了/fn/fn/fn

考虑转化一下构建线段树的过程，构造一条 $n$ 个点的链，假设当前区间为 $[l,r]$，深度为 $dep$，选取的分割点为 $mid$，则我们给 $mid\to mid+1$ 的边 $dep$ 的权值，并断开这条边。

那么区间查询 $[l,r]$ 时访问到的最深深度即为 $l-1\to l$ 的权值和 $r\to r+1$ 的权值的最大值。

先考虑第一问，对于一次区间查询 $[l,r]$ 我们给第 $l-1$ 条边和第 $r$ 条边打上标记，显然我们只需要考虑打过标记的边，记这些边数量为 $cnt$，则我们只需要考虑由这 $cnt$ 条边组成的 $cnt+1$ 个点的链。

不难发现 $d=\lfloor\log_2cnt\rfloor+1$，即对这 $cnt$ 条边建立正常的线段树（以线段中点为分割点）。

再考虑第二问，此时我们需要确定哪些边的权值是 $d$，倒着考虑构建线段树的过程，显然给一条边权值 $d$ 相当于把左右两个线段树节点合并为一个节点，那么我们需要不断合并直到剩余节点能用 $d-1$ 层线段树表示，假设我们给 $i$ 条边权值 $d$，则 $i$ 需要满足 $\lfloor\log_2(cnt-i)\rfloor+1<d$。

此外，根据构建线段树的过程，相邻两条边的权值一定不同，所以我们问题就转化为了从 $cnt$ 条边里选 $i$ 条边，其中 $\lfloor\log_2(cnt-i)\rfloor+1<d$ 且相邻两条边至多选一条，要求这 $i$ 条边的标记数量和最小。

记 $f_{i,j,0/1}$ 表示前 $i$ 条边，选了 $j$ 条，当前边选/没选的最优值，转移显然。

时间复杂度 $\mathcal O(n^2+q)$。

---

## 作者：Purslane (赞：0)

# Solution

唐龙题，没啥难度。但是有点细节。

1. 考虑 $d$ 的最小值。假设本质不同的段有 $k$ 个，那么必定有 $2^d \ge k$，因此 $d_{\min} = \lceil \log_2(k) \rceil$。这是容易构造的。
2. 考虑求 $c$ 的最小值。显然在第 $d-1$ 层以内的本质不同的线段越多越好。因此我们要在第 $d$ 层放 $2(k - 2^{d - 1})$ 条线段，他们两两相邻配对，被经过的次数是两倍他们被经过的总次数减去四倍它们被同时经过的总次数。

复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=4000+10,MAXM=2e5+10;
int n,q,dp[MAXN][MAXN],l[MAXM],r[MAXM],lsh[MAXM],tot,cnt1[MAXN],cnt2[MAXN];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>q;
	ffor(i,1,q) cin>>l[i]>>r[i],lsh[++tot]=l[i],lsh[++tot]=r[i]+1;
	lsh[++tot]=1,lsh[++tot]=n+1;
	sort(lsh+1,lsh+tot+1),tot=unique(lsh+1,lsh+tot+1)-lsh-1;
	ffor(i,1,q) l[i]=lower_bound(lsh+1,lsh+tot+1,l[i])-lsh,r[i]=lower_bound(lsh+1,lsh+tot+1,r[i]+1)-lsh-1;
	int cnt=tot-1;
	cout<<ceil(log2(cnt))<<' ';
	if(cnt==1) return cout<<q,0;
	int rst=cnt-pow(2,(int)ceil(log2(cnt))-1);
	ffor(i,1,q) {
		cnt1[l[i]]++,cnt1[r[i]+1]--;
		cnt2[l[i]]++,cnt2[r[i]]--;	
	}
	ffor(i,1,tot) cnt1[i]+=cnt1[i-1],cnt2[i]+=cnt2[i-1];
	memset(dp,0x3f,sizeof(dp));
	dp[0][rst]=0;
	ffor(i,1,tot-1) {
		ffor(j,0,rst) dp[i][j]=dp[i-1][j];
		if(i>=2) ffor(j,0,rst-1) dp[i][j]=min(dp[i][j],dp[i-2][j+1]+cnt1[i]+cnt1[i-1]-2*cnt2[i-1]);
	}
	cout<<dp[tot-1][0]*2;
	return 0;
}
```

---

