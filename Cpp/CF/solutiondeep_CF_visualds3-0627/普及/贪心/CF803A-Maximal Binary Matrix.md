# 题目信息

# Maximal Binary Matrix

## 题目描述

You are given matrix with $ n $ rows and $ n $ columns filled with zeroes. You should put $ k $ ones in it in such a way that the resulting matrix is symmetrical with respect to the main diagonal (the diagonal that goes from the top left to the bottom right corner) and is lexicographically maximal.

One matrix is lexicographically greater than the other if the first different number in the first different row from the top in the first matrix is greater than the corresponding number in the second one.

If there exists no such matrix then output -1.

## 样例 #1

### 输入

```
2 1
```

### 输出

```
1 0 
0 0 
```

## 样例 #2

### 输入

```
3 2
```

### 输出

```
1 0 0 
0 1 0 
0 0 0 
```

## 样例 #3

### 输入

```
2 5
```

### 输出

```
-1
```

# AI分析结果



### 题解思路与算法分析

#### **核心贪心策略**
1. **行优先填充**：按行遍历矩阵，每行从左到右处理，优先填充靠前的行和列，确保字典序最大。
2. **对称处理**：非对角线位置需同时填充 `(i,j)` 和 `(j,i)`，消耗 2 个 1；对角线位置 `(i,i)` 仅消耗 1 个 1。
3. **剩余处理**：若最后剩余 1 个 1，必须填充到未使用的对角线位置。

#### **解决难点**
- **字典序最大化**：通过行优先遍历确保前面的行尽可能填满 1。
- **奇偶处理**：当剩余 1 个 1 时，需调整填充策略，确保对称性。
- **边界条件**：特判 `k=0` 或 `k>n²`，直接输出全零或 `-1`。

---

### 题解评分（≥4星）

1. **用户：_Lazy_zhr_（5星）**
   - **亮点**：行优先遍历，代码简洁高效，正确处理奇偶剩余。
   - **代码片段**：
     ```cpp
     for(int i=1;i<=n;i++) for(int j=i;j<=n;j++){
         if(k==0) break;
         if(i==j) a[i][j]=1, k--;
         else if(k>=2) a[i][j]=a[j][i]=1, k-=2;
     }
     ```

2. **用户：syf2008（4星）**
   - **亮点**：简洁的全局遍历，处理对称对，但遍历顺序略有不严谨。
   - **代码片段**：
     ```cpp
     for(int i=1;i<=n;i++) for(int j=1;j<=n;j++){
         if(a[i][j]) continue;
         if(i==j) a[i][j]=1, k--;
         else if(k>=2) a[i][j]=a[j][i]=1, k-=2;
     }
     ```

3. **用户：FJ_OIer（4星）**
   - **亮点**：分层贪心，每层优先填满对称对，处理剩余逻辑清晰。
   - **代码片段**：
     ```cpp
     for(int i=1;i<=n;i++) for(int j=i;j<=n;j++){
         if(k==0) break;
         if(i==j) a[i][j]=1, k--;
         else if(k>=2) a[i][j]=a[j][i]=1, k-=2;
     }
     ```

---

### 最优思路提炼
1. **贪心顺序**：按行遍历，每行从左到右填充，确保字典序最大。
2. **对称填充**：非对角线位置成对填充，对角线单独处理。
3. **剩余处理**：剩余 1 个 1 时填充到最早未使用的对角线位置。

---

### 相似题目推荐
1. **P1090 合并果子**（贪心选择最小代价）
2. **P1223 排队接水**（贪心排序最小等待时间）
3. **P1106 删数问题**（贪心构造字典序最小数）

---

### 可视化设计（复古像素风格）
1. **动画展示**：矩阵以 8-bit 像素网格渲染，当前填充位置高亮为红色，已填充为绿色。
2. **交互功能**：
   - **步进控制**：按空格单步执行，观察填充顺序。
   - **音效提示**：填充时播放 8-bit 音效，剩余 1 时播放警报音。
3. **自动演示**：AI 自动填充，展示贪心策略的逐步决策。

---

### 代码实现（关键贪心逻辑）
```cpp
// 用户：_Lazy_zhr_ 的贪心实现
#include<bits/stdc++.h>
using namespace std;
int n, k, a[105][105];

int main() {
    cin >> n >> k;
    if (k > n*n) { cout << -1; return 0; }
    for (int i=1; i<=n; i++) {
        for (int j=i; j<=n; j++) {
            if (k == 0) break;
            if (i == j) a[i][j] = 1, k--;
            else if (k >= 2) a[i][j] = a[j][i] = 1, k -= 2;
        }
    }
    // 处理剩余 1 个 1
    if (k == 1) {
        for (int i=1; i<=n; i++) {
            if (!a[i][i]) { a[i][i] = 1; break; }
        }
    }
    // 输出矩阵
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) cout << a[i][j] << " ";
        cout << endl;
    }
    return 0;
}
```

---

### 总结
贪心策略通过行优先遍历确保字典序最大，对称填充和剩余处理是关键。可视化设计通过复古风格和交互功能增强理解，同类题目可举一反三。

---
处理用时：170.47秒