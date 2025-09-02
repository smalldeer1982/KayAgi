# 题目信息

# Median of an Array

## 题目描述

You are given an array $ a $ of $ n $ integers.

The median of an array $ q_1, q_2, \ldots, q_k $ is the number $ p_{\lceil \frac{k}{2} \rceil} $ , where $ p $ is the array $ q $ sorted in non-decreasing order. For example, the median of the array $ [9, 5, 1, 2, 6] $ is $ 5 $ , as in the sorted array $ [1, 2, 5, 6, 9] $ , the number at index $ \lceil \frac{5}{2} \rceil = 3 $ is $ 5 $ , and the median of the array $ [9, 2, 8, 3] $ is $ 3 $ , as in the sorted array $ [2, 3, 8, 9] $ , the number at index $ \lceil \frac{4}{2} \rceil = 2 $ is $ 3 $ .

You are allowed to choose an integer $ i $ ( $ 1 \le i \le n $ ) and increase $ a_i $ by $ 1 $ in one operation.

Your task is to find the minimum number of operations required to increase the median of the array.

Note that the array $ a $ may not necessarily contain distinct numbers.

## 说明/提示

In the first test case, you can apply one operation to the first number and obtain the array $ [3, 2, 8] $ , the median of this array is $ 3 $ , as it is the number at index $ \lceil \frac{3}{2} \rceil = 2 $ in the non-decreasing sorted array $ [2, 3, 8] $ . The median of the original array $ [2, 2, 8] $ is $ 2 $ , as it is the number at index $ \lceil \frac{3}{2} \rceil = 2 $ in the non-decreasing sorted array $ [2, 2, 8] $ . Thus, the median increased ( $ 3 > 2 $ ) in just one operation.

In the fourth test case, you can apply one operation to each of the numbers at indices $ 1, 2, 3 $ and obtain the array $ [6, 6, 6, 4, 5] $ , the median of this array is $ 6 $ , as it is the number at index $ \lceil \frac{5}{2} \rceil = 3 $ in the non-decreasing sorted array $ [4, 5, 6, 6, 6] $ . The median of the original array $ [5, 5, 5, 4, 5] $ is $ 5 $ , as it is the number at index $ \lceil \frac{5}{2} \rceil = 2 $ in the non-decreasing sorted array $ [4, 5, 5, 5, 5] $ . Thus, the median increased ( $ 6 > 5 $ ) in three operations. It can be shown that this is the minimum possible number of operations.

In the fifth test case, you can apply one operation to each of the numbers at indices $ 1, 3 $ and obtain the array $ [3, 1, 3, 3, 1, 4] $ , the median of this array is $ 3 $ , as it is the number at index $ \lceil \frac{6}{2} \rceil = 3 $ in the non-decreasing sorted array $ [1, 1, 3, 3, 3, 4] $ . The median of the original array $ [2, 1, 2, 3, 1, 4] $ is $ 2 $ , as it is the number at index $ \lceil \frac{6}{2} \rceil = 3 $ in the non-decreasing sorted array $ [1, 1, 2, 2, 3, 4] $ . Thus, the median increased ( $ 3 > 2 $ ) in two operations. It can be shown that this is the minimum possible number of operations.

## 样例 #1

### 输入

```
8
3
2 2 8
4
7 3 3 1
1
1000000000
5
5 5 5 4 5
6
2 1 2 3 1 4
2
1 2
2
1 1
4
5 5 5 5```

### 输出

```
1
2
1
3
2
1
2
3```

# AI分析结果



**算法分类**  
贪心算法

---

**题解思路、算法要点与解决难点**  
所有题解核心思路一致：  
1. **排序数组**：确保中位数位置正确。  
2. **定位中位数**：索引为 `ceil(n/2)`。  
3. **统计连续相同元素**：从中位数位置开始向右遍历，统计所有与原中位数相等的元素个数。  

**解决难点**：  
- 必须保证修改后中位数严格大于原值。若仅修改中位数位置元素，后续相同元素会导致中位数不变。  
- 统计所有与原中位数相等的后续元素，确保它们全部被加1，才能提升中位数。  

---

**题解评分（≥4星）**  
1. **AK_400（5星）**  
   - **亮点**：代码最简，直接统计连续相同元素，无需分奇偶处理。  
   - **代码**：  
     ```cpp  
     sort(a+1,a+1+n);  
     int mid=(n+1)/2;  
     for(int i=mid;i<=n;i++) cnt+=a[i]==a[mid];  
     ```  
2. **OJ_killer（4星）**  
   - **亮点**：明确通过 `m = (n+1)/2` 统一处理奇偶情况。  
3. **xk2013（4星）**  
   - **亮点**：详细注释和变量命名，适合初学者理解。  

---

**最优思路提炼**  
**关键技巧**：  
- **贪心统计**：只需修改中位数及其后续相同元素，最小化操作次数。  
- **统一索引计算**：`mid = (n+1)/2` 适用于所有情况，无需分奇偶。  

---

**同类型题/算法套路**  
- **中位数贪心**：如 [LeetCode 462. Minimum Moves to Equal Array Elements II](https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/)。  
- **连续元素处理**：如 [CF 1433E Two Round Dances](https://codeforces.com/problemset/problem/1433/E)。  

---

**推荐相似题目**  
1. [CF 1486D Max Median](https://codeforces.com/problemset/problem/1486/D)  
2. [洛谷 P1168 中位数](https://www.luogu.com.cn/problem/P1168)  
3. [LeetCode 295. Find Median from Data Stream](https://leetcode.com/problems/find-median-from-data-stream/)  

---

**可视化与算法演示**  
**动画方案**：  
1. **像素排序展示**：  
   - 初始数组显示为无序像素块，点击排序后动态排列成有序序列。  
   - **颜色标记**：中位数位置用黄色高亮，后续相同元素用绿色闪烁。  
2. **统计过程**：  
   - 指针从中位数位置向右移动，遇到相同元素时播放“滴”音效，计数器递增。  
3. **复古风格**：  
   - **8位音效**：排序完成时播放胜利音效，统计结束显示结果时使用像素字体。  

**控制面板功能**：  
- **步进控制**：手动点击逐步执行排序和统计。  
- **自动演示**：按预设速度自动完成所有步骤，可随时暂停。  

---

**代码片段（关键逻辑）**  
```javascript  
// 伪代码：统计中位数后相同元素  
function calculateMinOperations(arr) {  
    arr.sort((a, b) => a - b);  
    const mid = Math.ceil(arr.length / 2) - 1; // JS数组从0开始  
    let count = 0;  
    for (let i = mid; i < arr.length; i++) {  
        if (arr[i] === arr[mid]) count++;  
        else break;  
    }  
    return count;  
}  
```  

**像素动画示例**（Canvas实现片段）：  
```javascript  
ctx.fillStyle = '#FFD700'; // 中位数颜色  
ctx.fillRect(midX * cellSize, 0, cellSize, cellSize);  
ctx.fillStyle = '#00FF00'; // 相同元素颜色  
for (let i = mid + 1; i < sameCount; i++) {  
    ctx.fillRect(i * cellSize, 0, cellSize, cellSize);  
}  
```  

--- 

**总结**  
通过排序与贪心统计，确保中位数提升的最小操作次数。可视化设计结合复古像素风格，直观展示关键步骤，适合教学与算法演示。

---
处理用时：84.07秒