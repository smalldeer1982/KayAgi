# [ABC216F] Max Sum Counting

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc216/tasks/abc216_f

長さ $ N $ の数列 $ A\ =\ (A_1,\ \dots,\ A_N),\ B\ =\ (B_1,\ \dots,\ B_N) $ が与えられます。$ \{1,2,\ldots,N\} $ の空でない部分集合 $ S $ であって、以下の条件を満たすものの個数を数えてください。

- $ \max_{i\ \in\ S}\ A_i\ \geq\ \sum_{i\ \in\ S}\ B_i $

なお、答えは非常に大きくなることがあるため、$ 998244353 $ で割ったあまりを出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 5000 $
- $ 1\ \leq\ A_i,B_i\ \leq\ 5000 $
- 入力は全て整数

### Sample Explanation 1

$ \{1,2,\ldots,N\} $ の空でない部分集合としてあり得るものは、$ \{1\} $, $ \{2\} $, $ \{1,2\} $ の $ 3 $ 通りです。 - $ S=\{1\} $ のとき $ \max_{i\ \in\ S}\ A_i=3 $, $ \sum_{i\ \in\ S}\ B_i=1 $ - $ S=\{2\} $ のとき $ \max_{i\ \in\ S}\ A_i=1 $, $ \sum_{i\ \in\ S}\ B_i=2 $ - $ S=\{1,2\} $ のとき $ \max_{i\ \in\ S}\ A_i=3 $, $ \sum_{i\ \in\ S}\ B_i=3 $ であるため、問題文中の条件、即ち $ \max_{i\ \in\ S}\ A_i\ \geq\ \sum_{i\ \in\ S}\ B_i $ を満たす $ S $ は $ \{1\} $ と $ \{1,2\} $ の $ 2 $ 通りです。

### Sample Explanation 2

条件を満たす $ S $ が存在しない場合もあります。

## 样例 #1

### 输入

```
2
3 1
1 2```

### 输出

```
2```

## 样例 #2

### 输入

```
2
1 1
2 2```

### 输出

```
0```

## 样例 #3

### 输入

```
20
1937 3980 2689 1208 3640 1979 581 2271 4229 3948 3708 1522 4161 4661 3797 96 3388 3395 2920 2247
4485 2580 174 1156 3770 3396 3558 3500 3494 479 269 3383 1230 1711 3545 3919 134 475 3796 1017```

### 输出

```
476```

# 题解

## 作者：liuruian (赞：5)

### 思路
1.  排序，从大到小，以保证遍历到 $i$ 点时 $a_i$ 的值为 $i$ 之前 $a$ 值最大的。
2.  对 $b$ 数组背包，到 $i$ 点时加上贡献。
### 总结
排序，再背包，时间复杂度是 $O(n^2)$ 的。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 5005
#define md 998244353
int n,dp[N][N],ans;
struct num{ll a,b;}nm[N];
bool cmp(num a,num b){return a.a<b.a;}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>nm[i].a;
	for(int i=1;i<=n;i++) cin>>nm[i].b;
	sort(nm+1,nm+n+1,cmp);//排序
	dp[0][0]=1;
	for(int i=1;i<=n;i++){
		dp[i][0]=1;
		for(int j=0;j<=nm[i].a-nm[i].b;j++) ans=(ans+dp[i-1][j])%md;//加上贡献
		for(int j=nm[i].b;j<=5000;j++) dp[i][j]=(dp[i][j]+dp[i-1][j-nm[i].b])%md;
		for(int j=1;j<=5000;j++) dp[i][j]=(dp[i][j]+dp[i-1][j])%md;
	}//背包
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：wangyibo201026 (赞：3)

## 前言

这道题目大概想了 $10$ 分钟就做出来了，同机房同学一个说用双指针，一个说用 ST 表，真就只我这么菜？

~~结果一个看错题目，一个发现不用。~~

话说真是自己想出来的 DP。

## 正解

首先考虑求 $\max$ 的问题，这个问题明显可以排序去扫，此时扫到的数就是最大值。

那么我们此时再把 $b$ 按照 $a$ 排序，此时我们发现对于每一个 $i$ 在 $1 \sim n$，要求的东西就是 $b$ 的前 $i$ 位有多少个子集的和大于 $a_i$，发现这个东西好像可以扫过去求，于是考虑 DP。

考虑按照求的东西设，设 $f_{i, j}$ 为 $b$ 的前 $i$ 位有多少个子集和大于 $j$，不难推出：

$$f_{i, j} = \sum_{k = 0}^{j - a_i} f_{i - 1, k}$$

发现这个东西的复杂度是 $O(n^3)$ 的，所以我们可以对这个东西前缀和优化，优化到 $O(n^2)$，如果你对空间追求极致，那么你可以使用滚动数组优化，空间复杂度 $O(n)$。

## 代码

本人代码为了接地气，没有采用滚动数组：

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

#define fir first
#define sec second
#define lep( i, l, r ) for ( int i = ( l ); i <= ( r ); i ++ )
#define rep( i, r, l ) for ( int i = ( r ); i >= ( l ); i -- )
#define gep( i, x ) for ( int i = head[( x )]; i; i = edges[i].next)

char _c; bool _f; template < class T > inline void read ( T &x ) {
	_f = 0, x = 0;
	while ( _c = getchar (), !isdigit (_c) ){
		if ( _c == '-' ) { _f = 1; }
	}
	while ( isdigit (_c) ){
		x = x * 10 + _c - '0', _c = getchar ();
		if (_f) { x = -x; }
	}
}

const int N = 5005;
const int mod = 998244353;

int n, ans;
int sum[N], f[N][N];

struct Node { int x, y; } a[N];

bool cmp ( Node x, Node y ) {
	return x.x < y.x;
}

signed main () {
	cin >> n;
	lep ( i, 1, n ) {
		cin >> a[i].x;
	}
	lep ( i, 1, n ) {
		cin >> a[i].y;
	}
	sort ( a + 1, a + 1 + n, cmp );
	sum[0] = 1;
	lep ( i, 1, n ) {
		lep ( j, a[i].y, 5000 ) {
			f[i][j] = sum[j - a[i].y];
		}
		lep ( j, a[i].y, 5000 ) {
			sum[j] += f[i][j];
			sum[j] %= mod;
		}
		lep ( j, 0, a[i].x ) {
			ans += f[i][j];
			ans %= mod;
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：xpigeon (赞：2)

# 排序加背包

题目中最核心的条件:

$$\max_{i \in S} a_i \geq \sum_{i \in S} b_i$$

其中 $\max_{i \in S} a_i$ 这个条件，**我们可以考虑对所有元素按 $a$ 进行从小到大排序。**

这样做的好处：

设当前扫的元素的 $a$ 值为 $a_i$。

此时 $a_i$ 一定是在已选中的元素形成的集合里的最大值，于是我们就可以直接愉快地对 $a_i$ 统计答案啦。

至于为什么能想到这一步，道理也很简单：如果有一个 $a$ 值更大的元素，加入集合，那此时集合就不会对当前扫到的 $a_i$ 产生贡献了。

**接下来贡献的计算我们可以使用背包来做：**

设 $dp[j]$ 表示当前所选元素形成的集合中，$\sum_{i \in S} b_i=j$ 的方案数，那么往后扫的时候每次把 $b_i$ 的贡献加进去就好了。

统计时遍历到体积 $j$，如果满足 $a_i\geq j$，那么说明满足条件。但我们如何保证 $a_i$ 在当前的集合里呢？

**最后一步小转换**：只需统计 $dp[j-b_i]$ 即可，代表着第 $i$ 个元素存在于集合中时，能形成剩余体积的方案数。

总时间复杂度 $O(n^2)$。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
int n;
struct S{
	int a,b;
}s[5005];
int dp[5005];
int ans=0;
bool cmp(S x,S y){
	return x.a<y.a;
}
void xpigeon(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i].a;
	}
	for(int i=1;i<=n;i++){
		cin>>s[i].b;
	}
	sort(s+1,s+n+1,cmp);
	dp[0]=1;
	for(int i=1;i<=n;i++){
		for(int j=5000;j>=s[i].b;j--){
			dp[j]=(dp[j]+dp[j-s[i].b])%mod;
			if(s[i].a>=j){
				ans=(ans+dp[j-s[i].b])%mod;
			}
		}
	}
	cout<<ans;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	xpigeon();
}
```

---

## 作者：WaterSun (赞：1)

# 思路

首先，不难发现，对于本题将 $a,b$ 合成一个序列，并按照 $a_i$ 排序的答案不会发生变化。所以，我们可以直接排序，那么，我们当前枚举到的 $a_i$ 就是当前的 $\max(a_i)$。

定义 $dp_{i,j,0/1}$ 表示在 $1 \sim i$ 中，选择的 $b_i$ 之和为 $j$，并且第 $i$ 个数 不选/选 的方案数。

不难得出状态转移方程：

$$
\left\{\begin{matrix}
dp_{i,j,0} = dp_{i - 1,j,0} + dp_{i - 1,j,1} \\
dp_{i,j,1} = dp_{i - 1,j - b_i,0} + dp_{i - 1,j - b_i,1}
\end{matrix}\right.
$$

然后来考虑一下 $i,j$ 的边界问题，$i$ 明显是 $1 \leq i \leq n$，而 $j$ 要满足 $\sum_{k}b_k \leq \max(a_k)$ 的条件，所以 $j$ 不能大于 $\max(a_i)$，由此，$1 \leq j \leq \max(a_i)$。

递推起点为：$dp_{0,0,0} = 1$。答案为 $\sum_{i = 1}^n\sum_{j = 1}^{a_i}dp_{i,j}$。

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define fst first
#define snd second
#define re register

using namespace std;

typedef pair<int,int> pii;
const int N = 5010,mod = 998244353;
int n,ans;
int dp[N][N][2];
pii arr[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 1) + (r << 3) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

signed main(){
	dp[0][0][0] = 1;
	n = read();
	for (re int i = 1;i <= n;i++) arr[i].fst = read();
	for (re int i = 1;i <= n;i++) arr[i].snd = read();
	sort(arr + 1,arr + n + 1);
	for (re int i = 1;i <= n;i++){
		for (re int j = 0;j <= arr[n].fst;j++){
			dp[i][j][0] = (dp[i - 1][j][0] + dp[i - 1][j][1]) % mod;
			if (j >= arr[i].snd) dp[i][j][1] = (dp[i - 1][j - arr[i].snd][0] + dp[i - 1][j - arr[i].snd][1]) % mod;
		}
	}
	for (re int i = 1;i <= n;i++){
		for (re int j = 1;j <= arr[i].fst;j++) ans = (ans + dp[i][j][1]) % mod;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：liyuteng (赞：0)

## 题目分析

首先，最直接的想法是使用 $O(2^n)$ 的暴力枚举，即枚举每一个数字选与不选的情况。

## 优化思路

观察到 $1 \leq a_i \leq 5000$，所以最大值的范围很小，可以考虑使用动态规划（DP）来优化。

## 限制条件

问题中有一个关键限制条件：**在选中的集合 $S$ 中，$a_i$ 的最大值必须大于等于 $b_i$ 的总和**，即：
$$
\max_{i \in S} a_i \geq \sum_{i \in S} b_i
$$

为了快速计算当前选中的集合中 $a_i$ 的最大值，我们可以考虑将数组排序。

## 排序与背包

将数组按照 $a_i$ 升序排序后，对 $b$ 数组进行背包动态规划。在统计答案时，只有选择了当前 $b_i$ 的方案才会被统计。我们可以认为一个方案仅在其最后一个数字（排序后 $a_i$ 最大的位置）上被统计，这样可以避免同一种方案被重复计算的情况。

## 代码实现


```cpp
#include<bits/stdc++.h>
#define mod 998244353
#define int long long
#define N 5050
using namespace std;
struct node {
    int x, y;
} a[N * 2];
int dp[N];
bool cmp(node a, node b) {
    return a.x < b.x;
}
signed main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x;
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i].y;
    }
    sort(a + 1, a + 1 + n, cmp);
    dp[0] = 1;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 5000; j >= a[i].y; j--) {
            dp[j] = (dp[j] + dp[j - a[i].y]) % mod;
            if (j <= a[i].x)
                ans = (ans + dp[j - a[i].y]) % mod;
        }
    }
    cout << ans % mod << endl;
    return 0;
}

---

## 作者：wth2026 (赞：0)

# 题目思路
~~非常高级，以至于场切失败……~~

一道非常好的动态规划题。

考虑状态：
- $f_{j,0/1}$ 表示当前 $b$ 的和为 $j$，且当前点选还是不选的方案数。

考虑转移：
- 先将所有的 $a$ 按从小到大绑定 $b$ 排序。
- 对于每一个 $1 \leq i \leq n$，枚举每一个 $0 \leq j \leq 5 \times 10^3$：
  - 如果有 $b_i + j \leq a_i$，则 $f_{b_i + j, 1}=f_{b_i + j, 1}+f_{j, 0}+f_{j,1}$；
  - 否则，如果 $b_i + j$ 不超过范围，则 $f_{b_i + j, 0}=f_{b_i + j, 0}+f_{j, 0}+f_{j,1}$。

考虑答案表示：
- 答案可以表示为 $\sum_{i=1}^{5 \times 10^3}f_{i,0}$。

[AC Code](https://atcoder.jp/contests/abc216/submissions/58263006)

---

## 作者：orson111 (赞：0)

## 前言
But it's so obvious! There's a $\max$ in the equation!

## 正片开始
我们发现不等式的左边是个 $\max$，然后右边的加法有交换律，由此便想到排序。

接着我们执行 $\texttt{DP}$，定义 $f_{i,j}$ 是前 $i$ 个数中选一个集合 $S$ 满足 $(\sum_{i \in S}b_i) \le j$ 的方案数，注意可以为空！

最后计算时累加 $f_{i-1,a_i-b_i}$ 就可以了，具体见代码。

## 上代码！
直接复制将会受到评测姬的惩罚！
```cpp
#include<bits/stdc++.h>
#include<atcoder/modint>
using namespace std;
using namespace atcoder;
using mint=modint998244353;
typedef long long ll;
const ll N=5009;
ll n,mx;
mint f[N][N],ans;
struct node{ll a,b;} x[N];
bool cmp(node _x,node _y){return _x.a<_y.a;}
int mian(){
    cin>>n;
    for(ll i=1;i<=n;i++) cin>>x[i].a,mx=max(mx,x[i].a);
    for(ll i=1;i<=n;i++) cin>>x[i].b;
    sort(x+1,x+n+1,cmp);
    f[0][0]=1;
    for(ll i=1;i<=n;i++)
        for(ll j=0;j<=mx;j++)
            f[i][j]=f[i-1][j]+(j>=x[i].b?f[i-1][j-x[i].b]:0);
    for(ll i=0;i<=n;i++)
        for(ll j=1;j<=mx;j++)
            f[i][j]+=f[i][j-1];
    for(ll i=l;i<=n;i++){
        if(x[i].a<x[i].b) continue;
        ans+=f[i-1][x[i].a-x[i].b];
    }
    cout<<ans.val()<<endl;
    return 0;
}
```

---

## 作者：ttq012 (赞：0)

诈骗。

首先选出来的所有 $b_i$ 的和必然不超过 $\max a_i\le 5000$。

所以就可以直接 dp 了。~~Atcoder 是诈骗犯！~~

设 $f_{i,j,0/1}$ 表示前 $i$ 个数选出了数的和是 $j$，并且第 $i$ 个数选/不选。

很显然如果不选择的话，有 $f_{i,j,0}=f_{i-1,j,0}+f_{i-1,j,1}$。

如果选择的话就类似于背包问题，$f_{i,j,1}=f_{i-1,j-b_i,0}+f_{i-1,j-b_i,1}$。

初始条件有 $f_{0,0,0}=1$。

需要注意边界情况。

答案很好算，只需要把所有的答案累加起来即可。

时间复杂度为 $O(n^2)$。

这破题细节真多。

---

## 作者：Symbolize (赞：0)

# $\tt{Solution}$

根据我们教练所告诉我们的，遇到这种序列顺序不会影响计算的题，先排序再说，所以我们考虑将 $a$ 数组与 $b$ 数组放在一起，以 $a$ 的大小为第一关键字排序。此时我们发现，如果以 $a_i$ 为此最大值，只能够选择下标小于 $i$ 的组合，那么就可以考虑动态规划了。首先我们状态定义，$f_{i,j}$ 表示，在前 $i$ 个数中选择若干个 $b$ 数组的数，使得它们的和等于 $j$ 的方案数量。接着我们发现 $i$ 每加 $1$，都只需要考虑是否加入当前这个元素。所以就有状态转移方程 `f[i][j]=f[i-1][j]+f[i-1][j-x[i].y];`，打代码时需要注意判断边界，最后需要统计答案，枚举一遍 $n$ 我们发现 $i$ 必须选，所以 $i$ 的贡献应该为 $\sum\limits_{j=0}^{a_i-b_i} f_{i-1,j}$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(register int i=l;i<=r;++i)
#define rep2(i,l,r) for(register int i=l;i>=r;--i)
const int N=5e3+10;
const int mod=998244353;
using namespace std;
int n,f[N][N],ans;
pii x[N];
signed main()
{
	cin>>n;
	rep1(i,1,n) cin>>x[i].x;
	rep1(i,1,n) cin>>x[i].y;
	sort(x+1,x+n+1);//排序
	rep1(i,0,n) f[i][0]=1;//dp起点
	rep1(i,1,n) rep1(j,1,N-5)/*范围最多到a[i]的极限即5000*/ f[i][j]=(f[i-1][j]+((j-x[i].y>=0)?f[i-1][j-x[i].y]:0))%mod;//状态转移方程
	rep1(i,1,n) rep1(j,0,x[i].x-x[i].y) ans=(ans+f[i-1][j])%mod;//统计答案
	cout<<ans<<endl;//输出
	return 0;
}

```

---

## 作者：AlicX (赞：0)

## Solution 

集合问题，首先必须找到一个关键点进行讨论，此题的关键点就是集合中的最大值。为了满足单调性方便做，所以我们把 $a$ 数组和 $b$ 数组绑在一起，以 $a_i$ 为关键字排序。这样，当我们枚举到 $i$ 时，最大值便为 $a_i$。然后我们定义 $f_{i,j,k}$ 表示前 $i$ 个数中，选择了某个集合，其中 $b$ 数组的和为 $j$，且 $a_i$ 是否选择。状态转移方程：$f_{i,j,0}=f_{i-1,j,0}+f_{i-1,j,1}$，$f_{i,j,1}=f_{i-1,j-b_i,0}+f_{i-1,j-b_i,1}$。答案也很显然，为了防止重复，我们只累加 $f_{i,j,1}$ 的值。 

```cpp
#include<bits/stdc++.h>
#define int long long 
#define x first 
#define y second
#define il inline
#define debug() puts("-------") 
using namespace std; 
typedef pair<int,int> pii; 
const int N=5010,Mod=998244353,INF=1e9+7; 
int n; 
pii a[N]; 
int f[N][N][2]; 
signed main(){ 
//	freopen("ball.in","r",stdin); 
//	freopen("ball.out","w",stdout); 
	cin>>n; int ans=0; f[0][0][0]=1; 
	for(int i=1;i<=n;i++) cin>>a[i].x; 
	for(int i=1;i<=n;i++) cin>>a[i].y; 
	sort(a+1,a+n+1); 
	for(int i=1;i<=n;i++){ 
		for(int j=0;j<=a[n].x;j++){ 
			f[i][j][0]=(f[i-1][j][0]+f[i-1][j][1])%Mod; 
			if(j>=a[i].y) f[i][j][1]=(f[i-1][j-a[i].y][0]+f[i-1][j-a[i].y][1])%Mod; 
		} 
	} for(int i=1;i<=n;i++) for(int j=0;j<=a[i].x;j++) ans=(ans+f[i][j][1])%Mod; cout<<ans<<endl; 
	return 0; 
} /* 
5 4
3 
1 5 4 
2 
2 5 
3
3 4 1
2
2 3 
*/
```


---

## 作者：loser_seele (赞：0)

首先观察到 $ \max $ 有单调性，不难想到可以枚举 $ A $ 的最大值的取值。

于是先将数组以 $ A $ 为第一关键字，$ B $ 为第二关键字排序，问题转化为了有多少种方案选取 $ B $ 的一个子集，设这个问题的答案为 $ f(i,j) $，表示前 $ i $ 个元素选取后和恰好为 $ j $。则原问题答案显然为 $ \sum_{i=1}^n\sum_{j=0}^{A_i-B_i}f(i-1,j) $。观察到 $ f(i,j) $ 最多只有 $ n \times \max{a_i} $ 种不同的取值，直接朴素 dp 转移即可，转移方程见代码。

总时间复杂度为状态数 $ \mathcal{O}(n \times \max{a_i}) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
pair<int,int>a[5005];
int n;
int mod=998244353;
int dp[5005][5005],sum[5005];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i].first);
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i].second);
	sort(a+1,a+n+1);
	sum[0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=a[i].second;j<=5000;j++)
		dp[i][j]=sum[j-a[i].second];
		for(int j=a[i].second;j<=5000;j++)
		sum[j]=(sum[j]+dp[i][j])%mod;
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	for(int j=0;j<=a[i].first;j++)
	ans=(ans+dp[i][j])%mod;
	printf("%d",ans);
}
```


---

## 作者：卡卡卡卡卡卡 (赞：0)

## 题解：
考虑 ``dp``，先以 $A_i$ 为关键字排序，使 $\displaystyle\max_{i\in S} A_i$，不严格递增。

设 $f_{i,j,0/1}$ 表示在前 $i$ 个数中，选出的 $\displaystyle\sum_{i\in S} B_i$ 为 $j$，第 $i$ 个数选或不选。

则有方程：
$$\begin{cases}f_{0,0,0}=1\\f_{i,j,0}=f_{i-1,j,0}+f_{i-1,j,1}\\
f_{i,j,1}=f_{i-1,j-B_i,0}+f_{i-1,j-B_i,1}(j\geq B_i)\end{cases}$$
答案为：
$$\displaystyle\sum_{i=1}^{n}\displaystyle\sum_{j=0}^{A_i}f_{i,j,1}$$
## code：

```cpp
#include<bits/stdc++.h> 
using namespace std; 
const long long mod=998244353; 
long long n,f[5005][5005][2],ans; 
struct node
{
	long long a,b;
}t[5005];
bool cmp(node x,node y) {return x.a<y.a;}
int main()
{ 
	cin>>n; 
	f[0][0][0]=1; 
	for(long long i=1;i<=n;i++) cin>>t[i].a; 
	for(long long i=1;i<=n;i++) cin>>t[i].b; 
	sort(t+1,t+n+1,cmp); 
	for(long long i=1;i<=n;i++)
		for(long long j=0;j<=t[n].a;j++)
		{ 
			f[i][j][0]=(f[i-1][j][0]+f[i-1][j][1])%mod; 
			if(j>=t[i].b) f[i][j][1]=(f[i-1][j-t[i].b][0]+f[i-1][j-t[i].b][1])%mod; 
		}
	for(long long i=1;i<=n;i++) 
		for(long long j=0;j<=t[i].a;j++) 
		{
			ans=(ans+f[i][j][1])%mod; 
		}
	cout<<ans;
}
```

---

