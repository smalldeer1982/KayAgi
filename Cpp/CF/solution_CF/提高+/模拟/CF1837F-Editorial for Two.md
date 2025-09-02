# Editorial for Two

## 题目描述

Berland Intercollegiate Contest has just finished. Monocarp and Polycarp, as the jury, are going to conduct an editorial. Unfortunately, the time is limited, since they have to finish before the closing ceremony.

There were $ n $ problems in the contest. The problems are numbered from $ 1 $ to $ n $ . The editorial for the $ i $ -th problem takes $ a_i $ minutes. Monocarp and Polycarp are going to conduct an editorial for exactly $ k $ of the problems.

The editorial goes as follows. They have a full problemset of $ n $ problems before them, in order. They remove $ n - k $ problems without changing the order of the remaining $ k $ problems. Then, Monocarp takes some prefix of these $ k $ problems (possibly, an empty one or all problems). Polycarp takes the remaining suffix of them. After that, they go to different rooms and conduct editorials for their problems in parallel. So, the editorial takes as much time as the longer of these two does.

Please, help Monocarp and Polycarp to choose the problems and the split in such a way that the editorial finishes as early as possible. Print the duration of the editorial.

## 样例 #1

### 输入

```
6
5 4
1 10 1 1 1
5 3
1 20 5 15 3
5 3
1 20 3 15 5
10 6
10 8 20 14 3 8 6 4 16 11
10 5
9 9 2 13 15 19 4 9 13 12
1 1
1```

### 输出

```
2
6
5
21
18
1```

# 题解

## 作者：封禁用户 (赞：7)


> Um\_nik teaches us to use binary search.

单调性显然。两个老六一共选 $k$ 个，不就是你少我多么，感性理解。

## How to check?

一种简单的思路是枚举分割点，前后各扫一下，贪心的记录前 $i$ 个元素在合法条件下的最多能拿多少个数字，再进行匹配，看是否有任意一组可行解大于 $k$ 即可。具体实现看代码。

用堆实现其实很方便，``size()`` 统计当前能拿多少数字，``top()`` 更新当前解等等。然后本题的难点是在开 ``long long``。

复杂度 $O(n \log^2 n)$。

~~但是这真的是 F 题吗？出题人没卡这种做法啊。~~

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn = 3e5 + 5;
#define int long long
int q, n, k;
int ans;
int a[maxn];
int l, r;
#define pq priority_queue

bool check(int mid) {
	pq<int> q;
	int need[maxn];
	int sum = 0;
	for (int i = 1; i <= n; ++i) {
		q.push(a[i]);
		sum += a[i];
		for (; (sum > mid);) sum -= q.top(),q.pop(); 
		need[i] = q.size();
	}sum = 0;
	while (!q.empty()) q.pop();
	for (int i = n; i > 0; i--) {
		q.push(a[i]);
		sum += a[i];
		for (; (sum > mid);) sum -= q.top(),q.pop();
		if (q.size() + need[i - 1] >= k)  //need[i-1] 注意边界
			return 1;
	}return 0;
}

signed main() {
	qin >> q;
	while (q--) {
		l = 0;
		r = 0;
		qin >> n >> k;
		for (int i = 1; i <= n; i++) {
			qin >> a[i];
			r += a[i];
		}
		while (l <= r) {
			int mid_qwq = (l + r) >> 1;
			if (check(mid)) {
				r = mid - 1;
				ans = mid;
			} ele_QWQ {
				l = mid + 1;
			}
		}
		qout << ans << '\n';
	}
}
```

---

## 作者：Little09 (赞：6)

首先有个简单的双 $\log$ 做法：先二分答案，然后枚举分段点，前后都尽可能选小的，比较个数和 $k$ 的大小，用堆维护即可。

两 $\log$ 看起来太蠢了，跑起来还巨慢，能不能优化一下呢？感觉上二分去不掉，考虑能不能把堆去掉。我们用堆其实维护了这么个事情：

- 加入一个元素；
- 弹出最大的元素。

同时我们要做 $\log A$ 轮这个事情，并且每轮加入元素的顺序是一样的。这启示我们对每个元素 $a_i$ 预处理一次，找到它加入后会在哪个元素前面（也就是找到最大的 $a_j$ 满足 $j<i$ 且 $a_j\le a_i$），这样就可以用双向链表维护这个事情了。也就是用双向链表时刻维护有序的结构。

这样做会有个问题，就是如果你发现你应该加在 $x$ 前面，但是此时 $x$ 已被删除，怎么办？注意到这题中，如果 $x$ 被删除，说明 $x$ 及以上的元素都是无效的。所以这种情况我们直接不加入这个元素即可。

瓶颈在二分答案，复杂度 $O(n\log A)$。

---

## 作者：541forever (赞：4)

看到题解区全是基于二分的双 $\log$ 做法似乎还需要卡常，这里提供一篇不需卡常的单 $\log$ 做法。

首先，本题有个贪心的思想就是你会让前缀和后缀的和进尽可能接近，那么，我们可以考虑枚举一个分界点 $i$，在枚举左边选了 $x$ 个，则右边选了 $k-x$ 个，则以 $i$ 为分界点的答案最优为左半边最小的 $x$ 个数的和与右半边最小的 $k-x$ 个数的和的最大值最小的时候。接下来，我们又可以发现，当分界点向右移动时，最优的左半边选的数的个数一定是不降的，右半边选的数的个数一定是不升的。于是用两个单调的指针维护左半边和右半边取的个数，查询可以考虑将 $a$ 离散后在权值线段树上二分。

[Code](https://codeforces.com/contest/1837/submission/207725104)

---

## 作者：Reunite (赞：2)

## 一
---
   一眼经典题。
   - 首先考虑单调性问题，显然我们希望让两者的和都尽量接近，单调性显然。套路地考虑二分答案。
   
   - 考虑二分什么值，二分选的数量的话，是没有理由和前途的，我们考虑就二分最终的答案。
   
   - 怎么快速判断二分的值是否可行呢？我们首先以 $O(n)$ 的时间代价枚举端点。由于二分的 $mid$ 为前后两段和的最大值，那么问题就转化为：    能否在前后两段选择出 $\geq k$ 个数，使每一段的和的最大值都 $\leq mid$。
   
   - 似乎还是不怎么好处理？这里可以贪心的考虑。我们尽量选出较小的元素，这样就能让选出来的数量尽可能多了，选的数量越多，就越有可能满足总数 $\geq k$ 的约束条件。贪心的正确性显然。
   
## 二
---
   实现也很简单，用优先队列就可以 $O(\log)$ 找出到了前（或后）位置 $i$ 时，所有选择的元素和 $\leq mid$ 最多能选多少元素。
   
   这应该不是正解，因为有些卡常。可能需要吸氧。
   
   总时间复杂度有两只 $\log$，要注意常数。
   
代码：
```cpp

#pragma GCC optimize("O2")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define ll long long
using namespace std;

int t,n,k,m;
int a[300005];
int f[300005];
int ff[300005];
priority_queue <int> q;

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

inline bool check(ll mid){
	ll s=0;
	while(!q.empty()) q.pop();
	for(int i=1;i<=n;i++){
		s+=a[i];
		q.push(a[i]);
		f[i]=f[i-1]+1;
		if(s>mid) f[i]--,s-=q.top(),q.pop();
	}
	ff[n+1]=0;
	while(!q.empty()) q.pop();
	s=0;
	for(int i=n;i>=1;i--){
		s+=a[i];
		q.push(a[i]);
		ff[i]=ff[i+1]+1;
		if(s>mid) ff[i]--,s-=q.top(),q.pop();
	}
	for(int i=0;i<n;i++) if(f[i]+ff[i+1]>=k) return true;
	return false;
}

int main(){
	in(t);
	while(t--){
		in(n),in(k);
		for(int i=1;i<=n;i++) in(a[i]);
		ll l=1,r=1e18,mid;
		while(l<=r){
			mid=l+r>>1;
			if(check(mid)) r=mid-1;
			else l=mid+1;
		}
		printf("%lld\n",l);
	}
	
	return 0;
} 

```

---

## 作者：离散小波变换° (赞：2)

赛时被卡麻了。

## 题解

题面可以转化为从原数列里选出一个大小为 $k$ 的子序列 $M$，接着将这个子序列分为两段 $M=A+B$，最小化 $\max\{\operatorname{sum} A,\operatorname{sum} B\}$ 的值。其中 $\operatorname{sum} M$ 表示 $M$ 中的元素之和。

那么我们枚举 $A$ 里面的元素的下标的最大值 $i$。那么 $A$ 里的元素的下标肯定在 $[1,i]$ 内，$B$ 里的元素的下标肯定在 $[i+1,n]$ 内。接着我们需要贪心地去选择 $k$ 个元素，假设在 $A$ 中选择了 $k_1$ 个，那一定要选择 $A$ 当中前 $k_1$ 小的元素；在 $B$ 中选择了 $k_2=k-k_1$ 个，一定要选择 $B$ 当中前 $k_2$ 小的元素。

接着发现，随着 $k_1$ 的增大，$\operatorname{sum} A$ 会单调增大，$\operatorname{sum} B$ 会单调减小。因为我们要最小化 $\max\{\operatorname{sum} A,\operatorname{sum} B\}$，所以总是可以二分出这样的 $k_1=x$，使得 $\operatorname{sum} A\le \operatorname{sum} B$，最优的 $k_1$ 的值肯定是 $x$ 或者 $x+1$。

那么我们需要这样一个数据结构来动态维护 $A,B$，它支持以下功能：

- 插入一个元素 $x$；
- 删除一个元素 $x$；
- 查询前 $k$ 小的元素之和。

容易使用平衡树实现，复杂度为 $\mathcal O(n\log^2 n)$。如果常数太大就会像我这样 fhqTreap 写了一年卡半天常数遗憾退场。赛后我写了个替罪羊树。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l, r, i) for(int i = l, END##i = r;i <= END##i;++ i)
#define dn(r, l, i) for(int i = r, END##i = l;i >= END##i;-- i)
using namespace std;
typedef long long i64;
const int INF = 2147483647;
typedef unsigned int       u32;
typedef unsigned long long u64;
namespace SCT{
    const double alpha = 0.8;
    const int SIZ = 6e5 + 3;
    int L[SIZ], R[SIZ], C[SIZ], S[SIZ], H[SIZ], W[SIZ];
    int size; i64 X[SIZ];
    void pushup(int t){
        S[t] = S[L[t]] + S[R[t]] + C[t];
        X[t] = X[L[t]] + X[R[t]] + 1ll * C[t] * W[t];
        H[t] = H[L[t]] + H[R[t]] +    1;
    }
    int newnode(int w){
        ++ size;
        L[size] = R[size] = 0;
        S[size] = C[size] = H[size] = 1;
        W[size] = X[size] = w;
        return size;
    }
    void dfs(int t){
        if(L[t]) dfs(L[t]);
        printf("%d : %d\n", C[t], W[t]);
        if(R[t]) dfs(R[t]);
    }
    void solve1(vector<pair<int, int>> &N, vector<int> &I, int t){
        if(L[t]) solve1(N, I, L[t]);
        N.push_back(make_pair(C[t], W[t]));
        I.push_back(t);
        if(R[t]) solve1(N, I, R[t]);
    }
    int  solve2(vector<pair<int, int>> &N, vector<int> &I, int l, int r){
        if(l > r) return 0; else {
            int m = l + r >> 1, u = I[m];
            L[u] = solve2(N, I, l, m - 1);
            R[u] = solve2(N, I, m + 1, r);
            C[u] = N[m].first ;
            W[u] = N[m].second;
            pushup(u);
            return u;
        }
    }
    int check(int t){
        if(max(H[L[t]], H[R[t]]) >= max(5.0, H[t] * alpha + 1)){
            // puts("REBUILD");
            static vector<pair<int, int>> N;
            static vector<int>            I;
            N.clear(), I.clear();
            solve1(N, I, t);
            return solve2(N, I, 0, N.size() - 1);
        }
        return t;
    }
    int insert(int t, int w){
        if(t == 0) return newnode(w);
        if(w == W[t]) ++ C[t], pushup(t); else 
        if(w <  W[t]) L[t] = insert(L[t], w), pushup(t);
            else      R[t] = insert(R[t], w), pushup(t);
        return check(t);
    }
    int erase(int t, int w){
        if(t == 0) return 0;
        if(w == W[t]) -- C[t], pushup(t); else 
        if(w <  W[t]) L[t] = erase(L[t], w), pushup(t);
            else      R[t] = erase(R[t], w), pushup(t);
        return check(t);
    }
    i64 find_kth(int t, int k){
        if(k == 0) return 0;
        if(k <= S[L[t]]       ) return find_kth(L[t], k);
        if(k <= S[L[t]] + C[t]) return X[L[t]] + 1ll * W[t] * (k - S[L[t]]);
        return find_kth(R[t], k - S[L[t]] - C[t]) + X[L[t]] + 1ll * W[t] * C[t];
    }
    void clear(){
        size = 0;
    }
}
int qread(){
    int w = 1, c, ret;
    while((c = getchar()) >  '9' || c <  '0') w = (c == '-' ? -1 : 1); ret = c - '0';
    while((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + c - '0';
    return ret * w;
}
const int MAXN= 3e5 + 3;
int A[MAXN];
int main(){
    up(1, qread(), _){
        int n = qread(), k = qread();
        int t1 = 0, t2 = 0, h = 18;
        up(1, n, i) A[i] = qread();
        up(1, n, i) t2 = SCT :: insert(t2, A[i]);
        i64 val = 1e18;
        up(0, n, i){
            if(i > 0){
                t1 = SCT :: insert(t1, A[i]);
                t2 = SCT :: erase (t2, A[i]);
            }
            int ans = 0;
            int l = max(0, k - SCT :: S[t2]);
            int r = min(k,     SCT :: S[t1]);
            // printf("[%d, %d]\n", l, r);
            dn(h, 0, j){
                int s1 = l - 1 + (ans | 1 << j);
                int s2 = k - s1;
                if(s1 <= r){
                    i64 w1 = SCT :: find_kth(t1, s1);
                    i64 w2 = SCT :: find_kth(t2, s2);
                    // printf("val = %lld, %lld\n", w1, w2);
                    if(w1 <= w2) ans |= 1 << j;
                    val = min(val, max(w1, w2));
                }
            }
        }
        printf("%lld\n", val);
        SCT :: clear();
    }
    return 0;
}
```

---

## 作者：Helenty (赞：1)

~~数据结构题。~~

可以考虑二分这个答案 $p$，然后在原数列上面枚举断点，那么左右分别从小取到不超过 $p$ 看个数是否超过 $k$ 个，这个事情可以用大根堆解决，这样就是 $O(n\log n\log V)$。

但是这个大根堆的顺序在 $O(\log V)$ 次二分中是固定的，所以我们可以一次 $O(n\log n)$ 预处理出 $a_j\leq a_i,j<i$ 让 $j$ 作为 $i$ 的前驱，然后用双向链表即可做到 $O(n(\log n+\log V))$。

---

## 作者：EuphoricStar (赞：1)

这是一个常规 $\log^2$ 做法。

最大值最小，想到二分答案。

设二分一个 $x$，枚举分割点，就相当于要求前缀和后缀选出若干个元素，使得和均 $\le x$，并且选数的数量 $\ge m$。

显然贪心选，也就是前缀和后缀都选最小的。设 $f_i$ 为 $[1, i]$ 的前缀，选出第 $[1, j]$ 小的数，和 $\le x$，$j$ 的最大值。这个随便树状数组上二分。同理设 $g_i$ 表示 $[i, n]$ 的后缀的答案。最后判是否 $\exists i \in [0, n], f_i + g_{i + 1} \ge m$ 即可。

时间复杂度 $O(n \log n (\log n + \log V))$，其中 $V$ 为值域。不知道为什么还要卡常才勉强能过。

[code](https://codeforces.com/contest/1837/submission/207311280)

---

## 作者：hanjinghao (赞：1)

# 题意

给定一个长度为 $ n $ 的序列，从中找出一个长度为 $ k $ 的子序列（可以不连续），然后将这个子序列划分为前后两部分，使得前半部分元素和与后半部分元素和的 $ \max $ 最小。输出这个最小值。

# 思路

二分答案，然后考虑如何检验。

设当前要检验的答案为 $ x $，对于每个位置 $ i $，求出其左边的元素中，最多能选出多少个元素，使它们的和不超过 $ x $，以及其右边的元素中，最多能选出多少个元素，使它们的和不超过 $ x $。如果左右两边的个数加起来大于等于 $ k $，那么 $ x $ 就是一个合法的答案。

用大根堆存储当前已被选择的元素，并用一个变量记录这些元素的和。如果加入当前的元素后，元素的和依旧不超过 $ x $，那么直接加入即可。否则，把这个元素与堆顶比较，如果它比堆顶小，就把堆顶舍弃掉，用它来顶替，否则把这个元素舍弃掉。正确性显然。

# AC 代码如下

```cpp
#include <bits/stdc++.h>
using namespace std;

char buf[1000005];
int ppos, llen;

inline char gch()
{
	if (ppos == llen)
	{
		ppos = 0;
		llen = fread(buf, 1, 1000000, stdin);
	}
	if (ppos == llen) return -1;
	return buf[ppos++];
}

template < typename T >
inline void read(T &x)
{
	x = 0;
	bool flg = 0;
	char c;
	while ((c = gch()) < 48 || c > 57)
		flg |= (c == '-');
	do
		x = (x << 1) + (x << 3) + (c ^ 48);
	while ((c = gch()) > 47 && c < 58);
	if (flg) x = -x;
}

int OUTPUT[45];

template < typename T >
inline void write(T x)
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	int len = 0;
	do
	{
		OUTPUT[++len] = (x % 10) | 48;
		x /= 10;
	}while (x);
	while (len)
		putchar(OUTPUT[len--]);
}

template < typename T >
inline void writesp(T x)
{
	write(x);
	putchar(32);
}

template < typename T >
inline void writeln(T x)
{
	write(x);
	putchar(10);
}

const int N = 3e5 + 5;
int T, n, k, a[N], b[N], mx1[N], mx2[N];
priority_queue < int > q;

inline bool Check(long long x)
{
	while (q.size())
		q.pop();
	long long sum = 0ll; 
	for (int i = 1; i <= n; ++i)
	{
		if (sum + a[i] <= x)
		{
			sum += a[i];
			q.push(a[i]);
		}
		else if (q.size())
		{
			int tmp = q.top();
			if (a[i] < tmp)
			{
				sum += a[i] - tmp;
				q.pop();
				q.push(a[i]);
			}
		}
		mx1[i] = q.size();
	}
	while (q.size())
		q.pop();
	sum = 0ll; 
	for (int i = n; i; --i)
	{
		if (sum + a[i] <= x)
		{
			sum += a[i];
			q.push(a[i]);
		}
		else if (q.size())
		{
			int tmp = q.top();
			if (a[i] < tmp)
			{
				sum += a[i] - tmp;
				q.pop();
				q.push(a[i]);
			}
		}
		mx2[i] = q.size();
	}
	mx1[0] = 0;
	mx2[n + 1] = 0;
	for (int i = 0; i <= n; ++i)
		if (mx1[i] + mx2[i + 1] >= k) return 1;
	return 0;
}

int main()
{
	read(T);
	while (T--)
	{
		read(n);
		read(k); 
		for (int i = 1; i <= n; ++i)
		{
			read(a[i]);
			b[i] = a[i];
		}
		sort(b + 1, b + n + 1);
		long long rgh = 0;
		for (int i = 1; i <= k; ++i)
			rgh += b[i];
		long long lft = 1ll, ans = rgh;
		while (lft <= rgh)
		{
			long long md = (lft + rgh) >> 1;
			if (Check(md))
			{
				ans = md;
				rgh = md - 1;
			}
			else lft = md + 1;
		}
		writeln(ans);
	}
	return 0;
}

```

---

## 作者：淸梣ling (赞：0)

# Sol

这里说一个比较直接的方法。

首先看到求最大值，我们选择**二分答案** $x$。对于分割点两侧，要确保每一侧选的数的和不超过 $x$，并且两侧选择的个数和不小于 $k$。我们考虑贪心，也就是**不断在剩余的数里面选择最小值**。

那么我们可以设 $f_i$ 为 $1$ 到 $i$ 选择的总和不超过 $x$ 的情况下，最多能选多少个数，$g_i$ 为 $i$ 到 $n$ 选择的总和不超过 $x$ 的情况下，最多能选多少个数。那么我们只需要查找时候有 $f_i+g_{i+1} \ge k$ 的位置。

这里拿求 $f_i$ 举例，$g_i$ 求法相同。我们可以用**大根堆**维护当前已经选择的数字，每次加入 $a_i$，若总和超过 $x$，则弹去目前选择的数中的最大值。

时间复杂度 $O(n\log^2 n)$

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

int a[300100];
int n,m;
int f[300100],g[300100];

bool check(ll x)
{
    priority_queue<ll> q;
    ll now=0;

    for(int i=1; i<=n; i++)
    {
        q.push(a[i]); now+=a[i];
        while(now>x) now-=q.top(), q.pop();
        f[i]=q.size();
    }
    while(q.size()) q.pop(); now=0;
    for(int i=n; i>=1; i--)
    {
        q.push(a[i]); now+=a[i];
        while(now>x) now-=q.top(), q.pop();
        g[i]=q.size();
    }
    for(int i=1; i<n; i++)
    if(f[i]+g[i+1]>=m)
    return 1;
    return 0;
}
ll erfen(ll l, ll r)
{
    while(l<r)
    {
        ll mid=(l+r)>>1;
        if(check(mid))
        r=mid;
        else
        l=mid+1;
    }
    return l;
}
void work()
{
    cin>>n>>m;
    for(int i=1; i<=n; i++)
    scanf("%d", &a[i]);
    if(n==1) cout<<a[1]<<"\n";
    else cout<<erfen(0, 1e15)<<"\n";
}
int main()
{
    int t;
    cin>>t;
    while(t-->0) work();
    return 0;
}
```



---

## 作者：Smallbasic (赞：0)

一个 $\Theta(n\log n\log V)$ 的做法。

首先二分答案，假设当前答案为 $t$。枚举分割点，当前要合法仅当分割点前面选尽量多的数使得它们的和小于等于 $t$,分割点后面选尽量多的数使得它们的和小于等于 $t$，选的数的个数大于等于 $k$。

于是对于每个前缀和后缀，预处理出它们最多可以选出多少个数。选数每次肯定是贪心的选最小值更优，排序之后就变成选一段尽量长的前缀使得和小于 $k$，这个可以用树状数组上二分来维护（线段树的话会超时）。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 3e5 + 5;

inline int read() {
	register int s = 0, f = 1; register char ch = getchar();
	while (!isdigit(ch)) f = (ch == '-' ? -1 : 1), ch = getchar();
	while (isdigit(ch)) s = (s * 10) + (ch & 15), ch = getchar();
	return s * f;
}

int a[N], n, T, k;
int pre[N], suf[N], ord[N], pos[N];

int cnt[N];
ll sum[N];

inline void insert(int q, int x) {
	for (int i = q; i <= n; i += i & -i) ++cnt[i], sum[i] += x;
}

inline void clear() {
	memset(cnt, 0, (n + 1) * sizeof(int));
	memset(sum, 0, (n + 1) * sizeof(ll));
}

inline int query(ll t) {
	int res = 0, pos = 0, tt = __lg(n); ll S = 0;
	for (int i = tt; ~i; --i) {
		if (pos + (1 << i) <= n && S + sum[pos + (1 << i)] <= t) {
			pos += 1 << i;
			res += cnt[pos];
			S += sum[pos];
		}
	} return res;
 }

inline bool cmp(int x, int y) {
	return a[x] < a[y];
}

inline bool check(ll t) {
	clear(); pre[0] = 0;
	for (int i = 1; i <= n; ++i) {
		insert(pos[i], a[i]);
		pre[i] = query(t);
	} clear();
	suf[n + 1] = 0;
	for (int i = n; i; --i) {
		insert(pos[i], a[i]);
		suf[i] = query(t);
		if (pre[i - 1] + suf[i] >= k) return 1;
	} return 0;
}

int main() {
	T = read();
	while (T--) {
		n = read(); k = read();
		for (int i = 1; i <= n; ++i) a[i] = read(), ord[i] = i;
		sort(ord + 1, ord + n + 1, cmp); 
		for (int i = 1; i <= n; ++i) pos[ord[i]] = i;
		ll l = 0, r = 0, mid, res = 1e18;
		for (int i = 1; i <= k; ++i) {
			r += a[ord[i]];
			if (i == k / 2) l = r;
		}
		while (l <= r) {
			mid = l + r >> 1;
			if (check(mid)) r = (res = mid) - 1;
			else l = mid + 1;
		} printf("%lld\n", res);
	}
	return 0;
}
```


---

## 作者：_jimmywang_ (赞：0)

赛时卡 E 了，~~看成输入排名~~，因此没看 F，亏。

先离散化。

在 **原序列** $a$ 中枚举分割点 $t$，钦定第一个人只在 $[1,t]$ 中选数，第二个人只在 $[t+1,n]$ 中选。

假设第一个人选 $x$ 个，那么第二个人选 $k-x$ 个。

那么第一个人的最小值 $A$ 等于 $[1,t]$ 中的 **前 $x$ 小的数的和**，第二个人的最小值 $B$ 等于 $[t+1,n]$ 中的 **前 $k-x$ 小的数的和**。

此时答案为 $\max(A,B)$。

当我们增加 $x$ 时，$A$ 会上升，$B$ 会下降，$A-B$ 具有单调性。看成函数的话，两个图像的交点即为 $\max(A,B)$ 的最小值，此时 $A-B$ 最接近 0。

因此假设我们能快速得到 $A$ 和 $B$，我们就可以对 $A-B$ 二分出最接近 0 的位置。这部分是 $O(\log n)$。

接下来考虑如何快速得到 $A$ 和 $B$。

使用两棵 **权值线段树**，第一棵存当前 $[1,t]$ 中的数，第二棵存 $[t+1,n]$ 中的数。每个节点记录一下它代表的区间中数的个数和它们的和，这样前后缀的前 $x$ 小值的和可以在这两棵树上 $O(\log n)$ 查询。

移动 $t$ 到 $t+1$ 时，只需在第一棵树中加入一个 $a_{t+1}$ 并在第二棵中删除一个 $a_{t+1}$ 即可。

总复杂度 $O(n\log^2n)$，不用卡常。

---

