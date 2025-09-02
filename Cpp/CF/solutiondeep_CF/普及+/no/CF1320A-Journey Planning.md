# 题目信息

# Journey Planning

## 题目描述

Tanya wants to go on a journey across the cities of Berland. There are $ n $ cities situated along the main railroad line of Berland, and these cities are numbered from $ 1 $ to $ n $ .

Tanya plans her journey as follows. First of all, she will choose some city $ c_1 $ to start her journey. She will visit it, and after that go to some other city $ c_2 > c_1 $ , then to some other city $ c_3 > c_2 $ , and so on, until she chooses to end her journey in some city $ c_k > c_{k - 1} $ . So, the sequence of visited cities $ [c_1, c_2, \dots, c_k] $ should be strictly increasing.

There are some additional constraints on the sequence of cities Tanya visits. Each city $ i $ has a beauty value $ b_i $ associated with it. If there is only one city in Tanya's journey, these beauty values imply no additional constraints. But if there are multiple cities in the sequence, then for any pair of adjacent cities $ c_i $ and $ c_{i + 1} $ , the condition $ c_{i + 1} - c_i = b_{c_{i + 1}} - b_{c_i} $ must hold.

For example, if $ n = 8 $ and $ b = [3, 4, 4, 6, 6, 7, 8, 9] $ , there are several three possible ways to plan a journey:

- $ c = [1, 2, 4] $ ;
- $ c = [3, 5, 6, 8] $ ;
- $ c = [7] $ (a journey consisting of one city is also valid).

There are some additional ways to plan a journey that are not listed above.

Tanya wants her journey to be as beautiful as possible. The beauty value of the whole journey is the sum of beauty values over all visited cities. Can you help her to choose the optimal plan, that is, to maximize the beauty value of the journey?

## 说明/提示

The optimal journey plan in the first example is $ c = [2, 4, 5] $ .

The optimal journey plan in the second example is $ c = [1] $ .

The optimal journey plan in the third example is $ c = [3, 6] $ .

## 样例 #1

### 输入

```
6
10 7 1 9 10 15```

### 输出

```
26```

## 样例 #2

### 输入

```
1
400000```

### 输出

```
400000```

## 样例 #3

### 输入

```
7
8 9 26 11 12 29 14```

### 输出

```
55```

# AI分析结果

### 题目中文重写
# 旅行规划

## 题目描述
Tanya 想要开启一场穿越 Berland 城市的旅行。Berland 的主要铁路沿线分布着 $n$ 个城市，这些城市从 $1$ 到 $n$ 编号。

Tanya 这样规划她的旅行：首先，她会选择某个城市 $c_1$ 作为旅行的起点。她会游览这个城市，之后前往另一个城市 $c_2 > c_1$，接着再去另一个城市 $c_3 > c_2$，以此类推，直到她选择在某个城市 $c_k > c_{k - 1}$ 结束旅行。所以，她访问的城市序列 $[c_1, c_2, \dots, c_k]$ 应该是严格递增的。

对于 Tanya 访问的城市序列还有一些额外的限制条件。每个城市 $i$ 都有一个与之关联的美丽值 $b_i$。如果 Tanya 的旅行中只有一个城市，那么这些美丽值不会带来额外的限制。但如果序列中有多个城市，那么对于任意一对相邻的城市 $c_i$ 和 $c_{i + 1}$，必须满足条件 $c_{i + 1} - c_i = b_{c_{i + 1}} - b_{c_i}$。

例如，如果 $n = 8$ 且 $b = [3, 4, 4, 6, 6, 7, 8, 9]$，有以下几种可能的旅行规划方式：
- $c = [1, 2, 4]$；
- $c = [3, 5, 6, 8]$；
- $c = [7]$（仅包含一个城市的旅行也是有效的）。

还有一些未列出的其他旅行规划方式。

Tanya 希望她的旅行尽可能美丽。整个旅行的美丽值是所有访问城市的美丽值之和。你能帮她选择最优的旅行规划，即最大化旅行的美丽值吗？

## 说明/提示
第一个样例中的最优旅行规划是 $c = [2, 4, 5]$。
第二个样例中的最优旅行规划是 $c = [1]$。
第三个样例中的最优旅行规划是 $c = [3, 6]$。

## 样例 #1
### 输入
```
6
10 7 1 9 10 15
```
### 输出
```
26
```

## 样例 #2
### 输入
```
1
400000
```
### 输出
```
400000
```

## 样例 #3
### 输入
```
7
8 9 26 11 12 29 14
```
### 输出
```
55
```

### 算法分类
动态规划

### 综合分析与结论
这些题解的核心思路都是对给定条件 $c_{i + 1} - c_i = b_{c_{i + 1}} - b_{c_i}$ 进行移项，得到 $b_{c_{i + 1}} - c_{i + 1} = b_{c_i} - c_i$，即满足条件的城市其美丽值与下标之差相等。基于此，不同题解采用了不同的数据结构来存储和计算相同差值的美丽值之和，最后取最大值作为结果。

主要的算法要点在于对等式的变形和对相同差值的处理，解决的难点是差值可能为负数，不同题解采用了加偏移量或使用 `map` 来解决。

### 所选题解
- **dblark（5星）**
    - **关键亮点**：思路清晰，代码简洁，直接用数组记录相同差值的答案，通过加 $n$ 处理差值为负的情况。
    - **重点代码**：
```cpp
#include <cstdio>
#include <algorithm>

int n;
int a[200005];
long long ans;
long long f[600005];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= n; ++i) ans = std::max(ans, f[a[i] - i + n] += a[i]);
    printf("%lld\n", ans);
    return 0;
}
```
核心实现思想：先读取城市数量和每个城市的美丽值，然后遍历每个城市，计算其美丽值与下标的差值并加上偏移量 $n$，将该城市的美丽值累加到对应差值的数组位置上，同时更新最大美丽值。

- **xht（4星）**
    - **关键亮点**：使用 `map` 处理差值，代码简洁，避免了手动处理差值为负的问题。
    - **重点代码**：
```cpp
const int N = 2e5 + 7;
int n;
ll a[N], ans;

int main() {
    rd(n), rda(a, n);
    map<ll, ll> f;
    for (int i = 1; i <= n; i++) f[a[i]-i] += a[i];
    for (auto o : f) ans = max(ans, o.se);
    print(ans);
    return 0;
}
```
核心实现思想：读取城市数量和美丽值后，使用 `map` 存储差值及其对应的美丽值之和，遍历每个城市更新 `map`，最后遍历 `map` 找出最大的美丽值之和。

- **Reanap（4星）**
    - **关键亮点**：使用动态规划思想，定义 $dp_i$ 为选择第 $i$ 个位置的最大值，通过维护同种差值的最大 $dp$ 值实现 $O(1)$ 转移。
    - **重点代码**：
```cpp
#include <map>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 2e5 + 5;
map <int , LL> M;
LL dp[MAXN] , n , b[MAXN] , ans;
int main() {
    scanf("%lld" , &n);
    for (int i = 1; i <= n; ++i) scanf("%lld" , &b[i]);
    for (int i = 1; i <= n; ++i) {
        dp[i] = M[b[i] - i] + b[i];
        M[b[i] - i] = max(M[b[i] - i] , dp[i]);
        ans = max(ans , dp[i]);
    }
    printf("%lld" , ans);
    return 0;
}
```
核心实现思想：读取城市数量和美丽值后，遍历每个城市，计算 $dp_i$ 为同种差值的最大 $dp$ 值加上当前城市的美丽值，同时更新同种差值的最大 $dp$ 值和最终答案。

### 最优关键思路或技巧
- **等式变形**：将条件 $c_{i + 1} - c_i = b_{c_{i + 1}} - b_{c_i}$ 变形为 $b_{c_{i + 1}} - c_{i + 1} = b_{c_i} - c_i$，从而将问题转化为对相同差值的处理。
- **处理负数差值**：可以通过加偏移量（如加 $n$ 或一个较大的常数）或使用 `map` 来处理差值可能为负的情况。

### 拓展思路
同类型题可能会有不同的条件限制和数据范围，但核心思路可能都是对给定条件进行变形，然后通过某种数据结构来存储和计算相关信息。类似的算法套路包括对等式进行变形以简化问题，以及使用合适的数据结构处理特殊情况（如负数）。

### 推荐洛谷题目
- P1048 [采药](https://www.luogu.com.cn/problem/P1048)：经典的 0 - 1 背包问题，考察动态规划思想。
- P1616 [疯狂的采药](https://www.luogu.com.cn/problem/P1616)：完全背包问题，也是动态规划的典型应用。
- P1802 [5 倍经验日](https://www.luogu.com.cn/problem/P1802)：同样是动态规划问题，通过状态转移方程求解最优解。

### 个人心得摘录与总结
- **流绪**：比赛时一直以为要写一个 $nlog(n)$ 的算法，甚至怀疑误入了 div1，第二天才发现是自己想复杂了。总结是要仔细读题，不要被题目表面的复杂所迷惑。
- **dead_X**：赛时想出做法用了 9 分钟，比赛 A 掉用了 21 分钟，建议难度为橙/黄。说明在比赛中要合理分配时间，提高解题效率。 

---
处理用时：57.18秒