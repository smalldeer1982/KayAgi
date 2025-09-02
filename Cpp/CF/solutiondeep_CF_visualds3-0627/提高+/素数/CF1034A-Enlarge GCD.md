# 题目信息

# Enlarge GCD

## 题目描述

Mr. F has $ n $ positive integers, $ a_1, a_2, \ldots, a_n $ .

He thinks the greatest common divisor of these integers is too small. So he wants to enlarge it by removing some of the integers.

But this problem is too simple for him, so he does not want to do it by himself. If you help him, he will give you some scores in reward.

Your task is to calculate the minimum number of integers you need to remove so that the greatest common divisor of the remaining integers is bigger than that of all integers.

## 说明/提示

In the first example, the greatest common divisor is $ 1 $ in the beginning. You can remove $ 1 $ so that the greatest common divisor is enlarged to $ 2 $ . The answer is $ 1 $ .

In the second example, the greatest common divisor is $ 3 $ in the beginning. You can remove $ 6 $ and $ 9 $ so that the greatest common divisor is enlarged to $ 15 $ . There is no solution which removes only one integer. So the answer is $ 2 $ .

In the third example, there is no solution to enlarge the greatest common divisor. So the answer is $ -1 $ .

## 样例 #1

### 输入

```
3
1 2 4
```

### 输出

```
1```

## 样例 #2

### 输入

```
4
6 9 15 30
```

### 输出

```
2```

## 样例 #3

### 输入

```
3
1 1 1
```

### 输出

```
-1```

# AI分析结果



# Enlarge GCD 题解分析

## 算法分类
**数论（质因数分解与筛法）**

---

## 题解思路与核心算法

### 核心思想
1. **消除原GCD影响**：将每个数除以所有数的原GCD，转化为求新数组的最大公约数大于1的问题。
2. **质数倍数统计**：通过筛法统计每个质数的倍数出现次数，找到出现次数最多的质数，所需删除次数为总数减去该次数。

### 解决难点
- **原GCD的预处理**：通过除以原GCD，将问题简化为求新数组的GCD>1。
- **高效统计质数倍数**：使用埃氏筛法或线性筛法，批量统计每个质数的倍数，避免逐个分解质因数的时间消耗。
- **大值域处理**：当值域达到1.5e7时，普通质因数分解不可行，筛法的时间复杂度O(m log log m)更优。

---

## 最优题解（评分≥4星）

### 1. Siyuan（5星）
- **亮点**：通过筛法直接统计质数倍数，代码简洁高效。
- **关键代码**：
  ```cpp
  sieve(mx); // 筛出最大数以内的质数
  for (int i=1;i<=tot;++i) {
      int x=p[i],num=0;
      for (int j=x;j<=mx;j+=x) num+=cnt[j];
      if(num) ans=std::min(ans,n-num);
  }
  ```

### 2. Acc_Robin（4.5星）
- **亮点**：对复杂度进行数学分析，指出筛法的调和级数性质。
- **核心优化**：在筛质数时直接统计倍数，省去显式分解步骤。

### 3. Zimo_666（4星）
- **亮点**：强调最终GCD必为质数，简化问题逻辑。
- **代码片段**：
  ```cpp
  for (int j=1;prm[i]*j<=maxx;j++) res+=buc[prm[i]*j];
  ```

---

## 核心算法可视化设计

### 动画方案
1. **筛法过程展示**：
   - **像素网格**：用Canvas绘制值域区间，每个单元格表示一个数。
   - **质数高亮**：筛到质数p时，用黄色标记p的倍数单元格。
   - **统计标记**：对每个质数p，显示其倍数总数`num`，并用绿色柱状图表示。

2. **关键操作演示**：
   - **步进控制**：单步执行质数筛的过程，展示p=2,3,5...时的倍数统计。
   - **颜色标记**：
     - 红色：当前质数p。
     - 蓝色：当前筛中的倍数j。
     - 绿色：统计后的最大值对应的质数。

3. **音效设计**：
   - **筛中质数**：播放“滴”声。
   - **更新最大值**：播放上升音调。
   - **最终结果**：播放胜利音效。

---

## 代码实现（核心逻辑）

### 最优解代码（Siyuan优化版）
```cpp
#include <cstdio>
#include <algorithm>
const int N=3e5+5, M=1.5e7+5;
int n, a[N], cnt[M], mx, ans;
bool vis[M];

int gcd(int x, int y) { return y ? gcd(y, x%y) : x; }

int main() {
    scanf("%d", &n);
    int g = 0;
    for (int i=1; i<=n; ++i) {
        scanf("%d", &a[i]);
        g = gcd(g, a[i]);
    }
    for (int i=1; i<=n; ++i) {
        a[i] /= g;
        mx = std::max(mx, a[i]);
        cnt[a[i]]++;
    }
    ans = n;
    for (int i=2; i<=mx; ++i) {
        if (!vis[i]) {
            int num = 0;
            for (int j=i; j<=mx; j+=i) {
                vis[j] = true; // 标记筛过的数
                num += cnt[j];
            }
            if (num) ans = std::min(ans, n - num);
        }
    }
    printf("%d\n", ans == n ? -1 : ans);
    return 0;
}
```

---

## 同类型题目推荐
1. **P1072 [NOIP2009 提高组] Hankson 的趣味题**（质因数分解与GCD/LCM结合）
2. **P1414 又是毕业季II**（统计多个数的约数出现次数）
3. **P2651 添加括号III**（通过约分操作改变GCD性质）

---

## 个人心得摘录
- **调试教训**：初始未考虑除以原GCD导致统计错误，通过增加`a[i] /= g`修正。
- **优化顿悟**：发现统计质数倍数时无需分解每个数，直接筛法统计更高效。

---

## 可视化设计（复古像素版）
```javascript
// Canvas初始化（伪代码）
const canvas = document.getElementById("screen");
const ctx = canvas.getContext("2d");
const gridSize = 4; // 4x4像素块代表一个数

function drawNumber(num, x, y, color) {
    ctx.fillStyle = color;
    ctx.fillRect(x * gridSize, y * gridSize, gridSize, gridSize);
}

// 筛法动画
function animateSieve() {
    let p = 2;
    while (p <= mx) {
        if (!vis[p]) {
            // 高亮当前质数p
            drawNumber(p, p % 100, Math.floor(p/100), "#FF0000");
            // 标记倍数
            for (let j = p; j <= mx; j += p) {
                drawNumber(j, j % 100, Math.floor(j/100), "#0000FF");
                audio.play("tick"); // 播放音效
            }
        }
        p++;
    }
}
```

---

**总结**：通过消除原GCD影响，将问题转化为质数统计问题，结合筛法高效实现。核心在于质数倍数的批量统计与最小值计算，时间复杂度优化至O(m log log m)。

---
处理用时：79.70秒