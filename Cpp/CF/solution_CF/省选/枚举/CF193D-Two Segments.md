# Two Segments

## 题目描述

Nick has some permutation consisting of $ p $ integers from $ 1 $ to $ n $ . A segment $ [l,r] $ ( $ l<=r $ ) is a set of elements $ p_{i} $ satisfying $ l<=i<=r $ .

Nick calls a pair of segments $ [a_{0},a_{1}] $ and $ [b_{0},b_{1}] $ ( $ 1<=a_{0}<=a_{1}&lt;b_{0}<=b_{1}<=n $ ) good if all their $ (a_{1}-a_{0}+b_{1}-b_{0}+2) $ elements, when sorted in ascending order, form an arithmetic progression with a difference of $ 1 $ . That is, when they sorted in ascending order, the elements are in the form $ {x,x+1,x+2,...,x+m-1} $ , for some $ x $ and $ m $ .

Your task is to find the number of distinct pairs of good segments in the given permutation. Two pairs of segments are considered distinct if the sets of elements contained in these pairs of segments are distinct. For example, any segment $ [l,r] $ $ (l&lt;r) $ can be represented as a pair of segments, as $ [l,i] $ and $ [i+1,r] $ ( $ l<=i<=r $ ). As all these pairs consist of the same set of elements, they are considered identical.

See the notes accompanying the sample tests for clarification.

## 说明/提示

In the first sample the following pairs of segments are good: ( $ [1,1] $ , $ [2,2] $ ); ( $ [2,2] $ , $ [3,3] $ ); ( $ [1,2] $ , $ [3,3] $ ). Pair of segments ( $ [1,1] $ , $ [2,3] $ ) is by definition equivalent to pair ( $ [1,2] $ , $ [3,3] $ ), since both of them covers the same set of elements, namely $ {1,2,3} $ .

In the third sample the following pairs of segments are good: ( $ [4,4] $ , $ [5,5] $ ); ( $ [3,3] $ , $ [4,5] $ ); ( $ [2,2] $ , $ [3,5] $ ); ( $ [1,1] $ , $ [2,5] $ ); ( $ [3,3] $ , $ [5,5] $ ); ( $ [2,3] $ , $ [5,5] $ ); ( $ [1,3] $ , $ [5,5] $ ); ( $ [2,2] $ , $ [3,3] $ ); ( $ [1,1] $ , $ [2,3] $ ); ( $ [1,1] $ , $ [2,2] $ ).

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5
1 4 5 3 2
```

### 输出

```
10
```

## 样例 #3

### 输入

```
5
5 4 3 1 2
```

### 输出

```
10
```

# 题解

## 作者：Iang_ (赞：8)

拿到题有两种思路：

- 第一种枚举两个区间；

- 第二种枚举连续的值域区间。

第一种不好做 ~~（至少我不会T_T）~~ ，第二种一眼看上去比较可做。
对于这种区间问题，一般套路是确定一个点，然后对其他点算贡献。

我们枚举右端点 $i$，那么小于等于 $i$ 的数都要插入，所以按照 $1\sim n$ 插入节点维护一颗权值线段树。对于第 $j$ 个点 $(j<i)$ 需要维护 $j\sim i$ 权值区间需要分块数量的最小值，可以再维护区间最小值$mn$，最小值数量 $cnt[0]$，次小值数量 $cnt[1]$，次小值一定是 $mn+1$ （对于 $mn$ 所对应的段多分一段）。

当一个点作为右端点插入时，先假设这个点需要另分一块，就把 $1\sim i$ 的区间数量 $+1$，即 $add(1,i,1)$。若在原 $a[i]$ 序列中 $a[i-1]<i$ 说明 $a[i-1]$ 插入过，$1\sim a[i-1]$ 所有值到 $i$ 分块数 $-1$（$a[i+1]$ 同理）。最后询问$1\sim i-1$ 需要分的块数是否小于等于 $2$ 即可。

具体细节见代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct Tree {
	int l,r;
	int mn; //区间最小值 
	int AG; //区间最小值出现次数 
	int DYG; //区间次小值出现次数 
	lazy;
}t[1200010];
int n,a[300010],p[300010],ans;
void update(int p) {
	t[p].mn=min(t[p<<1].mn,t[p<<1|1].mn);
	t[p].AG=t[p<<1].AG*(t[p<<1].mn==t[p].mn)+t[p<<1|1].AG*(t[p<<1|1].mn==t[p].mn);
	t[p].DYG=(t[p<<1].mn==t[p].mn)*t[p<<1].DYG+(t[p<<1].mn==t[p].mn+1)*t[p<<1].AG+(t[p<<1|1].mn==t[p].mn)*t[p<<1|1].DYG+(t[p<<1|1].mn==t[p].mn+1)*t[p<<1|1].AG;
}
void spread(int p) {
	t[p<<1].mn+=t[p].lazy;
	t[p<<1|1].mn+=t[p].lazy;
	t[p<<1].lazy+=t[p].lazy;
	t[p<<1|1].lazy+=t[p].lazy;
	t[p].lazy=0;
}
void build(int p,int l,int r) {
	t[p].l=l,t[p].r=r;
	if(l==r) {
		t[p].AG=1;
		return ;
	}
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	update(p);
}
void add(int p,int l,int r,int val) {
	if(t[p].l>r||t[p].r<l) return ;
	if(t[p].l>=l&&t[p].r<=r) {
		t[p].mn+=val;
		t[p].lazy+=val;
		return ;
	}
	spread(p);
	add(p<<1,l,r,val);
	add(p<<1|1,l,r,val);
	update(p);
}
int ask(int p,int l,int r) {
	if(t[p].l>r||t[p].r<l) return 0;
	if(t[p].l>=l&&t[p].r<=r) return t[p].AG*(t[p].mn<=2)+t[p].DYG*(t[p].mn<=1);
	//最小值<=2就加上最小值的方案数，最小值<=1就加上次小值的方案数（因为此时次小值为2） 
	spread(p);
	return ask(p<<1,l,r)+ask(p<<1|1,l,r);
}
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]),p[a[i]]=i;
	build(1,1,n);
	for(int i=1;i<=n;i++) {
		add(1,1,i,1);
		if(a[p[i]-1]<i&&a[p[i]-1]) add(1,1,a[p[i]-1],-1);
		if(a[p[i]+1]<i&&a[p[i]+1]) add(1,1,a[p[i]+1],-1);
		ans+=ask(1,1,i-1);
	}
	printf("%lld",ans);
	return 0;
}
```

~~不要在意我的变量名QAQ。~~

**这确实是一道好题，转化枚举的权值区间很有学习价值。**

---

## 作者：chengni (赞：5)

这道题个人感觉很难，不知道能否说明白

首先，我们枚举的东西是两个小区间得到的那个连续区间是什么，而不是那两个小区间分别是什么

对于区间 $[l,r]$ 如果这段区间能被表示出来，那么其最多能被分成两段。

朴素做法是 $n^2$ 枚举区间，这样肯定不行

我们枚举答案区间的右端点 $r$ ,每次统计 $[1,r]$之间的i,有多少 $[i,r] $ 被分成 $1$ 段或 $2$ 段.

我们要维护的东西，是这个区间里最少被分成多少段，次少被分成多少段以及各自的方案数。

我们从小到大枚举 $i$ ，每次新加入一个数的时候，令 $x$ 在原全排列中左边的数为$l$ ,右边的数为 $r$ .如果它们 $≤x$ ,那么就在之前被插入过了；如果 $l$ 和 $r$ 都没有被插入，那么 $x$ 将组成一个独立的区间;如果 $l$ 和 $r$ 都被插入了，那么$x$ 将会使区间数减少 $1$，否则区间数保持不变。

我们开一棵线段树，用这种方式来进行更新

因为次少段数是最少段数加一，所以我们可以不记录。

统计答案的时候判断两个段数是否都小于等于 $2$ 即可，即我们统计的答案是有多少符合条件的连续区间在全排列中为 $1$ 段或 $2$ 段。

线段树的传递信息过程具体看代码吧

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

inline ll read(){
	char ch=getchar();ll x=0,f=1;
    while(ch<'0' || ch>'9') {
       if(ch=='-') f=-1;
	  	  ch=getchar();
	}
    while(ch<='9' && ch>='0') {
	   x=x*10+ch-'0';
	   ch=getchar();
	}
    return x*f;
}

struct node{
	int l,r;
	int m,f,g,d;
}t[8040404];

int a[8020202],p[8020202];

void build(int p,int l,int r){
	t[p].l=l;t[p].r=r;
	if(l==r){
		t[p].f=1;
		return;
	}
	int mid=l+r>>1;
	build(p<<1,l,mid);build(p<<1|1,mid+1,r);
}

void pushup(int p){
	t[p].m=min(t[p<<1].m,t[p<<1|1].m);
	t[p].f=t[p<<1].f*(t[p].m==t[p<<1].m)+t[p<<1|1].f*(t[p].m==t[p<<1|1].m);
	t[p].g=t[p<<1].g*(t[p].m==t[p<<1].m)+t[p<<1|1].g*(t[p].m==t[p<<1|1].m)+t[p<<1].f*(t[p].m==t[p<<1].m-1)+t[p<<1|1].f*(t[p].m==t[p<<1|1].m-1);	
}

void pushdown(int p){
	t[p<<1].m+=t[p].d;t[p<<1|1].m+=t[p].d;
	t[p<<1].d+=t[p].d;t[p<<1|1].d+=t[p].d;
	t[p].d=0;
}

void updata(int p,int l,int r,int v){
	if(l<=t[p].l && r>=t[p].r){
		t[p].m+=v;
		t[p].d+=v;
		return;
	}
	if(t[p].d) pushdown(p);
	int mid=t[p].l+t[p].r>>1;
	if(l<=mid) updata(p<<1,l,r,v);
	if(r>mid) updata(p<<1|1,l,r,v);
	pushup(p);
}


int qsum(int p,int l,int r){
	if(l<=t[p].l && r>=t[p].r){
		return t[p].f*(t[p].m<=2)+t[p].g*(t[p].m<=1);
	}
	pushdown(p);
	int mid=t[p].l+t[p].r>>1;
	int ans=0;
	if(l<=mid) ans+=qsum(p<<1,l,r);
	if(r>mid) ans+=qsum(p<<1|1,l,r);
	return ans; 
}

int main(){
	int n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		p[a[i]]=i;
	}
	build(1,1,n);
	ll ans=0;
	for(int i=1;i<=n;i++){
		int x=a[p[i]-1],y=a[p[i]+1];
		updata(1,1,i,1);
		if(x && x<i) updata(1,1,x,-1);
		if(y && y<i) updata(1,1,y,-1);
		ans+=qsum(1,1,i);
		cout<<ans-i<<endl;
	}
	cout<<ans-n;
	return 0;
}
```
线段树能够维护这些支持合并的信息，这样的题型我还真是没有见过。珂怕。果然数据结构博大精深啊。




---

## 作者：CaoSheng_zzz (赞：3)

挺好的一道题目。

对于本题我们思考一下连续的一段区间满足什么，首先没有重复的数，其次假色区间左端为 $l$，右端为 $r$，最大的数为 $max$，最小的为 $min$，那么 $r - l = max - min$。

如果我们枚举两个区间维护这肯定很难因为我们需要去重，但是我们可以考虑维护值域区间。

那我们可以枚举区间左端点 $r$，然后考虑有多少个 $i \in [1, r]$，有多少个 $[i, r]$ 满足被分成 $1 \sim 2$ 段。

然后我们考虑如何减少时间复杂度，不难发现如果没有两个区间的排序之后的序列为 $l \sim r$ 那么就没有区间满足 $l - 1 \sim r$，如果有两个区间满足排序之后的序列为 $l \sim r$ 那么就一定有两个区间满足排完序之后序列为 $l + 1 \sim r (l + 1 \leqslant r)$。所以 $l$ 可以作为全局变量我们只需要在枚举 $r$ 的时候维护 $l$ 就行了。

对于答案的统计用线段树维护即可。

---

## 作者：lOpzIth (赞：3)

题很好，和同学讨论出来了一种奇怪的分块做法。

考虑这个题本质上是求有多少个在值域上的区间满足：它们的出现位置可以被表示成序列上的两个区间。这个条件也等价于它们出现位置为 $1$ 或 $2$ 个区间，且长度不为 $1$。

枚举值域上的区间右端点 $r$。我们要求有多少左端点 $l$ 满足以上条件。自然的考虑到可以维护当前形成的连续段数量 $cnt$，再维护出撤销一个前缀 $i$ 对整个序列连续段数量的影响。因为每次撤销和加入操作带来的贡献只会受其左右影响，所以这个维护是可行的。

首先，我们每次加入一个数 $r$，记 $r$ 在排列中出现位置为 $pos$，排列为数组 $per$。

- 若 $per_{pos - 1} < r$ 且 $per_{pos + 1} < r$，则其对当前连续段数量的贡献为 $1$。

- 若 $per_{pos - 1} < r$ 或 $per_{pos + 1} < r$，则没有贡献。

- 若 $per_{pos - 1} > r$ 且 $per_{pos + 1} > r$，则贡献为 $-1$。

接着，考虑撤销 $r$ 这个前缀的影响，显然它会比撤销 $r - 1$ 再少一个连续段，即为 $-1$。

我们还要考虑新加入 $r$ 会对它左右的撤销带来怎样的影响。

显然 $r$ 对左边和对右边的影响是等价的，在此只考虑对左边的影响，并且，只有 $per_{pos - 1} < r$ 时，$r$ 才会对 $per_{pos - 1}$ 产生影响。

- $per_{pos - 2} \in [1, per_{pos - 1})$ 我们会将其贡献 $-1 \rightarrow 0$。

- $per_{pos - 2} \in (per_{pos - 1}, r)$ 我们会将其贡献 $0 \rightarrow 1$。

- $per_{pos - 2} \in (x, n]$ 我们会将其贡献 $-1 \rightarrow 0$。

经过讨论，我们发现，若产生影响，则只会将对应位置贡献 $+1$。

现在我们维护出每个位置实时对应的撤销的贡献，并做一遍前缀和得到前缀和数组 $sum$。值域区间 $[l, r]$ 对应的连续段数量即为：枚举右端点到 $r$ 时的连续段数量 $cnt$ 再加上 $sum_{l - 1}$。所以，每个右端点对答案贡献即为 $i \in [1, r]$ 中，有多少 $cnt + sum_i = 1$ 和有多少 $cnt + sum_i = 2$。

那么如何维护 $sum$ 数组？

发现 $sum$ 数组在右端点移动后只会修改至多 $2$ 次区间值，所以我们希望有一个数据结构能够维护：

- 区间加。

- 区间查找一个数 $w$ 的出现次数。

然后这个事情单 $\log$ 数据结构显然难以做到，于是考虑根号算法。

首先分块，然后对每个块维护出每个数的出现次数，开一个数组记下来。每次若修改整块则记一个偏移值 $t$，直接对 $t$ 修改，修改散块暴力修改。

同理，查询时整块直接调用数组里的出现次数，散块暴力扫一遍。

记 $B$ 为分块的块数，显然当 $B = \sqrt{n}$ 时最优。

时间复杂度：$O(n \sqrt{n})$。 

空间复杂度：$O(n \sqrt{n})$。

然后我们悲催的发现空间有点炸，大概要 $1024$ 兆。

有一个经典的卡空间 trick。我们枚举每个块，只用考虑操作序列中影响到它的操作，每次只需开一个数组，每次清空即可。

时间复杂度：$O(n \sqrt{n})$。 

空间复杂度：$O(n)$。

最后注意一下细节：长度为 $1$ 的不被计入答案。

卡了卡块长，4.5s 勉强能冲过去。

```cpp
#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace __gnu_pbds;
#define DEFAULT 5e5 + 5
#define int long long
#define i64 long long
#define ll long long
#define i128 __int128
#define ull unsigned long long
#define db double
#define ldb long double
#define Arr std::vector
#define Ptn std::pair
#define fi first
#define se second
#define eb emplace_back
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define popc(x) __builtin_popcountll(x)
#define clz(x) __builtin_clzll(x)
#define ctz(x) __builtin_ctzll(x)
#define FILE(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout)
#define TEST(x) freopen(x ".in", "r", stdin), freopen("test.out", "w", stdout)
#define KEL(x) freopen(x ".in", "r", stdin), freopen("a.out", "w", stdout)
#define debug std::cout << "Running on " << __FUNCTION__ << ' ' << __LINE__ << std::endl;
#define fail assert(0);
bool BeginPoint;
const int INF = 0x3f3f3f3f;
const int llINF = 0x3f3f3f3f3f3f3f3f;
const int N = 3e5 + 5;
const int T = 3e5;
const int B = 1000;
int A[N], now;
int t, count[N << 1];
int n, ans, vis[N], per[N], ref[N], pre[N];
int bn, L[B], R[B], bel[N];
Arr< std::array<int, 4> > C; // {type, L, R, w}   
// type = 1  ->  [L, R] += w
// type = 2  ->  query how many (w) appear in [L, R]
inline int read()
{
    int w = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        w = (w << 3) + (w << 1) + (ch - 48);
        ch = getchar();
    }
    return w * f;
}

void Init()
{
    for (int l = 1, r = B; r <= n; l += B, r += B) 
    {
        L[++bn] = l, R[bn] = r;
        for (int i = l; i <= r; i++) bel[i] = bn;
    }
    if (R[bn] < n)
    {
        L[bn + 1] = R[bn] + 1; bn++; R[bn] = n;
        for (int i = L[bn]; i <= R[bn]; i++) bel[i] = bn;
    }
}

void add(int x, int pos)
{
    if (pos && per[pos - 1] < x) C.pb({1, per[pos - 1], n, 1});
    if (pos < n && per[pos + 1] < x) C.pb({1, per[pos + 1], n, 1});
    if (vis[pos - 1] + vis[pos + 1] == 2)
    {
        now--;
    } // -1
    else if (vis[pos - 1] + vis[pos + 1] == 0)
    {
        now++;
    } // +1
    ans += (now == 1); ans += (now == 2);
    vis[pos] = 1;
    C.pb({2, 1, x, 1 - now});
    C.pb({2, 1, x, 2 - now});
    // add [1 ~ x] SegCnt = now

}

void Calc(int x)
{
    memset(count, 0, sizeof(count)); t = 0;
    for (int i = L[x]; i <= R[x]; i++) count[A[i] + T]++;
    for (auto info : C)
    {
        int typ = info[0], l = info[1], r = info[2], w = info[3];
        if (r < L[x] || R[x] < l) continue;
        l = std::max(l, L[x]), r = std::min(r, R[x]);
        if (typ == 1)
        {
            if (l == L[x] && R[x] == r) t += w;
            else for (int i = l; i <= r; i++) count[A[i] + T]--, A[i] += w, count[A[i] + T]++;
        }
        else 
        {
            if (l == L[x] && R[x] == r)
            {
                if (w + T - t >= 0) ans += count[w + T - t];
            }
            else 
            {
                for (int i = l; i <= r; i++) ans += (A[i] + t == w);
            }
        }
    }
}

void Solve()
{
    Init();
    for (int i = 1; i <= n; i++) add(i, ref[i]);
    for (int i = 1; i <= bn; i++) Calc(i);
    ans -= n;
    printf("%lld\n", ans);
}

bool EndPoint;
signed main()
{
    std::cerr << "Memory = " << fabs(&BeginPoint - &EndPoint) / 1048576.0 << "MB" << std::endl;

    n = read(); for (int i = 1; i <= n; i++) per[i] = read(), ref[per[i]] = i, A[i] = -i;
    per[0] = per[n + 1] = INF;
    Solve();

    std::cerr << "Time = " << (double)clock() / CLOCKS_PER_SEC << "s" << std::endl;
    return 0;
}

```

---

## 作者：ttq012 (赞：2)

$\texttt{Difficulty : }\tt{\color{red}{\star2900}}$。

~~AC喵可爱！~~

## $\texttt{Part 1: 题目简述}$

给一个 $1\sim n$ 的排列 $a$，求有多少种选择两个不重叠的区间 $[l_1, r_1]$ 和 $[l_2,r_2]$ 的方法让这些元素排序之后在值域里是连续的一段。$1\le n\le 3\times 10^5$。

## $\texttt{Part 2: 题解}$

暴力 $1$：暴力枚举两个区间然后排序，时间复杂度 $O(n^4\times \log n)$。

暴力 $2$：将排序改为基数排序，时间复杂度近似于 $O(n^4)$。

正解：萌萌数数题。

开一个位置数组 $p$，$p_i$ 代表 $i$ 在 $a$ 数组的那个地方，并且满足 $a_{p_i}=i$。

在 $a$ 数组中，要求的问题是有多少种选择两个不重叠的区间 $[l_1, r_1]$ 和 $[l_2, r_2]$ 的方法让这些元素单独提溜出来排序之后在值域中是连续的一段，那么在 $p$ 位置数组里，我们需要让选出来的**一段区间**组成的段数 $\le 2$。

优化后的暴力 $3$：计算出 $p$ 之后暴力枚举左右端点，视使用复杂度的优劣为 $O(n^3)\sim O(n^3\times \log^2n)$。

优化后的暴力 $4$：预处理一下，时间复杂度暂未计算（反正无论如何都要枚举左右端点肯定过不去）。

然后考虑进行一次 $\texttt{DP}$。

设 $f[l][r]$ 为 $l\sim r$ 这一段形成了多少个段数 $\le 2$ 的区间。

### 2.1 DP 的初始条件

由于一开始只有 $p_1$ 一个位置，所以有 $f[1][1] = 1$。

### 2.2 DP 的转移方程

假设现在从位置 $p_1$ 开始插入，然后插入 $p_2$，$p_3$，$\cdots$，假设插入到了 $p_i$。

现在我们固定 $\tt{DP}$ 数组的右端点 $i$，也就是要一次性求出 $f[1][i]$，$f[2][i]$，$f[3][i]$，$\cdots$，$f[i][i]$ 且时间复杂度必须保持在 $O(i)$ 级别的。

现在将 $f[1][i]$，$f[2][i]$，$f[3][i]$，$\cdots$，$f[i][i]$ 看做一个一维数组 $g[j]$。

假设现在新插入了一个数，那么当前的段数有可能会变多，变少或者不变。

当 $p$ 插入到这个位置的时候，由于没有影响到所有连续的段，所以段数就会变多。（情况 $1$）

由于 $p$ 插入的位置的右边（或者左边）有连续的段且连上了，那么段数就会不变。（情况 $2$）

$p$ 插入的位置左右两边都有段且都连上了，那么段数就会变少。（情况 $3$）

那么如何计算 $g[j]$ 的值的变化？

举个栗子：

假设现在插入 $p_{i+1}$，已经插入了 $p_1\sim p_n$。

如果有 $p_{i+1}=5$：

假设 $\sum_{j=1}^i [p_j=4]+\sum_{j=1}^i [p_j=6] = 0$，也就是前面已经插入的 $p_j$ 没有等于 $4$ 或者等于 $6$ 的（情况 $1$），那么就相当于是一个区间加操作。

假设 $\sum_{j=1}^i [p_j=4]>0$ 且当前仅当 $j = k$ 的时候满足 $p_k = 4$，且 $\sum_{j=1}^i[p_j=6]=0$，（情况 $2$ 的变种 $1$），$p_{k+1}\sim p_i$ 这一段不包含 $4$，也就是 $\sum_{j=k+1}^i [p_j=4]=0$，那么 $p_{k+1}\sim p_i$ 区间加入了 $p_{i+1}=5$，$k+1\sim i$ 这一段区间就是区间加法，而 $1\sim k$ 这一段由于和 $i+1$ 没有关系，所以这一段不变。

假设 $\sum_{j=1}^i [p_j=6]>0$ 且当前仅当 $j = k$ 的时候满足 $p_k = 6$，且 $\sum_{j=1}^i[p_j=4]=0$，（情况 $2$ 的变种 $2$），和变种 $1$ 一样。

假设 $\sum_{j=1}^i [p_j=4]>0$ 且 $\sum_{j=1}^i[p_j=6]>0$，（情况 $3$），容易发现是将最右边的那一段进行区间加法，最左边的那一段进行区间减法，中间的一段不变即可。（受到了情况 $2$ 的启发）。

容易发现，区间加法为区间 $+1$，区间减法为区间 $-1$。

但是时间复杂度仍然是 $O(n^2)$ 的。

容易发现可以使用一个线段树来维护。（毒瘤）

那么 ———— 如何维护段数 $\le 2$ 呢？

可以在线段树里维护一些东东：最小值，次小值，最小值出现的次数和次小值出现的次数。

其中次小值为区间里的严格次小值。

然后可以分类讨论：

最小值为 $1$，次小值为 $2$：答案为最小值出现的次数加上次小值出现的次数。

最小值 $\le 2$，次小值 $> 2$：答案为最小值出现的次数。

次小值 $>$ 最小值 $> 2$：由于最小值已经 $>2$ ，所以答案为 $0$。

到最后线段树统计答案即可。

时间复杂度为 $O(n\log n)$。

总结：需要维护一个区间最小值，区间次小值，区间最小值出现的次数和区间次小值出现的次数即可。

## $\texttt{Part 3: 代码}$

```cpp
// 我是写的最麻烦的了呜呜
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 3e5 + 10;

struct Node {
    int l, r, lazy;
    int min_value, minp_value;
    int min_count, minp_count;
    Node () {
        min_value = 0x3f3f3f3f3f3f3f3f;
        minp_value = 0x3f3f3f3f3f3f3f3f;
        min_count = 0, minp_count = 0;
    }
    void init(int p) {
        l = r = p;
        lazy = 0;
        min_count = 1;
        minp_count = 0;
        min_value = 0;
        minp_value = 0x3f3f3f3f3f3f3f3f;
    }
    void color(int p) {
        if (min_value <= 0x3f3f3f3f3f3f3f3f)
        min_value += p;
        if (minp_value <= 0x3f3f3f3f3f3f3f3f)
        minp_value += p;
        lazy += p;
    }
} z[N << 2];
int a[N], pos[N];

Node operator + (const Node &lhs, const Node &rhs) {
    Node res;
    res.l = lhs.l, res.r = rhs.r;
    res.lazy = 0;
    if (lhs.min_value < rhs.min_value) {
        res.min_value = lhs.min_value;
        res.min_count = lhs.min_count;
        if (lhs.minp_value < rhs.min_value) {
            res.minp_value = lhs.minp_value;
            res.minp_count = lhs.minp_count;
        }
        else if (lhs.minp_value == rhs.min_value) {
            res.minp_value = lhs.minp_value;
            res.minp_count = lhs.minp_count + rhs.min_count;
        }
        else {
            res.minp_value = rhs.min_value;
            res.minp_count = rhs.min_count;
        }
    }
    else if (lhs.min_value == rhs.min_value) {
        res.min_value = lhs.min_value;
        res.min_count = lhs.min_count + rhs.min_count;
        if (lhs.minp_value < rhs.minp_value) {
            res.minp_value = lhs.minp_value;
            res.minp_count = lhs.minp_count;
        }
        else if (lhs.minp_value > rhs.minp_value) {
            res.minp_value = rhs.minp_value;
            res.minp_count = rhs.minp_count;
        }
        else {
            res.minp_value = lhs.minp_value;
            res.minp_count = lhs.minp_count + rhs.minp_count;
        }
    }
    else {
        res.min_value = rhs.min_value;
        res.min_count = rhs.min_count;
        if (rhs.minp_value < lhs.min_value) {
            res.minp_value = rhs.minp_value;
            res.minp_count = rhs.minp_count;
        }
        else if (rhs.minp_value == lhs.min_value) {
            res.minp_value = rhs.minp_value;
            res.minp_count = rhs.minp_count + lhs.min_count;
        }
        else {
            res.minp_value = lhs.min_value;
            res.minp_count = lhs.min_count;
        }
    }
    return res;
}

void build(int l, int r, int rt) {
    if (l == r)
        z[rt].init(l);
    else {
        int mid = l + r >> 1;
        build(l, mid, rt << 1);
        build(mid + 1, r, rt << 1 | 1);
        z[rt] = z[rt << 1] + z[rt << 1 | 1];
    }
}

void push_lazy(int p) {
    if (z[p].lazy) {
        z[p << 1].color(z[p].lazy);
        z[p << 1 | 1].color(z[p].lazy);
        z[p].lazy = 0;
    }
}

void modify(int l, int r, int rt, int nowl, int nowr, int v) {
    if (nowl <= l && r <= nowr)
        z[rt].color(v);
    else {
        push_lazy(rt);
        int mid = l + r >> 1;
        if (nowl <= mid)
            modify(l, mid, rt << 1, nowl, nowr, v);
        if (mid < nowr)
            modify(mid + 1, r, rt << 1 | 1, nowl, nowr, v);
        z[rt] = z[rt << 1] + z[rt << 1 | 1];
    }
}

int query(int l, int r, int rt, int nowl, int nowr) {
    if (nowl <= l && r <= nowr) {
        int ans = 0;
        if (z[rt].min_value <= 2)
            ans += z[rt].min_count;
        if (z[rt].minp_value <= 2)
            ans += z[rt].minp_count;
        return ans;
    } else {
        push_lazy(rt);
        int mid = l + r >> 1;
        int ans = 0;
        if (nowl <= mid)
            ans += query(l, mid, rt << 1, nowl, nowr);
        if (mid < nowr)
            ans += query(mid + 1, r, rt << 1 | 1, nowl, nowr);
        return ans;
    }
}

signed main() {
    // freopen ("output.txt", "w", stdout);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i ++)
        cin >> a[i];
    for (int i = 1; i <= n; i ++)
        pos[a[i]] = i;
    build(1, n, 1);
    int ans = 0;
    for (int i = 1; i <= n; i ++) { // 枚举右端点
        modify(1, n, 1, 1, i, 1);
        if (a[pos[i] - 1] && a[pos[i] - 1] < i) {
            modify(1, n, 1, 1, a[pos[i] - 1], -1);
            // cout << i << " #1\n";
        }
        if (a[pos[i] + 1] && a[pos[i] + 1] < i) {
            modify(1, n, 1, 1, a[pos[i] + 1], -1);
            // cout << i << " #2\n";
        }
        ans += query(1, n, 1, 1, i);
        // cout << ans - i << '\n';
        // cout << "-----------------------------------------------\n";
        // cout << "i=" << i << " and ans=" << ans << '\n';
    }
    cout << ans - n << '\n';
    return 0;
}
```

## $\texttt{Part 4: 后记}$

十年 OI 一场空，不开 long long 见祖宗。

即将 NOI，祝大家 NOI2022 RP++。

~~最终也没能mj成AC喵，恼~~

---

## 作者：Elma_ (赞：1)

挺有意思的一道题。

问题等价于给一个 $[1,n]$ 的排列 $a$，问有多少个值域区间 $[l,r]$ 满足 $a$ 中所有值在 $[l,r]$ 之间的数所形成的区间个数小于等于 $2$。

暴力显然没有前途，我们考虑枚举 $r$，然后快速计算出以 $r$ 为右端点的合法值域区间个数。考虑 $l$ 从 $k + 1$ 变成 $k$ 对区间个数的影响，显然我们只需要考虑 $k$ 在 $a$ 中的位置：

- 如果 $k$ 左右两边的数都在 $[k,r]$ 范围内，那么 $k$ 的加入会导致区间个数减 $1$；
- 如果 $k$ 左右两边的数恰有一个在 $[k,r]$ 范围内，那么 $k$ 的加入对区间个数没有影响；
- 如果 $k$ 左右两边的数都不在 $[k,r]$ 范围内，那么 $k$ 的加入会导致区间个数加 $1$。

因此，在固定了 $r$ 的情况下，$l$ 从 $r$ 降到 $1$ 的过程中，区间个数的情况大致可以分为三段，每段中区间个数相同：

- 起初 $l$ 左右两边的数都不在 $[l,r]$ 范围内；
- 随着 $l$ 下降，当 $l$ 下降到 $r$ 左右元素中较大的一个时，$r$ 左右两边的数恰有一个在 $[l, r]$ 范围内；
- $l$ 继续下降，当 $l$ 下降到 $r$ 左右元素中较小的一个时，$r$ 左右两边的数都在 $[l,r]$ 范围内。

于是我们可以将 $[l,r]$ 对应的区间个数当做数列来处理，需要支持区间加，区间查询有多少个元素小于等于 $2$。好像并不好处理，但我们可以发现所有的元素一定都是正整数，因此小于等于 $2$ 的元素要么是最小值，要么是次小值。

用线段树维护最小值和最小值、次小值分别出现的次数即可。时间复杂度 $O(n \log n)$。

```cpp
#include <map>
#include <ctime>
#include <stack>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;
 
inline int read() {
	int x = 0, w = 1;char ch = getchar();
	while (ch > '9' || ch < '0') { if (ch == '-')w = -1;ch = getchar(); }
	while (ch >= '0' && ch <= '9')x = x * 10 + ch - '0', ch = getchar();
	return x * w;
}
inline void write(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
 
const int maxn = 3e5 + 5;
const int mod = 1e9 + 7;
const int inf = 1e9;
 
inline int min(int x, int y) { return x < y ? x : y; }
inline int max(int x, int y) { return x > y ? x : y; }

int n, ans, a[maxn], pos[maxn];

#define ls(x) x << 1
#define rs(x) x << 1 | 1
struct SGT {
    int tag[maxn << 2], cnt1[maxn << 2], cnt2[maxn << 2], minx[maxn << 2];
    inline void pushup(int x) {
        minx[x] = min(minx[ls(x)], minx[rs(x)]);
        cnt1[x] = cnt1[ls(x)] * (minx[x] == minx[ls(x)]) + cnt1[rs(x)] * (minx[x] == minx[rs(x)]);
        cnt2[x] = cnt2[ls(x)] * (minx[x] == minx[ls(x)]) + cnt1[ls(x)] * (minx[x] == minx[ls(x)] - 1);
        cnt2[x] += cnt2[rs(x)] * (minx[x] == minx[rs(x)]) + cnt1[rs(x)] * (minx[x] == minx[rs(x)] - 1);
    }
    inline void pushdown(int x) {
        if (tag[x]) {
            minx[ls(x)] += tag[x], minx[rs(x)] += tag[x];
            tag[ls(x)] += tag[x], tag[rs(x)] += tag[x];
            tag[x] = 0;
        }
    }
    inline void build(int x, int l, int r) {
        if (l == r) {
            cnt1[x] = 1;
            return;
        }
        int mid = (l + r) >> 1;
        build(ls(x), l, mid);
        build(rs(x), mid + 1, r);
        pushup(x);
    }
    inline void modify(int x, int l, int r, int L, int R, int k) {
        if (r < L || l > R) return;
        if (l >= L && r <= R) {
            tag[x] += k, minx[x] += k;
            return;
        }
        int mid = (l + r) >> 1; pushdown(x);
        modify(ls(x), l, mid, L, R, k);
        modify(rs(x), mid + 1, r, L, R, k);
        pushup(x);
    }
    inline int query(int x, int l, int r, int L, int R) {
        if (r < L || l > R) return 0;
        if (l >= L && r <= R) return cnt1[x] * (minx[x] <= 2) + cnt2[x] * (minx[x] <= 1);
        int mid = (l + r) >> 1; pushdown(x);
        return query(ls(x), l, mid, L, R) + query(rs(x), mid + 1, r, L, R);
    }
} T;
#undef ls(x)
#undef rs(x)

signed main(void) { 
    n = read();
    for (int i = 1;i <= n;i++) {
        a[i] = read(), pos[a[i]] = i;
    }
    T.build(1, 1, n);
    for (int i = 1;i <= n;i++) {
        T.modify(1, 1, n, 1, i, 1);
        if (a[pos[i] - 1] < i && a[pos[i] - 1]) T.modify(1, 1, n, 1, a[pos[i] - 1], -1);
        if (a[pos[i] + 1] < i && a[pos[i] + 1]) T.modify(1, 1, n, 1, a[pos[i] + 1], -1);
        ans += T.query(1, 1, n, 1, i - 1);
    }
    printf("%lld\n", ans);
    return 0; 
}
```


---

## 作者：chenxia25 (赞：1)

讲个笑话：tzc 告诉我 hb 给他们讲了 193B（\*2000），我看成了 193D（\*2900），然后还真自己做出来了（

---

首先有一个平方（或者带 log）级别的暴力：枚举组成的等差数列的左右端点，然后判是否可行。很有优化前途。

我们考虑一个套路的扫描线：枚举右端点，维护关于左端点的可行性序列。

考虑一对左右端点可行的充要条件。显然有，当且仅当它们组成 $\leq 2$ 个区间（连通块）。于是我们考虑维护关于左端点的连通块数量序列。考虑新加进一个 $r$ 会让 $l$ 们对应的连通块数量获得哪些变化。

这个其实不难。先考虑把 $r$ 令为一个单独的连通块整体 $+1$。然后考虑合并，显然对左边和右边能合并当且仅当它被 $[l,r-1]$ 包含。那么合并 $0,1,2$ 显然分别是区间。

那么问题就转化为了区间 $\pm 1$，区间数 $1,2$。这个东西我见过不止一遍了（最初的思路来自 rng，然而现在他 goodbye 了），所以秒掉了：考虑线段树的每个节点维护最小值、最小值出现次数、次小值、次小值出现次数，那么显然可上传可懒标记。查询的时候，由于如果有 $1,2$ 的话那么它们必定是最小值或者次小值，直接查就可以了。

所以说 *2900 应该是因为远古场的原因。但是有个细节：合并的时候有可能出现左儿子的次小值小于右儿子的最小值，分类讨论出错了，可以直接放进数组大力 `sort`。调死爷辣！

**_[code](https://www.luogu.com.cn/paste/er12viev)_**

---

## 作者：zhangxy__hp (赞：0)

首先将枚举原排列中的区间转化为枚举值域上的区间。

从小往大对 $r$ 扫描线，对于每个 $l\in[1,r)$ 维护将 $[l,r]$ 在原排列中最少要分成多少段。显然只有 $1$ 或 $2$ 段才会产生贡献。那么我们用线段树维护值域上的每个 $l$ 的最小段数，并维护值域区间上的最小值与最小值和最小值加一的数量。考虑加入 $p_i$，如何影响我们维护的值。首先对于 $l\in[1,p_i]$，要多出一段。如果 $p_{i-1}<p_i$，那么对于 $l\in[1,p_{i-1}]$，会减少一段。$p_{i+1}$ 同理。直接在线段树上区间修改即可。时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define il inline
#define lid id<<1
#define rid id<<1|1
using namespace std;
namespace asbt{
namespace cplx{bool begin;}
const int maxn=3e5+5;
int n,a[maxn],b[maxn],tag[maxn<<2];
struct node{
	int zhi,nm1,nm2;
	node(int zhi=0,int nm1=0,int nm2=0):zhi(zhi),nm1(nm1),nm2(nm2){}
	il node operator+(const node &x)const{
		node res(min(zhi,x.zhi));
		if(res.zhi==zhi){
			res.nm1+=nm1;
			res.nm2+=nm2;
		}
		else if(res.zhi+1==zhi){
			res.nm2+=nm1;
		}
		if(res.zhi==x.zhi){
			res.nm1+=x.nm1;
			res.nm2+=x.nm2;
		}
		else if(res.zhi+1==x.zhi){
			res.nm2+=x.nm1;
		}
		return res;
	}
}tr[maxn<<2];
#define zhi(id) tr[id].zhi
#define nm1(id) tr[id].nm1
#define nm2(id) tr[id].nm2
il void pushup(int id){
	tr[id]=tr[lid]+tr[rid];
}
il void pushtag(int id,int v){
	tag[id]+=v,zhi(id)+=v;
}
il void pushdown(int id){
	if(tag[id]){
		pushtag(lid,tag[id]);
		pushtag(rid,tag[id]);
		tag[id]=0;
	}
}
il void build(int id,int l,int r){
	if(l==r){
		nm1(id)=1;
		return ;
	}
	int mid=(l+r)>>1;
	build(lid,l,mid);
	build(rid,mid+1,r);
	pushup(id);
}
il void add(int id,int L,int R,int l,int r,int v){
	if(l>r){
		return ;
	}
	if(L>=l&&R<=r){
		pushtag(id,v);
		return ;
	}
	pushdown(id);
	int mid=(L+R)>>1;
	if(l<=mid){
		add(lid,L,mid,l,r,v);
	}
	if(r>mid){
		add(rid,mid+1,R,l,r,v);
	}
	pushup(id);
}
il int query(int id,int L,int R,int l,int r){
	if(l>r){
		return 0;
	}
	if(L>=l&&R<=r){
		int res=0;
		if(zhi(id)<=2){
			res+=nm1(id);
		}
		if(zhi(id)<=1){
			res+=nm2(id);
		}
		return res;
	}
	pushdown(id);
	int mid=(L+R)>>1,res=0;
	if(l<=mid){
		res+=query(lid,L,mid,l,r);
	}
	if(r>mid){
		res+=query(rid,mid+1,R,l,r);
	}
	return res;
}
#undef zhi
#undef nm1
#undef nm2
namespace cplx{
	bool end;
	il double usdmem(){return (&begin-&end)/1048576.0;}
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[a[i]]=i;
	}
	ll ans=0;
	build(1,1,n);
	for(int i=1;i<=n;i++){
		add(1,1,n,1,i,1);
		if(a[b[i]-1]<i){
			add(1,1,n,1,a[b[i]-1],-1);
		}
		if(a[b[i]+1]<i){
			add(1,1,n,1,a[b[i]+1],-1);
		}
		ans+=query(1,1,n,1,i-1);
	}
	cout<<ans;
	return 0;
}
}
int main(){return asbt::main();}
```

---

## 作者：toolong114514 (赞：0)

2025 年/回归文化课后第一篇题解。
## 解题思路
注意到公差为 $1$ 的等差数列就是一段连续的整数区间。

那么有两种思路：枚举原序列上这两个区间、枚举只有一段的连续整数区间（值域）。后一种显然更有前途。

考虑从小到大枚举值域区间的右端点，并维护对于当前的右端点，每一个左端点构成的值域区间，在映射到原序列上能划分的最小段数（简称划分段数），查找段数 $\le2$ 的值域区间（由于长度为 $1$ 的区间显然不是答案之一，所以所有在原序列上是一整段的值域区间一定能划分成两段）。

枚举右端点已经是 $O(n)$ 的了，不能每次再用 $O(n)$ 的时间暴力维护，要考虑从上一个右端点推出来。

记当前的右端点为 $i$，其在原序列的位置为 $p_i$。

我们假设对于所有值域区间，新加入的这一点与它在原序列上映射的区间全部不相邻，所以先给所有的值域区间的划分段数 $+1$。

注意到对于区间 $[1,i],[2,i],\dots,[a_{p_i-1},i]$，位置 $p_i$ 与它们的一段划分区间相邻，所以要给左端点在 $[1,a_{p_i-1}]$ 的区间的划分段数减去 $1$。修改应在 $a_{p_i-1}<i$ 时进行，否则违反关于区间的定义。

注意到对于区间 $[1,i],[2,i],\dots,[a_{p_i+1},i]$，位置 $p_i$ 与它们的一段划分区间相邻（如果区间同时满足上面的情况，那么这种情况下的相邻区间和上面的不同），所以要给左端点在 $[1,a_{p_i+1}]$ 的区间的划分段数减去 $1$。修改应在 $a_{p_i+1}<i$ 时进行，否则违反关于区间的定义。

还注意到只有划分段数 $\le2$ 的区间要被考虑，总体上只可能是最小值和次小值，那么可以直接使用线段树维护值域区间左端点区间的划分段数最小值及其计数、次小值及其计数，用时查询即可。

时间复杂度 $O(n\log{n})$，可以通过本题。
## 参考代码

```cpp
#include<algorithm>
#include<iostream>
using namespace std;
#define int long long
const int N=3e5+10;
struct ccf{
	int l,r,laz,min1,min2,cnt1,cnt2;
}tree[4*N];
void build(int pos,int lft,int rgt){
	tree[pos].l=lft;
	tree[pos].r=rgt;
	tree[pos].min2=N;
	tree[pos].cnt1=rgt-lft+1;
	if(lft==rgt) return;
	int mid=(lft+rgt)/2;
	build(pos*2,lft,mid);
	build(pos*2+1,mid+1,rgt);
}
void push_up(int pos){
	tree[pos].cnt1=tree[pos].cnt2=0;
	tree[pos].min2=N;
	tree[pos].min1=min(tree[pos*2].min1,tree[pos*2+1].min1);
	if(tree[pos].min1==tree[pos*2].min1) tree[pos].cnt1+=tree[pos*2].cnt1;
	else tree[pos].min2=min(tree[pos].min2,tree[pos*2].min1);
	if(tree[pos].min1==tree[pos*2+1].min1) tree[pos].cnt1+=tree[pos*2+1].cnt1;
	else tree[pos].min2=min(tree[pos].min2,tree[pos*2+1].min1);
	tree[pos].min2=min(tree[pos].min2,min(tree[pos*2].min2,tree[pos*2+1].min2));
	if(tree[pos].min2==tree[pos*2].min1) tree[pos].cnt2+=tree[pos*2].cnt1;
	if(tree[pos].min2==tree[pos*2+1].min1) tree[pos].cnt2+=tree[pos*2+1].cnt1;
	if(tree[pos].min2==tree[pos*2].min2) tree[pos].cnt2+=tree[pos*2].cnt2;
	if(tree[pos].min2==tree[pos*2+1].min2) tree[pos].cnt2+=tree[pos*2+1].cnt2;
}
void push_down(int pos){
	tree[pos*2].min1+=tree[pos].laz,tree[pos*2].min2+=tree[pos].laz;
	tree[pos*2+1].min1+=tree[pos].laz,tree[pos*2+1].min2+=tree[pos].laz;
	tree[pos*2].laz+=tree[pos].laz,tree[pos*2+1].laz+=tree[pos].laz;
	tree[pos].laz=0; 
}
void upd(int pos,int lft,int rgt,int x){
	if(lft>rgt||tree[pos].r<lft||rgt<tree[pos].l) return;
	if(lft<=tree[pos].l&&tree[pos].r<=rgt){
		tree[pos].min1+=x,tree[pos].min2+=x,tree[pos].laz+=x;
		return;
	}
	push_down(pos);
	upd(pos*2,lft,rgt,x);
	upd(pos*2+1,lft,rgt,x);
	push_up(pos);
}
int ask(int pos,int lft,int rgt){
	if(tree[pos].r<lft||rgt<tree[pos].l) return 0;
	if(lft<=tree[pos].l&&tree[pos].r<=rgt){
		int tmp=0;
		if(tree[pos].min1<=2) tmp+=tree[pos].cnt1;
		if(tree[pos].min2<=2) tmp+=tree[pos].cnt2;
		return tmp;
	}
	push_down(pos);
	return ask(pos*2,lft,rgt)+ask(pos*2+1,lft,rgt);
}
int a[N],b[N];
int n,ans;
signed main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[a[i]]=i;
	}
	build(1,1,n);
	for(int i=1;i<=n;i++){
		int ll=b[i]-1,rr=b[i]+1;
		upd(1,1,i,1);
		if(a[ll]<i) upd(1,1,a[ll],-1);
		if(a[rr]<i) upd(1,1,a[rr],-1);
		ans+=ask(1,1,i-1);
	}
	cout<<ans;
	return 0;
}
```
[CF 通过记录](https://codeforces.com/problemset/submission/193/301660649)

Written by [toolong114514](https://www.luogu.com/user/477821) on 2025/1/19.

---

## 作者：Laoshan_PLUS (赞：0)

## [[CF193D] Two Segments](https://www.luogu.com.cn/problem/CF193D)

线段树维护值域区间。

一般对于这种 “公差为 $1$ 的等差数列”，就应该想到化枚举区间为**枚举值域区间**。于是问题转化为在连续的一段值域上，这些值域组成的连续段 $\le2$ 的方案数。（注意是小于等于 $2$，因为等于 $1$ 说明剩下的一部分也是等差数列。处理算重问题会讲。）

对于这种区间问题，一般来说是一个一个 “加入”，然后统计答案。关键在于，我们需要维护每个加入点对总区间数的影响。如果加入的这个 $i$ **在原来序列中的位置**：

- 左右两边的数都比 $i$ 小，也就是它们原本都是在 $[1,i]$ 之内的，这时 $i$ 的加入相当于连接了原本的两个区间，会使得区间个数 $-1$；
- 左右两边的数一个比 $i$ 大、一个比 $i$ 小，相当于扩展了原区间，则区间个数不变；
- 都比 $i$ 大，相当于用原本的一个区间一次扩展了两个区间，区间个数 $+1$。

具体实现上来说，我们按照 $1\sim n$ 枚举值域右端点，每次枚举到一个新的 $i$ 时，先假设当前点需要再分一块连续段，于是 $\operatorname{mdf}(1,i,1)$。然后依次判断 $i$ 在原序列位置左右两端的数，有一个小于就 $\operatorname{mdf}(1,a[p_i-1],-1)$ 或 $\operatorname{mdf}(1,a[p_i+1],-1)$。最后统计的是 $\sum\operatorname{query}(1,i-1)$。

为什么是 $i-1$ 呢，因为 $i-1$ 是你**保证完全处理好的**，如果查 $\operatorname{query}(1,i)$ 则不确定 $i$ 是否还会被 $i+1$ 更新，所以每一次查询上一位。不能查询 $\operatorname{query}(1,n)$，因为 $1\sim n$ 无非是从中间任劈两半，而这些情况我们之前都算过了。

以上，就是我对这道题、对线段树维护区间的浅薄理解。

```cpp
#define lp p<<1
#define rp p<<1|1
using ll=long long;
constexpr int MAXN=3e5+5;
int n,a[MAXN],p[MAXN];
ll ans;
struct{
	ll mn,lazy,tm,ctm;
}st[MAXN<<2];
ll min(ll a,ll b){
	return a<b?a:b;
}
void pushup(int p){
	st[p].mn=min(st[lp].mn,st[rp].mn);
	st[p].tm=st[lp].tm*(st[lp].mn==st[p].mn)+st[rp].tm*(st[rp].mn==st[p].mn);
	st[p].ctm=st[lp].ctm*(st[lp].mn==st[p].mn)+st[lp].tm*(st[lp].mn==st[p].mn+1)+st[rp].ctm*(st[rp].mn==st[p].mn)+st[rp].tm*(st[rp].mn==st[p].mn+1);
}
void build(int s,int t,int p){
	if(s==t) return st[p].tm=1,void();
	int mid=(s+t)>>1;
	build(s,mid,lp),build(mid+1,t,rp);
	pushup(p);
}
void pushdown(int p){
	if(!st[p].lazy) return;
	st[lp].mn+=st[p].lazy;
	st[lp].lazy+=st[p].lazy;
	st[rp].mn+=st[p].lazy;
	st[rp].lazy+=st[p].lazy;
	st[p].lazy=0;
}
void mdf(int l,int r,ll k,int s=1,int t=n,int p=1){
	if(l>t||s>r) return;
	if(l<=s&&t<=r) return st[p].mn+=k,st[p].lazy+=k,void();
	pushdown(p);
	int mid=(s+t)>>1;
	mdf(l,r,k,s,mid,lp),mdf(l,r,k,mid+1,t,rp);
	pushup(p);
}
int sum(int l,int r,int s=1,int t=n,int p=1){
	if(l>t||s>r) return 0;
	if(l<=s&&t<=r) return st[p].tm*(st[p].mn<=2)+st[p].ctm*(st[p].mn<=1);
	pushdown(p);
	int mid=(s+t)>>1;
	return sum(l,r,s,mid,lp)+sum(l,r,mid+1,t,rp);
}

int main(){
	n=read();
	for(int i=1;i<=n;++i) a[i]=read(),p[a[i]]=i;
	build(1,n,1);
	for(int i=1;i<=n;++i){
		mdf(1,i,1);
		if(a[p[i]-1]<i&&a[p[i]-1]) mdf(1,a[p[i]-1],-1);
		if(a[p[i]+1]<i&&a[p[i]+1]) mdf(1,a[p[i]+1],-1);
		ans+=sum(1,i-1);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Cx114514 (赞：0)

### 题目链接：[Two Segments](https://codeforces.com/contest/193/problem/D)
由于位置不连续，且容易算重，所以考虑值域。问题转化为了在连续的一段值域上，位置组成的连续段 $\le 2$ 的方案数。

考虑连续段怎么维护：

从左到右扫整个序列，开一个线段树实时维护，以当前节点为右端点，左端点所在的区间形成的连续段的最小值、次小值及出现次数（最小值 $1$，次小值 $2$）。

假设我们当前扫到的右端点为 $r$，先假设它单独形成一段，将 $\left[1,r\right]+1$。接下来考虑它与 $a_{r-1}$ 合并的情况。设 $a_{r-1}$ 所在的位置为 $p1$，若 $p1\le r$，则将 $\left[1,p1\right]-1$；它与 $a_{r+1}$ 合并的情况同理。

时间复杂度 $O\left(n\log n\right)$。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int read()
{
	int f = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') f = -1;
		c = getchar();
	}
	int x = 0;
	while (isdigit(c))
	{
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * f;
}

int buf[15];

void write(int x)
{
	int p = 0;
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	if (x == 0) putchar('0');
	else
	{
		while (x)
		{
			buf[++p] = x % 10;
			x /= 10;
		}
		for (int i = p; i >= 1; i--)
			putchar('0' + buf[i]);
	}
}

int n, ans, a[300005], p[300005], tag[1200005];

struct node
{
	int min1, min2, cnt1, cnt2;
} tree[1200005];

struct node2
{
	int val, cnt;
} t[5];

bool cmp(node2 q, node2 p)
{
	return q.val < p.val;
}

void build(int rt, int l, int r)
{
	tree[rt] = {0, 1145141919, r - l + 1, 0};
	if (l == r) return;
	int mid = (l + r) / 2;
	build(rt * 2, l, mid);
	build(rt * 2 + 1, mid + 1, r);
}

void update(int rt, int l, int r, int tl, int tr, int x)
{
	if (tl <= l && r <= tr)
	{
		tree[rt].min1 += x;
		tree[rt].min2 += x;
		tag[rt] += x;
	}
	else
	{
		int mid = (l + r) / 2;
		if (tag[rt])
		{
			tree[rt * 2].min1 += tag[rt];
			tree[rt * 2].min2 += tag[rt];
			tag[rt * 2] += tag[rt];
			tree[rt * 2 + 1].min1 += tag[rt];
			tree[rt * 2 + 1].min2 += tag[rt];
			tag[rt * 2 + 1] += tag[rt];
			tag[rt] = 0;
		}
		if (tl <= mid) update(rt * 2, l, mid, tl, tr, x);
		if (tr > mid) update(rt * 2 + 1, mid + 1, r, tl, tr, x);
		t[1].val = tree[rt * 2].min1;
		t[2].val = tree[rt * 2].min2;
		t[3].val = tree[rt * 2 + 1].min1;
		t[4].val = tree[rt * 2 + 1].min2;
		t[1].cnt = tree[rt * 2].cnt1;
		t[2].cnt = tree[rt * 2].cnt2;
		t[3].cnt = tree[rt * 2 + 1].cnt1;
		t[4].cnt = tree[rt * 2 + 1].cnt2;
		sort(t + 1, t + 5, cmp);
		int tot = t[1].cnt;
		for (int i = 1; i < 4; i++)
			if (t[i].val == t[i + 1].val) 
			{
				t[i + 1].cnt += t[i].cnt;
				t[i].val = 1145141919;	
				t[i].cnt = 0;
			}
		sort(t + 1, t + 5, cmp);
		tree[rt].min1 = t[1].val;
		tree[rt].min2 = t[2].val;
		tree[rt].cnt1 = t[1].cnt;
		tree[rt].cnt2 = t[2].cnt;
	}
}

node query(int rt, int l, int r, int tl, int tr)
{
	if (tl <= l && r <= tr) return tree[rt];
	int mid = (l + r) / 2;
	if (tag[rt])
	{
		tree[rt * 2].min1 += tag[rt];
		tree[rt * 2].min2 += tag[rt];
		tag[rt * 2] += tag[rt];
		tree[rt * 2 + 1].min1 += tag[rt];
		tree[rt * 2 + 1].min2 += tag[rt];
		tag[rt * 2 + 1] += tag[rt];
		tag[rt] = 0;
	}
	if (tr <= mid) return query(rt * 2, l, mid, tl, tr);
	if (tl > mid) return query(rt * 2 + 1, mid + 1, r, tl, tr);
	node A = query(rt * 2, l, mid, tl, tr), B = query(rt * 2 + 1, mid + 1, r, tl, tr), C;
	t[1].val = A.min1;
	t[2].val = A.min2;
	t[3].val = B.min1;
	t[4].val = B.min2;
	t[1].cnt = A.cnt1;
	t[2].cnt = A.cnt2;
	t[3].cnt = B.cnt1;
	t[4].cnt = B.cnt2;
	sort(t + 1, t + 5, cmp);
	int tot = t[1].cnt;
	for (int i = 1; i < 4; i++)
		if (t[i].val == t[i + 1].val) 
		{
			t[i + 1].cnt += t[i].cnt;
			t[i].val = 1145141919;	
			t[i].cnt = 0;
		}
	sort(t + 1, t + 5, cmp);
	C.min1 = t[1].val;
	C.min2 = t[2].val;
	C.cnt1 = t[1].cnt;
	C.cnt2 = t[2].cnt;
	return C;
}

signed main()
{
	n = read();
	for (int i = 1; i <= n; i++)	
		a[i] = read();
	for (int i = 1; i <= n; i++)
		p[a[i]] = i;
	build(1, 1, n);
	for (int i = 1; i <= n; i++)
	{
		update(1, 1, n, 1, i, 1);
		if (p[i] != 1 && a[p[i] - 1] <= i) update(1, 1, n, 1, a[p[i] - 1], -1);
		if (p[i] != n && a[p[i] + 1] <= i) update(1, 1, n, 1, a[p[i] + 1], -1);
		if (i != 1)
		{
			node x = query(1, 1, n, 1, i - 1);
			if (x.min1 <= 2) ans += x.cnt1;
			if (x.min2 <= 2) ans += x.cnt2;
		}
	}
	write(ans);
	putchar('\n');
	return 0;
}
```

---

## 作者：tzc_wk (赞：0)

[Codeforces 题目传送门](https://codeforces.com/contest/193/problem/D) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF193D)

~~感觉这个 *2900 并不难啊，为什么我没想出来呢 awa~~

~~顺便膜拜 ycx 一眼秒掉此题 %%%~~

首先碰到这类题有两种思路，一是枚举两个区间，显然这个思路是不可行的，因为这个思路有四个自由变量 $l_1,r_1,l_2,r_2$，并且还会出现重复计算的情况，非常棘手。二是注意到 $[l_1,r_1]\cup[l_2,r_2]$ 是一段连续的区间，故考虑枚举这段区间值域的左右端点 $[l,r]$，我们只需统计有多少个区间 $[l,r]$ 满足值在 $[l,r]$ 中的数组成连续段的个数 $\le 2$ 即可。

我们考虑记录 $f(l,r)$ 表示值在 $[l,r]$ 中的数组成连续段的个数，$S(l,r)$ 表示 $a_p\in[l,r]$ 的 $p$ 组成的集合。考虑动态枚举 $r$，建一棵线段树，下标为 $l$ 的位置实时维护 $[l,r]$ 的个数。考虑右端点从 $r$ 移到 $r-1$ 会对 $f(l,r)$ 的值产生什么影响，假设 $a_p=r$，首先显然 $\forall l\le r$，$p\in S(l,r)$，故我们先假设 $p$ 单独一段，即令 $[1,r]$ 的值加 $1$。其次如果 $a_{p-1}<r$，那么对于 $\forall l\le a_{p-1}$，$p,p-1$ 必定都属于 $S(l,r)$，因此我们可以将它们合并起来，$f(l,r)$ 的值减 $1$，$a_{p+1}$ 也同理。以上操作都可以通过线段树区间加在 $\mathcal O(\log n)$ 的时间内搞定。

最后考虑怎样统计答案，显然对于固定的右端点 $r$，符合条件的 $l$ 个数即为满足 $l\in[1,r],f(l,r)\le 2$ 的 $l$ 个数。直接统计是比较麻烦的，不过这里有一个我见过 N 次的套路，显然 $\forall l\le r,f(l,r)>0$，因此区间 $[1,r]$ 中最小值 $\ge 1$，次小值 $\ge 2$，故我们只需维护最小值、最小值个数、次小值、次小值个数，查询时访问对应区间，如果最小值 $\le 2$ 答案加上最小值个数，如果次小值 $\le 2$ 答案加上次小值个数。节点合并就将左右儿子的最小值、次小值放到一个长度为 $4$ 的数组里排个序乱搞搞即可。

时间复杂度 $\mathcal O(n\log n)$。

```cpp
const int MAXN=3e5;
const int INF=0x3f3f3f3f;
int n,p[MAXN+5],pos[MAXN+5];
struct node{int l,r,lz;pii fst,snd;} s[MAXN*4+5];
void pushup(int k){
	static pii p[4];
	p[0]=s[k<<1].fst;p[1]=s[k<<1].snd;
	p[2]=s[k<<1|1].fst;p[3]=s[k<<1|1].snd;
	sort(p,p+4);s[k].fst=mp(p[0].fi,0);int cur=0;
	while(p[cur].fi==p[0].fi) s[k].fst.se+=p[cur].se,cur++;
	s[k].snd=mp(p[cur].fi,0);
	while(p[cur].fi==s[k].snd.fi) s[k].snd.se+=p[cur].se,cur++;
}
void build(int k,int l,int r){
	s[k].l=l;s[k].r=r;if(l==r){s[k].fst=mp(0,1);s[k].snd=mp(INF,0);return;}
	int mid=l+r>>1;build(k<<1,l,mid);build(k<<1|1,mid+1,r);pushup(k);
}
void pushdown(int k){
	if(s[k].lz){
		s[k<<1].fst.fi+=s[k].lz;s[k<<1].snd.fi+=s[k].lz;s[k<<1].lz+=s[k].lz;
		s[k<<1|1].fst.fi+=s[k].lz;s[k<<1|1].snd.fi+=s[k].lz;s[k<<1|1].lz+=s[k].lz;
		s[k].lz=0;
	}
}
void modify(int k,int l,int r,int x){
	if(l<=s[k].l&&s[k].r<=r){
		s[k].fst.fi+=x;s[k].snd.fi+=x;s[k].lz+=x;
		return;
	} pushdown(k);int mid=s[k].l+s[k].r>>1;
	if(r<=mid) modify(k<<1,l,r,x);
	else if(l>mid) modify(k<<1|1,l,r,x);
	else modify(k<<1,l,mid,x),modify(k<<1|1,mid+1,r,x);
	pushup(k);
}
int query(int k,int l,int r){
	if(l<=s[k].l&&s[k].r<=r){
		int ret=0;
		if(s[k].fst.fi<=2) ret+=s[k].fst.se;
		if(s[k].snd.fi<=2) ret+=s[k].snd.se;
		return ret; 
	} pushdown(k);int mid=s[k].l+s[k].r>>1;
	if(r<=mid) return query(k<<1,l,r);
	else if(l>mid) return query(k<<1|1,l,r);
	else return query(k<<1,l,mid)+query(k<<1|1,mid+1,r);
}
int main(){
	scanf("%d",&n);ll ans=0;build(1,1,n);
	for(int i=1;i<=n;i++) scanf("%d",&p[i]),pos[p[i]]=i;
	for(int i=1;i<=n;i++){
		modify(1,1,i,1);
		if(pos[i]!=1&&p[pos[i]-1]<i) modify(1,1,p[pos[i]-1],-1);
		if(pos[i]!=n&&p[pos[i]+1]<i) modify(1,1,p[pos[i]+1],-1);
		if(i!=1) ans+=query(1,1,i-1);
	} printf("%lld\n",ans);
	return 0;
}
```



---

