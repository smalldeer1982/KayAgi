# 题目信息

# New Product

## 题目背景

**一个经商的神奇故事……**

(善意提醒：注意时限！）


## 题目描述

LiM 有一家手工糕点店，因为糕点既实惠又好吃，于是积累了 $P$ 个常客（$P$ 为质数）。

每次这家店出 New Product（新品）的时候，都会做很多个，这 $P$ 个人都会支持，支持方法是：

**每个人买的数量都相同，而且买的总数要尽量多。**

这家店共有 $B$ 个工人，一分钟可以生产已经生产的数量的 $A$ 倍。

（注：一开始有一个已制作的 New Product 作为制作样品）

而当制作完毕，抢购（只考虑常客）完后：

**为了考虑工人们，最后要剩下正好 $B$ 个。**

下面给出已知条件，请你帮 LiM 算算最少要工作多长时间吧！

## 说明/提示



#### 样例 $1$ 解释：

有 $5$ 个常客，一分钟可以生产已生产的 $2$ 倍，有 $3$ 个工人。

则最小需要 $3$ 分钟（生产 $2^3=8$ 个）才能符合要求。

#### 样例 $2$ 解释：

有 $2$ 个常客，一分钟可以生产已生产的 $2$ 倍，有 $2$ 个工人。

因为不管是多长时间都会余下 $0$ 个，所以输出 `Couldn't Produce!`。


----------------------------------------------

说明：

LiM 不是工人哦！

对于每组 New Product，常客数量不同。

对于 $20\%$ 的数据，$T=1$，所有条件 $\leqslant 100$。

对于 $100\%$ 的数据，$T \leqslant 5000$，所有条件 $\leqslant 5 \times 10^4$。$P$ 为质数。

## 样例 #1

### 输入

```
1
5 2 3```

### 输出

```
3```

## 样例 #2

### 输入

```
1
2 2 2```

### 输出

```
Couldn't Produce!```

# AI分析结果



---

## 算法分类：数论

## 题解思路与核心算法

### 核心公式推导
题目等价于求解离散对数问题：求最小非负整数 x 使得  
$$ A^x \equiv B \mod P $$  
其中 P 为质数，B 必须满足 $0 \leq B < P$。当且仅当满足以下条件时存在解：
1. A 和 P 不互质时，B 必须为 0
2. B = 1 时 x = 0
3. A = 0 时 B 必须为 0

### 解决难点
1. **边界条件处理**：需特判 B=1、A=0、B≥P 等情况
2. **循环节优化**：利用费马小定理将解空间缩小到 [0, P-1)
3. **高效求解**：使用 BSGS 算法将时间复杂度优化至 $O(\sqrt{P})$

### 关键数学步骤
BSGS 算法实现流程：
1. 计算分块大小 $m = \lceil \sqrt{P} \rceil$
2. 预处理 $ba^j \mod P$ 存入哈希表
3. 枚举 $i$ 计算 $a^{im} \mod P$ 并在哈希表中查找匹配

---

## 高星题解推荐 (≥4星)

### 1. 皎月半洒花（★★★★★）
- **亮点**：正确处理模数为质数的所有边界条件，使用 unordered_map 优化查询效率
- **核心代码**：
```cpp
void bsgs(LL x, LL y, LL p){
    LL P = ceil(sqrt(p)), Q = expow(x, -P + 2*(p-1), p);
    for(LL i=1,j=0; j<P; ++j, (i*=x)%=p)
        Hash[i] = j;
    for(LL i=y,j=0; j<=P; ++j, (i*=Q)%=p)
        if(Hash.count(i)) return Hash[i]+j*P;
}
```

### 2. 123rrc（★★★★☆）
- **亮点**：详细处理了 6 种边界情况，代码可读性极强
- **特判逻辑**：
```cpp
if(b >= p) 无解;
if(b == 1) return 0;
if(a == 0) return b == 0 ? 1 : 无解;
```

### 3. emptysetvvvv（★★★★☆）
- **亮点**：完整的 BSGS 实现，包含详细的数学推导注释
- **分块处理**：
```cpp
const int q = ceil(sqrt(p));
for(int j=1; j<=q; j++) // 预处理右部
for(int i=1; i<=q; i++) // 枚举左部
```

---

## 最优思路提炼

### 关键技巧
1. **分块哈希**：将指数分解为 $x = im - j$ 形式，预处理后半部分
2. **逆元优化**：使用费马小定理计算 $a^{-m} \equiv a^{p-1-m} \mod p$
3. **边界剪枝**：优先处理 B=1、A=0 等特殊情形

### 思维突破点
将指数方程转化为分块哈希问题，利用哈希表的 $O(1)$ 查询特性，将暴力 $O(P)$ 优化为 $O(\sqrt{P})$。

---

## 同类题目推荐
1. [P3846] 可爱的质数 - BSGS 模板题
2. [CF1106F] 线性递推与 BSGS 结合
3. [POJ2417] Discrete Logging - 基础离散对数问题

---

## 可视化方案设计

### 动画流程设计
```mermaid
graph TD
    Start[输入A,B,P] --> Check[B≥P?]
    Check -->|Yes| NoSol[输出无解]
    Check -->|No| SpecialCase[B=1?]
    SpecialCase -->|Yes| Output0[输出0]
    SpecialCase -->|No| ComputeM[计算m=ceil(sqrt(P))]
    ComputeM --> PreHash[预处理j=0..m-1的BA^j]
    PreHash --> BuildMap[建立值→j的哈希表]
    BuildMap --> GiantStep[计算A^(im) mod P]
    GiantStep --> Query[查询哈希表中是否存在]
    Query -->|存在| Output[输出im-j]
    Query -->|不存在| NextI[i++]
    NextI --> GiantStep
```

### 8位像素风格演示
```javascript
// Canvas 绘制伪代码
function drawStep(ctx, step) {
    // 使用16色调色板绘制当前计算步骤
    const colors = ["#000","#00F","#0F0","#FF0","#F0F"];
    ctx.fillStyle = colors[step % 5];
    // 绘制分块示意图
    drawGrid(m, current_i, current_j);
    // 高亮当前计算的哈希键
    highlightHashEntry(current_val);
}
```

### 音效触发逻辑
- **计算步骤**：每处理一个 j/i 播放 500Hz 方波 50ms
- **找到匹配**：播放上升琶音（C4-E4-G4）
- **无解情况**：播放低频噪音

---

## 核心代码实现
```cpp
int BSGS(int a, int b, int p) {
    if(b == 1) return 0;
    unordered_map<int,int> hash;
    int m = ceil(sqrt(p));
    // 预处理右边 b*a^j
    for(int j=0, val=b; j<m; j++) {
        hash[val] = j;
        val = 1LL * val * a % p;
    }
    // 计算 a^m
    int am = 1;
    for(int i=0; i<m; i++) 
        am = 1LL * am * a % p;
    // 枚举左边 a^(im)
    for(int i=1, val=am; i<=m; i++) {
        if(hash.count(val))
            return i * m - hash[val];
        val = 1LL * val * am % p;
    }
    return -1;
}
```

---
处理用时：72.48秒