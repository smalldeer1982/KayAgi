# 题目信息

# Romantic Glasses

## 题目描述

Iulia has $ n $ glasses arranged in a line. The $ i $ -th glass has $ a_i $ units of juice in it. Iulia drinks only from odd-numbered glasses, while her date drinks only from even-numbered glasses.

To impress her date, Iulia wants to find a contiguous subarray of these glasses such that both Iulia and her date will have the same amount of juice in total if only the glasses in this subarray are considered. Please help her to do that.

More formally, find out if there exists two indices $ l $ , $ r $ such that $ 1 \leq l \leq r \leq n $ , and $ a_l + a_{l + 2} + a_{l + 4} + \dots + a_{r} = a_{l + 1} + a_{l + 3} + \dots + a_{r-1} $ if $ l $ and $ r $ have the same parity and $ a_l + a_{l + 2} + a_{l + 4} + \dots + a_{r - 1} = a_{l + 1} + a_{l + 3} + \dots + a_{r} $ otherwise.

## 说明/提示

In the first test case, Iulia can pick $ l=1 $ and $ r=3 $ . Then she drinks $ a_1+a_3=1+2=3 $ units and her date drinks $ a_2=3 $ units of juice.

In the second test case, Iulia can pick $ l=2 $ and $ r=5 $ . Then she drinks $ a_3+a_5=1+1=2 $ units and her date drinks $ a_2+a_4=1+1=2 $ units of juice.

In the third test case no such contiguous subarray works.

In the fourth test case, Iulia can pick $ l=2 $ and $ r=8 $ . Then she drinks $ a_3+a_5+a_7=11+1+1=13 $ units and her date drinks $ a_2+a_4+a_6+a_8=2+4+5+2=13 $ units of juice.

## 样例 #1

### 输入

```
6
3
1 3 2
6
1 1 1 1 1 1
10
1 6 9 8 55 3 14 2 7 2
8
1 2 11 4 1 5 1 2
6
2 6 1 5 7 8
9
2 5 10 4 4 9 6 7 8```

### 输出

```
YES
YES
NO
YES
NO
YES```

# AI分析结果



# 算法分类
前缀和与哈希表

---

## 综合分析与结论

### 核心思路
将奇数下标视为正贡献，偶数下标视为负贡献，寻找连续子数组使得正负贡献相等。通过维护前缀和差值，利用哈希表快速判断是否存在重复差值，从而在O(n)时间复杂度内解决问题。

### 解决难点
1. **奇偶交替处理**：通过将偶数下标元素取负，将问题转化为寻找和为0的连续子数组。
2. **快速查询**：使用哈希表存储前缀和差值，将双重循环优化为单次遍历。
3. **边界条件**：初始化哈希表插入0值，处理从第一个元素开始的合法子数组情况。

---

## 题解清单（≥4星）

1. **WsW_（4星）**
   - **亮点**：代码结构清晰，使用`set`存储差值，明确展示核心等式转换过程。
   - **关键代码**：
     ```cpp
     set<ll> s; s.insert(0); // 初始化
     sum[i&1] += a[...];    // 奇偶分离累加
     if(s.count(sum[1]-sum[0])) return YES;
     ```

2. **wxzzzz（4星）**
   - **亮点**：直接使用`map`实现，简洁高效，明确等式变形逻辑。
   - **关键代码**：
     ```cpp
     if (sum1 == sum2 || flag[sum1 - sum2]) return 1;
     flag[sum1 - sum2] = 1; // 哈希表标记差值
     ```

3. **huangzhixia（4星）**
   - **亮点**：详细推导前缀和转化过程，适合教学理解。
   - **心得摘录**："必须清空map！否则多测数据会互相干扰。"

---

## 最优思路与技巧

### 核心技巧
- **符号转换**：将偶数下标元素取负，统一为寻找和为0的连续子数组问题。
- **差值哈希**：维护前缀和差值，利用哈希表O(1)查询重复值。
- **初始化技巧**：插入初始值0，处理全区间合法的情况。

### 代码实现
```cpp
// 核心代码段
set<long long> s;
s.insert(0); // 关键初始化
long long prefix = 0;
for(int i=1; i<=n; i++){
    prefix += (i%2 ? a[i] : -a[i]); // 奇正偶负
    if(s.count(prefix)) return true;
    s.insert(prefix);
}
```

---

## 类似题目推荐
1. **洛谷P3369** - 最大子段和（前缀和极值）
2. **LeetCode 525. 连续数组** - 0/1平衡子数组
3. **LeetCode 560. 和为K的子数组** - 前缀和差值计数

---

## 可视化设计

### 动画方案
1. **像素风格界面**：
   - 使用16色调色板，每个元素显示为8位像素块。
   - 当前处理元素高亮闪烁，差值显示在顶部状态栏。

2. **关键步骤演示**：
   - **步骤1**：元素按奇偶显示不同颜色（绿/红），实时计算前缀和差值。
   - **步骤2**：右侧哈希表区域动态显示已存储的差值，命中时触发爆炸特效。
   - **步骤3**：找到合法区间时，地面升起像素庆祝动画，播放8位胜利音效。

3. **交互功能**：
   - **速度控制**：滑块调节执行速度（0.5x-4x）。
   - **单步执行**：按空格键逐步查看差值计算过程。
   - **AI演示**：自动模式展示最优路径，附带路径高亮。

### 音效设计
- **元素处理**：短促"哔"声（每处理一个元素）。
- **哈希命中**：经典FC得分音效（250Hz方波）。
- **错误提示**：低沉嗡鸣声（100Hz三角波）。

---

通过将算法过程转化为直观的像素动画与声效反馈，学习者可快速理解前缀差值与哈希表查询的核心机制，同时增强学习趣味性。

---
处理用时：56.29秒