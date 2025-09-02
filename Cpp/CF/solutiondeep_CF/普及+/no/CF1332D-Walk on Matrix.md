# 题目信息

# Walk on Matrix

## 题目描述

Bob is playing a game named "Walk on Matrix".

In this game, player is given an $ n \times m $ matrix $ A=(a_{i,j}) $ , i.e. the element in the $ i $ -th row in the $ j $ -th column is $ a_{i,j} $ . Initially, player is located at position $ (1,1) $ with score $ a_{1,1} $ .

To reach the goal, position $ (n,m) $ , player can move right or down, i.e. move from $ (x,y) $ to $ (x,y+1) $ or $ (x+1,y) $ , as long as player is still on the matrix.

However, each move changes player's score to the [bitwise AND](https://en.wikipedia.org/wiki/Bitwise_operation#AND) of the current score and the value at the position he moves to.

Bob can't wait to find out the maximum score he can get using the tool he recently learnt — dynamic programming. Here is his algorithm for this problem.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1332D/f77be4abbc0e4a1768015d201a26d68f6c552a32.png)However, he suddenly realize that the algorithm above fails to output the maximum score for some matrix $ A $ . Thus, for any given non-negative integer $ k $ , he wants to find out an $ n \times m $ matrix $ A=(a_{i,j}) $ such that

- $ 1 \le n,m \le 500 $ (as Bob hates large matrix);
- $ 0 \le a_{i,j} \le 3 \cdot 10^5 $ for all $ 1 \le i\le n,1 \le j\le m $ (as Bob hates large numbers);
- the difference between the maximum score he can get and the output of his algorithm is exactly $ k $ .

It can be shown that for any given integer $ k $ such that $ 0 \le k \le 10^5 $ , there exists a matrix satisfying the above constraints.

Please help him with it!

## 说明/提示

In the first example, the maximum score Bob can achieve is $ 300000 $ , while the output of his algorithm is $ 300000 $ .

In the second example, the maximum score Bob can achieve is $ 7\&3\&3\&3\&7\&3=3 $ , while the output of his algorithm is $ 2 $ .

## 样例 #1

### 输入

```
0```

### 输出

```
1 1
300000```

## 样例 #2

### 输入

```
1```

### 输出

```
3 4
7 3 3 1
4 8 3 6
7 7 7 3```

# AI分析结果

### 题目中文重写
# 矩阵上的行走

## 题目描述
Bob正在玩一个名为“矩阵上的行走”的游戏。

在这个游戏中，玩家会得到一个 $n \times m$ 的矩阵 $A=(a_{i,j})$，即第 $i$ 行第 $j$ 列的元素是 $a_{i,j}$。初始时，玩家位于位置 $(1,1)$，分数为 $a_{1,1}$。

为了到达目标位置 $(n,m)$，玩家可以向右或向下移动，即从 $(x,y)$ 移动到 $(x,y + 1)$ 或 $(x + 1,y)$，只要玩家仍在矩阵内即可。

然而，每次移动都会将玩家的分数变为当前分数与移动到的位置的值的[按位与](https://en.wikipedia.org/wiki/Bitwise_operation#AND)结果。

Bob迫不及待地想用他最近学到的工具——动态规划来找出他能得到的最大分数。以下是他解决这个问题的算法。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1332D/f77be4abbc0e4a1768015d201a26d68f6c552a32.png)

然而，他突然意识到上述算法对于某些矩阵 $A$ 无法输出最大分数。因此，对于任何给定的非负整数 $k$，他想找出一个 $n \times m$ 的矩阵 $A=(a_{i,j})$，使得：
- $1 \le n,m \le 500$（因为Bob讨厌大矩阵）；
- 对于所有 $1 \le i\le n$，$1 \le j\le m$，$0 \le a_{i,j} \le 3 \cdot 10^5$（因为Bob讨厌大数字）；
- 他能得到的最大分数与他的算法输出的分数之差恰好为 $k$。

可以证明，对于任何给定的整数 $k$（$0 \le k \le 10^5$），都存在满足上述约束的矩阵。

请帮助他完成这个任务！

## 说明/提示
在第一个样例中，Bob能达到的最大分数是 $300000$，而他的算法输出的分数也是 $300000$。

在第二个样例中，Bob能达到的最大分数是 $7\&3\&3\&3\&7\&3 = 3$，而他的算法输出的分数是 $2$。

## 样例 #1
### 输入
```
0
```
### 输出
```
1 1
300000
```

## 样例 #2
### 输入
```
1
```
### 输出
```
3 4
7 3 3 1
4 8 3 6
7 7 7 3
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心目标都是构造一个满足条件的矩阵来 hack 掉 Bob 的动态规划算法，使得正确答案与该算法输出的答案之差恰好为 $k$。各题解的思路大多围绕利用按位与运算的特性，通过巧妙设计矩阵元素，让 Bob 的算法选择错误的路径，从而达到差值为 $k$ 的目的。

### 所选题解
- **CXY07（4星）**
    - **关键亮点**：思路清晰，详细分析了 Bob 算法的错误原因，通过具体的矩阵构造和逐步推导，说明了如何让 Bob 的算法输出 $0$，而正确答案为 $k$，差值恰好为 $k$。代码简洁易懂。
    - **个人心得**：作者提到一开始写的是 $2^{18}+k$，但当 $k$ 取最大值 $10^5$ 时，$2^{18}+10^5$ 超过了 $a_{i,j}$ 的限制 $3 \times 10^5$，提醒读者注意数据范围。
- **George1123（4星）**
    - **关键亮点**：从数据范围和样例中猜测到有通解，通过研究样例发现 Bob 代码的问题，构造了一个 $3\times 4$ 的矩阵，详细说明了 Bob 算法的输出和正确答案，差值为 $k$。代码简洁。
- **一扶苏一（4星）**
    - **关键亮点**：先分析了 Bob 的动态规划算法错误的原因是不满足最优子结构，然后通过具体的矩阵示例说明，接着构造了一个三行两列的矩阵，让 Bob 算法输出 $0$，正解输出 $k$。代码实现简单。

### 重点代码
#### CXY07
```cpp
#include<bits/stdc++.h>
using namespace std;

int k;

signed main () {
    scanf("%d",&k);
    printf("%d %d\n",2,3);
    printf("%d %d %d\n",(1 << 17) + k,(1 << 17),0);
    printf("%d %d %d\n",k,(1 << 17) + k,k);
    return 0;
}
```
**核心实现思想**：构造一个 $2\times 3$ 的矩阵，利用 $2^{17}$ 和 $k$ 的二进制位不相互影响的特点，让 Bob 的算法选择错误的路径，输出 $0$，而正确答案为 $k$。

#### George1123
```cpp
int main(){
    int k,t=1;
    scanf("%d",&k);
    while(t<=k) t<<=1;
    printf("3 4\n");
    printf("%d %d %d %d\n",t|k,k,k,0);
    printf("%d %d %d %d\n",t,0,k,0);
    printf("%d %d %d %d\n",t,t,t|k,k);
    return 0;
}
```
**核心实现思想**：找到一个 $t=2^c>k$，构造一个 $3\times 4$ 的矩阵，让 Bob 的算法输出 $0$，而真正的最小按位与路径答案为 $k$，差值为 $k$。

#### 一扶苏一
```cpp
#include <cmath>
#include <cstdio>
#include <iostream>

int main() {
    int k;
    std::cin >> k;
    int t = log2(k);
    puts("3 2");
    printf("%d %d\n", (1 << (t + 2)) - 1, k);
    printf("%d %d\n", 1 << (t + 1), (1 << (t + 2)) - 1);
    printf("0 %d\n", k);
    return 0;
}
```
**核心实现思想**：通过分析 Bob 算法的错误原因，构造一个三行两列的矩阵，在最高位上进行“诱导”，让 Bob 算法输出 $0$，正解输出 $k$。

### 关键思路或技巧
- 利用按位与运算的特性，大的数字与上某个特定数字不一定得到大的结果，通过巧妙设计矩阵元素，让 Bob 的算法选择错误的路径。
- 找到一个合适的二进制位，使得构造的矩阵元素满足题目要求，同时不超过数据范围。

### 拓展思路
同类型题可能会要求构造满足其他条件的矩阵或数据，关键在于分析给定算法的错误原因，利用相关运算的特性进行构造。类似算法套路包括利用贪心算法的错误、动态规划的不适用性等进行构造，以达到特定的差值或其他条件。

### 推荐题目
- [P1149 火柴棒等式](https://www.luogu.com.cn/problem/P1149)：考察构造和枚举的能力。
- [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)：涉及质数和构造的知识。
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：考察组合和构造的思想。

---
处理用时：55.85秒