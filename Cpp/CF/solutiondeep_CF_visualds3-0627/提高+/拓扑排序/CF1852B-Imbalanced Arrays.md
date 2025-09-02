# 题目信息

# Imbalanced Arrays

## 题目描述

Ntarsis has come up with an array $ a $ of $ n $ non-negative integers.

Call an array $ b $ of $ n $ integers imbalanced if it satisfies the following:

- $ -n\le b_i\le n $ , $ b_i \ne 0 $ ,
- there are no two indices $ (i, j) $ ( $ 1 \le i, j \le n $ ) such that $ b_i + b_j = 0 $ ,
- for each $ 1 \leq i \leq n $ , there are exactly $ a_i $ indices $ j $ ( $ 1 \le j \le n $ ) such that $ b_i+b_j>0 $ , where $ i $ and $ j $ are not necessarily distinct.

Given the array $ a $ , Ntarsis wants you to construct some imbalanced array. Help him solve this task, or determine it is impossible.

## 说明/提示

For the first test case, $ b = [1] $ is an imbalanced array. This is because for $ i = 1 $ , there is exactly one $ j $ ( $ j = 1 $ ) where $ b_1 + b_j > 0 $ .

For the second test case, it can be shown that there exists no imbalanced array.

For the third test case, $ a = [0, 1, 0] $ . The array $ b = [-3, 1, -2] $ is an imbalanced array.

- For $ i = 1 $ and $ i = 3 $ , there exists no index $ j $ such that $ b_i + b_j > 0 $ .
- For $ i = 2 $ , there is only one index $ j = 2 $ such that $ b_i + b_j > 0 $ ( $ b_2 + b_2 = 1 + 1 = 2 $ ).

 Another possible output for the third test case could be $ b = [-2, 1, -3] $ .

## 样例 #1

### 输入

```
5
1
1
4
1 4 3 4
3
0 1 0
4
4 3 2 1
3
1 3 1```

### 输出

```
YES
1 
NO
YES
-3 1 -2 
YES
4 2 -1 -3 
YES
-1 3 -1```

# AI分析结果



**唯一算法分类**  
贪心 + 双指针  

---

### 题解思路与算法要点  
#### 核心思路  
**排序后贪心构造**：  
1. **极端值优先**：将数组排序后，每次优先处理当前剩余元素中的最大值或最小值，通过双指针逐步确定每个位置的绝对值。  
2. **维护调整变量**：通过 `add` 变量记录已确定的正数对后续元素的贡献（每个正数会导致后续所有元素的 `a` 值减 1）。  
3. **合法性检查**：若无法找到合法极端值（当前 `a_i` 应为剩余长度或 0），则直接判定无解。  

#### 解决难点  
- **无相反数约束**：通过排序后绝对值从大到小赋值，确保每个值的符号唯一。  
- **动态调整 `a` 值**：利用 `add` 变量避免每次显式修改剩余元素的 `a` 值，提高效率。  
- **双指针决策**：左指针处理负数（`a_i=0`），右指针处理正数（`a_i=剩余长度`）。  

#### 可视化设计  
1. **动画流程**：  
   - **排序阶段**：展示原数组 `a` 的排序过程，突出最大值和最小值。  
   - **双指针移动**：高亮左指针（红色）和右指针（蓝色），显示当前处理的 `a_i` 值和对应条件（0 或剩余长度）。  
   - **赋值与调整**：显示确定的 `b` 值（绿色为负，黄色为正），并动态更新 `add` 变量。  
   - **合法性检查**：若无法满足条件，播放失败音效并终止。  
2. **复古像素风格**：  
   - **Canvas 网格**：将数组元素绘制为像素块，指针移动时添加闪烁动画。  
   - **音效触发**：成功赋值时播放 8-bit 上升音调，失败时播放低沉音效。  
3. **交互控制**：支持暂停/继续、单步执行，速度调节（1x/2x/4x）。  

---

### 题解评分（≥4星）  
1. **dark_moon（5星）**  
   - **亮点**：思路清晰，代码简洁，维护 `add` 变量优化时间复杂度至 O(n)。  
   - **关键代码**：双指针逻辑与动态调整 `add` 的实现。  
   ```cpp  
   if (s[l].a + add == 0) {  
       s[l].b = -i;  
       l++;  
   } else if (now - (s[r].a + add) == 0) {  
       s[r].b = i;  
       add--;  
       r--;  
   }  
   ```  
2. **Zooping（4星）**  
   - **亮点**：类似双指针逻辑，代码可读性高，维护 `jian` 变量等效于 `add`。  
   - **关键代码**：  
   ```cpp  
   if (a[l].num + jian == 0) {  
       b[a[l].wei] = -cnt;  
       l++;  
   } else if (a[r].num + jian == cnt) {  
       b[a[r].wei] = cnt;  
       jian--;  
       r--;  
   }  
   ```  
3. **phil071128（4星）**  
   - **亮点**：倒序枚举维护 `x`（正数计数）和 `y`（负数计数），思路新颖。  
   - **关键代码**：  
   ```cpp  
   if (t[x + i]) {  
       b[i] = +i;  
       x++;  
   } else if (t[n - i - y]) {  
       b[i] = -i;  
       y++;  
   }  
   ```  

---

### 最优技巧提炼  
1. **绝对值排序**：通过排序将问题转化为贪心决策，确保每一步处理当前最大可能的正数或最小可能的负数。  
2. **变量维护代替显式修改**：用 `add` 或 `jian` 记录已处理正数的数量，避免显式修改剩余元素的 `a` 值。  
3. **双指针合法性检查**：每一步仅需判断左右指针的当前值是否符合极端条件（0 或剩余长度）。  

---

### 相似题目推荐  
1. **P1090 [NOIP2004 提高组] 合并果子**（贪心 + 优先队列）  
2. **P1106 删数问题**（贪心 + 单调栈）  
3. **P2123 皇后游戏**（构造 + 排序策略）  

---

### 核心代码实现（dark_moon）  
完整代码：  
```cpp  
#include<bits/stdc++.h>  
using namespace std;  
struct Node { int a, b, id; };  
bool cmp(Node a, Node b) { return a.a < b.a; }  

signed main() {  
    int t; cin >> t;  
    while (t--) {  
        int n; cin >> n;  
        Node s[n + 5];  
        for (int i = 1; i <= n; i++)  
            cin >> s[i].a, s[i].id = i;  
        sort(s + 1, s + 1 + n, cmp);  

        int l = 1, r = n, now = n, add = 0, ans[n + 5];  
        bool valid = true;  
        for (int i = n; i >= 1; i--) {  
            if (s[l].a + add == 0 && s[r].a + add == now) { valid = false; break; }  
            if (s[l].a + add == 0) {  
                ans[s[l].id] = -i;  
                l++;  
                now--;  
            } else if (s[r].a + add == now) {  
                ans[s[r].id] = i;  
                r--;  
                now--;  
                add--;  
            } else { valid = false; break; }  
        }  
        if (valid) { /* Output YES and ans */ }  
        else cout << "NO\n";  
    }  
}  
```  

---

### 可视化与游戏化设计  
**复古像素动画示例（伪代码）**  
```javascript  
// Canvas 初始化与网格绘制  
const grid = new PixelGrid(800, 600, 16); // 16x16 像素块  
grid.drawArray(a, {x: 100, y: 300}, "Original Array");  

// 双指针动画  
function animateStep() {  
    highlightPointer(left, "red");  
    highlightPointer(right, "blue");  
    if (checkCondition(left)) {  
        assignValue(left, -currentN);  
        playSound("negative");  
        left++;  
    } else if (checkCondition(right)) {  
        assignValue(right, currentN);  
        playSound("positive");  
        right--;  
        add--;  
    } else {  
        playSound("error");  
        showGameOver();  
    }  
}  
```  

**交互功能**  
- **速度调节**：1x（正常）、2x（快速）、4x（极速）。  
- **AI 自动模式**：自动执行双指针决策，展示构造过程。  
- **积分系统**：每正确构造一个元素得 10 分，失败扣 50 分。

---
处理用时：101.61秒