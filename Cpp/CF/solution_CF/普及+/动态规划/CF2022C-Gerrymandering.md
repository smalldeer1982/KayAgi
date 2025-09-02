# Gerrymandering

## 题目描述

We all steal a little bit. But I have only one hand, while my adversaries have two.

Álvaro Obregón



Álvaro and José are the only candidates running for the presidency of Tepito, a rectangular grid of $ 2 $ rows and $ n $ columns, where each cell represents a house. It is guaranteed that $ n $ is a multiple of $ 3 $ .

Under the voting system of Tepito, the grid will be split into districts, which consist of any $ 3 $ houses that are connected $ ^{\text{∗}} $ . Each house will belong to exactly one district.

Each district will cast a single vote. The district will vote for Álvaro or José respectively if at least $ 2 $ houses in that district select them. Therefore, a total of $ \frac{2n}{3} $ votes will be cast.

As Álvaro is the current president, he knows exactly which candidate each house will select. If Álvaro divides the houses into districts optimally, determine the maximum number of votes he can get.

 $ ^{\text{∗}} $ A set of cells is connected if there is a path between any $ 2 $ cells that requires moving only up, down, left and right through cells in the set.

## 说明/提示

The image below showcases the optimal arrangement of districts Álvaro can use for each test case in the example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2022C/df820ffc2e1ad6e016254b57c0ce9fb7f735735d.png)

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

## 作者：Yorg (赞：6)

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

## 作者：_O_v_O_ (赞：1)

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

