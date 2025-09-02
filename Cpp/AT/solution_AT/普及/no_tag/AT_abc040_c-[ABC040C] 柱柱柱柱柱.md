# [ABC040C] 柱柱柱柱柱

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc040/tasks/abc040_c

$ N $ 本の木の柱が左から右へ一列に並んだアスレチックがあります。左から $ i $ 本目の柱の高さは $ a_i $ センチメートルです。

高橋君は左から $ 1 $ 本目の柱からスタートし、右へ柱を渡っていき $ N $ 本目の柱まで行こうとしています。

高橋君がある柱にいるとき、次には現在の柱から $ 1 $ 個もしくは $ 2 $ 個右にある柱のどちらかへ移動することができます。

移動するときには、現在いる柱の高さと、移動後の柱の高さの差の絶対値のぶんだけコストがかかります。

$ N $ 本目の柱まで行くとき、コストの合計の最小値はいくらになるでしょうか。

## 说明/提示

### 制約

- $ 2\ ≦\ N\ ≦\ 100,000 $
- $ 0\ ≦\ a_i\ ≦\ 10,000 $
- $ a_i $ はすべて整数である。

### Sample Explanation 1

このケースでは以下のような移動によって最小コストを達成できる。 - $ 1 $ 本目の柱から $ 3 $ 本目の柱へ移動する。(コスト $ 30 $) - $ 3 $ 本目の柱から $ 4 $ 本目の柱へ移動する。(コスト $ 10 $) 合計コストは $ 40 $ となる。

### Sample Explanation 2

このケースでは以下のような移動によって最小コストを達成できる。 - $ 1 $ 本目の柱から $ 2 $ 本目の柱へ移動する。(コスト $ 25 $) - $ 2 $ 本目の柱から $ 4 $ 本目の柱へ移動する。(コスト $ 15 $) 合計コストは $ 40 $ となる。

## 样例 #1

### 输入

```
4
100 150 130 120```

### 输出

```
40```

## 样例 #2

### 输入

```
4
100 125 80 110```

### 输出

```
40```

## 样例 #3

### 输入

```
9
314 159 265 358 979 323 846 264 338```

### 输出

```
310```

# 题解

## 作者：user470883 (赞：3)

~~值得一题的是，这个题目名字好好玩。~~

## 思路：

动态规划。

显然，第 $i$ 根柱子必定是由第 $i-1$ 根柱子和第 $i-2$ 根柱子决定的，那么这是不是有些像熟悉的走楼梯问题呢？

经过观察写出转移方程：

$$f_i=\min(f_{i-1}+|a_i-a_{i-1}|,f_{i-2}+|a_i-a_{i-2}|)$$

然后答案即为 $f_n$。

## AC CODE:
```
#include<bits/stdc++.h>
using namespace std;

int a[114514],dp[114514];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	for(int i = 1 ; i <= n ; i++)
	{
		cin >> a[i];
	}
	dp[1]=0;
	dp[2]=abs(a[1]-a[2]);
	for(int i = 3 ; i <= n ; i++)
	{
		dp[i]=min(dp[i-1]+abs(a[i]-a[i-1]),dp[i-2]+abs(a[i]-a[i-2]));

	}
	cout << dp[n];
	return 0;
}

```
有问题私我。

---

## 作者：panyanppyy (赞：1)

[传送门](https://www.luogu.com.cn/problem/AT1932)

难度建议在 $\textcolor{orange}{pj-}$ 左右

这是一道 $dp$ 入门题吧，从题面中仔细观察就会发现“转移” 这个词出现频率极其之高，状态转移也十分~~明显~~吧。

## 解析
第 $i$ 根柱子可以由第 $i-1$ 与 $i-2$ 根柱子转移而来，代价是两根柱子的高度差(不要忘记绝对值)。

理清题目，转移方程就很好写了：

$f_i=max(f_{i-1}+|a_i-a_{i-1}|,f_{i-2}+|a_i-a_{i-2}|)$

那么问题就出现了，边界条件怎么处理呢？试想一下 $f_1$ 的情况，在这之前显然没有柱子了，那么 $f_1\gets 0$。

但这还没有结束。$f_2$ 是由 $f_1$ 和 $f_0$ 转移而来的。可是 $f_0$ 是未定义！那么 $f_2$ 只能由 $f_1$ 转移而来：

$f_2\gets f_1+|a_1-a_2|\Rightarrow f_2\gets|a_1-a_2|$。

输出 $f_n$ 的值就行了。

最后就是令人愉快的代码环节。

[Code](https://www.luogu.com.cn/paste/8aza79kr)

---

## 作者：sandwich (赞：1)

咳咳咳咳

作为第一个通过的人~~交了三遍才通过QWQ~~

一开始，我竟然以为这题是记忆化搜索……

其实，这是一道非常简单的动规问题

由题可知，从1~n的路有很多（具体可以了解一下走楼梯）
那么，每次只能走1或2根柱，由此，我们可以推出方程式

```cpp
ans1=dp[i-1]+abs(a[i]-a[i-1]);
ans2=dp[i-2]+abs(a[i]-a[i-2]);
```
那么，这其中最小的就是dp[i]的值，最后再输出dp[n]就完事啦！！！

代码
```
#include<bits/stdc++.h>
using namespace std;
long long n,i,j,k,a[100001],dp[100001];
int c[2]={1,2};
int main()
{
    cin>>n;
    for(i=1;i<=n;i++)
    cin>>a[i];
    dp[1]=0;
    dp[2]=abs(a[2]-a[1]);
    for(i=3;i<=n;i++)
    {
    	int ans1=dp[i-1]+abs(a[i]-a[i-1]);
    	int ans2=dp[i-2]+abs(a[i]-a[i-2]);
    	dp[i]=min(ans1,ans2);
	}
    cout<<dp[n];
    return 0;
}
```




---

## 作者：MrSWdAxiv (赞：0)

这是一道初级**动态规划**题。
## 思路
>
>第 $i$ 根柱子是由第 $i-1$ 和第 $i-2$ 根柱子决定的，可得：
>
>$$\textstyle f_i = min(f_{i-1} + \vert a_i - a_{i-1} \vert , f_{i-2} + \vert a_i - a_{i-2} \vert)$$
>
>当然，不要忘了将 $f_1$ 与 $f_2$ 初始化。
>
>$$\textstyle f_1=0$$
>
>$$\textstyle f_2=\vert a_1 - a_2 \vert$$
>
## 代码
>```cpp
>#include<bits/stdc++.h>
>using namespace std;
>int n,a[100005],f[100005];
>int main(){
>	ios::sync_with_stdio(false);
>	cin.tie(0);
>	cout.tie(0);
>	cin>>n;
>	for(int i=1;i<=n;i++){
>		cin>>a[i];
>	}
>	f[2]=abs(a[1]-a[2]);
>	for(int i=3;i<=n;i++){
>		f[i]=min(f[i-1]+abs(a[i]-a[i-1]),f[i-2]+abs(a[i]-a[i-2]));
>	}
>	cout<<f[n]<<'\n';
>	return 0;
>}
>
>```
#### 完结撒花！！！

---

## 作者：Tear_stains (赞：0)

题目说明第 $i$ 根柱子可以由第 $i-1$ 根柱子或第 $i-2$ 根柱子得到，代价是两根柱子的高度差的绝对值。

转移方程：

当前的代价可以由第 $i-1$ 的代价 $+$ 第 $i-1$ 个柱子与第 $i$ 根柱子的差或第 $i-2$ 的代价 $+$ 第 $i-2$ 个柱子与第 $i$ 根柱子的差。

由此得到转移方程：
```cpp
f[i] = min(f[i - 1] + abs(a[i] - a[i - 1]), f[i - 2] + abs(a[i] - a[i - 2]));
```

代码如下：
```cpp
#include<iostream>
#include<cmath>
using namespace std;
int n;
int a[100005];
int f[100005];
int main() {
	cin >> n;
	for(int i = 1;i <= n; ++i) {
		cin >> a[i];
	}
	f[1] = 0;
	f[2] = abs(a[1] - a[2]);
	for(int i = 3;i <= n; ++i) {
		f[i] = min(f[i - 1] + abs(a[i] - a[i - 1]), f[i - 2] + abs(a[i] - a[i - 2]));
	}
	cout << f[n] << endl;
	return 0;
}

```




---

