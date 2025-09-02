# 题目信息

# Riverside Curio

## 题目描述

Arkady decides to observe a river for $ n $ consecutive days. The river's water level on each day is equal to some real value.

Arkady goes to the riverside each day and makes a mark on the side of the channel at the height of the water level, but if it coincides with a mark made before, no new mark is created. The water does not wash the marks away. Arkady writes down the number of marks strictly above the water level each day, on the $ i $ -th day this value is equal to $ m_{i} $ .

Define $ d_{i} $ as the number of marks strictly under the water level on the $ i $ -th day. You are to find out the minimum possible sum of $ d_{i} $ over all days. There are no marks on the channel before the first day.

## 说明/提示

In the first example, the following figure shows an optimal case.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF924C/ad72072688b34b2729139a36473993902a371313.png)Note that on day $ 3 $ , a new mark should be created because if not, there cannot be $ 3 $ marks above water on day $ 4 $ . The total number of marks underwater is $ 0+0+2+0+3+1=6 $ .

In the second example, the following figure shows an optimal case.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF924C/193fbf53ff0eac39a568b94979481249f6765c97.png)

## 样例 #1

### 输入

```
6
0 1 0 3 0 2
```

### 输出

```
6
```

## 样例 #2

### 输入

```
5
0 1 2 1 2
```

### 输出

```
1
```

## 样例 #3

### 输入

```
5
0 1 1 2 2
```

### 输出

```
0
```

# AI分析结果

### 题目内容
# 河畔奇事

## 题目描述
阿尔卡迪决定连续观察一条河流 $n$ 天。每天河流的水位都是某个实数值。

阿尔卡迪每天都会去河畔，并在河道边与水位齐平的高度做一个标记，但如果该水位与之前做过的标记重合，则不再创建新标记。水不会冲走这些标记。阿尔卡迪记录下每天水位严格上方的标记数量，在第 $i$ 天，这个值等于 $m_{i}$ 。

定义 $d_{i}$ 为第 $i$ 天水位严格下方的标记数量。你需要找出所有天数中 $d_{i}$ 的最小可能总和。在第一天之前，河道上没有标记。

## 说明/提示
在第一个示例中，下图展示了一种最优情况。

![示例1](https://cdn.luogu.com.cn/upload/vjudge_pic/CF924C/ad72072688b34b2729139a36473993902a371313.png)
注意，在第 3 天，应该创建一个新标记，因为如果不这样做，第 4 天就不可能有 3 个标记在水位上方。水位下方标记的总数为 $0+0+2+0+3+1=6$ 。

在第二个示例中，下图展示了一种最优情况。

![示例2](https://cdn.luogu.com.cn/upload/vjudge_pic/CF924C/193fbf53ff0eac39a568b94979481249f6765c97.png)

## 样例 #1
### 输入
```
6
0 1 0 3 0 2
```
### 输出
```
6
```

## 样例 #2
### 输入
```
5
0 1 2 1 2
```
### 输出
```
1
```

## 样例 #3
### 输入
```
5
0 1 1 2 2
```
### 输出
```
0
```

### 算法分类
贪心

### 题解综合分析与结论
- **思路**：各题解都基于贪心思想，即尽可能让标记重合来使总标记数最少，进而使水位以下标记数总和最小。
- **算法要点**：
    - **Wf_yjqd**：倒序维护第 $i$ 天可能的最少标记数 $f_i=\max(m_i,f_{i + 1}-1)$ ，再正序求前缀最大值更新 $f_i$ ，最后通过 $d_i = f_i - m_i$ 计算并累加水位以下标记数。
    - **XL4453**：用栈维护在当前限制下可重合的位置，根据当前位置的限制决定前一个位置是否入栈或弹出栈中元素，最后根据栈内情况计算答案。
    - **尹昱钦**：利用单调栈维护最长的 $(i - m[i])$ 上升后缀，以此求出每段区间重复的条数，进而统计答案。
    - **C20203030**：设 $t[i]$ 为 $i$ 时刻线的数量，根据 $t[i]\geq t[i - 1]$ ，$t[i]\geq m[i]$ ，$t[i]-1\leq t[i - 1]$ 这三个限制条件确定 $t[i]$ ，最后计算答案。
- **解决难点**：核心难点在于如何在满足每天水位上方标记数要求的前提下，合理安排标记重合情况以达到水位以下标记数总和最小。各题解通过不同方式解决，如维护单调栈、利用标记数限制条件等。

### 所选的题解
- **Wf_yjqd（5星）**
    - **关键亮点**：思路清晰易懂，代码简洁明了，直接利用贪心策略，通过倒序和正序两次遍历数组，简洁地实现了对最少标记数的维护和答案计算。
    - **个人心得**：提到题目翻译不友好，读题困难。
    - **重点代码核心实现思想**：先读入数据并将水位以上标记数总和从答案中减去，倒序遍历确定每天最少标记数，正序遍历更新最少标记数并累加到答案中，最后输出答案。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn = 2e5;
ll n, ans, a[maxn], f[maxn];
int main() {
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        ans -= a[i];
    }
    for (ll i = n; i >= 1; i--)
        f[i] = max(a[i], f[i + 1] - 1);
    for (ll i = 1; i <= n; i++) {
        f[i] = max(f[i], f[i - 1]);
        ans += f[i];
    }
    printf("%lld\n", ans);
    return 0;
}
```
- **C20203030（4星）**
    - **关键亮点**：通过数学推导得出标记数的限制条件，利用这些条件简洁地计算出每天的标记数，进而得出答案，逻辑严谨。
    - **重点代码核心实现思想**：先读入数据并根据前两个限制条件初始化每天的标记数，再从后往前根据第三个限制条件调整标记数，最后遍历计算水位以下标记数总和。
```cpp
#include <cstdio>
#include <iostream>
#define int long long
using namespace std;
const int M = 100005;
int read() {
    int x = 0, flag = 1; char c;
    while ((c = getchar()) < '0' || c > '9') if (c == '-') flag = -1;
    while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
    return x * flag;
}
int n, ans, m[M], t[M];
signed main() {
    n = read();
    for (int i = 1; i <= n; i++)
        t[i] = max(t[i - 1], (m[i] = read()) + 1);
    for (int i = n - 1; i >= 1; i--)
        if (t[i + 1] - 1 > t[i])
            t[i] = t[i + 1] - 1;
    for (int i = 1; i <= n; i++)
        ans += t[i] - m[i] - 1;
    printf("%lld\n", ans);
}
```

### 最优关键思路或技巧
通过贪心策略，利用标记数的单调不减性质以及每天水位上方标记数的限制，合理维护每天的最少标记数。如Wf_yjqd题解中通过两次遍历数组来维护最少标记数，C20203030题解中通过数学推导得出标记数限制条件并据此计算最少标记数。

### 可拓展思路
此类题目属于贪心策略在实际场景中的应用，类似套路是分析问题中的限制条件和可优化方向，利用贪心思想找到最优解。同类型题可关注一些资源分配、任务安排等场景下，在满足一定条件下求最值的问题。

### 洛谷推荐题目
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
- [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)
- [P2859 [USACO06DEC]Milk Patterns G](https://www.luogu.com.cn/problem/P2859)

---
处理用时：71.87秒