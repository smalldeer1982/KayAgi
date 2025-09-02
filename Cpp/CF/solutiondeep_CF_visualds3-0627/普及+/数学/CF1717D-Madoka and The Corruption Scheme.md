# 题目信息

# Madoka and The Corruption Scheme

## 题目描述

Madoka decided to entrust the organization of a major computer game tournament "OSU"!

In this tournament, matches are held according to the "Olympic system". In other words, there are $ 2^n $ participants in the tournament, numbered with integers from $ 1 $ to $ 2^n $ . There are $ n $ rounds in total in the tournament. In the $ i $ -th round there are $ 2^{n - i} $ matches between two players (one of whom is right, the other is left), after which the winners go further along the tournament grid, and the losing participants are eliminated from the tournament. Herewith, the relative order in the next round does not change. And the winner of the tournament — is the last remaining participant.

But the smaller the participant's number, the more he will pay Madoka if he wins, so Madoka wants the participant with the lowest number to win. To do this, she can arrange the participants in the first round as she likes, and also determine for each match who will win — the participant on the left or right.

But Madoka knows that tournament sponsors can change the winner in matches no more than $ k $ times. (That is, if the participant on the left won before the change, then the participant on the right will win after the change, and if the participant on the right won, then the participant on the left will win after the change).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1717D/f3b4c42531ac8b0aab0fa40e7e46069a137caf77.png)So, the first image shows the tournament grid that Madoka made, where the red lines denote who should win the match. And the second one shows the tournament grid, after one change in the outcome of the match by sponsors (a match between $ 1 $ and $ 3 $ players).Print the minimum possible number of the winner in the tournament, which Madoka can get regardless of changes in sponsors. But since the answer can be very large, output it modulo $ 10^9 + 7 $ . Note that we need to minimize the answer, and only then take it modulo.

## 说明/提示

In the first example, there is only one match between players $ 1 $ and $ 2 $ , so the sponsors can always make player $ 2 $ wins.

The tournament grid from the second example is shown in the picture in the statement.

## 样例 #1

### 输入

```
1 1```

### 输出

```
2```

## 样例 #2

### 输入

```
2 1```

### 输出

```
3```

## 样例 #3

### 输入

```
3 2```

### 输出

```
7```

# AI分析结果



# 分析与解答

## 算法分类
**组合数学**

---

## 题解思路与核心难点

### 核心思路
将每个选手到根节点的比赛路径视为一个二进制数（0表示需要翻转比赛结果），赞助商最多可修改k次结果。答案转化为求二进制数中0的个数≤k的路径数量，即组合数求和：$\sum_{i=0}^{\min(k,n)} \binom{n}{i}$。

### 关键公式推导
- **路径翻转次数**：每个选手的路径对应一个二进制数，0的个数即为需翻转的次数。
- **组合数求和**：允许翻转k次的路径总数为$\sum_{i=0}^k \binom{n}{i}$。

### 解决难点
- **思维转换**：将比赛路径转化为二进制数，并发现翻转次数与组合数的关系。
- **模运算处理**：预处理阶乘和逆元快速计算组合数。

---

## 题解评分（≥4星）

1. **Hedgehog_210508（4.5星）**
   - 思路清晰，直接给出组合数求和的结论。
   - 代码简洁，预处理阶乘和逆元高效计算组合数。
   - 特判k≥n的情况处理得当。

2. **DaiRuiChen007（4.5星）**
   - 预处理阶乘和逆元，代码结构清晰。
   - 组合数计算使用费马小定理求逆元，效率高。

3. **Plozia（4星）**
   - 详细分析路径属性，代码简洁。
   - 使用逆元预处理组合数，但变量命名稍显复杂。

---

## 最优思路与技巧

### 关键技巧
- **组合数快速计算**：预处理阶乘和逆元，使用费马小定理求模逆元。
- **特判优化**：当k≥n时，直接返回$2^n \mod (10^9+7)$。

### 核心代码实现
```cpp
// 预处理阶乘和逆元
fac[0] = 1;
for (int i = 1; i <= n; ++i) 
    fac[i] = fac[i-1] * i % MOD;
inv[n] = ksm(fac[n], MOD-2, MOD);
for (int i = n-1; i >= 0; --i)
    inv[i] = inv[i+1] * (i+1) % MOD;

// 计算组合数之和
int ans = 0;
for (int i = 0; i <= min(n, k); ++i)
    ans = (ans + C(n, i)) % MOD;
```

---

## 同类题目推荐

1. **洛谷 P1771** - 组合数问题  
   **标签**：组合数学、前缀和

2. **洛谷 P2822** - 组合数问题（NOIP 提高组）  
   **标签**：组合数、模运算

3. **洛谷 P1350** - 车的放置  
   **标签**：组合数学、排列组合

---

## 可视化与动画设计

### 动画方案
1. **像素风格路径展示**：  
   - 使用Canvas绘制完全二叉树，叶子节点显示编号。
   - 选中某叶子节点时，高亮其到根节点的路径，红色标记需翻转的边（0的位数）。

2. **组合数计算过程**：  
   - 步进显示$\binom{n}{0}$到$\binom{n}{k}$的计算，每个步骤显示当前i值和组合数值。
   - 颜色标记当前累加项，最终总和以闪烁效果突出。

3. **音效与交互**：  
   - 点击节点时播放8-bit音效，成功累加时播放上升音调。
   - 提供速度调节滑块和单步执行按钮。

### 复古游戏化实现
```javascript
// 示例：Canvas绘制组合数计算
const canvas = document.getElementById('pixelCanvas');
const ctx = canvas.getContext('2d');
let currentStep = 0;

function drawCombination(n, k) {
    ctx.fillStyle = '#000';
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    for (let i = 0; i <= currentStep; i++) {
        ctx.fillStyle = i === currentStep ? '#FF0000' : '#FFF';
        ctx.fillText(`C(${n},${i}) = ${comb(n, i)}`, 10, 20 + i*20);
    }
}

function nextStep() {
    if (currentStep <= k) {
        playSound('step');
        currentStep++;
        drawCombination(n, k);
    } else {
        playSound('success');
    }
}
```

---

## 个人心得

- **调试教训**：逆元预处理顺序需从后向前，避免重复计算。
- **思维突破**：将路径翻转视为二进制数，极大简化问题分析。
- **模运算陷阱**：减法取模需加MOD再取余，防止负数。

---
处理用时：71.62秒