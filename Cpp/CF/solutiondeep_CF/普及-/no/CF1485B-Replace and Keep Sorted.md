# 题目信息

# Replace and Keep Sorted

## 题目描述

Given a positive integer $ k $ , two arrays are called $ k $ -similar if:

- they are strictly increasing;
- they have the same length;
- all their elements are positive integers between $ 1 $ and $ k $ (inclusive);
- they differ in exactly one position.

You are given an integer $ k $ , a strictly increasing array $ a $ and $ q $ queries. For each query, you are given two integers $ l_i \leq r_i $ . Your task is to find how many arrays $ b $ exist, such that $ b $ is $ k $ -similar to array $ [a_{l_i},a_{l_i+1}\ldots,a_{r_i}] $ .

## 说明/提示

In the first example:

In the first query there are $ 4 $ arrays that are $ 5 $ -similar to $ [2,4] $ : $ [1,4],[3,4],[2,3],[2,5] $ .

In the second query there are $ 3 $ arrays that are $ 5 $ -similar to $ [4,5] $ : $ [1,5],[2,5],[3,5] $ .

## 样例 #1

### 输入

```
4 2 5
1 2 4 5
2 3
3 4```

### 输出

```
4
3```

## 样例 #2

### 输入

```
6 5 10
2 4 6 7 8 9
1 4
1 2
3 5
1 6
5 5```

### 输出

```
8
9
7
6
9```

# AI分析结果

### 题目内容
# 替换并保持有序

## 题目描述
给定一个正整数 $k$，若两个数组满足以下条件，则称它们是 $k$ 相似的：
- 它们严格递增；
- 它们长度相同；
- 它们所有元素都是介于 $1$ 到 $k$ 之间（包含 $1$ 和 $k$）的正整数；
- 它们仅在一个位置上不同。

给定一个整数 $k$、一个严格递增数组 $a$ 以及 $q$ 个查询。对于每个查询，给定两个整数 $l_i \leq r_i$。你的任务是找出存在多少个数组 $b$，使得 $b$ 与数组 $[a_{l_i},a_{l_i+1}\ldots,a_{r_i}]$ 是 $k$ 相似的。

## 说明/提示
在第一个示例中：
在第一个查询中，有 $4$ 个数组与 $[2,4]$ 是 $5$ 相似的：$[1,4],[3,4],[2,3],[2,5]$。
在第二个查询中，有 $3$ 个数组与 $[4,5]$ 是 $5$ 相似的：$[1,5],[2,5],[3,5]$。

## 样例 #1
### 输入
```
4 2 5
1 2 4 5
2 3
3 4
```
### 输出
```
4
3
```

## 样例 #2
### 输入
```
6 5 10
2 4 6 7 8 9
1 4
1 2
3 5
1 6
5 5
```
### 输出
```
8
9
7
6
9
```

### 算法分类
数学

### 题解综合分析与结论
这些题解的核心思路都是通过分析每个位置元素可替换的方案数来计算满足 $k$ -相似的数组数量。主要难点在于准确确定每个位置元素的取值范围，以保证替换后数组仍严格递增。多数题解通过分类讨论不同位置（两端和中间）元素的取值范围得出方案数，部分题解利用前缀和优化计算过程，但本质思路一致。

### 所选的题解
- **作者：11D_Beyonder (5星)**
  - **关键亮点**：思路清晰简洁，直接推导出总方案数的公式 $a_r - a_l - 2\times(r - l) + k - 1$，代码实现简洁高效。
  - **重点代码**：
```cpp
#include<iostream>
using namespace std;
const int N = 100005;
int n, q, k;
int a[N];
int main() {
    cin >> n >> q >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= q; i++) {
        int l, r;
        cin >> l >> r;
        cout << a[r] - a[l] - 2 * (r - l) + k - 1 << endl;
    }
    return 0;
}
```
  - **核心实现思想**：先读入数据，然后对于每个查询，直接根据推导出的公式计算并输出结果。

- **作者：Cutest_Junior (4星)**
  - **关键亮点**：从每个数对答案的贡献角度出发，分析不同取值范围的数对答案贡献为 $0$、$1$ 或 $2$，思路独特且容易理解。
  - **重点代码**：
```cpp
#include <cstdio>
using namespace std;
const int N = 1e5 + 5;
int arr[N];
void run() {
    int n, q, k;
    scanf("%d%d%d", &n, &q, k);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &arr[i]);
    }
    for (int i = 1; i <= q; ++i) {
        int l, r;
        scanf("%d%d", &l, &r);
        int ans = arr[l] + k - arr[r] - 1;
        ans += ((arr[r] - arr[l] + 1) - (r - l + 1)) * 2;
        printf("%d\n", ans);
    }
}
int main() {
    run();
}
```
  - **核心实现思想**：读入数据后，对于每次查询，根据不同取值范围数的贡献推导出的公式计算答案并输出。

### 最优关键思路或技巧
通过分类讨论确定每个位置元素的取值范围从而得出方案数，这是解决本题的关键。11D_Beyonder 的方法直接推导出简洁公式，在代码实现上最为简洁高效；Cutest_Junior 从数的贡献角度分析，有助于理解问题本质。

### 拓展
同类型题目通常围绕序列的特定性质和变换规则，计算满足条件的序列数量。类似算法套路是通过分析每个位置元素的变化对整体序列性质的影响，分类讨论得出方案数。

### 推荐题目
- [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)：通过分析每天的活动时间来判断是否满足特定条件，涉及简单的数学分析。
- [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)：根据给定的数分析其可由哪些连续自然数相加得到，需要一定的数学推导。
- [P1440 求m区间内的最小值](https://www.luogu.com.cn/problem/P1440)：通过分析区间内元素关系，计算满足条件的结果，与本题分析位置元素关系有相似之处。 

---
处理用时：62.82秒