# 【MGVOI R1-C】收集括号（brackets）

## 题目描述


本题中 **合法括号串** 的定义如下：

::::info[合法括号串的定义]{open}
* ```()``` 是合法括号串。
* 若 ```A``` 是合法括号串，则 ```(A)``` 也是合法括号串。
* 若 ```A```，```B``` 均为合法括号串，则 ```AB``` 也是合法括号串。
* 所有的合法括号串都可以通过上述三条规则得到。

::::

Alice 和 Bob 正在合作玩一款叫做“收集括号”的游戏！这个游戏总共分为以下三步流程：

::::success[第一步：初始化]{open}

* 首先，计算机会自动生成一个 $n$ 行 $m$ 列的方格图，其中第 $i$ 行第 $j$ 列的方格对应的坐标为 $(i,j)$。例如，左上角方格的坐标为 $(1,1)$，右下角方格的坐标为 $(n,m)$。

* 然后，计算机会在每个方格中都填入一个字符（从 ```L```，```R```，```X``` 中选择）。若某个方格中的字符为 ```L```，则表示方格中有一个左括号；若为 ```R```，则表示方格中有一个右括号；若为 ```X```，则表示方格中有一个障碍物。

::::

::::success[第二步：Alice 的行动回合]{open}

* **在第一步流程完全结束之后**，Alice 可以对方格图进行任意次（包括 $0$ 次）**反转操作**。
  
* 在一次反转操作中，Alice 首先需要选择方格图的 **某一行或某一列** 作为这次操作的范围。

* 之后，计算机将遍历 Alice 选择的这一行（或这一列）。对于每一个范围内的方格（除了障碍物），计算机都会反转这个方格上的字符。也就是说，如果方格上原先的字符是 ```L```，那么就将其改为 ```R```；如果原先是 ```R```，那么就将其改为 ```L```；如果原先是 ```X```，那么不做任何改动。

* 对于这一次反转操作而言，如果 Alice 选择了第 $i$ 行（$1\le i\le n$）作为反转范围，那么需要花费 $a_i$ 枚金币；如果她选择了第 $j$ 列（$1\le j\le m$）作为反转范围，那么需要花费 $b_j$ 枚金币。

::::

::::success[第三步：Bob 的行动回合]{open}

* **在第二步流程完全结束之后**，Bob 将从坐标为 $(1,1)$ 的方格处（也就是方格图的左上角）出发，开始收集方格图中的括号。

* 在任意时刻，Bob 都可以选择 **向正下方或正右方** 移动一个方格（前提是要到达的位置既不超过方格图的边界，也没有障碍物）。也就是说，如果 Bob 位于方格 $(x,y)$，那么他下一步就可以前往方格 $(x+1,y)$ 或者方格 $(x,y+1)$，只要他保证自己 **始终位于方格图的范围内，并且不会前往有障碍物的方格**。

* Bob 每到达一个方格，就会收集这个方格中的括号。在抵达坐标为 $(n,m)$ 的终点方格（也就是方格图的右下角）之后，他会整理自己收集到的所有括号（包括起点和终点方格的括号），并将其 **由先到后按照收集的顺序** 排成一个字符串 $S$。

* 如果 $S$ 是一个合法括号串，则 Alice 和 Bob 在这局游戏中共同获胜；否则他们在这局游戏中落败。（如果 Bob 无法到达终点方格，则也认为他们落败）
::::


---


**注意：** 我们假设 Bob 是绝顶聪明的，也就是说，在 Alice 的所有操作完成之后，只要存在任何一种符合上述规则的行动方式能让他们获胜，Bob 就会采用这种行动方式。

在计算机已经填满方格图的情况下（即第一步的初始化流程已经完成），请你帮 Alice 判断，是否存在一种操作方案，使得她能够和 Bob 共同获胜？如果存在，则她最少需要花费多少枚金币来取胜？



## 说明/提示

**【样例 #1】**

::::info[样例 #1 解释]

对于第一组测试数据，计算机生成的方格图为 ```LXXR```。由于中间两个障碍物的阻挡，Bob 无法从方格 $(1,1)$ 向右移动到方格 $(1,4)$，故 Alice 和 Bob 不可能获胜，输出 ```-1```；

对于第二组测试数据，计算机生成的方格图为 ```LLRR```。显然，Bob 可以直接从方格 $(1,1)$ 向右移动到方格 $(1,4)$，最终得到的 $S=(())$ 就是一个合法括号串。因此，Alice 无需花费任何金币进行反转操作即可获胜，输出 ```0```；

对于第三组测试数据，Alice 只需花费 $b_3=1$ 枚金币对第三列使用一次反转操作。在这之后，方格图的状态变为：

| $\orange{\mathtt{L}}$ | $\orange{\mathtt{R}}$ | $\orange{\mathtt{L}}$ |
| -----------: | -----------: | -----------: |
| $\mathtt{X}$ | $\mathtt{R}$ | $\orange{\mathtt{R}}$ |

Bob 只需按照橙色方格对应的路径行动，最终可以得到 $S=()()$，这是一个合法括号串。

容易证明，要让他们获胜最少需要 $1$ 枚金币，故输出 ```1```。

::::

**【样例 #2】**

::::info[样例 #2 解释]

:::success[第一组测试数据]

对于第一组测试数据，Alice 可以分别对第二行和第三列使用反转操作。在这之后，方格图的状态变为：

| $\orange{\mathtt{L}}$ | $\orange{\mathtt{L}}$ | $\orange{\mathtt{R}}$ |
| -----------: | -----------: | -----------: |
| $\mathtt{R}$ | $\mathtt{X}$ | $\orange{\mathtt{L}}$ |
| $\mathtt{L}$ | $\mathtt{X}$ | $\orange{\mathtt{R}}$ |
| $\mathtt{L}$ | $\mathtt{L}$ | $\orange{\mathtt{R}}$ |

* 值得注意的一点是，对于方格 $(2,3)$，由于它总共经历了两次反转，所以仍然维持最开始的状态 $\mathtt{L}$。

Bob 只需按照橙色方格对应的路径行动，最终可以得到 $S=(()())$，这是一个合法括号串。

Alice 总共需要花费 $a_2+b_3=2$ 枚金币，可以证明为最小花费。
:::

:::success[第二组测试数据]

对于第二组测试数据，Alice 可以对第四行使用反转操作。在这之后，方格图的状态变为：

| $\orange{\mathtt{L}}$ | $\mathtt{L}$ | $\mathtt{L}$ |
| -----------: | -----------: | -----------: |
| $\orange{\mathtt{L}}$ | $\mathtt{X}$ | $\mathtt{L}$ |
| $\orange{\mathtt{L}}$ | $\mathtt{X}$ | $\mathtt{L}$ |
| $\orange{\mathtt{R}}$ | $\orange{\mathtt{R}}$ | $\orange{\mathtt{R}}$ |

Bob 只需按照橙色方格对应的路径行动，最终可以得到 $S=((()))$，这是一个合法括号串。

Alice 总共需要花费 $a_4=1$ 枚金币，可以证明为最小花费。

:::

:::success[第三组测试数据]

对于第三组测试数据，Alice 可以分别对第一行、第二行使用反转操作。在这之后，方格图的状态变为：

| $\orange{\mathtt{L}}$ | $\mathtt{L}$ | $\mathtt{L}$ | $\mathtt{L}$ | $\mathtt{L}$ |
| -----------: | -----------: | -----------: | -----------: | -----------: |
| $\orange{\mathtt{L}}$ | $\orange{\mathtt{L}}$ | $\mathtt{X}$ | $\mathtt{X}$ | $\mathtt{L}$ |
| $\mathtt{X}$ | $\orange{\mathtt{R}}$ | $\orange{\mathtt{R}}$ | $\orange{\mathtt{R}}$ | $\mathtt{L}$ |
| $\mathtt{R}$ | $\mathtt{X}$ | $\mathtt{L}$ | $\orange{\mathtt{L}}$ | $\orange{\mathtt{R}}$ |

Bob 只需按照橙色方格对应的路径行动，最终可以得到 $S=((()))()$，这是一个合法括号串。

Alice 总共需要花费 $a_1+a_2=13$ 枚金币，可以证明为最小花费。

:::

:::success[第四组测试数据]

对于第四组测试数据，Alice 可以分别对第一行、第六行、第七行、第二列使用反转操作。在这之后，方格图的状态变为：

| $\orange{\mathtt{L}}$ | $\orange{\mathtt{L}}$ | $\orange{\mathtt{R}}$ | $\mathtt{R}$ | $\mathtt{R}$ | $\mathtt{R}$ | $\mathtt{R}$ | $\mathtt{R}$ | $\mathtt{X}$ | $\mathtt{X}$ |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| $\mathtt{R}$ | $\mathtt{X}$ | $\orange{\mathtt{L}}$ | $\mathtt{X}$ | $\mathtt{L}$ | $\mathtt{X}$ | $\mathtt{L}$ | $\mathtt{L}$ | $\mathtt{R}$ | $\mathtt{L}$ |
| $\mathtt{R}$ | $\mathtt{R}$ | $\orange{\mathtt{L}}$ | $\orange{\mathtt{L}}$ | $\orange{\mathtt{L}}$ | $\mathtt{L}$ | $\mathtt{X}$ | $\mathtt{L}$ | $\mathtt{L}$ | $\mathtt{L}$ |
| $\mathtt{L}$ | $\mathtt{R}$ | $\mathtt{X}$ | $\mathtt{X}$ | $\orange{\mathtt{R}}$ | $\orange{\mathtt{R}}$ | $\orange{\mathtt{R}}$ | $\mathtt{X}$ | $\mathtt{L}$ | $\mathtt{X}$ |
| $\mathtt{L}$ | $\mathtt{R}$ | $\mathtt{L}$ | $\mathtt{L}$ | $\mathtt{L}$ | $\mathtt{R}$ | $\orange{\mathtt{L}}$ | $\orange{\mathtt{L}}$ | $\mathtt{L}$ | $\mathtt{X}$ |
| $\mathtt{X}$ | $\mathtt{L}$ | $\mathtt{R}$ | $\mathtt{R}$ | $\mathtt{X}$ | $\mathtt{R}$ | $\mathtt{X}$ | $\orange{\mathtt{R}}$ | $\orange{\mathtt{R}}$ | $\mathtt{L}$ |
| $\mathtt{R}$ | $\mathtt{L}$ | $\mathtt{X}$ | $\mathtt{R}$ | $\mathtt{X}$ | $\mathtt{R}$ | $\mathtt{R}$ | $\mathtt{X}$ | $\orange{\mathtt{R}}$ | $\orange{\mathtt{R}}$ |


Bob 只需按照橙色方格对应的路径行动，最终可以得到 $S=(\red{()}\blue{(}\red{((()))}\orange{(())}\blue{)})$，这是一个合法括号串。（注：括号串的颜色仅为方便观察，与答案无关）

Alice 总共需要花费 $a_1+a_6+a_7+b_2=22$ 枚金币，可以证明为最小花费。
:::

::::

**【样例 #3】**

见附件中的 ```brackets/brackets3.in``` 与 ```brackets/brackets3.ans```。

这个样例满足测试点 $5 \sim 8$ 的限制。

**【样例 #4】**

见附件中的 ```brackets/brackets4.in``` 与 ```brackets/brackets4.ans```。

这个样例满足测试点 $9 \sim 12$ 的限制。

**【样例 #5】**

见附件中的 ```brackets/brackets5.in``` 与 ```brackets/brackets5.ans```。

这个样例满足测试点 $13 \sim 20$ 的限制。

---



**【数据范围】**

对于所有测试点，保证 $1\le T\le 5$，$1\le n,m\le 100$（$n+m$ 为奇数），$1\le a_i,b_j\le 10^5$，并且方格图中初始填入的字符仅含 ```L```，```R```，```X```，其中左上角和右下角的字符一定不为 ```X```。

::cute-table{tuack}

| **测试点编号** | $T \le$ | $n,m \le$ | $n+m\le$ | **特殊性质** |
|:-:|:-:|:-:|:-:|:-:|
| $1 \sim 4$ | $1$ | $6$ | $7$ |  无
| $5 \sim 8$ | $2$ | $14$ | $15$ | ^
| $9 \sim 12$ | $5$ | $100$ | $101$ | **A**
| $13 \sim 20$ | ^ | ^ | $199$ | 无

特殊性质 **A**：保证 $n=1$。

* 分值分配：每个测试点的分值为 $5$ 分。
* 为避免对算法复杂度常系数的考察，本题的时间限制被设为 1.5s。

## 样例 #1

### 输入

```
3
1 4
1
1 1 1 1
LXXR
1 4
1
1 1 1 1
LLRR
2 3
1 1
1 1 1
LRR
XRL```

### 输出

```
-1
0
1```

## 样例 #2

### 输入

```
4
4 3
1 1 1 9
1 1 1
LLL
LXL
LXL
LLL
4 3
1 1 1 1
1 1 1
LLL
LXL
LXL
LLL
4 5
8 5 6 3
8 5 6 5 3
RRRRR
RRXXR
XRRRL
RXLLR
7 10
10 100 1 1 100 1 10
10 1 1 1 1 1 1 1 1 10
RLLLLLLLXX
RXLXLXLLRL
RLLLLLXLLL
LLXXRRRXLX
LLLLLRLLLX
XLLLXLXLLR
LLXLXLLXLL```

### 输出

```
2
1
13
22```

# 题解

## 作者：zhlzt (赞：2)

:::info[喜提洛谷当前最优解]
<https://www.luogu.com.cn/record/231368443>
:::

注意到数据范围很小，考虑 dp。

设第 $i$ 行为 $r_i$，第 $j$ 行为 $c_j$。钦定左括号的权值为 $1$，右括号为 $-1$。

若 $(i,j)$ 自 $(i-1,j)$ 转移而来，则此前仅有反转 $c_j$ 的操作会对 $(i,j)$ 造成影响。

若 $(i,j)$ 自 $(i,j-1)$ 转移而来，则此前仅有反转 $r_i$ 的操作会对 $(i,j)$ 造成影响。

令 $dp_{i,j,k,0/1,0/1}$ 表示当前位于 $(i,j)$，累计权值为 $k$，是（否）反转 $r_i$，是（否）反转 $c_j$ 时的最小费用。

则最终答案即为 $\min(dp_{n,m,0,0,0},dp_{n,m,0,0,1},dp_{n,m,0,1,0},dp_{n,m,0,1,1})$。

边界可以令 $dp_{1,0,0,0,0}=0$，$dp_{1,0,0,1,0}=a_1$。

时间复杂度 $\mathcal{O}(nm(n+m))$，空间复杂度 $\mathcal{O}(nm(n+m))$。

:::success[【MGVOI R1-C】收集括号 - brackets.cpp]
```cpp line-numbers
#include<bits/stdc++.h>
using namespace std;
const int maxn=105;
int n,m,a[maxn],b[maxn],dp[maxn][maxn][maxn][2][2];
char str[maxn][maxn];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t;cin>>t;
    while(t--){
        cin>>n>>m;
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=1;i<=m;i++) cin>>b[i];
        for(int i=1;i<=n;i++) cin>>(str[i]+1);
        int tot=(n+m-1)/2;
        for(int i=0;i<=n;i++){
            for(int j=0;j<=m;j++){
                for(int k=0;k<=tot;k++){
                    dp[i][j][k][0][0]=dp[i][j][k][0][1]=1e9;
                    dp[i][j][k][1][0]=dp[i][j][k][1][1]=1e9;
                }
            }
        }
        dp[1][0][0][0][0]=0;
        dp[1][0][0][1][0]=a[1];
        int vali,valj;
        for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        for(int k=0;k<=tot;k++){
            if(str[i][j]=='L'){
                if(k>0){
                    vali=min(dp[i-1][j][k-1][0][0],dp[i-1][j][k-1][1][0]);
                    valj=min(dp[i][j-1][k-1][0][0],dp[i][j-1][k-1][0][1]);
                    dp[i][j][k][0][0]=min(dp[i][j][k][0][0],min(vali,valj));
                    vali=min(dp[i-1][j][k-1][1][1],dp[i-1][j][k-1][0][1])+a[i];
                    valj=min(dp[i][j-1][k-1][1][1],dp[i][j-1][k-1][1][0])+b[j];
                    dp[i][j][k][1][1]=min(dp[i][j][k][1][1],min(vali,valj));
                }
                if(k<tot){
                    vali=min(dp[i-1][j][k+1][0][0],dp[i-1][j][k+1][1][0])+a[i];
                    valj=min(dp[i][j-1][k+1][1][0],dp[i][j-1][k+1][1][1]);
                    dp[i][j][k][1][0]=min(dp[i][j][k][1][0],min(vali,valj));
                    vali=min(dp[i-1][j][k+1][0][1],dp[i-1][j][k+1][1][1]);
                    valj=min(dp[i][j-1][k+1][0][0],dp[i][j-1][k+1][0][1])+b[j];
                    dp[i][j][k][0][1]=min(dp[i][j][k][0][1],min(vali,valj));
                }
            }
            else if(str[i][j]=='R'){
                if(k>0){
                    vali=min(dp[i-1][j][k-1][0][0],dp[i-1][j][k-1][1][0])+a[i];
                    valj=min(dp[i][j-1][k-1][1][0],dp[i][j-1][k-1][1][1]);
                    dp[i][j][k][1][0]=min(dp[i][j][k][1][0],min(vali,valj));
                    vali=min(dp[i-1][j][k-1][0][1],dp[i-1][j][k-1][1][1]);
                    valj=min(dp[i][j-1][k-1][0][0],dp[i][j-1][k-1][0][1])+b[j];
                    dp[i][j][k][0][1]=min(dp[i][j][k][0][1],min(vali,valj));
                }
                if(k<tot){
                    vali=min(dp[i-1][j][k+1][0][0],dp[i-1][j][k+1][1][0]);
                    valj=min(dp[i][j-1][k+1][0][0],dp[i][j-1][k+1][0][1]);
                    dp[i][j][k][0][0]=min(dp[i][j][k][0][0],min(vali,valj));
                    vali=min(dp[i-1][j][k+1][1][1],dp[i-1][j][k+1][0][1])+a[i];
                    valj=min(dp[i][j-1][k+1][1][1],dp[i][j-1][k+1][1][0])+b[j];
                    dp[i][j][k][1][1]=min(dp[i][j][k][1][1],min(vali,valj));
                }
            }
		}
		int ans=min(min(dp[n][m][0][0][0],dp[n][m][0][0][1]),
		            min(dp[n][m][0][1][0],dp[n][m][0][1][1]));
		if(ans==1e9) cout<<(-1)<<"\n";
		else cout<<ans<<"\n";
    }
    return 0;
}
```
:::

---

## 作者：XIAOWANGCHAI (赞：2)

### 正文

对于任何一个合法的括号串 $S$，我们有这个性质：

::::info[性质]{open}
$S$ 的任何前缀中，左括号数量不小于右括号数量。
::::

该性质非常重要，是解决该题的关键。

---

我们可以发现 $\texttt{Alice}$ 只能往右与往下走，无后效性，考虑 $\texttt{dp}$。

由于合法括号串的性质，我们给 $\texttt{dp}$ 加一个维度 $k$ 表示左括号数量减去右括号数量的差，只有保证其为非负数才可以转移。

由于 $\texttt{Bob}$ 可以翻转，我们再定义两维表示当前状态的这一行是否翻转与这一列是否翻转。

这个 $\texttt{dp}$ 有五个维度，我们表示为 $dp_{i,j,k,p,q}$ 表示第 $i$ 行，第 $j$ 列，当前左括号减去右括号的差与第 $i$ 行是否翻转，第 $j$ 列是否翻转的最小花费。

为方便下文描述，定义如下数组：

- $x[i][j]$：若第 $i$ 行第 $j$ 列的字符为 $\texttt{L}$，则为 $1$，若为 $\texttt{R}$，则为 $-1$，若为 $\texttt{X}$，则为 $0$。
- $y[i][j]$：若第 $i$ 行第 $j$ 列的字符为 $\texttt{L}$，则为 $-1$，若为 $\texttt{R}$，则为 $1$，若为 $\texttt{X}$，则为 $0$。
---

初始化：

初始时所有的 $\texttt{dp}$ 都应为极大值，可用 $dp_{1,1}$ 作为起始点，则有：

- 若 $x[1][1]=1$，则 $dp_{1,1,x[1][1],0,0}=0$。
- 若 $y[1][1]=1$，则$dp_{1,1,y[1][1],1,0}=a_1$。
- 若 $y[1][1]=1$，则 $dp_{1,1,y[1][1],0,1}=b_1$。
- 若 $x[1][1]=1$，则 $dp_{1,1,x[1][1],1,1}=a_1+b_1$。

除此之外不变。

---

转移：

格子为 $\texttt{X}$ 或 $i=1,j=1$ 直接跳过。

每个格子只能从上或左转移过来，但需要注意，若本行 $p=q=0$，则从上转移来的 $q$ 值必须为 $0$，从左转移来的 $p$ 值必须为 $0$，即你不能说同一列的两个 $\texttt{dp}$ 的转移一个不变列，一个变列，因为所有变化都统一进行了。形式化的，假如正在转移 $\texttt{dp}$，则上面转移来的 $\texttt{dp}$ 的 $q$ 必须与当前的 $q$ 相等，则左面转移来的 $\texttt{dp}$ 的 $p$ 必须与当前的 $p$ 相等。

最后需要判断，若当前变化了行，则从上面来的要加上 $b_j$，若当前变化了列，则从左面来的要加 $a_i$，除此之外还要判断 $k$ 的值是否会变为负数（使用 $x$ 与 $y$ 数组），若 $k+x[i][j]<0$，则不可以转移 $p=0,q=0$ 与 $p=1,q=1$ 的情况，若 $k+y[i][j]$，则不可以转移 $p=0,q=1$ 与 $p=1,q=0$ 的情况。

---

答案：

答案就很简单了，最后括号串应合法则左括号减去右括号的差应为 $0$，即 $\min(dp_{n,m,0,0,0},dp_{n,m,0,1,0},dp_{n,m,0,0,1},dp_{n,m,0,1,1)}$，需要注意，若其为极大值，则无解输出 $\texttt{-1}$。

### 总结

码量确实有点大，但思路清晰照着转移写还是很快的。

### 代码

```
#include<bits/stdc++.h>
#define int long long
#define code using
#define by namespace
#define XWC std;
#define fi first
#define se second
#define debug(a,n)\
		cerr<<#a<<":";\
		for(int i=1;i<=n;i++) cerr<<#a<<"["<<i<<"]="<<a[i]<<" ";\
		cerr<<"\n";
#define debug2(a,n,m)\
		cerr<<#a<<":\n";\
		for(int i=1;i<=n;i++){\
			for(int j=1;j<=m;j++) cerr<<#a<<"["<<i<<"]["<<j<<"]="<<a[i][j]<<" ";\
			cerr<<"\n";\
		}\
		cerr<<"\n";
#define ls (k<<1)
#define rs (k<<1|1)
code by XWC
template<typename T>
inline void read(T &x){
	x=0;
	char ch=getchar();
	bool f=0;
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	if(f) x=-x;
}
template<typename T,typename ...Args>
inline void read(T &tmp,Args &...tmps){
	read(tmp);
	read(tmps...);
}
int t;
int n,m;
const int N=110;
int a[N],b[N];
char c[N][N];
int x[N][N],y[N][N];
int dp[N][N][2*N][2][2];
signed main(){
	read(t);
	while(t--){
		read(n,m);
		for(int i=1;i<=n;i++) read(a[i]);
		for(int i=1;i<=m;i++) read(b[i]);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>c[i][j];
				if(c[i][j]=='L') x[i][j]=1,y[i][j]=-1;
				if(c[i][j]=='R') x[i][j]=-1,y[i][j]=1;
			}
		}
		memset(dp,0x3f,sizeof dp);
		dp[1][1][x[1][1]][0][0]=0;
		dp[1][1][y[1][1]][1][0]=a[1];
		dp[1][1][y[1][1]][0][1]=b[1];
		dp[1][1][x[1][1]][1][1]=a[1]+b[1];
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				for(int k=0;k<2*N;k++){
					if(c[i][j]=='X'||(i==1&&j==1)) continue;
					if(k-x[i][j]>=0){
						dp[i][j][k][0][0]=min(dp[i-1][j][k-x[i][j]][0][0],dp[i-1][j][k-x[i][j]][1][0]);
						int q=min(dp[i][j-1][k-x[i][j]][0][0],dp[i][j-1][k-x[i][j]][0][1]);
						dp[i][j][k][0][0]=min(dp[i][j][k][0][0],q);
					}
					if(k-y[i][j]>=0){
						dp[i][j][k][1][0]=min(dp[i-1][j][k-y[i][j]][0][0]+a[i],dp[i-1][j][k-y[i][j]][1][0]+a[i]);
						int q=min(dp[i][j-1][k-y[i][j]][1][0],dp[i][j-1][k-y[i][j]][1][1]);
						dp[i][j][k][1][0]=min(dp[i][j][k][1][0],q);
					}
					if(k-y[i][j]>=0){
						dp[i][j][k][0][1]=min(dp[i-1][j][k-y[i][j]][0][1],dp[i-1][j][k-y[i][j]][1][1]);
						int q=min(dp[i][j-1][k-y[i][j]][0][0]+b[j],dp[i][j-1][k-y[i][j]][0][1]+b[j]);
						dp[i][j][k][0][1]=min(dp[i][j][k][0][1],q);
					}
					if(k-x[i][j]>=0){
						dp[i][j][k][1][1]=min(dp[i-1][j][k-x[i][j]][0][1]+a[i],dp[i-1][j][k-x[i][j]][1][1]+a[i]);
						int q=min(dp[i][j-1][k-x[i][j]][1][0]+b[j],dp[i][j-1][k-x[i][j]][1][1]+b[j]);
						dp[i][j][k][1][1]=min(dp[i][j][k][1][1],q);
					}
				}
			}
		}
		int q=min({dp[n][m][0][0][0],dp[n][m][0][1][0],dp[n][m][0][0][1],dp[n][m][0][1][1]});
		if(q>1e8) cout<<-1<<"\n";
		else cout<<q<<"\n";
	}
	return 0;
}
```

---

## 作者：nbhs23a28 (赞：1)

由题面及数据范围，很难不发现这是一道比较难以评价的多维 DP 题。

既然要用 DP，首先考虑以下子问题：如何在 DP 中自动筛掉括号不匹配情形？考虑括号匹配机制，我们只要满足过程中任意时刻左括号个数不小于右括号个数，且最终左右括号数相等即可。为了维护，我们在朴素方格数上二维线性 DP 的基础上加一维右括号个数，转移时只转移右括号数小于等于 $(i+j-1)/2$ 的即可。

解决此子问题后，接下来顺着 DP 思路考虑如何维护行列翻转。很难不注意到由于 Bob 只会向右或向下走，对于 $(i,j)$，第 $[1,i-1]$ 行的翻转以及 $[1,j-1]$ 列的翻转显然是无后效性的，符合 DP 要求。不过要注意到本行本列的会对接下来的转移产生影响，如何处理这一后效性呢？暴力多开两维 $0,1$ 存呗！然后本题的简要口胡思路分析就愉快地结束了。时间复杂度显然的 $O(Tn^3)$，足以通过此题。

然后本题的代码实现（状态转移）就非常不愉快了，由于过于长，见代码核心部分（三层循环）。（请忽略我一大坨的实现对观感的影响，~~50 多行代码高达 2KB 也是无敌了，赛时极速 30min 调出~~）

::::success[Code]
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[110],b[110];
long long f[110][110][110][2][2];
char c[110][110];
int main()
{int t;cin>>t;
 while(t--)
 {cin>>n>>m;
  for(int i=0;i<=101;i++)
  {for(int j=0;j<=101;j++)
   {for(int k=0;k<=101;k++)
     f[i][j][k][0][0]=f[i][j][k][0][1]=f[i][j][k][1][0]=f[i][j][k][1][1]=1e18; 
   }   
  }
  for(int i=1;i<=n;i++) cin>>a[i];
  for(int i=1;i<=m;i++) cin>>b[i];
  for(int i=1;i<=n;i++)
  {for(int j=1;j<=m;j++)
    cin>>c[i][j];
  }
  if(c[1][1]=='L')
  f[1][1][0][0][0]=0,f[1][1][0][1][1]=a[1]+b[1];
  else
  f[1][1][0][0][1]=b[1],f[1][1][0][1][0]=a[1];
  for(int i=1;i<=n;i++)
  {for(int j=1;j<=m;j++)
   {if(i==1&&j==1) continue;
    for(int k=0;k<=(i+j-1)/2;k++)//k:r的个数
    {if(c[i][j]=='X') f[i][j][k][0][0]=f[i][j][k][0][1]=f[i][j][k][1][0]=f[i][j][k][1][1]=1e18;
     else
     {if(c[i][j]=='L')
      {f[i][j][k][0][0]=min(min(f[i-1][j][k][0][0],f[i-1][j][k][1][0]),min(f[i][j-1][k][0][0],f[i][j-1][k][0][1]));
       f[i][j][k][1][1]=min(min(f[i-1][j][k][0][1],f[i-1][j][k][1][1])+a[i],min(f[i][j-1][k][1][0],f[i][j-1][k][1][1])+b[j]);
       if(k>=1)
       {f[i][j][k][0][1]=min(min(f[i-1][j][k-1][0][1],f[i-1][j][k-1][1][1]),min(f[i][j-1][k-1][0][0],f[i][j-1][k-1][0][1])+b[j]);
       f[i][j][k][1][0]=min(min(f[i-1][j][k-1][0][0],f[i-1][j][k-1][1][0])+a[i],min(f[i][j-1][k-1][1][0],f[i][j-1][k-1][1][1]));
       }
      }
      else
      {f[i][j][k][0][1]=min(min(f[i-1][j][k][0][1],f[i-1][j][k][1][1]),min(f[i][j-1][k][0][0],f[i][j-1][k][0][1])+b[j]);
       f[i][j][k][1][0]=min(min(f[i-1][j][k][0][0],f[i-1][j][k][1][0])+a[i],min(f[i][j-1][k][1][0],f[i][j-1][k][1][1]));
       if(k>=1)
       {f[i][j][k][0][0]=min(min(f[i-1][j][k-1][0][0],f[i-1][j][k-1][1][0]),min(f[i][j-1][k-1][0][0],f[i][j-1][k-1][0][1]));
        f[i][j][k][1][1]=min(min(f[i-1][j][k-1][0][1],f[i-1][j][k-1][1][1])+a[i],min(f[i][j-1][k-1][1][0],f[i][j-1][k-1][1][1])+b[j]);
       }
      }
     }
    }
  }
 }
  long long ans=min(min(f[n][m][(n+m-1)/2][0][0],f[n][m][(n+m-1)/2][1][1]),min(f[n][m][(n+m-1)/2][0][1],f[n][m][(n+m-1)/2][1][0]));
  if(ans==1e18) cout<<"-1\n";
  else cout<<ans<<'\n';
} 
}

---

## 作者：Lishuyi0504 (赞：1)

## 题意
给定一个 $n\times m$ 的矩阵，其中 L 是左括号，R 是右括号，X 为障碍物。给定反转行、列的代价，求从 $(1,1)$ 至 $(n,m)$ 只能往右走或往下走构成合法括号序列的最小代价。
## 分析
根据题目，可以惊喜的发现本题的走法是没有后效性的，那么自然而然的就可以考虑到 DP。

首先，考虑括号的匹配问题，我们可以定义一维表示待匹配栈内的左括号数量（右括号可以与左括号匹配）。其次，考虑标记当前的行与列是否被反转并已经花费，我们可以进行状态扩展：用一个二位的二进制表示，第一位表示是否反转该行，第二位表示是否反转该列。

所以 $dp[x][y][k][st]$ 表示位于 $(x,y)$ 位置，剩余 $k$ 个左括号未匹配，行列的反转状态为 $st$ 时的最小代价。

单次询问时间复杂度为 $O(nm(n+m))$。
## 代码
``` cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 101, M = 201, inf = 0x3f3f3f3f;
int n, m, dp[N][N][M][4], a[N], b[N];
char mp[N][N];
void solve()
{
	memset(dp, 0x3f, sizeof dp); 
	cin >> n >> m;
	for(int i = 1; i <= n; i ++) cin >> a[i];
	for(int i = 1; i <= m; i ++) cin >> b[i];
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			cin >> mp[i][j];

    // 初始化
	if(mp[1][1] == 'L')
	{
		dp[1][1][1][0] = 0;
		dp[1][1][1][3] = a[1] + b[1];
	}else
	{
		dp[1][1][1][1] = a[1];
		dp[1][1][1][2] = b[1];
	}
    // 状态转移
	for(int i = 1; i <= n; i ++)
	{
		for(int j = 1; j <= m; j ++)
		{
			if(mp[i][j] == 'X') continue; // 跳过无效的障碍物
			if(i == 1 && j == 1) continue; // 跳过起点
			for(int k = 0; k <= i + j - 1; k ++) // k 最小为 0，最大为路径长度的一半，注意合法括号串前缀和非负
            // st 的取值与表示: 0  1 - 2 | 3 +
			{
				int op = mp[i][j] == 'L' ? 1 : -1; // 该位置为栈内元素数量的贡献
				if(k - op >= 0) // 是否合法
				{
					dp[i][j][k][0] = min({inf, dp[i - 1][j][k - op][1], dp[i - 1][j][k - op][0], dp[i][j - 1][k - op][2], dp[i][j - 1][k - op][0]});
					dp[i][j][k][3] = min({inf, dp[i - 1][j][k - op][2] + a[i], dp[i - 1][j][k - op][3] + a[i], dp[i][j - 1][k - op][1] + b[j], dp[i][j - 1][k - op][3] + b[j]});
				}
				if(k + op >= 0)
				{
					dp[i][j][k][1] = min({inf, dp[i - 1][j][k + op][0] + a[i], dp[i - 1][j][k + op][1] + a[i], dp[i][j - 1][k + op][1], dp[i][j - 1][k + op][3]});
					dp[i][j][k][2] = min({inf, dp[i - 1][j][k + op][2], dp[i - 1][j][k + op][3], dp[i][j - 1][k + op][0] + b[j], dp[i][j - 1][k + op][2] + b[j]});
				}
			}
		}
	}
    // 找答案
	int ans = min({dp[n][m][0][0], dp[n][m][0][1], dp[n][m][0][2], dp[n][m][0][3]});
	if(ans == inf) cout << -1 << '\n';
	else cout << ans << '\n';
}
int main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int T;
	cin >> T;
	while(T --) solve();
	return 0; // 华丽的结束
}

```

---

## 作者：HKW0202 (赞：1)

题意已经说的非常清楚了，很容易发现这是一道裸的 $dp$ 题。

我们可以先考虑给定一个方格图，求是否能够从左上角到右下角使得路径是一个合法的括号序列。我们令 $f[i][j][k]$ 表示当前在第 $i$ 行第 $j$ 列，未匹配的左括号还有 $k$ 个的情况。

- 若 $s[i][j]$ 为 $L$，则有$f[i][j][k]=f[i][j][k]\mid f[i-1][j][k-1]$ ，从左侧转移同理。
- 若 $s[i][j]$ 为 $R$，则有$f[i][j][k]=f[i][j][k]\mid f[i-1][j][k+1]$ ，从左侧转移同理。

会做这个问题，那么这道题就简单多了，我们设 $f[i][j][k][op1][op2]$ ，其中 $i,j,k$ 与上文意义相同，$op1$ 表示这一行是否翻转，$op2$ 表示这一列是否翻转，在这种情况下所需代价的最小值。转移与之前的相似，我写的略为复杂，具体看代码实现。

```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define int long long
#define qwq ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
const int N=2e2+10,mod=1e9+7;
int T,n,m,a[N],b[N],f[102][102][202][2][2];
char o[N][N],s[N][N];
void minn(int &x,int y){
	x=min(x,y);
}
int solve(){
	for(int i=0;i<=n;i++)for(int j=0;j<=m;j++)for(int k=0;k<=n+m;k++)f[i][j][k][0][0]=f[i][j][k][0][1]=f[i][j][k][1][0]=f[i][j][k][1][1]=1e18;
	if(s[1][1]=='L'){
		f[1][1][1][0][0]=0;
		f[1][1][1][1][1]=a[1]+b[1];
	}
	else{
		f[1][1][1][1][0]=a[1];
		f[1][1][1][0][1]=b[1];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(i==j&&j==1||s[i][j]=='X')continue;
			if(s[i][j]=='L'){
				for(int k=1;k<=i+j;k++){
					if(i>1)minn(f[i][j][k][0][0],f[i-1][j][k-1][0][0]);
					if(j>1)minn(f[i][j][k][0][0],f[i][j-1][k-1][0][1]);
					if(i>1)minn(f[i][j][k][0][0],f[i-1][j][k-1][1][0]);
					if(j>1)minn(f[i][j][k][0][0],f[i][j-1][k-1][0][0]);
					
					if(i>1)minn(f[i][j][k][1][1],f[i-1][j][k-1][0][1]+a[i]);
					if(j>1)minn(f[i][j][k][1][1],f[i][j-1][k-1][1][0]+b[j]);
					if(i>1)minn(f[i][j][k][1][1],f[i-1][j][k-1][1][1]+a[i]);
					if(j>1)minn(f[i][j][k][1][1],f[i][j-1][k-1][1][1]+b[j]);
				}
				for(int k=0;k<=i+j;k++){
					if(i>1)minn(f[i][j][k][0][1],f[i-1][j][k+1][0][1]);
					if(j>1)minn(f[i][j][k][0][1],f[i][j-1][k+1][0][0]+b[j]);
					if(i>1)minn(f[i][j][k][0][1],f[i-1][j][k+1][1][1]);
					if(j>1)minn(f[i][j][k][0][1],f[i][j-1][k+1][0][1]+b[j]);
					
					if(i>1)minn(f[i][j][k][1][0],f[i-1][j][k+1][0][0]+a[i]);
					if(j>1)minn(f[i][j][k][1][0],f[i][j-1][k+1][1][0]);
					if(i>1)minn(f[i][j][k][1][0],f[i-1][j][k+1][1][0]+a[i]);
					if(j>1)minn(f[i][j][k][1][0],f[i][j-1][k+1][1][1]);
				}
			}
			else{
				for(int k=0;k<=i+j;k++){
					if(i>1)minn(f[i][j][k][0][0],f[i-1][j][k+1][0][0]);
					if(j>1)minn(f[i][j][k][0][0],f[i][j-1][k+1][0][1]);
					if(i>1)minn(f[i][j][k][0][0],f[i-1][j][k+1][1][0]);
					if(j>1)minn(f[i][j][k][0][0],f[i][j-1][k+1][0][0]);
					
					if(i>1)minn(f[i][j][k][1][1],f[i-1][j][k+1][0][1]+a[i]);
					if(j>1)minn(f[i][j][k][1][1],f[i][j-1][k+1][1][0]+b[j]);
					if(i>1)minn(f[i][j][k][1][1],f[i-1][j][k+1][1][1]+a[i]);
					if(j>1)minn(f[i][j][k][1][1],f[i][j-1][k+1][1][1]+b[j]);
				}
				for(int k=1;k<=i+j;k++){
					if(i>1)minn(f[i][j][k][0][1],f[i-1][j][k-1][0][1]);
					if(j>1)minn(f[i][j][k][0][1],f[i][j-1][k-1][0][0]+b[j]);
					if(i>1)minn(f[i][j][k][0][1],f[i-1][j][k-1][1][1]);
					if(j>1)minn(f[i][j][k][0][1],f[i][j-1][k-1][0][1]+b[j]);
					
					if(i>1)minn(f[i][j][k][1][0],f[i-1][j][k-1][0][0]+a[i]);
					if(j>1)minn(f[i][j][k][1][0],f[i][j-1][k-1][1][0]);
					if(i>1)minn(f[i][j][k][1][0],f[i-1][j][k-1][1][0]+a[i]);
					if(j>1)minn(f[i][j][k][1][0],f[i][j-1][k-1][1][1]);
				}
			}
			
		}
	}
	int ans=min(f[n][m][0][0][0],f[n][m][0][0][1]);
	ans=min(ans,f[n][m][0][1][0]);
	ans=min(ans,f[n][m][0][1][1]);
	if(ans>1e9)return -1;//场上数字写小了只剩25pts qwq 
	return ans;
}
signed main(){
	qwq;
	cin>>T;
	while(T--){
		cin>>n>>m;
		int ans=1e18;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=m;i++)cin>>b[i];
		for(int i=1;i<=n;i++)cin>>s[i]+1;
		cout<<solve()<<"\n";
	}
	return 0;
}

```

---

## 作者：mahaorui2012 (赞：0)

# 前言

这题题面好长啊，看了我半天。 

# 思路

不妨认为，在 Bob 进入新的一行或一列时， Alice 再决定是否翻转。

容易发现当前的格子被没被翻转仅取决于当前列和当前行被没被翻转；一个括号序列合法等价于其所有前缀的左括号数量不小于右括号数量。我们只需要知道当前位于哪个格子上、前缀左括号剩余数量，以及当前行和列是否被翻转即可。考虑dp。

设 $f_{i,j,k,p,q}$ 表示当前位于格子 $(i,j)$ 上，前面剩下 $k$ 个括号没匹配，$p$ 和 $q$ 为 $0$ 或 $1$，分别表示当前行和列被没被翻转，值为达到这种状态的最小金币数量。

初始状态是 $f_{1,1,1,p,q}$，其中 $p$ 和 $q$ 需要满足翻转后第一格上是左括号。 

转移从左边和上面选一边过来即可。需要一直保证 $k\geq 0$。 

答案即 $f_{n,m,0,p,q}$，$p$ 和 $q$ 随意。

状态有 $O(n^3)$ 个，转移 $O(1)$，但常数可能偏大。 

# AC CODE 

状态比较多，看起来比较丑。 

```cpp
#include <iostream>
#include <cstring>
using namespace std;

const int N=105;

int a[N],b[N];

int g[N][N];
int dp[N][N][2*N][2][2];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	
	int t;
	cin>>t;
	while(t--){
		int n,m;
		cin>>n>>m;
		for(int i=1;i<=n;++i){
			cin>>a[i];
		}for(int i=1;i<=m;++i){
			cin>>b[i];
		}
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				char c;
				cin>>c;
				switch(c){
					case 'L':
						g[i][j]=0;
						break;
					case 'R':
						g[i][j]=1;
						break;
					case 'X':
						g[i][j]=2;
						break;
				}
			}
		}
		memset(dp,0x3f,sizeof(dp));
		if(g[1][1]==0){
			dp[1][1][1][0][0]=0;
			dp[1][1][1][1][1]=a[1]+b[1];
		}else{
			dp[1][1][1][1][0]=b[1];
			dp[1][1][1][0][1]=a[1];
		}
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				if(g[i][j]==2) continue;
				if(i==1 && j==1) continue;
				for(int k=0;k<=n+m;++k){
					for(int p=0;p<=1;++p){
						for(int q=0;q<=1;++q){
							int cur=((g[i][j]^p^q)?-1:1);
							if(k-cur<0) continue;
							if(i>1) dp[i][j][k][p][q]=min(dp[i][j][k][p][q],
										min(dp[i-1][j][k-cur][p][0],
											dp[i-1][j][k-cur][p][1])+a[i]*q);
							if(j>1) dp[i][j][k][p][q]=min(dp[i][j][k][p][q],
										min(dp[i][j-1][k-cur][0][q],
											dp[i][j-1][k-cur][1][q])+b[j]*p);
							//cout<<i<<' '<<j<<' '<<k<<' '<<p<<' '<<q<<' '<<dp[i][j][k][p][q]<<'\n';
						}
					}
				}
			}
		}
		int ans=min(min(dp[n][m][0][0][0],dp[n][m][0][0][1]),
					min(dp[n][m][0][1][0],dp[n][m][0][1][1]));
		cout<<(ans<=1e9?ans:-1)<<'\n';
	}
	return 0;
}
```

---

## 作者：GrYWnds (赞：0)

## 写在前面
**清晰思路成就优雅代码**

虽然最优解排到了第三页，但是1.5KB代码超越所有人。
## 思路

首先经典思路，将左括号看做 1，将右括号看做 -1，由此问题转化为：选择一条从 $(1,1)$ 到 $(n,m)$ 的路径，使得路径权值和为 0 且路径上任意一点的前缀权值和非负。

考虑翻转操作：显而易见的是对于同一行或者同一列不会翻转 2 次，因为这样相当于没有操作而且浪费了金币。

那么我们考虑在第一次到达某一行或者某一列时就决定该行（列）要不要翻转。接下来发现每一次到达新的行一定是由一次向下移动来达成；每一次到达新的列一定是由一次向右移动来达成。发现这很像 dp 的转移式，同时观察到数据很小，于是我们使用 dp 来解决。

考虑状态设计：设 $dp_{i,j,k,p,q}$，$p,q \in \{ 0,1 \} $ 表示：当前考虑到第 $i$ 行第 $j$ 列，当前路径权值和为 $k$，第 $i$ 行是否翻转 $(p)$，第 $j$ 行是否翻转 $(q)$ 的情况下所花费的金币最小值。

考虑转移：首先如果 $(i,j)$ 为障碍就不进行转移，因为到不了。

接下来分别考虑两种移动，设 $o$ 表示在 $p$，$q$ 的情况下 $(i,j)$ 格左右括号的情况，由上文得 $o \in \{1,-1\} $：

若 $(i,j)$ 由 $(i-1,j)$ 通过向下移动得到，那么第 $j$ 列的翻转情况 $q$ 应该相同，由于行发生了变化，上一行是否翻转与本行无关，因此对上一行是否翻转的情况取 $\min$ 然后转移，再加上本行是否翻转的代价，方程：

$$
dp_{i,j,k,p,q} = \min( dp_{i-1,j,k-o,1,q} , dp_{i-1,j,k-o,0,q} ) + [p=1] \times a_i
$$

若 $(i,j)$ 由 $(i,j-1)$ 通过向右移动得到，那么第 $i$ 行的翻转情况 $p$ 应该相同，由于列发生了变化，上一列是否翻转与本列无关，因此对上一列是否翻转的情况取 $\min$ 然后转移，再加上本列是否翻转的代价，方程：

$$
dp_{i,j,k,p,q} = \min( dp_{i,j-1,k-o,p,1} , dp_{i,j-1,k-o,p,0} ) + [q=1] \times b_i
$$


接下来考虑初始化：由于求最小值，初始 dp 数组应全为 $\infty$。$(1,1)$ 是由 $(1,0)$ 与 $(0,1)$ 得到的，因此这两格应设为：

$$
dp_{1,0,0,0,0} = 0 , dp_{1,0,0,1,0} = a_1 , dp_{0,1,0,0,0} = 0 , dp_{0,1,0,0,1} = b_1
$$

考虑答案统计：我们要走到 $(n,m)$，且路径权值和应为 0，至于最后一行最后一列是否翻转我们并不关心，设答案为 $ans$，则：

$$
ans = \min( dp_{n,m,0,0,0} , dp_{n,m,0,0,1} , dp_{n,m,0,1,0} , dp_{n,m,0,1,1} )
$$

时间复杂度 $O(n^3)$，此处 $k$ 的取值可以只取到 $(n+m-1) \div 2$，因为若左括号数大于这个值一定不会有足够的右括号去匹配。

## 代码
**Think twice Code once.**

代码比预想中简洁得多。

::::success[代码]

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 110

long long read(){
	long long res=0;char c=getchar();bool flag=0;
	while(c<'0'||c>'9'){
		flag|=(c=='-');
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		res=(res<<1)+(res<<3)+(c^48);
		c=getchar();
	}
	return res * ( flag ? -1 : 1 );
}

int n,m,len,a[N],b[N];
int dp[N][N][N][2][2];
int mp[N][N][2];

void GrYWnds(){
	memset(dp,0x3f,sizeof(dp));
	n=read();m=read();len=(n+m-1)/2;
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=m;i++) b[i]=read();
	for(int i=1;i<=n;i++){
		string s;cin>>s;
		for(int j=1;j<=m;j++){
			mp[i][j][0] = s[j-1]=='X' ? 0 : s[j-1]=='L' ? 1 : -1 ;
			mp[i][j][1] = s[j-1]=='X' ? 0 : s[j-1]=='L' ? -1 : 1 ;
		}
	}
	dp[1][0][0][0][0]=0;
	dp[1][0][0][1][0]=a[1];
	dp[0][1][0][0][0]=0;
	dp[0][1][0][0][1]=b[1];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(mp[i][j][0]==0) continue;
			for(int k=0;k<=len;k++){
				for(int p=0;p<=1;p++){
					for(int q=0;q<=1;q++){
						int o=mp[i][j][p^q];
						if(o==1&&k==0) continue;
						dp[i][j][k][p][q] = min( dp[i][j][k][p][q] , min( dp[i-1][j][k-o][1][q] , dp[i-1][j][k-o][0][q] ) + (p==1)*a[i] );
						dp[i][j][k][p][q] = min( dp[i][j][k][p][q] , min( dp[i][j-1][k-o][p][1] , dp[i][j-1][k-o][p][0] ) + (q==1)*b[j] );
					}
				}
			}
		}
	}
	int ans=min( min( dp[n][m][0][0][0] , dp[n][m][0][0][1] ) , min( dp[n][m][0][1][0] , dp[n][m][0][1][1] ) );
	if(ans>1e9) printf("-1\n");
	else printf("%d\n",ans);
}

int main(){
	int T=read();
	while(T--) GrYWnds();
	return 0;
}

```
::::

---

## 作者：Ligans (赞：0)

先回顾一下怎么判断合法括号串，这是[P1739](https://www.luogu.com.cn/problem/P1739)。

具体地，维护一个辅助的栈，大小用 $k$ 表示。对字符串从左到右扫一遍，遇到左括号将 $k$ 加 $1$，遇到右括号将 $k$ 减 $1$。若 $k$ 始终非负，且最终为 $0$，则这是一个合法括号串。

回到题目。

若不存在反转操作，不难想到使用动态规划。

设 $dp_{i,j,k}$ 表示当前在 $(i,j)$ 位置，辅助栈大小为 $k$ 的可行性。容易写出初状态和转移。

考虑反转操作。由于反转操作在收集操作之前，不能边收集边反悔，所以沿用原状态枚举这一位置是否反转是不可行的。

在状态设计上加上两维 $0/1$ 维，分别表示第 $i$ 行、第 $j$ 列是否被反转。容易写出初状态，大力讨论转移即可。

视 $n,m$ 同阶，单次测试复杂度 $O(n^3)$。

```cpp
void sol(){
	ans=inf;
	memset(dp,0x3f,sizeof dp);
	
	n=rd(),m=rd();
	_rep(i,1,n) a[i]=rd();
	_rep(i,1,m) b[i]=rd();
	_rep(i,1,n) _rep(j,1,m) scanf(" %c",&c[i][j]);
	_rep(i,1,n) _rep(j,1,m) _rep(k,0,i+j-1){
		if(c[i][j]=='X') continue;
		_rep(ii,0,1) _rep(jj,0,1){
			int res;
			if(c[i][j]=='L') res=-1;
			if(c[i][j]=='R') res=1;
			if(ii) res=-res;
			if(jj) res=-res;
			if(i==1&&j==1&&k==1&&res==-1) dp[i][j][k][ii][jj]=ii*a[i]+jj*b[j];
			ckmin(dp[i][j][k][ii][jj],dp[i-1][j][k+res][0][jj]+ii*a[i]);
			ckmin(dp[i][j][k][ii][jj],dp[i-1][j][k+res][1][jj]+ii*a[i]);
			ckmin(dp[i][j][k][ii][jj],dp[i][j-1][k+res][ii][0]+jj*b[j]);
			ckmin(dp[i][j][k][ii][jj],dp[i][j-1][k+res][ii][1]+jj*b[j]);
		}
	}
	_rep(ii,0,1) _rep(jj,0,1) ckmin(ans,dp[n][m][0][ii][jj]);
	if(ans==inf) puts("-1");
	else wr(ans),ptc('\n');
}
```

---

题面那么长真的看得很累啊。

---

## 作者：K_yuxiang_rose (赞：0)

~~可惜比赛还剩两个多小时才进去的，不然就场了。~~

题面看着很长，它的意思其实就是选定若干个行和列，付出相应代价，将每个行列反转，指的是 `L` 变成 `R`，`R` 变成 `L`。若 `L` 代表左括号，`R` 代表有括号，问从左上角走到右下角，每次只能往右或往下走，不能走到 `X`，使得沿途连成的括号串合法的最小代价是多少，无法达成输出 $-1$。

要让这个字符串最终合法，首先要保证它始终合法，也就是任意时刻，字符串中 `L` 的个数不少于 `R` 的个数。同时容易发现每个行或列最多被反转一次，并且只对于当前行或当前列存在后效性，于是考虑 DP。设 $dp_{i,j,k,0/1,0/1}$ 表示对于第 $i$ 行，第 $j$ 列，当前字符串中有 $k$ 个 `L`，是否已经反转当前行，是否已经反转当前列的最小代价，然后就能无脑转移了。

注意事项：

* 因为 `L` 的个数不能少于 `R` 的个数，所以 $k$ 要大于等于 $\lceil \frac{i+j-1}{2}\rceil$。
* 不能通过未反转的状态来达到反转状态，例如：$dp_{i,j,k,0,1}=dp_{i-1,j,k-1,0,0}+b_j$，这里本来第 $j$ 行没有反转，却被转移成了反转，有后效性。

具体转移见代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[105],b[105],dp[105][105][205][2][2];
char c[105][105];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int t;
	cin>>t;
	while(t--)
	{
		int n,m;
		cin>>n>>m;
		for(int i=0;i<=100;i++)
			for(int j=0;j<=100;j++)
				for(int k=0;k<=200;k++)
					for(int l=0;l<2;l++)
						for(int _=0;_<2;_++)
							dp[i][j][k][l][_]=1e18;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=m;i++) cin>>b[i];
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				cin>>c[i][j];
		if(c[1][1]=='L')
		{
			dp[1][1][1][0][0]=0;
			dp[1][1][1][1][1]=a[1]+b[1];
		}
		else
		{
			dp[1][1][1][1][0]=a[1];
			dp[1][1][1][0][1]=b[1];
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(i==1&&j==1) continue;
				for(int k=(i+j)/2;k<=i+j-1;k++)
				{
					if(c[i][j]=='X') continue;
					if(c[i][j]=='L')
					{
						dp[i][j][k][0][0]=min({dp[i][j-1][k-1][0][1],dp[i][j-1][k-1][0][0],dp[i-1][j][k-1][1][0],dp[i-1][j][k-1][0][0]});
						dp[i][j][k][0][1]=min(min(dp[i][j-1][k][0][0],dp[i][j-1][k][0][1])+b[j],min(dp[i-1][j][k][0][1],dp[i-1][j][k][1][1]));
						dp[i][j][k][1][0]=min(min(dp[i-1][j][k][0][0],dp[i-1][j][k][1][0])+a[i],min(dp[i][j-1][k][1][0],dp[i][j-1][k][1][1]));
						dp[i][j][k][1][1]=min(min(dp[i-1][j][k-1][0][1],dp[i-1][j][k-1][1][1])+a[i],min(dp[i][j-1][k-1][1][0],dp[i][j-1][k-1][1][1])+b[j]);
					}
					else
					{
						dp[i][j][k][0][0]=min({dp[i][j-1][k][0][1],dp[i][j-1][k][0][0],dp[i-1][j][k][1][0],dp[i-1][j][k][0][0]});
						dp[i][j][k][0][1]=min(min(dp[i][j-1][k-1][0][0],dp[i][j-1][k-1][0][1])+b[j],min(dp[i-1][j][k-1][0][1],dp[i-1][j][k-1][1][1])); 
						dp[i][j][k][1][0]=min(min(dp[i-1][j][k-1][0][0],dp[i-1][j][k-1][1][0])+a[i],min(dp[i][j-1][k-1][1][0],dp[i][j-1][k-1][1][1]));
						dp[i][j][k][1][1]=min(min(dp[i-1][j][k][0][1],dp[i-1][j][k][1][1])+a[i],min(dp[i][j-1][k][1][0],dp[i][j-1][k][1][1])+b[j]);
					}
				}
			}
		}
		int ans=min({dp[n][m][(n+m-1)/2][0][0],dp[n][m][(n+m-1)/2][0][1],dp[n][m][(n+m-1)/2][1][0],dp[n][m][(n+m-1)/2][1][1]});
		if(ans>=1e18) cout<<"-1\n";
		else cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：FruitWasTaken (赞：0)

## 出题人题解

### 主要知识点

* 【3】栈
* 【5】深度优先搜索
* 【6】多维动态规划

建议在了解 [P1739 表达式括号匹配](https://www.luogu.com.cn/problem/P1739) 和 [P1002 过河卒](https://www.luogu.com.cn/problem/P1002) 的解法之后再阅读本题解。

---

### 子问题：分析 Bob 的最优策略

我们先来考虑一个弱化版的问题：假设现在没有反转操作，只有一张字符方格图，我们该如何判断 Bob 是否存在获胜的行动方式呢？（数据范围不变）

先看暴搜怎么写：我们在搜索路径的时候可以实时模拟一个用于括号匹配的栈，即用一个变量 $k$ 来表示它此刻的大小。只要搜集到一个左括号就把 $k$ 增加 $1$，对于右括号则把 $k$ 减小 $1$，那么只要“从起点到终点的路径”上任意一点对应的 $k$ 均非负，并且最终 $k=0$，就意味着得到的字符串 $S$ 是一个合法括号串。

```cpp
void dfs(int x, int y, int k)
{
    if (x > n || y > m)
        return false;

    if (map[x][y] == 'X')
        return false;

    k += (map[x][y] == '(' ? 1 : -1);

    if (k < 0)
        return false;

    if (x == n && y == m)
        return k == 0;

    return dfs(x + 1, y, k) || dfs(x, y + 1, k);
}
```

然后其实改成记忆化搜索就能由 $O(2^{nm})$ 优化到 $O(nm\cdot (n+m))$ 了，我们考虑直接换成 dp 的形式来写：

```cpp
bool check()
{
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= m; j++)
			for (int k = 0; k <= n + m; k++)
				dp[i][j][k] = false;
	 
	dp[0][1][0] = dp[1][0][0] = true;
	
	char brac;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			brac = map[i][j];
			if (brac == 'X')
				continue;
			
			for (int k = 0; k < m + n; k++)
			{
				if (brac == 'L' && k >= 1)
					dp[i][j][k] = dp[i - 1][j][k - 1] || dp[i][j - 1][k - 1];
					
				if (brac == 'R')
					dp[i][j][k] = dp[i - 1][j][k + 1] || dp[i][j - 1][k + 1];
			}
		}
	}
	
	return dp[n][m][0];
}
```

回到原问题，这样配合 $O(2^{n+m})$ 的 DFS 枚举反转情况，可以拿到 $40$ 分。

同时可以稍加思考一下 $n=1$ 的情况，其实就是枚举唯一的一行是否反转，然后类比上述过程，将“括号匹配栈”的大小作为 DP 状态，边走边枚举每列是否反转。并且发现这个“边走边枚举是否反转”的思路似乎是可以推广到一般情况的，更加坚定了我们选择 DP 解决此问题的决心！

---


### 正解：通过 DP 实现“边走边枚举反转”

虽然只有在 Alice 的所有反转结束之后 Bob 才能行动，但是我们也可以让 Bob 先开始走，再临时决定当前所在的行或列是否反转。

我们先尝试和子问题一样，用 $dp_{i,j,k}$ 表示 Bob 走到 $(i,j)$，并且使得当前栈的大小为 $k$ 时最少需要花费的金币数。状态转移时，枚举当前的行和列是否反转。问题来了，这样设计状态可以吗？

考虑这样一种情况：Bob 刚刚走过 $(i,j)$ 和 $(i, j+1)$，现在走到 $(i,j+2)$，然后我们还能自由地决定走到 $(i,j+2)$ 这个方格的时候，第 $i$ 行是否反转吗？**显然不行！** 因为这可能和前两个方格所枚举的“第 $i$ 行是否反转”相冲突，但这一行要么反转，要么不反转，这是 Alice 需要提前决定好的，不能在 Bob 走一半时临时反悔。

因此，我们在状态转移时需要更多的信息，来**描述当前行或列的反转情况**。

于是我们加两维：用 $dp_{i,j,k,x,y}$ 来表示 Bob 走到 $(i,j)$，使得当前栈的大小为 $k$ ，并且第 $i$ 行的反转情况为 $x$，第 $j$ 列的反转情况为 $y$（$0\le x,y\le 1$，$0$ 和 $1$ 分别表示不反转和反转），最少需要花费的金币数。

这样设计状态就没问题了，无后效性是很容易验证的，因为整个行动过程中，所在方格的行列编号都是单调不降的，不可能出现类似“离开某一行后又绕回来重新决策”的情况。在状态转移时，我们只需在 **第一次进入** 某一行或某一列时枚举这一行/列的决策，再在每一步移动时直接视情况继承 $x$ 和 $y$ 的状态，就能够规避刚才决策冲突的问题。

理解了原理之后，我们来具体看一组转移方程（其中 ```upd``` 函数的功能是尝试更新最小值，细节详见代码）：

```cpp
if (x ^ y)
    map[i][j] = (map[i][j] == 'L' ? 'R' : 'L'); //根据当前行列是否反转，确定 map[i][j]

if (map[i][j] == 'L' && k >= 1)
{
    upd(dp[i][j][k][x][y], dp[i][j - 1][k - 1][x][0] + y * b[j]);
    upd(dp[i][j][k][x][y], dp[i][j - 1][k - 1][x][1] + y * b[j]);
}
```

> $dp_{i,j,k,x,y}$ 表示 Bob 走到 $(i,j)$，使得当前栈的大小为 $k$ ，并且第 $i$ 行的反转情况为 $x$，第 $j$ 列的反转情况为 $y$（$0\le x,y\le 1$，$0$ 和 $1$ 分别表示不反转和反转），最少需要花费的金币数。

从 $(i, j-1)$ 这个方格移动到 $(i,j)$ 这个方格，为了避免之前分析过的决策冲突，**必须保证新状态第 $\bm{i}$ 行的反转情况直接继承原状态**。然而，由于我们离开了第 $j-1$ 列（显然也永远不会再返回去了），所以无需保证列的反转情况和原状态一致。而且由于我们是第一次进入第 $j$ 列，所以可以任意枚举第 $j$ 列的反转情况。

其它转移方程同理。至此，$O(T\cdot n^3)$ 地解决问题。（视 $n,m$ 同阶）

---


### 代码

```cpp
#include <bits/stdc++.h>
#define int long long 
#define map my_map
using namespace std;

int n, m;
string map[105];

int dp[105][105][205][2][2];
int a[105], b[105];

char rev(char brac)
{
	return brac == 'R' ? 'L' : 'R';
}

void upd(int &var, int val)
{
	var = min(var, val);
	return;
}

void solve()
{
	cin >> n >> m;
	
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	
	for (int i = 1; i <= m; i++)
		cin >> b[i];
	
	for (int i = 1; i <= n; i++)
	{
		cin >> map[i];
		map[i] = '0' + map[i];
	}
	
	const int inf = 1e10;
	
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= m; j++)
			for (int k = 0; k <= n + m; k++)
				for (int x = 0; x < 2; x++)
					for (int y = 0; y < 2; y++)
						dp[i][j][k][x][y] = inf;
	
	for (int x = 0; x < 2; x++)
		for (int y = 0; y < 2; y++)
			dp[0][1][0][x][y] = dp[1][0][0][x][y] = x * a[1] + y * b[1];
	
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (map[i][j] == 'X')
            {
                continue;
            }
				
			for (int k = 0; k <= i + j - 1; k++)
			{
				for (int x = 0; x < 2; x++)
				{
					if (x)
						map[i][j] = rev(map[i][j]);
						
					for (int y = 0; y < 2; y++)
					{
						if (y)
							map[i][j] = rev(map[i][j]);
							
						if (map[i][j] == 'L' && k >= 1)
						{
							upd(dp[i][j][k][x][y], dp[i][j - 1][k - 1][x][0] + y * b[j]);
							upd(dp[i][j][k][x][y], dp[i][j - 1][k - 1][x][1] + y * b[j]);
								
							upd(dp[i][j][k][x][y], dp[i - 1][j][k - 1][0][y] + x * a[i]);
							upd(dp[i][j][k][x][y], dp[i - 1][j][k - 1][1][y] + x * a[i]);
						}
						
						if (map[i][j] == 'R')
						{
							upd(dp[i][j][k][x][y], dp[i][j - 1][k + 1][x][0] + y * b[j]);
							upd(dp[i][j][k][x][y], dp[i][j - 1][k + 1][x][1] + y * b[j]);
								
							upd(dp[i][j][k][x][y], dp[i - 1][j][k + 1][0][y] + x * a[i]);
							upd(dp[i][j][k][x][y], dp[i - 1][j][k + 1][1][y] + x * a[i]);
						}
						
						if (y)
							map[i][j] = rev(map[i][j]);
					}
					
					if (x)
						map[i][j] = rev(map[i][j]);
				}
			}
		}
	}
	
	int ans = inf;
	
	for (int x = 0; x < 2; x++)
		for (int y = 0; y < 2; y++)
			ans = min(ans, dp[n][m][0][x][y]);
	
	cout << (ans == inf ? (-1) : ans) << '\n';
	return;
}

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0); 
	
	int _;
	cin >> _;
	while (_--)
	{
		solve();
	}
	
	return 0;
}
```

---

## 作者：The_foolishest_OIer (赞：0)

这是什么奶龙题？

发现数据范围小，直接考虑 dp，又发现一个格子地状态只与这个格子行、列是否反转有关。

记 $f_{i,j,k,p,q}$ 表示位于 $(i,j)$ 地格子当前左括号数量减去右括号数量为 $k$，$p=1$ 表示行反转，$q=1$ 表示列反转，反转后记 $x$ 值为，若当前格子为 $\texttt{(}$ 值为 $1$，否则为 $-1$，记 $y$ 值为反转所需要的代价。

从 $(i-1,j)$ 转移，有 $f_{i,j,k,p,q} \gets \min(f_{i-1,j,k-x,0,q},f_{i-1,j,k-x,1,q}) + y$。

从 $(i,j-1)$ 转移，有 $f_{i,j,k,p,q} \gets \min(f_{i,j-1,k-x,p,0},f_{i,j-1,k-x,p,1}) + y$。

复杂度 $O(n^3)$，视 $n$ 和 $m$ 同阶。

```cpp
void solve(){
	cin >> n >> m;
	int sum = 0;
	for (int i = 1 ; i <= n ; i++) cin >> a[i],sum += a[i];
	for (int i = 1 ; i <= m ; i++) cin >> b[i],sum += b[i];
	for (int i = 1 ; i <= n ; i++)
		for (int j = 1 ; j <= m ; j++)
			cin >> mp[i][j];
	if (mp[1][1] == 'X') return cout << "-1\n",void();
	if (mp[1][1] == 'L') dp[1][1][1][0][0] = 0,dp[1][1][1][1][1] = a[1] + b[1],dp[1][1][1][1][0] = dp[1][1][1][0][1] = inf;
	if (mp[1][1] == 'R') dp[1][1][1][0][0] = dp[1][1][1][1][1] = inf,dp[1][1][1][1][0] = a[1],dp[1][1][1][0][1] = b[1];
	int mx = (n + m - 1) / 2;
	for (int i = 1 ; i <= n ; i++){
		for (int j = 1 ; j <= m ; j++){
			for (int k = 0 ; k <= min(i + j - 1,mx) ; k++){
				for (int p = 0 ; p < 2 ; p++){
					for (int q = 0 ; q < 2 ; q++){
						if (i != 1 || j != 1 || k != 1) dp[i][j][k][p][q] = inf; 
						if ((i == 1 && j == 1) || mp[i][j] == 'X') continue;
						int xx = ((p + q) & 1 ? -1 : 1);
						int yy = (mp[i][j] == 'L' ? 1 : -1);
						int real = xx * yy,lk = k - real;
						if (lk > min(i + j - 2,mx) || lk < 0) continue;
						int ex1 = (p ? a[i] : 0),ex2 = (q ? b[j] : 0); 
						if (i > 1) dp[i][j][k][p][q] = min(dp[i][j][k][p][q],min(dp[i - 1][j][lk][0][q],dp[i - 1][j][lk][1][q]) + ex1);
						if (j > 1) dp[i][j][k][p][q] = min(dp[i][j][k][p][q],min(dp[i][j - 1][lk][p][0],dp[i][j - 1][lk][p][1]) + ex2);
					}
				}
			}
		}
	}
	int ans = min(min(dp[n][m][0][0][0],dp[n][m][0][1][1]),min(dp[n][m][0][0][1],dp[n][m][0][1][0]));
	cout << (ans > sum ? -1 : ans) << endl;
}
```

---

