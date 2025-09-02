# 题目信息

# Addition on Segments

## 题目描述

Grisha come to a contest and faced the following problem.

You are given an array of size $ n $ , initially consisting of zeros. The elements of the array are enumerated from $ 1 $ to $ n $ . You perform $ q $ operations on the array. The $ i $ -th operation is described with three integers $ l_i $ , $ r_i $ and $ x_i $ ( $ 1 \leq l_i \leq r_i \leq n $ , $ 1 \leq x_i \leq n $ ) and means that you should add $ x_i $ to each of the elements with indices $ l_i, l_i + 1, \ldots, r_i $ . After all operations you should find the maximum in the array.

Grisha is clever, so he solved the problem quickly.

However something went wrong inside his head and now he thinks of the following question: "consider we applied some subset of the operations to the array. What are the possible values of the maximum in the array?"

Help Grisha, find all integers $ y $ between $ 1 $ and $ n $ such that if you apply some subset (possibly empty) of the operations, then the maximum in the array becomes equal to $ y $ .

## 说明/提示

Consider the first example. If you consider the subset only of the first query, the maximum is equal to $ 1 $ . If you take only the second query, the maximum equals to $ 2 $ . If you take the first two queries, the maximum becomes $ 3 $ . If you take only the fourth query, the maximum becomes $ 4 $ . If you take the fourth query and something more, the maximum becomes greater that $ n $ , so you shouldn't print it.

In the second example you can take the first query to obtain $ 1 $ . You can take only the second query to obtain $ 2 $ . You can take all queries to obtain $ 3 $ .

In the third example you can obtain the following maximums:

- You can achieve the maximim of $ 2 $ by using queries: $ (1) $ .
- You can achieve the maximim of $ 3 $ by using queries: $ (2) $ .
- You can achieve the maximim of $ 5 $ by using queries: $ (1, 2) $ .
- You can achieve the maximim of $ 6 $ by using queries: $ (3) $ .
- You can achieve the maximim of $ 8 $ by using queries: $ (1, 3) $ .
- You can achieve the maximim of $ 9 $ by using queries: $ (2, 3) $ .

## 样例 #1

### 输入

```
4 3
1 3 1
2 4 2
3 4 4
```

### 输出

```
4
1 2 3 4 
```

## 样例 #2

### 输入

```
7 2
1 5 1
3 7 2
```

### 输出

```
3
1 2 3 
```

## 样例 #3

### 输入

```
10 3
1 1 2
1 1 3
1 1 6
```

### 输出

```
6
2 3 5 6 8 9 
```

# AI分析结果



**唯一算法分类**：动态规划（DP）与线段树分治结合位运算（Bitset）

---

### **综合分析与结论**

**题目核心**：确定所有可能的数组最大值y∈[1,n]，通过选择某些区间加法操作，使得最大值为y。

**核心难点**：
1. **区间覆盖影响**：每个操作影响连续区间，需高效处理区间重叠对最大值的影响。
2. **组合爆炸**：直接枚举所有操作子集不可行，需优化状态表示。

**解决方案对比**：
1. **动态规划（DP）**（如zhaoyp、_edge_的题解）：
   - **状态设计**：`f[j]`表示最大值j的最小左端点。
   - **转移逻辑**：按区间右端点排序，从后向前处理，若当前区间覆盖`f[j-x]`，则更新`f[j]`。
   - **时间复杂度**：O(n²)，适用于n=1e4。

2. **线段树分治+bitset**（如一扶苏一、万弘的题解）：
   - **操作分解**：用线段树将区间操作分布到节点。
   - **bitset加速**：每个节点维护可能的和，通过位运算快速合并。
   - **时间复杂度**：O(q log n + n²/w)，w为bitset位数，效率更高。

**可视化设计**：
- **DP状态转移**：动态展示`f[j]`的更新过程，高亮当前处理的区间和影响的j值。
- **线段树操作分布**：动画演示线段树节点如何收集操作，合并bitset。
- **复古像素风格**：用8位色块表示数组状态变化，音效提示关键步骤（如区间合并、状态更新）。

---

### **题解清单（≥4星）**

1. **zhaoyp（★★★★☆）**：
   - **亮点**：DP状态设计巧妙，代码简洁高效。
   - **关键代码**：
     ```cpp
     for (int i = m; i; i--)
         for (int j = n; j >= a[i].x; j--)
             if (f[j - a[i].x] <= a[i].r)
                 f[j] = min(f[j], max(f[j - a[i].x], a[i].l));
     ```

2. **一扶苏一（★★★★★）**：
   - **亮点**：线段树分治+bitset优化，时间复杂度优异。
   - **关键代码**：
     ```cpp
     void calc(int o) {
         auto u = tree + o;
         for (auto p : u->opid) bt[o] |= bt[o] << op[p].x;
         if (u->ld) {
             bt[u->ld] = bt[u->rd] = bt[o];
             calc(u->ld); calc(u->rd);
         } else ans |= bt[o];
     }
     ```

3. **万弘（★★★★☆）**：
   - **亮点**：线段树分治实现清晰，易于理解。
   - **关键代码**：
     ```cpp
     void modify(int ql, int qr, int k) {
         if (ql <= l && r <= qr) { rt.push_back(k); return; }
         if (ql <= mid) modify(ql, qr, k, l, mid, num<<1);
         if (qr > mid) modify(ql, qr, k, mid+1, r, num<<1|1);
     }
     ```

---

### **最优思路提炼**

1. **DP状态压缩**：
   - **核心**：`f[j]`记录最大值j的最小左端点，通过区间排序和逆向转移确保正确性。
   - **优化**：滚动数组节省空间，按右端点排序简化覆盖判断。

2. **线段树分治**：
   - **分解操作**：将区间操作分布到线段树节点，避免重复处理。
   - **bitset加速**：利用位运算并行计算所有可能和，复杂度降为O(n²/w)。

---

### **相似题目推荐**

1. **P5020 货币系统**（背包问题+贪心）
2. **P4095 [HEOI2013]Eden的背包问题**（多重背包+bitset优化）
3. **P3224 [HNOI2012]永无乡**（线段树合并）

---

### **个人心得摘录**

- **踩坑**：sanaka87的退背包方法在撤销操作时易出错，需谨慎处理。
- **顿悟**：线段树分治将区间影响分解为独立路径，极大简化问题。

---

### **可视化与算法演示**

**动态规划动画方案**：
- **网格视图**：行表示处理的操作，列表示可能的j值。
- **颜色标记**：当前处理的区间（红色），更新的j值（绿色）。
- **步进控制**：单步执行观察`f[j]`的更新过程。

**像素风格设计**：
- **8位色板**：用不同颜色表示数组状态（如蓝色为0，黄色为当前最大值）。
- **音效**：操作应用时播放“哔”声，找到可行y时播放胜利音效。

**AI自动演示**：
- **逻辑**：按排序后的区间顺序自动处理，高亮转移路径。
- **交互**：可暂停查看当前状态，调节动画速度。

```javascript
// 示例：bitset更新可视化（伪代码）
function updateBitset(node, x) {
    node.bitset = node.bitset.or(node.bitset.leftShift(x));
    drawCanvas(node.bitset); // 在Canvas上绘制当前bitset状态
    playSound('bit-update');
}
```

---

**结论**：DP方法适合快速实现，线段树分治+bitset在大数据下更优。实际选择需根据问题规模及实现复杂度权衡。

---
处理用时：74.63秒