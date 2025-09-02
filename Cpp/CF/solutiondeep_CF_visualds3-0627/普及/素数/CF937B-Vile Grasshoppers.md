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



## 算法分类
**数学优化下的暴力枚举**

---

## 题解思路与核心难点
### 核心思路
**倒序枚举**：从 `y` 开始倒序遍历到 `p+1`，检查每个数是否能被 `2` 到 `min(p, sqrt(i))` 中的任意数整除。若存在这样的因数，则跳过；否则输出该数作为答案。

### 解决难点
1. **时间复杂度优化**：  
   直接遍历 `y` 到 `p` 会导致超时。通过数学观察，若一个数 `i` 有因数，则至少有一个因数 ≤ `sqrt(i)`。因此，只需检查 `2` 到 `min(p, sqrt(i))` 的范围，将复杂度降至 `O(log y * sqrt(y))`，实际因质数间隔较小（约 300），可通过。
   
2. **边界处理**：  
   当 `p ≥ sqrt(y)` 时，只需检查到 `sqrt(i)`；当 `p < sqrt(y)` 时，检查到 `p` 即可。确保不遗漏可能的因数。

---

## 题解评分（≥4星）
### [hu1029282594] ⭐⭐⭐⭐
- **亮点**：明确时间复杂度计算，强调质数间隔的数学特性，代码简洁。
- **心得**：通过讨论意识到质数间隔规律，验证暴力枚举可行性。

### [Jasper08] ⭐⭐⭐⭐
- **亮点**：预处理质数列表优化检查过程，代码结构化清晰。
- **优化**：线性筛法预处理质数，减少冗余计算。

### [E1_de5truct0r] ⭐⭐⭐⭐
- **亮点**：结合时间复杂度公式推导，代码逻辑简洁，注释详细。
- **数学分析**：质数间隔理论确保暴力枚举高效性。

---

## 最优思路提炼
1. **倒序枚举**：从 `y` 开始向下遍历，确保找到第一个合法数即为最大值。
2. **因数检查范围优化**：仅需检查到 `sqrt(i)` 和 `p` 的最小值。
3. **数学特性利用**：质数间隔小，暴力枚举实际运行次数有限。

---

## 同类型题推荐
1. **洛谷 P1217**：[USACO1.5] 回文质数 - 暴力枚举结合数学优化。
2. **洛谷 P3383**：线性筛素数 - 预处理质数的应用。
3. **洛谷 P1075**：质因数分解 - 因数检查与数学优化。

---

## 可视化算法演示
### 核心流程设计
1. **动画效果**：  
   - **像素风格**：用 8-bit 网格展示每个数的检查过程，当前检查的数高亮为绿色，因数检查范围标记为红色。
   - **音效**：每次检查播放短音效，找到答案时播放胜利音效，无解时播放失败音效。
   
2. **交互设计**：  
   - **步进控制**：支持暂停/继续、单步执行、调整速度。
   - **参数输入**：允许用户输入 `p` 和 `y`，观察不同用例下的执行过程。

### 关键步骤说明
1. **倒序枚举**：从 `y` 到 `p+1` 遍历，每个数用绿色方块表示。
2. **因数检查**：对当前数 `i`，遍历 `2` 到 `min(p, sqrt(i))` 的因数，红色方块标记检查位置。
3. **结果反馈**：找到合法数时，绿色方块闪烁并显示结果；遍历结束无解则显示 `-1`。

---

## 核心代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;

int main() {
    int p, y;
    cin >> p >> y;
    for (int i = y; i > p; i--) {
        bool valid = true;
        for (int j = 2; j * j <= i && j <= p; j++) {
            if (i % j == 0) {
                valid = false;
                break;
            }
        }
        if (valid) {
            cout << i << endl;
            return 0;
        }
    }
    cout << -1 << endl;
    return 0;
}
```

---

## 个人心得摘录
- **hu1029282594**：“质数间隔理论是本题暴力通过的关键，避免了对大范围的无效遍历。”
- **Jasper08**：“预处理质数虽增加代码复杂度，但显著减少重复计算，适合大 `p` 场景。”

---

## 复古游戏化设计
1. **像素风格**：  
   - 使用 16 色调色板，绿色表示当前检查数，红色表示因数范围。
   - Canvas 绘制网格，每个数对应一个方块，动态更新颜色。

2. **音效系统**：  
   - **检查音效**：每次因数检查播放 `beep` 声。
   - **成功音效**：8-bit 风格胜利音乐。
   - **失败音效**：低音 `buzz` 声。

3. **自动演示模式**：  
   - AI 自动执行倒序检查，展示算法决策流程。
   - 可调节速度，观察不同速度下的检查过程。

---
处理用时：116.57秒