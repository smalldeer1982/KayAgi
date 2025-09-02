# Yet Another Segments Subset

## 题目描述

给你 $n$ 个线段，每个线段用左右端点 $l_i, r_i$ 表示。  
现在要你从中选出尽量多的线段，使得他们两两之间要么完全不相交，要么其中一个完全包含另一个。

你需要回答 $t$ 次询问。

## 样例 #1

### 输入

```
4
4
1 5
2 4
2 3
3 4
5
1 5
2 3
2 5
3 5
2 2
3
1 3
2 4
2 3
7
1 10
2 8
2 5
3 4
4 4
6 8
7 7```

### 输出

```
3
4
2
7```

# 题解

## 作者：灵茶山艾府 (赞：11)

我们可以先求出每条线段至多可以包含的线段数 $c_i$，然后定义 $dp_i$ 为在 $[1,i]$ 这个范围上我们至多能选出多少条满足题意的线段数，我们枚举不被包含的线段，由于不能与其他线段相交，故状态转移为

$$dp_{r_i} = \max\{dp_{r_i-1},dp_{l_i-1}+c_i\}$$

$c_i$ 的求法类似，为保证状态转移的正确性，我们需要从将所有线段按照其长度排序，这样可以从短线段转移到长线段。排序后，对每条线段，在其对应的范围上跑一遍上述转移。

注意到 $l_i$ 和 $r_i$ 范围比较大，需要先离散化之后再计算。这样复杂度是 $O(n^2)$ 的。

AC 代码 (Golang)

```go
package main

import (
	"bufio"
	. "fmt"
	"os"
	"sort"
)

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()
	type segment struct{ l, r, contains int }

	var T, n int
	for Fscan(in, &T); T > 0; T-- {
		Fscan(in, &n)
		seg := make([]segment, n)
		a := []int{}
		for i := range seg {
			Fscan(in, &seg[i].l, &seg[i].r)
			a = append(a, seg[i].l, seg[i].r)
		}
		sort.Ints(a)
		k := 1
		kth := map[int]int{a[0]: k}
		for i := 1; i < len(a); i++ {
			if a[i] != a[i-1] {
				k++
				kth[a[i]] = k
			}
		}
		for i, s := range seg {
			seg[i].l = kth[s.l]
			seg[i].r = kth[s.r]
		}
		sort.Slice(seg, func(i, j int) bool { a, b := seg[i], seg[j]; return a.r-a.l < b.r-b.l })

		k++
		ids := make([][]int, k)
		for i, s := range seg {
			ids[s.r] = append(ids[s.r], i)
		}
		for i, s := range seg {
			dp := make([]int, k)
			for j := s.l; j <= s.r; j++ {
				dp[j] = dp[j-1]
				for _, id := range ids[j] {
					if t := seg[id]; t.l >= s.l {
						dp[j] = max(dp[j], dp[t.l-1]+t.contains)
					}
				}
			}
			seg[i].contains = dp[s.r] + 1
		}

		rseg := make([][]segment, k)
		for _, s := range seg {
			rseg[s.r] = append(rseg[s.r], s)
		}
		dp := make([]int, k)
		for i := 1; i < k; i++ {
			dp[i] = dp[i-1]
			for _, s := range rseg[i] {
				dp[i] = max(dp[i], dp[s.l-1]+s.contains)
			}
		}
		Fprintln(out, dp[k-1])
	}
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
```


---

## 作者：滑大稽 (赞：8)

这题就没人暴力记忆化搜索吗...

首先对线段的端点进行离散化。然后，我们设 $f(l,r)$ 为该段区间的答案。

但是该怎么转移？考虑枚举子段来更新，同时若有线段正好覆盖了这个区间，答案再加一。

但是暴力枚举子段是 $O(n^3)$ 的。我们可以考虑如下转移：

首先可以单独放缩 $l$ 或 $r$ 端点，即用 $f(l+1,r)$ 和 $f(l,r-1)$ 来更新 $f(l,r)$。

然后对于切割区间，假如有若干条线段的左端点在 $l$ 这个位置，设其中一个的右端点为 $r'$，我们发现只有我们把区间切割为 $[l,r']$ 和 $[r'+1,r]$ 时才有意义。对于线段右端点在 $r$ 同理。

所以我们可以对于每个端点，存下有哪些线段以他为左端点。转移枚举即可。每个线段最多影响 $O(n)$ 个转移区间，使他们枚举复杂度加一（左端点为 $l$ 或右端点为 $r$ 的区间），所以枚举的复杂度为 $O(n^2)$。同时状态数也为 $O(n^2)$，所以整体复杂度 $O(n^2)$。

~~还有一个偷懒的做法~~：我们发现我们只用考虑左端点在 $l$ 的线段，至于右端点在 $r$ 的线段，我们发现放缩和用左端点在 $l$ 的线段来切割区间可以完全替代用右端点在 $r$ 的线段来切割区间。所以只用维护一个方向即可。

```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<vector>
const int N=6005;
using namespace std;
char te1;
int a[N],b[N],l[N];
unsigned short int f[N][N];
vector<int>rx[N];
bool v[N][N];
char te2;
inline int read()
{
	char h=getchar();
	int y=0;
	while(h<'0'||h>'9')h=getchar();
	while(h>='0'&&h<='9')y=y*10+h-'0',h=getchar();
	return y;
}
unsigned short int dfs(int l,int r)
{
	if(l>r)return 0; 
	if(f[l][r]!=65535)return f[l][r];
	f[l][r]=0;
	f[l][r]=dfs(l+1,r);
	f[l][r]=max(f[l][r],dfs(l,r-1));
	for(int i=0;i<rx[l].size()&&rx[l][i]<r;i++)f[l][r]=max(f[l][r],(unsigned short int)(dfs(l,rx[l][i])+dfs(rx[l][i]+1,r)));
	f[l][r]+=v[l][r];
	return f[l][r];
}
signed main()
{
	int t=read();
	while(t--)
	{
		int n=read();
		for(int i=1;i<=n;i++)a[i]=read(),b[i]=read(),l[i]=a[i],l[i+n]=b[i];
		sort(l+1,l+1+n+n);
		int m=unique(l+1,l+1+n+n)-l-1;
		for(int i=1;i<=n;i++)a[i]=lower_bound(l+1,l+1+m,a[i])-l,b[i]=lower_bound(l+1,l+1+m,b[i])-l;
		for(int i=1;i<=m;rx[i].clear(),i++)
		for(int j=1;j<=m;j++)f[i][j]=-1,v[i][j]=0;
		for(int i=1;i<=n;i++)v[a[i]][b[i]]++,rx[a[i]].push_back(b[i]);
		for(int i=1;i<=m;i++)sort(rx[i].begin(),rx[i].end());
		cout<<dfs(1,m)<<"\n";
	}
}
```

---

## 作者：Mr_Skirt (赞：2)

提供一个非官方的思路。首先，假设有线段$A$，$B$，且$A$完全被$B$包含，那么我们就可以把$B$看做一个权值为$2$的线段。此时我们就可以把这道题转化为如何选不相交区间使得权值最大化。

那么我们就可以设$f(i)$为最后一个选中区间是第$i$个区间的情况下，最大的权值，于是有
$$
f(i) = \max (f[j])+w_i\ (r_j<l_i)
$$
其中$w_i$代表的是，能完全被这个区间包含的最大不相交区间个数。那么现在问题就变成：对于所有区间如何求出$w_i$。

其实我们可以利用图论的思想，所有区间和它包含的区间之间的关系构成了一棵树。$A$完全被$B$包含那么$A$就是$B$的子节点，以此类推，如果我们求出子节点的$w_i$，我们就可以进行一次dp求出当前节点的$w_i$了。

所以我们只需要进行一个树上 dp 套线性 dp 就好了。但是这就意味着，每个节点我们都需要对它的子节点进行一次 dp，但是这样很有可能会超时。

于是我就想了一个用树状数组优化 dp 转移的方法。首先根据贪心思想，我们可以把子节点所代表的区间按照右端点升序排序，那么对于每个$f(i)$，我们就只需要知道满足 $r_j<l_i$ 的最大值是什么就好了。

利用树状数组动态插入值，我们就可以在$O(nlogn)$时间内求出满足条件的最大区间数量$w_i$了。

最后求出所有$w_i$的值以后再对所有区间来一次大 dp，这次的 dp 就可以用$O(n^2)$的暴力转移了，不会影响复杂度。

因为这道题$f(i)$的 dp 是从前往后的，所以树状数组是可以求出最大值的，因为值域比较大，所以还是得离散化一下，具体见代码。

总体复杂度：$O(n^2\log{n})$
但是不知道为啥跑的还挺快。

```cpp
struct Inv {
    int l, r, id;
    bool operator<(const Inv& a) const { return r < a.r; }
};
Inv invs[MAXN];
// cnt代表的就是题解里的w_i，
// 也就是每个区间包含的区间里最多可以选多少个符合题意的区间（包括自己
// f[i]是用于dp的临时数组
int cnt[MAXN], f[MAXN];

vector<int> G[MAXN];
bool vis[MAXN];
int N;

// 求最大值用的树状数组
struct FenwickTree {
    FenwickTree() {}
    inline void increase(int t, int x) {
        for (int i = t; i <= N; i += lowbit(i)) _arr[i] = max(_arr[i], x);
    }
    inline int getSum(int t) {
        int s = 0;
        for (int i = t; i; i -= lowbit(i)) s = max(s, _arr[i]);
        return s;
    }
    void clear() {
        for (int i = 1; i <= N; i++) _arr[i] = 0;
    }
    int _arr[MAXN * 3];
    inline int lowbit(int x) { return x & (-x); }
};
template <typename T>
struct Discretization {
    vector<T> xp;
    int size() const { return xp.size(); }
    void add(T val) { xp.push_back(val); }
    void discretize() {
        sort(xp.begin(), xp.end());
        xp.resize(unique(xp.begin(), xp.end()) - xp.begin());
    }
    int get(T val) {
        return lower_bound(xp.begin(), xp.end(), val) - xp.begin() + 1;
    }
    void clear() { xp.clear(); }
    T get2(int num) { return xp[num - 1]; }
};
FenwickTree tree;
Discretization<int> discrete;

void dfs(int x) {
    if (vis[x]) return;
    vis[x] = true;
    if (G[x].empty()) return;
    for (auto v : G[x]) dfs(v);
    sort(G[x].begin(), G[x].end(),
         [](int a, int b) { return invs[a].r < invs[b].r; });

    // 利用树状数组优化线性dp
    int sz = G[x].size(), num = 0;
    for (int i = 0; i < sz; i++) {
        f[i] = cnt[G[x][i]] + tree.getSum(invs[G[x][i]].l - 1);
        tree.increase(invs[G[x][i]].r, f[i]);
        num = max(num, f[i]);
    }
    tree.clear();
    cnt[x] = num + 1;
}

void solve() {
    scanf("%d", &n);
    discrete.clear();
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &invs[i].l, &invs[i].r);
        invs[i].id = i;
        cnt[i] = 1;
        vis[i] = false;
        G[i].clear();
        discrete.add(invs[i].l);
        discrete.add(invs[i].r);
    }

    // 对区间左右端点离散化
    discrete.discretize();
    N = discrete.size();
    for (int i = 1; i <= n; i++) {
        invs[i].l = discrete.get(invs[i].l);
        invs[i].r = discrete.get(invs[i].r);
    }

    // 给区间们连边
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != j && invs[i].l >= invs[j].l && invs[i].r <= invs[j].r) {
                G[j].push_back(i);
            }
        }
    }

    // 树上dp
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) dfs(i);
    }

    // 最后来一个大dp，这里也可以优化成 O(nlogn)
    int ans = 0;
    // 注意排序以后区间会乱序
    sort(invs + 1, invs + n + 1);
    f[0] = 0;
    for (int i = 1; i <= n; i++) {
        f[i] = 0;
        for (int j = i - 1; j >= 0; j--) {
            if (invs[j].r < invs[i].l) {
                f[i] = max(f[i], cnt[invs[i].id] + f[j]);
            }
        }
        ans = max(ans, f[i]);
    }
    printf("%d\n", ans);
}
```

---

## 作者：shao0320 (赞：1)

# CF1399F Yet Another Segments Subset

为了给机房学弟做表率于是写个题解

首先可以发现是个 dp ，设 $f(i)$ 表示 $i$ 这个前缀的最多线段数量。

设 $i$ 线段最多能**同时包含** $g(i)$ 个线段，那么暴力转移就是枚举右端点和右端点所在线段。

那么注意到这个线段的包含关系是个树形结构，考虑树上 $dp$ 。

直接树上 $dp$ 是 $O(N^3)$ ，考虑树状数组优化一下每层的 $dp$

时间复杂度 $O(N^2\log N)$。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define pb push_back
#define N 6005
#define MAXN 6000
#define lowbit(x) x&-x
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int T,n,L[N],R[N],p[N],de[N],f[N],g[N],h[N],cnt;
struct BIT
{
	int c[N];
	void clear(){memset(c,0,sizeof(c));}
	void modify(int x,int k){for(;x<=cnt;x+=lowbit(x))c[x]=max(c[x],k);}
	int query(int x){int res=0;for(;x;x-=lowbit(x))res=max(res,c[x]);return res;}
}t;
vector<int>G[N];
vector<int>F[N]; 
int belong(int i,int j){return (L[i]>=L[j]&&R[i]<=R[j]);}
int cmp(int x,int y){return R[x]<R[y];}
//is i belong to j? 
void dfs(int x)
{
	if(g[x])return;
	int siz=F[x].size();
	for(int i=0;i<siz;i++)dfs(F[x][i]);
	t.clear();
	sort(F[x].begin(),F[x].end(),cmp);
	int now=0;
	for(int i=0;i<siz;i++)
	{
		now=max(now,t.query(L[F[x][i]]-1)+g[F[x][i]]);
		t.modify(R[F[x][i]],t.query(L[F[x][i]]-1)+g[F[x][i]]);
	}
	g[x]=now+1;
}
int main()
{
	T=read();
	while(T--)
	{
		n=read();cnt=0;memset(de,0,sizeof(de));memset(g,0,sizeof(g));memset(f,0,sizeof(f));
		for(int i=1;i<=n;i++)L[i]=read(),R[i]=read(),p[++cnt]=L[i],p[++cnt]=R[i],F[i].clear();
		sort(p+1,p+1+cnt);int tot=unique(p+1,p+1+cnt)-p-1;
		for(int i=1;i<=n;i++)L[i]=lower_bound(p+1,p+1+tot,L[i])-p,R[i]=lower_bound(p+1,p+1+tot,R[i])-p;
		for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(i!=j&&belong(i,j))F[j].pb(i);
		for(int i=1;i<=n;i++)if(!g[i])dfs(i);
		f[0]=0;h[0]=0;
		for(int i=1;i<=MAXN;i++)G[i].clear();
		for(int i=1;i<=n;i++)G[R[i]].pb(i);
		for(int i=1;i<=MAXN;i++)
		{
			int siz=G[i].size();
			for(int j=0;j<siz;j++)
			{
				int ID=G[i][j];
				f[i]=max(f[i],h[L[ID]-1]+g[ID]);
			}
			h[i]=max(h[i-1],f[i]);
		}
		printf("%d\n",h[MAXN]);
	}
}

```

---

## 作者：jasonliujiahua (赞：0)

# CF1399F

## Solution

非常好的区间 dp 题。dp 状态其实很好想，$dp_{l,r}$ 表示离散化后区间 $[l,r]$ 中最多能有多少个区间。问题的核心是转移：我们只需考虑固定一个端点的区间！这里考虑右端点。分下面两种情况讨论：
   - 没有右端点为 $R$ 的区间：$dp_{L,R-1}$
   - 有右端点为 $R$ 的区间：枚举该区间 $i$，贡献为 $dp_{L,l_i-1}+dp_{l_i,R}$
   
   取最大值即可。还应注意的是如果有区间等于 $[L,R]$，则不应在上面第二种情况里讨论它，而是最后直接把答案加 $1$。均摊后时间复杂度 $O(n^2)$。
   
## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=6e3+10;
int t,n,L[maxn],R[maxn],b[maxn<<1],lb,dp[maxn][maxn];
vector<int> v[maxn];
void init()
{
	for(int i=1;i<=lb;i++) v[i].clear();
	lb=0;
	cin>>n;
	for(int i=1;i<=n;i++) 
	{
		cin>>L[i]>>R[i];
		b[++lb]=L[i];
		b[++lb]=R[i]; 
	}
	sort(b+1,b+lb+1);
	lb=unique(b+1,b+lb+1)-b-1;
	for(int i=1;i<=n;i++)
	{
		L[i]=lower_bound(b+1,b+lb+1,L[i])-b;
		R[i]=lower_bound(b+1,b+lb+1,R[i])-b;
		v[R[i]].push_back(i);
	}
	for(int i=1;i<=lb;i++) 
		for(int j=1;j<=lb;j++) dp[i][j]=-1;
}
int DP(int l,int r)
{
	if(l>r) return dp[l][r]=0;
	if(dp[l][r]!=-1) return dp[l][r];
	bool ok=0;
	dp[l][r]=DP(l,r-1);
	for(int i=0;i<v[r].size();i++)
	{
		int x=v[r][i];
		if(L[x]==l) ok=1;
		else if(L[x]>l) dp[l][r]=max(dp[l][r],DP(l,L[x]-1)+DP(L[x],r));
	}
	dp[l][r]+=ok;
	return dp[l][r];
}
int main()
{
	cin>>t;
	while(t--)
	{
		init();
		printf("%d\n",DP(1,lb));
	}
	return 0;
} 
```

---

