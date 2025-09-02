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



# Madoka and The Corruption Scheme 分析

## 算法分类
组合数学

---

## 综合分析与结论
### 核心思路
将比赛结构视为完全二叉树，每个叶节点到根的路径对应一个二进制数。赞助商最多修改k次比赛结果，相当于允许路径上有k次方向翻转。问题转化为计算二进制数中0的个数≤k的叶节点数量，即组合数求和 $\sum_{i=0}^k C(n,i)$。

### 难点与解决方案
1. **问题转化**：需要理解路径上的方向翻转次数与二进制位的关系，通过组合数建模。
2. **大数取模**：预处理阶乘和逆元，利用费马小定理快速计算组合数。
3. **边界处理**：当k≥n时结果直接为$2^n$。

### 可视化设计
- **二叉树路径演示**：以像素风格绘制完全二叉树，高亮路径中允许翻转的边。
- **组合数累加动画**：每次k增加时，显示新增的$C(n,i)$项及累加过程。
- **音效反馈**：方向翻转时触发8-bit音效，计算结果时播放胜利旋律。

---

## 题解清单（4星以上）
1. **whhsteven（5星）**  
   清晰阐释二进制路径属性与修改次数的关系，给出严格的数学证明，代码简洁高效。

2. **Plozia（4星）**  
   提供完整预处理逆元实现，代码规范易移植，边界处理严谨。

3. **DaiRuiChen007（4星）**  
   模块化组合数计算函数，代码结构清晰，适合教学演示。

---

## 核心代码实现
```cpp
const int MOD = 1e9+7;
long long fac[MAXN], inv[MAXN];

void precompute(int n) {
    fac[0] = 1;
    for(int i=1; i<=n; ++i) 
        fac[i] = fac[i-1] * i % MOD;
    inv[n] = pow(fac[n], MOD-2, MOD);
    for(int i=n-1; i>=0; --i)
        inv[i] = inv[i+1] * (i+1) % MOD;
}

long long solve(int n, int k) {
    k = min(n, k);
    long long res = 0;
    for(int i=0; i<=k; ++i) {
        long long C = fac[n] * inv[i] % MOD;
        C = C * inv[n-i] % MOD;
        res = (res + C) % MOD;
    }
    return res;
}
```

---

## 相似题目推荐
1. **洛谷P3807** 卢卡斯定理应用  
2. **洛谷P1313** 组合数计算与多项式展开  
3. **洛谷P1357** 树状路径计数问题

---

## 学习心得
关键顿悟在于将比赛路径抽象为二进制位，发现修改次数与二进制位中0的个数直接对应。调试时需特别注意模运算中减法的处理，例如`(a - b + MOD) % MOD`避免负数。

---

## 可视化算法演示
```html
<canvas id="tournament-tree"></canvas>
<script>
// 8-bit风格渲染参数
const config = {
    nodeColor: ['#FF6B6B', '#4ECDC4', '#45B7D1'], 
    lineWidth: 2,
    beepSound: new Audio('data:audio/wav;base64,UklGRl9...')
};

function drawTree(ctx, depth, k) {
    // 递归绘制二叉树，高亮可修改路径
    // 当当前修改次数≤k时触发音效并闪烁节点
}
</script>
```
- **交互功能**：滑动条调整k值，实时显示组合数求和过程
- **自动演示**：按DFS顺序遍历所有有效路径，步进间隔可调
- **计分系统**：正确识别路径时积累连击数，解锁成就特效

---

通过将复杂的组合问题转化为清晰的数学模型，并辅以直观的可视化交互，能够有效加深对组合数学在竞赛编程中应用的理解。

---
处理用时：65.23秒