# 题目信息

# Doremy's Pegging Game

## 题目描述

Doremy has $ n+1 $ pegs. There are $ n $ red pegs arranged as vertices of a regular $ n $ -sided polygon, numbered from $ 1 $ to $ n $ in anti-clockwise order. There is also a blue peg of slightly smaller diameter in the middle of the polygon. A rubber band is stretched around the red pegs.

Doremy is very bored today and has decided to play a game. Initially, she has an empty array $ a $ . While the rubber band does not touch the blue peg, she will:

1. choose $ i $ ( $ 1 \leq i \leq n $ ) such that the red peg $ i $ has not been removed;
2. remove the red peg $ i $ ;
3. append $ i $ to the back of $ a $ .

Doremy wonders how many possible different arrays $ a $ can be produced by the following process. Since the answer can be big, you are only required to output it modulo $ p $ . $ p $ is guaranteed to be a prime number.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1764D/39b25225514736b577fbcbcd5d0b5bf29ecc4db4.png) game with $ n=9 $ and $ a=[7,5,2,8,3,9,4] $ and another game with $ n=8 $ and $ a=[3,4,7,1,8,5,2] $

## 说明/提示

In the first test case, $ n=4 $ , some possible arrays $ a $ that can be produced are $ [4,2,3] $ and $ [1,4] $ . However, it is not possible for $ a $ to be $ [1] $ or $ [1,4,3] $ .

## 样例 #1

### 输入

```
4 100000007```

### 输出

```
16```

## 样例 #2

### 输入

```
1145 141919831```

### 输出

```
105242108```

# AI分析结果



## 算法分类
**组合数学**

---

## 题解思路与解决难点

### 核心逻辑
游戏终止条件：当存在连续至少 $\lfloor n/2 \rfloor$ 个红钉被移除时，橡皮筋会触碰到蓝钉。要求计算所有可能的操作序列数目。

### 关键公式推导
1. **终止条件转化**：当剩余红钉中存在一个长度为 $L = n - \lfloor n/2 \rfloor$ 的连续未被移除区域时，游戏终止。
2. **对称性简化**：由于环形对称性，最后一个移除的钉子（记为 $a_k$）的位置不影响计数，最终结果可简化为计算 $a_k = n$ 的情况后乘 $n$。
3. **组合计数**：枚举两侧连续移除区域长度 $s$ 和 $t$ 的和 $m = s + t$，计算剩余钉子的排列组合数：
   $$\text{答案} = n \cdot \sum_{m} \left( \text{可行}(m) \cdot \sum_{i=0}^{M} \binom{M}{i} \cdot (m+i)! \right) $$
   其中 $M = n - m - 3$，$\text{可行}(m)$ 表示满足 $m \geq \lfloor n/2 \rfloor - 1$ 的系数。

### 解决难点
1. **避免重复计数**：确保最后一个操作触达终止条件，而之前的操作不满足。
2. **高效计算组合数**：预处理阶乘和逆元，快速计算 $\binom{n}{k} \mod p$。
3. **边界处理**：处理 $n$ 奇偶性对 $\lfloor n/2 \rfloor$ 的影响，特判 $n$ 为偶数时的特殊情况。

---

## 题解评分（≥4星）

1. **VinstaG173（4.5星）**
   - **亮点**：对称性分析透彻，公式推导严谨，代码预处理阶乘逆元高效。
   - **代码**：预处理阶乘和逆元，时间复杂度 $O(n^2)$，清晰易读。

2. **Alex_Wei（4星）**
   - **亮点**：枚举最终绑定点距离，逻辑清晰，特判奇偶情况。
   - **优化**：直接枚举关键参数，避免复杂状态转移。

3. **james1BadCreeper（4星）**
   - **亮点**：简洁枚举连续段长度，代码结构紧凑。
   - **心得**：强调预处理组合数的重要性。

---

## 最优思路提炼
1. **对称性简化**：利用环形对称性，固定最后一个移除的钉子，减少计算量。
2. **组合数+阶乘预处理**：通过预处理阶乘和逆元，快速计算组合数与排列数。
3. **枚举关键参数**：通过枚举连续区域长度或绑定点距离，将问题转化为可计算的组合数求和。

---

## 同类型题套路
- **组合计数模板**：预处理阶乘、逆元，快速计算 $\binom{n}{k}$。
- **环形问题处理**：利用对称性简化问题，转化为线性计算。
- **终止条件分析**：确定触发终止的关键参数（如连续段长度），避免重复计数。

---

## 推荐题目
1. **P3197 [HNOI2008]越狱**（组合计数）
2. **P1350 车的放置**（排列组合+容斥）
3. **P3223 [HNOI2012]排队**（复杂排列组合）

---

## 代码片段（VinstaG173）
```cpp
int n, ntf; ll res, tmp;
ll fac[5003], fic[5003];
inline ll C(int m, int b) {
    return fac[m] * fic[b] % ntf * fic[m - b] % ntf;
}
void solve() {
    rd(n); rd(ntf);
    fac[0] = 1;
    for (rg int i = 1; i <= n; ++i) fac[i] = fac[i-1] * i % ntf;
    fic[n] = qpow(fac[n], ntf-2, ntf);
    for (rg int i = n; i; --i) fic[i-1] = fic[i] * i % ntf;
    // 枚举m并累加结果
    for (rg int m = n/2 - 1; m < n-2; ++m) {
        tmp = 0;
        for (rg int i = 0; i <= n - m - 3; ++i)
            tmp = (tmp + fac[m+i] * C(n-m-3, i)) % ntf;
        res = (res + (n - (n&1) - 1 - m) * tmp) % ntf;
    }
    res = res * n % ntf;
    printf("%lld\n", res);
}
```

---

## 可视化设计
### 像素动画方案
1. **钉子排列**：用16色像素画展示环形红钉和中心蓝钉，移除钉子时变为灰色。
2. **高亮区域**：当连续移除区域接近 $\lfloor n/2 \rfloor$ 时，用红色边框提示终止条件。
3. **公式计算**：右侧面板实时显示当前枚举的 $m$ 和 $i$，组合数 $\binom{M}{i}$ 和阶乘 $(m+i)!$ 的值。
4. **音效提示**：移除钉子时播放8位“点击”音效，达成终止条件时播放胜利音效。

### 复古UI控件
- **步进控制**：按钮 [Step] 单步执行枚举过程，[Auto] 自动播放（速度可调）。
- **统计面板**：显示当前答案、已计算轮次、剩余参数组合。

```javascript
// 伪代码：Canvas绘制钉子
function drawPegs(removed) {
    ctx.fillStyle = "#2D2D2D"; // 背景色
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    for (let i = 0; i < n; i++) {
        if (!removed.has(i)) {
            const angle = (i * 2 * Math.PI) / n;
            const x = cx + Math.cos(angle) * radius;
            const y = cy + Math.sin(angle) * radius;
            drawPixelPeg(x, y, "#FF0000"); // 红钉
        }
    }
    drawPixelPeg(cx, cy, "#0000FF"); // 蓝钉
}
```

---

## 个人心得摘录
- **MortisM**：调试时发现组合数边界未处理，导致WA。教训：始终验证 $\binom{n}{k}$ 中 $k \leq n$。
- **honglan0301**：最初未考虑偶数特例，补充后AC。心得：仔细分析奇偶性对结果的影响。

---
处理用时：78.62秒