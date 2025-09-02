# Gerrymandering

## 题目描述

我们都会偷一点点。但我只有一只手，而我的对手有两只。

Álvaro Obregón

Álvaro 和 José 是唯一竞选 Tepito 总统的候选人。Tepito 是一个 $2$ 行 $n$ 列的矩形网格，每个格子代表一座房子。保证 $n$ 是 $3$ 的倍数。

在 Tepito 的投票制度下，网格会被划分为若干个选区，每个选区由任意 $3$ 个连通的房子组成 $^{\text{∗}}$。每个房子恰好属于一个选区。

每个选区会投出一票。如果该选区中至少有 $2$ 个房子选择某位候选人，则该选区会投给这位候选人。因此，总共会投出 $\frac{2n}{3}$ 票。

作为现任总统，Álvaro 知道每个房子会选择哪位候选人。如果 ÁLvaro 最优地划分选区，请你求出他最多能获得多少票。

$^{\text{∗}}$ 一组格子是连通的，当且仅当任意两个格子之间存在一条路径，只经过该组格子，并且每一步只能上下左右移动。

## 说明/提示

下图展示了样例中每个测试用例的最优选区划分方式。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2022C/df820ffc2e1ad6e016254b57c0ce9fb7f735735d.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
3
AAA
AJJ
6
JAJAJJ
JJAJAJ
6
AJJJAJ
AJJAAA
9
AJJJJAJAJ
JAAJJJJJA```

### 输出

```
2
2
3
2```

# 题解

## 作者：Yorg (赞：10)

# 算法
题意是清楚的，我们注意到，类似于这种框图问题，考虑使用轮廓线 $\rm{dp}$ 。

首先要确定几种情况，观察样例就可以知道，分割完一个选区之后，只有这几种情况。

[![pA505aF.png](https://s21.ax1x.com/2024/11/29/pA505aF.png)](https://imgse.com/i/pA505aF)

所以我们记录 $s$ 表示当前决策点处轮廓线长什么样，$i$ 表示这是决策点是第几列，就有定义 $f_{i, s}$ ，其中
$$ 
s \in
\left\{
    \left [
    \begin{array}{}
    1 & 1 \\
    1 & 0 \\
    \end{array}
    \right ]

    ,

    \left [
    \begin{array}{}
    1 & 0 \\
    1 & 0 \\
    \end{array}
    \right ]

    ,

    \left [
    \begin{array}{}
    1 & 0 \\
    1 & 1 \\
    \end{array}
    \right ]

\right\}
$$

分别记为 $s_1, s_2, s_3$。

考虑 $\rm{dp}$ 方程。

首先是状态的变动, 我们分类讨论，

---
在上面加上三横排，\
同样的, 必须要在下面加。

$$
\left [
\begin{array}{}
1 & 1 \\
1 & 0 \\
\end{array}
\right ]

\Rightarrow

\left [
\begin{array}{}
1 & 1 \\
1 & 0 \\
\end{array}
\right ]
$$

$$
\left [
\begin{array}{}
1 & 0 \\
1 & 1 \\
\end{array}
\right ]

\Rightarrow

\left [
\begin{array}{}
1 & 0 \\
1 & 1 \\
\end{array}
\right ]
$$

$$
\left [
\begin{array}{}
1 & 0 \\
1 & 0 \\
\end{array}
\right ]

\Rightarrow

\left [
\begin{array}{}
1 & 0 \\
1 & 0 \\
\end{array}
\right ]
$$

其实就是保持不变，

有，
$$ f_{i, s} \gets f_{i - 3, s} $$

---

对于
$$
\left [
\begin{array}{}
1 & 0 \\
1 & 0 \\
\end{array}
\right ]

$$

可以加上一个
[![pA5BlMq.png](https://s21.ax1x.com/2024/11/29/pA5BlMq.png)](https://imgse.com/i/pA5BlMq)

变成这个

$$
\left [
\begin{array}{}
1 & 0 \\
1 & 1 \\
\end{array}
\right ]

$$

有 
$$f_{i, s_3} \gets f_{i - 1, s_2}$$

---

对于

$$
\left [
\begin{array}{}
1 & 0 \\
1 & 1 \\
\end{array}
\right ]

$$

可以加上一个

[![pA5BDL6.png](https://s21.ax1x.com/2024/11/29/pA5BDL6.png)](https://imgse.com/i/pA5BDL6)

变成

$$
\left [
\begin{array}{}
1 & 0 \\
1 & 0 \\
\end{array}
\right ]
$$

有

$$
f_{i, s_2} \gets f_{i - 2, s_3}
$$
---

对于

$$
\left [
\begin{array}{}
1 & 1 \\
1 & 0 \\
\end{array}
\right ]

$$

[![pA5BseK.png](https://s21.ax1x.com/2024/11/29/pA5BseK.png)](https://imgse.com/i/pA5BseK)

变成

$$
\left [
\begin{array}{}
1 & 0 \\
1 & 0 \\
\end{array}
\right ]
$$

有

$$
f_{i, s_2} \gets f_{i - 2, s_1}
$$

---

对于

$$
\left [
\begin{array}{}
1 & 0 \\
1 & 0 \\
\end{array}
\right ]

$$

[![pA5BqYQ.png](https://s21.ax1x.com/2024/11/29/pA5BqYQ.png)](https://imgse.com/i/pA5BqYQ)

变成

$$
\left [
\begin{array}{}
1 & 1 \\
1 & 0 \\
\end{array}
\right ]
$$

有

$$ f_{i, s_1} \gets f_{i - 1, s_2} $$

---

总结一下, 方程为：

($res$ 表示选区是否投票， $res \in \{0, 1\}$)

$$
\begin{cases}
\begin{aligned}
& dp_{i, 1 / 2 / 3} \gets dp_{i - 3, 1 / 2 / 3}  + res\\
& dp_{i, 2} \gets dp_{i - 2, 3} + res\\
& dp_{i, 3} \gets dp_{i - 1, 2}  + res\\
& dp_{i, 1} \gets dp_{i - 1, 2}  + res\\
& dp_{i, 2} \gets dp_{i - 2, 1}  + res\\
\end{aligned}
\end{cases}
$$

对每个 $dp_{i, 1 / 2 / 3}$ 取最大值即可，答案即为 $f_{n + 1, 2}$。

复杂度 $\mathcal{O}(n)$。

# 代码
[代码](https://www.luogu.com.cn/paste/2djndm9h)

---

## 作者：_O_v_O_ (赞：3)

我们设 $dp_{0\sim 8}$ 为最后四个块为下图状态（灰色代表已选，白色代表未被选）：

![](https://cdn.luogu.com.cn/upload/image_hosting/gomirg3g.png)

那么我们就直接分讨每种状态的拼合就行了，细节和转移方程见代码，注意代码中的状态与上面不太相同。


```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=1e5+5;
int n,a[N][2],dp[N][15];

int ss(int x,int b,int c){
	if(x==b) return x;
	if(x==c) return x;
	if(b==c) return b;
}

signed main(){
	ios::sync_with_stdio(0),cin.tie(0);
	int T;cin>>T;while(T--){
		cin>>n;
		for(int i=0;i<2;i++){
			for(int j=1;j<=n;j++){
				char c;cin>>c;
				if(c=='A') a[j][i]=1;
				else a[j][i]=0;
			}
		}
		for(int i=0;i<n+5;i++){
			for(int j=0;j<8;j++){
				dp[i][j]=0;
			}
		}
		for(int i=2;i<=n;i++){
			if(i%3==0){
				dp[i][0]=dp[i-1][4]+ss(a[i-1][1],a[i][0],a[i][1]);
				dp[i][0]=max(dp[i][0],dp[i-1][5]+ss(a[i-1][0],a[i][0],a[i][1]));
				dp[i][6]=dp[i-1][4];
				dp[i][7]=dp[i-1][5];
				if(i>2) dp[i][0]=max(dp[i][0],dp[i-1][8]+ss(a[i-2][0],a[i-1][0],a[i][0])+ss(a[i-2][1],a[i-1][1],a[i][1]));
			} 
			if(i%3==2){
				dp[i][4]=dp[i-1][1]+ss(a[i-1][0],a[i-1][1],a[i][0]);
				dp[i][5]=dp[i-1][1]+ss(a[i-1][0],a[i-1][1],a[i][1]);
				if(i>2) dp[i][4]=max(dp[i][4],dp[i-1][2]+ss(a[i-2][0],a[i-1][0],a[i][0]));
				if(i>2) dp[i][5]=max(dp[i][5],dp[i-1][3]+ss(a[i-2][1],a[i-1][1],a[i][1]));
				dp[i][8]=dp[i-1][1];
			}
			if(i%3==1){
				dp[i][1]=dp[i-1][0];
				if(i>2) dp[i][2]=max(dp[i][2],dp[i-1][6]+ss(a[i-2][1],a[i-1][1],a[i][1]));
				if(i>2) dp[i][3]=max(dp[i][3],dp[i-1][7]+ss(a[i-2][0],a[i-1][0],a[i][0]));
			}
		}
//		for(int i=0;i<n+5;i++){
//			for(int j=0;j<8;j++){
//				cout<<dp[i][j]<<' ';
//			}
//			cout<<endl;
//		}
		cout<<dp[n][0]<<endl;
	} 
	return 0;
}

```

---

## 作者：liugh_ (赞：3)

## [Gerrymandering](https://codeforces.com/contest/2022/problem/C)

贪心是不好做的，当前的决策不同，之后的决策也会跟着不同。考虑 dp，注意到只有两行，我们可以设 $f(a,b)$ 为第一行填到第 $a$ 列，第二行填到第 $b$ 列时的答案，转移是容易的，时间复杂度 $O(n^2)$。

注意到选区只有两种形状：条和拐。这意味着当两行已填长度差超过 $1$ 时，必须给短的那行填上条。于是很多状态之间的转移是唯一的，这启发我们省去这些无用的状态，设 $f(i,j)$ 为第一行填到第 $i$ 列，第一行与第二行已填长度差为 $j\in\{-1,0,1\}$ 时的答案。转移过程中如果两行已填长度差超过 $1$，就立即补上短的那行。转移详见代码。时间复杂度 $O(n)$。

```cpp
int f[n+5][3]{};
#define f(a,b) f[a][b+1]
#define calc(a,x,b,y,c,z) ((s[x][a]=='A')+(s[y][b]=='A')+(s[z][c]=='A')>=2)
f(0,-1)=f(0,1)=-1e9,f(0,0)=0;
for(int i=0;i<=n;i++){
	tomax(f(i+2,0),f(i,-1)+calc(i+1,0,i+2,0,i+2,1));
	tomax(f(i+3,-1),f(i,-1)+calc(i+1,0,i+2,0,i+3,0)+calc(i+2,1,i+3,1,i+4,1));
	tomax(f(i+3,0),f(i,0)+calc(i+1,0,i+2,0,i+3,0)+calc(i+1,1,i+2,1,i+3,1));
	tomax(f(i+2,1),f(i,0)+calc(i+1,0,i+2,0,i+1,1));
	tomax(f(i+1,-1),f(i,0)+calc(i+1,0,i+1,1,i+2,1));
	tomax(f(i+1,0),f(i,1)+calc(i+1,0,i,1,i+1,1));
	tomax(f(i+3,1),f(i,1)+calc(i+1,0,i+2,0,i+3,0)+calc(i,1,i+1,1,i+2,1));
}
cout<<f(n,0)<<'\n';
```

---

## 作者：xrz114514 (赞：1)

# CF2022C 题解
## [题目传送门](https://www.luogu.com.cn/problem/CF2022C)
## 思路
我们不妨从左到右进行考虑。

很容易想到一个状态 $dp_{i,j}$ 表示上面一行已经分完了 $i$ 个格子，下面一行已经分完了 $j$ 个格子，但这样明显不行。  
发现如果 $i$ 和 $j$ 相差超过三，这样的状态明显没意义。所以可以重新设计状态 $dp_{i,j}$ 表示上面一行已经分完了 $i$ 个，且 $i + j - 3 = k$ ，其中 $k$ 为下面一行已经分完了的格子数。(之所以要减 3 是为了避免负数下标问题)。

转移不用多说，可以将上面叠上3 （一型），或是将下面叠上 3 （一型），或是将一个叠 2 、一个叠 1（ L 型），之后更新差和 $i$ 即可。**需要注意，有时 L 型不能叠，一叠就重复了**。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5, INF = 1e9;

int t, n, a[3][N], dp[N][7];

void Solve(){
  cin >> n;
  for(int i = 1; i <= 2; ++i){
    for(int j = 1; j <= n; ++j){
      char c;
      cin >> c;
      a[i][j] = c == 'A';
    }
  }
  fill(&dp[0][0], &dp[n][6] + 1, -INF);
  dp[0][3] = 0;
  for(int i = 0; i <= n; ++i){
    for(int j = -3; j <= 3; ++j){
      int to = j + 3;
      if(i + j > n || i + j < 0){
        continue;
      }
      if(j <= 0 && i + j + 3 <= n){
        int x = a[2][i + j + 1] + a[2][i + j + 2] + a[2][i + j + 3];
        dp[i][to + 3] = max(dp[i][to + 3], dp[i][to] + (x >= 2));
      }
      if(j >= 0 && i + 3 >= 0){
        int x = a[1][i + 1] + a[1][i + 2] + a[1][i + 3];
        dp[i + 3][to - 3] = max(dp[i][to - 3], dp[i][to] + (x >= 2));
      }
      if((j == 0 || j == 1) && i + j + 1 <= n && i + 2 <= n){
        int x = a[1][i + 1] + a[1][i + 2] + a[2][i + j + 1];
        dp[i + 2][to - 1] = max(dp[i + 2][to - 1], dp[i][to] + (x >= 2));
      }
      if((j == -1 || j == 0) && i + 1 <= n && i + j + 2 <= n){
        int x = a[2][i + j + 1] + a[2][i + j + 2] + a[1][i + 1];
        dp[i + 1][to + 1] = max(dp[i + 1][to + 1], dp[i][to] + (x >= 2));
      }
      //cout << i << ' ' << j << ' ' << dp[i][to] << '\n';
    }
  }
  cout << dp[n][3] << '\n';
}

int main(){
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> t;
  while(t--){
    Solve();
  }
  return 0;
}

```

---

## 作者：_Chronostatis_ (赞：0)

## 题意
给定一个 $2 \cdot n$ 的 01 矩阵，要求将其分为 $\frac{2n}{3}$ 个大小为 3 的连通块，使得满足总和不小于 2 的连通块数量最大，求最大的数量。

## 思路
稍加观察会发现，可以从头开始使用两个指针移动来分出连通块并计算答案。例如：

![](https://cdn.luogu.com.cn/upload/image_hosting/v39vftbt.png)

与[此题](https://www.luogu.com.cn/problem/AT_abc386_f)类似，可以使用**将两指针差和其中一指针**作为状态来做 dp，且指针差较小。

注意到，设计状态时，两指针差只需设定在 $[-3, 3]$ 内即可，因为其他的指针差均被之前所计算过的信息所包含。

### 状态设计
设计状态 $dp_{i, k} \ (k \in [-3, 3])$ 表示其中一指针为 $i$，指针 1 减去指针 2 的值为 $j$ 时，第一行前 $i$ 个格子和第二行前 $i - k$ 个格子中符合要求的连通块的最大数量。但是在实现中，显然不能存储负数下表。所以需要将 $k$ 整体向右偏移 3 位。下文陈述转移时，将按照偏移后的下标来描述。

### 转移
让我们把第一个指针定为 $p$，第二个定为 $q$。转移时，有 4 种情况：
1. $p$ 向前移动 3 个格子，此时 $i \rightarrow i + 3, k \rightarrow k + 3$。$dp_{i, k} \rightarrow dp_{i + 3, k + 3}$。在 $i \in [0, n - 3], k \in [0, 3]$ 时可转移。
2. $q$ 向前移动 3 个格子，此时 $i$ 不变，$k \rightarrow k - 3$。$dp_{i, k} \rightarrow dp_{i, k - 3}$。在 $i \in [0, n], k \in [3, 6]$ 时可转移。
3. $p$ 向前移动 2 个格子，$q$ 向前移动 1 个格子，此时 $i \rightarrow i + 2, k \rightarrow k + 1$。$dp_{i, k} \rightarrow dp_{i + 2, k + 1}$。在 $i \in [0, n - 2], k \in [2, 3]$*时可转移。
4. $p$ 向前移动 1 个格子，$q$ 向前移动 2 个格子，此时 $i \rightarrow i + 1, k \rightarrow k - 1$。$dp_{i, k} \rightarrow dp_{i + 1, k - 1}$。在 $i \in [0, n - 1], k \in [3, 4]$**时可转移。

*：将 $k$ 向左偏移 3 位，得到 $p - q \in [-1, 0]$。如下图，$p - q$ 不在这个区间内，非法。
![](https://cdn.luogu.com.cn/upload/image_hosting/8ijuygzy.png)
**：同上。

### 复杂度分析
时间：状态数 $n \cdot k$，转移 $O(1)$。总时间 $O(n \cdot k)$。

空间：状态数 $n \cdot k$，存储数组 $O(2 \cdot n)$，总空间 $O(n \cdot k + 2 \cdot n) = O(n \cdot k)$。

## 代码
比较丑陋，看看得了。
```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 1e5 + 10, INF = 2e9;

int n, dp[MAXN][7];
bool a[MAXN][2];

bool C(const vector<bool> &v) {
  int cnt = 0;
  for (auto x : v) cnt += x;
  return cnt >= 2;
}

void Solve() {
  cin >> n;
  for (int _ : {0, 1}) {
    for (int i = 1; i <= n; i++) {
      char c;
      cin >> c;
      a[i][_] = c == 'A';
    }
  }
  fill(&dp[0][0], &dp[n][6] + 1, -INF);
  dp[0][3] = 0;
  for (int i = 0; i <= n; i++) {
    for (int k = 6; k >= 0; k--) {
      int j = i - k + 3;
      if (j < 0 || j > n) continue;
      if (i <= n - 3 && k <= 3) {
        dp[i + 3][k + 3] = max(dp[i + 3][k + 3], dp[i][k] + C({a[i + 1][0], a[i + 2][0], a[i + 3][0]}));
      }
      if (k >= 3) {
        dp[i][k - 3] = max(dp[i][k - 3], dp[i][k] + C({a[j + 1][1], a[j + 2][1], a[j + 3][1]}));
      }
      if (i <= n - 2 && k <= 3 && k >= 2) {
        dp[i + 2][k + 1] = max(dp[i + 2][k + 1], dp[i][k] + C({a[i + 1][0], a[i + 2][0], a[j + 1][1]}));
      }
      if (i <= n - 1 && k >= 3 && k <= 4) {
        dp[i + 1][k - 1] = max(dp[i + 1][k - 1], dp[i][k] + C({a[i + 1][0], a[j + 1][1], a[j + 2][1]}));
      }
    }
  }
  cout << dp[n][3] << '\n';
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int T;
  for (cin >> T; T--; Solve());
  return 0;
}
```

---

