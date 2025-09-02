# Alice's Adventures in Cutting Cake

## 题目描述

爱丽丝参加了疯帽子的茶话会！有一块长长的蛋糕，由 $n$ 个部分组成，每个部分的美味度值为 $a_1, a_2, \ldots, a_n$ 。茶话会上共有 $m$ 个生物，但不包括爱丽丝。

爱丽丝将把蛋糕切成 $m + 1$ 块。正式地说，她将把蛋糕分成 $m + 1$ 个子串，每个子串由一定数量的相邻部分组成。一块蛋糕的美味度是其各部分美味度的总和。之后，她会将这些 $m + 1$ 块蛋糕分给 $m$ 个生物和她自己（她的那块蛋糕可以是空的）。但是，只有当每个 $m$ 个生物的蛋糕美味度达到或超过 $v$ 时，它们才会感到高兴。

Alice 想要确保每个生物都快乐。受此条件限制，她还想最大化自己的那块食物的美味程度。你能帮助 Alice 找到她的那块食物可以达到的最大美味程度吗？如果没有办法确保每个生物都快乐，则输出 $-1$ 。

## 样例 #1

### 输入

```
7
6 2 1
1 1 10 1 1 10
6 2 2
1 1 10 1 1 10
6 2 3
1 1 10 1 1 10
6 2 10
1 1 10 1 1 10
6 2 11
1 1 10 1 1 10
6 2 12
1 1 10 1 1 10
6 2 12
1 1 1 1 10 10```

### 输出

```
22
12
2
2
2
0
-1```

# 题解

## 作者：chenxi2009 (赞：12)

# 思路
~~你说得对，二分可以做，但是双指针复杂度更优。刚复习双指针就写一篇双指针题解吧。~~

问题肯定要用到区间和，先处理前缀和 $s$。

发现 Alice 取的蛋糕是一个连续区间，并且是可以双指针的，即：

当取区间 $[l,r]$ 时，若 $[l,r+1]$ 可取，则 $[l,r+1]$ 更优（显然值更大）；\
当取区间 $[l,r]$ 时，区间 $[l+1,r]$ 也是可取的。

**关于双指针：[双指针板子](https://www.luogu.com.cn/problem/P1147)**

那怎么判断一个区间是否可取呢？我们需要知道对于任意区间 $[1,l)$ 和 $(r,n]$ 能满足多少个 creatures（以下称小动物）的需求，如果说加起来达到 $m$ 就可以了。

怎么得到一段蛋糕的前缀/后缀能满足多少个小动物呢？对于前缀 $[1,r]$，如果知道**这一段的后缀** $[l',r]$ 可以满足一个小动物，那么 $[l,r]$ 就可以满足 $[1,l')$ 这一段满足的小动物数量 $+1$ 个小动物了。\
——因为要知道这一段前缀**最多**能满足多少个小动物，所以自然 $[l',r]$ 要最短。怎么找到最短的可以满足一个小动物的区间呢？\
——双指针。后缀同理。

倒着写一遍，这道题就做完啦。时间复杂度 $O(n)$。不明白的可以参考代码注释。相信聪明的读者看完之后都能增进对双指针的理解吧。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,v,a[200001],b[200001],r,l,c[200001],mxb[200001],mxa[200002];
long long s[200001],ans;
int main(){
	scanf("%d",&T);
	while(T --){
		r = 0,ans = -1;
		scanf("%d%d%d",&n,&m,&v);
		for(int i = 1;i <= n;i ++){
			scanf("%d",&a[i]);
			s[i] = s[i - 1] + a[i];//前缀和 
		}
		for(l = 1;l <= n;l ++){
			while(r <= n && s[r] - s[l - 1] < v)r ++;
			b[l] = r;//双指针：[l,r] 是以 l 为左端的最短的能满足一个小动物的区间，r=n+1 为满足不了 
		}
		l = n + 1;
		for(r = n;r;r --){
			while(l && s[r] - s[l - 1] < v)l --;
			c[r] = l;//双指针：[l,r] 是以 r 为右端的最短的能满足一个小动物的区间，l=0 为满足不了 
		}
		for(int i = 1;i <= n;i ++)mxb[i] = c[i] ? mxb[c[i] - 1] + 1 : 0;//[1,i] 可以满足的小动物数量 
		mxa[n + 1] = 0;//防越界 
		for(int i = n;i;i --)mxa[i] = b[i] <= n ? mxa[b[i] + 1] + 1 : 0;//[i,n] 可以满足的小动物数量 
		r = 0;
		for(l = 1;l <= n;l ++){
			while(r < n && mxb[l - 1] + mxa[r + 2] >= m)r ++;//双指针：[l,r] 是以 l 为左端的 Alice 可取的最长区间 
			if(mxb[l - 1] + mxa[r + 1] >= m)ans = max(ans,s[r] - s[l - 1]);//可能查到无效区间，所以需要判定 
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：_299817_ (赞：6)

## Part 0：前言
逆天场，鉴定为 B >>>> C。

## Part 1：题意

给定一个数组，你要把这个数组分成 $m+1$ 段，你要保证其中的 $m$ 段中每段的元素和大于等于 $V$，然后将剩下的那一段中的元素和最大化，求最大化的值。

## Part 2：思路

不难发现，我们几乎所有的错误的贪心做法都卡在了一个地方：你不知道我们需要最大化的那个区间的开始位置，于是我们考虑枚举每个区间的开始位置，接着预处理出 $1\sim i$ 和 $i\sim n$ 中最多能分成多少个区间和大于等于 $V$ 的区间。

然后这道题的正解也就显而易见了，枚举我们需要让区间和最大化的区间的起始位置，然后二分我们能在保证元素和大于等于 $V$ 的段数不小于 $m$ 的情况下，区间最右边的右端点，然后我们要做一个前缀和去保证我们能实时求出区间和（更新答案）。

## Part 3：代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<unordered_map>
#include<map>
#include<queue>
#include<stack>
#include<bitset>
#include<list>
#include<cstdint>
using namespace std;
#define rep(i, l, r) for(i32 i = (i32)(l); i <= (i32)(r); i++)
#define per(i, l, r) for(i32 i = (i32)(l); i >= (i32)(r); i--)
#define FILEIO(INNAME, OUTNAME) freopen(INNAME".in", "r", stdin), freopen(OUTNAME".out", "w", stdout)
#define sort stable_sort
#ifdef QwQ_ATM
    #define Debug(x) cout << "---------- #Debug " << x << " ----------" << endl
    #define DDebug(s, x) cout << s << x
    #define Output(x) cout << x
#else
    #define Debug(x) 1
    #define DDebug(s, x) 1
    #define Output(x) 1
    #define endl '\n'
    #include<bits/stdc++.h>
#endif
#define int long long
typedef pair<int, int> pii;
using i32 = int32_t;
using i64 = int64_t;

const int MAXN = 200010;

int T, n, m, v;
int a[MAXN];
int sum[MAXN];
int pre[MAXN], lst[MAXN];

i32 main(){
    #ifdef QwQ_ATM
        FILEIO("input", "output");
    #endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    while(T--){
        cin >> n >> m >> v;
        rep(i, 1, n) cin >> a[i];
        rep(i, 1, n + 1) sum[i] = sum[i - 1] + a[i]; // 前缀和
        int now = 0; // 预处理数组的所有前缀和后缀中最多能分成多少个区间和大于等于 V 的区间，分别是 pre 和 lst
        rep(i, 1, n){
            now += a[i];
            if(now >= v) pre[i] = pre[i - 1] + 1, now = 0;
            else pre[i] = pre[i - 1];
        }
        now = 0;
        per(i, n, 1){
            now += a[i];
            if(now >= v) lst[i] = lst[i + 1] + 1, now = 0;
            else lst[i] = lst[i + 1];
        }
        if(pre[n] < m){ // 判断无解的情况，也就是整个序列根本不能分成 m 个区间和大于等于 V 的区间
            cout << -1 << endl;
            continue;
        }
        int ans = -1;
        rep(i, 1, n){
            int need = m - pre[i - 1]; // 计算出我们现在还需要多少个区间和大于等于 V 的区间
            int u = upper_bound(lst + i, lst + n + 2, need, greater<int>()) - lst - 1; // 二分右端点
            if(lst[u] < need) continue; // 这个左端点不满足条件
            ans = max(ans, sum[u - 1] - sum[i - 1]); // 用前缀和更新答案
        }
        cout << ans << endl; // 输出
        rep(i, 1, n) pre[i] = lst[i] = 0; // 多测记得清空
    }
    return 0;
}
```

---

## 作者：djfuck (赞：3)

很明显这个题贪心是做不了的。

我们设留给 Alice 的那块蛋糕为 $[l, r]$，那么这个方案合法 $\Leftrightarrow$ $[1, l - 1]$ 和 $[r + 1, n]$ 加起来可供 $m$ 个生物。

接下来就很清晰了。我们设 $\text{prefix}_i$ 表示 $[1, i]$ 最多可供的生物数，$\text{suffix}_i$ 表示 $[i, n]$ 最多可供的生物数，贪心地遍历就可以了。

最后，用双指针就能统计出答案。注意还需要用前缀和以快速得到 $\sum_\ell^{r} a_i$。

```cpp
#include <bits/stdc++.h>

void solve() {
    int64_t n, m, v;
    std::cin >> n >> m >> v;
    std::vector<int64_t> a(n + 2);
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }

    std::vector<int64_t> prefix(n + 2), suffix(n + 2), prefix_sum(n + 2);
    for (int i = n, leftover = 0; i <= n; ++i) {
        prefix[i] = prefix[i - 1];
        leftover += a[i];
        if (leftover >= v) {
            prefix[i]++;
            leftover = 0;
        }
    }
    for (int i = n, leftover = 0; i >= 1; --i) {
        suffix[i] = suffix[i + 1];
        leftover += a[i];
        if (leftover >= v) {
            suffix[i]++;
            leftover = 0;
        }
    }
    for (int i = 1; i <= n; ++i) {
        prefix_sum[i] = prefix_sum[i - 1] + a[i];
    }
    
    auto sum = [&](int L, int R) -> int64_t {
        return prefix_sum[R] - prefix_sum[L - 1];
    };
    auto check = [&](int L, int R) -> int64_t {
        return prefix[L - 1] + suffix[R + 1] >= m;
    };

    int64_t maxAns = -1;
    if (check(1, 0) == false) {
        std::cout << -1 << std::endl;
        return;
    }
    for (int l = 1, r = 0; l <= n; ++l) {
        while (check(l, r) == true && r <= n) {
            r++;
        }
        --r;
        if (check(l, r)) {
            maxAns = std::max(maxAns, sum(l, r));
        }
    }
    std::cout << maxAns << std::endl;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    int tc;
    std::cin >> tc;
    while (tc--) {
        solve();
    }
    return 0;
}
```

---

## 作者：netlify (赞：3)

翻译者题解。

### 思考

1. 如何快速地决定 Alice 可获得一段字串呢？

2. 当我们枚举 $i$ ，如何快速地决定最大的 $j$ 使得 $[i,j]$ 可获得呢？

### 思路

#### 预处理

对于一个左端点 $i$ ，右端点 $j$ 可以有多大？

我们可以预处理一个前缀 $pre[i]$ 表示 $[1,i]$ 最多可以喂养多少生物。

设前面第 $1$ 个 $k$ 满足 $sum[k,i]\ge v$ 则：
$$
pre[i]=pre[k-1]+1
$$
同理预处理后缀 $suf[i]$ 。

#### 求贡献

如果 $pre[n]<m$ ，显然不能喂养这么多生物。

然后枚举所有左端点 $i$ ，双指针求出最后一个 $j$ 满足
$$
pre[i]+suf[j]\ge m
$$
然后产生贡献 $sum[i,j-1]$ 。

````cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+1;
int T,n,m,v,a[N],sum[N],pre[N],suf[N];
#define sum(i,j) (sum[j]-sum[i])
signed main(){
	for(cin>>T;T--;){
		cin>>n>>m>>v;
		for(int i=0;i<=n;i++)pre[i]=suf[i]=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			sum[i]=sum[i-1]+a[i];
			pre[i]=suf[i]=0;
		}
		for(int i=1;i<=n;i++){
			int l=0,r=i+1,mid;
			while(l+1<r)
				mid=l+r>>1,(sum[i]-sum[mid-1]>=v)?l=mid:r=mid;
			if(sum[i]-sum[l-1]>=v)pre[i]=pre[l-1]+1;
		}
		for(int i=n;i;i--){
			int pos=lower_bound(sum+i,sum+n+1,v+sum[i-1])-sum;
			if(sum[pos]-sum[i-1]>=v)suf[i]=suf[pos+1]+1;
		}
		if(pre[n]<m){
			cout<<"-1\n";
			continue;
		}
		int j=1,ans=0;
		for(int i=0;i<n;i++){
			while(j<=n&&pre[i]+suf[j+1]>=m)++j;
			if(pre[i]+suf[j]>=m)
				ans=max(ans,sum(i,j-1));
		}
		cout<<ans<<"\n";
	}
	return 0;
}

````

---

## 作者：Yxy7952 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF2028C)

## 题目大意

你需要把有 $n$ 个数的序列分为 $m$ 或者 $m+1$ 个连续的子序列。**要求**：每一个子序列中的数字之和需要大于等于 $v$。

如果能这样分配序列，并且有 $m+1$ 的一个子序列，输出这些子序列的和中最大是多少（当只有 $m$ 个子序列时，输出 ```0```）。

否则，输出 ```-1```。

## 思路

这道题显然是**二分答案**。

二分答案，之所以有**答案**两个字，就是因为其一般枚举所求问题的结果。

但是我们发现，我们只二分最大值的话，不确定他是哪一个区间，也就是不知道区间的左端点和右端点，比如 $2 ~1~1~1~3$。

对于这个序列，如果二分的值为 $2$（先不考虑正确性），那区间的左端点和右端点有两种情况。

$\begin{cases}
  l=1,r=1\\
  l=2,r=3\\
\end{cases}$

显然，这对答案是有影响的。

所以，我们必须枚举其中一个端点，这里枚举 $l$。

考虑判断函数 check。如果 Alice 可以获得区间 $[l,r]$ 则 $[1,l - 1]$ 和 $[r + 1 , n]$ 加起来可供 $m$ 个生物。

这可以使用两个数组 $q_i,nxt_j$ 分别表示 $[1 , i]$ 的食物中最多可供的生物数，和 $[j , n]$ 的食物中最多可供的生物数。他们能在 $O(n)$ 预处理后 $O(1)$ 直接使用。

直接展示代码，所有要注意的细节以及问题都体现在注释中。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 200005 ; 
ll n , m , v , ans = 0 ; 
ll a[N] , s[N] ; 
ll q[N] , nxt[N] ; 
void Main(){
	cin >> n >> m >> v ; 
	for(int i = 1 ; i <= n ; i++){
		cin >> a[i] ; 
		s[i] = s[i - 1] + a[i] ; //这里用前缀和优化求区间和.
	}
	ll sum = 0 ; 
	for(int i = 1 ; i <= n ; i++){
		sum += a[i] , q[i] = q[i - 1] ; 
		if(sum >= v) q[i]++ , sum = 0 ; 
	}
	sum = 0 ; 
	for(int i = n ; i >= 1 ; i--){
		sum += a[i] , nxt[i] = nxt[i + 1] ; 
		if(sum >= v) nxt[i]++ , sum = 0 ; 
	}
	if(q[n] < m){
		cout << "-1\n" ; 
		return ; 
	}
	//只有当整个序列不能分成 m 个和大于等于 v 的子序列时输出 -1。 
	for(int i = 1 ; i <= n ; i++){
		int l = i , r = n ; 
		while(l <= r){
			int mid = l + r >> 1 ; 
			if(q[i - 1] + nxt[mid + 1] >= m) ans = max(ans , s[mid] - s[i - 1]) , l = mid + 1 ;
            //通过这里 if 语句的条件可以看出 i 是我们暴力枚举的 Ailce 获得食物的区间左端点 l，
            //而这里的 l 和 r 只是在二分查找符合要求的最大右端点，所以 mid 才是 Ailce 获得食物的区间右端点 r。
			else r = mid - 1 ; 
		}
	}
	cout << ans << "\n" ; 
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int T ; 
	cin >> T ; 
	while(T--) ans = 0 , Main() ; 
	return 0;
}
```

---

## 作者：panxz2009 (赞：2)

全机房 VP 碰到的。

考虑枚举我们要最大化的那一段的左端点 $l$。

要使这一段最大化，右端点 $r$ 在合法的前提下自然越远越好，所以题目就可以转化为：对于一个固定的 $l$，找到最大的 $r$，使得 $1$ 到 $l-1$ 之间可以构造出的最多合法区间加上 $r+1$ 到 $n$ 之间可以构造出的最多合法区间数大于等于 $m$。

那么不妨设 $f_i$ 表示从 $1$ 到 $i$ 可以构造出的最多合法区间数，$g_i$ 表示从 $i$ 到 $n$ 可以构造出的最多合法区间数。求这两个东西显然是等价的，只考虑 $f_i$。显然记录一个临时变量 $sum$，然后直接递推，递推到第 $i$ 个点时，$sum$ 加上 $a_i$，如果 $sum$ 小于 $v$，那么 $f_i=f_{i-1}$，否则 $f_i=f_{i-1}+1$，并将 $sum$ 清空。求 $g_i$ 倒过来就行。

发现 $f_i$ 单调递增，$g_i$ 单调递减，那么双指针就可以快速找到右端点 $r$。

时间复杂度 $\mathcal O(n)$。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 2e5 + 10, inf = 1e18;
int n, m, v, f[maxn], g[maxn], a[maxn], s[maxn], ans;
void solve() {
	scanf("%lld%lld%lld", &n, &m, &v);
	for(int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		s[i] = s[i - 1] + a[i];
	}
	f[0] = 0;
	int sum = 0;
	for(int i = 1; i <= n; i++) {
		sum += a[i];
		f[i] = f[i - 1];
		if(sum >= v) {
			f[i]++;
			sum = 0;
		}
	}
	g[n + 1] = 0, sum = 0;
	for(int i = n; i >= 1; i--) {
		sum += a[i];
		g[i] = g[i + 1];
		if(sum >= v) {
			g[i]++;
			sum = 0;
		}
	}
//	for(int i = 1; i <= n; i++) {
//		printf("%d %d\n", f[i], g[i]);
//	}
	if(f[n] < m) {
		puts("-1");
		return;
	}
	ans = 0;
	for(int l = 0, r = 0; l <= n; l++) {
		while(r <= n && f[l] + g[r + 1] >= m) r++;
		ans = max(ans, s[r - 1] - s[l]);
	}
	printf("%lld\n", ans);
}
signed main() {
	int T;
	scanf("%lld", &T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：PeppaPig_qwq (赞：1)

首先，Alice 选取的蛋糕一定是一段连续区间。设区间为 $[l,r]$。不难发现，当 $l$ 递增时，$r$ 也会递增。预处理出 $pre_i$ 表示前 $i$ 个蛋糕能分成多少个美味值大于 $v$ 的区间，和 $suf_i$ 表示后 $i$ 个蛋糕能分成多少个美味值大于 $v$ 的区间。使用双指针寻找即可。

---

