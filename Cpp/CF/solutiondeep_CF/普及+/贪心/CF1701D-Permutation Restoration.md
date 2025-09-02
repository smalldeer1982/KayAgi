# 题目信息

# Permutation Restoration

## 题目描述

Monocarp 有一个长度为 $n$ ，由 $1$ ~ $n$ 构成的数组  $a$ ，其中每个元素在 $a$ 中出现且仅出现 $1$ 次。

现在 Monocarp 计算一个数组 $b$ ，使得 $b_i=\lfloor\frac{i}{a_i}\rfloor$ 。

现在给出 $b$ 数组，要求求出任意一组 $a$ 。

注意：保证对于所给出的 $b$ 至少有一组 $a$ 与之对应。

## 样例 #1

### 输入

```
4
4
0 2 0 1
2
1 1
5
0 0 1 4 1
3
0 1 3```

### 输出

```
2 1 4 3 
1 2 
3 4 2 1 5 
3 2 1```

# AI分析结果



# Permutation Restoration

## 题目描述

Monocarp 有一个长度为 $n$，由 $1$ 至 $n$ 构成的数组 $a$，其中每个元素在 $a$ 中出现且仅出现一次。

现在 Monocarp 计算一个数组 $b$，使得 $b_i=\lfloor\frac{i}{a_i}\rfloor$。

现给定数组 $b$，要求求出任意一组满足条件的 $a$。

注意：保证对于所给出的 $b$ 至少存在一组对应的 $a$。

---

## 题解综合分析

### 核心思路
所有题解均基于以下数学推导：
1. 由 $b_i = \lfloor i/a_i \rfloor$ 得 $\frac{i}{b_i+1} < a_i \le \frac{i}{b_i}$
2. 处理为区间 $[l_i, r_i]$，其中 $l_i = \lfloor i/(b_i+1) \rfloor + 1$，$r_i = \lfloor i/b_i \rfloor$（特判 $b_i=0$ 时 $r_i=n$）

### 贪心策略
采用按左端点排序 + 优先队列维护右端点的贪心方法：
1. 将所有区间按左端点升序排序
2. 从左到右枚举数值 $x$（1到n），将左端点等于 $x$ 的区间加入以右端点为小根堆的优先队列
3. 每次取出堆顶（右端点最小的区间）分配当前数值 $x$

---

## 精选题解

### 1. Morax_ 题解（⭐⭐⭐⭐⭐）
**亮点**：
- 清晰的数学推导与区间转化
- 使用优先队列维护可分配区间的右端点
- 代码结构清晰，包含详细注释

**核心代码**：
```cpp
for(int i=1;i<=n;++i){
    // 将左端点等于i的区间加入堆
    while(cnt<=n && k[cnt].l==i){
        int id=k[cnt].i;
        Q.push({b[id]==0 ? n : id/b[id], id});
        cnt++;
    }
    // 取出最小右端点的区间分配i
    a[Q.top().second] = i;
    Q.pop();
}
```

### 2. intel_core 题解（⭐⭐⭐⭐）
**亮点**：
- 使用vector预存各左端点对应的区间
- 简洁的优先队列实现
- 代码行数少但功能完整

**代码片段**：
```cpp
for(int i=1;i<=n;i++){
    for(int x:v[i]) q.push({r[x],x}); // 按右端点入堆
    a[q.top().second] = i; 
    q.pop();
}
```

### 3. roumeideclown 题解（⭐⭐⭐⭐）
**亮点**：
- 明确的贪心正确性证明
- 使用自定义结构体与运算符重载
- 包含WA调试经验（强调不能简单排序）

**关键实现**：
```cpp
struct line { int l,r,id; };
priority_queue<line, vector<line>, greater<line>> q; // 按r排序

while(a[j].l==i && j<=n){
    q.push(a[j++]); // 左端点等于i的入堆
}
ans[q.top().id] = i; // 分配当前数值
```

---

## 关键技巧总结
1. **区间转换**：将数学约束转化为区间范围是解题突破口
2. **贪心选择**：按左端点排序后，优先处理右端点最小的区间（类似任务调度）
3. **数据结构**：优先队列（小根堆）维护当前可分配区间
4. **特判处理**：对 $b_i=0$ 的情况单独处理右端点

---

## 相似题目推荐
1. [P1969 积木大赛](https://www.luogu.com.cn/problem/P1969) - 区间覆盖与贪心
2. [P2887 防晒霜](https://www.luogu.com.cn/problem/P2887) - 优先队列处理区间分配
3. [P1250 种树](https://www.luogu.com.cn/problem/P1250) - 差分约束与区间处理

---
处理用时：55.00秒