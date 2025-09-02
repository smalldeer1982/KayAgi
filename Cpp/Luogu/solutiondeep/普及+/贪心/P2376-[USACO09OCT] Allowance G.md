# 题目信息

# [USACO09OCT] Allowance G

## 题目描述

作为创造产奶纪录的回报，Farmer John 决定开始每个星期给Bessie 一点零花钱。

FJ 有一些硬币，一共有 $N (1 \le N \le 20)$ 种不同的面额。每一个面额都能整除所有比它大的面额。

他想用给定的硬币的集合，每个星期至少给 Bessie 某个零花钱的数目 $C (1 \le C \le 100000000)$。请帮他计算他最多能支付多少个星期的零花钱。


## 样例 #1

### 输入

```
3 6
10 1
1 100
5 120```

### 输出

```
111```

# AI分析结果



### 综合分析与结论
本题核心在于利用面额整除特性实现贪心策略。所有题解均基于以下逻辑：优先使用大面额硬币减少浪费，当无法凑整时用最小面额补缺口。关键差异在于是否批量处理相同支付模式来优化时间复杂度。最优解法需结合贪心正确性证明与批量计算优化。

---

### 精选题解与评分

#### 1. ButterflyDew（★★★★★）
**关键亮点**：  
- 给出严谨的贪心策略数学证明  
- 明确指出题目条件"大面额能被小面额整除"是贪心成立的关键  
- 提出"用最小面额产生浪费"的核心思想  

**核心代码思想**：  
```cpp
// 每次支付时：
int x = c;
// 从大到小尽可能使用硬币
for (i从大到小遍历硬币)
   使用尽可能多的当前硬币
// 若仍有剩余，找最小可补的硬币
for (i从小到大遍历硬币)
   找到第一个能补足剩余的硬币
```

#### 2. kkxhh（★★★★☆）
**关键亮点**：  
- 引入批量计算优化，记录每次支付方案并复用  
- 通过取最小值确定复用次数，减少循环次数  
- 代码实现包含高效IO优化  

**核心代码片段**：  
```cpp
int ans = 1e9;
for (所有硬币) ans = min(ans, 当前硬币数/使用量); // 计算可复用次数
sum += ans; // 批量增加答案
for (所有硬币) 数量 -= ans*使用量; // 批量扣除硬币
```

#### 3. Super_Cube（★★★★☆）
**关键亮点**：  
- 代码简洁易读，降序排序逻辑清晰  
- 使用双循环结构突出贪心层次  
- 正确处理硬币数量耗尽情况  

**核心实现**：  
```cpp
stable_sort(v降序); // 按面值从大到小排序
while(1) {
    int k = c;
    for (大面额硬币) 尽可能使用;
    if (仍有剩余) for (小面额硬币) 找第一个能补的;
    if (无法补足) break;
    ans++;
}
```

---

### 关键思路与技巧总结
1. **整除特性应用**：大面额能被小面额整除 → 小面额可组合出任意大面额的倍数，保证贪心有效性  
2. **分层贪心策略**：  
   - 第一层：优先用大面额填满  
   - 第二层：用最小可能的小面额补缺口  
3. **预处理优化**：直接处理面额≥C的硬币，减少后续计算量  
4. **批量计算**：记录单次支付方案，通过取最小值确定可复用次数，避免逐周计算  

---

### 拓展与相似题目
1. **同类题目推荐**：  
   - [P2924 [USACO08DEC]Largest Fence G](https://www.luogu.com.cn/problem/P2924)（几何贪心）  
   - [P5020 货币系统](https://www.luogu.com.cn/problem/P5020)（面额覆盖问题）  
   - [P2217 [HAOI2007]分割矩阵](https://www.luogu.com.cn/problem/P2217)（整除性质应用）  

2. **调试心得摘录**：  
   - *"当剩余金额>0时，必须从最小面额开始反向查找，否则可能跳过可用硬币"* —— 强调补缺口方向的重要性  
   - *"批量扣除硬币数量前要确认v[i]非零，否则除零错误"* —— 边界条件处理经验  

---

### 核心代码参考（ButterflyDew思路）
```cpp
sort(coins.begin(), coins.end(), greater<>());
int weeks = 0;
while (true) {
    int remain = C;
    vector<int> used(n, 0);
    
    // 阶段1：用大面额填充
    for (int i = 0; i < n; ++i) {
        used[i] = min(coins[i].count, remain / coins[i].val);
        remain -= used[i] * coins[i].val;
    }
    
    // 阶段2：补缺口
    if (remain > 0) {
        for (int i = n-1; i >= 0; --i) {
            if (coins[i].count > used[i] && coins[i].val >= remain) {
                used[i]++;
                remain -= coins[i].val;
                break;
            }
        }
    }
    
    if (remain > 0) break;
    
    // 计算可复用次数
    int repeat = INT_MAX;
    for (int i = 0; i < n; ++i) 
        if (used[i]) repeat = min(repeat, coins[i].count / used[i]);
    
    weeks += repeat;
    for (int i = 0; i < n; ++i)
        coins[i].count -= used[i] * repeat;
}
```

---
处理用时：62.64秒