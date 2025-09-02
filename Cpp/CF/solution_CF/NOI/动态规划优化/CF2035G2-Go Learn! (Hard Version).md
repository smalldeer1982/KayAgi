# Go Learn! (Hard Version)

## 题目描述

本题的简单版与困难版的区别在于 $n$ 和 $n$ 的总和的限制。在本题中，$n \leq 3 \cdot 10^5$，且所有 $n$ 的总和不超过 $10^6$。只有在两种版本都通过后才能进行 hack。

让我们看看 Bessie 是如何管理她的财务的。她似乎陷入了困境！幸运的是，她正在申请 Moogle 的工作来解决这个问题。Moogle 的面试需要对冷门算法和复杂数据结构有深入了解，但 Bessie 从一位 LGM 那里得到了确切的学习建议。

Bessie 写了如下代码，试图在一个可能无序的数组 $[a_1, a_2, \ldots, a_n]$ 中用二分查找某个元素 $k$：

```
let l = 1
let h = n

while l < h:
  let m = floor((l + h) / 2)

  if a[m] < k:
    l = m + 1
  else:
    h = m

return l
```

Bessie 将她的代码提交给 Farmer John 的问题，并有 $m$（$1 \leq m \leq n$）组测试。第 $i$ 组测试为 $(x_i, k_i)$（$1 \leq x, k \leq n$）。保证所有 $x_i$ 互不相同，所有 $k_i$ 互不相同。

第 $i$ 组测试是正确的，当且仅当满足以下条件：

1. 数组的第 $x_i$ 个元素为 $k_i$。
2. 如果 Bessie 按上述代码对 $k_i$ 进行二分查找，返回值为 $x_i$。

可能无法让所有 $m$ 组测试在同一个数组上都正确，因此 Farmer John 会移除其中一些测试，使 Bessie 能够 AC。设 $r$ 为需要移除的最少测试数，使得存在一个数组 $[a_1, a_2, \ldots, a_n]$，$1 \leq a_i \leq n$，使得剩下的所有测试都正确。

除了求 $r$，Farmer John 还希望你统计有多少个数组 $[a_1, a_2, \ldots, a_n]$，$1 \leq a_i \leq n$，存在一种移除恰好 $r$ 个测试的方法，使得剩下的测试都正确。由于答案可能很大，请输出对 $998\,244\,353$ 取模的结果。

## 说明/提示

请参考第一个样例。

在第一个测试用例中，数组 $[1,2,2,3,4]$ 能满足所有 $m$ 个测试，因此 Bessie 需要移除的测试数最少为 $0$。注意，这也是唯一能满足所有 $m$ 个测试的数组。

在第二个测试用例中，最少需要移除 $1$ 个测试。Bessie 唯一可以移除的测试是 $(2,5)$。如果移除测试 $(2,5)$，则能满足剩下 $m-1$ 个测试的数组有 $[2,2,3,1,4]$、$[2,2,3,2,4]$、$[2,2,3,3,4]$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
5 4
1 1
2 2
4 3
5 4
5 4
5 4
2 5
1 2
3 3```

### 输出

```
0 1
1 3```

## 样例 #2

### 输入

```
3
6 6
1 3
2 5
3 1
4 2
5 4
6 6
30 8
19 22
6 12
12 1
28 27
3 4
14 25
29 14
11 15
300000 1
5 10```

### 输出

```
3 78
3 839271911
0 702730519```

# 题解

## 作者：Milmon (赞：4)

## Statement

给定 $n$，$a$ 是一个未知的长度为 $n$ 的值域为 $[1, n]$ 的整数数列。

有 $m$ 个测试点，第 $i$ 个测试点用 $x_i, k_i$ 表示。能通过某个测试点，当且仅当 $a_{x_i} = k_i$，并且在 $a$ 上二分查找 $k_i$ 得到的位置是 $x_i$。

请求出：

- 至少要删除多少个测试点才可以使得存在一个数列 $a$ 能够通过所有测试点，记为 $P$。
- 有多少个不同的数列 $a$ 满足存在一种删除 $P$ 个测试点的方案使得 $a$ 能够通过所有测试点。答案对 $998244353$ 取模。

数据范围：数据组数 $T \leq 10^4$，$1 \leq m \leq n \leq 3 \times 10^5$，$\sum n \leq 10^6$，$1 \leq x_i, k_i \leq n$ 并且所有 $k_i$ 互不相同，所有 $x_i$ 也互不相同。

## Solution

首先将所有测试点按照 $x_i$ 排序。下面给出一个结论：能通过所有测试点的必要条件是保留的测试点的 $k_i$ 递增。这是因为考虑两个测试点 $i < j$ 满足 $x_i < x_j$，由于一定存在一个 $l, r$ 得出的分界点 $m$ 满足 $l \leq x_i \leq m$ 并且 $m < x_j \leq r$，根据二分条件得出 $k_i \leq a_m < k_j$，故 $k_i < k_j$。

若对于一个数列 $a$ 存在两种删除 $P$ 个测试点的方案，那么该数列至少同时满足 $m - P + 1$ 个测试点，与 $P$ 的最优性矛盾。所以对于任意数列 $a$ 至多存在一种删除 $P$ 个测试点的方案。

考虑 dp 计算最后一个测试点为某个测试点时最多选择的测试点数量以及合法数列的方案数。

记当前测试点为 $i$，转移考虑枚举上一个测试点 $j < i$，需要满足 $k_j < k_i$，转移的系数即为 $x_j + 1$ 和 $x_i - 1$ 之间的位置上填数的方案数。设 $S_i$ 表示二分找到 $i$ 所需检验的所有位置，则 $|S_i| = \Theta(\log n)$。枚举 $S_i, S_j$ 中所有在区间内的位置计算方案数，剩下的位置可以任意填数。这样单次转移时间复杂度 $O(\log n)$。

统计答案只需要枚举最后一个选择的测试点并计算最后一段区间的填数方案数即可。需要注意的一点是，要忽略所有 $k_i = 1$ 但是 $x_i \neq 1$ 的测试点，因为当 $k = 1$ 时总是找到第一个位置。总时间复杂度 $O(m^2 \log n)$，可以通过 Easy Version。

考虑优化。注意到在 $[x_j, x_i)$ 中的并且同时在 $S_i, S_j$ 中的分界点的数量总是只有一个，这是因为第一次把这两个值区分开之后不会存在相同的分界点。设分界点为 $m$，分为两种情况讨论：

- $m = x_j$，此时只需要枚举 $S_i$ 中小于 $i$ 的所有位置统计答案即可。
- $m \neq x_j$，此时 $x_j + 1$ 和 $x_i - 1$ 之间的位置上只属于 $S_j$ 的位置均在 $m$ 左侧，只属于 $S_i$ 的位置均在 $m$ 右侧，填数方案数分别只与 $j$ 和 $i$ 有关。每个位置记录其作为分界点时左侧的贡献总和，对于 $i$ 枚举 $S_i$ 中小于 $i$ 的数作为 $m$ 统计答案，对于 $j$ 枚举 $S_j$ 中大于 $j$ 的数作为 $m$ 更新贡献总和。

需要注意的一点是，第二种情况下 $m$ 上可以填的数有 $k_i - k_j$ 个，不能方便计算。不妨把贡献拆为 $x k_i - x k_j$，分界点处记录两个值：$x$ 的总和以及 $x k_j$ 的总和，这样就可以快速计算总贡献了。

处理一个位置的时间复杂度是 $\Theta(\log n)$，总时间复杂度 $O(n \log n)$，可以接受。

## Solution (English)

First, sort all the test points according to $x_i$. The following conclusion is given: a necessary condition to pass through all test points is that the retained test points' $k_i$ are in increasing order. This is because considering two test points $i < j$ satisfying $x_i < x_j$, there must exist a boundary point $m$ derived from some $l, r$ that satisfies $l \leq x_i \leq m$ and $m < x_j \leq r$. According to the binary division condition, we conclude $k_i \leq a_m < k_j$, hence $k_i < k_j$.

If there exist two deletion schemes for $P$ test points in a sequence $a$, then the sequence must satisfy at least $m - P + 1$ test points, contradicting the optimality of $P$. Therefore, for any sequence $a$, there exists at most one scheme to delete $P$ test points.

Consider using dynamic programming to calculate the maximum number of test points that can be selected when the last test point is a certain test point, as well as the number of valid sequences.

Let the current test point be $i$. For the transition, consider enumerating the previous test point $j < i$, which needs to satisfy $k_j < k_i$. The transition coefficient is the number of ways to fill numbers between $x_j + 1$ and $x_i - 1$. Let $S_i$ represent all positions that need to be checked for finding $i$ using binary search, then $|S_i| = \Theta(\log n)$. Enumerating all positions within $S_i, S_j$ to calculate the number of ways, while the remaining positions can be filled freely. Thus, the time complexity for a single transition is $O(\log n)$.

To count the answer, we only need to enumerate the last selected test point and calculate the number of filling ways for the last segment of the interval. It is important to note that all test points with $k_i = 1$ but $x_i \neq 1$ should be ignored, as when $k = 1$, we always find the first position. The total time complexity is $O(m^2 \log n)$, which can be accepted by the Easy Version.

Consider optimization. Note that the number of boundary points that are in both $S_i$ and $S_j$ within the interval $[x_j, x_i)$ is always just one. This is because once we distinguish these two values, there will not be any identical boundary points. Let the boundary point be $m$, and discuss two cases:

- $m = x_j$: In this case, we only need to enumerate all positions in $S_i$ that are less than $i$ to count the answer.
- $m \neq x_j$: In this case, positions that only belong to $S_j$ between $x_j + 1$ and $x_i - 1$ are all to the left of $m$, while those that only belong to $S_i$ are all to the right of $m$. The filling ways depend only on $j$ and $i$. Each position records the total contribution from the left side when it serves as a boundary point. For $i$, enumerate numbers in $S_i$ that are less than $i$ as $m$ to count the answer; for $j$, enumerate numbers in $S_j$ that are greater than $j$ as $m$ to update the total contribution.

It is important to note that in the second case, the number of values that can be filled at $m$ is $k_i - k_j$, which is not easy to compute. We can break down the contribution into $x k_i - x k_j$. At the boundary point, we record two values: the total sum of $x$ and the total sum of $x k_j$; thus, we can quickly compute the total contribution.

The time complexity to handle one position is $\Theta(\log n)$, making the overall time complexity $O(n \log n)$, which is acceptable.

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
int power(int x,int y=mod-2){
    if(!y)return 1;
    int tmp=power(x,y>>1);
    tmp=1ll*tmp*tmp%mod;
    if(y&1)tmp=1ll*tmp*x%mod;
    return tmp;
}

int n,invn,m,a[300001],pos[300001],cur[300001],curmul[300001];
vector<int> l[300001],r[300001],mul[300001];

struct Node{
    int len,cnt;
    Node():len(0),cnt(0){}
    Node(int _len,int _cnt):len(_len),cnt(_cnt){}
    inline friend Node operator+(const Node x,const Node y){
        if(x.len>y.len)return x;
        if(y.len>x.len)return y;
        return Node(x.len,(x.cnt+y.cnt)%mod);
    }
    inline friend Node operator-(const Node x,const Node y){
        assert(x.len==y.len);
        return Node(x.len,(x.cnt-y.cnt+mod)%mod);
    }
    inline friend Node operator*(const Node x,const int y){
        return Node(x.len,1ll*x.cnt*y%mod);
    }
}dp[300001],answer,f[300001],g[300001];

int main(){
    int T; scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        invn=power(n);
        for(int i=1;i<=n;i++)a[i]=pos[i]=0;
        for(int i=1;i<=m;i++){
            int x,y;
            scanf("%d%d",&x,&y);
            if(y!=1||x==1)a[x]=y,pos[y]=x;
        }
        answer=Node(0,1);
        for(int i=1;i<=n;i++){
            l[i].clear(),r[i].clear(),mul[i].clear();
            dp[i]=f[i]=g[i]=Node(-1,1),cur[i]=0,curmul[i]=1;
            int L=1,R=n;
            while(L<R){
                int mid=(L+R)>>1;
                if(i<=mid)mid!=i?r[i].push_back(mid):void(),R=mid;
                else mid!=i?l[i].push_back(mid):void(),L=mid+1;
            }
            reverse(l[i].begin(),l[i].end());
            reverse(r[i].begin(),r[i].end());
        }
        for(int i=1;i<=n;i++){
            mul[i]=l[i];
            for(int &j :mul[i]){
                int base=1ll*(n-a[j]+1)*invn%mod;
                while(cur[j]<(int)r[j].size()&&r[j][cur[j]]<i)curmul[j]=1ll*curmul[j]*base%mod,cur[j]++;
                j=curmul[j];
            }
        }
        for(int i=1;i<=n;i++){
            if(!pos[i])continue;
            int x=pos[i],now=1,base=1ll*(i-1)*invn%mod;
            for(int j=0;j<(int)l[x].size();j++){
                int y=l[x][j];
                dp[x]=dp[x]+(f[y]*i-g[y])*now*invn;
                if(a[y])dp[x]=dp[x]+dp[y]*mul[x][j]*now;
                now=1ll*now*base%mod;
            }
            dp[x]=dp[x]+Node(0,now),dp[x].len++;
            now=1,base=1ll*(n-i+1)*invn%mod;
            for(int j=0;j<(int)r[x].size();j++){
                int y=r[x][j];
                f[y]=f[y]+dp[x]*now;
                g[y]=g[y]+dp[x]*now*i;
                now=1ll*now*base%mod;
            }
            answer=answer+dp[x]*now;
        }
        printf("%d %lld\n",m-answer.len,1ll*answer.cnt*power(n,n-answer.len)%mod);
    }
    return 0;
}
```

---

## 作者：bunH2O (赞：3)

对于一个点对 $(x,t)$，我们认为数组 $a$ 合法当且仅当 $\text{lower\_bound(a,\,x)\;=\;t}$。

给定大小为 $m$ 的点对集合 $S=\{(x,k)\}$，保证 $x_i$ 和 $k_i$ 分别互不相同，你需要：

1. 找到 $S'\subseteq S$，使得存在一个长度为 $n$，值域为 $[1,n]$ 的数组 $a$，其对 $S'$ 中的所有点对都合法。最大化 $|S'|$ 。
1. 设上一问答案为 $\text{Ans}$，求出长度为 $n$，值域为 $[1,n]$ 的数组 $a$ 的个数，使得存在一个大小为 $\text{Ans}$ 的集合 $S'\subseteq S$，满足 $a$ 对 $S'$ 中的所有点对都合法。对 $\text{998244353}$ 取模。

Easy Version：$1\leq m\leq n\leq 3000,\sum n\leq 10^4$。

Hard Version：$1\leq m\leq n\leq 3\times 10^5,\sum n\leq 10^6$。

5s,256MB。

---

下文中为标记方便，对于 $S/S'$ 中的数对 $(a,b)$，记 $x_b=a$。$x$ 数组在数对未涉及的地方无定义。

我们从 $\text{lower\_bound}$ 的过程入手，把二分的过程扔到线段树上去刻画：对一个值 $p$ 进行二分时，首先把他丢到根节点上，然后与 $a_{mid}$ 进行比较。假如有 $x\leq a_{mid}$，那就把他扔到左子树，否则把他扔到右子树。

我们定义集合 $S'$ 是合法的，当且仅当存在一个对 $S'$ 合法的序列 $a$。我们考虑如何判断一个集合 $S'$ 是否是合法的：

还是从二分的过程考虑。不难发现， $S'$ 中 $x_{1\sim mid}$ 必然 $\leq a_{mid}$。反之亦然。所以说 $a_{mid}$ 的取值在 $\max\limits_{i=1}^{mid}\{x_i\}$ 到 $\min\limits_{i=mid+1}^{n}\{x_i\}$ 之间。也即 $\max\limits_{i=1}^{mid}\{x_i\}<\min\limits_{i=mid+1}^{n}\{x_i\}$。

我建议你暂停想一想这意味着什么。如果你设计出了 $\Omicron(n^4)$ 的 dp，那恭喜你，不过这个不重要。

**你需要注意到的性质是：$x$ 数组单调递增。** 证明由于平凡所以省略。

因此第一问的答案就是容易求的了：不难发现就是 $S$ 去除部分非法信息后，$x$ 的最长上升子序列。

什么是不合法信息呢？不难发现只有 $x_t=1$ 且 $t$ 大于 $1$ 时信息不合法，证明同样平凡所以省略。

我们仿照求 LIS 的过程作 $dp$。记 $dp_i$ 表示线段树上区间全部在 $[1,i]$ 内的节点答案。考虑转移：

$$dp_i=\sum dp_j\times \cdots \times[\text{LIS}_i=\text{LIS}_j+1 \land x_i>x_j]$$

其中 $\cdots$ 为右端点从 $j$ 扩展到 $i$ 新扩展线段树节点的答案。对于每个被扩展的节点 $[l,r]$，其贡献为 $\min\limits_{i=mid+1}^{r}\{x_i\}-\max\limits_{i=l}^{mid}\{x_i\}$。其中若 $\min$ 无定义则为 $n+1$，$\max$ 无定义则为 $1$。

直接 $dp$ 时间复杂度为 $\Omicron(n^3)$，可用前缀和等方法优化到 $\Omicron(n^2\log n)$。可以通过 Easy Version。

当 $n\leq 3\times 10^5$ 时，$\Omicron(n^2)$ 的时间复杂度不可接受，考虑数据结构优化。

优化的方式同样仿照 LIS。我们枚举 $\text{LCA}(i,j)$，不难发现 $\text{LCA}$ 的左子树和右子树的贡献分别只与 $j,\text{LCA}$ 和 $i,\text{LCA}$ 有关。因此我们预处理出所有贡献。转移式变为如下状态：

$$dp_i=\sum dp_j\times wl_{j,\text{LCA}}\times wr_{i,\text{LCA}}\times [\text{LIS}_i=\text{LIS}_j+1 \land x_i>x_j]$$

$$dp_i=\sum\limits_{\text{LCA}}wr_{i,\text{LCA}}\times\sum\limits_{j\in lson(LCA)} (dp_j\times wl_{j,\text{LCA}})\times [\text{LIS}_i=\text{LIS}_j+1 \land x_i>x_j]$$

可以线段树+扫描线转移，时间复杂度 $\Omicron(n\log^2n)$，可以通过此题。

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/CF2035G2)

**题目大意**

> 给定 $m$ 个限制 $(x,y)$，表示在 $a$ 序列上二分第一个 $\ge y$ 的位置会得到 $x$（$a$ 序列不一定要有序）。
>
> 删除尽可能少的限制使得存在一个 $a$ 序列满足上述限制，并求这样的 $a$ 个数。
>
> 数据范围：$n,m\le 3\times 10^5$，所有 $x$ 两两不同，$y$ 两两不同。

**思路分析**

很显然建立线段树，那么每个限制对应线段树上一条到叶子的路径，对每个节点 $mid$ 的权值有限制，即大于等于左子树的最大权值，小于右子树的最小权值。

对于两个限制 $x_i<x_j$，如果 $y_i>y_j$，那么他们线段树上的 LCA 的权值无法构造。

因此保留的限制必须满足 $x_i<x_j,y_i<y_j$，很显然只要不存在 $x>1,y=1$ 的限制，就一定能构造出对应的方案。

把这些不可能满足的限制删除，第一问的答案就是 LIS。

然后考虑第二问，把所有限制按 $y_i$ 排序，逐个插入线段树，求出对应的方案数 $f_i$。

假设限制 $i$ 的前驱是限制 $j$，那么 $x_i\to x_j$ 的路径上的点的 $a_{mid}$ 的取值范围都已经确定。

注意到除了 $\mathrm{LCA}$，其他的点的取值范围只和 $y_i,y_j$ 其中一个有关系。

因此我们动态维护每个 $\mathrm{LCA}$ 子树内的可能的 $j$ 的方案数之和，以及对应 $y_j$ 之和。

注意特殊处理 $\mathrm{LCA}$ 的 $mid$ 恰好是 $j$ 的情况，此时 $a_{mid}$ 取值已经确定。

时间复杂度 $\mathcal O(n\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=3e5+5,MOD=998244353,inf=1e9;
ll ksm(ll a,ll b=MOD-2) { ll s=1; for(;b;a=a*a%MOD,b>>=1) if(b&1) s=s*a%MOD; return s; }
struct info {
	int x; ll w;
	inline friend info operator +(const info &u,const info &v) {
		return u.x^v.x?(u.x>v.x?u:v):info{u.x,(u.w+v.w)%MOD};
	}
	inline info operator -(const info &o) const { return {x,(w+MOD-o.w)%MOD}; }
	inline info operator *(const ll &o) const { return {x,w*o%MOD}; }
}	f[MAXN],s1[MAXN],s2[MAXN];
vector <int> L[MAXN],R[MAXN];
int n,m,a[MAXN],p[MAXN];
void solve() {
	scanf("%d%d",&n,&m);
	ll inv=ksm(n);
	for(int i=1,x,y;i<=m;++i) {
		scanf("%d%d",&x,&y);
		if(x==1||y>1) a[x]=y,p[y]=x;
	}
	for(int i=1;i<=n;++i) {
		f[i]=s1[i]=s2[i]={-inf,1};
		for(int l=1,r=n;l<r;) {
			int j=(l+r)>>1;
			if(i<=j) {
				r=j;
				if(i!=j) R[i].push_back(j);
			} else l=j+1,L[i].push_back(j);
		}
		reverse(L[i].begin(),L[i].end());
		reverse(R[i].begin(),R[i].end());
	}
	info ans={0,1};
	for(int i=1;i<=n;++i) if(p[i]) {
		int x=p[i]; ll vl=1,wys=(i-1)*inv%MOD;
		for(int j:L[x]) {
			f[x]=f[x]+(s1[j]*i-s2[j])*vl*inv;
			if(a[j]) f[x]=f[x]+f[j]*vl;
			vl=vl*wys%MOD;
		}
		f[x]=f[x]+info{0,vl},++f[x].x;
		vl=1,wys=(n-i+1)*inv%MOD;
		for(int j:R[x]) {
			s1[j]=s1[j]+f[x]*vl;
			s2[j]=s2[j]+f[x]*vl*i;
			vl=vl*wys%MOD;
		}
		ans=ans+f[x]*vl;
	}
	printf("%d %lld\n",m-ans.x,ans.w*ksm(n,n-ans.x)%MOD);
	for(int i=1;i<=n;++i) L[i].clear(),R[i].clear(),a[i]=p[i]=0;
}
signed main() {
	int _; scanf("%d",&_);
	while(_--) solve();
	return 0;
}
```

---

