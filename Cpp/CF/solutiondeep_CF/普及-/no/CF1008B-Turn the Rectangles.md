# 题目信息

# Turn the Rectangles

## 题目描述

There are $ n $ rectangles in a row. You can either turn each rectangle by $ 90 $ degrees or leave it as it is. If you turn a rectangle, its width will be height, and its height will be width. Notice that you can turn any number of rectangles, you also can turn all or none of them. You can not change the order of the rectangles.

Find out if there is a way to make the rectangles go in order of non-ascending height. In other words, after all the turns, a height of every rectangle has to be not greater than the height of the previous rectangle (if it is such).

## 说明/提示

In the first test, you can rotate the second and the third rectangles so that the heights will be \[4, 4, 3\].

In the second test, there is no way the second rectangle will be not higher than the first one.

## 样例 #1

### 输入

```
3
3 4
4 6
3 5
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
2
3 4
5 5
```

### 输出

```
NO
```

# AI分析结果



# 翻转矩形

## 题目描述  
给定一行排列的 $n$ 个矩形。每个矩形可以旋转 90 度（交换宽高）或保持原状。请判断是否存在一种旋转方式，使得所有矩形的高度构成非递增序列（每个矩形的高度不大于前一个的高度）。

## 输入输出样例  
示例 1：  
输入：  
3  
3 4  
4 6  
3 5  
输出：  
YES  

示例 2：  
输入：  
2  
3 4  
5 5  
输出：  
NO  

**算法分类**：贪心

---

### 题解综合分析  
所有题解均采用贪心策略，核心思路是：从前向后遍历，每个矩形尽可能选择最大的可用高度，同时不超过前一个高度。关键差异在于条件判断的顺序和边界处理方式。

#### 高分题解推荐
1. **alex_liu（★★★★☆）**  
   **关键亮点**：  
   - 使用极大值初始化前序高度，避免单独处理第一个矩形  
   - 通过严格的条件分支覆盖所有可能情况  
   **核心代码**：  
   ```cpp
   if(x>first&&y>first) return 0; // 双超必败
   else if(x>first) first=y;      // 只能选y
   else if(y>first) first=x;      // 只能选x
   else first=max(x,y);           // 选较大者
   ```

2. **codesonic（★★★★☆）**  
   **关键亮点**：  
   - 代码最简，仅用两个条件判断覆盖所有情况  
   - 通过 max/min 函数快速判定可选范围  
   **核心代码**：  
   ```cpp
   if(max(x,y)<=last) last=max(x,y);
   else if(min(x,y)<=last) last=min(x,y);
   else return 0;
   ```

3. **_lgh_（★★★★☆）**  
   **优化技巧**：  
   - 边输入边处理，提前终止无效情况  
   - 通过交换操作统一处理方向，减少条件判断  
   **代码亮点**：  
   ```cpp
   if(x<y) swap(x,y); // 统一将较大值置于x
   if(x>shang) {
       if(y>shang) return 0;
       else shang=y;
   }
   ```

---

### 最优思路总结  
**核心贪心策略**：  
1. 初始化前序高度为极大值  
2. 对每个矩形，优先尝试选较大边作为当前高度  
3. 若较大边超过前序高度，则尝试较小边  
4. 若两方向都超限则判定失败  

**实现技巧**：  
- 使用 `max()` 和 `min()` 简化条件判断  
- 初始值设为极大值可避免单独处理首元素  
- 边输入边处理可提前退出无效情况  

---

### 拓展建议  
类似贪心问题：  
1. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)（双指针配对）  
2. [P1233 木棍加工](https://www.luogu.com.cn/problem/P1233)（二维排序后求LIS）  
3. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)（单调栈维护递减序列）  

---

### 题解心得摘录  
- **BADFIVE**：`sum=0x3f3f3f3f` 的初始值设置避免了特判首元素  
- **zjr0330**：最初想用 DFS 但意识到贪心更高效，体现算法选择的重要性  
- **MuYC**：通过 VP 比赛实践验证思路，强调贪心策略的直觉培养

---
处理用时：38.22秒