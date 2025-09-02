# [ARC037C] 億マス計算

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc037/tasks/arc037_c

高橋君は「$ N^2 $マス計算」で計算力をつけることにした。「$ N^2 $マス計算」は $ N $ 行 $ N $ 列の表を用意して行う。 $ i $ 行目の左端のマスのさらに左には数 $ a_i $ が書かれており、 $ j $ 列目の上端のマスのさらに上には数 $ b_j $ が書かれている。高橋君はこの表の $ i $ 行 $ j $ 列目 に $ a_i\ ×\ b_j $ の値を計算して書き込む。

すぐに解き終わってしまい退屈したので、高橋君は自分が書き込んだ $ N^2 $ 個の値を昇順に並べ替えることにした。並べ替えた結果小さい方から $ K $ 番目 ($ 1 $ 番から数える) に位置する値を求めよ。

## 说明/提示

### 部分点

この問題には部分点が設定されている。

- $ 5 $ 点分のテストケースは $ 1 $ $ ≦ $ $ N $ $ ≦ $ $ 10 $ を満たす。

### Sample Explanation 1

!\[\](http://arc037.contest.atcoder.jp/img/arc/037/ljlefijfewkjfwefk/C\_sample1.png) 高橋君が書き込んだ値を昇順に並べ替えると $ 6,\ 9,\ 10,\ 15 $ となり、小さい方から $ 3 $ 番目の値は $ 10 $ となる。

### Sample Explanation 2

!\[\](http://arc037.contest.atcoder.jp/img/arc/037/ljlefijfewkjfwefk/C\_sample2.png) 高橋君が書き込んだ値を昇順に並べ替えると $ 1,\ 1,\ 2,\ 2,\ 2,\ 2,\ 2,\ 4,\ 4 $ となり、小さい方から $ 7 $ 番目の値は $ 2 $ となる。

## 样例 #1

### 输入

```
2 3
2 3
3 5```

### 输出

```
10```

## 样例 #2

### 输入

```
3 7
1 2 1
2 1 2```

### 输出

```
2```

## 样例 #3

### 输入

```
4 8
701687787 500872619 516391519 599949380
458299111 633119409 377269575 717229869```

### 输出

```
317112176525562171```

# 题解

## 作者：yzx3195 (赞：2)

# 题目大意
给你两个长度为 $n$ 的数组 $a$，$b$，现在将两个数组内的元素两两相乘，求在新数组中第 $k$ 小的数是多少。
# 做法
显然，暴力并不可行，考虑二分答案。

我们每次二分出一个答案 $midl$，然后在 $b$ 数组中查找有几个数是大于 $midl$ 的，然后与 $k$ 比较就可以知道二分出来的答案的合法性。

那怎么查找？显然也可以用二分。这样就结束了。

~~听说这道题是模板~~。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e04 * 5 + 7;

#define int long long

int n, k;

int a[MAXN];

int b[MAXN];

int ans;

bool check(int midl)
{
	int cnt = 0;
	for(int i = 1; i <= n; i++)
	{
		int l = 1, r = n, lim = midl / a[i];
		while(l <= r)
		{
			int mid = (l + r) >> 1;
			if(lim >= b[mid])
				l = mid + 1;
			else
				r = mid - 1;
		}
		cnt += (r);
	}
//	cout << cnt << "\n";
	return cnt >= k;
}

signed main()
{
	scanf("%lld%lld", &n, &k);
	
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
		
	for(int i = 1; i <= n; i++)
		scanf("%lld", &b[i]);
	
	sort(b + 1, b + n + 1);
		
	int l = 0, r = 1e18;
	
	while(l <= r)
	{
		int mid = (l + r) >> 1;
		if(!check(mid))
			l = mid + 1;
		else
			r = mid - 1;
	}
	
	printf("%lld\n", ++r);
	
	return 0;
}
```

---

## 作者：_czy (赞：1)

## 分析

这题其实不难，主要是二分。

先将 $b$ 数组排序，然后二分第 $k$ 小等于多少，$check$ 函数就枚举每个 $a_i$，通过二分 $b_j$ 计算有几个数大于二分出来的答案。

详见代码。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[30002],b[30002];
#define ll long long
ll l,r=1e18,mid,s;
bool check(ll x){
	int s=0;
	for(int i=1;i<=n;i++){
		s+=upper_bound(b+1,b+n+1,x/a[i])-b-1;
	}
	return s>=k;
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)scanf("%d",a+i);
	for(int i=1;i<=n;i++)scanf("%d",b+i);
	sort(b+1,b+n+1);
	while(l<=r){
		mid=l+r>>1;
		if(check(mid))r=mid-1;
		else l=mid+1;
	}
	printf("%lld\n",r+1);
}
```

---

## 作者：Brute_Force (赞：0)

### 做法

二分。

首先，我们对 $a,b$ 两个数组进行排序。接下来，枚举一个答案 $x$，将然后在 $b$ 数组中查找有几个数是大于 $x$ 的。比较 $k$，验证答案 $x$ 是否是我们想要的。

枚举和查找都用二分优化，可以通过此题。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, k, a[30000 + 5], b[30000 + 5];
bool check (long long x) {
	long long c = 0;
	for (long long i = 1; i <= n; i++) {
		long long l = 1, r = n, y = x / a[i];
		while (l <= r) {
			long long mid = (l + r) / 2;
			if (y >= b[mid]) l = mid + 1;
			else r = mid - 1;
		}
		c += r;
	}
	return c >= k;
}
int main() {
	cin >> n >> k;
	for (long long i = 1; i <= n; i++) cin >> a[i];
	for (long long i = 1; i <= n; i++) cin >> b[i];
	sort (a + 1, a + n + 1);
	sort (b + 1, b + n + 1);
	long long l = 0, r = 1e18;
	while (l <= r) {
		long long mid = (l + r) / 2;
		if (!check (mid)) l = mid + 1;
		else r = mid - 1;
	}
	cout << r + 1 << endl;
	return 0;
}
```

---

## 作者：UnfortunatelyDead (赞：0)

发现第 $x$ 小值一定是按照不降序排列的，那么一定具有单调性，可以二分第 $k$ 小值。

具体地，二分出答案 $mid$，我们算小于等于 $mid$ 的 $a_i \times b_j$ 的个数，考虑一下如何写 `check` 函数。

考虑对 $a,b$ 排序后，每个序列都满足单调性，于是考虑枚举 $a_i$，求 $a_i \times b_j \leq mid$ 其实就是求 $b_j \leq \frac{mid}{a_i}$，我们前面说了存在单调性，所以可以继续二分 $b_j$。

复杂度 $O(n \log^2 n)$。

```cpp
const int N = 30019;
int a[N], b[N];
void solve() {
	int n, k; read(n, k);
	for (int i = 1; i <= n; ++i) read(a[i]);
	for (int i = 1; i <= n; ++i) read(b[i]);
	sort(a + 1, a + 1 + n); sort(b + 1, b + 1 + n);
	auto check = [&](int x) -> bool {
		int cnt = 0;
		for (int i = 1; i <= n; ++i) cnt += upper_bound(b + 1, b + 1 + n, x / a[i]) - b - 1;
		return cnt >= k;
	};
	int l = 1, r = 1e18 + 19;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (check(mid)) r = mid;
		else l = mid+1;
	}
	write(l, '\n');
}
```

---

