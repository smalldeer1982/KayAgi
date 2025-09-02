# 题目信息

# Turtle and a MEX Problem (Easy Version)

## 题目描述

The two versions are different problems. In this version of the problem, you can choose the same integer twice or more. You can make hacks only if both versions are solved.

One day, Turtle was playing with $ n $ sequences. Let the length of the $ i $ -th sequence be $ l_i $ . Then the $ i $ -th sequence was $ a_{i, 1}, a_{i, 2}, \ldots, a_{i, l_i} $ .

Piggy gave Turtle a problem to solve when Turtle was playing. The statement of the problem was:

- There was a non-negative integer $ x $ at first. Turtle would perform an arbitrary number (possibly zero) of operations on the integer.
- In each operation, Turtle could choose an integer $ i $ such that $ 1 \le i \le n $ , and set $ x $ to $ \text{mex}^{\dagger}(x, a_{i, 1}, a_{i, 2}, \ldots, a_{i, l_i}) $ .
- Turtle was asked to find the answer, which was the maximum value of $ x $ after performing an arbitrary number of operations.

Turtle solved the above problem without difficulty. He defined $ f(k) $ as the answer to the above problem when the initial value of $ x $ was $ k $ .

Then Piggy gave Turtle a non-negative integer $ m $ and asked Turtle to find the value of $ \sum\limits_{i = 0}^m f(i) $ (i.e., the value of $ f(0) + f(1) + \ldots + f(m) $ ). Unfortunately, he couldn't solve this problem. Please help him!

 $ ^{\dagger}\text{mex}(c_1, c_2, \ldots, c_k) $ is defined as the smallest non-negative integer $ x $ which does not occur in the sequence $ c $ . For example, $ \text{mex}(2, 2, 0, 3) $ is $ 1 $ , $ \text{mex}(1, 2) $ is $ 0 $ .

## 说明/提示

In the first test case, when $ x $ is initially $ 2 $ , Turtle can choose $ i = 3 $ and set $ x $ to $ \text{mex}(x, a_{3, 1}, a_{3, 2}, a_{3, 3}, a_{3, 4}) = \text{mex}(2, 7, 0, 1, 5) = 3 $ . It can be proved that Turtle can't make the value of $ x $ greater than $ 3 $ , so $ f(2) = 3 $ .

It can be seen that $ f(0) = 3 $ , $ f(1) = 3 $ , $ f(2) = 3 $ , $ f(3) = 3 $ , and $ f(4) = 4 $ . So $ f(0) + f(1) + f(2) + f(3) + f(4) = 3 + 3 + 3 + 3 + 4 = 16 $ .

In the second test case, when $ x $ is initially $ 1 $ , Turtle can choose $ i = 3 $ and set $ x $ to $ \text{mex}(x, a_{3, 1}, a_{3, 2}, a_{3, 3}, a_{3, 4}, a_{3, 5}) = \text{mex}(1, 1, 3, 0, 3, 3) = 2 $ , and choose $ i = 3 $ and set $ x $ to $ \text{mex}(x, a_{3, 1}, a_{3, 2}, a_{3, 3}, a_{3, 4}, a_{3, 5}) = \text{mex}(2, 1, 3, 0, 3, 3) = 4 $ . It can be proved that Turtle can't make the value of $ x $ greater than $ 4 $ , so $ f(1) = 4 $ .

It can be seen that $ f(0) = 4 $ , $ f(1) = 4 $ , $ f(2) = 4 $ , $ f(3) = 4 $ , and $ f(4) = 4 $ . So $ f(0) + f(1) + f(2) + f(3) + f(4) = 4 + 4 + 4 + 4 + 4 = 20 $ .

In the fourth test case, it can be seen that $ f(0) = 3 $ and $ f(1) = 3 $ . So $ f(0) + f(1) = 3 + 3 = 6 $ .

## 样例 #1

### 输入

```
6
3 4
2 0 2
3 2 3 3
4 7 0 1 5
3 4
5 0 2 0 4 11
1 1
5 1 3 0 3 3
2 50
2 1 2
2 1 2
1 1
7 1 2 4 1 4 9 5
4 114514
2 2 2
5 7 3 6 0 3
3 0 1 1
5 0 9 2 1 5
5 1919810
1 2
2 324003 0
3 1416324 2 1460728
4 1312631 2 0 1415195
5 1223554 192248 2 1492515 725556```

### 输出

```
16
20
1281
6
6556785365
1842836177961```

# AI分析结果



### 唯一算法分类
组合数学

### 综合分析与结论
**核心思路**：每个序列通过两次 mex 操作得到次小未出现数，取所有序列中的最大值 v_p。初始 x ≤ v_p 时结果为 v_p，否则取 x。总和拆分为两部分求和。

**关键公式推导**：
1. 对每个序列求两次 mex：
   - u_i = mex(a_i)
   - v_i = mex(a_i ∪ {u_i})
2. 取最大 v_p，总和为：
   - 当 x ≤ v_p 时贡献 v_p
   - 当 x > v_p 时贡献 x
   总和公式：`sum = v_p * (min(v_p, m) + 1) + (m - v_p) * (v_p + 1 + m) // 2`（若 m > v_p）

**可视化设计**：
- **像素动画**：展示每个序列的两次 mex 计算，用不同颜色区分元素是否存在于集合中。
- **动态区间划分**：以 v_p 为分界，左侧蓝色区域（v_p 贡献），右侧绿色区域（x 自身贡献），滚动显示每项求和过程。
- **音效触发**：完成 mex 计算时播放“滴”声，总和计算完毕时播放胜利音效。

### 题解清单 (≥4星)
1. **Exp10re (4星)**
   - **亮点**：简明推导两次 mex 的作用，直接给出总和公式，代码高效。
2. **Defy_HeavenS (4星)**
   - **亮点**：详细分析操作过程，代码包含 set 实现 mex 的细节，注释清晰。

### 最优思路提炼
- **两次 mex 极值**：通过两次 mex 操作确定每个序列的最大提升能力，取全局最大值。
- **区间分段求和**：数学拆分总和为定值区间与递增区间的和，利用等差数列公式高效计算。

### 同类型题推荐
1. **CF1849D**：利用 mex 性质进行动态规划。
2. **CF1375E**：涉及 mex 操作与贪心策略。
3. **CF1673C**：组合数学与 mex 的综合应用。

### 代码核心实现
```cpp
// 计算每个序列的次小 mex
int compute_second_mex(vector<int>& a) {
    set<int> s;
    unordered_map<int, int> cnt;
    for (int x : a) {
        if (x > a.size() + 2) x = a.size() + 2; // 优化处理大数
        cnt[x]++;
        s.insert(x);
    }
    int u = 0;
    while (s.count(u)) u++; // 第一次 mex
    cnt[u]++;
    s.insert(u);
    int v = 0;
    while (s.count(v)) v++; // 第二次 mex
    return v;
}

// 总和计算
long long sum_f(int m, int v_p) {
    if (m < v_p) return (long long)(m + 1) * v_p;
    long long len = v_p + 1;
    long long part1 = v_p * len;
    long long part2 = (m - v_p) * (v_p + 1 + m) / 2;
    return part1 + part2;
}
```

### 复古游戏化动画设计
- **Canvas 绘制**：
  1. **序列处理阶段**：每个序列元素以 8x8 像素块显示，计算 mex 时高亮缺失的最小值。
  2. **v_p 展示**：用闪烁的金色方块标记最大次小 mex。
  3. **求和界面**：左侧为蓝色静态条（0~v_p），右侧为绿色递增条（v_p+1~m），下方实时更新总和。
- **音效**：8-bit 风格音效，关键步骤触发不同音调。
- **自动演示**：按空格键逐步执行，Enter 键自动播放，速度可调。

---
处理用时：65.91秒