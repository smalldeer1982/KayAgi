# 题目信息

# Bag of mice

## 题目描述

The dragon and the princess are arguing about what to do on the New Year's Eve. The dragon suggests flying to the mountains to watch fairies dancing in the moonlight, while the princess thinks they should just go to bed early. They are desperate to come to an amicable agreement, so they decide to leave this up to chance.

They take turns drawing a mouse from a bag which initially contains $ w $ white and $ b $ black mice. The person who is the first to draw a white mouse wins. After each mouse drawn by the dragon the rest of mice in the bag panic, and one of them jumps out of the bag itself (the princess draws her mice carefully and doesn't scare other mice). Princess draws first. What is the probability of the princess winning?

If there are no more mice in the bag and nobody has drawn a white mouse, the dragon wins. Mice which jump out of the bag themselves are not considered to be drawn (do not define the winner). Once a mouse has left the bag, it never returns to it. Every mouse is drawn from the bag with the same probability as every other one, and every mouse jumps out of the bag with the same probability as every other one.

## 说明/提示

Let's go through the first sample. The probability of the princess drawing a white mouse on her first turn and winning right away is 1/4. The probability of the dragon drawing a black mouse and not winning on his first turn is 3/4 \* 2/3 = 1/2. After this there are two mice left in the bag — one black and one white; one of them jumps out, and the other is drawn by the princess on her second turn. If the princess' mouse is white, she wins (probability is 1/2 \* 1/2 = 1/4), otherwise nobody gets the white mouse, so according to the rule the dragon wins.

## 样例 #1

### 输入

```
1 3
```

### 输出

```
0.500000000
```

## 样例 #2

### 输入

```
5 5
```

### 输出

```
0.658730159
```

# AI分析结果



---

### **唯一算法分类**  
**动态规划（概率DP）**

---

### **综合分析与结论**  
#### 核心思路与难点  
1. **状态定义**：  
   - 定义 `dp[i][j]` 表示剩余 `i` 只白鼠、`j` 只黑鼠时，公主（先手）获胜的概率。  
   - **难点**：正确推导转移方程，尤其是处理「两人均抽到黑鼠后逃出一只」的分支情况。  

2. **状态转移**：  
   - **直接胜利**：公主抽到白鼠，概率为 `i/(i+j)`。  
   - **共同失败路径**：若公主和龙均抽到黑鼠，需分两种情况：  
     - **逃出白鼠**：概率为 `(j/(i+j)) * ((j-1)/(i+j-1)) * (i/(i+j-2))`，转移至 `dp[i-1][j-2]`。  
     - **逃出黑鼠**：概率为 `(j/(i+j)) * ((j-1)/(i+j-1)) * ((j-2)/(i+j-2))`，转移至 `dp[i][j-3]`。  

3. **初始与边界条件**：  
   - `dp[i][0] = 1`（无黑鼠时公主必赢），`dp[0][j] = 0`（无白鼠时必输）。  

#### 可视化设计思路  
- **动态网格更新**：以网格展示 `dp[i][j]` 的值，当前计算的状态高亮为黄色，依赖的子状态（如 `dp[i-1][j-2]`）高亮为蓝色。  
- **概率分解动画**：演示抽鼠过程时，分步骤显示概率计算（如先抽黑鼠→龙抽黑鼠→逃出白鼠），并配以概率公式浮动提示。  
- **复古像素风格**：  
  - 使用 8-bit 像素风格的老鼠图标，白鼠为白色方块，黑鼠为黑色方块。  
  - 抽选时播放短促音效（如 `beep` 声），逃出老鼠时触发对应颜色闪光特效。  

---

### **题解清单 (≥4星)**  
1. **yingyudou（4.5星）**  
   - **亮点**：递推实现逻辑清晰，边界处理完备，代码简洁易读。  
   - **关键代码**：  
     ```cpp  
     f[i][j] = 1.0*i/(i+j);  
     f[i][j] += j/(i+j) * (j-1)/(i+j-1) * i/(i+j-2) * f[i-1][j-2];  
     if(j>2) f[i][j] += j/(i+j) * (j-1)/(i+j-1) * (j-2)/(i+j-2) * f[i][j-3];  
     ```  

2. **Pathetique（4星）**  
   - **亮点**：记忆化搜索减少无效状态计算，代码可读性高，注释明确。  
   - **关键代码**：  
     ```cpp  
     double dfs(int nw, int nb) {  
         if(nw==0) return 0.0;  
         if(nb==0) return 1.0;  
         double ans = 1.0*nw/(nw+nb);  
         ans += 1.0*nb/(nw+nb) * (nb-1)/(nw+nb-1) * ...;  
         return ans;  
     }  
     ```  

---

### **最优思路提炼**  
1. **状态压缩与转移优化**：  
   - 仅需二维状态 `dp[i][j]`，通过递推或记忆化搜索避免重复计算。  
2. **概率乘法分解**：  
   - 将复杂事件拆分为独立步骤（如抽鼠→再抽鼠→逃出鼠），逐项计算乘积。  

---

### **同类型题与算法套路**  
- **通用解法**：  
  - 多阶段决策问题中，使用概率DP分解事件路径，累加各分支的期望值。  
- **类似题目**：  
  - **P1850 换教室**（概率+最短路）  
  - **P2473 奖励关**（状态压缩DP与期望结合）  
  - **P4550 收集邮票**（期望递推与分阶段计算）  

---

### **推荐洛谷题目**  
1. **P1850**：概率与动态规划结合，需计算最优换课策略。  
2. **P4550**：经典期望问题，分阶段计算收集邮票的期望花费。  
3. **P6835**：概率与图论结合，通过DP计算路径选择的最优期望。  

---

### **个人心得摘录**  
- **踩坑记录**：未处理 `j=2` 时逃出黑鼠的分支导致数组越界（需加 `if(j>2)` 判断）。  
- **调试技巧**：打印 `dp[i][j]` 中间值验证转移逻辑，优先测试边界情况（如 `w=1, b=3`）。  

---

### **可视化与算法演示**  
#### 核心算法流程  
1. **初始化网格**：  
   - 创建 `w x b` 的网格，初始状态 `dp[i][0]=1`（绿色），`dp[0][j]=0`（红色）。  
2. **状态更新动画**：  
   - **递推方向**：从左到右、从下到上填充 `dp[i][j]`，当前单元格高亮为黄色。  
   - **分支展示**：点击单元格时，弹出概率分解公式（如 `i/(i+j) + ...`）。  
3. **复古像素特效**：  
   - **Canvas 绘制**：老鼠用 8x8 像素方块表示，抽选时播放 `8-bit` 音效。  
   - **自动演示模式**：按层扫描网格，每步延迟 500ms，模拟递推过程。  

#### 代码片段（JS 伪代码）  
```javascript  
// 初始化 Canvas 网格  
const grid = initGrid(w, b);  
// 递推填充  
for (let i = 1; i <= w; i++) {  
    for (let j = 1; j <= b; j++) {  
        highlightCell(i, j, 'yellow');  
        dp[i][j] = i / (i + j);  
        if (j >= 2) {  
            dp[i][j] += ...; // 显示分支公式  
        }  
        updateGridCell(i, j, dp[i][j]);  
        playSound('beep');  
    }  
}  
```  

--- 

**答案**  
```cpp  
#include <bits/stdc++.h>  
using namespace std;  

const int N = 1010;  
double dp[N][N];  

int main() {  
    int w, b;  
    cin >> w >> b;  
    // 初始化边界条件  
    for (int i = 1; i <= w; i++) dp[i][0] = 1.0;  
    for (int j = 1; j <= b; j++) dp[0][j] = 0.0;  
    // 递推计算  
    for (int i = 1; i <= w; i++) {  
        for (int j = 1; j <= b; j++) {  
            dp[i][j] = 1.0 * i / (i + j);  
            if (j >= 2) {  
                dp[i][j] += (1.0 * j / (i + j)) * (1.0 * (j - 1) / (i + j - 1))  
                    * (1.0 * i / (i + j - 2)) * dp[i - 1][j - 2];  
            }  
            if (j >= 3) {  
                dp[i][j] += (1.0 * j / (i + j)) * (1.0 * (j - 1) / (i + j - 1))  
                    * (1.0 * (j - 2) / (i + j - 2)) * dp[i][j - 3];  
            }  
        }  
    }  
    printf("%.9lf\n", dp[w][b]);  
    return 0;  
}  
```

---
处理用时：103.55秒