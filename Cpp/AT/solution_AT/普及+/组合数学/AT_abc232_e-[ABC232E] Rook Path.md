# [ABC232E] Rook Path

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc232/tasks/abc232_e

縦 $ H $ 行、横 $ W $ 行の $ H\ \times\ W $ マスからなるグリッドがあります。上から $ i $ 行目、左から $ j $ 列目のマスを $ (i,\ j) $ と表します。

はじめ、マス $ (x_1,\ y_1) $ にルークが置かれており、高橋君は以下の操作を $ K $ 回行います。

- 現在ルークが置かれているマスと行または列が同じマスにルークを移動させる。ただし、現在ルークが置かれているマスとは異なるマスに移動させる必要がある。

$ K $ 回の操作の後、ルークがマス $ (x_2,\ y_2) $ に置かれているようにする方法は何通りありますか？答えは非常に大きくなることがあるので、$ 998244353 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ H,\ W\ \leq\ 10^9 $
- $ 1\ \leq\ K\ \leq\ 10^6 $
- $ 1\ \leq\ x_1,\ x_2\ \leq\ H $
- $ 1\ \leq\ y_1,\ y_2\ \leq\ W $

### Sample Explanation 1

以下の $ 2 $ 通りです。 - $ 1 $ 回目の操作でルークをマス $ (1,\ 2) $ からマス $ (1,\ 1) $ へ動かし、$ 2 $ 回目の操作でルークをマス $ (1,\ 1) $ からマス $ (2,\ 1) $ に動かす。 - $ 1 $ 回目の操作でルークをマス $ (1,\ 2) $ からマス $ (2,\ 2) $ へ動かし、$ 2 $ 回目の操作でルークをマス $ (2,\ 2) $ からマス $ (2,\ 1) $ に動かす。

### Sample Explanation 2

$ 998244353 $ で割った余りを求めなければならないことに注意して下さい。

## 样例 #1

### 输入

```
2 2 2
1 2 2 1```

### 输出

```
2```

## 样例 #2

### 输入

```
1000000000 1000000000 1000000
1000000000 1000000000 1000000000 1000000000```

### 输出

```
24922282```

## 样例 #3

### 输入

```
3 3 3
1 3 3 3```

### 输出

```
9```

# 题解

## 作者：沉石鱼惊旋 (赞：9)

### 题目翻译

有一个 $H\times W$ 的国际象棋棋盘，求一个**车**从 $(x_1,y_1)$ 走到 $(x_2,y_2)$ 正好用 $K$ 步的方案数。

### 题目思路

首先看到题，很显然是动态规划。$f_{k,i,j}$ 表示走到 $(i,j)$ 正好 $k$ 步的方案。但时间复杂度过高，考虑进行优化。

我们可以不记录具体走到哪个点位，我们只需知道当前在不在起点即可。于是就有 $f_{k,0/1/2/3}$ 表示第 $k$ 步时，当前位置为 $(x_1,y_1),(x_1,非y_1),(非x_1,y_1),(非x_1,非y_1)$。

我们在运用一些排列组合的基本知识，便能得到以下转移方程：

$f_{k,0} = f_{k,1} \times (W-1) + f_{k,2} \times (H-1)$

$f_{k,1} = f_{k,1} \times (W-2) + f_{k,0} + f_{k,3} \times (H-1)$

$f_{k,2} = f_{k,2} \times (H-2) + f_{k,0} + f_{k,3} \times (W-1)$

$f_{k,3} = f_{k,3} \times (H+W-4) + f_{k,2} + f_{k,1}$


接着，我们再循环过程中是可以压掉第一维 $k$ 的，那么我们只需记录 $4$ 个变量即可。

### 完整代码

远古时期代码，码风有点不好请见谅。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define p 998244353
using namespace std;
long long a,b,c,d;
int main()
{
	ll h,w,k,xx1,xx2,yy1,yy2;
	cin>>h>>w>>k>>xx1>>yy1>>xx2>>yy2;
	a=1;
	for(int i=0;i<k;i++)
	{
		ll a1,b1,c1,d1;
		a1=b*(w-1)+c*(h-1);
		b1=b*(w-2)+a+d*(h-1);
		c1=c*(h-2)+a+d*(w-1);
		d1=d*(h+w-4)+b+c;
		a1%=p;
		b1%=p;
		c1%=p;
		d1%=p;
		a=a1;
		b=b1;
		c=c1;
		d=d1;
	}
	if(xx2==xx1&&yy2==yy1)cout<<a%p;
	else if(xx2==xx1)cout<<b%p;
	else if(yy2==yy1)cout<<c%p;
	else cout<<d%p;
	return 0;
}
```



---

## 作者：guanyf (赞：7)

### 题意简述
- 给定一个 $H \times W$ 的棋盘，一个车在位置 $(x_1,y_1)$，每次它可以移动到同行的一个位置或同列的一个位置，不能移动到它原来的位置。求正好移动 $K$ 步到 $(x_2,y_2)$ 的方案数。

- $2 \le H,W \le 10^9$，答案对 $998244353$ 取模。

### 导入
由于这道题转移比较复杂，因此考虑先用动态规划来做。设状态为 $\{i,j,k\}$，表示车移动到 $(i,j)$ 用了 $k$ 步的方案数，因此转移就是：

$$dp_{i,j,k} = \sum_{x=1 \ x \not=j}^{W}dp_{i,x,k-1}+\sum_{y=1 \  y \not=i}^{H}dp_{y,j,k-1}$$

转移表示**同行**与**同列**转移过来但位置不同，初始状态 $dp_{x_1,y_1,0}=1$，最终状态是 $dp_{x_2,y_2,k}$。

[代码](https://www.luogu.com.cn/paste/ub6iltmj)

由于时空复杂度非常高，因此根本不可能过此题，接着就要优化了。

### 分析 / 思路
依然是动态规划，不过需要优化状态与转移。

```
1  | .     #     .     .
   |
2  | *     N     *     *
   |
3  | .     #     .     .
   |
4  |_._____#_____._____.___ 

     4     3     2     1
```

首先考虑状态。上图把棋盘分成了四部分，位于 `#` 和 `*` 的部分只需要一步就可以转移到 `N`，而 `.` 则需要两步。实际上在转移过程中单个符号的值与变化是一样的，因此我们只需要将状态分成四份就行了。分别是 $dp_{i,0 \sim 3}$。因为题目最终答案是在位置 $(x_2,y_2)$，因此我们只需要关注这个位置就行了。

在这里，它们分别表示：

1. 终点

2. 终点同行不同列的点

3. 终点同列不同行的点

4. 终点不同列不同行的点


接着考虑优化转移。对于每个状态来说，我们只需要运用排列组合的思想转移就行了（具体操作看状态转移方程）。

$$(1 \le i \le k)$$
$$dp_{i,0} = dp_{i-1,1}+dp_{i-1,2}$$
$$dp_{i,1} = dp_{i-1,0} \times (W-1) + dp_{i-1,1} \times (W-2) + dp_{i-1,3}$$
$$dp_{i,2} = dp_{i-1,0} \times (H-1) + dp_{i-1,2} \times (H-2) + dp_{i,3}$$
$$dp_{i,3} = dp_{i-1,1} \times (H-1) + dp_{i-1,2} \times (W-1) + dp_{i-1,3} \times (H+W-4)$$

对于每个状态看来说，都要记得取模。初始状态就是 $(x_1,y_1)$ 所在的区域为 $1$，最终状态就是 $a$。

时间复杂度：$\operatorname{O}(K)$。

#### 代码

```cpp
#include <iostream>
#define int long long
#define debug(a) cout << #a << ' ' << a << '\n'
using namespace std;
const int mod = 998244353, MAXN = 1e6 + 5;
int n, m, k, x1, y1, x2, y2, dp[MAXN][4]; 
signed main() {
  ios::sync_with_stdio(0);
  cin >> n >> m >> k >> x1 >> y1 >> x2 >> y2;
  (x1 == x2 && y1 == y2) && (dp[0][0] = 1);
  (x1 == x2 && y1 != y2) && (dp[0][1] = 1);
  (x1 != x2 && y1 == y2) && (dp[0][2] = 1);
  (x1 != x2 && y1 != y2) && (dp[0][3] = 1); //以上为初始状态
  for (int i = 1; i <= k; i++) { 
    dp[i][0] = (dp[i - 1][1] + dp[i - 1][2]) % mod;
    dp[i][1] = (dp[i - 1][0] * (m - 1) % mod + dp[i - 1][1] * (m - 2) % mod + dp[i - 1][3]) % mod;
    dp[i][2] = (dp[i - 1][0] * (n - 1) % mod + dp[i - 1][2] * (n - 2) % mod + dp[i - 1][3]) % mod;
    dp[i][3] = (dp[i - 1][1] * (n - 1) % mod + dp[i - 1][2] * (m - 1) % mod + dp[i - 1][3] * (n - 2 + m - 2) % mod) % mod; //转移
  }
  cout << dp[k][0];
  return 0;
}
```

---

## 作者：chengning0909 (赞：3)

# abc 232 e

## 题意

有一个 $n \times m$ 的矩阵，一开始有个物品放在 $(x_1, y_1)$ 上。

有 $k$ 次操作，每次操作可以将这个物品移动到同一行或者同一列的另一个格子上。

请你求出在 $k$ 次操作后，使得这个物品到达 $(x_2, y_2)$ 的方法有多少种，对 `998244353` 取模。

## 思路

首先，这道题我们先考虑暴力。

$dp_{x, y, k}$ 表示走 $k$ 步到格子 $(x, y)$ 的方案数。

那么就有转移：
$$dp_{x, y, k} = \sum _ {x' = x, y' \ne y} dp_{x', y', k - 1} + \sum _ {x' \ne x, y' = y} dp_{x', y', k - 1}$$

所以，状态总数为 $n \times m \times k$，每次有 $n + m$ 种转移，总时间复杂度为 $O(n \times m \times k \times (n + m))$，也就是 $10 ^ {33}$，很明显会超时。

通过打表输出 `dp` 数组，我们可以发现，整个矩阵最后的结果一共可以分为四种：

1. 起点

2. 和起点同行的点

3. 和起点同列的点

4. 和起点不同行也不同列的点

所以，$dp_{k, 0}$ 表示用 $k$ 步走到起点的方案数，$dp_{k, 1}$ 表示用 $k$ 步走到与起点同行的其他的点的方案数，$dp_{k, 2}$ 表示用 $k$ 步走到与起点同列的其他的点的方案数，$dp_{k, 3}$ 表述用 $k$ 步走到和起点不同行也不同列的点的方案数。

那么，转移是什么呢？

我们可以画一个图来看一看。

![](https://cdn.luogu.com.cn/upload/image_hosting/94rfmk0o.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/vqkey8lu.png)

$$dp_{k, 0} = dp_{k - 1, 1} \times (m - 1) + dp_{k - 1, 2} \times (n - 1)$$

![](https://cdn.luogu.com.cn/upload/image_hosting/trft6zgp.png)

$$dp_{k, 1} = dp_{k - 1, 0} + dp_{k - 1, 1} \times (m - 2) + dp_{k - 1, 3} \times (n - 1)$$

![](https://cdn.luogu.com.cn/upload/image_hosting/70n0bo3l.png)

$$dp_{k, 2} = dp_{k - 1, 0} + dp_{k - 1, 2} \times (n - 2) + dp_{k - 1, 3} \times (m - 1)$$

![](https://cdn.luogu.com.cn/upload/image_hosting/59kwedyp.png)

$$dp_{k, 3} = dp_{k - 1, 1} + dp_{k - 1, 2} + dp_{k - 1, 3} \times (n + m - 4)$$

所以，时间复杂度为 $O(k)$。

---

## 作者：wangyinghao (赞：2)

首先考虑暴力解法。

定义 $dp_{i,j,k}$ 为这个车在第 $k$ 步走到 $(i,j)$ 的方案数，那么有转移方程：

$$dp_{i,j,k}=\sum_{l=1,l\ne i}^{H} dp_{l,j,k-1} + \sum_{l=1,l\ne j}^{W} dp_{i,l,k-1}$$

我们把暴力的代码打出来，输出整个 $dp$ 数组，这里太懒没有取模：

```cpp
#include<iostream>
using namespace std;
int dp[50][50][50];

int main(){
	int h,w,k,x1,y1,x2,y2;
	cin>>h>>w>>k>>x1>>y1>>x2>>y2;
	dp[0][x1][y1]=1;
	for(int i=1;i<=k;i++){//小细节，要先枚举k 
		for(int j=1;j<=h;j++){
			for(int k=1;k<=w;k++){
				for(int l=1;l<=h;l++){
					if(l!=j) dp[i][j][k]+=dp[i-1][l][k];
				}
				for(int l=1;l<=w;l++){
					if(l!=k) dp[i][j][k]+=dp[i-1][j][l];
				}
			}
		}
	}
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			cout<<dp[k][i][j]<<" ";
		}
		cout<<'\n';
	}
	return 0;
}
```

随便构造一组样例输出结果：

![](https://cdn.luogu.com.cn/upload/image_hosting/axpri398.png)

你发现了什么？



| $D$ | $C$ | $D$ | $D$ |
|:-:|:-:|:-:|:-:|
| $B$ | $A$ | $B$ | $B$ |
| $D$ | $C$ | $D$ | $D$ |

这里假设 $(x1,y1)$ 为 $A$ 的坐标。大胆猜想一下，不管 $k$ 怎么变化，图表中有同一个字母的格子里的数永远相同。

接下来试图证明。$k=1$ 时，$dp$ 数组如表格所示：

| $0$ | $1$ | $0$ | $0$ |
|:-:|:-:|:-:|:-:|
| $1$ | $0$ | $1$ | $1$ |
| $0$ | $1$ | $0$ | $0$ |

此时上面总结的规律成立。接下来把目光放回暴力推出的转移方程，定义 $dp_{i,1}$ 为第 $i$ 步时 $A$ 格子的值，$dp_{i,2}$ 为 $B$ 格子的值，以此类推。

那么 $dp_{2,1}=(W-1)\times dp_{1,2}+(H-1)\times dp_{1,3}$

$dp_{2,2}=(H-1)\times dp_{1,4}+(W-1)\times dp_{1,2}+dp_{1,1}$

$dp_{2,3}=(W-1)\times dp_{1,4}+(H-1)\times dp_{1,3}+dp_{1,1}$

$dp_{2,4}=dp_{1,2}+dp_{1,3}+(H+W-4)\times dp_{1,4}$

因为 $k=1$ 时每个字母对应的格子数值一样，所以 $k=2$ 时每个字母对应的格子数值也一样，$k=3$ 也是，以此类推。所以上面的猜想成立。

那么就可以推出转移方程了：

$dp_{i,1}=(W-1)\times dp_{i-1,2}+(H-1)\times dp_{i-1,3}$

$dp_{i,2}=(H-1)\times dp_{i-1,4}+(W-1)\times dp_{i-1,2}+dp_{u-1,1}$

$dp_{i,3}=(W-1)\times dp_{i-1,4}+(H-1)\times dp_{i-1,3}+dp_{i-1,1}$

$dp_{i,4}=dp_{i-1,2}+dp_{i-1,3}+(H+W-4)\times dp_{i-1,4}$

时间复杂度 $O(K)$。

### AC Code

```cpp
#include<iostream>
using namespace std;
#define int long long
int dp[1000005][6];
const int INF=998244353;

signed main(){
	int h,w,k,x1,x2,y1,y2;
	cin>>h>>w>>k>>x1>>y1>>x2>>y2;
	dp[0][1]=1;
	for(int i=1;i<=k;i++){
		dp[i][1]=dp[i-1][2]*(w-1)%INF+dp[i-1][3]*(h-1)%INF;
		dp[i][2]=dp[i-1][2]*(w-2)%INF+dp[i-1][1]%INF+dp[i-1][4]*(h-1)%INF;
		dp[i][3]=dp[i-1][1]%INF+dp[i-1][4]*(w-1)%INF+dp[i-1][3]*(h-2)%INF;
		dp[i][4]=dp[i-1][2]%INF+dp[i-1][3]%INF+dp[i-1][4]*(h+w-4)%INF;
	}
	if(x1==x2 && y1==y2) cout<<dp[k][1]%INF;
	else if(x2==x1) cout<<dp[k][2]%INF;
	else if(y1==y2) cout<<dp[k][3]%INF;
	else cout<<dp[k][4]%INF;
	return 0;
}

```

---

## 作者：Laoshan_PLUS (赞：1)

### 题意

给定一个 $H\times W$ 的国际象棋棋盘，求一个車从 $(x_1,y_1)$ 走到 $(x_2,y_2)$ 用 $K$ 步的方案数。答案对 $998244353$ 取模。

### 解析

最简单的思路当然是设 $\textit{dp}(i,j,k)$ 表示走 $k$ 步到 $(i,j)$ 的方案数，但考虑到 $H,W\le 10^9$ 恐怖如斯，遂不得不放弃。

我们不得不考虑新的转移。

------------

$$
\begin{bmatrix}
\texttt.&\texttt\#&\texttt.&\texttt. \\
\texttt.&\texttt\#&\texttt.&\texttt. \\
\texttt*&\mathbf{\text車}&\texttt*&\texttt* \\
\texttt.&\texttt\#&\texttt.&\texttt.
\end{bmatrix}
$$

考虑如图棋盘。对于位于 $\texttt\#$ 和 $\texttt*$ 的部分，車都可以一步到达；而对于位于 $\texttt.$ 的部分则需要两步。我们不需要记录当前在哪个点位，只需记录在终点的何处位置、走了多少步即可。于是设 $\textit{dp}(k,0/1/2/3)$ 表示走 $k$ 步，分别在终点、终点同行、终点同列、终点不同行不同列的步数。则有状态转移方程：
$$
\begin{aligned}
\textit{dp}(k,0)&=\textit{dp}(k-1,1)+\textit{dp}(k-1,2) \\
\textit{dp}(k,1)&=\textit{dp}(k-1,0)\times(W-1)+\textit{dp}(k-1,1)\times(W-2)+\textit{dp}(k-1,3) \\
\textit{dp}(k,2)&=\textit{dp}(k-1,0)\times(H-1)+\textit{dp}(k-1,2)\times(H-2)+\textit{dp}(k-1,3) \\
\textit{dp}(k,3)&=\textit{dp}(k-1,1)\times(H-1)+\textit{dp}(k-1,2)\times(W-1)+\textit{dp}(k-1,3)\times(H+W-4)
\end{aligned}
$$

答案即为 $\textit{dp}(k,0)$，时间复杂度 $O(K)$。

### 实现

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

constexpr int MAXN = 1e6 + 5, MOD = 998244353;
int h, w, k, x1, Y1, x2, y2; // y1不能用
int dp[MAXN][4];

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin >> h >> w >> k >> x1 >> Y1 >> x2 >> y2;
	if (x1 == x2 && Y1 == y2) dp[0][0] = 1;
	if (x1 == x2 && Y1 != y2) dp[0][1] = 1;
	if (x1 != x2 && Y1 == y2) dp[0][2] = 1;
	if (x1 != x2 && Y1 != y2) dp[0][3] = 1;
	for (int i = 1; i <= k; i++) {
		dp[i][0] = (dp[i - 1][1] + dp[i - 1][2]) % MOD;
		dp[i][1] = ((dp[i - 1][3] + dp[i - 1][1] * (w - 2) % MOD) % MOD + dp[i - 1][0] * (w - 1) % MOD) % MOD;
		dp[i][2] = ((dp[i - 1][3] + dp[i - 1][2] * (h - 2) % MOD) % MOD + dp[i - 1][0] * (h - 1) % MOD) % MOD;
		dp[i][3] = ((dp[i - 1][3] * (h + w - 4) % MOD + dp[i - 1][1] * (h - 1) % MOD) % MOD + dp[i - 1][2] * (w - 1) % MOD) % MOD;
	}
	cout << dp[k][0] << '\n';
	
	return 0;
}
```

---

## 作者：cloud2764scallop_eve (赞：1)

## 题意
在象棋棋盘上有一个车，它的位置是 $(x1,y1)$，求车从此处到达 $(x2,y2)$ 有多少种情况。

## 思路
明显的~~组合数学~~与 DP 题。

最最最先，一定要明确一个概念，车可以横向或竖向移动到当前列或行的任意一个（除去它本身现在的位置），但不可以斜着移动。  
![](https://cdn.luogu.com.cn/upload/image_hosting/qtu5rhz1.png)  
如图所示，$(x1,y1)$ 是车当前的位置，标注 $1$ 的位置是车可以一步到达的，而标注 $0$ 的位置则意味着不可以一步到达。

考虑暴力 DP。设 $dp_{x, y, k}$ 表示进行了 $k$ 次操作后车走到 $(x, y)$ 的方案数。  
状态转移方程为：  
$$dp_{x, y, k} = \sum_{1 \le i \le H,i \neq x} dp_{i, y, k - 1} + \sum_{1 \le i \le W,i \neq y} dp_{x, j, k - 1}$$

最终答案为 $dp_{x2, y2, k}$。

但这样高达 $O(kH^3)$ 的优秀时间复杂度，再水的数据都明显过不了。  
考虑优化。

我们可以设四个集合，分别表示：  
- $S_{0, 0}$ 表示与车同行同列（就是车的位置）的点的集合；
- $S_{0, 1}$ 表示与车同行不同列的点的集合；
- $S_{1, 0}$ 表示与车同列不同行的点的集合；
- $S_{1, 1}$ 表示与车不同行不同列的点的集合。

可以表示为：  
$S_{0, 0} = {(x, y) \mid x = x1, y = y1}$；  
$S_{0, 1} = {(x, y) \mid x = x1, y \neq y1}$；  
$S_{1, 0} = {(x, y) \mid x \neq x1, y = y1}$；  
$S_{1, 1} = {(x, y) \mid x \neq x1, y \ neq y1}$。  

观察四个集合，可以看出当 $a, b \in {0, 1}$ 且 $(x1, y1)(x2, y2) \in S_{a, b}$ 时，$dp_{x1, y1, k} = dp_{x2, y2, k}(0 \le k \le K)$。  
当 $k$ 相同时，同一个集合内的所有点的 $dp$ 值是相同的。

所以不妨设：  
$$f_{n, m, k}(n, m \in {0, 1}) = \sum_{(x, y) \in S_{a, b}} dp_{x, y, k}$$

那么 $f$ 的边界条件也就很好处理了。分别是：  
1. $f_{0, 0, 0} = 1$；
2. $f_{0, 1, 0} = 0$；
3. $f_{1, 0, 0} = 0$；
4. $f_{1, 1, 0} = 0$。

现在就可以推导转移方程了。方便起见，可以先分情况讨论：  
- $x1 = x2$ 且 $y1 = y2$：$ans = f_{0, 0, k}$；
- $x1 = x2$ 且 $y1 \neq y2$：$ans = \frac{f_{0, 1, K}}{W - 1}$；
- $x1 \neq x2$ 且 $y1 = y2$：$ans = \frac{f_{0, 1, K}}{H - 1}$；
- $x1 \neq x2$ 且 $y1 \neq y2$：$ans = \frac{f_{0, 1, K}}{(W - 1) \times (H - 1)}$。

那么转移方程就应为：  
- $f_{0, 0, k} = f_{0, 1, k - 1} + f_{1, 0, k - 1}$；
- $f_{0, 1, k} = (W - 1) \times f_{0, 0, k - 1} + (W - 2) \times f_{0, 1, k - 1} + f_{1, 1, k - 1}$；
- $f_{1, 0, k} = (H - 1) \times f_{0, 0, k - 1} + (H - 2) \times f_{1, 0, k - 1} + f_{1, 1, k - 1}$；
- $f_{1, 1, k} = (W - 1) \times f_{0, 1, k - 1} + (H - 1) \times f_{1, 0, k - 1} + (W + H - 4) \times f_{1, 1, k - 1}$。

得解。

## 代码
除法需要使用乘法逆元。

**所用的函数请务必使用 `long long`！**  
不然就会：[R.I.P](https://atcoder.jp/contests/abc232/submissions/48990002)。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 998244353, N = 1e7 + 5;
int n, m, k, x, y, xx, yy;
int ans;
int f[2][2][N];
int inv(int x) {
	return x == 1 ? 1 : (mod - mod / x) * inv(mod % x) % mod;
}
signed main() {
	scanf("%lld%lld%lld", &n, &m, &k);
	scanf("%lld%lld%lld%lld", &x, &y, &xx, &yy);
	f[0][0][0] = 1;
	for (int i = 1; i <= k; i++) {
		f[0][0][i] = (f[0][1][i - 1] + f[1][0][i - 1]) % mod;
		f[0][1][i] = ((m - 1) * f[0][0][i - 1] % mod + (m - 2) * f[0][1][i - 1] % mod + f[1][1][i - 1] % mod + mod) % mod;
		f[1][0][i] = ((n - 1) * f[0][0][i - 1] % mod + (n - 2) * f[1][0][i - 1] % mod + f[1][1][i - 1] % mod + mod) % mod;
		f[1][1][i] = ((n - 1) * f[0][1][i - 1] % mod + (m - 1) * f[1][0][i - 1] % mod + (n + m - 4) * f[1][1][i - 1] % mod + mod) % mod;
	}
	if (x == xx && y == yy) ans = f[0][0][k];
	else if (x == xx && y != yy) ans = f[0][1][k] * inv(m - 1) % mod;
	else if (x != xx && y == yy) ans = f[1][0][k] * inv(n - 1) % mod;
	else ans = f[1][1][k] * inv((n - 1) * (m - 1) % mod) % mod;
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Tachibana27 (赞：1)

很好的计数！

---

容易发现是个计数问题，直接组合计数发现糊不出来，所以用 dp 解决。

考虑设计很裸的暴力状态：$f_{i,j,k}$ 表示走到 $(i,j)$ 用了 $k$ 步。容易发现复杂度无法接受，考虑优化。

容易发现具体在哪个位置我们其实是**不关心的**。我们只要知道当前状态是否在终点的 $x$ 轴或 $y$ 轴上就好了。优化状态：

$dp_{i,j}$ 表示到第 $i$ 步时，与终点的关系为 $j$ 的方案数。

考虑以下 $j$ 的取值：

- $j=0$，当前状态位置为**终点**。
- $j=1$，当前状态位置与**终点**有且仅有 $x$ 轴相同。
- $j=2$，当前状态位置与**终点**有且仅有 $y$ 轴相同。
- $j=3$，当前状态位置均不在**终点**的 $x,y$ 轴上。

运用很基础的计数原理，可以推出转移：

- 当 $j=0$ 时，转移为： $dp_{i-1,1}+dp_{i-1,2}$。
- 当 $j=1$ 时，转移为： $dp_{i-1,0}\times (m-1)+dp_{i-1,1}\times (m-2)+dp_{i-1,3}$。
- 当 $j=2$ 时，转移为： $dp_{i-1,0}\times(n-1)+dp_{i-1,2}\times(n-2)+dp_{i-1,3}$。
- 当 $j=3$ 时，转移为： $dp_{i-1,1}\times(n-1)+dp_{i-1,2}\times(m-1)+dp_{i-1,3}\times(n-2+m-2)$。

最后答案在 $dp_{k,0}$ 中。

容易发现每次只需要上一步的答案，所以可以把它滚动掉。但是我懒，所以我懒得写。

初始状态由状态设计可简单推出，参考代码：

```cpp

int n,m,k;
std::pair<int,int>x,y;
int dp[1000086][5];
signed main(){
	std::cin>>n>>m>>k;
	std::cin>>x.first>>x.second>>y.first>>y.second;
	dp[0][0]=(x.first==y.first and x.second==y.second?1:0);
	dp[0][1]=(x.first==y.first and x.second-y.second?1:0);
	dp[0][2]=(x.first-y.first and x.second==y.second?1:0);
	dp[0][3]=(x.first-y.first and x.second-y.second?1:0);//初始状态
	for(int i=1;i<=k;i++){ 
	    dp[i][0]=(dp[i-1][1]+dp[i-1][2])%mod;
	    dp[i][1]=(dp[i-1][0]*(m-1)%mod+dp[i-1][1]*(m-2)%mod+dp[i-1][3])% mod;
	    dp[i][2]=(dp[i-1][0]*(n-1)%mod+dp[i-1][2]*(n-2)%mod+dp[i-1][3])% mod;
	    dp[i][3]=(dp[i-1][1]*(n-1)%mod+dp[i-1][2]*(m-1)%mod+dp[i-1][3]*(n+m-4)%mod)%mod;//转移
	}
	std::cout<<dp[k][0];
	return 0;//撒花
}
```

显然的，本题不开 long long 见祖宗。

---

## 作者：_maple_leaf_ (赞：0)

## [或许更好的阅读体验](https://www.cnblogs.com/Red-maple/articles/18564322)
## 题意
已经够清晰了。
## 思路
由于直接转移复杂度太高，考虑另类转移。

设 $f_{i,j}$ 表示移动了 $i$ 步之后，状态为 $j$：
- 当 $j$ 为 $0$ 时，表示在原点上；
- 当 $j$ 为 $1$ 时，表示在原点那一行上，但不在原点上；
- 当 $j$ 为 $2$ 时，表示在原点那一列上，但不在原点上；
- 当 $j$ 为 $3$ 时，表示既不在原点那一行上，也不在原点那一行上。

于是得到转移：
- $f{i,0}=f_{i-1,1}\times (W-1)+f_{i-1,2}\times (H-1)$；
- $f{i,1}=f{i,0}+f_{i-1,1}\times (W-2)+f_{i-1,3}\times (H-1)$；
- $f{i,2}=f{i,0}+f_{i-1,2}\times (W-2)+f_{i-1,3}\times (H-1)$；
- $f{i,3}=f_{i-1,1}+f_{i-1,2}+f_{i-1,3}\times(W+H)$；

可以发现第一维是可以压掉的，我就用临时变量代替了。

## code
```c++
//By _maple_leaf_
#include<bits/stdc++.h>
#define FAST true
#define FIO true
#define DEBUG true
using namespace std;
#if FIO
void fio(string s,int i=0){
	freopen(((s+(i?to_string(i):""))+".in").c_str(),"r",stdin);
	freopen(((s+(i?to_string(i):""))+".out").c_str(),"w",stdout);
}
#endif
#define int long long
#define _27 998244353
//#define int unsigned int
//#define int __int128
#if DEBUG
bool Memory_start;
void debug();
#endif
#if FAST
inline int read(){
	char c=getchar();
	int ret=0,f=1;
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		ret=(ret<<3)+(ret<<1)+c-'0';
		c=getchar();
	}return ret*f;
}
inline void write(int x,int op=0){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10,0);
	putchar((char)(x%10+'0'));
	if(op){
		if(op>0)puts("");
		if(op<0)putchar(' ');
		if(op==0)puts("114514");
	}
}
#endif
int h,w,k;
int x,y,X,Y;
int Ta,chi,ba,na;
signed main(){
	h=read(),w=read(),k=read(),x=read(),y=read(),X=read(),Y=read();
	Ta=1;
	for(int i=1;i<=k;i++){
		int ta,tb,tc,td;
		(ta=chi*(w-1)+ba*(h-1))%=_27;
		(tb=Ta+chi*(w-2)+na*(h-1))%=_27;
		(tc=Ta+ba*(h-2)+na*(w-1))%=_27;
		(td=chi+ba+na*(w+h-4))%=_27;
		Ta=ta,chi=tb,ba=tc,na=td;
	}
	if(x==X&&y==Y)write(Ta);
	else if(x==X&&y!=Y)write(chi);
	else if(x!=X&&y==Y)write(ba);
	else write(na);
#if DEBUG
	debug();
#endif
	return 0;
}//~*完结撒花*~
#if DEBUG
bool Memory_end;
void debug(){
	cerr<<"Time: "<<clock()<<" ms\n";
	cerr<<fixed<<setprecision(6)<<"Memory: "<<abs(&Memory_start-&Memory_end)/1024.0/1024.0<<" MB";
}
#endif
```

---

## 作者：Zhao_daodao (赞：0)

# solution
一个 **车** 从 $(x_1,y_1)$ 走向 $(x_2,y_2)$，问恰好走 $k$ 次的方案数。

**车** 可以走到当前行和当前列的任意一个点，但不能保持不动。
## first step
发现从一个点发散不好考虑，考虑一个点此时的方案数。

因为每一个点可能从这一整行和这一整列到达，所以只用统计行和列的数据即可。

再结合 $k\le 10^6$，可以得出一种 $O(k)$ 的迭代做法。

~~通过打表可得~~，这一题只用记录：
1. 原点
2. 原点的横边
3. 原点的竖边
4. 其他店

的信息。

## second step

记录 $yuan$，$x$，$y$，$other$ 四个变量。

$yuan$ 表示 $(x_1,y_1)$ 的方案数。

$x$ 表示 $(p,y_1)$ 的方案数。其中 $p\in[1,n],p\ne x_1$。

$y$ 表示 $(x_1,p)$ 的方案数。其中 $p\in[1,m],p\ne y_1$。 

$other$ 表示其他点的方案数。

对于每一个 $i\in[1,k]$：

$yuan:=(n-1)\times x+(m-1)\times y$。

$x:=yuan+(n-2)\times x+(m-1)\times other$。

$y:=yuan+(m-2)\times y+(n-1)\times other$。

$other:=(n-2+m-2)\times other +x+y$。

只需要这样迭代 $k$ 次就可以了。
### 初值
$yuan=1$，其他的都是 $0$。
### 最后判断
如果 $x_1=x_2$ 且 $y_1=y_2$，输出 $yuan$。

如果 $x_1\ne x_2$ 且 $y_1=y_2$，输出 $x$。

如果 $x_1=x_2$ 且 $y_1\ne y_2$，输出 $y$。

如果 $x_1\ne x_2$ 且 $y_1\ne y_2$，输出 $other$。
# code
```cpp
#include<bits/stdc++.h>
#define int long long
#define Pair pair<int,int>
#define mod 998244353
using namespace std;
int n,m,k;
Pair start,endd;
int yuan=1,x,y,other;
void read(){
    cin>>n>>m>>k;
    cin>>start.first>>start.second;
    cin>>endd.first>>endd.second;
}
signed main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    read();
    for(int i=1;i<=k;i++){
        int yuan1,x1,y1,other1;
        yuan1=(n-1)*x%mod+(m-1)*y%mod; yuan1%=mod;
        x1=yuan+(n-2)*x%mod+(m-1)*other%mod; x1%=mod;
        y1=yuan+(m-2)*y%mod+(n-1)*other%mod; y1%=mod;
        other1=(n+m-4)%mod*other%mod+x+y; other1%=mod;
        yuan=yuan1; x=x1; y=y1; other=other1;
    }
    if(start==endd)cout<<yuan<<"\n";
    else if(start.second==endd.second)cout<<x<<"\n";
    else if(start.first==endd.first)cout<<y<<"\n";
    else cout<<other<<"\n";
}
```

---

## 作者：CarroT5656 (赞：0)

**题目大意**

有一个 $H\times W$ 的棋盘。在 $(x_1,y_1)$ 处有一个棋子，每次可以横向或纵向走任意格。求走 $K$ 步后恰好到达 $(x_2,y_2)$ 的方案数。

**解法分析**

显然是动态规划。

考虑到不好每一个点都有一个状态，将状态设为：

* $dp_{i,0}$ 表示已经走了 $i$ 步，无法一步到达 $(x_2,y_2)$。

* $dp_{i,1}$ 表示已经走了 $i$ 步，可以一步到达 $(x_2,y_2)$，与终点纵坐标相同。

* $dp_{i,2}$ 表示已经走了 $i$ 步，可以一步到达 $(x_2,y_2)$，与终点横坐标相同。

* $dp_{i,3}$ 表示已经走了 $i$ 步，已经到达 $(x_2,y_2)$。

接下来就可以转移。

* $dp_{i,0}=dp_{i-1,0}\times (H+W-4)+dp_{i-1,1}\times (W-1)+dp_{i-1,2}\times (H-1)$

* $dp_{i,1}=dp_{i-1,0}+dp_{i-1,1}\times(H-2)+dp_{i-1,3}\times (H-1)$

* $dp_{i,2}=dp_{i-1,0}+dp_{i-1,2}\times(W-2)+dp_{i-1,3}\times (W-1)$

* $dp_{i,3}=dp_{i-1,1}+dp_{i-1,2}$

可以画图理解一下转移方程。

根据 $(x_1,y_1)$ 与 $(x_2,y_2)$ 的位置设置 $dp_0$ 的初始值，转移即可。

时间复杂度 $O(4K)$，可以通过。

**Code**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long
#define mod 998244353
#define N 1000005
ll n,m,k,f[N][5],sx,sy,ex,ey;
int main(){
	scanf("%lld%lld%lld%lld%lld%lld%lld",&n,&m,&k,&sx,&sy,&ex,&ey);
	if(sx==ex&&sy==ey) f[0][4]=1;
	else if(sx==ex) f[0][3]=1;
	else if(sy==ey) f[0][2]=1;
	else f[0][1]=1;
	for(ll i=1;i<=k;i++){
		f[i][1]=(f[i-1][1]*(n+m-4)%mod+f[i-1][2]*(m-1)%mod+f[i-1][3]*(n-1)%mod)%mod;
		f[i][2]=(f[i-1][1]+f[i-1][4]*(n-1)+f[i-1][2]*(n-2))%mod;
		f[i][3]=(f[i-1][1]+f[i-1][4]*(m-1)+f[i-1][3]*(m-2))%mod;
		f[i][4]=(f[i-1][2]+f[i-1][3])%mod;
	}
	printf("%lld\n",f[k][4]%mod);
	return 0;
}
```

---

