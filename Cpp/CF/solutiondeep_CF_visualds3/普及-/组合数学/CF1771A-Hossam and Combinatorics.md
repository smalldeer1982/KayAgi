# 题目信息

# Hossam and Combinatorics

## 题目描述

Hossam woke up bored, so he decided to create an interesting array with his friend Hazem.

Now, they have an array $ a $ of $ n $ positive integers, Hossam will choose a number $ a_i $ and Hazem will choose a number $ a_j $ .

Count the number of interesting pairs $ (a_i, a_j) $ that meet all the following conditions:

- $ 1 \le i, j \le n $ ;
- $ i \neq j $ ;
- The absolute difference $ |a_i - a_j| $ must be equal to the maximum absolute difference over all the pairs in the array. More formally, $ |a_i - a_j| = \max_{1 \le p, q \le n} |a_p - a_q| $ .

## 说明/提示

In the first example, the two ways are:

- Hossam chooses the fourth number $ 8 $ and Hazem chooses the fifth number $ 1 $ .
- Hossam chooses the fifth number $ 1 $ and Hazem chooses the fourth number $ 8 $ .

In the second example, the four ways are:

- Hossam chooses the second number $ 2 $ and Hazem chooses the sixth number $ 10 $ .
- Hossam chooses the sixth number $ 10 $ and Hazem chooses the second number $ 2 $ .
- Hossam chooses the fifth number $ 2 $ and Hazem chooses the sixth number $ 10 $ .
- Hossam chooses the sixth number $ 10 $ and Hazem chooses the fifth number $ 2 $ .

## 样例 #1

### 输入

```
2
5
6 2 3 8 1
6
7 2 8 3 2 10```

### 输出

```
2
4```

# AI分析结果


### 💡 Kay的C++算法解析：Hossam and Combinatorics 深入学习指南 💡

#### **题目解读与核心算法识别**
✨ **本题主要考察**：`编程技巧应用`（极值统计与组合计数）  
🗣️ **初步分析**：
> 解决本题的关键在于**快速定位数组极值并高效计数**。就像在迷宫中同时寻找最高点和最低点一样，我们需要：
> - 遍历数组时**同步记录**最大值、最小值及其出现次数  
> - 通过数学推导得出满足条件的配对数量公式  
> 
> **核心难点**在于区分两种场景：  
> 1. 全数组元素相同时：所有配对均满足条件  
> 2. 存在极差时：仅最大值与最小值的配对有效  
> 
> **可视化设计思路**：  
> 采用像素风格热力图展示数组（图1），动态高亮极值点并连线配对。当自动播放时，算法像"贪吃蛇AI"扫描数组：  
> - 红光闪烁标记当前扫描元素  
> - 绿/蓝像素块分别表示最小/最大值  
> - 配对成功时触发"叮"音效+金色闪光  

![](https://via.placeholder.com/400x200?text=图1：像素化数组热力图+极值标记动画)

---

#### **精选优质题解参考**
**题解：极值统计与组合计数（作者：Kay）**  
* **点评**：  
  解法采用**单次遍历完成极值统计**，避免不必要排序（时间复杂度O(n)优于O(n log n)）。代码中：  
  - `max_val/min_val` 动态更新逻辑清晰  
  - `cnt_max/cnt_min` 计数同步进行  
  - 分支处理（全等数组 vs 极差数组）严谨  
  亮点在于**空间复杂度O(1)** 且边界处理完备，可直接用于竞赛。

---

#### **核心难点辨析与解题策略**
1. **难点：极值动态更新与计数同步**  
   * **分析**：遍历时需同时判断"大于当前最大值"/"等于当前最大值"等四种情况。代码通过`if-else if`链保证互斥条件判断  
   * 💡 **学习笔记**：极值统计需在遍历中维护"当前已知极值"状态  

2. **难点：全等数组的特殊处理**  
   * **分析**：当`max_val == min_val`时，任意两个不同位置的元素都满足条件，总对数=n(n-1)  
   * 💡 **学习笔记**：注意数学公式的物理意义而非机械套用  

3. **难点：配对数的组合推导**  
   * **分析**：非全等数组中，每个最小值可与每个最大值组成**2个有序对**（(min_pos,max_pos)和(max_pos,min_pos)）  
   * 💡 **学习笔记**：组合计数需考虑顺序相关性  

##### ✨ 解题技巧总结
- **技巧1 状态同步更新**：单次遍历完成多指标统计  
- **技巧2 数学建模**：将问题转化为极值出现频次的计算  
- **技巧3 边界完备性**：显式处理全等数组的特殊情况  

---

#### **C++核心代码实现赏析**
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<long long> a(n);
        long long max_val = -1e18, min_val = 1e18;
        long long cnt_min = 0, cnt_max = 0;

        // 核心遍历：同步更新极值与计数
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            // 最大值检测与更新
            if (a[i] > max_val) {
                max_val = a[i];
                cnt_max = 1;
            } else if (a[i] == max_val) {
                cnt_max++;
            }
            // 最小值检测与更新
            if (a[i] < min_val) {
                min_val = a[i];
                cnt_min = 1;
            } else if (a[i] == min_val) {
                cnt_min++;
            }
        }

        // 结果输出分支
        if (max_val == min_val) {
            cout << 1LL * n * (n - 1) << '\n';
        } else {
            cout << 2LL * cnt_min * cnt_max << '\n';
        }
    }
    return 0;
}
```

**代码解读**：  
> 1. **动态极值维护**：  
>    - `max_val`/`min_val`初始化为理论极值（±10¹⁸）  
>    - 当`a[i] > max_val`时重置计数（`cnt_max=1`）  
>    - 遇等值时递增计数（`else if`分支）  
> 
> 2. **组合数计算**：  
>    - 全等数组：任意有序对均有效 → n(n-1)  
>    - 极差数组：最小值点×最大值点×2（有序对）  
> 
> 3. **类型安全**：`1LL`强制转换避免int溢出  

---

#### **算法可视化：像素动画演示**
![](https://via.placeholder.com/600x300?text=图2：极值扫描像素动画示意图)  
* **主题**：8-bit风格《极值猎人》  
* **核心交互**：  
  1. **初始化**：像素网格化数组（图2），控制面板含调速滑块  
  2. **扫描阶段**：  
     - 红光扫描器逐格移动（步进音效）  
     - 遇新最大值→方块变蓝+“升级”音效  
     - 遇新最小值→方块变绿+“降级”音效  
  3. **配对阶段**：  
     - 绿/蓝方块自动连线（金色光束）  
     - 显示配对公式 `2 × ${cnt_min} × ${cnt_max}`  
     - 触发“胜利”音效+BGM变调  
* **技术实现**：  
  - Canvas绘制动态热力网格  
  - 音效绑定：Web Audio API播放8-bit音效  
  - 自动演示模式：setInterval控制扫描速度  

---

#### **拓展练习与相似问题思考**
1. **洛谷 P1102** - A-B数对  
   → 强化极差配对思想的变式应用  
2. **洛谷 P1631** - 序列合并  
   → 多序列极值协同处理的进阶训练  
3. **洛谷 P1908** - 逆序对  
   → 结合分治思想的计数问题拓展  

---

#### **学习心得与经验分享**
> 本次分析的题解中未发现明确的作者个人心得分享部分。

--- 
**Kay的结语**：  
掌握极值统计与组合计数的核心在于理解**状态同步维护**的思想。就像同时追踪天空的最高飞鸟和最低云朵，高效算法需要我们在一次遍历中捕捉多重信息。尝试用可视化工具模拟本文的像素动画，你会对动态更新产生更直觉的理解！ 🚀

---
处理用时：212.34秒