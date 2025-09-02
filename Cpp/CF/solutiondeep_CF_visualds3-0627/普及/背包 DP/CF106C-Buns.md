# 题目信息

# Buns

## 题目描述

Lavrenty, a baker, is going to make several buns with stuffings and sell them.

Lavrenty has $ n $ grams of dough as well as $ m $ different stuffing types. The stuffing types are numerated from 1 to $ m $ . Lavrenty knows that he has $ a_{i} $ grams left of the $ i $ -th stuffing. It takes exactly $ b_{i} $ grams of stuffing $ i $ and $ c_{i} $ grams of dough to cook a bun with the $ i $ -th stuffing. Such bun can be sold for $ d_{i} $ tugriks.

Also he can make buns without stuffings. Each of such buns requires $ c_{0} $ grams of dough and it can be sold for $ d_{0} $ tugriks. So Lavrenty can cook any number of buns with different stuffings or without it unless he runs out of dough and the stuffings. Lavrenty throws away all excess material left after baking.

Find the maximum number of tugriks Lavrenty can earn.

## 说明/提示

To get the maximum number of tugriks in the first sample, you need to cook 2 buns with stuffing 1, 4 buns with stuffing 2 and a bun without any stuffing.

In the second sample Lavrenty should cook 4 buns without stuffings.

## 样例 #1

### 输入

```
10 2 2 1
7 3 2 100
12 3 1 10
```

### 输出

```
241```

## 样例 #2

### 输入

```
100 1 25 50
15 5 20 10
```

### 输出

```
200```

# AI分析结果



# 算法分类
**动态规划（多重背包）**

---

## 题解思路与算法要点

### 核心问题建模
题目本质是多重背包问题：
- 面团总重量为背包容量
- 每种馅料的包子对应有限数量的物品
- 无馅包子视为完全背包的特殊情况

### 关键算法步骤
1. **状态定义**：`dp[i]` 表示恰好使用 i 克面团的最大收益
2. **初始化处理**：预处理无馅包子，填充所有 `i*c₀` 克面团的收益
3. **多重背包处理**：对每个馅料，拆分为 `a_i/b_i` 次 0-1 背包操作
4. **结果计算**：遍历所有可能的 i 取最大值

### 解决难点对比
| 题解 | 初始化方式 | 空间复杂度 | 时间复杂度 | 正确性保障 |
|-----|----------|----------|----------|----------|
| 0x3F | 精确填充 `i*c₀` 位置 | O(n) | O(nΣa_i/b_i) | 最后全局扫描取最优 |
| StupidSeven | 二维状态转移 | O(mn) | O(mn²) | 单独计算剩余面团 |
| Yeji_方法1 | 连续填充非精确值 | O(n) | O(nΣa_i/b_i) | 可能存在初始化误差 |
| Victorique | 统一处理所有物品 | O(n) | O(nΣa_i/b_i) | 同 0x3F |

---

## 精炼结论
**最优题解核心逻辑**：
1. 将无馅包子视为初始物品，按精确面消耗填充
2. 多重背包的暴力拆分法（每个可用次数视为独立物品）
3. 一维滚动数组优化空间

**可视化设计要点**：
1. **动态数组高亮**：在背包更新时，用红色标记当前更新的面团克数
2. **馅料处理动画**：每个馅料类型展示为不同颜色的方块，逐层叠加到面团容量线上
3. **收益对比动效**：当发现更高收益时，触发金色闪光效果
4. **复古像素风格**：用 8-bit 像素画风表现面团克数格子，音效随每次状态更新播放

---

## 题解评分（≥4星）

1. **0x3F（5星）**
   - ✅ 思路清晰：严格推导多重背包转化过程
   - ✅ 空间优化：一维滚动数组
   - ✅ 实践性强：代码简洁易移植
   - ❗ 个人心得："厉行节约"初始化方式体现优化思维

2. **Yeji_方法一（4星）**
   - ✅ 直观易懂：连续初始化更易理解
   - ❗ 潜在问题：非精确初始化可能影响极值
   - 💡 亮点：两种实现对比帮助理解

3. **Victorique_De_Blois（4星）**
   - ✅ 统一处理逻辑：无馅包子作为特殊物品
   - ❗ 可读性：变量命名可优化
   - 💡 亮点：注册器优化提升速度

---

## 核心代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, a, b, c, d, dp[1010], ans;

int main() {
    cin >> n >> m >> c >> d;
    // 初始化无馅包子
    for (int i = 1; i <= n/c; i++) 
        dp[i*c] = i*d;
    
    // 处理每种馅料
    while (m--) {
        cin >> a >> b >> c >> d;
        int cnt = a/b; // 最大包子数
        for (int t = 1; t <= cnt; t++) 
            for (int i = n; i >= c; i--)
                dp[i] = max(dp[i], dp[i-c] + d);
    }
    
    // 找最大收益
    for (int i = 1; i <= n; i++)
        ans = max(ans, dp[i]);
    cout << ans << endl;
    return 0;
}
```

---

## 同类型题目推荐
1. **P1776 宝物筛选**（多重背包经典题）
2. **P1833 樱花**（混合背包问题）
3. **P1853 投资的最大效益**（完全背包变种）

---

## 可视化方案设计
**8-bit 像素化背包演示**：
1. **Canvas 布局**：横向排列面团容量格子（1像素=1克）
2. **颜色编码**：
   - 绿色：当前可用的面团容量
   - 红色：正在更新的背包格子
   - 金色：当前最大收益值
3. **音效系统**：
   - 每次状态更新：8-bit "哔"声
   - 发现新最大值：上升音阶
   - 处理完一种馅料：鼓声音效
4. **自动演示模式**：按最优路径自动步进，速度可调

---

## 个人心得摘录
"多重背包的暴力拆分在数据规模小时反而更优——0x3F 的题解启示我们，理论复杂度不是唯一标准，实际代码效率往往取决于常数因子和实现方式。"

---

## 知识扩展
**多重背包优化技巧**：
1. **二进制拆分**：将数量 k 分解为 2⁰+2¹+...+2^m + r 的形式
2. **单调队列优化**：O(nm) 时间复杂度解法
3. **混合背包处理**：区分完全背包和多重背包部分

**举一反三**：
当遇到资源消耗型最大化问题时，先尝试建立背包模型，再根据物品特性选择适当的背包变种解法。

---
处理用时：198.81秒