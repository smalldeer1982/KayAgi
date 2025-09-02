# 题目信息

# Multicolored Markers

## 题目描述

There is an infinite board of square tiles. Initially all tiles are white.

Vova has a red marker and a blue marker. Red marker can color $ a $ tiles. Blue marker can color $ b $ tiles. If some tile isn't white then you can't use marker of any color on it. Each marker must be drained completely, so at the end there should be exactly $ a $ red tiles and exactly $ b $ blue tiles across the board.

Vova wants to color such a set of tiles that:

- they would form a rectangle, consisting of exactly $ a+b $ colored tiles;
- all tiles of at least one color would also form a rectangle.

Here are some examples of correct colorings:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1029F/4e60c629e360885141e5179d3d4cdaf35671b392.png)Here are some examples of incorrect colorings:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1029F/8bb11d3a5c5094b0326713ae6edbddbecf3531f0.png)Among all correct colorings Vova wants to choose the one with the minimal perimeter. What is the minimal perimeter Vova can obtain?

It is guaranteed that there exists at least one correct coloring.

## 说明/提示

The first four examples correspond to the first picture of the statement.

Note that for there exist multiple correct colorings for all of the examples.

In the first example you can also make a rectangle with sides $ 1 $ and $ 8 $ , though its perimeter will be $ 18 $ which is greater than $ 8 $ .

In the second example you can make the same resulting rectangle with sides $ 3 $ and $ 4 $ , but red tiles will form the rectangle with sides $ 1 $ and $ 3 $ and blue tiles will form the rectangle with sides $ 3 $ and $ 3 $ .

## 样例 #1

### 输入

```
4 4
```

### 输出

```
12
```

## 样例 #2

### 输入

```
3 9
```

### 输出

```
14
```

## 样例 #3

### 输入

```
9 3
```

### 输出

```
14
```

## 样例 #4

### 输入

```
3 6
```

### 输出

```
12
```

## 样例 #5

### 输入

```
506 2708
```

### 输出

```
3218
```

# AI分析结果



# 算法分类
枚举、数学因数分解

---

# 题解思路与算法分析

## 核心思路
1. **大矩形枚举**：从 $\sqrt{a+b}$ 向下枚举大矩形的宽度 $i$，此时对应高度为 $(a+b)/i$。由于周长随长宽差的减小而减小，优先枚举较大的宽度可快速找到最优解。
2. **颜色矩形检查**：对于每个 $i$，检查是否存在红色或蓝色矩形能嵌入大矩形。即判断是否存在 $j \leq i$ 且 $a/j \leq (a+b)/i$（红）或类似条件（蓝）。
3. **因数预处理**：预处理颜色块的所有因数，通过双指针技巧快速找到当前 $i$ 下最大的合法因数，时间复杂度优化至 $O(\sqrt{a})$。

## 解决难点
- **高效因数检查**：利用预处理与双指针避免重复遍历因数，解决大数因数分解的效率问题。
- **贪心剪枝**：从最大可能的宽度开始枚举，首个合法解即为最优，无需后续计算。

---

# 题解评分（≥4星）

## [Siyuan 题解] ⭐⭐⭐⭐⭐
- **亮点**：预处理因数+双指针优化，时间复杂度最优。代码简洁，逻辑清晰。
- **代码关键**：`solve` 函数中动态维护指针，快速判断合法解。

## [Bring 题解] ⭐⭐⭐⭐
- **亮点**：实时调整因数检查范围，减少无效遍历。代码高度优化，执行效率极高。
- **优化点**：通过 `min(f,i)` 动态缩小因数检查范围。

## [Xiao_mo 题解] ⭐⭐⭐⭐
- **亮点**：预处理红蓝颜色块因数，分离检查逻辑。枚举时直接访问预存因数，思路直观。

---

# 最优思路提炼

1. **逆向枚举宽度**：从 $\sqrt{a+b}$ 向下枚举大矩形宽，保证首个合法解周长最小。
2. **因数双指针法**：预处理颜色块因数后，用指针动态追踪最大合法因数，避免重复遍历。
3. **贪心剪枝**：找到首个解立即返回，无需后续枚举。

---

# 同类型题与套路

- **常见套路**：大数分解问题中预处理因数+贪心枚举。类似问题如寻找最接近的正方形、矩形覆盖优化等。
- **类似题目**：CF510D（因数分解+动态规划）、LeetCode 593（有效正方形验证）。

---

# 推荐题目
1. [CF510D - Fox And Jumping](https://codeforces.com/problemset/problem/510/D)  
   **关键点**：因数分解与动态规划结合。
2. [LeetCode 593 - Valid Square](https://leetcode.com/problems/valid-square/)  
   **关键点**：几何验证与数学因数思想。
3. [洛谷 P1072 - Hankson的趣味题](https://www.luogu.com.cn/problem/P1072)  
   **关键点**：大数因数分解与条件判断。

---

# 可视化设计

## 算法动画方案
- **网格绘制**：Canvas 绘制大矩形网格，动态高亮当前枚举的宽度 $i$ 及对应高度。
- **因数检查**：以闪烁效果显示当前检查的颜色块因数对 $(j, a/j)$，若合法则标记为绿色。
- **指针移动**：可视化双指针在预处理因数数组上的移动过程，颜色区分已检查与待检查区域。

## 复古像素风格
- **8-bit 调色板**：使用经典 FC 游戏的 16 色方案，如大矩形用深蓝边框，合法解显示为金色。
- **音效设计**：
  - **枚举步进**：短促“哔”声。
  - **合法解发现**：经典马里奥金币音效。
  - **错误提示**：低沉“嗡”声。

---

# 核心代码（Siyuan 题解）

```cpp
#include <cstdio>
#include <algorithm>
#include <vector>

long long solve(long long tot, long long a) {
    std::vector<int> f;
    for (int i = 1; 1LL * i * i <= a; ++i)
        if (a % i == 0) f.push_back(i);
    int p = (int)f.size() - 1;
    for (int i = sqrt(tot); i >= 1; --i) {
        if (tot % i) continue;
        while (f[p] > i) --p;
        if (a / f[p] <= tot / i) return 2LL * (i + tot / i);
    }
    return 1LL << 60;
}

int main() {
    long long n, m;
    scanf("%lld%lld", &n, &m);
    printf("%lld\n", std::min(solve(n + m, n), solve(n + m, m)));
    return 0;
}
```

**核心逻辑**：预处理因数后，逆序枚举大矩形宽，双指针快速定位最大合法因数。

---
处理用时：121.47秒