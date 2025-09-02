# 题目信息

# Coprime Arrays

## 题目描述

#### 题意：

我们称一个大小为 $n$ 的数组 $a$ 互质，当且仅当 $gcd(a_1,a_2,\cdots,a_n)=1$，$gcd$ 是最大公约数的意思。

给定 $n,k$，对于每个 $i$ $(1\le i\le k)$，你都需要确定这样的数组的个数——长度为 $n$ 的互质数组 $a$ ，满足对每个 $j$ $(1\le j\le n)$，都有 $1\le a_j\le i$。

答案可能非常大，请对 $10^9+7$ 取模。

## 说明/提示

因为互质数组的数量比较多，我们只列出不互质的：

当 $i=1$ 时，唯一的数组就是互质的，$b_1=1$。

当 $i=2$ 时，数组 $[2,2,2]$ 不是互质的，$b_2=7$。

当 $i=3$ 时，数组 $[2,2,2],[3,3,3]$ 不是互质的，$b_3=25$。

当 $i=4$ 时，数组 $[2,2,2],[3,3,3],[2,2,4],[2,4,2],[2,4,4],[4,2,2],[4,2,4],[4,4,2],[4,4,4]$ 不是互质的，$b_4=55$。

Translated by 小粉兔

## 样例 #1

### 输入

```
3 4
```

### 输出

```
82
```

## 样例 #2

### 输入

```
2000000 8
```

### 输出

```
339310063
```

# AI分析结果



### 唯一算法分类
**莫比乌斯反演 + 差分数组优化**

---

### 综合分析与结论
**核心思路**：  
利用莫比乌斯反演将互质条件转化为倍数容斥，再通过差分数组高效维护每个前缀的贡献变化，最终通过前缀和累加得到答案。

**算法流程**：  
1. **预处理**：  
   - 线性筛法计算莫比乌斯函数 $\mu(d)$  
   - 预处理每个数 $x$ 的 $n$ 次幂 $x^n \bmod MOD$  
2. **差分贡献**：  
   - 对每个 $d$，枚举其倍数 $i$，计算 $\mu(d) \cdot (\lfloor i/d \rfloor^n - \lfloor (i-1)/d \rfloor^n)$，并更新差分数组  
3. **前缀和**：  
   - 累加差分数组得到每个 $b_i$，再计算异或和  

**解决难点**：  
- 直接计算每个 $b_i$ 的复杂度为 $O(k \sqrt{k})$，不可行  
- 通过观察 $\lfloor \frac{i}{d} \rfloor$ 变化的规律，仅在 $d \mid i$ 时产生贡献，将复杂度优化至 $O(k \log k)$  

**可视化设计**：  
- **动画方案**：  
  - **网格展示**：用像素网格表示差分数组，每个单元格对应一个 $i$  
  - **颜色标记**：当前处理的 $d$ 对应的贡献区域高亮为蓝色，数值变化时闪烁黄色  
  - **步进控制**：允许单步执行，观察每个 $d$ 如何更新差分数组  
- **复古风格**：  
  - 8-bit 音效：每次更新差分时播放“哔”声，前缀和完成时播放短旋律  
  - Canvas 绘制：用 16x16 像素块表示数组元素，背景为深灰色，数值用绿色像素点密度表示  
  - AI 演示模式：自动按 $d=1,2,\dots,k$ 的顺序播放贡献过程  

---

### 题解清单（≥4星）
1. **Elegia（★★★★★）**  
   - 关键亮点：清晰推导莫比乌斯反演公式，差分数组维护贡献成段变化  
   - 代码亮点：线性筛同时预处理幂次，高效处理负数取模  

2. **lahlah（★★★★☆）**  
   - 关键亮点：简洁的差分公式推导，直接枚举约数贡献  
   - 代码亮点：预处理幂次后直接计算差分，逻辑紧凑  

3. **ZillionX（★★★★☆）**  
   - 关键亮点：Dirichlet 卷积优化至 $O(k \log \log k)$，理论复杂度更优  
   - 代码亮点：魔改 Dirichlet 前缀和实现高效计算  

---

### 核心代码实现
```cpp
#include <cstdio>
using namespace std;
typedef long long ll;
const int P = 1e9+7, N = 2e6+10;
int n, k, pc;
int pw[N], mu[N], p[N], b[N];
bool vis[N];

void sieve() {
    mu[1] = 1;
    for (int x=2; x<=k; ++x) {
        if (!vis[x]) p[++pc]=x, mu[x]=-1;
        for (int j=1; x*p[j]<=k; ++j)
            if (x%p[j]==0) { mu[x*p[j]]=0; break; }
            else mu[x*p[j]] = -mu[x], vis[x*p[j]]=1;
    }
}

int pow(int x, int k) {
    int ret=1;
    for (;k;k>>=1,x=(ll)x*x%P) if(k&1) ret=(ll)ret*x%P;
    return ret;
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i=1; i<=k; ++i) pw[i] = pow(i, n);
    sieve();
    for (int d=1; d<=k; ++d) {
        for (int i=d; i<=k; i+=d) {
            int x = i/d;
            int val = (ll)(pw[x] - pw[x-1] + P) * (P + mu[d]) % P;
            b[i] = (b[i] + val) % P;
        }
    }
    int ans=0, sum=0;
    for (int i=1; i<=k; ++i) {
        sum = (sum + b[i]) % P;
        ans = (ans + (sum ^ i)) % P;
    }
    printf("%d\n", ans);
    return 0;
}
```

---

### 同类型题与套路
**通用套路**：  
- 当需要计算多个前缀的容斥值时，考虑差分贡献的成段性  
- 莫比乌斯反演结合整除分块的优化技巧  

**相似题目**：  
1. [P2522 Problem B](https://www.luogu.com.cn/problem/P2522)  
2. [P3455 ZAP-Queries](https://www.luogu.com.cn/problem/P3455)  
3. [P3312 数表](https://www.luogu.com.cn/problem/P3312)  

---

### 可视化代码片段（Canvas 动画）
```javascript
class DiffVisualizer {
    constructor(canvas, k) {
        this.ctx = canvas.getContext('2d');
        this.k = k;
        this.cellSize = 10;
        this.currentD = 1;
        this.playing = false;
        // 初始化颜色映射
        this.colorMap = new Array(k+1).fill(0).map(() => 
            `hsl(${Math.random()*360}, 70%, 50%)`);
    }

    drawGrid(b) {
        this.ctx.clearRect(0, 0, canvas.width, canvas.height);
        for (let i=1; i<=this.k; ++i) {
            const x = (i-1)*this.cellSize % 500;
            const y = Math.floor((i-1)/50) * this.cellSize;
            // 颜色根据差分值强度变化
            const alpha = Math.min(0.5 + b[i]/100, 1);
            this.ctx.fillStyle = `rgba(100,200,255,${alpha})`;
            this.ctx.fillRect(x, y, this.cellSize-1, this.cellSize-1);
        }
    }

    playStep(d) {
        this.currentD = d;
        // 高亮当前d的影响区域
        for (let i=d; i<=this.k; i+=d) {
            const x = (i-1)*this.cellSize % 500;
            const y = Math.floor((i-1)/50) * this.cellSize;
            this.ctx.fillStyle = 'rgba(255,255,0,0.3)';
            this.ctx.fillRect(x, y, this.cellSize, this.cellSize);
        }
        // 播放音效
        beep(100 + d*50, 0.1);
    }
}
```

---

### 个人心得摘录
> "当需要连续计算多个前缀的容斥值时，差分数组是避免重复计算的关键。莫比乌斯函数的符号处理需要特别注意取模后的负数修正。" —— Elegia  
> "预处理幂次时，发现线性筛法可以同时计算质数的快速幂，大幅减少计算量。" —— lahlah  

---

### 复古游戏化设计
**关键元素**：  
- **音效**：使用 Web Audio API 生成 8-bit 音效  
  ```javascript
  function beep(freq, duration) {
    const osc = audioCtx.createOscillator();
    osc.type = 'square';
    osc.frequency.setValueAtTime(freq, audioCtx.currentTime);
    osc.connect(audioCtx.destination);
    osc.start(); osc.stop(audioCtx.currentTime + duration);
  }
  ```
- **像素动画**：每个差分更新对应一个黄色闪光，完成时绿色波纹扩散  
- **积分系统**：每正确处理 1000 个 $d$ 获得 1 积分，积分满时解锁自动播放速度提升  

**AI 演示逻辑**：  
```javascript
function autoPlay() {
    let d = 1;
    const interval = setInterval(() => {
        visualizer.playStep(d);
        if (++d > k) clearInterval(interval);
    }, 100 - speedSlider.value * 10); // 速度可调
}
```

---
处理用时：113.76秒