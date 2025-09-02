# 题目信息

# Fox And Jumping

## 题目描述

Fox Ciel is playing a game. In this game there is an infinite long tape with cells indexed by integers (positive, negative and zero). At the beginning she is standing at the cell 0.

There are also $ n $ cards, each card has 2 attributes: length $ l_{i} $ and cost $ c_{i} $ . If she pays $ c_{i} $ dollars then she can apply $ i $ -th card. After applying $ i $ -th card she becomes able to make jumps of length $ l_{i} $ , i. e. from cell $ x $ to cell $ (x-l_{i}) $ or cell $ (x+l_{i}) $ .

She wants to be able to jump to any cell on the tape (possibly, visiting some intermediate cells). For achieving this goal, she wants to buy some cards, paying as little money as possible.

If this is possible, calculate the minimal cost.

## 说明/提示

In first sample test, buying one card is not enough: for example, if you buy a card with length 100, you can't jump to any cell whose index is not a multiple of 100. The best way is to buy first and second card, that will make you be able to jump to any cell.

In the second sample test, even if you buy all cards, you can't jump to any cell whose index is not a multiple of 10, so you should output -1.

## 样例 #1

### 输入

```
3
100 99 9900
1 1 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
10 20 30 40 50
1 1 1 1 1
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
7
15015 10010 6006 4290 2730 2310 1
1 1 1 1 1 1 10
```

### 输出

```
6
```

## 样例 #4

### 输入

```
8
4264 4921 6321 6984 2316 8432 6120 1026
4264 4921 6321 6984 2316 8432 6120 1026
```

### 输出

```
7237
```

# AI分析结果



---

## 唯一算法分类  
动态规划（状态压缩 + 质因数分解）

---

## 综合分析与结论  

### 核心算法流程  
1. **问题转化**：通过裴蜀定理将问题转化为求一组数的gcd为1的最小代价  
2. **状态定义**：用质因数集合的二进制状态表示当前gcd的质因子  
3. **状态转移**：  
   - 对每个数分解质因数，生成其质因数状态码  
   - 用当前状态码与新数的质因数状态码进行按位与运算，更新状态  
4. **优化手段**：  
   - 状压DP的状态规模由质因数数量决定（最多9位二进制）  
   - 对每个数独立进行质因数分解，避免重复计算  

### 可视化设计要点  
- **像素化状态转移图**：在Canvas中以9x9网格表示质因数状态（如3号质因数对应第3行第3列方块）  
- **动态高亮**：  
  - 黄色方块表示当前处理的质因数  
  - 绿色方块表示被保留的质因数（按位与后的结果）  
- **音效设计**：  
  - 方块碰撞音效：当状态转移发生时播放8位电子音  
  - 胜利音效：当状态变为全0（gcd=1）时播放经典FC过关音效  

---

## 题解清单 (≥4星)

### 1. ZYF_B（5星）  
**亮点**：  
- 质因数分解的状压DP思路  
- 时间复杂度稳定在O(n²2^9)  
- 代码中通过预处理质因数减少状态规模  

**核心代码**：  
```cpp
for(int j=1;j<=n;j++) {
    int s=0;
    for(int k=1;k<=cnt[i];k++) { // 生成当前数的质因数状态码
        int flag=0;
        for(int x=1;x<=cnt[j];x++)
            if(g[i][k]==g[j][x]) flag=1;
        if(flag) s|=(1<<(k-1));
    }
    for(int k=0;k<M;k++)
        f[k&s] = min(f[k&s], f[k]+cost[j]); // 状态转移
}
```

### 2. Kohakuwu（4星）  
**亮点**：  
- 使用map维护动态gcd状态  
- 代码简洁易懂（仅20行核心逻辑）  
- 自解释的转移方程：`f[gcd(x,l)] = min(f[gcd(x,l)], f[x]+c)`

**核心思路**：  
```cpp
for(pair<int,int> x : mp) {
    int num = gcd(a[i], x.first);
    mp[num] = min(mp[num], x.second + b[i]);
}
```

### 3. fanfansann（4星）  
**亮点**：  
- 将问题建模为图论最短路  
- 使用unordered_map实现隐式状态存储  
- 清晰的Dijkstra框架实现  

**关键转移**：  
```cpp
for(int j=1; j<=n; ++j) {
    int y = gcd(x, l[j]);
    if(dist[y] > dist[x] + c[j]) {
        dist[y] = dist[x] + c[j];
        q.push({dist[y], y});
    }
}
```

---

## 最优思路提炼

### 关键技巧
1. **质因数状态压缩**  
   - 将每个数的质因数转换为二进制状态  
   - 通过按位与操作实现gcd计算  
   - 例如：数12=2²×3¹ → 状态码0b11（假设质因数列表为[2,3]）

2. **动态规划的空间优化**  
   - 使用滚动数组：`f[k&s] = min(f[k&s], f[k]+cost)`  
   - 每个数独立处理，避免状态冲突

3. **预处理优化**  
   - 提前分解所有数的质因数  
   - 建立质因数索引表减少匹配时间

---

## 类似题目推荐

1. **P4549 裴蜀定理**  
   - 直接应用裴蜀定理求最小系数  
   - 关键点：多个数的线性组合

2. **P3951 小凯的疑惑**  
   - 利用互质数的最大不可表数性质  
   - 公式：a×b - a - b

3. **P1072 Hankson的趣味题**  
   - 数论综合应用题  
   - 涉及gcd与lcm的性质转换

---

## 复古游戏化动画设计

### 实现方案
```javascript
// 伪代码示例
class GCDGame {
  constructor() {
    this.states = new Map(); // 当前gcd状态
    this.grid = new PixelGrid(9, 9); // 质因数显示网格
    this.sfx = new SFXController(); // 音效控制器
  }

  updateState(newGcd, cost) {
    // 在网格中高亮变化的质因数
    const bits = getPrimeFactors(newGcd).map(p => this.primeIndex[p]);
    bits.forEach(i => this.grid.highlight(i, 0xFF00FF));
    
    // 播放8-bit音效
    this.sfx.play('state_change', bits.length);
    
    // 胜利检测
    if(newGcd === 1) {
      this.grid.explode();
      this.sfx.play('victory');
    }
  }
}

// 像素网格渲染
class PixelGrid {
  highlight(index, color) {
    const x = index % 3;
    const y = Math.floor(index / 3);
    this.drawSquare(x*3, y*3, color);
  }
}
```

### 交互特性
- **自动演示模式**：AI自动选择最优卡片序列  
- **连击系统**：连续选择有效卡片时获得分数加成  
- **历史回放**：以快照形式保存关键状态转移路径

---

## 核心代码实现

### 质因数分解优化
```cpp
vector<int> factorize(int x) {
  vector<int> primes;
  for(int p=2; p*p<=x; ++p) {
    if(x%p == 0) {
      primes.push_back(p);
      while(x%p == 0) x /= p;
    }
  }
  if(x > 1) primes.push_back(x);
  return primes;
}

// 预处理所有数的质因数
unordered_map<int, vector<int>> precomputeFactors(vector<int>& nums) {
  unordered_map<int, vector<int>> factors;
  for(int x : nums) {
    auto f = factorize(x);
    factors[x] = f;
  }
  return factors;
}
```

### 状压DP核心逻辑
```cpp
int solve() {
  vector<unordered_map<int, int>> dp(n+1);
  dp[0][0] = 0; // 初始状态：gcd=0（未选任何数）

  for(int i=1; i<=n; ++i) {
    auto& factors = precomputed[i];
    int state = 0;
    for(int p : factors) 
      state |= (1 << primeIndex[p]);

    // 状态转移
    for(auto [prev_state, cost] : dp[i-1]) {
      int new_gcd = gcd(prev_state, l[i]);
      int new_state = getState(new_gcd);
      dp[i][new_state] = min(dp[i][new_state], cost + c[i]);
    }
  }

  return dp[n][1]; // 返回gcd=1的最小代价
}
```

---
处理用时：97.53秒