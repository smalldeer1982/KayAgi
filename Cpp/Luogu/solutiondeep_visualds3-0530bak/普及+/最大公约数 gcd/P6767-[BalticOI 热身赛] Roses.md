# 题目信息

# [BalticOI 热身赛] Roses

## 题目背景

因为特殊原因，本题目另外 $24$ 组数据请在 [这里](https://www.luogu.com.cn/problem/U127462) 提交。

Valentine 是人赢。

## 题目描述

现在 Valentine 要给他的 $N$ 个妹子买玫瑰花，现在 Valentine 面前有两家店，每一家店有无数朵玫瑰花，但是他们按束卖。第一家店一束花里有 $A$ 朵，每一束花要用 $B$ 块钱。第二家店一束花里有 $C$ 朵，每一束花要用 $D$ 块钱。

求 Valentine 至少买 $N$ 朵花最少需要花多少钱。

至少可以这么理解，假如 $M>N$，但是买 $M$ 朵花的钱比买 $N$ 朵花的少，Valentine 就会买 $M$ 朵花，并把多出来的花给其他妹子，没错，Valentine 很花心。

## 说明/提示

#### 样例说明

对于样例 $1$，Valentine 可以选择在第二家店买 $2$ 束花。

对于样例 $2$，Valentine 可以选择在第一家店买 $1$ 束花，在第二家店买 $2$ 束花。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（20 pts）：$N,A,B,C,D \le 1000$。
- Subtask 2（80 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le N \le 10^{15}$，$1 \le A,B,C,D \le 10^5$，保证答案不超过 $10^{18}$。

#### 说明

翻译自 [BalticOI 2020 Day0 B Roses](http://www.boi2020.lv/data/tasks/en/day0/roses.pdf)。

与 BalticOI 2012 Day0 A 内容一致。

## 样例 #1

### 输入

```
5 1 4 3 6```

### 输出

```
12```

## 样例 #2

### 输入

```
22 2 3 10 14```

### 输出

```
31```

# AI分析结果



## 唯一算法分类
**枚举优化**

---

## 综合分析与结论
### 核心思路与算法要点
1. **贪心策略**：优先购买单价更优的花束（通过交叉相乘避免浮点精度问题：`a*d >= b*c` 时认为第一家性价比高）
2. **有限枚举**：通过数学推导将枚举次数限制在 `a/gcd(a,c)` 范围内，时间复杂度从 O(N) 优化至 O(1e5)
3. **关键公式**：  
   - 剩余花朵需求 `max(0, n - i*a)`  
   - 另一家店购买量计算 `(remain + c-1)/c` （向上取整技巧）

### 解决难点
1. **超大规模数据**：当 N ≤ 1e15 时，直接枚举会超时
2. **最优性证明**：通过数学分析证明枚举到 `a/gcd(a,c)` 即可覆盖所有可能更优的组合
3. **代码陷阱**：浮点数比较可能引入误差，需用整数运算替代

### 可视化设计思路
1. **动画流程**：
   - 左右分屏显示两家店铺的单价比较结果
   - 动态展示枚举过程：用红色高亮当前枚举的购买次数，蓝色标记已计算的最优解
   - 每次循环时更新购买量公式 `i*b + (remain + c-1)/c*d` 的分解步骤
2. **像素风格交互**：
   - 8-bit 音效：每次枚举时播放短促 "beep" 音，找到更优解时播放上扬音效
   - Canvas 网格绘制购买次数与花费的折线图，用绿色像素块标记最优解
   - 自动演示模式下，算法流程会以 0.5s/步 的速度自动执行

---

## 题解清单 (评分 ≥4星)
### 1. zjh111111（★★★★☆）
**亮点**：  
- 使用 `a/gcd(a,c)` 精确控制枚举次数  
- 代码中 `x = n - c*i` 的剩余计算清晰  
```cpp
for (i=0 到 a/gcd(a,c)) 
    ans = min(ans, i*d + 剩余花朵在第一家的花费)
```

### 2. 快斗游鹿（★★★★☆）
**亮点**：  
- 单独封装 `getcost` 函数提升可读性  
- 使用 `__gcd` 简化代码  
```cpp
int k = a/__gcd(a,c);
for (i=1 到 k) 
    ans = min(ans, i*d + getcost(n-i*c, a,b))
```

### 3. happy_dengziyue（★★★★☆）
**亮点**：  
- 明确标注代码中的坑点（`n-i*a` 可能为负数）  
- 使用 `mi()` 替代 `min` 提升代码可读性  
```cpp
ans = mi(ans, i*d + ((x-1)/a+1)*b)
```

---

## 最优代码片段
```cpp
// 核心逻辑：比较单价 + 有限枚举
if (a*d < b*c) swap(a,c), swap(b,d); // 确保第一家更优
ll ans = (n + a-1)/a * b; // 全买第一家的初始解
ll max_cnt = a / __gcd(a,c); // 关键枚举上限

for (ll i=1; i<=max_cnt; ++i) {
    ll remain = n - c*i; // 买i束第二家后的剩余需求
    if (remain <= 0) 
        ans = min(ans, i*d);
    else 
        ans = min(ans, i*d + ((remain + a-1)/a)*b);
}
```

---

## 相似题目推荐
1. **P3951 小凯的疑惑**（数学推导与枚举结合）
2. **P2920 [USACO08NOV]Time Management S**（贪心策略优化）
3. **P2667 [NOIP2015 提高组] 跳石头**（二分答案 + 有限枚举）

---

## 个人心得摘录
> "最开始直接枚举到 `s=(n+a-1)/a` 导致 TLE，后来发现当 `A,C ≤1e5` 时，只需枚举到 1e5 次即可。这告诉我：面对大范围数据时，寻找数学约束比盲目优化代码更有效。"  
> —— sysong 调试日志

---

## 复古像素动画实现
### HTML/JS 关键代码
```html
<canvas id="pixel-canvas" width="640" height="240"></canvas>
<script>
// 初始化 8-bit 调色板
const COLORS = ['#000', '#F00', '#0F0', '#00F', '#FF0', '#FFF'];
const ctx = document.getElementById('pixel-canvas').getContext('2d');

function drawStep(i, currentCost, bestCost) {
    // 绘制当前枚举状态
    ctx.fillStyle = COLORS[2]; 
    ctx.fillRect(i*10 % 640, 100, 8, 8); // 红色方块表示当前枚举
    
    if (currentCost < bestCost) {
        playSound('up'); // 找到更优解时播放音效
        ctx.fillStyle = COLORS[3];
        ctx.fillRect(300, 50, 100, 30); // 更新最优解显示区域
    }
}
</script>
```

### 音效设计
- **常规操作音**：方波生成的 500Hz 短脉冲  
- **最优解音效**：频率从 400Hz 滑升至 800Hz  
- **背景音乐**：8-bit 风格循环旋律（使用 Web Audio API 合成）

---
处理用时：88.41秒