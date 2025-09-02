# 题目信息

# Vile Grasshoppers

## 题目描述

The weather is fine today and hence it's high time to climb the nearby pine and enjoy the landscape.

The pine's trunk includes several branches, located one above another and numbered from $ 2 $ to $ y $ . Some of them (more precise, from $ 2 $ to $ p $ ) are occupied by tiny vile grasshoppers which you're at war with. These grasshoppers are known for their awesome jumping skills: the grasshopper at branch $ x $ can jump to branches ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF937B/e256171e16de0ce2bc4667496d6c5befd611ffc8.png).

Keeping this in mind, you wisely decided to choose such a branch that none of the grasshoppers could interrupt you. At the same time you wanna settle as high as possible since the view from up there is simply breathtaking.

In other words, your goal is to find the highest branch that cannot be reached by any of the grasshoppers or report that it's impossible.

## 说明/提示

In the first sample case grasshopper from branch $ 2 $ reaches branches $ 2 $ , $ 4 $ and $ 6 $ while branch $ 3 $ is initially settled by another grasshopper. Therefore the answer is $ 5 $ .

It immediately follows that there are no valid branches in second sample case.

## 样例 #1

### 输入

```
3 6
```

### 输出

```
5
```

## 样例 #2

### 输入

```
3 4
```

### 输出

```
-1
```

# AI分析结果



---

### **唯一算法分类**  
**暴力枚举 + 质数间隔优化**

---

### **综合分析与结论**  
#### **核心思路**  
题目要求找到最大的不被 `2~p` 中任意数整除的 `x (x ∈ [2, y])`。所有题解均采用以下核心逻辑：  
1. **倒序枚举**：从 `y` 开始向下枚举，保证找到的第一个符合条件的数即为最大值。  
2. **快速判断**：对每个枚举的 `x`，只需检查是否能被 `2~min(p, sqrt(x))` 中的数整除，避免冗余计算。  
3. **质数间隔理论**：由于相邻质数的间隔较小（如不超过 300），实际需要枚举的 `x` 的个数远低于 `y-p`，时间复杂度可接受。

#### **解决难点**  
1. **时间复杂度优化**：通过限制枚举范围和利用质数间隔理论，将原本看似 `O(y-p)*O(sqrt(y))` 的时间复杂度降低至可接受范围。  
2. **边界处理**：正确处理 `x ≤ p` 的情况（此时一定不满足条件，直接输出 `-1`）。

#### **可视化设计思路**  
- **变量高亮**：  
  - 绿色方块表示当前枚举的 `x`，红色方块表示正在检查的因数 `i`。  
  - 若 `x % i == 0`，显示红色闪烁动画；若所有 `i` 检查通过，显示绿色高亮并播放成功音效。  
- **步进控制**：允许用户手动点击“下一步”观察每个 `x` 的检查过程，或自动播放（速度可调）。  
- **像素风格**：  
  - 使用 8-bit 风格的网格布局，每行表示一个 `x`，每列表示一个因数 `i`。  
  - 背景音乐采用经典 FC 游戏的循环音轨，音效使用短促的“哔”声提示检查结果。

---

### **题解清单 (≥4星)**  
1. **作者：Jasper08 (⭐⭐⭐⭐⭐)**  
   - **关键亮点**：使用线性筛法预处理 `2~min(p, sqrt(y))` 的质数，进一步优化检查速度。代码可读性强，注释清晰，时间复杂度最优。  
   - **代码片段**：  
     ```cpp  
     void get_primes(int n) {  
         st[0] = st[1] = 1;  
         for (int i = 2; i <= n; ++i) {  
             if (!st[i]) primes[cnt++] = i;  
             for (int j = 0; primes[j] <= n/i && j < cnt; ++j) {  
                 st[i*primes[j]] = 1;  
                 if (i % primes[j] == 0) break;  
             }  
         }  
     }  
     ```  

2. **作者：hu1029282594 (⭐⭐⭐⭐)**  
   - **关键亮点**：通过质数间隔理论解释时间复杂度，代码简洁高效。  
   - **个人心得**：“要不是看到讨论，我永远想不到这样能过”——强调质数间隔的理论突破。  

3. **作者：User757711 (⭐⭐⭐⭐)**  
   - **关键亮点**：代码结构清晰，逻辑直白，适合快速理解核心思路。  

---

### **最优思路与技巧提炼**  
1. **倒序枚举**：从 `y` 向下遍历，找到第一个满足条件的数即可终止。  
2. **快速因数检查**：仅需检查 `2~min(p, sqrt(x))` 的范围。  
3. **质数预处理**（可选）：对 `2~min(p, sqrt(y))` 预处理质数，减少检查次数。

---

### **同类型题与算法套路**  
1. **最大不可达数问题**：如 [CF12B Correct Solution?](https://www.luogu.com.cn/problem/CF12B)。  
2. **质数间隔优化**：如 [洛谷 P1217 [USACO1.5] 回文质数](https://www.luogu.com.cn/problem/P1217)。  
3. **暴力枚举优化**：如 [洛谷 P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)。

---

### **推荐相似题目**  
1. **CF230B - T-primes**：判断一个数是否为平方质数。  
2. **P3912 素数个数**：统计大范围内的素数数量。  
3. **P1865 A % B Problem**：区间质数查询，结合筛法优化。

---

### **个人心得摘录**  
- **hu1029282594**：“真坑啊！先贴代码”——强调思维突破的重要性。  
- **Jasper08**：“线性筛法预处理质数”——展示预处理对性能的提升。  

---

### **代码实现（核心逻辑）**  
```cpp  
// 作者：Jasper08 的预处理质数版本  
#include <bits/stdc++.h>  
using namespace std;  
const int N = 5e4+10;  
int primes[N], cnt;  
bitset<N> st;  

void get_primes(int n) {  
    st[0] = st[1] = 1;  
    for (int i = 2; i <= n; ++i) {  
        if (!st[i]) primes[cnt++] = i;  
        for (int j = 0; primes[j] <= n/i && j < cnt; ++j) {  
            st[i*primes[j]] = 1;  
            if (i % primes[j] == 0) break;  
        }  
    }  
}  

int main() {  
    int p, y;  
    scanf("%d%d", &p, &y);  
    int t = min(p, (int)sqrt(y));  
    get_primes(t);  
    for (int i = y; i > p; --i) {  
        bool ok = true;  
        for (int j = 0; j < cnt; ++j) {  
            if (i % primes[j] == 0) {  
                ok = false;  
                break;  
            }  
        }  
        if (ok) {  
            printf("%d\n", i);  
            return 0;  
        }  
    }  
    puts("-1");  
    return 0;  
}  
```  

---

### **可视化与算法演示**  
#### **动画流程**  
1. **初始化**：显示 `y` 到 `p` 的垂直数轴，每个数用像素方块表示。  
2. **倒序扫描**：绿色方块从 `y` 开始向下移动，每次检查当前数 `x`。  
3. **因数检查**：  
   - 红色方块遍历 `2~min(p, sqrt(x))`，若 `x % i == 0`，显示红色闪烁。  
   - 若所有检查通过，绿色方块变为金色，播放胜利音效。  
4. **结束条件**：若扫描到 `p+1` 仍未找到，显示灰色方块和失败音效。  

#### **交互设计**  
- **控制面板**：启动/暂停、步进、速度滑块。  
- **音效触发**：  
  - 检查失败：短促“哔”声。  
  - 检查成功：8-bit 风格胜利旋律。  
- **自动演示模式**：AI 自动运行，模拟“贪吃蛇”式路径扫描。  

#### **复古风格实现**  
```javascript  
// 伪代码：Canvas 绘制核心逻辑  
function drawPixel(x, y, color) {  
    ctx.fillStyle = color;  
    ctx.fillRect(x * 10, y * 10, 8, 8);  
}  

function animateCheck(x, i) {  
    drawPixel(x, 0, "#00FF00"); // 当前 x 绿色  
    drawPixel(i, 1, "#FF0000"); // 当前因数 i 红色  
    if (x % i === 0) playSound("error");  
}  
```

---
处理用时：87.79秒