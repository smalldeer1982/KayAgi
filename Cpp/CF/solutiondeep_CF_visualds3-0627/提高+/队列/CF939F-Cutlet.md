# 题目信息

# Cutlet

## 题目描述

Arkady wants to have a dinner. He has just returned from a shop where he has bought a semifinished cutlet. He only needs to fry it. The cutlet should be fried for $ 2n $ seconds, in particular, it should be fried for $ n $ seconds on one side and $ n $ seconds on the other side. Arkady has already got a frying pan and turn on fire, but understood that maybe he won't be able to flip the cutlet exactly after $ n $ seconds after the beginning of cooking.

Arkady is too busy with sorting sticker packs in his favorite messenger and can flip the cutlet only in some periods of time. Namely, there are $ k $ periods of time in which he can do it, the $ i $ -th of them is an interval of time from $ l_{i} $ seconds after he starts cooking till $ r_{i} $ seconds, inclusive. Arkady decided that it's not required to flip the cutlet exactly in the middle of cooking, instead, he will flip it several times in such a way that the cutlet will be fried exactly $ n $ seconds on one side and $ n $ seconds on the other side in total.

Help Arkady and find out if it's possible for him to cook the cutlet, if he is able to flip the cutlet only in given periods of time; and if yes, find the minimum number of flips he needs to cook the cutlet.

## 说明/提示

In the first example Arkady should flip the cutlet in time moment $ 3 $ seconds after he starts cooking and in time moment $ 13 $ seconds after he starts cooking.

In the second example, Arkady can flip the cutlet at $ 10 $ seconds after he starts cooking.

## 样例 #1

### 输入

```
10 2
3 5
11 13
```

### 输出

```
Full
2
```

## 样例 #2

### 输入

```
10 3
3 5
9 10
11 13
```

### 输出

```
Full
1
```

## 样例 #3

### 输入

```
20 1
3 19
```

### 输出

```
Hungry
```

# AI分析结果



**唯一算法分类**  
动态规划（DP）与单调队列优化

---

### **题解思路、算法要点与解决难点**  
1. **核心思路**  
   - 动态规划状态定义为 `f[i][j]` 表示处理到第 `i` 个时间段结束时，未被煎的面（背面）已累计煎 `j` 秒的最小翻转次数。  
   - 每个时间段内最多翻转两次（多次翻转可等效为 0/1/2 次），分三种情况转移：  
     - **不翻转**：直接继承上一阶段状态。  
     - **翻转一次**：枚举翻转时间点，通过单调队列维护区间最小值。  
     - **翻转两次**：同样用单调队列优化，维护有效区间的最小值。  

2. **关键难点**  
   - **状态转移的优化**：直接枚举时间点会导致 `O(n^2)` 复杂度，需用单调队列将每次转移降为 `O(1)`。  
   - **滚动数组空间优化**：用滚动数组存储当前和上一阶段的状态，空间复杂度从 `O(nk)` 降为 `O(n)`。  

3. **算法实现要点**  
   - **翻转一次**的转移需倒序处理 `j`，维护 `[l_i - j, r_i - j]` 的单调队列。  
   - **翻转两次**的转移需正序处理 `j`，维护 `[j - (r_i - l_i), j]` 的单调队列。  

---

### **题解评分 (≥4星)**  
1. **Kelin（5星）**  
   - **亮点**：代码简洁高效，滚动数组和单调队列实现清晰，注释详细。  
   - **代码片段**：  
     ```cpp  
     h=1,t=0;  
     fp(j,0,min(n,r)){  
         while(h<=t&&f[p^1][j]<=f[p^1][q[t]])--t;  
         while(h<=t&&q[h]<j-(r-l))++h; q[++t]=j;  
         cmin(f[p][j],f[p^1][q[h]]+2);  
     }  
     ```  
   - **个人心得**：通过分情况讨论翻转次数，避免冗余计算。  

2. **yc20170111（4星）**  
   - **亮点**：状态转移方程推导详细，适合理解数学逻辑。  
   - **代码片段**：  
     ```cpp  
     while(h<=t&&q[h]<j-r+l)++h;  
     while(h<=t&&f[!(i&1)][q[t]]>f[!(i&1)][j])--t;  
     q[++t]=j; f[i&1][j]=min(f[i&1][j],f[!(i&1)][q[h]]+2);  
     ```  

3. **hstt（4星）**  
   - **亮点**：状态定义明确，代码注释清晰，适合初学者。  
   - **个人心得**：强调翻转次数的等效性，避免复杂枚举。  

---

### **最优思路或技巧提炼**  
- **单调队列优化**：将区间最值查询从 `O(n)` 降为 `O(1)`，核心在于维护队列的单调性和下标范围。  
- **滚动数组**：仅保留当前和上一阶段的状态，节省空间。  
- **分情况讨论翻转次数**：将复杂问题分解为有限次翻转的逻辑，简化状态转移。  

---

### **同类型题或类似算法套路**  
- **滑动窗口最值**：如 [Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/)。  
- **动态规划优化**：如任务调度中的时间分片优化（[CF1025D](https://codeforces.com/problemset/problem/1025/D)）。  

---

### **推荐相似题目**  
1. [P1725 琪露诺](https://www.luogu.com.cn/problem/P1725)  
2. [P3957 跳房子](https://www.luogu.com.cn/problem/P3957)  
3. [CF372C Watching Fireworks is Fun](https://codeforces.com/problemset/problem/372/C)  

---

### **可视化与算法演示**  
1. **动画设计**  
   - **网格视图**：横向为时间轴（时间段），纵向为 `j` 值（背面已煎时间），每个格子颜色表示 `f[j]` 的值。  
   - **高亮当前操作**：  
     - **红色方块**：当前处理的 `j` 值。  
     - **绿色队列**：单调队列的有效区间，动态显示入队和出队。  
   - **步进控制**：支持暂停/继续，调整动画速度观察队列变化。  

2. **复古像素风格**  
   - **8-bit 音效**：翻转时播放“哔”声，找到最优解时播放胜利音效。  
   - **Canvas 绘制**：用像素块表示 `f[j]` 值，颜色深浅反映数值大小。  

**代码片段（Canvas 绘制示例）**  
```javascript  
function drawGrid(ctx, f, currentJ) {  
    for (let j = 0; j <= n; j++) {  
        const color = f[j] === INF ? 0 : 255 - Math.min(255, f[j] * 10);  
        ctx.fillStyle = `rgb(${color}, ${color}, ${color})`;  
        ctx.fillRect(j * 10, currentJ * 10, 10, 10);  
        if (j === currentJ) {  
            ctx.fillStyle = 'red';  
            ctx.fillRect(j * 10, currentJ * 10, 10, 2);  
        }  
    }  
}  
```  

---

**总结**  
本题通过动态规划与单调队列优化，高效处理时间区间内的状态转移。核心在于分情况讨论翻转次数，并通过滑动窗口维护区间最值。可视化设计可通过网格和像素动画直观展示状态变化，增强学习体验。

---
处理用时：71.91秒