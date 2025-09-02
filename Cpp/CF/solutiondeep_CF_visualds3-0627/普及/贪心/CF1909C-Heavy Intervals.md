# 题目信息

# Heavy Intervals

## 题目描述

[Shiki - Pure Ruby](https://soundcloud.com/shiki-8/pure-rubyversoundcloud)

⠀



You have $ n $ intervals $ [l_1, r_1], [l_2, r_2], \dots, [l_n, r_n] $ , such that $ l_i < r_i $ for each $ i $ , and all the endpoints of the intervals are distinct.

The $ i $ -th interval has weight $ c_i $ per unit length. Therefore, the weight of the $ i $ -th interval is $ c_i \cdot (r_i - l_i) $ .

You don't like large weights, so you want to make the sum of weights of the intervals as small as possible. It turns out you can perform all the following three operations:

- rearrange the elements in the array $ l $ in any order;
- rearrange the elements in the array $ r $ in any order;
- rearrange the elements in the array $ c $ in any order.

However, after performing all of the operations, the intervals must still be valid (i.e., for each $ i $ , $ l_i < r_i $ must hold).

What's the minimum possible sum of weights of the intervals after performing the operations?

## 说明/提示

In the first test case, you can make

- $ l = [8, 3] $ ;
- $ r = [23, 12] $ ;
- $ c = [100, 100] $ .

In that case, there are two intervals:

- interval $ [8, 23] $ with weight $ 100 $ per unit length, and $ 100 \cdot (23-8) = 1500 $ in total;
- interval $ [3, 12] $ with weight $ 100 $ per unit length, and $ 100 \cdot (12-3) = 900 $ in total.

The sum of the weights is $ 2400 $ . It can be shown that there is no configuration of final intervals whose sum of weights is less than $ 2400 $ .

In the second test case, you can make

- $ l = [1, 2, 5, 20] $ ;
- $ r = [3, 4, 10, 30] $ ;
- $ c = [3, 3, 2, 2] $ .

In that case, there are four intervals:

- interval $ [1, 3] $ with weight $ 3 $ per unit length, and $ 3 \cdot (3-1) = 6 $ in total;
- interval $ [2, 4] $ with weight $ 3 $ per unit length, and $ 3 \cdot (4-2) = 6 $ in total;
- interval $ [5, 10] $ with weight $ 2 $ per unit length, and $ 2 \cdot (10-5) = 10 $ in total;
- interval $ [20, 30] $ with weight $ 2 $ per unit length, and $ 2 \cdot (30-20) = 20 $ in total.

The sum of the weights is $ 42 $ . It can be shown that there is no configuration of final intervals whose sum of weights is less than $ 42 $ .

## 样例 #1

### 输入

```
2
2
8 3
12 23
100 100
4
20 1 2 5
30 4 3 10
2 3 2 3```

### 输出

```
2400
42```

# AI分析结果



### 综合分析与结论  
**核心思路**：将最小区间差（diff）与最大权重系数（c）配对，总和最小。  
**贪心策略**：  
1. **排序**：l升序排列，r升序排列，c降序排列。  
2. **匹配**：对每个r_i，选择最大的可用l_j（l_j < r_i）生成diff。  
3. **乘法配对**：diff升序与c降序逐项相乘求和。  

**难点对比**：  
- 如何高效找到每个r_i对应的最大l_j？  
  - **栈**：遍历排序后的r，用栈缓存可用的l（Sikiru、gaomingyang101011）。  
  - **平衡树**：动态查询比r_i小的最大l_j（Withershine）。  
  - **并查集**：维护已匹配的l下标（what_can_I_do）。  

**可视化设计**：  
- **动画方案**：  
  1. **排序阶段**：l和r数组元素动态排序，颜色渐变为有序序列。  
  2. **匹配阶段**：高亮当前r_i，弹出栈顶l_j并连线，生成diff。  
  3. **乘法阶段**：diff和c数组以不同颜色对齐，动态显示乘积累加。  
- **复古像素风格**：用8位色块表示l/r/c元素，音效提示匹配成功。  
- **交互功能**：步进控制、速度调节，对比不同数据结构的匹配过程。  

---

### 题解清单（评分≥4星）  
1. **Sikiru（★★★★★）**  
   - **亮点**：栈实现简洁高效，代码可读性强，复杂度O(n log n)。  
   - **关键代码**：  
     ```cpp  
     stack<int> s;  
     for (r_i in sorted_r) {  
         while (l[p] < r_i) s.push(l[p++]);  
         diff[i] = r_i - s.top();  
     }  
     ```  

2. **zcxnb（★★★★☆）**  
   - **亮点**：代码简洁，栈与排序逻辑清晰，适合教学演示。  
   - **个人心得**：“贪心选择需先排序，栈缓存l是关键”。  

3. **what_can_I_do（★★★★☆）**  
   - **亮点**：用并查集维护已匹配的l下标，避免重复选择。  
   - **关键代码**：  
     ```cpp  
     int k = lower_bound(l, r_i) - 1;  
     k = find(k); // 并查集找可用l  
     ```  

---

### 最优思路与技巧提炼  
1. **排序策略**：  
   - l和r必须升序排序，确保每个r_i能匹配最大的可用l_j。  
2. **栈缓存法**：  
   - 遍历排序后的r，将l中小于r_i的元素压栈，栈顶即最大l_j。  
3. **乘法配对**：  
   - diff升序与c降序逐项相乘，总和最小（排序不等式）。  

---

### 同类型题与算法套路  
**通用贪心模板**：  
1. **排序配对**：将两组数据排序后按序匹配（如小乘大、大乘大）。  
2. **区间调度**：选择不重叠区间最大化数量（按结束时间排序）。  
3. **最小化代价**：通过排序和优先级队列动态选择最优解。  

**推荐题目**：  
1. **P1223 排队接水**（贪心排序求最小等待时间）。  
2. **P1090 合并果子**（优先队列实现最小合并代价）。  
3. **P1012 拼数**（字符串排序拼接最大数）。  

---

### 个人心得摘录  
- **栈的妙用**：后进先出特性天然适配“最大可用l_j”需求。  
- **数据类型陷阱**：diff和c可能很大，必须用long long避免溢出。  
- **排序验证**：通过数学证明（排序不等式）确认贪心正确性。  

---

### 代码实现（Sikiru版核心逻辑）  
```cpp  
sort(l, l + n);  
sort(r, r + n);  
stack<int> s;  
int p = 0;  
for (int i = 0; i < n; ++i) {  
    while (p < n && l[p] < r[i]) s.push(l[p++]);  
    diff[i] = r[i] - s.top();  
    s.pop();  
}  
sort(diff, diff + n);  
sort(c, c + n, greater<int>());  
long long ans = 0;  
for (int i = 0; i < n; ++i) ans += diff[i] * c[i];  
```  

---

### 可视化与复古游戏化设计  
**像素动画设计**：  
1. **排序阶段**：l/r数组元素用绿色/红色像素块，动态冒泡排序。  
2. **匹配阶段**：当前r_i高亮为黄色，栈顶l_j闪烁蓝色，连线生成diff。  
3. **音效设计**：  
   - 匹配成功：8-bit“哔”声。  
   - 计算完成：胜利音效+得分显示。  

**AI自动演示**：  
- 自动按步执行，间隔500ms，可暂停/加速。  
- 错误匹配触发“警告音”并回退步骤。  

**关卡积分**：  
- 每正确匹配一个r_i得10分，连击加倍。  
- 最终总分与历史最佳对比，解锁不同像素成就图标。

---
处理用时：81.47秒