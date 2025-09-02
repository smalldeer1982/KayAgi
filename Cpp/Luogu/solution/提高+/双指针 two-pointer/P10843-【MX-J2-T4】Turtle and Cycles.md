# 【MX-J2-T4】Turtle and Cycles

## 题目背景

原题链接：<https://oier.team/problems/J2E>。

## 题目描述

给你一个环形的 $0 \sim n - 1$ 的**排列** $a_0, a_1, \ldots, a_{n - 1}$。

一次操作你可以选择一个整数 $i \in [0, n - 1]$，把 $a_i$ 赋值成 $a_{(i - 1) \bmod n} + a_{(i + 1) \bmod n} - a_i$。

一个位置 $i \in [0, n - 1]$ 是好的当且仅当 $a_{(i - 1) \bmod n} < a_i$ 且 $a_{(i + 1) \bmod n} < a_i$。

环形序列 $a$ 是好的当且仅当存在**恰好**一个位置 $i \in [0, n - 1]$ 使得位置 $i$ 是好的。

求至少要进行多少次操作能让 $a$ 变成好的。可以证明一定有解。

## 说明/提示

#### 【样例解释】

在第一组数据中，初始序列恰好存在一个好的位置 $i = 0$，所以答案为 $0$。

在第二组数据中，可以选择 $i = 2$ 操作，操作后序列变为 $a = [2, 3, 7, 4, 1]$。此时序列恰好存在一个好的位置 $i = 2$，所以答案为 $1$。

#### 【数据范围】

**本题采用捆绑测试且开启子任务依赖。**

| 子任务编号 | 分值 | $n \le$ | $\sum n \le$ | 特殊性质 | 子任务依赖 |
| :-: | :-: | :-: | :-: | :-: | :-: |
| $1$ | $19$ | $6$ | $10^4$ | 无 | 无 |
| $2$ | $14$ | $12$ | $10^4$ | 无 | $1$ |
| $3$ | $27$ | $2 \cdot 10^3$ | $10^4$ | 无 | $1, 2$ |
| $4$ | $2$ | $2 \cdot 10^5$ | $2 \cdot 10^5$ | $a_i = i$ | 无 |
| $5$ | $38$ | $2 \cdot 10^5$ | $2 \cdot 10^5$ | 无 | $1, 2, 3, 4$ |

对于所有数据，满足 $1 \le T \le 10^4$，$2 \le n, \sum n \le 2 \cdot 10^5$，$0 \le a_i \le n - 1$，$a$ 是一个 $0 \sim n - 1$ 的排列。

## 样例 #1

### 输入

```
3
2
1 0
5
2 3 0 4 1
10
0 5 9 7 3 1 6 4 8 2
```

### 输出

```
0
1
5
```

# 题解

## 作者：_LSA_ (赞：19)

# Solution

考虑每操作一次对序列的大小关系会造成什么影响。

考虑相邻三个数 $x,y,z$。

若 $x<y<z$，对 $y$ 操作后仍然 $x<y<z$；

若 $x>y>z$，对 $y$ 操作后仍然 $x>y>z$；

若 $x>y<z$，对 $y$ 操作后则 $x<y>z$；

若 $x<y>z$，对 $y$ 操作后则 $x>y<z$。

证明代入 $y=x+z-y$ 即可。

为了方便，我们把小于号记作数字 $0$，大于号记作数字 $1$。

那么原序列我们可以根据大小关系转换成一个由 $01$ 构成的环（设原序列为 $\{a_n\}$ 转换后的序列为 $\{b_n\}$，则 $b_i=[a_i>a_{(i+1)  \mod n}]$）。

比如样例第三个点 $0,5,9,7,3,1,6,4,8,2$ 就可以转换成 $0011101011$。

我们发现上面四种操作实质上对应着交换转换后环形序列的相邻两个数。

那么题意就转化为给定一个由 $01$ 构成的环，每次操作可以交换相邻两个数，求多少次操作能把所有的 $0$ 连在一起，所有的 $1$ 连在一起。

断环成链，那么就问题等价于求把一些 $1$ 移到最左边，一些 $1$ 移到最右边的最小操作次数最小值。

记序列的中点为 $mid$，我们把 $i \le mid$ 的 $1$ 移到左边，其他移到右边，我们发现一定存在一条边将它断开后形成的序列通过这种方式操作能得到最优的答案。

考虑如何实现，我们只需把转换后的数组复制一边在末尾，然后前缀和记录每 $1$ 的出现次数和下标和就能快速计算了。

时间复杂度 $O(n)$。

# Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int> 
#define mk make_pair
#define fi first
#define se second
using namespace std;
ll read(){
    ll X = 0,r = 1;
    char ch = getchar();
    while(!isdigit(ch) && ch != '-') ch = getchar();
    if(ch == '-') r = -1,ch = getchar();
    while(isdigit(ch)) X = X*10+ch-'0',ch = getchar();
    return X*r;
}
const int N = 4e5+10;
int n,a[N],b[N];
ll cnt[N],sum[N];
int main(){
  int T = read();
  while(T--){
      n = read();
      for(int i=1;i<=n;i++) a[i] = read();
      a[n+1] = a[1];
      ll ans = 1e18;
      for(int i=1;i<=n;i++){
          if(a[i] < a[i+1]) b[i] = 0;
          else b[i] = 1;
      }
      for(int i=1;i<n;i++) b[i+n] = b[i];
      for(int i=1;i<2*n;i++)
          cnt[i] = cnt[i-1]+b[i],sum[i] = sum[i-1]+b[i]*i;
      int len = (n+1)/2;
      for(int i=1;i<=n;i++){
          ll sz1 = cnt[i+len-1]-cnt[i-1],sz2 = cnt[i+n-1]-cnt[i+len-1];
          ll ct1 = sum[i+len-1]-sum[i-1],ct2 = sum[i+n-1]-sum[i+len-1];
          sz1 = (i+i+sz1-1)*sz1/2; sz2 = (i+n-1-sz2+1+i+n-1)*sz2/2;
          ans = min(ans,ct1-sz1+sz2-ct2);
      }
      cout << ans << "\n";
    }
    return 0;
}

```

---

## 作者：EuphoricStar (赞：10)

设 $b_i = a_{(i + 1) \bmod n} - a_i$，那么一次操作相当于交换 $b_i$ 和 $b_{(i + 1) \bmod n}$。序列是好的等价于 $b$ 中全部正数被换在一起。我们只关注 $b_i$ 的正负，所以让正数变成 $1$，负数变成 $0$。

那么原问题被转化成，一个环形 $01$ 序列，一次操作可以交换相邻两个元素，求全部 $1$ 被换在一起的最小操作次数。

设环上总共有 $k$ 个 $1$。先断环成链，此时链上有 $2k$ 个 $1$。枚举一个位置 $i$ 使得 $i$ 左边和右边的 $1$ 都尽量往中间靠。设 $p_j$ 为第 $j$ 个 $1$ 到中心（即位置 $i$）之间 $0$ 的个数。那么相当于求 $p_1, p_2, \ldots, p_{2k}$ 的前 $k$ 小值的和。

可以直接二分第 $k$ 小的值，可以通过算 $i$ 左边第 $x + 1$ 个 $0$ 和 $i$ 右边第 $x + 1$ 个 $0$ 之间 $1$ 的个数求出有多少个 $p_i \le x$。求出第 $k$ 小的值 $x$ 后，算 $p_i \le x - 1$ 的 $p_i$ 的和（可以通过计算值为 $1$ 的位置的前缀和实现）并设其为 $s$，设 $p_i \le x - 1$ 的 $i$ 个数为 $t$，那么这种交换方案的答案为 $s + (k - t) \cdot x$。

最终答案对所有交换方案的答案取 $\min$ 即可。

时间复杂度 $O(\sum n \log n)$，瓶颈在二分第 $k$ 小。也存在 $O(\sum n)$ 的做法，思路大体一样（？，把二分换成双指针即可。


```cpp
#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<ll, ll> pii;

const int maxn = 400100;

ll n, a[maxn], b[maxn], c[maxn], d[maxn], e[maxn];

void solve() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i]);
	}
	for (int i = 1; i < n; ++i) {
		b[i] = b[i + n] = (a[i] < a[i + 1]);
	}
	b[n] = b[n + n] = (a[n] < a[1]);
	int m = 0, cnt = 0;
	for (int i = 1; i <= n * 2; ++i) {
		if (b[i] == 0) {
			d[++m] = i;
		}
		cnt += (i <= n && b[i]);
		c[i] = c[i - 1] + b[i];
		a[i] = a[i - 1] + (!b[i]);
		e[i] = e[i - 1] + (b[i] ? a[i] : 0);
	}
	ll ans = 1e18;
	for (int i = 1; i < n * 2; ++i) {
		int k = upper_bound(d + 1, d + m + 1, i) - d - 1;
		int l = 0, r = n * 2, p = -1;
		while (l <= r) {
			int mid = (l + r) >> 1;
			int L = d[max(0, k - mid)], R = d[min(m, k + mid + 1)];
			if (c[R] - c[L] >= cnt) {
				p = mid;
				r = mid - 1;
			} else {
				l = mid + 1;
			}
		}
		if (!p) {
			puts("0");
			return;
		}
		l = d[max(0, k - p + 1)];
		r = d[min(m, k + p)];
		ll res = (cnt - (c[r] - c[l])) * p;
		res += a[i] * (c[i] - c[l]) - (e[i - 1] - (l ? e[l - 1] : 0));
		res += e[r] - e[i] - a[i] * (c[r] - c[i]);
		ans = min(ans, res);
	}
	printf("%lld\n", ans);
}

int main() {
	int T = 1;
	scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}

```

---

## 作者：Louis_1346 (赞：4)

## 【MX-J2-T4】Turtle and Cycles 题解

### 题目描述

给你一个环形的 $0 \sim n - 1$ 的**排列** $a_0, a_1, \ldots, a_{n - 1}$。

一次操作你可以选择一个整数 $i \in [0, n - 1]$，把 $a_i$ 赋值成 $a_{(i - 1) \bmod n} + a_{(i + 1) \bmod n} - a_i$。

一个位置 $i \in [0, n - 1]$ 是好的当且仅当 $a_{(i - 1) \bmod n} < a_i$ 且 $a_{(i + 1) \bmod n} < a_i$。

环形序列 $a$ 是好的当且仅当存在**恰好**一个位置 $i \in [0, n - 1]$ 使得位置 $i$ 是好的。

求至少要进行多少次操作能让 $a$ 变成好的。可以证明一定有解。

数据范围满足 $n\in[1,2\times10^5]$。

###  分析

首先，先看这样一个例子（也是样例）：$ \{ 2,3,0,4,1 \}$。对着个序列取差分数组后得到$\{ 1,-3,4,-3,1\}$。

然后我们会发现，只要差分数组满足负数和负数连在一起，整数和整数连在一起，就有且仅有一个位置的数比旁边两个位置的数大。

接着，对第3个数操作一下，两个序列分别变成 $\{ 2,3,0,-3,1\}$ 和 $\{ 1,-3,-3,4,1\}$。

发现了吗，在原数组进行一次操作，就相当于在差分数组里进行一次相邻两个数的交换。这个时候，把正数看成  $1$，负数看成 $0$，问题变成了对于一个 $0，1$ 序列，最少需要多少次交换把 $0，1$ 分别放在一起。

对于后面这个问题，先发现三个性质。

- 数组是环形的。
- 如果预处理出排名的前缀和，就可以 $O(1)$ 计算出最少的移动次数。
- 假设确定了最后 $1$ 的确切位置，则这个位置左边 $n/2$ 的位置的 $1$ 往右挪是最优的，右边的往左挪是最优的。

环形很好解决，只需要把数组整体复制一遍，放到原数组后面，然后枚举每一次 $1$ 的中心，然后把左右两边分别挪过来就可以了。

但是如何用排名计算移动次数？
![](https://cdn.luogu.com.cn/upload/image_hosting/knszlcxp.png)

以这个图为例，假设我们要把1到5中的 $1$ 全部挪到右边，于是算出现在的排名 $cnt = 1+3+4 = 8$，挪动后的排名 $sum=(5+3)\times3/2=12$。

每一次交换相当于把排名提高了 $1$，所以挪动的答案可以直接计算。

所以说，只需要枚举中心，分别计算左边的 $1$ 和右边的 $1$ 所需要的操作次数，最后取min就做完了。

最终的复杂度为 $O(n)$。当然也有 $O(n\log n)$ 的做法。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=4e5+10;
int arr[maxn],cmp[maxn];
int sum[maxn],cnt[maxn]; 
int a=0,b=0;
signed main(){
	int T;
	scanf("%lld",&T);
	while(T--){
//		memset(sum,0,sizeof(sum));
//		memset(cnt,0,sizeof(cnt));
//		memset(arr,0,sizeof(arr));
//		memset(cmp,0,sizeof(cmp));
		int n;
		scanf("%lld",&n);
		for(int i=1;i<=n;i++){
			scanf("%lld",&arr[i]);
			
		}
		arr[n+1]=arr[1];
		for(int i=1;i<=n;i++){
			if(arr[i+1]>arr[i]) cmp[i]=1;
			else cmp[i]=0;
			cmp[i+n]=cmp[i];
		}
//		for(int i=1;i<=2*n;i++){
//			printf("%lld ",cmp[i]);
//		}
//		printf("\n");
		for(int i=1;i<=2*n;i++){
			sum[i]=sum[i-1]+cmp[i],cnt[i]=cnt[i-1]+cmp[i]*i;
		}
//		for(int i=1;i<=2*n;i++){
//			printf("%lld ",sum[i]);
//		}
//		printf("\n");
//		for(int i=1;i<=n*2;i++){
//			printf("%lld ",cnt[i]);
//		}
//		printf("\n\n");
		int ans=0x3f3f3f3f3f3f3f3f;
		int len=(n+1)/2;
		for(int i=1;i<=n;i++){
			int a1=sum[i+len-1]-sum[i-1],a2=sum[i+n-1]-sum[i+len-1];
			int b1=cnt[i+len-1]-cnt[i-1],b2=cnt[i+n-1]-cnt[i+len-1];
			a1=((2*(i+len-1)-a1+1)*a1)/2,a2=((2*(i+len)+a2-1)*a2)/2;
//			printf("%lld %lld %lld %lld\n",a1,b1,a2,b2);
			ans=min(ans,a1-b1+b2-a2);
		}
//		printf("\n\n");
		printf("%lld\n",ans);
	}
}
```

---

## 作者：MnZnOIer (赞：3)

update：2025/01/18-修改几处笔误。

### 题意解析
我们令 $p_i=a_i-a_{(i+1)\bmod n}$，操作后：

$$\begin{aligned}p_i &=a_{(i-1)\bmod n}+a_{(i+1)\bmod n}-a_i-a_{(i+1)\bmod n} \\&=a_{(i-1)\bmod n}-a_i\end{aligned}$$

$$\begin{aligned}p_{i-1}&=a_{(i-1)\bmod n}-(a_{(i-1)\bmod n}+a_{(i+1)\bmod n}-a_i)\\&=a_i-a_{(i+1)\bmod n}\end{aligned}$$

观察可以发现，一次操作相当于交换相邻的两个差分数组的值。对于只有一个好的位置，他的两边的值都大于他，说明他左边的差分数组为正，右边的差分数组为负。并且要求只有一个这样的情况，就说明要把差分数组所有正数移到一起。

我们令正数为 $1$，负数为 $0$，这样我们就把问题转化成了：给定一个 01 串形成环，求最小要交换几次相邻的项使得所有正数在一起，所有负数在一起的最小代价。

我们可以贪心地令所有在中点左边的移动到最左边去，中点右边的一道最右边去，因为这是一个环，任何数都可以作为中点，我们需要先枚举在环上选取的区间。当前区间的第一个点为 $1$，我们可以令 $f_i$ 表示 $[1,i]$ 内的 $1$ 的个数，$g_i$ 表示 $[1,i]$ 内所有 $1$ 都移动到 $1$ 号位置的代价，$rg_i$ 表示 $[1,i]$ 内所有 $1$ 都移到 $n$ 号位置的代价。

我们先考虑区间 $[1,mid]$，我们可以先令所有的 $1$ 都移到 $1$ 号位置，再减去不必要的贡献。显然，并不需要都移到 $1$，我们把这些 $1$ 移到 $1,2,3\dots$，形成了一个等差数列，它的贡献为 $\frac{c\times (c-1)}{2}$，$c$ 表示 $1$ 的数量，把它减掉即可。再来考虑右边，右边也可以先把所有 $1$ 移到 $n$，再减去多算的等差数列。

现在回到代码中，处理一些细节：

1. 用前缀和计算 $f$ 和 $g$，后缀和计算 $rg$；

2. 因为我们虚拟 $1$ 为左端点 $l$，所以全都移到 $1$ 是还要减去 $l\times c$，$c$ 依旧表示 $1$ 的数量。

### 代码部分
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 4e5 + 5;
int T, n, a[N], t[N], s[N], c[N], rt[N], ans;
void solve ()
{
	ans = 1e18;
	cin >> n;
	for (int i = 1; i <= n; ++ i)cin >> a[i];
	a[n + 1] = a[1];
	for (int i = 1; i <= n; ++ i)c[i] = c[i + n] = a[i + 1] > a[i];
	for (int i = 1; i <= 2 * n; ++ i)s[i] = s[i - 1] + c[i], t[i] = t[i - 1] + c[i] * i;
    for (int i = 2 * n; i; -- i)rt[i] = rt[i + 1] + (2 * n - i + 1) * c[i];
	for (int i = 1; i <= n; ++ i)
	{
		int mid = i + (n >> 1) - 1;
        ans = min (ans, t[mid] - t[i - 1] - (s[mid] - s[i - 1]) * i - (s[mid] - s[i - 1] - 1) * (s[mid] - s[i - 1]) / 2 + rt[mid + 1] - rt[i + n] - (s[i + n - 1] - s[mid]) * (n - i + 2) - (s[i + n - 1] - s[mid] - 1) * (s[i + n - 1] - s[mid]) / 2);
	}
    cout << ans << '\n';
}
signed main ()
{
    ios::sync_with_stdio (0), cin.tie (0), cout.tie (0);
    cin >> T;
    while (T --)solve ();
    return 0;
}
```

---

## 作者：ZHR100102 (赞：2)

很典的修改转化为交换差分数组的 trick 运用。这个 trick 实际上在 NOIp2021 里出过一次了。

# 转化

首先，$a_{(i - 1) \bmod n} + a_{(i + 1) \bmod n} - a_i$ 是个很典的形式。设 $a_{(i - 1) \bmod n}=x,a_i=y,a_{(i + 1) \bmod n}=z$，那么 $a_i$ 处的原来的差分值为 $y-x$，$a_{(i + 1) \bmod n}$ 处的原来的差分值为 $z-y$。

修改后，$a_i$ 处的差分值变为 $x+z-y-x=z-y$，$a_{(i + 1) \bmod n}$ 处的差分值变为 $z-(x+z-y)=z-x-z+y=y-x$。所以对 $a_i$ 进行修改后相当于把 $a_i$ 与 $a_{(i + 1) \bmod n}$ 处的差分值交换了。

设 $b_i$ 表示 $a_i$ 处的差分值。

那么我们要让这个环满足条件，首先就得破环为链。拆成链之后，显然只能有一个地方满足 $b_i>0,b_{(i + 1) \bmod n}<0$。于是设 $b_i>0$ 时为 $1$，否则为 $0$，就可以先转化为 $01$ 串问题来解决。这个 $01$ 串合法的条件就是满足 $111\dots000\dots111$ 的形式。

# 贪心

接下来考虑如何最小化操作次数，不难发现，贪心移动时，对于在中间点左边的 $1$ 都必须移动到左边来，对于在中间点右边的 $1$ 都必须移动到右边来。那么如何快速计算这个值呢？

假设我们当前计算的区间为 $[l,r]$。

先考虑左半边的情况，设 $g_i$ 表示前 $i$ 个数里的 $1$ 的下标之和为多少，$f_i$ 表示前 $i$ 个数中 $1$ 的个数。如果先让这些 $1$ 全都移动到 $l$ 处，那么答案就是 $g_{mid}-g_{l-1}-l\times (f_{mid}-f_{l-1})$。

但是实际有些 $1$ 是不需要完全移动到 $l$ 处的，它们有些可以移动到 $l+1,l+2,l+3$ 等位置，这就需要减掉它们的贡献。而这些贡献显然构成一个等差数列，那么只需要求和一下就好了，多算的贡献即为 $\frac{(f_{mid}-f_{l-1}-1)\times (f_{mid}-f_{l-1})}{2}$。

左半边的答案就是 $g_{mid}-g_{l-1}-l\times (f_{mid}-f_{l-1})-\frac{(f_{mid}-f_{l-1}-1)\times (f_{mid}-f_{l-1})}{2}$。

右半边同理，就不写了。

时间复杂度 $O(n)$。

# 代码

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define lc (p<<1)
#define rc ((p<<1)|1)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pi;
int t,n,a[400005];
ll g[400005],f[400005],sg[400005];
bitset<400005>b;
ll cal()
{
    ll ans=0x3f3f3f3f3f3f3f3f;
    for(ll i=1;i<=n;i++)
    {
        int mid=i+n/2-1;
        ll lk=f[mid]-f[i-1];
        ll lres=g[mid]-g[i-1]-lk*i-(lk-1)*lk/2;
        ll rk=f[i+n-1]-f[mid];
        ll rres=sg[mid+1]-sg[i+n]-rk*(2*n-(i+n-1)+1)-(rk-1)*rk/2;
        ans=min(ans,lres+rres);
    }
    return ans;
}
void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        a[i+n]=a[i];
    }
    for(int i=2;i<=n+1;i++)
    {
        b[i-1]=(a[i]>a[i-1]);
        b[i-1+n]=b[i-1];
    }
    for(int i=1;i<=2*n;i++)
    {
        f[i]=f[i-1]+b[i];
        g[i]=g[i-1]+i*b[i];
    }
    sg[2*n+1]=0;
    for(int j=1,i=2*n;i>=1;i--,j++)sg[i]=sg[i+1]+j*b[i];
    cout<<cal()<<'\n';
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>t;
    while(t--)solve();
    return 0;
}
```

---

## 作者：Hadtsti (赞：2)

### 题目分析

感觉不到蓝，绿差不多。

把 $a_i$ 赋值成 $a_{(i-1)\bmod n}+a_{(i+1)\bmod n}-a_i$，这一操作直接看貌似没什么好的性质。我们观察到里面包含了相邻两项的差，不妨将原序列差分分析。

设 $b_i=a_i-a_{(i-1)\bmod n}$，那么一次操作等价于让 $b_i$ 变成 $a_{(i-1)\bmod n}+a_{(i+1)\bmod n}-a_i-a_{(i-1)\bmod n}=a_{(i+1)\bmod n}-a_i=b_{(i+1)\bmod n}$，同时让 $b_{(i+1)\bmod n}$ 变成 $a_{(i-1)\bmod n}-(a_{(i-1)\bmod n}+a_{(i+1)\bmod n}-a_i)=a_i-a_{(i-1)\bmod n}=b_i$，即交换相邻两项，这是一个非常简单的操作。

我们再来分析合法序列有什么性质。有且只有一个 $i\in[0,n-1]$ 满足 $a_{(i-1)\bmod n}<a_i$ 且 $a_{(i+1)\bmod n}<a_i$ 意味着有且只有一个 $i$ 满足 $b_{i}>0,b_{(i+1)\bmod n}<0$。我们知道所有的 $b_i$  都不等于 $0$，那么刚刚的条件就等价于通过交换相邻两项的操作把所有为负数的 $b_i$ 集中成连续的一段。现在求最小的交换次数。

先想想这个问题放在链上怎么做。根据基础的数学知识我们知道把集中点放在中位数附近是最优的。但现在在环上，每个数都可以成为中位数。故枚举每个数作为中位数统计答案即可，实现细节看代码。复杂度线性，目前最优解。

### 代码实现


```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,l,r,a[400010],b[400010];
long long s[400010],sum1,sum2,mn;
inline void rd(int &x)
{
	x=0;
	char c=getchar();
	for(;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())
		x=(x<<3)+(x<<1)+c-'0';
}
inline long long min(long long a,long long b)
{
	return a<b?a:b;
}
int main()
{
	rd(T);
	while(T--)
	{
		rd(n);
		for(register int i=1;i<=n;i++)
			rd(b[i]);
		m=0;
		mn=LLONG_MAX;
		if(b[1]-b[n]<0)
			a[++m]=1;
		for(register int i=2;i<=n;i++)
			if(b[i]-b[i-1]<0)
				a[++m]=i;
		l=(m-1)/2,r=m-1-l;
		for(register int i=1;i<=m;i++)
			s[i]=s[i-1]+a[i];
		for(register int i=m+1;i<=2*m;i++)
			a[i]=a[i-m]+n,s[i]=s[i-1]+a[i];
		for(register int i=1;i<=m;i++)
		{
			if(i-l<1)
			{
				sum1=s[i+m-1]-s[i+m-l-1];
				sum1=1ll*l*a[m+i]-sum1;
				sum1-=1ll*l*(l+1)/2;
			}
			else
			{
				sum1=s[i-1]-s[i-l-1];
				sum1=1ll*l*a[i]-sum1;
				sum1-=1ll*l*(l+1)/2;
			}
			if(i+r>m)
			{
				sum2=s[i+r]-s[i];
				sum2=sum2-1ll*r*a[i];
				sum2-=1ll*r*(r+1)/2;
			}
			else
			{
				sum2=s[i+r]-s[i];
				sum2=sum2-1ll*r*a[i];
				sum2-=1ll*r*(r+1)/2;
			}
			mn=min(mn,sum1+sum2);
		}
		printf("%lld\n",mn);
	}
	return 0;
}
```

---

## 作者：steambird (赞：0)

## 思路

下面加粗的“**注意**”部分为赛时错解。错解及其错因提供在此，以供读者吸取教训。

首先我们注意到题目中描述的操作较难描述，因此考虑将题目中的操作转化为我们容易处理的操作。

对含有加减、只和前后项有关的式子，我们考虑差分。设初始序列为 $\{a,b,c\}$，对中间的元素 $b$ 操作一次后变为 $\{a,a+c-b,c\}$，操作前后的差分序列分别为 $\{a,b-a,c-b\}$ 与 $\{a,c-b,b-a\}$，即后两个元素发生了一次交换。

同时，位置 $i$ 是“好的”也可以在差分序列中描述：$a_i>0,a_{(i+1) \bmod n}<0$。因此，我们最终只关心差分数值是否大于 $0$ 或小于 $0$。由于给定的是排列，不可能有两数相等。下面将差分序列中大于 $0$ 的数值标注为 `+`，小于 $0$ 的标注为 `-`。这样，“好的”位置可以描述为 `+-`。

于是我们就可以将操作描述为：每次操作可以交换差分序列中的两个元素，求最小的操作次数使最终序列形如 `-----+++++++-----`，即只存在一个 `+-`。**注意，这是在一个环上操作，所以不是逆序对个数计数！**

接下来，我们需要解决一个问题：寻找 `+-` 的位置。观察上面提到的最终序列，可以发现这一序列的本质是所有 `+` 都连在一起（否则一定有超过一对 `+-`）。

如果上述问题在一个线性序列中，我们很容易通过枚举位置并用前缀和计算代价找到最小操作次数。记 $sum_i$ 为前 $i$ 个数中 `+` 的位置编号之和，$cnt_i$ 为前 $i$ 个数中 `+` 的数量，将除 $x$ 位置（下文称为“集合位置”，因为所有的 `+` 都要“集合”到这个位置附近，**注意，这个位置需要是一个 `+`，否则所有的 `+` 仍然不连续**）外的 `+` 都移动到 $x$ 两侧所需的交换次数 $S$ 为移动左侧所有 `+` 的交换次数 $S_L$ 与右侧所有 `+` 的交换次数 $S_R$ 之和，且有：

$$ S_L=cnt_{x-1} \times x-sum_{x-1}-(\sum_{i=1}^{cnt_{x-1}} i) $$

$$ S_R=(sum_n-sum_x)-((cnt_n-cnt_x) \times x)-(\sum_{i=1}^{cnt_n-cnt_x} i) $$

在环上处理时，我们面临的问题是最佳的集合位置可能因为处于 $n$ 和 $1$ 相连的边界而不被计算（如 `++++--------++++` 可能具有更优的答案，但按照上述方法则不会被处理）。

要解决这个问题，只需破环成链（将环上的 $1,2,...,n$ 复制到 $n+1,n+2,...,2n$），然后分别处理 $[1,n],[2,n+1],...,[n,2n-1]$，取最小值即可。此时需要将上式中的 $cnt_{x-1}$ 和 $sum_{x-1}$ 减去实际起点处的 `+` 的数量与位置编号之和，具体实现见下方代码。

到这里，问题并没有全部解决。如果枚举破环成链后的区间起点 $i$ 和区间内集合位置 $j$，时间复杂度将为 $O(n^2)$，将会出现 TLE。

观察集合位置的特性可以发现，当集合位置向右移动时，左侧所有 `+` 至多需要多移动一步（如果移动之前位置上已经有 `+`，则不需要再移动，但左侧的 `+` 数量增多），右侧所有 `+` 至多少移动一步（如果移动到的位置上已经有 `+`，则仍在右侧的 `+` 的移动步数不减少，但右侧的 `+` 数量减少）。

因此，集合位置向右移动时，相比不移动的情况，答案要么先减少或不变（此时右侧步数减少大于等于左侧步数增多，同时右侧 `+` 数量减少，左侧 `+` 数量增多）后增多（此时由于左侧 `+` 数量增多，对答案的增加越来越多，右侧 `+` 数量减少，对答案的减少越来越少），要么持续增多（左侧对答案的增加始终多于右侧对答案的减少）。

由上述结论，可以在每次区间起点向右移动后**尽可能地**向右移动集合位置，直至移动到的下一个集合位置超出区间终点或使答案增加。**注意，如果答案相等，向右之后的区间中答案既可能增加也可能减少。如果相等时不向右移动，则可能错过此后减少的部分。**

上述做法中，有两个指针（$i$ 和 $j$）同时从左往右移动，只扫描整个序列最多一次，故算法时间复杂度为 $O(n)$。

## 代码

```c++
#include <bits/stdc++.h>
using namespace std;

#define int long long

inline void train() {
	   ios::sync_with_stdio(false);
	   cin.tie(0);
	   cout.tie(0);
}

constexpr int N = 5e5+4;

int t, n, a[N], neg[N], nextpeak[N], nexts[N];
bool peak[N];
long long pocnt[N], pdsum[N];

long long l_becmg[N], r_becmg[N], ans_becmg[N];
bool scanned[N];

// 计算 1+2+...+x
inline long long summer(long long x) {
	return x*(x+1)/2;
}

inline long long mini(long long a, long long b) {
	return a < b ? a : b;
}

inline long long evaluate(int target, int i) {
	if (target <= 0) return LLONG_MAX;
	long long lcnt = pocnt[target-1] - pocnt[i];
	long long ltravel = (lcnt * target - (pdsum[target-1] - pdsum[i])) - summer(lcnt);
	
	long long rcnt = pocnt[i+n] - pocnt[target];
	long long rdis = (pdsum[i+n] - pdsum[target]) - (rcnt * target);
	long long rtravel = rdis - summer(rcnt);
	long long cur = ltravel + rtravel;
	
	return cur;
}

inline void subgroup() {
	cin>>n;
	for (int i = 1; i <= n; i++) {
		cin>>a[i];
		peak[i] = false;
		scanned[i] = false;
	}
	for (int i = 1; i <= n; i++) {
		if (i == 1) {
			if (a[n] < a[1]) peak[1] = true;
		} else {
			if (a[i-1] < a[i]) peak[i] = true;
		}
	}
	for (int i = n+1, ptr = 1; ptr <= n; i++, ptr++) {
		peak[i] = peak[ptr];
	}
	nextpeak[(2*n)+1] = -1;
	for (int i = 2*n; i >= 1; i--) {
		if (peak[i]) {
			nextpeak[i] = i;
		} else {
			nextpeak[i] = nextpeak[i+1];
		}
		nexts[i] = nextpeak[i+1];
	}
	for (int i = 1; i <= 2*n; i++) {
		pocnt[i] = pocnt[i-1];
		pdsum[i] = pdsum[i-1];
		if (peak[i]) {
			pocnt[i]++;
			pdsum[i] += i;
		}
	}
	long long single_ans = LLONG_MAX;
	int single_at = -1, moveptr = nextpeak[1];
	for (int i = 0; i < n; i++) {
		long long now = evaluate(moveptr, i);
		while (moveptr < (i+n)) {
			if (nexts[moveptr] > (i+n)) break;
			long long cur = evaluate(nexts[moveptr], i);
			if (cur <= now) {
				now = cur;
				moveptr = nexts[moveptr];
			} else break;
		}
		single_ans = mini(single_ans, now);
	}
	cout<<single_ans<<'\n';
}

signed main() {

	int t;
	cin>>t;
	for (int gs = 0; gs < t; gs++) {
		subgroup();
	}

	return 0;
}
```

---

