# [ABC331C] Sum of Numbers Greater Than Me

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc331/tasks/abc331_c

長さ $ N $ の数列 $ A=(A_1,\ldots,A_N) $ が与えられます。

$ i=1,\ldots,N $ のそれぞれについて次の問題を解いてください。

問題：$ A $ の要素のうち $ A_i $ より大きな要素全ての和を求めよ。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^6 $
- 入力は全て整数である
 
### Sample Explanation 1

\- $ i=1 $ のとき $ A_1=1 $ より大きな要素の和は $ 4+4+2=10 $ - $ i=2 $ のとき $ A_2=4 $ より大きな要素の和は $ 0 $ - $ i=3 $ のとき $ A_3=1 $ より大きな要素の和は $ 4+4+2=10 $ - $ i=4 $ のとき $ A_4=4 $ より大きな要素の和は $ 0 $ - $ i=5 $ のとき $ A_5=2 $ より大きな要素の和は $ 4+4=8 $

## 样例 #1

### 输入

```
5
1 4 1 4 2```

### 输出

```
10 0 10 0 8```

## 样例 #2

### 输入

```
10
31 42 59 26 53 58 97 93 23 54```

### 输出

```
456 414 190 487 361 249 0 97 513 307```

## 样例 #3

### 输入

```
50
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1```

### 输出

```
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0```

# 题解

## 作者：huangzhixia (赞：3)

# 题解
## 算法
本题要用到的算法有**二分**和**前缀和**。
## 思路
我先看题意，大致的意思就是枚举每个 $a[i]$，然后对每个 $a[i]$ 的操作就是输出在序列中大于 $a[i]$ 的所有数的和是多少。

那么我们如果暴力遍历的话会超时，时间复杂度为 $O(n^2)$，那么我们要怎么做呢？这时候就要用到二分。

二分什么呢？

二分有多少个数小于等于当前的 $a[i]$，为什么是小于等于啊？题目中不是大于吗？那是为我们的前缀和做铺垫，我们在 $a$ 数组上做完前缀和后，用 $s$ 数组来记，那么大家可以看看这个式子：

$s[n] - s[L]$

什么意思呢？$s[n]$ 就是代表我们这 $n$ 个数的总和。$s[L]$ 中的 $L$ 则是我们二分出来的小于等于 $a[i]$ 的数的个数。那么 $s[L]$ 也就是小于等于当前 $a[i]$ 的数的总和。那 $s[n]$ 和 $s[L]$ 一减是不是就是大于当前 $a[i]$ 的数的总和？

这样就好做了。

另外，我们不能改动 $a[i]$，为什么大家都知道，所以我们可以用个 $b$ 数组来进行操作。

## 温馨提示
本题二分需要的排序可以用自带的排序函数，不会超时，详见代码。

## code:
```c
// C - Sum of Numbers Greater Than Me
//
// by vecon
//
// algorithm：binary search，PreSum 
#include <bits/stdc++.h>

using namespace std;

int n, a[200001], b[200001];

long long s[200001];

int main(){
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]), b[i] = a[i];
	sort(b + 1, b + n + 1); 	
	for (int i = 1; i <= n; i++)
		s[i] = s[i - 1] + b[i];
	for (int i = 1; i <= n; i++) {
		int x = a[i];
		int L = 0, R = n + 1;
		while (L + 1 < R) {
			int M = (L + R) / 2;
			if (b[M] <= x)	
				L = M;
			else
				R = M;
		}
		printf("%lld ", s[n] - s[L]);
	}
}
```

---

## 作者：wmrqwq (赞：2)

# 题目链接：

[[ABC331C] Sum of Numbers Greater Than Me](https://www.luogu.com.cn/problem/AT_abc331_c)

# 题意简述：

有一个 $n$ 个数的序列，你需要求出对于每个 $a_i$ 所有大于 $a_i$ 的数的和。

# 解题思路：

我们可以先将 $a$ 序列排序，然后用前缀和维护前 $i$ 个数的和，于是问题就转化成了求所有数之和减去最后一个 $\le a_i$ 的数的位置的前缀和的值，但是这样时间复杂度还是会被卡到 $O(n^2)$，于是我们可以直接二分一下，这样时间复杂度就正确了。

# 参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,ans[200010],sum[200010];
struct node{
	long long x,id;
}a[200010];
bool cmp(node x,node y){
	return x.x<y.x;
}
long long f(long long x)
{
	long long l=1,r=n,mid;
	while(l<=r)
	{
		mid=(l+r)/2;
		if(a[mid].x<=x)
			l=mid+1;
		else
			r=mid-1;
	}
	return l;
}
#define lowbit(x) x&-x
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
int main()
{
	IOS;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i].x,a[i].id=i;
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++)
		sum[i]=sum[i-1]+a[i].x;
	for(int i=1;i<=n;i++)
		ans[a[i].id]=sum[n]-sum[f(a[i].x)-1];
	for(int i=1;i<=n;i++)
		cout<<ans[i]<<" ";
	QwQ;
}
```

---

## 作者：封禁用户 (赞：2)

这道题有很多种解法，这里给出一种最好写的：

构造一个桶数组，把每一个数的个数与数值的乘积存进去，再使用后缀和输出即可。

注意事项：开 `long long`。~~俗话说的好~~，不开 `long long` 见祖宗。

示例代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[200005],cnt[1000005]; 
signed main(){
	int n;
	scanf("%lld",&n);
	for(int i=1;i<=n;++i){
		scanf("%lld",a+i);
		cnt[a[i]]+=a[i];
	}for(int i=1000000;i>=0;--i){
		cnt[i]+=cnt[i+1];
	}for(int i=1;i<=n;++i){
		printf("%lld ",cnt[a[i]+1]);
	}printf("\n");
	return 0;
}
```

---

## 作者：xz001 (赞：1)

- 由于 $a_i\le10^6$，我们可以直接记录下来每个数出现的次数，然后对其贡献做一个前缀和即可，查询时直接输出 $sum_{10^6}-sum_{a_i}$ 即可。
- 时间复杂度 $O(n)$，代码如下：

```cpp
/*
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3, "Ofast", "inline")
*/
#include<bits/stdc++.h>

using namespace std;

#define re			register
#define int			long long
#define fi			first
#define se			second
#define swap(a, b) 	a ^= b, b ^= a, a ^= b
#define pb 			push_back
#define all(x)		x.begin(), x.end()
#define max(a, b)	(a > b ? a : b)
#define min(a, b)	(a < b ? a : b)
#define il			inline
#define abs(x)		((x ^ (x >> 63)) - (x >> 63))

typedef pair<int, int> PII;

const int N = 1e6 + 10;
const int INF = 1e18, P = 998244353;
const double eps = 1e-6;

il int  read() { re int x = 0; re bool f = true; re char c = getchar(); while (c < 48 || c > 57) { if (c == '-') f = false; c = getchar(); } while (c >= 48 && c <= 57) x = (x << 3) + (x << 1) + c - 48, c = getchar(); return f ? x : -x; }
il void write(int x) { if (x < 0) putchar('-'), x = -x; if (x > 9) write(x / 10); putchar(x % 10 + 48); }
il void wel(int x) { write(x), putchar('\n'); }
il void wsp(int x) { write(x), putchar(' '); }

int n, s, m, l, a[200005], sum[N];

signed main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++ i) scanf("%lld", a + i), ++ sum[a[i]];
    for (int i = 1; i <= 1e6; ++ i) sum[i] = sum[i - 1] + sum[i] * i/*每个数的贡献*/;
    for (int i = 1; i <= n; ++ i) printf("%lld ", sum[1000000] - sum[a[i]]);
    return 0;
}


```

---

## 作者：Leeb (赞：0)

### 题意简述

给定一个长度为 $n$ 的序列 $A$，求每个 $i(i\in[1,n])$ 的问题的解。问题：求 $A$ 中所有大于 $A_i$ 的元素之和。
### 解题思路

输入时统计 $A$ 中每个元素出现的次数，对 $A$ 进行排序和去重，再对 $A$ 中的元素乘上它出现的次数进行前缀和，同时开个 map，记录 $A$ 中每个元素出现的位置，直接用前缀和输出对于每个 $i(i\in[1,n])$ 的解。

感觉我说的不是很清楚，可以看看代码。
### 参考代码

```cpp
// -- More and More vegetales, what should I do?
// -- AFO! AFO YYDS!
// Code Author : Leeb
// #include <bits/stdc++.h>
#include <map>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 200005
#define inf 0x3f3f3f3f
#define endl '\n'
#define elif else if
#define int long long 
// #define ll long long
#define ub upper_bound
#define lb lower_bound
#define ls (x << 1)
#define rs (x << 1 | 1)
#define mem(a, x) memset(a, x, sizeof(a))
using namespace std;
int n, a[N], b[N], s[N], t[N * 10];
map<int, int> mp;
inline int in() {
    int a = 0; bool f = 0; char ch = getchar();
    while (ch < '0' || ch > '9')
        {if (ch == '-') f = 1; ch = getchar();}
    while (ch >= '0' && ch <= '9')
        a = (a << 1) + (a << 3) + (ch ^ 48), ch = getchar();
    if (f) return ~a + 1;   
    return a;
}
inline void print(int x) {
    if (x < 0) putchar('-'), x = ~x + 1;
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}
inline void out(int x, char ch) {
    print(x);
    putchar(ch);
}
inline void init() {
    n = in();
    for (int i = 1; i <= n; ++i) b[i] = a[i] = in(), t[a[i]]++;
}
inline void work() {
    sort(a + 1, a + 1 + n);
    int m = unique(a + 1, a + 1 + n) - a - 1;
    for (int i = 1; i <= m; ++i) s[i] = s[i - 1] + a[i] * t[a[i]];
    for (int i = 1; i <= m; ++i) mp[a[i]] = i;
    for (int i = 1; i <= n; ++i)
        out(s[m] - s[mp[b[i]]], ' ');
    puts("");
}
signed main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int t = 1;
    while (t--) {
        init();
        work();
    }
    return 0;
}
```

---

## 作者：haokee (赞：0)

## 题目大意

给我一个长度为 $N$ 的序列 $A$，第 $i$ 个数的值为 $A_i$。对于 $A_i$，你需要求出比 $A_i$ 大的数的和。

## 思路

我们首先将数组排序，注意要记录编号，因为这题需要输出所有的答案。排完序之后，我们就从后往前做一个后缀和，因为 $A_{(i+1)}$ 一定大于等于 $A_i$。注意这里需要特殊处理一下等于的情况，使用 $l$ 记录等于了几个数，$x$ 表示等于的是几。然后统计到 $ans$ 数组就行了。

注意这题要开 `long long`，不然会 WA。

## 代码

```cpp
#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

const ll kMaxN = 2e5 + 5;

struct Node {
  ll v, id;  // 值和编号
} a[kMaxN];

ll p[kMaxN], ans[kMaxN], n, l, x;  // p 是后缀和数组，ans 是答案数组

int main() {
  cin >> n;
  for (ll i = 1; i <= n; i++) {
    cin >> a[i].v, a[i].id = i;  // 输入并记录编号
  }
  sort(a + 1, a + n + 1, [](const Node &a, const Node &b) {  // 排序
    return a.v < b.v;                                        // 根据值来排序
  });
  p[n] = 0;                                   // 第 n 个元素没有更大的值
  for (ll i = n - 1; i >= 1; i--) {           // 从后往前枚举
    if (a[i].v == a[i + 1].v) {               // 如果是等于的情况
      p[i] = p[i + 1];                        // 直接赋值过来
      l++, x = a[i].v;                        // 等于的长度加一，并记录下等于的值
    } else {                                  // 如果不是等于的情况
      p[i] += p[i + 1] + a[i + 1].v + l * x;  // 那么把之前的全部累加起来
      l = x = 0;                              // 清空
    }
  }
  for (ll i = 1; i <= n; i++) {
    ans[a[i].id] = p[i];  // 记录答案
  }
  for (ll i = 1; i <= n; i++) {
    cout << ans[i] << ' ';  // 输出答案
  }
  return 0;
}
```

---

## 作者：Down_syndrome (赞：0)

## 题目描述
给出一个长度为 $n$ 的序列 $A$，对于每个 $i\ (1\le i \le n)$，求出序列中大于 $A_i$ 的数的总和。
## 思路
由于 $n$ 比较大，所以不能直接暴力。看到大于 $A_i$ 可以想到二分。看到求和可以想到前缀和。另序列 $B \gets A$，对序列 $B$ 排序（单独拿出另一个序列排序是因为要按原顺序输出，排序后顺序就乱了），求出 $B$ 的前缀和，每次用二分在 $B$ 中找到第一个大于 $A_i$ 的数。因为已经排序了，所以后面的数一定也大于 $A_i$，直接用前缀和求和即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,a[N],b[N];
long long sum[N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+b[i];
	for(int i=1;i<=n;i++) printf("%lld ",sum[n]-sum[upper_bound(b+1,b+n+1,a[i])-b-1]);
	return 0;
}
```


---

