# [ABC334D] Reindeer and Sleigh

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc334/tasks/abc334_d

$ N $ 台のソリがあり、各ソリには $ 1,2,\ldots,\ N $ の番号がつけられています。

ソリ $ i $ を引くために必要なトナカイは $ R_i $ 匹です。

また、各トナカイが引けるソリは高々 $ 1 $ 台です。より厳密には、$ m $ 台のソリ $ i_1,\ i_2,\ \ldots,\ i_m $ を引くために必要なトナカイは $ \sum_{k=1}^{m}\ R_{i_k} $ 匹です。

以下の形式のクエリが $ Q $ 個与えられるので、答えを求めてください。

- 整数 $ X $ が与えられる。トナカイが $ X $ 匹いるときに最大で何台のソリを引けるか求めよ。

## 说明/提示

### 制約

- $ 1\ \leq\ N,\ Q\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ R_i\ \leq\ 10^9 $
- $ 1\ \leq\ X\ \leq\ 2\ \times\ 10^{14} $
- 入力される数値はすべて整数
 
### Sample Explanation 1

トナカイが $ 16 $ 匹いるとき、ソリ $ 1,2,4 $ を引くことができます。 $ 16 $ 匹のトナカイで $ 4 $ 台のソリを引くことはできないので、クエリ $ 1 $ の答えは $ 3 $ となります。

## 样例 #1

### 输入

```
4 3
5 3 11 8
16
7
1000```

### 输出

```
3
1
4```

## 样例 #2

### 输入

```
6 6
1 2 3 4 5 6
1
2
3
4
5
6```

### 输出

```
1
1
2
2
2
3```

## 样例 #3

### 输入

```
2 2
1000000000 1000000000
200000000000000
1```

### 输出

```
2
0```

# 题解

## 作者：qejwdi (赞：20)

要最多，那么显然就尽量取小的，那么从小到大排个序，然后做个前缀和，二分即可。

---

## 作者：xz001 (赞：1)

- 很明显我们为了拉走更多的车子，我们肯定是要尽量拉需要的驯鹿少的车子，因此我们可以在一开始将每辆车子需要的驯鹿数量从小到大排序，然后求一个前缀和，询问时在前缀和上二分求得能拉的最大驯鹿数即可。
- 代码如下：

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
const int M = 1e6 + 10;
const int INF = 1e18, P = 998244353;
const double eps = 1e-6;

il int  read() { re int x = 0; re bool f = true; re char c = getchar(); while (c < 48 || c > 57) { if (c == '-') f = false; c = getchar(); } while (c >= 48 && c <= 57) x = (x << 3) + (x << 1) + c - 48, c = getchar(); return f ? x : -x; }
il void write(int x) { if (x < 0) putchar('-'), x = -x; if (x > 9) write(x / 10); putchar(x % 10 + 48); }
il void wel(int x) { write(x), putchar('\n'); }
il void wsp(int x) { write(x), putchar(' '); }

int n, q, a[N], sum[N];

signed main() {
    scanf("%lld%lld", &n, &q);
    for (int i = 1; i <= n; ++ i) scanf("%lld", a + i);
    sort(a + 1, a + n + 1);  //排序
    for (int i = 1; i <= n; ++ i) sum[i] = sum[i - 1] + a[i]; //前缀和
    while (q -- ) {
    	int x;
    	scanf("%lld", &x);
    	int l = 0, r = n, ans; 
    	while (l <= r) {   // 二分
    		int mid = (l + r) >> 1;
    		if (sum[mid] <= x) {  //若能拉至少 mid 辆车子
    			ans = mid;
    			l = mid + 1;
			} else {  
				r = mid - 1;
			}
		}
		printf("%lld\n", ans);
	}
    return 0;
}


```

---

## 作者：jubingkun (赞：1)

## 题目大意
给定 $n$ 个物品，第 $i$ 件物品的体积为 $a_i$，再给出 $q$ 个问题，每个问题给出一个正整数 $x$，代表背包的大小，问这个背包最多能塞下几个物品。

## 题目分析
看懂题后，很容易想到贪心。

把数组 $a$ 从小到大排序一遍，只要空间还够，就继续选。
```cpp
sort(a + 1, a + n + 1);
while (q--) {
	cin >> x;
	int ans = 0;
	if (x >= sum)	cout << n << "\n";//这里加了个小优化，相信大家能看懂（sum是a数组的和）
	else {
		for (int i = 1; i <= n; ++i)
			if (x >= a[i]) {
				ans++, x -= a[i];
			} else	break;
		cout << ans << "\n";
	}
}
```
但是在这样的数据范围下，这个做法一定超时。

### 考虑优化
经过分析，我们会发现，最优的选法一定是从第一个开始，**连续**选若干个后停止，因为这样所选出的 $a_i$ 的和一定最小。

于是我们便可以用前缀和优化：在把 $a$ 数组排完序后，$O(n)$ 处理出前缀和，再用二分查找前缀和数组中最后一个小于等于 $x$ 的数的位置即可。

## Code:
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define int long long
using namespace std;
const int MAXN = 2e5 + 5;
int n, q, sum;
int a[MAXN], x, pre[MAXN];
signed main() {
	ios::sync_with_stdio(0);
	cin >> n >> q;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		sum += a[i];
	}
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; ++i)
		pre[i] = pre[i - 1] + a[i];
	while (q--) {
		cin >> x;
		if (x >= sum)	cout << n << "\n";
		else {
			/*这里我用的是upper_bound，upper_bound会返回在该序列中第一个大于x的数的位置，直接减去1就好了*/
			int b = upper_bound(pre + 1, pre + n + 1, x) - pre;
			cout << b - 1 << "\n";
		}
	}
	return 0;
}
```

---

## 作者：无钩七不改名 (赞：0)

根据贪心思想，我们肯定先拉需要驯鹿数量少的车。那么我们可以对 $r_i$ 数组进行排序，统计前缀和数组 $q_i$，表示拉 $i$ 辆车至少需要 $q_i$ 头驯鹿。

对于每次询问，在 $q_i$ 中二分查找即可。

### 赛时代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=200005;

int n,q;
long long r[N];
long long ans;

long long read(){
	int f=1;
	long long k=0;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		k=k*10+c-'0';
		c=getchar();
	}
	return f*k;
}

int main(){
	n=read();q=read();
	for(int i(1);i<=n;++i)r[i]=read();
	sort(r+1,r+1+n);
	for(int i(1);i<=n;++i)r[i]+=r[i-1];
	while(q--){
		long long x=read();
		ans=0;int lx=1,rx=n;
		while(lx<=rx){
			int mid=(lx+rx)>>1;
			if(r[mid]<=x)ans=mid,lx=mid+1;
			else rx=mid-1;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：aaron0919 (赞：0)

# [AT_abc334_d の题解](https://www.luogu.com.cn/problem/AT_abc334_d)

### 理性分析

我们肯定近可能选小的，通过前缀和求出拉 $i$ 架雪橇最小需要的匹数，由于答案满足单调性，二分查找最大小于等于 $query_i$ 的数下标即可。

### code

[AC 记录](https://atcoder.jp/contests/abc334/tasks/abc334_d)

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5 + 10;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;

template <typename T>
void out(const T &t)
{
	cout << t << endl;
}

template <typename T, typename...Args>
void out(const T &t, const Args&...rest)
{
	cout << t << ' ';
	out(rest...);
}

ll n, q, x;
ll a[N];

int main()
{
#define endl '\n'
	cin.tie(nullptr) -> sync_with_stdio(false);

	cin >> n >> q;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	sort(a + 1, a + 1 + n);
	for (int i = 1; i <= n; i++)
	{
		a[i] += a[i - 1];
	}
	while (q--)
	{
		cin >> x;
		int l = 0, r = n;
		while (l < r)
		{
			int mid = (l + r + 1) / 2;
			if (a[mid] <= x)
			{
				l = mid;
			}
			else
			{
				r = mid - 1;
			}
		}
		out(l);
	}
	return 0;
}

```

---

## 作者：CheZiHe929 (赞：0)

# AT_abc334_d 题解

### 题目链接

[Atcoder](https://atcoder.jp/contests/abc334/tasks/abc334_d)

[Luogu](https://www.luogu.com.cn/problem/AT_abc334_d)

### 简要题意

共有 $n$ 辆雪橇，每个雪橇需要 $r_i$ 个驯鹿来拉动，每个驯鹿只能拉一个雪橇。

给你 $q$ 次询问，每次给定一个正整数 $x$，代表此时有 $x$ 只驯鹿，问最多能拉几辆雪橇。

### 简要思路

一眼二分。

我们对 $r$ 数组排序，然后计算前缀和。

对于每次询问，我们使用 `upper_bound` 函数寻找第一个 $> x$ 的位置，记为 $ans$，那么 $ans-1$ 就是最后一个 $\le x$ 的位置，即最多能拉动的雪橇的数量。

### 完整代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
const int MAXN=2e5+5;

int n,q,x;
int r[MAXN];

signed main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin>>n>>q;
	for(int i=1;i<=n;i++)std::cin>>r[i];
	std::sort(r+1,r+n+1);//排序
	for(int i=1;i<=n;i++)r[i]+=r[i-1];//前缀和
	
	while(q--){
		std::cin>>x;
		int ans=std::upper_bound(r+1,r+n+1,x)-r-1;//二分
		std::cout<<ans<<endl;
	}

	return 0;
}
```

### AC 记录

[Atcoder](https://atcoder.jp/contests/abc334/submissions/48810488)

[Luogu](https://www.luogu.com.cn/record/140764905)

**THE END.**

**THANK YOU.**

---

