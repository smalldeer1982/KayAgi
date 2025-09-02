# 题目信息

# The Wall

## 题目描述

Iahub and his friend Floyd have started painting a wall. Iahub is painting the wall red and Floyd is painting it pink. You can consider the wall being made of a very large number of bricks, numbered $ 1 $ , $ 2 $ , $ 3 $ and so on.

Iahub has the following scheme of painting: he skips $ x-1 $ consecutive bricks, then he paints the $ x $ -th one. That is, he'll paint bricks $ x $ , $ 2·x $ , $ 3·x $ and so on red. Similarly, Floyd skips $ y-1 $ consecutive bricks, then he paints the $ y $ -th one. Hence he'll paint bricks $ y $ , $ 2·y $ , $ 3·y $ and so on pink.

After painting the wall all day, the boys observed that some bricks are painted both red and pink. Iahub has a lucky number $ a $ and Floyd has a lucky number $ b $ . Boys wonder how many bricks numbered no less than $ a $ and no greater than $ b $ are painted both red and pink. This is exactly your task: compute and print the answer to the question.

## 说明/提示

Let's look at the bricks from $ a $ to $ b $ $ (a=6,b=18) $ . The bricks colored in red are numbered 6, 8, 10, 12, 14, 16, 18. The bricks colored in pink are numbered 6, 9, 12, 15, 18. The bricks colored in both red and pink are numbered with 6, 12 and 18.

## 样例 #1

### 输入

```
2 3 6 18
```

### 输出

```
3```

# AI分析结果



# 分析与题解

## 算法分类
**数论**

---

## 题解思路与难点对比

### 核心公式与推导
题目要求找出区间 `[a, b]` 内同时是 `x` 和 `y` 倍数的数的个数。这类数必然是 `x` 和 `y` 的最小公倍数（LCM）的倍数。数学推导如下：

1. **求 LCM**  
   `lcm(x, y) = x * y / gcd(x, y)`  
   其中 `gcd(x, y)` 为最大公约数，可通过辗转相除法快速求解。

2. **区间计数**  
   区间 `[a, b]` 内 `lcm` 的倍数个数为：  
   `count = floor(b / lcm) - floor((a - 1) / lcm)`

### 解决难点
- **边界处理**：通过 `floor((a - 1)/lcm)` 而非 `floor(a/lcm)` 避免漏掉 `a` 自身是倍数的情况。
- **大数溢出**：使用 `long long` 防止计算 `x * y` 时溢出。

### 题解对比
- **暴力枚举**：遍历区间会超时（时间复杂度 `O(b-a+1)`）。
- **数学公式**：直接计算 `floor` 商差，时间复杂度 `O(log(min(x,y)))`（辗转相除法复杂度）。

---

## 题解评分（≥4星）

### [Quit] ⭐⭐⭐⭐
- **亮点**：公式正确，代码简洁，但边界处理稍显复杂。
- **改进点**：用 `(a-1)/lcm` 代替循环判断起始点。

### [BetaCutS] ⭐⭐⭐⭐⭐
- **亮点**：公式一步到位，代码极简，完美处理边界。
- **代码片段**：
  ```cpp
  printf("%d", b/z - (a-1)/z);
  ```

### [Qerucy] ⭐⭐⭐⭐
- **亮点**：完整公式推导，代码可读性强。
- **注意点**：需确保 `lcm` 计算正确，避免溢出。

---

## 最优思路提炼
1. **计算 LCM**：`lcm = x * y / gcd(x, y)`。
2. **区间计数公式**：  
   `count = (b // lcm) - ((a - 1) // lcm)`。

---

## 同类型题与算法套路
- **常见套路**：区间内倍数问题 → 转换为 LCM 计算。
- **扩展题型**：多个数的公倍数、带偏移的区间计数等。

---

## 推荐题目
1. [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)  
2. [P1072 Hankson 的趣味题](https://www.luogu.com.cn/problem/P1072)  
3. [P1516 青蛙的约会](https://www.luogu.com.cn/problem/P1516)  

---

## 个人心得摘录
- **BetaCutS**：“用 `floor(b/z) - floor((a-1)/z)` 直接计算，避免循环，效率最优。”
- **Colead**：“注意 `__gcd` 在竞赛中的使用限制，需手写实现。”

---

## 可视化算法分析

### 核心步骤演示（伪代码）
```plaintext
1. 输入 x=2, y=3, a=6, b=18
2. 计算 gcd(2,3)=1 → lcm=6
3. 计算：
   floor(18/6) = 3
   floor((6-1)/6) = 0
4. 结果：3 - 0 = 3
```

### 复古像素风格动画设计
- **颜色标记**：
  - 红色：当前计算的变量（如 `x`, `y`）。
  - 绿色：中间结果（`gcd`, `lcm`）。
  - 黄色：最终答案。
- **音效**：
  - 计算完成：8-bit 成功音效。
  - 错误输入：短促警报声。
- **Canvas 绘制**：  
  动态展示砖块编号，高亮 `x` 和 `y` 的倍数，最终标记共同倍数。

---

## 核心代码实现
```cpp
#include <iostream>
using namespace std;
typedef long long ll;

ll gcd(ll x, ll y) {
    return y == 0 ? x : gcd(y, x % y);
}

int main() {
    ll x, y, a, b;
    cin >> x >> y >> a >> b;
    ll lcm = x / gcd(x, y) * y; // 防止溢出
    cout << (b / lcm - (a - 1) / lcm);
    return 0;
}
```

---
处理用时：59.95秒