# 题目信息

# [ABC336E] Digit Sum Divisible

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc336/tasks/abc336_e

正整数 $ n $ の **桁和** を、$ n $ を $ 10 $ 進法で表したときの各桁の和として定義します。例えば $ 2024 $ の桁和は $ 2+0+2+4=8 $ です。  
 正整数 $ n $ が $ n $ の桁和で割り切れる時、$ n $ を **良い整数** と呼びます。例えば $ 2024 $ はその桁和である $ 8 $ で割り切れるので良い整数です。  
 正整数 $ N $ が与えられます。$ N $ 以下の良い整数は全部で何個ありますか？

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^{14} $
- $ N $ は整数
 
### Sample Explanation 1

$ 20 $ 以下の良い整数は $ 1,2,3,4,5,6,7,8,9,10,12,18,20 $ の $ 13 $ 個です。

## 样例 #1

### 输入

```
20```

### 输出

```
13```

## 样例 #2

### 输入

```
2024```

### 输出

```
409```

## 样例 #3

### 输入

```
9876543210```

### 输出

```
547452239```

# AI分析结果



0. **题目翻译**

# [ABC336E] 数位和可整除数

## 题目描述

正整数 $n$ 的 **数位和** 定义为将其十进制表示中所有数字相加的和。例如 $2024$ 的数位和为 $2+0+2+4=8$。  
当正整数 $n$ 能被其数位和整除时，称其为 **好数**。例如 $2024$ 被其数位和 $8$ 整除，因此是好数。  
给定正整数 $N$，求 $N$ 及以下的所有好数数量。

## 输入输出样例

### 样例 #1
输入：  
20  
输出：  
13  
解释：1~20 中好数有 13 个

### 样例 #2
输入：  
2024  
输出：  
409

---

1. **唯一算法分类**  
线性DP

---

2. **综合分析与结论**

### 核心思路
所有题解均采用 **枚举数位和 + 数位DP** 的双层结构：  
1. 枚举所有可能的数位和（1~14×9=126）
2. 对每个数位和进行数位DP计算，统计满足以下条件的数：
   - 数位和等于当前枚举值
   - 数值能被该数位和整除

### 状态设计
典型四维状态：  
`f[pos][sum][mod][limit]`  
- `pos`：当前处理位（从高位到低位）
- `sum`：已确定的数位和
- `mod`：当前数值模当前数位和的余数  
- `limit`：是否受数字N的上限约束

### 关键转移方程
当处理第`pos`位时，枚举数字`d`：  
`f[pos][sum][mod][limit] += f[pos-1][sum+d][(mod*10 + d) % x][new_limit]`  
其中`x`为当前枚举的数位和，`new_limit`根据当前位是否达到上限确定

### 可视化设计
采用 **像素风格DP矩阵** 进行展示：  
- **颜色编码**：
  - 红色高亮：当前处理的位`pos`
  - 绿色渐变：`mod`值的变化（颜色越深余数越大）
  - 动态波纹：当`sum`超过当前枚举数位和时触发警告动画
- **音效系统**：
  - 8-bit 音效：状态转移时播放短促"滴"声
  - 发现解时播放经典马里奥金币音效
- **自动演示模式**：
  ```javascript
  function autoRun() {
    for(let x=1; x<=126; x++){
      drawGrid(x); // 绘制当前数位和的DP网格
      stepByStepDP(x); // 按帧执行数位DP过程
    }
  }
  ```

---

3. **题解清单 (≥4星)**

| 题解作者 | 评分 | 亮点 |
|---------|------|-----|
| int_R   | ⭐⭐⭐⭐ | 状态设计最精简，利用`cur`缓存当前数位和优化空间 |
| xz001   | ⭐⭐⭐⭐ | 采用记忆化搜索实现，代码结构清晰易扩展 |
| aaron0919 | ⭐⭐⭐⭐ | 引入`sum > mod`剪枝策略提升效率 |

---

4. **核心代码实现**

```cpp
// int_R 题解核心代码
int dfs(int pos, int s, int sum, bool limit) {
    if(s < 0) return 0;
    if(!pos) return !s && !sum;
    if(f[pos][s][sum][limit] != -1) return f[pos][s][sum][limit];
    
    int ans = 0, up = limit ? a[pos] : 9;
    for(int d=0; d<=up; ++d) {
        ans += dfs(pos-1, s-d, (sum*10 + d)%cur, limit && (d==up));
    }
    return f[pos][s][sum][limit] = ans;
}

// 主调用逻辑
for(int x=1; x<=14*9; ++x) {
    memset(f, -1, sizeof(f));
    cur = x; // 当前枚举的数位和
    ANS += dfs(tot, x, 0, 1); // tot为数字总位数
}
```

---

5. **同类型题推荐**

1. **P4127 [AHOI2009] 同类分布**  
   完全相同的数位和模数问题，可直接套用本题解法

2. **P2602 [ZJOI2010] 数字计数**  
   基础数位DP，统计数字出现次数

3. **CF55D Beautiful numbers**  
   进阶数位DP，需结合数论知识处理模数

---

6. **可视化关键实现**

```javascript
// Canvas绘制DP状态网格
function drawDPState(pos, sum, mod) {
    ctx.fillStyle = `hsl(${mod*3},70%,50%)`; // 根据余数变化颜色
    ctx.fillRect(pos*30, sum*30, 28, 28);
    
    // 绘制当前位标记
    ctx.strokeStyle = '#ff0000';
    ctx.strokeRect(pos*30, sum*30, 28, 28);
}

// 音效触发系统
const audioCtx = new AudioContext();
function playBeep(freq) {
    const oscillator = audioCtx.createOscillator();
    oscillator.type = 'square';
    oscillator.frequency.setValueAtTime(freq, audioCtx.currentTime);
    oscillator.connect(audioCtx.destination);
    oscillator.start();
    oscillator.stop(audioCtx.currentTime + 0.05);
}
```

---

7. **总结**

本题展现了数位DP的经典模式：**外层枚举关键参数，内层进行数位状态转移**。通过将数位和作为枚举参数，将原问题转化为多个标准数位DP子问题，这种"参数分解"思想在处理复杂约束条件时极为有效。

可视化设计通过将抽象的DP状态具象化为彩色网格，配合音效反馈，能够直观展示数位DP的递推过程。复古像素风格的选择不仅降低渲染开销，更增强了算法演示的趣味性。

---
处理用时：80.45秒