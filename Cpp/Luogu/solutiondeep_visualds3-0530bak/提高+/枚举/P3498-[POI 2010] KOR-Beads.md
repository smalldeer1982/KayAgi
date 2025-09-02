# 题目信息

# [POI 2010] KOR-Beads

## 题目描述

Byteasar 有 $n$ 个珠子，第 $i$ 个颜色为 $a_i$，和一台机器。

Byteasar 可以选定一个值 $k$，然后机器会让 $1\sim k$ 的珠子组成项链 $b_1$，$k+1\sim 2k$ 的珠子组成项链 $b_2$，以此类推，**最后 $n\bmod k$ 个珠子不会组成项链，而是被丢弃**。

现在让你求出一个 $k$ 值，使得在 $\left\lfloor\dfrac{n}{k}\right\rfloor$ 个项链 $b$ 中，存在 **不同的** 项链数量最多。

项链可以反转，形式化地，$b_x$ 和 $b_y$ 不同，当且仅当存在至少一个 $i$，使得 $b_{x,i}\ne b_{y,i}$ 且 $b_{x,i} \ne b_{y,k-i+1}$。

例如 $[1,2,3]$ 和 $[3,2,1]$ 是相同的，而 $[1,2,3]$ 和 $[2,3,1]$ 是不同的。

## 说明/提示

对于全部数据，$1\le n\le2\times 10^5$，且 $\forall 1\le i\le n$，有 $1\le a_i\le n$。

## 样例 #1

### 输入

```
21
1 1 1 2 2 2 3 3 3 1 2 3 3 1 2 2 1 3 3 2 1```

### 输出

```
6 1
2```

# AI分析结果



## 算法分类
哈希（Hashing）、枚举（Enumeration）

## 题解思路与算法要点

### 核心逻辑
1. **哈希预处理**：计算前缀哈希（正序）和后缀哈希（逆序），支持快速获取任意子串的正/反哈希值
2. **调和级数枚举**：枚举所有可能的k值，总时间复杂度为O(n log n)
3. **高效判重机制**：用哈希表存储已出现的子串特征，处理正反视为同一的情况

### 关键实现
1. **双哈希处理**：对每个子串同时计算正序和逆序哈希值，取两者最小值（或乘积）作为唯一标识
2. **时间戳优化**：通过记录时间戳避免哈希表清空操作，降低时间复杂度
3. **剪枝策略**：当剩余可能子串数不足以超越当前最优解时提前终止

```c++示例
// 预处理部分
unsigned long long power[MAXN], ha1[MAXN], ha2[MAXN];
for(int i=1; i<=n; i++) {
    ha1[i] = ha1[i-1] * BASE + a[i];
    power[i] = power[i-1] * BASE;
}
for(int i=n; i>=1; i--) 
    ha2[i] = ha2[i+1] * BASE + a[i];

// 哈希计算
inline unsigned long long get_hash(int l, int r, bool reverse) {
    return reverse ? ha2[l] - ha2[r+1]*power[r-l+1] 
                   : ha1[r] - ha1[l-1]*power[r-l+1];
}
```

## 题解评分（≥4★）

### [4.5★] 作者：beng
- **核心亮点**：手写哈希表+时间戳优化，时间复杂度最优
- **创新点**：使用双哈希存储正反序列，通过取模位置记录时间戳避免重复初始化
- **代码质量**：变量命名清晰，但未使用STL容器，可读性稍弱

### [4.2★] 作者：zhangxiao666
- **核心亮点**：使用map清晰展示算法逻辑，适合教学理解
- **优化点**：直接存储正反哈希值，采用自然溢出简化运算
- **不足**：map的O(log n)查询影响性能

### [4.0★] 作者：XyzL
- **核心亮点**：模块化设计，包含详细注释
- **创新点**：采用模数优化哈希冲突
- **不足**：未实现剪枝策略

## 最优思路提炼

1. **调和级数优化**：利用Σ(n/k) ≈ O(n log n)的特性，保证枚举k值的可行性
2. **双哈希判等**：同时计算正反哈希值，通过取min或乘积累加作为唯一标识
3. **时间戳技巧**：用当前k值标记哈希槽位，避免重复初始化
4. **剪枝策略**：当n/k < 当前最优解时提前终止

## 同类题目推荐

1. **P3370 字符串哈希**（哈希基础模板）
2. **P2852 [USACO06DEC]Milk Patterns G**（哈希处理重复子串）
3. **P3649 [APIO2014]回文串**（回文串哈希处理）

## 可视化设计

### 动画方案
1. **分帧演示**：
   - 步骤1：显示当前k值分割线（红色虚线）
   - 步骤2：高亮当前处理的子串（蓝色方块）
   - 步骤3：显示正反哈希值计算过程（黄色公式弹出）
   - 步骤4：哈希表插入动画（绿色条目闪烁）

2. **像素风格**：
   ```javascript
   // 伪代码示例
   function drawHashTable() {
       ctx.fillStyle = '#8BDBE5'; // 水蓝色背景
       drawGrid(10, 10, 16*8, 16*8); // 16x16像素网格
       currentHash.forEach((val, idx) => {
           drawPixelText(idx%16*8, Math.floor(idx/16)*8, val.toString(16));
       });
   }
   ```

3. **音效设计**：
   - 成功插入哈希表：8-bit "ping"声（440Hz方波）
   - 重复哈希值：低沉"bump"声（220Hz方波）
   - 剪枝触发：快速下滑音效

## 调试心得摘录

> "哈希基数选择19260817时AC，用10007会WA，说明大质数对减少碰撞至关重要" —— 作者：CheemsaDoge  
> "发现正反哈希相乘比单独存储效率提升30%" —— 作者：_zhy  
> "时间戳优化使运行时间从1.2s降至0.4s" —— 作者：beng

---

## 核心代码实现
```c++
// 基于beng题解的优化版本
vector<int> solve(int n, vector<int>& a) {
    constexpr ull BASE = 19260817;
    vector<ull> ha1(n+2), ha2(n+2), power(n+2);
    vector<int> ans;

    // 预处理哈希
    power[0] = 1;
    for(int i=1; i<=n; ++i) {
        ha1[i] = ha1[i-1] * BASE + a[i-1];
        power[i] = power[i-1] * BASE;
    }
    for(int i=n; i>=1; --i)
        ha2[i] = ha2[i+1] * BASE + a[i-1];

    // 哈希表相关
    constexpr int MOD = 1e6+7;
    vector<ull> hashtable(MOD);
    vector<int> timestamp(MOD, -1);

    int max_cnt = 0;
    for(int k=1; k<=n; ++k) {
        int cnt = 0;
        for(int i=k; i<=n; i+=k) {
            ull h1 = ha1[i] - ha1[i-k] * power[k];
            ull h2 = ha2[i-k+1] - ha2[i+1] * power[k];
            ull key = min(h1, h2);

            int pos = key % MOD;
            while(true) {
                if(timestamp[pos] != k) {
                    hashtable[pos] = key;
                    timestamp[pos] = k;
                    ++cnt;
                    break;
                }
                if(hashtable[pos] == key) break;
                pos = (pos+1) % MOD;
            }
        }
        // 更新答案逻辑...
    }
    return ans;
}
```

---
处理用时：76.78秒