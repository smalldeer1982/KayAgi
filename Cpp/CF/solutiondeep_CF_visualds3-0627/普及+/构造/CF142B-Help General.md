# 题目信息

# Help General

## 题目描述

Once upon a time in the Kingdom of Far Far Away lived Sir Lancelot, the chief Royal General. He was very proud of his men and he liked to invite the King to come and watch drill exercises which demonstrated the fighting techniques and tactics of the squad he was in charge of. But time went by and one day Sir Lancelot had a major argument with the Fairy Godmother (there were rumors that the argument occurred after the general spoke badly of the Godmother's flying techniques. That seemed to hurt the Fairy Godmother very deeply).

As the result of the argument, the Godmother put a rather strange curse upon the general. It sounded all complicated and quite harmless: "If the squared distance between some two soldiers equals to $ 5 $ , then those soldiers will conflict with each other!"

The drill exercises are held on a rectangular $ n×m $ field, split into $ nm $ square $ 1×1 $ segments for each soldier. Thus, the square of the distance between the soldiers that stand on squares $ (x_{1},y_{1}) $ and $ (x_{2},y_{2}) $ equals exactly $ (x_{1}-x_{2})^{2}+(y_{1}-y_{2})^{2} $ . Now not all $ nm $ squad soldiers can participate in the drill exercises as it was before the Fairy Godmother's curse. Unless, of course, the general wants the soldiers to fight with each other or even worse... For example, if he puts a soldier in the square $ (2,2) $ , then he cannot put soldiers in the squares $ (1,4) $ , $ (3,4) $ , $ (4,1) $ and $ (4,3) $ — each of them will conflict with the soldier in the square $ (2,2) $ .

Your task is to help the general. You are given the size of the drill exercise field. You are asked to calculate the maximum number of soldiers that can be simultaneously positioned on this field, so that no two soldiers fall under the Fairy Godmother's curse.

## 说明/提示

In the first sample test Sir Lancelot can place his 4 soldiers on the $ 2×4 $ court as follows (the soldiers' locations are marked with gray circles on the scheme):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF142B/0d23ce3839b0ce156cddd9663617e134809111ae.png)In the second sample test he can place 6 soldiers on the $ 3×4 $ site in the following manner:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF142B/57bf2bd762016d87a2641e15975b3acd653786ad.png)

## 样例 #1

### 输入

```
2 4
```

### 输出

```
4```

## 样例 #2

### 输入

```
3 4
```

### 输出

```
6```

# AI分析结果



### 算法分类
**数学建模/分类讨论**（核心在于数学规律推导与特殊情况的分类处理）

---

### 题解思路、算法要点与解决难点
#### 核心思路
1. **数学规律推导**：  
   通过棋盘染色法发现，当行列均 ≥3 时，最大放置数为 `(n*m +1)/2`（黑白格交替放置）。
2. **特殊情况处理**：  
   - **n=1 或 m=1**：全放满（无冲突可能）。
   - **n=2 或 m=2**：以4列为一组循环放置，处理余数列。

#### 解决难点
- **n=2 的构造**：需精确处理余数列（如余1列放2个，余2列放4个）。
- **二分图证明**：需理解棋盘染色后形成的二分图性质，证明最大独立集为半数格子。

---

### 题解评分（≥4星）
1. **a___（★★★★★）**  
   - **亮点**：严谨的二分图证明，覆盖所有边界条件，代码清晰。
2. **封禁用户（★★★★☆）**  
   - **亮点**：数学规律与特判结合，代码简洁但缺乏严格证明。
3. **xiaohuang（★★★★☆）**  
   - **亮点**：直观构造示意图，分情况讨论明确。

---

### 最优思路或技巧提炼
1. **棋盘染色法**：  
   将棋盘视为国际象棋棋盘，交替放置士兵，保证任何两个士兵不在同一颜色区域。
2. **n=2 的分组构造**：  
   每4列为一组，按 `1100` 模式循环填充，余数列按规则补全。
3. **数学公式统一**：  
   一般情况公式 `(n*m +1)/2` 覆盖大部分场景，仅需特判极小棋盘。

---

### 同类型题或类似算法套路
- **棋盘放置问题**：如国际象棋中的皇后、车等棋子的最大独立集问题。
- **二分图应用**：最大匹配、最小顶点覆盖等问题的图论解法。

---

### 推荐相似题目
1. **P1219 [USACO1.5] 八皇后**（棋盘放置问题）  
2. **P1896 [SCOI2005] 互不侵犯**（状压DP与棋盘约束）  
3. **P3355 骑士共存问题**（国际象棋马放置的图论建模）

---

### 个人心得摘录
> "当考试中无法快速推导严格证明时，通过构造小样例找规律是高效策略。" —— 封禁用户  
> "二分图的最大独立集性质是解决此类棋盘问题的通用武器，但需注意特殊情况的独立处理。" —— a___

---

### 可视化与算法演示
#### 动画方案
1. **棋盘动态染色**：  
   - 使用Canvas绘制棋盘，黑色格子高亮显示当前可放置位置。
   - 步进演示：每次放置一个士兵后，用红色标记其攻击范围。
2. **n=2 的特例演示**：  
   - 按4列分组填充，余数列用不同颜色区分填充规则。
3. **音效与交互**：  
   - **放置音效**：8-bit风格“滴”声提示成功放置。
   - **错误提示**：放置冲突时播放低音警告。

#### 复古游戏化设计
- **像素风格棋盘**：使用16色调色板（如#000000、#FFFFFF、#FF0000）。
- **自动演示模式**：AI按最优策略自动填充棋盘，速度可调。
- **关卡设计**：  
  - 第1关：3x3棋盘（验证公式）。  
  - 第2关：2x5棋盘（练习分组构造）。  
  - 第3关：5x5棋盘（综合测试）。

```javascript
// 伪代码示例：棋盘填充动画
function drawBoard(n, m) {
  const canvas = document.getElementById('board');
  const ctx = canvas.getContext('2d');
  // 绘制棋盘网格
  for (let i = 0; i < n; i++) {
    for (let j = 0; j < m; j++) {
      ctx.fillStyle = (i + j) % 2 === 0 ? '#000000' : '#FFFFFF';
      ctx.fillRect(j * 20, i * 20, 20, 20);
    }
  }
}
// 触发音效
function playSound(type) {
  const sound = type === 'success' ? 'beep.wav' : 'error.wav';
  new Audio(sound).play();
}
```

---

### 关键代码实现
#### 核心逻辑片段
```cpp
if (n == 1 || m == 1) {
    cout << max(n, m); // 特判单行/单列
} else if (n == 2 || m == 2) {
    int k = max(n, m);
    if (k % 4 == 1 || k % 4 == 3) cout << k + 1;
    else if (k % 4 == 2) cout << k + 2;
    else cout << k; // n=2 的复杂特判
} else {
    cout << (n * m + 1) / 2; // 通用公式
}
```

#### 完整代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    if (n > m) swap(n, m);
    if (n == 1) cout << m;
    else if (n == 2) {
        if (m % 4 == 1 || m % 4 == 3) cout << m + 1;
        else if (m % 4 == 2) cout << m + 2;
        else cout << m;
    } else {
        cout << (n * m + 1) / 2;
    }
    return 0;
}
```

---
处理用时：107.48秒