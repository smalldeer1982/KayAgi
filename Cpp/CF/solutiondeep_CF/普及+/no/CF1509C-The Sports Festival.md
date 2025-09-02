# 题目信息

# The Sports Festival

## 题目描述

The student council is preparing for the relay race at the sports festival.

The council consists of $ n $ members. They will run one after the other in the race, the speed of member $ i $ is $ s_i $ . The discrepancy $ d_i $ of the $ i $ -th stage is the difference between the maximum and the minimum running speed among the first $ i $ members who ran. Formally, if $ a_i $ denotes the speed of the $ i $ -th member who participated in the race, then $ d_i = \max(a_1, a_2, \dots, a_i) - \min(a_1, a_2, \dots, a_i) $ .

You want to minimize the sum of the discrepancies $ d_1 + d_2 + \dots + d_n $ . To do this, you are allowed to change the order in which the members run. What is the minimum possible sum that can be achieved?

## 说明/提示

In the first test case, we may choose to make the third member run first, followed by the first member, and finally the second. Thus $ a_1 = 2 $ , $ a_2 = 3 $ , and $ a_3 = 1 $ . We have:

- $ d_1 = \max(2) - \min(2) = 2 - 2 = 0 $ .
- $ d_2 = \max(2, 3) - \min(2, 3) = 3 - 2 = 1 $ .
- $ d_3 = \max(2, 3, 1) - \min(2, 3, 1) = 3 - 1 = 2 $ .

The resulting sum is $ d_1 + d_2 + d_3 = 0 + 1 + 2 = 3 $ . It can be shown that it is impossible to achieve a smaller value.

In the second test case, the only possible rearrangement gives $ d_1 = 0 $ , so the minimum possible result is $ 0 $ .

## 样例 #1

### 输入

```
3
3 1 2```

### 输出

```
3```

## 样例 #2

### 输入

```
1
5```

### 输出

```
0```

## 样例 #3

### 输入

```
6
1 6 3 3 6 3```

### 输出

```
11```

## 样例 #4

### 输入

```
6
104 943872923 6589 889921234 1000000000 69```

### 输出

```
2833800505```

# AI分析结果

### 题目内容中文重写
# 体育节

## 题目描述
学生会正在为体育节的接力赛做准备。

学生会由 $n$ 名成员组成。他们将在比赛中依次跑步，成员 $i$ 的速度是 $s_i$。第 $i$ 阶段的差异值 $d_i$ 是前 $i$ 名跑步成员中最大跑步速度和最小跑步速度的差值。形式上，如果 $a_i$ 表示第 $i$ 名参赛成员的速度，那么 $d_i = \max(a_1, a_2, \dots, a_i) - \min(a_1, a_2, \dots, a_i)$。

你希望最小化差异值的总和 $d_1 + d_2 + \dots + d_n$。为此，你可以改变成员跑步的顺序。能够达到的最小总和是多少？

## 说明/提示
在第一个测试用例中，我们可以选择让第三名成员先跑，接着是第一名成员，最后是第二名成员。因此 $a_1 = 2$，$a_2 = 3$，$a_3 = 1$。我们有：
- $d_1 = \max(2) - \min(2) = 2 - 2 = 0$。
- $d_2 = \max(2, 3) - \min(2, 3) = 3 - 2 = 1$。
- $d_3 = \max(2, 3, 1) - \min(2, 3, 1) = 3 - 1 = 2$。

得到的总和是 $d_1 + d_2 + d_3 = 0 + 1 + 2 = 3$。可以证明不可能达到更小的值。

在第二个测试用例中，唯一可能的排列得到 $d_1 = 0$，所以最小可能的结果是 $0$。

## 样例 #1
### 输入
```
3
3 1 2
```
### 输出
```
3
```

## 样例 #2
### 输入
```
1
5
```
### 输出
```
0
```

## 样例 #3
### 输入
```
6
1 6 3 3 6 3
```
### 输出
```
11
```

## 样例 #4
### 输入
```
6
104 943872923 6589 889921234 1000000000 69
```
### 输出
```
2833800505
```

### 算法分类
动态规划

### 综合分析与结论
这些题解的核心思路都是先对数组进行排序，然后利用区间动态规划来解决问题。通过证明每次放置的数应该是当前未放置数中的最大值或最小值，从而得出前 $i$ 个数在排序后的数组中是连续段，进而设计出状态 $dp_{i,j}$ 表示前 $j - i + 1$ 个数分别放 $a_i, a_{i + 1}, \dots, a_{j - 1}, a_j$ 时最小的 $\sum\limits_{k = 1}^{j - i + 1}d_k$，状态转移方程为 $dp_{i,j}=\min(dp_{i + 1,j}, dp_{i,j - 1}) + a_j - a_i$。

### 所选题解
- **Cutest_Junior（5星）**
    - **关键亮点**：思路清晰，先通过分析得出要使 $\sum\limits_{i = 1}^{n - 1} d_i$ 最小，应把 $a_{max}$ 或 $a_{min}$ 放在最后面，并给出了证明。然后根据此结论推出前 $i$ 个数在排序后的数组中是连续段，进而设计出区间动态规划的状态和转移方程。代码简洁明了，注释较少但逻辑清晰。
    - **个人心得**：无
- **lsz_（4星）**
    - **关键亮点**：同样详细地证明了每次放置的数应该是当前未放置数中的最大值或最小值，思路清晰。代码实现规范，有一定的注释，易于理解。
    - **个人心得**：无
- **jasonliujiahua（4星）**
    - **关键亮点**：对解题步骤进行了详细的分析，包括贪心解释、排序的必要性以及区间动态规划的决策过程，思路清晰。代码结构清晰，有函数封装，提高了代码的可读性。
    - **个人心得**：无

### 重点代码
#### Cutest_Junior 的代码
```cpp
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;

const int N = 2005;

int a[N];

ll dp[N][N];

void solve() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    sort(a + 1, a + n + 1);
    for (int k = 1; k <= n; ++k) {
        for (int l = 1; l <= n; ++l) {
            int r = l + k - 1;
            if (r > n) {
                continue;
            }
            dp[l][r] = a[r] - a[l] + min(dp[l][r - 1], dp[l + 1][r]);
        }
    }
    printf("%lld\n", dp[1][n]);
}

int main() {
    solve();
}
```
**核心实现思想**：先读取输入的数组并排序，然后通过两层循环枚举区间长度和左端点，根据状态转移方程 $dp_{l,r} = a[r] - a[l] + \min(dp[l][r - 1], dp[l + 1][r])$ 计算 $dp$ 值，最后输出 $dp[1][n]$。

#### lsz_ 的代码
```cpp
#include<bits/stdc++.h>
#define LL long long
#define N 2010
using namespace std;
int n;
int a[N];
LL f[N][N];
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)    cin>>a[i];
    sort(a+1,a+n+1);
    for(int l=2;l<=n;l++)
    {
        for(int i=1;i+l-1<=n;i++)
        {
            int j=i+l-1;
            f[i][j]=min(f[i][j-1],f[i+1][j])+a[j]-a[i];
        }
    }
    cout<<f[1][n];
    return 0;
}
```
**核心实现思想**：读取输入的数组并排序，通过两层循环枚举区间长度和左端点，根据状态转移方程 $f_{i,j}=\min(f_{i,j - 1}, f_{i + 1,j}) + a[j] - a[i]$ 计算 $f$ 值，最后输出 $f[1][n]$。

#### jasonliujiahua 的代码
```c++
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=2010;
ll n,a[maxn],dp[maxn][maxn];
void init()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);
}
void DP()
{
    for(int w=1;w<n;w++)
        for(int i=1,j=i+w;j<=n;i++,j++)
            dp[i][j]=min(dp[i+1][j],dp[i][j-1])+a[j]-a[i];
}
int main()
{
    init();
    DP();
    cout<<dp[1][n];
    return 0;
}
```
**核心实现思想**：通过 `init` 函数读取输入的数组并排序，`DP` 函数通过两层循环枚举区间长度和左端点，根据状态转移方程 $dp_{i,j}=\min(dp_{i + 1,j}, dp_{i,j - 1}) + a[j] - a[i]$ 计算 $dp$ 值，最后在 `main` 函数中调用这两个函数并输出 $dp[1][n]$。

### 最优关键思路或技巧
- **贪心思想**：通过证明得出每次放置的数应该是当前未放置数中的最大值或最小值，从而简化问题。
- **区间动态规划**：根据贪心结论，设计出区间动态规划的状态和转移方程，将问题转化为区间问题进行求解。

### 拓展思路
同类型题或类似算法套路：
- 涉及序列重排求最值的问题，可先考虑贪心策略，再结合动态规划求解。
- 对于一些需要枚举所有可能排列的问题，若能发现某些特殊性质（如连续段等），可使用区间动态规划进行优化。

### 推荐题目
- [P1880 [NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880)
- [P4170 [CQOI2007] 涂色](https://www.luogu.com.cn/problem/P4170)
- [P1040 [NOIP2003 提高组] 加分二叉树](https://www.luogu.com.cn/problem/P1040)

### 个人心得摘录与总结
- **Moon_Goddy**：一开始尝试贪心算法，结果第五个测试点 WA 了，发现每一步的最优并不一定答案最优，从而想到用区间 $dp$ 解决问题。总结：在遇到贪心算法无法解决的问题时，要考虑动态规划等其他算法。 

---
处理用时：63.19秒