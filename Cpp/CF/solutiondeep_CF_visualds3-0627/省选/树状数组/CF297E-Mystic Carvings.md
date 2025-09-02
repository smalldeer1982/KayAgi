# 题目信息

# Mystic Carvings

## 题目描述

The polar bears have discovered a gigantic circular piece of floating ice with some mystic carvings on it. There are $ n $ lines carved on the ice. Each line connects two points on the boundary of the ice (we call these points endpoints). The endpoints are numbered $ 1,2,...,2n $ counter-clockwise along the circumference. No two lines share an endpoint.

Now a group of 6 polar bears (Alice, Bob, Carol, Dave, Eve, Frank) are going to build caves on the endpoints. Each polar bear would build a cave and live in it. No two polar bears can build a cave on the same endpoints. Alice and Bob is a pair of superstitious lovers. They believe the lines are carved by aliens (or humans, which are pretty much the same thing to polar bears), and have certain spiritual power. Therefore they want to build their caves on two endpoints which are connected by a line. The same for Carol and Dave, Eve and Frank.

The distance between two caves X and Y is defined as one plus minimum number of other caves one need to pass through in order to travel from X to Y along the boundary of the ice (endpoints without caves are not counted).

To ensure fairness, the distances between the three pairs of lovers have to be the same (that is, the distance between Alice and Bob, the distance between Carol and Dave, and the distance between Eve and Frank are the same).

The figures below show two different configurations, where the dots on the circle are the endpoints. The configuration on the left is not valid. Although each pair of lovers (A and B, C and D, E and F) is connected a line, the distance requirement is not satisfied. The distance between A and B is 2 (one can go from A to B in the clockwise direction passing through F). The distance between E and F is also 2. However, the distance between C and D is 1 (one can go from C to D in the counter-clockwise direction without passing through any other caves). The configuration on the right is valid. All three pairs have the same distance 1.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF297E/d4294009e1edf87a8acd5f07b8b6190c53a3334c.png)Count the number of ways to build the caves under the requirements. Two configurations are considered the same if the same set of 6 endpoints are used.

## 说明/提示

The second sample corresponds to the figure in the problem statement.

## 样例 #1

### 输入

```
4
5 4
1 2
6 7
8 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
8
1 7
2 4
3 9
5 11
6 8
10 16
13 15
14 12
```

### 输出

```
6
```

# AI分析结果



---

**算法分类**  
组合数学 + 二维偏序 + 容斥原理

---

### **题解思路与算法要点**  
#### **核心问题模型**  
在环形排列的弦中选择三对端点，满足每对端点间的距离相等。将环形问题转化为二维平面上的端点区间关系，通过相交、包含、相离等几何关系进行分类讨论。

#### **关键思路对比**  
1. **stoorz题解**  
   - **容斥框架**：总方案数 $C(n,3)$ 减去非法情况（图1、3、4）。  
   - **二维偏序统计**：  
     - 对每条弦 $i$，计算其左侧不相交的弦数 $l[i]$ 和右侧不相交的弦数 $r[i]$。  
     - 图1的非法数：$\sum l[i] \times r[i]$（中间弦左右各有一条不相交弦）。  
     - 图3/4的非法数：$\frac{1}{2} \sum (l[i]+r[i]) \times (n-l[i]-r[i]-1)$（相交与不相交组合）。  
   - **高效数据结构**：通过三次排序 + 树状数组统计区间端点关系。  

2. **未来姚班zyl题解**  
   - **分类统计**：定义四种区间关系（相离、包含、相交、被包含），分别统计各关系数量。  
   - **容斥公式**：总方案数减去非法组合（包含相交与相离的混合情况）。  
   - **树状数组应用**：通过多轮扫描统计不同条件下的区间数量。  

#### **解决难点**  
- **几何关系转化**：将环形端点映射为线性区间，判断相交/包含需处理复杂的端点大小关系。  
- **高效统计**：利用二维偏序性质，通过树状数组在 $O(n \log n)$ 时间内完成多次区间计数。  
- **去重处理**：非法情况的重复计数需通过除以2修正（如每对相交弦被统计两次）。  

---

### **最优思路提炼**  
**stoorz题解的核心优化**：  
1. **分类讨论非法情况**，通过容斥简化计算。  
2. **三次排序 + 树状数组**精准统计每弦的左右相离数。  
3. **公式推导清晰**，直接计算非法贡献，避免复杂分类。  

**关键代码片段（stoorz）**  
```cpp
// 统计左侧不相交弦数 l[i]
sort(a+1, a+1+n, cmp1);  // 按左端点升序排序
for (int i=1; i<=n; i++) {
    // 左侧满足 x' < x 且 y' < x 或 y' > y 的弦数
    l[a[i].id] += bit.ask(a[i].x) + (bit.ask(2n) - bit.ask(a[i].y));
    bit.add(a[i].y, 1);  // 将当前弦右端点加入树状数组
}

// 统计右侧不相交弦数 r[i]
memset(bit.c, 0, sizeof(bit.c));
sort(a+1, a+1+n, cmp2);  // 按右端点降序排序
for (int i=1; i<=n; i++) {
    // 右侧满足 x' > x 且 y' < y 的弦数
    r[a[i].id] += bit.ask(a[i].y) - bit.ask(a[i].x);
    bit.add(a[i].y, 1);
}
```

---

### **同类型题与算法套路**  
- **二维偏序**：适用于区间统计问题（如逆序对、区间包含计数）。  
- **容斥原理**：在组合计数中，总合法数 = 全集 - 非法子集并集。  
- **树状数组优化**：高效维护动态前缀和，支持多次区间查询。  

**类似题目推荐**  
1. [CF1396C - Monster Invaders](https://codeforces.com/problemset/problem/1396/C)（二维偏序）  
2. [洛谷 P1908 逆序对](https://www.luogu.com.cn/problem/P1908)（树状数组应用）  
3. [CF1311F - Moving Points](https://codeforces.com/problemset/problem/1311/F)（离散化 + 偏序统计）  

---

### **题解评分**  
1. **stoorz（5星）**  
   - 思路清晰，公式推导严谨，代码结构简洁。  
   - 树状数组操作与排序逻辑紧密对应，易理解。  

2. **未来姚班zyl（3星）**  
   - 思路正确但变量命名复杂（如ct1-ct4），代码可读性较低。  
   - 统计方法稍显冗余，未明确说明分类依据。  

---

### **可视化与算法演示**  
**动画设计要点**  
1. **环形弦可视化**：在Canvas中以圆环显示所有弦，用颜色区分合法/非法组合。  
2. **树状数组操作**：动态高亮当前处理的弦端点，展示树状数组的更新与查询过程。  
3. **步进控制**：允许单步执行排序、树状数组更新，观察l[i]/r[i]的计算步骤。  

**复古像素风格实现**  
- **颜色方案**：8色调色板（红/绿/蓝分别表示三种合法对，灰为非法）。  
- **音效设计**：  
  - 添加端点时播放短促「滴」声。  
  - 计算完成时播放胜利音效（合法组合高亮）。  
- **自动演示模式**：AI按排序顺序逐步处理弦，树状数组数值实时显示在右侧面板。  

---

### **个人心得摘录**  
> "通过二维偏序将环形问题转化为线性排序，是本题的关键突破口。调试时需特别注意端点相等的情况，排序时的稳定性直接影响统计结果。" —— stoorz  

---

**完整代码（stoorz）**  
见原题解部分，核心逻辑已提炼至关键代码片段。

---
处理用时：104.05秒