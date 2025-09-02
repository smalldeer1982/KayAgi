# [NOISG 2025 Prelim] Train Or Bus

## 题目描述

你是一名游客，希望探索一些城市。有 $n + 1$ 个城市，按顺序从 $1$ 到 $n + 1$ 编号。这些城市之间有一些公交车和火车运行。

为了在城市 $i$ 和城市 $i + 1$ 之间旅行，你有两种交通选项：

- 乘坐**火车**，需要 $a[i]$ 单位时间。
- 乘坐**公交车**，需要 $b[i]$ 单位时间。

确定从城市 $1$ 到城市 $n + 1$ 所需的最短总时间。


## 说明/提示

### 子任务

对于所有测试用例，输入将满足以下约束条件：

- $1 \leq n \leq 10$
- 对所有 $1 \leq i \leq n$，都有 $1 \leq a[i] \leq 10$
- 对所有 $1 \leq i \leq n$，都有 $1 \leq b[i] \leq 10$

你的程序将在满足以下特殊性质的输入数据上进行测试：

| 子任务 | 分数 | 特殊性质 |
| :-: | :-: | :-: |
| $0$ | $0$ | 样例 |
| $1$ | $100$ | 无 |

### 样例 1 解释

你从城市 $1$ 出发。然后：

- 从城市 $1$ 到城市 $2$ 乘坐火车（耗时 $7$ 单位）。
- 从城市 $2$ 到城市 $3$ 乘坐火车（耗时 $7$ 单位）。
- 从城市 $3$ 到城市 $4$ 乘坐公交车（耗时 $1$ 单位）。

总耗时为 $15$。


## 样例 #1

### 输入

```
3
7
7
5
9
8
1```

### 输出

```
15```

# 题解

## 作者：dg114514 (赞：12)

~~bushi 这能交题解？~~\
给红题写题解自然得写好一点。\
思路：使用贪心法，将每个选择上的两种方式取最小时间累加即可。\
证明：使用反证法。假设有路径 $p'$ 的总时间小于贪心选出的最优路径 $p$ 的总时间。那么显然，$p'$ 一定要有某次选择的时间短于 $p$ 才能优于 $p$。但是 $p$ 基于贪心，在所有选择路上选择的都是时间最小的方式。所以 $p'$ 不存在，$p$ 为最优路径。

---

## 作者：Yi_chen123 (赞：2)

## 思路

考虑贪心，为了保证时间最小化，每一次从城市 $i$ 到城市 $i+1$，一定要考虑最小的时间，即 $\min(a_i, b_i)$，那么从城市 $1$ 到 $n+1$，答案为每次行程最小时间之和，即

$$
\sum_{i=1}^{n} \min(a_i,b_i) = \min(a_1,b_1) + \min(a_2, b_2) + \cdots + \min(a_n,b_n)
$$

## 正解

```cpp
#include<bits/stdc++.h>
using namespace std;

int a[20], b[20];
int main(){
	int n, ans = 0;
	cin >> n;
	for(int i = 0; i < n; ++i) cin >> a[i];
	for(int i = 0; i < n; ++i) cin >> b[i];
	for(int i = 0; i < n; ++i) ans += min(a[i], b[i]);
	cout << ans << endl;
	return 0;
}
```

---

## 作者：ridewind2013 (赞：0)

## 分析

一共有 $n + 1$ 个城市，要从第 $1$ 个城市到第 $n + 1$ 个城市，从第 $i$ 个城市到第 $i + 1$ 个城市坐火车要花费 $a_{i}$ 的时间，坐公交车要花费 $b_{i}$ 的时间，求最短总时间是多少。

## 思路

运用贪心的思想，每次乘坐坐火车和坐公交车中花费时间最小的一个，也就是 $\min(a_{i},b_{i})$，然后累加到答案 $ans$ 里，最后直接输出 $ans$ 即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[20],b[20];//a数组是坐火车时间，b数组是坐公交车时间
int main(){
	int n;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)cin>>b[i];
    int ans=0;
    for(int i=1;i<=n;i++)ans+=min(a[i],b[i]);//贪心
    cout<<ans;//输出答案
	return 0;
}
```

---

## 作者：ylzpl (赞：0)

贪心捏，对于每一站的花费，我们肯定是优先取最小的，这样才能使总花费最小，所以我们可以从第 $1$ 站变量到第 $n$ 站的花费，每次加上 $\min(train_i,bus_i)$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int bus[15],train[15];//数据范围很小
signed main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>train[i];
	}
	for(int i=1;i<=n;i++)
	{
		cin>>bus[i];
	}
	int cost=0;
	for(int i=1;i<=n;i++)
	{
		cost+=min(train[i],bus[i]);//取最小的花费
	}
	cout<<cost;
	return 0;
} 
```

---

## 作者：Aamumatematiikka (赞：0)

题目要求从 $1$ 城市走到 $n+1$ 城市，也就是要乘坐 $n$ 站交通工具。每一站乘坐两种中耗时较短的一辆。

代码如下：

```cpp
#include <iostream>
using namespace std;
typedef long long ll;
const int N=15;
int n, a[N], b[N], ans=0;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) scanf("%d",&b[i]);
	for(int i=1;i<=n;i++) ans+=min(a[i],b[i]);
	return printf("%d",ans)&0;
}
```

总复杂度为 $\Omicron(n)$，足以 $\color{green}\text{AC}$ 这道题。

---

## 作者：Jerry_zpl (赞：0)

本题算法：贪心。  
我们可以这样想：题目既然让我们求最小费用，那么对于每一个站点，$i$ 到 $i+1$，我们都要选择费用最小的出行方式，即 $\min(a_i,b_i)$。所以我们从第 $i$ 到第 $i+1$ 站的花费就是 $\min(a_i,b_i)$。最后相加即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[1000005],b[1000005];
signed main(){
	int ans=0,n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
	}
	for(int i=1;i<=n;i++){
		ans+=min(a[i],b[i]);
	}
	cout<<ans;
	return 0;
} 
```

---

