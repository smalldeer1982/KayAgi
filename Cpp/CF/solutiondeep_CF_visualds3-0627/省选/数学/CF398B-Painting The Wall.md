# 题目信息

# Painting The Wall

## 题目描述

User ainta decided to paint a wall. The wall consists of $ n^{2} $ tiles, that are arranged in an $ n×n $ table. Some tiles are painted, and the others are not. As he wants to paint it beautifully, he will follow the rules below.

1. Firstly user ainta looks at the wall. If there is at least one painted cell on each row and at least one painted cell on each column, he stops coloring. Otherwise, he goes to step 2.
2. User ainta choose any tile on the wall with uniform probability.
3. If the tile he has chosen is not painted, he paints the tile. Otherwise, he ignores it.
4. Then he takes a rest for one minute even if he doesn't paint the tile. And then ainta goes to step 1.

However ainta is worried if it would take too much time to finish this work. So he wants to calculate the expected time needed to paint the wall by the method above. Help him find the expected time. You can assume that choosing and painting any tile consumes no time at all.

## 样例 #1

### 输入

```
5 2
2 3
4 1
```

### 输出

```
11.7669491886
```

## 样例 #2

### 输入

```
2 2
1 1
1 2
```

### 输出

```
2.0000000000
```

## 样例 #3

### 输入

```
1 1
1 1
```

### 输出

```
0.0000000000
```

# AI分析结果



## 【唯一算法分类】  
组合数学  

---

## 【题解思路、算法要点与解决难点】  
### **核心思路**  
- **状态设计**：定义 `dp[i][j]` 表示还剩 `i` 行和 `j` 列未涂色时的期望步数。  
- **转移方程**：每次操作可能影响四种情况：  
  1. 选中行和列均未涂的格子，概率为 `i*j/n²`，转移至 `dp[i-1][j-1]`  
  2. 选中行已涂、列未涂的格子，概率为 `(n-i)*j/n²`，转移至 `dp[i][j-1]`  
  3. 选中列已涂、行未涂的格子，概率为 `i*(n-j)/n²`，转移至 `dp[i-1][j]`  
  4. 选中已涂区域，概率为 `(n-i)*(n-j)/n²`，保持 `dp[i][j]`  
  通过全期望公式推导并移项得到递推式：  
  ```math
  dp[i][j] = \frac{n² + i j \cdot dp[i-1][j-1] + i(n-j) \cdot dp[i-1][j] + (n-i)j \cdot dp[i][j-1]}{n(i+j) - i j}
  ```  
- **边界条件**：  
  - `dp[0][0] = 0`  
  - `dp[i][0]` 和 `dp[0][i]` 为调和级数求和：`dp[i][0] = dp[i-1][0] + n/i`  

### **解决难点**  
- **自环处理**：通过移项消除方程中的 `dp[i][j]` 自指项。  
- **概率推导**：精确计算四种转移情况的概率，确保分母和分子正确对应。  

---

## 【题解评分 (≥4星)】  
1. **Aoki_灏 (5星)**  
   - 思路清晰，详细推导期望公式与状态转移。  
   - 代码简洁，预处理边界条件逻辑明确。  
   - 关键亮点：数学推导完整，代码可读性强。  

2. **c202201 (4星)**  
   - 分步解析四种转移情况，公式推导详细。  
   - 代码实现与公式严格对应，变量命名直观。  
   - 关键亮点：边界条件处理代码简洁。  

3. **codecode (4星)**  
   - 类比经典期望问题（优惠券收集），降低理解难度。  
   - 代码结构清晰，注释明确。  
   - 关键亮点：结合经典模型，提升思维迁移性。  

---

## 【最优思路或技巧提炼】  
1. **状态压缩**：仅需记录未涂色的行/列数，无需关心具体位置。  
2. **调和级数优化**：边界条件 `dp[i][0]` 直接通过调和级数公式计算，避免递归。  
3. **方程化简**：通过移项消除自环项，避免迭代计算。  

---

## 【同类型题与算法套路】  
- **常见模型**：优惠券收集问题、马尔可夫链期望问题。  
- **通用套路**：  
  1. 定义状态为未完成的目标数量。  
  2. 列出全期望公式并化简。  
  3. 预处理边界条件，按拓扑序递推。  

---

## 【推荐类似题目】  
1. **P1291 [SHOI2002] 百事世界杯之旅**（优惠券收集问题）  
2. **P4550 收集邮票**（双重期望递推）  
3. **P3750 [六省联考 2017] 分手是祝愿**（概率DP与期望结合）  

---

## 【个人心得摘录】  
- **ww3113306**：  
  > “倒推可能导致初始条件复杂化，正推更符合直觉。”  
- **OtterZ**：  
  > “将已涂色行列移到左下角简化分析，是马尔可夫链建模的关键。”  

---

## 【可视化与算法演示】  
### **动画设计**  
- **网格视图**：以 `n×n` 网格展示当前未涂色的行列，高亮 `dp[i][j]` 的计算位置。  
- **公式推导**：分步显示四种转移概率，动态计算分子和分母。  
- **像素风格**：  
  - **颜色标记**：红色表示未涂色行列，绿色表示已涂色区域。  
  - **音效触发**：计算完成时播放 8-bit 音效，错误时短促提示。  

### **交互功能**  
- **步进控制**：支持暂停/继续，调节动画速度。  
- **自动推导**：模拟 AI 自动填充 DP 表，展示递推路径。  

---

## 【核心代码实现】  
```cpp
double dp[N][N];
int n, m, remain_row, remain_col;
bool row[N], col[N];

int main() {
    scanf("%d%d", &n, &m);
    remain_row = remain_col = n;
    for (int i = 0; i < m; i++) {
        int x, y; scanf("%d%d", &x, &y);
        if (!row[x]) row[x] = true, remain_row--;
        if (!col[y]) col[y] = true, remain_col--;
    }

    // 边界条件：行或列为0时的调和级数
    for (int i = 1; i <= n; i++) {
        dp[i][0] = dp[i-1][0] + (double)n / i;
        dp[0][i] = dp[0][i-1] + (double)n / i;
    }

    // DP递推
    for (int i = 1; i <= remain_row; i++) {
        for (int j = 1; j <= remain_col; j++) {
            double numerator = n*n + i*j*dp[i-1][j-1] 
                            + i*(n-j)*dp[i-1][j] 
                            + (n-i)*j*dp[i][j-1];
            double denominator = n*(i + j) - i*j;
            dp[i][j] = numerator / denominator;
        }
    }
    printf("%.10f\n", dp[remain_row][remain_col]);
    return 0;
}
```

---
处理用时：73.29秒