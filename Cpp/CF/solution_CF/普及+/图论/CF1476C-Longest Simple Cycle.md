# Longest Simple Cycle

## 题目描述

You have $ n $ chains, the $ i $ -th chain consists of $ c_i $ vertices. Vertices in each chain are numbered independently from $ 1 $ to $ c_i $ along the chain. In other words, the $ i $ -th chain is the undirected graph with $ c_i $ vertices and $ (c_i - 1) $ edges connecting the $ j $ -th and the $ (j + 1) $ -th vertices for each $ 1 \le j < c_i $ .

Now you decided to unite chains in one graph in the following way:

1. the first chain is skipped;
2. the $ 1 $ -st vertex of the $ i $ -th chain is connected by an edge with the $ a_i $ -th vertex of the $ (i - 1) $ -th chain;
3. the last ( $ c_i $ -th) vertex of the $ i $ -th chain is connected by an edge with the $ b_i $ -th vertex of the $ (i - 1) $ -th chain.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1476C/c3d2e7e1f5aff9aaa07bb3c082d03d1303c3b897.png)Picture of the first test case. Dotted lines are the edges added during uniting processCalculate the length of the longest simple cycle in the resulting graph.

A simple cycle is a chain where the first and last vertices are connected as well. If you travel along the simple cycle, each vertex of this cycle will be visited exactly once.

## 说明/提示

In the first test case, the longest simple cycle is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1476C/85078a1da0cf5e3248371659b535343ffec9669a.png)We can't increase it with the first chain, since in such case it won't be simple — the vertex $ 2 $ on the second chain will break simplicity.

## 样例 #1

### 输入

```
3
4
3 4 3 3
-1 1 2 2
-1 2 2 3
2
5 6
-1 5
-1 1
3
3 5 2
-1 1 1
-1 3 5```

### 输出

```
7
11
8```

# 题解

## 作者：registerGen (赞：4)

[可能更好的阅读体验](https://registergen.github.io/post/solution-cf1476c/)

A simple dp problem.

# Solution

应该能看出来是个 dp。

设 $f_i$ 表示用前 $i$ 条链，且第 $i$ 条链必须选所能组成的最大的环。

则：

$$f_i=\begin{cases}c_i+1,&a_i=b_i\\\max(c_i+1+f_{i-1}-|a_i-b_i|,c_i+1+|a_i-b_i|),&a_i\ne b_i\end{cases}$$

可以结合下图理解。

![](https://i.loli.net/2021/02/01/rIAniPFqdxVUuWY.png)

答案即为 $f_1\sim f_n$ 中的最大值。

# Code

<https://codeforces.com/contest/1476/submission/105896470>

---

## 作者：QWQ_123 (赞：1)

考虑 DP，设 $f_i$ 表示前 $i$ 个能组成的最大环的长度。

那么若当前连着前一个是 $a_i = b_i$，那么显然上一个就是这个环的开始，不然就不是简单环了。

所以若 $a_i = b_i$ 则 $f_i = 1$。

否则要么从前一个继承过来，即 $f_i = f_i - 1 + \left | a_i - 1 \right | + \left | l_{i-1} - b_i \right | + 2$。

要么从前一个重新开一个，即 $f_i = \left | a_i - b_i \right | + 1$。

然后两者取最大值，用 $f_i + l_i$ 取最大即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int T;
int n;
int l[100010];
ll f[100010];
int a[100010], b[100010];

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);

		for (int i = 1; i <= n; ++i) scanf("%d", &l[i]);
		for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &b[i]); if (b[i] < a[i]) swap(a[i], b[i]);
		}
		a[1] = b[1] = 1;

		f[1] = 0;
		f[2] = b[2] - a[2] + 1;
		ll ans = 0;
		ans = max(ans, f[2] + l[2]);

		for (int i = 3; i <= n; ++i) {
			if (a[i] == b[i]) f[i] = 1;
			else f[i] = max(f[i - 1] + abs(a[i] - 1) + abs(b[i] - l[i - 1]) + 2, 1ll * abs(a[i] - b[i]) + 1ll);
			// cout << f[i] << endl;
			ans = max(ans, f[i] + l[i]);
		}

		printf("%lld\n", ans);

	}
	return 0;
}
```

---

## 作者：henrytb (赞：1)

考虑扫一遍这些链。

我们定义“半圈”表示差一条链子的一部分就可以变成一个环的部分。例如下图中的红色链与绿色链都是半圈。

![](https://cdn.luogu.com.cn/upload/image_hosting/rb180dqg.png)

记目前到的这个半圈的长度为 $now$。

我们每到一个链子，都有以下两种操作：

- 放弃前面的部分，从这个链子开始继续考虑；

- 将这个链子接上前面的链子作为一个半圈，继续维护半圈长度。

同时，在遍历的时候随时对当前的半圈长度加上当前遍历到的链与左侧连接点两点之间距离取 $\max$。详见代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
int _,n,c[100005],a[100005],b[100005];
int now=0,ans=0;
signed main() {
    for(scanf("%lld",&_);_;--_) {
        now=0;ans=0;
        scanf("%lld",&n);
        rep(i,1,n) {
            scanf("%lld",&c[i]);
        }
        rep(i,1,n) scanf("%lld",&a[i]);
        rep(i,1,n) scanf("%lld",&b[i]);
        per(i,n,2) {
            if(!now) now=c[i]-1;
            if(a[i]==b[i]) ans=max(ans,now+2),now=0;
            else {
                now+=2;
                ans=max(ans,now+abs(a[i]-b[i]));
                now+=c[i-1]-1-abs(a[i]-b[i]);
                if(c[i-1]-1>now) now=c[i-1]-1;
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：ka_da_Duck (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1476C)

思路
-
一眼题，考虑 dp 做法

很容易看出，如果是成环的话有两种情况

- 与上一条链连接的起点，终点所连节点重合（$a_i=b_i$），那么前一个的最大值要舍去，环长度为 $f_i=a_i + 1$。

- 起点，终点不重合（$a_i\ne b_i$），那么可以对前一条链组成的环进行选择。容易得到 $f_i=\max(f_{i - 1} + a_i + 1 - \left|b_i - c_i\right|,a_i + 1 + \left|b_i - c_i\right|)$。

代码
-
```cpp
#include <bits/stdc++.h>
#define int long long
#define ios ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)

using namespace std;
const int maxn = 1e5 + 10;

int n;
int a[maxn], b[maxn], c[maxn];
int f[maxn];

inline void solve() {
	cin >> n;
	int ans = 0;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= n; ++i) cin >> b[i];
	for (int i = 1; i <= n; ++i) cin >> c[i];
	f[1] = 1;
	for (int i = 2; i <= n; ++i) {
		if (b[i] == c[i]) f[i] = (a[i] - 1) + 2;
		else f[i] = max(f[i - 1] + a[i] - 1 + 2 - abs(b[i] - c[i]), a[i] - 1 + 2 + abs(b[i] - c[i]));
		ans = max(ans, f[i]);
	}
	cout << ans << '\n';
}

signed main() {
	ios;
	int t;
	cin >> t;
	while (t--) solve();
}
```

---

## 作者：copper_ingot (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1476C)

显然 DP。

首先，定义 $r_i$ 为 $|a_i - b_i|$。图中一条链上红色线段的长度就是其下一条链的 $r_i$。

![](https://cdn.luogu.com.cn/upload/image_hosting/qk8pt9b2.png?x-oss-process=image/resize,m_lfit,h_340,w_450)

样例中的 $r$ 数组为：$[0,1,0,1]$。

接下来就可以开始考虑递推公式了。

定义 $dp_i$ 为以第 $i$ 条链为最右边时环的最长长度，显然 $dp_1 = 0$。假设我们现在要求 $dp_i$。

![](https://cdn.luogu.com.cn/upload/image_hosting/9cpu70dd.png?x-oss-process=image/resize,m_lfit,h_340,w_450)

上图红色线为第 $i$ 条链和它向左连的两条边，其长度为 $c_i + 1$。注意 $c_i$ 表示第 $i$ 条链的实际长度加一。

蓝色线为 $dp_{i - 1}$ 长度的环，是以第 $(i-1)$ 条链为最右边时的最优解。绿色线为红色线和第 $(i-1)$ 条链的两个连接点间的连线，其长度为 $|a_i - b_i|$，即 $r_i$。

现在红色边有两种方式可以和蓝色边的一部分连成环：

![](https://cdn.luogu.com.cn/upload/image_hosting/z2i9ke1t.png?x-oss-process=image/resize,m_lfit,h_340,w_450)

1. 和蓝色线左边的一段连接，其总长度为 $c_i+1+dp_{i-1}-r_i$；

![](https://cdn.luogu.com.cn/upload/image_hosting/g7n4r4la.png?x-oss-process=image/resize,m_lfit,h_340,w_450)

2. 和蓝色线右边的一段连接，其总长度为 $c_i+1+r_i$。

所以，递推公式就是：$\max(c_i+1+dp_{i-1}-r_i,c_i+1+r_i)$。

当然还是有特殊情况的，比如 $r_i = 0$ 时：

![](https://cdn.luogu.com.cn/upload/image_hosting/1u8wlf2a.png?x-oss-process=image/resize,m_lfit,h_340,w_450)

显然此时红色线已经形成一个环，并且没法向左连接，所以 $dp_i$ 只能等于 $c_i+1$。

最后的答案是所有 $dp_i$ 中的最大值。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long//不开long long见祖宗
int t, n, c[100001], a[100001], b[100001], r[100001], dp[100001], maxn;
signed main(){
	scanf("%lld", &t);
	while (t--){
		scanf("%lld", &n);
		for (int i = 1; i <= n; i++) scanf("%lld", &c[i]);
		for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		for (int i = 1; i <= n; i++) scanf("%lld", &b[i]);
		maxn = 0;
		for (int i = 2; i <= n; i++) r[i] = abs(a[i] - b[i]);//求r数组
		for (int i = 2; i <= n; i++){
			if (!r[i]) dp[i] = c[i] + 1;
			else dp[i] = max(c[i] + 1 + dp[i - 1] - r[i], c[i] + 1 + r[i]);//DP
			maxn = max(maxn, dp[i]);
		}
		printf("%lld\n", maxn);
	}
	return 0;
}
```

---

