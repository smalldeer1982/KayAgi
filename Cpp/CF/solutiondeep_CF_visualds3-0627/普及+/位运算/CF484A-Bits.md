# 题目信息

# Bits

## 题目描述

Let's denote as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) the number of bits set ('1' bits) in the binary representation of the non-negative integer $ x $ .

You are given multiple queries consisting of pairs of integers $ l $ and $ r $ . For each query, find the $ x $ , such that $ l<=x<=r $ , and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) is maximum possible. If there are multiple such numbers find the smallest of them.

## 说明/提示

Let's denote as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) the number of bits set ('1' bits) in the binary representation of the non-negative integer $ x $ .

You are given multiple queries consisting of pairs of integers $ l $ and $ r $ . For each query, find the $ x $ , such that $ l<=x<=r $ , and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) is maximum possible. If there are multiple such numbers find the smallest of them.

## 样例 #1

### 输入

```
3
1 2
2 4
1 10
```

### 输出

```
1
3
7
```

# AI分析结果



## 算法分类
贪心算法

---

## 题解思路与核心难点

### 核心思路
从**最低位**开始，通过位运算逐步将`l`的每个二进制位变为1，直到无法再添加1（即操作后超过`r`）为止。此方法保证在不超过`r`的前提下，尽可能多地填充1的个数，同时保持数值最小。

### 关键步骤
1. **初始化**：从最低位开始（`i=1`）。
2. **逐位填充**：尝试将`l`的当前位设为1（`l | i`），若结果仍不超过`r`，则更新`l`。
3. **终止条件**：当填充后的数值超过`r`时停止。

### 解决难点
- **低位优先**：填充低位对数值增长影响最小，保证结果最小。
- **位运算优化**：用`i <<= 1`快速处理每一位，时间复杂度为`O(log r)`。

---

## 题解评分（≥4星）

1. **XiXi（5星）**
   - **亮点**：代码最简洁，直接通过`l|=i`和`i<<=1`实现贪心，清晰展示核心逻辑。
   - **代码可读性**：无冗余代码，变量命名明确。
   ```cpp
   for (i=1; (l|i)<=r; i<<=1) l|=i;
   ```

2. **EuphoricStar（4星）**
   - **亮点**：使用`ull`避免溢出，核心逻辑与XiXi一致。
   - **优化**：明确提到`<<`等价于`*2`，适合新手理解。

3. **SIXIANG32（4星）**
   - **亮点**：详细解释“构造”思路，强调CF题构造特性。
   - **代码**：封装`solve`函数增强可读性。

---

## 最优思路提炼

### 关键技巧
- **低位优先填充**：从最低位开始，逐步将0变为1。
- **位运算加速**：用`|`操作直接设置某位为1，用`<<`快速遍历所有位。

### 实现模板
```cpp
for (long long i = 1; (l | i) <= r; i <<= 1) {
    l |= i; // 将当前最低的0位设为1
}
```

---

## 同类型题推荐

1. **P2431 正妹吃月饼**  
   - 类似贪心：用尽可能多的低权值硬币组合出指定数值。

2. **CF276D Little Girl and Maximum XOR**  
   - 位运算贪心：在区间内找异或值最大的数。

3. **洛谷 P2114 [NOI2014] 起床困难综合症**  
   - 位运算贪心：在操作序列后选择最优初始值。

---

## 可视化算法演示

### 动画设计
- **像素风格界面**：  
  - 使用8位色调色板（绿/红表示0/1，黄表示当前操作位）。
  - 网格展示`l`的二进制位，从右向左逐位填充。
- **交互控制**：  
  - **步进**：手动点击触发填充下一位。
  - **自动播放**：以500ms/步的速度自动运行。
- **音效**：  
  - 填充成功：短促“滴”声。
  - 终止条件：低沉“哔”声。

### 演示流程
1. 初始显示`l`和`r`的二进制形式。
2. 每次循环高亮当前位（`i`对应的位置）。
3. 若`l | i ≤ r`，将该位变为绿色（成功填充），否则停止。
4. 最终结果以闪烁效果标记。

---

## 个人心得摘录

- **XiXi**：  
  > “第一次还想着根据玄学关系做这题” → 强调贪心策略的简洁性。

- **MVP_Harry**：  
  > “分情况讨论递归” → 复杂方法不如贪心直接。

---

## 核心代码实现

```cpp
#include <cstdio>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        long long l, r;
        scanf("%lld%lld", &l, &r);
        for (long long i = 1; (l | i) <= r; i <<= 1) {
            l |= i; // 核心操作：填充当前最低的0位
        }
        printf("%lld\n", l);
    }
    return 0;
}
```

---
处理用时：79.64秒