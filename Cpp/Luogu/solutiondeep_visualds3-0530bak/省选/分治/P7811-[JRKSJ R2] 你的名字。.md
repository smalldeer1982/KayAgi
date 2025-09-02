# 题目信息

# [JRKSJ R2] 你的名字。

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/73iq08qk.png)

## 题目描述

给你一个长为 $n$ 的序列 $a$，有 $m$ 次查询，每次查询区间 $[l,r]$ 模 $k$ 意义下的最小值。

## 说明/提示

Idea：mcyl35，Solution：mcyl35，Code：mcyl35，Data：cyffff&mcyl35

本题采用捆绑测试。

| $\text{Subtask}$ | $n,m\le$ | $k,a_i\le$ | 特殊性质 | 分值 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| $\text{1}$ | $10^4$ | $10^5$ | 无 | $3$ | $1$ |
| $\text{2}$ | $10^5$ | $300$ | 无 | $6$ | $1$ |
| $\text{3}$ | $10^5$ | $10^5$ | $k\ge 10^3$ | $10$ | $1\to2$ |
| $\text{4}$ | $10^5$ | $10^5$ | 无 | $19$ |$2\to4$ |
| $\text{5}$ | $3\times10^5$ | $10^5$ | 数据随机 | $14$ |$1$ |
| $\text{6}$ | $3\times10^5$ | $10^5$ | $k\ge 10^3$ | $2$ |$2\to3$ |
| $\text{7}$ | $3\times10^5$ | $10^5$ | 无 | $46$ |$2\to5$ |

对于 $100\%$ 的数据，$1\le n,m\le3\times10^5$，$1\le a_i,k\le 10^5$。

前 $6$ 个 $\text{Subtask}$ 的空间限制为 $256\text{MB}$，第 $7$ 个 $\text{Subtask}$ 的空间限制为 $128\text{MB}$。

## 样例 #1

### 输入

```
10 10
15 14 14 4 8 10 18 14 10 9 
2 10 8
2 4 7
3 9 6
1 7 5
3 4 6
6 6 12
4 8 20
1 6 18
7 8 8
2 6 6```

### 输出

```
0
0
0
0
2
10
4
4
2
2```

## 样例 #2

### 输入

```
5 5
77 24 80 90 92 
2 3 84
4 5 37
1 1 4
3 5 85
1 4 46```

### 输出

```
24
16
1
5
24```

# AI分析结果



# [JRKSJ R2] 你的名字 题解分析

## 唯一算法分类
**根号分治**

---

## 核心思路与解决难点

### 根号分治策略
1. **小k处理（k ≤ B）**：
   - 预处理每个k的模值数组，使用分块维护块内最小值
   - 查询时通过块间合并快速获取最小值
   - 时间复杂度：O(nB + m√n)

2. **大k处理（k > B）**：
   - 将模运算转化为 a - ck 的最小值问题
   - 离线处理所有询问，按k的倍数降序排序
   - 使用双指针维护当前处理的元素，插入分块结构维护区间最小值
   - 时间复杂度：O(n√n + m*(v/B))

**分治阈值选择**：B = √v（v为值域上限1e5）

---

## 题解评分（≥4星）

| 题解作者 | 星级 | 核心亮点 |
|---------|------|---------|
| critnos | ⭐⭐⭐⭐ | 双重分块 + 猫树维护块间最小值 |
| CXY07   | ⭐⭐⭐⭐ | 离线排序双指针 + 分块前后缀min |
| dead_X  | ⭐⭐⭐⭐ | 莫队+bitset快速查找余数 |

---

## 最优技巧提炼

### 关键数据结构
```cpp
// 分块维护区间最小值（小k处理）
struct Block {
    int mn[BLOCK_SIZE]; // 块内模k最小值
    void build(int k) {
        for(int i=l; i<=r; i++)
            mn[k] = min(mn[k], a[i]%k);
    }
};

// 分块维护区间后继（大k处理）
struct LargeKBlock {
    int pre[SQRT_N], suf[SQRT_N]; // 块前后缀min
    int st[LOG][SQRT_N]; // 块间ST表
    void update(int pos) {
        // 更新pos所在块的前后缀和ST表
    }
};
```

### 核心算法流程
```cpp
// 大k处理离线流程
vector<Query> queries;
sort(queries.begin(), queries.end(), [](auto &a, auto &b){
    return a.k > b.k; // 按k降序处理
});

int ptr = n;
for(auto &q : queries) {
    while(ptr >=1 && a[ptr] >= q.p) {
        blocks.update(ptr, a[ptr]); // 插入元素
        ptr--;
    }
    ans[q.id] = blocks.query(q.l, q.r) - q.p;
}
```

---

## 同类型题目推荐
1. **P4137 Rmq Problem**（区间mex问题）
2. **P3396 哈希冲突**（根号分治经典）
3. **P5356 [Ynoi2017] 由乃打扑克**（分块+阈值处理）

---

## 可视化设计

### 像素化算法演示
![根号分治可视化](https://i.imgur.com/8WjG7rN.gif)

#### 动画要素：
1. **分界点展示**：左侧红色区域表示k≤B的小模数处理，右侧蓝色区域表示大k处理
2. **块操作高亮**：插入元素时对应块闪烁黄色，查询时绿色覆盖查询区间
3. **音效触发**：
   - 插入元素：8-bit "beep" 音效（频率随值大小变化）
   - 查询完成：马里奥金币音效

#### 交互功能：
```javascript
// 伪代码示例
class Visualizer {
    constructor() {
        this.canvas = document.getElementById("pixel-canvas");
        this.blocks = this.initBlocks(); // 分块像素绘制
        this.speedControl = new SpeedSlider();
    }
    
    renderStep() {
        if(currentMode === SMALL_K) {
            this.highlightBlock(k); // 当前处理的k值块
            this.playSound(440 + k*10); // 音调随k变化
        } else {
            this.drawPointer(ptr); // 双指针移动动画
        }
    }
}
```

---

## 总结
本题通过**根号分治**平衡了时间与空间复杂度，关键点在于：
1. 对模数k的阈值分治策略
2. 离线处理大k时的倍数降序扫描
3. 分块数据结构的高效维护

**调试经验**：部分题解通过调整分块大小（如n/sqrt(m)）显著优化常数，建议结合具体数据分布动态调整阈值。

---
处理用时：70.66秒