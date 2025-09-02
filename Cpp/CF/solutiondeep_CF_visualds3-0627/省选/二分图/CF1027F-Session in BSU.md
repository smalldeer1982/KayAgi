# 题目信息

# Session in BSU

## 题目描述

Polycarp studies in Berland State University. Soon he will have to take his exam. He has to pass exactly $ n $ exams.

For the each exam $ i $ there are known two days: $ a_i $ — day of the first opportunity to pass the exam, $ b_i $ — day of the second opportunity to pass the exam ( $ a_i < b_i $ ). Polycarp can pass at most one exam during each day. For each exam Polycarp chooses by himself which day he will pass this exam. He has to pass all the $ n $ exams.

Polycarp wants to pass all the exams as soon as possible. Print the minimum index of day by which Polycarp can pass all the $ n $ exams, or print -1 if he cannot pass all the exams at all.

## 样例 #1

### 输入

```
2
1 5
1 7
```

### 输出

```
5
```

## 样例 #2

### 输入

```
3
5 13
1 5
1 7
```

### 输出

```
7
```

## 样例 #3

### 输入

```
3
10 40
40 80
10 80
```

### 输出

```
80
```

## 样例 #4

### 输入

```
3
99 100
99 100
99 100
```

### 输出

```
-1
```

# AI分析结果



**算法分类**：图论（基环树、并查集）

---

### **题解思路与算法要点**
#### **核心思路**
将每个考试的两个时间点视为图中的一条边，问题转化为图的结构分析。对每个连通块：
1. **边数 > 点数** → 无解（输出 `-1`）
2. **边数 = 点数** → 基环树，取该连通块的最大时间点
3. **边数 = 点数-1** → 树结构，取次大时间点

最终答案为所有连通块结果的最大值。关键难点在于正确建模图结构并分类处理连通块。

#### **关键步骤**
1. **离散化**：将时间点压缩至连续索引。
2. **建图**：每个考试作为边连接两个离散化后的时间点。
3. **DFS遍历**：统计每个连通块的边数、点数、最大值和次大值。
4. **分类决策**：根据边数与点数关系计算各连通块贡献的最大时间。

---

### **题解评分**
1. **大菜鸡fks（5星）**  
   - 思路清晰，通过基环树结构分类讨论。  
   - 代码完整，离散化与DFS实现明确。  
2. **ModestCoder_（5星）**  
   - 并查集实现简洁高效，离散化处理巧妙。  
   - 动态维护时间点选择，逻辑直观。  
3. **hsfzLZH1（4星）**  
   - 详细分类讨论，代码注释清晰。  
   - 图遍历与数据结构结合紧密。

---

### **最优思路代码**
**并查集解法核心代码**（作者：ModestCoder_）：
```cpp
int main() {
    n = read();
    // 离散化处理
    for (int i = 1; i <= n; ++i) 
        a[i] = lower_bound(...), b[i] = lower_bound(...);
    // 并查集初始化
    for (int i = 1; i <= p; ++i) f[i] = i;
    for (int i = 1; i <= n; ++i) {
        int s1 = get(a[i]), s2 = get(b[i]);
        if (!s1 && !s2) { puts("-1"); return 0; }
        if (s1 == s2 || !s1 || !s2) { 
            ans = max(ans, max(num[s1], num[s2])); 
            f[s1] = f[s2] = 0; 
        } else {
            if (s1 > s2) swap(s1, s2);
            ans = max(ans, num[s1]); 
            f[s1] = s2; 
        }
    }
    printf("%d\n", ans);
}
```
**核心思想**：动态合并时间点，优先选择较小时间点，保留较大时间点作为候选，确保最终答案最优。

---

### **同类型题与算法套路**
- **通用解法**：将时间点建模为节点，考试为边，通过图结构（基环树/树）或并查集动态处理冲突。
- **类似题目**：  
  1. [P1330 封锁阳光大学](https://www.luogu.com.cn/problem/P1330)（图结构分析）  
  2. [P1892 团伙](https://www.luogu.com.cn/problem/P1892)（并查集维护关系）  
  3. [CF1151F Sonya and Informatics](https://www.luogu.com.cn/problem/CF1151F)（离散化与动态规划）

---

### **可视化与算法演示**
**动画设计**：
1. **节点与边绘制**：离散化后的时间点显示为网格节点，考试作为边连接两点。
2. **颜色标记**：  
   - 红色：当前处理的时间点对。  
   - 绿色：已合并的连通块。  
   - 灰色：不可用节点。  
3. **步进逻辑**：  
   - 显示并查集合并过程，动态更新最大时间点。  
   - 基环树解法中高亮DFS路径，统计边数与点数。

**复古像素风格**：
- **8位调色板**：节点用蓝/绿/红色块，边用黄色线条。
- **音效触发**：  
  - 合并成功：短促“滴”声。  
  - 无解：低沉“错误”音效。  
  - 选择时间点：清脆音效。
- **Canvas动画**：网格布局，每次操作后更新节点状态与连通块颜色。

---

### **结论**
通过图论建模或并查集动态处理，离散化时间点是关键步骤。基环树解法侧重结构分析，并查集解法高效简洁。两种方法均需确保每个连通块的决策不冲突，最终取最大值作为答案。

---
处理用时：101.67秒