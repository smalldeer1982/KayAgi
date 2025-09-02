# 题目信息

# Anonymity Is Important

## 题目描述

In the work of a doctor, it is important to maintain the anonymity of clients and the results of tests. The test results are sent to everyone personally by email, but people are very impatient and they want to know the results right away.

That's why in the testing lab "De-vitro" doctors came up with an experimental way to report the results. Let's assume that $ n $ people took the tests in the order of the queue. Then the chief doctor Sam can make several statements, in each telling if there is a sick person among the people in the queue from $ l $ -th to $ r $ -th (inclusive), for some values $ l $ and $ r $ .

During the process, Sam will check how well this scheme works and will be interested in whether it is possible to find out the test result of $ i $ -th person from the information he announced. And if it can be done, then is that patient sick or not.

Help Sam to test his scheme.

## 说明/提示

In the first test for the five first queries:

1. Initially Sam tells that people $ 4 $ , $ 5 $ are not sick.
2. In the next query Sam asks the status of the patient $ 5 $ . From the previous query, we know that the patient is definitely not sick.
3. In the next query Sam asks the status of the patient $ 6 $ . We don't know any information about that patient now.
4. After that Sam tells that there exists a sick patient among $ 4 $ , $ 5 $ , $ 6 $ .
5. In the next query Sam asks the status of the patient $ 6 $ . Now we can tell that this patient is definitely sick.

## 样例 #1

### 输入

```
6 9
0 4 5 0
1 5
1 6
0 4 6 1
1 6
0 2 5 1
0 2 2 0
1 3
1 2```

### 输出

```
NO
N/A
YES
YES
NO```

# AI分析结果



**唯一算法分类**: 无算法分类

---

### **题解思路、算法要点与解决难点**

#### **核心思路**
题目需要动态维护区间信息，快速判断某点是否为病人。核心在于：
- **0操作（区间无病人）**：合并区间，标记所有点为非病人。
- **1操作（区间有病人）**：记录可能的区间，后续通过其他0操作缩小可能范围。
- **查询操作**：判断点是否被0操作覆盖（NO），或存在唯一1区间覆盖且其他点被排除（YES），否则N/A。

#### **关键数据结构**
1. **并查集**：高效合并连续的0区间，快速判断某点是否被标记为非病人。
2. **线段树/Set**：维护1操作的区间信息，快速查询是否存在包含当前点的有效区间。

#### **解决难点**
- **高效合并区间**：并查集在O(α(n))时间内合并连续区间。
- **判断唯一性**：通过维护每个左端点的最小右端点，结合左右边界判断是否存在唯一覆盖。

---

### **题解评分 (≥4星)**

1. **Francais_Drake的题解 (5星)**
   - **亮点**：并查集合并0区间，线段树维护1区间，代码简洁高效。
   - **核心代码**：
     ```cpp
     // 合并0区间
     while(l<=r){
         a=Find(l);b=Find(l+1);rt[a]=b;
         lt[b]=min(lt[a],lt[b]);l=b;
     }
     // 查询是否为YES
     if(lt[l]<Find(l+1)) printf("YES\n");
     ```

2. **CGDGAD的题解 (4星)**
   - **亮点**：Set维护未覆盖点，线段树快速查询区间。
   - **核心代码**：
     ```cpp
     // Set删除0区间
     while (!s.empty()) {
         int pos = *s.lower_bound(l);
         if (pos <= r) s.erase(pos);
     }
     // 查询区间最小值
     if (SegTree::query(l+1, x) < r) YES;
     ```

3. **Nightingale_OI的题解 (4星)**
   - **亮点**：并查集维护左右边界，线段树记录最小右端点。
   - **核心代码**：
     ```cpp
     // 合并区间并更新线段树
     le[s] = s-1; ri[s] = s+1;
     if (ask(1, s, q) <= ri_x) YES;
     ```

---

### **最优思路或技巧提炼**
1. **并查集合并0区间**：将连续的0区间合并为块，查询时直接判断是否在块内。
2. **线段树维护1区间**：记录每个左端点对应的最小右端点，快速判断是否存在有效区间。
3. **左右边界查询**：通过Set或并查集找到当前点的左右最近非0区间，缩小检查范围。

---

### **同类型题或类似算法套路**
- **区间合并+查询**：常见于动态维护区间覆盖问题。
- **并查集优化**：用于高效合并相邻区间，如「朋友圈合并」问题。
- **线段树/Set维护最值**：用于快速查询区间极值或存在性。

---

### **推荐相似题目**
1. **P1972 [SDOI2009]HH的项链**（区间查询不同元素数量）
2. **P5490 【模板】扫描线**（区间覆盖与面积计算）
3. **P2894 [USACO08FEB]Hotel G**（区间合并与查询）

---

### **可视化与算法演示**

#### **可视化设计**
1. **动画方案**：
   - **区间合并**：用颜色块表示合并后的0区间，动态展示并查集合并过程。
   - **线段树查询**：高亮当前查询的左端点，显示最小右端点。
   - **边界收缩**：用箭头标记当前点的左右边界，逐步缩小范围。

2. **复古像素风格**：
   - **8位网格**：用像素方块表示区间，合并时方块颜色变化。
   - **音效提示**：合并成功时播放“滴”声，查询时不同结果触发不同音效。

3. **交互功能**：
   - **步进控制**：允许单步执行合并或查询，观察数据结构变化。
   - **自动演示**：AI自动生成操作序列，展示典型用例的解决过程。

---

### **代码实现（Francais_Drake核心片段）**
```cpp
// 并查集合并0区间
void merge(int l, int r) {
    while (l <= r) {
        int a = Find(l), b = Find(l + 1);
        rt[a] = b;
        lt[b] = min(lt[a], lt[b]);
        l = b;
    }
}

// 查询处理
if (Find(i) != i) cout << "NO\n"; // 被0区间覆盖
else if (lt[i] < Find(i + 1)) cout << "YES\n"; // 存在有效1区间
else cout << "N/A\n";
```

---

### **总结**
本题通过结合并查集和线段树，高效处理区间合并与查询。核心在于动态维护非病人区间，并快速判断是否存在唯一病人。可视化设计可帮助理解区间合并与查询的交互过程，适合通过动态演示加深理解。

---
处理用时：73.96秒