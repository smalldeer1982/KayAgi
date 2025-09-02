# 题目信息

# Making a String

## 题目描述

You are given an alphabet consisting of $ n $ letters, your task is to make a string of the maximum possible length so that the following conditions are satisfied:

- the $ i $ -th letter occurs in the string no more than $ a_{i} $ times;
- the number of occurrences of each letter in the string must be distinct for all the letters that occurred in the string at least once.

## 说明/提示

For convenience let's consider an alphabet consisting of three letters: "a", "b", "c". In the first sample, some of the optimal strings are: "cccaabbccbb", "aabcbcbcbcb". In the second sample some of the optimal strings are: "acc", "cbc".

## 样例 #1

### 输入

```
3
2 5 5
```

### 输出

```
11
```

## 样例 #2

### 输入

```
3
1 1 2
```

### 输出

```
3
```

# AI分析结果



# 题目重写

## 题目描述

给定包含 $n$ 个字母的字母表，要求构造一个尽可能长的字符串，满足以下条件：

- 第 $i$ 个字母在字符串中的出现次数不超过 $a_i$ 次；
- 每个字母的出现次数（至少出现一次的字母）必须互不相同。

## 输入格式

输入第一行为整数 $n$，第二行包含 $n$ 个整数 $a_1, a_2, \dots, a_n$。

## 输出格式

输出字符串的最大可能长度。

## 样例 #1

### 输入
```
3
2 5 5
```

### 输出
```
11
```

## 样例 #2

### 输入
```
3
1 1 2
```

### 输出
```
3
```

---

# 算法分类
**贪心**

---

# 题解分析与结论

## 核心思路
1. **贪心策略**：每个字母尽可能取最大可用次数，若冲突则逐步递减直至找到可用次数。
2. **去重方法**：使用排序后倒序处理或哈希表记录已用次数。
3. **优化关键**：通过排序避免重复检查，或利用哈希表快速查找冲突。

---

# 高分题解精选

## 题解1：那一条变阻器（4星）
**亮点**：直观的贪心实现 + 哈希表去重  
**核心代码**：
```cpp
map<long long, int> a; // 记录已用次数
long long n, ans = 0, p;
int main() {
    cin >> n;
    while(n--) {
        a[0] = 0; // 特殊处理0
        cin >> p;
        while(a[p]) p--; // 递减至可用次数
        a[p] = 1;        // 标记已用
        ans += p;
    }
    cout << ans;
}
```
**思路**：逐个处理字母，用 `map` 记录已使用的次数。若当前次数已被占用，则递减直至找到未使用的次数。

---

## 题解2：wmrqwq（4星）
**亮点**：排序预处理 + 线性贪心  
**核心代码**：
```cpp
sort(a, a+n); // 从小到大排序
long long sum = a[n-1] + 1, ans = 0;
for(int i = n-1; i >= 0; --i) {
    if(sum > a[i]) sum = a[i];
    else if(sum > 0) sum--;
    ans += sum;
}
```
**思路**：先排序，从最大的次数开始处理。维护一个递减计数器 `sum`，确保每次选择的次数严格小于前一个字母的次数。

---

# 最优思路总结
1. **贪心选择**：优先取最大可用次数，确保总和最大化。
2. **冲突解决**：通过递减或排序处理重复次数。
3. **数据结构**：哈希表快速查重或排序后线性处理提升效率。

**关键技巧**：  
- 使用 `map` 快速检测重复次数，时间复杂度 $O(n \log n)$  
- 排序后倒序处理可将复杂度优化至 $O(n \log n)$（排序）+ $O(n)$（处理）

---

# 拓展与心得
**个人心得**：  
1. 当处理次数范围较大时（如 $a_i \leq 10^9$），直接使用数组不可行，需用哈希表。
2. 注意处理边界条件（如次数减至0时停止）。

**类似题目推荐**：  
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)（贪心+优先队列）
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)（排序贪心）
3. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)（贪心选择最优删除策略）

---
处理用时：53.58秒