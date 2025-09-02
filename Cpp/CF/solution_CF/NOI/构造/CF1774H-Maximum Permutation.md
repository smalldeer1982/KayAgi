# Maximum Permutation

## 题目描述

Ecrade 买了一副编号从 $1$ 到 $n$ 的牌。一个长度为 $n$ 的排列 $a$ 的价值定义为 $\min\limits_{i = 1}^{n - k + 1}\ \sum\limits_{j = i}^{i + k - 1}a_j$。

Ecrade 想要在所有排列中找到价值最大的那一个。然而，这似乎有点难，所以请你帮帮他！

## 说明/提示

在第一个测试用例中，$[1,4,5,3,2]$ 的价值为 $13$。可以证明，当 $k=4$ 时，没有长度为 $5$ 的排列的价值大于 $13$。

在第二个测试用例中，$[4,2,5,7,8,3,1,6]$ 的价值为 $18$。可以证明，当 $k=4$ 时，没有长度为 $8$ 的排列的价值大于 $18$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
5 4
8 4```

### 输出

```
13
1 3 4 5 2 
18
1 8 2 7 3 6 4 5```

# 题解

## 作者：Ecrade_ (赞：9)

题目即求一个 $1\sim n$ 的排列，使得所有长度为 $k$ 的区间和的最小值最大。

### 先考虑 $n$ 为 $k$ 倍数的情况。

为了方便表述，令 $t=\dfrac{n}{k}$。

考虑 $p_{[1:k]},p_{[k+1:2k]},\dots,p_{[n-k+1:n]}$ 这 $t$ 个区间。

显然这些区间覆盖了整个 $p$，它们的和为 $\dfrac{n(n+1)}{2}$。

注意到答案一定不大于这些区间和的平均值，即 $\dfrac{n(n+1)}{2t}=\dfrac{k(n+1)}{2}$，故我们可以尝试使答案尽量接近这个数。

**$k$ 为偶数**

这种情况较为简单，考虑构造 $p=[1,n,2,n-1,3,n-2,\dots,\dfrac{n}{2},\dfrac{n}{2}+1]$ 即可使答案等于上述平均值。

**$k$ 为奇数**

为了便于理解，我们将 $p_{[1:k]},p_{[k+1:2k]},\dots,p_{[n-k+1:n]}$ 这 $t$ 个区间依次从上至下拼接成一个 $t\times k$ 的表格，这样我们直接在表格中填数即可。


![](https://cdn.luogu.com.cn/upload/image_hosting/sppt7k67.png)

注意到相邻两个区间和的差值对应表格的同一列中相邻两数的差值，而一个比较直观的感受就是要“物尽其用”，即相邻两个区间和的差值要小一点更容易填完。

我们可以先把后 $k-3$ 列用 $3t+1\sim n$ 这些数按照“蛇行”的方式填完：

![](https://cdn.luogu.com.cn/upload/image_hosting/206nvzte.png)

这样，对于后 $k-3$ 列，每行的和相等且同一列中相邻两数的差值最小。

那么问题就转化为了：将 $1\sim 3t$ 这些数分成 $t$ 组，每组 $3$ 个数，使得每组的和尽量接近。

当 $n$ 为奇数时，若我们想使答案取到开头提到的那个平均值，那么我们只能让这 $t$ 组数的和均相等；而当 $n$ 为偶数时，平均值非整数，每组数的和不能确定。

故考虑先从 $n$ 为奇数的情况开始构造。

一种可行的构造方案为：

$$(1,\frac{3t+1}{2},3t),(3,\frac{3t-1}{2},3t-1),(5,\frac{3t-3}{2},3t-2),\dots,(t,t+1,\frac{5t+1}{2}),(2,2t,\frac{5t-1}{2}),(4,2t-1,\frac{5t-3}{2}),\dots,(t-1,\frac{3t+3}{2},2t+1)$$

按照如下的方式将这些数填入表格中：

![](https://cdn.luogu.com.cn/upload/image_hosting/2456g8yc.png)

可以证明，这样填能够取到平均值，有兴趣的话可以手玩下。

$n$ 为偶数的情况也可照葫芦画瓢按照如下的方式填完表格：

![](https://cdn.luogu.com.cn/upload/image_hosting/q5zl6p32.png)

至此，我们便成功解决了 $n$ 为 $k$ 倍数的情况。

### 再考虑 $n$ 非 $k$ 倍数的情况。

令 $n=qk+r\ (r,q\in \mathbb{N},1\le r<k)$。

考虑将排列 $p$ 进行如下划分：

![](https://cdn.luogu.com.cn/upload/image_hosting/a4ub3vdt.png)

容易发现 $p$ 被划分成了 $(q+1)$ 个长为 $r$ 的红色区间和 $q$ 个长为 $(k-r)$ 的蓝色区间。

考虑选取 $q$ 个互不相交的长为 $k$ 的区间，且每个区间均恰好包含一个红色区间和一个蓝色区间，那么答案不会超过这些区间和的平均值。

照此方法选取后，发现最终会剩下一个红色区间，故这些区间和为所有数之和减去剩下的红色区间和。

而发现这个剩下的红色区间可以为任意红色区间，故要想使答案的理论上界最大，需使所有红色区间的区间和的最大值最小。

可以证明，利用 $n$ 为 $k$ 倍数情况的填法依次填入红色圆圈中，恰能使所有红色区间的区间和的最大值最小。

同理，我们需使所有蓝色区间的区间和的最小值最大，而这也可利用同样的方法填入蓝色圆圈。

需要特判 $k=3$，$r=1$ 及 $k-r=1$ 这三种情况，而 $k=3$ 这种情况尤为繁琐，故未将其放在数据中。

还有一些细节未在题解中呈现出，大家可以自行手玩，这也不失为一个挺有意思的过程。

时间复杂度为 $O(\sum n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t,n,k,seq[100009],ans[100009];
inline ll read(){
	ll s = 0,w = 1;
	char ch = getchar();
	while (ch > '9' || ch < '0'){ if (ch == '-') w = -1; ch = getchar();}
	while (ch <= '9' && ch >= '0') s = (s << 1) + (s << 3) + (ch ^ 48),ch = getchar();
	return s * w;
}
ll f(ll x,ll y,ll k){return (x - 1) * k + y;}
void get(ll n,ll k){
	if (!(k & 1)){
		for (ll i = 1;i <= n >> 1;i += 1) seq[(i << 1) - 1] = i,seq[i << 1] = n + 1 - i;
		return;
	}
	ll m = n / k,cur = 3 * m;
	for (ll i = 4;i <= k;i += 1){
		if (i & 1) for (ll j = m;j >= 1;j -= 1) seq[f(j,i,k)] = ++ cur;
		else for (ll j = 1;j <= m;j += 1) seq[f(j,i,k)] = ++ cur;
	}
	for (ll i = 1;i <= (m + 1 >> 1);i += 1){
		seq[f(i,1,k)] = (i << 1) - 1;
		seq[f(i,2,k)] = ((3 * m + 3) >> 1) - i;
		seq[f(i,3,k)] = 3 * m - i + 1;
	}
	for (ll i = (m + 3 >> 1);i <= m;i += 1){
		ll delta = i - (m + 3 >> 1);
		seq[f(i,1,k)] = ((3 * m + 3) >> 1) + delta;
		seq[f(i,2,k)] = (m << 1) + 1 + delta;
		seq[f(i,3,k)] = m - (m & 1) - (delta << 1);
	}
}
void print(){
	ll res = 0,sum = 0;
	for (ll i = 1;i <= k;i += 1) sum += ans[i];
	res = sum;
	for (ll i = k + 1;i <= n;i += 1) sum += ans[i] - ans[i - k],res = min(res,sum);
	printf("%lld\n",res);
	for (ll i = 1;i <= n;i += 1) printf("%lld ",ans[i]);
	puts("");
}
int main(){
	t = read();
	while (t --){
		n = read(),k = read();
		if (!(n % k)){
			get(n,k);
			for (ll i = 1;i <= n;i += 1) ans[i] = seq[i];
			print();
			continue;
		}
		ll q = n / k,r = n % k;
		if (r == 1){
			ll cur = 0,delta = (q << 1) + 1;
			for (ll i = 1;i <= n;i += k) ans[i] = ++ cur;
			for (ll i = n - k + 1;i >= 2;i -= k) ans[i] = ++ cur;
			get(q * (k - 2),k - 2),cur = 0;
			for (ll i = 3;i <= n;i += k) for (ll j = i;j <= i + k - 3;j += 1) ans[j] = seq[++ cur] + delta;
			print();
			continue;
		}
		if (k - r == 1){
			if (q == 1){
				ll cur = 0;
				ans[k] = n;
				get(n - 1,k - 1);
				for (ll i = 1;i < k;i += 1) ans[i] = seq[++ cur];
				for (ll i = k + 1;i <= n;i += 1) ans[i] = seq[++ cur];
				print();
				continue;
			}
			ll cur = n + 1,delta = q + 1;
			for (ll i = k;i <= n;i += k) ans[i] = -- cur;
			cur = 0;
			for (ll i = 1;i <= n;i += k) ans[i] = ++ cur;
			get((q + 1) * (r - 1),r - 1),cur = 0;
			for (ll i = 2;i <= n;i += k) for (ll j = i;j <= i + r - 2;j += 1) ans[j] = seq[++ cur] + delta;
			print();
			continue;
		}
		ll cur = 0,delta = (q + 1) * r;
		get((q + 1) * r,r);
		for (ll i = 1;i <= n;i += k) for (ll j = i;j <= i + r - 1;j += 1) ans[j] = seq[++ cur];
		get(q * (k - r),k - r),cur = 0;
		for (ll i = r + 1;i <= n;i += k) for (ll j = i;j <= i + (k - r) - 1;j += 1) ans[j] = seq[++ cur] + delta;
		print();
	}
	return 0;
}
```


---

