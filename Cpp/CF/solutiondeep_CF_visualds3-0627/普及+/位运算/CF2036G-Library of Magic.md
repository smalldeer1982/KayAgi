# 题目信息

# Library of Magic

## 题目描述

This is an interactive problem.

The Department of Supernatural Phenomena at the Oxenfurt Academy has opened the Library of Magic, which contains the works of the greatest sorcerers of Redania — $ n $ ( $ 3 \leq n \leq 10^{18} $ ) types of books, numbered from $ 1 $ to $ n $ . Each book's type number is indicated on its spine. Moreover, each type of book is stored in the library in exactly two copies! And you have been appointed as the librarian.

One night, you wake up to a strange noise and see a creature leaving the building through a window. Three thick tomes of different colors were sticking out of the mysterious thief's backpack. Before you start searching for them, you decide to compute the numbers $ a $ , $ b $ , and $ c $ written on the spines of these books. All three numbers are distinct.

So, you have an unordered set of tomes, which includes one tome with each of the pairwise distinct numbers $ a $ , $ b $ , and $ c $ , and two tomes for all numbers from $ 1 $ to $ n $ , except for $ a $ , $ b $ , and $ c $ . You want to find these values $ a $ , $ b $ , and $ c $ .

Since you are not working in a simple library, but in the Library of Magic, you can only use one spell in the form of a query to check the presence of books in their place:

- "xor l r" — Bitwise XOR query with parameters $ l $ and $ r $ . Let $ k $ be the number of such tomes in the library whose numbers are greater than or equal to $ l $ and less than or equal to $ r $ . You will receive the result of the computation $ v_1 \oplus v_2 \oplus ... \oplus v_k $ , where $ v_1 ... v_k $ are the numbers on the spines of these tomes, and $ \oplus $ denotes the operation of [bitwise exclusive OR](http://tiny.cc/xor_wiki_eng).

Since your magical abilities as a librarian are severely limited, you can make no more than $ 150 $ queries.

## 说明/提示

In the first test case, the books in the library after the theft look like this:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2036G/fa5245a6b21b822e029654d6d78459d7dcab42ae.png)

Now consider the answers to the queries:

- For the query "xor 1 1", you receive the result $ 1 \oplus 1 = 0 $ . Two tomes satisfy the condition specified in the query — both with the number $ 1 $ .
- For the query "xor 2 2", you receive the result $ 2 $ , as only one tome satisfies the specified condition.
- For the query "xor 3 3", you receive the result $ 3 $ .
- For the query "xor 4 6", you receive the result $ 4 \oplus 6 \oplus 4 \oplus 5 \oplus 6 = 5 $ .

In the second test case, there are only $ 3 $ types of books, and it is easy to guess that the missing ones have the numbers $ 1 $ , $ 2 $ , and $ 3 $ .

## 样例 #1

### 输入

```
2
6

0

2

3

5

3```

### 输出

```
xor 1 1

xor 2 2

xor 3 3

xor 4 6

ans 2 3 5

ans 1 2 3```

# AI分析结果



### 算法分类
交互题、位运算、二分法

---

### 题解思路与难点分析

#### 核心思路
1. **异或性质**：每个数出现两次会被异或抵消，查询结果为三个缺失数的异或和。
2. **分情况处理**：
   - **异或和 ≠ 0**：二分确定最小值和最大值，中间值通过异或和推导。
   - **异或和 = 0**：寻找二进制最高位确定最小值，再二分最大值。

#### 解决难点
1. **异或和为0的特殊处理**：
   - 三个数的二进制每位必须有偶数个1，最高位属于两个较大数。
   - 枚举二进制位，查询前缀区间 `[1, 2^i-1]`，首次非零结果即为最小值。
2. **高效二分**：
   - 对非零情况，通过两次二分分别确定最小和最大值，总查询次数为 `2*log(n)`。
   - 对零情况，通过一次枚举和两次二分，总次数仍控制在 `O(log n)`。

#### 算法流程
```python
def solve():
    xor_all = query(1, n)
    if xor_all != 0:
        # 二分确定最小值和最大值
        a = binary_search_prefix()
        c = binary_search_suffix()
        b = xor_all ^ a ^ c
    else:
        # 枚举二进制位确定最小值
        for i in range(60, -1, -1):
            if query(1, 2^i-1) != 0:
                a = query(1, 2^i-1)
                break
        # 二分确定最大值
        c = binary_search_suffix(a+1, n)
        b = a ^ c
    return a, b, c
```

---

### 题解评分（≥4星）

#### 沉石鱼惊旋（★★★★☆）
- **关键亮点**：
  - 清晰分情况处理，代码逻辑完整。
  - 处理异或和为0时通过位枚举高效定位。
- **代码片段**：
  ```cpp
  if (axbxc == 0) {
      for (int i = 60; i >= 0; i--) {
          ll t = query(1, (1LL << i) - 1);
          if (t) { /* 找到最小值 */ }
      }
  }
  ```

#### CJ_Fu（★★★★☆）
- **关键亮点**：
  - 利用二进制最高位特性推导，逻辑简洁。
  - 实现中结合二分与位运算，减少冗余查询。
- **代码片段**：
  ```cpp
  if (num != 0) {
      int l = x + 1, r = n, res = 0;
      while (l <= r) {
          mid = (l + r) >> 1;
          if (ask(x+1, mid) == x) /* 二分找最大值 */
      }
  }
  ```

#### wly09（★★★★☆）
- **关键亮点**：
  - 代码紧凑，处理异或和0时快速定位。
  - 通过二分嵌套实现高效查询。
- **代码片段**：
  ```cpp
  for (i=2; ;i*=2)
      if (ask(1, i-1)) break;
  a = ask(1, i-1);
  ```

---

### 最优思路与技巧
1. **异或和分治**：根据异或和是否为0选择不同策略，避免无效查询。
2. **二进制位枚举**：针对异或和为0的情况，利用最高位特性快速定位最小值。
3. **双重二分**：通过前缀和后缀二分确定极值，时间复杂度稳定。

---

### 同类题型与推荐
1. **CF1797C Li Hua and Chess**（交互题，二分定位）
2. **CF1848C Vika and Price Tags**（位运算性质分析）
3. **洛谷 P2446 [SDOI2010] 大陆争霸**（交互思维与异或应用）

---

### 可视化设计
#### 动画方案（8位像素风格）
1. **核心流程**：
   - **步骤1**：显示整个数轴，用绿色方块表示完整区间 `[1, n]`。
   - **步骤2**：执行 `xor 1 n`，结果以闪烁红字显示。
   - **步骤3**（异或非零）：
     - 二分过程：黄色光标移动，蓝色区域表示当前查询区间。
     - 确定最小值/最大值时，对应位置出现爆炸特效。
   - **步骤4**（异或为零）：
     - 二进制位从高到低扫描，红色光束标记有效位。
     - 确定最小值后，右侧区间以紫色高亮，继续二分。

2. **交互功能**：
   - **速度滑块**：调整二分步进速度（0.5x-3x）。
   - **音效**：查询时播放“哔”声，定位成功时播放“叮咚”音效。

#### 代码片段（Canvas绘制）
```javascript
function drawBinarySearch(l, r, mid, result) {
    ctx.fillStyle = "#8B00FF"; // 紫色表示当前区间
    ctx.fillRect(l * scaleX, 0, (r-l)*scaleX, canvas.height);
    ctx.fillStyle = "#FFD700"; // 金色表示光标
    ctx.fillRect(mid * scaleX, 0, 2, canvas.height);
    if (result !== 0) {
        playSound("success.wav"); // 成功音效
    }
}
```

---

### 总结
通过分治策略和位运算特性，结合高效二分与枚举，解决交互场景下的异或难题。可视化设计以复古像素风格增强学习趣味性，重点展示关键查询步骤与结果推导。

---
处理用时：114.86秒