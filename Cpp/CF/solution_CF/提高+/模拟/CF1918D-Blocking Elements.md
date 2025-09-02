# Blocking Elements

## 题目描述

You are given an array of numbers $ a_1, a_2, \ldots, a_n $ . Your task is to block some elements of the array in order to minimize its cost. Suppose you block the elements with indices $ 1 \leq b_1 < b_2 < \ldots < b_m \leq n $ . Then the cost of the array is calculated as the maximum of:

- the sum of the blocked elements, i.e., $ a_{b_1} + a_{b_2} + \ldots + a_{b_m} $ .
- the maximum sum of the segments into which the array is divided when the blocked elements are removed. That is, the maximum sum of the following ( $ m + 1 $ ) subarrays: \[ $ 1, b_1 − 1 $ \], \[ $ b_1 + 1, b_2 − 1 $ \], \[ $ \ldots $ \], \[ $ b_{m−1} + 1, b_m - 1 $ \], \[ $ b_m + 1, n $ \] (the sum of numbers in a subarray of the form \[ $ x,x − 1 $ \] is considered to be $ 0 $ ).

For example, if $ n = 6 $ , the original array is \[ $ 1, 4, 5, 3, 3, 2 $ \], and you block the elements at positions $ 2 $ and $ 5 $ , then the cost of the array will be the maximum of the sum of the blocked elements ( $ 4 + 3 = 7 $ ) and the sums of the subarrays ( $ 1 $ , $ 5 + 3 = 8 $ , $ 2 $ ), which is $ \max(7,1,8,2) = 8 $ .

You need to output the minimum cost of the array after blocking.

## 说明/提示

The first test case matches with the array from the statement. To obtain a cost of $ 7 $ , you need to block the elements at positions $ 2 $ and $ 4 $ . In this case, the cost of the array is calculated as the maximum of:

- the sum of the blocked elements, which is $ a_2 + a_4 = 7 $ .
- the maximum sum of the segments into which the array is divided when the blocked elements are removed, i.e., the maximum of $ a_1 $ , $ a_3 $ , $ a_5 + a_6 = \max(1,5,5) = 5 $ .

So the cost is $ \max(7,5) = 7 $ .

In the second test case, you can block the elements at positions $ 1 $ and $ 4 $ .

In the third test case, to obtain the answer $ 11 $ , you can block the elements at positions $ 2 $ and $ 5 $ . There are other ways to get this answer, for example, blocking positions $ 4 $ and $ 6 $ .

## 样例 #1

### 输入

```
3
6
1 4 5 3 3 2
5
1 2 3 4 5
6
4 1 6 3 10 7```

### 输出

```
7
5
11```

# 题解

## 作者：Register_int (赞：20)

答案由两部分组成，一部分为加和，另一部分为 $\max$。假设我们当前已经确定答案不超过 $x$，那么有：

- 两个点间的最大间隔不超过 $x$。
- 点权之和不超过 $x$。

不妨用前者来约束后者。加入两个虚点 $a_0=a_{n+1}=0$，设 $dp_i$ 表示考虑前 $i$ 个位置，选了第 $i$ 个位置，且最大间隔不超过 $x$ 的最小价值。容易得到转移：

$$dp_i=a_i+\min_{s_{i-1}-s_j\le x}dp_j$$

其中 $s$ 为前缀和数组。显然每次可转移到 $i$ 的区间左右端点都单增，所以可以单调队列优化至线性。

此时 $dp_{n+1}$ 即为答案，若 $dp_{n+1}\le x$，则表示答案可以 $\le x$。二分答案即可，时间复杂度 $O(n\log nV)$。

# AC 代码 

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e5 + 10;

int T, n; ll a[MAXN], s[MAXN], dp[MAXN];

deque<int> q;

inline 
bool check(ll x) {
	for (int i = 1; i <= n + 1; i++) dp[i] = 0;
	q.clear(), q.push_back(0);
	for (int i = 1, j = 0; i <= n + 1; i++) {
		for (; !q.empty() && s[i - 1] - s[q.front()] > x; q.pop_front());
		dp[i] = a[i] + dp[q.front()];
		for (; !q.empty() && dp[q.back()] >= dp[i]; q.pop_back());
		q.push_back(i);
	}
	return dp[n + 1] <= x;
}

ll l, r, mid;

int main() {
	for (scanf("%d", &T); T--;) {
		scanf("%d", &n), a[n + 1] = 0;
		for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		for (int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i];
		for (l = 1, r = s[n]; l < r; check(mid = l + r >> 1) ? r = mid : l = mid + 1);
		printf("%lld\n", l);
	}
}
```

---

## 作者：w9095 (赞：4)

[CF1918D Blocking Elements](https://www.luogu.com.cn/problem/CF1918D)

如果你做过以下两道题目，那么这道题对你来说会简单得多。

[P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)

[P2034 选择数字](https://www.luogu.com.cn/problem/P2034)

由于题目要求最大值的最小值，考虑二分。

如果我们使用 $x$ 的费用划分了整个数列，那么我们同样也可以使用比 $x$ 更多的费用划分这个数列，因为划分方式不用进行改变。所以满足二分条件，可以二分。

考虑二分之后如何让判断是否可以划分整个序列。当我们选择隔断一个数时，会对已经选出的数的总和造成影响。由于这个影响，我们发现很难对这个问题进行贪心判定，所以考虑动态规划。

由于一般的动态规划方式很难对上一个隔断的位置进行维护，所以需要状态中包含位置信息。有一种经典的解决方式，设状态 $dp[i]$ 表示隔断第 $i$ 个元素，使前 $i-1$ 个元素满足条件的最小隔断元素之和，这样每个状态就包含了位置信息。然而，由于最后一个元素并不一定要被隔断，所以统计答案时要将所有在 $i$ 处隔断后，不再进行隔断，最后一段之和小于当前二分答案值的位置 $dp[i]$ 都统计进去，求最小值。

设 $a_i$ 表示数列中的 $i$ 个元素的值，$s_i$ 为数列 $a$ 的前缀和，$k$ 为二分当前值。根据状态定义，很容易推出以下转移方程：

$$dp[i]=\min(dp[j]+a_i)(j\lt i,s_{i-1}-s_{j}\le k)$$

经过观察，我们发现每次可以转移的状态是根据位置减少的，且每次补充一个新的元素，这是很经典的单调队列优化动态规划的应用模型。使用单调队列维护可转移集合，即可做到 $O(n)$ 求出所有 $dp[i]$ 的值。

于是，我们就以 $O(n\log n)$ 的时间复杂度解决了这个问题。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long t,n,a[300000],s[300000],f[300000];
long long v[300000],p[300000],q=1,h=0;
bool check(long long now)
{
	long long ans=1e15;
	for(int i=1;i<=n;i++)f[i]=1e15;
	q=1,h=0;
	v[++h]=0,p[h]=0;
	for(int i=1;i<=n;i++)
	    {
	    	while(s[i-1]-p[q]>now&&q<=h)q++;
	    	f[i]=v[q]+a[i];
	    	while(f[i]<=v[h]&&q<=h)h--;
	    	v[++h]=f[i],p[h]=s[i];
		}
	for(int i=n;i>=0;i--)
	    {
	    	if(s[n]-s[i]>now)break;
	    	ans=min(ans,f[i]);
		}
	return ans<=now;
}
 
int main()
{
	scanf("%lld",&t);
	while(t--)
	   {
	   	scanf("%lld",&n);
	   	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	   	for(int i=1;i<=n;i++)s[i]=s[i-1]+a[i];
	   	long long l=1,r=1e15,ans=0;
	   	while(l<=r)
	   	   {
	   	   	long long mid=(l+r)>>1;
	   	   	if(check(mid))ans=mid,r=mid-1;
	   	   	else l=mid+1;
		   }
		printf("%lld\n",ans);
	   }
	return 0;
} 
```

---

## 作者：BIG_CUTE_BUG (赞：1)

[题传](https://www.luogu.com.cn/problem/CF1918D)

## 思路

最大最小想到二分答案。

称原题目中的选择封锁的数为断点，断出的子数组即划分出的区间，当前二分值为 $mid$。

每次 `check` 考虑：在划分出的每个区间之和都小于等于 $mid$ 的情况下，判断最小断点和是否也小于等于 $mid$。

于是设计 dp：$f_i$ 表示选第 $i$ 个数作为断点时，前 $i$ 个数的 **合法划分方案** 中，最小的断点和。

这里可以选择一个点，作为上一个断点来进行转移。

首先因为要满足划分的每个区间都小于等于 $mid$，所以对当前断点 $i$ 就有一个极限划分区间 $[l,i-1]$，其和恰好不大于 $mid$。由此有上一个断点的选取范围 $[l-1,i-1]$。

其次要最小，就得在 $[l-1,i-1]$ 中找一个 $p$，使得 $f_p$ 最小。

前者可以双指针，后者单调队列。

推完 $f$ 后，最后若 $\exists i\in [1,n],f_i\le mid$ 为真，则当前值 $mid$ 可行。

`check` 复杂度 $\text{O}(n)$，总复杂度 $\text{O}(n\log n)$。


## CPP
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N= 1e5+ 5;
typedef long long ll;
int t, n, a[N], q[N];
ll f[N];
bool check(ll x)
{
	int l= 0, hh= 0, tt= 0; ll sum= 0;
	memset(q, 0, sizeof q);
	for(int i= 1; i<= n; i++)
	{
		while(sum> x) sum-= a[l+ 1], ++l;
		while(q[hh]< l && hh<= tt) hh++;
		f[i]= f[q[hh]]+ a[i];
		while(f[q[tt]]> f[i] && hh<= tt) tt--; q[++tt]= i;
		sum+= a[i];
	}
	sum= 0;
	for(int i= n; i>= 0; i--)
	{
		if(sum<= x && f[i]<= x) return 1;
		sum+= a[i];
		if(sum> x) break;
	}
	return 0;
}
signed main()
{
	ios:: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin>> t;
	for(int p= 1; p<= t; p++)
	{
		cin>> n;
		ll l= 0, r= 0, ans;
		for(int i= 1; i<= n; i++) cin>> a[i], r+= a[i];
		while(l<= r)
		{
			ll mid= l+ r>> 1;
			if(check(mid)) r= mid- 1, ans= mid;
			else l= mid+ 1;
		}
		cout<< ans<< '\n';
	}
	return 0;
}
```

---

## 作者：MaxBlazeResFire (赞：1)

献祭我的 100 分钟。

先二分答案。问题转化为能否选出若干不触碰的连续段，每段的和 $\leq k$，且分割开它们的数的和 $\leq k$。

可以把问题转化为，选出若干这样的连续段，每段的和 $\leq k$，并且最大化每段的和的和。若能求出这个最大值，只需要判断它是否 $\geq S-k$，其中 $S$ 是所有数的和。

记 $s$ 为前缀和，$f_r$ 表示右端点恰在 $r$ 的答案，$g$ 为 $f$ 的前缀 $\max$，有转移

$$f_r=\max_{l'\geq l_r}s_r-s_{l'-1}+g_{l'-2}$$

其中 $l_i$ 为最小的 $j$ 使得 $[j,i]$ 区间和 $\leq k$，可以双指针求出。

注意到我们要优化的是一个后缀 $\max$ 的形式，动态加点 $\rm st$ 表维护 $v_l=-s_{l-1}+g_{l-2}$ 即可。

复杂度 $O(n\log n\log S)$。

实际上注意到查询的区间左端点单调不降，可以做到 $O(n\log S)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 100005

//f[r] 表示最靠右的子段右端点在 r 时的最大和，g[r] 表示最靠右的子段右端点在 r 及 r 左侧时的最大和
//动态加点 st 表维护后缀 max

int n,S,s[MAXN],a[MAXN],f[MAXN],g[MAXN],L[MAXN],lg2[MAXN],st[MAXN][17];

inline void insert( int x , int v ){
	st[x][0] = v;
	for( int j = 1 ; j <= 16 ; j ++ )
		if( x - ( 1 << j ) + 1 >= 1 ) st[x - ( 1 << j ) + 1][j] = max( st[x - ( 1 << j ) + 1][j - 1] , st[x - ( 1 << ( j - 1 ) ) + 1][j - 1] );
}

inline int query( int l , int r ){
	int len = lg2[r - l + 1];
	return max( st[l][len] , st[r - ( 1 << len ) + 1][len] );
}

inline bool chk( int X ){
	for( int i = 1 ; i <= n ; i ++ ) f[i] = g[i] = L[i] = 0;
	for( int i = 1 ; i <= n ; i ++ )
		for( int j = 0 ; j <= 16 ; j ++ ) st[i][j] = 0;
	L[n] = n + 1;
	for( int i = n ; i >= 1 ; i -- ){
		if( i < n ) L[i] = L[i + 1];
		while( L[i] >= 2 && s[i] - s[L[i] - 2] <= X ) L[i] --;
		if( L[i] > i ) return 0;
	}
	for( int r = 1 ; r <= n ; r ++ ){
		insert( r , - s[r - 1] + ( r > 1 ? g[r - 2] : 0 ) );
		f[r] = query( L[r] , r ) + s[r];
		g[r] = max( g[r - 1] , f[r] );
	}
	return S - g[n] <= X;
}

inline void solve(){
	scanf("%lld",&n); S = 0;
	for( int i = 1 ; i <= n ; i ++ ) scanf("%lld",&a[i]),S += a[i],s[i] = s[i - 1] + a[i];
	int l = 0,r = S,ans = 0;
	while( l <= r ){
		int mid = ( l + r ) >> 1;
		if( chk( mid ) ) ans = mid,r = mid - 1;
		else l = mid + 1;
	}
	for( int i = 1 ; i <= n ; i ++ )
		for( int j = 0 ; j <= 16 ; j ++ ) st[i][j] = 0;
	printf("%lld\n",ans);
}

signed main(){
	for( int i = 2 ; i <= MAXN - 5 ; i ++ ) lg2[i] = lg2[i >> 1] + 1;
	int testcase; scanf("%lld",&testcase);
	while( testcase -- ) solve();
	return 0;
}
```

---

## 作者：SamHJD (赞：0)

## [Blocking Elements](https://www.luogu.com.cn/problem/CF1918D)

### 题意

给出 $a$ 数组，你需要删除一些数，使数组被分为若干段，这些段的和的最大值为 $x$，设删除的数的和为 $y$。求 $\max(x,y)$ 的最小值。

### 解法

二分 $\max(x,y)=mid$。

不好找出一个贪心策略使方案满足限制并且 $y$ 最小，于是尝试动态规划。

设 $f_i$ 表示考虑前 $i$ 个数使其满足限制，并且强制删除 $i$，删除的数的和的最小值。设一个最小的 $pos$ 满足 $sum_{[pos+1,i-1]}\le mid$，则有转移：

$$f_i=\begin{cases}\min\limits_{j=pos}^{i-1}\{f_j+a_i\}\\a_i\ (sum_{[1,i-1]}\le mid)\end{cases}$$

显然随着 $i$ 上升，$pos$ 不降，可以用单调队列优化转移。第二条转移特判即可。

### [代码](https://www.luogu.com.cn/paste/vtqgrm0i)

---

## 作者：KingPowers (赞：0)

感觉比 C 题还简单啊。

答案显然具有单调性，因此考虑二分转化为判定性问题。

假设我们要求代价不超过 $mid$，那么限制就是拿出来的数字之和不超过 $mid$，拿出来的数字分成的每一段的和不超过 $mid$。

考虑 dp，在保证每一段的和不超过 $mid$ 的前提下，维护拿出来的数字和的最小值：设 $f_i$ 表示强行拿出来 $a_i$ 的情况下，$[1,i]$ 中拿出来的数的和的最小值，转移平凡：

$$
f_{i}=\min_{s_{i-1}-s_{j}<mid}\{f_j+a_i\}
$$

其中 $s_i=\sum_{j=1}^i a_j$，也就是前缀和。

不难发现直接转移是 $O(n^2)$ 的，但是注意到随着 $i$ 的增大，$j$ 一定不会变小，换句话说取 $\min$ 的区间是个滑动窗口，单调队列优化即可将 dp 过程优化到 $O(n)$。

注意的一点是，只需要存在一个 $f_i$ 满足 $f_i\le mid$ 且 $s_n-s_i\le mid$ 就满足条件了。

时间复杂度 $O(n\log n)$。

赛时偷懒写的小根堆，复杂度会多一个 $\log$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i, a, b) for(int i = (a); i <= (b); i++)
#define Rof(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
const int N = 5e5 + 5;
int n, a[N], f[N], sum[N];
bool check(int mid){
    For(i, 1, n) f[i] = 1e18;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>q;
    q.push({0, 0}); f[0] = 0; int pos = 0;
    For(i, 1, n){
        while(pos + 1 < i && sum[i - 1] - sum[pos] > mid) pos++;
        while(q.top().second < pos) q.pop();
        f[i] = q.top().first + a[i];
        q.push({f[i], i});
    }
    For(i, 1, n) if(f[i] <= mid && sum[n] - sum[i] <= mid) return true; 
    return false;
}
void Solve(){
    cin >> n;
    For(i, 1, n) cin >> a[i];
    For(i, 1, n) sum[i] = sum[i - 1] + a[i];
    int l = 0, r = 1e16, ans = -1;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(check(mid)) r = mid - 1, ans = mid;
        else l = mid + 1;
    }
    cout << ans << '\n';
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T = 1; cin >> T;
    while(T--) Solve();
    return 0;
}
```

---

## 作者：GI录像机 (赞：0)

## 思路

让最大值最小，很容易想到二分答案。

假设目前我们要检查的答案是 $x$。设 $dp_i$ 表示第 $i$ 个数作为分割点时 $i$ 及之前的分割点和的最小合法值，易得转移方程为：$dp_i=a_i+\min dp_j(a_{j+1}+\cdots+a_{i-1}\le x)$。

我们只需要找到一个 $dp_i\le x$ 且 $a_{i+1}+\cdots+a_n\le x$ 就代表 $x$ 作为答案是可行的，即分割点之和与最后一段均小于 $x$。

转移使用单调队列和前缀和优化即可，复杂度 $O(n\log n)$。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read() {
	int f = 1, x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return f * x;
}
void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
const int N = 1e5 + 10, MOD = 1e9 + 7, INF = 0x3f3f3f3f;
int t = read(), dp[N], n, a[N], sum[N];
bool check(int x) {
	bool flag = 0;
	for (int i = 1; i <= n; i++)dp[i] = 0;
	deque<int>q;
	q.push_front(0);
	for (int i = 1; i <= n; i++) {
		while (sum[i - 1] - sum[q.front()] > x)q.pop_front();
		dp[i] = dp[q.front()] + a[i];
		while (dp[q.back()] > dp[i])q.pop_back();
		q.push_back(i);
		if (sum[n] - sum[i] <= x && dp[i] <= x)flag = 1;
	}
	return flag;
}
signed main() {
	while (t--) {
		int l = 0, r = 0;
		n = read();
		for (int i = 1; i <= n; i++) {
			a[i] = read();
			sum[i] = sum[i - 1] + a[i];
			r += a[i];
			l = max(l, a[i]);
		}
		int ans = r;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (check(mid)) {
				ans = mid;
				r = mid - 1;
			} else l = mid + 1;
		}
		write(ans);
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：DerrickLo (赞：0)

首先很容易想到二分答案。

然后我们考虑二分后怎么判断是否可行，假设当前二分的值是 $mid$，那我们用 $dp_i$ 表示考虑了前 $i$ 个数且第 $i$ 个数是切割点，切割点权值总和的最小值，那么

$$dp_i=\min_{sum(j,i-1)\le mid}dp_j+a_i$$

其中 $sum(j,i-1)$ 表示 $\displaystyle{\sum_{k=j}^{i-1}a_k}$。

然后我们枚举一下最后一个切割点在哪，就能做到 $O(n^2\log V)$。

然后我们发现对于每个 $i$，$j$ 能取到的数都是一个区间，那么就用线段树优化一下就能做到 $O(n\log n\log V)$ 了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,a[100005],dp[100005],sm[100005];
struct tree{
	int l,r,minx;
}tr[400005];
void pushup(int u){
	tr[u].minx=min(tr[u<<1].minx,tr[u<<1|1].minx);
}
void build(int u,int l,int r){
	tr[u]={l,r,0};
	if(l==r)return;
	int mid=l+r>>1;
	build(u<<1,l,mid),build(u<<1|1,mid+1,r);
}
void change(int u,int pos,int k){
	if(tr[u].l==tr[u].r){
		tr[u].minx=k;
		return;
	}
	int mid=tr[u].l+tr[u].r>>1;
	if(pos<=mid)change(u<<1,pos,k);
	else change(u<<1|1,pos,k);
	pushup(u);
}
int query(int u,int l,int r){
	if(tr[u].l>=l&&tr[u].r<=r)return tr[u].minx;
	int mid=tr[u].l+tr[u].r>>1,res=1e18;
	if(l<=mid)res=min(res,query(u<<1,l,r));
	if(r>mid)res=min(res,query(u<<1|1,l,r));
	return res;
}
bool check(int mid){
	build(1,0,n);
	dp[0]=0,change(1,0,0);
	for(int i=1;i<=n;i++)dp[i]=1e18,change(1,i,1e18);
	int anss=1e18,summ=0,j=1;
	for(int i=1;i<=n;i++){
		int sum=0;
		while(sm[i-1]-sm[j-1]>mid)j++;
		dp[i]=query(1,j-1,i-1)+a[i];
		change(1,i,dp[i]);
	}
	for(int i=n;i;i--){
		if(summ>mid)break;
		anss=min(anss,dp[i]);
		summ+=a[i];
	}
	return anss<=mid;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i],sm[i]=sm[i-1]+a[i];
		int l=1,r=1e18,ans=1e18;
		while(l<=r){
			int mid=l+r>>1;
			if(check(mid))ans=mid,r=mid-1;
			else l=mid+1;
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：yyrwlj (赞：0)

赛后 $1$ 分钟切了。

## 题意简述

给定一个正整数序列，选择一些点作为分割点，让分割点的和，和分割后每段和的最大值最小。

## 思路

考虑二分答案。

check 函数考虑动态规划。

设 $f_i$ 表示 $i$ 是分割点的所有满足最大子段和小于等于 $mid$ 的情况下，分割点的最小和。

对原序列构建出前缀和数组 $sum$，有朴素的转移：

$$f_i = \min_{sum_{i-1}-sum_j \le mid}{f_j+a_i} $$

因为原序列都是正整数，所以前缀和的 $sum$ 数组是单调递增的，就可以对 $sum_{i-1}-sum_j \le mid$ 的部分做单调队列优化。

最后只需控制最后一段的和，只要有 $sum_n - sum_i \le mid$ 而且 $f_i \le mid$ 的情况，就说明可以满足 check 的 $mid$。

---

