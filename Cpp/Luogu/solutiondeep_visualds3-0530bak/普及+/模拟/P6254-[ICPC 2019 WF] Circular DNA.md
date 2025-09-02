# 题目信息

# [ICPC 2019 WF] Circular DNA

## 题目描述

You have an internship with a bioinformatics research group studying DNA. A single strand of DNA consists of many genes, which fall into different categories called gene types. Gene types are delimited by specific nucleotide sequences known as gene markers. Each gene type i has a unique start marker $\texttt s_i$ and a unique end marker $\texttt e_i$ . After many dirty jobs (growing bacteria, cell extraction, protein engineering,and so on), your research group can convert DNA into a form consisting of only the gene markers, removing all the genetic material lying between the markers.

Your research group came up with the interesting hypothesis that gene interpretation depends on whether the markers of some gene types form properly nested structures. To decide whether markers of gene type $i$ form a proper nesting in a given sequence of markers $w$, one needs to consider the subsequence of $w$ containing only the markers of gene type $i$ ($\texttt s_i$ and $\texttt e_i$), leaving none of them out. The following (and only the following) are considered to be properly nested structures:

- $\texttt s_i \texttt e_i$
- $\texttt s_i N \texttt e_i$, where $N$ is a properly nested structure
- $AB$, where $A$ and $B$ are properly nested structures

Given your computing background, you were assigned to investigate this property, but there is one further complication. Your group is studying a specific type of DNA called circular DNA, which is DNA that forms a closed loop. To study nesting in circular DNA, it is necessary to cut the loop at some location, which results in a unique sequence of markers (the direction of reading is fixed by molecular properties). Whether a gene type $i$ forms a proper nesting now also depends on where the circular DNA is cut. Your task is to find the cutting location that maximizes the number of gene types that form a properly nested structure. Figure D.1 shows an example corresponding to Sample Input 1. The indicated cut results in the markers for gene type 1 being properly nested.

![](https://cdn.luogu.com.cn/upload/image_hosting/l856fbko.png)

## 说明/提示

Source: ICPC 2019 World Finals.

## 样例 #1

### 输入

```
9
e1 e1 s1 e2 s1 s2 e42 e1 s1```

### 输出

```
3 1```

## 样例 #2

### 输入

```
8
s1 s1 e3 e1 s3 e1 e3 s3```

### 输出

```
8 2```

# AI分析结果



## **算法分类**
括号匹配、前缀和与线性扫描

---

## **综合分析与结论**

### **题目核心思路**
将每个基因类型的括号序列独立处理，计算其前缀和及最小值。初始时统计所有可能合法的基因类型数。移动切割点时，仅调整被移动的基因类型的前缀和最小值，快速更新合法数目。

### **解决难点**
1. **环形结构处理**：通过将环拆为链，递推每个切割点的合法数目。
2. **高效更新合法数目**：每次移动切割点时，只需处理被移动的基因类型，时间复杂度为 *O(1)*。
3. **前缀和与最小值维护**：通过记录每个基因类型的总和和最小前缀和，快速判断合法性。

### **核心算法流程**
1. **预处理**：计算每个基因类型的前缀和总和 `Sum[x]` 和最小前缀和 `Low[x]`。
2. **初始统计**：遍历所有基因类型，若 `Sum[x] = 0` 且 `Low[x] = 0`，则合法。
3. **移动切割点**：
   - 若左端是 `s`，前缀和最小值减 1，若原最小值为 0，合法数目减 1。
   - 若左端是 `e`，前缀和最小值加 1，若新最小值为 0，合法数目加 1。
4. **维护最大值**：每次移动后更新最优切割点。

### **可视化设计**
- **动画效果**：展示切割点移动时，当前基因类型的前缀和最小值变化（如红色高亮）。
- **状态面板**：显示当前切割点、合法数目、每个基因类型的 `Sum` 和 `Low`。
- **复古像素风**：用 8-bit 像素块表示基因类型，移动切割点时播放音效。

---

## **题解清单（≥4星）**

### **1. 比利♂海灵顿（★★★★★）**
- **关键亮点**：线性时间复杂度，利用递推更新合法数目，代码简洁高效。
- **代码片段**：
  ```cpp
  for (int i = 1; i < n; ++i) {
    if (Sum[a[i].Number] == 0) {
      if (a[i].SE == 1) {
        if (Low[a[i].Number] == 0) --Tmp;
        --Low[a[i].Number];
      } else {
        ++Low[a[i].Number];
        if (Low[a[i].Number] == 0) ++Tmp;
      }
    }
    if (Tmp > Ans) Ans = Tmp, Pos = i + 1;
  }
  ```

### **2. 内拉组里（★★★★☆）**
- **关键亮点**：详细分析移动切割点时对前缀和的影响，代码逻辑清晰。
- **代码片段**：
  ```cpp
  if (a[i].first == 1) {
    if (!mn[a[i].second]--) cnt--;
  } else {
    if (!++mn[a[i].second]) cnt++;
  }
  ```

### **3. YingLi（★★★★☆）**
- **关键亮点**：使用单调队列维护滑动窗口最小值，树状数组统计合法区间。
- **代码片段**：
  ```cpp
  while (!q.empty() && pre[q.back()] >= pre[r]) q.pop_back();
  q.push_back(r);
  if (pre[q.front()] >= pre[r - m]) update_diff();
  ```

---

## **最优思路提炼**
1. **独立处理基因类型**：每个基因类型的合法性独立判断。
2. **前缀和与最小值**：通过 `Sum[x]` 和 `Low[x]` 快速判断合法性。
3. **递推更新**：移动切割点时仅调整被移动基因类型的最小值，避免重复计算。

---

## **同类型题与算法套路**
- **括号匹配**：如 [LeetCode 32. 最长有效括号](https://leetcode.com/problems/longest-valid-parentheses/)。
- **环形数组处理**：如 [LeetCode 503. 下一个更大元素 II](https://leetcode.com/problems/next-greater-element-ii/)。

---

## **推荐题目**
1. **洛谷 P1944**（最长括号匹配）
2. **洛谷 P1886**（滑动窗口 / 单调队列）
3. **洛谷 P3406**（环形结构处理）

---

## **个人心得摘录**
> "算法竞赛中追求完美精神让我受益，即使最优解无关排名，也要追求高效和简洁。" —— 比利♂海灵顿

---

## **可视化与算法演示**
### **动画方案**
1. **初始状态**：环形 DNA 序列显示为像素块，切割点用光标标记。
2. **切割点移动**：左端基因移动到右端，播放“切割音效”。
3. **前缀和变化**：当前基因类型的前缀和曲线动态更新，最小值区域红色闪烁。
4. **合法数目更新**：计数器实时变化，达到新高时触发“胜利音效”。

### **复古风格实现**
```javascript
// 伪代码：Canvas 绘制 DNA 环
function drawDNA() {
  ctx.fillStyle = '#8B00FF'; // 紫色像素块
  for (let i = 0; i < n; i++) {
    ctx.fillRect(i * 10 % 300, Math.floor(i * 10 / 300) * 10, 8, 8);
  }
  // 播放音效
  if (newRecord) playSound('win.wav');
}
```

---

**答案总结**：最优解法通过前缀和与线性递推，时间复杂度 *O(n)*，核心代码简洁高效，可视化可结合复古像素风格与实时状态更新。

---
处理用时：81.96秒