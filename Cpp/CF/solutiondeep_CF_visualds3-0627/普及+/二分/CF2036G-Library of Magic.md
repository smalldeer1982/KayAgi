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



# 算法分类
**二分**

---

## 综合分析与结论
**核心思路**：  
题目需通过异或查询找出被偷的三个不同数。核心思路分为两种情况处理：  
1. **异或和非零**：利用二分法快速定位最小和最大值，中间值由异或性质推导。  
2. **异或和为零**：通过枚举最高位确定其中一个数，再二分剩余区间。  

**二分关键点**：  
1. **区间收缩**：  
   - **前缀二分**：当查询 `[1, mid]` 结果非零时，说明最小数在左半区间，右边界收缩。  
   - **后缀二分**：当查询 `[mid, n]` 结果非零时，说明最大数在右半区间，左边界收缩。  
2. **边界条件**：  
   - `mid` 取中间值，采用 `(L + R) >> 1` 避免溢出。  
   - 循环终止条件为 `L <= R`，确保覆盖所有可能。  

**解决难点**：  
- **异或和为零**时，常规二分失效。通过最高位枚举，利用二进制特性打破平衡。  
- **避免死循环**：正确调整左右边界，确保每次查询能缩小有效范围。  

---

## 题解评分（≥4星）
1. **沉石鱼惊旋（5星）**  
   - **亮点**：清晰的分类讨论，高效处理异或和为0的情况，代码简洁。  
   - **代码片段**：  
     ```cpp
     // 处理异或和为0的情况
     for (int i = 60; i >= 0; i--) {
         if ((1LL << i) - 1 > n) continue;
         ll t = query(1, (1LL << i) - 1);
         if (t) { ... }
     }
     ```

2. **MrPython（4.5星）**  
   - **亮点**：使用C++20 ranges优化二分逻辑，代码风格现代。  
   - **代码片段**：  
     ```cpp
     auto view = ranges::views::iota(1ull, n + 1) | 
                 ranges::views::transform([](uli v) { return ask(1, v); });
     ```

3. **Super_Cube（4星）**  
   - **亮点**：数学推导严谨，处理异或和为零时的最高位分析清晰。  
   - **代码片段**：  
     ```cpp
     for (int i = 60; ~i; --i) {
         if ((1ll<<i)-1 > n) continue;
         if (ask(1, (1ll<<i)-1)) { ... }
     }
     ```

---

## 最优思路提炼
1. **分类讨论**：根据全局异或和是否为0选择策略。  
2. **二分条件**：  
   - **非零情况**：前缀二分找最小数，后缀二分找最大数。  
   - **零情况**：枚举最高位确定最小数，剩余区间二分找最大数。  
3. **异或性质**：利用 `a^b^c` 的特性快速推导中间值。  

---

## 类似算法套路
1. **二分答案**：如寻找满足条件的极值（最小值最大或最大值最小）。  
2. **异或特性应用**：如查找唯一出现奇数次数的元素。  
3. **位运算优化**：利用二进制位快速缩小搜索范围。  

---

## 推荐题目
1. **P1873 砍树**（二分答案）  
2. **P1462 通往奥格瑞玛的道路**（二分答案+最短路）  
3. **P1631 序列合并**（二分查找中位数）  

---

## 个人心得摘录
- **调试经验**：在二分过程中，输出中间变量（如 `mid` 和查询结果）可快速定位逻辑错误。  
- **边界处理**：当 `n=3` 时需特判，避免二分逻辑失效。  

---

## 可视化设计
**动画方案**：  
1. **区间展示**：用滑动条表示当前区间 `[L, R]`，高亮 `mid`。  
2. **颜色标记**：  
   - **红色**：查询结果非零，区间向左/右收缩。  
   - **绿色**：查询结果为零，区间向右/左扩张。  
3. **步进控制**：允许单步执行，观察 `mid` 计算与区间更新。  

**复古像素风格**：  
- **颜色方案**：8位色（红、绿、蓝）表示区间状态。  
- **音效**：  
  - **更新 mid**：短促“哔”声。  
  - **找到答案**：上扬音效。  

---

## 核心代码实现
```cpp
// 处理异或和非零的情况
ll L = 1, R = n, a = n;
while (L <= R) {
    ll mid = (L + R) >> 1;
    if (query(1, mid)) {
        R = mid - 1;
        a = mid;
    } else {
        L = mid + 1;
    }
}
// 类似逻辑处理后缀二分找最大值 c
```

---
处理用时：138.17秒