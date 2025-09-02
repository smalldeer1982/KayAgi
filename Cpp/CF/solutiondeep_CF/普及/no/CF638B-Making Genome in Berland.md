# 题目信息

# Making Genome in Berland

## 题目描述

Berland scientists face a very important task - given the parts of short DNA fragments, restore the dinosaur DNA! The genome of a berland dinosaur has noting in common with the genome that we've used to: it can have $ 26 $ distinct nucleotide types, a nucleotide of each type can occur at most once. If we assign distinct English letters to all nucleotides, then the genome of a Berland dinosaur will represent a non-empty string consisting of small English letters, such that each letter occurs in it at most once.

Scientists have $ n $ genome fragments that are represented as substrings (non-empty sequences of consecutive nucleotides) of the sought genome.

You face the following problem: help scientists restore the dinosaur genome. It is guaranteed that the input is not contradictory and at least one suitable line always exists. When the scientists found out that you are a strong programmer, they asked you in addition to choose the one with the minimum length. If there are multiple such strings, choose any string.

## 样例 #1

### 输入

```
3
bcd
ab
cdef
```

### 输出

```
abcdef
```

## 样例 #2

### 输入

```
4
x
y
z
w
```

### 输出

```
xyzw
```

# AI分析结果



【中文重写题目】
# 重构Berland的基因组

## 题目描述

Berland的科学家面临一项重要任务——根据短DNA片段的部分信息，重构恐龙DNA！Berland恐龙的基因组与我们所知的不同：它包含26种不同的核苷酸类型，每种类型最多出现一次。若用不同英文字母表示核苷酸，则其基因组为非空小写字母字符串，且每个字母最多出现一次。

科学家提供了n个基因组片段，这些片段均为目标基因组的连续子串。请帮助科学家重构符合条件的恐龙基因组，并要求结果字符串长度尽可能短。若有多个解，输出任意一个。题目保证输入合法且有解。

## 样例 #1

### 输入
```
3
bcd
ab
cdef
```

### 输出
```
abcdef
```

## 样例 #2

### 输入
```
4
x
y
z
w
```

### 输出
```
xyzw
```

【算法分类】
图论（拓扑排序）

【题解对比分析】
1. **共同点**：两解法均通过构建字符间依赖关系，进行拓扑排序。
2. **差异点**：
   - jch123使用DFS遍历后继列表，适用于更一般的拓扑排序场景。
   - yangzd通过维护前驱/后继链式结构，直接遍历字符链，更简洁高效。
3. **难点处理**：
   - 确保字符顺序满足所有子串约束。
   - 处理多个无前驱字符时的顺序选择。

【高星题解推荐】
1. **jch123的题解（4星）**
   - 亮点：通用DFS拓扑排序思路，动态维护后继关系。
   - 代码片段：
     ```cpp
     void dfs(int x) {
         book[x] = 1;
         ans[++len] = char('a'+x);
         for(int i=0; i<A[x].size(); i++) {
             if(book[A[x][i]] == 0)
                 dfs(A[x][i]);
         }
     }
     ```
2. **yangzd的题解（4星）**
   - 亮点：链式结构直接遍历，时间复杂度O(n)。
   - 代码片段：
     ```cpp
     for(long long i=0; i<26; i++)
         if(pre[i]==-1 && flag[i]) {
             long long j=i;
             while(j != -1) {
                 flag[j] = 0;
                 cout << char(j+'a');
                 j = nex[j];
             }
         }
     ```

【关键思路总结】
1. **依赖关系建模**：将每个字符的后继视为有向边，形成DAG。
2. **拓扑起点选择**：从无前驱的字符出发，确保所有约束被满足。
3. **链式合并优化**：通过维护pre/nex数组直接输出路径，无需复杂遍历。

【拓展思考】
类似拓扑排序问题可考虑：
- 课程安排（LeetCode 207）
- 任务调度（存在依赖关系的任务序列）
- 字符串重组（要求满足多个子序列约束）

【推荐练习题】
1. P1137 旅行计划（拓扑排序基础）
2. P2712 食物链（拓扑判环应用）
3. P1347 排序（拓扑排序动态判断）

---
处理用时：255.10秒