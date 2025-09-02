# Yarik and Array

## 题目描述

A subarray is a continuous part of array.

Yarik recently found an array $ a $ of $ n $ elements and became very interested in finding the maximum sum of a non empty subarray. However, Yarik doesn't like consecutive integers with the same parity, so the subarray he chooses must have alternating parities for adjacent elements.

For example, $ [1, 2, 3] $ is acceptable, but $ [1, 2, 4] $ is not, as $ 2 $ and $ 4 $ are both even and adjacent.

You need to help Yarik by finding the maximum sum of such a subarray.

## 样例 #1

### 输入

```
7
5
1 2 3 4 5
4
9 9 8 8
6
-1 4 -1 0 5 -4
4
-1 2 4 -3
1
-1000
3
101 -99 101
20
-10 5 -8 10 6 -10 7 9 -2 -6 7 2 -4 6 -1 7 -6 -7 4 1```

### 输出

```
15
17
8
4
-1000
101
10```

# 题解

## 作者：wmrqwq (赞：5)

# 题目链接

[CF1899C Yarik and Array](https://www.luogu.com.cn/problem/CF1899C)

# 题意简述

有一个长度为 $n$ 的序列，你需要找出一个奇偶交替的子段使得这个子段的和最大。

# 解题思路

对于这个题，我们可以考虑这两种情况：

1. 序列中的所有数都为负数，这时我们直接取序列中的最大值即可，

2. 序列中有正数，这时我们有一个贪心的思路，就是我们取的第一个数一定是正数，然后若和后面的数一直奇偶交替，则一直取，注意在这个过程中要一直取序列总和的最大值。

然后就能 AC 了。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,a[200010],sum,ans,maxn,pd;
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
int main()
{
	IOS;
	cin>>t;
	while(t--)
	{
		ans=-1e18,sum=0,pd=0;
		cin>>n>>a[1];
		maxn=a[1];
		if(a[1]>0)
			pd=1;
		if(n==1)//如果n=1，则直接输出这个数
		{
			cout<<a[1]<<endl;
			continue;
		}
		for(int i=2;i<=n;i++)
		{
			cin>>a[i];
			if(a[i]>0)
				pd=1;
			maxn=max(maxn,a[i]);
		}
		if(!pd)//若序列中全为负数
		{
			cout<<maxn<<endl;
			continue;
		}
		for(int i=1;i<=n;i++)
		{
			if(sum==0)
			{
				if(a[i]>0)
					sum=a[i];
			}
			else
			{
				if((abs(a[i-1])%2+abs(a[i])%2)==1)
					sum+=a[i];
				else
				{
					if(a[i]>0)
						sum=a[i];
					else
						sum=0;
				}
			}
			sum=max(sum,a[i]);
			ans=max(ans,sum);//这里取最大值
		//	cout<<sum<<' ';
		}
		cout<<ans<<endl;
	}
	QwQ;
}
```

---

## 作者：lailai0916 (赞：3)

## 原题链接

- [洛谷 CF1899C Yarik and Array](https://www.luogu.com.cn/problem/CF1899C)

## 解题思路

对于第 $2\sim n$ 个元素，分类讨论：

- 若能与前面的元素接上，取接或不接的最大值。
- 否则，只能选择不接。

实时更新最大值即可。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=200005;
int a[N];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
	{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		int sum=a[1],ans=a[1];
		for(int i=2;i<=n;i++)
		{
			if(a[i]-a[i-1]&1)
			{
				sum=max(sum+a[i],a[i]);
			}
			else
			{
				sum=a[i];
			}
			ans=max(ans,sum);
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：WA_sir (赞：1)

## [题目](https://codeforces.com/problemset/problem/1899/C)|[链接](https://www.luogu.com.cn/problem/CF1899C)

### 题目大意

在 $n$ 个数中找出一非空区间，使得其任意相邻两个元素奇偶不同。求区间和最大值。

### 题目分析

元素可能为负，所以本题并不只是找区间求和。

可以从前往后推一遍，如果 $a_i$ 与 $a_{i-1}$ 奇偶不同，就可以合并 $a_i$ 与上一个连续区间，或者从 $a_i$ 起重新计算区间。最后求最大值。

时间复杂度 $O(n)$。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200005],b[200005];//b数组可以省略
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",a+i),b[i]=a[i];
		int ans=a[1];
		for(int i=2;i<=n;ans=max(ans,b[i++]))
			if(abs(a[i])%2!=abs(a[i-1])%2)
				b[i]=max(a[i]+b[i-1],a[i]);
		printf("%d\n",ans);
	}
	return 0;
}
```
感谢您的阅读。

---

## 作者：Focalors (赞：1)

简要题意：长为 $n$ 的数组的最大子段和，但是子段内任意相邻两数奇偶性不能相同，求出这个和。

最大字段和变体。

若相邻两数奇偶相同，则可以将其分为前后两段，分别求出他们的最大子段和，然后取较大值即可。

取模时需注意，由于 `c++` 对负数取模的特殊性（`c++` 中 $-3 \bmod 2 = -1$），需对余数取绝对值。

至于最大子段和的求法，递推式是 $f(i)=\max\{f(i-1)+a_i,a_i\}$，然后答案是 $f$ 中的最大值。

时间复杂度 $\mathcal{O}(n)$。

代码：
```c++
#include <bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read() {
	ll x = 0, y = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-') y = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c & 15), c = getchar();
	return x * y;

}
const int N = 2e5 + 7;
ll T, n, a[N];
void fufu() {
	ll sum = a[1];
	ll ans = a[1];
	for (int i = 2; i <= n; i++) {
		if (abs(a[i - 1] % 2) == abs(a[i] % 2))
			sum = a[i]; 
		else sum = max(sum + a[i], a[i]);
		ans = max(ans, sum);
	}
	printf("%lld\n", ans);
}
int main() {
	T = read();
	while (T--) {
		n = read();
		for (int i = 1; i <= n; i++) {
			a[i] = read();
		}
		fufu();
	}
	return 0;
}
```

---

## 作者：tbdsh (赞：0)

# 题意简述
[洛谷原题面](https://www.luogu.com.cn/problem/CF1899C)

[CodeForces 原题面](https://codeforces.com/problemset/problem/1899/C)

有 $t$ 组数据。每组数据给定一个长度为 $n(1\le n\le 2\times 10^5)$ 的序列 $a(|a|\le 10^3)$。

请找到一个**连续**的子数组，满足该数组内的数字奇偶数是交替的，且子数组中所有数的和最大。

输出这个最大的和。

# 分析
这题可以用类似 DP 的思想解决。

不难发现，这题的转移方程为：

$$
dp_i=\begin{cases}
\max(a_i,dp_{i-1}+a_i) & a_i \bmod 2 + a_{i-1}\ \bmod 2 = 2\\
a_i & \text{otherwize}
\end{cases}
$$

最后的答案就是 $\max\{dp_i\}$。

时间复杂度：$O(n)$。
# Code
```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;
const int MAXN = 2e5 + 5;
int n, a[MAXN];
void Solve(){
  cin >> n;
  for (int i = 1; i <= n; i++){
    cin >> a[i];
  }
  int ans = a[1], tmp = a[1];
  for (int i = 2; i <= n; i++){
    if ((a[i] + 6000) % 2 == !((a[i - 1] + 6000) % 2)){
      tmp = max({a[i], tmp + a[i]});
    }else {
      tmp = a[i];
    }
    ans = max(ans, tmp);
  }
  cout << ans << '\n';
}
signed main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int t = 1;
  cin >> t;
  while (t--){
    Solve();
  }
  return 0;
}
```

---

## 作者：FireRain (赞：0)

# 思路

定义 $dp_i$ 表示选出一段以 $i$ 结尾的子串的最大和。

显然需要分类讨论一下：

1. 当不取 $i$ 之前的元素时，$dp_i = a_i$。

2. 当取 $i$ 之前的元素时，$dp_i = \max(dp_{i - 1},0) + a_i$，这里与 $0$ 取 $\max$ 是因为 $dp_{i - 1}$ 有可能为负。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long

using namespace std;

const int N = 2e5 + 10,inf = (int)(1e18) + 10;
int T,n;
int arr[N],dp[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline void solve(){
    int ans = -inf;
    n = read();
    for (re int i = 1;i <= n;i++) arr[i] = dp[i] = read();
    for (re int i = 2;i <= n;i++){
        if (abs(arr[i] & 1) != abs(arr[i - 1] & 1)) dp[i] = max(dp[i],max(dp[i - 1],0ll) + arr[i]);
    }
    for (re int i = 1;i <= n;i++) ans = max(ans,dp[i]);
    printf("%lld\n",ans);
}

signed main(){
    T = read();
    while (T--) solve();
    return 0;
}
```

---

## 作者：_O_v_O_ (赞：0)

~~这个蒟蒻打 CFdiv3 没 AK，太逊了。~~

前置知识：[最大子段和](https://www.luogu.com.cn/problem/P1115)。

众所周知，最大子段和的 dp 方式为：如果 $dp_{i-1}<0$ 就不选前面，否则选。

而该题如果 $a_{i-1}$ 和 $a_i$ 奇偶性不同（即 $|a_{i-1}-a_{i}|\bmod2=1$），则不能选它们。而在 dp 中，不选它们象征着不判定「$dp_{i-1}<0$」而直接让 $dp_i=a_i$（也就是不选前面）。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int T;
int n,a[200005],dp[200005],mx;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		mx=dp[1]=a[1];
		for(int i=2;i<=n;i++){
			if(abs(a[i]-a[i-1])%2==0) dp[i]=a[i];
			else dp[i]=max(dp[i-1],0)+a[i];
			mx=max(mx,dp[i]);
		}
		cout<<mx<<endl;
	}
	return 0;
}
```



---

## 作者：szhqwq (赞：0)

## $\tt{Solution}$

考虑 dp。

$dp_i$ 表示前 $i$ 个数中的子数组最大和（即最大子段和）。

我们令题目给定的序列为 $a$。

1. 当 $a_i$ 和 $a_{i - 1}$ 的奇偶性相同时，不能从 $i - 1$ 转移到 $i$，所以 $dp_i = a_i$；

2. 当 $a_i$ 和 $a_{i - 1}$ 的奇偶性不同时，考虑 $dp_{i - 1}$ 是否小于 $0$，小于 $0$ 则 $dp_i = a_i$，否则 $dp_i = dp_{i - 1} + a_i$。

[Link](https://codeforces.com/contest/1899/submission/233538449)

---

## 作者：bluewindde (赞：0)

有一道题叫做 [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)。

设 $dp_i$ 表示前 $i$ 个元素的答案。

同为奇数或偶数：$dp_i=\max(dp_{i-1}+a_i,a_i)$。（这里与 $a_i$ 取 $\max$ 是为了防止 $dp_{i-1}<0$ 取到更劣的结果）

奇偶性不同：$dp_i=a_i$。

代码

```cpp
#include <iostream>

#define int long long

using namespace std;

int T, n;
int a[200005];
int dp[200005];

static inline bool islegel(int x, int y)
{ // 判断奇偶性
    x = abs(x) % 2;
    y = abs(y) % 2;
    return x != y;
}

signed main()
{
#ifdef DEBUG
    freopen("T3.in", "r", stdin);
#endif
    cin >> T;
    while (T--)
    {
        cin >> n;
        for (int i = 1; i <= n; ++i)
        {
            cin >> a[i];
        }
        int ans = -1e18;
        for (int i = 1; i <= n; ++i)
        {
            if (i == 1 || islegel(a[i - 1], a[i]))
            {
                dp[i] = max(dp[i - 1] + a[i], a[i]);
            }
            else
            {
                dp[i] = a[i];
            }
            ans = max(ans, dp[i]);
        }
        cout << ans << endl;
    }
    return 0;
}

/*
gcc T3.cpp -o T3.exe -lstdc++ -std=c++2a -Wall -Wextra -Wconversion -Wshadow -DDEBUG
*/
```

---

