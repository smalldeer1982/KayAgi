# 题目信息

# Maximum Crossings (Easy Version)

## 题目描述

The only difference between the two versions is that in this version $ n \leq 1000 $ and the sum of $ n $ over all test cases does not exceed $ 1000 $ .

A terminal is a row of $ n $ equal segments numbered $ 1 $ to $ n $ in order. There are two terminals, one above the other.

You are given an array $ a $ of length $ n $ . For all $ i = 1, 2, \dots, n $ , there should be a straight wire from some point on segment $ i $ of the top terminal to some point on segment $ a_i $ of the bottom terminal. For example, the following pictures show two possible wirings if $ n=7 $ and $ a=[4,1,4,6,7,7,5] $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1676H1/71a1fe41f3cad0f3cbda88716457eefb4e46b4ca.png)A crossing occurs when two wires share a point in common. In the picture above, crossings are circled in red.

What is the maximum number of crossings there can be if you place the wires optimally?

## 说明/提示

The first test case is shown in the second picture in the statement.

In the second test case, the only wiring possible has the two wires cross, so the answer is $ 1 $ .

In the third test case, the only wiring possible has one wire, so the answer is $ 0 $ .

## 样例 #1

### 输入

```
4
7
4 1 4 6 7 7 5
2
2 1
1
1
3
2 2 2```

### 输出

```
6
1
0
3```

# AI分析结果



## 唯一算法分类
**逆序对统计/二维偏序问题**

---

## 题解思路与核心分析

### 核心算法流程
1. **交叉条件推导**：当且仅当两条线满足 `i < j` 且 `a[i] >= a[j]` 时，必然存在交点。  
2. **暴力枚举**：遍历所有 `i < j` 的组合，统计满足条件的对数。  
3. **时间复杂度**：O(n²)，适用于 n ≤ 1000 的简单版本。

### 解决难点
- **正确推导交叉条件**：需理解线段的排列方式导致交叉的充要条件是逆序关系。  
- **暴力法的可行性**：由于数据规模较小，直接双重循环即可通过。

### 题解对比
两位题解思路完全一致，均通过双重循环统计逆序对。差异仅在于循环顺序：
- **题解1**：外层 `i` 遍历，内层 `j` 从 `i+1` 到 `n`。  
- **题解2**：外层 `j` 遍历，内层 `i` 从 `1` 到 `j-1`。  

两者时间复杂度相同，实现等价。

---

## 题解评分（≥4星）

1. **5k_sync_closer 的题解（5星）**  
   - 思路清晰，代码简洁，直接点明问题本质为逆序对统计。  
   - 代码可读性强，双重循环逻辑明确。  
   - 提供了二维偏序问题的优化方向（O(n log n)），拓展性强。

2. **include_BM 的题解（4.5星）**  
   - 逻辑正确，但循环顺序稍显不同，未提及更高阶优化。  
   - 代码同样简洁，但外层循环从 `j` 开始可能更直观。

---

## 最优思路提炼
**关键技巧**：将交叉问题转化为逆序对统计，暴力枚举所有 `i < j` 的组合。  
**思维核心**：理解线段交叉的几何条件等价于数组中的逆序关系。

---

## 同类型题目与套路
- **逆序对问题**：如统计数组中满足 `i < j` 且 `a[i] > a[j]` 的对数。  
- **二维偏序问题**：如统计满足 `x_i < x_j` 且 `y_i > y_j` 的点对。  

**通用解法**：  
- 小数据直接暴力双重循环。  
- 大数据使用归并排序或树状数组优化至 O(n log n)。

---

## 推荐题目
1. **P1908 逆序对**（洛谷）  
2. **CF977F Consecutive Subsequence**（二维偏序变种）  
3. **LeetCode 315. Count of Smaller Numbers After Self**

---

## 可视化与算法演示

### 动画设计
1. **动态高亮**：  
   - 当前比较的 `i` 和 `j` 以红色标记，对应的 `a[i]` 和 `a[j]` 显示数值。  
   - 满足条件时，连线交叉处显示黄色圆圈，计数器递增。  
2. **步进控制**：支持暂停/继续，调整比较速度。  
3. **像素风格**：  
   - 数组元素以 8-bit 像素方块展示，背景音乐为复古芯片音乐。  
   - 每次发现逆序对时播放“哔”音效，统计完成时播放胜利音效。

### 代码片段（伪代码）
```javascript
// 伪代码：动画核心逻辑
function visualize(a) {
    let count = 0;
    for (let i = 0; i < a.length; i++) {
        for (let j = i + 1; j < a.length; j++) {
            highlight(i, j); // 高亮当前i,j
            if (a[i] >= a[j]) {
                drawCross(i, j); // 绘制交叉点
                count++;
                playSound('beep'); // 触发音效
            }
            wait(200); // 步进延迟
        }
    }
    playSound('victory'); // 完成音效
}
```

---

## 代码实现（题解1）
```cpp
#include <cstdio>
int T, n, s, a[1050];
int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n); s = 0;
        for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        for(int i = 1; i <= n; ++i)
            for(int j = i + 1; j <= n; ++j)
                s += a[i] >= a[j];
        printf("%d\n", s);
    }
    return 0;
}
```

**核心逻辑**：双重循环遍历所有 `i < j` 组合，统计满足 `a[i] >= a[j]` 的对数。

---
处理用时：87.78秒