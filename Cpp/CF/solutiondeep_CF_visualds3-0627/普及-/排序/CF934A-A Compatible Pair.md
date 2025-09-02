# 题目信息

# A Compatible Pair

## 题目描述

Nian is a monster which lives deep in the oceans. Once a year, it shows up on the land, devouring livestock and even people. In order to keep the monster away, people fill their villages with red colour, light, and cracking noise, all of which frighten the monster out of coming.

Little Tommy has $ n $ lanterns and Big Banban has $ m $ lanterns. Tommy's lanterns have brightness $ a_{1},a_{2},...,a_{n} $ , and Banban's have brightness $ b_{1},b_{2},...,b_{m} $ respectively.

Tommy intends to hide one of his lanterns, then Banban picks one of Tommy's non-hidden lanterns and one of his own lanterns to form a pair. The pair's brightness will be the product of the brightness of two lanterns.

Tommy wants to make the product as small as possible, while Banban tries to make it as large as possible.

You are asked to find the brightness of the chosen pair if both of them choose optimally.

## 说明/提示

In the first example, Tommy will hide $ 20 $ and Banban will choose $ 18 $ from Tommy and $ 14 $ from himself.

In the second example, Tommy will hide $ 3 $ and Banban will choose $ 2 $ from Tommy and $ 1 $ from himself.

## 样例 #1

### 输入

```
2 2
20 18
2 14
```

### 输出

```
252
```

## 样例 #2

### 输入

```
5 3
-1 0 1 2 3
-1 0 1
```

### 输出

```
2
```

# AI分析结果



## 算法分类
无特定算法分类（暴力枚举）

---

## 综合分析与结论

### 核心思路
题目要求确定Tommy隐藏一个灯笼后，Banban能选出的最大乘积的最小值。暴力枚举每个可能的隐藏灯笼，计算剩余灯笼与Banban灯笼的所有乘积，取最大值后比较所有隐藏情况的最小值。这是本题的最优解，时间复杂度为$O(n^2 m)$，在数据规模较小时可行。

### 解决难点
- **双方策略的博弈**：Tommy需预判Banban的选择策略，找到隐藏后最不利情况的最小值。
- **乘积极值的快速计算**：通过三层循环枚举所有可能情况，确保覆盖所有组合。
- **数据范围适配性**：$n$和$m$均$\leq 50$，暴力枚举时间复杂度为$10^5$级别，完全可行。

### 可视化设计思路
1. **动画方案**：  
   - **网格展示**：将Tommy的灯笼排列为一列，Banban的灯笼为另一列。每次隐藏一个灯笼（标记为灰色），高亮剩余灯笼与Banban灯笼的配对过程。  
   - **颜色标记**：当前隐藏的灯笼用红色标记，正在计算的配对用绿色，最大值配对用黄色。  
   - **动态更新**：每隐藏一个灯笼，动态计算并显示最大值，最终结果通过比较所有隐藏情况得出。

2. **复古像素风格**：  
   - **8位色块**：灯笼用不同颜色像素块表示，隐藏操作伴随闪烁效果。  
   - **音效提示**：配对计算时播放“点击”音效，找到最大值时播放上扬音效。

---

## 题解评分（≥4星）

### StudyingFather（⭐⭐⭐⭐⭐）
- **亮点**：代码简洁，直接三层循环暴力枚举，逻辑清晰。  
- **关键代码**：  
  ```cpp
  for(int i=1;i<=n;i++) {
    long long now=-INF;
    for(int j=1;j<=n;j++) if(j!=i)
      for(int k=1;k<=m;k++) now=max(now,a[j]*b[k]);
    res=min(res,now);
  }
  ```

### Tweetuzki（⭐⭐⭐）
- **思路**：贪心寻找极值组合，但可能存在遗漏情况。  
- **关键代码**：计算隐藏最大或最小后的极值组合：  
  ```cpp
  llt ans1 = max( max(Maxer1 * Max2, Maxer1 * Min2), max(Min1 * Max2, Min1 * Min2) );
  llt ans2 = max( max(Max1 * Max2, Max1 * Min2), max(Miner1 * Max2, Miner1 * Min2) );
  llt ans = min(ans1, ans2);
  ```

### Eason_AC（⭐⭐⭐⭐）
- **亮点**：代码规范，变量命名清晰，注释明确。  
- **关键代码**：  
  ```cpp
  _for(k, 1, n) {
    ll maxi = -0x3f3f3f3f3f3f3f3f;
    _for(i, 1, n) _for(j, 1, m)
      if(i != k) maxi = max(maxi, a[i] * b[j]);
    ans = min(ans, maxi);
  }
  ```

---

## 最优思路提炼

### 暴力枚举法（核心代码）
```cpp
#include <iostream>
using namespace std;
typedef long long ll;

int main() {
    int n, m;
    ll a[55], b[55], ans = 1e18;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < m; ++i) cin >> b[i];
    
    for (int hide = 0; hide < n; ++hide) {  // 枚举隐藏的灯笼
        ll current_max = -1e18;
        for (int i = 0; i < n; ++i) {       // 遍历剩余灯笼
            if (i == hide) continue;
            for (int j = 0; j < m; ++j) {   // 遍历Banban的灯笼
                current_max = max(current_max, a[i] * b[j]);
            }
        }
        ans = min(ans, current_max);        // 更新全局最小值
    }
    cout << ans << endl;
    return 0;
}
```

---

## 相似题目推荐

1. **P1219 八皇后**（暴力枚举与回溯）  
2. **P1036 选数**（组合枚举与条件判断）  
3. **P1149 火柴棒等式**（枚举与数学优化）

---

## 个人心得摘录

- **调试教训**：乘积可能溢出`int`，必须使用`long long`。
- **思维突破**：题目本质是极小化极大问题，暴力枚举在数据小时是最优解。

---

## 可视化实现（伪代码示例）

```javascript
// 初始化Canvas和音效
const canvas = document.getElementById('animation');
const ctx = canvas.getContext('2d');
const clickSound = new Audio('click.wav');
const successSound = new Audio('success.wav');

function drawLanterns(hideIndex, currentMax) {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    // 绘制Tommy的灯笼，隐藏的标记为灰色
    for (let i = 0; i < n; i++) {
        if (i === hideIndex) ctx.fillStyle = '#888';
        else ctx.fillStyle = '#f00';
        ctx.fillRect(20, 20 + i * 30, 20, 20);
    }
    // 绘制Banban的灯笼
    for (let j = 0; j < m; j++) {
        ctx.fillStyle = '#00f';
        ctx.fillRect(100, 20 + j * 30, 20, 20);
    }
    // 高亮当前最大乘积
    ctx.fillStyle = '#ff0';
    ctx.fillRect(20 + currentMax.i * 30, 20 + currentMax.j * 30, 20, 20);
}

// 自动播放算法过程
let hideIndex = 0;
let currentMax = -Infinity;
function animate() {
    if (hideIndex >= n) return;
    // 计算当前隐藏情况的最大值
    for (let i = 0; i < n; i++) {
        if (i === hideIndex) continue;
        for (let j = 0; j < m; j++) {
            const product = a[i] * b[j];
            if (product > currentMax) {
                currentMax = product;
                drawLanterns(hideIndex, {i, j});
                clickSound.play();
            }
        }
    }
    successSound.play();
    hideIndex++;
    setTimeout(animate, 2000);
}
animate();
```

---
处理用时：103.32秒