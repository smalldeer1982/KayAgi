# 题目信息

# Dreamoon and Notepad

## 题目描述

Dreamoon has just created a document of hard problems using notepad.exe. The document consists of $ n $ lines of text, $ a_{i} $ denotes the length of the $ i $ -th line. He now wants to know what is the fastest way to move the cursor around because the document is really long.

Let $ (r,c) $ be a current cursor position, where $ r $ is row number and $ c $ is position of cursor in the row. We have $ 1<=r<=n $ and $ 0<=c<=a_{r} $ .

We can use following six operations in notepad.exe to move our cursor assuming the current cursor position is at $ (r,c) $ :

1. up key: the new cursor position $ (nr,nc)=(max(r-1,1),min(a_{nr},c)) $
2. down key: the new cursor position $ (nr,nc)=(min(r+1,n),min(a_{nr},c)) $
3. left key: the new cursor position $ (nr,nc)=(r,max(0,c-1)) $
4. right key: the new cursor position $ (nr,nc)=(r,min(a_{nr},c+1)) $
5. HOME key: the new cursor position $ (nr,nc)=(r,0) $
6. END key: the new cursor position $ (nr,nc)=(r,a_{r}) $

You're given the document description ( $ n $ and sequence $ a_{i} $ ) and $ q $ queries from Dreamoon. Each query asks what minimal number of key presses is needed to move the cursor from $ (r_{1},c_{1}) $ to $ (r_{2},c_{2}) $ .

## 说明/提示

In the first sample, the first query can be solved with keys: HOME, right.

The second query can be solved with keys: down, down, down, END, down.

The third query can be solved with keys: down, END, down.

The fourth query can be solved with keys: END, down.

## 样例 #1

### 输入

```
9
1 3 5 3 1 3 5 3 1
4
3 5 3 1
3 3 7 3
1 0 3 3
6 0 7 3
```

### 输出

```
2
5
3
2
```

## 样例 #2

### 输入

```
2
10 5
1
1 0 1 5
```

### 输出

```
3
```

# AI分析结果



# 算法分类  
**贪心策略与数据结构优化**

---

## 题解思路与解决难点  

### 核心思路  
1. **分类讨论**：将移动策略分为直接移动、使用HOME键、使用END键、绕行上下方等情况。  
2. **ST表优化**：维护区间最小值，快速计算移动过程中横向位置的最小约束。  
3. **二分查找**：确定使用END键的最优行，例如找到满足 `min(r0, r2) ≤ c2` 的最大行。  

### 解决难点  
- **横向约束**：上下移动时横向位置受目标行长度限制，需快速计算路径中的最小行长度。  
- **绕行优化**：向下或向上绕行时，需考虑行末操作对总步数的影响，通过维护 `a[i]+2i` 和 `a[i]-2i` 等属性快速求解最优路径。  

---

## 最优思路提炼  

### 关键数据结构  
- **ST表**：预处理区间最小值，支持 O(1) 查询，用于快速确定 `min(r1, r2)`。  
- **二分法**：确定使用END键的最优行，例如在区间 `[r1, r2]` 中二分寻找满足条件的最小行。  

### 核心策略  
1. **直接移动**：纵向移动后横向调整，代价为 `r2 - r1 + |c0 - c2|`，其中 `c0` 是路径中的最小行长度。  
2. **使用HOME/END键**：HOME键固定代价为 `c2 + 1`，END键需通过二分找到最优行 `r0`。  
3. **绕行策略**：通过维护 `a[i]+2i` 和 `a[i]-2i` 的ST表，快速计算绕行后的最优代价。  

---

## 代码实现（关键片段）  
```cpp
// ST表预处理与查询
struct RMQ {
    int f[MAXN][20];
    void build(int *a, int n) { /* ... */ }
    int query(int l, int r) { /* ... */ }
} A, U, D;

// 核心二分与计算
auto solve = [&](const vector<Query> Q) -> void {
    for (auto q : Q) {
        int c0 = min(c1, A.query(r1, r2));
        int ans = (r2 - r1) + abs(c0 - c2);
        // 使用HOME键
        ans = min(ans, (r2 - r1) + c2 + 1);
        // 使用END键的二分
        int r0 = Find1(r1, r2);
        if (r0 >= r1) ans = min(ans, (r2 - r1) + (c2 - A.query(r0, r2)) + 1);
        // 绕行下方
        r0 = Find2(r1, r2);
        if (r0 <= n) ans = min(ans, (r0 - r1) + (r0 - r2) + (c2 - A.query(r2, r0)) + mov);
    }
};
```

---

## 可视化设计  

### 动画方案  
- **网格绘制**：用像素风格网格表示每行文本，光标用红色方块表示。  
- **操作高亮**：  
  - **上下移动**：绿色箭头标记移动方向。  
  - **HOME/END键**：黄色闪光特效。  
  - **绕行路径**：蓝色虚线标记绕行路线。  
- **音效设计**：  
  - 移动时播放“滴”声，使用按键时播放“咔嚓”声，成功时播放上扬音效。  

### 交互功能  
- **步进控制**：允许单步执行，观察二分查找和ST表查询过程。  
- **参数调节**：可调整动画速度，查看不同查询的路径差异。  

---

## 相似题目  
1. **洛谷 P1886**：滑动窗口（区间极值查询）  
2. **洛谷 P1440**：求区间最小值（单调队列优化）  
3. **洛谷 P1908**：逆序对（分治与数据结构结合）  

---

## 个人心得  
- **踩坑教训**：未考虑绕行后是否需要额外操作（如END键的 `+1` 代价），需仔细分类讨论。  
- **调试技巧**：构造极端样例（如所有行长度为1）验证边界条件。  

--- 

# 题解评分与推荐  

### 高分题解（≥4星）  
1. **DaiRuiChen007（5星）**  
   - **亮点**：系统分类讨论，ST表与二分结合，代码清晰。  
   - **代码可读性**：结构清晰，注释明确。  

2. **Tyyyyyy（4星）**  
   - **亮点**：单调栈与线段树优化，思路新颖。  
   - **优化点**：实现稍复杂，但覆盖了更多边界情况。  

3. **青白呀（4星）**  
   - **亮点**：线段树维护多属性，分情况细致。  
   - **实践性**：代码较长但模块化设计便于调试。  

---

## 完整代码  
[DaiRuiChen007的代码](#)（已嵌入关键注释，完整代码见原文）

---
处理用时：72.87秒