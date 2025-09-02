# 题目信息

# Ivan the Fool and the Probability Theory

## 题目描述

Recently Ivan the Fool decided to become smarter and study the probability theory. He thinks that he understands the subject fairly well, and so he began to behave like he already got PhD in that area.

To prove his skills, Ivan decided to demonstrate his friends a concept of random picture. A picture is a field of $ n $ rows and $ m $ columns, where each cell is either black or white. Ivan calls the picture random if for every cell it has at most one adjacent cell of the same color. Two cells are considered adjacent if they share a side.

Ivan's brothers spent some time trying to explain that it's not how the randomness usually works. Trying to convince Ivan, they want to count the number of different random (according to Ivan) pictures. Two pictures are considered different if at least one cell on those two picture is colored differently. Since the number of such pictures may be quite large, print it modulo $ 10^9 + 7 $ .

## 说明/提示

The picture below shows all possible random pictures of size $ 2 $ by $ 3 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1239A/79c5ab51966bd63fcda5df4992b30330daa2ccc2.png)

## 样例 #1

### 输入

```
2 3
```

### 输出

```
8
```

# AI分析结果

### 题目翻译
## 伊万傻瓜与概率论

### 题目描述
最近，傻瓜伊万决定变得更聪明些，于是开始学习概率论。他觉得自己已经相当了解这门学科了，便开始表现得好像已经拿到了该领域的博士学位一样。

为了证明自己的能力，伊万决定向朋友们展示“随机图片”的概念。一张图片是一个由 $n$ 行 $m$ 列组成的区域，每个单元格要么是黑色，要么是白色。伊万称一张图片是随机的，当且仅当对于每个单元格，与其相邻的单元格中至多只有一个与其颜色相同。如果两个单元格共用一条边，则称它们相邻。

伊万的兄弟们花了一些时间试图向他解释，这并不是通常意义上的随机。为了说服伊万，他们想计算出不同的（按照伊万的定义）随机图片的数量。如果两张图片中至少有一个单元格的颜色不同，则认为这两张图片不同。由于这样的图片数量可能非常大，因此将结果对 $10^9 + 7$ 取模后输出。

### 说明/提示
下图展示了所有可能的 $2$ 行 $3$ 列的随机图片。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1239A/79c5ab51966bd63fcda5df4992b30330daa2ccc2.png)

### 样例 #1
#### 输入
```
2 3
```
#### 输出
```
8
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路大多围绕发现题目中隐藏的斐波那契数列规律来求解。不同题解的思路和实现方式各有不同：
- **找规律类**：通过观察一行或一列的涂色情况，发现其满足斐波那契数列规律，再结合多行多列的特殊情况（如第一行有相邻同色和无相邻同色）推导出最终答案公式，如 `zty111`、`寒鸽儿`、`MattL` 等题解。
- **动态规划类**：定义状态数组，根据状态转移方程进行递推计算，最后得出结果，如 `Meatherm` 的题解。
- **模拟与容斥类**：先模拟计算横竖两种情况，再通过容斥原理减去重复计算的部分，如 `Froggy` 的题解。

各题解的难点主要在于发现题目中的规律以及处理重复计算的情况。

### 所选题解
- **zty111（5星）**
    - **关键亮点**：思路简洁明了，直接指出题目是之前试题的加强版，快速抓住问题核心，通过固定第一个格子颜色，分情况讨论得出答案公式，代码实现简单易懂。
- **Meatherm（4星）**
    - **关键亮点**：详细阐述了动态规划的思路，通过发现确定第一行和第一列状态后整个矩阵状态确定的性质，巧妙地将问题转化为 DP 问题，状态转移方程推导清晰。
- **寒鸽儿（4星）**
    - **关键亮点**：先对数据范围进行分析，合理猜测横纵坐标统计独立，然后通过证明相关结论，将问题转化为列的排列划分，进而得出与斐波那契数列的关系，逻辑严谨。

### 重点代码
#### zty111 的题解
```cpp
#include <cstdio>
#include <iostream>
using namespace std;
const int N = 100010;
const int mod = 1e9 + 7;
long long f[N];
int main() {
    int n, m;
    scanf("%d %d", &m, &n);
    f[1] = f[0] = 1;
    for(int i = 2; i <= max(n, m); i++)
        f[i] = (f[i-1] + f[i-2]) % mod;
    long long ans = ((f[n] + f[m] - 1) % mod) * 2 % mod;
    printf("%lld\n", ans);
    return 0;
}
```
**核心实现思想**：先计算斐波那契数列，再根据推导出的公式 `(F[n] + F[m] - 1) * 2` 计算最终答案。

#### Meatherm 的题解
```cpp
# include <bits/stdc++.h>
# define int long long
# define rr register
const int N=100010,MOD=1e9+7;
int f[N][2][2];
signed main(void){
    int n,m;
    scanf("%I64d%I64d",&n,&m);
    f[1][1][0]=1;
    f[1][0][0]=1;
    for(rr int i=2;i<=std::max(n,m);++i){
        f[i][0][1]+=f[i-1][0][0];
        f[i][0][1]%=MOD;
        f[i][0][0]+=f[i-1][1][1]+f[i-1][1][0];
        f[i][0][0]%=MOD;
        f[i][1][1]+=f[i-1][1][0];
        f[i][1][1]%=MOD;
        f[i][1][0]+=f[i-1][0][1]+f[i-1][0][0];
        f[i][1][1]%=MOD;
    }
    printf("%I64d",((f[n][0][0]+f[n][0][1]+f[n][1][0]+f[n][1][1]+(f[m][0][0]+f[m][0][1]+f[m][1][0]+f[m][1][1])-2)%MOD));
    return 0;
}
```
**核心实现思想**：定义状态数组 `f[i][0/1][0/1]` 表示前 $i$ 个格子中最后一个格子的颜色是黑色/白色，结尾是否连续放置了两个相同颜色的格子，通过状态转移方程递推计算，最后得出答案。

#### 寒鸽儿的题解
```cpp
#include <iostream>
using namespace std;
const int mode = 1e9+7, maxn = 123456;
int f[maxn];
int main() {
    ios::sync_with_stdio(false);
    int n, m, mx;
    cin >> n >> m;
    mx = max(n, m);
    f[0] = f[1] = 1;
    for(int i = 2; i <= mx; ++i) f[i] = (f[i-1] + f[i-2]) % mode;
    cout << ((f[n] + f[m] - 1) % mode) * 2 % mode << endl;
    return 0;
}
```
**核心实现思想**：先证明横纵坐标统计独立的相关结论，将问题转化为列的排列划分，计算斐波那契数列，再根据公式 `(f[n] + f[m] - 1) * 2` 计算答案。

### 关键思路或技巧
- **找规律**：通过观察一行或一列的涂色情况，发现其满足斐波那契数列规律，这是解决本题的关键。
- **分类讨论**：分第一行有相邻同色和无相邻同色两种情况进行讨论，分别计算方案数，最后得出最终答案。
- **状态压缩**：在动态规划中，通过合理定义状态数组，将问题转化为可递推的形式，减少计算量。

### 拓展思路
同类型题目可能会在图形形状、颜色种类、相邻条件等方面进行变化，但解题的关键仍然是寻找规律和合理分类讨论。例如，可能会将矩形网格变为三角形网格，或者增加颜色种类等。

### 推荐题目
- [P1962 斐波那契数列](https://www.luogu.com.cn/problem/P1962)：直接考察斐波那契数列的计算。
- [P1044 栈](https://www.luogu.com.cn/problem/P1044)：需要通过找规律和递推来解决问题。
- [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)：涉及递推和状态转移的思想。

### 个人心得摘录与总结
- **Froggy**：提到在考场上通过在演草纸上乱画发现相邻同色的格子要么都是横着的，要么都是竖着的规律，然后进行分开计算。这表明在考试中，通过手动模拟和观察可以帮助发现问题的规律，从而找到解题思路。
- **big_news**：采用“数论不会先打表”的方法，通过打出一行的答案表，发现其满足斐波那契数列规律。这说明在遇到难题时，通过列举小数据并寻找规律是一种有效的解题策略。

---
处理用时：60.37秒