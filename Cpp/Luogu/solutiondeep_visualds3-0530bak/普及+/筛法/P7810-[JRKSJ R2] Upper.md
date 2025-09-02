# 题目信息

# [JRKSJ R2] Upper

## 题目描述

有 $n$ 张扑克，第 $i$ 张扑克上写有一个正整数 $a_i$。

现在要把扑克划分成若干个合法的连续子段，其中，一个连续子段 $[l,r]$ “合法”当且仅当这个子段同时满足两个条件： 

* $a_l< a_r$
* $\gcd(a_l,a_r)>1$ 

请问最多能划分多少段。如果没有合法的划分方案，输出 $-1$ 即可。

如果您不知道 $\gcd$ 是什么意思，请看“提示”部分。

## 说明/提示

### 数据范围
本题采用捆绑测试。

对于 $100\%$ 的数据，$2\le n\le 10^5$，$1\le a_i\le 10^9$。

| $\text{Subtask}$ | $n\le$ | $a_i\le$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $5$ | $10^9$ | 无 | $5$ |
| $2$ | $3\times10^3$ | $10^9$ | 无 | $15$ |
| $3$ | $2\times10^4$ | $10^6$ | 无 | $20$ |
| $4$ | $2\times 10^4$ | $10^9$ | 无 | $10$ |
| $5$ | $10^5$ | $10^9$ | 数据随机 | $10$ |
| $6$ | $10^5$ | $10^9$ | 无 | $40$ |

### 样例解释
对于样例 $1$，有且仅有一种划分方案 $\{2,1,8\},\{3,9\}$。\
对于样例 $2$，无合法的划分方案。

### 提示
对于两个正整数 $a,b$，$\gcd(a,b)$ 为它们的最大公因数，即满足既是 $a$ 的因数又是 $b$ 的因数的数中最大的数。

## 样例 #1

### 输入

```
5
2 1 8 3 9```

### 输出

```
2```

## 样例 #2

### 输入

```
5
5 4 3 2 1```

### 输出

```
-1```

## 样例 #3

### 输入

```
20
20 9 36 36 40 8 3 10 9 20 18 12 30 20 30 15 8 9 27 45```

### 输出

```
7```

# AI分析结果



## 唯一算法分类
动态规划 + 质因数分解 + 权值线段树

---

## 综合分析与结论

### 核心算法流程
1. **动态规划定义**：`f[i]` 表示前 `i` 个元素的最大划分数，初始 `f[0] = 0`
2. **质因数分解**：对每个 `a_i` 分解质因数，得到其所有质因子集合
3. **权值线段树**：为每个质因子维护动态开点线段树，存储离散化后的 `a_j` 值与对应的 `f[j-1]` 最大值
4. **转移优化**：对于当前 `a_i` 的每个质因子 `d`，在 `d` 的线段树中查询所有 `< a_i` 的位置的最大值，更新 `f[i]`
5. **离散化**：将 `a` 数组离散化以压缩权值范围

### 解决难点
- **质因数处理**：通过分解质因子将 `gcd` 条件转化为质因子交集问题
- **快速查询**：权值线段树支持 `O(log n)` 查询区间最大值
- **空间优化**：动态开点线段树仅维护实际用到的质因子，避免全量存储

### 可视化设计思路
- **像素风格展示**：用不同颜色方块表示不同质因子，线段树节点以网格形式展示
- **动态分解动画**：显示每个 `a_i` 分解出的质因子及其对应的线段树
- **音效提示**：成功查询时播放上扬音效，更新线段树节点时播放轻微点击音
- **步进控制**：允许单步执行观察质因子分解、线段树查询和 `f[i]` 更新过程

---

## 题解清单（≥4星）

### 1. KazamaRuri（5★）
- **亮点**：代码简洁高效，质数筛预处理优化分解速度，动态开点线段树空间控制优秀
- **核心代码**：
  ```cpp
  for(int i=1;i<=n;i++)
    for(auto x:q[i]){
      if(rt[x]) f[i] = max(f[i], ask(rt[x],1,n,a[i]-1)+1);
      if(f[i-1]>=0) upd(rt[x],1,n,a[i],f[i-1]);
    }
  ```

### 2. ZillionX（5★）
- **亮点**：Exact Division 加速质因数分解，哈希表管理线段树根节点
- **关键优化**：
  ```cpp
  ui inv32(ui n) { // Exact Division 核心
    ui x = 1;
    x *= 2u-n*x, x *= 2u-n*x, x *= 2u-n*x, x *= 2u-n*x;
    return x;
  }
  ```

### 3. Spasmodic（4★）
- **亮点**：清晰的质数筛实现，代码结构模块化
- **质因数分解**：
  ```cpp
  void dcp(int id){
    int x = a[id];
    for(int i=1; p[i]*p[i]<=x; i++)
      if(x%p[i]==0){
        pr[id][++cnt[id]] = p[i];
        while(x%p[i]==0) x /= p[i];
      }
    if(x>1) pr[id][++cnt[id]] = x;
  }
  ```

---

## 最优思路提炼

### 关键技巧
1. **质因子桥梁**：将 `gcd>1` 转换为存在公共质因子，缩小查询范围
2. **权值离散化**：将大范围数值映射到连续区间，降低线段树高度
3. **动态开点**：仅维护实际存在的质因子对应的线段树，节省空间
4. **前驱贡献累积**：通过 `f[i-1]` 更新线段树，确保后续查询包含当前贡献

### 思维突破点
- **双重条件分离**：将 `a_j < a_i` 与 `gcd` 条件解耦，前者通过权值线段树的区间查询处理，后者通过质因子分治
- **时间换空间**：对每个质因子独立维护数据结构，牺牲部分内存换取查询效率

---

## 同类型题目推荐

1. **P1972 [SDOI2009]HH的项链**  
   （区间统计 + 树状数组优化）

2. **P5490 【模板】扫描线**  
   （离散化 + 线段树覆盖计数）

3. **P3383 【模板】线性筛素数**  
   （质数筛基础训练）

---

## 可视化代码片段（JS Canvas）

```javascript
class PixelAnimator {
  constructor(canvas) {
    this.ctx = canvas.getContext('2d');
    this.ctx.imageSmoothingEnabled = false;
    this.scale = 4; // 8-bit 风格缩放
  }

  drawPrimeGrid(primes, x, y) {
    primes.forEach((p, i) => {
      this.ctx.fillStyle = this.getPrimeColor(p);
      this.ctx.fillRect(x + i*8*this.scale, y, 6*this.scale, 6*this.scale);
    });
  }

  updateSegTree(d, pos, value) {
    // 播放线段树更新动画
    playSound('click');
    this.highlightNode(d, pos);
    this.drawValueChange(pos, value);
  }
}
```

---

## 复古音效设计（Web Audio）

```javascript
const audioCtx = new (window.AudioContext || window.webkitAudioContext)();

function playSound(type) {
  const oscillator = audioCtx.createOscillator();
  const gainNode = audioCtx.createGain();
  
  oscillator.connect(gainNode);
  gainNode.connect(audioCtx.destination);

  // 8-bit 音效参数
  const freq = type === 'success' ? 880 : 440;
  const duration = type === 'success' ? 0.2 : 0.1;

  oscillator.frequency.setValueAtTime(freq, audioCtx.currentTime);
  gainNode.gain.setValueAtTime(0.1, audioCtx.currentTime);
  
  oscillator.start();
  oscillator.stop(audioCtx.currentTime + duration);
}
```

---
处理用时：83.69秒