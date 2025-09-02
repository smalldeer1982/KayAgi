# Knapsack 1

## 题目描述

[problemUrl]: https://atcoder.jp/contests/dp/tasks/dp_d

$ N $ 個の品物があります。 品物には $ 1,\ 2,\ \ldots,\ N $ と番号が振られています。 各 $ i $ ($ 1\ \leq\ i\ \leq\ N $) について、品物 $ i $ の重さは $ w_i $ で、価値は $ v_i $ です。

太郎君は、$ N $ 個の品物のうちいくつかを選び、ナップサックに入れて持ち帰ることにしました。 ナップサックの容量は $ W $ であり、持ち帰る品物の重さの総和は $ W $ 以下でなければなりません。

太郎君が持ち帰る品物の価値の総和の最大値を求めてください。

## 说明/提示

### 制約

- 入力はすべて整数である。
- $ 1\ \leq\ N\ \leq\ 100 $
- $ 1\ \leq\ W\ \leq\ 10^5 $
- $ 1\ \leq\ w_i\ \leq\ W $
- $ 1\ \leq\ v_i\ \leq\ 10^9 $

### Sample Explanation 1

品物 $ 1,\ 3 $ を選べばよいです。 すると、重さの総和は $ 3\ +\ 5\ =\ 8 $ となり、価値の総和は $ 30\ +\ 60\ =\ 90 $ となります。

### Sample Explanation 2

答えは 32-bit 整数型に収まらない場合があります。

### Sample Explanation 3

品物 $ 2,\ 4,\ 5 $ を選べばよいです。 すると、重さの総和は $ 5\ +\ 6\ +\ 3\ =\ 14 $ となり、価値の総和は $ 6\ +\ 6\ +\ 5\ =\ 17 $ となります。

## 样例 #1

### 输入

```
3 8
3 30
4 50
5 60```

### 输出

```
90```

## 样例 #2

### 输入

```
5 5
1 1000000000
1 1000000000
1 1000000000
1 1000000000
1 1000000000```

### 输出

```
5000000000```

## 样例 #3

### 输入

```
6 15
6 5
5 6
6 4
6 6
3 5
7 2```

### 输出

```
17```

# 题解

## 作者：Haphyxlos (赞：18)

# AT4525 【Knapsack 1】
[题目传送门](https://www.luogu.com.cn/problem/AT4525)

很显然，本题就是01背包的裸题，那么就直接上板子就ok了。

很显然， 我们可以得到二维背包的转移方程：$ f[i][j]=\max(f[i-1][j-w[i]]+v[i],f[i-1][j]) $

代码如下：
```cpp
for(int i=1;i<=n;++i){
	for(int j=1;j<=m;++j){
		if(j>=w[i])f[i][j]=max(f[i-1][j-w[i]]+v[i],f[i-1][j]);
		else f[i][j]=f[i-1][j];	
	}
}
```

接下来，我们考虑压缩掉一维，即将原本的$f[i][j]$更改为$f[j]$，我们只需要将第二层循环的的顺序稍作改变。

则原方程变为：$f[j]=\max(f[j-w[i]]+v[i],f[j])$


改变如下：
```cpp
for(int j=m;j>=w[i];--j)
```

解释如下：

之所以这么改变呢，是因为枚举到当前的$j$时，$j-w[i]$ 还没有被枚举到，这样就可以忽略掉原先的第一维。

本题完整AC代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
const double eps=1e7-8;
const int INF=0x3f3f3f3f;
const int maxn=1e5+5;
const int maxm=1e6+5;
ll n,m,f[maxn],w[maxn],v[maxn]; 
//本题有个值得注意的地方就是，本题可能会炸int，所以得开ll
int main(int argc, char const *argv[]){
	std::ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;++i)cin>>w[i]>>v[i];
	for(int i=1;i<=n;++i){
		for(int j=m;j>=w[i];--j){
			f[j]=max(f[j-w[i]]+v[i],f[j]);
		}
	}
	cout<<f[m];
	return 0;
}
```

本篇题解就到此结束了，如果喜欢，还请点个赞吧。

---

## 作者：Doqin07 (赞：3)

## 其实就是一道$01$背包的板子题
### 我们设$dp[i][j]$表示考虑了$i$个物品，背包容量为$j$的最大价值。所以在算时，只有两种情况需要考虑
#### - 选第$i$件物品，那么背包容量剩余$j-w_i$，$i-1$个物品，价值为$dp[i-1][j-w_i]+v_i$

#### - 不选第$i$件物品，那么背包容量仍然不变为$j$，这时价值为$dp[i-1][j]$
----

#### 所以可以得到$dp$的转移方程:
![](https://cdn.luogu.com.cn/upload/image_hosting/a4n9vjpy.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

-----
## ありがとうございます。

---

## 作者：chenxia25 (赞：2)

>### [洛谷题目页面传送门](https://www.luogu.com.cn/problem/AT4525) & [AtCoder题目页面传送门](https://atcoder.jp/contests/dp/tasks/dp_d)

>有$n$个物品，第$i$个物品重量为$w_i$，价值为$v_i$。要选若干个物品装进一个容量为$m$的背包，求在总重量不超过$m$的情况下，总价值的最大值。

>$n\in[1,100],m\in\left[1,10^5\right]$。

01背包模板题。

设$dp_{i,j}$表示考虑到第$i$个物品，在总容量不超过$j$的情况下，总价值的最大值。边界是$dp_{0,i}=0$，目标是$dp_{n,m}$，状态转移方程是$dp_{i,j}=\max\begin{cases}dp_{i-1,j}\\dp_{i-1,j-w_i}+v_i&j\geq w_i\end{cases}$（选或不选第$i$个物品）。时间复杂度$\mathrm O(nm)$。

有一种将数组压成一维的简便写法：当前考虑到第$i$个物品，$dp'_j$就表示$dp_{i,j}$。考虑更新方法。还没更新时，$dp'_j=dp_{i-1,j}$，正好是方程中的第$1$项。然后从大到小枚举$j\in[w_i,m]$（当$j<w_i$时第$2$项不能算），令$dp'_j=\max\!\left(dp'_j,dp'_{j-w_i}+v_i\right)$。因为是从大到小，所以枚举到$j$时$j-w_i$还没被枚举到，此时$dp'_{j-w_i}=dp_{i-1,j-w_i}$，与方程吻合。最终目标是$dp'_m$。

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=100,M=100000;
int n,m;
int v[N+1],w[N+1];
int dp[M+1];//dp' 
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>w[i]>>v[i];
	for(int i=1;i<=n;i++)for(int j=m;j>=w[i];j--)//转移 
		dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
	cout<<dp[m];//目标 
	return 0;
}
```

---

