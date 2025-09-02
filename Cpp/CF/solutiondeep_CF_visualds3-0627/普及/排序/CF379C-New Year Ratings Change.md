# 题目信息

# New Year Ratings Change

## 题目描述

One very well-known internet resource site (let's call it X) has come up with a New Year adventure. Specifically, they decided to give ratings to all visitors.

There are $ n $ users on the site, for each user we know the rating value he wants to get as a New Year Present. We know that user $ i $ wants to get at least $ a_{i} $ rating units as a present.

The X site is administered by very creative and thrifty people. On the one hand, they want to give distinct ratings and on the other hand, the total sum of the ratings in the present must be as small as possible.

Help site X cope with the challenging task of rating distribution. Find the optimal distribution.

## 样例 #1

### 输入

```
3
5 1 1
```

### 输出

```
5 1 2
```

## 样例 #2

### 输入

```
1
1000000000
```

### 输出

```
1000000000
```

# AI分析结果



# 算法分类
**贪心、排序**

---

# 题解思路与解决难点

## 核心思路
所有题解的核心目标是为每个用户分配最小的不重复评分。关键在于如何高效处理重复的初始值并保证总和最小。主要分为两类方法：
1. **排序+递推**：将初始值排序后，依次将每个值调整为前一个值+1（若重复），保证递增性。
2. **路径压缩（并查集）**：用哈希结构记录已分配值，递归查找下一个可用值，跳过已占用区间。

## 解决难点对比
- **排序法**：需处理原始顺序恢复，通过记录下标实现。难点在于证明排序后递推的正确性（确保递增性即最优）。
- **路径压缩法**：需避免重复查询已占用值，通过哈希表存储下一个可用值，路径压缩优化查询效率。

---

# 题解评分（≥4星）

1. **fls233666（5星）**  
   - 思路清晰，排序后逐个调整并恢复顺序，时间复杂度稳定为 $O(n \log n)$。  
   - 代码可读性高，结构简洁，适合快速实现。  
   - 附手动模拟数据，验证算法正确性。

2. **frankchenfu（4星）**  
   - 递推公式 $b_i = \max(b_{i-1}+1, a_i)$ 简洁明确。  
   - 通过两次排序恢复原始顺序，逻辑严谨。

3. **drop（4星）**  
   - 第二次尝试改用排序法，代码简洁高效。  
   - 通过结构体保留原始下标，恢复顺序巧妙。

---

# 最优思路提炼

**贪心排序法**  
1. 将用户按初始值升序排序。  
2. 遍历时，若当前值 ≤ 前一个结果，则调整为前一个结果+1。  
3. 恢复原始顺序输出。  

**关键数据结构**：结构体保存初始值和下标，排序后处理再按原下标输出。

---

# 同类型题与算法套路

**相似题目**  
- **区间调度**：按结束时间排序选择最多不重叠区间。  
- **任务分配**：最小化总等待时间，贪心排序处理。  
- **合并区间**：排序后合并重叠区间。

**通用套路**  
- **排序预处理**：将无序数据按特定规则排序，简化后续处理。  
- **贪心调整**：通过局部最优调整（如递增调整）达到全局最优。

---

# 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)（贪心+优先队列）  
2. [P1803 线段覆盖](https://www.luogu.com.cn/problem/P1803)（排序+贪心选择）  
3. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)（贪心删除策略）

---

# 个人心得摘录

- **fls233666**：手动构造测试数据模拟，验证排序后递推的正确性。  
- **zjc5**：路径压缩法因递归层数过多导致TLE，改用非递归或优化实现。  
- **drop**：第一次暴力法TLE后反思，改用排序法避免循环查找。

---

# 可视化与算法演示

## 核心算法流程（排序法）
1. **初始数组**：显示原始数组和排序后数组。  
   ```plaintext
   原始输入：[5, 1, 1] → 排序后：[1, 1, 5]
   ```
2. **递推调整**：高亮当前处理元素，与前一个结果比较。  
   ```plaintext
   第1步：1 → 保持1  
   第2步：1 (前为1) → 调整为2  
   第3步：5 (前为2) → 保持5  
   ```
3. **恢复顺序**：按原始下标映射输出结果。  
   ```plaintext
   排序后结果：[1, 2, 5] → 原下标输出：[5, 1, 2]
   ```

## 复古像素化设计
- **动画效果**：  
  - 用16色像素块表示数组元素，排序时元素交换动画。  
  - 调整时当前元素闪烁，显示箭头指向前一个元素。  
- **音效**：  
  - 排序完成：8-bit 胜利音效。  
  - 元素调整：短促“滴”声。  
- **交互**：  
  - 步进控制：方向键控制动画进度。  
  - 自动演示：按A键启动AI自动执行。

---

# 核心代码实现

## fls233666 的排序法
```cpp
struct people { int a, b; }; // a: 初始值, b: 原始下标
sort(p, p + n, [](people p1, people p2) { return p1.a < p2.a; });

ans[p[0].b] = p[0].a;
for (int i = 1; i < n; i++) {
    if (p[i].a > ans[p[i-1].b]) 
        ans[p[i].b] = p[i].a;
    else 
        ans[p[i].b] = ans[p[i-1].b] + 1;
}
```

## 路径压缩法（zjc5）
```cpp
unordered_map<int, int> mp;
int find(int x) {
    if (!mp.count(x)) {
        mp[x] = x + 1;
        return x;
    }
    return mp[x] = find(mp[x]); // 路径压缩
}
// 调用：对每个x输出find(x)
```

---
处理用时：79.90秒