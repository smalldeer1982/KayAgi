# Three-level Laser

## 题目描述

An atom of element X can exist in $ n $ distinct states with energies $ E_{1}<E_{2}<...<E_{n} $ . Arkady wants to build a laser on this element, using a three-level scheme. Here is a simplified description of the scheme.

Three distinct states $ i $ , $ j $ and $ k $ are selected, where $ i<j<k $ . After that the following process happens:

1. initially the atom is in the state $ i $ ,
2. we spend $ E_{k}-E_{i} $ energy to put the atom in the state $ k $ ,
3. the atom emits a photon with useful energy $ E_{k}-E_{j} $ and changes its state to the state $ j $ ,
4. the atom spontaneously changes its state to the state $ i $ , losing energy $ E_{j}-E_{i} $ ,
5. the process repeats from step 1.

Let's define the energy conversion efficiency as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF924B/dd021747dbc78de91e905a31390ad0cfead20383.png), i. e. the ration between the useful energy of the photon and spent energy.

Due to some limitations, Arkady can only choose such three states that $ E_{k}-E_{i}<=U $ .

Help Arkady to find such the maximum possible energy conversion efficiency within the above constraints.

## 说明/提示

In the first example choose states $ 1 $ , $ 2 $ and $ 3 $ , so that the energy conversion efficiency becomes equal to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF924B/dce12a2cd3991eb50251b026c5d21e8a7972a1a8.png).

In the second example choose states $ 4 $ , $ 5 $ and $ 9 $ , so that the energy conversion efficiency becomes equal to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF924B/92eb31d78d8cae5d41f0d6508215bf8fc27fa5c7.png).

## 样例 #1

### 输入

```
4 4
1 3 5 7
```

### 输出

```
0.5
```

## 样例 #2

### 输入

```
10 8
10 13 15 16 17 19 20 22 24 25
```

### 输出

```
0.875
```

## 样例 #3

### 输入

```
3 1
2 5 10
```

### 输出

```
-1
```

# 题解

## 作者：_edge_ (赞：1)

警告，这是乱搞做法，非正解！！！

我们可以先枚举 $k$ 这个点，然后来确定一下 $i,j$。

由于题目限制，所以 $i$ 的左边界可以很轻松的确定，用二分就可以了。

但是有一个问题就是如何确定 $i,j$ 这两个点具体的位置。

在这里我们用一种更加神奇的做法，我们设一个阈值 $B=\dfrac{10^8}{n}$，然后向后扫描然后扫 $B$ 个就停下来，很容易发现他答案比较靠近，因此这样做是有很大概率对的。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int INF=1e5+5;
int n,e,a[INF];
double res;
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>e;
	for (int i=1;i<=n;i++) cin>>a[i];
	res=-1;
	int B=1e8;
	B/=n;
	for (int i=3;i<=n;i++) {
		int l=1,r=i,ans=1;
		while (l<=r) {
			int Mid=(l+r)>>1;
			if (a[i]-a[Mid]<=e) r=(ans=Mid)-1;
			else l=Mid+1;
		}
		if (ans>=i-1) continue;
		if (ans==-1) continue;
		for (int I=max(1,ans);I<=min(i-2,ans+B);I++) {
			res=max(res,1.0*(a[i]-a[I+1])/(a[i]-a[I]));
		}
	}
	printf("%.11lf\n",res);
	return 0;
}
```


---

## 作者：codwarm (赞：0)

[题目传送门~](https://www.luogu.com.cn/problem/CF924B)

## 题目分析
主要思路：枚举每个 $i$，求出对应最佳情况的 $j$ 和 $k$，取最大值。

- 当 $i$,$k$ 固定时，显然 $E_k-E_i$ 为定值。此时 $E_k-E_j$ 应取最大值，即 $E_j$ 取最小值，$j$ 应取最小值为 $i+1$。

- 当 $i$,$j$ 固定时，$\frac{E_k-E_j}{E_k-E_i} $ 取最大值当且仅当 $E_k$ 取得最大值且 $E_k - E_i \le U$。具体证明见下。这一步可以用二分解决。

证明：$\frac{E_k-E_j}{E_k-E_i} $ 取最大值当且仅当 $E_k$ 取得最大值。

假设存在 $E_{k_1} < E_{k_2},x = E_{k_2} - E_{k_1}$ 使得：

$$\frac{E_{k_1}-E_j}{E_{k_1}-E_i} > \frac{E_{k_2}-E_j}{E_{k_2}-E_i} $$

换元简化式子可得：

$$\frac{a}{b} > \frac{a+x}{b+x}  (a > 0,b>0,x>0) $$
进一步化简得：
$$a > b$$
显然矛盾，故假设不成立，原命题成立。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5+5;
int n,k,a[N];
double res = -1;

int find(int i)
{
	int x = a[i]+k,l = i+2,r = n;	
	while (l < r) // 二分
	{
		int mid = l + r + 1 >> 1;
		if (a[mid] <= x) l = mid;
		else r = mid-1;
	}
	if (a[l] <= x) return l;
	else return -1;
}

int main()
{
	scanf("%d%d",&n,&k);
	for (int i = 1;i <= n;i++) scanf("%d",&a[i]);
	for (int i = 1;i <= n-2;i++)
	{
		int x = find(i);
		if (x == -1) continue; // i j k 分别为 i i+1 x
		res = max(res,1.0*(a[x]-a[i+1])/(a[x]-a[i]));	
	}
	if (res < 0) puts("-1"); //不存在
	else printf("%.10f",res);
	return 0;
}
```


---

## 作者：梦应归于何处 (赞：0)

### 题目大意
有一个长度为 $n(n\le 10^5)$ 的严格单调递增整数序列 $\{E\}(E_i\le 10^9)$。求 $i,j,k(i<j<k)$ 使得 $\eta=\frac{E_k-E_j}{E_k-E_i}$ 最大且 $E_k-E_i\le U(U\le 10^9)$。输出这个 $\eta$。

### 思路

我们先假设我们已经知道了 $i$ 和 $k$。那么 $j$ 应该放在哪里呢？最优情况下 $j$ 应该等于 $i+1$ 因为 $E_k-E_i$ 已经确定了，我们知道分母相同的时候，分子越大这个数越大，所以 $j$ 应该等于 $i+1$。

根据上面我们说的，我们只要枚举 $i$ 就可以知道 $j$ 那么，$k$ 应该是什么呢？我们发现 $k$ 越往后越好，但是我们不要忘记题目中有一个条件：$E_k - E_i \le U$。所以我们要在 $E$ 数组中找到一个和 $E_i$ 相差小于等于 $U$ 的最后面的一个数。这个过程可以用二分实现。

总时间复杂度：$O(n \log n)$。

### 代码

~~~cpp
#include <bits/stdc++.h>
#define db double
#define ll long long
#define ex exit(0)
#define endl "\n"
#define inl inline
#define null NULL
#define pb(a) push_back(a)
using namespace std;
ll e[200000];
int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ll n, u;
	cin >> n >> u;
	for (int i = 0; i < n; i++) {
		cin >> e[i];
	}
	double ans = -1e9;
	for (int i = 0; i < n - 2; i++) {
		ll j = i + 1;
		ll k = upper_bound(e, e + n, e[i] + u) - e - 1;
		if (k - i >= 2) {
			ans = max(ans, double(double(e[k] - e[j]) / (e[k] - e[i])));
		}
	}
	if (ans < 0) {
		cout << "-1";
	} else {
		printf("%.12lf", ans);
	}
	return 0;
}
~~~

---

