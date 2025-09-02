# Brooklyn Round 1 & NNOI Round 1 B - Gift

## 题目背景

我想要礼物！

## 题目描述

有 $n$ 名同学要来参加生日会，小 X 对第 $i$ 名同学的好感度为 $a_i$，他会带来价值为 $b_i$ 的礼物。随着人越来越多，小 X 会对礼物逐渐失去兴趣。小 X 对第 $i$ 名同学的兴趣度为 

$s_i = \begin{cases}
	a_i & b_i < \sum_{j = 1}^{i-1} b_j \\
	a_i \times b_i & b_i \ge \sum_{j = 1}^{i-1} b_j
\end{cases}$

你可以改变同学来的顺序，请你求出兴趣度之和最大值，也就是 $\sum_{i = 1}^{n} s_i$。

## 说明/提示

**本题采用捆绑测试。**

+ Subtask 1（10pts）：$n = 1$。

+ Subtask 2（20pts）：$n = 1000$。

+ Subtask 3（10pts）：$b_i = 1$。

+ Subtask 4（60pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le n \le 5 \times 10^5,b_i \ge 1,1 \le \sum_{i = 1}^{n} b_i \le 5 \times 10^6,1 \le a_i \le 10^8$。

## 样例 #1

### 输入

```
5
1 2 3 4 5
5 4 3 2 1
```

### 输出

```
29```

# 题解

## 作者：__CJY__ (赞：1)

官解讲得不太清楚，特来补一篇。
## 思路
当 $b_i \ge \sum\limits_{j=1}^{i-1} b_j$ 时，$s_i=a_i \times b_i=a_i+a_i \times (b_i-1)$，所以设权值为 $a_i \times (b_i-1)$。

然后将 $b$ 排序，记得用结构体绑定 $a,b$ 再进行排序。

设 $k$ 为当前 $b_i$ 的总和，接下来从 $\min(k,b_i)$ 开始向前枚举，避免重复计算。

我们设 $f_i$ 为当前已选同学的 $b_i$ 之和为 $i$ 时，能获得的**最大额外权值**和，动态转移方程过于明显，没什么好讲的：
$$f_{j+b_i}=\max(f_{j+b_i},f_j+a_i \times (b_i-1))$$

然后更新总礼物价值 $k \gets k+b_i$。

结果就为 $\left(\max\limits_{i=1}^{5 \times 10^6}f_i\right)+\sum\limits_{i=1}^na_i$，$\sum\limits_{i=1}^na_i$ 就是把 $a_i+a_i \times (b_i-1)$ 中的 $a_i$ 加上，因为我们设的权值是 $a_i \times (b_i-1)$。

注意要开 `long long`，$f$ 的范围要开到 $5 \times 10^6$ 而不是 $5 \times 10^5$！

有问题请指出！

---

## 作者：Tjaweiof (赞：1)

# P12678 题解
[题目传送门](https://www.luogu.com.cn/problem/P12678)

先考虑把所有准备让 $s_i=a_i$ 的扔到最后面，发现不影响前面的选择。

考虑把所有准备让 $s_i=a_i\times b_i$ 的按照 $b_i$ 排序，发现更优。

所以先按照 $b_i$ 排序。问题转化成了，选择一个序列 $c_1,c_2,\dots,c_k$ 使得对于每个 $1\le i\le k$，$b_i\ge\sum_{j=1}^{i-1}b_j$。求：在序列 $c$ 符合要求的前提下，$\sum_{i=1}^na_i+\sum_{i=1}^ka_i\times b_{i-1}$ 的最大值。

枚举 $i$，设 $dp_j$ 为将 $i$ 加入序列 $c$ 的最大答案，那么就很好转移了。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define FILE(x) freopen(x".in", "r", stdin);freopen(x".out", "w", stdout);
int n;
long long dp[5000001], sum, ans;
pair <long long, long long> a[500001];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> a[i].second;
		sum += a[i].second;
	}
	for (int i = 1; i <= n; i++){
		cin >> a[i].first;
	}
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++){
		for (int j = a[i].first; j >= 0; j--){
			dp[j + a[i].first] = max(dp[j + a[i].first], dp[j] + (a[i].first - 1) * a[i].second);
			ans = max(ans, dp[j + a[i].first]);
		}
	}
	cout << ans + sum;
	return 0;
}
```

---

## 作者：篮网总冠军 (赞：0)

本题是一个 dp 基础题。

我们考虑先对所有同学按照 $b_i$ 排序。

我们先假设每个同学的权值是 $a_i \times (b_i-1)$。

我们设 $dp_i$ 代表选了 $b$ 总和为 $i$ 的同学最大权值和。

我们思考，如果我们要选第 $i$ 个同学，那么之前所有选的同学加起来一定不能超过 $b_i$。

不用判断这个权值是否存在，因为就算存在，也一定不是最优解。

代码如下：


```cpp
#include <bits/stdc++.h>
using namespace std;

struct node{
	long long a,b;
}a[500005];
long long dp[5000005];
bool cmp(node x,node y){
	return x.b<y.b;
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i].a;
	for(int i=1;i<=n;i++) cin>>a[i].b;
	sort(a+1,a+1+n,cmp);
	long long rt=0,ans=0;
	for(int i=1;i<=n;i++){
		for(int j=min(rt,a[i].b);j>=0;j--){
			dp[j+a[i].b]=max(dp[j+a[i].b],dp[j]+a[i].a*(a[i].b-1)); 
		}
		rt+=a[i].b;
	}
	for(int i=1;i<=5000000;i++) ans=max(ans,dp[i]);
	for(int i=1;i<=n;i++) ans+=a[i].a;
	cout<<ans<<endl;
	return 0;
}

```

---

