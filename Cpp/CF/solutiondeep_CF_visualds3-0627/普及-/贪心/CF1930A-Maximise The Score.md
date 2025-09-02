# 题目信息

# Maximise The Score

## 题目描述

There are $ 2n $ positive integers written on a whiteboard. Being bored, you decided to play a one-player game with the numbers on the whiteboard.

You start with a score of $ 0 $ . You will increase your score by performing the following move exactly $ n $ times:

- Choose two integers $ x $ and $ y $ that are written on the whiteboard.
- Add $ \min(x,y) $ to your score.
- Erase $ x $ and $ y $ from the whiteboard.

Note that after performing the move $ n $ times, there will be no more integers written on the whiteboard.

Find the maximum final score you can achieve if you optimally perform the $ n $ moves.

## 说明/提示

In the first test case, you can only make one move. You select $ x=2 $ and $ y=3 $ , and your score will be $ \min(x,y)=2 $ .

In the second test case, the following is a sequence of moves that achieves a final score of $ 2 $ :

- In the first move, select $ x=1 $ and $ y=1 $ . Then, add $ \min(x,y)=1 $ to the score. After erasing $ x $ and $ y $ , the integers left on the whiteboard are $ 1 $ and $ 2 $ .
- In the second move, select $ x=1 $ and $ y=2 $ . Then, add $ \min(x,y)=1 $ to the score. After removing $ x $ and $ y $ , no more integers will be left on the whiteboard.

 It can be proved that it is not possible to get a score greater than $ 2 $ .In the third test case, you will perform the move thrice, adding $ 1 $ to the score each time.

## 样例 #1

### 输入

```
3
1
2 3
2
1 1 2 1
3
1 1 1 1 1 1```

### 输出

```
2
2
3```

# AI分析结果



### 综合分析与结论

**题目核心**：给定 $2n$ 个数，每次选两数，取较小值累加得分，求最大得分。  
**关键贪心策略**：将数组升序排序后，取所有奇数位置的数之和。  
**难点**：如何证明排序后取奇数位的策略是最优的？  
- **证明思路**：每次选取相邻两数，确保较大的数被保留用于后续配对，从而保证每次的最小值尽可能大。交换任意两对的配对方式会得到更差的结果。  
**可视化设计**：  
- **动画方案**：排序后的数组以相邻两数为组，每组高亮较小值，逐步累加。  
- **复古像素风格**：用不同颜色标记当前操作对，音效提示得分增加。  
- **交互功能**：步进控制、自动播放、速度调节，对比不同配对策略的得分差异。

---

### 题解清单（评分≥4星）

1. **Little_x_starTYJ（5星）**  
   - **亮点**：详细推导贪心策略，解释排序后奇数位和的数学依据，代码简洁规范。  
   - **引用**：“将最小的两个数同时操作，避免浪费较大的数。”

2. **zhouchuer（4星）**  
   - **亮点**：代码清晰，注释明确，强调多组数据的初始化处理。  
   - **引用**：“注意初始化，避免上一组数据影响。”

3. **Cold_Eyes_bystander（4星）**  
   - **亮点**：用“同归于尽”形象描述贪心策略，代码逻辑直接体现核心思想。  
   - **引用**：“最小的数必须被利用，与次小的配对。”

---

### 最优思路与技巧提炼

1. **贪心核心**：排序后相邻配对，取每组较小值。  
   - **数学依据**：排序后的数组 $a_1 \leq a_2 \leq \dots \leq a_{2n}$，最优和为 $\sum_{i=1}^n a_{2i-1}$。  
2. **实现关键**：排序后遍历奇数位累加。  
3. **调试教训**：数组需开 $2n$ 大小（如题解 `BJqxszx_zhuyukun` 的提醒）。

---

### 同类型题目与算法套路

1. **区间调度**：选择不重叠区间使数量最多（按结束时间排序）。  
2. **最小代价问题**：如 Huffman 编码，每次合并最小两节点。  
3. **配对问题**：如两数之和最小化最大值（排序后首尾配对）。

**推荐题目**：  
- 洛谷 P1223：排队接水（贪心排序）  
- 洛谷 P1094：纪念品分组（相邻配对）  
- 洛谷 P5019：铺设道路（区间覆盖贪心）

---

### 个人心得摘录

- **Cold_Eyes_bystander**：  
  “最小的数一定会加入分数，和第二小的同归于尽。”  
  **总结**：最小数必须尽早使用，避免被更大的数“浪费”。

- **BJqxszx_zhuyukun**：  
  “数组要开 $2$ 倍才能过（别问我怎么知道的）。”  
  **教训**：输入规模需仔细核对，避免越界。

---

### 核心代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, ans = 0;
        cin >> n;
        vector<int> a(2 * n);
        for (int &x : a) cin >> x;
        sort(a.begin(), a.end());
        for (int i = 0; i < 2 * n; i += 2) ans += a[i];
        cout << ans << endl;
    }
    return 0;
}
```

---

### 可视化设计要点（复古像素风格）

1. **Canvas 绘制**：  
   - 数字以像素方块显示，排序过程动态交换位置。  
   - 当前操作对高亮为红色，得分数字闪烁绿色。  
2. **音效设计**：  
   - 配对成功：8-bit 短音效。  
   - 得分累加：音调逐渐升高。  
3. **自动演示**：  
   - AI 按步选择相邻两数，实时显示得分。  
4. **交互功能**：  
   - 速度滑块调节动画速度，暂停/继续按钮。  
   - 对比模式：允许用户手动配对，对比得分差异。

**示例动画流程**：  
- 初始乱序数组 → 排序动画 → 逐步高亮配对 → 显示累加得分。

---
处理用时：115.45秒