# Turtle vs. Rabbit Race: Optimal Trainings

## 题目描述

Isaac begins his training. There are $ n $ running tracks available, and the $ i $ -th track ( $ 1 \le i \le n $ ) consists of $ a_i $ equal-length sections.

Given an integer $ u $ ( $ 1 \le u \le 10^9 $ ), finishing each section can increase Isaac's ability by a certain value, described as follows:

- Finishing the $ 1 $ -st section increases Isaac's performance by $ u $ .
- Finishing the $ 2 $ -nd section increases Isaac's performance by $ u-1 $ .
- Finishing the $ 3 $ -rd section increases Isaac's performance by $ u-2 $ .
- $ \ldots $
- Finishing the $ k $ -th section ( $ k \ge 1 $ ) increases Isaac's performance by $ u+1-k $ . (The value $ u+1-k $ can be negative, which means finishing an extra section decreases Isaac's performance.)

You are also given an integer $ l $ . You must choose an integer $ r $ such that $ l \le r \le n $ and Isaac will finish each section of each track $ l, l + 1, \dots, r $ (that is, a total of $ \sum_{i=l}^r a_i = a_l + a_{l+1} + \ldots + a_r $ sections).

Answer the following question: what is the optimal $ r $ you can choose that the increase in Isaac's performance is maximum possible?

If there are multiple $ r $ that maximize the increase in Isaac's performance, output the smallest $ r $ .

To increase the difficulty, you need to answer the question for $ q $ different values of $ l $ and $ u $ .

## 说明/提示

For the $ 1 $ -st query in the first test case:

- By choosing $ r = 3 $ , Isaac finishes $ a_1 + a_2 + a_3 = 3 + 1 + 4 = 8 $ sections in total, hence his increase in performance is $ u+(u-1)+\ldots+(u-7)=8+7+6+5+4+3+2+1 = 36 $ .
- By choosing $ r = 4 $ , Isaac finishes $ a_1 + a_2 + a_3 + a_4 = 3 + 1 + 4 + 1 = 9 $ sections in total, hence his increase in performance is $ u+(u-1)+\ldots+(u-8)=8+7+6+5+4+3+2+1+0 = 36 $ .

Both choices yield the optimal increase in performance, however we want to choose the smallest $ r $ . So we choose $ r = 3 $ .

For the $ 2 $ -nd query in the first test case, by choosing $ r = 4 $ , Isaac finishes $ a_2 + a_3 + a_4 = 1 + 4 + 1 = 6 $ sections in total, hence his increase in performance is $ u+(u-1)+\ldots+(u-5)=7+6+5+4+3+2 = 27 $ . This is the optimal increase in performance.

For the $ 3 $ -rd query in the first test case:

- By choosing $ r = 5 $ , Isaac finishes $ a_5 = 5 $ sections in total, hence his increase in performance is $ u+(u-1)+\ldots+(u-4)=9+8+7+6+5 = 35 $ .
- By choosing $ r = 6 $ , Isaac finishes $ a_5 + a_6 = 5 + 9 = 14 $ sections in total, hence his increase in performance is $ u+(u-1)+\ldots+(u-13)=9+8+7+6+5+4+3+2+1+0+(-1)+(-2)+(-3)+(-4) = 35 $ .

Both choices yield the optimal increase in performance, however we want to choose the smallest $ r $ . So we choose $ r = 5 $ .

Hence the output for the first test case is $ [3, 4, 5] $ .

## 样例 #1

### 输入

```
5
6
3 1 4 1 5 9
3
1 8
2 7
5 9
1
10
1
1 1
9
5 10 9 6 8 3 10 7 3
5
8 56
1 12
9 3
1 27
5 45
5
7 9 2 5 2
10
1 37
2 9
3 33
4 32
4 15
2 2
4 2
2 19
3 7
2 7
10
9 1 6 7 6 3 10 7 3 10
5
10 43
3 23
9 3
6 8
5 14```

### 输出

```
3 4 5 
1 
9 2 9 4 9 
5 2 5 5 5 2 4 5 4 2 
10 6 9 7 7```

# 题解

## 作者：__YSC__ (赞：4)

# 题目描述

有 $N$ 条跑道，第 $i$ 条跑道有 $A_i$ 节。给定整数 $u$，跑第 $k$ 节会使分数加 $u-k+1$(有可能为负数)。给定 $q$ 个询问，每个询问会给定 $l,u$，求最小的 $r$，使得你得到的分数最大。

# 思路

对于每次询问，二分最大的 $r$，使得第 $r$ 条跑道的分数  $>0$，而第 $i$ 条跑道的分数为 $\frac{(2u + 2sum_{l - 1} - sum_{i - 1}  - sum_i + 1) \cdot A_i}{2}$，其中 $sum_i=\sum \limits_{j=1}^i A_j$。

时间复杂度 $O(TQ\log N)$，空间复杂度 $O(N)$。

## 细节

无。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 100001;

int t, n, q, a[MAXN], sum[MAXN];

ll Calc(int l, int r, int u) {
  return 1ll * (u + 1 - (sum[r - 1] - sum[l - 1] + 1) + u + 1 - (sum[r] - sum[l - 1])) * a[r] / 2ll;
}

int erfen(int L, int u) {
  int l = L, r = n;
  while(l < r) {
    int mid = (l + r + 1) >> 1;
    if(Calc(L, mid, u) > 0) {
      l = mid;
    }else {
      r = mid - 1;
    }
  }
  return l;
}

void Solve() {
  cin >> n;
  for(int i = 1; i <= n; ++i) {
    cin >> a[i];
    sum[i] = sum[i - 1] + a[i];
  }
  cin >> q;
  for(int i = 1, l, u; i <= q; ++i) {
    cin >> l >> u;
    cout << erfen(l, u) << " ";
  }
  cout << "\n";
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> t;
  while(t--) {
    Solve();
  }
  return 0;
}

```

---

## 作者：Frodo (赞：4)

## 题面翻译

给定 $n$ 个正整数 $a_1,a_2,\cdots,a_n$。

$q$ 次询问：每次给定 $l,u$，求出最小的 $r$ 使 $\frac{s(2u-s+1)}{2}$ 最大，其中 $s=\sum_l^r a_i$。

本题多测，共 $T$ 组数据。

## 思路

容易发现 $f(s)=\frac{s(2u-s+1)}{2}$ 为一个二次函数，即单峰函数，于是二分答案。

判断上升：

$f(x) \leq f(x+1)$

$\Longleftrightarrow  x(2u-x+1) \leq (x+1)(2u-x) $

$\Longleftrightarrow 2xu-x^2+x \leq 2xu+2u-x^2-x$

$\Longleftrightarrow x \leq u$

注意在二分结束后特判 $r$ 和 $r+1$ 那个更优。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[100100],sum[100100];
signed main(){
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++){cin>>a[i];sum[i]=sum[i-1]+a[i];}
        int q;cin>>q;
        while(q--){
            int l,u;
            cin>>l>>u;
            int L=l,R=n;
            while(L<R){
                int mid=(L+R+1)>>1;
                if(sum[mid]-sum[l-1]<=u) L=mid;
                else R=mid-1;
            }
            L=R;
            int s1=abs(sum[L]-sum[l-1]-u),s2=abs(sum[L+1]-sum[l-1]-u);
            if(L==n) cout<<L<<" ";
            else{
                if(s1<=s2-1) cout<<L<<" ";
                else cout<<L+1<<" ";
            }
        }
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：yhylivedream (赞：2)

## 分析

以下记 $sum$ 等于 $\sum^r_{i=l}{a_i}$。

很显然如果 $sum>u$ 那么 $u+1-sum$ 就是负数了，所以我们可以二分分界点 $r$ 使得 $sum < u,sum+a_{r+1}>u$，最后在计算一遍输出答案即可，区间和可以用前缀和来快速计算。

那么如何快速计算 $u+u-1+ \cdots +u-sum+1$，我们将 $u$ 提出算式变为：$u \times sum - (1 + 2 + \cdots + sum - 1)$，发现括号内为 $1\sim sum-1$ 求和，那么算式化简后即为：$u \times sum-\frac{sum \times (sum-1)}{2}$。

## 代码

```cpp
# include <bits/stdc++.h> 

using namespace std;
using ll = long long;
using PII = pair <int, int>;

const int N = 2e5 + 5;
ll T, n, q, a[N], pre[N];

signed main () {
  for (cin >> T; T; T --) {
    cin >> n;
    for (ll i = 1; i <= n; i ++) {
      cin >> a[i];
      pre[i] = pre[i - 1] + a[i];
    }
    for (cin >> q; q; q --) {
      ll x, u;
      cin >> x >> u;
      ll l = x - 1, r = n + 1;
      for (; l + 1 < r;) {
        ll mid = (l + r) / 2;
        (pre[mid] - pre[x - 1] <= u ? l = mid : r = mid);
      }
      if (a[x] > u) {
        cout << x << ' ';
      } else if (r == n + 1) {
        cout << n << ' ';
      } else {
        ll t = pre[l] - pre[x - 1], t2 = t + a[l + 1];
        ll ans = u * t - (t * (t - 1) / 2), ans2 = u * t2 - (t2 * (t2 - 1) / 2);
        cout << (ans >= ans2 ? l : l + 1) << ' ';
      }
    }
    cout << '\n';
  }
  return 0;
}
```

---

## 作者：ZhaoV1 (赞：1)

# 解析

看到连续区间，我们可以维护前缀和来提高效率 $s$。  
假设我们能得到最小的第一次加到非正整数值的 $r_2$，那么如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/zdftzql3.png)

存在 $s_{r_1} ≥ s_{r_2}$ 或 $s_{r_1} ＜ s_{r_2}$ 的可能，即答案一定出在 $r_1$ 或 $r_2$ 的位置。我们用二分去得到最小的第一次加到非正整数值 $r_2$，然后分别用 $r_1$ 和 $r_2$ 关于 $u$ 进行比较，看谁更大，若均相等则选择 $r_1$。

注意细节，思路最重要，代码仅供参考。

AC Code
---


```cpp
#define int long long
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
const int N = 1e5+5;
int t,n,q,l,u;
int a[N], s[N];

bool check(int mid){
	int x = s[mid] - s[l-1];
	return x > u;
}

void solve(){
	cin >> n;
	for(int i=1;i<=n;i++){
		cin >> a[i];
		s[i] = s[i-1] + a[i];
	}
	cin >> q;
	while(q--){
		cin >> l >> u;
		int left = l-1, right = n+1;
		while(left + 1 < right){//找到刚好让目标得到负数的最早位置 
			int mid = (left + right) >> 1;
			if(check(mid)){
				right = mid;
			}else left = mid;
		}
		if(right > n){
			cout << n << " ";
			continue;
		}

		if(abs((s[right] - s[l-1]) - (u+1)) >= abs((s[right-1] - s[l-1]) - u) && right-1 >= l){
			cout << right-1 << " ";
		}else cout << right << " ";
	}
	cout << '\n';
}
```

---

## 作者：Vitamin_B (赞：1)

# 思路
很明显 $s$ 越接近 $\frac{2u+1}2$ 答案越大，于是我们可以定义一个前缀和数组 $a$，然后二分找到最后一个 $\le\frac{2u+1}2$ 的数和第一个 $\ge\frac{2u+1}2$ 的数，比较一下两个数距离 $\frac{2u+1}2$ 的距离哪个小就输出哪个。
# 题解
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
const int inf = 2e9;
int t, n, q, a[100005], l, r, u, ans1, ans2;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n;
		for (int i = 1; i <= n; ++ i)
			cin >> a[i], a[i] += a[i - 1];
		cin >> q;
		while (q --) {
			cin >> l >> u;
			r = lower_bound (a + 1, a + 1 + n, u + a[l - 1]) - a;
			ans2 = inf;
			if (r <= n)
				ans1 = r, ans2 = a[r] - a[l - 1] - u;
			if (-- r >= l && u + a[l - 1] - a[r] < ans2)
				ans1 = r;
			cout << ans1 << ' ';
		}
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：minVan (赞：0)

**题目大意**

给定序列 $a_1,a_2,\cdots,a_n$，每次询问给定起点 $l$ 以及初始值 $u$，你要选定右端点 $r$，这段区间的答案为 $\dfrac{s(2u-s+1)}2$，其中 $s=\sum\limits_{i=l}^ra_i$。求当答案取最大值时 $r$ 的最小值。

**解题思路**

首先求前缀和方便求区间和，令 $t$ 为在 $(l,n]$ 内最后一个比 $s_{l-1}+u$ 小的数的下标，而 $t+1$ 和 $t$ 均有可能是答案，比较一下即可。

**AC 代码，请勿抄袭。**

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 5;
int n, q, l, u, s[N];
signed main(){
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while(t--){
    cin >> n;
    s[n + 1] = 1e18;
    for(int i = 1, x; i <= n; i++) {
      cin >> x;
      s[i] = s[i - 1] + x;
    }
    cin >> q;
    while(q--){
      cin >> l >> u;
      int i = lower_bound(s + l + 1, s + n + 2, s[l - 1] + u) - s - 1;
      int k1 = s[i] - s[l - 1], k2 = s[i + 1] - s[l - 1];
      if(u * k1 - k1 * (k1 - 1) / 2 >= u * k2 - k2 * (k2 - 1) / 2) {
        cout << min(i, n) << " ";
      } else {
        cout << min(i + 1, n) << " ";
      }
    }
    cout << '\n';
  }
  return 0;
}

```

---

## 作者：Houkiseino_Kokoro (赞：0)

### $\texttt{E. Turtle vs. Rabbit Race: Optimal Trainings}$
#### [原题链接](https://codeforces.com/contest/1933/problem/E)
#### 题意简述
给定一个含 $n$ 项的数列 $a$ 与 $q$ 次询问，数列 $a$ 中元素 $a_i$ 的值代表 $a_i$ 段连续等长的跑道。此时可以连续跑若干段跑道，每当跑过第 $k$ 段跑道后，产生 $u + 1 - k$ 的贡献。贡献可以非正。

每次询问给出 $l$，$u$ 两个值。对于每次询问，需要回答一个值 $r$，表示当连续跑 $\sum_{i = l}^r a_i$ 段时，总贡献值最大。若有多个 $r$ 可以使总贡献值最大，输出最小的那个。
#### 解法
很简单的E，使我跳过D。

显然利用等差数列求和来计算贡献值。设连续跑了 $x$ 段，产生的贡献值即为 $\dfrac{1}{2}x(2u + 1 - x)$。根据二次函数的性质容易得出当 $x = \dfrac{1}{2}(2u + 1)$ 时贡献值最大，且最优答案两侧的答案均单调。因此先处理出前缀和，然后二分查找最优答案即可。

时间复杂度为 $O(\sum (n + q\log n))$，可以通过本题相当宽松的时间限制。

需要注意的是，如果使用 `std::lower_bound` 或 `std::upper_bound` 库函数查找而不是手写二分查找的话，由于 $\dfrac{1}{2}(2u + 1)$ 必不是整数，二分查找后需要对结果附近的多个值进行检验，寻找其中的最大值；同时函数返回的结果可能会落在合法区间 $\left[l,n\right]$ 外，需要手动移进区间。

以及别忘开 `long long`。
#### 代码
```cpp
void solve()
{
    long long n, q, l, u;
    std::cin >> n;
    std::vector<long long> arr(n + 1);
    for (size_t i = 1; i <= n; i++)
    {
        std::cin >> arr[i];
        arr[i] += arr[i - 1];
    }
    std::cin >> q;
  	// 等差数列求和
    auto calc = [](long long u, long long x) -> long long
    {
        return ((2 * u + 1 - x) * x) / 2;
    };
    for (size_t i = 0; i < q; i++)
    {
        std::cin >> l >> u;
        auto ans = std::lower_bound(arr.begin(), arr.end(), (2 * u + 1) / 2 + arr[l - 1]) - arr.begin();
        // 若所得答案非法，移至合法区间内
      	if (ans > n)
        {
            ans = n;
        }
        if (ans < l)
        {
            ans = l;
        }
      	// 对答案附近的多个点进行检验，取其中的最大值
        if (ans - 1 >= l && calc(u, arr[ans - 1] - arr[l - 1]) >= calc(u, arr[ans] - arr[l - 1]))
        {
            ans = ans - 1;
        }
        if (ans + 1 <= n && calc(u, arr[ans + 1] - arr[l - 1]) > calc(u, arr[ans] - arr[l - 1]))
        {
            ans = ans + 1;
        }
        if (ans + 2 <= n && calc(u, arr[ans + 2] - arr[l - 1]) > calc(u, arr[ans] - arr[l - 1]))
        {
            ans = ans + 2;
        }
        if (ans + 3 <= n && calc(u, arr[ans + 3] - arr[l - 1]) > calc(u, arr[ans] - arr[l - 1]))
        {
            ans = ans + 3;
        }
        std::cout << ans << ' ';
    }
    std::cout << std::endl;
}

```

---

