# 题目信息

# [NEERC 2017] Easy Quest

## 题目描述



A young hero is starting his heroic life. The wise wizard suggested him an easy first quest. During this quest our young hero meets $n$ magical creatures, in specific order. In order to help the young hero, the wizard gave him a clue -- a list of $n$ integers $a_{i}.$

If $a_{i}$ is positive, then the i-th magical creature is benevolent and gives to our hero one magical item of type $a_{i}.$ The hero can keep several items of the same type.

If $a_i$ is negative, then the i-th magical creature is evil and in order to defeat it the young hero needs one magical item of type $−a_{i}.$ All magical items are fragile and can be used only once.

If $a_{i}$ is zero, then the i-th creature is a unicorn. It gives the hero any magical item he asks for, but only one.

Your task is to help the young hero to finish the first quest, defeating all enemies on the way, or say that it is impossible.



## 说明/提示

Time limit: 3 s, Memory limit: 512 MB. 

spj provider:@[shenyouran](/user/137367).

## 样例 #1

### 输入

```
10
1 0 -4 0 0 -1 -3 0 -1 -2
```

### 输出

```
Yes
4 1 3 2
```

## 样例 #2

### 输入

```
5
5 8 0 -6 -3
```

### 输出

```
No
```

## 样例 #3

### 输入

```
3
2 -2 -2
```

### 输出

```
No
```

# AI分析结果



**算法分类**: 贪心

---

### 综合分析与结论
本题核心是贪心策略：**优先消耗已有的物品，无法满足时使用延迟处理的万能物品（0的配额）**。所有题解均采用桶计数 + 贪心延迟处理 0 的思路。关键点在于：
1. 用桶维护物品实时数量。
2. 遇到负数时优先消耗桶中的对应物品，不足则使用之前预留的 0 配额。
3. 记录 0 的补救操作，剩余未使用的 0 输出任意值。

---

### 高星题解推荐

#### 1. Up_Xu 的题解（⭐⭐⭐⭐⭐）
**关键亮点**:
- 使用 `sum` 变量直接记录剩余可用的 0 配额，逻辑简洁。
- 用数组 `a` 记录补救的负数类型，最后统一输出。
- 代码清晰，处理剩余 0 时直接填充固定值（如 1000）。

**核心代码**:
```cpp
int sum = 0, f[1010] = {0}, a[1010], t = 0;
for (遍历每个元素) {
    if (x > 0) f[x]++;
    else if (x < 0) {
        if (f[-x] > 0) f[-x]--;
        else if (sum > 0) a[t++] = -x, sum--;
        else return "No";
    } else sum++;
}
// 输出补救的 a 数组和剩余 sum 的填充值
```

#### 2. Misophiliac 的题解（⭐⭐⭐⭐⭐）
**关键亮点**:
- 代码极简，仅用 `cnt` 和 `top` 分别记录总 0 数和已使用的 0。
- 使用栈存储补救操作，最后直接输出栈和剩余 0。

**核心代码**:
```cpp
int cnt = 0, top = 0, stk[1005], a[1005] = {0};
for (遍历每个元素) {
    if (x > 0) a[x]++;
    else if (x < 0) {
        x = -x;
        if (a[x]) a[x]--;
        else if (top < cnt) stk[++top] = x;
        else return "No";
    } else cnt++;
}
// 输出 stk 数组和剩余 cnt - top 的填充值
```

#### 3. wdgm4 的题解（⭐⭐⭐⭐）
**关键亮点**:
- 明确使用 `num` 记录剩余 0 配额，`k` 记录已使用的 0。
- 处理剩余 0 时统一填充 1，代码易读。

**核心代码**:
```cpp
int num = 0, k = 0, b[1005], a[1005] = {0};
for (遍历每个元素) {
    if (x == 0) num++;
    else if (x < 0) {
        if (a[-x]) a[-x]--;
        else if (num > 0) num--, b[++k] = -x;
        else return "No";
    } else a[x]++;
}
// 输出 b 数组和剩余 num 的填充值
```

---

### 关键思路总结
1. **贪心延迟处理**：0 的配额留到无法用现有物品时再使用。
2. **桶计数优化效率**：直接通过数组索引维护物品数量，O(1) 时间查询/更新。
3. **输出顺序一致性**：按补救顺序记录 0 的使用，剩余 0 可任意填充。

---

### 拓展与相似题目
- **同类题目套路**：资源分配问题中优先使用实时资源，不足时动用备用资源（如 P5019 铺设道路）。
- **推荐题目**:
  1. [P1086 花生采摘](https://www.luogu.com.cn/problem/P1086)（贪心选择最优路径）
  2. [P5019 铺设道路](https://www.luogu.com.cn/problem/P5019)（贪心模拟）
  3. [P1607 [NOI2016] 区间](https://www.luogu.com.cn/problem/P1607)（贪心+排序）

---
处理用时：63.02秒