# 题目信息

# Color Stripe

## 题目描述

A colored stripe is represented by a horizontal row of $ n $ square cells, each cell is pained one of $ k $ colors. Your task is to repaint the minimum number of cells so that no two neighbouring cells are of the same color. You can use any color from 1 to $ k $ to repaint the cells.

## 样例 #1

### 输入

```
6 3
ABBACC
```

### 输出

```
2
ABCACA
```

## 样例 #2

### 输入

```
3 2
BBB
```

### 输出

```
1
BAB
```

# AI分析结果



# 颜色条纹

## 题目描述  
将水平排列的n个颜色单元格重新染色，使得相邻单元格颜色不同。每个单元格可染成1到k种颜色中的任意一种。要求找出需要重新染色的最小单元格数，并输出任意一种可行方案。

## 输入格式  
第一行两个整数n和k（1 ≤ n ≤ 5×10⁵，2 ≤ k ≤ 26）  
第二行包含长度为n的字符串，表示初始颜色条纹  

## 输出格式  
第一行输出最小修改次数  
第二行输出修改后的字符串  

## 样例  
### 样例输入1  
6 3  
ABBACC  
### 样例输出1  
2  
ABCACA  

### 样例输入2  
3 2  
BBB  
### 样例输出2  
1  
BAB  

---

**算法分类**: 贪心

---

## 题解综合分析

### 核心思路对比
各题解普遍采用贪心策略，核心差异在于：
1. **常规处理**：k≥3时从左到右遍历，遇到相同字符时选择与前一个和后一个都不同的最小字符
2. **特判处理**：k=2时只能形成ABAB/BABA两种交替模式，需比较两种模式的修改代价
3. **实现差异**：字符选择方式分为顺序枚举与直接构造两种模式

### 优化要点
1. **k=2特判**：通过预构造两种交替序列快速计算最小修改次数
2. **贪心顺序**：优先选择字典序小的字符（如选A而非C），不影响最优性但简化实现
3. **原地修改**：直接在原字符串上操作节省空间

---

## 精选题解

### 1. codeLJH114514（⭐⭐⭐⭐⭐）
**核心亮点**：  
- 模块化设计Min函数处理常规情况
- 优雅的k=2特判实现
- 完整处理字符串边界问题

**关键代码**：
```cpp
if (k == 2) {
    // 构造ABAB和BABA两种模式
    string a, b;
    for (int i = 1; i <= n; i++) a += char('A' + (i % 2));
    for (int i = 1; i <= n; i++) b += char('A' + not (i % 2));
    
    // 计算两种模式的修改代价
    int ca = count_diff(a), cb = count_diff(b);
    cout << min(ca, cb) << "\n" << (ca < cb ? a : b);
    return;
}

char Min(int pos) {
    for (char c = 'A'; c < 'A'+k; c++) 
        if(c != s[pos-1] && (pos==n || c!=s[pos+1]))
            return c;
}
```

### 2. 流绪（⭐⭐⭐⭐）
**亮点**：  
- 简洁的k=2处理逻辑
- 边界条件合并处理

**关键实现**：
```cpp
int find_replace(char prev, char next) {
    for(char c='A'; c<'A'+k; c++)
        if(c != prev && c != next) 
            return c;
}

void process() {
    for(int i=1; i<n; i++) {
        if(s[i] == s[i-1]) {
            s[i] = (i == n-1) ? find_replace(s[i-1], 0) 
                             : find_replace(s[i-1], s[i+1]);
            cnt++;
        }
    }
}
```

### 3. 王熙文（⭐⭐⭐）
**独特思路**：  
- 尝试动态规划解法
- 记录转移路径重构答案

**复杂度问题**：  
虽然DP思路正确，但O(nk²)复杂度在n=5e5时不可行，仅作为思路扩展参考

---

## 关键技巧总结
1. **贪心选择策略**：修改时确保与前后字符不同，且优先选择可用字符中的最小字符
2. **k=2特判**：预生成两种交替模式并取最优解
3. **原地修改优化**：直接在原字符串数组操作避免额外空间消耗
4. **边界处理**：字符串末尾字符只需保证与前一个不同

---

## 拓展训练
1. [P1328 生活大爆炸版石头剪刀布] - 交替模式计数
2. [P2587 红黑树] - 相邻节点约束问题 
3. [CF1215B 黑白棋] - 交替序列构造

---

## 调试心得摘录
1. **codeLJH114514**：  
_"提交时WA on test 11，发现k=2时存在死循环，通过构造两种交替模式解决"_

2. **alan1118**：  
_"原以为简单贪心就能解决，直到遇到k=2的特殊情况，意识到必须完全不同的处理方式"_

---
处理用时：64.34秒