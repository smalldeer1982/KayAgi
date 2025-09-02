# 题目信息

# [USACO13NOV] No Change G

## 题目描述

Farmer John is at the market to purchase supplies for his farm.  He has in his pocket K coins (1 <= K <= 16), each with value in the range 1..100,000,000.  FJ would like to make a sequence of N purchases (1 <= N <= 100,000), where the ith purchase costs c(i) units of money (1 <= c(i) <= 10,000).  As he makes this sequence of purchases, he can periodically stop and pay, with a single coin, for all the purchases made since his last payment (of course, the single coin he uses must be large enough to pay for all of these).  Unfortunately, the vendors at the market are completely out of change, so whenever FJ uses a coin that is larger than the amount of money he owes, he sadly receives no changes in return!

Please compute the maximum amount of money FJ can end up with after making his N purchases in sequence.  Output -1 if it is impossible for FJ to make all of his purchases.

约翰到商场购物，他的钱包里有K(1 <= K <= 16)个硬币，面值的范围是1..100,000,000。

约翰想按顺序买 N个物品(1 <= N <= 100,000)，第i个物品需要花费c(i)块钱，(1 <= c(i) <= 10,000)。

在依次进行的购买N个物品的过程中，约翰可以随时停下来付款，每次付款只用一个硬币，支付购买的内容是从上一次支付后开始到现在的这些所有物品（前提是该硬币足以支付这些物品的费用）。不幸的是，商场的收银机坏了，如果约翰支付的硬币面值大于所需的费用，他不会得到任何找零。

请计算出在购买完N个物品后，约翰最多剩下多少钱。如果无法完成购买，输出-1


## 说明/提示

FJ has 3 coins of values 12, 15, and 10.  He must make purchases in sequence of value 6, 3, 3, 2, 3, and 7.


FJ spends his 10-unit coin on the first two purchases, then the 15-unit coin on the remaining purchases.  This leaves him with the 12-unit coin.


## 样例 #1

### 输入

```
3 6 
12 
15 
10 
6 
3 
3 
2 
3 
7 
```

### 输出

```
12 
```

# AI分析结果



## 算法分类
**状态压缩动态规划（状压DP）**

---

## 题解思路与解决难点

### 核心思路
1. **状态设计**：用二进制位表示硬币使用状态，`dp[i]`表示状态`i`能覆盖的最远物品位置，`f[i]`记录总花费。
2. **转移方法**：枚举每个未使用的硬币，计算其能覆盖的连续物品范围（通过前缀和+二分或预处理的区间表）。
3. **优化手段**：  
   - **二分查找**：在状态转移时，通过前缀和与二分快速确定硬币能覆盖的终点。  
   - **双指针预处理**：预先计算每个硬币从每个起点能覆盖的最大终点，实现O(1)查询。

### 解决难点
- **高效覆盖计算**：大物品数下需快速计算硬币覆盖范围，二分和预处理是关键。
- **状态转移顺序**：从小到大枚举状态，确保子状态已处理。
- **边界处理**：前缀和从0开始，确保空状态正确初始化。

---

## 题解评分（≥4星）

1. **jun1lesszZZ（4.5星）**  
   - **亮点**：清晰的状压DP框架，结合二分优化，代码简洁。  
   - **关键代码**：通过`check`函数二分查找覆盖终点，动态更新`dp`数组。

2. **Imakf（4.5星）**  
   - **亮点**：双指针预处理区间表，状态转移O(1)查询，效率更高。  
   - **关键代码**：预处理`far`数组记录每个硬币的覆盖终点，直接查表转移。

3. **UltiMadow（4星）**  
   - **亮点**：代码极简，利用`upper_bound`直接二分，注释清晰。  
   - **关键代码**：通过前缀和与二分动态计算覆盖范围。

---

## 最优思路提炼
1. **状压DP核心结构**  
   ```cpp
   for (int state = 0; state < (1<<k); state++) {
       for (int coin = 0; coin < k; coin++) {
           if (state & (1<<coin)) continue;
           int new_state = state | (1<<coin);
           dp[new_state] = max(dp[new_state], calc_range(state, coin));
       }
   }
   ```
2. **覆盖范围计算优化**  
   **方法1（二分）**：  
   ```cpp
   int find(int start, int value) {
       int l = start, r = n;
       while (l <= r) {
           int mid = (l+r)/2;
           if (sum[mid] - sum[start] <= value) l = mid+1;
           else r = mid-1;
       }
       return r;
   }
   ```
   **方法2（双指针预处理）**：  
   ```cpp
   // 预处理far[i][j]: 硬币i从j开始能覆盖的终点
   for (int i=1; i<=k; i++) {
       int l=1, sum=0;
       for (int r=1; r<=n; r++) {
           sum += cost[r];
           while (sum > coin[i]) sum -= cost[l++];
           far[i][l] = r;
       }
   }
   ```

---

## 类似题目推荐
1. **P1879 [Corn Fields]**：状压DP处理网格覆盖问题。  
2. **P1896 [互不侵犯]**：状压DP处理棋盘放置问题。  
3. **P4329 [COCI2006-2007#1] Bond**：状压DP优化任务分配。

---

## 可视化设计思路
1. **像素风格动画**：  
   - **硬币**：8位像素方块，不同颜色区分硬币面值。  
   - **物品**：连续色块表示购买序列，覆盖时填充硬币颜色。  
   - **状态转移**：二进制位闪烁表示状态变化，覆盖终点动态扩展。

2. **音效设计**：  
   - **硬币使用**：8位"哔"声。  
   - **覆盖成功**：上升音调。  
   - **完全覆盖**：胜利音效。

3. **交互控制**：  
   - **速度调节**：滑块控制动画速度（0.5x-5x）。  
   - **单步执行**：按步观察状态转移细节。  
   - **模式切换**：二分 vs 预处理效果对比。

---

## 核心代码示例（jun1lesszZZ版）
```cpp
int check(int x, int cha) {
    int l = cha, r = n, mid;
    while(l <= r) {
        mid = (l + r) >> 1;
        if(sum[mid] - sum[cha-1] <= x) l = mid+1;
        else r = mid-1;
    }
    return r;
}

for(int i=1; i<(1<<m); i++) {
    for(int j=0; j<m; j++) if(i & (1<<j)) {
        int prev_state = i ^ (1<<j);
        int pos = check(coin[j+1], dp[prev_state]+1);
        if(pos > dp[i]) {
            dp[i] = pos;
            f[i] = f[prev_state] + coin[j+1];
        }
        if(dp[i] == n) ans = min(ans, f[i]);
    }
}
```

---

## 总结
本题通过状压DP将硬币使用状态压缩为二进制，结合前缀和与二分/预处理高效计算覆盖范围，是典型的**状态压缩+优化计算**组合。关键点在于合理设计状态转移和覆盖计算，不同优化方法在时间空间上各有取舍，但核心DP框架一致。

---
处理用时：87.38秒