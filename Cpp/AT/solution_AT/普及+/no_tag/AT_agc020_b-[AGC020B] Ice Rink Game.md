# [AGC020B] Ice Rink Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc020/tasks/agc020_b

スケートリンクで、一人の大人の司会と $ N $ 人の子供がゲームを行います。 ゲームは $ K $ ラウンドからなり、ラウンド $ i $ では司会が次のように言います。

- $ A_i $ 人組を作って！

すると、まだ脱落していない子供たちは $ A_i $ 人からなるグループをできるだけ多く組みます。 一人につき一つのグループにしか入れません。 グループに入れなかった子供たちは脱落し、その他は次のラウンドに進みます。 ラウンドで誰も脱落しないこともありえます。

最後まで、つまりラウンド $ K $ のあとまで残ったのは $ 2 $ 人で、彼らが勝者となりました。

あなたは $ A_1 $, $ A_2 $, ..., $ A_K $ の値を聞き、$ N $ の値は知りませんが、推定してみたくなりました。

ゲームの開始前にいた子供たちの人数として考えられる最小の値と、最大の値を求めてください。もしくは、考えられる $ N $ の値は存在しないと判定してください。

## 说明/提示

### 制約

- $ 1\ \leq\ K\ \leq\ 10^5 $
- $ 2\ \leq\ A_i\ \leq\ 10^9 $
- 入力値はすべて整数である。

### Sample Explanation 1

例えば、ゲームの開始時に子供が $ 6 $ 人いた場合、以下のように進行します。 - ラウンド $ 1 $ では、$ 6 $ 人の子供たちが $ 3 $ 人組を $ 2 $ つ作り、誰も脱落しません。 - ラウンド $ 2 $ では、$ 6 $ 人の子供たちが $ 4 $ 人組を $ 1 $ つ作り、$ 2 $ 人が脱落します。 - ラウンド $ 3 $ では、$ 4 $ 人の子供たちが $ 3 $ 人組を $ 1 $ つ作り、$ 1 $ 人が脱落します。 - ラウンド $ 4 $ では、$ 3 $ 人の子供たちが $ 2 $ 人組を $ 1 $ つ作り、$ 1 $ 人が脱落します。 最後まで残った二人が勝者となります。

### Sample Explanation 2

このような状況はありえません。 特に、ゲームの開始時の子供たちの人数が $ 100 $ 人未満の場合は、ラウンド $ 3 $ で全員が脱落します。

## 样例 #1

### 输入

```
4
3 4 3 2```

### 输出

```
6 8```

## 样例 #2

### 输入

```
5
3 4 100 3 2```

### 输出

```
-1```

## 样例 #3

### 输入

```
10
2 2 2 2 2 2 2 2 2 2```

### 输出

```
2 3```

# 题解

## 作者：Dimly_dust (赞：3)

- 算法：**分治 $\&$ 递推**

- $L_i,R_i$表示第$i$轮过后的最小人数和最大人数。

- 令$X_i,Y_i$表示区间$[L_i,R_i]$中最小的$a_i$倍数和最大的$a_i$倍数。

所以得递推式如下：

$
\begin{cases} 
L_{i-1}=X_i\\
R_{i-1}=Y_i+a_i-1\\
X_i=\frac{L_i}{a_i}\\
Y_i=\frac{R_i}{a_i}\\
\end{cases}$

其中$X_i$为上取整，$Y_i$为下取整。

**最终答案为：$L_0,R_0$。**

所以可得代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long lef=2,rig=2;
int n,ans[100010];
int main()
{
	cin>>n;
	for(int i=1; i<=n; i++)
	{
		cin>>ans[i];
	}
	for(int i=n; i>=1; i--)
	{
		lef=((lef-1)/ans[i]+1)*ans[i];
		rig=rig/ans[i]*ans[i]+ans[i]-1;
	}
	if(lef>rig)cout<<-1;
	else cout<<lef<<" "<<rig;
	return 0;
}
```


---

## 作者：Ender_NaCl (赞：2)

一道简单的递推，标的绿题，大概只有橙或黄（虽然有些细节卡了我好几次）。

已知最后还剩 $2$ 人，求初始人数，考虑逆向推。

由于最终的答案是一个 $[l,r]$ 区间，所以可以考虑**求出经过每个 $a_i$ 前能取到的人数的区间 $[l,r]$，进行递推**。

于是就抽离出了一个小的问题，**已知经过 $a_i$ 后能取到的人数区间为 $[L,R]$，求经过 $a_i$ 前能取到的人数区间 $[l,r]$**。

稍微思考一下，不难想出， $l = a_i \times p$ 以及 $r = a_i \times (q + 1) - 1$ 

![](https://cdn.luogu.com.cn/upload/image_hosting/cdbkych2.png)

考虑几种无解情况：

- $R < a_i$，这不用多说

- $[L,R]$ 被夹在 $a_i$ 的两个倍数之间，暂且叫它特殊情况吧，待会特判一下

除去这两种，容易算出：

$p = \left\lceil\dfrac{L}{a_i}\right\rceil$

$q = \left\lfloor\dfrac{R}{a_i}\right\rfloor$

- 对于特殊情况，根据上式算出 $p$，$q$ 后必有 $p > q$，舍去即可

上代码

```cpp
#include <iostream>

using namespace std;

const int N = 100010;     
long long a[N],l[N],r[N];

int main()
{
	int n,i;
	cin>>n;
	for(i = n;i >= 1;i--) cin>>a[i]; //逆向存储方便递推 
	l[0] = r[0] = 2;
	for(i = 1;i <= n;i++)
	{
		if(r[i - 1] < a[i]) break;
		long long p = l[i - 1] / a[i] + (l[i - 1] % a[i] != 0?1:0),q = r[i - 1] / a[i];
		if(p > q) break;
		l[i] = p * a[i];
		r[i] = (q + 1) * a[i] - 1;
	}
	if(l[n] == 0) cout<<-1;
	else cout<<l[n]<<' '<<r[n];
	return 0;
}
```


---

## 作者：_zhx (赞：0)

# AT_agc020_b [AGC020B] Ice Rink Game 题解

## 题目大意

$n$ 个人进行游戏，每轮只保留最大的 $a[i]$ 倍数的人，最后一轮过后剩余 $2$ 人，输出最小的 $l_i$ 和最大的 $r_i$，或输出 $-1$。

### 题目思路

我们分别用 $l_i$ 和 $r_i$ 表示 $i$ 轮后的最大人数。

设 $x_i$ 和 $y_i$ 为 $l_i\sim r_i$ 中最小的 $a[i]$ 的倍数和最大的 $a[i]$ 的倍数。

得出以下式子：

$l_{i-1}=\left\lceil\ x_i \right\rceil$；

$r_{i-1}=\left\lfloor\ y_i+a_i-1 \right\rfloor$；

$\left\lceil\ x_i \right\rceil=l_i \div a_i$；

$\left\lfloor\ y_i \right\rfloor=r_i \div a_i$；

最后，答案是 $l_0$ 和 $r_0$。

所以，我们**不需要用数组**。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
long long n,a[N],l=2,r=2;
int main()
{
	cin>>n;
	for(int i=n;i>=1;i--) cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		l=((l-1)/a[i]+1)*a[i];
		r=r/a[i]*a[i]+a[i]-1;
	}
	if(l>r) cout<<"-1\n",exit(0);
	cout<<l<<' '<<r;
	return 0;
}

```


---

