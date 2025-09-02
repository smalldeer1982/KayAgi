# Mycraft Sand Sort

## 题目描述

Steve has a permutation $ ^{\text{∗}} $ $ p $ and an array $ c $ , both of length $ n $ . Steve wishes to sort the permutation $ p $ .

Steve has an infinite supply of coloured sand blocks, and using them he discovered a physics-based way to sort an array of numbers called gravity sort. Namely, to perform gravity sort on $ p $ , Steve will do the following:

- For all $ i $ such that $ 1 \le i \le n $ , place a sand block of color $ c_i $ in position $ (i, j) $ for all $ j $ where $ 1 \le j \le p_i $ . Here, position $ (x, y) $ denotes a cell in the $ x $ -th row from the top and $ y $ -th column from the left.
- Apply downwards gravity to the array, so that all sand blocks fall as long as they can fall.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2064E/bacbf9735e7645cca9c686c572d9f449ff8d01a4.png) An example of gravity sort for the third testcase. $ p = [4, 2, 3, 1, 5] $ , $ c = [2, 1, 4, 1, 5] $ Alex looks at Steve's sand blocks after performing gravity sort and wonders how many pairs of arrays $ (p',c') $ where $ p' $ is a permutation would have resulted in the same layout of sand. Note that the original pair of arrays $ (p, c) $ will always be counted.

Please calculate this for Alex. As this number could be large, output it modulo $ 998\,244\,353 $ .

 $ ^{\text{∗}} $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is a $ 4 $ in the array).

## 说明/提示

The second test case is shown below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2064E/b18fd20848076bc3f7761173879dc3bf19a532a5.png) Gravity sort of the second testcase.It can be shown that permutations of $ p $ will yield the same result, and that $ c $ must equal $ [1,1,1,1,1] $ (since all sand must be the same color), so the answer is $ 5! = 120 $ .

The third test case is shown in the statement above. It can be proven that no other arrays $ p $ and $ c $ will produce the same final result, so the answer is $ 1 $ .

## 样例 #1

### 输入

```
4
1
1
1
5
5 3 4 1 2
1 1 1 1 1
5
4 2 3 1 5
2 1 4 1 5
40
29 15 20 35 37 31 27 1 32 36 38 25 22 8 16 7 3 28 11 12 23 4 14 9 39 13 10 30 6 2 24 17 19 5 34 18 33 26 40 21
3 1 2 2 1 2 3 1 1 1 1 2 1 3 1 1 3 1 1 1 2 2 1 3 3 3 2 3 2 2 2 2 1 3 2 1 1 2 2 2```

### 输出

```
1
120
1
143654893```

# 题解

## 作者：Mr_Az (赞：8)

# [CF2064E Mycraft Sand Sort](https://codeforces.com/problemset/problem/2064/E)

### Algorithm:

并查集合并信息。

### Solution:

首先观察到颜色集合 $c$ 不会发生变化，因为如果改变颜色则第一列就已经不一样了，所以变化的只有长度排列 $p$。

考虑什么时候交换两行的长度不会对最终的结果。对于两行颜色一样的行 $l,r(l<r)$，他们能交换当且仅当：

1. $\max_{i=l+1}^{r-1} p_i<\min(p_l,p_r)$
2. $r=l+1$，即这两行相邻。

需要满足 $1$ 条件的原因是：中间行的长度小于 $p_l$ 是为了不让中间的颜色掉下来，小于 $p_r$ 是为了让第 $r$ 行掉下来。如果这两行相邻则显然可以交换。

我们考虑按照 $p_i$ 从小到大删除每一行，每次删除的时候检查上下两行的颜色是否一致。因为我们规定了从小到大的删除顺序，使得剩下的行都比当前要删除的行要长。

实现的时候用模拟链表维护删除行，并查集维护合并行，计算贡献的时候只需要查询当前 $i$ 行所在的块的大小，第 $i$ 行可以跟里面任意一行交换，所以 $ans$ 直接乘上大小即可。乘完之后大小要减一，因为当前行的贡献已经计算完了。

### Code:

```cpp
const int N=2e5+8,mod=998244353;
int T=0;
int n,ans;
int p[N],id[N],c[N],fa[N],siz[N],nxt[N],pre[N];
int getfa(int p){return p==fa[p]?p:fa[p]=getfa(fa[p]);}
inline void merge(int u,int v){
    u=getfa(u);v=getfa(v);
    if(siz[u]<siz[v]) swap(u,v);
    if(u==v) return ;
    siz[u]+=siz[v];
    fa[v]=u;
}
inline void solve(){
    read(n);ans=1;
    for(rint i=1;i<=n;i++) siz[i]=1,nxt[i]=i+1,pre[i]=i-1;
    for(rint i=1;i<=n;i++) read(p[i]),id[p[i]]=i;
    for(rint i=1;i<=n;i++) read(c[i]),fa[i]=i;
    for(rint i=1;i<n;i++) if(c[i]==c[i+1]) merge(i,i+1);
    for(rint i=1;i<=n;i++){
        ans=ans*siz[getfa(id[i])]%mod;
        siz[getfa(id[i])]--;
        int pr=pre[id[i]],nx=nxt[id[i]];
        nxt[pr]=nx;pre[nx]=pr;
        if(pr==0||nx==n+1||c[pr]!=c[nx]) continue;
        merge(nx,pr);
    }
    printf("%lld\n",ans);
}
```

---

## 作者：冷却心 (赞：8)

这说明你的实力不足以上 Master。

唐题，但是我没有场切。

我们有以下的观察：

- 首先只能移动数的位置，数的颜色不能改变，因为如果改变了那么这种颜色对应的个数就变少了显然不同。
- 只有同色的数之间才**可能**可以互换位置，因为如果把两种不同颜色的数位置互换，那么最终他们落下之后上下的相对位置改变了，导致结果不同，非法。为什么是**可能**，因为比如对于 $p=\{1,3,2,4\}$，$c=\{1,1,2,1\}$，这种情况，你会发现他和 $p=\{4,3,2,1\}$，$c=\{1,1,2,1\}$ 是不同的，你会感觉一个数不能交换到比它更大并且不同色的位置（当然这并不充分），因此有了下面的讨论。
- 最小的数不影响其他数的相同颜色位置的互换。这个有点难以说明，考虑一个例子：$p=\{3,1,4,2\}$，$c=\{1,2,1,1\}$，你会发现除了 $1$，其他数怎么交换都是合法的，因为其他数都大于 $1$，不管怎么换都不会 $1$ 这一纵列上的相对颜色位置及个数。

然后其实就做完了。我们考虑维护相邻的极大同色块，这个可以并查集，从小到大枚举数，我们发现当前的数能换到的位置就是这个块的大小，所以答案累乘，然后因为这个数并不影响之后的数的放置，所以把这个数删去，如果这个数上下的数同色，那么合并，这个可以用链表维护，然后最后输出答案即可。

代码很好写。不知道为什么官解用了线段树，比较抽象。


```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 2e5 + 10;
const LL MOD = 998244353;
int n, A[N], C[N], nxt[N], pre[N]; pair<int, int> p[N];
int fa[N], sz[N]; 
int Find(int x) { return (fa[x] == x ? x : fa[x] = Find(fa[x])); };
void merge(int a, int b) {
	int x = Find(a), y = Find(b);
	if (x == y) return ;
	fa[x] = y; sz[y] += sz[x]; sz[x] = 0;
}
int main() {
	freopen(".in", "r", stdin); freopen(".out", "w", stdout);
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int _; cin >> _;
	while (_ --) {
		cin >> n;
		for (int i = 1; i <= n; i ++) { cin >> A[i]; p[i] = {A[i], i}; }
		for (int i = 1; i <= n; i ++) cin >> C[i];
		for (int i = 1; i <= n; i ++) fa[i] = i, sz[i] = 1;
		sort(p + 1, p + 1 + n); LL Ans = 1; C[n + 1] = 114514191; nxt[0] = 1, pre[n + 1] = n;
		for (int i = 1; i <= n; i ++) nxt[i] = i + 1, pre[i] = i - 1;
		for (int i = 2; i <= n; i ++) if (C[i] == C[i - 1]) merge(i, i - 1);
		for (int i = 1; i <= n; i ++) {
			int u = p[i].second;
			Ans = Ans * sz[Find(u)] % MOD; sz[Find(u)] --;
			if (C[nxt[u]] == C[pre[u]]) merge(nxt[u], pre[u]);
			nxt[pre[u]] = nxt[u]; pre[nxt[u]] = pre[u];
		} cout << Ans << "\n";
	}
	return 0;
}
```

---

## 作者：chenwenmo (赞：3)

[CF2064E Mycraft Sand Sort](https://codeforces.com/contest/2064/problem/E)

### Description

给定一个排列 $p$ 和序列 $c$，长度都为 $n(\le 2\times 10^5)$，表示在一个二维的有重力的环境中，从上往下第 $i$ 行，从左往右排列着 $p_i$ 个颜色为 $c_i$ 的受重力的大小相等的方块。

这些方块受到重力影响，会往下掉落，直到下面有支撑，第 $n$ 行的下面是地面。

![示例图片](https://espresso.codeforces.com/95f43ad9415a1959b30fc38adbe82a42bc680e67.png)

请求出有多少对不同的 $(p', c')$，使得掉落后的结果与给定的 $(p, c)$ 相同。对 $998244353$ 取模。 

### Solution

发现第一列的颜色不会改变，所以 $c' = c$，我们只需考虑有多少不同的 $p'$。

若要产生不同的 $p'$，相当于对 $p$ 做若干次交换的操作。

假设交换 $p_i$ 和 $p_j$，$(i<j)$，那么必须满足 $c_i = c_j$，并且 $[i,j]$ 中不存在 $p_k > \min(p_i,p_j)$。

那怎么统计答案呢？

设 $p$ 排序后为 $a$，显然 $a_1$ 只能和它 **在 $p$ 中** 左右相邻且颜色相同的交换，交换的方案数就是这个相同相邻颜色段的大小。那如果我们把 $a_1$ 从 $p$ 中删去，并把 $p$ 的左右两块合并，发现对于 $a_2$ 来说也是这么个情况。依此类推。

那么我们只需要维护连续相同颜色段，并支持删除，合并。DSU + 链表 容易做到这一点。

利用乘法原理，把每次交换的方案数相乘即可。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using ULL = unsigned long long;
using PII = pair<int, int>;

const int N = 2e5 + 5, INF = 1e9, MOD = 998244353;

int n, p[N], c[N], pos[N];
int l[N], r[N];

struct DSU {
    int n, fa[N], siz[N];

    void init(int _n) {
        n = _n;
        for (int i = 1; i <= n; i++) {
            fa[i] = i;
            siz[i] = 1;
        }
    }

    int find(int x) { return (fa[x] == x ? x : fa[x] = find(fa[x])); }

    void merge(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx == fy) return;
        if (siz[fx] > siz[fy]) swap(fx, fy);
        fa[fx] = fy;
        siz[fy] += siz[fx];
    }

    bool is_merge(int x, int y) { return find(x) == find(y); }
} dsu;

void erase(int x) {
    l[r[x]] = l[x];
    r[l[x]] = r[x];
}

void Solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        pos[p[i]] = i;
    }
    dsu.init(n);
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        if (c[i] == c[i - 1]) dsu.merge(i, i - 1);
        l[i] = i - 1;
        r[i] = i + 1;
    }
    int ans = 1;
    for (int i = 1; i <= n; i++) {
        int cur = pos[i];
        int f = dsu.find(cur);
        ans = (LL)ans * dsu.siz[f] % MOD;
        erase(cur);
        if (!(--dsu.siz[f])) {
            if (l[cur] && r[cur] <= n && c[l[cur]] == c[r[cur]]) dsu.merge(l[cur], r[cur]);
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    while (T--) Solve();
    return 0;
}
```

---

## 作者：xyvsvg (赞：2)

考虑每一列消失的那一行。

显然当前位造成的贡献为当前列与下一列匹配的方案，而这个方案数就等于当前点的上下的极长同色连续段（每一行都可以消失）。

直接用 ```map``` 维护即可，代码很短：


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
void solve()
{
    int n;
    cin>>n;
    vector<int>a(n+10),b(n+10),mapp(n+10);
    map<int,P>odt;
    for(int i=1;i<=n;++i)
        cin>>a[i],mapp[a[i]]=i;
    for(int i=1;i<=n;++i)
        cin>>b[i];
    for(int cnt=0,i=1;i<=n;++i)
    {
        ++cnt;
        if(b[i]!=b[i+1])
        {
            odt[i-cnt+1]={b[i],cnt};
            cnt=0;
        }
    }
    odt[0]={-1,-1};
    odt[n+1]={-1,-1};
    int ans=1;
    const int mod=998244353;
    for(int j=1;j<=n;++j)
    {
        int i=mapp[j];
        auto it=prev(odt.upper_bound(i));
        ans=1LL*ans*it->second.second%mod;
        if(!--it->second.second)
        {
            auto pre=prev(it);
            for(it=odt.erase(it);it->second.first==pre->second.first;it=odt.erase(it))
                pre->second.second+=it->second.second;
        }

    }
    cout<<ans<<endl;
}
int main()
{
    int t;
    cin>>t;
    while(t--)
        solve();
    return 0;
}

```

---

## 作者：w9095 (赞：2)

[CF2064E Mycraft Sand Sort](https://www.luogu.com.cn/problem/CF2064E)

第一次一眼秒了一道 E，但是被人均六分钟 C 题硬控一小时，未能写完，遗憾离场，特此纪念。

考虑第一列，无论排列 $p'$ 是什么样子，第一列一定是 $c'$。因此，$c'$ 数组一定等于 $c$ 数组。

这个结论还引出一个推论，$p'$ 一定由 $p$ 中颜色相同的位置交换得到。如果异色交换，一定会有一种颜色的方块总数变化，此时一定不与初始状态相同。

那我们先考虑一种颜色。一种颜色某个元素可以邻项交换的条件是这两个元素之间的位置大小必须都小于这个位置的大小。手玩一下充分性是显然的，考虑之间的位置大小大于的情况一定会导致某两个方块颜色改变，所以也是必要的。

那么，一个元素可以交换的位置是一段连续的区间，即左右都到第一个大于这个元素的异色位置。这种计数问题的经典做法是先考虑最紧的限制。我们先考虑最小的元素，从小到大依次安排位置。当我们安排一个更大的元素时，这个元素的区间要么和之前的区间无交，要么完全包含。我们把占位置的贡献挂到每段可行区间的左端点，统计有多少个位置已经被占只需要查询可行区间的区间和即可。

然后我们发现每种颜色是独立的，我们先交换小的元素，这样就不会被后来交换的元素影响，一定存在方案。直接乘起来就行了。

上面提到的东西都可以使用线段树维护，使用普通二分时间复杂度 $O(n\log^2 n)$，使用线段树二分时间复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define lc(x) ((x)<<1)
#define rc(x) ((x)<<1)|1
using namespace std;
struct node
{
	long long mx,sum;
}tr1[1200000],tr2[1200000];
long long t,n,p[300000],c[300000],rt=1;
vector<long long>a[300000];
pair<long long,long long>b[300000];
const long long mod=998244353;
void pushup(struct node tr[],long long x)
{
	tr[x].mx=max(tr[lc(x)].mx,tr[rc(x)].mx);
	tr[x].sum=tr[lc(x)].sum+tr[rc(x)].sum;
}

void build1(long long x,long long l,long long r)
{
	tr1[x].mx=tr1[x].sum=0;
	if(l==r)
	   {
	   	tr1[x].mx=p[l];
	   	return;
	   }
	long long mid=(l+r)>>1;
	build1(lc(x),l,mid),build1(rc(x),mid+1,r);
	pushup(tr1,x);
}

long long query1(long long x,long long l,long long r,long long lx,long long rx)
{
	if(lx>rx)return 0;
	if(l>=lx&&r<=rx)return tr1[x].mx;
	long long mid=(l+r)>>1,ans=0;
	if(lx<=mid)ans=max(ans,query1(lc(x),l,mid,lx,rx));
	if(rx>=mid+1)ans=max(ans,query1(rc(x),mid+1,r,lx,rx));
	return ans;
}

void build2(long long x,long long l,long long r,long long c)
{
	tr2[x].mx=tr2[x].sum=0;
	if(l==r)
	   {
	   	tr2[x].mx=query1(rt,1,n,a[c][l-1]+1,a[c][l]-1);
	   	return;
	   }
	long long mid=(l+r)>>1;
	build2(lc(x),l,mid,c),build2(rc(x),mid+1,r,c);
	pushup(tr2,x);
}

void add(long long x,long long l,long long r,long long p,long long k)
{
	if(l==r)
	   {
	   	tr2[x].sum+=k;
	   	return;
	   }
	long long mid=(l+r)>>1;
	if(p<=mid)add(lc(x),l,mid,p,k);
	else add(rc(x),mid+1,r,p,k);
	pushup(tr2,x);
}

long long query2(long long x,long long l,long long r,long long lx,long long rx)
{
	if(lx>rx)return 0;
	if(l>=lx&&r<=rx)return tr2[x].mx;
	long long mid=(l+r)>>1,ans=0;
	if(lx<=mid)ans=max(ans,query2(lc(x),l,mid,lx,rx));
	if(rx>=mid+1)ans=max(ans,query2(rc(x),mid+1,r,lx,rx));
	return ans;
}

long long query3(long long x,long long l,long long r,long long lx,long long rx)
{
	if(lx>rx)return 0;
	if(l>=lx&&r<=rx)return tr2[x].sum;
	long long mid=(l+r)>>1,ans=0;
	if(lx<=mid)ans=ans+query3(lc(x),l,mid,lx,rx);
	if(rx>=mid+1)ans=ans+query3(rc(x),mid+1,r,lx,rx);
	return ans;
}

int main()
{
	scanf("%lld",&t);
	while(t--)
	   {
	   	scanf("%lld",&n);
	   	for(int i=1;i<=n;i++)a[i].clear(),a[i].push_back(0);
	   	for(int i=1;i<=n;i++)scanf("%lld",&p[i]);
	   	for(int i=1;i<=n;i++)scanf("%lld",&c[i]),a[c[i]].push_back(i);
	   	build1(rt,1,n);
	   	long long ans=1;
	   	for(int i=1;i<=n;i++)
	   	    if(a[i].size()>1)
	   	       {
	   	       long long w=a[i].size()-1;
	   	       build2(rt,1,w,i);
	   	       for(int j=1;j<=w;j++)b[j].first=p[a[i][j]],b[j].second=j;
	   	       sort(b+1,b+w+1);
	   	       for(int j=1;j<=w;j++)
		   	       {
		   	       long long l=1,r=b[j].second-1,lx=r+1,rx=r+1;
		   	       while(l<=r)
		   	          {
		   	          	long long mid=(l+r)>>1;
		   	          	if(query2(rt,1,w,mid+1,b[j].second)<b[j].first)lx=mid,r=mid-1;
		   	          	else l=mid+1;
					  }
				   l=b[j].second+1,r=w;
				   while(l<=r)
		   	          {
		   	          	long long mid=(l+r)>>1;
		   	          	if(query2(rt,1,w,b[j].second+1,mid)<b[j].first)rx=mid,l=mid+1;
		   	          	else r=mid-1;
					  }
				   ans=ans*(rx-lx+1-query3(rt,1,w,lx,rx))%mod,add(rt,1,w,lx,1);
				   }
			   }
		printf("%lld\n",ans%mod);
	   	}
	return 0;
}
```

---

## 作者：Redshift_Shine (赞：2)

重力排序确实挺有趣的，可惜太慢了，不实用。但是可以用来出题。

考虑按列从前往后考虑。

由于 $p$ 是个排列，所以每次都会从一列中删掉一行。

显然，从一列中删掉与原来的一列中删掉的位置处在同一个**极大同色连通块**中的位置不会影响后一列的形态。

所以解法显然。使用链表+并查集动态处理删除的位置以及极大连通块的大小，将删除途中所有所在极大同色连通块的大小乘起来即为答案。

时间复杂度 $O(n\alpha(n))$。

```c++
// #define Redshift_Debug
#ifdef Redshift_Debug
#define debug(...) fprintf(stderr, __VA_ARGS__)
#include <chrono>
#else
#define debug(...)
#endif
#include <cstdio>

using namespace std;
const int N = 2e5 + 10, mod = 998244353;
int n, a[N], b[N], prv[N], nxt[N], f[N], sz[N], rnk[N], res;
inline int find(int x)
{
	return x == f[x] ? x : f[x] = find(f[x]);
}
inline void merge(int x, int y)
{
	x = find(x), y = find(y);
	if (x == y)
		return;
	f[y] = x;
	sz[x] += sz[y];
	sz[y] = 0;
}
void init_global()
{
}
void init_local()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", a + i), f[i] = i, sz[i] = 1, rnk[a[i]] = i;
	for (int i = 1; i <= n; i++)
		scanf("%d", b + i), nxt[i] = i + 1, prv[i] = i - 1;
	nxt[0] = 1, prv[n + 1] = n, b[n + 1] = 0;
}
void run()
{
	res = 1;
	for (int i = 1; i < n; i++)
	{
		if (b[i] == b[i + 1])
			merge(i, i + 1);
	}
	for (int i = 1, j; i <= n; i++)
	{
		j = rnk[i];
		res = 1ll * res * sz[find(j)] % mod;
		sz[find(j)]--;
		if (b[nxt[j]] == b[prv[j]])
			merge(prv[j], nxt[j]);
		prv[nxt[j]] = prv[j], nxt[prv[j]] = nxt[j];
	}
	printf("%d\n", res);
}
int main()
{
#ifdef Redshift_Debug
	auto st = chrono::high_resolution_clock::now();
#endif
	int T = 1;
	scanf("%d", &T);
	init_global();
	while (T--)
	{
		init_local();
		run();
	}
#ifdef Redshift_Debug
	auto ed = chrono::high_resolution_clock::now();
	fprintf(stderr, "%.9lf\n", (ed - st).count() / 1e9);
#endif
}
```

---

## 作者：flyfreemrn (赞：1)

[链接：E](https://codeforces.com/contest/2064/problem/E)

首先，我们可以知道，每一行的颜色是不能更换的，因为第一列不会下落，如果我们更换了每一行的颜色，那么第一列一定不符合要求。

其次，什么时候两行交换位置不会对最终的形态造成影响，当我们找到颜色相同的两行 $i,j$ 且 $i,j$ 中间所有不同颜色行的长度都小于 $i,j$。

这个时候，$i,j$ 两行的沙块会在最终的三角形中相接，可以自己手模一边。

这样的话，一行对于答案的影响是所有满足上述条件的行的个数，讲所有行的贡献相乘就是答案。

我们可以从长度小的行开始，统计完长度为 $i$ 的行后把这一行删去，这样，当我们遍历到一行 $i$ 时，所有与 $i$ 满足条件的行 $j$ 都会与 $i$ 连通（中间颜色都相同）。

我们可以用链表维护删边，然后用并查集维护连通块大小，删除一行后判断两端颜色是否相同，相同的话就将并查集合并，这一行对答案的贡献也就等于连通块大小。

[AC记录](https://codeforces.com/contest/2064/submission/306555391)

---

## 作者：ywli08 (赞：1)

我们发现如果知道最后的结果，可以反推出排列与颜色的对应情况：假设我们知道第 $i$ 列和第 $i + 1$ 列的颜色序列分别是 $C_{i, 1}, \dots, C_{i, n - i + 1}$ 与 $C_{i+1, 1}, \dots, C_{i + 1, n - i}$，由题目知道这两者编辑距离为 $1$，它们应该长这样：
$$
\begin{matrix}
C_{i, 1} \\
C_{i, 2} & C_{i, 1} \\
C_{i, 3} & C_{i, 2} \\
\vdots & \vdots \\
\textcolor{green}{C_{i, k}} & C_{i, k-1} \\
\textcolor{red}{C_{i, k + 1}} & \textcolor{red}{C_{i, k + 1}}\\
\vdots & \vdots
\end{matrix}
$$
我们可以找出这个 $\textcolor{green}{C_{i, k}}$，其就是 $i$ 对应的颜色。由此我们可以证明，对于某一种排序结果，某个数 $x$ 对应的颜色是一定的。

所以我们可以记录每一个 $p_i, c_i$ 对，并且记 $pos_i$ 为 $i$ 所在的位置，$col_{p_i}$ 为 $p_i$ 对应的 $c_i$。

考虑是什么在对答案做贡献。还是这张图
$$
\begin{matrix}
& C_{i, 1} \\
& C_{i, 2} & & C_{i + 1, 1} \\
& C_{i, 3} & & C_{i + 1, 2} \\
& \vdots & & \vdots \\
\rightarrow & \textcolor{green}{C_{i + 1, l}} & & \vdots \\
& \vdots & \nwarrow & \textcolor{green}{C_{i + 1, l}}\\
& \vdots & & \vdots \\
\rightarrow & \textcolor{green}{C_{i, k}} & \Longleftrightarrow & \textcolor{green}{C_{i + 1, k - 1}} \\
& \vdots & & \vdots \\
\rightarrow & \textcolor{green}{C_{i, r}} & \Longleftrightarrow & \textcolor{green}{C_{i + 1, r - 1}} \\
& \textcolor{red}{C_{i, r + 1}} & \Longleftrightarrow & \textcolor{red}{C_{i + 1, r}}\\
& \vdots & & \vdots
\end{matrix}
$$
现在我们向列 $C_{i + 1}$ 中插入 $col_i = C_{i, k}$，并且我们知道，$C_{i, l}$ 到 $C_{i, r}$ 中间的颜色都是一样的。我们发现，对于 $C_{i, k}$ 所在的**颜色连续段** $[l, r]$，$col_i$ 可以插入**连续段中的任意间隔**，就是说下面几种是等价的：
$$
\begin{matrix}
C_{i, 1} \\
C_{i, 2} & C_{i + 1, 1} \\
C_{i, 3} & C_{i + 1, 2} \\
\vdots & \vdots \\
\textcolor{green}{C_{i, l} = col_i} & \vdots \\
\textcolor{green}{C_{i, l + 1} = C_{i + 1, l}} & \textcolor{green}{C_{i + 1, l}}\\
\vdots & \vdots \\
\vdots & \vdots \\
\textcolor{green}{C_{i, r} = C_{i + 1, r - 1}} & \textcolor{green}{C_{i + 1, r - 1}} \\
\textcolor{red}{C_{i, r + 1} = C_{i + 1, r}} & \textcolor{red}{C_{i + 1, r}}\\
\vdots & \vdots
\end{matrix}

\quad \Longleftrightarrow \quad

\begin{matrix}
C_{i, 1} \\
C_{i, 2} & C_{i + 1, 1} \\
C_{i, 3} & C_{i + 1, 2} \\
\vdots & \vdots \\
\textcolor{green}{C_{i, l} = C_{i + 1, l}} & \vdots \\ 
\vdots & \textcolor{green}{C_{i + 1, l}}\\
\textcolor{green}{C_{i, mid} = col_i} & \vdots \\
\vdots & \vdots \\
\textcolor{green}{C_{i, r} = C_{i + 1, r - 1}} & \textcolor{green}{C_{i + 1, r - 1}} \\
\textcolor{red}{C_{i, r + 1} = C_{i + 1, r}} & \textcolor{red}{C_{i + 1, r}}\\
\vdots & \vdots
\end{matrix}

\quad \Longleftrightarrow \quad

\begin{matrix}
C_{i, 1} \\
C_{i, 2} & C_{i + 1, 1} \\
C_{i, 3} & C_{i + 1, 2} \\
\vdots & \vdots \\
\textcolor{green}{C_{i, l} = C_{i + 1, l}} & \vdots \\
\vdots & \textcolor{green}{C_{i + 1, l}}\\
\vdots & \vdots \\
\textcolor{green}{C_{i, r - 1} = C_{i + 1, r - 1}} & \vdots \\
\textcolor{green}{C_{i, k} = col_i} & \textcolor{green}{C_{i + 1, r - 1}} \\
\textcolor{red}{C_{i, r + 1} = C_{i + 1, r}} & \textcolor{red}{C_{i + 1, r}}\\
\vdots & \vdots
\end{matrix}
$$
可以得到 $i$ 的贡献既是 $r - l + 1$。由乘法原理得
$$
ans = \prod_i (r_i - l_i + 1).
$$
用数据结构维护 $i$ 所在的颜色连续段即可。可以按 $pos_i$ 建立线段树，每个叶子节点维护所在段的左右端点，每个线段树节点维护对应子段目前存在多少个数。

具体地说，我们从大到小加入 $i$，用 `set` 维护 $pos_i$ 的前驱后继；对于前驱后继的颜色与当前的颜色进行分类讨论，更新每个点所在段端点。

更详细看程序。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5+5;
const ll mod = 998244353;

int n, m;
int a[maxn], pos[maxn];
int col[maxn];
ll dp[maxn];
ll cnt[maxn];

set<int> st;

struct segnode{
    int lt, rt;
    int siz;
    void push_up(segnode a, segnode b){
        siz = a.siz + b.siz;
    }
    int ch[2];
};

struct tagnode{
    int lt = 0, rt = 0;
};

struct segtree{
    segnode tr[maxn << 2];
    tagnode tag[maxn << 2];
    int rt, sz;
    void build(int &x, int l, int r){
        x = ++sz;
        if(l == r){
            tr[x] = {l, r};
            return ;
        }
        int mid = l + r >> 1;
        build(tr[x].ch[0], l, mid);
        build(tr[x].ch[1], mid + 1, r);
        tr[x].push_up(tr[tr[x].ch[0]], tr[tr[x].ch[1]]);
    }
    void lazy(int x, tagnode k){
        if(k.lt != 0){
            tr[x].lt = k.lt;
            tag[x].lt = k.lt;
        }
        if(k.rt != 0){
            tr[x].rt = k.rt;
            tag[x].rt = k.rt;
        }
    }
    void push_down(int x){
        lazy(tr[x].ch[0], tag[x]);
        lazy(tr[x].ch[1], tag[x]);
        tag[x] = tagnode();
    }
    void update(int lt, int rt, tagnode k, int l, int r, int x){
        if(lt <= l && r <= rt){
            return lazy(x, k);
        }
        int mid = l + r >> 1;
        push_down(x);
        if(lt <= mid) update(lt, rt, k, l, mid, tr[x].ch[0]);
        if(rt > mid) update(lt, rt, k, mid + 1, r, tr[x].ch[1]);
        tr[x].push_up(tr[tr[x].ch[0]], tr[tr[x].ch[1]]);
        return ;
    }
    void add(int pt, int l, int r, int x){
        if(l == r){
            return tr[x].siz ++, void();
        }
        int mid = l + r >> 1;
        push_down(x);
        if(pt <= mid) add(pt, l, mid, tr[x].ch[0]);
        else add(pt, mid + 1, r, tr[x].ch[1]);
        tr[x].push_up(tr[tr[x].ch[0]], tr[tr[x].ch[1]]);
    }
    segnode query(int pt, int l, int r, int x){
        if(l == r){
            return tr[x];
        }
        int mid = l + r >> 1;
        segnode ans;
        push_down(x);
        if(pt <= mid) ans = query(pt, l, mid, tr[x].ch[0]);
        else ans = query(pt, mid + 1, r, tr[x].ch[1]);
        tr[x].push_up(tr[tr[x].ch[0]], tr[tr[x].ch[1]]);
        return ans;
    }
    ll size(int lt, int rt, int l, int r, int x){
        if(lt <= l && r <= rt){
            return tr[x].siz;
        }
        int mid = l + r >> 1;
        ll ans = 0;
        push_down(x);
        if(lt <= mid) ans += size(lt, rt, l, mid, tr[x].ch[0]);
        if(rt > mid) ans += size(lt, rt, mid + 1, r, tr[x].ch[1]);
        tr[x].push_up(tr[tr[x].ch[0]], tr[tr[x].ch[1]]);
        return ans;
    }
}tree;

int _main(){
    cin >> n;
    for(int i = 1;i <= n;i++){
        cin >> a[i]; pos[a[i]] = i;
    }
    a[0] = 0, a[n + 1] = n + 1;
    pos[0] = 0, pos[n + 1] = n + 1;
    col[0] = 0, col[n + 1] = n + 1;
    for(int i = 1;i <= n;i++){
        cin >> col[a[i]];
    }
    st.insert(0), st.insert(n + 1);
    dp[n + 1] = 1;
    tree.build(tree.rt, 1, n);
    for(int i = n;i >= 1;i--){
        ll tmp = 0;
        int pre = *--st.lower_bound(pos[i]);
        int nxt = *st.lower_bound(pos[i]);
         if(col[a[pre]] == col[i] && col[a[nxt]] == col[i]){
            auto [lt, _1, sizl, _cl] = tree.query(pre, 1, n, tree.rt);
            auto [_2, rt, sizr, _cr] = tree.query(nxt, 1, n, tree.rt);
            auto siz = tree.size(lt, rt, 1, n, tree.rt);
            tree.update(lt, rt, {lt, rt}, 1, n, tree.rt);
            tmp = siz + 1;
        }
        else if(col[a[pre]] == col[i]){
            auto [lt, _1, sizl, _cl] = tree.query(pre, 1, n, tree.rt);
            tree.update(lt, pos[i], {lt, pos[i]}, 1, n, tree.rt);
            auto siz = tree.size(lt, pre, 1, n, tree.rt);
            tmp = siz + 1;
        }
        else if(col[a[nxt]] == col[i]){
            auto [_2, rt, sizr, _cr] = tree.query(nxt, 1, n, tree.rt);
            tree.update(pos[i], rt, {pos[i], rt}, 1, n, tree.rt);
            auto siz = tree.size(nxt, rt, 1, n, tree.rt);
            tmp = siz + 1;
        }
        else{
            if(col[a[nxt]] != col[a[pre]]){
                tree.update(pos[i], pos[i], {pos[i], pos[i]}, 1, n, tree.rt);
                tmp = 1;
            }
            else{
                auto [lt, _1, sizl, _cl] = tree.query(pre, 1, n, tree.rt);
                auto [_2, rt, sizr, _cr] = tree.query(nxt, 1, n, tree.rt);
                tree.update(lt, pre, {lt, pre}, 1, n, tree.rt);
                tree.update(nxt, rt, {nxt, rt}, 1, n, tree.rt);
                tree.update(pos[i], pos[i], {pos[i], pos[i]}, 1, n, tree.rt);
                tmp = 1;
            }
        }
        dp[i] = dp[i + 1] * tmp % mod;
        tree.add(pos[i], 1, n, tree.rt); st.insert(pos[i]);
    }
    cout << dp[1] << endl;
    tree.sz = 0; tree.rt = 0;
    for(int i = 0;i <= n + 1;i++){
        a[i] = pos[i] = col[i] = 0;
        dp[i] = 0;
    } st.clear();
    return 0;
}

int T;

int main(){
    cin >> T;
    while(T--){
        _main();
    }
}
```

---

## 作者：yvbf (赞：0)

![](bilibili:BV19cAaeVEme?t=2596)

---

## 作者：MightZero (赞：0)

### Preface

简单题，没场切完全是自己作的/kk

### Solution

以下定义 $rk_i$ 为第 $i$ 根柱子的长度，$p_i$ 为长度 $i$ 的柱子所在的位置（两者互为逆排列），$col_i$ 为第 $i$ 根柱子的颜色。 

观察样例和题目配图，发现最左侧一列在重力作用后不变，可以得到合法排列的颜色序列是固定的，即所有合法方案的 $col$ 都相同；因此可以把每种颜色单独提出来观察。

注意到对于一个固定的长度，所有合法方案中对应长度的柱子的颜色必定是相同的，即不存在两种安排柱子的方案 $\{rk,p\},\{rk',p'\}$，使得存在 $i$ 满足 $col_{p_i}\neq col_{p'_i}$。由此得出的结论是只能改变同种颜色的柱子的排列顺序。

对于两个颜色相同的柱子，假设它们的长度分别为 $x,y$，且 $p_x<p_y$
，则两根柱子能交换的充要条件是 $\forall i \in (p_x,p_y),rk_i<\min(x,y)$。因此忽略掉高度小于某值的所有柱子后，同色柱子会构成联通块，联通块的大小即为每根柱子能安放的位置数量，可以用并查集维护联通块及其大小。根据一般套路，考虑按照长度从小到大删除柱子，将答案乘上被删除柱子所在联通块的大小，删除后合并两侧的柱子（如果同色），并将被删除的柱子所在的联通块大小减 $1$。

**误区 统计联通块的最终大小再计算阶乘之积是错误的**：每根柱子可能安放的位置必须满足上述的条件，即合并联通块删去的所有柱子高度必须小于当前柱子，联通块大小才能表示当前柱子能安放的位置数量，也就是**从大到小枚举到当前柱子时联通块的大小**，而非**最终合并完成后联通块的大小**，否则答案会偏大。（赛时就是因为这个挂的）

对于删除柱子和查找两侧的柱子，可以用链表（`std::list`）维护，联通块的维护可以用并查集，总体时间复杂度 $O(n\alpha(n))$。

### Code

非常短且好写。


``` cpp
#include<bits/stdc++.h>
#define loop(x,l,r) for(ll (x) = (l);(x)<=(r);++(x))
#define rloop(x,l,r) for(ll (x) = (r);(x)>=(l);--(x))
#define elif else if
using namespace std;
using ll = long long;
inline ll read()
{
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x*=10;x+=ch-'0';ch=getchar();}
    return x*f;
}
const ll N=2e5+5,mod=998244353;
ll n,ans,p[N],rk[N],col[N],fa[N],sz[N];
list<ll> ls;
list<ll>::iterator its[N];
ll find(ll x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void merge(ll x,ll y){x=find(x),y=find(y);if(x^y){fa[x]=y,sz[y]+=sz[x];}}
void solve()
{
    n=read(),ans=1,ls.clear();
    loop(i,1,n)rk[i]=read(),fa[i]=i,sz[i]=1,ls.push_back(i),its[i]=prev(ls.end());
    loop(i,1,n)col[i]=read(),p[rk[i]]=i;
    loop(i,2,n)if(col[i]==col[i-1])merge(i,i-1);
    loop(i,1,n)
    {
        ll np=p[i];
        ans=(ans*sz[find(np)])%mod;
        auto it=its[np],itp=prev(it),itn=next(it);
        if(it!=ls.begin()&&itn!=ls.end()&&col[*itp]==col[*itn])merge(*itp,*itn);
        ls.erase(it),sz[find(np)]--;
    }
    printf("%lld\n",ans);
}   
signed main()
{
    ll T=read();
    while(T--)solve();    
    return 0;
}
```

---

## 作者：DerrickLo (赞：0)

实际上 $c'$ 必然等于 $c$，所以只需要统计 $p$ 的个数即可。

设原来的集合是 $\{1,2,\ldots,n\}$，然后每次删去一个数，相当于对于第 $i$ 次，删去 $p_j=i$ 的 $j$，然后 $n$ 次删完。不难发现每个删数的方式都对应了一个排列 $p$，我们只需要对删数的方式计数即可。

考虑第 $i$ 列的所有方块的颜色是什么，不难发现就是从前到后所有满足 $p_j\ge i$ 的 $c_j$ 构成的序列。而对于第 $i$ 次删数，方案数就是满足 $p_j=i$ 的 $j$ 所在的颜色相同的连续段的长度，因为我们删去所有这个连续段中的数都不会改变删掉后的颜色，而删去其他数则必然改变。直接把所有 $n$ 次的方案数乘起来就可以了。

使用 set 维护连续段，时间复杂度 $\mathcal O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define mod 998244353
#define int long long
using namespace std;
int t,n,p[200005],c[200005],pos[200005];
struct nd{
	int l,len,x;
	friend bool operator<(const nd&a,const nd&b){
		return a.l<b.l;
	}
};
multiset<nd>st;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n,st.clear();
		for(int i=1;i<=n;i++)cin>>p[i],pos[p[i]]=i;
		for(int i=1;i<=n;i++)cin>>c[i];
		int ans=1,lst=1;
		for(int i=1;i<=n;i++)if(c[i]!=c[lst])st.insert({lst,i-lst,c[lst]}),lst=i;st.insert({lst,n-lst+1,c[lst]}); 
		for(int i=1;i<=n;i++){
			int x=pos[i];
			int sum=0;
			auto it=st.upper_bound((nd){x,0,0});it--;
			auto pp=*it;
			if(pp.len!=1){
				ans*=pp.len,ans%=mod;
				st.erase(st.find(pp)),pp.len--;
				st.insert(pp);continue;
			}
			if(it!=st.begin()){
				it--;auto xx=*it;it++;
				it++;
				if(it!=st.end()){
					auto yy=*it;
					if(xx.x==yy.x){
						st.erase(st.find(xx)),st.erase(st.find(yy));
						st.insert((nd){xx.l,xx.len+yy.len,xx.x});
					}
				}
			}
			st.erase(st.find(pp));
		}
		cout<<ans<<"\n";
	}
}
```

---

